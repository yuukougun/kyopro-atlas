---
id: fft-ntt
title: FFT・NTT の仕組みと任意 mod の畳み込み
aliases: [FFT, NTT, 高速フーリエ変換, fast Fourier transform, 数論変換, number theoretic transform, 任意 mod 畳み込み, 3 素数 NTT]
type: overview
field: math
chapter: 畳み込みと多項式
order: 370
level: 発展
kind: [畳み込み・多項式]
prerequisites: [convolution-ntt]
related: [multiplicative-order, crt, fps-basics, online-convolution]
summary: 畳み込みを自作するときや任意 mod で求めるときに、多項式を 1 の N 乗根での値に変えて各点の積にし、分割統治で O(N log N) で変換する。任意 mod は 3 つの素数で計算して CRT で戻す。
complexity: null
signs:
  - {type: phrase, text: mod 10^9+7 や整数のままで畳み込みたい}
  - {type: phrase, text: 畳み込みを自作ライブラリで実装したい・浮動小数の FFT の誤差が心配}
acl: [convolution, convolution_ll]
verify: [convolution_mod, convolution_mod_1000000007, convolution_mod_2_64]
frequency: C
frequency_evidence: recent 0・前提として届くページなし・古い ABC 0 問
sections:
  - {title: 点での値に直すと掛け算が O(N)（多項式の値表現）, anchor: point-value}
  - {title: 1 の N 乗根と分割統治（バタフライ）, anchor: butterfly}
  - {title: 複素数の FFT と誤差、NTT に向く素数（c·2^k + 1）と原始根, anchor: ntt-prime}
  - {title: 任意 mod の畳み込み（3 素数 NTT と Garner、convolution_ll）, anchor: arbitrary-mod}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：畳み込みを自作するときや任意 mod で求めるときに、多項式を 1 の N 乗根での値に変えて各点の積にし、分割統治で O(N log N) で変換する。任意 mod は 3 つの素数で計算して CRT で戻す。
    - **いつ使うか**：
        - mod 10^9+7 や整数のままで畳み込みたい
        - 畳み込みを自作ライブラリで実装したい・浮動小数の FFT の誤差が心配
    - **計算量**：（執筆時に書く）
    - **前提**：[畳み込みの使い方](../math/convolution-ntt.md)
