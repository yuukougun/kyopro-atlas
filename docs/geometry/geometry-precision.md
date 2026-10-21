---
id: geometry-precision
title: 誤差の扱いと整数での処理
aliases: [浮動小数点の誤差, floating-point error, EPS, 整数化, 桁落ち, 直線の正規化, 方向ベクトルの約分, ax+by+c=0]
type: technique
field: geometry
order: 20
level: 水
kind: [幾何, 整数論]
prerequisites: [geometry-vectors, gcd-lcm]
related: [cpp-types-literals#floating-point, integer-root#compare-sqrt, binary-search-answer, circle-geometry, argument-sort]
summary: 幾何の計算をできるだけ整数で行い、誤差による判定の誤りを防ぐ。小数の入力は 10^k 倍し、比較は外積・内積・距離の 2 乗で、傾きや直線は gcd で約分して符号をそろえた組で表し、実数は避けられないときだけ使う。
complexity: null
signs:
  - {type: phrase, text: 座標や値が小数第 k 位まで与えられる}
  - {type: phrase, text: ちょうど境界上か・整数になるかを判定する}
  - {type: phrase, text: K 点以上を通る直線の数・平行な辺の組（台形）の数}
  - {type: phrase, text: 絶対誤差または相対誤差 10^-6〜10^-9 まで許される}
  - {type: constraint, text: 座標が 10^9 規模の整数で、傾きや角度を比べる}
acl: []
verify: []
frequency: B
frequency_evidence: recent 1（abc467_d）・前提として 1 ページに届く（直接 1）・古い ABC 7 問
sections:
  - {title: double の精度の目安（仮数 53 ビット・値 10^9 で絶対誤差 10^-7 程度）と桁落ち, anchor: double-precision}
  - {title: 小数の入力を 10^k 倍して整数にする（文字列で読んで整数にする）, anchor: scale-to-integer}
  - {title: 比較は外積・内積・距離の 2 乗で（sqrt・atan2・除算を避ける）, anchor: integer-comparison}
  - {title: '方向・直線の正規化：gcd で約分し、(1, −1) と (−1, 1) を同じにする符号の決め方', anchor: line-normalization}
  - {title: 中点を整数にするために座標を 2 倍する, anchor: double-coordinates}
  - {title: 実数が避けられないとき：long double と、値の大きさに合わせた EPS, anchor: eps}
  - {title: 出力の桁数と、実数の二分探索の打ち切り, anchor: output-and-binary-search}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：幾何の計算をできるだけ整数で行い、誤差による判定の誤りを防ぐ。小数の入力は 10^k 倍し、比較は外積・内積・距離の 2 乗で、傾きや直線は gcd で約分して符号をそろえた組で表し、実数は避けられないときだけ使う。
    - **いつ使うか**：
        - 座標や値が小数第 k 位まで与えられる
        - ちょうど境界上か・整数になるかを判定する
        - K 点以上を通る直線の数・平行な辺の組（台形）の数
        - 絶対誤差または相対誤差 10&#94;-6〜10&#94;-9 まで許される
        - 座標が 10^9 規模の整数で、傾きや角度を比べる
    - **計算量**：（執筆時に書く）
    - **前提**：[ベクトルと外積](../geometry/geometry-vectors.md)、[GCD・LCM とユークリッドの互除法](../math/gcd-lcm.md)
