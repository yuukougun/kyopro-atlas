#!/usr/bin/env python3
"""目次（planning/catalog/*.yaml）を検証する（第2版）。規則は planning/catalog/README.md の §2〜§7。

使い方:
  python3 tools/check_catalog.py                  全分野を検証し、統計・エラーの全件・警告の種類ごとの件数を出す
  python3 tools/check_catalog.py --verbose        警告も全件を出す（-v でもよい）
  python3 tools/check_catalog.py --field ds       その分野のページに関わる指摘だけを出す（下書き中の自己確認用）
  python3 tools/check_catalog.py --field ds -v    その分野の警告も全件を出す
終了コード: エラーがあれば 1（警告だけなら 0）。--field のときはその分野のエラーだけで決める

重さ:
  エラー  形式（YAML・必須の項目・値の形）、解決できない参照（前提・related・id#anchor）、前提の循環、
          id の重複、調査の key の取りこぼし（README §6 の統合で消えたページの id を含む）、実在しない問題
  警告    それ以外（README §3 の規則からの外れ）。種類ごとに件数をまとめて出す

第1版から続く検査: 形式、id の重複、前提・related の解決と循環、前提のレベルの逆転、kind の語彙、問題の実在、
調査の key の取りこぼし（README §6 の統合で消えたページの id も key として扱う）
第2版で足した検査（README §7）: 節の構造（title・anchor・level。anchor の形と一意）と節のレベル（ページ以上、
基礎のページは青まで）、visual の形と priority 1 の数（担当ごとの枠と全体）、problems の形（role・代表問題・
summary に手法名らしい語がないか・approach）、推移的に冗長な前提、前提と related の重複、調査の key のままの
参照、id#anchor の anchor、同じ分野の前提の並び、入ってくる道のないページ、2ページ以上の例題、同じ別名、
根拠の問題の帯（abc319 以降を主に見る）、練習の不足、水・青の最近の問題、summary の文の数・長さ・禁止語、
signs の type と constraint の数、hub の規則、frequency の有無、問題の数の目安、統合が済んでいないページ

第1版と第2版の形式が混ざっていても止まらない。第1版の形式の項目（sections の要素が文字列、visual が文字列、
problems の要素に approach がない）は「第1版の形式のまま」の警告にし、その項目では第2版だけの検査を行わない。
意図した別名の重複は、関わる分野の open_issues に「別名「Fenwick」は…（意図した重複）」のように、語をかぎかっこ
（「」・『』）か ` で囲み、「別名」か「重複」とともに書くと数えない。
問題のデータ（difficulty・コンテスト）は tools/ap.py のキャッシュを読む（取得し直さない）。
"""
from __future__ import annotations

import argparse
import collections
import re
import sys
import unicodedata
from pathlib import Path

import yaml

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))
import ap  # noqa: E402  （同じフォルダの問題データの確認ツール）

CATALOG = ROOT / "planning" / "catalog"
RESEARCH = ROOT / "planning" / "research"

FIELDS = ["start", "guide", "basics", "thinking", "dp", "graph", "tree", "ds", "math", "comb",
          "string", "geometry", "misc", "patterns", "cpp"]
TYPES = {"technique", "thinking", "pattern", "hub", "overview", "cpp", "guide"}
LEVELS = ["基礎", "水", "青", "黄", "発展"]
RANK = {lv: i for i, lv in enumerate(LEVELS)}
NO_LEVEL_FIELDS = {"start", "guide", "patterns"}
NO_FREQ_FIELDS = {"cpp", "guide", "patterns", "start"}   # frequency を持たない（README §5）
NO_FREQ_TYPES = {"hub", "guide", "cpp"}
FREQ = {"A", "B", "C"}
ROLES = {"example", "practice", "challenge"}
SIGN_TYPES = {"phrase", "constraint", "shape"}
VISUAL_KINDS = {"dynamic", "static"}
KINDS = {
    "計算量", "全探索", "二分探索", "累積和・差分", "尺取り・スライド窓", "貪欲", "ソート・座標圧縮", "ダブリング・分割統治",
    "DP", "グラフ探索", "最短路", "連結性・全域木", "フロー・マッチング", "木", "データ構造", "区間クエリ",
    "クエリ処理の工夫", "整数論", "線形代数・行列", "畳み込み・多項式", "数え上げ", "確率・期待値", "ゲーム",
    "文字列", "ハッシュ・乱択", "幾何", "ビット演算", "考察", "実装・C++", "案内",
}
ID_RE = re.compile(r"^[a-z0-9]+(-[a-z0-9]+)*$")       # ページの id と節の anchor
PID_RE = re.compile(r"(?<![A-Za-z0-9_])([a-z][A-Za-z0-9_]*_[A-Za-z0-9]+)(?![A-Za-z0-9_])")   # 問題 ID らしい語
ABC_RE = re.compile(r"^abc(\d+)$")
RECENT_ABC = 319            # abc319（2023-09、7問体制）以降を「最近」とする（README §3.2-2）
PLACEHOLDER = "（執筆時に確かめる）"
SUMMARY_MAX = 120

PAGE_KEYS = {"id", "chapter", "title", "nav_title", "aliases", "type", "level", "level_evidence", "kind",
             "prerequisites", "related", "summary", "signs", "acl", "verify", "frequency", "frequency_evidence",
             "sections", "merged_keys", "visual", "problems", "problems_note", "sources"}
CPP_KEYS = {"cpp_std", "gcc_min", "atcoder"}     # cpp のページだけの項目（設計書 §3.3）
PROBLEM_KEYS = {"id", "role", "representative", "summary", "approach"}
SECTION_KEYS = {"title", "anchor", "level"}
VISUAL_KEYS = {"kind", "priority", "text"}

# visual の priority 1 の枠（design-review §4.2。担当ごと）。枠の書かれていない担当は 0 とみなす
VISUAL_P1_CAPS = [
    ("basics・thinking・misc", ("basics", "thinking", "misc"), 3),
    ("dp", ("dp",), 4),
    ("graph", ("graph",), 5),
    ("tree", ("tree",), 3),
    ("ds", ("ds",), 3),
    ("math", ("math",), 2),
    ("comb", ("comb",), 2),
    ("string・geometry", ("string", "geometry"), 2),
    ("cpp", ("cpp",), 0),
    ("start・guide・patterns", ("start", "guide", "patterns"), 0),
]
VISUAL_P1_TOTAL = 25        # 全体で25前後（design-review D8）

# 調査の area（topics.yaml の area・suggested_area）→ 担当の分野（取りこぼしの指摘を --field で担当に見せるため）
AREA_FIELD = {"curriculum": ("start", "guide", "patterns"), "basics": ("basics", "thinking", "misc"), "dp": ("dp",),
              "graph": ("graph",), "tree": ("tree",), "ds": ("ds",), "math-nt": ("math",), "math-comb": ("comb",),
              "string-geo": ("string", "geometry"), "cpp": ("cpp",)}

# 問題の summary（問いだけ）に入っていたら疑う語。kind の語彙のうち手法を指す語と、主な手法名（簡易な目安）。
# 問いにも出る語（最短路・全域木・マッチング・期待値・文字列・ゲーム・木・ソートなど）は入れない
TECH_WORDS = [
    "全探索", "全列挙", "半分全列挙", "枝刈り", "バックトラック", "二分探索", "三分探索", "決め打ち",
    "累積和", "いもす", "尺取り", "スライド最小値", "スライド窓", "貪欲", "交換論法", "座標圧縮", "イベントソート",
    "偏角ソート", "平面走査", "ダブリング", "分割統治", "動的計画", "メモ化", "桁 DP", "区間 DP", "木 DP",
    "全方位木", "挿入 DP", "幅優先", "深さ優先", "トポロジカルソート", "強連結成分", "ダイクストラ", "拡張ダイクストラ",
    "ワーシャル", "ベルマン", "クラスカル", "プリム法", "最大流", "最小カット", "燃やす埋める", "最小費用流",
    "オイラーツアー", "重心分解", "HL 分解", "マージテク", "データ構造", "セグ木", "セグメント木", "遅延セグ",
    "平方分割", "永続", "トライ木", "優先度付きキュー", "単調スタック", "オフライン", "逆順に処理", "クエリ先読み",
    "整数論", "逆元", "フェルマー", "エラトステネス", "篩", "素因数分解", "互除法", "中国剰余", "メビウス",
    "ゼータ変換", "約数包除", "線形代数", "行列累乗", "掃き出し", "ガウスの消去", "XOR 基底", "線形基底",
    "畳み込み", "形式的冪級数", "母関数", "二項係数", "包除", "主客転倒", "寄与", "余事象", "線形性",
    "ローリングハッシュ", "ハッシュ", "乱択", "接尾辞配列", "凸包", "外積", "スロープトリック", "幾何", "ビット演算",
    "bit ごと", "考察",
]
TECH_ASCII = [   # 英字の語は前後が英数字でないときだけ当てる
    "DP", "bitDP", "BFS", "DFS", "01-BFS", "0-1 BFS", "SCC", "lowlink", "2-SAT", "Dijkstra", "Union-Find",
    "UnionFind", "DSU", "Kruskal", "LCA", "HLD", "BIT", "Fenwick", "Sparse Table", "Mo", "Trie", "Wavelet",
    "set", "multiset", "map", "deque", "priority_queue", "lower_bound", "upper_bound", "CRT", "FFT", "NTT",
    "FPS", "Grundy", "Sprague", "KMP", "Z-algorithm", "Manacher", "Suffix Array", "Aho-Corasick", "CHT",
    "Li Chao", "Monge", "Alien", "slope trick", "ACL", "imos",
]
TECH_RE = re.compile("|".join(
    [re.escape(w) for w in sorted(TECH_WORDS, key=len, reverse=True)]
    + [r"(?<![A-Za-z0-9])" + re.escape(w) + r"(?![A-Za-z0-9_])" for w in sorted(TECH_ASCII, key=len, reverse=True)]))

# ページの summary に使わない語（README §3.5-1）
SUMMARY_NG = ["このページ", "ここ", "まとめる", "扱う", "紹介する"]
BAND_RE = re.compile(r"(水|青|黄)(色|の帯|帯|コーダー|レベル|の節|以上|以下|まで|から|で必須|で頻出)"
                     r"|(基礎|発展)(の帯|帯|レベル|の節)|[（(](基礎|水|青|黄|発展)[）)]")
DESU_RE = re.compile(r"(です|ます)(。|$|、)")
NUM_RE = re.compile(r"[0-9０-９≤≥<>≦≧＜＞]")


class Report:
    """指摘を (重さ, 種類, 関わる分野, 文) で持つ。分野が空のものは全体の指摘（--field では出さない）。"""

    def __init__(self) -> None:
        self.items: list[tuple[str, str, frozenset, str]] = []

    def add(self, sev: str, kind: str, fields, msg: str) -> None:
        if isinstance(fields, str):
            fields = (fields,)
        self.items.append((sev, kind, frozenset(fields or ()), msg))

    def error(self, kind: str, fields, msg: str) -> None:
        self.add("E", kind, fields, msg)

    def warn(self, kind: str, fields, msg: str) -> None:
        self.add("W", kind, fields, msg)

    def select(self, sev: str, field: str | None) -> list[tuple[str, str]]:
        return [(k, m) for s, k, f, m in self.items if s == sev and (field is None or field in f)]


def load_yaml(path: Path):
    try:
        return yaml.safe_load(path.read_text(encoding="utf-8"))
    except Exception as e:  # noqa: BLE001
        return e


def text(v) -> str:
    return v.strip() if isinstance(v, str) else ""


def scalar(v):
    """集合・辞書で引けるように、リストなどの値は repr の文字列にする（形の崩れた途中の状態でも落ちないため）。"""
    return v if v is None or isinstance(v, (str, int, float, bool)) else repr(v)


def norm_name(s) -> str:
    """別名の照合用：全角・半角をそろえ、空白・中黒・かっこを除き、小文字にする。"""
    s = unicodedata.normalize("NFKC", str(s))
    return re.sub(r"[\s・()（）]", "", s).lower()


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


def readme_merges(rep: Report) -> list[tuple[str, str, str, str]]:
    """README §6 の表（統合するページ → 受けるページ）を (key, 送る分野, 受ける分野, 受けるページ) の列で返す。"""
    try:
        body = (CATALOG / "README.md").read_text(encoding="utf-8")
    except OSError:
        rep.warn("README §6 を読めない", (), "planning/catalog/README.md がない")
        return []
    m = re.search(r"^## 6\..*?(?=^## |\Z)", body, re.M | re.S)
    out = []
    for line in (m.group(0).splitlines() if m else []):
        if not line.startswith("|"):
            continue
        cells = [c.strip() for c in line.strip().strip("|").split("|")]
        if len(cells) < 2:
            continue
        src = re.findall(r"([a-z]+)/([a-z0-9-]+)", cells[0])
        dst = re.findall(r"([a-z]+)/([a-z0-9-]+)", cells[1])
        if src and dst:
            out += [(k, f, dst[0][0], dst[0][1]) for f, k in src]
    if not out:
        rep.warn("README §6 を読めない", (), "README §6 の統合の表が見つからない（統合で消えたページの id を検査しない）")
    return out


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--field", choices=FIELDS, help="その分野のページに関わる指摘だけを出す")
    parser.add_argument("-v", "--verbose", action="store_true", help="警告も全件を出す")
    args = parser.parse_args()

    rep = Report()
    data = ap.Data()

    # ---- 調査の key
    research: dict[str, tuple[str, str, tuple]] = {}   # key -> (調査のファイル, 題名, 担当の分野)
    for f in sorted(RESEARCH.glob("*.topics.yaml")):
        doc = load_yaml(f)
        if not isinstance(doc, dict):
            continue
        area = doc.get("area")
        for t in doc.get("topics") or []:
            if isinstance(t, dict) and isinstance(t.get("key"), str):
                fld = AREA_FIELD.get(scalar(t.get("suggested_area")) or area, ())
                research.setdefault(t["key"], (f.stem.split(".")[0], str(t.get("title", "")), fld))

    # ---- 目次を読む
    pages: dict[str, dict] = {}
    order: list[str] = []
    merged: dict[str, str] = {}                     # 調査の key -> ページ id
    moved: dict[str, tuple[str, str]] = {}          # key -> (移す先, 移した分野)
    dropped: dict[str, str] = {}
    open_issues: dict[str, list[str]] = {}          # 分野 -> open_issues（意図した別名の重複の判定に使う）
    present: list[str] = []
    broken: list[str] = []                          # 読めなかった分野（取りこぼしの判定が不確かになる）
    for field in FIELDS:
        path = CATALOG / f"{field}.yaml"
        if not path.exists():
            continue
        present.append(field)
        doc = load_yaml(path)
        if isinstance(doc, Exception):
            mark = getattr(doc, "problem_mark", None)
            at = f"（{mark.line + 1} 行 {mark.column + 1} 列）" if mark else ""
            rep.error("YAML が読めない", field, f"{path.name}: {getattr(doc, 'problem', None) or doc}{at}")
            broken.append(field)
            continue
        if not isinstance(doc, dict):
            rep.error("形式", field, f"{path.name}: 最上位がマッピングでない")
            broken.append(field)
            continue
        if doc.get("field") != field:
            rep.error("形式", field, f"{path.name}: field が {doc.get('field')!r}（{field!r} のはず）")
        plist = doc.get("pages") or []
        if not isinstance(plist, list):
            rep.error("形式", field, f"{path.name}: pages がリストでない")
            plist = []
        for idx, p in enumerate(plist):
            if not isinstance(p, dict):
                rep.error("形式", field, f"{path.name}: pages の {idx + 1} 番目がマッピングでない")
                continue
            pid = p.get("id")
            if not isinstance(pid, str) or not ID_RE.match(pid):
                rep.error("形式", field, f"{field}: 不正な id: {pid!r}（{p.get('title')}）")
                continue
            if pid in pages:
                rep.error("id の重複", (field, pages[pid]["_field"]), f"id の重複: {pid}（{pages[pid]['_field']} と {field}）")
                continue
            p = dict(p)
            p["_field"], p["_idx"] = field, idx
            pages[pid] = p
            order.append(pid)
            mk = p.get("merged_keys") or []
            for k in (mk if isinstance(mk, list) else [mk]):
                if not isinstance(k, str):
                    rep.error("形式", field, f"{field}/{pid}: merged_keys に文字列でない要素: {k!r}")
                    continue
                if k in merged and merged[k] != pid:
                    rep.error("id の重複", (field, pages[merged[k]]["_field"]), f"merged_keys の重複: {k}（{merged[k]} と {pid}）")
                merged[k] = pid
        for key, store in (("moved", moved), ("dropped", dropped)):
            for m in doc.get(key) or []:
                if not isinstance(m, dict) or not isinstance(m.get("key"), str):
                    rep.error("形式", field, f"{path.name}: {key} の要素の形が不正: {m!r}")
                elif key == "moved":
                    store[m["key"]] = (m.get("to"), field)
                else:
                    store[m["key"]] = str(m.get("reason", ""))
        oi = doc.get("open_issues") or []
        open_issues[field] = [str(x) for x in (oi if isinstance(oi, list) else [oi])]

    def resolve(ref: str) -> str | None:
        if ref in pages:
            return ref
        return merged.get(ref)

    def where(pid: str) -> str:
        return f"{pages[pid]['_field']}/{pid}"

    def lst(p: dict, key: str) -> list:
        """リストの項目を返す。リストでなければ形式のエラーにし、文字列なら1要素のリストとして続ける。"""
        v = p.get(key)
        if v is None:
            return []
        if isinstance(v, list):
            return v
        rep.error("形式", p["_field"], f"{where(p['id'])}: {key} がリストでない: {v!r}")
        return [v] if isinstance(v, str) and key not in {"sections", "signs", "problems"} else []

    def info(qid):
        return data.info(qid) if isinstance(qid, str) else None

    def is_recent(x: dict | None) -> bool:
        m = ABC_RE.match(x["contest_id"]) if x else None
        return bool(m) and int(m.group(1)) >= RECENT_ABC

    # ---- ページごとの検査
    graph: dict[str, list[str]] = collections.defaultdict(list)
    incoming: collections.Counter = collections.Counter()
    example_pages: dict[str, list[str]] = collections.defaultdict(list)
    names: dict[str, set[tuple[str, str]]] = collections.defaultdict(set)   # 照合用の名前 -> {(ページ, 元の書き方)}
    fmt_tally: collections.Counter = collections.Counter()
    p1: dict[str, list[str]] = collections.defaultdict(list)       # 分野 -> priority 1 のページ
    anchor_refs: list[tuple[str, str, str, str]] = []                # (ページ, 項目, 相手, anchor)
    n_problems = 0
    for pid in order:
        p = pages[pid]
        field, w = p["_field"], where(pid)
        t, lv = scalar(p.get("type")), scalar(p.get("level"))

        for key in sorted(map(str, set(p) - PAGE_KEYS - {"_field", "_idx"} - (CPP_KEYS if field == "cpp" else set()))):
            rep.warn("知らない項目", field, f"{w}: 知らない項目 {key}（綴りの誤りか）")
        for key in ("title", "type", "summary"):
            if p.get(key) is not None and not isinstance(p.get(key), str):
                rep.error("形式", field, f"{w}: {key} が文字列でない: {p.get(key)!r}")
            elif not text(p.get(key)):
                rep.error("形式", field, f"{w}: {key} がない")
        if isinstance(p.get("type"), str) and t and t not in TYPES:
            rep.error("形式", field, f"{w}: type が不正: {t}")
        if p.get("nav_title") is not None and not isinstance(p.get("nav_title"), str):
            rep.error("形式", field, f"{w}: nav_title が文字列でない")
        lst(p, "verify")
        lst(p, "sources")
        lst(p, "acl")

        # レベル（第1版の検査）
        if field in NO_LEVEL_FIELDS:
            if lv is not None:
                rep.warn("level の付け方", field, f"{w}: この分野は level を持たない（{lv}）")
        elif t == "hub":
            if lv is not None:
                rep.warn("hub の規則", field, f"{w}: hub は level を持たない（{lv}）")
        elif field == "cpp":
            if lv is not None and lv not in RANK:
                rep.error("形式", field, f"{w}: level が不正: {lv}")
        else:
            if lv not in RANK:
                rep.error("形式", field, f"{w}: level が不正か、ない: {lv!r}")
            if t == "overview" and lv != "発展":
                rep.warn("level の付け方", field, f"{w}: overview なのに level が {lv}")
            if lv == "発展" and t != "overview":
                rep.warn("level の付け方", field, f"{w}: 発展なのに type が {t}")
            if not text(p.get("level_evidence")) and t in {"technique", "overview"}:
                rep.warn("level_evidence がない", field, f"{w}: level_evidence がない")
        has_band = lv in RANK and field != "cpp" and t != "hub"

        # kind・frequency
        kinds = lst(p, "kind")
        if not kinds:
            rep.error("形式", field, f"{w}: kind がない")
        for k in map(scalar, kinds):
            if k not in KINDS:
                rep.error("kind の語彙", field, f"{w}: kind が語彙にない: {k}")
        if len(kinds) > 3:
            rep.warn("kind の数", field, f"{w}: kind が {len(kinds)} 個（1〜3 個）")
        if t == "hub" and "案内" not in kinds:
            rep.warn("hub の規則", field, f"{w}: hub の kind に「案内」がない")
        fr = scalar(p.get("frequency"))
        if field in NO_FREQ_FIELDS or t in NO_FREQ_TYPES:
            if fr is not None:
                rep.warn("frequency を持たない", field, f"{w}: cpp・hub・guide・patterns・start は frequency を持たない（{fr}）")
        elif field not in NO_LEVEL_FIELDS and fr not in FREQ:
            rep.error("形式", field, f"{w}: frequency が不正か、ない: {fr!r}")

        # summary（README §3.5-1）
        s = text(p.get("summary"))
        if s:
            n = count_sentences(s)
            if n > 2 or len(s) > SUMMARY_MAX:
                rep.warn("summary の長さ・文の数", field, f"{w}: {n} 文・{len(s)} 字（2 文・{SUMMARY_MAX} 字まで）")
            bad = [x for x in SUMMARY_NG if x in s] + [m.group(0) for m in BAND_RE.finditer(s)]
            bad += ["です・ます"] if DESU_RE.search(s) else []
            if bad:
                rep.warn("summary の禁止語", field, f"{w}: 「{'」「'.join(dict.fromkeys(bad))}」")

        # signs（README §3.5-2）
        signs = lst(p, "signs")
        if t in {"technique", "thinking", "overview"} and not signs:
            rep.warn("signs がない", field, f"{w}: signs がない")
        for sg in signs:
            if not isinstance(sg, dict) or scalar(sg.get("type")) not in SIGN_TYPES or not text(sg.get("text")):
                rep.error("形式", field, f"{w}: signs の形が不正（type は phrase・constraint・shape）: {sg}")
            elif sg["type"] == "constraint" and not NUM_RE.search(sg["text"]):
                rep.warn("constraint に数・不等号がない", field, f"{w}: {sg['text']}")

        # 題名・別名
        title = text(p.get("title"))
        aliases = lst(p, "aliases")
        for a in aliases:
            if title and str(a).strip() == title:
                rep.warn("題名と同じ別名", field, f"{w}: {a}")
        for x in [title] + aliases:
            if str(x).strip():
                names[norm_name(x)].add((pid, str(x).strip()))

        # 前提と related（README §3.3）
        pre_ids: list[str] = []
        rel_ids: list[tuple[str, str | None]] = []
        for key in ("prerequisites", "related"):
            for ref in lst(p, key):
                if not isinstance(ref, str) or not ref.strip():
                    rep.error("形式", field, f"{w}: {key} に文字列でない要素: {ref!r}")
                    continue
                base, sharp, anchor = ref.partition("#")
                if sharp and not anchor:
                    rep.error("形式", field, f"{w}: {key} の # の後ろが空: {ref}")
                r = resolve(base)
                if r is None:
                    if base in moved and moved[base][0] in broken:
                        continue
                    if base in moved:
                        rep.warn("移した先がまだ取り込んでいない参照", field,
                                 f"{w}: {key} の {ref} は {moved[base][1]} が {moved[base][0]} へ移したが、まだ取り込まれていない")
                    else:
                        rep.error("解決できない参照", field, f"{w}: {key} を解決できない: {ref}")
                    continue
                if r != base:
                    rep.warn(f"{key} が調査の key のまま", field, f"{w}: {ref} → {r}{'#' + anchor if anchor else ''} と書く")
                if anchor:
                    if not ID_RE.match(anchor):
                        rep.error("形式", field, f"{w}: {key} の anchor の形が不正: {ref}")
                    anchor_refs.append((pid, key, r, anchor))
                    if key == "prerequisites":
                        rep.warn("前提に節（#anchor）", field, f"{w}: 前提はページの id で書く: {ref}")
                if r != pid:
                    incoming[r] += 1
                if key == "prerequisites":
                    if r == pid:
                        rep.error("前提の循環", field, f"{w}: 自分自身を前提にしている")
                        continue
                    if r in pre_ids:
                        continue
                    pre_ids.append(r)
                    graph[pid].append(r)
                    q = pages[r]
                    plv = scalar(q.get("level"))
                    if plv in RANK and lv in RANK and RANK[plv] > RANK[lv]:
                        rep.warn("前提のレベルが高い", field, f"{w}（{lv}）: 前提 {r} のレベルが高い（{plv}）")
                    if q["_field"] == field and q["_idx"] > p["_idx"]:
                        rep.warn("同じ分野の前提がナビゲーションで後ろ", field,
                                 f"{w}（{p.get('chapter')}）: 前提 {r}（{q.get('chapter')}）が後ろにある")
                else:
                    rel_ids.append((r, anchor or None))
        if len(pre_ids) > 4:
            rep.warn("前提が多い", field, f"{w}: 前提が {len(pre_ids)} 個（多くて 4 つ）")
        for r in dict.fromkeys(r for r, _ in rel_ids):
            if r in pre_ids:
                rep.warn("前提と related の重複", field, f"{w}: {r} が前提と related の両方にある")

        # sections（README §3.2-3・4）
        secs = lst(p, "sections")
        v1_secs, v2_secs, anchors = 0, 0, set()
        for sec in secs:
            if isinstance(sec, str):
                v1_secs += 1
                continue
            v2_secs += 1
            if not isinstance(sec, dict):
                rep.error("形式", field, f"{w}: sections の要素の形が不正: {sec!r}")
                continue
            st, an, slv = text(sec.get("title")), sec.get("anchor"), scalar(sec.get("level"))
            for key in sorted(map(str, set(sec) - SECTION_KEYS)):
                rep.warn("知らない項目", field, f"{w}: 節の知らない項目 {key}")
            if not st:
                rep.error("形式", field, f"{w}: 節に title がない: {sec}")
            if not isinstance(an, str) or not ID_RE.match(an):
                rep.error("形式", field, f"{w}: 節の anchor が不正（英小文字・数字・ハイフン）: {an!r}（{st}）")
            elif an in anchors:
                rep.error("id の重複", field, f"{w}: 節の anchor の重複: {an}")
            else:
                anchors.add(an)
            if slv is not None:
                if slv not in RANK:
                    rep.error("形式", field, f"{w}: 節の level が不正: {slv!r}（{st}）")
                elif lv in RANK:
                    if RANK[slv] < RANK[lv]:
                        rep.warn("節のレベルがページより低い", field, f"{w}（{lv}）: {st}（{slv}）")
                    if lv == "基礎" and RANK[slv] > RANK["青"]:
                        rep.warn("基礎のページに黄・発展の節", field, f"{w}: {st}（{slv}）")
        p["_anchors"] = anchors if v2_secs else None
        p["_anchors_partial"] = bool(v1_secs)

        # visual（README §3.5-5）
        vis = p.get("visual")
        v1_vis = isinstance(vis, str)
        if isinstance(vis, dict):
            for key in sorted(map(str, set(vis) - VISUAL_KEYS)):
                rep.warn("知らない項目", field, f"{w}: visual の知らない項目 {key}")
            pr = scalar(vis.get("priority"))
            if scalar(vis.get("kind")) not in VISUAL_KINDS:
                rep.error("形式", field, f"{w}: visual の kind が不正（dynamic・static）: {vis.get('kind')!r}")
            if isinstance(pr, bool) or pr not in (1, 2, 3):
                rep.error("形式", field, f"{w}: visual の priority が不正（1・2・3）: {pr!r}")
            elif pr == 1 and scalar(vis.get("kind")) == "dynamic":
                # 枠は動く図を作る量を抑えるためのもの。静的な図は数えない
                p1[field].append(pid)
            if not text(vis.get("text")):
                rep.error("形式", field, f"{w}: visual に text がない")
        elif vis is not None and not v1_vis:
            rep.error("形式", field, f"{w}: visual の形が不正: {vis!r}")

        # problems（README §3.4）
        roles: collections.Counter = collections.Counter()
        seen: set[str] = set()
        reps_: list[tuple[str, str, dict | None]] = []
        band_examples: list[str] = []
        v1_probs = v2_probs = 0
        recent = False
        probs = lst(p, "problems")
        for q in probs:
            if not isinstance(q, dict) or not isinstance(q.get("id"), str) or not q["id"].strip():
                rep.error("形式", field, f"{w}: problems の要素の形が不正: {q!r}")
                continue
            n_problems += 1
            qid, role = q["id"], scalar(q.get("role"))
            if role not in ROLES:
                rep.error("形式", field, f"{w}: 問題の role が不正: {qid} {role!r}")
            roles[role] += 1
            if qid in seen:
                rep.warn("同じページに同じ問題", field, f"{w}: {qid}")
            seen.add(qid)
            x = info(qid)
            if x is None:
                rep.error("実在しない問題", field, f"{w}: 問題が実在しない: {qid}")
            recent = recent or is_recent(x)
            if role == "example":
                example_pages[qid].append(pid)
                if x and x["difficulty"] is not None and x["level"] == lv:
                    band_examples.append(qid)
            for key in sorted(map(str, set(q) - PROBLEM_KEYS)):
                rep.warn("知らない項目", field, f"{w}: 問題 {qid} の知らない項目 {key}")
            if "approach" in q:
                v2_probs += 1
                qs = text(q.get("summary"))
                if not qs:
                    rep.error("形式", field, f"{w}: 問題 {qid} に summary がない")
                elif qs != PLACEHOLDER:
                    hits = list(dict.fromkeys(m.group(0) for m in TECH_RE.finditer(qs)))
                    if hits:
                        rep.warn("問題の summary に手法名らしい語", field, f"{w}: {qid}「{'」「'.join(hits)}」: {qs}")
                if not text(q.get("approach")):
                    rep.warn("問題の approach が空", field, f"{w}: {qid}")
            else:
                v1_probs += 1
            if "representative" in q:
                if not isinstance(q["representative"], bool):
                    rep.error("形式", field, f"{w}: 問題 {qid} の representative が true・false でない")
                elif q["representative"]:
                    reps_.append((qid, role, x))
        note = text(p.get("problems_note"))
        if p.get("problems_note") is not None and not isinstance(p.get("problems_note"), str):
            rep.error("形式", field, f"{w}: problems_note が文字列でない")

        # 代表問題（README §3.4-3）
        if reps_ or v2_probs:
            if len(reps_) > 1:
                rep.warn("代表問題", field, f"{w}: representative が {len(reps_)} 問（1 問）")
            for qid, role, x in reps_:
                if role != "example":
                    rep.warn("代表問題", field, f"{w}: 代表問題 {qid} が例題でない（{role}）")
                elif has_band and x and x["difficulty"] is not None and x["level"] != lv:
                    rep.warn("代表問題", field, f"{w}（{lv}）: 代表問題 {qid}（{x['difficulty']}）が帯の外")
            if not reps_ and band_examples and has_band:
                rep.warn("代表問題", field, f"{w}: 代表問題（representative: true）がない（帯の中の例題 {'・'.join(band_examples)}）")

        # 問題の数（README §3.4-1・7、hub の規則）
        e, pr_, ch = roles["example"], roles["practice"], roles["challenge"]
        if t in {"technique", "thinking", "overview"}:
            if pr_ < 2 and not note and t != "overview":    # overview（発展）の本文は例題 0〜2 だけ（設計書 §6）
                rep.warn("練習が2問未満で problems_note がない", field, f"{w}（{lv}）: 練習 {pr_} 問")
            if t == "thinking":
                lo, hi = 2, 4
            elif lv == "基礎":
                lo, hi = 1, 1
            elif lv == "発展" or t == "overview":
                lo, hi = 0, 2
            else:
                lo, hi = 1, 3
            if e > hi or (e < lo and not note) or (pr_ > 6 and t != "overview") or ch > 3:
                rng = "" if t == "overview" else "（2〜6）"
                rep.warn("問題の数が目安の外", field, f"{w}（{lv}・{t}）: 例題 {e}（{lo}〜{hi}）・練習 {pr_}{rng}・力試し {ch}（0〜3）")
        elif t == "hub":
            if e + pr_ + ch > 3 or e > 2:
                rep.warn("hub の規則", field, f"{w}: hub の問題は 0〜3（例題 0〜2）: 例題 {e}・練習 {pr_}・力試し {ch}")
        elif t == "pattern":
            if e > 1 or pr_ > 3 or ch > 0:
                rep.warn("問題の数が目安の外", field, f"{w}（pattern）: 例題 {e}（0〜1）・練習 {pr_}（0〜3）・力試し {ch}")
        if lv in ("水", "青") and has_band and not recent and not note:
            rep.warn(f"水・青のページに abc{RECENT_ABC} 以降の問題がない", field, f"{w}（{lv}）")

        # 根拠の問題と帯（README §3.2-2）：level_evidence と problems（帯より難しい力試しは除く）の問題のうち、
        # abc319 以降のものがあればそれだけを、なければ全部を見て、どれもページの帯に入らなければ指摘する
        if has_band:
            ids = [m.group(1) for m in PID_RE.finditer(text(p.get("level_evidence")))]
            ids += [q["id"] for q in probs
                    if isinstance(q, dict) and isinstance(q.get("id"), str) and q.get("role") != "challenge"]
            known = [(i, x) for i in dict.fromkeys(ids) if (x := info(i)) and x["difficulty"] is not None]
            rec = [(i, x) for i, x in known if is_recent(x)]
            use = rec or known
            if use and not any(x["level"] == lv for _, x in use):
                lab = f"abc{RECENT_ABC} 以降の問題" if rec else f"問題（abc{RECENT_ABC} 以降はない）"
                rep.warn("根拠の問題がどれも帯に入らない", field,
                         f"{w}（{lv}）: {lab}が帯の外: " + "・".join(f"{i} {x['difficulty']}" for i, x in use[:8]))

        # 第1版の形式のまま
        old = []
        if v1_secs:
            old.append(f"sections（{v1_secs} 節）")
        if v1_vis:
            old.append("visual")
        if v1_probs:
            old.append(f"problems（{v1_probs} 問）")
        if old:
            rep.warn("第1版の形式のまま", field, f"{w}: " + "・".join(old))
        new = bool(v2_secs or isinstance(vis, dict) or v2_probs)
        fmt_tally["混在" if old and new else "第1版" if old else "第2版" if new else "判定できない"] += 1

    # ---- id#anchor の anchor が相手のページの節にあるか
    for pid, key, r, anchor in anchor_refs:
        anchors = pages[r].get("_anchors")
        if anchors is None or (anchor not in anchors and pages[r].get("_anchors_partial")):
            rep.warn("anchor を確かめられない", pages[pid]["_field"],
                     f"{where(pid)}: {key} の {r}#{anchor}（{r} の sections が第1版の形式か、ない）")
        elif anchor not in anchors:
            rep.error("解決できない参照", pages[pid]["_field"], f"{where(pid)}: {key} の {r}#{anchor}: {r} にその anchor の節がない")

    # ---- 前提の循環
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
    for u in order:
        if state.get(u) is None:
            dfs(u, [])
    for c in cycles:
        rep.error("前提の循環", {pages[x]["_field"] for x in c}, "前提の循環: " + " → ".join(c))

    # ---- 推移的に冗長な前提（README §3.3-1）
    closure: dict[str, set[str]] = {}

    def reach(u: str) -> set[str]:
        if u not in closure:
            seen_, todo = set(), list(graph.get(u, []))
            while todo:
                v = todo.pop()
                if v not in seen_:
                    seen_.add(v)
                    todo += graph.get(v, [])
            closure[u] = seen_
        return closure[u]

    for pid in order:
        pre = graph.get(pid, [])
        for q in pre:
            via = [r for r in pre if r != q and q in reach(r)]
            if via:
                rep.warn("推移的に冗長な前提", pages[pid]["_field"], f"{where(pid)}: 前提 {q} は {via[0]} を経由して届く")

    # ---- 入ってくる道のないページ（README §3.3-5）
    for pid in order:
        if not incoming[pid]:
            rep.warn("入ってくる道がない", pages[pid]["_field"], f"{where(pid)}: どのページの prerequisites・related にも出てこない")

    # ---- 例題の重複（README §3.4-2）
    for qid, ps in sorted(example_pages.items()):
        if len(set(ps)) > 1:
            rep.warn("2ページ以上で例題", {pages[x]["_field"] for x in ps}, f"{qid}: " + "・".join(where(x) for x in ps))

    # ---- 同じ別名（または題名）（README §3.5-4）
    # 関わる分野の open_issues の1項目に、その語をかぎかっこ（「」・『』）か ` で囲んで「別名」か「重複」とともに
    # 書いてあれば、意図した重複とみなして数えない
    def declared(raw: str, fs: set[str]) -> bool:
        pat = re.compile(r"[「『`]\s*" + re.escape(raw) + r"\s*[」』`]", re.I)
        return any(("別名" in e or "重複" in e) and pat.search(e) for f in fs for e in open_issues.get(f, []))

    for nm, items in sorted(names.items()):
        ps = sorted({x for x, _ in items}, key=order.index)
        if len(ps) < 2:
            continue
        fs = {pages[x]["_field"] for x in ps}
        if any(declared(raw, fs) for _, raw in items):
            continue
        rep.warn("同じ別名（題名）が2ページ以上", fs, f"{sorted(raw for _, raw in items)[0]}: " + "・".join(where(x) for x in ps))

    # ---- visual の priority 1 の数（design-review §4.2・D8）
    total = sum(len(v) for v in p1.values())
    for label, fs, cap in VISUAL_P1_CAPS:
        got = [x for f in fs for x in p1.get(f, [])]
        if len(got) > cap:
            rep.warn("visual の priority 1 が枠を超える", fs, f"{label}: {len(got)}（枠 {cap}）: " + "・".join(got))
    if total > VISUAL_P1_TOTAL:
        rep.warn("visual の priority 1 が枠を超える", (), f"全体: {total}（{VISUAL_P1_TOTAL} 前後）")

    # ---- 調査の key の取りこぼし（README §3.1。§6 の統合で消えたページの id も key として扱う）
    def covered(key: str) -> bool:
        return key in pages or key in merged or key in dropped

    unsure = f"（{'・'.join(broken)} が読めないので不確か）" if broken else ""

    for key, (area, title, fld) in research.items():
        if covered(key):
            continue
        if key in moved:
            to, frm = moved[key]
            if to in present and to not in broken:
                rep.error("調査の key の取りこぼし", (to, frm), f"{frm} から移された {key}（{title}）を {to} が取り込んでいない")
            continue
        rep.error("調査の key の取りこぼし", fld, f"{key}（{area}: {title}）がどこにも入っていない（id・merged_keys・moved・dropped）{unsure}")
    merges = readme_merges(rep)
    for key, frm, to, owner in merges:
        fs = (frm, to)
        if key in pages:
            rep.warn("統合が済んでいない", fs, f"{key} はまだページ（README §6 では {to}/{owner} へ統合）")
        elif key in merged:
            if merged[key] != owner:
                rep.warn("統合が済んでいない", fs, f"{key} が {where(merged[key])} の merged_keys にある（README §6 では {to}/{owner}）")
        elif key in dropped:
            rep.warn("統合が済んでいない", fs, f"{key} が dropped にある（README §6 では {to}/{owner} へ統合）")
        elif key in moved:
            if key not in research and moved[key][0] in present and moved[key][0] not in broken:
                rep.error("調査の key の取りこぼし", fs, f"{moved[key][1]} から移された {key} を {moved[key][0]} が取り込んでいない（README §6 では {owner}）")
        elif key not in research:
            rep.error("調査の key の取りこぼし", fs, f"統合で消えたページ {frm}/{key} がどこにも入っていない（README §6 では {to}/{owner} の merged_keys）{unsure}")
    merge_keys = {key for key, *_ in merges}
    for k, pid in merged.items():
        if k in pages and k != pid and k not in merge_keys:
            rep.warn("統合が済んでいない", (pages[k]["_field"], pages[pid]["_field"]),
                     f"{k} が {where(pid)} の merged_keys にあるのに、まだページとしてある")

    # ---- 出力
    sel_field = args.field
    if sel_field is None:
        print(f"catalog: {len(present)} 分野 {present}")
        by_field = collections.Counter(pages[x]["_field"] for x in order)
        by_type = collections.Counter(scalar(pages[x].get("type")) for x in order)
        by_level = collections.Counter(scalar(pages[x].get("level")) for x in order)
        print(f"ページ数: {len(order)}  分野別: {dict(by_field)}")
        print(f"種類別: {dict(by_type)}")
        print(f"レベル別: {dict(by_level)}")
        print("形式: " + "・".join(f"{k} {fmt_tally[k]}" for k in ("第2版", "第1版", "混在", "判定できない")) + " ページ")
        print(f"問題: 延べ {n_problems}・例題 {sum(len(v) for v in example_pages.values())}　visual の priority 1: {total}"
              + (f"（{', '.join(f'{f} {len(v)}' for f, v in p1.items())}）" if p1 else ""))
    else:
        ps = [x for x in order if pages[x]["_field"] == sel_field]
        print(f"{sel_field}: {len(ps)} ページ")

    errors = rep.select("E", sel_field)
    warnings = rep.select("W", sel_field)
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
    print(f"\n警告 {len(warnings)} 件" + ("" if args.verbose else "（種類ごとの件数と1件目。全件は --verbose）"))
    for k, ms in sorted(groups.items(), key=lambda kv: -len(kv[1])):
        if args.verbose:
            print(f"  [{k}] {len(ms)} 件")
            for m in ms:
                print("    " + m)
        else:
            ex = ms[0] if len(ms[0]) <= 110 else ms[0][:109] + "…"
            print(f"  {len(ms):5d}  {k}　例: {ex}")
    sys.exit(1 if errors else 0)


if __name__ == "__main__":
    main()
