---
id: manhattan-chebyshev
title: マンハッタン距離と 45 度回転
aliases: [45 度回転, マンハッタン距離, Manhattan distance, チェビシェフ距離, Chebyshev distance, L1 距離, L∞ 距離, 'u=x+y, v=x−y', 絶対値を外す, 斜めの番号]
type: technique
field: geometry
order: 50
level: 水
kind: [幾何, 考察]
prerequisites: [sorting-techniques, prefix-sum]
related: [median-absolute, reformulation, segment-tree, prefix-sum-2d, lis, parity, rotation-transform, spanning-tree-advanced]
summary: u = x+y、v = x−y と座標を変える（45 度回転）と、マンハッタン距離はチェビシェフ距離 max(|Δu|, |Δv|) になる。ひし形の範囲が正方形に変わり、最遠点対・距離の和・斜め移動を x と y に分けて解ける。
complexity: null
signs:
  - {type: phrase, text: マンハッタン距離が最大の 2 点・ある点から最も遠い点}
  - {type: phrase, text: マンハッタン距離の和の最小・全ペアの距離の総和}
  - {type: phrase, text: 斜め移動（キングの移動）だけでの距離・斜めにしか動けない駒}
  - {type: phrase, text: ひし形の範囲（|x|+|y| ≤ D）にある点の数}
  - {type: constraint, text: N ≤ 2×10^5 点の全ペアのマンハッタン距離の和や最大を問い、全組 O(N^2) が間に合わない}
  - {type: shape, text: '|x_i − x_j| + |y_i − y_j| や max(|x_i − x_j|, |y_i − y_j|) の最大・和が式に出る'}
acl: [segtree]
verify: []
frequency: A
frequency_evidence: recent 2（abc457_g・abc476_f）・前提として届くページなし・古い ABC 9 問
sections:
  - {title: '45 度回転：|Δx|+|Δy| = max(|Δu|, |Δv|) になる理由', anchor: rotate-45}
  - {title: 最遠点対：x+y と x−y の最大・最小（点の更新はセグ木）, anchor: farthest-pair}
  - {title: x と y を独立に扱う：距離の和は軸ごと・中央値・寄与, anchor: axis-independence}
  - {title: 絶対値の外し方：向きを固定して場合分けし、盤面を反転してもう一度, anchor: remove-abs}
  - {title: 盤面の斜め：r+c・r−c で斜めの線に番号を付ける（色の偶奇は parity）, anchor: diagonal-coordinates}
  - {title: 回転後の偶奇：u と v の偶奇がそろう点だけが元の格子点（チェビシェフ → マンハッタンで 1/2 が出る）, anchor: parity-after-rotation, level: 青}
  - {title: ひし形の範囲を正方形にして 2 次元累積和, anchor: diamond-range, level: 黄}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：u = x+y、v = x−y と座標を変える（45 度回転）と、マンハッタン距離はチェビシェフ距離 max(|Δu|, |Δv|) になる。ひし形の範囲が正方形に変わり、最遠点対・距離の和・斜め移動を x と y に分けて解ける。
    - **いつ使うか**：
        - マンハッタン距離が最大の 2 点・ある点から最も遠い点
        - マンハッタン距離の和の最小・全ペアの距離の総和
        - 斜め移動（キングの移動）だけでの距離・斜めにしか動けない駒
        - ひし形の範囲（|x|+|y| ≤ D）にある点の数
        - N ≤ 2×10^5 点の全ペアのマンハッタン距離の和や最大を問い、全組 O(N^2) が間に合わない
        - |x_i − x_j| + |y_i − y_j| や max(|x_i − x_j|, |y_i − y_j|) の最大・和が式に出る
    - **計算量**：（執筆時に書く）
    - **前提**：[ソートで考える](../basics/sorting-techniques.md)、[累積和](../basics/prefix-sum.md)
