---
id: inclusion-exclusion-dp
title: 包除 DP
aliases: [符号付き DP, 最初に踏む障害物で分類, 障害物 DP, 包除原理を DP に載せる]
type: technique
field: comb
chapter: 包除の系統
order: 190
level: 黄
kind: [数え上げ, DP]
prerequisites: [inclusion-exclusion, dp-basics, lattice-paths]
related: [dp-grid, counting-dedup, tree-dp, insertion-dp]
summary: 包除の和 Σ(−1)^|S| N(S) の項が多すぎて列挙できないとき、S を作る過程を DP にし、符号を DP の値に掛けて運ぶ。障害物を並べて最初に踏む障害物で分類し全体から引く形も同じ仲間である。
complexity: null
signs:
  - {type: constraint, text: 'H, W ≤ 10^5 のグリッドに障害物が N ≤ 3000 個'}
  - {type: phrase, text: 禁止条件が列や木に沿って並ぶ数え上げ}
  - {type: phrase, text: '|P_i − i| など、位置と値の差に制約がある順列の個数'}
  - {type: phrase, text: 隣り合う値が異なる数列の個数}
acl: []
frequency: C
frequency_evidence: recent 0・前提として届くページなし・古い ABC 2 問
sections:
  - {title: 包除の和を「S を作る過程」の重みの和と見る, anchor: weighted-sum}
  - {title: 最初に踏む障害物で分類する（ソート順と終点の扱い）, anchor: first-obstacle}
  - {title: 違反の個数を状態に持ち、最後に符号と残りの自由度を掛ける, anchor: count-violations}
  - {title: 「等しい」を区間にまとめる符号付き DP, anchor: equal-blocks}
  - {title: 符号付きの木 DP, anchor: tree, level: 発展}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：包除の和 Σ(−1)^|S| N(S) の項が多すぎて列挙できないとき、S を作る過程を DP にし、符号を DP の値に掛けて運ぶ。障害物を並べて最初に踏む障害物で分類し全体から引く形も同じ仲間である。
    - **いつ使うか**：
        - H, W ≤ 10^5 のグリッドに障害物が N ≤ 3000 個
        - 禁止条件が列や木に沿って並ぶ数え上げ
        - |P_i − i| など、位置と値の差に制約がある順列の個数
        - 隣り合う値が異なる数列の個数
    - **計算量**：（執筆時に書く）
    - **前提**：[包除原理](../comb/inclusion-exclusion.md)、[DP の基本](../dp/dp-basics.md)、[格子路の数え上げ](../comb/lattice-paths.md)
