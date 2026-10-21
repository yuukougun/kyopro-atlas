---
id: dilworth-path-cover
title: 最小パス被覆と Hall の定理
aliases: [最小パス被覆, 最大反鎖, 最小鎖被覆, 結婚定理, マッチングの双対, path cover, Hall's theorem]
type: overview
field: graph
chapter: フロー・マッチング
order: 450
level: 発展
kind: [フロー・マッチング]
prerequisites: [bipartite-matching, scc]
related: [lis, konig-theorem, zeta-mobius-subset, bitset-speedup]
summary: DAG の頂点を最少の本数のパスで覆う数は、頂点を 2 つに分けた二部グラフの最大マッチングから求まる。完全マッチングがあるかは、Hall の定理で部分集合ごとに確かめられる。
complexity: null
signs:
  - {type: phrase, text: 互いに包含しない（比べられない）ものを最大数選ぶ}
  - {type: phrase, text: 最少の本数のパス（鎖）で全頂点を覆う}
  - {type: constraint, text: 種類が 20 程度以下で、部分集合ごとに供給と需要を比べられる}
acl: [mf_graph]
frequency: B
frequency_evidence: recent 0・前提として届くページなし・古い ABC 4 問
sections:
  - {title: DAG の最小パス被覆（頂点を 2 つに分けた二部マッチング）, anchor: path-cover}
  - {title: 推移閉包と最大反鎖（数列なら LIS のページの Dilworth の定理へ）, anchor: antichain}
  - {title: Hall の結婚定理, anchor: hall}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：DAG の頂点を最少の本数のパスで覆う数は、頂点を 2 つに分けた二部グラフの最大マッチングから求まる。完全マッチングがあるかは、Hall の定理で部分集合ごとに確かめられる。
    - **いつ使うか**：
        - 互いに包含しない（比べられない）ものを最大数選ぶ
        - 最少の本数のパス（鎖）で全頂点を覆う
        - 種類が 20 程度以下で、部分集合ごとに供給と需要を比べられる
    - **計算量**：（執筆時に書く）
    - **前提**：[二部マッチング](../graph/bipartite-matching.md)、[強連結成分分解（SCC）](../graph/scc.md)
