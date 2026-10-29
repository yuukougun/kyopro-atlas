---
title: 整数論・代数
type: generated
---

<!-- tools/gen_site.py が生成する。手で直さない -->

# 整数論・代数

mod、素数・約数、GCD と合同式、floor、行列・線形代数、畳み込み。42 ページ。ページ名の横の印はレベル（[レベルの意味](../start/how-to-use.md#levels)）である。

学ぶ順：[色別ロードマップ](../guide/roadmap.md#reading-order)。使い分け：[数の扱い](../guide/method-comparison.md#numbers)・[繰り返しの高速化](../guide/method-comparison.md#repetition)。問題集：[典型90問](../guide/problem-sets.md#problem-sets-typical90)・[アルゴ数学](../guide/problem-sets.md#problem-sets-math-and-algorithm)。自作：[自作ライブラリの設計と動作確認](../guide/library-design.md)。

## 式と整数の基本

- [Σ の変形](sigma-manipulation.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：二重和の順序交換・添字の範囲の書き換え・付け替え・線形性で、Σ の式を計算しやすい形に変える。
- [整数の割り算と余り](integer-division.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：負の数を含む割り算・余り・切り上げや区間の倍数の個数を、C++ の / と % の切り捨ての向きに注意して正しく求める。

## mod の計算

- [mod の計算の基本](mod-arithmetic.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：答えを m で割った余りで求めるとき、足し算・引き算・掛け算は途中で何度余りを取ってもよい。
- [繰り返し二乗法](mod-pow.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：a^n mod m を、n の2進表記に沿って a, a², a⁴, … を掛け合わせて O(log n) で求める。
- [逆元と mod での割り算](mod-inverse.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：a·x ≡ 1 (mod m) となる逆元 x を求め、mod での割り算を掛け算に直す。
- [modint](modint.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：四則演算のたびに自動で余りを取る型で、mod 付きの数え上げを素直に書ける。
- [フェルマーの小定理と指数の mod](exponent-mod.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>：a&#94;(K&#94;N) のように指数が巨大な累乗の mod を、gcd(a, p) = 1 なら指数を p − 1 で割った余りに直して求める。
- [等比数列の和を mod で求める](geometric-series-mod.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：1 + r + … + r^(n−1) を mod で求める。
- [桁と mod](digit-and-mod.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>：10 進数の桁を mod で考えて、倍数判定・数の連結 x·10^d + y・部分文字列が P の倍数になる個数を求める。

## 素数と約数

- [約数列挙と素数判定](divisor-enum.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：d と N/d が √N を境に対になることを使い、素数判定と約数の列挙を O(√N) で行う。
- [素因数分解とルジャンドルの公式](prime-factorization.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：√N までの数で割れるだけ割り、残りが 1 より大きければそれも素数として、N = Π p^e を O(√N) で求める。
- [エラトステネスの篩](sieve-eratosthenes.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：N 以下の素数を、小さい素数の倍数を順に消して O(N log log N) で列挙する。
- [最小素因数の篩と線形篩](spf-sieve.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：篩のついでに各数の最小素因数を記録し、それで割り続けて O(log n) で素因数分解する。
- [調和級数と倍数の列挙](harmonic-sum.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>：割り切る・割り切られる関係にある組を値ごとに数えるとき、各 d の倍数をすべてたどる二重ループが、値の上限 M に対して合計 M/1 + … + M/M ≈ M ln M 回で済むことを使う。
- [約数の個数の上界と高度合成数](divisor-count-bound.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>：約数（の組）を全部試す全探索が間に合うかを、約数の個数の上界（10^9 以下で 1344、10^18 以下で 103680）から見積もる。
- [区間篩](segmented-sieve.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>：L が 10^12 と大きくても R − L が 10^6 程度なら、√R までの素数で区間 [L, R] だけを篩える。
- [素因数の指数で考える](prime-exponent-vector.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：積が平方数になる組・巨大な lcm・割り切れる回数などを、整数を素数ごとの指数のベクトルとみて素数ごとに独立に考える。
- [オイラーの φ 関数](euler-phi.md) <span class="kp-mini kp-lv-ki" title="difficulty 2000〜2399">黄</span>：1..n で n と互いに素な数の個数 φ(n) を、素因数分解から φ(n) = n Π(1 − 1/p) で求める。
- [大きな数の素数判定と素因数分解](miller-rabin.md) <span class="kp-mini kp-lv-hatten" title="difficulty 2400〜（概要だけ）">発展</span>：10^18 程度の数の素数判定を Miller-Rabin で、素因数分解を Pollard's rho で期待 O(N^{1/4}) で行う。

## GCD と合同式

- [GCD・LCM とユークリッドの互除法](gcd-lcm.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：gcd(a, b) = gcd(b, a mod b) を繰り返して最大公約数を O(log min(a, b)) で求め、lcm は a / gcd × b で求める。
- [拡張ユークリッドの互除法と一次合同式](ext-gcd.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>：互除法の途中経過から ax + by = gcd(a, b) の整数解を求める。
- [GCD の性質](gcd-properties.md) <span class="kp-mini kp-lv-ao" title="difficulty 1600〜1999">青</span>：全体に同じ数を足したときの gcd を隣接差の gcd に直し、左端を固定した区間 gcd が O(log A) 種類しかないことで区間 gcd を速く求める。
- [中国剰余定理](crt.md) <span class="kp-mini kp-lv-ao" title="difficulty 1600〜1999">青</span>：複数の合同式 x ≡ r_i (mod m_i) を同時に満たす x を、拡張ユークリッドで2式ずつ合わせて mod lcm でただ1つに求める。
- [位数・原始根・離散対数](multiplicative-order.md) <span class="kp-mini kp-lv-ki" title="difficulty 2000〜2399">黄</span>：a^k ≡ 1 となる最小の k（位数）を φ(m) の約数から求め、原始根で掛け算を指数の足し算に直す。
- [整数の証明の型](proof-patterns.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：実験で見つけた整数の規則が正しいかを、定番の筋道で確かめる。

## floor と商

- [整数の平方根・K 乗根と累乗数](integer-root.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：⌊√N⌋ を double の sqrt で求めると 10^18 付近で ±1 ずれるので、r² ≤ N < (r+1)² になるまで整数で補正するか二分探索で求める。
- [N 進法](base-conversion.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：N を b で割った余りを並べて b 進表記にし、Horner 法で数に戻す。
- [商の列挙](floor-quotient-enum.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>：Σ_{i=1}^{N} f(⌊N/i⌋) を、⌊N/i⌋ の値が高々 2√N 種類で同じ値の i が区間をなすことを使って O(√N) で求める。
- [乗法的関数の和と素数の個数](multiplicative-function.md) <span class="kp-mini kp-lv-hatten" title="difficulty 2400〜（概要だけ）">発展</span>：N ≤ 10^10 程度で、φ・μ などの乗法的関数の和 Σ_{n≤N} f(n) や N 以下の素数の個数を、商の列挙を使って O(N^{3/4}/log N) などで求める。
- [floor sum](floor-sum.md) <span class="kp-mini kp-lv-ki" title="difficulty 2000〜2399">黄</span>：Σ_{i=0}^{n−1} ⌊(ai + b)/m⌋ を、互除法と同じ形の再帰で O(log m) で求める。
- [Stern-Brocot 木と連分数](stern-brocot.md) <span class="kp-mini kp-lv-hatten" title="difficulty 2400〜（概要だけ）">発展</span>：分母・分子が N 以下で実数に最も近い分数などを、既約分数をすべて 1 回ずつ含む二分木を降りて O(log N) 段で求める。

## 行列と線形代数

- [行列累乗](matrix-power.md) <span class="kp-mini kp-lv-ao" title="difficulty 1600〜1999">青</span>：状態が毎回同じ線形の遷移 v' = Av で変わるとき、K 回後の A^K v を行列の繰り返し二乗法で O(n³ log K) で求める。
- [掃き出し法](gaussian-elimination.md) <span class="kp-mini kp-lv-ao" title="difficulty 1600〜1999">青</span>：行基本変形で行列を階段形にし、連立一次方程式の解なし・一意・無数を判定してランクを O(n³) で求める。
- [XOR 基底](xor-basis.md) <span class="kp-mini kp-lv-ki" title="difficulty 2000〜2399">黄</span>：整数の集合から XOR で作れる値の全体を、最上位 bit が互いに異なる r 個の基底で表す。
- [行列式](determinant.md) <span class="kp-mini kp-lv-hatten" title="difficulty 2400〜（概要だけ）">発展</span>：掃き出し法で上三角にし、対角成分の積に行の交換の回数だけ符号を掛けて行列式を O(n³) で求める。

## 畳み込みと多項式

- [畳み込みの使い方](convolution-ntt.md) <span class="kp-mini kp-lv-ao" title="difficulty 1600〜1999">青</span>：c_k = Σ_{i+j=k} a_i b_j（多項式の積）を ACL の convolution で O(N log N) で求める。
- [FFT・NTT の仕組みと任意 mod の畳み込み](fft-ntt.md) <span class="kp-mini kp-lv-hatten" title="difficulty 2400〜（概要だけ）">発展</span>：畳み込みを自作するときや任意 mod で求めるときに、多項式を 1 の N 乗根での値に変えて各点の積にし、分割統治で O(N log N) で変換する。
- [XOR 畳み込み](hadamard-transform.md) <span class="kp-mini kp-lv-hatten" title="difficulty 2400〜（概要だけ）">発展</span>：c_k = Σ_{i XOR j = k} a_i b_j を、アダマール変換で各点の積に直して O(N log N) で求める。
- [分割統治 FFT・オンライン畳み込み](online-convolution.md) <span class="kp-mini kp-lv-hatten" title="difficulty 2400〜（概要だけ）">発展</span>：多数の多項式の積を次数の小さいものから2つずつ掛けて O(N log² N) で求める。
- [形式的冪級数と多項式の演算](fps-basics.md) <span class="kp-mini kp-lv-hatten" title="difficulty 2400〜（概要だけ）">発展</span>：数列を冪級数とみて、逆元 1/f・log・exp・累乗を O(N log N) で計算し、多項式の割り算・Taylor shift・多点評価も行う。
- [線形漸化式の高速化](linear-recurrence-fast.md) <span class="kp-mini kp-lv-hatten" title="difficulty 2400〜（概要だけ）">発展</span>：K 項の線形漸化式の第 N 項を、行列累乗より速くきたまさ法 O(K² log N) や Bostan-Mori O(K log K log N) で求める。
- [ラグランジュ補間とべき乗和](lagrange-interpolation.md) <span class="kp-mini kp-lv-hatten" title="difficulty 2400〜（概要だけ）">発展</span>：d 次多項式は d + 1 点の値で決まるので、x = 0..d での値から任意の x での値を階乗の逆元を使って O(d) で求める。

## ほかの分野にある関連ページ {#elsewhere}

種類に[整数論](../lists/kind-number-theory.md)・[線形代数・行列](../lists/kind-linear-algebra.md)・[畳み込み・多項式](../lists/kind-convolution.md)のどれかを持つ、ほかの分野のページ。

- [動的計画法](../dp/index.md)：[余り・個数を状態に持つ DP](../dp/dp-mod-state.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>・[動的 DP](../dp/dynamic-dp.md) <span class="kp-mini kp-lv-hatten" title="difficulty 2400〜（概要だけ）">発展</span>
- [グラフ](../graph/index.md)：[剰余を頂点にする最短路](../graph/modular-shortest-path.md) <span class="kp-mini kp-lv-hatten" title="difficulty 2400〜（概要だけ）">発展</span>・[行列木定理](../graph/matrix-tree-theorem.md) <span class="kp-mini kp-lv-hatten" title="difficulty 2400〜（概要だけ）">発展</span>
- [数え上げ・確率・ゲーム](../comb/index.md)：[二項係数の前計算](../comb/binomial-precompute.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>・[LGV 補題](../comb/lgv-lemma.md) <span class="kp-mini kp-lv-hatten" title="difficulty 2400〜（概要だけ）">発展</span>・[母関数の考え方](../comb/generating-function-counting.md) <span class="kp-mini kp-lv-hatten" title="difficulty 2400〜（概要だけ）">発展</span>・[約数包除](../comb/divisor-inclusion-exclusion.md) <span class="kp-mini kp-lv-ao" title="difficulty 1600〜1999">青</span>・[約数・倍数のゼータ変換とメビウス変換](../comb/zeta-mobius-divisor.md) <span class="kp-mini kp-lv-ao" title="difficulty 1600〜1999">青</span>・[メビウス関数とメビウス反転](../comb/mobius-function.md) <span class="kp-mini kp-lv-ki" title="difficulty 2000〜2399">黄</span>・[部分集合の高速ゼータ変換とメビウス変換](../comb/zeta-mobius-subset.md) <span class="kp-mini kp-lv-ki" title="difficulty 2000〜2399">黄</span>・[第 1 種スターリング数](../comb/stirling-first.md) <span class="kp-mini kp-lv-hatten" title="difficulty 2400〜（概要だけ）">発展</span>・[確率・期待値を mod 998244353 で答える](../comb/rational-mod.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>・[閉路のある期待値](../comb/expectation-linear-equations.md) <span class="kp-mini kp-lv-ao" title="difficulty 1600〜1999">青</span>
- [幾何](../geometry/index.md)：[誤差の扱いと整数での処理](../geometry/geometry-precision.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>・[回転・平行移動・アフィン変換](../geometry/rotation-transform.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>
