# lagrange-interpolation の報告（b4）

- 書いたファイル：docs/math/lagrange-interpolation.md、snippets/lagrange-interpolation/eval.{cpp,yaml}（図はなし。catalog の visual は null）
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-22）。sections に `{title: 自作するときの要点と Library Checker, anchor: library}` を足した
- 検査の結果：check_pages（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、check_snippets（1 件、期待と違う 0）、textlint（エラー 0。警告 6 件はどれも数式を含む文の長さ・読点の数の誤検出）
- 使った出典：kmjp（ABC137 F）・rsk0315（ABC137 F）・ikatakos（ラグランジュ補間のページ、ABC208 の記録の F の解法の節だけ）・ei1333.hateblo.jp・Nyaan のライブラリ（nyaannyaan.github.io と GitHub）・library-checker-problems（GitHub）
- 新しく noai を確かめたドメイン：ei1333.hateblo.jp（noai・noimageai の指定なし。2026-10-22 に check_noai.py で確認）→ 付録 B への追加を提案

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc137_f | evidence | 現状の 2 件で足りる（kmjp は補間公式と組立除法、rsk0315 は 1 − (x − i)^(p−1)）。checked を埋める | https://kmjp.hatenablog.jp/entry/2019/08/10/0930 ・ https://rsk0315.hatenablog.com/entry/2019/08/28/235335 |

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| 標本点 | sampling-point | 多項式の値を知っている点。d 次の多項式は異なる d + 1 個の標本点での値で決まる |
| 組立除法 | synthetic-division | 多項式を 1 次式 (x − a) で割る筆算を、係数だけで O(次数) で行う方法 |

本文ではどちらもリンクせず短く定義した（§15-1）。

## 手引きへの提案

- 付録 A の「整数論・代数」に「ラグランジュ補間」「標本点」「組立除法」を足す案。
- 付録 B に ei1333.hateblo.jp を足す。

## 問題の補充の候補

| 問題 ID | 何を問うか | 裏付けの URL |
| --- | --- | --- |
| abc208_f（diff 2772） | 数列の累積和を M 回取った表の N 番目の値（N が巨大）を求める。答えが N の K + M 次式になるので、小さい N の値から補間する | https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2021/0704_abc208 ・ https://nyaannyaan.github.io/docs/problems/editorials/ （手法名がラグランジュ補間の O(N)） |
| arc033_4（diff 2470、参考値） | N 次多項式の x = 0..N での値から x = T の値を mod 10^9+7 で求める。O(N) の補間そのもの | https://kmjp.hatenablog.jp/entry/2015/02/01/1000 ・ https://ei1333.hateblo.jp/entry/2021/07/08/221742 （ARC033 D で検証したと書かれている） |

- abc208_f は 2 つ目の例題（「答えが多項式になる DP」の代表）に向く。発展の概要の例題は 0〜2 なので、例題に足すなら applications 節から例題の小見出しへリンクを張り替える。今は本文で問題 ID を出さず「数列の累積和を何回も取った値を問う型」とだけ書いた。
- arc033_4 は O(d) の補間をそのまま問う代表で、練習（または例題）に向く。

## 未解決の点

- ABC137 F の p の上限は確かめていない（本文では「O(p²) が間に合う大きさ」とだけ書いた）。
- べき乗和を線形篩で O(k) に近づける話は計算量の正確な言い方（素数での累乗が O(k / log k) 回 × O(log k)）を本文で詳しく書いていない。「O(k) に近づく」とぼかした。
- Library Checker の Sum of Exponential times Polynomial は r ≠ 1 で補間以外の考え方（母関数）が要るので、Nyaan 氏の解説を資料にした。verify に載せたままでよいかはメインの判断に任せる。

## 検証の指摘への対応

- 指摘 1〜6 をすべて直した（採らなかったものはない）。指摘 6 は eval.cpp の注釈だけの直しで、cases は変わらない。
- 未解決の点 1（ABC137 F の p の上限）と 3（verify）は、検証で今のままでよいとされたので残した。点 2 は指摘 2 で O(k) と書き直して解消した。
- textlint の警告は 9 件（エラー 0）。増えた分は数式を含む文の長さで、指摘どおりの文言を保つため残した。
- 共有ファイルへの提案：abc137_f の `checked` に 2026-10-22 を入れる（検証役も賛成）。
