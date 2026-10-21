---
id: linked-list
title: 配列で作る連結リスト
aliases: [連結リスト, 双方向リスト, linked list, doubly linked list, prev・next の配列]
type: technique
field: ds
chapter: 標準コンテナの応用
order: 70
level: 基礎
kind: [データ構造]
prerequisites: [stl-containers]
related: [balanced-bst, ordered-set, kth-element]
summary: 各要素の前と次を配列（値が大きければ map）で持つ双方向リストで、「x の直後に y を挿入」「x を削除」「列の付け替え」を O(1) で行い、最後に先頭からたどって列を出力する。
complexity: null
signs:
  - {type: phrase, text: 値 x の直後に y を挿入・値 x を削除する操作を繰り返し、最後の列を出力する}
  - {type: phrase, text: カードの山を別のカードの上へ付け替える}
  - {type: phrase, text: 列車の連結・切り離し}
acl: []
verify: []
frequency: B
frequency_evidence: recent 1（abc455_d）・前提として届くページなし・古い ABC 3 問
sections:
  - {title: prev・next の配列と番兵（先頭・末尾）, anchor: arrays}
  - {title: 挿入・削除・付け替えの手順, anchor: operations}
  - {title: 最後に先頭からたどって出力する, anchor: output}
  - {title: 使い分け（位置で指定するなら連結リストでは速くならない → 逆順の処理と BIT・平衡二分探索木）, anchor: choosing}
  - {title: 落とし穴（値が重複すると節点を特定できない・削除した節点の指す先を使う）, anchor: pitfalls}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：各要素の前と次を配列（値が大きければ map）で持つ双方向リストで、「x の直後に y を挿入」「x を削除」「列の付け替え」を O(1) で行い、最後に先頭からたどって列を出力する。
    - **いつ使うか**：
        - 値 x の直後に y を挿入・値 x を削除する操作を繰り返し、最後の列を出力する
        - カードの山を別のカードの上へ付け替える
        - 列車の連結・切り離し
    - **計算量**：（執筆時に書く）
    - **前提**：[STL コンテナの使い分け](../ds/stl-containers.md)
