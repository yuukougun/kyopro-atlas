---
id: tree-centroid
title: 木の重心
aliases: [重心, centroid, 重み付き重心, tree centroid]
type: technique
field: tree
chapter: 木全体の形
order: 110
level: 黄
kind: [木]
prerequisites: [tree-traversal]
related: [centroid-decomposition, tree-diameter, tree-dp#reroot-difference, rerooting]
summary: 重心は取り除いたときに残る成分の大きさがすべて N/2 以下になる頂点で、1 個か隣接する 2 個ある。部分木サイズから O(N) で求まり、全ペアが重心を通るペアの作り方や重心分解に使う。
complexity: null
signs:
  - {type: phrase, text: ペアを作ってパスの長さの和を最大化する}
  - {type: phrase, text: どの成分も半分以下になるように分ける}
acl: []
frequency: B
frequency_evidence: recent 1（abc453_f）・前提として 1 ページに届く（直接 1）・古い ABC 2 問
sections:
  - {title: 定義と求め方（子の部分木と親側の N − sz）, anchor: definition}
  - {title: 重心は 1 個か隣接する 2 個, anchor: one-or-two}
  - {title: 重心で分けて別の枝どうしを組む, anchor: pair-across}
  - {title: 中心との違い, anchor: vs-center}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：重心は取り除いたときに残る成分の大きさがすべて N/2 以下になる頂点で、1 個か隣接する 2 個ある。部分木サイズから O(N) で求まり、全ペアが重心を通るペアの作り方や重心分解に使う。
    - **いつ使うか**：
        - ペアを作ってパスの長さの和を最大化する
        - どの成分も半分以下になるように分ける
    - **計算量**：（執筆時に書く）
    - **前提**：[根付き木と走査順](../tree/tree-traversal.md)
