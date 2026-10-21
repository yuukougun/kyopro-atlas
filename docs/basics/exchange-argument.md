---
id: exchange-argument
title: 交換論法と比較関数の設計
aliases: [隣接交換, exchange argument, ソートの比較関数を作る, 連結して最大・最小, a+b と b+a]
type: technique
field: basics
chapter: 貪欲
order: 270
level: 青
kind: [貪欲, ソート・座標圧縮]
prerequisites: [greedy-basics]
related: [exchange-argument-dp, lexicographic-greedy, cpp-comparators, interval-scheduling, tree-ratio-greedy]
summary: 隣り合う 2 つを入れ替えたときに変わる項だけを比べ、「i を先に置くべき条件」を式で導いて比較関数にする。導いた比較が推移的（狭義の弱順序）かを確かめ、その順に並べてから貪欲や DP を行う。
complexity: null
signs:
  - {type: phrase, text: 並べる順番で結果が変わる}
  - {type: phrase, text: 文字列・数を並べて連結した結果を最大（最小）にする}
  - {type: shape, text: 2 つを入れ替えたときの差が、その 2 つだけで決まる}
acl: []
frequency: A
frequency_evidence: recent 2（abc467_f・abc471_f）・前提として 2 ページに届く（直接 2）・古い ABC 4 問
sections:
  - {title: 隣接交換で比較を導く, anchor: adjacent-swap}
  - {title: 比較が狭義の弱順序になっているか, anchor: strict-weak-ordering}
  - {title: 比は掛け算で比べる・分母 0, anchor: ratios}
  - {title: 連結の比較（a+b と b+a）, anchor: concatenation}
  - {title: 順に並べてから DP（DP の章へ）, anchor: then-dp}
  - {title: 入れ替えで改善できるかを考える型, anchor: improve-by-swap}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：隣り合う 2 つを入れ替えたときに変わる項だけを比べ、「i を先に置くべき条件」を式で導いて比較関数にする。導いた比較が推移的（狭義の弱順序）かを確かめ、その順に並べてから貪欲や DP を行う。
    - **いつ使うか**：
        - 並べる順番で結果が変わる
        - 文字列・数を並べて連結した結果を最大（最小）にする
        - 2 つを入れ替えたときの差が、その 2 つだけで決まる
    - **計算量**：（執筆時に書く）
    - **前提**：[貪欲法の考え方と正当性](../basics/greedy-basics.md)
