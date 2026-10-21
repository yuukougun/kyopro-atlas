---
id: top-k-multiset
title: 上位 K 個の和と中央値の管理
aliases: [2 つの multiset, 2 つのヒープ, two heaps, 下位 K 個の和, 動的な中央値, running median, Priority Sum Structure]
type: technique
field: ds
chapter: 標準コンテナの応用
order: 40
level: 水
kind: [データ構造]
prerequisites: [ordered-set, priority-queue]
related: [segment-tree-on-values, kth-element, median-absolute, slope-trick, greedy-priority-queue]
summary: 追加・削除のたびに上位（下位）K 個の和や中央値を O(log N) で答える。小さい方の K 個と残りを 2 つの multiset（ヒープ）に分けて持ち、境界の 1 個を移して分け方を保つ。
complexity: null
signs:
  - {type: phrase, text: 1 点を更新するたびに、大きい方から K 個の和を答える}
  - {type: phrase, text: 幅 M の窓をずらしながら、小さい方から K 個の和を答える}
  - {type: phrase, text: 数を追加しながら中央値（|x − a_i| の和を最小にする x）を答える}
  - {type: constraint, text: Q ≤ 2×10^5 で、更新のたびに上位 K 個の和や中央値を答える}
acl: []
verify: []
frequency: B
frequency_evidence: recent 1（abc458_d）・前提として 1 ページに届く（直接 1）・古い ABC 3 問
sections:
  - {title: 2 つに分けて持つ（L＝小さい K 個、R＝残り。L の和を持つ）, anchor: two-sets}
  - {title: 保つ性質（L の個数が K・L の最大 ≤ R の最小）と、境界の 1 個を移して回復する手順, anchor: invariants}
  - {title: 削除・更新（どちらにあるかを見て消してから回復する）, anchor: erase-update}
  - {title: 中央値を保つ（個数の差を 1 以内に。削除がなければヒープ 2 本）と Σ|x − a_i| の更新, anchor: median}
  - {title: 値を添字にした BIT・セグメント木で書く方法（→ 値を添字にする BIT・セグメント木）, anchor: by-index}
  - {title: 落とし穴（同じ値の削除先・multiset の erase・和の更新漏れ）, anchor: pitfalls}
  - {title: '|x − a| + b を足していく関数の最小値（中央値の更新の応用。slope trick の入口）', anchor: absolute-sum-function, level: 黄}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：追加・削除のたびに上位（下位）K 個の和や中央値を O(log N) で答える。小さい方の K 個と残りを 2 つの multiset（ヒープ）に分けて持ち、境界の 1 個を移して分け方を保つ。
    - **いつ使うか**：
        - 1 点を更新するたびに、大きい方から K 個の和を答える
        - 幅 M の窓をずらしながら、小さい方から K 個の和を答える
        - 数を追加しながら中央値（|x − a_i| の和を最小にする x）を答える
        - Q ≤ 2×10^5 で、更新のたびに上位 K 個の和や中央値を答える
    - **計算量**：（執筆時に書く）
    - **前提**：[set・multiset・map の応用](../ds/ordered-set.md)、[優先度付きキュー](../ds/priority-queue.md)
