---
id: max-flow
title: 最大流
aliases: [最大フロー, Ford-Fulkerson, Dinic, 残余グラフ, 増加路, maximum flow]
type: technique
field: graph
chapter: フロー・マッチング
order: 390
level: 黄
kind: [フロー・マッチング]
prerequisites: [bfs, dfs]
related: [min-cut, bipartite-matching, min-cost-flow, flow-lower-bounds, grid-graph, graph-modeling]
summary: 容量付きの有向グラフで s から t へ流せる最大量を、残余グラフ上の増加路に流すことをくり返して求める。逆辺で押し戻せることが正しさの要で、ACL の mf_graph（Dinic）で書ける。
complexity: null
signs:
  - {type: phrase, text: 同時に使えない資源を割り当てる・各行・各列に高々 1 つ}
  - {type: phrase, text: 辺（頂点）を共有しない経路の本数}
  - {type: phrase, text: 容量・上限つきで送れる量の最大}
  - {type: constraint, text: 頂点数が数百〜数千、辺数が 10^5 程度まで（フローが間に合う規模）}
acl: [mf_graph]
frequency: B
frequency_evidence: recent 0・前提として 8 ページに届く（直接 4）・古い ABC 3 問
sections:
  - {title: 残余グラフと増加路・逆辺が要る理由, anchor: residual}
  - {title: Ford-Fulkerson・Dinic と計算量, anchor: algorithms}
  - {title: モデル化の型（行と列を頂点に・頂点の分割・時間の層）, anchor: modeling}
  - {title: 無向の辺・頂点の容量の表し方, anchor: undirected-vertex-capacity}
  - {title: ACL では（mf_graph の囲み）, anchor: acl}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：容量付きの有向グラフで s から t へ流せる最大量を、残余グラフ上の増加路に流すことをくり返して求める。逆辺で押し戻せることが正しさの要で、ACL の mf_graph（Dinic）で書ける。
    - **いつ使うか**：
        - 同時に使えない資源を割り当てる・各行・各列に高々 1 つ
        - 辺（頂点）を共有しない経路の本数
        - 容量・上限つきで送れる量の最大
        - 頂点数が数百〜数千、辺数が 10^5 程度まで（フローが間に合う規模）
    - **計算量**：（執筆時に書く）
    - **前提**：[幅優先探索（BFS）と無重み最短路](../graph/bfs.md)、[深さ優先探索（DFS）](../graph/dfs.md)
