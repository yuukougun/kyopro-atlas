---
id: reformulation
title: 言い換えの典型
aliases: [言い換え, 式変形, 条件の言い換え, 独立に分解, x と y を分ける, 変数変換, reformulation]
type: thinking
field: thinking
order: 10
level: 水
kind: [考察]
prerequisites: []
related: [thinking-checklist#q-rephrase, prefix-sum-counting, fractional-binary-search, difference-sequence, bitwise-independence, manhattan-chebyshev#axis-independence, inversion-number]
summary: 条件や目的関数を、数えやすい・判定しやすい形に書き直す。区間和が M の倍数 ⇔ 累積和の余りが等しい、平均 ≥ x ⇔ Σ(a − x) ≥ 0 のように、手法に結びつく言い換えの型を表で引ける。
complexity: null
signs:
  - {type: phrase, text: 条件が複雑で直接は数えにくい・判定しにくい}
  - {type: phrase, text: x 方向と y 方向・bit ごと・連結成分ごとに結果が独立に決まる}
  - {type: shape, text: 式を変形すると i の項と j の項に分離できる}
acl: []
frequency: A
frequency_evidence: recent 7（abc454_f・abc459_f・abc466_e・abc470_g・abc475_e・abc479_fほか）・前提として届くページなし・古い ABC 4 問
sections:
  - {title: 言い換えの一覧表（元の条件 → 言い換え → 使う手法のページ）, anchor: table}
  - {title: i と j を分離する（a_i − i などの変数変換）, anchor: separate-indices}
  - {title: 独立に分解する（x と y・bit ごと・連結成分ごと）, anchor: independence}
  - {title: 操作の言い換え（区間操作を差分列で・隣接 swap を転倒数で）, anchor: operations}
  - {title: 言い換えてからデータ構造に載せる, anchor: then-data-structure, level: 青}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：条件や目的関数を、数えやすい・判定しやすい形に書き直す。区間和が M の倍数 ⇔ 累積和の余りが等しい、平均 ≥ x ⇔ Σ(a − x) ≥ 0 のように、手法に結びつく言い換えの型を表で引ける。
    - **いつ使うか**：
        - 条件が複雑で直接は数えにくい・判定しにくい
        - x 方向と y 方向・bit ごと・連結成分ごとに結果が独立に決まる
        - 式を変形すると i の項と j の項に分離できる
    - **計算量**：（執筆時に書く）
    - **前提**：なし
