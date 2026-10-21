# gcd-lcm の報告と提案（工程8b・b1）

- 書いたファイル：docs/math/gcd-lcm.md、snippets/gcd-lcm/euclid.{cpp,yaml}、snippets/gcd-lcm/reduce-fraction.{cpp,yaml}、docs/img/gcd-lcm/euclid-squares.svg
- front matter で変えたもの：complexity・stage（draft）・updated。sections に `{title: 拡張ユークリッド・GCD の性質・素因数の指数へのつながり, anchor: next-steps}` を足した（level はページと同じ基礎）
- 検査の結果：check_pages（エラー 0・警告 0）、check_snippets（2 件とも一致）、textlint（エラー 0、警告 11。数式を含む文の長さ・読点の数・助詞の重なりで、数式の中の読点や `\gcd` の式を含む文の誤検出が主）。fix_problems --check は gcd-lcm の行は 0 件だが、全体では math/harmonic-sum.md の 7 行（`- abc170_d：…` の形のまま）で失敗する（担当外）
- 使った出典：drken の ABC109 C・ABC070 C・ABC125 C の記事、E869120 の典型90 022 の解答例（いずれも付録 B のドメイン）。新しく noai を確かめたドメインはない
- 動く図：catalog の visual は priority 2（長方形から正方形を切り取る互除法）。静的な SVG（16×6）で代えた。動く図にするなら `<div class="kp-viz" data-viz="euclid-squares" data-config='{"a":16,"b":6}'></div>` を #euclid の図の位置に置き、各ステップで「正方形を q 個取り、(b, a mod b) が残る」を caption にする

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc109_c | summary | 数直線上の座標 X から ±D の移動を繰り返して N 個の都市をすべて訪れたいとき、それが可能な最大の D を求める。（「全て」→「すべて」。prh の規則） | 表記の規則（手引き §7） |
| typical90_v | summary | A × B × C の直方体を、すべて同じ大きさの立方体に切り分けるときの最小の切断回数を求める。 | 同上 |
| abc070_c | summary | N 個の時計の針がそれぞれ T_i 秒で一周するとき、すべての針が再び同時に真上を向く最初の時刻を求める。 | 同上 |
| abc125_c | alternatives（gcd-lcm）の summary | N 個の整数のうち 1 つを好きな整数に書き換えたときの、全体の最大公約数の最大値を求める。（「1つ」→「1 つ」） | 同上 |

本文の 4 行は上の値で書いてある（fix_problems は summary を書き換えないことを確かめた）。

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| 互いに素 | coprime | 2 つの整数の最大公約数が 1 であること。共通の素因数をもたない、と言っても同じである。 |
| 既約分数 | irreducible-fraction | 分子と分母が互いに素な分数である。分母を正にそろえると、値の等しい分数の既約な表し方は 1 通りに決まる。 |

（本文では用語集へリンクしていない。足すなら #reduce-fraction の「既約」に付けられる）

## 手引きへの提案

- §13 の 7（台帳の summary が表記の規則に合わないとき）は「本文だけ直さない」とあるが、textlint のエラー 0（§13 の 8）と両立しない。今回は本文の行を規則に合わせて直し、台帳の直しを提案した。どちらを優先するかを手引きに明記してほしい
- fix_problems --check は全ページを見るので、担当外のページ（今回は harmonic-sum）の未展開の行で失敗する。執筆者向けには `--page <id>` での確認を指示に書くとよい

## 問題の補充の候補

| 問題 ID | 何を問うか | 役割の案 | 裏付けの URL |
| --- | --- | --- | --- |
| abc148_c（C. Snack、diff 63） | 2 数の lcm（割ってから掛ける）。最も易しい lcm の練習 | 練習（先頭） | https://drken1215.hatenablog.com/entry/2019/12/22/224100_2 （research/06 §5.4 で確認済みとされる。台帳には未登録） |
| typical90_al（038. Large LCM（★3）） | 2 数の lcm が 10^18 を超えるかを判定し、超えなければ出力する。#lcm-overflow の型そのもの | 練習（台帳では integer-division の練習。gcd-lcm にも練習として足す） | https://github.com/E869120/kyopro_educational_90/blob/main/sol/038.cpp ・ https://drken1215.hatenablog.com/entry/2023/11/21/020301 （台帳の evidence） |
| abc118_c（C. Monsters Battle Royale、diff 646） | 攻撃し合って残る体力の最小値が全体の gcd になる（互除法の操作そのもの） | 練習（台帳では proof-patterns の例題） | https://drken1215.hatenablog.com/entry/2019/02/16/224200 （台帳の evidence） |
| abc248_e（E. K-colinear Line、diff 1292） | K 点以上を通る直線の数（直線を既約な整数の組で表す）。#reduce-fraction（水）の練習 | 練習（台帳では geometry-precision の練習） | https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2022/0416_abc248 （台帳の evidence） |

abc148_c 以外は台帳で確認済みで、ページの割り当て（pages）に gcd-lcm を足すだけでよい。abc319 以降で gcd-lcm を直接使う問題は見つけていない（frequency_evidence の abc460_e は台帳の approach が桁ごとの式変形で、このページの例にはしなかった）。

## 未解決の点

- 例題 ABC109 C で「都市の座標は X と異なる」という制約を書くか迷い、確かめられなかったので書かなかった（解法は差が 0 でも変わらない）
- frequency_evidence の recent 1（abc460_e）は、台帳の approach（桁数ごとの式変形）からは gcd-lcm との関係が読み取れない。根拠として妥当か確かめてほしい
- 互除法の最悪回数（10^9 で 42 回、10^18 で 85 回、long long で 90 回）は手元の Python で数えた値で、research/06 §6.3 と一致した

## 検証の指摘への対応（verify/gcd-lcm.md）

- 指摘 1（回数の上限の条件）：直した。「$a \ge b$ なら、2 回の置き換えで…」とし、「$a < b$ から始めても、1 回目で $(b, a)$ に入れ替わって $a \ge b$ になる」を足した
- 指摘 2（取り込みの範囲）：直した。euclid.cpp の印を `gcd`（my_gcd）と `lcm`（lcm_capped）に分け、#euclid は `gcd`、#lcm-overflow の段落の後に `lcm` を取り込んだ。「上の `lcm_capped`」は「次の `lcm_capped`」にした
- 指摘 3（落とし穴の見出し）：直した。「gcd で割ると 0 除算になる」にした
- 指摘 4（「1つ」「全て」の表記）：本文の見出しは front matter の sections の title と対になるので、本文だけでは直さなかった。メインへの提案は下の「front matter への提案」
- 指摘 5（frequency_evidence の abc460_e）：front matter と台帳にかかわるので直さず、下の提案に回した
- 指摘 6（既約の定義）：用語集の反映がまだなので、手順 1 に「（分子と分母の gcd が 1、すなわち互いに素な状態を既約という）」を足した。用語集に互いに素・既約分数が入ったら、リンクに置き換えてよい

## front matter への提案（検証の指摘 4・5）

| 項目 | いまの値 | 新しい値 |
| --- | --- | --- |
| summary | …1つ除いた gcd を累積 gcd で求め… | …1 つ除いた gcd を累積 gcd で求め… |
| signs の 2 つ目 | 等間隔に移動して全ての点を訪れられる最大の幅（gcd） | 等間隔に移動してすべての点を訪れられる最大の幅（gcd） |
| signs の 3 つ目 | 1つだけ書き換え（取り除い）たときの gcd の最大 | 1 つだけ書き換え（取り除い）たときの gcd の最大 |
| sections の 4 つ目の title | 左右からの累積 gcd（1つ除いた gcd） | 左右からの累積 gcd（1 つ除いた gcd） |
| frequency_evidence | recent 1（abc460_e）・… | abc460_e は gcd を道具として使う程度（中身は gcd-properties の「mod の周期」に近い）。A の判断は「前提として 14 ページに届く」を主にし、abc460_e は gcd-properties の frequency_evidence に移す（または両方に書く）ことを検討 |

- sections の title を直したら、本文の見出し「## 左右からの累積 gcd（1つ除いた gcd） {#prefix-suffix-gcd}」も「1 つ」にそろえる（メインの反映時か、次の直しで執筆者が行う）
- 台帳の abc460_e は `checked` の日付と summary（いまは「（執筆時に確かめる）」）を、担当のページの執筆時に入れる必要がある
