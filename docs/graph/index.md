---
title: グラフ
type: generated
---

<!-- tools/gen_site.py が生成する。手で直さない -->

# グラフ

探索、最短路、有向グラフ、連結性と全域木、探索木と次数の性質、フロー。47 ページ。ページ名の横の印はレベル（[レベルの意味](../start/how-to-use.md#levels)）である。

学ぶ順：[色別ロードマップ](../guide/roadmap.md#reading-order)。使い分け：[最短路の選び方（重みと始点の数）](../guide/method-comparison.md#shortest-path)・[連結性](../guide/method-comparison.md#connectivity)。問題集：[典型90問](../guide/problem-sets.md#problem-sets-typical90)・[ACL Practice](../guide/problem-sets.md#problem-sets-practice2)・[鉄則本](../guide/problem-sets.md#problem-sets-tessoku-book)。自作：[自作ライブラリの設計と動作確認](../guide/library-design.md)。

## 基本と探索

- [グラフの表現と用語](graph-basics.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：N 頂点 M 辺のグラフを隣接リスト・隣接行列・辺リストのどれで持つかを選び、次数・パス・連結・木・DAG などの用語をそろえる。
- [グラフへの帰着](graph-modeling.md)：物・値・座標・状態・時刻・剰余などを頂点に、関係・操作・制約を辺にすると、問題が既知のグラフの問題（連結・二部・閉路・最短路）に変わる。
- [深さ優先探索（DFS）](dfs.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：行けるところまで進んでから戻る探索で、到達可能性・連結成分・閉路検出・トポロジカル順の土台になる。
- [幅優先探索（BFS）と無重み最短路](bfs.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：始点に近い順に頂点を確定させる探索で、辺の重みがすべて等しいグラフの最短距離を O(N+M) で求める。
- [グリッドグラフ](grid-graph.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：マスを頂点、隣り合うマスを辺と見て、BFS・DFS・Union-Find をそのまま使う。
- [連結成分](connected-components.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：無向グラフを互いに行き来できる頂点の集まりに分け、成分ごとに頂点数・辺数などを集計する。
- [閉路の検出と復元](cycle-detection.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：無向グラフでは Union-Find か親以外の訪問済み頂点への辺、有向グラフでは探索中の頂点への辺（3 色の DFS）で閉路を見つけ、親をたどって復元する。
- [なもりグラフ](namori-graph.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>：N 頂点 N 辺の連結グラフは木に辺を 1 本足した形で、閉路がちょうど 1 つあり、閉路上の各頂点から木がぶら下がる。
- [二部グラフ判定](bipartite-graph.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：隣り合う頂点を反対の色で塗っていき、同じ色どうしを結ぶ辺（奇数長の閉路）があれば二部グラフでない。
- [小さいグラフの全探索](small-graph-brute-force.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：N ≤ 8〜10 程度の小さいグラフで、頂点の対応（N! 通り）・辺の部分集合・彩色を全部試す。
- [彩色数・最大独立集合・最大クリーク](chromatic-number.md) <span class="kp-mini kp-lv-hatten" title="difficulty 2400〜（概要だけ）">発展</span>：一般グラフの彩色数・最大独立集合・最大クリークは NP 困難で、彩色数は包除原理で O(2^N N)、最大独立集合は N ≤ 40 程度なら分枝や半分全列挙で求める。

## 最短路

- [ダイクストラ法](dijkstra.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：辺の重みが非負のグラフで、暫定距離が最小の頂点から順に確定させ、単一始点の最短距離を O((N+M) log N) で求める。
- [01-BFS](zero-one-bfs.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>：辺の重みが 0 か 1 のとき、コスト 0 の辺で得た頂点は deque の先頭へ、コスト 1 の辺は末尾へ入れて、最短距離を O(N+M) で求める。
- [ワーシャルフロイド法](warshall-floyd.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>：経由してよい頂点を 1 つずつ増やす DP で、全点対の最短距離を O(N^3) で求める。
- [ベルマンフォード法](bellman-ford.md) <span class="kp-mini kp-lv-ao" title="difficulty 1600〜1999">青</span>：負の辺があっても、全辺の緩和を N−1 回くり返して単一始点の最短距離を O(NM) で求める。
- [最短路 DAG](shortest-path-dag.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>：始点からの距離 d で d(v) = d(u) + w(u, v) を満たす辺だけを残すと DAG になり、最短路はその上のパスと一対一に対応する。
- [状態を頂点にする](extended-dijkstra.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>：元の頂点だけでは次の動きが決まらないとき、向き・残り回数・偶奇・盤面などを組にした状態を頂点にして最短路を求める。
- [時刻で変わる辺の最短路](time-dependent-dijkstra.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>：辺の所要時間が出発時刻で変わる最短路は、早く着いて損をしない（待てる）なら、各頂点で最も早い到着時刻だけを持つダイクストラ法で求まる。
- [差分制約（牛ゲー）](difference-constraints.md) <span class="kp-mini kp-lv-ao" title="difficulty 1600〜1999">青</span>：x_v − x_u ≤ c の形の条件を辺 u→v（重み c）と読み、始点からの最短距離で全条件を満たす最大の解を求める。
- [補グラフ上の BFS](complement-graph-bfs.md) <span class="kp-mini kp-lv-ki" title="difficulty 2000〜2399">黄</span>：完全グラフから M 本の辺を除いたグラフ（補グラフ）を、未訪問頂点の集合から元のグラフで隣接しない頂点を一度に取り出す BFS で、O(N + M) で探索する。
- [剰余を頂点にする最短路](modular-shortest-path.md) <span class="kp-mini kp-lv-hatten" title="difficulty 2400〜（概要だけ）">発展</span>：K で割った余りを頂点、数を作る操作を辺にした最短路で、K の倍数のうち桁和が最小のものや、いくつかの数の和で作れる数を求める。
- [区間に辺を張る](segment-tree-graph.md) <span class="kp-mini kp-lv-hatten" title="difficulty 2400〜（概要だけ）">発展</span>：頂点から区間内の全頂点へ辺がある問題で、セグメント木のノードを補助頂点にして区間を O(log N) 個で覆い、辺の数を O(M log N) に減らして最短路を求める。
- [K 番目の最短路](k-shortest-paths.md) <span class="kp-mini kp-lv-hatten" title="difficulty 2400〜（概要だけ）">発展</span>：始点から終点への経路のうち、短い方から K 番目の長さを求める。
- [最小シュタイナー木](steiner-tree.md) <span class="kp-mini kp-lv-hatten" title="difficulty 2400〜（概要だけ）">発展</span>：一般のグラフで指定した K 点（K ≤ 10 程度）をすべてつなぐ最小コストを、端点の集合と頂点を状態にした DP で O(3^K N + 2^K (N + M) log N) で求める。

ほかの章の関連ページ：[幅優先探索（BFS）と無重み最短路](bfs.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>（基本と探索の章）

## 有向グラフ

- [トポロジカルソート](topological-sort.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：閉路のない有向グラフの頂点を、すべての辺が前から後ろへ向くように O(N+M) で並べる。
- [強連結成分分解（SCC）](scc.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>：有向グラフを互いに行き来できる頂点の極大集合に分け、成分を 1 点に縮めて DAG にする。
- [Functional graph（出次数 1 のグラフ）](functional-graph.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>：各頂点から出る辺がちょうど 1 本の有向グラフは、各成分に閉路がちょうど 1 つあり、そこへ木が流れ込む ρ の形になる。
- [2-SAT](two-sat.md) <span class="kp-mini kp-lv-hatten" title="difficulty 2400〜（概要だけ）">発展</span>：各変数が真か偽で、条件がすべて「2 つのリテラルの OR」のとき、全条件を満たす割当を含意グラフの SCC で O(N+M) で求める。

## 連結性と全域木

- [Union-Find で連結性を扱う](union-find-connectivity.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>：辺や頂点の削除を時間の逆順の追加に直したり、しきい値の順に辺を足したりして、連結成分の数・大きさや 2 点の連結を Union-Find で答える。
- [最小全域木](minimum-spanning-tree.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>：連結グラフの全域木のうち辺の重みの和が最小のものを、辺を重みの昇順に見て閉路を作らない辺だけを採るクラスカル法か、頂点を 1 つずつ伸ばすプリム法で求める。
- [最小ボトルネック路](bottleneck-path.md) <span class="kp-mini kp-lv-ao" title="difficulty 1600〜1999">青</span>：経路上の辺の最大値を最小にする経路は最小全域木の上で実現でき、クラスカル法で辺を足して 2 点が初めてつながったときの重みが答えになる。
- [橋・関節点・二重連結成分](lowlink.md) <span class="kp-mini kp-lv-ki" title="difficulty 2000〜2399">黄</span>：DFS 木の行きがけ番号 ord と、部分木から後退辺を 1 本使って戻れる最小の番号 low から、取り除くと非連結になる辺（橋）と頂点（関節点）を O(N+M) で求める。
- [辺の追加と削除が混ざる連結性](offline-dynamic-connectivity.md) <span class="kp-mini kp-lv-hatten" title="difficulty 2400〜（概要だけ）">発展</span>：辺の追加と削除が混ざる連結性の質問に、各辺が存在する時間の区間を時間軸のセグ木の O(log Q) 個のノードに載せ、DFS で入るときに併合・出るときに取り消してオフラインで答える。
- [特殊な最小全域木](spanning-tree-advanced.md) <span class="kp-mini kp-lv-hatten" title="difficulty 2400〜（概要だけ）">発展</span>：辺が暗黙に与えられる完全グラフの最小全域木を Borůvka 法で求め、マンハッタン距離の完全グラフは候補辺を O(N) 本に絞る。
- [行列木定理](matrix-tree-theorem.md) <span class="kp-mini kp-lv-hatten" title="difficulty 2400〜（概要だけ）">発展</span>：無向グラフの全域木の個数は、ラプラシアン行列（次数行列 − 隣接行列）から 1 行 1 列を除いた行列の行列式に等しい。

ほかの章の関連ページ：[連結成分](connected-components.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>（基本と探索の章）

## 探索木と次数の性質

- [DFS 木・BFS 木とグラフの構築](graph-construction.md) <span class="kp-mini kp-lv-ao" title="difficulty 1600〜1999">青</span>：無向グラフの DFS 木では木に入らない辺がすべて祖先と子孫を結び、BFS 木では層が高々 1 違う頂点どうしを結ぶ。
- [オイラー路（一筆書き）](euler-path.md) <span class="kp-mini kp-lv-ki" title="difficulty 2000〜2399">黄</span>：すべての辺をちょうど 1 回ずつ通る路は、辺のある頂点が連結で、奇数次数の頂点が 0 個か 2 個（有向なら入次数と出次数の条件）のときに限りあり、Hierholzer 法で O(N + M) で作れる。
- [次数による平方分割](degree-sqrt.md) <span class="kp-mini kp-lv-ao" title="difficulty 1600〜1999">青</span>：次数が √M を超える重い頂点は 2√M 個以下しかないことを使い、重い頂点と軽い頂点で処理を分けて、頂点とその隣接頂点すべてへのクエリを O(√M) にする。

## フロー・マッチング

- [最大流](max-flow.md) <span class="kp-mini kp-lv-ki" title="difficulty 2000〜2399">黄</span>：容量付きの有向グラフで s から t へ流せる最大量を、残余グラフ上の増加路に流すことをくり返して求める。
- [最小カット](min-cut.md) <span class="kp-mini kp-lv-ki" title="difficulty 2000〜2399">黄</span>：頂点を s 側と t 側に分けたとき、s 側から t 側へ向かう辺の容量の和の最小値は最大流に等しい。
- [燃やす埋める](project-selection.md) <span class="kp-mini kp-lv-ki" title="difficulty 2000〜2399">黄</span>：各要素を選ぶか選ばないかの 2 択とその組合せのコストを辺に直し、最小カットで最適な選び方を求める。
- [二部マッチング](bipartite-matching.md) <span class="kp-mini kp-lv-ki" title="difficulty 2000〜2399">黄</span>：二部グラフで端点を共有しない辺の最大集合を、容量 1 の最大流（s → 左 → 右 → t）で求める。
- [König の定理](konig-theorem.md) <span class="kp-mini kp-lv-ki" title="difficulty 2000〜2399">黄</span>：二部グラフでは最大マッチングの大きさが最小頂点被覆の大きさに等しく、最大独立集合は頂点数から最小頂点被覆を引いたものになる。
- [最小費用流](min-cost-flow.md) <span class="kp-mini kp-lv-ki" title="difficulty 2000〜2399">黄</span>：流量 F を流すときのコストの最小値を、残余グラフ上のコストの最短路に沿って流すことをくり返して求める。
- [最小パス被覆と Hall の定理](dilworth-path-cover.md) <span class="kp-mini kp-lv-hatten" title="difficulty 2400〜（概要だけ）">発展</span>：DAG の頂点を最少の本数のパスで覆う数は、頂点を 2 つに分けた二部グラフの最大マッチングから求まる。
- [最小流量制約付きフロー](flow-lower-bounds.md) <span class="kp-mini kp-lv-hatten" title="difficulty 2400〜（概要だけ）">発展</span>：辺に「少なくとも L は流す」という下限があるとき、L を先に流したことにして超頂点で過不足を調整し、普通の最大流に帰着する。
- [一般グラフのマッチング](general-matching.md) <span class="kp-mini kp-lv-hatten" title="difficulty 2400〜（概要だけ）">発展</span>：二部グラフでないグラフの最大マッチングは、奇閉路（花）を縮約する Edmonds のアルゴリズムで多項式時間で求まる。

## ほかの分野にある関連ページ {#elsewhere}

種類に[グラフ探索](../lists/kind-graph-search.md)・[最短路](../lists/kind-shortest-path.md)・[連結性・全域木](../lists/kind-connectivity.md)・[フロー・マッチング](../lists/kind-flow.md)のどれかを持つ、ほかの分野のページ。

- [動的計画法](../dp/index.md)：[DAG 上の DP](../dp/dp-dag.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>
- [木](../tree/index.md)：[根付き木と走査順](../tree/tree-traversal.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>・[併合過程の木](../tree/merge-process-tree.md) <span class="kp-mini kp-lv-hatten" title="difficulty 2400〜（概要だけ）">発展</span>
- [データ構造](../ds/index.md)：[Union-Find](../ds/union-find.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>・[Union-Find の応用](../ds/union-find-applications.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>・[重み付き Union-Find](../ds/weighted-union-find.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>・[部分永続 Union-Find](../ds/partially-persistent-union-find.md) <span class="kp-mini kp-lv-hatten" title="difficulty 2400〜（概要だけ）">発展</span>・[ロールバックできる Union-Find](../ds/rollback-union-find.md) <span class="kp-mini kp-lv-hatten" title="difficulty 2400〜（概要だけ）">発展</span>
- [数え上げ・確率・ゲーム](../comb/index.md)：[後退解析](../comb/game-retrograde-analysis.md) <span class="kp-mini kp-lv-ki" title="difficulty 2000〜2399">黄</span>
