---
id: monge
title: Monge 性による DP の高速化
aliases: [Monge, 四角不等式, 四辺形不等式, Quadrangle Inequality, monotone minima, 分割統治 DP, Divide and Conquer DP, SMAWK, LARSCH, Knuth-Yao, Knuth's optimization, '(max,+) 畳み込み', min-plus 畳み込み, DP の凸性]
type: overview
field: dp
chapter: DP の高速化
order: 360
level: 発展
kind: [DP, ダブリング・分割統治]
prerequisites: [dp-sequence-partition, divide-and-conquer]
related: [interval-dp, alien-dp, cht, slope-trick, ternary-search#convexity, knapsack-01, dp-speedup-overview]
summary: コスト c(i, j) が Monge なら各行の最小値を取る位置が単調になり、分割統治（monotone minima）や Knuth-Yao で区間分割 DP・区間 DP を速くできる。凸な列どうしの合成も速い。
complexity: null
signs:
  - {type: shape, text: '区間分割 DP のコストが c(a, c) + c(b, d) ≤ c(a, d) + c(b, c) を満たす（区間を広げるほど増え方が大きい）'}
  - {type: shape, text: 最適な区切り位置 opt(i) が i について単調に動く}
  - {type: phrase, text: 区間から k 個選ぶときの最大値を、すべての k について求める}
  - {type: constraint, text: N ≤ 10^5 の列を K（数十）個の区間に分ける}
acl: []
verify: [min_plus_convolution_convex_arbitrary, min_plus_convolution_convex_convex]
frequency: B
frequency_evidence: recent 1（abc458_g）・前提として 1 ページに届く（直接 1）・古い ABC 4 問
sections:
  - {title: Monge 性の定義と確かめ方, anchor: definition}
  - {title: monotone minima（分割統治で O(N log N)）, anchor: monotone-minima}
  - {title: SMAWK・LARSCH（O(N)・オンラインに決まる DP）, anchor: smawk-larsch}
  - {title: Knuth-Yao（区間 DP の分割点の範囲を絞って O(N^2)）, anchor: knuth-yao}
  - {title: DP の値の凸性（個数について凸な答え）, anchor: dp-convexity}
  - {title: '凸な列どうしの (max,+) 畳み込み（差分のマージ）', anchor: convex-max-plus-convolution}
  - {title: ライブラリでの検証（Library Checker の min_plus_convolution_convex_arbitrary など）, anchor: verify}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：コスト c(i, j) が Monge なら各行の最小値を取る位置が単調になり、分割統治（monotone minima）や Knuth-Yao で区間分割 DP・区間 DP を速くできる。凸な列どうしの合成も速い。
    - **いつ使うか**：
        - 区間分割 DP のコストが c(a, c) + c(b, d) ≤ c(a, d) + c(b, c) を満たす（区間を広げるほど増え方が大きい）
        - 最適な区切り位置 opt(i) が i について単調に動く
        - 区間から k 個選ぶときの最大値を、すべての k について求める
        - N ≤ 10^5 の列を K（数十）個の区間に分ける
    - **計算量**：（執筆時に書く）
    - **前提**：[区間分割 DP](../dp/dp-sequence-partition.md)、[分割統治](../basics/divide-and-conquer.md)
