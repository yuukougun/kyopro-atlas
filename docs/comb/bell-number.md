---
id: bell-number
title: 第 2 種スターリング数とベル数
aliases: [集合の分割の数, 第 2 種スターリング数, ベル数, 'S(n,k)', B_n, Stirling numbers of the second kind, Bell number]
type: technique
field: comb
chapter: 置換・分割・木の数え上げ
order: 270
level: 青
kind: [数え上げ, DP]
prerequisites: [binomial-coefficient, dp-basics]
related: [twelvefold-way, recursive-enumeration, inclusion-exclusion#surjection, partition-number, stirling-first, subset-enumeration-dp]
summary: 区別できる n 個を区別しない k 個の空でない組に分ける数が S(n,k)、組の数を問わない総数がベル数 B_n である。最後の要素で場合分けした漸化式で求め、B_12 ≈ 4.2×10^6 から全列挙の可否を見積もる。
complexity: null
signs:
  - {type: constraint, text: N ≤ 10〜12 で、グループ分けを全部試す}
  - {type: phrase, text: N 人を区別しない K 組に分ける（どの組も空でない）方法の数}
acl: []
frequency: C
frequency_evidence: recent 0・前提として届くページなし・古い ABC 2 問
sections:
  - {title: 'S(n,k) の漸化式（最後の要素が新しい組を作るか既存の組に入るか）', anchor: recurrence}
  - {title: ベル数と全列挙の個数の見積もり（B_10 = 115975、B_12 = 4213597）, anchor: size}
  - {title: bitDP・3^N の部分集合 DP との使い分け, anchor: vs-subset-dp}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：区別できる n 個を区別しない k 個の空でない組に分ける数が S(n,k)、組の数を問わない総数がベル数 B_n である。最後の要素で場合分けした漸化式で求め、B_12 ≈ 4.2×10^6 から全列挙の可否を見積もる。
    - **いつ使うか**：
        - N ≤ 10〜12 で、グループ分けを全部試す
        - N 人を区別しない K 組に分ける（どの組も空でない）方法の数
    - **計算量**：（執筆時に書く）
    - **前提**：[二項係数の意味と性質](../comb/binomial-coefficient.md)、[DP の基本](../dp/dp-basics.md)
