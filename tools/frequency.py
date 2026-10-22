#!/usr/bin/env python3
"""ページの出題頻度（front matter の frequency と frequency_evidence）を、データから機械的に付け直す。
基準は planning/catalog/README.md §5 と手引き（planning/style-guide.md）§17-7。

使い方:
  python3 tools/frequency.py               --check と同じ
  python3 tools/frequency.py --check       今の値と計算した値の差分を出す（差分があれば終了コード 1）
  python3 tools/frequency.py --write       差分のあるページの frequency・frequency_evidence の 2 行だけを書き換える
  python3 tools/frequency.py --page union-find --check
                                           そのページだけ（id かパス。複数回・カンマ区切りでもよい）
  python3 tools/frequency.py --root DIR    DIR/docs・DIR/data を読む（試験用）

材料:
  recent   data/recent-abc.yaml（abc451〜480 の D〜G）の pages に、そのページ（id#anchor は id）が出る問題の数。
           1問に同じページが何度出ても 1 回。alternatives は数えない
  前提     各ページの prerequisites を逆にたどって、そのページを前提に持つページの数（推移的に届く数と直接の数）。
           前提は type を問わずすべてのページのものを使う
  古い ABC data/problems.yaml で、contest が abc の問題（abc451〜480 を除く）のうち、そのページに載る
           （pages の役割が例題・練習・力試しのどれか）問題の数。status が 未確認 のものは数えない

基準:
  A  recent が 2 以上、または多くのページの前提（届くページが 13 以上か、直接の前提が 5 以上）
  B  recent が 1、または古い ABC が 3 問以上（§17-7）
  C  それ以外
  ただし MANUAL に書いたページは、計算した値が手で決めた値より低いときだけ手の値と文を使う（今は modint だけ）。

frequency_evidence の文の形（今のページの書き方のまま）:
  recent 2（abc455_e・abc473_e）・前提として 7 ページに届く（直接 3）・古い ABC 3 問
  recent 0・前提として届くページなし・古い ABC 2 問
  recent の問題は 6 問まで並べ、それより多いときは 6 問目の後ろに「ほか」を付ける。

frequency を持つのは type が technique・thinking・overview のページだけ（cpp・hub・guide・pattern・start は持たない）。
--write は front matter の 2 行（frequency: と frequency_evidence:）だけを置き換え、ほかの行の並びと書式は変えない。
2 行のどちらかがないページは書かずに知らせる。依存は PyYAML と tools/check_pages.py（ページの読み込み）。
"""
from __future__ import annotations

import argparse
import collections
import re
import sys
from dataclasses import dataclass
from pathlib import Path

import yaml

sys.path.insert(0, str(Path(__file__).resolve().parent))
import check_pages as cp  # noqa: E402

FREQ_TYPES = {"technique", "thinking", "overview"}
NO_FREQ_FIELDS = {"start", "guide", "patterns", "cpp"}
RECENT_RANGE = (451, 480)          # data/recent-abc.yaml の範囲。古い ABC の数からは除く
REACH_A = 13                       # 届くページがこの数以上で A
DIRECT_A = 5                       # 直接の前提がこの数以上で A
RECENT_A = 2
OLD_B = 3                          # 古い ABC の問題がこの数以上で B（§17-7）
LIST_MAX = 6                       # evidence に並べる recent の問題の数
UNCONFIRMED = "未確認"

# 手で決めた値（計算した値がこれより低いときだけ使う）
MANUAL = {
    "modint": ("A", "数え上げ・確率を mod で答える問題で常に使う道具（ページ単体の最近の出現は数えにくいので手で A にした）"),
}

ABC_RE = re.compile(r"^abc(\d+)$")


@dataclass
class Counts:
    recent: list[str]
    reach: int
    direct: int
    old: int


def classify(c: Counts) -> str:
    if len(c.recent) >= RECENT_A or c.reach >= REACH_A or c.direct >= DIRECT_A:
        return "A"
    if len(c.recent) == 1 or c.old >= OLD_B:
        return "B"
    return "C"


def evidence(c: Counts) -> str:
    ids = sorted(c.recent)
    if ids:
        shown = "・".join(ids[:LIST_MAX]) + ("ほか" if len(ids) > LIST_MAX else "")
        rec = f"recent {len(ids)}（{shown}）"
    else:
        rec = "recent 0"
    pre = f"前提として {c.reach} ページに届く（直接 {c.direct}）" if c.reach else "前提として届くページなし"
    return f"{rec}・{pre}・古い ABC {c.old} 問"


def decide(pid: str, c: Counts) -> tuple[str, str]:
    f, ev = classify(c), evidence(c)
    if pid in MANUAL:
        mf, mev = MANUAL[pid]
        if cp.FREQ_RANK[mf] < cp.FREQ_RANK[f]:
            return mf, mev
    return f, ev


def recent_counts(recent: list[dict]) -> dict[str, set[str]]:
    out: dict[str, set[str]] = collections.defaultdict(set)
    for e in recent:
        for x in e.get("pages") or []:
            out[str(x).split("#")[0]].add(e["id"])
    return out


def old_counts(ledger: dict[str, dict]) -> dict[str, set[str]]:
    out: dict[str, set[str]] = collections.defaultdict(set)
    for pid, e in ledger.items():
        m = ABC_RE.match(str(e.get("contest") or ""))
        if not m or RECENT_RANGE[0] <= int(m.group(1)) <= RECENT_RANGE[1]:
            continue
        if e.get("status") == UNCONFIRMED:
            continue
        for pg in e.get("pages") or []:
            if isinstance(pg, dict) and pg.get("role") in cp.ROLES and pg.get("id"):
                out[pg["id"]].add(pid)
    return out


def prereq_graph(prereqs: dict[str, list[str]]) -> dict[str, set[str]]:
    """前提 → それを直接の前提に持つページ。"""
    rev: dict[str, set[str]] = collections.defaultdict(set)
    for pid, qs in prereqs.items():
        for q in qs or []:
            rev[str(q).split("#")[0]].add(pid)
    return rev


def reach_of(rev: dict[str, set[str]], pid: str) -> set[str]:
    seen: set[str] = set()
    stack = [pid]
    while stack:
        v = stack.pop()
        for w in rev.get(v, ()):
            if w not in seen and w != pid:
                seen.add(w)
                stack.append(w)
    return seen


def compute(pages: list, ledger: dict[str, dict], recent: list[dict]) -> dict[str, tuple[str, str, Counts]]:
    rc = recent_counts(recent)
    oc = old_counts(ledger)
    rev = prereq_graph({p.id: p.get("prerequisites") or [] for p in pages})
    out = {}
    for p in pages:
        if p.get("type") not in FREQ_TYPES or p.dir_field in NO_FREQ_FIELDS:
            continue
        c = Counts(recent=sorted(rc.get(p.id, ())), reach=len(reach_of(rev, p.id)),
                   direct=len(rev.get(p.id, ())), old=len(oc.get(p.id, ())))
        f, ev = decide(p.id, c)
        out[p.id] = (f, ev, c)
    return out


FREQ_LINE_RE = re.compile(r"^frequency:[ \t]*(?P<v>.*?)[ \t]*$")
EV_LINE_RE = re.compile(r"^frequency_evidence:[ \t]*(?P<v>.*?)[ \t]*$")


def rewrite(text: str, freq: str, ev: str) -> str | None:
    """front matter の frequency・frequency_evidence の 2 行だけを置き換えた文を返す。2 行がそろわなければ None。"""
    lines = text.split("\n")
    if not lines or lines[0].rstrip() != "---":
        return None
    end = next((i for i in range(1, len(lines)) if lines[i].rstrip() in ("---", "...")), None)
    if end is None:
        return None
    fi = [i for i in range(1, end) if FREQ_LINE_RE.match(lines[i])]
    ei = [i for i in range(1, end) if EV_LINE_RE.match(lines[i])]
    if len(fi) != 1 or len(ei) != 1:
        return None
    lines[fi[0]] = f"frequency: {freq}"
    lines[ei[0]] = f"frequency_evidence: {yaml_scalar(ev)}"
    return "\n".join(lines)


def yaml_scalar(s: str) -> str:
    """そのまま書いて同じ文字列に読める値は引用符なしで、そうでなければ YAML の引用符付きで返す。"""
    try:
        if yaml.safe_load(f"k: {s}") == {"k": s}:
            return s
    except yaml.YAMLError:
        pass
    return yaml.safe_dump(s, allow_unicode=True, default_style='"', width=10**9).strip().removesuffix("\n...")


def main() -> None:
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    g = ap.add_mutually_exclusive_group()
    g.add_argument("--check", action="store_true", help="差分を出す（既定）")
    g.add_argument("--write", action="store_true", help="差分のあるページの 2 行を書き換える")
    ap.add_argument("--page", action="append", default=[], help="id かパス（複数回・カンマ区切り可）")
    ap.add_argument("--root", type=Path, default=cp.ROOT)
    args = ap.parse_args()

    root = args.root.resolve()
    pages, _ = cp.load_docs(root / "docs")
    ledger = cp.load_ledger(root / "data" / "problems.yaml")
    recent = cp.load_recent(root / "data" / "recent-abc.yaml")
    known = {p.id for p in pages}
    for e in recent:
        for x in e.get("pages") or []:
            if str(x).split("#")[0] not in known:
                print(f"警告: recent-abc の {e['id']} が知らないページ {x} を指す", file=sys.stderr)
    result = compute(pages, ledger, recent)

    want = {w.strip() for a in args.page for w in a.split(",") if w.strip()}

    def picked(p) -> bool:
        return not want or p.id in want or p.rel in want or f"docs/{p.rel}" in want

    diffs = 0
    written = 0
    for p in pages:
        if not picked(p):
            continue
        cur_f, cur_ev = p.get("frequency"), p.get("frequency_evidence")
        if p.id not in result:
            if cur_f is not None or cur_ev is not None:
                print(f"{p.rel}: frequency を持たない type・分野なのに値がある（{cur_f}）")
                diffs += 1
            continue
        f, ev, _ = result[p.id]
        if (cur_f, cur_ev) == (f, ev):
            continue
        diffs += 1
        mark = f"{cur_f} → {f}" if cur_f != f else f"{f}"
        print(f"{p.rel}: {mark}")
        if cur_ev != ev:
            print(f"  - {cur_ev}\n  + {ev}")
        if args.write:
            new = rewrite(p.path.read_text(encoding="utf-8"), f, ev)   # ほかの直しと重ならないよう読み直す
            if new is None:
                print(f"  書けない: front matter に frequency と frequency_evidence の行が 1 つずつない", file=sys.stderr)
                continue
            p.path.write_text(new, encoding="utf-8")
            written += 1
    print(f"差分 {diffs} ページ" + (f"（書き換え {written}）" if args.write else ""))
    sys.exit(1 if diffs and not args.write else 0)


if __name__ == "__main__":
    main()
