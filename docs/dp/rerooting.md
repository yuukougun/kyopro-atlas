---
id: rerooting
title: 全方位木 DP
aliases: [Rerooting, ReRooting DP, 換根 DP]
type: technique
field: dp
chapter: 状態の形で分かれる DP
order: 280
level: 青
kind: [DP, 木]
prerequisites: [tree-dp, prefix-sum]
related: [tree-diameter#eccentricity, tree-edge-contribution#edge-pairs, centroid-decomposition]
summary: すべての頂点を根としたときの木 DP の値を、下向きの値と親側の部分木の値を 2 回の DFS で求めて O(N) で出す。兄弟を除いた合成は左右からの累積で作るので逆元が要らない。
complexity: null
signs:
  - {type: phrase, text: すべての頂点について、その頂点を根（起点）としたときの値}
  - {type: phrase, text: 各頂点から最も遠い頂点までの距離（頂点や辺の重みつき）}
  - {type: shape, text: 根を v としたときの木 DP の値を、すべての v について求めたい（N 回の木 DP は O(N^2)）}
acl: []
frequency: B
frequency_evidence: recent 0・前提として届くページなし・古い ABC 4 問
sections:
  - {title: 根を隣へ移すと変わるのは親側の部分木だけ, anchor: what-changes}
  - {title: 一般の枠組み（子の値の合成と「根を付ける」操作を分ける）, anchor: framework}
  - {title: 自分以外の兄弟の合成（左右からの累積）, anchor: exclude-self}
  - {title: 使い分け（最遠点は直径の性質で、距離の総和は根の移動の差分で済む）, anchor: when-to-use}
  - {title: 落とし穴：親側の値から自分自身の寄与を除き忘れる, anchor: pitfalls}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：すべての頂点を根としたときの木 DP の値を、下向きの値と親側の部分木の値を 2 回の DFS で求めて O(N) で出す。兄弟を除いた合成は左右からの累積で作るので逆元が要らない。
    - **いつ使うか**：
        - すべての頂点について、その頂点を根（起点）としたときの値
        - 各頂点から最も遠い頂点までの距離（頂点や辺の重みつき）
        - 根を v としたときの木 DP の値を、すべての v について求めたい（N 回の木 DP は O(N^2)）
    - **計算量**：（執筆時に書く）
    - **前提**：[木 DP](../dp/tree-dp.md)、[累積和](../basics/prefix-sum.md)
