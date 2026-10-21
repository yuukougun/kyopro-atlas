---
id: zeta-mobius-divisor
title: 約数・倍数のゼータ変換とメビウス変換
aliases: [約数ゼータ変換, 倍数ゼータ変換, 約数メビウス変換, 倍数メビウス変換, GCD 畳み込み, LCM 畳み込み, GCD convolution, LCM convolution]
type: technique
field: comb
chapter: 包除の系統
order: 210
level: 青
kind: [数え上げ, 整数論, 畳み込み・多項式]
prerequisites: [divisor-inclusion-exclusion, sieve-eratosthenes]
related: [harmonic-sum#collect-multiples, zeta-mobius-subset, mobius-function, convolution-ntt, hadamard-transform, divisors-and-multiples]
summary: すべての d について d の倍数（約数）にわたる和を求める変換とその逆変換で、素数ごとに累積和を取って O(N log log N) で求める。GCD 畳み込みは倍数の版、LCM 畳み込みは約数の版の変換で求める。
complexity: null
signs:
  - {type: phrase, text: 各値 d について、d の倍数（約数）である要素の個数・和}
  - {type: phrase, text: 'Σ f(gcd(A_i, A_j)) や lcm の総和'}
  - {type: constraint, text: 値の上限 ≤ 10^6 程度で、gcd・lcm ごとに集計する}
acl: []
frequency: B
frequency_evidence: recent 1（abc474_f）・前提として届くページなし・古い ABC 1 問
sections:
  - {title: 素数ごとの累積和で O(N log log N), anchor: per-prime}
  - {title: 逆変換（メビウス変換）と回す向き, anchor: inverse}
  - {title: GCD 畳み込み・LCM 畳み込み, anchor: gcd-lcm-convolution}
  - {title: 部分集合のゼータ変換との対応（指数ベクトルの累積和）, anchor: vs-subset}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：すべての d について d の倍数（約数）にわたる和を求める変換とその逆変換で、素数ごとに累積和を取って O(N log log N) で求める。GCD 畳み込みは倍数の版、LCM 畳み込みは約数の版の変換で求める。
    - **いつ使うか**：
        - 各値 d について、d の倍数（約数）である要素の個数・和
        - Σ f(gcd(A_i, A_j)) や lcm の総和
        - 値の上限 ≤ 10^6 程度で、gcd・lcm ごとに集計する
    - **計算量**：（執筆時に書く）
    - **前提**：[約数包除](../comb/divisor-inclusion-exclusion.md)、[エラトステネスの篩](../math/sieve-eratosthenes.md)
