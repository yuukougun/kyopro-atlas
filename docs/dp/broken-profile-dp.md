---
id: broken-profile-dp
title: プロファイル DP
aliases: [Broken Profile DP, 插頭 DP, フロンティア法, 連結性 DP, スライド bitDP, 敷き詰めの DP]
type: technique
field: dp
chapter: 状態の形で分かれる DP
order: 240
level: 黄
kind: [DP, ビット演算]
prerequisites: [bit-dp]
related: [matrix-power#profile-dp, dp-grid, grid#tiling]
summary: 幅の小さいグリッドを 1 マスずつ進め、まだ処理していない部分に影響する境界の情報だけを bit で持って、敷き詰め方や塗り方を数える。取り得る状態だけに圧縮すると状態がさらに減る。
complexity: null
signs:
  - {type: constraint, text: グリッドの短い辺 ≤ 6〜14}
  - {type: phrase, text: タイル・ドミノの敷き詰め方の数}
  - {type: phrase, text: 隣り合わないように置く・隣と異なる色で塗る方法の数}
  - {type: phrase, text: 黒マスが連結になる塗り方}
acl: []
frequency: B
frequency_evidence: recent 0・前提として届くページなし・古い ABC 4 問
sections:
  - {title: 1 行ずつ進める（行の配置パターンを状態に）, anchor: row-by-row}
  - {title: 1 マスずつ進める（境界の折れ線を状態に）, anchor: cell-by-cell}
  - {title: 取り得る状態だけを列挙して番号を付ける（圧縮）, anchor: compress}
  - {title: 長さが巨大なら行列累乗と組み合わせる, anchor: with-matrix-power}
  - {title: 連結性を持つ（フロンティア法）, anchor: connectivity, level: 発展}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：幅の小さいグリッドを 1 マスずつ進め、まだ処理していない部分に影響する境界の情報だけを bit で持って、敷き詰め方や塗り方を数える。取り得る状態だけに圧縮すると状態がさらに減る。
    - **いつ使うか**：
        - グリッドの短い辺 ≤ 6〜14
        - タイル・ドミノの敷き詰め方の数
        - 隣り合わないように置く・隣と異なる色で塗る方法の数
        - 黒マスが連結になる塗り方
    - **計算量**：（執筆時に書く）
    - **前提**：[bitDP](../dp/bit-dp.md)
