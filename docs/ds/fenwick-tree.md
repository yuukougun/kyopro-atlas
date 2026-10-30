---
id: fenwick-tree
title: BIT（Fenwick Tree）
aliases: [Binary Indexed Tree, フェニック木, fenwick_tree]
tags: [フェニック]
search: {boost: 1.8}
type: technique
field: ds
chapter: 区間クエリ
order: 150
level: 水
kind: [データ構造, 区間クエリ]
prerequisites: [prefix-sum, bit-operations]
related: [segment-tree, inversion-number, kth-element, coordinate-compression, sweep-line-2d, offline-queries, imos, segment-tree-on-values]
summary: 一点への加算と接頭辞の和（したがって区間の和）を、どちらも O(log N) で行う。区間の和は 2 つの接頭辞の差なので演算に逆元が要り、値を添字にして個数を数える使い方が多い。
complexity: 構築 O(N)（全要素 0 から、または線形時間の構築）、一点加算・接頭辞の和・区間の和はどれも O(log N)（1 回ごとの上限）
signs:
  - {type: phrase, text: 一点の値の更新と区間の和の質問が交互に来る}
  - {type: phrase, text: i より前にある x 以下の要素の個数}
  - {type: shape, text: 'j < i の [A_j ≤ A_i] の和のように、前にある要素のうち条件を満たすものの個数・和を i ごとに足す'}
  - {type: constraint, text: 'N, Q ≤ 2×10^5 で更新があり、累積和を毎回作り直すと間に合わない'}
acl: [fenwick_tree]
verify: [point_add_range_sum, static_range_sum]
frequency: A
frequency_evidence: recent 2（abc452_f・abc467_g）・前提として 16 ページに届く（直接 6）・古い ABC 6 問
sections:
  - {title: 何ができるか（一点加算・接頭辞の和と逆元）, anchor: what-it-does}
  - {title: 保つ性質（添字 i は、i で終わる長さ lowbit(i) の区間の和を持つ）, anchor: invariants}
  - {title: 各操作の手順（add は上へ、sum は下へ。線形時間の構築）, anchor: operations}
  - {title: 境界（添字の変換・i = 0・符号なし整数）, anchor: boundaries}
  - {title: 値を添字にして数える（座標圧縮と組む）, anchor: count-by-value}
  - {title: 変種（差分の BIT・BIT 2 本・2 次元 BIT・接頭辞の max）, anchor: variants}
  - {title: BIT 上の二分探索, anchor: binary-search}
stage: done
updated: 2026-10-29
---

!!! abstract "要点"
    - **何ができるか**：一点への加算と接頭辞の和（したがって区間の和）を、どちらも $O(\log N)$ で行う。区間の和は 2 つの接頭辞の差なので演算に逆元が要り、値を添字にして個数を数える使い方が多い。
    - **いつ使うか**：
        - 一点の値の更新と区間の和の質問が交互に来る
        - $i$ より前にある $x$ 以下の要素の個数
        - $\sum_{j<i} [A_j \le A_i]$ のように、前にある要素のうち条件を満たすものの個数・和を $i$ ごとに足す
        - $N, Q \le 2 \times 10^5$ で更新があり、累積和を毎回作り直すと間に合わない
    - **計算量**：構築 $O(N)$（全要素 0 から作るか、初期値から線形時間で作る）。一点加算・接頭辞の和・区間の和はどれも $O(\log N)$（ならしではなく 1 回ごとの上限）。領域 $O(N)$
    - **前提**：[累積和](../basics/prefix-sum.md)、[bit 演算の基本と XOR の性質](../basics/bit-operations.md)

<!-- textlint-disable -->
別名：Binary Indexed Tree・フェニック木・fenwick_tree
<!-- textlint-enable -->

BIT（Fenwick Tree）は、長さ $N$ の列を「長さが 2 の冪の区間の和」の箱 $N$ 個に分けて持ち、一点の加算と接頭辞の和をどちらも $O(\log N)$ で行うデータ構造である。どの箱が何を持つかは添字の 2 進数の最下位の 1 だけで決まるので、配列 1 本と数行のループで書ける。

## 何ができるか（一点加算・接頭辞の和と逆元） {#what-it-does}

BIT は、長さ $N$ の列 $a_0, \dots, a_{N-1}$（0-indexed）に対して次の 2 つの操作を、どちらも $O(\log N)$ で行う。

- **一点加算**：$a_p \leftarrow a_p + x$
- **接頭辞の和**：$a_0 + a_1 + \dots + a_{r-1}$ を求める

区間 $[l, r)$ の和は「$r$ までの接頭辞の和 − $l$ までの接頭辞の和」で求める。[累積和](../basics/prefix-sum.md#half-open)と同じ引き算である。

[累積和](../basics/prefix-sum.md)は区間の和を $O(1)$ で答えるが、$a_p$ が 1 つ変わると $S_{p+1}, \dots, S_N$ がすべて変わり、作り直しに $O(N)$ かかる。$N, Q \le 2 \times 10^5$ で更新と質問が交互に来ると、合わせて $4 \times 10^{10}$ 回ほどになり間に合わない。逆に配列のまま持てば更新は $O(1)$ だが、質問が $O(N)$ になる。BIT はこの間を取り、どちらも $O(\log N)$ にする。

区間の和を引き算で出すので、演算には「足したものを取り消す」逆の操作が要る。

- **使える**：整数の和（逆は引き算）・XOR（自分自身が逆）・mod での和
- **そのままでは使えない**：min・max（$\min(a, b)$ から $b$ を取り除いて $a$ に戻せない）・mod での積（0 を掛けると戻せない）

区間の min・max や、結合法則だけを満たす一般の演算は[セグメント木](../ds/segment-tree.md)を使う。BIT で max を扱えるのは、値が増える更新と接頭辞の質問だけのときである（[変種](#variants)）。

## 保つ性質（添字 i は、i で終わる長さ lowbit(i) の区間の和を持つ） {#invariants}

BIT の中身は、1-indexed の配列 $t[1], \dots, t[N]$ である。この節と次の節では、列も 1-indexed で $a_1, \dots, a_N$ と書く。$\mathrm{lowbit}(i)$ を「$i$ の 2 進数で最下位の 1 だけを残した値」とする（C++ では `i & -i`。[popcount・最下位 bit](../basics/bit-operations.md#popcount)）。BIT は次の性質を保つ。

> $t[i] = a_{i - \mathrm{lowbit}(i) + 1} + \dots + a_i$、すなわち $t[i]$ は区間 $(i - \mathrm{lowbit}(i), i]$ の和である。

たとえば $12 = 1100_{(2)}$ は $\mathrm{lowbit}(12) = 4$ なので、$t[12] = a_9 + a_{10} + a_{11} + a_{12}$ である。奇数の $i$ は $\mathrm{lowbit}(i) = 1$ なので、$t[i] = a_i$ である。次の図は $N = 8$ のときの箱の並びで、横棒の位置と長さが各 $t[i]$ の受け持つ区間を表す。

![N = 8 の BIT の箱の並び。奇数の i は長さ 1、2 と 6 は長さ 2、4 は長さ 4、8 は長さ 8 の区間を受け持つ。sum(7) は t[7]・t[6]・t[4] を足し、add(3) は t[3]・t[4]・t[8] を直す](../img/fenwick-tree/boxes.svg)

図から読み取れることは 2 つある。

- **接頭辞は箱に重なりなく分かれる**：閉区間 $[1, 7]$ は $t[7]$（$a_7$）、$t[6]$（$a_5$〜$a_6$）、$t[4]$（$a_1$〜$a_4$）の 3 つにちょうど分かれる。$t[i]$ の左端の 1 つ手前が $i - \mathrm{lowbit}(i)$ なので、そこから同じことをくり返せば隙間なくつながる
- **1 つの位置を含む箱は各段に高々 1 つ**：$a_3$ を含む箱は $t[3]$・$t[4]$・$t[8]$ の 3 つだけである

次の動く図は、同じ $N = 8$ の箱に値を入れたものである。列 $a_1, \dots, a_8$ は 3・1・4・1・5・9・2・6 とした（図の a の行）。sum(7) と add(3, +2) を 1 箱ずつ進める。sum(7) は $t[7]$・$t[6]$・$t[4]$ を足して $2 + 14 + 9 = 25$ になり、add(3, +2) は $t[3]$・$t[4]$・$t[8]$ に 2 を足す。箱の並びの下に添字の 2 進数を書いてあるので、次の $i$ に移るとき最下位の 1 がどう変わるかも見られる（手順は[次の節](#operations)で述べる）。

<div class="kp-viz" data-viz="fenwick-tree" data-config='{"a": [3, 1, 4, 1, 5, 9, 2, 6], "ops": [{"type": "sum", "i": 7}, {"type": "add", "i": 3, "x": 2}]}'></div>

## 各操作の手順（add は上へ、sum は下へ。線形時間の構築） {#operations}

保つ性質から、2 つの操作の手順は次のようになる（1-indexed）。

```text
sum(i):                  # a_1 + … + a_i
    s ← 0
    while i > 0:
        s ← s + t[i]
        i ← i − lowbit(i)    # 箱の左端の 1 つ手前へ（最下位の 1 を消す）
    return s

add(i, x):               # a_i ← a_i + x
    while i ≤ N:
        t[i] ← t[i] + x
        i ← i + lowbit(i)    # i を含む次の（長い）箱へ
```

**sum が速い理由**：$i - \mathrm{lowbit}(i)$ は $i$ の最下位の 1 を消した値である。1 が 1 つずつ消えるので、ループは $i$ の 2 進数の 1 の個数（$\lfloor \log_2 N \rfloor + 1$ 以下）だけ回る。$i = 7 = 111_{(2)}$ なら $7 \to 6 \to 4 \to 0$ の 3 回である。

**add が正しく速い理由**：$a_i$ を含む箱を、短い順にちょうど 1 回ずつ通る。$i$ を含む長さ $2^k$ の箱は、あるなら $i$ の下の $k$ 桁を切り上げた位置（$i$ 以上で最小の $2^k$ の倍数）を右端に持つ。$i \leftarrow i + \mathrm{lowbit}(i)$ は、この切り上げを短い順に行う操作である。また $i + \mathrm{lowbit}(i)$ は最下位の 1 の桁で繰り上がりが起きるので、最下位の 1 の位置が真に上がる。よってループは高々 $\lfloor \log_2 N \rfloor + 1$ 回で終わる。$i = 3 = 011_{(2)}$ なら $3 \to 4 \to 8$ と進み、$N = 8$ を超えたら止まる。

??? note "証明：add が通る箱は、i を含む箱のすべてである"
    長さ $2^k$ の箱は、右端 $j$ が「$2^k$ の倍数で $2^{k+1}$ の倍数でない」ものである。その区間は $(j - 2^k, j]$ で、$j - 2^k$ は $2^{k+1}$ の倍数である。よって長さ $2^k$ の箱は $2^{k+1}$ ごとに 1 つずつ、重ならずに並び、$i$ を含む長さ $2^k$ の箱は高々 1 つである。それがあるのは「$i$ 以上で最小の $2^k$ の倍数 $j$」が $2^{k+1}$ の倍数でないときに限る。

    $i$ から始めて $i \leftarrow i + \mathrm{lowbit}(i)$ をくり返すと、各段階の $i$ は元の $i$ 以上で、最下位の 1 が $2^k$ の位置にある。このとき今の $i$ は「元の $i$ 以上で最小の $2^k$ の倍数」で、$2^{k+1}$ の倍数でない。下の桁を切り上げる操作しかしていないからである。逆に、途中で飛ばされた $k$（今の $i$ が $2^{k+1}$ の倍数になっている段）には、$i$ を含む長さ $2^k$ の箱がない。よって add は $i$ を含む箱をすべて、ちょうど 1 回ずつ通る。

**線形時間の構築**：初期値がある列から作るとき、add を $N$ 回呼ぶと $O(N \log N)$ である。次のようにすると $O(N)$ で作れる。まず $t[i] = a_i$ とし、$i = 1, 2, \dots, N$ の順に $t[i]$ を $t[i + \mathrm{lowbit}(i)]$ に足し込む（$N$ を超えるなら足さない）。$t[i + \mathrm{lowbit}(i)]$ は $t[i]$ の区間を含むすぐ上の箱で、各箱の区間は「自分の要素 1 つ」と「すぐ下の箱たち」にちょうど分かれる。$i$ の小さい順に足せば、$t[i]$ は親へ渡す前に完成している。

??? note "自作するとき：`BIT`（ACL の `fenwick_tree` に当たる）"
    外から見た添字は 0-indexed、区間は半開区間である。コンストラクタ `BIT()`・`BIT(n)`（全要素 0）と、`add(p, x)`・`sum(l, r)` の名前と意味は ACL の `fenwick_tree` と同じにした。ACL にないものは 3 つある。初期値の配列から線形時間で作るコンストラクタ `BIT(a)`、先頭から $r$ 個の和の `sum(r)`、[BIT 上の二分探索](#binary-search)の `lower_bound(w)` である。同じ探索を、[K 番目の値を求めるデータ構造](../ds/kth-element.md#bit-binary-search)では `kth(k)` と呼んでいる。ACL と違い、中身は `long long` のまま足す（符号なし整数で持つ ACL の工夫は[境界](#boundaries)にある）。添字の範囲を確かめる `assert` も省いた。

    ```cpp
    --8<-- "fenwick-tree/own-bit.cpp:core"
    ```

    完全なプログラム：[`own-bit.cpp`](https://github.com/yuukougun/kyopro-atlas/blob/main/snippets/fenwick-tree/own-bit.cpp)（GitHub）
    { .kp-code-src }

    試験では、区間の和と `lower_bound` の答えを、素朴に足した値と照らし合わせている。線形時間の構築は、`BIT(n)` から `add` を $N$ 回呼んで作った中の配列と比べている。Library Checker の [Point Add Range Sum](https://judge.yosupo.jp/problem/point_add_range_sum) が同じ形の問題である。名前の約束は[インターフェースの決め方](../guide/library-design.md#interface)、確かめ方は[動作確認の手順](../guide/library-design.md#verify)にある。

## 境界（添字の変換・i = 0・符号なし整数） {#boundaries}

BIT のバグは、ほとんどが次の境界で起きる。

- **内部は 1-indexed、外部は 0-indexed の半開区間**：内部を 1-indexed にするのは、$\mathrm{lowbit}(0) = 0$ で 0 番の箱が作れないからである。外部の `add(p, x)` は内部の $p + 1$ から始め、`sum(r)` は $[0, r)$ の和で内部の $r$ から始める。この対応は ACL と同じである。どちらで書くかを最初に決め、混ぜない。問題文の閉区間 $[L, R]$（1-indexed）の和は `sum(L - 1, R)` になる
- **$i = 0$ の add は止まらない**：内部の添字 $0$ から add を始めると、$0 + \mathrm{lowbit}(0) = 0$ で同じ所を回り続ける（無限ループ）。自作で外部の 0-indexed を変換し忘れると起きる。sum は $i > 0$ の間だけ回るので、`sum(0)` は 0 を返して止まる
- **区間の和は 2 回の接頭辞の差**：$l = r$ なら 0 である。$l > r$ を渡すと負の区間になり、ACL では `assert` で止まる
- **値の型**：和は要素の和の上限まで大きくなる。$a_i \le 10^9$ が $2 \times 10^5$ 個なら $2 \times 10^{14}$ で、`int` に収まらない。個数を数えるだけなら BIT の中身は `int` でよい。ただし各 $i$ の個数を足し合わせた答えは、$N = 2 \times 10^5$ で最大 $N(N-1)/2 \approx 2 \times 10^{10}$ になる。答えの変数は `long long` にする
- **ACL は内部を符号なし整数で持つ**：`fenwick_tree<int>` などでも中身は `unsigned int` で足すので、あふれても未定義動作にはならず、$2^{32}$（`long long` なら $2^{64}$）を法とした値が返る。負の値を足しても、答えが型に収まる限り正しい。裏を返すと、`int` で和があふれても落ちずに黙って違う値を返すので、型の選び忘れに気づきにくい
- **配列の長さは値の上限ではなく個数**：値を添字にするとき、値が $10^9$ まであるなら長さ $10^9$ の BIT は作れない。[座標圧縮](../basics/coordinate-compression.md)してから使う（[値を添字にして数える](#count-by-value)）

!!! info "ACL では"
    `fenwick_tree<T> fw(n);`（全要素 0。$O(N)$）。`fw.add(p, x)` で $a_p$ に $x$ を足し、`fw.sum(l, r)` で $[l, r)$ の和を返す。どちらも $O(\log N)$ で、添字は 0-indexed、`l == r` なら 0 を返す。`T` は `int`・`unsigned int`・`long long`・`unsigned long long`・`modint`。演算は足し算に固定で、XOR や max には使えない。初期値の配列から作るコンストラクタはないので、`add` を $N$ 回呼ぶ（$O(N \log N)$）。

```cpp
--8<-- "fenwick-tree/acl-usage.cpp:core"
```

完全なプログラム：[`acl-usage.cpp`](https://github.com/yuukougun/kyopro-atlas/blob/main/snippets/fenwick-tree/acl-usage.cpp)（GitHub）
{ .kp-code-src }

## 値を添字にして数える（座標圧縮と組む） {#count-by-value}

BIT が最もよく出るのは、列の位置ではなく値を添字にして「これまでに出た値の個数」を持つ使い方である。「$j < i$ かつ $A_j \le A_i$ となる $j$ の個数」を各 $i$ について求めるなら、左から順に次をくり返す。

1. BIT の $[0, A_i + 1)$ の和（`sum(0, A_i + 1)`）を読む。これが「すでに出た値のうち $A_i$ 以下の個数」である
2. BIT の位置 $A_i$ に 1 を足す

先に読んでから足すので、自分自身は数えない。左から順に処理することで「$j < i$」の条件が、BIT の添字の範囲で「$A_j \le A_i$」の条件が満たされる。1 つの条件を処理の順序で、もう 1 つを BIT の添字で受け持つのが要点である。

値が $10^9$ まであるときは、[座標圧縮](../basics/coordinate-compression.md#with-ds)で $0$〜$K-1$ の番号にしてから BIT に載せる（$K$ は異なる値の個数）。

```cpp
--8<-- "fenwick-tree/count-by-value.cpp:core"
```

完全なプログラム：[`count-by-value.cpp`](https://github.com/yuukougun/kyopro-atlas/blob/main/snippets/fenwick-tree/count-by-value.cpp)（GitHub）
{ .kp-code-src }

この形からいくつかの型に広がる。

- **不等号を変える**：「$A_j < A_i$」なら $[0, \mathrm{id})$、「$A_j > A_i$」なら「これまでの個数 − $[0, \mathrm{id} + 1)$ の和」を読む。等しい値をどちらに入れるかは、問題の不等号をそのまま写す。$i$ より前の大きい値の個数を足し合わせたものが[転倒数](../ds/inversion-number.md)である
- **個数と和を両方持つ**：BIT を 2 本にして、一方に個数、もう一方に値の和を足す。「前にある $A_i$ 以下の値との差の和」は「$A_i \times$ 個数 − 和」になる（[例題 ABC351 F](#abc351_f)）
- **個数でなく重みを足す**：「$2^{-j}$」のような重みを足して、組ごとに変わる寄与をまとめて数える（練習の LEQ）
- **2 つの条件を持つ組**：$A_j \le A_i$ かつ $B_j \le B_i$ のように条件が 2 つなら、一方でソートして順に処理し、もう一方を BIT の添字にする。2 次元の点の数え上げで、[平面走査](../ds/sweep-line-2d.md#rectangle-count)の基本形である

値をすべて先に知らないと圧縮できない。クエリの値も添字に使うなら、クエリを先に全部読む（[クエリの先読み](../ds/offline-queries.md)）。発展的な使い方は[値を添字にする BIT・セグメント木](../ds/segment-tree-on-values.md)で扱う。

## 変種（差分の BIT・BIT 2 本・2 次元 BIT・接頭辞の max） {#variants}

BIT の「一点加算・接頭辞の和」は、持つ列を変えると別の操作になる。

**区間加算・一点取得（差分の BIT）**：差分の列 $d_k = a_k - a_{k-1}$（$a_{-1} = 0$）を BIT で持つ。$[l, r)$ に $x$ を足す操作は、$d_l \mathrel{+}= x$ と $d_r \mathrel{-}= x$ の 2 回の一点加算で、$a_p$ は $d_0 + \dots + d_p$ の接頭辞の和である。[いもす法](../basics/imos.md#online)を、途中で何度も値を読めるようにした形である。$r = N$ のときの $d_N$ は捨ててよいので、長さを $N + 1$ にしておくと場合分けが要らない。

**区間加算・区間和（BIT 2 本）**：差分 $d_k$ を使うと、接頭辞の和は次のように書ける。

$$
a_0 + \dots + a_{r-1} = \sum_{k<r} d_k \, (r - k) = r \sum_{k<r} d_k - \sum_{k<r} k \, d_k
$$

$d_k$ を足す BIT と $k \, d_k$ を足す BIT の 2 本を持てば、区間加算は 4 回の一点加算、区間和は 2 本の接頭辞の和の 2 組で求まる。遅延セグメント木でも書けるが、こちらは短く定数倍も軽い。

```cpp
--8<-- "fenwick-tree/range-add-sum.cpp:core"
```

完全なプログラム：[`range-add-sum.cpp`](https://github.com/yuukougun/kyopro-atlas/blob/main/snippets/fenwick-tree/range-add-sum.cpp)（GitHub）
{ .kp-code-src }

**2 次元 BIT**：$t[i][j]$ を「行 $(i - \mathrm{lowbit}(i), i]$・列 $(j - \mathrm{lowbit}(j), j]$ の長方形の和」とし、add と sum のループを入れ子にする。一点加算と、原点を角とする長方形の和が $O(\log H \log W)$ で、任意の長方形の和は 4 つの長方形の和の足し引き（[2 次元累積和](../basics/prefix-sum-2d.md)と同じ）になる。領域は $O(HW)$ なので、座標が大きいときは使えない。点を先に知っているなら、一方でソートして 1 次元の BIT にする[平面走査](../ds/sweep-line-2d.md)の方が軽い。

```text
add(i, j, x):  for (p = i; p ≤ H; p += lowbit(p)) for (q = j; q ≤ W; q += lowbit(q)) t[p][q] += x
sum(i, j):     for (p = i; p > 0; p −= lowbit(p)) for (q = j; q > 0; q −= lowbit(q)) s += t[p][q]
```

**接頭辞の max**：「$a_p \leftarrow \max(a_p, x)$」の更新と「$a_0, \dots, a_{r-1}$ の max」の質問だけなら、add の `+` を `max` に変えた BIT で正しく動く。値が増えるだけなので、箱の値を max で上書きしても古い値と矛盾しないからである。値が減る更新や、途中から始まる区間の max には使えない（max には逆がない）。$\mathrm{dp}[v] = \max_{u < v} \mathrm{dp}[u] + 1$ のように、値を添字にした接頭辞の max で遷移する DP（[最長増加部分列](../dp/lis.md)など）で使う。

## BIT 上の二分探索 {#binary-search}

すべての $a_i$ が 0 以上なら、接頭辞の和は単調に増える。よって「$a_0 + \dots + a_r \ge w$ となる最小の $r$」は二分探索で求まる。外側で二分探索して毎回 sum を呼ぶと $O(\log^2 N)$ だが、BIT の箱の形を使うと $O(\log N)$ になる。

手順は、位置 $\mathrm{pos} = 0$ から始めて、歩幅 $\mathrm{step}$ を $N$ 以下の最大の 2 の冪から 1 まで半分ずつにしながら、次を行う（1-indexed）。

```text
pos ← 0
for step = (N 以下の最大の 2 の冪), …, 2, 1:
    if pos + step ≤ N かつ t[pos + step] < w:
        w ← w − t[pos + step]
        pos ← pos + step
答えは pos（1-indexed で pos + 1 番目、0-indexed で pos 番目の要素で初めて w 以上になる）
```

**なぜ正しいか**：$\mathrm{pos}$ はいつも $2 \cdot \mathrm{step}$ の倍数なので、$\mathrm{lowbit}(\mathrm{pos} + \mathrm{step}) = \mathrm{step}$ である。よって $t[\mathrm{pos} + \mathrm{step}]$ はちょうど $(\mathrm{pos}, \mathrm{pos} + \mathrm{step}]$ の和で、「次の $\mathrm{step}$ 個を足しても $w$ に届かないか」を 1 回で判定できる。届かなければ進み、届くなら進まない。上の桁から 2 進数で答えを 1 桁ずつ決めていくのと同じで、ループは $\lfloor \log_2 N \rfloor + 1$ 回である。

値に負があると接頭辞の和が単調でなくなり、「ここで届かないから先にある」という判断が成り立たなくなる。正しく動くのは値が 0 以上のときだけである。

この探索は、個数の BIT で「$k$ 番目に小さい値」を求めるのに使う。値を添字にした個数の BIT で、$w = k$ とした位置が $k$ 番目の値の番号である。値の追加・削除がある多重集合の $k$ 番目は、ほかの方法との比較を含めて[K 番目の値を求めるデータ構造](../ds/kth-element.md)にまとめる。

## 落とし穴 {#pitfalls}

- **1-indexed の閉区間をそのまま渡す**：問題文の $[L, R]$（1-indexed）の和を `fw.sum(L, R)` と書くと、$A_L$ が抜けて $A_{L+1}$〜$A_R$ の和になる。正しくは `fw.sum(L - 1, R)` である。一点の更新も `fw.add(P - 1, x)` にする（`fw.add(N, x)` は ACL の `assert` で止まる）
- **ACL で XOR をしようとする**：`atcoder::fenwick_tree` は足し算に固定である。XOR の BIT は自作の `+` を `^` に変える（[例題 ABC185 F](#abc185_f)）
- **読む前に足す**：「前にあるもの」を数えるとき、位置 $A_i$ に足してから $[0, A_i + 1)$ を読むと自分自身を数えてしまう。読んでから足す（[値を添字にして数える](#count-by-value)）
- **ほかの節で述べた誤り**：区間の min・max に使う（[何ができるか](#what-it-does)）、値の上限を BIT の長さにする、和や答えの型を `int` にする（どちらも[境界](#boundaries)）

## 例題 {#examples}

### PRACTICE2 B. Fenwick Tree {#practice2_b}

<div class="kp-problems" data-role="example" markdown>

- [PRACTICE2 B. Fenwick Tree](https://atcoder.jp/contests/practice2/tasks/practice2_b)（diff なし）：一点加算と区間和のクエリを処理する。

</div>

一点加算と半開区間の和を、そのまま BIT で処理する ACL の練習用の問題である。$N, Q$ はどちらも $5 \times 10^5$ まで、値と加える数は $10^9$ までなので、全体で $O((N + Q) \log N)$ になる。

??? note "解法の詳細"
    `atcoder::fenwick_tree<long long> fw(n)` を作り、初期値を `fw.add(i, a[i])` で入れる。加算のクエリは `fw.add(p, x)`、和のクエリは `fw.sum(l, r)` をそのまま出力する（区間は問題も 0-indexed の半開区間）。和は最大で約 $10^{15}$ になるので、`int` ではあふれる。ACL は符号なしで持つので落ちずに違う値を返す。

### ABC185 F. Range Xor Query {#abc185_f}

<div class="kp-problems" data-role="example" markdown>

- [ABC185 F. Range Xor Query](https://atcoder.jp/contests/abc185/tasks/abc185_f)（diff 1053）：一点を XOR で更新し、区間の XOR を答える。

</div>

XOR は $x \oplus x = 0$ なので、自分自身が逆の操作になる。閉区間 $[x, y]$ の XOR は、$y$ までの接頭辞の XOR と $x - 1$ までの接頭辞の XOR の XOR で求まる。よって BIT の `+` をすべて `^` に変えればそのまま使える。$N, Q \le 3 \times 10^5$ で、全体で $O((N + Q) \log N)$ である。

??? note "解法の詳細"
    自作の BIT の add を `t[i] ^= x`、sum を `s ^= t[i]` に変える。更新のクエリ（$A_x \leftarrow A_x \oplus y$）は 1-indexed の $x$ からの add、質問のクエリは `sum(y) ^ sum(x - 1)` を出力する。ACL の `fenwick_tree` は足し算に固定なので使えない。ACL の `segtree` に XOR と単位元 0 を渡してもよい（[セグメント木](../ds/segment-tree.md)）。

### ABC351 F. Double Sum {#abc351_f}

<div class="kp-problems" data-role="example" markdown>

- [ABC351 F. Double Sum](https://atcoder.jp/contests/abc351/tasks/abc351_f)（diff 1253）：すべての i < j について max(A_j − A_i, 0) の総和を求める。

</div>

$\max(A_j - A_i, 0)$ は、$A_i \le A_j$ の組だけが $A_j - A_i$ を足し、ほかは 0 である。$j$ を固定すると、前にある $A_j$ 以下の値の個数を $c$、それらの和を $s$ として、寄与は $A_j \cdot c - s$ になる。[値を添字にして数える](#count-by-value)の型そのもので、座標圧縮した BIT を個数用と和用の 2 本持てば $O(N \log N)$ で解ける。

??? note "解法の詳細"
    $A$ を座標圧縮し、番号 $\mathrm{id}_j$ を求める。BIT を 2 本（個数 `cnt`、和 `sum`）用意し、$j = 0, 1, \dots, N-1$ の順に次を行う。

    1. $c = \mathtt{cnt}[0, \mathrm{id}_j + 1)$、$s = \mathtt{sum}[0, \mathrm{id}_j + 1)$（位置 $\mathrm{id}_j$ 以下の和）を読み、答えに $A_j \cdot c - s$ を足す
    2. `cnt` の位置 $\mathrm{id}_j$ に 1、`sum` の位置 $\mathrm{id}_j$ に $A_j$ を足す

    $A_i = A_j$ の組は寄与が 0 なので、等しい値を数えても数えなくても答えは同じである。答えは最大で $\frac{N(N-1)}{2} \times 10^8$、$N = 4 \times 10^5$ で約 $8 \times 10^{18}$ になり、`long long` の上限（約 $9.2 \times 10^{18}$）にぎりぎり収まる。

    別の書き方として、値の小さい順に要素を処理し、元の位置を添字にした BIT で「自分より左にある、処理済みの要素」の個数と和を数えてもよい。条件「$i < j$」と「$A_i \le A_j$」の受け持ちを、処理の順序と BIT の添字で入れ替えたものである。

## 練習問題 {#practice}

<div class="kp-problems" data-role="practice" markdown>

- [ABC340 E. Mancala 2](https://atcoder.jp/contests/abc340/tasks/abc340_e)（diff 1157）：円環に並ぶ箱の玉を取り出して順に配る操作を繰り返した後の、各箱の玉の数を求める。
- [ABC221 E. LEQ](https://atcoder.jp/contests/abc221/tasks/abc221_e)（diff 1515）：先頭 ≤ 末尾となる長さ 2 以上の部分列の個数を 998244353 で割った余りを求める。
- [ABC276 F. Double Chance](https://atcoder.jp/contests/abc276/tasks/abc276_f)（diff 1562）：先頭 K 枚から 2 枚を復元抽出したときの最大値の期待値を、各 K について求める。
- [ABC231 F. Jealous Two](https://atcoder.jp/contests/abc231/tasks/abc231_f)（diff 1580）：A_i ≥ A_j かつ B_i ≤ B_j となる組 (i, j) の数を求める。

</div>

??? note "練習の方針"
    - **ABC340 E**：区間加算・一点取得なので差分の BIT を使う。箱の玉を取り出すときは一点取得した値を引いて 0 にする。配る玉のうち $N$ の倍数の分は全体への加算にし、余りは次の箱からの区間加算にする（円環の端を跨ぐなら 2 つの区間に分ける）
    - **ABC221 E**：$i < j$ かつ $A_i \le A_j$ の組は、間の要素を自由に選べるので $2^{j-i-1}$ 個の部分列を作る。$2^{j-i-1} = 2^{j-1} \cdot 2^{-i}$ と $i$ の部分と $j$ の部分に分け、座標圧縮した BIT の位置 $A_i$ に $2^{-i}$（mod での逆元）を足す。$j$ では $A_j$ 以下の重みの和に $2^{j-1}$ を掛ける。`fenwick_tree<modint998244353>` が使える
    - **ABC276 F**：先頭 $K$ 枚での最大値の総和を、$K$ を 1 つ増やすたびの差分で更新する。$K$ 枚目と前の各カードの組の最大値は、前のカードが $A_K$ 以下なら $A_K$、大きければその値である。値を座標圧縮した BIT で「$A_K$ 以下の個数」と「$A_K$ より大きい値の和」を持つ
    - **ABC231 F**：$A$ の小さい順に並べ、$A$ が等しいものは $B$ の大きい順にする。順に処理しながら、$B$ を座標圧縮した BIT で「すでに入れたもののうち $B$ が自分以上の個数」を数える。$(A, B)$ がまったく同じものどうしは互いに条件を満たすので、同じ組はまとめて BIT に入れてから数える

## 力試し {#challenge}

<div class="kp-problems" data-role="challenge" markdown>

- [ARC068 E. Snuke Line](https://atcoder.jp/contests/arc068/tasks/arc068_c)（diff 2307）：各 d について、d 刻みで止まる列車が通る区間の数を求める。

</div>

??? note "力試しの方針"
    - **ARC068 E**：長さ $d$ 以上の区間は $d$ 刻みで必ず踏まれる。長さ $d$ 未満の区間は $d$ の倍数を高々 1 つしか含まないので、「各位置を覆う区間の数」を $d$ の倍数の位置で足せば重複なく数えられる。$d$ を小さい順に増やしながら、長さが $d$ 未満になった区間を区間加算・一点取得の BIT（差分の BIT）に入れる。$d$ の倍数は全部で $M/1 + M/2 + \dots + M/M = O(M \log M)$ 個なので、全体で $O(N \log N + M \log^2 M)$ である

## 確認問題 {#quiz}

??? question "確認問題：t[12] は a の何番目から何番目の和か（1-indexed）。sum(13) はどの箱を足すか"
    $12 = 1100_{(2)}$ で $\mathrm{lowbit}(12) = 4$ なので、$t[12] = a_9 + a_{10} + a_{11} + a_{12}$ である。sum(13) は $13 = 1101_{(2)}$ から最下位の 1 を消していくので、$t[13]$・$t[12]$・$t[8]$ を足す。それぞれ $a_{13}$、$a_9$〜$a_{12}$、$a_1$〜$a_8$ で、閉区間 $[1, 13]$ にちょうど分かれる。

??? question "確認問題：区間の最小値に BIT を使えないのはなぜか"
    BIT で区間 $[l, r)$ の値を出すには、$r$ までの接頭辞の値から $l$ までの接頭辞の値を「取り除く」必要がある。和なら引き算で取り除けるが、$\min(a, b)$ から $b$ の分を取り除いて $a$ に戻す方法はない。接頭辞の min なら値が減る更新だけのときに使えるが、区間の min は[セグメント木](../ds/segment-tree.md)を使う。

??? question "確認問題：BIT 上の二分探索で、値に負があるとなぜ壊れるか"
    BIT 上の二分探索は、$t[\mathrm{pos} + \mathrm{step}] < w$ なら「その $\mathrm{step}$ 個の中では $w$ に届かない」と判断して先へ進む。値に負があると、区間の合計が $w$ 未満でも途中の接頭辞の和が $w$ を超えていることがある。その位置を飛ばしてしまうので、最小の位置が求まらない。

??? question "確認問題：自作の BIT で add(0, x) を内部の添字 0 のまま呼ぶと何が起きるか"
    $\mathrm{lowbit}(0) = 0$ なので、$i \leftarrow i + \mathrm{lowbit}(i)$ で $i$ が 0 のまま変わらず、ループが止まらない。外部を 0-indexed にするなら、add の最初に 1 を足して内部の添字に変換する。

## 使い分け {#comparison}

区間の和を扱う道具は、更新の種類で選ぶ。

| 状況 | 使う手法 |
| --- | --- |
| 更新がなく、区間の和を何度も答える | [累積和](../basics/prefix-sum.md) |
| 区間加算をまとめてしてから、最後に各点を読む | [いもす法](../basics/imos.md) |
| 一点更新と区間の和が交互に来る | BIT |
| 区間加算と一点取得・区間の和が交互に来る | 差分の BIT・BIT 2 本（[変種](#variants)） |
| 区間の min・max、非可換な演算 | [セグメント木](../ds/segment-tree.md) |
| 区間の代入・アフィン変換と区間の和 | [遅延セグメント木](../ds/lazy-segment-tree.md) |

BIT でできることはすべてセグメント木でもできる。BIT を選ぶ理由は、短く書けて定数倍が軽いことである。

## 参考 {#references}

- [AtCoder Library「Fenwick Tree」（document_ja）](https://github.com/atcoder/ac-library/blob/master/document_ja/fenwicktree.md)：API・型の要件・計算量・あふれたときの値（v1.6 の手元の版で確かめた）
- [AtCoder Library「fenwicktree.hpp」](https://github.com/atcoder/ac-library/blob/master/atcoder/fenwicktree.hpp)：内部の 1-indexed と符号なし整数、`sum` が 2 つの接頭辞の差であること
- [drken「AtCoder Library Practice Contest B - Fenwick Tree (1Q)」](https://drken1215.hatenablog.com/entry/2022/12/14/215822)：例題 practice2_b の制約と答えの型
- [drken「AtCoder ABC 185 F - Range Xor Query (緑色, 600 点)」](https://drken1215.hatenablog.com/entry/2020/12/14/005700)：例題 abc185_f の制約と、XOR の逆が XOR であること
- [torus711「AtCoder Beginner Contest 351, F : Double Sum」](https://torus711.hatenablog.com/entry/2024/04/28/182823)：例題 abc351_f の式の変形と、値の順に処理する書き方
- [oraclesqlpuzzle「ABC351-F Double Sum」](https://oraclesqlpuzzle.ninja-web.net/kyoupro/05-atcoder-02-abc/kyoupro-abc351-f.html)：例題 abc351_f の座標圧縮と個数・和の BIT 2 本
- [tayu0110「ABC340E - Mancala 2」](https://tayu0110.hatenablog.com/entry/2024/02/11/015113)：練習 abc340_e が区間加算・一点取得に帰着すること
- [syamashi「\[ABC221\] E - LEQ」](https://note.com/syamashi/n/nc5b5876e0514)：練習 abc221_e の重み $2^{-i}$ を載せる方法
- [gotoki_no_joe「ABC276 A～F をHaskellで」](https://qiita.com/gotoki_no_joe/items/a1f1755cfe99192773d6)：練習 abc276_f の差分の式と、個数・和の 2 本の木
- [m193h「AtCoder ABC231 個人的メモ」](https://zenn.dev/m193h/articles/20211212sun001912m193habc231)：練習 abc231_f のソートの順序と同じ組の扱い
- [drken「AtCoder ARC 068 E - Snuke Line (黄色, 700 点)」](https://drken1215.hatenablog.com/entry/2019/04/17/212900)：力試し arc068_c の長さの順に入れる方法と計算量
