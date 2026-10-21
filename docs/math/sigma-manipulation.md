---
id: sigma-manipulation
title: Σ の変形
aliases: [シグマの変形, 和の順序交換, 総和の変形, 二重和, 添字の付け替え, order of summation]
type: technique
field: math
chapter: 式と整数の基本
order: 10
level: 基礎
kind: [考察, 数え上げ]
prerequisites: []
related: [notation, contribution, linearity-of-expectation, harmonic-sum, floor-quotient-enum]
summary: 二重和の順序交換・添字の範囲の書き換え・付け替え・線形性で、Σ の式を計算しやすい形に変える。同じ和を別の順で計算して計算量を下げる式変形の土台になる。
complexity: null
signs:
  - {type: phrase, text: '全ての組 (i, j)（i < j）について〜を足した和を求める'}
  - {type: shape, text: 'Σ_{i=1}^{N} Σ_{j=i}^{N} f(i, j) のように、内側の和の範囲が外側の添字で決まる二重和'}
  - {type: shape, text: 'Σ_{K=1}^{N} K × (K の約数の個数) のように、約数・倍数の関係で書き換えられる和'}
acl: []
verify: []
frequency: A
frequency_evidence: recent 2（abc455_f・abc471_e）・前提として 7 ページに届く（直接 3）・古い ABC 3 問
sections:
  - {title: Σ の線形性と分解（定数を外に出す・和を分ける）, anchor: linearity}
  - {title: 二重和の順序交換と添字の範囲（i ≤ j ≤ N を j の側から見る）, anchor: swap-order}
  - {title: 添字の付け替え（i → N − i、k = i + j、約数 d と倍数）, anchor: reindex}
  - {title: 値でまとめ直す（同じ値になる添字の個数を掛ける）, anchor: group-by-value}
  - {title: 'よく使う和の公式と Σ_{i≠j} a_i a_j = (Σa)² − Σa²', anchor: formulas}
  - {title: 空の和は 0・空の積は 1 と境界, anchor: empty-sum}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：二重和の順序交換・添字の範囲の書き換え・付け替え・線形性で、Σ の式を計算しやすい形に変える。同じ和を別の順で計算して計算量を下げる式変形の土台になる。
    - **いつ使うか**：
        - 全ての組 (i, j)（i < j）について〜を足した和を求める
        - Σ_{i=1}^{N} Σ_{j=i}^{N} f(i, j) のように、内側の和の範囲が外側の添字で決まる二重和
        - Σ_{K=1}^{N} K × (K の約数の個数) のように、約数・倍数の関係で書き換えられる和
    - **計算量**：（執筆時に書く）
    - **前提**：なし
