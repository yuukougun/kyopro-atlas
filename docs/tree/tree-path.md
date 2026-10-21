---
id: tree-path
title: 木の上のパスの判定と分解
aliases: [パスクエリ, 2 頂点間のパス, パスの分解, 合流点, パスの交差, path queries on a tree]
type: technique
field: tree
chapter: パス
order: 160
level: 青
kind: [木]
prerequisites: [lca, tree-distance]
related: [euler-tour, hld, inclusion-exclusion, tree-imos]
summary: パス u–v を「u から LCA へ上る」と「LCA から v へ下る」に分け、点がパス上にあるか・3 点の合流点・2 本のパスの交差・パス上の K 番目の頂点を、LCA と距離の式で判定する。
complexity: null
signs:
  - {type: phrase, text: u から v へのパス上の…・パスに含まれる辺}
  - {type: phrase, text: 2 本のパスが交わるか・共通部分}
  - {type: phrase, text: どちらの端点に近いか（パスの中点）}
acl: []
verify: [jump_on_tree]
frequency: B
frequency_evidence: recent 0・前提として届くページなし・古い ABC 3 問
sections:
  - {title: '点 x がパス上にあるか（d(u,x) + d(x,v) = d(u,v)）', anchor: on-path}
  - {title: 3 点の合流点と根の付け替え, anchor: meeting-point}
  - {title: 2 本のパスの交差, anchor: intersection}
  - {title: パス上の K 番目の頂点, anchor: kth-on-path}
  - {title: 頂点の値と辺の値で LCA の扱いが違う, anchor: vertex-vs-edge}
  - {title: パスを辺の集合として扱う（包除原理）, anchor: edge-set}
  - {title: パスへの一括更新があるなら HL 分解, anchor: to-hld, level: 発展}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：パス u–v を「u から LCA へ上る」と「LCA から v へ下る」に分け、点がパス上にあるか・3 点の合流点・2 本のパスの交差・パス上の K 番目の頂点を、LCA と距離の式で判定する。
    - **いつ使うか**：
        - u から v へのパス上の…・パスに含まれる辺
        - 2 本のパスが交わるか・共通部分
        - どちらの端点に近いか（パスの中点）
    - **計算量**：（執筆時に書く）
    - **前提**：[最小共通祖先（LCA）](../tree/lca.md)、[木の上の距離](../tree/tree-distance.md)
