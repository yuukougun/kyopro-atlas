# harmonic-sum の報告と提案

- 書いたファイル：docs/math/harmonic-sum.md、snippets/harmonic-sum/multiples.{cpp,yaml}、docs/img/harmonic-sum/multiples-grid.svg
- front matter で変えたもの：complexity・stage（draft）・updated。sections の title を本文の見出しに合わせて直した（anchor は変えていない）
  - why-n-log-n：「N/1 + … ≈ N ln N」を「M/1 + M/2 + … + M/M ≈ M ln M」に（本文では列の長さ N と値の上限 M を分けたため）
  - collect-multiples：「（d の倍数である要素の個数・和を全ての d について求める）」を「（d の倍数である要素の個数・和）」に（「全て」の表記と長さ）
  - vs-sieve：「（N log log N）」を「（M log log M）」に
  - pitfalls：title を「落とし穴」に（手引き §13.1 の定型の見出しと合わせた）
- 検査の結果：check_pages エラー 0・警告 0／fix_problems --check 直すべき行 0／check_snippets 期待と違う 0／textlint エラー 0・警告 18（数式を含む文の長さ・読点の数、問題の行と折りたたみの中の文の長さ。言い換えると読みにくくなるもの）
- 動く図：visual は static・priority 2 なので、静的な SVG（d = 1..12 の行に倍数の ● を打った 12×12 の表）だけを作った。SVG を描画して見た目は確かめていない（手元に rsvg などがない）
- 使った出典：drken1215.hatenablog.com（abc170_d・abc179_c・abc134_d・abc356_e・abc128_f）、ikatakos.com（abc393_e・abc469_f。解法の節だけ）。新しいドメインはない

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc356_e | summary（alternatives の harmonic-sum 版と本体の両方） | 「全ての組」を「すべての組」に（prh の規則。本文の行は手で「すべて」にした） | 手引き 付録 A・§7 |
| abc128_f | summary | 「同じ蓮を2回踏むと失敗」を「同じ蓮を 2 回踏むと失敗」に（半角数字の前後の空白。本文は直した） | 手引き §7 |
| abc179_c | approach | 「A ごとに B は (N − 1)/A 通りで、合計が調和級数になる」は、割り算で数えれば O(N) で調和級数は要らない。「A ごとに B は ⌊(N − 1)/A⌋ 通り。組を 1 つずつたどっても合計が調和級数で収まる」に | https://drken1215.hatenablog.com/entry/2020/09/21/070100 |
| abc393_e | evidence | 第三者の解説の方法は倍数方向のゼータ変換（素数ごと、O(M log log M)）で、本文の方法（すべての d で倍数を回す、O(M log M)）とは計算量が違う。本文の方法は記事の言い換えと同じ考えで正しいが、同じ方法の解説を 1 つ足せるとよい | https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2025/0215_abc393 |
| abc170_d・abc393_e・abc179_c・abc134_d・abc356_e・abc128_f | checked | 検証役が evidence と本文の一致を確かめたら日付を入れる | — |

## 用語集への提案

なし（本文で用語集へリンクした語はない）。「調和級数」は本文で定義した（$H_M$ の部分和）。用語集に入れるなら：調和級数｜harmonic-series｜$1 + 1/2 + \dots + 1/M$ の和。$\ln M$ とほぼ同じ速さで増え、$d = 1..M$ の倍数をたどる回数が $O(M \log M)$ になる根拠である。

## 手引きへの提案

- §13.1 は「落とし穴」を sections に載せない定型の節とするが、catalog の sections に pitfalls が入っているページがある（このページ）。title を「落とし穴」に直して残したが、sections から外すべきかをメインが決めるとよい
- 列の長さ N と、値を添字にしたときの上限 M を分ける書き方（§6 の文字の一覧に「値の上限 M」を足す）を決めておくと、値を添字にする整数論のページでそろう。ただし §6 では M は辺数なので、別の文字（V など）にするかも含めて決めたい

## 問題の補充の候補

| 問題 ID | 何を問うか | 役割の案 | 裏付けの URL |
| --- | --- | --- | --- |
| abc206_e（E. Divide Both、diff 1745、ap.py で確認） | L 以上 R 以下の組 (x, y) で、gcd が 1 でも x・y 自身でもないものの個数。gcd を固定して倍数の個数から数え、大きい順に引く（本文の「倍数の箱を後ろから決める」の gcd の例と同じ形） | 練習（divisor-inclusion-exclusion の例題と重なるなら練習の参照だけ） | https://drken1215.hatenablog.com/entry/2021/06/25/121800 （research/01 §5 の記載。今回は記事を開いていない） |
| abc177_e（E. Coprime、diff 1057） | pairwise coprime の判定を「各 d ≥ 2 で d の倍数である要素が 2 個以上あるか」で倍数を回して調べる。spf-sieve の例題なので、ここでは練習か本文の参照 | 練習 | https://drken1215.hatenablog.com/entry/2020/10/31/203300 （research/01 §5 の記載。今回は開いていない） |

abc319 以降の水の問題は abc393_e（例題）と abc469_f（練習）で、手引き §10 の目安は満たしている。

## 未解決の点

- 「同じ値の組の ⌊max/min⌋ の和の最大」を「N = 2×10^5・A_i ≤ 10^6 で約 10^16」と書いた（半分が 1・半分が 10^6 のとき約 (10^5)^2 × 10^6）。上界の見積もりとしては正しいが、厳密な最大値は計算していない
- abc128_f の「C が N − 1 の約数のとき 2 つの列が重なる」は drken の記事の要約に基づく。重なりの条件の細部（踏む回数との関係）は本文では「場合分けする」までにとどめた
- abc469_f の計算量（A_i が相異なるので候補の数が O(M log M)）は自分の見積もりで、ikatakos 氏の記録は約数の側から箱に入れる形で説明している
- 使用量の目安：道具の呼び出し 約 30 回、Web 取得 8 回（うち題名の確認に curl）

## 検証の指摘への対応（2026-10-21）

- 指摘 1（直すべき）：sections から pitfalls の行を消した（見出しと anchor はそのまま）
- 指摘 2（直すべき）：multiples-grid.svg の題を「M = 12：…」、下の行を「O(M²)」「O(M log M)」にした
- 指摘 3（直すべき）：ABC128 F の方針を「C が N − 1 の約数のときは踏む回数が多いと重なる。約数でも回数が少なければ重ならないので、C ごと捨てずに kC ≥ N − 1 − kC になる手前で止める」に直した
- 指摘 4（直すとよい）：採った。本文を「実際に数えると約 2.9×10^6 回」に、表の回数の列を「Σ_p M/p ≈ M ln ln M」（すべての d の行も Σ_d M/d ≈ M ln M）にし、値に「（実際の回数）」を添えた
- 指摘 5（直すとよい）：採った。内側の和を $\sum_{d \mid k,\ k \le M}$ にした
- 指摘 6（直すとよい・メインへの提案）：front matter の summary・signs は執筆者が変えない項目なので直していない。メインへの提案として再掲する：summary を「… 合計 M/1 + … + M/M ≈ M ln M 回で済むことを使う（M は値の上限）…」、signs の shape を「Σ_{d=1}^{M} Σ_{k=1}^{⌊M/d⌋} f(d, kd)」に。あわせて手引き §6 の「値の上限」の文字を決める
- 指摘 7（直すとよい）：採った。#collect-multiples の箇条と #pitfalls の文を指摘のとおり分けた
- 台帳への提案：検証役の判断により、abc170_d・abc393_e・abc179_c・abc134_d・abc356_e・abc128_f の `checked` に 2026-10-21 を入れる（上の表の最後の行）
- 検査：check_pages エラー 0・警告 0、fix_problems --check 直すべき行 0、check_snippets 期待と違う 0、textlint 0 errors（警告 18 は数式を含む文の誤検出）
