---
id: permutation-cycles
title: 置換の巡回分解
aliases: [巡回置換, サイクル分解, 順列のサイクル, swap でソートする最小回数, 置換の位数, cycle decomposition]
type: technique
field: comb
chapter: 置換・分割・木の数え上げ
order: 240
level: 基礎
kind: [数え上げ, 考察]
prerequisites: []
related: [permutation-parity, functional-graph, inversion-number, partition-number#cycle-type, stirling-first, doubling, crt, permutation]
summary: 順列 P を i → P_i の矢印で描くといくつかの巡回に分かれ、任意の 2 要素の swap でソートする最小回数は N − (巡回の個数) になる。K 回の合成は各巡回の上を K 歩進む操作である。
complexity: null
signs:
  - {type: phrase, text: 順列を任意の 2 要素の swap でソートする最小回数}
  - {type: phrase, text: i → P_i をたどる・置換を何回も繰り返す}
  - {type: phrase, text: 元に戻るまでの回数}
  - {type: constraint, text: 置換を K ≤ 10^18 回繰り返した結果を求める}
acl: []
frequency: B
frequency_evidence: recent 0・前提として 4 ページに届く（直接 3）・古い ABC 5 問
sections:
  - {title: 巡回分解の作り方（訪問済みの印を付けてたどる）, anchor: decompose}
  - {title: swap で巡回が割れる・つながる：最小回数は N − 巡回の個数, anchor: min-swaps}
  - {title: 隣接 swap（転倒数）との違い, anchor: vs-adjacent}
  - {title: K 回の合成と元に戻る回数（巡回の長さの lcm）, anchor: power, level: 青}
  - {title: Functional graph との関係, anchor: functional-graph}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：順列 P を i → P_i の矢印で描くといくつかの巡回に分かれ、任意の 2 要素の swap でソートする最小回数は N − (巡回の個数) になる。K 回の合成は各巡回の上を K 歩進む操作である。
    - **いつ使うか**：
        - 順列を任意の 2 要素の swap でソートする最小回数
        - i → P_i をたどる・置換を何回も繰り返す
        - 元に戻るまでの回数
        - 置換を K ≤ 10^18 回繰り返した結果を求める
    - **計算量**：（執筆時に書く）
    - **前提**：なし
