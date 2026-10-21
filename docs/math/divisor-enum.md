---
id: divisor-enum
title: 約数列挙と素数判定
aliases: [試し割り, trial division, divisor enumeration, primality test, √N まで調べる, 約数の総和]
type: technique
field: math
chapter: 素数と約数
order: 100
level: 基礎
kind: [整数論, 全探索]
prerequisites: [integer-division]
related: [prime-factorization, divisor-count-bound, sieve-eratosthenes, brute-force, miller-rabin, divisors-and-multiples#enumerate]
summary: d と N/d が √N を境に対になることを使い、素数判定と約数の列挙を O(√N) で行う。答えの候補が N の約数に限られる問題で、約数を全部試す全探索に使う。
complexity: null
signs:
  - {type: constraint, text: N ≤ 10^12 程度（√N ≤ 10^6）の約数・素数判定}
  - {type: phrase, text: a × b = N となる組を調べる}
  - {type: phrase, text: 答え（gcd・周期・個数）が N の約数のどれかになる}
  - {type: phrase, text: X 以上の最小の素数}
acl: []
verify: []
frequency: B
frequency_evidence: recent 1（abc461_f）・前提として 12 ページに届く（直接 2）・古い ABC 4 問
sections:
  - {title: √N まで調べればよい理由（約数の対）, anchor: why-sqrt}
  - {title: 素数判定（試し割り）, anchor: primality}
  - {title: 約数の列挙とソート・平方数での重複, anchor: enumerate}
  - {title: 約数の個数 Π(e+1) と約数の総和の公式, anchor: count-and-sum}
  - {title: 答えの候補が約数に限られる型（gcd の最大・商と余り・割るか引くか）, anchor: candidates}
  - {title: 落とし穴：sqrt を double で求める・i*i のあふれ, anchor: pitfalls}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：d と N/d が √N を境に対になることを使い、素数判定と約数の列挙を O(√N) で行う。答えの候補が N の約数に限られる問題で、約数を全部試す全探索に使う。
    - **いつ使うか**：
        - N ≤ 10^12 程度（√N ≤ 10^6）の約数・素数判定
        - a × b = N となる組を調べる
        - 答え（gcd・周期・個数）が N の約数のどれかになる
        - X 以上の最小の素数
    - **計算量**：（執筆時に書く）
    - **前提**：[整数の割り算と余り](../math/integer-division.md)
