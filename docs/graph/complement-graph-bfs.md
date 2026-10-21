---
id: complement-graph-bfs
title: 補グラフ上の BFS
aliases: [補グラフ, 未訪問頂点の集合, complement graph]
type: technique
field: graph
chapter: 最短路
order: 190
level: 黄
kind: [グラフ探索]
prerequisites: [bfs, ordered-set]
related: [shortest-path-dag, linked-list]
summary: 完全グラフから M 本の辺を除いたグラフ（補グラフ）を、未訪問頂点の集合から元のグラフで隣接しない頂点を一度に取り出す BFS で、O(N + M) で探索する。
complexity: null
signs:
  - {type: phrase, text: 完全グラフから M 本の辺を取り除いたグラフ・辺が「ない」組が与えられる}
  - {type: constraint, text: N ≤ 2×10^5 で、補グラフの辺は N^2 本近くあり列挙できない}
acl: []
verify: [connected_components_of_complement_graph]
frequency: C
frequency_evidence: recent 0・前提として届くページなし・古い ABC 1 問
sections:
  - {title: 未訪問頂点の集合から取り出す, anchor: take-unvisited}
  - {title: 各頂点が 1 回しか取り出されない理由（O(N + M)）, anchor: complexity}
  - {title: 層ごとに最短路の本数を数える, anchor: count-by-layer}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：完全グラフから M 本の辺を除いたグラフ（補グラフ）を、未訪問頂点の集合から元のグラフで隣接しない頂点を一度に取り出す BFS で、O(N + M) で探索する。
    - **いつ使うか**：
        - 完全グラフから M 本の辺を取り除いたグラフ・辺が「ない」組が与えられる
        - N ≤ 2×10^5 で、補グラフの辺は N^2 本近くあり列挙できない
    - **計算量**：（執筆時に書く）
    - **前提**：[幅優先探索（BFS）と無重み最短路](../graph/bfs.md)、[set・multiset・map の応用](../ds/ordered-set.md)
