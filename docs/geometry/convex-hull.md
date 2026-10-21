---
id: convex-hull
title: 凸包と凸多角形
aliases: [凸包, convex hull, Andrew のアルゴリズム, monotone chain, Graham scan, 上側凸包, 下側凸包, 点の内外判定, 凸多角形の内外判定, 交差数判定, Pick の定理, 多角形の格子点, 線分上の格子点]
type: technique
field: geometry
order: 70
level: 黄
kind: [幾何]
prerequisites: [geometry-vectors, binary-search, gcd-lcm]
related: [cht, argument-sort, advanced-geometry, monotonic-stack, fractional-binary-search, floor-sum#swap-axes]
summary: 点を x 座標でソートし、スタックの末尾が凹む間は取り除くことで、全点を囲む最小の凸多角形（凸包）を O(N log N) で作る。凸多角形への多数の点の内外判定（1 点 O(log N)）や、格子点の数（Pick の定理）にも使う。
complexity: null
signs:
  - {type: phrase, text: すべての点を囲む最小の凸多角形}
  - {type: phrase, text: 外側にある点だけが効く}
  - {type: phrase, text: 区間の平均・傾き・比の最大}
  - {type: phrase, text: 多数の点が凸多角形の内部・境界・外部のどこにあるか}
  - {type: phrase, text: 多角形の内部にある格子点の数}
  - {type: shape, text: (S_j − S_i)/(j − i) の最大（2 点を結ぶ傾きの最大）}
acl: []
verify: [static_convex_hull]
frequency: B
frequency_evidence: recent 1（abc478_g）・前提として 2 ページに届く（直接 2）・古い ABC 5 問
sections:
  - {title: Andrew 法（monotone chain）：下側と上側を作る, anchor: andrew}
  - {title: 一直線上の点・重複点・全点が一直線上のときの扱い（外積の不等号の向き）, anchor: degenerate}
  - {title: 比・平均の最大は上側凸包の接線（累積和の点）, anchor: max-slope}
  - {title: '凸包と CHT の双対（点 (a, b) と直線 y = ax+b）', anchor: cht-duality}
  - {title: 凸多角形の内外判定：扇形に分けて二分探索（O(log N)）, anchor: point-in-convex-polygon}
  - {title: 一般の多角形の内外判定（交差数の偶奇）, anchor: point-in-polygon}
  - {title: '格子点：線分上は gcd(|dx|, |dy|)+1、Pick の定理 S = i + b/2 − 1（面積の 2 倍で整数のまま）', anchor: lattice-points}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：点を x 座標でソートし、スタックの末尾が凹む間は取り除くことで、全点を囲む最小の凸多角形（凸包）を O(N log N) で作る。凸多角形への多数の点の内外判定（1 点 O(log N)）や、格子点の数（Pick の定理）にも使う。
    - **いつ使うか**：
        - すべての点を囲む最小の凸多角形
        - 外側にある点だけが効く
        - 区間の平均・傾き・比の最大
        - 多数の点が凸多角形の内部・境界・外部のどこにあるか
        - 多角形の内部にある格子点の数
        - (S_j − S_i)/(j − i) の最大（2 点を結ぶ傾きの最大）
    - **計算量**：（執筆時に書く）
    - **前提**：[ベクトルと外積](../geometry/geometry-vectors.md)、[二分探索](../basics/binary-search.md)、[GCD・LCM とユークリッドの互除法](../math/gcd-lcm.md)
