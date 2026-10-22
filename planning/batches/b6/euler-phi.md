# euler-phi の問題の補充（b6・工程9）

- ページ：docs/math/euler-phi.md（レベル 黄）。今の練習は abc222_g（diff 2242）の 1 問、例題は abc212_g
- 探したところ：(1) b3 の報告 planning/batches/b3/euler-phi.md の「問題の補充の候補」に arc185_e・abc162_e（b3 summary/candidates.md にも同じ記載、abc335_g は multiplicative-order の側として入れなかったもの）。b1 の candidates.md は abc212_g・abc222_g（本文に既にある）だけで、b5 の candidates.md には euler-phi の記載なし。(2) data/problems.yaml で pages に euler-phi を持つが本文にない問題は abc162_e（role: practice）の 1 問。(3) drken 氏のブログのカテゴリ「Euler関数」から abc186_e を見つけた
- 問題の実在・題名・difficulty は `python3 tools/ap.py show` で確かめた（2026-10-22）
- WebSearch の回数の上限に達したため、(3) の探索はカテゴリの一覧をたどる範囲にとどまった
- 下の 3 問をすべて入れると練習は合わせて 3 問（abc222_g・abc162_e・abc186_e）、力試しが 1 問（arc185_e）になる

## 候補

### arc185_e（新規。台帳になし）

- 問題ID：arc185_e
- 題名：E. Adjacent GCD
- difficulty：2185（黄）
- 役割：practice（帯の中。divisor-sum の節の $\gcd(a,b) = \sum_{d \mid a, d \mid b} \varphi(d)$ をそのまま使う。b3 の報告では力試しとしていたが、黄の帯の中なので練習に置ける。役割はメインが決める）
- 要約：数列の長さ M の接頭辞それぞれについて、空でない部分列すべての「隣り合う 2 要素の gcd の和」を合計した値を 998244353 で割った余りで求める。
- 方針の要点：$\gcd(A_x, A_n) = \sum_{d \mid \gcd} \varphi(d)$ と分け、約数 d ごとに「d の倍数である前の要素 $A_i$ の $2^i$ の和」を持てば、$f(n+1) = 2f(n) + \sum_{d \mid A_n} \varphi(d) \cdot p(d)$ で更新できる。
- 裏付け：
    - https://kmjp.hatenablog.jp/entry/2024/10/19/0900 （問いの確認と、φ(d) と d の倍数ごとの 2^i の和で更新する方針。コンテスト中は約数包除で解いたとも書かれている）
- 台帳への追加の提案：pages に {id: euler-phi, role: practice}（b3 の提案どおり zeta-mobius-divisor・divisor-inclusion-exclusion・mobius-function と重なる）

### abc162_e（台帳にあり、本文になし）

- 問題ID：abc162_e
- 題名：E. Sum of gcd of Tuples (Hard)
- difficulty：1662（青）
- 役割：practice（帯の下だが、divisor-sum の節の使いどころとして入りやすい）
- 要約：1 以上 K 以下の整数からなる長さ N の数列すべてについて全体の gcd を求め、その総和を 10^9+7 で割った余りで求める。
- 方針の要点：$g = \sum_{d \mid g} \varphi(d)$ を各列の gcd に当てはめると、答えは $\sum_{d=1}^{K} \varphi(d) \lfloor K/d \rfloor^N$ になり、φ の表を篩で作れば $O(K \log N)$ で求まる。
- 裏付け：
    - https://kmjp.hatenablog.jp/entry/2020/04/12/1000 （問いと、d の倍数だけの列が ⌊K/d⌋^N 個あることを使い、大きい g から引いて gcd がちょうど g の個数を求める方針）
    - https://maspypy.com/atcoder-参加感想-2020-04-12abc-162 （同じ数え方を約数のゼータ・メビウス変換で書いたもの）
- 注意：開いた第三者の解説（kmjp・maspy・ikatakos）はどれも約数包除（メビウス反転）で解いていて、φ の和 $\sum \varphi(d) \lfloor K/d \rfloor^N$ の形を書いた解説は確かめられなかった。φ の形は「$\sum_g g \cdot f(g)$ に $g = \sum_{d \mid g} \varphi(d)$ を代入して和の順を入れ替える」という本ページの divisor-sum の節からの導出になる。本文に載せるなら、方針を「約数包除の別の書き方として φ でも書ける」と述べ、出典は約数包除の解説とするのがよい

### abc186_e（台帳にあり。euler-phi は pages になし）

- 問題ID：abc186_e
- 題名：E. Throne
- difficulty：1461（水）
- 役割：practice（帯より低い。euler-theorem の節の「法が素数でないときの逆元を $a^{\varphi(n)-1}$ で求める」の確かめに向く。帯を厳しく見るなら入れない）
- 要約：N 個の椅子が円形に並び、玉座から S 個先にいる人が 1 手で K 個ずつ進むとき、玉座に着くまでの手数の最小を求める（着けなければ −1、N, K ≤ 10^9、T ≤ 100）。
- 方針の要点：$Kx \equiv -S \pmod{N}$ を gcd で割って K と N を互いに素にし、K の逆元をオイラーの定理から $K^{\varphi(N)-1}$ として試し割りの $O(\sqrt{N})$ で求める。
- 裏付け：
    - https://drken1215.hatenablog.com/entry/2020/12/20/015100 （制約と、解法 (3) として Euler の定理で逆元を求める方針。N が素数とは限らないのでフェルマーの小定理が使えないことも書かれている。主な解法 (1) は拡張ユークリッドの互除法）
- 台帳への追加の提案：既存の pages（mod-inverse:practice・ext-gcd:example）に {id: euler-phi, role: practice} を足す。主な解法は ext-gcd なので、本文の方針の注記に「拡張ユークリッドでも解ける。ここでは φ を使う別解として」と書くとよい

## 除いたもの

- abc212_g（例題）・abc222_g（練習）：本文に既にある
- abc335_g（G. Discrete Logarithm Problems、diff 2614 発展）：位数を P − 1 の約数から求める問題で multiplicative-order の側。帯から離れ、第三者の解説も開いていない（b3 と同じ判断）
- Educational Codeforces Round 81 D（Same GCDs）：φ を使う典型だが AtCoder の問題ではなく、codeforces.com は noai 指定なので除いた
