---
id: tree-dp-square
title: 二乗の木 DP
aliases: [2 乗の木 DP, O(N^2) の木 DP, 木の上のナップサック]
type: technique
field: dp
chapter: 状態の形で分かれる DP
order: 290
level: 黄
kind: [DP, 木]
prerequisites: [tree-dp, knapsack-01]
related: [small-to-large, subset-sum]
summary: 子の配列を順にマージする木の上のナップサックのような DP は、配列の長さを部分木のサイズに合わせると全体 O(N^2) で済む。どの頂点の組も、LCA でのマージで 1 回だけ数えられるからである。
complexity: null
signs:
  - {type: constraint, text: N ≤ 2000〜5000 の木}
  - {type: phrase, text: 部分木から K 個選ぶ・連結成分の数ごとに数える}
  - {type: shape, text: 'dp[v][k] を子の dp[c][j] との (k, j) の組の全探索でマージしていて、O(N^3) に見える'}
acl: []
frequency: C
frequency_evidence: recent 0・前提として届くページなし・古い ABC 2 問
sections:
  - {title: O(N^2) で済む理由（頂点の組が LCA で 1 回だけ数えられる）, anchor: why-n2}
  - {title: 配列の長さを部分木のサイズに合わせる, anchor: size-bounded}
  - {title: サイズを K で打ち切ると O(NK), anchor: cap-k}
  - {title: 頂点の状態と個数を同時に持つ, anchor: state-and-count}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：子の配列を順にマージする木の上のナップサックのような DP は、配列の長さを部分木のサイズに合わせると全体 O(N^2) で済む。どの頂点の組も、LCA でのマージで 1 回だけ数えられるからである。
    - **いつ使うか**：
        - N ≤ 2000〜5000 の木
        - 部分木から K 個選ぶ・連結成分の数ごとに数える
        - dp\[v][k] を子の dp\[c][j] との (k, j) の組の全探索でマージしていて、O(N^3) に見える
    - **計算量**：（執筆時に書く）
    - **前提**：[木 DP](../dp/tree-dp.md)、[ナップサック DP](../dp/knapsack-01.md)
