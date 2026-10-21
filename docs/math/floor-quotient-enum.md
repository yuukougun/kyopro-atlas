---
id: floor-quotient-enum
title: 商の列挙
aliases: [商列挙, enumerate quotients, 数論分块, √N 分割, floor でまとめる, 約数の個数の和]
type: technique
field: math
chapter: floor と商
order: 280
level: 水
kind: [整数論]
prerequisites: [sigma-manipulation, integer-division]
related: [harmonic-sum, floor-sum, sqrt-decomposition, base-conversion, multiplicative-function]
summary: Σ_{i=1}^{N} f(⌊N/i⌋) を、⌊N/i⌋ の値が高々 2√N 種類で同じ値の i が区間をなすことを使って O(√N) で求める。√N を境に「i が小さい側」と「商が小さい側」に分けて考える型にも使う。
complexity: null
signs:
  - {type: phrase, text: 'Σ_{i=1}^{N} ⌊N/i⌋ を求める'}
  - {type: constraint, text: N ≤ 10^12 で i を全部回すと間に合わない}
  - {type: phrase, text: xy ≤ N となる組を数える}
  - {type: shape, text: 'Σ_{i=1}^{N} f(⌊N/i⌋) の形の和'}
acl: []
verify: [enumerate_quotients]
frequency: C
frequency_evidence: recent 0・前提として 1 ページに届く（直接 1）・古い ABC 2 問
sections:
  - {title: 値が O(√N) 種類である理由（i ≤ √N と i > √N）, anchor: why-sqrt}
  - {title: 同じ商になる区間の右端 ⌊N/⌊N/l⌋⌋, anchor: block-end}
  - {title: √N を境に場合分けする（片方を √N まで全探索）, anchor: split-at-sqrt}
  - {title: 調和級数・floor sum との使い分け, anchor: vs-others}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：Σ_{i=1}^{N} f(⌊N/i⌋) を、⌊N/i⌋ の値が高々 2√N 種類で同じ値の i が区間をなすことを使って O(√N) で求める。√N を境に「i が小さい側」と「商が小さい側」に分けて考える型にも使う。
    - **いつ使うか**：
        - Σ_{i=1}^{N} ⌊N/i⌋ を求める
        - N ≤ 10^12 で i を全部回すと間に合わない
        - xy ≤ N となる組を数える
        - Σ_{i=1}^{N} f(⌊N/i⌋) の形の和
    - **計算量**：（執筆時に書く）
    - **前提**：[Σ の変形](../math/sigma-manipulation.md)、[整数の割り算と余り](../math/integer-division.md)
