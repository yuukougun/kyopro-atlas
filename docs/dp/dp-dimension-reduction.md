---
id: dp-dimension-reduction
title: DP の状態の削減
aliases: [状態の削減, 次元の削減, 状態の圧縮, 値と添字の入れ替え, キーと値を入れ替える, 添字と値を逆に, 上限で打ち切る]
type: technique
field: dp
chapter: 列の DP
order: 120
level: 青
kind: [DP]
prerequisites: [dp-state-design, knapsack-01]
related: [dp-mod-state, lis, inline-dp, meet-in-the-middle]
summary: DP の表が大きすぎるとき、範囲を上限で打ち切るか、ほかの添字から決まる量・支配される量を値の側に回して状態を減らす。どれを添字に残すかは、範囲が小さい量で決める。
complexity: null
signs:
  - {type: constraint, text: 重さの上限 W ≤ 10^9 で、価値の総和が 10^5 程度}
  - {type: phrase, text: ペナルティが 2^(C−1) のように指数的に増える}
  - {type: shape, text: 'dp[i][a][b] の表が大きすぎ、同じ (i, a) なら b が大きい（小さい）ほど常に良い'}
acl: []
frequency: B
frequency_evidence: recent 0・前提として届くページなし・古い ABC 7 問
sections:
  - {title: 上限で打ち切る（log 回で十分な量・目標以上をまとめる）, anchor: cap}
  - {title: 値と添字の入れ替え（同じ添字なら値が良い方が常に良いとき）, anchor: dp-swap-key-value}
  - {title: どれを添字に残すか（範囲が小さい量を選ぶ）, anchor: which-to-index}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：DP の表が大きすぎるとき、範囲を上限で打ち切るか、ほかの添字から決まる量・支配される量を値の側に回して状態を減らす。どれを添字に残すかは、範囲が小さい量で決める。
    - **いつ使うか**：
        - 重さの上限 W ≤ 10^9 で、価値の総和が 10^5 程度
        - ペナルティが 2^(C−1) のように指数的に増える
        - dp\[i]\[a][b] の表が大きすぎ、同じ (i, a) なら b が大きい（小さい）ほど常に良い
    - **計算量**：（執筆時に書く）
    - **前提**：[DP の状態の設計](../dp/dp-state-design.md)、[ナップサック DP](../dp/knapsack-01.md)
