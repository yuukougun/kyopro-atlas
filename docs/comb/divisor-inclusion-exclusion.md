---
id: divisor-inclusion-exclusion
title: 約数包除
aliases: [約数系包除, gcd がちょうど g, 倍数から引く, 互いに素な組の数, gcd の総和]
type: technique
field: comb
chapter: 包除の系統
order: 200
level: 青
kind: [数え上げ, 整数論]
prerequisites: [counting-mindset, gcd-lcm, harmonic-sum]
related: [mobius-function, zeta-mobius-divisor, euler-phi, burnside-lemma, inclusion-exclusion, divisors-and-multiples]
summary: gcd がちょうど g のものの個数 f(g) を、すべて g の倍数のものの個数 F(g) から大きい g の順に f(g) = F(g) − f(2g) − f(3g) − … で求める。全体で O(N log N) になる。
complexity: null
signs:
  - {type: phrase, text: gcd の総和を求める}
  - {type: phrase, text: gcd が 1 になる（互いに素な）組の個数}
  - {type: phrase, text: 最小周期が d の列（文字列）の個数}
  - {type: constraint, text: 値の上限 ≤ 10^6 程度で、すべての g について数える}
acl: []
frequency: B
frequency_evidence: recent 0・前提として 2 ページに届く（直接 2）・古い ABC 4 問
sections:
  - {title: '「g の倍数」は gcd = g, 2g, 3g, … に排反に分かれる', anchor: partition}
  - {title: 大きい g から引く理由と計算量 O(N log N), anchor: order}
  - {title: gcd の総和・互いに素な組, anchor: gcd-sum}
  - {title: 周期の数え上げ（約数の周期で重複した分を引く）, anchor: period}
  - {title: 完全累乗などの重複を指数ごとに除く, anchor: perfect-powers}
  - {title: メビウス関数での書き方との対応, anchor: vs-mobius}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：gcd がちょうど g のものの個数 f(g) を、すべて g の倍数のものの個数 F(g) から大きい g の順に f(g) = F(g) − f(2g) − f(3g) − … で求める。全体で O(N log N) になる。
    - **いつ使うか**：
        - gcd の総和を求める
        - gcd が 1 になる（互いに素な）組の個数
        - 最小周期が d の列（文字列）の個数
        - 値の上限 ≤ 10^6 程度で、すべての g について数える
    - **計算量**：（執筆時に書く）
    - **前提**：[数え上げの考え方](../comb/counting-mindset.md)、[GCD・LCM とユークリッドの互除法](../math/gcd-lcm.md)、[調和級数と倍数の列挙](../math/harmonic-sum.md)
