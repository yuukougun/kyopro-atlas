---
id: determinant
title: 行列式
aliases: [determinant, 行列式 mod p]
type: overview
field: math
chapter: 行列と線形代数
order: 350
level: 発展
kind: [線形代数・行列]
prerequisites: [gaussian-elimination]
related: [matrix-tree-theorem, spanning-tree-advanced, lgv-lemma]
summary: 掃き出し法で上三角にし、対角成分の積に行の交換の回数だけ符号を掛けて行列式を O(n³) で求める。全域木の数を数える行列木定理の部品になる。
complexity: null
signs:
  - {type: phrase, text: 行列式を mod p で求める}
  - {type: phrase, text: 全域木の個数・交わらない経路の組の数}
acl: []
verify: [matrix_det, matrix_det_mod_2, matrix_det_arbitrary_mod]
frequency: C
frequency_evidence: recent 0・前提として 2 ページに届く（直接 2）・古い ABC 0 問
sections:
  - {title: 掃き出しで行列式を求める（行の交換で符号が変わる）, anchor: by-elimination}
  - {title: mod p での計算と、法が素数でない場合（互除法による掃き出し）, anchor: modulus}
  - {title: 行列木定理・LGV 補題への入口, anchor: applications}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：掃き出し法で上三角にし、対角成分の積に行の交換の回数だけ符号を掛けて行列式を O(n³) で求める。全域木の数を数える行列木定理の部品になる。
    - **いつ使うか**：
        - 行列式を mod p で求める
        - 全域木の個数・交わらない経路の組の数
    - **計算量**：（執筆時に書く）
    - **前提**：[掃き出し法](../math/gaussian-elimination.md)
