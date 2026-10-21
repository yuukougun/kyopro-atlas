---
id: tree-dp
title: 木 DP
aliases: [Tree DP, 部分木の DP, 木の上の DP]
type: technique
field: dp
chapter: 状態の形で分かれる DP
order: 270
level: 水
kind: [DP, 木]
prerequisites: [dp-basics, tree-traversal]
related: [rerooting, tree-dp-square, small-to-large#subtree-merge, tree-diameter, tree-centroid, binary-search-answer#dp-check, cpp-environment#stack-depth, static-top-tree]
summary: 根を決めると各頂点の部分木は互いに交わらない小問題になるので、部分木ごとの値を子の値から帰りがけ順に求める。頂点自身の選択（白黒・選ぶか）を状態に足すのが基本形である。
complexity: null
signs:
  - {type: phrase, text: 木の各頂点を塗る・選ぶ（隣り合う頂点に条件がある）}
  - {type: phrase, text: 木の辺を選ぶ（次数の上限つき）}
  - {type: phrase, text: 部分木ごとの値（部分木の上位 K 個など）}
  - {type: phrase, text: 木の各頂点からほかの全頂点への距離の総和}
acl: []
frequency: B
frequency_evidence: recent 0・前提として 4 ページに届く（直接 4）・古い ABC 10 問
sections:
  - {title: 帰りがけ順に子から集める（再帰なしなら BFS 順の逆）, anchor: postorder}
  - {title: 頂点の選択を状態に足す（独立集合型）, anchor: vertex-states}
  - {title: 子の値の積・和（数え上げ）, anchor: product-of-children}
  - {title: 根から下へ配る, anchor: top-down}
  - {title: 根を動かした差分（全方位の入口）, anchor: reroot-difference}
  - {title: 子ごとの「得」を大きい順に取る, anchor: greedy-children, level: 青}
  - {title: 二分探索と組み合わせて判定にする, anchor: with-binary-search, level: 黄}
  - {title: 部分木の情報をデータ構造で持ってマージする（マージテク）, anchor: tree-dp-merge, level: 黄}
  - {title: 落とし穴：再帰の深さ・親への逆流・根の選び方, anchor: pitfalls}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：根を決めると各頂点の部分木は互いに交わらない小問題になるので、部分木ごとの値を子の値から帰りがけ順に求める。頂点自身の選択（白黒・選ぶか）を状態に足すのが基本形である。
    - **いつ使うか**：
        - 木の各頂点を塗る・選ぶ（隣り合う頂点に条件がある）
        - 木の辺を選ぶ（次数の上限つき）
        - 部分木ごとの値（部分木の上位 K 個など）
        - 木の各頂点からほかの全頂点への距離の総和
    - **計算量**：（執筆時に書く）
    - **前提**：[DP の基本](../dp/dp-basics.md)、[根付き木と走査順](../tree/tree-traversal.md)
