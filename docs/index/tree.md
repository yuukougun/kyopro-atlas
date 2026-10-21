---
title: 木の詳細索引
type: generated
search:
  exclude: true
---

<!-- tools/gen_site.py が生成する。手で直さない -->

# 木の詳細索引

分野の全ページの id・URL・別名・サイン・種類・前提・節。全分野の1行の一覧と索引の版は https://yuukougun.github.io/kyopro-atlas/llms.txt にある。stub（準備中）のページは要約と前提しかなく、節の見出しもまだない。

## 木の基本性質と表現（tree-basics） {#tree-basics}

- id：`tree-basics`　レベル：基礎　段階：stub　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/tree/tree-basics/
- 別名：木の定義、森、根付き木、木の性質、親の番号が自分より小さい入力、tree、forest
- 種類：木
- 前提：`dfs`
- サイン：
    - 言い回し：辺を 1 本取り除く・1 本足す・閉路をなくして森にする
    - 言い回し：森として残せる辺の数・消す辺の数
- 節：
    - `tree-basics#definitions` 木の同じ意味の定義と、そこから使える事実の一覧：https://yuukougun.github.io/kyopro-atlas/tree/tree-basics/#definitions
    - `tree-basics#input-forms` 入力の形（辺のリスト・親の配列・p_i < i）と根の決め方：https://yuukougun.github.io/kyopro-atlas/tree/tree-basics/#input-forms
    - `tree-basics#remove-add-edge` 辺を 1 本取り除くと 2 つの成分、1 本足すと閉路が 1 つ：https://yuukougun.github.io/kyopro-atlas/tree/tree-basics/#remove-add-edge
    - `tree-basics#forest` 森の連結成分の数 = 頂点数 − 辺数：https://yuukougun.github.io/kyopro-atlas/tree/tree-basics/#forest
    - `tree-basics#edge-to-child` 辺の値を子の頂点に寄せる：https://yuukougun.github.io/kyopro-atlas/tree/tree-basics/#edge-to-child
    - `tree-basics#extremes` 形の両極端（パスと星）でテストする：https://yuukougun.github.io/kyopro-atlas/tree/tree-basics/#extremes

## 根付き木と走査順（tree-traversal） {#tree-traversal}

- id：`tree-traversal`　レベル：基礎　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/tree/tree-traversal/
- 別名：木の探索、行きがけ順、帰りがけ順、DFS 順、BFS 順、部分木サイズ、深さ、preorder、postorder
- 種類：木、グラフ探索
- 前提：`tree-basics`、`bfs`
- サイン：
    - 言い回し：頂点 1 を根とする根付き木で、部分木の頂点数・和・最大を求める
    - 言い回し：子孫・祖先・訪問順を答える
    - 言い回し：p_i < i（親の番号が自分より小さい）形で木が与えられる
- 節：
    - `tree-traversal#parent-depth-size` 親・深さ・部分木サイズを求める：https://yuukougun.github.io/kyopro-atlas/tree/tree-traversal/#parent-depth-size
    - `tree-traversal#pre-post-order` 行きがけ順と帰りがけ順（子から親へ集約する）：https://yuukougun.github.io/kyopro-atlas/tree/tree-traversal/#pre-post-order
    - `tree-traversal#bfs-order` BFS 順の逆で再帰を使わずに集約する：https://yuukougun.github.io/kyopro-atlas/tree/tree-traversal/#bfs-order
    - `tree-traversal#parent-index` p_i < i なら番号の逆順で足りる：https://yuukougun.github.io/kyopro-atlas/tree/tree-traversal/#parent-index
    - `tree-traversal#recursion-depth` 再帰の深さ（パス状の木）と非再帰の書き方：https://yuukougun.github.io/kyopro-atlas/tree/tree-traversal/#recursion-depth
    - `tree-traversal#to-tree-dp` 一般の木 DP は DP の章へ：https://yuukougun.github.io/kyopro-atlas/tree/tree-traversal/#to-tree-dp

## 木の 2 色塗り分けと距離の偶奇（tree-bipartite） {#tree-bipartite}

- id：`tree-bipartite`　レベル：基礎　段階：stub　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/tree/tree-bipartite/
- 別名：木は二部グラフ、深さの偶奇、距離の偶奇、tree bipartition
- 種類：木
- 前提：`tree-traversal`、`bipartite-graph`
- サイン：
    - 言い回し：距離の偶奇・2 人が同時に動いて出会う場所
    - 言い回し：辺の重みの偶奇で頂点を塗り分ける
    - 言い回し：独立集合を N/2 個以上選ぶ・二部グラフのまま辺を足す
- 節：
    - `tree-bipartite#by-depth` 深さの偶奇で塗る（重みがあるなら重みの偶奇で）：https://yuukougun.github.io/kyopro-atlas/tree/tree-bipartite/#by-depth
    - `tree-bipartite#distance-parity` 距離の偶奇は深さだけで分かる：https://yuukougun.github.io/kyopro-atlas/tree/tree-bipartite/#distance-parity
    - `tree-bipartite#majority-color` 多い方の色は N/2 個以上：https://yuukougun.github.io/kyopro-atlas/tree/tree-bipartite/#majority-color
    - `tree-bipartite#cross-pairs` 色の違う組の数（二部グラフのまま足せる辺）：https://yuukougun.github.io/kyopro-atlas/tree/tree-bipartite/#cross-pairs

## 木の上の距離（tree-distance） {#tree-distance}

- id：`tree-distance`　レベル：基礎　段階：stub　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/tree/tree-distance/
- 別名：木の距離、根からの累積、XOR 距離、追いかけっこ、2 点からの距離、distance on a tree
- 種類：木
- 前提：`tree-traversal`
- サイン：
    - 言い回し：頂点 K を経由する最短距離
    - 言い回し：2 人の追いかけっこ・どちらが先に着くか
    - 言い回し：パス上の辺の重みの XOR
- 節：
    - `tree-distance#from-one` 1 点からの距離（ダイクストラはいらない）：https://yuukougun.github.io/kyopro-atlas/tree/tree-distance/#from-one
    - `tree-distance#from-two` 2 点からの距離を比べる：https://yuukougun.github.io/kyopro-atlas/tree/tree-distance/#from-two
    - `tree-distance#root-prefix` 根からの累積値で 2 点間を表す（XOR は LCA が不要、和は LCA が要る）：https://yuukougun.github.io/kyopro-atlas/tree/tree-distance/#root-prefix

## 木の上の累積和・いもす法（tree-imos） {#tree-imos}

- id：`tree-imos`　レベル：基礎　段階：stub　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/tree/tree-imos/
- 別名：木上のいもす法、部分木加算、パス加算、木上の累積和、prefix sums on a tree
- 種類：木、累積和・差分
- 前提：`tree-traversal`、`imos`
- サイン：
    - 言い回し：部分木の全頂点に x を加算するクエリがたくさん来て、最後に全頂点の値を出力する
    - 言い回し：辺のどちら側かの頂点すべてに加算する
    - 言い回し：多数のパスに沿って +1 し、各辺・各頂点を通った回数を求める
- 節：
    - `tree-imos#subtree-add` 部分木への加算（根から下へ累積する）：https://yuukougun.github.io/kyopro-atlas/tree/tree-imos/#subtree-add
    - `tree-imos#edge-side` 辺の片側への加算を子の部分木への加算に直す：https://yuukougun.github.io/kyopro-atlas/tree/tree-imos/#edge-side
    - `tree-imos#depth-limited` 根から y 世代までに及ぶ値を伝える：https://yuukougun.github.io/kyopro-atlas/tree/tree-imos/#depth-limited
    - `tree-imos#online-queries` 途中で値を聞かれるならオイラーツアーと BIT：https://yuukougun.github.io/kyopro-atlas/tree/tree-imos/#online-queries
    - `tree-imos#path-add` パスへの加算（LCA に印を置いて葉から上へ累積する）（青）：https://yuukougun.github.io/kyopro-atlas/tree/tree-imos/#path-add

## 指定頂点を結ぶ最小の部分木（steiner-subtree） {#steiner-subtree}

- id：`steiner-subtree`　レベル：基礎　段階：stub　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/tree/steiner-subtree/
- 別名：指定頂点を含む最小の部分木、必要な辺の数、木の上のシュタイナー木、Steiner tree on a tree
- 種類：木
- 前提：`tree-traversal`
- サイン：
    - 言い回し：指定した K 頂点をすべて連結に保つのに必要な最小の頂点数・辺数
- 節：
    - `steiner-subtree#root-at-terminal` 指定頂点を根にして、部分木に指定頂点を含むかで判定する：https://yuukougun.github.io/kyopro-atlas/tree/steiner-subtree/#root-at-terminal
    - `steiner-subtree#prune-leaves` 指定されていない葉を削り続ける：https://yuukougun.github.io/kyopro-atlas/tree/steiner-subtree/#prune-leaves
    - `steiner-subtree#vs-graph` 一般のグラフのシュタイナー木は別物（グラフの章）：https://yuukougun.github.io/kyopro-atlas/tree/steiner-subtree/#vs-graph

## 完全二分木（complete-binary-tree） {#complete-binary-tree}

- id：`complete-binary-tree`　レベル：基礎　段階：stub　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/tree/complete-binary-tree/
- 別名：ヒープ番号、親は i/2、K 分木、heap numbering、perfect binary tree
- 種類：木、ビット演算
- 前提：`tree-basics`、`bit-operations`
- サイン：
    - 言い回し：頂点 i と ⌊i/2⌋ を結ぶ・L/R/U の移動の列
    - 制約：N ≤ 10^18 の木
- 節：
    - `complete-binary-tree#binary-path` 番号の 2 進表記と根からの道順：https://yuukougun.github.io/kyopro-atlas/tree/complete-binary-tree/#binary-path
    - `complete-binary-tree#lru-moves` L/R/U の移動はスタックで打ち消す：https://yuukougun.github.io/kyopro-atlas/tree/complete-binary-tree/#lru-moves
    - `complete-binary-tree#lca-by-index` 番号だけで LCA を求める（大きい方を 2 で割る）：https://yuukougun.github.io/kyopro-atlas/tree/complete-binary-tree/#lca-by-index
    - `complete-binary-tree#k-ary` K 分木への一般化：https://yuukougun.github.io/kyopro-atlas/tree/complete-binary-tree/#k-ary
    - `complete-binary-tree#count-at-distance` 距離 K の頂点の数（部分木の深さの範囲を N で切る）（青）：https://yuukougun.github.io/kyopro-atlas/tree/complete-binary-tree/#count-at-distance

## 葉から考える（leaf-first） {#leaf-first}

- id：`leaf-first`　レベル：水　段階：stub　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/tree/leaf-first/
- 別名：葉から貪欲、葉を刈る、次数 1 の頂点を削る、葉から決める貪欲、greedy from leaves
- 種類：木、貪欲
- 前提：`tree-traversal`、`greedy-basics`
- サイン：
    - 言い回し：木を K 頂点ずつのパスに分ける
    - 言い回し：辺をすべて使う・すべて覆う
    - 言い回し：葉を消していく操作
- 節：
    - `leaf-first#peel-leaves` 次数 1 の頂点をキューで削る：https://yuukougun.github.io/kyopro-atlas/tree/leaf-first/#peel-leaves
    - `leaf-first#send-up` 帰りがけ順に葉から情報を上へ送る：https://yuukougun.github.io/kyopro-atlas/tree/leaf-first/#send-up
    - `leaf-first#why-greedy` 葉の唯一の辺を今使ってよい理由（交換論法）：https://yuukougun.github.io/kyopro-atlas/tree/leaf-first/#why-greedy
    - `leaf-first#tree-matching` 木の最大マッチング（葉と親を組む）：https://yuukougun.github.io/kyopro-atlas/tree/leaf-first/#tree-matching

## 木の次数列と Prüfer 列（tree-degree） {#tree-degree}

- id：`tree-degree`　レベル：青　段階：stub　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/tree/tree-degree/
- 別名：次数列、プリューファー列、Prüfer code、Prüfer sequence、握手補題、星、degree sequence
- 種類：木、数え上げ
- 前提：`leaf-first`
- サイン：
    - 言い回し：各頂点の次数を決めて木を作る・次数の和が 2N−2
    - 言い回し：次数が○以下の木・星や雪の結晶など次数で決まる形
- 節：
    - `tree-degree#degree-facts` 次数だけで分かること（葉の数・星の中心）：https://yuukougun.github.io/kyopro-atlas/tree/tree-degree/#degree-facts
    - `tree-degree#realizable` 次数列から木を作れる条件：https://yuukougun.github.io/kyopro-atlas/tree/tree-degree/#realizable
    - `tree-degree#pruefer` Prüfer 列と木の全単射（出現回数 = 次数 − 1）：https://yuukougun.github.io/kyopro-atlas/tree/tree-degree/#pruefer
    - `tree-degree#allocate-degrees` 次数を配る最適化：https://yuukougun.github.io/kyopro-atlas/tree/tree-degree/#allocate-degrees
    - `tree-degree#counting-links` 木の数え上げ（Cayley の公式）は数え上げの章、全域木の個数はグラフの章の行列木定理：https://yuukougun.github.io/kyopro-atlas/tree/tree-degree/#counting-links

## 木の直径と最遠点（tree-diameter） {#tree-diameter}

- id：`tree-diameter`　レベル：水　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/tree/tree-diameter/
- 別名：直径、最遠点、離心数、double sweep、2 回の BFS、木の中心、半径、長鎖分解、long-path decomposition、tree diameter
- 種類：木
- 前提：`tree-distance`
- サイン：
    - 言い回し：最も遠い 2 頂点・最長のパス
    - 言い回し：全頂点を訪れる最短の移動（戻らなくてよい）
    - 言い回し：各頂点から最も遠い頂点・2 つの木をつないだときの直径
    - 言い回し：K 個の頂点を選んで通る辺の総長を最大化する（K = 1, 2, … のすべてについて）
- 節：
    - `tree-diameter#double-sweep` 2 回の最遠点探索が正しい理由：https://yuukougun.github.io/kyopro-atlas/tree/tree-diameter/#double-sweep
    - `tree-diameter#eccentricity` 各点の最遠点は直径の端点（離心数）：https://yuukougun.github.io/kyopro-atlas/tree/tree-diameter/#eccentricity
    - `tree-diameter#visit-all` 全頂点を回る最短 = 2 × 辺の総和 − 直径：https://yuukougun.github.io/kyopro-atlas/tree/tree-diameter/#visit-all
    - `tree-diameter#negative-weights` 負の重みなら木 DP（DP の章）：https://yuukougun.github.io/kyopro-atlas/tree/tree-diameter/#negative-weights
    - `tree-diameter#root-at-end` 直径の端点を根にして距離 K の頂点を探す（青）：https://yuukougun.github.io/kyopro-atlas/tree/tree-diameter/#root-at-end
    - `tree-diameter#join-trees` 2 つの木をつないだ直径（青）：https://yuukougun.github.io/kyopro-atlas/tree/tree-diameter/#join-trees
    - `tree-diameter#center` 中心と半径・直径の個数（黄）：https://yuukougun.github.io/kyopro-atlas/tree/tree-diameter/#center
    - `tree-diameter#long-path-decomposition` 長鎖分解（最も深い子へつなぐ分解と、最も遠い葉を順に選ぶ貪欲）（黄）：https://yuukougun.github.io/kyopro-atlas/tree/tree-diameter/#long-path-decomposition

## 木の重心（tree-centroid） {#tree-centroid}

- id：`tree-centroid`　レベル：黄　段階：stub　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/tree/tree-centroid/
- 別名：重心、centroid、重み付き重心、tree centroid
- 種類：木
- 前提：`tree-traversal`
- サイン：
    - 言い回し：ペアを作ってパスの長さの和を最大化する
    - 言い回し：どの成分も半分以下になるように分ける
- 節：
    - `tree-centroid#definition` 定義と求め方（子の部分木と親側の N − sz）：https://yuukougun.github.io/kyopro-atlas/tree/tree-centroid/#definition
    - `tree-centroid#one-or-two` 重心は 1 個か隣接する 2 個：https://yuukougun.github.io/kyopro-atlas/tree/tree-centroid/#one-or-two
    - `tree-centroid#pair-across` 重心で分けて別の枝どうしを組む：https://yuukougun.github.io/kyopro-atlas/tree/tree-centroid/#pair-across
    - `tree-centroid#vs-center` 中心との違い：https://yuukougun.github.io/kyopro-atlas/tree/tree-centroid/#vs-center

## 辺で切って数える（tree-edge-contribution） {#tree-edge-contribution}

- id：`tree-edge-contribution`　レベル：水　段階：stub　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/tree/tree-edge-contribution/
- 別名：辺の寄与、木の主客転倒、全点対の距離の和、全ペアのパスの寄与、contribution of edges
- 種類：木、考察
- 前提：`tree-traversal`、`contribution`
- サイン：
    - 言い回し：すべての i < j について f(i, j) の総和
    - 言い回し：全ペアのパス上の最大値（最小値）の和
    - 制約：N ≤ 2×10^5 の木で、全ペア（N^2/2 組）についての和を求める
- 節：
    - `tree-edge-contribution#edge-pairs` 辺を通るペアは s(N−s) 個：https://yuukougun.github.io/kyopro-atlas/tree/tree-edge-contribution/#edge-pairs
    - `tree-edge-contribution#forest-count` 森の成分数 = 頂点数 − 辺数 に分けて数える：https://yuukougun.github.io/kyopro-atlas/tree/tree-edge-contribution/#forest-count
    - `tree-edge-contribution#max-on-path` パス上の最大値の和（重みの小さい順に併合して数える型は Union-Find の応用へ）：https://yuukougun.github.io/kyopro-atlas/tree/tree-edge-contribution/#max-on-path
    - `tree-edge-contribution#expectation` 期待値・特定の色を通らないパスへの応用（黄）：https://yuukougun.github.io/kyopro-atlas/tree/tree-edge-contribution/#expectation

## 木の構築・復元（tree-construction） {#tree-construction}

- id：`tree-construction`　レベル：水　段階：stub　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/tree/tree-construction/
- 別名：木の構築、木の復元、距離の表から木、訪問順から木、tree construction
- 種類：木、考察
- 前提：`tree-traversal`
- ACL：`dsu`
- サイン：
    - 言い回し：条件を満たす木を 1 つ出力せよ（なければ −1）
    - 言い回し：距離の情報から木を復元できるか
    - 言い回し：訪問順（DFS 順）から元の木が何通りあるか
- 節：
    - `tree-construction#from-distances` 距離の情報から作る（最も近い頂点とは辺で結ばれる）：https://yuukougun.github.io/kyopro-atlas/tree/tree-construction/#from-distances
    - `tree-construction#from-order` 訪問順から親の候補を数える：https://yuukougun.github.io/kyopro-atlas/tree/tree-construction/#from-order
    - `tree-construction#verify-output` 作った木を必ず確かめる：https://yuukougun.github.io/kyopro-atlas/tree/tree-construction/#verify-output
    - `tree-construction#from-degrees` 次数の条件から作る（次数の足りない成分どうしをつなぐ）（青）：https://yuukougun.github.io/kyopro-atlas/tree/tree-construction/#from-degrees
    - `tree-construction#from-eccentricities` 最遠距離の列から直径を決める（青）：https://yuukougun.github.io/kyopro-atlas/tree/tree-construction/#from-eccentricities

## 木の同型判定と木のハッシュ（tree-isomorphism） {#tree-isomorphism}

- id：`tree-isomorphism`　レベル：発展　段階：stub　type：overview
- URL：https://yuukougun.github.io/kyopro-atlas/tree/tree-isomorphism/
- 別名：木の同型、木のハッシュ、AHU、rooted tree hash、tree isomorphism
- 種類：木、ハッシュ・乱択
- 前提：`tree-diameter`
- サイン：
    - 言い回し：形が同じ部分木の種類数
    - 言い回し：2 つの木が同じ形か（根あり・根なし）
- 節：
    - `tree-isomorphism#ahu` AHU 法（子の名前の多重集合に名前を付ける）：https://yuukougun.github.io/kyopro-atlas/tree/tree-isomorphism/#ahu
    - `tree-isomorphism#tree-hash` 木のハッシュと衝突しにくい設計：https://yuukougun.github.io/kyopro-atlas/tree/tree-isomorphism/#tree-hash
    - `tree-isomorphism#unrooted` 根のない木は中心を根にする：https://yuukougun.github.io/kyopro-atlas/tree/tree-isomorphism/#unrooted

## 最小共通祖先（LCA）（lca） {#lca}

- id：`lca`　レベル：青　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/tree/lca/
- 別名：LCA、Lowest Common Ancestor、最近共通祖先、木のダブリング、K 個上の祖先、level ancestor
- 種類：木、ダブリング・分割統治
- 前提：`tree-traversal`、`doubling`
- サイン：
    - 言い回し：木の 2 頂点の距離をクエリでたくさん聞かれる
    - 制約：パス u–v に関するクエリが Q ≤ 2×10^5 個
    - 言い回し：ちょうど距離 K の頂点・K 個上の祖先
- 節：
    - `lca#jump` 深さをそろえてから同時に跳ぶ：https://yuukougun.github.io/kyopro-atlas/tree/lca/#jump
    - `lca#distance` 距離 = dep(u) + dep(v) − 2 dep(lca)：https://yuukougun.github.io/kyopro-atlas/tree/lca/#distance
    - `lca#kth-ancestor` K 個上の祖先（K を 2 進数に分けて跳ぶ）：https://yuukougun.github.io/kyopro-atlas/tree/lca/#kth-ancestor
    - `lca#path-aggregate` パス上の最大値・和を表と一緒に持つ：https://yuukougun.github.io/kyopro-atlas/tree/lca/#path-aggregate
    - `lca#farthest-ancestor` 条件を満たす最も遠い祖先：https://yuukougun.github.io/kyopro-atlas/tree/lca/#farthest-ancestor
    - `lca#comparison` LCA の求め方の比較（ダブリング・オイラーツアーと Sparse Table・HL 分解・オフライン）：https://yuukougun.github.io/kyopro-atlas/tree/lca/#comparison

## 木の上のパスの判定と分解（tree-path） {#tree-path}

- id：`tree-path`　レベル：青　段階：stub　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/tree/tree-path/
- 別名：パスクエリ、2 頂点間のパス、パスの分解、合流点、パスの交差、path queries on a tree
- 種類：木
- 前提：`lca`、`tree-distance`
- サイン：
    - 言い回し：u から v へのパス上の…・パスに含まれる辺
    - 言い回し：2 本のパスが交わるか・共通部分
    - 言い回し：どちらの端点に近いか（パスの中点）
- 節：
    - `tree-path#on-path` 点 x がパス上にあるか（d(u,x) + d(x,v) = d(u,v)）：https://yuukougun.github.io/kyopro-atlas/tree/tree-path/#on-path
    - `tree-path#meeting-point` 3 点の合流点と根の付け替え：https://yuukougun.github.io/kyopro-atlas/tree/tree-path/#meeting-point
    - `tree-path#intersection` 2 本のパスの交差：https://yuukougun.github.io/kyopro-atlas/tree/tree-path/#intersection
    - `tree-path#kth-on-path` パス上の K 番目の頂点：https://yuukougun.github.io/kyopro-atlas/tree/tree-path/#kth-on-path
    - `tree-path#vertex-vs-edge` 頂点の値と辺の値で LCA の扱いが違う：https://yuukougun.github.io/kyopro-atlas/tree/tree-path/#vertex-vs-edge
    - `tree-path#edge-set` パスを辺の集合として扱う（包除原理）：https://yuukougun.github.io/kyopro-atlas/tree/tree-path/#edge-set
    - `tree-path#to-hld` パスへの一括更新があるなら HL 分解（発展）：https://yuukougun.github.io/kyopro-atlas/tree/tree-path/#to-hld

## 根からのパスを DFS で持ち回る（root-path-dfs） {#root-path-dfs}

- id：`root-path-dfs`　レベル：青　段階：stub　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/tree/root-path-dfs/
- 別名：DFS の巻き戻し、根からのパスの情報、入るとき足して出るとき戻す、rollback on DFS
- 種類：木、クエリ処理の工夫
- 前提：`tree-traversal`
- サイン：
    - 言い回し：根から頂点 v までのパス上の…を、すべての v について求める
    - 言い回し：祖先の情報だけで決まる値
    - 言い回し：操作を元に戻す・保存した状態に戻る
- 節：
    - `root-path-dfs#stack-is-path` DFS のスタックは根からのパス：https://yuukougun.github.io/kyopro-atlas/tree/root-path-dfs/#stack-is-path
    - `root-path-dfs#undo-log` 変更の記録と巻き戻し（後に変えたものから戻す）：https://yuukougun.github.io/kyopro-atlas/tree/root-path-dfs/#undo-log
    - `root-path-dfs#path-statistics` パス上の LIS・中央値・種類数：https://yuukougun.github.io/kyopro-atlas/tree/root-path-dfs/#path-statistics
    - `root-path-dfs#to-version-tree` 操作の履歴を木にする型は永続データ構造の版の木へ：https://yuukougun.github.io/kyopro-atlas/tree/root-path-dfs/#to-version-tree
    - `root-path-dfs#no-path-compression` 経路圧縮つきの Union-Find は戻せない（取り消せる Union-Find はデータ構造の章）：https://yuukougun.github.io/kyopro-atlas/tree/root-path-dfs/#no-path-compression

## オイラーツアー（euler-tour） {#euler-tour}

- id：`euler-tour`　レベル：青　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/tree/euler-tour/
- 別名：Euler Tour、行きがけ順の番号付け、in/out、木の平坦化、tree flattening、辺のオイラーツアー、DFS 順で部分木を区間にする
- 種類：木、区間クエリ
- 前提：`tree-traversal`、`fenwick-tree`
- ACL：`fenwick_tree`、`segtree`、`lazy_segtree`
- サイン：
    - 言い回し：部分木の和・最大・個数を、更新を挟みながら聞かれる
    - 言い回し：部分木に加算する・辺を取り除いたときの片側の和
    - 言い回し：u が v の祖先か・v の子孫のうち深さ d のもの
    - 言い回し：辺の重みの変更と 2 点間の距離のクエリ
    - 制約：N, Q ≤ 2×10^5 で、部分木への更新と質問が交互に来る
- 節：
    - `euler-tour#meanings` 「オイラーツアー」の 4 つの意味：https://yuukougun.github.io/kyopro-atlas/tree/euler-tour/#meanings
    - `euler-tour#in-out` 部分木が区間になる理由と in・out の定義：https://yuukougun.github.io/kyopro-atlas/tree/euler-tour/#in-out
    - `euler-tour#ancestor-depth` 祖先の判定と深さごとの頂点の数：https://yuukougun.github.io/kyopro-atlas/tree/euler-tour/#ancestor-depth
    - `euler-tour#complement` 部分木の補集合は 2 つの区間：https://yuukougun.github.io/kyopro-atlas/tree/euler-tour/#complement
    - `euler-tour#root-path` 根からのパスを区間で扱う（辺の重みを子の部分木に配る）：https://yuukougun.github.io/kyopro-atlas/tree/euler-tour/#root-path
    - `euler-tour#mo-on-tree` 木上の Mo（データ構造の章）：https://yuukougun.github.io/kyopro-atlas/tree/euler-tour/#mo-on-tree
    - `euler-tour#to-hld` 逆元がない演算・パスへの一括更新は HL 分解（発展）：https://yuukougun.github.io/kyopro-atlas/tree/euler-tour/#to-hld

## HL 分解（hld） {#hld}

- id：`hld`　レベル：発展　段階：draft　type：overview
- URL：https://yuukougun.github.io/kyopro-atlas/tree/hld/
- 別名：HLD、Heavy-Light Decomposition、重軽分解
- 種類：木、区間クエリ
- 前提：`euler-tour`、`lca`、`segment-tree`
- ACL：`segtree`、`lazy_segtree`
- サイン：
    - 言い回し：パスへの一括更新とパスの取得が混ざる
    - 言い回し：パス上の最大値（逆元のない演算）を更新つきで答える
    - 言い回し：部分木とパスの両方のクエリ
- 節：
    - `hld#heavy-light` 重い辺と軽い辺・根からの軽い辺が log N 本以下の理由：https://yuukougun.github.io/kyopro-atlas/tree/hld/#heavy-light
    - `hld#numbering` 番号の振り方（重い子を先に）とパスの区間への分解：https://yuukougun.github.io/kyopro-atlas/tree/hld/#numbering
    - `hld#edge-values` 辺の値は子の頂点に置く・非可換な演算の向き：https://yuukougun.github.io/kyopro-atlas/tree/hld/#edge-values
    - `hld#when-to-use` いつ使うか（オイラーツアーと LCA で足りる場合との使い分け）：https://yuukougun.github.io/kyopro-atlas/tree/hld/#when-to-use
    - `hld#library` 自作ライブラリでの扱い：https://yuukougun.github.io/kyopro-atlas/tree/hld/#library

## Static Top Tree と木 DP の動的更新（static-top-tree） {#static-top-tree}

- id：`static-top-tree`　レベル：発展　段階：stub　type：overview
- URL：https://yuukougun.github.io/kyopro-atlas/tree/static-top-tree/
- 別名：Static Top Tree、動的木 DP、重軽再帰 DP、dynamic tree DP
- 種類：木、DP、データ構造
- 前提：`hld`、`tree-dp`
- サイン：
    - 言い回し：頂点の値を更新するたびに、木全体についての最適値・数え上げの結果を答える
- 節：
    - `static-top-tree#heavy-path-dp` 重いパスの上で DP をセグ木に載せる：https://yuukougun.github.io/kyopro-atlas/tree/static-top-tree/#heavy-path-dp
    - `static-top-tree#compress-rake` Static Top Tree（圧縮と併合）：https://yuukougun.github.io/kyopro-atlas/tree/static-top-tree/#compress-rake

## 動的木（dynamic-tree） {#dynamic-tree}

- id：`dynamic-tree`　レベル：発展　段階：stub　type：overview
- URL：https://yuukougun.github.io/kyopro-atlas/tree/dynamic-tree/
- 別名：Link-Cut Tree、LCT、Euler Tour Tree、Top Tree、dynamic tree
- 種類：木、データ構造
- 前提：`hld`、`balanced-bst`
- サイン：
    - 言い回し：辺の追加と削除をくり返す森でのパスのクエリ
    - 言い回し：根の付け替えがある
- 節：
    - `dynamic-tree#link-cut` Link-Cut Tree でできること：https://yuukougun.github.io/kyopro-atlas/tree/dynamic-tree/#link-cut
    - `dynamic-tree#ett-top-tree` Euler Tour Tree・Top Tree：https://yuukougun.github.io/kyopro-atlas/tree/dynamic-tree/#ett-top-tree
    - `dynamic-tree#add-only` 辺の追加だけならマージテク：https://yuukougun.github.io/kyopro-atlas/tree/dynamic-tree/#add-only

## マージテク（small-to-large） {#small-to-large}

- id：`small-to-large`　レベル：水　段階：stub　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/tree/small-to-large/
- 別名：small-to-large、小さい方を大きい方へ移す、データ構造をマージする一般的なテク、weighted union heuristic、DSU on Tree、Sack
- 種類：データ構造、木
- 前提：`union-find`、`ordered-set`
- ACL：`dsu`
- サイン：
    - 言い回し：グループの併合と、グループ内の種類数・個数の問い合わせ
    - 言い回し：部分木ごとに集合（map）を持って併合する
    - 言い回し：すべての部分木について、色の種類数・最頻値を求める
- 節：
    - `small-to-large#why-log` 要素が移るのは高々 log N 回の理由：https://yuukougun.github.io/kyopro-atlas/tree/small-to-large/#why-log
    - `small-to-large#swap` swap で入れ替える・大きい方を代表に残す：https://yuukougun.github.io/kyopro-atlas/tree/small-to-large/#swap
    - `small-to-large#map-on-root` Union-Find の代表元に map を持たせる：https://yuukougun.github.io/kyopro-atlas/tree/small-to-large/#map-on-root
    - `small-to-large#reroot-smaller` 森に辺を足すとき小さい方を根付け直す（黄）：https://yuukougun.github.io/kyopro-atlas/tree/small-to-large/#reroot-smaller
    - `small-to-large#subtree-merge` 部分木ごとの集合の併合（木 DP での使い方は DP の章）（黄）：https://yuukougun.github.io/kyopro-atlas/tree/small-to-large/#subtree-merge
    - `small-to-large#dsu-on-tree` DSU on Tree（重い子の結果を残す）（黄）：https://yuukougun.github.io/kyopro-atlas/tree/small-to-large/#dsu-on-tree

## 重心分解（centroid-decomposition） {#centroid-decomposition}

- id：`centroid-decomposition`　レベル：黄　段階：stub　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/tree/centroid-decomposition/
- 別名：centroid decomposition、点分治、木の分割統治
- 種類：木、ダブリング・分割統治
- 前提：`tree-centroid`、`divide-and-conquer`
- サイン：
    - 言い回し：距離がちょうど K の頂点の組の個数
    - 言い回し：全ペアのパスについての量で、辺ごとに分解できないもの
    - 言い回し：ある頂点から距離 d 以内の頂点の集計クエリ
- 節：
    - `centroid-decomposition#depth` 再帰の深さが log N になる理由：https://yuukougun.github.io/kyopro-atlas/tree/centroid-decomposition/#depth
    - `centroid-decomposition#count-through` 重心を通るペアを数え、同じ成分の中のペアを引く：https://yuukougun.github.io/kyopro-atlas/tree/centroid-decomposition/#count-through
    - `centroid-decomposition#centroid-tree-queries` 木全体の数え上げと、重心木を上にたどるクエリ：https://yuukougun.github.io/kyopro-atlas/tree/centroid-decomposition/#centroid-tree-queries
    - `centroid-decomposition#with-convolution` 距離の頻度表は畳み込みと組む（発展）：https://yuukougun.github.io/kyopro-atlas/tree/centroid-decomposition/#with-convolution

## Auxiliary Tree（auxiliary-tree） {#auxiliary-tree}

- id：`auxiliary-tree`　レベル：発展　段階：stub　type：overview
- URL：https://yuukougun.github.io/kyopro-atlas/tree/auxiliary-tree/
- 別名：Virtual Tree、虚樹、圧縮木、LCA 木、指定頂点の圧縮木
- 種類：木
- 前提：`lca`、`euler-tour`、`steiner-subtree`、`tree-dp`
- サイン：
    - 言い回し：色ごと・クエリごとに少数の頂点だけが関わり、その頂点数の合計が N 程度
    - 言い回し：クエリごとに指定された頂点をすべてつなぐのに必要な辺の数を答える
    - 制約：クエリごとに K_i 個の頂点が指定され、ΣK_i ≤ 2×10^5
- 節：
    - `auxiliary-tree#steiner-queries` 指定頂点を結ぶ部分木の大きさ（DFS 順で隣り合う 2 点の距離の和の半分）：https://yuukougun.github.io/kyopro-atlas/tree/auxiliary-tree/#steiner-queries
    - `auxiliary-tree#build` DFS 順に並べて隣り合う 2 点の LCA を足す：https://yuukougun.github.io/kyopro-atlas/tree/auxiliary-tree/#build
    - `auxiliary-tree#stack-build` スタックで組み立てる：https://yuukougun.github.io/kyopro-atlas/tree/auxiliary-tree/#stack-build
    - `auxiliary-tree#alternatives` マージテク・平方分割で代用できる場合：https://yuukougun.github.io/kyopro-atlas/tree/auxiliary-tree/#alternatives

## 併合過程の木（merge-process-tree） {#merge-process-tree}

- id：`merge-process-tree`　レベル：発展　段階：stub　type：overview
- URL：https://yuukougun.github.io/kyopro-atlas/tree/merge-process-tree/
- 別名：クラスカル再構築木、Kruskal 再構築木、Kruskal reconstruction tree、KRT、DSU-tree、Union-Find の併合の過程を表す木
- 種類：木、連結性・全域木
- 前提：`minimum-spanning-tree`、`euler-tour`、`lca`
- ACL：`dsu`
- サイン：
    - 言い回し：ある時点のグループについての問い合わせ（オフライン）
    - 言い回し：パス上の最大の辺の最小値（ボトルネック）をオンラインで多数答える
    - 言い回し：辺を重みの順に足していく過程を後から問われる
- 節：
    - `merge-process-tree#new-vertex` 併合のたびに新しい頂点を作る：https://yuukougun.github.io/kyopro-atlas/tree/merge-process-tree/#new-vertex
    - `merge-process-tree#group-as-interval` ある時点のグループは DFS 順の区間：https://yuukougun.github.io/kyopro-atlas/tree/merge-process-tree/#group-as-interval
    - `merge-process-tree#bottleneck` ボトルネックは LCA の重み：https://yuukougun.github.io/kyopro-atlas/tree/merge-process-tree/#bottleneck
    - `merge-process-tree#alternatives` マージテク・部分永続 Union-Find・並列二分探索との使い分け：https://yuukougun.github.io/kyopro-atlas/tree/merge-process-tree/#alternatives

## 比で親に併合する貪欲（tree-ratio-greedy） {#tree-ratio-greedy}

- id：`tree-ratio-greedy`　レベル：発展　段階：stub　type：overview
- URL：https://yuukougun.github.io/kyopro-atlas/tree/tree-ratio-greedy/
- 別名：01 on Tree、木の上の順序最適化、比による併合、親を先に選ぶ制約つきの並べ方
- 種類：木、貪欲
- 前提：`union-find`、`exchange-argument`
- ACL：`dsu`
- サイン：
    - 言い回し：親を子より先に選ぶ制約つきで、順番による重み付きの和を最適化する
- 節：
    - `tree-ratio-greedy#why-ratio` 比が最大の塊は親の直後に来てよい理由：https://yuukougun.github.io/kyopro-atlas/tree/tree-ratio-greedy/#why-ratio
    - `tree-ratio-greedy#merge-with-heap` Union-Find と優先度付きキューで併合する：https://yuukougun.github.io/kyopro-atlas/tree/tree-ratio-greedy/#merge-with-heap
