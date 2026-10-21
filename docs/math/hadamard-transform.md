---
id: hadamard-transform
title: XOR 畳み込み
aliases: [アダマール変換, Walsh-Hadamard, FWHT, XOR convolution, 添字の XOR の畳み込み]
type: overview
field: math
chapter: 畳み込みと多項式
order: 380
level: 発展
kind: [畳み込み・多項式, ビット演算]
prerequisites: [convolution-ntt, bit-operations]
related: [zeta-mobius-subset, zeta-mobius-divisor, nim, fft-ntt]
summary: c_k = Σ_{i XOR j = k} a_i b_j を、アダマール変換で各点の積に直して O(N log N) で求める。添字の演算（和・XOR・AND/OR・gcd/lcm）ごとに使う変換が変わる。
complexity: null
signs:
  - {type: phrase, text: i XOR j = k となる組を全ての k について数える}
  - {type: phrase, text: XOR が 0 でない Nim の盤面の数を数える}
  - {type: constraint, text: 値が 2^16〜2^20 程度で、添字の XOR で畳み込む}
acl: []
verify: [bitwise_xor_convolution]
frequency: C
frequency_evidence: recent 0・前提として届くページなし・古い ABC 1 問
sections:
  - {title: 'アダマール変換と逆変換（各 bit で (x + y, x − y)）', anchor: transform}
  - {title: 同じ配列を K 回 XOR 畳み込みする（変換後の累乗）, anchor: power}
  - {title: 添字の演算と変換の対応（和は FFT、AND/OR は高速ゼータ変換、gcd/lcm は約数のゼータ変換）, anchor: index-operations}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：c_k = Σ_{i XOR j = k} a_i b_j を、アダマール変換で各点の積に直して O(N log N) で求める。添字の演算（和・XOR・AND/OR・gcd/lcm）ごとに使う変換が変わる。
    - **いつ使うか**：
        - i XOR j = k となる組を全ての k について数える
        - XOR が 0 でない Nim の盤面の数を数える
        - 値が 2&#94;16〜2&#94;20 程度で、添字の XOR で畳み込む
    - **計算量**：（執筆時に書く）
    - **前提**：[畳み込みの使い方](../math/convolution-ntt.md)、[bit 演算の基本と XOR の性質](../basics/bit-operations.md)
