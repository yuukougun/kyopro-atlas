---
id: static-top-tree
title: Static Top Tree と木 DP の動的更新
aliases: [Static Top Tree, 動的木 DP, 重軽再帰 DP, dynamic tree DP]
type: overview
field: tree
chapter: 部分木とパスのクエリ
order: 200
level: 発展
kind: [木, DP, データ構造]
prerequisites: [hld, tree-dp]
related: [dynamic-dp, dynamic-tree, tree-isomorphism]
summary: 頂点の値を書き換えるたびに、木 DP の根の値を O(log N) 程度で更新する。HL 分解の重いパスの上で DP をセグメント木に載せる方法と、木をパスの圧縮と部分木の併合で平衡に組み直す Static Top Tree がある。
complexity: null
signs:
  - {type: phrase, text: 頂点の値を更新するたびに、木全体についての最適値・数え上げの結果を答える}
acl: []
verify: [point_set_tree_path_composite_sum]
frequency: C
frequency_evidence: recent 0・前提として届くページなし・古い ABC 2 問
sections:
  - {title: 重いパスの上で DP をセグ木に載せる, anchor: heavy-path-dp}
  - {title: Static Top Tree（圧縮と併合）, anchor: compress-rake}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：頂点の値を書き換えるたびに、木 DP の根の値を O(log N) 程度で更新する。HL 分解の重いパスの上で DP をセグメント木に載せる方法と、木をパスの圧縮と部分木の併合で平衡に組み直す Static Top Tree がある。
    - **いつ使うか**：頂点の値を更新するたびに、木全体についての最適値・数え上げの結果を答える
    - **計算量**：（執筆時に書く）
    - **前提**：[HL 分解](../tree/hld.md)、[木 DP](../dp/tree-dp.md)
