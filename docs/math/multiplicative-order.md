---
id: multiplicative-order
title: 位数・原始根・離散対数
aliases: [multiplicative order, primitive root, discrete logarithm, 累乗の周期, 生成元, BSGS, baby-step giant-step, 平方剰余, mod の平方根, mod の K 乗根, Tonelli-Shanks, Cipolla]
type: technique
field: math
chapter: GCD と合同式
order: 240
level: 黄
kind: [整数論]
prerequisites: [euler-phi, mod-inverse]
related: [exponent-mod, cycle-detection, meet-in-the-middle, convolution-ntt, fft-ntt]
summary: a^k ≡ 1 となる最小の k（位数）を φ(m) の約数から求め、原始根で掛け算を指数の足し算に直す。a^x ≡ b を満たす x（離散対数）は Baby-step Giant-step で O(√m) で求める。
complexity: null
signs:
  - {type: phrase, text: 同じ数字を n 個並べた数が K の倍数になる最小の n}
  - {type: phrase, text: a^x ≡ b (mod P) となる最小の x}
  - {type: phrase, text: X ← AX + B (mod P) を繰り返して G が最初に現れる番号}
  - {type: phrase, text: x^n ≡ y (mod P) となる組を数える}
  - {type: phrase, text: mod P での積の値ごとに個数を数える}
  - {type: constraint, text: 法 P が 10^9 程度で、√P ≈ 3×10^4 個の表なら持てる}
acl: []
verify: [discrete_logarithm_mod, primitive_root, sqrt_mod, kth_root_mod]
frequency: B
frequency_evidence: recent 0・前提として届くページなし・古い ABC 4 問
sections:
  - {title: 位数は φ(m) の約数になる理由と、累乗の列の周期, anchor: order}
  - {title: 位数の求め方（φ(m) の約数を試す・素因数を1つずつ取り除く）, anchor: find-order}
  - {title: '原始根の定義・存在条件（1, 2, 4, p^k, 2p^k）と見つけ方', anchor: primitive-root}
  - {title: 位数が d の元は φ(d) 個, anchor: count-by-order}
  - {title: 掛け算を指数の足し算に直す（積の個数を畳み込みへ）, anchor: mul-to-add}
  - {title: 離散対数：Baby-step Giant-step（表の大きさを √m にする理由）, anchor: bsgs}
  - {title: 'gcd(a, m) ≠ 1 の場合と、最小の解の取り方', anchor: bsgs-details}
  - {title: 一次漸化式を不動点で等比数列に直して離散対数に帰着する, anchor: affine-recurrence}
  - {title: 平方剰余と mod の K 乗根（オイラーの規準・Tonelli-Shanks・Cipolla）, anchor: mod-root, level: 発展}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：a^k ≡ 1 となる最小の k（位数）を φ(m) の約数から求め、原始根で掛け算を指数の足し算に直す。a^x ≡ b を満たす x（離散対数）は Baby-step Giant-step で O(√m) で求める。
    - **いつ使うか**：
        - 同じ数字を n 個並べた数が K の倍数になる最小の n
        - a^x ≡ b (mod P) となる最小の x
        - X ← AX + B (mod P) を繰り返して G が最初に現れる番号
        - x^n ≡ y (mod P) となる組を数える
        - mod P での積の値ごとに個数を数える
        - 法 P が 10^9 程度で、√P ≈ 3×10^4 個の表なら持てる
    - **計算量**：（執筆時に書く）
    - **前提**：[オイラーの φ 関数](../math/euler-phi.md)、[逆元と mod での割り算](../math/mod-inverse.md)
