# floor-quotient-enum の報告と提案

- 書いたファイル：docs/math/floor-quotient-enum.md、snippets/floor-quotient-enum/quotient-blocks.{cpp,yaml}、docs/img/floor-quotient-enum/staircase.svg
- front matter で変えたもの：complexity・stage（draft）・updated（節は足していない）
- 検査の結果：check_pages エラー 0・警告 0／check_snippets 期待と違う 0／textlint エラー 0・警告 19（数式を含む文の長さ・読点の数、問題の行と囲みの中の文の長さ、「に」「は」の重なりなど。残りは誤検出か、言い換えると読みにくくなるもの）／fix_problems --check はこのページで直すべき行 0（終了コード 1 はほかのページ comb/minimax.md・comb/probability-dp.md の行のため）
- 使った出典：kazun-kyopro.hatenablog.com（abc230_e）、drken1215.hatenablog.com（arc160_b・abc296_d・arc060_b）。問題の補充の候補を探すのに zenn.dev（付録 B にある）を読んだ。新しいドメインはない
- 動く図：priority 1 なので、置き場の div `<div class="kp-viz" data-viz="floor-quotient-enum" data-config='{"n": 20}'></div>` だけを書いた（静的な SVG を前に置いた）。図の仕様：i を横軸・⌊N/i⌋ を縦軸にした棒の階段。ステップごとに現在の区間 [l, r] を強調し、caption に「l = 7、q = ⌊20/7⌋ = 2、r = ⌊20/2⌋ = 10、和に (10 − 7 + 1) × 2 = 8 を足す」のように書く。√N の位置に縦線を引き、左側（1 個ずつ）と右側（商が √N 未満）の区別を見せる。最後のステップで区間の数（N = 20 で 8）と和（66）を示す

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| arc160_b | summary | 「全て」を「すべて」に（prh の規則。本文の行は手で「すべて」に直したので、fix_problems で作り直すと textlint のエラーが戻る） | 付録 A・§7 |
| arc060_b | （確認のみ）| label は「ARC060 D. Digit Sum」で、drken の記事の題名は「ABC 044 D - 桁和 (ARC 060 D)」。同時開催の abc044_d と同じ問題であることを、必要なら alternatives か備考に | https://drken1215.hatenablog.com/entry/2024/09/14/115435 |

## 用語集への提案

なし（本文で用語集へリンクした語はない）。

## 手引きへの提案

- 本文中で（例題でない）練習・力試しの問題に触れるとき、`[力試し](#challenge)の ARC060 D` のように見出しへのリンクと label の一部を書いた。この書き方でよいか決めておくとよい

## 問題の補充の候補

| 問題 ID | 何を問うか | 役割の案 | 裏付けの URL |
| --- | --- | --- | --- |
| abc414_e（Count A%B=C、diff 1296、ap.py で確認） | 1 以上 N 以下の相異なる a, b, c で a mod b = c となる組の個数を 998244353 で割った余りで求める。b < a の組の数から a が b の倍数の組の数（Σ⌊N/b⌋ の形）を引き、商が同じ区間ごとにまとめる | 練習（水・abc319 以降の根拠になる。catalog の level_evidence と problems_note の「abc319 以降の根拠がない」を解消できる） | https://zenn.dev/nakst_hide/articles/f5b3e3a3473e9d （N の上限は記事に明記がなく未確認。もう 1 つ解説で確かめたい） |

## 未解決の点

- abc414_e の N の制約（10^12 程度と思われる）を第三者の解説で確かめきれていない
- 「(long long)sqrt(n) が 1 ずれる」境目を 2^53 と書いた（double に直す時点で丸められるため）。2^53 以下では IEEE 754 の sqrt は正しく丸められるので floor が合うと考えたが、実機で網羅的には確かめていない。本文では直し方（前後に直す）を勧めているので、結論は変わらない
- related の base-conversion・multiplicative-function・harmonic-sum・sqrt-decomposition は stub なので、節ではなくページへリンクした
- 使用量の目安：道具の呼び出し 約 35 回、Web 取得 6 回、検索 4 回

## 検証の指摘への対応（2026-10-21）

- 指摘 1〜3（直すべき）：すべて直した。$2^{53}$ の境目は「$2^{52}$（約 $4.5 \times 10^{15}$）程度」に改め、理由を `double` の精度（$\sqrt{m^2 - 1}$ が $m$ に丸められる）にした。確認問題の答えは「どの $N$ でも $l = 1$ で右端が 0 になり止まらない」に書き換え、一般の形も添えた。ARC160 B は「値は約 $1.3 \times 10^{14}$ で `long long` に収まり、最後に余りを取ればよい」にした
- 指摘 4・5：直した（約 $4.2 \times 10^{19}$。`sum_floor` と main の和の変数を `sum` に）
- 指摘 6：採った。`:core` を素朴な for ループで $\sum \lfloor N/i \rfloor$ を求める `sum_floor` にし、`:sum` の取り込みをやめた。ラムダを渡す `for_each_quotient` は snippets の中に残し、main の確かめにだけ使う
- 指摘 7：採った。staircase.svg の文字を 14px（題は 15px）に上げ、縦軸の目盛りを 1・2・5・10・20 に減らした。下の 2 つの説明文の位置を少しずらした。和文フォントのある環境での見え方は確かめていない
- 指摘 8（メイン向け）：提案として残す。報告の仕様で動く図 `floor-quotient-enum` を頼むか、公開までに作らないなら #why-sqrt の `<div class="kp-viz" …>` を一時的に外すかをメインが決める
- 台帳への提案（追加）：abc230_e・arc160_b・abc296_d・arc060_b の `checked` に 2026-10-21 を入れる（検証役が evidence と本文の一致を確認済み）
