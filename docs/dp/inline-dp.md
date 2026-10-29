---
id: inline-dp
title: インライン DP
aliases: [in-place DP, Inline DP, 配列を使い回して一括更新, 遅延セグ木 DP]
type: technique
field: dp
chapter: DP の高速化
order: 330
level: 青
kind: [DP, 区間クエリ]
prerequisites: [dp-segment-tree, lazy-segment-tree, knapsack-01]
related: [dp-dimension-reduction, lazy-segment-tree-patterns, global-offset#offset, lis, monotonic-stack#dp-transition]
summary: dp[i][*] から dp[i+1][*] へほとんどの値がそのまま写るとき、配列を 1 本だけ持って変わる場所だけを書き換える。一律の加算や区間加算は遅延セグメント木で、全体の平行移動は添字のずらしで表す。
complexity: 状態数 N・段数 K・変わる場所の数の合計 U として O(N + K + U)。範囲への加算と範囲の最大・最小を遅延セグメント木で行うなら O(N + (K + U) log N)
signs:
  - {type: shape, text: 'dp[i][*] から dp[i+1][*] で変わる場所が少ない'}
  - {type: shape, text: 遷移で dp 全体に一律の加算・平行移動が入る}
  - {type: shape, text: '区間 [l, r] の右端 r で、l 以降の位置の dp にまとめて加算する'}
acl: [lazy_segtree]
frequency: B
frequency_evidence: recent 1（abc480_g）・前提として届くページなし・古い ABC 3 問
sections:
  - {title: 2 次元の表で考えてから、行ごとに変わる場所を書き出す, anchor: diff-per-row}
  - {title: 変わる場所だけを更新する（辺を 1 本ずつ緩和する）, anchor: update-changes}
  - {title: 全体のシフトを添字のずらしで表す, anchor: global-shift}
  - {title: 区間加算と区間最大を遅延セグメント木で（区間の右端で加算する）, anchor: lazy-segment-tree}
  - {title: 単調スタックと組み合わせる, anchor: with-monotonic-stack, level: 黄}
stage: reviewed
updated: 2026-10-22
---

!!! abstract "要点"
    - **何ができるか**：$\mathrm{dp}[i][\ast]$ から $\mathrm{dp}[i+1][\ast]$ へほとんどの値がそのまま写るとき、配列を 1 本だけ持って変わる場所だけを書き換え、写しの手間を消す。一律の加算や区間加算は遅延セグメント木で、全体の平行移動は添字のずらしで表す。
    - **いつ使うか**：
        - dp\[i][\*] から dp\[i+1][\*] で変わる場所が少ない
        - 遷移で dp 全体に一律の加算・平行移動が入る
        - 区間 [l, r] の右端 r で、l 以降の位置の dp にまとめて加算する
    - **計算量**：状態数 $N$・段数 $K$・変わる場所の数の合計 $U$ として $O(N + K + U)$。範囲への加算と範囲の最大・最小を遅延セグメント木で行うなら $O(N + (K + U) \log N)$
    - **前提**：[セグメント木・スライド最小値による DP の高速化](../dp/dp-segment-tree.md)、[遅延セグメント木](../ds/lazy-segment-tree.md)、[ナップサック DP](../dp/knapsack-01.md)

<!-- textlint-disable -->
別名：in-place DP・Inline DP・配列を使い回して一括更新・遅延セグ木 DP
<!-- textlint-enable -->

インライン DP は、段の添字 $i$ を持つ 2 次元の DP 表を、1 本の配列（またはセグメント木）の上書きで計算する方法である。0-1 ナップサックの配列の使い回しと形は同じだが、目的はメモリではなく時間にある。各段で値が変わる場所だけに手を付けるので、段ごとに $N$ 個を写す $O(NK)$ の手間がなくなる。

## 2 次元の表で考えてから、行ごとに変わる場所を書き出す {#diff-per-row}

インライン DP は、いきなり 1 本の配列で考えずに、まず段の添字を持つ 2 次元の表 $\mathrm{dp}[i][j]$ で[状態](../guide/glossary.md#state)と[遷移](../guide/glossary.md#transition)を書くところから始める。そのうえで、行 $i$ から行 $i+1$ へ移るときに値が変わる場所を書き出す。

素朴に表を作ると、段数 $K$ と 1 行の大きさ $N$ の積 $O(NK)$ かかる。$N, K \le 2 \times 10^5$ なら $4 \times 10^{10}$ で間に合わない。ところが多くの問題では、1 行のうち変わるのは数か所で、残りは前の行の写し $\mathrm{dp}[i+1][j] = \mathrm{dp}[i][j]$ である。写しは 1 本の配列なら「何もしない」で済むので、変わる場所の数だけの手間になる。

次の図は、辺の列を順に見て、頂点 1 から各頂点への長さの最小を求める表である（[例題 ABC271 E](#abc271_e) と同じ形）。辺 $a \to b$ を見る行で変わりうるのは $\mathrm{dp}[k][b]$ の 1 か所だけで、ほかのマスは前の行の写しになる。

![2 次元の表 dp[k][v] の 5 行のうち、各行で値が変わりうるのは辺の行き先の 1 マスだけで、ほかは前の行の写しである。表は 1 本の配列 dist への書き換え（v=2 は ∞ から 3、v=3 は ∞ から 5、v=4 は ∞ から 6）に置き換えられる](../img/inline-dp/row-diff.svg)

図の k = 3 の行のように、調べても値が変わらないマスもある。1 本の配列にすると、書き換えの回数は行の数 $K$ 回だけになり、全体は初期化を合わせて $O(N + K)$ である。

行ごとの変化は、次の 4 つの形のどれかに分けて考えるとよい。形ごとに道具が決まる。

| 行の変化 | 1 本の配列での書き方 | 節 |
| --- | --- | --- |
| 少数の場所の値が変わる | その場所だけ書き換える | [変わる場所だけを更新する](#update-changes) |
| 全体に一律に $c$ を足す | 足した量を変数 1 つに持つ | [全体への操作を変数で持つ](../ds/global-offset.md#offset) |
| 全体が 1 つ右へずれる | 添字の読み替えを 1 つずらす | [全体のシフト](#global-shift) |
| ある範囲に一律に $c$ を足し、範囲の最大を読む | 遅延セグメント木の区間加算・区間最大 | [遅延セグメント木で](#lazy-segment-tree) |

1 本の配列で書き換えてよいかは、「同じ行で書き換えた値を、同じ行の計算で読むか」で決まる。読むなら、書き換える前の値を先に集めてから書き込むか、読む順序を工夫する（0-1 ナップサックで容量の大きい方から回すのはこの工夫である。[配列の使い回し](../dp/knapsack-01.md#dp-rolling-array)）。どちらにするかを決めるためにも、2 次元の表で式を書いておく。

## 変わる場所だけを更新する（辺を 1 本ずつ緩和する） {#update-changes}

いちばん基本の形は、各行で値の変わる場所が $O(1)$ 個のものである。図の例では、$\mathrm{dp}[k][v]$ を「辺の列の先頭 $k$ 本から部分列を選んでたどったとき、頂点 1 から $v$ へ行く長さの最小」とする。$k$ 本目の辺 $a \to b$（長さ $c$）を使うかどうかで場合分けすると、次の遷移になる。

$$
\mathrm{dp}[k][v] =
\begin{cases}
\min(\mathrm{dp}[k-1][b],\ \mathrm{dp}[k-1][a] + c) & (v = b) \\
\mathrm{dp}[k-1][v] & (v \ne b)
\end{cases}
$$

初期値を $\mathrm{dp}[0][1] = 0$、ほかを $+\infty$ とすると、答えは $\mathrm{dp}[K][N]$ である。$v \ne b$ の行は写しなので、1 本の配列 $\mathrm{dist}$ で $\mathrm{dist}[b] \leftarrow \min(\mathrm{dist}[b], \mathrm{dist}[a] + c)$ の 1 回の[緩和](../guide/glossary.md#relaxation)だけを行えばよい。

```cpp
--8<-- "inline-dp/relax-edges.cpp:core"
```

完全なプログラム：[`relax-edges.cpp`](https://github.com/yuukougun/kyopro-atlas/blob/main/snippets/inline-dp/relax-edges.cpp)（GitHub）
{ .kp-code-src }

この行で読むのは $\mathrm{dist}[a]$ で、書くのは $\mathrm{dist}[b]$ である。$a \ne b$ なら読む値は前の行のままなので、1 本の配列で正しい。$a = b$ でも、$c \ge 0$ なら値は変わらない。

同じ形は、値を添字にした DP にも現れる。[LIS](../dp/lis.md#binary-search) の二分探索版は「長さ $\ell$ の増加列の末尾の最小」を添字 $\ell$ の配列に持ち、要素を 1 つ読むたびに 1 か所だけを書き換える。重み付きの LIS をセグメント木で解くのも、1 点の更新と範囲の取得だけで行を進める同じ考え方である（[dp の値をセグメント木に載せる](../dp/dp-segment-tree.md#values-on-segment-tree)）。

**応用の型**：段 $i$ に「イベント」が 1 つずつ対応し、イベントのない状態は何も起きない（写し）。辺の列・盤の上の障害物・値の列の 1 要素などがイベントになる。変わる場所の数の合計が $U$ なら $O(N + K + U)$ で、イベントを段の順に並べるソートが要るなら $O(U \log U)$ が足される。

## 全体のシフトを添字のずらしで表す {#global-shift}

各行で「すべての状態が 1 つ隣へ移る」遷移は、値は変わらず位置だけが動く。1 本の配列 $a$ と時刻 $t$ を持ち、本当の値を

$$
\mathrm{dp}[t][v] = a[(v - t) \bmod N]
$$

と読み替える約束にすると、$t$ を 1 増やすだけで全体が 1 つ右へずれる。配列の中身は何も動かさない。[全体への加算をオフセットの変数で持つ](../ds/global-offset.md#offset)のと同じ考え方を、値ではなく添字に使ったものである。

例として、次の有向グラフで頂点 0 から $K$ 回移動する方法の数を求める（[例題 ABC372 F](#abc372_f) の形）。頂点 $0, 1, \dots, N-1$ が $v \to v+1$（$N-1 \to 0$）の辺で円環になり、ほかに追加の辺 $x_j \to y_j$ が $M$ 本ある。素朴な表は

$$
\mathrm{dp}[t+1][v] = \mathrm{dp}[t][v-1] + \sum_{j : y_j = v} \mathrm{dp}[t][x_j]
$$

で、1 行に $O(N + M)$ かかる。右辺の第 1 項は全体のシフトなので、添字のずらしでただになる。残るのは追加の辺による $M$ 個の足し込みだけで、1 行 $O(M)$、全体 $O(N + MK)$ になる。

```cpp
--8<-- "inline-dp/shift.cpp:core"
```

完全なプログラム：[`shift.cpp`](https://github.com/yuukougun/kyopro-atlas/blob/main/snippets/inline-dp/shift.cpp)（GitHub）。`mint` は ACL の `modint998244353`（[modint](../math/modint.md)）。
{ .kp-code-src }

足し込む値 $\mathrm{dp}[t][x_j]$ は、ずらす前の時刻 $t$ の値である。追加の辺どうしが $y_j = x_{j'}$ のようにつながっていると、先に書き込んだ値を後の辺が読んでしまう。そこで、すべての辺の読み出しを先に済ませ、それから書き込む。コードの 2 つのループはこのためにある。

**応用の型**：添字が時刻とともに一定の速さで動く状態（円環を回る・毎ターン全員が 1 歩進む・毎回 1 ずつ増える値）は、ずらしで写しにできる。全体への一律の加算も同時にあるなら、オフセットの変数をもう 1 つ持つ。逆向き（$v \to v - 1$）なら読み替えを $a[(v + t) \bmod N]$ にする。

## 区間加算と区間最大を遅延セグメント木で（区間の右端で加算する） {#lazy-segment-tree}

行の変化が「ある範囲の状態へ $c$ を一律に足す」形なら、1 本の配列を[遅延セグメント木](../ds/lazy-segment-tree.md)で置き換え、区間加算を 1 回 $O(\log N)$ で行う。遷移元の範囲の最大（最小）もそのまま読める。

代表は、0/1 の列を決めるとき、区間 $[l_j, r_j]$（閉区間、1-indexed）に 1 が 1 つ以上あれば得点 $a_j$ を得る問題である（[例題 EDPC W](#dp_w)）。状態を次のように置く。

- $\mathrm{dp}[i][j]$ ＝ 先頭 $i$ 文字を決め、最後に 1 を置いた位置が $j$（$0 \le j \le i$、$j = 0$ はまだ 1 がない）のときの、右端が $i$ 以下の区間による得点の最大

区間 $[l, r]$ に 1 があるかは、位置 $r$ まで決めた時点の「最後の 1 の位置 $j$」だけで決まる。$j \ge l$ なら 1 がある。だから得点は**区間の右端で**数える。左端の時点では、後で区間の中に 1 を置くかがまだ分からない。この状態で足りるのは、右端が $i$ より後の区間の得点が、$j$ と $i + 1$ 文字目以降の選び方だけで決まるからである。

行 $i - 1$ から行 $i$ への変化は次の 3 つである。

1. $i$ 文字目を 0 にする：$\mathrm{dp}[i][j] = \mathrm{dp}[i-1][j]$（$j < i$）。写しなので何もしない
2. $i$ 文字目を 1 にする：$\mathrm{dp}[i][i] = \max_{0 \le j < i} \mathrm{dp}[i-1][j]$。区間最大を 1 回読み、1 点に書く
3. 右端が $i$ の区間 $[l, i]$ ごとに、$l \le j \le i$ の $\mathrm{dp}[i][j]$ に $a$ を足す。区間加算を 1 回行う

初期値は $\mathrm{dp}[0][0] = 0$ で、答えは $\max_j \mathrm{dp}[N][j]$ である。2 を 3 より先に行う。$i$ 文字目に置いた 1 も、右端が $i$ の区間に含まれるからである。

```cpp
--8<-- "inline-dp/intervals.cpp:core"
```

完全なプログラム：[`intervals.cpp`](https://github.com/yuukougun/kyopro-atlas/blob/main/snippets/inline-dp/intervals.cpp)（GitHub）
{ .kp-code-src }

各位置で区間最大と 1 点の書き込みを 1 回ずつ、各区間で区間加算を 1 回行うので、全体 $O((N + M) \log N)$ である。

!!! info "ACL では"
    `lazy_segtree<S, op, e, F, mapping, composition, id> seg(v);` に区間加算・区間最大の[標準の型](../ds/lazy-segment-tree.md#acl-standard)（`op` は `max`、`e()` は $-\infty$、`mapping(f, x)` は $x + f$、`composition(f, g)` は $f + g$、`id()` は $0$）を渡す。`seg.apply(l, r, f)`・`seg.prod(l, r)`・`seg.set(p, x)` はどれも $O(\log N)$ で、区間は半開区間 $[l, r)$ である。問題の閉区間 $[l, r]$ は `apply(l, r + 1, a)` にする。

**応用の型**：「区間の中に条件を満たす要素が 1 つ以上ある」を、最後にその要素を置いた位置を状態にして、区間の右端で判定する。「最後に〇〇した位置」を添字にする DP は、遷移が「新しい位置へ全体の最大から移る」と「右端の区間で範囲に加算」の 2 つになりやすい。

## 単調スタックと組み合わせる {#with-monotonic-stack}

この節は黄の内容で、[単調スタック](../ds/monotonic-stack.md#procedure)を前提にする。

列を連続する区間に分け、区間ごとのコストの和を最小にする DP で、コストが区間の最大・最小で決まる形を扱う。例として、各区間のコストを $C + (\text{最大} - \text{最小})$ とする。

$$
\mathrm{dp}[i] = \min_{0 \le j < i} \bigl(\mathrm{dp}[j] + C + \max A[j, i) - \min A[j, i)\bigr)
$$

$i$ を 1 つ進めるたびに、始点 $j$ ごとの値 $g_i[j] = \mathrm{dp}[j] + \max A[j, i) - \min A[j, i)$ を遅延セグメント木に持つ。新しい要素 $A[i-1]$ が加わると、最大が変わる始点は「$A[i-1]$ 以下の値に最大を決められていた始点」だけである。

各 $i$ では、まず新しい始点 $i - 1$ に $\mathrm{dp}[i-1]$ を 1 点で書く（区間 $[i-1, i)$ は要素が 1 つなので最大 − 最小は 0 である）。最大の単調スタックには、値が狭義に減る順で添字を積む。スタックで $p$ の 1 つ下が $q$ なら、始点 $j \in (q, p]$ の区間の最大は $A[p]$ である。$p$ がスタックの底なら $q = -1$ とする。$A[i-1] \ge A[p]$ で $p$ を降ろすとき、その範囲の始点の最大は $A[p]$ から $A[i-1]$ へ上がる。そこで $[q + 1, p + 1)$ へ $A[i-1] - A[p]$ を区間加算する。最小も同じスタックをもう 1 本持てばよい。最後に $\mathrm{dp}[i] = \min_{j < i} g_i[j] + C$ を区間最小で読む。

各添字はスタックに 1 回積まれて 1 回降ろされるだけなので、区間加算は全体で $O(N)$ 回（ならし）で、全体 $O(N \log N)$ になる。

??? note "C++ の実装の中心（区間のコストが C + 最大 − 最小）"
    ```cpp
    --8<-- "inline-dp/stack-lazy.cpp:core"
    ```

    完全なプログラム：[`stack-lazy.cpp`](https://github.com/yuukougun/kyopro-atlas/blob/main/snippets/inline-dp/stack-lazy.cpp)（GitHub）
    { .kp-code-src }

区間の長さに下限 $L$ があるなら、最後に読む範囲を $[0, i - L + 1)$ に縮める。$i < L$ では読む範囲が空になり、`prod` は `e()` ＝ $+\infty$ を返す。これは行けない状態を表すので、そのまま木に書いてよい。後から足される量は最大 − 最小の幅までなので、あふれない。

コストが最大だけ（または最小だけ）なら、スタックを 1 本にすればよい。ただし「最大 × 長さ」のように長さに比例する項があると、$i$ を 1 進めるだけで、最大の変わらない始点の値も範囲ごとに違う量だけ増える。区間加算の回数がならしで $O(N)$ に収まらないので、この方法だけでは足りない。

**応用の型**：遷移のコストが「$j$ から $i$ までの最大・最小」を含み、遷移元 $j$ が $i$ より前のすべてにわたる。$O(N^2)$ の DP を書くと、$i$ を伸ばしたとき、$j$ ごとの値が範囲ごと一律に変わることが見える。

## 落とし穴 {#pitfalls}

- **同じ行で書き換えた値を読む**：同じ行の中で、ある場所を書き換えた後に、別の遷移がその場所の値を前の行の値のつもりで読むと誤る。[全体のシフト](#global-shift)の追加の辺どうしがつながっている場合や、盤の同じ行に障害物が複数ある場合に起きる。その行で読む値を先にすべて集めてから書き込む
- **減る変化を書き漏らす**：「変わる場所」は値が増える場所だけではない。たとえば前の行から真上にしか進めないマスが障害物でふさがれると、そのマスは到達できなくなる。2 次元の表の式を書き、写しでないマスをすべて挙げてから実装する
- **負の数の剰余**：添字のずらしの $(v - t) \bmod N$ を C++ の `(v - t) % n` で書くと、負の値になることがある。`((v - t) % n + n) % n` にする
- **遅延セグメント木の初期値**：まだ到達していない状態を $-\infty$ にするなら、その範囲に区間加算が届いても下限が崩れない大きさにする。[EDPC W](#dp_w) では、加算は位置 $i$ を書いた後にしか届かないので、$-2^{60}$ のままで足りる
- **書き込みと区間加算の順序**：[区間の右端で加算する](#lazy-segment-tree)とき、位置 $i$ への 1 点の書き込みを右端 $i$ の区間の加算より後で行うと、位置 $i$ の 1 が区間 $[l, i]$ で数えられない

## 使い分け {#comparison}

| 状況 | 使う手法 |
| --- | --- |
| 毎行ほぼすべての値が変わる | 行を 2 本で交互に使う（[配列の使い回し](../dp/knapsack-01.md#dp-rolling-array)） |
| 範囲の和から貰い、1 行を作り直す | [累積和による DP の高速化](../dp/dp-prefix-sum.md) |
| 1 点を更新し、範囲の最大・最小から貰う | [セグメント木・スライド最小値による DP の高速化](../dp/dp-segment-tree.md#values-on-segment-tree) |
| 前の行がほぼ写り、少数の点・範囲加算・シフトだけが入る | インライン DP（このページ） |
| どの行も同じ線形の遷移で、段数が巨大 | [行列累乗](../math/matrix-power.md) |

状態の次元そのものを減らす工夫は[状態の削減](../dp/dp-dimension-reduction.md)に、遅延セグメント木に載せる値と作用の設計は[遅延セグメント木の載せ方の型](../ds/lazy-segment-tree-patterns.md#design-steps)にまとめる。

## 例題 {#examples}

### ABC271 E. Subsequence Path {#abc271_e}

<div class="kp-problems" data-role="example" markdown>

- [ABC271 E. Subsequence Path](https://atcoder.jp/contests/abc271/tasks/abc271_e)（diff 1402）：辺の番号の列 E が与えられ、その部分列の順に辺をたどって都市 1 から都市 N へ行く経路の長さの最小を求める。

</div>

辺は有向で、$N, M, K \le 2 \times 10^5$ である。辺の列の先頭 $k$ 本までで状態を作ると、$k$ 本目の辺で変わりうるのはその辺の行き先の 1 か所だけである。[変わる場所だけを更新する](#update-changes)の 1 本の配列で、辺を列の順に 1 回ずつ緩和すればよい。

??? note "解法の詳細"
    $\mathrm{dist}$ を長さ $N$ の配列にし、$\mathrm{dist}[1] = 0$、ほかを $+\infty$ にする。$k = 1, \dots, K$ の順に、辺 $E_k = (A, B, C)$ について $\mathrm{dist}[B] \leftarrow \min(\mathrm{dist}[B], \mathrm{dist}[A] + C)$ とする。最後の $\mathrm{dist}[N]$ が答えで、$+\infty$ のままなら行けない（そのときの出力は問題の指定に従う）。辺の長さは $10^9$ まで、たどる辺は $K$ 本までなので、和は `long long` で持つ。全体 $O(N + M + K)$ である。

### ABC372 F. Teleporting Takahashi 2 {#abc372_f}

<div class="kp-problems" data-role="example" markdown>

- [ABC372 F. Teleporting Takahashi 2](https://atcoder.jp/contests/abc372/tasks/abc372_f)（diff 1722）：円環状の N 頂点と追加の M 本（≤ 50）の辺がある有向グラフで、頂点 1 から K 回移動する方法の数を求める。

</div>

$N, K \le 2 \times 10^5$ なので、時刻ごとに全頂点を作り直す $O((N + M)K)$ は間に合わない。円環の辺による移動は全体のシフトなので、[添字のずらし](#global-shift)で写しにする。各時刻に残る仕事は、追加の辺の $M$ 個の足し込みだけになる。

??? note "解法の詳細"
    頂点を 0-indexed にし、配列 $a$ と時刻 $t$ で $\mathrm{dp}[t][v] = a[(v - t) \bmod N]$ と読む。初めは $a[0] = 1$ である。各時刻で、まず追加の辺 $x_j \to y_j$ ごとに $\mathrm{dp}[t][x_j]$ を読んで控え、$t$ を 1 進めてから $\mathrm{dp}[t+1][y_j]$ の位置に控えを足す。$K$ 回の後、$a$ の総和が答えである（998244353 で割った余り）。読み出しを先に済ませるのは、追加の辺の行き先が別の追加の辺の出発点になりうるからである。全体 $O(N + MK)$ で、$MK \le 10^7$ である。

    頂点を「追加の辺の端点」だけに縮め、円環の区間を重み付きの辺にして DP する方法もある（参考の drken の記事）。

### EDPC W. Intervals {#dp_w}

<div class="kp-problems" data-role="example" markdown>

- [EDPC W. Intervals](https://atcoder.jp/contests/dp/tasks/dp_w)（diff —）：長さ N の 0/1 列の得点が、各区間 [l, r] に 1 が含まれれば a を足す形で決まるとき、得点の最大を求める。

</div>

得点 $a$ は負のこともある（すべて正なら全部を 1 にすればよい）。最後に 1 を置いた位置を添字にし、区間の得点は右端で数える。行ごとの変化は「新しい位置に全体の最大を書く」と「右端の区間の範囲へ一律に足す」なので、[区間加算と区間最大の遅延セグメント木](#lazy-segment-tree)で $O((N + M) \log N)$ になる。

??? note "解法の詳細"
    遅延セグメント木の添字を $0, \dots, N$ とし、添字 0 だけを 0、ほかを $-\infty$ で作る。区間を右端ごとに分けておく。$i = 1, \dots, N$ の順に、まず添字 $i$ に $[0, i)$ の最大を書き（$i$ 文字目を 1 にする）、次に右端が $i$ の区間 $[l, i]$ ごとに $[l, i + 1)$ へ $a$ を足す。最後に全体の最大が答えである。$N, M \le 2 \times 10^5$、$\lvert a \rvert \le 10^9$ なので、得点の和の絶対値は $2 \times 10^{14}$ までになり、`long long` で持つ。

## 練習問題 {#practice}

<div class="kp-problems" data-role="practice" markdown>

- [ABC203 E. White Pawn](https://atcoder.jp/contests/abc203/tasks/abc203_e)（diff 1750）：白いポーンが 1 行ずつ進み、黒いポーンのある列へは斜めにだけ進めるとき、最後の行で到達できる列の数を求める。
- [TDPC K. ターゲット](https://atcoder.jp/contests/tdpc/tasks/tdpc_target)（diff —）：数直線上に中心を持つ円の集合から、入れ子（次の円の内側にある）の鎖になるように選べる円の個数の最大を求める。

</div>

??? note "練習の方針"
    - **ABC203 E**：盤は $10^9$ 規模だが、黒いポーンのない行は到達できる列の集合が変わらない（写し）。黒いポーンのある行だけを行の順に処理し、到達できる列を `set` で持つ。黒いポーンのある列 $y$ は、前の行で $y - 1$ か $y + 1$ に到達できれば到達でき、そうでなければ到達できなくなる。同じ行の黒いポーンは、前の行の集合を読んで追加と削除を先に集め、まとめて反映する
    - **TDPC K**：円を区間に直してソートし、入れ子の鎖を減少列の最長として求める（[LIS の 2 次元の入れ子](../dp/lis.md#nesting)）。LIS の二分探索版は、要素を 1 つ読むたびに 1 か所だけを書き換えるインライン DP である

## 力試し {#challenge}

<div class="kp-problems" data-role="challenge" markdown>

- [ABC480 G. Zonal Score Minimization](https://atcoder.jp/contests/abc480/tasks/abc480_g)（diff 2100）：整数列を長さ 2 以上の連続する区間に分けるとき、各区間の最大値と最小値の差の和の最小を求める。

</div>

??? note "力試しの方針"
    - **ABC480 G**：[単調スタックと組み合わせる](#with-monotonic-stack)の DP を当てはめる。問題のコストと区間の長さの条件が節の例とどこで違うかを確かめ、節の DP のどこを変えるかを決める

## 確認問題 {#quiz}

??? question "確認問題：辺の列の代わりに、段ごとに辺の集合が与えられ、各段ではその中から高々 1 本を使えるとする。段の中の辺を 1 本の配列で順に緩和すると何が誤るか。どう直すか"
    段の中に辺 $a \to b$ と $b \to c$ があり、この順に緩和すると、後の辺は書き換え済みの $\mathrm{dist}[b]$ を読む。1 つの段で 2 本の辺を使った経路まで数えてしまう。直すには、段の中のすべての辺について、前の段の値から候補 $\mathrm{dist}[a] + c$ を先に集め、それから各行き先へ書き込む。書き込む回数は段の辺の数のままなので、計算量は変わらない。

??? question "確認問題：EDPC W の型で、区間の得点を左端で足さないのはなぜか"
    左端 $l$ の時点では、区間 $[l, r]$ の中に後で 1 を置くかどうかがまだ決まっていない。右端 $r$ の時点なら、最後に 1 を置いた位置 $j$ が $l$ 以上かどうかだけで決まり、それは状態の添字そのものなので、範囲 $[l, r]$ への区間加算で表せる。

??? question "確認問題：円環の辺が v → v − 1 の向きなら、添字のずらしはどう変わるか"
    全体が 1 つ左へずれるので、$\mathrm{dp}[t][v] = a[(v + t) \bmod N]$ と読む。$t$ を 1 増やすと、$\mathrm{dp}[t+1][v] = a[(v + t + 1) \bmod N] = \mathrm{dp}[t][v + 1]$ になり、頂点 $v + 1$ から $v$ への移動を表す。

## 参考 {#references}

- [かんプリン「競技プログラミング　典型問題メモ」](https://kanpurin.hatenablog.com/entry/2020/04/07/182948)：インライン DP の定義（更新する場所が限られるとき配列を使い回す）と問題の一覧
- [drken「LIS でも大活躍！ DP の配列使いまわしテクニックを特集」](https://qiita.com/drken/items/68b8503ad4ffb469624c)：配列の使い回しから in-place 化してセグメント木に載せる流れと、EDPC W の位置づけ
- [Kazun「AtCoder Beginner Contest 271 E問題 Subsequence Path」](https://kazun-kyopro.hatenablog.com/entry/ABC/271/E)：例題 abc271_e の状態・遷移・制約と、変わる場所が 1 か所である点
- [drken「AtCoder ABC 372 F - Teleporting Takahashi 2」](https://drken1215.hatenablog.com/entry/2024/09/22/030233)：例題 abc372_f の設定・制約と、頂点を縮める別解
- [KCPC「【ABC372】KCPCブログを開設しました！」](https://kcpc.hatenablog.com/entry/2024/09/22/201128)：abc372_f を配列のずらしで解く考え方と、更新後の値を読む誤り
- [Series_205「Educational DP Contest (EDPC) T ~ W 問題 解説」](https://qiita.com/Series_205/items/7d2c57b45179006d0bc6)：例題 dp_w の状態・遷移と区間の右端での加算
- [drken「EDPC (Educational DP Contest) W - Intervals」](https://drken1215.hatenablog.com/entry/2021/08/11/005634)：例題 dp_w の制約（$a$ は負になりうる）と、すべて非負なら全部 1 が最適である点
- [かんプリン「ABC203 E - White Pawn」](https://kanpurin.hatenablog.com/entry/2021/05/31/041904)：練習 abc203_e の状態と、黒いポーンのある行だけを更新する方針
- [kmjp「AtCoder ABC #480 : Div1 G Zonal Score Minimization」](https://kmjp.hatenablog.jp/entry/2026/10/17/0930)：力試し abc480_g の DP と、単調スタックで区間加算する範囲
- [AtCoder Library「Lazy Segtree」（document_ja）](https://github.com/atcoder/ac-library/blob/master/document_ja/lazysegtree.md)：`lazy_segtree` の引数と計算量
