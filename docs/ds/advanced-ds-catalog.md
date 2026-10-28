---
id: advanced-ds-catalog
title: 見慣れないデータ構造の名前と用途
aliases: [セグ木マージ, segment tree merging, 2 次元セグ木, 2 次元 BIT, K-D tree, 併合可能なヒープ, meldable heap, skew heap, leftist heap, Fast Set, Fractional Cascading, 析合木, Kinetic Segment Tree]
type: hub
field: ds
chapter: そのほかのデータ構造
order: 370
level: null
kind: [案内, データ構造]
prerequisites: []
related: [segment-tree, priority-queue, small-to-large, balanced-bst, wavelet-matrix, dynamic-tree, cdq-divide-and-conquer, mo-algorithm, cht]
summary: 解説に見慣れない名前のデータ構造が出てきたときに、何ができるかと代わりになる手を 1 行ずつ引く。セグ木のマージ・2 次元セグ木・K-D tree・併合可能なヒープ・Fast Set・析合木などを並べる。
complexity: null
signs: []
acl: []
verify: []
sections:
  - {title: ほかのページにあるもの（木の動的な構造は木の章、CDQ 分割統治・時間付き Mo・Li Chao Tree は各ページ）, anchor: elsewhere}
  - {title: 名前・何ができるか・代わりになる手の表, anchor: table}
  - {title: 併合可能なヒープ（skew heap・leftist heap・ランダム化ヒープ。マージテクで足りることが多い）, anchor: meldable-heap}
stage: reviewed
updated: 2026-10-29
---

!!! abstract "要点"
    - **何のページか**：解説に見慣れない名前のデータ構造が出てきたときに、何ができるかと代わりになる手を 1 行ずつ引く。セグ木のマージ・2 次元セグ木・K-D tree・併合可能なヒープ・Fast Set・析合木などを並べる。
    - **いつ使うか**：
        - 解説やライブラリに知らない名前のデータ構造が出てきて、何をするものかを知りたい。
        - 想定解のデータ構造を書けないので、黄までの範囲の手で代えられるかを知りたい。
    - **使い方**：まず[ほかのページにあるもの](#elsewhere)の表で名前を探し、ページがあればそこへ進む。なければ[名前・何ができるか・代わりになる手の表](#table)で用途と代わりの手を確かめる。
    - **計算量**：名前ごとの値は表のとおり。併合可能なヒープの併合は $O(\log N)$（skew heap がならし、leftist heap が最悪、ランダム化ヒープが期待の上限）

<!-- textlint-disable -->
別名：セグ木マージ・segment tree merging・2 次元セグ木・2 次元 BIT・K-D tree・併合可能なヒープ・meldable heap・skew heap・leftist heap・Fast Set・Fractional Cascading・析合木・Kinetic Segment Tree
<!-- textlint-enable -->

見慣れないデータ構造の名前と用途は、解説で名前だけ出会う発展的なデータ構造を、何ができるか・計算量・代わりになる手の 3 つで引くための一覧である。ABC で必須になった例はほとんどなく、ほとんどの問題は代わりの列の手で解ける。名前を知っておくと、解説の想定解が自分の知っている手のどれに当たるかを判断しやすくなる。

## ほかのページにあるもの（木の動的な構造は木の章、CDQ 分割統治・時間付き Mo・Li Chao Tree は各ページ） {#elsewhere}

解説で見かける名前のうち、この教材にページか節があるものを並べた。左の列の名前で探し、右の列のページへ進む。

**区間・列のデータ構造**

| 解説で見かける名前 | 何をするものか | ページ |
| --- | --- | --- |
| 双対セグ木（Dual Segment Tree） | 区間への作用と一点の取得 | [遅延セグメント木](../ds/lazy-segment-tree.md#dual-segment-tree) |
| 動的セグ木・sparse segment tree | 添字の範囲が大きいとき、要るノードだけを作る | [値を添字にする BIT・セグメント木](../ds/segment-tree-on-values.md#dynamic-segment-tree) |
| Segment Tree Beats・吉司机线段树 | 区間 chmin・chmax と区間の和 | [Segment Tree Beats](../ds/segment-tree-beats.md) |
| 永続セグ木・経路コピー | 更新前の版を残したまま更新する | [永続データ構造](../ds/persistent-data-structures.md#path-copying) |
| マージソート木・領域木・Range Tree | 区間の $x$ 以下の個数・和をオンラインで | [マージソート木](../ds/merge-sort-tree.md) |
| Wavelet Matrix・Wavelet Tree | 区間の K 番目・$x$ 未満の個数を静的な列で | [Wavelet Matrix](../ds/wavelet-matrix.md) |
| Disjoint Sparse Table | 冪等でない演算の静的な区間の積を $O(1)$ で | [Sparse Table](../ds/sparse-table.md#disjoint-sparse-table) |
| ODT・Chtholly Tree・珂朵莉树 | 値が同じ区間をまとめて set で持つ | [区間を set で管理する](../ds/interval-set.md) |
| treap・splay・RBST・implicit treap | 列の途中への挿入・削除、区間の反転 | [平衡二分探索木と pb_ds の tree](../ds/balanced-bst.md#treap) |
| pb_ds の tree・order statistics tree | K 番目の要素と $x$ 未満の個数 | [平衡二分探索木と pb_ds の tree](../ds/balanced-bst.md#pbds) |
| Binary Trie・XOR Trie | XOR の最小・最大、K 番目 | [Binary Trie](../ds/binary-trie.md) |
| Cartesian Tree・デカルト木 | 最大値の位置で区間を割る再帰の木 | [単調スタックとスライド最小値](../ds/monotonic-stack.md#cartesian-tree) |
| SWAG（Sliding Window Aggregation） | 総積を答えられるキュー | [単調スタックとスライド最小値](../ds/monotonic-stack.md#swag) |
| Priority Sum Structure | 上位 K 個の和の管理 | [上位 K 個の和と中央値の管理](../ds/top-k-multiset.md#two-sets) |
| 部分永続 Union-Find | 過去の時刻での連結判定 | [部分永続 Union-Find](../ds/partially-persistent-union-find.md) |
| Undo つき Union-Find | 直前の併合を取り消す | [ロールバックできる Union-Find](../ds/rollback-union-find.md) |
| Li Chao Tree・李超线段树 | 直線の追加と、ある $x$ での最小値 | [Convex Hull Trick と Li Chao Tree](../dp/cht.md#li-chao-tree) |

**クエリの処理の工夫**

| 解説で見かける名前 | 何をするものか | ページ |
| --- | --- | --- |
| CDQ 分割統治・オフラインの分割統治 | 時刻で分割統治し、前半の更新が後半の質問に与える影響をまとめて数える | [CDQ 分割統治](../ds/cdq-divide-and-conquer.md) |
| 整体二分・parallel binary search | 全部の質問の二分探索を同時に進める | [並列二分探索](../ds/parallel-binary-search.md) |
| 時間付き Mo・ロールバック Mo | 更新つきの Mo、要素を出すのが難しい量の Mo | [Mo's algorithm](../ds/mo-algorithm.md#variants) |
| 木上の Mo・Mo on tree | 木のパスの質問に Mo を使う | [Mo's algorithm](../ds/mo-algorithm.md#mo-on-tree) |
| Offline Dynamic Connectivity・時間軸のセグ木 | 辺の追加と削除が混ざる連結判定を先読みで | [辺の追加と削除が混ざる連結性](../graph/offline-dynamic-connectivity.md#time-segment-tree) |
| 区間に辺を張るテク・セグ木グラフ | 区間の頂点すべてへの辺を $O(\log N)$ 本で表す | [区間に辺を張る](../graph/segment-tree-graph.md) |
| Dynamic DP・DDP | 値の更新のたびに DP の答えを行列のセグ木で求め直す | [動的 DP](../dp/dynamic-dp.md) |

**木のデータ構造**

| 解説で見かける名前 | 何をするものか | ページ |
| --- | --- | --- |
| Link-Cut Tree・LCT | 辺の追加・削除がある森のパスの質問 | [動的木](../tree/dynamic-tree.md#link-cut) |
| Euler Tour Tree・Top Tree | 辺の追加・削除がある森の部分木の質問 | [動的木](../tree/dynamic-tree.md#ett-top-tree) |
| Static Top Tree | 頂点の値の更新のたびに木 DP の根の値を求め直す | [Static Top Tree と木 DP の動的更新](../tree/static-top-tree.md) |
| HL 分解（HLD） | 木のパスを $O(\log N)$ 本の区間に分ける | [HL 分解](../tree/hld.md) |
| 点分治・重心分解 | 木のパスを重心で分割統治して数える | [重心分解](../tree/centroid-decomposition.md) |
| Virtual Tree・虚樹 | 指定した頂点と LCA だけの圧縮した木 | [Auxiliary Tree](../tree/auxiliary-tree.md) |
| クラスカル再構築木・KRT | Union-Find の併合の過程を木にする | [併合過程の木](../tree/merge-process-tree.md) |
| DSU on Tree・Sack | 重い子の結果を残して部分木の集合を作る | [マージテク](../tree/small-to-large.md#dsu-on-tree) |
| 長鎖分解 | 深さを添字にする木 DP を線形にする | [木の直径と最遠点](../tree/tree-diameter.md#long-path-decomposition) |

## 名前・何ができるか・代わりになる手の表 {#table}

この教材に独立のページがないデータ構造を並べた。$N$ は要素数、$C$ は値の範囲、$H \times W$ は盤面の大きさである。代わりの手の列は、先に考えるとよい軽い方法を書いた。

| 名前 | 何ができるか | 計算量 | 代わりになる手 |
| --- | --- | --- | --- |
| セグ木のマージ・分割 | 値を添字にした動的セグ木どうしを併合し、値の境目で 2 つに分ける | 併合は全体でならし $O(N \log C)$、分割は 1 回 $O(\log C)$ | [マージテク](../tree/small-to-large.md#subtree-merge)で set や BIT を併合（$O(N \log^2 N)$） |
| 2 次元セグ木（セグ木の入れ子） | 点の更新と長方形の集約を、逆元のない演算（最大値など）でもオンラインで答える | 1 回 $O(\log H \log W)$、メモリ $O(HW)$ | 更新がなければ[平面走査](../ds/sweep-line-2d.md)、和なら 2 次元 BIT や [CDQ 分割統治](../ds/cdq-divide-and-conquer.md#alternatives) |
| 2 次元 BIT | 座標が小さい盤面で、一点への加算と長方形の和 | 1 回 $O(\log H \log W)$、メモリ $O(HW)$ | 点を先に知っていれば[平面走査](../ds/sweep-line-2d.md#rectangle-count) |
| K-D tree | 多次元の点のうち長方形に入るものの探索、最も近い点の探索 | 構築 $O(N \log N)$、2 次元の長方形の集約は 1 回 $O(\sqrt{N})$（入る点を列挙するなら個数 $K$ の分 $+K$）、最近点は最悪 $O(N)$ | [平面走査](../ds/sweep-line-2d.md)、マンハッタン距離なら 45 度回転 |
| 併合可能なヒープ | 2 つのヒープを 1 つに併合する | 併合・追加・取り出しが $O(\log N)$ | [マージテク](../tree/small-to-large.md#why-log)で入れ直す（[次の節](#meldable-heap)） |
| Fast Set（64 分木） | $0$ 以上 $N$ 未満の整数の集合への追加・削除と、$x$ 以上の最小・$x$ 以下の最大 | どれも $O(\log_{64} N)$、メモリは $N/64$ 語ほど（全段で $N/63$ 語ほど） | `std::set`、削除しかないなら[次の空きへ飛ぶ Union-Find](../ds/union-find-applications.md#next-pointer) |
| Fractional Cascading | [マージソート木](../ds/merge-sort-tree.md)の各ノードの二分探索を、根での 1 回にまとめる | 区間の $x$ 以下の個数が $O(\log N)$（素朴なマージソート木は $O(\log^2 N)$） | [Wavelet Matrix](../ds/wavelet-matrix.md)、[永続セグ木](../ds/persistent-data-structures.md#prefix-versions) |
| 析合木（permutation tree） | 順列で、値が連続した範囲になる区間をすべて木で表す | 構築 $O(N \log N)$（線形の方法もある） | 区間の個数だけなら、最大値・最小値と遅延セグ木で数える |
| Kinetic Segment Tree | 各要素が一次関数 $a_i t + b_i$ で、$t$ を増やしながら区間の最小値（最大値）を答える | 取得と一点の更新は 1 回 $O(\log N)$、更新がなければ $t$ を進める操作は全体でならし $O(N \log^2 N)$ | 全体の最小なら [CHT・Li Chao Tree](../dp/cht.md#li-chao-tree)、更新がなければ各ノードに下側の包絡線を持つセグ木 |
| Sqrt Tree | 結合法則を満たす演算の、静的な列の区間の積 | 前計算 $O(N \log \log N)$、取得 $O(1)$ | [Disjoint Sparse Table](../ds/sparse-table.md#disjoint-sparse-table)（前計算 $O(N \log N)$、取得 $O(1)$）、[セグメント木](../ds/segment-tree.md) |

表の行のうち、仕組みの要点があると代わりの手を選びやすいものを補う。

**セグ木のマージ・分割**：要素ごとに値の位置だけを持つ動的セグ木（[動的セグメント木](../ds/segment-tree-on-values.md#dynamic-segment-tree)）を作り、2 本を根から同時に降りて、片方にしかない部分木はそのままつなぐ。両方にあるノードを訪れるたびにノードが 1 つ減るので、併合の手間の合計は最初に作ったノードの数（1 要素につき $O(\log C)$）で抑えられる。これがならし $O(N \log C)$ の根拠である。木の各頂点に部分木の値の集合を持たせる問題で使われる。同じ問題はマージテクで `set` や BIT を併合しても $O(N \log^2 N)$ で解けるので、まずそちらを考える。

**2 次元セグ木と 2 次元 BIT の違い**：2 次元 BIT は原点を角とする長方形の和を足し引きして任意の長方形を求めるので、引き算（[逆元](../guide/glossary.md#inverse-element)）のある演算でしか使えない（[2 次元 BIT](../ds/fenwick-tree.md#variants)）。最大値のように引けない演算で長方形を聞かれ、しかも更新が混ざるときに、2 次元セグ木が要る。座標が大きいときは、更新される点を先読みして各ノードの中を座標圧縮すると、メモリが $O(N \log N)$ に収まる。先読みできない（[オンライン強制](../guide/glossary.md#forced-online)）ときは、この圧縮ができず、CDQ 分割統治のような分割統治も使えない。このときは、内側の木を動的セグメント木にした入れ子が残る手になる（メモリは更新 1 回につき $O(\log H \log W)$）。

**K-D tree**：点を $x$ 座標の中央値で 2 つに分け、それぞれを $y$ 座標の中央値で分け、と軸を交互に変えて二分木にする。長方形の質問の $O(\sqrt{N})$ は、各ノードに和や個数を持たせて集約を答える、静的な 2 次元の場合の上限で、点の追加には作り直しの工夫が要る。最近点の探索は最悪 $O(N)$ で、それより速い保証はない。速いのは枝刈りが効く経験的な場合である。平面走査で済む問題に使う理由はほとんどない。

**Fast Set**：$0$ 以上 $N$ 未満の整数の有無を 64 bit の語に 1 bit ずつ詰め、「その語が 0 でないか」をさらに 1 段上の語に 1 bit ずつ詰める、という段を重ねる。$x$ 以上の最小の探索は、0 でない bit が見つかるまで段を上ってから下りる。上りと下りで段ごとに高々 2 語を見るので、段の数 $\lceil \log_{64} N \rceil$ の 2 倍ほどで終わる。$64^4 \approx 1.7 \times 10^7$ なので、$N \le 10^7$ なら 4 段で済む。`std::set` と同じ前後の要素の検索を、配列だけで定数倍よく行える。値の範囲が大きいときは座標圧縮が要る。

**析合木**：値が連続した範囲になる区間（連続段）が互いに入り組む形を、包含関係の木で表す。合点（子のどの連続する並びも連続段になる頂点）と析点（子の並び全体を除き、2 つ以上の連続する子の並びがどれも連続段にならない頂点）の 2 種類の頂点がある。「区間の最大値 $-$ 最小値 $=$ 区間の長さ $-1$」となる区間を数えるだけなら、右端を進めながら各左端の「最大値 $-$ 最小値 $-$（右端 $-$ 左端）」を単調スタックと[遅延セグメント木](../ds/lazy-segment-tree.md)で持ち、最小値 0 の個数を数えれば $O(N \log N)$ で済む。

**Kinetic Segment Tree**：各ノードに、今の $t$ で勝っている子と、部分木の中で次に勝ち負けが入れ替わる時刻（各ノードの入れ替わりの時刻の、部分木での最小値）を持たせる。$t$ を進めるときは、この時刻を過ぎた部分木だけを降りて作り直す。$t$ が減る方向には戻せない。$t$ を自由に聞かれ、更新がないなら、各ノードに区間の直線の下側の包絡線を持たせ、ノードごとに二分探索すれば 1 回 $O(\log^2 N)$ で答えられる。

自作したら、Library Checker で確かめられる。

- [Predecessor Problem](https://judge.yosupo.jp/problem/predecessor_problem)：$N$ 未満の非負整数の集合への追加・削除と、$k$ 以上の最小・$k$ 以下の最大（Fast Set）
- [Point Add Rectangle Sum](https://judge.yosupo.jp/problem/point_add_rectangle_sum)：重みつきの点の追加と長方形の和（2 次元のデータ構造。座標は $10^9$ まで）
- [Common Interval Decomposition Tree](https://judge.yosupo.jp/problem/common_interval_decomposition_tree)：順列から析合木を作って出力する

## 併合可能なヒープ（skew heap・leftist heap・ランダム化ヒープ。マージテクで足りることが多い） {#meldable-heap}

併合可能なヒープ（meldable heap）は、2 つの[優先度付きキュー](../ds/priority-queue.md)を $O(\log N)$ で 1 つにまとめられるヒープである。`std::priority_queue` は配列 1 本の二分ヒープなので、2 つをまとめるには片方の要素を 1 つずつ入れ直すしかない。併合可能なヒープは、節点をポインタ（配列の添字）でつないだ二分木にし、併合を基本の操作にする。追加は「1 要素のヒープとの併合」、最小の取り出しは「根を除いた左右の子の併合」になる。

| 名前 | 併合の計算量 | 仕組みの要点 |
| --- | --- | --- |
| skew heap | ならし $O(\log N)$ | 右の子へ降りて併合し、戻るたびに左右の子を入れ替える。木の深さの保証はない |
| leftist heap | 最悪 $O(\log N)$ | 各節点の dist（右の子をたどって空に着くまでの節点の数）が、左の子 $\ge$ 右の子になるように保つ |
| ランダム化ヒープ | 期待 $O(\log N)$ | 降りる子を毎回乱数で選ぶ |
| pairing heap（pb_ds の既定） | 併合は $O(1)$、取り出しはならし $O(\log N)$ | 根どうしをつなぐだけで併合し、整理は取り出しのときにまとめて行う |

**マージテクで足りるか**：多くの問題では、併合のたびに小さい方の要素を大きい方へ 1 つずつ入れ直す[マージテク](../tree/small-to-large.md#why-log)で間に合う。各要素が入れ直されるのは高々 $\log_2 N$ 回で、1 回 $O(\log N)$ なので、全体は $O(N \log^2 N)$ になる。$N = 2 \times 10^5$ なら $\log_2 N \approx 18$ で、$2 \times 10^5 \times 18^2 \approx 6.5 \times 10^7$ 回ほどである。併合可能なヒープが要るのは、これでも足りないときか、次のように全体への加算や永続化と組み合わせるときである。

- **最小有向全域木**：頂点ごとに入る辺をヒープに入れ、閉路を縮約するたびにヒープを併合する。閉路の頂点に入る辺の重みを一律に減らすので、全体に足す値（遅延の印）を持てるヒープを使うと $O(M \log N)$ になる（[最小有向全域木](../graph/spanning-tree-advanced.md#directed)）。
- **K 番目の最短路（Eppstein の方法）**：頂点ごとのヒープを、親のヒープを壊さずに作る。併合で通った節点だけを写す永続の leftist heap を使う（[K 番目の最短路](../graph/k-shortest-paths.md#yen-eppstein)）。
- **木の上の Slope Trick**：子の関数を表すヒープを親へ足し込む。片側のヒープだけで済む形なら、マージテクの $O(N \log^2 N)$ が併合可能なヒープで $O(N \log N)$ に下がる（[Slope Trick](../dp/slope-trick.md#on-trees)）。

leftist heap は、併合の再帰が右の背骨だけを降りることで速くなる。dist の条件から、節点数 $n$ のヒープの右の背骨は $\lfloor \log_2 (n + 1) \rfloor$ 個以下の節点しか持たない。併合は 2 本の右の背骨を合わせた長さしか降りないので、再帰の深さも $O(\log N)$ に収まる。skew heap は深さの保証がない。再帰で書くと、1 回の併合で再帰が深くなることがある。全体に足す値は、根に「子にまだ配っていない加算」として持ち、子へ降りる前に配る（[遅延評価](../guide/glossary.md#lazy-evaluation)）。

```cpp
--8<-- "advanced-ds-catalog/leftist-heap.cpp:core"
```

- **空の節点**：添字 0 を空とし、`dist[0] = 0` にしておくと、子が空の場合を分けずに書ける。
- **降ろす順**：`meld` で `rc[a]` を書き換える前と、`pop` で子を併合する前に `push` で保留の加算を配る。配る前に子を付け替えると、加算がほかの部分木に混ざる。
- **根の比較**：根の値は保留の加算を含んだ値にしておく（`add_all` で根の値にも足す）。そうすれば根どうしをそのまま比べられる。

全体への加算が要らないなら、GCC の拡張の pb_ds にある `__gnu_pbds::priority_queue` の `join` で済む。既定の pairing heap では `join` は $O(1)$ である。全体への加算はできないので、最小有向全域木のような使い方には向かない。

```cpp
--8<-- "advanced-ds-catalog/pbds-join.cpp:core"
```

## 確認問題 {#quiz}

??? question "確認問題：ヒープの全体への加算があるとき、併合可能なヒープを使わず、マージテクのまま `priority_queue` で併合できるか"
    できる。各ヒープに「全体に足した値」$d$ を 1 つ持ち、実際の値を「ヒープの中の値 $+ d$」とする。全体への加算は $d$ を変えるだけで済む。小さい方のヒープの要素を大きい方へ入れ直すときは、$d_{\text{小}} - d_{\text{大}}$ を足してから入れる。計算量はマージテクのまま $O(N \log^2 N)$ である。

??? question "確認問題：skew heap を再帰で書くと、何が困るか"
    skew heap は木の深さを保証せず、右の背骨が長くなることもある。ならしで $O(\log N)$ でも、1 回の併合で $O(N)$ 段を降りうる。再帰の深さが増え、スタックあふれを起こしうる。leftist heap（最悪の深さ $O(\log N)$）を使うか、ループで書く。

## 参考 {#references}

- [OI Wiki「线段树合并 & 分裂」](https://oi-wiki.org/ds/seg-merge-split/)：セグ木のマージの合計がならしで作ったノードの数に抑えられること、分割が 1 回 $O(\log N)$ であること（文章・図は使っていない）
- [OI Wiki「K-D Tree」](https://oi-wiki.org/ds/kdt/)：構築 $O(N \log N)$、2 次元の長方形の質問 $O(\sqrt{N})$、最近点の探索が最悪 $O(N)$ であること、追加のときの作り直し（文章・図は使っていない）
- [OI Wiki「析合树」](https://oi-wiki.org/ds/divide-combine/)：連続段・合点・析点の定義と、構築 $O(N \log N)$（線形の方法への言及も）（文章・図は使っていない）
- [OI Wiki「左偏树」](https://oi-wiki.org/ds/leftist-tree/)：leftist heap の dist の条件と、併合が最悪 $O(\log N)$ になる理由（文章・図は使っていない）
- [cp-algorithms「Randomized Heap」](https://cp-algorithms.com/data_structures/randomized_heap.html)：ランダム化ヒープの併合と期待 $O(\log N)$（文章は使っていない）
- [cp-algorithms「Sqrt Tree」](https://cp-algorithms.com/data_structures/sqrt-tree.html)：前計算 $O(N \log \log N)$・取得 $O(1)$ と、演算に要る条件（文章は使っていない）
- [Wikipedia「Skew heap」](https://en.wikipedia.org/wiki/Skew_heap)：skew heap の操作がならし $O(\log N)$ で、深さの保証がないこと
- [Wikipedia「Pairing heap」](https://en.wikipedia.org/wiki/Pairing_heap)：pairing heap の取り出しのならし $O(\log N)$ と、併合の $O(1)$
- [koosaga「Segment Tree Beats와 Kinetic Segment Tree」](https://koosaga.com/307)：Kinetic Segment Tree の操作（一次関数・区間の最小値・時刻を進める操作）と、更新がないときの全体 $O(N \log^2 N)$
- [maspypy「library: ds/fastset.hpp」](https://github.com/maspypy/library/blob/main/ds/fastset.hpp)：64 分木の段の持ち方と、メモリがおよそ $N/63$ 語であること
- [GCC「Policy-Based Data Structures: Design」](https://gcc.gnu.org/onlinedocs/libstdc++/manual/policy_data_structures_design.html)：pb_ds の `priority_queue` の既定が pairing heap で、`join` が $O(1)$ であること
- [yosupo06「library-checker-problems」](https://github.com/yosupo06/library-checker-problems)：検証に使う問題（predecessor_problem・point_add_rectangle_sum・common_interval_decomposition_tree）の内容
