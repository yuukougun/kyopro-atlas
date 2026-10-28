#!/usr/bin/env python3
"""全ページの front matter と本文の問題の一覧から、サイトの生成物を作る（planning/interfaces.md §5・§8、設計書 §8.3）。

使い方:
  python3 tools/gen_site.py                 生成物を書く（変わったファイルだけ）。古い生成物（docs/lists/・docs/index/）は消す
  python3 tools/gen_site.py --check         作り直して差分がないかだけを見る（書かない）。差分があれば終了コード 1
  python3 tools/gen_site.py --check --diff  差分の中身（unified diff）も出す
  python3 tools/gen_site.py --root DIR      DIR/docs を読み、DIR/nav.yml・DIR/overrides/assets/data/graph.json に書く（試験用）
  python3 tools/gen_site.py --list-blocks   手書きのページに置ける生成部分の名前の一覧
  python3 tools/gen_site.py --force         生成物の目印のない docs/<field>/index.md も上書きする
実行と commit はメインのセッションだけが行う（CLAUDE.md・design-review T9）。

読むもの: docs/<field>/<id>.md（front matter と本文の問題の一覧）、data/problems.yaml（問題の表示名・difficulty）、
data/recent-abc.yaml（最近の ABC）。front matter が足りないページ（id・title・type・field・order）は飛ばして知らせる。
書くもの:
  nav.yml                              分野の順 → 分野の入口 → chapter のないページ → chapter ごと（order の順）。nav_title が
                                       あればそれを使う。先頭にホーム（docs/index.md があれば）、最後に「一覧」（lists/ の全ページ。
                                       テンプレートは nav にある一覧にだけバッジのリンクを張るため）。extra.kp に一覧の slug
                                       （levels・kinds）と分野の表示名（fields）を書く（overrides/main.html が引く。interfaces.md の外）
  docs/<field>/index.md                分野の入口（章ごとの表：題名・レベル・要約・準備中の印）。ページのある分野だけ
  docs/lists/index.md・level-<…>.md・kind-<…>.md   レベル別・種類別の一覧（ページのあるものだけ。名前は LEVEL_SLUGS・KIND_SLUGS）
  docs/llms.txt                        1行1ページ「- [タイトル](URL)（id・レベル・分野・段階）：要約」と、使い方・版・詳細索引への案内
  docs/index/<field>.md                分野ごとの詳細索引（id・URL・別名・サイン・kind・前提・ACL・節）。サイト内検索からは外す
  overrides/assets/data/graph.json     interfaces.md §5（pages は1行1ページ）
  手書きのページの生成部分             <!-- gen:begin 名前 --> 〜 <!-- gen:end 名前 --> の間（名前は --list-blocks）。
                                       フェンスの中の目印は無視する。目印のないページ・まだないページは飛ばして知らせる
版: 入力（全ページの front matter・本文の問題の一覧・使った問題の台帳の値・最近の ABC）の内容の SHA-256 の先頭 12 桁と、
front matter の updated の最大値。生成日時は書かないので、入力が同じなら出力も同じ（--check と両立する。T5）。
リンク: 生成する Markdown のリンクは相対パス（mkdocs build --strict で検査される）。節（#anchor）へのリンクは、相手の
stage が draft 以降（本文に見出しがあることを check_pages.py が保証する）のときだけ付け、stub のページはページへのリンクにする。
本文に atcoder.jp の問題へのリンクは書かない（問題は「ABC451 D. 題名」の表示名で書く。リンクは問題の囲みの中だけ。interfaces.md §3）。
共通の部品は check_pages.py にある。
"""
from __future__ import annotations

import argparse
import collections
import difflib
import hashlib
import json
import re
import sys
import unicodedata
from dataclasses import dataclass, field
from pathlib import Path

import yaml

sys.path.insert(0, str(Path(__file__).resolve().parent))
import check_pages as cp  # noqa: E402  （共通の部品）

GEN_MARK = "<!-- tools/gen_site.py が生成する。手で直さない -->"
GEN_BEGIN_RE = re.compile(r"^<!--\s*gen:begin\s+(?P<name>[A-Za-z0-9_-]+)\s*-->$")
GEN_END_RE = re.compile(r"^<!--\s*gen:end(?:\s+(?P<name>[A-Za-z0-9_-]+))?\s*-->$")

FIELD_DESCRIPTIONS = {   # 設計書 §2.1 の「中身」
    "start": "この教材の使い方、記法と用語の約束、AtCoder の仕組み",
    "guide": "逆引き辞典、用語の索引、使い分け、知識マップ、ロードマップ、早見表、戦い方など",
    "basics": "計算量の見積もり、全探索、二分探索、累積和・いもす法、尺取り法、ソート・座標圧縮、貪欲、半分全列挙、ダブリング、分割統治、周期性、bit 演算",
    "thinking": "言い換え・主客転倒・寄与・余事象・偶奇・不変量・構築などの考察の型",
    "dp": "DP の考え方、列・区間・集合・桁・木の DP、DP の高速化",
    "graph": "探索、最短路、有向グラフ、連結性と全域木、探索木と次数の性質、フロー",
    "tree": "木の性質、直径・LCA・オイラーツアー・マージテク・重心など",
    "ds": "STL の応用、スタック・キュー、Union-Find、BIT・セグメント木、クエリ処理の工夫",
    "math": "mod、素数・約数、GCD と合同式、floor、行列・線形代数、畳み込み",
    "comb": "数え方の考え方、二項係数・包除、確率・期待値（期待値 DP を含む）、ゲーム（ゲーム DP を含む）",
    "string": "ハッシュ、Z・KMP・Manacher、Trie、Suffix Array、Aho-Corasick",
    "geometry": "ベクトルと外積、誤差、凸包、偏角ソート、45 度回転など",
    "misc": "インタラクティブ、乱択、bitset による高速化、構文解析",
    "patterns": "括弧列・mex・順列・XOR・区間・グリッドなど、問題に現れる対象から手法を引く案内",
    "cpp": "解説コードに出る書き方、AtCoder と手元の環境、落とし穴、ACL の読み方",
}
LEVEL_SLUGS = {"基礎": "basic", "水": "cyan", "青": "blue", "黄": "yellow", "発展": "advanced"}
LEVEL_RANGES = {"基礎": "difficulty 〜1199", "水": "difficulty 1200〜1599", "青": "difficulty 1600〜1999",
                "黄": "difficulty 2000〜2399", "発展": "difficulty 2400〜（概要だけ）"}
KIND_SLUGS = {
    "計算量": "complexity", "全探索": "brute-force", "二分探索": "binary-search", "累積和・差分": "prefix-sum",
    "尺取り・スライド窓": "two-pointers", "貪欲": "greedy", "ソート・座標圧縮": "sorting", "ダブリング・分割統治": "doubling",
    "DP": "dp", "グラフ探索": "graph-search", "最短路": "shortest-path", "連結性・全域木": "connectivity",
    "フロー・マッチング": "flow", "木": "tree", "データ構造": "data-structure", "区間クエリ": "range-query",
    "クエリ処理の工夫": "query-processing", "整数論": "number-theory", "線形代数・行列": "linear-algebra", "畳み込み・多項式": "convolution",
    "数え上げ": "counting", "確率・期待値": "probability", "ゲーム": "game", "文字列": "string", "ハッシュ・乱択": "hashing",
    "幾何": "geometry", "ビット演算": "bit", "考察": "observation", "実装・C++": "implementation", "案内": "guide",
}
FREQ_JA = {"A": "必修", "B": "準必修", "C": "余裕があれば"}
STAGE_JA = {"stub": "準備中", "draft": "本文あり・未検証", "reviewed": "検証済み", "done": "完成"}
# 逆引き（言い回し）の分け方：ページの kind の1つ目で決める
PHRASE_GROUPS = [
    ("search", "探索・最適化", {"計算量", "全探索", "二分探索", "貪欲", "ソート・座標圧縮", "ダブリング・分割統治", "DP", "考察"}),
    ("sequence", "区間・列・データ構造", {"累積和・差分", "尺取り・スライド窓", "区間クエリ", "データ構造", "クエリ処理の工夫"}),
    ("graph", "グラフ・木", {"グラフ探索", "最短路", "連結性・全域木", "フロー・マッチング", "木"}),
    ("math", "整数・数え上げ・確率", {"整数論", "線形代数・行列", "畳み込み・多項式", "数え上げ", "確率・期待値", "ビット演算"}),
    ("other", "文字列・幾何・ゲーム・そのほか", {"文字列", "ハッシュ・乱択", "幾何", "ゲーム", "実装・C++", "案内"}),
]
# 制約の帯（catalog の reverse-index-constraints の行）：(上限, 見出し, anchor)
CONSTRAINT_BANDS = [
    (10, "10 以下", "10"), (20, "20 以下", "20"), (40, "40 以下", "40"), (80, "80 以下", "80"), (500, "500 以下", "500"),
    (5000, "5000 以下", "5000"), (5 * 10 ** 5, "2×10^5 前後（5×10^5 以下）", "2e5"), (10 ** 6, "10^6 以下", "1e6"),
    (10 ** 7, "10^7 以下", "1e7"), (10 ** 12, "10^12 以下", "1e12"), (float("inf"), "10^12 より大きい（10^18 など）", "1e18"),
]
# 制約のサインの上限の数の読み方（constraint_bound）。数は 2×10^5・10^9・2^30・5000・数百 の形で、「a〜b」は b を読む
NUM_PAT = r"(?:\d+(?:\.\d+)?\s*×\s*10\^\d+|10\^\d+|2\^\d+|\d+(?:,\d{3})*|数[十百千万])"
NUM_RANGE_RE = re.compile(r"(?P<a>" + NUM_PAT + r")(?:\s*〜\s*(?P<b>" + NUM_PAT + r"))?")
BOUND_OP_RE = re.compile(r"(?P<lhs>[^\s、，,（(]{0,12})\s*(?:≤|<|≦|≈)\s*$")     # 数の直前の不等号と、その左辺
# 数の直後の語：個・回（個数・回数）→ 程度・前後・規模・級 → 以下・未満・以内・まで（「個程度」「程度まで」も読む）
BOUND_SUFFIX_RE = re.compile(r"\s*(?:(?P<count>個|回)\s*)?(?:(?:程度|前後|規模|級)\s*)?(?:(?:以下|未満|以内|まで)\s*)?")
LOWER_BOUND_RE = re.compile(r"以上|超|より大き")                                # 「10^5 個以上」は下限なので読まない
RANGE_END_RE = re.compile(r"\s*(?:$|[、，,。）)]|で|と|の)")                    # 範囲だけの「10^9〜10^18 と広い」の後ろ（「3〜5 秒」は読まない）
SUBJECT_RE = re.compile(r"(?P<subj>[^\s、，,（(]{0,12})\s*$")                   # 後ろの語で読んだ数の主語（値か個数かの判定）
EXPR_BEFORE_RE = re.compile(r"(?:[A-Za-z0-9_^.!]|[+\-−×*/^·]\s*)$")           # 式の一部の数（log2・B12・N^2・M + 1・N^2/64）
EXPR_AFTER_RE = re.compile(r"[×*^!/·A-Za-z]")                                  # 式の一部の数（3^N・9!・26×(N+1)・64bit）
COMPUTED_LHS_RE = re.compile(r"[√^!)）]|^O\(")                                 # 見積もりの式（O(N√N) ≈ 10^8・60^4 ≈ 1.3×10^7）
VALUE_LHS = ("A", "値", "座標", "答", "−", "-")                                 # 値の上限の左辺（A_i ≤ 10^9・座標が 10^9 まで）
PROBLEM_SETS = [   # 問題集（contest id → 見出し）。ほかの abc・arc・agc 以外のコンテストは最後に「そのほか」
    ("typical90", "競プロ典型 90 問"), ("dp", "EDPC（Educational DP Contest）"), ("tdpc", "TDPC（Typical DP Contest）"),
    ("ndpc", "NDPC（Next DP Contest）"), ("practice2", "ACL Practice（AtCoder Library Practice Contest）"),
    ("aalc001", "AAL Contest"), ("tessoku-book", "鉄則本（競技プログラミングの鉄則 演習問題集）"),
    ("math-and-algorithm", "アルゴ数学（アルゴリズムと数学 演習問題集）"), ("fps-24", "FPS 24 題"), ("game-24", "組合せゲーム 24 題"),
]
RECENT_POSITIONS = ["E", "F", "G"]          # 位置ごとの頻出手法は E（水）・F（青）・G（黄）（設計書 §7）
# 見出しの帯。abc451〜abc480 の G は黄 12 問・発展 14 問・青 4 問なので「黄・発展」（s10 decisions）
POSITION_LEVEL = {"D": "基礎", "E": "水", "F": "青", "G": "黄・発展"}

# 手書きのページに置ける生成部分：名前 → (中身, 置く想定のページ。None はどこでもよい)
BLOCKS = {
    "home-links": ("ホームの入口（知識マップ・逆引き辞典・ロードマップ・レベル別の一覧・用語の索引）", "index.md"),
    "version": ("索引の版（入力のハッシュと updated の最大値）", None),
    "fields": ("章の一覧（分野の入口へのリンク・ページ数・準備中があればその数と、最後の章「一覧」）", None),
    "lists": ("レベル別・種類別の一覧へのリンク", None),
    "stage-summary": ("制作状況の表（分野ごとの stage の集計。設計書 §10.3）", None),
    "signs-phrase": ("逆引き辞典：言い回しから（signs の phrase。kind で分ける）", "guide/reverse-index-signs.md"),
    "signs-shape": ("逆引き辞典：立てた式の形から（signs の shape）", "guide/reverse-index-signs.md"),
    "signs-constraint": ("逆引き辞典：制約の帯ごとの候補のページ（signs の constraint を上限の数で分ける）", "guide/reverse-index-constraints.md"),
    "terms-kana": ("用語の索引：かな・漢字・記号で始まる語（題名・別名）", "guide/term-index.md"),
    "terms-latin": ("用語の索引：英数字で始まる語（題名・別名・acl）", "guide/term-index.md"),
    "terms-shared": ("用語の索引：複数のページに当たる語", "guide/term-index.md"),
    "roadmap-order": ("ロードマップ：色ごとのページの列（前提の順。同順は分野の並び → frequency。上位の節を含む。D17）", "guide/roadmap.md"),
    "recent-positions": ("ロードマップ：位置ごとの頻出手法（最近30回の E・F・G。recent-abc.yaml）", "guide/roadmap.md"),
    "recent-abc": ("最近の ABC → ページ（recent-abc.yaml）", "guide/problem-sets.md"),
    "problem-sets": ("問題集の問題 → ページ（本文の問題の一覧から）", "guide/problem-sets.md"),
    "verify-table": ("ページ → Library Checker の問題（verify）", "guide/library-design.md"),
}


# ---------------------------------------------------------------- ページ

@dataclass
class P:
    page: cp.Page
    id: str
    title: str
    field: str
    order: int
    type: str
    nav_title: str | None = None
    chapter: str | None = None
    level: str | None = None
    kind: list[str] = field(default_factory=list)
    frequency: str | None = None
    stage: str = "stub"
    summary: str = ""
    prerequisites: list[str] = field(default_factory=list)
    related: list[str] = field(default_factory=list)
    sections: list[dict] = field(default_factory=list)
    signs: list[dict] = field(default_factory=list)
    aliases: list[str] = field(default_factory=list)
    acl: list[str] = field(default_factory=list)
    verify: list[str] = field(default_factory=list)
    updated: str | None = None

    @property
    def rel(self) -> str:
        return self.page.rel

    @property
    def url(self) -> str:
        return f"{self.field}/{self.id}/"

    @property
    def anchors(self) -> set[str]:
        return {s["anchor"] for s in self.sections}

    @property
    def stub(self) -> bool:
        return self.stage == "stub"


def strs(v) -> list[str]:
    return [x for x in v if isinstance(x, str) and x.strip()] if isinstance(v, list) else []


def to_p(pg: cp.Page) -> tuple[P | None, str | None]:
    m = pg.meta
    if m is None:
        return None, pg.meta_error
    need = []
    if not (isinstance(m.get("id"), str) and cp.ID_RE.match(m["id"]) and m["id"] == pg.stem):
        need.append("id（ファイル名と同じ）")
    if not (isinstance(m.get("title"), str) and m["title"].strip()):
        need.append("title")
    if m.get("type") not in cp.TYPES:
        need.append("type")
    if m.get("field") != pg.dir_field:
        need.append("field（フォルダと同じ）")
    if not (isinstance(m.get("order"), int) and not isinstance(m.get("order"), bool)):
        need.append("order")
    if need:
        return None, "front matter の " + "・".join(need) + " が足りない・違う"
    secs = []
    for s in m.get("sections") or []:
        if isinstance(s, dict) and isinstance(s.get("anchor"), str) and isinstance(s.get("title"), str):
            secs.append({"title": s["title"], "anchor": s["anchor"], "level": s.get("level") if s.get("level") in cp.LEVEL_RANK else None})
    signs = [{"type": s["type"], "text": s["text"]} for s in m.get("signs") or []
             if isinstance(s, dict) and s.get("type") in cp.SIGN_JA and isinstance(s.get("text"), str) and s["text"].strip()]
    return P(
        page=pg, id=m["id"], title=m["title"], field=m["field"], order=m["order"], type=m["type"],
        nav_title=m.get("nav_title") if isinstance(m.get("nav_title"), str) and m["nav_title"].strip() else None,
        chapter=m.get("chapter") if isinstance(m.get("chapter"), str) and m["chapter"].strip() else None,
        level=m.get("level") if m.get("level") in cp.LEVEL_RANK else None,
        kind=[k for k in strs(m.get("kind")) if k in KIND_SLUGS],
        frequency=m.get("frequency") if m.get("frequency") in cp.FREQ_RANK else None,
        stage=pg.stage, summary=m.get("summary") if isinstance(m.get("summary"), str) else "",
        prerequisites=strs(m.get("prerequisites")), related=strs(m.get("related")), sections=secs, signs=signs,
        aliases=strs(m.get("aliases")), acl=strs(m.get("acl")), verify=strs(m.get("verify")),
        updated=m.get("updated") if isinstance(m.get("updated"), str) else None,
    ), None


def yaml_scalar(s: str) -> str:
    """YAML のキー・値として安全なら素のまま、そうでなければ二重引用符で書く。"""
    try:
        if yaml.safe_load(f"{s}: x") == {s: "x"} and s == s.strip() and "#" not in s:
            return s
    except yaml.YAMLError:
        pass
    return json.dumps(s, ensure_ascii=False)


def table(header: list[str], rows: list[list[str]]) -> str:
    out = ["| " + " | ".join(header) + " |", "| " + " | ".join("---" for _ in header) + " |"]
    out += ["| " + " | ".join(r) + " |" for r in rows]
    return "\n".join(out)


def kana_key(s: str) -> str:
    """かなの並べ替えの鍵：カタカナをひらがなにし、長音を除く。"""
    out = []
    for ch in unicodedata.normalize("NFKC", s):
        o = ord(ch)
        if 0x30A1 <= o <= 0x30F6:
            ch = chr(o - 0x60)
        if ch != "ー":
            out.append(ch)
    return "".join(out).casefold()


KANA_ROWS = [("a", "あ行", 0x3041, 0x304A), ("ka", "か行", 0x304B, 0x3054), ("sa", "さ行", 0x3055, 0x305E),
             ("ta", "た行", 0x305F, 0x3069), ("na", "な行", 0x306A, 0x306E), ("ha", "は行", 0x306F, 0x307D),
             ("ma", "ま行", 0x307E, 0x3082), ("ya", "や行", 0x3083, 0x3088), ("ra", "ら行", 0x3089, 0x308D),
             ("wa", "わ行", 0x308E, 0x3093), ("a", "あ行", 0x3094, 0x3094), ("ka", "か行", 0x3095, 0x3096)]


def term_class(s: str) -> str:
    c = unicodedata.normalize("NFKC", s)[:1]
    if c.isascii() and c.isalnum():
        return "latin"
    k = kana_key(c)[:1]
    if k and 0x3041 <= ord(k) <= 0x3096:
        return "kana"
    return "other"


def parse_num(s: str) -> float:
    s = s.replace(",", "").replace(" ", "")
    if s.startswith("数"):
        return {"十": 50, "百": 500, "千": 5000, "万": 50000}[s[1]]
    if "×10^" in s:
        a, b = s.split("×10^")
        return float(a) * 10 ** int(b)
    if s.startswith("10^"):
        return 10 ** int(s[3:])
    if s.startswith("2^"):
        return 2 ** int(s[2:])
    return float(s)


def paren_mask(text: str) -> list[bool]:
    """文字ごとに、かっこ（（…）・(…)）の中か。かっこの文字そのものも中に数える。"""
    depth, out = 0, []
    for ch in text:
        if ch in "（(":
            depth += 1
        out.append(depth > 0)
        if ch in "）)":
            depth = max(0, depth - 1)
    return out


def bound_candidates(text: str) -> list[tuple[tuple[bool, bool, int, int], float]]:
    """制約のサインから上限として読める数：((値の上限か, かっこの中か, 書き方, 位置), 数) の一覧。
    書き方は 0 が ≤ など、1 が後ろの語、2 が範囲だけ。

    上限として読む数は、直前に ≤・<・≦・≈ がある数（左辺が O(N√N)・60^4・√N のような見積もりの式なら読まない）と、
    直後に 程度・前後・規模・級・以下・未満・以内・まで・個・回 が続く数（「個以上」「10^18 を超える」の下限は読まない）と、
    「10^9〜10^18 と広い」のように範囲だけで書いた数の上端（後ろが で・と・の・読点・句点・閉じかっこ・文の終わりのときだけ。
    「3〜5 秒」のように単位が続くものは読まない）。
    式の一部の数（N^2・M + 1・log2・3^N）と、2 未満の数（「1 回あたり」）は読まない。
    値の上限は、左辺・主語が A_i・値・座標・答え で始まるか、_ を含む（ΣK_i は除く）か、主語のない数（「10^9 程度の値」）。
    個・回の付いた数は値の上限にしない（個数・回数・長さ・総和・N・Q・K などの上限と同じ扱い）。
    """
    inside = paren_mask(text)
    out = []
    for m in NUM_RANGE_RE.finditer(text):
        before, after = text[:m.start()], text[m.end():]
        if EXPR_BEFORE_RE.search(before) or EXPR_AFTER_RE.match(after):
            continue
        val = parse_num(m.group("b") or m.group("a"))
        if val < 2:
            continue
        op = BOUND_OP_RE.search(before)
        if op:
            lhs, written, count = op.group("lhs").strip(), 0, False
            if COMPUTED_LHS_RE.search(lhs):
                continue
        else:
            sm = BOUND_SUFFIX_RE.match(after)
            if sm.group(0).strip():
                if LOWER_BOUND_RE.match(after[sm.end():]):
                    continue
                written, count = 1, bool(sm.group("count"))
            elif m.group("b") and RANGE_END_RE.match(after):
                written, count = 2, False
            else:
                continue
            lhs = SUBJECT_RE.search(before).group("subj").strip()
        is_value = not count and (lhs == "" or lhs.startswith(VALUE_LHS) or ("_" in lhs and not lhs.startswith("Σ")))
        out.append(((is_value, inside[m.start()], written, m.start()), val))
    return out


def constraint_bound(text: str) -> float | None:
    """制約のサインの上限の数（帯を決める数）。読めなければ None（「数の上限で分けられないもの」に入る）。

    次の順で 1 つ選ぶ（bound_candidates の鍵の順）：個数・回数・長さ・総和・N・Q・K などの上限を、値の上限（A_i・座標など）より先に。
    同じ種類の中では、かっこの外の数を先に（かっこの中の数は補足や見積もりなので、外に読める数がないときだけ使う）、
    ≤ などで書いた上限を「程度」「まで」などで読んだ数より先に（「文字の種類 26 程度、|S| ≤ 2×10^5」は 2×10^5）、
    範囲だけで書いた数をその後に（「頂点数が数百〜数千、辺数が 10^5 程度まで」は 10^5）、最後に最初に書かれた数を使う。
    """
    cands = bound_candidates(text)
    return min(cands)[1] if cands else None


# ---------------------------------------------------------------- 生成

class Site:
    def __init__(self, docs: Path, pages: list[cp.Page], others: list[cp.Page], ledger: dict[str, dict], recent: list[dict]):
        self.docs = docs
        self.notes: list[str] = []
        self.ledger = ledger
        self.recent = recent
        self.raw_pages = pages
        self.others = others
        ps: list[P] = []
        seen: dict[str, P] = {}
        for pg in pages:
            p, err = to_p(pg)
            if p is None:
                self.notes.append(f"飛ばしたページ: {pg.rel}（{err}）")
                continue
            if p.id in seen:
                self.notes.append(f"飛ばしたページ: {pg.rel}（id {p.id} が {seen[p.id].rel} と重なる）")
                continue
            seen[p.id] = p
            ps.append(p)
        self.pages = sorted(ps, key=lambda p: (cp.FIELDS.index(p.field), p.order, p.id))
        self.by_id = {p.id: p for p in self.pages}
        self.fields = [f for f in cp.FIELDS if any(p.field == f for p in self.pages)]
        self.used_problems = self._used_problems()
        self.version = self._version()
        ups = [p.updated for p in self.pages if p.updated]
        self.updated = max(ups) if ups else None

    # ---- 入力の要約
    def _used_problems(self) -> dict[str, dict]:
        out: dict[str, dict] = {}
        for p in self.pages:
            for q in p.page.problems:
                if q.id in out:
                    continue
                e = self.ledger.get(q.id)
                if e is not None:
                    d = e.get("difficulty")
                    out[q.id] = {"label": cp.problem_label(e), "url": cp.problem_url(e),
                                 "difficulty": d if isinstance(d, int) and not isinstance(d, bool) else None}
                else:
                    out[q.id] = {"label": q.label, "url": q.url, "difficulty": int(q.diff) if q.diff.isdigit() else None}
        return dict(sorted(out.items()))

    def _version(self) -> str:
        data = {
            "pages": [{"meta": p.page.meta, "problems": [[q.id, q.role] for q in p.page.problems]}
                      for p in sorted(self.pages, key=lambda p: p.id)],
            "problems": self.used_problems,
            "recent": cp.plain(self.recent),
        }
        blob = json.dumps(data, ensure_ascii=False, sort_keys=True, separators=(",", ":"))
        return hashlib.sha256(blob.encode("utf-8")).hexdigest()[:12]

    def version_text(self) -> str:
        return f"{self.version}（updated の最大：{self.updated or '—'}）"

    # ---- 部品
    def link(self, host: str, p: P, anchor: str | None = None, text: str | None = None, table_cell: bool = False) -> str:
        href = cp.rel_link(host, p.rel)
        if anchor and not p.stub and anchor in p.anchors:
            href += "#" + anchor
        if text is None:
            text = cp.md_text(p.title, table=table_cell).replace("[", "\\[").replace("]", "\\]")
        return f"[{text}]({href})"

    def ref_link(self, host: str, ref: str, table_cell: bool = False) -> str:
        """id か id#anchor へのリンク（ページがなければ文字のまま）。"""
        base, _, anchor = ref.partition("#")
        p = self.by_id.get(base)
        if p is None:
            return f"`{ref}`"
        if anchor:
            sec = next((s for s in p.sections if s["anchor"] == anchor), None)
            if sec:
                return self.link(host, p, anchor, table_cell=table_cell) + " › " + cp.md_text(sec["title"], table=table_cell)
        return self.link(host, p, table_cell=table_cell)

    @staticmethod
    def mark(p: P) -> str:
        return "（準備中）" if p.stub else ""

    @staticmethod
    def lv(p: P) -> str:
        return p.level or "—"

    def front(self, title: str, search_exclude: bool = False) -> str:
        fm = f"---\ntitle: {yaml_scalar(title)}\ntype: generated\n"
        if search_exclude:
            fm += "search:\n  exclude: true\n"
        return fm + "---\n\n" + GEN_MARK + "\n\n"

    @staticmethod
    def upper(p: P, s: dict) -> bool:
        """ページより上の帯の節か（D1）。ページが level を持たないときは、level の付いた節をすべて上とみなす。"""
        if s["level"] is None:
            return False
        return p.level is None or cp.LEVEL_RANK[s["level"]] > cp.LEVEL_RANK[p.level]

    def section_items(self, level: str) -> list[tuple[P, dict]]:
        """その level の節を持つ、下のレベルのページの (ページ, 節)。"""
        return [(p, s) for p in self.pages for s in p.sections
                if s["level"] == level and p.level in cp.LEVEL_RANK and self.upper(p, s)]

    # ---- nav.yml
    def nav_yml(self) -> str:
        lines = ["# tools/gen_site.py が生成する。手で直さない（mkdocs.yml が INHERIT: nav.yml で読む）。",
                 "# 並びは interfaces.md §8：分野の順 → 分野の入口 → chapter のないページ → chapter ごと（order の順）。最後に一覧。",
                 "nav:"]
        if (self.docs / "index.md").exists():
            lines.append("  - ホーム: index.md")
        for f in self.fields:
            ps = [p for p in self.pages if p.field == f]
            lines.append(f"  - {yaml_scalar(cp.FIELD_TITLES[f])}:")
            lines.append(f"      - {f}/index.md")
            for p in ps:
                if not p.chapter:
                    lines.append(f"      - {yaml_scalar(p.nav_title or p.title)}: {p.rel}")
            for ch in dict.fromkeys(p.chapter for p in ps if p.chapter):
                lines.append(f"      - {yaml_scalar(ch)}:")
                for p in ps:
                    if p.chapter == ch:
                        lines.append(f"          - {yaml_scalar(p.nav_title or p.title)}: {p.rel}")
        lines += ["  - 一覧:", "      - lists/index.md"]
        if self.levels_present():
            lines.append("      - レベル別:")
            lines += [f"          - {lv}: lists/level-{LEVEL_SLUGS[lv]}.md" for lv in self.levels_present()]
        if self.kinds_present():
            lines.append("      - 種類別:")
            lines += [f"          - {yaml_scalar(k)}: lists/kind-{KIND_SLUGS[k]}.md" for k in self.kinds_present()]
        # テンプレート（overrides/main.html）が config.extra.kp で引く：一覧の slug と分野の表示名（interfaces.md の外）
        lines += ["extra:", "  kp:", "    levels:"]
        lines += [f"      {lv}: {slug}" for lv, slug in LEVEL_SLUGS.items()]
        lines.append("    kinds:")
        lines += [f"      {yaml_scalar(k)}: {slug}" for k, slug in KIND_SLUGS.items()]
        lines.append("    fields:")
        lines += [f"      {f}: {yaml_scalar(cp.FIELD_TITLES[f])}" for f in cp.FIELDS]
        return "\n".join(lines) + "\n"

    # ---- 分野の入口
    def entrance(self, f: str) -> str:
        ps = [p for p in self.pages if p.field == f]
        host = f"{f}/index.md"
        n_stub = sum(p.stub for p in ps)
        out = self.front(cp.FIELD_TITLES[f])
        out += f"# {cp.FIELD_TITLES[f]}\n\n{cp.md_text(FIELD_DESCRIPTIONS[f])}。{len(ps)} ページ" + (f"（準備中 {n_stub}）" if n_stub else "") + "。\n"

        def rows(group: list[P]) -> str:
            return table(["ページ", "レベル", "要約"], [[self.link(host, p, table_cell=True) + self.mark(p), self.lv(p),
                                                       cp.md_text(p.summary, table=True)] for p in group])

        top = [p for p in ps if not p.chapter]
        if top:
            out += "\n" + rows(top) + "\n"
        for ch in dict.fromkeys(p.chapter for p in ps if p.chapter):
            out += f"\n## {cp.md_text(ch)}\n\n" + rows([p for p in ps if p.chapter == ch]) + "\n"
        return out

    # ---- 一覧
    def level_list(self, lv: str) -> str:
        host = f"lists/level-{LEVEL_SLUGS[lv]}.md"
        ps = [p for p in self.pages if p.level == lv]
        secs = self.section_items(lv)
        out = self.front(f"レベル別の一覧：{lv}")
        out += f"# レベル別の一覧：{lv}\n\n{LEVEL_RANGES[lv]} の帯で主に必要になるページ（{len(ps)} ページ）。"
        out += f"下のレベルのページの中にある{lv}の節は最後の表にある。\n" if secs else "\n"
        for f in cp.FIELDS:
            group = [p for p in ps if p.field == f]
            if group:
                out += f"\n## {cp.FIELD_TITLES[f]}\n\n" + table(["ページ", "種類", "要約"], [
                    [self.link(host, p, table_cell=True) + self.mark(p), cp.md_text("・".join(p.kind), table=True),
                     cp.md_text(p.summary, table=True)] for p in group]) + "\n"
        if secs:
            out += f"\n## 下のレベルのページの中の{lv}の節\n\n" + table(["節", "ページ（レベル）", "分野"], [
                [cp.md_text(s["title"], table=True), self.link(host, p, s["anchor"], table_cell=True) + f"（{self.lv(p)}）" + self.mark(p),
                 cp.FIELD_TITLES[p.field]] for p, s in secs]) + "\n"
        return out

    def kind_list(self, k: str) -> str:
        host = f"lists/kind-{KIND_SLUGS[k]}.md"
        ps = [p for p in self.pages if k in p.kind]
        out = self.front(f"種類別の一覧：{k}")
        out += f"# 種類別の一覧：{cp.md_text(k)}\n\n手法の種類（kind）に「{cp.md_text(k)}」を持つページ（{len(ps)} ページ）。分野の順に並べる。\n"
        for f in cp.FIELDS:
            group = [p for p in ps if p.field == f]
            if group:
                out += f"\n## {cp.FIELD_TITLES[f]}\n\n" + table(["ページ", "レベル", "要約"], [
                    [self.link(host, p, table_cell=True) + self.mark(p), self.lv(p), cp.md_text(p.summary, table=True)] for p in group]) + "\n"
        return out

    def levels_present(self) -> list[str]:
        return [lv for lv in cp.LEVELS if any(p.level == lv for p in self.pages)]

    def kinds_present(self) -> list[str]:
        return [k for k in cp.KINDS if any(k in p.kind for p in self.pages)]

    def lists_index(self) -> str:
        out = self.front("一覧")
        out += "# 一覧\n\nレベル別と種類別の一覧。分野ごとの一覧は各分野の入口にある。\n\n" + self.lists_links("lists/index.md", headings=True) + "\n"
        return out

    def lists_links(self, host: str, headings: bool = False) -> str:
        lv = "・".join(f"[{x}]({cp.rel_link(host, f'lists/level-{LEVEL_SLUGS[x]}.md')})（{sum(p.level == x for p in self.pages)}）"
                      for x in self.levels_present()) or "まだない"
        kd = "・".join(f"[{cp.md_text(x)}]({cp.rel_link(host, f'lists/kind-{KIND_SLUGS[x]}.md')})（{sum(x in p.kind for p in self.pages)}）"
                      for x in self.kinds_present()) or "まだない"
        if headings:
            return f"## レベル別\n\n{lv}\n\n## 種類別\n\n{kd}"
        return f"- レベル別：{lv}\n- 種類別：{kd}"

    # ---- Claude 用の索引
    def llms_txt(self) -> str:
        n_stub = sum(p.stub for p in self.pages)
        out = ["# kyopro-atlas", "",
               "> AtCoder で黄色（レート 2000）を目指す学習者向けの、辞書として引く競技プログラミングの教材。"
               "手法・考察・データ構造・数学・C++ のページを分野ごとに置く。", "",
               f"- 版：{self.version_text()}。tools/gen_site.py が生成する",
               f"- ページ数：{len(self.pages)}" + (f"（準備中 {n_stub}）" if n_stub else ""),
               "- 1 行が 1 ページ：「- [タイトル](URL)（id・レベル・分野・段階）：要約」",
               "- レベルは difficulty の帯：基礎 〜1199・水 1200〜1599・青 1600〜1999・黄 2000〜2399・発展 2400〜（概要だけ）。"
               "「—」はレベルを持たないページ",
               "- 段階：stub は準備中（要約と前提しかないので根拠にしない）、draft は本文あり・未検証、reviewed は検証済み、done は完成",
               "- 別名・問題のサイン・手法の種類・前提・節（アンカー付きの URL）は、下の分野ごとの詳細索引にある", "",
               "## 分野ごとの詳細索引", ""]
        for f in self.fields:
            n = sum(p.field == f for p in self.pages)
            out.append(f"- [{cp.FIELD_TITLES[f]}]({cp.SITE_URL}index/{f}/)：{n} ページ。{FIELD_DESCRIPTIONS[f]}")
        for f in self.fields:
            out += ["", f"## {cp.FIELD_TITLES[f]}", ""]
            for p in self.pages:
                if p.field == f:
                    out.append(f"- [{p.title}]({cp.SITE_URL}{p.url})（{p.id}・{self.lv(p)}・{p.field}・{p.stage}）：{p.summary}")
        return "\n".join(out) + "\n"

    def field_index(self, f: str) -> str:
        ps = [p for p in self.pages if p.field == f]
        out = self.front(f"{cp.FIELD_TITLES[f]}の詳細索引", search_exclude=True)
        out += (f"# {cp.FIELD_TITLES[f]}の詳細索引\n\n分野の全ページの id・URL・別名・サイン・種類・前提・節。"
                f"全分野の1行の一覧と索引の版は {cp.SITE_URL}llms.txt にある。"
                + ("stub（準備中）のページは要約と前提しかなく、節の見出しもまだない。" if any(p.stub for p in ps) else "") + "\n")
        for p in ps:
            url = cp.SITE_URL + p.url
            out += f"\n## {cp.md_text(p.title)}（{p.id}） {{#{p.id}}}\n\n"
            out += f"- id：`{p.id}`　レベル：{self.lv(p)}　段階：{p.stage}　type：{p.type}\n"
            out += f"- URL：{url}\n"
            if p.aliases:
                out += f"- 別名：{'、'.join(cp.md_text(a) for a in p.aliases)}\n"
            if p.kind:
                out += f"- 種類：{'、'.join(p.kind)}\n"
            if p.prerequisites:
                out += f"- 前提：{'、'.join(f'`{x}`' for x in p.prerequisites)}\n"
            if p.acl:
                out += f"- ACL：{'、'.join(f'`{x}`' for x in p.acl)}\n"
            if p.signs:
                out += "- サイン：\n" + "".join(f"    - {cp.SIGN_JA[s['type']]}：{cp.md_text(s['text'])}\n" for s in p.signs)
            if p.sections:
                out += "- 節：\n"
                for s in p.sections:
                    lv = f"（{s['level']}）" if s["level"] and s["level"] != p.level else ""
                    out += f"    - `{p.id}#{s['anchor']}` {cp.md_text(s['title'])}{lv}：{url}#{s['anchor']}\n"
        return out

    # ---- graph.json
    def graph_json(self) -> str:
        def dumps(v) -> str:
            return json.dumps(v, ensure_ascii=False, separators=(",", ":"))

        fields = [{"id": f, "title": cp.FIELD_TITLES[f], "order": i + 1} for i, f in enumerate(cp.FIELDS)]
        pages = []
        for p in self.pages:
            rel = list(dict.fromkeys(r.partition("#")[0] for r in p.related if r.partition("#")[0] != p.id))
            pages.append({
                "id": p.id, "title": p.title, "nav_title": p.nav_title, "field": p.field, "chapter": p.chapter, "order": p.order,
                "type": p.type, "level": p.level, "kind": p.kind, "frequency": p.frequency, "stage": p.stage, "url": p.url,
                "summary": p.summary, "prerequisites": p.prerequisites, "related": rel,
                "sections": [{"anchor": s["anchor"], "title": s["title"], "level": s["level"]} for s in p.sections if self.upper(p, s)],
                "problems": [{"id": q.id, "role": q.role} for q in p.page.problems],
            })
        lines = ["{", f'"version":{dumps(self.version)},', f'"updated":{dumps(self.updated)},', f'"levels":{dumps(cp.LEVELS)},',
                 f'"fields":{dumps(fields)},', '"pages":[']
        lines += [dumps(x) + ("," if i < len(pages) - 1 else "") for i, x in enumerate(pages)]
        lines.append("],")
        lines.append('"problems":{')
        items = list(self.used_problems.items())
        lines += [f"{dumps(k)}:{dumps(v)}" + ("," if i < len(items) - 1 else "") for i, (k, v) in enumerate(items)]
        lines += ["}", "}"]
        return "\n".join(lines) + "\n"

    # ---- 手書きのページの生成部分
    def render(self, name: str, host: str) -> str:
        return getattr(self, "b_" + name.replace("-", "_"))(host)

    def b_home_links(self, host: str) -> str:
        def page(pid: str, text: str | None = None) -> str:
            p = self.by_id.get(pid)
            return self.link(host, p, text=text) if p else f"{text or pid}（準備中）"

        lv = "・".join(f"[{x}]({cp.rel_link(host, f'lists/level-{LEVEL_SLUGS[x]}.md')})" for x in self.levels_present()) or "準備中"
        return "\n".join([
            f"- {page('knowledge-map', '知識マップ')}：ページの前提関係をたどる",
            f"- 逆引き辞典：{page('reverse-index-signs', '言い回しから')}・{page('reverse-index-constraints', '制約と計算量から')}",
            f"- {page('roadmap', '色別ロードマップ')}：色ごとに読むページの順と、最近の ABC の位置ごとの頻出手法",
            f"- レベル別の一覧：{lv}（[すべての一覧]({cp.rel_link(host, 'lists/index.md')})）",
            f"- {page('term-index', '用語の索引')}：手法の名前・別名・英語名から引く",
        ])

    def b_version(self, host: str) -> str:
        return f"索引の版：`{self.version}`（ページの updated の最大：{self.updated or '—'}）"

    def b_fields(self, host: str) -> str:
        """ナビゲーションの章の表：分野ごとの行と、最後の章「一覧」の行（nav_yml と同じ並び）。"""
        # 準備中のページが1つもなければ「準備中」の列を出さない（s10 audit-shared）
        any_stub = any(p.stub for p in self.pages)
        rows = []
        for f in self.fields:
            ps = [p for p in self.pages if p.field == f]
            rows.append([f"[{cp.FIELD_TITLES[f]}]({cp.rel_link(host, f'{f}/index.md')})", cp.md_text(FIELD_DESCRIPTIONS[f], table=True),
                         str(len(ps))] + ([str(sum(p.stub for p in ps))] if any_stub else []))
        if not rows:
            return "（まだページがない）"
        # 「一覧」は分野ではなく、全分野のページを並べ直した生成物の章なので、ページの数は「—」
        rows.append([f"[一覧]({cp.rel_link(host, 'lists/index.md')})",
                     f"レベル別の一覧 {len(self.levels_present())} つと種類別の一覧 {len(self.kinds_present())} 個"
                     "（全分野のページを、レベルと手法の種類で並べ直したもの）", "—"] + (["—"] if any_stub else []))
        head = ["章", "中身", "ページ"] + (["準備中"] if any_stub else [])
        return table(head, rows)

    def b_lists(self, host: str) -> str:
        return self.lists_links(host)

    def b_stage_summary(self, host: str) -> str:
        rows, tot = [], collections.Counter()
        for f in self.fields:
            c = collections.Counter(p.stage for p in self.pages if p.field == f)
            tot += c
            rows.append([cp.FIELD_TITLES[f]] + [str(c[s]) for s in cp.STAGES] + [str(sum(c.values()))])
        rows.append(["**計**"] + [f"**{tot[s]}**" for s in cp.STAGES] + [f"**{sum(tot.values())}**"])
        return table(["分野"] + [f"{s}（{STAGE_JA[s]}）" for s in cp.STAGES] + ["計"], rows)

    def sign_rows(self, host: str, kind: str, ps: list[P]) -> list[list[str]]:
        return [[cp.md_text(s["text"], table=True), self.link(host, p, table_cell=True) + self.mark(p), self.lv(p)]
                for p in ps for s in p.signs if s["type"] == kind]

    def b_signs_phrase(self, host: str) -> str:
        out = []
        for key, title, kinds in PHRASE_GROUPS:
            ps = [p for p in self.pages if (p.kind[0] if p.kind else "案内") in kinds]
            rows = self.sign_rows(host, "phrase", ps)
            if rows:
                out.append(f"### {title} {{#signs-phrase-{key}}}\n\n" + table(["言い回し・求めるもの", "ページ", "レベル"], rows))
        return "\n\n".join(out) or "（まだ言い回しのサインがない）"

    def b_signs_shape(self, host: str) -> str:
        rows = self.sign_rows(host, "shape", self.pages)
        return table(["立てた式・遷移の形", "ページ", "レベル"], rows) if rows else "（まだ式の形のサインがない）"

    def b_signs_constraint(self, host: str) -> str:
        bands: dict[str, list[tuple[float, int, list[str]]]] = collections.defaultdict(list)
        other = []
        for i, p in enumerate(self.pages):
            for s in p.signs:
                if s["type"] != "constraint":
                    continue
                row = [cp.md_text(s["text"], table=True), self.link(host, p, table_cell=True) + self.mark(p), self.lv(p)]
                b = constraint_bound(s["text"])
                if b is None:
                    other.append(row)
                    continue
                band = next(x for x in CONSTRAINT_BANDS if b <= x[0])
                bands[band[2]].append((b, i, row))
        out = []
        for _, label, key in CONSTRAINT_BANDS:
            if bands[key]:
                rows = [r for _, _, r in sorted(bands[key], key=lambda t: (t[0], t[1]))]
                out.append(f"### 上限が {label} {{#signs-constraint-{key}}}\n\n" + table(["制約", "ページ", "レベル"], rows))
        if other:
            out.append("### 数の上限で分けられないもの {#signs-constraint-other}\n\n" + table(["制約", "ページ", "レベル"], other))
        return "\n\n".join(out) or "（まだ制約のサインがない）"

    def acl_owners(self) -> dict[str, list[P]]:
        """ACL の名前 → その名前の持ち主のページ。acl はそのページで使う ACL の一覧なので、名前で引くときは持ち主だけを出す：
        題名・別名がその名前と（大文字小文字・空白・_・- を除いて）同じページ → 使うページのうち id が名前に含まれるもの →
        使うページのうちナビゲーションで最初のもの。"""
        def loose(s: str) -> str:
            return re.sub(r"[\s_\-・]", "", unicodedata.normalize("NFKC", s).casefold())

        names: dict[str, list[P]] = collections.defaultdict(list)
        users: dict[str, list[P]] = collections.defaultdict(list)
        for p in self.pages:
            for w in [p.title] + p.aliases:
                if p not in names[loose(w)]:
                    names[loose(w)].append(p)
            for a in p.acl:
                users[a].append(p)
        out = {}
        for a, ps in users.items():
            out[a] = names.get(loose(a)) or [p for p in ps if loose(p.id) in loose(a)] or ps[:1]
        return out

    def terms(self) -> dict[str, dict]:
        out: dict[str, dict] = {}

        def add(w: str, p: P, is_title: bool) -> None:
            key = cp.norm_text(w)
            if not key:
                return
            e = out.setdefault(key, {"display": w.strip(), "pages": [], "title_of": []})
            if p not in e["pages"]:
                e["pages"].append(p)
            if is_title and p not in e["title_of"]:
                e["title_of"].append(p)

        for p in self.pages:
            for w in [p.title] + ([p.nav_title] if p.nav_title else []) + p.aliases:
                add(w, p, w == p.title)
        for a, owners in sorted(self.acl_owners().items()):
            for p in owners:
                add(a, p, False)
        for e in out.values():
            e["pages"].sort(key=lambda p: (cp.FIELDS.index(p.field), p.order))
        return out

    def term_line(self, host: str, e: dict) -> str:
        links = "、".join(self.link(host, p) for p in e["pages"])
        if len(e["pages"]) == 1 and e["title_of"]:
            return f"- {links}"
        return f"- {cp.md_text(e['display'])} → {links}"

    def b_terms_kana(self, host: str) -> str:
        ts = [e for e in self.terms().values() if term_class(e["display"]) != "latin"]
        kana = sorted((e for e in ts if term_class(e["display"]) == "kana"), key=lambda e: (kana_key(e["display"]), e["display"]))
        other = sorted((e for e in ts if term_class(e["display"]) == "other"),
                       key=lambda e: (unicodedata.normalize("NFKC", e["display"]), e["display"]))
        out = []
        rows: dict[str, list[dict]] = collections.defaultdict(list)
        names = {}
        for e in kana:
            o = ord(kana_key(e["display"])[0])
            key, label = next((k, lab) for k, lab, lo, hi in KANA_ROWS if lo <= o <= hi)
            rows[key].append(e)
            names[key] = label
        for key in dict.fromkeys(k for k, *_ in KANA_ROWS):
            if rows[key]:
                out.append(f"### {names[key]} {{#terms-{key}}}\n\n" + "\n".join(self.term_line(host, e) for e in rows[key]))
        if other:
            out.append("### 漢字・記号で始まる語（最初の字の順。読みの順ではない） {#terms-kanji}\n\n"
                       + "\n".join(self.term_line(host, e) for e in other))
        return "\n\n".join(out) or "（まだ語がない）"

    def b_terms_latin(self, host: str) -> str:
        """英数字で始まる語：先頭に跳び先の行、数字と A〜Z ごとの小見出し（{#terms-latin-digits}・{#terms-latin-a} など）。"""
        ts = sorted((e for e in self.terms().values() if term_class(e["display"]) == "latin"),
                    key=lambda e: (cp.norm_text(e["display"]), e["display"]))
        groups: dict[str, list[dict]] = {}       # 並べ替えの鍵の順なので、数字 → a → … → z の順に入る
        for e in ts:
            c = cp.norm_text(e["display"])[:1]
            groups.setdefault("digits" if c.isdigit() else c, []).append(e)
        if not groups:
            return "（まだ語がない）"
        label = {k: "0〜9" if k == "digits" else k.upper() for k in groups}
        out = ["・".join(f"[{label[k]}](#terms-latin-{k})" for k in groups)]
        for k, es in groups.items():
            out.append(f"### {label[k]} {{#terms-latin-{k}}}\n\n" + "\n".join(self.term_line(host, e) for e in es))
        return "\n\n".join(out)

    def b_terms_shared(self, host: str) -> str:
        ts = sorted((e for e in self.terms().values() if len(e["pages"]) > 1), key=lambda e: (cp.norm_text(e["display"]), e["display"]))
        return "\n".join(f"- {cp.md_text(e['display'])} → " + "、".join(self.link(host, p) for p in e["pages"])
                         for e in ts) or "（複数のページに当たる語はない）"

    def roadmap_items(self, lv: str) -> list[tuple[P, dict | None]]:
        """色 lv の列（D17）：前提の順の段（同じ色の前提だけで数える）→ 分野の並び → frequency → order。上位の節は段 0。"""
        nodes = [p for p in self.pages if p.level == lv and p.type in cp.BAND_TYPES]
        ids = {p.id for p in nodes}
        rank: dict[str, int] = {}

        def depth(p: P, stack: set[str]) -> int:
            if p.id in rank:
                return rank[p.id]
            stack.add(p.id)
            d = 0
            for r in p.prerequisites:
                if r in ids and r not in stack:
                    d = max(d, depth(self.by_id[r], stack) + 1)
            stack.discard(p.id)
            rank[p.id] = d
            return d

        items = []
        for p in nodes:
            items.append(((depth(p, set()), cp.FIELDS.index(p.field), cp.FREQ_RANK.get(p.frequency, 3), p.order, 0), p, None))
        for p, s in self.section_items(lv):
            if p.type in cp.BAND_TYPES:
                items.append(((0, cp.FIELDS.index(p.field), cp.FREQ_RANK.get(p.frequency, 3), p.order, 1 + p.sections.index(s)), p, s))
        return [(p, s) for _, p, s in sorted(items, key=lambda t: t[0])]

    def b_roadmap_order(self, host: str) -> str:
        out = []
        for lv in cp.LEVELS:
            items = self.roadmap_items(lv)
            if not items:
                continue
            rows = []
            for i, (p, s) in enumerate(items, 1):
                if s is None:
                    name = self.link(host, p, table_cell=True) + self.mark(p)
                else:
                    name = self.link(host, p, s["anchor"], table_cell=True) + " › " + cp.md_text(s["title"], table=True) + f"（{self.lv(p)}のページの節）" + self.mark(p)
                rows.append([str(i), name, cp.FIELD_TITLES[p.field], FREQ_JA.get(p.frequency or "", "—")])
            title = f"{lv}（{LEVEL_RANGES[lv]}）"
            out.append(f"### {title} {{#reading-order-{LEVEL_SLUGS[lv]}}}\n\n" + table(["#", "ページ", "分野", "頻度"], rows))
        return "\n\n".join(out) or "（まだページがない）"

    def recent_pages(self, e: dict) -> list[str]:
        return list(dict.fromkeys(r for r in e.get("pages") or [] if isinstance(r, str)))

    @staticmethod
    def recent_label(e: dict, short: bool = False) -> str:
        """最近の ABC の問題の表示名。問題の一覧の label と同じ形（ABC451 D. Concat Power of 2）で、short は ABC451 D。
        台帳にない問題もあるので、recent-abc.yaml の id・position・title から作る。リンクは付けない（style-guide §2.5）。"""
        cid, _, idx = e["id"].rpartition("_")
        index = str(e.get("position") or idx.upper())
        title = str(e.get("title") or "").strip()
        if short or not title:
            return f"{cp.contest_name(cid)} {index}"
        return cp.problem_label({"contest": cid, "index": index, "title": title})

    def b_recent_positions(self, host: str) -> str:
        out = []
        missing = set()
        by_id = {e["id"]: e for e in self.recent}
        for pos in RECENT_POSITIONS:
            probs = [e for e in self.recent if e.get("position") == pos]
            if not probs:
                continue
            kinds: dict[str, dict] = {}
            for e in probs:
                seen: set[str] = set()   # 同じページの別の anchor（mst#a と mst#b）を 1 問で 2 回と数えない
                for ref in self.recent_pages(e):
                    p = self.by_id.get(ref.partition("#")[0])
                    if p is None:
                        missing.add(ref)
                        continue
                    k = p.kind[0] if p.kind else "案内"
                    g = kinds.setdefault(k, {"problems": [], "pages": collections.Counter()})
                    if e["id"] not in g["problems"]:
                        g["problems"].append(e["id"])
                    if p.id not in seen:
                        seen.add(p.id)
                        g["pages"][p.id] += 1
            rows = []
            for k, g in sorted(kinds.items(), key=lambda kv: (-len(kv[1]["problems"]), cp.KINDS.index(kv[0]) if kv[0] in cp.KINDS else 99)):
                pages = sorted(g["pages"].items(), key=lambda kv: (-kv[1], cp.FIELDS.index(self.by_id[kv[0]].field), self.by_id[kv[0]].order))
                links = "、".join(self.link(host, self.by_id[pid], table_cell=True) + (f"（{n}）" if n > 1 else "") for pid, n in pages)
                # 幅 390px でも「ABC453 E」を空白で 2 行に割らないよう、改行しない空白でつなぐ（折り返しは「・」の後だけ）。
                # 表は列ごとに最小 5rem あり、4 列だとスマートフォンの画面の右端を越えるので、数字だけの問題数を最後の列に置き、
                # 問題の列が画面の内側に来るようにする（右端で切れても、見えなくなるのは問題数の後ろの余白だけ）
                rows.append([cp.md_text(k, table=True), links,
                             "・".join(self.recent_label(by_id[q], short=True).replace(" ", "&nbsp;") for q in g["problems"]),
                             str(len(g["problems"]))])
            lvl = POSITION_LEVEL.get(pos, "")
            out.append(f"### {pos} 問題（{lvl}の帯） {{#recent-positions-{pos.lower()}}}\n\n"
                       f"abc451〜abc480 の {pos} の {len(probs)} 問で使われた手法を、ページの種類（kind の1つ目）で分けて多い順に並べる。"
                       "かっこの数は、その位置でそのページを使った問題の数（1 のときは書かない）。\n\n"
                       + table(["種類", "ページ", "問題", "問題数"], rows))
        if missing:
            self.notes.append("recent-abc.yaml の参照でページのないもの: " + "、".join(sorted(missing)))
        return "\n\n".join(out) or "（data/recent-abc.yaml に問題がない）"

    def b_recent_abc(self, host: str) -> str:
        rows = []
        for e in sorted(self.recent, key=lambda e: e["id"]):
            refs = self.recent_pages(e)
            links = "、".join(self.ref_link(host, r, table_cell=True) for r in refs) or "—（対応するページがない）"
            d = e.get("difficulty")
            rows.append([cp.md_text(self.recent_label(e), table=True), str(e.get("position") or "—"),
                         str(d) if isinstance(d, int) else "—", links])
        return table(["問題", "位置", "diff", "使う手法のページ"], rows) if rows else "（data/recent-abc.yaml に問題がない）"

    def b_problem_sets(self, host: str) -> str:
        uses: dict[str, list[tuple[P, str]]] = collections.defaultdict(list)
        for p in self.pages:
            for q in p.page.problems:
                if (p, q.role) not in uses[q.id]:
                    uses[q.id].append((p, q.role))
        sets: dict[str, list[str]] = collections.defaultdict(list)
        for qid in uses:
            e = self.ledger.get(qid) or {}
            cid = str(e.get("contest") or qid.rsplit("_", 1)[0])
            if re.fullmatch(r"(abc|arc|agc)\d+", cid):
                continue
            sets[cid].append(qid)
        known = [c for c, _ in PROBLEM_SETS]
        names = dict(PROBLEM_SETS)
        out = []
        for cid in known + sorted(c for c in sets if c not in known):
            if not sets.get(cid):
                continue
            rows = []
            for qid in sorted(sets[cid], key=lambda x: (str((self.ledger.get(x) or {}).get("index", "")).zfill(4), x)):
                info = self.used_problems[qid]
                rows.append([cp.md_text(info["label"], table=True), str(info["difficulty"] or "—"),
                             "、".join(self.link(host, p, table_cell=True) + f"（{cp.ROLE_JA.get(r, r)}）" for p, r in uses[qid])])
            out.append(f"### {cp.md_text(names.get(cid, cp.contest_name(cid)))} {{#problem-sets-{cid}}}\n\n" + table(["問題", "diff", "ページ（役割）"], rows))
        return "\n\n".join(out) or "（本文の問題の一覧に、問題集の問題がまだない）"

    def b_verify_table(self, host: str) -> str:
        rows = [[self.link(host, p, table_cell=True) + self.mark(p), cp.FIELD_TITLES[p.field],
                 "、".join(f"[{v}](https://judge.yosupo.jp/problem/{v})" for v in p.verify)] for p in self.pages if p.verify]
        return table(["ページ", "分野", "Library Checker の問題"], rows) if rows else "（verify を持つページがない）"

    # ---- 手書きのページに書き込む
    def apply_blocks(self, pg: cp.Page) -> tuple[str, list[str], list[str]]:
        lines = pg.text.split("\n")
        infence: set[int] = set()
        for a, b, _, _ in cp.fence_spans(lines):
            infence.update(range(a, b + 1))
        out: list[str] = []
        found, problems = [], []
        i = 0
        while i < len(lines):
            s = lines[i].strip()
            if i in infence:
                out.append(lines[i])
                i += 1
                continue
            m = GEN_BEGIN_RE.match(s)
            if not m:
                if GEN_END_RE.match(s):
                    problems.append(f"{pg.rel}:{i + 1}: 対応する gen:begin のない gen:end")
                out.append(lines[i])
                i += 1
                continue
            name, indent = m.group("name"), lines[i][: len(lines[i]) - len(lines[i].lstrip())]
            j = i + 1
            while j < len(lines) and not GEN_END_RE.match(lines[j].strip()) and not GEN_BEGIN_RE.match(lines[j].strip()):
                j += 1
            if j >= len(lines) or GEN_BEGIN_RE.match(lines[j].strip()):
                problems.append(f"{pg.rel}:{i + 1}: gen:begin {name} が閉じていない（gen:end {name} がない）")
                out.append(lines[i])
                i += 1
                continue
            end = GEN_END_RE.match(lines[j].strip()).group("name")
            if end and end != name:
                problems.append(f"{pg.rel}:{i + 1}: gen:begin {name} と gen:end {end} の名前が違う")
                out.extend(lines[i:j + 1])
            elif name not in BLOCKS:
                problems.append(f"{pg.rel}:{i + 1}: 知らない生成部分の名前 {name}（--list-blocks で一覧）")
                out.extend(lines[i:j + 1])
            else:
                body = self.render(name, pg.rel)
                out.append(lines[i])
                # 生成部分は目次の題名・別名（揺れた表記をわざと含む）を写すので、表記の検査から外す
                out.append(indent + "<!-- textlint-disable -->")
                out.append("")
                out += [(indent + x) if x else "" for x in body.split("\n")]
                out.append("")
                out.append(indent + "<!-- textlint-enable -->")
                out.append(lines[j])
                found.append(name)
            i = j + 1
        return "\n".join(out), found, problems

    # ---- 全部
    def outputs(self, root: Path, force: bool) -> tuple[dict[Path, str], list[Path], dict[str, list[str]], list[str]]:
        docs = self.docs
        outs: dict[Path, str] = {}
        outs[root / "nav.yml"] = self.nav_yml()
        for f in self.fields:
            outs[docs / f / "index.md"] = self.entrance(f)
        outs[docs / "lists" / "index.md"] = self.lists_index()
        for lv in self.levels_present():
            outs[docs / "lists" / f"level-{LEVEL_SLUGS[lv]}.md"] = self.level_list(lv)
        for k in self.kinds_present():
            outs[docs / "lists" / f"kind-{KIND_SLUGS[k]}.md"] = self.kind_list(k)
        outs[docs / "llms.txt"] = self.llms_txt()
        for f in self.fields:
            outs[docs / "index" / f"{f}.md"] = self.field_index(f)
        outs[root / "overrides" / "assets" / "data" / "graph.json"] = self.graph_json()
        # 手書きのページの生成部分
        where: dict[str, list[str]] = collections.defaultdict(list)
        problems: list[str] = []
        for pg in self.raw_pages + self.others:
            text, found, probs = self.apply_blocks(pg)
            problems += probs
            for n in found:
                where[n].append(pg.rel)
            if text != pg.text:
                outs[pg.path] = text
        # 生成物の目印のない入口は上書きしない
        for f in self.fields:
            path = docs / f / "index.md"
            if path.exists() and GEN_MARK not in path.read_text(encoding="utf-8") and not force:
                problems.append(f"{path.relative_to(root)} に生成物の目印がないので上書きしない（手書きなら別の名前に移す。上書きは --force）")
                del outs[path]
        # 消すもの：docs/lists/・docs/index/ の古い生成物と、ページのなくなった分野の入口
        stale = []
        for d in (docs / "lists", docs / "index"):
            if d.is_dir():
                stale += [x for x in sorted(d.glob("*.md")) if x not in outs]
        for f in cp.FIELDS:
            path = docs / f / "index.md"
            if f not in self.fields and path.exists() and GEN_MARK in path.read_text(encoding="utf-8"):
                stale.append(path)
        return outs, stale, where, problems


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--check", action="store_true", help="作り直して差分がないかだけを見る（書かない）")
    parser.add_argument("--diff", action="store_true", help="--check で差分の中身も出す")
    parser.add_argument("--root", type=Path, default=cp.ROOT, help="docs/ と生成物の置き場所（既定はリポジトリ）")
    parser.add_argument("--ledger", type=Path, default=cp.LEDGER_PATH, help="問題の台帳（既定は data/problems.yaml）")
    parser.add_argument("--recent", type=Path, default=cp.RECENT_PATH, help="最近の ABC（既定は data/recent-abc.yaml）")
    parser.add_argument("--force", action="store_true", help="生成物の目印のない docs/<field>/index.md も上書きする")
    parser.add_argument("--list-blocks", action="store_true", help="生成部分の名前の一覧を出す")
    args = parser.parse_args()

    if args.list_blocks:
        print("手書きのページに <!-- gen:begin 名前 --> と <!-- gen:end 名前 --> を置くと、その間を gen_site.py が書く。")
        for name, (desc, host) in BLOCKS.items():
            print(f"  {name:18s} {desc}" + (f"（docs/{host}）" if host else ""))
        return

    root = args.root.resolve()
    docs = root / "docs"
    pages, others = cp.load_docs(docs)
    site = Site(docs, pages, others, cp.load_ledger(args.ledger), cp.load_recent(args.recent))
    outs, stale, where, problems = site.outputs(root, args.force)

    changed = []
    for path, text in outs.items():
        old = path.read_text(encoding="utf-8") if path.exists() else None
        if old != text:
            changed.append((path, old, text))

    def rel(path: Path) -> str:
        try:
            return str(path.relative_to(root))
        except ValueError:
            return str(path)

    print(f"ページ {len(site.pages)}（分野 {len(site.fields)}）  版 {site.version_text()}")
    for n in dict.fromkeys(site.notes):
        print("注意: " + n)
    for pr in problems:
        print("注意: " + pr)
    skipped = []
    for name, (desc, host) in BLOCKS.items():
        if where.get(name) or host is None:
            continue
        exists = (docs / host).exists()
        skipped.append(f"{name}（docs/{host} " + ("に目印がない" if exists else "がまだない") + "）")
    if skipped:
        print(f"飛ばした生成部分 {len(skipped)}: " + "、".join(skipped))

    if args.check:
        for path, old, text in changed:
            print(("作られる: " if old is None else "変わる: ") + rel(path))
            if args.diff and old is not None:
                d = difflib.unified_diff(old.split("\n"), text.split("\n"), rel(path), rel(path) + "（作り直し）", lineterm="", n=1)
                for k, line in enumerate(d):
                    if k >= 60:
                        print("    …")
                        break
                    print("    " + line)
        for path in stale:
            print("消える: " + rel(path))
        if changed or stale:
            print(f"\n生成物が古い：{len(changed) + len(stale)} ファイル。python3 tools/gen_site.py で作り直してコミットする")
            sys.exit(1)
        print("生成物は最新")
        return

    for path, _, text in changed:
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(text, encoding="utf-8")
    for path in stale:
        path.unlink()
    print(f"書いた: {len(changed)} ファイル・消した: {len(stale)} ファイル（生成物 {len(outs)} のうち変わったものだけ）")
    for path, old, _ in changed[:20]:
        print(("  作った " if old is None else "  変えた ") + rel(path))
    if len(changed) > 20:
        print(f"  …ほか {len(changed) - 20}")
    for path in stale:
        print("  消した " + rel(path))


if __name__ == "__main__":
    main()
