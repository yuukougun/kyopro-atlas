---
id: interval-dp
title: 区間 DP
aliases: ['dp[l][r]', Interval DP, Range DP, 区間を状態にする DP]
type: technique
field: dp
chapter: 状態の形で分かれる DP
order: 200
level: 青
kind: [DP]
prerequisites: [dp-order, memoized-recursion]
related: [interval-dp-advanced, dp-sequence-partition, monge#knuth-yao, minimax, exchange-argument-dp, palindrome]
summary: dp[l][r]＝区間 [l, r) について求めた値を、内側の短い区間の値から求める。区間の短い順に埋めれば依存関係が満たされ、分割点を全探索する O(N^3) が基本になる。
complexity: null
signs:
  - {type: constraint, text: N ≤ 300〜500 で O(N^3) が通る}
  - {type: phrase, text: 隣り合うものを合体させる・消す操作のコストの最小}
  - {type: phrase, text: 列の両端から交互に取っていく}
  - {type: phrase, text: 括弧の対応・回文}
acl: []
frequency: B
frequency_evidence: recent 0・前提として 1 ページに届く（直接 1）・古い ABC 7 問
sections:
  - {title: 長さ順に埋める理由（l を昇順に回すと困ること）, anchor: by-length}
  - {title: 分割点型（最後に行う操作で区間を 2 つに割る）, anchor: split-point}
  - {title: 両端型（左端か右端を取る）, anchor: ends}
  - {title: 最後に残す・最後に消すものを決める型, anchor: last-operation}
  - {title: 端の相手で分ける数え上げ（二項係数で操作の順序を混ぜる）, anchor: pair-with-left-end}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：dp\[l][r]＝区間 [l, r) について求めた値を、内側の短い区間の値から求める。区間の短い順に埋めれば依存関係が満たされ、分割点を全探索する O(N^3) が基本になる。
    - **いつ使うか**：
        - N ≤ 300〜500 で O(N^3) が通る
        - 隣り合うものを合体させる・消す操作のコストの最小
        - 列の両端から交互に取っていく
        - 括弧の対応・回文
    - **計算量**：（執筆時に書く）
    - **前提**：[DP の計算順序](../dp/dp-order.md)、[メモ化再帰](../dp/memoized-recursion.md)
