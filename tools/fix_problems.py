#!/usr/bin/env python3
"""本文の問題の一覧（<div class="kp-problems" …> の囲み）の各行の label・URL・difficulty を、台帳 data/problems.yaml から
作り直す（planning/interfaces.md §3）。要約（「：」の後ろ）は変えない。

使い方:
  python3 tools/fix_problems.py                  全ページを直す（変わったファイルだけ書く）
  python3 tools/fix_problems.py --check          直すべき行を出すだけ（書かない）。あれば終了コード 1
  python3 tools/fix_problems.py --page lazy-segment-tree   そのページだけ（くり返し・カンマ区切り可。--field より優先）
  python3 tools/fix_problems.py --check --page lazy-segment-tree   そのページだけを検査する（書かない）
  python3 tools/fix_problems.py --field ds       その分野だけ（--page がないときだけ効く）
  python3 tools/fix_problems.py --root DIR       DIR/docs のページを直す（試験用。台帳は --ledger）
--check では、台帳の pages にあるのに本文の囲みにない（問題, ページ）も「警告」として出す（終了コードには入れない）。
終了コード: --check で直すべき行がある、または直せない行がある（ID が読めない・台帳にない・要約がない）と 1

読める行の形（囲みの中の1行）:
  - [ABC300 E. Dice Product 3](https://atcoder.jp/contests/abc300/tasks/abc300_e)（diff 1354）：要約   ← 正しい形
  - [なんでも](https://atcoder.jp/contests/abc300/tasks/abc300_e)：要約                               ← diff がない・label が違う
  - abc300_e：要約                                                                                    ← 問題 ID だけ（書くときの近道）
問題 ID は URL の tasks/<ID> か、行頭の ID から読む。台帳で確認済みでない問題も行は作り直すが、check_pages.py がエラーにする。
フェンス（```）の中は見ない。共通の部品は check_pages.py にある。
"""
from __future__ import annotations

import argparse
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import check_pages as cp  # noqa: E402  （共通の部品）

URL_ID_RE = re.compile(r"https?://atcoder\.jp/contests/[^/\s)]+/tasks/(?P<id>[A-Za-z0-9_]+)")
LINK_TAIL_RE = re.compile(r"^- \[(?:[^\[\]]|\[[^\[\]]*\])*\]\([^)]*\)\s*(?:（diff[^）]*）)?\s*[：:]\s*(?P<summary>.+)$")
BARE_RE = re.compile(r"^- (?P<id>[a-z][A-Za-z0-9_]*_[A-Za-z0-9]+)\s*(?:（diff[^）]*）)?\s*[：:]\s*(?P<summary>.+)$")


def fix_text(text: str, rel: str, ledger: dict[str, dict]) -> tuple[str, list[str], list[str]]:
    """(直した全文, 直した行の説明, 直せない行の説明)。"""
    lines = text.split("\n")
    infence: set[int] = set()
    for a, b, _, _ in cp.fence_spans(lines):
        infence.update(range(a, b + 1))
    changes, problems = [], []
    indent: str | None = None
    for i, raw in enumerate(lines):
        if i in infence:
            continue
        s = raw.strip()
        if indent is None:
            if cp.BLOCK_OPEN_RE.match(s):
                indent = raw[: len(raw) - len(raw.lstrip())]
            continue
        if cp.BLOCK_CLOSE_RE.match(s):
            indent = None
            continue
        if not s or cp.COMMENT_LINE_RE.match(s) or not s.startswith("- "):
            if s and not cp.COMMENT_LINE_RE.match(s):
                problems.append(f"{rel}:{i + 1}: 問題の行でない（- で始まらない）: {s[:60]}")
            continue
        m = cp.PROBLEM_LINE_RE.match(s)
        if m:
            qid, summary = m.group("id"), m.group("summary")
        else:
            u = URL_ID_RE.search(s)
            t = LINK_TAIL_RE.match(s)
            b = BARE_RE.match(s)
            if u and t:
                qid, summary = u.group("id"), t.group("summary")
            elif b:
                qid, summary = b.group("id"), b.group("summary")
            else:
                problems.append(f"{rel}:{i + 1}: 問題 ID か要約が読めない: {s[:80]}")
                continue
        e = ledger.get(qid)
        if e is None:
            problems.append(f"{rel}:{i + 1}: {qid} が台帳にない（台帳に足すのはメインのセッション）")
            continue
        new = indent + cp.problem_line(e, summary.strip())
        if new != raw:
            changes.append(f"{rel}:{i + 1}: {qid}\n    前: {s}\n    後: {new.strip()}")
            lines[i] = new
    if indent is not None:
        problems.append(f"{rel}: 問題の一覧の囲みが閉じていない（</div> がない）")
    return "\n".join(lines), changes, problems


def body_problem_ids(text: str) -> set[str]:
    """本文の問題の一覧の囲みに載る問題 ID の集合（フェンスの中は見ない）。"""
    lines = text.split("\n")
    infence: set[int] = set()
    for a, b, _, _ in cp.fence_spans(lines):
        infence.update(range(a, b + 1))
    ids: set[str] = set()
    inside = False
    for i, raw in enumerate(lines):
        if i in infence:
            continue
        s = raw.strip()
        if not inside:
            inside = bool(cp.BLOCK_OPEN_RE.match(s))
            continue
        if cp.BLOCK_CLOSE_RE.match(s):
            inside = False
            continue
        u = URL_ID_RE.search(s)
        b = BARE_RE.match(s)
        if u:
            ids.add(u.group("id"))
        elif b:
            ids.add(b.group("id"))
    return ids


def ledger_not_in_body(targets: list, ledger: dict[str, dict]) -> list[str]:
    """台帳の pages にあるのに、そのページの本文の問題の囲みにない（問題, ページ）の説明。status が確認済みでない問題は数えない
    （逆向きの検査。b5/summary/other.md の提案）。見たページの分だけ調べる。"""
    by_page = {p.id: p for p in targets if getattr(p, "id", None)}
    body = {pid: body_problem_ids(p.text) for pid, p in by_page.items()}
    out = []
    for qid, e in sorted(ledger.items()):
        if e.get("status") != cp.CONFIRMED:
            continue
        for ref in e.get("pages") or []:
            pid = ref.get("id") if isinstance(ref, dict) else None
            if pid in body and qid not in body[pid]:
                out.append(f"{by_page[pid].rel}: {qid}（台帳の役割 {ref.get('role')}）が本文の問題の囲みにない"
                           "（本文に足すか、台帳の pages から外す）")
    return out


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--check", action="store_true", help="直すべき行を出すだけ（書かない）")
    parser.add_argument("--page", action="append", default=[], help="そのページだけ（id かパス。くり返し・カンマ区切り可）")
    parser.add_argument("--field", choices=cp.FIELDS, action="append", default=[], help="その分野だけ（--page があるときは使わない）")
    parser.add_argument("--root", type=Path, default=cp.ROOT, help="docs/ のある場所（既定はリポジトリ）")
    parser.add_argument("--ledger", type=Path, default=cp.LEDGER_PATH, help="問題の台帳（既定は data/problems.yaml）")
    args = parser.parse_args()

    docs = args.root / "docs"
    if not docs.is_dir():
        sys.exit(f"{docs} がない")
    ledger = cp.load_ledger(args.ledger)
    pages, others = cp.load_docs(docs)
    targets = pages + others
    wanted = [x.strip() for v in args.page for x in v.split(",") if x.strip()]
    if wanted:
        # --page があれば --field は見ない（決定 D1・D2：執筆者はそのページだけを直す・検査する）
        missing = [x for x in wanted if not any(x in (p.id, p.rel, f"docs/{p.rel}") for p in targets)]
        if missing:
            sys.exit("そのページがない: " + ", ".join(missing))
        if args.field:
            print("注意: --page があるので --field は使わない", file=sys.stderr)
        targets = [p for p in targets if any(x in (p.id, p.rel, f"docs/{p.rel}") for x in wanted)]
    elif args.field:
        targets = [p for p in targets if p.dir_field in args.field]

    n_changes, n_files, all_problems = 0, 0, []
    for p in targets:
        text, changes, problems = fix_text(p.text, p.rel, ledger)
        all_problems += problems
        if not changes:
            continue
        n_changes += len(changes)
        n_files += 1
        for c in changes:
            print(("直すべき行 " if args.check else "直した行 ") + c)
        if not args.check:
            p.path.write_text(text, encoding="utf-8")
    for pr in all_problems:
        print("直せない: " + pr)
    reverse = ledger_not_in_body(targets, ledger) if args.check else []
    for w in reverse:
        print("警告: " + w)
    verb = "直すべき行" if args.check else "直した行"
    tail = f"・台帳にあって本文にない（警告）: {len(reverse)}" if args.check else ""
    print(f"\n{verb}: {n_changes}（{n_files} ファイル）・直せない行: {len(all_problems)}{tail}（見たページ {len(targets)}）")
    sys.exit(1 if all_problems or (args.check and n_changes) else 0)


if __name__ == "__main__":
    main()
