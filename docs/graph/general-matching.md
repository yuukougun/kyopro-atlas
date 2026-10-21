---
id: general-matching
title: 一般グラフのマッチング
aliases: [Edmonds, blossom, 花のアルゴリズム, 一般グラフの最大マッチング, general matching]
type: overview
field: graph
chapter: フロー・マッチング
order: 470
level: 発展
kind: [フロー・マッチング]
prerequisites: [bipartite-matching]
related: [bit-dp, konig-theorem]
summary: 二部グラフでないグラフの最大マッチングは、奇閉路（花）を縮約する Edmonds のアルゴリズムで多項式時間で求まる。N ≤ 16 程度なら bitDP で足りる。
complexity: null
signs:
  - {type: phrase, text: 二部グラフでないグラフでペアを作る最大数}
  - {type: constraint, text: N ≤ 16 程度の一般グラフでペアを作る}
acl: []
verify: [general_matching, general_weighted_matching]
frequency: C
frequency_evidence: recent 0・前提として届くページなし・古い ABC 1 問
sections:
  - {title: 二部グラフとの違い（奇閉路）, anchor: odd-cycles}
  - {title: Edmonds のアルゴリズムの概要, anchor: edmonds}
  - {title: 小さければ bitDP, anchor: bitdp}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：二部グラフでないグラフの最大マッチングは、奇閉路（花）を縮約する Edmonds のアルゴリズムで多項式時間で求まる。N ≤ 16 程度なら bitDP で足りる。
    - **いつ使うか**：
        - 二部グラフでないグラフでペアを作る最大数
        - N ≤ 16 程度の一般グラフでペアを作る
    - **計算量**：（執筆時に書く）
    - **前提**：[二部マッチング](../graph/bipartite-matching.md)
