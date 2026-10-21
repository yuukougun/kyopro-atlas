---
id: tree-basics
title: 木の基本性質と表現
aliases: [木の定義, 森, 根付き木, 木の性質, 親の番号が自分より小さい入力, tree, forest]
type: technique
field: tree
chapter: 木の基礎
order: 10
level: 基礎
kind: [木]
prerequisites: [dfs]
related: [tree-traversal, namori-graph, functional-graph, tree-degree, connected-components, tree-bipartite]
summary: 連結で辺が N−1 本・閉路がない・2 点間のパスがちょうど 1 本、の 3 つは同値で、辺を 1 本除くと 2 つに分かれ、1 本足すと閉路が 1 つできる。根の決め方と、辺の値を子の頂点に寄せる小技が多くの問題の出発点になる。
complexity: null
signs:
  - {type: phrase, text: 辺を 1 本取り除く・1 本足す・閉路をなくして森にする}
  - {type: phrase, text: 森として残せる辺の数・消す辺の数}
acl: []
frequency: A
frequency_evidence: recent 0・前提として 28 ページに届く（直接 3）・古い ABC 4 問
sections:
  - {title: 木の同じ意味の定義と、そこから使える事実の一覧, anchor: definitions}
  - {title: 入力の形（辺のリスト・親の配列・p_i < i）と根の決め方, anchor: input-forms}
  - {title: 辺を 1 本取り除くと 2 つの成分、1 本足すと閉路が 1 つ, anchor: remove-add-edge}
  - {title: 森の連結成分の数 = 頂点数 − 辺数, anchor: forest}
  - {title: 辺の値を子の頂点に寄せる, anchor: edge-to-child}
  - {title: 形の両極端（パスと星）でテストする, anchor: extremes}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：連結で辺が N−1 本・閉路がない・2 点間のパスがちょうど 1 本、の 3 つは同値で、辺を 1 本除くと 2 つに分かれ、1 本足すと閉路が 1 つできる。根の決め方と、辺の値を子の頂点に寄せる小技が多くの問題の出発点になる。
    - **いつ使うか**：
        - 辺を 1 本取り除く・1 本足す・閉路をなくして森にする
        - 森として残せる辺の数・消す辺の数
    - **計算量**：（執筆時に書く）
    - **前提**：[深さ優先探索（DFS）](../graph/dfs.md)
