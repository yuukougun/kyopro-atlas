---
id: dp-sequence-partition
title: 区間分割 DP
aliases: [区間分割型 DP, 仕切りを入れる DP, 列を区切る DP]
type: technique
field: dp
chapter: 列の DP
order: 160
level: 水
kind: [DP]
prerequisites: [dp-prefix-sum]
related: [interval-dp, two-pointers, dp-mod-state, monge, alien-dp]
summary: 列をいくつかの区間に区切る方法の数や最小コストを、最後の区間の左端 j で分けて求める。j の範囲が単調に動くなら尺取りと累積和で、区間の番号に依存するなら番号を状態に足して速くする。
complexity: null
signs:
  - {type: phrase, text: 列をいくつかの連続部分に分ける方法の数}
  - {type: phrase, text: 各区間のコストの和の最小}
  - {type: phrase, text: 各区間が条件を満たすように区切れるか}
  - {type: shape, text: 'dp[i] = Σ（または min）_{j < i, [j, i) が条件を満たす} dp[j]'}
acl: []
frequency: C
frequency_evidence: recent 0・前提として 2 ページに届く（直接 1）・古い ABC 1 問
sections:
  - {title: '最後の区間で分ける（dp[0] = 1 は空の区切り）', anchor: last-block}
  - {title: '区間 DP（dp[l][r]）との違い', anchor: vs-interval-dp}
  - {title: 遷移元の範囲が単調に動く：尺取りと累積和, anchor: two-pointers}
  - {title: 区間の番号に依存する条件：番号を状態に足す, anchor: block-index, level: 青}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：列をいくつかの区間に区切る方法の数や最小コストを、最後の区間の左端 j で分けて求める。j の範囲が単調に動くなら尺取りと累積和で、区間の番号に依存するなら番号を状態に足して速くする。
    - **いつ使うか**：
        - 列をいくつかの連続部分に分ける方法の数
        - 各区間のコストの和の最小
        - 各区間が条件を満たすように区切れるか
        - dp[i] = Σ（または min）\_{j < i, [j, i) が条件を満たす} dp[j]
    - **計算量**：（執筆時に書く）
    - **前提**：[累積和・いもす法による DP の高速化](../dp/dp-prefix-sum.md)
