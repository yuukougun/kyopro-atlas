---
id: burnside-lemma
title: Burnside の補題
aliases: [Pólya の数え上げ定理, ネックレス, 数珠順列, 回転で同一視して数える, Burnside's lemma]
type: overview
field: comb
chapter: 数え方の考え方
order: 110
level: 発展
kind: [数え上げ]
prerequisites: [counting-dedup]
related: [divisor-inclusion-exclusion, euler-phi, gcd-lcm]
summary: 回転・反転などで同一視したときの異なるものの数を、各操作で動かないものの数の平均として求める。重複度が対象ごとに違って単純に割れないときに使い、回転だけの数珠は (1/n) Σ_{d|n} φ(d) k^(n/d) になる。
complexity: null
signs:
  - {type: phrase, text: 回転（反転）して一致するものは同じとみなす}
  - {type: phrase, text: 数珠・ネックレスの塗り方の数}
  - {type: phrase, text: 立方体の面の塗り方（書き込み方）の数}
acl: []
frequency: C
frequency_evidence: recent 0・前提として届くページなし・古い ABC 2 問
sections:
  - {title: 何ができるか（同一視したものの数 = 動かないものの数の平均）, anchor: what}
  - {title: なぜ単純に操作の数で割れないか, anchor: why-not-divide}
  - {title: 数珠（回転のみ）の式, anchor: necklace}
  - {title: 最短周期で分類して割る方法（約数包除の形）, anchor: by-period}
  - {title: 立方体の 24 通りの回転, anchor: cube}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：回転・反転などで同一視したときの異なるものの数を、各操作で動かないものの数の平均として求める。重複度が対象ごとに違って単純に割れないときに使い、回転だけの数珠は (1/n) Σ_{d|n} φ(d) k^(n/d) になる。
    - **いつ使うか**：
        - 回転（反転）して一致するものは同じとみなす
        - 数珠・ネックレスの塗り方の数
        - 立方体の面の塗り方（書き込み方）の数
    - **計算量**：（執筆時に書く）
    - **前提**：[重複の除き方](../comb/counting-dedup.md)
