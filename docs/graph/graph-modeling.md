---
id: graph-modeling
title: グラフへの帰着
aliases: [グラフに言い換える, モデル化, 何を頂点にするか, 何を辺にするか, グラフの縮約, graph modeling]
type: hub
field: graph
chapter: 基本と探索
order: 20
level: null
kind: [案内, グラフ探索, 考察]
prerequisites: [graph-basics]
related: [reformulation, connected-components, bipartite-graph, cycle-detection, extended-dijkstra, difference-constraints, scc, functional-graph]
summary: 物・値・座標・状態・時刻・剰余などを頂点に、関係・操作・制約を辺にすると、問題が既知のグラフの問題（連結・二部・閉路・最短路）に変わる。自由に行き来できる部分は 1 点に縮約できる。
complexity: null
signs: []
acl: []
sections:
  - {title: 何を頂点にするか（物・値・座標・状態・時刻・剰余・区間の端点 → 行き先のページの表）, anchor: what-to-vertex}
  - {title: 何を辺にするか（関係・操作・制約・写像）, anchor: what-to-edge}
  - {title: 制約を辺にすると何の問題になるか（二部グラフ・閉路・差分制約）, anchor: constraints-to-edges}
  - {title: 自由に行き来できる部分を 1 点に縮約する（Union-Find・SCC・次数 2 の頂点を消す）, anchor: contraction}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何のページか**：物・値・座標・状態・時刻・剰余などを頂点に、関係・操作・制約を辺にすると、問題が既知のグラフの問題（連結・二部・閉路・最短路）に変わる。自由に行き来できる部分は 1 点に縮約できる。
    - **使い方**：（執筆時に書く）
    - **前提**：[グラフの表現と用語](../graph/graph-basics.md)
