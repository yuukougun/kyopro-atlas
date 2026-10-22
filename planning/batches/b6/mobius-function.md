# mobius-function の問題の補充（工程9）

- ページ：docs/comb/mobius-function.md（レベル 黄）
- 今の問題：例題 agc038_c（2327）・練習 agc039_c（2379）・力試し abc230_g（2516）
- 探した所：b1・b3・b5 の candidates.md（b3 に abc020_d・arc185_e・abc248_g）、b3 の報告 planning/batches/b3/mobius-function.md の「問題の補充の候補」、data/problems.yaml（このページを pages に持つのは上の 3 問だけで、本文にない問題はなかった）、ap.py の題名検索（GCD・Coprime・LCM・Prime の 1500〜2800）、drken の「メビウスの反転公式」カテゴリ（5 件。うち AtCoder で ap.py に載るのは abc304_f・agc039_c）
- 実在・題名・difficulty はすべて `python3 tools/ap.py show` で確かめた（2026-10-22）

## 候補

### 練習（practice）

| 問題 ID | 題名 | difficulty | 役割 | 要約 | 方針の要点 | 裏付けの URL |
| --- | --- | --- | --- | --- | --- | --- |
| abc304_f | F. Shift Table | 1619 | practice | '.' と '#' からなる長さ N の予定 S について、'#' の一部を '.' に変えてできる列のうち、N 未満の N の約数 M を周期に持つものの数を mod 998244353 で求める。 | 周期 d を持つ列の数 F(d) = 2^(自由な剰余類の数) を約数ごとに数え、最小周期がちょうど d の数を F(d) = Σ_{e\|d} f(e) の反転で戻し、答えを F(N) − f(N) = −Σ_{d\|N, d<N} μ(N/d) F(d) とする。 | https://drken1215.hatenablog.com/entry/2023/06/07/153403 |
| arc185_e | E. Adjacent GCD | 2185 | practice | 列 A の各接頭辞について、空でない部分列すべての「隣り合う要素の gcd の和」の総和を mod 998244353 で求める。 | 答えの漸化式 f(n+1) = 2f(n) + Σ_{x<n} 2^x gcd(A_x, A_n) の gcd を Σ_{d\|gcd} φ(d) に置き換え（本文の応用の型で f(n) = n のときの重み w = φ）、d ごとに「d の倍数である A_i の 2^i の和」を持って更新する。 | https://kmjp.hatenablog.jp/entry/2024/10/19/0900 |
| abc206_e | E. Divide Both | 1745 | practice（優先度は低い） | L ≤ x, y ≤ R の組で、g = gcd(x, y) が 1 でなく、x/g と y/g がどちらも 1 でないものの数を求める（R ≤ 10^6）。 | gcd ≠ 1 の組の数を「全体 − 互いに素な組」とし、互いに素な組を Σ_d μ(d)·c(d)^2（c(d) は区間の d の倍数の数）で数え、x \| y または y \| x の組を引く。 | https://drken1215.hatenablog.com/entry/2021/06/25/121800 |

### 力試し（challenge）

| 問題 ID | 題名 | difficulty | 役割 | 要約 | 方針の要点 | 裏付けの URL |
| --- | --- | --- | --- | --- | --- | --- |
| abc248_g | G. GCD cost on the tree | 2514 | challenge | 各頂点に正の整数が書かれた木で、すべての 2 頂点の組についての「パス上の値の gcd × パスの頂点数」の総和を求める。 | d ごとに値が d の倍数の頂点だけの森を作り、パスの頂点数の和 g(d)（gcd が d の倍数のパス）を木 DP で数え、gcd がちょうど d の分を倍数について戻して Σ d·f(d) とする。 | https://kmjp.hatenablog.jp/entry/2022/04/18/0900 |
| abc020_d | D. LCM Rush | 2695（参考値） | challenge | 1 ≤ i ≤ N について lcm(i, K) の総和を mod 10^9+7 で求める（N, K ≤ 10^9）。 | gcd(i, K) = M ごとに分けて i = M·i' とし、i' ≤ ⌊N/M⌋ で K/M と互いに素な i' の和を、K/M の素因数の部分集合（μ(d) ≠ 0 の約数 d）について符号付きで足す。 | https://tsutaj.hatenablog.com/entry/2017/07/01/073648 |

## 確かめた内容と注意

- abc304_f：drken の記事が F(d) = Σ_{e|d} f(e) をメビウス反転で戻し、答えを −Σ μ(N/d) F(d) と書いていることを確かめた。台帳では kmp の例題・divisor-inclusion-exclusion の練習（例題は 1 ページだけなので、ここは練習にできる）。練習の agc039_c と同じ「周期の数え上げ」の型で、その易しい版として前に置ける
- arc185_e：kmjp の記事は φ(d) を「約数の分を引いて」求める書き方で、μ は直接は出てこない。本文 #gcd-one の節の「f(n) = n なら w = φ」の型の練習として置く。台帳にない（b3 で 4 ページが同じ問題を挙げた。持ち主をどこにするかはメインで決める）
- abc206_e：drken の記事の主な解法は約数包除（大きい順に倍数を引く）で、メビウス関数は「約数包除をメビウス関数で行う」別解として触れているだけ。kyo-pro（https://kyo-pro.hatenablog.com/entry/ABC206E）も倍数を引く方法で μ は使わない。μ の式 Σ μ(d) c(d)^2 は本文の型をそのまま当てたもので、自分で導いた。台帳では divisor-inclusion-exclusion の例題。練習が 2〜3 問で足りるなら外してよい
- abc248_g：kmjp の記事は「d の倍数の頂点の森」と「大きい d から倍数の分を引く」で解いており、μ・φ は使っていない。本文 #vs-divisor-ie の書き換え（倍数を引く ⇔ μ の和）の範囲で、μ で書いても同じ。N と値の上限は記事の文では確かめておらず、コードの配列の大きさから 10^5 程度と読める。2514 で帯より上なので力試し
- abc020_d：tsutaj の記事が gcd で分けて互いに素な数の和を素因数の部分集合の包除で求めることを確かめた（b3 の候補と同じ）。2695 は参考値で、帯から遠いので力試し（発展寄り）。tsutaj.hatenablog.com は付録 B にないので check_noai で確かめた（noai・noimageai の指定はない）。付録 B への追加の提案
- 練習に置くと、合わせて 3 問（abc304_f・arc185_e・agc039_c）、abc206_e も入れれば 4 問になる

## 採らなかったもの

- abc162_e（1662）：Σ gcd の型だが、台帳では divisor-inclusion-exclusion の例題・euler-phi の練習で、すでに 2 ページにある。arc185_e と型が重なるので挙げない
- abc195_f・abc263_g・abc191_f・abc136_e・arc126_c など題名に GCD・Coprime を含む問題：μ を使う解説を確かめていない（b3 の報告でも別の手法と見ている）ので候補にしない
- drken の「メビウスの反転公式」カテゴリの arc064_f（Rotated Palindromes）は ap.py で見つからなかった（ID の形が違う可能性がある）。帯も赤で遠いので深追いしていない
