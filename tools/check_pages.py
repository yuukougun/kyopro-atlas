#!/usr/bin/env python3
"""ページ（docs/<field>/<id>.md）の front matter と本文を検査する。規則は planning/interfaces.md §2〜§4・§9・§10、
設計書 §3・§6.5・§6.6・§8.6、design-review D1・D4・D10・D12・T3・T11。

使い方:
  python3 tools/check_pages.py                  全ページを検査し、エラーの全件と、警告の種類ごとの件数・1件目を出す
  python3 tools/check_pages.py -v               警告も全件を出す
  python3 tools/check_pages.py --field ds       その分野のページに関わる指摘だけを出す
  python3 tools/check_pages.py --page lazy-segment-tree --page docs/ds/segment-tree.md
                                                そのページに関わる指摘だけを出す（id かパス。カンマ区切りでもよい）
  python3 tools/check_pages.py --root DIR       DIR/docs と DIR/snippets を検査する（骨格の試験など。台帳は --ledger）
終了コード: エラーがあれば 1、警告だけなら 0。--field・--page のときは、絞ったページのエラーだけで決める

検査するファイル: docs/<field>/<id>.md（field は15分野）。docs/<field>/index.md・docs/lists/・docs/index/ は生成物なので
見ない（鮮度は tools/gen_site.py --check）。docs/index.md など分野の外の Markdown は、本文の検査（問題の一覧の書式と台帳・
囲みの外の問題リンク・```cpp）だけを行う。

エラー（直すまで CI が通らない）
  front matter  ない・YAML が読めない・schema/page.schema.json に合わない・status を使っている
  id            ファイル名と違う・field がフォルダと違う・id の重複・節の anchor の重複
  参照          prerequisites・related の id が docs にも catalog（planning/catalog/*.yaml）にもない、
                id#anchor の anchor が相手の sections にない、前提の循環
                （catalog にだけある id は、試作の間はまだページがないので「未作成のページへの参照」の警告にし、anchor は見ない）
  問題の一覧    囲みの形、1行の書式（interfaces.md §3 の正規表現）、台帳にない・台帳で確認済みでない、
                label・URL・difficulty が台帳と違う（tools/fix_problems.py で直せる）、囲みの外の問題リンク
  本文          要点の囲み（!!! abstract "要点"）が本文の最初にない、```cpp に取り込み（--8<--）以外を書いている、
                取り込むコード片のファイル・範囲（[start:名前]）がない、
                stage が draft 以降なのに sections の anchor が本文の見出し（{#anchor}）にない、
                stage が reviewed 以降なのに別名が冒頭（最初の ## より前）にない
  リンク        本文の相対リンク（[..](../<field>/<id>.md#anchor)・[..](#anchor)・用語集の #anchor。コードの中は見ない）を
                mkdocs build --strict の validation と同じ見方で確かめる：先のファイルがない、相対リンクとして解釈できない
                （生の [&](auto&& self) など）、絶対パス、先に anchor がない（見出しの {#id}・toc が見出しから作る id・
                attr_list の {#id}・HTML の id・脚注）、用語集に anchor がない、stage が stub のページの節へのリンク
警告
  前提のレベルの逆転、節のレベルがページより低い・基礎のページに黄・発展の節、同じ分野の前提が order で後ろ、
  推移的に冗長な前提、前提と related の重複、自分への related、level が発展なのに type が overview でない、
  summary の長さ・文の数・禁止語（D10）、要点の項目の欠け（technique・thinking・overview・cpp）、
  stage が draft なのに別名が冒頭にない、draft 以降なのに complexity が null・要点に「（執筆時に書く）」が残る、
  同じページに同じ問題、2ページ以上で例題（D4）、分野の外のフォルダのページ

このファイルには、gen_site.py・fix_problems.py・make_skeleton.py が使う共通の部品（定数、ページの読み込み、問題の一覧の
読み取り、台帳と問題の表示名、Markdown の文字のエスケープ、schema の検査器）も置く。MkDocs は import しない。
依存は PyYAML だけ。schema の検査は、このファイルの中の小さな検査器で行う（JSON Schema Draft-07 のうち
schema/page.schema.json が使うキーワードだけに対応し、知らないキーワードがあれば止まる。独自の x-message は
その部分が合わないときの文）。
"""
from __future__ import annotations

import argparse
import collections
import datetime
import json
import posixpath
import re
import sys
import unicodedata
import urllib.parse
from dataclasses import dataclass, field
from pathlib import Path

import yaml

ROOT = Path(__file__).resolve().parent.parent
SCHEMA_PATH = ROOT / "schema" / "page.schema.json"
LEDGER_PATH = ROOT / "data" / "problems.yaml"
RECENT_PATH = ROOT / "data" / "recent-abc.yaml"
CATALOG_DIR = ROOT / "planning" / "catalog"
SITE_URL = "https://yuukougun.github.io/kyopro-atlas/"

# ---------------------------------------------------------------- 定数（設計書 §2・§3、catalog/README.md §4、interfaces.md）

FIELDS = ["start", "guide", "basics", "thinking", "dp", "graph", "tree", "ds", "math", "comb",
          "string", "geometry", "misc", "patterns", "cpp"]
FIELD_TITLES = {
    "start": "はじめに", "guide": "横断ページ", "basics": "基本テクニック", "thinking": "考察", "dp": "動的計画法",
    "graph": "グラフ", "tree": "木", "ds": "データ構造", "math": "整数論・代数", "comb": "数え上げ・確率・ゲーム",
    "string": "文字列", "geometry": "幾何", "misc": "その他の技法", "patterns": "題材別", "cpp": "C++",
}
TYPES = ["technique", "thinking", "pattern", "hub", "overview", "cpp", "guide"]
BAND_TYPES = {"technique", "thinking", "overview"}      # level（帯）と frequency を必ず持つ type
LEVELS = ["基礎", "水", "青", "黄", "発展"]
LEVEL_RANK = {lv: i for i, lv in enumerate(LEVELS)}
STAGES = ["stub", "draft", "reviewed", "done"]
STAGE_RANK = {s: i for i, s in enumerate(STAGES)}
FREQ_RANK = {"A": 0, "B": 1, "C": 2}
ROLES = ["example", "practice", "challenge"]
ROLE_JA = {"example": "例題", "practice": "練習", "challenge": "力試し"}
SIGN_JA = {"phrase": "言い回し", "constraint": "制約", "shape": "式の形"}
KINDS = [
    "計算量", "全探索", "二分探索", "累積和・差分", "尺取り・スライド窓", "貪欲", "ソート・座標圧縮", "ダブリング・分割統治",
    "DP", "グラフ探索", "最短路", "連結性・全域木", "フロー・マッチング", "木", "データ構造", "区間クエリ",
    "クエリ処理の工夫", "整数論", "線形代数・行列", "畳み込み・多項式", "数え上げ", "確率・期待値", "ゲーム",
    "文字列", "ハッシュ・乱択", "幾何", "ビット演算", "考察", "実装・C++", "案内",
]
CONFIRMED = "確認済み"
PLACEHOLDER = "（執筆時に書く）"          # 骨格の要点の計算量など（interfaces.md §4）
ABSTRACT_ITEMS = ["何ができるか", "いつ使うか", "計算量", "前提"]

ID_RE = re.compile(r"^[a-z0-9]+(-[a-z0-9]+)*$")
# interfaces.md §3 の1行の形（そのまま）
PROBLEM_LINE_RE = re.compile(
    r"^- \[(?P<label>[^\]]+)\]\((?P<url>https://atcoder\.jp/contests/(?P<contest>[^/]+)/tasks/(?P<id>[A-Za-z0-9_]+))\)"
    r"（diff (?P<diff>\d+|—)）：(?P<summary>.+)$")
BLOCK_OPEN_RE = re.compile(r'^<div class="kp-problems" data-role="(?P<role>[^"]*)" markdown(?:="(?:1|block)")?>$')
BLOCK_CLOSE_RE = re.compile(r"^</div>$")
TASK_LINK_RE = re.compile(r"atcoder\.jp/contests/[^/\s)\"'>]+/tasks/[A-Za-z0-9_]+")
FENCE_RE = re.compile(r"^(?P<indent>[ \t]*)(?P<fence>`{3,}|~{3,})(?P<info>.*)$")
HEADING_RE = re.compile(r"^[ ]{0,3}(?P<hashes>#{1,6})\s+(?P<text>.*?)\s*$")
ATTR_ID_RE = re.compile(r"\{[^{}]*?#(?P<id>[A-Za-z0-9_:.-]+)[^{}]*\}\s*$")
HTML_ID_RE = re.compile(r"""<[A-Za-z][^>]*?\sid=["'](?P<id>[^"']+)["']""")
ABSTRACT_RE = re.compile(r'^!!!\s+abstract(?:\s+[A-Za-z_-]+)*\s+"要点"\s*$')
SNIPPET_LINE_RE = re.compile(r"""^\s*;?-{1,}8<-{1,}\s*(?:(?P<q>["'])(?P<path>[^"']+)(?P=q))?\s*$""")
COMMENT_LINE_RE = re.compile(r"^\s*<!--.*-->\s*$")

CONTEST_NAMES = {"typical90": "典型90", "dp": "EDPC", "tdpc": "TDPC", "math-and-algorithm": "アルゴ数学",
                 "tessoku-book": "鉄則本"}

# summary の規則（catalog/README.md §3.5-1。check_catalog.py と同じ）
SUMMARY_MAX = 120
SUMMARY_NG = ["このページ", "ここ", "まとめる", "扱う", "紹介する"]
BAND_RE = re.compile(r"(水|青|黄)(色|の帯|帯|コーダー|レベル|の節|以上|以下|まで|から|で必須|で頻出)"
                     r"|(基礎|発展)(の帯|帯|レベル|の節)|[（(](基礎|水|青|黄|発展)[）)]")
DESU_RE = re.compile(r"(です|ます)(。|$|、)")


# ---------------------------------------------------------------- 小さな部品

def plain(v):
    """YAML の日付を ISO 形式の文字列にする（JSON にできる形にそろえる）。"""
    if isinstance(v, (datetime.date, datetime.datetime)):
        return v.isoformat()
    if isinstance(v, dict):
        return {str(k): plain(x) for k, x in v.items()}
    if isinstance(v, list):
        return [plain(x) for x in v]
    return v


def norm_text(s) -> str:
    """照合用：全角・半角をそろえ、小文字にし、空白をつめる。"""
    s = unicodedata.normalize("NFKC", str(s)).casefold()
    return re.sub(r"\s+", " ", s).strip()


def count_sentences(s: str) -> int:
    """かっこの外の「。」で文を数える。"""
    depth, n, tail = 0, 0, False
    for ch in s:
        if ch in "（(「『":
            depth += 1
        elif ch in "）)」』":
            depth = max(0, depth - 1)
        if ch == "。" and depth == 0:
            n += 1
            tail = False
        elif not ch.isspace():
            tail = True
    return n + (1 if tail else 0)


def md_text(s, table: bool = False) -> str:
    """Markdown の本文に入れる文字列のエスケープ（catalog の題名・要約・サイン・節の題名を生成物に入れるとき）。

    Python-Markdown で意味を持つ文字だけを最小限に変える：\\ と * と ` と $ は前に \\、語の頭の _ は \\_、
    タグに見える < は &lt;、実体参照に見える & は &amp;、リンクに見える [ … ]( や [ … ][ の [ は \\[、
    行頭の # と箇条書きの印、末尾の }（attr_list）、表の中の |。^…^ や ~…~ の組（空白なし）があるときだけ
    ^・~ を数値文字参照にする（pymdownx.caret・tilde 対策）。
    """
    s = str(s)
    caret = bool(re.search(r"\^[^\s^]+\^", s))
    tilde = bool(re.search(r"~[^\s~]+~", s))
    link_open = set()          # リンクの始まりに見える [ の位置（対応する ] の次が ( か [）
    stack: list[int] = []
    for i, ch in enumerate(s):
        if ch == "[":
            stack.append(i)
        elif ch == "]" and stack:
            j = stack.pop()
            if s[i + 1:i + 2] in ("(", "[") or (j == 0 and s[i + 1:i + 2] == ":"):
                link_open.add(j)
    out: list[str] = []
    prev = ""
    for i, ch in enumerate(s):
        nxt = s[i + 1] if i + 1 < len(s) else ""
        if ch in "\\*`$" or (ch == "[" and i in link_open):
            out.append("\\" + ch)
        elif ch == "_" and not prev.isalnum():
            out.append("\\_")
        elif ch == "<" and (nxt.isalpha() or nxt in "/!?"):
            out.append("&lt;")
        elif ch == "&" and re.match(r"&[A-Za-z0-9#]+;", s[i:]):
            out.append("&amp;")
        elif ch == "|" and table:
            out.append("\\|")
        elif ch == "^" and caret:
            out.append("&#94;")
        elif ch == "~" and tilde:
            out.append("&#126;")
        else:
            out.append(ch)
        prev = ch
    r = "".join(out)
    if re.match(r"#|[-+>](\s|$)", r):
        r = "\\" + r
    elif m := re.match(r"(\d+)([.)])(\s|$)", r):
        r = m.group(1) + "\\" + r[len(m.group(1)):]
    if r.endswith("}"):
        r = r[:-1] + "\\}"
    return r


def rel_link(host_rel: str, target_rel: str) -> str:
    """docs からの相対パスどうしの、host から target への相対リンク。"""
    base = posixpath.dirname(host_rel) or "."
    return posixpath.relpath(target_rel, base)


def contest_name(cid: str) -> str:
    """コンテストの表示名（interfaces.md §3）。"""
    m = re.fullmatch(r"(abc|arc|agc)(\d+)", cid)
    if m:
        return m.group(1).upper() + m.group(2)
    return CONTEST_NAMES.get(cid, cid.upper())


def problem_label(e: dict) -> str:
    # 題名は AtCoder Problems の値を写しているので、末尾の空白（'Pac-Takahashi ' など）があり得る。label では落とす
    return f"{contest_name(str(e.get('contest')))} {e.get('index')}. {str(e.get('title')).strip()}"


def problem_url(e: dict) -> str:
    return f"https://atcoder.jp/contests/{e.get('contest')}/tasks/{e.get('id')}"


def diff_text(e: dict) -> str:
    d = e.get("difficulty")
    return str(d) if isinstance(d, int) and not isinstance(d, bool) else "—"


def problem_line(e: dict, summary: str) -> str:
    """台帳の項目から問題の一覧の1行を作る（interfaces.md §3）。"""
    return f"- [{problem_label(e)}]({problem_url(e)})（diff {diff_text(e)}）：{summary}"


def load_ledger(path: Path = LEDGER_PATH) -> dict[str, dict]:
    doc = yaml.safe_load(path.read_text(encoding="utf-8")) or {}
    return {e["id"]: e for e in doc.get("problems") or [] if isinstance(e, dict) and isinstance(e.get("id"), str)}


def load_recent(path: Path = RECENT_PATH) -> list[dict]:
    doc = yaml.safe_load(path.read_text(encoding="utf-8")) or {}
    return [e for e in doc.get("problems") or [] if isinstance(e, dict) and isinstance(e.get("id"), str)]


def split_front_matter(text: str) -> tuple[str | None, str, int, str | None]:
    """(front matter の YAML, 本文, 本文の1行目の行番号, 閉じていないときのエラー)。"""
    lines = text.split("\n")
    if not lines or lines[0].rstrip() != "---":
        return None, text, 1, None
    for i in range(1, len(lines)):
        if lines[i].rstrip() in ("---", "..."):
            return "\n".join(lines[1:i]), "\n".join(lines[i + 1:]), i + 2, None
    return None, text, 1, "front matter が閉じていない（--- がない）"


def parse_lang(info: str) -> str:
    s = info.strip()
    if s.startswith("{"):
        s = s.strip("{} ")
    tok = s.split()[0] if s.split() else ""
    return tok.lstrip(".").rstrip("}").lower()


def fence_spans(lines: list[str]) -> list[tuple[int, int, str, str]]:
    """フェンスのコードの範囲 (開始行, 終了行, 言語, 字下げ) を返す（0 始まり、終了行を含む。閉じていなければ最後まで）。"""
    spans = []
    i = 0
    while i < len(lines):
        m = FENCE_RE.match(lines[i])
        if not m or (m.group("fence")[0] == "`" and "`" in m.group("info")):
            i += 1
            continue
        ch, n = m.group("fence")[0], len(m.group("fence"))
        j = i + 1
        while j < len(lines):
            c = re.match(r"^[ \t]*(`{3,}|~{3,})\s*$", lines[j])
            if c and c.group(1)[0] == ch and len(c.group(1)) >= n:
                break
            j += 1
        spans.append((i, min(j, len(lines) - 1), parse_lang(m.group("info")), m.group("indent")))
        i = j + 1
    return spans


@dataclass
class ProblemRef:
    id: str
    role: str
    line: int          # ファイルの行番号
    text: str          # 行（字下げを除く）
    label: str
    url: str
    contest: str
    diff: str
    summary: str


@dataclass
class Issue:
    line: int
    msg: str


@dataclass
class Page:
    """docs の Markdown 1つ。meta は front matter（日付は文字列にしたもの）。"""
    path: Path
    rel: str                       # docs からの相対パス（posix）
    text: str
    meta: dict | None = None
    meta_error: str | None = None
    body: str = ""
    body_line: int = 1             # 本文の1行目のファイル上の行番号
    lines: list[str] = field(default_factory=list)
    in_fence: list[bool] = field(default_factory=list)
    spans: list[tuple[int, int, str, str]] = field(default_factory=list)
    problems: list[ProblemRef] = field(default_factory=list)
    problem_issues: list[Issue] = field(default_factory=list)
    outside_links: list[Issue] = field(default_factory=list)

    @property
    def dir_field(self) -> str | None:
        parts = self.rel.split("/")
        return parts[0] if len(parts) == 2 and parts[0] in FIELDS else None

    @property
    def stem(self) -> str:
        return posixpath.splitext(posixpath.basename(self.rel))[0]

    @property
    def is_content(self) -> bool:
        """docs/<field>/<id>.md（分野の入口 index.md は除く）。"""
        return self.dir_field is not None and self.stem != "index"

    def get(self, key, default=None):
        if not isinstance(self.meta, dict):
            return default
        v = self.meta.get(key, default)
        return default if v is None and default is not None else v

    @property
    def id(self) -> str:
        v = self.get("id")
        return v if isinstance(v, str) else self.stem

    @property
    def stage(self) -> str:
        v = self.get("stage")
        return v if v in STAGE_RANK else "stub"

    def url(self) -> str:
        """サイトのルートからの URL（use_directory_urls）。"""
        stem = self.rel[:-3]
        # index.md と <dir>/index.md だけがディレクトリの URL になる（cpp-reverse-index.md は違う）
        is_index = stem == "index" or stem.endswith("/index")
        return (stem[: -len("index")] if is_index else stem + "/")

    def line_no(self, i: int) -> int:
        return self.body_line + i

    def analyze(self) -> None:
        """本文を行に分け、フェンスの範囲・問題の一覧・囲みの外の問題リンクを読む。"""
        self.lines = self.body.split("\n")
        self.spans = fence_spans(self.lines)
        self.in_fence = [False] * len(self.lines)
        for a, b, _, _ in self.spans:
            for k in range(a, b + 1):
                self.in_fence[k] = True
        block: tuple[str, int, str] | None = None          # (role, 開始行, 字下げ)
        for i, raw in enumerate(self.lines):
            if self.in_fence[i]:
                continue
            s = raw.strip()
            no = self.line_no(i)
            if block is None:
                if "kp-problems" in s:
                    m = BLOCK_OPEN_RE.match(s)
                    if not m:
                        self.problem_issues.append(Issue(no, '問題の一覧の囲みの開始の形が違う（<div class="kp-problems" '
                                                             'data-role="practice" markdown> の形）'))
                        continue
                    role = m.group("role")
                    if role not in ROLES:
                        self.problem_issues.append(Issue(no, f"data-role が不正: {role!r}（example・practice・challenge）"))
                    block = (role, no, raw[: len(raw) - len(raw.lstrip())])
                    continue
                for m in TASK_LINK_RE.finditer(raw):
                    self.outside_links.append(Issue(no, f"問題の一覧の囲みの外に問題へのリンクがある: {m.group(0)}"
                                                        "（本文から問題に触れるときはページか小見出しへのリンクにする）"))
                continue
            role, start, indent = block
            if BLOCK_CLOSE_RE.match(s):
                block = None
                continue
            if not s or COMMENT_LINE_RE.match(s):
                continue
            if s.startswith("<div") or "kp-problems" in s:
                self.problem_issues.append(Issue(no, f"問題の一覧の囲み（{start} 行から）が閉じる前に別の囲みがある"))
                continue
            line = raw[len(indent):] if raw.startswith(indent) else raw.lstrip()
            m = PROBLEM_LINE_RE.match(line.rstrip())
            if not m:
                self.problem_issues.append(Issue(no, "問題の一覧の行の書式が違う（- [ABC300 E. 題名](https://atcoder.jp/"
                                                     f"contests/abc300/tasks/abc300_e)（diff 1882）：要約）: {s[:80]}"))
                continue
            self.problems.append(ProblemRef(m.group("id"), role, no, line.rstrip(), m.group("label"), m.group("url"),
                                            m.group("contest"), m.group("diff"), m.group("summary")))
        if block is not None:
            self.problem_issues.append(Issue(block[1], "問題の一覧の囲みが閉じていない（</div> がない）"))

    def heading_anchors(self) -> set[str]:
        """本文の見出しの {#anchor} と、HTML の id="…"（フェンスの外）。"""
        out = set()
        for i, raw in enumerate(self.lines):
            if self.in_fence[i]:
                continue
            h = HEADING_RE.match(raw)
            if h:
                m = ATTR_ID_RE.search(h.group("text"))
                if m:
                    out.add(m.group("id"))
            for m in HTML_ID_RE.finditer(raw):
                out.add(m.group("id"))
        return out

    def opening(self) -> str:
        """冒頭：本文の最初の ## 見出しより前（要点の囲みを含む）。"""
        out = []
        for i, raw in enumerate(self.lines):
            if not self.in_fence[i] and re.match(r"^[ ]{0,3}##\s", raw):
                break
            out.append(raw)
        return "\n".join(out)

    def abstract(self) -> tuple[int | None, list[str]]:
        """要点の囲み：(本文の中の開始行, 中身の行)。最初の空でない行（# の題名は飛ばす）が囲みでなければ (None, [])。"""
        i = 0
        while i < len(self.lines) and (not self.lines[i].strip() or COMMENT_LINE_RE.match(self.lines[i])):
            i += 1
        if i < len(self.lines) and re.match(r"^#\s", self.lines[i]):
            i += 1
            while i < len(self.lines) and not self.lines[i].strip():
                i += 1
        if i >= len(self.lines) or not ABSTRACT_RE.match(self.lines[i].rstrip()):
            return None, []
        start, content = i, []
        i += 1
        while i < len(self.lines) and (not self.lines[i].strip() or self.lines[i].startswith(("    ", "\t"))):
            content.append(self.lines[i])
            i += 1
        return start, content


def read_page(path: Path, docs: Path) -> Page:
    text = path.read_text(encoding="utf-8")
    p = Page(path=path, rel=path.relative_to(docs).as_posix(), text=text)
    fm, body, body_line, err = split_front_matter(text)
    p.body, p.body_line = body, body_line
    if err:
        p.meta_error = err
    elif fm is None:
        p.meta_error = "front matter がない"
    else:
        try:
            meta = yaml.safe_load(fm)
        except yaml.YAMLError as e:
            mark = getattr(e, "problem_mark", None)
            at = f"（{mark.line + 2} 行）" if mark else ""
            p.meta_error = f"front matter の YAML が読めない: {getattr(e, 'problem', None) or e}{at}"
        else:
            if isinstance(meta, dict):
                p.meta = plain(meta)
            else:
                p.meta_error = "front matter がマッピングでない"
    p.analyze()
    return p


def is_generated(rel: str) -> bool:
    """gen_site.py の生成物（docs/<field>/index.md・docs/lists/・docs/index/）。"""
    parts = rel.split("/")
    return (len(parts) == 2 and parts[0] in FIELDS and parts[1] == "index.md") or parts[0] in ("lists", "index") and len(parts) > 1


def load_docs(docs: Path) -> tuple[list[Page], list[Page]]:
    """(ページ docs/<field>/<id>.md の列, そのほかの手書きの Markdown の列)。生成物は入れない。並びはパスの順。"""
    pages, others = [], []
    if not docs.is_dir():
        return pages, others
    for path in sorted(docs.rglob("*.md")):
        rel = path.relative_to(docs).as_posix()
        if is_generated(rel):
            continue
        p = read_page(path, docs)
        (pages if p.is_content else others).append(p)
    return pages, others


# ---------------------------------------------------------------- schema の検査器（JSON Schema Draft-07 の一部）

class SchemaError(Exception):
    pass


class Validator:
    KEYWORDS = {"$schema", "$id", "$comment", "title", "description", "default", "examples", "x-message",
                "type", "enum", "const", "pattern", "minLength", "maxLength", "minimum", "maximum", "multipleOf",
                "required", "properties", "additionalProperties", "items", "minItems", "maxItems", "uniqueItems",
                "allOf", "anyOf", "not", "if", "then", "else", "$ref", "definitions"}
    TYPES = {"string": lambda v: isinstance(v, str), "integer": lambda v: isinstance(v, int) and not isinstance(v, bool),
             "number": lambda v: isinstance(v, (int, float)) and not isinstance(v, bool),
             "boolean": lambda v: isinstance(v, bool), "null": lambda v: v is None,
             "array": lambda v: isinstance(v, list), "object": lambda v: isinstance(v, dict)}

    def __init__(self, schema: dict) -> None:
        self.root = schema
        self._check(schema, "#")

    def _check(self, s, where: str) -> None:
        if isinstance(s, bool):
            return
        if not isinstance(s, dict):
            raise SchemaError(f"{where}: スキーマがオブジェクトでない")
        unknown = set(s) - self.KEYWORDS
        if unknown:
            raise SchemaError(f"{where}: 検査器が知らないキーワード {sorted(unknown)}（tools/check_pages.py の Validator に足す）")
        for k in ("properties", "definitions"):
            for name, sub in (s.get(k) or {}).items():
                self._check(sub, f"{where}/{k}/{name}")
        for k in ("additionalProperties", "items", "not", "if", "then", "else"):
            if k in s:
                self._check(s[k], f"{where}/{k}")
        for k in ("allOf", "anyOf"):
            for i, sub in enumerate(s.get(k) or []):
                self._check(sub, f"{where}/{k}/{i}")

    def resolve(self, ref: str) -> dict:
        if not ref.startswith("#/"):
            raise SchemaError(f"$ref は文書の中だけ: {ref}")
        node = self.root
        for part in ref[2:].split("/"):
            node = node[part]
        return node

    @staticmethod
    def fmt_path(path: tuple) -> str:
        out = ""
        for x in path:
            out += f"[{x}]" if isinstance(x, int) else (f".{x}" if out else str(x))
        return out or "front matter"

    def errors(self, inst, s=None, path: tuple = ()) -> list[tuple[str, str]]:
        s = self.root if s is None else s
        if s is True:
            return []
        if s is False:
            return [(self.fmt_path(path), "この項目は持てない")]
        if "$ref" in s:
            s = {**self.resolve(s["$ref"]), **{k: v for k, v in s.items() if k != "$ref"}}
        errs: list[tuple[str, str]] = []
        p = self.fmt_path(path)

        def add(msg: str) -> None:
            errs.append((p, s.get("x-message") or msg))

        if "type" in s:
            types = s["type"] if isinstance(s["type"], list) else [s["type"]]
            if not any(self.TYPES[t](inst) for t in types):
                add(f"型が違う（{'・'.join(types)} のはず。値 {inst!r}）")
                return errs
        if "enum" in s and not any(inst == e and type(inst) is type(e) for e in s["enum"]):
            add(f"{inst!r} は使えない（{'・'.join('null' if e is None else str(e) for e in s['enum'])} のどれか）")
        if "const" in s and not (inst == s["const"] and type(inst) is type(s["const"])):
            add(f"{inst!r} は使えない（{'null' if s['const'] is None else s['const']!r} のはず）")
        if isinstance(inst, str):
            if "pattern" in s and not re.search(s["pattern"], inst):
                add(f"形が違う: {inst!r}")
            if len(inst) < s.get("minLength", 0):
                add("空にできない")
            if "maxLength" in s and len(inst) > s["maxLength"]:
                add(f"長すぎる（{len(inst)} 字。{s['maxLength']} 字まで）")
        if isinstance(inst, (int, float)) and not isinstance(inst, bool):
            if "minimum" in s and inst < s["minimum"]:
                add(f"{inst} は小さすぎる（{s['minimum']} 以上）")
            if "maximum" in s and inst > s["maximum"]:
                add(f"{inst} は大きすぎる（{s['maximum']} 以下）")
            if "multipleOf" in s and inst % s["multipleOf"]:
                add(f"{inst} は {s['multipleOf']} の倍数でない")
        if isinstance(inst, dict):
            for k in s.get("required", []):
                if k not in inst:
                    errs.append((self.fmt_path(path + (k,)), "ない（必須）"))
            props = s.get("properties", {})
            for k, v in inst.items():
                if k in props:
                    errs += self.errors(v, props[k], path + (k,))
                elif "additionalProperties" in s:
                    ap = s["additionalProperties"]
                    if ap is False:
                        errs.append((self.fmt_path(path + (k,)), "知らない項目（綴りの誤りか）"))
                    elif isinstance(ap, dict):
                        errs += self.errors(v, ap, path + (k,))
        if isinstance(inst, list):
            if len(inst) < s.get("minItems", 0) or ("maxItems" in s and len(inst) > s["maxItems"]):
                rng = f"{s.get('minItems', 0)}〜{s['maxItems']}" if "maxItems" in s else f"{s.get('minItems', 0)} 以上"
                add(f"要素が {len(inst)} 個（{rng} 個）")
            if s.get("uniqueItems"):
                keys = [json.dumps(x, sort_keys=True, ensure_ascii=False) for x in inst]
                dup = [k for k, c in collections.Counter(keys).items() if c > 1]
                if dup:
                    add(f"同じ要素が重なっている: {', '.join(dup)}")
            if "items" in s:
                for i, x in enumerate(inst):
                    errs += self.errors(x, s["items"], path + (i,))
        for sub in s.get("allOf", []):
            errs += self.errors(inst, sub, path)
        if "anyOf" in s and all(self.errors(inst, sub, path) for sub in s["anyOf"]):
            add("どの形にも合わない")
        if "not" in s and not self.errors(inst, s["not"], path):
            add("この形にはできない")
        if "if" in s:
            branch = s.get("then") if not self.errors(inst, s["if"], path) else s.get("else")
            if branch is not None:
                errs += self.errors(inst, branch, path)
        return errs


def load_validator(path: Path = SCHEMA_PATH) -> Validator:
    return Validator(json.loads(path.read_text(encoding="utf-8")))


def load_catalog_ids(catalog: Path = CATALOG_DIR) -> set[str]:
    """catalog（planning/catalog/*.yaml）のページの id。まだ docs にないページへの参照を「未作成」と見分けるのに使う。"""
    ids: set[str] = set()
    for path in sorted(catalog.glob("*.yaml")) if catalog.is_dir() else []:
        try:
            doc = yaml.safe_load(path.read_text(encoding="utf-8")) or {}
        except yaml.YAMLError:
            continue
        for p in doc.get("pages") or [] if isinstance(doc, dict) else []:
            if isinstance(p, dict) and isinstance(p.get("id"), str):
                ids.add(p["id"])
    return ids


# ---------------------------------------------------------------- 検査

class Report:
    """指摘を (重さ, 種類, 関わるページのパスの集合, 文) で持つ。"""

    def __init__(self) -> None:
        self.items: list[tuple[str, str, frozenset, str]] = []

    def add(self, sev: str, kind: str, keys, msg: str) -> None:
        if isinstance(keys, str):
            keys = (keys,)
        self.items.append((sev, kind, frozenset(keys), msg))

    def error(self, kind: str, keys, msg: str) -> None:
        self.add("E", kind, keys, msg)

    def warn(self, kind: str, keys, msg: str) -> None:
        self.add("W", kind, keys, msg)

    def select(self, sev: str, keys: set[str] | None) -> list[tuple[str, str]]:
        return [(k, m) for s, k, ks, m in self.items if s == sev and (keys is None or ks & keys)]


def check_body_common(p: Page, rep: Report, ledger: dict[str, dict], snippets: Path) -> None:
    """どの Markdown にも行う本文の検査：問題の一覧・囲みの外のリンク・```cpp。"""
    where = f"{p.rel}"
    for it in p.problem_issues:
        rep.error("問題の一覧の書式", p.rel, f"{where}:{it.line}: {it.msg}")
    for it in p.outside_links:
        rep.error("囲みの外の問題リンク", p.rel, f"{where}:{it.line}: {it.msg}")
    for q in p.problems:
        e = ledger.get(q.id)
        if e is None:
            rep.error("台帳にない問題", p.rel, f"{where}:{q.line}: {q.id} が台帳（data/problems.yaml）にない")
            continue
        if e.get("status") != CONFIRMED:
            rep.error("台帳で確認済みでない問題", p.rel, f"{where}:{q.line}: {q.id} の status が {e.get('status')!r}（確認済みだけを書ける）")
        bad = []
        if q.label != problem_label(e):
            bad.append(f"label（台帳から作ると {problem_label(e)}）")
        if q.url != problem_url(e):
            bad.append(f"URL（{problem_url(e)}）")
        if q.diff != diff_text(e):
            bad.append(f"diff（台帳は {diff_text(e)}）")
        if bad:
            rep.error("台帳と違う（fix_problems.py で直せる）", p.rel, f"{where}:{q.line}: {q.id} の " + "・".join(bad))
    seen = collections.Counter(q.id for q in p.problems)
    for qid, n in seen.items():
        if n > 1:
            rep.warn("同じページに同じ問題", p.rel, f"{where}: {qid} が {n} 回")
    # ```cpp は取り込みだけ（interfaces.md §9、T11）
    for a, b, lang, indent in p.spans:
        if lang not in ("cpp", "c++", "cxx", "cc", "hpp", "h"):
            continue
        in_block = False
        bad_lines = []
        for x in (y for y in p.lines[a + 1:b] if y.strip()):
            m = SNIPPET_LINE_RE.match(x)
            if m:
                in_block = in_block if m.group("path") else not in_block
            elif not (in_block and re.fullmatch(r"\s*;?[^\s\"']+\s*", x)):
                bad_lines.append(x.strip())
        if bad_lines:
            rep.error("```cpp に C++ を直接書いている", p.rel,
                      f"{where}:{p.line_no(a)}: ```{lang} には --8<-- の取り込みだけを書く（擬似コードは ```text）: {bad_lines[0][:60]}")
    # 取り込むコード片（pymdownx.snippets はフェンスの中でも外でも --8<-- を展開する。; で始まる行はエスケープ）
    for i, ref in snippet_refs(p.lines):
        check_snippet_ref(p, rep, snippets, ref, p.line_no(i))


def snippet_refs(lines: list[str]) -> list[tuple[int, str]]:
    """--8<-- "path" の1行の形と、--8<-- の行で挟んだ複数行の形の取り込み (行, パス)。"""
    refs, in_block = [], False
    for i, x in enumerate(lines):
        m = SNIPPET_LINE_RE.match(x)
        escaped = x.lstrip().startswith(";")
        if m:
            if escaped:
                continue
            if m.group("path"):
                refs.append((i, m.group("path")))
            else:
                in_block = not in_block
        elif in_block and x.strip() and not x.strip().startswith(";"):
            refs.append((i, x.strip()))
    return refs


def check_snippet_ref(p: Page, rep: Report, snippets: Path, ref: str, line: int) -> None:
    path, _, section = ref.partition(":")
    f = snippets / path
    if not f.is_file():
        rep.error("取り込むコード片がない", p.rel, f"{p.rel}:{line}: snippets/{path} がない")
        return
    if section and not re.fullmatch(r"[\d,\-: ]+", section):
        text = f.read_text(encoding="utf-8", errors="replace")
        if f"[start:{section}]" not in text or f"[end:{section}]" not in text:
            rep.error("取り込むコード片がない", p.rel, f"{p.rel}:{line}: snippets/{path} に範囲 [start:{section}]〜[end:{section}] がない")


# ---------------------------------------------------------------- 本文のリンクと anchor（mkdocs build --strict の validation に合わせる）

# [文字](行き先) と ![代替](行き先)。文字は1段の [ ] を含んでよい。行き先は1段のかっこを含んでよい（Python-Markdown と同じ）
LINK_RE = re.compile(r"(?<!\\)!?\[(?:[^\[\]\\\n]|\\.|\[(?:[^\[\]\\\n]|\\.)*\])*\]\((?P<dest>(?:[^()\n]|\([^()\n]*\))*)\)")
REFDEF_RE = re.compile(r"^[ ]{0,3}\[(?!\^)[^\]]+\]:\s*(?P<dest>\S+)")
CODE_SPAN_RE = re.compile(r"(`+)(?:(?!\1).)+?\1")
MATH_RE = re.compile(r"\$\$.+?\$\$|(?<![\\$])\$(?!\s)(?:\\.|[^$\\\n])+?(?<!\s)\$")
ATTR_ANY_RE = re.compile(r"\{:?[^{}\n]*?#(?P<id>[A-Za-z0-9_:.-]+)[^{}\n]*\}")
ANY_HEADING_RE = re.compile(r"^\s*(?P<hashes>#{1,6})\s+(?P<text>.*?)\s*#*\s*$")
HTML_NAME_RE = re.compile(r"""<a\s[^>]*?\bname=["'](?P<id>[^"']+)["']""")
FOOTNOTE_DEF_RE = re.compile(r"^\[\^(?P<id>[^\]]+)\]:")
FOOTNOTE_REF_RE = re.compile(r"\[\^(?P<id>[^\]]+)\](?!:)")
GLOSSARY_REL = "guide/glossary.md"


def prose_lines(p: Page) -> list[tuple[int, str]]:
    """フェンス・HTML のコメント・$$ の数式ブロックの外の行 (本文の行の番号, 行)。行の中のコード（`…`）と数式（$…$）は空白にする。"""
    out, in_comment, in_math = [], False, False
    for i, raw in enumerate(p.lines):
        if p.in_fence[i]:
            continue
        s = raw
        if in_comment:
            if "-->" not in s:
                continue
            s, in_comment = s.split("-->", 1)[1], False
        s = re.sub(r"<!--.*?-->", "", s)
        if "<!--" in s:
            s, in_comment = s.split("<!--", 1)[0], True
        if s.strip() == "$$":
            in_math = not in_math
            continue
        if in_math:
            continue
        s = CODE_SPAN_RE.sub(lambda m: " " * len(m.group(0)), s)
        s = MATH_RE.sub(lambda m: " " * len(m.group(0)), s)
        out.append((i, s))
    return out


def link_dest(dest: str) -> str:
    """リンクの (…) の中から行き先を取り出す（Python-Markdown と同じく、"題" が続かなければ空白も行き先に含める）。"""
    d = dest.strip()
    if d.startswith("<") and ">" in d:
        return d[1:d.index(">")]
    m = re.match(r"""^(\S+)\s+(?:"[^"]*"|'[^']*'|\([^()]*\))$""", d)
    return m.group(1) if m else d


def page_links(p: Page) -> list[tuple[int, str]]:
    """本文のリンク (ファイルの行番号, 行き先)。コードの中のものは入れない。"""
    out = []
    for i, s in prose_lines(p):
        for m in LINK_RE.finditer(s):
            out.append((p.line_no(i), link_dest(m.group("dest"))))
        if m := REFDEF_RE.match(s):
            out.append((p.line_no(i), m.group("dest").strip("<>")))
    return out


def heading_attr(text: str) -> tuple[str | None, str]:
    """見出しの末尾の attr_list：(id, attr_list を除いた文字)。attr_list の HEADER_RE と同じく、コードの外で最初の
    ' {' から末尾の '}' までを attr_list とみなすので、途中に { } があれば（例 [&] { ... }(); … {#x}）attr_list にならない。"""
    t = CODE_SPAN_RE.sub(lambda m: " " * len(m.group(0)), text)
    m = re.search(r"[ ]+\{:?[ ]*([^}\n ][^\n]*)[ ]*\}[ ]*$", t)
    if not m or "{" in m.group(1) or "}" in m.group(1):
        return None, text
    a = re.search(r"(?:^|\s)#([^\s}]+)", m.group(1))
    return (a.group(1) if a else None), text[:m.start()]


def heading_slug(text: str) -> str:
    """見出しの文字から toc が作る id（mkdocs.yml の pymdownx.slugs.slugify(case=lower) の近似）。"""
    import html
    t = re.sub(r"!?\[([^\]]*)\]\([^)]*\)", r"\1", text)                 # リンクは文字だけ
    t = re.sub(r"(`+)(.+?)\1", r"\2", t)
    t = re.sub(r"\*\*|__|(?<!\w)[*_]|[*_](?!\w)", "", t)
    t = re.sub(r"</?[^>]*>", "", html.unescape(t))
    t = unicodedata.normalize("NFC", t).strip().lower()
    return re.sub(r"[^\w\- ]", "", t).replace(" ", "-")


def page_anchor_ids(p: Page) -> set[str]:
    """ページを描画したときにある id（見出しの {#id} と toc が作る id、attr_list の {#id}、HTML の id・name、脚注）。"""
    cached = getattr(p, "_anchor_ids", None)
    if cached is not None:
        return cached
    ids: set[str] = set()
    heads: list[str] = []
    for i, s in prose_lines(p):
        raw = p.lines[i]
        h = ANY_HEADING_RE.match(raw)
        if h:
            hid, htext = heading_attr(h.group("text"))
            if hid:
                ids.add(hid)
            else:
                heads.append(htext)
        else:
            for m in ATTR_ANY_RE.finditer(s):
                ids.add(m.group("id"))
        for m in HTML_ID_RE.finditer(raw):
            ids.add(m.group("id"))
        for m in HTML_NAME_RE.finditer(raw):
            ids.add(m.group("id"))
        if m := FOOTNOTE_DEF_RE.match(raw):
            ids.add("fn:" + m.group("id"))
        for m in FOOTNOTE_REF_RE.finditer(s):
            ids.add("fnref:" + m.group("id"))
    for text in heads:              # toc の unique()：重なれば _1, _2 …
        a = heading_slug(text)
        while a in ids or not a:
            m = re.match(r"^(.*)_([0-9]+)$", a)
            a = f"{m.group(1)}_{int(m.group(2)) + 1}" if m else f"{a}_1"
        ids.add(a)
    p._anchor_ids = ids
    return ids


def check_links(all_pages: list[Page], rep: Report, docs: Path) -> None:
    """本文の相対リンクを mkdocs の validation（unrecognized_links・not_found・anchors）と同じ見方で確かめる。"""
    by_rel = {p.rel: p for p in all_pages}
    extra_roots = [docs.parent / "overrides"]

    def target_page(rel: str) -> Page | None:
        if rel not in by_rel:
            f = docs / rel
            by_rel[rel] = read_page(f, docs) if f.is_file() else None
        return by_rel[rel]

    for p in all_pages:
        for no, url in page_links(p):
            where = f"{p.rel}:{no}"
            parts = urllib.parse.urlsplit(url)
            if parts.scheme or parts.netloc:
                continue
            if url.startswith(("/", "\\")):
                rep.error("絶対パスのリンク", p.rel, f"{where}: 絶対パスのリンク {url!r}（相対パス ../<field>/<id>.md で書く）")
                continue
            path, anchor = urllib.parse.unquote(parts.path), parts.fragment
            if not path:
                q, trel = p, p.rel
            else:
                trel = posixpath.normpath(posixpath.join(posixpath.dirname(p.rel), path))
                exists = not trel.startswith("../") and ((docs / trel).is_file() or any((r / trel).is_file() for r in extra_roots))
                if not exists:
                    if not posixpath.splitext(path)[1]:
                        rep.error("解釈できない相対リンク", p.rel,
                                  f"{where}: {url!r} は相対リンクとして解釈できない（MkDocs の unrecognized relative link）。"
                                  "リンクのつもりでなければ [ を \\[ にするかコード（`…`）に入れる")
                    else:
                        rep.error("リンク先のファイルがない", p.rel, f"{where}: {url!r} の先 docs/{trel} がない")
                    continue
                if not trel.endswith(".md"):
                    continue
                q = target_page(trel)
            if not anchor or anchor.startswith("__") or q is None:
                continue
            if q is not p and q.is_content and q.meta is not None and q.stage == "stub" and trel != GLOSSARY_REL:
                # 用語集はメインが書く語の辞書で、stage にかかわらず anchor を持つので、下で anchor だけを見る
                rep.error("準備中のページの節へのリンク", (p.rel, q.rel),
                          f"{where}: {url} の先 {q.rel} は stage が stub（節へのリンクは draft 以降のページにだけ付ける。"
                          "ページへのリンクにする）")
                continue
            if anchor in page_anchor_ids(q):
                continue
            if trel == GLOSSARY_REL:
                rep.error("用語集に anchor がない", (p.rel, q.rel),
                          f"{where}: {url}: 用語集に {{#{anchor}}} がない（新しい語なら、語・anchor・定義を報告で提案する）")
            else:
                rep.error("リンク先に anchor がない", (p.rel, q.rel),
                          f"{where}: {url}: {q.rel} に {{#{anchor}}} の見出し・要素がない")


def check_all(pages: list[Page], others: list[Page], rep: Report, ledger: dict[str, dict], validator: Validator,
              snippets: Path, catalog_ids: set[str] | None = None, docs: Path | None = None) -> None:
    catalog_ids = catalog_ids or set()
    if docs is None and (pages or others):
        q = (pages or others)[0]
        docs = Path(str(q.path)[: -len(q.rel)])
    if docs is not None:
        check_links(pages + others, rep, docs)
    # ---- ページごと
    by_id: dict[str, Page] = {}
    for p in pages:
        w = p.rel
        check_body_common(p, rep, ledger, snippets)
        if p.meta is None:
            rep.error("front matter", w, f"{w}: {p.meta_error}")
            continue
        m = p.meta
        if "status" in m:
            rep.error("front matter", w, f"{w}: status は使わない（Material の予約キー。制作の段階は stage に書く）")
        for path, msg in validator.errors({k: v for k, v in m.items() if k != "status"}):
            rep.error("front matter の形（schema）", w, f"{w}: {path}: {msg}")
        pid = m.get("id")
        if isinstance(pid, str):
            if pid != p.stem:
                rep.error("id とファイル名", w, f"{w}: id が {pid}（ファイル名 {p.stem}.md と同じにする）")
            if pid in by_id:
                rep.error("id の重複", (w, by_id[pid].rel), f"id の重複: {pid}（{by_id[pid].rel} と {w}）")
            else:
                by_id[pid] = p
        if m.get("field") != p.dir_field:
            rep.error("id とファイル名", w, f"{w}: field が {m.get('field')!r}（フォルダ {p.dir_field} と同じにする）")
        lv, t, stage = m.get("level"), m.get("type"), p.stage
        if lv == "発展" and t != "overview":
            rep.warn("level の付け方", w, f"{w}: level が発展なのに type が {t}（発展は overview）")
        # 節（D1）
        anchors: list[str] = []
        for i, sec in enumerate(m.get("sections") or []):
            if not isinstance(sec, dict):
                continue
            an, slv = sec.get("anchor"), sec.get("level")
            if isinstance(an, str):
                if an in anchors:
                    rep.error("節の anchor の重複", w, f"{w}: sections の anchor {an} が重なっている")
                anchors.append(an)
            if slv in LEVEL_RANK and lv in LEVEL_RANK:
                if LEVEL_RANK[slv] < LEVEL_RANK[lv]:
                    rep.warn("節のレベルがページより低い", w, f"{w}（{lv}）: 節 {sec.get('title')}（{slv}）")
                if lv == "基礎" and LEVEL_RANK[slv] > LEVEL_RANK["青"]:
                    rep.warn("基礎のページに黄・発展の節", w, f"{w}: 節 {sec.get('title')}（{slv}）")
        # summary（D10）
        s = m.get("summary")
        if isinstance(s, str) and s.strip():
            n = count_sentences(s)
            if n > 2 or len(s) > SUMMARY_MAX:
                rep.warn("summary の長さ・文の数", w, f"{w}: {n} 文・{len(s)} 字（2 文・{SUMMARY_MAX} 字まで）")
            bad = [x for x in SUMMARY_NG if x in s] + [mm.group(0) for mm in BAND_RE.finditer(s)]
            bad += ["です・ます"] if DESU_RE.search(s) else []
            if bad:
                rep.warn("summary の禁止語", w, f"{w}: 「{'」「'.join(dict.fromkeys(bad))}」")
        # 要点の囲み（interfaces.md §4）
        start, box = p.abstract()
        if start is None:
            rep.error("要点の囲みがない", w, f'{w}: 本文の最初に !!! abstract "要点" の囲みがない')
        else:
            boxtext = "\n".join(box)
            if t in ("technique", "thinking", "overview", "cpp"):
                miss = [x for x in ABSTRACT_ITEMS if f"**{x}**" not in boxtext]
                if miss:
                    rep.warn("要点の項目の欠け", w, f"{w}: 要点に {'・'.join(miss)} がない")
            if STAGE_RANK.get(stage, 0) >= 1 and PLACEHOLDER in boxtext:
                rep.warn("draft 以降で要点に（執筆時に書く）", w, f"{w}: stage が {stage} なのに要点に「{PLACEHOLDER}」が残っている")
        # draft 以降の本文
        if STAGE_RANK.get(stage, 0) >= 1:
            have = p.heading_anchors()
            miss = [a for a in anchors if a not in have]
            if miss:
                rep.error("sections の anchor が本文にない", w,
                          f"{w}: stage が {stage} なのに本文の見出しに " + "・".join("{#" + a + "}" for a in miss) + " がない")
            if t in ("technique", "overview") and m.get("complexity") in (None, ""):
                rep.warn("draft 以降で complexity が null", w, f"{w}: stage が {stage} なのに complexity が null")
            opening = norm_text(p.opening())
            amiss = [a for a in m.get("aliases") or [] if isinstance(a, str) and norm_text(a) not in opening]
            if amiss:
                msg = f"{w}: 別名が冒頭（最初の ## より前）にない: {'、'.join(amiss)}"
                if STAGE_RANK[stage] >= 2:
                    rep.error("別名が冒頭にない", w, msg)
                else:
                    rep.warn("別名が冒頭にない（draft）", w, msg)
    for p in others:
        check_body_common(p, rep, ledger, snippets)
        if not p.rel.startswith("img/") and "/" in p.rel:
            rep.warn("分野の外のフォルダのページ", p.rel, f"{p.rel}: 分野のフォルダ（docs/<field>/）の外にある")

    # ---- 参照（D12）
    graph: dict[str, list[str]] = collections.defaultdict(list)
    ok = {pid: p for pid, p in by_id.items()}

    def sec_anchors(q: Page) -> set[str]:
        return {s.get("anchor") for s in q.get("sections") or [] if isinstance(s, dict)}

    for pid, p in ok.items():
        w, lv = p.rel, p.get("level")
        pre = [r for r in p.get("prerequisites") or [] if isinstance(r, str)]
        rel = [r for r in p.get("related") or [] if isinstance(r, str)]
        for key, refs in (("prerequisites", pre), ("related", rel)):
            for ref in refs:
                base, _, anchor = ref.partition("#")
                q = ok.get(base)
                if q is None:
                    if base in catalog_ids:   # 試作の間など、catalog にあってまだ docs にないページ（anchor は確かめない）
                        rep.warn("未作成のページへの参照", w, f"{w}: {key} の {ref} はまだない（catalog にはある）")
                    else:
                        rep.error("解決できない参照", w, f"{w}: {key} の {ref} を解決できない（docs にも catalog にもない）")
                    continue
                if anchor and anchor not in sec_anchors(q):
                    rep.error("解決できない参照", (w, q.rel), f"{w}: {key} の {ref}: {q.rel} の sections にその anchor がない")
                if key == "related" and base == pid:
                    rep.warn("自分への related", w, f"{w}: related に自分（{ref}）がある")
                if key != "prerequisites":
                    continue
                if base == pid:
                    rep.error("前提の循環", w, f"{w}: 自分自身を前提にしている")
                    continue
                graph[pid].append(base)
                qlv = q.get("level")
                if qlv in LEVEL_RANK and lv in LEVEL_RANK and LEVEL_RANK[qlv] > LEVEL_RANK[lv]:
                    rep.warn("前提のレベルが高い", w, f"{w}（{lv}）: 前提 {base} のレベルが高い（{qlv}）")
                if q.get("field") == p.get("field") and isinstance(q.get("order"), int) and isinstance(p.get("order"), int) \
                        and q.get("order") > p.get("order"):
                    rep.warn("同じ分野の前提が後ろ", w, f"{w}（order {p.get('order')}）: 前提 {base} の order が後ろ（{q.get('order')}）")
        both = {r.partition("#")[0] for r in rel} & set(pre)
        for r in sorted(both):
            rep.warn("前提と related の重複", w, f"{w}: {r} が前提と related の両方にある")

    # 循環
    state: dict[str, int] = {}
    cycles: list[list[str]] = []

    def dfs(u: str, stack: list[str]) -> None:
        state[u] = 1
        stack.append(u)
        for v in graph.get(u, []):
            if state.get(v) == 1:
                cycles.append(stack[stack.index(v):] + [v])
            elif state.get(v) is None:
                dfs(v, stack)
        stack.pop()
        state[u] = 2

    sys.setrecursionlimit(10000)
    for u in sorted(ok):
        if state.get(u) is None:
            dfs(u, [])
    for c in cycles:
        rep.error("前提の循環", {ok[x].rel for x in c}, "前提の循環: " + " → ".join(c))

    # 推移的に冗長な前提
    closure: dict[str, set[str]] = {}

    def reach(u: str) -> set[str]:
        if u not in closure:
            seen, todo = set(), list(graph.get(u, []))
            while todo:
                v = todo.pop()
                if v not in seen:
                    seen.add(v)
                    todo += graph.get(v, [])
            closure[u] = seen
        return closure[u]

    for pid in sorted(ok):
        pre = graph.get(pid, [])
        for q in pre:
            via = [r for r in pre if r != q and q in reach(r)]
            if via:
                rep.warn("推移的に冗長な前提", ok[pid].rel, f"{ok[pid].rel}: 前提 {q} は {via[0]} を経由して届く")

    # 例題は1問1ページ（D4）
    ex: dict[str, list[Page]] = collections.defaultdict(list)
    for p in pages + others:
        for q in p.problems:
            if q.role == "example" and p not in ex[q.id]:
                ex[q.id].append(p)
    for qid, ps in sorted(ex.items()):
        if len(ps) > 1:
            rep.warn("2ページ以上で例題", {x.rel for x in ps}, f"{qid}: " + "・".join(x.rel for x in ps))


def print_report(rep: Report, keys: set[str] | None, verbose: bool) -> int:
    errors, warnings = rep.select("E", keys), rep.select("W", keys)
    groups: dict[str, list[str]] = collections.defaultdict(list)
    for k, m in errors:
        groups[k].append(m)
    print(f"\nエラー {len(errors)} 件")
    for k, ms in sorted(groups.items(), key=lambda kv: -len(kv[1])):
        print(f"  [{k}] {len(ms)} 件")
        for m in ms:
            print("    " + m)
    groups = collections.defaultdict(list)
    for k, m in warnings:
        groups[k].append(m)
    print(f"\n警告 {len(warnings)} 件" + ("" if verbose or not warnings else "（種類ごとの件数と1件目。全件は -v）"))
    for k, ms in sorted(groups.items(), key=lambda kv: -len(kv[1])):
        if verbose:
            print(f"  [{k}] {len(ms)} 件")
            for m in ms:
                print("    " + m)
        else:
            ex = ms[0] if len(ms[0]) <= 110 else ms[0][:109] + "…"
            print(f"  {len(ms):5d}  {k}　例: {ex}")
    return 1 if errors else 0


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--field", choices=FIELDS, help="その分野のページに関わる指摘だけを出す")
    parser.add_argument("--page", action="append", default=[], help="そのページに関わる指摘だけを出す（id かパス。くり返し・カンマ区切り可）")
    parser.add_argument("--root", type=Path, default=ROOT, help="docs/ と snippets/ のある場所（既定はリポジトリ）")
    parser.add_argument("--ledger", type=Path, default=LEDGER_PATH, help="問題の台帳（既定は data/problems.yaml）")
    parser.add_argument("-v", "--verbose", action="store_true", help="警告も全件を出す")
    args = parser.parse_args()

    docs = args.root / "docs"
    if not docs.is_dir():
        sys.exit(f"{docs} がない")
    validator = load_validator()
    ledger = load_ledger(args.ledger)
    pages, others = load_docs(docs)
    rep = Report()
    check_all(pages, others, rep, ledger, validator, args.root / "snippets", load_catalog_ids(), docs)

    keys: set[str] | None = None
    if args.field or args.page:
        keys = set()
        if args.field:
            keys |= {p.rel for p in pages if p.dir_field == args.field}
        wanted = [x.strip() for v in args.page for x in v.split(",") if x.strip()]
        for x in wanted:
            hit = [p.rel for p in pages + others
                   if x in (p.id, p.rel, f"docs/{p.rel}") or Path(x).resolve() == p.path.resolve()]
            if not hit:
                sys.exit(f"--page {x}: そのページがない")
            keys |= set(hit)

    sel = [p for p in pages if keys is None or p.rel in keys]
    by_field = collections.Counter(p.dir_field for p in sel)
    by_stage = collections.Counter(p.stage if p.meta else "（読めない）" for p in sel)
    print(f"ページ {len(sel)}（全 {len(pages)}）  分野別: " + "・".join(f"{f} {by_field[f]}" for f in FIELDS if by_field[f]))
    print("段階別: " + "・".join(f"{s} {by_stage[s]}" for s in STAGES + ["（読めない）"] if by_stage[s])
          + f"  本文の問題: {sum(len(p.problems) for p in sel)} 行")
    if keys is None and others:
        print(f"分野の外の Markdown: {len(others)}（本文の検査だけ）: " + "・".join(p.rel for p in others[:8]) + ("…" if len(others) > 8 else ""))
    sys.exit(print_report(rep, keys, args.verbose))


if __name__ == "__main__":
    main()
