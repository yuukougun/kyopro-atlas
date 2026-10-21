# ext-gcd の報告と提案（工程8b・バッチ b1）

- 書いたファイル：docs/math/ext-gcd.md、snippets/ext-gcd/ext-gcd.{cpp,yaml}、snippets/ext-gcd/linear-congruence.{cpp,yaml}、docs/img/ext-gcd/table.svg
- front matter で変えたもの：complexity・stage（draft）・updated。sections に「応用の型（円周の移動・倍数の余り・面積 1 の格子点・CRT）」（anchor: applications、level はページと同じ）を足した
- 検査の結果：check_pages --page ext-gcd はエラー 0・警告 0。fix_problems --check は ext-gcd では直す行 0（全体では basics/meet-in-the-middle.md の 6 行が出るが、別の執筆者のページ）。check_snippets snippets/ext-gcd は期待と違う 0。textlint はエラー 0、警告 19（数式を含む文の長さ・読点の数・数式内の助詞の重なり・画像の代替テキストの長さ・`[0, L)` の括弧の対・出典の題名の「「」の連続。どれも誤検出として残した）
- 動く図：作っていない（visual は priority 2・static の指定なので、静的な SVG の表 table.svg で代えた）

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc186_e | summary | 「1回に」→「1 回に」（半角数字と全角の間の空白。本文の行は textlint のエラーを消すため手で直した） | 表記の規則（手引き §7） |
| abc060_b | summary | 「（1つ以上）」→「（1 つ以上）」（同上） | 表記の規則 |

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| 互いに素 | coprime | 2 つの整数の最大公約数が 1 であること。$a$ と $m$ が互いに素なら、$a$ は法 $m$ で逆元をもつ。 |

## 手引きへの提案

- 台帳の summary に「1回」「1つ」のような空白のない表記が残っていると、本文の行で textlint のエラーになる。台帳の summary を一括で textlint にかけるか、fix_problems が summary も台帳から作り直すようにすると、執筆者が本文だけ直す食い違いがなくなる（§13.7 と §13.8 が両立しない場合がある）

## 問題の補充の候補

| 問題 ID | 何を問うか | 役割の案 | 裏付けの URL |
| --- | --- | --- | --- |
| abc340_f | 整数の点 (X, Y) が与えられ、原点・(X, Y)・(A, B) の三角形の面積が 1 になる整数の点 (A, B) を 1 つ求める（なければ -1）。面積は \|AY − BX\| / 2 なので AY − BX = ±2 を拡張ユークリッドで解き、gcd(X, Y) が 3 以上なら解なし | 練習（diff 1516、水。abc319 以降の水のページの根拠にもなる） | https://programming-hiroba.com/abc340-f/ （check_noai で noai の指定なしを確認。付録 B のドメイン） |

- 本文の「応用の型」では、台帳にないので問題 ID を出さずに型（面積 1 の三角形の格子点）だけを書いた。台帳に入れば、練習の囲みに abc340_f を足し、方針の折りたたみに「$\lvert AY - BX \rvert = 2$ に直し、$\gcd(X, Y) \mid 2$ を判定、拡張ユークリッドの解を $2/g$ 倍する」を書ける
- frequency_evidence の abc459_g（diff 3123）は難しすぎるので、このページの問題には使わなかった

## 未解決の点

- 出典の programming-hiroba の記事は問題文を載せておらず、制約（出力の範囲 ±10^18 など）は確かめていない。abc340_f の summary を台帳に書くときは、もう 1 件の第三者の解説で問いと制約を確かめたい（kazun-kyopro・oraclesqlpuzzle には記事が見つからなかった）
- abc186_e の解法の詳細の「$K$ が $N$ 以上のこともある」は、drken 氏の記事の制約（$1 \le K \le 10^9$、$2 \le N \le 10^9$）から判断した
- 係数の上界 $\lvert x \rvert \le b/g$、$\lvert y \rvert \le a/g$（$a, b \ge 1$）は、ACL の internal_math.hpp のコメントと、snippets の 1〜60 の全組の assert で確かめた（一般の証明は本文に載せていない）
- 再帰で書く形は文章だけで説明し、コード片にしていない
- gcd-lcm・mod-inverse・crt はまだ stub なので、節（`#ext-gcd` など）へはリンクせず、ページへのリンクにした。mod-inverse の節 `ext-gcd`（拡張ユークリッドによる逆元）は、このページへのリンクで済ませると重複が少ない

## 使った出典

- drken「拡張ユークリッドの互除法 〜 一次不定方程式 ax + by = c の解き方 〜」（qiita、研究の記録経由）：存在条件・一般解
- drken「AtCoder ABC 186 E - Throne (1D, 水色, 500 点)」https://drken1215.hatenablog.com/entry/2020/12/20/015100 ：例題の問いと方針を確認
- drken「AtCoder ABC 060 B - Choose Integers (4Q, 茶色, 200 点)」https://drken1215.hatenablog.com/entry/2024/10/18/025758 ：練習の問いと方針を確認
- ACL v1.6 の document_ja/math.md と atcoder/internal_math.hpp・math.hpp・modint.hpp（手元）：inv_mod・inv_gcd・crt・modint::inv の要件
- 新しく noai を確かめた URL：https://programming-hiroba.com/abc340-f/ （ドメインは付録 B に既出）

## 使用量の目安

- 道具の呼び出し 約 35 回、Web 取得 8 回（検索 5 回）

## 検証の指摘への対応（planning/batches/b1/verify/ext-gcd.md）

- 指摘 1（直すべき）：直した。「4 行目」をやめ、太枠でない $i = 3$ の行（$38 \cdot (-1) + 14 \cdot 3 = 4$）を例にした
- 指摘 2：直した。#min-solution の手順の前に「$a, b > 0$、$c \ge 0$ とする。$c$ が負なら手順 3 の余りも `(… % L + L) % L` で直す」を足した
- 指摘 3：直した。係数の符号が 1 行ごとに入れ替わり $\lvert x_{i+1} \rvert = \lvert x_{i-1} \rvert + q_i \lvert x_i \rvert$ で増え続け、最後の行（図の破線）で $(b/g, a/g)$ になる、という理由を足した
- 指摘 4：直した。法を割り忘れたときの 2 通りの失敗（解なしと誤る・周期を取り違えて最小解を逃す。例 $6x \equiv 3 \pmod 9$ で 2 と 5）を書いた
- 指摘 5：直した。$x^*$ を使う前に「その解を $0 \le x^* < m/g$ とすると」と定義し、円周の箇条で $S$・$T$ を「今の位置」「目標の位置」と定義した（位置の式も $(S + Kx) \bmod N$ と括弧を付けた）
- 指摘 6：直した。使い分けを練習問題の後、参考の前へ移した
- 指摘 7：直した。table.svg の注記 3 行（説明の 1 行と下の 2 行）を 15px にそろえた。幅に収めるため、破線の注記を「何倍足しても 38x + 14y は同じ」に縮めた
- 検査：check_pages --page ext-gcd はエラー 0・警告 0、check_snippets は期待と違う 0、textlint はエラー 0・警告 19（直す前と同じ種類）。fix_problems --check は ext-gcd では 0 行（全体では basics/fractional-binary-search.md の行が出るが、別の執筆者のページ）
- 台帳への提案（検証役の提案に同意）：abc186_e・abc060_b に `checked: 2026-10-21` を入れる
