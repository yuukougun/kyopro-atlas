---
id: small-graph-brute-force
title: 小さいグラフの全探索
aliases: [グラフ同型, 全域木の全列挙, 彩色の全探索, 頂点の対応の全探索, graph isomorphism]
type: technique
field: graph
chapter: 基本と探索
order: 90
level: 基礎
kind: [全探索, グラフ探索]
prerequisites: [dfs, bit-full-search]
related: [chromatic-number, bit-dp]
summary: N ≤ 8〜10 程度の小さいグラフで、頂点の対応（N! 通り）・辺の部分集合・彩色を全部試す。場合の数の見積もりと、成分ごとに分ける枝刈りが要になる。
complexity: null
signs:
  - {type: constraint, text: N ≤ 8〜10 で頂点の対応や辺の部分集合を全部試せる}
  - {type: phrase, text: 頂点の番号を付け替えて同じ形にできるか}
  - {type: phrase, text: 隣り合う頂点が異なる色になる 3 色の塗り方の数}
acl: []
frequency: B
frequency_evidence: recent 0・前提として届くページなし・古い ABC 4 問
sections:
  - {title: 頂点の対応の全探索（同型の判定・同型にするコスト）, anchor: isomorphism}
  - {title: 辺の部分集合の全探索（全域木の全列挙）, anchor: edge-subsets}
  - {title: 彩色は成分ごとに DFS で塗って探索を絞る, anchor: coloring, level: 青}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：N ≤ 8〜10 程度の小さいグラフで、頂点の対応（N! 通り）・辺の部分集合・彩色を全部試す。場合の数の見積もりと、成分ごとに分ける枝刈りが要になる。
    - **いつ使うか**：
        - N ≤ 8〜10 で頂点の対応や辺の部分集合を全部試せる
        - 頂点の番号を付け替えて同じ形にできるか
        - 隣り合う頂点が異なる色になる 3 色の塗り方の数
    - **計算量**：（執筆時に書く）
    - **前提**：[深さ優先探索（DFS）](../graph/dfs.md)、[bit 全探索と順列全探索](../basics/bit-full-search.md)
