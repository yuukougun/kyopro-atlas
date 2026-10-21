---
id: mobius-function
title: メビウス関数とメビウス反転
aliases: [メビウス関数, μ, メビウス反転, Möbius function, Mobius inversion]
type: technique
field: comb
chapter: 包除の系統
order: 220
level: 黄
kind: [数え上げ, 整数論]
prerequisites: [divisor-inclusion-exclusion, sieve-eratosthenes]
related: [zeta-mobius-divisor, multiplicative-function, floor-quotient-enum, euler-phi]
summary: 約数にわたる和 F(n) = Σ_{d|n} f(d) から f をメビウス関数 μ で戻す（メビウス反転）。[gcd = 1] = Σ_{d|gcd} μ(d) と置き換えて和の順序を入れ替えるのが典型である。
complexity: null
signs:
  - {type: phrase, text: 'gcd(i, j) = 1 となる組の個数・和'}
  - {type: phrase, text: Σ gcd や Σ lcm を求める}
  - {type: constraint, text: N ≤ 10^6 程度で、μ を篩で前計算できる}
acl: []
frequency: C
frequency_evidence: recent 0・前提として届くページなし・古い ABC 1 問
sections:
  - {title: μ の定義と、約数についての和が n = 1 のときだけ 1 になる性質, anchor: definition}
  - {title: メビウス反転, anchor: inversion}
  - {title: 「gcd が 1」の条件の置き換えと和の入れ替え, anchor: gcd-one}
  - {title: μ を篩で作る, anchor: sieve}
  - {title: 商の列挙で同じ値の範囲を束ねる, anchor: quotient, level: 発展}
  - {title: 約数包除との書き換え, anchor: vs-divisor-ie}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：約数にわたる和 F(n) = Σ_{d|n} f(d) から f をメビウス関数 μ で戻す（メビウス反転）。[gcd = 1] = Σ_{d|gcd} μ(d) と置き換えて和の順序を入れ替えるのが典型である。
    - **いつ使うか**：
        - gcd(i, j) = 1 となる組の個数・和
        - Σ gcd や Σ lcm を求める
        - N ≤ 10^6 程度で、μ を篩で前計算できる
    - **計算量**：（執筆時に書く）
    - **前提**：[約数包除](../comb/divisor-inclusion-exclusion.md)、[エラトステネスの篩](../math/sieve-eratosthenes.md)
