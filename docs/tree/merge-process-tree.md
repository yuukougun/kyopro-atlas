---
id: merge-process-tree
title: 併合過程の木
aliases: [クラスカル再構築木, Kruskal 再構築木, Kruskal reconstruction tree, KRT, DSU-tree, Union-Find の併合の過程を表す木]
type: overview
field: tree
chapter: まとめる・分ける
order: 250
level: 発展
kind: [木, 連結性・全域木]
prerequisites: [minimum-spanning-tree, euler-tour, lca]
related: [bottleneck-path, small-to-large, partially-persistent-union-find, parallel-binary-search]
summary: Union-Find の併合のたびに新しい頂点を作って 2 つの成分を子にした木を作ると、ある時点のグループが DFS 順の区間になる。辺を重みの順に併合すれば、2 点の LCA の重みが経路の最大の辺の最小値になる。
complexity: null
signs:
  - {type: phrase, text: ある時点のグループについての問い合わせ（オフライン）}
  - {type: phrase, text: パス上の最大の辺の最小値（ボトルネック）をオンラインで多数答える}
  - {type: phrase, text: 辺を重みの順に足していく過程を後から問われる}
acl: [dsu]
frequency: C
frequency_evidence: recent 0・前提として届くページなし・古い ABC 1 問
sections:
  - {title: 併合のたびに新しい頂点を作る, anchor: new-vertex}
  - {title: ある時点のグループは DFS 順の区間, anchor: group-as-interval}
  - {title: ボトルネックは LCA の重み, anchor: bottleneck}
  - {title: マージテク・部分永続 Union-Find・並列二分探索との使い分け, anchor: alternatives}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：Union-Find の併合のたびに新しい頂点を作って 2 つの成分を子にした木を作ると、ある時点のグループが DFS 順の区間になる。辺を重みの順に併合すれば、2 点の LCA の重みが経路の最大の辺の最小値になる。
    - **いつ使うか**：
        - ある時点のグループについての問い合わせ（オフライン）
        - パス上の最大の辺の最小値（ボトルネック）をオンラインで多数答える
        - 辺を重みの順に足していく過程を後から問われる
    - **計算量**：（執筆時に書く）
    - **前提**：[最小全域木](../graph/minimum-spanning-tree.md)、[オイラーツアー](../tree/euler-tour.md)、[最小共通祖先（LCA）](../tree/lca.md)
