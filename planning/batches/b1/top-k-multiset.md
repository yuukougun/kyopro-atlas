# top-k-multiset の報告と提案（工程8b・b1）

- 書いたファイル：docs/ds/top-k-multiset.md、snippets/top-k-multiset/{bottom-k,running-median}.{cpp,yaml}、docs/img/top-k-multiset/move-boundary.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21 のまま）。sections は 黄 の節の title の「slope trick」を正規形の「Slope Trick」に直しただけ（anchor は同じ）
- 検査の結果：
  - check_pages --page top-k-multiset：エラー 0・警告 0
  - check_snippets snippets/top-k-multiset：2 件すべて一致
  - textlint：エラー 0・警告 2。38 行の sentence-length（要点の「いつ使うか」の入れ子の箇条書きを 1 文と数える。見本の lazy-segment-tree と同じ形）、63 行の max-comma（数式 $\{1, 4, 5, 7, 9\}$ の中の読点）
  - fix_problems --check：このページの直すべき行は 0。ただし全体では ds/global-offset.md の 7 行（`- abc212_d：…` の形のまま）が残っていて終了コードは 1。別の執筆者の担当ページなので触っていない
- 図：静的な SVG を 1 枚（visual は priority 2 の static）。K = 3 で追加・削除のたびに境界の 1 個が移る 3 段の図。L は塗りつぶし、R は破線の丸、境界は縦の破線で、色だけに頼らない。描画して目で確かめる道具がなく、XML として読めることと座標の計算だけを確かめた。表示の確認を検証役に頼みたい
- 使った出典：hibit（Qiita、abc306_e の方針）、comet725（Qiita、abc458_d の問いと方針）、drken（はてなブログ、abc281_e・arc074_b・abc127_f）、maspypy（slope trick 解説編）。題名は各ページの title 要素で確かめた。新しく noai を確かめたドメインはない（どれも付録 B）

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc458_d | summary | 最初に 1 つの整数を書き、続けて 2 つずつ整数を書き足すたびに、書かれている整数の中央値を答える。 | https://qiita.com/comet725/items/4e3a310ec19ed32e12f6（入力の形と出力。個数が常に奇数になることもコードから分かる） |
| abc458_d | approach | 小さい半分と大きい半分を 2 つのヒープで持ち、個数の差を 1 以内に保って中央値を答える（「research/00 §2.3.8 の分類」の注記を外す） | 同上 |
| abc281_e | title | 末尾の空白（'Least Elements '）は AtCoder Problems のデータのまま。fix_problems の label は空白なしで出ているので問題はないが、気づいた点として記す | python3 tools/ap.py show abc281_e |

ほかの使った問題（abc306_e・abc281_e・arc074_b・abc127_f）の summary と approach は、evidence の解説と食い違いがなかった。abc281_e は segment-tree-on-values の例題で、このページでは練習として載せた（D4 のとおり）。

## 用語集への提案

- 中央値｜median｜値を小さい順に並べたときの真ん中の値。個数が偶数のときは真ん中の 2 つのうち小さい方・大きい方・平均のどれを指すかを問題ごとに確かめる。本文は `../guide/glossary.md#median` でリンクした（median-absolute も同じ anchor でリンク済みのはず）
- 不変条件｜invariant｜処理の各段階の後で常に成り立つように保つ性質。本文ではリンクしていない（「保つ性質」と書いた）。ds の各ページで共通に使うなら足したい

## 手引きへの提案

- §13.1 では「落とし穴」を定型の節として sections に載せないが、このページは骨格の時点で sections に `anchor: pitfalls`（かっこ書きつきの題名）を持っていた。§13.2 に従い見出しを sections の title と同じにした。binary-search の報告と同じ論点なので、まとめて決めてほしい
- 基礎でない technique の目安では「必要になる場面」「計算量とその根拠」を節にするが、§13.1 で sections に載せない定型の節に入っていない。今回は sections を増やさず、two-sets と invariants の節の中に書いた

## 問題の補充の候補

- abc218_g（G. Game on Tree 2、diff 2217、台帳で確認済み、いまは root-path-dfs と minimax の力試し）：根から葉へのパス上の値の中央値をスコアにするゲーム。DFS で値の追加と削除をくり返しながら中央値を求めるので、削除のある「中央値を保つ」の力試しになる。裏付け：https://kmjp.hatenablog.jp/entry/2021/09/12/0900（台帳の evidence）。偶数個のときの中央値は 2 つの平均で、`R の最小` も読む型になる（この点は解説で確かめていない。検証役に頼みたい）
- abc319 以降で水の帯の例題・練習になる問題は見つからなかった（ap.py の題名検索「Median」と、台帳の summary・approach の検索で探した）。catalog の level_evidence の記述（D2）と同じ結論

## 未解決の点

- abc306_e の制約（N の上限・値の上限）は解説記事に書かれておらず確かめていないので、本文には具体的な上限を書かず「K 個の和は int に収まらない」とだけ書いた
- abc458_d の偶数個のときの中央値の定義は、個数が常に奇数になるので関係しないと判断した（comet725 の記事のコードから読み取った。問題文は開いていない）
- Slope Trick の節は入口の説明にとどめ、片側だけの関数を足すときの最小値の更新式は書いていない（slope-trick のページの担当と考えた）
- 使用量の目安：道具の呼び出し 約 40 回、Web 取得 6 回（WebFetch）と題名の確認 6 回（curl）
