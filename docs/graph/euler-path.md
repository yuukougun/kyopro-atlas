---
id: euler-path
title: オイラー路（一筆書き）
aliases: [オイラー閉路, 一筆書き, Hierholzer, Euler path, Eulerian trail]
type: technique
field: graph
chapter: 探索木と次数の性質
order: 370
level: 黄
kind: [グラフ探索]
prerequisites: [connected-components]
related: [bit-dp, graph-modeling, matrix-tree-theorem, euler-tour]
summary: すべての辺をちょうど 1 回ずつ通る路は、辺のある頂点が連結で、奇数次数の頂点が 0 個か 2 個（有向なら入次数と出次数の条件）のときに限りあり、Hierholzer 法で O(M) で作れる。
complexity: null
signs:
  - {type: phrase, text: すべての辺をちょうど 1 回ずつ通る・一筆書き}
  - {type: phrase, text: 同じ道を 2 度通らずにすべての道を通れるか}
acl: []
verify: [eulerian_trail_directed, eulerian_trail_undirected]
frequency: C
frequency_evidence: recent 0・前提として届くページなし・古い ABC 1 問
sections:
  - {title: 存在条件（無向・有向）, anchor: conditions}
  - {title: Hierholzer 法で構成する, anchor: hierholzer}
  - {title: 孤立点・多重辺・自己ループの扱い, anchor: pitfalls}
  - {title: ハミルトン路（頂点をちょうど 1 回、bitDP）との違い, anchor: vs-hamiltonian}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：すべての辺をちょうど 1 回ずつ通る路は、辺のある頂点が連結で、奇数次数の頂点が 0 個か 2 個（有向なら入次数と出次数の条件）のときに限りあり、Hierholzer 法で O(M) で作れる。
    - **いつ使うか**：
        - すべての辺をちょうど 1 回ずつ通る・一筆書き
        - 同じ道を 2 度通らずにすべての道を通れるか
    - **計算量**：（執筆時に書く）
    - **前提**：[連結成分](../graph/connected-components.md)
