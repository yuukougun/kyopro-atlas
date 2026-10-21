---
id: inline-dp
title: インライン DP
aliases: [in-place DP, Inline DP, 配列を使い回して一括更新, 遅延セグ木 DP]
type: technique
field: dp
chapter: DP の高速化
order: 330
level: 青
kind: [DP, 区間クエリ]
prerequisites: [dp-segment-tree, lazy-segment-tree, knapsack-01]
related: [dp-dimension-reduction, lazy-segment-tree-patterns, global-offset#offset, lis, monotonic-stack#dp-transition]
summary: dp[i][*] から dp[i+1][*] へほとんどの値がそのまま写るとき、配列を 1 本だけ持って変わる場所だけを書き換える。一律の加算や区間加算は遅延セグメント木で、全体の平行移動は添字のずらしで表す。
complexity: null
signs:
  - {type: shape, text: 'dp[i][*] から dp[i+1][*] で変わる場所が少ない'}
  - {type: shape, text: 遷移で dp 全体に一律の加算・平行移動が入る}
  - {type: shape, text: '区間 [l, r] の右端 r で、l 以降の位置の dp にまとめて加算する'}
acl: [lazy_segtree]
frequency: B
frequency_evidence: recent 1（abc480_g）・前提として届くページなし・古い ABC 5 問
sections:
  - {title: 2 次元の表で考えてから、行ごとに変わる場所を書き出す, anchor: diff-per-row}
  - {title: 変わる場所だけを更新する（辺を 1 本ずつ緩和する）, anchor: update-changes}
  - {title: 全体のシフトを添字のずらしで表す, anchor: global-shift}
  - {title: 区間加算と区間最大を遅延セグメント木で（区間の右端で加算する）, anchor: lazy-segment-tree}
  - {title: 単調スタックと組み合わせる, anchor: with-monotonic-stack, level: 黄}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：dp\[i][\*] から dp\[i+1][\*] へほとんどの値がそのまま写るとき、配列を 1 本だけ持って変わる場所だけを書き換える。一律の加算や区間加算は遅延セグメント木で、全体の平行移動は添字のずらしで表す。
    - **いつ使うか**：
        - dp\[i][\*] から dp\[i+1][\*] で変わる場所が少ない
        - 遷移で dp 全体に一律の加算・平行移動が入る
        - 区間 [l, r] の右端 r で、l 以降の位置の dp にまとめて加算する
    - **計算量**：（執筆時に書く）
    - **前提**：[セグメント木・スライド最小値による DP の高速化](../dp/dp-segment-tree.md)、[遅延セグメント木](../ds/lazy-segment-tree.md)、[ナップサック DP](../dp/knapsack-01.md)
