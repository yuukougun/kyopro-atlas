# 節へのリンクへの張り替え候補

候補は 333 件（basics 38・thinking 10・dp 58・misc 1・graph 45・geometry 7・tree 17・string 27・ds 31・cpp 12・math 33・comb 48・patterns 6）。

相手のページが stub だったので anchor を付けずにページへ張ったリンクのうち、相手が draft 以上になり、張り替え先の anchor が相手の本文の見出し（{#…}）に実在するもの。2026-10-22 の本文で行番号を確かめた。

- 資料：planning/batches/b1/handoff.md §1（1.1〜1.3）、planning/batches/b3/handoff-b2b3.md §1（1.1・1.2）、b1・b2・b3 の各ページの報告の同種の申し送り
- 「行」は張り替える行の目安（今の本文の行番号）。「今のリンク」はその行にある、anchor のないページへのリンク。張り替えは、リンク先の `.md` の後ろに `#anchor` を足すだけ
- 申し送りの anchor 案が相手の見出しにないもの・文と合わないものは、相手の見出しから選び直し、根拠にそう書いた
- 候補から外したもの：要点の「前提」の行（前提はページへのリンクのままにする）、「この節は〜を前提にする」でページ全体を指す文、使い分けの表などでページ全体を指す行、同じ文のすぐ後ろに相手の節へのリンクがすでにある行、相手がまだ stub のもの、張り替えでなくリンク先のページを替える・リンクを新しく足す提案（例：string-automaton-dp の表を dp-phase#matched-prefix へ、multiplicative-order#count-by-order から euler-phi#divisor-sum へ）
- 呼び名が相手の題名と違うと申し送りにあるもの（tree-degree の「ラベル付き木の数と Prüfer 列」、lis の「根からのパスを持つ DFS」、tree-basics・tree-construction の「次数と次数列」「次数と木」）は、張り替えのときに文言もそろえるかを決める

## basics

| 元のページ | 行 | 今のリンク | 張り替え先 | 根拠 |
| --- | --- | --- | --- | --- |
| docs/basics/binary-search-answer.md | 165 | `[K 番目の値を求める](../basics/kth-value.md)` | `kth-value#why-count` | x 以下の個数を数えて二分探索（b1 1.3・b2b3 1.1） |
| docs/basics/bit-full-search.md | 188 | `[掃き出し法](../math/gaussian-elimination.md)` | `gaussian-elimination#mod-2` | スイッチと電球（b1 1.3・b2b3 1.1） |
| docs/basics/bit-operations.md | 146 | `[部分集合を列挙する DP](../dp/subset-enumeration-dp.md)` | `subset-enumeration-dp#why-3n` | 3 通りの数え方（b1 handoff で名指し・b2b3 1.1） |
| docs/basics/bit-operations.md | 178 | `[部分集合を列挙する DP](../dp/subset-enumeration-dp.md)` | `subset-enumeration-dp#submask-loop` | 3^N の列挙を DP の遷移に（b2b3 1.1） |
| docs/basics/bit-operations.md | 179 | `[XOR 基底](../math/xor-basis.md)` | `xor-basis#insert` | 掃き出し法で作れる値を調べる（b2b3 1.1） |
| docs/basics/bitwise-independence.md | 103 | `[Sparse Table](../ds/sparse-table.md)` | `sparse-table#idempotent` | 区間の AND・OR は冪等なので Sparse Table（b1 1.3） |
| docs/basics/bitwise-independence.md | 142 | `[Binary Trie](../ds/binary-trie.md)` | `binary-trie#build` | 同じ木を明示的に作るのが Binary Trie（b1 1.2・b2b3 1.1） |
| docs/basics/bitwise-independence.md | 170 | `[Binary Trie](../ds/binary-trie.md)` | `binary-trie#implicit` | この再帰は上位ビットの二分木をたどるのと同じ（b1 1.2・b2b3 1.1 の #implicit） |
| docs/basics/bitwise-independence.md | 209 | `[Binary Trie](../ds/binary-trie.md)` | `binary-trie#xor-min-max` | 追加・削除しながら x との XOR の最小・最大（b1 1.2・b2b3 1.1） |
| docs/basics/complexity-estimation.md | 59 | `[順列全探索](../basics/bit-full-search.md)` | `bit-full-search#permutations` | 制約の表の順列全探索（b1 handoff で名指し・1.1） |
| docs/basics/complexity-estimation.md | 138 | `[第 2 種スターリング数とベル数](../comb/bell-number.md)` | `bell-number#size` | 組分けの数の見積もり（b1 1.3・b2b3 1.1） |
| docs/basics/complexity-estimation.md | 149 | `[bitset による高速化](../misc/bitset-speedup.md)` | `bitset-speedup#word-parallel` | 64 個ずつで約 1/64、次数は変わらない（b1 1.3） |
| docs/basics/complexity-estimation.md | 150 | `[入出力と定数倍](../cpp/cpp-io.md)` | `cpp-io#tle-causes` | 入出力で TLE になる書き方（b1 1.1） |
| docs/basics/greedy-basics.md | 122 | `[答えで二分探索](../basics/binary-search-answer.md)` | `binary-search-answer#greedy-check` | 同じ問題を答えの二分探索で、判定は貪欲（b1 1.1） |
| docs/basics/greedy-basics.md | 160 | `[交換論法](../basics/exchange-argument.md)` | `exchange-argument#adjacent-swap` | 隣り合う 2 つを入れ替えたときの差（b1 1.3） |
| docs/basics/greedy-basics.md | 173 | `[交換論法](../basics/exchange-argument.md)` | `exchange-argument#adjacent-swap` | 効果が順番で変わるなら比較関数を作る（b1 1.3） |
| docs/basics/greedy-basics.md | 185 | `[交換論法](../basics/exchange-argument.md)` | `exchange-argument#adjacent-swap` | 入れ替えたときの差から比較関数（b1 1.3） |
| docs/basics/imos.md | 123 | `[差分列への言い換え](../basics/difference-sequence.md)` | `difference-sequence#min-operations` | 最小回数や可否を考える問題（b1 1.3） |
| docs/basics/imos.md | 210 | `[差分列への言い換え](../basics/difference-sequence.md)` | `difference-sequence#min-operations` | 区間の操作の最小回数や可否（b1 1.3） |
| docs/basics/interval-scheduling.md | 136 | `[交換論法](../basics/exchange-argument.md)` | `exchange-argument#adjacent-swap` | 隣り合う 2 つの順を入れ替えても悪くならない（b1 1.3） |
| docs/basics/lexicographic-greedy.md | 83 | `[部分列の判定](../string/subsequence-matching.md)` | `subsequence-matching#next-occurrence` | 次の出現位置の表を後ろから作る（b1 1.1 の案 #lexicographically-smallest より文に合う） |
| docs/basics/lexicographic-greedy.md | 167 | `[交換論法](../basics/exchange-argument.md)` | `exchange-argument#concatenation` | a + b と b + a で比べる（b1 1.3） |
| docs/basics/median-absolute.md | 121 | `[マンハッタン距離と 45 度回転](../geometry/manhattan-chebyshev.md)` | `manhattan-chebyshev#rotate-45` | チェビシェフ距離を 45 度回転でマンハッタンに（b1 1.1 の案 #axis-independence より文に合う） |
| docs/basics/meet-in-the-middle.md | 142 | `[bitset](../misc/bitset-speedup.md)` | `bitset-speedup#subset-sum-shift` | 表の「DP を bitset で O(NT/64)」（b1 1.3） |
| docs/basics/meet-in-the-middle.md | 158 | `[ハッシュの衝突と安全な設計](../string/hash-safety.md)` | `hash-safety#unordered-map` | unordered_map を衝突させる入力（b1 1.3） |
| docs/basics/periodicity.md | 51 | `[鳩の巣原理](../thinking/symmetry-pigeonhole-casework.md)` | `symmetry-pigeonhole-casework#pigeonhole` | S + 1 個の中に同じ状態が 2 回（b1 1.1） |
| docs/basics/prefix-sum-2d.md | 163 | `[平面走査](../ds/sweep-line-2d.md)` | `sweep-line-2d#intervals-as-points` | 同じ「区間を点と見る」言い換えのまま（b1 1.1 の BIT の行と同じ文。b1 1.3） |
| docs/basics/prefix-sum-2d.md | 204 | `[平面走査](../ds/sweep-line-2d.md)` | `sweep-line-2d#rectangle-count` | 一点の更新と長方形の和を先読みで（b1 1.3） |
| docs/basics/recursion-structure.md | 142 | `[ラムダ式](../cpp/cpp-lambda.md)` | `cpp-lambda#self-argument` | 自分自身を引数で受け取る再帰ラムダ（b1 1.1 の案 #recursive-lambda より文に合う） |
| docs/basics/recursion-structure.md | 156 | `[分割統治](../basics/divide-and-conquer.md)` | `divide-and-conquer#crossing` | 左右を解いてからまたぐものを数える（b1 1.3・b2b3 1.1） |
| docs/basics/recursive-enumeration.md | 104 | `[ベル数](../comb/bell-number.md)` | `bell-number#size` | B_10 = 115975 の見積もり（b1 1.2・b2b3 1.1） |
| docs/basics/recursive-enumeration.md | 194 | `[部分集合を列挙する DP](../dp/subset-enumeration-dp.md)` | `subset-enumeration-dp#fix-minimum` | 最小番号の人を含む組から選ぶ（b1 1.3） |
| docs/basics/sorting-techniques.md | 65 | `[交換論法](../basics/exchange-argument.md)` | `exchange-argument#adjacent-swap` | 2 つの比較から並べる順を決める（b1 1.3） |
| docs/basics/sorting-techniques.md | 162 | `[交換論法](../basics/exchange-argument.md)` | `exchange-argument#adjacent-swap` | 2 つを比べてどちらを先にするか（b1 1.3） |
| docs/basics/ternary-search.md | 204 | `[円と幾何の最適化](../geometry/circle-geometry.md)` | `circle-geometry#geometry-optimization` | 凸と言い切れない幾何の最適化は候補の列挙（b1 1.2） |
| docs/basics/ternary-search.md | 249 | `[円と幾何の最適化](../geometry/circle-geometry.md)` | `circle-geometry#min-enclosing-circle` | 2 点を直径とする円と 3 点の外接円を候補に（b1 1.2 の案 #geometry-optimization より文に合う） |
| docs/basics/ternary-search.md | 250 | `[木の次数列と Prüfer 列](../tree/tree-degree.md)` | `tree-degree#realizable` | 次数が 1 以上で和が 2N − 2 なら木を作れる（b1 1.3） |
| docs/basics/two-pointers.md | 147 | `[K 番目の値](../basics/kth-value.md)` | `kth-value#counting-patterns` | 尺取りで数える（b1 1.3・b2b3 1.1） |

（38 件）

## thinking

| 元のページ | 行 | 今のリンク | 張り替え先 | 根拠 |
| --- | --- | --- | --- | --- |
| docs/thinking/complement.md | 107 | `[包除原理](../comb/inclusion-exclusion.md)` | `inclusion-exclusion#bit-enumeration` | 条件の組を bit 全探索して符号付きで足す（b1 1.3） |
| docs/thinking/contribution.md | 62 | `[Σ の変形](../math/sigma-manipulation.md)` | `sigma-manipulation#swap-order` | 和の順序の入れ替え（b1 1.1） |
| docs/thinking/invariant.md | 48 | `[証明の型](../math/proof-patterns.md)` | `proof-patterns#necessary-sufficient` | 必要条件 → 十分性（b1 1.1） |
| docs/thinking/invariant.md | 140 | `[差分列](../basics/difference-sequence.md)` | `difference-sequence#to-point-operations` | 区間に一律に足す操作を差分列に（b1 1.3） |
| docs/thinking/parity.md | 140 | `[置換の偶奇](../comb/permutation-parity.md)` | `permutation-parity#sign` | swap の回数の偶奇は変わらない（b1 1.3） |
| docs/thinking/reformulation.md | 55 | `[差分列](../basics/difference-sequence.md)` | `difference-sequence#strict-to-weak` | 狭義単調増加を A_i − i で広義に（b1 handoff で名指し・1.2） |
| docs/thinking/reformulation.md | 59 | `[K 番目の値を求める](../basics/kth-value.md)` | `kth-value#why-count` | K 番目に小さい値 ≤ x ⇔ x 以下が K 個以上（b1 1.3・b2b3 1.1） |
| docs/thinking/reformulation.md | 136 | `[l, r)$ に $+1$ する操作は、$d_l$ を $+1$ し $d_r$ を $-1$ する 2 点の操作になる。区間の位置や長さの組み合わせを考える代わりに、差分列の各点をいくつ増減させればよいかを考えればよい。たとえば「区間に $+1$ する操作で、全体を 0 から $a$ にする最小回数」は、$d_i > 0$ の総和になる（左端の $a_{-1} = 0$ とする）。1 回の操作で $+1$ される $d$ は 1 点だけなので、正の部分の総和以上は要る。逆に、左から見て $d_i > 0$ の位置で $d_i$ 本の区間を始め、$d_i < 0$ の位置で $-d_i$ 本を終えれば、その回数で作れる（[差分列](../basics/difference-sequence.md)` | `difference-sequence#min-operations` | 区間に +1 する操作の最小回数（b1 1.3） |
| docs/thinking/reverse-thinking.md | 87 | `[優先度付きキュー](../ds/priority-queue.md)` | `priority-queue#patterns` | 増える候補から毎回最良を取る（b1 1.1 の案 #abc137_d は priority-queue にないので選び直し） |
| docs/thinking/symmetry-pigeonhole-casework.md | 109 | `[次数で分ける](../graph/degree-sqrt.md)` | `degree-sqrt#four-cycles` | 4-サイクルの検出（b1 1.3） |

（10 件）

## dp

| 元のページ | 行 | 今のリンク | 張り替え先 | 根拠 |
| --- | --- | --- | --- | --- |
| docs/dp/bit-dp.md | 164 | `[ゲームの基本](../comb/game-basics.md)` | `game-basics#win-lose` | 各局面の勝ち負けを決める考え方（b1 1.1 の案 #state-design より文に合う） |
| docs/dp/digit-dp.md | 132 | `[桁 DP の応用](../dp/digit-dp-advanced.md)` | `digit-dp-advanced#count-and-sum` | 個数と総和を同時に持つ（b1 1.3・b2b3 1.1） |
| docs/dp/digit-dp.md | 178 | `[桁 DP の応用](../dp/digit-dp-advanced.md)` | `digit-dp-advanced#multiple-numbers` | 2 つの数のそれぞれに上限（b1 1.3・b2b3 1.1。繰り上がりは同じ文の後半） |
| docs/dp/digit-dp.md | 219 | `[文字列の照合状態を持つ DP](../string/string-automaton-dp.md)` | `string-automaton-dp#matching-state` | パターンとの照合を状態にする（b1 1.3・b2b3 1.1） |
| docs/dp/dp-basics.md | 160 | `[貪欲法](../basics/greedy-basics.md)` | `greedy-basics#when-greedy-fails` | 貪欲が正しくないとき DP へ（b1 1.1） |
| docs/dp/dp-basics.md | 183 | `[挿入 DP](../dp/insertion-dp.md)` | `insertion-dp#relative-rank` | 表の「相対順位」（b1 1.3） |
| docs/dp/dp-dag.md | 156 | `[bitset による高速化](../misc/bitset-speedup.md)` | `bitset-speedup#reachability` | 到達可能性の大量のクエリ（b1 1.2） |
| docs/dp/dp-grid.md | 74 | `[包除 DP](../comb/inclusion-exclusion-dp.md)` | `inclusion-exclusion-dp#first-obstacle` | 最初に通る壁で分ける（b2b3 1.1） |
| docs/dp/dp-grid.md | 93 | `[bitset による高速化](../misc/bitset-speedup.md)` | `bitset-speedup#subset-sum-shift` | 集合をシフトと OR で（b1 1.3） |
| docs/dp/dp-grid.md | 292 | `[包除 DP](../comb/inclusion-exclusion-dp.md)` | `inclusion-exclusion-dp#first-obstacle` | 盤面が大きく壁が少ない（b2b3 1.1） |
| docs/dp/dp-mod-state.md | 130 | `[ゲームの基本と勝敗の DP](../comb/game-basics.md)` | `game-basics#win-lose` | 必勝・必敗を前提にする節（b1 1.1） |
| docs/dp/dp-order.md | 58 | `[期待値の方程式を解く](../comb/expectation-linear-equations.md)` | `expectation-linear-equations#linear-system` | 連立方程式を解く（b1 1.3・b2b3 1.1） |
| docs/dp/dp-order.md | 76 | `[区間 DP](../dp/interval-dp.md)` | `interval-dp#by-length` | 表の「区間の長さ順」（b1 1.3） |
| docs/dp/dp-phase.md | 117 | `[部分列 DP](../dp/subsequence-dp.md)` | `subsequence-dp#positions-or-strings` | できる文字列の種類を数えるなら部分列 DP（b2b3 1.1） |
| docs/dp/dp-phase.md | 235 | `[部分列 DP](../dp/subsequence-dp.md)` | `subsequence-dp#positions-or-strings` | 位置の組の数と文字列の種類の数（b2b3 1.1） |
| docs/dp/dp-prefix-sum.md | 133 | `[挿入 DP](../dp/insertion-dp.md)` | `insertion-dp#prefix-sum` | 相対順位の DP も遷移元が範囲（b1 1.3） |
| docs/dp/dp-prefix-sum.md | 164 | `[l..r))$ を 2 つの累積 min から作ることはできないので、任意の範囲の min なら[セグメント木](../dp/dp-segment-tree.md)` | `dp-segment-tree#values-on-segment-tree` | [セグメント木]：任意の範囲の min（b1 1.3。同じ行に 2 つあるうちの前） |
| docs/dp/dp-prefix-sum.md | 164 | `[スライド最小値](../dp/dp-segment-tree.md)` | `dp-segment-tree#dp-sliding-window` | [スライド最小値]：範囲が一方向に動く（b1 1.3。同じ行の後ろ） |
| docs/dp/dp-prefix-sum.md | 170 | `[i - K, i)$ は左端も動くので接頭辞ではなく、累積 min $\min(\mathrm{dp}[0..i))$ から $[0, i - K)$ の分を取り除く方法がない。範囲は右へ単調に動くので、スライド最小値（両端キュー）で 1 回ならし $O(1)$、セグメント木なら $O(\log N)$ で取る（[セグメント木・スライド最小値による DP の高速化](../dp/dp-segment-tree.md)` | `dp-segment-tree#dp-sliding-window` | 範囲が右へ単調に動くのでスライド最小値（b1 1.3） |
| docs/dp/dp-reconstruction.md | 87 | `[幅優先探索](../graph/bfs.md)` | `bfs#path-restoration` | BFS で最短路を復元するのと同じ（b1 1.1） |
| docs/dp/dp-reconstruction.md | 105 | `[辞書順の貪欲](../basics/lexicographic-greedy.md)` | `lexicographic-greedy#feasibility` | 残りで条件を満たせるかを判定して先頭から決める（b1 1.1 の案 #kth は文と合わないので選び直し） |
| docs/dp/dp-reconstruction.md | 191 | `[部分列 DP](../dp/subsequence-dp.md)` | `subsequence-dp#kth-subsequence` | 部分列の個数で K 番目（b1 1.3・b2b3 1.1） |
| docs/dp/dp-reconstruction.md | 192 | `[幅優先探索](../graph/bfs.md)` | `bfs#path-restoration` | 遷移元を記録して経路を復元（b1 1.1） |
| docs/dp/dp-reconstruction.md | 270 | `[部分列 DP](../dp/subsequence-dp.md)` | `subsequence-dp#shortest-non-subsequence` | ARC081 E の方針（b1 1.3・b2b3 1.1） |
| docs/dp/dp-sequence-partition.md | 125 | `[セグメント木・スライド最小値による DP の高速化](../dp/dp-segment-tree.md)` | `dp-segment-tree#dp-sliding-window` | 範囲の両端が単調に動く（b1 1.3） |
| docs/dp/dp-state-design.md | 136 | `[照合オートマトン上の DP](../string/string-automaton-dp.md)` | `string-automaton-dp#kmp-automaton` | 何文字目まで一致しているかだけを持つ（b1 1.3・b2b3 1.1） |
| docs/dp/dp-state-design.md | 217 | `[重複の除き方](../comb/counting-dedup.md)` | `counting-dedup#in-dp` | 状態は決め方から 1 つに決まる形に（b1 1.2） |
| docs/dp/dp-state-design.md | 317 | `[照合オートマトン上の DP](../string/string-automaton-dp.md)` | `string-automaton-dp#kmp-automaton` | 一致している長さを持つ（b1 1.3・b2b3 1.1） |
| docs/dp/exchange-argument-dp.md | 46 | `[交換論法](../basics/exchange-argument.md)` | `exchange-argument#then-dp` | 交換論法で決めた順に並べてから DP（b2 exchange-argument-dp の報告・b2b3 1.1） |
| docs/dp/inline-dp.md | 190 | `[セグメント木・スライド最小値による DP の高速化](../dp/dp-segment-tree.md)` | `dp-segment-tree#values-on-segment-tree` | 1 点を更新し範囲の最大・最小から貰う（b2 inline-dp の報告） |
| docs/dp/inline-dp.md | 194 | `[遅延セグメント木の載せ方の型](../ds/lazy-segment-tree-patterns.md)` | `lazy-segment-tree-patterns#design-steps` | 遅延セグメント木に載せる値と作用の設計（b2 inline-dp の報告） |
| docs/dp/knapsack-01.md | 167 | `[状態の削減](../dp/dp-dimension-reduction.md)` | `dp-dimension-reduction#dp-swap-key-value` | 添字と値の入れ替え（b1 1.3） |
| docs/dp/knapsack-01.md | 214 | `[戻す DP](../dp/knapsack-undo.md)` | `knapsack-undo#undo-by-subtraction` | 品物を取り除く逆の更新（b1 1.3） |
| docs/dp/knapsack-01.md | 216 | `[二乗の木 DP](../dp/tree-dp-square.md)` | `tree-dp-square#size-bounded` | 選んだ個数の範囲を部分木のサイズまでに（b1 1.3） |
| docs/dp/knapsack-01.md | 217 | `[分割統治](../basics/divide-and-conquer.md)` | `divide-and-conquer#range-knapsack` | 区間の品物だけのナップサック（b2b3 1.1） |
| docs/dp/knapsack-01.md | 222 | `[半分全列挙](../basics/meet-in-the-middle.md)` | `meet-in-the-middle#vs-knapsack` | 重さの上限が大きく N が 40 程度（b1 1.1） |
| docs/dp/knapsack-undo.md | 148 | `[分割統治](../basics/divide-and-conquer.md)` | `divide-and-conquer#range-knapsack` | 区間の品物だけを使うクエリ（b2 knapsack-undo の報告・b2b3 1.1） |
| docs/dp/knapsack-undo.md | 218 | `[分割統治](../basics/divide-and-conquer.md)` | `divide-and-conquer#range-knapsack` | 区間の品物だけを使うクエリ（b2 knapsack-undo の報告・b2b3 1.1） |
| docs/dp/lcs.md | 166 | `[部分列 DP](../dp/subsequence-dp.md)` | `subsequence-dp#leftmost` | 異なる共通部分列は最も左を取る（b1 1.3・b2b3 1.1） |
| docs/dp/lcs.md | 321 | `[部分列 DP](../dp/subsequence-dp.md)` | `subsequence-dp#next-table-dp` | 異なる部分列の種類数（b1 1.3・b2b3 1.1） |
| docs/dp/lis.md | 180 | `[根からのパスを持つ DFS](../tree/root-path-dfs.md)` | `root-path-dfs#undo-log` | 根からのパスを保ったまま戻す（b2b3 1.1。呼び名「根からのパスを持つ DFS」は題名と違う） |
| docs/dp/lis.md | 202 | `[45 度回転](../geometry/manhattan-chebyshev.md)` | `manhattan-chebyshev#rotate-45` | 45 度回転（b1 1.1） |
| docs/dp/memoized-recursion.md | 136 | `[期待値の方程式を解く](../comb/expectation-linear-equations.md)` | `expectation-linear-equations#unknown` | 未知数を置いて方程式を解く（b2b3 1.1） |
| docs/dp/memoized-recursion.md | 158 | `[l, r)$ の値は内側の短い区間で決まる。長さの順に回す代わりに、メモ化再帰でも書ける（[区間 DP](../dp/interval-dp.md)` | `interval-dp#by-length` | 長さの順に回す代わりにメモ化再帰（b1 1.3） |
| docs/dp/memoized-recursion.md | 159 | `[桁 DP の応用](../dp/digit-dp-advanced.md)` | `digit-dp-advanced#sparse-states` | 状態がまばらな応用（b1 1.3・b2b3 1.1） |
| docs/dp/rerooting.md | 166 | `[辺の寄与](../tree/tree-edge-contribution.md)` | `tree-edge-contribution#edge-pairs` | 辺を 1 本切ったときの両側（b1 1.1） |
| docs/dp/rerooting.md | 172 | `[直径](../tree/tree-diameter.md)` | `tree-diameter#eccentricity` | 最も遠い頂点は直径の端点（b1 1.1） |
| docs/dp/rerooting.md | 178 | `[重心分解](../tree/centroid-decomposition.md)` | `centroid-decomposition#count-through` | 頂点の組すべての和（b1 1.3・b2b3 1.1） |
| docs/dp/subset-enumeration-dp.md | 229 | `[ラベル付きグラフの数え上げ](../comb/counting-labeled-graphs.md)` | `counting-labeled-graphs#complement` | 「連結 = 全体 − 非連結」（b2b3 1.1 の案 #component-of-1・#complement） |
| docs/dp/subset-sum.md | 64 | `[bitset による高速化](../misc/bitset-speedup.md)` | `bitset-speedup#subset-sum-shift` | dp \|= dp << a（b1 1.2） |
| docs/dp/subset-sum.md | 160 | `[bitset](../misc/bitset-speedup.md)` | `bitset-speedup#subset-sum-shift` | 可否だけの部分和を bitset で（b1 1.2） |
| docs/dp/subset-sum.md | 161 | `[戻す DP](../dp/knapsack-undo.md)` | `knapsack-undo#undo-by-subtraction` | i 番目を除いた部分和を逆にたどる（b1 1.3） |
| docs/dp/subset-sum.md | 162 | `[余りを状態に持つ DP](../dp/dp-mod-state.md)` | `dp-mod-state#why-remainder` | 和の代わりに余りを状態に（b1 1.1 の案 #average は文と合わないので選び直し） |
| docs/dp/tree-dp.md | 174 | `[重心](../tree/tree-centroid.md)` | `tree-centroid#definition` | 重心の定義と同じ（b1 1.3） |
| docs/dp/tree-dp.md | 209 | `[答えで二分探索](../basics/binary-search-answer.md)` | `binary-search-answer#dp-check` | 決め打ちのたびに表を作り直す・判定の単調性（b1 1.1） |
| docs/dp/tree-dp.md | 213 | `[マージテク](../tree/small-to-large.md)` | `small-to-large#subtree-merge` | 部分木ごとの集合の併合を前提にする節（b1 1.1） |
| docs/dp/tree-dp.md | 329 | `[二乗の木 DP](../dp/tree-dp-square.md)` | `tree-dp-square#size-bounded` | 部分木のサイズまでの配列（b1 1.3） |
| docs/dp/tree-dp.md | 331 | `[マージテク](../tree/small-to-large.md)` | `small-to-large#subtree-merge` | 部分木ごとの集合・色の集計（b1 1.1） |

（58 件）

## misc

| 元のページ | 行 | 今のリンク | 張り替え先 | 根拠 |
| --- | --- | --- | --- | --- |
| docs/misc/bitset-speedup.md | 326 | `[XOR 基底](../math/xor-basis.md)` | `xor-basis#max` | XOR の最大化（b2 bitset-speedup の報告・b2b3 1.1） |

（1 件）

## graph

| 元のページ | 行 | 今のリンク | 張り替え先 | 根拠 |
| --- | --- | --- | --- | --- |
| docs/graph/bfs.md | 51 | `[ダイクストラ法](../graph/dijkstra.md)` | `dijkstra#why-correct` | 距離の小さい順に頂点を確定させる（b1 1.1 の案 #super-vertex は dijkstra にないので選び直し） |
| docs/graph/bfs.md | 163 | `[状態を頂点にする](../graph/extended-dijkstra.md)` | `extended-dijkstra#choose-state` | dist を（位置, 状態）の組ごとに持つ（b1 1.1） |
| docs/graph/bfs.md | 169 | `[補グラフ上の BFS](../graph/complement-graph-bfs.md)` | `complement-graph-bfs#take-unvisited` | 辺を全部張らずに補グラフを BFS（b1 1.3） |
| docs/graph/bipartite-graph.md | 169 | `[二部マッチング](../graph/bipartite-matching.md)` | `bipartite-matching#reduction` | 両側を始点と終点につなぐと最大流で求まる（b1 1.3） |
| docs/graph/bipartite-graph.md | 170 | `[König の定理](../graph/konig-theorem.md)` | `konig-theorem#theorem` | König の定理（b1 1.3・b2b3 1.1） |
| docs/graph/bipartite-graph.md | 171 | `[燃やす埋める](../graph/project-selection.md)` | `project-selection#flip-side` | 「違うとコスト」だけ表せ、片側を反転する（b1 1.3） |
| docs/graph/bipartite-matching.md | 82 | `[最大流](../graph/max-flow.md)` | `max-flow#modeling` | 頂点の容量など最大流のモデル化（b2b3 1.1 の「各ページ」） |
| docs/graph/bipartite-matching.md | 273 | `[最小費用流](../graph/min-cost-flow.md)` | `min-cost-flow#modeling` | 組ごとの重み（重み付き二部マッチング）（b2b3 1.1 の「各ページ」） |
| docs/graph/bipartite-matching.md | 275 | `[König の定理](../graph/konig-theorem.md)` | `konig-theorem#theorem` | 最小頂点被覆・最大独立集合への言い換え（b2b3 1.1 の「各ページ」） |
| docs/graph/cycle-detection.md | 161 | `[lowlink](../graph/lowlink.md)` | `lowlink#conditions` | どの辺が閉路の上にないか（橋）（b1 1.3・b2b3 1.1） |
| docs/graph/dfs.md | 129 | `[橋・関節点・二重連結成分](../graph/lowlink.md)` | `lowlink#ord-low` | 行きがけ番号と lowlink を比べる（b1 1.3・b2b3 1.1） |
| docs/graph/dijkstra.md | 171 | `[最短路 DAG](../graph/shortest-path-dag.md)` | `shortest-path-dag#edge-on-path` | 辺が s-t 最短路に乗る条件（b1 1.1 の案 #build より文に合う） |
| docs/graph/dijkstra.md | 193 | `[ベルマンフォード法](../graph/bellman-ford.md)` | `bellman-ford#vs-potential` | Johnson のポテンシャル（b2b3 1.1） |
| docs/graph/dijkstra.md | 202 | `[最小費用流](../graph/min-cost-flow.md)` | `min-cost-flow#successive-shortest-path` | 負のコストの残余辺とポテンシャル（b1 1.3） |
| docs/graph/dijkstra.md | 221 | `[最小費用流](../graph/min-cost-flow.md)` | `min-cost-flow#successive-shortest-path` | ポテンシャルで負の残余辺を消して最短路を繰り返す（b1 1.3） |
| docs/graph/functional-graph.md | 59 | `[木の基本](../tree/tree-basics.md)` | `tree-basics#remove-add-edge` | 1 本足すと閉路がちょうど 1 つ（b1 1.1） |
| docs/graph/functional-graph.md | 119 | `[強連結成分分解](../graph/scc.md)` | `scc#on-cycle` | 頂点が 2 個以上の強連結成分は閉路（b1 1.1） |
| docs/graph/functional-graph.md | 240 | `[なもりグラフ](../graph/namori-graph.md)` | `namori-graph#directed-version` | 向きのない N 頂点 N 辺の連結グラフとの対比（b1 1.1） |
| docs/graph/graph-basics.md | 81 | `[オイラー路](../graph/euler-path.md)` | `euler-path#hierholzer` | 使った辺に印を付ける（b1 1.3） |
| docs/graph/graph-basics.md | 81 | `[lowlink](../graph/lowlink.md)` | `lowlink#multi-edges` | 来た辺だけを戻らない（辺の番号）（b1 1.3・b2b3 1.1） |
| docs/graph/graph-basics.md | 98 | `[補グラフの BFS](../graph/complement-graph-bfs.md)` | `complement-graph-bfs#take-unvisited` | 辺の数が N^2 近いので工夫が要る（b1 1.3） |
| docs/graph/graph-basics.md | 115 | `[次数による平方分割](../graph/degree-sqrt.md)` | `degree-sqrt#few-heavy` | 次数が √M 以上の頂点は 2√M 個以下（b1 1.3） |
| docs/graph/grid-graph.md | 124 | `[燃やす埋める](../graph/project-selection.md)` | `project-selection#flip-side` | 片方の色のマスだけ 0 と 1 を入れ替える（b1 1.3） |
| docs/graph/konig-theorem.md | 76 | `[二部マッチング](../graph/bipartite-matching.md)` | `bipartite-matching#reduction` | 整数の最大流の値が最大マッチング（b2b3 1.1 の「各ページ。相手の見出しを見て選ぶ」） |
| docs/graph/konig-theorem.md | 81 | `[最小カット](../graph/min-cut.md)` | `min-cut#maxflow-mincut` | 最小カットの容量は最大流の値（b2b3 1.1 の「各ページ」） |
| docs/graph/min-cut.md | 57 | `[残余グラフ](../graph/max-flow.md)` | `max-flow#residual` | 残余グラフ（b2b3 1.1） |
| docs/graph/min-cut.md | 114 | `[最大流](../graph/max-flow.md)` | `max-flow#undirected-vertex-capacity` | 頂点を入口と出口に分ける（b2b3 1.1） |
| docs/graph/minimum-spanning-tree.md | 182 | `[Union-Find の応用](../ds/union-find-applications.md)` | `union-find-applications#multiple-uf` | 重みの種類が少ないときの節の前提（しきい値ごとの Union-Find）（b1 1.1） |
| docs/graph/minimum-spanning-tree.md | 214 | `[最小ボトルネック路](../graph/bottleneck-path.md)` | `bottleneck-path#why-mst` | 最小全域木の上の道がボトルネック最小（b1 1.3・b2b3 1.1） |
| docs/graph/minimum-spanning-tree.md | 288 | `[最小ボトルネック路](../graph/bottleneck-path.md)` | `bottleneck-path#why-mst` | 保証されるのは道の上の最大の辺が最小（b1 1.3・b2b3 1.1） |
| docs/graph/namori-graph.md | 189 | `[lowlink](../graph/lowlink.md)` | `lowlink#conditions` | この辺を消すと分かれるか（b1 1.3・b2b3 1.1） |
| docs/graph/project-selection.md | 65 | `[最小カット](../graph/min-cut.md)` | `min-cut#restore` | 残余グラフで s から届く頂点で割り当てを復元（b2b3 1.1 の案 min-cut#restore） |
| docs/graph/project-selection.md | 224 | `[König の定理](../graph/konig-theorem.md)` | `konig-theorem#theorem` | 二部グラフの最大独立集合（b2b3 1.1 の「各ページ」） |
| docs/graph/scc.md | 115 | `[橋・関節点・二重連結成分](../graph/lowlink.md)` | `lowlink#vs-scc` | 同じ ord と low を無向グラフで（b1 1.3・b2b3 1.1） |
| docs/graph/scc.md | 160 | `[DAG 上の DP](../dp/dp-dag.md)` | `dp-dag#with-cycles` | 成分を縮めて DAG 上の DP（b1 1.1 の案 #find-dag より文に合う） |
| docs/graph/scc.md | 190 | `[bitset による高速化](../misc/bitset-speedup.md)` | `bitset-speedup#reachability` | 縮約してから到達可能性を全部求める（b1 1.3） |
| docs/graph/scc.md | 198 | `[bitset による高速化](../misc/bitset-speedup.md)` | `bitset-speedup#reachability` | 辿り着ける集合を bitset の OR で（b1 1.3） |
| docs/graph/scc.md | 267 | `[橋と関節点](../graph/lowlink.md)` | `lowlink#vs-scc` | 使い分けの表（b1 1.3・b2b3 1.1） |
| docs/graph/shortest-path-dag.md | 88 | `[DAG 上の DP](../dp/dp-dag.md)` | `dp-dag#count-shortest-paths` | dist の後に DAG 上の DP として配る（b1 1.1） |
| docs/graph/shortest-path-dag.md | 187 | `[lowlink](../graph/lowlink.md)` | `lowlink#conditions` | 消すと連結でなくなる辺（b1 1.3・b2b3 1.1） |
| docs/graph/topological-sort.md | 79 | `[閉路の検出と復元](../graph/cycle-detection.md)` | `cycle-detection#restore` | 閉路そのものを求める（b1 1.1。同じ行の Kahn 法へのリンクは張り替え済み） |
| docs/graph/topological-sort.md | 137 | `[後退解析](../comb/game-retrograde-analysis.md)` | `game-retrograde-analysis#counter` | 行き先の数のカウンタを減らして確定（b1 1.3） |
| docs/graph/union-find-connectivity.md | 159 | `[最小ボトルネック路](../graph/bottleneck-path.md)` | `bottleneck-path#kruskal-order` | クラスカルの順に併合して経路の最大値の最小（b1 1.3・b2b3 1.1） |
| docs/graph/warshall-floyd.md | 115 | `[ベルマンフォード法](../graph/bellman-ford.md)` | `bellman-ford#relevant-cycles` | 負閉路がありうるときは単一始点のベルマンフォードで（b2b3 1.1） |
| docs/graph/warshall-floyd.md | 193 | `[DFS 木・BFS 木とグラフの構築](../graph/graph-construction.md)` | `graph-construction#from-distances` | 距離表から迂回できない組だけに辺（b1 1.3・b2b3 1.1） |

（45 件）

## geometry

| 元のページ | 行 | 今のリンク | 張り替え先 | 根拠 |
| --- | --- | --- | --- | --- |
| docs/geometry/argument-sort.md | 288 | `[凸包](../geometry/convex-hull.md)` | `convex-hull#andrew` | Graham scan と Andrew 法（b1 1.3・b2b3 1.1） |
| docs/geometry/geometry-precision.md | 112 | `[整数の平方根](../math/integer-root.md)` | `integer-root#compare-sqrt` | √ を含む式を 2 乗して整数で比べる（b1 1.1） |
| docs/geometry/geometry-precision.md | 204 | `[整数の平方根](../math/integer-root.md)` | `integer-root#sqrt-correction` | sqrt で整数の平方根を求める落とし穴（b1 1.1 の案 #compare-sqrt より文に合う） |
| docs/geometry/geometry-precision.md | 280 | `[凸包](../geometry/convex-hull.md)` | `convex-hull#point-in-convex-polygon` | 扇形に分けて二分探索する内外判定（b1 1.3・b2b3 1.1） |
| docs/geometry/geometry-precision.md | 301 | `[円](../geometry/circle-geometry.md)` | `circle-geometry#two-circles` | 円の判定（b1 1.3） |
| docs/geometry/geometry-vectors.md | 237 | `[凸包](../geometry/convex-hull.md)` | `convex-hull#andrew` | 末尾の 2 点と新しい点が左に曲がらない間は取り除く（b1 1.3） |
| docs/geometry/rotation-transform.md | 154 | `[l, r)$ の合成を何度も問われるなら行列を[セグメント木](../ds/segment-tree-monoids.md)` | `segment-tree-monoids#matrix` | 操作の区間の合成を行列で（b1 1.3） |

（7 件）

## tree

| 元のページ | 行 | 今のリンク | 張り替え先 | 根拠 |
| --- | --- | --- | --- | --- |
| docs/tree/euler-tour.md | 188 | `[Mo's algorithm](../ds/mo-algorithm.md)` | `mo-algorithm#mo-on-tree` | 列の区間に直してから Mo（b1 1.3・b2b3 1.1） |
| docs/tree/euler-tour.md | 319 | `[Mo's algorithm](../ds/mo-algorithm.md)` | `mo-algorithm#mo-on-tree` | オイラーツアーと Mo（b1 1.3・b2b3 1.1） |
| docs/tree/hld.md | 133 | `[木の上のパスの判定と分解](../tree/tree-path.md)` | `tree-path#on-path` | 頂点がパス上にあるかの判定（b1 1.3） |
| docs/tree/small-to-large.md | 303 | `[重心分解](../tree/centroid-decomposition.md)` | `centroid-decomposition#count-through` | 部分木の組を数える（b1 1.3・b2b3 1.1） |
| docs/tree/tree-basics.md | 80 | `[次数と次数列](../tree/tree-degree.md)` | `tree-degree#realizable` | その次数列を持つ木が必ず作れる（b1 1.3。呼び名「次数と次数列」は題名と違う） |
| docs/tree/tree-bipartite.md | 142 | `[König の定理](../graph/konig-theorem.md)` | `konig-theorem#theorem` | 木は二部グラフなので König の定理が使える（b1 1.3・b2b3 1.1） |
| docs/tree/tree-construction.md | 102 | `[区間 DP](../dp/interval-dp-advanced.md)` | `interval-dp-advanced#dfs-order-trees` | 訪問順の区間を部分木とみる区間 DP（b1 1.3） |
| docs/tree/tree-construction.md | 189 | `[グラフの構築](../graph/graph-construction.md)` | `graph-construction#from-distances` | 一般のグラフを距離の表から作る（b1 1.3・b2b3 1.1） |
| docs/tree/tree-construction.md | 190 | `[次数と木](../tree/tree-degree.md)` | `tree-degree#pruefer` | 次数の列から木を Prüfer 列で数える（b1 1.3。呼び名「次数と木」は題名と違う） |
| docs/tree/tree-degree.md | 165 | `[ラベル付き木の数と Prüfer 列](../comb/cayley-pruefer.md)` | `cayley-pruefer#with-polynomials` | 母関数の係数に (N−2)! を掛けて数える（b2b3 1.1。呼び名「ラベル付き木の数と Prüfer 列」は題名と違う） |
| docs/tree/tree-degree.md | 248 | `[Cayley の公式](../comb/cayley-pruefer.md)` | `cayley-pruefer#cayley` | Cayley の公式（b2b3 1.1） |
| docs/tree/tree-diameter.md | 189 | `[木の重心](../tree/tree-centroid.md)` | `tree-centroid#vs-center` | 中心と重心は別物（b1 1.3） |
| docs/tree/tree-diameter.md | 311 | `[木の重心](../tree/tree-centroid.md)` | `tree-centroid#vs-center` | 中心と重心（b1 1.3） |
| docs/tree/tree-distance.md | 134 | `[木のパスの扱い](../tree/tree-path.md)` | `tree-path#intersection` | パスどうしの交わり（b1 1.3） |
| docs/tree/tree-edge-contribution.md | 160 | `[重心分解](../tree/centroid-decomposition.md)` | `centroid-decomposition#count-through` | 距離ごと・色の組ごとの数え上げ（b1 1.3・b2b3 1.1） |
| docs/tree/tree-edge-contribution.md | 178 | `[重心分解](../tree/centroid-decomposition.md)` | `centroid-decomposition#count-through` | 距離がちょうど K の組の数（b1 1.3・b2b3 1.1） |
| docs/tree/tree-imos.md | 94 | `[根からのパスを DFS で持ち回る](../tree/root-path-dfs.md)` | `root-path-dfs#path-statistics` | 根からのパス上の値をデータ構造に入れて DFS（b1 1.3・b2b3 1.1） |

（17 件）

## string

| 元のページ | 行 | 今のリンク | 張り替え先 | 根拠 |
| --- | --- | --- | --- | --- |
| docs/string/hash-safety.md | 134 | `[詳しく](../string/hashing-for-sets.md)` | `hashing-for-sets#collision-and-rng` | 差が 0 になる確率は集合なら 2^-64（b2b3 1.1 は #random-values の案。行の中身は衝突確率） |
| docs/string/hash-safety.md | 146 | `[集合・多重集合のハッシュ](../string/hashing-for-sets.md)` | `hashing-for-sets#random-values` | 集合のハッシュの乱数の割り当て方（b2b3 1.1。#random-values は見出しにある） |
| docs/string/hashing-for-sets.md | 111 | `[Mo's algorithm](../ds/mo-algorithm.md)` | `mo-algorithm#what-it-does` | 区間の値の個数を Mo で（b1 1.3・b2b3 1.1） |
| docs/string/hashing-for-sets.md | 142 | `[ハッシュを安全に使う](../string/hash-safety.md)` | `hash-safety#atcoder-tests` | シードを固定するとハックで衝突させられる（b1 1.3） |
| docs/string/hashing-for-sets.md | 261 | `[Mo's algorithm](../ds/mo-algorithm.md)` | `mo-algorithm#ordering` | O(N√Q) の見積もり（b1 1.3・b2b3 1.1） |
| docs/string/kmp.md | 175 | `[約数包除](../comb/divisor-inclusion-exclusion.md)` | `divisor-inclusion-exclusion#period` | 周期を持つ文字列の数え上げの節の前提（b1 1.3） |
| docs/string/kmp.md | 186 | `[メビウス関数](../comb/mobius-function.md)` | `mobius-function#inversion` | μ を使って f(N) を書く（メビウス反転）（b1 1.3） |
| docs/string/kmp.md | 210 | `[照合オートマトン上の DP](../string/string-automaton-dp.md)` | `string-automaton-dp#matrix-power` | L が巨大なら遷移を行列にして累乗（b1 1.3・b2b3 1.1） |
| docs/string/kmp.md | 217 | `[Aho-Corasick 法](../string/aho-corasick.md)` | `aho-corasick#failure-links` | Trie にまとめて π の代わりに失敗リンクを張る話（b2b3 1.1 の案 #build・#failure-links から、文に合う方） |
| docs/string/palindrome.md | 141 | `[l, r)$ の両端を組にした [区間 DP](../dp/interval-dp.md)` | `interval-dp#ends` | 両端を組にした区間 DP（b1 1.3） |
| docs/string/rolling-hash.md | 102 | `[ハッシュの安全な設計](../string/hash-safety.md)` | `hash-safety#birthday-bound` | 比較の回数ではなく組の数（b1 handoff で名指し・b2b3 1.1） |
| docs/string/rolling-hash.md | 103 | `[ハッシュの安全な設計](../string/hash-safety.md)` | `hash-safety#birthday-bound` | 1 組あたり約 1/p の根拠と限界（b2b3 1.1） |
| docs/string/rolling-hash.md | 109 | `[ハッシュの安全な設計](../string/hash-safety.md)` | `hash-safety#recommended-design` | 迷ったら次の設計（b2b3 1.1） |
| docs/string/rolling-hash.md | 114 | `[ハッシュの安全な設計](../string/hash-safety.md)` | `hash-safety#mod-2-64` | mod 2^64 は長さ 1024 程度で衝突させられる（b2b3 1.1） |
| docs/string/rolling-hash.md | 148 | `[Manacher](../string/palindrome.md)` | `palindrome#manacher` | 決定的な Manacher（b1 handoff で名指し・1.1） |
| docs/string/rolling-hash.md | 174 | `[セグ木に載せるモノイドの設計](../ds/segment-tree-monoids.md)` | `segment-tree-monoids#non-commutative` | ハッシュの連結をセグメント木にする節の前提（b1 1.3） |
| docs/string/rolling-hash.md | 211 | `[Manacher](../string/palindrome.md)` | `palindrome#manacher` | 区間が回文か（b1 1.1） |
| docs/string/rolling-hash.md | 214 | `[Aho-Corasick 法](../string/aho-corasick.md)` | `aho-corasick#count-occurrences` | 多数のパターンの出現（b1 1.3・b2b3 1.1） |
| docs/string/rolling-hash.md | 215 | `[畳み込み](../math/convolution-ntt.md)` | `convolution-ntt#string-matching` | ワイルドカード・ハミング距離（b1 1.2・b2b3 1.1） |
| docs/string/string-basics.md | 145 | `[交換論法](../basics/exchange-argument.md)` | `exchange-argument#then-dp` | この順に並べたうえで DP が要る（b1 1.3） |
| docs/string/string-basics.md | 169 | `[Z-algorithm](../string/z-algorithm.md)` | `z-algorithm#cyclic-shift` | A + A の中で B を探す（b1 handoff で名指し・1.1） |
| docs/string/subsequence-matching.md | 165 | `[部分列 DP](../dp/subsequence-dp.md)` | `subsequence-dp#positions-or-strings` | 何通り取り出せるか・異なる部分列の数（b1 1.3・b2b3 1.1） |
| docs/string/suffix-array.md | 261 | `[Aho-Corasick 法](../string/aho-corasick.md)` | `aho-corasick#abc362_g` | ABC362 G は Aho-Corasick 法でも解ける（b2b3 1.1） |
| docs/string/trie.md | 184 | `[Grundy 数](../comb/grundy-number.md)` | `grundy-number#sum` | 空いた部分木ごとの Grundy 数の XOR（b1 1.3） |
| docs/string/trie.md | 299 | `[Binary Trie](../ds/binary-trie.md)` | `binary-trie#xor-min-max` | XOR の最小・最大（b1 1.3・b2b3 1.1。案 #build・#comparison より文に合う） |
| docs/string/trie.md | 300 | `[Aho-Corasick 法](../string/aho-corasick.md)` | `aho-corasick#count-occurrences` | 多数のパターンの出現を数える（b2b3 1.1） |
| docs/string/z-algorithm.md | 169 | `[j, N) = R[0, N - j)$ を意味する。$R[0, N - j)$ は $S[j, N)$ を反転したものなので、これは $S[j, N)$ が反転しても変わらないことと同じである。条件を満たす最小の $j$ が最長の回文の接尾辞を与える。回文の中心ごとの半径まで要るなら [回文のページ](../string/palindrome.md)` | `palindrome#manacher` | 回文のページの Manacher（b1 1.1） |

（27 件）

## ds

| 元のページ | 行 | 今のリンク | 張り替え先 | 根拠 |
| --- | --- | --- | --- | --- |
| docs/ds/fenwick-tree.md | 162 | `[平面走査](../ds/sweep-line-2d.md)` | `sweep-line-2d#rectangle-count` | 2 次元の点の数え上げの基本形（b1 1.3） |
| docs/ds/global-offset.md | 163 | `[遅延セグメント木](../ds/lazy-segment-tree.md)` | `lazy-segment-tree#idea` | ノードにオフセット（保留）を持たせる（b1 1.1） |
| docs/ds/inversion-number.md | 133 | `[分割統治](../basics/divide-and-conquer.md)` | `divide-and-conquer#crossing` | マージソートで転倒数（b1 1.3・b2b3 1.1） |
| docs/ds/inversion-number.md | 134 | `[Mo's algorithm](../ds/mo-algorithm.md)` | `mo-algorithm#implementation` | 区間ごとの転倒数（b1 1.3・b2b3 1.1） |
| docs/ds/inversion-number.md | 135 | `[遅延セグメント木の載せ方の型](../ds/lazy-segment-tree-patterns.md)` | `lazy-segment-tree-patterns#flip` | 0/1 の列の区間反転と転倒数（b1 1.3・b2b3 1.1） |
| docs/ds/kth-element.md | 74 | `[Binary Trie](../ds/binary-trie.md)` | `binary-trie#kth-and-global-xor` | 個数を持って K 番目、全体に XOR（b1 1.3・b2b3 1.1） |
| docs/ds/kth-element.md | 166 | `[K 番目の値](../basics/kth-value.md)` | `kth-value#why-count` | count(x) ≥ K となる最小の x（b2b3 1.1 の「必要なら #why-count」） |
| docs/ds/lazy-segment-tree-patterns.md | 192 | `[平方分割](../ds/sqrt-decomposition.md)` | `sqrt-decomposition#buckets` | ブロックごとに保留を持ち端は 1 つずつ（b2 lazy-segment-tree-patterns の報告） |
| docs/ds/lazy-segment-tree.md | 155 | `[遅延セグメント木の載せ方の型](../ds/lazy-segment-tree-patterns.md)` | `lazy-segment-tree-patterns#pattern-table` | 型の一覧（b1 1.3・b2b3 1.1） |
| docs/ds/lazy-segment-tree.md | 302 | `[遅延セグメント木の載せ方の型](../ds/lazy-segment-tree-patterns.md)` | `lazy-segment-tree-patterns#design-steps` | 値と作用を自分で設計する（b1 1.3・b2b3 1.1） |
| docs/ds/linked-list.md | 144 | `[補グラフ上の BFS](../graph/complement-graph-bfs.md)` | `complement-graph-bfs#take-unvisited` | 未訪問の頂点の集合（b1 1.3） |
| docs/ds/monotonic-stack.md | 185 | `[セグメント木による DP の高速化](../dp/dp-segment-tree.md)` | `dp-segment-tree#values-on-segment-tree` | 値を添字にした範囲から取るならセグメント木に載せる（b1 1.3） |
| docs/ds/monotonic-stack.md | 298 | `[最大値の位置で分ける分割統治](../basics/divide-and-conquer.md)` | `divide-and-conquer#split-at-max` | 最大値の位置で分ける分割統治（b1 1.3・b2b3 1.1） |
| docs/ds/offline-queries.md | 98 | `[l, r)$ の位置 $i$ のうち、直前の同じ値の位置 $\mathrm{prev}_i$ が $l$ より前のものの個数」とも言える。これは点 $(i, \mathrm{prev}_i)$ の 2 次元の数え上げなので、[平面走査と BIT](../ds/sweep-line-2d.md)` | `sweep-line-2d#rectangle-count` | 点 (i, prev_i) の 2 次元の数え上げ（b1 1.3） |
| docs/ds/offline-queries.md | 176 | `[永続セグメント木](../ds/persistent-data-structures.md)` | `persistent-data-structures#prefix-versions` | 接頭辞ごとの版の永続セグメント木（b1 1.3） |
| docs/ds/offline-queries.md | 267 | `[Mo's algorithm](../ds/mo-algorithm.md)` | `mo-algorithm#what-it-does` | BIT に載らない量を Mo で（b1 1.3・b2b3 1.1） |
| docs/ds/ordered-set.md | 155 | `[Binary Trie](../ds/binary-trie.md)` | `binary-trie#comparison` | XOR の最小の組もソート順で隣り合う。証明は binary-trie の使い分けにある（b2b3 1.1） |
| docs/ds/segment-tree-on-values.md | 50 | `[BIT](../ds/fenwick-tree.md)` | `fenwick-tree#count-by-value` | 値を添字にする BIT（b1 1.1） |
| docs/ds/segment-tree-on-values.md | 69 | `[オフライン](../ds/offline-queries.md)` | `offline-queries#compress` | 先に全部読んで座標圧縮する（b1 1.1 の案 #online より文に合う） |
| docs/ds/segment-tree-on-values.md | 110 | `[セグメント木による遷移の高速化](../dp/dp-segment-tree.md)` | `dp-segment-tree#which-tool` | 遷移の式の形から高速化を選ぶ（b1 1.3） |
| docs/ds/segment-tree-on-values.md | 132 | `[上位 K 個の和を保つ（2 つの multiset）](../ds/top-k-multiset.md)` | `top-k-multiset#two-sets` | 2 つの multiset でも書ける（b1 1.1 の案 #by-index は逆向きの節なので選び直し） |
| docs/ds/segment-tree-on-values.md | 175 | `[平方分割](../ds/sqrt-decomposition.md)` | `sqrt-decomposition#buckets` | 整列した列をバケットに分けて持つ（b1 1.3） |
| docs/ds/segment-tree-on-values.md | 215 | `[上位 K 個の和を保つ（2 つの multiset）](../ds/top-k-multiset.md)` | `top-k-multiset#two-sets` | 下位 K 個と残りを分けて持つ（b1 1.1 の案 #by-index は逆向きの節なので選び直し） |
| docs/ds/segment-tree.md | 231 | `[セグメント木に何を載せるか](../ds/segment-tree-monoids.md)` | `segment-tree-monoids#design-steps` | 結合できる情報の組に直す設計（b1 1.3） |
| docs/ds/sparse-table.md | 61 | `[分割統治](../basics/divide-and-conquer.md)` | `divide-and-conquer#split-at-max` | 最大値の位置で区間を分ける（b2b3 1.1） |
| docs/ds/sparse-table.md | 145 | `[分割統治](../basics/divide-and-conquer.md)` | `divide-and-conquer#range-knapsack` | 中点をまたぐ区間を中点からの累積で（b2b3 1.1） |
| docs/ds/sqrt-decomposition.md | 251 | `[次数による平方分割](../graph/degree-sqrt.md)` | `degree-sqrt#push-pull` | 頂点とその隣接頂点すべてへの操作（b2b3 1.2 の「重い頂点」と同じ申し送り） |
| docs/ds/stack-techniques.md | 123 | `[永続データ構造](../ds/persistent-data-structures.md)` | `persistent-data-structures#version-tree` | 版を木にして持つ（b1 1.3） |
| docs/ds/stack-techniques.md | 160 | `[構文解析](../misc/parsing.md)` | `parsing#bnf` | 数式の評価を再帰で読む（b1 1.3。b2b3 1.1 の案 #deep-nesting は再帰の深さの節で、文は構文解析そのもの） |
| docs/ds/stl-containers.md | 123 | `[ハッシュの衝突と安全な設計](../string/hash-safety.md)` | `hash-safety#unordered-map` | 乱数を混ぜたハッシュを渡す（b1 1.3） |
| docs/ds/top-k-multiset.md | 164 | `[BIT](../ds/fenwick-tree.md)` | `fenwick-tree#count-by-value` | 値を添字にした BIT（b1 1.1 の案 #binary-search より文に合う） |

（31 件）

## cpp

| 元のページ | 行 | 今のリンク | 張り替え先 | 根拠 |
| --- | --- | --- | --- | --- |
| docs/cpp/acl-reading.md | 114 | `[最大流](../graph/max-flow.md)` | `max-flow#acl` | ACL の mf_graph（b1 1.3） |
| docs/cpp/acl-reading.md | 115 | `[最小費用流](../graph/min-cost-flow.md)` | `min-cost-flow#acl` | ACL の mcf_graph（b1 1.3） |
| docs/cpp/acl-reading.md | 116 | `[畳み込みの使い方](../math/convolution-ntt.md)` | `convolution-ntt#acl` | ACL の convolution（b1 1.3・b2b3 1.1） |
| docs/cpp/acl-reading.md | 206 | `[セグメント木に何を載せるか](../ds/segment-tree-monoids.md)` | `segment-tree-monoids#design-steps` | どんな S と op を設計するか（b1 1.3） |
| docs/cpp/acl-reading.md | 215 | `[ラムダ式](../cpp/cpp-lambda.md)` | `cpp-lambda#template-argument` | キャプチャのないラムダをテンプレート引数に（b1 1.1） |
| docs/cpp/cpp-comparators.md | 69 | `[未定義動作](../cpp/cpp-undefined-behavior.md)` | `cpp-undefined-behavior#other-ub` | 比較関数の誤りは未定義動作（b1 1.1 の案 #debug-build より文に合う） |
| docs/cpp/cpp-container-idioms.md | 232 | `[ハッシュの衝突と安全な設計](../string/hash-safety.md)` | `hash-safety#unordered-map` | 攻撃の仕組みと乱数を混ぜたハッシュ（b1 1.3） |
| docs/cpp/cpp-math-functions.md | 205 | `[bitset による高速化](../misc/bitset-speedup.md)` | `bitset-speedup#subset-sum-shift` | 部分和の作れる和の集合を bitset に（b1 1.3） |
| docs/cpp/cpp-math-functions.md | 225 | `[乱択アルゴリズム](../misc/randomized.md)` | `randomized#cpp-random` | mt19937_64 と分布（b1 1.3） |
| docs/cpp/cpp-structured-bindings.md | 55 | `[初期化の書き方](../cpp/cpp-initialization.md)` | `cpp-initialization#ctad` | CTAD（b1 handoff で名指し・1.1） |
| docs/cpp/cpp-structured-bindings.md | 164 | `[未定義動作](../cpp/cpp-undefined-behavior.md)` | `cpp-undefined-behavior#dangling-pq-top` | pq.top() の参照と pop（b1 handoff で名指し・1.1） |
| docs/cpp/cpp-views-cpp23.md | 57 | `[構造化束縛](../cpp/cpp-structured-bindings.md)` | `cpp-structured-bindings#enumerate-reference` | views::enumerate を [i, x] で受ける（b1 1.1） |

（12 件）

## math

| 元のページ | 行 | 今のリンク | 張り替え先 | 根拠 |
| --- | --- | --- | --- | --- |
| docs/math/convolution-ntt.md | 232 | `[位数・原始根](../math/multiplicative-order.md)` | `multiplicative-order#primitive-root` | 2^c 乗して初めて 1 になる数（b2b3 1.1） |
| docs/math/crt.md | 136 | `[任意 mod の畳み込み](../math/convolution-ntt.md)` | `convolution-ntt#convolution-ll` | 3 つの素数で計算した任意 mod の畳み込み（b1 1.3・b2b3 1.1） |
| docs/math/exponent-mod.md | 72 | `[位数](../math/multiplicative-order.md)` | `multiplicative-order#order` | 最短の周期が位数で p − 1 の約数（b1 1.3） |
| docs/math/exponent-mod.md | 95 | `[中国剰余定理](../math/crt.md)` | `crt#applications` | 法を素因数に分けて計算し CRT でまとめる（b1 1.1 の案 #acl より文に合う） |
| docs/math/exponent-mod.md | 166 | `[位数](../math/multiplicative-order.md)` | `multiplicative-order#find-order` | 約数を調べて位数を求める（b1 1.3） |
| docs/math/exponent-mod.md | 195 | `[位数](../math/multiplicative-order.md)` | `multiplicative-order#find-order` | 約数を小さい順に試す（位数の求め方）（b1 1.3） |
| docs/math/ext-gcd.md | 163 | `[逆元](../math/mod-inverse.md)` | `mod-inverse#existence` | a/g と m/g が互いに素なので逆元がある（b1 1.1 の案 #ext-gcd より文に合う） |
| docs/math/ext-gcd.md | 189 | `[逆元](../math/mod-inverse.md)` | `mod-inverse#ext-gcd` | 法が素数でないときの逆元（b1 1.1） |
| docs/math/ext-gcd.md | 246 | `[逆元](../math/mod-inverse.md)` | `mod-inverse#fermat` | 法が素数ならフェルマーの小定理（b1 1.1 の案 #ext-gcd より文に合う） |
| docs/math/floor-sum.md | 262 | `[凸包](../geometry/convex-hull.md)` | `convex-hull#lattice-points` | 多角形の格子点（Pick の定理）（b1 1.2・b2b3 1.1） |
| docs/math/gcd-lcm.md | 124 | `[GCD の性質](../math/gcd-properties.md)` | `gcd-properties#range-gcd` | 区間 gcd の問題（b1 1.3） |
| docs/math/gcd-properties.md | 164 | `[凸包](../geometry/convex-hull.md)` | `convex-hull#lattice-points` | ピックの定理で内部の格子点（b2b3 1.1） |
| docs/math/harmonic-sum.md | 125 | `[約数・倍数のゼータ変換とメビウス変換](../comb/zeta-mobius-divisor.md)` | `zeta-mobius-divisor#per-prime` | 素数の倍数だけで O(M log log M)（b1 1.3） |
| docs/math/harmonic-sum.md | 151 | `[約数包除](../comb/divisor-inclusion-exclusion.md)` | `divisor-inclusion-exclusion#partition` | すべて d の倍数から、ちょうど d を引く（b1 1.3） |
| docs/math/harmonic-sum.md | 188 | `[約数・倍数のゼータ変換とメビウス変換](../comb/zeta-mobius-divisor.md)` | `zeta-mobius-divisor#per-prime` | 素数ごとの段に分ける（b1 1.3） |
| docs/math/integer-root.md | 158 | `[約数の包除原理](../comb/divisor-inclusion-exclusion.md)` | `divisor-inclusion-exclusion#perfect-powers` | 累乗数を指数ごとに包除（b1 1.3） |
| docs/math/matrix-power.md | 159 | `[Aho-Corasick 法](../string/aho-corasick.md)` | `aho-corasick#inherit-terminal` | 禁止文字列を接尾辞に持つノードも捨てる話（b2b3 1.1。string-automaton-dp の案と食い違うが本文の文は終端の受け継ぎ） |
| docs/math/matrix-power.md | 159 | `[文字列の照合の DP](../string/string-automaton-dp.md)` | `string-automaton-dp#multiple-patterns` | 状態数は禁止文字列の長さの合計 + 1 以下（b1 1.3） |
| docs/math/matrix-power.md | 229 | `[l, r)$ の遷移の積を何度も求めるなら、行列を[セグメント木](../ds/segment-tree-monoids.md)` | `segment-tree-monoids#matrix` | 区間の遷移の積を行列をセグメント木に（b1 1.3） |
| docs/math/matrix-power.md | 316 | `[文字列の照合の DP](../string/string-automaton-dp.md)` | `string-automaton-dp#multiple-patterns` | 禁止文字列を Aho-Corasick 法の状態で（b1 1.3・b2b3 1.1） |
| docs/math/matrix-power.md | 390 | `[セグメント木](../ds/segment-tree-monoids.md)` | `segment-tree-monoids#matrix` | 位置ごとに違う行列の区間の積（b1 1.3） |
| docs/math/mod-arithmetic.md | 139 | `[畳み込みの使い方](../math/convolution-ntt.md)` | `convolution-ntt#acl` | 998244353 が長さ 2^23 まで満たす（b1 1.3・b2b3 1.1） |
| docs/math/mod-inverse.md | 151 | `[二項係数の前計算](../comb/binomial-precompute.md)` | `binomial-precompute#fact-ifact` | 階乗と逆階乗の表（b1 1.1 の案 #lucas は文と合わないので選び直し） |
| docs/math/modint.md | 136 | `[畳み込み](../math/convolution-ntt.md)` | `convolution-ntt#acl` | ACL の convolution に static_modint を渡す（b1 1.3・b2b3 1.1） |
| docs/math/prime-exponent-vector.md | 158 | `[掃き出し法](../math/gaussian-elimination.md)` | `gaussian-elimination#rank` | 階数と選び方の数（b1 1.3・b2b3 1.1） |
| docs/math/prime-exponent-vector.md | 158 | `[XOR 基底](../math/xor-basis.md)` | `xor-basis#count` | 空でない選び方は 2^(N−r) − 1（b1 1.3） |
| docs/math/proof-patterns.md | 96 | `[拡張ユークリッドの互除法](../math/ext-gcd.md)` | `ext-gcd#general-solution` | ax + by の正の最小が gcd（ベズー）。存在条件の節（b1 1.1 の案 #applications より文に合う） |
| docs/math/proof-patterns.md | 112 | `[GCD の性質](../math/gcd-properties.md)` | `gcd-properties#step-mod` | N 点の円周を K ずつ進む（b2 gcd-properties の報告） |
| docs/math/sieve-eratosthenes.md | 126 | `[メビウス関数](../comb/mobius-function.md)` | `mobius-function#sieve` | 篩でメビウス関数の表を作る（b1 1.3） |
| docs/math/spf-sieve.md | 66 | `[試し割り](../math/prime-factorization.md)` | `prime-factorization#which-method` | V を超える数は試し割りに戻る（b1 1.1） |
| docs/math/spf-sieve.md | 103 | `[オイラーの φ 関数](../math/euler-phi.md)` | `euler-phi#formula` | φ の定義を前提にする節（b2b3 1.1） |
| docs/math/spf-sieve.md | 103 | `[メビウス関数](../comb/mobius-function.md)` | `mobius-function#definition` | メビウス関数の定義を前提にする節（b1 1.3） |
| docs/math/spf-sieve.md | 152 | `[試し割り](../math/prime-factorization.md)` | `prime-factorization#which-method` | 1 個か少数なら試し割り（b1 1.1） |

（33 件）

## comb

| 元のページ | 行 | 今のリンク | 張り替え先 | 根拠 |
| --- | --- | --- | --- | --- |
| docs/comb/bell-number.md | 219 | `[包除原理](../comb/inclusion-exclusion.md)` | `inclusion-exclusion#surjection` | 使い分けの「組に名前があり、どの組も空でない」は全射の数（b2 bell-number の報告。recurrence の節は張り替え済み） |
| docs/comb/binomial-precompute.md | 94 | `[鏡像法](../comb/reflection-principle.md)` | `reflection-principle#catalan` | 括弧列の個数（b1 1.3・b2b3 1.1） |
| docs/comb/binomial-precompute.md | 292 | `[ラベル付きグラフの数え上げ](../comb/counting-labeled-graphs.md)` | `counting-labeled-graphs#bfs-layers` | 頂点 1 からの距離の層ごとに数える（b1 1.3） |
| docs/comb/counting-basics.md | 170 | `[包除原理](../comb/inclusion-exclusion.md)` | `inclusion-exclusion#surjection` | 全部が片方の箱を引く、一般には包除（全射の数）（b1 1.3） |
| docs/comb/counting-bijection.md | 111 | `[鏡像法](../comb/reflection-principle.md)` | `reflection-principle#reflection` | 累積和が負にならない折れ線（b2b3 1.1） |
| docs/comb/counting-bijection.md | 124 | `[鏡像法](../comb/reflection-principle.md)` | `reflection-principle#reflection` | 最初に破った点から先で折り返す（b2b3 1.1） |
| docs/comb/counting-dedup.md | 104 | `[部分列 DP](../dp/subsequence-dp.md)` | `subsequence-dp#next-table-dp` | 次の出現位置の表で最も左の取り出し（b2b3 1.1 の案 #leftmost。文は表を使う方） |
| docs/comb/counting-dedup.md | 130 | `[部分列 DP](../dp/subsequence-dp.md)` | `subsequence-dp#leftmost` | 最も左を取る（b2b3 1.1） |
| docs/comb/counting-dedup.md | 132 | `[包除原理を DP に載せる](../comb/inclusion-exclusion-dp.md)` | `inclusion-exclusion-dp#first-obstacle` | 最初に通った障害物で分ける（b2 counting-dedup の報告・b2b3 1.1） |
| docs/comb/counting-fix-order.md | 163 | `[挿入 DP](../dp/insertion-dp.md)` | `insertion-dp#relative-rank` | 最後に置いた物が何番目に小さいか（b1 1.3） |
| docs/comb/counting-mindset.md | 111 | `[約数包除](../comb/divisor-inclusion-exclusion.md)` | `divisor-inclusion-exclusion#partition` | gcd がちょうど g を「g の倍数」から引く（b1 1.3） |
| docs/comb/counting-mindset.md | 111 | `[期待値と確率の変換](../comb/expectation-tail-sum.md)` | `expectation-tail-sum#kth-value` | 最大値の期待値を「k 以上」の確率の和で（b1 1.3・b2b3 1.1） |
| docs/comb/counting-mindset.md | 162 | `[重複の除き方](../comb/counting-dedup.md)` | `counting-dedup#divide` | k! で割ってよいのは重複度が一定のときだけ（b1 1.3） |
| docs/comb/coupon-collector.md | 59 | `[期待値を「k 以上」の確率の和で求める](../comb/expectation-tail-sum.md)` | `expectation-tail-sum#identity` | k 回以上かかる確率の和が期待値（b2b3 1.1） |
| docs/comb/coupon-collector.md | 130 | `[包除原理](../comb/inclusion-exclusion.md)` | `inclusion-exclusion#min-max` | min-max 包除の節（b1 handoff で名指し） |
| docs/comb/coupon-collector.md | 132 | `[期待値を「k 以上」の確率の和で求める](../comb/expectation-tail-sum.md)` | `expectation-tail-sum#waiting-time` | k 回目までに終わらない確率の和（b2b3 1.1） |
| docs/comb/expectation-linear-equations.md | 94 | `[最適戦略の期待値](../comb/optimal-strategy-expectation.md)` | `optimal-strategy-expectation#guess-answer` | X が min の中に入るとき（b2 expectation-linear-equations の報告） |
| docs/comb/expectation-linear-equations.md | 257 | `[最適戦略の期待値](../comb/optimal-strategy-expectation.md)` | `optimal-strategy-expectation#guess-answer` | 答えを仮定して二分探索（b2 expectation-linear-equations の報告） |
| docs/comb/expectation-tail-sum.md | 163 | `[二乗の期待値](../comb/expectation-of-square.md)` | `expectation-of-square#pairs` | 和や積の二乗の期待値（b2b3 1.1。検証の指摘 5） |
| docs/comb/expected-value-dp.md | 127 | `[期待値の方程式を解く](../comb/expectation-linear-equations.md)` | `expectation-linear-equations#unknown` | 未知数を置いて方程式で解く（b1 1.3・b2b3 1.1） |
| docs/comb/expected-value-dp.md | 174 | `[最適戦略の期待値](../comb/optimal-strategy-expectation.md)` | `optimal-strategy-expectation#guess-answer` | やり直しで答え自身が式に入る（b1 1.3） |
| docs/comb/game-basics.md | 183 | `[対称性](../thinking/symmetry-pigeonhole-casework.md)` | `symmetry-pigeonhole-casework#symmetry` | 対称性の考え方を前提にする節（b1 1.1） |
| docs/comb/inclusion-exclusion-dp.md | 237 | `[挿入 DP](../dp/insertion-dp.md)` | `insertion-dp#hakone-ekiden-dp` | 位置と値の両方で相手が未定のものを状態に（b2b3 1.1 の「相手の見出しを見て選ぶ」） |
| docs/comb/lattice-paths.md | 51 | `[対応づけ](../comb/counting-bijection.md)` | `counting-bijection#bijection` | 経路と列が 1 対 1 に対応する（b1 1.3） |
| docs/comb/lattice-paths.md | 91 | `[鏡像法](../comb/reflection-principle.md)` | `reflection-principle#reflection` | 途中で座標が負にならない（b1 1.3・b2b3 1.1） |
| docs/comb/lattice-paths.md | 112 | `[包除 DP](../comb/inclusion-exclusion-dp.md)` | `inclusion-exclusion-dp#first-obstacle` | 最初に踏む障害物で分類（b1 1.3・b2b3 1.1） |
| docs/comb/lattice-paths.md | 124 | `[縦の和の公式](../comb/binomial-identities.md)` | `binomial-identities#hockey-stick` | 縦の和の公式（b1 1.2） |
| docs/comb/lattice-paths.md | 175 | `[鏡像法とカタラン数](../comb/reflection-principle.md)` | `reflection-principle#reflection` | 直線を越えない経路を折り返して数える（b1 1.3・b2b3 1.1） |
| docs/comb/lattice-paths.md | 176 | `[包除 DP](../comb/inclusion-exclusion-dp.md)` | `inclusion-exclusion-dp#first-obstacle` | 最初に踏む障害物ごとに全体から引く（b1 1.3・b2b3 1.1） |
| docs/comb/lattice-paths.md | 178 | `[対応づけ・数える対象の言い換え](../comb/counting-bijection.md)` | `counting-bijection#to-lattice-paths` | 言い換えの的として格子路（b1 1.3） |
| docs/comb/linearity-of-expectation.md | 198 | `[二乗の期待値](../comb/expectation-of-square.md)` | `expectation-of-square#difference` | 表の「二乗 X^2 は E[X]^2 ではない」（b1 1.3・b2b3 1.1 の案 #pairs より行に合う） |
| docs/comb/linearity-of-expectation.md | 199 | `[期待値と確率の変換](../comb/expectation-tail-sum.md)` | `expectation-tail-sum#kth-value` | max の期待値（b1 1.3・b2b3 1.1） |
| docs/comb/linearity-of-expectation.md | 304 | `[期待値と確率の変換](../comb/expectation-tail-sum.md)` | `expectation-tail-sum#kth-value` | 最大値・K 番目の値の期待値（b1 1.3・b2b3 1.1） |
| docs/comb/minimax.md | 285 | `[Grundy 数](../comb/grundy-number.md)` | `grundy-number#sum` | 独立なゲームの和（b1 1.3） |
| docs/comb/multinomial-coefficient.md | 63 | `[重複の除き方](../comb/counting-dedup.md)` | `counting-dedup#representative` | 重複の回数が違うときは割り算で直せない（b1 1.3） |
| docs/comb/multinomial-coefficient.md | 185 | `[重複の除き方](../comb/counting-dedup.md)` | `counting-dedup#representative` | 重複の回数がそろわない数え方の直し方（b1 1.3） |
| docs/comb/multinomial-coefficient.md | 218 | `[置換の偶奇](../comb/permutation-parity.md)` | `permutation-parity#duplicates` | 同じ文字が 2 個以上あれば偶奇を調整できる（b1 1.3） |
| docs/comb/nim.md | 114 | `[Grundy 数と Sprague-Grundy の定理](../comb/grundy-number.md)` | `grundy-number#patterns` | 山ごとの値を表にして規則を探す（b1 1.3・b2b3 1.1） |
| docs/comb/nim.md | 175 | `[勝敗の DP](../comb/game-basics.md)` | `game-basics#game-dp` | 勝敗の DP で全部の局面を調べる（b1 1.1） |
| docs/comb/nim.md | 176 | `[Grundy 数](../comb/grundy-number.md)` | `grundy-number#as-nim` | Grundy 数で各ゲームを Nim の山に直す（b1 1.3） |
| docs/comb/probability-basics.md | 130 | `[期待値の線形性](../comb/linearity-of-expectation.md)` | `linearity-of-expectation#split` | 部分の和に分けて線形性（b1 1.1） |
| docs/comb/probability-basics.md | 164 | `[期待値の線形性](../comb/linearity-of-expectation.md)` | `linearity-of-expectation#indicator` | 個数や総和の期待値は確率を足すだけ（b1 1.1） |
| docs/comb/probability-symmetry.md | 111 | `[期待値の線形性](../comb/linearity-of-expectation.md)` | `linearity-of-expectation#indicator` | 対象 i の寄与を数える（b1 1.1 の案 #pairs より文に合う） |
| docs/comb/probability-symmetry.md | 214 | `[期待値の線形性](../comb/linearity-of-expectation.md)` | `linearity-of-expectation#indicator` | 「〜の個数」の期待値（b1 1.1） |
| docs/comb/rational-mod.md | 130 | `[最適戦略の期待値](../comb/optimal-strategy-expectation.md)` | `optimal-strategy-expectation#compare-real` | 期待値を比べる必要がある（b1 1.3） |
| docs/comb/stars-and-bars.md | 145 | `[対応づけ](../comb/counting-bijection.md)` | `counting-bijection#decompose` | 素因数ごとに分けて独立な積に（b1 1.3） |
| docs/comb/stars-and-bars.md | 157 | `[包除原理](../comb/inclusion-exclusion.md)` | `inclusion-exclusion#symmetric` | 上限を破る変数の集合で包除（b1 1.3） |
| docs/comb/zeta-mobius-subset.md | 256 | `[ラベル付きグラフの数え上げ](../comb/counting-labeled-graphs.md)` | `counting-labeled-graphs#component-of-1` | 決めた 1 頂点を含む連結成分で引く（b2b3 1.1 の「相手の見出しを見て選ぶ」） |

（48 件）

## patterns

| 元のページ | 行 | 今のリンク | 張り替え先 | 根拠 |
| --- | --- | --- | --- | --- |
| docs/patterns/bracket-sequence.md | 79 | `[鏡像法とカタラン数](../comb/reflection-principle.md)` | `reflection-principle#catalan` | 長さ 2N の括弧列の個数（b1 1.3・b2b3 1.1） |
| docs/patterns/bracket-sequence.md | 81 | `[セグメント木に何を載せるか](../ds/segment-tree-monoids.md)` | `segment-tree-monoids#pattern-table` | （合計, 最小値）を載せる（b1 1.3） |
| docs/patterns/bracket-sequence.md | 120 | `[鏡像法とカタラン数](../comb/reflection-principle.md)` | `reflection-principle#catalan` | カタラン数の導き方（b1 1.3・b2b3 1.1） |
| docs/patterns/bracket-sequence.md | 146 | `[セグメント木に何を載せるか](../ds/segment-tree-monoids.md)` | `segment-tree-monoids#design-steps` | 載せ方の考え方（b1 1.3） |
| docs/patterns/bracket-sequence.md | 157 | `[交換論法と比較関数の設計](../basics/exchange-argument.md)` | `exchange-argument#adjacent-swap` | 隣り合う 2 列を入れ替えても悪くならない（b1 1.3） |
| docs/patterns/bracket-sequence.md | 171 | `[構文解析](../misc/parsing.md)` | `parsing#bnf` | 文法の規則ごとの関数で再帰的に読む（b1 1.3・b2b3 1.1） |

（6 件）

