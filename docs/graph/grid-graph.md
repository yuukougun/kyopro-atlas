---
id: grid-graph
title: グリッドグラフ
aliases: [グリッド BFS, 迷路の探索, 4 近傍, 8 近傍, grid graph]
type: technique
field: graph
chapter: 基本と探索
order: 50
level: 基礎
kind: [グラフ探索]
prerequisites: [bfs, dfs]
related: [connected-components, zero-one-bfs, union-find-connectivity, bipartite-graph, max-flow, grid]
summary: マスを頂点、隣り合うマスを辺と見て、BFS・DFS・Union-Find をそのまま使う。(i, j) の 1 次元化・番兵・止まるマスの扱いと、市松模様で二部グラフになることが要点になる。
complexity: null
signs:
  - {type: phrase, text: H×W のマス目を上下左右（8 方向）に移動する・壁や障害物がある}
  - {type: constraint, text: 'H, W ≤ 2000 程度（マスの数が 4×10^6 程度まで）'}
  - {type: phrase, text: 'H, W が巨大で、障害物の数だけが少ない'}
acl: []
frequency: A
frequency_evidence: recent 2（abc453_d・abc460_d）・前提として届くページなし・古い ABC 4 問
sections:
  - {title: 4 近傍・8 近傍と dx・dy の配列, anchor: neighbors}
  - {title: '(i, j) を i×W+j に 1 次元化する・外周に番兵を置く', anchor: flatten}
  - {title: 止まるマス・境界のマスの数え方, anchor: boundary-cells}
  - {title: 市松模様で二部グラフになる（フロー・マッチングへの入口）, anchor: checkerboard}
  - {title: 障害物どうしの 8 近傍の連結で通れるかを判定する, anchor: obstacle-dual, level: 青}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：マスを頂点、隣り合うマスを辺と見て、BFS・DFS・Union-Find をそのまま使う。(i, j) の 1 次元化・番兵・止まるマスの扱いと、市松模様で二部グラフになることが要点になる。
    - **いつ使うか**：
        - H×W のマス目を上下左右（8 方向）に移動する・壁や障害物がある
        - H, W ≤ 2000 程度（マスの数が 4×10^6 程度まで）
        - H, W が巨大で、障害物の数だけが少ない
    - **計算量**：（執筆時に書く）
    - **前提**：[幅優先探索（BFS）と無重み最短路](../graph/bfs.md)、[深さ優先探索（DFS）](../graph/dfs.md)
