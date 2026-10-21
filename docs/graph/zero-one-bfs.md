---
id: zero-one-bfs
title: 01-BFS
aliases: [0-1 BFS, deque BFS]
type: technique
field: graph
chapter: 最短路
order: 120
level: 水
kind: [最短路]
prerequisites: [dijkstra]
related: [bfs, extended-dijkstra, grid-graph, modular-shortest-path, method-comparison]
summary: 辺の重みが 0 か 1 のとき、コスト 0 の辺で得た頂点は deque の先頭へ、コスト 1 の辺は末尾へ入れて、最短距離を O(N+M) で求める。壁を壊す回数や向きを変える回数の最小化に使う。
complexity: null
signs:
  - {type: phrase, text: 壁を壊す回数・向きを変える回数・ワープの回数を最小化する}
  - {type: phrase, text: 1 回の移動のコストが 0 か 1}
  - {type: shape, text: 言い換えると、辺の重みが 0 と 1 の 2 種類だけのグラフの最短路になる}
acl: []
frequency: B
frequency_evidence: recent 0・前提として 1 ページに届く（直接 1）・古い ABC 3 問
sections:
  - {title: deque の中の距離が 2 種類に保たれる理由, anchor: deque-invariant}
  - {title: 初めて見つけたときに確定させてはいけない, anchor: no-early-fix}
  - {title: 向きを状態に持つ（頂点数が 4 倍になる）, anchor: direction-state}
  - {title: '重みが 0, 1, 2 ならどうするか', anchor: weights-012}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：辺の重みが 0 か 1 のとき、コスト 0 の辺で得た頂点は deque の先頭へ、コスト 1 の辺は末尾へ入れて、最短距離を O(N+M) で求める。壁を壊す回数や向きを変える回数の最小化に使う。
    - **いつ使うか**：
        - 壁を壊す回数・向きを変える回数・ワープの回数を最小化する
        - 1 回の移動のコストが 0 か 1
        - 言い換えると、辺の重みが 0 と 1 の 2 種類だけのグラフの最短路になる
    - **計算量**：（執筆時に書く）
    - **前提**：[ダイクストラ法](../graph/dijkstra.md)
