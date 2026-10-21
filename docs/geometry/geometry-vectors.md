---
id: geometry-vectors
title: ベクトルと外積
aliases: [外積, 内積, cross product, ccw, 向き判定, 符号付き面積, 多角形の面積, 靴紐公式, shoelace formula, 線分の交差判定, 点と直線の距離, 3 次元の基本, 直方体の共通部分]
type: technique
field: geometry
order: 10
level: 基礎
kind: [幾何]
prerequisites: []
related: [geometry-precision, argument-sort, convex-hull, prefix-sum, two-pointers]
summary: 外積 a.x·b.y − a.y·b.x の符号で向き（左・右・一直線上）が、絶対値で平行四辺形の面積が分かる。3 点の一直線判定・凸性・多角形の面積・線分の交差を、整数のまま誤差なく判定できる。
complexity: null
signs:
  - {type: phrase, text: 3 点が一直線上にあるか・三角形ができるか}
  - {type: phrase, text: 左に曲がるか右に曲がるか・四角形が凸か}
  - {type: phrase, text: 頂点が順に与えられた多角形の面積}
  - {type: phrase, text: 2 本の線分が交わるか・多角形を線分で切って分かれる個数}
  - {type: phrase, text: 直方体どうしの共通部分の体積}
  - {type: constraint, text: '座標が整数で |x|, |y| ≤ 10^9（外積は long long にぎりぎり収まる）'}
  - {type: shape, text: (x2 − x1)(y3 − y1) − (y2 − y1)(x3 − x1) の符号で場合を分ける}
acl: []
verify: []
frequency: A
frequency_evidence: recent 2（abc467_d・abc472_f）・前提として 7 ページに届く（直接 4）・古い ABC 7 問
sections:
  - {title: 外積と内積の意味（符号と大きさ）, anchor: cross-and-dot}
  - {title: ccw：3 点の回り方・一直線上の判定・凸性の判定, anchor: ccw}
  - {title: オーバーフローの見積もり（座標 10^9 で外積は 8×10^18、さらに足すなら __int128）, anchor: overflow}
  - {title: 三角形・多角形の面積：座標の公式（面積の 2 倍を整数のまま扱う）, anchor: polygon-area, level: 水}
  - {title: 線分の交差判定（端点で接する・同一直線上の場合）と点と直線の距離, anchor: segment-intersection, level: 水}
  - {title: 3 次元の基本：軸に平行な直方体の共通部分は軸ごとの区間の積, anchor: 3d-geometry}
  - {title: '点の表し方：整数の構造体と std::complex', anchor: point-representation}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：外積 a.x·b.y − a.y·b.x の符号で向き（左・右・一直線上）が、絶対値で平行四辺形の面積が分かる。3 点の一直線判定・凸性・多角形の面積・線分の交差を、整数のまま誤差なく判定できる。
    - **いつ使うか**：
        - 3 点が一直線上にあるか・三角形ができるか
        - 左に曲がるか右に曲がるか・四角形が凸か
        - 頂点が順に与えられた多角形の面積
        - 2 本の線分が交わるか・多角形を線分で切って分かれる個数
        - 直方体どうしの共通部分の体積
        - 座標が整数で |x|, |y| ≤ 10^9（外積は long long にぎりぎり収まる）
        - (x2 − x1)(y3 − y1) − (y2 − y1)(x3 − x1) の符号で場合を分ける
    - **計算量**：（執筆時に書く）
    - **前提**：なし
