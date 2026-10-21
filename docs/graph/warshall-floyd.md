---
id: warshall-floyd
title: ワーシャルフロイド法
aliases: [ワーシャルフロイド, Floyd-Warshall, 全点対最短路, all-pairs shortest paths]
type: technique
field: graph
chapter: 最短路
order: 130
level: 水
kind: [最短路, DP]
prerequisites: [dijkstra, dp-basics]
related: [bellman-ford, bit-full-search, bit-dp, graph-construction, method-comparison]
summary: 経由してよい頂点を 1 つずつ増やす DP で、全点対の最短距離を O(N^3) で求める。負辺があっても使え、辺を 1 本足したときは O(N^2) で更新できる。
complexity: null
signs:
  - {type: constraint, text: N ≤ 400 程度で全点対の距離が要る}
  - {type: phrase, text: 辺を 1 本ずつ追加（削除）するたびに、距離についての値を答える}
  - {type: phrase, text: 訪れる地点の順番を全部試す（地点間の距離が要る）}
acl: []
frequency: B
frequency_evidence: recent 0・前提として届くページなし・古い ABC 7 問
sections:
  - {title: k を一番外のループにする理由, anchor: k-outer}
  - {title: '初期化（d[i][i] = 0・多重辺・INF のあふれ）と負閉路の判定', anchor: init}
  - {title: 辺の追加を O(N^2) で反映する（削除は逆順の追加に）, anchor: add-edge}
  - {title: 距離表を作ってから順列全探索・bitDP, anchor: with-enumeration}
  - {title: 迂回できる辺は不要, anchor: redundant-edges, level: 青}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：経由してよい頂点を 1 つずつ増やす DP で、全点対の最短距離を O(N^3) で求める。負辺があっても使え、辺を 1 本足したときは O(N^2) で更新できる。
    - **いつ使うか**：
        - N ≤ 400 程度で全点対の距離が要る
        - 辺を 1 本ずつ追加（削除）するたびに、距離についての値を答える
        - 訪れる地点の順番を全部試す（地点間の距離が要る）
    - **計算量**：（執筆時に書く）
    - **前提**：[ダイクストラ法](../graph/dijkstra.md)、[DP の基本](../dp/dp-basics.md)
