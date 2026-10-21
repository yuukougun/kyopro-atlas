---
id: parallel-binary-search
title: 並列二分探索
aliases: [parallel binary search, 整体二分, 全クエリの二分探索を同時に進める]
type: overview
field: ds
chapter: クエリ処理の工夫
order: 300
level: 発展
kind: [クエリ処理の工夫, 二分探索]
prerequisites: [binary-search-answer, offline-queries]
related: [partially-persistent-union-find, union-find, cdq-divide-and-conquer, merge-process-tree]
summary: 多数のクエリがそれぞれ「単調な過程のどの時点で条件を満たすか」を二分探索するとき、全クエリの探索を同時に進める。各段で過程を最初から 1 回だけ流して判定し、段の数は O(log M) で済む。
complexity: null
signs:
  - {type: phrase, text: 多数のクエリが、それぞれ何回目の操作で条件を満たすようになるかを問う}
  - {type: phrase, text: 最初の t 回の操作の後に条件を満たす最小の t を、クエリごとに答える}
acl: []
verify: []
frequency: C
frequency_evidence: recent 0・前提として届くページなし・古い ABC 0 問
sections:
  - {title: 何ができるか（オフラインで全クエリの二分探索を一斉に進める）, anchor: what-it-does}
  - {title: 手順（各段で mid の順にクエリを並べ、過程を 1 回流して判定する）と計算量, anchor: procedure}
  - {title: Union-Find と組む例（最初の t 本の辺で条件を満たすか）, anchor: with-union-find}
  - {title: 代わりの手（部分永続 Union-Find・併合過程の木）, anchor: alternatives}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：多数のクエリがそれぞれ「単調な過程のどの時点で条件を満たすか」を二分探索するとき、全クエリの探索を同時に進める。各段で過程を最初から 1 回だけ流して判定し、段の数は O(log M) で済む。
    - **いつ使うか**：
        - 多数のクエリが、それぞれ何回目の操作で条件を満たすようになるかを問う
        - 最初の t 回の操作の後に条件を満たす最小の t を、クエリごとに答える
    - **計算量**：（執筆時に書く）
    - **前提**：[答えで二分探索](../basics/binary-search-answer.md)、[クエリの先読み](../ds/offline-queries.md)
