---
id: binary-search
title: 二分探索
aliases: [二分法, lower_bound, upper_bound, めぐる式二分探索, partition_point, binary search]
type: technique
field: basics
chapter: ソートと二分探索
order: 80
level: 基礎
kind: [二分探索]
prerequisites: [sorting-techniques]
related: [binary-search-answer, two-pointers, segment-tree-binary-search, ordered-set, interactive]
summary: 単調な条件の境界を、ok 側と ng 側の不変条件を保ちながら区間を半分ずつ狭めて O(log N) で見つける。ソート済みの列では lower_bound・upper_bound で x 以上の位置や個数を求められる。
complexity: null
signs:
  - {type: phrase, text: ソート済みの列で x 以上の最初の位置・x 以下の個数}
  - {type: phrase, text: 片方を固定して、もう片方が条件を満たす個数を数える}
  - {type: phrase, text: 左右で最も近い要素を探す}
  - {type: constraint, text: N ≤ 2×10^5 個の値に対して、Q ≤ 2×10^5 個の位置・個数の質問がある}
acl: []
frequency: A
frequency_evidence: recent 4（abc457_e・abc476_d・abc480_d・abc480_e）・前提として 26 ページに届く（直接 12）・古い ABC 5 問
sections:
  - {title: めぐる式（ok と ng の不変条件・初期値は判定しない番兵）, anchor: meguru}
  - {title: lower_bound・upper_bound と個数の数え方, anchor: lower-bound}
  - {title: 片方を固定してもう片方を二分探索する, anchor: fix-one-side}
  - {title: '落とし穴（(ok + ng) / 2 のあふれ・負の数の丸め・set に std::lower_bound）', anchor: pitfalls}
  - {title: 質問で二分探索する（インタラクティブ問題へ）, anchor: interactive}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：単調な条件の境界を、ok 側と ng 側の不変条件を保ちながら区間を半分ずつ狭めて O(log N) で見つける。ソート済みの列では lower_bound・upper_bound で x 以上の位置や個数を求められる。
    - **いつ使うか**：
        - ソート済みの列で x 以上の最初の位置・x 以下の個数
        - 片方を固定して、もう片方が条件を満たす個数を数える
        - 左右で最も近い要素を探す
        - N ≤ 2×10^5 個の値に対して、Q ≤ 2×10^5 個の位置・個数の質問がある
    - **計算量**：（執筆時に書く）
    - **前提**：[ソートで考える](../basics/sorting-techniques.md)
