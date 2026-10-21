---
id: lgv-lemma
title: LGV 補題
aliases: [Lindström-Gessel-Viennot の補題, 交わらない経路の組, LGV lemma]
type: overview
field: comb
chapter: 二項係数の系統
order: 160
level: 発展
kind: [数え上げ, 線形代数・行列]
prerequisites: [lattice-paths, determinant]
related: [matrix-tree-theorem, bit-dp]
summary: DAG 上で k 個の始点から k 個の終点への、互いに交わらない経路の組の数（符号付き）を、始点 i から終点 j への経路数を並べた行列の行列式で求める。交わる組は符号で打ち消し合う。
complexity: null
signs:
  - {type: phrase, text: K 本の経路が互いに交わらない組の個数}
  - {type: phrase, text: 複数の駒が衝突せずに動く確率}
acl: []
frequency: C
frequency_evidence: recent 0・前提として届くページなし・古い ABC 1 問
sections:
  - {title: 何ができるか（行列式で数える）, anchor: what}
  - {title: 符号付きで数える理由（交わる組が打ち消し合う）, anchor: why-signed}
  - {title: 格子路と組み合わせる, anchor: with-lattice-paths}
  - {title: 行列式を bitDP で展開する例, anchor: bitdp}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：DAG 上で k 個の始点から k 個の終点への、互いに交わらない経路の組の数（符号付き）を、始点 i から終点 j への経路数を並べた行列の行列式で求める。交わる組は符号で打ち消し合う。
    - **いつ使うか**：
        - K 本の経路が互いに交わらない組の個数
        - 複数の駒が衝突せずに動く確率
    - **計算量**：（執筆時に書く）
    - **前提**：[格子路の数え上げ](../comb/lattice-paths.md)、[行列式](../math/determinant.md)
