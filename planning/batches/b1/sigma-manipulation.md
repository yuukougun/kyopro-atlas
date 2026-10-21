# sigma-manipulation の報告と提案（工程8b・b1）

- 書いたファイル：docs/math/sigma-manipulation.md、snippets/sigma-manipulation/{divisor-sum,pair-product}.{cpp,yaml}、docs/img/sigma-manipulation/swap-grid.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21）。sections に「上位の手法へのつながり」（anchor: next-steps、level はページと同じ）を足した（手引き §4 の基礎の構成の「上位の手法とのつながり」に当たる節）
- 検査の結果：check_pages（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、check_snippets（2 本・期待と違う 0）、textlint（エラー 0・警告 14）。残った警告は、数式を含む文の長さ・読点の数と、半開区間 $[kd, (k+1)d)$ の括弧の対応（誤検出）
- 図：catalog の visual（static・priority 2）どおり、$1 \le i \le j \le 4$ の組を表にして、行ごとに囲む（実線）と列ごとに囲む（破線）を左右に並べた SVG を置いた。動く図はない。描画の道具が手元になく、SVG は座標を計算して書いたので、レイアウトの目視の確認はしていない
- 使った出典：scrapbox.io（wafuwafualgorithm の abc172_d。新しいドメインで、check_noai で noai・noimageai の指定がないことを確かめた）、blog.hamayanhamayan.com（abc172_d）、kazun-kyopro.hatenablog.com（abc230_e）、qiita.com（hyouri・bit_otter の abc471_e）、drken1215.hatenablog.com（abc356_e）。題名は各ページの title で確かめた
- 事実の確認：$\sum_K K\,d(K) = \sum_d d \cdot M(M+1)/2$（$M = \lfloor N/d \rfloor$）を Python で $N \le 12$ の愚直な計算と照合し、snippets でも $N \le 300$ を assert で確かめた。$N = 9999999$ で約 $8.4 \times 10^{14}$。$N(N+1)(2N+1)$ が $N = 2 \times 10^6$ で約 $1.6 \times 10^{19}$ になることを確かめた。snippets の cases に問題の入出力例は使っていない（abc172_d の例の N は避けた）

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠の URL |
| --- | --- | --- | --- |
| abc471_e | summary（pages の両方と alternatives） | N 個の整数から K 個を選ぶすべての選び方について、選んだ値の和の 2 乗を足し合わせ、998244353 で割った余りを求める。 | https://qiita.com/hyouri/items/941cbb14aaf4c810fa90 ・ https://qiita.com/bit_otter/items/b032b01dcf3ab95a042e |
| abc471_e | approach（sigma-manipulation） | 和の 2 乗を a_i² の項と a_i a_j（i ≠ j）の項に展開し、各項を含む選び方 C(N−1, K−1)・C(N−2, K−2) を掛ける。Σ_{i≠j} a_i a_j = (Σa)² − Σa² | 同上 |
| abc356_e | summary | 「全ての組」を「すべての組」に（prh の規則。本文の行は「すべて」に直してある。台帳を直したら fix_problems を流してほしい） | — |
| abc172_d | evidence | 今の evidence（dvoraker3 の Qiita）は典型90 039 の類題として名前を挙げるだけで、解法の説明がない。https://scrapbox.io/wafuwafualgorithm/ABC172_D_-_Sum_of_Divisors （約数ごとの入れ替えと等差数列の和、O(N)）と https://blog.hamayanhamayan.com/entry/2020/06/27/230811 （N ≤ 10^7 と篩の別解）を足す | 左に記載 |

## front matter・catalog への提案

- signs の 1 つ目「全ての組 (i, j)（i < j）について〜を足した和を求める」は prh で「すべて」に直る語。要点の囲みは「すべての組」に直したので、signs も「すべての組」にそろえたい（signs は執筆者が直せない項目なので提案にする）

## 用語集への提案

- なし（本文から用語集へのリンクは既存の identity-element だけ）。記法として $[P]$（Iverson の記法）を本文の「このページで使う記法」で定義した。記法と用語の約束（start/notation）にも載せるとよい

## 手引きへの提案

- 基礎の technique で、§4 の「上位の手法とのつながり」を中身の節として sections に足した（anchor: next-steps。見本の binary-search-answer と同じ anchor）。§13 の定型の節の一覧に、基礎のページの「上位の手法へのつながり {#next-steps}」を加えると、ページごとに迷わない

## 問題の補充の候補

| 問題 ID | 何を問うか | 裏付けの URL |
| --- | --- | --- |
| abc177_c（diff 386、台帳で確認済み。今は symmetry-pigeonhole-casework の例題） | i < j の組の積 A_i A_j の総和（mod 10^9+7）。公式の節の (Σa)² − Σa² をそのまま使う問題。易しい練習として practice に足す案 | 台帳の evidence |
| abc186_d（diff 436、台帳で確認済み。今は contribution の例題） | すべての組の差の絶対値の和。ソートして Σ (2j − N − 1) a_j に直す。公式の節の最後の式の練習として practice に足す案 | 台帳の evidence |
| abc351_f（diff 1253、台帳で確認済み） | i < j の max(A_j − A_i, 0) の和。j を外側にして内側を BIT で持つ（「独立でない和を積に分けない」落とし穴の形）。BIT を使うので練習としてはやや上 | 台帳の evidence |

基礎の練習は 3 問で、易しい側（diff 1000 未満の式変形だけの問題）が abc230_e・abc471_e だけなので、上の abc177_c・abc186_d のどちらかを足すと段差が小さくなる。abc319 以降の問題は abc471_e だけ。

## 未解決の点

- abc471_e の制約（N・K・A_i の上限）は第三者の解説に書かれておらず確かめきれなかった。本文では制約に触れていない
- 例題の詳細の中のコード片を `??? note` の中に字下げして取り込んだ（dp-order などと同じ書き方）。ビルドでの見え方は gen_site・mkdocs で確かめてほしい
- 使用量の目安：道具の呼び出し約 35 回、Web 取得 9 回（検索 2 回を含む）

## 検証の指摘への対応（verify/sigma-manipulation.md）

- 指摘 1〜9 はすべて直した（1：mod の例を外し、外に出せない側に反例と mod の組を数える注を置いた。2：$h$ が対称のときの式を display で書き、対称でないと成り立たない旨を添えた。3：2 と 3 の因子・2 だけ割っても上限に近いこと。4：max と floor の反例の式。5：$d$ より大きい値で区間を数える。6：1-indexed に直した。7：mint と inv の 1 文と modint へのリンク。8：練習へのリンク。9：$2\sqrt{N}$ の理由）
- 指摘 10（図）は、マスのラベルの font-size を 12 → 14 に上げた（マス 48px に収まる）。全体の幅は変えていない
- 採らなかったもの：なし

## 検証の提案（メインへ。共有ファイルなので書いていない）

- 検証役の提案のとおり：abc172_d の checked に 2026-10-21、evidence に scrapbox・はまやんの 2 件、scrapbox.io を付録 B に。abc356_e の summary と signs 1 つ目の「全て」→「すべて」。練習に abc186_d（#formulas の最後の式の練習）を足す案
