---
id: dp-grid
title: グリッド上の DP
aliases: [グリッド DP, Grid DP, 格子路の DP, 最大正方形]
type: technique
field: dp
chapter: 列の DP
order: 150
level: 水
kind: [DP]
prerequisites: [dp-basics]
related: [dp-dag, grid-graph, bfs, lattice-paths, inclusion-exclusion-dp#first-obstacle, dp-prefix-sum, grid#right-down]
summary: 右か下にしか動けないグリッドで、経路の数や経路上の値の最大を、マスの昇順の DP で求める。上下左右に動けるなら閉路ができるので、BFS やダイクストラ法を使う。
complexity: null
signs:
  - {type: phrase, text: 右か下にしか動けない}
  - {type: phrase, text: 経路の数・経路上で集める値の最大}
  - {type: phrase, text: 条件を満たす正方形の数・最大の正方形}
  - {type: constraint, text: 'H, W ≤ 3000 程度'}
acl: []
frequency: B
frequency_evidence: recent 1（abc476_f）・前提として届くページなし・古い ABC 11 問
sections:
  - {title: 計算順序と初期化（1 行目・1 列目・壁）, anchor: order-and-init}
  - {title: 状態を足す（今の行で拾った個数・作れる差の集合）, anchor: extra-state}
  - {title: 方向ごとの累積和で遷移をまとめる, anchor: directional-prefix}
  - {title: 最大の正方形（左・上・左上の min + 1）, anchor: largest-square}
  - {title: 向きを反転してもう一度, anchor: flip-direction}
  - {title: 経路上の上位 K 個（K 番目を固定して状態に）, anchor: top-k-on-path, level: 黄}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：右か下にしか動けないグリッドで、経路の数や経路上の値の最大を、マスの昇順の DP で求める。上下左右に動けるなら閉路ができるので、BFS やダイクストラ法を使う。
    - **いつ使うか**：
        - 右か下にしか動けない
        - 経路の数・経路上で集める値の最大
        - 条件を満たす正方形の数・最大の正方形
        - H, W ≤ 3000 程度
    - **計算量**：（執筆時に書く）
    - **前提**：[DP の基本](../dp/dp-basics.md)
