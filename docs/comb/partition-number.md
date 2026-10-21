---
id: partition-number
title: 整数の分割と分割数
aliases: [分割数, 'p(n,k)', 分割の全列挙, 巡回型, partition number, integer partition]
type: technique
field: comb
chapter: 置換・分割・木の数え上げ
order: 280
level: 黄
kind: [数え上げ, DP]
prerequisites: [recursive-enumeration, dp-basics, permutation-cycles]
related: [twelvefold-way, stars-and-bars, bell-number, young-tableaux, stirling-first, knapsack-01]
summary: n を順序を区別せずに正の整数の和で表す方法の数が分割数 p(n) で、p(n,k) = p(n,k−1) + p(n−k,k) で数える。降順の列だけを作れば重複なく全列挙でき、p(50) = 204226 と少ない。
complexity: null
signs:
  - {type: constraint, text: N ≤ 50 程度で、長さ（個数）の組合せ（多重集合）を全部試す}
  - {type: phrase, text: 和が N になる多重集合の個数}
  - {type: phrase, text: 区別のない玉を区別のない箱へ配る方法の数}
  - {type: phrase, text: 順列を巡回の長さの組ごとに分類して数える}
acl: []
frequency: B
frequency_evidence: recent 0・前提として 1 ページに届く（直接 1）・古い ABC 3 問
sections:
  - {title: '分割数の漸化式 p(n,k)', anchor: recurrence}
  - {title: 降順の列だけを作る全列挙, anchor: enumeration}
  - {title: 全列挙の個数の見積もり（p(30) = 5604、p(50) = 204226）, anchor: size}
  - {title: 置換の巡回型ごとの数 N!/Π(ℓ^m_ℓ · m_ℓ!), anchor: cycle-type}
  - {title: 分割数型の DP, anchor: partition-dp, level: 発展}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：n を順序を区別せずに正の整数の和で表す方法の数が分割数 p(n) で、p(n,k) = p(n,k−1) + p(n−k,k) で数える。降順の列だけを作れば重複なく全列挙でき、p(50) = 204226 と少ない。
    - **いつ使うか**：
        - N ≤ 50 程度で、長さ（個数）の組合せ（多重集合）を全部試す
        - 和が N になる多重集合の個数
        - 区別のない玉を区別のない箱へ配る方法の数
        - 順列を巡回の長さの組ごとに分類して数える
    - **計算量**：（執筆時に書く）
    - **前提**：[再帰による全列挙](../basics/recursive-enumeration.md)、[DP の基本](../dp/dp-basics.md)、[置換の巡回分解](../comb/permutation-cycles.md)
