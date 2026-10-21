---
id: monotonic-stack
title: 単調スタックとスライド最小値
aliases: [monotonic stack, 単調 stack, ヒストグラム内最大長方形, sliding window minimum, 単調 deque, 単調キュー, SWAG, Sliding Window Aggregation, Cartesian Tree, デカルト木]
type: technique
field: ds
chapter: スタックとキュー
order: 90
level: 水
kind: [データ構造, 尺取り・スライド窓]
prerequisites: [stack-techniques]
related: [two-pointers, segment-tree-binary-search, sparse-table, contribution, dp-segment-tree, divide-and-conquer]
summary: 各要素について「左（右）で初めて自分より大きい（小さい）要素」を、添字を単調に積んだスタックで全体 O(N) で求める。同じ考え方で幅 K の窓の最小値を deque で O(N) で求め、Cartesian tree も作れる。
complexity: null
signs:
  - {type: phrase, text: 左（右）で初めて自分より大きい（小さい）要素の位置}
  - {type: phrase, text: 各ビルから見えるビルの数・すべての区間の最小値の和}
  - {type: phrase, text: 長さ K のすべての区間の最小値（最大値）}
  - {type: shape, text: 'dp[i] = min(dp[i−K..i−1]) + c のように、直前 K 個の最小値で決まる遷移'}
  - {type: constraint, text: N ≤ 2×10^5 で、各要素から左右を見ていくと O(N^2) になる}
acl: []
verify: [queue_operate_all_composite, deque_operate_all_composite]
frequency: B
frequency_evidence: recent 1（abc480_g）・前提として届くページなし・古い ABC 5 問
sections:
  - {title: 単調スタックの手順と保つ性質（中の値は単調。各添字は 1 回積まれ 1 回降ろされるので O(N)）, anchor: procedure}
  - {title: ヒストグラムの最大長方形, anchor: histogram}
  - {title: i が最大（最小）になる区間の数 (i − L)(R − i) と寄与の数え上げ（同じ値は片側 ≤・片側 <）, anchor: contribution}
  - {title: 見えるビルの数・水位のシミュレーション, anchor: visible}
  - {title: スライド最小値（単調 deque。末尾から支配される要素を捨て、先頭が窓から出たら捨てる）, anchor: sliding-window-minimum}
  - {title: DP の遷移の高速化に使う（→ DP の章のセグメント木・スライド最小値による高速化）, anchor: dp-transition}
  - {title: 使い分け（区間の最大値を多数聞くならセグメント木・Sparse Table、窓の最小値は multiset でも書ける）, anchor: choosing}
  - {title: Cartesian tree（最大値で区間を左右に割る再帰を O(N) で作る）, anchor: cartesian-tree, level: 黄}
  - {title: SWAG：スタック 2 本で作る総積つきキュー（gcd・行列・一次関数の合成の窓）, anchor: swag, level: 発展}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：各要素について「左（右）で初めて自分より大きい（小さい）要素」を、添字を単調に積んだスタックで全体 O(N) で求める。同じ考え方で幅 K の窓の最小値を deque で O(N) で求め、Cartesian tree も作れる。
    - **いつ使うか**：
        - 左（右）で初めて自分より大きい（小さい）要素の位置
        - 各ビルから見えるビルの数・すべての区間の最小値の和
        - 長さ K のすべての区間の最小値（最大値）
        - dp[i] = min(dp[i−K..i−1]) + c のように、直前 K 個の最小値で決まる遷移
        - N ≤ 2×10^5 で、各要素から左右を見ていくと O(N^2) になる
    - **計算量**：（執筆時に書く）
    - **前提**：[スタック・キュー・deque の使いどころ](../ds/stack-techniques.md)
