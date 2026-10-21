---
id: spanning-tree-advanced
title: 特殊な最小全域木
aliases: [Borůvka 法, Boruvka, Manhattan MST, Chu-Liu/Edmonds, 最小有向全域木, 第 2 最小全域木, directed MST]
type: overview
field: graph
chapter: 連結性と全域木
order: 340
level: 発展
kind: [連結性・全域木]
prerequisites: [minimum-spanning-tree]
related: [matrix-tree-theorem, steiner-tree, centroid-decomposition]
summary: 辺が暗黙に与えられる完全グラフの最小全域木を Borůvka 法で求め、マンハッタン距離の完全グラフは候補辺を O(N) 本に絞る。有向グラフの最小全域木（Chu-Liu/Edmonds）と第 2 最小全域木の求め方もある。
complexity: null
signs:
  - {type: phrase, text: 辺が暗黙に O(N^2) 本ある完全グラフの最小全域木}
  - {type: phrase, text: マンハッタン距離の完全グラフ}
  - {type: phrase, text: 有向グラフで、根から全頂点へ届く最小コストの辺の集合}
acl: []
verify: [directedmst, manhattanmst]
frequency: C
frequency_evidence: recent 0・前提として届くページなし・古い ABC 0 問
sections:
  - {title: Borůvka 法, anchor: boruvka}
  - {title: Manhattan MST, anchor: manhattan}
  - {title: 最小有向全域木（Chu-Liu/Edmonds）, anchor: directed}
  - {title: 第 2 最小全域木, anchor: second-best}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：辺が暗黙に与えられる完全グラフの最小全域木を Borůvka 法で求め、マンハッタン距離の完全グラフは候補辺を O(N) 本に絞る。有向グラフの最小全域木（Chu-Liu/Edmonds）と第 2 最小全域木の求め方もある。
    - **いつ使うか**：
        - 辺が暗黙に O(N^2) 本ある完全グラフの最小全域木
        - マンハッタン距離の完全グラフ
        - 有向グラフで、根から全頂点へ届く最小コストの辺の集合
    - **計算量**：（執筆時に書く）
    - **前提**：[最小全域木](../graph/minimum-spanning-tree.md)
