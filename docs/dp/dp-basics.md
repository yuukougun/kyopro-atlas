---
id: dp-basics
title: DP の基本
aliases: [動的計画法, DP, Dynamic Programming, 漸化式, 配る DP, 貰う DP, push 型, pull 型]
type: technique
field: dp
chapter: DP の考え方
order: 10
level: 基礎
kind: [DP]
prerequisites: [brute-force]
related: [memoized-recursion, dp-dag, dp-state-design, dp-prefix-sum, dp-speedup-overview, greedy-basics#when-greedy-fails, expected-value-dp, game-basics#game-dp]
summary: 全探索で同じ部分問題が何度も現れるとき、状態ごとの最良値や場合の数を表に 1 回だけ求めて使い回す。状態・遷移・初期値・答えの取り出し方の 4 つを決めれば書ける。
complexity: null
signs:
  - {type: phrase, text: 前から順に 1 つずつ選んでいくときの、〜の最小値・最大値}
  - {type: phrase, text: ちょうど X にできるか（可否の判定）}
  - {type: constraint, text: N ≤ 10^5 程度で、各位置の選択肢が数通り（全探索だと K^N 通り）}
  - {type: shape, text: 'dp[i] が dp[i−1]・dp[i−2] など定数個の前の状態から決まる'}
acl: []
frequency: A
frequency_evidence: recent 0・前提として 63 ページに届く（直接 19）・古い ABC 6 問
sections:
  - {title: 状態・遷移・初期値・答えの 4 つを決める, anchor: four-parts}
  - {title: 最適化・数え上げ・可否判定を同じ骨組みで書く（演算と単位元・到達できない状態の表し方）, anchor: three-kinds}
  - {title: 配る DP と貰う DP（どちらも各遷移を 1 回ずつ使う）, anchor: dp-push-pull}
  - {title: 貰う形にすると遷移元が区間になる（累積和でまとめる高速化へ）, anchor: pull-to-prefix-sum, level: 水}
  - {title: 貪欲で解けないことの確かめ方（反例から DP へ）, anchor: greedy-counterexample}
  - {title: DP の型の地図（列・区間・集合・桁・木・順列・確率・ゲーム・高速化）, anchor: map}
  - {title: 落とし穴：到達できない状態の INF に足して溢れる・mod の取り忘れ・添字のずれ, anchor: pitfalls}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：全探索で同じ部分問題が何度も現れるとき、状態ごとの最良値や場合の数を表に 1 回だけ求めて使い回す。状態・遷移・初期値・答えの取り出し方の 4 つを決めれば書ける。
    - **いつ使うか**：
        - 前から順に 1 つずつ選んでいくときの、〜の最小値・最大値
        - ちょうど X にできるか（可否の判定）
        - N ≤ 10^5 程度で、各位置の選択肢が数通り（全探索だと K^N 通り）
        - dp[i] が dp[i−1]・dp[i−2] など定数個の前の状態から決まる
    - **計算量**：（執筆時に書く）
    - **前提**：[全探索の設計](../basics/brute-force.md)
