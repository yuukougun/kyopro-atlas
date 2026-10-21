---
id: graph-construction
title: DFS 木・BFS 木とグラフの構築
aliases: [グラフの構築, DFS 木, BFS 木, 後退辺, グラフの復元, DFS tree, back edge]
type: technique
field: graph
chapter: 探索木と次数の性質
order: 360
level: 青
kind: [グラフ探索, 考察]
prerequisites: [dfs, bfs]
related: [warshall-floyd, construction, tree-construction, lowlink]
summary: 無向グラフの DFS 木では木に入らない辺がすべて祖先と子孫を結び、BFS 木では層が高々 1 違う頂点どうしを結ぶ。この性質で条件を満たす木や経路を作り、距離表からグラフを復元する。
complexity: null
signs:
  - {type: phrase, text: 条件を満たすグラフ・経路・全域木を 1 つ出力せよ}
  - {type: phrase, text: 訪問回数の偶奇が指定された経路を作る}
  - {type: phrase, text: 全点対の距離表からグラフを復元できるか}
acl: []
frequency: B
frequency_evidence: recent 0・前提として届くページなし・古い ABC 3 問
sections:
  - {title: DFS 木の性質（木に入らない辺は後退辺だけ）, anchor: dfs-tree}
  - {title: BFS 木の性質（層が高々 1 違う）, anchor: bfs-tree}
  - {title: 距離表からの復元（迂回できる辺は不要）, anchor: from-distances}
  - {title: DFS 木をたどって偶奇を合わせる, anchor: parity-walk, level: 黄}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：無向グラフの DFS 木では木に入らない辺がすべて祖先と子孫を結び、BFS 木では層が高々 1 違う頂点どうしを結ぶ。この性質で条件を満たす木や経路を作り、距離表からグラフを復元する。
    - **いつ使うか**：
        - 条件を満たすグラフ・経路・全域木を 1 つ出力せよ
        - 訪問回数の偶奇が指定された経路を作る
        - 全点対の距離表からグラフを復元できるか
    - **計算量**：（執筆時に書く）
    - **前提**：[深さ優先探索（DFS）](../graph/dfs.md)、[幅優先探索（BFS）と無重み最短路](../graph/bfs.md)
