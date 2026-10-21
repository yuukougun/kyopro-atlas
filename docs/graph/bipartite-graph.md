---
id: bipartite-graph
title: 二部グラフ判定
aliases: [二部グラフ, 2 彩色, 奇閉路, 2 色の塗り分け, bipartite graph]
type: technique
field: graph
chapter: 基本と探索
order: 80
level: 基礎
kind: [グラフ探索]
prerequisites: [dfs, bfs]
related: [weighted-union-find, tree-bipartite, bipartite-matching, konig-theorem, project-selection, grid-graph, graph-modeling]
summary: 隣り合う頂点を反対の色で塗っていき、同じ色どうしを結ぶ辺（奇数長の閉路）があれば二部グラフでない。成分ごとの色の数を使う数え上げや、二部マッチング・最小カットの前提になる。
complexity: null
signs:
  - {type: phrase, text: 2 つのグループに分ける・隣り合うものは異なる色}
  - {type: phrase, text: X_i と Y_i は異なる値、という条件が M 個ある}
  - {type: phrase, text: 奇数長の閉路があるか}
acl: [dsu]
frequency: A
frequency_evidence: recent 2（abc451_f・abc472_e）・前提として 5 ページに届く（直接 2）・古い ABC 3 問
sections:
  - {title: BFS・DFS で塗る（非連結なら成分ごとに）, anchor: coloring}
  - {title: 二部グラフでないことと奇閉路があることは同じ, anchor: odd-cycle}
  - {title: 成分ごとの色の数を使う数え上げ, anchor: count-by-color}
  - {title: Union-Find（頂点を 2 倍にする・偶奇を持つ）で判定する, anchor: union-find}
  - {title: 木・4 近傍のグリッドは必ず二部グラフ, anchor: always-bipartite}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：隣り合う頂点を反対の色で塗っていき、同じ色どうしを結ぶ辺（奇数長の閉路）があれば二部グラフでない。成分ごとの色の数を使う数え上げや、二部マッチング・最小カットの前提になる。
    - **いつ使うか**：
        - 2 つのグループに分ける・隣り合うものは異なる色
        - X_i と Y_i は異なる値、という条件が M 個ある
        - 奇数長の閉路があるか
    - **計算量**：（執筆時に書く）
    - **前提**：[深さ優先探索（DFS）](../graph/dfs.md)、[幅優先探索（BFS）と無重み最短路](../graph/bfs.md)
