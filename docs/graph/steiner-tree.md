---
id: steiner-tree
title: 最小シュタイナー木
aliases: [シュタイナー木, Steiner tree, Dreyfus-Wagner]
type: overview
field: graph
chapter: 最短路
order: 230
level: 発展
kind: [最短路, DP]
prerequisites: [dijkstra, subset-enumeration-dp]
related: [minimum-spanning-tree, steiner-subtree]
summary: 一般のグラフで指定した K 点（K ≤ 10 程度）をすべてつなぐ最小コストを、端点の集合と頂点を状態にした DP で O(3^K N + 2^K M log N) で求める。部分集合の分割とダイクストラを交互に行う。
complexity: null
signs:
  - {type: constraint, text: 指定した K 点（K ≤ 10 程度）をすべて連結にする最小コスト}
acl: []
verify: [minimum_steiner_tree]
frequency: C
frequency_evidence: recent 0・前提として届くページなし・古い ABC 2 問
sections:
  - {title: 'dp[S][v] の定義', anchor: state}
  - {title: 部分集合を 2 つに分けて合わせる遷移, anchor: merge}
  - {title: ダイクストラで v を動かす遷移, anchor: dijkstra-step}
  - {title: 木の上なら易しい（木の章の「指定頂点を結ぶ最小の部分木」）, anchor: on-tree}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：一般のグラフで指定した K 点（K ≤ 10 程度）をすべてつなぐ最小コストを、端点の集合と頂点を状態にした DP で O(3^K N + 2^K M log N) で求める。部分集合の分割とダイクストラを交互に行う。
    - **いつ使うか**：指定した K 点（K ≤ 10 程度）をすべて連結にする最小コスト
    - **計算量**：（執筆時に書く）
    - **前提**：[ダイクストラ法](../graph/dijkstra.md)、[部分集合を列挙する DP](../dp/subset-enumeration-dp.md)
