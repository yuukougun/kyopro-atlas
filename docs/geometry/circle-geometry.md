---
id: circle-geometry
title: 円と幾何の最適化
aliases: [円の交差判定, 2 円の位置関係, 外接円, 円と格子点, 最小包含円, smallest enclosing circle, Welzl, 半径の二分探索, 三分探索で幾何, 候補点の列挙]
type: technique
field: geometry
order: 60
level: 青
kind: [幾何, 二分探索]
prerequisites: [geometry-precision, binary-search-answer]
related: [union-find, ternary-search, integer-root#sqrt-correction, randomized]
summary: 2 円の位置関係は、中心間の距離と半径の和・差を 2 乗して整数のまま判定できる。実数の位置・半径・時刻の最適化は、最適解が少数の点で決まるなら候補を列挙し、判定が単調なら答えで二分探索、凸なら三分探索する。
complexity: null
signs:
  - {type: phrase, text: 円周を伝って移動できるか・円どうしが交わるか}
  - {type: phrase, text: すべての点を含む最小の円}
  - {type: phrase, text: 障害物を避けて通れる円の最大の半径}
  - {type: phrase, text: 円の内部にある格子点の数}
  - {type: constraint, text: N ≤ 50 程度の点で、実数の位置や半径を最適化する}
acl: [dsu]
verify: [minimum_enclosing_circle]
frequency: B
frequency_evidence: recent 0・前提として届くページなし・古い ABC 8 問
sections:
  - {title: 2 円の位置関係（離れる・外接・交わる・内接・内包）を 2 乗した整数で判定, anchor: two-circles}
  - {title: 円と格子点：y ごとに x の範囲を整数で求める, anchor: lattice-points-in-circle}
  - {title: 円のつながりを Union-Find で, anchor: connectivity}
  - {title: 最小包含円：候補は 2 点を直径とする円か 3 点の外接円（Welzl の乱択も）, anchor: min-enclosing-circle}
  - {title: 外心の計算と退化（3 点が一直線上）, anchor: circumcenter}
  - {title: 幾何の最適化の選び方：候補の列挙・答えの二分探索（半径・時刻）・三分探索, anchor: geometry-optimization}
  - {title: 三分探索の注意：凸性の確認・入れ子の三分探索・式の変わり目の時刻を列挙する方法, anchor: ternary-search-caveats, level: 黄}
  - {title: 山登り・焼きなましに頼らない（ABC の幾何の最適化は凸性や候補の列挙で解ける）, anchor: no-heuristics}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：2 円の位置関係は、中心間の距離と半径の和・差を 2 乗して整数のまま判定できる。実数の位置・半径・時刻の最適化は、最適解が少数の点で決まるなら候補を列挙し、判定が単調なら答えで二分探索、凸なら三分探索する。
    - **いつ使うか**：
        - 円周を伝って移動できるか・円どうしが交わるか
        - すべての点を含む最小の円
        - 障害物を避けて通れる円の最大の半径
        - 円の内部にある格子点の数
        - N ≤ 50 程度の点で、実数の位置や半径を最適化する
    - **計算量**：（執筆時に書く）
    - **前提**：[誤差の扱いと整数での処理](../geometry/geometry-precision.md)、[答えで二分探索](../basics/binary-search-answer.md)
