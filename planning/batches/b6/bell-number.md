# bell-number の問題の補充（b6・工程9）

- ページ：docs/comb/bell-number.md（レベル 青）。今の練習は abc310_d（diff 1368）の 1 問、例題は abc390_d
- 探したところ：(1) b2 の報告 planning/batches/b2/bell-number.md の「問題の補充の候補」に dp_u・typical90_as（b3 summary/candidates.md にも記載。b1・b5 の candidates.md には bell-number の補充の候補なし）。(2) data/problems.yaml で pages に bell-number を持つが本文にない問題は dp_u・typical90_as の 2 問（どちらも role: practice で台帳に入っている）。(3) 第三者の解説で abc217_g を新たに見つけた
- 問題の実在・題名・difficulty は `python3 tools/ap.py show` で確かめた（2026-10-22）
- 候補 3 問を足すと練習は合わせて 4 問になる

## 候補

### abc217_g（新規。台帳になし）

- 問題ID：abc217_g
- 題名：G. Groups
- difficulty：2047（黄）
- 役割：practice（帯の上端 1999 を少し超えるだけで、手法がこのページの漸化式そのものなので練習に置く。帯を厳しく見るなら challenge）
- 要約：1〜N の番号の N 人を、番号を M で割った余りが等しい 2 人が同じ組に入らないように k 個の空でない組に分ける方法の数を、k = 1, …, N のそれぞれについて 998244353 で割った余りで求める。
- 方針の要点：S(n,k) の漸化式と同じく人 i が新しい組を作るか既存の組に入るかで分け、入れる既存の組が j − ⌊(i−1)/M⌋ 個に減るので dp[i][j] = dp[i−1][j−1] + (j − ⌊(i−1)/M⌋)·dp[i−1][j] とし O(N^2) で求める。
- 裏付け：
    - https://bondo.hateblo.jp/entry/2021/09/05/010120 （上の漸化式と dp[0][0] = 1。bondo.hateblo.jp は付録 B にないので check_noai で確かめた：X-Robots-Tag なし、meta robots="max-image-preview:large"、noai・noimageai の指定なし。付録 B への追加を提案する）
    - https://kmjp.hatenablog.jp/entry/2021/09/05/0900 （問題の設定の確認。解き方は余りの類ごとに既存の組へ入る人数を選ぶ別の DP で、こちらも O(N^2)）
- 台帳への追加の提案：pages に {id: bell-number, role: practice}。包除原理で番号付きの組を数えて k! で割る解き方もあるので（kmjp の記事は公式の解説と別解と書いている）、inclusion-exclusion#surjection の practice にも向く可能性があるが、そちらは確かめていない

### dp_u（台帳にあり、本文になし）

- 問題ID：dp_u
- 題名：U. Grouping
- difficulty：なし（AtCoder Problems に値なし。EDPC は rated の対象外）
- 役割：practice
- 要約：N 羽（N ≤ 16）のうさぎをいくつかのグループに分け、同じグループになった 2 羽の組ごとに決まる得点の和の最大を求める。
- 方針の要点：分け方は B_16 ≈ 1.0×10^10 通りで全列挙できないので、dp[S] ＝ 集合 S を分けたときの最大得点として部分集合の部分集合を列挙する O(3^N) の DP にする（vs-subset-dp の節の対比、確認問題「全列挙か DP か」と同じ形）。
- 裏付け：
    - https://qiita.com/Series_205/items/7d2c57b45179006d0bc6 （N ≤ 16、dp_S = max(f(S), dp_T + dp_{S∖T})、O(3^N) を確かめた）

### typical90_as（台帳にあり、本文になし）

- 問題ID：typical90_as
- 題名：045. Simple Grouping（★6）
- difficulty：なし（典型90 は AtCoder Problems に値なし。★6）
- 役割：practice
- 要約：平面上の N 点を K 個の空でないグループに分け、各グループの中で最も遠い 2 点の距離の、全グループでの最大を最小化する。
- 方針の要点：組の数がちょうど K という S(N,K) 型の分け方だが全列挙ではなく、各部分集合の直径を前計算して dp[i][S] ＝ S を i 組に分けたときの最小値とし、部分集合の部分集合を列挙する O(K·3^N) の DP にする。
- 裏付け：
    - https://raw.githubusercontent.com/E869120/kyopro_educational_90/main/sol/045.cpp （dp[i][mask]、`k = (k - 1) & j` の部分集合の列挙、答えが dp[K][(1<<N)-1] であることを確かめた）
- 台帳の直しの提案：typical90_as の evidence の `https://raw.githubusercontent.com/E869120/kyopro_educational_90/main/sol/044.cpp` は 044（Shift and Swapping、配列の回転とスワップのクエリ）の解答で、この問題のものではない。`.../sol/045.cpp` に直す

## 除いたもの

- abc390_d（例題）・abc310_d（練習）：本文に既にある
- arc096_c（E. Everything on It、diff 3163）：第 2 種スターリング数を使う問題として知られるが、帯（青）から離れすぎるうえ解説を開いて確かめていないので候補にしない
- arc067_c（E. Grouping、diff 2190）：組の大きさごとの多項係数の DP で、台帳では multinomial-coefficient の challenge。集合の分割を数えるが、このページの手法（S(n,k) の漸化式・B_n の見積もり）ではないので除いた
- abc187_f（Close Group、diff 1895）：部分集合の部分集合の DP で subset-enumeration-dp の例題。dp_u・typical90_as と役割が重なるので足さない
- abc453_e（Team Division）・abc375_e（3 Team Division）：題名は組分けだが、台帳の要約と方針ではそれぞれ二項係数の和・和の DP で、このページの手法ではない

## 本文に足すときのメモ

- 練習の並びは易しい順に abc310_d（1368）→ dp_u → typical90_as → abc217_g（2047）が自然。dp_u・typical90_as は「B_N では間に合わないので部分集合の DP」の対比、abc217_g は recurrence の節の漸化式の変形（係数 k が「入れる組の数」に変わる）の練習になる
