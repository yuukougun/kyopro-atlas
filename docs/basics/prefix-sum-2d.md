---
id: prefix-sum-2d
title: 2 次元累積和
aliases: [二次元累積和, 2D prefix sum, 長方形の和, 3 次元累積和, 多次元の累積和]
type: technique
field: basics
chapter: 累積和といもす法
order: 140
level: 水
kind: [累積和・差分, 区間クエリ]
prerequisites: [prefix-sum]
related: [imos, sweep-line-2d, fenwick-tree, inclusion-exclusion]
summary: 長方形領域の和を、S[i+1][j+1] = S[i][j+1] + S[i+1][j] − S[i][j] + a[i][j] の前計算と 4 項の足し引きで O(1) で求める。3 次元以上も包除の符号で同じように求められる。
complexity: null
signs:
  - {type: phrase, text: 長方形領域の和・個数を何度も求める}
  - {type: phrase, text: 正方形・長方形を全部試す}
  - {type: phrase, text: 模様が周期的に敷き詰められた盤面}
  - {type: constraint, text: 'H, W ≤ 2000 程度のグリッドで領域の和を何度も求める'}
acl: []
frequency: A
frequency_evidence: recent 3（abc461_d・abc465_f・abc475_f）・前提として 1 ページに届く（直接 1）・古い ABC 3 問
sections:
  - {title: 前計算の式と長方形の和（4 項の包除）, anchor: formula}
  - {title: 各左上から辺の長さを二分探索する, anchor: with-binary-search}
  - {title: 周期的な盤面（周期で分割する）, anchor: periodic-board}
  - {title: '区間を点 (l, r) と見て数える', anchor: intervals-as-points}
  - {title: 3 次元以上（項の数と符号の決め方）, anchor: higher-dimensions, level: 青}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：長方形領域の和を、S\[i+1][j+1] = S\[i][j+1] + S\[i+1][j] − S\[i][j] + a\[i][j] の前計算と 4 項の足し引きで O(1) で求める。3 次元以上も包除の符号で同じように求められる。
    - **いつ使うか**：
        - 長方形領域の和・個数を何度も求める
        - 正方形・長方形を全部試す
        - 模様が周期的に敷き詰められた盤面
        - H, W ≤ 2000 程度のグリッドで領域の和を何度も求める
    - **計算量**：（執筆時に書く）
    - **前提**：[累積和](../basics/prefix-sum.md)
