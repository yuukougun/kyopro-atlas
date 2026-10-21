---
id: counting-bijection
title: 対応づけ・数える対象の言い換え
aliases: [全単射, 1 対 1 対応, 経路数に帰着, bijection, bijective proof]
type: technique
field: comb
chapter: 数え方の考え方
order: 80
level: 青
kind: [数え上げ, 考察]
prerequisites: [counting-mindset, stars-and-bars, lattice-paths]
related: [reflection-principle, cayley-pruefer, counting-dedup, reformulation, prime-exponent-vector, bracket-sequence]
summary: 数えにくい対象を、個数が同じで数えやすい対象に 1 対 1 で対応させて数える。逆向きの写像が作れることが正しさの確かめになり、単射でない対応では同じものを重複して数えてしまう。
complexity: null
signs:
  - {type: phrase, text: 単調な数列の個数}
  - {type: phrase, text: 積（和）が決まった値になる数列の個数}
  - {type: phrase, text: 途中で負にならない ±1 の列の個数}
  - {type: shape, text: 二項係数の積の和を、1 つの二項係数（経路の数）に直したい}
acl: []
frequency: C
frequency_evidence: recent 0・前提として届くページなし・古い ABC 2 問
sections:
  - {title: 全単射なら個数が等しい（逆に戻せるかで検算する）, anchor: bijection}
  - {title: 素因数ごと・軸ごとに分けて独立な成分の積にする, anchor: decompose}
  - {title: 格子路に帰着できないかを疑う, anchor: to-lattice-paths}
  - {title: 括弧列と格子路、ラベル付き木と Prüfer 列, anchor: classic-bijections}
  - {title: 単射でない対応は重複する, anchor: non-injective}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：数えにくい対象を、個数が同じで数えやすい対象に 1 対 1 で対応させて数える。逆向きの写像が作れることが正しさの確かめになり、単射でない対応では同じものを重複して数えてしまう。
    - **いつ使うか**：
        - 単調な数列の個数
        - 積（和）が決まった値になる数列の個数
        - 途中で負にならない ±1 の列の個数
        - 二項係数の積の和を、1 つの二項係数（経路の数）に直したい
    - **計算量**：（執筆時に書く）
    - **前提**：[数え上げの考え方](../comb/counting-mindset.md)、[重複組合せ](../comb/stars-and-bars.md)、[格子路の数え上げ](../comb/lattice-paths.md)
