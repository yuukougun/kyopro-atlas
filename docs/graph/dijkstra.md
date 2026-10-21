---
id: dijkstra
title: ダイクストラ法
aliases: [ダイクストラ, Dijkstra, Dijkstra's algorithm, 経由点の最短路, 両端からのダイクストラ, 逆向きのグラフ, 最短閉路, ポテンシャルで負辺を消す, Johnson のアイデア]
type: technique
field: graph
chapter: 最短路
order: 110
level: 基礎
kind: [最短路]
prerequisites: [bfs]
related: [priority-queue, zero-one-bfs, bellman-ford, extended-dijkstra, time-dependent-dijkstra, shortest-path-dag, k-shortest-paths, method-comparison]
summary: 辺の重みが非負のグラフで、暫定距離が最小の頂点から順に確定させ、単一始点の最短距離を O((N+M) log N) で求める。逆向きのグラフや両端からの距離を組み合わせれば、経由点や往復の問題も解ける。
complexity: null
signs:
  - {type: phrase, text: 非負の重み付きグラフの最短距離・最小コスト（頂点にもコストがある）}
  - {type: constraint, text: 'N, M ≤ 2×10^5 で辺の重みが非負'}
  - {type: phrase, text: 頂点 k を経由する最短路をすべての k について・行きと帰り}
  - {type: phrase, text: 負の辺の重みが「高さの差」の形をしている}
acl: []
verify: [shortest_path]
frequency: A
frequency_evidence: recent 2（abc463_e・abc477_e）・前提として 12 ページに届く（直接 9）・古い ABC 8 問
sections:
  - {title: 取り出した頂点の距離が確定する理由, anchor: why-correct}
  - {title: 古い組を読み飛ばす・priority_queue を最小ヒープにする, anchor: skip-stale}
  - {title: 頂点の重みを辺に足す・経路復元は BFS と同じ, anchor: vertex-weights}
  - {title: 密グラフの O(N^2) 版, anchor: dense}
  - {title: 負辺で壊れる例, anchor: negative-edges}
  - {title: 最短閉路（ある頂点を含む閉路の最小の長さ）, anchor: shortest-cycle}
  - {title: 逆向きのグラフと両端からの最短路, anchor: reverse-graph, level: 水}
  - {title: ポテンシャルで負辺を消す（Johnson のアイデア）, anchor: potential, level: 水}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：辺の重みが非負のグラフで、暫定距離が最小の頂点から順に確定させ、単一始点の最短距離を O((N+M) log N) で求める。逆向きのグラフや両端からの距離を組み合わせれば、経由点や往復の問題も解ける。
    - **いつ使うか**：
        - 非負の重み付きグラフの最短距離・最小コスト（頂点にもコストがある）
        - N, M ≤ 2×10^5 で辺の重みが非負
        - 頂点 k を経由する最短路をすべての k について・行きと帰り
        - 負の辺の重みが「高さの差」の形をしている
    - **計算量**：（執筆時に書く）
    - **前提**：[幅優先探索（BFS）と無重み最短路](../graph/bfs.md)
