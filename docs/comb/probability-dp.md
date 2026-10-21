---
id: probability-dp
title: 確率 DP
aliases: [前向きに確率を配る, 到達確率, 分布を求める DP, ランダムウォーク, random walk]
type: technique
field: comb
chapter: 確率・期待値
order: 370
level: 水
kind: [確率・期待値, DP]
prerequisites: [probability-basics, dp-basics]
related: [expected-value-dp, rational-mod, probability-symmetry, dp-state-design, matrix-power#dp-transition, lattice-paths#independent-axes]
summary: dp[t][s] = 時刻 t に状態 s にいる確率を、初期状態の 1 から前向きに配って求める。確率の和が 1 に保たれることが検算になり、時刻が決まっている問題や分布そのものが要る問題に向く。
complexity: null
signs:
  - {type: phrase, text: K 回の操作の後に〜である確率}
  - {type: phrase, text: どちらが先にゴールするかの確率}
  - {type: phrase, text: 時刻 T に〜している確率}
  - {type: phrase, text: N 回ランダムに上下左右へ動いた後の位置}
acl: [modint]
frequency: B
frequency_evidence: recent 1（abc463_g）・前提として届くページなし・古い ABC 5 問
sections:
  - {title: 状態に到達する確率を前から配る（和が 1 の検算）, anchor: forward}
  - {title: 状態の設計：まとめる・上限で打ち切る・到達する値だけ持つ, anchor: state-design}
  - {title: 時刻ごとに配る, anchor: by-time}
  - {title: 期待値 DP との使い分け（前向きと後ろ向き）, anchor: vs-expected-value-dp}
  - {title: ランダムウォークと二項係数, anchor: random-walk, level: 青}
  - {title: 同じ遷移を多数回行うときは行列累乗へ, anchor: matrix-power, level: 黄}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：dp\[t][s] = 時刻 t に状態 s にいる確率を、初期状態の 1 から前向きに配って求める。確率の和が 1 に保たれることが検算になり、時刻が決まっている問題や分布そのものが要る問題に向く。
    - **いつ使うか**：
        - K 回の操作の後に〜である確率
        - どちらが先にゴールするかの確率
        - 時刻 T に〜している確率
        - N 回ランダムに上下左右へ動いた後の位置
    - **計算量**：（執筆時に書く）
    - **前提**：[確率の基本](../comb/probability-basics.md)、[DP の基本](../dp/dp-basics.md)
