---
id: tree-distance
title: 木の上の距離
aliases: [木の距離, 根からの累積, XOR 距離, 追いかけっこ, 2 点からの距離, distance on a tree]
type: technique
field: tree
chapter: 木の基礎
order: 40
level: 基礎
kind: [木]
prerequisites: [tree-traversal]
related: [lca, tree-path, tree-diameter, xor]
summary: 木では 2 点間のパスが一意なので、重み付きでも DFS 1 回で 1 点からの距離が求まる。2 点からの距離を比べる型と、根からの累積値で 2 点間の値を表す型（XOR なら LCA がいらない）がある。
complexity: null
signs:
  - {type: phrase, text: 頂点 K を経由する最短距離}
  - {type: phrase, text: 2 人の追いかけっこ・どちらが先に着くか}
  - {type: phrase, text: パス上の辺の重みの XOR}
acl: []
frequency: B
frequency_evidence: recent 1（abc451_e）・前提として 3 ページに届く（直接 2）・古い ABC 3 問
sections:
  - {title: 1 点からの距離（ダイクストラはいらない）, anchor: from-one}
  - {title: 2 点からの距離を比べる, anchor: from-two}
  - {title: 根からの累積値で 2 点間を表す（XOR は LCA が不要、和は LCA が要る）, anchor: root-prefix}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：木では 2 点間のパスが一意なので、重み付きでも DFS 1 回で 1 点からの距離が求まる。2 点からの距離を比べる型と、根からの累積値で 2 点間の値を表す型（XOR なら LCA がいらない）がある。
    - **いつ使うか**：
        - 頂点 K を経由する最短距離
        - 2 人の追いかけっこ・どちらが先に着くか
        - パス上の辺の重みの XOR
    - **計算量**：（執筆時に書く）
    - **前提**：[根付き木と走査順](../tree/tree-traversal.md)
