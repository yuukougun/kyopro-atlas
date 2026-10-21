# dp-prefix-sum の報告と提案（工程8b・b1）

- 書いたファイル：docs/dp/dp-prefix-sum.md、snippets/dp-prefix-sum/{pull,push,candies}.{cpp,yaml}、docs/img/dp-prefix-sum/pull-prefix.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21 のまま）。sections は変えていない
- 検査の結果：check_pages（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、check_snippets（3 件すべて一致）、textlint（エラー 0・警告 27）
  - 残した警告：sentence-length・max-comma・no-unmatched-pair はどれも数式（$[l, r)$ の半開区間や $\max(0, \cdot)$ の読点）を含む文の誤検出。no-doubled-joshi（「は」）は数式の中の語を拾ったもの
- 図：catalog の visual（static、priority 2）として pull-prefix.svg を作った（dp の下に累積和を境目に合わせて並べ、dp[7] = S[6] − S[3] を示す）。描画して目で確かめる道具がなく、座標の計算だけで確かめた。表示の確認を検証役に頼みたい
- 使った出典：Series_205（Qiita、EDPC M）、drken のはてなブログ 6 本（abc179_d・abc178_d・abc207_e・abc265_f・abc130_e・abc183_e）、kazun（abc253_e）、ikatakos（abc442_f。解説の部分だけ）、sigma425（TDPC F）、E869120 の GitHub（典型90 042。画像なので題名は記述的に書いた）。題名は title 要素で確かめた。新しく noai を確かめたドメインはない（どれも付録 B のドメイン）

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc207_e | summary | 「数列をいくつかの区間に区切り、K 番目の区間の和が K で割り切れるようにする方法の数を求める。」（prh が「k 番目」を「K 番目」に直すので、textlint のエラーになる。本文の行は手で直してある。fix_problems --page を流すと戻るので台帳を直してほしい。alternatives の summary も同じ） | 手引き §7 |
| abc183_e | pages | dp-prefix-sum に role: practice を足す。節 directional の「方向ごとの累積」の練習に使いたい（本文では型だけを書き、参考に解説を挙げた） | https://drken1215.hatenablog.com/entry/2020/11/16/204900 |
| abc130_e | pages | dp-prefix-sum に role: practice（または challenge）を足す。節 two-dimensional（青）の練習がない。本文では型だけを書いた | https://drken1215.hatenablog.com/entry/2019/06/21/230200 |
| tdpc_semiexp | approach | 「最後に通過した駅で場合分けして窓の和にする（2·dp[i] − dp[i−K] の形にも整理できる）。最後の駅に止まる条件は余事象」。sigma425 の解説は累積和を使わず漸化式の差で O(N) にしているので、「累積和で」と書くと解説と少しずれる | https://sigma425.hatenablog.com/entry/2016/08/02/214547 |

ほかの使った問題（dp_m・abc179_d・abc178_d・typical90_ap・abc253_e・abc442_f・abc265_f）の summary と approach は、evidence の解説と食い違いがなかった。

## 用語集への提案

- 差分（差分配列）｜difference-array｜列の隣り合う値の差を並べた配列。区間 [l, r) に v を足すことが、差分の l に +v、r に −v を書く 2 か所の操作になり、左から累積すると元の列に戻る（いもす法の土台。本文ではリンクしていない。imos のページで足りるなら不要）
- 接尾辞・接頭辞は文字列の語として付録 A にあるが、本文では「配列の端から始まる範囲」の意味でも使った。用語集で配列にも使うと書いておくとよい

## 手引きへの提案

- §13.1 は落とし穴を定型の節とするが、この骨格は sections に `anchor: pitfalls` と長い題名を持つ。§13.2 に従い見出しを sections の title と同じにした（binary-search と同じ状況）。定型にそろえるかはメインで決めてほしい
- technique（水）の目安にある「必要になる場面」「アイデアとなぜ正しいか」「計算量」は sections にないので、最初の節（pull-and-push）の中に太字の段落としてまとめた。sections にない見出しを足してよいかを §13 に書いておくと迷わない

## 問題の補充の候補

- abc183_e（E. Queen on Grid、diff 1288、台帳で確認済み）：壁のあるグリッドで右・下・右下へ何マスでも進めるときの経路数。方向ごとの累積を壁で 0 に戻す。裏付け：https://drken1215.hatenablog.com/entry/2020/11/16/204900
- abc130_e（E. Common Subsequence、diff 1676、台帳で確認済み）：2 つの列の、内容の等しい部分列の組（位置で区別）の数。左上の長方形からの遷移を 2 次元累積和で O(1) にする。裏付け：https://drken1215.hatenablog.com/entry/2019/06/21/230200
- abc222_d（D. Between Two Arrays、diff 865、ap.py で実在を確認。台帳になし）：a_i ≤ c_i ≤ b_i を満たす広義単調増加の列 c の数。最後の値を状態にし、遷移元が [0, x] の接頭辞になるので累積和で O(NM)。緑の入門の練習として易しい側に置ける。裏付け：https://blog.hamayanhamayan.com/entry/2021/10/10/133722
- abc319 以降の問題は abc442_f（2026、累積 min）が既にある。ほかは探していない

## 未解決の点

- 節 by-remainder の「一定の歩幅で飛ぶ遷移元」と個数制限付きナップサックの数え上げは、research（02-dp §4.B、arc104_d の行）の記述と自分の導出に基づく。問題での裏付けは付けていない
- 節 two-dimensional の式 dp[i][j] = [X_i = Y_j]·(1 + W[i][j]) は、drken の解説（空列を dp[0][0] に置く形）を 0-indexed で書き直したもの。添字の対応を検証役に確かめてほしい
- 典型90 042 の方針（9 の倍数 ⇔ 桁和が 9 の倍数、直前 9 項の和）は公式解説が画像のため本文を読めておらず、問題の性質からの導出による
- frequency_evidence の「古い ABC 11 問」のうち abc222_d・abc311_f・abc132_f は、このページでは使っていない（abc132_f は台帳にない）

## 検証の指摘への対応（2026-10-21）

- 指摘 1（直すべき）：#directional の斜めの段落に $a + b$ 一定の向きの累積 $U$ と「向きごとに累積を作って足す」を足し、力試しの ABC265 F の方針を「2 点の間は $a + b$ 一定、外側は 2 本の対角線、計 3 本の線分」に直した
- 指摘 2：窓が一定の幅（典型90 042）と接頭辞（ABC178 D）を箇条書きで分け、総和の文字 $S$ を外した。ABC178 D の方針に「$v \ge 3$、$v = 1, 2$ は 0」を足した
- 指摘 3：一般式の「条件を満たすものだけ」を外し、$X_i \ne Y_j$ は 0・$N$・$M$ の定義・答え $1 + W[N][M]$ を足した
- 指摘 4：挿入 DP の文を #same-row（上限つきの配り方の例の後）へ移し、「前の段の連続した範囲の和になる点で同じ形」と書き直した
- 指摘 5：リンクの文字列をページの題名にそろえ、最初の「スライド最小値」を `dp-segment-tree.md#dp-sliding-window` へのリンクにした
- 指摘 6：図の 12px・13px の文字を 14px にし、viewBox を高さ 350 に広げた。「足す」「引く」と S[k] の注記を下へ移し、境目の点線を遷移元のラベルの所（y 128〜152）で切った
- 指摘 7：コードは変えず、本文に「差分の配列 $D$（コードの `diff`）」「累積した値（コードの `cur`）」と添えた（コード片の検証をやり直さずに済むため）
- 指摘 8：`%` の説明を「割られる数が負なら 0 以下の余りを返す（符号は割られる数に従う）」に直した
- 採らなかった指摘：なし
