# b2 提案：dp-dimension-reduction（DP の状態の削減）

- 書いたファイル：docs/dp/dp-dimension-reduction.md、snippets/dp-dimension-reduction/{value-knapsack,skip-penalty,sensor}.{cpp,yaml}、docs/img/dp-dimension-reduction/swap-tables.svg
- front matter で変えたもの：complexity・stage（draft）・updated。sections は骨格のまま（落とし穴は定型の節）
- 検査：check_pages エラー 0・警告 0、fix_problems --check 直す行 0、check_snippets 3 本とも一致（どれも小さい入力で全探索・別の DP と assert で突き合わせる）、textlint エラー 0（警告 10 は助詞の重なりと数式を含む文の長さ）。SVG は render_svg.py の 360px・720px で目視した
- 使った出典：kyopro-friends（EDPC E）、qiita drken（EDPC E）、drken1215（abc325_f・abc315_f）、qiita tototti（abc410_e）、programming-hiroba（abc364_e）、torus711（abc376_f）、blog.hamayanhamayan.com（abc203_f）。どれも付録 B のドメイン。新しいドメインは使っていない
- 動く図：なし（visual は priority 2 の static。静的な SVG で作った）

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc203_f | evidence | `https://blog.hamayanhamayan.com/entry/2021/05/30/230136` を足す | 台帳の ikatakos の URL は執筆時に 503 で読めなかった。hamayan 氏の解説で、操作回数が 30 回程度に収まること・dp[i][t] の定義・二分探索の遷移を確かめた |
| abc325_f | title | 末尾の空白を外す（`Sensor Optimization Dilemma`） | label の生成には影響しないが、abc376_f と同じく AtCoder Problems の題名の末尾に空白がある |
| abc376_f | title | 末尾の空白を外す（`Hands on Ring (Hard)`） | fix_problems は空白を落として label を作ったが、台帳の title に空白が残っている |

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| 支配（DP の状態の） | dominance | 2 つの状態 s, t について、t から続けられる選び方は s からも続けられ、結果も悪くならないとき「s は t を支配する」と言う。支配される状態は表から捨ててよく、値と添字の入れ替えの根拠になる。 |

本文では用語集へのリンクを張っていない（anchor がないと check_pages がエラーにするため）。用語集に足したら、節 dp-swap-key-value の「支配する」に最初の 1 回だけリンクを張ってほしい。

## 手引きへの提案

- §13-5 は「用語集の anchor はまだなくてもリンクを書いてよい」とするが、check_pages は anchor のない用語集へのリンクをエラーにする。どちらかにそろえてほしい（今回はリンクを外した）

## 問題の補充の候補

| 問題 ID | 何を問うか | 裏付けの URL |
| --- | --- | --- |
| abc317_d（台帳では knapsack-01 の練習） | 議席の過半数を取る鞍替えの最小。議席数の総和が小さいので議席数を添字、人数の最小を値にする入れ替えの易しい例 | https://programming-hiroba.com/abc317-d/ |

ABC319 以降の問題は abc325_f（例題）・abc364_e・abc376_f・abc410_e と足りているので、新しい ABC の追加は要らないと判断した。

## 未解決の点

- abc364_e の制約（N ≤ 80、X, Y ≤ 10^4）は、2 つの第三者の解説の計算量の見積もり（O(NXY) ＝ 8×10^9）から確かめた。制約を明記した解説は読めていない（1 つの記事は X, Y ≤ 10^5 と書いていた）。本文の「範囲で選ぶ例」はこの値を使っている
- abc410_e の H・M の上限は解説で確かめられなかったので、本文には数値を書いていない
- abc315_f の上限 C ≤ 28 は自分で見積もった（座標 ≤ 10^4・N ≤ 10^4 は drken 氏の記事で確認）。drken 氏は 30〜50 を使っている
- 骨格の導入で「段の次元の使い回し」は knapsack-01#dp-rolling-array へのリンクで済ませた。catalog の research の (a) 型をこのページで扱わない判断でよいか

## 検証（verify/dp-dimension-reduction.md）への対応

- 指摘 1（直すべき）：確認問題の答えを「28 から 34 へ 6 増えるだけ」に直した
- 指摘 2：コードは 28 のまま残し、cap の節の最後の段落に「上のコードは式で求めた 28 をそのまま使ったが、30 にしてもよい」と断った（本文の 28・29・8.4×10^6 の数値をそのまま使えるため）
- 指摘 3：「$\sqrt{2} \times 10^4$ 以下で、$1.5 \times 10^4$ 未満」に直した（確認問題の答えも）
- 指摘 4：swap-tables.svg の凡例を図の下へ移し、viewBox を 560×660 に詰め、文字を 13〜14px に上げた。図の題も短くした。render_svg の 360px・720px で目視
- 指摘 5：ABC315 F は練習に残した（台帳の role を変えずに済む方）。cap の節の例を「練習の ABC315 F と同じ形」と明記し、練習の方針から節のコードへの言及を外した。例題に移すかはメインの判断に任せる（移すなら台帳の abc315_f の role を example に）
- 指摘 6：「足し算があふれ（符号付き整数のあふれは未定義動作で、多くの環境では負の値になり）」に直した
