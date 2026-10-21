---
id: reverse-index-constraints
title: 逆引き辞典（制約・計算量から）
aliases: [制約から解法を推測する, 計算量の目安, 制約と計算量の対応表, 制約から逆引き, 計算量から逆引き]
type: guide
field: guide
chapter: 辞書として引く
order: 20
level: null
kind: [案内]
prerequisites: []
related: [reverse-index-signs, cheatsheet#complexity-and-constraints, complexity-estimation, harmonic-sum, cpp-io#tle-causes]
summary: N の上限などの制約から、間に合う計算量と候補の手法を引ける。計算量から手法を引く逆向きの表も持ち、制約の帯ごとの候補のページは各ページの制約のサインから生成する。
complexity: null
signs: []
acl: []
sections:
  - {title: 引き方と注意, anchor: how-to-read}
  - {title: 1 秒あたりの演算回数の目安, anchor: ops-per-second}
  - {title: 制約 → 計算量 → 候補の手法, anchor: constraint-table}
  - {title: 制約の帯ごとの候補のページ, anchor: pages-by-constraint}
  - {title: N = 2×10^5 のときの量の目安, anchor: magnitudes}
  - {title: 値や複数の制約から読めるサイン, anchor: value-signs}
  - {title: 見た目より速い・遅い計算量, anchor: deceptive}
  - {title: 計算量から手法を引く, anchor: complexity-to-methods}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何のページか**：N の上限などの制約から、間に合う計算量と候補の手法を引ける。計算量から手法を引く逆向きの表も持ち、制約の帯ごとの候補のページは各ページの制約のサインから生成する。
    - **使い方**：（執筆時に書く）

<!-- gen:begin signs-constraint -->
<!-- textlint-disable -->

### 上限が 10 以下 {#signs-constraint-10}

| 制約 | ページ | レベル |
| --- | --- | --- |
| 制約の一部だけが小さい（K ≤ 5、末尾の K ≤ 10 文字、文字の種類 26） | [DP の状態の設計](../dp/dp-state-design.md) | 水 |
| N ≤ 8 / 20 / 40 / 400 / 5000 / 2×10^5 / 10^18 のような制約の大きさ | [計算量の見積もり](../basics/complexity-estimation.md) | 基礎 |
| 一方の次元だけ極端に小さい（H ≤ 8 など） | [全探索の設計](../basics/brute-force.md) | 基礎 |
| パターンの個数 ≤ 8 程度で、すべてを含むかを問う | [照合オートマトン上の DP](../string/string-automaton-dp.md)（準備中） | 青 |
| N ≤ 8〜10 で並び順・割り当て・頂点の対応を決める | [bit 全探索と順列全探索](../basics/bit-full-search.md) | 基礎 |
| N ≤ 10 程度で、経路を全部列挙できる | [深さ優先探索（DFS）](../graph/dfs.md) | 基礎 |
| N ≤ 8〜10 で頂点の対応や辺の部分集合を全部試せる | [小さいグラフの全探索](../graph/small-graph-brute-force.md) | 基礎 |
| 指定した K 点（K ≤ 10 程度）をすべて連結にする最小コスト | [最小シュタイナー木](../graph/steiner-tree.md)（準備中） | 発展 |
| K ≤ 10 程度の少数の要素を選ぶ条件で、要素の種類が多い | [乱択アルゴリズム](../misc/randomized.md)（準備中） | 青 |

### 上限が 20 以下 {#signs-constraint-20}

| 制約 | ページ | レベル |
| --- | --- | --- |
| 各要素が 3 択で N ≤ 12 程度（3^N 通り） | [bit 全探索と順列全探索](../basics/bit-full-search.md) | 基礎 |
| N ≤ 10〜12 人を組・グループに分ける（ベル数 B12 ≈ 4.2×10^6） | [再帰による全列挙](../basics/recursive-enumeration.md) | 水 |
| N ≤ 10〜12 で、グループ分けを全部試す | [第 2 種スターリング数とベル数](../comb/bell-number.md)（準備中） | 青 |
| グリッドの短い辺 ≤ 6〜14 | [プロファイル DP](../dp/broken-profile-dp.md)（準備中） | 黄 |
| 2N ≤ 16 人を 2 人組に分ける（(2N−1)!! 通り） | [再帰による全列挙](../basics/recursive-enumeration.md) | 水 |
| N ≤ 16 程度の一般グラフでペアを作る | [一般グラフのマッチング](../graph/general-matching.md)（準備中） | 発展 |
| 特別な地点が K ≤ 17 個（ほかの地点はグラフで結ばれている） | [bitDP](../dp/bit-dp.md) | 水 |
| N ≤ 17 程度の頂点数で、条件を満たす辺の選び方を数える | [連結なグラフの数え上げ](../comb/counting-labeled-graphs.md)（準備中） | 黄 |
| N ≤ 18 程度で、集合とその部分集合の組をすべて調べる（全体で 3^N） | [bit 演算の基本と XOR の性質](../basics/bit-operations.md) | 基礎 |
| N ≤ 16〜18（3&#94;N ≈ 4×10&#94;7〜4×10&#94;8） | [部分集合を列挙する DP](../dp/subset-enumeration-dp.md)（準備中） | 青 |
| カードの枚数 N ≤ 18 程度で、残りのカードの集合が局面になる | [ゲームの基本と勝敗の DP](../comb/game-basics.md) | 水 |
| N ≤ 15〜20 で各要素を「選ぶ／選ばない」 | [bit 全探索と順列全探索](../basics/bit-full-search.md) | 基礎 |
| N ≤ 16〜20 | [bitDP](../dp/bit-dp.md) | 水 |
| 禁止条件が M ≤ 20 個程度 | [包除原理](../comb/inclusion-exclusion.md)（準備中） | 青 |
| N ≤ 20 で、すべての部分集合（bit）ごとの和・最大を求める | [部分集合の高速ゼータ変換とメビウス変換](../comb/zeta-mobius-subset.md)（準備中） | 黄 |

### 上限が 40 以下 {#signs-constraint-40}

| 制約 | ページ | レベル |
| --- | --- | --- |
| N ≤ 40 で部分集合を選ぶ（2^N は無理だが 2^(N/2) は間に合う） | [半分全列挙](../basics/meet-in-the-middle.md) | 水 |
| H + W ≤ 40 程度のグリッドで、左上から右下への経路をすべて考える | [半分全列挙](../basics/meet-in-the-middle.md) | 水 |
| N ≤ 20〜40 の一般グラフで、独立集合・彩色・クリークを求める | [彩色数・最大独立集合・最大クリーク](../graph/chromatic-number.md)（準備中） | 発展 |

### 上限が 80 以下 {#signs-constraint-80}

| 制約 | ページ | レベル |
| --- | --- | --- |
| N ≤ 50 程度で、長さ（個数）の組合せ（多重集合）を全部試す | [整数の分割と分割数](../comb/partition-number.md)（準備中） | 黄 |
| N ≤ 50 程度の点で、実数の位置や半径を最適化する | [円と幾何の最適化](../geometry/circle-geometry.md)（準備中） | 青 |
| N ≤ 60 程度で、mod を取らない正確な値を求める | [二項係数の意味と性質](../comb/binomial-coefficient.md) | 基礎 |

### 上限が 500 以下 {#signs-constraint-500}

| 制約 | ページ | レベル |
| --- | --- | --- |
| N ≤ 100、K ≤ 10^5 程度で、O(NK) は通るが O(NK^2) は通らない | [累積和・いもす法による DP の高速化](../dp/dp-prefix-sum.md) | 水 |
| N ≤ 100、値の総和 ≤ 10^5 程度 | [部分和 DP](../dp/subset-sum.md) | 基礎 |
| 状態数 n ≤ 100 程度で、繰り返しの回数 K が 10&#94;9〜10&#94;18 | [行列累乗](../math/matrix-power.md) | 青 |
| N ≤ 400 前後 | [区間 DP の応用](../dp/interval-dp-advanced.md)（準備中） | 黄 |
| N ≤ 400 程度で全点対の距離が要る | [ワーシャルフロイド法](../graph/warshall-floyd.md) | 水 |
| N ≤ 300〜500 で O(N^3) が通る | [区間 DP](../dp/interval-dp.md)（準備中） | 青 |
| N ≤ 数百、M ≤ 数千程度で、流す量 K ≤ N | [最小費用流](../graph/min-cost-flow.md)（準備中） | 黄 |

### 上限が 5000 以下 {#signs-constraint-5000}

| 制約 | ページ | レベル |
| --- | --- | --- |
| M ≤ 1000 程度、N ≤ 100 程度 | [余り・個数を状態に持つ DP](../dp/dp-mod-state.md) | 水 |
| H, W ≤ 2000 程度のグリッドで領域の和を何度も求める | [2 次元累積和](../basics/prefix-sum-2d.md) | 水 |
| H, W ≤ 2000 程度（マスの数が 4×10^6 程度まで） | [グリッドグラフ](../graph/grid-graph.md) | 基礎 |
| H, W ≤ 3000 程度 | [グリッド上の DP](../dp/dp-grid.md) | 水 |
| N ≤ 3000 程度の順列の数え上げ | [挿入 DP・箱根駅伝 DP](../dp/insertion-dp.md)（準備中） | 黄 |
| N ≤ 100〜5000、W ≤ 10&#94;4〜10&#94;5（O(NW) が通る） | [ナップサック DP](../dp/knapsack-01.md) | 基礎 |
| 2 つの列・文字列で N, M ≤ 3000〜5000 | [最長共通部分列と編集距離](../dp/lcs.md) | 水 |
| N ≤ 2000〜5000 の木 | [二乗の木 DP](../dp/tree-dp-square.md)（準備中） | 黄 |
| N, M ≤ 数千（O(NM) が間に合う） | [ベルマンフォード法](../graph/bellman-ford.md)（準備中） | 青 |
| 値の範囲 M ≤ 5000 程度で、各 k について P(X ≥ k) を数える | [期待値と確率の変換](../comb/expectation-tail-sum.md)（準備中） | 黄 |
| \|S\| ≤ 5000 程度で、回転や置き方を全部試せる | [文字列の基本操作と辞書順](../string/string-basics.md) | 基礎 |
| N ≤ 2000〜5000 程度で、O(N^3) や O(N^2 M) が少し間に合わない | [bitset による高速化](../misc/bitset-speedup.md)（準備中） | 青 |

### 上限が 2×10^5 前後（5×10^5 以下） {#signs-constraint-2e5}

| 制約 | ページ | レベル |
| --- | --- | --- |
| 法 P が 10^9 程度で、√P ≈ 3×10^4 個の表なら持てる | [位数・原始根・離散対数](../math/multiplicative-order.md)（準備中） | 黄 |
| N ≤ 10^5 程度で、各位置の選択肢が数通り（全探索だと K^N 通り） | [DP の基本](../dp/dp-basics.md) | 基礎 |
| N ≤ 10^5 の列を K（数十）個の区間に分ける | [Monge 性による DP の高速化](../dp/monge.md)（準備中） | 発展 |
| A_i < 2^60 で N ≤ 10^5 程度 | [XOR 基底](../math/xor-basis.md)（準備中） | 黄 |
| H, W ≤ 10^5 のグリッドで、左上から右下への経路の数を求める | [格子路の数え上げ](../comb/lattice-paths.md) | 基礎 |
| H, W ≤ 10^5 のグリッドに障害物が N ≤ 3000 個 | [包除 DP](../comb/inclusion-exclusion-dp.md)（準備中） | 黄 |
| 状態数 N ≤ 10^5 程度で、各状態の遷移が少数（または区間） | [期待値 DP](../comb/expected-value-dp.md) | 水 |
| Q ≤ 2×10^5 個のクエリ（1 回あたり O(log N) 以下が必要） | [計算量の見積もり](../basics/complexity-estimation.md) | 基礎 |
| A_i < 2&#94;30〜2&#94;60 で、全ペア（N ≤ 2×10&#94;5）の値を集計する | [bit ごとに独立に考える](../basics/bitwise-independence.md) | 水 |
| N ≤ 2×10^5 個の値に対して、Q ≤ 2×10^5 個の位置・個数の質問がある | [二分探索](../basics/binary-search.md) | 基礎 |
| Q ≤ 2×10^5 個の区間和のクエリで、値の更新がない | [累積和](../basics/prefix-sum.md) | 基礎 |
| N, Q ≤ 2×10^5 で区間への加算が多数あり、値を読むのは最後だけ | [いもす法](../basics/imos.md) | 基礎 |
| N ≤ 2×10^5 で区間を全部は調べられない | [尺取り法](../basics/two-pointers.md) | 基礎 |
| N ≤ 2×10^5 で、K が N^2 程度まで大きい | [K 番目の値](../basics/kth-value.md)（準備中） | 青 |
| N ≤ 2×10^5 本の区間で、座標は 10^9 まで | [区間スケジューリング・区間の串刺し](../basics/interval-scheduling.md) | 基礎 |
| K ≤ 2×10^5 程度で、小さい順に K 個取り出せば足りる | [優先度付きキューを使う貪欲](../basics/greedy-priority-queue.md) | 水 |
| N, Q ≤ 2×10^5 で、区間ごとに計算し直すと間に合わない | [分割統治](../basics/divide-and-conquer.md)（準備中） | 黄 |
| N ≤ 2×10^5 で 3 つ組は N^3 通りあり、全部は試せない | [一部を固定して数える](../thinking/fix-variable.md) | 基礎 |
| N ≤ 2×10^5 で、組・区間は N^2 個あり列挙できない | [主客転倒・寄与](../thinking/contribution.md) | 水 |
| N ≤ 2×10^5 で「部分列」「単調増加」 | [最長増加部分列](../dp/lis.md) | 水 |
| 文字の種類 26 程度、\|S\| ≤ 2×10^5 | [部分列 DP](../dp/subsequence-dp.md)（準備中） | 黄 |
| N ≤ 2×10^5 では N^2 の隣接行列を持てない（N ≤ 2000 程度なら持てる） | [グラフの表現と用語](../graph/graph-basics.md) | 基礎 |
| N, M ≤ 2×10^5、またはマスの数 H×W ≤ 10^6 程度 | [幅優先探索（BFS）と無重み最短路](../graph/bfs.md) | 基礎 |
| N, M ≤ 2×10^5 で辺の重みが非負 | [ダイクストラ法](../graph/dijkstra.md) | 基礎 |
| N ≤ 2×10^5 で、補グラフの辺は N^2 本近くあり列挙できない | [補グラフ上の BFS](../graph/complement-graph-bfs.md)（準備中） | 黄 |
| 完全グラフで N ≤ 2×10^5（辺が N^2 本あり、候補の辺を減らす必要がある） | [最小全域木](../graph/minimum-spanning-tree.md) | 水 |
| N, M ≤ 2×10^5 で、辺を 1 本ずつ除いて調べる O(M(N+M)) は間に合わない | [橋・関節点・二重連結成分](../graph/lowlink.md)（準備中） | 黄 |
| N, M, Q ≤ 2×10^5 で、1 つの頂点の次数が N 近くになりうる | [次数による平方分割](../graph/degree-sqrt.md)（準備中） | 青 |
| N ≤ 2×10^5 の木で、全ペア（N^2/2 組）についての和を求める | [辺で切って数える](../tree/tree-edge-contribution.md) | 水 |
| パス u–v に関するクエリが Q ≤ 2×10^5 個 | [最小共通祖先（LCA）](../tree/lca.md) | 青 |
| N, Q ≤ 2×10^5 で、部分木への更新と質問が交互に来る | [オイラーツアー](../tree/euler-tour.md) | 青 |
| クエリごとに K_i 個の頂点が指定され、ΣK_i ≤ 2×10^5 | [Auxiliary Tree](../tree/auxiliary-tree.md)（準備中） | 発展 |
| N, Q ≤ 2×10^5 で、追加・削除・検索のクエリが来る | [STL コンテナの使い分け](../ds/stl-containers.md) | 基礎 |
| Q ≤ 2×10^5 で、更新のたびに上位 K 個の和や中央値を答える | [上位 K 個の和と中央値の管理](../ds/top-k-multiset.md) | 水 |
| Q ≤ 2×10^5 で、全体への操作を毎回 O(N) で行うと間に合わない | [全体への操作を変数で持つ](../ds/global-offset.md) | 基礎 |
| N ≤ 2×10^5 で、各要素から左右を見ていくと O(N^2) になる | [単調スタックとスライド最小値](../ds/monotonic-stack.md) | 水 |
| N, Q ≤ 2×10^5 で辺の追加と質問が混ざる | [Union-Find](../ds/union-find.md) | 基礎 |
| 情報と質問が交互に Q ≤ 2×10^5 回来る | [重み付き Union-Find](../ds/weighted-union-find.md) | 水 |
| N, Q ≤ 2×10^5 で更新があり、累積和を毎回作り直すと間に合わない | [BIT（Fenwick Tree）](../ds/fenwick-tree.md) | 水 |
| N ≤ 2×10^5 で、答えが約 2×10^10 まで大きくなる | [転倒数](../ds/inversion-number.md) | 水 |
| N, Q ≤ 2×10^5 で、更新のたびに条件を満たす最初の位置を答える | [セグメント木上の二分探索](../ds/segment-tree-binary-search.md) | 水 |
| 値が 10^9 まで、N, Q ≤ 2×10^5 | [値を添字にする BIT・セグメント木](../ds/segment-tree-on-values.md) | 水 |
| N, Q ≤ 2×10^5 で、区間の更新と区間の取得が交互に来る | [遅延セグメント木](../ds/lazy-segment-tree.md) | 水 |
| 値が 10^9 まで、N, Q ≤ 2×10^5 で、クエリにも新しい値が現れる | [クエリの先読み](../ds/offline-queries.md) | 水 |
| N, Q ≈ 2×10^5 で、制限時間が長めにとってある | [Mo's algorithm](../ds/mo-algorithm.md)（準備中） | 青 |
| \|S\| ≤ 2×10^5 の数字列で、部分文字列を全部試すと間に合わない | [桁と mod](../math/digit-and-mod.md) | 水 |
| N, Q ≤ 2×10^5 で区間 gcd のクエリ | [GCD の性質](../math/gcd-properties.md)（準備中） | 青 |
| N ≤ 2×10^5 程度で C(n,k) を何度も求める | [二項係数の前計算](../comb/binomial-precompute.md) | 基礎 |
| N, Q ≤ 2×10^5 で区間の多重集合を毎回比べる | [集合・多重集合のハッシュ](../string/hashing-for-sets.md) | 水 |
| 操作が M ≤ 2×10^5 回、各クエリは途中の時点での点の位置 | [回転・平行移動・アフィン変換](../geometry/rotation-transform.md) | 水 |
| N ≤ 2×10^5 点の全ペアのマンハッタン距離の和や最大を問い、全組 O(N^2) が間に合わない | [マンハッタン距離と 45 度回転](../geometry/manhattan-chebyshev.md) | 水 |
| A_i ≤ 10^9 を N ≤ 2×10^5 個足す、または 2 つ掛ける（int に収まらない） | [整数のオーバーフローと \_\_int128](../cpp/cpp-integer-overflow.md) | 基礎 |
| N ≤ 2×10^5 の木やグラフを再帰でたどる（一直線の入力では深さが N になり、手元の 8 MiB のスタックでは落ちることがある） | [AtCoder と手元の C++ 環境](../cpp/cpp-environment.md)（準備中） | — |
| N, Q ≤ 2×10&#94;5〜5×10&#94;5 で、一点の更新と区間の質問が交互に来る | [セグメント木](../ds/segment-tree.md) | 水 |
| \|S\| ≤ 5×10^5 程度で全部分文字列を扱う | [Suffix Array と LCP 配列](../string/suffix-array.md) | 黄 |

### 上限が 10^6 以下 {#signs-constraint-1e6}

| 制約 | ページ | レベル |
| --- | --- | --- |
| A_i ≤ 10&#94;6（〜10&#94;7）の各要素を素因数分解する | [最小素因数の篩と線形篩](../math/spf-sieve.md) | 基礎 |
| A_i ≤ 10^6 程度で、値を配列の添字にできる | [調和級数と倍数の列挙](../math/harmonic-sum.md) | 水 |
| 値の上限 ≤ 10^6 程度で、すべての g について数える | [約数包除](../comb/divisor-inclusion-exclusion.md)（準備中） | 青 |
| 値の上限 ≤ 10^6 程度で、gcd・lcm ごとに集計する | [約数・倍数のゼータ変換とメビウス変換](../comb/zeta-mobius-divisor.md)（準備中） | 青 |
| N ≤ 10^6 程度で、μ を篩で前計算できる | [メビウス関数とメビウス反転](../comb/mobius-function.md)（準備中） | 黄 |
| \|S\| ≤ 10&#94;5〜10&#94;6、文字は英小文字で 26×(N+1) の表が持てる | [部分列の判定と次の出現位置の表](../string/subsequence-matching.md) | 基礎 |
| N ≤ 10&#94;5〜10&#94;6 で、任意の 2 区間の一致判定が Q ≤ 2×10&#94;5 回 | [ローリングハッシュ](../string/rolling-hash.md) | 水 |
| \|S\|, \|T\| ≤ 10^6 で、ずらし方ごとに比べる O(\|S\|\|T\|) が間に合わない | [Z-algorithm](../string/z-algorithm.md) | 水 |
| \|S\| ≤ 10^6 で、すべての接頭辞について周期や一致する長さを問う | [KMP 法と文字列の周期](../string/kmp.md) | 青 |
| N ≤ 10^6 で、すべての中心（区間）について回文かを問う | [回文の扱いと Manacher](../string/palindrome.md) | 水 |

### 上限が 10^7 以下 {#signs-constraint-1e7}

| 制約 | ページ | レベル |
| --- | --- | --- |
| N ≤ 10&#94;6〜10&#94;7 の範囲の素数を全部使う | [エラトステネスの篩](../math/sieve-eratosthenes.md) | 基礎 |

### 上限が 10^12 以下 {#signs-constraint-1e12}

| 制約 | ページ | レベル |
| --- | --- | --- |
| 状態数が 10&#94;6〜10&#94;7 程度に収まる（9! = 362880、60&#94;4 ≈ 1.3×10&#94;7） | [状態を頂点にする](../graph/extended-dijkstra.md) | 水 |
| 制限時間が長めで、O(N√N) ≈ 10^8 なら間に合う | [平方分割](../ds/sqrt-decomposition.md)（準備中） | 黄 |
| −10^9 ≤ A_i ≤ 10^9 のように負の値を含む | [累積和と連想配列で区間を数える](../basics/prefix-sum-counting.md) | 基礎 |
| 重さの上限 W ≤ 10^9 で、価値の総和が 10^5 程度 | [DP の状態の削減](../dp/dp-dimension-reduction.md)（準備中） | 青 |
| 法 M ≤ 10^9 が素数とは限らず、a^(M−2) で逆元を作れない | [拡張ユークリッドの互除法と一次合同式](../math/ext-gcd.md) | 水 |
| n, m ≤ 10^9 程度で i を全部回せない | [floor sum](../math/floor-sum.md) | 黄 |
| n ≤ 10^9 で k ≤ 10^6 程度 | [二項係数の前計算](../comb/binomial-precompute.md) | 基礎 |
| 座標が整数で \|x\|, \|y\| ≤ 10^9（外積は long long にぎりぎり収まる） | [ベクトルと外積](../geometry/geometry-vectors.md) | 基礎 |
| A_i < 2^30 で、追加・削除・質問が合わせて 2×10^5 回程度 | [Binary Trie](../ds/binary-trie.md)（準備中） | 青 |
| N ≤ 10&#94;10〜10&#94;11 で Σ_{n≤N} f(n)（f は φ・約数の個数など）を求める | [乗法的関数の和と素数の個数](../math/multiplicative-function.md)（準備中） | 発展 |
| K ≤ 10^12 で約数を扱う（約数の個数は最大 6720） | [全探索の設計](../basics/brute-force.md) | 基礎 |
| N ≤ 10^12 程度（√N ≤ 10^6）の約数・素数判定 | [約数列挙と素数判定](../math/divisor-enum.md) | 基礎 |
| N ≤ 10^12 程度の数を1つだけ素因数分解する | [素因数分解とルジャンドルの公式](../math/prime-factorization.md) | 基礎 |
| L, R ≤ 10^12 で R − L ≤ 10^6 | [区間篩](../math/segmented-sieve.md) | 水 |
| N ≤ 10^12 で i を全部回すと間に合わない | [商の列挙](../math/floor-quotient-enum.md) | 水 |
| N ≤ 10^12 で、N の約数や素因数を使う | [約数と倍数](../patterns/divisors-and-multiples.md)（準備中） | — |

### 上限が 10^12 より大きい（10^18 など） {#signs-constraint-1e18}

| 制約 | ページ | レベル |
| --- | --- | --- |
| K ≤ 10&#94;18 回の操作で、状態の種類は 10&#94;5〜10&#94;6 程度 | [周期性の検出](../basics/periodicity.md) | 基礎 |
| K ≤ 10^18 回の移動・操作で、始点やクエリが多い | [ダブリング](../basics/doubling.md) | 水 |
| N ≤ 10^18 で、⌊N/2⌋・⌊N/3⌋ のような値しか現れない | [メモ化再帰](../dp/memoized-recursion.md) | 基礎 |
| N ≤ 10^18、または N が 10^4 桁の文字列 | [桁 DP](../dp/digit-dp.md) | 水 |
| K 回（K ≤ 10^18）移動した後の位置 | [Functional graph（出次数 1 のグラフ）](../graph/functional-graph.md) | 水 |
| N ≤ 10^18 の木 | [完全二分木](../tree/complete-binary-tree.md) | 基礎 |
| 入力に負の数（\|X\| ≤ 10^18 など）があり、割り算・余り・切り上げを使う | [整数の割り算と余り](../math/integer-division.md) | 基礎 |
| 指数・繰り返しの回数が N ≤ 10^18 | [繰り返し二乗法](../math/mod-pow.md) | 基礎 |
| 項数 N ≤ 10&#94;12〜10&#94;18 の等比数列の和を、素数とは限らない法 M ≤ 10&#94;9 で求める | [等比数列の和を mod で求める](../math/geometric-series-mod.md) | 基礎 |
| N ≤ 10&#94;12〜10&#94;18 で、約数の組を全探索して間に合うかを見積もる | [約数の個数の上界と高度合成数](../math/divisor-count-bound.md) | 水 |
| N ≤ 10^18 の素数判定・素因数分解（√N の試し割りでは間に合わない） | [大きな数の素数判定と素因数分解](../math/miller-rabin.md)（準備中） | 発展 |
| N ≤ 10^18 で平方数・平方根を扱う | [整数の平方根・K 乗根と累乗数](../math/integer-root.md) | 基礎 |
| 線形漸化式の項数 K が数百〜数千で、N ≤ 10^18 | [線形漸化式の高速化](../math/linear-recurrence-fast.md)（準備中） | 発展 |
| N ≤ 10^18 で、答えが段階ごとの選択肢の数の積になる | [和・積の法則と順列・組合せ](../comb/counting-basics.md) | 基礎 |
| 置換を K ≤ 10^18 回繰り返した結果を求める | [置換の巡回分解](../comb/permutation-cycles.md) | 基礎 |
| N ≤ 10&#94;9〜10&#94;18 で、パターンの長さの総和が小さい | [照合オートマトン上の DP](../string/string-automaton-dp.md)（準備中） | 青 |

### 数の上限で分けられないもの {#signs-constraint-other}

| 制約 | ページ | レベル |
| --- | --- | --- |
| 実行時間制限が 5 秒など長い（重めの全探索が想定されている） | [計算量の見積もり](../basics/complexity-estimation.md) | 基礎 |
| テストケースが T 個あり、N の総和が 2×10^5 以下 | [計算量の見積もり](../basics/complexity-estimation.md) | 基礎 |
| 答えの範囲が 10&#94;9〜10&#94;18 と広い | [答えで二分探索](../basics/binary-search-answer.md) | 基礎 |
| 値は 10^9 まであるが、個数は 2×10^5 以下 | [座標圧縮](../basics/coordinate-compression.md) | 基礎 |
| 座標は 10^9 まで、区間とクエリは合わせて 2×10^5 個程度 | [イベントソートと平面走査の基本](../basics/event-sort.md) | 水 |
| レベルは 50 程度まででも、全体の長さが 10^15 を超える | [再帰的な構造](../basics/recursion-structure.md) | 基礎 |
| 余りや状態が M 種類しかなく、M + 1 個以上の候補がある | [対称性・鳩の巣原理・場合分け](../thinking/symmetry-pigeonhole-casework.md) | 基礎 |
| クエリの数 Q と目標の和 K がともに 5000 程度（O(QK) が通る） | [戻す DP](../dp/knapsack-undo.md)（準備中） | 青 |
| K が 10&#94;5〜10&#94;6 程度 | [剰余を頂点にする最短路](../graph/modular-shortest-path.md)（準備中） | 発展 |
| 頂点数が数百〜数千、辺数が 10^5 程度まで（フローが間に合う規模） | [最大流](../graph/max-flow.md)（準備中） | 黄 |
| 要素の数 N が 100〜数百程度で、選び方は 2^N 通りある | [燃やす埋める](../graph/project-selection.md)（準備中） | 黄 |
| 種類が 20 程度以下で、部分集合ごとに供給と需要を比べられる | [最小パス被覆と Hall の定理](../graph/dilworth-path-cover.md)（準備中） | 発展 |
| 値が 10^9 まであり、配列の添字にできない | [set・multiset・map の応用](../ds/ordered-set.md) | 基礎 |
| 追加と取り出しが合わせて 2×10^5 回程度 | [優先度付きキュー](../ds/priority-queue.md) | 水 |
| 座標が 10^9 まで（配列の添字にできない） | [区間を set で管理する](../ds/interval-set.md) | 水 |
| クエリが 10^6 級で、1 回 O(1) で答えたい | [Sparse Table](../ds/sparse-table.md)（準備中） | 青 |
| 座標が 10^9 まで・点とクエリが 2×10^5 個（2 次元累積和の表は作れない） | [平面走査](../ds/sweep-line-2d.md)（準備中） | 青 |
| 積・lcm・累乗が 10^18 を超えうる（long long の上限は約 9.2×10^18） | [整数の割り算と余り](../math/integer-division.md) | 基礎 |
| 10^9 程度の値の積を何度も取り、余りを取らないと 64bit に収まらない | [mod の計算の基本](../math/mod-arithmetic.md) | 基礎 |
| 指数が 10^18 をさらに累乗した大きさになる | [フェルマーの小定理と指数の mod](../math/exponent-mod.md) | 水 |
| 変数・式の数が数百〜2000 程度で O(n³) や O(n³/64) | [掃き出し法](../math/gaussian-elimination.md)（準備中） | 青 |
| 値の範囲や列の長さが 10&#94;5〜10&#94;6 程度で、組の全探索 O(N²) が間に合わない | [畳み込みの使い方](../math/convolution-ntt.md)（準備中） | 青 |
| 値が 2&#94;16〜2&#94;20 程度で、添字の XOR で畳み込む | [XOR 畳み込み](../math/hadamard-transform.md)（準備中） | 発展 |
| 山の大きさが 10^18 程度まであり、小さい山から全部の局面を調べられない | [Grundy 数と Sprague-Grundy の定理](../comb/grundy-number.md)（準備中） | 青 |
| 比べ合うハッシュが 10^5 個以上（組が 5×10^9 以上） | [ハッシュの衝突と安全な設計](../string/hash-safety.md)（準備中） | 青 |
| 文字列の個数が多く、長さの総和が 5×10^5 程度まで | [Trie](../string/trie.md) | 水 |
| パターンの長さの総和が 10&#94;5〜10&#94;6 で、パターンの個数も多い | [Aho-Corasick 法](../string/aho-corasick.md)（準備中） | 青 |
| 座標が 10^9 規模の整数で、傾きや角度を比べる | [誤差の扱いと整数での処理](../geometry/geometry-precision.md) | 水 |
| 座標が 10^9 規模の整数で、角度の大小や一致を正確に比べる | [偏角ソート](../geometry/argument-sort.md) | 水 |
| 質問回数の上限が 20 回など log2 N 程度 | [インタラクティブ問題](../misc/interactive.md) | 基礎 |
| N が 5×10^4 程度で N^2/64 の計算が間に合う | [bitset による高速化](../misc/bitset-speedup.md)（準備中） | 青 |
| 式の長さが 2×10^5 程度で、括弧の入れ子が深くなりうる | [構文解析](../misc/parsing.md)（準備中） | 青 |
| 入力や出力が 10^6 個程度ある（入出力の書き方で実行時間に差が出る） | [入出力と定数倍](../cpp/cpp-io.md) | 基礎 |

<!-- textlint-enable -->
<!-- gen:end signs-constraint -->
