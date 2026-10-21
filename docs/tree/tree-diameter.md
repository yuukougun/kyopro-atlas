---
id: tree-diameter
title: 木の直径と最遠点
aliases: [直径, 最遠点, 離心数, double sweep, 2 回の BFS, 木の中心, 半径, 長鎖分解, long-path decomposition, tree diameter]
type: technique
field: tree
chapter: 木全体の形
order: 100
level: 水
kind: [木]
prerequisites: [tree-distance]
related: [rerooting, tree-centroid, lca, tree-construction, hld, tree-dp]
summary: 直径（最も遠い 2 点を結ぶパス）は、任意の点から最も遠い点 a を求め、a から最も遠い点 b を求めれば a–b になる（重みが非負のとき）。各点の最遠点は直径の端点のどちらかになる。
complexity: null
signs:
  - {type: phrase, text: 最も遠い 2 頂点・最長のパス}
  - {type: phrase, text: 全頂点を訪れる最短の移動（戻らなくてよい）}
  - {type: phrase, text: 各頂点から最も遠い頂点・2 つの木をつないだときの直径}
  - {type: phrase, text: 'K 個の頂点を選んで通る辺の総長を最大化する（K = 1, 2, … のすべてについて）'}
acl: []
verify: [tree_diameter]
frequency: B
frequency_evidence: recent 1（abc460_f）・前提として 1 ページに届く（直接 1）・古い ABC 8 問
sections:
  - {title: 2 回の最遠点探索が正しい理由, anchor: double-sweep}
  - {title: 各点の最遠点は直径の端点（離心数）, anchor: eccentricity}
  - {title: 全頂点を回る最短 = 2 × 辺の総和 − 直径, anchor: visit-all}
  - {title: 負の重みなら木 DP（DP の章）, anchor: negative-weights}
  - {title: 直径の端点を根にして距離 K の頂点を探す, anchor: root-at-end, level: 青}
  - {title: 2 つの木をつないだ直径, anchor: join-trees, level: 青}
  - {title: 中心と半径・直径の個数, anchor: center, level: 黄}
  - {title: 長鎖分解（最も深い子へつなぐ分解と、最も遠い葉を順に選ぶ貪欲）, anchor: long-path-decomposition, level: 黄}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：直径（最も遠い 2 点を結ぶパス）は、任意の点から最も遠い点 a を求め、a から最も遠い点 b を求めれば a–b になる（重みが非負のとき）。各点の最遠点は直径の端点のどちらかになる。
    - **いつ使うか**：
        - 最も遠い 2 頂点・最長のパス
        - 全頂点を訪れる最短の移動（戻らなくてよい）
        - 各頂点から最も遠い頂点・2 つの木をつないだときの直径
        - K 個の頂点を選んで通る辺の総長を最大化する（K = 1, 2, … のすべてについて）
    - **計算量**：（執筆時に書く）
    - **前提**：[木の上の距離](../tree/tree-distance.md)
