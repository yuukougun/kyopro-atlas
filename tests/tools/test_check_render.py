"""描画の崩れの検査（tools/check_pages.py の check_rendering：#50・#51・#61、tools/check_svg.py の背景：#61）の試験。
python3 -m unittest discover -s tests/tools
Python-Markdown があれば（.venv の Python。CI は uv sync の後）、代替テキストの数え方を本物と突き合わせる試験も走る。"""
import random
import re
import sys
import tempfile
import unittest
import xml.etree.ElementTree as ET
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
import check_pages as cp  # noqa: E402
import check_svg as cs  # noqa: E402

try:
    import markdown
except ImportError:          # システムの Python には入っていないことがある
    markdown = None
try:
    from mkdocs.config import load_config
except ImportError:
    load_config = None


def page(body: str) -> cp.Page:
    p = cp.Page(path=Path("docs/basics/x.md"), rel="basics/x.md", text=body)
    p.body = body
    p.analyze()
    return p


def found(body: str, viz_dir: Path | None = None) -> list[tuple[str, str, str]]:
    """(重さ E・W, 種類, 文) の列。"""
    rep = cp.Report()
    cp.check_rendering([page(body)], rep, viz_dir)
    return [(sev, kind, msg) for sev, kind, _, msg in rep.items]


def images_made(line: str) -> int:
    return sum(ok for _, ok, _ in cp.md_images(cp.md_inline_mask(line)))


# (1 行, 画像になる数)。#50 の形と、エスケープ・数式・コードの中の [ ]、先に作られる link、link の文字の中の画像
IMAGE_CASES = [
    ("![区間 [1, 5) に +1](x.svg)", 0),
    ("![区間 \\[1, 5) に +1](x.svg)", 1),
    ("![区間 $[1, 5)$ に +1](x.svg)", 1),
    ("![区間 `[1, 5)` に +1](x.svg)", 1),
    ("![閉区間 [1, 5] の和](x.svg)", 1),
    ("![区間 (l, r]](x.svg)", 0),
    ("![区間 (l, r\\]](x.svg)", 1),
    ("![a [b](c) d](e.svg)", 1),
    ("![a \\\\[b) d](e.svg)", 0),
    ("![区間 [1, 5)](x.svg) と閉区間の右端 (l, r]", 0),
    ("![x](a.svg) と ![区間 [1, 5)](b.svg)", 1),
    ("[![区間 \\[1, 5)](x.svg)](y.md)", 1),
    ("![a](x (1).svg)", 1),
    ("![a](x.svg", 0),
    ("![a $\\\\`](x.svg) ($", 1),
    ("![区間 \\(a[\\)](x.svg)", 1),
]


class ImageBracketTest(unittest.TestCase):
    def test_cases(self):
        for line, n in IMAGE_CASES:
            with self.subTest(line=line):
                self.assertEqual(images_made(line), n)

    def test_errors(self):
        e = found("![区間 [1, 5) に +1](../img/x/a.svg)")
        self.assertEqual([(s, k) for s, k, _ in e], [("E", "画像の代替テキストの角括弧")])
        self.assertIn("閉じない [ がある", e[0][2])
        self.assertIn("\\[ にエスケープ", e[0][2])
        self.assertIn("basics/x.md:1:", e[0][2])
        e = found("![区間 (l, r]](../img/x/a.svg)")
        self.assertIn("途中の ] で閉じる", e[0][2])
        self.assertIn("\\] にエスケープ", e[0][2])
        self.assertIn("( が閉じない", found("![a](x.svg")[0][2])
        self.assertEqual(len(found("![a](x.svg) と ![区間 [1, 5)](b.svg) と ![c [d)](e.svg)")), 2)

    def test_errors_with_text_after(self):
        # 後ろの ] や ][ で代替テキストが閉じても、図のファイルの場所が画像にならなければ崩れ（verify-f1-tools の A1）
        for line in ["![区間 [1, 5)](x.svg) と閉区間の右端 (l, r]",
                     "![区間 [1, 5) の図](x.svg)。左が開いた (l, r] も同じ",
                     "![区間 [1, 5)](x.svg) と ![区間 (2, 6]](y.svg)",
                     "![(l, r][1, 5)](x.svg)",
                     "[![区間 [1, 5)](x.svg)](y.md)"]:
            with self.subTest(line=line):
                self.assertEqual(len(found(line)), 1)

    def test_not_images_and_code(self):
        self.assertEqual(found("![区間 \\[1, 5) に +1](x.svg)"), [])
        self.assertEqual(found("![図][ref] と ![注意] は画像のつもりとみなさない"), [])
        self.assertEqual(found("![注意] は [リンク](x.md) を見る"), [])                # 図のファイルを指さない（A2）
        self.assertEqual(found("答えは 5 だ![^1] 詳しくは [解説](x.md)"), [])
        self.assertEqual(found("![区間 \\[1, 5)\nの図](x.svg)"), [])                  # 行をまたぐ代替テキストは見ない
        self.assertEqual(found("- [解説（画像）](https://example.com/a.jpg)：図の解説"), [])   # ![ のない行の図へのリンク
        self.assertEqual(found("`![区間 [1, 5)](x.svg)` と書くと崩れる"), [])
        self.assertEqual(found("```text\n![区間 [1, 5)](x.svg)\n```"), [])
        self.assertEqual(found("<!-- ![区間 [1, 5)](x.svg) -->"), [])
        self.assertEqual(found("<!--\n![区間 [1, 5)](x.svg)\n-->"), [])

    def test_line_numbers(self):
        e = found("一行目\n\n```text\n![a [b](c)\n```\n\n![区間 [1, 5)](x.svg)")
        self.assertEqual(len(e), 1)
        self.assertIn("basics/x.md:7:", e[0][2])

    def test_code_spans(self):
        self.assertEqual(cp.md_code_spans("`a` と `b`"), [(0, 3), (6, 9)])
        self.assertEqual(cp.md_code_spans("``a`b``"), [(0, 7)])
        self.assertEqual(cp.md_code_spans("``a`"), [(0, 4)])            # 同じ長さの閉じがなければ最長の列で閉じる
        self.assertEqual(cp.md_code_spans("\\`a`"), [])                 # 奇数個の \ の後の ` は開きでない
        self.assertEqual(cp.md_code_spans("\\\\`a`"), [(0, 2), (2, 5)])  # 偶数個の \ はエスケープした \ になる
        self.assertEqual(cp.md_code_spans("`a"), [])


@unittest.skipUnless(markdown, "Python-Markdown がない（.venv の Python で走らせる）")
class AgainstPythonMarkdownTest(unittest.TestCase):
    """サイトと同じ拡張の Python-Markdown が作る <img> の数と、検査のまねが一致するか。"""

    @classmethod
    def setUpClass(cls):
        if load_config is not None:          # mkdocs.yml と同じ拡張・設定（MkDocs があるとき）
            cfg = load_config(config_file=str(ROOT / "mkdocs.yml"))
            cls.md = markdown.Markdown(extensions=cfg["markdown_extensions"], extension_configs=cfg["mdx_configs"])
        else:
            cls.md = markdown.Markdown(
                extensions=["attr_list", "md_in_html", "tables", "pymdownx.arithmatex", "pymdownx.inlinehilite",
                            "pymdownx.superfences"],
                extension_configs={"pymdownx.arithmatex": {"generic": True}})

    def real(self, line: str) -> int:
        self.md.reset()
        return self.md.convert(line).count("<img")

    def test_cases(self):
        for line, n in IMAGE_CASES:
            with self.subTest(line=line):
                self.assertEqual(self.real(line), n)

    def test_random_lines(self):
        tokens = ["a", "区間", " ", "[", "]", "\\[", "\\]", "\\\\", "`", "``", "$", "$[1, 5)$", "(", ")", "1, 5",
                  "\\", "!", "\\(", "\\)", "![b](y.svg)", "[l](u)", "](z.svg)"]
        rnd = random.Random(20261029)
        for _ in range(400):
            line = "![" + "".join(rnd.choice(tokens) for _ in range(rnd.randint(1, 10)))
            if re.fullmatch(r"\s*(\$\$.+\$\$|\\\[.+\\\])\s*", line):     # 段落全体が別行の数式のブロック
                continue
            with self.subTest(line=line):
                self.assertEqual(images_made(line), self.real(line))


class VizTest(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.viz = Path(self.tmp.name)
        (self.viz / "ok.js").write_text("", encoding="utf-8")

    def tearDown(self):
        self.tmp.cleanup()

    def test_missing_script(self):
        e = found('<div class="kp-viz" data-viz="missing" data-config=\'{"a": [1, 2], "b": "x>y"}\'></div>', self.viz)
        self.assertEqual([(s, k) for s, k, _ in e], [("E", "動く図のスクリプトがない")])
        self.assertIn("overrides/assets/js/viz/missing.js がない", e[0][2])

    def test_ok_and_ignored(self):
        self.assertEqual(found('<div class="kp-viz" data-viz="ok" data-config=\'{"n": 3}\'></div>', self.viz), [])
        self.assertEqual(found('<div class="note" data-viz="missing"></div>', self.viz), [])       # viz.js が取り付けない
        self.assertEqual(found('```html\n<div class="kp-viz" data-viz="missing"></div>\n```', self.viz), [])
        self.assertEqual(found('`<div class="kp-viz" data-viz="missing">`', self.viz), [])
        self.assertEqual(found('<div class="kp-viz" data-viz="missing"></div>', None), [])         # 置き場が分からない

    def test_bad_name(self):
        e = found('<div class="kp-viz wide" data-viz="Bad_Name"></div>', self.viz)
        self.assertEqual(len(e), 1)
        self.assertIn("名前の形", e[0][2])

    def test_tag_over_lines(self):
        e = found('前の段落\n\n<div class="kp-viz"\n     data-viz="missing"\n     data-config=\'{"n": 3}\'></div>', self.viz)
        self.assertEqual(len(e), 1)
        self.assertIn("basics/x.md:3:", e[0][2])
        self.assertEqual(found('<DIV CLASS="kp-viz" DATA-VIZ="ok"></DIV>', self.viz), [])

    def test_root_without_overrides(self):
        # --root の木に overrides/assets/js/viz がなければ、動く図の検査は飛ばす（verify-f1-tools の B1）
        with tempfile.TemporaryDirectory() as d:
            docs = Path(d) / "docs"
            (docs / "basics").mkdir(parents=True)
            body = '<div class="kp-viz" data-viz="missing"></div>\n'
            (docs / "basics" / "x.md").write_text(body, encoding="utf-8")
            pages, others = cp.load_docs(docs)
            rep = cp.Report()
            cp.check_all(pages, others, rep, {}, cp.load_validator(), Path(d) / "snippets", set(), docs)
            self.assertNotIn("動く図のスクリプトがない", [k for _, k, _, _ in rep.items])
            (Path(d) / cp.VIZ_DIR_REL).mkdir(parents=True)
            rep = cp.Report()
            cp.check_all(pages, others, rep, {}, cp.load_validator(), Path(d) / "snippets", set(), docs)
            self.assertIn("動く図のスクリプトがない", [k for _, k, _, _ in rep.items])


class TextInMathTest(unittest.TestCase):
    def kinds(self, body):
        return [(s, k) for s, k, _ in found(body)]

    def test_dollar_in_text(self):
        err = [("E", "インラインの数式の \\text の中の $")]
        self.assertEqual(self.kinds("$X_i = [\\text{$i$ が条件を満たす}]$ とおく"), err)
        self.assertEqual(self.kinds("表の $E[L \\cdot [\\text{$v$ にいる}]]$ を運ぶ"), err)
        self.assertEqual(self.kinds("$\\textbf{箱 $i$ が空}$"), err)
        self.assertEqual(self.kinds("$P(\\text{$i$ 回目}) \\cdot P(\\text{$i - 1$ 回目})$"), err * 2)

    def test_allowed(self):
        self.assertEqual(self.kinds("$X_i = [i \\text{ が条件を満たす}]$"), [])
        self.assertEqual(self.kinds("$$\\sum_{\\text{$S$ の部分集合}} x$$"), [])                # 別行の数式
        self.assertEqual(self.kinds("$$\n\\sum_{\\text{$S$ の部分集合}} x\n$$"), [])
        self.assertEqual(self.kinds("$\\text{価格 \\$100}$"), [])
        self.assertEqual(self.kinds("`$\\text{$i$}$` は崩れる"), [])
        self.assertEqual(self.kinds("$\\textstyle x$ と $\\operatorname{lcm}(a, b)$"), [])

    def test_long_text(self):
        warn = [("W", "インラインの数式の長い \\text")]
        self.assertEqual(self.kinds("高さを $\\min(B, \\text{法が 1 になるまでの段数より数段多い段数})$ に縮める"), warn)
        self.assertEqual(self.kinds("$\\mathrm{mask}[v] = (\\text{ちょうど } v \\text{ で終わるパターンの bit}) "
                                    "\\mathbin{\\text{OR}} \\mathrm{mask}[\\mathrm{link}(v)]$"), warn)     # 塊に 17 字
        self.assertEqual(self.kinds("$X_v = [v \\text{ が自分の属する成分で番号が最小}]$"), [])               # 15.5 字
        self.assertEqual(self.kinds("$\\text{" + "あ" * 16 + "}$"), [])                                        # 段落は 16.0 字まで
        self.assertEqual(self.kinds("$\\text{" + "あ" * 16 + "a}$"), warn)
        self.assertEqual(self.kinds("$$\\text{法が 1 になるまでの段数より数段多い段数}$$"), [])

    def test_long_text_by_box(self):
        # 箇条書き・囲みの中は幅が違う（verify-f1-tools の C1。HEAD の aho-corasick:142 は箇条書きの中の 15 字で 25px 溢れた）
        warn = [("W", "インラインの数式の長い \\text")]
        num = "$\\mathrm{num}[v] = (\\text{ちょうど } v \\text{ で終わるパターンの数}) + \\mathrm{num}[\\mathrm{link}(v)]$"
        self.assertEqual(self.kinds("- 個数：" + num + "。"), warn)                        # 箇条書き 1 段は 14.5 字まで
        self.assertEqual(self.kinds("個数：" + num + "。"), [])                            # 段落なら 15 字は収まる
        t = lambda n: "$\\text{" + "あ" * n + "}$"
        self.assertEqual(self.kinds("- a\n    - " + t(13)), warn)                          # 2 段は 12.9 字まで
        self.assertEqual(self.kinds("- a\n    - " + t(12)), [])
        self.assertEqual(self.kinds("- a\n\n    続きの段落 " + t(15)), warn)                # 項目の中の段落も 1 段
        self.assertEqual(self.kinds("- a\n\n続きでない段落 " + t(15)), [])
        self.assertEqual(self.kinds('!!! note "題"\n    ' + t(18)), [])                     # 囲みの中は文字が小さく 18.5 字まで
        self.assertEqual(self.kinds('!!! note "題"\n    ' + t(19)), warn)
        self.assertEqual(self.kinds("??? note\n    - " + t(17)), warn)                     # 囲みの中の箇条書きは 17.0 字まで
        self.assertEqual(self.kinds("??? note\n    - " + t(16)), [])
        self.assertEqual(self.kinds("| " + t(20) + " | a |\n| --- | --- |"), [])            # 表は表の中で横に送れる
        e = found("- 個数：" + num)
        self.assertIn("箇条書き 1 段の幅 298px では 14.5 字まで", e[0][2])

    def test_long_text_chunks_and_scripts(self):
        warn = [("W", "インラインの数式の長い \\text")]
        a, b = "\\text{" + "あ" * 9 + "}", "\\text{" + "い" * 9 + "}"
        self.assertEqual(self.kinds(f"${a} = {b}$"), [])                                   # = の後で折り返せる
        self.assertEqual(self.kinds(f"$({a}) \\cdot ({b})$"), [])
        self.assertEqual(self.kinds(f"$({a}, {b})$"), warn)                                # コンマでは折り返さない
        self.assertEqual(self.kinds(f"$\\left({a} + {b}\\right)$"), warn)                # \\left … \\right の中も
        self.assertEqual(self.kinds(f"${{{a} + {b}}}$"), warn)                              # {} の中も
        self.assertEqual(self.kinds(f"$-{a} {b}$"), warn)                                  # 単項の − では折り返さない
        self.assertEqual(self.kinds("$2^{(\\text{" + "あ" * 20 + "})}$"), [])               # 指数の中は 0.7 倍
        self.assertEqual(self.kinds("$2^{\\text{" + "あ" * 24 + "}}$"), warn)
        self.assertEqual(self.kinds("$\\frac{\\text{" + "あ" * 20 + "}}{\\text{" + "い" * 20 + "}}$"), [])
        self.assertEqual(self.kinds("$\\dfrac{\\text{" + "あ" * 17 + "}}{x}$"), warn)

    def test_boxes(self):
        p = page("段落\n- 項目\n    - 入れ子\n    項目の続き\n!!! note \"題\"\n    囲み\n    - 囲みの箇条書き\n| 表 |\n> 引用\n"
                 "```text\n- コード\n```\n=== \"タブ\"\n    タブの中")
        got = [None if b is None else (round(b[0], 1), b[1], b[2]) for b in cp.line_boxes(p)]
        self.assertEqual(got[:9], [(328.0, 16.0, "段落"), (298.0, 16.0, "箇条書き 1 段"), (268.0, 16.0, "箇条書き 2 段"),
                                   (298.0, 16.0, "箇条書き 1 段"), (301.0, 12.8, "囲み"), (301.0, 12.8, "囲み"),
                                   (277.0, 12.8, "囲みの中の箇条書き 1 段"), None, (312.0, 16.0, "引用")])
        self.assertEqual(got[13], (328.0, 16.0, "段落"))                                  # タブは幅を変えない
        self.assertAlmostEqual(cp.text_room(328, 16), 16.04, places=2)

    def test_chunks_and_extent(self):
        self.assertEqual(cp.math_chunks("a = b + c"), ["a =", " b +", " c"])
        self.assertEqual(cp.math_chunks("-a + b"), ["-a +", " b"])
        self.assertEqual(cp.math_chunks("(a, -b) \\le c"), ["(a, -b) \\le", " c"])
        self.assertEqual(cp.math_chunks("{a + b} = c"), ["{a + b} =", " c"])
        self.assertEqual(cp.math_chunks("\\left(a + b\\right) x"), ["\\left(a + b\\right) x"])
        self.assertEqual(cp.math_chunks("a \\mathbin{\\text{OR}} b"), ["a \\mathbin{\\text{OR}}", " b"])
        self.assertEqual(cp.math_chunks("\\text{a = b} = c"), ["\\text{a = b} =", " c"])
        self.assertEqual(cp.text_extent("\\text{ab あ}"), 2.5)
        self.assertAlmostEqual(cp.text_extent("2^{\\text{あいう}}"), 2.1)
        self.assertAlmostEqual(cp.text_extent("2^\\text{あいう}"), 2.1)
        self.assertAlmostEqual(cp.text_extent("x_{a_{\\text{あい}}}"), 1.0)                # 2 段目から 0.5 倍
        self.assertAlmostEqual(cp.text_extent("\\frac{\\text{あいう}}{\\text{あ}}"), 2.1)   # 上と下の大きいほう
        self.assertAlmostEqual(cp.text_extent("\\dfrac{\\text{あいう}}{x}"), 3.0)
        self.assertEqual(cp.text_extent("x \\"), 0.0)                                    # 末尾の \\ で落ちない

    def test_inline_math_spans(self):
        self.assertEqual([(a, b) for a, b, _ in cp.inline_math("a $x$ b $y$")], [(2, 4), (8, 10)])
        self.assertEqual(cp.inline_math("$ x$"), [])                          # 空白の前の $ は開きでない
        self.assertEqual(len(cp.inline_math("\\$100 と $x$")), 1)
        self.assertEqual([t for _, _, t in cp.inline_math("$f(\\text{a $b$ c})$")], [[(3, "\\text", "a $b$ c")]])
        self.assertEqual(cp.text_width("ab あ"), 2.5)


def svg_warnings(src: str) -> list[str]:
    with tempfile.TemporaryDirectory() as d:
        f = Path(d) / "a.svg"
        f.write_text(src, encoding="utf-8")
        warns, err = cs.check(f)
    assert err is None, err
    return [w for w in warns if "背景" in w]


def svg(view: str, body: str, size: str = 'width="280" height="276"') -> str:
    return f'<svg xmlns="http://www.w3.org/2000/svg" viewBox="{view}" {size}>{body}<text x="10" y="20" font-size="14">a</text></svg>'


class SvgBackgroundTest(unittest.TestCase):
    def test_not_covering(self):
        w = svg_warnings(svg("300 0 280 276", '<rect width="100%" height="100%" fill="#ffffff"/>'))
        self.assertEqual(len(w), 1)
        self.assertIn("右 300", w[0])
        self.assertIn('<rect x="300" y="0" width="280" height="276" fill="#ffffff"/>', w[0])
        w = svg_warnings(svg("0 0 400 239", '<rect width="400" height="232" fill="#ffffff"/>', 'width="400" height="239"'))
        self.assertIn("下 7", w[0])
        w = svg_warnings(svg("8 0 310 344", '<rect x="0" y="0" width="640" height="320" fill="#ffffff"/>'))
        self.assertIn("下 24", w[0])
        self.assertNotIn("左", w[0])

    def test_covering(self):
        self.assertEqual(svg_warnings(svg("300 0 280 276", '<rect x="300" y="0" width="280" height="276" fill="#fff"/>')), [])
        self.assertEqual(svg_warnings(svg("0 0 280 276", '<rect width="100%" height="100%" fill="white"/>')), [])
        self.assertEqual(svg_warnings(svg("0 0 405 292", '<g transform="translate(0 12)"><rect x="0" y="-12" '
                                          'width="405" height="292" fill="#ffffff"/></g>')), [])
        self.assertEqual(svg_warnings(svg("0 0 280 276", '<g fill="#FFF"><rect width="280" height="276"/></g>')), [])
        self.assertEqual(svg_warnings(svg("0 0 280 276", '<rect width="280" height="276" style="fill: #ffffff"/>')), [])
        self.assertEqual(svg_warnings(svg("10 0 280 276", '<rect x="10" width="100%" height="100%" fill="#fff"/>')), [])
        self.assertEqual(svg_warnings('<svg xmlns="http://www.w3.org/2000/svg" width="200" height="100">'
                                      '<rect width="200" height="100" fill="#fff"/></svg>'), [])     # viewBox なし

    def test_first_white_rect_and_skips(self):
        # defs の中は描かれない。最初の白い rect が背景で、後ろの白い箱は見ない
        self.assertEqual(svg_warnings(svg("0 0 280 276", '<defs><rect width="1" height="1" fill="#fff"/></defs>'
                                          '<rect width="280" height="276" fill="#fff"/>'
                                          '<rect x="10" y="10" width="20" height="20" fill="#fff"/>')), [])
        # translate 以外の transform の中は調べない
        self.assertEqual(svg_warnings(svg("0 0 280 276", '<g transform="scale(2)"><rect width="140" height="138" '
                                          'fill="#fff"/></g>')), [])
        w = svg_warnings(svg("0 0 280 276", '<rect width="280" height="276" fill="#f4f4f4"/>'))
        self.assertIn("白い背景の rect がない", w[0])

    def test_length(self):
        self.assertEqual(cs.length(None, 100), 0.0)
        self.assertEqual(cs.length("50%", 300), 150.0)
        self.assertEqual(cs.length("-12", 300), -12.0)
        self.assertEqual(cs.length("1e1px", 300), 10.0)
        self.assertIsNone(cs.length("2em", 300))
        root = ET.fromstring(svg("0 0 280 276", '<rect width="280" height="276" fill="#fff"/>'))
        self.assertIsNone(cs.background_gaps(root, (0, 0, 280, 276)))


if __name__ == "__main__":
    unittest.main()
