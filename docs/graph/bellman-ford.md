---
id: bellman-ford
title: ベルマンフォード法
aliases: [ベルマンフォード, Bellman-Ford, 負閉路検出, SPFA, 負辺のある最短路]
type: technique
field: graph
chapter: 最短路
order: 140
level: 青
kind: [最短路]
prerequisites: [dijkstra]
related: [difference-constraints, warshall-floyd, min-cost-flow, method-comparison]
summary: 負の辺があっても、全辺の緩和を N−1 回くり返して単一始点の最短距離を O(NM) で求める。答えに影響するのは、始点から届き終点へ行ける負閉路だけである。
complexity: null
signs:
  - {type: phrase, text: 負の重みの辺がある・得点を最大化する（符号を反転すると負辺になる）}
  - {type: phrase, text: いくらでも大きくできるなら inf と出力する}
  - {type: constraint, text: 'N, M ≤ 数千（O(NM) が間に合う）'}
acl: []
frequency: B
frequency_evidence: recent 0・前提として 1 ページに届く（直接 1）・古い ABC 3 問
sections:
  - {title: N−1 回で十分な理由, anchor: why-n-minus-1}
  - {title: 答えに影響する負閉路だけを判定する（到達可能性で絞る・−∞ を伝える）, anchor: relevant-cycles}
  - {title: 最長路は符号を反転する, anchor: longest-path}
  - {title: SPFA の注意（最悪の計算量は同じ）, anchor: spfa}
  - {title: 負辺があってもダイクストラで済む場合との見分け（ポテンシャル）, anchor: vs-potential}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：負の辺があっても、全辺の緩和を N−1 回くり返して単一始点の最短距離を O(NM) で求める。答えに影響するのは、始点から届き終点へ行ける負閉路だけである。
    - **いつ使うか**：
        - 負の重みの辺がある・得点を最大化する（符号を反転すると負辺になる）
        - いくらでも大きくできるなら inf と出力する
        - N, M ≤ 数千（O(NM) が間に合う）
    - **計算量**：（執筆時に書く）
    - **前提**：[ダイクストラ法](../graph/dijkstra.md)
