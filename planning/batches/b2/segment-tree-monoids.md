# segment-tree-monoids の報告（b2）

- 書いたファイル：docs/ds/segment-tree-monoids.md、snippets/segment-tree-monoids/{second-largest,max-subarray,affine,min-plus}.{cpp,yaml}、docs/img/segment-tree-monoids/bracket-merge.svg
- front matter で変えたもの：complexity・stage（draft）・updated。sections の title を 2 つ短くした（anchor は変えていない。§13-2・§14-12）
  - design-steps：「設計の手順（答えに要る情報 → 親が作れるまで情報を足す → 結合律と単位元を確かめる）」→「設計の手順（答えに要る情報を足し、結合法則と単位元を確かめる）」（矢印の記号を避け、用語を付録 A の「結合法則」にそろえた）
  - matrix：「行列を載せる（(min,+)・(max,+) の半環も。行列の積は行列累乗のページ、1 点更新のたびに DP を求め直すなら動的 DP）」→「行列を載せる（(min,+)・(max,+) の半環も）」（60 字を超えるため。後半の内容は節の本文に書いた）
  - docs/guide/problem-sets.md の abc456_f の行は古い title を出しているので、gen_site で作り直すときに新しい title になるはず
- 構成：level 青の technique（§4）。必要になる場面・アイデアとなぜ正しいか・処理の流れは design-steps で兼ねた（§14-5）。ACL の囲みは design-steps の中に置いた（§14-4）。応用の型は各節の中に置いた
- 検査の結果：check_pages エラー 0・警告 0、fix_problems --check 直す行 0、check_snippets 4 本とも期待どおり、textlint エラー 0・警告 23（数式の中のカンマと括弧、図の代替テキストの長さ、折りたたみの中の箇条書きなど。誤検出か、短くすると意味が崩れるものとして残した）
- コード片：4 本とも main で素朴な方法と比べる assert を持つ。min-plus.cpp は N ≤ 12 のとき払う位置の集合の全探索と比べ、乱数の入力 400 個で一致を確かめた（scratchpad で実行。ファイルには残していない）
- 図：bracket-merge.svg（visual priority 2 の静的な図。左の子 "(()(" と右の子 "))()" の高さの折れ線と（合計, 最小値）、親で右が合計 2 だけ持ち上がる様子。線の種類（実線・破線・点線）とラベルで区別）。render_svg.py で 360px・720px を目で確かめた。動く図は作っていない（priority 2 なので div も置いていない）

## 使った出典

- https://github.com/atcoder/ac-library/blob/master/document_ja/segtree.md（手元の ~/lib/ac-library-master/document_ja/segtree.md）：prod が op(a[l], …, a[r-1]) を返すこと、l = r で e()
- https://programming-hiroba.com/abc343-f/：例題 abc343_f の要約（最大・個数・2 番目・個数）と単位元
- https://qiita.com/gotoki_no_joe/items/7446ddde2d6a36eae210：例題 abc343_f（台帳の evidence。マージソートのマージのように結ぶ、という記述だけ）
- https://hackmd.io/@amoshyc/S1yZNoYBF：例題 abc223_f の別解（累積和の遅延セグ木）と判定の条件。（合計, 最小接頭和）の方法は bracket-sequence#monoid と自分の検算で確かめた
- https://zenn.dev/loop0919/articles/f779f54ccdfedf：例題 abc456_f の問い・DP・(min,+) 行列・窓 [l, l+K) と [l, l+K+1) の 2 回の取得
- https://qiita.com/ZOI_dayo/items/a55cc4342832efdc23ba：練習 abc309_f の方針
- https://www.cnblogs.com/wushansinger/p/17021389.html：練習 abc283_f の 4 通りの場合分け
- https://drken1215.hatenablog.com/entry/2018/02/14/121239：力試し arc008_4 の問い（N ≤ 10^12、M ≤ 10^5）と方針
- 新しく noai を確かめたドメイン：なし（すべて付録 B のドメイン）

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc343_f | evidence に追加 | https://programming-hiroba.com/abc343-f/ | 今の evidence（gotoki_no_joe 氏の記事）は結合を「マージソートのマージのように」と書くだけで、単位元や答えの取り出しが読めない。プロひろの記事は ACL の segtree で S・op・e を書いている |
| abc223_f | evidence | 1 つ目の https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/ （記録の一覧の入口で、問題の記事ではない）を外し、https://hackmd.io/@amoshyc/S1yZNoYBF を足す | 一覧の URL はこの問題の解説ではない（§14-17） |
| abc456_f | evidence の順 | zenn の記事を先頭にする（任意） | 今回 ikatakos.com が 503 で読めず、問いと方針は zenn の記事だけで確かめた |

## 用語集への提案

- 交換法則｜commutativity｜2 つの値の順序を入れ替えても演算の結果が変わらない性質（$x \cdot y = y \cdot x$）。和・最小値は満たし、関数の合成・文字列の連結・行列の積は満たさない。セグメント木に載せる演算には要らない。（本文の non-commutative の節で使う。用語集に anchor がないと check_pages がエラーにするので、いまはリンクを張っていない。足したら初出の「交換法則」にリンクを張る）

## 手引きへの提案

- §13-5 は「用語集へのリンクは、まだなくても書いてよい」とするが、check_pages は用語集にない anchor をエラーにする。どちらに合わせるかを決めてほしい（今回はリンクを外して提案に回した）
- 行列をセグメント木に載せるときの向き：本ページは「行列の (p, q) 成分は直前の状態 p → 次の状態 q、状態は横ベクトル」として op(a, b) = ab にした。行列累乗のページは縦ベクトル（v' = Av）なので、区間の積の向きが逆になる。本文で両方の書き方と op の向きを明記したが、dynamic-dp を書くときにどちらにそろえるかを決めておくとよい

## 問題の補充の候補

- なし（例題 3・練習 3・力試し 2 で目安に足りている。abc319 以降は abc331_f・abc343_f・abc456_f・abc460_f）

## 未解決の点

1. ikatakos.com が 503 を返し、台帳の evidence のうち abc223_f・abc456_f・abc460_f の記事を読めなかった。abc456_f は zenn の記事で問いと方針を確かめ、自分の読み（費用なしの日は隣り合えない・窓の左端は払う・端の日は外側を休日でないとみなす）を全探索との比較で確かめた。問題文そのものは読んでいないので、端の日（1 日目・N 日目）を費用なしにできない点と A_i ≥ 0 は、検証役が別の解説で確かめてほしい
2. abc460_f の方針は tree-diameter・lca のページの方針の書き方と台帳の approach に合わせた（自分では解説を読めていない）
3. abc343_f・abc223_f の制約（N, Q の上限）は解説から読み取れなかったので、本文に数値を書いていない
4. 使い分けの表に SWAG（monotonic-stack#swag）を「更新がなく、固定長の窓ごとの総積」として載せた。abc456_f の解法の詳細でも別解として触れた。SWAG で abc456_f が解けることは自分の推論で、解説では確かめていない（結合法則だけを使う手法なので成り立つはず）

## 使用量の目安

- 道具の呼び出し 50 回ほど、Web 取得 13 回（うち 503 が 5 回）、検索 2 回

## 検証の指摘への対応（b2 の直し）

- 1（直すべき・ARC008 D の初期状態）：方針を「初期状態の値 1 と、差し替えのたびに全体の合成を 1 に施した値の、最大と最小を答える」に直した
- 2（費用なしの位置が隣り合えない理由）：指摘の案どおり書き換え、「費用なしの位置の両隣は、どちらも払った位置になる」を続けた
- 3（図が 360px で小さい）：下の 3 行の説明を外し（本文と代替テキストにある）、凡例を短くし、左右の子を詰めて viewBox を 640×466 から 480×420 にした。題を 2 行に分けた。render_svg の 360px で文字が読めることを確かめた
- 4（区間反転）：「区間の 0 と 1 を入れ替える反転と組むと、遅延セグメント木の載せ方の型（lazy-segment-tree-patterns#flip）になる」に直した
- 5（ABC309 F・ABC283 F の位置づけ）：方針の冒頭に「載せるのは最小値だけで、工夫は添字の選び方にある。値そのものを載せる型で足りる」と書いた。台帳の役割の見直しは下の提案に回した
- 6（表の記号）：最大部分配列和の行の要約を「（和 sum, 最大接頭和 pre, 最大接尾和 suf, 最大 best）」にした
- 検査：check_pages エラー 0・警告 0、fix_problems --check 直す行 0、check_snippets 4 本とも期待どおり、textlint エラー 0（警告 22）

### 台帳への提案（直しで追加）

- abc309_f・abc283_f：このページの練習としては主題（情報を足して載せる）に合わない。segment-tree-on-values の練習に移し、このページの練習には情報を足す型の問題を補うのがよい（メインの判断に任せる。今回は位置づけを書いて残した）
