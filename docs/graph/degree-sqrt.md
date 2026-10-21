---
id: degree-sqrt
title: 次数による平方分割
aliases: [次数の平方分割, 重い頂点と軽い頂点, 三角形の列挙, 4-サイクルの検出, sqrt decomposition on degrees]
type: technique
field: graph
chapter: 探索木と次数の性質
order: 380
level: 青
kind: [グラフ探索, クエリ処理の工夫]
prerequisites: [graph-basics]
related: [sqrt-decomposition, symmetry-pigeonhole-casework#pigeonhole, bitset-speedup]
summary: 次数が √M を超える重い頂点は 2√M 個以下しかないことを使い、重い頂点と軽い頂点で処理を分けて、頂点とその隣接頂点すべてへのクエリを O(√M) にする。三角形の列挙や 4-サイクルの検出も同じ考え方で速くなる。
complexity: null
signs:
  - {type: phrase, text: 頂点とその隣接頂点すべてに対する操作・質問が大量に来る}
  - {type: phrase, text: 長さ 3・4 の閉路を見つける・数える}
  - {type: constraint, text: 'N, M, Q ≤ 2×10^5 で、1 つの頂点の次数が N 近くになりうる'}
acl: []
verify: [enumerate_triangles, counting_c4]
frequency: C
frequency_evidence: recent 0・前提として届くページなし・古い ABC 1 問
sections:
  - {title: 重い頂点は 2√M 個以下, anchor: few-heavy}
  - {title: 重い頂点は受け取る側、軽い頂点は配る側, anchor: push-pull}
  - {title: 三角形の列挙（次数の小さい方から向き付ける）, anchor: triangles, level: 黄}
  - {title: 4-サイクルの検出（鳩の巣原理で打ち切る）, anchor: four-cycles, level: 黄}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：次数が √M を超える重い頂点は 2√M 個以下しかないことを使い、重い頂点と軽い頂点で処理を分けて、頂点とその隣接頂点すべてへのクエリを O(√M) にする。三角形の列挙や 4-サイクルの検出も同じ考え方で速くなる。
    - **いつ使うか**：
        - 頂点とその隣接頂点すべてに対する操作・質問が大量に来る
        - 長さ 3・4 の閉路を見つける・数える
        - N, M, Q ≤ 2×10^5 で、1 つの頂点の次数が N 近くになりうる
    - **計算量**：（執筆時に書く）
    - **前提**：[グラフの表現と用語](../graph/graph-basics.md)
