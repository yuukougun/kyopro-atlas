"""tools/gen_site.py の小さな試験：制約のサインの上限の読み方（#42）・英字の索引の小見出し（#45）・最近の ABC の表示名（#46）・
章の表の「一覧」（#49）・問題番号の索引（#6）・ホームの目的別の入口（#7）・分野の入口（#58・#65・#75）。
python3 -m unittest discover -s tests/tools"""
import re
import sys
import tempfile
import unittest
from pathlib import Path
from unittest import mock

import yaml

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


# 問題番号の索引・入口の試験の問題（どれも data/problems.yaml の確認済みの問題。題名と difficulty は台帳のとおり）
LEDGER = {e["id"]: e for e in [
    {"id": "abc006_4", "contest": "abc006", "index": "D", "title": "トランプ挿入ソート", "difficulty": 1696},
    {"id": "abc174_e", "contest": "abc174", "index": "E", "title": "Logs", "difficulty": 1227},
    {"id": "abc451_e", "contest": "abc451", "index": "E", "title": "Tree Distance", "difficulty": 1215},
    {"id": "arc005_3", "contest": "arc005", "index": "C", "title": "器物損壊！高橋君", "difficulty": 1503},
    {"id": "agc001_e", "contest": "agc001", "index": "E", "title": "BBQ Hard", "difficulty": None},
    {"id": "typical90_a", "contest": "typical90", "index": "001", "title": "Yokan Party（★4）", "difficulty": None},
    {"id": "dp_a", "contest": "dp", "index": "A", "title": "Frog 1", "difficulty": None},
    {"id": "abl_d", "contest": "abl", "index": "D", "title": "Flat Subsequence", "difficulty": 1283},
]}


def problems(role: str, *qids: str) -> str:
    lines = [f'<div class="kp-problems" data-role="{role}" markdown>', ""]
    for q in qids:
        e = LEDGER[q]
        lines.append(f"- [{cp.problem_label(e)}]({cp.problem_url(e)})（diff {cp.diff_text(e)}）：要約")
    return "\n".join(lines + ["", "</div>"])


def example(q: str) -> str:
    return f"### {cp.problem_label(LEDGER[q])} {{#{q}}}\n\n" + problems("example", q)


class EntrancesTest(unittest.TestCase):
    """問題番号の索引（#6）・ホームの目的別の入口（#7）・分野の入口（#58・#65・#75）。"""

    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        docs = Path(self.tmp.name) / "docs"
        pages = [
            # (分野, id, 題名, 章, レベル, kind, 本文)
            ("start", "how-to-use", "この教材の使い方", None, None, ["案内"], "## 辞書としての引き方 {#lookup}\n\n## 色ごとに学ぶとき {#by-color}\n\n"
             "## レベルの意味 {#levels}"),
            ("guide", "problem-sets", "問題集と練習用コンテストの案内", None, None, ["案内"],
             "## 最近の ABC → ページ {#recent-abc}\n\n## 問題集の問題 → ページ {#sets-to-pages}\n\n"
             "<!-- gen:begin problem-sets -->\n<!-- gen:end problem-sets -->"),
            ("guide", "thinking-checklist", "詰まったときの発想リスト", None, None, ["案内"], "本文"),
            ("guide", "reverse-index-signs", "逆引き辞典（言い回しから）", None, None, ["案内"],
             "## 言い回しから引く {#by-phrase}\n\n## 題材から引く {#by-topic}"),
            ("patterns", "interval", "区間", None, None, ["案内"], "本文"),
            ("basics", "binary-search-answer", "答えで二分探索", "二分探索", "水", ["二分探索"],
             "## 例題 {#examples}\n\n" + example("typical90_a") + "\n\n## 練習問題 {#practice}\n\n" + problems("practice", "abc174_e", "abc451_e")),
            ("dp", "dp-basics", "DP の基本", "DP の考え方", "基礎", ["DP"],
             "## 例題 {#examples}\n\n" + example("dp_a") + "\n\n" + example("abc174_e")),
            ("dp", "tree-dp", "木 DP", "木の DP", "水", ["DP", "木"], "本文"),
            ("graph", "bfs", "BFS", "基本と探索", "基礎", ["グラフ探索", "最短路"], "本文"),
            ("graph", "zero-one-bfs", "01-BFS", "最短路", "水", ["最短路"], "## 例題 {#examples}\n\n" + example("arc005_3")),
            ("graph", "dijkstra", "ダイクストラ法", "最短路", "基礎", ["最短路"], "本文"),
            ("tree", "tree-basics", "木の基本", "木の基礎", "基礎", ["木"], "本文"),
            ("comb", "lattice-paths", "格子路の数え上げ", None, "基礎", ["数え上げ"],
             "## 力試し {#challenge}\n\n" + problems("challenge", "agc001_e")),
            ("ds", "segment-tree-on-values", "値を添字にする BIT・セグメント木", None, "水", ["データ構造"],
             "## 練習問題 {#practice}\n\n" + problems("practice", "abl_d", "abc006_4")),
            ("thinking", "complement", "余事象", None, "基礎", ["考察"], "本文"),
        ]
        for i, (field, pid, title, chapter, level, kind, body) in enumerate(pages):
            secs = [{"title": t, "anchor": a} for t, a in re.findall(r"^## (.+?) \{#([a-z0-9-]+)\}$", body, flags=re.M)]
            fm = {"id": pid, "title": title, "type": "guide" if level is None else "technique", "field": field, "order": 10 * (i + 1),
                  "level": level, "kind": kind, "summary": f"{title}で引ける（かっこ。の中）。2 文目。", "stage": "draft", "sections": secs}
            if chapter:
                fm["chapter"] = chapter
            path = docs / field / f"{pid}.md"
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_text("---\n" + yaml.safe_dump(fm, allow_unicode=True, sort_keys=False) + "---\n\n" + body + "\n", encoding="utf-8")
        recent = [{"id": "abc451_e", "position": "E", "title": "Tree Distance", "difficulty": 1215, "pages": ["binary-search-answer"]}]
        pages_, others = cp.load_docs(docs)
        self.site = gs.Site(docs, pages_, others, LEDGER, recent)

    def tearDown(self):
        self.tmp.cleanup()

    def test_index_parts(self):
        self.assertEqual(self.site.index_parts, {"abc": ["abc006_4", "abc174_e", "abc451_e"], "arc": ["arc005_3"], "agc": ["agc001_e"],
                                                 "sets": ["typical90_a", "dp_a"], "other": ["abl_d"]})

    def test_index_line_example_first(self):
        # 練習のページ（ナビゲーションで先）より、例題のページを先に出す。例題は小見出し、練習は一覧の節へ跳ぶ。リンクは atcoder.jp に張らない
        self.assertEqual(self.site.index_line("guide/problem-index.md", "abc174_e"),
                         "- ABC174 E. Logs → [DP の基本](../dp/dp-basics.md#abc174_e)（例題）、"
                         "[答えで二分探索](../basics/binary-search-answer.md#practice)（練習）")

    def test_index_abc_headings(self):
        out = self.site.b_problem_index_abc("guide/problem-index.md")
        lines = out.split("\n")
        self.assertEqual(lines[0], "[001〜049](#abc-001)・[150〜199](#abc-150)・[450〜451](#abc-450)")
        self.assertEqual([x for x in lines if x.startswith("### ")],
                         ["### ABC001〜ABC049 {#abc-001}", "### ABC150〜ABC199 {#abc-150}", "### ABC450〜ABC451 {#abc-450}"])
        # 最近の ABC の表の回を含む小見出しにだけ、その表への 1 文を添える
        self.assertEqual(out.count("最近の ABC → ページ"), 1)
        self.assertIn("### ABC450〜ABC451 {#abc-450}\n\nABC451 の E（1 問）は、本文に載せていない問題も"
                      "[最近の ABC → ページ](problem-sets.md#recent-abc)の表で", out)
        self.assertLess(out.index("ABC006 D."), out.index("ABC174 E."))

    def test_index_other_parts(self):
        host = "guide/problem-index.md"
        sets = self.site.b_problem_index_sets(host)
        self.assertTrue(sets.startswith("[典型90問](#sets-typical90)・[EDPC](#sets-dp)\n\n### 競プロ典型 90 問 {#sets-typical90}"), sets)
        self.assertIn("### EDPC（Educational DP Contest） {#sets-dp}\n\n- EDPC A. Frog 1 → [DP の基本](../dp/dp-basics.md#dp_a)（例題）", sets)
        self.assertEqual(self.site.b_problem_index_arc(host),
                         "- ARC005 C. 器物損壊！高橋君 → [01-BFS](../graph/zero-one-bfs.md#arc005_3)（例題）")
        self.assertEqual(self.site.b_problem_index_agc(host),
                         "- AGC001 E. BBQ Hard → [格子路の数え上げ](../comb/lattice-paths.md#challenge)（力試し）")
        self.assertEqual(self.site.b_problem_index_other(host),
                         "- ABL D. Flat Subsequence → [値を添字にする BIT・セグメント木](../ds/segment-tree-on-values.md#practice)（練習）")
        for name in gs.INDEX_PARTS:
            self.assertNotIn("atcoder.jp", self.site.render(f"problem-index-{name}", host))
        # 問題集の表も、例題のページを先にして例題の小見出しへ跳ぶ
        self.assertIn("| EDPC A. Frog 1 | — | [DP の基本](../dp/dp-basics.md#dp_a)（例題） |",
                      self.site.b_problem_sets("guide/problem-sets.md"))

    def test_home_links(self):
        out = self.site.b_home_links("index.md")
        self.assertEqual([x for x in out.split("\n") if x.startswith("### ")],
                         ["### 解けなかった問題から引く {#from-problem}", "### 色ごとに順に学ぶ {#by-color}", "### 初めて使う {#first-time}"])
        self.assertIn("- [辞書としての引き方](start/how-to-use.md#lookup)：", out)
        self.assertIn("- [この教材の使い方](start/how-to-use.md)：", out)
        self.assertIn("問題番号の索引（準備中）", out)          # まだないページはリンクにしない

    def test_entrance_items_and_guides(self):
        out = self.site.entrance("basics")
        self.assertNotIn("| ページ |", out)                    # 列のある表にしない（#58）
        self.assertIn("- [答えで二分探索](binary-search-answer.md) "
                      '<span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>：答えで二分探索で引ける（かっこ。の中）。\n', out)
        self.assertIn("ページ名の横の印はレベル（[レベルの意味](../start/how-to-use.md#levels)）である。", out)
        self.assertNotIn("2 文目", out)                        # 要約は 1 文目だけ
        # 問題集は、分野のページに FIELD_SET_MIN 問以上を載せたものだけ出す（ここでは典型90問が 1 問）
        self.assertNotIn("問題集：", out)
        with mock.patch.object(gs, "FIELD_SET_MIN", 1):
            self.assertIn("\n問題集：[典型90問](../guide/problem-sets.md#problem-sets-typical90)。\n", self.site.entrance("basics"))

    def test_entrance_related_pages(self):
        tree = self.site.entrance("tree")
        self.assertIn("## ほかの分野にある関連ページ {#elsewhere}", tree)
        self.assertIn("- [動的計画法](../dp/index.md)：[木 DP](../dp/tree-dp.md) <span class=\"kp-mini kp-lv-mizu\"", tree)
        graph = self.site.entrance("graph")
        # 最短路の章の後に、基本と探索の章の BFS（kind の 2 つ目が最短路）
        self.assertIn("## 最短路\n\n- [01-BFS](zero-one-bfs.md)", graph)
        self.assertIn("\nほかの章の関連ページ：[BFS](bfs.md) <span class=\"kp-mini kp-lv-kiso\" title=\"difficulty 〜1199\">基礎</span>"
                      "（基本と探索の章）\n", graph)

    def test_field_notes(self):
        # 考察の入口の 1 行（#65）。注記の参照は {id}・{id#anchor}・{id#anchor|文字}
        out = self.site.entrance("thinking")
        self.assertIn("\n問題の形から試す型を選ぶときは[詰まったときの発想リスト](../guide/thinking-checklist.md)、"
                      "言い回しからは[逆引き辞典（言い回しから）](../guide/reverse-index-signs.md#by-phrase)を使う。\n", out)
        self.assertEqual(self.site.note_text("patterns/index.md", "{problem-sets#recent-abc|表}と{no-such-page|文字}"),
                         "[表](../guide/problem-sets.md#recent-abc)と文字")
        self.assertIn("分野の入口の注記の参照でページのないもの: no-such-page", self.site.notes)
        # 題材別の入口（#75）：逆引き辞典の題材別の表への 1 行。レベルを持たないページだけなので、レベルの印も「—」も出さない
        pat = self.site.entrance("patterns")
        self.assertIn("[逆引き辞典の「題材から引く」](../guide/reverse-index-signs.md#by-topic)の表", pat)
        self.assertIn("\n- [区間](interval.md)：区間で引ける（かっこ。の中）。\n", pat)
        for s in ("—", "kp-mini", "ページ名の横の印"):
            self.assertNotIn(s, pat)


if __name__ == "__main__":
    unittest.main()
