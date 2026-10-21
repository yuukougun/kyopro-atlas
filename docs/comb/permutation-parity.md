---
id: permutation-parity
title: 置換の偶奇
aliases: [偶置換, 奇置換, 置換の符号, swap の回数の偶奇, 3 要素の巡回, sign of a permutation]
type: technique
field: comb
chapter: 置換・分割・木の数え上げ
order: 250
level: 青
kind: [数え上げ, 考察]
prerequisites: [permutation-cycles, parity]
related: [inversion-number, invariant, multinomial-coefficient, game-basics#move-parity]
summary: 同じ置換をどんな swap の列で作っても swap の回数の偶奇は変わらない（置換の符号）。ちょうど K 回の swap や 3 要素の巡回だけで作れる列は偶奇で決まり、同じ値があれば偶奇を調整できる。
complexity: null
signs:
  - {type: phrase, text: ちょうど K 回（10^100 回など）の swap の後にありうる列}
  - {type: phrase, text: 3 つの要素を巡回させる操作しかできない}
  - {type: phrase, text: 2 つの列でそれぞれ 1 回ずつの swap を同時に行う}
  - {type: phrase, text: 同じ値があるかどうかで答えが変わる}
acl: []
frequency: B
frequency_evidence: recent 1（abc470_f）・前提として届くページなし・古い ABC 1 問
sections:
  - {title: 置換の符号：swap の回数の偶奇は列によらない, anchor: sign}
  - {title: 巡回の個数・転倒数から偶奇を求める, anchor: compute}
  - {title: 3 要素の巡回は偶置換, anchor: three-cycle}
  - {title: 同じ値があれば偶奇を調整できる, anchor: duplicates}
  - {title: ちょうど K 回の操作で作れるもの, anchor: exactly-k}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：同じ置換をどんな swap の列で作っても swap の回数の偶奇は変わらない（置換の符号）。ちょうど K 回の swap や 3 要素の巡回だけで作れる列は偶奇で決まり、同じ値があれば偶奇を調整できる。
    - **いつ使うか**：
        - ちょうど K 回（10^100 回など）の swap の後にありうる列
        - 3 つの要素を巡回させる操作しかできない
        - 2 つの列でそれぞれ 1 回ずつの swap を同時に行う
        - 同じ値があるかどうかで答えが変わる
    - **計算量**：（執筆時に書く）
    - **前提**：[置換の巡回分解](../comb/permutation-cycles.md)、[偶奇に着目する](../thinking/parity.md)
