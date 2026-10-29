"""tools/fix_code_links.py（コードの下の完全なプログラムへのリンクの行・mint の注記・地の文の snippets/… のリンク。
Issue #8・#72・#62）の試験。python3 -m unittest discover -s tests/tools
Python-Markdown と pymdownx があれば（.venv の Python。CI は uv sync の後）、作った行がコードの塊と同じ入れ物の
<p class="kp-code-src"> になることも本物で確かめる。"""
import contextlib
import io
import sys
import tempfile
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
import fix_code_links as fcl  # noqa: E402

try:
    import markdown
    import pymdownx  # noqa: F401
except ImportError:          # システムの Python には入っていないことがある
    markdown = None

URL = "https://github.com/yuukougun/kyopro-atlas/blob/main/snippets/"
FM = "---\nid: x\nstage: draft\n---\n"

SNIPPETS = {
    "x/a.cpp": "#include <bits/stdc++.h>\nusing namespace std;\n// --8<-- [start:core]\nint f(int v) { return v + 1; }\n"
               "// --8<-- [end:core]\n// --8<-- [start:other]\nint g(int v) { return v; }\n// --8<-- [end:other]\n"
               "int main() {}\n",
    "x/m.cpp": "#include <atcoder/modint>\nusing namespace std;\nusing mint = atcoder::modint998244353;\n"
               "// --8<-- [start:core]\nmint twice(mint v) { return v * 2; }\n// --8<-- [end:core]\n"
               "// --8<-- [start:plain]\nint h() { return 0; }\n// --8<-- [end:plain]\nint main() { mint z = 1; }\n",
    "x/p.cpp": "#include <atcoder/modint>\nusing mint = atcoder::modint1000000007;\n// --8<-- [start:core]\n"
               "mint one() { return 1; }\n// --8<-- [end:core]\nint main() {}\n",
    "x/q.cpp": "// mint は自作の型\n// --8<-- [start:core]\nmint q();\n// --8<-- [end:core]\nint main() {}\n",
    "x/b.cpp": "int b() { return 2; }\nint main() {}\n",
    "y/a.cpp": "int a2() { return 3; }\nint main() {}\n",
}


def fence(ref: str, indent: str = "") -> str:
    return f"{indent}```cpp\n{indent}--8<-- \"{ref}\"\n{indent}```\n"


def line(names: str, indent: str = "", note: str = "") -> str:
    return f"\n{indent}完全なプログラム：{names}（GitHub）{note}\n{indent}{{ .kp-code-src }}\n"


def link(path: str, name: str | None = None) -> str:
    return f"[`{name or path.rsplit('/', 1)[-1]}`]({URL}{path})"


NOTE_998 = "。`mint` は ACL の `modint998244353`（[modint](../math/modint.md)）。"


class Base(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.snip = Path(self.tmp.name) / "snippets"
        for rel, text in SNIPPETS.items():
            f = self.snip / rel
            f.parent.mkdir(parents=True, exist_ok=True)
            f.write_text(text, encoding="utf-8")

    def tearDown(self):
        self.tmp.cleanup()

    def fix(self, body: str, rel: str = "basics/x.md") -> fcl.Result:
        return fcl.fix_text(FM + body, rel, self.snip)

    def body(self, body: str, rel: str = "basics/x.md") -> str:
        r = self.fix(body, rel)
        self.assertEqual(r.problems, [])
        self.assertTrue(r.text.startswith(FM))
        return r.text[len(FM):]

    def assertStable(self, body: str, rel: str = "basics/x.md"):
        """2 回目は変わらない（道具の行を読み戻して作り直しても同じ）。"""
        once = self.fix(body, rel).text
        twice = fcl.fix_text(once, rel, self.snip)
        self.assertEqual(twice.text, once)
        self.assertEqual((twice.added, twice.updated, twice.removed, twice.mentions), (0, 0, 0, 0))


class LineTest(Base):
    def test_basic(self):
        src = "前の文。\n\n" + fence("x/a.cpp:core") + "\n後の文。\n"
        out = self.body(src)
        self.assertEqual(out, "前の文。\n\n" + fence("x/a.cpp:core") + line(link("x/a.cpp")) + "\n後の文。\n")
        self.assertStable(src)
        r = self.fix(src)
        self.assertEqual((r.added, r.lines, r.fences, r.notes), (1, 1, 1, 0))

    def test_indent_in_admonition_tabs_and_list(self):
        for ind, head in (("    ", '??? note "解法の詳細"\n    説明。\n\n'), ("    ", '=== "C++"\n\n'), ("    ", "- 項目\n\n")):
            with self.subTest(head=head):
                src = head + fence("x/a.cpp:core", ind) + "\n後の文。\n"
                self.assertEqual(self.body(src), head + fence("x/a.cpp:core", ind) + line(link("x/a.cpp"), ind) + "\n後の文。\n")
                self.assertStable(src)

    def test_adjacent_same_file_once(self):
        src = fence("x/a.cpp:core") + "\n" + fence("x/a.cpp:other") + "\n後。\n"
        out = self.body(src)
        self.assertEqual(out, fence("x/a.cpp:core") + "\n" + fence("x/a.cpp:other") + line(link("x/a.cpp")) + "\n後。\n")
        self.assertEqual(self.fix(src).lines, 1)
        self.assertStable(src)

    def test_prose_between_gets_each(self):
        src = fence("x/a.cpp:core") + "\n間の文。\n\n" + fence("x/a.cpp:other") + "\n"
        out = self.body(src)
        self.assertEqual(out.count("{ .kp-code-src }"), 2)
        self.assertStable(src)

    def test_adjacent_different_files_and_indents(self):
        src = fence("x/a.cpp:core") + "\n" + fence("x/b.cpp") + "\n"
        self.assertEqual(self.body(src).count("{ .kp-code-src }"), 2)
        src = fence("x/a.cpp:core") + "\n" + fence("x/a.cpp:other", "    ") + "\n"
        self.assertEqual(self.body(src).count("{ .kp-code-src }"), 2)

    def test_two_includes_in_one_fence(self):
        src = "```cpp\n--8<-- \"x/a.cpp:core\"\n\n--8<-- \"x/a.cpp:other\"\n```\n"
        self.assertEqual(self.body(src), src + line(link("x/a.cpp")))
        src = "```cpp\n--8<-- \"x/a.cpp:core\"\n--8<-- \"y/a.cpp\"\n```\n"
        self.assertEqual(self.body(src), src + line(link("x/a.cpp", "x/a.cpp") + "・" + link("y/a.cpp", "y/a.cpp")))

    def test_block_form_and_escape(self):
        src = "```cpp\n--8<--\nx/a.cpp:core\nx/b.cpp\n--8<--\n```\n"
        self.assertEqual(self.body(src), src + line(link("x/a.cpp") + "・" + link("x/b.cpp")))
        src = "```cpp\n;--8<-- \"x/a.cpp:core\"\n```\n"
        self.assertEqual(self.body(src), src)

    def test_not_cpp_and_comment(self):
        for src in ("```text\n--8<-- \"x/a.cpp:core\"\n```\n",
                    "<!--\n" + fence("x/a.cpp:core") + "-->\n",
                    "````markdown\n" + fence("x/a.cpp:core") + "````\n"):
            with self.subTest(src=src):
                self.assertEqual(self.body(src), src)

    def test_no_blank_after_and_end_of_file(self):
        src = fence("x/a.cpp:core") + "後の文。\n"
        self.assertEqual(self.body(src), fence("x/a.cpp:core") + line(link("x/a.cpp")) + "\n後の文。\n")
        self.assertStable(src)
        src = fence("x/a.cpp:core").rstrip("\n")
        self.assertEqual(self.body(src), src + "\n" + line(link("x/a.cpp")).rstrip("\n"))
        self.assertStable(src)


class MintTest(Base):
    def test_note_from_using(self):
        self.assertEqual(self.body(fence("x/m.cpp:core")), fence("x/m.cpp:core") + line(link("x/m.cpp"), note=NOTE_998))
        note = "。`mint` は ACL の `modint1000000007`（[modint](../math/modint.md)）。"
        self.assertEqual(self.body(fence("x/p.cpp:core")), fence("x/p.cpp:core") + line(link("x/p.cpp"), note=note))
        self.assertEqual(self.fix(fence("x/m.cpp:core")).notes, 1)

    def test_only_shown_range(self):
        # mint はファイルにあるが、取り込む範囲 plain には出ない
        self.assertEqual(self.body(fence("x/m.cpp:plain")), fence("x/m.cpp:plain") + line(link("x/m.cpp")))
        # 行の範囲（3〜5 行目に using mint と twice がある）とファイル全体
        self.assertIn("modint998244353", self.body(fence("x/m.cpp:3:5")))
        self.assertNotIn("`mint`", self.body(fence("x/m.cpp:8:8")))
        self.assertIn("modint998244353", self.body(fence("x/m.cpp")))

    def test_run_merges_note(self):
        src = fence("x/m.cpp:plain") + "\n" + fence("x/m.cpp:core") + "\n"
        self.assertEqual(self.body(src).count(NOTE_998), 1)

    def test_link_forms(self):
        self.assertIn("（[modint](math/modint.md)）", self.body(fence("x/m.cpp:core"), rel="index.md"))
        self.assertIn("（[modint](../math/modint.md)）", self.body(fence("x/m.cpp:core"), rel="math/fps.md"))
        self.assertNotIn("`mint` は", self.body(fence("x/m.cpp:core"), rel=fcl.MODINT_REL))

    def test_type_names(self):
        self.assertEqual(fcl.mint_note("atcoder::modint", "a/b.md", "modint"), "`mint` は ACL の `modint`（[modint](../math/modint.md)）。")
        self.assertEqual(fcl.mint_note("modint998244353", "a/b.md", "modint"), "`mint` は ACL の `modint998244353`（[modint](../math/modint.md)）。")
        self.assertEqual(fcl.mint_note("atcoder::static_modint<17>", "a/b.md", "modint"),
                         "`mint` は ACL の `static_modint<17>`（[modint](../math/modint.md)）。")
        self.assertEqual(fcl.mint_note("ModInt<998244353>", "a/b.md", "modint"), "`mint` は `ModInt<998244353>`（[modint](../math/modint.md)）。")

    def test_unknown_type_is_a_problem(self):
        r = self.fix(fence("x/q.cpp:core"))
        self.assertEqual(len(r.problems), 1)
        self.assertIn("using mint", r.problems[0])
        self.assertNotIn("`mint` は", r.text)


class StaleTest(Base):
    def test_update_and_remove(self):
        src = fence("x/b.cpp") + line(link("x/a.cpp")) + "\n後。\n"
        r = self.fix(src)
        self.assertEqual((r.added, r.updated, r.removed), (0, 1, 0))
        self.assertEqual(r.text, FM + fence("x/b.cpp") + line(link("x/b.cpp")) + "\n後。\n")
        # 取り込みがなくなったフェンスの下・離れたところの行は消す
        src = "```text\nx\n```\n" + line(link("x/a.cpp")) + "\n文。\n" + line(link("x/a.cpp")) + "\n後。\n"
        r = self.fix(src)
        self.assertEqual((r.added, r.removed), (0, 2))
        self.assertEqual(r.text, FM + "```text\nx\n```\n\n文。\n\n後。\n")
        # 続きになったので、前のフェンスの下の行を消す
        src = fence("x/a.cpp:core") + line(link("x/a.cpp")) + "\n" + fence("x/a.cpp:other") + "\n"
        r = self.fix(src)
        self.assertEqual((r.added, r.removed), (1, 1))
        self.assertEqual(r.text.count("{ .kp-code-src }"), 1)

    def test_lines_inside_fences_are_kept(self):
        src = "```markdown\n完全なプログラム：x\n{ .kp-code-src }\n```\n"
        self.assertEqual(self.body(src), src)

    def test_problem_lines(self):
        r = self.fix("前。\n\n" + fence("x/none.cpp:core") + "\n" + fence("x/a.cpp:nothere"))
        self.assertEqual(len(r.problems), 2)
        self.assertIn("basics/x.md:8:", r.problems[0])          # 取り込みの行（front matter の 4 行を足したファイルの行）
        self.assertIn("[start:nothere]", r.problems[1])
        self.assertEqual(r.text.count("{ .kp-code-src }"), 1)    # ファイルはあるので行は置く


class MentionTest(Base):
    def test_link(self):
        src = "完全なプログラムは `snippets/x/a.cpp` で、`snippets/x/` と `snippets/` もある。\n"
        tree = "https://github.com/yuukougun/kyopro-atlas/tree/main/snippets"
        self.assertEqual(self.body(src), f"完全なプログラムは [`snippets/x/a.cpp`]({URL}x/a.cpp) で、"
                         f"[`snippets/x/`]({tree}/x) と [`snippets/`]({tree}) もある。\n")
        self.assertStable(src)
        self.assertEqual(self.fix(src).mentions, 3)

    def test_skip(self):
        for src in (f"もう [`snippets/x/a.cpp`]({URL}x/a.cpp) にある。\n",
                    "```text\n`snippets/x/a.cpp`\n```\n",
                    "<!--\n`snippets/x/a.cpp`\n-->\n",
                    "$$\n`snippets/x/a.cpp`\n$$\n",
                    "`snippets` と `snippets/README.md` と `x/a.cpp`\n"):
            with self.subTest(src=src):
                r = self.fix(src)
                self.assertEqual(r.text, FM + src)

    def test_existing_links_are_checked(self):
        src = "古い [`snippets/x/a.cpp`](https://github.com/yuukougun/kyopro-atlas/blob/dev/snippets/x/a.cpp) へ。\n"
        r = self.fix(src)
        self.assertEqual(r.text, FM + f"古い [`snippets/x/a.cpp`]({URL}x/a.cpp) へ。\n")
        self.assertEqual(r.mentions, 1)
        r = self.fix(f"消えた [`snippets/x/gone.cpp`]({URL}x/gone.cpp) へ。\n")
        self.assertEqual(len(r.problems), 1)
        self.assertIn("リンクの先", r.problems[0])
        # ほかのサイトへのリンクの文字の中なら見ない
        src = "[`snippets/x/gone.cpp`](https://example.com/x) へ。\n"
        self.assertEqual(self.body(src), src)

    def test_problems(self):
        for src in ("## 見出し `snippets/x/a.cpp`\n", "`snippets/x/a.cpp` <!-- c -->\n", "`snippets/x/none.cpp`\n"):
            with self.subTest(src=src):
                r = self.fix(src)
                self.assertEqual(r.text, FM + src)
                self.assertEqual(len(r.problems), 1)


class CliTest(Base):
    def run_main(self, *args) -> tuple[int, str]:
        out = io.StringIO()
        old = sys.argv
        sys.argv = ["fix_code_links.py", *args]
        try:
            with contextlib.redirect_stdout(out), contextlib.redirect_stderr(io.StringIO()):
                try:
                    fcl.main()
                    code = 0
                except SystemExit as e:
                    code = e.code if isinstance(e.code, int) else 1
        finally:
            sys.argv = old
        return code, out.getvalue()

    def test_check_write_check(self):
        root = Path(self.tmp.name)
        page = root / "docs" / "basics" / "x.md"
        page.parent.mkdir(parents=True)
        page.write_text(FM + fence("x/m.cpp:core"), encoding="utf-8")
        code, out = self.run_main("--root", str(root), "--check")
        self.assertEqual(code, 1)
        self.assertIn("+++ b/docs/basics/x.md", out)
        self.assertIn("+{ .kp-code-src }", out)
        self.assertEqual(page.read_text(encoding="utf-8"), FM + fence("x/m.cpp:core"))     # --check は書かない
        code, out = self.run_main("--root", str(root), "--check", "--stat")
        self.assertEqual(code, 1)
        self.assertNotIn("+++", out)
        self.assertEqual(self.run_main("--root", str(root))[0], 0)
        self.assertIn(NOTE_998, page.read_text(encoding="utf-8"))
        self.assertEqual(self.run_main("--root", str(root), "--check")[0], 0)
        self.assertEqual(self.run_main("--root", str(root), "--check", "--page", "x")[0], 0)


@unittest.skipIf(markdown is None, "Python-Markdown と pymdownx がない")
class RenderTest(Base):
    """作った行が、コードの塊の後ろの同じ入れ物の <p class="kp-code-src"> になる（空行がないとコードごと段落に入る）。"""

    def render(self, text: str) -> str:
        md = markdown.Markdown(
            extensions=["admonition", "attr_list", "md_in_html", "pymdownx.details", "pymdownx.highlight",
                        "pymdownx.superfences", "pymdownx.snippets", "pymdownx.tabbed"],
            extension_configs={"pymdownx.snippets": {"base_path": [str(self.snip)], "check_paths": True,
                                                     "dedent_subsections": True},
                               "pymdownx.tabbed": {"alternate_style": True}})
        return md.convert(text)

    def test_paragraph(self):
        src = ("前。\n\n" + fence("x/m.cpp:core") + "\n後。\n\n"
               '??? note "解法の詳細"\n    説明。\n\n' + fence("x/a.cpp:core", "    ") + "\n"
               '=== "C++"\n\n' + fence("x/a.cpp:core", "    ") + "\n=== \"B\"\n\n    b\n")
        html = self.render(self.body(src))
        self.assertEqual(html.count('<p class="kp-code-src">'), 3)
        self.assertNotIn('<p class="kp-code-src"><div', html)
        self.assertNotIn("{ .kp-code-src }", html)
        self.assertIn('<code>mint</code> は ACL の <code>modint998244353</code>', html)
        details = html[html.index("<details"):html.index("</details>")]
        self.assertIn('<p class="kp-code-src">', details)
        first = html.index('class="tabbed-block"')
        tab = html[first:html.index('class="tabbed-block"', first + 1)]      # 1 つ目のタブの中身
        self.assertIn('<p class="kp-code-src">', tab)
        # 空行を挟まないと、コードの塊ごと段落に入る（置くときに空行を入れる理由）
        bad = self.render(fence("x/a.cpp:core") + "完全なプログラム：x\n{ .kp-code-src }\n")
        self.assertIn('<p class="kp-code-src"><div', bad)


if __name__ == "__main__":
    unittest.main()
