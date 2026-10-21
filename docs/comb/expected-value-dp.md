---
id: expected-value-dp
title: 期待値 DP
aliases: [後ろから決める期待値, 残りの期待値, 全期待値の公式, 自己ループ, 振り直し, 移項して解く, 選択は max・偶然は平均]
type: technique
field: comb
chapter: 確率・期待値
order: 380
level: 水
kind: [確率・期待値, DP]
prerequisites: [linearity-of-expectation, dp-order]
related: [probability-dp, rational-mod, optimal-strategy-expectation, expectation-linear-equations, coupon-collector, dp-prefix-sum, memoized-recursion]
summary: 終わるまでの量の期待値 E[s] を、最初の一手で場合分けした E[s] = c(s) + Σ P(s→t) E[t] で、終状態の E = 0 から後ろ向きに埋める。自己ループは移項して消し、選択がある状態では max を取る。
complexity: null
signs:
  - {type: phrase, text: 〜になるまでの操作回数の期待値}
  - {type: phrase, text: 終わるまでにかかる費用の期待値}
  - {type: phrase, text: 出た目が〜なら振り直し・確率 p で何も起きない}
  - {type: constraint, text: 状態数 N ≤ 10^5 程度で、各状態の遷移が少数（または区間）}
  - {type: shape, text: 'E[s] が、s から 1 手で移る状態の E の平均に定数を足した式になる'}
acl: [modint]
frequency: B
frequency_evidence: recent 0・前提として 2 ページに届く（直接 2）・古い ABC 9 問
sections:
  - {title: 全期待値の公式（最初の一手で場合分け）, anchor: total-expectation}
  - {title: なぜ後ろ向きか（終状態が 0 の境界条件）, anchor: why-backward}
  - {title: 状態の設計：区別しない・個数の組にする, anchor: state-design}
  - {title: 計算順序とメモ化再帰, anchor: order}
  - {title: 自己ループの移項 E = (c + Σ …)/(1 − p), anchor: self-loop}
  - {title: 選択がある期待値：選択は max、偶然は平均, anchor: choice}
  - {title: 遷移を累積和でまとめる, anchor: prefix-sum, level: 青}
  - {title: 前向きの確率 DP との使い分け, anchor: vs-probability-dp}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：終わるまでの量の期待値 E[s] を、最初の一手で場合分けした E[s] = c(s) + Σ P(s→t) E[t] で、終状態の E = 0 から後ろ向きに埋める。自己ループは移項して消し、選択がある状態では max を取る。
    - **いつ使うか**：
        - 〜になるまでの操作回数の期待値
        - 終わるまでにかかる費用の期待値
        - 出た目が〜なら振り直し・確率 p で何も起きない
        - 状態数 N ≤ 10^5 程度で、各状態の遷移が少数（または区間）
        - E[s] が、s から 1 手で移る状態の E の平均に定数を足した式になる
    - **計算量**：（執筆時に書く）
    - **前提**：[期待値の線形性と指示確率変数](../comb/linearity-of-expectation.md)、[DP の計算順序](../dp/dp-order.md)
