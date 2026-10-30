---
id: lagrange-interpolation
title: ラグランジュ補間とべき乗和
aliases: [Lagrange interpolation, 多項式補間, 補間, べき乗和, Faulhaber, 答えが多項式になる]
type: overview
field: math
chapter: 畳み込みと多項式
order: 420
level: 発展
kind: [畳み込み・多項式]
prerequisites: [mod-inverse]
related: [binomial-precompute, fps-basics, gaussian-elimination]
summary: d 次多項式は d + 1 点の値で決まるので、x = 0..d での値から任意の x での値を階乗の逆元を使って O(d) で求める。べき乗和 Σ i^k や、答えが N の多項式になる DP を小さい N で計算して補間するのに使う。
complexity: x = 0..d の値から 1 点の値を O(d)（逆元 1 回を含めると O(d + log p)）、係数の復元 O(d^2)、べき乗和 Σ i^k（i ≤ N）は O(k log k)
signs:
  - {type: phrase, text: 答えが N の多項式になる（小さい N で実験すると分かる）}
  - {type: phrase, text: i = 1..N の i^k の和を N ≤ 10^18 で求める}
  - {type: phrase, text: mod p で p 点の値から多項式の係数を復元する}
  - {type: shape, text: 答え f(N) が N の d 次多項式になる}
acl: []
verify: [shift_of_sampling_points_of_polynomial, sum_of_exponential_times_polynomial]
frequency: C
frequency_evidence: recent 0・前提として届くページなし・古い ABC 1 問
sections:
  - {title: d + 1 点で多項式が決まる理由, anchor: uniqueness}
  - {title: x = 0..d のときの O(d) の補間（階乗の逆元）, anchor: linear-time}
  - {title: べき乗和・多項式になる DP への応用, anchor: applications}
  - {title: 係数の復元（O(d²)）, anchor: coefficients}
  - {title: 自作するときの要点と Library Checker, anchor: library}
stage: done
updated: 2026-10-29
---

!!! abstract "要点"
    - **何ができるか**：$d$ 次多項式は $d + 1$ 点の値で決まるので、$x = 0, 1, \dots, d$ での値から任意の $x$ での値を階乗の逆元を使って $O(d)$ で求める。べき乗和 $\sum i^k$ や、答えが $N$ の多項式になる DP を小さい $N$ で計算して補間するのに使う。
    - **いつ使うか**：
        - 答えが $N$ の多項式になる（小さい $N$ で実験すると分かる）
        - $\sum_{i=1}^{N} i^k$ を $N \le 10^{18}$ で求める
        - mod $p$ で $p$ 点の値から多項式の係数を復元する
        - 答え $f(N)$ が $N$ の $d$ 次多項式になる
    - **計算量**：$x = 0, \dots, d$ の値から 1 点の値を $O(d)$（階乗の逆元の前計算を含む。逆元 1 回の $O(\log p)$ は別）。係数の復元が $O(d^2)$、べき乗和 $\sum_{i=1}^{N} i^k$ が $O(k \log k)$
    - **前提**：[逆元と mod での割り算](../math/mod-inverse.md)

<!-- textlint-disable -->
別名：Lagrange interpolation・多項式補間・補間・べき乗和・Faulhaber・答えが多項式になる
<!-- textlint-enable -->

ラグランジュ補間は、多項式のいくつかの点での値から、ほかの点での値や係数を求める方法である。$N$ が $10^{18}$ のように大きくても、答えが $N$ の $d$ 次多項式だと分かっていれば、$N = 0, 1, \dots, d$ の小さい値だけを計算して $f(N)$ を $O(d)$ で求められる。

このページの記法：多項式の次数を $d$、標本点（値を知っている点）を $x = 0, 1, \dots, d$、その値を $y_i = f(i)$、求めたい点を $t$ とする。計算は素数 $p$ を法として行う（記法の全体は[記法と用語の約束](../start/notation.md)）。

ABC での出題は少なく、F 問題で 2 問ほどである。サインは次の 2 つである。

- 立てた式が $\sum_{i=1}^{N} i^k$ や $\binom{N + c}{r}$ の和のように、$N$ の多項式になる。$N$ だけが巨大で、次数（$k$ や $r$）は $10^5$〜$10^6$ 程度。
- 小さい $N$ で答えを並べると、差を何回か取ると 0 になる（差を $d + 1$ 回取って 0 なら $d$ 次以下）。

ACL に補間はないので自作する。$x = 0, \dots, d$ での補間は 20 行ほどで書ける（[自作するときの要点](#library)）。

## d + 1 点で多項式が決まる理由 {#uniqueness}

$d$ 次以下の多項式 $f$ と $g$ が $d + 1$ 個の異なる点で同じ値なら、$f = g$ である。差 $h = f - g$ は $d$ 次以下で $d + 1$ 個の根を持つが、0 でない $d$ 次以下の多項式の根は $d$ 個以下だからである（根 $a$ ごとに $(x - a)$ で割り切れるので、根が $d + 1$ 個あると次数が $d + 1$ 以上になる）。

法が素数 $p$ なら、0 でない数で割れるので同じ議論が mod $p$ でも成り立つ。ただし点が $p$ を法として異なっている必要があり、次数は $p - 1$ 以下に限られる。

$d + 1$ 点で指定した値をとる $d$ 次以下の多項式があることは、次の式（ラグランジュの補間公式）で具体的に作れることから分かる。

$$
f(t) = \sum_{i=0}^{d} y_i \prod_{j \ne i} \frac{t - x_j}{x_i - x_j}
$$

$i$ 番目の項の積は、$t = x_i$ で 1、ほかの標本点で 0 になる。だから右辺は各標本点で $y_i$ をとる $d$ 次以下の多項式で、一意性からこれが $f$ である。そのまま計算すると $t$ 1 点に $O(d^2)$ かかる。

## x = 0..d のときの O(d) の補間（階乗の逆元） {#linear-time}

標本点が $x_i = i$（$i = 0, \dots, d$）なら、公式の分子と分母がどちらも速く求まる。

- **分母**：$\prod_{j \ne i} (i - j) = \bigl(i (i-1) \cdots 1\bigr) \cdot \bigl((-1)(-2) \cdots (-(d-i))\bigr) = (-1)^{d-i}\, i!\, (d-i)!$ である。[階乗とその逆元の表](../math/mod-inverse.md#inverse-table)があれば $O(1)$ で逆数になる。
- **分子**：$\prod_{j \ne i} (t - j)$ は、前からの積 $L_i = \prod_{j < i} (t - j)$ と後ろからの積 $R_i = \prod_{j > i} (t - j)$ の積である。どちらも $O(d)$ で全部作れる。

よって

$$
f(t) = \sum_{i=0}^{d} (-1)^{d-i}\, y_i \cdot \frac{L_i\, R_i}{i!\, (d-i)!}
$$

を $O(d)$ で計算できる。逆元は $d!$ の 1 回だけで、あとは掛け算である（[階乗の逆元を後ろから作る理由](../comb/binomial-precompute.md#fact-ifact)）。

例：$f(x) = x^2$ で $y = (0, 1, 4)$、$d = 2$、$t = 3$ とする。$i = 0$ の項は $y_0 = 0$ なので 0 である。$i = 1$ の項は $(-1)^1 \cdot 1 \cdot \frac{3 \cdot 1}{1! \cdot 1!} = -3$、$i = 2$ の項は $(-1)^0 \cdot 4 \cdot \frac{3 \cdot 2}{2! \cdot 0!} = 12$ で、合計 $9 = 3^2$ になる。

標本点が等差数列 $x_i = a + ih$ でも、分母が $h^d$ 倍になるだけで同じように $O(d)$ で計算できる。標本点がばらばらなら 1 点に $O(d^2)$ かかる。

## べき乗和・多項式になる DP への応用 {#applications}

**べき乗和**：$S_k(n) = \sum_{i=1}^{n} i^k$ は $n$ の $k + 1$ 次の多項式である（Faulhaber の公式。$k = 1$ なら $n(n+1)/2$）。$S_k(0), S_k(1), \dots, S_k(k+1)$ の $k + 2$ 点を累積和で作り、$t = n$ で補間する。$i^k$ を繰り返し二乗法で求めると全体は $O(k \log k)$ である。$i^k$ が $i$ について乗法的（$(ij)^k = i^k j^k$）なことを使い、素数（約 $k / \ln k$ 個）でだけ $O(\log k)$ の累乗を計算し、合成数は線形篩で $p^k \cdot (i/p)^k$ と 1 回の掛け算で埋めると $O(k)$ になる。

**答えが多項式になる DP**：次の性質を組み合わせて、答えが $N$ の何次式かを見積もる。

- $\binom{N + c}{r}$ は $N$ の $r$ 次式である。
- $d$ 次式 $g(i)$ の和 $\sum_{i=1}^{N} g(i)$ は $N$ の $d + 1$ 次式である。累積和を $M$ 回取ると次数が $M$ 上がる。
- 多項式どうしの積の次数は次数の和である。

次数が $D$ と分かれば、$N = 0, 1, \dots, D$ の答えを DP や愚直な計算で求め、[O(d) の補間](#linear-time)で $f(N)$ を出す。数列の累積和を何回も取った値を問う型が典型である。次数の見積もりに自信がなければ、$D + 2$ 点目を計算して補間の値と一致するかで確かめる。

!!! warning "多項式にならない例"
    $2^N$ や $\lfloor N/2 \rfloor$ を含む答えは多項式ではない。$\lfloor N/2 \rfloor$ のように偶奇で式が変わるときは、$N$ の偶奇ごとに別の多項式として補間する。$N$ の範囲で式が切り替わる（$N \le K$ と $N > K$ で場合分けがある）ときも、切り替わった後の点だけを標本点にする。

## 係数の復元（O(d²)） {#coefficients}

値ではなく係数が欲しいときは、補間公式を係数ごとに展開する。素朴には $d + 1$ 個の積を毎回展開して $O(d^3)$ かかるので、次の手順で $O(d^2)$ にする。

1. $M(x) = \prod_{j=0}^{d} (x - x_j)$ の係数を、1 次式を 1 つずつ掛けて $O(d^2)$ で作る。
2. 各 $i$ について、$M(x)$ を $(x - x_i)$ で割った商（組立除法で $O(d)$）が $\prod_{j \ne i}(x - x_j)$ の係数である。
3. それに $y_i / \prod_{j \ne i}(x_i - x_j)$ を掛けて足し込む。分母は $i$ ごとに $O(d)$ で、標本点が $0, \dots, d$ なら階乗で $O(1)$ である。

組立除法は、商の係数を次数の高い方から $q_d = m_{d+1}$、$k = d, d-1, \dots, 1$ について $q_{k-1} = m_k + x_i\, q_k$ と求める（$M(x)$ は $d + 1$ 次なので商は $d$ 次）。余りは $m_0 + x_i\, q_0 = M(x_i) = 0$ になるので検算に使える。

法 $p$ で $x = 0, 1, \dots, p-1$ の全部の値が分かっているときは、フェルマーの小定理で割り算を避けられる。$a \not\equiv 0$ なら $a^{p-1} \equiv 1$、$a \equiv 0$ なら $0$ なので、$1 - (x - i)^{p-1}$ は $x = i$ で 1、ほかの点で 0 になる。$y_i \bigl(1 - (x - i)^{p-1}\bigr)$ を、$(x - i)^{p-1}$ を二項定理で展開して足せば、やはり $O(p^2)$ で係数が出る（[例題 ABC137 F](#abc137_f)）。

連立一次方程式 $\sum_k c_k x_i^k = y_i$ を[掃き出し法](../math/gaussian-elimination.md#mod-p)で解いても係数は出るが $O(d^3)$ である。$d$ が $10^5$ 以上なら $O(d \log^2 d)$ の方法（[形式的冪級数](../math/fps-basics.md#polynomial-ops)の多点評価・補間）が要る。

## 自作するときの要点と Library Checker {#library}

$x = 0, \dots, d$ の値から $f(t)$ を返す関数と、それを使うべき乗和の例である。

```cpp
--8<-- "lagrange-interpolation/eval.cpp:core"
```

完全なプログラム：[`eval.cpp`](https://github.com/yuukougun/kyopro-atlas/blob/main/snippets/lagrange-interpolation/eval.cpp)（GitHub）。`mint` は ACL の `modint998244353`（[modint](../math/modint.md)）。
{ .kp-code-src }

- $t \le d$ なら $y_t$ をそのまま返す。$t$ が負の場合や $p$ 以上の場合も、$t$ を $p$ で割った余りを使えばよい（多項式の値は $t \bmod p$ だけで決まる）。
- 分子を「全体の積 $\prod_j (t - j)$ を $(t - i)$ で割る」で求めない。$t \bmod p$ が $0, \dots, d$ のどれかと一致すると 0 で割ることになる（$t = p$ や $t = p + 1$ で起きる）。前後からの積なら割り算がない。
- 点の数は次数より 1 つ多い。べき乗和 $\sum_{i \le n} i^k$ は $k + 1$ 次なので $k + 2$ 点が要る。1 つ少ないと、値は出るが誤った答えになる。
- 階乗の逆元を使うので $d < p$ が必要である。法が $10^9 + 7$ や 998244353 なら問題にならない。

完全なプログラム（[`snippets/lagrange-interpolation/eval.cpp`](https://github.com/yuukougun/kyopro-atlas/blob/main/snippets/lagrange-interpolation/eval.cpp)）は、小さい $k$・$n$ で愚直な和と比べ、$n = p$ のように $t \bmod p$ が標本点と重なる場合も確かめたものである。

Library Checker の対応：

- [Shift of Sampling Points of Polynomial](https://judge.yosupo.jp/problem/shift_of_sampling_points_of_polynomial)：$f(0), \dots, f(N-1)$ から $f(c), \dots, f(c + M - 1)$ を求める。1 点ずつの $O(d)$ では $O(NM)$ になり、上限（$N, M \le 2^{19}$）では畳み込みを使う速い方法が要る。小さい入力で 1 点の補間を確かめるのに使える。
- [Sum of Exponential times Polynomial](https://judge.yosupo.jp/problem/sum_of_exponential_times_polynomial)：$\sum_{i=0}^{n-1} r^i i^d$ を求める。$r = 1$ がべき乗和である（$0^0 = 1$ の約束に注意）。$r \ne 1$ の扱いは学ぶための資料の Nyaan 氏の解説にある。$d \le 10^7$ なので $i^d$ を線形篩で作る。
- [Polynomial Interpolation](https://judge.yosupo.jp/problem/polynomial_interpolation)：任意の点からの係数の復元。$N \le 2^{17}$ なので $O(N^2)$ では間に合わず、$O(N \log^2 N)$ の方法の確認用である。

## 学ぶための資料 {#resources}

- [ikatakos「ラグランジュ補間」](https://ikatakos.com/pot/programming_algorithm/linear_algebra/lagrange_interpolation)：一意性（Vandermonde の行列式）、$O(d^2)$ の公式、等差数列の標本点での $O(d)$ 化、係数の復元、答えが多項式かどうかの見分け方までが 1 ページにまとまっている。
- [ei1333「ラグランジュ補間」](https://ei1333.hateblo.jp/entry/2021/07/08/221742)：連続した標本点での $O(d)$ の補間を、前後からの積と階乗で書く手順とコード。
- [Nyaan「$\sum_{i}a^i f(i)$」](https://nyaannyaan.github.io/library/fps/sum-of-exponential-times-poly.hpp)：べき乗和に等比数列が掛かった和を、母関数を使って $O(d + \log p)$ で求める方法。

## 例題 {#examples}

### ABC137 F. Polynomial Construction {#abc137_f}

<div class="kp-problems" data-role="example" markdown>

- [ABC137 F. Polynomial Construction](https://atcoder.jp/contests/abc137/tasks/abc137_f)（diff 2402）：素数 p と 0/1 の列 a_0, …, a_(p−1) が与えられるとき、f(i) ≡ a_i (mod p) を満たす p − 1 次以下の多項式 f の係数を求める。

</div>

方針：$p$ 点の値が分かっているので、$p - 1$ 次以下の多項式は一意に決まる（[一意性](#uniqueness)）。値ではなく係数が問われるので、[係数の復元](#coefficients)を $O(p^2)$ で行う。制約の $p$ は $O(p^2)$ が間に合う大きさである。

??? note "解法の詳細"
    - 割り算を避ける書き方：$a_i = 1$ の $i$ ごとに $1 - (x - i)^{p-1}$ を足す。$(x - i)^{p-1} = \sum_{k} \binom{p-1}{k} x^k (-i)^{p-1-k}$ なので、二項係数と $(-i)$ の累乗の表で $x^k$ の係数を $O(p)$ で足し込める。全体で $O(p^2)$ である。
    - 補間公式で書く場合：$M(x) = \prod_{j=0}^{p-1}(x - j)$ を作り、$a_i = 1$ の $i$ ごとに $M(x)$ を $(x - i)$ で組立除法し、分母 $\prod_{j \ne i}(i - j)$ の逆元を掛けて足す。
    - 係数は $0$ 以上 $p - 1$ 以下で出力するので、引き算の後に $p$ を足して余りを取る。

## 参考 {#references}

- [ikatakos「ラグランジュ補間」](https://ikatakos.com/pot/programming_algorithm/linear_algebra/lagrange_interpolation)：学ぶための資料。一意性の根拠、等差数列の標本点での $O(d)$ 化、答えが多項式かどうかの見分け方
- [ei1333「ラグランジュ補間」](https://ei1333.hateblo.jp/entry/2021/07/08/221742)：学ぶための資料。前後からの積と階乗による $O(d)$ の補間
- [Nyaan「$\sum_{i}a^i f(i)$」](https://nyaannyaan.github.io/library/fps/sum-of-exponential-times-poly.hpp)：学ぶための資料。Sum of Exponential times Polynomial の解き方
- [kmjp「AtCoder ABC #137 : F - Polynomial Construction」](https://kmjp.hatenablog.jp/entry/2019/08/10/0930)：例題 ABC137 F の補間公式と組立除法による $O(p^2)$ の方針
- [rsk0315「AtCoder Beginner Contest 137 F: Polynomial Construction」](https://rsk0315.hatenablog.com/entry/2019/08/28/235335)：例題 ABC137 F の $1 - (x - i)^{p-1}$ による割り算のない方針
- [ikatakos「AtCoder Beginner Contest 208 E,F問題メモ」](https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2021/0704_abc208)：累積和を繰り返した値が多項式になることと次数の見積もり（解法の節だけを読んだ）
- [yosupo06「library-checker-problems」](https://github.com/yosupo06/library-checker-problems)：対応する問題の名前と制約（polynomial・other のディレクトリ）
