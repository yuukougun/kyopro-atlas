---
id: segmented-sieve
title: 区間篩
aliases: [区間ふるい, segmented sieve, 区間の素因数分解]
type: technique
field: math
chapter: 素数と約数
order: 160
level: 水
kind: [整数論]
prerequisites: [sieve-eratosthenes]
related: [prime-factorization, spf-sieve]
summary: L が 10^12 と大きくても R − L が 10^6 程度なら、√R までの素数で区間 [L, R] だけを篩える。区間の各数の素数判定や素因数分解を O((R−L) log log R + √R) で行う。
complexity: null
signs:
  - {type: constraint, text: 'L, R ≤ 10^12 で R − L ≤ 10^6'}
  - {type: phrase, text: 連続する区間の数をそれぞれ素因数分解する}
  - {type: phrase, text: '二項係数 C(N, K) の分子 N−K+1..N を素因数分解する'}
acl: []
verify: []
frequency: C
frequency_evidence: recent 0・前提として届くページなし・古い ABC 2 問
sections:
  - {title: √R までの素数で十分な理由, anchor: why-sqrt}
  - {title: 区間で最初の p の倍数 ⌈L/p⌉·p の求め方と、p 自身・L = 1 の扱い, anchor: first-multiple}
  - {title: 区間の各数の素因数分解（√R までで割った残りは素数）, anchor: factorize-range}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：L が 10^12 と大きくても R − L が 10^6 程度なら、√R までの素数で区間 [L, R] だけを篩える。区間の各数の素数判定や素因数分解を O((R−L) log log R + √R) で行う。
    - **いつ使うか**：
        - L, R ≤ 10^12 で R − L ≤ 10^6
        - 連続する区間の数をそれぞれ素因数分解する
        - 二項係数 C(N, K) の分子 N−K+1..N を素因数分解する
    - **計算量**：（執筆時に書く）
    - **前提**：[エラトステネスの篩](../math/sieve-eratosthenes.md)
