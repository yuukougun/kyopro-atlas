#!/usr/bin/env python3
"""本文に取り込んだコード片の下に、GitHub の完全なプログラムへのリンクの行を置き、地の文の `snippets/…` をリンクにする
（Issue #8・#72・#62。考え方は fix_problems.py と同じで、行は道具が決まった形で作る。手で書かない）。

使い方:
  python3 tools/fix_code_links.py                 全ページを直す（変わったファイルだけ書く）
  python3 tools/fix_code_links.py --check         直すべき差分（unified diff）を出すだけ（書かない）。あれば終了コード 1
  python3 tools/fix_code_links.py --check --stat  差分の代わりに、ファイルごとの件数だけを出す
  python3 tools/fix_code_links.py --page hld      そのページだけ（id かパス。くり返し・カンマ区切り可。--field より優先）
  python3 tools/fix_code_links.py --field ds      その分野だけ（--page がないときだけ効く）
  python3 tools/fix_code_links.py --root DIR      DIR/docs のページを直す（試験用。コード片は DIR/snippets、なければ
                                                  リポジトリの snippets/。--snippets で変えられる）
終了コード: --check で直すべきところがある、または直せないところがある（取り込むファイルや範囲がない、mint の型が読めない、
リンクにできない言及）と 1

1. コードの下の行（#8・#62）
   ```cpp（c++・cxx・cc・hpp・h も）のフェンスの中の取り込み --8<-- "<id>/<名前>:<範囲>" を見つけ、閉じのフェンスの後に
   空行を 1 つ置いて、次の 2 行の段落を置く（字下げはフェンスの開きに合わせるので、折りたたみ・囲み・タブ・箇条書きの中でも
   同じ入れ物に入る。空行がないと、Python-Markdown はコードの塊ごと段落に入れてしまう）。

       完全なプログラム：[`binom.cpp`](https://github.com/yuukougun/kyopro-atlas/blob/main/snippets/binomial-precompute/binom.cpp)（GitHub）
       { .kp-code-src }

   - 取り込む範囲（[start:名前]〜[end:名前]、行の範囲、ファイル全体。pymdownx.snippets と同じ切り出し方）に `mint` が出れば、
     同じ行に「。`mint` は ACL の `modint998244353`（[modint](../math/modint.md)）。」を足す。型はファイルの
     `using mint = …;` から読む（atcoder:: を外す。ACL の型でなければ「ACL の」を付けない）。modint のページ自身には付けない
   - 同じファイルを続けて取り込むとき：空行だけを挟んで続き、字下げが同じで、取り込むファイルの組が同じフェンスは
     1 つの続きとみなし、最後のフェンスの下にだけ行を置く。地の文などを挟めば、それぞれのフェンスの下に置く
     （節だけを読まれても、各コードの近くにリンクがあるように）。1 つのフェンスで同じファイルを 2 回取り込んでもリンクは 1 つ
   - 2 行目は attr_list の class（見た目は kp.css の .kp-code-src。p 要素に付く）。この 2 行の形の段落は道具のものとみなし、
     毎回作り直す（ファイル名の変更・mint の有無の変化・不要になった行の削除も追う）
   - HTML のコメントの中のフェンスと、; でエスケープした取り込みは見ない
2. 地の文の言及（#72）
   フェンス・HTML のコメント・$$ の数式ブロックの外で、行の中のコード `snippets/<id>/<名前>` を、同じ URL へのリンク
   [`snippets/<id>/<名前>`](https://github.com/…/blob/main/snippets/<id>/<名前>) にする（フォルダと `snippets/` だけなら
   …/tree/main/…）。
   リンクの文字の中のものはそのまま（[`snippets/…`](このリポジトリの GitHub の URL) の形なら、URL を作り直し、先のファイルが
   なければ「直せない」に出す）。見出しの中・コメントのある行の中・ないファイルは直さず「直せない」に出す

依存は PyYAML だけ（共通の部品は check_pages.py）。MkDocs は import しない。
"""
from __future__ import annotations

import argparse
import difflib
import posixpath
import re
import sys
import urllib.parse
from dataclasses import dataclass, field
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import check_pages as cp  # noqa: E402  （共通の部品）

REPO_URL = "https://github.com/yuukougun/kyopro-atlas"
BRANCH = "main"
LINE_PREFIX = "完全なプログラム："
LINE_CLASS = "kp-code-src"
CLASS_LINE = "{ .%s }" % LINE_CLASS
CLASS_LINE_RE = re.compile(r"^\{:?[ ]*\.%s[ ]*\}$" % re.escape(LINE_CLASS))
MODINT_REL = "math/modint.md"
CPP_LANGS = {"cpp", "c++", "cxx", "cc", "hpp", "h"}
CLOSE_FENCE_RE = re.compile(r"^[ \t]*(`{3,}|~{3,})\s*$")
MINT_RE = re.compile(r"\bmint\b")
MINT_DEF_RES = [re.compile(r"^\s*using\s+mint\s*=\s*(?P<t>[^;]+?)\s*;"),
                re.compile(r"^\s*typedef\s+(?P<t>[^;]+?)\s+mint\s*;")]
ACL_MODINT_RE = re.compile(r"(?:(?:::)?atcoder::)?(?P<name>modint998244353|modint1000000007|modint"
                           r"|static_modint<[^<>]+>|dynamic_modint<[^<>]+>)")
MENTION_RE = re.compile(r"^snippets/(?P<path>(?:[A-Za-z0-9._-]+(?:/[A-Za-z0-9._-]+)*)?)/?$")
# pymdownx.snippets（10.x）の切り出しと同じ形（RE_SNIPPET_SECTION・RE_SNIPPET_FILE）
SECTION_MARK_RE = re.compile(
    r"(?i)^(?P<pre>.*?)(?P<escape>;*)(?P<inline_marker>-{1,}8<-{1,}[ \t]+)"
    r"(?P<section>\[[ \t]*(?P<type>start|end)[ \t]*:[ \t]*(?P<name>[a-z][-_0-9a-z]*)[ \t]*\])(?P<post>.*?)$")
FILE_SPEC_RE = re.compile(
    r"(?i)(.*?)(?:((?::-?[0-9]*){1,2}(?:(?:,(?=[-0-9:])-?[0-9]*)(?::-?[0-9]*)?)*)|(:[a-z][-_0-9a-z]*))?$")


# ---------------------------------------------------------------- コード片の読み取り

def file_url(path: str, is_dir: bool = False) -> str:
    """snippets/ からの相対パスの GitHub の URL（空なら snippets/ のフォルダ）。"""
    url = f"{REPO_URL}/{'tree' if is_dir or not path.strip('/') else 'blob'}/{BRANCH}/snippets"
    return url + ("/" + urllib.parse.quote(path.strip("/"), safe="/") if path.strip("/") else "")


def split_ref(ref: str) -> tuple[str, list[tuple[int | None, int | None]] | None, str | None]:
    """取り込みの指定 "<パス>:<範囲>" を (パス, 行の範囲の列か None, 範囲の名前か None) に分ける（pymdownx.snippets と同じ）。"""
    m = FILE_SPEC_RE.match(ref.strip())
    path = m.group(1).strip() if m else ref.strip()
    if m and m.group(2):
        ranges = []
        for nums in m.group(2)[1:].split(","):
            span = nums.split(":")
            st = int(span[0]) if span[0] else None
            en = int(span[1]) if len(span) > 1 and span[1] else None
            ranges.append((st if st is None or st < 0 else max(0, st - 1), en))
        return path, ranges, None
    if m and m.group(3):
        return path, None, m.group(3)[1:]
    return path, None, None


def read_lines(f: Path) -> list[str]:
    """pymdownx.snippets と同じ行の分け方（改行で終わるファイルは最後に空の行が付く）。"""
    text = f.read_text(encoding="utf-8", errors="replace")
    lines = text.splitlines()
    if text.endswith(("\n", "\r")):
        lines.append("")
    return lines


def shown_lines(f: Path, ranges, section: str | None) -> list[str] | None:
    """サイトに出る行（範囲の名前がファイルになければ None）。"""
    lines = read_lines(f)
    if ranges:
        total, out = len(lines), []
        for st, en in ranges:
            s = min(max(total + st, 0), total) if st and st < 0 else st
            e = min(max(total + 1 + en, 0), total) if en and en < 0 else en
            out.extend(lines[s:e])
        return out
    if not section:
        return [x for x in lines if not (SECTION_MARK_RE.match(x) and not SECTION_MARK_RE.match(x).group("escape"))]
    out, start, found = [], False, False
    for x in lines:
        m = SECTION_MARK_RE.match(x)
        if m and start and m.group("escape"):
            pass
        elif m and m.group("name") == section:
            if not start and m.group("type") == "start":
                start = found = True
                continue
            if start and m.group("type") == "start":
                continue
            break                       # 終わり（か、始まりのない終わり）
        elif m and start:
            continue                    # ほかの範囲の目印は出ない
        if start:
            out.append(x)
    return out if found else None


def mint_types(f: Path) -> list[str]:
    """ファイルの `using mint = …;`（typedef も）の型の列（重なりを除き、空白を詰める）。"""
    out: list[str] = []
    for x in read_lines(f):
        for rx in MINT_DEF_RES:
            if m := rx.match(x):
                t = re.sub(r"\s+", "", m.group("t"))
                if t not in out:
                    out.append(t)
    return out


def page_link(host_rel: str, target_rel: str) -> str:
    """ページへの相対リンク。docs/<field>/ のページからは手引き §7 の形 ../<field>/<id>.md（同じ分野でも）にする。"""
    return "../" + target_rel if host_rel.count("/") == 1 else cp.rel_link(host_rel, target_rel)


def mint_note(t: str, host_rel: str, modint_title: str) -> str:
    m = ACL_MODINT_RE.fullmatch(t)
    name, acl = (m.group("name"), "ACL の ") if m else (t, "")
    return f"`mint` は {acl}`{name}`（[{cp.md_text(modint_title)}]({page_link(host_rel, MODINT_REL)})）。"


# ---------------------------------------------------------------- 1 ページの直し

@dataclass
class Fence:
    start: int                      # 開きの行（本文の行の番号、0 始まり）
    end: int                        # 閉じの行
    indent: str
    refs: list[tuple[int, str]]     # (行, 取り込みの指定)
    files: list[str] = field(default_factory=list)
    mint: list[str] = field(default_factory=list)    # 取り込む範囲に出る mint の型


@dataclass
class Result:
    text: str
    added: int = 0
    updated: int = 0
    removed: int = 0
    lines: int = 0                  # 置いた行（mint の注記つきは notes）
    notes: int = 0
    fences: int = 0                 # 取り込みのある ```cpp
    mentions: int = 0               # リンクにした地の文の言及
    problems: list[str] = field(default_factory=list)


def is_generated(lines: list[str], i: int) -> bool:
    return (i + 1 < len(lines) and lines[i].lstrip().startswith(LINE_PREFIX)
            and CLASS_LINE_RE.match(lines[i + 1].strip()) is not None)


def comment_lines(lines: list[str], spans) -> set[int]:
    """HTML のコメント（<!-- … -->）の中の行（フェンスの中の <!-- は見ない）。"""
    fence_at = {a: b for a, b, _, _ in spans}
    out, inside, i = set(), False, 0
    while i < len(lines):
        if not inside and i in fence_at:
            i = fence_at[i] + 1
            continue
        s = lines[i]
        if inside:
            out.add(i)
            if "-->" in s:
                inside = False
                s = s.split("-->", 1)[1]
            else:
                i += 1
                continue
        s = re.sub(r"<!--.*?-->", "", s)
        if "<!--" in s:
            inside = True
        i += 1
    return out


def fence_refs(lines: list[str], a: int, b: int) -> list[tuple[int, str]]:
    """フェンスの中の取り込み（1 行の形と、--8<-- の行で挟んだ形。; で始まる行はエスケープ）。"""
    refs, block = [], False
    for i in range(a + 1, b):
        x = lines[i]
        m = cp.SNIPPET_LINE_RE.match(x)
        if m:
            if x.lstrip().startswith(";"):
                continue
            if m.group("path"):
                refs.append((i, m.group("path")))
            else:
                block = not block
        elif block and x.strip() and not x.strip().startswith(";"):
            refs.append((i, x.strip()))
    return refs


def make_line(indent: str, files: list[str], types: list[str], host_rel: str, modint_title: str) -> str:
    base = [posixpath.basename(f) for f in files]
    names = [f if base.count(b) > 1 else b for f, b in zip(files, base)]
    links = "・".join(f"[`{n}`]({file_url(f)})" for n, f in zip(names, files))
    note = "".join("。" + mint_note(t, host_rel, modint_title) for t in types)
    return f"{indent}{LINE_PREFIX}{links}（GitHub）{note}"


def fix_text(text: str, rel: str, snippets: Path, modint_title: str = "modint") -> Result:
    """1 つの Markdown を直した結果。rel は docs からの相対パス（相対リンクと「直せない」の表示に使う）。"""
    _, _, body_line, _ = cp.split_front_matter(text)
    all_lines = text.split("\n")
    head, lines = all_lines[:body_line - 1], all_lines[body_line - 1:]
    res = Result(text=text)

    def where(i: int) -> str:
        return f"{rel}:{body_line + i}"

    # 1. 地の文の `snippets/…` をリンクにする（行の数は変わらない。道具の段落にはコードの snippets/… がない）
    lines = link_mentions(lines, rel, snippets, res, where)

    # 2. 道具の段落（2 行）を外す。どのフェンスの下にあったか（フェンスの何番目か）を覚えておく
    old: dict[int, str] = {}
    orphans = 0
    spans = cp.fence_spans(lines)
    close_at = {b: k for k, (a, b, _, _) in enumerate(spans)}
    infence = {i for a, b, _, _ in spans for i in range(a, b + 1)}
    keep: list[str] = []
    orig: list[int] = []                         # 残した行の元の行の番号（「直せない」の表示用）
    i = 0
    while i < len(lines):
        if i not in infence and is_generated(lines, i):
            j = i - 1
            while j >= 0 and not lines[j].strip():
                j -= 1
            if j in close_at:
                old[close_at[j]] = lines[i]
            else:
                orphans += 1
            if keep and not keep[-1].strip():
                keep.pop()                       # 前の空行（置くときに足したもの）
                orig.pop()
            i += 2
            continue
        keep.append(lines[i])
        orig.append(i)
        i += 1
    lines = keep

    def at(i: int) -> str:
        return where(orig[i])

    # 3. 取り込みのあるフェンスと、置く行
    spans = cp.fence_spans(lines)
    in_comment = comment_lines(lines, spans)
    fences: list[tuple[int, Fence]] = []
    for k, (a, b, lang, indent) in enumerate(spans):
        if lang not in CPP_LANGS or a in in_comment:
            continue
        refs = fence_refs(lines, a, b)
        if not refs:
            continue
        if b <= a or not CLOSE_FENCE_RE.match(lines[b]):
            res.problems.append(f"{at(a)}: ```{lang} が閉じていない")
            continue
        fc = Fence(a, b, indent, refs)
        for li, ref in refs:
            path, ranges, section = split_ref(ref)
            f = snippets / path
            if not path or not f.is_file():
                res.problems.append(f"{at(li)}: 取り込むファイル snippets/{path} がない")
                continue
            if path not in fc.files:
                fc.files.append(path)
            shown = shown_lines(f, ranges, section)
            if shown is None:
                res.problems.append(f"{at(li)}: snippets/{path} に範囲 [start:{section}]〜[end:{section}] がない")
                continue
            if any(MINT_RE.search(x) for x in shown):
                types = mint_types(f)
                if len(types) != 1:
                    res.problems.append(f"{at(li)}: snippets/{path} の範囲に mint が出るが、using mint = …; が"
                                        + ("ない" if not types else f" {len(types)} 通りある（{'・'.join(types)}）")
                                        + "（注記を付けない）")
                elif types[0] not in fc.mint:
                    fc.mint.append(types[0])
        if fc.files:
            fences.append((k, fc))
    res.fences = len(fences)

    # 同じファイルの組を空行だけを挟んで続けて取り込むフェンスは、最後のフェンスの下にだけ置く
    groups: list[list[tuple[int, Fence]]] = []
    for k, fc in fences:
        if groups:
            prev = groups[-1][-1][1]
            if (prev.indent == fc.indent and prev.files == fc.files
                    and all(not x.strip() for x in lines[prev.end + 1:fc.start])):
                groups[-1].append((k, fc))
                continue
        groups.append([(k, fc)])

    new: dict[int, tuple[int, str]] = {}          # フェンスの番号 → (閉じの行, 置く行)
    for g in groups:
        k, last = g[-1]
        types: list[str] = []
        for _, fc in g:
            types += [t for t in fc.mint if t not in types]
        if rel == MODINT_REL:
            types = []
        if len(types) > 1:
            res.problems.append(f"{at(last.start)}: 続けて取り込むコードの mint の型が {len(types)} 通りある"
                                f"（{'・'.join(types)}。注記を付けない）")
            types = []
        new[k] = (last.end, make_line(last.indent, last.files, types, rel, modint_title))
        res.lines += 1
        res.notes += bool(types)

    for k, (_, line) in new.items():
        if k not in old:
            res.added += 1
        elif old[k] != line:
            res.updated += 1
    res.removed = orphans + sum(1 for k in old if k not in new)

    for k in sorted(new, reverse=True):
        end, line = new[k]
        add = ["", line, spans[k][3] + CLASS_LINE]
        if end + 1 < len(lines) and lines[end + 1].strip():
            add.append("")
        lines[end + 1:end + 1] = add

    res.text = "\n".join(head + lines)
    return res


def link_mentions(lines: list[str], rel: str, snippets: Path, res: Result, where) -> list[str]:
    p = cp.Page(path=Path(rel), rel=rel, text="\n".join(lines))
    p.body = p.text
    p.analyze()
    out = list(lines)
    for i, s in cp.text_lines(p):
        raw = lines[i]
        spans = [(a, b) for a, b in cp.md_code_spans(raw)
                 if raw[a] == "`" and MENTION_RE.match(raw[a:b].strip("`").strip())]
        if not spans:
            continue
        if s != raw or cp.ANY_HEADING_RE.match(raw):
            why = "見出しの中" if cp.ANY_HEADING_RE.match(raw) else "HTML のコメントのある行"
            res.problems.append(f"{where(i)}: {why}の snippets/… はリンクにしない（文を直す）")
            continue
        links = list(cp.LINK_RE.finditer(raw))
        new = raw
        for a, b in reversed(spans):
            code = raw[a:b]
            path = MENTION_RE.match(code.strip("`").strip()).group("path")
            f = snippets / path
            exists = f.is_file() or f.is_dir()
            m = next((m for m in links if m.start() <= a and b <= m.end()), None)
            if m is not None:
                # もうリンクの文字の中にある。[`snippets/…`](このリポジトリの URL) の形なら、先のファイルと URL を確かめる
                dest = cp.link_dest(m.group("dest"))
                if raw[m.start():a] == "[" and raw[b:b + 2] == "](" and dest.startswith(REPO_URL + "/"):
                    if not exists:
                        res.problems.append(f"{where(i)}: {code} のリンクの先 snippets/{path} がない")
                    elif dest != file_url(path, f.is_dir()):
                        new = new[:m.start()] + f"[{code}]({file_url(path, f.is_dir())})" + new[m.end():]
                        res.mentions += 1
                continue
            if not exists:
                res.problems.append(f"{where(i)}: {code} の snippets/{path} がない（リンクにしない）")
                continue
            new = new[:a] + f"[{code}]({file_url(path, f.is_dir())})" + new[b:]
            res.mentions += 1
        out[i] = new
    return out


# ---------------------------------------------------------------- 全体

def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--check", action="store_true", help="直すべき差分を出すだけ（書かない）")
    parser.add_argument("--stat", action="store_true", help="--check で、差分の代わりにファイルごとの件数だけを出す")
    parser.add_argument("--page", action="append", default=[], help="そのページだけ（id かパス。くり返し・カンマ区切り可）")
    parser.add_argument("--field", choices=cp.FIELDS, action="append", default=[], help="その分野だけ（--page があるときは使わない）")
    parser.add_argument("--root", type=Path, default=cp.ROOT, help="docs/ のある場所（既定はリポジトリ）")
    parser.add_argument("--snippets", type=Path, default=None,
                        help="コード片の場所（既定は <root>/snippets。なければリポジトリの snippets/）")
    args = parser.parse_args()

    docs = args.root / "docs"
    if not docs.is_dir():
        sys.exit(f"{docs} がない")
    snippets = args.snippets or (args.root / "snippets")
    if not snippets.is_dir():
        if args.snippets is None and (cp.ROOT / "snippets").is_dir():
            print(f"注意: {snippets} がないので {cp.ROOT / 'snippets'} を使う", file=sys.stderr)
            snippets = cp.ROOT / "snippets"
        else:
            sys.exit(f"{snippets} がない")
    pages, others = cp.load_docs(docs)
    everything = pages + others
    modint = next((p for p in everything if p.rel == MODINT_REL), None)
    title = modint.get("title") if modint is not None else None
    modint_title = title if isinstance(title, str) and title.strip() else "modint"

    targets = everything
    wanted = [x.strip() for v in args.page for x in v.split(",") if x.strip()]
    if wanted:
        missing = [x for x in wanted if not any(x in (p.id, p.rel, f"docs/{p.rel}") for p in targets)]
        if missing:
            sys.exit("そのページがない: " + ", ".join(missing))
        if args.field:
            print("注意: --page があるので --field は使わない", file=sys.stderr)
        targets = [p for p in targets if any(x in (p.id, p.rel, f"docs/{p.rel}") for x in wanted)]
    elif args.field:
        targets = [p for p in targets if p.dir_field in args.field]

    tot = Result(text="")
    n_files = 0
    problems: list[str] = []
    for p in targets:
        r = fix_text(p.text, p.rel, snippets, modint_title)
        problems += r.problems
        for k in ("added", "updated", "removed", "lines", "notes", "fences", "mentions"):
            setattr(tot, k, getattr(tot, k) + getattr(r, k))
        if r.text == p.text:
            continue
        n_files += 1
        detail = (f"行 追加 {r.added}・更新 {r.updated}・削除 {r.removed}（置く行 {r.lines}、うち mint の注記 {r.notes}）"
                  f"・言及のリンク {r.mentions}")
        if args.check and not args.stat:
            sys.stdout.writelines(difflib.unified_diff(
                p.text.splitlines(keepends=True), r.text.splitlines(keepends=True),
                fromfile=f"a/docs/{p.rel}", tofile=f"b/docs/{p.rel}"))
            if not r.text.endswith("\n"):
                print()
        print(("直すべきファイル " if args.check else "直したファイル ") + f"docs/{p.rel}: {detail}")
        if not args.check:
            p.path.write_text(r.text, encoding="utf-8")
    for pr in problems:
        print("直せない: " + pr)
    verb = "直すべきファイル" if args.check else "直したファイル"
    print(f"\n{verb}: {n_files}・コードの下の行 追加 {tot.added}・更新 {tot.updated}・削除 {tot.removed}"
          f"・地の文の snippets/… をリンクに {tot.mentions}・直せない: {len(problems)}"
          f"（見たページ {len(targets)}・取り込みのある ```cpp {tot.fences}・置く行 {tot.lines}、うち mint の注記 {tot.notes}）")
    sys.exit(1 if problems or (args.check and n_files) else 0)


if __name__ == "__main__":
    main()
