---
id: segment-tree-on-values
title: 値を添字にする BIT・セグメント木
aliases: [値域セグ木, 権値線段樹, 値を添字にするセグ木, 動的セグ木, dynamic segment tree, sparse segment tree]
type: technique
field: ds
chapter: 区間クエリ
order: 200
level: 水
kind: [データ構造, 区間クエリ, ソート・座標圧縮]
prerequisites: [segment-tree, coordinate-compression]
related: [fenwick-tree, kth-element, top-k-multiset, dp-segment-tree, segment-tree-binary-search, offline-queries]
summary: 値（必要なら座標圧縮した値）を添字にした BIT・セグメント木に個数や和を載せ、「x 以下の個数・和」「上位 K 個の和」を O(log N) で求める。DP の「その値で終わる最良」も値の添字で持てる。
complexity: null
signs:
  - {type: phrase, text: 隣り合う要素の差が D 以下の部分列の最長}
  - {type: phrase, text: 値を追加しながら、上位 K 個の和・ソートしたときの奇数番目の和を答える}
  - {type: phrase, text: 前の答えを使って次のクエリが復号され、先読みができない}
  - {type: shape, text: 'dp[v] = max(dp[v − D..v + D]) + 1 のように、値の範囲から最大を取る遷移'}
  - {type: constraint, text: '値が 10^9 まで、N, Q ≤ 2×10^5'}
acl: [segtree, fenwick_tree]
verify: [point_set_range_composite_large_array]
frequency: B
frequency_evidence: recent 0・前提として 2 ページに届く（直接 1）・古い ABC 5 問
sections:
  - {title: 値を添字にする（個数・和を載せる）と座標圧縮, anchor: index-by-value}
  - {title: DP の値を値の添字で持つ（→ DP の章のセグメント木による遷移の高速化）, anchor: dp-on-values}
  - {title: 上位 K 個の和（個数と和を載せ、境界はセグメント木上の二分探索で探す）, anchor: top-k-sum, level: 青}
  - {title: 左の個数の偶奇で右の読み方が変わる量（ソート後の奇数番目の和）, anchor: odd-position-sum, level: 黄}
  - {title: 動的セグメント木（必要なノードだけ作る。オフラインなら座標圧縮で済む）, anchor: dynamic-segment-tree, level: 黄}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：値（必要なら座標圧縮した値）を添字にした BIT・セグメント木に個数や和を載せ、「x 以下の個数・和」「上位 K 個の和」を O(log N) で求める。DP の「その値で終わる最良」も値の添字で持てる。
    - **いつ使うか**：
        - 隣り合う要素の差が D 以下の部分列の最長
        - 値を追加しながら、上位 K 個の和・ソートしたときの奇数番目の和を答える
        - 前の答えを使って次のクエリが復号され、先読みができない
        - dp[v] = max(dp[v − D..v + D]) + 1 のように、値の範囲から最大を取る遷移
        - 値が 10^9 まで、N, Q ≤ 2×10^5
    - **計算量**：（執筆時に書く）
    - **前提**：[セグメント木](../ds/segment-tree.md)、[座標圧縮](../basics/coordinate-compression.md)
