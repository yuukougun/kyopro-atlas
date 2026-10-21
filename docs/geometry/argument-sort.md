---
id: argument-sort
title: 偏角ソート
aliases: [偏角, 角度でソート, argument sort, atan2, 方向の順に並べる, 回転する光線]
type: technique
field: geometry
order: 30
level: 水
kind: [幾何, ソート・座標圧縮]
prerequisites: [geometry-vectors, sorting-techniques]
related: [geometry-precision, convex-hull, interval-scheduling, two-pointers, prefix-sum, rotation-transform]
summary: 点を原点から見た角度の順に並べる。整数座標なら上下の半平面に分け、同じ半平面の中は外積の符号で比べることで、atan2 を使わず誤差なく O(N log N) で並べられる。
complexity: null
signs:
  - {type: phrase, text: 原点から見た方向の順に並べる}
  - {type: phrase, text: 回転する光線（レーザー）に当たる点の数}
  - {type: phrase, text: ∠ABC の最大}
  - {type: phrase, text: ベクトルをいくつか選んで和の長さを最大にする}
  - {type: constraint, text: 座標が 10^9 規模の整数で、角度の大小や一致を正確に比べる}
acl: []
verify: [sort_points_by_argument]
frequency: B
frequency_evidence: recent 1（abc479_g）・前提として届くページなし・古い ABC 4 問
sections:
  - {title: 半平面に分けて外積で比べる（全周を外積だけで比べると推移律が壊れる理由）, anchor: half-plane-compare}
  - {title: atan2 の手軽さと限界, anchor: atan2}
  - {title: 原点・同じ方向の点・半平面の境界（x 軸の正と負）の扱い, anchor: edge-cases}
  - {title: 並べた後に：角度の範囲の点の数（累積和）, anchor: range-count}
  - {title: 一周を扱う：配列を 2 周分にして尺取り, anchor: wrap-around, level: 青}
  - {title: 反対方向に最も近い点の二分探索, anchor: opposite-direction, level: 青}
  - {title: 角度の区間のスケジューリング・連続する範囲だけを試す最適化, anchor: angular-intervals, level: 青}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：点を原点から見た角度の順に並べる。整数座標なら上下の半平面に分け、同じ半平面の中は外積の符号で比べることで、atan2 を使わず誤差なく O(N log N) で並べられる。
    - **いつ使うか**：
        - 原点から見た方向の順に並べる
        - 回転する光線（レーザー）に当たる点の数
        - ∠ABC の最大
        - ベクトルをいくつか選んで和の長さを最大にする
        - 座標が 10^9 規模の整数で、角度の大小や一致を正確に比べる
    - **計算量**：（執筆時に書く）
    - **前提**：[ベクトルと外積](../geometry/geometry-vectors.md)、[ソートで考える](../basics/sorting-techniques.md)
