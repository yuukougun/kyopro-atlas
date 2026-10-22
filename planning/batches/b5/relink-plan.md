# 節へのリンクへの張り替え候補（2 回目）

候補は 333 件（basics 18・thinking 6・dp 34・misc 2・graph 52・geometry 4・tree 17・string 8・ds 24・cpp 15・math 42・comb 52・patterns 7・guide 50・start 2）。

相手のページが stub だったので anchor を付けずにページへ張ったリンクのうち、前回（planning/batches/b3/relink-plan.md）で相手が stub のため外したもの。2026-10-22 の時点で全 353 ページが draft なので、相手の stage はすべて draft 以上である。張り替え先の anchor は、相手の本文の見出しの `{#…}` か front matter の sections にあることを、スクリプトで全件確かめた。

- 資料：planning/batches/b5/handoff-b4b5.md §1、planning/batches/b1/handoff.md §1.2・§1.3、planning/batches/b3/handoff-b2b3.md §1.2、b1〜b5 の各ページの報告の「stub なのでページへのリンクにした」という申し送り
- 拾い方：docs の本文（front matter と `<!-- gen:begin -->`〜`<!-- gen:end -->` の生成ブロックを除く。docs/lists と各分野の index.md も除く）から、b4・b5 のページ（前回の時点で stub だった 83 ページ）への anchor のないリンクを全部 grep し（531 か所）、1 か所ずつ文と相手の節を照らして選んだ
- 「行」は 2026-10-22 の本文の行番号（張り替える行の目安）。その行に「今のリンク」があることもスクリプトで確かめた。張り替えは、リンク先の `.md` の後ろに `#anchor` を足すだけ（リンクの文字も直すものは根拠に書いた）
- 根拠の括弧の中は出典：「b4b5 1.1」＝handoff-b4b5 §1.1、「b1 1.2」「b1 1.3」＝b1/handoff.md、「b2b3 1.2」＝handoff-b2b3 §1.2、「報告 X」＝そのページの報告。出典のないものは、申し送りが「相手が stub なのでページへのリンクにした」とだけ書いた箇所（b4 の各報告、b5 の reverse-index-signs・contest-strategy・glossary・practice-method・roadmap・how-to-use・library-design・interval など）か、b1〜b4 の執筆の時点で相手が stub だった箇所で、文に合う節を選んだもの
- 申し送りの anchor 案が文と合わないものは、相手の見出しから選び直し、根拠にそう書いた（例：lis:203 は #antichain でなく #path-cover、steiner-subtree:92 は #on-tree でなく #state、small-to-large:247 は #practice）

## 候補から外したもの

- b5 のページから b4 のページへのリンク（twelvefold-way → burnside-lemma、glossary → cdq-divide-and-conquer・stirling-first・generating-function-counting・linear-recurrence-fast・stern-brocot・slope-trick、reverse-index-signs・kth-and-median → wavelet-matrix、permutation → stirling-first、problem-sets → fps-basics、cheatsheet → two-sat、notation → fps-basics）。b5 を書いた時点で b4 はすでに draft で、stub のためにページへ張ったものではない
- 要点の「前提」の行、要点の「使い方」「ほかの入口」の行、ページの導入の段落で、ほかのページの役割をページ単位で並べる文（contest-strategy:42、problem-sets:38、thinking-checklist:51、atcoder-system:33 など）
- 「記法は〜にそろえる」「ほかの記法は〜」のように notation 全体を指す文。記号の定義の直後にかっこで付けた notation へのリンクは、その記号の節（#probability・#math・#string・#tree・#sets-bits）を選んだ
- 使い分けの表・一覧で、1 つの手法だけを扱うページを道具としてまるごと指す行（例：wavelet-matrix・segment-tree-beats・two-sat・flow-lower-bounds・general-matching・offline-dynamic-connectivity・twelvefold-way・stirling-first への行、advanced-ds-catalog#elsewhere の表の行）。相手が複数の手法を節に分けているページ（miller-rabin・chromatic-number・dilworth-path-cover・suffix-automaton など）で、行が 1 つの手法を指すものは候補に入れた
- 同じ文のすぐ後ろに相手の節へのリンクがある箇所（alien-dp:136 の Monge。直後に monge#smawk-larsch がある）
- 文に合う節が相手にないもの（例：binomial-identities:101・partition-number:201・stirling-first:140 → generating-function-counting、burnside-lemma:219 → linear-recurrence-fast、determinant:131 → spanning-tree-advanced、centroid-decomposition:216 → auxiliary-tree、modint:142 → library-design、stl-containers:61 → balanced-bst）
- 申し送りで「ページへのまま」とされたもの：matrix-tree-theorem の行列式の前提、glossary の judge の前置きと shojin、how-to-use → notation、cpp-reverse-index → debugging-checklist
- 張り替えではないもの：advanced-geometry#segment-intersections → sweep-line-2d（相手に該当の節がまだない）、slope-trick:125・k-shortest-paths:87 → advanced-ds-catalog#meldable-heap（リンクを新しく足す提案）、two-sat#acl の title の変更に伴うリンクの文字の確認

## 張り替えるときに文言も直すもの

- comb/euler-phi.md:153：リンクの文字「バーンサイドの補題」→「Burnside の補題」
- graph/bipartite-matching.md:157：リンクの文字を「Hall の結婚定理」に
- graph/difference-constraints.md:219：「グラフへの言い換え」→「グラフへの帰着」
- graph/euler-path.md:221：「グラフの作り方」→「グラフへの帰着」
- ds/priority-queue.md:196・ds/cdq-divide-and-conquer.md:119：「発展的なデータ構造の一覧」→「見慣れないデータ構造の名前と用途」

## basics

| 元のページ | 行 | 今のリンク | 張り替え先 | 根拠 |
| --- | --- | --- | --- | --- |
| docs/basics/binary-search-answer.md | 167 | `[並列二分探索](../ds/parallel-binary-search.md)` | `parallel-binary-search#what-it-does` | 全クエリの二分探索を段ごとにまとめる（b4b5 1.1・b1 1.3） |
| docs/basics/bit-operations.md | 179 | `[XOR](../patterns/xor.md)` | `xor#overview` | XOR が絡む問題の型（b4b5 1.1） |
| docs/basics/bitwise-independence.md | 211 | `[XOR](../patterns/xor.md)` | `xor#overview` | XOR を含む問題全体の入口（b4b5 1.1） |
| docs/basics/complexity-estimation.md | 68 | `[逆引き辞典（制約・計算量から）](../guide/reverse-index-constraints.md)` | `reverse-index-constraints#pages-by-constraint` | 帯ごとの細かい表とページの一覧（b1 1.3） |
| docs/basics/difference-sequence.md | 163 | `[Slope Trick](../dp/slope-trick.md)` | `slope-trick#operations` | 変えた量の絶対値の和を最小にして単調にする（\|x − a\| を足す・累積 min） |
| docs/basics/divide-and-conquer.md | 164 | `[Monge](../dp/monge.md)` | `monge#monotone-minima` | 表の行の Monotone minima |
| docs/basics/divide-and-conquer.md | 165 | `[オンライン畳み込み](../math/online-convolution.md)` | `online-convolution#online` | 表の行の分割統治 FFT（左で確定した値の寄与を右へ） |
| docs/basics/divide-and-conquer.md | 166 | `[CDQ 分割統治](../ds/cdq-divide-and-conquer.md)` | `cdq-divide-and-conquer#procedure` | 表の行の「左の更新が右のクエリに与える影響」 |
| docs/basics/divide-and-conquer.md | 241 | `[ミンコフスキー和](../geometry/advanced-geometry.md)` | `advanced-geometry#minkowski-sum` | 左右の凸包のミンコフスキー和 |
| docs/basics/exchange-argument.md | 103 | `[ストレステストと実験](../guide/stress-testing.md)` | `stress-testing#procedure` | 小さい N で全順列の最適値と比べる（b4b5 1.1。全探索との比較の組み方なら #setups） |
| docs/basics/exchange-argument.md | 178 | `[比で親に併合する貪欲](../tree/tree-ratio-greedy.md)` | `tree-ratio-greedy#why-ratio` | 比の最も良い塊を親の塊の直後に併合する |
| docs/basics/greedy-basics.md | 133 | `[ストレステスト](../guide/stress-testing.md)` | `stress-testing#procedure` | 反例探しの手順（b4b5 1.1・b1 1.3） |
| docs/basics/greedy-priority-queue.md | 163 | `[Alien DP](../dp/alien-dp.md)` | `alien-dp#undoable-greedy` | 取り消しの印を入れる貪欲（b1 1.2・報告 greedy-priority-queue） |
| docs/basics/greedy-priority-queue.md | 163 | `[Slope Trick](../dp/slope-trick.md)` | `slope-trick#breakpoints` | 関数の形を直接持つ（b1 1.3、案なし） |
| docs/basics/greedy-priority-queue.md | 193 | `[Alien DP](../dp/alien-dp.md)` | `alien-dp#undoable-greedy` | 取り消しの形が複雑な場合（b1 1.2） |
| docs/basics/median-absolute.md | 187 | `[Slope Trick](../dp/slope-trick.md)` | `slope-trick#two-heaps` | 2 つのヒープで傾きの変わる点を持つ（b1 1.3） |
| docs/basics/recursion-structure.md | 133 | `[AtCoder と手元の C++ 環境](../cpp/cpp-environment.md)` | `cpp-environment#stack-depth` | 再帰の深さとスタック（b1 1.3・報告 recursion-structure） |
| docs/basics/ternary-search.md | 164 | `[Slope Trick](../dp/slope-trick.md)` | `slope-trick#operations` | \|x − a\| を次々に足して最小値を答える（b1 1.3） |

（18 件）

## thinking

| 元のページ | 行 | 今のリンク | 張り替え先 | 根拠 |
| --- | --- | --- | --- | --- |
| docs/thinking/construction.md | 154 | `[ストレステスト](../guide/stress-testing.md)` | `stress-testing#caveats` | チェッカーの組み立て（b4b5 1.1） |
| docs/thinking/fix-variable.md | 139 | `[ストレステスト](../guide/stress-testing.md)` | `stress-testing#procedure` | 全列挙と比べる（b4b5 1.1。全探索との比較の組み方なら #setups） |
| docs/thinking/reformulation.md | 106 | `[Convex Hull Trick](../dp/cht.md)` | `cht#lines` | 積の項を CHT で扱う（b1 1.3） |
| docs/thinking/reformulation.md | 253 | `[詰まったときの発想リスト](../guide/thinking-checklist.md)` | `thinking-checklist#q-rephrase` | どの言い換えを試すかの問い（b1 1.2） |
| docs/thinking/symmetry-pigeonhole-casework.md | 87 | `[ストレステストと実験](../guide/stress-testing.md)` | `stress-testing#experiment` | 小さい入力の全探索で比べる（b4b5 1.1・b1 1.2） |
| docs/thinking/symmetry-pigeonhole-casework.md | 127 | `[ストレステストと実験](../guide/stress-testing.md)` | `stress-testing#experiment` | 場合ごとの答えを全探索と比べる（b4b5 1.1・b1 1.2） |

（6 件）

## dp

| 元のページ | 行 | 今のリンク | 張り替え先 | 根拠 |
| --- | --- | --- | --- | --- |
| docs/dp/alien-dp.md | 124 | `[Slope Trick](../dp/slope-trick.md)` | `slope-trick#breakpoints` | 関数の形を直接持つ |
| docs/dp/alien-dp.md | 136 | `[Convex Hull Trick](../dp/cht.md)` | `cht#lines` | (S_i − S_j)^2 のような積の項を持つコスト |
| docs/dp/cht.md | 206 | `[Monge 性による DP の高速化](../dp/monge.md)` | `monge#monotone-minima` | 最適な遷移元の位置が単調 |
| docs/dp/cht.md | 207 | `[Alien DP](../dp/alien-dp.md)` | `alien-dp#penalty` | ちょうど K 回の制約を外してから CHT と組む |
| docs/dp/cht.md | 208 | `[DP の高速化の選び方](../dp/dp-speedup-overview.md)` | `dp-speedup-overview#shape-to-tool` | 全体の選び方 |
| docs/dp/dp-basics.md | 156 | `[DP の高速化の全体像](../dp/dp-speedup-overview.md)` | `dp-speedup-overview#shape-to-tool` | 累積和で足りない形（b1 1.3） |
| docs/dp/dp-basics.md | 187 | `[DP の高速化の全体像](../dp/dp-speedup-overview.md)` | `dp-speedup-overview#shape-to-tool` | 遷移の式の形から高速化の道具を選ぶ（b1 1.3） |
| docs/dp/dp-dag.md | 157 | `[最小パス被覆と Hall の定理](../graph/dilworth-path-cover.md)` | `dilworth-path-cover#path-cover` | 縮約した DAG の最小パス被覆（b1 1.3） |
| docs/dp/dp-dag.md | 165 | `[再帰の深さとスタック](../cpp/cpp-environment.md)` | `cpp-environment#stack-depth` | メモ化再帰の深さ（b1 1.2） |
| docs/dp/dp-grid.md | 294 | `[グリッド](../patterns/grid.md)` | `grid#overview` | グリッドの問題の全体の見取り図（b1 1.2 の案 #right-down より文に合う） |
| docs/dp/dp-prefix-sum.md | 301 | `[DP の高速化の全体像](../dp/dp-speedup-overview.md)` | `dp-speedup-overview#read-the-recurrence` | 貰う形の式を書いて右辺の形を見る（b1 1.3） |
| docs/dp/dp-segment-tree.md | 114 | `[Convex Hull Trick](../dp/cht.md)` | `cht#lines` | 積の項 a_y x が残る遷移 |
| docs/dp/dp-segment-tree.md | 182 | `[Convex Hull Trick](../dp/cht.md)` | `cht#lines` | コストが a_j x_i の積を含む |
| docs/dp/dp-segment-tree.md | 182 | `[DP の高速化の全体像](../dp/dp-speedup-overview.md)` | `dp-speedup-overview#shape-to-tool` | 全体の選び方 |
| docs/dp/dp-sequence-partition.md | 156 | `[Monge 性による DP の高速化](../dp/monge.md)` | `monge#monotone-minima` | Monge なら最適な j が i について単調（b1 1.3） |
| docs/dp/dp-sequence-partition.md | 156 | `[Alien DP](../dp/alien-dp.md)` | `alien-dp#penalty` | 区間の個数の次元を外す（b1 1.3） |
| docs/dp/dp-sequence-partition.md | 177 | `[DP の高速化の選び方](../dp/dp-speedup-overview.md)` | `dp-speedup-overview#shape-to-tool` | どの道具を選ぶかの全体（b1 1.3） |
| docs/dp/dynamic-dp.md | 141 | `[Static Top Tree](../tree/static-top-tree.md)` | `static-top-tree#compress-rake` | Static Top Tree（圧縮と併合）の説明 |
| docs/dp/dynamic-dp.md | 156 | `[Static Top Tree のページ](../tree/static-top-tree.md)` | `static-top-tree#resources` | Static Top Tree の資料 |
| docs/dp/interval-dp.md | 125 | `[b, c) \subseteq [a, d)$ なら $\mathrm{cost}(b, c) \le \mathrm{cost}(a, d)$）とき、最適な境目が $l$・$r$ について単調になり、$O(N^2)$ に落とせる（Knuth-Yao の高速化。[Monge](../dp/monge.md)` | `monge#knuth-yao` | Knuth-Yao の高速化 |
| docs/dp/interval-dp.md | 296 | `[Monge](../dp/monge.md)` | `monge#knuth-yao` | 分割点型の Knuth-Yao の高速化 |
| docs/dp/knapsack-undo.md | 85 | `[母関数による数え上げ](../comb/generating-function-counting.md)` | `generating-function-counting#dp-as-polynomial` | DP の更新を多項式の積・商として見る |
| docs/dp/knapsack-undo.md | 128 | `[オフライン動的連結性](../graph/offline-dynamic-connectivity.md)` | `offline-dynamic-connectivity#time-segment-tree` | 時間軸のセグメント木の考え方 |
| docs/dp/lis.md | 203 | `[Dilworth の定理とパス被覆](../graph/dilworth-path-cover.md)` | `dilworth-path-cover#path-cover` | 一般の DAG のパス被覆を二部マッチングで（b1 1.2 の案 #antichain より文に合う） |
| docs/dp/memoized-recursion.md | 128 | `[AtCoder と手元の C++ 環境](../cpp/cpp-environment.md)` | `cpp-environment#stack-depth` | 再帰の深さとスタック（報告 memoized-recursion） |
| docs/dp/monge.md | 101 | `[Alien DP](../dp/alien-dp.md)` | `alien-dp#with-monge` | Monge と Alien DP の組み合わせ |
| docs/dp/monge.md | 139 | `[Alien DP](../dp/alien-dp.md)` | `alien-dp#penalty` | k について凸なのが Alien DP の根拠 |
| docs/dp/monge.md | 142 | `[Slope Trick](../dp/slope-trick.md)` | `slope-trick#breakpoints` | 増分の列で関数を持つ |
| docs/dp/slope-trick.md | 188 | `[Alien DP](../dp/alien-dp.md)` | `alien-dp#penalty` | 答えが選ぶ個数について凸 |
| docs/dp/subsequence-dp.md | 288 | `[動的 DP](../dp/dynamic-dp.md)` | `dynamic-dp#matrix-on-segment-tree` | 遷移を行列にしてセグメント木に載せる |
| docs/dp/subsequence-dp.md | 289 | `[部分列と部分文字列](../patterns/subsequence-and-substring.md)` | `subsequence-and-substring#overview` | 問われ方ごとの対応 |
| docs/dp/subset-enumeration-dp.md | 159 | `[彩色数](../graph/chromatic-number.md)` | `chromatic-number#chromatic-number` | 包除と高速ゼータ変換で O(2^N N)（b2b3 1.2） |
| docs/dp/subset-enumeration-dp.md | 205 | `[彩色数](../graph/chromatic-number.md)` | `chromatic-number#chromatic-number` | 彩色数を包除で O(2^N N)（b2b3 1.2） |
| docs/dp/tree-dp.md | 223 | `[環境の設定](../cpp/cpp-environment.md)` | `cpp-environment#stack-depth` | 再帰の深さ（報告 tree-dp） |

（34 件）

## misc

| 元のページ | 行 | 今のリンク | 張り替え先 | 根拠 |
| --- | --- | --- | --- | --- |
| docs/misc/interactive.md | 190 | `[ストレステスト](../guide/stress-testing.md)` | `stress-testing#interactive` | ジャッジ役を乱数にして回す（b4b5 1.1・b1 1.2） |
| docs/misc/parsing.md | 115 | `[AtCoder と手元の C++ 環境](../cpp/cpp-environment.md)` | `cpp-environment#stack-depth` | スタックの上限を広げる（b2b3 1.2） |

（2 件）

## graph

| 元のページ | 行 | 今のリンク | 張り替え先 | 根拠 |
| --- | --- | --- | --- | --- |
| docs/graph/bipartite-graph.md | 141 | `[グラフへの帰着](../graph/graph-modeling.md)` | `graph-modeling#what-to-vertex` | x 座標と y 座標を頂点にした二部グラフ（相手の節に図がある。b4b5 1.1 の案「#what-to-edge か #what-to-vertex」） |
| docs/graph/bipartite-graph.md | 172 | `[2-SAT](../graph/two-sat.md)` | `two-sat#when-to-use` | 片向きの条件が混ざると 2-SAT（b1 1.3） |
| docs/graph/bipartite-matching.md | 157 | `[Dilworth の定理・DAG の最小パス被覆](../graph/dilworth-path-cover.md)` | `dilworth-path-cover#hall` | Hall の結婚定理（b4b5 1.1・b2b3 1.2。リンクの文字を「Hall の結婚定理」に） |
| docs/graph/bipartite-matching.md | 171 | `[一般グラフのマッチング](../graph/general-matching.md)` | `general-matching#odd-cycles` | 二部グラフでないのにそのまま流す（b4b5 1.1） |
| docs/graph/bipartite-matching.md | 274 | `[一般グラフのマッチング](../graph/general-matching.md)` | `general-matching#odd-cycles` | 奇数長の閉路がある（b4b5 1.1） |
| docs/graph/bipartite-matching.md | 276 | `[Dilworth の定理・DAG の最小パス被覆](../graph/dilworth-path-cover.md)` | `dilworth-path-cover#path-cover` | DAG の最小パス被覆を二部マッチングで |
| docs/graph/bottleneck-path.md | 129 | `[並列二分探索](../ds/parallel-binary-search.md)` | `parallel-binary-search#alternatives` | 連結以外の条件の時刻（b4b5 1.1） |
| docs/graph/bottleneck-path.md | 129 | `[部分永続 Union-Find](../ds/partially-persistent-union-find.md)` | `partially-persistent-union-find#binary-search-time` | 成分の頂点数が z 以上になる時刻 |
| docs/graph/bottleneck-path.md | 133 | `[併合過程の木](../tree/merge-process-tree.md)` | `merge-process-tree#new-vertex` | 木の作り方の詳細（b4b5 1.1） |
| docs/graph/connected-components.md | 109 | `[実行環境](../cpp/cpp-environment.md)` | `cpp-environment#stack-depth` | 再帰の DFS の深さ（b1 1.3） |
| docs/graph/connected-components.md | 129 | `[グラフへの帰着](../graph/graph-modeling.md)` | `graph-modeling#what-to-vertex` | 値を頂点にする（b4b5 1.1。「この節は〜を前提にする」の文） |
| docs/graph/cycle-detection.md | 116 | `[C++ の実行環境](../cpp/cpp-environment.md)` | `cpp-environment#stack-depth` | 再帰の深さ（b1 1.3） |
| docs/graph/dfs.md | 109 | `[AtCoder と手元の C++ 環境](../cpp/cpp-environment.md)` | `cpp-environment#stack-depth` | スタックの上限を広げる（b1 1.2） |
| docs/graph/difference-constraints.md | 219 | `[グラフへの言い換え](../graph/graph-modeling.md)` | `graph-modeling#constraints-to-edges` | 差分制約にならない条件のほかの型（b4b5 1.1。リンクの文字「グラフへの言い換え」を題名「グラフへの帰着」に） |
| docs/graph/dijkstra.md | 220 | `[K 番目の最短路](../graph/k-shortest-paths.md)` | `k-shortest-paths#k-times` | 各頂点を K 回まで取り出す（b4b5 1.1） |
| docs/graph/euler-path.md | 148 | `[行列木定理](../graph/matrix-tree-theorem.md)` | `matrix-tree-theorem#best-theorem` | BEST 定理（b4b5 1.1・b2b3 1.2） |
| docs/graph/euler-path.md | 219 | `[行列木定理](../graph/matrix-tree-theorem.md)` | `matrix-tree-theorem#best-theorem` | 表の行の BEST 定理（b4b5 1.1・b2b3 1.2） |
| docs/graph/euler-path.md | 221 | `[グラフの作り方](../graph/graph-modeling.md)` | `graph-modeling#contraction` | 自由に通れる辺がある（b4b5 1.1。リンクの文字「グラフの作り方」を題名に） |
| docs/graph/extended-dijkstra.md | 395 | `[区間に辺を張る](../graph/segment-tree-graph.md)` | `segment-tree-graph#two-trees` | 超頂点を何段も重ねる |
| docs/graph/extended-dijkstra.md | 396 | `[同余最短路](../graph/modular-shortest-path.md)` | `modular-shortest-path#residue-vertices` | 値の mod を頂点にする（b4b5 1.1） |
| docs/graph/extended-dijkstra.md | 397 | `[グラフへの帰着](../graph/graph-modeling.md)` | `graph-modeling#what-to-vertex` | 何を頂点にするか（b4b5 1.1） |
| docs/graph/grid-graph.md | 176 | `[グリッド](../patterns/grid.md)` | `grid#overview` | グリッドの問題の型の一覧（b1 1.3） |
| docs/graph/konig-theorem.md | 128 | `[Dilworth・最小パス被覆](../graph/dilworth-path-cover.md)` | `dilworth-path-cover#path-cover` | 各頂点を出る側と入る側に分ける |
| docs/graph/konig-theorem.md | 135 | `[一般グラフのマッチング](../graph/general-matching.md)` | `general-matching#edmonds` | 一般グラフの最大マッチングは多項式時間 |
| docs/graph/konig-theorem.md | 139 | `[彩色数・最大独立集合](../graph/chromatic-number.md)` | `chromatic-number#independent-set` | N が 40 程度までの分枝・半分全列挙（b2b3 1.2） |
| docs/graph/konig-theorem.md | 242 | `[彩色数・最大独立集合](../graph/chromatic-number.md)` | `chromatic-number#independent-set` | 表の行（最大独立集合・一般で N が小さい） |
| docs/graph/konig-theorem.md | 244 | `[Dilworth・最小パス被覆](../graph/dilworth-path-cover.md)` | `dilworth-path-cover#path-cover` | 表の行（最小パス被覆・DAG） |
| docs/graph/lowlink.md | 120 | `[オフラインの動的連結性](../graph/offline-dynamic-connectivity.md)` | `offline-dynamic-connectivity#abc334_g` | 相手の例題の ABC334 G |
| docs/graph/lowlink.md | 208 | `[オフラインの動的連結性](../graph/offline-dynamic-connectivity.md)` | `offline-dynamic-connectivity#abc334_g` | 「〜の例題」と書いている ABC334 G |
| docs/graph/min-cost-flow.md | 127 | `[Alien DP](../dp/alien-dp.md)` | `alien-dp#penalty` | K 個の制約を外してペナルティを課す |
| docs/graph/minimum-spanning-tree.md | 163 | `[特殊な最小全域木](../graph/spanning-tree-advanced.md)` | `spanning-tree-advanced#manhattan` | 8 つの領域に分ける Manhattan MST（b1 1.3） |
| docs/graph/minimum-spanning-tree.md | 214 | `[併合過程の木](../tree/merge-process-tree.md)` | `merge-process-tree#new-vertex` | 併合の順を木として残す（b1 1.3） |
| docs/graph/minimum-spanning-tree.md | 215 | `[特殊な最小全域木](../graph/spanning-tree-advanced.md)` | `spanning-tree-advanced#boruvka` | Borůvka 法（b1 1.3） |
| docs/graph/offline-dynamic-connectivity.md | 73 | `[ロールバックできる Union-Find](../ds/rollback-union-find.md)` | `rollback-union-find#what-it-does` | 後入れ先出しの取り消しができる Union-Find |
| docs/graph/scc.md | 189 | `[2-SAT](../graph/two-sat.md)` | `two-sat#unsatisfiable` | x と「x でない」が同じ成分なら充足不能（b1 1.3） |
| docs/graph/scc.md | 190 | `[最小パス被覆と Hall の定理](../graph/dilworth-path-cover.md)` | `dilworth-path-cover#path-cover` | 最小パス被覆を求める（b1 1.3） |
| docs/graph/small-graph-brute-force.md | 106 | `[彩色数の手法](../graph/chromatic-number.md)` | `chromatic-number#chromatic-number` | 3 色以上の塗り分け（b1 1.3） |
| docs/graph/small-graph-brute-force.md | 133 | `[行列木定理](../graph/matrix-tree-theorem.md)` | `matrix-tree-theorem#laplacian` | 全域木の数を行列式で（b4b5 1.1） |
| docs/graph/small-graph-brute-force.md | 134 | `[彩色数・最大独立集合・最大クリーク](../graph/chromatic-number.md)` | `chromatic-number#chromatic-number` | 包除原理で O(2^N N)（b1 1.3） |
| docs/graph/small-graph-brute-force.md | 135 | `[木の同型判定と木のハッシュ](../tree/tree-isomorphism.md)` | `tree-isomorphism#ahu` | 子の形に名前を付けていく（b1 1.3） |
| docs/graph/spanning-tree-advanced.md | 106 | `[併合可能なヒープ](../ds/advanced-ds-catalog.md)` | `advanced-ds-catalog#meldable-heap` | 併合可能なヒープ（b4b5 1.1・報告 spanning-tree-advanced。語は張り替え済み） |
| docs/graph/spanning-tree-advanced.md | 116 | `[行列木定理](../graph/matrix-tree-theorem.md)` | `matrix-tree-theorem#directed` | 有向全域木の個数 |
| docs/graph/steiner-tree.md | 111 | `[Auxiliary Tree](../tree/auxiliary-tree.md)` | `auxiliary-tree#build` | 指定頂点だけの木に縮める |
| docs/graph/topological-sort.md | 168 | `[AtCoder と手元の C++ 環境](../cpp/cpp-environment.md)` | `cpp-environment#stack-depth` | DFS の再帰の深さ（b1 1.2） |
| docs/graph/union-find-connectivity.md | 120 | `[部分永続 Union-Find](../ds/partially-persistent-union-find.md)` | `partially-persistent-union-find#what-it-does` | 過去の任意の時点での連結（b1 1.3） |
| docs/graph/union-find-connectivity.md | 146 | `[ロールバックできる Union-Find](../ds/rollback-union-find.md)` | `rollback-union-find#what-it-does` | 取り消しに使う Union-Find（b1 1.3） |
| docs/graph/union-find-connectivity.md | 165 | `[並列二分探索](../ds/parallel-binary-search.md)` | `parallel-binary-search#with-union-find` | 「初めて連結になる値」を多数（b4b5 1.1） |
| docs/graph/union-find-connectivity.md | 165 | `[併合過程の木](../tree/merge-process-tree.md)` | `merge-process-tree#bottleneck` | 初めて連結になる値は LCA の重み（b1 1.3） |
| docs/graph/union-find-connectivity.md | 268 | `[並列二分探索](../ds/parallel-binary-search.md)` | `parallel-binary-search#with-union-find` | 「初めて連結になる値」のクエリが多い（b4b5 1.1） |
| docs/graph/warshall-floyd.md | 296 | `[似た手法の使い分け](../guide/method-comparison.md)` | `method-comparison#shortest-path` | 最短路の使い分け（b4b5 1.1） |
| docs/graph/zero-one-bfs.md | 152 | `[剰余を頂点にする最短路](../graph/modular-shortest-path.md)` | `modular-shortest-path#residue-vertices` | K で割った余りを頂点にする（b4b5 1.1） |
| docs/graph/zero-one-bfs.md | 269 | `[似た手法の使い分け](../guide/method-comparison.md)` | `method-comparison#shortest-path` | 最短路の手法全体の選び方（b4b5 1.1） |

（52 件）

## geometry

| 元のページ | 行 | 今のリンク | 張り替え先 | 根拠 |
| --- | --- | --- | --- | --- |
| docs/geometry/advanced-geometry.md | 59 | `[CHT のページ](../dp/cht.md)` | `cht#lower-envelope` | 直線の側で交点を持たせる作り方 |
| docs/geometry/convex-hull.md | 153 | `[Convex Hull Trick](../dp/cht.md)` | `cht#lower-envelope` | 直線の集まりの最大値と点の凸包（b2b3 1.2 の「cht 側の該当節」） |
| docs/geometry/convex-hull.md | 168 | `[発展の幾何](../geometry/advanced-geometry.md)` | `advanced-geometry#dynamic-hull` | 直線（点）の追加とクエリが混ざる |
| docs/geometry/manhattan-chebyshev.md | 250 | `[最小全域木の応用](../graph/spanning-tree-advanced.md)` | `spanning-tree-advanced#manhattan` | マンハッタン距離の最小全域木（b1 1.3） |

（4 件）

## tree

| 元のページ | 行 | 今のリンク | 張り替え先 | 根拠 |
| --- | --- | --- | --- | --- |
| docs/tree/dynamic-tree.md | 43 | `[平衡二分探索木](../ds/balanced-bst.md)` | `balanced-bst#what-it-does` | 列を平衡二分探索木で持ち分割と結合で追従する |
| docs/tree/dynamic-tree.md | 88 | `[Static Top Tree](../tree/static-top-tree.md)` | `static-top-tree#compress-rake` | compress と rake の 2 種類の併合 |
| docs/tree/hld.md | 133 | `[Static Top Tree](../tree/static-top-tree.md)` | `static-top-tree#heavy-path-dp` | 重いパスの上にさらに構造を作る（b1 1.3） |
| docs/tree/lca.md | 259 | `[Auxiliary Tree](../tree/auxiliary-tree.md)` | `auxiliary-tree#build` | LCA を使って小さな木に縮める（b1 1.3） |
| docs/tree/root-path-dfs.md | 161 | `[ロールバックできる Union-Find](../ds/rollback-union-find.md)` | `rollback-union-find#no-path-compression` | 経路圧縮をする dsu は使えない（報告 root-path-dfs） |
| docs/tree/small-to-large.md | 247 | `[併合過程の木](../tree/merge-process-tree.md)` | `merge-process-tree#practice` | abc183_f の別解（相手の練習問題の Confluence に解き方がある。b4b5 1.1 の案 #group-as-interval・#alternatives から、文が abc183_f を指すので選び直した） |
| docs/tree/small-to-large.md | 301 | `[併合過程の木](../tree/merge-process-tree.md)` | `merge-process-tree#group-as-interval` | 表の行の「各時点のグループを問う」（b4b5 1.1） |
| docs/tree/static-top-tree.md | 110 | `[列の動的 DP](../dp/dynamic-dp.md)` | `dynamic-dp#matrix-on-segment-tree` | 列の DP をセグメント木に載せたもの |
| docs/tree/steiner-subtree.md | 92 | `[最小シュタイナー木](../graph/steiner-tree.md)` | `steiner-tree#state` | 部分集合と頂点の組を状態にした DP（b1 1.2 の案 #on-tree より文に合う） |
| docs/tree/steiner-subtree.md | 110 | `[Auxiliary Tree](../tree/auxiliary-tree.md)` | `auxiliary-tree#steiner-queries` | DFS 順で隣り合う 2 点の距離の和（b1 1.2） |
| docs/tree/steiner-subtree.md | 111 | `[Auxiliary Tree](../tree/auxiliary-tree.md)` | `auxiliary-tree#build` | 指定頂点と隣り合う LCA だけの小さな木を作る（b1 1.2 の案 #steiner-queries より文に合う） |
| docs/tree/tree-centroid.md | 44 | `[記法と用語の約束](../start/notation.md)` | `notation#tree` | sz[v]・par[v] の記法 |
| docs/tree/tree-centroid.md | 92 | `[木の同型判定](../tree/tree-isomorphism.md)` | `tree-isomorphism#unrooted` | 重心が 2 個のときの根の選び方 |
| docs/tree/tree-degree.md | 167 | `[行列木定理](../graph/matrix-tree-theorem.md)` | `matrix-tree-theorem#laplacian` | ラプラシアン行列の行列式（b4b5 1.1） |
| docs/tree/tree-degree.md | 248 | `[行列木定理](../graph/matrix-tree-theorem.md)` | `matrix-tree-theorem#laplacian` | 使える辺が決まったグラフ（b4b5 1.1） |
| docs/tree/tree-diameter.md | 229 | `[C++ の環境](../cpp/cpp-environment.md)` | `cpp-environment#stack-depth` | 再帰の深さ（b1 1.3） |
| docs/tree/tree-traversal.md | 142 | `[AtCoder と手元の C++ 環境](../cpp/cpp-environment.md)` | `cpp-environment#stack-depth` | 手元のスタックの上限（b1 1.2） |

（17 件）

## string

| 元のページ | 行 | 今のリンク | 張り替え先 | 根拠 |
| --- | --- | --- | --- | --- |
| docs/string/aho-corasick.md | 264 | `[Suffix Automaton](../string/suffix-automaton.md)` | `suffix-automaton#suffix-automaton` | 表の行のテキスト側の全部分文字列（相手は複数の手法を節に分けている） |
| docs/string/hash-safety.md | 144 | `[Miller-Rabin](../math/miller-rabin.md)` | `miller-rabin#deterministic-bases` | 2^64 未満で決定的な Miller-Rabin（b4b5 1.1・b2b3 1.2） |
| docs/string/hash-safety.md | 146 | `[木の同型判定](../tree/tree-isomorphism.md)` | `tree-isomorphism#tree-hash` | 根付き木のハッシュ |
| docs/string/palindrome.md | 286 | `[回文木](../string/suffix-automaton.md)` | `suffix-automaton#palindromic-tree` | 回文木（b1 1.2） |
| docs/string/string-basics.md | 87 | `[部分列と部分文字列](../patterns/subsequence-and-substring.md)` | `subsequence-and-substring#overview` | 問われ方ごとの道具の対応（b1 1.3） |
| docs/string/subsequence-matching.md | 168 | `[部分列と部分文字列](../patterns/subsequence-and-substring.md)` | `subsequence-and-substring#overview` | 問われ方ごとの対応（b1 1.3） |
| docs/string/suffix-array.md | 264 | `[Suffix Automaton](../string/suffix-automaton.md)` | `suffix-automaton#abc452_g` | ABC452 G は相手の例題 |
| docs/string/suffix-array.md | 290 | `[Suffix Automaton](../string/suffix-automaton.md)` | `suffix-automaton#suffix-automaton` | 文字を後ろに足しながら異なる部分文字列を数える（b1 1.3） |

（8 件）

## ds

| 元のページ | 行 | 今のリンク | 張り替え先 | 根拠 |
| --- | --- | --- | --- | --- |
| docs/ds/cdq-divide-and-conquer.md | 119 | `[発展的なデータ構造の一覧](../ds/advanced-ds-catalog.md)` | `advanced-ds-catalog#table` | オンライン強制の代わりの構造（b4b5 1.1。リンクの文字も題名「見慣れないデータ構造の名前と用途」に） |
| docs/ds/cdq-divide-and-conquer.md | 121 | `[並列二分探索](../ds/parallel-binary-search.md)` | `parallel-binary-search#what-it-does` | 全部の質問の二分探索をまとめて分割統治 |
| docs/ds/kth-element.md | 72 | `[平衡二分探索木と pb_ds の tree](../ds/balanced-bst.md)` | `balanced-bst#pbds` | pb_ds の tree（b1 1.3） |
| docs/ds/lazy-segment-tree-patterns.md | 228 | `[mex](../patterns/mex.md)` | `mex#overview` | mex の題材（b2b3 1.2） |
| docs/ds/mo-algorithm.md | 180 | `[二項係数の部分和](../comb/binomial-prefix-sum.md)` | `binomial-prefix-sum#update` | S(n, k) を 1 項ずつ動かす更新式 |
| docs/ds/offline-queries.md | 118 | `[並列二分探索](../ds/parallel-binary-search.md)` | `parallel-binary-search#what-it-does` | しきい値を答えるクエリを一斉に二分探索（b4b5 1.1） |
| docs/ds/parallel-binary-search.md | 123 | `[併合過程の木](../tree/merge-process-tree.md)` | `merge-process-tree#bottleneck` | 初めて連結になる時刻は LCA の時刻（b4b5 1.1） |
| docs/ds/partially-persistent-union-find.md | 109 | `[並列二分探索](../ds/parallel-binary-search.md)` | `parallel-binary-search#with-union-find` | 各段で普通の Union-Find に辺を足し直す |
| docs/ds/partially-persistent-union-find.md | 110 | `[併合過程の木](../tree/merge-process-tree.md)` | `merge-process-tree#bottleneck` | 初めて連結になる時刻は 2 頂点の LCA の時刻（b4b5 1.1） |
| docs/ds/partially-persistent-union-find.md | 114 | `[Undo 可能 Union-Find](../ds/rollback-union-find.md)` | `rollback-union-find#what-it-does` | 直前から順に取り消すだけ（b4b5 1.1 の「文に合う節」） |
| docs/ds/persistent-data-structures.md | 126 | `[部分永続 Union-Find](../ds/partially-persistent-union-find.md)` | `partially-persistent-union-find#what-it-does` | 部分永続の代表（過去の時刻での find） |
| docs/ds/persistent-data-structures.md | 155 | `[ロールバックできる Union-Find](../ds/rollback-union-find.md)` | `rollback-union-find#no-path-compression` | 経路圧縮をしない Union-Find |
| docs/ds/persistent-data-structures.md | 171 | `[Wavelet Matrix](../ds/wavelet-matrix.md)` | `wavelet-matrix#usage` | マージソート木と並べたオンラインのほかの方法 |
| docs/ds/priority-queue.md | 196 | `[発展的なデータ構造の一覧](../ds/advanced-ds-catalog.md)` | `advanced-ds-catalog#meldable-heap` | O(log N) で併合できるヒープ（b4b5 1.1。リンクの文字を題名「見慣れないデータ構造の名前と用途」に） |
| docs/ds/rollback-union-find.md | 92 | `[部分永続 Union-Find](../ds/partially-persistent-union-find.md)` | `partially-persistent-union-find#what-it-does` | 過去の時点の判定 |
| docs/ds/rollback-union-find.md | 96 | `[オフライン動的連結性](../graph/offline-dynamic-connectivity.md)` | `offline-dynamic-connectivity#time-segment-tree` | 辺の追加と削除が混ざるときの詳しい手順 |
| docs/ds/segment-tree-monoids.md | 195 | `[動的 DP](../dp/dynamic-dp.md)` | `dynamic-dp#on-trees` | 同じ考え方を木へ広げた動的 DP |
| docs/ds/stack-techniques.md | 158 | `[ロールバックできる Union-Find](../ds/rollback-union-find.md)` | `rollback-union-find#what-it-does` | 変更前の値を積んで戻す（b1 1.3） |
| docs/ds/top-k-multiset.md | 206 | `[Slope Trick](../dp/slope-trick.md)` | `slope-trick#two-heaps` | L・R の 2 つで傾きの変わる点を持つ（b1 1.3） |
| docs/ds/union-find-applications.md | 201 | `[併合過程を表す木](../tree/merge-process-tree.md)` | `merge-process-tree#group-as-interval` | 各時点の成分を DFS 順の区間にする（b1 1.3） |
| docs/ds/union-find-applications.md | 203 | `[Undo 可能な Union-Find](../ds/rollback-union-find.md)` | `rollback-union-find#offline-dynamic-connectivity` | 削除を含むオフラインの方法（b1 1.3） |
| docs/ds/union-find.md | 137 | `[Undo 可能 Union-Find](../ds/rollback-union-find.md)` | `rollback-union-find#no-path-compression` | 経路圧縮を入れない形（b1 1.3） |
| docs/ds/union-find.md | 202 | `[Undo 可能 Union-Find](../ds/rollback-union-find.md)` | `rollback-union-find#no-path-compression` | 経路圧縮をやめて union by size だけにする（b1 1.3） |
| docs/ds/union-find.md | 202 | `[部分永続 Union-Find](../ds/partially-persistent-union-find.md)` | `partially-persistent-union-find#no-path-compression` | 経路圧縮をやめて union by size だけにする（b1 1.3） |

（24 件）

## cpp

| 元のページ | 行 | 今のリンク | 張り替え先 | 根拠 |
| --- | --- | --- | --- | --- |
| docs/cpp/acl-reading.md | 113 | `[2-SAT](../graph/two-sat.md)` | `two-sat#acl` | 部品の表の two_sat の行（b1 1.3） |
| docs/cpp/acl-reading.md | 310 | `[C++ の逆引き](../cpp/cpp-reverse-index.md)` | `cpp-reverse-index#compile-errors` | 最初の error: と required from here を探す（b1 1.3） |
| docs/cpp/cpp-initialization.md | 113 | `[AtCoder の C++ 環境](../cpp/cpp-environment.md)` | `cpp-environment#auto-var-init` | -ftrivial-auto-var-init=zero（b1 1.3） |
| docs/cpp/cpp-integer-overflow.md | 237 | `[環境構築](../cpp/cpp-environment.md)` | `cpp-environment#gnu-mode` | -std=gnu++23 と -std=c++23（b1 1.3） |
| docs/cpp/cpp-lambda.md | 299 | `[AtCoder の環境と手元の環境](../cpp/cpp-environment.md)` | `cpp-environment#stack-depth` | 手元のスタックの広げ方（b1 1.2） |
| docs/cpp/cpp-macros-template-file.md | 57 | `[AtCoder と手元の環境](../cpp/cpp-environment.md)` | `cpp-environment#pch` | プリコンパイル済みヘッダ（b1 1.3） |
| docs/cpp/cpp-macros-template-file.md | 203 | `[AtCoder と手元の環境](../cpp/cpp-environment.md)` | `cpp-environment#judge-macros` | -DATCODER -DONLINE_JUDGE（b1 1.3） |
| docs/cpp/cpp-macros-template-file.md | 210 | `[AtCoder と手元の環境](../cpp/cpp-environment.md)` | `cpp-environment#march-native` | -march=native（b1 1.3） |
| docs/cpp/cpp-macros-template-file.md | 250 | `[ライブラリの設計](../guide/library-design.md)` | `library-design#bundling` | ライブラリを展開した後のファイル（b1 1.3） |
| docs/cpp/cpp-math-functions.md | 248 | `[ストレステストと実験](../guide/stress-testing.md)` | `stress-testing#procedure` | 乱数の小さな入力で解答を確かめる手順（b4b5 1.1） |
| docs/cpp/cpp-undefined-behavior.md | 53 | `[AtCoder と手元の C++ 環境](../cpp/cpp-environment.md)` | `cpp-environment#options` | AtCoder の GCC のオプション（b1 1.3） |
| docs/cpp/cpp-undefined-behavior.md | 272 | `[ランダムテスト](../guide/stress-testing.md)` | `stress-testing#procedure` | 小さいケースを大量に試す（b4b5 1.1） |
| docs/cpp/cpp-undefined-behavior.md | 290 | `[プリコンパイル済みヘッダ](../cpp/cpp-environment.md)` | `cpp-environment#pch` | 作ったときと同じオプションでしか使われない（b1 1.3） |
| docs/cpp/cpp-undefined-behavior.md | 291 | `[AtCoder と手元の C++ 環境](../cpp/cpp-environment.md)` | `cpp-environment#stack-depth` | ulimit -s unlimited（b1 1.3） |
| docs/cpp/cpp-views-cpp23.md | 279 | `[AtCoder と手元の環境](../cpp/cpp-environment.md)` | `cpp-environment#options` | 手元のオプションを AtCoder の -std=gnu++23 にそろえる（b1 1.3。C++26 の機能の話として指すなら #not-on-atcoder） |

（15 件）

## math

| 元のページ | 行 | 今のリンク | 張り替え先 | 根拠 |
| --- | --- | --- | --- | --- |
| docs/math/base-conversion.md | 47 | `[記法と用語の約束](../start/notation.md)` | `notation#math` | x mod b の記法（b1 1.3） |
| docs/math/convolution-ntt.md | 54 | `[記法と用語の約束](../start/notation.md)` | `notation#math` | [P] の記法（b1 1.3・b2b3 1.2） |
| docs/math/convolution-ntt.md | 80 | `[FFT・NTT の仕組み](../math/fft-ntt.md)` | `fft-ntt#point-value` | 点での値どうしなら積は各点の掛け算 |
| docs/math/convolution-ntt.md | 92 | `[母関数で数える](../comb/generating-function-counting.md)` | `generating-function-counting#coefficients` | 各品物の選び方の数え上げは多項式の積 |
| docs/math/convolution-ntt.md | 220 | `[アダマール変換](../math/hadamard-transform.md)` | `hadamard-transform#index-operations` | 添字の XOR・OR・AND の畳み込み |
| docs/math/convolution-ntt.md | 257 | `[分割統治 FFT](../math/online-convolution.md)` | `online-convolution#product-of-many` | 次数の小さいものから 2 つずつ掛ける分割統治 |
| docs/math/crt.md | 49 | `[記法と用語の約束](../start/notation.md)` | `notation#math` | a mod m の記法（b1 1.3） |
| docs/math/determinant.md | 126 | `[行列木定理](../graph/matrix-tree-theorem.md)` | `matrix-tree-theorem#laplacian` | ラプラシアン行列 |
| docs/math/determinant.md | 159 | `[行列木定理](../graph/matrix-tree-theorem.md)` | `matrix-tree-theorem#examples` | 行列式を使う問題は相手の例題に置く |
| docs/math/digit-and-mod.md | 49 | `[l, r)$ と書き、$S[l, r)$ を 10 進の整数とみた値を $\mathrm{val}(S[l, r))$ と書く。$d(y)$ は正の整数 $y$ の 10 進の桁数である（[記法と用語の約束](../start/notation.md)` | `notation#string` | 部分文字列 S[l, r) の記法（b1 1.3） |
| docs/math/digit-and-mod.md | 93 | `[余りを頂点にした最短路](../graph/modular-shortest-path.md)` | `modular-shortest-path#residue-vertices` | 余りの移り方を辺にする（b4b5 1.1） |
| docs/math/digit-and-mod.md | 210 | `[余りを頂点にした最短路](../graph/modular-shortest-path.md)` | `modular-shortest-path#arc084_b` | ARC084 D は相手の例題（b4b5 1.1） |
| docs/math/digit-and-mod.md | 217 | `[余りを頂点にした最短路](../graph/modular-shortest-path.md)` | `modular-shortest-path#residue-vertices` | 余りの間を操作で移る（b4b5 1.1） |
| docs/math/divisor-count-bound.md | 106 | `[大きな数の素因数分解](../math/miller-rabin.md)` | `miller-rabin#pollard-rho` | Pollard の ρ 法で分解（b1 1.3） |
| docs/math/divisor-count-bound.md | 207 | `[大きな数の素因数分解](../math/miller-rabin.md)` | `miller-rabin#pollard-rho` | 10^12 より大きい N の分解（b1 1.3） |
| docs/math/divisor-enum.md | 153 | `[Miller-Rabin](../math/miller-rabin.md)` | `miller-rabin#miller-rabin` | 素数判定は Miller-Rabin（b1 1.3） |
| docs/math/euler-phi.md | 153 | `[バーンサイドの補題](../comb/burnside-lemma.md)` | `burnside-lemma#necklace` | ネックレスの式（b4b5 1.1。リンクの文字「バーンサイドの補題」を題名「Burnside の補題」に） |
| docs/math/euler-phi.md | 240 | `[乗法的関数](../math/multiplicative-function.md)` | `multiplicative-function#prefix-sums` | N = 10^10 以上の φ の和 |
| docs/math/exponent-mod.md | 167 | `[大きな数の素数判定と素因数分解](../math/miller-rabin.md)` | `miller-rabin#miller-rabin` | a^{p−1} ≡ 1 を素数判定に使う（b1 1.3） |
| docs/math/fft-ntt.md | 45 | `[形式的冪級数](../math/fps-basics.md)` | `fps-basics#operations` | 形式的冪級数の演算を作るとき |
| docs/math/floor-quotient-enum.md | 103 | `[乗法的関数](../math/multiplicative-function.md)` | `multiplicative-function#prime-counting` | 素数の個数を数える方法（b1 1.3） |
| docs/math/fps-basics.md | 56 | `[分割統治の積](../math/online-convolution.md)` | `online-convolution#product-of-many` | 次数の小さいものから掛ける分割統治の積 |
| docs/math/fps-basics.md | 119 | `[ラグランジュ補間](../math/lagrange-interpolation.md)` | `lagrange-interpolation#linear-time` | 点が等間隔なら簡単で速い（b4b5 1.1 の「文に合う節」） |
| docs/math/fps-basics.md | 146 | `[オンライン畳み込み](../math/online-convolution.md)` | `online-convolution#online` | けんちょん氏の解説の DP をオンライン畳み込みで（b4b5 1.1 の「文に合う節」） |
| docs/math/fps-basics.md | 161 | `[母関数の考え方](../comb/generating-function-counting.md)` | `generating-function-counting#abc303_h` | ABC303 Ex は相手の例題 |
| docs/math/gcd-lcm.md | 166 | `[Stern–Brocot 木と連分数](../math/stern-brocot.md)` | `stern-brocot#continued-fraction` | 互除法の商の列は連分数（b1 1.3） |
| docs/math/gcd-properties.md | 184 | `[同余最短路](../graph/modular-shortest-path.md)` | `modular-shortest-path#congruence` | 余り mod a ごとの最小の値（b4b5 1.1・b2b3 1.2） |
| docs/math/hadamard-transform.md | 47 | `[記法と用語の約束](../start/notation.md)` | `notation#sets-bits` | ⊕ と popcount の記法 |
| docs/math/lagrange-interpolation.md | 119 | `[形式的冪級数](../math/fps-basics.md)` | `fps-basics#polynomial-ops` | O(d log^2 d) の補間 |
| docs/math/linear-recurrence-fast.md | 80 | `[形式的冪級数](../math/fps-basics.md)` | `fps-basics#polynomial-ops` | 多項式の割り算（b4b5 1.1） |
| docs/math/linear-recurrence-fast.md | 162 | `[形式的冪級数](../math/fps-basics.md)` | `fps-basics#operations` | 多項式の逆元 |
| docs/math/matrix-power.md | 284 | `[線形漸化式の高速化](../math/linear-recurrence-fast.md)` | `linear-recurrence-fast#vs-matrix` | 状態数が数百を超えるとき（b1 1.3） |
| docs/math/matrix-power.md | 391 | `[DP の高速化の一覧](../dp/dp-speedup-overview.md)` | `dp-speedup-overview#shape-to-tool` | 遷移の形から高速化を選ぶ（b1 1.3） |
| docs/math/mod-arithmetic.md | 47 | `[記法と用語の約束](../start/notation.md)` | `notation#math` | a mod m・合同式の記法（b1 1.3） |
| docs/math/online-convolution.md | 46 | `[記法と用語の約束](../start/notation.md)` | `notation#math` | [x^k] f の記法 |
| docs/math/online-convolution.md | 71 | `[形式的冪級数](../math/fps-basics.md)` | `fps-basics#operations` | g^N を FPS の累乗で |
| docs/math/prime-exponent-vector.md | 49 | `[記法と用語の約束](../start/notation.md)` | `notation#math` | v_p(n)・a \| b の記法（b1 1.3） |
| docs/math/prime-factorization.md | 132 | `[大きな数の素因数分解](../math/miller-rabin.md)` | `miller-rabin#pollard-rho` | 表の行の Pollard's rho（b1 1.3） |
| docs/math/proof-patterns.md | 49 | `[記法と用語の約束](../start/notation.md)` | `notation#math` | a \| b・合同式・mod の記法（b1 1.3） |
| docs/math/proof-patterns.md | 179 | `[ストレステスト](../guide/stress-testing.md)` | `stress-testing#experiment` | 予想を assert で確かめる（b4b5 1.1） |
| docs/math/spf-sieve.md | 148 | `[大きな数の素数判定と素因数分解](../math/miller-rabin.md)` | `miller-rabin#pollard-rho` | 10^18 の数の素因数分解（b1 1.3） |
| docs/math/spf-sieve.md | 155 | `[大きな数の素数判定と素因数分解](../math/miller-rabin.md)` | `miller-rabin#pollard-rho` | 1 個で値が 10^18 程度の素因数分解（b1 1.3） |

（42 件）

## comb

| 元のページ | 行 | 今のリンク | 張り替え先 | 根拠 |
| --- | --- | --- | --- | --- |
| docs/comb/bell-number.md | 152 | `[写像 12 相](../comb/twelvefold-way.md)` | `twelvefold-way#why-not-divide` | 空の組を許すと k! で割れない |
| docs/comb/bell-number.md | 154 | `[第 1 種スターリング数](../comb/stirling-first.md)` | `stirling-first#vs-second-kind` | 第 1 種と第 2 種の係数の取り違え |
| docs/comb/binomial-identities.md | 51 | `[記法と用語の約束](../start/notation.md)` | `notation#math` | Iverson の記法 [P]（notation の #math にある。b2b3 1.2） |
| docs/comb/binomial-identities.md | 222 | `[ランダムテスト](../guide/stress-testing.md)` | `stress-testing#procedure` | 全列挙との比較を自動で繰り返す（b4b5 1.1） |
| docs/comb/binomial-identities.md | 318 | `[二項係数の部分和](../comb/binomial-prefix-sum.md)` | `binomial-prefix-sum#update` | n と K を 1 ずつ動かして更新する |
| docs/comb/burnside-lemma.md | 160 | `[大きな数の素因数分解](../math/miller-rabin.md)` | `miller-rabin#pollard-rho` | 10^18 程度の素因数分解（Factorize） |
| docs/comb/cayley-pruefer.md | 82 | `[行列木定理](../graph/matrix-tree-theorem.md)` | `matrix-tree-theorem#laplacian` | 使える辺が決まったグラフの全域木（b4b5 1.1） |
| docs/comb/cayley-pruefer.md | 160 | `[形式的冪級数と多項式の演算](../math/fps-basics.md)` | `fps-basics#polynomial-ops` | FPS の演算（b4b5 1.1 で cayley-pruefer は #polynomial-ops。「この節は〜を前提にする」の文なので、前提をページへのままにするなら外す） |
| docs/comb/cayley-pruefer.md | 179 | `[行列木定理](../graph/matrix-tree-theorem.md)` | `matrix-tree-theorem#laplacian` | 決まったグラフなら行列木定理（b4b5 1.1） |
| docs/comb/cayley-pruefer.md | 242 | `[行列木定理](../graph/matrix-tree-theorem.md)` | `matrix-tree-theorem#laplacian` | 使える辺が決まったグラフの全域木の数（b4b5 1.1） |
| docs/comb/counting-basics.md | 91 | `[Burnside の補題](../comb/burnside-lemma.md)` | `burnside-lemma#necklace` | 同じ色を含む円形の並べ方（b4b5 1.1・検証役も同じ） |
| docs/comb/counting-basics.md | 160 | `[写像 12 相](../comb/twelvefold-way.md)` | `twelvefold-way#table` | 写像 12 相の表そのものの説明（b1 1.3） |
| docs/comb/counting-basics.md | 191 | `[Burnside の補題](../comb/burnside-lemma.md)` | `burnside-lemma#necklace` | 回転で同一視し同じ色を含む（b4b5 1.1 は案なし。文に合う節を選んだ） |
| docs/comb/counting-dedup.md | 63 | `[Burnside の補題](../comb/burnside-lemma.md)` | `burnside-lemma#why-not-divide` | 重複度がそろわず 4^6 / 6 が整数にならない（b4b5 1.1 は案なし。文に合う節を選んだ） |
| docs/comb/counting-dedup.md | 226 | `[Burnside の補題](../comb/burnside-lemma.md)` | `burnside-lemma#necklace` | 6 個の輪を 4 色で塗り回転で数える（b4b5 1.1 は案なし。文に合う節を選んだ） |
| docs/comb/counting-labeled-graphs.md | 278 | `[行列木定理](../graph/matrix-tree-theorem.md)` | `matrix-tree-theorem#laplacian` | 使い分けの表の全域木の数の行（b4b5 1.1） |
| docs/comb/counting-mindset.md | 154 | `[ストレステストと実験](../guide/stress-testing.md)` | `stress-testing#experiment` | 値を並べて式を推測・OEIS（b4b5 1.1・b1 1.2） |
| docs/comb/coupon-collector.md | 45 | `[記法と用語の約束](../start/notation.md)` | `notation#probability` | E[X]・P(A) の記法（b1 1.3） |
| docs/comb/divisor-inclusion-exclusion.md | 150 | `[Burnside の補題](../comb/burnside-lemma.md)` | `burnside-lemma#by-period` | 最短周期で分類する数え方（b4b5 1.1） |
| docs/comb/expectation-linear-equations.md | 50 | `[記法と用語の約束](../start/notation.md)` | `notation#probability` | E[s]・P(s → t) の記法 |
| docs/comb/expectation-tail-sum.md | 131 | `[連続値の確率](../comb/continuous-probability.md)` | `continuous-probability#integral` | 連続値の tail sum の積分（b4b5 1.1・b2b3 1.2。「この節は〜を前提にする」の文） |
| docs/comb/expectation-tail-sum.md | 145 | `[連続値の確率](../comb/continuous-probability.md)` | `continuous-probability#piecewise` | 区間の端点で区切った区分ごとの多項式を積分して足す |
| docs/comb/expected-value-dp.md | 54 | `[記法と用語の約束](../start/notation.md)` | `notation#probability` | E[s]・P(s → t) の記法（b1 1.3） |
| docs/comb/generating-function-counting.md | 122 | `[第 1 種スターリング数](../comb/stirling-first.md)` | `stirling-first#records` | 上昇階乗の係数 = 左から見える位置の個数ごとの順列の数（b4b5 1.1 の「文に合う節」） |
| docs/comb/generating-function-counting.md | 130 | `[形式的冪級数（FPS）](../math/fps-basics.md)` | `fps-basics#operations` | 母関数を立てた後の多項式の演算（b4b5 1.1） |
| docs/comb/generating-function-counting.md | 210 | `[第 1 種スターリング数](../comb/stirling-first.md)` | `stirling-first#abc385_g` | ABC385 G は相手の例題（b4b5 1.1 の「文に合う節」） |
| docs/comb/grundy-number.md | 56 | `[mex](../patterns/mex.md)` | `mex#properties` | mex そのものの求め方と性質 |
| docs/comb/grundy-number.md | 163 | `[ランダムテスト](../guide/stress-testing.md)` | `stress-testing#experiment` | 小さい範囲の表と予想を比べる（b4b5 1.1） |
| docs/comb/grundy-number.md | 195 | `[非不偏ゲーム](../comb/partizan-games.md)` | `partizan-games#why-not-grundy` | 不偏でないと mex の定義が成り立たない（b4b5 1.1） |
| docs/comb/inclusion-exclusion.md | 197 | `[彩色数](../graph/chromatic-number.md)` | `chromatic-number#chromatic-number` | 彩色数を包除で数える |
| docs/comb/inclusion-exclusion.md | 221 | `[形式的冪級数と多項式の演算](../math/fps-basics.md)` | `fps-basics#signs` | ∏(1 − x^{w_i}) のような多数の因子の積の係数 |
| docs/comb/lattice-paths.md | 177 | `[LGV 補題](../comb/lgv-lemma.md)` | `lgv-lemma#with-lattice-paths` | 交わらない複数の格子路を行列式で（b1 1.3） |
| docs/comb/lgv-lemma.md | 138 | `[行列式](../math/determinant.md)` | `determinant#modulus` | 法が素数でないときの互除法の掃き出し（b4b5 1.1） |
| docs/comb/linearity-of-expectation.md | 51 | `[記法と用語の約束](../start/notation.md)` | `notation#probability` | E[X]・P(A)・[C] の記法 |
| docs/comb/mobius-function.md | 181 | `[乗法的関数](../math/multiplicative-function.md)` | `multiplicative-function#prefix-sums` | メルテンス関数を杜教篩で |
| docs/comb/mobius-function.md | 290 | `[乗法的関数](../math/multiplicative-function.md)` | `multiplicative-function#prefix-sums` | N = 10^9 以上の和は杜教篩など |
| docs/comb/multinomial-coefficient.md | 151 | `[写像 12 相](../comb/twelvefold-way.md)` | `twelvefold-way#why-not-divide` | 空のグループを許すと割り算が使えない（b1 1.3） |
| docs/comb/multinomial-coefficient.md | 172 | `[写像 12 相](../comb/twelvefold-way.md)` | `twelvefold-way#why-not-divide` | 空のグループを許すのに k! で割る（b1 1.3） |
| docs/comb/nim.md | 124 | `[非不偏ゲーム](../comb/partizan-games.md)` | `partizan-games#why-not-grundy` | 手番で打てる手が違うと Bouton の定理も XOR も使えない（b4b5 1.1） |
| docs/comb/nim.md | 177 | `[非不偏ゲーム](../comb/partizan-games.md)` | `partizan-games#why-not-grundy` | 手番で打てる手が違うなら XOR は使えない（b1 1.3） |
| docs/comb/partition-number.md | 81 | `[写像 12 相](../comb/twelvefold-way.md)` | `twelvefold-way#table` | 区別のない玉を区別のない箱へ入れるマス |
| docs/comb/partition-number.md | 172 | `[第 1 種スターリング数](../comb/stirling-first.md)` | `stirling-first#recurrence` | 巡回の個数で数えるなら漸化式が速い |
| docs/comb/partition-number.md | 288 | `[Young 図形とフック長公式](../comb/young-tableaux.md)` | `young-tableaux#hook-length` | 標準 Young 盤を数える |
| docs/comb/permutation-cycles.md | 143 | `[第 1 種スターリング数](stirling-first.md)` | `stirling-first#what` | ちょうど k 個の巡回からなる置換の数 |
| docs/comb/probability-basics.md | 47 | `[記法と用語の約束](../start/notation.md)` | `notation#probability` | P(A)・P(A \| B)・E[X] の記法（b1 1.2） |
| docs/comb/probability-symmetry.md | 49 | `[記法と用語の約束](../start/notation.md)` | `notation#probability` | P(A)・E[X] の記法 |
| docs/comb/reflection-principle.md | 279 | `[LGV の補題](../comb/lgv-lemma.md)` | `lgv-lemma#why-signed` | 交わった点から先を入れ替える全単射 |
| docs/comb/stars-and-bars.md | 166 | `[母関数](../comb/generating-function-counting.md)` | `generating-function-counting#formulas` | 上限や「偶数だけ」の制限を母関数で（b1 1.3） |
| docs/comb/stirling-first.md | 121 | `[形式的冪級数と多項式の演算](../math/fps-basics.md)` | `fps-basics#operations` | FPS で上昇階乗を掛ける（b4b5 1.1。「この節は〜を前提にする」の文） |
| docs/comb/zeta-mobius-divisor.md | 145 | `[アダマール変換](../math/hadamard-transform.md)` | `hadamard-transform#index-operations` | 添字の演算と変換の対応（XOR はアダマール変換） |
| docs/comb/zeta-mobius-divisor.md | 255 | `[約数と倍数](../patterns/divisors-and-multiples.md)` | `divisors-and-multiples#overview` | 約数・倍数の問題の全体の地図 |
| docs/comb/zeta-mobius-subset.md | 194 | `[アダマール変換](../math/hadamard-transform.md)` | `hadamard-transform#transform` | XOR 畳み込みはゼータ変換では求まらずアダマール変換（b2b3 1.2） |

（52 件）

## patterns

| 元のページ | 行 | 今のリンク | 張り替え先 | 根拠 |
| --- | --- | --- | --- | --- |
| docs/patterns/grid.md | 164 | `[操作列とクエリ](../patterns/operation-sequence.md)` | `operation-sequence#overwrite` | 後の操作が前の操作を上書きする（b4b5 1.1） |
| docs/patterns/interval.md | 97 | `[部分列と部分文字列](../patterns/subsequence-and-substring.md)` | `subsequence-and-substring#overview` | 表の行の文字列の連続部分（報告 interval：stub の patterns はページへ） |
| docs/patterns/interval.md | 149 | `[K 番目と中央値](../patterns/kth-and-median.md)` | `kth-and-median#overview` | 中央値の題材の全体（報告 interval） |
| docs/patterns/interval.md | 150 | `[mex](../patterns/mex.md)` | `mex#sum-of-mex` | 全区間の mex の総和（報告 interval） |
| docs/patterns/interval.md | 151 | `[順列](../patterns/permutation.md)` | `permutation#overview` | 順列についての問われ方（報告 interval） |
| docs/patterns/interval.md | 218 | `[部分列と部分文字列](../patterns/subsequence-and-substring.md)` | `subsequence-and-substring#overview` | 問われ方からの引き方（報告 interval） |
| docs/patterns/kth-and-median.md | 176 | `[順列](permutation.md)` | `permutation#lexicographic` | 順列の K 番目は残りの並べ方の数 |

（7 件）

## guide

| 元のページ | 行 | 今のリンク | 張り替え先 | 根拠 |
| --- | --- | --- | --- | --- |
| docs/guide/cheatsheet.md | 40 | `[逆引き辞典（制約・計算量から）](../guide/reverse-index-constraints.md)` | `reverse-index-constraints#constraint-table` | 制約から手法を探す入口（b4b5 1.1 の「計算量と制約の節の最初のリンク → 帯の節」。今は冒頭の段落にしかリンクがないので表の節を選んだ） |
| docs/guide/cheatsheet.md | 295 | `[写像 12 相](../comb/twelvefold-way.md)` | `twelvefold-way#table` | 表の行の「写像 12 相の表」 |
| docs/guide/cheatsheet.md | 353 | `[AtCoder と手元の C++ 環境](../cpp/cpp-environment.md)` | `cpp-environment#version-matrix` | C++ の版の表（b4b5 1.1。文の「環境の違い」に合わせるなら #options） |
| docs/guide/contest-strategy.md | 56 | `[difficulty の帯](../start/atcoder-system.md)` | `atcoder-system#levels` | difficulty の帯と教材のレベル（b4b5 1.1） |
| docs/guide/contest-strategy.md | 63 | `[色別ロードマップ](roadmap.md)` | `roadmap#recent-positions` | 位置ごとにどの手法が多いか（b4b5 1.1） |
| docs/guide/contest-strategy.md | 156 | `[逆引き辞典（言い回しから）](reverse-index-signs.md)` | `reverse-index-signs#by-phrase` | 問題文の言い回しから当たりを付ける |
| docs/guide/contest-strategy.md | 168 | `[詰まったときの発想リスト](thinking-checklist.md)` | `thinking-checklist#q-misreading` | 問いを順にたどる（b4b5 1.1 の「#q-misreading ほか」。問いの列の先頭の節） |
| docs/guide/contest-strategy.md | 172 | `[ストレステストと実験](stress-testing.md)` | `stress-testing#experiment` | 小さいケースを試して規則を探す |
| docs/guide/contest-strategy.md | 176 | `[WA・TLE・RE・MLE の原因チェックリスト](debugging-checklist.md)` | `debugging-checklist#wa` | WA が取れないときの症状ごとの原因 |
| docs/guide/contest-strategy.md | 176 | `[ストレステストと実験](stress-testing.md)` | `stress-testing#procedure` | 愚直解と比べる |
| docs/guide/contest-strategy.md | 191 | `[WA・TLE・RE・MLE の原因チェックリスト](debugging-checklist.md)` | `debugging-checklist#before-submit` | 提出前の確認（b4b5 1.1） |
| docs/guide/contest-strategy.md | 198 | `[ストレステストと実験](stress-testing.md)` | `stress-testing#procedure` | 愚直解と比べて反例を探す |
| docs/guide/contest-strategy.md | 214 | `[この教材の使い方](../start/how-to-use.md)` | `how-to-use#claude` | claude.ai への頼み方（b4b5 1.1） |
| docs/guide/contest-strategy.md | 216 | `[AtCoder の仕組み](../start/atcoder-system.md)` | `atcoder-system#ai-rules` | ルールの版の扱い（b4b5 1.1） |
| docs/guide/contest-strategy.md | 227 | `[精進の仕方](practice-method.md)` | `practice-method#when-to-read` | 解説を読むまでの時間・復習・記録（b4b5 1.1 の「#upsolve・#when-to-read・#records」。文は 3 つを並べるので先頭の節） |
| docs/guide/glossary.md | 46 | `[早見表](cheatsheet.md)` | `cheatsheet#magnitudes` | 数値の目安 |
| docs/guide/glossary.md | 107 | `[AtCoder の仕組み](../start/atcoder-system.md)` | `atcoder-system#rating` | 成績の指標の定義と数値（b4b5 1.1） |
| docs/guide/glossary.md | 155 | `[自作ライブラリの設計と動作確認](library-design.md)` | `library-design#verify` | verify の手順（b4b5 1.1） |
| docs/guide/glossary.md | 167 | `[問題集と練習用コンテストの案内](problem-sets.md)` | `problem-sets#practice-contests` | 練習用コンテスト（b4b5 1.1） |
| docs/guide/knowledge-map.md | 143 | `[使い方](../start/how-to-use.md)` | `how-to-use#backup` | 書き出しと読み込み |
| docs/guide/practice-method.md | 158 | `[問題集と練習用コンテストの案内](problem-sets.md)` | `problem-sets#collections` | 問題集と練習用コンテストのどれを使うか |
| docs/guide/practice-method.md | 158 | `[色別ロードマップ](roadmap.md)` | `roadmap#reading-order` | 色ごとに読むページの順 |
| docs/guide/problem-sets.md | 63 | `[知識マップ](../guide/knowledge-map.md)` | `knowledge-map#by-field` | 分野の位置を確かめながら進める |
| docs/guide/problem-sets.md | 92 | `[色別ロードマップ](../guide/roadmap.md)` | `roadmap#recent-positions` | 位置ごとにどの手法が多いかの集計 |
| docs/guide/problem-sets.md | 502 | `[AtCoder の仕組み](../start/atcoder-system.md)` | `atcoder-system#contests` | ARC の区分（b4b5 1.1） |
| docs/guide/problem-sets.md | 514 | `[精進の仕方](../guide/practice-method.md)` | `practice-method#records` | 記録の付け方 |
| docs/guide/problem-sets.md | 518 | `[自作ライブラリの設計と動作確認](../guide/library-design.md)` | `library-design#verify` | 確かめ方の手順 |
| docs/guide/reverse-index-constraints.md | 55 | `[逆引き辞典（言い回しから）](../guide/reverse-index-signs.md)` | `reverse-index-signs#by-phrase` | 問題文の言い回しからも引く |
| docs/guide/reverse-index-constraints.md | 63 | `[AtCoder と手元の C++ 環境](../cpp/cpp-environment.md)` | `cpp-environment#options` | AtCoder の C++ のオプション（b4b5 1.1） |
| docs/guide/reverse-index-signs.md | 1081 | `[K 番目と中央値](../patterns/kth-and-median.md)` | `kth-and-median#overview` | K 番目と中央値の題材（b4b5 1.1） |
| docs/guide/reverse-index-signs.md | 1144 | `[グラフへの帰着](../graph/graph-modeling.md)` | `graph-modeling#what-to-vertex` | 残り回数などを頂点に含める（b4b5 1.1 は案なし。文に合う節を選んだ） |
| docs/guide/reverse-index-signs.md | 1199 | `[XOR](../patterns/xor.md)` | `xor#overview` | XOR のほかの問われ方（b4b5 1.1） |
| docs/guide/reverse-index-signs.md | 1207 | `[区間](../patterns/interval.md)` | `interval#overview` | 題材の表（b4b5 1.1、bracket-sequence の形） |
| docs/guide/reverse-index-signs.md | 1208 | `[部分列と部分文字列](../patterns/subsequence-and-substring.md)` | `subsequence-and-substring#overview` | 題材の表（b4b5 1.1、bracket-sequence の形） |
| docs/guide/reverse-index-signs.md | 1209 | `[順列と置換](../patterns/permutation.md)` | `permutation#overview` | 題材の表（b4b5 1.1、bracket-sequence の形） |
| docs/guide/reverse-index-signs.md | 1211 | `[mex](../patterns/mex.md)` | `mex#overview` | 題材の表（b4b5 1.1、bracket-sequence の形） |
| docs/guide/reverse-index-signs.md | 1212 | `[K 番目と中央値](../patterns/kth-and-median.md)` | `kth-and-median#overview` | 題材の表（b4b5 1.1、bracket-sequence の形） |
| docs/guide/reverse-index-signs.md | 1213 | `[XOR](../patterns/xor.md)` | `xor#overview` | 題材の表（b4b5 1.1、bracket-sequence の形） |
| docs/guide/reverse-index-signs.md | 1214 | `[約数と倍数](../patterns/divisors-and-multiples.md)` | `divisors-and-multiples#overview` | 題材の表（b4b5 1.1、bracket-sequence の形） |
| docs/guide/reverse-index-signs.md | 1215 | `[グリッド](../patterns/grid.md)` | `grid#overview` | 題材の表（b4b5 1.1、bracket-sequence の形） |
| docs/guide/reverse-index-signs.md | 1216 | `[操作列とクエリ](../patterns/operation-sequence.md)` | `operation-sequence#overview` | 題材の表（b4b5 1.1、bracket-sequence の形） |
| docs/guide/reverse-index-signs.md | 1218 | `[グラフへの帰着](../graph/graph-modeling.md)` | `graph-modeling#what-to-vertex` | 何を頂点・辺にすれば既知の問題になるか（b4b5 1.1 は案なし。文に合う節を選んだ） |
| docs/guide/reverse-index-signs.md | 1226 | `[逆引き辞典（制約・計算量から）](../guide/reverse-index-constraints.md)` | `reverse-index-constraints#constraint-table` | 制約の数字しか手がかりがない（b4b5 1.1 の「帯の節」。行は帯を決めないので表の節） |
| docs/guide/reverse-index-signs.md | 1228 | `[見慣れないデータ構造の名前と用途](../ds/advanced-ds-catalog.md)` | `advanced-ds-catalog#table` | 見慣れない名前のデータ構造（b4b5 1.1 は案なし。文に合う節を選んだ） |
| docs/guide/roadmap.md | 207 | `[知識マップ](knowledge-map.md)` | `knowledge-map#focus` | 前提のつながりを図で見る |
| docs/guide/roadmap.md | 735 | `[問題集と練習用コンテストの案内](problem-sets.md)` | `problem-sets#collections` | 問題集の一覧 |
| docs/guide/roadmap.md | 777 | `[逆引き辞典（言い回しから）](reverse-index-signs.md)` | `reverse-index-signs#by-phrase` | 解けなかった問題から手法を探す（b4b5 1.1 の「文に合う節」） |
| docs/guide/roadmap.md | 777 | `[逆引き辞典（制約から）](reverse-index-constraints.md)` | `reverse-index-constraints#constraint-table` | 制約から引く（b4b5 1.1 の「文に合う節」） |
| docs/guide/thinking-checklist.md | 168 | `[逆引き辞典（言い回しから）](reverse-index-signs.md)` | `reverse-index-signs#by-phrase` | 言い回しから引く |
| docs/guide/thinking-checklist.md | 194 | `[逆引き辞典（制約・計算量から）](reverse-index-constraints.md)` | `reverse-index-constraints#pages-by-constraint` | 制約の帯ごとのページの一覧 |

（50 件）

## start

| 元のページ | 行 | 今のリンク | 張り替え先 | 根拠 |
| --- | --- | --- | --- | --- |
| docs/start/how-to-use.md | 147 | `[問題集と練習用コンテストの案内](../guide/problem-sets.md)` | `problem-sets#collections` | 問題集の一覧 |
| docs/start/notation.md | 43 | `[早見表](../guide/cheatsheet.md)` | `cheatsheet#magnitudes` | 数値の目安 |

（2 件）

