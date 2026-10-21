---
id: merge-sort-tree
title: マージソート木
aliases: [Merge Sort Tree, マージソートツリー, 領域木, Range Tree]
type: technique
field: ds
chapter: そのほかのデータ構造
order: 330
level: 青
kind: [データ構造, 区間クエリ]
prerequisites: [segment-tree, binary-search]
related: [wavelet-matrix, sweep-line-2d, persistent-data-structures, offline-queries]
summary: 区間内の x 以下の要素の個数・和を、オンラインで O(log^2 N) で答える静的な構造。セグメント木の各ノードにその区間をソートした列と累積和を持ち、メモリは O(N log N)。
complexity: null
signs:
  - {type: phrase, text: 区間内で X 以下の要素の個数・和を多数のクエリで答える}
  - {type: phrase, text: 前の答えで次のクエリが決まる（オンライン強制）}
acl: []
verify: [static_range_sum_with_upper_bound]
frequency: B
frequency_evidence: recent 1（abc467_g）・前提として 1 ページに届く（直接 1）・古い ABC 1 問
sections:
  - {title: 作り方（子の列をマージする）とメモリ O(N log N), anchor: build}
  - {title: クエリの手順（O(log N) 個のノードで二分探索）と累積和で和も, anchor: query}
  - {title: 各段に BIT を持たせる（先読みと組む）, anchor: bit-per-level, level: 発展}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：区間内の x 以下の要素の個数・和を、オンラインで O(log^2 N) で答える静的な構造。セグメント木の各ノードにその区間をソートした列と累積和を持ち、メモリは O(N log N)。
    - **いつ使うか**：
        - 区間内で X 以下の要素の個数・和を多数のクエリで答える
        - 前の答えで次のクエリが決まる（オンライン強制）
    - **計算量**：（執筆時に書く）
    - **前提**：[セグメント木](../ds/segment-tree.md)、[二分探索](../basics/binary-search.md)
