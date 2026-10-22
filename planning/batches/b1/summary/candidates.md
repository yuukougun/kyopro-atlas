# 問題の補充の候補：バッチ b1

出どころ：各ページの報告の「問題の補充の候補」（見出しの言い回しの違いを含む）と、「検証の指摘への対応」の節で候補に触れた行（（対応の節）と記す）。「なし」だけの報告は除いた。台帳の状態は data/problems.yaml を引いた結果（今の pages の役割）。

## 1. 問題 ID ごとの索引

台帳にない問題 123 問、台帳にある問題 231 問。2 ページ以上が挙げた問題は太字。

### 1.1 台帳にない問題（新しく足す候補）

| 問題 ID | 挙げたページ |
| --- | --- |
| abc018_4 | meet-in-the-middle |
| abc034_c | lattice-paths |
| abc035_c | imos |
| **abc037_d** | dp-dag・memoized-recursion |
| abc038_d | lis |
| abc040_c | dp-basics |
| abc051_b | brute-force |
| abc054_c | small-graph-brute-force |
| abc054_d | knapsack-01 |
| abc089_c | brute-force |
| abc104_c | bit-full-search |
| **abc138_d** | dfs・tree-imos |
| abc148_c | gcd-lcm |
| abc163_f | tree-edge-contribution |
| abc170_f | time-dependent-dijkstra |
| abc175_f | palindrome |
| abc209_c | counting-fix-order |
| abc214_h | scc |
| abc215_d | spf-sieve |
| abc220_b | base-conversion |
| abc222_d | dp-prefix-sum |
| abc223_g | rerooting |
| abc225_d | linked-list |
| abc225_f | lexicographic-greedy |
| **abc232_d** | dp-dag・dp-order |
| abc233_f | permutation-cycles |
| abc236_g | matrix-power |
| abc238_d | bitwise-independence |
| abc242_c | dp-basics |
| abc244_e | dp-mod-state |
| abc245_c | dp-basics |
| abc248_c | dp-basics |
| abc249_f | greedy-priority-queue |
| abc250_g | greedy-priority-queue |
| abc260_d | ordered-set |
| abc264_h | complete-binary-tree |
| abc266_b | mod-arithmetic |
| abc276_b | graph-basics |
| abc280_h | suffix-array |
| abc283_d | stack-techniques |
| abc286_e | warshall-floyd |
| abc289_d | knapsack-01 |
| abc291_e | topological-sort |
| abc300_f | periodicity |
| abc302_e | ordered-set |
| abc310_f | probability-dp |
| abc319_e | time-dependent-dijkstra |
| abc326_f | meet-in-the-middle |
| abc329_c | run-length-encoding |
| abc331_e | priority-queue |
| abc334_f | monotonic-stack |
| **abc336_f** | meet-in-the-middle・rotation-transform |
| abc340_f | ext-gcd |
| abc343_b | graph-basics |
| abc345_b | integer-division |
| abc347_d | bitwise-independence |
| abc350_d | union-find |
| abc353_d | digit-and-mod |
| **abc363_d** | dp-reconstruction・palindrome |
| abc364_d | kth-element |
| **abc369_e** | dijkstra・warshall-floyd |
| abc370_e | dp-sequence-partition |
| abc375_c | rotation-transform |
| abc379_f | monotonic-stack |
| abc380_d | recursion-structure |
| abc384_e | priority-queue |
| abc386_f | lcs |
| abc389_c | global-offset |
| abc400_d | zero-one-bfs |
| abc404_b | rotation-transform |
| abc407_f | monotonic-stack |
| abc408_c | imos |
| abc414_c | base-conversion |
| abc414_e | floor-quotient-enum |
| abc414_f | tree-distance |
| abc416_e | warshall-floyd |
| **abc420_g** | divisor-enum・integer-root |
| abc428_c | stack-techniques |
| abc437_g | tree-bipartite |
| abc444_e | ordered-set |
| abc456_g | stars-and-bars |
| abc459_g | ext-gcd |
| abc462_f | dp-state-design |
| abc463_f | probability-basics |
| abc464_d | dp-state-design |
| abc467_e | event-sort |
| abc468_f | lis |
| abc469_g | matrix-power |
| abc474_d | construction |
| **abc474_e** | brute-force・sorting-techniques |
| abc476_d | brute-force |
| abc480_e | brute-force |
| agc001_c | tree-diameter |
| agc023_a | prefix-sum-counting |
| agc033_c | game-basics |
| agc039_a | run-length-encoding |
| arc017_3 | meet-in-the-middle |
| arc060_c | doubling |
| arc073_b | knapsack-01 |
| arc087_c | trie |
| arc091_d | nim |
| arc092_b | bitwise-independence |
| arc096_a | brute-force |
| arc103_b | manhattan-chebyshev |
| arc150_c | time-dependent-dijkstra |
| arc164_a | base-conversion |
| code_festival_2017_qualc_c | palindrome |
| jsc2019_qual_e | namori-graph |
| keyence2020_b | interval-scheduling |
| math_and_algorithm_aq | mod-pow |
| math_and_algorithm_w | probability-basics |
| nikkei2019_final_c | median-absolute |
| panasonic2020_c | integer-root |
| past202209_c | probability-basics |
| tdpc_number | digit-dp |
| tdpc_tournament | probability-dp |
| tenka1_2017_f | exponent-mod |
| tessoku_book_af | game-basics |
| typical90_aj | manhattan-chebyshev |
| typical90_bx | prefix-sum |
| typical90_p | brute-force |
| typical90_q | inversion-number |
| typical90_t | integer-division |

### 1.2 台帳にある問題（役割を足す・移す候補、または参照として挙がったもの）

| 問題 ID | 挙げたページ | 台帳の今の pages | status |
| --- | --- | --- | --- |
| abc019_4 | interactive | tree-diameter:practice | 確認済み |
| abc073_d | small-graph-brute-force | warshall-floyd:practice | 確認済み |
| abc105_d | reformulation | prefix-sum-counting:practice・reformulation:example | 確認済み |
| **abc106_d** | offline-queries・prefix-sum-2d | event-sort:practice・sweep-line-2d:practice | 確認済み |
| abc118_c | gcd-lcm | proof-patterns:example | 確認済み |
| abc124_d | two-pointers | run-length-encoding:example | 確認済み |
| abc125_d | parity | invariant:example | 確認済み |
| abc126_c | probability-basics | probability-basics:example | 確認済み |
| abc127_e | manhattan-chebyshev | counting-mindset:example | 確認済み |
| abc129_c | dp-basics | dp-basics:practice | 確認済み |
| abc129_e | reformulation | bitwise-independence:practice・digit-dp:practice | 確認済み |
| abc129_f | matrix-power | geometric-series-mod:challenge | 確認済み |
| abc130_e | dp-prefix-sum | lcs:practice・counting-dedup:practice | 確認済み |
| abc131_f | union-find-applications | graph-modeling:practice・connected-components:challenge | 確認済み |
| **abc132_d** | binomial-precompute・stars-and-bars | binomial-precompute:practice | 確認済み |
| abc133_c | symmetry-pigeonhole-casework | proof-patterns:example | 確認済み |
| **abc136_d** | doubling・parity | run-length-encoding:practice | 確認済み |
| abc137_d | reverse-thinking | greedy-priority-queue:example | 確認済み |
| abc140_e | linked-list | contribution:challenge・ordered-set:challenge | 確認済み |
| abc141_d | greedy-basics | greedy-priority-queue:practice | 確認済み |
| **abc145_d** | binomial-coefficient・binomial-precompute | lattice-paths:example・counting-bijection:practice | 確認済み |
| abc146_d | construction | tree-traversal:practice | 確認済み |
| abc147_d | contribution | bitwise-independence:example | 確認済み |
| abc150_c | bit-full-search | permutation:practice | 確認済み |
| abc150_f | kmp | rolling-hash:challenge・kmp:example | 確認済み |
| abc151_d | grid-graph | bfs:practice | 確認済み |
| **abc156_d** | binomial-coefficient・binomial-precompute・complement | binomial-precompute:practice | 確認済み |
| abc159_e | bit-full-search | bit-full-search:challenge | 確認済み |
| abc164_d | digit-and-mod | prefix-sum-counting:practice・digit-and-mod:example | 確認済み |
| abc171_e | bit-operations | xor:example | 確認済み |
| abc172_c | two-pointers | prefix-sum:practice | 確認済み |
| abc172_d | contribution | sigma-manipulation:example | 確認済み |
| abc177_c | sigma-manipulation | symmetry-pigeonhole-casework:example | 確認済み |
| abc177_e | harmonic-sum | spf-sieve:example | 確認済み |
| abc178_c | counting-basics | complement:example | 確認済み |
| **abc179_e** | functional-graph・symmetry-pigeonhole-casework | periodicity:example | 確認済み |
| abc180_c | divisor-enum | divisors-and-multiples:practice | 確認済み |
| abc181_c | geometry-precision | geometry-vectors:example | 確認済み |
| abc183_e | dp-prefix-sum | dp-grid:practice | 確認済み |
| abc184_d | memoized-recursion | expected-value-dp:example | 確認済み |
| abc186_d | sigma-manipulation | contribution:example | 確認済み |
| **abc186_e** | crt・mod-inverse | mod-inverse:practice・ext-gcd:example | 確認済み |
| abc187_e | euler-tour | tree-imos:example | 確認済み |
| abc188_d | imos | event-sort:practice | 確認済み |
| abc188_e | dp-order | dp-order:example | 確認済み |
| abc189_f | expected-value-dp | expectation-linear-equations:practice | 確認済み |
| abc192_e | time-dependent-dijkstra | time-dependent-dijkstra:example | 確認済み |
| abc193_d | probability-basics | probability-basics:practice | 確認済み |
| abc193_f | grid-graph | project-selection:practice | 確認済み |
| abc197_c | bit-full-search | xor:practice | 確認済み |
| abc197_e | dp-order | dp-order:example | 確認済み |
| abc199_d | connected-components | small-graph-brute-force:challenge | 確認済み |
| **abc201_d** | dp-grid・memoized-recursion | minimax:example | 確認済み |
| abc201_e | tree-edge-contribution | tree-distance:practice | 確認済み |
| abc203_d | prefix-sum-2d | fractional-binary-search:example | 確認済み |
| abc206_e | harmonic-sum | divisor-inclusion-exclusion:example | 確認済み |
| abc211_d | bfs | dp-dag:practice・shortest-path-dag:example | 確認済み |
| **abc212_g** | divisor-count-bound・exponent-mod | euler-phi:example・multiplicative-order:practice | 確認済み |
| abc214_e | greedy-priority-queue | priority-queue:practice | 確認済み |
| abc216_e | greedy-priority-queue | greedy-basics:practice | 確認済み |
| abc218_g | top-k-multiset | root-path-dfs:challenge・minimax:challenge | 確認済み |
| abc220_f | tree-edge-contribution | tree-dp:example | 確認済み |
| abc221_d | coordinate-compression | imos:practice | 確認済み |
| abc221_g | subset-sum | bitset-speedup:challenge | 確認済み |
| abc222_e | tree-imos | subset-sum:practice・tree-imos:practice | 確認済み |
| abc222_g | exponent-mod | exponent-mod:practice・euler-phi:practice・multiplicative-order:example | 確認済み |
| abc223_f | segment-tree | segment-tree-monoids:example | 確認済み |
| abc224_c | geometry-precision | geometry-vectors:practice | 確認済み |
| abc227_g | segmented-sieve | segmented-sieve:practice | 確認済み |
| abc230_e | sigma-manipulation | sigma-manipulation:practice・floor-quotient-enum:example | 確認済み |
| abc231_f | coordinate-compression | fenwick-tree:practice | 確認済み |
| **abc233_d** | prefix-sum-counting・stl-containers | prefix-sum-counting:example | 確認済み |
| abc234_d | stl-containers | priority-queue:example | 確認済み |
| abc235_e | namori-graph | minimum-spanning-tree:example・lca:practice・offline-queries:practice | 確認済み |
| abc237_d | stack-techniques | linked-list:practice | 確認済み |
| abc239_b | integer-division | integer-division:example | 確認済み |
| abc241_e | periodicity | doubling:example | 確認済み |
| abc244_c | game-basics | interactive:practice | 確認済み |
| abc245_f | scc | topological-sort:practice | 確認済み |
| abc248_e | gcd-lcm | geometry-precision:practice | 確認済み |
| abc253_c | priority-queue | stl-containers:example | 確認済み |
| abc258_g | complexity-estimation | bitset-speedup:example | 確認済み |
| abc265_d | prefix-sum | interval:practice | 確認済み |
| abc266_g | multinomial-coefficient | multinomial-coefficient:practice | 確認済み |
| abc267_f | tree-diameter | lca:example | 確認済み |
| abc275_b | mod-arithmetic | mod-arithmetic:example | 確認済み |
| **abc281_g** | modint・tree-diameter | modint:practice・binomial-precompute:challenge・counting-labeled-graphs:example | 確認済み |
| abc282_f | construction | sparse-table:example・interactive:challenge | 確認済み |
| **abc284_c** | connected-components・graph-basics | graph-basics:practice | 確認済み |
| abc285_f | fenwick-tree | segment-tree:practice | 確認済み |
| abc287_g | offline-queries | segment-tree-on-values:challenge | 確認済み |
| abc290_f | tree-diameter | binomial-identities:challenge・cayley-pruefer:example | 確認済み |
| abc292_d | namori-graph | connected-components:practice・namori-graph:practice・union-find:practice | 確認済み |
| abc293_e | matrix-power | geometric-series-mod:practice | 確認済み |
| abc296_g | argument-sort | geometry-precision:challenge・convex-hull:example | 確認済み |
| abc298_h | rerooting | tree-path:challenge | 確認済み |
| abc299_d | binary-search | interactive:example | 確認済み |
| abc300_e | divisor-count-bound | memoized-recursion:practice・rational-mod:practice・expected-value-dp:practice | 確認済み |
| abc305_g | kmp | matrix-power:example・string-automaton-dp:practice | 確認済み |
| abc307_e | counting-basics | dp-state-design:practice・counting-basics:practice | 確認済み |
| abc309_e | tree-imos | tree-traversal:practice | 確認済み |
| abc309_f | segment-tree | segment-tree-monoids:practice | 確認済み |
| **abc311_c** | cycle-detection・functional-graph | cycle-detection:practice | 確認済み |
| abc314_e | coupon-collector | expected-value-dp:practice・optimal-strategy-expectation:practice | 確認済み |
| abc323_e | rational-mod | rational-mod:example・probability-dp:practice | 確認済み |
| abc324_e | reformulation | reformulation:example・subsequence-matching:practice | 確認済み |
| abc324_f | fractional-binary-search | fractional-binary-search:example | 確認済み |
| abc325_d | interval-scheduling | greedy-priority-queue:example | 確認済み |
| **abc326_e** | expected-value-dp・rational-mod | rational-mod:practice | 確認済み |
| abc328_e | minimum-spanning-tree | small-graph-brute-force:practice | 確認済み |
| abc328_f | weighted-union-find | weighted-union-find:example | 確認済み |
| abc329_f | small-to-large | small-to-large:example | 確認済み |
| abc330_e | segment-tree-binary-search | ordered-set:practice・interval-set:practice・segment-tree-binary-search:practice | 確認済み |
| abc330_f | reformulation | median-absolute:practice・manhattan-chebyshev:practice | 確認済み |
| abc331_d | periodicity | prefix-sum-2d:example | 確認済み |
| abc333_d | leaf-first | tree-traversal:practice | 確認済み |
| **abc335_e** | dp-dag・scc | dp-dag:practice | 確認済み |
| abc335_g | divisor-count-bound | multiplicative-order:challenge | 確認済み |
| abc337_e | interactive | interactive:practice | 確認済み |
| abc337_g | rerooting | euler-tour:challenge | 確認済み |
| abc338_f | warshall-floyd | bit-dp:practice・warshall-floyd:challenge | 確認済み |
| abc339_e | segment-tree-on-values | dp-segment-tree:practice・segment-tree-on-values:example | 確認済み |
| abc341_f | dp-order | dp-order:practice | 確認済み |
| abc344_f | dp-grid | dp-grid:practice | 確認済み |
| abc345_d | recursive-enumeration | recursive-enumeration:practice | 確認済み |
| **abc348_e** | rerooting・tree-dp | tree-dp:practice | 確認済み |
| abc348_f | complexity-estimation | bitset-speedup:example | 確認済み |
| abc349_e | minimax | minimax:practice | 確認済み |
| **abc350_e** | coupon-collector・expected-value-dp | expected-value-dp:practice | 確認済み |
| abc351_d | grid-graph | grid-graph:practice | 確認済み |
| **abc351_f** | fenwick-tree・sigma-manipulation | contribution:practice・fenwick-tree:example | 確認済み |
| abc353_e | trie | trie:example | 確認済み |
| abc354_e | game-basics | game-basics:example | 確認済み |
| abc355_e | interactive | interactive:challenge | 確認済み |
| abc355_f | union-find-applications | minimum-spanning-tree:challenge・union-find-applications:challenge | 確認済み |
| **abc357_d** | mod-inverse・modint | mod-inverse:practice・modint:practice・geometric-series-mod:example | 確認済み |
| abc359_f | ternary-search | ternary-search:practice・tree-degree:example | 確認済み |
| abc361_b | geometry-vectors | geometry-vectors:practice | 確認済み |
| abc362_g | suffix-array | aho-corasick:example・suffix-array:practice | 確認済み |
| abc364_f | union-find-applications | minimum-spanning-tree:challenge・union-find-applications:challenge | 確認済み |
| abc368_d | steiner-subtree | steiner-subtree:example | 確認済み |
| abc369_c | run-length-encoding | imos:practice | 確認済み |
| **abc369_f** | dp-grid・dp-reconstruction・lis | dp-reconstruction:practice・dp-grid:practice | 確認済み |
| abc369_g | tree-dp | tree-diameter:challenge | 確認済み |
| abc371_f | segment-tree-binary-search | lazy-segment-tree-patterns:practice | 確認済み |
| abc371_g | crt | permutation-cycles:challenge | 確認済み |
| abc372_e | union-find-applications | union-find-applications:example | 確認済み |
| abc374_g | scc | dilworth-path-cover:practice | 確認済み |
| **abc375_f** | shortest-path-dag・warshall-floyd | warshall-floyd:example | 確認済み |
| abc376_e | fix-variable | greedy-priority-queue:practice | 確認済み |
| abc377_g | lcs | trie:practice | 確認済み |
| abc378_e | inversion-number | inversion-number:practice | 確認済み |
| abc378_f | namori-graph | tree-basics:practice | 確認済み |
| **abc380_e** | interval-set・union-find-applications | interval-set:example | 確認済み |
| abc380_f | game-basics | memoized-recursion:challenge・game-basics:practice | 確認済み |
| **abc382_e** | expected-value-dp・probability-dp | expected-value-dp:practice | 確認済み |
| abc390_d | recursive-enumeration | recursive-enumeration:challenge・bell-number:example | 確認済み |
| abc393_e | harmonic-sum | harmonic-sum:example・zeta-mobius-divisor:practice | 確認済み |
| abc396_f | inversion-number | inversion-number:practice | 確認済み |
| abc398_e | game-basics | tree-bipartite:challenge・game-basics:example | 確認済み |
| abc400_c | integer-root | integer-root:example | 確認済み |
| abc403_e | trie | trie:practice | 確認済み |
| abc403_g | segment-tree-on-values | segment-tree-on-values:challenge・sqrt-decomposition:practice | 確認済み |
| abc407_g | grid-graph | min-cost-flow:practice | 確認済み |
| abc409_f | union-find-applications | union-find-applications:practice | 確認済み |
| abc413_g | union-find-connectivity | grid-graph:challenge | 確認済み |
| abc415_e | dp-grid | binary-search-answer:practice | 確認済み |
| abc419_f | kmp | aho-corasick:practice・string-automaton-dp:example | 確認済み |
| abc420_e | union-find-applications | union-find-applications:practice | 確認済み |
| abc430_e | z-algorithm | rolling-hash:practice・z-algorithm:example・kmp:practice | 確認済み |
| abc432_c | integer-division | integer-division:practice | 確認済み |
| abc435_e | interval-set | interval-set:example | 確認済み |
| abc437_e | trie | trie:practice | 確認済み |
| abc442_e | argument-sort | argument-sort:example | 確認済み |
| abc442_f | dp-prefix-sum | dp-prefix-sum:practice | 確認済み |
| abc447_f | tree-dp | tree-dp:example・tree-diameter:practice | 確認済み |
| abc451_e | union-find | tree-construction:example | 確認済み |
| abc451_f | weighted-union-find | bipartite-graph:practice・weighted-union-find:practice | 確認済み |
| abc452_f | two-pointers | inversion-number:example | 確認済み |
| **abc453_e** | binomial-precompute・fix-variable | fix-variable:challenge | 確認済み |
| abc455_e | prefix-sum-counting | complement:practice | 確認済み |
| abc456_d | dp-state-design | subsequence-and-substring:practice | 確認済み |
| abc457_e | sorting-techniques | interval:practice | 確認済み |
| **abc458_e** | binomial-precompute・fix-variable | fix-variable:practice | 確認済み |
| abc458_f | kmp | matrix-power:practice・aho-corasick:practice・string-automaton-dp:example | 確認済み |
| abc460_d | parity | bfs:challenge | 確認済み |
| **abc460_e** | digit-and-mod・gcd-lcm・reformulation | reformulation:practice・digit-and-mod:practice・counting-mindset:practice | 確認済み |
| abc460_f | lca | tree-diameter:practice・segment-tree-monoids:challenge | 確認済み |
| abc461_d | two-pointers | prefix-sum-2d:practice | 確認済み |
| abc461_e | segment-tree | segment-tree:practice | 確認済み |
| abc464_f | meet-in-the-middle | meet-in-the-middle:challenge・probability-symmetry:challenge | 確認済み |
| abc466_e | reformulation | imos:practice・difference-sequence:practice・dp-phase:practice | 確認済み |
| abc468_e | mod-inverse | contribution:practice | 確認済み |
| abc469_e | fractional-binary-search | fractional-binary-search:example | 確認済み |
| abc469_f | harmonic-sum | minimum-spanning-tree:practice・harmonic-sum:practice | 確認済み |
| abc470_f | multinomial-coefficient | multinomial-coefficient:practice・permutation-parity:example | 確認済み |
| abc470_g | two-pointers | lazy-segment-tree-patterns:challenge | 確認済み |
| abc471_e | sigma-manipulation | symmetry-pigeonhole-casework:practice・sigma-manipulation:practice | 確認済み |
| abc472_d | bfs | grid:practice | 確認済み |
| abc473_d | recursive-enumeration | recursive-enumeration:practice | 確認済み |
| **abc473_e** | greedy-basics・prefix-sum-counting | prefix-sum-counting:practice | 確認済み |
| abc475_d | recursive-enumeration | sieve-eratosthenes:practice | 確認済み |
| abc475_f | prefix-sum-2d | inclusion-exclusion:practice | 確認済み |
| abc476_e | segment-tree | segment-tree:practice | 確認済み |
| **abc478_d** | event-sort・interval-set | event-sort:practice | 確認済み |
| abc479_e | tree-edge-contribution | tree-edge-contribution:practice | 確認済み |
| agc014_d | leaf-first | game-basics:challenge | 確認済み |
| agc031_b | dp-sequence-partition | dp-sequence-partition:example | 確認済み |
| arc060_d | kmp | kmp:challenge | 確認済み |
| arc081_c | lexicographic-greedy | dp-reconstruction:challenge・subsequence-dp:practice・subsequence-matching:challenge | 確認済み |
| arc083_b | warshall-floyd | graph-construction:example | 確認済み |
| arc084_a | fix-variable | binary-search:practice | 確認済み |
| arc098_b | bit-operations | two-pointers:challenge | 確認済み |
| arc101_b | inversion-number | fractional-binary-search:challenge | 確認済み |
| arc105_d | nim | game-basics:practice | 確認済み |
| **arc143_c** | game-basics・nim | nim:practice | 確認済み |
| arc167_b | divisor-count-bound | divisor-count-bound:example | 確認済み |
| dp_g | topological-sort | memoized-recursion:practice・dp-dag:example | 確認済み |
| dp_k | game-basics | game-basics:example | 確認済み |
| math_and_algorithm_as | mod-inverse | mod-inverse:practice・geometric-series-mod:practice | 確認済み |
| tdpc_lexicographical | dp-reconstruction | subsequence-dp:challenge | 確認済み |
| tdpc_target | lis | lis:challenge・inline-dp:practice | 確認済み |
| **typical90_ai** | lca・steiner-subtree | auxiliary-tree:example | 確認済み |
| typical90_al | gcd-lcm | integer-division:practice | 確認済み |
| typical90_bp | offline-queries | weighted-union-find:practice | 確認済み |
| **typical90_bt** | dfs・recursive-enumeration | complexity-estimation:practice・dfs:practice | 確認済み |
| typical90_bw | prime-factorization | divisors-and-multiples:practice | 確認済み |
| typical90_cd | mod-inverse | mod-inverse:example | 確認済み |
| **typical90_cg** | divisor-count-bound・divisor-enum | divisor-count-bound:practice | 確認済み |
| typical90_ck | inversion-number | dp-sequence-partition:practice | 確認済み |
| typical90_e | dp-mod-state | matrix-power:challenge | 確認済み |

## 2. ページごとの候補（報告の文のまま）

### argument-sort

- catalog の数（例題 2・練習 2・力試し 2）で足りている。水のページなので abc319 以降の水の問題が例題か練習にあると良いが、abc442_e（1355）が例題にある。次は節に合う候補（第三者の解説での裏付けは research 08 のもの）。
- abc296_g（G. Polygon and Points、2241。ap.py で実在と difficulty を確かめた）：凸多角形に対する多数の点の内外判定。内部の点から見た頂点の偏角で辺を二分探索する。research 08 §5 に例題として載る（point-in-polygon との境界）｜https://merom686.hatenablog.com/entry/2023/04/01/235440
- Library Checker の sort_points_by_argument は verify に入っている。本文では Library Checker の順序の違い（(−π, π]・原点は 0）に触れた

### base-conversion

- abc414_c（ABC414 C. Palindromic in Both Bases、diff 709）：N 以下で 10 進でも A 進でも回文になる整数の総和を求める（N ≤ 10^12）。10 進の回文を前半から生成し、各候補を A 進に変換して回文か判定する。abc319 以降の練習として。裏付け：https://zenn.dev/testcampus/articles/72d76d6366df7d
- abc220_b（ABC220 B. Base K、diff 58）：K 進で書かれた 2 数を 10 進に直して積を求める型と思われる（題名だけ ap.py で確認。第三者の解説は未確認）
- arc164_a（ARC164 A. Ternary Decomposition、diff 532）：3 進表記の桁和と分解の個数の関係を使う型と思われる（ap.py で実在のみ確認。解説は未確認）

### bfs

- 台帳の確認済みの問題で数は足りている（例題 1・練習 5・力試し 1）。補充の候補は次のとおり（ap.py で存在を確認するのはメイン側で）：
- abc211_d（確認済み・shortest-path-dag の例題）：最短路の本数。本ページでは shortest-path-dag へのリンクだけにした。練習に入れる必要はない
- abc472_d（確認済み・grid の練習、summary 未確定）：多始点 BFS の型と分類されている。summary が「（執筆時に確かめる）」のため使わなかった。grid-graph の執筆時に確かめる

### binary-search

- abc299_d（D. Find by Query、diff 684、台帳で確認済み）：先頭が 0・末尾が 1 の隠れた 01 列で、隣と値が異なる位置を 20 回以内の質問で見つける。めぐる式の判定を質問に置き換える型。裏付け：https://oraclesqlpuzzle.ninja-web.net/kyoupro/05-atcoder-02-abc/kyoupro-abc299-d.html
- abc319 以降の問題は、基礎のページの要件でないため探していない

### binomial-coefficient

- 基礎のページとしては例題 1・練習 2 で目安の下限にあたる。足すなら次の型が合う（どれも台帳で確認済みだが、別のページの持ち物）。
- abc145_d（lattice-paths の例題）：2 種類の移動の回数を決めて並べ方を二項係数で数える。本ページの「0/1 列の形」の練習として practice に足せる。裏付け https://drken1215.hatenablog.com/entry/2020/04/26/180000
- abc156_d（binomial-precompute の練習）：n が巨大で k が小さい二項係数。使い分けの表の参照先としてだけ使い、本ページには載せない方がよい

### binomial-precompute

- abc145_d（diff 1009、台帳で確認済み。今は lattice-paths の例題）｜ナイトの動きで (X, Y) へ行く方法の数。(X+Y)/3 回の移動のうち一方の動きの回数を決めると二項係数 1 つになり、表の大きさは X+Y の 1/3 程度まで要る。表の大きさの節の練習として practice に足す案｜https://drken1215.hatenablog.com/entry/2020/04/26/180000
- 基礎の練習が ABC2 問（abc156_d・abc132_d）と少ないので、abc319 以降で、表の大きさが 2N や N+K になる ABC の E を 1 問足したい。台帳の recent（abc453_e・abc458_e など）は前提として届く問題で、この手法を主に使うかは確かめていない。

### bit-full-search

- abc197_c｜数列を区間に区切り、各区間の OR の XOR を最小化する（区切り方 2^(N−1) 通り）｜https://oraclesqlpuzzle.ninja-web.net/kyoupro/05-atcoder-02-abc/kyoupro-abc197-c.html｜台帳では確認済み（xor の practice）。practice への追加を推す
- abc104_c｜各難易度の問題を「全部解く／解かない」で 2^D 通り決め、残りは 1 つの難易度だけを部分的に解く貪欲で、目標点に届く最小の問題数を求める｜第三者の解説は未取得（研究メモ 01-basics §4.B・§7.5 に型として記載）｜ap.py で実在を確認（C. All Green、diff 1393）。台帳にない。片側を bit で決めて残りは貪欲の型で、abc159_e と並ぶ水の代表。裏付けの解説を取ってから台帳に足す
- abc150_c｜2 つの順列が辞書順で何番目かを、全順列を列挙して求める｜https://drken1215.hatenablog.com/entry/2020/01/12/122100｜台帳では確認済み（permutation の practice）。順列全探索の練習として追加してよい

### bit-operations

- abc171_e（E. Red Scarf、diff 778、台帳で確認済み・xor のページの例題）｜「自分以外の XOR」から各値を復元する。本文の XOR の性質の節の型そのもの｜https://drken1215.hatenablog.com/entry/2020/06/22/122500（台帳の evidence）。このページの練習に足すことを提案する（例題は xor のページのまま）
- arc098_b（D. Xor Sum 2、diff 1404、台帳で確認済み・two-pointers の力試し）｜和と XOR が等しい ⇔ 桁が重ならない、を使う｜https://drken1215.hatenablog.com/entry/2018/06/26/125054。このページの力試しの候補（尺取り法が要るので、力試しなら可）
- 部分集合の部分集合の列挙で 3^N の DP（集合を 2 つ以上のグループに分ける ABC の問題）は subset-enumeration-dp の担当なので、ここには足さない

### bitwise-independence

- abc347_d（D. Popcount and XOR、diff 1041、ap.py で確認）｜popcount(X) = a、popcount(Y) = b、X xor Y = C となる 60 bit 以内の (X, Y) を 1 つ作る（なければ -1）｜C の bit が 1 の位置は X・Y の一方だけ、0 の位置は両方か両方でないかと bit ごとに決まるので、個数と偶奇で可否を判定して割り振る。abc319 以降の問題なので練習に向く（易しい側）｜https://zenn.dev/testcampus/articles/089f7b56e3745c 、https://qiita.com/hyouchun/items/0c2a8b3bc4f281b34e24
- abc238_d（D. AND and SUM、diff 921、ap.py で確認）｜x AND y = a かつ x + y = s となる非負整数の組があるかを判定する｜a + b = (a xor b) + 2(a and b) を使い、s − 2a ≥ 0 かつ (s − 2a) AND a = 0 で判定する。節 addition の練習（易しい）。bit-operations の xor-properties の練習でもよい｜https://qiita.com/rute_not_route/items/5d586f9f28b605d8233f 、https://qiita.com/u2dayo/items/12ac3e1834ededba1824
- arc092_b（ABC091 D. Two Sequences、diff 2207、ap.py で確認）｜2 つの数列のすべての組の和の XOR を求める｜bit k ごとに mod 2^(k+1) の余りをソートし、和が [2^k, 2^(k+1)) か [3·2^k, 2^(k+2)) に入る組の数の偶奇を二分探索で数える。節 addition の「下の bit をまとめて見る」の力試し（黄なので力試しの上限）｜第三者の解説の URL は未確認（drken の記事があると思うが、URL を確かめていない）

### brute-force

- 台帳にない（または他ページの担当の）問題で、このページの節の型に合うもの。本文では ID を出していない。
- abc051_b｜0 以上 K 以下の X, Y, Z で X+Y+Z = S となる組を数える｜what-to-enumerate（コード片 fix-two と同じ形。練習向き）｜https://drken1215.hatenablog.com/entry/2019/07/06/221600
- arc096_a｜A・B・AB ピザの買い方で費用を最小にする（AB ピザの枚数だけ全探索）｜what-to-enumerate（残りの最良がすぐ決まる型。本文で型だけ触れた）｜https://qiita.com/e869120/items/eb50fdaece12be418faa
- typical90_p｜3 種類の硬貨でちょうど N 円払う最小枚数（2 種類を全探索し 3 種類目は割り算）｜what-to-enumerate（割り切れるかの確認）｜https://github.com/Reputeless/tenkei_90
- abc089_c｜頭文字ごとに人数を数え、5 文字から 3 つを選ぶ 10 通りを試す｜small-candidates（同じ種類をまとめる）｜https://blog.hamayanhamayan.com/entry/2018/03/05/003346
- abc476_d｜（research/00 §2.3.8 で「全探索＋累積和＋二分探索」）問いは未確認｜half-enumeration｜https://qiita.com/comet725/items/fb0182ba408f04fa3a59 （未読）
- abc474_e｜（同「ソート＋境界の全探索＋累積和・累積 min」）問いは未確認｜half-enumeration（分け目の全探索）｜ikatakos.com の abc474 の記録（未読）
- half-enumeration の節は、いま練習に該当する問題がない。frequency_evidence に挙がった abc474_e・abc476_d・abc480_e のどれかを台帳で確かめて練習に足すのがよい（abc469 以降の新しい ABC で、水への入口の型）。

### complement

- abc156_d：1 本以上選ぶ選び方 2^n − 1 から、本数が a・b のものを引く（空集合の扱い）。https://drken1215.hatenablog.com/entry/2020/04/22/013400 （台帳に確認済みで登録あり。pages に complement の practice を足す案）

### complete-binary-tree

- abc264_h（Ex. Perfect Binary Tree、diff 2660）｜頂点を順に加えながら、完全二分木の高さが log N 程度しかないことを使って祖先の DP だけを更新する｜https://kmjp.hatenablog.jp/entry/2022/08/13/0930 （research 04-tree §5.1 の候補。ap.py で実在と diff 2660（橙）を確かめた。台帳にはない。基礎のページには難しすぎるので、載せるなら tree-dp か別の上位のページの力試し）
- 練習が 1 問しかない（catalog の problems_note のとおり）。基礎の形の ABC の問題は見つけられなかった。セグメント木を番号で自作する問題や、ヒープの問題を練習に回すかはメインで判断してほしい

### complexity-estimation

- catalog の数（例題 1・練習 4）で足りているので必須ではない。複数テストケース（ΣN）と定数倍の節に台帳の問題がないので、余力があれば次を探す価値がある（未確認。ap.py と第三者の解説での裏付けはまだしていない）。
- 複数テストケースで ΣN の制約がある ABC の問題（abc319 以降に多い形式）：ケースごとの初期化を使った分だけにする型
- research 08 §4.9 の abc258_g・abc348_f（定数倍の差の具体例として挙がっている）：定数倍の節の練習か力試しの候補。ただし bitset のページとの重なりを確かめる必要がある

### connected-components

- abc284_c（C, diff 193）｜単純無向グラフの連結成分の個数を求める。台帳にあり確認済み（graph-basics の練習）。このページの練習にも足したい｜https://drken1215.hatenablog.com/entry/2023/09/28/022105
- abc199_d（D, diff 1804）｜N ≤ 20 のグラフの 3 彩色の数。連結成分ごとに DFS で塗り、成分ごとの数を掛け合わせる（台帳にあり確認済み。small-graph-brute-force の力試し）。「成分ごとに独立に数える」の力試しとして参照の候補｜https://blog.hamayanhamayan.com/entry/2021/04/25/002321

### construction

- abc474_d（D. Outweigh、diff 389、ap.py で実在を確認）：A_x > B_x となる位置 x があるかで可否が決まり、あればその位置だけを非常に大きい値にした数列を作る（重み付きの比較の条件を満たす数列の構築）。裏付け：https://qiita.com/comet725/items/3772fa3312c73be086e3 。ただしこの記事は解答コードが中心で問題の条件が十分に読み取れず、ikatakos 氏の abc474 の記録には D の節がなかった。問いの裏付けをもう 1 件取ってから練習に足すのがよい（最近の ABC の基礎の構築として価値が高い）
- abc282_f（F. Union of Two Sets、diff 1734、ap.py で確認）：区間をあらかじめ選んでおき、どのクエリ区間も選んだ 2 つの和集合で表す。2 冪の長さの区間を用意する（Sparse Table の考え方）。裏付け：https://drken1215.hatenablog.com/entry/2022/12/29/112939（research/01 §5 の表。今回は記事を開いていない）。インタラクティブ寄りなので力試しの候補
- abc146_d（D. Coloring Edges on Tree、diff 1192、ap.py で確認）：木の辺を、同じ頂点に接する辺が違う色になるよう最少の色数で塗る。最大次数が下界で、DFS で達成する（上界・下界と達成の型）。research/01 §4.L が bound-and-construct の候補に挙げている。裏付けの解説はまだ確かめていない。本文の確認問題「木の辺の塗り分け」は問題 ID を出さずにこの型を扱った

### contribution

- abc172_d｜1 以上 N 以下の各 K について K × (K の約数の個数) の総和を求める。約数 d ごとに倍数の和として数え直す。台帳は確認済みで sigma-manipulation の例題｜練習（本文の「各約数の寄与」に対応する問題がまだない）｜https://qiita.com/dvoraker3/items/8388ab6e1dc3af55070e
- abc147_d｜全ペアの XOR の総和。bit ごとに 0 と 1 の個数の積で数える。台帳は確認済みで bitwise-independence の例題｜練習（任意。本文はリンクで済ませた）｜https://drken1215.hatenablog.com/entry/2020/04/25/032000

### coordinate-compression

- catalog の数（例題 1・練習 3）で足りており、力試しは 0。どれも台帳では確認済みで、ほかのページの持ち物なので、このページには役割の追加の提案になる。
- abc231_f（F. Jealous Two、diff 1580）｜A_i ≥ A_j かつ B_i ≤ B_j となる組の数を求める。B を圧縮して BIT で数える｜https://zenn.dev/m193h/articles/20211212sun001912m193habc231｜役割：challenge（with-ds の節の「値の大小で数える」の代表。台帳では fenwick-tree の practice）
- abc221_d（D. Online games、diff 832）｜ログイン期間からちょうど k 人がログインしていた日数を k ごとに求める。端点を圧縮していもす法｜https://oraclesqlpuzzle.ninja-web.net/kyoupro/05-atcoder-02-abc/kyoupro-abc221-d.html｜役割：practice（intervals・keep-original の節の型そのもの。台帳では imos の practice）

### counting-basics

- catalog の練習は abc307_e の 1 問だけで、手引きの目安（練習 2〜6）に届かない。
- abc178_c（Ubiquity、diff 653、ap.py で実在を確認）：長さ N の数字の列で 0 と 9 をどちらも含むものを数える。重複順列と、和の法則で重なりを扱う型。台帳では complement の例題なので、ここでは練習として足す案｜https://drken1215.hatenablog.com/entry/2020/10/09/162600
- 積の法則・円順列だけで解く易しい ABC（C・D）は、今回は探しきれていない。必要なら調査で「並べ方の数」「何通り」の ABC C を拾う

### counting-fix-order

- abc209_c（C. Not Equal、diff 285）：各 i について 1 以上 C_i 以下の整数を、すべて異なるように選ぶ方法の数。上限の小さい順に決めると選択肢が C_i − i 個で一定になり積の法則が使える（本文の bfs-order の節の最初の例）。裏付け https://qiita.com/AKpirion/items/21b1aead96fec77d67ef 。diff が低いので practice の先頭（易しい順）に置く想定
- abc319 以降の問題は見つからなかった（Web 検索 3 回）。水のページなので 1 問以上ほしいが、「n!/k!」「親が子より先」の型は ABC では近年少ない

### coupon-collector

- 練習は 2 問（目安の下限）で、例題 1・練習 2 と基礎の目安を満たす。ap.py と research の候補表を見たが、等確率の段階分けか幾何分布そのものを主役にする確認済みでない ABC の問題は見つけられなかった
- 関連として research にある abc350_e（E. Toward 0、diff 1385）・abc314_e（E. Roulettes、diff 1722）は自己ループの移項（E = 1 + (1 − p)E の一般化）が主役で、expected-value-dp の練習が持ち主として適切。本ページには載せない

### cpp-algorithms

- 探していない（C++ のページは問題を置かない方針のため）

### cpp-math-functions

- 探していない（C++ のページは problems を置かない方針。catalog の problems_note のとおり）

### crt

- **abc371_g**（G. Lexicographically Smallest Permutation、diff 2348、台帳で確認済み）：置換を何回か適用した列の辞書順最小。巡回ごとに「操作回数 ≡ r (mod 巡回の長さ)」の条件を前から足し、法が互いに素でない CRT で統合する。裏付け：https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2024/0914_abc371 。crt の力試しにすることを提案する（上の台帳への提案）
- abc319 以降で crt を例題・練習にできる水〜青の ABC は、drken の「中国剰余定理」カテゴリ（11 件。ABC は 103 C・186 E・193 は無し）と Web 検索では見つからなかった。abc186_e（Throne）は ext-gcd の例題なので crt には足さない

### cycle-detection

- 確認済みの問題で数は足りている（例題 1・練習 2・力試し 1）。補うなら次の型が欲しい。
- 有向グラフの閉路を 3 色の DFS で「復元」まで行う問題（出次数 1 でない一般の有向グラフ）。今の練習の abc311_c は出次数 1 なので、復元の一般形を練習できる問題がない。候補は未調査（ap.py と第三者の解説で探す必要がある）
- 無向グラフの閉路の復元（多重辺を含む）。Library Checker の cycle_detection_undirected（AtCoder の問題ではないので台帳の対象外）

### dfs

- abc138_d（D. Ki、diff 920）：根付き木の部分木への加算を、根から DFS で値を流して処理する。調査レポート §5.2 に例題の候補として載るが台帳にない。tree-traversal の例題の方が合うかもしれない。裏付け：https://blog.hamayanhamayan.com/entry/2019/08/19/024030
- 練習の並び：typical90_bt は difficulty がなく、★4 で閉路の扱いがあるため最後に置いた。complexity-estimation のページでの位置と合わせるなら確認してほしい

### digit-and-mod

- abc353_d（D. Another Sigma Problem、diff 844）｜数列の i < j のすべての組について、A_i の後ろに A_j を連結した数の総和を 998244353 で割った余りを求める。数の連結の節の「ペアの連結の総和」の型そのもの（本文では問題 ID を出さず型だけ書いた）。練習の候補。diff が基礎の帯なので、練習の最初に置く｜https://torus711.hatenablog.com/entry/2024/05/12/202925 （検索結果の要約で、A_j の桁数 d ごとに A_i·10^d が寄与することを確認。本文はまだ読んでいない）
- abc319 以降の問題は abc460_e が 1 問ある（水の練習）。例題の abc164_d は古いので、接尾辞の余りの型で abc319 以降の問題があれば例題か練習に足したいが、今回は見つけていない

### digit-dp

- tdpc_number（TDPC E. 数、diff なし）｜N 以下（N は最大 10^4 桁）の正の整数のうち、各桁の和が D の倍数になるものの個数。EDPC S と同じ型なので練習に足すなら 1 問として｜https://sigma425.hatenablog.com/entry/2016/08/02/214547 （research/02-dp §5.1 に候補として載っている。台帳には未登録。中身は今回は読んでいない）

### dijkstra

- abc369_e｜指定された K 本（K ≤ 5）の橋をすべて通る、頂点 1 から N への最短時間をクエリごとに答える｜https://www.cnblogs.com/Lanly/p/18402027（調査レポート 03-graph §5.2 の裏付け）｜ap.py で実在と diff 1301 を確認（台帳には未登録）。頂点間の距離は全点対で前計算するので、dijkstra よりワーシャルフロイド法の練習に向く
- 確認済みの問題で役割の数（例題 1・練習 6・力試し 2）は足りているので、補充はしなかった。

### divisor-count-bound

- **abc300_e**（E. Dice Product 3、diff 1354、台帳で確認済み）：サイコロの目を掛けていき積がちょうど N になる確率。現れる値が N の約数（2・3・5 の積）に限られ、メモの大きさが d(N) で抑えられる。divisor-dp の節の「メモ化再帰でも同じ」の練習に向く。裏付け：https://drken1215.hatenablog.com/entry/2023/05/03/212600 （drken の「数量が小さいことの活用：約数の個数」カテゴリ）
- **abc212_g**（G. Power Pair、diff 2150、台帳で確認済み）：P − 1 の約数ごとに φ(d) を求めて数える（P ≤ 10^12）。約数ごとに重い処理をしても間に合う型の力試しに向く。裏付け：https://drken1215.hatenablog.com/entry/2021/08/01/163600
- **abc335_g**（G. Discrete Logarithm Problems、diff 2614、台帳で確認済み）：P − 1 の約数を使って位数を求める。発展なので候補にとどめる。裏付け：https://drken1215.hatenablog.com/entry/2024/01/07/220400
- abc319 以降の水（E 相当）でこのページの例題になる ABC は見つからなかった。例題は catalog どおり arc167_b のままにした。arc167_b は「約数の個数の上界」よりも「約数の個数の公式と偶奇」の問題なので、上界の見積もりそのものが鍵の例題としては typical90_cg の方が近い。例題と練習の入れ替えを検討してほしい（typical90_cg は difficulty がない）

### divisor-enum

- abc180_c｜N の約数をすべて小さい順に出力する（√N までのループで i と N/i を集めてソート）。台帳では確認済みで divisors-and-multiples の練習｜練習（diff 142。列挙とソートの最初の 1 問）｜https://drken1215.hatenablog.com/entry/2020/10/21/194700 （台帳の evidence）
- typical90_cg｜a ≤ b ≤ c、abc = K（K ≤ 10^12）の組の数。約数の組を全部試す。台帳では確認済みで divisor-count-bound の練習｜練習（本文の「積が N になる組」の 3 数の型の代表）｜https://github.com/E869120/kyopro_educational_90/blob/main/sol/085.cpp （台帳の evidence）
- abc420_g｜n² + n + X が平方数となる整数 n をすべて求める（4X − 1 を 2 数の積に分ける約数の列挙）｜練習（diff 1427、abc319 以降）｜research/06 §5.3 では usaco.guide の練習問題の一覧でだけ確認（状態はタグ）。第三者の解説では未確認で、台帳に入れる前に確かめが要る

### doubling

- abc136_d｜R と L のマスで子どもが 10^100 回移動した後の各マスの人数（決まった遷移を十分大きい偶数回進める）｜練習（台帳には run-length-encoding の練習としてある。ダブリングの解き方もある）｜https://drken1215.hatenablog.com/entry/2020/12/29/190100（drken のダブリングの分類に入っている。本文は未読）
- arc060_c｜ホテルの間を 1 日 L 以内で移動するとき、2 つのホテルの間の最小日数を答えるクエリ（ダブリング上の二分探索の代表）｜力試し（diff 2154 で黄。ap.py で確認）｜第三者の解説はまだ見つけていない（要調査）
- 水のページだが abc319 以降（7 問体制）の問題が 0 問である。ap.py の search は題名でしか引けないので、ダブリングの最近の ABC は見つけられていない。第三者の解説（はてなブログの分類など）で探す必要がある
- （対応の節）- 指摘 8（直すとよい・arc060_c を力試しに置く）：採らなかった。第三者の解説での裏付けがまだなく、台帳への追加はメインの仕事なので、上の「問題の補充の候補」に残す

### dp-basics

- catalog の数（例題 1・練習 4）は目安の範囲だが、数え上げの練習が abc129_c の 1 問だけなので、状態に少し情報を足す易しい問題を足す候補を挙げる。
- abc245_c（Choose Elements、diff 403）：各位置で A_i か B_i を選び、隣り合う値の差をすべて K 以下にできるかを判定する。dp[i][直前に A を選んだか B を選んだか] の可否 DP｜https://drken1215.hatenablog.com/entry/2022/03/29/112500（記事の本文の条件の不等号は誤植で、コードと図は「K 以下」）
- abc242_c（1111gal password、diff 512）：各桁が 1〜9 で隣り合う桁の差が 1 以下の N 桁の整数の個数を求める。dp[i][末尾の数字] の数え上げ｜https://kazun-kyopro.hatenablog.com/entry/ABC/242/C
- abc248_c（Dice Sum、diff 787）：各項が 1〜M で総和が K 以下の長さ N の列の個数。和を状態にする数え上げ｜https://kazun-kyopro.hatenablog.com/entry/ABC/248/C（調査レポート 02-dp §5.3 の裏付け。私は開いていない）
- abc040_c（柱柱柱柱柱、diff 896 参考値）：Frog 1 と同じ構造｜https://qiita.com/drken/items/dc53c683d6de8aeacf5a（例題と重なるので優先度は低い）

### dp-dag

- abc232_d｜壁のあるグリッドを左上から右か下へだけ進むとき、通れるマスの数の最大を求める（グリッドが DAG で、行ごとに左から見る順がトポロジカル順）｜練習（diff 539 で最も易しい。level_evidence にも挙がっている）｜https://qiita.com/uniTM/items/2d7a99ccd449c5140c4f
- abc037_d｜グリッドで隣へ値が増える向きにだけ進む経路の総数（値の昇順がトポロジカル順）｜練習（diff 1377 参考値。台帳にはまだない。memoized-recursion の候補にも挙がっている）｜https://qiita.com/drken/items/03c7db44ccd27820ea0d（類題として挙げている。解法は本文では未確認）
- 基礎のページだが、練習が水（1528・1540）に寄っている。abc232_d を足すと易しい順の入口ができる
- abc319 以降の問題は abc335_e だけ。最近の ABC の DAG 上の DP の問題は見つけていない

### dp-grid

- 足さなくても例題 2・練習 6・力試し 1 で目安を満たし、abc319 以降も 2 問（abc369_f・abc344_f）ある
- abc415_e（E. Hungry Takahashi、diff 1212、台帳で確認済み・binary-search-answer の練習）：グリッドを右か下に進み、所持枚数が負にならない最初の枚数の最小を求める。右下から「要る枚数の最小」を DP する向きの反転の練習として dp-grid にも practice で載せられる。裏付け：https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2025/0719_abc415
- abc201_d（D. Game in Momotetsu World、diff 1317、確認済み・minimax の例題）：右下から埋めるグリッドのゲーム。本文では minimax の節へのリンクで触れただけ。dp-grid の練習に足すかはメインの判断

### dp-mod-state

- catalog の problems_note のとおり、abc319 以降で余りを状態にする DP が主役の問題は見つけられなかった（水のページに abc319 以降が 1 問以上という目安を満たせていない）。
- abc244_e（diff 1125）｜長さ K の歩道で頂点 X を通る回数が偶数のものの数。偶奇（2 で割った余り）を状態に持つ（research/02 §5.3 の候補）。練習に向く｜https://kazun-kyopro.hatenablog.com/entry/ABC/244/E （未読。台帳に入れる前に確かめる）
- typical90_e（★7）｜使える数字が決まった N 桁（N ≤ 10^18）の数で B の倍数の個数。余りの DP を桁数の倍化で速くする。台帳では matrix-power の力試しにある。力試しか related の参照に向く｜https://drken1215.hatenablog.com/entry/2021/10/08/231200 （台帳の evidence）

### dp-order

- abc232_d｜壁のあるグリッドを左上から右か下へだけ進むときに通れるマスの数の最大（行ごとに左から回す順が依存の向きに合う）｜練習（diff 539 と易しい。添字の順の入口として）｜https://kazun-kyopro.hatenablog.com/entry/ABC/232/D（02-dp §5.3 にある。本文では未読）
- abc319 以降の問題は abc341_f（練習）だけである。水のページに 1 問以上という目安は満たすが、例題は abc188_e・abc197_e と古い。abc319 以降で「後ろから」「値の順」が主役の E を、ap.py と第三者の解説で探す余地がある（今回は探しきれていない）

### dp-prefix-sum

- abc183_e（E. Queen on Grid、diff 1288、台帳で確認済み）：壁のあるグリッドで右・下・右下へ何マスでも進めるときの経路数。方向ごとの累積を壁で 0 に戻す。裏付け：https://drken1215.hatenablog.com/entry/2020/11/16/204900
- abc130_e（E. Common Subsequence、diff 1676、台帳で確認済み）：2 つの列の、内容の等しい部分列の組（位置で区別）の数。左上の長方形からの遷移を 2 次元累積和で O(1) にする。裏付け：https://drken1215.hatenablog.com/entry/2019/06/21/230200
- abc222_d（D. Between Two Arrays、diff 865、ap.py で実在を確認。台帳になし）：a_i ≤ c_i ≤ b_i を満たす広義単調増加の列 c の数。最後の値を状態にし、遷移元が [0, x] の接頭辞になるので累積和で O(NM)。緑の入門の練習として易しい側に置ける。裏付け：https://blog.hamayanhamayan.com/entry/2021/10/10/133722
- abc319 以降の問題は abc442_f（2026、累積 min）が既にある。ほかは探していない

### dp-reconstruction

- tdpc_lexicographical（TDPC G. 辞書順、台帳で確認済み・diff なし）：文字列の空でない異なる部分列のうち辞書順で K 番目を求める。後ろからの個数の DP を K で頭打ちにして先頭から決める型で、K 番目の節のそのままの力試しになる。challenge として dp-reconstruction にも載せることを提案する。裏付け：https://drken1215.hatenablog.com/entry/2021/08/10/193121（研究ノート 02-dp の表にある URL。今回は開いていない）
- abc363_d（ABC363 D. Palindromic Number、diff 975）：N 番目に小さい回文数。桁数ごとの個数で桁数を決めてから前半を決める（数え上げで K 番目を決める型の易しい例）。裏付け：https://programming-hiroba.com/abc363-d/（研究ノート 02-dp の表にある URL。今回は開いていない。台帳での状態は未確認）
- abc319 以降で「選び方を出力する DP」の問題はこのページの台帳では abc369_f だけである。ほかの候補は今回見つけられなかった

### dp-sequence-partition

- abc370_e（E. Avoid K Partition、diff 1453、2024-09-07。ap.py で確認）｜数列を連続する区間に区切る方法のうち、和がちょうど K になる区間を含まないものの数を求める（mod 998244353。A_i と K は負もありうる）｜例題（水・abc319 以降・E の位置。representative の agc031_b より素直な代表）。最後の区間で分け、全体の和から「累積和の値が S_i − K の j の dp の和」を連想配列で引く。本文の two-pointers 節の「除く j が値で決まる」の型を ID なしで書いてある｜https://scrapbox.io/kani/ABC370_-_E_-_Avoid_K_Partition ・ https://www.cnblogs.com/superl61/p/18523419
- research の 02-dp §5 末尾で abc370_e は「解説で手法を確認できなかったので外した」とあるが、上の 2 つの第三者の解説で区間分割 DP（全体から引く遷移）だと確かめた。台帳に足すなら、本文の two-pointers 節の箇条書き「除く j が値で決まる」をこの問題の例題の見出しへのリンクにし、例題を 2 問（abc370_e → agc031_b）にするとよい。

### dp-state-design

- abc464_d（D. Celester、diff 752、ap.py で実在を確認、台帳に未登録）：N 日の天気を晴れか雨に決め、元の天気から変えると費用がかかり、雨の翌日に晴れると得点が入るときの、得点から費用を引いた最大を求める（問いは解説のコードからの推測を含む）。直前の天気を状態にする型で、典型の要約（直前の値）の練習に。裏付け：https://qiita.com/comet725/items/79b0587199021cc0f723 。recent-abc.yaml でも dp-state-design#typical-summaries に割り当て済み
- abc462_f（F. More ABC、diff 1952、ap.py で実在を確認、台帳に未登録）：recent-abc.yaml で dp-state-design#last-characters に割り当て済み。「A」「AB」まで一致しているかと作った ABC の数を状態にする（recent-abc.yaml の note）。難しさから力試しの候補。裏付け：https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2026/0613_abc462 （今回は読んでいない。登録前に問いを確かめてほしい）
- abc456_d（D. Not Adjacent 2、diff 586、台帳で確認済み・subsequence-and-substring の練習）：recent-abc.yaml では dp-state-design#last-characters に割り当てられている。こちらにも練習として載せるかはメインの判断（今回は evidence を読んでいない）

### euler-tour

- abc187_e（diff 1358、台帳では tree-imos の例題）：辺の片側の頂点すべてに加算するクエリの後の各頂点の値。euler-tour の練習に足すと、補集合の 2 区間への加算を BIT で行う解き方と、いもす法でよい場面の対比になる。裏付け：https://qiita.com/recuraki/items/dd85ed26718c851582b6 （題名に「オイラーツアー+区間和のアプローチ」。本文は読んでいない。検証時に確かめてほしい）
- abc319 以降で青の帯（1600〜1999）の例題は見つけられなかった（catalog の level_evidence の open_issues のとおり）。検索を 1 回しただけなので、続けて探す余地はある

### event-sort

- catalog の数（例題 2・練習 4・力試し 1）で足りており、abc319 以降の問題も 1 問（abc478_d）ある。追加は必須ではない。
- abc467_e（recent-abc.yaml にあり、frequency_evidence に挙がっている）：台帳にない。ikatakos 氏の記録によれば主役は変数の固定と偶奇で、折り返し点をソートして増分を追う部分がイベントソートに当たる。このページの練習にするより fix-variable の側で扱うのがよい。裏付け：https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2026/0718_abc467 （本文には使っていない。中身は読んでいない）

### expected-value-dp

- abc326_e｜サイコロを振って給料が決まる過程の、給料の期待値を mod 998244353 で求める（後ろからの期待値と累積和）。台帳で確認済みで、rational-mod の練習。prefix-sum の節の練習に足せる｜https://programming-hiroba.com/abc326-e/ （台帳の evidence。本文の確認はしていない）
- abc189_f｜振り出しに戻るマスがあるすごろくの期待値（未知数を置く）。expectation-linear-equations 側の例題候補で、このページの使い分けの裏付けになる｜https://kmjp.hatenablog.jp/entry/2021/01/23/0900 （調査レポート 02 §5.1 に記載。台帳の状態は見ていない）
- abc319 以降（7 問体制）は abc350_e・abc382_e の 2 問が練習にある。例題に 7 問体制の問題はない（水の E で期待値 DP の基本形の新しい問題は見つけていない）。

### exponent-mod

- 練習が abc222_g の 1 問だけで、abc319 以降の問題もない。ap.py の検索（Tower・Power・Exponent・Fermat・Euler・累乗・べき・塔）と Web の検索では、指数を p − 1 や φ(m) で割ることが主役の ABC の問題は新たに見つからなかった。
- abc212_g（G. Power Pair、diff 2150。台帳で確認済み）：素数 P について x^n ≡ y となる組の数。上の台帳への提案のとおり練習に足せる。裏付け：https://drken1215.hatenablog.com/entry/2021/08/01/163600
- tenka1_2017_f（F. ModularPowerEquation!!、diff 3653。ap.py で実在を確かめた）：A^K ≡ K (mod M) となる K を求める問題で、法を φ に置き換えて再帰する一般化（黄の節）の典型と記憶しているが、第三者の解説で問いを確かめていない。発展の帯なので、確かめられても力試しか参照にとどめる
- Library Checker の Tetration Mod（verify に既にある）：一般の法の節の確認用。AtCoder の問題ではないので台帳の対象外

### ext-gcd

- abc340_f｜整数の点 (X, Y) が与えられ、原点・(X, Y)・(A, B) の三角形の面積が 1 になる整数の点 (A, B) を 1 つ求める（なければ -1）。面積は \｜AY − BX\｜/ 2 なので AY − BX = ±2 を拡張ユークリッドで解き、gcd(X, Y) が 3 以上なら解なし｜練習（diff 1516、水。abc319 以降の水のページの根拠にもなる）｜https://programming-hiroba.com/abc340-f/ （check_noai で noai の指定なしを確認。付録 B のドメイン）
- 本文の「応用の型」では、台帳にないので問題 ID を出さずに型（面積 1 の三角形の格子点）だけを書いた。台帳に入れば、練習の囲みに abc340_f を足し、方針の折りたたみに「$\lvert AY - BX \rvert = 2$ に直し、$\gcd(X, Y) \mid 2$ を判定、拡張ユークリッドの解を $2/g$ 倍する」を書ける
- frequency_evidence の abc459_g（diff 3123）は難しすぎるので、このページの問題には使わなかった

### fenwick-tree

- abc285_f｜一文字の書き換えを挟みながら、部分文字列が「全体をソートした文字列」の部分文字列になっているかを答える｜文字ごとの個数の BIT 26 本と、隣り合う文字の大小の逆転を 0/1 で持つ BIT（diff 1876。練習か力試し）｜https://qiita.com/recuraki/items/38a850c4aad563853149（research/05-ds §5 の候補。記事はこの作業では読んでいない）
- 例題・練習の数は手引きの目安（例題 1〜3、練習 2〜6、力試し 0〜3）を満たし、abc319 以降の問題（abc351_f）も 1 問ある。補充は必須ではない。

### fix-variable

- abc376_e（Max × Sum、diff 1063、確認済み）：A の最大値を固定し、それ以下の中から B の小さい K 個の和をヒープで保つ。「最大値を固定して残りを最適化する」節の代表。台帳では greedy-priority-queue の practice だけなので、fix-variable の practice に足す案。https://oraclesqlpuzzle.ninja-web.net/kyoupro/05-atcoder-02-abc/kyoupro-abc376-e.html （research/01 §5 でも「fix-variable と共通」とある）
- arc084_a（Snuke Festival、diff 1096、確認済み）：中段を固定し、上段・下段の個数を二分探索で数える。真ん中を固定する代表。台帳では binary-search の practice。fix-variable の practice に足す案。https://drken1215.hatenablog.com/entry/2021/02/25/223800
- abc458_e を外すと練習が 2 問になるので、上の 2 問のどちらかを足すと thinking の目安（練習 2〜6）に余裕が出る
- （対応の節）- 指摘 6：台帳の直しはメインの作業なので、上の「台帳への提案」のとおり（abc453_e の summary・approach・evidence、abc458_e を fix-variable の pages から外す、checked の日付）。本文は変えていない。練習を足す場合の候補は「問題の補充の候補」の arc084_a・abc376_e

### floor-quotient-enum

- abc414_e（Count A%B=C、diff 1296、ap.py で確認）｜1 以上 N 以下の相異なる a, b, c で a mod b = c となる組の個数を 998244353 で割った余りで求める。b < a の組の数から a が b の倍数の組の数（Σ⌊N/b⌋ の形）を引き、商が同じ区間ごとにまとめる｜練習（水・abc319 以降の根拠になる。catalog の level_evidence と problems_note の「abc319 以降の根拠がない」を解消できる）｜https://zenn.dev/nakst_hide/articles/f5b3e3a3473e9d （N の上限は記事に明記がなく未確認。もう 1 つ解説で確かめたい）

### fractional-binary-search

- 水のページに abc319 以降の問題が abc469_e と abc324_f の 2 問ある（abc324_f は 2023-10 で 7 問体制）ので、手引き §10 の目安は満たしている。今回は新しい候補を探していない
- 練習に平均の易しい形（連続部分列の平均で長さの下限つき）が台帳にない。ABC の候補が見つかれば補いたい（未調査）

### functional-graph

- 確認済みの問題で足りている（例題 2・練習 3）。足すなら次の候補（台帳への追加を提案。本文では触れていない） - abc179_e（E. Sequence Sum、diff 1175、台帳で確認済み・periodicity の例題）：A_{i+1} = A_i^2 mod M の列の和。写像の周期を見つける。裏付け：https://drken1215.hatenablog.com/entry/2020/09/20/091500 。ただし主題は周期性のページ（periodicity の例題）なので、ここでは練習としての参照が妥当 - abc311_c（C. Find it!、diff 448、台帳で確認済み）：各頂点から辺が 1 本出るグラフの閉路を 1 つ出力する。cycle-detection の練習として台帳にある。functional-graph にも練習として載せる候補（易しい側の 1 問）

### game-basics

- 水のページだが abc319 以降の ABC の例題・練習は abc354_e・abc380_f・abc398_e で、要件（1 問以上）は満たす。足すなら次の候補（研究の表にあり、台帳での状態は未確認）。
- tessoku_book_af｜A 個か B 個取れる石取りの勝敗を、石の数ごとの勝ち負けの DP で求める｜練習（dp_k と同じ型なので、どちらか一方でもよい）｜https://github.com/E869120/kyopro-tessoku/blob/main/codes/cpp/chap05/answer_A32.cpp
- abc244_c｜1〜2N+1 を交互に言うゲームをジャッジと行い、まだ言われていない数を答え続ける｜練習（インタラクティブの節の入門。diff 165 と易しい）｜https://drken1215.hatenablog.com/entry/2025/02/08/111105
- arc143_c｜先手は X 個、後手は Y 個ずつ取る非対称なゲームを、X+Y で割った余りと相手の手を戻す戦略で判定する｜力試し（真似戦略・手番で手が違う節。nim-variants と分け合う）｜https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2022/0626_arc143#c_-_piles_of_pebbles
- agc033_c｜木のコイン取りの勝敗が直径の長さを 3 で割った余りで決まることを示す｜力試し（総手数・不変量の節。ただし偶奇でなく mod 3 の規則の発見で、grundy-patterns 寄り）｜https://drken1215.hatenablog.com/entry/2019/05/07/005700

### gcd-lcm

- abc148_c（C. Snack、diff 63）｜2 数の lcm（割ってから掛ける）。最も易しい lcm の練習｜練習（先頭）｜https://drken1215.hatenablog.com/entry/2019/12/22/224100_2 （research/06 §5.4 で確認済みとされる。台帳には未登録）
- typical90_al（038. Large LCM（★3））｜2 数の lcm が 10^18 を超えるかを判定し、超えなければ出力する。#lcm-overflow の型そのもの｜練習（台帳では integer-division の練習。gcd-lcm にも練習として足す）｜https://github.com/E869120/kyopro_educational_90/blob/main/sol/038.cpp ・ https://drken1215.hatenablog.com/entry/2023/11/21/020301 （台帳の evidence）
- abc118_c（C. Monsters Battle Royale、diff 646）｜攻撃し合って残る体力の最小値が全体の gcd になる（互除法の操作そのもの）｜練習（台帳では proof-patterns の例題）｜https://drken1215.hatenablog.com/entry/2019/02/16/224200 （台帳の evidence）
- abc248_e（E. K-colinear Line、diff 1292）｜K 点以上を通る直線の数（直線を既約な整数の組で表す）。#reduce-fraction（水）の練習｜練習（台帳では geometry-precision の練習）｜https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2022/0416_abc248 （台帳の evidence）
- abc148_c 以外は台帳で確認済みで、ページの割り当て（pages）に gcd-lcm を足すだけでよい。abc319 以降で gcd-lcm を直接使う問題は見つけていない（frequency_evidence の abc460_e は台帳の approach が桁ごとの式変形で、このページの例にはしなかった）。

### geometric-series-mod

- 現状で例題 1・練習 2・力試し 1 で、手引きの数の目安の範囲内なので探していない
- abc319 以降の問題が無い（基礎のページなので必須ではない）。必要なら次のバッチで「法が入力の等比数列の和」「同じ数字列を並べた数」の形を ap.py と第三者の解説で探す

### geometry-precision

- 台帳で足りているので追加の候補はなし。参考までに、research/08 の表で geometry-vectors の例題になっている abc181_c・abc224_c は、このページの練習には入れていない（易しすぎ、外積の基本のため）

### geometry-vectors

- 確認済みの問題で、例題 1・練習 4・力試し 3 がそろっているので、補充は必須ではない。基礎の練習に abc319 以降の問題がない（abc361_b だけ）ので、余力があれば ap.py と第三者の解説で abc319 以降の外積・ccw の易しい問題を探すとよい（今回は探していない）。

### global-offset

- abc389_c（C. Snake Queue、diff 255、ap.py で実在を確認、台帳になし）：蛇の列の末尾への追加・先頭の蛇が抜ける・K 番目の蛇の頭の座標を答えるクエリを処理する。追加時の座標を保存し、抜けた蛇の長さの合計をオフセットとして引く。abc319 以降の問題で、オフセットの節の練習の最初の 1 問に合う。裏付け：https://merom686.hatenablog.com/entry/2025/01/19/020250 、https://zenn.dev/shinonome81/articles/b1de75b0849b32 （research/05-ds の付録の候補にもある）

### graph-basics

- 練習が 1 問なので、表現そのものを問う問題を 2 つ挙げる（どちらも ap.py で実在と題名・difficulty を確認、台帳には書いていない）。
- abc276_b（B. Adjacency List、diff 143）：都市と道路の組から、各都市につながる都市の個数と番号を昇順に出力する。辺リストから隣接リストを両方向に作り、ソートする。裏付け：https://qiita.com/sano192/items/298c551f0e63c9c93260
- abc343_b（B. Adjacency Matrix、diff 53）：N×N の 0/1 の隣接行列から、各頂点につながる頂点の番号を昇順に出力する。行ごとに 1 の列を拾う（隣接行列 → 隣接リストの変換）。裏付け：https://www.cnblogs.com/Lanly/p/18058486
- どちらも灰色の B 問題で易しい。役割は practice を想定（並びは abc343_b → abc276_b → abc284_c）

### greedy-basics

- catalog の数（例題 1・練習 2）は手引きの目安の下限。次の候補で練習を足せる。
- abc473_e（K-Divisible Subarrays、966、台帳では prefix-sum-counting の練習・確認済み）：数列から重ならない連続部分列を選び、和が K の倍数のものを最大いくつ選べるか。累積和 mod K を見て、条件を満たす区間ができたら最も早く閉じる貪欲（最初の区間を早く終わる区間に入れ替えても悪くならない、の交換論法）。このページの proof の節の練習として合う｜https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2026/0829_abc473（解説の部分）
- abc141_d（Powerful Discount Tickets、823、台帳では greedy-priority-queue の練習・確認済み）：毎回最も高い商品に券を使う。「1 回ごとに最大を選ぶ」サインの易しい代表で、ここから greedy-priority-queue へつなげられる｜https://drken1215.hatenablog.com/entry/2019/09/16/032000（台帳の evidence。私は開いていない）

### greedy-priority-queue

- catalog の練習は 3 問で、力試しがない。後悔付き貪欲の節（#regret）と時刻を飛ばす節に問題がない。どれも `python3 tools/ap.py show` で実在と difficulty を確かめた。
- abc216_e｜1084｜乗るたびに楽しさが 1 減るアトラクションに合計 K 回まで乗るときの、楽しさの合計の最大値（同じ値をまとめて処理する。#take-max）｜練習（台帳では greedy-basics の練習。こちらにも足す）｜https://blog.hamayanhamayan.com/entry/2021/08/29/231101（台帳の evidence）
- abc249_f｜1786｜代入と加算の操作の列から K 個まで無視できるとき、最後の値の最大（後ろから見て、最後に残す代入を固定し、無視する負の加算の小さい K 個をヒープで保つ。#fix-max-keep-k の応用）｜力試し｜https://oraclesqlpuzzle.ninja-web.net/kyoupro/05-atcoder-02-abc/kyoupro-abc249-f.html
- abc214_e｜1835｜各ボールを区間 [L, R] の中の別々の箱に入れられるかの判定（時刻順に入れて締め切りの早いものから処理し、時刻を飛ばす。#earliest-deadline）｜力試し（台帳では priority-queue の練習。こちらにも足す）｜台帳の evidence（scrapbox.io/procon-kirokuyou の記事）。今回は開いていないので、使うなら検証役が読むこと
- abc250_g｜2219｜各日に株を 1 株買う・売る・何もしないのどれかを選ぶときの利益の最大（価格を 2 回入れて売りを取り消す後悔付き貪欲。#regret）｜力試し（黄なので、alien-dp の練習に回す案もある）｜https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2022/0508_abc250（記録の筆者は「正当性は未証明」と書いている）

### grid-graph

- どれも台帳に確認済みで別のページに載っている問題。このページへの追加は役割の追加になる。
- abc151_d（D. Maze Master、diff 959）：迷路の 2 マス間の最短距離の最大値を求める。H, W ≤ 20 なので全マスから BFS する。本文の neighbors の確認問題と同じ型。現在 bfs の練習。裏付け：https://blog.hamayanhamayan.com/entry/2020/01/12/225950 （research/03-graph の表。今回は読んでいない）
- abc407_g（G. Domino Covering SUM、diff 2190）：ドミノの配置を市松模様の二部グラフにして最小費用流で解く。checkerboard の節の力試しに向く（現在 min-cost-flow の練習）。裏付け：https://kmjp.hatenablog.jp/entry/2025/05/27/0900 （research/03-graph の表。今回は読んでいない）
- abc193_f（F. Zebraness、diff 2475）：市松模様で片側の色を反転して最小カットにする。checkerboard の節の「燃やす埋める」の 1 文の実例。発展の難しさなので本文で型として触れるだけでもよい（現在 project-selection の練習）。裏付け：https://kmjp.hatenablog.jp/entry/2021/02/27/1000
- 止まるマス（boundary-cells）の節は abc351_d が練習にあるだけで、ABC の新しい回（abc400 以降）の例がない。research の §5.3 の未確認の候補から探す価値がある
- （対応の節）- 4（市松模様の用語）：(a)(b) は提案どおり直した。(c) は後半の 1 文を消し、「片方の色のマスだけ値の 0 と 1 の意味を入れ替えると、燃やす埋める（最小カット）で扱える形になることがある」と具体化した。abc193_f は台帳の役割の追加になるので、本文には入れず「問題の補充の候補」のままにした

### harmonic-sum

- abc206_e（E. Divide Both、diff 1745、ap.py で確認）｜L 以上 R 以下の組 (x, y) で、gcd が 1 でも x・y 自身でもないものの個数。gcd を固定して倍数の個数から数え、大きい順に引く（本文の「倍数の箱を後ろから決める」の gcd の例と同じ形）｜練習（divisor-inclusion-exclusion の例題と重なるなら練習の参照だけ）｜https://drken1215.hatenablog.com/entry/2021/06/25/121800 （research/01 §5 の記載。今回は記事を開いていない）
- abc177_e（E. Coprime、diff 1057）｜pairwise coprime の判定を「各 d ≥ 2 で d の倍数である要素が 2 個以上あるか」で倍数を回して調べる。spf-sieve の例題なので、ここでは練習か本文の参照｜練習｜https://drken1215.hatenablog.com/entry/2020/10/31/203300 （research/01 §5 の記載。今回は開いていない）
- abc319 以降の水の問題は abc393_e（例題）と abc469_f（練習）で、手引き §10 の目安は満たしている。

### hashing-for-sets

- 例題 2・練習 2・力試し 1 で手引きの数の目安を満たすので、新しい候補は探していない。練習を増やすなら「区間の各値が偶数個」（XOR の累積）を問う ABC の E・F を探すとよい。

### imos

- abc035_c（C. オセロ、diff 1096 参考値。台帳にない）：一列の駒の閉区間をくり返し裏返した後の、各駒の色を求める。裏返した回数の偶奇をいもす法で求める（range-flip 節の基本形として練習に向く）。裏付け：https://programming-hiroba.com/abc035-c/
- abc408_c（C. Not All Covered、diff 223。台帳にない）：閉区間への +1 を M 回まとめて行った後の最小値を求める。閉区間の右端 + 1 に −1 を置く基本形。abc319 以降。裏付け：https://qiita.com/t_j_/items/acac189e688d01a5ee69
- abc188_d（台帳で確認済み、event-sort の練習）：座標が大きいときのイベントのソートの練習として、このページにも practice で足してよい（large-coordinates 節）

### integer-division

- abc345_b（B. Integer Division Returns、diff 91、ap.py で実在を確認）：$-10^{18} \le X \le 10^{18}$ の整数 X について ⌈X/10⌉ を求める。例題の abc239_b と対になる切り上げの版で、`(X + 9) / 10` が負の X で誤ることを確かめる練習になる。裏付け：https://fkgtinfo.com/2024/03/17/abc345/ （問いと制約）、https://zenn.dev/yamasakit/articles/b40cc269f80b1b （切り上げの式。ただし Python の // なので負の数は自動で正しい）
- typical90_t（020. Log Inequality（★3）、ap.py で実在を確認）：$\log_2 a < b \log_2 c$ を判定する。整数の $a < c^b$ に直して誤差を避ける（[double で割らない](#no-double)の節の練習）。裏付け：https://github.com/E869120/kyopro_educational_90/blob/main/sol/020.cpp （research/06 で確認済み）、https://ryo-manba.hatenablog.com/entry/2021/08/25/225307
- abc319 以降の問題は、基礎のページの要件でないため探していない（練習のうち abc432_c が 2025 年）

### integer-root

- **panasonic2020_c**（C. Sqrt Inequality、diff 701、ap.py で実在を確認）：正の整数 a, b, c（≤ 10^9）について √a + √b < √c かを判定する。c − a − b の符号を見てから 2 乗し、4ab < (c − a − b)² を整数で比べる。本文の [√ を含む式の大小を整数で比べる](#compare-sqrt) 節の例にちょうど合う（今は台帳にないので問題 ID を出さずに型だけ書いた）。役割は practice（基礎のページの例題は 1 問なので）。裏付け：https://at274.hatenablog.com/entry/2020/03/15/122125 （問い・制約・式変形）、https://qiita.com/shun310/items/6bb8bde789a6f2d9ee47 （検索結果の要約で同じ変形を確認。本文は読んでいない）
- abc420_g（G. sqrt(n²+n+X)、diff 1427、ap.py で実在を確認）：題名から平方数の判定に関わる問題と思われるが、第三者の解説で問いを確かめていない。候補の手掛かりとしてだけ挙げる
- abc319 以降の問題は abc400_c（例題）だけ。基礎のページの要件ではないので深くは探していない

### interactive

- abc019_4（台帳にあり・確認済み、ページの割り当ては interactive にない）｜距離の質問で木の直径を求める（2 回の探索、2(N−1) 回の質問）｜https://drken1215.hatenablog.com/entry/2021/06/14/001500（研究 08 の表）。本文の「未知のグラフを探索する」で問題 ID を出さずに型だけ書いた。interactive の練習（または tree-diameter の練習）として pages に足すことを提案する。difficulty 1378（参考値）
- 水・青の帯に abc319 以降の問題が 2 問（abc337_e・abc355_e）しかない。直近のインタラクティブ問題は ap.py で題名から探しきれなかったので、メインのバッチで候補を探してほしい

### interval-scheduling

- catalog の練習は 2 問で、「重ならない区間の最大個数」そのものを問う問題が台帳にない（例題は串刺しの型、練習の 1 問は構築）。次の候補を練習に足すことを提案する。
- keyence2020_b｜B. Robot Arms（ap.py：diff 889、2020-01-18）｜位置 X と腕の長さ L のロボットから、腕の範囲 (X−L, X+L) が重ならないように残せる最大の台数を求める。区間に直して右端の順に選ぶ区間スケジューリングそのもの｜https://qiita.com/Nary_/items/ba86d70dd9876106ee85 （区間に直して終点でソートする貪欲。端点が接するのを許すかは記事では問題文の画像だけで明記がなく、コードは接するのを許す扱い。本文に入れる前に、端点の扱いを別の解説でも確かめたい）
- abc325_d（台帳では greedy-priority-queue の例題）は、このページでは「処理時間と締め切り」の節で型として触れただけで、問題 ID は出していない

### interval-set

- abc478_d（D. Range Set Insertion Query、diff 729、台帳では event-sort の練習で summary が未確定）：区間に値を入れる操作の後、各位置にある値の種類数を求める。値ごとに区間をまとめて重複を除いてからいもす法で数える型で、このページの「覆われた区間だけを持つ形」の練習に使える。裏付け：https://qiita.com/tototti/items/1915baced8ce575d28b2（research/05-ds 付録 A、確度 medium。今回は読んでいない）
- abc319 以降の水の E で、区間を set で管理する問題を ap.py と解説で探すのは今回できていない。例題の abc435_e・abc380_e がどちらも abc319 以降なので、要件（水のページに 1 問以上）は満たしている

### invariant

- なし（例題 3・練習 2 で目安を満たす）。abc319 以降の問題は recent 0 で見つけていない。「添字を K で割った余りごとにソートする」「1 行目を全探索すると残りが決まる」の型は本文で問題 ID を出さずに書いたので、台帳に確認済みの問題があれば練習に足せる

### inversion-number

- typical90_ck（089. Partitions and Inversions（★7）、diff なし。台帳にない）：各部分の転倒数が K 以下になる列の分割の数を求める。尺取り＋BIT で各右端の左端の限界を求め、累積和で DP する（sliding-window 節の発展の練習）。裏付け：https://emtubasa.hateblo.jp/entry/2021/07/11/192251 （research/05-ds の記録。今回は開いておらず、ドメインの noai も未確認）
- arc101_b（D. Median of Medians、diff 2073。台帳にない）：すべての連続区間の中央値を集めた列の中央値を求める。答えを二分探索し、±1 の累積和の大小の組を BIT で数える（reformulation 節の力試し）。裏付け：https://drken1215.hatenablog.com/entry/2018/09/08/011500 （research の記録。今回は開いていない）
- typical90_q（017. Crossing Segments（★7）、diff なし。台帳にない）：円周上の点を結ぶ線分のうち交差する組の数を数える。端点でソートし BIT で数える（転倒数型の数え上げ）。裏付け：https://kaage.hatenablog.com/entry/2021/04/21/235030 （research の記録。今回は開いておらず、ドメインの noai も未確認）
- abc319 以降の水の練習が abc378_e・abc396_f の 2 問で、どちらも差分・言い換えの型。BIT で数えるだけの易しい abc319 以降の問題があれば足したいが、今回は ap.py の題名検索だけでは見つけられなかった

### kmp

- 照合オートマトンをそのまま使う青の練習（KMP の表の DP）を探したが、ABC で 1 パターンの KMP オートマトンだけで解ける問題を第三者の解説で裏付けられなかった。候補の abc305_g・abc419_f・abc458_f は複数パターン（Aho-Corasick）なので string-automaton-dp・aho-corasick に任せる
- abc319 以降（7 問体制）の問題がこのページにない（例題・練習はすべて古い ABC か ARC）。水・青のページには 1 問以上という目安を満たしていない。border の連鎖・周期を問う新しい ABC の候補を見つけられなかった（drken の KMP 法のカテゴリは abc150_f・arc060_d と Codeforces の 1 問だけ）

### knapsack-01

- arc073_b（D. Simple Knapsack、diff 1477）｜重さが w_1〜w_1 + 3 の 4 種類しかない 0-1 ナップサック。重さごとに価値の降順の累積和を作り、何個取るかを全探索（O(N^4)）。「計算量で解法を切り替える」節の 4 行目（重さの種類が少ない）の代表。練習（水の節）向き｜https://drken1215.hatenablog.com/entry/2024/10/19/042434
- abc289_d（D. Step Up Robot、diff 551）｜決まった歩幅を何度でも使い、罠の段を避けてちょうど X 段に着けるかの可否 DP。個数制限なしの易しい練習｜https://kazun-kyopro.hatenablog.com/entry/ABC/289/D
- abc054_d（D. Mixing Experiment、diff 1655）｜2 種の薬品の量を状態にした費用の最小（2 次元のナップサック）。調査レポート 02 §5.1 の候補。今回は解説を読んでいない｜https://drken1215.hatenablog.com/entry/2019/02/15/205900

### kth-element

- catalog の problems_note のとおり、水の帯で手法をそのまま使う ABC の例題（abc319 以降）がない。ap.py の題名検索（K-th・Kth・Insert・Query など）と Web 検索で探したが、BIT 上の二分探索が主役の abc319 以降の問題は見つからなかった。
- abc364_d（diff 1136）｜数直線上の点 B_j ごとに、点の集合 A のうち k_j 番目に近い点までの距離を答える｜https://junkobayashi.hatenablog.com/entry/2024/07/28/030800（noai の指定なしを確かめた）｜集合は固定で、距離の答えの二分探索と lower_bound で数える型。このページより kth-value（または vs-kth-value の対比の練習）向き。基礎の帯
- メインで、abc319 以降の「追加・削除と K 番目」「空きの K 番目」の問題を第三者の解説から探す必要がある。

### lattice-paths

- abc034_c（C. 経路、diff 1440 参考値。ap.py で確認）：H×W のグリッドの左上から右下へ、右と下だけで進む経路の数を法 10^9+7 で求める。障害物のない基本形そのもので、ABC145 D の前の練習として易しい側に置ける。裏付け：https://qiita.com/2yuu/items/35617e56e1794d33c22b 、https://qiita.com/tiaki73/items/43f222d75da0e6a66426
- abc319 以降の格子路の問題は見つけていない（frequency_evidence も recent 0）

### lca

- abc460_f（台帳にあり、確認済み）｜頂点の白黒の切り替えのたびに、黒い頂点どうしの距離の最大を答える。セグ木の合成で 2 点間の距離を何度も求めるので、LCA（特に O(1) の方式）が要る｜https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2026/0530_abc460
- typical90_ai（台帳にあり、確認済み）｜指定された頂点をすべてつなぐのに要る辺の最小数を多数の質問で答える。行きがけ順に並べた隣どうしの距離を LCA で求める｜https://github.com/E869120/kyopro_educational_90/blob/main/sol/035-04.cpp

### lcs

- abc386_f（F. Operate K、diff 1875、青）｜文字列 S を K 回以下の挿入・削除・置換で T にできるか（K ≤ 20、長さは 5×10^5 まで）。編集距離が K 以下かの判定で、|i − j| ≤ K の帯だけを埋める｜https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2024/1228_abc386 （ikatakos 氏の記録は解説の部分だけを使うこと）、https://www.tunamaguro.dev/articles/2024/12/abc386/ （新しいドメイン。check_noai は未実施）。役割は練習か力試し。abc319 以降の水〜青の LCS 型がないという catalog の見立てを補える。本文の編集距離の節には、問題 ID を出さずに「距離が K 以下かだけを問われたら帯だけを埋める」という型を書いた
- 検索の結果：ap.py で LCS・Edit・Subsequence・Common・Palindrome・Distance を abc の diff 1000 以上で探したが、ほかに LCS の表を直接使う abc319 以降の問題は見つからなかった（abc377_g Edit to Match は Trie の問題）

### leaf-first

- abc333_d（diff 704、確認済み・tree-traversal の練習）｜練習｜葉を 1 つずつ消す操作で頂点 1 を消すまでの最小の回数（サイン「葉を消していく操作」の代表。易しいので練習の 1 問目）｜https://drken1215.hatenablog.com/entry/2024/11/02/192645 （drken のカテゴリ「葉から考える」に入っている）
- agc014_d（diff 2266、台帳にあり）｜力試し｜2 人が交互に木の頂点を塗るゲームの勝敗。木に完全マッチングがあるかに帰着し、葉から貪欲にマッチングを作ってキューで判定する（木の最大マッチングの節の応用）｜https://drken1215.hatenablog.com/entry/2019/05/30/021200 、https://blog.hamayanhamayan.com/entry/2017/05/06/232930
- 練習は今も 0 問である。水の帯の ABC で葉から決める問題は、ap.py の題名の検索と drken のカテゴリ（17 件。AtCoder の ABC は 333 D・359 F・282 E だけで、359 F・282 E は青で別の手法が主役）では見つからなかった。

### lexicographic-greedy

- 確認済みの問題で役割の数（例題 1・練習 4・力試し 1）は足りているので、補充は必須ではない。frequency_evidence が recent 0 なので、abc319 以降の「辞書順最小を出力」の型があれば足したい（今回は探していない）
- 候補（research/08 §5 にあり、台帳で未確認なら確かめが要る）： - abc225_f｜K 枚を選んで連結した辞書順最小。a+b < b+a で並べた後に後ろから DP（前からの貪欲だけでは誤る）。exchange-argument か本ページの青の節の力試し向き｜https://merom686.hatenablog.com/entry/2021/10/30/235859 - arc081_c｜部分列でない最短の文字列の辞書順最小。次の出現位置の表で後ろから DP し、前から貪欲に復元する。本ページの「判定が重い型（後ろからの DP で判定の表を作る）」の例に合う｜https://drken1215.hatenablog.com/entry/2018/09/22/201000

### linked-list

- abc225_d（D. Play Train、diff 778）｜電車の連結・切り離しと、ある電車を含む編成を前から出力する質問（出力の総数 ≤ 10^6）。前後の電車を配列で持ち、質問では先頭まで戻ってからたどる｜練習（「列車の連結・切り離し」のサインの代表。本文の付け替えの節と「途中で x を含む列を出力」の段落にそのまま当たる）｜https://kazun-kyopro.hatenablog.com/entry/ABC/225/D
- ap.py で実在と diff を確認した（`OK abc225_d D. Play Train diff=778 茶/基礎`）
- 削除だけの列で「消す時点の左右の生き残り」を使う型（本文の「上位の手法とのつながり」）の例として abc140_e（Second Sum）を考えたが、連結リストで解く第三者の解説が見つからなかった（kmjp・ARMERIA・maspypy などは set・BIT）。提案しない

### lis

- abc038_d（D. プレゼント、diff 1804 参考値）：箱を幅と高さがともに狭義に大きい箱へ入れていくとき、入れ子にできる箱の個数の最大を求める。節 nesting の代表（幅の昇順・同じ幅は高さの降順に並べて高さの狭義 LIS）。https://scrapbox.io/wafuwafualgorithm/ABC038_D_-_%E3%83%97%E3%83%AC%E3%82%BC%E3%83%B3%E3%83%88（noai の指定なしを確認済み）。tdpc_target より易しく、入れ子の練習に向く
- abc468_f（F. Chmax、diff 1693）：2 つの変数に値を順に入れていき、入れる先の値より大きいと得点が入るとき、得点の最大を求める。前から最大値を更新する要素の個数と、それを除いた列の LIS の和になる（LIS の発展）。https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2026/0725_abc468。frequency_evidence に名前があるのに catalog の problems にないので、練習に足す案（abc319 以降の水〜青の問題で、ページの水の根拠にもなりうる）
- abc369_f（F. Gather Coins、diff 1618、台帳で確認済み・dp-reconstruction と dp-grid の練習）：節 restore の練習として lis にも載せる案（コインの位置で LIS 型の DP をし、直前を記録して経路を復元する）。https://torus711.hatenablog.com/entry/2024/09/01/181216。本文では問題 ID を出さず型だけに触れた

### manhattan-chebyshev

- typical90_aj（036. Max Manhattan Distance（★5）、diff なし）：N 点と Q 個の問いで、指定した点から最も遠い点までのマンハッタン距離を答える。x+y と x−y の最大・最小の 4 通りの差。最遠点対の節の「ある点から最も遠い点」の練習によい（role 案：practice）｜https://github.com/E869120/kyopro_educational_90/blob/main/sol/036.cpp （research 08 §に記載。今回は開いていない）
- abc127_e（E. Cell Distance、diff 1938）：グリッドから K マスを選ぶすべての選び方について、選んだマスの全ペアのマンハッタン距離の和の総和を求める。x と y を独立にして、差 d ごとの寄与を数える（role 案：practice。axis-independence）｜research 08 §1081 付近に記載。今回は裏付けの解説を開いていないので、追加するなら第三者の解説で確かめが要る
- arc103_b（D. Robot Arms、diff 2677）：発展。45 度回転で 2 軸を独立にして 2 の冪の腕で構成する。水のページには難しすぎるので、載せるなら challenge か advanced-geometry 側（https://drken1215.hatenablog.com/entry/2018/09/30/002900、research に記載。今回は開いていない）

### matrix-power

- catalog の数（例題 3・練習 6・力試し 2）で足りている。frequency_evidence にある最近の問題で、ページに載っていないものを挙げる（どれも台帳にない・未確認）。
- abc469_g（G. K-nacci Operations、diff 2804・発展。ap.py で実在を確かめた）：frequency_evidence に挙がっているが、問いと解法は第三者の解説で確かめていない。発展の帯なので、このページより linear-recurrence-fast の候補かもしれない
- abc293_e（E. Geometric Progression、diff 1453・水。ap.py で確かめた）：台帳では geometric-series-mod の練習。2×2 の行列の累乗でも解ける別解として、このページの練習か本文の参照にできる（研究 06 §7.2 の記述。第三者の解説での裏付けは geometric-series-mod の台帳の evidence を使える見込み）
- abc129_f（F. Takahashi's Basics in Education and Learning、diff 2621・発展。ap.py で確かめた）：桁数ごとに 3×3 の行列を累乗する型（研究 06 §4.6）。台帳では geometric-series-mod の力試し。本文の合成の節の「周期のある遷移」に近い
- abc236_g（G. Good Vertices、diff 2438）：(max,min) の行列のダブリングの代表。研究 06 §7.5 で未確認とされていて、本文では問題 ID を出さず「ボトルネック」の型だけを書いた。第三者の解説で確かめられれば、半環の節の力試しの候補

### median-absolute

- nikkei2019_final_c（全国統一プログラミング王決定戦本選 C. Come Together、diff なし）：グリッドの全マスのコマから K 個を除き、残りを 1 マスに集める上下左右の移動回数の最小を求める。行と列に分け、各座標のコマの数を重みにした重み付き中央値を取る。練習に向く（even-count の重み付き中央値と separate-axes の両方を使う）。裏付け：https://drken1215.hatenablog.com/entry/2019/02/18/173100

### meet-in-the-middle

- 水・青のページには abc319 以降の問題を 1 問以上（手引き §10）とあるが、今は力試しの abc464_f（2225）だけ。次を候補にする。
- abc326_f（F. Robot Rotation、diff 1870、ap.py で確認）｜練習｜「回るたびに 90 度向きを変えながら進むロボットで、各移動の左右の回り方を選んで点 (X, Y) に着けるか判定し、着けるなら回り方を 1 つ出力する。」移動は x 軸と y 軸に交互に効くので、x と y の問題に分け、それぞれ ± の符号の選び方を半分全列挙で突き合わせ、選び方を復元する｜裏付け：https://www.cnblogs.com/RainPPR/p/solution-at-abc326-f.html（check_noai で指定なし）。atcoder-tags の「半分全列挙」にも載る（https://atcoder-tags.herokuapp.com/tags/Technique/Split-And-List）。制約（N ≤ 80 など）は解説から確かめきれていない
- abc336_f（Rotation Puzzle、diff 2018、atcoder-tags で半分全列挙）｜力試し（両側探索）の候補。第三者の解説はまだ見つけていない（未確認）
- 古い問題（atcoder-tags の同じタグ）：abc018_4 バレンタインデー（1711）・arc017_3 無駄なものが嫌いな人（1625）。どちらも未確認。典型 90 051 の類題としてリンク集（dvoraker3）にも載る

### memoized-recursion

- 台帳への追加はしていない。ap.py での確認はしていない（研究ノート 02-dp.md の候補をそのまま挙げる）ので、追加の前に ap.py と解説で確かめてほしい。
- abc037_d｜グリッドで隣の値が大きいマスへだけ進む経路の総数を求める（値の大小が DAG を作り、計算順序が添字の順でない）｜https://qiita.com/drken/items/03c7db44ccd27820ea0d（研究ノート 02-dp.md §5.3。difficulty は参考値 1377）
- abc184_d・abc201_d｜研究ノート §3 の level_evidence に「計算順が自明でない・メモ化が楽」の例として名前だけある。題材は未確認

### minimax

- 水のページに要る abc319 以降の問題は、練習の abc349_e（diff 1464）で満たしている。追加の候補は探していない
- [木の上のゲーム](../../../docs/comb/minimax.md) の節には、易しい（青までの）練習がない。木を降りるゲームで終局の値を max・min で決めるだけの易しい問題が見つかれば、練習に足したい（今回は探していない）

### minimum-spanning-tree

- 確認済みの問題で足りたので、補充の候補はない。参考までに、research/03 §4.E にある abc328_e（N ≤ 8 の全域木の全列挙）は small-graph-brute-force の担当と考え、このページには載せていない。

### mod-arithmetic

- abc266_b（B. Modulo Number、diff 95、ap.py で確認済み）：|N| ≤ 10^18 の負もありうる N について、N − x が 998244353 の倍数になる 0 以上 998244353 未満の x を求める。C++ の % は負の余りを返すので、MOD を足して直す（[引き算の後の負の数を 0 以上に直す](#negative) の練習） - 裏付け：https://kazun-kyopro.hatenablog.com/entry/ABC/266/B ・ https://oraclesqlpuzzle.ninja-web.net/kyoupro/05-atcoder-02-abc/kyoupro-abc266-b.html （どちらも付録 B のドメイン。記事の本文はまだ読んでおらず、検索結果の要約で問いを確かめただけ） - 役割の案：practice（例題 abc275_b より易しいが、負の数の直しだけを問う最小の問題なので、練習の先頭に置く）

### mod-inverse

- 足りているので新しい候補は探していない（例題 1：typical90_cd、練習 3：math_and_algorithm_as・abc357_d・abc186_e）
- 参考：frequency_evidence に挙がっている abc468_e（E. Sum of Average、diff 1038、ap.py で実在を確認）は台帳では contribution の練習で、summary が「（執筆時に確かめる）」のまま。本ページには載せていない。平均（割り算）を mod で求める問題なら本ページの練習にも向くが、問いを第三者の解説で確かめていない

### mod-pow

- math_and_algorithm_aq（アルゴ数学 050. Power）｜a^b を 10^9+7 で割った余り（繰り返し二乗法をそのまま使う入門）｜https://github.com/E869120/math-algorithm-book （4.6 節の解答のフォルダ。問題との対応は未確認）｜未確認。ap.py で実在のみ確認。問いの裏付けは取れていないので、確かめてから練習の先頭に置く候補

### modint

- 例題は catalog の problems_note のとおり置かず、練習 2 問（abc357_d・abc281_g）だけにした。基礎のページとしては練習が少ないが、mod の数え上げの練習は comb のページに任せる方針なので、無理に足さない。足すなら次の型が合う（ap.py と第三者の解説の確認はまだ）。
- 法が入力で与えられる易しい数え上げ（dynamic_modint の set_mod の練習）。水以下の ABC で探す価値がある
- 「方法がなければ -1」と mod の数え上げが同時に出る問題（到達可能性を別に持つ落とし穴の練習）

### monotonic-stack

- abc407_f（F. Sums of Sliding Window Maximum、diff 1740、ap.py で実在を確認、台帳になし）：長さ N の列について、窓の幅 k = 1..N ごとに、幅 k のすべての窓の最大値の和を求める。各要素が最大になる範囲（左右で初めて大きい位置。同じ値は片側 ≤）を求め、窓の幅ごとの個数が台形になるので 2 階の差分で足す。範囲は単調スタックでも set でも求まる。contribution の節の練習（青）に向く。裏付け：https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2025/0524_abc407 （ikatakos は set で範囲を求めている。単調スタックで書けることは同じ範囲を求めるだけなので自明だが、第三者の記述は未確認）
- abc379_f（F. Buildings 2、diff 1659、ap.py で実在を確認、台帳になし）：research/05-ds では確度 medium（解法の細部は未確認）。見えるビルの数の応用（右から単調スタックを作りながらクエリをオフラインで処理し、スタックの上を二分探索）。第三者の解説での裏付けがまだないので、使うなら解説を探してほしい
- abc334_f（F. Christmas Present 2、diff 1813、ap.py で実在を確認）：research/02-dp で dp-sliding-window の候補（確度 low・裏付け未取得）。直前 K 個の最小値で決まる DP の遷移の例題として dp-transition の節に欲しい。本文では問題 ID を出さず、型だけを書いた

### multinomial-coefficient

- 練習は 2 問（abc470_f・abc266_g）、力試し 1 問で目安の範囲内。補充は必須ではないので探していない。水の帯の練習（abc319 以降、diff 1200〜1700 で多項係数をそのまま使う E）があれば足したいが、裏付けまでは取っていない

### namori-graph

- catalog の problems_note のとおり、練習が 1 問（abc292_d、diff 579 で基礎の帯）で abc319 以降の問題がない。
- abc378_f（F. Add One Edge 2、diff 1436）：木に辺を 1 本足してできるグラフのうち、閉路の頂点の次数がすべて 3 になるものの数を数える。次数 3 の頂点の成分ごとに、隣の次数 2 の頂点から 2 つ選ぶ。台帳では tree-basics の練習。なもりグラフの「木＋1 辺で閉路がちょうど 1 つ」の練習としても使える（abc319 以降）。裏付け：https://drken1215.hatenablog.com/entry/2024/11/04/002341
- abc235_e（E. MST + 1、diff 1304）：最小全域木に辺を 1 本足すとできる閉路の最大の辺と比べる。台帳では minimum-spanning-tree の例題。research/04 §5.1 がなもりの練習に挙げている。裏付け：https://kazun-kyopro.hatenablog.com/entry/ABC/235/E
- jsc2019_qual_e（E. Card Collector、diff 2691）：drken 氏のカテゴリ「なもりグラフ」にある（各成分が辺 ≤ 頂点、すなわち木かなもりになる条件で選ぶ）。発展の帯なので力試しにも重い。記事 https://drken1215.hatenablog.com/entry/2019/09/27/185400 は未読で、問いは確かめていない

### nim

- 練習が arc143_c の 1 問で、目安（2〜6）に足りない。ap.py の search Nim で見つけた候補（裏付けの解説はまだ読んでいない。台帳には未登録か未確認）：
- arc105_d（D. Let's Play Nim、diff 1871）：袋から皿へ硬貨を移してから Nim をするゲームの勝敗。真似戦略と Nim の組合せと見られる（research の game-mirror-strategy にも挙がる）。裏付けの URL は未確認（第三者の解説を探す必要がある）
- arc091_d（F. Strange Nim、diff 2395）：取れる個数が山ごとに決まる変種で、Grundy 数の周期を求める型と見られる。grundy-number の力試し向き。裏付けの URL は未確認
- abc319 以降の ABC で Nim そのものの問題は ap.py の題名検索では見つからなかった（catalog の problems_note と同じ）
- （対応の節）- 指摘 8（台帳・メイン）：ページ側では直さない。上の「問題の補充の候補」（arc105_d・arc091_d）の裏付けをメインが取るか、grundy-number と配分を決めてほしい

### offline-queries

- abc319 以降で、基本形の先読み（右端の順・しきい値の順）だけで解ける水の ABC を見つけられていない（level_evidence にもある既知の不足）。今回は探索に時間を使っていない
- abc106_d（ABC106 D. AtCoder Express 2、diff 1319）：区間とクエリを右端の順に並べ、BIT で左端を数える（2 時点の差・右端の順の入門）。台帳は確認済み（event-sort・sweep-line-2d の練習）。このページの練習に足す案｜https://drken1215.hatenablog.com/entry/2018/09/06/020200
- typical90_bp（典型90 068. Paired Information（★5））：クエリを先読みして Union-Find で関係の確定を判定する。台帳は確認済み（weighted-union-find の練習）。このページの練習に足す案｜https://enakai00.hatenablog.com/entry/2021/09/06/103720（このセッションでは記事を開いていない。research/05-ds §5 の記載による）
- abc287_g（ABC287 G. Balance Update Query、diff 2180）：得点を先読みして座標圧縮し、値を添字にした BIT で上位 X 枚の和を答える（compress の節の力試し）。台帳は確認済み（segment-tree-on-values の力試し）｜https://kmjp.hatenablog.jp/entry/2023/01/28/0900（このセッションでは開いていない）

### ordered-set

- abc302_e（E. Isolation、diff 988）｜辺の追加と、ある頂点の全辺の削除のたびに孤立点の数を答える｜隣接頂点を set で持ち、変わった分だけ数え直す（前後の要素ではなく set の削除の練習）｜https://drken1215.hatenablog.com/entry/2023/06/01/020700（research の値。今回は読んでいない）
- abc444_e（E. Sparse Range、diff 1107）｜どの 2 要素も差が D 以上である連続部分列の個数｜尺取り法で窓の値を順序付き集合に持ち、新しい値の前後が D 未満かを調べる｜https://inamori.hateblo.jp/entry/2026/02/09/194520（著者はセグ木で代用。set の解は別の第三者の解説で確かめる必要あり。確度 medium）
- abc260_d（D. Draw Your Cards、diff 1074）｜カードを場の山に重ね、K 枚で消える操作で各カードが消える時刻｜山の一番上の値を set で持ち upper_bound で置き先を探す｜research 付録 B（低確度）。第三者の解説で未確認
- パレート境界の節（水）に対応する確認済みの問題がない。ABC で「支配される点を消す map」を使う問題を探す必要がある

### palindrome

- code_festival_2017_qualc_c（Inserting 'x'、diff 975）｜文字列の好きな位置に x を挿入して回文にする最小の回数（できなければ −1）。両端から 2 つの添字を寄せる貪欲｜練習（外側から組み立てる・両端から作るの基礎の型）｜https://drken1215.hatenablog.com/entry/2020/02/19/093100
- abc363_d（Palindromic Number、diff 975）｜N 番目に小さい回文数。桁数ごとの個数を数え、前半の桁で決まることを使う（内容は記憶による。第三者の解説で未確認）｜練習の候補（裏付けを取ってから）｜未取得（ikatakos 0720_abc363 には D の節がない）
- abc175_f（Making Palindrome、diff 2512）｜文字列を左右に置いて回文を作る最小コスト。左右の余りを状態にした最短路｜力試し（発展帯なので載せるかは判断を任せる）｜https://drken1215.hatenablog.com/entry/2020/08/16/032500 （調査レポート §5 にある）

### parity

- abc125_d｜隣り合う 2 つの符号を同時に反転する操作をくり返したときの総和の最大。負の数の個数の偶奇が変わらないことから決まる（台帳では invariant の例題。parity では練習として）｜練習｜https://drken1215.hatenablog.com/entry/2019/04/27/224100
- abc136_d｜L/R に従って子どもが 10^100 回動いた後の人数。RL の境界ごとに、境界までの距離の偶奇で 2 か所に振り分ける（research 01 の表では「塊の長さの偶奇で振り分ける」）（台帳では run-length-encoding の練習。[exactly-k] の「回数が非常に大きいときは偶奇」の例）｜練習｜https://drken1215.hatenablog.com/entry/2020/12/29/190100
- abc319 以降で基礎〜水の偶奇の問題は見つけていない（catalog の level_evidence と同じ）。abc460_d（距離の偶奇、bfs の力試し）は bfs に置いたままでよい

### periodicity

- catalog の問題は 6 問すべて確認済みで足りている。補うなら次の候補（abc241_e・abc331_d は台帳で確認済みで、ほかのページの持ち物）。
- abc241_e（diff 1248）：皿の飴の個数の和 mod N を状態にする型（状態に将来を決める情報だけを入れる）。doubling の例題なので、このページでは練習として載せる候補。裏付け https://qiita.com/recuraki/items/e26c220f2bc01f58e185
- abc331_d（diff 1361）：周期的に敷き詰めた盤面の長方形の数え上げ。prefix-sum-2d の例題なので、このページの「盤面・剰余の周期」節の練習の候補。裏付け https://oraclesqlpuzzle.ninja-web.net/kyoupro/05-atcoder-02-abc/kyoupro-abc331-d.html
- abc300_f（diff 1846、台帳にない。ap.py で実在を確認。題名 F. More Holidays）：文字列を M 回繰り返した周期構造で開始位置を 1 周期分だけ試す。裏付け https://drken1215.hatenablog.com/entry/2023/05/03/002258（research/01-basics の表）

### permutation-cycles

- 練習 2・力試し 1 で目安（練習 2〜6）は満たしている。補充するなら次を探す価値がある（どれも問いと解き方の裏付けはまだ取っていない）。
- ap.py で題名に Swap・Permut を含む ABC を見たが、巡回分解が主役と確かめられたものはなかった。abc233_f（Swap and Sort、2038）は swap できる組が限られる問題で、巡回分解より連結成分・木の話が主役と思われるので、このページの候補にはしない
- 「任意の swap でソートする最小回数」そのもの（N − c）を問う易しい問題があれば練習の先頭に置きたい（ikatakos 氏によれば近年の ABC で頻出の題材なので、ABC の C〜E にある可能性が高い）

### prefix-sum-2d

- abc106_d｜M 本の区間のうち、クエリの区間 [p, q] に完全に含まれるものの数（端点 ≤ 500）｜練習（節 intervals-as-points の代表。台帳では event-sort・sweep-line-2d の練習）｜https://drken1215.hatenablog.com/entry/2018/09/06/020200 （r ≤ 500 なので 2 次元累積和が想定と記述）
- abc203_d｜N×N の池の K×K の区画の中央値の最小値（判定を 2 次元累積和で行う）｜練習（台帳では fractional-binary-search の例題。ここでは練習として参照）｜https://oraclesqlpuzzle.ninja-web.net/kyoupro/05-atcoder-02-abc/kyoupro-abc203-d.html
- 節 intervals-as-points は台帳に本ページの問題がないので、問題 ID を出さず型だけを書いた（手引き §13-6）。abc106_d を本ページの練習に足せば節と問題がそろう
- abc475_f（包除原理と 2 次元累積和、1916）は frequency_evidence に挙がっているが、台帳では inclusion-exclusion の練習で summary も未確認のため使わなかった

### prefix-sum-counting

- agc023_a｜A. Zero-Sum Ranges（diff 1038、ap.py で実在を確認）｜区間和が 0 の区間を数える（累積和が等しい組の数）｜https://drken1215.hatenablog.com/entry/2019/12/25/123932 （ただしこの記事の本文は Qiita の記事への案内だけで、問いの中身は記事からは確かめきれていない。research 01 §4.E の表に載っている）。練習の易しい側（abc233_d と abc473_e の間）か、確認問題「和が 0 の区間」の対応問題に向く。台帳に載れば aliases の「Zero-Sum Ranges」とも合う
- abc455_e（Unbalanced ABC Substrings）：frequency_evidence に挙がっているが、台帳では complement のページの練習だけで、このページには載せていない。「個数が等しい区間」（next-steps の 2 つ目）の型に近い可能性があるが、解説を読んで確かめていない

### prefix-sum

- typical90_bx（076. Cake Cut（★3）、ap.py で実在を確認、diff なし）：円環に並んだケーキのピースから連続する部分を取り、和をちょうど全体の 1/10 にできるか判定する。列を 2 周分に伸ばした累積和の上で、各始点から目標の値を二分探索する（尺取りでもよい）｜https://github.com/Reputeless/tenkei_90/blob/main/076.md（解答コードで方針を確認。問いはコードからの推定なので、公式の解説画像 https://github.com/E869120/kyopro_educational_90/blob/main/editorial/076.jpg でも確かめるとよい）｜節 circular の練習の候補。research 01 §4.E でも円環の例に挙がっている
- abc265_d（D. Iroha and Haiku (New ABC Edition)、diff 727、台帳では interval の practice）：区間和が P・Q・R と続く位置があるか判定する。累積和の値を集合に入れて調べる｜https://oraclesqlpuzzle.ninja-web.net/kyoupro/05-atcoder-02-abc/kyoupro-abc265-d.html｜節 with-binary-search の練習の候補（research 01 §5 で prefix-sum の候補に挙がっている）。interval のページと重なるので、どちらに置くかはメインで判断
- （対応の節）- 指摘 5（ケーキの型）：直した。「全体の和が 10 で割り切れなければ不可能」を足した。typical90_bx を台帳に足すかはメインの判断（上の「問題の補充の候補」）

### prime-exponent-vector

- 確認済みの問題で例題 1・練習 3・力試し 3 がそろうので、補充は必須ではない
- 候補（未確認、台帳は書いていない）：「指数をそろえる操作」の型（2 で割る・3 で割るなどの操作で全要素を等しくする）は練習に問題がない。ap.py と第三者の解説で ABC から探す価値がある。本文では型だけを書いた

### prime-factorization

- typical90_bw（典型90 075. Magic For Balls（★3））：N を素因数分解し、素因数の個数（重複込み）k から操作回数 ⌈log2 k⌉ を求める。練習の候補（abc319 以降ではないが、素因数の個数そのものを使う型の代表）。裏付け：https://github.com/E869120/kyopro_educational_90/blob/main/sol/075.cpp （調査 06-math-nt §5.3 で確認済みとされる。今回は再確認していない）
- abc319 以降の問題は見つけていない（ap.py での探索はしていない）。素因数分解そのものが本体になる新しい ABC は少なく、spf-sieve・prime-exponent-vector 側に回る傾向がある

### priority-queue

- catalog の例題 3・練習 5 で足りているので必須ではない。research/05-ds にある次の問題は台帳になく、ページの型の練習に合う（ap.py と第三者の解説での確認はしていない。足すなら確かめる）。
- abc253_c｜多重集合への追加・個数を指定した削除と、最大値 − 最小値の出力（遅延削除か multiset）｜https://kyo-pro.hatenablog.com/entry/ABC253C
- abc331_e｜禁止の組を除いた主菜と副菜の組の最大価格（価格の大きい組から列挙）｜https://zenn.dev/shinonome81/articles/3e1c0c8a9c00fc
- abc384_e｜グリッドで隣のスライムを条件つきで吸収し続けた後の最大の強さ（弱い順にヒープから）｜https://zenn.dev/shinonome81/articles/b1de75b0849b32

### probability-basics

- abc463_f（F. Senshuraku、diff 2127）：最後の試合の勝敗がランダムに決まった後、最多勝の選手から一様に優勝者を選ぶとき、各選手の優勝確率を mod 998244353 で求める。自分の試合の勝敗で条件付けし、同率の人数の分布（二項分布）と 1/k の和で全確率の公式を使う。裏付け https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2026/0620_abc463 。frequency_evidence と problem-sets で #conditional に結び付けられているので、力試し（challenge）として足すのがよい。ただし基礎のページの力試しとしては重いので、role は main の判断に任せる
- math_and_algorithm_w（アルゴ数学 023. Dice Expectation、diff なし）：題名からは期待値の定義の練習に見えるが、第三者の解説を検索で見つけられず、問いを確かめていない（候補止まり）
- past202209_c（C. Biased Dice、diff なし）：題名からは確率の基本の練習に見えるが、問いを確かめていない（候補止まり）
- 基礎の練習として abc 茶〜緑の確率の問題（場合の数の比・余事象）を 1〜2 問足したいが、ap.py の題名検索（Dice・Coin・Probab）では確かな候補が見つからなかった。研究ノート 07 §2.3 の表でも茶〜緑帯の純粋な確率の問題は abc126_c・abc193_d だけ

### probability-dp

- abc382_e（確認済み、1671）｜パックを開け続けてレアを X 枚集めるまでの回数の期待値。1 パックのレアの枚数の分布を確率 DP で求め、期待値 DP と組み合わせる｜上の表のとおり。practice の候補（前向きと後ろ向きの組み合わせの例として「期待値 DP との使い分け」の節に合う）
- abc310_f（台帳になし、1938）｜N 個のサイコロ（i 個目は 1〜A_i）を振ったとき、いくつかを選んで和を 10 にできる確率を mod 998244353 で求める。作れる和（10 以下）の集合を bit で持つ確率 DP｜02-dp §5.1 の候補表。第三者の解説で確かめられたのは https://scrapbox.io/konan-compro/ABC310_(2023%2F07%2F15) の感想（「k に作れる確率」の DP では和が 1 にならず、bit DP にする）だけで、裏付けとしては弱い。challenge か practice の候補。採るなら解説をもう 1 つ探す
- tdpc_tournament（台帳になし）｜2^K 人のトーナメントで各人が優勝する確率｜02-dp §5.1 の候補表（sigma425 の TDPC 記事）。本文で中身は確かめていない

### probability-symmetry

- 例題 1・練習 2・力試し 2 で数の目安を満たし、abc319 以降も ABC360 E・ABC473 G・ABC464 F があるので、今回は探していない
- 型として欲しいもの（未調査）：「残りから一様に選ぶ」を順列に置き換えるだけで解ける水〜青の E（AGC049 A は linearity-of-expectation の練習にある。このページの練習に足してもよい）

### proof-patterns

- 数の目安（thinking：例題 2〜4・練習 2〜6）は満たしているので、新しい候補は探していない。並べ替え論法・mod での矛盾の節には問題がない。補充するなら、mod での矛盾（平方数の余り）や円周を一定の歩幅で回る型の ABC を探す余地がある（未調査）。

### rational-mod

- 足りている（例題 1・練習 3、うち abc319 以降が 2 問：abc323_e・abc326_e）ので探していない
- #no-compare（比較は実数で、答えは mod で）の練習が台帳にない。optimal-strategy-expectation の担当が問題を探すときに、比較が要り答えを mod で出す ABC の問題があれば、このページの力試しにも足したい

### recursion-structure

- abc380_d（D. Strange Mirroring、diff 849）｜文字列の後ろに大文字・小文字を入れ替えたものを連結する操作を繰り返した文字列の、K 文字目（K は 10^18 程度まで）を答えるクエリ。長さが倍々に増えるので、K を含むブロックを探して前半へ戻ることを約 60 段繰り返す｜練習（depth の節「必要な深さは log K」の代表。研究ノートでも depth の例に挙がっている）｜https://oraclesqlpuzzle.ninja-web.net/kyoupro/05-atcoder-02-abc/kyoupro-abc380-d.html
- ap.py で実在・題名・difficulty を確かめた（`OK abc380_d D. Strange Mirroring diff=849`）。ikatakos のページには ABC380 の記録がなかった
- 本文では台帳にないため問題に触れず、depth の節は自作の構造（$S_n = S_{n-1} + c_n + S_{n-1}$）で説明した。追加されたら練習に入れ、方針に「長さが倍々なので K を含むブロックを探して反転の回数を数える」を書くとよい

### recursive-enumeration

- catalog の数（例題 2・練習 4・力試し 1）で足りているので必須ではない。abc319 以降の問題は abc345_d・abc390_d・abc473_d がある。
- abc475_d（D. Alphametic Prime、diff 741、台帳では sieve-eratosthenes の練習で確認済み）：文字に数字を割り当てる候補を DFS で全部作り、素数かを篩で判定する。生成型の練習に足せる｜https://qiita.com/comet725/items/777d32f7cf7630a48663（frequency_evidence に挙がっているのに本文にないため。summary は「（執筆時に確かめる）」のままなので、足すなら summary の確認が要る）
- typical90_bt（072. Loop Railway Plan（★4）、台帳で確認済み・complexity-estimation と dfs の練習）：経路のバックトラック。枝刈りと見積もりの節の練習に足せる｜https://github.com/E869120/kyopro_educational_90/blob/main/sol/072.cpp

### reformulation

- thinking の例題は 2〜4 問が目安で、台帳の例題は 2 問（abc324_e・abc105_d）だった。足すなら次の候補がある（どれも台帳では確認済みで、ほかのページに置かれている）。
- abc129_e（diff 1547）：a + b ≤ L かつ a + b = a xor b の組の数。表の「a + b = a ⊕ b ⇔ a AND b = 0」の代表。https://drken1215.hatenablog.com/entry/2019/06/10/150000 。今は bitwise-independence・digit-dp の練習。reformulation の練習に足す案
- abc466_e（diff 1027）：区間の反転を切り替え点 2 つに言い換えて DP。操作の言い換えの節の易しい代表。https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2026/0711_abc466 ／ https://qiita.com/comet725/items/d9928d9fdb242140f987 。台帳の summary が「（執筆時に確かめる）」なので、difference-sequence の執筆者の確認を待ってから練習に足す案
- abc330_f（diff 1718）：点を合計 K 回以下動かして 1 辺 d の正方形に収める最小の d。独立に分解する節の確認問題の題材（軸をまたぐ合計の制約）。https://ikatakos.com/ の該当回の記録などで裏付けを取ってから練習に足す案（今回は解説を読んでいないので、本文では問題 ID を出さず型だけ書いた）
- abc460_e を例題に格上げする案：式変形で変数を消す型の代表で、abc319 以降の E。今は reformulation・digit-and-mod・counting-mindset の 3 ページで練習なので、例題の持ち主をどこにするかはメインの判断

### rerooting

- abc223_g（G. Vertex Deletion、diff 2351）：各頂点を取り除いたときに木の最大マッチングが変わらないかを問う。全方位木 DP で頂点を除いた値を求める。裏付け https://kmjp.hatenablog.jp/entry/2021/10/19/0930 。力試しの候補（黄の下限なので、ページの青より上）
- abc298_h：kanpurin 氏の典型問題メモ（https://kanpurin.hatenablog.com/entry/2020/04/07/182948）の全方位木 DP の一覧にある。問いは確かめていない（候補の手がかりだけ）
- abc319 以降で一般の全方位木 DP が要る ABC は見つからなかった（kanpurin 氏の一覧の abc337_g は research/04 がオイラーツアーの問題とし、abc348_e は根の移動の差分で済む）。drken 氏のカテゴリ「全方位木DP」の一覧は途中までしか読めていない

### reverse-thinking

- なし。台帳の確認済み 6 問（例題 3・練習 2・力試し 1）で、目安（thinking の例題 2〜4・練習 2〜6）を満たす。締め切りの節の代表 abc137_d は greedy-priority-queue の例題なので、本文からその小見出しへリンクした。練習に加えるなら abc137_d を practice としてこのページにも載せる案がある（台帳の pages に {reverse-thinking, practice} を足す。根拠 https://drken1215.hatenablog.com/entry/2020/12/29/195900）

### rolling-hash

- 足さなくても数の目安（例題 2・練習 3・力試し 3、abc319 以降 3 問）を満たしているので、補充の候補は出さない。

### rotation-transform

- catalog の problems_note のとおり abc319 以降の問題がない。見つけた候補：
- abc375_c｜C. Spiral Rotation（diff 972）｜N×N の盤面で、外側から k 層目のマスを k 回ずつ時計回りに 90 度回した後の盤面を求める。層の番号 min(i+1, j+1, N−i, N−j) を 4 で割った余りの回数だけ (i, j) → (j, N−1−i) を施す。盤面を毎回作り直すと O(N^3) で間に合わない｜練習（節 grid-rotation）｜https://zenn.dev/os515/articles/atcoder-abc375-c
- abc404_b｜B. Grid Rotation（diff 181）｜盤面の回転と塗り替えで別の盤面に一致させる問題と思われる（題名からの推測）。第三者の解説を見つけられず未確認｜練習の候補（未確認）｜なし
- 水の帯で abc319 以降の、回転・アフィン変換が本体の問題は見つからなかった（ap.py の題名検索で Rotat・Spin・Flip・Mirror・Grid などを見た範囲）。abc336_f（Rotation Puzzle、2018）は部分の 180 度回転の操作列を半分全列挙で探す問題で、本体は meet-in-the-middle のため候補にしていない（解説は読んでいない）

### run-length-encoding

- 基礎のページなので練習は足りている。「塊ごとに数える」型と、塊が繰り返しでつながる型を補うなら次が候補（どれも ap.py で実在と diff を確かめた）。
- abc329_c｜205｜英小文字の文字列で、1 種類の文字だけからなる空でない部分文字列の種類数を求める｜文字ごとに最長の塊の長さを取って足す｜https://drken1215.hatenablog.com/entry/2023/11/21/032500
- abc369_c｜323｜数列の連続部分列のうち等差数列であるものの個数を求める｜隣接差の列を塊に分け、塊ごとに数える（台帳にあり、今は imos の練習。run-length-encoding の練習にも足すか、差分列の側に置くかはメインに任せる）｜https://drken1215.hatenablog.com/entry/2024/09/01/153129
- agc039_a｜517｜文字列 S を K 回つないだ文字列で、隣り合う文字がすべて異なるようにするための書き換えの最小回数を求める｜塊ごとに ⌊長さ/2⌋。全部が同じ文字の場合と、先頭と末尾の塊がつながる場合を分ける｜https://drken1215.hatenablog.com/entry/2020/11/11/203000

### scc

- abc335_e（diff 1540、確認済み・dp-dag の練習）：値の書かれたグラフで、値が減らないように頂点 1 から N へ進むときの値の種類数の最大。値の小さい方から大きい方へ（同じ値なら両方向に）有向辺を張って強連結成分で縮約し、DAG 上で DP する。scc の練習（dp-on-dag の節の代表）に足すことを提案する｜https://torus711.hatenablog.com/entry/2024/01/07/215719（強連結成分で縮約し、成分の番号順に DP すると明記）
- abc245_f（diff 1451、確認済み・topological-sort の練習）：有向グラフで、無限に動き続けられる頂点の数。強連結成分で「閉路の成分か、閉路の成分に辿り着ける成分」を後ろから決めても解ける（本文の on-cycle の節に型として書いた）。ただし evidence の kyo-pro の記事は出次数 0 から剥がす方法だけで、強連結成分の解き方は第三者の解説で未確認。足すなら SCC の解き方を書いた解説を evidence に足してほしい｜https://kyo-pro.hatenablog.com/entry/ABC245F
- 力試し（青の位置）は確認済みの候補が見つからなかった。research の abc374_g（2608）・abc214_h（3138）は発展で、dilworth-path-cover などの担当

### segment-tree-binary-search

- abc371_f（F. Takahashi in Narrow Road、diff 2109）：一列に並ぶ人を順に目的地へ動かすときの総移動回数を求める。X_i − i に直した単調な列に区間代入し、影響範囲を遅延セグ木上の二分探索で求める。青の節（on-lazy-segment-tree）の練習か力試しの候補。裏付け：research/05-ds §（ikatakos 氏 https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2024/0914_abc371 。ただし今回は開いていない。採るなら解法の部分で確かめる）
- 例題の位置の目安（水＝E）に合う abc319 以降の E が例題にない（例題は C・practice・F）。abc330_e（diff 1004）は練習に置いたが、ordered-set・interval-set でも練習なので、例題に上げるかは台帳の持ち主の決定に従う

### segment-tree-on-values

- 足りている（例題 2・練習 2・力試し 2。abc319 以降は abc339_e・abc403_g）。練習を増やすなら、値を添字にした（個数, 和）や区間 max の DP の水の ABC（abc319 以降）を探す余地がある。今回は ap.py での探索はしていない

### segment-tree

- 今回は探していない。例題 2・練習 5 で目安を満たし、abc319 以降の ABC も練習に 2 問（abc476_e・abc461_e）ある
- 力試しが 0 問なので、余力があれば青の帯の一点更新・区間取得の応用（research/05 §5 の segment-tree-monoids の候補 abc309_f・abc223_f など）を、monoids のページと重ならない形で 1 問足すとよい（未確認。役割の判断はメインに任せる）

### segmented-sieve

- 確認済みの問題は例題 1・練習 1（abc227_g は黄の diff 2207 で、水のページの練習としては難しい）。易しい練習（区間の素数を数えるだけのもの）の候補は、この作業では探していない（ap.py での検索も未実施）。ABC 以外（典型90・アルゴ数学・鉄則本・yukicoder の区間篩の問題）を問題の補充で探すとよい
- Library Checker には区間篩そのものの問題はない（Enumerate Primes は 1 からの篩）。verify は空のまま

### shortest-path-dag

- abc319 以降の水の候補を ap.py の題名検索（Shortest・Road・Path・Route）で探したが、最短路 DAG が本体と確かめられる問題は見つからなかった（catalog の level_evidence と同じ結論）。手引き §10 の「水のページには abc319 以降を 1 問以上」は満たせていない
- abc375_f（F. Road Blocked、diff 1546）は題名が近いが、調査（03-graph §4.B）ではワーシャルフロイド法の逆順の辺の追加の問題なので候補にしない

### sieve-eratosthenes

- 台帳の確認済みの問題で数は足りている（例題 1・練習 4）。力試しはない（基礎のページなので 0 でよいと判断した）。補充は提案しない。

### sigma-manipulation

- abc177_c（diff 386、台帳で確認済み。今は symmetry-pigeonhole-casework の例題）｜i < j の組の積 A_i A_j の総和（mod 10^9+7）。公式の節の (Σa)² − Σa² をそのまま使う問題。易しい練習として practice に足す案｜台帳の evidence
- abc186_d（diff 436、台帳で確認済み。今は contribution の例題）｜すべての組の差の絶対値の和。ソートして Σ (2j − N − 1) a_j に直す。公式の節の最後の式の練習として practice に足す案｜台帳の evidence
- abc351_f（diff 1253、台帳で確認済み）｜i < j の max(A_j − A_i, 0) の和。j を外側にして内側を BIT で持つ（「独立でない和を積に分けない」落とし穴の形）。BIT を使うので練習としてはやや上｜台帳の evidence
- 基礎の練習は 3 問で、易しい側（diff 1000 未満の式変形だけの問題）が abc230_e・abc471_e だけなので、上の abc177_c・abc186_d のどちらかを足すと段差が小さくなる。abc319 以降の問題は abc471_e だけ。

### small-graph-brute-force

- abc054_c｜N ≤ 8 の無向グラフで、頂点 1 から出発してすべての頂点をちょうど 1 回ずつ通るパスの数を求める（頂点の並びを順列で全部試し、隣どうしに辺があるか確かめる）｜https://drken1215.hatenablog.com/entry/2019/09/16/224600｜ap.py で実在を確認（C. One-stroke Path、diff 1244）。台帳にない。題名と検索結果の要約で問いと方針を確かめた（記事本文は未読）。頂点の順列をパスとして読む型で、練習に足すと「対応」以外の順列の読み方が増える。bitDP のページの導入（N が大きければ bitDP）とも結べる
- abc073_d｜訪れる町 R ≤ 8 個の順番を全部試し、ワーシャルフロイドで求めた距離で経路長の最小をとる｜https://blog.hamayanhamayan.com/entry/2017/09/10/002511｜台帳では確認済み（warshall-floyd の practice、diff 1345）。「距離を前計算して頂点の順列を全部試す」型として本ページの練習に足してもよいが、diff が水なので力試しが妥当

### small-to-large

- 確認済みの問題で数は足りている（例題 2・練習 4・力試し 1）。水のページの例題に abc319 以降が abc329_f の 1 問あるので条件も満たす。補充はなし。

### sorting-techniques

- abc474_e（E. One Time Coupon、diff 1153、ap.py で確認）｜商品をすべて買う最小の金額を、クーポンの得方と使い方を考えて求める。$A_i - B_i$ の昇順（同値なら $A_i$ の昇順）に並べると定価で買う商品が先頭の連続部分になり、分割位置を全探索できる｜https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2026/0906_abc474 ｜力試しの候補。frequency_evidence の recent に挙がっている。ただし要約を取った範囲では「先頭に連続すると考えられる」理由までは確かめていないので、台帳に入れる前に解説の本文で根拠を確かめること
- abc457_e は台帳で interval の練習になっており、このページには足していない

### spf-sieve

- abc215_d（D. Coprime 2、diff 736）｜数列のどの要素とも互いに素な M 以下の整数 k を列挙する。各 A_i の素因数を集め、その倍数を篩のように消す（A_i の分解に最小素因数の表が使える。試し割りでも可）｜https://qiita.com/sano192/items/00f6b70dab3bd3323ae6 ・ https://qiita.com/okm-uv/items/240b3fd3d2ff5f9561ab
- ap.py で実在と diff を確認済み（2021-08-21、diff 736）。練習（易しい側）として spf-sieve に載せることを提案する。台帳には書いていない
- 解説の多くは試し割りで分解しているので、「最小素因数の篩でも試し割りでも解ける」型の練習になる

### stack-techniques

- abc428_c（C. Brackets Stack Query、diff 483）：括弧の末尾への追加・削除のたびに正しい括弧列かを答える。undo の節の型（状態を積む）の練習。裏付け：https://qiita.com/masa2796/items/486bd7caa8fa49e0442e 。本文ではいま問題 ID を出さず、型とコード片（undo.cpp）だけを書いた
- abc237_d（D. LR insertion、diff 544）：直前の要素の左右に挿入する操作の結果。deque の節の「逆順に処理して両端に足す」の練習。裏付け：https://kazun-kyopro.hatenablog.com/entry/ABC/237/D 。本文では型だけを書いた
- abc283_d（D. Scope、diff 453）：括弧の対応と、閉じたときに中身を戻す。brackets の節の練習。裏付け：https://drken1215.hatenablog.com/entry/2024/11/01/130905
- 「真ん中への挿入は deque 2 本」の型の AtCoder の問題は見つけていない（research でも未発見）

### stars-and-bars

- abc132_d｜N 個の玉のうち K 個が青で、青を連続でまとめて回収する操作がちょうど i 回で済む並べ方を各 i で数える（青の分け方の正の整数解 × 赤の間に隣り合わないように置く）｜https://drken1215.hatenablog.com/entry/2019/06/30/183400 （台帳で確認済み。pages に足すだけ）
- abc319 以降（7 問体制）の問題は今回見つけていない（frequency_evidence の abc456_g は diff 2488 で発展。中身は第三者の解説で確かめていないので載せなかった）。

### steiner-subtree

- typical90_ai｜木と多数のクエリで、各クエリの指定頂点をすべてつなぐのに必要な辺の数の最小値を答える（指定頂点を行きがけ順に並べ、隣り合う 2 点と最後・最初の距離の和の半分）｜このページの力試し（台帳では auxiliary-tree の例題。例題は 1 ページだけなので、ここでは力試しに）｜https://github.com/E869120/kyopro_educational_90/blob/main/sol/035-04.cpp
- ap.py で題名を「Steiner」「Connectivity」「Visit」「Necessary」などで探したが、基礎の形の ABC の問題は abc368_d のほかに見つからなかった。catalog の problems_note のとおり練習は空のままにした

### stl-containers

- abc233_d：和がちょうど K の連続部分列の個数（map で累積和を数える）。05-ds §5 の候補。ただし prefix-sum-counting の例題なので、ここに足すなら練習扱い。裏付け https://drken1215.hatenablog.com/entry/2024/11/23/150237
- abc234_d（priority-queue の例題）を「容器を選ぶ」練習として触れる案もあるが、例題の重複になるので見送った

### string-basics

- 確認済みの問題で例題 1・練習 4 がそろったので、新しい候補は探していない
- frequency_evidence が recent 0 なので、abc319 以降の B〜C から回転・辞書順の比較・文字の対応を問う問題を足せるとよい。今回は ap.py での探索まではしていない

### subset-sum

- 追加は不要と判断した（例題 1・練習 5）。力試しの候補は abc221_g（diff 2914、45 度回転して 2 つの ± の部分和に分け bitset で判定・復元、https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2021/1002_abc221 ）だが、基礎のページには難しすぎるので bitset-speedup の側で扱うのがよい

### suffix-array

- abc280_h（Ex. Substring Sort、diff 3307、ap.py で確認）｜複数の文字列の全部分文字列を重複込みで辞書順に並べたときの K 番目を、複数の K について答える。SA と LCP 配列で数える（発展の節 kth-substring の代表）｜力試し（kth-substring の節）｜https://drken1215.hatenablog.com/entry/2023/01/02/070100 （planning/research/08-string-geo.md の表にあるが、本文の執筆では開いていない。採るなら解説で問いを確かめてから台帳へ）
- 水・青の例題（ACL を呼ぶだけで解ける ABC の E・F）は台帳にない。abc362_g（1625）が最も易しいが、例題は aho-corasick が持つ

### symmetry-pigeonhole-casework

- abc133_c｜L 以上 R 以下から選ぶ 2 数の積の mod 2019 の最小値。幅が 2019 以上なら答えは 0（鳩の巣原理の「範囲が広ければ答えが決まる」型）｜practice（台帳では proof-patterns の例題。#pigeonhole の 3 つ目の型の練習として）｜https://drken1215.hatenablog.com/entry/2019/07/07/233700
- abc179_e｜値が M 種類の漸化式の列の和。M + 1 項以内に同じ値が現れる（鳩の巣原理の「同じ状態に戻る」型）｜practice（台帳では periodicity の例題）｜https://drken1215.hatenablog.com/entry/2020/09/20/091500
- 今の問題（例題 3・練習 3）で thinking の目安（例題 2〜4、全体 5〜6）を満たすので、補充は任意

### ternary-search

- drken の「三分探索」「凸関数」の分類から探したが、ABC で水〜青の新しい候補は見つからなかった（ABC314 Ex は赤で難しすぎる。https://drken1215.hatenablog.com/archive/category/三分探索 ・ https://drken1215.hatenablog.com/archive/category/凸関数 ）。abc319 以降の問題は abc359_f（練習）で 1 問あり、手引き §10 の条件は満たしている
- 練習が 2 問で最小限なので、次のバッチで「整数の凸関数の最小化（丸めを含まない式）」の ABC D〜E を探すとよい（未確認のため ID は挙げない）

### time-dependent-dijkstra

- 練習が 1 問しかない（catalog の problems_note のとおり）。時刻で変わる辺を直接使う ABC の問題は、ap.py の題名検索（Train・Bus・Rush・時刻など）と第三者の解説で探した範囲では、次の 1 問だけが近い。
- abc319_e（E. Bus Stops、diff 1353）｜家からバス停を順に進み、バス停 i からは P_i の倍数の時刻に出るバスで T_i かかるとき、各クエリの出発時刻に対して会社へ最も早く着く時刻を求める｜役割の案：練習（[次の出発時刻まで待つ遷移](#wait)の切り上げと、分岐のない道で周期 840 を前計算する点。グラフの探索は要らないので、periodicity が持ち主になりそうなら、こちらは「使い分け」の参照だけにする）｜裏付け：https://programming-hiroba.com/abc319-e/ 、https://merom686.hatenablog.com/entry/2023/09/10/022053 （後者は検索結果に出ただけで未読）
- 参考：miscalc の記事は、同じ型の問題として TKPPC4-1 H「don't be late」（abc192_e とほぼ同じ）、abc170_f（Pond Skater。この形に落とし込むまでの考察が要る）、arc150_c を挙げている。abc170_f は ap.py で difficulty を確かめていない。台帳に入っているかと、このページの練習に向くかを確かめる価値がある（abc170_f は grid-graph や extended-dijkstra の持ち主の方が自然かもしれない）

### top-k-multiset

- abc218_g（G. Game on Tree 2、diff 2217、台帳で確認済み、いまは root-path-dfs と minimax の力試し）：根から葉へのパス上の値の中央値をスコアにするゲーム。DFS で値の追加と削除をくり返しながら中央値を求めるので、削除のある「中央値を保つ」の力試しになる。裏付け：https://kmjp.hatenablog.jp/entry/2021/09/12/0900（台帳の evidence）。偶数個のときの中央値は 2 つの平均で、`R の最小` も読む型になる（この点は解説で確かめていない。検証役に頼みたい）
- abc319 以降で水の帯の例題・練習になる問題は見つからなかった（ap.py の題名検索「Median」と、台帳の summary・approach の検索で探した）。catalog の level_evidence の記述（D2）と同じ結論

### topological-sort

- abc291_e（E. Find Permutation、diff 1069）｜大小関係の情報から順列が一意に決まるかを判定し、決まるなら復元する。Kahn 法でキューに 2 個以上入ったら一意でない（または最長路の長さが N−1 か）。unique の節の練習に向く｜https://programming-hiroba.com/abc291-e/
- dp_g（EDPC G. Longest Path）｜DAG の最長路。台帳にはあるので、to-dag-dp 節から参照するなら dp-dag の例題として本文でリンク（このページには載せていない）｜台帳の既存の evidence
- abc291_e は本文の unique の節で問題 ID を出さず型だけを書いた（手引き §13-6）。台帳に入れば練習に足したい。

### tree-bipartite

- abc437_g（G. Colorful Christmas Tree、diff 2806）｜木が二部グラフであることを使い、色で頂点を左右に分けて最大流で解く｜https://kmjp.hatenablog.jp/entry/2025/12/20/0930 （調査 04-tree §5.1 にあり、台帳での状態は確かめていない。帯が高すぎるので、置くなら上位の手法とのつながりの参照か、二部マッチング・最大流のページの力試し）
- 基礎のページなので例題 1・練習 2・力試し 1 で足りると判断し、新しい候補は探していない

### tree-diameter

- 数は足りている（例題 2・練習 5・力試し 2）。補充するなら次のとおり。
- abc267_f（台帳で確認済み・lca の例題）：頂点 u から距離がちょうど k の頂点を 1 つ答える質問に Q 回答える。直径の端点を根にした K 個上の祖先。裏付け https://kazun-kyopro.hatenablog.com/entry/ABC/267/F 。練習に足すのがよい（上の台帳の提案）
- agc001_c（ap.py で実在を確認。題名 Shorten Diameter、diff なし。台帳になし）：木から頂点を消して直径を K 以下にするとき、消す頂点の最小数を求める型で、中心の候補（頂点か辺）を全部試す。第三者の日本語の解説を見つけられず（検索で出たのは codeforces.com だけで、開いていない）、裏付けの URL はない。執筆では使っていない
- abc281_g（Farthest City、diff 2304）・abc290_f（Maximum Diameter、diff 2300）は題名に直径・最遠が入るが、数え上げが本体なので comb の担当（ap.py で実在のみ確認）

### tree-distance

- 確認済みの問題は例題 1・練習 2・力試し 1 で、手引きの目安（練習 2〜6）の下限にある。次は研究の資料にある候補で、台帳には入っていない。
- abc414_f｜木の上でちょうど K 辺ずつ進む移動の最短回数を、距離の余りと来た方向を状態に持つ BFS で求める（研究の資料 04-tree §5.1 で練習の候補。グラフの状態拡張との境界なので、力試しが合う）｜https://merom686.hatenablog.com/entry/2025/07/13/021033 （この URL は今回は読んでいない。研究の資料の記載のまま）
- abc319 以降の ABC から新しい候補を探す作業はしていない（第三者の解説での裏付けが要るため、次の担当に回したい）。

### tree-dp

- 水のページに abc319 以降の問題を 1 問以上という目安は、abc348_e（練習）と abc447_f（例題）で満たしている。新しい候補は探していない
- catalog の level_evidence にある abc369_g（2055、子ごとの得の応用）は台帳を見ていない。greedy-children 節の力試しに足すなら、第三者の解説での確認が要る

### tree-edge-contribution

- abc201_e｜重み付きの木の全頂点対について、パスの XOR の総和を求める。根からの累積 XOR の bit ごとの 0 と 1 の個数の積で数える。台帳は確認済み（tree-distance の練習）｜練習（本文の edge-pairs の「XOR の和」の型に対応。abc479_e を外すと、水の ABC の練習が 1 問減るので補う）｜https://blog.hamayanhamayan.com/entry/2021/05/15/235842
- abc220_f｜木の各頂点について、ほかの全頂点への距離の和を求める。台帳は確認済み（tree-dp の例題）｜練習（任意。使い分けの「頂点ごとの値は根の移動の差分」に対応）｜https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2021/0926_abc220
- abc163_f｜頂点に色がある木で、色ごとに「その色の頂点を 1 つ以上通るパスの数」を求める。台帳にない（ap.py で実在と diff 2470 を確認）｜力試し（黄の節 expectation の「特定の色を通らないパス」に対応。本文では問題 ID を出さず型だけを書いた）｜https://kmjp.hatenablog.jp/entry/2020/04/20/0930

### tree-imos

- abc138_d（D. Ki、diff 920）｜部分木への加算を繰り返した後の各頂点の値（部分木加算の基本形）｜https://drken1215.hatenablog.com/entry/2020/05/18/174000
- abc309_e（E. Family and Insurance、diff 957、台帳にあり）｜家系図で y 世代先までの子孫に及ぶ保険に入っている人数（max を下へ伝える形）｜https://qiita.com/ZOI_dayo/items/a55cc4342832efdc23ba
- パスへの加算（青の節）の代表の ABC の問題は見つけていない（abc222_e は素朴な方法でも通る）。台帳に既にある問題で「多数のパスに +1 して各頂点・各辺の回数」を問うものがあれば、練習か力試しに足したい

### trie

- arc087_c（E. Prefix-free Game、diff 2431、ap.py で実在を確認、台帳になし）：接頭辞の関係にならないよう文字列を足していくゲームの勝敗。Trie の空いた部分木ごとに Grundy 数を求めて XOR する型で、節 dp-on-trie の「ゲーム」の段落の代表になる。発展の難しさなので力試しか、grundy-number の練習が向く。裏付け：drken「AtCoder 版！蟻本 (上級編)」で文字列（Trie）の章の問題として挙がっている（https://qiita.com/drken/items/9b311d553aa434bb26e4）。解法の詳しい第三者の解説は見つけられておらず、台帳に入れるなら evidence を探す必要がある
- abc319 以降の水の問題は、abc353_e・abc403_e・abc437_e がすでにあるので探していない
- （対応の節）- 指摘 11 の arc087_c は台帳になく evidence も未確保なので、本文に問題へのリンクは付けていない。上の「問題の補充の候補」の提案はそのまま

### two-pointers

- catalog の数（例題 1・練習 4・力試し 2）で足りているので必須ではない。次は節の内容に合う候補（ap.py で実在と difficulty を確かめていない。research 01 に載っているもの）。
- abc172_c（Tsundoku、930）：累積和と尺取り（片方を増やすともう片方が減る 2 つの列の尺取り）。台帳では prefix-sum の練習。二分探索との関係の節の練習にも合う｜https://blog.hamayanhamayan.com/entry/2020/06/27/230511
- abc124_d（Handstand、1138）：ランレングスの塊の列で固定個数の窓を尺取り。台帳では run-length-encoding の例題。本文の「使い分け」で型だけ触れた｜https://drken1215.hatenablog.com/entry/2019/04/14/222900
- abc319 以降の尺取りの問題（frequency_evidence の abc452_f・abc461_d・abc470_g など）は台帳に未登録。水のページではないので必須ではないが、近年の例として練習に 1 問あると良い（第三者の解説での裏付けはまだしていない）

### union-find-applications

- abc131_f（F. Must Be Rectangular!、diff 1937、台帳で確認済み）：長方形の 3 頂点があれば 4 頂点目を足す操作を、最大で何回できるかを求める。x 座標と y 座標を頂点にした Union-Find で、成分ごとに（x の数）×（y の数）の和 − N。裏付け：https://drken1215.hatenablog.com/entry/2019/06/23/004700
- abc380_e（E. 1D Bucket Tool、diff 1230、台帳で確認済み・interval-set の例題）：1 列のマスで、同じ色でつながった区間を塗り替えるクエリと、色ごとのマス数のクエリを処理する。根に区間の左端・右端・色を持たせ、隣と同色なら併合する。練習に足す候補。裏付け：https://drken1215.hatenablog.com/entry/2024/11/17/035045
- abc319 以降で水の帯の候補は、台帳の abc372_e・abc409_f・abc420_e・abc364_f・abc355_f で足りていると判断し、新たには探していない

### union-find-connectivity

- abc413_g（G. Big Banned Grid、diff 1723、確認済み・grid-graph の力試し）：巨大なグリッドで障害物を避けて左上から右下へ行けるかを判定する。障害物どうしを 8 近傍で Union-Find につなぎ、左端・下端に接するものと右端・上端に接するものをそれぞれまとめて、両者が連結なら通れない。裏付け https://kmjp.hatenablog.jp/entry/2025/07/05/0930 。練習（超頂点の節）として提案
- 逆順の削除そのものを問う abc319 以降の ABC は見つけられなかった（catalog の problems_note と同じ）。候補探しは ap.py と第三者の解説で続ける必要がある

### union-find

- abc350_d（D. New Friends、diff 773、ap.py で実在と difficulty を確認。台帳になし）：友達の友達と友達になる操作を繰り返したとき、新しく増える友達の組の数の最大を求める。各連結成分で「頂点数 s の完全グラフの辺数 s(s−1)/2 − 今ある辺数」を足す。根に頂点数と辺数を持たせる型と、積の `long long` の練習になる。練習（practice）での追加を提案する。裏付け：https://oraclesqlpuzzle.ninja-web.net/kyoupro/05-atcoder-02-abc/kyoupro-abc350-d.html
- abc319 以降の問題は、基礎のページの要件でないため探していない（frequency_evidence の recent の abc451_e は台帳で tree-construction の例題で、Union-Find は道具として使うだけなので載せていない）

### warshall-floyd

- catalog の数（例題 3・練習 4・力試し 1）は目安の範囲だが、abc319 以降の問題が abc375_f と abc338_f の 2 問だけで、`recent 0` の根拠も薄いので、最近の ABC の候補を挙げる。
- abc369_e（Sightseeing Tour、diff 1301）：各クエリで指定された K 本（5 以下）の橋をすべて渡って頂点 1 から N へ行く最短時間を求める。全点対の距離を前計算し、橋の順番（K!）と渡る向き（2^K）を全探索する。with-enumeration の節の「通る辺が決まっている」の型の代表で、練習に向く｜https://programming-hiroba.com/abc369-e/
- abc416_e（Development、diff 1428）：道路の追加と空港の設置のクエリを処理しながら、全点対の最短距離の総和を答える。空港を超頂点につなぎ、追加のたびに表を O(N^2) で更新する。add-edge の節の練習に向く（abc375_f と違い、追加そのものが来る型）｜https://kcpc.hatenablog.com/entry/2025/07/28/090000（制約の N・Q の値は記事に書かれておらず、確かめていない）
- abc286_e（Souvenir、diff 1128）：直行便の表とお土産の価値から、各クエリの 2 都市間で、乗る便の数が最小の経路のうちお土産の価値の和が最大のものを答える。（距離, 価値）の組を辞書順で比べるワーシャルフロイド法。beyond-distance の節の練習に向く｜https://programming-hiroba.com/abc286-e/
- arc083_b（Restoring Road Network）は graph-construction の例題なので、redundant-edges の節では問題 ID を出さず、graph-construction へのリンクだけにした（変更の提案ではない）

### weighted-union-find

- 確認済みの問題は例題 2・練習 5・力試し 1 で、目安を満たすので新しい候補は探していない
- abc319 以降の問題は abc328_f（例題）と abc451_f（練習）の 2 問で、水のページの要件（1 問以上）を満たす

### z-algorithm

- 水・青のページには abc319 以降を 1 問以上という目安は abc430_e（例題）で満たしている。追加の候補は探していない（台帳の 7 問で数の目安を満たす）。

### zero-one-bfs

- abc400_d（D. Takahashi the Wall Breaker、diff 1026（緑/基礎）、ap.py で実在を確認）：グリッドで、前方 1〜2 マスの壁を壊して進む前蹴りの最小回数を求める。通路へ歩く移動を重み 0、前蹴りで前方 1 マスまたは 2 マスへ進む移動を重み 1 にした 01-BFS。catalog の problems_note にある「abc319 以降の 01-BFS の問題」に当たる。difficulty は水に届かないので練習の最初に置くのがよい。裏付け：https://oraclesqlpuzzle.ninja-web.net/kyoupro/05-atcoder-02-abc/kyoupro-abc400-d.html
