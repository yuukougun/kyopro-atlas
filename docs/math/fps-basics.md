---
id: fps-basics
title: 形式的冪級数と多項式の演算
aliases: [FPS, formal power series, 多項式の逆元, 多項式の割り算, Taylor shift, 多点評価, 冪級数の log・exp]
type: overview
field: math
chapter: 畳み込みと多項式
order: 400
level: 発展
kind: [畳み込み・多項式, 数え上げ]
prerequisites: [convolution-ntt, mod-inverse]
related: [generating-function-counting, knapsack-undo, online-convolution, lagrange-interpolation, cayley-pruefer, fft-ntt]
summary: 数列を冪級数とみて、逆元 1/f・log・exp・累乗を O(N log N) で計算し、多項式の割り算・Taylor shift・多点評価も行う。数え上げの式を多項式で立てた後の計算を受け持つ。
complexity: null
signs:
  - {type: phrase, text: (1 + x^v) を掛ける・割るように、集合への追加と削除を繰り返して個数の分布を求める}
  - {type: phrase, text: 次数の条件つきの木や個数の分布を、多項式の累乗の係数として数える}
  - {type: shape, text: 答えが多項式 f の 1/f・log f・exp f・f^K の係数で書ける}
acl: [convolution]
verify: [inv_of_formal_power_series, log_of_formal_power_series, exp_of_formal_power_series, pow_of_formal_power_series, sqrt_of_formal_power_series, division_of_polynomials, polynomial_taylor_shift, multipoint_evaluation, polynomial_interpolation]
frequency: B
frequency_evidence: recent 1（abc473_g）・前提として 1 ページに届く（直接 1）・古い ABC 4 問
sections:
  - {title: 演算の一覧と計算量（inv・log・exp・pow・sqrt）, anchor: operations}
  - {title: 多項式の割り算・Taylor shift・多点評価, anchor: polynomial-ops}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：数列を冪級数とみて、逆元 1/f・log・exp・累乗を O(N log N) で計算し、多項式の割り算・Taylor shift・多点評価も行う。数え上げの式を多項式で立てた後の計算を受け持つ。
    - **いつ使うか**：
        - (1 + x^v) を掛ける・割るように、集合への追加と削除を繰り返して個数の分布を求める
        - 次数の条件つきの木や個数の分布を、多項式の累乗の係数として数える
        - 答えが多項式 f の 1/f・log f・exp f・f^K の係数で書ける
    - **計算量**：（執筆時に書く）
    - **前提**：[畳み込みの使い方](../math/convolution-ntt.md)、[逆元と mod での割り算](../math/mod-inverse.md)
