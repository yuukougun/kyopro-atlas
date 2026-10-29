"""問題の行の difficulty の書き方（#5・#76）の試験：tools/check_pages.py の diff_text・problem_line・PROBLEM_LINE_RE と
書式・台帳の検査、tools/fix_problems.py の作り直し。python3 -m unittest discover -s tests/tools

行の diff は「（diff 1354）」、台帳で参考値（experimental: true）なら「（diff 1856・参考値）」、値がなければ「（diff なし）」。"""
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path

import yaml

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
import check_pages as cp  # noqa: E402
import fix_problems as fp  # noqa: E402

# 台帳（data/problems.yaml）の項目の形。題名・difficulty・参考値かどうかは tools/ap.py で確かめた実在の問題
LEDGER = {
    "abc300_e": {"id": "abc300_e", "contest": "abc300", "index": "E", "title": "Dice Product 3",
                 "difficulty": 1354, "experimental": False, "status": "確認済み"},
    "abc014_4": {"id": "abc014_4", "contest": "abc014", "index": "D", "title": "閉路",
                 "difficulty": 1856, "experimental": True, "status": "確認済み"},
    "typical90_a": {"id": "typical90_a", "contest": "typical90", "index": "001", "title": "Yokan Party（★4）",
                    "difficulty": None, "experimental": None, "status": "確認済み"},
}
HEAD = {
    "abc300_e": "- [ABC300 E. Dice Product 3](https://atcoder.jp/contests/abc300/tasks/abc300_e)",
    "abc014_4": "- [ABC014 D. 閉路](https://atcoder.jp/contests/abc014/tasks/abc014_4)",
    "typical90_a": "- [典型90 001. Yokan Party（★4）](https://atcoder.jp/contests/typical90/tasks/typical90_a)",
}
GOOD = {
    "abc300_e": HEAD["abc300_e"] + "（diff 1354）：要約。",
    "abc014_4": HEAD["abc014_4"] + "（diff 1856・参考値）：要約。",
    "typical90_a": HEAD["typical90_a"] + "（diff なし）：要約。",
}


def block(*lines: str, indent: str = "", role: str = "practice") -> str:
    out = [f'<div class="kp-problems" data-role="{role}" markdown>', "", *lines, "", "</div>"]
    return "\n".join(indent + x if x else x for x in out)


def page(body: str) -> cp.Page:
    p = cp.Page(path=Path("docs/basics/x.md"), rel="basics/x.md", text=body)
    p.body = body
    p.analyze()
    return p


def errors(body: str) -> list[tuple[str, str]]:
    """本文の検査（check_body_common）のエラーの (種類, 文) の列。"""
    rep = cp.Report()
    cp.check_body_common(page(body), rep, LEDGER, ROOT / "snippets")
    return [(kind, msg) for sev, kind, _, msg in rep.items if sev == "E"]


class DiffTextTest(unittest.TestCase):
    def test_forms(self):
        self.assertEqual(cp.diff_text(LEDGER["abc300_e"]), "1354")
        self.assertEqual(cp.diff_text(LEDGER["abc014_4"]), "1856・参考値")
        self.assertEqual(cp.diff_text(LEDGER["typical90_a"]), "なし")

    def test_edges(self):
        # 値がなければ experimental は見ない。true・false は値にしない。参考値は experimental が true のときだけ
        self.assertEqual(cp.diff_text({"difficulty": None, "experimental": True}), "なし")
        self.assertEqual(cp.diff_text({"difficulty": True}), "なし")
        self.assertEqual(cp.diff_text({}), "なし")
        self.assertEqual(cp.diff_text({"difficulty": 1200}), "1200")
        self.assertEqual(cp.diff_text({"difficulty": 1200, "experimental": None}), "1200")


class ProblemLineTest(unittest.TestCase):
    def test_line_from_ledger(self):
        for qid, line in GOOD.items():
            with self.subTest(qid=qid):
                self.assertEqual(cp.problem_line(LEDGER[qid], "要約。"), line)

    def test_regex_reads_lines(self):
        for qid, diff in [("abc300_e", "1354"), ("abc014_4", "1856・参考値"), ("typical90_a", "なし")]:
            m = cp.PROBLEM_LINE_RE.match(GOOD[qid])
            self.assertIsNotNone(m, qid)
            self.assertEqual((m["id"], m["diff"], m["summary"]), (qid, diff, "要約。"))

    def test_regex_rejects_other_forms(self):
        # 前の形の「—」、かっこの参考値、値のない参考値、空は書式の違い
        for diff in ["—", "1856（参考値）", "1856 参考値", "なし・参考値", "参考値", "-", ""]:
            with self.subTest(diff=diff):
                self.assertIsNone(cp.PROBLEM_LINE_RE.match(f"{HEAD['abc014_4']}（diff {diff}）：要約。"))


class CheckPagesTest(unittest.TestCase):
    def test_new_forms_pass(self):
        self.assertEqual(errors(block(*GOOD.values())), [])

    def test_old_dash_points_to_new_form(self):
        e = errors(block(HEAD["typical90_a"] + "（diff —）：要約。"))
        self.assertEqual([k for k, _ in e], ["問題の一覧の書式"])
        self.assertIn("（diff なし）", e[0][1])
        self.assertIn("fix_problems.py", e[0][1])
        self.assertIn("basics/x.md:3:", e[0][1])

    def test_other_format_error_shows_forms(self):
        e = errors(block(HEAD["abc014_4"] + "（diff 1856（参考値））：要約。"))
        self.assertEqual([k for k, _ in e], ["問題の一覧の書式"])
        self.assertIn("（diff 1856・参考値）", e[0][1])
        self.assertIn("（diff なし）", e[0][1])

    def test_mismatch_with_ledger(self):
        # 参考値の印の欠け・余分、値のある問題の「なし」は台帳との違い（fix_problems.py で直せる）
        for line, want in [(HEAD["abc014_4"] + "（diff 1856）：要約。", "diff 1856・参考値"),
                           (HEAD["abc300_e"] + "（diff 1354・参考値）：要約。", "diff 1354）"),
                           (HEAD["abc300_e"] + "（diff なし）：要約。", "diff 1354）"),
                           (HEAD["typical90_a"] + "（diff 1000）：要約。", "diff なし）")]:
            with self.subTest(line=line):
                e = errors(block(line))
                self.assertEqual([k for k, _ in e], ["台帳と違う（fix_problems.py で直せる）"])
                self.assertIn(f"（台帳から作ると {want}", e[0][1])


class FixTextTest(unittest.TestCase):
    def fix(self, line: str, indent: str = "") -> tuple[str, list[str], list[str]]:
        new, changes, problems = fp.fix_text(block(line, indent=indent), "basics/x.md", LEDGER)
        return new.split("\n")[2], changes, problems

    def test_rewrites_to_new_forms(self):
        # 要約（「：」の後ろ。かっこを含んでもよい）は変えない
        cases = [
            (HEAD["typical90_a"] + "（diff —）：要約（注）。", HEAD["typical90_a"] + "（diff なし）：要約（注）。"),
            (HEAD["abc014_4"] + "（diff 1856）：要約。", GOOD["abc014_4"]),
            (HEAD["abc014_4"] + "（diff 1856（参考値））：要約。", GOOD["abc014_4"]),
            (HEAD["abc300_e"] + "（diff 1354・参考値）：要約。", GOOD["abc300_e"]),
            ("- [なんでも](https://atcoder.jp/contests/abc014/tasks/abc014_4)：要約。", GOOD["abc014_4"]),
            ("- abc014_4：要約。", GOOD["abc014_4"]),
            ("- typical90_a（diff —）：要約。", GOOD["typical90_a"]),
        ]
        for before, after in cases:
            with self.subTest(before=before):
                line, changes, problems = self.fix(before)
                self.assertEqual(problems, [])
                self.assertEqual(line, after)
                self.assertEqual(len(changes), 1)

    def test_keeps_indent(self):
        line, changes, problems = self.fix(HEAD["typical90_a"] + "（diff —）：要約。", indent="    ")
        self.assertEqual((line, len(changes), problems), ("    " + GOOD["typical90_a"], 1, []))

    def test_idempotent(self):
        text = block(*GOOD.values())
        self.assertEqual(fp.fix_text(text, "basics/x.md", LEDGER), (text, [], []))

    def test_fence_untouched(self):
        text = "```text\n" + block(HEAD["typical90_a"] + "（diff —）：要約。") + "\n```"
        self.assertEqual(fp.fix_text(text, "basics/x.md", LEDGER), (text, [], []))


PAGE = """---
id: x
title: X
---

本文。

{block}
"""


class FixProblemsCliTest(unittest.TestCase):
    """--root・--ledger の一時の木で、--check の終了コードと書き換えを確かめる。"""

    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        root = Path(self.tmp.name)
        self.page = root / "docs" / "basics" / "x.md"
        self.page.parent.mkdir(parents=True)
        self.page.write_text(PAGE.format(block=block(HEAD["typical90_a"] + "（diff —）：要約。",
                                                     HEAD["abc014_4"] + "（diff 1856）：要約。",
                                                     GOOD["abc300_e"])), encoding="utf-8")
        self.ledger = root / "problems.yaml"
        self.ledger.write_text(yaml.safe_dump({"problems": list(LEDGER.values())}, allow_unicode=True), encoding="utf-8")
        self.args = [sys.executable, str(ROOT / "tools" / "fix_problems.py"), "--root", str(root), "--ledger", str(self.ledger)]

    def tearDown(self):
        self.tmp.cleanup()

    def run_tool(self, *extra: str) -> subprocess.CompletedProcess:
        return subprocess.run(self.args + list(extra), capture_output=True, text=True, encoding="utf-8")

    def test_check_then_fix(self):
        before = self.page.read_text(encoding="utf-8")
        r = self.run_tool("--check")
        self.assertEqual(r.returncode, 1, r.stdout + r.stderr)
        self.assertIn("直すべき行: 2（1 ファイル）", r.stdout)
        self.assertEqual(self.page.read_text(encoding="utf-8"), before)     # --check は書かない
        r = self.run_tool()
        self.assertEqual(r.returncode, 0, r.stdout + r.stderr)
        self.assertEqual(self.page.read_text(encoding="utf-8"),
                         PAGE.format(block=block(GOOD["typical90_a"], GOOD["abc014_4"], GOOD["abc300_e"])))
        r = self.run_tool("--check")
        self.assertEqual(r.returncode, 0, r.stdout + r.stderr)
        self.assertIn("直すべき行: 0（0 ファイル）", r.stdout)


if __name__ == "__main__":
    unittest.main()
