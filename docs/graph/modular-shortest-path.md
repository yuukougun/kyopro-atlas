---
id: modular-shortest-path
title: 剰余を頂点にする最短路
aliases: [同余最短路, 剰余グラフ, mod を頂点に]
type: overview
field: graph
chapter: 最短路
order: 200
level: 発展
kind: [最短路, 整数論]
prerequisites: [zero-one-bfs, extended-dijkstra]
related: [digit-and-mod]
summary: K で割った余りを頂点、数を作る操作を辺にした最短路で、K の倍数のうち桁和が最小のものや、いくつかの数の和で作れる数を求める。
complexity: null
signs:
  - {type: phrase, text: K の倍数のうち桁和などが最小のもの}
  - {type: phrase, text: いくつかの数の和で作れる数の集合（硬貨の組合せ）}
  - {type: constraint, text: K が 10^5〜10^6 程度}
acl: []
frequency: C
frequency_evidence: recent 0・前提として届くページなし・古い ABC 0 問
sections:
  - {title: 余りを頂点、操作を辺にする, anchor: residue-vertices}
  - {title: 同余最短路（最小の数で割った余りごとの最小値）, anchor: congruence}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：K で割った余りを頂点、数を作る操作を辺にした最短路で、K の倍数のうち桁和が最小のものや、いくつかの数の和で作れる数を求める。
    - **いつ使うか**：
        - K の倍数のうち桁和などが最小のもの
        - いくつかの数の和で作れる数の集合（硬貨の組合せ）
        - K が 10&#94;5〜10&#94;6 程度
    - **計算量**：（執筆時に書く）
    - **前提**：[01-BFS](../graph/zero-one-bfs.md)、[状態を頂点にする](../graph/extended-dijkstra.md)
