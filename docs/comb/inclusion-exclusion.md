---
id: inclusion-exclusion
title: 包除原理
aliases: [包除, 撹乱順列, 完全順列, モンモール数, 全射の数, min-max 包除, inclusion-exclusion principle, derangement]
type: technique
field: comb
chapter: 包除の系統
order: 180
level: 青
kind: [数え上げ]
prerequisites: [counting-mindset, complement, bit-full-search]
related: [inclusion-exclusion-dp, divisor-inclusion-exclusion, twelvefold-way, bell-number, stars-and-bars, zeta-mobius-subset, coupon-collector, chromatic-number]
summary: どの条件も破らないものの個数を、条件の集合 S を少なくとも破るものの個数 N(S) の符号付きの和 Σ(−1)^|S| N(S) で求める。条件が少なければ bit 全探索し、対称なら破る個数ごとに足して撹乱順列や全射の数も求める。
complexity: null
signs:
  - {type: phrase, text: すべて異なる・A_i ≠ B_i となるものの個数}
  - {type: phrase, text: どの禁止条件も満たさないものの個数}
  - {type: phrase, text: 各色（各行・各列）を少なくとも 1 回使うものの個数}
  - {type: constraint, text: 禁止条件が M ≤ 20 個程度}
acl: []
frequency: A
frequency_evidence: recent 3（abc456_g・abc462_g・abc475_f）・前提として 2 ページに届く（直接 2）・古い ABC 7 問
sections:
  - {title: 一般形と、N(S) が「少なくとも」である理由, anchor: general}
  - {title: 条件の組を bit 全探索する（M ≤ 20）, anchor: bit-enumeration}
  - {title: 対称なら破る個数 k ごとに足す, anchor: symmetric}
  - {title: 撹乱順列（完全順列）, anchor: derangement}
  - {title: 全射の数（各色を少なくとも 1 回使う）, anchor: surjection}
  - {title: 使い分け：余事象・包除 DP・約数包除, anchor: when-to-use}
  - {title: min-max 包除（全種類がそろうまでの期待値）, anchor: min-max, level: 発展}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：どの条件も破らないものの個数を、条件の集合 S を少なくとも破るものの個数 N(S) の符号付きの和 Σ(−1)^|S| N(S) で求める。条件が少なければ bit 全探索し、対称なら破る個数ごとに足して撹乱順列や全射の数も求める。
    - **いつ使うか**：
        - すべて異なる・A_i ≠ B_i となるものの個数
        - どの禁止条件も満たさないものの個数
        - 各色（各行・各列）を少なくとも 1 回使うものの個数
        - 禁止条件が M ≤ 20 個程度
    - **計算量**：（執筆時に書く）
    - **前提**：[数え上げの考え方](../comb/counting-mindset.md)、[余事象](../thinking/complement.md)、[bit 全探索と順列全探索](../basics/bit-full-search.md)
