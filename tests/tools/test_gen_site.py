"""tools/gen_site.py の小さな試験：制約のサインの上限の読み方（#42）・英字の索引の小見出し（#45）・最近の ABC の表示名（#46）・
章の表の「一覧」（#49）。python3 -m unittest discover -s tests/tools"""
import sys
import tempfile
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[2] / "tools"))
import check_pages as cp  # noqa: E402
import gen_site as gs  # noqa: E402


class ConstraintBoundTest(unittest.TestCase):
    def test_words_after_number(self):
        # 「≤」がなくても、程度・以下・まで・個・回・級・規模 が続く数は上限として読む
        self.assertEqual(gs.constraint_bound("追加と取り出しが合わせて 2×10^5 回程度"), 2e5)
        self.assertEqual(gs.constraint_bound("クエリが 10^6 級で、1 回 O(1) で答えたい"), 1e6)
        self.assertEqual(gs.constraint_bound("文字列の個数が多く、長さの総和が 5×10^5 程度まで"), 5e5)
        self.assertEqual(gs.constraint_bound("式の長さが 2×10^5 程度で、括弧の入れ子が深くなりうる"), 2e5)
        self.assertEqual(gs.constraint_bound("テストケースが T 個あり、N の総和が 2×10^5 以下"), 2e5)
        self.assertEqual(gs.constraint_bound("座標が 10^9 規模の整数で、傾きや角度を比べる"), 1e9)

    def test_counts_before_values(self):
        self.assertEqual(gs.constraint_bound("座標が 10^9 まで・点とクエリが 2×10^5 個（2 次元累積和の表は作れない）"), 2e5)
        self.assertEqual(gs.constraint_bound("A_i < 2^30 で、追加・削除・質問が合わせて 2×10^5 回程度"), 2e5)
        self.assertEqual(gs.constraint_bound("値は 10^9 まであるが、個数は 2×10^5 以下"), 2e5)
        self.assertEqual(gs.constraint_bound("値が 10^9 まであり、配列の添字にできない"), 1e9)   # 値の上限しかなければ値で分ける

    def test_parentheses_last(self):
        # かっこの中の見積もりは読まない。外に同じ種類の数がなければ、かっこの中の上限を使う（帯をなくさない）
        self.assertEqual(gs.constraint_bound("状態数が 10^6〜10^7 程度に収まる（9! = 362880、60^4 ≈ 1.3×10^7）"), 1e7)
        self.assertEqual(gs.constraint_bound("N ≤ 2×10^5 では N^2 の隣接行列を持てない（N ≤ 2000 程度なら持てる）"), 2e5)
        self.assertEqual(gs.constraint_bound("一方の次元だけ極端に小さい（H ≤ 8 など）"), 8)
        self.assertEqual(gs.constraint_bound("K 回（K ≤ 10^18）移動した後の位置"), 1e18)
        self.assertEqual(gs.constraint_bound("A_i < 2^30〜2^60 で、全ペア（N ≤ 2×10^5）の値を集計する"), 2e5)

    def test_le_before_words(self):
        self.assertEqual(gs.constraint_bound("文字の種類 26 程度、|S| ≤ 2×10^5"), 2e5)
        self.assertEqual(gs.constraint_bound("M ≤ 1000 程度、N ≤ 100 程度"), 1000)       # 同じ形なら最初に書かれた数

    def test_ranges(self):
        self.assertEqual(gs.constraint_bound("N ≤ 16〜18（3^N ≈ 4×10^7〜4×10^8）"), 18)
        self.assertEqual(gs.constraint_bound("要素の数 N が 100〜数百程度で、選び方は 2^N 通りある"), 500)
        self.assertEqual(gs.constraint_bound("N, Q ≈ 2×10^5 で、制限時間が長めにとってある"), 2e5)

    def test_bare_ranges(self):
        # ≤ も後ろの語もない「a〜b」は上端を読む。ほかの書き方の数があれば、そちらを先に使う
        self.assertEqual(gs.constraint_bound("答えの範囲が 10^9〜10^18 と広い"), 1e18)
        self.assertEqual(gs.constraint_bound("パターンの長さの総和が 10^5〜10^6 で、パターンの個数も多い"), 1e6)
        self.assertEqual(gs.constraint_bound("頂点数が数百〜数千、辺数が 10^5 程度まで（フローが間に合う規模）"), 1e5)
        self.assertEqual(gs.constraint_bound("状態数 n ≤ 100 程度で、繰り返しの回数 K が 10^9〜10^18"), 100)
        self.assertEqual(gs.constraint_bound("線形漸化式の項数 K が数百〜数千で、N ≤ 10^18"), 1e18)

    def test_not_bounds(self):
        for text in ["比べ合うハッシュが 10^5 個以上（組が 5×10^9 以上）",
                     "余りや状態が M 種類しかなく、M + 1 個以上の候補がある",
                     "積・lcm・累乗が 10^18 を超えうる（long long の上限は約 9.2×10^18）",
                     "制限時間が長めで、O(N√N) ≈ 10^8 なら間に合う",
                     "実行時間制限が 5 秒など長い（重めの全探索が想定されている）",
                     "実行時間制限が 3〜5 秒と長い",                       # 単位の付いた範囲は読まない
                     "長さが 10^5〜10^6 以上ある",                        # 下限の範囲も読まない
                     "質問の回数は log2 N 程度"]:
            self.assertIsNone(gs.constraint_bound(text), text)


PAGE = """---
id: {id}
title: {title}
type: technique
field: {field}
order: {order}
level: 水
kind: [{kind}]
aliases: [{aliases}]
stage: draft
---

本文
"""


class SiteTest(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        docs = Path(self.tmp.name) / "docs"
        for field, pid, title, kind, aliases in [
            ("graph", "zero-one-bfs", "01-BFS", "グラフ探索", "0-1 BFS"),
            ("ds", "union-find", "Union-Find", "データ構造", "DSU, 素集合データ構造"),
            ("ds", "segment-tree", "セグメント木", "データ構造", "segtree, セグ木"),
        ]:
            path = docs / field / f"{pid}.md"
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_text(PAGE.format(id=pid, title=title, field=field, order=10, kind=kind, aliases=aliases), encoding="utf-8")
        recent = [{"id": "abc451_e", "position": "E", "title": "Tree Distance", "difficulty": 1215, "pages": ["union-find"]},
                  {"id": "abc452_e", "position": "E", "title": "You WILL Like Sigma Problem", "pages": ["union-find", "segment-tree"]}]
        pages, others = cp.load_docs(docs)
        self.site = gs.Site(docs, pages, others, {}, recent)

    def tearDown(self):
        self.tmp.cleanup()

    def test_terms_latin_headings(self):
        out = self.site.b_terms_latin("guide/term-index.md")
        lines = out.split("\n")
        self.assertEqual(lines[0], "[0〜9](#terms-latin-digits)・[D](#terms-latin-d)・[S](#terms-latin-s)・[U](#terms-latin-u)")
        heads = [x for x in lines if x.startswith("### ")]
        self.assertEqual(heads, ["### 0〜9 {#terms-latin-digits}", "### D {#terms-latin-d}", "### S {#terms-latin-s}",
                                 "### U {#terms-latin-u}"])
        self.assertLess(out.index("0-1 BFS"), out.index("### D "))
        self.assertLess(out.index("### S "), out.index("segtree"))

    def test_recent_labels(self):
        e = {"id": "abc451_d", "position": "D", "title": "Concat Power of 2 "}
        self.assertEqual(gs.Site.recent_label(e), "ABC451 D. Concat Power of 2")
        self.assertEqual(gs.Site.recent_label(e, short=True), "ABC451 D")
        self.assertEqual(gs.Site.recent_label({"id": "abc460_g"}), "ABC460 G")
        table = self.site.b_recent_abc("guide/problem-sets.md")
        self.assertIn("| ABC451 E. Tree Distance | E | 1215 |", table)
        self.assertNotIn("abc451_e", table)
        self.assertNotIn("atcoder.jp", table)
        pos = self.site.b_recent_positions("guide/roadmap.md")
        # 狭い画面でも「ABC451 E」を空白で 2 行に割らない。数字だけの問題数は最後の列（画面の右端で切れてよい列）
        self.assertIn("| 種類 | ページ | 問題 | 問題数 |", pos)
        self.assertIn("| ABC451&nbsp;E・ABC452&nbsp;E | 2 |", pos)
        self.assertNotIn("abc451_e", pos)

    def test_fields_has_lists_chapter(self):
        rows = self.site.b_fields("start/how-to-use.md").split("\n")
        self.assertEqual(rows[0], "| 章 | 中身 | ページ |")
        self.assertTrue(rows[-1].startswith("| [一覧](../lists/index.md) | レベル別の一覧 1 つと種類別の一覧 2 個"), rows[-1])
        self.assertTrue(rows[-1].endswith("| — |"))


if __name__ == "__main__":
    unittest.main()
