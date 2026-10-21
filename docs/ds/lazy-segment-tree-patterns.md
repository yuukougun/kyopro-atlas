---
id: lazy-segment-tree-patterns
title: 遅延セグメント木の載せ方の型
aliases: [遅延セグ木のチートシート, S と F の設計, 区間加算区間最小, 区間代入区間和, Range Affine Range Sum, 区間反転]
type: technique
field: ds
chapter: 区間クエリ
order: 230
level: 青
kind: [データ構造, 区間クエリ, 考察]
prerequisites: [lazy-segment-tree, segment-tree-monoids]
related: [sweep-line-2d, inversion-number, bracket-sequence, difference-sequence, contribution, segment-tree-beats, inline-dp]
summary: 区間作用の問題で、遅延セグメント木に載せる S（値）と F（作用）・mapping・composition の組を型の表から選ぶ。0/1 列や X_i − i への言い換えで、そのままでは載らない問題を載る形に直す。
complexity: null
signs:
  - {type: phrase, text: 区間をソートする操作を繰り返す}
  - {type: phrase, text: 2 つの数列への区間加算と、区間の Σ A_i B_i}
  - {type: phrase, text: 0/1 列の区間反転と、区間で 1 が連続する最大の長さ}
  - {type: phrase, text: 一列に並ぶ人を順に動かす総移動量}
acl: [lazy_segtree]
verify: [range_set_range_composite]
frequency: B
frequency_evidence: recent 1（abc455_f）・前提として届くページなし・古い ABC 6 問
sections:
  - {title: 設計の手順と載せられる条件（S はモノイド・F は恒等写像を含み合成で閉じる・f(x·y) = f(x)·f(y)）, anchor: design-steps}
  - {title: 型の表（S・op・e・F・mapping・composition・id）, anchor: pattern-table}
  - {title: 区間代入の「なし」の番兵と composition の向き, anchor: assign-sentinel}
  - {title: 0/1 反転・転倒数・最長の連続（0 と 1 の情報を入れ替える）, anchor: flip}
  - {title: 等差数列の加算・2 列の積の和（添字の和や Σa・Σb を S に足す）, anchor: arithmetic-add}
  - {title: 載らない作用（区間 chmin と区間和・区間の割り算・区間の並べ替え）と逃げ道, anchor: not-applicable}
  - {title: 言い換えてから載せる（しきい値で 0/1 にする・X_i − i・寄与）, anchor: reformulate, level: 黄}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：区間作用の問題で、遅延セグメント木に載せる S（値）と F（作用）・mapping・composition の組を型の表から選ぶ。0/1 列や X_i − i への言い換えで、そのままでは載らない問題を載る形に直す。
    - **いつ使うか**：
        - 区間をソートする操作を繰り返す
        - 2 つの数列への区間加算と、区間の Σ A_i B_i
        - 0/1 列の区間反転と、区間で 1 が連続する最大の長さ
        - 一列に並ぶ人を順に動かす総移動量
    - **計算量**：（執筆時に書く）
    - **前提**：[遅延セグメント木](../ds/lazy-segment-tree.md)、[セグメント木に何を載せるか](../ds/segment-tree-monoids.md)
