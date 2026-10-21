---
id: dp-phase
title: フェーズを状態に持つ DP
aliases: [耳 DP, 段階を状態に持つ DP, 最大部分配列和, Kadane, Kadane's algorithm]
type: technique
field: dp
chapter: DP の考え方
order: 70
level: 青
kind: [DP]
prerequisites: [dp-state-design]
related: [subsequence-dp, string-automaton-dp, dp-sequence-partition, difference-sequence, lis]
summary: 区間を 1 つ選ぶ・何文字目まで集めたか、のように各位置でいまどの段階にいるかを状態に持つ。区間の両端を全探索する代わりに段階の切り替えを遷移にして、O(N^2) を O(N) にする。
complexity: null
signs:
  - {type: phrase, text: 区間を 1 つ選んで、その中だけ操作する（1 回だけ変更できる）}
  - {type: phrase, text: '部分列として ''ABC'' などが何個含まれるか（''?'' を埋めた全通りの和）'}
  - {type: phrase, text: 連続する部分列の和の最大}
  - {type: shape, text: '区間 [l, r) の両端を全探索すると O(N^2) になり、各位置の扱いが「区間の前・中・後」で変わる'}
acl: []
frequency: B
frequency_evidence: recent 1（abc466_e）・前提として届くページなし・古い ABC 4 問
sections:
  - {title: 最大部分配列和（Kadane）：区間を 1 つ選ぶ最も簡単な例, anchor: kadane}
  - {title: 段階の数え方（区間の外側にも段階がある）, anchor: counting-phases}
  - {title: 何文字目まで集めたか（部分列として現れる回数を数える）, anchor: matched-prefix}
  - {title: 区間の反転・変更を段階の切り替えで表す, anchor: flip-interval}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：区間を 1 つ選ぶ・何文字目まで集めたか、のように各位置でいまどの段階にいるかを状態に持つ。区間の両端を全探索する代わりに段階の切り替えを遷移にして、O(N^2) を O(N) にする。
    - **いつ使うか**：
        - 区間を 1 つ選んで、その中だけ操作する（1 回だけ変更できる）
        - 部分列として 'ABC' などが何個含まれるか（'?' を埋めた全通りの和）
        - 連続する部分列の和の最大
        - 区間 [l, r) の両端を全探索すると O(N^2) になり、各位置の扱いが「区間の前・中・後」で変わる
    - **計算量**：（執筆時に書く）
    - **前提**：[DP の状態の設計](../dp/dp-state-design.md)
