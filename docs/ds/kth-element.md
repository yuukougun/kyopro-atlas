---
id: kth-element
title: K 番目の値を求めるデータ構造
aliases: [BIT 上の二分探索, Fenwick tree binary search, order statistics, 順序統計量, 空きの K 番目]
type: technique
field: ds
chapter: 区間クエリ
order: 170
level: 水
kind: [データ構造, 二分探索]
prerequisites: [fenwick-tree, ordered-set]
related: [segment-tree-binary-search, top-k-multiset, segment-tree-on-values, balanced-bst, binary-trie, kth-value, wavelet-matrix, sqrt-decomposition, linked-list]
summary: 値の追加・削除がある多重集合で、K 番目に小さい値や x 以下の個数を O(log N) で求める。値を添字にした個数の BIT の上で、2 べきの歩幅を大きい順に試して境界を探す。
complexity: null
signs:
  - {type: phrase, text: 数の追加・削除と、K 番目に小さい値の質問}
  - {type: phrase, text: 空いている場所のうち K 番目に置く・指定した位置への挿入を繰り返した最終的な列}
  - {type: phrase, text: x 以下の要素の個数（順位）}
acl: [fenwick_tree]
verify: [ordered_set]
frequency: B
frequency_evidence: recent 0・前提として届くページなし・古い ABC 3 問
sections:
  - {title: 方法の比較（multiset で K 歩・BIT 上の二分探索・セグメント木の max_right・外側の二分探索・pb_ds・2 つのヒープ・Binary Trie・平方分割）, anchor: comparison}
  - {title: BIT 上の二分探索の手順（2 べきの歩幅を大きい順に試す。値が非負であることが前提）, anchor: bit-binary-search}
  - {title: 挿入を逆順に処理して「空きの P 番目」に置く, anchor: reverse-insertion}
  - {title: 答えの二分探索で K 番目を数える方法（→ 基本テクニックの K 番目の値）との違い, anchor: vs-kth-value}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：値の追加・削除がある多重集合で、K 番目に小さい値や x 以下の個数を O(log N) で求める。値を添字にした個数の BIT の上で、2 べきの歩幅を大きい順に試して境界を探す。
    - **いつ使うか**：
        - 数の追加・削除と、K 番目に小さい値の質問
        - 空いている場所のうち K 番目に置く・指定した位置への挿入を繰り返した最終的な列
        - x 以下の要素の個数（順位）
    - **計算量**：（執筆時に書く）
    - **前提**：[BIT（Fenwick Tree）](../ds/fenwick-tree.md)、[set・multiset・map の応用](../ds/ordered-set.md)
