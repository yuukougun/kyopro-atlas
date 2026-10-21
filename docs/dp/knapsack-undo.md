---
id: knapsack-undo
title: 戻す DP
aliases: [ナップサックの削除, 削除できるナップサック, 減らすナップサック]
type: technique
field: dp
chapter: 列の DP
order: 130
level: 青
kind: [DP, 数え上げ]
prerequisites: [subset-sum, knapsack-01]
related: [divide-and-conquer#range-knapsack, dp-dimension-reduction]
summary: 数え上げの部分和 DP の更新は逆向きに解けるので、要素を 1 つ取り除いた状態に戻せる。max や min の DP は戻せないので、前後からの DP のマージや分割統治を使う。
complexity: null
signs:
  - {type: phrase, text: 要素の追加と削除のクエリのたびに、和が K になる選び方の数を答える}
  - {type: phrase, text: 各 i について、i を使わないときの答え（〜を除いたとき）}
  - {type: constraint, text: クエリの数 Q と目標の和 K がともに 5000 程度（O(QK) が通る）}
acl: []
frequency: B
frequency_evidence: recent 0・前提として届くページなし・古い ABC 3 問
sections:
  - {title: 足し算の更新は引き算で戻せる（ループの向きは追加と逆）, anchor: undo-by-subtraction}
  - {title: 戻せない DP（max・min・OR）, anchor: not-undoable}
  - {title: 前後からの DP をマージする, anchor: prefix-and-suffix}
  - {title: 分割統治でオフラインに処理する, anchor: offline-divide-and-conquer, level: 黄}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：数え上げの部分和 DP の更新は逆向きに解けるので、要素を 1 つ取り除いた状態に戻せる。max や min の DP は戻せないので、前後からの DP のマージや分割統治を使う。
    - **いつ使うか**：
        - 要素の追加と削除のクエリのたびに、和が K になる選び方の数を答える
        - 各 i について、i を使わないときの答え（〜を除いたとき）
        - クエリの数 Q と目標の和 K がともに 5000 程度（O(QK) が通る）
    - **計算量**：（執筆時に書く）
    - **前提**：[部分和 DP](../dp/subset-sum.md)、[ナップサック DP](../dp/knapsack-01.md)
