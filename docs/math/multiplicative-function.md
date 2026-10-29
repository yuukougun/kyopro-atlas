---
id: multiplicative-function
title: 乗法的関数の和と素数の個数
aliases: [ディリクレ積, Dirichlet convolution, 杜教筛, Min_25, 乗法的関数の prefix sum, 素数計数, prime counting, Lucy DP, Meissel-Lehmer]
type: overview
field: math
chapter: floor と商
order: 290
level: 発展
kind: [整数論]
prerequisites: [euler-phi, floor-quotient-enum]
related: [mobius-function, zeta-mobius-divisor, spf-sieve, sieve-eratosthenes]
summary: N ≤ 10^10 程度で、φ・μ などの乗法的関数の和 Σ_{n≤N} f(n) や N 以下の素数の個数を、商の列挙を使って O(N^{3/4}/log N) などで求める。関数どうしの関係はディリクレ積で表す。
complexity: 素数の個数・素数の和は Lucy DP で O(N^{3/4}/log N)、φ・μ の和は杜教篩で O(N^{2/3})（N^{2/3} までの表を前計算）、一般の乗法的関数の和は Min_25 篩で O(N^{3/4}/log N) 程度（再帰の実装は Θ(N^{1−ε}) だが N ≤ 10^11 では十分速い）。どれもメモリは O(√N)〜O(N^{2/3})
signs:
  - {type: constraint, text: 'N ≤ 10^10〜10^11 で Σ_{n≤N} f(n)（f は φ・約数の個数など）を求める'}
  - {type: phrase, text: N 以下の素数の個数・素数の和}
acl: []
verify: [counting_primes, sum_of_totient_function, sum_of_multiplicative_function]
frequency: C
frequency_evidence: recent 0・前提として届くページなし・古い ABC 0 問
sections:
  - {title: 乗法的関数（φ・μ・d・σ）とディリクレ積（φ * 1 = id など）, anchor: dirichlet}
  - {title: 素数の個数・素数の和（Lucy DP）, anchor: prime-counting}
  - {title: 和の求め方の概要（杜教篩・Lucy DP・Min_25 篩）, anchor: prefix-sums}
  - {title: 公開ライブラリと自作するときの要点, anchor: library}
stage: reviewed
updated: 2026-10-22
---

!!! abstract "要点"
    - **何ができるか**：$N \le 10^{10}$ 程度で、$\varphi$・$\mu$ などの乗法的関数の和 $\sum_{n \le N} f(n)$ や $N$ 以下の素数の個数を、商 $\lfloor N/k \rfloor$ の値だけについて表を持つ方法で、篩より速く求める。関数どうしの関係はディリクレ積で表す。
    - **いつ使うか**：
        - $N \le 10^{10}$〜$10^{11}$ で $\sum_{n \le N} f(n)$（$f$ は $\varphi$・約数の個数など）を求める。
        - $N$ 以下の素数の個数・素数の和を求める。
    - **計算量**：素数の個数・素数の和は Lucy DP で $O(N^{3/4}/\log N)$。$\varphi$・$\mu$ の和は杜教篩で $O(N^{2/3})$（$N^{2/3}$ までの表を前計算）。一般の乗法的関数の和は Min_25 篩で $O(N^{3/4}/\log N)$ 程度（再帰の実装は $\Theta(N^{1-\varepsilon})$ だが $N \le 10^{11}$ では十分速い）。
    - **前提**：[オイラーの φ 関数](../math/euler-phi.md)、[商の列挙](../math/floor-quotient-enum.md)

<!-- textlint-disable -->
別名：ディリクレ積・Dirichlet convolution・杜教筛・Min_25・乗法的関数の prefix sum・素数計数・prime counting・Lucy DP・Meissel-Lehmer
<!-- textlint-enable -->

乗法的関数の和の手法は、$N$ が $10^{10}$ を超えて[エラトステネスの篩](../math/sieve-eratosthenes.md)の表が置けないときに、$\sum_{n \le N} f(n)$ を求める方法の総称である。どの方法も、$\lfloor N/k \rfloor$ の形の値（[商の列挙](../math/floor-quotient-enum.md)で $O(\sqrt{N})$ 種類）についてだけ和の表を持ち、表どうしの漸化式で答えを出す。ABC で必須になる出題は少なく（台帳で確かめた例題はまだない）、Library Checker の問題が自作の確かめに使える。

次の形を見たら、このページの手法を疑う。

- **$N$ が $10^{10}$ 以上の和**：篩は $O(N)$ のメモリが要るので $10^8$ 程度が限界である。$\sum \varphi(n)$・$\sum \mu(n)$・$\sum d(n)$・素数の個数を $N = 10^{10}$ で聞かれたら、篩では間に合わない。
- **$\sum_{n \le N} \varphi(n)$ が式に出る**：$\gcd(i, j) = 1$ の組の個数（$1 \le i, j \le N$）は $2 \sum_{n \le N} \varphi(n) - 1$ になる。[メビウス関数](../comb/mobius-function.md)で書き換えた式に $\sum \mu$ が残るときも同じである。

このページで使う記法：$p$ は素数、$\sum_{d \mid n}$ は $n$ の正の約数 $d$ すべてについての和である。和 $F(x) = \sum_{n \le x} f(n)$ のように、関数の小文字に対して和を大文字で書く。ほかの記法は[記法と用語の約束](../start/notation.md)にそろえる。

## 乗法的関数（φ・μ・d・σ）とディリクレ積（φ * 1 = id など） {#dirichlet}

関数 $f$ が**乗法的**であるとは、$f(1) = 1$ で、[互いに素](../guide/glossary.md#coprime)な $a, b$ について $f(ab) = f(a) f(b)$ が成り立つことである。素因数分解 $n = p_1^{e_1} \cdots p_r^{e_r}$ から $f(n) = f(p_1^{e_1}) \cdots f(p_r^{e_r})$ となり、素数べきでの値だけで $f$ が決まる。互いに素でなくても $f(ab) = f(a)f(b)$ が成り立つものを完全乗法的という（$n^k$ など）。

よく使う乗法的関数と、素数べきでの値は次のとおりである。

- $\varphi(p^e) = p^e - p^{e-1}$（[オイラーの φ 関数](../math/euler-phi.md)）。
- $\mu(p) = -1$、$e \ge 2$ なら $\mu(p^e) = 0$（[メビウス関数](../comb/mobius-function.md#definition)）。
- 約数の個数 $d(p^e) = e + 1$、約数の和 $\sigma(p^e) = 1 + p + \dots + p^e$。
- 完全乗法的なもの：定数 $1(n) = 1$、恒等写像 $\mathrm{id}(n) = n$、単位 $\varepsilon(n) = [n = 1]$。

2 つの関数の**ディリクレ積**を $(f * g)(n) = \sum_{d \mid n} f(d) \, g(n/d)$ と決める。和の順を入れ替えても同じなので $f * g = g * f$ で、$\varepsilon$ を掛けても変わらない。乗法的な関数どうしのディリクレ積は、また乗法的になる。上の関数は次の関係で結ばれる。

$$
1 * 1 = d, \qquad \mathrm{id} * 1 = \sigma, \qquad \varphi * 1 = \mathrm{id}, \qquad \mu * 1 = \varepsilon, \qquad \mu * \mathrm{id} = \varphi
$$

$\varphi * 1 = \mathrm{id}$ は「$n$ の約数 $d$ について $\varphi(d)$ を足すと $n$」の言い換えで（[約数についての φ の和](../math/euler-phi.md#divisor-sum)）、$\mu * 1 = \varepsilon$ は「$\mu$ を約数について足すと $n = 1$ のときだけ 1」の言い換えである。「$1$ を掛ける」は約数についての和（[約数のゼータ変換](../comb/zeta-mobius-divisor.md)）で、「$\mu$ を掛ける」はそれを戻す操作（メビウス反転）になる。

和を求めるときに効くのは、ディリクレ積の和が商の値だけで書けることである。$h = f * g$ なら、$n = ij$ と分けて

$$
H(N) = \sum_{ij \le N} f(i) \, g(j) = \sum_{i \le N} f(i) \, G(\lfloor N/i \rfloor)
$$

となる。$\lfloor \lfloor N/a \rfloor / b \rfloor = \lfloor N/(ab) \rfloor$ なので、再帰の先でも引数は $N$ の商の値から出ない。以下の方法はどれもこの形を使う。

$N$ が $10^7$ 程度までなら、ここまでの話は篩で足りる。$\varphi$・$\mu$ の表は[線形篩](../math/spf-sieve.md#linear-sieve)で $O(N)$、2 つの表のディリクレ積は倍数を列挙して $O(N \log N)$（[調和級数](../math/harmonic-sum.md)）で作れる。

## 素数の個数・素数の和（Lucy DP） {#prime-counting}

Lucy DP は、$N$ 以下の素数の個数 $\pi(N)$ を $O(N^{3/4}/\log N)$ 時間・$O(\sqrt{N})$ メモリで求める。エラトステネスの篩を「個数だけ」で行い、個数を商の値 $x = \lfloor N/k \rfloor$ についてだけ持つ方法である。

$S(x, p)$ を「$2$ 以上 $x$ 以下の整数のうち、素数であるか、最小素因数が $p$ より大きいものの個数」とする。篩で $p$ 以下の素数の倍数（素数自身は残す）を消し終えた後に残っている数の個数である。$S(x, 1) = x - 1$ から始め、素数 $p$ を小さい順に処理する。

- $p^2 > x$ なら、新しく消える数はないので $S(x, p) = S(x, p - 1)$ である。
- $p^2 \le x$ なら、新しく消えるのは最小素因数がちょうど $p$ の合成数 $pm$（$p \le m \le x/p$、$m$ は $p$ 未満の素因数を持たない）である。その個数は $S(\lfloor x/p \rfloor, p - 1)$ から $p$ 未満の素数の個数 $S(p - 1, p - 1)$ を引いたものなので、次の式になる。

$$
S(x, p) = S(x, p - 1) - \bigl( S(\lfloor x/p \rfloor, p - 1) - S(p - 1, p - 1) \bigr)
$$

$\sqrt{N}$ 以下の素数まで処理すると $S(N, \cdot) = \pi(N)$ になる。右辺に出る $\lfloor x/p \rfloor$ も $p - 1$（$p \le \sqrt{N}$ なので $\lfloor N/k \rfloor$ の形で書ける）も商の値なので、表は $O(\sqrt{N})$ 個で閉じる。

$N = 10$ で動かす。商の値は $1, 2, 3, 5, 10$ で、初めの $S$ はそれぞれ $0, 1, 2, 4, 9$ である。$p = 2$ では $p^2 \le x$ の $x = 10, 5$ を更新し、$S(10) = 9 - (S(5) - S(1)) = 9 - 4 = 5$、$S(5) = 4 - (S(2) - S(1)) = 3$ になる。$p = 3$ では $x = 10$ だけを更新し、$S(10) = 5 - (S(3) - S(2)) = 5 - 1 = 4$ になる。$\pi(10) = 4$（2・3・5・7）と一致する。

完全なプログラムは [`snippets/multiplicative-function/lucy.cpp`](https://github.com/yuukougun/kyopro-atlas/blob/main/snippets/multiplicative-function/lucy.cpp) である。$x \le \sqrt{N}$ の値を `lo[x]`、$x = \lfloor N/k \rfloor$ の値を `hi[k]` に持つ。

```cpp
--8<-- "multiplicative-function/lucy.cpp:core"
```

完全なプログラム：[`lucy.cpp`](https://github.com/yuukougun/kyopro-atlas/blob/main/snippets/multiplicative-function/lucy.cpp)（GitHub）
{ .kp-code-src }

自作するときの要点は[ライブラリの節](#library)にまとめる。計算量は、各 $x$ について $p \le \sqrt{x}$ の素数の個数だけ更新するので、$x$ について $\sqrt{x}/\log x$ を足して $O(N^{3/4}/\log N)$ になる。手元では $N = 10^{10}$ と $10^{11}$ を合わせて 0.3 秒以内で終わった。$O(N^{2/3})$ 程度のさらに速い方法もあるが、Library Checker の Counting Primes（$N \le 10^{11}$）は Lucy DP で足りる。

## 和の求め方の概要（杜教篩・Lucy DP・Min_25 篩） {#prefix-sums}

一般の乗法的関数の和は、関数の形によって方法を選ぶ。

### 杜教篩（ディリクレ積で割る）

杜教篩は、$f * g = h$ となる $g$ と $h$ の和が速く求まるとき、$F(N)$ を求める方法である。$H(N) = \sum_{i \le N} g(i) F(\lfloor N/i \rfloor)$ の $i = 1$ の項を移すと、次の漸化式になる。

$$
g(1) F(N) = H(N) - \sum_{i=2}^{N} g(i) \, F(\lfloor N/i \rfloor)
$$

右辺の和は $\lfloor N/i \rfloor$ が同じ値の区間をまとめて（[同じ商の区間の右端](../math/floor-quotient-enum.md#block-end)）$O(\sqrt{N})$ 項にできる。

- $\varphi$ の和：$g = 1$、$h = \mathrm{id}$ として $\Phi(N) = N(N + 1)/2 - \sum_{i=2}^{N} \Phi(\lfloor N/i \rfloor)$。
- $\mu$ の和（メルテンス関数 $M(N)$）：$g = 1$、$h = \varepsilon$ として $M(N) = 1 - \sum_{i=2}^{N} M(\lfloor N/i \rfloor)$。

$N^{2/3}$ 以下の値を篩の累積和で前計算し、それより大きい商の値だけを[メモ化再帰](../dp/memoized-recursion.md)で求めると $O(N^{2/3})$ になる。前計算なしで $\sqrt{N}$ までの表だけなら $O(N^{3/4})$ である。$\varphi$ の和のプログラムは [`snippets/multiplicative-function/phi-sum.cpp`](https://github.com/yuukougun/kyopro-atlas/blob/main/snippets/multiplicative-function/phi-sum.cpp) である。

```cpp
--8<-- "multiplicative-function/phi-sum.cpp:core"
```

完全なプログラム：[`phi-sum.cpp`](https://github.com/yuukougun/kyopro-atlas/blob/main/snippets/multiplicative-function/phi-sum.cpp)（GitHub）
{ .kp-code-src }

自作するときの要点は[ライブラリの節](#library)にまとめる。

### Min_25 篩（素数での値が多項式の関数）

Min_25 篩は、$f(p)$ が $p$ の多項式（$\sum_k c_k p^k$）で、$f(p^e)$ がすぐ計算できる乗法的関数の和を求める。2 段で考える。

- **素数の和**：$f(p) = \sum_k c_k p^k$ の各項について、素数 $p \le x$ にわたる $p^k$ の和を Lucy DP（[素数の個数・素数の和](#prime-counting)）ですべての商の値 $x$ について求める。これで「素数だけの和」が商の値ごとにそろう。
- **合成数を足す**：最小素因数とその指数で場合分けし、「最小素因数が $p$ より大きい数の和」を、小さい素因数から再帰で組み立てる。$N$ 以下の合成数は $\sqrt{N}$ 以下の素因数を必ず持つので、再帰の枝は少ない。

計算量は $O(N^{3/4}/\log N)$ とされることが多いが、実装しやすい再帰の形では $\Theta(N^{1-\varepsilon})$ と解析されている。Library Checker の Sum of Multiplicative Function（$f(p^e) = ae + bp$）がこの形の確かめになる。

## 公開ライブラリと自作するときの要点 {#library}

ACL には対応するものがない。ライブラリを持つなら、Nyaan 氏のライブラリの `prime_counting(N)`（Lucy DP）、`sum_of_totient<T>(N)`、乗法的関数の和の `mf_prefix_sum`（$f(p^e)$ を返す関数をテンプレート引数に渡し、`pi_table()`・`prime_sum_table()` から作った素数での和の表を `run` に渡す）が読みやすい。

**Lucy DP を自作するときの要点**は次のとおりである。

- **大きい $x$ から更新する**：式の右辺は $p - 1$ の段の値なので、1 本の表で書き換えるなら $x$ の大きい方から回す。`hi`（大きい $x$）を先に、`lo` を後に、`lo` は $x$ の大きい方から更新する。
- **$p$ が素数かの判定**：$p \le \sqrt{N}$ では `lo[p] != lo[p - 1]` なら $p$ は素数である（$p$ が残っている）。別に篩を作らなくてよい。
- **$\sqrt{N}$ を整数で求める**：`sqrt` の浮動小数点の誤差で $v = \lfloor \sqrt{N} \rfloor$ が 1 ずれると、`lo` と `hi` の境目が崩れる。$v^2 \le N < (v + 1)^2$ になるまで直す。
- **素数の和**：初めの値を $\sum_{n=2}^{x} n = x(x + 1)/2 - 1$ にし、引く量に $p$ を掛ける（$p \cdot (S(\lfloor x/p \rfloor) - S(p - 1))$）。消える数 $pm$ の和は $p$ と $m$ の和の積になるからで、$n^k$ のような完全乗法的な重みなら同じように使える。初めの値 $x(x + 1)/2$ は $N = 10^{10}$ で約 $5 \times 10^{19}$ になり `long long` を超えるので、mod を取るか `__int128` にする（答えそのものは約 $2.2 \times 10^{18}$ で収まる）。

**杜教篩を自作するときの要点**は次のとおりである。

- **メモの添字**：$N^{2/3}$ より大きい商の値 $m$ は $k = \lfloor N/m \rfloor$ で一意に決まるので、`map` ではなく長さ $N^{1/3}$ 程度の配列に $k$ を添字にして持てる。
- **$N(N + 1)/2$ のオーバーフロー**：$N = 10^{10}$ で $N(N + 1)$ は $10^{20}$ になり `long long` を超える。先に mod を取ってから掛け、2 で割る代わりに 2 の逆元を掛ける。
- **前計算の大きさ**：$N = 10^{10}$ なら $N^{2/3} \approx 4.6 \times 10^6$ で、篩の表は数十 MB に収まる。

Min_25 篩は再帰の枝の扱いが込み入るので、公開ライブラリを使い、Library Checker の Sum of Multiplicative Function で確かめるのが確実である。自作したものは、[練習問題](#practice)の Library Checker の問題と、篩の表の累積和（$N \le 10^7$ 程度）の答えとを比べて確かめる。

## 使い分け {#comparison}

| 求めるもの | 方法 | 計算量 |
| --- | --- | --- |
| 素数の個数・素数の和 | Lucy DP | $O(N^{3/4}/\log N)$ |
| $\varphi$・$\mu$ など、簡単な $g$・$h$ で $f * g = h$ と書ける関数の和 | 杜教篩 | $O(N^{2/3})$ |
| $f(p)$ が $p$ の多項式の乗法的関数の和 | Min_25 篩 | $O(N^{3/4}/\log N)$ 程度（再帰の実装は $\Theta(N^{1-\varepsilon})$。[概要](#prefix-sums)を参照） |
| $N \le 10^7$ 程度の和 | [線形篩](../math/spf-sieve.md#linear-sieve)の表の累積和 | $O(N)$ |

$\sum \varphi$ や $\sum \mu$ は杜教篩でも Min_25 篩でも求まる。杜教篩は関数ごとに $g$・$h$ を探す必要があるが、コードが短い。

## 学ぶための資料 {#resources}

- maspy 氏の記事[「Dirichlet 積と、数論関数の累積和」](https://maspypy.com/dirichlet-%E7%A9%8D%E3%81%A8%E3%80%81%E6%95%B0%E8%AB%96%E9%96%A2%E6%95%B0%E3%81%AE%E7%B4%AF%E7%A9%8D%E5%92%8C)：ディリクレ積の和を商の値ごとに求める考え方から、$\varphi$ の和やメルテンス関数を $O(N^{2/3})$ で求めるまでを、計算量の見積もりとともに追える。

## 練習問題 {#practice}

ABC で必須になる問題は確認できなかった。

### Library Checker

- [Counting Primes](https://judge.yosupo.jp/problem/counting_primes)：$N$ 以下の素数の個数を求める（$N \le 10^{11}$）。Lucy DP の確かめに使う。
- [Sum of Totient Function](https://judge.yosupo.jp/problem/sum_of_totient_function)：$\sum_{i \le N} \varphi(i) \bmod 998244353$ を求める（$N \le 10^{10}$）。杜教篩の確かめに使う。
- [Sum of Multiplicative Function](https://judge.yosupo.jp/problem/sum_of_multiplicative_function)：$f(p^e) = ae + bp$ の乗法的関数の和を $469762049$ で割った余りを、$T$ 個のテストケースについて求める（$T = 1$ なら $N \le 10^{11}$）。Min_25 篩の確かめに使う。
- [Counting Squarefrees](https://judge.yosupo.jp/problem/counting_squarefrees)：$N$ 以下の [squarefree](../guide/glossary.md#squarefree) な数の個数を求める（$N \le 10^{18}$）。個数は $\sum_{d \le \sqrt{N}} \mu(d) \lfloor N/d^2 \rfloor$ と書け、$\mu$ の和を商の値で求める練習になる。

## 確認問題 {#quiz}

??? question "確認問題：Lucy DP で、p = 3 の段の更新を x の小さい方から行うとどうなるか"
    $S(x, 3)$ の式の右辺は $S(\lfloor x/3 \rfloor, 2)$ で、$p = 2$ の段の値を読む必要がある。小さい $x$ から書き換えると、$\lfloor x/3 \rfloor$ がすでに $p = 3$ の段の値になっていて、消すべき数を引き残す。たとえば $N = 27$ で $S(9)$ を先に 3 の段へ更新すると（5 から 4 になる）、$S(27)$ の更新はその 4 を読む。引く量が 1 少なくなり、合成数の 27 が消されずに残る。1 本の表で書き換えるなら $x$ の大きい方から回す。

??? question "確認問題：φ の和を杜教篩で求めるとき、g = 1、h = id を選ぶ理由は何か"
    杜教篩では $G$ と $H$ の和が速く求まる必要がある。$G(x) = x$、$H(x) = x(x + 1)/2$ はどちらも式 1 本で求まり、$\varphi * 1 = \mathrm{id}$ が成り立つ。$g$ に $\mu$ を選ぶと、$G$ がメルテンス関数になって、それ自体を求める手間がかかる。

## 参考 {#references}

- [maspy「Dirichlet 積と、数論関数の累積和」](https://maspypy.com/dirichlet-%E7%A9%8D%E3%81%A8%E3%80%81%E6%95%B0%E8%AB%96%E9%96%A2%E6%95%B0%E3%81%AE%E7%B4%AF%E7%A9%8D%E5%92%8C)：ディリクレ積の和を商の値で求める方法と計算量、$\varphi$ の和とメルテンス関数を $O(N^{2/3})$ で求めること
- [Nyaan「素数カウント(O(N^{3/4}/log N))」](https://nyaannyaan.github.io/library/multiplicative-function/prime-counting.hpp)：Lucy DP の計算量と `prime_counting` の使い方
- [Nyaan「乗法的関数のprefix sum」](https://nyaannyaan.github.io/library/multiplicative-function/sum-of-multiplicative-function.hpp)：Min_25 篩の要件（素数での値が多項式）と計算量の注記、`mf_prefix_sum` の使い方
- [Nyaan「素数カウント(O(N^{2/3}))」](https://nyaannyaan.github.io/library/multiplicative-function/prime-counting-o2d3.hpp)：素数の個数を $O(N^{2/3})$ で求める方法があること
- [Nyaan「トーシェント関数の和」](https://nyaannyaan.github.io/library/multiplicative-function/sum-of-totient.hpp)：`sum_of_totient` の使い方
- [OI Wiki「Min_25 筛」](https://oi-wiki.org/math/number-theory/min-25/)：Min_25 篩の 2 段の構成と計算量（$O(N^{3/4}/\log N)$ と $\Theta(N^{1-\varepsilon})$）の事実だけを参照
- [Wikipedia「Dirichlet convolution」](https://en.wikipedia.org/wiki/Dirichlet_convolution)：乗法的関数どうしのディリクレ積が乗法的になることと、$1 * 1 = d$・$\varphi * 1 = \mathrm{id}$ などの関係
- [Wikipedia「Prime-counting function」](https://en.wikipedia.org/wiki/Prime-counting_function)：$\pi(10^{10})$・$\pi(10^{11})$ の値（コード片の期待値）
- [yosupo「Library Checker の問題（number_theory）」](https://github.com/yosupo06/library-checker-problems/tree/master/number_theory)：練習の問題の問いと制約（counting_primes・sum_of_totient_function・sum_of_multiplicative_function・counting_squarefrees の task.md・info.toml）
