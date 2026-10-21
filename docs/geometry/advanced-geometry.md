---
id: advanced-geometry
title: 発展の幾何
aliases: [回転キャリパー, rotating calipers, 最遠点対, 最近点対, closest pair, 半平面交差, 動的凸包, ミンコフスキー和, Minkowski sum, ボロノイ図, ドロネー三角形分割, 円の反転]
type: overview
field: geometry
order: 80
level: 発展
kind: [幾何]
prerequisites: [convex-hull]
related: [cht, sweep-line-2d, divide-and-conquer, spanning-tree-advanced]
summary: 動的な凸包・回転キャリパー（最遠点対）・最近点対・半平面交差・ミンコフスキー和で、点集合と凸図形の最大・最小・共通部分を O(N log N) 前後で求める。ABC での出題はまれで、Library Checker で確かめられる。
complexity: null
signs:
  - {type: phrase, text: 最も遠い 2 点（凸包上の対蹠点）}
  - {type: phrase, text: 最も近い 2 点（N ≤ 2×10^5）}
  - {type: phrase, text: 点の追加と ax+by の最大のクエリ}
  - {type: phrase, text: 2 つの凸な点集合の和の凸包}
  - {type: phrase, text: 半平面の共通部分}
acl: []
verify: [closest_pair, furthest_pair]
frequency: B
frequency_evidence: recent 1（abc478_g）・前提として届くページなし・古い ABC 1 問
sections:
  - {title: 動的な凸包（点の追加と ax+by の最大）, anchor: dynamic-hull}
  - {title: 回転キャリパー（凸包上の最遠点対）, anchor: rotating-calipers}
  - {title: 最近点対（分割統治・平面走査で O(N log N)）, anchor: closest-pair}
  - {title: 半平面交差, anchor: half-plane-intersection}
  - {title: ミンコフスキー和（凸包の和）, anchor: minkowski-sum}
  - {title: ボロノイ図・ドロネー三角形分割, anchor: voronoi}
  - {title: 線分の交点の列挙（Bentley-Ottmann）, anchor: segment-intersections}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：動的な凸包・回転キャリパー（最遠点対）・最近点対・半平面交差・ミンコフスキー和で、点集合と凸図形の最大・最小・共通部分を O(N log N) 前後で求める。ABC での出題はまれで、Library Checker で確かめられる。
    - **いつ使うか**：
        - 最も遠い 2 点（凸包上の対蹠点）
        - 最も近い 2 点（N ≤ 2×10^5）
        - 点の追加と ax+by の最大のクエリ
        - 2 つの凸な点集合の和の凸包
        - 半平面の共通部分
    - **計算量**：（執筆時に書く）
    - **前提**：[凸包と凸多角形](../geometry/convex-hull.md)
