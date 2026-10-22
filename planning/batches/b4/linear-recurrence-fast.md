# linear-recurrence-fast の報告（b4）

- 書いたファイル：docs/math/linear-recurrence-fast.md、snippets/linear-recurrence-fast/recurrence.{cpp,yaml}（図はなし。catalog の visual は null）
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-22）。sections は変えていない
- 検査の結果：check_pages エラー0・警告0、fix_problems --check 直す行0、check_snippets 期待と違う0、textlint エラー0（警告19。数式を含む文の長さ・問題の行・資料の一覧の助詞の重複など）。学ぶための資料の一覧は記事の題名（「線形漸化的数列のN項目の計算」など）をそのまま書くため、ja-space-between-half-and-full-width だけをコメントで外した
- コード片：Bostan-Mori・Berlekamp-Massey と、確かめ用の素朴なきたまさ法。手元で d ≤ 30 のランダムな 300 件（法 998244353 での値、係数に 0 を含む場合を含む）で assert が通ることを確かめた
- 使った出典：ryuhe1 の Qiita（手順・2M(d) 対 3M(d)）、arXiv:2008.08822（原典）、ikatakos の berlekamp_massey（2d 項）、ACL document_ja/convolution.md、library-checker-problems の other/ の task.md・info.toml（制約と題名）、例題の解説（drken・rui_er・ikatakos・kmjp）
- 新しく noai を確かめたドメイン：arxiv.org（指定なし）、hashiryo.github.io（指定なし。本文では使っていない）。raw.githubusercontent.com（github.com の Library Checker の問題定義）

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc300_h | summary | a_0 = … = a_{K−1} = 1、a_i = a_{i−1} + … + a_{i−K}（i ≥ K）で定まる数列について、m AND N = m を満たす非負整数 m すべてにわたる a_m の和を 998244353 で割った余りで求める（K ≤ 5×10^4、N ≤ 10^18）。 | https://drken1215.hatenablog.com/entry/2023/05/02/202900 ・ https://kmjp.hatenablog.jp/entry/2023/05/04/0930 |
| abc300_h | evidence | kmjp の記事を追加 | https://kmjp.hatenablog.jp/entry/2023/05/04/0930 |
| abc436_g | evidence | ikatakos の記事を追加（解法の節：答えは 1/((1−y)Π(1−y^{A_i})) の [y^M]、Bostan-Mori で O(d log d log M)） | https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2025/1213_abc436 |

- abc436_g の summary の「≤ M」（和 0 の組を含む）は、ikatakos の [y^M] の式と、rui_er のコード（F[0] = 1 を含む累積和をそのまま出力）で裏付けた。ただし rui_er の本文の式は Σ_{m=1}^{M} f(m) と書いていて食い違う（コードの方が正しいと判断した）。法 998244353 は台帳のとおりで、二つの解説では明記を確かめられなかった

## 用語集への提案

- 特性多項式｜characteristic-polynomial｜線形漸化式 a_n = c_1 a_{n−1} + … + c_K a_{n−K} に対する多項式 x^K − c_1 x^{K−1} − … − c_K。行列 A に対しては det(xI − A) で、A を代入すると零行列になる（Cayley-Hamilton の定理）。
- 線形漸化式｜linear-recurrence｜各項が直前の K 項の定数倍の和で決まる数列の規則 a_n = c_1 a_{n−1} + … + c_K a_{n−K}。母関数は分母が 1 − c_1 x − … − c_K x^K の有理式になる。
- （本文では用語集へのリンクを張っていない。§15-1）

## 手引きへの提案

- 付録 A の正規形に「線形漸化式・特性多項式・きたまさ法・Bostan-Mori・Berlekamp-Massey」を足す（本文はこの表記にそろえた）。
- 学ぶための資料・参考で、記事の題名が半角と全角を空白なしでつなぐ（「第N項」）ときの textlint の扱いを決めておくとよい（今回は ja-space-between-half-and-full-width だけを外した）。

## 問題の補充の候補

- typical90_e（005. Restricted Digits（★7））：使える数字が限られた N 桁の B の倍数の個数。桁 DP のダブリングが想定で、Bostan-Mori の別解がある。research/06 §5.6 に「練」として載っているが台帳にない。裏付け：https://drken1215.hatenablog.com/entry/2021/10/08/231200 ・ https://github.com/E869120/kyopro_educational_90/blob/main/sol/005-03.cpp （今回は中身を読んでいないので、追加するなら別途確かめが要る）

## 未解決の点

- Library Checker の consecutive_terms の解き方は本文で「多項式の逆元と組み合わせる工夫が要る」とだけ書いた（詳しい手順は確かめていない）。
- fps-basics は front matter が draft だが本文の見出しがまだないので、節ではなくページへリンクした。相手の見出しができたら、きたまさ法の節の「多項式の割り算」を fps-basics#polynomial-ops へ張り替えるとよい。
- 例題の並び：tdpc_fibonacci（diff なし）を易しい方として先に置いた。

## 検証の指摘への対応（b4 直し）

- 指摘 1〜6 をすべて本文に反映した（採らなかったものはない）。指摘 5 は「考案者の解説（ryuhe1 氏の Qiita）によると」に改めた
- 台帳への提案（追加）：abc436_g の summary に N・A_i・M の上限を入れるなら、解説で制約の数値を確かめてからメインが反映する（本文では「分母の次数は制約から 10^4 程度」とだけ書いた。根拠：ikatakos・rui_er の解説）。tdpc_fibonacci・abc300_h・abc436_g の checked に 2026-10-22（検証役の提案）
