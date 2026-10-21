---
id: multiplicative-function
title: 乗法的関数の和と素数の個数
aliases: [ディリクレ積, Dirichlet convolution, 杜教筛, Min_25, 乗法的関数の prefix sum, 素数計数, prime counting, Lucy DP, Meissel-Lehmer]
type: overview
field: math
chapter: floor と商
order: 290
level: 発展
kind: [整数論]
prerequisites: [euler-phi, floor-quotient-enum]
related: [mobius-function, zeta-mobius-divisor, spf-sieve, sieve-eratosthenes]
summary: N ≤ 10^10 程度で、φ・μ などの乗法的関数の和 Σ_{n≤N} f(n) や N 以下の素数の個数を、商の列挙を使って O(N^{3/4}/log N) などで求める。関数どうしの関係はディリクレ積で表す。
complexity: null
signs:
  - {type: constraint, text: 'N ≤ 10^10〜10^11 で Σ_{n≤N} f(n)（f は φ・約数の個数など）を求める'}
  - {type: phrase, text: N 以下の素数の個数・素数の和}
acl: []
verify: [counting_primes, sum_of_totient_function, sum_of_multiplicative_function]
frequency: C
frequency_evidence: recent 0・前提として届くページなし・古い ABC 1 問
sections:
  - {title: 乗法的関数（φ・μ・d・σ）とディリクレ積（φ * 1 = id など）, anchor: dirichlet}
  - {title: 和の求め方の概要（杜教筛・Lucy DP・Min_25）, anchor: prefix-sums}
  - {title: 素数の個数・素数の和（Lucy DP）, anchor: prime-counting}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：N ≤ 10^10 程度で、φ・μ などの乗法的関数の和 Σ_{n≤N} f(n) や N 以下の素数の個数を、商の列挙を使って O(N^{3/4}/log N) などで求める。関数どうしの関係はディリクレ積で表す。
    - **いつ使うか**：
        - N ≤ 10&#94;10〜10&#94;11 で Σ_{n≤N} f(n)（f は φ・約数の個数など）を求める
        - N 以下の素数の個数・素数の和
    - **計算量**：（執筆時に書く）
    - **前提**：[オイラーの φ 関数](../math/euler-phi.md)、[商の列挙](../math/floor-quotient-enum.md)
