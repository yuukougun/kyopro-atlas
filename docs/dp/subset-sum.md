---
id: subset-sum
title: 部分和 DP
aliases: [部分和, 部分和問題, Subset Sum, 部分和の数え上げ]
type: technique
field: dp
chapter: 列の DP
order: 110
level: 基礎
kind: [DP]
prerequisites: [dp-basics]
related: [knapsack-01, knapsack-undo, meet-in-the-middle, bitset-speedup#subset-sum-shift, dp-mod-state, exchange-argument-dp]
summary: いくつか選んで作れる和の集合や、和が S になる選び方の数を、和を添字にした DP で求める。2 グループへの分け方や ± の符号の付け方も、部分和に言い換えて解ける。
complexity: null
signs:
  - {type: phrase, text: いくつか選んで和をちょうど S にできるか・その選び方の数}
  - {type: phrase, text: 2 つのグループに分けて差（遅い方）を最小にする}
  - {type: phrase, text: 各要素に + か − を付けて和を K にする}
  - {type: constraint, text: N ≤ 100、値の総和 ≤ 10^5 程度}
acl: []
frequency: B
frequency_evidence: recent 0・前提として 1 ページに届く（直接 1）・古い ABC 7 問
sections:
  - {title: 可否・数え上げ・最大の 3 つの形, anchor: three-forms}
  - {title: 典型の言い換え（2 グループに分ける・± の和・x と y が独立）, anchor: reformulations}
  - {title: 最大値を固定するためにソートしてから数える, anchor: sort-then-count, level: 水}
  - {title: 全部分集合についての和（含む部分集合の数を重みにする）, anchor: over-all-subsets, level: 青}
  - {title: 落とし穴：負の和のオフセット・空集合を数えるか, anchor: pitfalls}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：いくつか選んで作れる和の集合や、和が S になる選び方の数を、和を添字にした DP で求める。2 グループへの分け方や ± の符号の付け方も、部分和に言い換えて解ける。
    - **いつ使うか**：
        - いくつか選んで和をちょうど S にできるか・その選び方の数
        - 2 つのグループに分けて差（遅い方）を最小にする
        - 各要素に + か − を付けて和を K にする
        - N ≤ 100、値の総和 ≤ 10^5 程度
    - **計算量**：（執筆時に書く）
    - **前提**：[DP の基本](../dp/dp-basics.md)
