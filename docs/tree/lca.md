---
id: lca
title: 最小共通祖先（LCA）
aliases: [LCA, Lowest Common Ancestor, 最近共通祖先, 木のダブリング, K 個上の祖先, level ancestor]
type: technique
field: tree
chapter: パス
order: 150
level: 青
kind: [木, ダブリング・分割統治]
prerequisites: [tree-traversal, doubling]
related: [tree-path, euler-tour, sparse-table, hld, complete-binary-tree, bottleneck-path, auxiliary-tree]
summary: 根付き木で 2 頂点の共通の祖先のうち最も深いものを、各頂点の 2^k 個上の祖先の表（ダブリング）で、前処理 O(N log N)・1 回 O(log N) で求める。2 点間の距離・K 個上の祖先・パス上の最大値にそのまま使える。
complexity: null
signs:
  - {type: phrase, text: 木の 2 頂点の距離をクエリでたくさん聞かれる}
  - {type: constraint, text: パス u–v に関するクエリが Q ≤ 2×10^5 個}
  - {type: phrase, text: ちょうど距離 K の頂点・K 個上の祖先}
acl: []
verify: [lca]
frequency: A
frequency_evidence: recent 2（abc460_f・abc477_g）・前提として 6 ページに届く（直接 4）・古い ABC 5 問
sections:
  - {title: 深さをそろえてから同時に跳ぶ, anchor: jump}
  - {title: 距離 = dep(u) + dep(v) − 2 dep(lca), anchor: distance}
  - {title: K 個上の祖先（K を 2 進数に分けて跳ぶ）, anchor: kth-ancestor}
  - {title: パス上の最大値・和を表と一緒に持つ, anchor: path-aggregate}
  - {title: 条件を満たす最も遠い祖先, anchor: farthest-ancestor}
  - {title: LCA の求め方の比較（ダブリング・オイラーツアーと Sparse Table・HL 分解・オフライン）, anchor: comparison}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：根付き木で 2 頂点の共通の祖先のうち最も深いものを、各頂点の 2^k 個上の祖先の表（ダブリング）で、前処理 O(N log N)・1 回 O(log N) で求める。2 点間の距離・K 個上の祖先・パス上の最大値にそのまま使える。
    - **いつ使うか**：
        - 木の 2 頂点の距離をクエリでたくさん聞かれる
        - パス u–v に関するクエリが Q ≤ 2×10^5 個
        - ちょうど距離 K の頂点・K 個上の祖先
    - **計算量**：（執筆時に書く）
    - **前提**：[根付き木と走査順](../tree/tree-traversal.md)、[ダブリング](../basics/doubling.md)
