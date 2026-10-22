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
stage: draft
updated: 2026-10-22
---

!!! abstract "要点"
    - **何のページか**：典型90問・EDPC・鉄則本・ACL Practice などの問題集と練習用コンテストを、問題数・中身・レベルの目安から選べる。最近の ABC と各問題集の問題から、使う手法のページも引ける。
    - **使い方**：問題集を選ぶなら[問題集の一覧](#collections)、典型90問の★を帯に読み替えるなら[典型90問の★とレベル](#typical90-stars)を見る。解けなかった問題の手法を探すなら、[最近の ABC → ページ](#recent-abc)か[問題集の問題 → ページ](#sets-to-pages)の表で問題を探す。
    - **数の出どころ**：問題数・開催日・difficulty は AtCoder Problems の公開データ（2026-10-21 取得）による。

<!-- textlint-disable -->
別名：典型90問・EDPC・TDPC・NDPC・鉄則本の問題集・アルゴリズムと数学・ACL Practice・AAL・ADT・AWC・NoviSteps・最近の ABC の対応表
<!-- textlint-enable -->

問題集と練習用コンテストの案内は、過去の ABC 以外の練習の材料を探すときと、問題集で解けなかった問題の手法をこの教材で引くときに使う。問題集は AtCoder の上にコンテストの形で置かれ、過去問と同じように提出して判定を受けられる。解き方の進め方（解説を見るまでの時間・復習）は[精進の仕方](../guide/practice-method.md)、レートや ABC の形式は [AtCoder の仕組み](../start/atcoder-system.md)に任せる。

## 問題集の一覧 {#collections}

問題集の多くには、AtCoder Problems の difficulty（その問題を半々の確率で解けるレート）が付かない。difficulty は参加者のレートとコンテストの結果から推定する値で、レートの変わらない問題集の問題にはほとんど付かない。そこで次の表の「レベルの目安」は、典型90問は作者の★から、ほかは本文でその問題集の問題を載せたページの帯から書いた。本文でまだ使っていない問題集は、題名から分かる分野だけを書いた。

| 問題集（contest id） | 問題数 | 中身 | レベルの目安 |
| --- | ---: | --- | --- |
| [競プロ典型 90 問](#problem-sets-typical90)（typical90） | 90 | 考察と実装の典型を 1 問に 1 つずつ。2021 年に日曜を除く毎日 1 問ずつ出た | ★2〜★7（[次の節](#typical90-stars)）。水以上は 46 問 |
| [EDPC](#problem-sets-dp)（dp） | 26 | DP の典型の基本形を A〜Z の 1 問ずつ。2019-01 | 基礎〜青が中心。本文では DP の各ページの最初の例題に多く使う |
| [TDPC](#problem-sets-tdpc)（tdpc） | 20 | DP。2013-08 | 水〜黄のページに多い |
| NDPC（ndpc） | 20 | DP。2026-05。題名に Knapsack・LIS・Union of Intervals・Independent Set など | 本文ではまだ使っていない |
| [鉄則本の演習問題集](#problem-sets-tessoku-book)（tessoku-book） | 151 | 『競技プログラミングの鉄則』の章（累積和・二分探索・DP・数学・考察・データ構造・グラフ・ヒューリスティック・総合問題）に沿う | 基礎〜水が多い。最大流・二部マッチング・燃やす埋めるなど黄のページの練習も入る |
| [アルゴリズムと数学 演習問題集](#problem-sets-math-and-algorithm)（math-and-algorithm） | 104 | 『アルゴリズム×数学』の本に沿う数学の基礎（素数・場合の数・確率・行列累乗など） | 基礎が中心 |
| [ACL Practice](#problem-sets-practice2)（practice2） | 12 | ACL の主な機能を 1 問ずつ（遅延セグメント木は 2 問） | 機能ごとのページ（水〜黄が多い）の例題 |
| AAL Contest 001: Let's use segtree!（aalc001） | 24 | セグメント木の問題集。2026-10。題名に Lazy Segment Tree・Binary Search on a Segment Tree・Inversion Count など | 本文ではまだ使っていない |
| FPS 24 題（fps-24） | 24 | 形式的冪級数。2025-11 | 発展（[形式的冪級数](../math/fps-basics.md)は発展の帯） |
| 組合せゲーム 24 題（game-24） | 24 | Nim・Grundy 数などのゲーム。2026-10 | 本文ではまだ使っていない |
| AtCoder Typical Contest 001・002（atc001・atc002） | 3・3 | DFS・Union-Find・FFT と、BFS・繰り返し二乗法・最適二分探索木 | 基本の確かめ（atc002 C の満点は発展） |
| AtCoder Beginners Selection（abs） | 11 | ABC の A〜C の過去問 10 問と練習問題 1 問の入門 | この教材の範囲より易しい |

表の左の列のリンクは、このページの[問題集の問題 → ページ](#sets-to-pages)の表の、その問題集の部分へ飛ぶ。リンクのない問題集は、本文の問題の一覧にまだ載っていない。

目的ごとの選び方の目安は次のとおりである。

- **典型を一通り知りたい**：典型90問の★5〜★7（水〜黄）を順に解く。1 問ごとに考察の型が違うので、[知識マップ](../guide/knowledge-map.md)で分野の位置を確かめながら進めるとよい。
- **DP を固めたい**：EDPC で基本形を一通り解き、TDPC・NDPC へ進む。EDPC の各問題がどのページの例題かは[EDPC の表](#problem-sets-dp)にある。
- **ACL の使い方を覚えたい**：ACL Practice を機能ごとに解き、各機能のページの「ACL では」の囲みと見比べる（[ライブラリの確かめ用の問題集](#verify-sets)）。
- **本と一緒に進めたい**：鉄則本とアルゴリズムと数学の演習問題集は、本の章の順に並ぶ。本の例題を自分で書いて提出して確かめる。

## 典型90問の★とレベル {#typical90-stars}

典型90問の問題名に付く★は、作者が問題ごとに付けた難しさで、★ごとに difficulty の範囲が決まっている。典型90問には AtCoder Problems の difficulty が付かないので、この教材では★を帯の根拠にする。

| ★ | difficulty の範囲 | この教材の帯 | 問題数 |
| --- | --- | --- | ---: |
| ★2 | 150〜399 | 基礎 | 10 |
| ★3 | 400〜799 | 基礎 | 20 |
| ★4 | 800〜1199 | 基礎 | 14 |
| ★5 | 1200〜1599 | 水 | 17 |
| ★6 | 1600〜1999 | 青 | 14 |
| ★7 | 2000〜 | 黄以上 | 15 |

- difficulty の範囲は作者の告知記事の表、問題数は AtCoder Problems の問題名から数えた値である。★1（〜149）の問題はない。
- ★の範囲は difficulty の範囲なので、difficulty と同じく「★5 の問題は、レート 1200〜1599 の人が半々の確率で解ける程度」と読める。
- 作者の勧める取り組み方は 4 つある。解法が分かったら AC まで実装する。1 日考えても解けなければ解説を読む。解説にある類題をいくつか解く。本番のコンテストにも出て、身につけた典型を使ってみる。解説は作者の GitHub のリポジトリに画像で置かれている。
- 本文で例題・練習に使った典型90問は、[典型90問の表](#problem-sets-typical90)に問題番号の順で並ぶ。

## 最近の ABC → ページ {#recent-abc}

次の表は、abc451〜abc480 の D〜G の 120 問について、第三者の解説で使われた手法を確かめ、この教材のページに対応させたものである。解いた（解けなかった）最近の ABC の問題から、復習するページを引くのに使う。

- 「位置」は問題の記号、「diff」は AtCoder Problems の difficulty である。最近の ABC では、おおよそ D が基礎、E が水、F が青、G が黄の帯に当たる（[色別ロードマップ](../guide/roadmap.md)）。
- 「使う手法のページ」の › の後は、そのページの中で特に使う節の題である。
- 位置ごとにどの手法が多いかの集計は、[色別ロードマップ](../guide/roadmap.md)にある。

<!-- gen:begin recent-abc -->
<!-- textlint-disable -->

| 問題 | 位置 | diff | 使う手法のページ |
| --- | --- | --- | --- |
| abc451_d Concat Power of 2 | D | 856 | [全探索の設計](../basics/brute-force.md) |
| abc451_e Tree Distance | E | 1215 | [最小全域木](../graph/minimum-spanning-tree.md#kruskal-prim) › クラスカル法とプリム法（密なら O(N^2) のプリム法）、[Union-Find](../ds/union-find.md)、[木の上の距離](../tree/tree-distance.md#from-one) › 1 点からの距離（ダイクストラはいらない）、[木の構築・復元](../tree/tree-construction.md#from-distances) › 距離の情報から作る（最も近い頂点とは辺で結ばれる） |
| abc451_f Make Bipartite 3 | F | 1540 | [重み付き Union-Find](../ds/weighted-union-find.md#generalization) › 一般化（XOR で偶奇・二部グラフ、頂点を 2 倍にする）、[二部グラフ判定](../graph/bipartite-graph.md#union-find) › Union-Find（頂点を 2 倍にする・偶奇を持つ）で判定する |
| abc451_g Minimum XOR Walk | G | 2221 | [XOR 基底](../math/xor-basis.md#xor-walk) › グラフのウォークの XOR（全域木の根からの XOR と、閉路の XOR の基底）、[分割統治](../basics/divide-and-conquer.md) |
| abc452_d No-Subsequence Substring | D | 903 | [部分列の判定と次の出現位置の表](../string/subsequence-matching.md#next-occurrence) › 次の出現位置の表（後ろから作る・番兵 N） |
| abc452_e You WILL Like Sigma Problem | E | 1318 | [周期性の検出](../basics/periodicity.md#periodic-patterns) › 盤面・剰余の周期を割り算で数える、[調和級数と倍数の列挙](../math/harmonic-sum.md#mark-multiples) › 値の倍数に印を付ける、[累積和](../basics/prefix-sum.md) |
| abc452_f Interval Inversion Count | F | 1630 | [尺取り法](../basics/two-pointers.md)、[転倒数](../ds/inversion-number.md#sliding-window) › 窓を伸縮しながら転倒数を増減する（尺取り・期待値と組む）、[BIT（Fenwick Tree）](../ds/fenwick-tree.md) |
| abc452_g 221 Substring | G | 2255 | [ランレングス圧縮](../basics/run-length-encoding.md#keep-compressed) › ランレングスのまま処理する、[Suffix Automaton と発展の文字列アルゴリズム](../string/suffix-automaton.md#suffix-automaton) › Suffix Automaton（状態数 2N−1 以下・遷移数 3N−4 以下。文字の追加に強い）、[Suffix Array と LCP 配列](../string/suffix-array.md#distinct-substrings) › 異なる部分文字列の数 = N(N+1)/2 − Σlcp |
| abc453_d Go Straight | D | 1011 | [状態を頂点にする](../graph/extended-dijkstra.md#parity-mod-direction) › 偶奇・mod・向きを持つ、[幅優先探索（BFS）と無重み最短路](../graph/bfs.md)、[グリッドグラフ](../graph/grid-graph.md) |
| abc453_e Team Division | E | 1513 | [一部を固定して数える](../thinking/fix-variable.md)、[二項係数の前計算](../comb/binomial-precompute.md)、[いもす法](../basics/imos.md#imos-1d) › 1 次元のいもす法（閉区間なら右端 + 1 に −x） |
| abc453_f Avoid Division | F | 2811 | [木の重心](../tree/tree-centroid.md#pair-across) › 重心で分けて別の枝どうしを組む、[構築問題の考え方](../thinking/construction.md) |
| abc453_g Copy Query | G | 1735 | [クエリの先読み](../ds/offline-queries.md)、[永続データ構造](../ds/persistent-data-structures.md#offline-version-tree) › 操作の版を木にしてオフラインで処理する（版の木の DFS と取り消し）、[オイラーツアー](../tree/euler-tour.md) |
| abc454_d (xx) | D | 706 | [スタック・キュー・deque の使いどころ](../ds/stack-techniques.md#cancel) › 直前と打ち消し合うものを消す（末尾を見て pop） |
| abc454_e LRUD Moving | E | 1627 | [偶奇に着目する](../thinking/parity.md#checkerboard) › 市松模様の偶奇、[構築問題の考え方](../thinking/construction.md) |
| abc454_f Make it Palindrome 2 | F | 2169 | [差分列への言い換え](../basics/difference-sequence.md#palindrome) › 回文にする操作は左右の差の列に直してから差分を取る、[言い換えの典型](../thinking/reformulation.md#operations) › 操作の言い換え（区間操作を差分列で・隣接 swap を転倒数で）、[貪欲法の考え方と正当性](../basics/greedy-basics.md) |
| abc454_g Mode in the Subtree | G | 2253 | [マージテク](../tree/small-to-large.md#dsu-on-tree) › DSU on Tree（重い子の結果を残す） |
| abc455_d Card Pile Query | D | 796 | [配列で作る連結リスト](../ds/linked-list.md#operations) › 挿入・削除・付け替えの手順 |
| abc455_e Unbalanced ABC Substrings | E | 1157 | [余事象](../thinking/complement.md#two-conditions) › 2〜3 条件の包除（重なりを足し戻す）、[累積和と連想配列で区間を数える](../basics/prefix-sum-counting.md#equal-k) › S_r − S_l = K となる l を数える（S_0 を入れ忘れない） |
| abc455_f Merge Slimes 2 | F | 1549 | [主客転倒・寄与](../thinking/contribution.md)、[Σ の変形](../math/sigma-manipulation.md#formulas) › よく使う和の公式と Σ_{i≠j} a_i a_j = (Σa)² − Σa²、[遅延セグメント木の載せ方の型](../ds/lazy-segment-tree-patterns.md#design-steps) › 設計の手順と載せられる条件（S はモノイド・F は恒等写像を含み合成で閉じる・f(x·y) = f(x)·f(y)） |
| abc455_g Balanced Subarrays | G | 3092 | [集合・多重集合のハッシュ](../string/hashing-for-sets.md#prefix-hash) › 接頭辞・区間のハッシュ（集合の接頭辞は初めて出た値だけ入れる）、[尺取り法](../basics/two-pointers.md) |
| abc456_d Not Adjacent 2 | D | 586 | [DP の状態の設計](../dp/dp-state-design.md#last-characters) › 末尾の数文字を状態にする（禁止された並び・回文を避ける） |
| abc456_e Endless Holidays | E | 1214 | [状態を頂点にする](../graph/extended-dijkstra.md#layered-graph) › 頂点倍化（層を作り、層の間の辺でコストを表す）、[閉路の検出と復元](../graph/cycle-detection.md#directed) › 有向グラフ：3 色の DFS（探索中の頂点への辺だけが閉路） |
| abc456_f Plan Holidays | F | 1888 | [セグメント木に何を載せるか](../ds/segment-tree-monoids.md#matrix) › 行列を載せる（(min,+)・(max,+) の半環も）、[行列累乗](../math/matrix-power.md#semiring) › (min,+)・(max,+) などの半環の行列と単位元・零元 |
| abc456_g Count Holidays | G | 2488 | [包除原理](../comb/inclusion-exclusion.md#symmetric) › 対称なら破る個数 k ごとに足す、[重複組合せ](../comb/stars-and-bars.md#stars-bars) › 玉と仕切りの対応（非負解と正の解）、[数え上げの考え方](../comb/counting-mindset.md#exactly-vs-at-most) › 「ちょうど」を「以下」の差で数える |
| abc457_d Raise Minimum | D | 677 | [答えで二分探索](../basics/binary-search-answer.md#minimax) › 最大値の最小化・最小値の最大化 |
| abc457_e Crossing Table Cloth | E | 1428 | [ソートで考える](../basics/sorting-techniques.md)、[二分探索](../basics/binary-search.md#lower-bound) › lower_bound・upper_bound と個数の数え方 |
| abc457_f Second Gap | F | 2167 | [対称性・鳩の巣原理・場合分け](../thinking/symmetry-pigeonhole-casework.md#casework) › 場合分け（端の場合・大小関係・操作の順序によらないこと）、[数え上げの考え方](../comb/counting-mindset.md)、[DP の状態の設計](../dp/dp-state-design.md#typical-summaries) › 典型の要約（直前の値・on/off・偶奇・個数・上限で打ち切った値） |
| abc457_g Catch All Apples | G | 1928 | [マンハッタン距離と 45 度回転](../geometry/manhattan-chebyshev.md#rotate-45) › 45 度回転：\|Δx\|+\|Δy\| = max(\|Δu\|, \|Δv\|) になる理由、[最長増加部分列](../dp/lis.md#dilworth) › Dilworth の定理（増加列への最小分割数＝最長減少部分列の長さ） |
| abc458_d Chalkboard Median | D | 450 | [上位 K 個の和と中央値の管理](../ds/top-k-multiset.md#median) › 中央値を保つ（個数の差を 1 以内に。削除がなければヒープ 2 本）と Σ\|x − a_i\| の更新 |
| abc458_e Count 123 | E | 1309 | [一部を固定して数える](../thinking/fix-variable.md)、[二項係数の前計算](../comb/binomial-precompute.md) |
| abc458_f Critical Misread | F | 1744 | [Aho-Corasick 法](../string/aho-corasick.md#as-automaton) › 照合オートマトンとして使う（DP・行列累乗）、[照合オートマトン上の DP](../string/string-automaton-dp.md#matrix-power) › N が巨大なとき：遷移行列の累乗・ダブリング、[行列累乗](../math/matrix-power.md#dp-transition) › DP の遷移を行列にする（照合の状態・末尾の数文字・グリッドの境界の状態） |
| abc458_g Children Yearn for the Evil Kindergarten | G | 2831 | [答えで二分探索](../basics/binary-search-answer.md#dp-check) › 判定を DP で作る（決め打ちごとに初期化し直す）、[Monge 性による DP の高速化](../dp/monge.md#convex-max-plus-convolution) › 凸な列どうしの (max,+) 畳み込み（差分のマージ）、[Slope Trick](../dp/slope-trick.md#breakpoints) › 凸関数を傾きの変わる点の集まりで表す |
| abc459_d Adjacent Distinct String | D | 701 | [貪欲法の考え方と正当性](../basics/greedy-basics.md#strongest-first) › 基準を決めて強い順に使う、[対称性・鳩の巣原理・場合分け](../thinking/symmetry-pigeonhole-casework.md#pigeonhole) › 鳩の巣原理（必ず一致が起きる・探索の打ち切り回数） |
| abc459_e Select from Subtrees | E | 1298 | [葉から考える](../tree/leaf-first.md#send-up) › 帰りがけ順に葉から情報を上へ送る、[根付き木と走査順](../tree/tree-traversal.md#pre-post-order) › 行きがけ順と帰りがけ順（子から親へ集約する）、[二項係数の前計算](../comb/binomial-precompute.md) |
| abc459_f -1, +1 | F | 2163 | [差分列への言い換え](../basics/difference-sequence.md#strict-to-weak) › 狭義の条件は a_i − i で広義に直してから差分を取る、[言い換えの典型](../thinking/reformulation.md#operations) › 操作の言い換え（区間操作を差分列で・隣接 swap を転倒数で） |
| abc459_g Golf 2 | G | 3123 | [偶奇に着目する](../thinking/parity.md#checkerboard) › 市松模様の偶奇、[拡張ユークリッドの互除法と一次合同式](../math/ext-gcd.md#general-solution) › ax + by = c の解の存在条件と一般解 x = x0 + k·b/g |
| abc460_d Repeatedly Repainting | D | 1216 | [幅優先探索（BFS）と無重み最短路](../graph/bfs.md#multi-source) › 多始点 BFS（超頂点から距離 0 の辺を張るのと同じ）、[グリッドグラフ](../graph/grid-graph.md#neighbors) › 4 近傍・8 近傍と dx・dy の配列、[偶奇に着目する](../thinking/parity.md#alternating) › 1 歩ごとに偶奇が入れ替わる |
| abc460_e x + y ≡ x + y | E | 1362 | [桁と mod](../math/digit-and-mod.md#concatenation) › 数の連結：x の後ろに d 桁の y を付けると x·10^d + y、[整数の割り算と余り](../math/integer-division.md#count-multiples) › 区間の中の K の倍数の個数と、x 以上で m で割って r 余る最小の数、[GCD・LCM とユークリッドの互除法](../math/gcd-lcm.md) |
| abc460_f Farthest Pair Query | F | 1987 | [木の直径と最遠点](../tree/tree-diameter.md)、[セグメント木に何を載せるか](../ds/segment-tree-monoids.md)、[最小共通祖先（LCA）](../tree/lca.md#distance) › 距離 = dep(u) + dep(v) − 2 dep(lca) |
| abc460_g Vertex Flip Query | G | 2838 | [HL 分解](../tree/hld.md)、[セグメント木](../ds/segment-tree.md) |
| abc461_d Count Subgrid Sum = K | D | 914 | [2 次元累積和](../basics/prefix-sum-2d.md#formula) › 前計算の式と長方形の和（4 項の包除）、[尺取り法](../basics/two-pointers.md)、[一部を固定して数える](../thinking/fix-variable.md) |
| abc461_e E-liter | E | 1431 | [セグメント木](../ds/segment-tree.md)、[主客転倒・寄与](../thinking/contribution.md) |
| abc461_f Total Product is N | F | 1940 | [約数の個数の上界と高度合成数](../math/divisor-count-bound.md#divisor-dp) › 約数を状態にした DP（約数の個数が少ないことを使う）、[ナップサック DP](../dp/knapsack-01.md)、[約数列挙と素数判定](../math/divisor-enum.md#enumerate) › 約数の列挙とソート・平方数での重複 |
| abc461_g Graph Problem 2026 | G | 2391 | [König の定理](../graph/konig-theorem.md#lp-half-integrality) › 頂点を 2 倍にして二部グラフにする（LP の半整数性）、[二部マッチング](../graph/bipartite-matching.md#reduction) › 最大流への帰着（容量 1） |
| abc462_d Accomplice | D | 798 | [いもす法](../basics/imos.md#imos-1d) › 1 次元のいもす法（閉区間なら右端 + 1 に −x） |
| abc462_e Alternating Costs | E | 1226 | [対称性・鳩の巣原理・場合分け](../thinking/symmetry-pigeonhole-casework.md#symmetry-cases) › 対称性で場合を減らす（N ≤ M に入れ替える） |
| abc462_f More ABC | F | 1952 | [DP の状態の設計](../dp/dp-state-design.md#last-characters) › 末尾の数文字を状態にする（禁止された並び・回文を避ける） |
| abc462_g Completely Wrong | G | 2232 | [包除原理](../comb/inclusion-exclusion.md#derangement) › 撹乱順列（完全順列）、[分割統治 FFT・オンライン畳み込み](../math/online-convolution.md#product-of-many) › 多数の多項式の積（次数の小さいものから掛ける・分割統治） |
| abc463_d Maximize the Gap | D | 838 | [答えで二分探索](../basics/binary-search-answer.md#greedy-check) › 判定を貪欲・探索で作る |
| abc463_e Roads and Gates | E | 1055 | [状態を頂点にする](../graph/extended-dijkstra.md#super-vertex) › 超頂点・補助頂点で辺の数を減らす、[ダイクストラ法](../graph/dijkstra.md) |
| abc463_f Senshuraku | F | 2127 | [確率の基本](../comb/probability-basics.md#conditional) › 条件付き確率と全確率の公式、[対称性・鳩の巣原理・場合分け](../thinking/symmetry-pigeonhole-casework.md#casework) › 場合分け（端の場合・大小関係・操作の順序によらないこと）、[二項係数の前計算](../comb/binomial-precompute.md) |
| abc463_g Random Walk Distance | G | 2452 | [確率 DP](../comb/probability-dp.md#random-walk) › ランダムウォークと二項係数、[二項係数の前計算](../comb/binomial-precompute.md)、[クエリの先読み](../ds/offline-queries.md) |
| abc464_d Celester | D | 752 | [DP の状態の設計](../dp/dp-state-design.md#typical-summaries) › 典型の要約（直前の値・on/off・偶奇・個数・上限で打ち切った値） |
| abc464_e Fill-Rect Query | E | 1075 | [いもす法](../basics/imos.md#imos-2d) › 2 次元いもす法（四隅に ±1、横と縦に累積） |
| abc464_f Random Vault Heist | F | 2225 | [対称性で確率を求める](../comb/probability-symmetry.md#random-permutation) › 残りから一様に選ぶ = ランダムな順列、[期待値の線形性と指示確率変数](../comb/linearity-of-expectation.md)、[半分全列挙](../basics/meet-in-the-middle.md#combine-halves) › 前半・後半を列挙して突き合わせる（ソート＋二分探索・尺取り）、[尺取り法](../basics/two-pointers.md) |
| abc464_g Celester 2 | G | 2592 | [Alien DP](../dp/alien-dp.md#undoable-greedy) › 取り消し付きの貪欲で解ける場合（優先度付きキュー）、[優先度付きキューを使う貪欲](../basics/greedy-priority-queue.md#regret) › 選んだものを後から入れ替える（後悔付き貪欲。一般形は Alien DP のページ） |
| abc465_d X to Y | D | 839 | [完全二分木](../tree/complete-binary-tree.md#lca-by-index) › 番号だけで LCA を求める（大きい方を 2 で割る）、[完全二分木](../tree/complete-binary-tree.md#k-ary) › K 分木への一般化 |
| abc465_e Digit Circus | E | 1417 | [桁 DP](../dp/digit-dp.md#extra-state) › 問題の情報を状態に足す（桁和の余り・個数） |
| abc465_f Sjeltzer? | F | 1754 | [2 次元累積和](../basics/prefix-sum-2d.md#higher-dimensions) › 3 次元以上（項の数と符号の決め方）、[いもす法](../basics/imos.md) |
| abc465_g Sum of Mex of Mod of Linear | G | 3082 | —（対応するページがない） |
| abc466_d Placing Rooks | D | 494 | —（対応するページがない） |
| abc466_e Range Flip | E | 1027 | [いもす法](../basics/imos.md#range-flip) › 区間反転を切り替え点 2 つで表す、[フェーズを状態に持つ DP](../dp/dp-phase.md#flip-interval) › 区間の反転・変更を段階の切り替えで表す、[言い換えの典型](../thinking/reformulation.md#operations) › 操作の言い換え（区間操作を差分列で・隣接 swap を転倒数で） |
| abc466_f Many Mod Calculation | F | 1887 | [後ろから・逆順に考える](../thinking/reverse-thinking.md)、[set・multiset・map の応用](../ds/ordered-set.md) |
| abc466_g Segment Sum Constraints | G | 3347 | [桁 DP の応用](../dp/digit-dp-advanced.md#carry) › 下の桁からの繰り上がりを状態にする、[桁 DP](../dp/digit-dp.md#binary) › 2 進の桁 DP（XOR・AND） |
| abc467_d Concentric Circles | D | 928 | [誤差の扱いと整数での処理](../geometry/geometry-precision.md#line-normalization) › 方向・直線の正規化：gcd で約分し、(1, −1) と (−1, 1) を同じにする符号の決め方、[ベクトルと外積](../geometry/geometry-vectors.md#cross-and-dot) › 外積と内積の意味（符号と大きさ） |
| abc467_e Adjacent Sums (hard) | E | 1694 | [一部を固定して数える](../thinking/fix-variable.md)、[偶奇に着目する](../thinking/parity.md#alternating) › 1 歩ごとに偶奇が入れ替わる、[イベントソートと平面走査の基本](../basics/event-sort.md) |
| abc467_f Email Scheduling Optimization | F | 2052 | [交換論法と比較関数の設計](../basics/exchange-argument.md)、[セグメント木](../ds/segment-tree.md)、[座標圧縮](../basics/coordinate-compression.md) |
| abc467_g Many Sweets Problem | G | 2544 | [クエリの先読み](../ds/offline-queries.md)、[マージソート木](../ds/merge-sort-tree.md#bit-per-level) › 各段に BIT を持たせる（先読みと組む）、[BIT（Fenwick Tree）](../ds/fenwick-tree.md) |
| abc468_d Pre-Palindrome | D | 683 | [回文の扱いと Manacher](../string/palindrome.md#expand-center) › 中心から伸ばす O(N^2)（奇数長と偶数長の中心） |
| abc468_e Sum of Average | E | 1038 | [主客転倒・寄与](../thinking/contribution.md#swap-roles) › 数える対象を入れ替える（表の行と列。式の規則は Σ の変形のページ）、[逆元と mod での割り算](../math/mod-inverse.md#inverse-table) › 逆元表を O(N) で作る方法と階乗の逆元、[累積和](../basics/prefix-sum.md) |
| abc468_f Chmax | F | 1693 | [最長増加部分列](../dp/lis.md#binary-search) › 二分探索版（L が単調になる理由・狭義は lower_bound、広義は upper_bound）、[貪欲法の考え方と正当性](../basics/greedy-basics.md) |
| abc468_g Restricted Permutation | G | 1975 | [挿入 DP・箱根駅伝 DP](../dp/insertion-dp.md) |
| abc469_d The Big Two | D | 1102 | [全探索の設計](../basics/brute-force.md#small-candidates) › 候補が少ないことに気づく（答えの側・小さい次元・約数の個数・log 回の収束） |
| abc469_e Pro Exam Eligibility | E | 1566 | [平均・中央値の最大化](../basics/fractional-binary-search.md#average) › 平均の言い換え（x を引いた和の符号で判定する）、[累積和](../basics/prefix-sum.md) |
| abc469_f GCD Maximum Spanning Tree | F | 1567 | [最小全域木](../graph/minimum-spanning-tree.md#reduce-candidates) › 辺の候補を減らす（ソートした隣どうし・約数で絞る）、[最小全域木](../graph/minimum-spanning-tree.md#maximum) › 最大全域木、[調和級数と倍数の列挙](../math/harmonic-sum.md#collect-multiples) › 倍数を回して集める（d の倍数である要素の個数・和） |
| abc469_g K-nacci Operations | G | 2804 | [行列累乗](../math/matrix-power.md#write-as-matrix) › 漸化式・状態の遷移を行列で書く（定数項を状態に入れる） |
| abc470_d Inverse and Swap | D | 777 | [順列と置換](../patterns/permutation.md#inverse) › 位置と値の両方から引く操作 → 逆置換を同時に持つ |
| abc470_e Concentration | E | 2096 | [最適戦略の期待値](../comb/optimal-strategy-expectation.md#state-design) › 残すもの・知っている情報を状態にする、[メモ化再帰](../dp/memoized-recursion.md) |
| abc470_f Googol Swaps | F | 1604 | [置換の偶奇](../comb/permutation-parity.md#duplicates) › 同じ値があれば偶奇を調整できる、[連結成分](../graph/connected-components.md)、[多項係数](../comb/multinomial-coefficient.md) |
| abc470_g Σex | G | 2097 | [主客転倒・寄与](../thinking/contribution.md)、[尺取り法](../basics/two-pointers.md)、[遅延セグメント木](../ds/lazy-segment-tree.md)、[言い換えの典型](../thinking/reformulation.md#then-data-structure) › 言い換えてからデータ構造に載せる |
| abc471_d Chargers | D | 570 | [優先度付きキュー](../ds/priority-queue.md) |
| abc471_e Sum of Square of Sum | E | 990 | [Σ の変形](../math/sigma-manipulation.md#formulas) › よく使う和の公式と Σ_{i≠j} a_i a_j = (Σa)² − Σa²、[数え上げの考え方](../comb/counting-mindset.md#contribution-with-binomial) › 二項係数と組み合わせた寄与（残りの選び方を掛ける）、[二項係数の前計算](../comb/binomial-precompute.md) |
| abc471_f Concat (maximize) | F | 1895 | [交換論法と比較関数の設計](../basics/exchange-argument.md#concatenation) › 連結の比較（a+b と b+a）、[貪欲法の考え方と正当性](../basics/greedy-basics.md) |
| abc471_g Caeser Syllables | G | 2464 | [主客転倒・寄与](../thinking/contribution.md#swap-roles) › 数える対象を入れ替える（表の行と列。式の規則は Σ の変形のページ）、[畳み込みの使い方](../math/convolution-ntt.md) |
| abc472_d Bomber Mad | D | 605 | [幅優先探索（BFS）と無重み最短路](../graph/bfs.md#multi-source) › 多始点 BFS（超頂点から距離 0 の辺を張るのと同じ） |
| abc472_e Odd Cycle | E | 1029 | [二部グラフ判定](../graph/bipartite-graph.md#odd-cycle) › 二部グラフでないことと奇閉路があることは同じ |
| abc472_f Centroid of a Slice | F | 1707 | [ベクトルと外積](../geometry/geometry-vectors.md#polygon-area) › 三角形・多角形の面積：座標の公式（面積の 2 倍を整数のまま扱う）、[累積和](../basics/prefix-sum.md) |
| abc472_g Cascading Grid | G | 2018 | [燃やす埋める](../graph/project-selection.md#closure) › 最大重み閉包（依存関係）、[最小カット](../graph/min-cut.md) |
| abc473_d Coefficient Stair | D | 838 | [再帰による全列挙](../basics/recursive-enumeration.md) |
| abc473_e K-Divisible Subarrays | E | 966 | [累積和と連想配列で区間を数える](../basics/prefix-sum-counting.md#same-remainder) › 余りが等しい組（M の倍数の区間・負の余りの正規化）、[貪欲法の考え方と正当性](../basics/greedy-basics.md) |
| abc473_f A/AB Insertion | F | 1303 | [遅延セグメント木](../ds/lazy-segment-tree.md#acl-standard) › ACL の lazy_segtree で標準の型を呼ぶ、[累積和](../basics/prefix-sum.md) |
| abc473_g Wipeout | G | 1974 | [対称性で確率を求める](../comb/probability-symmetry.md#random-permutation) › 残りから一様に選ぶ = ランダムな順列、[挿入 DP・箱根駅伝 DP](../dp/insertion-dp.md)、[形式的冪級数と多項式の演算](../math/fps-basics.md) |
| abc474_d Outweigh | D | 389 | [構築問題の考え方](../thinking/construction.md) |
| abc474_e One Time Coupon | E | 1153 | [ソートで考える](../basics/sorting-techniques.md)、[全探索の設計](../basics/brute-force.md)、[累積和](../basics/prefix-sum.md#left-right) › 左右からの累積（1 つ除いた gcd・max） |
| abc474_f Increment All Divisors | F | 1911 | [約数・倍数のゼータ変換とメビウス変換](../comb/zeta-mobius-divisor.md#inverse) › 逆変換（メビウス変換）と回す向き |
| abc474_g LRUD Moving 2 | G | 2280 | [偶奇に着目する](../thinking/parity.md#checkerboard) › 市松模様の偶奇、[構築問題の考え方](../thinking/construction.md#small-cases) › 小さい N で作って規則を一般化する |
| abc475_d Alphametic Prime | D | 741 | [再帰による全列挙](../basics/recursive-enumeration.md)、[エラトステネスの篩](../math/sieve-eratosthenes.md) |
| abc475_e Quiz Competition: Qualifiers | E | 1737 | [言い換えの典型](../thinking/reformulation.md)、[set・multiset・map の応用](../ds/ordered-set.md) |
| abc475_f Rectangle Filling | F | 1916 | [包除原理](../comb/inclusion-exclusion.md)、[2 次元累積和](../basics/prefix-sum-2d.md) |
| abc475_g Has Many Divisors | G | 2360 | [約数の個数の上界と高度合成数](../math/divisor-count-bound.md#enumerate-hcn) › 高度合成数の列挙（小さい素数の指数が単調に減る形を DFS で） |
| abc476_d Automat | D | 860 | [全探索の設計](../basics/brute-force.md)、[累積和](../basics/prefix-sum.md#with-binary-search) › 累積和の上で二分探索・尺取り、[二分探索](../basics/binary-search.md) |
| abc476_e Min-Max Swap | E | 964 | [セグメント木](../ds/segment-tree.md) |
| abc476_f Chebyshev Cafe | F | 1728 | [マンハッタン距離と 45 度回転](../geometry/manhattan-chebyshev.md#remove-abs) › 絶対値の外し方：向きを固定して場合分けし、盤面を反転してもう一度、[グリッド上の DP](../dp/dp-grid.md#directional-prefix) › 方向ごとの累積和で遷移をまとめる |
| abc476_g Increasing Popcount | G | 2477 | [最長増加部分列](../dp/lis.md#dilworth) › Dilworth の定理（増加列への最小分割数＝最長減少部分列の長さ）、[bit 演算の基本と XOR の性質](../basics/bit-operations.md#popcount) › popcount・最下位ビット、[再帰的な構造](../basics/recursion-structure.md)、[二項係数の意味と性質](../comb/binomial-coefficient.md) |
| abc477_d Masking Tape | D | 946 | [後ろから・逆順に考える](../thinking/reverse-thinking.md#decide-from-back) › 後ろから決めると一意になる |
| abc477_e Wheel Distance | E | 1235 | [ダイクストラ法](../graph/dijkstra.md)、[累積和](../basics/prefix-sum.md#circular) › 円環は 2 周分に伸ばす |
| abc477_f Count Cells in a Window | F | 1629 | [クエリの先読み](../ds/offline-queries.md)、[平面走査](../ds/sweep-line-2d.md#rectangle-count) › 支配点の数え上げと長方形内の点の数、[遅延セグメント木](../ds/lazy-segment-tree.md) |
| abc477_g Frequency Query on Tree | G | 2226 | [Mo's algorithm](../ds/mo-algorithm.md#mo-on-tree) › 木上の Mo（入りと出の両方を記録した列で、パスを区間にする。LCA を別に足す）、[オイラーツアー](../tree/euler-tour.md#mo-on-tree) › 木上の Mo（データ構造の章）、[最小共通祖先（LCA）](../tree/lca.md) |
| abc478_d Range Set Insertion Query | D | 729 | [イベントソートと平面走査の基本](../basics/event-sort.md#make-events) › イベントの作り方と同じ座標での処理順 |
| abc478_e lt and le | E | 1376 | [強連結成分分解（SCC）](../graph/scc.md#condensation) › 縮約したグラフが DAG になる理由、[トポロジカルソート](../graph/topological-sort.md) |
| abc478_f Min-First Search | F | 1588 | [木の構築・復元](../tree/tree-construction.md#from-order) › 訪問順から親の候補を数える、[セグメント木上の二分探索](../ds/segment-tree-binary-search.md) |
| abc478_g Division Point Hull | G | 2582 | [分割統治](../basics/divide-and-conquer.md)、[凸包と凸多角形](../geometry/convex-hull.md#andrew) › Andrew 法（monotone chain）：下側と上側を作る、[発展の幾何](../geometry/advanced-geometry.md#minkowski-sum) › ミンコフスキー和（凸包の和） |
| abc479_d Back and Forth Distance | D | 563 | [累積和](../basics/prefix-sum.md#left-right) › 左右からの累積（1 つ除いた gcd・max） |
| abc479_e Cut and Add | E | 1000 | [辺で切って数える](../tree/tree-edge-contribution.md#edge-pairs) › 辺を通るペアは s(N−s) 個、[根付き木と走査順](../tree/tree-traversal.md#parent-depth-size) › 親・深さ・部分木サイズを求める |
| abc479_f Narrow Passage | F | 1938 | [転倒数](../ds/inversion-number.md#adjacent-swaps) › なぜ隣接 swap の最小回数か（1 回の隣接 swap で転倒数はちょうど 1 増減する）、[言い換えの典型](../thinking/reformulation.md#operations) › 操作の言い換え（区間操作を差分列で・隣接 swap を転倒数で） |
| abc479_g Tuning | G | 2386 | [偏角ソート](../geometry/argument-sort.md#range-count) › 並べた後に：角度の範囲の点の数（累積和）、[累積和](../basics/prefix-sum.md) |
| abc480_d Concatenation of Prefixes | D | 864 | [累積和](../basics/prefix-sum.md#with-binary-search) › 累積和の上で二分探索・尺取り、[二分探索](../basics/binary-search.md) |
| abc480_e Product-Bounded Arithmetic Sequences | E | 1355 | [全探索の設計](../basics/brute-force.md)、[二分探索](../basics/binary-search.md) |
| abc480_f Cake Cutting | F | 1840 | [言い換えの典型](../thinking/reformulation.md)、[bitDP](../dp/bit-dp.md#set-only) › 集合だけを状態にする（マッチングの数） |
| abc480_g Zonal Score Minimization | G | 2100 | [インライン DP](../dp/inline-dp.md#with-monotonic-stack) › 単調スタックと組み合わせる、[遅延セグメント木](../ds/lazy-segment-tree.md)、[単調スタックとスライド最小値](../ds/monotonic-stack.md) |

<!-- textlint-enable -->
<!-- gen:end recent-abc -->

## 問題集の問題 → ページ {#sets-to-pages}

次の表は、本文の例題・練習・力試しに載せた問題集の問題を問題集ごとに並べ、載せたページと役割を示したものである。問題集で解けなかった問題から、その手法のページを引くのに使う。

- 「ページ（役割）」の役割は、そのページでの扱い（例題は方針と解法の詳細があり、練習・力試しは問題の一覧だけ）である。例題として載せたページから読むとよい。
- 問題集の difficulty は付かないので、diff の列はほとんど「—」になる。典型90問は題名の★を見る。
- 問題集の後に、ABC・ARC・AGC 以外の本番のコンテスト（企業の名前の付いたコンテストなど）の問題も、コンテストごとに並ぶ。
- 表は本文の問題の一覧から自動で作るので、ページが増えると行も増える。

<!-- gen:begin problem-sets -->
<!-- textlint-disable -->

### 競プロ典型 90 問 {#problem-sets-typical90}

| 問題 | diff | ページ（役割） |
| --- | --- | --- |
| 典型90 001. Yokan Party（★4） | — | [答えで二分探索](../basics/binary-search-answer.md)（例題） |
| 典型90 002. Encyclopedia of Parentheses（★3） | — | [再帰的な構造](../basics/recursion-structure.md)（練習） |
| 典型90 003. Longest Circular Road（★4） | — | [木の直径と最遠点](../tree/tree-diameter.md)（練習） |
| 典型90 005. Restricted Digits（★7） | — | [行列累乗](../math/matrix-power.md)（力試し） |
| 典型90 006. Smallest Subsequence（★5） | — | [辞書順最小を前から決める貪欲](../basics/lexicographic-greedy.md)（練習）、[部分列 DP](../dp/subsequence-dp.md)（練習）、[部分列の判定と次の出現位置の表](../string/subsequence-matching.md)（練習） |
| 典型90 008. AtCounter（★4） | — | [フェーズを状態に持つ DP](../dp/dp-phase.md)（例題） |
| 典型90 009. Three Point Angle（★6） | — | [偏角ソート](../geometry/argument-sort.md)（例題） |
| 典型90 011. Gravy Jobs（★6） | — | [並べ替えてから DP する](../dp/exchange-argument-dp.md)（例題） |
| 典型90 012. Red Painting（★4） | — | [グリッドグラフ](../graph/grid-graph.md)（練習）、[Union-Find](../ds/union-find.md)（練習） |
| 典型90 013. Passing（★5） | — | [ダイクストラ法](../graph/dijkstra.md)（練習） |
| 典型90 014. We Used to Sing a Song Together（★3） | — | [ソートで考える](../basics/sorting-techniques.md)（練習） |
| 典型90 015. Don't be too close（★6） | — | [重複組合せ](../comb/stars-and-bars.md)（練習） |
| 典型90 019. Pick Two（★6） | — | [区間 DP](../dp/interval-dp.md)（例題） |
| 典型90 021. Come Back in One Piece（★5） | — | [強連結成分分解（SCC）](../graph/scc.md)（例題） |
| 典型90 022. Cubic Cake（★2） | — | [GCD・LCM とユークリッドの互除法](../math/gcd-lcm.md)（練習） |
| 典型90 023. Avoid War（★7） | — | [プロファイル DP](../dp/broken-profile-dp.md)（練習） |
| 典型90 024. Select +／- One（★2） | — | [偶奇に着目する](../thinking/parity.md)（練習） |
| 典型90 025. Digit Product Equation（★7） | — | [素因数の指数で考える](../math/prime-exponent-vector.md)（力試し） |
| 典型90 026. Independent Set on a Tree（★4） | — | [木の 2 色塗り分けと距離の偶奇](../tree/tree-bipartite.md)（練習） |
| 典型90 028. Cluttered Paper（★4） | — | [いもす法](../basics/imos.md)（練習） |
| 典型90 029. Long Bricks（★5） | — | [座標圧縮](../basics/coordinate-compression.md)（練習）、[遅延セグメント木](../ds/lazy-segment-tree.md)（練習） |
| 典型90 030. K Factors（★5） | — | [エラトステネスの篩](../math/sieve-eratosthenes.md)（練習） |
| 典型90 031. VS AtCoder（★6） | — | [Grundy 数と Sprague-Grundy の定理](../comb/grundy-number.md)（練習） |
| 典型90 034. There are few types of elements（★4） | — | [尺取り法](../basics/two-pointers.md)（練習） |
| 典型90 035. Preserve Connectivity（★7） | — | [Auxiliary Tree](../tree/auxiliary-tree.md)（例題） |
| 典型90 037. Don't Leave the Spice（★5） | — | [セグメント木・スライド最小値による DP の高速化](../dp/dp-segment-tree.md)（例題） |
| 典型90 038. Large LCM（★3） | — | [整数の割り算と余り](../math/integer-division.md)（練習） |
| 典型90 039. Tree Distance（★5） | — | [辺で切って数える](../tree/tree-edge-contribution.md)（例題） |
| 典型90 040. Get More Money（★7） | — | [燃やす埋める](../graph/project-selection.md)（例題） |
| 典型90 041. Piles in AtCoder Farm（★7） | — | [凸包と凸多角形](../geometry/convex-hull.md)（例題） |
| 典型90 042. Multiple of 9（★4） | — | [累積和・いもす法による DP の高速化](../dp/dp-prefix-sum.md)（練習） |
| 典型90 043. Maze Challenge with Lack of Sleep（★4） | — | [01-BFS](../graph/zero-one-bfs.md)（練習） |
| 典型90 044. Shift and Swapping（★3） | — | [全体への操作を変数で持つ](../ds/global-offset.md)（練習） |
| 典型90 045. Simple Grouping（★6） | — | [部分集合を列挙する DP](../dp/subset-enumeration-dp.md)（練習） |
| 典型90 047. Monochromatic Diagonal（★7） | — | [ローリングハッシュ](../string/rolling-hash.md)（力試し）、[ハッシュの衝突と安全な設計](../string/hash-safety.md)（例題） |
| 典型90 049. Flip Digits 2（★6） | — | [最小全域木](../graph/minimum-spanning-tree.md)（練習） |
| 典型90 051. Typical Shop（★5） | — | [半分全列挙](../basics/meet-in-the-middle.md)（例題） |
| 典型90 055. Select 5（★2） | — | [計算量の見積もり](../basics/complexity-estimation.md)（例題） |
| 典型90 056. Lucky Bag（★5） | — | [DP の復元](../dp/dp-reconstruction.md)（例題） |
| 典型90 057. Flip Flap（★6） | — | [掃き出し法](../math/gaussian-elimination.md)（例題） |
| 典型90 058. Original Calculator（★4） | — | [周期性の検出](../basics/periodicity.md)（練習） |
| 典型90 059. Many Graph Queries（★7） | — | [bitset による高速化](../misc/bitset-speedup.md)（例題） |
| 典型90 060. Chimera（★5） | — | [最長増加部分列](../dp/lis.md)（例題） |
| 典型90 063. Monochromatic Subgrid（★4） | — | [全探索の設計](../basics/brute-force.md)（練習） |
| 典型90 064. Uplift（★3） | — | [いもす法](../basics/imos.md)（練習） |
| 典型90 065. RGB Balls 2（★7） | — | [畳み込みの使い方](../math/convolution-ntt.md)（練習） |
| 典型90 066. Various Arrays（★5） | — | [期待値の線形性と指示確率変数](../comb/linearity-of-expectation.md)（例題） |
| 典型90 067. Base 8 to 9（★2） | — | [N 進法](../math/base-conversion.md)（練習） |
| 典型90 068. Paired Information（★5） | — | [重み付き Union-Find](../ds/weighted-union-find.md)（練習） |
| 典型90 069. Colorful Blocks 2（★3） | — | [繰り返し二乗法](../math/mod-pow.md)（練習）、[和・積の法則と順列・組合せ](../comb/counting-basics.md)（例題） |
| 典型90 070. Plant Planning（★4） | — | [絶対値の和の最小化と中央値](../basics/median-absolute.md)（練習） |
| 典型90 071. Fuzzy Priority（★7） | — | [トポロジカルソート](../graph/topological-sort.md)（力試し） |
| 典型90 072. Loop Railway Plan（★4） | — | [計算量の見積もり](../basics/complexity-estimation.md)（練習）、[深さ優先探索（DFS）](../graph/dfs.md)（練習） |
| 典型90 073. We Need Both a and b（★5） | — | [木 DP](../dp/tree-dp.md)（練習） |
| 典型90 075. Magic For Balls（★3） | — | [約数と倍数](../patterns/divisors-and-multiples.md)（練習） |
| 典型90 077. Planes on a 2D Plane（★7） | — | [二部マッチング](../graph/bipartite-matching.md)（例題） |
| 典型90 078. Easy Graph Problem（★2） | — | [グラフの表現と用語](../graph/graph-basics.md)（例題） |
| 典型90 079. Two by Two（★3） | — | [不変量・単調に変わる量](../thinking/invariant.md)（練習） |
| 典型90 082. Counting Numbers（★3） | — | [逆元と mod での割り算](../math/mod-inverse.md)（例題） |
| 典型90 083. Colorful Graph（★6） | — | [次数による平方分割](../graph/degree-sqrt.md)（例題） |
| 典型90 084. There are two types of characters（★3） | — | [ランレングス圧縮](../basics/run-length-encoding.md)（練習） |
| 典型90 085. Multiplication 085（★4） | — | [約数の個数の上界と高度合成数](../math/divisor-count-bound.md)（練習） |
| 典型90 087. Chokudai's Demand（★5） | — | [ワーシャルフロイド法](../graph/warshall-floyd.md)（練習） |
| 典型90 089. Partitions and Inversions（★7） | — | [区間分割 DP](../dp/dp-sequence-partition.md)（練習） |
| 典型90 090. Tenkei90's Last Problem（★7） | — | [DP の高速化の選び方](../dp/dp-speedup-overview.md)（力試し） |

### EDPC（Educational DP Contest） {#problem-sets-dp}

| 問題 | diff | ページ（役割） |
| --- | --- | --- |
| EDPC A. Frog 1 | — | [DP の基本](../dp/dp-basics.md)（例題） |
| EDPC B. Frog 2 | — | [DP の基本](../dp/dp-basics.md)（練習） |
| EDPC C. Vacation | — | [DP の状態の設計](../dp/dp-state-design.md)（例題） |
| EDPC D. Knapsack 1 | — | [ナップサック DP](../dp/knapsack-01.md)（例題） |
| EDPC E. Knapsack 2 | — | [DP の状態の削減](../dp/dp-dimension-reduction.md)（例題） |
| EDPC F. LCS | — | [DP の復元](../dp/dp-reconstruction.md)（練習）、[最長共通部分列と編集距離](../dp/lcs.md)（例題） |
| EDPC G. Longest Path | — | [メモ化再帰](../dp/memoized-recursion.md)（練習）、[DAG 上の DP](../dp/dp-dag.md)（例題） |
| EDPC H. Grid 1 | — | [グリッド上の DP](../dp/dp-grid.md)（例題） |
| EDPC I. Coins | — | [確率 DP](../comb/probability-dp.md)（例題） |
| EDPC J. Sushi | — | [期待値 DP](../comb/expected-value-dp.md)（例題） |
| EDPC K. Stones | — | [ゲームの基本と勝敗の DP](../comb/game-basics.md)（例題） |
| EDPC L. Deque | — | [区間 DP](../dp/interval-dp.md)（練習）、[ミニマックス](../comb/minimax.md)（例題） |
| EDPC M. Candies | — | [累積和・いもす法による DP の高速化](../dp/dp-prefix-sum.md)（例題） |
| EDPC N. Slimes | — | [区間 DP](../dp/interval-dp.md)（例題） |
| EDPC O. Matching | — | [bitDP](../dp/bit-dp.md)（例題） |
| EDPC P. Independent Set | — | [木 DP](../dp/tree-dp.md)（例題） |
| EDPC Q. Flowers | — | [最長増加部分列](../dp/lis.md)（練習）、[セグメント木・スライド最小値による DP の高速化](../dp/dp-segment-tree.md)（例題） |
| EDPC R. Walk | — | [行列累乗](../math/matrix-power.md)（例題） |
| EDPC S. Digit Sum | — | [桁 DP](../dp/digit-dp.md)（例題） |
| EDPC T. Permutation | — | [挿入 DP・箱根駅伝 DP](../dp/insertion-dp.md)（例題） |
| EDPC U. Grouping | — | [部分集合を列挙する DP](../dp/subset-enumeration-dp.md)（例題） |
| EDPC V. Subtree | — | [全方位木 DP](../dp/rerooting.md)（例題） |
| EDPC W. Intervals | — | [インライン DP](../dp/inline-dp.md)（例題） |
| EDPC X. Tower | — | [並べ替えてから DP する](../dp/exchange-argument-dp.md)（例題） |
| EDPC Y. Grid 2 | — | [包除 DP](../comb/inclusion-exclusion-dp.md)（例題） |
| EDPC Z. Frog 3 | — | [Convex Hull Trick と Li Chao Tree](../dp/cht.md)（例題） |

### TDPC（Typical DP Contest） {#problem-sets-tdpc}

| 問題 | diff | ページ（役割） |
| --- | --- | --- |
| TDPC A. コンテスト | — | [部分和 DP](../dp/subset-sum.md)（例題） |
| TDPC B. ゲーム | — | [ミニマックス](../comb/minimax.md)（練習） |
| TDPC D. サイコロ | — | [確率 DP](../comb/probability-dp.md)（練習） |
| TDPC F. 準急 | — | [累積和・いもす法による DP の高速化](../dp/dp-prefix-sum.md)（練習） |
| TDPC G. 辞書順 | — | [部分列 DP](../dp/subsequence-dp.md)（力試し） |
| TDPC I. イウィ | — | [区間 DP](../dp/interval-dp.md)（練習） |
| TDPC J. ボール | — | [期待値 DP](../comb/expected-value-dp.md)（力試し） |
| TDPC K. ターゲット | — | [最長増加部分列](../dp/lis.md)（力試し）、[インライン DP](../dp/inline-dp.md)（練習） |
| TDPC N. 木 | — | [全方位木 DP](../dp/rerooting.md)（練習） |
| TDPC O. 文字列 | — | [挿入 DP・箱根駅伝 DP](../dp/insertion-dp.md)（練習） |
| TDPC P. うなぎ | — | [二乗の木 DP](../dp/tree-dp-square.md)（練習） |
| TDPC S. マス目 | — | [プロファイル DP](../dp/broken-profile-dp.md)（力試し） |
| TDPC T. フィボナッチ | — | [線形漸化式の高速化](../math/linear-recurrence-fast.md)（例題） |

### ACL Practice（AtCoder Library Practice Contest） {#problem-sets-practice2}

| 問題 | diff | ページ（役割） |
| --- | --- | --- |
| PRACTICE2 A. Disjoint Set Union | — | [Union-Find](../ds/union-find.md)（練習） |
| PRACTICE2 B. Fenwick Tree | — | [BIT（Fenwick Tree）](../ds/fenwick-tree.md)（例題） |
| PRACTICE2 C. Floor Sum | — | [floor sum](../math/floor-sum.md)（例題） |
| PRACTICE2 D. Maxflow | — | [最大流](../graph/max-flow.md)（例題） |
| PRACTICE2 E. MinCostFlow | — | [最小費用流](../graph/min-cost-flow.md)（例題） |
| PRACTICE2 F. Convolution | — | [畳み込みの使い方](../math/convolution-ntt.md)（例題） |
| PRACTICE2 G. SCC | — | [強連結成分分解（SCC）](../graph/scc.md)（例題） |
| PRACTICE2 H. Two SAT | — | [2-SAT](../graph/two-sat.md)（例題） |
| PRACTICE2 I. Number of Substrings | — | [Suffix Array と LCP 配列](../string/suffix-array.md)（例題） |
| PRACTICE2 J. Segment Tree | — | [セグメント木上の二分探索](../ds/segment-tree-binary-search.md)（例題） |
| PRACTICE2 K. Range Affine Range Sum | — | [遅延セグメント木](../ds/lazy-segment-tree.md)（例題） |
| PRACTICE2 L. Lazy Segment Tree | — | [遅延セグメント木の載せ方の型](../ds/lazy-segment-tree-patterns.md)（練習） |

### 鉄則本（競技プログラミングの鉄則 演習問題集） {#problem-sets-tessoku-book}

| 問題 | diff | ページ（役割） |
| --- | --- | --- |
| 鉄則本 A30. Combination | — | [二項係数の前計算](../comb/binomial-precompute.md)（例題） |
| 鉄則本 A33. Game 2 | — | [Nim と XOR](../comb/nim.md)（例題） |
| 鉄則本 A34. Game 3 | — | [Grundy 数と Sprague-Grundy の定理](../comb/grundy-number.md)（例題） |
| 鉄則本 A35. Game 4 | — | [ミニマックス](../comb/minimax.md)（練習） |
| 鉄則本 A54. Map | — | [STL コンテナの使い分け](../ds/stl-containers.md)（練習） |
| 鉄則本 A55. Set | — | [STL コンテナの使い分け](../ds/stl-containers.md)（練習） |
| 鉄則本 A58. RMQ (Range Maximum Queries) | — | [セグメント木](../ds/segment-tree.md)（練習） |
| 鉄則本 A60. Stock Price | — | [単調スタックとスライド最小値](../ds/monotonic-stack.md)（練習） |
| 鉄則本 A68. Maximum Flow | — | [最大流](../graph/max-flow.md)（練習） |
| 鉄則本 A69. Bipartite Matching | — | [二部マッチング](../graph/bipartite-matching.md)（練習） |
| 鉄則本 B68. ALGO Express | — | [燃やす埋める](../graph/project-selection.md)（練習） |

### アルゴ数学（アルゴリズムと数学 演習問題集） {#problem-sets-math-and-algorithm}

| 問題 | diff | ページ（役割） |
| --- | --- | --- |
| アルゴ数学 026. Coin Gacha | — | [幾何分布とコンプリートガチャ](../comb/coupon-collector.md)（練習） |
| アルゴ数学 053. Sum of 4^N | — | [逆元と mod での割り算](../math/mod-inverse.md)（練習）、[等比数列の和を mod で求める](../math/geometric-series-mod.md)（練習） |
| アルゴ数学 057. Domino Tiling | — | [行列累乗](../math/matrix-power.md)（練習） |

### ABL {#problem-sets-abl}

| 問題 | diff | ページ（役割） |
| --- | --- | --- |
| ABL D. Flat Subsequence | 1283 | [値を添字にする BIT・セグメント木](../ds/segment-tree-on-values.md)（練習） |
| ABL E. Replace Digits | 1706 | [遅延セグメント木](../ds/lazy-segment-tree.md)（練習） |

### ACL1 {#problem-sets-acl1}

| 問題 | diff | ページ（役割） |
| --- | --- | --- |
| ACL1 B. Sum is Multiple | 1785 | [約数の個数の上界と高度合成数](../math/divisor-count-bound.md)（練習）、[中国剰余定理](../math/crt.md)（例題） |

### CHOKUDAI_S001 {#problem-sets-chokudai_S001}

| 問題 | diff | ページ（役割） |
| --- | --- | --- |
| CHOKUDAI_S001 J. 転倒数 | — | [分割統治](../basics/divide-and-conquer.md)（練習）、[転倒数](../ds/inversion-number.md)（例題） |

### CODE-FESTIVAL-2017-QUALB {#problem-sets-code-festival-2017-qualb}

| 問題 | diff | ページ（役割） |
| --- | --- | --- |
| CODE-FESTIVAL-2017-QUALB C. 3 Steps | 1883 | [二部グラフ判定](../graph/bipartite-graph.md)（力試し） |

### CODE-THANKS-FESTIVAL-2017 {#problem-sets-code-thanks-festival-2017}

| 問題 | diff | ページ（役割） |
| --- | --- | --- |
| CODE-THANKS-FESTIVAL-2017 H. Union Sets | — | [部分永続 Union-Find](../ds/partially-persistent-union-find.md)（例題）、[並列二分探索](../ds/parallel-binary-search.md)（練習） |

### DIVERTA2019 {#problem-sets-diverta2019}

| 問題 | diff | ページ（役割） |
| --- | --- | --- |
| DIVERTA2019 D. DivRem Number | 1098 | [約数列挙と素数判定](../math/divisor-enum.md)（練習） |

### DONUTS-2015 {#problem-sets-donuts-2015}

| 問題 | diff | ページ（役割） |
| --- | --- | --- |
| DONUTS-2015 C. 行列のできるドーナツ屋 | 1661 | [単調スタックとスライド最小値](../ds/monotonic-stack.md)（練習） |

### HHKB2020 {#problem-sets-hhkb2020}

| 問題 | diff | ページ（役割） |
| --- | --- | --- |
| HHKB2020 C. Neq Min | 352 | [計算量の見積もり](../basics/complexity-estimation.md)（練習） |

### KEYENCE2019 {#problem-sets-keyence2019}

| 問題 | diff | ページ（役割） |
| --- | --- | --- |
| KEYENCE2019 E. Connecting Cities | 2623 | [重心分解](../tree/centroid-decomposition.md)（力試し） |

### KEYENCE2020 {#problem-sets-keyence2020}

| 問題 | diff | ページ（役割） |
| --- | --- | --- |
| KEYENCE2020 C. Subarray Sum | 625 | [構築問題の考え方](../thinking/construction.md)（練習） |

### PRACTICE {#problem-sets-practice}

| 問題 | diff | ページ（役割） |
| --- | --- | --- |
| PRACTICE B. Interactive Sorting | — | [インタラクティブ問題](../misc/interactive.md)（練習） |

### SOUNDHOUND2018-SUMMER-QUAL {#problem-sets-soundhound2018-summer-qual}

| 問題 | diff | ページ（役割） |
| --- | --- | --- |
| SOUNDHOUND2018-SUMMER-QUAL D. Saving Snuuk | 1637 | [ダイクストラ法](../graph/dijkstra.md)（力試し） |

### SUMITRUST2019 {#problem-sets-sumitrust2019}

| 問題 | diff | ページ（役割） |
| --- | --- | --- |
| SUMITRUST2019 D. Lucky PIN | 838 | [全探索の設計](../basics/brute-force.md)（練習） |

### YAHOO-PROCON2019-QUAL {#problem-sets-yahoo-procon2019-qual}

| 問題 | diff | ページ（役割） |
| --- | --- | --- |
| YAHOO-PROCON2019-QUAL D. Ears | 1998 | [フェーズを状態に持つ DP](../dp/dp-phase.md)（練習） |
| YAHOO-PROCON2019-QUAL E. Odd Subrectangles | 2585 | [掃き出し法](../math/gaussian-elimination.md)（力試し） |

<!-- textlint-enable -->
<!-- gen:end problem-sets -->

## 練習用のコンテスト {#practice-contests}

決まった時刻に始まり、制限時間の中で解く形の練習には、次のコンテストがある。AtCoder Problems のデータでは、どれもレートが変わらない（Rated の範囲が付いていない）。

- **AtCoder Daily Training（ADT）**：過去の ABC の問題を組み直して、平日に 60 分で出すコンテストである（ごく一部に CODE QUEEN の問題が混じる）。2023-10-17 から開かれ、2026 年は主に平日に 1 日 2 回開かれている。EASY（5 問）と ALL（9 問）の 2 つのコースがあり、2026-02-05 までは MEDIUM と HARD（各 5 問）もあった。
- **AtCoder Weekday Contest（AWC）**：2026-02-09 から平日に毎日開かれている Beta のコンテストである。ほとんどの回が 5 問で、制限時間は awc0006 から 60 分（awc0001〜awc0005 は 90 分）。awc0100 と awc0150 は 15 問・150 分の回だった。問題は AWC のために用意されたもので（AtCoder Problems のデータでは、過去の問題を使い回していない）、difficulty は付かない。
- **アルゴリズム実技検定（PAST）の過去問**：AtCoder Problems のデータに 24 回分（各 15 問）が載っている。1 回分を通しで解くと、典型の当てはめの速さを確かめられる。
- **過去の ABC のバーチャル参加**：好きな時刻に本番の形で解くなら、AtCoder Problems のバーチャルコンテスト（[AtCoder 以外の道具](#tools)）を使い、過去の ABC を時間を計って解く。

ADT の各位置の difficulty の中央値（2023-10〜2026-10 の全回、AtCoder Problems のデータから計算）は次のとおりである。400 未満の値は、AtCoder Problems の表示と同じく縮めた値である（[400 未満は縮めた値](../start/atcoder-system.md#difficulty)）。ALL の A〜E は同じ回の EASY と同じ問題で、ALL にはその後に F〜I が足される。

| コース | A〜E | F | G | H | I |
| --- | --- | ---: | ---: | ---: | ---: |
| EASY | 12・13・57・60・354 | — | — | — | — |
| ALL | 12・13・57・60・354 | 357 | 844 | 1295 | 1819 |

中央値で見ると、ALL の H は水、I は青の帯に当たる。レート 1000 前後から黄を目指すなら、ALL を選び、H・I を解き切ることを目標にするとよい。問題は過去の ABC から選ばれるので、解いたことのある問題も混じる。そのときは、解法を思い出す速さと、実装の速さの練習に使う。

ARC にも Rated の範囲の違う区分（ARC--・ARC・ARC++）があり、レートの低い人も出られる回がある。区分の詳しい話は [AtCoder の仕組み](../start/atcoder-system.md)に任せる。

## AtCoder 以外の道具 {#tools}

問題を選ぶ・記録する・時間を計るための、AtCoder の外の道具をまとめる。どれも非公式のサービスである。

- **AtCoder Problems**：AtCoder の問題を一覧にし、解いた問題を表で示すサイトである。difficulty は「その問題を 50% の確率で解けるレート」で、「X 色の問題は X 色の人の半分が解ける問題」という意味であり、「X 色の人なら解ける問題」ではない。
    - **おすすめ（Recommendation）**：自分のレートから、解ける確率が 80%（Easy）・50%（Moderate）・20%（Difficult）の問題を選んで示す。解いた問題を除くこともできる。
    - **バーチャルコンテスト**：問題と制限時間を選んで、仮想のコンテストを作る。difficulty の範囲を指定して問題をランダムに選ぶ機能（Bacha Gacha）と、参加者が解いた問題を除く設定がある。過去の ABC を 1 回分選べば、本番と同じ形で練習できる。
- **NoviSteps**：AtCoder の過去問に、易しい方から 11Q〜1Q・1D〜6D の 17 段階のグレードを付けたサイトである。グレードは利用者の投票でそろえていく仕組みで、解答の状況（AC・解説 AC・挑戦中など）を記録できる。トピックごとの問題集もある。
- **AtCoder Clans**：AtCoder に関するツール・ライブラリ・記事・書籍などのリンクを、目的と形式ごとに分けて並べたサイトである。ほかの道具を探すときの入口に使う。

解いた問題と理解したページの記録の付け方は、[精進の仕方](../guide/practice-method.md)に任せる。

## ライブラリの確かめ用の問題集 {#verify-sets}

自作のライブラリや ACL の使い方が正しいかは、入力の形が決まった問題に提出して確かめる。確かめ方の手順とページごとの対応は[自作ライブラリの設計と動作確認](../guide/library-design.md)に任せ、ここでは問題集だけを挙げる。

- **ACL Practice（practice2）**：ACL の主な機能を 1 問ずつ（遅延セグメント木は 2 問）、計 12 問が並ぶ。Union-Find・BIT・floor sum・最大流・最小費用流・畳み込み・SCC・2-SAT・Suffix Array・セグメント木・遅延セグメント木を扱う。各問題がどのページの例題かは [ACL Practice の表](#problem-sets-practice2)にある。自作したデータ構造を、ACL と同じ問題で確かめるのにも使える。
- **Library Checker**（[judge.yosupo.jp](https://judge.yosupo.jp/)）：データ構造・アルゴリズムごとに、確かめ用の問題を集めたジャッジである。問題の一覧には、14 の分野（データ構造・グラフ・木・畳み込み・数論・多項式・文字列・幾何など）に 235 問がある。
- **AAL Contest 001: Let's use segtree!（aalc001）**：セグメント木の 24 問。題名から、ふつうのセグメント木・遅延セグメント木・セグメント木上の二分探索・転倒数などを順に使う構成と読める。[セグメント木](../ds/segment-tree.md)と[遅延セグメント木](../ds/lazy-segment-tree.md)を自作した後の確かめに向く。
- **AtCoder Typical Contest 001・002**：DFS・Union-Find・FFT・BFS・繰り返し二乗法など、基本のアルゴリズムを入出力の素直な形で問う。ただし atc002 C（最適二分探索木）は、満点を取るには $O(N \log N)$ の解法（Hu-Tucker など）が要り、基本の確かめの範囲を超える。
- **ACL Beginner Contest（abl）**：ACL を使うことを想定した本番の ABC（2020-09、6 問）。こちらは本番として開かれたので difficulty が付く。

## 参考 {#references}

- [E869120「競プロ典型 90 問」の告知記事（Qiita）](https://qiita.com/e869120/items/1b2a5f0f07fd927e44e9)：★と difficulty の対応、出題の期間、勧める進め方
- [E869120「kyopro_educational_90」（GitHub）](https://github.com/E869120/kyopro_educational_90)：典型90問の解説の置き場
- [E869120「kyopro-tessoku」（GitHub）](https://github.com/E869120/kyopro-tessoku)：鉄則本の章立てと、章ごとの解答コード
- [drken「動的計画法超入門！ Educational DP Contest の A〜E 問題の解説と類題集」（Qiita）](https://qiita.com/drken/items/dc53c683d6de8aeacf5a)：EDPC の位置づけ（DP を初めて学ぶ人向けの問題）
- [AtCoder Problems の FAQ（GitHub）](https://github.com/kenkoooo/AtCoderProblems/blob/master/doc/faq_ja.md)：difficulty の意味
- [AtCoder Problems のガイド（GitHub）](https://github.com/kenkoooo/AtCoderProblems/tree/master/guide/src/ja)：おすすめ問題とバーチャルコンテストの機能
- [AtCoder NoviSteps「About」](https://atcoder-novisteps.vercel.app/about)：グレードの段階と投票、記録の機能
- [AtCoder Clans](https://kato-hiro.github.io/AtCoderClans/)：ツールと記事の一覧の構成
- [yosupo06「library-checker-problems」の categories.toml（GitHub）](https://github.com/yosupo06/library-checker-problems/blob/master/categories.toml)：Library Checker の分野と問題数
