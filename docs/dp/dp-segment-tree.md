---
id: dp-segment-tree
title: セグメント木・スライド最小値による DP の高速化
aliases: [セグ木 DP, BIT で DP を速くする, 値を添字にした DP, deque DP, 単調スタック DP]
type: technique
field: dp
chapter: DP の高速化
order: 320
level: 青
kind: [DP, 区間クエリ, 尺取り・スライド窓]
prerequisites: [dp-prefix-sum, segment-tree-on-values]
related: [monotonic-stack#sliding-window-minimum, segment-tree#dp, fenwick-tree, lis, inline-dp, cht, dp-speedup-overview]
summary: 遷移元が添字や値の範囲の最小・最大・和になる DP を、dp の値をセグメント木に載せて 1 回 O(log N) にする。遷移元の窓が単調に動くだけなら、スライド最小値でならし O(1) にできる。
complexity: null
signs:
  - {type: phrase, text: 隣り合う要素の差が D 以下になるように選ぶ部分列の最長}
  - {type: shape, text: 'dp[i] = max_{j < i, l ≤ a_j ≤ r} dp[j] + c のように、遷移元が添字や値の範囲の最小・最大'}
  - {type: shape, text: 遷移のコストに |x_i − x_j| を含む（x_j < x_i と x_j > x_i で分けられる）}
  - {type: shape, text: 'dp[i] = min_{i−K ≤ j < i} dp[j] + c（窓が単調に動く）'}
acl: [segtree, fenwick_tree]
frequency: B
frequency_evidence: recent 0・前提として 1 ページに届く（直接 1）・古い ABC 4 問
sections:
  - {title: dp の値を位置や値を添字にしたセグメント木に載せる（座標圧縮）, anchor: values-on-segment-tree}
  - {title: '|x − y| を左右に分けて 2 本のセグメント木に', anchor: split-abs}
  - {title: 区間を覆う最小コスト（右端までの最小）, anchor: interval-cover}
  - {title: スライド最小値（単調 deque）と単調スタックによる遷移, anchor: dp-sliding-window}
  - {title: セグメント木・累積和・スライド最小値の使い分け, anchor: which-tool}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：遷移元が添字や値の範囲の最小・最大・和になる DP を、dp の値をセグメント木に載せて 1 回 O(log N) にする。遷移元の窓が単調に動くだけなら、スライド最小値でならし O(1) にできる。
    - **いつ使うか**：
        - 隣り合う要素の差が D 以下になるように選ぶ部分列の最長
        - dp[i] = max_{j < i, l ≤ a_j ≤ r} dp[j] + c のように、遷移元が添字や値の範囲の最小・最大
        - 遷移のコストに |x_i − x_j| を含む（x_j < x_i と x_j > x_i で分けられる）
        - dp[i] = min_{i−K ≤ j < i} dp[j] + c（窓が単調に動く）
    - **計算量**：（執筆時に書く）
    - **前提**：[累積和・いもす法による DP の高速化](../dp/dp-prefix-sum.md)、[値を添字にする BIT・セグメント木](../ds/segment-tree-on-values.md)
