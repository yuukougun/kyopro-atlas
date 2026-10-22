---
id: hadamard-transform
title: XOR 畳み込み
aliases: [アダマール変換, Walsh-Hadamard, FWHT, XOR convolution, 添字の XOR の畳み込み]
type: overview
field: math
chapter: 畳み込みと多項式
order: 380
level: 発展
kind: [畳み込み・多項式, ビット演算]
prerequisites: [convolution-ntt, bit-operations]
related: [zeta-mobius-subset, zeta-mobius-divisor, nim, fft-ntt]
summary: c_k = Σ_{i XOR j = k} a_i b_j を、アダマール変換で各点の積に直して O(N log N) で求める。添字の演算（和・XOR・AND/OR・gcd/lcm）ごとに使う変換が変わる。
complexity: 長さ 2^n の列で、変換・逆変換・XOR 畳み込みは O(n 2^n)（長さ N = 2^n なら O(N log N)）。同じ列の K 回の畳み込みは O(2^n (n + log K))
signs:
  - {type: phrase, text: i XOR j = k となる組をすべての k について数える}
  - {type: phrase, text: XOR が 0 でない Nim の盤面の数を数える}
  - {type: constraint, text: 値が 2^16〜2^20 程度で、添字の XOR で畳み込む}
acl: []
verify: [bitwise_xor_convolution]
frequency: C
frequency_evidence: recent 0・前提として届くページなし・古い ABC 1 問
sections:
  - {title: 'アダマール変換と逆変換（各 bit で (x + y, x − y)）', anchor: transform}
  - {title: 同じ配列を K 回 XOR 畳み込みする（変換後の累乗）, anchor: power}
  - {title: 添字の演算と変換の対応（和は FFT、AND/OR は高速ゼータ変換、gcd/lcm は約数のゼータ変換）, anchor: index-operations}
  - {title: 自作するときの要点と Library Checker, anchor: library}
stage: reviewed
updated: 2026-10-22
---

!!! abstract "要点"
    - **何ができるか**：$c_k = \sum_{i \oplus j = k} a_i b_j$（添字の XOR についての畳み込み）を、アダマール変換で各点の積に直して $O(N \log N)$ で求める。同じ列を $K$ 回畳み込むのも、変換した各点を $K$ 乗するだけで済む。添字の演算（和・XOR・AND/OR・gcd/lcm）ごとに使う変換が変わる。
    - **いつ使うか**：
        - $i \oplus j = k$ となる組を、すべての $k$ について数える。
        - XOR が 0 でない Nim の盤面の数を数える。
        - 値が $2^{16}$〜$2^{20}$ 程度で、添字の XOR で畳み込む。
    - **計算量**：長さ $N = 2^n$ の列で、変換・逆変換・XOR 畳み込みは $O(n 2^n) = O(N \log N)$。同じ列の $K$ 回の畳み込みは $O(2^n (n + \log K))$
    - **前提**：[畳み込みの使い方](../math/convolution-ntt.md)、[bit 演算の基本と XOR の性質](../basics/bit-operations.md)

<!-- textlint-disable -->
別名：アダマール変換・Walsh-Hadamard・FWHT・XOR convolution・添字の XOR の畳み込み
<!-- textlint-enable -->

XOR 畳み込みは、2 つの列から「添字の XOR が $k$ になる組の積の和」を作る演算である。組をすべて試すと長さ $N$ の列で $O(N^2)$ かかるが、アダマール変換をかけると XOR 畳み込みが各点の積になり、$O(N \log N)$ で求まる。仕組みは添字の和の[畳み込み](../math/convolution-ntt.md)と同じ「変換 → 各点の積 → 逆変換」で、変換が bit ごとの和と差に変わる。ACL には入っていないので自作する。

このページで使う記法：列は 0-indexed で長さを $2^n$ とし、添字を $n$ bit の整数とみる。$\oplus$ は XOR、$\operatorname{popcount}(x)$ は $x$ の 2 進表記の 1 の個数（[popcount](../guide/glossary.md#popcount)）である（[記法と用語の約束](../start/notation.md#sets-bits)）。

## アダマール変換と逆変換（各 bit で (x + y, x − y)） {#transform}

列 $a$ のアダマール変換 $\hat{a}$ を次で定める。

$$
\hat{a}_s = \sum_{i=0}^{2^n - 1} (-1)^{\operatorname{popcount}(i \text{ AND } s)} \, a_i
$$

**なぜ各点の積になるか**：符号 $\chi_s(i) = (-1)^{\operatorname{popcount}(i \text{ AND } s)}$ は、$s$ の 1 の位置のうち $i$ も 1 である bit の個数の偶奇である。bit ごとに見ると $(i \oplus j)$ の bit は $i$ と $j$ の bit の和の偶奇なので、$\chi_s(i)\,\chi_s(j) = \chi_s(i \oplus j)$ が成り立つ。よって $c = a \ast_{\oplus} b$ について

$$
\hat{c}_s = \sum_{k} \chi_s(k) \sum_{i \oplus j = k} a_i b_j = \sum_{i, j} \chi_s(i)\,a_i \cdot \chi_s(j)\,b_j = \hat{a}_s \, \hat{b}_s
$$

となる。和の畳み込みで指数法則 $x^i x^j = x^{i+j}$ が担う役目を、XOR では $\chi_s(i)\chi_s(j) = \chi_s(i \oplus j)$ が担っている。

**逆変換は同じ変換を 2^n で割ったもの**：同じ変換をもう一度かけて $2^n$ で割ると元に戻る。

??? note "証明：2 回かけると 2^n 倍に戻る"
    変換を 2 回かけると $\sum_s \chi_s(i)\chi_s(k) = \sum_s \chi_s(i \oplus k)$ が掛かる。$i = k$ なら $2^n$ である。$i \ne k$ なら $i \oplus k$ の 1 の bit $t$ を 1 つ取ると、$s$ と $s \oplus 2^t$ で符号が逆になり、和は 0 になる。したがって 2 回かけると元の列の $2^n$ 倍に戻り、逆変換は「もう一度変換して $2^n$ で割る」で済む。

**なぜ速いか**：符号は bit ごとの積 $\chi_s(i) = \prod_t (-1)^{i_t s_t}$ に分かれるので、変換も 1 bit ずつ行える。bit $t$ だけが違う添字の組 $(x, y)$（$x$ が bit $t$ が 0 の側）を $(x + y,\ x - y)$ に置き換える操作を、$t = 0, 1, \dots, n - 1$ の順に全体へ行う。1 段が $O(2^n)$ で $n$ 段なので $O(n 2^n)$ である。[高速ゼータ変換](../comb/zeta-mobius-subset.md#vs-xor)と同じ形のループで、1 段の式だけが違う。

小さな例で確かめる。$n = 1$、$a = (1, 2)$、$b = (3, 4)$ とする。素朴に計算すると $c_0 = a_0 b_0 + a_1 b_1 = 11$、$c_1 = a_0 b_1 + a_1 b_0 = 10$ である。変換すると $\hat{a} = (1 + 2,\ 1 - 2) = (3, -1)$、$\hat{b} = (3 + 4,\ 3 - 4) = (7, -1)$ で、各点の積は $(21, 1)$ になる。これをもう一度変換すると $(22, 20)$ で、$2^1$ で割ると $(11, 10)$ となり、素朴な計算と一致する。

次のコード片は、mod 998244353 で変換と XOR 畳み込みを行う。$2^n$ で割る代わりに、その逆元を掛ける。

```cpp
--8<-- "hadamard-transform/xor-convolution.cpp:core"
```

??? question "確認問題：長さをそろえるとき 2 倍にするか"
    値が $0$ 以上 $V$ 未満の列どうしを XOR 畳み込みする。和の畳み込みでは結果の長さが $2V - 1$ になるので長さを 2 倍に取った。XOR 畳み込みでも 2 倍にする必要があるか。

    ??? success "答え"
        要らない。$2^n \ge V$ となる最小の $n$ を取れば、$2^n$ 未満の 2 数の XOR は $2^n$ 未満なので、結果も長さ $2^n$ に収まる。和と違い、桁上がりが起きないからである。

## 同じ配列を K 回 XOR 畳み込みする（変換後の累乗） {#power}

同じ列 $a$ を $K$ 回 XOR 畳み込みした列は、変換した各点を $K$ 乗して逆変換すれば求まる。各点の積になるので、$K$ 回の畳み込みは $\hat{a}_s^K$ になるからである。各点の累乗を[繰り返し二乗法](../math/mod-pow.md)で行えば、全体は $O(2^n (n + \log K))$ である。$K = 0$ では各点が 1 になり、逆変換すると $(1, 0, \dots, 0)$ になる。これは XOR 畳み込みの[単位元](../guide/glossary.md#identity-element)で、「0 個の XOR は 0」に当たる。

```cpp
--8<-- "hadamard-transform/xor-convolution.cpp:power"
```

**典型の型：XOR が決まった値になる列を数える**。「各要素を候補の集合から選んで長さ $K$ の列を作るとき、全要素の XOR が $x$ になる列はいくつか」は、候補の[指示関数](../guide/glossary.md#indicator) $f$（候補の値に 1 を立てた列）を $K$ 回 XOR 畳み込みした列の第 $x$ 項である。Nim の盤面の数え上げはこの形で、先手必勝の数は XOR が 0 でない列の数になる（[必勝局面の数え上げ](../comb/nim.md#counting)）。

**長さが範囲で与えられるとき**：長さ $1$ から $L$ までの列をすべて数えるなら、各点で等比数列の和 $v + v^2 + \dots + v^L$（$v = \hat{f}_s$）を取ってから逆変換する。mod $p$ で公式 $v(v^L - 1)/(v - 1)$ を使うときは、$v \equiv 1 \pmod p$ の点だけ分母が 0 になるので、和を $L$ として別に扱う。割り算を避けて、$L$ の偶奇で半分の長さに帰着する分割統治で $O(\log L)$ で求めてもよい。

## 添字の演算と変換の対応（和は FFT、AND/OR は高速ゼータ変換、gcd/lcm は約数のゼータ変換） {#index-operations}

「$c_k = \sum_{i \circ j = k} a_i b_j$」の形の畳み込みは、添字の演算 $\circ$ ごとに、畳み込みを各点の積に変える変換がある。どれも「変換 → 各点の積 → 逆変換」の同じ流れで、違うのは変換だけである。

| 添字の演算 | 変換 | 計算量 | ページ |
| --- | --- | --- | --- |
| 和 $i + j$ | FFT・NTT（ACL の `convolution`） | $O(N \log N)$ | [畳み込み](../math/convolution-ntt.md) |
| XOR | アダマール変換 | $O(n 2^n)$ | このページ |
| OR・AND | 部分集合・上位集合のゼータ変換 | $O(n 2^n)$ | [OR 畳み込み・AND 畳み込み](../comb/zeta-mobius-subset.md#or-and-convolution) |
| gcd・lcm | 倍数・約数のゼータ変換 | $O(N \log \log N)$ | [GCD 畳み込み・LCM 畳み込み](../comb/zeta-mobius-divisor.md#gcd-lcm-convolution) |

表の $N$ は列の長さ（gcd・lcm では添字の上限）、$n$ は bit の数である。どの変換を使うかは、問題を「添字の何が $k$ になる組を数えるか」に言い換えたときの演算で決まる。OR・AND・XOR の 3 つは、bit ごとに 1 段ずつ $(x, y)$ を書き換える点が共通で、1 段の式だけが違う（[XOR 畳み込みとの違い](../comb/zeta-mobius-subset.md#vs-xor)）。

AND・OR の変換と逆変換は足し算と引き算だけなので整数のまま戻せるが、XOR の逆変換は $2^n$ で割るので、法は奇数に限る（[自作するときの要点](#library)）。

## 自作するときの要点と Library Checker {#library}

ACL に対応する関数はない。自作するときの要点は次のとおりである。

- **長さ**：値の上限 $V$ 以上の 2 のべき $2^n$ にそろえ、足りない分は 0 で埋める。結果の長さも $2^n$ のままでよい。
- **逆変換の割り算**：もう一度変換してから、全体に $2^n$ の逆元を 1 回掛ける。2 で割るのを各段で行ってもよいが、掛ける回数が増える。
- **mod を取らないとき**：変換後の値は元の値の $2^n$ 倍まで大きくなり、積はその 2 乗になる。$n = 16$ で元の値が $10^5$ なら、積は $(2^{16} \times 10^5)^2 \approx 4 \times 10^{19}$ で `long long` を超える。最後の $2^n$ での割り算は割り切れるので、値が収まるなら整数のままでよい。
- **偶数の法では戻せない**：$2^{64}$ で割った余りなど、法が偶数だと $2^n$ の逆元がない。998244353 や $10^9 + 7$ のような奇数の法なら問題ない。
- **変換したまま使う**：同じ列と何度も畳み込むなら、変換した列を持っておき、逆変換は最後に 1 回だけ行う（[同じ配列を K 回](#power)の形）。

自作した関数は Library Checker で確かめる。

- [Bitwise Xor Convolution](https://judge.yosupo.jp/problem/bitwise_xor_convolution)：$N \le 20$ について、長さ $2^N$ の 2 つの列の XOR 畳み込みを 998244353 で割った余りで求める。

## 学ぶための資料 {#resources}

<!-- textlint-disable -->
- sapphire15 氏の「Hadamard 変換とbitwise XOR convolution」：アダマール行列を 2 × 2 の行列の Kronecker 積で定義し、XOR 畳み込みが各点の積になることを符号の偶奇から証明している。剰余で割り算を避ける実装と、AND・OR 畳み込みへの拡張もある。
- izu_nori 氏の「xor畳み込みと高速Hadamard変換」：$n = 2$ の行列から帰納法で示す流れと、疎な行列の積に分解して $O(N \log N)$ にする説明。付録に、XOR 畳み込みを $(\mathbb{Z}/2\mathbb{Z})^n$ 上のフーリエ変換とみる見方と AND・OR の場合がある。
<!-- textlint-enable -->
- kazuma8128 氏の「色々な畳み込み」：添字の和・AND・OR・XOR ごとに使う変換を短くまとめた一覧。

## 例題 {#examples}

### ABC212 H. Nim Counting {#abc212_h}

<div class="kp-problems" data-role="example" markdown>

- [ABC212 H. Nim Counting](https://atcoder.jp/contests/abc212/tasks/abc212_h)（diff 2741）：K 種類の整数から長さ 1 以上 N 以下の列（Nim の山の大きさ）を作るとき、先手が勝つものの個数を 998244353 で割った余りで求める。

</div>

Nim で先手が勝つのは、山の大きさの XOR が 0 でないときである。長さ $M$ の列の XOR の分布は、候補の指示関数 $f$（長さ $2^{16}$）を $M$ 回 XOR 畳み込みしたものなので、$M = 1, \dots, N$ について足し合わせ、XOR が 0 でない項の和を答える。

??? note "解法の詳細"
    1. 候補の値に 1 を立てた長さ $2^{16}$ の列 $f$ を作り、アダマール変換して $\hat{f}$ を得る。
    2. 各点の値 $v = \hat{f}_s$ を、等比数列の和 $v + v^2 + \dots + v^N$ に置き換える。$v \equiv 0$ なら 0、$v \equiv 1$ なら $N$、それ以外は $v(v^N - 1)/(v - 1)$ で求める。
    3. 逆変換すると、長さ $1$ から $N$ までの列について XOR ごとの個数が得られる。第 1 項以降（XOR が 0 でない項）の和が答えである。全体の数 $K + K^2 + \dots + K^N$ から第 0 項を引いてもよい。

    計算量は、変換が $O(16 \cdot 2^{16})$、各点の等比数列の和が、公式で逆元も求めるなら $O(2^{16} (\log N + \log p))$（$p = 998244353$）、逆元を使わない分割統治なら $O(2^{16} \log N)$ である。

## 参考 {#references}

- [sapphire15「Hadamard 変換とbitwise XOR convolution」](https://sapphire15.hatenablog.com/entry/2021/09/13/114900)：符号の偶奇による証明、逆変換を $2^n$ で割る実装、AND・OR への拡張
- [izu_nori「xor畳み込みと高速Hadamard変換」](https://qiita.com/izu_nori/items/7810fc2bc0423c8d407f)：帰納法による証明と高速化、群上のフーリエ変換としての見方
- [kazuma8128「色々な畳み込み」](https://kazuma8128.hatenablog.com/entry/2018/05/31/144519)：添字の演算ごとの変換の一覧
- [drken「AtCoder ABC 212 H - Nim Counting (4D, 橙色, 600 点)」](https://drken1215.hatenablog.com/entry/2021/08/01/025200)：例題の方針（余事象・XOR 畳み込みの累乗・割り算を避けた等比数列の和）
- [kmjp「AtCoder ABC #212 : H - Nim Counting」](https://kmjp.hatenablog.jp/entry/2021/08/03/0930)：例題の方針（変換後の各点で等比数列の和を取り、値が 1 の点を別に扱う）
- [Library Checker「Bitwise Xor Convolution」の問題定義（GitHub）](https://github.com/yosupo06/library-checker-problems/tree/master/convolution/bitwise_xor_convolution)：問題の内容と制約（$N \le 20$、法 998244353）
