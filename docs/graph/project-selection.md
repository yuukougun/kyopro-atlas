---
id: project-selection
title: 燃やす埋める
aliases: [Project Selection, 最大重み閉包, 劣モジュラ, project selection problem]
type: technique
field: graph
chapter: フロー・マッチング
order: 410
level: 黄
kind: [フロー・マッチング]
prerequisites: [min-cut]
related: [konig-theorem, two-sat, bipartite-graph]
summary: 各要素を選ぶか選ばないかの 2 択とその組合せのコストを辺に直し、最小カットで最適な選び方を求める。利得は定数を足してコストに読み替え、二部グラフなら片側の意味を反転する。
complexity: null
signs:
  - {type: phrase, text: 各要素を選ぶ・選ばないの 2 択で、利得とコストの合計を最大化する}
  - {type: phrase, text: A を選ぶなら B も選ぶ必要がある（依存関係）}
  - {type: phrase, text: 隣どうしが違う（同じ）とペナルティ・利得}
  - {type: constraint, text: 要素の数 N が 100〜数百程度で、選び方は 2^N 通りある}
  - {type: shape, text: 目的関数が、0/1 変数ごとの項と「x_i = 1 かつ x_j = 0 ならコスト c」の項の和で書ける}
acl: [mf_graph]
frequency: B
frequency_evidence: recent 1（abc472_g）・前提として届くページなし・古い ABC 6 問
sections:
  - {title: 条件から辺への早見表, anchor: cheatsheet}
  - {title: 利得はコストに読み替えて定数を足す, anchor: gains}
  - {title: 最大重み閉包（依存関係）, anchor: closure}
  - {title: 表せる項と表せない項（劣モジュラ）, anchor: submodular}
  - {title: 二部グラフで片側の意味を反転する, anchor: flip-side}
  - {title: 多値変数を頂点の列で表す, anchor: multi-valued, level: 発展}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：各要素を選ぶか選ばないかの 2 択とその組合せのコストを辺に直し、最小カットで最適な選び方を求める。利得は定数を足してコストに読み替え、二部グラフなら片側の意味を反転する。
    - **いつ使うか**：
        - 各要素を選ぶ・選ばないの 2 択で、利得とコストの合計を最大化する
        - A を選ぶなら B も選ぶ必要がある（依存関係）
        - 隣どうしが違う（同じ）とペナルティ・利得
        - 要素の数 N が 100〜数百程度で、選び方は 2^N 通りある
        - 目的関数が、0/1 変数ごとの項と「x_i = 1 かつ x_j = 0 ならコスト c」の項の和で書ける
    - **計算量**：（執筆時に書く）
    - **前提**：[最小カット](../graph/min-cut.md)
