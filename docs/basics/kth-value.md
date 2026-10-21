---
id: kth-value
title: K 番目の値
aliases: [K 番目を二分探索で求める, 順位を数える, N^2 個の K 番目, K-th smallest]
type: technique
field: basics
chapter: 二分探索の応用
order: 210
level: 青
kind: [二分探索]
prerequisites: [binary-search-answer, two-pointers]
related: [kth-element, greedy-priority-queue, priority-queue, fractional-binary-search]
summary: N^2 個の積・和のように全部は列挙できない値の K 番目を、「x 以下の個数 ≥ K」となる最小の x として二分探索で求める。x 以下の個数を速く数えられることが条件になる。
complexity: null
signs:
  - {type: phrase, text: N^2 個（以上）の値の K 番目}
  - {type: phrase, text: 大きい方から M 個の和}
  - {type: constraint, text: N ≤ 2×10^5 で、K が N^2 程度まで大きい}
  - {type: shape, text: 全部は列挙できないが「x 以下が何個あるか」は数えられる}
acl: []
frequency: B
frequency_evidence: recent 0・前提として届くページなし・古い ABC 6 問
sections:
  - {title: なぜ count(x) ≥ K となる最小の x が答えか, anchor: why-count}
  - {title: 数え方の型（ソート＋二分探索・尺取り、符号で場合分け、包除）, anchor: counting-patterns}
  - {title: 上位 M 個の和（同じ値の分の調整）, anchor: top-m-sum}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：N^2 個の積・和のように全部は列挙できない値の K 番目を、「x 以下の個数 ≥ K」となる最小の x として二分探索で求める。x 以下の個数を速く数えられることが条件になる。
    - **いつ使うか**：
        - N^2 個（以上）の値の K 番目
        - 大きい方から M 個の和
        - N ≤ 2×10^5 で、K が N^2 程度まで大きい
        - 全部は列挙できないが「x 以下が何個あるか」は数えられる
    - **計算量**：（執筆時に書く）
    - **前提**：[答えで二分探索](../basics/binary-search-answer.md)、[尺取り法](../basics/two-pointers.md)
