---
id: lagrange-interpolation
title: ラグランジュ補間とべき乗和
aliases: [Lagrange interpolation, 多項式補間, 補間, べき乗和, Faulhaber, 答えが多項式になる]
type: overview
field: math
chapter: 畳み込みと多項式
order: 420
level: 発展
kind: [畳み込み・多項式]
prerequisites: [mod-inverse]
related: [binomial-precompute, fps-basics, gaussian-elimination]
summary: d 次多項式は d + 1 点の値で決まるので、x = 0..d での値から任意の x での値を階乗の逆元を使って O(d) で求める。べき乗和 Σ i^k や、答えが N の多項式になる DP を小さい N で計算して補間するのに使う。
complexity: null
signs:
  - {type: phrase, text: 答えが N の多項式になる（小さい N で実験すると分かる）}
  - {type: phrase, text: 'Σ_{i=1}^{N} i^k を N ≤ 10^18 で求める'}
  - {type: phrase, text: mod p で p 点の値から多項式の係数を復元する}
  - {type: shape, text: 答え f(N) が N の d 次多項式になる}
acl: []
verify: [shift_of_sampling_points_of_polynomial, sum_of_exponential_times_polynomial]
frequency: C
frequency_evidence: recent 0・前提として届くページなし・古い ABC 2 問
sections:
  - {title: d + 1 点で多項式が決まる理由, anchor: uniqueness}
  - {title: x = 0..d のときの O(d) の補間（階乗の逆元）, anchor: linear-time}
  - {title: べき乗和・多項式になる DP への応用, anchor: applications}
  - {title: 係数の復元（O(d²)）, anchor: coefficients}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：d 次多項式は d + 1 点の値で決まるので、x = 0..d での値から任意の x での値を階乗の逆元を使って O(d) で求める。べき乗和 Σ i^k や、答えが N の多項式になる DP を小さい N で計算して補間するのに使う。
    - **いつ使うか**：
        - 答えが N の多項式になる（小さい N で実験すると分かる）
        - Σ_{i=1}^{N} i^k を N ≤ 10^18 で求める
        - mod p で p 点の値から多項式の係数を復元する
        - 答え f(N) が N の d 次多項式になる
    - **計算量**：（執筆時に書く）
    - **前提**：[逆元と mod での割り算](../math/mod-inverse.md)
