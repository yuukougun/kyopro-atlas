---
id: stirling-first
title: 第 1 種スターリング数
aliases: [巡回の個数ごとの順列の数, 上昇階乗, Stirling numbers of the first kind]
type: overview
field: comb
chapter: 置換・分割・木の数え上げ
order: 260
level: 発展
kind: [数え上げ, 畳み込み・多項式]
prerequisites: [permutation-cycles]
related: [bell-number, generating-function-counting, fps-basics, insertion-dp]
summary: ちょうど k 個の巡回からなる n 次の置換の数で、c(n,k) = c(n−1,k−1) + (n−1) c(n−1,k) を満たす。上昇階乗 x(x+1)…(x+n−1) の係数なので、FPS で一度に求める。
complexity: null
signs:
  - {type: phrase, text: 巡回（サイクル）の個数ごとの順列の数}
  - {type: phrase, text: 左から見える（最大値を更新する）位置の個数ごとの順列の数}
  - {type: phrase, text: 最小の swap 回数ごとの並びの数}
acl: [convolution]
frequency: C
frequency_evidence: recent 0・前提として届くページなし・古い ABC 2 問
sections:
  - {title: 何ができるか（巡回の個数ごとの数）, anchor: what}
  - {title: 漸化式と上昇階乗, anchor: recurrence}
  - {title: 左から見える位置の数との対応, anchor: records}
  - {title: FPS・分割統治で一度に求める, anchor: fps}
  - {title: 第 2 種との違い, anchor: vs-second-kind}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：ちょうど k 個の巡回からなる n 次の置換の数で、c(n,k) = c(n−1,k−1) + (n−1) c(n−1,k) を満たす。上昇階乗 x(x+1)…(x+n−1) の係数なので、FPS で一度に求める。
    - **いつ使うか**：
        - 巡回（サイクル）の個数ごとの順列の数
        - 左から見える（最大値を更新する）位置の個数ごとの順列の数
        - 最小の swap 回数ごとの並びの数
    - **計算量**：（執筆時に書く）
    - **前提**：[置換の巡回分解](../comb/permutation-cycles.md)
