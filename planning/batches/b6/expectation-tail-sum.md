# expectation-tail-sum の問題の補充（b6・工程9）

- 対象：docs/comb/expectation-tail-sum.md（レベル 黄）。今の問題は例題 abc295_e（2157）・力試し abc352_g（2413）で、練習は 0 問
- 結論：練習に置ける候補は 2 問（abc411_e と、易しすぎる入門の arc085_a）。黄の帯（2000〜2399）に入る練習の問題は見つからなかった。力試しの候補を 1 問（hhkb2020_f）挙げる

## 候補

| 問題 ID | 題名 | difficulty | 役割 | 要約 | 方針の要点 | 裏付けの URL |
| --- | --- | --- | --- | --- | --- | --- |
| abc411_e | E. E [max] | 1400（水） | practice | 6 面に値が書かれたサイコロ N 個を振ったときの、出た目の最大値の期待値を mod 998244353 で求める。 | 出てくる値に圧縮し、P(最大値 ≤ v) を各サイコロの「v 以下の面の割合」の積として値の小さい順に更新し、差（または #identity の値がとびとびのときの式）で足す。本文の #kth-value の「値の範囲が広いとき」と落とし穴の「0 を含む積」にそのまま当たる。 | https://qiita.com/Shizen_Tota/items/687ddc17baff09e97176 ・ https://kcpc.hatenablog.com/entry/2025/06/28/233000 |
| arc085_a | C. HSI | 752（基礎） | practice（入門。任意） | 1 回の提出が確率 1/2^M で通るとき、通るまで提出を繰り返す合計時間の期待値を求める。 | 回数 T について P(T ≥ k) = (1 − 1/2^M)^(k−1) の等比級数を足して E[T] = 2^M を出し、1 回の時間を掛ける（#waiting-time の幾何分布）。 | https://drken1215.hatenablog.com/entry/2019/03/23/175300 |
| hhkb2020_f | F. Random Max | 2691（発展） | challenge | N 個の実数をそれぞれ区間 [L_i, R_i] から一様に選んだときの最大値の期待値に (N+1)!·Π(R_i − L_i) を掛けた値を mod 10^9+7 で求める。 | P(最大値 ≤ x) が各値の因子の積で、端点で区切った区分ごとに多項式になることを使い、区分ごとに積分して足す（#continuous と #kth-value の最大値の言い換えを合わせた形）。 | https://drken1215.hatenablog.com/entry/2020/10/11/145500 ・ https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2020/1010_hhkb2020 |

## 確かめたこと

- 実在・題名・difficulty は `python3 tools/ap.py show` で確かめた（2026-10-22）：abc411_e「E. E [max]」1400、arc085_a「C. HSI」752、hhkb2020_f「F. Random Max」2691
- abc411_e：台帳 data/problems.yaml にすでにあり（pages に expectation-tail-sum の practice、status 確認済み）、本文に載っていない。b3 の執筆者・検証役が挙げた候補と同じ。Qiita（Shizen_Tota）は「最大値が x 以下の確率を各サイコロの割合の積で求め、差をとる。値を圧縮して区間に掛ける（双対セグ木）」、kcpc は「P(X = k) = P(X ≤ k) − P(X ≤ k−1)、値を圧縮して imos 法で掛け込み、最大値になりえない値は 0 にする」と書いている。どちらの記事も制約の数値（面の値の範囲）は書いていないので、本文に上限を書くときは別に確かめる
- arc085_a：drken の記事の「証明 2」が、期待値を「k 回以上かかる確率」の和に直して等比級数で 1/p を出している（主解法は 1/p をそのまま使う）。diff 752 で帯から大きく下に離れ、coupon-collector の幾何分布とも重なるので、置くなら入門として最初に置く程度。置かなくてもよい
- hhkb2020_f：drken・ikatakos とも、P(最大値 ≤ x) を区分ごとの多項式の積として持ち、∫ x·F'(x) dx を区分ごとに足している。本文の ∫ P(X > t) dt とは部分積分で同じ値になる（形は少し違う）。b5 の候補で continuous-probability の練習にも挙がっている問題なので、両方の pages に置くかはメインが決める。帯（黄）から上に離れるので力試し

## 見つからなかったもの

- 黄の帯の練習：ap.py の題名検索（Expect・Max・Min・Kth・Random・Dice・Gacha など、diff 1300〜2700）と Web 検索で探したが、tail sum を本筋に使う第三者の解説が見つかる問題はなかった
- 調べて外したもの：abc450_g（2227、Random Subtraction）は最後に残る値の二乗の期待値で tail sum ではない。abc464_f（2225、Random Vault Heist）は第三者の解説が見つからず、何を問うか確かめていない。abc226_h（2813）は continuous-probability の例題で、帯から離れすぎる。abc276_f（1562、Double Chance）は 2 枚の大きい方の期待値だが、解説の多くは BIT で和を数える方針で、このページの手法の練習としては確かめていない
- 新しく使ったドメインはない（qiita.com・kcpc.hatenablog.com・drken1215.hatenablog.com・ikatakos.com はどれも付録 B にある）
