---
id: stirling-first
title: 第 1 種スターリング数
aliases: [巡回の個数ごとの順列の数, 上昇階乗, Stirling numbers of the first kind]
type: overview
field: comb
chapter: 置換・分割・木の数え上げ
order: 260
level: 発展
kind: [数え上げ, 畳み込み・多項式]
prerequisites: [permutation-cycles]
related: [bell-number, generating-function-counting, fps-basics, insertion-dp]
summary: ちょうど k 個の巡回からなる n 次の置換の数で、c(n,k) = c(n−1,k−1) + (n−1) c(n−1,k) を満たす。上昇階乗 x(x+1)…(x+n−1) の係数なので、FPS で一度に求める。
complexity: 1 行 c(N,0..N) は分割統治の畳み込みで O(N log^2 N)（Taylor shift の倍化なら O(N log N)）、表 c(n,k)（n ≤ N）は漸化式で O(N^2)、列 c(n,K)（n ≤ N）は FPS の累乗で O(N log N)
signs:
  - {type: phrase, text: 巡回（サイクル）の個数ごとの順列の数}
  - {type: phrase, text: 左から見える（最大値を更新する）位置の個数ごとの順列の数}
  - {type: phrase, text: 最小の swap 回数ごとの並びの数}
acl: [convolution]
frequency: C
frequency_evidence: recent 0・前提として届くページなし・古い ABC 2 問
sections:
  - {title: 何ができるか（巡回の個数ごとの数）, anchor: what}
  - {title: 漸化式と上昇階乗, anchor: recurrence}
  - {title: 左から見える位置の数との対応, anchor: records}
  - {title: FPS・分割統治で一度に求める, anchor: fps}
  - {title: ライブラリでの使い方, anchor: library}
  - {title: 第 2 種との違い, anchor: vs-second-kind}
stage: reviewed
updated: 2026-10-29
---

!!! abstract "要点"
    - **何ができるか**：ちょうど $k$ 個の巡回からなる $n$ 次の置換の数 $c(n, k)$ を求める。漸化式 $c(n, k) = c(n-1, k-1) + (n-1) \, c(n-1, k)$ を満たす。[上昇階乗](../guide/glossary.md#rising-factorial) $x(x+1)\cdots(x+n-1)$ を展開した $x^k$ の係数に等しいので、$k = 0, \dots, n$ の値を畳み込みで一度に求められる。
    - **いつ使うか**：
        - 巡回（サイクル）の個数ごとの順列の数を求める。
        - 左から見える（最大値を更新する）位置の個数ごとの順列の数を求める。
        - 最小の swap 回数ごとの並びの数を求める。
    - **計算量**：$c(n, k)$ の表（$n \le N$）は漸化式で $O(N^2)$。1 行 $c(N, 0), \dots, c(N, N)$ は上昇階乗を分割統治で掛けて $O(N \log^2 N)$、Taylor shift で倍々にすれば $O(N \log N)$。列 $c(n, K)$（$K$ を固定、$n \le N$）は FPS の累乗で $O(N \log N)$。
    - **前提**：[置換の巡回分解](../comb/permutation-cycles.md)

<!-- textlint-disable -->
別名：巡回の個数ごとの順列の数・上昇階乗・Stirling numbers of the first kind
<!-- textlint-enable -->

第 1 種スターリング数は、順列を巡回の個数で分類したときの各組の大きさである。巡回の個数は「任意の swap でソートする最小回数」や「左から見える位置の個数」と結び付くので、順列をこれらの量ごとに数える問題の答えになる。ABC では G・Ex に現れ、多項式の積（[畳み込み](../math/convolution-ntt.md)）と組み合わせて使う。

このページの $c(n, k)$ は符号なしの値（個数）である。資料によっては $\left[ {n \atop k} \right]$ と書く。符号付きの $s(n, k) = (-1)^{n-k} c(n, k)$ もあり、Library Checker の問題は符号付きで答える。

## 何ができるか（巡回の個数ごとの数） {#what}

数える対象は、$1, \dots, n$ の順列 $p$ を矢印 $i \to p_i$ で描いたときに、巡回がちょうど $k$ 個になるものである（巡回の作り方は[置換の巡回分解](../comb/permutation-cycles.md#decompose)）。長さ 1 の巡回（[固定点](../guide/glossary.md#fixed-point)）も 1 個と数える。

$n = 3$ の 6 個の順列を書き出すと次のようになる。

| 巡回の個数 $k$ | 順列（$p_1 p_2 p_3$） | 個数 $c(3, k)$ |
| --- | --- | --- |
| 1 | 231・312 | 2 |
| 2 | 132・213・321 | 3 |
| 3 | 123 | 1 |

小さい値は次のとおりで、各行の和は $n!$ になる（どの順列も巡回の個数がただ 1 つに決まるから）。

$$
c(4, \cdot) = (0, 6, 11, 6, 1), \qquad c(5, \cdot) = (0, 24, 50, 35, 10, 1)
$$

ここで $c(n, 0) = 0$（$n \ge 1$）、$c(0, 0) = 1$（空の順列は巡回 0 個）、$c(n, n) = 1$（恒等置換）、$c(n, 1) = (n-1)!$（1 本の輪に並べる方法）である。

問題で出会うのは、次の 3 つの言い換えのどれかであることが多い。

- **巡回の個数そのもの**：「置換を巡回に分けたときの個数が $k$」「$k$ 個の輪に人を座らせる方法（輪の回転は同一視し、裏返しは区別する。輪どうしは区別しない）」。
- **最小の swap 回数**：任意の 2 要素の swap でソートする最小回数は $n - (\text{巡回の個数})$ である（[最小回数の節](../comb/permutation-cycles.md#min-swaps)）。最小回数がちょうど $m$ の順列は $c(n, n - m)$ 個ある。
- **左から見える位置の個数**：それまでの最大値を更新する位置がちょうど $k$ 個の順列も $c(n, k)$ 個ある（[左から見える位置の節](#records)）。

## 漸化式と上昇階乗 {#recurrence}

**漸化式**。$n$ 個の順列を、$n - 1$ 個の順列に要素 $n$ を加えて作ると考える。要素 $n$ の入れ方は 2 通りに分かれる。

- **$n$ が 1 人だけの巡回を作る**（$p_n = n$）：残りの $n - 1$ 個は $k - 1$ 個の巡回を作るので $c(n-1, k-1)$ 通り。
- **$n$ を既存の巡回の中に入れる**：巡回の矢印 $i \to j$ を $i \to n \to j$ に付け替える。矢印は $n - 1$ 本あるので $(n-1) \, c(n-1, k)$ 通り。巡回の個数は変わらない。

逆に、要素 $n$ を消す（$i \to n \to j$ を $i \to j$ に戻す）と元の順列がただ 1 つに決まる。したがって重複も漏れもない。合わせて次の式になる。

$$
c(n, k) = c(n-1, k-1) + (n-1) \, c(n-1, k), \qquad c(0, 0) = 1
$$

表を埋めるだけなら $O(N^2)$ である。$N$ が数千までならこれで足りる。表全体を持つとメモリも $O(N^2)$ になるので、1 行だけが要るなら 2 行ぶんの配列を使い回す。

```cpp
--8<-- "stirling-first/rising.cpp:table"
```

**上昇階乗**。漸化式の 2 通りを多項式で書くと、「新しい巡回を作る」に $x$ を、「既存の巡回に入れる」に $n - 1$ を掛けることになる。$f_n(x) = \sum_k c(n, k) x^k$ とおくと $f_n(x) = (x + n - 1) f_{n-1}(x)$ なので、

$$
x(x+1)(x+2)\cdots(x+n-1) = \sum_{k=0}^{n} c(n, k) \, x^k
$$

である。左辺を上昇階乗と呼び、$x^{\overline{n}}$ と書く。$x = 1$ を入れると $n! = \sum_k c(n, k)$ に戻る。符号付きの $s(n, k)$ は下降階乗 $x(x-1)\cdots(x-n+1)$ の係数である。

上昇階乗の形は、問題を解くときに役に立つ。「$i$ 番目の要素を入れるとき、ある量を 1 増やす入れ方が 1 通り、変えない入れ方が $i - 1$ 通り」という形の数え上げは、どれも $\prod_i (x + i - 1)$ の係数になる。

## 左から見える位置の数との対応 {#records}

順列 $p$ の位置 $i$ が**左から見える**とは、$p_i$ がそれより左のどの値よりも大きいことをいう（左から高さ $p_i$ のビルを眺めると見える、の意味）。左から見える位置がちょうど $k$ 個の順列も $c(n, k)$ 個ある。

$n = 3$ では、見える位置が 1 個のものは 312・321、2 個のものは 132・213・231、3 個のものは 123 で、個数は巡回の表と同じ 2・3・1 になる。ただし、各組に入る順列は巡回の表と違う（231 は巡回が 1 個だが見える位置は 2 個）。等しいのは個数だけである。

**なぜ個数が等しいか**。値を大きい順に 1 つずつ、今ある列の好きな隙間へ入れて順列を作る（[値の順に挿入する見方](../dp/insertion-dp.md#insert-by-value)）。$i$ 個を並べた後、$i + 1$ 番目に大きい値を入れる隙間は $i + 1$ か所ある。

- **先頭に入れる**：入れた値は左に何もないので見える。すでにある値はどれも入れた値より大きいので、見えるかどうかは変わらない。見える位置が 1 増える。
- **それ以外の $i$ か所**：左に自分より大きい値があるので見えない。ほかの値も変わらない。

1 回目（最大の値）は必ず見えるので $x$、以降は $(x + i)$ を掛けることになり、全体は $x(x+1)\cdots(x+n-1)$ で上昇階乗と一致する。右から見える位置の個数も、左右を反転すれば同じ分布になる。

**応用の型**（サイン：「左から見える数と右から見える数の組」）。最大の値は左右のどちらからも見え、それより小さい値は先頭に入れれば左から、末尾に入れれば右から見える。左右の 2 つの量を同時に追う問題は、変数を 2 つにした積、つまり最大の値の $xy$ と $i = 1, \dots, n-1$ の $(x + y + i - 1)$ の積で考える（$i$ はすでに並べた個数で、隙間 $i + 1$ か所のうち先頭が $x$、末尾が $y$、残りの $i - 1$ か所が $1$ になる。[例題](#abc385_g)）。

## FPS・分割統治で一度に求める {#fps}

この節は[形式的冪級数と多項式の演算](../math/fps-basics.md)を前提にする。1 行 $c(N, 0), \dots, c(N, N)$ が欲しいとき、漸化式では $O(N^2)$ かかる。$N = 2 \times 10^5$ なら上昇階乗を多項式として掛ける。

**分割統治の積**。$(x + l)(x + l + 1)\cdots(x + r - 1)$ を、区間を半分に分けた 2 つの積の畳み込みで求める。深さ $\log N$ の各段で、掛ける多項式の次数の合計は $N$ なので、1 段 $O(N \log N)$、全体 $O(N \log^2 N)$ である。次数の小さい多項式から掛ける（優先度付きキューで小さい 2 つを取り出す）書き方でも同じ計算量になる。

```cpp
--8<-- "stirling-first/rising.cpp:core"
```

**Taylor shift で倍々にする**。$f_m(x) = x(x+1)\cdots(x+m-1)$ とすると $f_m(x + m) = (x + m)\cdots(x + 2m - 1)$ なので、$f_{2m}(x) = f_m(x) \cdot f_m(x + m)$ である。$f_m(x + m)$ の係数は、多項式の平行移動（Taylor shift）によって $O(m \log m)$ で求まる。$N$ を上の bit から読み、奇数のときは $(x + 2m)$ を 1 つ掛ければ、全体は $O(N \log N)$ になる。ただし Taylor shift の実装が要るので、自作するなら分割統治から作り、速さが足りないときに倍化へ替えるとよい。

**列 $c(n, K)$（$K$ を固定）**。巡回 1 個の指数型母関数は $\sum_{m \ge 1} (m-1)! \frac{x^m}{m!} = -\log(1 - x)$ で、順列は巡回の集まり（巡回どうしは区別しない）なので

$$
\sum_{n \ge 0} c(n, K) \frac{x^n}{n!} = \frac{1}{K!} \bigl( -\log(1 - x) \bigr)^{K}
$$

になる。$\sum_{m \ge 1} x^m / m$ の $K$ 乗を FPS の累乗で求め、$n! / K!$ を掛ければ、$n \le N$ の値が $O(N \log N)$ でそろう（[母関数の考え方](../comb/generating-function-counting.md)）。

## ライブラリでの使い方 {#library}

!!! info "ACL では"
    `vector<mint> c = atcoder::convolution(a, b);`（`mint` は `atcoder::modint998244353`）。長さの和を $n$ として $O(n \log n)$ で、法は $998244353$ のような NTT 向きの素数に限る（[ACL の convolution の要件](../math/convolution-ntt.md#acl)）。上昇階乗そのものの機能はないので、分割統治は[前の節](#fps)のコード片のように自分で書く。

自作するときの要点は次のとおりである。

- $n = 0$ の上昇階乗は空の積の $1$ で、$c(0, 0) = 1$ である。分割統治の再帰に区間の長さ 0 を渡さないよう、先に分ける。
- 符号付きが欲しいときは、最後に $n - k$ が奇数の項の符号を反転する（下降階乗を直接掛けてもよい）。
- 返る値は mod の値なので、「$c(n, k)$ が 0 か」「どちらが大きいか」を mod の値で判定しない。$c(n, k) > 0$ は $1 \le k \le n$（または $n = k = 0$）と同じである。

Library Checker で確かめられる問題は[練習問題の節](#practice)に挙げた（どれも符号付き）。

## 第 2 種との違い {#vs-second-kind}

[第 2 種スターリング数](../comb/bell-number.md#recurrence) $S(n, k)$ は、区別できる $n$ 個を区別しない $k$ 個の空でない組に分ける方法の数である。第 1 種は、分けた各組の中をさらに巡回に並べたもの（組の中の並びを輪として区別する）を数える。そのため $c(n, k) \ge S(n, k)$ である。大きさ 2 以下の組は輪の並べ方が 1 通りなので、どの分け方でも組の大きさが 2 以下になる $k \ge n - 1$ のとき（と $k = 0$ のとき）$c(n, k) = S(n, k)$ になる。

| | 第 1 種 $c(n, k)$ | 第 2 種 $S(n, k)$ |
| --- | --- | --- |
| 数える対象 | $k$ 個の巡回に分けた置換 | $k$ 個の組への分け方 |
| 漸化式の係数 | $(n-1) \, c(n-1, k)$ | $k \, S(n-1, k)$ |
| 多項式との関係 | $x^{\overline{n}} = \sum_k c(n, k) x^k$ | $x^n = \sum_k S(n, k) \, x(x-1)\cdots(x-k+1)$ |
| 例（$n = 4$、$k = 2$） | 11 | 7 |

漸化式の違いは、要素 $n$ を既存の部分に入れる方法の数にある。第 2 種では入る組を選ぶだけなので $k$ 通り、第 1 種では巡回の矢印のどこに割り込むかを選ぶので $n - 1$ 通りになる。係数を取り違えると $n = 4$、$k = 2$ で 11 と 7 が入れ替わるので、この値で確かめるとよい。

## 学ぶための資料 {#resources}

- [ikatakos「AtCoder Beginner Contest 247 E,G,Ex問題メモ」](https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2022/0410_abc247)の Ex の節：swap の最小回数を巡回の個数に直し、第 1 種スターリング数の行を色ごとに畳み込む流れが、表を使って丁寧に書かれている。
- [Nyaan「Nyaan's Library: 有名な数列（fps/fps-famous-series.hpp）」](https://nyaannyaan.github.io/library/fps/fps-famous-series.hpp)：1 行を Taylor shift の倍化で、列 $c(n, K)$ を FPS の累乗で求める実装。自作するときの関数の分け方の参考になる。
- Library Checker の 3 問（[練習問題の節](#practice)の一覧）：自作した関数の確かめに使う。問題文の定義は符号付きである。

## 例題 {#examples}

### ABC385 G. Counting Buildings {#abc385_g}

<div class="kp-problems" data-role="example" markdown>

- [ABC385 G. Counting Buildings](https://atcoder.jp/contests/abc385/tasks/abc385_g)（diff 2492）：N 個の建物の高さの順列のうち、左から見える建物の数と右から見える建物の数の差がちょうど K になるものの数を求める。

</div>

方針：値を大きい順に挿入すると、各値は「先頭に入れて左から見える」「末尾に入れて右から見える」「それ以外で見えない」の 3 通りに分かれる（[左から見える位置の節](#records)）。差だけを追えばよいので、左を $y$、右を $y^{-1}$ で表すと、答えは最大の値を除いた積 $\prod_{i=1}^{N-1} (y + y^{-1} + i - 1)$ の $y^K$ の係数になる。

??? note "解法の詳細"
    - **上昇階乗に直す**：$z = y + y^{-1}$ とおくと、積は $z(z+1)\cdots(z+N-2)$ で、$N - 1$ 次の上昇階乗である。したがって $\sum_{j} c(N-1, j) \, z^j$ と展開できる。
    - **$z^j$ の $y^K$ の係数**：$(y + y^{-1})^j$ で $y$ を $a$ 個、$y^{-1}$ を $j - a$ 個選ぶと指数は $2a - j$ になる。$y^K$ の係数は、$j - K$ が 0 以上の偶数のとき $\binom{j}{(j+K)/2}$、そうでなければ 0 である。
    - **答え**：$\sum_{j} c(N-1, j) \binom{j}{(j+K)/2}$（$j \equiv K \pmod 2$、$\lvert K \rvert \le j \le N - 1$）。左右を反転すると差の符号が変わるだけなので、$K$ は絶対値にしてよい。
    - **計算量**：$c(N-1, \cdot)$ の 1 行を分割統治の積で $O(N \log^2 N)$、残りの和は階乗の表で $O(N)$ である。$y + y^{-1} + i - 1$ のまま（$y$ の指数をずらして）分割統治で掛けても同じ計算量で解ける。参考の記事はどちらもこの形で解いている。

    ```cpp
    --8<-- "stirling-first/buildings.cpp:core"
    ```

    元のプログラムは、$N \le 7$ のすべての $K$ で順列の全列挙と一致することを確かめている。

## 練習問題 {#practice}

<div class="kp-problems" data-role="practice" markdown>

- [ABC247 Ex. Rearranging Problem](https://atcoder.jp/contests/abc247/tasks/abc247_h)（diff 2664）：N 人の服の色の列が与えられ、2 人を選んで位置を入れ替える操作をちょうど K 回行った後の人の並びのうち、服の色の列が初めと同じになるものの数を求める。

</div>

??? note "練習の方針"
    - **ABC247 Ex**：同じ並びを作る最小の swap 回数を $m$ とすると、$m \le K$ かつ $m \equiv K \pmod 2$ の並びはちょうど $K$ 回でも作れる（同じ 2 人を 2 回入れ替えて回数を稼ぐ）。swap 1 回で置換の偶奇が変わるので、偶奇の違う回数では作れない。最小回数を考えるなら同じ色どうしだけを入れ替えればよい。色ごとの人数を $a_1, a_2, \dots$ とすると、最小回数ごとの並びの数は、各色の $\sum_k c(a_i, k) \, x^{a_i - k}$ の積になる。各色の行を上昇階乗で求め、色をまたいで畳み込む。

### Library Checker

どれも符号付きの $s(n, k)$ で答える。

- [Stirling Number of the First Kind](https://judge.yosupo.jp/problem/stirling_number_of_the_first_kind)：1 行 $s(N, 0), \dots, s(N, N)$（$N \le 5 \times 10^5$）。分割統治か倍化の確認。
- [Stirling Number of the First Kind (Fixed K)](https://judge.yosupo.jp/problem/stirling_number_of_the_first_kind_fixed_k)：列 $s(n, K)$（$K \le n \le N$）。FPS の累乗の確認。
- [Stirling Number of the First Kind (Small p, Large n)](https://judge.yosupo.jp/problem/stirling_number_of_the_first_kind_small_p_large_n)：小さい素数 $p$ と巨大な $n$ での値。周期性を使う発展の話題なので、資料に任せる。

## 参考 {#references}

- [kmjp「AtCoder ABC #385 (ユニークビジョンプログラミングコンテスト2024 クリスマス) : G - Counting Buildings」](https://kmjp.hatenablog.jp/entry/2024/12/21/0930)：例題の、値を大きい順に挿入して 3 通りに分ける見方と、多項式の積で数える方針
- [ikatakos「ユニークビジョンプログラミングコンテスト2024 クリスマス（AtCoder Beginner Contest 385）E,F,G問題メモ」](https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2024/1221_abc385)：例題の方針（解法の節だけを読んだ）。差だけを状態にまとめ、$(y^{-1} + i + y)$ の積を小さい方から畳み込む
- [kmjp「AtCoder ABC #247 : Ex - Rearranging Problem」](https://kmjp.hatenablog.jp/entry/2022/04/10/1100)：練習の方針。最小の swap 回数を巡回の個数に直し、上昇階乗を NTT で展開する
- [ikatakos「AtCoder Beginner Contest 247 E,G,Ex問題メモ」](https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2022/0410_abc247)：練習の方針と学ぶための資料（解法の節だけを読んだ）。回数の偶奇と、色ごとの行の畳み込み
- [Nyaan「Nyaan's Library: 有名な数列（fps/fps-famous-series.hpp）」](https://nyaannyaan.github.io/library/fps/fps-famous-series.hpp)：学ぶための資料。Taylor shift の倍化と、列 $c(n, K)$ を FPS の累乗で求める実装
- [yosupo「Library Checker の問題（enumerative_combinatorics）」](https://github.com/yosupo06/library-checker-problems/tree/master/enumerative_combinatorics)：3 問の定義（符号付き）と制約
- [AtCoder「AC Library のドキュメント（document_ja）」](https://github.com/atcoder/ac-library/tree/master/document_ja)：ACL の囲みの convolution の宣言・計算量・要件
