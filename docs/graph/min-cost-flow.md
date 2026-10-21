---
id: min-cost-flow
title: 最小費用流
aliases: [primal-dual, 重み付きマッチング, 割当問題, ハンガリアン法, slope, minimum cost flow]
type: technique
field: graph
chapter: フロー・マッチング
order: 440
level: 黄
kind: [フロー・マッチング]
prerequisites: [max-flow, dijkstra]
related: [bipartite-matching, konig-theorem]
summary: 流量 F を流すときのコストの最小値を、残余グラフ上のコストの最短路に沿って流すことをくり返して求める。逆辺の負のコストはポテンシャルで消してダイクストラを使い、ACL の mcf_graph で書ける。
complexity: null
signs:
  - {type: phrase, text: K 個選んだときの最大（最小）を K ごとに答える}
  - {type: phrase, text: 重み付きの割当・各行・各列から高々 K 個}
  - {type: phrase, text: 流す量とコストの両方を最適化する}
  - {type: constraint, text: N ≤ 数百、M ≤ 数千程度で、流す量 K ≤ N}
acl: [mcf_graph]
verify: [min_cost_b_flow, assignment]
frequency: B
frequency_evidence: recent 0・前提として届くページなし・古い ABC 5 問
sections:
  - {title: 逐次最短路とポテンシャル, anchor: successive-shortest-path}
  - {title: コストは 0 以上（最大化は「定数 − 利得」に直す）, anchor: nonnegative-cost}
  - {title: 流量ごとの最小コスト（slope は下に凸）, anchor: slope}
  - {title: モデル化の型（重み付き二部マッチング・市松模様・差分列の流れ）, anchor: modeling}
  - {title: ACL では（mcf_graph の囲み）, anchor: acl}
  - {title: 割当問題とハンガリアン法, anchor: hungarian, level: 発展}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：流量 F を流すときのコストの最小値を、残余グラフ上のコストの最短路に沿って流すことをくり返して求める。逆辺の負のコストはポテンシャルで消してダイクストラを使い、ACL の mcf_graph で書ける。
    - **いつ使うか**：
        - K 個選んだときの最大（最小）を K ごとに答える
        - 重み付きの割当・各行・各列から高々 K 個
        - 流す量とコストの両方を最適化する
        - N ≤ 数百、M ≤ 数千程度で、流す量 K ≤ N
    - **計算量**：（執筆時に書く）
    - **前提**：[最大流](../graph/max-flow.md)、[ダイクストラ法](../graph/dijkstra.md)
