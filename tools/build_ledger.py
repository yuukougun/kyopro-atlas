#!/usr/bin/env python3
"""問題の台帳 data/problems.yaml の下書きを、catalog と調査レポートから作る（design-review D3）。

使い方:
  python3 tools/build_ledger.py            台帳を作り直して data/problems.yaml に書き、統計を出す
  python3 tools/build_ledger.py --check    catalog と台帳の食い違いを報告する（書かない）。食い違いがあれば終了コード 1
  python3 tools/build_ledger.py --stdout   書かずに台帳の YAML を標準出力に出す（統計は標準エラー出力へ）
  python3 tools/build_ledger.py --force    checked の付いた項目がある台帳や、読めない catalog があっても書く

対象: catalog（planning/catalog/*.yaml）の全ページの problems に出る問題（役割を問わない）。1問1項目で ID の順。
項目:
  id・contest（初出のコンテスト）・index・title・difficulty・experimental（difficulty が参考値か）・
  difficulty_fetched（difficulty の取得日）
      tools/ap.py のキャッシュ（.cache/atcoder-problems/、取得日は fetched_at.txt）から。取得し直さない
  summary（問い）・approach（方針）
      catalog の第2版の値。第1版の summary しかないときは、かっこの外の最初の「。」までを summary、残りを
      approach の候補にする。手法名・出典の分類だけの要約（「§2.3.8 の分類」「最近の D」「の基本形」など）は
      summary を「（執筆時に確かめる）」にし、全文を approach に入れる。ページによって食い違うときは example の
      ページの値を優先し（次に第2版の値、次に catalog の順）、ほかの値は alternatives に残す
  pages       使っているページの id と役割（catalog の順）
  evidence    planning/research/*.md と *.topics.yaml で、その問題 ID と同じ行（表の行・箇条書きの行。topics.yaml
              では問題の項目と、ID を含む文字列）に出る URL のうち、atcoder.jp・codeforces.com・kenkoooo.com 以外のもの
  status      同じ行か、その行を含む表（見出し行・直前の文）・節（見出し）が「未確認」「確認できなかった」「却下」
              「不採用」と書いている（topics.yaml では status: unverified も）なら 未確認。そうでなく evidence が
              あれば 確認済み、なければ 未確認
  unverified_in  未確認と書いている場所（ファイル:行）。人が確かめて status を直すときの手がかり（あるときだけ）
  checked     確かめた日。空（人が書く）

統計（問題数・status 別・evidence のない問題の一覧）は標準出力に出す。台帳に checked の付いた項目があるときは、
人が確かめた結果を消さないよう上書きしない（--force で上書き）。
"""
from __future__ import annotations

import argparse
import collections
import re
import sys
import urllib.parse
from pathlib import Path

import yaml

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))
import ap  # noqa: E402  （同じフォルダの問題データの確認ツール）

CATALOG = ROOT / "planning" / "catalog"
RESEARCH = ROOT / "planning" / "research"
LEDGER = ROOT / "data" / "problems.yaml"

FIELDS = ["start", "guide", "basics", "thinking", "dp", "graph", "tree", "ds", "math", "comb",
          "string", "geometry", "misc", "patterns", "cpp"]
ROLE_JA = {"example": "例題", "practice": "練習", "challenge": "力試し"}
PLACEHOLDER = "（執筆時に確かめる）"
CONFIRMED, UNCONFIRMED, REJECTED = "確認済み", "未確認", "不採用"

MARK_RE = re.compile("未確認|確認できなかった|却下|不採用")
PID_RE = re.compile(r"(?<![A-Za-z0-9_])([a-z][A-Za-z0-9_]*_[A-Za-z0-9]+)(?![A-Za-z0-9_])")
URL_RE = re.compile(r"https?://[A-Za-z0-9\-._~:/?#@!$&*+,;=%]+")
EXCLUDED_HOSTS = ("atcoder.jp", "codeforces.com", "kenkoooo.com")
HEADING_RE = re.compile(r"^(#{1,6})\s+(.*?)\s*#*\s*$")
# 第1版の要約が手法名・出典の分類だけかを見る語
SOURCE_ONLY_RE = re.compile(r"§2\.3\.8|§5\.2|執筆時|最近の [A-H](?![A-Za-z])|\d{4} 年の [A-H](?![A-Za-z])|をそのまま使う")
LABEL_RE = re.compile(r"の基本形|の使用例|の演習")
LABEL_TAIL_RE = re.compile(r"^(?P<q>.+?)\s*[（(](?P<label>[^（）()]*)[）)]$")


# ---------------------------------------------------------------- catalog

def clean(v) -> str:
    return re.sub(r"\s+", " ", v).strip() if isinstance(v, str) else ""


def scalar(v):
    """集合・辞書で引けるように、リストなどの値は repr の文字列にする（形の崩れた途中の状態でも落ちないため）。"""
    return v if v is None or isinstance(v, (str, int, float, bool)) else repr(v)


def split_first_sentence(s: str) -> tuple[str, str]:
    """かっこの外の最初の「。」で2つに分ける（「。」は前に含める）。"""
    depth = 0
    for i, ch in enumerate(s):
        if ch in "（(「『":
            depth += 1
        elif ch in "）)」』":
            depth = max(0, depth - 1)
        elif ch == "。" and depth == 0:
            return s[: i + 1], s[i + 1:].strip()
    return s, ""


def from_v1(s: str) -> tuple[str, str]:
    """第1版の要約を (summary, approach) に分ける。"""
    if not s:
        return PLACEHOLDER, ""
    head, tail = split_first_sentence(s)
    if SOURCE_ONLY_RE.search(head):
        return PLACEHOLDER, s
    core, dot = (head[:-1], "。") if head.endswith("。") else (head, "")
    m = LABEL_TAIL_RE.match(core)
    if m and LABEL_RE.search(m.group("label")) and not LABEL_RE.search(m.group("q")):
        # 「問い（〜の基本形）」：かっこの中は型の名前なので approach へ
        return m.group("q").strip() + dot, "。".join(x for x in (m.group("label").strip(), tail) if x)
    if LABEL_RE.search(head):
        return PLACEHOLDER, s
    return head, tail


def load_catalog() -> tuple[dict[str, list[dict]], list[str]]:
    """問題 ID → 使っているページの列。読めなかった分野の名前も返す。"""
    uses: dict[str, list[dict]] = collections.defaultdict(list)
    broken: list[str] = []
    for fi, field in enumerate(FIELDS):
        path = CATALOG / f"{field}.yaml"
        if not path.exists():
            continue
        try:
            doc = yaml.safe_load(path.read_text(encoding="utf-8"))
        except Exception as e:  # noqa: BLE001
            print(f"警告: {path.name} が読めない（{getattr(e, 'problem', None) or e}）。この分野の問題は入らない", file=sys.stderr)
            broken.append(field)
            continue
        pages = doc.get("pages") if isinstance(doc, dict) else None
        for pi, p in enumerate(pages if isinstance(pages, list) else []):
            if not isinstance(p, dict) or not isinstance(p.get("id"), str) or not isinstance(p.get("problems"), list):
                continue
            for qi, q in enumerate(p["problems"]):
                if not isinstance(q, dict) or not isinstance(q.get("id"), str) or not q["id"].strip():
                    continue
                v2 = "approach" in q
                summary, approach = (clean(q.get("summary")), clean(q.get("approach"))) if v2 else from_v1(clean(q.get("summary")))
                uses[q["id"].strip()].append({"page": p["id"], "field": field, "role": scalar(q.get("role")), "order": (fi, pi, qi),
                                              "v2": v2, "summary": summary, "approach": approach})
    return uses, broken


# ---------------------------------------------------------------- 調査レポート

def urls_in(s: str) -> list[str]:
    out = []
    for m in URL_RE.finditer(s):
        u = m.group(0).rstrip(".,;:!?*")
        host = (urllib.parse.urlsplit(u).hostname or "").lower()
        if not any(host == h or host.endswith("." + h) for h in EXCLUDED_HOSTS):
            out.append(u)
    return out


class Evidence:
    """問題ごとの裏付けの URL と、「未確認」などと書いている場所。"""

    def __init__(self, ids: set[str]) -> None:
        self.ids = ids
        self.urls: dict[str, list[str]] = collections.defaultdict(list)
        self.marks: dict[str, list[str]] = collections.defaultdict(list)

    def add(self, s: str, urls: list[str], reasons: list[str]) -> None:
        for pid in dict.fromkeys(PID_RE.findall(s)):
            if pid in self.ids:
                self.urls[pid] += [u for u in urls if u not in self.urls[pid]]
                self.marks[pid] += [r for r in reasons if r not in self.marks[pid]]

    def scan_markdown(self, path: Path) -> None:
        name = path.name
        stack: list[tuple[int, str, int]] = []      # 見出し (深さ, 文, 行)
        fence = in_table = False
        table_reason: str | None = None
        last_text: tuple[int, str] | None = None   # 表の直前の文を見るため
        for i, line in enumerate(path.read_text(encoding="utf-8").split("\n"), 1):
            s = line.strip()
            if s.startswith(("```", "~~~")):
                fence = not fence
                continue
            if fence:
                continue
            m = HEADING_RE.match(line)
            if m:
                while stack and stack[-1][0] >= len(m.group(1)):
                    stack.pop()
                stack.append((len(m.group(1)), m.group(2), i))
                in_table, last_text = False, None
                continue
            if s.startswith("|"):
                if not in_table:
                    in_table = True
                    if MARK_RE.search(s):
                        table_reason = f"{name}:{i}（表の見出し行）"
                    elif last_text and i - last_text[0] <= 2 and MARK_RE.search(last_text[1]):
                        table_reason = f"{name}:{last_text[0]}（表の直前の文）"
                    else:
                        table_reason = None
            else:
                in_table = False
                if s:
                    last_text = (i, s)
            if not PID_RE.search(line):
                continue
            reasons = [f"{name}:{i}（同じ行）"] if MARK_RE.search(line) else []
            if in_table and table_reason:
                reasons.append(table_reason)
            sec = next((h for h in stack if MARK_RE.search(h[1])), None)
            if sec:
                reasons.append(f"{name}:{sec[2]}（節「{sec[1]}」）")
            self.add(line, urls_in(line), reasons)

    def scan_topics(self, path: Path) -> None:
        name = path.name

        class LineLoader(yaml.SafeLoader):
            pass

        def mapping(loader, node):
            m = loader.construct_mapping(node, deep=True)
            m["__line__"] = node.start_mark.line + 1
            return m

        LineLoader.add_constructor(yaml.resolver.BaseResolver.DEFAULT_MAPPING_TAG, mapping)
        try:
            doc = yaml.load(path.read_text(encoding="utf-8"), Loader=LineLoader)  # noqa: S506（SafeLoader の派生）
        except Exception as e:  # noqa: BLE001
            print(f"警告: {name} が読めない（{e}）", file=sys.stderr)
            return

        def strings(v):
            if isinstance(v, str):
                yield v
            elif isinstance(v, list):
                for x in v:
                    yield from strings(x)
            elif isinstance(v, dict):
                for k, x in v.items():
                    if k != "__line__":
                        yield from strings(x)

        for t in (doc.get("topics") or []) if isinstance(doc, dict) else []:
            if not isinstance(t, dict):
                continue
            for q in t.get("problems") or []:
                if isinstance(q, dict) and isinstance(q.get("id"), str):
                    body = " ".join(str(v) for k, v in q.items() if k != "__line__")
                    marked = q.get("status") == "unverified" or MARK_RE.search(body)
                    self.add(q["id"], urls_in(body), [f"{name}:{q['__line__']}（問題の項目）"] if marked else [])
            for k, v in t.items():
                if k in ("problems", "__line__"):
                    continue
                for s in strings(v):
                    reasons = [f"{name}:{t['__line__']}（{t.get('key')} の {k}）"] if MARK_RE.search(s) else []
                    self.add(s, urls_in(s), reasons)


def collect_evidence(ids: set[str]) -> Evidence:
    ev = Evidence(ids)
    for path in sorted(RESEARCH.glob("*")):
        if path.name.endswith(".topics.yaml"):
            ev.scan_topics(path)
        elif path.suffix == ".md":
            ev.scan_markdown(path)
    return ev


# ---------------------------------------------------------------- 台帳

class Flow(dict):
    """1行で書くマッピング（pages の要素）。"""


class Dumper(yaml.SafeDumper):
    def ignore_aliases(self, data):  # noqa: ANN001
        return True


Dumper.add_representer(Flow, lambda d, v: d.represent_mapping("tag:yaml.org,2002:map", v, flow_style=True))

HEADER = """\
# 問題の台帳（design-review D3）。tools/build_ledger.py が catalog と調査レポートから作った下書き。
# 1問1項目。項目の意味と status の決め方は tools/build_ledger.py の冒頭に書いた。
# status が 未確認 の問題は本文に使わない。確かめたら status を直し、checked に日付を書く。
"""


def fetched_date() -> str | None:
    try:
        return (ap.CACHE / "fetched_at.txt").read_text(encoding="utf-8").strip()[:10] or None
    except OSError:
        return None


def build(uses: dict[str, list[dict]], data: ap.Data, ev: Evidence) -> tuple[list[dict], list[str]]:
    entries, missing = [], []
    date = fetched_date()
    for pid in sorted(uses):
        x = data.info(pid)
        if x is None:
            missing.append(pid)
            continue
        us = sorted(uses[pid], key=lambda u: u["order"])
        ranked = sorted(us, key=lambda u: (u["role"] != "example", not u["v2"], u["order"]))
        best = ranked[0]
        alts: dict[tuple[str, str], list[str]] = {}
        for u in ranked[1:]:
            val = (u["summary"], u["approach"])
            if val != (best["summary"], best["approach"]):
                alts.setdefault(val, [])
                if u["page"] not in alts[val]:
                    alts[val].append(u["page"])
        e = {
            "id": pid,
            "contest": x["contest_id"],
            "index": x["index"],
            "title": x["name"],
            "difficulty": x["difficulty"],
            "experimental": x["experimental"],
            "difficulty_fetched": date,
            "summary": best["summary"],
            "approach": best["approach"],
        }
        if alts:
            e["alternatives"] = [{"pages": ps, "summary": s, "approach": a} for (s, a), ps in alts.items()]
        e["pages"] = [Flow(id=page, role=role) for page, role in dict.fromkeys((u["page"], u["role"]) for u in us)]
        e["evidence"] = list(ev.urls.get(pid, []))
        marks = ev.marks.get(pid, [])
        e["status"] = UNCONFIRMED if marks or not e["evidence"] else CONFIRMED
        if marks:
            e["unverified_in"] = list(marks)
        e["checked"] = None
        entries.append(e)
    return entries, missing


def dump(entries: list[dict]) -> str:
    body = yaml.dump({"problems": entries}, Dumper=Dumper, allow_unicode=True, sort_keys=False, width=4096)
    return HEADER + body


def page_list(us: list[dict]) -> str:
    return "・".join(f"{u['field']}/{u['page']}（{ROLE_JA.get(u['role'], u['role'])}）" for u in sorted(us, key=lambda u: u["order"]))


def stats(entries: list[dict], uses: dict[str, list[dict]], missing: list[str], out) -> None:
    n = len(entries)
    st = collections.Counter(e["status"] for e in entries)
    marked = [e for e in entries if e.get("unverified_in")]
    noev = [e for e in entries if not e["evidence"]]
    kinds = collections.Counter()
    for e in marked:
        for k in ("同じ行", "問題の項目", "表の", "節「", " の "):
            if any(k in r for r in e["unverified_in"]):
                kinds[{"同じ行": "同じ行", "問題の項目": "topics.yaml の項目", "表の": "表", "節「": "節",
                       " の ": "topics.yaml の文"}[k]] += 1
    only_wide = [e for e in marked if e["evidence"] and all(("表の" in r or "節「" in r) for r in e["unverified_in"])]
    ex_unconf = [e for e in entries if e["status"] == UNCONFIRMED and any(u["role"] == "example" for u in uses[e["id"]])]
    print(f"問題数: {n}（catalog の延べ {sum(len(v) for v in uses.values())} 件）", file=out)
    print("status: " + "・".join(f"{k} {st[k]}" for k in (CONFIRMED, UNCONFIRMED)), file=out)
    print(f"  未確認のうち、調査が「未確認」などと書いている {len(marked)} 問（" + "・".join(f"{k} {v}" for k, v in kinds.most_common())
          + f"。重なりあり）、裏付けの URL がない {sum(1 for e in noev if not e.get('unverified_in'))} 問", file=out)
    print(f"  そのうち表・節の見出しだけで未確認になり、ほかの行には URL がある問題: {len(only_wide)}"
          "（その URL で確かめられれば確認済みに直せる候補）", file=out)
    print(f"  未確認の問題を例題にしている: {len(ex_unconf)} 問（--check で一覧）", file=out)
    print(f"要約がページで食い違う問題（alternatives あり）: {sum(1 for e in entries if e.get('alternatives'))}", file=out)
    print(f"summary が「{PLACEHOLDER}」: {sum(1 for e in entries if e['summary'] == PLACEHOLDER)}", file=out)
    print(f"difficulty がない問題: {sum(1 for e in entries if e['difficulty'] is None)}", file=out)
    if missing:
        print(f"実在しない問題（台帳に入れない）{len(missing)} 問: " + "、".join(f"{m}（{page_list(uses[m])}）" for m in missing), file=out)
    print(f"\nevidence のない問題 {len(noev)} 問:", file=out)
    for e in noev:
        print(f"  {e['id']}\t{e['index']}. {e['title']}\t{e['difficulty']}\t{page_list(uses[e['id']])}", file=out)


def check(uses: dict[str, list[dict]], broken: list[str], data: ap.Data) -> int:
    if not LEDGER.exists():
        print(f"台帳 {LEDGER.relative_to(ROOT)} がない。先に python3 tools/build_ledger.py で作る")
        return 1
    try:
        doc = yaml.safe_load(LEDGER.read_text(encoding="utf-8")) or {}
        items = {e["id"]: e for e in doc.get("problems") or [] if isinstance(e, dict) and isinstance(e.get("id"), str)}
    except Exception as e:  # noqa: BLE001
        print(f"台帳が読めない: {e}")
        return 1
    if broken:
        print(f"注意: catalog の {'・'.join(broken)} が読めないので、その分野の問題は数えていない")
    nonexist = sorted(pid for pid in uses if data.info(pid) is None)
    absent = sorted(pid for pid in uses if pid not in items and pid not in nonexist)
    gone = sorted(pid for pid in items if pid not in uses)
    unconf = [pid for pid in sorted(uses) if pid in items and items[pid].get("status") == UNCONFIRMED
              and any(u["role"] == "example" for u in uses[pid])]
    rejected = [pid for pid in sorted(uses) if pid in items and items[pid].get("status") == REJECTED]
    diff = []
    for pid in sorted(uses):
        if pid in items:
            have = {(scalar(p.get("id")), scalar(p.get("role"))) for p in items[pid].get("pages") or [] if isinstance(p, dict)}
            if have != {(u["page"], u["role"]) for u in uses[pid]}:
                diff.append(pid)

    def show(label: str, ids: list[str], detail) -> None:
        print(f"\n{label} {len(ids)} 問")
        for pid in ids:
            print(f"  {pid}\t{detail(pid)}")

    print(f"台帳 {len(items)} 問・catalog {len(uses)} 問")
    show("台帳にない問題（catalog にある）", absent, lambda p: page_list(uses[p]))
    show("catalog から消えた問題（台帳にだけある）", gone,
         lambda p: "・".join(f"{x.get('id')}（{ROLE_JA.get(scalar(x.get('role')), x.get('role'))}）" for x in items[p].get("pages") or [] if isinstance(x, dict)))
    show("未確認の問題を例題に使っている", unconf,
         lambda p: page_list([u for u in uses[p] if u["role"] == "example"]) + "　" + "、".join(items[p].get("unverified_in") or ["裏付けの URL がない"]))
    if rejected:
        show("不採用の問題を catalog が使っている", rejected, lambda p: page_list(uses[p]))
    if nonexist:
        show("実在しない問題（catalog の誤り）", nonexist, lambda p: page_list(uses[p]))
    show("使うページ・役割が台帳と違う（作り直すと直る）", diff, lambda p: page_list(uses[p]))
    return 1 if absent or gone or unconf or rejected or nonexist else 0


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--check", action="store_true", help="catalog と台帳の食い違いを報告する（書かない）")
    parser.add_argument("--stdout", action="store_true", help="書かずに YAML を標準出力に出す")
    parser.add_argument("--force", action="store_true", help="checked の付いた項目や読めない catalog があっても書く")
    args = parser.parse_args()

    data = ap.Data()
    uses, broken = load_catalog()
    if args.check:
        sys.exit(check(uses, broken, data))

    if broken and not args.force and not args.stdout:
        sys.exit(f"catalog の {'・'.join(broken)} が読めないので書かない（--force で書く）")
    if LEDGER.exists() and not args.force and not args.stdout:
        try:
            old = yaml.safe_load(LEDGER.read_text(encoding="utf-8")) or {}
            done = [e.get("id") for e in old.get("problems") or [] if isinstance(e, dict) and e.get("checked")]
        except Exception:  # noqa: BLE001
            sys.exit(f"今の {LEDGER.relative_to(ROOT)} が読めないので上書きしない（--force で上書き）")
        if done:
            sys.exit(f"今の台帳に checked の付いた項目が {len(done)} 問ある（{', '.join(map(str, done[:5]))} など）。"
                     "人が確かめた結果を消さないよう上書きしない（--force で上書き）")

    entries, missing = build(uses, data, collect_evidence(set(uses)))
    text = dump(entries)
    if args.stdout:
        sys.stdout.write(text)
        stats(entries, uses, missing, sys.stderr)
        return
    LEDGER.parent.mkdir(parents=True, exist_ok=True)
    LEDGER.write_text(text, encoding="utf-8")
    print(f"台帳: {LEDGER.relative_to(ROOT)} に書いた")
    stats(entries, uses, missing, sys.stdout)


if __name__ == "__main__":
    main()
