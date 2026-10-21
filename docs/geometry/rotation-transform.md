---
id: rotation-transform
title: 回転・平行移動・アフィン変換
aliases: [回転行列, rotation matrix, 座標の回転, affine transformation, 合同変換, 複素数で回転, グリッドの回転, 90 度回転, 転置, 三角関数, ラジアン, 余弦定理]
type: technique
field: geometry
order: 40
level: 水
kind: [幾何, 線形代数・行列]
prerequisites: [geometry-vectors]
related: [matrix-power#composition, manhattan-chebyshev, argument-sort, brute-force, geometry-precision]
summary: 点の回転・反転・平行移動を式で計算し、操作列を何回か行った後の位置を求める。90 度回転は (−y, x) で整数のまま書け、操作は (x, y, 1) に掛ける 3×3 行列にすると積の累積で合成できる。
complexity: null
signs:
  - {type: phrase, text: 点を θ 度回転した位置}
  - {type: phrase, text: 回転・反転・平行移動の操作を順に行った後の位置のクエリ}
  - {type: phrase, text: 回転と平行移動で 2 つの点集合が重なるか}
  - {type: phrase, text: 盤面を 90 度回転して一致させる}
  - {type: constraint, text: 操作が M ≤ 2×10^5 回、各クエリは途中の時点での点の位置}
acl: []
verify: []
frequency: B
frequency_evidence: recent 0・前提として届くページなし・古い ABC 8 問
sections:
  - {title: 回転の式と、中心まわりの回転（中心を原点に移す・回す・戻す）, anchor: rotation-formula}
  - {title: 90 度回転・反転を整数のまま書く, anchor: rotate-90}
  - {title: 'アフィン変換：(x, y, 1) と 3×3 行列・掛ける順序（後の操作を左から掛ける）', anchor: affine}
  - {title: 操作列の累積とクエリ, anchor: prefix-composition}
  - {title: 'グリッドの回転・転置・反転の添字（(i, j) → (j, N−1−i)）', anchor: grid-rotation}
  - {title: 三角関数と角度の基本（度とラジアン・π は acos(−1)・余弦定理）, anchor: trig-angle}
  - {title: 点集合の合同判定：重心をそろえて照合する, anchor: congruence, level: 黄}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：点の回転・反転・平行移動を式で計算し、操作列を何回か行った後の位置を求める。90 度回転は (−y, x) で整数のまま書け、操作は (x, y, 1) に掛ける 3×3 行列にすると積の累積で合成できる。
    - **いつ使うか**：
        - 点を θ 度回転した位置
        - 回転・反転・平行移動の操作を順に行った後の位置のクエリ
        - 回転と平行移動で 2 つの点集合が重なるか
        - 盤面を 90 度回転して一致させる
        - 操作が M ≤ 2×10^5 回、各クエリは途中の時点での点の位置
    - **計算量**：（執筆時に書く）
    - **前提**：[ベクトルと外積](../geometry/geometry-vectors.md)
