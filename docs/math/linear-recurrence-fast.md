---
id: linear-recurrence-fast
title: 線形漸化式の高速化
aliases: [きたまさ法, Bostan-Mori, Berlekamp-Massey, Fiduccia, 線形漸化式の第 N 項]
type: overview
field: math
chapter: 畳み込みと多項式
order: 410
level: 発展
kind: [線形代数・行列, 畳み込み・多項式]
prerequisites: [matrix-power, fps-basics]
related: [convolution-ntt]
summary: K 項の線形漸化式の第 N 項を、行列累乗より速くきたまさ法 O(K² log N) や Bostan-Mori O(K log K log N) で求める。最初の 2K 項から漸化式を見つける Berlekamp-Massey も使う。
complexity: 第 N 項はきたまさ法（素朴な掛け算）O(K^2 log N)、Bostan-Mori（NTT）O(K log K log N)。漸化式の発見は Berlekamp-Massey で 2K 項から O(K^2)（法は素数）
signs:
  - {type: constraint, text: 線形漸化式の項数 K が数百〜数千で、N ≤ 10^18}
  - {type: phrase, text: 有理式 P(x)/Q(x) の N 次の係数}
  - {type: phrase, text: 答えが線形漸化式を満たしそうだが式が分からない（最初の項から推定する）}
  - {type: shape, text: 'a_n = Σ_{k=1}^{K} c_k a_{n−k} の形の漸化式'}
acl: [convolution]
verify: [kth_term_of_linearly_recurrent_sequence, find_linear_recurrence, consecutive_terms_of_linear_recurrent_sequence]
frequency: C
frequency_evidence: recent 0・前提として届くページなし・古い ABC 2 問
sections:
  - {title: 行列累乗との比較（いつ必要になるか）, anchor: vs-matrix}
  - {title: きたまさ法（x^N mod 特性多項式）, anchor: kitamasa}
  - {title: Bostan-Mori（Q(x)Q(−x) で次数を半分にする）, anchor: bostan-mori}
  - {title: Berlekamp-Massey（漸化式を見つける）, anchor: berlekamp-massey}
  - {title: ACL の convolution を使った実装, anchor: implementation}
stage: draft
updated: 2026-10-22
---

!!! abstract "要点"
    - **何ができるか**：$K$ 項の線形漸化式の第 $N$ 項を、行列累乗より速く求める（きたまさ法なら $O(K^2 \log N)$、Bostan-Mori なら $O(K \log K \log N)$）。漸化式が分からなくても、最初の $2K$ 項から Berlekamp-Massey で漸化式そのものを見つけられる。
    - **いつ使うか**：
        - 線形漸化式の項数 K が数百〜数千で、N ≤ 10^18
        - 有理式 P(x)/Q(x) の N 次の係数
        - 答えが線形漸化式を満たしそうだが式が分からない（最初の項から推定する）
        - a_n = Σ_{k=1}^{K} c_k a_{n−k} の形の漸化式
    - **計算量**：第 $N$ 項はきたまさ法（素朴な掛け算）$O(K^2 \log N)$、Bostan-Mori（NTT）$O(K \log K \log N)$。漸化式の発見は Berlekamp-Massey で $2K$ 項から $O(K^2)$（法は素数）
    - **前提**：[行列累乗](../math/matrix-power.md)、[形式的冪級数と多項式の演算](../math/fps-basics.md)

<!-- textlint-disable -->
別名：きたまさ法・Bostan-Mori・Berlekamp-Massey・Fiduccia・線形漸化式の第 N 項
<!-- textlint-enable -->

線形漸化式の高速化は、$K$ 項の線形漸化式の第 $N$ 項を、$K \times K$ の行列を累乗せずに多項式の計算で求める手法の総称である。きたまさ法は $x^N$ を特性多項式で割った余りを、Bostan-Mori は母関数 $P(x)/Q(x)$ の係数を求める。どちらも、漸化式が分からなければ Berlekamp-Massey で最初の項から見つけてから使う。

記法：数列は 0-indexed で $a_0, a_1, \dots$ とし、漸化式を $a_n = c_1 a_{n-1} + \dots + c_K a_{n-K}$（$n \ge K$）と書く。$[x^n] F(x)$ は $F(x)$ の $x^n$ の係数である。記法の全体は[記法と用語の約束](../start/notation.md)にある。

## 行列累乗との比較（いつ必要になるか） {#vs-matrix}

$K$ 項の線形漸化式は、直近の $K$ 項を並べたベクトルに $K \times K$ の行列を掛ける形に書ける（[行列累乗](../math/matrix-power.md#write-as-matrix)）。行列の積は $O(K^3)$ なので、第 $N$ 項は $O(K^3 \log N)$ かかる。$N \le 10^{18}$（$\log N \approx 60$）とすると、$K = 100$ なら $10^6 \times 60$ 回ほどで間に合うが、$K = 1000$ なら $10^9 \times 60$ 回ほどになり間に合わない。

漸化式の行列は「1 段ずらして最後の行だけが係数」という特別な形で、情報は $K$ 個の係数にしかない。これを $K$ 次の多項式として扱うのが、このページの手法である。

| 手法 | 第 $N$ 項の計算量 | 向いている場面 |
| --- | --- | --- |
| 行列累乗 | $O(K^3 \log N)$ | $K \le 100$ 程度、または遷移が漸化式の形でない一般の線形変換 |
| きたまさ法 | 素朴に $O(K^2 \log N)$ | $K$ が数千まで。法が NTT に向かなくても素直に書ける |
| Bostan-Mori | NTT で $O(K \log K \log N)$ | $K$ が $10^4$〜$10^5$。素朴な掛け算でも $O(K^2 \log N)$ |

状態が $n$ 個の一般の線形な遷移（行列 $A$ の累乗）でも、求めたい値が 1 つの数列なら、その数列は $n$ 項以下の線形漸化式を満たす。$A$ の特性多項式 $\Phi(x)$ について $\Phi(A) = O$（Cayley-Hamilton の定理）なので、$A^i v$ の任意の成分の列が $\Phi$ の係数の漸化式を満たすからである。このときは最初の $2n$ 項を DP で作り、[Berlekamp-Massey](#berlekamp-massey) で漸化式を見つければ、行列を累乗しなくてよい。

## きたまさ法（x^N mod 特性多項式） {#kitamasa}

きたまさ法は、$a_N$ を最初の $K$ 項の線形結合 $a_N = r_0 a_0 + \dots + r_{K-1} a_{K-1}$ で表す係数 $r_i$ を、多項式の余りとして求める。

特性多項式を $\Phi(x) = x^K - c_1 x^{K-1} - \dots - c_K$ とし、多項式 $f(x) = \sum f_i x^i$ に数 $L(f) = \sum f_i a_i$ を対応させる（$x^i$ を $a_i$ に置き換える）。漸化式は $L(x^i \Phi(x)) = a_{i+K} - c_1 a_{i+K-1} - \dots - c_K a_i = 0$ と同じである。$L$ は線形なので、$\Phi$ の倍数はすべて $L$ で 0 に移る。よって

$$
a_N = L(x^N) = L(x^N \bmod \Phi(x))
$$

で、$r(x) = x^N \bmod \Phi(x)$ の係数がそのまま $r_i$ になる。

例：フィボナッチ数列（$c_1 = c_2 = 1$、$\Phi = x^2 - x - 1$）では $x^2 \equiv x + 1$ なので、$x^3 \equiv x^2 + x \equiv 2x + 1$ である。よって $a_3 = 2a_1 + a_0$ で、$a_0 = 0$、$a_1 = 1$ なら $a_3 = 2$ になる。

$x^N \bmod \Phi$ は[繰り返し二乗法](../math/mod-pow.md)で求める。次数 $K$ 未満の多項式どうしを掛けて（$O(K^2)$）、次数 $K$ 以上の項を $x^K = c_1 x^{K-1} + \dots + c_K$ で上から順に下げる（$O(K^2)$）。これを $O(\log N)$ 回行うので $O(K^2 \log N)$ である。掛け算を NTT に、余りを多項式の割り算（[形式的冪級数](../math/fps-basics.md)の逆元を使う）に替えると $O(K \log K \log N)$ になり、これを Fiduccia の方法と呼ぶ。速い版は次の Bostan-Mori の方が簡単で、定数倍も小さい。

## Bostan-Mori（Q(x)Q(−x) で次数を半分にする） {#bostan-mori}

Bostan-Mori は、有理式の係数 $[x^N] \dfrac{P(x)}{Q(x)}$（$\deg P < \deg Q = K$、$Q(0) \ne 0$）を $O(K \log K \log N)$ で求める方法である。線形漸化式の第 $N$ 項はこの形に直せる。

**漸化式を有理式にする**：$A(x) = \sum_{i \ge 0} a_i x^i$、$Q(x) = 1 - c_1 x - \dots - c_K x^K$ とすると、$A(x) Q(x)$ の $x^n$（$n \ge K$）の係数は $a_n - c_1 a_{n-1} - \dots - c_K a_{n-K} = 0$ である。よって $P(x) = A(x) Q(x) \bmod x^K$（最初の $K$ 項と $Q$ の積を $K$ 項で切ったもの）とおけば $A(x) = P(x)/Q(x)$ になる。[母関数](../comb/generating-function-counting.md#dp-as-polynomial)で答えが最初から有理式になる問題（分母が $(1 - x^{a})$ の積など）では、この変換も要らない。

**次数を半分にする**：分母と分子に $Q(-x)$ を掛ける。

$$
[x^N] \frac{P(x)}{Q(x)} = [x^N] \frac{P(x) Q(-x)}{Q(x) Q(-x)}
$$

分母 $V(x) = Q(x) Q(-x)$ は $x$ を $-x$ にしても変わらないので、偶数次の項しか持たず $V(x) = V_e(x^2)$ と書ける。分子 $U(x) = P(x) Q(-x)$ を偶数次と奇数次に分けて $U(x) = U_e(x^2) + x U_o(x^2)$ とすると、$1/V_e(x^2)$ も偶数次の項しか持たないので、$x^N$ の係数に効くのは $N$ と偶奇が同じ側だけである。

$$
[x^N] \frac{P(x)}{Q(x)} =
\begin{cases}
[x^{N/2}] \dfrac{U_e(x)}{V_e(x)} & (N \text{ が偶数}) \\[2ex]
[x^{(N-1)/2}] \dfrac{U_o(x)}{V_e(x)} & (N \text{ が奇数})
\end{cases}
$$

$V_e$ の次数は $K$、$U_e$・$U_o$ の次数は $K$ 未満のままで、$N$ だけが半分になる。$N = 0$ になったら答えは $P(0)/Q(0)$ である。

```text
while N > 0:
    U ← P(x)·Q(−x)        # 畳み込み 1 回
    V ← Q(x)·Q(−x)        # 畳み込み 1 回（偶数次だけ残る）
    P ← U の N と偶奇が同じ次数の係数を並べたもの
    Q ← V の偶数次の係数を並べたもの
    N ← ⌊N/2⌋
return P[0] / Q[0]
```

1 回の繰り返しは長さ $K$ ほどの畳み込み 2 回で、$O(\log N)$ 回なので $O(K \log K \log N)$ である。掛け算を素朴に行っても $O(K^2 \log N)$ で、きたまさ法と同じになる。考案者の解説（ryuhe1 氏の Qiita）によると、掛け算の回数は Fiduccia の方法のおよそ 3 分の 2 である。

偶奇で片側を選ぶ所を変えると、添字の bit に条件を付けた項の和も同じ計算量で求まる（[ABC300 Ex](#practice) がこの形）。

## Berlekamp-Massey（漸化式を見つける） {#berlekamp-massey}

Berlekamp-Massey は、数列の最初の $M$ 項 $s_0, \dots, s_{M-1}$ から、それらをすべて満たす最短の線形漸化式の係数 $c_1, \dots, c_L$ を $O(M^2)$ で求める方法である。途中で割り算をするので、法は素数にする。

使い方の要は、項の数の保証である。真の数列が $K$ 項以下の線形漸化式を満たすなら、最初の $2K$ 項を与えれば真の最短の漸化式が求まる。項が足りないと、与えた項だけに合う別の短い漸化式を返すことがあり、それでは第 $N$ 項を誤る。

そこで、次の手順で使う。

1. 答えの数列が何項以下の漸化式を満たすかを、根拠を持って見積もる。状態が $n$ 個の線形な DP なら $n$ 項以下（[行列累乗との比較](#vs-matrix)の Cayley-Hamilton の定理）、母関数が分母の次数 $D$ の有理式なら $D$ 項以下（分子の次数が分母以上なら、その分の余裕を足す）である
2. 見積もった項数の 2 倍に少し余裕を足した数の項を、素朴な DP で求める
3. Berlekamp-Massey で漸化式を求め、[Bostan-Mori](#bostan-mori) で第 $N$ 項を求める

見積もりが立たないまま「それらしい漸化式が出たから」と使うのは危ない。min や max を含む DP、法が素数でない計算、整数のまま大きくなる値には使えない。

## ACL の convolution を使った実装 {#implementation}

!!! info "ACL では"
    `atcoder::convolution(a, b)`（`<atcoder/convolution>`）が、2 つの列の畳み込み（法の既定は 998244353。テンプレート引数で NTT に向くほかの素数も指定できる）を $O((\lvert a \rvert + \lvert b \rvert) \log (\lvert a \rvert + \lvert b \rvert))$ で返す。法は NTT に向く素数でなければならない。線形漸化式そのものの関数は ACL にない。

Bostan-Mori の 1 回の繰り返しは、$Q(-x)$ を作って畳み込みを 2 回呼び、偶奇で係数を選ぶだけである。最初の $K$ 項と係数から $P$・$Q$ を作る関数と合わせて、次のようになる（完全なプログラムは `snippets/linear-recurrence-fast/recurrence.cpp`。素朴なきたまさ法と、漸化式を直接回した値とで答えを確かめている）。

```cpp
--8<-- "linear-recurrence-fast/recurrence.cpp:bostan-mori"
```

Berlekamp-Massey は、今の漸化式で次の項を予測したずれ $\delta$ が 0 でなければ、最後に長さが伸びた時点の漸化式を $\delta$ に合わせて倍して引き、ずれを消す。

```cpp
--8<-- "linear-recurrence-fast/recurrence.cpp:berlekamp-massey"
```

自作するときに気をつける点は次のとおりである。

- **$P$ を $K$ 項で切る**：最初の $K$ 項の多項式 $a_0 + \dots + a_{K-1} x^{K-1}$ と $Q$ の積を切らずに使うと、次数 $K$ 以上に余分な項が残り、$P/Q$ が元の数列にならない。切るのは最初の $K$ 項と $Q$ の積の、次数 $K$ 以上の部分である。
- **$N$ の型と $N = 0$**：$N \le 10^{18}$ は `long long` で受ける。$N = 0$ でもループに入らず $P(0)/Q(0) = a_0$ を返すことを確かめる。$N < K$ なら最初の項を直接返してもよい。
- **法が NTT に向かないとき（$10^9 + 7$ など）**：ACL の `convolution` はそのままでは使えない。$K$ が数千までなら、畳み込みを素朴な 2 重ループに替えた Bostan-Mori（$O(K^2 \log N)$）で足りる。大きな $K$ で法が $10^9 + 7$ なら、3 つの法で畳み込んで中国剰余定理で戻す（[mod 10^9+7 で欲しいとき](../math/convolution-ntt.md#convolution-ll)）。
- **Berlekamp-Massey の項数**：見積もった項数の 2 倍より少ないと、返った漸化式が与えた項にすべて合っていても、その先で外れることがある。小さい $N$ で素朴な DP と比べて確かめるときは、与えた項より先の値で比べる。

自作したものは Library Checker で確かめる（法はどれも 998244353）。

- [Kth term of Linearly Recurrent Sequence](https://judge.yosupo.jp/problem/kth_term_of_linearly_recurrent_sequence)：$d \le 10^5$ 項の漸化式の第 $k$ 項（$k \le 10^{18}$）。Bostan-Mori をそのまま確かめられる。
- [Find Linear Recurrence](https://judge.yosupo.jp/problem/find_linear_recurrence)：$N \le 10^4$ 項の列を満たす最短の漸化式。Berlekamp-Massey を確かめる。
- [Consecutive Terms of Linear Recurrent Sequence](https://judge.yosupo.jp/problem/consecutive_terms_of_linear_recurrent_sequence)：第 $k$ 項から連続する $M$ 項（$M \le 5 \times 10^5$）。第 $k$ 項を $M$ 回求めると間に合わないので、多項式の逆元（[形式的冪級数](../math/fps-basics.md)）と組み合わせる工夫が要る。

## 学ぶための資料 {#resources}

<!-- textlint-disable ja-space-between-half-and-full-width -->
- ryuhe1 氏の「線形漸化的数列のN項目の計算」（Qiita）：Fiduccia の方法と Bostan-Mori の手順を並べて説明し、掛け算の回数を比べている。Bostan-Mori の考案者の 1 人による日本語の解説である。
- Bostan・Mori の論文「A Simple and Fast Algorithm for Computing the N-th Term of a Linearly Recurrent Sequence」（arXiv）：手法の原典。正しさの証明と計算量の評価がある。
- ikatakos 氏の「数列の漸化式の特定と第N項の計算」：Berlekamp-Massey で漸化式を見つけてから Bostan-Mori で第 $N$ 項を求める、組み合わせの流れ。

<!-- textlint-enable ja-space-between-half-and-full-width -->

## 例題 {#examples}

### TDPC T. フィボナッチ {#tdpc_fibonacci}

<div class="kp-problems" data-role="example" markdown>

- [TDPC T. フィボナッチ](https://atcoder.jp/contests/tdpc/tasks/tdpc_fibonacci)（diff —）：a_1 = … = a_K = 1、a_i = a_{i−1} + … + a_{i−K} で定まる数列の第 N 項を 10^9+7 で割った余りで求める（K ≤ 1000、N ≤ 10^9）。

</div>

方針：$K$ 項の線形漸化式の第 $N$ 項そのものである。$K = 1000$ では行列累乗の $O(K^3 \log N)$ が間に合わないので、きたまさ法か Bostan-Mori を使う。法が $10^9 + 7$ なので、掛け算は素朴な $O(K^2)$ で書く。

??? note "解法の詳細"
    - 添字を 0 から付け直し、$a_0 = \dots = a_{K-1} = 1$ とすると、求めるのは $a_{N-1}$ である。
    - $Q(x) = 1 - x - x^2 - \dots - x^K$、$P(x) = (1 + x + \dots + x^{K-1}) Q(x) \bmod x^K$ とし、Bostan-Mori で $[x^{N-1}] P/Q$ を求める。
    - 掛け算を素朴に行うと $O(K^2 \log N)$ で、$K = 1000$、$\log N \approx 30$ なら $6 \times 10^7$ 回ほどで間に合う。きたまさ法で $x^{N-1} \bmod \Phi$ を求めても同じ計算量である。

### ABC436 G. Linear Inequation {#abc436_g}

<div class="kp-problems" data-role="example" markdown>

- [ABC436 G. Linear Inequation](https://atcoder.jp/contests/abc436/tasks/abc436_g)（diff 2164）：Σ A_i x_i ≤ M を満たす非負整数の組 (x_1, …, x_N) の個数を 998244353 で割った余りで求める（M は非常に大きい）。

</div>

方針：和がちょうど $m$ になる組の数の母関数は $\prod_i \frac{1}{1 - x^{A_i}}$ で、$\frac{1}{1 - x}$ を掛けると和が $m$ 以下の組の数（累積和）になる。答えは有理式 $\frac{1}{(1 - x) \prod_i (1 - x^{A_i})}$ の $x^M$ の係数なので、分母を展開して Bostan-Mori を使う。分母の次数は $1 + \sum A_i$ で、制約から $10^4$ 程度である。

??? note "解法の詳細"
    - 分母 $Q(x) = (1 - x) \prod_i (1 - x^{A_i})$ は、$1 - x^{A_i}$ を 1 つずつ掛けて作る（1 回 $O(D)$、$D = 1 + \sum A_i$）。分子は $P(x) = 1$ である。
    - Bostan-Mori で $[x^M] P/Q$ を $O(D \log D \log M)$ で求める。
    - 別の方法として、個数制限なしのナップサックの DP で最初の $2D$ 項ほどを求め、Berlekamp-Massey で漸化式を見つけてから Bostan-Mori を使ってもよい（$O(D^2 + D \log D \log M)$）。分母がすぐ書けるこの問題では、直接作る方が速い。

## 練習問題 {#practice}

<div class="kp-problems" data-role="practice" markdown>

- [ABC300 Ex. Fibonacci: Revisited](https://atcoder.jp/contests/abc300/tasks/abc300_h)（diff 3209）：a_0 = … = a_{K−1} = 1、a_i = a_{i−1} + … + a_{i−K}（i ≥ K）で定まる数列について、m AND N = m を満たす非負整数 m すべてにわたる a_m の和を 998244353 で割った余りで求める（K ≤ 5×10^4、N ≤ 10^18）。

</div>

??? note "方針"
    母関数 $P(x)/Q(x)$ に Bostan-Mori を使い、$N$ の bit を下から見る。bit が 0 なら $m$ のその bit は 0 なので偶数次の側だけを残し、bit が 1 なら 0 でも 1 でもよいので偶数次と奇数次の側の和を残す。計算量は通常の Bostan-Mori と同じ $O(K \log K \log N)$ である。

## 参考 {#references}

- [ryuhe1「線形漸化的数列のN項目の計算」（Qiita）](https://qiita.com/ryuhe1/items/da5acbcce4ac1911f47a)：Fiduccia の方法と Bostan-Mori の手順、$P(x)$ の作り方、掛け算の回数の比較（約 2 対 3）
- [Alin Bostan, Ryuhei Mori「A Simple and Fast Algorithm for Computing the N-th Term of a Linearly Recurrent Sequence」（arXiv:2008.08822）](https://arxiv.org/abs/2008.08822)：手法の原典と計算量 $O(M(d) \log N)$
- [ikatakos「数列の漸化式の特定と第N項の計算」](https://ikatakos.com/pot/programming_algorithm/number_theory/berlekamp_massey)：Berlekamp-Massey に要る項の数（2d 項）と、Bostan-Mori との組み合わせの流れ
- [ACL のドキュメント「Convolution」（GitHub）](https://github.com/atcoder/ac-library/blob/master/document_ja/convolution.md)：`convolution` の要件と計算量
- [Library Checker の問題定義（GitHub）](https://github.com/yosupo06/library-checker-problems/tree/master/other)：kth_term_of_linearly_recurrent_sequence・find_linear_recurrence・consecutive_terms_of_linear_recurrent_sequence の内容と制約
- [drken「TDPC (Typical DP Contest) T - フィボナッチ」](https://drken1215.hatenablog.com/entry/2023/05/02/160300)：例題の問いの確認と、母関数を作って Bostan-Mori を使う方針
- [rui_er「题解：AT_abc436_g ABC436G Linear Inequation」（中国語）](https://www.cnblogs.com/ruierqwq/p/19355328/abc436g)：例題の母関数と、DP と Berlekamp-Massey と Bostan-Mori を組み合わせる別解
- [ikatakos「AtCoder Beginner Contest 436 E,F,G問題メモ」](https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2025/1213_abc436)：例題の答えを有理式の係数として直接 Bostan-Mori で求める方針（解法の節だけを読んだ）
- [drken「AtCoder ABC 300 Ex - Fibonacci: Revisited」](https://drken1215.hatenablog.com/entry/2023/05/02/202900)：練習の問いの確認と、bit の条件で偶奇の側を選び分ける方針
- [kmjp「AtCoder ABC #300 : Ex - Fibonacci: Revisited」](https://kmjp.hatenablog.jp/entry/2023/05/04/0930)：練習の問いの確認（添字と和を取る m の条件）
