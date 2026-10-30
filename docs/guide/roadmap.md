---
id: roadmap
title: 色別ロードマップ
aliases: [学習順序, 何から学ぶか, 水色・青・黄色のロードマップ, 推奨ルート, 位置ごとの頻出手法]
type: guide
field: guide
chapter: 学び方と練習
order: 60
level: null
kind: [案内]
prerequisites: []
related: [knowledge-map, atcoder-system#difficulty-by-position, contest-strategy, practice-method, problem-sets#recent-abc, reformulation, study-list]
summary: 目標の色ごとに、到達の目安、読むページの順、最近の ABC の位置ごとの頻出手法、解いた数の進捗を見られる。ページの列はレベル・前提・出題頻度から生成する。
complexity: null
signs: []
acl: []
sections:
  - {title: 今の位置と目標, anchor: goal}
  - {title: 色ごとの到達の目安, anchor: targets}
  - {title: 黄を目指す段の主な条件, anchor: yellow}
  - {title: 位置ごとの頻出手法（最近30回）, anchor: recent-positions}
  - {title: 色ごとのページの列, anchor: reading-order}
  - {title: 色ごとの練習の方法, anchor: practice}
  - {title: 解いた数・理解した数, anchor: progress}
  - {title: シラバスではないこと, anchor: not-a-syllabus}
stage: reviewed
updated: 2026-10-29
---

!!! abstract "要点"
    - **何のページか**：目標の色ごとに、到達の目安、読むページの順、最近の ABC の位置ごとの頻出手法、解いた数の進捗を見られる。ページの列はレベル・前提・出題頻度から生成する。
    - **使い方**：今のレートから次の色を 1 つ決め、その色の列を「必修」の行から読む。最近の ABC の E・F・G で何が使われたかは、位置ごとの表で確かめる。
    - **前提**：なし

<!-- textlint-disable -->
別名：学習順序・何から学ぶか・水色・青・黄色のロードマップ・推奨ルート・位置ごとの頻出手法
<!-- textlint-enable -->

色別ロードマップは、目標の色に向けて次に何を読むかを決めるための案内である。ページの列と位置ごとの頻出手法の表は、各ページのレベル・前提・出題頻度と、最近 30 回の ABC の分類から機械的に作る。到達の目安と練習の方法は、AtCoder Problems のデータと[色変記事](../guide/glossary.md#color-change-article)をもとに手で書いた。

## 今の位置と目標 {#goal}

この教材のレベルは、その手法がまとまって使われ始める問題の [difficulty](../guide/glossary.md#difficulty) の帯で決めている。基礎は 1199 まで、水は 1200〜1599、青は 1600〜1999、黄は 2000〜2399、発展は 2400 からで、発展は概要だけを置く。

ABC の位置とレベルは、おおよそ次のように対応する（abc400〜abc480 の 81 回の difficulty による）。

- D は 93% が基礎である。
- E は水 59%・基礎 31%・青以上 10% である。
- F は青 49%・水 26%・黄 19%・発展 6% である。
- G は 38% が黄、49% が発展である。

つまり、水のページは E と易しい F、青のページは F と難しい E、黄のページは難しい F と易しい G で使う知識にあたる。位置ごとの difficulty の分布は[AtCoder の仕組み](../start/atcoder-system.md#difficulty-by-position)に図で、[コンテストの戦い方](contest-strategy.md#difficulty-by-position)に数で示した。

今のレートから、次の目標と読む列を決める。

| 今のレート | 次の目標 | 読む列 | 練習の中心 |
| --- | --- | --- | --- |
| 1199 まで | 水（1200） | 基礎の残り → 水 | D を速く、E を解く |
| 1200〜1599 | 青（1600） | 水の残り → 青 | E を落とさず、F を解く |
| 1600〜1999 | 黄（2000） | 青までの復習 → 黄 | F を速く、易しい G を解く |

色が上がるのは、目標の色の[パフォーマンス](../guide/glossary.md#performance)を何度も続けて出したときである（[レーティング](../guide/glossary.md#rating)は過去のパフォーマンスから決まる）。1 回の上振れでは届かないので、目標は「その色のパフォーマンスを安定して出す」ことに置く。

## 色ごとの到達の目安 {#targets}

目標の色のパフォーマンスを出すには、どの位置までを何分で解けばよいかを、AtCoder Problems のモデルで見積もった。表は abc400〜abc480 の 81 回について、レート P の人が A から順に解いたとき、各位置まで解き終える時刻と、E・F を解く確率の中央値である。

| P | A〜D | A〜E | E を解く確率 | F を解く確率 |
| --- | --- | --- | --- | --- |
| 1200 | 42 分 | 72 分 | 40% | 8% |
| 1600 | 30 分 | 56 分 | 80% | 34% |
| 2000 | 22 分 | 43 分 | 96% | 76% |

解く確率は difficulty のロジスティック曲線から、時刻は問題ごとの予測解答時間の和から求めた。予測解答時間は解けた人だけから求めた値なので、解く確率の低い位置では「もし解けたなら」の目安になる。

解く確率の列は「難しさが中央値の問題を解く確率」で、そのまま「何回に何回解けるか」ではない。回ごとの見込みは 81 回の確率の平均で言う方がよく、下の「何回に何回」は平均から出した。

- **水（1200）**：A〜D を約 40 分で解き、E は 5 回に 2 回解ける。D を落とさないことが土台で、E は解ければ上振れになる。
- **青（1600）**：A〜E を約 55 分で解き、E を 8 割の回で落とさない。F は 3 回に 1 回である。
- **黄（2000）**：A〜E を約 45 分、A〜F を約 70 分で解き、F は 3 回に 2 回ほど解ける（3 回に 1 回は落とす）。G を解くのは 5 回に 1 回ほどである。

A〜F まで含めた時刻の表、完答数とパフォーマンスの関係、コンテスト中の判断は[コンテストの戦い方](contest-strategy.md#time-targets)にまとめた。

## 黄を目指す段の主な条件 {#yellow}

黄のパフォーマンスの主な条件は、黄のページの知識よりも、青までの知識を確実に速く使えることである。abc400〜abc480 の F は 75% が difficulty 2000 未満で、[到達の目安](#targets)のとおり G を解ける回は多くない。黄のページの知識が効くのは、難しい F と易しい G である。

色変記事にも、同じ趣旨の声が複数ある。

- 青から黄までに新しく覚えた知識を本番で使った場面は少なく、必要な知識の多くは水色の時点で持っていた。効いたのは、青・黄 diff の問題を解いて身についた典型の力と考察の力、問題文を速く読む力やデバッグだった（nouka28 氏）。
- ローリングハッシュ・形式的冪級数・HL 分解を学ばないまま黄色に届いた。最後の決め手は、青 diff の正答率が上がったことだった（ks2m 氏）。
- 7 問体制の ABC では、6 完を安定させたうえで 550 点程度までの G を解けることが目安になる（bluebery1001 氏）。

この段では、次の順に時間を配るとよい。

1. 青までの列の「必修」のページを、例題を解説なしで解き直せるまで復習する。解き直しの方法は[精進の仕方](practice-method.md#upsolve)にある。
2. 黄の列は「必修」から読み、難しい F と易しい G の問題で使う。発展のページは、G の上半分を狙うときの概要として使う。
3. A〜E を速く確実に解く訓練をする。F を解けなかった回でも E までを速く解けば、大きくは崩れない。訓練の方法は[精進の仕方](practice-method.md#speed)にある。

## 位置ごとの頻出手法（最近30回） {#recent-positions}

abc451〜abc480 の D〜G の 120 問について、第三者の解説で使われた手法を確かめ、この教材のページに対応させた。下の表は E・F・G ごとに、使ったページを種類で分け、その種類のページを使った問題の数の多い順に並べたものである。1 問が複数の種類に入るので、問題数の合計は 30 を超える。

表から読み取れる傾向は次のとおりである。

- **E**：累積和・いもす法と、一部を固定して数える・寄与・余事象などの考察が多い。二項係数の前計算と組む数え上げも目立つ。
- **F**：セグメント木・BIT・遅延セグメント木などのデータ構造が最も多く（30 問のうち 11 問）、単独のページでは言い換えの典型が最も多い（4 問）。データ構造に載せる前の言い換えは[言い換えてからデータ構造に載せる](../thinking/reformulation.md#then-data-structure)の節にある。
- **G**：DP の発展（Monge・Alien DP・Slope Trick・挿入 DP）、クエリの先読みと Mo's algorithm、畳み込みと形式的冪級数、フロー、幾何など、専用の手法が散らばる。

30 回は少ないので、表に 1 回しか出ない手法や表にない手法も、今後は出うる。表は「どの種類の知識が多く使われたか」を見るためのもので、出題の予想ではない。問題ごとに使う手法のページを引くときは、[問題集と練習用コンテストの案内](problem-sets.md#recent-abc)の「最近の ABC → ページ」の表を使う。

<!-- gen:begin recent-positions -->
<!-- textlint-disable -->

### E 問題（水の帯） {#recent-positions-e}

abc451〜abc480 の E の 30 問で使われた手法を、ページの種類（kind の1つ目）で分けて多い順に並べる。かっこの数は、その位置でそのページを使った問題の数（1 のときは書かない）。

| 種類 | ページ | 問題 | 問題数 |
| --- | --- | --- | --- |
| 考察 | [一部を固定して数える](../thinking/fix-variable.md)（3）、[言い換えの典型](../thinking/reformulation.md)（2）、[主客転倒・寄与](../thinking/contribution.md)（2）、[偶奇に着目する](../thinking/parity.md)（2）、[余事象](../thinking/complement.md)、[構築問題の考え方](../thinking/construction.md)、[対称性・鳩の巣原理・場合分け](../thinking/symmetry-pigeonhole-casework.md)、[Σ の変形](../math/sigma-manipulation.md) | ABC453&nbsp;E・ABC454&nbsp;E・ABC455&nbsp;E・ABC458&nbsp;E・ABC461&nbsp;E・ABC462&nbsp;E・ABC466&nbsp;E・ABC467&nbsp;E・ABC468&nbsp;E・ABC471&nbsp;E・ABC475&nbsp;E | 11 |
| 累積和・差分 | [累積和](../basics/prefix-sum.md)（5）、[いもす法](../basics/imos.md)（3）、[累積和と連想配列で区間を数える](../basics/prefix-sum-counting.md)（2） | ABC452&nbsp;E・ABC453&nbsp;E・ABC455&nbsp;E・ABC464&nbsp;E・ABC466&nbsp;E・ABC468&nbsp;E・ABC469&nbsp;E・ABC473&nbsp;E・ABC474&nbsp;E・ABC477&nbsp;E | 10 |
| データ構造 | [セグメント木](../ds/segment-tree.md)（2）、[set・multiset・map の応用](../ds/ordered-set.md)、[Union-Find](../ds/union-find.md) | ABC451&nbsp;E・ABC461&nbsp;E・ABC475&nbsp;E・ABC476&nbsp;E | 4 |
| 数え上げ | [二項係数の前計算](../comb/binomial-precompute.md)（4）、[数え上げの考え方](../comb/counting-mindset.md) | ABC453&nbsp;E・ABC458&nbsp;E・ABC459&nbsp;E・ABC471&nbsp;E | 4 |
| 二分探索 | [二分探索](../basics/binary-search.md)（2）、[平均・中央値の最大化](../basics/fractional-binary-search.md) | ABC457&nbsp;E・ABC469&nbsp;E・ABC480&nbsp;E | 3 |
| ソート・座標圧縮 | [ソートで考える](../basics/sorting-techniques.md)（2）、[イベントソートと平面走査の基本](../basics/event-sort.md) | ABC457&nbsp;E・ABC467&nbsp;E・ABC474&nbsp;E | 3 |
| DP | [メモ化再帰](../dp/memoized-recursion.md)、[フェーズを状態に持つ DP](../dp/dp-phase.md)、[桁 DP](../dp/digit-dp.md) | ABC465&nbsp;E・ABC466&nbsp;E・ABC470&nbsp;E | 3 |
| グラフ探索 | [閉路の検出と復元](../graph/cycle-detection.md)、[二部グラフ判定](../graph/bipartite-graph.md)、[トポロジカルソート](../graph/topological-sort.md)、[強連結成分分解（SCC）](../graph/scc.md) | ABC456&nbsp;E・ABC472&nbsp;E・ABC478&nbsp;E | 3 |
| 最短路 | [ダイクストラ法](../graph/dijkstra.md)（2）、[状態を頂点にする](../graph/extended-dijkstra.md)（2） | ABC456&nbsp;E・ABC463&nbsp;E・ABC477&nbsp;E | 3 |
| 木 | [根付き木と走査順](../tree/tree-traversal.md)（2）、[木の上の距離](../tree/tree-distance.md)、[葉から考える](../tree/leaf-first.md)、[辺で切って数える](../tree/tree-edge-contribution.md)、[木の構築・復元](../tree/tree-construction.md) | ABC451&nbsp;E・ABC459&nbsp;E・ABC479&nbsp;E | 3 |
| 全探索 | [全探索の設計](../basics/brute-force.md)（2） | ABC474&nbsp;E・ABC480&nbsp;E | 2 |
| 整数論 | [整数の割り算と余り](../math/integer-division.md)、[逆元と mod での割り算](../math/mod-inverse.md)、[桁と mod](../math/digit-and-mod.md)、[GCD・LCM とユークリッドの互除法](../math/gcd-lcm.md) | ABC460&nbsp;E・ABC468&nbsp;E | 2 |
| 計算量 | [調和級数と倍数の列挙](../math/harmonic-sum.md) | ABC452&nbsp;E | 1 |
| 貪欲 | [貪欲法の考え方と正当性](../basics/greedy-basics.md) | ABC473&nbsp;E | 1 |
| ダブリング・分割統治 | [周期性の検出](../basics/periodicity.md) | ABC452&nbsp;E | 1 |
| 連結性・全域木 | [最小全域木](../graph/minimum-spanning-tree.md) | ABC451&nbsp;E | 1 |
| 確率・期待値 | [最適戦略の期待値](../comb/optimal-strategy-expectation.md) | ABC470&nbsp;E | 1 |

### F 問題（青の帯） {#recent-positions-f}

abc451〜abc480 の F の 30 問で使われた手法を、ページの種類（kind の1つ目）で分けて多い順に並べる。かっこの数は、その位置でそのページを使った問題の数（1 のときは書かない）。

| 種類 | ページ | 問題 | 問題数 |
| --- | --- | --- | --- |
| データ構造 | [転倒数](../ds/inversion-number.md)（2）、[遅延セグメント木](../ds/lazy-segment-tree.md)（2）、[セグメント木に何を載せるか](../ds/segment-tree-monoids.md)（2）、[set・multiset・map の応用](../ds/ordered-set.md)、[重み付き Union-Find](../ds/weighted-union-find.md)、[BIT（Fenwick Tree）](../ds/fenwick-tree.md)、[セグメント木](../ds/segment-tree.md)、[セグメント木上の二分探索](../ds/segment-tree-binary-search.md)、[遅延セグメント木の載せ方の型](../ds/lazy-segment-tree-patterns.md) | ABC451&nbsp;F・ABC452&nbsp;F・ABC455&nbsp;F・ABC456&nbsp;F・ABC460&nbsp;F・ABC466&nbsp;F・ABC467&nbsp;F・ABC473&nbsp;F・ABC477&nbsp;F・ABC478&nbsp;F・ABC479&nbsp;F | 11 |
| 考察 | [言い換えの典型](../thinking/reformulation.md)（4）、[対称性・鳩の巣原理・場合分け](../thinking/symmetry-pigeonhole-casework.md)（2）、[主客転倒・寄与](../thinking/contribution.md)、[後ろから・逆順に考える](../thinking/reverse-thinking.md)、[構築問題の考え方](../thinking/construction.md)、[Σ の変形](../math/sigma-manipulation.md) | ABC453&nbsp;F・ABC454&nbsp;F・ABC455&nbsp;F・ABC457&nbsp;F・ABC459&nbsp;F・ABC463&nbsp;F・ABC466&nbsp;F・ABC479&nbsp;F・ABC480&nbsp;F | 9 |
| DP | [DP の状態の設計](../dp/dp-state-design.md)（2）、[ナップサック DP](../dp/knapsack-01.md)、[グリッド上の DP](../dp/dp-grid.md)、[最長増加部分列](../dp/lis.md)、[bitDP](../dp/bit-dp.md)、[照合オートマトン上の DP](../string/string-automaton-dp.md) | ABC457&nbsp;F・ABC458&nbsp;F・ABC461&nbsp;F・ABC462&nbsp;F・ABC468&nbsp;F・ABC476&nbsp;F・ABC480&nbsp;F | 7 |
| 累積和・差分 | [累積和](../basics/prefix-sum.md)（2）、[2 次元累積和](../basics/prefix-sum-2d.md)（2）、[差分列への言い換え](../basics/difference-sequence.md)（2）、[いもす法](../basics/imos.md) | ABC454&nbsp;F・ABC459&nbsp;F・ABC465&nbsp;F・ABC472&nbsp;F・ABC473&nbsp;F・ABC475&nbsp;F | 6 |
| 数え上げ | [二項係数の前計算](../comb/binomial-precompute.md)、[数え上げの考え方](../comb/counting-mindset.md)、[多項係数](../comb/multinomial-coefficient.md)、[包除原理](../comb/inclusion-exclusion.md)、[約数・倍数のゼータ変換とメビウス変換](../comb/zeta-mobius-divisor.md)、[置換の偶奇](../comb/permutation-parity.md) | ABC457&nbsp;F・ABC463&nbsp;F・ABC470&nbsp;F・ABC474&nbsp;F・ABC475&nbsp;F | 5 |
| 貪欲 | [貪欲法の考え方と正当性](../basics/greedy-basics.md)（3）、[交換論法と比較関数の設計](../basics/exchange-argument.md)（2） | ABC454&nbsp;F・ABC467&nbsp;F・ABC468&nbsp;F・ABC471&nbsp;F | 4 |
| 木 | [木の直径と最遠点](../tree/tree-diameter.md)、[木の構築・復元](../tree/tree-construction.md)、[木の重心](../tree/tree-centroid.md)、[最小共通祖先（LCA）](../tree/lca.md) | ABC453&nbsp;F・ABC460&nbsp;F・ABC478&nbsp;F | 3 |
| 尺取り・スライド窓 | [尺取り法](../basics/two-pointers.md)（2） | ABC452&nbsp;F・ABC464&nbsp;F | 2 |
| グラフ探索 | [連結成分](../graph/connected-components.md)、[二部グラフ判定](../graph/bipartite-graph.md) | ABC451&nbsp;F・ABC470&nbsp;F | 2 |
| 線形代数・行列 | [行列累乗](../math/matrix-power.md)（2） | ABC456&nbsp;F・ABC458&nbsp;F | 2 |
| 確率・期待値 | [確率の基本](../comb/probability-basics.md)、[期待値の線形性と指示確率変数](../comb/linearity-of-expectation.md)、[対称性で確率を求める](../comb/probability-symmetry.md) | ABC463&nbsp;F・ABC464&nbsp;F | 2 |
| 幾何 | [ベクトルと外積](../geometry/geometry-vectors.md)、[マンハッタン距離と 45 度回転](../geometry/manhattan-chebyshev.md) | ABC472&nbsp;F・ABC476&nbsp;F | 2 |
| 計算量 | [調和級数と倍数の列挙](../math/harmonic-sum.md) | ABC469&nbsp;F | 1 |
| 全探索 | [半分全列挙](../basics/meet-in-the-middle.md) | ABC464&nbsp;F | 1 |
| ソート・座標圧縮 | [座標圧縮](../basics/coordinate-compression.md) | ABC467&nbsp;F | 1 |
| 連結性・全域木 | [最小全域木](../graph/minimum-spanning-tree.md) | ABC469&nbsp;F | 1 |
| クエリ処理の工夫 | [クエリの先読み](../ds/offline-queries.md)、[平面走査](../ds/sweep-line-2d.md) | ABC477&nbsp;F | 1 |
| 整数論 | [約数列挙と素数判定](../math/divisor-enum.md)、[約数の個数の上界と高度合成数](../math/divisor-count-bound.md) | ABC461&nbsp;F | 1 |
| 文字列 | [Aho-Corasick 法](../string/aho-corasick.md) | ABC458&nbsp;F | 1 |

### G 問題（黄・発展の帯） {#recent-positions-g}

abc451〜abc480 の G の 30 問で使われた手法を、ページの種類（kind の1つ目）で分けて多い順に並べる。かっこの数は、その位置でそのページを使った問題の数（1 のときは書かない）。

| 種類 | ページ | 問題 | 問題数 |
| --- | --- | --- | --- |
| DP | [最長増加部分列](../dp/lis.md)（2）、[挿入 DP・箱根駅伝 DP](../dp/insertion-dp.md)（2）、[桁 DP](../dp/digit-dp.md)、[桁 DP の応用](../dp/digit-dp-advanced.md)、[インライン DP](../dp/inline-dp.md)、[Monge 性による DP の高速化](../dp/monge.md)、[Alien DP](../dp/alien-dp.md)、[Slope Trick](../dp/slope-trick.md) | ABC457&nbsp;G・ABC458&nbsp;G・ABC464&nbsp;G・ABC466&nbsp;G・ABC468&nbsp;G・ABC473&nbsp;G・ABC476&nbsp;G・ABC480&nbsp;G | 8 |
| データ構造 | [遅延セグメント木](../ds/lazy-segment-tree.md)（2）、[マージテク](../tree/small-to-large.md)、[単調スタックとスライド最小値](../ds/monotonic-stack.md)、[BIT（Fenwick Tree）](../ds/fenwick-tree.md)、[セグメント木](../ds/segment-tree.md)、[永続データ構造](../ds/persistent-data-structures.md)、[マージソート木](../ds/merge-sort-tree.md) | ABC453&nbsp;G・ABC454&nbsp;G・ABC460&nbsp;G・ABC467&nbsp;G・ABC470&nbsp;G・ABC480&nbsp;G | 6 |
| クエリ処理の工夫 | [クエリの先読み](../ds/offline-queries.md)（3）、[Mo's algorithm](../ds/mo-algorithm.md) | ABC453&nbsp;G・ABC463&nbsp;G・ABC467&nbsp;G・ABC477&nbsp;G | 4 |
| 数え上げ | [包除原理](../comb/inclusion-exclusion.md)（2）、[二項係数の意味と性質](../comb/binomial-coefficient.md)、[二項係数の前計算](../comb/binomial-precompute.md)、[重複組合せ](../comb/stars-and-bars.md)、[数え上げの考え方](../comb/counting-mindset.md) | ABC456&nbsp;G・ABC462&nbsp;G・ABC463&nbsp;G・ABC476&nbsp;G | 4 |
| 考察 | [主客転倒・寄与](../thinking/contribution.md)（2）、[偶奇に着目する](../thinking/parity.md)（2）、[言い換えの典型](../thinking/reformulation.md)、[構築問題の考え方](../thinking/construction.md) | ABC459&nbsp;G・ABC470&nbsp;G・ABC471&nbsp;G・ABC474&nbsp;G | 4 |
| ダブリング・分割統治 | [分割統治](../basics/divide-and-conquer.md)（2）、[再帰的な構造](../basics/recursion-structure.md) | ABC451&nbsp;G・ABC476&nbsp;G・ABC478&nbsp;G | 3 |
| 木 | [オイラーツアー](../tree/euler-tour.md)（2）、[最小共通祖先（LCA）](../tree/lca.md)、[HL 分解](../tree/hld.md) | ABC453&nbsp;G・ABC460&nbsp;G・ABC477&nbsp;G | 3 |
| 畳み込み・多項式 | [畳み込みの使い方](../math/convolution-ntt.md)、[分割統治 FFT・オンライン畳み込み](../math/online-convolution.md)、[形式的冪級数と多項式の演算](../math/fps-basics.md) | ABC462&nbsp;G・ABC471&nbsp;G・ABC473&nbsp;G | 3 |
| 幾何 | [偏角ソート](../geometry/argument-sort.md)、[マンハッタン距離と 45 度回転](../geometry/manhattan-chebyshev.md)、[凸包と凸多角形](../geometry/convex-hull.md)、[発展の幾何](../geometry/advanced-geometry.md) | ABC457&nbsp;G・ABC478&nbsp;G・ABC479&nbsp;G | 3 |
| 尺取り・スライド窓 | [尺取り法](../basics/two-pointers.md)（2） | ABC455&nbsp;G・ABC470&nbsp;G | 2 |
| フロー・マッチング | [最小カット](../graph/min-cut.md)、[燃やす埋める](../graph/project-selection.md)、[二部マッチング](../graph/bipartite-matching.md)、[König の定理](../graph/konig-theorem.md) | ABC461&nbsp;G・ABC472&nbsp;G | 2 |
| 整数論 | [約数の個数の上界と高度合成数](../math/divisor-count-bound.md)、[拡張ユークリッドの互除法と一次合同式](../math/ext-gcd.md) | ABC459&nbsp;G・ABC475&nbsp;G | 2 |
| 線形代数・行列 | [行列累乗](../math/matrix-power.md)、[XOR 基底](../math/xor-basis.md) | ABC451&nbsp;G・ABC469&nbsp;G | 2 |
| 確率・期待値 | [対称性で確率を求める](../comb/probability-symmetry.md)、[確率 DP](../comb/probability-dp.md) | ABC463&nbsp;G・ABC473&nbsp;G | 2 |
| 二分探索 | [答えで二分探索](../basics/binary-search-answer.md) | ABC458&nbsp;G | 1 |
| 累積和・差分 | [累積和](../basics/prefix-sum.md) | ABC479&nbsp;G | 1 |
| 貪欲 | [優先度付きキューを使う貪欲](../basics/greedy-priority-queue.md) | ABC464&nbsp;G | 1 |
| 文字列 | [ランレングス圧縮](../basics/run-length-encoding.md)、[Suffix Array と LCP 配列](../string/suffix-array.md)、[Suffix Automaton と発展の文字列アルゴリズム](../string/suffix-automaton.md) | ABC452&nbsp;G | 1 |
| ハッシュ・乱択 | [集合・多重集合のハッシュ](../string/hashing-for-sets.md) | ABC455&nbsp;G | 1 |
| ビット演算 | [bit 演算の基本と XOR の性質](../basics/bit-operations.md) | ABC476&nbsp;G | 1 |

<!-- textlint-enable -->
<!-- gen:end recent-positions -->

## 色ごとのページの列 {#reading-order}

下の列は、各ページの front matter から次の手順で作る。

1. その色のレベルのページを集める。下のレベルのページにある上の帯の節も、「ページ › 節（基礎のページの節）」のような行として、その色の列に入れる。
2. 同じ色の中の前提の深さで並べる。同じ色に前提を持たないページが先に来て、分野をまたぐ前提も先に並ぶ。
3. 前提の深さが同じなら、分野の並び、頻度、分野の中の順で並べる。

頻度の欄は、最近の ABC（abc451〜abc480 の D〜G の分類）での出題の多さから付けた。

- **必修**：最近の ABC で 2 回以上使われたか、多くのページの前提になっている。
- **準必修**：最近の ABC で 1 回使われたか、古い ABC で繰り返し使われた。
- **余裕があれば**：それ以外である。発展のページの多くがここに入る。

列は番号の順に全部読むためのものではない。まず「必修」の行を前から読み、「準必修」と「余裕があれば」は、例題や本番で出会ったときに読めばよい。節の行は、そのページの下の帯の部分を読んでいれば、節だけを読めば足りる。黄を目指すときは、黄の列と並行して青までの「必修」を復習する（[黄を目指す段の主な条件](#yellow)）。前提のつながりを図で見るときは[知識マップ](knowledge-map.md#focus)を使う。

各行の先頭のチェック欄は、そのページの「理解した」と同じ記録である。節の行は、ページの上の「水の節」のような欄にあたる。ページの上と下の欄で付けても、この列の欄で付けてもよい。次の欄で「理解した行を隠す」を選ぶと、まだ理解していない行だけが残る。

<div class="kp-order-tools"></div>

<!-- gen:begin roadmap-order -->
<!-- textlint-disable -->

### 基礎（difficulty 〜1199） {#reading-order-basic}

| # | ページ | 分野 | 頻度 |
| --- | --- | --- | --- |
| 1 | [計算量の見積もり](../basics/complexity-estimation.md) | 基本テクニック | 必修 |
| 2 | [bit 演算の基本と XOR の性質](../basics/bit-operations.md) | 基本テクニック | 必修 |
| 3 | [ソートで考える](../basics/sorting-techniques.md) | 基本テクニック | 必修 |
| 4 | [累積和](../basics/prefix-sum.md) | 基本テクニック | 必修 |
| 5 | [ランレングス圧縮](../basics/run-length-encoding.md) | 基本テクニック | 準必修 |
| 6 | [周期性の検出](../basics/periodicity.md) | 基本テクニック | 準必修 |
| 7 | [再帰的な構造](../basics/recursion-structure.md) | 基本テクニック | 準必修 |
| 8 | [偶奇に着目する](../thinking/parity.md) | 考察 | 必修 |
| 9 | [後ろから・逆順に考える](../thinking/reverse-thinking.md) | 考察 | 必修 |
| 10 | [構築問題の考え方](../thinking/construction.md) | 考察 | 必修 |
| 11 | [対称性・鳩の巣原理・場合分け](../thinking/symmetry-pigeonhole-casework.md) | 考察 | 必修 |
| 12 | [余事象](../thinking/complement.md) | 考察 | 準必修 |
| 13 | [不変量・単調に変わる量](../thinking/invariant.md) | 考察 | 準必修 |
| 14 | [グラフの表現と用語](../graph/graph-basics.md) | グラフ | 必修 |
| 15 | [STL コンテナの使い分け](../ds/stl-containers.md) | データ構造 | 必修 |
| 16 | [Σ の変形](../math/sigma-manipulation.md) | 整数論・代数 | 必修 |
| 17 | [整数の割り算と余り](../math/integer-division.md) | 整数論・代数 | 必修 |
| 18 | [和・積の法則と順列・組合せ](../comb/counting-basics.md) | 数え上げ・確率・ゲーム | 必修 |
| 19 | [置換の巡回分解](../comb/permutation-cycles.md) | 数え上げ・確率・ゲーム | 準必修 |
| 20 | [ベクトルと外積](../geometry/geometry-vectors.md) | 幾何 | 必修 |
| 21 | [全探索の設計](../basics/brute-force.md) | 基本テクニック | 必修 |
| 22 | [二分探索](../basics/binary-search.md) | 基本テクニック | 必修 |
| 23 | [累積和と連想配列で区間を数える](../basics/prefix-sum-counting.md) | 基本テクニック | 必修 |
| 24 | [いもす法](../basics/imos.md) | 基本テクニック | 必修 |
| 25 | [尺取り法](../basics/two-pointers.md) | 基本テクニック | 必修 |
| 26 | [貪欲法の考え方と正当性](../basics/greedy-basics.md) | 基本テクニック | 必修 |
| 27 | [絶対値の和の最小化と中央値](../basics/median-absolute.md) | 基本テクニック | 余裕があれば |
| 28 | [深さ優先探索（DFS）](../graph/dfs.md) | グラフ | 必修 |
| 29 | [set・multiset・map の応用](../ds/ordered-set.md) | データ構造 | 必修 |
| 30 | [スタック・キュー・deque の使いどころ](../ds/stack-techniques.md) | データ構造 | 必修 |
| 31 | [Union-Find](../ds/union-find.md) | データ構造 | 必修 |
| 32 | [全体への操作を変数で持つ](../ds/global-offset.md) | データ構造 | 準必修 |
| 33 | [配列で作る連結リスト](../ds/linked-list.md) | データ構造 | 準必修 |
| 34 | [mod の計算の基本](../math/mod-arithmetic.md) | 整数論・代数 | 必修 |
| 35 | [GCD・LCM とユークリッドの互除法](../math/gcd-lcm.md) | 整数論・代数 | 必修 |
| 36 | [約数列挙と素数判定](../math/divisor-enum.md) | 整数論・代数 | 準必修 |
| 37 | [整数の平方根・K 乗根と累乗数](../math/integer-root.md) | 整数論・代数 | 準必修 |
| 38 | [N 進法](../math/base-conversion.md) | 整数論・代数 | 準必修 |
| 39 | [二項係数の意味と性質](../comb/binomial-coefficient.md) | 数え上げ・確率・ゲーム | 必修 |
| 40 | [確率の基本](../comb/probability-basics.md) | 数え上げ・確率・ゲーム | 必修 |
| 41 | [文字列の基本操作と辞書順](../string/string-basics.md) | 文字列 | 必修 |
| 42 | [bit 全探索と順列全探索](../basics/bit-full-search.md) | 基本テクニック | 必修 |
| 43 | [答えで二分探索](../basics/binary-search-answer.md) | 基本テクニック | 必修 |
| 44 | [座標圧縮](../basics/coordinate-compression.md) | 基本テクニック | 準必修 |
| 45 | [辞書順最小を前から決める貪欲](../basics/lexicographic-greedy.md) | 基本テクニック | 準必修 |
| 46 | [区間スケジューリング・区間の串刺し](../basics/interval-scheduling.md) | 基本テクニック | 余裕があれば |
| 47 | [一部を固定して数える](../thinking/fix-variable.md) | 考察 | 必修 |
| 48 | [DP の基本](../dp/dp-basics.md) | 動的計画法 | 必修 |
| 49 | [幅優先探索（BFS）と無重み最短路](../graph/bfs.md) | グラフ | 必修 |
| 50 | [連結成分](../graph/connected-components.md) | グラフ | 準必修 |
| 51 | [閉路の検出と復元](../graph/cycle-detection.md) | グラフ | 準必修 |
| 52 | [木の基本性質と表現](../tree/tree-basics.md) | 木 | 必修 |
| 53 | [繰り返し二乗法](../math/mod-pow.md) | 整数論・代数 | 必修 |
| 54 | [素因数分解とルジャンドルの公式](../math/prime-factorization.md) | 整数論・代数 | 必修 |
| 55 | [エラトステネスの篩](../math/sieve-eratosthenes.md) | 整数論・代数 | 準必修 |
| 56 | [整数の証明の型](../math/proof-patterns.md) | 整数論・代数 | 余裕があれば |
| 57 | [重複組合せ](../comb/stars-and-bars.md) | 数え上げ・確率・ゲーム | 準必修 |
| 58 | [幾何分布とコンプリートガチャ](../comb/coupon-collector.md) | 数え上げ・確率・ゲーム | 余裕があれば |
| 59 | [部分列の判定と次の出現位置の表](../string/subsequence-matching.md) | 文字列 | 準必修 |
| 60 | [インタラクティブ問題](../misc/interactive.md) | その他の技法 | 準必修 |
| 61 | [ナップサック DP](../dp/knapsack-01.md) | 動的計画法 | 必修 |
| 62 | [メモ化再帰](../dp/memoized-recursion.md) | 動的計画法 | 準必修 |
| 63 | [部分和 DP](../dp/subset-sum.md) | 動的計画法 | 準必修 |
| 64 | [グリッドグラフ](../graph/grid-graph.md) | グラフ | 必修 |
| 65 | [二部グラフ判定](../graph/bipartite-graph.md) | グラフ | 必修 |
| 66 | [ダイクストラ法](../graph/dijkstra.md) | グラフ | 必修 |
| 67 | [小さいグラフの全探索](../graph/small-graph-brute-force.md) | グラフ | 準必修 |
| 68 | [トポロジカルソート](../graph/topological-sort.md) | グラフ | 準必修 |
| 69 | [根付き木と走査順](../tree/tree-traversal.md) | 木 | 必修 |
| 70 | [完全二分木](../tree/complete-binary-tree.md) | 木 | 準必修 |
| 71 | [逆元と mod での割り算](../math/mod-inverse.md) | 整数論・代数 | 必修 |
| 72 | [最小素因数の篩と線形篩](../math/spf-sieve.md) | 整数論・代数 | 準必修 |
| 73 | [素因数の指数で考える](../math/prime-exponent-vector.md) | 整数論・代数 | 準必修 |
| 74 | [DAG 上の DP](../dp/dp-dag.md) | 動的計画法 | 準必修 |
| 75 | [木の 2 色塗り分けと距離の偶奇](../tree/tree-bipartite.md) | 木 | 準必修 |
| 76 | [木の上の距離](../tree/tree-distance.md) | 木 | 準必修 |
| 77 | [木の上の累積和・いもす法](../tree/tree-imos.md) | 木 | 準必修 |
| 78 | [指定頂点を結ぶ最小の部分木](../tree/steiner-subtree.md) | 木 | 余裕があれば |
| 79 | [modint](../math/modint.md) | 整数論・代数 | 必修 |
| 80 | [等比数列の和を mod で求める](../math/geometric-series-mod.md) | 整数論・代数 | 準必修 |
| 81 | [二項係数の前計算](../comb/binomial-precompute.md) | 数え上げ・確率・ゲーム | 必修 |
| 82 | [格子路の数え上げ](../comb/lattice-paths.md) | 数え上げ・確率・ゲーム | 必修 |

### 水（difficulty 1200〜1599） {#reading-order-cyan}

| # | ページ | 分野 | 頻度 |
| --- | --- | --- | --- |
| 1 | [計算量の見積もり](../basics/complexity-estimation.md#constant-factor) › 定数倍（配列と set・map の差・メモリの連続性・bitset）（基礎のページの節） | 基本テクニック | 必修 |
| 2 | [全探索の設計](../basics/brute-force.md#move-board) › 盤面を動かして全部試す（回転・平行移動）（基礎のページの節） | 基本テクニック | 必修 |
| 3 | [bit 全探索と順列全探索](../basics/bit-full-search.md#half-greedy) › 片側を bit で決めて残りは貪欲（基礎のページの節） | 基本テクニック | 必修 |
| 4 | [再帰による全列挙](../basics/recursive-enumeration.md) | 基本テクニック | 必修 |
| 5 | [答えで二分探索](../basics/binary-search-answer.md#real-number) › 実数の二分探索（反復回数を固定する）（基礎のページの節） | 基本テクニック | 必修 |
| 6 | [イベントソートと平面走査の基本](../basics/event-sort.md) | 基本テクニック | 必修 |
| 7 | [2 次元累積和](../basics/prefix-sum-2d.md) | 基本テクニック | 必修 |
| 8 | [ランレングス圧縮](../basics/run-length-encoding.md#keep-compressed) › ランレングスのまま処理する（基礎のページの節） | 基本テクニック | 準必修 |
| 9 | [半分全列挙](../basics/meet-in-the-middle.md) | 基本テクニック | 準必修 |
| 10 | [平均・中央値の最大化](../basics/fractional-binary-search.md) | 基本テクニック | 準必修 |
| 11 | [三分探索](../basics/ternary-search.md) | 基本テクニック | 準必修 |
| 12 | [周期性の検出](../basics/periodicity.md#periodic-patterns) › 盤面・剰余の周期を割り算で数える（基礎のページの節） | 基本テクニック | 準必修 |
| 13 | [ダブリング](../basics/doubling.md) | 基本テクニック | 準必修 |
| 14 | [言い換えの典型](../thinking/reformulation.md) | 考察 | 必修 |
| 15 | [主客転倒・寄与](../thinking/contribution.md) | 考察 | 必修 |
| 16 | [後ろから・逆順に考える](../thinking/reverse-thinking.md#delete-to-add) › 削除を逆順の追加にする（Union-Find はグラフの章）（基礎のページの節） | 考察 | 必修 |
| 17 | [構築問題の考え方](../thinking/construction.md#abc-patterns) › ABC の構築の型（手順・数列・グラフ）（基礎のページの節） | 考察 | 必修 |
| 18 | [対称性・鳩の巣原理・場合分け](../thinking/symmetry-pigeonhole-casework.md#pigeonhole) › 鳩の巣原理（必ず一致が起きる・探索の打ち切り回数）（基礎のページの節） | 考察 | 必修 |
| 19 | [DP の基本](../dp/dp-basics.md#pull-to-prefix-sum) › 貰う形にすると遷移元が区間になる（累積和でまとめる高速化へ）（基礎のページの節） | 動的計画法 | 必修 |
| 20 | [DP の状態の設計](../dp/dp-state-design.md) | 動的計画法 | 必修 |
| 21 | [ナップサック DP](../dp/knapsack-01.md#choose-by-size) › 計算量で解法を切り替える（重さ・価値・N のどれが小さいか）（基礎のページの節） | 動的計画法 | 必修 |
| 22 | [最長増加部分列](../dp/lis.md) | 動的計画法 | 必修 |
| 23 | [DAG 上の DP](../dp/dp-dag.md#find-dag) › DAG だと気づく・作る（値の順・距離の層・同じ値の頂点をまとめる）（基礎のページの節） | 動的計画法 | 準必修 |
| 24 | [DP の計算順序](../dp/dp-order.md) | 動的計画法 | 準必修 |
| 25 | [DP の復元](../dp/dp-reconstruction.md) | 動的計画法 | 準必修 |
| 26 | [累積和・いもす法による DP の高速化](../dp/dp-prefix-sum.md) | 動的計画法 | 準必修 |
| 27 | [部分和 DP](../dp/subset-sum.md#sort-then-count) › 最大値を固定するためにソートしてから数える（基礎のページの節） | 動的計画法 | 準必修 |
| 28 | [グリッド上の DP](../dp/dp-grid.md) | 動的計画法 | 準必修 |
| 29 | [最長共通部分列と編集距離](../dp/lcs.md) | 動的計画法 | 準必修 |
| 30 | [木 DP](../dp/tree-dp.md) | 動的計画法 | 準必修 |
| 31 | [ダイクストラ法](../graph/dijkstra.md#reverse-graph) › 逆向きのグラフと両端からの最短路（基礎のページの節） | グラフ | 必修 |
| 32 | [ダイクストラ法](../graph/dijkstra.md#potential) › ポテンシャルで負辺を消す（Johnson のアイデア）（基礎のページの節） | グラフ | 必修 |
| 33 | [状態を頂点にする](../graph/extended-dijkstra.md) | グラフ | 必修 |
| 34 | [最小全域木](../graph/minimum-spanning-tree.md) | グラフ | 必修 |
| 35 | [なもりグラフ](../graph/namori-graph.md) | グラフ | 準必修 |
| 36 | [01-BFS](../graph/zero-one-bfs.md) | グラフ | 準必修 |
| 37 | [ワーシャルフロイド法](../graph/warshall-floyd.md) | グラフ | 準必修 |
| 38 | [最短路 DAG](../graph/shortest-path-dag.md) | グラフ | 準必修 |
| 39 | [時刻で変わる辺の最短路](../graph/time-dependent-dijkstra.md) | グラフ | 準必修 |
| 40 | [強連結成分分解（SCC）](../graph/scc.md) | グラフ | 準必修 |
| 41 | [Functional graph（出次数 1 のグラフ）](../graph/functional-graph.md) | グラフ | 準必修 |
| 42 | [Union-Find で連結性を扱う](../graph/union-find-connectivity.md) | グラフ | 準必修 |
| 43 | [葉から考える](../tree/leaf-first.md) | 木 | 準必修 |
| 44 | [木の直径と最遠点](../tree/tree-diameter.md) | 木 | 準必修 |
| 45 | [マージテク](../tree/small-to-large.md) | 木 | 準必修 |
| 46 | [set・multiset・map の応用](../ds/ordered-set.md#rows-and-columns) › 行ごと・列ごとの set（グリッドで次の壁を探し、両方から消す）（基礎のページの節） | データ構造 | 必修 |
| 47 | [set・multiset・map の応用](../ds/ordered-set.md#pareto) › パレート境界を map で持つ（支配される点を消す。ならし O(log N)）（基礎のページの節） | データ構造 | 必修 |
| 48 | [スタック・キュー・deque の使いどころ](../ds/stack-techniques.md#chords) › 円を切り開いて弦の交差判定に帰着する（基礎のページの節） | データ構造 | 必修 |
| 49 | [BIT（Fenwick Tree）](../ds/fenwick-tree.md) | データ構造 | 必修 |
| 50 | [セグメント木](../ds/segment-tree.md) | データ構造 | 必修 |
| 51 | [全体への操作を変数で持つ](../ds/global-offset.md#to-lazy-segment-tree) › 遅延セグメント木とのつながり（全体への操作を区間への操作に広げる）（基礎のページの節） | データ構造 | 準必修 |
| 52 | [優先度付きキュー](../ds/priority-queue.md) | データ構造 | 準必修 |
| 53 | [区間を set で管理する](../ds/interval-set.md) | データ構造 | 準必修 |
| 54 | [単調スタックとスライド最小値](../ds/monotonic-stack.md) | データ構造 | 準必修 |
| 55 | [Union-Find の応用](../ds/union-find-applications.md) | データ構造 | 準必修 |
| 56 | [重み付き Union-Find](../ds/weighted-union-find.md) | データ構造 | 準必修 |
| 57 | [逆元と mod での割り算](../math/mod-inverse.md#ext-gcd) › 拡張ユークリッドによる逆元（法が素数でないとき）（基礎のページの節） | 整数論・代数 | 必修 |
| 58 | [調和級数と倍数の列挙](../math/harmonic-sum.md) | 整数論・代数 | 必修 |
| 59 | [約数の個数の上界と高度合成数](../math/divisor-count-bound.md) | 整数論・代数 | 必修 |
| 60 | [GCD・LCM とユークリッドの互除法](../math/gcd-lcm.md#reduce-fraction) › 分数・傾きを既約にして map のキーにする（基礎のページの節） | 整数論・代数 | 必修 |
| 61 | [等比数列の和を mod で求める](../math/geometric-series-mod.md#halving) › 法が任意のとき：S(2k) = S(k)(1 + r^k) で半分に割る（基礎のページの節） | 整数論・代数 | 準必修 |
| 62 | [フェルマーの小定理と指数の mod](../math/exponent-mod.md) | 整数論・代数 | 準必修 |
| 63 | [桁と mod](../math/digit-and-mod.md) | 整数論・代数 | 準必修 |
| 64 | [素因数の指数で考える](../math/prime-exponent-vector.md#huge-lcm) › 巨大な lcm を指数の最大で持つ（基礎のページの節） | 整数論・代数 | 準必修 |
| 65 | [素因数の指数で考える](../math/prime-exponent-vector.md#single-prime) › 特定の素数（2 など）の指数だけを比べる（基礎のページの節） | 整数論・代数 | 準必修 |
| 66 | [拡張ユークリッドの互除法と一次合同式](../math/ext-gcd.md) | 整数論・代数 | 準必修 |
| 67 | [N 進法](../math/base-conversion.md#negative-base) › 負の基数（余りを 0 以上に直してから割る）（基礎のページの節） | 整数論・代数 | 準必修 |
| 68 | [N 進法](../math/base-conversion.md#base-binary-search) › 基数の二分探索とオーバーフロー（1 桁の場合分け）（基礎のページの節） | 整数論・代数 | 準必修 |
| 69 | [商の列挙](../math/floor-quotient-enum.md) | 整数論・代数 | 準必修 |
| 70 | [区間篩](../math/segmented-sieve.md) | 整数論・代数 | 余裕があれば |
| 71 | [数え上げの考え方](../comb/counting-mindset.md) | 数え上げ・確率・ゲーム | 必修 |
| 72 | [対称性で確率を求める](../comb/probability-symmetry.md) | 数え上げ・確率・ゲーム | 必修 |
| 73 | [重複組合せ](../comb/stars-and-bars.md#applications) › 場合分けしてから配る・素因数ごとに配る（基礎のページの節） | 数え上げ・確率・ゲーム | 準必修 |
| 74 | [多項係数](../comb/multinomial-coefficient.md) | 数え上げ・確率・ゲーム | 準必修 |
| 75 | [確率・期待値を mod 998244353 で答える](../comb/rational-mod.md) | 数え上げ・確率・ゲーム | 準必修 |
| 76 | [期待値の線形性と指示確率変数](../comb/linearity-of-expectation.md) | 数え上げ・確率・ゲーム | 準必修 |
| 77 | [確率 DP](../comb/probability-dp.md) | 数え上げ・確率・ゲーム | 準必修 |
| 78 | [部分列の判定と次の出現位置の表](../string/subsequence-matching.md#lexicographically-smallest) › 辞書順最小の部分列（残りで足りる範囲の最小の文字を選ぶ）（基礎のページの節） | 文字列 | 準必修 |
| 79 | [ローリングハッシュ](../string/rolling-hash.md) | 文字列 | 準必修 |
| 80 | [集合・多重集合のハッシュ](../string/hashing-for-sets.md) | 文字列 | 準必修 |
| 81 | [Z-algorithm](../string/z-algorithm.md) | 文字列 | 準必修 |
| 82 | [回文の扱いと Manacher](../string/palindrome.md) | 文字列 | 準必修 |
| 83 | [Trie](../string/trie.md) | 文字列 | 準必修 |
| 84 | [ベクトルと外積](../geometry/geometry-vectors.md#polygon-area) › 三角形・多角形の面積：座標の公式（面積の 2 倍を整数のまま扱う）（基礎のページの節） | 幾何 | 必修 |
| 85 | [ベクトルと外積](../geometry/geometry-vectors.md#segment-intersection) › 線分の交差判定（端点で接する・同一直線上の場合）と点と直線の距離（基礎のページの節） | 幾何 | 必修 |
| 86 | [マンハッタン距離と 45 度回転](../geometry/manhattan-chebyshev.md) | 幾何 | 必修 |
| 87 | [誤差の扱いと整数での処理](../geometry/geometry-precision.md) | 幾何 | 準必修 |
| 88 | [偏角ソート](../geometry/argument-sort.md) | 幾何 | 準必修 |
| 89 | [回転・平行移動・アフィン変換](../geometry/rotation-transform.md) | 幾何 | 準必修 |
| 90 | [インタラクティブ問題](../misc/interactive.md#explore-graph) › 未知のグラフを探索する（DFS の行きと帰り）（基礎のページの節） | その他の技法 | 準必修 |
| 91 | [bit ごとに独立に考える](../basics/bitwise-independence.md) | 基本テクニック | 準必修 |
| 92 | [優先度付きキューを使う貪欲](../basics/greedy-priority-queue.md) | 基本テクニック | 準必修 |
| 93 | [桁 DP](../dp/digit-dp.md) | 動的計画法 | 必修 |
| 94 | [余り・個数を状態に持つ DP](../dp/dp-mod-state.md) | 動的計画法 | 準必修 |
| 95 | [bitDP](../dp/bit-dp.md) | 動的計画法 | 準必修 |
| 96 | [区間分割 DP](../dp/dp-sequence-partition.md) | 動的計画法 | 余裕があれば |
| 97 | [木の構築・復元](../tree/tree-construction.md) | 木 | 必修 |
| 98 | [辺で切って数える](../tree/tree-edge-contribution.md) | 木 | 準必修 |
| 99 | [転倒数](../ds/inversion-number.md) | データ構造 | 必修 |
| 100 | [遅延セグメント木](../ds/lazy-segment-tree.md) | データ構造 | 必修 |
| 101 | [クエリの先読み](../ds/offline-queries.md) | データ構造 | 必修 |
| 102 | [上位 K 個の和と中央値の管理](../ds/top-k-multiset.md) | データ構造 | 準必修 |
| 103 | [K 番目の値を求めるデータ構造](../ds/kth-element.md) | データ構造 | 準必修 |
| 104 | [セグメント木上の二分探索](../ds/segment-tree-binary-search.md) | データ構造 | 準必修 |
| 105 | [値を添字にする BIT・セグメント木](../ds/segment-tree-on-values.md) | データ構造 | 準必修 |
| 106 | [順序を固定して数える](../comb/counting-fix-order.md) | 数え上げ・確率・ゲーム | 準必修 |
| 107 | [期待値 DP](../comb/expected-value-dp.md) | 数え上げ・確率・ゲーム | 準必修 |
| 108 | [ゲームの基本と勝敗の DP](../comb/game-basics.md) | 数え上げ・確率・ゲーム | 準必修 |
| 109 | [ミニマックス](../comb/minimax.md) | 数え上げ・確率・ゲーム | 準必修 |
| 110 | [Nim と XOR](../comb/nim.md) | 数え上げ・確率・ゲーム | 準必修 |

### 青（difficulty 1600〜1999） {#reading-order-blue}

| # | ページ | 分野 | 頻度 |
| --- | --- | --- | --- |
| 1 | [答えで二分探索](../basics/binary-search-answer.md#dp-check) › 判定を DP で作る（決め打ちごとに初期化し直す）（基礎のページの節） | 基本テクニック | 必修 |
| 2 | [累積和と連想配列で区間を数える](../basics/prefix-sum-counting.md#length-limited) › 長さの制限付き（窓の中だけで数える）（基礎のページの節） | 基本テクニック | 必修 |
| 3 | [2 次元累積和](../basics/prefix-sum-2d.md#higher-dimensions) › 3 次元以上（項の数と符号の決め方）（水のページの節） | 基本テクニック | 必修 |
| 4 | [交換論法と比較関数の設計](../basics/exchange-argument.md) | 基本テクニック | 必修 |
| 5 | [bit ごとに独立に考える](../basics/bitwise-independence.md#split-by-top-bit) › 上位 bit で 2 つに分けて再帰する（水のページの節） | 基本テクニック | 準必修 |
| 6 | [半分全列挙](../basics/meet-in-the-middle.md#grid-diagonal) › グリッドの経路を対角線で分ける（水のページの節） | 基本テクニック | 準必修 |
| 7 | [平均・中央値の最大化](../basics/fractional-binary-search.md#median) › 中央値の言い換え（x 以上を +1、未満を −1）と偶数個のときの不等号（水のページの節） | 基本テクニック | 準必修 |
| 8 | [平均・中央値の最大化](../basics/fractional-binary-search.md#dp-check) › 判定を DP・DAG の最長路・全域木で行う（水のページの節） | 基本テクニック | 準必修 |
| 9 | [平均・中央値の最大化](../basics/fractional-binary-search.md#median-2d) › 領域の中央値（2 次元累積和）（水のページの節） | 基本テクニック | 準必修 |
| 10 | [K 番目の値](../basics/kth-value.md) | 基本テクニック | 準必修 |
| 11 | [三分探索](../basics/ternary-search.md#marginal-greedy) › 増分が単調なら 1 単位ずつ貪欲に配る（水のページの節） | 基本テクニック | 準必修 |
| 12 | [辞書順最小を前から決める貪欲](../basics/lexicographic-greedy.md#heavy-check) › 判定が重い型（基礎のページの節） | 基本テクニック | 準必修 |
| 13 | [絶対値の和の最小化と中央値](../basics/median-absolute.md#with-binary-search) › 距離の和で判定して二分探索する（基礎のページの節） | 基本テクニック | 余裕があれば |
| 14 | [言い換えの典型](../thinking/reformulation.md#then-data-structure) › 言い換えてからデータ構造に載せる（水のページの節） | 考察 | 必修 |
| 15 | [偶奇に着目する](../thinking/parity.md#checkerboard) › 市松模様の偶奇（基礎のページの節） | 考察 | 必修 |
| 16 | [ナップサック DP](../dp/knapsack-01.md#knapsack-bounded) › 個数制限付き（素朴な展開・二進分解・余りごとのスライド最小値）（基礎のページの節） | 動的計画法 | 必修 |
| 17 | [最長増加部分列](../dp/lis.md#contained) › 各要素が LIS に含まれうるか（前後から 2 回求める）（水のページの節） | 動的計画法 | 必修 |
| 18 | [最長増加部分列](../dp/lis.md#nesting) › 2 次元の入れ子（一方は昇順・もう一方は降順に並べる）（水のページの節） | 動的計画法 | 必修 |
| 19 | [最長増加部分列](../dp/lis.md#variants) › 1 か所だけ変更できる LIS・木の上の LIS（水のページの節） | 動的計画法 | 必修 |
| 20 | [最長増加部分列](../dp/lis.md#dilworth) › Dilworth の定理（増加列への最小分割数＝最長減少部分列の長さ）（水のページの節） | 動的計画法 | 必修 |
| 21 | [余り・個数を状態に持つ DP](../dp/dp-mod-state.md#game-by-remainder) › 後ろから余りごとの勝敗を決めるゲーム（水のページの節） | 動的計画法 | 準必修 |
| 22 | [フェーズを状態に持つ DP](../dp/dp-phase.md) | 動的計画法 | 準必修 |
| 23 | [累積和・いもす法による DP の高速化](../dp/dp-prefix-sum.md#by-remainder) › 余りごとの累積（水のページの節） | 動的計画法 | 準必修 |
| 24 | [累積和・いもす法による DP の高速化](../dp/dp-prefix-sum.md#two-dimensional) › 2 次元の累積（水のページの節） | 動的計画法 | 準必修 |
| 25 | [部分和 DP](../dp/subset-sum.md#over-all-subsets) › 全部分集合についての和（含む部分集合の数を重みにする）（基礎のページの節） | 動的計画法 | 準必修 |
| 26 | [DP の状態の削減](../dp/dp-dimension-reduction.md) | 動的計画法 | 準必修 |
| 27 | [最長共通部分列と編集距離](../dp/lcs.md#count-pairs) › 共通部分列の組の数（包除で重複を引く・2 次元の累積和）（水のページの節） | 動的計画法 | 準必修 |
| 28 | [区間 DP](../dp/interval-dp.md) | 動的計画法 | 準必修 |
| 29 | [bitDP](../dp/bit-dp.md#with-shortest-paths) › ほかの探索と組み合わせる（BFS・ワーシャルフロイド法で距離を前計算してから）（水のページの節） | 動的計画法 | 準必修 |
| 30 | [部分集合を列挙する DP](../dp/subset-enumeration-dp.md) | 動的計画法 | 準必修 |
| 31 | [木 DP](../dp/tree-dp.md#greedy-children) › 子ごとの「得」を大きい順に取る（水のページの節） | 動的計画法 | 準必修 |
| 32 | [全方位木 DP](../dp/rerooting.md) | 動的計画法 | 準必修 |
| 33 | [セグメント木・スライド最小値による DP の高速化](../dp/dp-segment-tree.md) | 動的計画法 | 準必修 |
| 34 | [戻す DP](../dp/knapsack-undo.md) | 動的計画法 | 余裕があれば |
| 35 | [区間分割 DP](../dp/dp-sequence-partition.md#block-index) › 区間の番号に依存する条件：番号を状態に足す（水のページの節） | 動的計画法 | 余裕があれば |
| 36 | [グリッドグラフ](../graph/grid-graph.md#obstacle-dual) › 障害物どうしの 8 近傍の連結で通れるかを判定する（基礎のページの節） | グラフ | 必修 |
| 37 | [状態を頂点にする](../graph/extended-dijkstra.md#resource-state) › 資源を状態に持ち、上限で打ち切る（水のページの節） | グラフ | 必修 |
| 38 | [状態を頂点にする](../graph/extended-dijkstra.md#visited-set) › 訪問した集合を持つ（bitDP へのつなぎ）（水のページの節） | グラフ | 必修 |
| 39 | [状態を頂点にする](../graph/extended-dijkstra.md#two-ends) › 両端から伸ばす（回文の最短路）（水のページの節） | グラフ | 必修 |
| 40 | [最小全域木](../graph/minimum-spanning-tree.md#modeling) › 操作を頂点にする・区間を辺にする（水のページの節） | グラフ | 必修 |
| 41 | [最小全域木](../graph/minimum-spanning-tree.md#few-weights) › 辺の重みの種類が少ないとき（水のページの節） | グラフ | 必修 |
| 42 | [連結成分](../graph/connected-components.md#values-as-vertices) › 座標や値を頂点にして成分を考える（基礎のページの節） | グラフ | 準必修 |
| 43 | [小さいグラフの全探索](../graph/small-graph-brute-force.md#coloring) › 彩色は成分ごとに DFS で塗って探索を絞る（基礎のページの節） | グラフ | 準必修 |
| 44 | [ワーシャルフロイド法](../graph/warshall-floyd.md#redundant-edges) › 迂回できる辺は不要（水のページの節） | グラフ | 準必修 |
| 45 | [時刻で変わる辺の最短路](../graph/time-dependent-dijkstra.md#optimal-departure) › 最適な出発時刻を計算してから進む（水のページの節） | グラフ | 準必修 |
| 46 | [ベルマンフォード法](../graph/bellman-ford.md) | グラフ | 準必修 |
| 47 | [Union-Find で連結性を扱う](../graph/union-find-connectivity.md#binary-search) › 二分探索と連結判定の組合せ（水のページの節） | グラフ | 準必修 |
| 48 | [最小ボトルネック路](../graph/bottleneck-path.md) | グラフ | 準必修 |
| 49 | [DFS 木・BFS 木とグラフの構築](../graph/graph-construction.md) | グラフ | 準必修 |
| 50 | [次数による平方分割](../graph/degree-sqrt.md) | グラフ | 準必修 |
| 51 | [木の構築・復元](../tree/tree-construction.md#from-degrees) › 次数の条件から作る（次数の足りない成分どうしをつなぐ）（水のページの節） | 木 | 必修 |
| 52 | [木の構築・復元](../tree/tree-construction.md#from-eccentricities) › 最遠距離の列から直径を決める（水のページの節） | 木 | 必修 |
| 53 | [最小共通祖先（LCA）](../tree/lca.md) | 木 | 必修 |
| 54 | [オイラーツアー](../tree/euler-tour.md) | 木 | 必修 |
| 55 | [木の上の累積和・いもす法](../tree/tree-imos.md#path-add) › パスへの加算（LCA に印を置いて葉から上へ累積する）（基礎のページの節） | 木 | 準必修 |
| 56 | [完全二分木](../tree/complete-binary-tree.md#count-at-distance) › 距離 K の頂点の数（部分木の深さの範囲を N で切る）（基礎のページの節） | 木 | 準必修 |
| 57 | [木の次数列と Prüfer 列](../tree/tree-degree.md) | 木 | 準必修 |
| 58 | [木の直径と最遠点](../tree/tree-diameter.md#root-at-end) › 直径の端点を根にして距離 K の頂点を探す（水のページの節） | 木 | 準必修 |
| 59 | [木の直径と最遠点](../tree/tree-diameter.md#join-trees) › 2 つの木をつないだ直径（水のページの節） | 木 | 準必修 |
| 60 | [根からのパスを DFS で持ち回る](../tree/root-path-dfs.md) | 木 | 準必修 |
| 61 | [set・multiset・map の応用](../ds/ordered-set.md#adjacent-pairs) › ソート順で隣り合う組の集合（2 番目に大きい値の寄与。最小 XOR の組は Binary Trie のページ）（基礎のページの節） | データ構造 | 必修 |
| 62 | [転倒数](../ds/inversion-number.md#sliding-window) › 窓を伸縮しながら転倒数を増減する（尺取り・期待値と組む）（水のページの節） | データ構造 | 必修 |
| 63 | [遅延セグメント木](../ds/lazy-segment-tree.md#invariants) › 保つ性質と push の手順（自作するとき）（水のページの節） | データ構造 | 必修 |
| 64 | [セグメント木に何を載せるか](../ds/segment-tree-monoids.md) | データ構造 | 必修 |
| 65 | [Union-Find の応用](../ds/union-find-applications.md#multiple-uf) › しきい値ごと・関係ごとに Union-Find を持つ（水のページの節） | データ構造 | 準必修 |
| 66 | [セグメント木上の二分探索](../ds/segment-tree-binary-search.md#on-lazy-segment-tree) › 遅延セグメント木の上の二分探索（単調な列への区間作用）（水のページの節） | データ構造 | 準必修 |
| 67 | [値を添字にする BIT・セグメント木](../ds/segment-tree-on-values.md#top-k-sum) › 上位 K 個の和（境界はセグメント木上の二分探索で探す）（水のページの節） | データ構造 | 準必修 |
| 68 | [Sparse Table](../ds/sparse-table.md) | データ構造 | 準必修 |
| 69 | [平面走査](../ds/sweep-line-2d.md) | データ構造 | 準必修 |
| 70 | [Mo's algorithm](../ds/mo-algorithm.md) | データ構造 | 準必修 |
| 71 | [永続データ構造](../ds/persistent-data-structures.md) | データ構造 | 準必修 |
| 72 | [マージソート木](../ds/merge-sort-tree.md) | データ構造 | 準必修 |
| 73 | [Binary Trie](../ds/binary-trie.md) | データ構造 | 準必修 |
| 74 | [約数の個数の上界と高度合成数](../math/divisor-count-bound.md#divisor-dp) › 約数を状態にした DP（約数の個数が少ないことを使う）（水のページの節） | 整数論・代数 | 必修 |
| 75 | [行列累乗](../math/matrix-power.md) | 整数論・代数 | 必修 |
| 76 | [等比数列の和を mod で求める](../math/geometric-series-mod.md#matrix) › 2×2 行列の累乗による別解（基礎のページの節） | 整数論・代数 | 準必修 |
| 77 | [最小素因数の篩と線形篩](../math/spf-sieve.md#linear-sieve) › 線形篩：各合成数を1回だけ作り、φ・μ の表を同時に作る（基礎のページの節） | 整数論・代数 | 準必修 |
| 78 | [中国剰余定理](../math/crt.md) | 整数論・代数 | 準必修 |
| 79 | [掃き出し法](../math/gaussian-elimination.md) | 整数論・代数 | 準必修 |
| 80 | [畳み込みの使い方](../math/convolution-ntt.md) | 整数論・代数 | 準必修 |
| 81 | [GCD の性質](../math/gcd-properties.md) | 整数論・代数 | 余裕があれば |
| 82 | [二項係数の前計算](../comb/binomial-precompute.md#lucas) › 法が小さい素数で n ≥ p になるとき：Lucas の定理（基礎のページの節） | 数え上げ・確率・ゲーム | 必修 |
| 83 | [二項係数の前計算](../comb/binomial-precompute.md#parity-pyramid) › p = 2 では (n & k) == k、ピラミッドの係数を二項係数と見抜く（基礎のページの節） | 数え上げ・確率・ゲーム | 必修 |
| 84 | [格子路の数え上げ](../comb/lattice-paths.md#forbidden-region) › 禁止領域を避ける：境界を越える点で分類する（基礎のページの節） | 数え上げ・確率・ゲーム | 必修 |
| 85 | [格子路の数え上げ](../comb/lattice-paths.md#sum-of-paths) › 経路数の総和と、二項係数の和を経路数として一括で求める（基礎のページの節） | 数え上げ・確率・ゲーム | 必修 |
| 86 | [格子路の数え上げ](../comb/lattice-paths.md#independent-axes) › 移動を軸ごとの回数に分けて独立にする（45 度回転）（基礎のページの節） | 数え上げ・確率・ゲーム | 必修 |
| 87 | [数え上げの考え方](../comb/counting-mindset.md#contribution-with-binomial) › 二項係数と組み合わせた寄与（残りの選び方を掛ける）（水のページの節） | 数え上げ・確率・ゲーム | 必修 |
| 88 | [包除原理](../comb/inclusion-exclusion.md) | 数え上げ・確率・ゲーム | 必修 |
| 89 | [重複の除き方](../comb/counting-dedup.md) | 数え上げ・確率・ゲーム | 準必修 |
| 90 | [二項係数の恒等式と和の公式](../comb/binomial-identities.md) | 数え上げ・確率・ゲーム | 準必修 |
| 91 | [約数包除](../comb/divisor-inclusion-exclusion.md) | 数え上げ・確率・ゲーム | 準必修 |
| 92 | [置換の巡回分解](../comb/permutation-cycles.md#power) › K 回の合成と元に戻る回数（巡回の長さの lcm）（基礎のページの節） | 数え上げ・確率・ゲーム | 準必修 |
| 93 | [置換の偶奇](../comb/permutation-parity.md) | 数え上げ・確率・ゲーム | 準必修 |
| 94 | [第 2 種スターリング数とベル数](../comb/bell-number.md) | 数え上げ・確率・ゲーム | 準必修 |
| 95 | [期待値の線形性と指示確率変数](../comb/linearity-of-expectation.md#pairs) › ペアごとの確率と対称性（水のページの節） | 数え上げ・確率・ゲーム | 準必修 |
| 96 | [確率 DP](../comb/probability-dp.md#random-walk) › ランダムウォークと二項係数（水のページの節） | 数え上げ・確率・ゲーム | 準必修 |
| 97 | [期待値 DP](../comb/expected-value-dp.md#prefix-sum) › 遷移を累積和でまとめる（水のページの節） | 数え上げ・確率・ゲーム | 準必修 |
| 98 | [閉路のある期待値](../comb/expectation-linear-equations.md) | 数え上げ・確率・ゲーム | 準必修 |
| 99 | [ゲームの基本と勝敗の DP](../comb/game-basics.md#mirror-strategy) › 真似戦略・ペアリング戦略（真似した手が合法かを確かめる）（水のページの節） | 数え上げ・確率・ゲーム | 準必修 |
| 100 | [Nim と XOR](../comb/nim.md#bounded) › 上限つき（x mod (k+1)）・範囲つきの変種（水のページの節） | 数え上げ・確率・ゲーム | 準必修 |
| 101 | [Nim と XOR](../comb/nim.md#asymmetric) › 先手と後手で取れる数が違うとき（水のページの節） | 数え上げ・確率・ゲーム | 準必修 |
| 102 | [Grundy 数と Sprague-Grundy の定理](../comb/grundy-number.md) | 数え上げ・確率・ゲーム | 準必修 |
| 103 | [対応づけ・数える対象の言い換え](../comb/counting-bijection.md) | 数え上げ・確率・ゲーム | 余裕があれば |
| 104 | [部分列の判定と次の出現位置の表](../string/subsequence-matching.md#repeated-string) › 繰り返した文字列の部分列（文字ごとの累積個数で位置を飛ばす）（基礎のページの節） | 文字列 | 準必修 |
| 105 | [ローリングハッシュ](../string/rolling-hash.md#hash-segment-tree) › セグ木に載せるハッシュ：（ハッシュ, B^長さ）の組で更新ありの一致・回文判定（水のページの節） | 文字列 | 準必修 |
| 106 | [ハッシュの衝突と安全な設計](../string/hash-safety.md) | 文字列 | 準必修 |
| 107 | [KMP 法と文字列の周期](../string/kmp.md) | 文字列 | 準必修 |
| 108 | [回文の扱いと Manacher](../string/palindrome.md#build-outside-in) › 外側から組み立てる（回文の式・約数）（水のページの節） | 文字列 | 準必修 |
| 109 | [回文の扱いと Manacher](../string/palindrome.md#manacher) › Manacher：各中心の最長回文半径を O(N) で（Z と同じく内側をコピーする）（水のページの節） | 文字列 | 準必修 |
| 110 | [Trie](../string/trie.md#dp-on-trie) › Trie 上の DFS と、節点に値を持つ DP（水のページの節） | 文字列 | 準必修 |
| 111 | [マンハッタン距離と 45 度回転](../geometry/manhattan-chebyshev.md#parity-after-rotation) › 回転後の偶奇：u と v の偶奇がそろう点だけが元の格子点（チェビシェフ → マンハッタンで 1/2 が出る）（水のページの節） | 幾何 | 必修 |
| 112 | [偏角ソート](../geometry/argument-sort.md#wrap-around) › 一周を扱う：配列を 2 周分にして尺取り（水のページの節） | 幾何 | 準必修 |
| 113 | [偏角ソート](../geometry/argument-sort.md#opposite-direction) › 反対方向に最も近い点の二分探索（水のページの節） | 幾何 | 準必修 |
| 114 | [偏角ソート](../geometry/argument-sort.md#angular-intervals) › 角度の区間のスケジューリング・連続する範囲だけを試す最適化（水のページの節） | 幾何 | 準必修 |
| 115 | [円と幾何の最適化](../geometry/circle-geometry.md) | 幾何 | 準必修 |
| 116 | [インタラクティブ問題](../misc/interactive.md#equations-crt) › 連立方程式・中国剰余定理で特定する（基礎のページの節） | その他の技法 | 準必修 |
| 117 | [インタラクティブ問題](../misc/interactive.md#output-structure-first) › 先に構造を出力してから答える（基礎のページの節） | その他の技法 | 準必修 |
| 118 | [乱択アルゴリズム](../misc/randomized.md) | その他の技法 | 準必修 |
| 119 | [bitset による高速化](../misc/bitset-speedup.md) | その他の技法 | 準必修 |
| 120 | [構文解析](../misc/parsing.md) | その他の技法 | 準必修 |
| 121 | [並べ替えてから DP する](../dp/exchange-argument-dp.md) | 動的計画法 | 準必修 |
| 122 | [インライン DP](../dp/inline-dp.md) | 動的計画法 | 準必修 |
| 123 | [差分制約（牛ゲー）](../graph/difference-constraints.md) | グラフ | 余裕があれば |
| 124 | [木の上のパスの判定と分解](../tree/tree-path.md) | 木 | 準必修 |
| 125 | [遅延セグメント木の載せ方の型](../ds/lazy-segment-tree-patterns.md) | データ構造 | 準必修 |
| 126 | [約数・倍数のゼータ変換とメビウス変換](../comb/zeta-mobius-divisor.md) | 数え上げ・確率・ゲーム | 準必修 |
| 127 | [Aho-Corasick 法](../string/aho-corasick.md) | 文字列 | 準必修 |
| 128 | [照合オートマトン上の DP](../string/string-automaton-dp.md) | 文字列 | 準必修 |

### 黄（difficulty 2000〜2399） {#reading-order-yellow}

| # | ページ | 分野 | 頻度 |
| --- | --- | --- | --- |
| 1 | [差分列への言い換え](../basics/difference-sequence.md) | 基本テクニック | 必修 |
| 2 | [分割統治](../basics/divide-and-conquer.md) | 基本テクニック | 必修 |
| 3 | [平均・中央値の最大化](../basics/fractional-binary-search.md#median-of-medians) › 全区間の中央値の中央値（転倒数で数える）（水のページの節） | 基本テクニック | 準必修 |
| 4 | [挿入 DP・箱根駅伝 DP](../dp/insertion-dp.md) | 動的計画法 | 必修 |
| 5 | [並べ替えてから DP する](../dp/exchange-argument-dp.md#place-at-ends) › 大きい順に左右の端へ置く（青のページの節） | 動的計画法 | 準必修 |
| 6 | [グリッド上の DP](../dp/dp-grid.md#top-k-on-path) › 経路上の上位 K 個（K 番目を固定して状態に）（水のページの節） | 動的計画法 | 準必修 |
| 7 | [最長共通部分列と編集距離](../dp/lcs.md#dp-of-dp) › LCS の値ごとに数える：DP の DP（内側の DP の 1 行を外側の状態にする）（水のページの節） | 動的計画法 | 準必修 |
| 8 | [部分列 DP](../dp/subsequence-dp.md) | 動的計画法 | 準必修 |
| 9 | [区間 DP の応用](../dp/interval-dp-advanced.md) | 動的計画法 | 準必修 |
| 10 | [bitDP](../dp/bit-dp.md#primes) › 素数の使用状況を集合で持つ（水のページの節） | 動的計画法 | 準必修 |
| 11 | [部分集合を列挙する DP](../dp/subset-enumeration-dp.md#vs-zeta) › 高速ゼータ変換との使い分け（青のページの節） | 動的計画法 | 準必修 |
| 12 | [プロファイル DP](../dp/broken-profile-dp.md) | 動的計画法 | 準必修 |
| 13 | [桁 DP の応用](../dp/digit-dp-advanced.md) | 動的計画法 | 準必修 |
| 14 | [木 DP](../dp/tree-dp.md#with-binary-search) › 二分探索と組み合わせて判定にする（水のページの節） | 動的計画法 | 準必修 |
| 15 | [木 DP](../dp/tree-dp.md#tree-dp-merge) › 部分木の情報をデータ構造で持ってマージする（マージテク）（水のページの節） | 動的計画法 | 準必修 |
| 16 | [インライン DP](../dp/inline-dp.md#with-monotonic-stack) › 単調スタックと組み合わせる（青のページの節） | 動的計画法 | 準必修 |
| 17 | [戻す DP](../dp/knapsack-undo.md#offline-divide-and-conquer) › 分割統治でオフラインに処理する（青のページの節） | 動的計画法 | 余裕があれば |
| 18 | [二乗の木 DP](../dp/tree-dp-square.md) | 動的計画法 | 余裕があれば |
| 19 | [最短路 DAG](../graph/shortest-path-dag.md#edge-removal) › 辺を消すと距離が変わるか（水のページの節） | グラフ | 準必修 |
| 20 | [最小ボトルネック路](../graph/bottleneck-path.md#many-queries) › 多数の 2 点の質問：成分にクエリを持たせて小さい方から移す（青のページの節） | グラフ | 準必修 |
| 21 | [橋・関節点・二重連結成分](../graph/lowlink.md) | グラフ | 準必修 |
| 22 | [DFS 木・BFS 木とグラフの構築](../graph/graph-construction.md#parity-walk) › DFS 木をたどって偶奇を合わせる（青のページの節） | グラフ | 準必修 |
| 23 | [次数による平方分割](../graph/degree-sqrt.md#triangles) › 三角形の列挙（次数の小さい方から向き付ける）（青のページの節） | グラフ | 準必修 |
| 24 | [次数による平方分割](../graph/degree-sqrt.md#four-cycles) › 長さ 4 の閉路の検出（鳩の巣原理で打ち切る）（青のページの節） | グラフ | 準必修 |
| 25 | [最大流](../graph/max-flow.md) | グラフ | 準必修 |
| 26 | [補グラフ上の BFS](../graph/complement-graph-bfs.md) | グラフ | 余裕があれば |
| 27 | [オイラー路（一筆書き）](../graph/euler-path.md) | グラフ | 余裕があれば |
| 28 | [木の直径と最遠点](../tree/tree-diameter.md#center) › 中心と半径・直径の個数（水のページの節） | 木 | 準必修 |
| 29 | [木の直径と最遠点](../tree/tree-diameter.md#long-path-decomposition) › 長鎖分解（最も深い子へつなぐ分解と、最も遠い葉を順に選ぶ貪欲）（水のページの節） | 木 | 準必修 |
| 30 | [辺で切って数える](../tree/tree-edge-contribution.md#expectation) › 期待値・特定の色を通らないパスへの応用（水のページの節） | 木 | 準必修 |
| 31 | [木の重心](../tree/tree-centroid.md) | 木 | 準必修 |
| 32 | [マージテク](../tree/small-to-large.md#reroot-smaller) › 森に辺を足すとき小さい方を根付け直す（水のページの節） | 木 | 準必修 |
| 33 | [マージテク](../tree/small-to-large.md#subtree-merge) › 部分木ごとの集合の併合（木 DP での使い方は DP の章）（水のページの節） | 木 | 準必修 |
| 34 | [マージテク](../tree/small-to-large.md#dsu-on-tree) › DSU on Tree（重い子の結果を残す）（水のページの節） | 木 | 準必修 |
| 35 | [上位 K 個の和と中央値の管理](../ds/top-k-multiset.md#absolute-sum-function) › \|x − a\| + b を足していく関数の最小値（中央値の更新の応用。Slope Trick の入口）（水のページの節） | データ構造 | 準必修 |
| 36 | [区間を set で管理する](../ds/interval-set.md#valued-intervals) › 値つきの区間の分割・統合（水のページの節） | データ構造 | 準必修 |
| 37 | [単調スタックとスライド最小値](../ds/monotonic-stack.md#cartesian-tree) › Cartesian tree（最大値で区間を割る再帰を O(N) で作る）（水のページの節） | データ構造 | 準必修 |
| 38 | [値を添字にする BIT・セグメント木](../ds/segment-tree-on-values.md#odd-position-sum) › 左の個数の偶奇で右の読み方が変わる量（ソート後の奇数番目の和）（水のページの節） | データ構造 | 準必修 |
| 39 | [値を添字にする BIT・セグメント木](../ds/segment-tree-on-values.md#dynamic-segment-tree) › 動的セグメント木（必要なノードだけ作る）（水のページの節） | データ構造 | 準必修 |
| 40 | [遅延セグメント木の載せ方の型](../ds/lazy-segment-tree-patterns.md#reformulate) › 言い換えてから載せる（しきい値で 0/1 にする・X_i − i・寄与）（青のページの節） | データ構造 | 準必修 |
| 41 | [平面走査](../ds/sweep-line-2d.md#union-area) › 長方形の和集合の面積（区間加算・最小値とその個数）（青のページの節） | データ構造 | 準必修 |
| 42 | [Mo's algorithm](../ds/mo-algorithm.md#two-prefixes) › 2 つの接頭辞の長さ (X, Y) を区間と見る（青のページの節） | データ構造 | 準必修 |
| 43 | [Mo's algorithm](../ds/mo-algorithm.md#mo-on-tree) › 木上の Mo（入りと出の両方を記録した列で、パスを区間にする。LCA を別に足す）（青のページの節） | データ構造 | 準必修 |
| 44 | [平方分割](../ds/sqrt-decomposition.md) | データ構造 | 準必修 |
| 45 | [約数の個数の上界と高度合成数](../math/divisor-count-bound.md#enumerate-hcn) › 高度合成数の列挙（小さい素数の指数が単調に減る形を DFS で）（水のページの節） | 整数論・代数 | 必修 |
| 46 | [行列累乗](../math/matrix-power.md#doubling-transition) › ダブリングで遷移を合成する（行列にすると大きすぎるとき・桁を倍々に伸ばす）（青のページの節） | 整数論・代数 | 必修 |
| 47 | [行列累乗](../math/matrix-power.md#profile-dp) › プロファイル DP の遷移行列と状態数の見積もり（青のページの節） | 整数論・代数 | 必修 |
| 48 | [フェルマーの小定理と指数の mod](../math/exponent-mod.md#euler-theorem) › 一般の法：オイラーの定理と、互いに素でないときの一般化（累乗の塔）（水のページの節） | 整数論・代数 | 準必修 |
| 49 | [オイラーの φ 関数](../math/euler-phi.md) | 整数論・代数 | 準必修 |
| 50 | [中国剰余定理](../math/crt.md#garner) › Garner のアルゴリズム（巨大な解を mod で求める）（青のページの節） | 整数論・代数 | 準必修 |
| 51 | [floor sum](../math/floor-sum.md) | 整数論・代数 | 準必修 |
| 52 | [XOR 基底](../math/xor-basis.md) | 整数論・代数 | 準必修 |
| 53 | [畳み込みの使い方](../math/convolution-ntt.md#string-matching) › 文字列の照合：ずらしたときの一致数・ハミング距離・ワイルドカード（青のページの節） | 整数論・代数 | 準必修 |
| 54 | [畳み込みの使い方](../math/convolution-ntt.md#split-by-bit) › bit ごと・文字ごとに分けて畳み込む（OR の和など）（青のページの節） | 整数論・代数 | 準必修 |
| 55 | [順序を固定して数える](../comb/counting-fix-order.md#tree-order) › 木の上の順番 n!/Π 部分木の大きさ（水のページの節） | 数え上げ・確率・ゲーム | 準必修 |
| 56 | [多項係数](../comb/multinomial-coefficient.md#insert-rest) › 一部を先に並べて残りを挿入する（水のページの節） | 数え上げ・確率・ゲーム | 準必修 |
| 57 | [多項係数](../comb/multinomial-coefficient.md#same-size-groups) › 区別しない同じ大きさのグループを割る（水のページの節） | 数え上げ・確率・ゲーム | 準必修 |
| 58 | [メビウス関数とメビウス反転](../comb/mobius-function.md) | 数え上げ・確率・ゲーム | 準必修 |
| 59 | [部分集合の高速ゼータ変換とメビウス変換](../comb/zeta-mobius-subset.md) | 数え上げ・確率・ゲーム | 準必修 |
| 60 | [整数の分割と分割数](../comb/partition-number.md) | 数え上げ・確率・ゲーム | 準必修 |
| 61 | [連結なグラフの数え上げ](../comb/counting-labeled-graphs.md) | 数え上げ・確率・ゲーム | 準必修 |
| 62 | [確率 DP](../comb/probability-dp.md#matrix-power) › 同じ遷移を多数回行うときは行列累乗へ（水のページの節） | 数え上げ・確率・ゲーム | 準必修 |
| 63 | [最適戦略の期待値](../comb/optimal-strategy-expectation.md) | 数え上げ・確率・ゲーム | 準必修 |
| 64 | [期待値と確率の変換](../comb/expectation-tail-sum.md) | 数え上げ・確率・ゲーム | 準必修 |
| 65 | [二乗の期待値・分散](../comb/expectation-of-square.md) | 数え上げ・確率・ゲーム | 準必修 |
| 66 | [ミニマックス](../comb/minimax.md#tree) › 木の上のゲーム（水のページの節） | 数え上げ・確率・ゲーム | 準必修 |
| 67 | [ミニマックス](../comb/minimax.md#binary-search) › 答えを決め打ちして勝敗に直す（水のページの節） | 数え上げ・確率・ゲーム | 準必修 |
| 68 | [後退解析](../comb/game-retrograde-analysis.md) | 数え上げ・確率・ゲーム | 準必修 |
| 69 | [鏡像法とカタラン数](../comb/reflection-principle.md) | 数え上げ・確率・ゲーム | 余裕があれば |
| 70 | [包除 DP](../comb/inclusion-exclusion-dp.md) | 数え上げ・確率・ゲーム | 余裕があれば |
| 71 | [ラベル付き木の数え上げ](../comb/cayley-pruefer.md) | 数え上げ・確率・ゲーム | 余裕があれば |
| 72 | [集合・多重集合のハッシュ](../string/hashing-for-sets.md#multiplicity-mod-k) › 各値が偶数個・k の倍数個かの判定（指数 mod k を乱数で符号化）（水のページの節） | 文字列 | 準必修 |
| 73 | [Z-algorithm](../string/z-algorithm.md#prefix-extension) › S＋区切り＋T で各位置から S の接頭辞が何文字続くか（DP の材料）（水のページの節） | 文字列 | 準必修 |
| 74 | [Trie](../string/trie.md#expectation-on-trie) › Trie 上の確率・期待値（水のページの節） | 文字列 | 準必修 |
| 75 | [Aho-Corasick 法](../string/aho-corasick.md#forbidden-greedy) › 禁止語の貪欲：一致したら書き換えて状態を根に戻す（青のページの節） | 文字列 | 準必修 |
| 76 | [Suffix Array と LCP 配列](../string/suffix-array.md) | 文字列 | 準必修 |
| 77 | [マンハッタン距離と 45 度回転](../geometry/manhattan-chebyshev.md#diamond-range) › ひし形の範囲を正方形にして 2 次元累積和（水のページの節） | 幾何 | 必修 |
| 78 | [回転・平行移動・アフィン変換](../geometry/rotation-transform.md#congruence) › 点集合の合同判定：重心をそろえて照合する（水のページの節） | 幾何 | 準必修 |
| 79 | [円と幾何の最適化](../geometry/circle-geometry.md#ternary-search-caveats) › 三分探索の注意：凸性の確認・入れ子の三分探索・式の変わり目の時刻を列挙する方法（青のページの節） | 幾何 | 準必修 |
| 80 | [凸包と凸多角形](../geometry/convex-hull.md) | 幾何 | 準必修 |
| 81 | [乱択アルゴリズム](../misc/randomized.md#color-coding) › Color Coding（青のページの節） | その他の技法 | 準必修 |
| 82 | [bitset による高速化](../misc/bitset-speedup.md#subset-sum-shift) › 部分和 DP のシフト OR（青のページの節） | その他の技法 | 準必修 |
| 83 | [bitset による高速化](../misc/bitset-speedup.md#reachability) › DAG の到達可能性（逆トポロジカル順に OR、閉路は SCC で縮約）（青のページの節） | その他の技法 | 準必修 |
| 84 | [bitset による高速化](../misc/bitset-speedup.md#memory-batching) › メモリの見積もりと 64 個ずつのクエリの処理（青のページの節） | その他の技法 | 準必修 |
| 85 | [最小カット](../graph/min-cut.md) | グラフ | 準必修 |
| 86 | [二部マッチング](../graph/bipartite-matching.md) | グラフ | 準必修 |
| 87 | [最小費用流](../graph/min-cost-flow.md) | グラフ | 準必修 |
| 88 | [重心分解](../tree/centroid-decomposition.md) | 木 | 準必修 |
| 89 | [位数・原始根・離散対数](../math/multiplicative-order.md) | 整数論・代数 | 準必修 |
| 90 | [燃やす埋める](../graph/project-selection.md) | グラフ | 準必修 |
| 91 | [König の定理](../graph/konig-theorem.md) | グラフ | 準必修 |

### 発展（difficulty 2400〜（概要だけ）） {#reading-order-advanced}

| # | ページ | 分野 | 頻度 |
| --- | --- | --- | --- |
| 1 | [平均・中央値の最大化](../basics/fractional-binary-search.md#dinkelbach) › Dinkelbach 法（水のページの節） | 基本テクニック | 準必修 |
| 2 | [挿入 DP・箱根駅伝 DP](../dp/insertion-dp.md#connected-component-dp) › 連結成分 DP（ブロックを作る・端に付ける・つなぐ）（黄のページの節） | 動的計画法 | 必修 |
| 3 | [プロファイル DP](../dp/broken-profile-dp.md#connectivity) › 連結性を持つ（フロンティア法）（黄のページの節） | 動的計画法 | 準必修 |
| 4 | [Monge 性による DP の高速化](../dp/monge.md) | 動的計画法 | 準必修 |
| 5 | [Alien DP](../dp/alien-dp.md) | 動的計画法 | 準必修 |
| 6 | [Slope Trick](../dp/slope-trick.md) | 動的計画法 | 準必修 |
| 7 | [動的 DP](../dp/dynamic-dp.md) | 動的計画法 | 余裕があれば |
| 8 | [Convex Hull Trick と Li Chao Tree](../dp/cht.md) | 動的計画法 | 余裕があれば |
| 9 | [最小ボトルネック路](../graph/bottleneck-path.md#reconstruction-tree) › 併合過程の木（Kruskal 再構築木）でオンラインに答える（木の章へ）（青のページの節） | グラフ | 準必修 |
| 10 | [橋・関節点・二重連結成分](../graph/lowlink.md#block-cut-tree) › 二重頂点連結成分とブロックカット木（黄のページの節） | グラフ | 準必修 |
| 11 | [最小カット](../graph/min-cut.md#cut-shape) › カットの形を決め打つ（黄のページの節） | グラフ | 準必修 |
| 12 | [燃やす埋める](../graph/project-selection.md#multi-valued) › 多値変数を頂点の列で表す（黄のページの節） | グラフ | 準必修 |
| 13 | [二部マッチング](../graph/bipartite-matching.md#edge-coloring) › 正則二部グラフの分解・辺彩色（黄のページの節） | グラフ | 準必修 |
| 14 | [König の定理](../graph/konig-theorem.md#lp-half-integrality) › 頂点を 2 倍にして二部グラフにする（LP の半整数性）（黄のページの節） | グラフ | 準必修 |
| 15 | [最小費用流](../graph/min-cost-flow.md#hungarian) › 割当問題とハンガリアン法（黄のページの節） | グラフ | 準必修 |
| 16 | [最小パス被覆と Hall の定理](../graph/dilworth-path-cover.md) | グラフ | 準必修 |
| 17 | [彩色数・最大独立集合・最大クリーク](../graph/chromatic-number.md) | グラフ | 余裕があれば |
| 18 | [剰余を頂点にする最短路](../graph/modular-shortest-path.md) | グラフ | 余裕があれば |
| 19 | [区間に辺を張る](../graph/segment-tree-graph.md) | グラフ | 余裕があれば |
| 20 | [K 番目の最短路](../graph/k-shortest-paths.md) | グラフ | 余裕があれば |
| 21 | [最小シュタイナー木](../graph/steiner-tree.md) | グラフ | 余裕があれば |
| 22 | [2-SAT](../graph/two-sat.md) | グラフ | 余裕があれば |
| 23 | [特殊な最小全域木](../graph/spanning-tree-advanced.md) | グラフ | 余裕があれば |
| 24 | [最小流量制約付きフロー](../graph/flow-lower-bounds.md) | グラフ | 余裕があれば |
| 25 | [一般グラフのマッチング](../graph/general-matching.md) | グラフ | 余裕があれば |
| 26 | [オイラーツアー](../tree/euler-tour.md#to-hld) › 逆元がない演算・パスへの一括更新は HL 分解（青のページの節） | 木 | 必修 |
| 27 | [木の上のパスの判定と分解](../tree/tree-path.md#to-hld) › パスへの一括更新があるなら HL 分解（青のページの節） | 木 | 準必修 |
| 28 | [HL 分解](../tree/hld.md) | 木 | 準必修 |
| 29 | [重心分解](../tree/centroid-decomposition.md#with-convolution) › 距離の頻度表は畳み込みと組む（黄のページの節） | 木 | 準必修 |
| 30 | [木の同型判定と木のハッシュ](../tree/tree-isomorphism.md) | 木 | 余裕があれば |
| 31 | [Auxiliary Tree](../tree/auxiliary-tree.md) | 木 | 余裕があれば |
| 32 | [併合過程の木](../tree/merge-process-tree.md) | 木 | 余裕があれば |
| 33 | [比で親に併合する貪欲](../tree/tree-ratio-greedy.md) | 木 | 余裕があれば |
| 34 | [単調スタックとスライド最小値](../ds/monotonic-stack.md#swag) › SWAG：スタック 2 本で作る総積つきキュー（水のページの節） | データ構造 | 準必修 |
| 35 | [Sparse Table](../ds/sparse-table.md#disjoint-sparse-table) › 冪等でない演算（2 べきに分けて O(log N)、Disjoint Sparse Table）（青のページの節） | データ構造 | 準必修 |
| 36 | [Mo's algorithm](../ds/mo-algorithm.md#variants) › 時間付き Mo・ロールバック Mo（青のページの節） | データ構造 | 準必修 |
| 37 | [永続データ構造](../ds/persistent-data-structures.md#prefix-versions) › 接頭辞ごとの版で区間の K 番目・x 以下の個数をオンラインで求める（青のページの節） | データ構造 | 準必修 |
| 38 | [マージソート木](../ds/merge-sort-tree.md#bit-per-level) › 各段に BIT を持たせる（先読みと組む）（青のページの節） | データ構造 | 準必修 |
| 39 | [部分永続 Union-Find](../ds/partially-persistent-union-find.md) | データ構造 | 余裕があれば |
| 40 | [ロールバックできる Union-Find](../ds/rollback-union-find.md) | データ構造 | 余裕があれば |
| 41 | [Segment Tree Beats](../ds/segment-tree-beats.md) | データ構造 | 余裕があれば |
| 42 | [並列二分探索](../ds/parallel-binary-search.md) | データ構造 | 余裕があれば |
| 43 | [CDQ 分割統治](../ds/cdq-divide-and-conquer.md) | データ構造 | 余裕があれば |
| 44 | [Wavelet Matrix](../ds/wavelet-matrix.md) | データ構造 | 余裕があれば |
| 45 | [平衡二分探索木と pb_ds の tree](../ds/balanced-bst.md) | データ構造 | 余裕があれば |
| 46 | [位数・原始根・離散対数](../math/multiplicative-order.md#mod-root) › 平方剰余と mod の K 乗根（オイラーの規準・Tonelli-Shanks・Cipolla）（黄のページの節） | 整数論・代数 | 準必修 |
| 47 | [floor sum](../math/floor-sum.md#applications) › 応用の型：bit ごとの popcount・1 次式の mod の積（黄のページの節） | 整数論・代数 | 準必修 |
| 48 | [分割統治 FFT・オンライン畳み込み](../math/online-convolution.md) | 整数論・代数 | 準必修 |
| 49 | [形式的冪級数と多項式の演算](../math/fps-basics.md) | 整数論・代数 | 準必修 |
| 50 | [大きな数の素数判定と素因数分解](../math/miller-rabin.md) | 整数論・代数 | 余裕があれば |
| 51 | [乗法的関数の和と素数の個数](../math/multiplicative-function.md) | 整数論・代数 | 余裕があれば |
| 52 | [Stern-Brocot 木と連分数](../math/stern-brocot.md) | 整数論・代数 | 余裕があれば |
| 53 | [行列式](../math/determinant.md) | 整数論・代数 | 余裕があれば |
| 54 | [FFT・NTT の仕組みと任意 mod の畳み込み](../math/fft-ntt.md) | 整数論・代数 | 余裕があれば |
| 55 | [XOR 畳み込み](../math/hadamard-transform.md) | 整数論・代数 | 余裕があれば |
| 56 | [ラグランジュ補間とべき乗和](../math/lagrange-interpolation.md) | 整数論・代数 | 余裕があれば |
| 57 | [包除原理](../comb/inclusion-exclusion.md#min-max) › min-max 包除（全種類がそろうまでの期待値）（青のページの節） | 数え上げ・確率・ゲーム | 必修 |
| 58 | [母関数の考え方](../comb/generating-function-counting.md) | 数え上げ・確率・ゲーム | 準必修 |
| 59 | [メビウス関数とメビウス反転](../comb/mobius-function.md#quotient) › 商の列挙で同じ値の範囲を束ねる（黄のページの節） | 数え上げ・確率・ゲーム | 準必修 |
| 60 | [整数の分割と分割数](../comb/partition-number.md#partition-dp) › 分割数型の DP（黄のページの節） | 数え上げ・確率・ゲーム | 準必修 |
| 61 | [期待値と確率の変換](../comb/expectation-tail-sum.md#continuous) › 連続値の場合（積分）（黄のページの節） | 数え上げ・確率・ゲーム | 準必修 |
| 62 | [Nim と XOR](../comb/nim.md#misere) › 逆形 Nim（最後に取った方が負け）（水のページの節） | 数え上げ・確率・ゲーム | 準必修 |
| 63 | [Nim と XOR](../comb/nim.md#counting) › 必勝局面の数え上げ（XOR 畳み込み）（水のページの節） | 数え上げ・確率・ゲーム | 準必修 |
| 64 | [後退解析](../comb/game-retrograde-analysis.md#weighted) › 得点のあるゲームはダイクストラ法の要領で確定させる（黄のページの節） | 数え上げ・確率・ゲーム | 準必修 |
| 65 | [Burnside の補題](../comb/burnside-lemma.md) | 数え上げ・確率・ゲーム | 余裕があれば |
| 66 | [鏡像法とカタラン数](../comb/reflection-principle.md#two-sided) › 両端を越えない場合（黄のページの節） | 数え上げ・確率・ゲーム | 余裕があれば |
| 67 | [二項係数の部分和](../comb/binomial-prefix-sum.md) | 数え上げ・確率・ゲーム | 余裕があれば |
| 68 | [包除 DP](../comb/inclusion-exclusion-dp.md#tree) › 符号付きの木 DP（黄のページの節） | 数え上げ・確率・ゲーム | 余裕があれば |
| 69 | [第 1 種スターリング数](../comb/stirling-first.md) | 数え上げ・確率・ゲーム | 余裕があれば |
| 70 | [Young 図形とフック長公式](../comb/young-tableaux.md) | 数え上げ・確率・ゲーム | 余裕があれば |
| 71 | [ラベル付き木の数え上げ](../comb/cayley-pruefer.md#with-polynomials) › 多項式（母関数）と組み合わせる（黄のページの節） | 数え上げ・確率・ゲーム | 余裕があれば |
| 72 | [連続値の確率](../comb/continuous-probability.md) | 数え上げ・確率・ゲーム | 余裕があれば |
| 73 | [非不偏ゲーム](../comb/partizan-games.md) | 数え上げ・確率・ゲーム | 余裕があれば |
| 74 | [Suffix Array と LCP 配列](../string/suffix-array.md#kth-substring) › 部分文字列の辞書順 K 番目（黄のページの節） | 文字列 | 準必修 |
| 75 | [Suffix Automaton と発展の文字列アルゴリズム](../string/suffix-automaton.md) | 文字列 | 準必修 |
| 76 | [発展の幾何](../geometry/advanced-geometry.md) | 幾何 | 準必修 |
| 77 | [構文解析](../misc/parsing.md#substring-sum) › 式の部分文字列の総和（青のページの節） | その他の技法 | 準必修 |
| 78 | [辺の追加と削除が混ざる連結性](../graph/offline-dynamic-connectivity.md) | グラフ | 余裕があれば |
| 79 | [行列木定理](../graph/matrix-tree-theorem.md) | グラフ | 余裕があれば |
| 80 | [Static Top Tree と木 DP の動的更新](../tree/static-top-tree.md) | 木 | 余裕があれば |
| 81 | [動的木](../tree/dynamic-tree.md) | 木 | 余裕があれば |
| 82 | [線形漸化式の高速化](../math/linear-recurrence-fast.md) | 整数論・代数 | 余裕があれば |
| 83 | [LGV 補題](../comb/lgv-lemma.md) | 数え上げ・確率・ゲーム | 余裕があれば |

<!-- textlint-enable -->
<!-- gen:end roadmap-order -->

## 色ごとの練習の方法 {#practice}

練習の中心は、目標の色のパフォーマンスで分かれ目になる位置の問題である。どの色でも、自分のレートから少し上の difficulty の問題を選び、解けなかった問題は解き直す。問題の選び方と量の目安は[精進の仕方](practice-method.md#choosing-problems)、問題集の一覧は[問題集と練習用コンテストの案内](problem-sets.md#collections)にある。

| 目標 | 中心の位置 | difficulty の目安 | 問題集の例 |
| --- | --- | --- | --- |
| 水 | E | 1200〜1599 | [典型90](../guide/glossary.md#typical90) の★5、鉄則本 |
| 青 | F と難しい E | 1600〜1999 | 典型90 の★6、[EDPC](../guide/glossary.md#edpc) |
| 黄 | 難しい F と易しい G | 2000〜2399 | 典型90 の★7 |

典型90 の★ごとに difficulty の範囲が決まっていて、仮に AtCoder に出たら、どのレート帯の参加者の半分が解きそうかを表す。★5 は 1200〜1599、★6 は 1600〜1999、★7 は 2000 以上にあたる（[典型90問の★とレベル](problem-sets.md#typical90-stars)）。

- **水**：E を解く練習と同じくらい、D までを速く確実に解く練習が効く。A〜D を約 40 分で解けないうちは、E を解いても水のパフォーマンスに届きにくい（[到達の目安](#targets)）。
- **青**：F で最も多いのはデータ構造なので、水の列のセグメント木を、条件を言い換えて載せる練習まで含めて身につける。E を落とした回は、E の見直しを優先する。
- **黄**：青 diff 以下の問題をペナルティなしで速く解けるかを、[バーチャル参加](practice-method.md#speed)や [ADT](../guide/glossary.md#adt) で確かめる。黄の列のページは、難しい F と易しい G の解き直しで身につける。

過去の ABC から問題を選ぶときは、位置ではなく difficulty で選ぶ。6 問体制（abc126〜abc211）の E・F は今より難しく、E の difficulty の中央値は 1528（abc400〜abc480 では 1286）、F は 2132（同じく 1744）である。8 問体制（abc212〜abc318）の E・F・G は今とほぼ同じ難しさで（中央値 1308・1866・2326。今の G は 2391）、その上の Ex は今の G より難しい（中央値 2912）。2023 年 9 月の abc319 からは 7 問体制で、E〜G の難しさに一方向の変化は見えないので、abc319 以降なら位置をそのまま目安にしてよい。

## 解いた数・理解した数 {#progress}

下の表は、このブラウザで付けた「理解した」と「解いた」のチェックを集計したものである。レベル別・分野別の表と、問題の difficulty の色別の表がある。

- **理解した**：各ページの上と下にあるチェック欄と、[色ごとのページの列](#reading-order)の行のチェック欄から数える。チェック欄はページのレベルと、ページの中の上の帯の節のレベルの数だけあり、1 つずつ数える。
- **解いた問題**：各ページの例題・練習・力試しの一覧の、行の先頭のチェック欄から数える。レベル別・分野別の表では、問題を載せたページのレベル・分野で数える。
- **difficulty の色別**：解いた問題を、問題そのものの difficulty の色（灰・茶・緑・水・青・黄・橙・赤）で数える。基礎のページにも difficulty の高い力試しが載るので、水の difficulty の問題を何問解いたかは、この表で見る。

<div class="kp-roadmap-stats"></div>

記録はこのブラウザの localStorage にだけ保存し、端末どうしで同期しない。別の端末へ移すときや退避するときは、次の欄で書き出し・読み込みをする。「ファイルに保存」で記録を JSON のファイルに書き出し、別の端末では「ファイルから読み込む」でそのファイルを選ぶ。欄には、最後に書き出した日も出る。

<div class="kp-progress-io"></div>

iPhone や Mac の Safari では、Safari を使った 7 日の間にこのサイトを一度も操作しないと、localStorage を含む保存データが消える。WebKit の Intelligent Tracking Prevention の仕様である。ホーム画面に追加したウェブアプリは、そのアプリを実際に使った日だけを数えるので消えにくい。Safari で読むときは、ときどきファイルに保存して退避しておく。

理解したページと前提のつながりは、[知識マップ](knowledge-map.md#progress)で塗り分けて見られる。あとで読みたいページは、各ページの「勉強したい」で[勉強したいリスト](study-list.md)に入れておける。

## シラバスではないこと {#not-a-syllabus}

このロードマップは読む順の案内であり、出題範囲の一覧（シラバス）ではない。

- **列にない知識も出る**：G の上半分では発展の手法が使われ、どのページにも当たらない考察だけで解く問題もある。
- **レベルは使われ始める帯である**：同じ手法でも、易しい使い方と難しい使い方で帯が変わる。そのためページの中に上の帯の節があり、列に節の行として入る。
- **列を終えてから次の色へ進むのではない**：水の列を全部読む前に E を解き始めてよい。列は、解けなかった問題の手法を探すときの地図としても使う。
- **列と頻度は変わる**：ページが増えたときや、最近の ABC の分類を付け直したときに、並びと頻度が変わる。

解けなかった問題から手法を探すときは、[逆引き辞典（言い回しから）](reverse-index-signs.md#by-phrase)・[逆引き辞典（制約から）](reverse-index-constraints.md#constraint-table)と、[詰まったときの発想リスト](thinking-checklist.md)を使う。

## 参考 {#references}

- [kenkoooo「AtCoderProblems / time-estimator/function.py」](https://github.com/kenkoooo/AtCoderProblems/blob/master/lambda-functions/time-estimator/function.py)：difficulty と予測解答時間のモデル。到達の目安の表は、このモデルの値を tools/ap.py のデータで集計した
- [E869120「AtCoder での実力アップを目指そう！　～競プロ典型 90 問～」](https://qiita.com/e869120/items/1b2a5f0f07fd927e44e9)：★と difficulty の帯の対応
- [nouka28「AtCoderで入黄しました！！」](https://qiita.com/nouka28/items/a8b06865331838642ff2)：青から黄で新しく覚えた知識を本番で使った場面
- [ks2m「AtCoder黄色になるまでにやったこととやっていないこと」](https://ks2m.hatenablog.com/entry/2021/03/08/230503)：学ばないまま黄色に届いた手法と、青 diff の正答率
- [bluebery1001「【Atcoder】高校2年生でAtcoder黄色になりました」](https://qiita.com/bluebery1001/items/3253399ebf287e197346)：7 問体制での黄色の目安
- [WebKit「Full Third-Party Cookie Blocking and More」](https://webkit.org/blog/10218/full-third-party-cookie-blocking-and-more/)：Safari が 7 日で保存データを消す条件と、ホーム画面のウェブアプリの扱い
