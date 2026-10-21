---
id: sorting-techniques
title: ソートで考える
aliases: [ソート, 安定ソート, ペアのソート, sorting]
type: technique
field: basics
chapter: ソートと二分探索
order: 70
level: 基礎
kind: [ソート・座標圧縮, 貪欲]
prerequisites: []
related: [exchange-argument, greedy-basics, cpp-comparators, cpp-algorithms]
summary: 並べ替えてよい問題では、ソートすると貪欲の順番が決まり、二分探索や尺取りが使えるようになる。比較関数は狭義の弱順序（<= を書かない）にし、比率は掛け算で比べる。
complexity: null
signs:
  - {type: phrase, text: 順番を自由に並べ替えてよい}
  - {type: phrase, text: 安い順・効果の大きい順に取る}
  - {type: phrase, text: 2 つの集合を 1 対 1 に対応させて距離の和を最小化する}
  - {type: phrase, text: 成功率などの比率の大小で並べる}
acl: []
frequency: A
frequency_evidence: recent 2（abc457_e・abc474_e）・前提として 58 ページに届く（直接 9）・古い ABC 3 問
sections:
  - {title: ソートで貪欲の順が決まる, anchor: greedy-order}
  - {title: 2 つの列を 1 対 1 に対応させる（両方ソートして順に組む）, anchor: matching-two-lists}
  - {title: 比較関数の要件（狭義の弱順序）, anchor: strict-weak-ordering}
  - {title: 比率は掛け算で比べる・同点の順序（stable_sort）, anchor: ratio-and-ties}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：並べ替えてよい問題では、ソートすると貪欲の順番が決まり、二分探索や尺取りが使えるようになる。比較関数は狭義の弱順序（<= を書かない）にし、比率は掛け算で比べる。
    - **いつ使うか**：
        - 順番を自由に並べ替えてよい
        - 安い順・効果の大きい順に取る
        - 2 つの集合を 1 対 1 に対応させて距離の和を最小化する
        - 成功率などの比率の大小で並べる
    - **計算量**：（執筆時に書く）
    - **前提**：なし
