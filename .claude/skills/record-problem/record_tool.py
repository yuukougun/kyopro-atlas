#!/usr/bin/env python3
"""記録用スキル /record-problem の補助。読むだけで、ファイルは書かない。

リポジトリの根で実行する:
  python3 .claude/skills/record-problem/record_tool.py pages [語 ...] [--problem ID] [--limit 20]
      関連ページの候補。docs/ の各ページの front matter の id・題名・別名・節の題名に語を含むものを出す。
      docs/ にまだないページは planning/catalog/*.yaml から補う（段階の欄が「目次のみ」）。
      --problem を付けると、台帳（data/problems.yaml・data/recent-abc.yaml）でその問題に結び付いたページを先に出す
  python3 .claude/skills/record-problem/record_tool.py url ID[#anchor] [...]
      ページ（節）の id を確かめて公開 URL を出す。ページの URL を渡してもよい。見つからなければ終了コード 1
  python3 .claude/skills/record-problem/record_tool.py check notes/<問題ID>.md
      記録のファイル（形は SKILL.md）の front matter と本文の節を確かめる。問題があれば終了コード 1
"""
from __future__ import annotations

import argparse
import datetime
import re
import sys
import unicodedata
from pathlib import Path

try:
    import yaml
except ImportError:
    sys.exit("PyYAML がない。`uv run python3 …` で実行するか、python3-yaml を入れる")

ROOT = Path(__file__).resolve().parents[3]
SITE_URL = "https://yuukougun.github.io/kyopro-atlas/"  # mkdocs.yml に site_url があればそちらを使う
CAUSES = ("知識不足", "気づけなかった", "実装ミス", "時間不足")
RECORD_KEYS = ("date", "cause", "learned", "pages", "improvement")
LOADER = getattr(yaml, "CSafeLoader", yaml.SafeLoader)
FRONT = re.compile(r"\A---[ \t]*\r?\n(.*?)^---[ \t]*\r?$", re.S | re.M)


def load_yaml(text: str):
    return yaml.load(text, Loader=LOADER)


def site_url() -> str:
    try:
        text = (ROOT / "mkdocs.yml").read_text(encoding="utf-8")
    except OSError:
        text = ""
    m = re.search(r"^site_url:\s*['\"]?([^'\"\s]+)", text, re.M)
    return (m.group(1) if m else SITE_URL).rstrip("/") + "/"


def front_matter(text: str) -> dict | None:
    m = FRONT.match(text)
    if not m:
        return None
    data = load_yaml(m.group(1))
    return data if isinstance(data, dict) else None


def entry(d: dict, field: object, stage: object) -> dict:
    return {
        "id": d["id"],
        "title": str(d.get("title") or ""),
        "nav_title": d.get("nav_title"),
        "aliases": [str(a) for a in d.get("aliases") or []],
        "field": field,
        "level": d.get("level"),
        "stage": stage,
        "sections": [s for s in d.get("sections") or [] if isinstance(s, dict) and s.get("anchor")],
    }


def load_pages() -> tuple[dict[str, dict], int]:
    """id → ページ。docs/ のページの front matter を正とし、docs/ にないものを catalog から補う。"""
    pages: dict[str, dict] = {}
    for path in sorted((ROOT / "docs").glob("*/*.md")):
        try:
            fm = front_matter(path.read_text(encoding="utf-8"))
        except (yaml.YAMLError, UnicodeDecodeError) as e:
            print(f"警告  {path.relative_to(ROOT)} の front matter が読めない（{e.__class__.__name__}）", file=sys.stderr)
            continue
        # 生成した一覧・索引を除き、docs/<field>/<id>.md のページ（stage を持つ）だけを読む
        if fm and fm.get("id") == path.stem and fm.get("field") == path.parent.name and "stage" in fm:
            pages[path.stem] = entry(fm, fm["field"], fm.get("stage") or "?")
    n_docs = len(pages)
    for path in sorted((ROOT / "planning" / "catalog").glob("*.yaml")):
        data = load_yaml(path.read_text(encoding="utf-8")) or {}
        for p in data.get("pages") or []:
            if isinstance(p, dict) and isinstance(p.get("id"), str) and p["id"] not in pages:
                pages[p["id"]] = entry(p, data.get("field"), "目次のみ")
    return pages, n_docs


def norm(s: object) -> str:
    return unicodedata.normalize("NFKC", str(s)).casefold()


def split_ref(ref: str) -> tuple[str, str]:
    """`id`・`id#anchor`・ページの URL を (id, anchor) にする。"""
    ref = ref.strip()
    if "://" in ref:
        path, _, anchor = ref.partition("#")
        parts = [x for x in path.split("/") if x]
        return (parts[-1] if parts else ""), anchor
    pid, _, anchor = ref.partition("#")
    return pid, anchor


def resolve(pages: dict[str, dict], ref: str, base: str) -> tuple[str | None, str]:
    """(1行, エラー)。1行は「id[#anchor]・題名・分野・レベル・段階・URL」をタブで区切ったもの。"""
    pid, anchor = split_ref(ref)
    p = pages.get(pid)
    if p is None:
        return None, "ページがない（pages で候補を探す）"
    url = f"{base}{p['field']}/{pid}/"
    if not anchor:
        return f"{pid}\t{p['title']}\t{p['field']}・{p['level'] or '-'}・{p['stage']}\t{url}", ""
    for s in p["sections"]:
        if s["anchor"] == anchor:
            level = s.get("level") or p["level"] or "-"
            return f"{pid}#{anchor}\t{p['title']} > {s.get('title', '')}\t{p['field']}・{level}・{p['stage']}\t{url}#{anchor}", ""
    return None, f"節 #{anchor} がない（ページ {pid} は {url}）"


def linked_refs(pid: str) -> list[str]:
    """台帳と最近の ABC のデータで、問題に結び付いたページ（id か id#anchor）。"""
    refs: list[str] = []
    for name in ("problems.yaml", "recent-abc.yaml"):
        path = ROOT / "data" / name
        if not path.exists():
            continue
        for item in (load_yaml(path.read_text(encoding="utf-8")) or {}).get("problems") or []:
            if isinstance(item, dict) and item.get("id") == pid:
                for x in item.get("pages") or []:
                    ref = x.get("id") if isinstance(x, dict) else x
                    if isinstance(ref, str) and ref not in refs:
                        refs.append(ref)
    return refs


def cmd_pages(terms: list[str], problem: str | None, limit: int) -> int:
    pages, n_docs = load_pages()
    base = site_url()
    out: list[str] = []
    seen: set[str] = set()
    for ref in linked_refs(problem) if problem else []:
        line, _ = resolve(pages, ref, base)
        if line:
            out.append(f"{line}\t台帳（{problem}）")
            seen.add(line.split("\t", 1)[0])
    raw = [unicodedata.normalize("NFKC", t.strip()) for t in terms if t.strip()]
    qs = [q.casefold() for q in raw]
    hits = []
    for order, p in enumerate(pages.values()):
        names_raw = [unicodedata.normalize("NFKC", str(x)) for x in (p["id"], p["title"], p["nav_title"] or "", *p["aliases"])]
        names = [n.casefold() for n in names_raw]
        score = sum(any(q in n for n in names) for q in qs)
        if score and p["id"] not in seen:
            exact = any(q in names for q in qs)  # id・題名・別名のどれかにそのまま一致
            cased = any(q in n for q in raw for n in names_raw)  # 大文字・小文字まで一致（BIT と bit を分ける）
            line, _ = resolve(pages, p["id"], base)
            hits.append((-score - exact - cased / 2, 0, order, f"{line}\t別名: {', '.join(p['aliases']) or '-'}"))
        for s in p["sections"]:
            ref = f"{p['id']}#{s['anchor']}"
            score = sum(q in norm(f"{s.get('title', '')} {s['anchor']}") for q in qs)
            if score and ref not in seen:
                line, _ = resolve(pages, ref, base)
                hits.append((-score, 1, order, f"{line}\t節"))
    hits.sort(key=lambda h: h[:3])
    out += [h[3] for h in hits]
    for line in out[:limit]:
        print(line)
    shown = f"{len(out)} 件" if len(out) <= limit else f"{len(out)} 件のうち {limit} 件（--limit で増やせる）"
    print(f"（{shown}。docs/ のページ {n_docs}・目次のみ {len(pages) - n_docs}）", file=sys.stderr)
    return 0 if out else 1


def cmd_url(refs: list[str]) -> int:
    pages, _ = load_pages()
    base = site_url()
    ng = 0
    for ref in refs:
        line, err = resolve(pages, ref, base)
        if line:
            print(f"OK  {line}")
        else:
            ng += 1
            print(f"NG  {ref}\t{err}", file=sys.stderr)
    return 1 if ng else 0


def cmd_check(path: Path) -> int:
    try:
        text = path.read_text(encoding="utf-8")
    except OSError as e:
        print(f"NG  {path}：読めない（{e.strerror}）")
        return 1
    errors: list[str] = []
    try:
        fm = front_matter(text)
        if fm is None:
            errors.append("先頭に front matter（--- の行で囲んだ YAML）がない")
    except yaml.YAMLError as e:
        fm = None
        errors.append("front matter の YAML が読めない：" + " ".join(str(e).split()))
    if fm is None:  # 中身を確かめられないので、ここで止める
        print(f"NG  {path}：{errors[0]}")
        return 1
    pid = fm.get("problem")
    if pid != path.stem:
        errors.append(f"problem（{pid}）がファイル名（{path.stem}）と違う")
    for key in ("contest", "title"):
        if not isinstance(fm.get(key), str) or not fm[key].strip():
            errors.append(f"{key} がない")
    if not re.fullmatch(rf"https://atcoder\.jp/contests/[\w-]+/tasks/{re.escape(str(pid))}", str(fm.get("url"))):
        errors.append("url が https://atcoder.jp/contests/<コンテスト>/tasks/<問題ID> の形でない")
    d = fm.get("difficulty")
    if d != "未定" and (isinstance(d, bool) or not isinstance(d, int)):
        errors.append("difficulty は整数か「未定」")
    records = fm.get("records")
    if not isinstance(records, list) or not records:
        errors.append("records（記録の列）がない")
        records = []
    base = site_url()
    for i, r in enumerate(records, 1):
        at = f"records の {i} 件目"
        if not isinstance(r, dict):
            errors.append(f"{at}が「項目: 値」の形でない")
            continue
        missing = [k for k in RECORD_KEYS if k not in r]
        if missing:
            errors.append(f"{at}に {'・'.join(missing)} がない（ないときも null か [] を書く）")
        date = r.get("date")
        if not isinstance(date, datetime.date) and not (isinstance(date, str) and re.fullmatch(r"\d{4}-\d{2}-\d{2}", date)):
            errors.append(f"{at}：date は YYYY-MM-DD")
        elif not re.search(rf"^## {re.escape(str(date))}", text, re.M):
            errors.append(f"{at}：本文に「## {date}」で始まる節がない")
        if r.get("cause") is not None and r.get("cause") not in CAUSES:
            errors.append(f"{at}：cause は {'・'.join(CAUSES)} のどれかか null")
        if not isinstance(r.get("learned"), str) or not r["learned"].strip():
            errors.append(f"{at}：learned（学んだことを一言）がない")
        links = r.get("pages", [])
        if not isinstance(links, list) or not all(
            isinstance(x, dict) and isinstance(x.get("id"), str) and str(x.get("url", "")).startswith(base) for x in links
        ):
            errors.append(f"{at}：pages は id と url の組の列（url は {base} で始まる。ないときは []）")
        if r.get("improvement") is not None and not isinstance(r.get("improvement"), str):
            errors.append(f"{at}：improvement は文字列か null")
    for e in errors:
        print(f"NG  {path}：{e}")
    if not errors:
        print(f"OK  {path}（記録 {len(records)} 件）")
    return 1 if errors else 0


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest="cmd", required=True)
    p = sub.add_parser("pages")
    p.add_argument("terms", nargs="*")
    p.add_argument("--problem")
    p.add_argument("--limit", type=int, default=20)
    u = sub.add_parser("url")
    u.add_argument("refs", nargs="+")
    c = sub.add_parser("check")
    c.add_argument("file")
    args = ap.parse_args()
    if args.cmd == "pages":
        if not args.terms and not args.problem:
            ap.error("語か --problem を渡す")
        return cmd_pages(args.terms, args.problem, args.limit)
    if args.cmd == "url":
        return cmd_url(args.refs)
    return cmd_check(Path(args.file))


if __name__ == "__main__":
    sys.exit(main())
