---
id: prefix-sum
title: 累積和
aliases: [prefix sum, cumulative sum, 累積 GCD, 累積 XOR, 累積 max, 左右からの累積]
type: technique
field: basics
chapter: 累積和といもす法
order: 120
level: 基礎
kind: [累積和・差分, 区間クエリ]
prerequisites: []
related: [imos, prefix-sum-counting, fenwick-tree, sparse-table, dp-prefix-sum]
summary: S[0] = 0、S[i+1] = S[i] + a[i] と前計算すると、区間 [l, r) の和が S[r] − S[l] で O(1) で求まる。引き算できない演算（gcd・max）は左右からの累積で「1 つ除いた値」を作る。
complexity: null
signs:
  - {type: phrase, text: 区間の和を何度も聞かれる}
  - {type: phrase, text: 1 つだけ除いた（変えた）ときの値}
  - {type: phrase, text: 円環上の区間}
  - {type: constraint, text: Q ≤ 2×10^5 個の区間和のクエリで、値の更新がない}
acl: []
frequency: A
frequency_evidence: recent 11（abc452_e・abc468_e・abc469_e・abc472_f・abc473_f・abc474_eほか）・前提として 51 ページに届く（直接 13）・古い ABC 4 問
sections:
  - {title: '半開区間と S[0] = 0', anchor: half-open}
  - {title: 左右からの累積（1 つ除いた gcd・max）, anchor: left-right}
  - {title: 円環は 2 周分に伸ばす, anchor: circular}
  - {title: 累積和の上で二分探索・尺取り, anchor: with-binary-search}
  - {title: あふれと添字のずれ, anchor: pitfalls}
  - {title: 値が更新されるなら BIT、静的な区間 min なら Sparse Table, anchor: next-tools}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：S[0] = 0、S[i+1] = S[i] + a[i] と前計算すると、区間 [l, r) の和が S[r] − S[l] で O(1) で求まる。引き算できない演算（gcd・max）は左右からの累積で「1 つ除いた値」を作る。
    - **いつ使うか**：
        - 区間の和を何度も聞かれる
        - 1 つだけ除いた（変えた）ときの値
        - 円環上の区間
        - Q ≤ 2×10^5 個の区間和のクエリで、値の更新がない
    - **計算量**：（執筆時に書く）
    - **前提**：なし
