---
id: stern-brocot
title: Stern-Brocot 木と連分数
aliases: [Stern-Brocot tree, continued fraction, 最良近似, 最良有理近似, Farey 数列, 有理数の二分探索]
type: overview
field: math
chapter: floor と商
order: 310
level: 発展
kind: [整数論, 二分探索]
prerequisites: [gcd-lcm]
related: [floor-sum, ext-gcd]
summary: 分母・分子が N 以下で実数に最も近い分数などを、既約分数を全て1回ずつ含む二分木を降りて O(log N) 段で求める。同じ方向への移動を一度に進めるのが連分数にあたる。
complexity: null
signs:
  - {type: phrase, text: 分母・分子が N 以下で、与えられた実数に最も近い分数}
  - {type: phrase, text: 分数の範囲を二分探索する}
acl: []
verify: [stern_brocot_tree, rational_approximation]
frequency: C
frequency_evidence: recent 0・前提として届くページなし・古い ABC 1 問
sections:
  - {title: Stern-Brocot 木と既約分数, anchor: tree}
  - {title: 同じ方向の移動を一度に進める（連分数）, anchor: continued-fraction}
  - {title: 最良有理近似と比較の精度（128bit 整数）, anchor: best-approximation}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：分母・分子が N 以下で実数に最も近い分数などを、既約分数を全て1回ずつ含む二分木を降りて O(log N) 段で求める。同じ方向への移動を一度に進めるのが連分数にあたる。
    - **いつ使うか**：
        - 分母・分子が N 以下で、与えられた実数に最も近い分数
        - 分数の範囲を二分探索する
    - **計算量**：（執筆時に書く）
    - **前提**：[GCD・LCM とユークリッドの互除法](../math/gcd-lcm.md)
