---
id: interval
title: 区間
aliases: [連続部分列, 部分配列, subarray, 区間の集合, interval]
type: pattern
field: patterns
order: 10
level: null
kind: [案内, 区間クエリ, 累積和・差分]
prerequisites: []
related: [prefix-sum, prefix-sum-counting, two-pointers, contribution, monotonic-stack, dp-sequence-partition, interval-dp, imos, fenwick-tree, segment-tree, lazy-segment-tree, sparse-table, difference-sequence, offline-queries, mo-algorithm, interval-scheduling, interval-set, event-sort, sweep-line-2d, subsequence-and-substring]
summary: 連続部分列や与えられた区間の集合が出てくる問題で、問われ方から使う手法を引ける。連続部分列を数える・選ぶ、区間に操作して質問する、区間の集合を選ぶ・つなぐ、の3つの型に分ける。
complexity: null
signs:
  - {type: phrase, text: 和が K（K の倍数）になる連続部分列の個数}
  - {type: phrase, text: すべての連続部分列についての最小値・最大値・2 番目の値の総和}
  - {type: phrase, text: 'N 個の区間 [L_i, R_i] から重ならないように最大何個選べるか'}
  - {type: phrase, text: 区間を塗るたびに、塗られていない長さや個数を答える}
  - {type: phrase, text: 区間に含まれる異なる値の個数を多数答える}
acl: []
sections:
  - {title: 題材の性質, anchor: properties}
  - {title: 問われ方と手法の一覧, anchor: overview}
  - {title: 区間の和 → 累積和（prefix-sum）, anchor: sum}
  - {title: 和が K・K の倍数の区間の個数 → 累積和と連想配列（prefix-sum-counting）, anchor: count-by-sum}
  - {title: 伸び縮みで単調な条件 → 尺取り法（two-pointers）, anchor: monotone-window}
  - {title: '全区間の最小値・最大値の総和 → 寄与と単調スタック（contribution, monotonic-stack）', anchor: sum-over-subarrays}
  - {title: '全区間の中央値・mex・転倒数 → 題材別の各ページ（kth-and-median, mex, permutation）', anchor: other-statistics}
  - {title: 列を区間に区切る方法の数・最適値 → 区間分割 DP（dp-sequence-partition）, anchor: partition}
  - {title: 縮めながら取り除く・隣どうしを合体させる → 区間 DP（interval-dp）, anchor: shrink-and-merge}
  - {title: 加算をまとめて最後に見る → いもす法（imos）, anchor: batch-add}
  - {title: '更新と質問が交互 → BIT・セグメント木（fenwick-tree, segment-tree）', anchor: online-updates}
  - {title: 値が変わらない列の区間の最小値 → Sparse Table（sparse-table）, anchor: static-min}
  - {title: 区間に ±1 する操作の回数・可否 → 差分列への言い換え（difference-sequence）, anchor: difference}
  - {title: '区間の種類数・x 以下の個数 → 先読みと BIT、Mo（offline-queries, mo-algorithm）', anchor: offline}
  - {title: 重ならない最大個数・すべてを串刺しにする点の数 → 区間スケジューリング（interval-scheduling）, anchor: scheduling}
  - {title: 区間の和集合・塗りつぶし・残りの長さ → 区間を set で管理（interval-set）, anchor: union}
  - {title: '含まれる・交差する区間の数 → イベントソート・平面走査（event-sort, sweep-line-2d）', anchor: containment}
  - {title: 数列ではなく文字列の連続部分 → 部分列と部分文字列（subsequence-and-substring）, anchor: substrings}
stage: reviewed
updated: 2026-10-22
---

!!! abstract "要点"
    - **何のページか**：連続部分列や与えられた区間の集合が出てくる問題で、問われ方から使う手法を引ける。連続部分列を数える・選ぶ、区間に操作して質問する、区間の集合を選ぶ・つなぐ、の 3 つの型に分ける。
    - **いつ使うか**：
        - 和が K（K の倍数）になる連続部分列の個数。
        - すべての連続部分列についての最小値・最大値・2 番目の値の総和。
        - N 個の区間 [L_i, R_i] から重ならないように最大何個選べるか。
        - 区間を塗るたびに、塗られていない長さや個数を答える。
        - 区間に含まれる異なる値の個数を多数答える。
    - **使い方**：3 つの型のどれかを決め、[一覧の表](#overview)で問われ方の行を探す。行の節で言い換えを確かめてから手法のページへ進む。
    - **計算量**：手法による。累積和は前計算 $O(N)$ で 1 回 $O(1)$、更新ありの区間の質問は 1 回 $O(\log N)$
    - **前提**：なし

<!-- textlint-disable -->
別名：連続部分列・部分配列・subarray・区間の集合・interval
<!-- textlint-enable -->

区間は、列の連続した一部分、または数直線上の範囲である。問題に出てくる形は多いが、「2 つの端点の組」と見る言い換えと、「片方の端を固定する」考え方が多くの手法の共通の出発点になる。

## 題材の性質 {#properties}

ここでは列を 0-indexed で $A = (a_0, \dots, a_{N-1})$ と書き、区間は[半開区間](../guide/glossary.md#half-open-interval) $[l, r)$（$0 \le l < r \le N$）で表す。問題文の 1-indexed の閉区間 $[L, R]$ は、0-indexed の $[L-1, R)$ にあたる。

- **区間の数**：空でない区間は $N(N+1)/2$ 個ある。$N = 2 \times 10^5$ なら約 $2 \times 10^{10}$ 個で、すべてを列挙すると間に合わない。数える・最大を取る問題は、区間を列挙せずにまとめて扱う
- **区間は端点の組**：先頭 $k$ 個の和を $S_k$（$S_0 = 0$）とすると、$[l, r)$ の和は $S_r - S_l$ である。区間の性質が「2 つの位置の値の差」に言い換わると、区間を数える問題が「位置の組を数える」問題になる
- **片方の端を固定する**：右端 $r$ を決めると、残りは左端 $l$ の選び方だけになる。$r$ を左から動かしながら、それまでの $l$ の情報を連想配列や BIT にためれば、全体を $O(N)$ や $O(N \log N)$ で数えられる
- **区間は平面の点**：区間 $[l, r)$ を点 $(l, r)$ と見ると、すべての区間は $l < r$ の三角形の領域に並ぶ。区間の条件は、この領域の中の範囲の条件になる

次の図は $N = 6$ のすべての区間を点 $(l, r)$ として並べたものである。

![N = 6 の区間 [l, r) を点 (l, r) として並べると、l < r の三角形に 21 個が並ぶ。A = (1, 3, 2, 4, 5, 0) で A[2] = 2 が最小になる区間は l が 1〜2、r が 3〜5 の長方形の 6 個になる。右端 r = 6 を固定した区間は 1 行に並ぶ](../img/interval/subarrays-as-points.svg)

図の長方形は、$a_2 = 2$ が最小値になる区間である。2 より小さい値の位置で最も近いものは、左では位置 0（値 1）、右では位置 5（値 0）である。そのため左端を $\{1, 2\}$ から、右端を $\{3, 4, 5\}$ から独立に選べる。条件が端点ごとに分かれると、領域は長方形になり、個数は積で求まる。点線の行は右端を固定した区間である。累積和と尺取り法は、この行ごとに数える。

与えられた区間の集合を扱うときは、区間を端点でソートするのが出発点になる。右端の順に並べると選ぶ問題の貪欲が、左端の順に並べるとつなぐ問題の走査が、端点を「始まり」と「終わり」の出来事に分けると数える問題の走査が書ける。

??? question "確認問題：長さがちょうど k の区間は、図のどこに並ぶか"
    $r - l = k$ の点なので、対角線に平行な 1 本の斜めの列に並ぶ。$l = 0, 1, \dots, N - k$ の $N - k + 1$ 個である。固定長の窓をずらす問題は、この斜めの列を順に見ることにあたる。

## 問われ方と手法の一覧 {#overview}

問題文の形から行を探し、行の節で言い換えを確かめてから手法のページへ進む。代表の問題は、このページの[練習問題](#practice)に載せたものだけを書いた。ほかの問題は行き先のページの例題・練習にある。

**連続部分列を数える・選ぶ**：列の連続部分列そのものが問われる。

| よく出る問われ方 | 使う手法 | ページ | 代表の問題 |
|---|---|---|---|
| 区間の和を何度も求める | 累積和の差 | [累積和](../basics/prefix-sum.md#half-open) | ABC265 D |
| 和が K・K の倍数の区間の個数 | 累積和の値を連想配列で数える | [累積和と連想配列で区間を数える](../basics/prefix-sum-counting.md#equal-k) | — |
| 和が K 以下・種類数が K 以下の区間の数・最長 | 尺取り法 | [尺取り法](../basics/two-pointers.md#two-types) | — |
| 全区間の最小値・最大値の総和、最大長方形 | 寄与と単調スタック | [単調スタック](../ds/monotonic-stack.md#contribution) | ABC189 C |
| 全区間の中央値・mex・転倒数 | 答えの二分探索・主客転倒など | 題材別の各ページ（[節](#other-statistics)） | — |
| 列を区間に区切る方法の数・最適値 | 区間分割 DP | [区間分割 DP](../dp/dp-sequence-partition.md#last-block) | — |
| 隣どうしの合体・取り除くと両隣がくっつく | 区間 DP | [区間 DP](../dp/interval-dp.md#split-point) | — |
| 文字列の連続部分 | [部分文字列](../guide/glossary.md#substring)の手法 | [部分列と部分文字列](../patterns/subsequence-and-substring.md#overview) | — |

**区間に操作して質問する**：列の区間に加算・代入をして、値や区間の和を問われる。

| よく出る問われ方 | 使う手法 | ページ | 代表の問題 |
|---|---|---|---|
| 区間加算をすべて終えてから値を見る | いもす法 | [いもす法](../basics/imos.md#imos-1d) | — |
| 更新と区間の質問が交互に来る | BIT・セグメント木 | [BIT](../ds/fenwick-tree.md#what-it-does)、[セグメント木](../ds/segment-tree.md#what-it-does)、[遅延セグメント木](../ds/lazy-segment-tree.md#what-it-does) | — |
| 値が変わらない列の区間の最小値 | Sparse Table | [Sparse Table](../ds/sparse-table.md#what-it-does) | — |
| 区間に ±1 する操作の最小回数・可否 | 差分列 | [差分列](../basics/difference-sequence.md#min-operations) | — |
| 区間の種類数・x 以下の個数を多数 | クエリの先読みと BIT、Mo | [クエリの先読み](../ds/offline-queries.md#distinct-count)、[Mo's algorithm](../ds/mo-algorithm.md#what-it-does) | — |

**区間の集合を選ぶ・つなぐ**：$[L_i, R_i]$ の形の区間がいくつも与えられる。

| よく出る問われ方 | 使う手法 | ページ | 代表の問題 |
|---|---|---|---|
| 重ならない最大個数・全部を突く点の数 | 右端の順の貪欲 | [区間スケジューリング](../basics/interval-scheduling.md#why-right-end) | — |
| 和集合・塗りつぶし・残りの長さ | 区間を set で管理 | [区間を set で管理](../ds/interval-set.md#applications) | — |
| 含まれる・交差する区間の数、2 つの区間の組合せ | イベントソート・平面走査 | [イベントソート](../basics/event-sort.md#make-events)、[平面走査](../ds/sweep-line-2d.md#intervals-as-points) | ABC457 E |

問題へのリンクは、[練習問題](#practice)の囲みにある。

## 区間の和 → 累積和（prefix-sum） {#sum}

区間の和は、先頭からの和の差で求まる。0-indexed で $S_0 = 0$、$S_{k+1} = S_k + a_k$ とすると、$[l, r)$ の和は $S_r - S_l$ で、前計算 $O(N)$、1 回 $O(1)$ である。$S_0$ を置くので、左端が 0 の区間も場合分けせずに書ける。添字の決め方は[累積和の半開区間の約束](../basics/prefix-sum.md#half-open)にある。

和が決まった値になる区間を探す問題も、差の形に直すと「$S_r = S_l + K$ となる $S_l$ があるか」になる。値がすべて正なら $S$ は狭義に増えるので、値から位置が 1 つに決まり、二分探索や集合で探せる。円環の区間は列を 2 周分に伸ばしてから累積する（[円環は 2 周分に伸ばす](../basics/prefix-sum.md#circular)）。

## 和が K・K の倍数の区間の個数 → 累積和と連想配列（prefix-sum-counting） {#count-by-sum}

和がちょうど $K$ の区間の個数は、[区間の和](#sum)の言い換えで $S_l = S_r - K$（$l < r$）となる組の個数になる。右端 $r$ を左から動かし、それまでに出た $S_0, \dots, S_{r-1}$ の値ごとの個数を連想配列に記録すれば、各 $r$ の相手は 1 回の検索で数えられる。全体で $O(N \log N)$（ハッシュなら期待 $O(N)$）である。最初に $S_0 = 0$ を 1 個入れておかないと、左端が 0 の区間を落とす。手順は[累積和と連想配列で区間を数える](../basics/prefix-sum-counting.md#equal-k)にある。

和が $M$ の倍数の区間は、差が 0 であることを余りの一致 $S_r \bmod M = S_l \bmod M$ に直し、余りごとの個数を数える（[余りが等しい組](../basics/prefix-sum-counting.md#same-remainder)）。値が負でも使えるのがこの方法の利点で、負の余りは $0$ 以上 $M$ 未満に直してから数える。

## 伸び縮みで単調な条件 → 尺取り法（two-pointers） {#monotone-window}

「和が $K$ 以下」「種類数が $K$ 以下」のように、条件を満たす区間の内側の区間も条件を満たすなら、左端 $l$ を右へ進めても、条件を満たす最大の右端 $r(l)$ は左へ戻らない。この単調性があれば、2 つの端を合わせて $O(N)$ 回だけ動かして、すべての $l$ の $r(l)$ が求まる。満たす区間の数は $r(l) - l$ の和、最長の長さは $r(l) - l$ の最大である。逆に「和が $K$ 以上」のように外側の区間も満たす型では、満たす最小の右端を求める。2 つの型の区別は[尺取り法の 2 つの型](../basics/two-pointers.md#two-types)にある。

値に負の数があると、和の条件は縮めても保たれず、$r(l)$ が単調でなくなる。そのときは累積和の差で、右端を固定して左端を数える。和がちょうど $K$ なら[和が K の区間の個数](#count-by-sum)と同じく連想配列で、$K$ 以下・以上なら $S_l \ge S_r - K$ のような大小の条件になるので、累積和を座標圧縮して BIT で $O(N \log N)$ で数える（[負の値があるとき](../basics/two-pointers.md#negative-values)）。

## 全区間の最小値・最大値の総和 → 寄与と単調スタック（contribution, monotonic-stack） {#sum-over-subarrays}

すべての区間の最小値の和は、区間を列挙せずに「各 $a_i$ が何個の区間で最小値になるか」を数えて、$a_i \times \text{個数}$ を足す（[寄与](../thinking/contribution.md#max-min-count)）。左で初めて $a_i$ より小さい値が出る位置を $L_i$、右を $R_i$ とすると（なければ $-1$ と $N$）、個数は $(i - L_i)(R_i - i)$ である。[題材の性質](#properties)の図の長方形がこの個数にあたる。$L_i$・$R_i$ は、[単調スタック](../ds/monotonic-stack.md#contribution)を使えば全体 $O(N)$ で求まる。

同じ値があると、最小値をとる要素が区間に 2 つ以上あって二重に数える。片側を「より小さい」、もう片側を「以下」で止めて、代表を 1 つに決める。2 番目に大きい値の和は、自分より大きい値を区間にちょうど 1 つ含む区間を数えるので、左右それぞれ 2 つ先までの大きい値の位置を使う（[寄与のページ](../thinking/contribution.md#max-min-count)）。

「区間の長さ × 区間の最小値」の最大は、ヒストグラムの最大長方形と同じ形である。各 $a_i$ を高さとして、$a_i$ が最小のまま広げられる幅 $R_i - L_i - 1$ を掛ければよい（[ヒストグラムの最大長方形](../ds/monotonic-stack.md#histogram)）。

## 全区間の中央値・mex・転倒数 → 題材別の各ページ（kth-and-median, mex, permutation） {#other-statistics}

最小値・最大値以外の統計量は、要素ごとの寄与に分けにくい。統計量ごとに次の言い換えを使う。

- **中央値**：「中央値が $x$ 以上か」は、$x$ 以上を $+1$、未満を $-1$ にした列の和の符号で判定できる。$x$ を二分探索し、各 $x$ で条件を満たす区間を累積和で数える（[中央値の言い換え](../basics/fractional-binary-search.md#median)、全区間の中央値の中央値は[転倒数で数える](../basics/fractional-binary-search.md#median-of-medians)）。題材の全体は [K 番目と中央値](../patterns/kth-and-median.md#overview)にある
- **mex**：全区間の mex の総和は、「mex が $k$ 以上の区間の数」を $k = 1, 2, \dots$ について足す主客転倒で数える。mex が $k$ 以上であることは、区間が $0, \dots, k-1$ をすべて含むことと同じである（[mex](../patterns/mex.md#sum-of-mex)）
- **転倒数**：窓を 1 つずらしたときの転倒数の増減は、出入りする要素より大きい・小さい要素の個数で直せる（[窓を伸縮しながら転倒数を増減する](../ds/inversion-number.md#sliding-window)）。順列についての問われ方は[順列](../patterns/permutation.md#overview)にある

## 列を区間に区切る方法の数・最適値 → 区間分割 DP（dp-sequence-partition） {#partition}

列をいくつかの連続部分に区切り、どの部分も条件を満たす区切り方の数や、部分ごとのコストの和の最小を求める問題である。[状態](../guide/glossary.md#state)を $\mathrm{dp}[i]$ ＝ 先頭 $i$ 個の区切り方の数（または最適値）とし、最後の区間 $[j, i)$ の左端 $j$ で場合分けする。初期値は空の区切りを 1 通りとする $\mathrm{dp}[0] = 1$ で、そのままでは $O(N^2)$ である（[最後の区間で分ける](../dp/dp-sequence-partition.md#last-block)）。

条件を満たす $j$ の範囲が $i$ とともに単調に動くなら、遷移元の和を累積和で取り、範囲を尺取り法で動かして $O(N)$ にできる（[遷移元の範囲が単調に動く](../dp/dp-sequence-partition.md#two-pointers)）。この DP で足りるのは、区切った後の部分どうしが影響し合わない場合である。影響し合うなら[次の節](#shrink-and-merge)の区間 DP にする（[区間 DP との違い](../dp/dp-sequence-partition.md#vs-interval-dp)）。

## 縮めながら取り除く・隣どうしを合体させる → 区間 DP（interval-dp） {#shrink-and-merge}

隣り合う 2 つを合体させる、区間を取り除くと両隣がくっつく、といった操作では、操作の順で途中の列が変わる。最後の区間を決めても左の部分が独立にならないので、区間 DP にして、任意の区間 $[l, r)$ の答えを $\mathrm{dp}[l][r]$ として持つ。短い区間から順に埋める。

遷移の形は 3 つに分かれる。1 つ目は[分割点型](../dp/interval-dp.md#split-point)で、最後の操作の境目 $m$ を決めて区間を 2 つに割る。$O(N^3)$ かかる。2 つ目は[両端型](../dp/interval-dp.md#ends)で、両端の一方を取り除く。$O(N^2)$ かかる。3 つ目は、ある要素がいつ・何と一緒に消えるかを決める型で、左端と組んで消える相手 $m$ を試すので $O(N^3)$ かかる。最後に残す要素を決める決め方もある（[最後に残す・最後に消すものを決める型](../dp/interval-dp.md#last-operation)）。

## 加算をまとめて最後に見る → いもす法（imos） {#batch-add}

区間 $[l, r)$ に $x$ を足す操作を何度も行い、最後に各要素の値を知りたいときは、長さ $N + 1$ の配列 $D$ の 2 か所 $D[l] \mathrel{+}= x$、$D[r] \mathrel{-}= x$ だけを書き換え、最後に先頭から累積する。$Q$ 回の加算で $O(N + Q)$ である。閉区間 $[l, r]$ なら右端は $r + 1$ に $-x$ を置く（[1 次元のいもす法](../basics/imos.md#imos-1d)）。座標が大きいときは座標圧縮するか、出来事を座標の順に並べる（[座標が大きいとき](../basics/imos.md#large-coordinates)）。

加算の途中で値を読む必要があるなら、いもす法では間に合わない。[次の節](#online-updates)のデータ構造にする。

## 更新と質問が交互 → BIT・セグメント木（fenwick-tree, segment-tree） {#online-updates}

更新と区間の質問が交互に来るときは、操作の組で使うデータ構造が決まる。どれも 1 回 $O(\log N)$ である。

- **1 点の更新と区間の和**：[BIT](../ds/fenwick-tree.md#what-it-does)。区間の和は 2 つの接頭辞の和の差で求める
- **区間加算と 1 点の値**：差分の列を BIT に載せる（[途中で値を読むなら BIT・遅延セグ木](../basics/imos.md#online)）
- **1 点の更新と区間の最小値・最大値などの集約**：[セグメント木](../ds/segment-tree.md#what-it-does)。[結合法則](../guide/glossary.md#associativity)を満たす演算なら載る。何を載せるかは[型の表](../ds/segment-tree-monoids.md#pattern-table)にある
- **区間の加算・代入と区間の和・最小値**：[遅延セグメント木](../ds/lazy-segment-tree.md#what-it-does)

## 値が変わらない列の区間の最小値 → Sparse Table（sparse-table） {#static-min}

列が最後まで変わらず、区間の最小値・最大値・gcd を多数答えるなら、[Sparse Table](../ds/sparse-table.md#what-it-does) で前計算 $O(N \log N)$、1 回 $O(1)$ にできる。長さが 2 のべきの区間の答えを表にしておき、区間を重なりのある 2 つの区間で覆う。重なりを許せるのは、min のように $x \cdot x = x$ となる[冪等](../guide/glossary.md#idempotent)な演算だけである（[なぜ重なってよいか](../ds/sparse-table.md#idempotent)）。和なら[累積和](#sum)で足りる。

## 区間に ±1 する操作の回数・可否 → 差分列への言い換え（difference-sequence） {#difference}

隣どうしの差の列で見ると、区間に 1 を足す操作は 2 点だけを変える。0-indexed で $A_{-1} = A_N = 0$ とし、両端の外も含めて $d_i = A_i - A_{i-1}$（$0 \le i \le N$）を取ると、$[l, r)$ への $+1$ は「$d_l$ を $+1$、$d_r$ を $-1$」という操作になる（[区間の操作を差分列の 2 点の操作に直す](../basics/difference-sequence.md#to-point-operations)）。

すべて 0 の列から区間への $+1$ だけで $A$（各 $A_i \ge 0$）を作る最小回数は、正の差分の和 $\sum_i \max(d_i, 0)$ で、負の差分の和の絶対値と等しい。1 回の操作で $+1$ される差分は 1 つだけだからである。$\pm 1$ のどちらもできる場合や長さが決まった区間の場合は[最小回数・可否を差分列の正負で考える](../basics/difference-sequence.md#min-operations)にある。

## 区間の種類数・x 以下の個数 → 先読みと BIT、Mo（offline-queries, mo-algorithm） {#offline}

区間の種類数は、2 つの区間の答えから合成できないので、セグメント木にそのままでは載らない。[オフライン](../guide/glossary.md#offline)で答えてよいなら、質問を右端の順に並べ、各値の最後の出現位置にだけ 1 を立てた列を BIT で持つ。$[l, r)$ の種類数は、その列の $[l, r)$ の和になる（[右端でソートして BIT](../ds/offline-queries.md#distinct-count)）。$x$ 以下の要素の個数・和も、要素と質問を値の順に並べて BIT に入れていけば答えられる（[しきい値でソート](../ds/offline-queries.md#threshold)）。

1 要素の出し入れで答えを直せる量なら、[Mo's algorithm](../ds/mo-algorithm.md#what-it-does) で質問の順を並べ替え、伸び縮みの総回数を $O(N\sqrt{Q})$ に抑えられる。前の答えを使って次の質問が決まる（オンラインを強いられる）問題では、どちらも使えない（[オンライン強制の見分け方](../ds/offline-queries.md#online)）。

## 重ならない最大個数・すべてを串刺しにする点の数 → 区間スケジューリング（interval-scheduling） {#scheduling}

区間の集合から重ならないように最大個数を選ぶには、右端の小さい順に見て、最後に選んだ区間と重ならなければ選ぶ。早く終わる区間を選ぶほど後に残せる範囲が広がる、という交換論法で正しさが示せる（[右端の順に選ぶ理由](../basics/interval-scheduling.md#why-right-end)）。左端の順や長さの順では誤る。

どの区間にも点が入るように置く点の最少個数（串刺し）も、右端の順に見て、まだ点の入っていない区間の右端に点を置く同じ貪欲で求まる（[区間の串刺し](../basics/interval-scheduling.md#stabbing)）。区間に重みがあって和を最大にするなら、貪欲ではなく DP にする（[区間に重みがあるなら DP](../basics/interval-scheduling.md#weighted)）。どれもソートの $O(N \log N)$ である。

## 区間の和集合・塗りつぶし・残りの長さ → 区間を set で管理（interval-set） {#union}

区間を塗る・消す操作のたびに覆われた長さやある点を含む区間を答えるときは、互いに重ならない区間の集合を持つ。左端をキーにした map を使う（[持ち方](../ds/interval-set.md#representation)）。新しい区間を入れるときは、重なる区間を取り出して 1 つにまとめる。1 回の操作で新しくできる区間は $O(1)$ 個で、消える区間は一度しか消えないので、ならし $O(\log N)$ になる。覆われた長さの合計は、消える区間の分を引き、入れる区間の分を足して保つ（[応用](../ds/interval-set.md#applications)）。

区間がはじめにすべて与えられ、和集合を 1 回求めるだけなら、左端の順に並べて前からつなげば足りる。

## 含まれる・交差する区間の数 → イベントソート・平面走査（event-sort, sweep-line-2d） {#containment}

各時刻に何本の区間が重なっているかは、区間を「始まり」と「終わり」の出来事に分けて座標の順に処理する[イベントソート](../basics/event-sort.md#make-events)で求まる。同じ座標での処理の順は区間の端の開閉で決まり、半開区間 $[l, r)$ なら「終わり → 始まり → 質問」の順になる。

質問の区間 $[p, q]$ に含まれる区間の数は、区間 $[L, R]$ を点 $(L, R)$ と見ると「$p \le L$ かつ $R \le q$ の点の数」で、2 次元の点を数える問題になる。右端の順に区間と質問を並べ、左端を BIT に入れて数える（[区間を 2 次元の点と見る](../ds/sweep-line-2d.md#intervals-as-points)）。区間が交わる（共通部分がある）数は、余事象の「$R < p$」と「$L > q$」が同時に起きないので、それぞれをソートと二分探索で数えて全体から引けばよい。

2 つの区間の組で決まる条件も、片方の端点で並べて走査し、もう一方を二分探索で探す形に直せることが多い。

## 数列ではなく文字列の連続部分 → 部分列と部分文字列（subsequence-and-substring） {#substrings}

文字列の連続した一部分を部分文字列と呼ぶ。飛び飛びに選ぶ[部分列](../guide/glossary.md#subsequence)とは別物で、問題文がどちらを指しているかを最初に確かめる。部分文字列の一致・比較・種類数は、和や最小値とは別の手法（ローリングハッシュ・Z-algorithm・Suffix Array）を使う。問われ方からの引き方は[部分列と部分文字列](../patterns/subsequence-and-substring.md#overview)にある。文字ごとの出現回数のように数で表せる性質なら、このページの累積和や尺取り法もそのまま使える。

## 落とし穴 {#pitfalls}

- **閉区間と半開区間の取り違え**：問題文の 1-indexed の閉区間 $[L, R]$ を 0-indexed の半開区間に直すと $[L-1, R)$ になる。累積和なら $S_R - S_{L-1}$ で求め、いもす法なら右端の次の位置に $-x$ を置く。どちらで書くかをコードの最初で決め、変換を 1 か所にまとめる
- **$S_0$ を入れ忘れる**：累積和の値を連想配列で数えるとき、最初に $S_0 = 0$ を入れないと、左端が 0 の区間をすべて落とす
- **負の値で尺取り法を使う**：和の条件は値が 0 以上のときだけ単調である。負の値があるなら累積和の差で数える
- **同じ値の二重数え**：全区間の最小値の和で両側を「より小さい」で止めると、同じ最小値が 2 つある区間を 2 回数える。片側だけを「以下」にする
- **答えの大きさ**：区間は $N(N+1)/2$ 個あるので、全区間の最小値（最大値）の総和は $N = 2 \times 10^5$・値 $10^9$ で約 $2 \times 10^{19}$ に届き、`long long`（約 $9.2 \times 10^{18}$ まで）を超えうる。全区間の和の総和なら約 $10^{24}$ で必ず超える。どの量かを制約から見積もり、mod を取るか `__int128` を使う
- **端点が触れる区間を重なりとみなすか**：閉区間 $[1, 3]$ と $[3, 5]$ は点 3 を共有して重なるが、半開区間 $[1, 3)$ と $[3, 5)$ は重ならない。区間スケジューリングの判定の不等号や、イベントの処理の順がこれで変わる

## 練習問題 {#practice}

<div class="kp-problems" data-role="practice" markdown>

- [ABC189 C. Mandarin Orange](https://atcoder.jp/contests/abc189/tasks/abc189_c)（diff 565）：区間を 1 つ選び、区間の長さと区間の最小値の積の最大値を求める。
- [ABC265 D. Iroha and Haiku (New ABC Edition)](https://atcoder.jp/contests/abc265/tasks/abc265_d)（diff 727）：数列の中で、隣り合う 3 つの区間の和が順に P, Q, R になる位置があるか判定する。
- [ABC457 E. Crossing Table Cloth](https://atcoder.jp/contests/abc457/tasks/abc457_e)（diff 1428）：M 個の区間からちょうど 2 個を選び、選んだ区間で覆われる範囲が、質問の区間とちょうど一致するようにできるかを、多数の質問について判定する。

</div>

??? note "練習の方針"
    - **ABC189 C**：[ヒストグラムの最大長方形](#sum-over-subarrays)の形である。制約が小さいので、左端を固定して右へ伸ばしながら最小値を更新する $O(N^2)$ の全探索で通る。$N$ が大きければ、各 $a_i$ が最小のまま広げられる幅を単調スタックで求めて $O(N)$ にする
    - **ABC265 D**：3 つの区間を $[x, y)$・$[y, z)$・$[z, w)$ とすると、条件は $S_y = S_x + P$、$S_z = S_y + Q$、$S_w = S_z + R$ である。値が正なので累積和は狭義に増え、値から位置が 1 つに決まる。累積和の値を集合に入れ、各 $x$ について $S_x + P$・$S_x + P + Q$・$S_x + P + Q + R$ がすべてあるかを調べる（[区間の和](#sum)）
    - **ABC457 E**：2 個の区間で $[S, T]$ をちょうど覆う形は、左端が $S$ の区間と右端が $T$ の区間がすき間なくつながる（重なってもよい）形か、$[S, T]$ そのものの区間とその内側の区間の組の 2 通りに限られる。区間を、左端ごと・右端ごとのソートした一覧に分けておく。そのうえで、質問を右端 $T$ の順に処理する。それぞれの形は、一覧の二分探索と、それまでに見た区間の左端の最大値を使って判定する（[含まれる・交差する区間の数](#containment)）

## 参考 {#references}

- [ikatakos「AtCoder Beginner Contest 189」](https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2021/0123_abc189)：ABC189 C をヒストグラムの最大長方形と見る方針と、$O(N^2)$・単調スタックの解法
- [oraclesqlpuzzle「ABC265-D Iroha and Haiku (New ABC Edition)」](https://oraclesqlpuzzle.ninja-web.net/kyoupro/05-atcoder-02-abc/kyoupro-abc265-d.html)：ABC265 D の、累積和の上で始点からの和を二分探索する解法
- [ikatakos「Polaris.AI プログラミングコンテスト 2026（AtCoder Beginner Contest 457）E,F問題メモ」](https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2026/0509_abc457)：ABC457 E の 2 通りの形の場合分けと、右端の順に走査して二分探索する解法
