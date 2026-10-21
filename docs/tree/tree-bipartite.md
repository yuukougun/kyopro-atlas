---
id: tree-bipartite
title: 木の 2 色塗り分けと距離の偶奇
aliases: [木は二部グラフ, 深さの偶奇, 距離の偶奇, tree bipartition]
type: technique
field: tree
chapter: 木の基礎
order: 30
level: 基礎
kind: [木]
prerequisites: [tree-traversal, bipartite-graph]
related: [tree-distance, parity]
summary: 木は閉路がないので深さの偶奇で必ず 2 色に塗れ、2 点の距離の偶奇は深さの和の偶奇で分かる。多い方の色が N/2 個以上あることや、色の違う組の数を使う問題に効く。
complexity: null
signs:
  - {type: phrase, text: 距離の偶奇・2 人が同時に動いて出会う場所}
  - {type: phrase, text: 辺の重みの偶奇で頂点を塗り分ける}
  - {type: phrase, text: 独立集合を N/2 個以上選ぶ・二部グラフのまま辺を足す}
acl: []
frequency: B
frequency_evidence: recent 0・前提として届くページなし・古い ABC 3 問
sections:
  - {title: 深さの偶奇で塗る（重みがあるなら重みの偶奇で）, anchor: by-depth}
  - {title: 距離の偶奇は深さだけで分かる, anchor: distance-parity}
  - {title: 多い方の色は N/2 個以上, anchor: majority-color}
  - {title: 色の違う組の数（二部グラフのまま足せる辺）, anchor: cross-pairs}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：木は閉路がないので深さの偶奇で必ず 2 色に塗れ、2 点の距離の偶奇は深さの和の偶奇で分かる。多い方の色が N/2 個以上あることや、色の違う組の数を使う問題に効く。
    - **いつ使うか**：
        - 距離の偶奇・2 人が同時に動いて出会う場所
        - 辺の重みの偶奇で頂点を塗り分ける
        - 独立集合を N/2 個以上選ぶ・二部グラフのまま辺を足す
    - **計算量**：（執筆時に書く）
    - **前提**：[根付き木と走査順](../tree/tree-traversal.md)、[二部グラフ判定](../graph/bipartite-graph.md)
