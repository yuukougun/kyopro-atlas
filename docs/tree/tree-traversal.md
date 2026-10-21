---
id: tree-traversal
title: 根付き木と走査順
aliases: [木の探索, 行きがけ順, 帰りがけ順, DFS 順, BFS 順, 部分木サイズ, 深さ, preorder, postorder]
type: technique
field: tree
chapter: 木の基礎
order: 20
level: 基礎
kind: [木, グラフ探索]
prerequisites: [tree-basics, bfs]
related: [euler-tour, tree-dp, cpp-environment#stack-depth, cpp-lambda#recursive-lambda]
summary: 根を決めて DFS か BFS をすると、親・深さ・部分木サイズ・行きがけ順・帰りがけ順が O(N) で求まる。帰りがけ順（または BFS 順の逆）で子の結果を親へ集約するのが木 DP の土台になる。
complexity: null
signs:
  - {type: phrase, text: 頂点 1 を根とする根付き木で、部分木の頂点数・和・最大を求める}
  - {type: phrase, text: 子孫・祖先・訪問順を答える}
  - {type: phrase, text: p_i < i（親の番号が自分より小さい）形で木が与えられる}
acl: []
frequency: A
frequency_evidence: recent 2（abc459_e・abc479_e）・前提として 25 ページに届く（直接 12）・古い ABC 6 問
sections:
  - {title: 親・深さ・部分木サイズを求める, anchor: parent-depth-size}
  - {title: 行きがけ順と帰りがけ順（子から親へ集約する）, anchor: pre-post-order}
  - {title: BFS 順の逆で再帰を使わずに集約する, anchor: bfs-order}
  - {title: p_i < i なら番号の逆順で足りる, anchor: parent-index}
  - {title: 再帰の深さ（パス状の木）と非再帰の書き方, anchor: recursion-depth}
  - {title: 一般の木 DP は DP の章へ, anchor: to-tree-dp}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：根を決めて DFS か BFS をすると、親・深さ・部分木サイズ・行きがけ順・帰りがけ順が O(N) で求まる。帰りがけ順（または BFS 順の逆）で子の結果を親へ集約するのが木 DP の土台になる。
    - **いつ使うか**：
        - 頂点 1 を根とする根付き木で、部分木の頂点数・和・最大を求める
        - 子孫・祖先・訪問順を答える
        - p_i < i（親の番号が自分より小さい）形で木が与えられる
    - **計算量**：（執筆時に書く）
    - **前提**：[木の基本性質と表現](../tree/tree-basics.md)、[幅優先探索（BFS）と無重み最短路](../graph/bfs.md)
