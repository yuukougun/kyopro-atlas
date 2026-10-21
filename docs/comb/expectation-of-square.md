---
id: expectation-of-square
title: 二乗の期待値・分散
aliases: [二乗の期待値, 分散, 'E[X^2]', 確率・期待値・二乗を同時に運ぶ, variance]
type: technique
field: comb
chapter: 確率・期待値
order: 420
level: 黄
kind: [確率・期待値]
prerequisites: [linearity-of-expectation]
related: [probability-dp, expected-value-dp, counting-mindset]
summary: E[X^2] は線形性で直接は求まらないので、X^2 = Σ_i Σ_j X_i X_j とペアごとの期待値を足すか、DP で確率・期待値 × 確率・二乗の期待値 × 確率を同時に運ぶ。分散は E[X^2] − E[X]^2 で求める。
complexity: null
signs:
  - {type: phrase, text: 〜の二乗の期待値}
  - {type: phrase, text: 分散を求める（最小化する）}
  - {type: phrase, text: スコアの二乗の期待値}
acl: []
frequency: C
frequency_evidence: recent 0・前提として届くページなし・古い ABC 2 問
sections:
  - {title: 'E[X^2] と E[X]^2 の違い', anchor: difference}
  - {title: ペアに分ける（i = j の項を忘れない）, anchor: pairs}
  - {title: (x + 1)^2 = x^2 + 2x + 1 で 3 つの量を同時に運ぶ, anchor: carry-three}
  - {title: 分散と二乗和の関係, anchor: variance}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：E[X^2] は線形性で直接は求まらないので、X^2 = Σ_i Σ_j X_i X_j とペアごとの期待値を足すか、DP で確率・期待値 × 確率・二乗の期待値 × 確率を同時に運ぶ。分散は E[X^2] − E[X]^2 で求める。
    - **いつ使うか**：
        - 〜の二乗の期待値
        - 分散を求める（最小化する）
        - スコアの二乗の期待値
    - **計算量**：（執筆時に書く）
    - **前提**：[期待値の線形性と指示確率変数](../comb/linearity-of-expectation.md)
