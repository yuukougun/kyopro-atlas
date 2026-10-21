---
title: グラフの詳細索引
type: generated
search:
  exclude: true
---

<!-- tools/gen_site.py が生成する。手で直さない -->

# グラフの詳細索引

分野の全ページの id・URL・別名・サイン・種類・前提・節。全分野の1行の一覧と索引の版は https://yuukougun.github.io/kyopro-atlas/llms.txt にある。stub（準備中）のページは要約と前提しかなく、節の見出しもまだない。

## グラフの表現と用語（graph-basics） {#graph-basics}

- id：`graph-basics`　レベル：基礎　段階：stub　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/graph/graph-basics/
- 別名：グラフの基本、隣接リスト、隣接行列、辺リスト、次数、adjacency list、graph representation
- 種類：グラフ探索
- サイン：
    - 言い回し：グラフが N×N の 0/1 の表（隣接行列）で与えられる
    - 制約：N ≤ 2×10^5 では N^2 の隣接行列を持てない（N ≤ 2000 程度なら持てる）
- 節：
    - `graph-basics#representations` 隣接リスト・隣接行列・辺リストとアルゴリズムごとの使い分け：https://yuukougun.github.io/kyopro-atlas/graph/graph-basics/#representations
    - `graph-basics#terms` 用語（次数・パスとウォーク・単純グラフ・連結・木・DAG・二部グラフ・補グラフ）：https://yuukougun.github.io/kyopro-atlas/graph/graph-basics/#terms
    - `graph-basics#handshake` 握手補題（次数の和は 2M）：https://yuukougun.github.io/kyopro-atlas/graph/graph-basics/#handshake
    - `graph-basics#pitfalls` 落とし穴（1-indexed・無向グラフは両方向に追加・多重辺・重みの和のあふれ）：https://yuukougun.github.io/kyopro-atlas/graph/graph-basics/#pitfalls

## グラフへの帰着（graph-modeling） {#graph-modeling}

- id：`graph-modeling`　レベル：—　段階：stub　type：hub
- URL：https://yuukougun.github.io/kyopro-atlas/graph/graph-modeling/
- 別名：グラフに言い換える、モデル化、何を頂点にするか、何を辺にするか、グラフの縮約、graph modeling
- 種類：案内、グラフ探索、考察
- 前提：`graph-basics`
- 節：
    - `graph-modeling#what-to-vertex` 何を頂点にするか（物・値・座標・状態・時刻・剰余・区間の端点 → 行き先のページの表）：https://yuukougun.github.io/kyopro-atlas/graph/graph-modeling/#what-to-vertex
    - `graph-modeling#what-to-edge` 何を辺にするか（関係・操作・制約・写像）：https://yuukougun.github.io/kyopro-atlas/graph/graph-modeling/#what-to-edge
    - `graph-modeling#constraints-to-edges` 制約を辺にすると何の問題になるか（二部グラフ・閉路・差分制約）：https://yuukougun.github.io/kyopro-atlas/graph/graph-modeling/#constraints-to-edges
    - `graph-modeling#contraction` 自由に行き来できる部分を 1 点に縮約する（Union-Find・SCC・次数 2 の頂点を消す）：https://yuukougun.github.io/kyopro-atlas/graph/graph-modeling/#contraction

## 深さ優先探索（DFS）（dfs） {#dfs}

- id：`dfs`　レベル：基礎　段階：stub　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/graph/dfs/
- 別名：深さ優先探索、DFS、depth-first search、単純パスの列挙
- 種類：グラフ探索
- 前提：`graph-basics`
- サイン：
    - 言い回し：すべての単純パス・経路を数える（答えが上限を超えたら打ち切ってよい）
    - 言い回し：依存関係をたどり、必要なものを先に済ませる順に出力する
    - 制約：N ≤ 10 程度で、経路を全部列挙できる
- 節：
    - `dfs#visit-once` 一度訪れた頂点は二度と訪れない型（O(N+M)）：https://yuukougun.github.io/kyopro-atlas/graph/dfs/#visit-once
    - `dfs#backtracking` バックトラック型（帰りがけで印を外す）：https://yuukougun.github.io/kyopro-atlas/graph/dfs/#backtracking
    - `dfs#pre-post-order` 行きがけ順と帰りがけ順：https://yuukougun.github.io/kyopro-atlas/graph/dfs/#pre-post-order
    - `dfs#iterative` 非再帰の DFS と再帰の深さ：https://yuukougun.github.io/kyopro-atlas/graph/dfs/#iterative
    - `dfs#comparison` BFS・Union-Find との使い分け：https://yuukougun.github.io/kyopro-atlas/graph/dfs/#comparison

## 幅優先探索（BFS）と無重み最短路（bfs） {#bfs}

- id：`bfs`　レベル：基礎　段階：stub　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/graph/bfs/
- 別名：幅優先探索、BFS、breadth-first search、無重み最短路、多始点 BFS、最短経路の復元
- 種類：グラフ探索、最短路
- 前提：`graph-basics`、`stack-techniques`
- サイン：
    - 言い回し：最小の手数・回数を求める（1 回の移動のコストがすべて同じ）
    - 言い回し：一番近い〇〇までの距離・複数の場所から同時に広がる
    - 言い回し：最短経路を 1 つ出力する・次に進む頂点を答える
    - 制約：N, M ≤ 2×10^5、またはマスの数 H×W ≤ 10^6 程度
- 節：
    - `bfs#why-shortest` 最初に見つけた距離が最短になる理由：https://yuukougun.github.io/kyopro-atlas/graph/bfs/#why-shortest
    - `bfs#mark-on-push` 印は push のときに付ける・dist を −1 で初期化して訪問済みの印を兼ねる：https://yuukougun.github.io/kyopro-atlas/graph/bfs/#mark-on-push
    - `bfs#path-restoration` 経路復元（発見したときの親を記録して終点からたどる）：https://yuukougun.github.io/kyopro-atlas/graph/bfs/#path-restoration
    - `bfs#multi-source` 多始点 BFS（超始点から距離 0 の辺を張るのと同じ）：https://yuukougun.github.io/kyopro-atlas/graph/bfs/#multi-source
    - `bfs#weighted` 重みが 1 と 2 なら辺を割る・重み付きなら 01-BFS かダイクストラ：https://yuukougun.github.io/kyopro-atlas/graph/bfs/#weighted

## グリッドグラフ（grid-graph） {#grid-graph}

- id：`grid-graph`　レベル：基礎　段階：stub　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/graph/grid-graph/
- 別名：グリッド BFS、迷路の探索、4 近傍、8 近傍、grid graph
- 種類：グラフ探索
- 前提：`bfs`、`dfs`
- サイン：
    - 言い回し：H×W のマス目を上下左右（8 方向）に移動する・壁や障害物がある
    - 制約：H, W ≤ 2000 程度（マスの数が 4×10^6 程度まで）
    - 言い回し：H, W が巨大で、障害物の数だけが少ない
- 節：
    - `grid-graph#neighbors` 4 近傍・8 近傍と dx・dy の配列：https://yuukougun.github.io/kyopro-atlas/graph/grid-graph/#neighbors
    - `grid-graph#flatten` (i, j) を i×W+j に 1 次元化する・外周に番兵を置く：https://yuukougun.github.io/kyopro-atlas/graph/grid-graph/#flatten
    - `grid-graph#boundary-cells` 止まるマス・境界のマスの数え方：https://yuukougun.github.io/kyopro-atlas/graph/grid-graph/#boundary-cells
    - `grid-graph#checkerboard` 市松模様で二部グラフになる（フロー・マッチングへの入口）：https://yuukougun.github.io/kyopro-atlas/graph/grid-graph/#checkerboard
    - `grid-graph#obstacle-dual` 障害物どうしの 8 近傍の連結で通れるかを判定する（青）：https://yuukougun.github.io/kyopro-atlas/graph/grid-graph/#obstacle-dual

## 連結成分（connected-components） {#connected-components}

- id：`connected-components`　レベル：基礎　段階：stub　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/graph/connected-components/
- 別名：連結成分分解、連結判定、connected components
- 種類：グラフ探索、連結性・全域木
- 前提：`dfs`、`union-find`
- ACL：`dsu`
- サイン：
    - 言い回し：つながっているか・グループの数・最大のグループの大きさ
    - 言い回し：友達の友達は友達
    - 式の形：成分ごとの頂点数と辺数の関係（木か・閉路がちょうど 1 つか）で条件が決まる
    - 言い回し：点 (x, y) の集合で、同じ x・同じ y を持つ点どうしが関係する
- 節：
    - `connected-components#three-methods` DFS・BFS・Union-Find の 3 つの求め方と使い分け：https://yuukougun.github.io/kyopro-atlas/graph/connected-components/#three-methods
    - `connected-components#per-component` 成分ごとの集計（頂点数と辺数で木・なもり・それ以外を見分ける）：https://yuukougun.github.io/kyopro-atlas/graph/connected-components/#per-component
    - `connected-components#pitfalls` 孤立点・多重辺・自己ループの数え方：https://yuukougun.github.io/kyopro-atlas/graph/connected-components/#pitfalls
    - `connected-components#forest` 森の連結成分の数は N − M：https://yuukougun.github.io/kyopro-atlas/graph/connected-components/#forest
    - `connected-components#values-as-vertices` 座標や値を頂点にして成分を考える（青）：https://yuukougun.github.io/kyopro-atlas/graph/connected-components/#values-as-vertices

## 閉路の検出と復元（cycle-detection） {#cycle-detection}

- id：`cycle-detection`　レベル：基礎　段階：stub　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/graph/cycle-detection/
- 別名：閉路検出、サイクル検出、有向閉路、無向閉路、3 色の DFS、cycle detection
- 種類：グラフ探索
- 前提：`dfs`、`union-find`
- ACL：`dsu`、`scc_graph`
- サイン：
    - 言い回し：循環している・依存関係が回っている・矛盾があれば −1
    - 言い回し：閉路を 1 つ見つけて出力せよ
- 節：
    - `cycle-detection#undirected` 無向グラフ：Union-Find・親以外の訪問済みの頂点への辺（多重辺は辺の番号で除外）：https://yuukougun.github.io/kyopro-atlas/graph/cycle-detection/#undirected
    - `cycle-detection#directed` 有向グラフ：3 色の DFS（探索中の頂点への辺だけが閉路）：https://yuukougun.github.io/kyopro-atlas/graph/cycle-detection/#directed
    - `cycle-detection#kahn-leftover` Kahn 法で残る頂点（すべてが閉路上とは限らない）：https://yuukougun.github.io/kyopro-atlas/graph/cycle-detection/#kahn-leftover
    - `cycle-detection#restore` 閉路の復元（親をたどる）：https://yuukougun.github.io/kyopro-atlas/graph/cycle-detection/#restore
    - `cycle-detection#out-degree-one` 出次数 1 のグラフでは同じ頂点に 2 回来るまで進む：https://yuukougun.github.io/kyopro-atlas/graph/cycle-detection/#out-degree-one
    - `cycle-detection#vs-periodicity` シミュレーションの周期の検出（基本テクニックの章）との違い：https://yuukougun.github.io/kyopro-atlas/graph/cycle-detection/#vs-periodicity

## 二部グラフ判定（bipartite-graph） {#bipartite-graph}

- id：`bipartite-graph`　レベル：基礎　段階：stub　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/graph/bipartite-graph/
- 別名：二部グラフ、2 彩色、奇閉路、2 色の塗り分け、bipartite graph
- 種類：グラフ探索
- 前提：`dfs`、`bfs`
- ACL：`dsu`
- サイン：
    - 言い回し：2 つのグループに分ける・隣り合うものは異なる色
    - 言い回し：X_i と Y_i は異なる値、という条件が M 個ある
    - 言い回し：奇数長の閉路があるか
- 節：
    - `bipartite-graph#coloring` BFS・DFS で塗る（非連結なら成分ごとに）：https://yuukougun.github.io/kyopro-atlas/graph/bipartite-graph/#coloring
    - `bipartite-graph#odd-cycle` 二部グラフでないことと奇閉路があることは同じ：https://yuukougun.github.io/kyopro-atlas/graph/bipartite-graph/#odd-cycle
    - `bipartite-graph#count-by-color` 成分ごとの色の数を使う数え上げ：https://yuukougun.github.io/kyopro-atlas/graph/bipartite-graph/#count-by-color
    - `bipartite-graph#union-find` Union-Find（頂点を 2 倍にする・偶奇を持つ）で判定する：https://yuukougun.github.io/kyopro-atlas/graph/bipartite-graph/#union-find
    - `bipartite-graph#always-bipartite` 木・4 近傍のグリッドは必ず二部グラフ：https://yuukougun.github.io/kyopro-atlas/graph/bipartite-graph/#always-bipartite

## 小さいグラフの全探索（small-graph-brute-force） {#small-graph-brute-force}

- id：`small-graph-brute-force`　レベル：基礎　段階：stub　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/graph/small-graph-brute-force/
- 別名：グラフ同型、全域木の全列挙、彩色の全探索、頂点の対応の全探索、graph isomorphism
- 種類：全探索、グラフ探索
- 前提：`dfs`、`bit-full-search`
- サイン：
    - 制約：N ≤ 8〜10 で頂点の対応や辺の部分集合を全部試せる
    - 言い回し：頂点の番号を付け替えて同じ形にできるか
    - 言い回し：隣り合う頂点が異なる色になる 3 色の塗り方の数
- 節：
    - `small-graph-brute-force#isomorphism` 頂点の対応の全探索（同型の判定・同型にするコスト）：https://yuukougun.github.io/kyopro-atlas/graph/small-graph-brute-force/#isomorphism
    - `small-graph-brute-force#edge-subsets` 辺の部分集合の全探索（全域木の全列挙）：https://yuukougun.github.io/kyopro-atlas/graph/small-graph-brute-force/#edge-subsets
    - `small-graph-brute-force#coloring` 彩色は成分ごとに DFS で塗って探索を絞る（青）：https://yuukougun.github.io/kyopro-atlas/graph/small-graph-brute-force/#coloring

## 彩色数・最大独立集合・最大クリーク（chromatic-number） {#chromatic-number}

- id：`chromatic-number`　レベル：発展　段階：stub　type：overview
- URL：https://yuukougun.github.io/kyopro-atlas/graph/chromatic-number/
- 別名：彩色数、頂点彩色、最大クリーク、一般グラフの最大独立集合、chromatic number、maximum independent set
- 種類：DP、数え上げ
- 前提：`bit-dp`、`inclusion-exclusion`
- サイン：
    - 制約：N ≤ 20〜40 の一般グラフで、独立集合・彩色・クリークを求める
- 節：
    - `chromatic-number#chromatic-number` 彩色数（包除原理で O(2^N N)）：https://yuukougun.github.io/kyopro-atlas/graph/chromatic-number/#chromatic-number
    - `chromatic-number#independent-set` 最大独立集合（分枝・半分全列挙）：https://yuukougun.github.io/kyopro-atlas/graph/chromatic-number/#independent-set
    - `chromatic-number#bipartite-case` 二部グラフなら König の定理：https://yuukougun.github.io/kyopro-atlas/graph/chromatic-number/#bipartite-case

## ダイクストラ法（dijkstra） {#dijkstra}

- id：`dijkstra`　レベル：基礎　段階：stub　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/graph/dijkstra/
- 別名：ダイクストラ、Dijkstra、Dijkstra's algorithm、経由点の最短路、両端からのダイクストラ、逆向きのグラフ、最短閉路、ポテンシャルで負辺を消す、Johnson のアイデア
- 種類：最短路
- 前提：`bfs`
- サイン：
    - 言い回し：非負の重み付きグラフの最短距離・最小コスト（頂点にもコストがある）
    - 制約：N, M ≤ 2×10^5 で辺の重みが非負
    - 言い回し：頂点 k を経由する最短路をすべての k について・行きと帰り
    - 言い回し：負の辺の重みが「高さの差」の形をしている
- 節：
    - `dijkstra#why-correct` 取り出した頂点の距離が確定する理由：https://yuukougun.github.io/kyopro-atlas/graph/dijkstra/#why-correct
    - `dijkstra#skip-stale` 古い組を読み飛ばす・priority_queue を最小ヒープにする：https://yuukougun.github.io/kyopro-atlas/graph/dijkstra/#skip-stale
    - `dijkstra#vertex-weights` 頂点の重みを辺に足す・経路復元は BFS と同じ：https://yuukougun.github.io/kyopro-atlas/graph/dijkstra/#vertex-weights
    - `dijkstra#dense` 密グラフの O(N^2) 版：https://yuukougun.github.io/kyopro-atlas/graph/dijkstra/#dense
    - `dijkstra#negative-edges` 負辺で壊れる例：https://yuukougun.github.io/kyopro-atlas/graph/dijkstra/#negative-edges
    - `dijkstra#shortest-cycle` 最短閉路（ある頂点を含む閉路の最小の長さ）：https://yuukougun.github.io/kyopro-atlas/graph/dijkstra/#shortest-cycle
    - `dijkstra#reverse-graph` 逆向きのグラフと両端からの最短路（水）：https://yuukougun.github.io/kyopro-atlas/graph/dijkstra/#reverse-graph
    - `dijkstra#potential` ポテンシャルで負辺を消す（Johnson のアイデア）（水）：https://yuukougun.github.io/kyopro-atlas/graph/dijkstra/#potential

## 01-BFS（zero-one-bfs） {#zero-one-bfs}

- id：`zero-one-bfs`　レベル：水　段階：stub　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/graph/zero-one-bfs/
- 別名：0-1 BFS、deque BFS
- 種類：最短路
- 前提：`dijkstra`
- サイン：
    - 言い回し：壁を壊す回数・向きを変える回数・ワープの回数を最小化する
    - 言い回し：1 回の移動のコストが 0 か 1
    - 式の形：言い換えると、辺の重みが 0 と 1 の 2 種類だけのグラフの最短路になる
- 節：
    - `zero-one-bfs#deque-invariant` deque の中の距離が 2 種類に保たれる理由：https://yuukougun.github.io/kyopro-atlas/graph/zero-one-bfs/#deque-invariant
    - `zero-one-bfs#no-early-fix` 初めて見つけたときに確定させてはいけない：https://yuukougun.github.io/kyopro-atlas/graph/zero-one-bfs/#no-early-fix
    - `zero-one-bfs#direction-state` 向きを状態に持つ（頂点数が 4 倍になる）：https://yuukougun.github.io/kyopro-atlas/graph/zero-one-bfs/#direction-state
    - `zero-one-bfs#weights-012` 重みが 0, 1, 2 ならどうするか：https://yuukougun.github.io/kyopro-atlas/graph/zero-one-bfs/#weights-012

## ワーシャルフロイド法（warshall-floyd） {#warshall-floyd}

- id：`warshall-floyd`　レベル：水　段階：stub　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/graph/warshall-floyd/
- 別名：ワーシャルフロイド、Floyd-Warshall、全点対最短路、all-pairs shortest paths
- 種類：最短路、DP
- 前提：`dijkstra`、`dp-basics`
- サイン：
    - 制約：N ≤ 400 程度で全点対の距離が要る
    - 言い回し：辺を 1 本ずつ追加（削除）するたびに、距離についての値を答える
    - 言い回し：訪れる地点の順番を全部試す（地点間の距離が要る）
- 節：
    - `warshall-floyd#k-outer` k を一番外のループにする理由：https://yuukougun.github.io/kyopro-atlas/graph/warshall-floyd/#k-outer
    - `warshall-floyd#init` 初期化（d\[i][i] = 0・多重辺・INF のあふれ）と負閉路の判定：https://yuukougun.github.io/kyopro-atlas/graph/warshall-floyd/#init
    - `warshall-floyd#add-edge` 辺の追加を O(N^2) で反映する（削除は逆順の追加に）：https://yuukougun.github.io/kyopro-atlas/graph/warshall-floyd/#add-edge
    - `warshall-floyd#with-enumeration` 距離表を作ってから順列全探索・bitDP：https://yuukougun.github.io/kyopro-atlas/graph/warshall-floyd/#with-enumeration
    - `warshall-floyd#redundant-edges` 迂回できる辺は不要（青）：https://yuukougun.github.io/kyopro-atlas/graph/warshall-floyd/#redundant-edges

## ベルマンフォード法（bellman-ford） {#bellman-ford}

- id：`bellman-ford`　レベル：青　段階：stub　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/graph/bellman-ford/
- 別名：ベルマンフォード、Bellman-Ford、負閉路検出、SPFA、負辺のある最短路
- 種類：最短路
- 前提：`dijkstra`
- サイン：
    - 言い回し：負の重みの辺がある・得点を最大化する（符号を反転すると負辺になる）
    - 言い回し：いくらでも大きくできるなら inf と出力する
    - 制約：N, M ≤ 数千（O(NM) が間に合う）
- 節：
    - `bellman-ford#why-n-minus-1` N−1 回で十分な理由：https://yuukougun.github.io/kyopro-atlas/graph/bellman-ford/#why-n-minus-1
    - `bellman-ford#relevant-cycles` 答えに影響する負閉路だけを判定する（到達可能性で絞る・−∞ を伝える）：https://yuukougun.github.io/kyopro-atlas/graph/bellman-ford/#relevant-cycles
    - `bellman-ford#longest-path` 最長路は符号を反転する：https://yuukougun.github.io/kyopro-atlas/graph/bellman-ford/#longest-path
    - `bellman-ford#spfa` SPFA の注意（最悪の計算量は同じ）：https://yuukougun.github.io/kyopro-atlas/graph/bellman-ford/#spfa
    - `bellman-ford#vs-potential` 負辺があってもダイクストラで済む場合との見分け（ポテンシャル）：https://yuukougun.github.io/kyopro-atlas/graph/bellman-ford/#vs-potential

## 最短路 DAG（shortest-path-dag） {#shortest-path-dag}

- id：`shortest-path-dag`　レベル：水　段階：stub　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/graph/shortest-path-dag/
- 別名：最短路木、最短経路の数え上げ、最短路に必ず使われる辺、shortest path DAG
- 種類：最短路、DP
- 前提：`dijkstra`、`dp-dag`
- サイン：
    - 言い回し：最短経路の本数を数える
    - 言い回し：この辺を通らなくても最短距離は変わらないか・最短路に使われない辺
    - 言い回し：始点からの最短距離を保ったまま辺を減らし、全域木を出力する
- 節：
    - `shortest-path-dag#build` 最短路 DAG の作り方と性質（重み 0 の辺に注意）：https://yuukougun.github.io/kyopro-atlas/graph/shortest-path-dag/#build
    - `shortest-path-dag#count-paths` 最短路の本数の DP：https://yuukougun.github.io/kyopro-atlas/graph/shortest-path-dag/#count-paths
    - `shortest-path-dag#shortest-path-tree` 最短路木（最小全域木との違い）：https://yuukougun.github.io/kyopro-atlas/graph/shortest-path-dag/#shortest-path-tree
    - `shortest-path-dag#edge-on-path` 辺が s-t 最短路に乗る条件（両端からの距離）：https://yuukougun.github.io/kyopro-atlas/graph/shortest-path-dag/#edge-on-path
    - `shortest-path-dag#edge-removal` 辺を消すと距離が変わるか（黄）：https://yuukougun.github.io/kyopro-atlas/graph/shortest-path-dag/#edge-removal

## 状態を頂点にする（extended-dijkstra） {#extended-dijkstra}

- id：`extended-dijkstra`　レベル：水　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/graph/extended-dijkstra/
- 別名：状態空間の探索、状態空間 BFS、拡張ダイクストラ、頂点倍化、頂点倍加、レイヤー化グラフ、超頂点、仮想頂点、補助頂点、盤面の BFS、state-space search、layered graph、super vertex
- 種類：最短路、グラフ探索
- 前提：`dijkstra`
- サイン：
    - 言い回し：K 回まで無料・スキップできる、手持ちのお金・燃料・体力がある
    - 言い回し：向き・直前の移動・歩数の偶奇や mod で次の移動が変わる
    - 言い回し：同じグループ（色・文字・集合）の中ならどこへでも移動できる
    - 言い回し：盤面・配置を操作して目標の形にする最小回数・2 人（2 つの駒）が同時に動く
    - 制約：状態数が 10&#94;6〜10&#94;7 程度に収まる（9! = 362880、60&#94;4 ≈ 1.3×10&#94;7）
    - 式の形：距離を dist\[頂点][向き・残り回数・偶奇] のように 2 次元以上で持ちたくなる
- 節：
    - `extended-dijkstra#choose-state` 状態として持つべき情報を決める：https://yuukougun.github.io/kyopro-atlas/graph/extended-dijkstra/#choose-state
    - `extended-dijkstra#state-count` 状態数と遷移数の見積もり・状態を整数に詰める（配列で引くか map で持つか）：https://yuukougun.github.io/kyopro-atlas/graph/extended-dijkstra/#state-count
    - `extended-dijkstra#pair-state` 2 つの位置の組を状態にする：https://yuukougun.github.io/kyopro-atlas/graph/extended-dijkstra/#pair-state
    - `extended-dijkstra#layered-graph` 頂点倍化（層を作り、層の間の辺でコストを表す）：https://yuukougun.github.io/kyopro-atlas/graph/extended-dijkstra/#layered-graph
    - `extended-dijkstra#parity-mod-direction` 偶奇・mod・向きを持つ：https://yuukougun.github.io/kyopro-atlas/graph/extended-dijkstra/#parity-mod-direction
    - `extended-dijkstra#super-vertex` 超頂点・補助頂点で辺の数を減らす：https://yuukougun.github.io/kyopro-atlas/graph/extended-dijkstra/#super-vertex
    - `extended-dijkstra#super-vertex-offset` 超頂点で距離がずれる場合の補正（2 で割る・1 を引く）：https://yuukougun.github.io/kyopro-atlas/graph/extended-dijkstra/#super-vertex-offset
    - `extended-dijkstra#key-points` 状態が多すぎるときは重要な点だけのグラフに作り直す：https://yuukougun.github.io/kyopro-atlas/graph/extended-dijkstra/#key-points
    - `extended-dijkstra#resource-state` 資源を状態に持ち、上限で打ち切る（青）：https://yuukougun.github.io/kyopro-atlas/graph/extended-dijkstra/#resource-state
    - `extended-dijkstra#visited-set` 訪問した集合を持つ（bitDP へのつなぎ）（青）：https://yuukougun.github.io/kyopro-atlas/graph/extended-dijkstra/#visited-set
    - `extended-dijkstra#two-ends` 両端から伸ばす（回文の最短路）（青）：https://yuukougun.github.io/kyopro-atlas/graph/extended-dijkstra/#two-ends

## 時刻で変わる辺の最短路（time-dependent-dijkstra） {#time-dependent-dijkstra}

- id：`time-dependent-dijkstra`　レベル：水　段階：stub　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/graph/time-dependent-dijkstra/
- 別名：時刻依存の最短路、待機、最終電車、出発時刻、time-dependent shortest path
- 種類：最短路
- 前提：`dijkstra`
- サイン：
    - 言い回し：決まった時刻にしか出発できない・待つことができる
    - 言い回し：出発時刻によって所要時間が変わる
    - 言い回し：終点に間に合う最も遅い出発時刻
- 節：
    - `time-dependent-dijkstra#fifo` 早く着いて損をしない性質（FIFO 性）：https://yuukougun.github.io/kyopro-atlas/graph/time-dependent-dijkstra/#fifo
    - `time-dependent-dijkstra#wait` 次の出発時刻まで待つ遷移：https://yuukougun.github.io/kyopro-atlas/graph/time-dependent-dijkstra/#wait
    - `time-dependent-dijkstra#latest-departure` 最終電車型：終点から逆向きに最も遅い時刻を確定させる：https://yuukougun.github.io/kyopro-atlas/graph/time-dependent-dijkstra/#latest-departure
    - `time-dependent-dijkstra#optimal-departure` 最適な出発時刻を計算してから進む（青）：https://yuukougun.github.io/kyopro-atlas/graph/time-dependent-dijkstra/#optimal-departure

## 差分制約（牛ゲー）（difference-constraints） {#difference-constraints}

- id：`difference-constraints`　レベル：青　段階：stub　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/graph/difference-constraints/
- 別名：牛ゲー、差分制約系、不等式を辺にする、difference constraints
- 種類：最短路
- 前提：`bellman-ford`、`prefix-sum`
- サイン：
    - 言い回し：x_j − x_i ≤ c の形の条件の下で、ある変数を最大化（最小化）する
    - 言い回し：区間の和が S 以上・以下という条件が並ぶ
    - 言い回し：位置の差の情報が矛盾しないか
    - 式の形：条件を整理すると x_v ≤ x_u + c の形の不等式の集まりになる
- 節：
    - `difference-constraints#direction` 不等式を辺にする向き：https://yuukougun.github.io/kyopro-atlas/graph/difference-constraints/#direction
    - `difference-constraints#why-maximum` 最短距離が最大の解になる理由：https://yuukougun.github.io/kyopro-atlas/graph/difference-constraints/#why-maximum
    - `difference-constraints#encodings` 等式・正値・区間の和の条件の書き方：https://yuukougun.github.io/kyopro-atlas/graph/difference-constraints/#encodings
    - `difference-constraints#which-algorithm` 負辺があればベルマンフォード、なければダイクストラ：https://yuukougun.github.io/kyopro-atlas/graph/difference-constraints/#which-algorithm
    - `difference-constraints#consistency` 整合性の判定だけなら重み付き Union-Find（データ構造の章）：https://yuukougun.github.io/kyopro-atlas/graph/difference-constraints/#consistency

## 補グラフ上の BFS（complement-graph-bfs） {#complement-graph-bfs}

- id：`complement-graph-bfs`　レベル：黄　段階：stub　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/graph/complement-graph-bfs/
- 別名：補グラフ、未訪問頂点の集合、complement graph
- 種類：グラフ探索
- 前提：`bfs`、`ordered-set`
- サイン：
    - 言い回し：完全グラフから M 本の辺を取り除いたグラフ・辺が「ない」組が与えられる
    - 制約：N ≤ 2×10^5 で、補グラフの辺は N^2 本近くあり列挙できない
- 節：
    - `complement-graph-bfs#take-unvisited` 未訪問頂点の集合から取り出す：https://yuukougun.github.io/kyopro-atlas/graph/complement-graph-bfs/#take-unvisited
    - `complement-graph-bfs#complexity` 各頂点が 1 回しか取り出されない理由（O(N + M)）：https://yuukougun.github.io/kyopro-atlas/graph/complement-graph-bfs/#complexity
    - `complement-graph-bfs#count-by-layer` 層ごとに最短路の本数を数える：https://yuukougun.github.io/kyopro-atlas/graph/complement-graph-bfs/#count-by-layer

## 剰余を頂点にする最短路（modular-shortest-path） {#modular-shortest-path}

- id：`modular-shortest-path`　レベル：発展　段階：stub　type：overview
- URL：https://yuukougun.github.io/kyopro-atlas/graph/modular-shortest-path/
- 別名：同余最短路、剰余グラフ、mod を頂点に
- 種類：最短路、整数論
- 前提：`zero-one-bfs`、`extended-dijkstra`
- サイン：
    - 言い回し：K の倍数のうち桁和などが最小のもの
    - 言い回し：いくつかの数の和で作れる数の集合（硬貨の組合せ）
    - 制約：K が 10&#94;5〜10&#94;6 程度
- 節：
    - `modular-shortest-path#residue-vertices` 余りを頂点、操作を辺にする：https://yuukougun.github.io/kyopro-atlas/graph/modular-shortest-path/#residue-vertices
    - `modular-shortest-path#congruence` 同余最短路（最小の数で割った余りごとの最小値）：https://yuukougun.github.io/kyopro-atlas/graph/modular-shortest-path/#congruence

## 区間に辺を張る（segment-tree-graph） {#segment-tree-graph}

- id：`segment-tree-graph`　レベル：発展　段階：stub　type：overview
- URL：https://yuukougun.github.io/kyopro-atlas/graph/segment-tree-graph/
- 別名：区間に辺を張るテク、セグ木グラフ、セグメント木の形の補助頂点、segment tree graph
- 種類：最短路、データ構造
- 前提：`extended-dijkstra`、`segment-tree`
- サイン：
    - 言い回し：頂点から区間内の全頂点へ移動できる・区間から区間へ移動できる
- 節：
    - `segment-tree-graph#two-trees` 下向きの木と上向きの木（コスト 0 の辺）：https://yuukougun.github.io/kyopro-atlas/graph/segment-tree-graph/#two-trees
    - `segment-tree-graph#cover` 区間を O(log N) 個のノードで覆う：https://yuukougun.github.io/kyopro-atlas/graph/segment-tree-graph/#cover

## K 番目の最短路（k-shortest-paths） {#k-shortest-paths}

- id：`k-shortest-paths`　レベル：発展　段階：stub　type：overview
- URL：https://yuukougun.github.io/kyopro-atlas/graph/k-shortest-paths/
- 別名：k shortest paths、K 番目に短い経路、Eppstein、Yen
- 種類：最短路
- 前提：`dijkstra`
- サイン：
    - 言い回し：K 番目に短い経路・歩道の長さ
- 節：
    - `k-shortest-paths#k-times` 各頂点を K 回まで取り出すダイクストラ：https://yuukougun.github.io/kyopro-atlas/graph/k-shortest-paths/#k-times
    - `k-shortest-paths#yen-eppstein` 単純パス（Yen）と歩道（Eppstein）：https://yuukougun.github.io/kyopro-atlas/graph/k-shortest-paths/#yen-eppstein

## 最小シュタイナー木（steiner-tree） {#steiner-tree}

- id：`steiner-tree`　レベル：発展　段階：stub　type：overview
- URL：https://yuukougun.github.io/kyopro-atlas/graph/steiner-tree/
- 別名：シュタイナー木、Steiner tree、Dreyfus-Wagner
- 種類：最短路、DP
- 前提：`dijkstra`、`subset-enumeration-dp`
- サイン：
    - 制約：指定した K 点（K ≤ 10 程度）をすべて連結にする最小コスト
- 節：
    - `steiner-tree#state` dp\[S][v] の定義：https://yuukougun.github.io/kyopro-atlas/graph/steiner-tree/#state
    - `steiner-tree#merge` 部分集合を 2 つに分けて合わせる遷移：https://yuukougun.github.io/kyopro-atlas/graph/steiner-tree/#merge
    - `steiner-tree#dijkstra-step` ダイクストラで v を動かす遷移：https://yuukougun.github.io/kyopro-atlas/graph/steiner-tree/#dijkstra-step
    - `steiner-tree#on-tree` 木の上なら易しい（木の章の「指定頂点を結ぶ最小の部分木」）：https://yuukougun.github.io/kyopro-atlas/graph/steiner-tree/#on-tree

## トポロジカルソート（topological-sort） {#topological-sort}

- id：`topological-sort`　レベル：基礎　段階：stub　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/graph/topological-sort/
- 別名：トポロジカル順序、Kahn 法、入次数、DAG、topological sort
- 種類：グラフ探索
- 前提：`dfs`、`bfs`
- ACL：`scc_graph`
- サイン：
    - 言い回し：a は b より前・依存関係・前提条件
    - 言い回し：条件を満たす辞書順最小の順序・順序が一意か
    - 言い回し：矛盾（閉路）があれば −1
- 節：
    - `topological-sort#kahn-dfs` Kahn 法と DFS の帰りがけ順：https://yuukougun.github.io/kyopro-atlas/graph/topological-sort/#kahn-dfs
    - `topological-sort#lexicographic` 辞書順最小は優先度付きキューの Kahn 法：https://yuukougun.github.io/kyopro-atlas/graph/topological-sort/#lexicographic
    - `topological-sort#unique` 順序が一意かの判定：https://yuukougun.github.io/kyopro-atlas/graph/topological-sort/#unique
    - `topological-sort#peel-sinks` 出次数 0 の頂点から逆向きに剥がす：https://yuukougun.github.io/kyopro-atlas/graph/topological-sort/#peel-sinks
    - `topological-sort#to-dag-dp` DAG 上の DP へ（DP の章）：https://yuukougun.github.io/kyopro-atlas/graph/topological-sort/#to-dag-dp
    - `topological-sort#acl` ACL の scc_graph を使う（DAG なら scc() の順がトポロジカル順）：https://yuukougun.github.io/kyopro-atlas/graph/topological-sort/#acl

## 強連結成分分解（SCC）（scc） {#scc}

- id：`scc`　レベル：水　段階：stub　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/graph/scc/
- 別名：強連結成分、SCC、Kosaraju、Tarjan、strongly connected components
- 種類：グラフ探索
- 前提：`topological-sort`
- ACL：`scc_graph`
- サイン：
    - 言い回し：互いに行き来できる頂点の組・グループ
    - 言い回し：何度でもくり返せる（閉路の中にいる）
    - 式の形：閉路を 1 点に縮めた DAG の上で DP・数え上げをしたくなる
- 節：
    - `scc#condensation` 縮約したグラフが DAG になる理由：https://yuukougun.github.io/kyopro-atlas/graph/scc/#condensation
    - `scc#algorithms` Kosaraju と Tarjan：https://yuukougun.github.io/kyopro-atlas/graph/scc/#algorithms
    - `scc#acl` ACL の scc_graph（トポロジカル順の成分のリスト）：https://yuukougun.github.io/kyopro-atlas/graph/scc/#acl
    - `scc#on-cycle` 閉路に含まれる頂点（自己ループに注意）：https://yuukougun.github.io/kyopro-atlas/graph/scc/#on-cycle
    - `scc#dp-on-dag` 縮約した DAG の上で DP する：https://yuukougun.github.io/kyopro-atlas/graph/scc/#dp-on-dag

## Functional graph（出次数 1 のグラフ）（functional-graph） {#functional-graph}

- id：`functional-graph`　レベル：水　段階：stub　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/graph/functional-graph/
- 別名：関数グラフ、ρ 形、rho 形、successor graph
- 種類：グラフ探索
- 前提：`cycle-detection`
- ACL：`scc_graph`
- サイン：
    - 言い回し：各 i から A_i へ移動する
    - 制約：K 回（K ≤ 10^18）移動した後の位置
    - 言い回し：嫌いな相手・行き先が 1 人（1 つ）ずつ決まっている
    - 式の形：遷移が x → f(x) の写像 1 つで決まる
- 節：
    - `functional-graph#one-cycle` 各成分に閉路がちょうど 1 つある理由：https://yuukougun.github.io/kyopro-atlas/graph/functional-graph/#one-cycle
    - `functional-graph#k-steps` K 回後の位置（しっぽと周回に分ける・ダブリング）：https://yuukougun.github.io/kyopro-atlas/graph/functional-graph/#k-steps
    - `functional-graph#on-cycle` 全頂点について閉路上かを求める（入次数 0 から剥がす・SCC）：https://yuukougun.github.io/kyopro-atlas/graph/functional-graph/#on-cycle
    - `functional-graph#per-cycle` 閉路ごとの集計・到達できる頂点の数：https://yuukougun.github.io/kyopro-atlas/graph/functional-graph/#per-cycle
    - `functional-graph#permutation` 置換は閉路の集まり（巡回分解は数え上げの章）：https://yuukougun.github.io/kyopro-atlas/graph/functional-graph/#permutation

## なもりグラフ（namori-graph） {#namori-graph}

- id：`namori-graph`　レベル：水　段階：stub　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/graph/namori-graph/
- 別名：なもり、unicyclic graph、pseudotree、閉路が 1 つのグラフ、木に辺を 1 本足したグラフ、N 頂点 N 辺の連結グラフ
- 種類：グラフ探索、木
- 前提：`connected-components`、`cycle-detection`、`tree-basics`
- ACL：`dsu`
- サイン：
    - 言い回し：N 頂点 N 辺の連結グラフ・木に辺を 1 本足したグラフ
    - 言い回し：2 頂点間の単純パスが一意か
- 節：
    - `namori-graph#one-cycle` 閉路がちょうど 1 つある理由：https://yuukougun.github.io/kyopro-atlas/graph/namori-graph/#one-cycle
    - `namori-graph#peel-leaves` 次数 1 の頂点を削って閉路を求める（Union-Find でも）：https://yuukougun.github.io/kyopro-atlas/graph/namori-graph/#peel-leaves
    - `namori-graph#hanging-trees` 閉路の頂点ごとにぶら下がる木に分ける：https://yuukougun.github.io/kyopro-atlas/graph/namori-graph/#hanging-trees
    - `namori-graph#unique-path` 単純パスが一意になる条件：https://yuukougun.github.io/kyopro-atlas/graph/namori-graph/#unique-path
    - `namori-graph#directed-version` 有向版は Functional graph：https://yuukougun.github.io/kyopro-atlas/graph/namori-graph/#directed-version

## 2-SAT（two-sat） {#two-sat}

- id：`two-sat`　レベル：発展　段階：stub　type：overview
- URL：https://yuukougun.github.io/kyopro-atlas/graph/two-sat/
- 別名：2SAT、充足可能性、含意グラフ、2-satisfiability
- 種類：グラフ探索
- 前提：`scc`
- ACL：`two_sat`
- サイン：
    - 言い回し：各要素が 2 択で「この 2 つは同時に選べない」「少なくともどちらか一方」
    - 言い回し：条件を満たす 2 択の割当があるか、あれば 1 つ出力する
    - 式の形：条件がすべて (x_i ∨ x_j) の形（2 つのリテラルの OR）に書ける
- 節：
    - `two-sat#implication` 節を含意の辺 ¬a→b・¬b→a に直す：https://yuukougun.github.io/kyopro-atlas/graph/two-sat/#implication
    - `two-sat#unsatisfiable` x と ¬x が同じ SCC なら充足不能・答えの復元：https://yuukougun.github.io/kyopro-atlas/graph/two-sat/#unsatisfiable
    - `two-sat#cheatsheet` モデル化の早見表（同時に選べない・どちらかは必ず・a なら b）：https://yuukougun.github.io/kyopro-atlas/graph/two-sat/#cheatsheet
    - `two-sat#at-most-one` 「高々 1 つ」を補助変数で O(K) 本の節にする：https://yuukougun.github.io/kyopro-atlas/graph/two-sat/#at-most-one
    - `two-sat#acl` ACL では（two_sat の囲み）：https://yuukougun.github.io/kyopro-atlas/graph/two-sat/#acl

## Union-Find で連結性を扱う（union-find-connectivity） {#union-find-connectivity}

- id：`union-find-connectivity`　レベル：水　段階：stub　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/graph/union-find-connectivity/
- 別名：逆順 Union-Find、削除を逆順の追加にする、辺の削除を逆から、オフラインの連結判定、offline connectivity
- 種類：連結性・全域木、クエリ処理の工夫
- 前提：`connected-components`
- ACL：`dsu`
- サイン：
    - 言い回し：辺（頂点）を順に削除し、そのつど連結成分の数・大きさを答える（橋が崩落する・停電）
    - 言い回し：重さ・高さ・年などの制限を満たす辺だけで行けるかを多数答える
    - 言い回し：答えを決め打つと、つながっているかどうかで判定できる
- 節：
    - `union-find-connectivity#reverse-deletion` 削除を逆順の追加にする（答えは逆順に記録して反転する）：https://yuukougun.github.io/kyopro-atlas/graph/union-find-connectivity/#reverse-deletion
    - `union-find-connectivity#threshold` しきい値の順に辺を足してクエリに答える（オフライン）：https://yuukougun.github.io/kyopro-atlas/graph/union-find-connectivity/#threshold
    - `union-find-connectivity#super-vertex` 超頂点と組み合わせる：https://yuukougun.github.io/kyopro-atlas/graph/union-find-connectivity/#super-vertex
    - `union-find-connectivity#mixed-updates` 辺の追加と削除が混ざるとき（ロールバック Union-Find・オフライン動的連結性へ）：https://yuukougun.github.io/kyopro-atlas/graph/union-find-connectivity/#mixed-updates
    - `union-find-connectivity#binary-search` 二分探索と連結判定の組合せ（青）：https://yuukougun.github.io/kyopro-atlas/graph/union-find-connectivity/#binary-search

## 最小全域木（minimum-spanning-tree） {#minimum-spanning-tree}

- id：`minimum-spanning-tree`　レベル：水　段階：stub　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/graph/minimum-spanning-tree/
- 別名：MST、クラスカル法、プリム法、Kruskal、Prim、最大全域木、minimum spanning tree
- 種類：連結性・全域木、貪欲
- 前提：`union-find`、`sorting-techniques`
- ACL：`dsu`
- サイン：
    - 言い回し：すべての頂点をつなぐ最小コスト
    - 言い回し：不要な辺を取り除いて報酬を最大にする
    - 制約：完全グラフで N ≤ 2×10^5（辺が N^2 本あり、候補の辺を減らす必要がある）
    - 言い回し：この辺は最小全域木に入るか
- 節：
    - `minimum-spanning-tree#kruskal-prim` Kruskal 法と Prim 法（密なら O(N^2) の Prim）：https://yuukougun.github.io/kyopro-atlas/graph/minimum-spanning-tree/#kruskal-prim
    - `minimum-spanning-tree#why-correct` 正しさの理由（カット性質・閉路性質）：https://yuukougun.github.io/kyopro-atlas/graph/minimum-spanning-tree/#why-correct
    - `minimum-spanning-tree#maximum` 最大全域木：https://yuukougun.github.io/kyopro-atlas/graph/minimum-spanning-tree/#maximum
    - `minimum-spanning-tree#query-edges` クエリの辺が最小全域木に入るか（まとめて重み順に処理する）：https://yuukougun.github.io/kyopro-atlas/graph/minimum-spanning-tree/#query-edges
    - `minimum-spanning-tree#reduce-candidates` 辺の候補を減らす（ソートした隣どうし・約数で絞る）：https://yuukougun.github.io/kyopro-atlas/graph/minimum-spanning-tree/#reduce-candidates
    - `minimum-spanning-tree#modeling` 操作を頂点にする・区間を辺にする（青）：https://yuukougun.github.io/kyopro-atlas/graph/minimum-spanning-tree/#modeling
    - `minimum-spanning-tree#few-weights` 辺の重みの種類が少ないとき（青）：https://yuukougun.github.io/kyopro-atlas/graph/minimum-spanning-tree/#few-weights

## 最小ボトルネック路（bottleneck-path） {#bottleneck-path}

- id：`bottleneck-path`　レベル：青　段階：stub　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/graph/bottleneck-path/
- 別名：minimax 経路、ボトルネック、経路上の最大の辺の最小化、bottleneck path
- 種類：連結性・全域木
- 前提：`minimum-spanning-tree`、`union-find-connectivity`
- ACL：`dsu`
- サイン：
    - 言い回し：経路上の最大の辺（最小の頂点）を最小化（最大化）する
    - 言い回し：重さ・高さの制限以下で行けるか
    - 言い回し：しきい値を上げていくと連結になる時刻
- 節：
    - `bottleneck-path#why-mst` 最小全域木の上の経路がボトルネック最小になる理由（カット性質）：https://yuukougun.github.io/kyopro-atlas/graph/bottleneck-path/#why-mst
    - `bottleneck-path#kruskal-order` Kruskal の順に成分を併合しながら答える：https://yuukougun.github.io/kyopro-atlas/graph/bottleneck-path/#kruskal-order
    - `bottleneck-path#many-queries` 多数の 2 点の質問：成分にクエリを持たせて小さい方から移す（黄）：https://yuukougun.github.io/kyopro-atlas/graph/bottleneck-path/#many-queries
    - `bottleneck-path#reconstruction-tree` 併合過程の木（Kruskal 再構築木）でオンラインに答える（木の章へ）（発展）：https://yuukougun.github.io/kyopro-atlas/graph/bottleneck-path/#reconstruction-tree

## 橋・関節点・二重連結成分（lowlink） {#lowlink}

- id：`lowlink`　レベル：黄　段階：stub　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/graph/lowlink/
- 別名：lowlink、橋、関節点、二重辺連結成分、二重頂点連結成分、ブロックカット木、ord と low、bridge、articulation point、biconnected components、block-cut tree
- 種類：連結性・全域木、グラフ探索
- 前提：`dfs`
- サイン：
    - 言い回し：その辺（頂点）を取り除くと非連結になるか
    - 言い回し：すべての辺（頂点）について、取り除いたときの連結成分の数を求める
    - 制約：N, M ≤ 2×10^5 で、辺を 1 本ずつ除いて調べる O(M(N+M)) は間に合わない
- 節：
    - `lowlink#ord-low` ord と low の定義と求め方：https://yuukougun.github.io/kyopro-atlas/graph/lowlink/#ord-low
    - `lowlink#conditions` 橋の条件 low[c] > ord[p] と関節点の条件（根は子の数で判定）：https://yuukougun.github.io/kyopro-atlas/graph/lowlink/#conditions
    - `lowlink#multi-edges` 多重辺は辺の番号で親を除外する：https://yuukougun.github.io/kyopro-atlas/graph/lowlink/#multi-edges
    - `lowlink#two-edge-connected` 二重辺連結成分（橋で分けて縮約すると木になる）：https://yuukougun.github.io/kyopro-atlas/graph/lowlink/#two-edge-connected
    - `lowlink#vs-scc` 有向グラフの SCC（同じ ord・low の考え方）との対比：https://yuukougun.github.io/kyopro-atlas/graph/lowlink/#vs-scc
    - `lowlink#block-cut-tree` 二重頂点連結成分とブロックカット木（発展）：https://yuukougun.github.io/kyopro-atlas/graph/lowlink/#block-cut-tree

## 辺の追加と削除が混ざる連結性（offline-dynamic-connectivity） {#offline-dynamic-connectivity}

- id：`offline-dynamic-connectivity`　レベル：発展　段階：stub　type：overview
- URL：https://yuukougun.github.io/kyopro-atlas/graph/offline-dynamic-connectivity/
- 別名：Offline Dynamic Connectivity、オフライン動的連結性、時間軸のセグ木、辺の削除がある連結判定
- 種類：連結性・全域木、クエリ処理の工夫
- 前提：`union-find-connectivity`、`rollback-union-find`、`segment-tree`
- サイン：
    - 言い回し：辺の追加と削除のクエリが混ざり、そのつど連結性を答える（先に全部読んでよい）
    - 言い回し：各要素が「ない」時刻の区間がいくつかある
- 節：
    - `offline-dynamic-connectivity#time-segment-tree` 各辺の存在する区間を時間軸のセグ木に載せる：https://yuukougun.github.io/kyopro-atlas/graph/offline-dynamic-connectivity/#time-segment-tree
    - `offline-dynamic-connectivity#dfs-rollback` DFS で入るときに併合・出るときに取り消す（ロールバック Union-Find はデータ構造の章）：https://yuukougun.github.io/kyopro-atlas/graph/offline-dynamic-connectivity/#dfs-rollback

## 特殊な最小全域木（spanning-tree-advanced） {#spanning-tree-advanced}

- id：`spanning-tree-advanced`　レベル：発展　段階：stub　type：overview
- URL：https://yuukougun.github.io/kyopro-atlas/graph/spanning-tree-advanced/
- 別名：Borůvka 法、Boruvka、Manhattan MST、Chu-Liu/Edmonds、最小有向全域木、第 2 最小全域木、directed MST
- 種類：連結性・全域木
- 前提：`minimum-spanning-tree`
- サイン：
    - 言い回し：辺が暗黙に O(N^2) 本ある完全グラフの最小全域木
    - 言い回し：マンハッタン距離の完全グラフ
    - 言い回し：有向グラフで、根から全頂点へ届く最小コストの辺の集合
- 節：
    - `spanning-tree-advanced#boruvka` Borůvka 法：https://yuukougun.github.io/kyopro-atlas/graph/spanning-tree-advanced/#boruvka
    - `spanning-tree-advanced#manhattan` Manhattan MST：https://yuukougun.github.io/kyopro-atlas/graph/spanning-tree-advanced/#manhattan
    - `spanning-tree-advanced#directed` 最小有向全域木（Chu-Liu/Edmonds）：https://yuukougun.github.io/kyopro-atlas/graph/spanning-tree-advanced/#directed
    - `spanning-tree-advanced#second-best` 第 2 最小全域木：https://yuukougun.github.io/kyopro-atlas/graph/spanning-tree-advanced/#second-best

## 行列木定理（matrix-tree-theorem） {#matrix-tree-theorem}

- id：`matrix-tree-theorem`　レベル：発展　段階：stub　type：overview
- URL：https://yuukougun.github.io/kyopro-atlas/graph/matrix-tree-theorem/
- 別名：Kirchhoff の定理、全域木の個数、全域木の数え上げ、BEST 定理、matrix-tree theorem
- 種類：数え上げ、線形代数・行列、連結性・全域木
- 前提：`determinant`
- サイン：
    - 言い回し：全域木の個数を数える（mod p で答える）
    - 言い回し：有向グラフのオイラー閉路の数
- 節：
    - `matrix-tree-theorem#laplacian` ラプラシアン行列と余因子：https://yuukougun.github.io/kyopro-atlas/graph/matrix-tree-theorem/#laplacian
    - `matrix-tree-theorem#directed` 有向グラフの版（根付き全域木の数）：https://yuukougun.github.io/kyopro-atlas/graph/matrix-tree-theorem/#directed
    - `matrix-tree-theorem#best-theorem` BEST 定理（有向オイラー閉路の数）：https://yuukougun.github.io/kyopro-atlas/graph/matrix-tree-theorem/#best-theorem
    - `matrix-tree-theorem#subset-dp` 頂点集合ごとに数えて部分集合の DP と組む：https://yuukougun.github.io/kyopro-atlas/graph/matrix-tree-theorem/#subset-dp

## DFS 木・BFS 木とグラフの構築（graph-construction） {#graph-construction}

- id：`graph-construction`　レベル：青　段階：stub　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/graph/graph-construction/
- 別名：グラフの構築、DFS 木、BFS 木、後退辺、グラフの復元、DFS tree、back edge
- 種類：グラフ探索、考察
- 前提：`dfs`、`bfs`
- サイン：
    - 言い回し：条件を満たすグラフ・経路・全域木を 1 つ出力せよ
    - 言い回し：訪問回数の偶奇が指定された経路を作る
    - 言い回し：全点対の距離表からグラフを復元できるか
- 節：
    - `graph-construction#dfs-tree` DFS 木の性質（木に入らない辺は後退辺だけ）：https://yuukougun.github.io/kyopro-atlas/graph/graph-construction/#dfs-tree
    - `graph-construction#bfs-tree` BFS 木の性質（層が高々 1 違う）：https://yuukougun.github.io/kyopro-atlas/graph/graph-construction/#bfs-tree
    - `graph-construction#from-distances` 距離表からの復元（迂回できる辺は不要）：https://yuukougun.github.io/kyopro-atlas/graph/graph-construction/#from-distances
    - `graph-construction#parity-walk` DFS 木をたどって偶奇を合わせる（黄）：https://yuukougun.github.io/kyopro-atlas/graph/graph-construction/#parity-walk

## オイラー路（一筆書き）（euler-path） {#euler-path}

- id：`euler-path`　レベル：黄　段階：stub　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/graph/euler-path/
- 別名：オイラー閉路、一筆書き、Hierholzer、Euler path、Eulerian trail
- 種類：グラフ探索
- 前提：`connected-components`
- サイン：
    - 言い回し：すべての辺をちょうど 1 回ずつ通る・一筆書き
    - 言い回し：同じ道を 2 度通らずにすべての道を通れるか
- 節：
    - `euler-path#conditions` 存在条件（無向・有向）：https://yuukougun.github.io/kyopro-atlas/graph/euler-path/#conditions
    - `euler-path#hierholzer` Hierholzer 法で構成する：https://yuukougun.github.io/kyopro-atlas/graph/euler-path/#hierholzer
    - `euler-path#pitfalls` 孤立点・多重辺・自己ループの扱い：https://yuukougun.github.io/kyopro-atlas/graph/euler-path/#pitfalls
    - `euler-path#vs-hamiltonian` ハミルトン路（頂点をちょうど 1 回、bitDP）との違い：https://yuukougun.github.io/kyopro-atlas/graph/euler-path/#vs-hamiltonian

## 次数による平方分割（degree-sqrt） {#degree-sqrt}

- id：`degree-sqrt`　レベル：青　段階：stub　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/graph/degree-sqrt/
- 別名：次数の平方分割、重い頂点と軽い頂点、三角形の列挙、4-サイクルの検出、sqrt decomposition on degrees
- 種類：グラフ探索、クエリ処理の工夫
- 前提：`graph-basics`
- サイン：
    - 言い回し：頂点とその隣接頂点すべてに対する操作・質問が大量に来る
    - 言い回し：長さ 3・4 の閉路を見つける・数える
    - 制約：N, M, Q ≤ 2×10^5 で、1 つの頂点の次数が N 近くになりうる
- 節：
    - `degree-sqrt#few-heavy` 重い頂点は 2√M 個以下：https://yuukougun.github.io/kyopro-atlas/graph/degree-sqrt/#few-heavy
    - `degree-sqrt#push-pull` 重い頂点は受け取る側、軽い頂点は配る側：https://yuukougun.github.io/kyopro-atlas/graph/degree-sqrt/#push-pull
    - `degree-sqrt#triangles` 三角形の列挙（次数の小さい方から向き付ける）（黄）：https://yuukougun.github.io/kyopro-atlas/graph/degree-sqrt/#triangles
    - `degree-sqrt#four-cycles` 4-サイクルの検出（鳩の巣原理で打ち切る）（黄）：https://yuukougun.github.io/kyopro-atlas/graph/degree-sqrt/#four-cycles

## 最大流（max-flow） {#max-flow}

- id：`max-flow`　レベル：黄　段階：stub　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/graph/max-flow/
- 別名：最大フロー、Ford-Fulkerson、Dinic、残余グラフ、増加路、maximum flow
- 種類：フロー・マッチング
- 前提：`bfs`、`dfs`
- ACL：`mf_graph`
- サイン：
    - 言い回し：同時に使えない資源を割り当てる・各行・各列に高々 1 つ
    - 言い回し：辺（頂点）を共有しない経路の本数
    - 言い回し：容量・上限つきで送れる量の最大
    - 制約：頂点数が数百〜数千、辺数が 10^5 程度まで（フローが間に合う規模）
- 節：
    - `max-flow#residual` 残余グラフと増加路・逆辺が要る理由：https://yuukougun.github.io/kyopro-atlas/graph/max-flow/#residual
    - `max-flow#algorithms` Ford-Fulkerson・Dinic と計算量：https://yuukougun.github.io/kyopro-atlas/graph/max-flow/#algorithms
    - `max-flow#modeling` モデル化の型（行と列を頂点に・頂点の分割・時間の層）：https://yuukougun.github.io/kyopro-atlas/graph/max-flow/#modeling
    - `max-flow#undirected-vertex-capacity` 無向の辺・頂点の容量の表し方：https://yuukougun.github.io/kyopro-atlas/graph/max-flow/#undirected-vertex-capacity
    - `max-flow#acl` ACL では（mf_graph の囲み）：https://yuukougun.github.io/kyopro-atlas/graph/max-flow/#acl

## 最小カット（min-cut） {#min-cut}

- id：`min-cut`　レベル：黄　段階：stub　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/graph/min-cut/
- 別名：最大流最小カット定理、頂点カット、頂点分割、カットの復元、minimum cut、s-t cut
- 種類：フロー・マッチング
- 前提：`max-flow`
- ACL：`mf_graph`
- サイン：
    - 言い回し：s と t を切り離す最小のコスト
    - 言い回し：頂点を消すコストの最小・どれを消したかも出力する
- 節：
    - `min-cut#maxflow-mincut` 最大流最小カット定理：https://yuukougun.github.io/kyopro-atlas/graph/min-cut/#maxflow-mincut
    - `min-cut#restore` カットの復元（ACL の min_cut）：https://yuukougun.github.io/kyopro-atlas/graph/min-cut/#restore
    - `min-cut#vertex-cut` 頂点を入口と出口に分けて頂点カットを表す：https://yuukougun.github.io/kyopro-atlas/graph/min-cut/#vertex-cut
    - `min-cut#cut-shape` カットの形を決め打つ（発展）：https://yuukougun.github.io/kyopro-atlas/graph/min-cut/#cut-shape

## 燃やす埋める（project-selection） {#project-selection}

- id：`project-selection`　レベル：黄　段階：stub　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/graph/project-selection/
- 別名：Project Selection、最大重み閉包、劣モジュラ、project selection problem
- 種類：フロー・マッチング
- 前提：`min-cut`
- ACL：`mf_graph`
- サイン：
    - 言い回し：各要素を選ぶ・選ばないの 2 択で、利得とコストの合計を最大化する
    - 言い回し：A を選ぶなら B も選ぶ必要がある（依存関係）
    - 言い回し：隣どうしが違う（同じ）とペナルティ・利得
    - 制約：要素の数 N が 100〜数百程度で、選び方は 2^N 通りある
    - 式の形：目的関数が、0/1 変数ごとの項と「x_i = 1 かつ x_j = 0 ならコスト c」の項の和で書ける
- 節：
    - `project-selection#cheatsheet` 条件から辺への早見表：https://yuukougun.github.io/kyopro-atlas/graph/project-selection/#cheatsheet
    - `project-selection#gains` 利得はコストに読み替えて定数を足す：https://yuukougun.github.io/kyopro-atlas/graph/project-selection/#gains
    - `project-selection#closure` 最大重み閉包（依存関係）：https://yuukougun.github.io/kyopro-atlas/graph/project-selection/#closure
    - `project-selection#submodular` 表せる項と表せない項（劣モジュラ）：https://yuukougun.github.io/kyopro-atlas/graph/project-selection/#submodular
    - `project-selection#flip-side` 二部グラフで片側の意味を反転する：https://yuukougun.github.io/kyopro-atlas/graph/project-selection/#flip-side
    - `project-selection#multi-valued` 多値変数を頂点の列で表す（発展）：https://yuukougun.github.io/kyopro-atlas/graph/project-selection/#multi-valued

## 二部マッチング（bipartite-matching） {#bipartite-matching}

- id：`bipartite-matching`　レベル：黄　段階：stub　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/graph/bipartite-matching/
- 別名：二部グラフの最大マッチング、Hopcroft-Karp、交互路、完全マッチング、二部グラフの辺彩色、bipartite matching
- 種類：フロー・マッチング
- 前提：`max-flow`、`bipartite-graph`
- ACL：`mf_graph`
- サイン：
    - 言い回し：ペアを作る最大数・各人に 1 つずつ割り当てる
    - 言い回し：答えを決め打つと、全員に割り当てられるかの判定になる
    - 言い回し：和が素数・偶奇で 2 つのグループに分かれる
- 節：
    - `bipartite-matching#reduction` 最大流への帰着（容量 1）：https://yuukougun.github.io/kyopro-atlas/graph/bipartite-matching/#reduction
    - `bipartite-matching#alternating-path` 交互路と増加路（Kuhn・Hopcroft-Karp）：https://yuukougun.github.io/kyopro-atlas/graph/bipartite-matching/#alternating-path
    - `bipartite-matching#binary-search` 答えの二分探索と完全マッチングの判定：https://yuukougun.github.io/kyopro-atlas/graph/bipartite-matching/#binary-search
    - `bipartite-matching#greedy-cases` 構造で貪欲が通る特殊な場合との見分け：https://yuukougun.github.io/kyopro-atlas/graph/bipartite-matching/#greedy-cases
    - `bipartite-matching#edge-coloring` 正則二部グラフの分解・辺彩色（発展）：https://yuukougun.github.io/kyopro-atlas/graph/bipartite-matching/#edge-coloring

## König の定理（konig-theorem） {#konig-theorem}

- id：`konig-theorem`　レベル：黄　段階：stub　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/graph/konig-theorem/
- 別名：Konig の定理、最小頂点被覆、最大独立集合、最小辺被覆、LP の半整数性、König's theorem
- 種類：フロー・マッチング
- 前提：`bipartite-matching`、`min-cut`
- ACL：`mf_graph`
- サイン：
    - 言い回し：衝突する（隣り合う）ものを同時に選ばずに最大数選ぶ
    - 言い回し：すべての辺（マス）を監視するのに必要な最小数
    - 言い回し：市松模様・偶奇で 2 つのグループに分かれる
- 節：
    - `konig-theorem#theorem` König の定理と 3 つの関係（頂点被覆・独立集合・辺被覆）：https://yuukougun.github.io/kyopro-atlas/graph/konig-theorem/#theorem
    - `konig-theorem#restore` 被覆の復元（最小カットから）：https://yuukougun.github.io/kyopro-atlas/graph/konig-theorem/#restore
    - `konig-theorem#make-bipartite` 二部グラフに作り直す（市松模様・偶奇）：https://yuukougun.github.io/kyopro-atlas/graph/konig-theorem/#make-bipartite
    - `konig-theorem#general-graph` 一般グラフでは難しい（彩色数・最大独立集合のページへ）：https://yuukougun.github.io/kyopro-atlas/graph/konig-theorem/#general-graph
    - `konig-theorem#lp-half-integrality` 頂点を 2 倍にして二部グラフにする（LP の半整数性）（発展）：https://yuukougun.github.io/kyopro-atlas/graph/konig-theorem/#lp-half-integrality

## 最小費用流（min-cost-flow） {#min-cost-flow}

- id：`min-cost-flow`　レベル：黄　段階：stub　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/graph/min-cost-flow/
- 別名：primal-dual、重み付きマッチング、割当問題、ハンガリアン法、slope、minimum cost flow
- 種類：フロー・マッチング
- 前提：`max-flow`、`dijkstra`
- ACL：`mcf_graph`
- サイン：
    - 言い回し：K 個選んだときの最大（最小）を K ごとに答える
    - 言い回し：重み付きの割当・各行・各列から高々 K 個
    - 言い回し：流す量とコストの両方を最適化する
    - 制約：N ≤ 数百、M ≤ 数千程度で、流す量 K ≤ N
- 節：
    - `min-cost-flow#successive-shortest-path` 逐次最短路とポテンシャル：https://yuukougun.github.io/kyopro-atlas/graph/min-cost-flow/#successive-shortest-path
    - `min-cost-flow#nonnegative-cost` コストは 0 以上（最大化は「定数 − 利得」に直す）：https://yuukougun.github.io/kyopro-atlas/graph/min-cost-flow/#nonnegative-cost
    - `min-cost-flow#slope` 流量ごとの最小コスト（slope は下に凸）：https://yuukougun.github.io/kyopro-atlas/graph/min-cost-flow/#slope
    - `min-cost-flow#modeling` モデル化の型（重み付き二部マッチング・市松模様・差分列の流れ）：https://yuukougun.github.io/kyopro-atlas/graph/min-cost-flow/#modeling
    - `min-cost-flow#acl` ACL では（mcf_graph の囲み）：https://yuukougun.github.io/kyopro-atlas/graph/min-cost-flow/#acl
    - `min-cost-flow#hungarian` 割当問題とハンガリアン法（発展）：https://yuukougun.github.io/kyopro-atlas/graph/min-cost-flow/#hungarian

## 最小パス被覆と Hall の定理（dilworth-path-cover） {#dilworth-path-cover}

- id：`dilworth-path-cover`　レベル：発展　段階：stub　type：overview
- URL：https://yuukougun.github.io/kyopro-atlas/graph/dilworth-path-cover/
- 別名：最小パス被覆、最大反鎖、最小鎖被覆、結婚定理、マッチングの双対、path cover、Hall's theorem
- 種類：フロー・マッチング
- 前提：`bipartite-matching`、`scc`
- ACL：`mf_graph`
- サイン：
    - 言い回し：互いに包含しない（比べられない）ものを最大数選ぶ
    - 言い回し：最少の本数のパス（鎖）で全頂点を覆う
    - 制約：種類が 20 程度以下で、部分集合ごとに供給と需要を比べられる
- 節：
    - `dilworth-path-cover#path-cover` DAG の最小パス被覆（頂点を 2 つに分けた二部マッチング）：https://yuukougun.github.io/kyopro-atlas/graph/dilworth-path-cover/#path-cover
    - `dilworth-path-cover#antichain` 推移閉包と最大反鎖（数列なら LIS のページの Dilworth の定理へ）：https://yuukougun.github.io/kyopro-atlas/graph/dilworth-path-cover/#antichain
    - `dilworth-path-cover#hall` Hall の結婚定理：https://yuukougun.github.io/kyopro-atlas/graph/dilworth-path-cover/#hall

## 最小流量制約付きフロー（flow-lower-bounds） {#flow-lower-bounds}

- id：`flow-lower-bounds`　レベル：発展　段階：stub　type：overview
- URL：https://yuukougun.github.io/kyopro-atlas/graph/flow-lower-bounds/
- 別名：下限付きフロー、最小流量制約、flow with demands、flow with lower bounds
- 種類：フロー・マッチング
- 前提：`max-flow`
- ACL：`mf_graph`
- サイン：
    - 言い回し：この辺には少なくとも L だけ流す
    - 言い回し：必ず使う・使ってもよい・使ってはいけないものが混在する割当
- 節：
    - `flow-lower-bounds#pre-flow` 下限を先に流したことにする：https://yuukougun.github.io/kyopro-atlas/graph/flow-lower-bounds/#pre-flow
    - `flow-lower-bounds#super-vertex` 超頂点で過不足を調整して判定する：https://yuukougun.github.io/kyopro-atlas/graph/flow-lower-bounds/#super-vertex

## 一般グラフのマッチング（general-matching） {#general-matching}

- id：`general-matching`　レベル：発展　段階：stub　type：overview
- URL：https://yuukougun.github.io/kyopro-atlas/graph/general-matching/
- 別名：Edmonds、blossom、花のアルゴリズム、一般グラフの最大マッチング、general matching
- 種類：フロー・マッチング
- 前提：`bipartite-matching`
- サイン：
    - 言い回し：二部グラフでないグラフでペアを作る最大数
    - 制約：N ≤ 16 程度の一般グラフでペアを作る
- 節：
    - `general-matching#odd-cycles` 二部グラフとの違い（奇閉路）：https://yuukougun.github.io/kyopro-atlas/graph/general-matching/#odd-cycles
    - `general-matching#edmonds` Edmonds のアルゴリズムの概要：https://yuukougun.github.io/kyopro-atlas/graph/general-matching/#edmonds
    - `general-matching#bitdp` 小さければ bitDP：https://yuukougun.github.io/kyopro-atlas/graph/general-matching/#bitdp
