---
id: lis
title: 最長増加部分列
aliases: [LIS, Longest Increasing Subsequence, 最長減少部分列, Dilworth の定理, 増加列への最小分割]
type: technique
field: dp
chapter: 列の DP
order: 170
level: 水
kind: [DP, 二分探索]
prerequisites: [dp-basics, binary-search]
related: [dp-segment-tree, segment-tree, dp-dimension-reduction, inline-dp, lcs, root-path-dfs#undo-log, dilworth-path-cover#antichain, manhattan-chebyshev#rotate-45, subsequence-and-substring#longest]
summary: 列から順序を保って選ぶ増加列の最長を、長さごとの末尾の最小値の配列を二分探索で更新して O(N log N) で求める。値を添字にしたセグメント木を使えば、重み付きや数え上げにも広げられる。
complexity: null
signs:
  - {type: constraint, text: N ≤ 2×10^5 で「部分列」「単調増加」}
  - {type: phrase, text: 最小で何本の増加（減少）列に分けられるか・何色で塗れるか}
  - {type: phrase, text: 抜いて差し込む操作の最小回数}
  - {type: phrase, text: 箱・円を入れ子にできる最大個数}
acl: [segtree]
verify: [longest_increasing_subsequence]
frequency: A
frequency_evidence: recent 3（abc457_g・abc468_f・abc476_g）・前提として届くページなし・古い ABC 5 問
sections:
  - {title: 二分探索版（L が単調になる理由・狭義は lower_bound、広義は upper_bound）, anchor: binary-search}
  - {title: セグメント木版（重み付き・各要素で終わる最長・数え上げ）, anchor: segment-tree}
  - {title: 復元（直前の要素を記録する）, anchor: restore}
  - {title: 各要素が LIS に含まれうるか（前後から 2 回求める）, anchor: contained, level: 青}
  - {title: 2 次元の入れ子（一方は昇順・もう一方は降順に並べる）, anchor: nesting, level: 青}
  - {title: 1 か所だけ変更できる LIS・木の上の LIS, anchor: variants, level: 青}
  - {title: Dilworth の定理（増加列への最小分割数＝最長減少部分列の長さ）, anchor: dilworth, level: 青}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：列から順序を保って選ぶ増加列の最長を、長さごとの末尾の最小値の配列を二分探索で更新して O(N log N) で求める。値を添字にしたセグメント木を使えば、重み付きや数え上げにも広げられる。
    - **いつ使うか**：
        - N ≤ 2×10^5 で「部分列」「単調増加」
        - 最小で何本の増加（減少）列に分けられるか・何色で塗れるか
        - 抜いて差し込む操作の最小回数
        - 箱・円を入れ子にできる最大個数
    - **計算量**：（執筆時に書く）
    - **前提**：[DP の基本](../dp/dp-basics.md)、[二分探索](../basics/binary-search.md)
