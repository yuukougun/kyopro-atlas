---
id: continuous-probability
title: 連続値の確率
aliases: [連続確率, 一様乱数, 確率と積分, 長さ・面積・角度の比, continuous probability]
type: overview
field: comb
chapter: 確率・期待値
order: 430
level: 発展
kind: [確率・期待値]
prerequisites: [expectation-tail-sum]
related: [geometry-vectors, convex-hull]
summary: '[0, 1] の一様乱数のような連続な確率変数について、確率は長さ・面積・角度の比、期待値は積分で求める。E[X] = ∫ P(X > t) dt や「N 個の一様乱数の K 番目の期待値は K/(N+1)」を使う。'
complexity: null
signs:
  - {type: phrase, text: 実数を一様ランダムに選ぶ}
  - {type: phrase, text: 円内（区間内）のランダムな点}
acl: []
frequency: C
frequency_evidence: recent 0・前提として届くページなし・古い ABC 1 問
sections:
  - {title: 何ができるか, anchor: what}
  - {title: 長さ・面積・角度の比, anchor: ratio}
  - {title: 積分と tail sum, anchor: integral}
  - {title: 区分的な多項式の積分, anchor: piecewise}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：[0, 1] の一様乱数のような連続な確率変数について、確率は長さ・面積・角度の比、期待値は積分で求める。E[X] = ∫ P(X > t) dt や「N 個の一様乱数の K 番目の期待値は K/(N+1)」を使う。
    - **いつ使うか**：
        - 実数を一様ランダムに選ぶ
        - 円内（区間内）のランダムな点
    - **計算量**：（執筆時に書く）
    - **前提**：[期待値と確率の変換](../comb/expectation-tail-sum.md)
