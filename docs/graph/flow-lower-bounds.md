---
id: flow-lower-bounds
title: 最小流量制約付きフロー
aliases: [下限付きフロー, 最小流量制約, flow with demands, flow with lower bounds]
type: overview
field: graph
chapter: フロー・マッチング
order: 460
level: 発展
kind: [フロー・マッチング]
prerequisites: [max-flow]
related: [bipartite-matching, extended-dijkstra]
summary: 辺に「少なくとも L は流す」という下限があるとき、L を先に流したことにして超頂点で過不足を調整し、普通の最大流に帰着する。
complexity: null
signs:
  - {type: phrase, text: この辺には少なくとも L だけ流す}
  - {type: phrase, text: 必ず使う・使ってもよい・使ってはいけないものが混在する割当}
acl: [mf_graph]
frequency: C
frequency_evidence: recent 0・前提として届くページなし・古い ABC 1 問
sections:
  - {title: 下限を先に流したことにする, anchor: pre-flow}
  - {title: 超頂点で過不足を調整して判定する, anchor: super-vertex}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：辺に「少なくとも L は流す」という下限があるとき、L を先に流したことにして超頂点で過不足を調整し、普通の最大流に帰着する。
    - **いつ使うか**：
        - この辺には少なくとも L だけ流す
        - 必ず使う・使ってもよい・使ってはいけないものが混在する割当
    - **計算量**：（執筆時に書く）
    - **前提**：[最大流](../graph/max-flow.md)
