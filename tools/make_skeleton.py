#!/usr/bin/env python3
"""catalog（planning/catalog/*.yaml）から骨格のページ（stage: stub）を docs/<field>/<id>.md に作る（工程8a。design-review T6・T13）。

使い方:
  python3 tools/make_skeleton.py                       catalog の全ページの骨格を docs/ に作る（あるページは上書きしない）
  python3 tools/make_skeleton.py --ids lazy-segment-tree,segment-tree   一部だけ（くり返しもよい）
  python3 tools/make_skeleton.py --field ds            その分野だけ
  python3 tools/make_skeleton.py --out DIR             DIR/<field>/<id>.md に作る（試験用。既定は docs）
  python3 tools/make_skeleton.py --force               あるページも上書きする（書いた本文が消えるので注意）
  python3 tools/make_skeleton.py --dry-run             書かずに、作る・飛ばすページを出す
  python3 tools/make_skeleton.py --date 2026-10-21     updated の日付（既定は実行した日）
  python3 tools/make_skeleton.py --gen-markers         生成部分を持つ横断ページ（逆引き・用語の索引・ロードマップなど）に、
                                                       gen_site.py の目印だけを足す（試験用。interfaces.md §2 の骨格は要点だけ）
終了コード: catalog に知らない id を指定した・作ったページが schema に合わない・書けないときは 1

front matter（interfaces.md §2）: catalog の項目のうち id・title・nav_title・aliases・type・chapter・level・kind・
prerequisites・related・summary・signs・acl・verify・frequency・frequency_evidence・sections・cpp_std・gcc_min・atcoder を
catalog にあるものだけ写し、field（ファイルの分野）・order（ファイルの中の並びから 10 刻み）・complexity: null・
stage: stub・updated（実行日）を足す。level_evidence・merged_keys・visual・problems・problems_note・sources は写さない
（catalog に残る執筆の指示。T10）。
本文（interfaces.md §4）: 要点の囲みだけ。「何ができるか」に summary、「いつ使うか」に signs、「前提」に prerequisites
（ページへのリンク）を入れ、計算量は「（執筆時に書く）」。guide・hub・pattern は「何のページか」「使い方」にする。
新しい事実は書かない（T13）。作ったページは schema/page.schema.json で検査してから書く。
"""
from __future__ import annotations

import argparse
import datetime
import sys
from pathlib import Path

import yaml

sys.path.insert(0, str(Path(__file__).resolve().parent))
import check_pages as cp  # noqa: E402  （共通の部品）

CATALOG = cp.ROOT / "planning" / "catalog"
COPY_KEYS = ["id", "title", "nav_title", "aliases", "type", "field", "chapter", "order", "level", "kind", "prerequisites",
             "related", "summary", "complexity", "signs", "acl", "verify", "frequency", "frequency_evidence", "sections",
             "stage", "updated", "cpp_std", "gcc_min", "atcoder"]
OPTIONAL_NULL = {"nav_title", "chapter"}            # catalog で null・空なら書かない（interfaces.md §2：任意・省く）

# gen_site.py の生成部分の目印を置くページ（--gen-markers。名前は gen_site.py の BLOCKS と同じ）
GEN_MARKERS = {
    "reverse-index-signs": ["signs-phrase", "signs-shape"],
    "reverse-index-constraints": ["signs-constraint"],
    "term-index": ["terms-kana", "terms-latin", "terms-shared"],
    "roadmap": ["recent-positions", "roadmap-order"],
    "problem-sets": ["recent-abc", "problem-sets"],
    "library-design": ["verify-table"],
}


class Dumper(yaml.SafeDumper):
    """リストを親のキーより2字下げて書く（interfaces.md §2 の例の見た目）。"""

    def increase_indent(self, flow=False, indentless=False):  # noqa: ANN001
        return super().increase_indent(flow, False)

    def ignore_aliases(self, data):  # noqa: ANN001
        return True


def load_catalog() -> list[dict]:
    out = []
    for f in cp.FIELDS:
        path = CATALOG / f"{f}.yaml"
        if not path.exists():
            continue
        doc = yaml.safe_load(path.read_text(encoding="utf-8")) or {}
        for i, p in enumerate(doc.get("pages") or []):
            if isinstance(p, dict) and isinstance(p.get("id"), str):
                out.append({**p, "_field": f, "_order": (i + 1) * 10})
    return out


def front_matter(p: dict, date: datetime.date) -> dict:
    src = {**p, "field": p["_field"], "order": p["_order"], "complexity": None, "stage": "stub", "updated": date}
    fm = {}
    for k in COPY_KEYS:
        if k not in src:
            continue
        v = src[k]
        if k in OPTIONAL_NULL and v in (None, ""):
            continue
        if k == "signs":
            v = [{"type": s.get("type"), "text": s.get("text")} for s in v or [] if isinstance(s, dict)]
        elif k == "sections":
            v = [{x: s[x] for x in ("title", "anchor", "level") if s.get(x) is not None} for s in v or [] if isinstance(s, dict)]
        fm[k] = v
    return fm


def dump_front_matter(fm: dict) -> str:
    body = yaml.dump(fm, Dumper=Dumper, allow_unicode=True, sort_keys=False, width=10 ** 9, default_flow_style=None)
    return "---\n" + body + "---\n"


def abstract(p: dict, titles: dict[str, tuple[str, str]]) -> str:
    """要点の囲み（interfaces.md §4）。"""
    t = p.get("type")
    signs = [s.get("text") for s in p.get("signs") or [] if isinstance(s, dict) and s.get("text")]
    pre = []
    for r in p.get("prerequisites") or []:
        if r in titles:
            title, field = titles[r]
            pre.append(f"[{cp.md_text(title)}](../{field}/{r}.md)")
        else:
            pre.append(cp.md_text(r))

    def item(label: str, values: list[str] | None, text: str | None = None) -> list[str]:
        if text is not None:
            return [f"    - **{label}**：{text}"]
        if not values:
            return [f"    - **{label}**：{cp.PLACEHOLDER}"]
        if len(values) == 1:
            return [f"    - **{label}**：{cp.md_text(values[0])}"]
        return [f"    - **{label}**："] + [f"        - {cp.md_text(v)}" for v in values]

    lines = ['!!! abstract "要点"']
    summary = cp.md_text(p.get("summary") or "") or cp.PLACEHOLDER
    if t in ("guide", "hub", "pattern"):
        lines += item("何のページか", None, summary)
        if signs:
            lines += item("いつ使うか", signs)
        lines += item("使い方", None, cp.PLACEHOLDER)
        if pre:
            lines += item("前提", None, "、".join(pre))
    else:
        lines += item("何ができるか", None, summary)
        lines += item("いつ使うか", signs)
        lines += item("計算量", None, cp.PLACEHOLDER)
        lines += item("前提", None, "、".join(pre) if pre else "なし")
    return "\n".join(lines) + "\n"


def page_text(p: dict, date: datetime.date, titles: dict[str, tuple[str, str]], markers: bool) -> tuple[str, dict]:
    fm = front_matter(p, date)
    text = dump_front_matter(fm) + "\n" + abstract(p, titles)
    if markers:
        for name in GEN_MARKERS.get(p["id"], []):
            text += f"\n<!-- gen:begin {name} -->\n<!-- gen:end {name} -->\n"
    return text, fm


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--ids", action="append", default=[], help="作るページの id（カンマ区切り・くり返し）")
    parser.add_argument("--field", choices=cp.FIELDS, action="append", default=[], help="その分野のページだけ（くり返し可）")
    parser.add_argument("--out", type=Path, default=cp.ROOT / "docs", help="出力先（既定は docs）")
    parser.add_argument("--force", action="store_true", help="あるページも上書きする")
    parser.add_argument("--dry-run", action="store_true", help="書かずに、作る・飛ばすページを出す")
    parser.add_argument("--date", type=datetime.date.fromisoformat, default=datetime.date.today(), help="updated（既定は今日）")
    parser.add_argument("--gen-markers", action="store_true", help="横断ページに gen_site.py の目印を足す（試験用）")
    args = parser.parse_args()

    catalog = load_catalog()
    by_id = {p["id"]: p for p in catalog}
    titles = {p["id"]: (p.get("title") or p["id"], p["_field"]) for p in catalog}
    want = [x.strip() for v in args.ids for x in v.split(",") if x.strip()]
    unknown = [x for x in want if x not in by_id]
    if unknown:
        sys.exit("catalog にない id: " + ", ".join(unknown))
    targets = [p for p in catalog if (not want or p["id"] in want) and (not args.field or p["_field"] in args.field)]

    validator = cp.load_validator()
    made, skipped, bad = [], [], []
    for p in targets:
        path = args.out / p["_field"] / f"{p['id']}.md"
        text, fm = page_text(p, args.date, titles, args.gen_markers)
        errs = validator.errors(cp.plain(fm))
        if errs:
            bad.append((p["id"], errs))
            continue
        elsewhere = [x for x in args.out.glob(f"*/{p['id']}.md") if x != path] if args.out.is_dir() else []
        if elsewhere:
            print(f"注意: {p['id']} は {', '.join(str(x) for x in elsewhere)} にもある（分野を移したなら古い方を消す）")
        if path.exists() and not args.force:
            skipped.append(path)
            continue
        made.append(path)
        if not args.dry_run:
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_text(text, encoding="utf-8")
    verb = "作る" if args.dry_run else "作った"
    print(f"{verb}: {len(made)} ページ（出力先 {args.out}）")
    if skipped:
        print(f"飛ばした（もうある。上書きは --force）: {len(skipped)} ページ: " + ", ".join(x.stem for x in skipped[:10])
              + ("…" if len(skipped) > 10 else ""))
    for pid, errs in bad:
        print(f"schema に合わないので書かなかった: {pid}: " + "; ".join(f"{a}: {b}" for a, b in errs))
    sys.exit(1 if bad else 0)


if __name__ == "__main__":
    main()
