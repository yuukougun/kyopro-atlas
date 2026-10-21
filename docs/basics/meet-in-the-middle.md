---
id: meet-in-the-middle
title: 半分全列挙
aliases: [Meet in the Middle, 半分全探索, 折半全列挙]
type: technique
field: basics
chapter: 二分探索の応用
order: 190
level: 水
kind: [全探索, 二分探索]
prerequisites: [bit-full-search, binary-search]
related: [two-pointers, knapsack-01#choose-by-size, subset-sum]
summary: N ≤ 40 程度の部分集合の問題を前半と後半に分け、それぞれ 2^(N/2) 通りを列挙してから、ソートと二分探索（または尺取り）で組み合わせる。
complexity: null
signs:
  - {type: constraint, text: N ≤ 40 で部分集合を選ぶ（2^N は無理だが 2^(N/2) は間に合う）}
  - {type: phrase, text: 2 つの独立な選択を組み合わせて条件を満たす}
  - {type: constraint, text: H + W ≤ 40 程度のグリッドで、左上から右下への経路をすべて考える}
acl: []
frequency: B
frequency_evidence: recent 1（abc464_f）・前提として届くページなし・古い ABC 3 問
sections:
  - {title: 前半・後半を列挙して突き合わせる（ソート＋二分探索・尺取り）, anchor: combine-halves}
  - {title: ちょうど K 個などの制約は個数ごとに分けて持つ, anchor: by-count}
  - {title: グリッドの経路を対角線で分ける, anchor: grid-diagonal, level: 青}
  - {title: 「片側を全探索して残りは貪欲」との違い, anchor: vs-greedy}
  - {title: 値の範囲が小さければナップサック DP, anchor: vs-knapsack}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：N ≤ 40 程度の部分集合の問題を前半と後半に分け、それぞれ 2^(N/2) 通りを列挙してから、ソートと二分探索（または尺取り）で組み合わせる。
    - **いつ使うか**：
        - N ≤ 40 で部分集合を選ぶ（2^N は無理だが 2^(N/2) は間に合う）
        - 2 つの独立な選択を組み合わせて条件を満たす
        - H + W ≤ 40 程度のグリッドで、左上から右下への経路をすべて考える
    - **計算量**：（執筆時に書く）
    - **前提**：[bit 全探索と順列全探索](../basics/bit-full-search.md)、[二分探索](../basics/binary-search.md)
