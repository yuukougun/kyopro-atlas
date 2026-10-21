---
id: library-design
title: 自作ライブラリの設計と動作確認
aliases: [ライブラリ整備, 自作ライブラリ, Library Checker, verify, ライブラリの動作確認]
type: guide
field: guide
chapter: 早見表と資料
order: 150
level: null
kind: [案内, 実装・C++]
prerequisites: []
related: [acl-reading#segtree-args, cpp-macros-template-file#bundling, segment-tree-monoids, stress-testing, problem-sets#verify-sets]
summary: 自作ライブラリを何から作るか、ACL を手本にしたインターフェースとヘッダの書き方、Library Checker などでの動作確認の手順がわかる。確認用の問題の対応表は各ページの verify から生成する。
complexity: null
signs: []
acl: []
sections:
  - {title: 何を自作するか, anchor: what-to-build}
  - {title: インターフェースの決め方, anchor: interface}
  - {title: ヘッダの書き方, anchor: headers}
  - {title: 提出用に 1 ファイルに展開する, anchor: bundling}
  - {title: 不変条件と境界のテスト, anchor: tests}
  - {title: 動作確認の手順, anchor: verify}
  - {title: ページ → 確認用の問題, anchor: verify-table}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何のページか**：自作ライブラリを何から作るか、ACL を手本にしたインターフェースとヘッダの書き方、Library Checker などでの動作確認の手順がわかる。確認用の問題の対応表は各ページの verify から生成する。
    - **使い方**：（執筆時に書く）

<!-- gen:begin verify-table -->
<!-- textlint-disable -->

| ページ | 分野 | Library Checker の問題 |
| --- | --- | --- |
| [最長増加部分列](../dp/lis.md) | 動的計画法 | [longest_increasing_subsequence](https://judge.yosupo.jp/problem/longest_increasing_subsequence) |
| [動的 DP](../dp/dynamic-dp.md)（準備中） | 動的計画法 | [point_set_range_composite](https://judge.yosupo.jp/problem/point_set_range_composite) |
| [Convex Hull Trick と Li Chao Tree](../dp/cht.md)（準備中） | 動的計画法 | [line_add_get_min](https://judge.yosupo.jp/problem/line_add_get_min)、[segment_add_get_min](https://judge.yosupo.jp/problem/segment_add_get_min) |
| [Monge 性による DP の高速化](../dp/monge.md)（準備中） | 動的計画法 | [min_plus_convolution_convex_arbitrary](https://judge.yosupo.jp/problem/min_plus_convolution_convex_arbitrary)、[min_plus_convolution_convex_convex](https://judge.yosupo.jp/problem/min_plus_convolution_convex_convex) |
| [閉路の検出と復元](../graph/cycle-detection.md) | グラフ | [cycle_detection](https://judge.yosupo.jp/problem/cycle_detection)、[cycle_detection_undirected](https://judge.yosupo.jp/problem/cycle_detection_undirected) |
| [彩色数・最大独立集合・最大クリーク](../graph/chromatic-number.md)（準備中） | グラフ | [chromatic_number](https://judge.yosupo.jp/problem/chromatic_number)、[maximum_independent_set](https://judge.yosupo.jp/problem/maximum_independent_set) |
| [ダイクストラ法](../graph/dijkstra.md) | グラフ | [shortest_path](https://judge.yosupo.jp/problem/shortest_path) |
| [補グラフ上の BFS](../graph/complement-graph-bfs.md)（準備中） | グラフ | [connected_components_of_complement_graph](https://judge.yosupo.jp/problem/connected_components_of_complement_graph) |
| [K 番目の最短路](../graph/k-shortest-paths.md)（準備中） | グラフ | [k_shortest_walk](https://judge.yosupo.jp/problem/k_shortest_walk) |
| [最小シュタイナー木](../graph/steiner-tree.md)（準備中） | グラフ | [minimum_steiner_tree](https://judge.yosupo.jp/problem/minimum_steiner_tree) |
| [強連結成分分解（SCC）](../graph/scc.md) | グラフ | [scc](https://judge.yosupo.jp/problem/scc) |
| [2-SAT](../graph/two-sat.md)（準備中） | グラフ | [two_sat](https://judge.yosupo.jp/problem/two_sat) |
| [最小全域木](../graph/minimum-spanning-tree.md) | グラフ | [minimum_spanning_tree](https://judge.yosupo.jp/problem/minimum_spanning_tree) |
| [橋・関節点・二重連結成分](../graph/lowlink.md)（準備中） | グラフ | [two_edge_connected_components](https://judge.yosupo.jp/problem/two_edge_connected_components)、[biconnected_components](https://judge.yosupo.jp/problem/biconnected_components) |
| [特殊な最小全域木](../graph/spanning-tree-advanced.md)（準備中） | グラフ | [directedmst](https://judge.yosupo.jp/problem/directedmst)、[manhattanmst](https://judge.yosupo.jp/problem/manhattanmst) |
| [行列木定理](../graph/matrix-tree-theorem.md)（準備中） | グラフ | [counting_spanning_tree_undirected](https://judge.yosupo.jp/problem/counting_spanning_tree_undirected)、[counting_spanning_tree_directed](https://judge.yosupo.jp/problem/counting_spanning_tree_directed) |
| [オイラー路（一筆書き）](../graph/euler-path.md)（準備中） | グラフ | [eulerian_trail_directed](https://judge.yosupo.jp/problem/eulerian_trail_directed)、[eulerian_trail_undirected](https://judge.yosupo.jp/problem/eulerian_trail_undirected) |
| [次数による平方分割](../graph/degree-sqrt.md)（準備中） | グラフ | [enumerate_triangles](https://judge.yosupo.jp/problem/enumerate_triangles)、[counting_c4](https://judge.yosupo.jp/problem/counting_c4) |
| [二部マッチング](../graph/bipartite-matching.md)（準備中） | グラフ | [bipartitematching](https://judge.yosupo.jp/problem/bipartitematching) |
| [最小費用流](../graph/min-cost-flow.md)（準備中） | グラフ | [min_cost_b_flow](https://judge.yosupo.jp/problem/min_cost_b_flow)、[assignment](https://judge.yosupo.jp/problem/assignment) |
| [一般グラフのマッチング](../graph/general-matching.md)（準備中） | グラフ | [general_matching](https://judge.yosupo.jp/problem/general_matching)、[general_weighted_matching](https://judge.yosupo.jp/problem/general_weighted_matching) |
| [木の直径と最遠点](../tree/tree-diameter.md) | 木 | [tree_diameter](https://judge.yosupo.jp/problem/tree_diameter) |
| [木の同型判定と木のハッシュ](../tree/tree-isomorphism.md)（準備中） | 木 | [rooted_tree_isomorphism_classification](https://judge.yosupo.jp/problem/rooted_tree_isomorphism_classification) |
| [最小共通祖先（LCA）](../tree/lca.md) | 木 | [lca](https://judge.yosupo.jp/problem/lca) |
| [木の上のパスの判定と分解](../tree/tree-path.md)（準備中） | 木 | [jump_on_tree](https://judge.yosupo.jp/problem/jump_on_tree) |
| [オイラーツアー](../tree/euler-tour.md) | 木 | [vertex_add_subtree_sum](https://judge.yosupo.jp/problem/vertex_add_subtree_sum) |
| [HL 分解](../tree/hld.md) | 木 | [vertex_set_path_composite](https://judge.yosupo.jp/problem/vertex_set_path_composite) |
| [Static Top Tree と木 DP の動的更新](../tree/static-top-tree.md)（準備中） | 木 | [point_set_tree_path_composite_sum](https://judge.yosupo.jp/problem/point_set_tree_path_composite_sum) |
| [動的木](../tree/dynamic-tree.md)（準備中） | 木 | [dynamic_tree_vertex_add_path_sum](https://judge.yosupo.jp/problem/dynamic_tree_vertex_add_path_sum) |
| [重心分解](../tree/centroid-decomposition.md)（準備中） | 木 | [frequency_table_of_tree_distance](https://judge.yosupo.jp/problem/frequency_table_of_tree_distance) |
| [比で親に併合する貪欲](../tree/tree-ratio-greedy.md)（準備中） | 木 | [rooted_tree_topological_order_with_minimum_inversions](https://judge.yosupo.jp/problem/rooted_tree_topological_order_with_minimum_inversions) |
| [STL コンテナの使い分け](../ds/stl-containers.md) | データ構造 | [associative_array](https://judge.yosupo.jp/problem/associative_array) |
| [set・multiset・map の応用](../ds/ordered-set.md) | データ構造 | [predecessor_problem](https://judge.yosupo.jp/problem/predecessor_problem)、[double_ended_priority_queue](https://judge.yosupo.jp/problem/double_ended_priority_queue) |
| [単調スタックとスライド最小値](../ds/monotonic-stack.md) | データ構造 | [queue_operate_all_composite](https://judge.yosupo.jp/problem/queue_operate_all_composite)、[deque_operate_all_composite](https://judge.yosupo.jp/problem/deque_operate_all_composite) |
| [Union-Find](../ds/union-find.md) | データ構造 | [unionfind](https://judge.yosupo.jp/problem/unionfind) |
| [重み付き Union-Find](../ds/weighted-union-find.md) | データ構造 | [unionfind_with_potential](https://judge.yosupo.jp/problem/unionfind_with_potential)、[unionfind_with_potential_non_commutative_group](https://judge.yosupo.jp/problem/unionfind_with_potential_non_commutative_group) |
| [ロールバックできる Union-Find](../ds/rollback-union-find.md)（準備中） | データ構造 | [dynamic_graph_vertex_add_component_sum](https://judge.yosupo.jp/problem/dynamic_graph_vertex_add_component_sum) |
| [BIT（Fenwick Tree）](../ds/fenwick-tree.md) | データ構造 | [point_add_range_sum](https://judge.yosupo.jp/problem/point_add_range_sum)、[static_range_sum](https://judge.yosupo.jp/problem/static_range_sum) |
| [K 番目の値を求めるデータ構造](../ds/kth-element.md) | データ構造 | [ordered_set](https://judge.yosupo.jp/problem/ordered_set) |
| [セグメント木](../ds/segment-tree.md) | データ構造 | [point_set_range_composite](https://judge.yosupo.jp/problem/point_set_range_composite) |
| [値を添字にする BIT・セグメント木](../ds/segment-tree-on-values.md) | データ構造 | [point_set_range_composite_large_array](https://judge.yosupo.jp/problem/point_set_range_composite_large_array) |
| [遅延セグメント木](../ds/lazy-segment-tree.md) | データ構造 | [range_affine_range_sum](https://judge.yosupo.jp/problem/range_affine_range_sum)、[range_add_range_min](https://judge.yosupo.jp/problem/range_add_range_min)、[range_affine_point_get](https://judge.yosupo.jp/problem/range_affine_point_get) |
| [遅延セグメント木の載せ方の型](../ds/lazy-segment-tree-patterns.md)（準備中） | データ構造 | [range_set_range_composite](https://judge.yosupo.jp/problem/range_set_range_composite) |
| [Sparse Table](../ds/sparse-table.md)（準備中） | データ構造 | [staticrmq](https://judge.yosupo.jp/problem/staticrmq) |
| [Segment Tree Beats](../ds/segment-tree-beats.md)（準備中） | データ構造 | [range_chmin_chmax_add_range_sum](https://judge.yosupo.jp/problem/range_chmin_chmax_add_range_sum) |
| [クエリの先読み](../ds/offline-queries.md) | データ構造 | [static_range_count_distinct](https://judge.yosupo.jp/problem/static_range_count_distinct)、[static_range_frequency](https://judge.yosupo.jp/problem/static_range_frequency) |
| [平面走査](../ds/sweep-line-2d.md)（準備中） | データ構造 | [rectangle_sum](https://judge.yosupo.jp/problem/rectangle_sum)、[area_of_union_of_rectangles](https://judge.yosupo.jp/problem/area_of_union_of_rectangles) |
| [Mo's algorithm](../ds/mo-algorithm.md)（準備中） | データ構造 | [static_range_inversions_query](https://judge.yosupo.jp/problem/static_range_inversions_query) |
| [平方分割](../ds/sqrt-decomposition.md)（準備中） | データ構造 | [static_range_mode_query](https://judge.yosupo.jp/problem/static_range_mode_query) |
| [CDQ 分割統治](../ds/cdq-divide-and-conquer.md)（準備中） | データ構造 | [point_add_rectangle_sum](https://judge.yosupo.jp/problem/point_add_rectangle_sum) |
| [永続データ構造](../ds/persistent-data-structures.md)（準備中） | データ構造 | [persistent_queue](https://judge.yosupo.jp/problem/persistent_queue)、[persistent_range_affine_range_sum](https://judge.yosupo.jp/problem/persistent_range_affine_range_sum) |
| [マージソート木](../ds/merge-sort-tree.md)（準備中） | データ構造 | [static_range_sum_with_upper_bound](https://judge.yosupo.jp/problem/static_range_sum_with_upper_bound) |
| [Wavelet Matrix](../ds/wavelet-matrix.md)（準備中） | データ構造 | [range_kth_smallest](https://judge.yosupo.jp/problem/range_kth_smallest) |
| [Binary Trie](../ds/binary-trie.md)（準備中） | データ構造 | [set_xor_min](https://judge.yosupo.jp/problem/set_xor_min) |
| [平衡二分探索木と pb_ds の tree](../ds/balanced-bst.md)（準備中） | データ構造 | [range_reverse_range_sum](https://judge.yosupo.jp/problem/range_reverse_range_sum)、[dynamic_sequence_range_affine_range_sum](https://judge.yosupo.jp/problem/dynamic_sequence_range_affine_range_sum) |
| [フェルマーの小定理と指数の mod](../math/exponent-mod.md) | 整数論・代数 | [tetration_mod](https://judge.yosupo.jp/problem/tetration_mod) |
| [エラトステネスの篩](../math/sieve-eratosthenes.md) | 整数論・代数 | [enumerate_primes](https://judge.yosupo.jp/problem/enumerate_primes) |
| [大きな数の素数判定と素因数分解](../math/miller-rabin.md)（準備中） | 整数論・代数 | [primality_test](https://judge.yosupo.jp/problem/primality_test)、[factorize](https://judge.yosupo.jp/problem/factorize) |
| [位数・原始根・離散対数](../math/multiplicative-order.md)（準備中） | 整数論・代数 | [discrete_logarithm_mod](https://judge.yosupo.jp/problem/discrete_logarithm_mod)、[primitive_root](https://judge.yosupo.jp/problem/primitive_root)、[sqrt_mod](https://judge.yosupo.jp/problem/sqrt_mod)、[kth_root_mod](https://judge.yosupo.jp/problem/kth_root_mod) |
| [整数の平方根・K 乗根と累乗数](../math/integer-root.md) | 整数論・代数 | [kth_root_integer](https://judge.yosupo.jp/problem/kth_root_integer) |
| [商の列挙](../math/floor-quotient-enum.md) | 整数論・代数 | [enumerate_quotients](https://judge.yosupo.jp/problem/enumerate_quotients) |
| [乗法的関数の和と素数の個数](../math/multiplicative-function.md)（準備中） | 整数論・代数 | [counting_primes](https://judge.yosupo.jp/problem/counting_primes)、[sum_of_totient_function](https://judge.yosupo.jp/problem/sum_of_totient_function)、[sum_of_multiplicative_function](https://judge.yosupo.jp/problem/sum_of_multiplicative_function) |
| [floor sum](../math/floor-sum.md) | 整数論・代数 | [sum_of_floor_of_linear](https://judge.yosupo.jp/problem/sum_of_floor_of_linear)、[min_of_mod_of_linear](https://judge.yosupo.jp/problem/min_of_mod_of_linear) |
| [Stern-Brocot 木と連分数](../math/stern-brocot.md)（準備中） | 整数論・代数 | [stern_brocot_tree](https://judge.yosupo.jp/problem/stern_brocot_tree)、[rational_approximation](https://judge.yosupo.jp/problem/rational_approximation) |
| [行列累乗](../math/matrix-power.md) | 整数論・代数 | [matrix_product](https://judge.yosupo.jp/problem/matrix_product)、[pow_of_matrix](https://judge.yosupo.jp/problem/pow_of_matrix) |
| [掃き出し法](../math/gaussian-elimination.md)（準備中） | 整数論・代数 | [system_of_linear_equations](https://judge.yosupo.jp/problem/system_of_linear_equations)、[system_of_linear_equations_mod_2](https://judge.yosupo.jp/problem/system_of_linear_equations_mod_2)、[matrix_rank](https://judge.yosupo.jp/problem/matrix_rank)、[matrix_rank_mod_2](https://judge.yosupo.jp/problem/matrix_rank_mod_2)、[inverse_matrix](https://judge.yosupo.jp/problem/inverse_matrix) |
| [XOR 基底](../math/xor-basis.md)（準備中） | 整数論・代数 | [intersection_of_f2_vector_spaces](https://judge.yosupo.jp/problem/intersection_of_f2_vector_spaces) |
| [行列式](../math/determinant.md)（準備中） | 整数論・代数 | [matrix_det](https://judge.yosupo.jp/problem/matrix_det)、[matrix_det_mod_2](https://judge.yosupo.jp/problem/matrix_det_mod_2)、[matrix_det_arbitrary_mod](https://judge.yosupo.jp/problem/matrix_det_arbitrary_mod) |
| [畳み込みの使い方](../math/convolution-ntt.md)（準備中） | 整数論・代数 | [convolution_mod](https://judge.yosupo.jp/problem/convolution_mod)、[wildcard_pattern_matching](https://judge.yosupo.jp/problem/wildcard_pattern_matching) |
| [FFT・NTT の仕組みと任意 mod の畳み込み](../math/fft-ntt.md)（準備中） | 整数論・代数 | [convolution_mod](https://judge.yosupo.jp/problem/convolution_mod)、[convolution_mod_1000000007](https://judge.yosupo.jp/problem/convolution_mod_1000000007)、[convolution_mod_2_64](https://judge.yosupo.jp/problem/convolution_mod_2_64) |
| [XOR 畳み込み](../math/hadamard-transform.md)（準備中） | 整数論・代数 | [bitwise_xor_convolution](https://judge.yosupo.jp/problem/bitwise_xor_convolution) |
| [形式的冪級数と多項式の演算](../math/fps-basics.md)（準備中） | 整数論・代数 | [inv_of_formal_power_series](https://judge.yosupo.jp/problem/inv_of_formal_power_series)、[log_of_formal_power_series](https://judge.yosupo.jp/problem/log_of_formal_power_series)、[exp_of_formal_power_series](https://judge.yosupo.jp/problem/exp_of_formal_power_series)、[pow_of_formal_power_series](https://judge.yosupo.jp/problem/pow_of_formal_power_series)、[sqrt_of_formal_power_series](https://judge.yosupo.jp/problem/sqrt_of_formal_power_series)、[division_of_polynomials](https://judge.yosupo.jp/problem/division_of_polynomials)、[polynomial_taylor_shift](https://judge.yosupo.jp/problem/polynomial_taylor_shift)、[multipoint_evaluation](https://judge.yosupo.jp/problem/multipoint_evaluation)、[polynomial_interpolation](https://judge.yosupo.jp/problem/polynomial_interpolation) |
| [線形漸化式の高速化](../math/linear-recurrence-fast.md)（準備中） | 整数論・代数 | [kth_term_of_linearly_recurrent_sequence](https://judge.yosupo.jp/problem/kth_term_of_linearly_recurrent_sequence)、[find_linear_recurrence](https://judge.yosupo.jp/problem/find_linear_recurrence)、[consecutive_terms_of_linear_recurrent_sequence](https://judge.yosupo.jp/problem/consecutive_terms_of_linear_recurrent_sequence) |
| [ラグランジュ補間とべき乗和](../math/lagrange-interpolation.md)（準備中） | 整数論・代数 | [shift_of_sampling_points_of_polynomial](https://judge.yosupo.jp/problem/shift_of_sampling_points_of_polynomial)、[sum_of_exponential_times_polynomial](https://judge.yosupo.jp/problem/sum_of_exponential_times_polynomial) |
| [部分集合の高速ゼータ変換とメビウス変換](../comb/zeta-mobius-subset.md)（準備中） | 数え上げ・確率・ゲーム | [bitwise_and_convolution](https://judge.yosupo.jp/problem/bitwise_and_convolution) |
| [Z-algorithm](../string/z-algorithm.md) | 文字列 | [zalgorithm](https://judge.yosupo.jp/problem/zalgorithm) |
| [回文の扱いと Manacher](../string/palindrome.md) | 文字列 | [enumerate_palindromes](https://judge.yosupo.jp/problem/enumerate_palindromes) |
| [Aho-Corasick 法](../string/aho-corasick.md)（準備中） | 文字列 | [aho_corasick](https://judge.yosupo.jp/problem/aho_corasick) |
| [Suffix Array と LCP 配列](../string/suffix-array.md) | 文字列 | [suffixarray](https://judge.yosupo.jp/problem/suffixarray)、[number_of_substrings](https://judge.yosupo.jp/problem/number_of_substrings) |
| [Suffix Automaton と発展の文字列アルゴリズム](../string/suffix-automaton.md)（準備中） | 文字列 | [eertree](https://judge.yosupo.jp/problem/eertree)、[lyndon_factorization](https://judge.yosupo.jp/problem/lyndon_factorization)、[runenumerate](https://judge.yosupo.jp/problem/runenumerate) |
| [偏角ソート](../geometry/argument-sort.md) | 幾何 | [sort_points_by_argument](https://judge.yosupo.jp/problem/sort_points_by_argument) |
| [円と幾何の最適化](../geometry/circle-geometry.md)（準備中） | 幾何 | [minimum_enclosing_circle](https://judge.yosupo.jp/problem/minimum_enclosing_circle) |
| [凸包と凸多角形](../geometry/convex-hull.md)（準備中） | 幾何 | [static_convex_hull](https://judge.yosupo.jp/problem/static_convex_hull) |
| [発展の幾何](../geometry/advanced-geometry.md)（準備中） | 幾何 | [closest_pair](https://judge.yosupo.jp/problem/closest_pair)、[furthest_pair](https://judge.yosupo.jp/problem/furthest_pair) |

<!-- textlint-enable -->
<!-- gen:end verify-table -->
