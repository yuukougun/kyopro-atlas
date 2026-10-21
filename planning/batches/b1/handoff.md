# b1 からの申し送り（2026-10-21）

b1（基礎・水 173 ページ）の報告のうち、後のバッチで相手のページを書く人と、メインが使う控え。出どころは b1 の各ページの報告（`planning/batches/b1/<id>.md`）をまとめた提案と、決定事項（[decisions.md](decisions.md)）の反映の作業。行番号は 2026-10-21 の反映の時点のもので、ページを直すとずれる。

使い方：

- 相手のページを書く人は、§1 で自分のページへ「ページへのリンク」を置いている行を探し、節が決まったらメインに知らせる（ほかのページの行は執筆者が直さない）
- メインは、相手が draft になったら §1 の行を節へのリンクに張り替える（decisions.md の E3）。§2〜§7 は、相手のページの執筆の指示に添える

## 1. 節へ張り替えるリンク

相手が stub だったので、anchor を付けずにページへリンクした箇所。anchor 案は、そのページの related・prerequisites の `id#anchor` と、報告の中の記述から機械的に拾った候補で、別の文脈の anchor が混ざることがある。張り替える前に、リンクを置いた文と相手の節の中身が合うかを確かめる。

報告で名指しされたもの（メインの控えに残すよう明記されたもの）：

- complexity-estimation の制約の表 → bit-full-search#permutations（bit-full-search は draft になった）
- reformulation の表の「狭義単調増加」の行 → difference-sequence#strict-to-weak
- topological-sort → cpp-environment#stack-depth（cpp-lambda・dfs・tree-dp・memoized-recursion・recursion-structure も cpp-environment へ回している）
- cpp-structured-bindings → cpp-undefined-behavior#dangling-pq-top・cpp-initialization#ctad（どちらも相手は draft になった）
- prefix-sum-counting → stl-containers・digit-and-mod・integer-division・reformulation の節（どの節かは prefix-sum-counting の報告を見る）
- bit-operations → cpp-math-functions#bit-functions・#builtins、cpp-integer-overflow#shift-width、subset-enumeration-dp#why-3n
- coupon-collector → inclusion-exclusion#min-max（本文は「min-max 包除の節」の文字で示している）
- string-basics の節 rotation → z-algorithm#cyclic-shift
- steiner-subtree → auxiliary-tree#steiner-queries、leaf-first#peel-leaves、steiner-tree の節
- rolling-hash → palindrome#manacher、hash-safety の節（birthday-bound・mod-2-64 など）

### 1.1 相手がすでに draft のもの（今すぐ張り替えられる）

「sections に」は、anchor 案が相手の sections（または定型の節）にあるか。「無」は報告の時点から anchor が変わったか、別の節を指す案なので、相手の見出しを見て選ぶ。

| ページ | 行 | リンク先 | anchor 案 | sections に |
| --- | --- | --- | --- | --- |
| docs/basics/bitwise-independence.md | 43 | bit-operations | #xor-properties | 有 |
| docs/basics/brute-force.md | 155 | bit-full-search | #assume-and-check・#half-greedy | 有 |
| docs/basics/brute-force.md | 175 | bit-full-search | #assume-and-check・#half-greedy | 有 |
| docs/basics/complexity-estimation.md | 59 | bit-full-search | #permutations | 有 |
| docs/basics/complexity-estimation.md | 150 | cpp-io | #tle-causes | 有 |
| docs/basics/greedy-basics.md | 39 | sorting-techniques | #greedy-order | 有 |
| docs/basics/greedy-basics.md | 122 | binary-search-answer | #greedy-check | 有 |
| docs/basics/lexicographic-greedy.md | 39 | greedy-basics | #counterexamples | 有 |
| docs/basics/lexicographic-greedy.md | 83 | subsequence-matching | #lexicographically-smallest | 有 |
| docs/basics/lexicographic-greedy.md | 169 | subsequence-matching | #lexicographically-smallest | 有 |
| docs/basics/median-absolute.md | 121 | manhattan-chebyshev | #axis-independence | 有 |
| docs/basics/meet-in-the-middle.md | 39 | bit-full-search | #half-greedy | 有 |
| docs/basics/meet-in-the-middle.md | 49 | bit-full-search | #half-greedy | 有 |
| docs/basics/periodicity.md | 51 | symmetry-pigeonhole-casework | #pigeonhole | 有 |
| docs/basics/prefix-sum-2d.md | 163 | fenwick-tree | #variants | 有 |
| docs/basics/recursion-structure.md | 142 | cpp-lambda | #recursive-lambda | 有 |
| docs/comb/counting-basics.md | 148 | dp-state-design | #dp-cyclic | 有 |
| docs/comb/counting-basics.md | 192 | dp-state-design | #dp-cyclic | 有 |
| docs/comb/coupon-collector.md | 130 | expected-value-dp | #self-loop | 有 |
| docs/comb/game-basics.md | 183 | symmetry-pigeonhole-casework | #symmetry | 有 |
| docs/comb/minimax.md | 168 | binary-search-answer | #dp-check | 有 |
| docs/comb/nim.md | 40 | game-basics | #game-dp・#mirror-strategy・#turn・#win-lose | 有 |
| docs/comb/nim.md | 175 | game-basics | #game-dp・#mirror-strategy・#turn・#win-lose | 有 |
| docs/comb/probability-basics.md | 130 | linearity-of-expectation | #nonlinear・#sum-vs-expectation | 有 |
| docs/comb/probability-basics.md | 164 | linearity-of-expectation | #nonlinear・#sum-vs-expectation | 有 |
| docs/comb/probability-dp.md | 155 | lattice-paths | #independent-axes | 有 |
| docs/comb/probability-dp.md | 186 | matrix-power | #dp-transition | 有 |
| docs/comb/probability-symmetry.md | 111 | linearity-of-expectation | #pairs | 有 |
| docs/comb/probability-symmetry.md | 214 | linearity-of-expectation | #pairs | 有 |
| docs/cpp/acl-reading.md | 41 | cpp-lambda | #template-argument | 有 |
| docs/cpp/acl-reading.md | 215 | cpp-lambda | #template-argument | 有 |
| docs/cpp/cpp-algorithms.md | 42 | cpp-container-idioms | #member-lower-bound | 有 |
| docs/cpp/cpp-comparators.md | 69 | cpp-undefined-behavior | #debug-build | 有 |
| docs/cpp/cpp-string-api.md | 203 | cpp-io | #float-output・#separators・#tle-causes | 有 |
| docs/cpp/cpp-structured-bindings.md | 55 | cpp-initialization | #ctad | 有 |
| docs/cpp/cpp-structured-bindings.md | 164 | cpp-undefined-behavior | #dangling-pq-top | 有 |
| docs/cpp/cpp-types-literals.md | 45 | cpp-integer-overflow | #edge-values・#int-product | 有 |
| docs/cpp/cpp-views-cpp23.md | 41 | cpp-structured-bindings | #enumerate-reference | 有 |
| docs/cpp/cpp-views-cpp23.md | 57 | cpp-structured-bindings | #enumerate-reference | 有 |
| docs/dp/bit-dp.md | 164 | game-basics | #state-design | 有 |
| docs/dp/digit-dp.md | 41 | mod-arithmetic | #negative | 有 |
| docs/dp/dp-basics.md | 160 | greedy-basics | #when-greedy-fails | 有 |
| docs/dp/dp-dag.md | 106 | scc | #dp-on-dag | 有 |
| docs/dp/dp-dag.md | 143 | scc | #dp-on-dag | 有 |
| docs/dp/dp-mod-state.md | 130 | game-basics | #state-design・#turn | 有 |
| docs/dp/dp-reconstruction.md | 87 | bfs | #path-restoration | 有 |
| docs/dp/dp-reconstruction.md | 105 | lexicographic-greedy | #kth | 有 |
| docs/dp/dp-reconstruction.md | 192 | bfs | #path-restoration | 有 |
| docs/dp/knapsack-01.md | 222 | meet-in-the-middle | #vs-knapsack | 有 |
| docs/dp/lis.md | 202 | manhattan-chebyshev | #rotate-45 | 有 |
| docs/dp/rerooting.md | 166 | tree-edge-contribution | #edge-pairs | 有 |
| docs/dp/rerooting.md | 172 | tree-diameter | #eccentricity | 有 |
| docs/dp/subset-sum.md | 58 | knapsack-01 | #dp-rolling-array | 有 |
| docs/dp/subset-sum.md | 158 | knapsack-01 | #dp-rolling-array | 有 |
| docs/dp/subset-sum.md | 162 | dp-mod-state | #average | 有 |
| docs/dp/tree-dp.md | 199 | binary-search-answer | #dp-check | 有 |
| docs/dp/tree-dp.md | 209 | binary-search-answer | #dp-check | 有 |
| docs/dp/tree-dp.md | 213 | small-to-large | #subtree-merge | 有 |
| docs/dp/tree-dp.md | 331 | small-to-large | #subtree-merge | 有 |
| docs/ds/global-offset.md | 163 | lazy-segment-tree | #idea | 有 |
| docs/ds/segment-tree-binary-search.md | 43 | binary-search | #comparison | 有 |
| docs/ds/segment-tree-binary-search.md | 294 | binary-search | #comparison | 有 |
| docs/ds/segment-tree-on-values.md | 44 | coordinate-compression | #with-ds | 有 |
| docs/ds/segment-tree-on-values.md | 50 | fenwick-tree | #binary-search・#count-by-value | 有 |
| docs/ds/segment-tree-on-values.md | 69 | offline-queries | #online | 有 |
| docs/ds/segment-tree-on-values.md | 130 | fenwick-tree | #binary-search・#count-by-value | 有 |
| docs/ds/segment-tree-on-values.md | 132 | top-k-multiset | #by-index | 有 |
| docs/ds/segment-tree-on-values.md | 215 | top-k-multiset | #by-index | 有 |
| docs/ds/segment-tree-on-values.md | 261 | top-k-multiset | #by-index | 有 |
| docs/ds/segment-tree-on-values.md | 265 | offline-queries | #online | 有 |
| docs/ds/top-k-multiset.md | 164 | fenwick-tree | #binary-search | 有 |
| docs/ds/weighted-union-find.md | 45 | union-find | #complexity | 有 |
| docs/ds/weighted-union-find.md | 51 | union-find | #complexity | 有 |
| docs/geometry/geometry-precision.md | 112 | integer-root | #compare-sqrt | 有 |
| docs/geometry/geometry-precision.md | 204 | integer-root | #compare-sqrt | 有 |
| docs/graph/bfs.md | 51 | dijkstra | #super-vertex・#super-vertex-offset | 無 |
| docs/graph/bfs.md | 139 | dijkstra | #super-vertex・#super-vertex-offset | 無 |
| docs/graph/bfs.md | 161 | extended-dijkstra | #super-vertex・#super-vertex-offset | 有 |
| docs/graph/dijkstra.md | 171 | shortest-path-dag | #build | 有 |
| docs/graph/functional-graph.md | 47 | scc | #on-cycle | 有 |
| docs/graph/functional-graph.md | 59 | tree-basics | #remove-add-edge | 有 |
| docs/graph/functional-graph.md | 119 | scc | #on-cycle | 有 |
| docs/graph/functional-graph.md | 150 | mod-pow | #binary-expansion | 有 |
| docs/graph/functional-graph.md | 239 | scc | #on-cycle | 有 |
| docs/graph/functional-graph.md | 240 | namori-graph | #directed-version・#one-cycle | 有 |
| docs/graph/minimum-spanning-tree.md | 182 | union-find-applications | #multiple-uf・#next-pointer | 有 |
| docs/graph/scc.md | 67 | dfs | #iterative・#pre-post-order | 有 |
| docs/graph/scc.md | 160 | dp-dag | #find-dag | 有 |
| docs/graph/shortest-path-dag.md | 39 | dp-dag | #count-shortest-paths | 有 |
| docs/graph/shortest-path-dag.md | 88 | dp-dag | #count-shortest-paths | 有 |
| docs/graph/topological-sort.md | 79 | cycle-detection | #kahn-leftover | 有 |
| docs/math/exponent-mod.md | 95 | crt | #acl | 有 |
| docs/math/exponent-mod.md | 117 | crt | #acl | 有 |
| docs/math/ext-gcd.md | 163 | mod-inverse | #ext-gcd | 有 |
| docs/math/ext-gcd.md | 189 | mod-inverse | #ext-gcd | 有 |
| docs/math/ext-gcd.md | 246 | mod-inverse | #ext-gcd | 有 |
| docs/math/mod-inverse.md | 151 | binomial-precompute | #lucas | 有 |
| docs/math/proof-patterns.md | 41 | gcd-lcm | #euclid | 有 |
| docs/math/proof-patterns.md | 96 | ext-gcd | #applications | 有 |
| docs/math/spf-sieve.md | 40 | prime-factorization | #which-method | 有 |
| docs/math/spf-sieve.md | 66 | prime-factorization | #which-method | 有 |
| docs/math/spf-sieve.md | 152 | prime-factorization | #which-method | 有 |
| docs/string/kmp.md | 322 | z-algorithm | #period | 有 |
| docs/string/rolling-hash.md | 148 | palindrome | #manacher | 有 |
| docs/string/rolling-hash.md | 211 | palindrome | #manacher | 有 |
| docs/string/string-basics.md | 169 | z-algorithm | #cyclic-shift | 有 |
| docs/string/string-basics.md | 190 | cpp-string-api | #string-view | 有 |
| docs/string/string-basics.md | 196 | z-algorithm | #cyclic-shift | 有 |
| docs/string/z-algorithm.md | 169 | palindrome | #manacher | 有 |
| docs/thinking/construction.md | 98 | parity | #checkerboard | 有 |
| docs/thinking/contribution.md | 62 | sigma-manipulation | #swap-order | 有 |
| docs/thinking/invariant.md | 48 | proof-patterns | #necessary-sufficient | 有 |
| docs/thinking/reverse-thinking.md | 87 | priority-queue | #abc137_d | 無 |
| docs/tree/tree-basics.md | 173 | tree-traversal | #parent-depth-size | 有 |

（114 行）

### 1.2 相手がまだ stub のもの（anchor 案がある）

| ページ | 行 | リンク先 | anchor 案 |
| --- | --- | --- | --- |
| docs/basics/greedy-priority-queue.md | 163 | alien-dp | #undoable-greedy |
| docs/basics/greedy-priority-queue.md | 193 | alien-dp | #undoable-greedy |
| docs/tree/steiner-subtree.md | 110 | auxiliary-tree | #steiner-queries |
| docs/tree/steiner-subtree.md | 111 | auxiliary-tree | #steiner-queries |
| docs/basics/recursive-enumeration.md | 104 | bell-number | #size |
| docs/basics/bitwise-independence.md | 142 | binary-trie | #implicit |
| docs/basics/bitwise-independence.md | 170 | binary-trie | #implicit |
| docs/basics/bitwise-independence.md | 209 | binary-trie | #implicit |
| docs/comb/lattice-paths.md | 122 | binomial-identities | #hockey-stick |
| docs/comb/lattice-paths.md | 124 | binomial-identities | #hockey-stick |
| docs/dp/dp-dag.md | 156 | bitset-speedup | #reachability |
| docs/dp/subset-sum.md | 64 | bitset-speedup | #subset-sum-shift |
| docs/dp/subset-sum.md | 160 | bitset-speedup | #subset-sum-shift |
| docs/basics/ternary-search.md | 204 | circle-geometry | #geometry-optimization |
| docs/basics/ternary-search.md | 249 | circle-geometry | #geometry-optimization |
| docs/math/floor-sum.md | 262 | convex-hull | #lattice-points |
| docs/string/rolling-hash.md | 215 | convolution-ntt | #string-matching |
| docs/dp/dp-state-design.md | 217 | counting-dedup | #in-dp |
| docs/cpp/cpp-lambda.md | 299 | cpp-environment | #stack-depth |
| docs/dp/dp-dag.md | 165 | cpp-environment | #stack-depth |
| docs/dp/memoized-recursion.md | 128 | cpp-environment | #stack-depth |
| docs/dp/tree-dp.md | 223 | cpp-environment | #stack-depth |
| docs/graph/dfs.md | 109 | cpp-environment | #stack-depth |
| docs/graph/topological-sort.md | 168 | cpp-environment | #stack-depth |
| docs/tree/tree-traversal.md | 142 | cpp-environment | #stack-depth |
| docs/thinking/reformulation.md | 55 | difference-sequence | #strict-to-weak |
| docs/thinking/reformulation.md | 136 | difference-sequence | #strict-to-weak |
| docs/dp/lis.md | 203 | dilworth-path-cover | #antichain |
| docs/dp/knapsack-01.md | 217 | divide-and-conquer | #range-knapsack |
| docs/dp/dp-prefix-sum.md | 164 | dp-segment-tree | #dp-sliding-window |
| docs/dp/dp-prefix-sum.md | 164 | dp-segment-tree | #dp-sliding-window |
| docs/dp/dp-prefix-sum.md | 170 | dp-segment-tree | #dp-sliding-window |
| docs/dp/dp-prefix-sum.md | 299 | dp-segment-tree | #dp-sliding-window |
| docs/dp/memoized-recursion.md | 136 | expectation-linear-equations | #cycle |
| docs/comb/coupon-collector.md | 59 | expectation-tail-sum | #waiting-time |
| docs/comb/coupon-collector.md | 132 | expectation-tail-sum | #waiting-time |
| docs/math/proof-patterns.md | 112 | gcd-properties | #step-mod |
| docs/dp/dp-grid.md | 294 | grid | #right-down |
| docs/string/rolling-hash.md | 102 | hash-safety | #recommended-design |
| docs/string/rolling-hash.md | 103 | hash-safety | #recommended-design |
| docs/string/rolling-hash.md | 109 | hash-safety | #recommended-design |
| docs/string/rolling-hash.md | 114 | hash-safety | #recommended-design |
| docs/comb/coupon-collector.md | 130 | inclusion-exclusion | #min-max |
| docs/dp/dp-grid.md | 74 | inclusion-exclusion-dp | #first-obstacle |
| docs/dp/dp-grid.md | 292 | inclusion-exclusion-dp | #first-obstacle |
| docs/comb/probability-basics.md | 47 | notation | #probability |
| docs/dp/lis.md | 180 | root-path-dfs | #undo-log |
| docs/math/matrix-power.md | 229 | segment-tree-monoids | #matrix |
| docs/math/matrix-power.md | 390 | segment-tree-monoids | #matrix |
| docs/tree/steiner-subtree.md | 92 | steiner-tree | #on-tree |
| docs/comb/counting-mindset.md | 154 | stress-testing | #experiment |
| docs/misc/interactive.md | 190 | stress-testing | #interactive |
| docs/thinking/symmetry-pigeonhole-casework.md | 87 | stress-testing | #experiment |
| docs/thinking/symmetry-pigeonhole-casework.md | 127 | stress-testing | #experiment |
| docs/basics/bit-operations.md | 146 | subset-enumeration-dp | #submask-loop・#why-3n |
| docs/basics/bit-operations.md | 178 | subset-enumeration-dp | #submask-loop・#why-3n |
| docs/string/palindrome.md | 286 | suffix-automaton | #palindromic-tree |
| docs/basics/prefix-sum-2d.md | 163 | sweep-line-2d | #intervals-as-points |
| docs/basics/prefix-sum-2d.md | 204 | sweep-line-2d | #intervals-as-points |
| docs/basics/prefix-sum-2d.md | 255 | sweep-line-2d | #intervals-as-points |
| docs/thinking/reformulation.md | 253 | thinking-checklist | #q-rephrase |

（61 行）

### 1.3 相手がまだ stub のもの（anchor 案なし）

相手のページを書いた人か、メインが節を選ぶ。リンク先ごとに、ページへのリンクを置いている行を `ページの id:行` で並べた。

- **advanced-ds-catalog**（1）：priority-queue:196
- **aho-corasick**（7）：matrix-power:159・kmp:217・kmp:329・rolling-hash:214・suffix-array:261・suffix-array:291・trie:300
- **alien-dp**（1）：dp-sequence-partition:156
- **auxiliary-tree**（2）：lca:259・small-to-large:303
- **balanced-bst**（3）：kth-element:72・linked-list:117・stl-containers:61
- **bell-number**（1）：complexity-estimation:138
- **bellman-ford**（7）：dp-dag:144・dijkstra:144・dijkstra:193・dijkstra:248・graph-basics:59・warshall-floyd:115・warshall-floyd:299
- **binary-trie**（3）：kth-element:74・ordered-set:155・trie:299
- **binomial-identities**（1）：binomial-coefficient:161
- **bipartite-matching**（4）：bipartite-graph:169・grid-graph:122・leaf-first:141・tree-bipartite:142
- **bitset-speedup**（6）：complexity-estimation:149・meet-in-the-middle:142・cpp-math-functions:205・dp-grid:93・scc:190・scc:198
- **bottleneck-path**（3）：minimum-spanning-tree:214・minimum-spanning-tree:288・union-find-connectivity:159
- **broken-profile-dp**（1）：matrix-power:251
- **burnside-lemma**（2）：counting-basics:91・counting-basics:191
- **centroid-decomposition**（4）：rerooting:178・small-to-large:303・tree-edge-contribution:160・tree-edge-contribution:178
- **chromatic-number**（2）：small-graph-brute-force:106・small-graph-brute-force:134
- **cht**（1）：reformulation:106
- **circle-geometry**（1）：geometry-precision:301
- **complement-graph-bfs**（3）：linked-list:144・bfs:167・graph-basics:98
- **convex-hull**（5）：argument-sort:288・geometry-precision:280・geometry-vectors:55・geometry-vectors:237・manhattan-chebyshev:248
- **convolution-ntt**（4）：acl-reading:116・crt:136・mod-arithmetic:139・modint:136
- **counting-bijection**（5）：counting-mindset:52・lattice-paths:51・lattice-paths:178・stars-and-bars:145・stars-and-bars:167
- **counting-dedup**（5）：recursive-enumeration:197・counting-mindset:162・multinomial-coefficient:63・multinomial-coefficient:185・lcs:152
- **counting-labeled-graphs**（1）：binomial-precompute:292
- **cpp-environment**（14）：recursion-structure:133・cpp-initialization:113・cpp-integer-overflow:237・cpp-macros-template-file:57・cpp-macros-template-file:203・cpp-macros-template-file:210・cpp-undefined-behavior:45・cpp-undefined-behavior:53・cpp-undefined-behavior:290・cpp-undefined-behavior:291・cpp-views-cpp23:279・connected-components:109・cycle-detection:116・tree-diameter:229
- **cpp-reverse-index**（1）：acl-reading:310
- **degree-sqrt**（2）：graph-basics:115・symmetry-pigeonhole-casework:109
- **difference-constraints**（1）：weighted-union-find:302
- **difference-sequence**（5）：imos:121・imos:208・run-length-encoding:75・run-length-encoding:157・invariant:140
- **digit-dp-advanced**（4）：digit-dp:132・digit-dp:178・digit-dp:218・memoized-recursion:159
- **dilworth-path-cover**（2）：dp-dag:157・scc:190
- **divide-and-conquer**（3）：recursion-structure:156・inversion-number:133・monotonic-stack:298
- **divisor-inclusion-exclusion**（6）：counting-mindset:111・harmonic-sum:151・harmonic-sum:286・integer-root:158・sigma-manipulation:187・kmp:175
- **dp-dimension-reduction**（3）：dp-state-design:203・dp-state-design:319・knapsack-01:167
- **dp-phase**（1）：dp-state-design:318
- **dp-segment-tree**（5）：dp-sequence-partition:125・dp-sequence-partition:177・monotonic-stack:185・segment-tree-on-values:110・segment-tree:227
- **dp-speedup-overview**（5）：dp-basics:156・dp-basics:187・dp-prefix-sum:301・dp-sequence-partition:177・matrix-power:391
- **dynamic-dp**（2）：matrix-power:229・matrix-power:390
- **dynamic-tree**（1）：small-to-large:304
- **euler-path**（2）：graph-basics:81・euler-tour:62
- **euler-phi**（2）：exponent-mod:117・spf-sieve:103
- **exchange-argument**（13）：event-sort:115・greedy-basics:160・greedy-basics:173・greedy-basics:185・interval-scheduling:68・interval-scheduling:136・lexicographic-greedy:167・sorting-techniques:65・sorting-techniques:162・bracket-sequence:82・bracket-sequence:157・string-basics:145・leaf-first:53
- **exchange-argument-dp**（2）：knapsack-01:215・subset-sum:110
- **expectation-linear-equations**（3）：expected-value-dp:127・expected-value-dp:324・dp-order:58
- **expectation-of-square**（2）：linearity-of-expectation:198・linearity-of-expectation:306
- **expectation-tail-sum**（3）：counting-mindset:111・linearity-of-expectation:199・linearity-of-expectation:304
- **game-retrograde-analysis**（7）：game-basics:71・game-basics:234・game-basics:244・minimax:188・minimax:287・dp-order:59・topological-sort:137
- **gaussian-elimination**（2）：bit-full-search:188・prime-exponent-vector:158
- **gcd-properties**（2）：gcd-lcm:124・gcd-lcm:164
- **generating-function-counting**（2）：multinomial-coefficient:120・stars-and-bars:166
- **graph-construction**（3）：warshall-floyd:193・construction:174・tree-construction:189
- **graph-modeling**（3）：bipartite-graph:141・connected-components:129・extended-dijkstra:397
- **grid**（1）：grid-graph:176
- **grundy-number**（7）：game-basics:73・game-basics:243・minimax:285・nim:114・nim:176・spf-sieve:95・trie:184
- **hadamard-transform**（1）：nim:154
- **hash-safety**（5）：meet-in-the-middle:158・cpp-container-idioms:232・stl-containers:123・hashing-for-sets:142・hashing-for-sets:262
- **inclusion-exclusion**（14）：prefix-sum-2d:74・prefix-sum-2d:167・counting-basics:53・counting-basics:170・counting-basics:190・counting-mindset:111・counting-mindset:185・probability-basics:78・stars-and-bars:81・stars-and-bars:157・stars-and-bars:166・complement:70・complement:107・complement:137
- **inclusion-exclusion-dp**（2）：lattice-paths:112・lattice-paths:176
- **inline-dp**（1）：dp-prefix-sum:300
- **insertion-dp**（5）：counting-fix-order:163・multinomial-coefficient:139・probability-symmetry:192・dp-basics:183・dp-prefix-sum:133
- **interval-dp**（8）：minimax:128・dp-basics:179・dp-order:76・dp-sequence-partition:88・dp-sequence-partition:174・lcs:179・memoized-recursion:158・palindrome:141
- **interval-dp-advanced**（1）：tree-construction:102
- **k-shortest-paths**（1）：dijkstra:220
- **knapsack-undo**（2）：knapsack-01:214・subset-sum:161
- **konig-theorem**（2）：bipartite-graph:170・tree-bipartite:142
- **kth-value**（8）：binary-search-answer:165・binary-search:178・fractional-binary-search:217・greedy-priority-queue:143・greedy-priority-queue:192・two-pointers:147・kth-element:166・reformulation:59
- **lazy-segment-tree-patterns**（3）：inversion-number:135・lazy-segment-tree:155・lazy-segment-tree:302
- **lgv-lemma**（1）：lattice-paths:177
- **library-design**（2）：cpp-macros-template-file:250・modint:142
- **linear-recurrence-fast**（2）：matrix-power:284・matrix-power:387
- **lowlink**（8）：cycle-detection:161・dfs:129・graph-basics:81・namori-graph:189・scc:115・scc:199・scc:267・shortest-path-dag:187
- **matrix-tree-theorem**（1）：small-graph-brute-force:133
- **max-flow**（2）：acl-reading:114・grid-graph:122
- **merge-process-tree**（5）：union-find-applications:201・minimum-spanning-tree:214・union-find-connectivity:165・small-to-large:247・small-to-large:301
- **merge-sort-tree**（3）：offline-queries:177・offline-queries:268・segment-tree-on-values:265
- **method-comparison**（2）：warshall-floyd:292・zero-one-bfs:269
- **mex**（1）：ordered-set:96
- **miller-rabin**（8）：divisor-count-bound:106・divisor-count-bound:207・divisor-enum:153・exponent-mod:167・prime-factorization:132・segmented-sieve:154・spf-sieve:148・spf-sieve:155
- **min-cost-flow**（3）：acl-reading:115・dijkstra:202・dijkstra:221
- **mo-algorithm**（6）：inversion-number:134・offline-queries:267・hashing-for-sets:111・hashing-for-sets:261・euler-tour:188・euler-tour:319
- **mobius-function**（3）：sieve-eratosthenes:126・spf-sieve:103・kmp:186
- **modular-shortest-path**（5）：extended-dijkstra:396・zero-one-bfs:152・digit-and-mod:93・digit-and-mod:210・digit-and-mod:217
- **monge**（1）：dp-sequence-partition:156
- **multiplicative-function**（1）：floor-quotient-enum:101
- **multiplicative-order**（3）：exponent-mod:72・exponent-mod:166・exponent-mod:195
- **notation**（30）：coupon-collector:45・expected-value-dp:54・linearity-of-expectation:51・probability-symmetry:49・base-conversion:47・crt:49・digit-and-mod:49・divisor-count-bound:47・divisor-enum:50・exponent-mod:47・ext-gcd:53・floor-quotient-enum:49・floor-sum:52・gcd-lcm:50・geometric-series-mod:49・harmonic-sum:51・integer-division:53・integer-root:47・matrix-power:57・mod-arithmetic:47・mod-inverse:46・mod-pow:48・modint:44・prime-exponent-vector:49・prime-factorization:49・proof-patterns:49・segmented-sieve:50・sieve-eratosthenes:48・sigma-manipulation:49・spf-sieve:48
- **offline-dynamic-connectivity**（2）：union-find-connectivity:146・union-find-connectivity:266
- **optimal-strategy-expectation**（3）：expected-value-dp:174・minimax:286・rational-mod:130
- **parallel-binary-search**（4）：binary-search-answer:167・offline-queries:118・union-find-connectivity:165・union-find-connectivity:268
- **parsing**（4）：stack-techniques:160・bracket-sequence:84・bracket-sequence:171・string-basics:199
- **partially-persistent-union-find**（2）：union-find:196・union-find-connectivity:120
- **partizan-games**（2）：nim:124・nim:177
- **permutation-parity**（3）：multinomial-coefficient:187・multinomial-coefficient:218・parity:140
- **persistent-data-structures**（4）：offline-queries:176・offline-queries:268・stack-techniques:123・stack-techniques:157
- **project-selection**（2）：bipartite-graph:171・grid-graph:124
- **randomized**（2）：cpp-math-functions:225・hashing-for-sets:262
- **reflection-principle**（5）：binomial-precompute:94・lattice-paths:91・lattice-paths:175・bracket-sequence:79・bracket-sequence:120
- **reverse-index-constraints**（1）：complexity-estimation:68
- **rollback-union-find**（5）：stack-techniques:158・union-find-applications:203・union-find:131・union-find:196・union-find-connectivity:146
- **root-path-dfs**（2）：minimax:150・tree-imos:94
- **segment-tree-beats**（2）：interval-set:249・lazy-segment-tree:303
- **segment-tree-graph**（1）：extended-dijkstra:395
- **segment-tree-monoids**（7）：acl-reading:206・segment-tree-on-values:136・segment-tree:231・rotation-transform:154・bracket-sequence:81・bracket-sequence:146・rolling-hash:174
- **slope-trick**（5）：greedy-priority-queue:163・greedy-priority-queue:193・median-absolute:187・ternary-search:164・top-k-multiset:206
- **spanning-tree-advanced**（3）：manhattan-chebyshev:250・minimum-spanning-tree:163・minimum-spanning-tree:215
- **sparse-table**（9）：bitwise-independence:103・doubling:183・prefix-sum:177・monotonic-stack:288・segment-tree:313・interactive:159・suffix-array:102・suffix-array:286・lca:255
- **sqrt-decomposition**（4）：lazy-segment-tree:303・segment-tree-on-values:175・segment-tree-on-values:264・floor-quotient-enum:157
- **static-top-tree**（2）：tree-dp:332・hld:133
- **steiner-tree**（1）：minimum-spanning-tree:207
- **stern-brocot**（1）：gcd-lcm:166
- **stress-testing**（7）：greedy-basics:133・interval-scheduling:122・cpp-math-functions:248・cpp-undefined-behavior:272・proof-patterns:179・construction:154・fix-variable:139
- **string-automaton-dp**（6）：digit-dp:219・dp-state-design:136・dp-state-design:317・matrix-power:159・matrix-power:316・kmp:210
- **subsequence-and-substring**（2）：string-basics:87・subsequence-matching:168
- **subsequence-dp**（5）：dp-reconstruction:191・dp-reconstruction:270・lcs:166・lcs:321・subsequence-matching:165
- **subset-enumeration-dp**（2）：recursive-enumeration:194・bit-dp:293
- **suffix-automaton**（2）：suffix-array:264・suffix-array:290
- **sweep-line-2d**（7）：coordinate-compression:114・event-sort:126・event-sort:147・fenwick-tree:162・fenwick-tree:184・offline-queries:98・offline-queries:269
- **tree-centroid**（3）：tree-dp:174・tree-diameter:189・tree-diameter:311
- **tree-degree**（5）：ternary-search:250・tree-basics:80・tree-basics:176・tree-construction:124・tree-construction:190
- **tree-dp-square**（2）：knapsack-01:216・tree-dp:329
- **tree-isomorphism**（1）：small-graph-brute-force:135
- **tree-path**（4）：complete-binary-tree:164・hld:133・lca:99・tree-distance:134
- **tree-ratio-greedy**（1）：leaf-first:168
- **twelvefold-way**（7）：counting-basics:160・counting-basics:189・multinomial-coefficient:151・multinomial-coefficient:172・multinomial-coefficient:186・stars-and-bars:161・stars-and-bars:165
- **two-sat**（4）：acl-reading:113・bipartite-graph:172・scc:189・scc:268
- **wavelet-matrix**（2）：kth-element:76・segment-tree-on-values:265
- **xor**（2）：bit-operations:179・bitwise-independence:211
- **xor-basis**（4）：bit-operations:179・bitwise-independence:208・nim:178・prime-exponent-vector:158
- **zeta-mobius-divisor**（3）：harmonic-sum:125・harmonic-sum:188・harmonic-sum:286
- **zeta-mobius-subset**（2）：bit-operations:152・bit-dp:294

（469 箇所、リンク先 130 ページ）

## 2. 内容の重なり（後から書く側が、先に書かれたページへリンクして短くする）

決定事項（ページの front matter の節）により、後から書く側が先に書かれたページの節へリンクして短くする。両方とも draft のものは、次に直すときにどちらかを短くする。

| 先に書かれた側（b1） | 重なる相手 | 申し送り |
| --- | --- | --- |
| bitwise-independence#split-by-top-bit | binary-trie#implicit | binary-trie を書くときにこちらへリンクする。abc281_f は binary-trie の例題で、bitwise-independence では力試し |
| cpp-views-cpp23#reference-tuples | cpp-structured-bindings#enumerate-reference | 構造化束縛の側をリンクにして短くする |
| ternary-search の flat-pitfall・convexity | circle-geometry の ternary-search-caveats（黄） | circle-geometry を書くときにこちらへリンクする |
| crt | ext-gcd | crt は「2 式の統合」の形に絞り、一次合同式の一般論は ext-gcd へリンクした。ext-gcd の側と重なりを確かめる |
| dp-dag（最短路の本数の節） | shortest-path-dag#count-paths | dp-dag は「距離の順が DAG の順」の見方と配り方に絞り、shortest-path-dag へ送っている。shortest-path-dag は同時に数える方法を dp-dag へリンクしている |
| minimum-spanning-tree（辺の重みの種類が少ないとき） | union-find-applications#multiple-uf | 式の導き方（MST 側）と Union-Find の持ち方（UF 側）で書き分けた。片方をリンクだけにしてもよい |
| prefix-sum-counting（後ろからの累積） | digit-and-mod#suffix-remainder | どちらに詳しく書くか未定。prefix-sum-counting は手順の要点だけにした |
| modint | acl-reading#modint・#modint-val | modint は「余りから元の値は分からない」側に絞り、`.val()` と比較演算子の話は acl-reading へリンクした |
| probability-symmetry | linearity-of-expectation#pairs | probability-symmetry はペアの 1/2 の理由と位置以外の対称性に絞り、転倒数は向こうへリンクした |
| cpp-algorithms | cpp-container-idioms#member-lower-bound | set の lower_bound の計測は cpp-container-idioms に寄せ、cpp-algorithms は 1 行とリンク |
| tree-construction（abc252_g の方針） | interval-dp-advanced | abc252_g は interval-dp-advanced の例題。tree-construction の方針の記述（区間 DP の 2 種類の状態と兄弟の番号の条件）と食い違わないか確かめる |
| global-offset#to-lazy-segment-tree | lazy-segment-tree | 全体への操作を区間への操作に広げる話が重なる。どちらに詳しく書くかは未定（両方とも draft） |
| steiner-subtree（辺の条件 1 ≤ c[v] ≤ K − 1） | tree-edge-contribution | tree-edge-contribution の内容と合うかを、その執筆時に確かめる |
| tree-imos（根から y 世代までの数える形） | root-path-dfs | root-path-dfs の本文でこの形を扱うかを確かめる |
| nim | grundy-number | 逆形 Nim・補充の候補（arc105_d・arc091_d）の配分を grundy-number を書くときに決める |

### 2.1 練習の答えが本文で見えてしまう

本文の説明が練習・力試しの解き方とほぼ同じもの。問題を例題に上げるか、本文の例を一般の形に弱めるかをメインが決める。

- connected-components：「座標や値を頂点にして成分を考える」節が力試し abc131_f の考え方（完全二部グラフ）をそのまま説明している
- trie：節 dp-on-trie の段落が abc377_g の解き方とほぼ同じ
- dp-mod-state：本文の節に abc195_e の答えになるコードがある。game-basics#turn も同じ形

## 3. 記法の提案（E1。start/notation を書くときにまとめる）

| 提案 | 出したページ |
| --- | --- |
| パスカルの三角形の表を $\mathrm{C}[n][k]$ と書く | binomial-coefficient |
| AND・OR は、数式では `\text{ AND }`、コードの話ではバッククォートの `&` | bit-operations |
| 擬似コードの中の `\|x\|` と本文の $\lvert \cdot \rvert$ の使い分け | bitwise-independence |
| 部分文字列を整数とみた値 $\mathrm{val}(S[l, r))$、連結 $\mathrm{concat}(x, y)$、桁数 $d(y)$ | digit-and-mod |
| 木の $\mathrm{ord}[t]$（$\mathrm{ord}[\mathrm{in}[v]] = v$）と $\mathrm{out}[v]$ の半開区間の流儀 | euler-tour |
| グリッドの (i, j) は i 行目・j 列目、移動の配列は di・dj | grid-graph |
| 値の上限の文字（M は辺数に使うので、値の上限は V などにする） | harmonic-sum（このページは front matter を M に直した。記法を決めたら合わせる） |
| 反転した文字列 $S^R$ | lcs |
| 状態ベクトルは列ベクトル、遷移は v' = Av（a_ij は j から i への係数） | matrix-power |
| 余事象 $\overline{A}$・条件付き確率 $P(A \mid B)$ | probability-basics（notation.md#probability へリンク済み） |
| Iverson の記法 $[P]$ | sigma-manipulation |
| 偏角の範囲の既定（[0, 2π)）と比較関数の名前（cross・half・arg_less） | argument-sort |
| 量の単位（「40 MB」の空白、メモリ制限は MiB） | spf-sieve |

## 4. 逆引き（cpp-reverse-index）・早見表への追加

| 行き先 | 追加する行 | 出したページ |
| --- | --- | --- |
| cpp-reverse-index#lookup-types | `bit_ceil`・`__builtin_popcountll`・`mt19937_64 rng(random_device{}())`・`uniform_int_distribution` → cpp-math-functions の bit-functions・builtins・random | cpp-math-functions |
| cpp-reverse-index（コンパイルエラーから引く節） | `deduced conflicting types for parameter` → cpp-templates-constexpr#deduction-failure、`'constexpr' loop iteration count exceeds limit of 262144` → #constexpr、`constraints not satisfied` → #concepts | cpp-templates-constexpr |
| cpp-reverse-index（書き方から引く） | `1e18`・`auto INF = 1e18`・`0x3f3f3f3f`・`memset(d, 0x3f, sizeof d)`・`0uz`・`ll(x)` → cpp-types-literals の各節 | cpp-types-literals |
| cpp-reverse-index#symptoms・interactive | インタラクティブで println・`'\n'` が届かないのは、同期を切る 2 行があるときの話（2 行なしでは届いた）。条件をそろえて書く | cpp-io |
| cpp-container-idioms の 166 行 | リンク先を ordered-set から kth-element か pb-ds の節へ | ordered-set |
| 早見表 | `<bit>` の関数の値と境界の表（cpp-math-functions の bit-functions の表、builtins の 0 を渡したときの表） | cpp-math-functions |
| 早見表 | `max<long long>(a, b)`・`min({a, 3LL, b})`・`constexpr auto T = [] { … }();` | cpp-templates-constexpr |
| 早見表の「INF の候補」 | cpp-types-literals#inf の表（INT_MAX・0x3f3f3f3f・1LL << 60・LLONG_MAX・1e18 と INF + INF） | cpp-types-literals |
| 早見表・使い分け（basics の「巨大な K 回」の行） | 「始点がすべてで K が 1 つなら、写像の繰り返し二乗法で O(N) のメモリで済む」 | doubling |
| 早見表の「外積の値の大きさ」 | research 08 §6.3 の 8×10^18 は各積の上界から足した見積もり。座標の絶対値が 10^9 以下の 3 点なら実際の最大は 4×10^18。「見積もり」と明記するか両方を書く | geometry-vectors |

## 5. 計測値・数値の不一致

research や catalog の数値が手元で再現しなかったもの。ほかのページ・早見表に同じ数値を書くときは、b1 のページの値にそろえる。

- cpp-lambda#speed：std::function の遅さは fib(40) で約 5 倍、木の DFS（完全二分木、2×10^6 頂点）で約 1.5 倍。research・catalog の「fib(35) で約 5 倍・木の DFS で約 1.3 倍」は再現しなかった（fib(35) は短すぎてぶれる）。cpp-reverse-index・cpp-io#tle-causes・早見表に「約 5 倍・約 1.3 倍」と書かない
- cpp-io：println の速さ（research の 2×10^6 行で println 0.20 秒・printf 0.31 秒・cout 0.42 秒）は再現せず、手元の 10^6 行の整数で println 0.04 秒・printf 0.03 秒・cout（同期なし）0.02 秒。set に std::lower_bound は、要素 2×10^5 の set で約 22 秒（g++-13 で約 26 秒）。research の「2×10^4 回で約 2 秒」は set の大きさが書かれていない
- cpp-integer-overflow：research/09 §4.35 の「あふれる行があると正しく書いた行まで 1410065408 になる」は g++-13・g++-15 の -O2 で再現しなかった。逆に、正しい行を先に置くとあふれる行の値が変わることは観測した。cpp-undefined-behavior#breaks-other-lines と食い違わないように書く
- cpp-undefined-behavior：cpp-comparators#less-equal-pitfall の「同じ値が多いと Segmentation fault」は、素の -O2 で同じ値 100 個では落ちなかった（ASan では検出）。要素数で変わると思われるので、cpp-comparators の検証で確かめる
- cpp-types-literals：「値が 10^9 なら double の誤差は 10^-7 程度」（10^9 付近の隣の数との間隔 2^-23 ≈ 1.19×10^-7 からの見積もり）を、geometry-precision の double-precision 節の数値とそろえる
- cpp-environment#stack-depth：tree-traversal の報告では、手元（ulimit -s 8192、g++-15 -std=gnu++23 -O2）で再帰ラムダの DFS がパス状の木の N = 10^5 でも Segmentation fault になった（BFS 順の版は N = 10^6 でも通った）。節の題名は「深さ 2×10^5 で落ちうる」の言い方をやめ、今回「手元の上限・ulimit -s unlimited・非再帰への書き直し」にした。本文の数値は cpp-environment の執筆時に確かめる。AtCoder のスタックの上限は、b1 のどのページも値を書かずに cpp-environment へ回している

## 6. 相手のページを書くときの内容

- hash-safety：mod 2^64 が長さ 1024 程度で衝突する構成（Thue-Morse 列）と出典。「多くの組を比べるとき 1 組あたり約 1/p とみなす根拠と限界」（rolling-hash の #recommended-design・#collision-bound がリンクしている）
- cpp-environment：GCC 15 の -O0 では _GLIBCXX_ASSERTIONS が自動で付くので、手元で範囲外が -O0 のときだけ止まる理由を説明できる（VS Code のビルドタスクは最適化なし。cpp-undefined-behavior から）。Ubuntu の g++ は既定で -fstack-protector-strong が付く（AtCoder で同じかは未確認）
- interactive：フラッシュの条件は cpp-io#flush にそろえる（同期を切る 2 行を書いたら、質問のたびに endl か fflush(stdout)）
- 参考のサイト名：「programming-hiroba」と「プロひろ」の揺れがある（warshall-floyd）。どちらかにそろえる

## 7. この反映でメインに残すこと

decisions.md の手引き A1〜A3・B1・B2 とページの front matter の反映（2026-10-21）で、判断を残したもの。

- **gen_site の作り直し**：sections から pitfalls・choosing・comparison・next-steps を外したので、docs/index/（分野ごとの詳細索引）に古い節が残っている。anchor を変えたのは dp-dag（connections → next-steps）と、choosing を持っていたページ（fenwick-tree・inversion-number・lazy-segment-tree・linked-list・monotonic-stack・segment-tree・stl-containers・union-find・weighted-union-find と stub の binary-trie・merge-sort-tree・mo-algorithm・persistent-data-structures・sparse-table・sqrt-decomposition・sweep-line-2d。いずれも → comparison）。本文の `#choosing` へのリンクは張り替えた
- **coupon-collector の prerequisites**：linearity-of-expectation を足すと、前提のレベルの逆転（基礎 → 水）と order の逆転（330 → 350）、probability-basics の冗長の警告が出るので、足さずに related のままにした。level・order を変えるか、前提にしないかを決める
- **frequency_evidence**：関係しないと判断して外したのは binomial-coefficient（abc476_g）・recursion-structure（abc476_g）・imos（abc465_f。6 次元の累積和）・event-sort（abc467_e。台帳になく関係も薄い）。報告で疑問が出たが、台帳の approach からページの手法を使うと読めるので残したもの：bit-operations（abc476_g の popcount）、gcd-lcm（abc460_e。gcd で数える）、imos（abc453_e・abc464_e）、contribution（5 問とも寄与・主客転倒）、construction、coordinate-compression（abc467_f）、grid-graph（abc453_d・abc460_d）、monotonic-stack（abc480_g）、reformulation、stack-techniques（abc454_d）、topological-sort（abc478_e）、tree-distance（abc451_e）、tree-edge-contribution（abc479_e。問いの確認待ち）、dp-grid（abc476_f）、dp-prefix-sum。台帳にないので確かめられなかったもの：binary-search の abc476_d・abc480_d・abc480_e、construction の abc453_f・abc474_d、ordered-set の abc475_e（abc466_f も関係は未確認）、reformulation の abc475_e。工程10の見直しで扱う
- **level_evidence**：dp-sequence-partition は abc370_e（1453）が水の根拠になる（front matter に level_evidence はないので catalog 側の記録）
- **aliases**：stars-and-bars の 'H(n,k)' を ₖHₙ に変えた（本文の ${}_k\mathrm{H}_n$ と引数の順をそろえた）
