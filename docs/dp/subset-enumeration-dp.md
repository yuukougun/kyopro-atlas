---
id: subset-enumeration-dp
title: 部分集合を列挙する DP
aliases: [3^N DP, 部分集合の部分集合, Submask Enumeration, グループ分け DP]
type: technique
field: dp
chapter: 状態の形で分かれる DP
order: 230
level: 青
kind: [DP, ビット演算]
prerequisites: [bit-dp]
related: [counting-dedup#min-index, zeta-mobius-subset, recursive-enumeration#partition, steiner-tree]
summary: 集合を部分集合と残りに分ける遷移を T = (T − 1) & S で列挙し、グループ分けの最適値や数を全体 O(3^N) で求める。順序の重複を除くため、最小の要素を含む部分集合だけを列挙する。
complexity: null
signs:
  - {type: phrase, text: N 個をいくつかのグループに分ける方法の数・最適値}
  - {type: phrase, text: 集合を部分集合の和に分割する}
  - {type: constraint, text: N ≤ 16〜18（3^N ≈ 4×10^7〜4×10^8）}
acl: []
frequency: B
frequency_evidence: recent 0・前提として 2 ページに届く（直接 2）・古い ABC 4 問
sections:
  - {title: 部分集合の部分集合を列挙する（T = (T − 1) & S）, anchor: submask-loop}
  - {title: 3^N になる理由（各要素が 3 通り）, anchor: why-3n}
  - {title: 最小の要素を含むグループから決める（順序の重複を除く）, anchor: fix-minimum}
  - {title: グループの数を状態に足す, anchor: group-count}
  - {title: 高速ゼータ変換との使い分け, anchor: vs-zeta}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：集合を部分集合と残りに分ける遷移を T = (T − 1) & S で列挙し、グループ分けの最適値や数を全体 O(3^N) で求める。順序の重複を除くため、最小の要素を含む部分集合だけを列挙する。
    - **いつ使うか**：
        - N 個をいくつかのグループに分ける方法の数・最適値
        - 集合を部分集合の和に分割する
        - N ≤ 16〜18（3&#94;N ≈ 4×10&#94;7〜4×10&#94;8）
    - **計算量**：（執筆時に書く）
    - **前提**：[bitDP](../dp/bit-dp.md)
