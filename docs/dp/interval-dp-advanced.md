---
id: interval-dp-advanced
title: 区間 DP の応用
aliases: [区間 DP で木を数える, 区間ゲーム]
type: technique
field: dp
chapter: 状態の形で分かれる DP
order: 210
level: 黄
kind: [DP, 数え上げ]
prerequisites: [interval-dp, binomial-coefficient]
related: [tree-dp, grundy-number#dp, euler-tour, digit-dp]
summary: 区間 DP の上で、DFS 順の区間を部分木とみる木の数え上げ、区間ごとの Grundy 数、訪れた範囲の両端を状態にする移動などを解く。区間の内と外を独立に数え、順序を二項係数で混ぜる設計が多い。
complexity: null
signs:
  - {type: phrase, text: 頂点を訪れた順（行きがけ順）が与えられたときの根付き木の数}
  - {type: phrase, text: 区間を選び合うゲームの勝敗}
  - {type: phrase, text: 数直線上を左右に動き、訪れた範囲が常に連続している}
  - {type: constraint, text: N ≤ 400 前後}
acl: []
frequency: B
frequency_evidence: recent 0・前提として届くページなし・古い ABC 7 問
sections:
  - {title: DFS 順の区間＝部分木（木の数え上げ）, anchor: dfs-order-trees}
  - {title: 区間ごとの Grundy 数（ゲーム）, anchor: grundy}
  - {title: 訪れた区間の両端と今いる端を状態にする, anchor: visited-range}
  - {title: '桁と区間で分ける（''?'' を含む数の列）', anchor: digits-and-ranges}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：区間 DP の上で、DFS 順の区間を部分木とみる木の数え上げ、区間ごとの Grundy 数、訪れた範囲の両端を状態にする移動などを解く。区間の内と外を独立に数え、順序を二項係数で混ぜる設計が多い。
    - **いつ使うか**：
        - 頂点を訪れた順（行きがけ順）が与えられたときの根付き木の数
        - 区間を選び合うゲームの勝敗
        - 数直線上を左右に動き、訪れた範囲が常に連続している
        - N ≤ 400 前後
    - **計算量**：（執筆時に書く）
    - **前提**：[区間 DP](../dp/interval-dp.md)、[二項係数の意味と性質](../comb/binomial-coefficient.md)
