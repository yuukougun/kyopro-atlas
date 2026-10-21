---
id: tree-ratio-greedy
title: 比で親に併合する貪欲
aliases: [01 on Tree, 木の上の順序最適化, 比による併合, 親を先に選ぶ制約つきの並べ方]
type: overview
field: tree
chapter: まとめる・分ける
order: 260
level: 発展
kind: [木, 貪欲]
prerequisites: [union-find, exchange-argument]
related: [leaf-first, priority-queue]
summary: 「親を子より先に選ぶ」制約つきで、順番に依存する重み付きの和を最適化する。比が最大の塊は親の塊の直後に訪れてよい（交換論法）ので、優先度付きキューと Union-Find で親の塊へ併合していく。
complexity: null
signs:
  - {type: phrase, text: 親を子より先に選ぶ制約つきで、順番による重み付きの和を最適化する}
acl: [dsu]
verify: [rooted_tree_topological_order_with_minimum_inversions]
frequency: C
frequency_evidence: recent 0・前提として届くページなし・古い ABC 1 問
sections:
  - {title: 比が最大の塊は親の直後に来てよい理由, anchor: why-ratio}
  - {title: Union-Find と優先度付きキューで併合する, anchor: merge-with-heap}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：「親を子より先に選ぶ」制約つきで、順番に依存する重み付きの和を最適化する。比が最大の塊は親の塊の直後に訪れてよい（交換論法）ので、優先度付きキューと Union-Find で親の塊へ併合していく。
    - **いつ使うか**：親を子より先に選ぶ制約つきで、順番による重み付きの和を最適化する
    - **計算量**：（執筆時に書く）
    - **前提**：[Union-Find](../ds/union-find.md)、[交換論法と比較関数の設計](../basics/exchange-argument.md)
