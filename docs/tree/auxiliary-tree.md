---
id: auxiliary-tree
title: Auxiliary Tree
aliases: [Virtual Tree, 虚樹, 圧縮木, LCA 木, 指定頂点の圧縮木]
type: overview
field: tree
chapter: まとめる・分ける
order: 240
level: 発展
kind: [木]
prerequisites: [lca, euler-tour, steiner-subtree, tree-dp]
related: [small-to-large, centroid-decomposition]
summary: 色ごと・クエリごとに少数の頂点だけが関わる木の問題で、指定頂点と DFS 順で隣り合う 2 点の LCA だけからなる圧縮木を作って木 DP をする。関わる頂点数の合計が O(N) なら全体で O(N log N) になる。
complexity: null
signs:
  - {type: phrase, text: 色ごと・クエリごとに少数の頂点だけが関わり、その頂点数の合計が N 程度}
  - {type: phrase, text: クエリごとに指定された頂点をすべてつなぐのに必要な辺の数を答える}
  - {type: constraint, text: クエリごとに K_i 個の頂点が指定され、ΣK_i ≤ 2×10^5}
acl: []
frequency: C
frequency_evidence: recent 0・前提として届くページなし・古い ABC 2 問
sections:
  - {title: 指定頂点を結ぶ部分木の大きさ（DFS 順で隣り合う 2 点の距離の和の半分）, anchor: steiner-queries}
  - {title: DFS 順に並べて隣り合う 2 点の LCA を足す, anchor: build}
  - {title: スタックで組み立てる, anchor: stack-build}
  - {title: マージテク・平方分割で代用できる場合, anchor: alternatives}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：色ごと・クエリごとに少数の頂点だけが関わる木の問題で、指定頂点と DFS 順で隣り合う 2 点の LCA だけからなる圧縮木を作って木 DP をする。関わる頂点数の合計が O(N) なら全体で O(N log N) になる。
    - **いつ使うか**：
        - 色ごと・クエリごとに少数の頂点だけが関わり、その頂点数の合計が N 程度
        - クエリごとに指定された頂点をすべてつなぐのに必要な辺の数を答える
        - クエリごとに K_i 個の頂点が指定され、ΣK_i ≤ 2×10^5
    - **計算量**：（執筆時に書く）
    - **前提**：[最小共通祖先（LCA）](../tree/lca.md)、[オイラーツアー](../tree/euler-tour.md)、[指定頂点を結ぶ最小の部分木](../tree/steiner-subtree.md)、[木 DP](../dp/tree-dp.md)
