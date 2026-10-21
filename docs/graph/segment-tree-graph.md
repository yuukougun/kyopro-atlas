---
id: segment-tree-graph
title: 区間に辺を張る
aliases: [区間に辺を張るテク, セグ木グラフ, セグメント木の形の補助頂点, segment tree graph]
type: overview
field: graph
chapter: 最短路
order: 210
level: 発展
kind: [最短路, データ構造]
prerequisites: [extended-dijkstra, segment-tree]
related: [dijkstra]
summary: 頂点から区間内の全頂点へ辺がある問題で、セグメント木のノードを補助頂点にして区間を O(log N) 個で覆い、辺の数を O(M log N) に減らして最短路を求める。
complexity: null
signs:
  - {type: phrase, text: 頂点から区間内の全頂点へ移動できる・区間から区間へ移動できる}
acl: []
frequency: C
frequency_evidence: recent 0・前提として届くページなし・古い ABC 1 問
sections:
  - {title: 下向きの木と上向きの木（コスト 0 の辺）, anchor: two-trees}
  - {title: 区間を O(log N) 個のノードで覆う, anchor: cover}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：頂点から区間内の全頂点へ辺がある問題で、セグメント木のノードを補助頂点にして区間を O(log N) 個で覆い、辺の数を O(M log N) に減らして最短路を求める。
    - **いつ使うか**：頂点から区間内の全頂点へ移動できる・区間から区間へ移動できる
    - **計算量**：（執筆時に書く）
    - **前提**：[状態を頂点にする](../graph/extended-dijkstra.md)、[セグメント木](../ds/segment-tree.md)
