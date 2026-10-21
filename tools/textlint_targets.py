#!/usr/bin/env python3
"""textlint で検査する Markdown の一覧を出す（package.json の lint:text が使う）。

対象は docs/ の手書きの Markdown のうち、stage が stub（準備中）でないもの。
生成物（lists/・index/・各分野の index.md）は除く。準備中のページの要点は目次の要約を写しただけで、
本文を書くときに書き直すので検査しない（planning/batches/pilot.md）。
"""
import re
import sys
from pathlib import Path

DOCS = Path(__file__).resolve().parent.parent / "docs"
STAGE_RE = re.compile(r"^stage:\s*(\S+)", re.M)

for path in sorted(DOCS.rglob("*.md")):
    rel = path.relative_to(DOCS)
    if rel.parts[0] in {"lists", "index"} or (len(rel.parts) == 2 and rel.name == "index.md"):
        continue
    text = path.read_text(encoding="utf-8")
    fm = text.split("---", 2)[1] if text.startswith("---") else ""
    m = STAGE_RE.search(fm)
    if m and m.group(1) == "stub":
        continue
    print(path.relative_to(DOCS.parent))
