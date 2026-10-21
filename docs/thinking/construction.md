---
id: construction
title: 構築問題の考え方
aliases: [構築, constructive, 1 つ出力せよ, 上界と下界, 必要条件と十分性, constructive algorithms]
type: thinking
field: thinking
order: 80
level: 基礎
kind: [考察]
prerequisites: []
related: [thinking-checklist#shape-construct, invariant, graph-construction, tree-construction, stress-testing]
summary: 条件を満たすものを 1 つ作る問題は、小さい N で手で作って規則を見つけ、不可能な場合の必要条件を先に挙げてから一般化する。最大値を求める問題では、上界を示してそれを達成する例を作る。
complexity: null
signs:
  - {type: phrase, text: 条件を満たすものを 1 つ出力せよ（存在しなければ −1）}
  - {type: phrase, text: 操作手順を出力せよ（回数の上限が与えられている）}
  - {type: phrase, text: 最大値を求めるが、答えに自然な上限がありそう}
acl: []
frequency: A
frequency_evidence: recent 4（abc453_f・abc454_e・abc474_d・abc474_g）・前提として届くページなし・古い ABC 5 問
sections:
  - {title: 小さい N で作って規則を一般化する, anchor: small-cases}
  - {title: 必要条件を先に挙げる, anchor: necessary-conditions}
  - {title: 上界・下界を示して達成する例を作る, anchor: bound-and-construct}
  - {title: 出力を検査するプログラムで確かめる, anchor: checker}
  - {title: ABC の構築の型（手順・数列・グラフ）, anchor: abc-patterns, level: 水}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：条件を満たすものを 1 つ作る問題は、小さい N で手で作って規則を見つけ、不可能な場合の必要条件を先に挙げてから一般化する。最大値を求める問題では、上界を示してそれを達成する例を作る。
    - **いつ使うか**：
        - 条件を満たすものを 1 つ出力せよ（存在しなければ −1）
        - 操作手順を出力せよ（回数の上限が与えられている）
        - 最大値を求めるが、答えに自然な上限がありそう
    - **計算量**：（執筆時に書く）
    - **前提**：なし
