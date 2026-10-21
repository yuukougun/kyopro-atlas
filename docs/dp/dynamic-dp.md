---
id: dynamic-dp
title: 動的 DP
aliases: [Dynamic DP, DDP, 遷移行列のセグメント木]
type: overview
field: dp
chapter: DP の高速化
order: 340
level: 発展
kind: [DP, 線形代数・行列, 区間クエリ]
prerequisites: [matrix-power, segment-tree-monoids]
related: [segment-tree, static-top-tree, subsequence-dp]
summary: 列の各位置の遷移を小さな行列にしてセグメント木に載せると、1 点の書き換えのたびに DP の答えを O(S^3 log N) で求め直せる。行列の積は非可換なので、掛ける向きを最初に決める。
complexity: null
signs:
  - {type: phrase, text: DP をする列に 1 点更新のクエリが来て、そのたびに DP の答えを求める}
  - {type: phrase, text: '列の区間 [l, r] だけで DP をしたときの答えを、クエリごとに求める'}
acl: [segtree]
verify: [point_set_range_composite]
frequency: C
frequency_evidence: recent 0・前提として届くページなし・古い ABC 1 問
sections:
  - {title: 何ができるか（1 点更新と区間の DP の答え）, anchor: what-it-does}
  - {title: 遷移を行列にしてセグメント木に載せる（ACL の segtree の S を行列にする）, anchor: matrix-on-segment-tree}
  - {title: 積の向きと単位行列, anchor: order-and-identity}
  - {title: 木の上の動的 DP（Static Top Tree へ）, anchor: on-trees}
  - {title: ライブラリでの検証（Library Checker の point_set_range_composite が土台）, anchor: verify}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：列の各位置の遷移を小さな行列にしてセグメント木に載せると、1 点の書き換えのたびに DP の答えを O(S^3 log N) で求め直せる。行列の積は非可換なので、掛ける向きを最初に決める。
    - **いつ使うか**：
        - DP をする列に 1 点更新のクエリが来て、そのたびに DP の答えを求める
        - 列の区間 [l, r] だけで DP をしたときの答えを、クエリごとに求める
    - **計算量**：（執筆時に書く）
    - **前提**：[行列累乗](../math/matrix-power.md)、[セグメント木に何を載せるか](../ds/segment-tree-monoids.md)
