---
id: chromatic-number
title: 彩色数・最大独立集合・最大クリーク
aliases: [彩色数, 頂点彩色, 最大クリーク, 一般グラフの最大独立集合, chromatic number, maximum independent set]
type: overview
field: graph
chapter: 基本と探索
order: 100
level: 発展
kind: [DP, 数え上げ]
prerequisites: [bit-dp, inclusion-exclusion]
related: [small-graph-brute-force, konig-theorem, meet-in-the-middle, bipartite-graph]
summary: 一般グラフの彩色数・最大独立集合・最大クリークは NP 困難で、彩色数は包除原理で O(2^N N)、最大独立集合は N ≤ 40 程度なら分枝や半分全列挙で求める。二部グラフなら易しい。
complexity: null
signs:
  - {type: constraint, text: N ≤ 20〜40 の一般グラフで、独立集合・彩色・クリークを求める}
acl: []
verify: [chromatic_number, maximum_independent_set]
frequency: C
frequency_evidence: recent 0・前提として届くページなし・古い ABC 0 問
sections:
  - {title: 彩色数（包除原理で O(2^N N)）, anchor: chromatic-number}
  - {title: 最大独立集合（分枝・半分全列挙）, anchor: independent-set}
  - {title: 二部グラフなら König の定理, anchor: bipartite-case}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：一般グラフの彩色数・最大独立集合・最大クリークは NP 困難で、彩色数は包除原理で O(2^N N)、最大独立集合は N ≤ 40 程度なら分枝や半分全列挙で求める。二部グラフなら易しい。
    - **いつ使うか**：N ≤ 20〜40 の一般グラフで、独立集合・彩色・クリークを求める
    - **計算量**：（執筆時に書く）
    - **前提**：[bitDP](../dp/bit-dp.md)、[包除原理](../comb/inclusion-exclusion.md)
