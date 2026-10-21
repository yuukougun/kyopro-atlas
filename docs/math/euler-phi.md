---
id: euler-phi
title: オイラーの φ 関数
aliases: [トーシェント, totient, Euler's totient function, φ(n), 互いに素な数の個数]
type: technique
field: math
chapter: 素数と約数
order: 180
level: 黄
kind: [整数論]
prerequisites: [prime-factorization]
related: [exponent-mod, multiplicative-order, spf-sieve, multiplicative-function, mobius-function, burnside-lemma]
summary: 1..n で n と互いに素な数の個数 φ(n) を、素因数分解から φ(n) = n Π(1 − 1/p) で求める。オイラーの定理 a^φ(n) ≡ 1 を通じて、位数や指数の mod の計算に使う。
complexity: null
signs:
  - {type: phrase, text: n と互いに素な 1..n の数の個数・既約分数の個数}
  - {type: phrase, text: 位数が d になる元の個数}
  - {type: phrase, text: a^k ≡ 1 (mod n) となる最小の k を探す}
acl: []
verify: []
frequency: C
frequency_evidence: recent 0・前提として 2 ページに届く（直接 2）・古い ABC 2 問
sections:
  - {title: 定義と公式 φ(n) = n Π(1 − 1/p)（素因数分解が必要）, anchor: formula}
  - {title: 篩で 1..N の φ を全て求める, anchor: sieve}
  - {title: オイラーの定理 a^φ(n) ≡ 1 と、指数の mod への応用, anchor: euler-theorem}
  - {title: 'Σ_{d|n} φ(d) = n と「位数が d の元は φ(d) 個」', anchor: divisor-sum}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：1..n で n と互いに素な数の個数 φ(n) を、素因数分解から φ(n) = n Π(1 − 1/p) で求める。オイラーの定理 a^φ(n) ≡ 1 を通じて、位数や指数の mod の計算に使う。
    - **いつ使うか**：
        - n と互いに素な 1..n の数の個数・既約分数の個数
        - 位数が d になる元の個数
        - a^k ≡ 1 (mod n) となる最小の k を探す
    - **計算量**：（執筆時に書く）
    - **前提**：[素因数分解とルジャンドルの公式](../math/prime-factorization.md)
