---
id: modular-shortest-path
title: 剰余を頂点にする最短路
aliases: [同余最短路, 剰余グラフ, mod を頂点に]
type: overview
field: graph
chapter: 最短路
order: 200
level: 発展
kind: [最短路, 整数論]
prerequisites: [zero-one-bfs, extended-dijkstra]
related: [digit-and-mod]
summary: K で割った余りを頂点、数を作る操作を辺にした最短路で、K の倍数のうち桁和が最小のものや、いくつかの数の和で作れる数を求める。
complexity: 余りの数 K・操作の種類 n として、ダイクストラ法で O(nK log K)。重みが 0 と 1 だけなら 01-BFS で O(nK)
signs:
  - {type: phrase, text: K の倍数のうち桁和などが最小のもの}
  - {type: phrase, text: いくつかの数の和で作れる数の集合（硬貨の組合せ）}
  - {type: constraint, text: K が 10^5〜10^6 程度}
acl: []
frequency: C
frequency_evidence: recent 0・前提として届くページなし・古い ABC 0 問
sections:
  - {title: 余りを頂点、操作を辺にする, anchor: residue-vertices}
  - {title: 同余最短路（最小の数で割った余りごとの最小値）, anchor: congruence}
stage: reviewed
updated: 2026-10-29
---

!!! abstract "要点"
    - **何ができるか**：$K$ で割った余りを頂点、数を作る操作を辺にした最短路で、$K$ の倍数のうち桁和が最小のものや、いくつかの数の和で作れる数を求める。
    - **いつ使うか**：
        - $K$ の倍数のうち桁和などが最小のもの
        - いくつかの数の和で作れる数の集合（硬貨の組合せ）
        - $K$ が $10^5$〜$10^6$ 程度
    - **計算量**：余りの数 $K$・操作の種類 $n$ として、ダイクストラ法で $O(nK \log K)$。重みが 0 と 1 だけなら 01-BFS で $O(nK)$
    - **前提**：[01-BFS](../graph/zero-one-bfs.md)、[状態を頂点にする](../graph/extended-dijkstra.md)

<!-- textlint-disable -->
別名：同余最短路・剰余グラフ・mod を頂点に
<!-- textlint-enable -->

剰余を頂点にする最短路は、値そのものは巨大でも、気にする性質が「$K$ で割った余り」だけで決まるとき、$K$ 個の余りを頂点にして最短路を求める方法である。値を作る操作を辺、操作のコストを重みにすると、各余りに届く最小のコストが最短距離になる。いくつかの数の和で作れる数を、最小の数で割った余りごとに調べる型は、とくに同余最短路と呼ばれる。

## 余りを頂点、操作を辺にする {#residue-vertices}

数を 1 つずつ作っていく問題で、作った数をそのまま状態にすると状態が無限にある。答えに効くのが数の $K$ で割った余りだけなら、余りが同じ数は同じ状態とみなしてよい。状態は余り $0, 1, \dots, K-1$ の $K$ 個で済み、[状態を頂点にする](../graph/extended-dijkstra.md)最短路として解ける。

- **頂点**：余り $r$（$0 \le r < K$）。
- **辺**：操作で数 $x$ が $f(x)$ に変わり、$f(x) \bmod K$ が $x \bmod K$ だけで決まるなら、辺 $r \to f(r) \bmod K$ を張る。「1 を足す」「10 倍する」「$a$ を足す」はどれもこの形である。
- **重み**：操作のコスト。重みが非負ならダイクストラ法、0 と 1 だけなら [01-BFS](../graph/zero-one-bfs.md) を使う。

各頂点から出る辺は操作の種類 $n$ 本なので、辺は $nK$ 本である。ダイクストラ法で $O(nK \log K)$、01-BFS で $O(nK)$ になり、$K$ が $10^5$〜$10^6$ なら間に合う。

この帰着が正しいことは、2 つの向きで確かめる。1 つは「どの数も、それを作る手順のコストで、その余りの頂点に届く」ことである。もう 1 つは「グラフの経路はどれも、目的の量（例題なら桁和）がその経路のコスト以下である実際の数に対応する」ことである。後者が崩れると、グラフの最短距離が実際より小さくなる。[例題の ARC084 D](#arc084_b) では、1 を足すと繰り上がりで桁和の減ることがある。それでもコストを常に 1 と数えれば経路のコストは桁和以上になり、最短距離は桁和の最小と一致する。

## 同余最短路（最小の数で割った余りごとの最小値） {#congruence}

正の整数 $a_1, \dots, a_n$ を何個ずつでも（0 個でもよい）足して作れる数を調べる型である。$n = 2$ で互いに素なら、作れない最大の数は $a_1 a_2 - a_1 - a_2$ という公式がある（[ax + by で表せない最大の数](../math/gcd-properties.md#frobenius)）。3 種類以上には一般の公式がなく、同余最短路で求める。

$m = \min_i a_i$ とし、余り $r$（$0 \le r < m$）ごとに

$$
d[r] = \text{作れる数のうち、} m \text{ で割った余りが } r \text{ の最小値}
$$

と置く（作れなければ $\infty$）。すると、数 $x$ が作れるのは、ちょうど $x \ge d[x \bmod m]$ のときである。

- $x$ が作れるなら、$d$ の定義から $x \ge d[x \bmod m]$ である。
- 逆に $x \ge d[r]$（$r = x \bmod m$）なら、$x = d[r] + km$（$k \ge 0$）と書ける。$d[r]$ を作った和に $m$ を $k$ 個足せば $x$ になる。

$d$ は、頂点を余り $0, \dots, m-1$、辺を $r \to (r + a_j) \bmod m$（重み $a_j$）としたグラフで、頂点 0 からの最短距離である。$a_j$ を 1 個足すと値が $a_j$ 増え、余りが $a_j$ だけ進むからである。例として $a = (3, 5, 7)$ なら $m = 3$ で、次のグラフになる。

![3 で割った余り 0・1・2 を頂点にし、+5 の辺と +7 の辺を張ったグラフ。頂点 0 からの最短距離は d[0] = 0、d[2] = 5、d[1] = 7。太線は最短距離を決める辺](../img/modular-shortest-path/coins-3-5-7.svg)

最短距離は $d = (0, 7, 5)$ で、図の太線（0 から +5 で 2、0 から +7 で 1）がそれを決める辺である。余り 1 の数は 7 以上なら作れ、余り 2 の数は 5 以上なら作れる。作れない最大の数は $\max_r d[r] - m = 7 - 3 = 4$ で、実際に 4 は 3・5・7 の和で作れず、5 以上はすべて作れる。

$d$ が求まれば、ほかの問いも余りごとの式で答えられる。

- **閉区間 $[0, H]$ で作れる数の個数**：$d[r] \le H$ の各 $r$ について $\lfloor (H - d[r]) / m \rfloor + 1$ を足す。$[L, R]$ なら $[0, R]$ の個数から $[0, L-1]$ の個数を引く。
- **作れない最大の数**：$d$ に $\infty$ がなければ $\max_r d[r] - m$。$m = 1$（$a$ に 1 を含む）のときは $-1$ になり、すべての数が作れることを表す。$\infty$ があるのは $\gcd(a_1, \dots, a_n) > 1$ のときで、作れない数は無限にある。

$m$ に最小の数を選ぶのは、頂点数 $m$ が最も小さくなるからである。どの $a_j$ を法にしても同じ議論が成り立つ。$n = 2$ では $d[(kb) \bmod a] = kb$（$k = 0, \dots, a-1$）となり、$\max d - a = (a-1)b - a$ から公式 $ab - a - b$ が出る。

頂点 $m$ 個・辺 $nm$ 本なので、ダイクストラ法で $O(nm \log m)$ である（[前の節](#residue-vertices)の $K$ が $m$ にあたる）。ダイクストラ法の中心は次のとおりである（完全なプログラムは [`snippets/modular-shortest-path/congruence.cpp`](https://github.com/yuukougun/kyopro-atlas/blob/main/snippets/modular-shortest-path/congruence.cpp) で、個数制限なしのナップサックによる愚直な方法と比べている）。

```cpp
--8<-- "modular-shortest-path/congruence.cpp:core"
```

完全なプログラム：[`congruence.cpp`](https://github.com/yuukougun/kyopro-atlas/blob/main/snippets/modular-shortest-path/congruence.cpp)（GitHub）
{ .kp-code-src }

## ライブラリでの使い方 {#library}

ACL に専用の関数はなく、ダイクストラ法か 01-BFS をそのまま書けば足りる。グラフを隣接リストで作る必要もなく、頂点 $r$ から出る辺は、$a_j$ を順に見ながらその場で作れる。自作するときの要点は次のとおりである。

- **値の大きさ**：$d[r]$ は最大で $m \cdot \max_j a_j$ 程度になり、$m$ と $a_j$ が $10^5$ でも `int` を超える。`long long` で持つ。$\infty$ は数の比較だけに使い、$\infty$ に重みを足さない。コード片の $\infty$ は `1LL << 60` で（[INF の決め方](../cpp/cpp-types-literals.md#inf)）、$H$ はそれより大きいことがあるので、個数を数えるときは $\infty$ の余りを先に除く。
- **自己ループ**：$a_j$ が $m$ の倍数なら辺は自己ループになり、飛ばしてよい。
- **始点**：同余最短路では頂点 0（何も足さない和の 0）から始める。「正の倍数」のように 0 を除くときは、始点を最初の操作の後の頂点にする（ARC084 D では 1 から始める）。
- **個数の上限**：数え上げの答えは $H$ 程度まで大きくなるので、`long long` で足す。

Library Checker に同余最短路そのものを問う問題はない（2026-10 の問題の一覧で確かめた）。最短路の部分は [Shortest Path](https://judge.yosupo.jp/problem/shortest_path) でダイクストラ法を確かめ、同余最短路は上のコード片のように、小さい範囲で個数制限なしのナップサック（作れるかの DP）と比べて確かめる。

## 学ぶための資料 {#resources}

- [drken「AtCoder ABC 077 D - Small Multiple (ARC 084 D) (3D, 橙色, 700 点)」](https://drken1215.hatenablog.com/entry/2021/07/30/160000)：余りを頂点にして +1 と ×10 の辺で 01-BFS する流れが詳しい。
- [Heartlessly「题解 P2371 【[国家集训队]墨墨的等式】」](https://www.luogu.com.cn/article/7yfca7t0)（洛谷。中国語）：同余最短路（法を最小の数にし、$[L, R]$ の個数を数える）を式までまとめている。
- [OI Wiki「同余最短路」](https://oi-wiki.org/graph/mod-shortest-path/)（中国語）：跳楼机と ARC084 D を例に構成を説明し、練習の問題の一覧を載せている。ダイクストラ法を使わない方法として、数の種類ごとに、同じ数を足す辺が分ける閉路をそれぞれ 2 周して緩和する方法も載っている。数 1 種類あたり $O(m)$ なので、全体で $O(nm)$ になる。

## 例題 {#examples}

### ARC084 D. Small Multiple {#arc084_b}

<div class="kp-problems" data-role="example" markdown>

- [ARC084 D. Small Multiple](https://atcoder.jp/contests/arc084/tasks/arc084_b)（diff 2457）：K の正の倍数のうち、10 進表記の桁和の最小値を求める。

</div>

方針：どの正の整数も、1 から始めて「1 を足す」と「10 倍する」を繰り返して作れる。$K$ で割った余りを頂点にし、1 を足す辺 $r \to (r + 1) \bmod K$ を重み 1、10 倍する辺 $r \to 10r \bmod K$ を重み 0 にして、余り 1 から余り 0 への最短距離を 01-BFS で求める。

??? note "解法の詳細"
    - 始点は数 1 の余り 1 で、距離 1 から始める（桁和 1）。答えは余り 0 の距離である。頂点 $K$ 個・辺 $2K$ 本で、01-BFS により $O(K)$ になる。
    - **最短距離が桁和の最小以下である理由**：上から順に桁を $c_1, c_2, \dots, c_L$ とする数は、1 に 1 を $c_1 - 1$ 回足し、10 倍して $c_2$ 回足し、…と作れる。各桁は 9 以下なので繰り上がりは起きず、コストはちょうど桁和である。
    - **最短距離が桁和の最小以上である理由**：1 を足すと桁和は高々 1 しか増えず（繰り上がりでは減る）、10 倍しても桁和は変わらない。よって、コスト $c$ の経路で作った数の桁和は $c$ 以下である。余り 0 に届く経路は $K$ の正の倍数を作るので、その桁和以上のコストがかかる。
    - 2 つを合わせると、余り 0 への最短距離は $K$ の正の倍数の桁和の最小に一致する。

## 参考 {#references}

- [drken「AtCoder ABC 077 D - Small Multiple (ARC 084 D) (3D, 橙色, 700 点)」](https://drken1215.hatenablog.com/entry/2021/07/30/160000)：学ぶための資料。例題 ARC084 D の頂点・辺・重みと、1 を足す辺のコストを 1 としてよい理由
- [drken「AtCoder 版！蟻本 (初級編)」](https://qiita.com/drken/items/e77685614f3c6bf86f44)：例題 ARC084 D をグラフの最短路に帰着する問題として位置づけていること
- [Heartlessly「题解 P2371 【[国家集训队]墨墨的等式】」](https://www.luogu.com.cn/article/7yfca7t0)：学ぶための資料（中国語）。法を最小の数にすること、辺の張り方と、$[0, x]$ の個数を $\lfloor (x - d_i) / m \rfloor + 1$ の和で数えること
- [OI Wiki「同余最短路」](https://oi-wiki.org/graph/mod-shortest-path/)：学ぶための資料（中国語。文章・図は使っていない）。跳楼机と ARC084 D の構成、数の種類ごとに閉路を 2 周して緩和する方法（$O(nm)$ はこの方法から数えた計算量）
- [Library Checker「Shortest Path」](https://judge.yosupo.jp/problem/shortest_path)：最短路の部分の検証に使う問題
