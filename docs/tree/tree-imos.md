---
id: tree-imos
title: 木の上の累積和・いもす法
aliases: [木上のいもす法, 部分木加算, パス加算, 木上の累積和, prefix sums on a tree]
type: technique
field: tree
chapter: 木の基礎
order: 50
level: 基礎
kind: [木, 累積和・差分]
prerequisites: [tree-traversal, imos]
related: [euler-tour, lca, tree-path]
summary: 部分木への加算をまとめて受けてから値を出力するなら、部分木の根に印を置いて根から下へ累積する。パスへの加算は端点と LCA に印を置いて葉から上へ累積し、途中で値を聞かれるならオイラーツアーを使う。
complexity: null
signs:
  - {type: phrase, text: 部分木の全頂点に x を加算するクエリがたくさん来て、最後に全頂点の値を出力する}
  - {type: phrase, text: 辺のどちら側かの頂点すべてに加算する}
  - {type: phrase, text: 多数のパスに沿って +1 し、各辺・各頂点を通った回数を求める}
acl: []
frequency: B
frequency_evidence: recent 0・前提として届くページなし・古い ABC 3 問
sections:
  - {title: 部分木への加算（根から下へ累積する）, anchor: subtree-add}
  - {title: 辺の片側への加算を子の部分木への加算に直す, anchor: edge-side}
  - {title: 根から y 世代までに及ぶ値を伝える, anchor: depth-limited}
  - {title: 途中で値を聞かれるならオイラーツアーと BIT, anchor: online-queries}
  - {title: パスへの加算（LCA に印を置いて葉から上へ累積する）, anchor: path-add, level: 青}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：部分木への加算をまとめて受けてから値を出力するなら、部分木の根に印を置いて根から下へ累積する。パスへの加算は端点と LCA に印を置いて葉から上へ累積し、途中で値を聞かれるならオイラーツアーを使う。
    - **いつ使うか**：
        - 部分木の全頂点に x を加算するクエリがたくさん来て、最後に全頂点の値を出力する
        - 辺のどちら側かの頂点すべてに加算する
        - 多数のパスに沿って +1 し、各辺・各頂点を通った回数を求める
    - **計算量**：（執筆時に書く）
    - **前提**：[根付き木と走査順](../tree/tree-traversal.md)、[いもす法](../basics/imos.md)
