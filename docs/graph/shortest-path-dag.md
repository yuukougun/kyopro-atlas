---
id: shortest-path-dag
title: 最短路 DAG
aliases: [最短路木, 最短経路の数え上げ, 最短路に必ず使われる辺, shortest path DAG]
type: technique
field: graph
chapter: 最短路
order: 150
level: 水
kind: [最短路, DP]
prerequisites: [dijkstra, dp-dag]
related: [bfs, minimum-spanning-tree, lowlink, warshall-floyd, complement-graph-bfs]
summary: 始点からの距離 d で d(v) = d(u) + w(u, v) を満たす辺だけを残すと DAG になり、最短路はその上のパスと一対一に対応する。最短路の本数・最短路木・必ず使われる辺が分かる。
complexity: null
signs:
  - {type: phrase, text: 最短経路の本数を数える}
  - {type: phrase, text: この辺を通らなくても最短距離は変わらないか・最短路に使われない辺}
  - {type: phrase, text: 始点からの最短距離を保ったまま辺を減らし、全域木を出力する}
acl: []
frequency: B
frequency_evidence: recent 0・前提として届くページなし・古い ABC 5 問
sections:
  - {title: 最短路 DAG の作り方と性質（重み 0 の辺に注意）, anchor: build}
  - {title: 最短路の本数の DP, anchor: count-paths}
  - {title: 最短路木（最小全域木との違い）, anchor: shortest-path-tree}
  - {title: 辺が s-t 最短路に乗る条件（両端からの距離）, anchor: edge-on-path}
  - {title: 辺を消すと距離が変わるか, anchor: edge-removal, level: 黄}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：始点からの距離 d で d(v) = d(u) + w(u, v) を満たす辺だけを残すと DAG になり、最短路はその上のパスと一対一に対応する。最短路の本数・最短路木・必ず使われる辺が分かる。
    - **いつ使うか**：
        - 最短経路の本数を数える
        - この辺を通らなくても最短距離は変わらないか・最短路に使われない辺
        - 始点からの最短距離を保ったまま辺を減らし、全域木を出力する
    - **計算量**：（執筆時に書く）
    - **前提**：[ダイクストラ法](../graph/dijkstra.md)、[DAG 上の DP](../dp/dp-dag.md)
