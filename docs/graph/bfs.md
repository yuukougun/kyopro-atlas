---
id: bfs
title: 幅優先探索（BFS）と無重み最短路
aliases: [幅優先探索, BFS, breadth-first search, 無重み最短路, 多始点 BFS, 最短経路の復元]
type: technique
field: graph
chapter: 基本と探索
order: 40
level: 基礎
kind: [グラフ探索, 最短路]
prerequisites: [graph-basics, stack-techniques]
related: [dfs, zero-one-bfs, dijkstra, grid-graph, shortest-path-dag, extended-dijkstra, complement-graph-bfs]
summary: 始点に近い順に頂点を確定させる探索で、辺の重みがすべて等しいグラフの最短距離を O(N+M) で求める。親を記録すれば経路を復元でき、全始点をキューに入れれば多始点の距離になる。
complexity: null
signs:
  - {type: phrase, text: 最小の手数・回数を求める（1 回の移動のコストがすべて同じ）}
  - {type: phrase, text: 一番近い〇〇までの距離・複数の場所から同時に広がる}
  - {type: phrase, text: 最短経路を 1 つ出力する・次に進む頂点を答える}
  - {type: constraint, text: 'N, M ≤ 2×10^5、またはマスの数 H×W ≤ 10^6 程度'}
acl: []
frequency: A
frequency_evidence: recent 3（abc453_d・abc460_d・abc472_d）・前提として 57 ページに届く（直接 10）・古い ABC 6 問
sections:
  - {title: 最初に見つけた距離が最短になる理由, anchor: why-shortest}
  - {title: 印は push のときに付ける・dist を −1 で初期化して訪問済みの印を兼ねる, anchor: mark-on-push}
  - {title: 経路復元（発見したときの親を記録して終点からたどる）, anchor: path-restoration}
  - {title: 多始点 BFS（超始点から距離 0 の辺を張るのと同じ）, anchor: multi-source}
  - {title: 重みが 1 と 2 なら辺を割る・重み付きなら 01-BFS かダイクストラ, anchor: weighted}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：始点に近い順に頂点を確定させる探索で、辺の重みがすべて等しいグラフの最短距離を O(N+M) で求める。親を記録すれば経路を復元でき、全始点をキューに入れれば多始点の距離になる。
    - **いつ使うか**：
        - 最小の手数・回数を求める（1 回の移動のコストがすべて同じ）
        - 一番近い〇〇までの距離・複数の場所から同時に広がる
        - 最短経路を 1 つ出力する・次に進む頂点を答える
        - N, M ≤ 2×10^5、またはマスの数 H×W ≤ 10^6 程度
    - **計算量**：（執筆時に書く）
    - **前提**：[グラフの表現と用語](../graph/graph-basics.md)、[スタック・キュー・deque の使いどころ](../ds/stack-techniques.md)
