---
id: divide-and-conquer
title: 分割統治
aliases: [divide and conquer, 分割統治法, マージソート, 中央をまたぐ区間, 区間ナップサック]
type: technique
field: basics
chapter: 再帰と分割統治
order: 320
level: 黄
kind: [ダブリング・分割統治]
prerequisites: [recursion-structure]
related: [inversion-number, cdq-divide-and-conquer, monge#monotone-minima, online-convolution, segment-tree, knapsack-01]
summary: 区間を半分に分けて左右を再帰で解き、中央を「またぐもの」だけを O(長さ) で処理すれば全体が O(N log N) になる。マージソートでの転倒数、最大値の位置での分割、区間クエリの左右の DP の合成に使う。
complexity: null
signs:
  - {type: phrase, text: 区間・部分列の全部の組について数える}
  - {type: phrase, text: '区間 [L, R] の品物だけを使うナップサックを多数のクエリで答える'}
  - {type: constraint, text: 'N, Q ≤ 2×10^5 で、区間ごとに計算し直すと間に合わない'}
  - {type: shape, text: 左右に分けたとき、中央をまたぐものだけなら速く数えられる}
  - {type: shape, text: 区間の最大値の位置で左右に分けると、それぞれが同じ形の問題になる}
acl: []
frequency: A
frequency_evidence: recent 2（abc451_g・abc478_g）・前提として 4 ページに届く（直接 3）・古い ABC 1 問
sections:
  - {title: 漸化式 T(N) = 2T(N/2) + O(N) と計算量, anchor: recurrence}
  - {title: またぐものの数え方（マージソートで転倒数）, anchor: crossing}
  - {title: 最大値の位置で分ける, anchor: split-at-max}
  - {title: 区間クエリを中央で分けて左右の DP を合わせる（区間ナップサック）, anchor: range-knapsack}
  - {title: 他の分野の分割統治（分割統治 DP・分割統治 FFT・CDQ）への案内, anchor: other-fields}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：区間を半分に分けて左右を再帰で解き、中央を「またぐもの」だけを O(長さ) で処理すれば全体が O(N log N) になる。マージソートでの転倒数、最大値の位置での分割、区間クエリの左右の DP の合成に使う。
    - **いつ使うか**：
        - 区間・部分列の全部の組について数える
        - 区間 [L, R] の品物だけを使うナップサックを多数のクエリで答える
        - N, Q ≤ 2×10^5 で、区間ごとに計算し直すと間に合わない
        - 左右に分けたとき、中央をまたぐものだけなら速く数えられる
        - 区間の最大値の位置で左右に分けると、それぞれが同じ形の問題になる
    - **計算量**：（執筆時に書く）
    - **前提**：[再帰的な構造](../basics/recursion-structure.md)
