---
id: interactive
title: インタラクティブ問題
aliases: [対話型, インタラクティブ, ジャッジとの対話, 質問回数, インタラクティブの二分探索, interactive problem]
type: technique
field: misc
order: 10
level: 基礎
kind: [二分探索, 実装・C++]
prerequisites: [binary-search]
related: [cpp-io#flush, game-basics#interactive, crt, tree-diameter#double-sweep, dfs, stress-testing#interactive]
summary: 質問を出力してジャッジの答えを受け取る形式の問題で、質問回数の上限から方針を逆算する（2 択の質問なら ⌈log2 候補数⌉ 回）。出力のたびに flush し、二分探索や 2 進表記で質問を設計する。
complexity: null
signs:
  - {type: phrase, text: 問題文に「インタラクティブ」「質問は Q 回まで」とある}
  - {type: phrase, text: 質問の答えが入力として返ってくる・入出力例が対話の形}
  - {type: constraint, text: 質問回数の上限が 20 回など log2 N 程度}
acl: []
frequency: B
frequency_evidence: recent 0・前提として届くページなし・古い ABC 9 問
sections:
  - {title: 形式と C++ の作法（出力のたびに flush・cin.tie(nullptr) を書いたとき）, anchor: format}
  - {title: 回数の上限から方針を逆算する（情報量の下界）, anchor: query-budget}
  - {title: 二分探索で候補を半分ずつ減らす, anchor: binary-search}
  - {title: 2 進表記で質問を設計する, anchor: binary-encoding}
  - {title: 未知のグラフを探索する（DFS の行きと帰り）, anchor: explore-graph, level: 水}
  - {title: 連立方程式・中国剰余定理で特定する, anchor: equations-crt, level: 青}
  - {title: 先に構造を出力してから答える, anchor: output-structure-first, level: 青}
  - {title: 適応的ジャッジ（最悪の場合の回数で考える）, anchor: adaptive-judge}
  - {title: 手元でのテスト（ジャッジ役のプログラムとパイプでつなぐ）, anchor: local-testing}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：質問を出力してジャッジの答えを受け取る形式の問題で、質問回数の上限から方針を逆算する（2 択の質問なら ⌈log2 候補数⌉ 回）。出力のたびに flush し、二分探索や 2 進表記で質問を設計する。
    - **いつ使うか**：
        - 問題文に「インタラクティブ」「質問は Q 回まで」とある
        - 質問の答えが入力として返ってくる・入出力例が対話の形
        - 質問回数の上限が 20 回など log2 N 程度
    - **計算量**：（執筆時に書く）
    - **前提**：[二分探索](../basics/binary-search.md)
