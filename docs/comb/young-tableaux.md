---
id: young-tableaux
title: Young 図形とフック長公式
aliases: [ヤング図形, 標準タブロー, フック長公式, Robinson-Schensted 対応, Young tableau, hook length formula]
type: overview
field: comb
chapter: 置換・分割・木の数え上げ
order: 290
level: 発展
kind: [数え上げ]
prerequisites: [partition-number]
related: [lis]
summary: 1〜N を Young 図形に行・列とも増加するように書き込む方法の数を、フック長公式 N!/Π(フック長) で求める。Robinson-Schensted 対応で、順列の LIS・LDS の長さの条件を図形の形の条件に言い換えられる。
complexity: null
signs:
  - {type: phrase, text: 最長増加部分列と最長減少部分列の長さが指定された順列の個数}
acl: []
frequency: C
frequency_evidence: recent 0・前提として届くページなし・古い ABC 1 問
sections:
  - {title: 何ができるか, anchor: what}
  - {title: フック長公式, anchor: hook-length}
  - {title: Robinson-Schensted 対応と LIS・LDS, anchor: robinson-schensted}
  - {title: 分割数との関係, anchor: partitions}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：1〜N を Young 図形に行・列とも増加するように書き込む方法の数を、フック長公式 N!/Π(フック長) で求める。Robinson-Schensted 対応で、順列の LIS・LDS の長さの条件を図形の形の条件に言い換えられる。
    - **いつ使うか**：最長増加部分列と最長減少部分列の長さが指定された順列の個数
    - **計算量**：（執筆時に書く）
    - **前提**：[整数の分割と分割数](../comb/partition-number.md)
