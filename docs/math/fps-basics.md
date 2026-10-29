---
id: fps-basics
title: 形式的冪級数と多項式の演算
aliases: [FPS, formal power series, 多項式の逆元, 多項式の割り算, Taylor shift, 多点評価, 冪級数の log・exp, 形式的べき級数]
type: overview
field: math
chapter: 畳み込みと多項式
order: 400
level: 発展
kind: [畳み込み・多項式, 数え上げ]
prerequisites: [convolution-ntt, mod-inverse]
related: [generating-function-counting, knapsack-undo, online-convolution, lagrange-interpolation, cayley-pruefer, fft-ntt]
summary: 数列を冪級数とみて、逆元 1/f・log・exp・累乗を O(N log N) で計算し、多項式の割り算・Taylor shift・多点評価も行う。数え上げの式を多項式で立てた後の計算を受け持つ。
complexity: 逆元・log・exp・累乗・平方根は N 項まで O(N log N)（素朴な方法は O(N^2)）、多項式の割り算・Taylor shift は O(N log N)、多点評価・補間は O(N log^2 N)
signs:
  - {type: phrase, text: (1 + x^v) を掛ける・割るように、集合への追加と削除を繰り返して個数の分布を求める}
  - {type: phrase, text: 次数の条件つきの木や個数の分布を、多項式の累乗の係数として数える}
  - {type: shape, text: 答えが多項式 f の 1/f・log f・exp f・f^K の係数で書ける}
acl: [convolution]
verify: [inv_of_formal_power_series, log_of_formal_power_series, exp_of_formal_power_series, pow_of_formal_power_series, sqrt_of_formal_power_series, division_of_polynomials, polynomial_taylor_shift, multipoint_evaluation, polynomial_interpolation]
frequency: B
frequency_evidence: recent 1（abc473_g）・前提として 1 ページに届く（直接 1）・古い ABC 4 問
sections:
  - {title: 式の形から使う演算を選ぶ, anchor: signs}
  - {title: 演算の一覧と計算量（inv・log・exp・pow・sqrt）, anchor: operations}
  - {title: 多項式の割り算・Taylor shift・多点評価, anchor: polynomial-ops}
  - {title: ACL の convolution と自作するときの要点, anchor: library}
stage: reviewed
updated: 2026-10-29
---

!!! abstract "要点"
    - **何ができるか**：数列を冪級数とみて、逆元 $1/f$・$\log f$・$\exp f$・累乗 $f^M$ の先頭 $N$ 項を $O(N \log N)$ で計算し、多項式の割り算・Taylor shift・多点評価も行う。数え上げの式を多項式で立てた後の計算を受け持つ。
    - **いつ使うか**：
        - $(1 + x^v)$ を掛ける・割るように、集合への追加と削除を繰り返して個数の分布を求める
        - 次数の条件つきの木や個数の分布を、多項式の累乗の係数として数える
        - 答えが多項式 $f$ の $1/f$・$\log f$・$\exp f$・$f^K$ の係数で書ける
    - **計算量**：先頭 $N$ 項の逆元・log・exp・累乗・平方根はニュートン法で $O(N \log N)$（素朴に係数を下から決めると $O(N^2)$）。多項式の割り算・Taylor shift は $O(N \log N)$、多点評価・補間は $O(N \log^2 N)$
    - **前提**：[畳み込みの使い方](../math/convolution-ntt.md)、[逆元と mod での割り算](../math/mod-inverse.md)

<!-- textlint-disable -->
別名：FPS・formal power series・多項式の逆元・多項式の割り算・Taylor shift・多点評価・冪級数の log・exp・形式的べき級数
<!-- textlint-enable -->

形式的冪級数（FPS）は、数列 $a_0, a_1, a_2, \dots$ を $f(x) = a_0 + a_1 x + a_2 x^2 + \cdots$ という「無限に続く多項式」とみて、掛け算・割り算・log・exp などの演算をする道具である。答えに要るのは $x^{N-1}$ までの係数だけなので、どの演算も先頭 $N$ 項に切り詰めて計算する。法は $998244353$ のような NTT 向きの素数にし、掛け算は[畳み込み](../math/convolution-ntt.md)で行う。

ABC では主に difficulty 2200 以上の G・Ex で現れる。式の立て方は[母関数の考え方](../comb/generating-function-counting.md)に任せ、ここでは立てた式をどの演算で計算するか、計算量、自作するときの要点をまとめる。証明と実装の細部は[学ぶための資料](#resources)に任せる。

このページで使う記法：$[x^n] f$ は $f$ の $x^n$ の係数、$f \bmod x^N$ は $x^N$ 以上の項を捨てたもの（先頭 $N$ 項）である。ほかの記法は[記法と用語の約束](../start/notation.md)にそろえる。

## 式の形から使う演算を選ぶ {#signs}

[母関数](../guide/glossary.md#generating-function)で式を立てたら、その形から演算を選ぶ。$N$ は要る係数の個数である。

- **分母がある**（$\frac{g}{f}$、$\frac{1}{(1 - x)^k}$ など）：逆元 $1/f$ を求めて掛ける。分母が $1 - x^v$ のような項の少ない式なら、逆元を作らずに係数を下から足していけば $O(N)$ で済む。
- **同じ因子の累乗**（$F(x)^M$）：累乗 $f^M$。次数の条件つきのラベル付き木の数は $F(x)^N$ の係数になる（[Prüfer 列と多項式](../comb/cayley-pruefer.md#with-polynomials)）。
- **多数の因子の積**（$\prod_i (1 + x^{a_i})$、$\prod_i \frac{1}{1 - x^{a_i}}$）：log をとって和にし、最後に exp で戻す。$\log(1 + x^a) = x^a - \frac{x^{2a}}{2} + \frac{x^{3a}}{3} - \cdots$ は $N/a$ 項しかないので、同じ $a$ をまとめると項の数の合計は調和級数で $O(N \log N)$ になる。因子の次数がばらばらなら、次数の小さいものから掛ける[分割統治の積](../math/online-convolution.md#product-of-many)でもよい（$O(N \log^2 N)$）。
- **ラベル付きの部品の集まり**（順列を巡回に分ける、森を木に分ける）：部品 1 つの指数型母関数（$\sum_n c_n \frac{x^n}{n!}$ の形）を $C(x)$ とすると、部品の集まりは $\exp C(x)$ になる。[例題の ABC318 Ex](#abc318_h)がこの形である。
- **1 つずつの追加・削除**（$(1 + x^v)$ を掛ける・割る）：1 回の掛け算・割り算は係数の足し引きで $O(N)$ なので、FPS の演算は要らない。割り算は和の小さい方から引く（[戻す DP](../dp/knapsack-undo.md#undo-by-subtraction)）。
- **多項式の値をたくさんの点で求める・点から係数を戻す**：[多点評価・補間](#polynomial-ops)。$f(x + c)$ の係数が欲しいなら Taylor shift である。

## 演算の一覧と計算量（inv・log・exp・pow・sqrt） {#operations}

先頭 $N$ 項を求めるときの、定義できる条件と計算量は次のとおりである（$a_0 = [x^0] f$）。

| 演算 | 条件 | ニュートン法 | 素朴な方法 |
| --- | --- | --- | --- |
| 逆元 $1/f$ | $a_0 \ne 0$ | $O(N \log N)$ | $O(N^2)$ |
| $\log f$ | $a_0 = 1$ | $O(N \log N)$ | $O(N^2)$ |
| $\exp f$ | $a_0 = 0$ | $O(N \log N)$ | $O(N^2)$ |
| 累乗 $f^M$ | なし（下の注意） | $O(N \log N)$ | $O(N^2)$ |
| 平方根 $\sqrt{f}$ | 下の注意 | $O(N \log N)$ | $O(N^2)$ |

**ニュートン法で精度を倍にする**。逆元なら、$f g \equiv 1 \pmod{x^m}$ を満たす $g$ から $h = g (2 - f g)$ を作ると、$1 - f h = (1 - f g)^2$ なので $f h \equiv 1 \pmod{x^{2m}}$ になる。$1 - fg$ は $x^m$ で割り切れ、その 2 乗は $x^{2m}$ で割り切れるからである。$g = 1/a_0$ から始めて精度を $1, 2, 4, \dots$ と倍にする。長さ $m$ の段では長さ $O(m)$ の畳み込みを定数回するので、合計は $O(N \log N)$ である（最後の段が支配的）。exp と平方根も、$\log g - f$ や $g^2 - f$ を 0 に近づける同じ形の反復になる。log は $\log f = \int \frac{f'}{f}$ で、微分と積分は $O(N)$、割り算は逆元 1 回で済む。累乗は $f^M = \exp(M \log f)$ である。どれも畳み込みを何回も呼ぶので、定数倍は畳み込み 1 回よりかなり重い。

**素朴な方法**。どの演算も、係数を下から 1 つずつ決める $O(N^2)$ の式がある。$g = 1/f$ なら $f g = 1$ の $x^n$ の係数から $g_n = -\frac{1}{a_0} \sum_{k=1}^{n} a_k g_{n-k}$ である。$g = \exp f$ なら $g' = f' g$ から $n g_n = \sum_{k=1}^{n} k a_k g_{n-k}$ になる。$g = f^M$（$a_0 \ne 0$）なら $f g' = M f' g$ の係数を比べる（$'$ は微分）。$N$ が数千までならこれで足りる。$f$ の項が $K$ 個しかないときは $O(NK)$ になり、Library Checker にも項の少ない版（`*_sparse`）がある。ニュートン法を自作したら、この方法と乱数の入力で比べて確かめるとよい。

ACL にあるのは畳み込みだけで、ここに挙げた演算は自作する。実装と要点は[ライブラリの節](#library)にまとめる。

## 多項式の割り算・Taylor shift・多点評価 {#polynomial-ops}

冪級数としての演算（先頭 $N$ 項）と違い、ここでは次数の決まった多項式そのものを扱う。どれも逆元や畳み込みに帰着する。

**多項式の割り算**。$N - 1$ 次の $f$ を $M - 1$ 次の $g$ で割った商 $q$（$N - M$ 次）と余り $r$（$M - 2$ 次以下）を求める（$N \ge M$ のとき。$N < M$ なら $q = 0$・$r = f$ である）。係数の並びを反転した多項式を $\operatorname{rev}(f) = x^{N-1} f(1/x)$ と書くと、$f = q g + r$ の上の $N - M + 1$ 項だけを見た式は

$$
\operatorname{rev}(q) \equiv \operatorname{rev}(f) \cdot \frac{1}{\operatorname{rev}(g)} \pmod{x^{N-M+1}}
$$

になる。$\operatorname{rev}(g)$ の定数項は $g$ の最高次の係数（0 でない）なので逆元が作れる。$q$ を求めたら $r = f - q g$ で、全体は $O(N \log N)$ である。割り算の筆算を上の次数からたどると $O(NM)$ である。

**Taylor shift**（$f(x + c)$ の係数）。$f(x) = \sum_i a_i x^i$ を二項定理で展開すると

$$
[x^j] f(x + c) = \frac{1}{j!} \sum_{i \ge j} \left( a_i \, i! \right) \frac{c^{i-j}}{(i - j)!}
$$

になる。添字の差 $i - j$ が一定の和なので、片方を反転すれば畳み込み 1 回で済み、$O(N \log N)$ である（[i − j = k の形は片方を反転する](../math/convolution-ntt.md#reverse)）。階乗とその逆元の表を前計算しておく。上昇階乗 $x(x+1)\cdots(x+N-1)$ を倍々に作るのに使える（[第 1 種スターリング数](../comb/stirling-first.md#fps)）。

**多点評価と補間**。$N - 1$ 次の $f$ の値を $M$ 個の点 $p_0, \dots, p_{M-1}$ で求める。$f(p) = f \bmod (x - p)$ を使い、点を半分ずつに分けた木の各ノードに $\prod (x - p_i)$ を持たせる（積の木）。根から順に、親の余りを子の積で割った余りを子に渡すと、葉で $f(p_i)$ が得られる。各段の割り算の次数の合計が $O(N + M)$ なので、全体で $O((N + M) \log^2 (N + M))$ になる。逆に $N$ 点の値から係数を戻す補間も、積の木とその微分の多点評価で $O(N \log^2 N)$ である。点が $0, 1, \dots, N - 1$ のように等間隔なら、[ラグランジュ補間](../math/lagrange-interpolation.md#linear-time)のほうが簡単で速い。

どれも定数倍が重く、ABC でそのまま要ることはまれである。$O(N^2)$ で間に合う制約なら素朴な方法を使う。

## ACL の convolution と自作するときの要点 {#library}

!!! info "ACL では"
    `#include <atcoder/convolution>`。ACL にあるのは `atcoder::convolution(a, b)`（長さの和を $n$ として $O(n \log n)$、法は NTT 向きの素数）だけで、逆元・log・exp・累乗は自作する。法の条件と長さの上限は [ACL の convolution の要件](../math/convolution-ntt.md#acl)にある。

逆元・log・exp をニュートン法で書くと次のようになる。完全なプログラムは [`snippets/fps-basics/newton.cpp`](https://github.com/yuukougun/kyopro-atlas/blob/main/snippets/fps-basics/newton.cpp) で、素朴な方法との比較も同じファイルにある。

```cpp
--8<-- "fps-basics/newton.cpp:inv"
```

```cpp
--8<-- "fps-basics/newton.cpp:log-exp"
```

完全なプログラム：[`newton.cpp`](https://github.com/yuukougun/kyopro-atlas/blob/main/snippets/fps-basics/newton.cpp)（GitHub）。`mint` は ACL の `modint998244353`（[modint](../math/modint.md)）。
{ .kp-code-src }

この exp は反復のたびに log（中で逆元）を呼ぶので、計算量は $O(N \log N)$ だが定数倍が重い。それでも手元では $N = 5 \times 10^5$ で 0.5 秒ほどで、ふつうはこれで足りる。さらに速くしたいときは、資料にある逆元を同時に更新する書き方に替える。

自作するときの要点は次のとおりである。

- **切り詰め**：掛けるたびに必要な項数に切る。切らないと長さが倍々に増える。反復の中で掛ける $f$ も、今の精度の $2m$ 項に切っておく。
- **定数項の条件**：$\log$ は $a_0 = 1$ に正規化してから（$a_0 \ne 1$ なら $a_0$ で割った後の log を使う）、$\exp$ は $a_0 = 0$ のときだけ使う。$\log f$ の定数項は 0、$\exp f$ の定数項は 1 である。
- **累乗で $a_0 = 0$**：$M = 0$ なら $f$ に関係なく答えは $1$ である（空の積）。$M \ge 1$ なら、最初の 0 でない係数を $a_d x^d$ とし、$f = a_d x^d \cdot h$（$h$ の定数項は 1）と分けて $f^M = a_d^M x^{dM} \exp(M \log h)$ とする。$dM \ge N$ なら答えはすべて 0 で、Library Checker では $M$ が $10^{18}$ まであるので $d M$ をそのまま掛けず、割り算で比べる（[オーバーフロー](../guide/glossary.md#overflow)）。$\exp$ に渡す $M$ は $M \bmod p$ でよいが、$a_d^M$ は元の $M$ で繰り返し二乗法をする（$O(\log M)$。指数を縮めるなら $M \bmod (p - 1)$）。比較の $dM \ge N$ も元の $M$ で行う。
- **平方根**：$f$ の先頭 $N$ 項がすべて 0 なら答えは 0 である。$a_0 = 0$ なら、最初の 0 でない係数の位置 $d$ が偶数でなければ平方根はない。$d$ が偶数なら $x^{d/2}$ をくくり出す。残りの定数項 $b$ は mod $p$ の平方根を持つ必要がある（持たなければ平方根はない）。平方根は [Tonelli-Shanks 法](../math/multiplicative-order.md#mod-root)などで求め、$\pm$ のどちらを選んでも平方根になる。

自作したら、[練習問題](#practice)の Library Checker の問題で演算ごとに確かめる。

## 学ぶための資料 {#resources}

- [hotman78「【競技プログラミング】形式的冪級数の応用テクニック(前編)」](https://qiita.com/hotman78/items/f0e6d2265badd84d429a)：逆元・log・exp・累乗・平方根をニュートン法で求める流れと計算量、定数項の条件を短くまとめている。和が $t$ になる部分集合の数を log と exp で求める例もある。
- [Nyaan「多項式/形式的冪級数ライブラリ」](https://nyaannyaan.github.io/library/fps/formal-power-series.hpp)：NTT 向きの法での演算をひとまとめにした実装である。多点評価・補間も同じライブラリにあり、自作するときの関数の切り分けの参考になる。
- [drken「「Polynomial Taylor Shift」に学ぶ畳み込み芸」](https://drken1215.hatenablog.com/entry/2023/09/08/003100)：Taylor shift の式を、和の順序を入れ替えて畳み込みに直す流れを丁寧に追っている。

## 例題 {#examples}

### ABC318 Ex. Count Strong Test Cases {#abc318_h}

<div class="kp-problems" data-role="example" markdown>

- [ABC318 Ex. Count Strong Test Cases](https://atcoder.jp/contests/abc318/tasks/abc318_h)（diff 2785）：1〜N の順列 P・Q で辺 i → P_i（重み Q_i）を張ったグラフの閉路をなくすために消す辺の重みの和を最小化する問題について、辺を番号の小さい順に見る貪欲法と大きい順に見る貪欲法がどちらも誤る (P, Q) の組の数を 998244353 で割った余りで求める。

</div>

方針：グラフは順列の巡回ごとの閉路に分かれ、最適解は各閉路で重み最小の辺を 1 本消す。小さい順の貪欲法は各閉路で番号最小の辺を消す（大きい順なら番号最大の辺を消す）ので、小さい順が正しいのは「どの閉路でも番号最小の辺の重みが最小」のときである。包除原理で「どちらかが正しい」組を数えて全体から引き、正しい組の数を指数型母関数の exp で求める。

??? note "解法の詳細"
    - 小さい順が正しい組の集合を $A$、大きい順が正しい組の集合を $B$ とする。答えは $(N!)^2 - \lvert A \rvert - \lvert B \rvert + \lvert A \cap B \rvert$ で、番号を反転すれば $\lvert A \rvert = \lvert B \rvert$ である。長さ 2 以上の閉路では番号最大と最小の辺が同時に重み最小になれない。よって両方正しいのはすべて自己ループ（$P$ が恒等置換）のときで、$\lvert A \cap B \rvert = N!$ になる。
    - $P$ を固定すると、$Q$ を一様に選んだとき、長さ $t$ の閉路で番号最小の辺が重み最小である確率は $1/t$ で、閉路ごとに独立である。よって $\lvert A \rvert = N! \sum_P \prod_{\text{閉路}} \frac{1}{t}$ になる。
    - 長さ $t$ の巡回は $(t-1)!$ 通りあり、重み $1/t$ を掛けた指数型母関数は $\sum_{t \ge 1} \frac{(t-1)!}{t} \frac{x^t}{t!} = \sum_{t \ge 1} \frac{x^t}{t^2}$ である。順列は巡回の集まりなので、$\sum_P \prod \frac{1}{t} = N! \, [x^N] \exp\left( \sum_{t \ge 1} \frac{x^t}{t^2} \right)$ となる。
    - 以上から答えは $(N!)^2 - 2 (N!)^2 [x^N] \exp\left( \sum_t \frac{x^t}{t^2} \right) + N!$ で、exp 1 回の $O(N \log N)$ で求まる。$N \le 5$ では全探索の値と一致することを手元で確かめた。
    - けんちょん氏の解説は、閉路の大きさで分ける DP $g(x) = \sum_{y < x} \frac{g(y)}{\max(y, 1) (x - y)}$ を立て、[オンライン畳み込み](../math/online-convolution.md#online)で $O(N \log^2 N)$ にしている。上の exp は、この DP の母関数を閉じた形で解いたものにあたる。

## 練習問題 {#practice}

<div class="kp-problems" data-role="practice" markdown>

- [ABC245 D. Polynomial division](https://atcoder.jp/contests/abc245/tasks/abc245_d)（diff 815）：N 次の多項式 A(x) と、A(x)B(x) = C(x) を満たす N+M 次の多項式 C(x) の係数が与えられるとき、B(x) の係数を求める。
- [ABC321 F. #(subset sum = K) with Add and Erase](https://atcoder.jp/contests/abc321/tasks/abc321_f)（diff 1645）：空の箱にボールを入れる・取り出すクエリのたびに、箱の中のボールから書かれた数の和が K になるように選ぶ方法の数を 998244353 で割った余りで答える。
- [ABC303 Ex. Constrained Tree Degree](https://atcoder.jp/contests/abc303/tasks/abc303_h)（diff 2501）：各頂点の次数が与えられた集合に入る N 頂点のラベル付き木の個数を 998244353 で割った余りで求める。

</div>

??? note "練習の方針"
    - ABC245 D：$C$ の最高次の係数から順に、$B$ の係数を 1 つずつ決める割り算の筆算である（$O(NM)$）。
    - ABC321 F：値 $v$ を入れる操作は $(1 + x^v)$ を掛けること、取り出す操作は割ることで、どちらも $K$ 次までの係数の足し引きで $O(K)$ になる（[戻す DP](../dp/knapsack-undo.md)が例題として扱う）。
    - ABC303 Ex：Prüfer 列で、答えは $(N-2)! \, [x^{N-2}] F(x)^N$（$F(x) = \sum_{d \in S} \frac{x^{d-1}}{(d-1)!}$）になる。累乗を log と exp で $O(N \log N)$ にする（[母関数の考え方](../comb/generating-function-counting.md#abc303_h)が例題として扱う）。

### Library Checker

自作したら、演算ごとに次の問題で確かめる。

- [Inv of Formal Power Series](https://judge.yosupo.jp/problem/inv_of_formal_power_series)：逆元。
- [Log of Formal Power Series](https://judge.yosupo.jp/problem/log_of_formal_power_series)：log（$a_0 = 1$）。
- [Exp of Formal Power Series](https://judge.yosupo.jp/problem/exp_of_formal_power_series)：exp（$a_0 = 0$）。
- [Pow of Formal Power Series](https://judge.yosupo.jp/problem/pow_of_formal_power_series)：累乗。$a_0 = 0$ や $M = 0$ の入力も来る。
- [Sqrt of Formal Power Series](https://judge.yosupo.jp/problem/sqrt_of_formal_power_series)：平方根。ないときは $-1$ を出す。
- [Division of Polynomials](https://judge.yosupo.jp/problem/division_of_polynomials)：多項式の商と余り。
- [Polynomial Taylor Shift](https://judge.yosupo.jp/problem/polynomial_taylor_shift)：$f(x + c)$ の係数。
- [Multipoint Evaluation](https://judge.yosupo.jp/problem/multipoint_evaluation)・[Polynomial Interpolation](https://judge.yosupo.jp/problem/polynomial_interpolation)：多点評価と補間。

## 参考 {#references}

- [hotman78「【競技プログラミング】形式的冪級数の応用テクニック(前編)」](https://qiita.com/hotman78/items/f0e6d2265badd84d429a)：学ぶための資料。各演算の計算量と定数項の条件、累乗を log と exp で求める方法
- [Nyaan「多項式/形式的冪級数ライブラリ」](https://nyaannyaan.github.io/library/fps/formal-power-series.hpp)：学ぶための資料。自作するときの実装の参考
- [Nyaan「Multipoint Evaluation」](https://nyaannyaan.github.io/library/fps/multipoint-evaluation.hpp)：多点評価の実装（積の木を作り、余りを葉へ下ろすコード。説明の文章はない）
- [drken「「Polynomial Taylor Shift」に学ぶ畳み込み芸」](https://drken1215.hatenablog.com/entry/2023/09/08/003100)：学ぶための資料。Taylor shift の式と計算量
- [drken「AtCoder ABC 318 Ex - Count Strong Test Cases (橙色, 650 点)」](https://drken1215.hatenablog.com/entry/2023/09/03/161400)：例題 ABC318 Ex の包除原理と閉路の大きさの DP
- [drken「AtCoder ABC 245 D - Polynomial division (1Q, 緑色, 400 点)」](https://drken1215.hatenablog.com/entry/2022/03/29/190000)：練習 ABC245 D
- [drken「AtCoder ABC 303 Ex - Constrained Tree Degree (橙色, 600 点)」](https://drken1215.hatenablog.com/entry/2023/05/28/010200)：練習 ABC303 Ex
- [drken「AtCoder ABC 321 F - #(subset sum = K) with Add and Erase (青色, 525 点)」](https://drken1215.hatenablog.com/entry/2023/09/25/070100)：練習 ABC321 F
- [AtCoder「AC Library のドキュメント（document_ja）」](https://github.com/atcoder/ac-library/tree/master/document_ja)：ACL の convolution の宣言と計算量
- [yosupo「Library Checker の問題（polynomial）」](https://github.com/yosupo06/library-checker-problems/tree/master/polynomial)：確かめに使う問題の名前と条件
