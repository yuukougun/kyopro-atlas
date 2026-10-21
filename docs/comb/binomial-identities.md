---
id: binomial-identities
title: 二項係数の恒等式と和の公式
aliases: [二項定理, Vandermonde の恒等式, hockey stick, 縦の和の公式, 吸収公式, 二項係数の和, binomial theorem, Vandermonde's identity]
type: technique
field: comb
chapter: 二項係数の系統
order: 130
level: 青
kind: [数え上げ]
prerequisites: [lattice-paths]
related: [sigma-manipulation, counting-bijection, binomial-prefix-sum, generating-function-counting]
summary: 二項定理・Vandermonde の恒等式・縦の和（hockey stick）・吸収公式などで、二項係数を含む和を閉じた式にする。どれも同じものを 2 通りに数えて説明でき、式変形は小さいケースで検算する。
complexity: null
signs:
  - {type: phrase, text: 長方形領域の各点への経路数の総和}
  - {type: phrase, text: 偶数個（奇数個）を選ぶ方法の数の和}
  - {type: phrase, text: 全ペアの (A_i + A_j)^x の和}
  - {type: shape, text: Σ の中に二項係数があり、N が大きく項ごとには足せない}
acl: []
frequency: B
frequency_evidence: recent 0・前提として 1 ページに届く（直接 1）・古い ABC 3 問
sections:
  - {title: 二項定理、二項係数の和 2^n と交代和, anchor: binomial-theorem}
  - {title: 偶奇の条件つきの和, anchor: parity-sum}
  - {title: Vandermonde の恒等式（2 グループから合計 k 個）, anchor: vandermonde}
  - {title: 縦の和（hockey stick）と経路数の総和, anchor: hockey-stick}
  - {title: '吸収公式 k C(n,k) = n C(n−1, k−1)', anchor: absorption}
  - {title: 二項定理で累乗の和を展開する, anchor: power-sums}
  - {title: 式変形の検算（小さいケース）, anchor: verify}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：二項定理・Vandermonde の恒等式・縦の和（hockey stick）・吸収公式などで、二項係数を含む和を閉じた式にする。どれも同じものを 2 通りに数えて説明でき、式変形は小さいケースで検算する。
    - **いつ使うか**：
        - 長方形領域の各点への経路数の総和
        - 偶数個（奇数個）を選ぶ方法の数の和
        - 全ペアの (A_i + A_j)^x の和
        - Σ の中に二項係数があり、N が大きく項ごとには足せない
    - **計算量**：（執筆時に書く）
    - **前提**：[格子路の数え上げ](../comb/lattice-paths.md)
