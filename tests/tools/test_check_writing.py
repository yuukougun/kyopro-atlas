"""書き方の検査（tools/check_pages.py の check_math_text・check_raw_math・check_plain_text・check_section_order・
check_strategy_titles。工程11、#68・#69）の試験。
python3 -m unittest discover -s tests/tools
Python-Markdown があれば（.venv の Python。CI は uv sync の後）、数式にならずに残る $ の数え方を、サイトと同じ拡張の
本物と乱択の文書で突き合わせる試験も走る。"""
import html.parser
import random
import sys
import tempfile
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
import check_pages as cp  # noqa: E402

try:
    import markdown
except ImportError:          # システムの Python には入っていないことがある
    markdown = None
try:
    from mkdocs.config import load_config
except ImportError:
    load_config = None


def page(body: str, rel: str = "basics/x.md", **meta) -> cp.Page:
    p = cp.Page(path=Path("docs") / rel, rel=rel, text=body)
    p.body = body
    p.meta = ({"id": Path(rel).stem, "type": "technique", "level": "水"} | meta) if meta is not None else None
    p.analyze()
    return p


def found(check, body: str, **meta) -> list[tuple[str, str, str]]:
    """(重さ E・W, 種類, 文) の列。"""
    rep = cp.Report()
    p = page(body, **meta)
    if check is cp.check_plain_text:
        check([p], [], {}, rep)
    else:
        check([p], rep)
    return [(sev, kind, msg) for sev, kind, _, msg in rep.items]


def leaked(body: str) -> int:
    """数式にならずに地の文に残る $ の数（text_runs と run_math のまね）。"""
    return sum(len(cp.run_math(r.text)[1]) for r in cp.text_runs(page(body)) if r.kind == "inline")


# (本文, 地の文に残る $ の数)。2026-10-29 に Python-Markdown 3.11（mkdocs.yml の拡張）で確かめた形
LEAK_CASES = [
    ("$S = $ `abc` から", 2),                         # 閉じの $ の前に空白（string-basics など）
    ("$S =$ `abc` と $S$ = `abc`", 0),
    ("$ x$ と $x $", 4),                              # 開きの $ の後・閉じの $ の前の空白
    ("$5 と $6", 2),
    ("価格 \\$5 と $x$", 0),                          # \$ は $ そのもの（数えない）
    ("`$S = $` はコード", 0),
    ("a $x\ny$ b", 0),                                # 段落の中の改行をまたぐ数式
    ("- a $x\n- y$ b", 2),                            # 箇条書きの項目はまたがない
    ("- a $x\n  y$ b", 0),                            # 項目の続きの行
    ("| $a | b$ |\n| --- | --- |\n| c | d |", 2),     # 表のセルはまたがない
    ("$a | b$\n| c |", 0),                            # 区切りの行がなければ表でない
    ("text\n$$\nx\n$$", 4),                           # 段落に続く $$（euler-phi の #formula）
    ("text\n\n$$\nx\n$$", 0),
    ("$$\nx\n$$\nafter", 4),                          # 後ろの行に続く $$
    ("$$\nx\n$$\n\nafter", 0),
    ("$$x = 1$$", 0),                                 # 1 行の別行の数式
    ("text\n$$x = 1$$", 2),
    ("## 見出し {#h}\n$$\nx\n$$", 0),                 # 見出しの後ろはブロックの始まり
    ("$$\nx\n$$\n## 見出し {#h}", 0),
    ('!!! note "題"\n    $$\n    x\n    $$\nafter', 0),   # 囲みの中身は字下げが浅くなれば終わる
    ('!!! note "題"\n    text\n    $$\n    x\n    $$', 4),
    ('!!! note "$x = $ y"\n    body', 2),            # 囲みの題も inline の塊
    ("```text\ncode $x\n```\n$$\nx\n$$", 4),          # フェンスの直後の $$
    ("<!-- c -->\n$$\nx\n$$", 0),                     # 行頭のコメントはブロックを分ける
    ("- a\n\n    $$\n    x\n    $$", 0),             # 箇条書きの項目の中の別行の数式
    ("- a\n\n    $$\n    x\n    $$\n- b", 4),        # 閉じの $$ の次の印は段落の続き
    ("- $$x$$", 0),                                   # 項目の中身が $$…$$
    ("text\n- $x$ と $", 1),                          # 段落の次の行の印は段落の続き
    ("> a $x\n> y$ b", 0),
    ("    $ x", 0),                                   # 字下げのコードのブロック
    ("a $x$$y$ b", 0),
    ("a $$ b", 2),
]


class LeakModelTest(unittest.TestCase):
    def test_cases(self):
        for body, n in LEAK_CASES:
            with self.subTest(body=body):
                self.assertEqual(leaked(body), n)

    def test_runs_and_positions(self):
        runs = cp.text_runs(page("段落 $a\nb$\n\n- 項目\n\n| x | y |\n| --- | --- |\n| 1 | 2 |"))
        self.assertEqual([(r.kind, r.role) for r in runs],
                         [("inline", "para"), ("inline", "item"), ("inline", "cell"), ("inline", "cell"),
                          ("inline", "cell"), ("inline", "cell")])
        self.assertEqual(runs[0].text, "段落 $a\nb$")
        self.assertEqual(runs[0].at(runs[0].text.index("b")), (1, 0))
        self.assertEqual([(r.parts[0][0], r.parts[0][2], r.text) for r in runs[2:4]], [(5, 1, " x "), (5, 5, " y ")])
        d = cp.text_runs(page("前\n\n$$\nx\n$$\n\n後"))
        self.assertEqual([r.kind for r in d], ["inline", "display", "inline"])

    def test_split_row(self):
        self.assertEqual([c for _, c in cp.split_row("| a | `b|c` | d |", True)], [" a ", " `b|c` ", " d "])
        self.assertEqual([c for _, c in cp.split_row("| a \\| b | c |", True)], [" a \\| b ", " c "])
        self.assertIsNotNone(cp.table_head(["| a | b |", "| --- | :-: |"]))
        self.assertIsNone(cp.table_head(["| a | b |", "| x | y |"]))
        self.assertIsNone(cp.table_head(["| a |"]))


class MathTextTest(unittest.TestCase):
    def kinds(self, body):
        return [(s, k) for s, k, _ in found(cp.check_math_text, body)]

    def test_leaked_dollar(self):
        e = found(cp.check_math_text, "一行目\n\n```text\n$S = $\n```\n\n$S = $ `ab`、$T = $ `cc` では")
        self.assertEqual([(s, k) for s, k, _ in e], [("E", "数式にならずに残る $")])
        self.assertIn("basics/x.md:7:", e[0][2])
        self.assertIn("$ が 4 個", e[0][2])
        e = found(cp.check_math_text, "包除原理から\n$$\n\\varphi(n)\n$$\nとなる")
        self.assertEqual(len(e), 2)                                    # 開きと閉じの $$ の行
        self.assertIn("basics/x.md:2:", e[0][2])
        self.assertIn("$$ の行の前後を空行にする", e[0][2])
        self.assertEqual(self.kinds("$x$ と $\\le$ と \\$5"), [])
        self.assertEqual(self.kinds("<!-- $S = $ -->\n\n`$S = $`"), [])

    def test_japanese_next_to_math(self):
        e = found(cp.check_math_text, "すると$p_i < p_{i+1}$ は（$-$最小, $-$最大）")
        self.assertEqual([(s, k) for s, k, _ in e], [("W", "和文に接した数式")] * 3)
        self.assertIn("の前が和文", e[0][2])
        self.assertIn("の後ろが和文", e[1][2])
        self.assertEqual(self.kinds("すると $p_i$ は、$x$。（$y$）・$z$・と「$w$」"), [])   # 空白・句読点・括弧・「・」の隣
        self.assertEqual(self.kinds("カタカナ$x$ー"), [("W", "和文に接した数式")])

    def test_mod_letter(self):
        e = found(cp.check_math_text, "割り算は $O(\\log \\mathrm{mod})$ で、$\\gcd(b, \\text{mod}) = 1$")
        self.assertEqual([(s, k) for s, k, _ in e], [("W", "法を表す mod の文字")])
        self.assertIn("\\mathrm{mod}・\\text{mod}", e[0][2])
        self.assertIn("（2 か所）", e[0][2])
        self.assertEqual(self.kinds("$\\mathrm{MOD}$ を足す"), [("W", "法を表す mod の文字")])
        self.assertEqual(self.kinds("$$\nx \\equiv y \\ (\\mathrm{mod}\\ k)\n$$"), [("W", "法を表す mod の文字")])
        # 「(\mathrm{mod}\ k)」は法の文字ではなく演算子の書き方：\pmod{k} にするよう出す。同じ行の法の文字とは分けて書く
        e = found(cp.check_math_text, "$P_t \\equiv P_i \\ (\\mathrm{mod}\\ k)$ と $\\left( \\mathrm{MOD} \\ 3 \\right)$ と $O(\\log \\mathrm{MOD})$")
        self.assertEqual(len(e), 1)
        self.assertIn("\\mathrm{mod}・\\mathrm{MOD} を「(\\mathrm{mod}\\ k)」の形の演算子に使っている（2 か所）（演算子の \\pmod{k} にする",
                      e[0][2])
        self.assertIn("数式の中の \\mathrm{MOD} を法の文字に使っている（法の文字は", e[0][2])
        self.assertEqual(self.kinds("$a \\bmod m$ と $a \\equiv b \\pmod{m}$ と $\\mathrm{mode}$"), [])
        self.assertEqual(self.kinds("`\\mathrm{mod}` と mod 998244353"), [])


class RawMathTest(unittest.TestCase):
    ABS = '!!! abstract "要点"\n    - **何ができるか**：…\n    - **いつ使うか**：\n        - {}\n\n導入'

    def words(self, line):
        return cp.raw_math_tokens(line)

    def test_tokens(self):
        self.assertEqual(self.words("N ≤ 2×10^5 で 3 つ組は N^3 通り"), ["2×10^5", "N^3"])
        self.assertEqual(self.words("X_i と Y_i は異なる値"), ["X_i", "Y_i"])
        self.assertEqual(self.words("dp\\[i][\\*] から"), ["dp\\[i][\\*]"])
        self.assertEqual(self.words("状態数が 10&#94;6 程度"), ["10^6"])
        self.assertEqual(self.words("Σ_{i=1}^{N} (Ai) mod M"), ["Σ_{i=1}^{N}"])
        self.assertEqual(self.words("3^(10^18) mod 7"), ["3^(10^18)"])
        self.assertEqual(self.words("A\\_i を足す"), ["A\\_i"])
        # 名前の _・コード・数式・リンクの行き先は見ない
        self.assertEqual(self.words("lower_bound・pb_ds・Min_25 篩・unordered_map"), [])
        self.assertEqual(self.words("`a_i` と $A_i$ と $10^6$ と [BIT](../ds/fenwick_tree.md)"), [])
        self.assertEqual(self.words("2 乗・x の 2 倍・XOR（^）"), [])

    def test_abstract_and_titles(self):
        e = found(cp.check_raw_math, self.ABS.format("N ≤ 2×10^5 で N^3 通り"))
        self.assertEqual([(s, k) for s, k, _ in e], [("W", "要点・題の素の数式")])
        self.assertIn("basics/x.md:4:", e[0][2])
        self.assertIn("「2×10^5」「N^3」", e[0][2])
        self.assertEqual(found(cp.check_raw_math, self.ABS.format("$N \\le 2 \\times 10^5$ で $N^3$ 通り")), [])
        e = found(cp.check_raw_math, '??? question "確認問題：3^(10^18) mod 7"\n    答え\n\n!!! note "長さ 2^17 の列"\n    a')
        self.assertEqual(len(e), 2)
        self.assertIn("囲み・折りたたみの題", e[0][2])
        self.assertEqual(found(cp.check_raw_math, '??? question "確認問題：$3^{10^{18}} \\bmod 7$"\n    答え'), [])
        self.assertEqual(found(cp.check_raw_math, "本文の 10^6 は見ない（本文は数式にならずに残る $ の検査で見る）"), [])

    def test_big_o_in_titles(self):
        # 題の素の計算量 O(…) は対のかっこまでを語にする。数式・コードの中と、要点の囲み・本文は見ない
        self.assertEqual(self.words("全体が O(N log N) で、O((N + Q) log N) になる", ), [])
        self.assertEqual(cp.raw_math_tokens("全体が O(N log N) で、O((N + Q) log N) になる", big_o=True),
                         ["O(N log N)", "O((N + Q) log N)"])
        self.assertEqual(cp.raw_math_tokens("O(N^2) と N^2", big_o=True), ["O(N^2)"])
        self.assertEqual(cp.raw_math_tokens("$O(N)$ と `O(1)` と BigO(1) と FOO(x)", big_o=True), [])
        e = found(cp.check_raw_math, '??? question "確認問題：全体が O(N) なのはなぜか"\n    答え')
        self.assertEqual(len(e), 1)
        self.assertIn("「O(N)」", e[0][2])
        self.assertEqual(found(cp.check_raw_math, '??? question "確認問題：全体が $O(N)$ なのはなぜか"\n    答え'), [])
        self.assertEqual(found(cp.check_raw_math, self.ABS.format("全体で O(N)")), [])
        self.assertEqual(found(cp.check_raw_math, "本文の O(N) は見ない"), [])


class PlainTextTest(unittest.TestCase):
    def test_front_matter(self):
        e = found(cp.check_plain_text, "本文", summary="Σ_{i=1}^{N} ⌊N/i⌋ を O(√N) で求める。", complexity="O(N^{1/4})",
                  signs=[{"type": "phrase", "text": "N^(1/4) と A_(i+1) と 10^18 と d_i^2"}],
                  sections=[{"title": "endl と '\\n'", "anchor": "endl"}, {"title": "x \\le y", "anchor": "le"}],
                  aliases=["Σ_{i=1}^{N}"])
        msgs = [m for _, _, m in e]
        self.assertEqual(len(msgs), 3)
        self.assertIn("front matter の summary に「_{」「^{」", msgs[0])
        self.assertIn("front matter の complexity に「^{」", msgs[1])
        self.assertIn("front matter の sections[1].title に「\\le」", msgs[2])

    def test_problem_lines_and_ledger(self):
        body = ('<div class="kp-problems" data-role="practice" markdown>\n\n'
                "- [ABC230 E. Fraction Floor Sum](https://atcoder.jp/contests/abc230/tasks/abc230_e)（diff 1271）："
                "Σ_{i=1}^{N} ⌊N/i⌋ を求める。\n"
                "- [ABC001 A. x](https://atcoder.jp/contests/abc001/tasks/abc001_a)（diff 100）：`$` と $H \\le 16$ の和を求める。\n"
                "- [ABC001 B. y](https://atcoder.jp/contests/abc001/tasks/abc001_b)（diff 100）：i = 1..N の ⌊N/i⌋ の和を求める。\n"
                "\n</div>")
        rep = cp.Report()
        ledger = {"abc230_e": {"summary": "Σ_{i=1}^{N} ⌊N/i⌋ を求める（N ≤ 10^12）。", "approach": "商の列挙",
                               "alternatives": [{"pages": ["x"], "summary": "i = 1..N の ⌊N/i⌋ の和を求める。"},
                                                {"pages": ["x", "none"], "approach": "−Σ_{d|N} μ(N/d) F(d) とする"}]},
                  "abc001_b": {"summary": "x", "approach": "M^{d(M)/2} を求める"}}
        cp.check_plain_text([page(body)], [], ledger, rep)
        got = [(keys, m) for _, _, keys, m in rep.items]
        self.assertEqual(len(got), 5)
        self.assertIn("basics/x.md:3: abc230_e の問題の行の要約に「_{」「^{」", got[0][1])
        self.assertIn("abc001_a の問題の行の要約に「$」「\\le」", got[1][1])            # コードの中の $ は数えない
        self.assertIn("data/problems.yaml: abc230_e の summary", got[2][1])
        self.assertEqual(got[2][0], frozenset({"data/problems.yaml", "basics/x.md"}))
        self.assertIn("abc230_e の alternatives[1].approach に「_{」", got[3][1])      # ページごとの言い回し
        self.assertEqual(got[3][0], frozenset({"data/problems.yaml", "basics/x.md"}))
        self.assertIn("abc001_b の approach に「^{」", got[4][1])


def sec(*names):
    """h2 の列の本文。名前は anchor（定型）か「c:anchor」（中身の節）。"""
    out = []
    for n in names:
        if n.startswith("c:"):
            out.append(f"## 中身 {n[2:]} {{#{n[2:]}}}\n\n本文\n")
        else:
            out.append(f"## {cp.SECTION_NAMES[n]} {{#{n}}}\n\n本文\n")
    return "\n".join(out)


class SectionOrderTest(unittest.TestCase):
    def warns(self, body, **meta):
        return [m for _, _, m in found(cp.check_section_order, body, **meta)]

    def test_technique(self):
        ok = sec("c:a", "c:up", "c:b", "pitfalls", "examples", "practice", "challenge", "quiz", "comparison", "references")
        self.assertEqual(self.warns(ok), [])
        w = self.warns(sec("c:a", "pitfalls", "quiz", "comparison", "examples", "practice", "references"))
        self.assertEqual(len(w), 1)
        self.assertIn("今は 落とし穴 → 確認問題 → 使い分け → 例題 → 練習問題 → 参考", w[0])
        self.assertIn("手引きの順は 落とし穴 → 例題 → 練習問題 → 確認問題 → 使い分け → 参考", w[0])
        self.assertIn("basics/x.md:9:", w[0])                       # 最初にずれた節（確認問題）の行
        w = self.warns(sec("c:a", "pitfalls", "c:late", "examples", "comparison", "c:up", "references"))
        self.assertEqual(len(w), 1)
        self.assertIn("中身の節 {#late}・{#up} が最初の定型の節（落とし穴）より後ろ", w[0])

    def test_basic_next_steps(self):
        ok = sec("c:a", "pitfalls", "next-steps", "examples", "practice", "comparison", "references")
        self.assertEqual(self.warns(ok, level="基礎"), [])
        w = self.warns(sec("c:a", "next-steps", "pitfalls", "comparison", "examples", "references"), level="基礎")
        self.assertIn("今は 上位の手法へのつながり → 落とし穴 → 使い分け → 例題 → 参考", w[0])
        # technique ならどの帯でも next-steps は定型（落とし穴の直後、例題の前）
        for level in ("水", "青", "黄"):
            self.assertEqual(self.warns(sec("c:a", "pitfalls", "next-steps", "examples", "references"), level=level), [])
        w = self.warns(sec("c:a", "pitfalls", "examples", "next-steps", "references"), level="青")
        self.assertIn("今は 落とし穴 → 例題 → 上位の手法へのつながり → 参考", w[0])
        # technique 以外では中身の節（定型の順に入れない）
        self.assertEqual(self.warns(sec("c:a", "examples", "next-steps", "references"), type="overview", level="発展"), [])
        # §17-4 の同じ役の中身の節は next-steps の位置
        body = sec("c:a", "pitfalls", "c:to-lazy-segment-tree", "examples", "references")
        self.assertEqual([m for _, _, m in found(cp.check_section_order, body, id="global-offset", level="基礎")], [])
        self.assertEqual([m for _, _, m in found(cp.check_section_order, body, id="global-offset", level="水")], [])

    def test_other_types(self):
        # technique 以外は定型の節の相対順だけを見る（中身の節はどこでもよい）
        ok = sec("c:a", "c:library", "resources", "c:b", "examples", "practice", "comparison", "references")
        self.assertEqual(self.warns(ok, type="overview", level="発展"), [])
        w = self.warns(sec("c:a", "comparison", "resources", "practice", "references"), type="overview", level="発展")
        self.assertIn("今は 使い分け → 学ぶための資料 → 練習問題 → 参考", w[0])
        self.assertEqual(self.warns(sec("c:a", "examples", "c:b", "comparison"), type="thinking", level="基礎"), [])
        w = self.warns(sec("pitfalls", "quiz", "challenge", "references"), type="hub", level=None)
        self.assertIn("今は 落とし穴 → 確認問題 → 力試し → 参考", w[0])
        # 定型の anchor を別の見出しで使ってよい節（roadmap の practice）は中身の節
        body = "## 色ごとの練習 {#practice}\n\n本文\n\n## 参考 {#references}\n"
        self.assertEqual([m for _, _, m in found(cp.check_section_order, "## 使い分け {#comparison}\n\n" + body,
                                                  id="roadmap", type="guide", level=None)], [])


class StrategyTitleTest(unittest.TestCase):
    def warns(self, body, **meta):
        return [m for _, _, m in found(cp.check_strategy_titles, body, **meta)]

    def test_titles(self):
        body = ("## 例題 {#examples}\n\n??? note \"方針\"\n    a\n\n"
                "## 練習問題 {#practice}\n\n??? note \"練習の方針\"\n    a\n\n??? note \"練習の方針（ABC142 E）\"\n    a\n\n"
                "??? note \"方針\"\n    a\n\n??? tip \"練習問題の方針\"\n    a\n\n??? note \"ヒント\"\n    a\n\n"
                "## 力試し {#challenge}\n\n??? note \"力試しの方針\"\n    a\n\n??? note \"方針（ABC195 F）\"\n    a\n\n"
                "```text\n??? note \"方針\"\n```\n")
        w = self.warns(body)
        self.assertEqual(len(w), 3)
        self.assertIn("練習問題の節の折りたたみの題「方針」は「練習の方針」にする", w[0])
        self.assertIn("「練習問題の方針」は「練習の方針」", w[1])
        self.assertIn("「方針（ABC195 F）」は「力試しの方針（ABC195 F）」にする", w[2])


class CheckAllTest(unittest.TestCase):
    def test_kinds_through_check_all(self):
        with tempfile.TemporaryDirectory() as d:
            docs = Path(d) / "docs"
            (docs / "basics").mkdir(parents=True)
            text = ("---\nid: x\ntitle: x\ntype: technique\nfield: basics\nlevel: 水\nsummary: Σ_{i=1}^{N} を求める。\n---\n\n"
                    '!!! abstract "要点"\n    - N ≤ 2×10^5\n\n本文の $S = $ `a`。\n\n## 使い分け {#comparison}\n\n'
                    "a\n\n## 例題 {#examples}\n\nb\n")
            (docs / "basics" / "x.md").write_text(text, encoding="utf-8")
            pages, others = cp.load_docs(docs)
            rep = cp.Report()
            cp.check_all(pages, others, rep, {}, cp.load_validator(), Path(d) / "snippets", set(), docs)
            kinds = {k for _, k, _, _ in rep.items}
            for k in ("数式にならずに残る $", "要点・題の素の数式", "平文の欄の TeX の記号", "節の並び"):
                self.assertIn(k, kinds)
            self.assertIn("basics/x.md:13:", next(m for _, k, _, m in rep.items if k == "数式にならずに残る $"))


class _Text(html.parser.HTMLParser):
    """HTML の地の文（code・pre・script・arithmatex の外）の $ を数える。"""

    def __init__(self):
        super().__init__(convert_charrefs=True)
        self.stack, self.n = [], 0

    def handle_starttag(self, tag, attrs):
        if tag in ("br", "img", "hr", "input"):
            return
        cls = (dict(attrs).get("class") or "").split()
        self.stack.append((tag, tag in ("code", "pre", "script", "style") or "arithmatex" in cls))

    def handle_endtag(self, tag):
        for k in range(len(self.stack) - 1, -1, -1):
            if self.stack[k][0] == tag:
                del self.stack[k:]
                break

    def handle_data(self, data):
        if not any(s for _, s in self.stack):
            self.n += data.count("$")


def escaped_dollars(body: str) -> int:
    """\\$（$ そのもの）の数。本物の HTML では地の文の $ として数えられる。"""
    n = 0
    for r in cp.text_runs(page(body)):
        if r.kind != "inline":
            continue
        t = cp.replace_each(cp.MD_MATH_RE, cp.mask_code(r.text), lambda m: "\x02" * len(m.group(0)))
        for k, c in enumerate(t):
            if c == "$":
                b = k
                while b > 0 and t[b - 1] == "\\":
                    b -= 1
                n += (k - b) % 2
    return n


TOKENS = ["a", "あ", " ", " ", "$", "$x$", "$S = $", "`c`", "`$`", "\\$", "\\\\", "$$", "\\(y\\)", "x_i", "(", ")", "$ ", " $"]


def para(rnd: random.Random) -> str:
    s = "".join(rnd.choice(TOKENS) for _ in range(rnd.randint(1, 8))).strip() or "a"
    return s.replace("```", "`` `")          # 行頭の ``` はフェンスの開きになる（閉じないフェンスはまねない）


def indent(text: str, k: int) -> str:
    return "\n".join((" " * k + x) if x else x for x in text.split("\n"))


def block(rnd: random.Random, depth: int = 0) -> str:
    c = rnd.randrange(19)
    p = lambda: para(rnd)  # noqa: E731
    return [
        lambda: p(),
        lambda: p() + "\n" + p(),
        lambda: "- " + p() + "\n- " + p(),
        lambda: "- " + p() + "\n  " + p(),
        lambda: "- " + p() + "\n    - " + p(),
        lambda: '!!! note "' + p().replace('"', "") + '"\n    ' + p(),
        lambda: '??? question "' + p().replace('"', "") + '"\n    ' + p() + "\n\n    " + p(),
        lambda: "## " + p() + " {#h" + str(rnd.randrange(99)) + "}",
        lambda: "| " + p().replace("|", "") + " | " + p().replace("|", "") + " |\n| --- | --- |\n| " + p() + " | b |",
        lambda: "$$\n" + rnd.choice(["x = 1", "\\sum_i a_i", "y"]) + "\n$$",
        lambda: "```text\ncode $x\n```",
        lambda: "<!-- c $ -->",
        lambda: "> " + p() + "\n> " + p(),
        lambda: "$$" + rnd.choice(["x", "a + b", " y "]) + "$$",
        lambda: "- " + p() + "\n\n" + indent(block(rnd, depth + 1) if depth < 2 else p(), 4)
        + rnd.choice(["\n- " + p(), "\n\n- " + p(), ""]),
        lambda: '??? note "t"\n' + indent(block(rnd, depth + 1) if depth < 2 else p(), 4)
        + rnd.choice(["\n" + p(), "\n\n" + p(), ""]),
        lambda: '<div class="kp-problems" data-role="practice" markdown>\n\n- ' + p() + "\n\n</div>",
        lambda: p() + "\n" + rnd.choice(["## h $x$ {#q}", "| a | b |\n| --- | --- |", "> " + p(), "$$\nx\n$$", "- " + p(),
                                         "<!-- c -->", "```text\nc\n```"]),
        lambda: rnd.choice(["- ", '!!! note "t"\n    ']) + p() + rnd.choice(["\n\n", "\n"]) + "    $$\n    " + p()
        + "\n    $$" + rnd.choice(["\n\n", "\n"]) + rnd.choice([p(), "- " + p(), "    " + p()]),
    ][c]()


def document(rnd: random.Random) -> str:
    out = []
    for _ in range(rnd.randint(1, 5)):
        out += [block(rnd), rnd.choice(["\n\n", "\n\n", "\n"])]
    return "".join(out).rstrip("\n")


@unittest.skipUnless(markdown, "Python-Markdown がない（.venv の Python で走らせる）")
class AgainstPythonMarkdownTest(unittest.TestCase):
    """サイトと同じ拡張の Python-Markdown の HTML の地の文に残る $ の数と、検査のまね（＋ \\$ の数）が一致するか。"""

    @classmethod
    def setUpClass(cls):
        if load_config is not None:
            cfg = load_config(config_file=str(ROOT / "mkdocs.yml"))
            cls.md = markdown.Markdown(extensions=cfg["markdown_extensions"], extension_configs=cfg["mdx_configs"])
        else:
            cls.md = markdown.Markdown(
                extensions=["admonition", "attr_list", "md_in_html", "tables", "pymdownx.arithmatex", "pymdownx.details",
                            "pymdownx.inlinehilite", "pymdownx.superfences"],
                extension_configs={"pymdownx.arithmatex": {"generic": True}})

    def real(self, body: str) -> int:
        self.md.reset()
        p = _Text()
        p.feed(self.md.convert(body))
        return p.n

    def test_cases(self):
        for body, n in LEAK_CASES:
            with self.subTest(body=body):
                self.assertEqual(self.real(body), n + escaped_dollars(body))

    def test_random_documents(self):
        rnd = random.Random(20261029)
        for _ in range(600):
            body = document(rnd)
            with self.subTest(body=body):
                self.assertEqual(self.real(body), leaked(body) + escaped_dollars(body))


if __name__ == "__main__":
    unittest.main()
