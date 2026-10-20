#!/usr/bin/env python3
"""目次（planning/catalog/*.yaml）を検証する。規則は planning/catalog/README.md §3・§7。

使い方:
  python3 tools/check_catalog.py                 全分野を検証し、統計を出す
  python3 tools/check_catalog.py --field ds      その分野のページの指摘だけを出す（下書き中の自己確認用）
終了コード: エラーがあれば 1（警告だけなら 0）
"""
from __future__ import annotations

import argparse
import collections
import re
import sys
from pathlib import Path

import yaml

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))
import ap  # noqa: E402  （同じフォルダの問題データの確認ツール）

FIELDS = ["start", "guide", "basics", "thinking", "dp", "graph", "tree", "ds", "math", "comb",
          "string", "geometry", "misc", "patterns", "cpp"]
TYPES = {"technique", "thinking", "pattern", "overview", "cpp", "guide"}
LEVELS = ["基礎", "水", "青", "黄", "発展"]
RANK = {lv: i for i, lv in enumerate(LEVELS)}
NO_LEVEL_FIELDS = {"start", "guide", "patterns"}
FREQ = {"A", "B", "C"}
ROLES = {"example", "practice", "challenge"}
KINDS = {
    "全探索", "二分探索", "累積和・差分", "尺取り・スライド窓", "貪欲", "ソート・座標圧縮", "ダブリング・分割統治",
    "DP", "グラフ探索", "最短路", "連結性・全域木", "フロー・マッチング", "木", "データ構造", "区間クエリ",
    "クエリ処理の工夫", "整数論", "線形代数・行列", "畳み込み・多項式", "数え上げ", "確率・期待値", "ゲーム",
    "文字列", "ハッシュ・乱択", "幾何", "ビット演算", "考察", "実装・C++", "案内",
}
ID_RE = re.compile(r"^[a-z0-9]+(-[a-z0-9]+)*$")


def load_yaml(path: Path):
    try:
        return yaml.safe_load(path.read_text(encoding="utf-8")) or {}
    except Exception as e:  # noqa: BLE001
        return e


def main() -> None:
    ap_ = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap_.add_argument("--field", choices=FIELDS)
    args = ap_.parse_args()

    errors: list[tuple[str, str]] = []    # (field, message)
    warnings: list[tuple[str, str]] = []

    # 調査の key
    research: dict[str, tuple[str, str]] = {}  # key -> (area file stem, title)
    for f in sorted((ROOT / "planning" / "research").glob("*.topics.yaml")):
        doc = load_yaml(f)
        if isinstance(doc, Exception):
            continue
        for t in doc.get("topics") or []:
            if t.get("key"):
                research.setdefault(t["key"], (f.stem.split(".")[0], t.get("title", "")))

    # 目次
    pages: dict[str, dict] = {}
    merged: dict[str, str] = {}           # 調査の key -> ページ id
    moved: dict[str, tuple[str, str]] = {}  # key -> (移す先, 移した分野)
    dropped: dict[str, str] = {}
    present: list[str] = []
    for field in FIELDS:
        path = ROOT / "planning" / "catalog" / f"{field}.yaml"
        if not path.exists():
            continue
        present.append(field)
        doc = load_yaml(path)
        if isinstance(doc, Exception):
            errors.append((field, f"{path.name}: YAML が読めない: {doc}"))
            continue
        if doc.get("field") != field:
            errors.append((field, f"{path.name}: field が {doc.get('field')!r}（{field!r} のはず）"))
        for p in doc.get("pages") or []:
            pid = p.get("id")
            if not pid or not ID_RE.match(str(pid)):
                errors.append((field, f"不正な id: {pid!r}（{p.get('title')}）"))
                continue
            if pid in pages:
                errors.append((field, f"id の重複: {pid}（{pages[pid]['_field']} と {field}）"))
                continue
            p["_field"] = field
            pages[pid] = p
            for k in p.get("merged_keys") or []:
                if k in merged and merged[k] != pid:
                    errors.append((field, f"merged_keys の重複: {k}（{merged[k]} と {pid}）"))
                merged[k] = pid
        for m in doc.get("moved") or []:
            moved[m.get("key")] = (m.get("to"), field)
        for d in doc.get("dropped") or []:
            dropped[d.get("key")] = d.get("reason", "")

    def resolve(ref: str) -> str | None:
        if ref in pages:
            return ref
        return merged.get(ref)

    data = ap.Data()
    graph: dict[str, list[str]] = collections.defaultdict(list)
    for pid, p in pages.items():
        field = p["_field"]
        where = f"{pid}"
        for key in ("title", "type", "summary"):
            if not p.get(key):
                errors.append((field, f"{where}: {key} がない"))
        t = p.get("type")
        if t and t not in TYPES:
            errors.append((field, f"{where}: type が不正: {t}"))
        lv = p.get("level")
        if field in NO_LEVEL_FIELDS:
            if lv is not None:
                warnings.append((field, f"{where}: この分野は level を持たない（{lv}）"))
        elif field == "cpp":
            if lv is not None and lv not in RANK:
                errors.append((field, f"{where}: level が不正: {lv}"))
        else:
            if lv not in RANK:
                errors.append((field, f"{where}: level が不正か、ない: {lv!r}"))
            if t == "overview" and lv != "発展":
                warnings.append((field, f"{where}: overview なのに level が {lv}"))
            if lv == "発展" and t != "overview":
                warnings.append((field, f"{where}: 発展なのに type が {t}"))
            if not p.get("level_evidence") and t in {"technique", "overview"}:
                warnings.append((field, f"{where}: level_evidence がない"))
        kinds = p.get("kind") or []
        if not kinds:
            errors.append((field, f"{where}: kind がない"))
        for k in kinds:
            if k not in KINDS:
                errors.append((field, f"{where}: kind が語彙にない: {k}"))
        fr = p.get("frequency")
        if field not in NO_LEVEL_FIELDS and t not in {"guide"} and fr not in FREQ:
            errors.append((field, f"{where}: frequency が不正か、ない: {fr!r}"))
        if t in {"technique", "thinking", "overview"} and not p.get("signs"):
            warnings.append((field, f"{where}: signs がない"))
        for s in p.get("signs") or []:
            if not isinstance(s, dict) or s.get("type") not in {"phrase", "constraint"} or not s.get("text"):
                errors.append((field, f"{where}: signs の形が不正: {s}"))
        for key in ("prerequisites", "related"):
            for ref in p.get(key) or []:
                r = resolve(ref)
                if r is None:
                    tag = "（相手の分野の catalog がまだない）" if ref in research and ref not in dropped else ""
                    (warnings if tag else errors).append((field, f"{where}: {key} を解決できない: {ref}{tag}"))
                elif key == "prerequisites":
                    if r == pid:
                        errors.append((field, f"{where}: 自分自身を前提にしている"))
                    else:
                        graph[pid].append(r)
                        plv, mylv = pages[r].get("level"), lv
                        if plv in RANK and mylv in RANK and RANK[plv] > RANK[mylv]:
                            warnings.append((field, f"{where}（{mylv}）: 前提 {r} のレベルが高い（{plv}）"))
        roles = collections.Counter()
        for q in p.get("problems") or []:
            qid = q.get("id")
            roles[q.get("role")] += 1
            if q.get("role") not in ROLES:
                errors.append((field, f"{where}: 問題の role が不正: {q}"))
            if not qid or data.info(qid) is None:
                errors.append((field, f"{where}: 問題が実在しない: {qid}"))

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
    for u in pages:
        if state.get(u) is None:
            dfs(u, [])
    for c in cycles:
        errors.append((pages[c[0]]["_field"], "前提の循環: " + " → ".join(c)))

    # 調査の key の取りこぼし
    uncovered = []
    for key, (area, title) in research.items():
        if key in pages or key in merged or key in dropped:
            continue
        if key in moved:
            to, frm = moved[key]
            if to in present:
                errors.append((to, f"{frm} から移された {key}（{title}）を {to} が取り込んでいない"))
            continue
        uncovered.append(f"{key}（{area}: {title}）")

    # 出力
    def show(items, label):
        sel = [m for f, m in items if args.field is None or f == args.field]
        print(f"\n{label} {len(sel)} 件")
        for m in sel:
            print("  " + m)

    if args.field is None:
        print(f"catalog: {len(present)} 分野 {present}")
        by_field = collections.Counter(p["_field"] for p in pages.values())
        by_type = collections.Counter(p.get("type") for p in pages.values())
        by_level = collections.Counter(p.get("level") for p in pages.values())
        print(f"ページ数: {len(pages)}  分野別: {dict(by_field)}")
        print(f"種類別: {dict(by_type)}")
        print(f"レベル別: {dict(by_level)}")
    show(errors, "エラー")
    show(warnings, "警告")
    if args.field is None:
        print(f"\n処理されていない調査の key {len(uncovered)} 件")
        for u in uncovered:
            print("  " + u)
    sys.exit(1 if [e for e in errors if args.field is None or e[0] == args.field] else 0)


if __name__ == "__main__":
    main()
