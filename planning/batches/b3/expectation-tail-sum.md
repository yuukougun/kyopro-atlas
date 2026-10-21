# expectation-tail-sum の報告（b3）

- 書いたファイル：docs/comb/expectation-tail-sum.md、snippets/expectation-tail-sum/kth-value.{cpp,yaml}、docs/img/expectation-tail-sum/area.svg
- front matter で変えたもの：complexity・stage（draft）。updated は 2026-10-21 のまま（今日）。sections は骨格のまま（title・anchor とも変えていない）
- 検査の結果：check_pages エラー 0・警告 0、fix_problems --check 直すべき行 0、check_snippets 期待と違う 0、textlint エラー 0・警告 7（数式を含む文の長さ・図の代替テキストの長さ・台帳の summary の行の助詞・確認問題の題の「「」の連続。どれも §13-8・§14-25 の誤検出の範囲）
- 図：area.svg（サイコロ 2 個の大きい方について、X = v の帯を積み、行で読むと Σ v·P(X = v)、列で読むと Σ P(X ≥ k) になる図）。render_svg.py で 360・720 の幅を目で確かめた。visual は priority 3（static）なので動く図は作っていない
- コード片：kth-value.cpp（0 の項を 1〜M の一様な値にした列の K 番目の期待値、O(NM)）。cases の期待値は Python の全列挙（分数）で求めて mod に直したもの

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc295_e | evidence | https://www.cnblogs.com/PHarr/p/17266778.html を足す | 台帳の evidence（ikatakos の abc295 の記録）は執筆中に 503 で読めなかったので、PHarr の記事で問いと方針（0 の項の二項分布の上側の和）を確かめた |
| arc085_a | pages | expectation-tail-sum を practice で足す（任意） | drken の HSI の記事が「k 回以上かかる確率」の等比級数で 2^M を出している。https://drken1215.hatenablog.com/entry/2019/03/23/175300 。ただし diff 752 で易しく、coupon-collector の練習と重なる |

## 用語集への提案

- なし（指示確率変数は既存の `#indicator` にリンクした）

## 手引きへの提案

- 例題の evidence のサイト（ikatakos.com）が一時的に 503 を返すことがある。代わりに読んだ第三者の解説を参考に載せ、台帳の evidence への追加を提案する、という扱いを決めておくとよい

## 問題の補充の候補

練習に置ける台帳の問題がなく、本文には練習の節を置いていない（catalog の problems_note のとおり）。次を候補として挙げる。

| 問題 ID | 何を問うか | 裏付けの URL |
| --- | --- | --- |
| abc411_e（E. E [max]、diff 1400） | N 個の 6 面のサイコロ（面の値は広い範囲の整数）を振ったときの最大値の期待値を mod 998244353 で求める。値を圧縮し、P(max ≤ v) を各サイコロの割合の積として値の順に更新し、差をとって足す（0 の因子の扱いが要点）。本文の #kth-value の「値の範囲が広いとき」と落とし穴の「0 を含む積」はこの型 | https://qiita.com/Shizen_Tota/items/687ddc17baff09e97176 ・ https://kcpc.hatenablog.com/entry/2025/06/28/233000 |
| arc085_a（C. HSI、diff 752） | 確率 1/2^M で通る提出を通るまで繰り返す総時間の期待値。幾何分布を P(T ≥ k) の等比級数で求める入門 | https://drken1215.hatenablog.com/entry/2019/03/23/175300 |

- abc411_e は面の値の範囲（10^9 程度か）を第三者の記事のコードからしか確かめていない。台帳に入れるときに制約を確かめてほしい
- 黄の練習（難しい F・易しい G）にふさわしい tail sum の問題は見つからなかった。drken のカテゴリ「回数の期待値=(k回以上の確率)の和」は ABC では abc352_g と arc085_a だけで、ほかは Codeforces（使えない）

## 未解決の点

- 例題 abc295_e の制約（N・M の上限）は第三者の記事のコードの配列の大きさ（2005）からの推測しかないので、本文には書かず「全体で O(NM)」とだけ書いた。要点の「M ≤ 5000 程度」は骨格の signs のまま
- continuous-probability と expectation-of-square は stub なので、ページへのリンクにとどめた（continuous-probability#integral が draft になったら #continuous からの張り替えを検討）
- coupon-collector:59・132 から本ページへのリンクは、#identity（59 行目）と #waiting-time（132 行目）へ張り替えられる。linearity-of-expectation:199・304 は #kth-value、counting-mindset:111 は #kth-value か #identity が合う

## 検証の指摘への対応（b3 の直し）

- 指摘 1（0 を含む積の境界）：直した。「各 $X_i$ の最小値のうち最大のもの以下の値では積を 0 として扱う」とし、その値ちょうどでも因子が 0 であることを括弧で添えた
- 指摘 2（確認問題が本文の文をそのまま問う）：直した。「0・10・1000 を確率 1/2・1/4・1/4 でとる X の期待値を、とびとびの値の式で求めよ」（答え 252.5、Σv·P(X = v) と一致）に替えた
- 指摘 3（靴下の区別）：直した。「靴下は同じ種類でも 1 枚ずつ区別して数える」を足し、長くなった文を分けた
- 指摘 4（図の文字が 360px で小さい）：直した。area.svg の viewBox を 580→500 に狭め、文字を 1 ずつ大きくし（11〜14→13〜15）、上の説明を 2 行に分け、「X = 1：1/36」を帯の上寄りに置いた。render_svg で 360px・720px を目視
- 指摘 5（expectation-of-square へのリンクを #pairs に）：採らなかった。手引き §14-23 のとおり、相手が draft になった後の節への張り替えはメインの作業なので、提案として残す

## 提案（直しの段階で追加）

- expectation-tail-sum の exactly-vs-at-least の節にある `../comb/expectation-of-square.md` を `../comb/expectation-of-square.md#pairs` に張り替える（検証の指摘 5。expectation-of-square は draft で、「和や積のような量の二乗」は #pairs が合う）
