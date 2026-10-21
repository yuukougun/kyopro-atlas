---
id: exchange-argument-dp
title: 並べ替えてから DP する
aliases: [交換論法＋DP, ソートしてから DP, 座布団 DP, 締切つきナップサック]
type: technique
field: dp
chapter: 列の DP
order: 140
level: 青
kind: [DP, 貪欲]
prerequisites: [exchange-argument, knapsack-01]
related: [greedy-basics, subset-sum#sort-then-count, interval-dp]
summary: 選ぶ集合が決まれば最適な順序がソートで決まるとき、先にその順に並べてから「選ぶ・選ばない」の DP をする。並べる基準は、隣り合う 2 つを入れ替えたときの損得の式から作る。
complexity: null
signs:
  - {type: phrase, text: 好きな順番で、いくつか選んで順に処理する}
  - {type: phrase, text: 締切・積み重ね（上に載せられる重さ）がある}
  - {type: phrase, text: 一次関数を好きな順に合成する}
  - {type: phrase, text: 最後の 1 つだけ制限を超えてよい}
acl: []
frequency: B
frequency_evidence: recent 0・前提として届くページなし・古い ABC 4 問
sections:
  - {title: 選ぶ集合と順序を分けて考える, anchor: set-and-order}
  - {title: 比較の基準の作り方（入れ替えの差を i だけの量と j だけの量に分ける）, anchor: comparison-key}
  - {title: 比は割らずに掛け算で比べる, anchor: compare-ratios}
  - {title: 大きい順に左右の端へ置く, anchor: place-at-ends, level: 黄}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：選ぶ集合が決まれば最適な順序がソートで決まるとき、先にその順に並べてから「選ぶ・選ばない」の DP をする。並べる基準は、隣り合う 2 つを入れ替えたときの損得の式から作る。
    - **いつ使うか**：
        - 好きな順番で、いくつか選んで順に処理する
        - 締切・積み重ね（上に載せられる重さ）がある
        - 一次関数を好きな順に合成する
        - 最後の 1 つだけ制限を超えてよい
    - **計算量**：（執筆時に書く）
    - **前提**：[交換論法と比較関数の設計](../basics/exchange-argument.md)、[ナップサック DP](../dp/knapsack-01.md)
