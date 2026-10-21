---
id: prime-exponent-vector
title: 素因数の指数で考える
aliases: [指数ベクトル, 平方因子, squarefree, smooth 数, 平方数の判定, 素数ごとに独立]
type: technique
field: math
chapter: 素数と約数
order: 170
level: 基礎
kind: [整数論]
prerequisites: [prime-factorization]
related: [gcd-lcm, spf-sieve, hashing-for-sets, meet-in-the-middle]
summary: 積が平方数になる組・巨大な lcm・割り切れる回数などを、整数を素数ごとの指数のベクトルとみて素数ごとに独立に考える。積は和、gcd は min、lcm は max、平方数は全成分が偶数になる。
complexity: null
signs:
  - {type: phrase, text: 積が平方数（立方数）になる組を数える}
  - {type: phrase, text: 多数の数の lcm を mod で求める}
  - {type: phrase, text: 2 で割り切れる回数・各素数の指数をそろえる}
  - {type: phrase, text: 素因数が P 以下の数（P-smooth 数）を数える}
acl: []
verify: []
frequency: B
frequency_evidence: recent 0・前提として届くページなし・古い ABC 5 問
sections:
  - {title: 積は和・gcd は min・lcm は max・割り切りは全成分で ≤（算術の基本定理）, anchor: exponent-ops}
  - {title: 平方因子を除いた核で、積が平方数になる組を数える（0 の扱い）, anchor: squarefree-kernel}
  - {title: 巨大な lcm を指数の最大で持つ, anchor: huge-lcm, level: 水}
  - {title: 特定の素数（2 など）の指数だけを比べる, anchor: single-prime, level: 水}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：積が平方数になる組・巨大な lcm・割り切れる回数などを、整数を素数ごとの指数のベクトルとみて素数ごとに独立に考える。積は和、gcd は min、lcm は max、平方数は全成分が偶数になる。
    - **いつ使うか**：
        - 積が平方数（立方数）になる組を数える
        - 多数の数の lcm を mod で求める
        - 2 で割り切れる回数・各素数の指数をそろえる
        - 素因数が P 以下の数（P-smooth 数）を数える
    - **計算量**：（執筆時に書く）
    - **前提**：[素因数分解とルジャンドルの公式](../math/prime-factorization.md)
