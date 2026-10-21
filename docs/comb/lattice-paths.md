---
id: lattice-paths
title: 格子路の数え上げ
aliases: [格子路, グリッドの最短経路の数, 障害物のある経路, lattice path]
type: technique
field: comb
chapter: 数え上げの基礎
order: 50
level: 基礎
kind: [数え上げ]
prerequisites: [binomial-precompute]
related: [counting-bijection, binomial-identities, reflection-principle, inclusion-exclusion-dp, dp-grid, lgv-lemma, manhattan-chebyshev]
summary: (0,0) から (a,b) への右・上の最短経路は C(a+b, a) 通りで、R と U の列に 1 対 1 に対応する。移動の種類が違えば回数の組に直し、禁止領域は境界を越える点で分けて数える。
complexity: null
signs:
  - {type: phrase, text: グリッドの左上から右下への最短経路の数}
  - {type: constraint, text: 'H, W ≤ 10^5 のグリッドで、左上から右下への経路の数を求める'}
  - {type: phrase, text: 通れない長方形の領域がある経路の数}
  - {type: phrase, text: 2 種類の移動を組み合わせて目的地へ行く方法の数}
acl: []
frequency: A
frequency_evidence: recent 0・前提として 6 ページに届く（直接 5）・古い ABC 4 問
sections:
  - {title: '基本：C(a+b, a) と R・U の列', anchor: basic}
  - {title: 移動の種類を回数の組に直す, anchor: move-counts}
  - {title: 禁止領域を避ける：境界を越える点で分類する, anchor: forbidden-region, level: 青}
  - {title: 経路数の総和と、二項係数の和を経路数として一括で求める, anchor: sum-of-paths, level: 青}
  - {title: 移動を軸ごとの回数に分けて独立にする（45 度回転）, anchor: independent-axes, level: 青}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：(0,0) から (a,b) への右・上の最短経路は C(a+b, a) 通りで、R と U の列に 1 対 1 に対応する。移動の種類が違えば回数の組に直し、禁止領域は境界を越える点で分けて数える。
    - **いつ使うか**：
        - グリッドの左上から右下への最短経路の数
        - H, W ≤ 10^5 のグリッドで、左上から右下への経路の数を求める
        - 通れない長方形の領域がある経路の数
        - 2 種類の移動を組み合わせて目的地へ行く方法の数
    - **計算量**：（執筆時に書く）
    - **前提**：[二項係数の前計算](../comb/binomial-precompute.md)
