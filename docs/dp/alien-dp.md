---
id: alien-dp
title: Alien DP
aliases: [Aliens trick, WQS 二分, Lagrangian Relaxation, Lagrange 緩和, 取り消し付きの貪欲]
type: overview
field: dp
chapter: DP の高速化
order: 370
level: 発展
kind: [DP, 二分探索]
prerequisites: [monge, binary-search]
related: [greedy-priority-queue#regret, dp-sequence-partition, ternary-search#convexity, priority-queue, slope-trick]
summary: 「ちょうど K 個選ぶ」制約のついた最適化で答えが K について凸なら、1 個あたりの罰金 λ を足して制約を外した問題を解き、選ばれる個数が K になる λ を二分探索する。
complexity: null
signs:
  - {type: phrase, text: 'ちょうど K 個選ぶ・K 個の区間に分ける（N, K ≤ 2×10^5）'}
  - {type: phrase, text: 隣り合わない k 個を選ぶ和の最大を、すべての k について答える}
  - {type: shape, text: K 個選ぶときの答え f(K) が K について凸（1 個増やすときの得が、個数が増えるほど減る）}
acl: []
frequency: B
frequency_evidence: recent 1（abc464_g）・前提として届くページなし・古い ABC 3 問
sections:
  - {title: 罰金 λ で個数の制約を外す（凸性が要る理由）, anchor: penalty}
  - {title: λ の二分探索と、同じ値が並ぶときの扱い, anchor: binary-search-lambda}
  - {title: 取り消し付きの貪欲で解ける場合（優先度付きキュー）, anchor: undoable-greedy}
  - {title: Monge な区間分割と組み合わせる, anchor: with-monge}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：「ちょうど K 個選ぶ」制約のついた最適化で答えが K について凸なら、1 個あたりの罰金 λ を足して制約を外した問題を解き、選ばれる個数が K になる λ を二分探索する。
    - **いつ使うか**：
        - ちょうど K 個選ぶ・K 個の区間に分ける（N, K ≤ 2×10^5）
        - 隣り合わない k 個を選ぶ和の最大を、すべての k について答える
        - K 個選ぶときの答え f(K) が K について凸（1 個増やすときの得が、個数が増えるほど減る）
    - **計算量**：（執筆時に書く）
    - **前提**：[Monge 性による DP の高速化](../dp/monge.md)、[二分探索](../basics/binary-search.md)
