---
id: chromatic-number
title: 彩色数・最大独立集合・最大クリーク
aliases: [彩色数, 頂点彩色, 最大クリーク, 一般グラフの最大独立集合, chromatic number, maximum independent set]
type: overview
field: graph
chapter: 基本と探索
order: 100
level: 発展
kind: [DP, 数え上げ]
prerequisites: [bit-dp, inclusion-exclusion]
related: [small-graph-brute-force, konig-theorem, meet-in-the-middle, bipartite-graph, subset-enumeration-dp]
summary: 一般グラフの彩色数・最大独立集合・最大クリークは NP 困難で、彩色数は包除原理で O(2^N N)、最大独立集合は N ≤ 40 程度なら分枝や半分全列挙で求める。二部グラフなら易しい。
complexity: 彩色数 O(2^N N)、最大独立集合・最大クリーク O(2^(N/2))（半分全列挙）または分枝でおよそ O(1.38^N)
signs:
  - {type: constraint, text: N ≤ 20〜40 の一般グラフで、独立集合・彩色・クリークを求める}
acl: []
verify: [chromatic_number, maximum_independent_set]
frequency: C
frequency_evidence: recent 0・前提として届くページなし・古い ABC 0 問
sections:
  - {title: 3 つの量の関係と難しさ, anchor: relations}
  - {title: 彩色数（包除原理で O(2^N N)）, anchor: chromatic-number}
  - {title: 最大独立集合（分枝・半分全列挙）, anchor: independent-set}
  - {title: 二部グラフなら König の定理, anchor: bipartite-case}
  - {title: 計算量と自作するときの要点, anchor: library}
stage: done
updated: 2026-10-29
---

!!! abstract "要点"
    - **何ができるか**：一般のグラフの彩色数（隣どうしを違う色にする塗り方の最少の色数）を包除原理で $O(2^N N)$ で、最大独立集合と最大クリークを $N \le 40$ 程度なら半分全列挙で $O(2^{N/2})$ か分枝で求める。どれも NP 困難だが、二部グラフなら易しい。
    - **いつ使うか**：$N \le 20$〜$40$ の一般グラフで、独立集合・彩色・クリークを求める。
    - **計算量**：彩色数 $O(2^N N)$（$N \le 20$ 程度）、最大独立集合・最大クリーク $O(2^{N/2})$（半分全列挙）または分枝でおよそ $O(1.38^N)$（$N \le 40$ 程度）
    - **前提**：[bitDP](../dp/bit-dp.md)、[包除原理](../comb/inclusion-exclusion.md)

<!-- textlint-disable -->
別名：彩色数・頂点彩色・最大クリーク・一般グラフの最大独立集合・chromatic number・maximum independent set
<!-- textlint-enable -->

彩色数・最大独立集合・最大クリークは、一般のグラフでは多項式時間の解き方が知られていない（[NP 困難](../guide/glossary.md#np-hard)）量である。そのため問題に出るときは頂点数が 20〜40 と小さく、頂点の集合を bit で表して指数時間で解く。グラフが二部グラフなら、マッチングや塗り分けで多項式時間に解ける。

## 3 つの量の関係と難しさ {#relations}

$N$ 頂点の単純な無向グラフ $G$ について、次の 3 つの量を考える。

- **最大独立集合** $\alpha(G)$：どの 2 頂点も辺で結ばれていない頂点の集まり（[独立集合](../guide/glossary.md#independent-set)）の、最大の大きさ。
- **最大クリーク** $\omega(G)$：どの 2 頂点も辺で結ばれている頂点の集まり（[クリーク](../guide/glossary.md#clique)）の、最大の大きさ。
- **彩色数** $\chi(G)$：隣り合う頂点が同じ色にならないように頂点を塗るときの、色の数の最小。同じ色の頂点の集まりは独立集合なので、「頂点全体を最少の個数の独立集合に分ける」と言い換えられる。

補グラフ（辺のある組とない組を入れ替えたグラフ）を $\overline{G}$ と書くと、$G$ の独立集合は $\overline{G}$ のクリークである。よって $\omega(G) = \alpha(\overline{G})$ で、最大クリークは補グラフの最大独立集合として求める。また独立集合の補集合は[頂点被覆](../guide/glossary.md#vertex-cover)なので、最小頂点被覆の大きさは $N - \alpha(G)$ である。

彩色数には次の下からの評価がある。クリークの頂点はすべて違う色が要るので $\chi(G) \ge \omega(G)$、各色は $\alpha(G)$ 個までしか塗れないので $\chi(G) \ge N / \alpha(G)$ である。等号は一般には成り立たない（5 頂点の閉路は $\omega = 2$ だが $\chi = 3$）。

難しさは色の数で分かれる。$\chi(G) \le 1$ は辺がないこと、$\chi(G) \le 2$ は二部グラフであることと同じで、どちらも $O(N + M)$ で判定できる。一方、3 色で塗れるかの判定はすでに NP 完全である。問題文に「3 色で塗る」とあっても、塗り方の数を数えるなら[小さいグラフの全探索](../graph/small-graph-brute-force.md#coloring)のように、隣と違う色だけを試す探索で済むことが多い。

## 彩色数（包除原理で O(2^N N)） {#chromatic-number}

彩色数は、$k = 1, 2, \dots$ の順に「$k$ 色で塗れるか」を判定し、初めて塗れた $k$ を答えにする。判定は「$k$ 個の独立集合で全体を覆う方法の数」が正かどうかで行う。

**覆う数と塗れることは同じ**：$k$ 色の塗り方があれば、色ごとの頂点の集まりは $k$ 個の独立集合で全体を覆う。逆に $k$ 個の独立集合 $I_1, \dots, I_k$（重なってよい・空でもよい）で全体を覆えたら、各頂点を「自分を含む $I_j$ のうち番号が最小のもの」の色に塗る。独立集合の部分集合はまた独立集合なので、これは正しい塗り方になる。

**包除原理で覆う数を数える**：$\mathrm{ind}(S)$ を「$S$ の部分集合のうち独立集合であるものの数（空集合を含む）」とする。$S$ の中だけで $k$ 個の独立集合を選ぶ方法は $\mathrm{ind}(S)^k$ 通りで、これは $k$ 個の和集合が $S$ に収まる組の数である。覆われない頂点の集合 $T = V \setminus S$ について[包除原理](../comb/inclusion-exclusion.md#general)を使うと、符号は $(-1)^{\lvert T \rvert}$ になり、和集合がちょうど $V$ になる組（全体を覆う組）の数は

$$
f(k) = \sum_{S \subseteq V} (-1)^{N - \lvert S \rvert} \, \mathrm{ind}(S)^k
$$

である。$\chi(G)$ は $f(k) > 0$ となる最小の $k$ である。

**$\mathrm{ind}(S)$ の求め方**：$S$ の最小の頂点 $v$ を選ばない場合と選ぶ場合に分ける。$v$ の隣の頂点の集合を $\mathrm{adj}[v]$ と書くと、$\mathrm{ind}(S) = \mathrm{ind}(S \setminus \lbrace v \rbrace) + \mathrm{ind}(S \setminus (\lbrace v \rbrace \cup \mathrm{adj}[v]))$ である。右辺の集合は $S$ より小さい整数になるので、$S$ を昇順に回せば $O(2^N)$ で全部求まる。独立集合の印に[高速ゼータ変換](../comb/zeta-mobius-subset.md)をかけても $O(2^N N)$ で求まる。

あとは $k$ ごとに $\mathrm{ind}(S)^k$ を前の $k$ の値に掛けて更新し、和を取る。$k$ が高々 $N$ なので全体の計算量は $O(2^N N)$ になる。$N = 20$ なら $2^{20} \times 20 \approx 2 \times 10^7$ 回ほどである。

```cpp
--8<-- "chromatic-number/chromatic.cpp:core"
```

完全なプログラム：[`chromatic.cpp`](https://github.com/yuukougun/kyopro-atlas/blob/main/snippets/chromatic-number/chromatic.cpp)（GitHub）
{ .kp-code-src }

$f(k)$ は最大で $2^{Nk}$ ほどの巨大な数なので、mod で計算する。mod の値は大小を比べられず、正の $f(k)$ の余りが偶然 0 になると「塗れない」と誤判定する。上のコード片は 2 つの素数で計算し、どちらかが 0 でなければ塗れるとしている（$f(k)$ は 0 以上なので、余りが 0 でなければ $f(k) > 0$ は確実である）。気になるなら法を乱択する。

部分集合の部分集合を回す $\mathrm{dp}[S] = \min_{T \subseteq S,\ T \text{ は独立}} \mathrm{dp}[S \setminus T] + 1$ で求める方法もあるが、$O(3^N)$ かかる（[部分集合を列挙する DP](../dp/subset-enumeration-dp.md#vs-zeta)）。$N = 20$ では $3^{20} \approx 3.5 \times 10^9$ で重い。

頂点全体をできるだけ少ないクリークに分ける問題は、補グラフの彩色数なので同じ方法が使える。[ABC187 F. Close Group](../dp/subset-enumeration-dp.md#abc187_f) はこの形で、$N \le 18$ なので $O(3^N)$ でも間に合う。

??? question "確認問題：辺のないグラフで $k = 1$ のとき"
    辺のない $N$ 頂点のグラフで $f(1)$ を計算すると、いくつになるか。

    ??? success "答え"
        どの部分集合も独立なので $\mathrm{ind}(S) = 2^{\lvert S \rvert}$ である。$f(1) = \sum_{S} (-1)^{N - \lvert S \rvert} 2^{\lvert S \rvert} = (2 - 1)^N = 1$ になる。全体を 1 つの独立集合で覆う方法は「全体を選ぶ」ただ 1 通りなので、数え方と合う。

## 最大独立集合（分枝・半分全列挙） {#independent-set}

最大独立集合は $N \le 40$ 程度まで求められる。$2^{40} \approx 10^{12}$ 通りの全探索は間に合わないので、次の 2 つのどちらかで減らす。最大クリークは補グラフに同じ関数を使えばよい。補グラフの隣接は、隣接の bit を反転して $N$ bit に絞り、自分を除いたもの（`~adj[v] & full & ~(1ULL << v)`、`full` は $N$ bit がすべて 1 の値）である。

以下、$\mathrm{adj}[v]$ は $v$ の隣の頂点の集合、$\mathrm{adj}[X]$ は $X$ のどれかの頂点に隣接する頂点の集合とする。

**半分全列挙**：頂点を前半 $A$ と後半 $B$ の 20 個ずつに分ける（[半分全列挙](../basics/meet-in-the-middle.md#combine-halves)）。

1. 後半の各部分集合 $Y \subseteq B$ について、$\mathrm{best}[Y]$ ＝ $Y$ の中の最大独立集合の大きさ を求める。$Y$ の最小の頂点 $v$ を選ばないなら $\mathrm{best}[Y \setminus \lbrace v \rbrace]$、選ぶなら $1 + \mathrm{best}[Y \setminus (\lbrace v \rbrace \cup \mathrm{adj}[v])]$ で、大きい方を取る。昇順に回せば $O(2^{N/2})$ である。
2. 前半の独立集合 $X \subseteq A$ ごとに、$X$ のどの頂点とも隣接しない後半の頂点の集合 $Y_X = B \setminus \mathrm{adj}[X]$ を求め、$\lvert X \rvert + \mathrm{best}[Y_X]$ の最大を答えにする。$X$ が独立かと $\mathrm{adj}[X]$ も、最小の頂点を 1 つ除いた集合から $O(1)$ で更新できる。

全体は $O(2^{N/2})$ で、$N = 40$ なら $2^{20} \approx 10^6$ 回の計算と $2^{20}$ 要素の配列が数本で済む。集合そのものも、$\mathrm{best}$ を達成した選び方を一緒に持てば復元できる。

```cpp
--8<-- "chromatic-number/mis.cpp:core"
```

完全なプログラム：[`mis.cpp`](https://github.com/yuukougun/kyopro-atlas/blob/main/snippets/chromatic-number/mis.cpp)（GitHub）
{ .kp-code-src }

**分枝**：残っているグラフで頂点 $v$ を 1 つ選び、「$v$ を取る（$v$ と隣を消す）」と「$v$ を取らない（$v$ を消す）」に分けて再帰する。工夫なしでは $2^N$ のままなので、次の規則で枝を減らす。

- 次数 0 か 1 の頂点 $v$ は分けずに取る。$v$ の隣 $u$ を含む最適解があっても、$u$ を $v$ に取り替えれば同じ大きさの独立集合になるからである。
- どの頂点も次数 2 以上なら、次数が最大の頂点で分ける。取らない枝は 1 個、取る枝は 3 個以上の頂点が消えるので、手間は $T(N) \le T(N-1) + T(N-3)$ で、およそ $1.47^N$（$N = 40$ で $4 \times 10^6$ ほど）になる。
- さらに次数がすべて 2 以下（パスと閉路の集まり）なら直接答えを出し、次数 3 以上の頂点だけで分けると $T(N) \le T(N-1) + T(N-4)$ で、およそ $1.38^N$ になる。

分枝は空間が $O(N)$ で済み、実際のグラフでは上の見積もりよりずっと速く終わることが多い。書きやすさは半分全列挙が上で、どちらでも Library Checker の $N \le 40$ は通る。

??? question "確認問題：次数 2 の頂点も分けずに取ってよいか"
    次数 0・1 の頂点は分けずに取ってよかった。次数 2 の頂点 $v$ でも同じことが言えるか。

    ??? success "答え"
        言えない。隣 $u$・$w$ の両方を含む最適解があると、$v$ に取り替えると 1 つ減る。たとえば $v$ の隣が $u$・$w$ だけで、$u$・$w$ がほかに隣を持たないパス $u - v - w$ では、最大独立集合は $\lbrace u, w \rbrace$ で $v$ を含まない。

## 二部グラフなら König の定理 {#bipartite-case}

グラフが二部グラフなら、3 つの量はどれも易しい。$N$ や $M$ が大きく、上の指数時間の方法が使えないときは、まず二部グラフかどうかを確かめる。

- **彩色数**：辺があれば 2、なければ 1 である。塗り方は [BFS・DFS で塗る](../graph/bipartite-graph.md#coloring)だけで求まる。
- **最大独立集合**：最大マッチングの大きさを $\nu$ とすると $\alpha(G) = N - \nu$ である（[König の定理と 3 つの関係](../graph/konig-theorem.md#theorem)）。最大流で $\nu$ を求め、集合そのものは最小カットから復元する。
- **最大クリーク**：二部グラフのクリークは辺 1 本か頂点 1 個なので、辺があれば 2 である。補グラフが二部グラフのときは、最大クリークが補グラフの最大独立集合になり、König の定理で求まる。

二部グラフでない一般のグラフで「$N - \nu$」を使うと誤る（三角形では $3 - 1 = 2$ になるが、正しくは 1）。一般のグラフで崩れる理由は [一般グラフでは難しい](../graph/konig-theorem.md#general-graph) にある。ほかに易しい形として、木なら最大独立集合を[木 DP](../dp/tree-dp.md#vertex-states) で $O(N)$ で求められる。

## 計算量と自作するときの要点 {#library}

ACL に対応する関数はない。自作するときの要点は次のとおりである。

- **集合を bit で持つ**：隣接を $\mathrm{adj}[v]$（隣の頂点の集合）で持つと、「$v$ と隣を除く」が `s & ~(1ULL << v) & ~adj[v]` の 1 回で済む。$N \le 40$ では `unsigned long long` を使う（32 bit で足りるなら `1 << v` でよい）。
- **最小の頂点の取り出し**：`__builtin_ctz(s)` で得る。64 bit なら `__builtin_ctzll(s)` を使う（`__builtin_ctz` は 32 bit に切り詰められる）。C++20 の `std::countr_zero` でもよい。$s$ を昇順に回せば、最小の頂点を除いた集合は必ず計算済みである。
- **メモリ**：彩色数は $2^N$ 要素の配列が 3 本（$N = 20$ で `long long` なら 24 MB ほど）、半分全列挙は $2^{N/2}$ 要素の配列が数本である。
- **mod の誤判定**：彩色数の $f(k)$ は mod で 0 になっても 0 とは限らない。法を 2 つ使うか乱択する。
- **$N = 0$ と辺のないグラフ**：彩色数は $N = 0$ なら 0、辺がなければ 1 である。$k$ を 1 から始めると $N = 0$ を取りこぼすので、先に返す。

自作した関数は Library Checker で確かめる。

- [Chromatic Number](https://judge.yosupo.jp/problem/chromatic_number)：$N \le 20$ の単純な無向グラフの彩色数を求める。
- [Maximum Independent Set](https://judge.yosupo.jp/problem/maximum_independent_set)：$N \le 40$ の単純な無向グラフの最大独立集合を 1 つ求める。

## 学ぶための資料 {#resources}

- [「Graph coloring」（英語版 Wikipedia）](https://en.wikipedia.org/wiki/Graph_coloring)：厳密なアルゴリズムの節に、包除原理と高速ゼータ変換による $O(2^N N)$ の判定（Björklund・Husfeldt・Koivisto）が載っている。それ以前の DP の計算量との比較もある。
- [「Independent set (graph theory)」（英語版 Wikipedia）](https://en.wikipedia.org/wiki/Independent_set_(graph_theory))：クリーク・頂点被覆との関係と、最大独立集合の厳密なアルゴリズムの計算量の到達点。
- [drken「AtCoder 版！蟻本 (中級編)」](https://qiita.com/drken/items/2f56925972c1d34e05d8)：半分全列挙の節で、一般グラフの最大独立集合が $n \le 40$ 程度なら半分全列挙で解けることと、より速い $O(1.381^n)$ の方法に触れている。

## 参考 {#references}

- [「Graph coloring」（英語版 Wikipedia）](https://en.wikipedia.org/wiki/Graph_coloring)：包除原理による $O(2^N N)$ の判定と、3 色の判定が NP 完全であること
- [「Independent set (graph theory)」（英語版 Wikipedia）](https://en.wikipedia.org/wiki/Independent_set_(graph_theory))：補グラフのクリーク・頂点被覆との関係、二部グラフで多項式時間になること
- [drken「AtCoder 版！蟻本 (中級編)」](https://qiita.com/drken/items/2f56925972c1d34e05d8)：最大独立集合を $n \le 40$ で半分全列挙で解く位置づけ
- [Library Checker「Chromatic Number」の問題定義（GitHub）](https://github.com/yosupo06/library-checker-problems/tree/master/graph/chromatic_number)：問題の内容と制約（$N \le 20$）
- [Library Checker「Maximum Independent Set」の問題定義（GitHub）](https://github.com/yosupo06/library-checker-problems/tree/master/graph/maximum_independent_set)：問題の内容と制約（$N \le 40$）
