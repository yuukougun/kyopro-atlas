---
id: coordinate-compression
title: 座標圧縮
aliases: [座圧, 値の圧縮, 離散化, coordinate compression]
type: technique
field: basics
chapter: ソートと二分探索
order: 100
level: 基礎
kind: [ソート・座標圧縮]
prerequisites: [binary-search]
related: [stl-containers, fenwick-tree, event-sort, imos]
summary: 値を sort・unique・lower_bound で 0〜K−1 の番号に置き換え、大小関係だけを残したまま配列の添字にできるようにする。BIT・セグ木・いもす法と組んで使う。
complexity: null
signs:
  - {type: constraint, text: 値は 10^9 まであるが、個数は 2×10^5 以下}
  - {type: phrase, text: 大小関係（順位）だけが重要}
  - {type: shape, text: 値を配列の添字にしたいが、値の範囲が広すぎる}
acl: []
frequency: B
frequency_evidence: recent 1（abc467_f）・前提として 4 ページに届く（直接 2）・古い ABC 4 問
sections:
  - {title: sort → unique → lower_bound の 3 段, anchor: three-steps}
  - {title: 区間を扱うときは両端点を入れる, anchor: intervals}
  - {title: 圧縮後の番号で長さを測らない（元の値を残す）, anchor: keep-original}
  - {title: map で足りる場合との使い分け, anchor: vs-map}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：値を sort・unique・lower_bound で 0〜K−1 の番号に置き換え、大小関係だけを残したまま配列の添字にできるようにする。BIT・セグ木・いもす法と組んで使う。
    - **いつ使うか**：
        - 値は 10^9 まであるが、個数は 2×10^5 以下
        - 大小関係（順位）だけが重要
        - 値を配列の添字にしたいが、値の範囲が広すぎる
    - **計算量**：（執筆時に書く）
    - **前提**：[二分探索](../basics/binary-search.md)
