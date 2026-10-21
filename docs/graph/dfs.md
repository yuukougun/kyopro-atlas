---
id: dfs
title: 深さ優先探索（DFS）
aliases: [深さ優先探索, DFS, depth-first search, 単純パスの列挙]
type: technique
field: graph
chapter: 基本と探索
order: 30
level: 基礎
kind: [グラフ探索]
prerequisites: [graph-basics]
related: [bfs, connected-components, cycle-detection, topological-sort, tree-traversal, recursive-enumeration, cpp-lambda#recursive-lambda, cpp-environment#stack-depth]
summary: 行けるところまで進んでから戻る探索で、到達可能性・連結成分・閉路検出・トポロジカル順の土台になる。帰りがけで訪問の印を外せば単純パスを全列挙できる。
complexity: null
signs:
  - {type: phrase, text: すべての単純パス・経路を数える（答えが上限を超えたら打ち切ってよい）}
  - {type: phrase, text: 依存関係をたどり、必要なものを先に済ませる順に出力する}
  - {type: constraint, text: N ≤ 10 程度で、経路を全部列挙できる}
acl: []
frequency: A
frequency_evidence: recent 0・前提として 58 ページに届く（直接 11）・古い ABC 3 問
sections:
  - {title: 一度訪れた頂点は二度と訪れない型（O(N+M)）, anchor: visit-once}
  - {title: バックトラック型（帰りがけで印を外す）, anchor: backtracking}
  - {title: 行きがけ順と帰りがけ順, anchor: pre-post-order}
  - {title: 非再帰の DFS と再帰の深さ, anchor: iterative}
  - {title: BFS・Union-Find との使い分け, anchor: comparison}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：行けるところまで進んでから戻る探索で、到達可能性・連結成分・閉路検出・トポロジカル順の土台になる。帰りがけで訪問の印を外せば単純パスを全列挙できる。
    - **いつ使うか**：
        - すべての単純パス・経路を数える（答えが上限を超えたら打ち切ってよい）
        - 依存関係をたどり、必要なものを先に済ませる順に出力する
        - N ≤ 10 程度で、経路を全部列挙できる
    - **計算量**：（執筆時に書く）
    - **前提**：[グラフの表現と用語](../graph/graph-basics.md)
