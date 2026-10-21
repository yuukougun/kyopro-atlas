---
id: slope-trick
title: Slope Trick
aliases: [スロープトリック, 区分線形凸関数, 区分線形凸関数の管理]
type: overview
field: dp
chapter: DP の高速化
order: 380
level: 発展
kind: [DP, データ構造]
prerequisites: [dp-state-design, top-k-multiset]
related: [priority-queue, median-absolute, monge, alien-dp, small-to-large#subtree-merge, greedy-priority-queue#regret]
summary: dp[x] が x について区分線形で凸なとき、傾きが変わる点を 2 つの優先度付きキューで持ち、「|x − a| を足す」「累積 min を取る」「平行移動」を 1 回 O(log N) で行う。
complexity: null
signs:
  - {type: phrase, text: 数列を単調（広義増加）にするための、値の変更量の和の最小}
  - {type: phrase, text: 時刻ごとに位置を少しずつ動かせるときの最小コスト}
  - {type: shape, text: 'dp[i][x] = min_{y ≤ x} dp[i−1][y] + |x − a_i| のように、x について区分線形で凸'}
acl: []
frequency: B
frequency_evidence: recent 1（abc458_g）・前提として届くページなし・古い ABC 2 問
sections:
  - {title: 凸関数を傾きの変わる点の集まりで表す, anchor: breakpoints}
  - {title: 2 つのヒープで中央値を管理する（入口）, anchor: two-heaps}
  - {title: '|x − a| を足す・累積 min・平行移動', anchor: operations}
  - {title: 木の上で凸関数をマージする（マージテクと組む）, anchor: on-trees}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：dp[x] が x について区分線形で凸なとき、傾きが変わる点を 2 つの優先度付きキューで持ち、「|x − a| を足す」「累積 min を取る」「平行移動」を 1 回 O(log N) で行う。
    - **いつ使うか**：
        - 数列を単調（広義増加）にするための、値の変更量の和の最小
        - 時刻ごとに位置を少しずつ動かせるときの最小コスト
        - dp\[i][x] = min_{y ≤ x} dp\[i−1][y] + |x − a_i| のように、x について区分線形で凸
    - **計算量**：（執筆時に書く）
    - **前提**：[DP の状態の設計](../dp/dp-state-design.md)、[上位 K 個の和と中央値の管理](../ds/top-k-multiset.md)
