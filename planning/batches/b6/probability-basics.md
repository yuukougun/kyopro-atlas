# probability-basics の問題の補充（工程9）

- ページ：docs/comb/probability-basics.md（レベル 基礎）
- 今の問題：例題 abc126_c、練習 abc193_d（1 問）。力試しなし
- 確かめた日：2026-10-22。実在・題名・difficulty は `python3 tools/ap.py show` で確かめた
- 台帳 data/problems.yaml でこのページを pages に持つのは abc126_c・abc193_d だけで、どちらも本文にある（台帳だけにある問題はない）
- 補充すると練習は 2 問（abc193_d・abc028_d）になり、目標の 2〜4 問に入る。力試しの候補を 2 つ挙げる（どちらを載せるかはメインの判断）
- 新しく noai を確かめたドメイン（`tools/check_noai.py`、どれも noai・noimageai の指定なし）：fukuro-hoho.hatenablog.com・mmxsrup.hatenablog.com・blog.tiramister.net

## 候補

### abc028_d　D. 乱数生成（diff 920、参考値）

- 役割：practice
- 台帳：未登録。追加の提案（pages: probability-basics の practice）
- 要約：1〜N の整数を独立に一様に 3 回選んだとき、3 つの中央値が K になる確率を求める問題である。
- 方針の要点：全体を順番を区別した N^3 通りとし、中央値が K になる並びを「3 つとも K」「K が 2 つと K 以外が 1 つ」「K 未満・K・K より大が 1 つずつ」に分けて 1 + 3(N−1) + 6(K−1)(N−K) 通りと数え、N^3 で割る（#ratio の「区別して数える・分子と分母の数え方をそろえる」の練習になる。整数のまま割らないよう浮動小数点に直して割る）。
- 裏付け：
    - https://fukuro-hoho.hatenablog.com/entry/2020/11/18/163357
    - https://mmxsrup.hatenablog.com/entry/2016/09/22/014911

### abc008_3　C. コイン（diff 1836、参考値）

- 役割：challenge（帯「基礎 〜1199」から離れるので力試し）
- 台帳：未登録。追加の提案（pages: probability-basics の challenge。probability-symmetry・linearity-of-expectation にも合う）
- 要約：数の書かれた N 枚のコインを一様にランダムな順に並べ、左から順に各コインについて右にある倍数のコインを裏返すとき、最後に表のコインの枚数の期待値を求める問題である。
- 方針の要点：コインごとに表になる確率を求めて足す（期待値の線形性）。値 x のコインに効くのは x の約数のコイン p 枚だけで、その p + 1 枚の並びは同様に確からしいので、x の左にある約数の枚数は 0〜p を等確率でとり、表の確率は「0〜p の偶数の個数 / (p + 1)」になる。
- 裏付け：
    - https://kmjp.hatenablog.jp/entry/2014/05/10/0900
    - https://blog.tiramister.net/posts/abc008-c/（検索結果の要約で同じ方針を確認。本文は開いていない）
- 注意：kmjp の本文の式は p が偶数のとき (p/2)/(p+1) と読めるが、p = 0 で 1 にならないので (p/2 + 1)/(p+1) が正しい（取得の要約が指摘。方針の文には偶数の個数で書いたので式の差は出ない）

### abc463_f　F. Senshuraku（diff 2127）

- 役割：challenge（帯から大きく離れる。b1 の報告の候補を確かめ直したもの）
- 台帳：未登録（frequency_evidence と problem-sets.md の #conditional の行では既に触れている）。追加の提案（pages: probability-basics の challenge）
- 要約：2N 人が最後の N 試合をそれぞれ確率 1/2 で勝ち負けし、最多勝の選手から一様に 1 人を優勝者に選ぶとき、各選手の優勝確率を mod 998244353 で求める問題である。
- 方針の要点：優勝しうるのは最多勝 m か m−1 の選手だけで、対象の選手の試合の勝敗で場合を分け（全確率の公式）、同率で並ぶほかの候補が k 人になる確率を二項係数で表して 1/(k+1) を掛けて足す。
- 裏付け：
    - https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2026/0620_abc463
    - （2 つ目の第三者の解説は検索で見つからなかった）
- 注意：二項係数の前計算と mod の逆元が要り、基礎のページの力試しとしては重い。abc008_3 と両方は載せず、どちらか 1 つにするのがよい

## 見送ったもの

- abc142_a（A. Odds of Oddness、diff 28）：1〜N から一様に選んだ数が奇数である確率で、場合の数の比そのものだが易しすぎる。練習をもう 1 問足すなら先頭に置ける
- arc085_a（C. HSI、diff 752）：成功確率が分かっている試行を成功するまで繰り返す期待値で #expectation に合うが、台帳で coupon-collector の practice。重複を避けて見送った
- abc154_d（D. Dice in Line、diff 485）：期待値の線形性のページの問題
- abc011_4（D. 大ジャンプ、diff 1843）：二項係数で数えて 4^N で割る型だが、台帳で lattice-paths・probability-dp の practice
- past202209_c（C. Biased Dice、diff なし）・math_and_algorithm_w（023. Dice Expectation、diff なし）：今回も第三者の解説が見つからず、問いを確かめられなかった（候補止まり）
- 茶〜緑帯で場合の数の比・余事象だけで解く ABC の確率の問題は、abc028_d のほかに見つけられなかった（ap.py の題名検索「確率」「Probability」「Dice」）
