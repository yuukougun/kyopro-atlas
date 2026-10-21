# バッチ b1（基礎・水 173ページ）の状態

**2026-10-21 完了**：173ページすべてが「執筆 → 検証 → 直し」を終え、stage は draft。再開では、止めたときに残っていた直し101・検証と直し38・すべて17ページを、それぞれの続きから流した（2本のワークフロー、同時20）。

残り：各 `<id>.md` にある共有ファイル（台帳・用語集・手引き）への提案の反映。

---

以下は途中で止めたとき（同日）の記録。

2026-10-21、Claude の利用上限が近いので途中で止めた。各ページは「執筆 → 検証（別の担当。指摘は `verify/<id>.md`）→ 直し（指摘を読んで直し、採らなかったものは `<id>.md` の末尾に理由）」の順に進める。再開では、下の段階の続きから同じ流れで行う。

- 並列の制作を2本のワークフローで動かしたが、4本の並びの方に渡したページの一覧が計画と食い違っていた（メインが一覧を手で打ち直したため）。存在しない id を渡された執筆者は書かずに報告だけを残し、正しい id に読み替えたもの（crt・reformulation・symmetry-pigeonhole-casework）は記録をその id に付け替えた。青・黄のページ6枚（下の「b1 の外」）は先に仕上がった。**一覧は必ずファイルから機械的に渡す**
- 執筆の途中で止まった tree-basics は骨格に戻した。直しの途中で止まった lca は「直しが未着手」に入れた（直しを最初からやり直す）
- 共有ファイル（台帳・用語集・手引き）への提案は各 `<id>.md` にあり、まだ反映していない

| 段階 | ページ数 |
| --- | --- |
| 仕上がり（直しまで済み） | 24 |
| 検証まで済み・直しが未着手 | 101 |
| 執筆まで済み・検証が未着手（公開中だが未検証） | 38 |
| 未着手（骨格のまま） | 17 |

## 直しが未着手

- basics/binary-search（基礎）
- basics/bit-full-search（基礎）
- basics/bit-operations（基礎）
- basics/bitwise-independence（水）
- basics/brute-force（基礎）
- basics/coordinate-compression（基礎）
- basics/doubling（水）
- basics/event-sort（水）
- basics/fractional-binary-search（水）
- basics/greedy-basics（基礎）
- basics/greedy-priority-queue（水）
- basics/imos（基礎）
- basics/interval-scheduling（基礎）
- basics/lexicographic-greedy（基礎）
- basics/median-absolute（基礎）
- basics/meet-in-the-middle（水）
- basics/periodicity（基礎）
- basics/prefix-sum-2d（水）
- basics/prefix-sum-counting（基礎）
- basics/prefix-sum（基礎）
- basics/recursion-structure（基礎）
- basics/recursive-enumeration（水）
- basics/run-length-encoding（基礎）
- basics/sorting-techniques（基礎）
- basics/ternary-search（水）
- basics/two-pointers（基礎）
- comb/binomial-coefficient（基礎）
- comb/binomial-precompute（基礎）
- comb/counting-basics（基礎）
- comb/counting-fix-order（水）
- comb/counting-mindset（水）
- comb/coupon-collector（基礎）
- comb/expected-value-dp（水）
- comb/game-basics（水）
- comb/lattice-paths（基礎）
- comb/minimax（水）
- comb/multinomial-coefficient（水）
- comb/nim（水）
- comb/permutation-cycles（基礎）
- comb/probability-basics（基礎）
- comb/probability-dp（水）
- comb/probability-symmetry（水）
- comb/rational-mod（水）
- comb/stars-and-bars（基礎）
- cpp/acl-reading（基礎）
- cpp/cpp-algorithms（基礎）
- cpp/cpp-comparators（基礎）
- cpp/cpp-container-idioms（基礎）
- cpp/cpp-initialization（基礎）
- cpp/cpp-integer-overflow（基礎）
- cpp/cpp-io（基礎）
- cpp/cpp-lambda（基礎）
- cpp/cpp-macros-template-file（基礎）
- cpp/cpp-math-functions（基礎）
- cpp/cpp-range-for（基礎）
- cpp/cpp-string-api（基礎）
- cpp/cpp-structured-bindings（基礎）
- cpp/cpp-templates-constexpr（基礎）
- cpp/cpp-types-literals（基礎）
- cpp/cpp-undefined-behavior（基礎）
- cpp/cpp-views-cpp23（基礎）
- dp/digit-dp（水）
- dp/dp-basics（基礎）
- dp/dp-dag（基礎）
- dp/dp-grid（水）
- dp/dp-mod-state（水）
- dp/dp-order（水）
- dp/dp-prefix-sum（水）
- dp/dp-reconstruction（水）
- dp/dp-sequence-partition（水）
- dp/dp-state-design（水）
- dp/knapsack-01（基礎）
- dp/lcs（水）
- dp/lis（水）
- dp/memoized-recursion（基礎）
- dp/subset-sum（基礎）
- dp/tree-dp（水）
- ds/fenwick-tree（水）
- ds/global-offset（基礎）
- ds/interval-set（水）
- ds/inversion-number（水）
- ds/kth-element（水）
- ds/linked-list（基礎）
- ds/monotonic-stack（水）
- ds/offline-queries（水）
- ds/ordered-set（基礎）
- ds/priority-queue（水）
- ds/segment-tree-binary-search（水）
- ds/segment-tree-on-values（水）
- ds/segment-tree（水）
- ds/stack-techniques（基礎）
- ds/stl-containers（基礎）
- ds/top-k-multiset（水）
- ds/union-find-applications（水）
- ds/union-find（基礎）
- ds/weighted-union-find（水）
- geometry/geometry-precision（水）
- geometry/geometry-vectors（基礎）
- geometry/rotation-transform（水）
- graph/graph-basics（基礎）
- tree/lca（青）

## 検証が未着手

- geometry/argument-sort（水）
- geometry/manhattan-chebyshev（水）
- graph/bfs（基礎）
- graph/bipartite-graph（基礎）
- graph/connected-components（基礎）
- graph/cycle-detection（基礎）
- graph/dfs（基礎）
- graph/dijkstra（基礎）
- graph/functional-graph（水）
- graph/grid-graph（基礎）
- graph/minimum-spanning-tree（水）
- graph/namori-graph（水）
- graph/scc（水）
- graph/shortest-path-dag（水）
- graph/small-graph-brute-force（基礎）
- graph/time-dependent-dijkstra（水）
- graph/topological-sort（基礎）
- graph/union-find-connectivity（水）
- graph/warshall-floyd（水）
- graph/zero-one-bfs（水）
- math/digit-and-mod（水）
- math/divisor-count-bound（水）
- math/divisor-enum（基礎）
- math/exponent-mod（水）
- math/gcd-lcm（基礎）
- math/geometric-series-mod（基礎）
- math/harmonic-sum（水）
- math/integer-division（基礎）
- math/mod-arithmetic（基礎）
- math/mod-inverse（基礎）
- math/mod-pow（基礎）
- math/modint（基礎）
- math/prime-exponent-vector（基礎）
- math/prime-factorization（基礎）
- math/segmented-sieve（水）
- math/sieve-eratosthenes（基礎）
- math/sigma-manipulation（基礎）
- math/spf-sieve（基礎）

## 未着手

- math/integer-root（基礎）
- math/proof-patterns（基礎）
- misc/interactive（基礎）
- string/hashing-for-sets（水）
- string/subsequence-matching（基礎）
- thinking/fix-variable（基礎）
- thinking/reverse-thinking（基礎）
- tree/complete-binary-tree（基礎）
- tree/leaf-first（水）
- tree/small-to-large（水）
- tree/steiner-subtree（基礎）
- tree/tree-basics（基礎）
- tree/tree-bipartite（基礎）
- tree/tree-construction（水）
- tree/tree-distance（基礎）
- tree/tree-edge-contribution（水）
- tree/tree-imos（基礎）

## 仕上がり（b1 の外の青・黄を含む）

- basics/complexity-estimation（基礎）
- dp/rerooting（青）
- math/base-conversion（基礎）
- math/crt（青）
- math/ext-gcd（水）
- math/floor-quotient-enum（水）
- math/matrix-power（青）
- string/kmp（青）
- string/palindrome（水）
- string/rolling-hash（水）
- string/string-basics（基礎）
- string/suffix-array（黄）
- string/trie（水）
- string/z-algorithm（水）
- thinking/complement（基礎）
- thinking/construction（基礎）
- thinking/contribution（水）
- thinking/invariant（基礎）
- thinking/parity（基礎）
- thinking/reformulation（水）
- thinking/symmetry-pigeonhole-casework（基礎）
- tree/euler-tour（青）
- tree/tree-diameter（水）
- tree/tree-traversal（基礎）
