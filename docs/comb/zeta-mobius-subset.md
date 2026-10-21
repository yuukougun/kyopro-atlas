---
id: zeta-mobius-subset
title: 部分集合の高速ゼータ変換とメビウス変換
aliases: [高速ゼータ変換, 高速メビウス変換, SOS DP, 部分集合にわたる和, 上位集合の和, OR 畳み込み, AND 畳み込み, zeta transform]
type: technique
field: comb
chapter: 包除の系統
order: 230
level: 黄
kind: [数え上げ, ビット演算, 畳み込み・多項式]
prerequisites: [bit-full-search, prefix-sum-2d]
related: [zeta-mobius-divisor, inclusion-exclusion, hadamard-transform, bit-dp, subset-enumeration-dp]
summary: すべての集合 S について、部分集合（上位集合）にわたる和を bit ごとの累積和として O(n 2^n) で求める（素朴には O(3^n)）。逆変換（メビウス変換）で戻せ、OR・AND 畳み込みは変換 → 各点の積 → 逆変換で求める。
complexity: null
signs:
  - {type: constraint, text: N ≤ 20 で、すべての部分集合（bit）ごとの和・最大を求める}
  - {type: phrase, text: A_i OR A_j が K の部分集合になる組}
  - {type: phrase, text: x ⊆ S となる x についての和を、すべての S で求める}
acl: []
verify: [bitwise_and_convolution]
frequency: C
frequency_evidence: recent 0・前提として届くページなし・古い ABC 2 問
sections:
  - {title: n 次元の累積和として見る（bit ごとに 1 軸ずつ）, anchor: multidimensional}
  - {title: ループの順（bit を外側）, anchor: loop-order}
  - {title: メビウス変換（引き算で同じ順に回す）, anchor: inverse}
  - {title: 上位集合の版, anchor: superset}
  - {title: OR 畳み込み・AND 畳み込み, anchor: or-and-convolution}
  - {title: 和の代わりに上位 2 つを持つ, anchor: top-two}
  - {title: XOR 畳み込みとの違い, anchor: vs-xor}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：すべての集合 S について、部分集合（上位集合）にわたる和を bit ごとの累積和として O(n 2^n) で求める（素朴には O(3^n)）。逆変換（メビウス変換）で戻せ、OR・AND 畳み込みは変換 → 各点の積 → 逆変換で求める。
    - **いつ使うか**：
        - N ≤ 20 で、すべての部分集合（bit）ごとの和・最大を求める
        - A_i OR A_j が K の部分集合になる組
        - x ⊆ S となる x についての和を、すべての S で求める
    - **計算量**：（執筆時に書く）
    - **前提**：[bit 全探索と順列全探索](../basics/bit-full-search.md)、[2 次元累積和](../basics/prefix-sum-2d.md)
