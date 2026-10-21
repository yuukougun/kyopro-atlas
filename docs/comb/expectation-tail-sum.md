---
id: expectation-tail-sum
title: 期待値と確率の変換
aliases: ['E[X] = Σ P(X ≥ k)', tail sum, 期待値と確率の行き来, 最大値の期待値, K 番目の値の期待値]
type: technique
field: comb
chapter: 確率・期待値
order: 410
level: 黄
kind: [確率・期待値]
prerequisites: [linearity-of-expectation, counting-mindset]
related: [coupon-collector, continuous-probability, binomial-precompute]
summary: 非負整数の確率変数 X について E[X] = Σ_{k≥1} P(X ≥ k) が成り立つ。最大値・最小値・K 番目の値の期待値を「X ≥ k となる確率」の和に直して求め、「〜になるまでの回数」の期待値にも使う。
complexity: null
signs:
  - {type: phrase, text: 最大値（最小値・K 番目の値）の期待値}
  - {type: phrase, text: 〜がそろうまでに取り出す回数の期待値}
  - {type: constraint, text: 値の範囲 M ≤ 5000 程度で、各 k について P(X ≥ k) を数える}
acl: []
frequency: C
frequency_evidence: recent 0・前提として 1 ページに届く（直接 1）・古い ABC 2 問
sections:
  - {title: 'X = Σ [X ≥ k] と線形性', anchor: identity}
  - {title: 最大値・K 番目の値：「すべて k 未満」の余事象, anchor: kth-value}
  - {title: 「〜になるまでの回数」= Σ P(k 回目までに終わらない), anchor: waiting-time}
  - {title: 連続値の場合（積分）, anchor: continuous, level: 発展}
  - {title: 「ちょうど」と「以上」の行き来, anchor: exactly-vs-at-least}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：非負整数の確率変数 X について E[X] = Σ_{k≥1} P(X ≥ k) が成り立つ。最大値・最小値・K 番目の値の期待値を「X ≥ k となる確率」の和に直して求め、「〜になるまでの回数」の期待値にも使う。
    - **いつ使うか**：
        - 最大値（最小値・K 番目の値）の期待値
        - 〜がそろうまでに取り出す回数の期待値
        - 値の範囲 M ≤ 5000 程度で、各 k について P(X ≥ k) を数える
    - **計算量**：（執筆時に書く）
    - **前提**：[期待値の線形性と指示確率変数](../comb/linearity-of-expectation.md)、[数え上げの考え方](../comb/counting-mindset.md)
