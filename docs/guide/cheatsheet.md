---
id: cheatsheet
title: 早見表
aliases: [チートシート, 一覧表, 1 秒で回る回数, 数の目安, 公式集]
type: guide
field: guide
chapter: 早見表と資料
order: 130
level: null
kind: [案内]
prerequisites: []
related: [reverse-index-constraints, notation, glossary, cpp-integer-overflow, cpp-types-literals#inf, cpp-environment#version-matrix, stl-containers, acl-reading, mod-arithmetic, bit-operations, twelvefold-way]
summary: コンテスト中や解説を読むときに、計算量と制約、型の範囲、数の目安、STL と ACL の計算量、mod の性質、よく使う公式、bit 演算の小技をすぐ引ける。各行から詳しいページへつなぐ。
complexity: null
signs: []
acl: []
sections:
  - {title: 計算量と制約, anchor: complexity-and-constraints}
  - {title: 型の範囲とオーバーフローの境目, anchor: type-limits}
  - {title: 数の目安, anchor: magnitudes}
  - {title: STL の計算量, anchor: stl}
  - {title: ACL の機能と計算量, anchor: acl}
  - {title: mod の性質, anchor: mod}
  - {title: よく使う公式, anchor: formulas}
  - {title: bit 演算の小技, anchor: bit-tricks}
  - {title: C++ の版と GCC・INF の候補, anchor: cpp}
stage: reviewed
updated: 2026-10-22
---

!!! abstract "要点"
    - **何のページか**：コンテスト中や解説を読むときに、計算量と制約、型の範囲、数の目安、STL と ACL の計算量、mod の性質、よく使う公式、bit 演算の小技をすぐ引ける。各行から詳しいページへつなぐ。
    - **使い方**：節の名前で表を探し、値を確かめる。理由や使い方が要るときは、行の右端のリンクから手法のページへ進む。
    - **数値の出どころ**：型の範囲と数の目安は手元のプログラムで計算した。ACL の計算量は ACL v1.6 のドキュメントによる。

<!-- textlint-disable -->
別名：チートシート・一覧表・1 秒で回る回数・数の目安・公式集
<!-- textlint-enable -->

早見表は、手法の中身ではなく「数と式」を 1 か所に集めた表である。どの行も、理由と使い方は各ページに任せ、ここには値と行き先だけを書く。制約から手法を探すときは[逆引き辞典（制約・計算量から）](../guide/reverse-index-constraints.md)、語の意味は[用語集](../guide/glossary.md)、記号の読み方は[記法と用語の約束](../start/notation.md)を引く。

## 計算量と制約 {#complexity-and-constraints}

C++ の単純な処理なら、1 秒に $10^8$ 回はまず間に合い、数×$10^8$ 回は中身次第である。制約の最大値を計算量の式に入れ、この範囲に収まる式を探す。見積もりの手順・ならし計算量・定数倍は[計算量の見積もり](../basics/complexity-estimation.md#how-to-estimate)にある。

| 制約の目安 | 許される計算量 | 疑う手法 |
| --- | --- | --- |
| $N \le 8$〜$10$ | $O(N! \cdot N)$ | [順列全探索](../basics/bit-full-search.md#permutations) |
| $N \le 15$〜$20$ | $O(2^N N)$、$O(3^N)$（$3^N$ は $N \le 15$〜$16$ 程度まで） | bit 全探索・[bitDP](../dp/bit-dp.md#complexity)・[部分集合の列挙](../basics/bit-operations.md#submask) |
| $N \le 40$ | $O(2^{N/2} N)$ | [半分全列挙](../basics/meet-in-the-middle.md) |
| $N \le 100$〜$500$ | $O(N^3)$ | [区間 DP](../dp/interval-dp.md)・[ワーシャルフロイド法](../graph/warshall-floyd.md) |
| $N \le 2000$〜$5000$ | $O(N^2)$ | 2 次元の DP・[LCS](../dp/lcs.md) |
| $N \le 2 \times 10^5$ | $O(N \log N)$、$O(N \log^2 N)$、$O(N \sqrt{N})$ | ソート・[セグメント木](../ds/segment-tree.md)・[Mo's algorithm](../ds/mo-algorithm.md) |
| $N \le 10^6$〜$10^7$ | $O(N)$、$O(N \log \log N)$ | [累積和](../basics/prefix-sum.md)・[エラトステネスの篩](../math/sieve-eratosthenes.md#complexity) |
| $N \le 10^{12}$ | $O(\sqrt{N})$ | [約数列挙と素数判定](../math/divisor-enum.md#why-sqrt)・[商の列挙](../math/floor-quotient-enum.md) |
| $N \le 10^{18}$ | $O(\log N)$ | [二分探索](../basics/binary-search.md)・[ダブリング](../basics/doubling.md)・[繰り返し二乗法](../math/mod-pow.md) |

表の境目は目安で、詳しい表と手法の一覧は[制約 → 許される計算量 → 疑う手法の表](../basics/complexity-estimation.md#constraint-table)にある。制約が複数あれば、それぞれの最大値を同時に入れる（$N, Q \le 2 \times 10^5$ でクエリごとに $O(N)$ なら $4 \times 10^{10}$ 回）。複数テストケースは $N$ の総和で見積もる（[複数テストケース](../basics/complexity-estimation.md#multiple-testcases)）。

$N = 2 \times 10^5$ のときの回数は次のとおりである（手元で計算した値）。

| 計算量 | 回数 |
| --- | --- |
| $O(N \log N)$ | 約 $3.5 \times 10^6$ |
| $O(N \log^2 N)$ | 約 $6.2 \times 10^7$ |
| $O(N \sqrt{N})$ | 約 $8.9 \times 10^7$ |
| $O(N^2)$ | $4 \times 10^{10}$（間に合わない） |

**代表的な手法の計算量**。頂点数を $N$、辺数を $M$ とする。条件の詳しい説明は各ページにある。

| 手法 | 計算量 | ページ |
| --- | --- | --- |
| ソート | $O(N \log N)$ | [ソートで考える](../basics/sorting-techniques.md) |
| DFS・BFS・トポロジカルソート・SCC | $O(N + M)$ | [BFS](../graph/bfs.md)・[SCC](../graph/scc.md) |
| ダイクストラ法（二分ヒープ） | $O((N + M) \log N)$ | [ダイクストラ法](../graph/dijkstra.md) |
| ベルマンフォード法 | $O(NM)$ | [ベルマンフォード法](../graph/bellman-ford.md) |
| ワーシャルフロイド法 | $O(N^3)$ | [ワーシャルフロイド法](../graph/warshall-floyd.md) |
| クラスカル法 | $O(M \log M)$ | [最小全域木](../graph/minimum-spanning-tree.md#kruskal-prim) |
| Union-Find（経路圧縮と大きさの併合） | 1 回 ならし $O(\alpha(N))$ | [Union-Find](../ds/union-find.md#complexity) |
| BIT・セグメント木の 1 回の操作 | $O(\log N)$ | [セグメント木](../ds/segment-tree.md#complexity) |
| LIS | $O(N \log N)$ | [最長増加部分列](../dp/lis.md#binary-search) |
| 巡回セールスマンの bitDP | $O(2^N N^2)$ | [bitDP](../dp/bit-dp.md#tsp) |
| 部分集合の部分集合の列挙 | $O(3^N)$ | [部分集合を列挙する DP](../dp/subset-enumeration-dp.md#why-3n) |
| 高速ゼータ変換 | $O(2^N N)$ | [部分集合の高速ゼータ変換](../comb/zeta-mobius-subset.md) |
| 試し割り | $O(\sqrt{N})$ | [約数列挙と素数判定](../math/divisor-enum.md#primality) |
| 倍数の列挙（調和級数） | $O(N \log N)$ | [調和級数と倍数の列挙](../math/harmonic-sum.md#why-n-log-n) |
| ユークリッドの互除法 | $O(\log \min(a, b))$ | [GCD・LCM](../math/gcd-lcm.md#euclid) |
| 行列累乗（$K \times K$ を $T$ 乗） | $O(K^3 \log T)$ | [行列累乗](../math/matrix-power.md) |
| 畳み込み（NTT） | $O(N \log N)$ | [畳み込みの使い方](../math/convolution-ntt.md) |
| Mo's algorithm | $O(N \sqrt{Q})$ 回の伸縮 | [Mo's algorithm](../ds/mo-algorithm.md#ordering) |
| Z-algorithm・KMP 法 | $O(N)$ | [Z-algorithm](../string/z-algorithm.md)・[KMP 法](../string/kmp.md) |

**値や式の形から手法を選ぶ**。制約の大きさだけでは決まらない、よく見る形を並べる。

| 形 | 手法 | ページ |
| --- | --- | --- |
| 操作を $K \le 10^{18}$ 回繰り返した後の位置 | ダブリング。始点がすべてで $K$ が 1 つなら、写像の繰り返し二乗法で $O(N)$ のメモリで済む | [段数とメモリの見積もり](../basics/doubling.md#memory) |
| 2 つの列の値の和・差の分布（値の範囲 $10^6$ 程度まで） | 畳み込み | [i + j = k の形に言い換える](../math/convolution-ntt.md#sum-pairs) |
| 添字の XOR で組み合わせる | アダマール変換 | [XOR 畳み込み](../math/hadamard-transform.md#index-operations) |
| 添字の OR・AND で組み合わせる | 部分集合のゼータ変換 | [OR 畳み込み・AND 畳み込み](../comb/zeta-mobius-subset.md#or-and-convolution) |
| 値の上限が $10^9$ で個数が $2 \times 10^5$ | 座標圧縮 | [座標圧縮](../basics/coordinate-compression.md) |

## 型の範囲とオーバーフローの境目 {#type-limits}

整数の型の上限と、浮動小数点数が整数を正確に表せる範囲である。値は AtCoder と手元の x86-64 の GCC のもので、`int` は 32 bit、`long long` は 64 bit である。

| 型 | 上限 | 目安 | ページ |
| --- | --- | --- | --- |
| `int` | $2^{31} - 1 = 2147483647$ | 約 $2.1 \times 10^9$ | [整数の型](../cpp/cpp-types-literals.md#integer-types) |
| `long long` | $2^{63} - 1$ | 約 $9.22 \times 10^{18}$ | [整数の型](../cpp/cpp-types-literals.md#integer-types) |
| `unsigned long long` | $2^{64} - 1$ | 約 $1.8 \times 10^{19}$ | [整数の型](../cpp/cpp-types-literals.md#integer-types) |
| `__int128` | $2^{127} - 1$ | 約 $1.7 \times 10^{38}$ | [__int128](../cpp/cpp-integer-overflow.md#int128) |
| `double`（仮数部 53 bit） | 整数が正確なのは $2^{53}$ まで | 約 $9.0 \times 10^{15}$、10 進で約 15〜16 桁 | [浮動小数点数の型](../cpp/cpp-types-literals.md#floating-point) |
| `long double`（仮数部 64 bit） | 整数が正確なのは $2^{64}$ まで | 10 進で約 18〜19 桁 | [浮動小数点数の型](../cpp/cpp-types-literals.md#floating-point) |

**オーバーフローの境目**。次の値は手元で計算して確かめた。左の列の値は型に収まり、その次の値で上限を超える。

| 量 | `int` に収まる最大 | `long long` に収まる最大 |
| --- | --- | --- |
| 階乗 $n!$ | $12! = 479001600$（$13!$ で超える） | $20! \approx 2.4 \times 10^{18}$（$21!$ で超える） |
| 中央の二項係数 $\binom{n}{\lfloor n/2 \rfloor}$ | $\binom{33}{16} \approx 1.2 \times 10^9$（$\binom{34}{17}$ で超える） | $\binom{66}{33} \approx 7.2 \times 10^{18}$（$\binom{67}{33}$ で超える） |
| フィボナッチ数 $F_n$（$F_1 = F_2 = 1$） | $F_{46} = 1836311903$（$F_{47}$ で超える） | $F_{92} \approx 7.5 \times 10^{18}$（$F_{93}$ で超える） |
| $2^k$ | $2^{30}$（$2^{31}$ で超える） | $2^{62}$（$2^{63}$ で超える） |

ほかに、型の境目で起きやすいものを並べる。

- **積**：$10^9$ 程度の `int` どうしの積は、`long long` の変数に入れても `int` のまま計算されてあふれる。片方を `1LL *` で広げてから掛ける（[int どうしの積](../cpp/cpp-integer-overflow.md#int-product)）
- **mod の積**：法 $998244353$ 未満の 2 数の積は約 $9.96 \times 10^{17}$ で `long long` に収まる。法が $10^{12}$ 程度なら積は $10^{24}$ になり `__int128` が要る（[掛け算のあふれ](../math/mod-arithmetic.md#overflow)）
- **外積**：座標の絶対値が $10^9$ 以下なら、外積は各積の上界から $8 \times 10^{18}$ 以下と見積もれ、`long long` にぎりぎり収まる。3 点が正方形の中にあるときの実際の最大は $4 \times 10^{18}$ である。外積どうしを掛けるとあふれる（[オーバーフローの見積もり](../geometry/geometry-vectors.md#overflow)）
- **型の端の値**：`abs(INT_MIN)` と `INT_MIN / -1` は未定義動作である（[INF + INF・abs(INT_MIN)・INT_MIN / -1](../cpp/cpp-integer-overflow.md#edge-values)）
- **シフト幅**：シフト幅が型の bit 数以上なら、どの版でも未定義動作である（[シフト幅](../cpp/cpp-integer-overflow.md#shift-width)）

## 数の目安 {#magnitudes}

全探索の候補の数や、表の大きさを見積もるときの値である。どれも手元のプログラムで計算した（素数の個数は $10^9$ までの篩で数えた）。

**2 と 3 の累乗**

| 式 | 値 |
| --- | --- |
| $2^{10}$・$2^{16}$・$2^{20}$ | $1024$・$65536$・$1048576 \approx 1.05 \times 10^6$ |
| $2^{30}$・$2^{31}$・$2^{32}$ | 約 $1.07 \times 10^9$・約 $2.15 \times 10^9$・約 $4.29 \times 10^9$ |
| $2^{60}$・$2^{62}$ | 約 $1.15 \times 10^{18}$・約 $4.61 \times 10^{18}$ |
| $3^{13}$・$3^{15}$・$3^{16}$ | $1594323$・$14348907 \approx 1.4 \times 10^7$・約 $4.3 \times 10^7$ |
| $3^{18}$・$3^{20}$ | 約 $3.9 \times 10^8$・約 $3.5 \times 10^9$ |

$3^N$ は部分集合の部分集合の列挙の回数で、$N = 16$ 程度までなら軽い（[部分集合の部分集合の列挙](../basics/bit-operations.md#submask)）。

**$\log_2$ の値**

| $N$ | $\log_2 N$ |
| --- | --- |
| $2 \times 10^5$ | 約 17.6 |
| $10^6$ | 約 19.9 |
| $10^9$ | 約 29.9 |
| $10^{18}$ | 約 59.8 |

二分探索やダブリングの段数は、$\log_2$ の値を切り上げたものになる。$10^{18}$ までなら 60 段で足りる。

**階乗・ベル数・二項係数**（順列・組分け・組合せの数）

| 量 | 値 | ページ |
| --- | --- | --- |
| $8!$・$10!$・$12!$ | $40320$・$3628800$・$479001600$ | [順列全探索](../basics/bit-full-search.md#permutations) |
| ベル数 $B_{10}$・$B_{12}$・$B_{13}$ | $115975$・$4213597$・$27644437$ | [ベル数の大きさ](../comb/bell-number.md#size) |
| $\binom{30}{15}$・$\binom{40}{20}$ | 約 $1.6 \times 10^8$・約 $1.4 \times 10^{11}$ | [二項係数](../comb/binomial-coefficient.md) |
| $\binom{100}{5}$ | $75287520$ | [候補の数で見積もる](../basics/complexity-estimation.md#count-candidates) |

**約数・素数**

| 量 | 値 | ページ |
| --- | --- | --- |
| 約数の個数の最大 | $10^6$ 以下で 240、$10^9$ 以下で 1344、$10^{12}$ 以下で 6720、$10^{18}$ 以下で 103680 | [約数の個数の上界](../math/divisor-count-bound.md#table) |
| 異なる素因数の個数の最大 | $10^9$ 以下で 9 個、$10^{18}$ 以下で 15 個 | [約数の個数の上界](../math/divisor-count-bound.md#table) |
| 素数の個数 $\pi(N)$ | $\pi(10^5) = 9592$、$\pi(2 \times 10^5) = 17984$、$\pi(10^6) = 78498$ | [エラトステネスの篩](../math/sieve-eratosthenes.md) |
| 素数の個数 $\pi(N)$（大きい $N$） | $\pi(10^7) = 664579$、$\pi(10^8) = 5761455$、$\pi(10^9) = 50847534$ | [エラトステネスの篩](../math/sieve-eratosthenes.md#memory) |
| 隣り合う素数の差の最大 | $10^9$ 以下で始まるもので 282 | [素数判定](../math/divisor-enum.md#primality) |
| $\lfloor N/i \rfloor$ の異なる値の個数 | $N = 10^6$ で 1999、$N = 10^{12}$ で 1999999（約 $2\sqrt{N}$） | [商の列挙](../math/floor-quotient-enum.md#why-sqrt) |
| 互除法の割り算の回数の最大 | $10^9$ 以下で 42、$10^{18}$ 以下で 85 | [GCD・LCM](../math/gcd-lcm.md#euclid) |
| 倍数の列挙の回数 $\sum_{d=1}^{M} \lfloor M/d \rfloor$ | 約 $M \ln M$。$M = 10^6$ で約 $1.4 \times 10^7$ | [調和級数と倍数の列挙](../math/harmonic-sum.md#why-n-log-n) |

**カタラン数・分割数**

| 量 | 値 | ページ |
| --- | --- | --- |
| カタラン数 $C_n$ | $C_{10} = 16796$、$C_{15} = 9694845$、$C_{20} = 6564120420$ | [カタラン数](../comb/reflection-principle.md#catalan) |
| 分割数 $p(n)$ | $p(10) = 42$、$p(30) = 5604$、$p(50) = 204226$、$p(100) = 190569292$ | [整数の分割と分割数](../comb/partition-number.md#size) |

**メモリ**

ABC の多くはメモリ制限が 1024 MiB である。1024 MiB に入る個数は、`int` で $268435456 \approx 2.7 \times 10^8$ 個、`long long` で $134217728 \approx 1.3 \times 10^8$ 個である。$5000 \times 5000$ の `long long` の表は約 191 MiB で入る。$2 \times 10^5 \times 2 \times 10^5$ の表は入らない（[見積もりの手順](../basics/complexity-estimation.md#how-to-estimate)）。

## STL の計算量 {#stl}

コンテナの操作の計算量の表は [STL コンテナの使い分け](../ds/stl-containers.md#complexity-table)にある。ここでは要点と、見た目と違って遅い・思わぬ振る舞いをする書き方を並べる。$N$ は要素数である。

| コンテナ | 速い操作 | 遅い操作 |
| --- | --- | --- |
| `vector` | 添字 $O(1)$、末尾の追加 ならし $O(1)$ | 途中への挿入・削除 $O(N)$ |
| `deque` | 添字 $O(1)$、両端の追加・削除 $O(1)$ | 途中への挿入・削除 $O(N)$ |
| `priority_queue` | 追加・取り出し $O(\log N)$、先頭を見る $O(1)$ | 任意の要素の削除（操作がない） |
| `set`・`map` | 追加・削除・検索・`lower_bound` $O(\log N)$ | K 番目の取得（操作がなく、`next` で進めると $O(N)$） |
| `unordered_set`・`unordered_map` | 追加・削除・検索 平均 $O(1)$ | 最悪 $O(N)$、順序がない |

**見た目と違う書き方**

| 書き方 | 計算量・振る舞い | ページ |
| --- | --- | --- |
| set に `lower_bound(st.begin(), st.end(), x)` | $O(N)$（メンバの `st.lower_bound(x)` なら $O(\log N)$） | [lower_bound はメンバ関数](../cpp/cpp-container-idioms.md#member-lower-bound) |
| set で `distance(st.begin(), it)` | $O(N)$ | [distance は set では O(N)](../cpp/cpp-container-idioms.md#iterator-index) |
| `multiset` の `erase(x)` | $x$ をすべて消す。1 個だけなら `erase(find(x))` | [multiset から 1 個だけ消す](../cpp/cpp-container-idioms.md#multiset-erase-one) |
| `s.substr(i, len)` | $O(len)$ のコピー | [substr と find](../cpp/cpp-string-api.md#substr-find) |
| `s = s + c` | $O(\lvert S \rvert)$（`s += c` なら ならし $O(1)$） | [文字の追加](../cpp/cpp-string-api.md#append) |
| `map` の `m[k]` で存在を調べる | キーがなければ要素を作る | [map の添字演算子](../cpp/cpp-container-idioms.md#map-subscript) |
| `endl` で改行する | 改行のたびに書き出す | [endl と改行文字](../cpp/cpp-io.md#endl) |

**アルゴリズム関数**

| 関数 | 計算量 | ページ |
| --- | --- | --- |
| `sort` | $O(N \log N)$ | [sort と降順](../cpp/cpp-algorithms.md#sort) |
| `lower_bound`・`upper_bound`（ソート済みの配列） | $O(\log N)$ | [二分探索の関数](../cpp/cpp-algorithms.md#lower-bound) |
| `unique`（ソートの後） | $O(N)$ | [重複の削除](../cpp/cpp-algorithms.md#unique-erase) |
| `next_permutation` で全順列 | 全体で $O(N! \cdot N)$ | [next_permutation](../cpp/cpp-algorithms.md#next-permutation) |

`lower_bound` は $x$ 以上の最初、`upper_bound` は $x$ より大きい最初の位置を返す。

## ACL の機能と計算量 {#acl}

ACL v1.6 のドキュメントに書かれた計算量である。$n$ は要素数や頂点数、$m$ は辺数である。呼び出し方は [ACL の読み方](../cpp/acl-reading.md#components)にある。

| 機能 | 計算量 | ページ |
| --- | --- | --- |
| `dsu`：`merge`・`same`・`leader`・`size` | ならし $O(\alpha(n))$ | [Union-Find](../ds/union-find.md) |
| `fenwick_tree`：`add`・`sum` | $O(\log n)$ | [BIT](../ds/fenwick-tree.md) |
| `segtree`：`set`・`prod`・`max_right`・`min_left` | $O(\log n)$（`get`・`all_prod` は $O(1)$） | [セグメント木](../ds/segment-tree.md) |
| `lazy_segtree`：`apply`・`prod` | $O(\log n)$ | [遅延セグメント木](../ds/lazy-segment-tree.md) |
| `scc_graph`・`two_sat` | $O(n + m)$ | [SCC](../graph/scc.md)・[2-SAT](../graph/two-sat.md) |
| `mf_graph`：`flow` | $O(n^2 m)$。容量がすべて 1 なら $O((n + m) \sqrt{m})$ | [最大流](../graph/max-flow.md#acl) |
| `mcf_graph`：`flow` | 流量 $F$ に対して $O(F (n + m) \log (n + m))$ | [最小費用流](../graph/min-cost-flow.md#acl) |
| `convolution` | $O(n \log n + \log \mathrm{mod})$ | [畳み込みの使い方](../math/convolution-ntt.md#acl) |
| `suffix_array`（文字列）・`lcp_array`・`z_algorithm` | $O(n)$ | [Suffix Array](../string/suffix-array.md)・[Z-algorithm](../string/z-algorithm.md) |
| `pow_mod`・`inv_mod`・`floor_sum` | $O(\log n)$・$O(\log m)$・$O(\log m)$ | [繰り返し二乗法](../math/mod-pow.md#acl)・[floor sum](../math/floor-sum.md) |
| `crt` | $O(n \log \operatorname{lcm})$ | [中国剰余定理](../math/crt.md#acl) |
| `modint`：四則 | $O(1)$（割り算と `inv` は $O(\log \mathrm{mod})$） | [modint](../math/modint.md) |

`mf_graph` の `flow` は、流した量を $F$ として $O(F (n + m))$ とも書かれている。`segtree`・`lazy_segtree` の計算量は、渡した演算が定数時間で動くと仮定した値である。

## mod の性質 {#mod}

法 $m$ で余りを取る計算の要点である。理由は各ページにある。

| 性質 | 式・値 | ページ |
| --- | --- | --- |
| 途中で余りを取ってよい | 足し算・引き算・掛け算は、各段で余りを取っても結果の余りは同じ | [途中で余りを取ってよい理由](../math/mod-arithmetic.md#why-mod) |
| 負の数の余り | C++ の `%` は、割られる数が負なら 0 か負の値を返す。`(a % m + m) % m` で 0 以上にする | [負の数を 0 以上に直す](../math/mod-arithmetic.md#negative) |
| 割り算 | 逆元を掛ける。逆元は $\gcd(a, m) = 1$ のときだけある | [逆元が存在する条件](../math/mod-inverse.md#existence) |
| 法が素数 $p$ の逆元 | $a^{-1} \equiv a^{p-2} \pmod{p}$（フェルマーの小定理） | [フェルマーの小定理による逆元](../math/mod-inverse.md#fermat) |
| 指数の余り | $p \nmid a$ なら $a^{n} \equiv a^{n \bmod (p-1)} \pmod{p}$ | [指数の計算は mod (p − 1)](../math/exponent-mod.md#exponent-mod-p-1) |
| 大小比較 | 余りを取った値で大小比較・最大値を考えてはいけない | [大小比較をしない](../math/mod-arithmetic.md#no-compare) |
| 二項係数 | 階乗とその逆元を前計算すれば、1 回 $O(1)$ | [二項係数の前計算](../comb/binomial-precompute.md#fact-ifact) |
| 法が小さい素数で $n \ge p$ | 階乗が 0 になり割れない。Lucas の定理を使う | [Lucas の定理](../comb/binomial-precompute.md#lucas) |

**よく使う法の値**（手元で計算して確かめた）

- $998244353 = 119 \times 2^{23} + 1$ は素数で、原始根は 3。長さ $2^{23}$ までの NTT に使える（[なぜ 998244353 か](../math/mod-arithmetic.md#why-998244353)）
- $10^9 + 7$ も素数だが、$p - 1 = 2 \times 500000003$ なので NTT には向かない
- $2^{-1} \equiv 499122177 \pmod{998244353}$
- どちらの法も $2^{30}$ 未満なので、余りどうしの和は `int` に、積は `long long` に収まる

## よく使う公式 {#formulas}

式だけを並べる。導き方と使い方は右端のページにある。

**和**

| 式 | 値 | ページ |
| --- | --- | --- |
| $\sum_{i=1}^{N} i$ | $\frac{N(N+1)}{2}$ | [よく使う和の公式](../math/sigma-manipulation.md#formulas) |
| $\sum_{i=1}^{N} i^2$ | $\frac{N(N+1)(2N+1)}{6}$ | [よく使う和の公式](../math/sigma-manipulation.md#formulas) |
| $\sum_{i=0}^{N-1} r^i$（$r \ne 1$） | $\frac{r^N - 1}{r - 1}$ | [等比数列の和を mod で求める](../math/geometric-series-mod.md) |
| $\sum_{i < j} a_i a_j$ | $\frac{1}{2}\left(\left(\sum a_i\right)^2 - \sum a_i^2\right)$ | [よく使う和の公式](../math/sigma-manipulation.md#formulas) |
| $\sum_{d=1}^{M} \frac{M}{d}$ | $O(M \log M)$ | [調和級数と倍数の列挙](../math/harmonic-sum.md#why-n-log-n) |

**二項係数・数え上げ**

| 式 | 値 | ページ |
| --- | --- | --- |
| $\binom{n}{k}$ | $\frac{n!}{k!\,(n-k)!}$、$\binom{n}{k} = \binom{n-1}{k-1} + \binom{n-1}{k}$ | [パスカルの三角形](../comb/binomial-coefficient.md#pascal) |
| $\sum_{k} \binom{n}{k}$ | $2^n$ | [二項定理](../comb/binomial-identities.md#binomial-theorem) |
| $\sum_{i} \binom{a}{i} \binom{b}{k-i}$ | $\binom{a+b}{k}$ | [Vandermonde の恒等式](../comb/binomial-identities.md#vandermonde) |
| $\sum_{i=r}^{n} \binom{i}{r}$ | $\binom{n+1}{r+1}$ | [縦の和](../comb/binomial-identities.md#hockey-stick) |
| $x_1 + \dots + x_k = n$ の非負整数解 | $\binom{n+k-1}{k-1}$ | [玉と仕切りの対応](../comb/stars-and-bars.md#stars-bars) |
| カタラン数 $C_n$ | $\frac{1}{n+1}\binom{2n}{n}$ | [カタラン数](../comb/reflection-principle.md#catalan) |
| 玉と箱の区別と制限ごとの数 | 写像 12 相の表 | [写像 12 相](../comb/twelvefold-way.md#table) |

**整数**

| 式 | 値 | ページ |
| --- | --- | --- |
| $\gcd(a, b)$ | $\gcd(b, a \bmod b)$、$\gcd(a, 0) = a$ | [互除法](../math/gcd-lcm.md#euclid) |
| $\operatorname{lcm}(a, b)$ | $a / \gcd(a, b) \times b$（割ってから掛ける） | [lcm のオーバーフロー](../math/gcd-lcm.md#lcm-overflow) |
| 約数の個数（$n = \prod p_i^{e_i}$） | $\prod (e_i + 1)$ | [約数の個数と総和の公式](../math/divisor-enum.md#count-and-sum) |
| オイラーの φ 関数 | $\varphi(n) = n \prod_{p \mid n} \left(1 - \frac{1}{p}\right)$ | [定義と公式](../math/euler-phi.md#formula) |
| $n!$ に含まれる $p$ の指数 | $\sum_{k \ge 1} \lfloor n / p^k \rfloor$ | [ルジャンドルの公式](../math/prime-factorization.md#legendre) |
| 閉区間 $[L, R]$ の $K$ の倍数の個数（$L \ge 1$） | $\lfloor R/K \rfloor - \lfloor (L-1)/K \rfloor$ | [区間の中の K の倍数の個数](../math/integer-division.md#count-multiples) |
| 切り上げ $\lceil a/b \rceil$（$b > 0$） | $\lfloor (a + b - 1)/b \rfloor$。C++ の `/` で書くなら $a + b - 1 \ge 0$ なら正しい（負だと誤ることがある） | [切り上げの式が使える条件](../math/integer-division.md#ceil-formula) |

**グラフ・確率・ゲーム・幾何**

| 式 | 値 | ページ |
| --- | --- | --- |
| 次数の和 | $\sum_v \deg(v) = 2M$ | [握手補題](../graph/graph-basics.md#handshake) |
| 0 以上の整数値の確率変数の期待値 | $E[X] = \sum_{k \ge 1} P(X \ge k)$ | [期待値と確率の変換](../comb/expectation-tail-sum.md#identity) |
| 確率 $p$ で成功する試行の、成功までの回数の期待値 | $1/p$ | [幾何分布](../comb/coupon-collector.md#geometric) |
| Nim の勝敗 | 山の XOR が 0 でなければ先手必勝 | [Bouton の定理](../comb/nim.md#bouton) |
| ゲームの和の Grundy 数 | 各ゲームの Grundy 数の XOR | [ゲームの和は XOR](../comb/grundy-number.md#sum) |
| 外積・内積 | $\mathrm{cross}(a, b) = a_x b_y - a_y b_x$、$\mathrm{dot}(a, b) = a_x b_x + a_y b_y$ | [外積と内積の意味](../geometry/geometry-vectors.md#cross-and-dot) |
| 多角形の面積の 2 倍 | $\left\lvert \sum_{i} \mathrm{cross}(p_i, p_{i+1}) \right\rvert$ | [多角形の面積](../geometry/geometry-vectors.md#polygon-area) |
| マンハッタン距離 | $(x + y, x - y)$ に移すとチェビシェフ距離になる | [マンハッタン距離と 45 度回転](../geometry/manhattan-chebyshev.md) |

## bit 演算の小技 {#bit-tricks}

集合を整数で表すときの短い書き方である。$x$ は 0 以上の整数とする。

| 書き方 | 意味 | ページ |
| --- | --- | --- |
| `(1 << n) - 1` | $n$ 要素の全体集合 | [AND・OR・XOR・シフト](../basics/bit-operations.md#operators) |
| `x >> i & 1` | $x$ の bit $i$ が立っているか | [AND・OR・XOR・シフト](../basics/bit-operations.md#operators) |
| `x & -x` | 最下位の 1 だけを残した値 | [popcount・最下位 bit](../basics/bit-operations.md#popcount) |
| `x & (x - 1)` | 最下位の 1 を消した値。`== 0` なら $x$ は 0 か 2 のべき乗 | [popcount・最下位 bit](../basics/bit-operations.md#popcount) |
| `s = (s - 1) & m` | $m$ の部分集合を大きい順にたどる | [部分集合の部分集合の列挙](../basics/bit-operations.md#submask) |
| `__builtin_popcountll(x)` | 1 の個数（`long long` には `ll` 付きを使う） | [組み込み関数](../cpp/cpp-math-functions.md#builtins) |
| `a ^ b ^ b` | $a$（同じ値の XOR は打ち消し合う） | [XOR の性質](../basics/bit-operations.md#xor-properties) |
| `a + b` と XOR | $a + b = (a \oplus b) + 2(a \text{ AND } b)$ | [XOR の性質](../basics/bit-operations.md#xor-properties) |

演算子の優先順位に注意する。`x & 1 == 0` は `x & (1 == 0)` と読まれるので、`(x & 1) == 0` と括弧を付ける（[AND・OR・XOR・シフトと演算子の優先順位](../basics/bit-operations.md#operators)）。

**`<bit>` の関数の値と境界**（C++20。符号なし整数だけを受ける）

| 関数 | 意味 | `unsigned` で $x = 12$ | $x = 0$ |
| --- | --- | --- | --- |
| `popcount(x)` | 1 の個数 | 2 | 0 |
| `countr_zero(x)` | 下から続く 0 の個数 | 2 | 32 |
| `countl_zero(x)` | 上から続く 0 の個数 | 28 | 32 |
| `bit_width(x)` | 桁数 $\lfloor \log_2 x \rfloor + 1$ | 4 | 0 |
| `bit_ceil(x)`・`bit_floor(x)` | $x$ 以上の最小・以下の最大の 2 のべき乗 | 16・8 | 1・0 |

表の値は [bit ヘッダの関数](../cpp/cpp-math-functions.md#bit-functions)で確かめたものである。組み込み関数の `__builtin_ctz`・`__builtin_clz`・`__lg` は、0 を渡したときの結果が決まっていない。`<bit>` の関数は 0 でも値が決まっている（[組み込み関数](../cpp/cpp-math-functions.md#builtins)）。`int` を `std::popcount` に渡すとコンパイルエラーになる（[符号なし整数しか受けない](../cpp/cpp-math-functions.md#bit-unsigned-only)）。

## C++ の版と GCC・INF の候補 {#cpp}

AtCoder の C++ は GCC 15.2 で、`-std=gnu++23 -O2` でコンパイルされる。手元の古い GCC で解説のコードが通らないときは、次の表で機能の版を確かめる。AtCoder と手元の環境の違いは [AtCoder と手元の C++ 環境](../cpp/cpp-environment.md#options)にある。

| 機能 | 規格 | GCC | ページ |
| --- | --- | --- | --- |
| `<bit>`（`popcount` など）・`set`・`map` の `contains`・`erase_if` | C++20 | 9〜（`bit_width`・`bit_ceil`・`bit_floor` は 10〜） | [bit ヘッダの関数](../cpp/cpp-math-functions.md#bit-functions)・[contains](../cpp/cpp-container-idioms.md#contains) |
| `std::format` | C++20 | 13〜 | [format と println](../cpp/cpp-io.md#format-println) |
| `views::enumerate`・`zip`・`chunk` など | C++23 | 13〜 | [views::enumerate](../cpp/cpp-views-cpp23.md#enumerate) |
| `ranges::fold_left`・`ranges::contains`・static ラムダ | C++23 | 13〜 | [fold_left](../cpp/cpp-algorithms.md#fold-left)・[ジェネリックラムダ](../cpp/cpp-lambda.md#generic-lambda) |
| `std::print`・`println` | C++23 | 14〜 | [format と println](../cpp/cpp-io.md#format-println) |
| deducing this（`this auto&& self`） | C++23 | 14〜 | [deducing this](../cpp/cpp-lambda.md#deducing-this) |
| `ranges::to` | C++23 | 14〜 | [ranges::to](../cpp/cpp-views-cpp23.md#ranges-to) |
| 範囲 for の一時オブジェクトの寿命の延長 | C++23 | 15〜 | [範囲 for の一時オブジェクト](../cpp/cpp-undefined-behavior.md#dangling-temporary) |
| `from_range`・`insert_range`・`append_range` | C++23 | 15〜 | [from_range](../cpp/cpp-views-cpp23.md#from-range) |

C++26 の機能（`views::concat` など）は、AtCoder の `-std=gnu++23` では使えない。

**INF の候補**。INF に辺の重みや別の INF を足すことがあるので、INF + INF が型に収まる値を選ぶ。

| 書き方 | 値 | INF + INF |
| --- | --- | --- |
| `INT_MAX` | 約 $2.1 \times 10^9$ | あふれる |
| `0x3f3f3f3f` | $1061109567$ | `int` に収まる。`memset` で配列を埋められる |
| `1LL << 60` | 約 $1.15 \times 10^{18}$ | `long long` に収まる |
| `LLONG_MAX` | 約 $9.2 \times 10^{18}$ | あふれる |
| `1e18` | $10^{18}$（型は `double`） | `long long INF = 1e18;` と型を書けば収まる |

選び方と落とし穴は [INF の決め方](../cpp/cpp-types-literals.md#inf) にある。`auto INF = 1e18;` が `double` になる理由も [1e18 は double](../cpp/cpp-types-literals.md#double-1e18) で扱う。

**型をそろえる短い書き方**

| 書き方 | 意味 | ページ |
| --- | --- | --- |
| `max<long long>(a, b)` | 型の違う 2 つ（`int` と `long long` など）の大きい方 | [型を明示して呼ぶ](../cpp/cpp-templates-constexpr.md#explicit-type) |
| `min({a, 3LL, b})` | 3 個以上の最小。中身の型をそろえる | [型を明示して呼ぶ](../cpp/cpp-templates-constexpr.md#explicit-type) |
| `constexpr auto T = [] { … }();` | ラムダをその場で呼び、コンパイル時に表を作る | [constexpr の定数と関数](../cpp/cpp-templates-constexpr.md#constexpr) |
| `1LL * a * b` | `int` どうしの積を `long long` で計算する | [int どうしの積](../cpp/cpp-integer-overflow.md#int-product) |

## 参考 {#references}

- [drken「計算量オーダーの求め方を総整理！ 〜 どこから log が出て来るか 〜」](https://qiita.com/drken/items/872ebc3a2b5caaa4a0d0)：1 秒に $10^8$ 回という目安
- [drken「ビット演算 (bit 演算) の使い方を総特集！ 〜 マスクビットから bit DP まで 〜」](https://qiita.com/drken/items/7c6ff2aa4d8fce1c9361)：部分集合の列挙と最下位 bit の小技の一覧
- [cppreference「Fundamental types」](https://en.cppreference.com/cpp/language/types)：整数の型の幅と LP64 のデータモデル
- [AtCoder「AC Library のドキュメント（document_ja）」](https://github.com/atcoder/ac-library/tree/master/document_ja)：ACL の各機能の計算量
