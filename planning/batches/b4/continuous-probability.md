# continuous-probability の報告と提案（b4）

- 書いたファイル：docs/comb/continuous-probability.md、snippets/continuous-probability/kth-max.{cpp,yaml}、docs/img/continuous-probability/holes-angles.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-22）。sections に `{title: 自作するときの要点, anchor: library}` を足した
- 検査：check_pages（エラー0・警告0）、fix_problems --check（直すべき行0）、check_snippets（1件・期待と違う0。2 通りの方法の一致を assert で確かめ、モンテカルロ法 10^6 回でも 1 ケースを確かめた）、textlint（エラー0、警告7：数式の括弧の対応・数式を含む文の長さ・折りたたみの中の助詞の誤検出）。図は render_svg で 360px・720px を目で確かめた
- 使った出典：en.wikipedia.org（Order statistic：K 番目の期待値 K/(N+1)）、github.com（library-checker-problems の一覧）、drken1215.hatenablog.com（agc021_b）、kmjp.hatenablog.jp（abc226_h）、ikatakos.com（abc226 の H の解法の節だけ）。新しいドメインはない

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc226_h | evidence に追加 | https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2021/1107_abc226 | 解法の節（長さ 1 の区分ごとの個数の DP と、区分の中の順位の期待値） |
| abc226_h | approach | 長さ 1 の区分ごとに、区分の中と上にある個数の DP で K 番目が入る確率を求め、区分の中の順位の期待値を掛けて足す（区分ごとに P(K 番目 > t) を多項式として積分してもよい） | kmjp・ikatakos の解説はどちらも前者。現在の approach（多項式の積分）は第三者の解説で裏付けていない。後者はコード片で両者の一致を確かめた |
| abc226_h | checked | 2026-10-22 | 上の 2 件で問いと解き方を確かめた |
| agc021_b | evidence | 2 件目が未確保（§15-6 の目標は 2 つ以上） | — |

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| 順序統計量 | order-statistic | 確率変数の組を小さい順に並べたときの K 番目の値。[0, 1] の一様乱数 N 個の K 番目の期待値は K/(N+1) である。 |
| モンテカルロ法（既存なら不要） | — | 本文で「乱数で何度も試した平均（モンテカルロ法）」と書いた。用語集にあればリンクを張りたい |

## 手引きへの提案

- §5 comb に「連続値の期待値を double で区分ごとに積分するときは、t = x + u と原点を区分の左端へ移してから [0, 1] で積分する（x^{d+1} の差は桁落ちする）」を足すか検討（持ち主は continuous-probability#library）

## 問題の補充の候補

| 問題 ID | 何を問うか | 裏付け |
| --- | --- | --- |
| hhkb2020_f（F. Random Max、diff 2691） | N 個の実数をそれぞれ区間 [L_i, R_i] から一様に選んだときの最大値の期待値（に定数を掛けた値）を求める。端点で区切った区分ごとに数える／多項式を積分する。練習の候補（例題の abc226_h の K = 1 に近いが、区間の端が大きく、座標圧縮した区分ごとに処理する） | https://kmjp.hatenablog.jp/entry/2020/10/10/1030 （座標圧縮した区分ごとの DP、O(N^3)）、https://scrapbox.io/nishio/HHKB2020 （最大値の分布を各変数の分布の積で求める方針のメモ。未 AC のメモなので補助） |

## 未解決の点

- Library Checker に連続値の確率の問題がないことは、GitHub の library-checker-problems の分類（math 系・polynomial・geo ほか）を一覧で見て確かめた。本文に「2026-10-22 に確かめた」と書いた
- expectation-tail-sum#continuous からこのページへのリンクは #integral へ張り替えられる（handoff-b2b3 の申し送り。メインの作業）。本文の #integral は expectation-tail-sum#continuous の式と最大値の例を繰り返さず、リンクで済ませた
- AGC021 B の解法の詳細の「一直線に並ぶときは両端が 1/2 ずつ」「辺の途中の点は確率 0」は、垂直二等分線の幾何から自分で導いた（drken の記事は EPS 付きの凸包で辺上の点を除く実装）
- visual は null なので動く図は作らず、静的な SVG を 1 枚描いた
- 使用量の目安：道具の呼び出し 約 35 回、Web 取得 10 回（検索 4 回を含む）

## 検証の指摘への対応

- 指摘 1・2・3：本文を直した
- 指摘 4（提案）：front matter の summary を「N 個の一様乱数の小さい方から K 番目の期待値は K/(N+1)」に変える（執筆者は summary を変えない規則なのでメインへ）
