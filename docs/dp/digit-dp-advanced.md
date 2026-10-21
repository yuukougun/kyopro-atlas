---
id: digit-dp-advanced
title: 桁 DP の応用
aliases: [繰り上がりの DP, 上限と下限の桁 DP, 複数の数の桁 DP]
type: technique
field: dp
chapter: 状態の形で分かれる DP
order: 260
level: 黄
kind: [DP, 数え上げ]
prerequisites: [digit-dp]
related: [memoized-recursion, bit-dp, dp-mod-state]
summary: 桁 DP を、2 つ以上の数を同時に決める・下の桁からの繰り上がりを状態にする・種類の少ない状態を map や bit で持つ、などに広げる。上限と下限の両方があるときはフラグを 2 つ持つ。
complexity: null
signs:
  - {type: phrase, text: 2 つ以上の数を同時に決める（a + b = a xor b・3 つの数の xor）}
  - {type: phrase, text: 支払いとお釣りの枚数の最小}
  - {type: phrase, text: 使った数字の種類数・指定の数字を全部含む数}
  - {type: phrase, text: L ≤ x ≤ y ≤ R の組を数える（上限と下限の両方）}
acl: []
frequency: B
frequency_evidence: recent 1（abc466_g）・前提として届くページなし・古い ABC 8 問
sections:
  - {title: 複数の数を同時に決める（フラグを並べる）, anchor: multiple-numbers}
  - {title: 上限と下限の両方（2 つのフラグ）, anchor: lower-and-upper}
  - {title: 下の桁からの繰り上がりを状態にする, anchor: carry}
  - {title: 状態の種類が少ないことを使う（桁の積を map で・数字の集合を bit で）, anchor: sparse-states}
  - {title: 個数と総和を同時に持つ（総和 += 個数×桁の値）, anchor: count-and-sum}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：桁 DP を、2 つ以上の数を同時に決める・下の桁からの繰り上がりを状態にする・種類の少ない状態を map や bit で持つ、などに広げる。上限と下限の両方があるときはフラグを 2 つ持つ。
    - **いつ使うか**：
        - 2 つ以上の数を同時に決める（a + b = a xor b・3 つの数の xor）
        - 支払いとお釣りの枚数の最小
        - 使った数字の種類数・指定の数字を全部含む数
        - L ≤ x ≤ y ≤ R の組を数える（上限と下限の両方）
    - **計算量**：（執筆時に書く）
    - **前提**：[桁 DP](../dp/digit-dp.md)
