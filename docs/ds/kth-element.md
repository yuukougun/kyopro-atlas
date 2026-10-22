---
id: kth-element
title: K 番目の値を求めるデータ構造
aliases: [BIT 上の二分探索, Fenwick tree binary search, order statistics, 順序統計量, 空きの K 番目]
type: technique
field: ds
chapter: 区間クエリ
order: 170
level: 水
kind: [データ構造, 二分探索]
prerequisites: [fenwick-tree, ordered-set]
related: [segment-tree-binary-search, top-k-multiset, segment-tree-on-values, balanced-bst, binary-trie, kth-value, wavelet-matrix, sqrt-decomposition, linked-list]
summary: 値の追加・削除がある多重集合で、K 番目に小さい値や x 以下の個数を O(log N) で求める。値を添字にした個数の BIT の上で、2 べきの歩幅を大きい順に試して境界を探す。
complexity: 追加・削除・K 番目・x 以下の個数はどれも O(log N)（N は値の種類数。値が大きければ座標圧縮の前処理 O(Q log Q)）
signs:
  - {type: phrase, text: 数の追加・削除と、K 番目に小さい値の質問}
  - {type: phrase, text: 空いている場所のうち K 番目に置く・指定した位置への挿入を繰り返した最終的な列}
  - {type: phrase, text: x 以下の要素の個数（順位）}
acl: [fenwick_tree]
verify: [ordered_set]
frequency: B
frequency_evidence: recent 0・前提として届くページなし・古い ABC 3 問
sections:
  - {title: BIT 上の二分探索の手順（値が 0 以上であることが前提）, anchor: bit-binary-search}
  - {title: 挿入を逆順に処理して「空きの P 番目」に置く, anchor: reverse-insertion}
  - {title: 答えの二分探索で K 番目を数える方法との違い, anchor: vs-kth-value}
stage: draft
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：値の追加・削除がある多重集合で、K 番目に小さい値や x 以下の個数を $O(\log N)$ で求める。値を添字にした個数の BIT の上で、2 べきの歩幅を大きい順に試して境界を探す。
    - **いつ使うか**：
        - 数の追加・削除と、K 番目に小さい値の質問
        - 空いている場所のうち K 番目に置く・指定した位置への挿入を繰り返した最終的な列
        - x 以下の要素の個数（順位）
    - **計算量**：追加・削除・K 番目・x 以下の個数はどれも $O(\log N)$（$N$ は値の種類数。値が大きければ座標圧縮の前処理に $O(Q \log Q)$）
    - **前提**：[BIT（Fenwick Tree）](../ds/fenwick-tree.md)、[set・multiset・map の応用](../ds/ordered-set.md)

<!-- textlint-disable -->
別名：BIT 上の二分探索・Fenwick tree binary search・order statistics・順序統計量・空きの K 番目
<!-- textlint-enable -->

K 番目の値を求めるデータ構造は、値の追加・削除が混ざる多重集合から「小さい方から K 番目」を取り出すための道具の総称である。中心になるのは、値ごとの個数を [BIT](../ds/fenwick-tree.md) に持ち、接頭辞の和が初めて K 以上になる位置を $O(\log N)$ で探す BIT 上の二分探索である。

## 必要になる場面 {#motivation}

C++ の `multiset` は追加・削除・最小値・`lower_bound` を $O(\log N)$ で行えるが、K 番目の要素へは先頭から K 歩進むしかない。イテレータは 1 歩ずつしか動けないので、K 番目を取るのに $O(K)$ かかる。K が 5 以下なら[イテレータを K 歩動かす](../ds/ordered-set.md#near-kth)だけで足りる。しかし K が要素数の半分くらいになりうる問題で、$Q = 2 \times 10^5$ 回聞かれると $10^{10}$ 歩ほどになり間に合わない。

見方を変えると、K 番目に小さい値は「その値以下の要素が初めて K 個以上になる値」である。値 $v$ の個数を $c_v$ とすると、接頭辞の和 $c_0 + c_1 + \dots + c_v$ は $v$ について単調に増える。よって K 番目は「接頭辞の和 $\ge K$」が初めて成り立つ $v$ で、二分探索で探せる。個数の配列を BIT に持てば、追加・削除は一点の加算になり、この探索も BIT の木の上で $O(\log N)$ でできる。

## 使い分け {#comparison}

K 番目を求める方法は多い。問題の条件（値の範囲・先読みできるか・K が固定か）で選ぶ。表の $N$ は要素数か値の種類数である。

| 方法 | K 番目の計算量 | 向いている条件 |
| --- | --- | --- |
| `multiset` から K 歩進む | $O(\log N + K)$ | K が小さい（5 程度まで） |
| 個数の BIT と BIT 上の二分探索 | $O(\log N)$ | 値の範囲が小さいか、先読みして座標圧縮できる |
| 個数のセグメント木と `max_right` | $O(\log N)$ | BIT と同じ条件。ACL で書ける |
| 外側の二分探索と BIT の接頭辞の和 | $O(\log^2 N)$ | 書きやすさを優先するとき |
| pb_ds の `tree` | $O(\log N)$ | 値が大きく、先読みできない |
| 2 つのヒープ・2 つの `multiset` | $O(\log N)$ | K が固定（中央値・上位 K 個） |
| Binary Trie | $O(\text{ビット数})$ | 整数で、全体への XOR と組むとき |
| 平方分割 | $O(\sqrt{N})$ | ほかが使えないときの逃げ道 |

各方法の要点は次のとおりである。

- **BIT 上の二分探索**：最も定数倍が軽く、コードも短い。値は配列の添字にするので、値が $10^9$ まであるなら、全クエリを先に読んで[座標圧縮](../basics/coordinate-compression.md#with-ds)する（[オフライン](../guide/glossary.md#offline)）。手順は[次の節](#bit-binary-search)で述べる
- **セグメント木の `max_right`**：個数を載せた和のセグメント木で、`max_right(0, [&](int s) { return s < k; })` が K 番目の位置を返す。ACL だけで書け、和以外の条件にも広げやすい（[セグメント木上の二分探索](../ds/segment-tree-binary-search.md)）
- **外側の二分探索**：値 $v$ を二分探索し、BIT の接頭辞の和で $v$ 以下の個数を数える。1 回の判定が $O(\log N)$ なので全体で $O(\log^2 N)$ になる。$Q = 2 \times 10^5$ なら $Q \log^2 N$ はおよそ $6 \times 10^7$ で、多くは間に合う
- **pb_ds の `tree`**：GCC の拡張の順序付き集合で、`find_by_order(k)`（0 始まりの番号 $k$ の要素）と `order_of_key(x)`（$x$ 未満の個数）を持つ。値を先読みできないオンラインの問題でも使える。重複を許すには `(値, 通し番号)` の組にする（[pb_ds の tree](../cpp/cpp-container-idioms.md#pb-ds)・[平衡二分探索木と pb_ds の tree](../ds/balanced-bst.md)）
- **2 つのヒープ**：K が最後まで変わらないなら、小さい K 個と残りに分けて持てば、K 番目は小さい側の最大値である。削除もあるなら 2 つの `multiset` にする（[上位 K 個の和と中央値の管理](../ds/top-k-multiset.md)）
- **Binary Trie**：整数を上位ビットから辿る木で、各ノードに個数を持てば K 番目を求められる。全体に XOR をかける操作と組むときに使う（[Binary Trie](../ds/binary-trie.md#kth-and-global-xor)）

区間ごとに K 番目を聞かれる（列の $[l, r)$ の中で K 番目に小さい値）なら、ここの方法では足りない。[Wavelet Matrix](../ds/wavelet-matrix.md) などの区間の構造を使う。

## BIT 上の二分探索の手順（値が 0 以上であることが前提） {#bit-binary-search}

BIT 上の二分探索は、BIT の配列 $t$ をそのまま辿って「接頭辞の和が初めて $K$ 以上になる位置」を $O(\log N)$ で求める方法である。この節では BIT の中を 1-indexed で書き、値 $v$ の個数を $c_v$（$1 \le v \le N$）とする。$t[i]$ は区間 $(i - \mathrm{lowbit}(i), i]$ の $c$ の和で、$\mathrm{lowbit}(i)$ は $i$ を割り切る最大の 2 べき（`i & -i`）である。

アイデアは、答えの位置を 2 進数で上の桁から 1 桁ずつ決めることである。いま $\mathrm{pos}$ まで進んでいて、歩幅 $\mathrm{step}$ が 2 べきで、$\mathrm{pos}$ が $2 \cdot \mathrm{step}$ の倍数なら、$\mathrm{lowbit}(\mathrm{pos} + \mathrm{step}) = \mathrm{step}$ である。よって $t[\mathrm{pos} + \mathrm{step}]$ は、ちょうど区間 $(\mathrm{pos}, \mathrm{pos} + \mathrm{step}]$ の和になる。この 1 つの値を見るだけで「$\mathrm{step}$ だけ進んでも和が $K$ に届かないか」が分かる。

次の図は、値 1〜8 の個数が $(1, 0, 2, 1, 0, 0, 3, 1)$ の多重集合で、5 番目に小さい値を探す様子である。上の 4 段が BIT の $t[i]$ で、各枠の横幅がその区間を表す。

![2 べきの歩幅 8・4・2・1 の順に t[8]・t[4]・t[6]・t[7] を試し、t[4] と t[6] で進んで pos = 6 に止まり、答えは 7 になる](../img/kth-element/bit-binary-search.svg)

図の流れを文章で追うと次のとおりである。

- 歩幅 8：$t[8] = 8$ は全体の個数で、$5$ 以上なので進まない。答えは $(0, 8]$ にある
- 歩幅 4：$t[4] = 4$ は $(0, 4]$ の個数で、$5$ 未満なので進む。$\mathrm{pos} = 4$、残りは $k = 5 - 4 = 1$ 個
- 歩幅 2：$t[6] = 0$ は $(4, 6]$ の個数で、$1$ 未満なので進む。$\mathrm{pos} = 6$、$k = 1$ のまま
- 歩幅 1：$t[7] = 3$ は $(6, 7]$ の個数で、$1$ 以上なので進まない。答えは $\mathrm{pos} + 1 = 7$

実際、接頭辞の和は $(1, 1, 3, 4, 4, 4, 7, 8)$ で、初めて $5$ 以上になるのは値 7 である。

### 保つ性質

各歩幅を試した後、次の 2 つが成り立つ。

- $(0, \mathrm{pos}]$ の和は元の $K$ より小さく、$k$ は「元の $K$ $-$ $(0, \mathrm{pos}]$ の和」である
- 答えは $(\mathrm{pos}, \mathrm{pos} + \mathrm{step}]$ にある（$\mathrm{pos} + \mathrm{step} > N$ なら $(\mathrm{pos}, N]$ にあるか、どこにもない）

試す前と後で、答えのある範囲の幅は $2 \cdot \mathrm{step}$ から $\mathrm{step}$ に半分になる。最初は $\mathrm{pos} = 0$ で、$\mathrm{step}$ を $N$ 以下の最大の 2 べきにすれば $2 \cdot \mathrm{step} > N$ なので、答えは $(0, N] \subseteq (0, 2 \cdot \mathrm{step}]$ にある。歩幅 $\mathrm{step}$ を試すと、答えがこの範囲の前半 $(\mathrm{pos}, \mathrm{pos} + \mathrm{step}]$ にあるか、後半 $(\mathrm{pos} + \mathrm{step}, \mathrm{pos} + 2 \cdot \mathrm{step}]$ にあるかが決まる。後半なら進むので、どちらでも試した後に 2 つめの性質が成り立つ。次の歩幅 $\mathrm{step} / 2$ から見ると、これは試す前の幅 $2 \cdot (\mathrm{step} / 2)$ の範囲である。$\mathrm{step} = 1$ まで試すと範囲の幅が 1 になり、答えは $\mathrm{pos} + 1$ に決まる。

「和が $K$ に届かない間は進む」と判断できるのは、接頭辞の和が単調に増えるからである。そのために、すべての $c_v$ が 0 以上でなければならない。

### 各操作の手順

```text
kth(k):                          # k ≥ 1。接頭辞の和が初めて k 以上になる位置
    pos ← 0
    step ← N 以下の最大の 2 べき
    while step > 0:
        if pos + step ≤ N かつ t[pos + step] < k:
            k ← k − t[pos + step]
            pos ← pos + step
        step ← step / 2
    return pos + 1               # 全体の和が k 未満なら N + 1
```

多重集合としての操作は次のようになる。

- 値 $v$ の追加・削除：$c_v$ に $+1$・$-1$ を加える（BIT の一点の加算）
- K 番目に小さい値：`kth(K)`。削除も伴うなら、見つけた値に $-1$ を加える
- $x$ 以下の個数（順位）：接頭辞の和 $c_1 + \dots + c_x$。$x$ 未満の個数は $c_1 + \dots + c_{x-1}$

C++ では、外から見た位置を 0-indexed にすると、内部の位置 $\mathrm{pos} + 1$ がそのまま外の $\mathrm{pos}$ になる。

```cpp
--8<-- "kth-element/bit-kth.cpp:core"
```

### 境界

- **K の数え方**：`kth` の $k$ は 1 始まりである。0 始まりの $k$ を受け取ったら $k + 1$ を渡す。$k = 0$ を渡すと、どの $t$ も $0$ 未満でないので最初の位置を返してしまう
- **K 個に満たないとき**：全体の和が $k$ 未満なら、範囲に収まる歩幅ではどれも進むので $\mathrm{pos} = N$ で終わり、外から見た $N$（配列の外）を返す。座標圧縮した値の配列を引く前に、この場合を除く
- **歩幅の初期値**：$N$ 以下の最大の 2 べき（C++20 の [`bit_floor`](../cpp/cpp-math-functions.md#bit-functions)）にする。歩幅は 2 べきでなければならない。$N$ が 2 べきでないのに $\mathrm{step} = N$ から始めると、$\mathrm{lowbit}(\mathrm{pos} + \mathrm{step}) \ne \mathrm{step}$ となり（$N = 6$ なら $t[6]$ は $(4, 6]$ の和）、$t[\mathrm{pos} + \mathrm{step}]$ が区間 $(\mathrm{pos}, \mathrm{pos} + \mathrm{step}]$ の和でなくなる。半分にしていっても $6 \to 3 \to 1$ と 2 べきでない歩幅が続く。なお $N$ 以上の 2 べきから始めても、条件 $\mathrm{pos} + \mathrm{step} \le N$ があれば正しい。条件 $\mathrm{pos} + \mathrm{step} \le N$ を忘れると配列の外を読む
- **不等号の向き**：`t[pos + step] < k` を `<=` にすると、接頭辞の和が初めて $k$ を超える位置、すなわち $K + 1$ 番目を返す

!!! info "ACL では"
    ACL の `fenwick_tree<T> fw(n);` は `fw.add(p, x)` と `fw.sum(l, r)`（どちらも $O(\log N)$）しか持たず、内部の配列も private なので、BIT 上の二分探索は書けない。ACL だけで書くなら、個数を載せた `segtree<int, op, e>`（`op` は和、`e()` は 0）で `seg.max_right(0, [&](int s) { return s < k; })` を呼ぶ。返り値 $r$ は $[0, r)$ の和が $k$ 未満で、$[0, r]$ の和が $k$ 以上になる位置なので、0-indexed の K 番目である（K 個に満たなければ $n$）。条件 `f(e())` が真であることが要件なので $k \ge 1$ にする。計算量は $O(\log N)$。

## 挿入を逆順に処理して「空きの P 番目」に置く {#reverse-insertion}

「空の列の先頭から $P_i$ 番目の位置に $i$ を挿入する」操作を $i = 1, 2, \dots, N$ の順に行い、最後の列を求める問題がある。`vector` の途中への挿入は 1 回 $O(N)$ なので合わせて $O(N^2)$ になり、$N$ が数十万だと間に合わない。挿入の場所が値ではなく位置で指定されるので、[配列で作る連結リスト](../ds/linked-list.md#comparison)でも速くならない。

最後に挿入した $N$ の位置は、その後に何も挿入されないので $P_N$ で確定する。そこで逆順に処理し、最終的な列の $N$ 個の場所のうち、まだ値の決まっていない場所を「空き」として持つ。

> $i = N, N-1, \dots, 1$ の順に、空きのうち前から $P_i$ 番目の場所に $i$ を置く。

**なぜ正しいか**：最終的な列から $N, N-1, \dots, i+1$ を取り除くと、$i$ を挿入した直後の列になる。この列で $i$ は前から $P_i$ 番目にある。取り除かなかった要素（$1, \dots, i$）の場所は、逆順の処理で $i$ を置く時点の空きとちょうど一致し、順序も保たれている。よって $i$ の場所は空きの $P_i$ 番目である。

たとえば $N = 4$、$P = (1, 1, 2, 1)$ では、前から挿入すると $(1) \to (2, 1) \to (2, 3, 1) \to (4, 2, 3, 1)$ になる。逆順では、4 を空き $\{1, 2, 3, 4\}$ の 1 番目（場所 1）に、3 を空き $\{2, 3, 4\}$ の 2 番目（場所 3）に、2 を空き $\{2, 4\}$ の 1 番目（場所 2）に、1 を残りの場所 4 に置く。結果は同じ $(4, 2, 3, 1)$ である。

空きを 1、埋まった場所を 0 とした BIT を作ると、「空きの $P_i$ 番目」は接頭辞の和が初めて $P_i$ 以上になる場所なので、BIT 上の二分探索で求まる。置いた場所には $-1$ を加える。全体で $O(N \log N)$ である。

```cpp
--8<-- "kth-element/reverse-insert.cpp:core"
```

同じ形は「残っている人のうち前から K 番目を取り除く」操作の繰り返しにも使える。残っている人を 1 とした BIT で K 番目を探し、取り除いた人に $-1$ を加えればよい。

## 答えの二分探索で K 番目を数える方法との違い {#vs-kth-value}

K 番目を求める方法には、もう 1 つ「答え $x$ を二分探索し、$x$ 以下の個数 $\mathrm{count}(x)$ が $K$ 以上になる最小の $x$ を求める」型がある（[K 番目の値](../basics/kth-value.md#why-count)）。どちらも「接頭辞の個数が初めて $K$ 以上になる値」を探す点は同じで、違うのは集合の持ち方である。

- **このページの方法**：集合を値ごとの個数として明示的に持ち、追加・削除のたびに更新する。値の候補は $N$ 種類ほどで、1 回の K 番目は $O(\log N)$
- **答えの二分探索**：「2 つの数の積すべて」のように、集合が大きすぎて持てないが、$\mathrm{count}(x)$ はソートや尺取り法で速く数えられる。集合は変わらないことが多く、値の範囲 $V$ について $O(\log V \times \text{数える時間})$

迷ったら、集合の要素を 1 つずつ数えられる大きさか（BIT に入るか）で分ける。要素が $10^{10}$ 個あるような集合では、このページの方法は使えない。逆に、追加・削除のたびに答えの二分探索で数え直すと、毎回 $O(N)$ 以上かかって遅い。外側の二分探索と BIT の接頭辞の和を組む $O(\log^2 N)$ の方法は、この 2 つの中間で、持ち方はこのページ、探し方は答えの二分探索である。

## 落とし穴 {#pitfalls}

- **個数が負になる**：存在しない値を削除すると、その $c_v$ が $-1$ になり、接頭辞の和が単調でなくなる。BIT 上の二分探索は「和が $K$ に届かない間は進む」と判断するので、本当の答えを飛び越えて先の位置を返す（[確認問題](#quiz)の 3 つめ）。その答えで削除を続けると、以後の結果も狂う。削除する値が集合にあることを確かめてから $-1$ を加える
- **座標圧縮した番号を答えてしまう**：BIT が返すのは圧縮後の番号である。元の値の配列 `vals[r]` に戻してから出力する
- **同じ値を区別する必要がある場合**：個数の BIT では同じ値は 1 か所にまとまるので、値の削除は $-1$ でよい（`multiset` の `erase(x)` がすべて消すのとは違う）。ただし同じ値の要素ごとに別の情報（和に加える重みや出どころ）を持たせたいなら、`(値, 添字)` の組で座標圧縮して全要素の番号を変える
- **値の範囲をそのまま添字にする**：値が $10^9$ まであると BIT の配列を確保できない。先読みできるなら座標圧縮、できないなら pb_ds の `tree` を使う
- **K 番目に大きい値**：個数を $M$ とすると、K 番目に大きい値は $M - K + 1$ 番目に小さい値である。BIT の向きを逆にして作り直す必要はない

## 例題 {#examples}

### ARC033 C. データ構造 {#arc033_3}

<div class="kp-problems" data-role="example" markdown>

- [ARC033 C. データ構造](https://atcoder.jp/contests/arc033/tasks/arc033_3)（diff 1641）：数の集合への追加と、小さい方から x 番目の数を答えて削除するクエリを処理する。

</div>

数の範囲が $2 \times 10^5$ までなので、値をそのまま BIT の添字にして個数を持てばよい。追加は一点の $+1$、質問は BIT 上の二分探索で x 番目を求めてから一点の $-1$ である。

??? note "解法の詳細"
    クエリ数 $Q$ と数 $X$ はどちらも $2 \times 10^5$ 以下である。長さ $2 \times 10^5 + 1$ の個数の BIT を用意し、値 $X$ を追加するときは位置 $X$ に $+1$ を加える。質問では `kth(X)` で接頭辞の和が初めて $X$ 以上になる位置 $v$ を求め、$v$ を出力して位置 $v$ に $-1$ を加える。数の上限を $M = 2 \times 10^5$ とすると、どちらの操作も $O(\log M)$ なので、全体で $O(Q \log M)$ になる。x 番目の数は必ず存在する前提で書いている。外側の二分探索と接頭辞の和で書いても $O(Q \log^2 M)$ で間に合う。

## 練習問題 {#practice}

<div class="kp-problems" data-role="practice" markdown>

- [ABC241 D. Sequence Query](https://atcoder.jp/contests/abc241/tasks/abc241_d)（diff 1177）：数の追加と「x 以下で大きい方から K 番目」「x 以上で小さい方から K 番目」の質問を処理する（K ≤ 5）。
- [ABC281 E. Least Elements](https://atcoder.jp/contests/abc281/tasks/abc281_e)（diff 1334）：長さ M の各窓で、小さい方から K 個の和を答える。
- [ABC392 F. Insert](https://atcoder.jp/contests/abc392/tasks/abc392_f)（diff 1395）：空の列に、i = 1, 2, …, N の順に i を先頭から P_i 番目の位置へ挿入した後の列を求める。

</div>

??? note "方針"
    - **ABC241 D**：$k$ が小さいので、`multiset` の `lower_bound`・`upper_bound` からイテレータを $k$ 歩動かせば足りる。BIT で解くなら、値を先読みして座標圧縮し、$x$ 以下の個数 $s$ から $s - k + 1$ 番目（$s < k$ ならなし）、$x$ 未満の個数 $s'$ から $s' + k$ 番目（全体の個数が $s' + k$ に満たなければなし）を BIT 上の二分探索で求める
    - **ABC281 E**：窓をずらすたびに 1 個の追加と 1 個の削除が起きる。値を座標圧縮した個数の BIT と和の BIT を持ち、K 番目の位置を BIT 上の二分探索で求めて、そこまでの和を答える。同じ値が K 番目をまたぐときは、`(値, 添字)` で圧縮しておくと和の調整が要らない
    - **ABC392 F**：[挿入を逆順に処理して「空きの P 番目」に置く](#reverse-insertion)の形そのものである

## 確認問題 {#quiz}

??? question "確認問題：pos が 2·step の倍数のとき、t[pos + step] が区間 (pos, pos + step] の和になるのはなぜか"
    $\mathrm{pos}$ は $2 \cdot \mathrm{step}$ の倍数なので、2 進数で $\mathrm{step}$ の桁から下はすべて 0 である。そこに $\mathrm{step}$ を足すと、$\mathrm{pos} + \mathrm{step}$ の最下位の 1 は $\mathrm{step}$ の桁になり、$\mathrm{lowbit}(\mathrm{pos} + \mathrm{step}) = \mathrm{step}$ である。$t[i]$ は $(i - \mathrm{lowbit}(i), i]$ の和なので、$t[\mathrm{pos} + \mathrm{step}]$ は $(\mathrm{pos}, \mathrm{pos} + \mathrm{step}]$ の和になる。歩幅を大きい順に試すので、$\mathrm{pos}$ は常にそれより大きい 2 べきの和で、この条件を満たす。

??? question "確認問題：K が固定のとき、2 つのヒープで K 番目を保てるのはなぜか"
    小さい方の K 個を最大ヒープ、残りを最小ヒープに入れると、K 番目は最大ヒープの先頭である。新しい値は先頭と比べてどちらかに入れ、個数が K からずれたら境界の 1 個を反対側へ移せばよい。どちらも先頭しか見ないので $O(\log N)$ で済む。K がクエリごとに変わると、境界を K に合わせて動かすのに多くの移動が要るので、この方法は使えない。

??? question "確認問題：多重集合 {1, 3, 4} で、入っていない値 2 を間違えて削除すると、1 番目に小さい値の探索はどうなるか"
    個数は $(c_1, c_2, c_3, c_4) = (1, -1, 1, 1)$、接頭辞の和は $(1, 0, 1, 2)$ になり、単調でなくなる。BIT は $t[2] = 0$・$t[3] = 1$・$t[4] = 2$ である。`kth(1)` は歩幅 4 で $t[4] = 2 \ge 1$ なので進まず、歩幅 2 で $t[2] = 0 < 1$ なので $\mathrm{pos} = 2$ へ進み、歩幅 1 で $t[3] = 1 \ge 1$ なので止まって 3 を返す。本当の答えは 1 である。和が一度 $K$ 以上になった後で下がると、そこを飛び越えてしまう。削除の前に個数が正かを確かめる。

## 参考 {#references}

- [drken「k 番目の値を高速に取り出せるデータ構造のまとめ - BIT上二分探索や平衡二分探索木など」](https://qiita.com/drken/items/1b7e6e459c24a83bb7fd)：方法の比較（値の範囲・先読み・K が固定の場合分け）、例題 arc033_3 の制約
- [drken「AtCoder ARC 033 C - データ構造」](https://drken1215.hatenablog.com/entry/2020/02/29/035900)：例題 arc033_3 の問い（Binary Trie による別解）
- [drken「AtCoder ABC 281 E - Least Elements」](https://drken1215.hatenablog.com/entry/2022/12/14/185200)：練習 abc281_e の解き方の一覧（座標圧縮した個数と和の BIT、BIT 上の二分探索）
- [kyo-pro「(C++)ABC241D - Sequence Query」](https://kyo-pro.hatenablog.com/entry/ABC241D-cpp)：練習 abc241_d の `multiset` での解き方
- [Yuulis「【AtCoder】ABC 392 F - Insert」](https://yuulis.hatenablog.com/entry/ABC-392-F)：練習 abc392_f の逆順の処理と、空きを 1 とした和のセグメント木の `max_right`
- [AtCoder Library「Segtree」（document_ja）](https://github.com/atcoder/ac-library/blob/master/document_ja/segtree.md)：`max_right` の返り値と要件（v1.6 の手元の版で確かめた）
- [AtCoder Library「Fenwick Tree」（document_ja）](https://github.com/atcoder/ac-library/blob/master/document_ja/fenwicktree.md)：`fenwick_tree` が持つ操作
