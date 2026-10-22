# 工程10 2巡目：frequency の付け直し（tools/frequency.py）

§17-7 と catalog/README §5 に従い、`tools/frequency.py --write` で全ページの frequency・frequency_evidence を付け直した（2026-10-22）。

## 基準（スクリプトの冒頭にも書いた）

- **A**：recent（data/recent-abc.yaml の pages に出る問題の数。1問1回）が 2 以上、または多くのページの前提（prerequisites を逆にたどって届くページが 13 以上か、直接の前提が 5 以上）
- **B**：recent が 1、または古い ABC（台帳で contest が abc の問題のうち abc451〜480 を除き、status が 未確認 でないもの。例題・練習・力試しのどれでも数える。工程9の補充の問題も数える）が 3 問以上（§17-7）
- **C**：それ以外
- 「多くのページの前提」の閾値（届く 13 以上か直接 5 以上）は文書に書かれていなかったので、今の値に合う境目を採った（audit-facts ## shared の推定と同じ。届く 12・直接 2 の divisor-enum は B、届く 14・直接 6 の bit-full-search は A）。A の付き方は今回の付け直しで 1 ページも変わっていない
- 手の値：modint の A（「手で A にした」）だけをスクリプトの MANUAL に残した（計算した値が低いときだけ使う）。interval-scheduling・median-absolute の「古い ABC で繰り返し出た定番（手で B にした）」は §17-7 が定めた「古い ABC で繰り返し使われた」の基準そのものに当たるので、手の値を外して基準どおりにした（どちらも台帳の古い ABC が 3 問未満なので C）。B に戻すなら、台帳に古い ABC の問題を足すか、MANUAL に入れる（メインの判断）

## 結果

差分は 114 ページ（値が変わったのは 20：C→B 17、B→C 3）。`python3 tools/frequency.py --check` は差分 0。check_pages はエラー 0・警告 0。
台帳（data/problems.yaml）は同じ巡で別の担当も直している（abc116_c・abc130_e の pages からの削除、仮の summary の問題の status など）。古い ABC の数はこの付け直しの時点の台帳で数えたので、バッチの終わりに `python3 tools/frequency.py --check` を流し、差分があれば `--write` で付け直す。

## 値が変わったページ（20）

| ページ | 前 → 後 | 前の evidence | 後の evidence | 理由 |
| --- | --- | --- | --- | --- |
| basics/interval-scheduling.md | B → C | 古い ABC で繰り返し出た定番（最近30回の出現は0。手で B にした） | recent 0・前提として届くページなし・古い ABC 2 問 | 手で B にしていたが、台帳の古い ABC が 3 問未満（§17-7 の基準に合わない）（recent 0・古い ABC 2） |
| basics/median-absolute.md | B → C | 古い ABC で繰り返し出た定番（最近30回の出現は0。手で B にした） | recent 0・前提として届くページなし・古い ABC 1 問 | 手で B にしていたが、台帳の古い ABC が 3 問未満（§17-7 の基準に合わない）（recent 0・古い ABC 1） |
| comb/bell-number.md | C → B | recent 0・前提として届くページなし・古い ABC 2 問 | recent 0・前提として届くページなし・古い ABC 3 問 | 古い ABC が 3 問以上（§17-7）（古い ABC 2→3） |
| comb/expectation-of-square.md | C → B | recent 0・前提として届くページなし・古い ABC 2 問 | recent 0・前提として届くページなし・古い ABC 3 問 | 古い ABC が 3 問以上（§17-7）（古い ABC 2→3） |
| comb/expectation-tail-sum.md | C → B | recent 0・前提として 1 ページに届く（直接 1）・古い ABC 2 問 | recent 0・前提として 1 ページに届く（直接 1）・古い ABC 3 問 | 古い ABC が 3 問以上（§17-7）（古い ABC 2→3） |
| comb/game-retrograde-analysis.md | C → B | recent 0・前提として届くページなし・古い ABC 2 問 | recent 0・前提として届くページなし・古い ABC 3 問 | 古い ABC が 3 問以上（§17-7）（古い ABC 2→3） |
| comb/mobius-function.md | C → B | recent 0・前提として届くページなし・古い ABC 1 問 | recent 0・前提として届くページなし・古い ABC 4 問 | 古い ABC が 3 問以上（§17-7）（古い ABC 1→4） |
| comb/nim.md | C → B | recent 0・前提として 2 ページに届く（直接 1）・古い ABC 2 問 | recent 0・前提として 2 ページに届く（直接 1）・古い ABC 3 問 | 古い ABC が 3 問以上（§17-7）（古い ABC 2→3） |
| comb/zeta-mobius-subset.md | C → B | recent 0・前提として届くページなし・古い ABC 2 問 | recent 0・前提として届くページなし・古い ABC 4 問 | 古い ABC が 3 問以上（§17-7）（古い ABC 2→4） |
| dp/knapsack-undo.md | B → C | recent 0・前提として届くページなし・古い ABC 3 問 | recent 0・前提として届くページなし・古い ABC 2 問 | 古い ABC が 3 問未満になった（recent 0・前提でも A・B に届かない）（古い ABC 3→2） |
| ds/sparse-table.md | C → B | recent 0・前提として届くページなし・古い ABC 1 問 | recent 0・前提として届くページなし・古い ABC 3 問 | 古い ABC が 3 問以上（§17-7）（古い ABC 1→3） |
| graph/degree-sqrt.md | C → B | recent 0・前提として届くページなし・古い ABC 1 問 | recent 0・前提として届くページなし・古い ABC 3 問 | 古い ABC が 3 問以上（§17-7）（古い ABC 1→3） |
| graph/namori-graph.md | C → B | recent 0・前提として届くページなし・古い ABC 2 問 | recent 0・前提として届くページなし・古い ABC 3 問 | 古い ABC が 3 問以上（§17-7）（古い ABC 2→3） |
| math/crt.md | C → B | recent 0・前提として届くページなし・古い ABC 2 問 | recent 0・前提として届くページなし・古い ABC 3 問 | 古い ABC が 3 問以上（§17-7）（古い ABC 2→3） |
| math/euler-phi.md | C → B | recent 0・前提として 2 ページに届く（直接 2）・古い ABC 2 問 | recent 0・前提として 2 ページに届く（直接 2）・古い ABC 4 問 | 古い ABC が 3 問以上（§17-7）（古い ABC 2→4） |
| math/exponent-mod.md | C → B | recent 0・前提として 1 ページに届く（直接 1）・古い ABC 2 問 | recent 0・前提として 1 ページに届く（直接 1）・古い ABC 3 問 | 古い ABC が 3 問以上（§17-7）（古い ABC 2→3） |
| math/floor-quotient-enum.md | C → B | recent 0・前提として 1 ページに届く（直接 1）・古い ABC 2 問 | recent 0・前提として 1 ページに届く（直接 1）・古い ABC 5 問 | 古い ABC が 3 問以上（§17-7）（古い ABC 2→5） |
| math/spf-sieve.md | C → B | recent 0・前提として届くページなし・古い ABC 2 問 | recent 0・前提として届くページなし・古い ABC 5 問 | 古い ABC が 3 問以上（§17-7）（古い ABC 2→5） |
| string/hash-safety.md | C → B | recent 0・前提として届くページなし・古い ABC 2 問 | recent 0・前提として届くページなし・古い ABC 4 問 | 古い ABC が 3 問以上（§17-7）（古い ABC 2→4） |
| tree/centroid-decomposition.md | C → B | recent 0・前提として届くページなし・古い ABC 2 問 | recent 0・前提として届くページなし・古い ABC 3 問 | 古い ABC が 3 問以上（§17-7）（古い ABC 2→3） |

## 値は同じで evidence の数だけ変わったページ（94）

| ページ | 値 | 変わった数 |
| --- | --- | --- |
| basics/binary-search-answer.md | A | 古い ABC 8→7 |
| basics/binary-search.md | A | 古い ABC 5→6 |
| basics/bit-full-search.md | A | 古い ABC 10→8 |
| basics/brute-force.md | A | 古い ABC 5→4 |
| basics/coordinate-compression.md | B | 古い ABC 4→3 |
| basics/divide-and-conquer.md | A | 古い ABC 1→2 |
| basics/event-sort.md | A | recent 1→2 |
| basics/imos.md | A | recent 4→5・古い ABC 6→4 |
| basics/kth-value.md | B | 古い ABC 6→5 |
| basics/periodicity.md | B | 古い ABC 5→4 |
| basics/prefix-sum.md | A | 古い ABC 4→3 |
| basics/recursion-structure.md | B | recent 0→1 |
| basics/sorting-techniques.md | A | 届く 58/9→59/9 |
| comb/binomial-coefficient.md | A | recent 0→1・古い ABC 3→2 |
| comb/binomial-identities.md | B | 古い ABC 3→5 |
| comb/binomial-precompute.md | A | 古い ABC 6→3 |
| comb/counting-basics.md | A | 古い ABC 2→3 |
| comb/counting-fix-order.md | B | 古い ABC 3→5 |
| comb/counting-labeled-graphs.md | B | 古い ABC 3→5 |
| comb/counting-mindset.md | A | 古い ABC 7→6 |
| comb/expectation-linear-equations.md | B | 古い ABC 3→4 |
| comb/inclusion-exclusion.md | A | 古い ABC 7→6 |
| comb/optimal-strategy-expectation.md | B | 古い ABC 7→5 |
| comb/permutation-cycles.md | B | 古い ABC 5→4 |
| comb/probability-basics.md | A | 古い ABC 2→4 |
| comb/probability-dp.md | B | 古い ABC 5→6 |
| dp/alien-dp.md | B | 古い ABC 3→2 |
| dp/bit-dp.md | B | 古い ABC 13→9 |
| dp/digit-dp-advanced.md | B | 古い ABC 8→6 |
| dp/digit-dp.md | A | 古い ABC 6→5 |
| dp/dp-basics.md | A | 古い ABC 6→4 |
| dp/dp-dag.md | B | 古い ABC 6→3 |
| dp/dp-dimension-reduction.md | B | 古い ABC 7→6 |
| dp/dp-grid.md | B | 古い ABC 11→8 |
| dp/dp-mod-state.md | B | 古い ABC 6→5 |
| dp/dp-order.md | B | 古い ABC 6→5 |
| dp/dp-phase.md | B | 古い ABC 4→2 |
| dp/dp-prefix-sum.md | B | 古い ABC 11→7 |
| dp/dp-state-design.md | A | 古い ABC 10→9 |
| dp/inline-dp.md | B | 古い ABC 5→3 |
| dp/interval-dp-advanced.md | B | 古い ABC 7→4 |
| dp/interval-dp.md | B | 古い ABC 7→3 |
| dp/knapsack-01.md | A | 古い ABC 13→7 |
| dp/memoized-recursion.md | B | 古い ABC 6→5 |
| dp/monge.md | B | 古い ABC 4→2 |
| dp/rerooting.md | B | 古い ABC 4→3 |
| dp/subsequence-dp.md | B | 古い ABC 4→3 |
| dp/subset-sum.md | B | 古い ABC 7→5 |
| dp/tree-dp.md | B | 古い ABC 10→8 |
| ds/binary-trie.md | B | 古い ABC 3→4 |
| ds/merge-sort-tree.md | B | 古い ABC 1→5 |
| ds/monotonic-stack.md | B | 古い ABC 5→6 |
| ds/ordered-set.md | A | 古い ABC 8→7 |
| ds/persistent-data-structures.md | B | 古い ABC 1→4 |
| ds/stack-techniques.md | A | 古い ABC 5→8 |
| ds/union-find-applications.md | B | 古い ABC 9→11 |
| ds/union-find.md | A | 届く 17/9→18/9 |
| geometry/circle-geometry.md | B | 古い ABC 8→7 |
| geometry/convex-hull.md | B | 古い ABC 5→4 |
| graph/bellman-ford.md | B | 古い ABC 3→5 |
| graph/bfs.md | A | 古い ABC 6→5 |
| graph/bipartite-graph.md | A | 古い ABC 3→2 |
| graph/connected-components.md | B | 古い ABC 4→5 |
| graph/dijkstra.md | A | 古い ABC 8→6 |
| graph/extended-dijkstra.md | A | 古い ABC 9→10 |
| graph/graph-basics.md | A | 古い ABC 1→3 |
| graph/min-cost-flow.md | B | 古い ABC 5→4 |
| graph/minimum-spanning-tree.md | A | 届く 3/3→4/4 |
| graph/scc.md | B | 古い ABC 3→2 |
| graph/time-dependent-dijkstra.md | B | 古い ABC 3→5 |
| graph/union-find-connectivity.md | B | 古い ABC 5→6 |
| math/ext-gcd.md | B | 古い ABC 2→4 |
| math/harmonic-sum.md | A | 古い ABC 7→6 |
| math/lagrange-interpolation.md | C | 古い ABC 2→1 |
| math/mod-arithmetic.md | A | 古い ABC 2→3 |
| math/multiplicative-function.md | C | 古い ABC 1→0 |
| misc/parsing.md | B | 古い ABC 3→4 |
| string/kmp.md | B | 古い ABC 6→5 |
| thinking/complement.md | B | 古い ABC 5→4 |
| thinking/construction.md | A | 古い ABC 5→4 |
| thinking/contribution.md | A | 古い ABC 6→5 |
| thinking/parity.md | A | 古い ABC 2→1 |
| thinking/reformulation.md | A | 古い ABC 4→3 |
| thinking/reverse-thinking.md | A | 古い ABC 3→2 |
| thinking/symmetry-pigeonhole-casework.md | A | 古い ABC 6→3 |
| tree/complete-binary-tree.md | B | 古い ABC 2→3 |
| tree/hld.md | B | 古い ABC 2→1 |
| tree/lca.md | A | 古い ABC 5→4 |
| tree/leaf-first.md | B | 古い ABC 2→5 |
| tree/root-path-dfs.md | B | 古い ABC 5→6 |
| tree/steiner-subtree.md | C | 古い ABC 1→2 |
| tree/tree-edge-contribution.md | B | 古い ABC 4→3 |
| tree/tree-imos.md | B | 古い ABC 3→4 |
| tree/tree-isomorphism.md | C | 古い ABC 1→0 |

## 1巡目の残りとの対応

- left-shared 1（audit-facts ## shared の 1〜3 項目）：済み。recent の数え漏れ（event-sort 1→2・imos 4→5・recursion-structure 0→1・binomial-coefficient 0→1）、届くページの数（sorting-techniques・union-find・minimum-spanning-tree など）、古い ABC の数をすべて今のデータで書き直した
- left-ds（union-find の「17 ページ」）・left-graph（minimum-spanning-tree の「3（直接 3）」）：済み（上の表）
