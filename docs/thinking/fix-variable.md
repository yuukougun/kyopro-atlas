---
id: fix-variable
title: 一部を固定して数える
aliases: [決め打ち, 固定して全探索, 真ん中を固定, 片方を固定, 最大値を固定, fix one variable]
type: thinking
field: thinking
order: 20
level: 基礎
kind: [考察, 全探索]
prerequisites: [brute-force]
related: [binary-search, contribution, counting-fix-order, greedy-priority-queue]
summary: 変数の一部（3 つ組の真ん中・最大値・余りなど）を固定すると、残りの条件が単純になって独立に数えられる。固定したあとは二分探索・累積和・連想配列で残りを速く数える。
complexity: null
signs:
  - {type: phrase, text: 3 つ組 (i < j < k) を数える}
  - {type: phrase, text: 2 つの値の組で、片方を決めればもう片方の条件が単純になる}
  - {type: phrase, text: 最大値（最小値）を決めて残りを最適化する}
  - {type: constraint, text: N ≤ 2×10^5 で 3 つ組は N^3 通りあり、全部は試せない}
acl: []
frequency: A
frequency_evidence: recent 4（abc453_e・abc458_e・abc461_d・abc467_e）・前提として届くページなし・古い ABC 3 問
sections:
  - {title: 真ん中を固定して左右を独立に数える, anchor: fix-middle}
  - {title: 角・余り・平方因子を除いた部分を固定する, anchor: fix-parts}
  - {title: 最大値を固定して残りを最適化する, anchor: fix-maximum}
  - {title: 固定したあとを速くする（二分探索・累積和・連想配列）, anchor: speed-up}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：変数の一部（3 つ組の真ん中・最大値・余りなど）を固定すると、残りの条件が単純になって独立に数えられる。固定したあとは二分探索・累積和・連想配列で残りを速く数える。
    - **いつ使うか**：
        - 3 つ組 (i < j < k) を数える
        - 2 つの値の組で、片方を決めればもう片方の条件が単純になる
        - 最大値（最小値）を決めて残りを最適化する
        - N ≤ 2×10^5 で 3 つ組は N^3 通りあり、全部は試せない
    - **計算量**：（執筆時に書く）
    - **前提**：[全探索の設計](../basics/brute-force.md)
