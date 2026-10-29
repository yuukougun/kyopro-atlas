"""コード片の検査（tools/check_snippets.py）の試験。python3 -m unittest discover -s tests/tools
#95：コードの位置のない -m のオプションへの cc1plus の警告（-march=native では、検査を動かす計算機の CPU しだいで出る。
AVX10.1 を持つ CPU では GCC 15 が cc1plus: warning: ‘-mavx10.1’ is aliased to 512 bit … を出す）は、expect: run・warning の
判定に数えず、結果の行の下に注記として出す。subprocess.run をまねてコンパイラの出力を決め、run_one と結果の出し方を確かめる。
g++-15（か版が 15 の g++）があれば、本物のコンパイラでも確かめる（-Wp,-mavx10.1 で、AVX10.1 を持たない計算機でも CI と
同じ形の警告を出す）。"""
from __future__ import annotations

import contextlib
import io
import os
import re
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path
from unittest import mock

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
import check_snippets as cs  # noqa: E402

# CI（gcc:15.2.0 のコンテナ。AVX10.1 を持つ CPU）の run 40823490357 で、fma-native.cpp の 1 回のコンパイルに 2 回出た形。
# 引用符は UTF-8 のロケールの ‘ ’。C・POSIX のロケールでは '
AVX10 = ("cc1plus: warning: ‘-mavx10.1’ is aliased to 512 bit since GCC14.3 and GCC15.1 while ‘-mavx10.1-256’ and "
         "‘-mavx10.1-512’ will be deprecated in GCC 16 due to all machines 512 bit vector size supported")
AVX10_C = AVX10.replace("‘", "'").replace("’", "'")
EVEX512 = "cc1plus: warning: ‘-mevex512’ will be deprecated in GCC 16 due to all machines 512 bit vector size supported"
# コードへの警告（g++-15 の出力の 4 行。数えるのは warning: の行だけ）
CODE = ["x/b.cpp: In function ‘int main()’:", "x/b.cpp:2:16: warning: unused variable ‘x’ [-Wunused-variable]",
        "    2 | int main(){int x; return 0;}", "      |                ^"]
# 今までどおり数える警告（g++-15 の本物の形。最後の 1 つは仮の形）
COUNTED = [
    CODE[1],                                                                                    # 位置（ファイル:行:列）
    "cc1plus: warning: command-line option ‘-std=gnu11’ is valid for C/ObjC but not for C++",   # -m 以外のオプション
    "cc1plus: warning: command-line option '-Wstrict-prototypes' is valid for C/ObjC but not for C++",
    "cc1plus: warning: ‘-fstack-check=’ and ‘-fstack-clash-protection’ are mutually exclusive; disabling ‘-fstack-check=’",
    "<command-line>: warning: ‘_FORTIFY_SOURCE’ redefined",                                     # -D の再定義
    AVX10.replace("cc1plus:", "g++-15:", 1),         # ドライバ（flags に -mavx10.1 を書いたとき。CPU によらず出る）
    AVX10.replace("cc1plus:", "x/b.cpp:1:9:", 1),    # 位置のある行は、文が -m のオプションで始まっても数える（仮の形）
]
ONE_CASE = [{"input": "", "output": "6\n"}]


def unit(expect: str, cases: list[dict] | None = None, name: str = "x/b") -> cs.Unit:
    u = cs.Unit(cpp=Path("/kp/snippets") / f"{name}.cpp", yml=Path("/kp/snippets") / f"{name}.yaml", name=name)
    u.config = {"compilers": ["g++-15"], "flags": "-std=gnu++23 -O2 -Wall -Wextra -march=native", "expect": expect,
                "cases": cases or []}
    return u


def fake_run(stderr: dict[str, list[str]], stdout: str = "6\n", code: int = 0):
    """subprocess.run の代わり。コンパイルはコード片の名前ごとに stderr の行を出して通り、実行は stdout を出して code で終わる。"""
    def run(cmd, **kw):
        if Path(cmd[0]).name == "a.out":
            return subprocess.CompletedProcess(cmd, code, stdout=stdout, stderr="")
        src = next(x for x in cmd if x.endswith(".cpp"))
        lines = stderr.get(src[:-len(".cpp")], [])
        return subprocess.CompletedProcess(cmd, 0, stdout="", stderr="".join(x + "\n" for x in lines))
    return run


def run_one(u: cs.Unit, stderr: list[str], stdout: str = "6\n", code: int = 0) -> tuple[bool, str, list[str]]:
    with mock.patch.object(cs, "resolve_compiler", return_value="g++-15"), \
            mock.patch.object(cs.subprocess, "run", side_effect=fake_run({u.name: stderr}, stdout, code)):
        return cs.run_one(u, "g++-15", None, 10.0)


def result_blocks(out: str) -> dict[str, tuple[str, str, list[str]]]:
    """道具の出力の結果の行（OK・NG）と、その下の字下げした行。鍵はコード片の名前（x/clean-run）。"""
    blocks: dict[str, tuple[str, str, list[str]]] = {}
    cur = None
    for line in out.split("\n"):
        m = re.match(r"(OK|NG)  (\S+)\.cpp（[^）]*）: (.*)", line)
        if m:
            cur = m.group(2)
            blocks[cur] = (m.group(1), m.group(3), [])
        elif cur and line.startswith("      "):
            blocks[cur][2].append(line[6:])
        else:
            cur = None
    return blocks


class SplitWarningsTest(unittest.TestCase):
    def test_m_option_warnings_of_cc1plus(self):
        for line in (AVX10, AVX10_C, EVEX512):
            with self.subTest(line=line):
                self.assertEqual(cs.split_warnings([line]), ([], [line]))

    def test_other_warnings_are_counted(self):
        for line in COUNTED:
            with self.subTest(line=line):
                self.assertEqual(cs.split_warnings([line]), ([line], []))

    def test_lines_without_warning(self):
        lines = [CODE[0], CODE[2], CODE[3], "<command-line>: note: this is the location of the previous definition"]
        self.assertEqual(cs.split_warnings(lines), ([], []))


class RunOneTest(unittest.TestCase):
    def test_run_ok_with_only_m_option_warning(self):
        """(1) -m のオプションへの cc1plus の警告だけなら run は OK。注記に出す（2 回出ても 1 行。引用符はどちらのロケールでも）"""
        for warn in (AVX10, AVX10_C):
            with self.subTest(warn=warn[:30]):
                self.assertEqual(run_one(unit("run", ONE_CASE), [warn, warn]), (True, "1 case 一致", [cs.NOTE + warn]))

    def test_run_ng_with_code_warning(self):
        """(2) コードの位置つきの警告があれば run は NG。数えない警告は注記として後ろに出す"""
        ok, msg, detail = run_one(unit("run", ONE_CASE), [AVX10, *CODE, AVX10])
        self.assertFalse(ok)
        self.assertEqual(msg, "警告が出た（run は警告なし。警告を確かめるなら expect: warning）")
        self.assertEqual(detail, [CODE[1], cs.NOTE + AVX10])

    def test_run_ng_with_other_warnings(self):
        """-m 以外のオプションへの警告・<command-line> の再定義・ドライバの警告は、今までどおり run で NG"""
        for line in COUNTED:
            with self.subTest(line=line):
                ok, msg, detail = run_one(unit("run"), [line])
                self.assertFalse(ok)
                self.assertEqual(detail, [line])

    def test_warning_ng_with_only_m_option_warning(self):
        """(3) warning の期待で -m のオプションへの警告しかないなら NG（警告が出ない扱い）"""
        self.assertEqual(run_one(unit("warning", ONE_CASE), [AVX10, AVX10]),
                         (False, "警告が出ない（warning のはず）", [cs.NOTE + AVX10]))

    def test_warning_ok_with_code_warning(self):
        self.assertEqual(run_one(unit("warning", ONE_CASE), [*CODE, AVX10]),
                         (True, "警告あり（期待どおり）・1 case 一致", [cs.NOTE + AVX10]))

    def test_note_after_wrong_output(self):
        """数えない警告のあとで出力が違って NG になったときも、注記を後ろに足す"""
        self.assertEqual(run_one(unit("run", ONE_CASE), [AVX10], stdout="7\n"),
                         (False, "case 1: 出力が違う", ["期待: 6", "出力: 7", cs.NOTE + AVX10]))

    def test_unchanged_without_m_option_warning(self):
        """-m のオプションへの警告がなければ今までどおり（注記なし）"""
        self.assertEqual(run_one(unit("run", ONE_CASE), []), (True, "1 case 一致", []))
        self.assertEqual(run_one(unit("run"), []), (True, "実行できた（case なし）", []))
        self.assertEqual(run_one(unit("warning"), CODE), (True, "警告あり（期待どおり）", []))
        self.assertEqual(run_one(unit("warning"), []), (False, "警告が出ない（warning のはず）", []))

    def test_crash_and_compile_error_are_unchanged(self):
        """crash は警告を問わないので注記を足さない。compile-error でコンパイルが通ったときは今までどおり出力をそのまま出す"""
        self.assertEqual(run_one(unit("crash"), [AVX10], code=-6), (True, "異常終了（期待どおり。シグナル SIGABRT）", []))
        self.assertEqual(run_one(unit("compile-error"), [AVX10]), (False, "コンパイルが通った（compile-error のはず）", [AVX10]))


class MainOutputTest(unittest.TestCase):
    def test_ok_with_note_is_printed_without_verbose(self):
        """注記のある OK は -v なしでも出し（どの計算機で何が出たかを残す）、最後に回数と CPU の 1 行を出す"""
        with tempfile.TemporaryDirectory(prefix="kp-test-snip-") as tmp:
            d = Path(tmp) / "x"
            d.mkdir()
            for name in ("clean", "noted"):
                (d / f"{name}.cpp").write_text("int main() {}\n", encoding="utf-8")
                (d / f"{name}.yaml").write_text("compilers: [g++-15]\nexpect: run\n", encoding="utf-8")
            out = io.StringIO()
            with mock.patch.object(cs, "resolve_compiler", return_value="g++-15"), \
                    mock.patch.object(cs.subprocess, "run", side_effect=fake_run({"x/noted": [AVX10, AVX10]})), \
                    mock.patch.object(sys, "argv", ["check_snippets.py", "--dir", tmp, "-j", "1"]), \
                    contextlib.redirect_stdout(out), self.assertRaises(SystemExit) as e:
                cs.main()
        self.assertEqual(e.exception.code, 0)
        self.assertEqual(result_blocks(out.getvalue()), {"x/noted": ("OK", "実行できた（case なし）", [cs.NOTE + AVX10])})
        last = out.getvalue().strip().split("\n")[-1]
        self.assertTrue(last.startswith("注記: ") and "コンパイル 1 回" in last, last)


GXX15 = cs.resolve_compiler("g++-15")
# -Wp,-mavx10.1 は -mavx10.1 をドライバを通さずに cc1plus にだけ渡す。AVX10.1 を持つ CPU で -march=native が広げたオプションと
# 同じく cc1plus だけが警告を出すので、AVX10.1 を持たない計算機でも CI と同じ形になる。後ろの -Wp,-mno-avx10.1 で外すので、
# できたプログラムは手元の CPU で動く
FLAGS = "-std=gnu++23 -O2 -Wall -Wextra -march=native -Wp,-mavx10.1 -Wp,-mno-avx10.1"


def compile_empty(env: dict[str, str] | None = None) -> subprocess.CompletedProcess:
    with tempfile.TemporaryDirectory(prefix="kp-test-snip-") as tmp:
        src = Path(tmp) / "a.cpp"
        src.write_text("int main() {}\n", encoding="utf-8")
        return subprocess.run([GXX15, *FLAGS.split(), "-fsyntax-only", str(src)], capture_output=True, text=True,
                              env=env, timeout=120)


@unittest.skipUnless(GXX15, "g++-15 がない（版が 15 の g++ もない）")
class RealCompilerTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        r = compile_empty()
        if r.returncode != 0 or "warning:" not in r.stderr:
            raise unittest.SkipTest("この g++-15 は -mavx10.1 に警告を出さないか、x86-64 でない")

    def test_message_in_each_locale(self):
        """C のロケール（引用符 '）でも C.UTF-8（‘ ’。CI のコンテナでは Python が LC_CTYPE を C.UTF-8 にして子に渡す）でも数えない"""
        for loc in ("C", "C.UTF-8"):
            with self.subTest(locale=loc):
                env = {k: v for k, v in os.environ.items() if not k.startswith("LC_") and k != "LANG"}
                env["LC_ALL"] = loc
                lines = compile_empty(env).stderr.strip().split("\n")
                self.assertEqual(cs.split_warnings(lines), ([], lines))
                if loc == "C":
                    self.assertIn("'-mavx10.1'", lines[0])

    def test_tool(self):
        """(1)〜(3) を道具の全体で：run の OK は -v なしでも注記と出し、位置つきの警告の run と、-m の警告だけの warning は NG"""
        with tempfile.TemporaryDirectory(prefix="kp-test-snip-") as tmp:
            d = Path(tmp) / "x"
            d.mkdir()

            def put(name: str, code: str, expect: str, cases: str = "") -> None:
                (d / f"{name}.cpp").write_text(code, encoding="utf-8")
                (d / f"{name}.yaml").write_text(f'compilers: [g++-15]\nflags: "{FLAGS}"\nexpect: {expect}\n{cases}',
                                                encoding="utf-8")

            put("clean-run", '#include <cstdio>\nint main() { std::puts("ok"); }\n', "run",
                'cases:\n  - {input: "", output: "ok\\n"}\n')
            put("unused-run", "int main() { int x; return 0; }\n", "run")
            put("clean-warning", "int main() { return 0; }\n", "warning")
            r = subprocess.run([sys.executable, str(ROOT / "tools" / "check_snippets.py"), "--dir", tmp],
                               capture_output=True, text=True, timeout=600)
        self.assertEqual(r.returncode, 1, r.stdout + r.stderr)
        blocks = result_blocks(r.stdout)
        self.assertEqual(set(blocks), {"x/clean-run", "x/unused-run", "x/clean-warning"}, r.stdout)
        st, msg, detail = blocks["x/clean-run"]
        self.assertEqual((st, msg), ("OK", "1 case 一致"))
        # AVX10.1 を持つ計算機（CI）では、-march=native が広げた -mavx10.1 に -Wp,-mno-avx10.1 が重なり、
        # ‘-mno-avx10.1-256, -mno-avx10.1-512’ cannot disable AVX512 … の警告も出る。どれも -m のオプションへの cc1plus の警告である
        self.assertTrue(detail and all(x.startswith(cs.NOTE) and cs.M_OPTION_WARNING_RE.match(x[len(cs.NOTE):])
                                       for x in detail), detail)
        st, msg, detail = blocks["x/unused-run"]
        self.assertEqual(st, "NG")
        self.assertIn("警告が出た", msg)
        self.assertIn("x/unused-run.cpp:1:18: warning: unused variable", detail[0])
        self.assertTrue(detail[-1].startswith(cs.NOTE), detail)
        st, msg, detail = blocks["x/clean-warning"]
        self.assertEqual((st, msg), ("NG", "警告が出ない（warning のはず）"))
        self.assertTrue(detail and all(x.startswith(cs.NOTE) for x in detail), detail)
        self.assertIn("コンパイル 3 回", r.stdout.strip().split("\n")[-1])


if __name__ == "__main__":
    unittest.main()
