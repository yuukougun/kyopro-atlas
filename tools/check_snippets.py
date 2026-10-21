#!/usr/bin/env python3
"""コード片（snippets/<page-id>/<name>.cpp と設定 <name>.yaml）をコンパイル・実行し、設定の期待どおりかを確かめる
（planning/interfaces.md §9、設計書 §6.5・§8.6、design-review T11）。

使い方:
  python3 tools/check_snippets.py                     すべてのコード片を確かめる
  python3 tools/check_snippets.py --changed           git で変わったコード片だけ（コミットしていない変更と、まだ追跡していないファイル）
  python3 tools/check_snippets.py --changed --base origin/main   加えて、--base からのコミットで変わったもの（CI の push では
                                                      github.event.before を渡す）
  python3 tools/check_snippets.py snippets/lazy-segment-tree     指定したものだけ（フォルダ・.cpp・.yaml。くり返し可）
  python3 tools/check_snippets.py --compiler g++-15   設定の compilers のうちこれだけを試す（くり返し・カンマ区切り可。
                                                      CI の gcc:15.2.0 のコンテナ用。どれも持たないコード片は飛ばして数を出す）
  python3 tools/check_snippets.py --acl ~/lib/ac-library-master  ACL の場所（既定は third_party/ac-library。まだないときの代わり）
  python3 tools/check_snippets.py --dir DIR           コード片のフォルダ（既定は snippets。試験用）
  python3 tools/check_snippets.py -j 8 --timeout 10   並列の数（既定は CPU の数と 8 の小さい方）・1 回の実行の秒数の上限
  python3 tools/check_snippets.py -v                  通ったものも1行ずつ出す
終了コード: 期待と違うものがあれば 1（コード片がないときは 0）

設定（<name>.yaml。interfaces.md §9 の4つ。ないときは既定の設定の run で、入力なしの実行が正常に終わるかだけを見る）:
  compilers: [g++-15]                         既定 [g++-15]。cpp の版の確認なら [g++-13, g++-15]。g++-N がなく g++ の版が N なら
                                              g++ を使う（CI の gcc:15.2 のコンテナ）
  flags: "-std=gnu++23 -O2 -Wall -Wextra"     既定はこれ（AtCoder の GCC と同じ版）。ACL の -I はこの道具が足す
  expect: run                                 run：警告なしでコンパイルでき、各 case の出力が一致する（case がなければ正常終了）
                                              compile-error：コンパイルが失敗する
                                              warning：コンパイルでき、警告（warning:）が出る。case があれば出力も確かめる
  cases: [{input: "3\\n1 2 3\\n", output: "6\\n"}]   出力は各行の末尾の空白と最後の改行を無視して比べる
知らない項目があれば誤りとする（綴りの誤りを見逃さないため）。範囲の目印（// --8<-- [start:名前] 〜 [end:名前]）の
対応と名前の重なりも確かめる。.yaml だけで .cpp がないものも誤りとする。
"""
from __future__ import annotations

import argparse
import concurrent.futures as cf
import os
import re
import shlex
import shutil
import subprocess
import sys
import tempfile
import time
from dataclasses import dataclass, field
from pathlib import Path

import yaml

ROOT = Path(__file__).resolve().parent.parent
SNIPPETS = ROOT / "snippets"
ACL = ROOT / "third_party" / "ac-library"
DEFAULTS = {"compilers": ["g++-15"], "flags": "-std=gnu++23 -O2 -Wall -Wextra", "expect": "run", "cases": []}
EXPECTS = {"run", "compile-error", "warning"}
MARK_RE = re.compile(r"--8<--\s*\[(start|end):([A-Za-z0-9_-]+)\]")


@dataclass
class Unit:
    cpp: Path
    yml: Path
    name: str                     # snippets からの相対パス（拡張子なし）
    config: dict = field(default_factory=dict)
    errors: list[str] = field(default_factory=list)


def load_unit(cpp: Path, base: Path) -> Unit:
    u = Unit(cpp=cpp, yml=cpp.with_suffix(".yaml"), name=cpp.relative_to(base).with_suffix("").as_posix())
    conf = dict(DEFAULTS)
    if u.yml.exists():
        try:
            doc = yaml.safe_load(u.yml.read_text(encoding="utf-8")) or {}
        except yaml.YAMLError as e:
            u.errors.append(f"設定の YAML が読めない: {e}")
            doc = {}
        if not isinstance(doc, dict):
            u.errors.append("設定がマッピングでない")
            doc = {}
        for k in sorted(set(doc) - set(DEFAULTS)):
            u.errors.append(f"設定の知らない項目 {k}（compilers・flags・expect・cases）")
        conf.update({k: v for k, v in doc.items() if k in DEFAULTS})
    comps = conf["compilers"]
    if isinstance(comps, str):
        comps = [comps]
    if not (isinstance(comps, list) and comps and all(isinstance(c, str) for c in comps)):
        u.errors.append(f"compilers が文字列のリストでない: {conf['compilers']!r}")
        comps = []
    conf["compilers"] = comps
    if not isinstance(conf["flags"], str):
        u.errors.append(f"flags が文字列でない: {conf['flags']!r}")
        conf["flags"] = DEFAULTS["flags"]
    if conf["expect"] not in EXPECTS:
        u.errors.append(f"expect が不正: {conf['expect']!r}（run・compile-error・warning）")
    cases = conf["cases"] or []
    good = []
    for i, c in enumerate(cases if isinstance(cases, list) else []):
        if isinstance(c, dict) and set(c) <= {"input", "output"} and all(isinstance(c.get(k, ""), str) for k in ("input", "output")):
            good.append({"input": c.get("input", ""), "output": c.get("output")})
        else:
            u.errors.append(f"cases[{i}] の形が不正（input と output の文字列）: {c!r}")
    if not isinstance(cases, list):
        u.errors.append("cases がリストでない")
    conf["cases"] = good
    u.config = conf
    # 範囲の目印
    text = cpp.read_text(encoding="utf-8", errors="replace")
    opened: dict[str, int] = {}
    closed: set[str] = set()
    for no, line in enumerate(text.split("\n"), 1):
        for m in MARK_RE.finditer(line):
            kind, nm = m.groups()
            if kind == "start":
                if nm in opened or nm in closed:
                    u.errors.append(f"{no} 行: 範囲 {nm} の start が重なっている")
                opened[nm] = no
            else:
                if nm not in opened:
                    u.errors.append(f"{no} 行: 範囲 {nm} の end に対応する start がない")
                else:
                    del opened[nm]
                    closed.add(nm)
    for nm, no in opened.items():
        u.errors.append(f"{no} 行: 範囲 {nm} の end がない")
    return u


_compiler_cache: dict[str, str | None] = {}


def resolve_compiler(name: str) -> str | None:
    if name not in _compiler_cache:
        found = name if shutil.which(name) else None
        if not found:
            m = re.fullmatch(r"(g\+\+|gcc|clang\+\+)-(\d+)", name)
            plain = m and shutil.which(m.group(1))
            if plain:
                ver = subprocess.run([m.group(1), "-dumpversion"], capture_output=True, text=True).stdout.strip()
                found = m.group(1) if ver.split(".")[0] == m.group(2) else None
        _compiler_cache[name] = found
    return _compiler_cache[name]


def norm_out(s: str) -> str:
    return "\n".join(line.rstrip() for line in s.replace("\r\n", "\n").split("\n")).rstrip("\n")


def run_one(u: Unit, compiler: str, acl: Path | None, timeout: float) -> tuple[bool, str, list[str]]:
    """(期待どおりか, 一言, 詳しい行)。"""
    exe_name = resolve_compiler(compiler)
    if exe_name is None:
        return False, f"コンパイラ {compiler} がない", []
    conf = u.config
    with tempfile.TemporaryDirectory(prefix="kp-snip-") as tmp:
        exe = Path(tmp) / "a.out"
        cmd = [exe_name, *shlex.split(conf["flags"])]
        if acl is not None:
            cmd += ["-I", str(acl)]
        cmd += [u.name + ".cpp", "-o", str(exe)]
        try:
            cp = subprocess.run(cmd, capture_output=True, text=True, timeout=300, cwd=u.cpp.parents[len(Path(u.name).parts) - 1])
        except subprocess.TimeoutExpired:
            return False, "コンパイルが 300 秒で終わらない", []
        diag = cp.stderr.strip().split("\n") if cp.stderr.strip() else []
        has_warning = any("warning:" in x for x in diag)
        expect = conf["expect"]
        if expect == "compile-error":
            if cp.returncode != 0:
                return True, "コンパイルエラー（期待どおり）", []
            return False, "コンパイルが通った（compile-error のはず）", diag[:10]
        if cp.returncode != 0:
            errs = [x for x in diag if "error" in x]
            return False, "コンパイルエラー", (errs or diag)[:8]
        if expect == "warning" and not has_warning:
            return False, "警告が出ない（warning のはず）", []
        if expect == "run" and has_warning:
            return False, "警告が出た（run は警告なし。警告を確かめるなら expect: warning）", [x for x in diag if "warning:" in x][:10]
        cases = conf["cases"] or ([{"input": "", "output": None}] if expect == "run" else [])
        for i, c in enumerate(cases):
            try:
                r = subprocess.run([str(exe)], input=c["input"], capture_output=True, text=True, timeout=timeout, cwd=tmp)
            except subprocess.TimeoutExpired:
                return False, f"case {i + 1}: {timeout:g} 秒で終わらない", []
            if r.returncode != 0:
                return False, f"case {i + 1}: 終了コード {r.returncode}", (r.stderr.strip().split("\n")[:8] if r.stderr.strip() else [])
            if c["output"] is not None and norm_out(r.stdout) != norm_out(c["output"]):
                exp, got = norm_out(c["output"]).split("\n"), norm_out(r.stdout).split("\n")
                return False, f"case {i + 1}: 出力が違う", [f"期待: {x}" for x in exp[:6]] + [f"出力: {x}" for x in got[:6]]
        what = {"run": f"{len(conf['cases'])} case 一致" if conf["cases"] else "実行できた（case なし）",
                "warning": "警告あり（期待どおり）" + (f"・{len(conf['cases'])} case 一致" if conf["cases"] else "")}[expect]
        return True, what, []


def git_changed(base_dir: Path, ref: str | None) -> tuple[set[Path], Path] | None:
    """git で変わったファイル（絶対パス）と、リポジトリの根。git がなければ None。"""
    try:
        top = Path(subprocess.run(["git", "-C", str(base_dir), "rev-parse", "--show-toplevel"], capture_output=True,
                                  text=True, check=True).stdout.strip())
    except (subprocess.CalledProcessError, FileNotFoundError):
        return None
    def git(*a: str) -> subprocess.CompletedProcess:
        return subprocess.run(["git", "-C", str(top), *a], capture_output=True, text=True)

    names: set[str] = set()
    r = git("diff", "--name-only", "HEAD")              # コミットしていない変更（ステージ済みを含む）
    if r.returncode != 0:                               # まだコミットがない：追跡しているものすべて
        r = git("ls-files")
    names |= set(r.stdout.split())
    names |= set(git("ls-files", "--others", "--exclude-standard").stdout.split())   # まだ追跡していないファイル
    if ref:
        r = git("diff", "--name-only", f"{ref}...HEAD")
        if r.returncode != 0:
            sys.exit(f"git diff {ref}...HEAD が失敗した: {r.stderr.strip()}")
        names |= set(r.stdout.split())
    return {(top / x).resolve() for x in names}, top


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("paths", nargs="*", type=Path, help="確かめるもの（フォルダ・.cpp・.yaml）。なければすべて")
    parser.add_argument("--changed", action="store_true", help="git で変わったものだけ")
    parser.add_argument("--base", help="--changed で、この ref からのコミットの変更も入れる")
    parser.add_argument("--dir", type=Path, default=SNIPPETS, help="コード片のフォルダ（既定は snippets）")
    parser.add_argument("--acl", type=Path, help="ACL の場所（既定は third_party/ac-library）")
    parser.add_argument("--compiler", action="append", default=[], help="設定の compilers のうちこれだけを試す（くり返し・カンマ区切り可）")
    parser.add_argument("-j", "--jobs", type=int, default=min(8, os.cpu_count() or 2))
    parser.add_argument("--timeout", type=float, default=10.0, help="1 回の実行の秒数の上限（既定 10）")
    parser.add_argument("-v", "--verbose", action="store_true", help="通ったものも出す")
    args = parser.parse_args()

    base = args.dir.resolve()
    if not base.is_dir():
        print(f"{base} がない（コード片はまだない）")
        return
    acl = (args.acl or ACL).expanduser().resolve()
    if not acl.is_dir():
        if args.acl:
            sys.exit(f"ACL の場所 {acl} がない")
        print(f"注意: {acl} がない。ACL を使うコード片はコンパイルできない（--acl ~/lib/ac-library-master で代わりを使える）")
        acl = None
    cpps = sorted(base.rglob("*.cpp"))
    orphans = [y for y in sorted(base.rglob("*.yaml")) if not y.with_suffix(".cpp").exists()]

    if args.paths:
        want = []
        for p in args.paths:
            w = p.expanduser()
            w = w.resolve() if w.exists() or not (base / w).exists() else (base / w).resolve()
            if not w.exists():
                sys.exit(f"{p} がない")
            want.append(w)
        cpps = [c for c in cpps if any(c == w or c.with_suffix(".yaml") == w or w in c.parents for w in want)]
        orphans = [y for y in orphans if any(y == w or w in y.parents for w in want)]
    if args.changed:
        got = git_changed(base, args.base)
        if got is None:
            sys.exit("git のリポジトリの中でないので --changed を使えない")
        changed, _ = got
        if acl is not None and any(acl in x.parents for x in changed):
            print("ACL のファイルが変わったので、すべてのコード片を確かめる")
        else:
            # .cpp・.yaml はそのコード片だけ、フォルダの中のほかのファイル（入力など）はフォルダのすべて
            dirs = {x.parent for x in changed if base in x.parents and x.suffix not in (".cpp", ".yaml")}
            cpps = [c for c in cpps if c in changed or c.with_suffix(".yaml") in changed or c.parent in dirs]
            orphans = [y for y in orphans if y in changed]

    units = [load_unit(c, base) for c in cpps]
    only = {x.strip() for v in args.compiler for x in v.split(",") if x.strip()}
    if only:
        for u in units:
            u.config["compilers"] = [c for c in u.config["compilers"] if c in only]
        skipped = [u for u in units if not u.errors and not u.config["compilers"]]
        units = [u for u in units if u.errors or u.config["compilers"]]
        if skipped:
            print(f"--compiler {','.join(sorted(only))} を設定に持たないので飛ばした: {len(skipped)}（" + "、".join(u.name for u in skipped[:5])
                  + ("…" if len(skipped) > 5 else "") + "）")
    jobs = [(u, comp) for u in units if not u.errors for comp in u.config["compilers"]]
    t0 = time.time()
    results: dict[tuple[str, str], tuple[bool, str, list[str]]] = {}
    with cf.ThreadPoolExecutor(max_workers=max(1, args.jobs)) as ex:
        futs = {ex.submit(run_one, u, comp, acl, args.timeout): (u.name, comp) for u, comp in jobs}
        for f in cf.as_completed(futs):
            results[futs[f]] = f.result()

    bad = 0
    for y in orphans:
        bad += 1
        print(f"NG  {y.relative_to(base)}: 設定だけで .cpp がない")
    for u in units:
        if u.errors:
            bad += 1
            print(f"NG  {u.name}.cpp: " + "; ".join(u.errors))
            continue
        for comp in u.config["compilers"]:
            ok, msg, detail = results[(u.name, comp)]
            if ok and not args.verbose:
                continue
            bad += 0 if ok else 1
            used = resolve_compiler(comp)
            alias = f"→{used}" if used and used != comp else ""
            print(f"{'OK' if ok else 'NG'}  {u.name}.cpp（{comp}{alias}・{u.config['expect']}）: {msg}")
            for line in detail:
                print("      " + line)
    print(f"\nコード片 {len(units)}・コンパイル {len(jobs)} 回・期待と違う {bad}（{time.time() - t0:.1f} 秒、並列 {args.jobs}"
          + (f"、ACL {acl}" if acl else "、ACL なし") + "）")
    sys.exit(1 if bad else 0)


if __name__ == "__main__":
    main()
