# imos の報告と提案（工程8b・b1）

- 書いたファイル：docs/basics/imos.md、snippets/imos/{imos-1d,second-order,imos-2d}.{cpp,yaml}、docs/img/imos/{imos-1d,imos-2d}.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21 のまま）。sections の by-length の title を「区間長ごとの加算に使う」から「区間長や開始時刻の範囲に直して加算する」に変えた（anchor は同じ。ABC462 D の「開始時刻の範囲に直す」型を同じ節に入れたため）
- 検査の結果：check_pages（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、check_snippets（3 件すべて一致。second-order は素朴な方法の結果と assert で照合）、textlint（エラー 0・警告 42）
  - 残した警告：ほとんどが数式の半開区間 $[l, r)$ を括弧の対と誤検出する no-unmatched-pair と、数式を含む文の sentence-length・max-comma。見出し「1 次元のいもす法（閉区間なら右端 + 1 に −x）」の ja-unnatural-alphabet（x は変数）。no-doubled-joshi のうち直せるものは直した
- 動く図：JS は書いていない。置き場の div を imos-1d 節に置いた：`<div class="kp-viz" data-viz="imos" data-config='{"n": 8, "ops": [{"l": 1, "r": 5, "x": 1}, {"l": 3, "r": 7, "x": 2}]}'>`。仕様の案は下の「動く図の仕様」
- 使った出典：いもす研（imoz.jp、新しく check_noai で確かめた：noai の指定なし）、drken（abc183_d・abc369_c）、Reputeless/tenkei_90（GitHub、CC0。028・064 の解答の md を読んだ）、comet725（Qiita。abc462_d・abc466_e）、iwamutsu256（Qiita。abc462_d。記事が問題文を載せているので、解き方の部分だけを参照した）、oraclesqlpuzzle（abc221_d・abc260_e）、ikatakos（abc466 の記録。誤って問題文の節も取得してしまったが、本文には解法の節の内容だけを使い、問題文の表現は使っていない）、programming-hiroba（abc035_c、補充の候補の裏付けだけ）、Qiita t_j_（abc408_c、補充の候補の裏付けだけ）。題名は各ページの title 要素で確かめた

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc462_d | summary | 各人が館にいた時間帯と犯行にかかる時間 D から、犯人 2 人と犯行の開始時刻の組としてありうるものの数を求める。（本文はこの文で書いた） | https://qiita.com/comet725/items/08fa48c68e736d690de7 、https://qiita.com/iwamutsu256/items/424aaf7ee6c55d1f44da |
| abc462_d | approach | 各人を犯行の開始時刻としてありうる範囲 [S_i, T_i − D] に直し、開始時刻ごとの人数をいもす法で数えて c(c − 1)/2 を足す | 同上 |
| abc462_d | evidence | iwamutsu256 の URL を足す（終わりの側を T_i − D + 1 に置く理由が書いてある） | 同上 |
| abc466_e | summary（pages と alternatives の両方） | 表と裏に数が書かれたカードの列で、区間の裏返しを K 回以下行った後の、上を向いた数の和の最大値を求める。（本文はこの文で書いた） | https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2026/0711_abc466 （解法の節）、https://qiita.com/comet725/items/d9928d9fdb242140f987 |

ほかの使った問題（abc183_d・typical90_bl・abc369_c・abc221_d・typical90_ab・abc260_e）の summary と approach は、evidence の解説と食い違いがなかった。

## 用語集への提案

- 隣接差｜adjacent-difference｜列の隣り合う 2 項の差 $A[i] - A[i - 1]$ を並べた列。区間に一律に足すと両端の 2 か所だけが変わり、累積和を取ると元の列に戻る。（本文ではリンクしていない。差分列への言い換えのページと共用するなら足してほしい）

## 手引きへの提案

- 骨格の frequency_evidence の recent 5 のうち abc453_e（fix-variable の力試し）・abc464_e（grid の練習）・abc465_f（prefix-sum-2d の力試し）は、台帳ではこのページの問題でない。いもす法への数え方として妥当か、メインで確かめてほしい（このページには載せていない）
- 基礎のページで「上位の手法とのつながり」にあたる節は、このページでは sections の online 節（BIT・遅延セグ木）が担った。使い分けの定型節とも少し重なる

## 動く図の仕様（priority 1。JS はまだない）

- 名前 `imos`。config：`n`（列の長さ）、`ops`（`{l, r, x}` の配列。半開区間）。2 次元は別の名前（`imos-2d`、config は `h`・`w`・`rects`）にするか、`mode: "2d"` で分けるかをメインで決めてほしい
- ステップ：(1) 空の D（長さ n + 1）と A を表示 → (2) 操作ごとに D[l] に +x、D[r] に −x を書き込む（区間を上に帯で示す）→ (3) 累積のカーソルを左から 1 つずつ進め、cur と A[i] を埋める。caption は「D[l] += x：l から先がすべて x 増える」「D[r] −= x：r から先は打ち消して元に戻る」「A[i] = cur = D[0] + … + D[i]」
- 静的な図 docs/img/imos/imos-1d.svg と同じ例（n = 8、[1, 5) に +1、[3, 7) に +2）にしてある。2 次元は imos-2d.svg の 3 段（四隅 → 横 → 縦）を 1 マスずつ進める

## 問題の補充の候補

- abc035_c（C. オセロ、diff 1096 参考値。台帳にない）：一列の駒の閉区間をくり返し裏返した後の、各駒の色を求める。裏返した回数の偶奇をいもす法で求める（range-flip 節の基本形として練習に向く）。裏付け：https://programming-hiroba.com/abc035-c/
- abc408_c（C. Not All Covered、diff 223。台帳にない）：閉区間への +1 を M 回まとめて行った後の最小値を求める。閉区間の右端 + 1 に −1 を置く基本形。abc319 以降。裏付け：https://qiita.com/t_j_/items/acac189e688d01a5ee69
- abc188_d（台帳で確認済み、event-sort の練習）：座標が大きいときのイベントのソートの練習として、このページにも practice で足してよい（large-coordinates 節）

## 未解決の点

- 図 2 枚は描画して目で確かめる道具がなく、XML として読めることと座標の計算だけを確かめた。文字のはみ出しの確認を検証役に頼みたい
- 例題 abc183_d の「時刻は 0 から 2×10^5 程度」と「半開区間 [S_i, T_i)」は drken の解説の記述に基づく（問題文は見ていない）
- 典型90 028 の「紙の角の座標をマスの範囲に直す」は Reputeless/tenkei_90 の解答コード（1001×1001 の盤に四隅の印）から読み取った
- 使用量の目安：道具の呼び出し約 45 回、Web 取得 約 15 回

## 検証の指摘への対応（2026-10-21）

- 1（直すべき）：#by-length の区間長の段落と力試しの方針で「位置を 1 から M で数える（1-indexed）」と断った（ABC260 E に合わせた）
- 2：時間の長さを $L$ と書き（問題の $D$ と断る）、閉区間なので $-1$ を $T_i - L + 1$ に置くと 1 文足した。練習の方針の ABC462 D もそろえた
- 3：座標圧縮の手順の中で $X[0] < X[1] < \dots$ を定義した
- 4：#range-flip に「表と裏の値・上を向いた値の和の最大」の設定、初期値（$\mathrm{dp}[0][0] = 0$、ほかは $-\infty$）、答えの取り出し方を足した
- 5：「長方形が $N$ 個なら」と、$d$ 次元の角の符号の規則（終わりの側を取った個数の偶奇）を書いた
- 6：「次数の拡張」の節に直した
- 7：2 次元の図を 2 段（① と ② の下に ③ と注記）に組み替え、行と列の番号（番兵を含む）を付けた。viewBox は 782×300 から 500×500、マスの数字は 15、注記は 14。1 次元の図は注記の font-size を 12 から 14 に上げた（行の配置は変えず、幅 698 のまま。狭い幅ではなお小さめだが、注記を本文に移すと図だけで読めなくなるので採らなかった）
- 8：落とし穴の最初の 2 項目を「境界の添字と配列の長さ」1 項目にまとめ、1 次元の節の 3 点へリンクし、2 階の差分と 2 次元の長さをまとめて書いた。「累積の前に値を読む」は残した（確認問題は畳まれていて、落とし穴の一覧から引く読者には要るため）
- 9：「印を置くのと累積は $O(M)$、全体は $r_l$ を求める手間との和で、ABC260 E では $O(N + M)$」に直した
- 検査：check_pages エラー 0・警告 0、fix_problems --check 0、check_snippets 期待と違う 0、textlint エラー 0（警告 43。数式の括弧の誤検出と文の長さ）
