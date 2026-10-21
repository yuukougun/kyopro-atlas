---
id: median-absolute
title: 絶対値の和の最小化と中央値
aliases: [中央値で絶対値最小, Σ|x − a_i|, マンハッタン距離の和の最小]
type: technique
field: basics
chapter: 凸と三分探索
order: 230
level: 基礎
kind: [ソート・座標圧縮, 考察]
prerequisites: [sorting-techniques]
related: [ternary-search, fractional-binary-search, manhattan-chebyshev#axis-independence, top-k-multiset#median, slope-trick]
summary: Σ|x − a_i| は中央値で最小になる（x を動かしたときの傾きが「左の点の数 − 右の点の数」になるため）。マンハッタン距離の和は x と y に分けてそれぞれ中央値を取る。
complexity: null
signs:
  - {type: phrase, text: Σ|x − a_i| を最小化する}
  - {type: phrase, text: マンハッタン距離の和が最小になる点}
  - {type: phrase, text: 全員を 1 か所に集める移動の和}
acl: []
frequency: B
frequency_evidence: 古い ABC で繰り返し出た定番（最近30回の出現は0。手で B にした）
sections:
  - {title: なぜ中央値か（傾きの変化）, anchor: why-median}
  - {title: 偶数個のとき（中央の 2 つの間ならどこでもよい）, anchor: even-count}
  - {title: 変数変換で帰着する（a_i − i）, anchor: change-variables}
  - {title: x と y に分ける, anchor: separate-axes}
  - {title: 距離の和で判定して二分探索する, anchor: with-binary-search, level: 青}
  - {title: 二乗和の最小（平均）との違い, anchor: vs-squares}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：Σ|x − a_i| は中央値で最小になる（x を動かしたときの傾きが「左の点の数 − 右の点の数」になるため）。マンハッタン距離の和は x と y に分けてそれぞれ中央値を取る。
    - **いつ使うか**：
        - Σ|x − a_i| を最小化する
        - マンハッタン距離の和が最小になる点
        - 全員を 1 か所に集める移動の和
    - **計算量**：（執筆時に書く）
    - **前提**：[ソートで考える](../basics/sorting-techniques.md)
