---
id: geometric-series-mod
title: 等比数列の和を mod で求める
aliases: [等比級数, geometric series, repunit, Σ A^i, 同じ数字を並べた数]
type: technique
field: math
chapter: mod の計算
order: 80
level: 基礎
kind: [整数論, ダブリング・分割統治]
prerequisites: [mod-inverse]
related: [matrix-power, doubling, digit-and-mod, exponent-mod]
summary: 1 + r + … + r^(n−1) を mod で求める。素数 mod で r ≢ 1 なら (r^n − 1)/(r − 1)、法が任意なら和を半分に割る漸化式か行列の累乗で O(log n) にする。
complexity: null
signs:
  - {type: phrase, text: 同じ数字列を M 回並べてできる数を mod で求める}
  - {type: phrase, text: 法 M が入力で与えられ、素数とは限らない}
  - {type: constraint, text: 項数 N ≤ 10^12〜10^18 の等比数列の和を、素数とは限らない法 M ≤ 10^9 で求める}
  - {type: shape, text: 'Σ_{i=0}^{N−1} A^i の形の和'}
acl: []
verify: []
frequency: B
frequency_evidence: recent 0・前提として届くページなし・古い ABC 3 問
sections:
  - {title: 公式 (r^n − 1)/(r − 1) と r ≡ 1 の場合分け, anchor: formula}
  - {title: 法が任意のとき：S(2k) = S(k)(1 + r^k) で半分に割る, anchor: halving, level: 水}
  - {title: '2×2 行列 [[r, 1], [0, 1]] の累乗による別解', anchor: matrix, level: 青}
  - {title: 同じ数字列を並べた数は公比 10^d の等比数列の和になる, anchor: repeated-digits}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：1 + r + … + r^(n−1) を mod で求める。素数 mod で r ≢ 1 なら (r^n − 1)/(r − 1)、法が任意なら和を半分に割る漸化式か行列の累乗で O(log n) にする。
    - **いつ使うか**：
        - 同じ数字列を M 回並べてできる数を mod で求める
        - 法 M が入力で与えられ、素数とは限らない
        - 項数 N ≤ 10&#94;12〜10&#94;18 の等比数列の和を、素数とは限らない法 M ≤ 10&#94;9 で求める
        - Σ_{i=0}^{N−1} A^i の形の和
    - **計算量**：（執筆時に書く）
    - **前提**：[逆元と mod での割り算](../math/mod-inverse.md)
