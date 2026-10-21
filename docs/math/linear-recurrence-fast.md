---
id: linear-recurrence-fast
title: 線形漸化式の高速化
aliases: [きたまさ法, Bostan-Mori, Berlekamp-Massey, Fiduccia, 線形漸化式の第 N 項]
type: overview
field: math
chapter: 畳み込みと多項式
order: 410
level: 発展
kind: [線形代数・行列, 畳み込み・多項式]
prerequisites: [matrix-power, fps-basics]
related: [convolution-ntt]
summary: K 項の線形漸化式の第 N 項を、行列累乗より速くきたまさ法 O(K² log N) や Bostan-Mori O(K log K log N) で求める。最初の 2K 項から漸化式を見つける Berlekamp-Massey も使う。
complexity: null
signs:
  - {type: constraint, text: 線形漸化式の項数 K が数百〜数千で、N ≤ 10^18}
  - {type: phrase, text: 有理式 P(x)/Q(x) の N 次の係数}
  - {type: phrase, text: 答えが線形漸化式を満たしそうだが式が分からない（最初の項から推定する）}
  - {type: shape, text: 'a_n = Σ_{k=1}^{K} c_k a_{n−k} の形の漸化式'}
acl: [convolution]
verify: [kth_term_of_linearly_recurrent_sequence, find_linear_recurrence, consecutive_terms_of_linear_recurrent_sequence]
frequency: C
frequency_evidence: recent 0・前提として届くページなし・古い ABC 2 問
sections:
  - {title: 行列累乗との比較（いつ必要になるか）, anchor: vs-matrix}
  - {title: きたまさ法（x^N mod 特性多項式）, anchor: kitamasa}
  - {title: Bostan-Mori（Q(x)Q(−x) で次数を半分にする）, anchor: bostan-mori}
  - {title: Berlekamp-Massey（漸化式を見つける）, anchor: berlekamp-massey}
  - {title: ACL の convolution を使った実装, anchor: implementation}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：K 項の線形漸化式の第 N 項を、行列累乗より速くきたまさ法 O(K² log N) や Bostan-Mori O(K log K log N) で求める。最初の 2K 項から漸化式を見つける Berlekamp-Massey も使う。
    - **いつ使うか**：
        - 線形漸化式の項数 K が数百〜数千で、N ≤ 10^18
        - 有理式 P(x)/Q(x) の N 次の係数
        - 答えが線形漸化式を満たしそうだが式が分からない（最初の項から推定する）
        - a_n = Σ_{k=1}^{K} c_k a_{n−k} の形の漸化式
    - **計算量**：（執筆時に書く）
    - **前提**：[行列累乗](../math/matrix-power.md)、[形式的冪級数と多項式の演算](../math/fps-basics.md)
