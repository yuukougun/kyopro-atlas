---
id: interval-scheduling
title: 区間スケジューリング・区間の串刺し
aliases: [区間スケジューリング問題, 区間を点で突く, Activity Selection, interval scheduling]
type: technique
field: basics
chapter: 貪欲
order: 250
level: 基礎
kind: [貪欲, ソート・座標圧縮]
prerequisites: [greedy-basics]
related: [greedy-priority-queue, exchange-argument, dp-basics]
summary: 重ならない区間をできるだけ多く選ぶには、右端の小さい順に、選んだ区間と重ならないものを取ればよい。すべての区間を最少の点で突く問題も、右端でソートして右端に点を置く同じ貪欲で解ける。
complexity: null
signs:
  - {type: phrase, text: 重ならない区間をできるだけ多く選ぶ}
  - {type: phrase, text: すべての区間を最少の点（串）で突く}
  - {type: constraint, text: N ≤ 2×10^5 本の区間で、座標は 10^9 まで}
acl: []
frequency: B
frequency_evidence: 古い ABC で繰り返し出た定番（最近30回の出現は0。手で B にした）
sections:
  - {title: 右端の順に選ぶ理由（交換論法）, anchor: why-right-end}
  - {title: 区間の串刺し（最少の点で突く）, anchor: stabbing}
  - {title: 左端の順・長さの順が失敗する例, anchor: counterexamples}
  - {title: 処理時間と締め切りがある場合（優先度付きキューの貪欲へ）, anchor: deadlines}
  - {title: 区間に重みがあるなら DP, anchor: weighted}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：重ならない区間をできるだけ多く選ぶには、右端の小さい順に、選んだ区間と重ならないものを取ればよい。すべての区間を最少の点で突く問題も、右端でソートして右端に点を置く同じ貪欲で解ける。
    - **いつ使うか**：
        - 重ならない区間をできるだけ多く選ぶ
        - すべての区間を最少の点（串）で突く
        - N ≤ 2×10^5 本の区間で、座標は 10^9 まで
    - **計算量**：（執筆時に書く）
    - **前提**：[貪欲法の考え方と正当性](../basics/greedy-basics.md)
