---
id: multinomial-coefficient
title: 多項係数
aliases: [同じものを含む順列, 並べ替えの数, グループ分けの数, 多項定理, multinomial coefficient]
type: technique
field: comb
chapter: 二項係数の系統
order: 120
level: 水
kind: [数え上げ]
prerequisites: [binomial-precompute]
related: [stars-and-bars, counting-dedup, permutation-parity, cayley-pruefer, insertion-dp]
summary: 種類ごとの個数が a_1, …, a_m の並べ方は (Σa_i)!/(a_1! … a_m!) 通りで、全部を区別した並べ方を同じ種類の入れ替えで割って得る。大きさを指定したグループ分けも同じ式で数える。
complexity: null
signs:
  - {type: phrase, text: 文字を並べ替えてできる文字列の個数}
  - {type: phrase, text: 各種類を使う個数が決まっている並べ方}
  - {type: phrase, text: 大きさを指定してグループに分ける方法の数}
acl: []
frequency: B
frequency_evidence: recent 1（abc470_f）・前提として 1 ページに届く（直接 1）・古い ABC 2 問
sections:
  - {title: 式の意味（全部区別した n! を入れ替えで割る）, anchor: meaning}
  - {title: 二項係数の積として順に場所を決める, anchor: product-of-binomials}
  - {title: DP で個数を決めながら合流ごとに二項係数を掛ける, anchor: dp-merge}
  - {title: 一部を先に並べて残りを挿入する, anchor: insert-rest, level: 黄}
  - {title: 区別しない同じ大きさのグループを割る, anchor: same-size-groups, level: 黄}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：種類ごとの個数が a_1, …, a_m の並べ方は (Σa_i)!/(a_1! … a_m!) 通りで、全部を区別した並べ方を同じ種類の入れ替えで割って得る。大きさを指定したグループ分けも同じ式で数える。
    - **いつ使うか**：
        - 文字を並べ替えてできる文字列の個数
        - 各種類を使う個数が決まっている並べ方
        - 大きさを指定してグループに分ける方法の数
    - **計算量**：（執筆時に書く）
    - **前提**：[二項係数の前計算](../comb/binomial-precompute.md)
