---
id: priority-queue
title: 優先度付きキュー
aliases: [priority_queue, ヒープ, heap, 二分ヒープ, binary heap, 削除できるヒープ, 遅延削除, erasable heap]
type: technique
field: ds
chapter: 標準コンテナの応用
order: 30
level: 水
kind: [データ構造, 貪欲]
prerequisites: [stl-containers]
related: [greedy-priority-queue, kth-value, top-k-multiset, ordered-set, global-offset, dijkstra, cpp-comparators, advanced-ds-catalog]
summary: 最大（最小）の要素の取り出しと追加を O(log N) で行う。ソートと組む貪欲・上位 K 個の列挙・接頭辞の K 番目に使い、任意の要素の削除は削除予定のヒープで遅らせて行う。
complexity: null
signs:
  - {type: phrase, text: 毎回いちばん大きい（小さい）ものを取り出し、新しい候補を入れる}
  - {type: phrase, text: 接頭辞ごとに K 番目に大きい値を答える}
  - {type: phrase, text: グループ間の移動のたびに、各グループの最大値のうちの最小値を答える}
  - {type: constraint, text: 追加と取り出しが合わせて 2×10^5 回程度}
acl: []
verify: []
frequency: B
frequency_evidence: recent 1（abc471_d）・前提として 3 ページに届く（直接 2）・古い ABC 7 問
sections:
  - {title: 何ができるか（push・top・pop。最小を取り出す向きと pair の比較順。書き方は C++ 章）, anchor: what-it-does}
  - {title: 二分ヒープの仕組み（保つ性質「親 ≤ 子」・push で上げる・pop で下げる・heapify は O(N)）, anchor: binary-heap}
  - {title: 使い方の型（ソートと組む貪欲・上位 K 個の列挙・大きさ K のヒープで接頭辞の K 番目）, anchor: patterns}
  - {title: 全体への加算と組む（入れるときに引き、出すときに足す）, anchor: with-offset}
  - {title: 削除できるヒープ（遅延削除：削除予定のヒープの top と一致したら両方から捨てる）, anchor: lazy-deletion}
  - {title: priority_queue と multiset の使い分け（任意の削除・両端・前後の要素が要るなら multiset）, anchor: vs-multiset}
  - {title: 落とし穴（向きの取り違え・古いエントリを捨て忘れる・空のときの top）, anchor: pitfalls}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：最大（最小）の要素の取り出しと追加を O(log N) で行う。ソートと組む貪欲・上位 K 個の列挙・接頭辞の K 番目に使い、任意の要素の削除は削除予定のヒープで遅らせて行う。
    - **いつ使うか**：
        - 毎回いちばん大きい（小さい）ものを取り出し、新しい候補を入れる
        - 接頭辞ごとに K 番目に大きい値を答える
        - グループ間の移動のたびに、各グループの最大値のうちの最小値を答える
        - 追加と取り出しが合わせて 2×10^5 回程度
    - **計算量**：（執筆時に書く）
    - **前提**：[STL コンテナの使い分け](../ds/stl-containers.md)
