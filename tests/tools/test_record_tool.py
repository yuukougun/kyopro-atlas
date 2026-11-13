"""記録用スキルの補助 .claude/skills/record-problem/record_tool.py の小さな試験：どこで実行しても根を返す root、
ap が tools/ap.py の show・contest・fetch だけを通すこと、check が v1 の記録と v2 の任意の項目を確かめること。
python3 -m unittest discover -s tests/tools"""
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
TOOL = ROOT / ".claude" / "skills" / "record-problem" / "record_tool.py"

NOTE = """---
problem: abc300_e
contest: abc300
title: "E. Dice Product 3"
url: https://atcoder.jp/contests/abc300/tasks/abc300_e
difficulty: 1354
records:
  - date: 2026-10-21
    cause: 気づけなかった
    learned: "自己ループは移項してから計算する"
    pages: []
    improvement: null
{extra}---

# [abc300_e E. Dice Product 3](https://atcoder.jp/contests/abc300/tasks/abc300_e)

## 2026-10-21（気づけなかった）

移項すると残りの目の平均になる。
"""


def run(*args: str, cwd: Path | None = None) -> subprocess.CompletedProcess:
    return subprocess.run([sys.executable, str(TOOL), *args], cwd=cwd, capture_output=True, text=True)


class RecordToolTest(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.dir = Path(self.tmp.name)

    def tearDown(self):
        self.tmp.cleanup()

    def test_root_from_other_folder_and_symlink(self):
        self.assertEqual(run("root", cwd=self.dir).stdout.strip(), str(ROOT))
        link = self.dir / "skills" / "record-problem"
        link.parent.mkdir()
        link.symlink_to(TOOL.parent)
        r = subprocess.run([sys.executable, str(link / "record_tool.py"), "root"], cwd=self.dir, capture_output=True, text=True)
        self.assertEqual(r.stdout.strip(), str(ROOT))      # リンク経由でも実体の kyopro-atlas を指す

    def test_ap_only_allows_three_commands(self):
        r = run("ap", "search", "x", cwd=self.dir)
        self.assertEqual(r.returncode, 2)
        self.assertIn("show・contest・fetch", r.stderr)
        self.assertEqual(run("ap", cwd=self.dir).returncode, 2)

    def check(self, extra: str) -> subprocess.CompletedProcess:
        path = self.dir / "abc300_e.md"
        path.write_text(NOTE.format(extra=extra), encoding="utf-8")
        return run("check", str(path), cwd=self.dir)

    def test_check_v1_and_v2(self):
        self.assertEqual(self.check("").returncode, 0, "v1 の記録（任意の項目なし）は通る")
        ok = "    support: ヒントだけ\n    status: AC\n    code: abc300/e/main.cpp\n"
        self.assertEqual(self.check(ok).returncode, 0)
        self.assertEqual(self.check("    support: null\n    status: null\n    code: null\n").returncode, 0)
        r = self.check("    support: 解説\n    status: WA\n")
        self.assertEqual(r.returncode, 1)
        self.assertIn("support は", r.stdout)
        self.assertIn("status は", r.stdout)


if __name__ == "__main__":
    unittest.main()
