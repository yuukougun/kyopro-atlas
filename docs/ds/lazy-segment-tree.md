---
id: lazy-segment-tree
title: 遅延セグメント木
aliases: [遅延セグ木, Lazy Segment Tree, lazy segtree, 遅延評価セグメント木, 遅延伝搬, 区間作用・区間取得, 双対セグ木, Dual Segment Tree]
type: technique
field: ds
chapter: 区間クエリ
order: 210
level: 水
kind: [データ構造, 区間クエリ]
prerequisites: [segment-tree]
related: [segment-tree-monoids, lazy-segment-tree-patterns, global-offset, fenwick-tree, segment-tree-beats, sqrt-decomposition, interval-set, acl-reading#lazy-segtree-args]
summary: 区間の全要素への加算・代入・アフィン変換と、区間の和・最小値などの取得を、どちらも O(log N) で行う。ACL の lazy_segtree に標準の型を渡して使い、区間の和には S に区間の長さを持たせる。
complexity: 構築 O(N)、区間の更新・区間の取得・一点の取得はどれも O(log N)
signs:
  - {type: phrase, text: 区間に一律に加算・代入・アフィン変換・反転し、区間の和・最小値・最大値を答える}
  - {type: phrase, text: 区間に一律に加算・代入し、一点の値だけを答える}
  - {type: constraint, text: 'N, Q ≤ 2×10^5 で、区間の更新と区間の取得が交互に来る'}
acl: [lazy_segtree]
verify: [range_affine_range_sum, range_add_range_min, range_affine_point_get]
frequency: A
frequency_evidence: recent 4（abc470_g・abc473_f・abc477_f・abc480_g）・前提として 4 ページに届く（直接 4）・古い ABC 4 問
sections:
  - {title: 何ができるか（区間作用・区間取得）, anchor: what-it-does}
  - {title: 保留を持たせるアイデアとなぜ正しいか, anchor: idea}
  - {title: 計算量とその根拠, anchor: complexity}
  - {title: ACL の lazy_segtree で標準の型を呼ぶ, anchor: acl-standard}
  - {title: 区間の長さを S に持たせる（区間和）, anchor: size-in-node}
  - {title: ACL の約束（mapping・composition・id）, anchor: acl-conventions}
  - {title: 境界（葉の長さ・e()・代入の番兵・INF・mod）, anchor: boundaries}
  - {title: 双対セグメント木（区間作用・一点取得）, anchor: dual-segment-tree}
  - {title: 保つ性質と push の手順（自作するとき）, anchor: invariants, level: 青}
stage: reviewed
updated: 2026-10-22
---

!!! abstract "要点"
    - **何ができるか**：区間の全要素への加算・代入・アフィン変換と、区間の和・最小値などの取得を、どちらも $O(\log N)$ で行う。ACL の `lazy_segtree` に標準の型を渡して使い、区間の和を取るときは値に区間の長さを持たせる。
    - **いつ使うか**：
        - 区間に一律に加算・代入・アフィン変換・反転し、区間の和・最小値・最大値を答える
        - 区間に一律に加算・代入し、一点の値だけを答える
        - $N, Q \le 2 \times 10^5$ で、区間の更新と区間の取得が交互に来る
    - **計算量**：構築 $O(N)$、区間の更新・区間の取得・一点の取得はどれも $O(\log N)$（ならしではなく 1 回ごとの上限）
    - **前提**：[セグメント木](../ds/segment-tree.md)

<!-- textlint-disable -->
別名：遅延セグ木・Lazy Segment Tree・lazy segtree・遅延評価セグメント木・遅延伝搬・区間作用・区間取得・双対セグ木・Dual Segment Tree
<!-- textlint-enable -->

遅延セグメント木は、[セグメント木](../ds/segment-tree.md)の各ノードに「子にまだ配っていない更新」を保留として持たせ、必要になったときだけ子へ降ろすことで、区間への一括の更新を $O(\log N)$ にしたデータ構造である。区間の取得はセグメント木と同じく $O(\log N)$ で行える。

## 何ができるか（区間作用・区間取得） {#what-it-does}

遅延セグメント木は、長さ $N$ の列 $a_0, \dots, a_{N-1}$（0-indexed）に対して次の 2 つの操作を、どちらも $O(\log N)$ で行う。区間は[半開区間](../guide/glossary.md#half-open-interval) $[l, r)$ で表す。

- **区間作用**：$l \le i < r$ のすべての $i$ について $a_i \leftarrow f(a_i)$ とする（$f$ は「$x$ を加える」「$x$ にする」「$b$ 倍して $c$ を足す」など）
- **区間取得**：$a_l \cdot a_{l+1} \cdot \dots \cdot a_{r-1}$ を求める（$\cdot$ は和・最小値・最大値など、[結合法則](../guide/glossary.md#associativity)を満たす演算）

素朴に配列で持つと、区間作用と区間取得のどちらも 1 回 $O(N)$ かかる。セグメント木の一点更新を $r - l$ 回くり返す方法では、1 回 $O(N \log N)$ になる。$N, Q \le 2 \times 10^5$ で両方の操作が何度も来ると、合わせて $4 \times 10^{10}$ 回ほどになり間に合わない。

載せられる演算と作用には条件がある。値の集合 $S$・演算 $\cdot$・[単位元](../guide/glossary.md#identity-element) $e$ の組が結合法則を満たす（[モノイド](../guide/glossary.md#monoid)）ことに加えて、作用の集合 $F$ が次の 3 つを満たす必要がある。

1. 「何もしない」作用 $\mathrm{id}$ を含む
2. 2 つの作用を続けて施したものも $F$ に入る（$f \circ g \in F$）。保留を 1 つの値にまとめられる
3. $f(x \cdot y) = f(x) \cdot f(y)$。区間の集約値に直接 $f$ を施した結果が、各要素に $f$ を施してから集約した結果と一致する

たとえば「区間に $x$ を加える」と「区間の最小値」は、$\min(p + x, q + x) = \min(p, q) + x$ なので 3 を満たす。一方「区間に $x$ を加える」と「区間の和」は、$(p + x) + (q + x) \ne (p + q) + x$ なので、そのままでは満たさない。区間の長さを値に足せば満たすようになる（[区間の長さを S に持たせる](#size-in-node)）。

取得が一点の値だけなら、集約値が要らないので条件 3 も要らない。この場合は保留だけを持つ[双対セグメント木](#dual-segment-tree)で足りる。

## 保留を持たせるアイデアとなぜ正しいか {#idea}

遅延セグメント木の核は、区間にすっぽり入るノードでは自分の値だけを直し、子孫の更新は保留にして後回しにすることである。セグメント木と同じく、区間 $[l, r)$ は $O(\log N)$ 個のノードにちょうど分けられる。区間に $x$ を加えるとき、それらのノードの最小値は $x$ だけ増えるので、その場で直せる。困るのはその下の子孫で、全部を直すと $O(N)$ かかる。

そこで各内部ノード $k$ に、値 $d[k]$ と並べて保留 $\mathrm{lz}[k]$ を持たせる。$\mathrm{lz}[k]$ は「$d[k]$ には反映済みで、子にはまだ配っていない作用」である。後の操作が $k$ の区間の一部だけを触るときに限り、先に $\mathrm{lz}[k]$ を 2 つの子へ 1 段だけ降ろす（push）。

次の図は、列 $(5, 3, 7, 2, 6, 4, 8, 1)$ に 3 つの操作を順に行う様子を示す。操作は「$[0, 4)$ に $+2$」「$[1, 4)$ に $-3$」「$[3, 6)$ の最小値」である。各ノードの上段が区間の最小値、下段が保留を表す。

<div class="kp-viz" data-viz="lazy-segment-tree" data-config='{"array": [5, 3, 7, 2, 6, 4, 8, 1], "ops": [{"type": "add", "l": 0, "r": 4, "x": 2}, {"type": "add", "l": 1, "r": 4, "x": -3}, {"type": "min", "l": 3, "r": 6}]}'></div>

図の流れを文章で追うと次のとおりである。

- 1 つ目の操作では、$[0, 4)$ のノードが区間にすっぽり入る。最小値を $2$ から $4$ にし、保留 $+2$ を付けて、その下へは進まない。最後に根の最小値を子から作り直す
- 2 つ目の操作では、$[0, 4)$ のノードは区間 $[1, 4)$ と一部だけ重なる。そこで保留 $+2$ を子の $[0, 2)$ と $[2, 4)$ へ降ろしてから下へ進む
- $[0, 2)$ も一部だけ重なるので、保留 $+2$ を葉へ降ろす。葉 $[1, 2)$ は $3 + 2 = 5$ になり、$-3$ を足して $2$ になる。$[0, 2)$ の最小値は $\min(7, 2) = 2$ に作り直す
- $[2, 4)$ はすっぽり入る。降りてきた $+2$ と今回の $-3$ を合わせた保留 $-1$ を持って止まり、最小値は $1$ になる
- 3 つ目の取得では、$[2, 4)$ のノードが一部だけ重なる。保留 $-1$ を葉へ降ろしてから、葉 $[3, 4)$ の値 $1$ を読む。$[4, 6)$ は保留のないまま読める。答えは $\min(1, 4) = 1$ である

保留が降りるのは、操作が通った経路の上だけである。ほかのノードの保留は、触られるまで残ったままでよい。

**なぜ正しいか**：次の性質を常に保つ。

> 各ノード $k$ について、$d[k]$ に「$k$ より上の祖先が持つ保留」をすべて施すと、$k$ の区間の本当の集約値になる。

区間にすっぽり入るノードで $d[k]$ に $f$ を施し、保留に $f$ を合成するのは、条件 3 によりこの性質を保つ。push は親の保留を子の $d$ と保留へ移すだけなので、祖先の保留を合わせたものは変わらない。区間取得では、読むノードの祖先を上から順にすべて push してから読む。このとき祖先の保留はすべて「何もしない」になっているので、$d[k]$ がそのまま正しい値になる。区間作用の後に経路上のノードを子から作り直すのは、そのノードの区間の一部の値が変わったからである。

保留を 1 ノードに 1 つで済ませられるのは条件 2 のおかげである。保留 $g$ の上に新しい作用 $f$ が来ても、合成した $f \circ g$ という 1 つの作用で表せる。

## 計算量とその根拠 {#complexity}

1 回の区間作用・区間取得で訪れるノードは、セグメント木の区間取得と同じく各段で 4 個以下である。木の段の数は $\lceil \log_2 N \rceil + 1$ なので、訪れるノードは $O(\log N)$ 個になる。各ノードでの push・作用・作り直しは、演算 $\cdot$・作用の適用・合成がそれぞれ $O(1)$ なら $O(1)$ である。よって 1 回 $O(\log N)$ で、これはならし計算量ではなく 1 回ごとの上限である。

- 構築：葉を並べて下から作り直すので $O(N)$
- 一点の取得：ACL の `get` は葉の祖先を上から push してから読むので $O(\log N)$（セグメント木の `get` は $O(1)$）
- 領域：葉の数を $N$ 以上の最小の 2 の冪 $\mathrm{size}$ とすると、値が $2 \cdot \mathrm{size}$ 個、保留が $\mathrm{size}$ 個で、どちらも $O(N)$

演算の中身に $O(T)$ かかるなら（たとえば値が $K \times K$ 行列なら $T = K^3$）、すべての計算量が $T$ 倍になる。

## ACL の lazy_segtree で標準の型を呼ぶ {#acl-standard}

水色の範囲では、ACL の `lazy_segtree` に標準の型を渡して呼べれば足りることが多い。渡すのは値の型 `S` と演算 `op`・単位元 `e`、作用の型 `F` と `mapping`・`composition`・`id` の 7 つである。

!!! info "ACL では"
    `lazy_segtree<S, op, e, F, mapping, composition, id> seg(v);`（`v` は `vector<S>`。`seg(n)` なら全要素が `e()`）。`seg.apply(l, r, f)` で $[l, r)$ に $f$ を作用させ、`seg.prod(l, r)` で $[l, r)$ の集約値を返し、`seg.get(p)` で一点の値を返す。構築は $O(N)$、ほかはどれも $O(\log N)$（`all_prod()` は $O(1)$）。要件は[何ができるか](#what-it-does)の条件 1〜3 で、`l == r` の `prod` は `e()` を返す。

区間加算・区間最小値は次のように書く。`mapping(f, x)` は値 $x$ に作用 $f$ を施した結果、`composition(f, g)` は保留 $g$ の後に $f$ を施す作用、`id()` は何もしない作用を返す。

```cpp
--8<-- "lazy-segment-tree/add-min.cpp:core"
```

区間代入では「何もしない」を表す値が要る。代入されうる値と重ならない番兵を `id()` にする。後から来た代入が前の代入を上書きするので、`composition(f, g)` は $f$ が番兵でなければ $f$ を返す。

```cpp
--8<-- "lazy-segment-tree/assign-max.cpp:core"
```

最小値と最大値を入れ替えるには、`op` と `e` だけを変える（最小値なら `min` と大きい番兵、最大値なら `max` と小さい番兵）。

| やりたいこと | `op` / `e()` | `mapping(f, x)` | `composition(f, g)` / `id()` |
| --- | --- | --- | --- |
| 区間加算・区間 min | `min` / $+\infty$ | $x + f$ | $f + g$ / $0$ |
| 区間加算・区間 max | `max` / $-\infty$ | $x + f$ | $f + g$ / $0$ |
| 区間代入・区間 min | `min` / $+\infty$ | なしなら $x$、ほかは $f$ | なしなら $g$、ほかは $f$ / なし |
| 区間代入・区間 max | `max` / $-\infty$ | なしなら $x$、ほかは $f$ | なしなら $g$、ほかは $f$ / なし |

## 区間の長さを S に持たせる（区間和） {#size-in-node}

区間の和を取るときは、値を「和と区間の長さの組」にする。区間に $c$ を加えると和は「$c \times$ 長さ」だけ増えるが、和だけを持っていると長さが分からず、`mapping` が計算できないからである。長さを持てば `mapping` が書け、条件 3 も満たす。

| やりたいこと | `mapping(f, (s, len))` | `composition(f, g)` | `id()` |
| --- | --- | --- | --- |
| 区間加算 | $(s + f \cdot len, len)$ | $f + g$ | $0$ |
| 区間代入 | なしなら $(s, len)$、ほかは $(f \cdot len, len)$ | なしなら $g$、ほかは $f$ | なし |
| 区間アフィン（$x \to bx + c$） | $(b s + c \cdot len, len)$ | $(b_f b_g, b_f c_g + c_f)$ | $(1, 0)$ |

`op` は成分ごとの和、`e()` は $(0, 0)$ である。アフィン変換は加算（$b = 1$）と代入（$b = 0$）を含むので、両方が来る問題もこの形 1 つで書ける。mod 998244353 での区間アフィン・区間和は次のようになる。

```cpp
--8<-- "lazy-segment-tree/affine-sum.cpp:core"
```

初期値の葉は `{a[i], 1}` のように長さ 1 で作る。長さ 0 の葉にすると、加算しても和が増えない（[境界](#boundaries)）。

値に足すのは長さに限らない。「作用の結果を計算するのに足りない情報を値に足す」のが設計の基本で、区間の反転・転倒数・等差数列の加算なども同じ考え方で載る。型の一覧は[遅延セグメント木の載せ方の型](../ds/lazy-segment-tree-patterns.md#pattern-table)にまとめる。

## ACL の約束（mapping・composition・id） {#acl-conventions}

ACL の 3 つの関数の意味と、引数の順序は次のとおりである。

- `mapping(f, x)`：値 $x$ に作用 $f$ を施した $f(x)$ を返す
- `composition(f, g)`：$g$ を施してから $f$ を施す作用 $f \circ g$ を返す。
  $g$ はノードがすでに持つ保留で、$f$ は新しく届いた作用である
- `id()`：何もしない作用を返す。`e()`（演算の単位元。値の側）と取り違えない

加算や chmin のように順序を入れ替えても結果が同じ作用では、合成の向きを間違えても答えは変わらない。代入やアフィン変換では向きが答えを変える。たとえば「$3$ を代入」（$g = (0, 3)$）の後に「$5$ を加算」（$f = (1, 5)$）が来たとする。正しい合成は $(b_f b_g, b_f c_g + c_f) = (0, 8)$ で、これは「$8$ を代入」である。向きを逆にすると $(0, 3)$ になり、加算が消える。

余りの葉（$\mathrm{size} > N$ のときの $N$ 番目以降）は `e()` で埋まる。ただし ACL の `apply` が作用を置くのは $[0, N)$ に収まるノードだけなので、余りの葉に届く作用は `id()` だけである。`mapping(id(), e()) = e()` は条件 1 から成り立つので、余りの葉のために気を付けることはない。

## 境界（葉の長さ・e()・代入の番兵・INF・mod） {#boundaries}

遅延セグメント木のバグは、ほとんどが次の境界で起きる。

- **葉の長さは 1**：区間和の葉は `{a[i], 1}` で作る。`lazy_segtree<…> seg(n)` は全要素を `e()`（長さ 0）で作るので、そのまま区間加算しても $(0 + f \cdot 0, 0) = (0, 0)$ のままで和が増えない。初期値が 0 でも `vector<S>(n, {0, 1})` から作る
- **`e()` の長さは 0**：`e()` の長さを 1 にすると、`prod` の途中で単位元を足すたびに長さが増え、結果がずれる
- **代入の「なし」の番兵**：代入する値に 0 が来うるなら、「なし」を 0 で表すと「0 を代入」と区別できない。値の範囲の外の数（`LLONG_MAX` など）か、`optional` や「代入するか」のフラグと値の組で表す
- **INF への加算**：区間加算・区間 min を `seg(n)` で作ると、実の要素も `e()`（INF）になる。`e()` が `LLONG_MAX` なら、そこへ区間加算が届いた瞬間にオーバーフローする。初期値に INF を入れる問題も同じである。`INF + 加算の総和` が型に収まる大きさ（`1LL << 60` など）にする
- **mod の取り忘れ**：アフィン変換の和は `mapping` と `composition` の両方で mod を取る。`modint` を使えば忘れない
- **区間の端**：ACL の引数は 0-indexed の半開区間である。問題文の閉区間 $[L, R]$（1-indexed）は `apply(L - 1, R, f)` になる。`l == r` の `apply` は何もせず、`prod` は `e()` を返す

## 双対セグメント木（区間作用・一点取得） {#dual-segment-tree}

双対セグメント木は、区間作用と一点取得だけを行うデータ構造で、各ノードに保留だけを持つ。一点 $p$ の値は、葉 $p$ から根までの経路の保留を初期値に施せば求まる。作用が可換でないときは、施す順序（後で述べる）が要る。区間の集約値を持たないので条件 3 が要らず、値 $S$ に結合法則も要らない。

同じ種類の可換な作用だけが来るとき（加算だけ、chmax だけなど）は、push も要らない。区間作用ではセグメント木と同じように区間をノードに分けて保留に足し、一点取得では葉から根まで保留を集めるだけでよい。

```cpp
--8<-- "lazy-segment-tree/dual-add.cpp:core"
```

代入やアフィン変換のように可換でない作用では、経路上の保留を集める順序が答えを変える。区間作用の前に、区間の両端へ向かう経路の保留を上から push しておくと、新しい作用を置くノードの祖先には保留が残らない。よって経路上では「上ほど新しい作用」という順序が保たれる。一点の値を求めるときは、葉に近い保留から順に初期値へ施し、根の保留を最後に施す。手で書くのが面倒なら、ACL の `lazy_segtree` で `get` だけを使ってもよい。

!!! tip "一点取得だけなら差分の BIT でもよい"
    区間加算・一点取得は、差分の列 $b_i = a_i - a_{i-1}$ を [BIT](../ds/fenwick-tree.md) に持てば、区間加算は 2 点の加算、一点取得は接頭辞の和になる。加算だけならこちらが短く書ける。

## 例題 {#examples}

### PRACTICE2 K. Range Affine Range Sum {#practice2_k}

<div class="kp-problems" data-role="example" markdown>

- [PRACTICE2 K. Range Affine Range Sum](https://atcoder.jp/contests/practice2/tasks/practice2_k)（diff —）：区間に x → bx + c を作用させる操作と、区間和の質問を処理する。

</div>

区間アフィン・区間和を mod 998244353 で処理する、ACL の練習用の問題である。値を（和, 長さ）、作用を $(b, c)$ にして、[区間の長さを S に持たせる](#size-in-node)の表のとおりに 7 つの関数を書けば解ける。$N, Q$ はどちらも $5 \times 10^5$ までなので、全体で $O(N + Q \log N)$ になる。

??? note "解法の詳細"
    初期値の葉は $(a_i, 1)$ で作る。作用 $(b, c)$ の `mapping` は $(b s + c \cdot len, len)$ を返す。$g$ の後に $f$ を施す合成は $(b_f b_g, b_f c_g + c_f)$ で、`id()` は $(1, 0)$ である。和は `atcoder::modint998244353` で持つ。合成の向きを逆にすると、アフィン変換が 2 回以上重なる入力で誤答になる。

### ABC473 F. A/AB Insertion {#abc473_f}

<div class="kp-problems" data-role="example" markdown>

- [ABC473 F. A/AB Insertion](https://atcoder.jp/contests/abc473/tasks/abc473_f)（diff 1303）：A と B からなる文字列の 1 文字の書き換えを挟みながら、指定した部分文字列が、空の文字列に A か AB を挿入する操作のくり返しで作れるかを答える。

</div>

A を $+1$、B を $-1$ に置き換えて累積和を取ると、部分文字列が作れることは「部分文字列の中で累積和が始点の値を一度も下回らない」ことと同じになる。1 文字の書き換えは累積和の後ろ側への区間加算に、判定は区間の最小値と一点の値の比較になるので、区間加算・区間最小値の遅延セグメント木をそのまま使える。

??? note "解法の詳細"
    1-indexed で $P_0 = 0$、$P_i = P_{i-1} + (S_i \text{ が A なら } +1 \text{、B なら } -1)$ とする。

    **言い換えが正しい理由**：作れる文字列では、各 B の直前のどこかに対応する A があるので、どの接頭辞でも A の数は B の数以上である。逆に、どの接頭辞でも A の数が B の数以上なら、最初の B の直前は A なので、その AB を取り除いても条件は保たれる。B がなくなれば A を 1 つずつ取り除けるので、空の文字列まで戻せる。

    **判定**：部分文字列 $S_l \dots S_r$ が作れることは、$l \le i \le r$ のすべてで $P_i \ge P_{l-1}$、すなわち $\min_{l \le i \le r} P_i \ge P_{l-1}$ である。$P$ を長さ $N + 1$ の列として区間加算・区間最小値の遅延セグメント木に載せ、`get(l - 1)` と `prod(l, r + 1)` を比べる。

    **書き換え**：$S_i$ を A から B に変えると $P_i, \dots, P_N$ が $2$ 減り、B から A なら $2$ 増える。`apply(i, N + 1, ∓2)` の区間加算 1 回で済む。

    どちらの操作も $O(\log N)$ なので、全体で $O(N + Q \log N)$ になる。

### ABC382 F. Falling Bars {#abc382_f}

<div class="kp-problems" data-role="example" markdown>

- [ABC382 F. Falling Bars](https://atcoder.jp/contests/abc382/tasks/abc382_f)（diff 1443）：横棒を下にある方から落とし続けたとき、各棒が最終的に止まる行を求める。

</div>

棒は自分より下の棒にしか止められないので、下にある棒から順に 1 本ずつ落とせば、各棒の止まる位置が順に決まる。列ごとに「いちばん上で埋まっている行」を持てば、棒が止まる行はその棒の列の範囲での最小値（上ほど行番号が小さい）の 1 つ上になり、落とした後はその範囲をその行で上書きする。区間最小値と区間代入（区間 chmin でもよい）の遅延セグメント木で解ける。

??? note "解法の詳細"
    行は上から $1, \dots, H$、列は 0-indexed とし、$\mathrm{top}[c]$ を列 $c$ でいちばん上の埋まっている行（何もなければ $H + 1$）とする。棒を行の大きい順（下から）に処理する。同じ行の棒は横に重ならないので、互いに影響しない。

    列 $[C, C + L)$ を占める棒は、$m = \min_{C \le c < C + L} \mathrm{top}[c]$ の 1 つ上の行 $m - 1$ に止まる。止まった後、その範囲の $\mathrm{top}$ を $m - 1$ にする。$m - 1$ は範囲内のどの $\mathrm{top}[c]$ よりも小さいので、区間代入と区間 chmin のどちらで書いても同じ結果になる。

    棒 1 本につき区間取得と区間作用を 1 回ずつ行うので、ソートを合わせて $O(N \log N + N \log W)$ である。

## 練習問題 {#practice}

<div class="kp-problems" data-role="practice" markdown>

- [ABC340 E. Mancala 2](https://atcoder.jp/contests/abc340/tasks/abc340_e)（diff 1157）：円環に並ぶ箱の玉を取り出して順に配る操作を繰り返した後の、各箱の玉の数を求める。
- [典型90 029. Long Bricks（★5）](https://atcoder.jp/contests/typical90/tasks/typical90_ac)（diff —）：区間にレンガを順に積んでいくとき、各レンガが置かれる高さを求める。
- [ABC455 F. Merge Slimes 2](https://atcoder.jp/contests/abc455/tasks/abc455_f)（diff 1549）：最初はすべて 0 の列の区間に値を加えるたびに、その区間の値を重さとするスライムを、重さ x と y を合わせるとコスト xy がかかる規則で 1 つにまとめる最小のコストを mod で答える。
- [ABL E. Replace Digits](https://atcoder.jp/contests/abl/tasks/abl_e)（diff 1706）：数字列の区間を 1 種類の数字で上書きする操作のたびに、整数としての値の mod を答える。
- [ABC179 F. Simplified Reversi](https://atcoder.jp/contests/abc179/tasks/abc179_f)（diff 1713）：盤の端から白石を置く操作を繰り返した後に残る黒石の数を求める。

</div>

??? note "方針"
    - **ABC340 E**：取り出した箱は、一点取得した値を引いて 0 にする。配る玉のうち 1 周を超える分は全体への加算にし、余りは区間加算にする（円環の端を跨ぐなら 2 つの区間に分ける）。区間加算・一点取得なので、双対セグメント木か差分の BIT でもよい
    - **典型90 029**：レンガの範囲の最大値に 1 を足した高さに置き、その範囲を新しい高さで上書きする。区間最大値・区間代入である
    - **ABC455 F**：コストはまとめる順序によらず、相異なる 2 要素の積の和になる。値を（長さ, 和, 相異なる 2 要素の積の和）にする。区間に $f$ を加えたときの積の和の増分は $f \cdot (\text{長さ} - 1) \cdot \text{和} + f^2 \binom{\text{長さ}}{2}$ である
    - **ABL E**：値を（その区間を 10 進数として読んだ値, 長さ）にし、作用を代入する数字にする。$10^k$ と「1 を $k$ 個並べた数」を前計算すれば、結合と代入はどちらも $O(1)$ でできる
    - **ABC179 F**：各行・各列について「最初の白石の位置」を区間 chmin・一点取得で持つ。chmin だけが来るので、双対セグメント木で足りる

## 力試し {#challenge}

<div class="kp-problems" data-role="challenge" markdown>

- [ABC342 G. Retroactive Range Chmax](https://atcoder.jp/contests/abc342/tasks/abc342_g)（diff 2107）：区間 chmax の追加・取り消しと、一点の現在の値の質問を処理する。

</div>

??? note "方針"
    - **ABC342 G**：取り消しがあるので保留を合成できない。セグメント木の各ノードに作用の多重集合を持たせ、区間をノードに分けて追加・削除する。一点の値は、葉から根までの各ノードの最大値と初期値の最大である（双対セグメント木の考え方）

## 確認問題 {#quiz}

??? question "確認問題：区間加算・区間和で、値に区間の長さを持たせるのはなぜか"
    区間の和に $c$ を加えた結果は「和 $+ c \times$ 要素数」で、和だけからは要素数が分からないからである。`mapping` は値と作用だけを受け取るので、要素数を値の側に持たせる必要がある。長さを持つと $f(x \cdot y) = f(x) \cdot f(y)$ も成り立つ。

??? question "確認問題：保留が「$c$ を代入」のノードに「$d$ を加算」が来たら、合成した保留は何になるか"
    「$c + d$ を代入」になる。アフィン変換で書くと $g = (0, c)$ の後に $f = (1, d)$ である。よって合成は $(1 \cdot 0, 1 \cdot c + d) = (0, c + d)$ になる。逆の順（加算の後に代入）なら、代入が前の加算を打ち消して「代入」だけが残る。

??? question "確認問題：区間 chmin と区間和の組が、この枠組みに乗らないのはなぜか"
    区間の和に「$t$ との min を取る」を施した結果は、区間の中で $t$ を超える要素の個数と、それらの和によって決まる。どの $t$ が来ても計算できるようにするには、値に区間の全要素の分布を持たせる必要があり、固定の大きさの値では条件 3 を満たせない。Segment Tree Beats は、最大値・2 番目の最大値・最大値の個数を持ち、条件が成り立たないノードだけ子へ降りることで、これをならし計算量で扱う。

??? question "確認問題：ACL の lazy_segtree の get が O(1) でなく O(log N) なのはなぜか"
    葉の値 $d[p]$ には、祖先に残る保留がまだ施されていないことがあるからである。`get` は葉の祖先を上から順に push してから葉を読むので、高さぶんの $O(\log N)$ かかる。

## 使い分け {#comparison}

遅延セグメント木を書く前に、もっと軽い手法で済まないかを確かめる。

| 状況 | 使う手法 |
| --- | --- |
| 全体への加算・代入だけ | [全体への操作を変数で持つ](../ds/global-offset.md) |
| 区間加算・一点取得だけ | 差分の [BIT](../ds/fenwick-tree.md)、または双対セグメント木 |
| 区間加算・区間和だけ | BIT 2 本（[BIT](../ds/fenwick-tree.md)） |
| 値と作用を自分で設計する | [遅延セグメント木の載せ方の型](../ds/lazy-segment-tree-patterns.md#design-steps) |
| 区間 chmin・区間和、区間の除算など | [Segment Tree Beats](../ds/segment-tree-beats.md)・[平方分割](../ds/sqrt-decomposition.md) |
| 区間を塗って、同じ値の区間をまとめて扱う | [区間を set で管理する](../ds/interval-set.md) |

## 保つ性質と push の手順（自作するとき） {#invariants}

この節は自分でライブラリを書く人向けで、[セグメント木](../ds/segment-tree.md)を配列で実装できることを前提にする。ACL と同じく、葉の数を $N$ 以上の最小の 2 の冪 $\mathrm{size}$ とし、根を 1、ノード $k$ の子を $2k$ と $2k + 1$、葉 $p$ をノード $\mathrm{size} + p$ に置く。

### 保つ性質

- $d[k]$（$1 \le k < 2 \cdot \mathrm{size}$）：$k$ の区間の集約値から、$k$ より上の祖先に残る保留の影響を除いたもの
- $\mathrm{lz}[k]$（$1 \le k < \mathrm{size}$、内部ノードだけ）：$d[k]$ には施し済みで、子にはまだ配っていない作用
- 祖先の保留をすべて施した $d[k]$ が、$k$ の区間の本当の集約値になる

### 各操作の手順

再帰で書くと次のようになる。ノード $k$ は区間 $[k_l, k_r)$ を受け持つ。

```text
all_apply(k, f):                 # ノード k の区間全体に f を施す
    d[k] ← mapping(f, d[k])
    k が内部ノードなら lz[k] ← composition(f, lz[k])

push(k):                         # 保留を子へ 1 段降ろす
    all_apply(2k, lz[k]); all_apply(2k+1, lz[k]); lz[k] ← id

apply(l, r, f, k, [kl, kr)):
    重ならない（r ≤ kl または kr ≤ l）なら戻る
    すっぽり入る（l ≤ kl かつ kr ≤ r）なら all_apply(k, f) して戻る
    push(k)                      # 一部だけ重なる：子を触る前に降ろす
    m ← (kl + kr) / 2
    apply(l, r, f, 2k, [kl, m)); apply(l, r, f, 2k+1, [m, kr))
    d[k] ← op(d[2k], d[2k+1])    # 子から作り直す

prod(l, r, k, [kl, kr)):
    重ならないなら e() を返す
    すっぽり入るなら d[k] を返す
    push(k)
    左右の子の prod を op で結んで返す（左が先）
```

ACL の実装は再帰を使わず、下から上へ書いている。区間作用・区間取得の前に、葉 $\mathrm{size} + l$ と $\mathrm{size} + r - 1$ の祖先を上から push する。ただし、区間の端がその段のノードの境目にそろっていれば、その段の push は省く。そろっている段のノードは区間に丸ごと入るか丸ごと外れるので、読むノードの祖先にならないからである。続けてセグメント木と同じ手順で区間をノードに分け、作用なら各ノードに `all_apply` する。作用の後は、同じ 2 本の経路を下から作り直す。

### 境界（自作で増えるもの）

- 保留は内部ノードだけが持つ。葉に `composition` を呼ぶと、配列の外を触るか、不要な計算が増える
- 余りの葉は `e()` で埋める。作用を置くのは $[0, N)$ に収まるノードだけなので、余りの葉には何もしない作用しか届かない
- 演算が可換でないときは、`prod` で左の子の結果を先に結ぶ
- push を忘れて子を読むと、上の保留が施されていない値を返す。取得の関数でも push する

??? note "C++ の実装例（再帰。区間加算・区間最小値）"
    ```cpp
    --8<-- "lazy-segment-tree/own-add-min.cpp:core"
    ```

## 参考 {#references}

- [AtCoder Library「Lazy Segtree」（document_ja）](https://github.com/atcoder/ac-library/blob/master/document_ja/lazysegtree.md)：載せられる条件・関数の約束・計算量（v1.6 の手元の版で確かめた）
- [AtCoder Library「lazysegtree.hpp」](https://github.com/atcoder/ac-library/blob/master/atcoder/lazysegtree.hpp)：`seg(n)` が `e()` で埋めること、`get` が祖先を push すること、端がそろった段の push を省くこと
- [drken「ACL Practice Contest K - Range Affine Range Sum」](https://drken1215.hatenablog.com/entry/2023/11/15/021000)：例題 practice2_k の値と作用の設計・制約
- [ikatakos「AtCoder Beginner Contest 473 D,E,F,G問題メモ」](https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2026/0829_abc473)：例題 abc473_f の言い換えと操作の対応（解法の部分だけ）
- [merom686「ABC382」](https://merom686.hatenablog.com/entry/2024/12/01/023230)：例題 abc382_f の処理の順序（下の棒から）と、区間最小値・区間 chmin の組
- [ikatakos「Ｓｋｙ株式会社プログラミングコンテスト2026（AtCoder Beginner Contest 455）F,G問題メモ」](https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2026/0425_abc455)：練習 abc455_f の値の持ち方（解法の部分だけ）
