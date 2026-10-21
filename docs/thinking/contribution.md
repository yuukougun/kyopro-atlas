---
id: contribution
title: 主客転倒・寄与
aliases: [主客転倒, 寄与, 貢献度, contribution technique, 足された回数, 各要素が何回数えられるか]
type: thinking
field: thinking
order: 30
level: 水
kind: [考察, 数え上げ]
prerequisites: []
related: [sigma-manipulation#swap-order, counting-mindset#contribution-with-binomial, linearity-of-expectation, bitwise-independence#per-bit-contribution, monotonic-stack#contribution, fenwick-tree]
summary: 全ペア・全区間・全部分集合についての総和を、「各要素が何回数えられるか × 値」の和に入れ替えて求める。各要素が最大・最小になる回数や各桁が現れる回数を数えれば、対象を 1 つずつ列挙しなくて済む。
complexity: null
signs:
  - {type: phrase, text: すべての組・区間・部分集合についての総和}
  - {type: phrase, text: 各要素が答えに何回足されるか}
  - {type: phrase, text: 全区間の最小値（2 番目に大きい値）の和}
  - {type: constraint, text: N ≤ 2×10^5 で、組・区間は N^2 個あり列挙できない}
acl: []
frequency: A
frequency_evidence: recent 5（abc455_f・abc461_e・abc468_e・abc470_g・abc471_g）・前提として 2 ページに届く（直接 2）・古い ABC 6 問
sections:
  - {title: 数える対象を入れ替える（表の行と列。式の規則は Σ の変形のページ）, anchor: swap-roles}
  - {title: ソートで符号を決める（全ペアの差）, anchor: sort-signs}
  - {title: 各桁・各約数の寄与, anchor: digits-divisors}
  - {title: 各要素が最大・最小になる回数（同じ値の扱い）, anchor: max-min-count}
  - {title: 数え上げ・期待値での使い方（数え上げの章へ）, anchor: counting}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：全ペア・全区間・全部分集合についての総和を、「各要素が何回数えられるか × 値」の和に入れ替えて求める。各要素が最大・最小になる回数や各桁が現れる回数を数えれば、対象を 1 つずつ列挙しなくて済む。
    - **いつ使うか**：
        - すべての組・区間・部分集合についての総和
        - 各要素が答えに何回足されるか
        - 全区間の最小値（2 番目に大きい値）の和
        - N ≤ 2×10^5 で、組・区間は N^2 個あり列挙できない
    - **計算量**：（執筆時に書く）
    - **前提**：なし
