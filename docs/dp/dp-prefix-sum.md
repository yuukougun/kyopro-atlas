---
id: dp-prefix-sum
title: 累積和・いもす法による DP の高速化
aliases: [累積和 DP, いもす法 DP, 累積和で遷移をまとめる]
type: technique
field: dp
chapter: DP の考え方
order: 90
level: 水
kind: [DP, 累積和・差分]
prerequisites: [dp-basics, imos]
related: [dp-segment-tree, inline-dp, prefix-sum-2d, dp-sequence-partition, insertion-dp, dp-grid, dp-speedup-overview]
summary: 遷移元が連続した範囲の和になる DP を、前の段の累積和で 1 回 O(1) にする。遷移先が範囲なら、いもす法で差分に書いておき後で累積する。
complexity: null
signs:
  - {type: phrase, text: 各人に 0〜a_i 個を配る方法の数（上限つきの配り方）}
  - {type: constraint, text: N ≤ 100、K ≤ 10^5 程度で、O(NK) は通るが O(NK^2) は通らない}
  - {type: shape, text: 'dp[i] = Σ_{j=i−R}^{i−L} dp[j] のように、遷移元が連続した範囲の和'}
  - {type: shape, text: 'dp[i] から i+L〜i+R の範囲へ同じ値を配る'}
acl: []
frequency: B
frequency_evidence: recent 0・前提として 6 ページに届く（直接 3）・古い ABC 11 問
sections:
  - {title: 貰う形と累積和・配る形といもす法, anchor: pull-and-push}
  - {title: 同じ段の累積和（上限つきの配り方）, anchor: same-row}
  - {title: 区間の和集合・方向ごとの累積（縦・横・斜め）, anchor: directional}
  - {title: 遷移元が接頭辞なら累積 min・累積 max でもよい, anchor: prefix-min}
  - {title: 余りごとの累積, anchor: by-remainder, level: 青}
  - {title: 2 次元の累積, anchor: two-dimensional, level: 青}
  - {title: 落とし穴：累積和を更新しながら使う順番・区間の端・mod の差が負になる, anchor: pitfalls}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：遷移元が連続した範囲の和になる DP を、前の段の累積和で 1 回 O(1) にする。遷移先が範囲なら、いもす法で差分に書いておき後で累積する。
    - **いつ使うか**：
        - 各人に 0〜a_i 個を配る方法の数（上限つきの配り方）
        - N ≤ 100、K ≤ 10^5 程度で、O(NK) は通るが O(NK^2) は通らない
        - dp[i] = Σ_{j=i−R}^{i−L} dp[j] のように、遷移元が連続した範囲の和
        - dp[i] から i+L〜i+R の範囲へ同じ値を配る
    - **計算量**：（執筆時に書く）
    - **前提**：[DP の基本](../dp/dp-basics.md)、[いもす法](../basics/imos.md)
