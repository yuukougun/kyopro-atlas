---
id: knapsack-01
title: ナップサック DP
aliases: [0-1 ナップサック, ナップサック, ナップザック, Knapsack Problem, 0-1 Knapsack, 個数制限なしナップサック, 個数無制限ナップサック, Unbounded Knapsack, 個数制限付きナップサック, 多重ナップサック, コイン問題, 配列の使い回し, 1 次元化]
type: technique
field: dp
chapter: 列の DP
order: 100
level: 基礎
kind: [DP]
prerequisites: [dp-basics]
related: [subset-sum, dp-dimension-reduction, meet-in-the-middle#vs-knapsack, knapsack-undo, exchange-argument-dp, tree-dp-square, greedy-basics, divide-and-conquer#range-knapsack]
summary: 品物を 1 つずつ「選ぶ・選ばない」で分け、重さの合計ごとに価値の最大を求める。1 次元の配列で書くと、ループの向きで 0-1（大きい方から）と個数制限なし（小さい方から）が分かれる。
complexity: null
signs:
  - {type: phrase, text: 重さの合計が W 以下で価値の和の最大}
  - {type: phrase, text: 同じものを何度でも使える（硬貨・魔法）}
  - {type: phrase, text: 各品物は B_i 個まで使える}
  - {type: constraint, text: N ≤ 100〜5000、W ≤ 10^4〜10^5（O(NW) が通る）}
acl: []
frequency: A
frequency_evidence: recent 1（abc461_f）・前提として 5 ページに届く（直接 5）・古い ABC 13 問
sections:
  - {title: 'dp[i][w] の意味（「以下」と「ちょうど」で初期値と答えが変わる）', anchor: meaning}
  - {title: 配列の使い回しとループの向き（0-1 は大きい方から、個数制限なしは小さい方から）, anchor: dp-rolling-array}
  - {title: 個数制限なし（数え上げでは品物と和のループの内外で組合せと列が分かれる）, anchor: knapsack-unbounded}
  - {title: 多次元の重さ・上限で打ち切る・グループから 1 つ選ぶ, anchor: variants}
  - {title: 計算量で解法を切り替える（重さ・価値・N のどれが小さいか）, anchor: choose-by-size, level: 水}
  - {title: 個数制限付き（素朴な展開・二進分解・余りごとのスライド最小値）, anchor: knapsack-bounded, level: 青}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：品物を 1 つずつ「選ぶ・選ばない」で分け、重さの合計ごとに価値の最大を求める。1 次元の配列で書くと、ループの向きで 0-1（大きい方から）と個数制限なし（小さい方から）が分かれる。
    - **いつ使うか**：
        - 重さの合計が W 以下で価値の和の最大
        - 同じものを何度でも使える（硬貨・魔法）
        - 各品物は B_i 個まで使える
        - N ≤ 100〜5000、W ≤ 10&#94;4〜10&#94;5（O(NW) が通る）
    - **計算量**：（執筆時に書く）
    - **前提**：[DP の基本](../dp/dp-basics.md)
