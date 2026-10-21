---
id: reflection-principle
title: 鏡像法とカタラン数
aliases: [鏡像法, 反射原理, カタラン数, ballot 数, Dyck path, 正しい括弧列の個数, reflection principle, Catalan number]
type: technique
field: comb
chapter: 二項係数の系統
order: 150
level: 黄
kind: [数え上げ]
prerequisites: [lattice-paths]
related: [counting-bijection, binomial-identities, bracket-sequence, dp-state-design]
summary: 境界を越える格子路を、最初に境界に触れた点から先を折り返して別の終点への経路と 1 対 1 に対応させ、全体から引いて数える。対角線を越えない経路の数がカタラン数 C(2n,n)/(n+1) で、正しい括弧列の個数に等しい。
complexity: null
signs:
  - {type: phrase, text: どの接頭辞でも A の個数が B の個数（+K）以上}
  - {type: phrase, text: 途中で負にならない ±1 の列の個数}
  - {type: phrase, text: 正しい括弧列の個数}
  - {type: phrase, text: 境界線を越えない経路の数}
acl: []
frequency: C
frequency_evidence: recent 0・前提として届くページなし・古い ABC 2 問
sections:
  - {title: 折り返しの全単射（最初に触れた点から先を折り返す）, anchor: reflection}
  - {title: 越えない経路 = 全体 − 越える経路, anchor: complement-count}
  - {title: カタラン数と括弧列・二分木, anchor: catalan}
  - {title: 折り返す線のずれ（+1）と条件を満たせないときの 0, anchor: offset}
  - {title: 括弧列を DP で数えるときとの使い分け, anchor: vs-dp}
  - {title: 両端を越えない場合, anchor: two-sided, level: 発展}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：境界を越える格子路を、最初に境界に触れた点から先を折り返して別の終点への経路と 1 対 1 に対応させ、全体から引いて数える。対角線を越えない経路の数がカタラン数 C(2n,n)/(n+1) で、正しい括弧列の個数に等しい。
    - **いつ使うか**：
        - どの接頭辞でも A の個数が B の個数（+K）以上
        - 途中で負にならない ±1 の列の個数
        - 正しい括弧列の個数
        - 境界線を越えない経路の数
    - **計算量**：（執筆時に書く）
    - **前提**：[格子路の数え上げ](../comb/lattice-paths.md)
