---
id: graph-basics
title: グラフの表現と用語
aliases: [グラフの基本, 隣接リスト, 隣接行列, 辺リスト, 次数, adjacency list, graph representation]
type: technique
field: graph
chapter: 基本と探索
order: 10
level: 基礎
kind: [グラフ探索]
prerequisites: []
related: [complexity-estimation, dfs, bfs, grid-graph, graph-modeling]
summary: N 頂点 M 辺のグラフを隣接リスト・隣接行列・辺リストのどれで持つかを選び、次数・パス・連結・木・DAG などの用語をそろえる。アルゴリズムごとに向く表現が決まっている。
complexity: null
signs:
  - {type: phrase, text: グラフが N×N の 0/1 の表（隣接行列）で与えられる}
  - {type: constraint, text: N ≤ 2×10^5 では N^2 の隣接行列を持てない（N ≤ 2000 程度なら持てる）}
acl: []
frequency: A
frequency_evidence: recent 0・前提として 84 ページに届く（直接 5）・古い ABC 1 問
sections:
  - {title: 隣接リスト・隣接行列・辺リストとアルゴリズムごとの使い分け, anchor: representations}
  - {title: 用語（次数・パスとウォーク・単純グラフ・連結・木・DAG・二部グラフ・補グラフ）, anchor: terms}
  - {title: 握手補題（次数の和は 2M）, anchor: handshake}
  - {title: 落とし穴（1-indexed・無向グラフは両方向に追加・多重辺・重みの和のあふれ）, anchor: pitfalls}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：N 頂点 M 辺のグラフを隣接リスト・隣接行列・辺リストのどれで持つかを選び、次数・パス・連結・木・DAG などの用語をそろえる。アルゴリズムごとに向く表現が決まっている。
    - **いつ使うか**：
        - グラフが N×N の 0/1 の表（隣接行列）で与えられる
        - N ≤ 2×10^5 では N^2 の隣接行列を持てない（N ≤ 2000 程度なら持てる）
    - **計算量**：（執筆時に書く）
    - **前提**：なし
