---
id: steiner-subtree
title: 指定頂点を結ぶ最小の部分木
aliases: [指定頂点を含む最小の部分木, 必要な辺の数, 木の上のシュタイナー木, Steiner tree on a tree]
type: technique
field: tree
chapter: 木の基礎
order: 60
level: 基礎
kind: [木]
prerequisites: [tree-traversal]
related: [lca, euler-tour, auxiliary-tree#steiner-queries, leaf-first, steiner-tree]
summary: 指定した K 頂点をすべて含む最小の連結な部分グラフは一意な部分木で、指定頂点の 1 つを根にして、部分木に指定頂点を含む頂点を残せば求まる。指定されていない葉を削り続けても同じになる。
complexity: null
signs:
  - {type: phrase, text: 指定した K 頂点をすべて連結に保つのに必要な最小の頂点数・辺数}
acl: []
frequency: C
frequency_evidence: recent 0・前提として 1 ページに届く（直接 1）・古い ABC 1 問
sections:
  - {title: 指定頂点を根にして、部分木に指定頂点を含むかで判定する, anchor: root-at-terminal}
  - {title: 指定されていない葉を削り続ける, anchor: prune-leaves}
  - {title: 一般のグラフのシュタイナー木は別物（グラフの章）, anchor: vs-graph}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：指定した K 頂点をすべて含む最小の連結な部分グラフは一意な部分木で、指定頂点の 1 つを根にして、部分木に指定頂点を含む頂点を残せば求まる。指定されていない葉を削り続けても同じになる。
    - **いつ使うか**：指定した K 頂点をすべて連結に保つのに必要な最小の頂点数・辺数
    - **計算量**：（執筆時に書く）
    - **前提**：[根付き木と走査順](../tree/tree-traversal.md)
