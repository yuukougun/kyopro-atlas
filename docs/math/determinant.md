---
id: determinant
title: 行列式
aliases: [determinant, 行列式 mod p]
type: overview
field: math
chapter: 行列と線形代数
order: 350
level: 発展
kind: [線形代数・行列]
prerequisites: [gaussian-elimination]
related: [matrix-tree-theorem, spanning-tree-advanced, lgv-lemma]
summary: 掃き出し法で上三角にし、対角成分の積に行の交換の回数だけ符号を掛けて行列式を O(n³) で求める。全域木の数を数える行列木定理の部品になる。
complexity: O(N^3)（法が素数なら逆元で割る掃き出し）、素数でない法 m は互除法で O(N^3 + N^2 log m)、mod 2 は bitset で O(N^3/64)
signs:
  - {type: phrase, text: 行列式を mod p で求める}
  - {type: phrase, text: 全域木の個数・交わらない経路の組の数}
acl: []
verify: [matrix_det, matrix_det_mod_2, matrix_det_arbitrary_mod]
frequency: C
frequency_evidence: recent 0・前提として 2 ページに届く（直接 2）・古い ABC 0 問
sections:
  - {title: 掃き出しで行列式を求める（行の交換で符号が変わる）, anchor: by-elimination}
  - {title: mod p での計算と、法が素数でない場合（互除法による掃き出し）, anchor: modulus}
  - {title: 行列木定理・LGV 補題への入口, anchor: applications}
  - {title: 計算量と自作するときの要点, anchor: library}
stage: done
updated: 2026-10-29
---

!!! abstract "要点"
    - **何ができるか**：掃き出し法で上三角にし、対角成分の積に行の交換の回数だけ $-1$ を掛けて、$N \times N$ 行列の行列式を $O(N^3)$ で求める。全域木の数を数える行列木定理や、交わらない経路の組を数える LGV 補題の部品になる。
    - **いつ使うか**：
        - 行列式を mod p で求める。
        - 全域木の個数・交わらない経路の組の数。
    - **計算量**：$O(N^3)$（法が素数なら逆元で割る掃き出し）。素数でない法 $m$ は互除法で $O(N^3 + N^2 \log m)$、mod 2 は bitset で $O(N^3 / 64)$
    - **前提**：[掃き出し法](../math/gaussian-elimination.md)

<!-- textlint-disable -->
別名：determinant・行列式 mod p
<!-- textlint-enable -->

行列式は、正方行列から 1 つの数を決める式である。定義どおりに展開すると $N!$ 個の項の和になるが、掃き出し法で上三角にすれば $O(N^3)$ で求まる。競技プログラミングでは、行列式そのものより、全域木や交わらない経路の組を数える定理の最後の 1 段として使うことが多い。

このページでは行列を $A = (a_{ij})$（$0 \le i, j < N$、0-indexed）と書き、法を $m$（素数なら $p$）とする（記法は[記法と用語の約束](../start/notation.md)）。

## 掃き出しで行列式を求める（行の交換で符号が変わる） {#by-elimination}

$N \times N$ 行列 $A$ の行列式は、$0, \dots, N-1$ の置換 $\sigma$ すべてにわたる和である。

$$
\det A = \sum_{\sigma} \operatorname{sgn}(\sigma) \prod_{i=0}^{N-1} a_{i, \sigma(i)}
$$

$\operatorname{sgn}(\sigma)$ は[置換の符号](../comb/permutation-parity.md#sign)（偶置換なら $+1$、奇置換なら $-1$）である。各行から列が重ならないように 1 つずつ成分を選んで掛け、符号を付けて足したものと言ってもよい。$2 \times 2$ なら $a_{00} a_{11} - a_{01} a_{10}$ である。

項は $N!$ 個あるので、$N = 20$ でも定義どおりには計算できない。そこで、行列式の次の 3 つの性質を使う。

1. **2 つの行を入れ替えると、符号だけが変わる**。置換に互換を 1 つ掛けることになり、各項の符号が反転するからである。
2. **ある行の定数倍を別の行に足しても、値は変わらない**。足した結果は「元の行列式」と「同じ行が 2 つある行列式の定数倍」の和に分かれ、後者は 0 である（同じ 2 行を入れ替えると、値は変わらないのに符号が変わるので 0）。
3. **上三角行列（対角より下がすべて 0）の行列式は、対角成分の積である**。恒等置換でない $\sigma$ には $\sigma(i) < i$ となる $i$ が必ずあり、その項は対角より下の 0 を含むので消える。

1 と 2 は[掃き出し法](../math/gaussian-elimination.md#row-reduction)の行基本変形のうちの 2 つである。行を定数倍する変形は値を定数倍するので使わない。よって手順は次のとおりになる。

```text
res ← 1
for c = 0, 1, ..., N-1:
    c 行目以降で、c 列が 0 でない行を探す
    なければ 0 を返す（この列から下が 0 なので、上三角にしても対角に 0 が残る）
    見つけた行が c 行目でなければ c 行目と入れ替え、res ← -res
    res ← res × a[c][c]
    c+1 行目以降の各行 r から、(a[r][c] / a[c][c]) 倍の c 行目を引く
return res
```

連立一次方程式の掃き出しと違い、ピボットより上の行は消さなくてよく、ピボットの行を 1 に割る必要もない。対角成分の値をそのまま掛けていけばよい。

たとえば $\begin{pmatrix} 0 & 2 \\ 3 & 1 \end{pmatrix}$ は 0 列目のピボットが 0 なので 2 行を入れ替え、$\begin{pmatrix} 3 & 1 \\ 0 & 2 \end{pmatrix}$ になる。すでに上三角なので、行列式は $-(3 \times 2) = -6$ である。定義の $0 \cdot 1 - 2 \cdot 3 = -6$ と一致する。

列 $c$ の処理では $N - c - 1$ 行それぞれの $N - c$ 個の成分を更新するので、全体で $O(N^3)$（およそ $N^3 / 3$ 回の掛け算と引き算）である。

## mod p での計算と、法が素数でない場合（互除法による掃き出し） {#modulus}

行列式の値は、成分が小さくてもすぐに巨大になる（$N$ 個の数の積の和である）。答えを求める問題ではふつう mod $m$ で求め、法によって書き方が変わる。

### 法が素数のとき

掃き出しの中で割り算をするのは「$a_{rc} / a_{cc}$ 倍を引く」の 1 か所だけで、ピボット $a_{cc}$ は mod $p$ で 0 でないので、[逆元](../math/mod-inverse.md)を掛ければよい。上の手順をそのまま mod $p$ で行える（完全なプログラムは [`snippets/determinant/mod-p.cpp`](https://github.com/yuukougun/kyopro-atlas/blob/main/snippets/determinant/mod-p.cpp)。小さい行列で定義どおりの和と比べている）。

```cpp
--8<-- "determinant/mod-p.cpp:core"
```

完全なプログラム：[`mod-p.cpp`](https://github.com/yuukougun/kyopro-atlas/blob/main/snippets/determinant/mod-p.cpp)（GitHub）。`mint` は ACL の `modint998244353`（[modint](../math/modint.md)）。
{ .kp-code-src }

「0 でない行を探す」の 0 は mod $p$ での 0 である。成分が $p$ の倍数なら、整数としては 0 でなくてもピボットにできない。

### 法が 2 のとき

mod 2 では $-1 \equiv 1$ なので、行の交換による符号は気にしなくてよい。上三角にした後の対角成分は 0 か 1 なので、行列式はすべての列にピボットがある（[ランク](../guide/glossary.md#rank)が $N$）とき 1、そうでなければ 0 である。行を bitset で持てば[行の引き算が XOR になり](../math/gaussian-elimination.md#mod-2)、$O(N^3 / 64)$ で求まる。

### 法が素数でないとき

法が素数でなければ、0 でない数でも逆元を持つとは限らない。mod 12 では 4 や 6 に逆元がないので、ピボットが 4 なら「$a_{rc} / 4$ 倍を引く」ができない。

そこで割り算を使わず、ユークリッドの互除法と同じ引き算で下の行の成分を 0 にする。成分を $[0, m)$ の整数の代表で持ち、列 $c$ のピボットの行 $c$ と下の行 $r$ について、$a_{rc} \ne 0$ の間、次を繰り返す。

1. 整数としての商 $q = \lfloor a_{cc} / a_{rc} \rfloor$ を求める。
2. $c$ 行目から $q$ 倍の $r$ 行目を引く。$a_{cc}$ は $a_{cc} \bmod a_{rc}$ になり、$a_{rc}$ より小さくなる。
3. $c$ 行目と $r$ 行目を入れ替え、符号を反転する。

$(a_{cc}, a_{rc})$ は互除法と同じように小さくなり、$a_{rc}$ がいつか 0 になる。使った操作は「定数倍を足す」と「入れ替え」だけなので、行列式は符号を除いて変わらない。商 $q$ は値を小さくするために選ぶだけで、mod $m$ の割り算ではないから、法が何であっても正しい。

$\begin{pmatrix} 4 & 1 \\ 6 & 5 \end{pmatrix}$（mod 12）で 0 列目を処理すると、$(a_{00}, a_{10})$ は $(4, 6) \to (6, 4) \to (4, 2) \to (2, 0)$ と進み、入れ替えは 3 回である。最後の行列は $\begin{pmatrix} 2 & 4 \\ 0 & 5 \end{pmatrix}$ なので、行列式は $-(2 \times 5) = -10 \equiv 2$ になる。定義どおりの $4 \cdot 5 - 1 \cdot 6 = 14 \equiv 2$ と一致する。

```cpp
--8<-- "determinant/arbitrary-mod.cpp:core"
```

完全なプログラム：[`arbitrary-mod.cpp`](https://github.com/yuukougun/kyopro-atlas/blob/main/snippets/determinant/arbitrary-mod.cpp)（GitHub）
{ .kp-code-src }

**計算量**：1 回の引き算は 1 行ぶんの $O(N)$ である。列 $c$ を処理する間、ピボット $a_{cc}$ は各行との互除法の結果（2 数の最大公約数）に置き換わり、前の値の約数になる。行 $r$ の処理の前後のピボットを $p_{r-1}, p_r$ とすると、互除法の回数は $\log(p_{r-1}/p_r) + O(1)$ 程度である。$r$ について足すと途中の項が消え、$\log(p_c/p_{N-1}) + O(N) \le \log m + O(N)$ になる。よって列 1 つで $O(N(N + \log m))$、全体で $O(N^3 + N^2 \log m)$ である。

法を素因数分解し、素因数ごとに求めて[中国剰余定理](../math/crt.md)で合わせる方法もある。ただし法が $p^k$（$k \ge 2$）を含むと、その部分は mod $p^k$ で求めることになり、$p$ の倍数に逆元がない問題が残る。互除法の方が素直である。

## 行列木定理・LGV 補題への入口 {#applications}

行列式を直接求めさせる問題は少なく、ほとんどは「何かを数える定理が行列式の形をしている」ので使う。代表は次の 2 つである。

- **[行列木定理](../graph/matrix-tree-theorem.md#laplacian)**：ラプラシアン行列は、対角に各頂点の次数（自己ループを除く）、$(u, v)$ 成分に $u$ と $v$ を結ぶ辺の本数（多重辺は本数をそのまま数える）の $-1$ 倍を置いた行列である。無向グラフの全域木の個数は、この行列からある頂点の行と列を除いた $(N-1) \times (N-1)$ 行列の行列式に等しい。サインは「全域木の個数を mod で答える」「辺の部分集合が木になる数」。
- **[LGV 補題](../comb/lgv-lemma.md#what)**：DAG の上で $k$ 個の始点から $k$ 個の終点への、互いに頂点を共有しない経路の組の数を、1 本ずつの経路数を並べた $k \times k$ 行列の行列式で求める。この数は置換の符号付きの和で、交わらない組が恒等置換でしか作れないように番号を付ければ個数そのものになる。サインは「K 本の経路が交わらない組の個数」「複数の駒が衝突せずに動く確率」。

どちらも、行列を作るまでがその定理のページの話で、最後の行列式はこのページの手順で求める。ラプラシアン行列のように負の成分がある行列は、mod $m$ に直すときは $m$ を足して $[0, m)$ に入れてから掃き出す。

頂点の部分集合ごとに全域木の数を求める問題では、行列式を $2^N$ 回求める（$N \le 14$ 程度なら $O(2^N N^3)$ で間に合う）。[特殊な最小全域木](../graph/spanning-tree-advanced.md)も参照のこと。

## 計算量と自作するときの要点 {#library}

ACL に行列式はないので自作する。計算量は $O(N^3)$ で、$N = 500$ なら $N^3 / 3 \approx 4 \times 10^7$ 回ほどの掛け算と引き算で済む。法が素数でなければ互除法の分が加わり $O(N^3 + N^2 \log m)$ である。

- **行列を値で受け取る**：掃き出しは行列を書き換えるので、呼び出し元の行列を使い回すならコピーを渡す（コード片は値渡しにしている）。
- **符号**：行を入れ替えるたびに $-1$ を掛ける。互除法の版では、1 回の引き算ごとに入れ替えるので、その都度反転する。
- **0 を返す条件**：列のピボット以下がすべて 0 なら、行列式は 0 である。この判定を忘れて 0 の逆元を求めると、ACL の modint なら assert で止まり、自作の累乗（$x^{p-2}$）で逆元を求めていれば誤った値になる。
- **$0 \times 0$ の行列**：行列式は空の積の 1 である。Library Checker の任意 mod の問題は、制約に $N = 0$ を含む。
- **オーバーフロー**：互除法の版の $q \times a_{rj}$ は $m^2$ 未満である。$m \le 10^9$ なら `long long` に収まるが、$m$ がもっと大きいなら `__int128` で掛ける（[繰り返し二乗法](../math/mod-pow.md)の mulmod の注意と同じ）。

自作した関数は、小さい行列で定義どおりの置換の和と比べると確実である（コード片の `det_brute`）。Library Checker の対応は[練習問題](#practice)に挙げる。

## 落とし穴 {#pitfalls}

- **行を定数倍してしまう**：連立一次方程式の掃き出しの癖でピボットの行を $a_{cc}$ で割ると、行列式も $1 / a_{cc}$ 倍になる。割るなら、割った値を別に掛け戻す。このページの手順のように行を割らなければ、この手間はない。
- **整数のまま掃き出す**：成分が整数でも、途中の $a_{rc} / a_{cc}$ は分数になる。実数（`double`）で計算すると、値が大きいときに誤差で答えの整数がずれる。整数の答えは mod で求める。
- **法が素数でないのに逆元を使う**：$10^9$ や $2^{32}$ のような法では、逆元がない数をピボットにすると、ACL の modint なら `inv()` の assert で止まり、自作の累乗で逆元を求めていれば誤った値になる。[互除法の掃き出し](#modulus)を使う。

## 学ぶための資料 {#resources}

- [「行列式」（日本語版 Wikipedia）](https://ja.wikipedia.org/wiki/%E8%A1%8C%E5%88%97%E5%BC%8F)：置換の和による定義、行の交換・定数倍の加算での変化、三角行列の行列式が対角成分の積になることが、まとめて載っている。
- [Nyaan「Determinant (arbitrary mod)」](https://nyaannyaan.github.io/library/matrix/determinant-arbitrary-mod.hpp)：素数でない法で、互除法で掃き出す実装の例。
- [OI Wiki「高斯消元」](https://oi-wiki.org/math/numerical/gauss/)（中国語）：掃き出しで行列式を求める節がある（文章と図の利用条件は CC BY-SA）。

## 練習問題 {#practice}

ABC で必須になる問題は確認できなかった。行列式を使う問題は、[行列木定理](../graph/matrix-tree-theorem.md#examples)と [LGV 補題](../comb/lgv-lemma.md#examples)のページに置く。

### Library Checker

- [Determinant of Matrix](https://judge.yosupo.jp/problem/matrix_det)：$N \le 500$ の行列式を mod 998244353 で求める。
- [Determinant of Matrix (Mod 2)](https://judge.yosupo.jp/problem/matrix_det_mod_2)：$N \le 4096$ の 0・1 の行列の行列式を mod 2 で求める（bitset の掃き出し）。
- [Determinant of Matrix (Arbitrary Mod)](https://judge.yosupo.jp/problem/matrix_det_arbitrary_mod)：$N \le 500$、法 $m \le 10^9$ は素数とは限らない。制約は $N = 0$ を含む。

## 確認問題 {#quiz}

??? question "確認問題：行を入れ替えずに済ませるには"
    ピボットが 0 のとき、行を入れ替える代わりに、下の 0 でない行を c 行目に足してもよいか。符号はどうなるか。

    ??? success "答え"
        よい。ある行（の 1 倍）を別の行に足しても行列式は変わらないので、符号の反転も要らない。足した後の $a_{cc}$ は 0 でなくなる。mod $m$ でも、0 に 0 でない値を足すので 0 にはならない。手間は入れ替えと同じ $O(N)$ で、どちらを使ってもよい（入れ替えなら符号の反転を忘れないこと）。

??? question "確認問題：mod 12 の上三角"
    mod 12 で $\begin{pmatrix} 3 & 0 \\ 0 & 4 \end{pmatrix}$ の行列式はいくつか。整数での行列式が 0 でないのに、mod では 0 になるのはなぜか。

    ??? success "答え"
        $3 \times 4 = 12 \equiv 0$ である。行列式は整数での値を $m$ で割った余りで、整数の値 12 が 12 の倍数なので 0 になる。法が素数なら、対角成分がどれも mod $p$ で 0 でなければ積も 0 でないが、素数でない法では 0 でない数どうしの積が 0 になりうる。

## 参考 {#references}

- [「行列式」（日本語版 Wikipedia）](https://ja.wikipedia.org/wiki/%E8%A1%8C%E5%88%97%E5%BC%8F)：置換の和による定義、行基本変形での値の変化、三角行列の行列式、掃き出しで $O(n^3)$ で求まること
- [OI Wiki「高斯消元」](https://oi-wiki.org/math/numerical/gauss/)：掃き出しで行列式を求める手順（ピボットが見つからなければ 0、交換で符号反転）を確かめた（文章と図は使っていない）
- [Nyaan「Determinant (arbitrary mod)」](https://nyaannyaan.github.io/library/matrix/determinant-arbitrary-mod.hpp)：素数でない法で、商を引いて行を入れ替える互除法の掃き出しの手順
- [Library Checker の問題定義（GitHub）](https://github.com/yosupo06/library-checker-problems/tree/master/linear_algebra)：3 問（matrix_det・matrix_det_mod_2・matrix_det_arbitrary_mod）の制約
