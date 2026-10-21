# kth-value の報告（b2）

- 書いたファイル：docs/basics/kth-value.md、snippets/kth-value/pair-product.{cpp,yaml}、snippets/kth-value/top-m-sum.{cpp,yaml}、docs/img/kth-value/count-staircase.svg
- front matter で変えたもの：complexity・stage（draft）・updated。sections は変えていない（catalog にあった pitfalls は手引き §14-1 に従い定型の `## 落とし穴 {#pitfalls}` にした）
- 構成：level が青なので §4 の technique（水・青・黄）に従った（§14-6）。必要になる場面・処理の流れ・計算量は sections の節で兼ねた（§14-5）。acl は空なので ACL の囲みはない
- 検査の結果：check_pages エラー 0・警告 0、fix_problems --check 直す行 0、check_snippets 期待と違う 0（2 本）、textlint エラー 0・警告 6（数式の中の集合・座標のカンマ、図の代替テキストの長さ・カンマ。誤検出として残した）
- 図：count-staircase.svg（visual priority 2 の静的な図。{1, 2, 2, 4, 5, 5} の count(x) の棒グラフと K = 3 の線、可・不可の文字、ハッチで区別）。render_svg.py で 360px・720px を目で確かめた。動く図は作っていない（priority 2 なので置き場の div も置いていない）

## 使った出典

- https://oraclesqlpuzzle.ninja-web.net/kyoupro/05-atcoder-02-abc/kyoupro-abc341-d.html：例題 abc341_d の個数の式（記事の題は「ABC340-D」だが中身は abc341_d。参考の行に注記した）
- https://drken1215.hatenablog.com/entry/2020/04/23/142200：例題 abc155_d（制約 |A_i| ≤ 10^9、N ≤ 2×10^5、符号の場合分け、自分自身との組と重複の除き方）
- https://drken1215.hatenablog.com/entry/2021/07/03/041500：練習 arc037_c（N ≤ 30000、値は正、upper_bound で数える）
- https://drken1215.hatenablog.com/entry/2024/05/20/004045：練習 abc205_d（欠けた数の個数 A_i − i の前計算）
- https://blog.hamayanhamayan.com/entry/2020/01/01/024415：力試し abc149_e（M 番目の値、累積和、同じ値の分の調整）
- 新しく noai を確かめたドメイン：なし（すべて付録 B のドメイン）

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc149_e | summary | 2 人の値の和を握手の値とし、選べる組（同じ人の組を含む N^2 通り）のうち大きい方から M 組の値の和を求める。 | 現行の「2 人の組（握手）の値」では、組が N^2 通り（順序付き・同じ人を含む）か N(N−1)/2 通りかが読めない。hamayan の解説のコードは i = j を含む順序付きの組を数え、「列挙すると 10^10 通り」とある（N ≤ 10^5）。ただし問題文そのものは確かめていないので、メインが別の解説でも確かめてから直す（未解決の点 1） |
| abc364_d | 追加 | role: practice（kth-value）、summary：数直線上の N 点と Q 個の質問点について、質問点から K 番目に近い点までの距離を答える。approach：距離 d を二分探索し、[b − d, b + d] に入る点の個数を lower_bound・upper_bound で数える | https://oraclesqlpuzzle.ninja-web.net/kyoupro/05-atcoder-02-abc/kyoupro-abc364-d.html （ap.py：ABC364 D. K-th Nearest、diff 1136） |

## 用語集への提案

- 多重集合｜multiset｜同じ要素を何度でも含んでよい集合である。要素ごとに含まれる個数を持つ。（本文では初出でかっこの中に定義を書いたので、リンクは張っていない）

## 手引きへの提案

- 「K 番目」を数える判定（count(x) ≥ K、大きい方からは「x 以上の個数 ≥ K」の最大）の書き方は、binary-search-answer・fractional-binary-search・kth-element・greedy-priority-queue で同じ言い回しにそろえるとよい。本文では「count(x)」を x 以下の個数、「x 以上の個数」は言葉で書いた

## 問題の補充の候補

- abc364_d（ABC364 D. K-th Nearest、diff 1136）：数直線上の点のうち、質問点から K 番目に近い点までの距離を、質問ごとに答える。距離を二分探索し、区間に入る点を lower_bound・upper_bound で数える。裏付け：https://oraclesqlpuzzle.ninja-web.net/kyoupro/05-atcoder-02-abc/kyoupro-abc364-d.html 。abc319 以降で、今の問題の中では abc341_d に次ぐ新しい問題になる（水・青のページに abc319 以降を 1 問以上の目安は abc341_d で満たしている）
- 青の形の abc319 以降の問題は見つからなかった（ap.py で「K-th」「Kth」「Largest」「Smallest」を検索。abc391_f K-th Largest Triplet は優先度付きキューで小さい順に取り出す型で、greedy-priority-queue#k-best 向き）

## 節へ張り替えるリンク（handoff §1.2・§1.3 の kth-value の 8 か所）

- binary-search-answer:165・reformulation:59（「K 番目に小さい値 ≤ x ⇔ x 以下が K 個以上」）→ `kth-value#why-count`
- two-pointers:147（尺取りで数える）→ `kth-value#counting-patterns`
- binary-search:178・greedy-priority-queue:143・greedy-priority-queue:192・kth-element:166（ページ全体への導入）→ ページへのリンクのままでよい（必要なら `#why-count`）
- fractional-binary-search:217（比の K 番目）→ ページへのリンクのままでよい

## 未解決の点

1. abc149_e の組の数え方（同じ人の組を含むか、順序を区別するか）を問題文で確かめていない。本文の力試しの方針は「問題文で確かめる」と書き、どちらかに決めていない。top-m-sum.cpp は 2 つの列 a・b の N^2 通りの和で書いた（b = a とすれば同じ人を含む順序付きの組になる）
2. abc341_d の制約（N, M ≤ 10^8、K ≤ 10^10、N ≠ M）は記事の本文では確かめきれず、記事のコードの入力例の大きさから推した。本文では制約の数値を書かず、上限 2KP の見積もりを N ≠ M だけから導いた（N, M ≤ 10^8・K ≤ 10^10 なら 2×10^18 で long long に収まる）
3. 本文の「二分探索は約 61 回」は V ≈ 2×10^18 の場合（log2(2×10^18) ≈ 60.8）。ほかのページの「約 60 回」（10^18）とは V が違う

## 検証の指摘への対応（verify/kth-value.md）

- 指摘 1〜6 はすべて直した（割り算のずれる条件、ABC149 E の組の数え方と kmjp の参考、`long long` の境目 約 3×10^9、2KP が収まるかの確認の 1 文、top-m-sum.cpp の変数名 `c`、確認問題の「ソート済み」と 0-indexed）。採らなかった指摘はない
- 未解決の点 1 は kmjp・hamayan の 2 つの解説で解決した（同じ人を含む順序付きの N^2 通り）。台帳の summary の提案（上の表）はこのままでよい

## 台帳への提案（検証の反映）

- abc149_e の evidence に https://kmjp.hatenablog.jp/entry/2019/12/30/0900 を足す（組の数え方の裏付け）
- abc341_d・abc155_d・abc205_d・arc037_c・abc149_e の `checked` に 2026-10-21 を入れる（検証役が evidence で確かめた）
