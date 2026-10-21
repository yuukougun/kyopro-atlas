---
id: prime-factorization
title: 素因数分解とルジャンドルの公式
aliases: [prime factorization, Legendre's formula, 階乗の素因数, 末尾の 0 の個数, v_p(n!)]
type: technique
field: math
chapter: 素数と約数
order: 110
level: 基礎
kind: [整数論]
prerequisites: [divisor-enum]
related: [spf-sieve, prime-exponent-vector, divisor-count-bound, miller-rabin, stars-and-bars]
summary: √N までの数で割れるだけ割り、残りが 1 より大きければそれも素数として、N = Π p^e を O(√N) で求める。N! の素因数 p の指数はルジャンドルの公式 Σ ⌊N/p^k⌋ で直接求める。
complexity: null
signs:
  - {type: phrase, text: 素数ごとに独立に考えられる（積・割り切れる回数）}
  - {type: phrase, text: N! の末尾の 0 の個数、N! が K の倍数になる最小の N}
  - {type: phrase, text: 積が M になる数列の数}
  - {type: constraint, text: N ≤ 10^12 程度の数を1つだけ素因数分解する}
acl: []
verify: []
frequency: A
frequency_evidence: recent 0・前提として 7 ページに届く（直接 5）・古い ABC 6 問
sections:
  - {title: 割れるだけ割る手順と、残った数が素数である理由, anchor: procedure}
  - {title: 素因数ごとに独立に考える（指数の組合せ）, anchor: per-prime}
  - {title: N! の素因数分解とルジャンドルの公式, anchor: legendre}
  - {title: 使い分け：1個なら試し割り、多数なら最小素因数の篩（10^18 は大きな数の素因数分解へ）, anchor: which-method}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：√N までの数で割れるだけ割り、残りが 1 より大きければそれも素数として、N = Π p^e を O(√N) で求める。N! の素因数 p の指数はルジャンドルの公式 Σ ⌊N/p^k⌋ で直接求める。
    - **いつ使うか**：
        - 素数ごとに独立に考えられる（積・割り切れる回数）
        - N! の末尾の 0 の個数、N! が K の倍数になる最小の N
        - 積が M になる数列の数
        - N ≤ 10^12 程度の数を1つだけ素因数分解する
    - **計算量**：（執筆時に書く）
    - **前提**：[約数列挙と素数判定](../math/divisor-enum.md)
