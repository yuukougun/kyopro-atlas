---
id: matrix-tree-theorem
title: 行列木定理
aliases: [Kirchhoff の定理, 全域木の個数, 全域木の数え上げ, BEST 定理, matrix-tree theorem]
type: overview
field: graph
chapter: 連結性と全域木
order: 350
level: 発展
kind: [数え上げ, 線形代数・行列, 連結性・全域木]
prerequisites: [determinant]
related: [cayley-pruefer, tree-degree, spanning-tree-advanced, euler-path, counting-labeled-graphs]
summary: 無向グラフの全域木の個数は、ラプラシアン行列（次数行列 − 隣接行列）から 1 行 1 列を除いた行列の行列式に等しい。有向グラフの版と、有向オイラー閉路を数える BEST 定理もある。
complexity: null
signs:
  - {type: phrase, text: 全域木の個数を数える（mod p で答える）}
  - {type: phrase, text: 有向グラフのオイラー閉路の数}
acl: []
verify: [counting_spanning_tree_undirected, counting_spanning_tree_directed]
frequency: C
frequency_evidence: recent 0・前提として届くページなし・古い ABC 1 問
sections:
  - {title: ラプラシアン行列と余因子, anchor: laplacian}
  - {title: 有向グラフの版（根付き全域木の数）, anchor: directed}
  - {title: BEST 定理（有向オイラー閉路の数）, anchor: best-theorem}
  - {title: 頂点集合ごとに数えて部分集合の DP と組む, anchor: subset-dp}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：無向グラフの全域木の個数は、ラプラシアン行列（次数行列 − 隣接行列）から 1 行 1 列を除いた行列の行列式に等しい。有向グラフの版と、有向オイラー閉路を数える BEST 定理もある。
    - **いつ使うか**：
        - 全域木の個数を数える（mod p で答える）
        - 有向グラフのオイラー閉路の数
    - **計算量**：（執筆時に書く）
    - **前提**：[行列式](../math/determinant.md)
