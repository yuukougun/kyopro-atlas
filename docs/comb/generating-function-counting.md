---
id: generating-function-counting
title: 母関数の考え方
aliases: [母関数, 生成関数, 数え上げの多項式表現, 形式的冪級数で数える, generating function]
type: overview
field: comb
chapter: 二項係数の系統
order: 170
level: 発展
kind: [数え上げ, 畳み込み・多項式]
prerequisites: [stars-and-bars, binomial-identities]
related: [fps-basics, convolution-ntt, cayley-pruefer, stirling-first, knapsack-undo]
summary: 選び方の数を多項式の係数で表し、積で独立な選択の組合せ、累乗で同じ選択の繰り返しを表す。DP の遷移も多項式の積・商として立式でき、多項式の演算そのものは FPS に任せる。
complexity: 上限つきの係数 1 つは前計算 O(N + K) の後 O(K/(c+1))。K 次までの多項式の累乗は繰り返し二乗法と畳み込みで O(K log K log N)、FPS の pow で O(K log K)
signs:
  - {type: phrase, text: 各要素の選び方が独立で、個数（和）の合計に条件がある}
  - {type: shape, text: 答えが (1 + x + … + x^c)^N のような式の特定の係数になる}
  - {type: shape, text: '遷移が dp''[s] = dp[s] + dp[s − v] のように、値をずらして足す形になる'}
acl: [convolution]
frequency: B
frequency_evidence: recent 0・前提として届くページなし・古い ABC 4 問
sections:
  - {title: 係数 = 数え方（積は独立な選択、累乗は繰り返し）, anchor: coefficients}
  - {title: 重複組合せ・上限つきの選び方を式で書く, anchor: formulas}
  - {title: DP の遷移を多項式の積・商として見る, anchor: dp-as-polynomial}
  - {title: 多項式の演算（逆元・log・exp）は FPS のページへ, anchor: to-fps}
  - {title: 例題：Prüfer 列と累乗、上限つきの桁の和, anchor: examples}
stage: draft
updated: 2026-10-22
---

!!! abstract "要点"
    - **何ができるか**：選び方の数を多項式の係数で表し、積で独立な選択の組合せ、累乗で同じ選択の繰り返しを表す。DP の遷移も多項式の積・商として立式できる。多項式の演算そのものは FPS に任せる。
    - **いつ使うか**：
        - 各要素の選び方が独立で、個数（和）の合計に条件がある
        - 答えが $(1 + x + \dots + x^c)^N$ のような式の特定の係数になる
        - 遷移が $\mathrm{dp}'[s] = \mathrm{dp}[s] + \mathrm{dp}[s - v]$ のように、値をずらして足す形になる
    - **計算量**：上限つきの係数 1 つは、階乗の前計算 $O(N + K)$ の後 $O(K / (c + 1))$。$K$ 次までの多項式の累乗は、繰り返し二乗法と畳み込みで $O(K \log K \log N)$、FPS の累乗で $O(K \log K)$
    - **前提**：[重複組合せ](../comb/stars-and-bars.md)、[二項係数の恒等式と和の公式](../comb/binomial-identities.md)

<!-- textlint-disable -->
別名：母関数・生成関数・数え上げの多項式表現・形式的冪級数で数える・generating function
<!-- textlint-enable -->

母関数の考え方は、「和が $n$ になる選び方の数」を多項式の $x^n$ の係数に置き、選び方の組合せを多項式の掛け算に言い換える見方である。言い換えると、重複組合せや包除原理の式が多項式の式変形から出てくる。DP の更新が多項式の掛け算・割り算に見えるので、速い多項式の演算（[畳み込み](../math/convolution-ntt.md)や[形式的冪級数](../math/fps-basics.md)）にもつながる。

ABC で母関数がそのまま要るのは、主に後半の G・Ex である（このページの例題は difficulty 2501 と 2631）。ただし、立式の考え方は青の帯の数え上げでも式を確かめる道具になる。

## 係数 = 数え方（積は独立な選択、累乗は繰り返し） {#coefficients}

数列 $a_0, a_1, a_2, \dots$ を係数に並べた $A(x) = a_0 + a_1 x + a_2 x^2 + \cdots$ を、数列 $a$ の**母関数**と呼ぶ。$x$ に値を代入することはなく、係数を並べておく入れ物として使う。$A(x)$ の $x^n$ の係数を $[x^n] A(x)$ と書く。

数え上げでは「重さ（和・個数）が $n$ の選び方の数」を $a_n$ にする。小さい例で確かめる。1 円玉を 0〜2 枚、2 円玉を 0〜1 枚選ぶとする。1 円玉の選び方の母関数は $1 + x + x^2$（$x^k$ が金額 $k$ の選び方 1 通りを表す）で、2 円玉のほうは $1 + x^2$ である。掛けると次のようになる。

$$
(1 + x + x^2)(1 + x^2) = 1 + x + 2x^2 + x^3 + x^4
$$

金額 2 の係数が 2 なのは、「1 円玉 2 枚」と「2 円玉 1 枚」の 2 通りがあるからである。展開すると、左の因子の $x^i$ と右の因子の $x^j$ の組それぞれについて、積 $x^{i+j}$ がちょうど 1 回現れる。だから $x^n$ の係数は「$i + j = n$ となる選び方の組の数」になり、重複も漏れもない。これが積の意味である。

- **積は独立な選択の組合せ**：$A(x) B(x)$ の係数 $c_n = \sum_{i + j = n} a_i b_j$ は、重さ $i$ の選び方と重さ $j$ の選び方を組にした数である。この式は[畳み込み](../math/convolution-ntt.md)そのものである。
- **累乗は同じ選択の繰り返し**：$N$ 個の箱が同じ選び方を持つなら、母関数は $A(x)^N$ になる。箱は区別される（どの箱から何を選んだかで区別する）。
- **和は場合分け**：重ならない 2 つの場合の数を足すときは、母関数を足す。

順番に並べる・ラベルを付けるなど、区別のある対象を合わせる数え上げでは、$\sum_k \frac{a_k}{k!} x^k$ の形（指数型母関数）を使うと、積の係数に二項係数が自動で掛かる。[多項係数](../comb/multinomial-coefficient.md#dp-merge)で並べ方を数える DP や、[Prüfer 列の数え上げ](../comb/cayley-pruefer.md#with-polynomials)がこの形である。

## 重複組合せ・上限つきの選び方を式で書く {#formulas}

この節は[重複組合せ](../comb/stars-and-bars.md#stars-bars)と[二項定理](../comb/binomial-identities.md#binomial-theorem)を使う。1 つの変数の選び方を母関数にし、閉じた式に直すと、係数が二項係数で求まる。

| 1 変数の選び方 | 母関数 |
| --- | --- |
| 0 以上いくつでも | $1 + x + x^2 + \cdots = \dfrac{1}{1 - x}$ |
| 1 以上 | $\dfrac{x}{1 - x}$ |
| 0 以上 $c$ 以下 | $1 + x + \cdots + x^c = \dfrac{1 - x^{c+1}}{1 - x}$ |
| 偶数だけ | $\dfrac{1}{1 - x^2}$ |

$\frac{1}{1 - x}$ は「$1 - x$ と掛けると 1 になる冪級数」の意味で、$(1 - x)(1 + x + x^2 + \cdots) = 1$ を展開して確かめられる。

**重複組合せ**。$x_1 + \dots + x_N = K$ の非負整数解の個数は $[x^K] \frac{1}{(1 - x)^N}$ である。玉と仕切りの数え方から、この係数は $\binom{K + N - 1}{N - 1}$ になる。

$$
\frac{1}{(1 - x)^N} = \sum_{K \ge 0} \binom{K + N - 1}{N - 1} x^K
$$

**上限つき**。各 $x_i$ が 0 以上 $c$ 以下なら、答えは $[x^K] \left(\frac{1 - x^{c+1}}{1 - x}\right)^N$ である。分子を二項定理で展開すると $x^{j(c+1)}$ の項だけが残るので、分母の係数と組み合わせて次の和になる。

$$
[x^K] \frac{(1 - x^{c+1})^N}{(1 - x)^N} = \sum_{j \ge 0} (-1)^j \binom{N}{j} \binom{K - j(c+1) + N - 1}{N - 1}
$$

これは「$j$ 個の変数で上限を破る」場合を引いたり足したりする[包除原理](../comb/inclusion-exclusion.md#symmetric)の式と同じである。項は $j(c+1) \le K$ の範囲だけなので、階乗と逆階乗の表があれば $O(K / (c + 1))$ 回の計算で済む。

$N = 3$、$c = 2$、$K = 3$ で確かめる。各変数が 0〜2 で和が 3 の組は、$(1, 1, 1)$ と $(0, 1, 2)$ の並べ替え 6 通りで 7 個である。式は $j = 0$ で $\binom{5}{2} = 10$、$j = 1$ で $-3 \binom{2}{2} = -3$ になり、合わせて 7 になる。

次のコード片は、同じ係数を「多項式の累乗を $K$ 次まで計算する方法」と「閉じた式」の 2 通りで求め、一致を確かめている（完全なプログラムは `snippets/generating-function-counting/bounded.cpp`）。閉じた式の方では、$N = 0$ を先に分けている。式のままでは $\binom{K - 1}{-1}$ になり、範囲外を 0 とする約束では空の積の 1 を落とすからである。

```cpp
--8<-- "generating-function-counting/bounded.cpp:closed"
```

閉じた式に直せないとき（変数ごとに許される値がばらばらなど）は、多項式を $K$ 次までに切り詰めて掛ける。同じ多項式の $N$ 乗なら、繰り返し二乗法で掛け算は $O(\log N)$ 回で済む。

```cpp
--8<-- "generating-function-counting/bounded.cpp:power"
```

## DP の遷移を多項式の積・商として見る {#dp-as-polynomial}

数え上げの DP の表 $\mathrm{dp}[0], \mathrm{dp}[1], \dots$ を、多項式 $P(x) = \sum_s \mathrm{dp}[s] x^s$ の係数とみる。すると、よく使う更新は多項式の掛け算・割り算になる。

| DP の更新 | 多項式の操作 | 1 本の配列で回す向き |
| --- | --- | --- |
| 値 $v$ を使う・使わない：$\mathrm{dp}'[s] = \mathrm{dp}[s] + \mathrm{dp}[s - v]$ | $(1 + x^v)$ を掛ける | $s$ の大きい方から |
| 値 $v$ をいくつでも：$\mathrm{dp}'[s] = \mathrm{dp}[s] + \mathrm{dp}'[s - v]$ | $\frac{1}{1 - x^v}$ を掛ける | $s$ の小さい方から |
| 値 $v$ を取り除く（使う・使わないの逆） | $(1 + x^v)$ で割る | $s$ の小さい方から |

2 行目は、$Q = \frac{P}{1 - x^v}$ を $Q = P + x^v Q$ と書き直すと、係数の式 $q_s = p_s + q_{s-v}$ になることから出る。割り算が係数の漸化式になるのは、割る多項式の定数項が 0 でない（mod $p$ なら逆元がある）からである。定数項が 1 の多項式で割る操作は、$K$ 次までに限っても一通りに決まる。取り除く操作の詳しい手順と、戻せない DP（max・min）との違いは[戻す DP](../dp/knapsack-undo.md#undo-by-subtraction)にある。

多項式とみると、更新の順番を入れ替えてよい理由もすぐ分かる。掛け算は順序によらないので、要素をどの順に入れても表は同じになる。

**挿入 DP と[上昇階乗](../guide/glossary.md#rising-factorial)**。値を 1 つずつ入れる DP で、$n$ 番目の段の遷移が「状態を 1 増やす重み 1」と「状態を変えない重み $n - 1$」なら、全体は $x (x + 1) (x + 2) \cdots (x + N - 1)$ の展開になる。順列なら、大きい値から順に入れ、状態を左から見える位置（それより左に大きい値がない位置）の個数とする。$n$ 番目に入れる値は $n$ か所に置け、左端の 1 か所に置いたときだけ見える個数が 1 増える。だからこの上昇階乗の係数は、左から見える位置の個数ごとの順列の数を表し、[第 1 種スターリング数](../comb/stirling-first.md)（の絶対値）になる。

**多くの因子の積**。$\prod_{i} (1 + x^{v_i})$ のように因子がばらばらなら、1 つずつ掛ける DP は $O(NK)$ である。次数の小さいものどうしから 2 つずつ掛ける分割統治にすると、畳み込みで $O(K \log^2 K)$ ほどになる（次数の合計が $O(K)$ のとき）。因子がすべて $1 + x^{v}$ の形なら、log を取って足し、exp で戻す方法もある（[FPS へ](#to-fps)）。

応用の型：遷移が「値をずらして足す」だけの DP は、多項式の積で書けるかを考える。書ければ、閉じた式に直すか、累乗・分割統治の掛け算で速くできる。

## 多項式の演算（逆元・log・exp）は FPS のページへ {#to-fps}

母関数で立式した後は、多項式（冪級数）を $K$ 次まで計算する。この節は[畳み込み](../math/convolution-ntt.md)を前提にする。どの演算も $998244353$ のような NTT 向きの素数を法として計算する。中身は[形式的冪級数（FPS）](../math/fps-basics.md)のページに任せ、ここでは何に使うかと計算量だけを並べる。

| 演算 | 何に使うか | 計算量 |
| --- | --- | --- |
| 積 $f g$ | 独立な選択の組合せ | $O(K \log K)$ |
| 逆元 $1 / f$ | 割り算（定数項が 0 でないとき） | $O(K \log K)$ |
| log・exp | 多くの因子の積を和に直す | $O(K \log K)$ |
| 累乗 $f^N$ | 同じ選択の $N$ 回の繰り返し | $O(K \log K)$（log と exp）、繰り返し二乗法なら $O(K \log K \log N)$ |
| 多くの因子の積 | ばらばらの選択の組合せ | 分割統治で $O(K \log^2 K)$ |

$K$ は求めたい係数の次数である。逆元・log・exp・累乗の $O(K \log K)$ は、ニュートン法で精度を倍々にする実装の計算量で、定数倍は積より重い。

!!! info "ACL では"
    `#include <atcoder/convolution>`。`atcoder::convolution(a, b)` は 2 つの列の畳み込みを $998244353$ で割った余りで返し、計算量は $n = \lvert a \rvert + \lvert b \rvert$ として $O(n \log n + \log \mathrm{mod})$（法を固定すれば $O(n \log n)$）である。`vector<modint998244353>` をそのまま渡せる。法の条件と長さの上限は[ACL の convolution の要件](../math/convolution-ntt.md#acl)にある。逆元・log・exp・累乗は ACL にないので、自作するか他のライブラリを使う。

自作するときの要点は次のとおりである。

- **切り詰め**：答えに要るのは $K$ 次までなので、掛けるたびに $K + 1$ 項に切る。切らないと長さが倍々に増えて遅くなる。
- **定数項**：$1/f$ と $\log f$ は定数項が 0 でないとき（log はふつう定数項 1 に正規化して）、$\exp f$ は定数項が 0 のときに定義する。累乗で定数項が 0 の $f$ は、$x^d$ をくくり出してから計算する。
- **素朴な方法を残す**：$O(K^2)$ の素朴な掛け算・割り算を残しておき、小さい入力で比べて確かめる。

自作したら、Library Checker で確かめる。

- Convolution：畳み込み（積）
- Inv of Formal Power Series・Log of Formal Power Series・Exp of Formal Power Series・Pow of Formal Power Series：逆元・log・exp・累乗
- Product of Polynomial Sequence：多くの多項式の積（分割統治）
- Sharp P Subset Sum：和が $t$ になる部分集合の数を $t = 1, \dots, T$ についてまとめて求める（$\prod_i (1 + x^{s_i})$ を log と exp で）
- Partition Function：分割数 $p(0), \dots, p(N)$（$\prod_{k \ge 1} (1 - x^k)$ は五角数定理で項がまばらになり、その逆元が分割数の母関数）
- Stirling Number of the First Kind：下降階乗 $x(x-1)\cdots(x-N+1)$ の係数（符号付き）。絶対値が上昇階乗の係数

## 学ぶための資料 {#resources}

- hotman78 氏の「形式的冪級数の応用テクニック（前編）」は、逆元・log・exp・累乗をニュートン法で求める流れと計算量をまとめている。和が $t$ になる部分集合の数を $\exp\left(\sum \log(1 + x^{e})\right)$ で求める例もある
- Nyaan's Library の「多項式/形式的冪級数ライブラリ」は、NTT 向きの法での演算をひとまとめにした実装で、自作するときの関数の切り分けの参考になる
- 立式の流れは、例題の ABC303 Ex の解説（けんちょん氏）が短く追いやすい。Prüfer 列で木を列に言い換えた後、母関数の累乗の係数に落とす

## 例題：Prüfer 列と累乗、上限つきの桁の和 {#examples}

### ABC303 Ex. Constrained Tree Degree {#abc303_h}

<div class="kp-problems" data-role="example" markdown>

- [ABC303 Ex. Constrained Tree Degree](https://atcoder.jp/contests/abc303/tasks/abc303_h)（diff 2501）：各頂点の次数が与えられた集合 S に含まれる、N 頂点のラベル付き木の数を求める。

</div>

方針：[Prüfer 列](../comb/cayley-pruefer.md#degree-sequence)で、次数 $d_v$ の頂点は長さ $N - 2$ の列にちょうど $d_v - 1$ 回現れる。次数列ごとの木の数は $\frac{(N-2)!}{\prod_v (d_v - 1)!}$ なので、頂点ごとに同じ母関数 $F(x) = \sum_{d \in S} \frac{x^{d-1}}{(d-1)!}$ を作れば、答えは $(N-2)! \, [x^{N-2}] F(x)^N$ になる。

??? note "解法の詳細"
    - 指数 $e_v = d_v - 1$ の合計は $N - 2$ である（次数の和が $2N - 2$ だから）。$F(x)^N$ の $x^{N-2}$ の係数は、合計が $N - 2$ になる $(e_v)$ すべての $\prod_v \frac{1}{e_v!}$ の和で、次数列ごとの木の数の和に $(N-2)!$ を掛ける前のものと一致する。
    - $F$ は $N - 2$ 次までに切り詰めてよい。FPS の累乗（log と exp）で $O(N \log N)$、繰り返し二乗法と畳み込みで $O(N \log^2 N)$ になる。
    - 頂点ごとに条件が違う場合や、閉じた式に落ちる場合の扱いは [Prüfer 列と多項式](../comb/cayley-pruefer.md#with-polynomials)にある。

### ABC449 G. Many Repunit Sum 2 {#abc449_g}

<div class="kp-problems" data-role="example" markdown>

- [ABC449 G. Many Repunit Sum 2](https://atcoder.jp/contests/abc449/tasks/abc449_g)（diff 2631）：1 桁から M 桁までのレピュニット（1 だけが並ぶ数）を重複を許して N 個選んで足すとき、和として現れる整数の種類数を求める。

</div>

方針：$d$ 桁のレピュニットは $\frac{10^d - 1}{9}$ なので、和の種類数は「$10$ の冪を $N$ 個足した値」の種類数と同じになる。同じ値を表す選び方のうち、$10^0, \dots, 10^{M-2}$ の個数がどれも 9 以下のものを代表とする。代表の個数の母関数は $(1 + x + \dots + x^9)^{M-1} \cdot \frac{1}{1 - x} = \frac{(1 - x^{10})^{M-1}}{(1 - x)^M}$ になる。必要な係数は分子と分母の二項係数から求まる。

??? note "解法の詳細"
    - 和は $\frac{1}{9}(\sum_i 10^{d_i} - N)$ と書けるので、$\sum_i 10^{d_i}$（$1 \le d_i \le M$）の種類数を数えればよい。全体を 10 で割って、指数を $0, \dots, M - 1$ にずらしても種類数は変わらない
    - $10^{i+1}$ を 1 個崩して $10^i$ を 10 個にすると、値を保ったまま個数が 9 増える。逆に $10^i$ が 10 個以上あれば 10 個を $10^{i+1}$ 1 個にまとめられる。まとめきった形（最も大きい $10^{M-1}$ を除いて各個数が 9 以下）が代表で、値ごとにただ 1 つに決まる。
    - 代表の個数を $T$ とする。個数をちょうど $N$ にできるのは、$T \le N$ かつ $T \equiv N \pmod 9$ で、値が $N$ 以上（すべて $10^0$ に崩せば個数は値と等しい）のときである。前の 2 つを満たす代表の数は、母関数の $x^N, x^{N-9}, x^{N-18}, \dots$ の係数の和である。値が $N$ 未満のもの（$N - 9, N - 18, \dots$ の $\lfloor N/9 \rfloor$ 個）を最後に引く。値と個数は 9 で割った余りが等しいので、これらは前の 2 つの条件を満たしている。
    - 分子 $(1 - x^{10})^{M-1}$ の $x^{10k}$ の係数は $(-1)^k \binom{M-1}{k}$、分母 $\frac{1}{(1-x)^M}$ の $x^j$ の係数は $\binom{M + j - 1}{j}$ である。$M$ が大きくても、どちらも隣の項との比で順に求められる。2 つの列を畳み込んで、要る係数を足す。どちらも $N$ 次まで求めればよい。畳み込みを含めて $O(N \log N)$ である（$M$ は二項係数の比の計算にだけ現れる）。

## 練習問題 {#practice}

<div class="kp-problems" data-role="practice" markdown>

- [ABC321 F. #(subset sum = K) with Add and Erase](https://atcoder.jp/contests/abc321/tasks/abc321_f)（diff 1645）：整数を箱に入れる・箱から取り出すクエリのたびに、箱の中から選んだ整数の和がちょうど K になる選び方の数を求める。
- [ABC385 G. Counting Buildings](https://atcoder.jp/contests/abc385/tasks/abc385_g)（diff 2492）：N 個の建物の高さの順列のうち、左から見える建物の数と右から見える建物の数の差がちょうど K になるものの数を求める。

</div>

??? note "練習の方針"
    - ABC321 F：表を多項式とみると、値 $v$ を入れる操作は $(1 + x^v)$ を掛けることで、取り出す操作はその割り算である。割り算は和の小さい方からの引き算になる（[戻す DP](../dp/knapsack-undo.md#undo-by-subtraction)）。母関数を知らなくても、追加の更新を逆にたどるだけで解ける。
    - ABC385 G：高い建物から順に入れる挿入 DP にする。$n$ 個並んだところへ次の建物を左端に入れると左から見える数が 1 増え、右端なら右から見える数が 1 増える。残りの $n - 1$ か所では変わらない。差の母関数は $\prod_{n=1}^{N-1} (x^{-1} + (n - 1) + x)$ になり、因子を分割統治で掛けると $O(N \log^2 N)$ になる。$y = x + x^{-1}$ とおくと上昇階乗 $y (y + 1) \cdots (y + N - 2)$ なので、[第 1 種スターリング数](../comb/stirling-first.md)と二項係数で展開する方法もある。

## 確認問題 {#quiz}

??? question "確認問題：各変数が 1 以上 c 以下のときの係数は、どう書けるか"
    1 変数の母関数は $x + \cdots + x^c = x \cdot \frac{1 - x^c}{1 - x}$ である。$N$ 乗すると $x^N \frac{(1 - x^c)^N}{(1 - x)^N}$ になる。答えは $[x^{K - N}] \frac{(1 - x^c)^N}{(1 - x)^N}$ で、[上限つきの式](#formulas)の $K$ を $K - N$、$c + 1$ を $c$ に置き換えればよい。各変数から 1 を引いて 0 以上 $c - 1$ 以下に直したのと同じである。

??? question "確認問題：値 v を何個でも使える更新を取り消したい。何を掛け、どちらの向きに回すか"
    個数制限なしの追加は $\frac{1}{1 - x^v}$ を掛ける操作なので、取り消しは $(1 - x^v)$ を掛ければよい。係数の式は $\mathrm{dp}[s] = \mathrm{dp}'[s] - \mathrm{dp}'[s - v]$ で、右辺は取り消す前の表だけを読む。1 本の配列で書くなら、まだ書き換えていない $\mathrm{dp}'[s - v]$ を読むために $s$ の大きい方から回す。

## 参考 {#references}

- [hotman78「【競技プログラミング】形式的冪級数の応用テクニック(前編)」](https://qiita.com/hotman78/items/f0e6d2265badd84d429a)：学ぶための資料。FPS の演算の計算量と、部分集合の和の数を log と exp で求める方法
- [Nyaan「多項式/形式的冪級数ライブラリ」](https://nyaannyaan.github.io/library/fps/formal-power-series.hpp)：学ぶための資料。自作するときの実装の参考
- [drken「AtCoder ABC 303 Ex - Constrained Tree Degree (橙色, 600 点)」](https://drken1215.hatenablog.com/entry/2023/05/28/010200)：例題 ABC303 Ex の立式と計算量
- [ikatakos「AtCoder Beginner Contest 449 E,F,G問題メモ」](https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2026/0314_abc449)：例題 ABC449 G の代表の取り方と母関数（解法の節だけを読んだ）
- [kmjp「AtCoder ABC #449 : G - Many Repunit Sum 2」](https://kmjp.hatenablog.jp/entry/2026/03/14/0900)：例題 ABC449 G の数え方の確認
- [kmjp「AtCoder ABC #385 (ユニークビジョンプログラミングコンテスト2024 クリスマス) : G - Counting Buildings」](https://kmjp.hatenablog.jp/entry/2024/12/21/0930)：練習 ABC385 G の挿入 DP と因子の積
- [drken「AtCoder ABC 321 F - #(subset sum = K) with Add and Erase (青色, 525 点)」](https://drken1215.hatenablog.com/entry/2023/09/25/070100)：練習 ABC321 F
- [AtCoder「AC Library のドキュメント（document_ja）」](https://github.com/atcoder/ac-library/tree/master/document_ja)：ACL の convolution の宣言と計算量
- [yosupo「Library Checker の問題（polynomial・enumerative_combinatorics ほか）」](https://github.com/yosupo06/library-checker-problems)：自作したときの確認に使う問題の内容
