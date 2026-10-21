---
id: centroid-decomposition
title: 重心分解
aliases: [centroid decomposition, 点分治, 木の分割統治]
type: technique
field: tree
chapter: まとめる・分ける
order: 230
level: 黄
kind: [木, ダブリング・分割統治]
prerequisites: [tree-centroid, divide-and-conquer]
related: [tree-edge-contribution, small-to-large, auxiliary-tree, convolution-ntt]
summary: 重心を取り、重心を通るパスを一度に処理してから重心を消し、残った各成分で再帰する。成分の大きさが半分以下になるので深さは O(log N) で、距離がちょうど K のペアの数など、辺ごとに分けられない全ペアの量を数えられる。
complexity: null
signs:
  - {type: phrase, text: 距離がちょうど K の頂点の組の個数}
  - {type: phrase, text: 全ペアのパスについての量で、辺ごとに分解できないもの}
  - {type: phrase, text: ある頂点から距離 d 以内の頂点の集計クエリ}
acl: []
verify: [frequency_table_of_tree_distance]
frequency: C
frequency_evidence: recent 0・前提として届くページなし・古い ABC 2 問
sections:
  - {title: 再帰の深さが log N になる理由, anchor: depth}
  - {title: 重心を通るペアを数え、同じ成分の中のペアを引く, anchor: count-through}
  - {title: 木全体の数え上げと、重心木を上にたどるクエリ, anchor: centroid-tree-queries}
  - {title: 距離の頻度表は畳み込みと組む, anchor: with-convolution, level: 発展}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：重心を取り、重心を通るパスを一度に処理してから重心を消し、残った各成分で再帰する。成分の大きさが半分以下になるので深さは O(log N) で、距離がちょうど K のペアの数など、辺ごとに分けられない全ペアの量を数えられる。
    - **いつ使うか**：
        - 距離がちょうど K の頂点の組の個数
        - 全ペアのパスについての量で、辺ごとに分解できないもの
        - ある頂点から距離 d 以内の頂点の集計クエリ
    - **計算量**：（執筆時に書く）
    - **前提**：[木の重心](../tree/tree-centroid.md)、[分割統治](../basics/divide-and-conquer.md)
