---
id: problem-sets
title: 問題集と練習用コンテストの案内
aliases: [典型90問, EDPC, TDPC, NDPC, 鉄則本の問題集, アルゴリズムと数学, ACL Practice, AAL, ADT, AWC, NoviSteps, 最近の ABC の対応表]
type: guide
field: guide
chapter: 学び方と練習
order: 80
level: null
kind: [案内]
prerequisites: []
related: [practice-method, roadmap#recent-positions, library-design#verify-table, atcoder-system#contests]
summary: 典型90問・EDPC・鉄則本・ACL Practice などの問題集と練習用コンテストを、構成とレベルの目安から選べる。最近の ABC と各問題集の問題から、使う手法のページも引ける。
complexity: null
signs: []
acl: []
sections:
  - {title: 問題集の一覧, anchor: collections}
  - {title: 典型90問の★とレベル, anchor: typical90-stars}
  - {title: 最近の ABC → ページ, anchor: recent-abc}
  - {title: 問題集の問題 → ページ, anchor: sets-to-pages}
  - {title: 練習用のコンテスト, anchor: practice-contests}
  - {title: AtCoder 以外の道具, anchor: tools}
  - {title: ライブラリの確かめ用の問題集, anchor: verify-sets}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何のページか**：典型90問・EDPC・鉄則本・ACL Practice などの問題集と練習用コンテストを、構成とレベルの目安から選べる。最近の ABC と各問題集の問題から、使う手法のページも引ける。
    - **使い方**：（執筆時に書く）

<!-- gen:begin recent-abc -->
<!-- textlint-disable -->

| 問題 | 位置 | diff | 使う手法のページ |
| --- | --- | --- | --- |
| abc451_d Concat Power of 2 | D | 856 | [全探索の設計](../basics/brute-force.md) |
| abc451_e Tree Distance | E | 1215 | [最小全域木](../graph/minimum-spanning-tree.md) › Kruskal 法と Prim 法（密なら O(N^2) の Prim）、[Union-Find](../ds/union-find.md)、[木の上の距離](../tree/tree-distance.md) › 1 点からの距離（ダイクストラはいらない）、[木の構築・復元](../tree/tree-construction.md) › 距離の情報から作る（最も近い頂点とは辺で結ばれる） |
| abc451_f Make Bipartite 3 | F | 1540 | [重み付き Union-Find](../ds/weighted-union-find.md) › 一般化（群なら載る。XOR で偶奇・二部グラフの判定、頂点を 2 倍にする Union-Find）、[二部グラフ判定](../graph/bipartite-graph.md) › Union-Find（頂点を 2 倍にする・偶奇を持つ）で判定する |
| abc451_g Minimum XOR Walk | G | 2221 | [XOR 基底](../math/xor-basis.md) › グラフのウォークの XOR（全域木の根からの XOR と、閉路の XOR の基底）、[分割統治](../basics/divide-and-conquer.md) |
| abc452_d No-Subsequence Substring | D | 903 | [部分列の判定と次の出現位置の表](../string/subsequence-matching.md) › 次の出現位置の表 nxt\[i][c]（後ろから作る・番兵 N） |
| abc452_e You WILL Like Sigma Problem | E | 1318 | [周期性の検出](../basics/periodicity.md) › 盤面・剰余の周期を割り算で数える、[調和級数と倍数の列挙](../math/harmonic-sum.md) › 値の倍数に印を付ける、[累積和](../basics/prefix-sum.md) |
| abc452_f Interval Inversion Count | F | 1630 | [尺取り法](../basics/two-pointers.md)、[転倒数](../ds/inversion-number.md) › 窓を伸縮しながら転倒数を増減する（尺取り・期待値と組む）、[BIT（Fenwick Tree）](../ds/fenwick-tree.md) |
| abc452_g 221 Substring | G | 2255 | [ランレングス圧縮](../basics/run-length-encoding.md) › ランレングスのまま処理する、[Suffix Automaton と発展の文字列アルゴリズム](../string/suffix-automaton.md) › Suffix Automaton（状態数 2N−1 以下・遷移数 3N−4 以下。文字の追加に強い）、[Suffix Array と LCP 配列](../string/suffix-array.md) › 異なる部分文字列の数 = N(N+1)/2 − Σlcp |
| abc453_d Go Straight | D | 1011 | [状態を頂点にする](../graph/extended-dijkstra.md#parity-mod-direction) › 偶奇・mod・向きを持つ、[幅優先探索（BFS）と無重み最短路](../graph/bfs.md)、[グリッドグラフ](../graph/grid-graph.md) |
| abc453_e Team Division | E | 1513 | [一部を固定して数える](../thinking/fix-variable.md)、[二項係数の前計算](../comb/binomial-precompute.md)、[いもす法](../basics/imos.md) › 1 次元のいもす法（閉区間なら右端 + 1 に −x） |
| abc453_f Avoid Division | F | 2811 | [木の重心](../tree/tree-centroid.md) › 重心で分けて別の枝どうしを組む、[構築問題の考え方](../thinking/construction.md) |
| abc453_g Copy Query | G | 1735 | [クエリの先読み](../ds/offline-queries.md)、[永続データ構造](../ds/persistent-data-structures.md) › 操作の版を木にしてオフラインで処理する（版の木の DFS と取り消し）、[オイラーツアー](../tree/euler-tour.md) |
| abc454_d (xx) | D | 706 | [スタック・キュー・deque の使いどころ](../ds/stack-techniques.md) › 直前と打ち消し合うものを消す（末尾を見て pop） |
| abc454_e LRUD Moving | E | 1627 | [偶奇に着目する](../thinking/parity.md) › 市松模様の偶奇、[構築問題の考え方](../thinking/construction.md) |
| abc454_f Make it Palindrome 2 | F | 2169 | [差分列への言い換え](../basics/difference-sequence.md) › 回文にする操作は左右の差の列に直してから差分を取る、[言い換えの典型](../thinking/reformulation.md) › 操作の言い換え（区間操作を差分列で・隣接 swap を転倒数で）、[貪欲法の考え方と正当性](../basics/greedy-basics.md) |
| abc454_g Mode in the Subtree | G | 2253 | [マージテク](../tree/small-to-large.md) › DSU on Tree（重い子の結果を残す） |
| abc455_d Card Pile Query | D | 796 | [配列で作る連結リスト](../ds/linked-list.md) › 挿入・削除・付け替えの手順 |
| abc455_e Unbalanced ABC Substrings | E | 1157 | [余事象](../thinking/complement.md) › 2〜3 条件の包除（重なりを足し戻す）、[累積和と連想配列で区間を数える](../basics/prefix-sum-counting.md) › S_r − S_l = K となる l を数える（S_0 を入れ忘れない） |
| abc455_f Merge Slimes 2 | F | 1549 | [主客転倒・寄与](../thinking/contribution.md)、[Σ の変形](../math/sigma-manipulation.md) › よく使う和の公式と Σ_{i≠j} a_i a_j = (Σa)² − Σa²、[遅延セグメント木の載せ方の型](../ds/lazy-segment-tree-patterns.md) › 設計の手順と載せられる条件（S はモノイド・F は恒等写像を含み合成で閉じる・f(x·y) = f(x)·f(y)） |
| abc455_g Balanced Subarrays | G | 3092 | [集合・多重集合のハッシュ](../string/hashing-for-sets.md) › 接頭辞・区間のハッシュ（集合の接頭辞は初めて出た値だけ入れる）、[尺取り法](../basics/two-pointers.md) |
| abc456_d Not Adjacent 2 | D | 586 | [DP の状態の設計](../dp/dp-state-design.md) › 末尾の数文字を状態にする（禁止された並び・回文を避ける） |
| abc456_e Endless Holidays | E | 1214 | [状態を頂点にする](../graph/extended-dijkstra.md#layered-graph) › 頂点倍化（層を作り、層の間の辺でコストを表す）、[閉路の検出と復元](../graph/cycle-detection.md) › 有向グラフ：3 色の DFS（探索中の頂点への辺だけが閉路） |
| abc456_f Plan Holidays | F | 1888 | [セグメント木に何を載せるか](../ds/segment-tree-monoids.md) › 行列を載せる（(min,+)・(max,+) の半環も。行列の積は行列累乗のページ、1 点更新のたびに DP を求め直すなら動的 DP）、[行列累乗](../math/matrix-power.md) › (min,+)・(max,+) などの半環の行列と単位元・零元 |
| abc456_g Count Holidays | G | 2488 | [包除原理](../comb/inclusion-exclusion.md) › 対称なら破る個数 k ごとに足す、[重複組合せ](../comb/stars-and-bars.md) › 玉と仕切りの対応（非負解と正の解）、[数え上げの考え方](../comb/counting-mindset.md) › 「ちょうど」を「以下」の差で数える |
| abc457_d Raise Minimum | D | 677 | [答えで二分探索](../basics/binary-search-answer.md#minimax) › 最大値の最小化・最小値の最大化 |
| abc457_e Crossing Table Cloth | E | 1428 | [ソートで考える](../basics/sorting-techniques.md)、[二分探索](../basics/binary-search.md) › lower_bound・upper_bound と個数の数え方 |
| abc457_f Second Gap | F | 2167 | [対称性・鳩の巣原理・場合分け](../thinking/symmetry-pigeonhole-casework.md) › 場合分け（端の場合・大小関係・操作の順序によらないこと）、[数え上げの考え方](../comb/counting-mindset.md)、[DP の状態の設計](../dp/dp-state-design.md) › 典型の要約（直前の値・on/off・偶奇・個数・上限で打ち切った値） |
| abc457_g Catch All Apples | G | 1928 | [マンハッタン距離と 45 度回転](../geometry/manhattan-chebyshev.md) › 45 度回転：\|Δx\|+\|Δy\| = max(\|Δu\|, \|Δv\|) になる理由、[最長増加部分列](../dp/lis.md) › Dilworth の定理（増加列への最小分割数＝最長減少部分列の長さ） |
| abc458_d Chalkboard Median | D | 450 | [上位 K 個の和と中央値の管理](../ds/top-k-multiset.md) › 中央値を保つ（個数の差を 1 以内に。削除がなければヒープ 2 本）と Σ\|x − a_i\| の更新 |
| abc458_e Count 123 | E | 1309 | [一部を固定して数える](../thinking/fix-variable.md)、[二項係数の前計算](../comb/binomial-precompute.md) |
| abc458_f Critical Misread | F | 1744 | [Aho-Corasick 法](../string/aho-corasick.md) › 照合オートマトンとして使う（DP・行列累乗）、[照合オートマトン上の DP](../string/string-automaton-dp.md) › N が巨大なとき：遷移行列の累乗・ダブリング、[行列累乗](../math/matrix-power.md) › DP の遷移を行列にする（照合の状態・末尾の数文字・グリッドの境界の状態） |
| abc458_g Children Yearn for the Evil Kindergarten | G | 2831 | [答えで二分探索](../basics/binary-search-answer.md#dp-check) › 判定を DP で作る（決め打ちごとに初期化し直す）、[Monge 性による DP の高速化](../dp/monge.md) › 凸な列どうしの (max,+) 畳み込み（差分のマージ）、[Slope Trick](../dp/slope-trick.md) › 凸関数を傾きの変わる点の集まりで表す |
| abc459_d Adjacent Distinct String | D | 701 | [貪欲法の考え方と正当性](../basics/greedy-basics.md) › 基準を決めて強い順に使う、[対称性・鳩の巣原理・場合分け](../thinking/symmetry-pigeonhole-casework.md) › 鳩の巣原理（必ず一致が起きる・探索の打ち切り回数） |
| abc459_e Select from Subtrees | E | 1298 | [葉から考える](../tree/leaf-first.md) › 帰りがけ順に葉から情報を上へ送る、[根付き木と走査順](../tree/tree-traversal.md) › 行きがけ順と帰りがけ順（子から親へ集約する）、[二項係数の前計算](../comb/binomial-precompute.md) |
| abc459_f -1, +1 | F | 2163 | [差分列への言い換え](../basics/difference-sequence.md) › 狭義の条件は a_i − i で広義に直してから差分を取る、[言い換えの典型](../thinking/reformulation.md) › 操作の言い換え（区間操作を差分列で・隣接 swap を転倒数で） |
| abc459_g Golf 2 | G | 3123 | [偶奇に着目する](../thinking/parity.md) › 市松模様の偶奇、[拡張ユークリッドの互除法と一次合同式](../math/ext-gcd.md) › ax + by = c の解の存在条件と一般解 x = x0 + k·b/g |
| abc460_d Repeatedly Repainting | D | 1216 | [幅優先探索（BFS）と無重み最短路](../graph/bfs.md) › 多始点 BFS（超始点から距離 0 の辺を張るのと同じ）、[グリッドグラフ](../graph/grid-graph.md) › 4 近傍・8 近傍と dx・dy の配列、[偶奇に着目する](../thinking/parity.md) › 1 歩ごとに偶奇が入れ替わる |
| abc460_e x + y ≡ x + y | E | 1362 | [桁と mod](../math/digit-and-mod.md) › 数の連結：x の後ろに d 桁の y を付けると x·10^d + y、[整数の割り算と余り](../math/integer-division.md) › 区間 [L, R] の K の倍数の個数と、x 以上で m で割って r 余る最小の数、[GCD・LCM とユークリッドの互除法](../math/gcd-lcm.md) |
| abc460_f Farthest Pair Query | F | 1987 | [木の直径と最遠点](../tree/tree-diameter.md)、[セグメント木に何を載せるか](../ds/segment-tree-monoids.md)、[最小共通祖先（LCA）](../tree/lca.md) › 距離 = dep(u) + dep(v) − 2 dep(lca) |
| abc460_g Vertex Flip Query | G | 2838 | [HL 分解](../tree/hld.md)、[セグメント木](../ds/segment-tree.md) |
| abc461_d Count Subgrid Sum = K | D | 914 | [2 次元累積和](../basics/prefix-sum-2d.md) › 前計算の式と長方形の和（4 項の包除）、[尺取り法](../basics/two-pointers.md)、[一部を固定して数える](../thinking/fix-variable.md) |
| abc461_e E-liter | E | 1431 | [セグメント木](../ds/segment-tree.md)、[主客転倒・寄与](../thinking/contribution.md) |
| abc461_f Total Product is N | F | 1940 | [約数の個数の上界と高度合成数](../math/divisor-count-bound.md) › 約数を状態にした DP（約数の個数が少ないことを使う）、[ナップサック DP](../dp/knapsack-01.md)、[約数列挙と素数判定](../math/divisor-enum.md) › 約数の列挙とソート・平方数での重複 |
| abc461_g Graph Problem 2026 | G | 2391 | [König の定理](../graph/konig-theorem.md) › 頂点を 2 倍にして二部グラフにする（LP の半整数性）、[二部マッチング](../graph/bipartite-matching.md) › 最大流への帰着（容量 1） |
| abc462_d Accomplice | D | 798 | [いもす法](../basics/imos.md) › 1 次元のいもす法（閉区間なら右端 + 1 に −x） |
| abc462_e Alternating Costs | E | 1226 | [対称性・鳩の巣原理・場合分け](../thinking/symmetry-pigeonhole-casework.md) › 対称性で場合を減らす（N ≤ M に入れ替える） |
| abc462_f More ABC | F | 1952 | [DP の状態の設計](../dp/dp-state-design.md) › 末尾の数文字を状態にする（禁止された並び・回文を避ける） |
| abc462_g Completely Wrong | G | 2232 | [包除原理](../comb/inclusion-exclusion.md) › 撹乱順列（完全順列）、[分割統治 FFT・オンライン畳み込み](../math/online-convolution.md) › 多数の多項式の積（次数の小さいものから掛ける・分割統治） |
| abc463_d Maximize the Gap | D | 838 | [答えで二分探索](../basics/binary-search-answer.md#greedy-check) › 判定を貪欲・探索で作る |
| abc463_e Roads and Gates | E | 1055 | [状態を頂点にする](../graph/extended-dijkstra.md#super-vertex) › 超頂点・補助頂点で辺の数を減らす、[ダイクストラ法](../graph/dijkstra.md) |
| abc463_f Senshuraku | F | 2127 | [確率の基本](../comb/probability-basics.md) › 条件付き確率と全確率の公式、[対称性・鳩の巣原理・場合分け](../thinking/symmetry-pigeonhole-casework.md) › 場合分け（端の場合・大小関係・操作の順序によらないこと）、[二項係数の前計算](../comb/binomial-precompute.md) |
| abc463_g Random Walk Distance | G | 2452 | [確率 DP](../comb/probability-dp.md) › ランダムウォークと二項係数、[二項係数の前計算](../comb/binomial-precompute.md)、[クエリの先読み](../ds/offline-queries.md) |
| abc464_d Celester | D | 752 | [DP の状態の設計](../dp/dp-state-design.md) › 典型の要約（直前の値・on/off・偶奇・個数・上限で打ち切った値） |
| abc464_e Fill-Rect Query | E | 1075 | [いもす法](../basics/imos.md) › 2 次元いもす法（四隅に ±1、横と縦に累積） |
| abc464_f Random Vault Heist | F | 2225 | [対称性で確率を求める](../comb/probability-symmetry.md) › 残りから一様に選ぶ = ランダムな順列、[期待値の線形性と指示確率変数](../comb/linearity-of-expectation.md)、[半分全列挙](../basics/meet-in-the-middle.md) › 前半・後半を列挙して突き合わせる（ソート＋二分探索・尺取り）、[尺取り法](../basics/two-pointers.md) |
| abc464_g Celester 2 | G | 2592 | [Alien DP](../dp/alien-dp.md) › 取り消し付きの貪欲で解ける場合（優先度付きキュー）、[優先度付きキューを使う貪欲](../basics/greedy-priority-queue.md) › 選んだものを後から入れ替える（後悔付き貪欲。一般形は Alien DP のページ） |
| abc465_d X to Y | D | 839 | [完全二分木](../tree/complete-binary-tree.md) › 番号だけで LCA を求める（大きい方を 2 で割る）、[完全二分木](../tree/complete-binary-tree.md) › K 分木への一般化 |
| abc465_e Digit Circus | E | 1417 | [桁 DP](../dp/digit-dp.md) › 問題の情報を状態に足す（桁和の余り・個数） |
| abc465_f Sjeltzer? | F | 1754 | [2 次元累積和](../basics/prefix-sum-2d.md) › 3 次元以上（項の数と符号の決め方）、[いもす法](../basics/imos.md) |
| abc465_g Sum of Mex of Mod of Linear | G | 3082 | —（対応するページがない） |
| abc466_d Placing Rooks | D | 494 | —（対応するページがない） |
| abc466_e Range Flip | E | 1027 | [いもす法](../basics/imos.md) › 区間反転を切り替え点 2 つで表す、[フェーズを状態に持つ DP](../dp/dp-phase.md) › 区間の反転・変更を段階の切り替えで表す、[言い換えの典型](../thinking/reformulation.md) › 操作の言い換え（区間操作を差分列で・隣接 swap を転倒数で） |
| abc466_f Many Mod Calculation | F | 1887 | [後ろから・逆順に考える](../thinking/reverse-thinking.md)、[set・multiset・map の応用](../ds/ordered-set.md) |
| abc466_g Segment Sum Constraints | G | 3347 | [桁 DP の応用](../dp/digit-dp-advanced.md) › 下の桁からの繰り上がりを状態にする、[桁 DP](../dp/digit-dp.md) › 2 進の桁 DP（XOR・AND） |
| abc467_d Concentric Circles | D | 928 | [誤差の扱いと整数での処理](../geometry/geometry-precision.md) › 方向・直線の正規化：gcd で約分し、(1, −1) と (−1, 1) を同じにする符号の決め方、[ベクトルと外積](../geometry/geometry-vectors.md) › 外積と内積の意味（符号と大きさ） |
| abc467_e Adjacent Sums (hard) | E | 1694 | [一部を固定して数える](../thinking/fix-variable.md)、[偶奇に着目する](../thinking/parity.md) › 1 歩ごとに偶奇が入れ替わる、[イベントソートと平面走査の基本](../basics/event-sort.md) |
| abc467_f Email Scheduling Optimization | F | 2052 | [交換論法と比較関数の設計](../basics/exchange-argument.md)、[セグメント木](../ds/segment-tree.md)、[座標圧縮](../basics/coordinate-compression.md) |
| abc467_g Many Sweets Problem | G | 2544 | [クエリの先読み](../ds/offline-queries.md)、[マージソート木](../ds/merge-sort-tree.md) › 各段に BIT を持たせる（先読みと組む）、[BIT（Fenwick Tree）](../ds/fenwick-tree.md) |
| abc468_d Pre-Palindrome | D | 683 | [回文の扱いと Manacher](../string/palindrome.md) › 中心から伸ばす O(N^2)（奇数長と偶数長の中心） |
| abc468_e Sum of Average | E | 1038 | [主客転倒・寄与](../thinking/contribution.md) › 数える対象を入れ替える（表の行と列。式の規則は Σ の変形のページ）、[逆元と mod での割り算](../math/mod-inverse.md) › 逆元表を O(N) で作る（inv[i] = −⌊m/i⌋·inv[m mod i]）と階乗の逆元、[累積和](../basics/prefix-sum.md) |
| abc468_f Chmax | F | 1693 | [最長増加部分列](../dp/lis.md) › 二分探索版（L が単調になる理由・狭義は lower_bound、広義は upper_bound）、[貪欲法の考え方と正当性](../basics/greedy-basics.md) |
| abc468_g Restricted Permutation | G | 1975 | [挿入 DP・箱根駅伝 DP](../dp/insertion-dp.md) |
| abc469_d The Big Two | D | 1102 | [全探索の設計](../basics/brute-force.md) › 候補が少ないことに気づく（答えの側・小さい次元・約数の個数・log 回の収束） |
| abc469_e Pro Exam Eligibility | E | 1566 | [平均・中央値の最大化](../basics/fractional-binary-search.md) › 平均の言い換え（x を引いた和の符号で判定する）、[累積和](../basics/prefix-sum.md) |
| abc469_f GCD Maximum Spanning Tree | F | 1567 | [最小全域木](../graph/minimum-spanning-tree.md) › 辺の候補を減らす（ソートした隣どうし・約数で絞る）、[最小全域木](../graph/minimum-spanning-tree.md) › 最大全域木、[調和級数と倍数の列挙](../math/harmonic-sum.md) › 倍数を回して集める（d の倍数である要素の個数・和を全ての d について求める） |
| abc469_g K-nacci Operations | G | 2804 | [行列累乗](../math/matrix-power.md) › 漸化式・状態の遷移を行列で書く（定数項を状態に入れる） |
| abc470_d Inverse and Swap | D | 777 | [順列と置換](../patterns/permutation.md) › 位置と値の両方から引く操作 → 逆置換を同時に持つ |
| abc470_e Concentration | E | 2096 | [最適戦略の期待値](../comb/optimal-strategy-expectation.md) › 残すもの・知っている情報を状態にする、[メモ化再帰](../dp/memoized-recursion.md) |
| abc470_f Googol Swaps | F | 1604 | [置換の偶奇](../comb/permutation-parity.md) › 同じ値があれば偶奇を調整できる、[連結成分](../graph/connected-components.md)、[多項係数](../comb/multinomial-coefficient.md) |
| abc470_g Σex | G | 2097 | [主客転倒・寄与](../thinking/contribution.md)、[尺取り法](../basics/two-pointers.md)、[遅延セグメント木](../ds/lazy-segment-tree.md)、[言い換えの典型](../thinking/reformulation.md) › 言い換えてからデータ構造に載せる |
| abc471_d Chargers | D | 570 | [優先度付きキュー](../ds/priority-queue.md) |
| abc471_e Sum of Square of Sum | E | 990 | [Σ の変形](../math/sigma-manipulation.md) › よく使う和の公式と Σ_{i≠j} a_i a_j = (Σa)² − Σa²、[数え上げの考え方](../comb/counting-mindset.md) › 二項係数と組み合わせた寄与（残りの選び方を掛ける）、[二項係数の前計算](../comb/binomial-precompute.md) |
| abc471_f Concat (maximize) | F | 1895 | [交換論法と比較関数の設計](../basics/exchange-argument.md) › 連結の比較（a+b と b+a）、[貪欲法の考え方と正当性](../basics/greedy-basics.md) |
| abc471_g Caeser Syllables | G | 2464 | [主客転倒・寄与](../thinking/contribution.md) › 数える対象を入れ替える（表の行と列。式の規則は Σ の変形のページ）、[畳み込みの使い方](../math/convolution-ntt.md) |
| abc472_d Bomber Mad | D | 605 | [幅優先探索（BFS）と無重み最短路](../graph/bfs.md) › 多始点 BFS（超始点から距離 0 の辺を張るのと同じ） |
| abc472_e Odd Cycle | E | 1029 | [二部グラフ判定](../graph/bipartite-graph.md) › 二部グラフでないことと奇閉路があることは同じ |
| abc472_f Centroid of a Slice | F | 1707 | [ベクトルと外積](../geometry/geometry-vectors.md) › 三角形・多角形の面積：座標の公式（面積の 2 倍を整数のまま扱う）、[累積和](../basics/prefix-sum.md) |
| abc472_g Cascading Grid | G | 2018 | [燃やす埋める](../graph/project-selection.md) › 最大重み閉包（依存関係）、[最小カット](../graph/min-cut.md) |
| abc473_d Coefficient Stair | D | 838 | [再帰による全列挙](../basics/recursive-enumeration.md) |
| abc473_e K-Divisible Subarrays | E | 966 | [累積和と連想配列で区間を数える](../basics/prefix-sum-counting.md) › 余りが等しい組（M の倍数の区間・負の余りの正規化）、[貪欲法の考え方と正当性](../basics/greedy-basics.md) |
| abc473_f A/AB Insertion | F | 1303 | [遅延セグメント木](../ds/lazy-segment-tree.md#acl-standard) › ACL の lazy_segtree で標準の型を呼ぶ、[累積和](../basics/prefix-sum.md) |
| abc473_g Wipeout | G | 1974 | [対称性で確率を求める](../comb/probability-symmetry.md) › 残りから一様に選ぶ = ランダムな順列、[挿入 DP・箱根駅伝 DP](../dp/insertion-dp.md)、[形式的冪級数と多項式の演算](../math/fps-basics.md) |
| abc474_d Outweigh | D | 389 | [構築問題の考え方](../thinking/construction.md) |
| abc474_e One Time Coupon | E | 1153 | [ソートで考える](../basics/sorting-techniques.md)、[全探索の設計](../basics/brute-force.md)、[累積和](../basics/prefix-sum.md) › 左右からの累積（1 つ除いた gcd・max） |
| abc474_f Increment All Divisors | F | 1911 | [約数・倍数のゼータ変換とメビウス変換](../comb/zeta-mobius-divisor.md) › 逆変換（メビウス変換）と回す向き |
| abc474_g LRUD Moving 2 | G | 2280 | [偶奇に着目する](../thinking/parity.md) › 市松模様の偶奇、[構築問題の考え方](../thinking/construction.md) › 小さい N で作って規則を一般化する |
| abc475_d Alphametic Prime | D | 741 | [再帰による全列挙](../basics/recursive-enumeration.md)、[エラトステネスの篩](../math/sieve-eratosthenes.md) |
| abc475_e Quiz Competition: Qualifiers | E | 1737 | [言い換えの典型](../thinking/reformulation.md)、[set・multiset・map の応用](../ds/ordered-set.md) |
| abc475_f Rectangle Filling | F | 1916 | [包除原理](../comb/inclusion-exclusion.md)、[2 次元累積和](../basics/prefix-sum-2d.md) |
| abc475_g Has Many Divisors | G | 2360 | [約数の個数の上界と高度合成数](../math/divisor-count-bound.md) › 高度合成数の列挙（小さい素数の指数が単調に減る形を DFS で） |
| abc476_d Automat | D | 860 | [全探索の設計](../basics/brute-force.md)、[累積和](../basics/prefix-sum.md) › 累積和の上で二分探索・尺取り、[二分探索](../basics/binary-search.md) |
| abc476_e Min-Max Swap | E | 964 | [セグメント木](../ds/segment-tree.md) |
| abc476_f Chebyshev Cafe | F | 1728 | [マンハッタン距離と 45 度回転](../geometry/manhattan-chebyshev.md) › 絶対値の外し方：向きを固定して場合分けし、盤面を反転してもう一度、[グリッド上の DP](../dp/dp-grid.md) › 方向ごとの累積和で遷移をまとめる |
| abc476_g Increasing Popcount | G | 2477 | [最長増加部分列](../dp/lis.md) › Dilworth の定理（増加列への最小分割数＝最長減少部分列の長さ）、[bit 演算の基本と XOR の性質](../basics/bit-operations.md) › popcount・最下位ビット、[再帰的な構造](../basics/recursion-structure.md)、[二項係数の意味と性質](../comb/binomial-coefficient.md) |
| abc477_d Masking Tape | D | 946 | [後ろから・逆順に考える](../thinking/reverse-thinking.md) › 後ろから決めると一意になる |
| abc477_e Wheel Distance | E | 1235 | [ダイクストラ法](../graph/dijkstra.md)、[累積和](../basics/prefix-sum.md) › 円環は 2 周分に伸ばす |
| abc477_f Count Cells in a Window | F | 1629 | [クエリの先読み](../ds/offline-queries.md)、[平面走査](../ds/sweep-line-2d.md) › 支配点の数え上げ・長方形内の点の数（4 つの接頭辞の包除、上端での値 − 下端の 1 つ前での値）、[遅延セグメント木](../ds/lazy-segment-tree.md) |
| abc477_g Frequency Query on Tree | G | 2226 | [Mo's algorithm](../ds/mo-algorithm.md) › 木上の Mo（入りと出の両方を記録した列で、パスを区間にする。LCA を別に足す）、[オイラーツアー](../tree/euler-tour.md) › 木上の Mo（データ構造の章）、[最小共通祖先（LCA）](../tree/lca.md) |
| abc478_d Range Set Insertion Query | D | 729 | [イベントソートと平面走査の基本](../basics/event-sort.md) › イベントの作り方と同じ座標での処理順 |
| abc478_e lt and le | E | 1376 | [強連結成分分解（SCC）](../graph/scc.md) › 縮約したグラフが DAG になる理由、[トポロジカルソート](../graph/topological-sort.md) |
| abc478_f Min-First Search | F | 1588 | [木の構築・復元](../tree/tree-construction.md) › 訪問順から親の候補を数える、[セグメント木上の二分探索](../ds/segment-tree-binary-search.md) |
| abc478_g Division Point Hull | G | 2582 | [分割統治](../basics/divide-and-conquer.md)、[凸包と凸多角形](../geometry/convex-hull.md) › Andrew 法（monotone chain）：下側と上側を作る、[発展の幾何](../geometry/advanced-geometry.md) › ミンコフスキー和（凸包の和） |
| abc479_d Back and Forth Distance | D | 563 | [累積和](../basics/prefix-sum.md) › 左右からの累積（1 つ除いた gcd・max） |
| abc479_e Cut and Add | E | 1000 | [辺で切って数える](../tree/tree-edge-contribution.md) › 辺を通るペアは s(N−s) 個、[根付き木と走査順](../tree/tree-traversal.md) › 親・深さ・部分木サイズを求める |
| abc479_f Narrow Passage | F | 1938 | [転倒数](../ds/inversion-number.md) › なぜ隣接 swap の最小回数か（1 回の隣接 swap で転倒数はちょうど 1 増減する）、[言い換えの典型](../thinking/reformulation.md) › 操作の言い換え（区間操作を差分列で・隣接 swap を転倒数で） |
| abc479_g Tuning | G | 2386 | [偏角ソート](../geometry/argument-sort.md) › 並べた後に：角度の範囲の点の数（累積和）、[累積和](../basics/prefix-sum.md) |
| abc480_d Concatenation of Prefixes | D | 864 | [累積和](../basics/prefix-sum.md) › 累積和の上で二分探索・尺取り、[二分探索](../basics/binary-search.md) |
| abc480_e Product-Bounded Arithmetic Sequences | E | 1355 | [全探索の設計](../basics/brute-force.md)、[二分探索](../basics/binary-search.md) |
| abc480_f Cake Cutting | F | 1840 | [言い換えの典型](../thinking/reformulation.md)、[bitDP](../dp/bit-dp.md#set-only) › 集合だけを状態にする（マッチングの数） |
| abc480_g Zonal Score Minimization | G | 2100 | [インライン DP](../dp/inline-dp.md) › 単調スタックと組み合わせる、[遅延セグメント木](../ds/lazy-segment-tree.md)、[単調スタックとスライド最小値](../ds/monotonic-stack.md) |

<!-- textlint-enable -->
<!-- gen:end recent-abc -->

<!-- gen:begin problem-sets -->
<!-- textlint-disable -->

### 競プロ典型 90 問 {#problem-sets-typical90}

| 問題 | diff | ページ（役割） |
| --- | --- | --- |
| 典型90 001. Yokan Party（★4） | — | [答えで二分探索](../basics/binary-search-answer.md)（例題） |
| 典型90 029. Long Bricks（★5） | — | [遅延セグメント木](../ds/lazy-segment-tree.md)（練習） |
| 典型90 066. Various Arrays（★5） | — | [期待値の線形性と指示確率変数](../comb/linearity-of-expectation.md)（例題） |

### EDPC（Educational DP Contest） {#problem-sets-dp}

| 問題 | diff | ページ（役割） |
| --- | --- | --- |
| EDPC O. Matching | — | [bitDP](../dp/bit-dp.md)（例題） |

### ACL Practice（AtCoder Library Practice Contest） {#problem-sets-practice2}

| 問題 | diff | ページ（役割） |
| --- | --- | --- |
| PRACTICE2 C. Floor Sum | — | [floor sum](../math/floor-sum.md)（例題） |
| PRACTICE2 K. Range Affine Range Sum | — | [遅延セグメント木](../ds/lazy-segment-tree.md)（例題） |

### ABL {#problem-sets-abl}

| 問題 | diff | ページ（役割） |
| --- | --- | --- |
| ABL E. Replace Digits | 1706 | [遅延セグメント木](../ds/lazy-segment-tree.md)（練習） |

<!-- textlint-enable -->
<!-- gen:end problem-sets -->
