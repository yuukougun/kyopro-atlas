# periodicity（周期性の検出）の報告と提案

- 書いたファイル：docs/basics/periodicity.md、snippets/periodicity/rho.{cpp,yaml}、snippets/periodicity/period-count.{cpp,yaml}、docs/img/periodicity/rho.svg、docs/img/periodicity/period-count.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21）。sections は変えていない
- 検査の結果：
  - check_pages --page periodicity：エラー 0・警告 0
  - check_snippets snippets/periodicity：コード片 2、期待と違う 0
  - textlint：エラー 0、警告 17（数式中の `[0, X)` などの半開区間を括弧の不一致と見る誤検出、数式を含む文の長さ、「数十回」の漢数字、助詞の重複）
  - fix_problems --check：このページの直すべき行は 0。ほかのページ（basics/fractional-binary-search.md の 8 行、並行して執筆中と思われる）で出ている
- 動く図：catalog の visual は priority 3 なので、静的な SVG（rho.svg）で代えた。div は置いていない
- SVG は手元にレンダラーがなく、座標の計算だけで配置した。表示の確認をお願いしたい

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc452_e | summary | 長さ N の数列 A と長さ M の数列 B について、すべての組 (i, j) の A_i × B_j × (i mod j) の和を 998244353 で割った余りを求める。 | https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2026/0404_abc452（解説の部分だけ参照） |
| abc452_e | approach | i mod j = i − j⌊i/j⌋ と分け、j ごとに i を長さ j の塊に分けて累積和で数える（塊の数の合計は調和級数） | 同上 |
| typical90_bf | summary | 表示された値にその各桁の和を足して 10^5 で割った余りに置き換える操作を K 回行った後の値を求める。（今の summary には「10^5 で割った余り」がなく、状態が有限である理由が読めない） | https://github.com/E869120/kyopro_educational_90/blob/main/sol/058.cpp 、https://github.com/Reputeless/tenkei_90/blob/main/058.md |

本文の abc452_e の行は上の summary で書いた（fix_problems は本文の要約を保つので、台帳を直せば一致する）。

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| 尾と周期（ρ 型） | rho-shape | 次の状態が今の状態だけで決まる列 x_0, x_1, … で、一度しか現れない先頭の部分（尾、長さ μ）と、その後に永遠に繰り返す部分（周期 λ）。尾から輪に入る形が ρ に似ている |

固定点（fixed-point）は既存の anchor にリンクした。

## 手引きへの提案

- 付録 A の正規形は「周期性」だが、ページの題名は「周期性の検出」である。題名を正規形に足すか、どちらで書くかを決めてほしい（本文では題名に合わせ「周期性の検出」を主語にした）
- 「尾」「輪」の言い方：Functional graph のページと用語をそろえたい（本文では「尾」「輪」「輪の入口」を使った。グラフの「閉路」とは言っていない）

## 問題の補充の候補

catalog の問題は 6 問すべて確認済みで足りている。補うなら次の候補（abc241_e・abc331_d は台帳で確認済みで、ほかのページの持ち物）。

- abc241_e（diff 1248）：皿の飴の個数の和 mod N を状態にする型（状態に将来を決める情報だけを入れる）。doubling の例題なので、このページでは練習として載せる候補。裏付け https://qiita.com/recuraki/items/e26c220f2bc01f58e185
- abc331_d（diff 1361）：周期的に敷き詰めた盤面の長方形の数え上げ。prefix-sum-2d の例題なので、このページの「盤面・剰余の周期」節の練習の候補。裏付け https://oraclesqlpuzzle.ninja-web.net/kyoupro/05-atcoder-02-abc/kyoupro-abc331-d.html
- abc300_f（diff 1846、台帳にない。ap.py で実在を確認。題名 F. More Holidays）：文字列を M 回繰り返した周期構造で開始位置を 1 周期分だけ試す。裏付け https://drken1215.hatenablog.com/entry/2023/05/03/002258（research/01-basics の表）

## 未解決の点

- abc452_e は、ikatakos 氏の記録では本質が「⌊i/j⌋ の階段（倍数の位置で増える差分）」であり、剰余の周期そのものより調和級数と差分・累積和の問題に近い。このページの練習に置くのは適切か、harmonic 系（商・調和級数）のページの練習に移すかを検討してほしい。本文では「剰余を含む和」の型として塊に分ける説明にした
- 「シミュレーションを速く進める」節のうち、盤面全体を状態にする型には台帳の確認済みの例がない（本文では問題 ID を出していない）
- 例題の解法の詳細の「和は M × N 程度まで大きくなる」は、drken 氏の記事の N ≤ 10^10・M ≤ 10^5 に基づく
- 使用量の目安：道具の呼び出し約 30 回、Web 取得 7 回（drken 4・ikatakos 1・GitHub 2）＋ curl で題名の確認
