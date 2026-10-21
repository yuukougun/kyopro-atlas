---
id: dp-speedup-overview
title: DP の高速化の選び方
aliases: [DP の高速化, DP 高速化, DP 最適化, DP Optimization, 遷移の高速化]
type: hub
field: dp
chapter: DP の高速化
order: 310
level: null
kind: [DP, 案内]
prerequisites: [dp-basics]
related: [dp-prefix-sum, dp-segment-tree, inline-dp, dp-dimension-reduction, bitset-speedup#subset-sum-shift, online-convolution#dp-as-polynomial, fps-basics, matrix-power#dp-transition, cht, monge, alien-dp, slope-trick]
summary: 素直な DP が間に合わないとき、貰う形の式の右辺の形（区間の和・区間の最小・多項式の積・同じ線形の遷移の繰り返し・一次関数の最小など）から速くする道具を選ぶ。
complexity: null
signs:
  - {type: shape, text: 素直に書いた DP の遷移が状態 1 つあたり O(N) かかり、全体で O(N^2) になる}
acl: []
sections:
  - {title: 状態を減らすか、遷移を速くするか, anchor: two-directions}
  - {title: 貰う形の式を書き、右辺の形を見る, anchor: read-the-recurrence}
  - {title: 早見表：遷移の形から道具を選ぶ, anchor: shape-to-tool}
  - {title: 多項式の積・同じ線形の遷移の繰り返し（畳み込み・行列累乗へ）, anchor: algebraic-tools}
  - {title: 凸性を使う高速化（CHT・Monge・Alien DP・Slope Trick）の使いどころ, anchor: convexity}
  - {title: 落とし穴：式を書かずに道具から考える・累積和とセグメント木の取り違え, anchor: pitfalls}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何のページか**：素直な DP が間に合わないとき、貰う形の式の右辺の形（区間の和・区間の最小・多項式の積・同じ線形の遷移の繰り返し・一次関数の最小など）から速くする道具を選ぶ。
    - **いつ使うか**：素直に書いた DP の遷移が状態 1 つあたり O(N) かかり、全体で O(N^2) になる
    - **使い方**：（執筆時に書く）
    - **前提**：[DP の基本](../dp/dp-basics.md)
