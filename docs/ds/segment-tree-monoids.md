---
id: segment-tree-monoids
title: セグメント木に何を載せるか
aliases: [モノイドの設計, monoid design, 抽象化セグ木, second best, 行列を載せるセグ木]
type: technique
field: ds
chapter: 区間クエリ
order: 220
level: 青
kind: [データ構造, 区間クエリ]
prerequisites: [segment-tree]
related: [lazy-segment-tree, lazy-segment-tree-patterns, rolling-hash#hash-segment-tree, bracket-sequence, matrix-power, dynamic-dp]
summary: 左右の子の情報だけから親の情報を作れるように、答えに要る情報を足してセグメント木に載せる。最小値とその個数、最大値と 2 番目、括弧列の (和, 最小接頭和)、ハッシュ、一次関数の合成、行列などの型がある。
complexity: null
signs:
  - {type: phrase, text: 1 点の更新と、区間が正しい括弧列か・回文かの判定}
  - {type: phrase, text: 区間で 2 番目に大きい値（の個数）}
  - {type: phrase, text: 区間の最大部分配列和・区間で最長の連続する 1}
  - {type: shape, text: '区間 [l, r) の答えが、各位置の一次関数や小さな行列を順に合成したもので書ける'}
acl: [segtree]
verify: []
frequency: A
frequency_evidence: recent 2（abc456_f・abc460_f）・前提として 2 ページに届く（直接 2）・古い ABC 5 問
sections:
  - {title: 設計の手順（答えに要る情報 → 親が作れるまで情報を足す → 結合律と単位元を確かめる）, anchor: design-steps}
  - {title: 型の表（和・min/max・gcd・最小値と個数・括弧列・最大部分配列和など）, anchor: pattern-table}
  - {title: 非可換なモノイド（一次関数の合成・ハッシュの連結。積む順序）, anchor: non-commutative}
  - {title: '行列を載せる（(min,+)・(max,+) の半環も。行列の積は行列累乗のページ、1 点更新のたびに DP を求め直すなら動的 DP）', anchor: matrix}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：左右の子の情報だけから親の情報を作れるように、答えに要る情報を足してセグメント木に載せる。最小値とその個数、最大値と 2 番目、括弧列の (和, 最小接頭和)、ハッシュ、一次関数の合成、行列などの型がある。
    - **いつ使うか**：
        - 1 点の更新と、区間が正しい括弧列か・回文かの判定
        - 区間で 2 番目に大きい値（の個数）
        - 区間の最大部分配列和・区間で最長の連続する 1
        - 区間 [l, r) の答えが、各位置の一次関数や小さな行列を順に合成したもので書ける
    - **計算量**：（執筆時に書く）
    - **前提**：[セグメント木](../ds/segment-tree.md)
