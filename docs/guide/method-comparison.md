---
id: method-comparison
title: 似た手法の使い分け
aliases: [手法の比較, どれを使うか, 使い分け, 混同しやすい手法, 最短路の選び方, 最短路の比較, 最短路アルゴリズムの使い分け]
type: guide
field: guide
chapter: 辞書として引く
order: 50
level: null
kind: [案内]
prerequisites: []
related: [bfs, zero-one-bfs, dijkstra, bellman-ford, warshall-floyd, extended-dijkstra, shortest-path-dag, dp-speedup-overview, kth-and-median#dynamic, subsequence-and-substring#properties, stl-containers, reverse-index-signs, cheatsheet]
summary: BFS・01-BFS・ダイクストラや累積和・BIT・セグメント木のように混同しやすい手法の組を、できる操作・計算量・前提条件で比べ、条件から選べる。
complexity: null
signs: []
acl: []
sections:
  - {title: 比べる観点, anchor: criteria}
  - {title: 最短路の選び方（重みと始点の数）, anchor: shortest-path}
  - {title: 最短路の判断の順序, anchor: shortest-path-steps}
  - {title: 最短路に共通の性質, anchor: shortest-path-properties}
  - {title: 区間の集約, anchor: range-queries}
  - {title: 二分探索の種類, anchor: binary-search}
  - {title: 繰り返しの高速化, anchor: repetition}
  - {title: 小さい N の全探索, anchor: small-n}
  - {title: 数え方, anchor: counting}
  - {title: ゲーム, anchor: games}
  - {title: 連結性, anchor: connectivity}
  - {title: 木の手法, anchor: trees}
  - {title: 集合とキュー, anchor: containers}
  - {title: 文字列の照合, anchor: strings}
  - {title: 最適化の方針, anchor: optimization}
  - {title: 名前が似た別物, anchor: similar-names}
  - {title: 数の扱い, anchor: numbers}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何のページか**：BFS・01-BFS・ダイクストラや累積和・BIT・セグメント木のように混同しやすい手法の組を、できる操作・計算量・前提条件で比べ、条件から選べる。
    - **使い方**：（執筆時に書く）
