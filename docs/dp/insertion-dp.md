---
id: insertion-dp
title: 挿入 DP・箱根駅伝 DP
aliases: [相対順位の DP, 順列の DP, 箱根 DP, Insertion DP, 連結成分 DP, Connected Component DP]
type: technique
field: dp
chapter: 状態の形で分かれる DP
order: 300
level: 黄
kind: [DP, 数え上げ]
prerequisites: [dp-state-design, dp-prefix-sum]
related: [inclusion-exclusion-dp#count-violations, counting-fix-order#relative-order, counting-dedup]
summary: 順列を、決めた部分の相対順位や「相手が未定の要素の数」だけを状態にして数える。隣り合う大小関係が指定された順列は、最後の要素の相対順位を状態にし累積和で O(N^2) になる。
complexity: null
signs:
  - {type: phrase, text: 順列で隣り合う大小関係（< と >）が指定される}
  - {type: phrase, text: '|p_i − i| の和がちょうど K の順列の数'}
  - {type: phrase, text: 値の小さい順に、列の好きな位置へ挿入していく}
  - {type: constraint, text: N ≤ 3000 程度の順列の数え上げ}
acl: []
frequency: A
frequency_evidence: recent 2（abc468_g・abc473_g）・前提として届くページなし・古い ABC 5 問
sections:
  - {title: 相対順位を状態にする（最後の要素が何番目か）, anchor: relative-rank}
  - {title: 遷移は区間になるので累積和でまとめる, anchor: prefix-sum}
  - {title: 値の大きい（小さい）順に挿入していく見方, anchor: insert-by-value}
  - {title: 箱根駅伝 DP（相手が未定の位置と値の数を持つ）, anchor: hakone-ekiden-dp}
  - {title: 連結成分 DP（ブロックを作る・端に付ける・つなぐ）, anchor: connected-component-dp, level: 発展}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：順列を、決めた部分の相対順位や「相手が未定の要素の数」だけを状態にして数える。隣り合う大小関係が指定された順列は、最後の要素の相対順位を状態にし累積和で O(N^2) になる。
    - **いつ使うか**：
        - 順列で隣り合う大小関係（< と >）が指定される
        - |p_i − i| の和がちょうど K の順列の数
        - 値の小さい順に、列の好きな位置へ挿入していく
        - N ≤ 3000 程度の順列の数え上げ
    - **計算量**：（執筆時に書く）
    - **前提**：[DP の状態の設計](../dp/dp-state-design.md)、[累積和・いもす法による DP の高速化](../dp/dp-prefix-sum.md)
