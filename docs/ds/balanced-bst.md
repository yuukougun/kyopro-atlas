---
id: balanced-bst
title: 平衡二分探索木と pb_ds の tree
aliases: [平衡二分木, balanced binary search tree, treap, implicit treap, RBST, splay, pb_ds tree, order statistics tree]
type: overview
field: ds
chapter: そのほかのデータ構造
order: 360
level: 発展
kind: [データ構造]
prerequisites: [ordered-set]
related: [kth-element, linked-list, segment-tree, advanced-ds-catalog]
summary: 位置で指定した挿入・削除・区間の反転・区間の総積を、期待 O(log N) で処理する列の構造。treap などで split・merge を基本操作にし、K 番目と順位だけなら GCC の pb_ds の tree で足りる。
complexity: null
signs:
  - {type: phrase, text: 列の途中（位置で指定）への挿入・削除と、区間の反転}
  - {type: phrase, text: K 番目の値と、値の順位の両方をオンラインで答える}
acl: []
verify: [range_reverse_range_sum, dynamic_sequence_range_affine_range_sum]
frequency: C
frequency_evidence: recent 0・前提として 1 ページに届く（直接 1）・古い ABC 1 問
sections:
  - {title: 何ができるか（位置で分割・結合する列の構造）, anchor: what-it-does}
  - {title: treap の split・merge と、深さが期待 O(log N) になる理由, anchor: treap}
  - {title: 'pb_ds の tree（order_of_key・find_by_order。重複は (値, 通し番号) にする）（→ C++ 章）', anchor: pbds}
  - {title: 代わりの手（BIT 上の二分探索・連結リスト・逆順の処理と BIT）, anchor: alternatives}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：位置で指定した挿入・削除・区間の反転・区間の総積を、期待 O(log N) で処理する列の構造。treap などで split・merge を基本操作にし、K 番目と順位だけなら GCC の pb_ds の tree で足りる。
    - **いつ使うか**：
        - 列の途中（位置で指定）への挿入・削除と、区間の反転
        - K 番目の値と、値の順位の両方をオンラインで答える
    - **計算量**：（執筆時に書く）
    - **前提**：[set・multiset・map の応用](../ds/ordered-set.md)
