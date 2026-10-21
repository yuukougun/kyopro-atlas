---
id: dynamic-tree
title: 動的木
aliases: [Link-Cut Tree, LCT, Euler Tour Tree, Top Tree, dynamic tree]
type: overview
field: tree
chapter: 部分木とパスのクエリ
order: 210
level: 発展
kind: [木, データ構造]
prerequisites: [hld, balanced-bst]
related: [small-to-large, static-top-tree]
summary: 辺の追加と削除がある森で、パスのクエリや根の付け替えを償却 O(log N) で処理する Link-Cut Tree と、部分木のクエリ向けの Euler Tour Tree、両方に使える Top Tree がある。
complexity: null
signs:
  - {type: phrase, text: 辺の追加と削除をくり返す森でのパスのクエリ}
  - {type: phrase, text: 根の付け替えがある}
acl: []
verify: [dynamic_tree_vertex_add_path_sum]
frequency: C
frequency_evidence: recent 0・前提として届くページなし・古い ABC 1 問
sections:
  - {title: Link-Cut Tree でできること, anchor: link-cut}
  - {title: Euler Tour Tree・Top Tree, anchor: ett-top-tree}
  - {title: 辺の追加だけならマージテク, anchor: add-only}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：辺の追加と削除がある森で、パスのクエリや根の付け替えを償却 O(log N) で処理する Link-Cut Tree と、部分木のクエリ向けの Euler Tour Tree、両方に使える Top Tree がある。
    - **いつ使うか**：
        - 辺の追加と削除をくり返す森でのパスのクエリ
        - 根の付け替えがある
    - **計算量**：（執筆時に書く）
    - **前提**：[HL 分解](../tree/hld.md)、[平衡二分探索木と pb_ds の tree](../ds/balanced-bst.md)
