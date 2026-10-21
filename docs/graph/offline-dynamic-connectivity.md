---
id: offline-dynamic-connectivity
title: 辺の追加と削除が混ざる連結性
aliases: [Offline Dynamic Connectivity, オフライン動的連結性, 時間軸のセグ木, 辺の削除がある連結判定]
type: overview
field: graph
chapter: 連結性と全域木
order: 330
level: 発展
kind: [連結性・全域木, クエリ処理の工夫]
prerequisites: [union-find-connectivity, rollback-union-find, segment-tree]
related: [lowlink, offline-queries]
summary: 辺の追加と削除が混ざる連結性の質問に、各辺が存在する時間の区間を時間軸のセグ木の O(log Q) 個のノードに載せ、DFS で入るときに併合・出るときに取り消してオフラインで答える。
complexity: null
signs:
  - {type: phrase, text: 辺の追加と削除のクエリが混ざり、そのつど連結性を答える（先に全部読んでよい）}
  - {type: phrase, text: 各要素が「ない」時刻の区間がいくつかある}
acl: []
frequency: C
frequency_evidence: recent 0・前提として届くページなし・古い ABC 1 問
sections:
  - {title: 各辺の存在する区間を時間軸のセグ木に載せる, anchor: time-segment-tree}
  - {title: DFS で入るときに併合・出るときに取り消す（ロールバック Union-Find はデータ構造の章）, anchor: dfs-rollback}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：辺の追加と削除が混ざる連結性の質問に、各辺が存在する時間の区間を時間軸のセグ木の O(log Q) 個のノードに載せ、DFS で入るときに併合・出るときに取り消してオフラインで答える。
    - **いつ使うか**：
        - 辺の追加と削除のクエリが混ざり、そのつど連結性を答える（先に全部読んでよい）
        - 各要素が「ない」時刻の区間がいくつかある
    - **計算量**：（執筆時に書く）
    - **前提**：[Union-Find で連結性を扱う](../graph/union-find-connectivity.md)、[ロールバックできる Union-Find](../ds/rollback-union-find.md)、[セグメント木](../ds/segment-tree.md)
