---
id: k-shortest-paths
title: K 番目の最短路
aliases: [k shortest paths, K 番目に短い経路, Eppstein, Yen]
type: overview
field: graph
chapter: 最短路
order: 220
level: 発展
kind: [最短路]
prerequisites: [dijkstra]
related: [extended-dijkstra]
summary: 始点から終点への経路のうち、短い方から K 番目の長さを求める。歩道なら各頂点を K 回まで取り出すダイクストラで求まり、単純パスは Yen、歩道の列挙は Eppstein の方法を使う。
complexity: null
signs:
  - {type: phrase, text: K 番目に短い経路・歩道の長さ}
acl: []
verify: [k_shortest_walk]
frequency: C
frequency_evidence: recent 0・前提として届くページなし・古い ABC 0 問
sections:
  - {title: 各頂点を K 回まで取り出すダイクストラ, anchor: k-times}
  - {title: 単純パス（Yen）と歩道（Eppstein）, anchor: yen-eppstein}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：始点から終点への経路のうち、短い方から K 番目の長さを求める。歩道なら各頂点を K 回まで取り出すダイクストラで求まり、単純パスは Yen、歩道の列挙は Eppstein の方法を使う。
    - **いつ使うか**：K 番目に短い経路・歩道の長さ
    - **計算量**：（執筆時に書く）
    - **前提**：[ダイクストラ法](../graph/dijkstra.md)
