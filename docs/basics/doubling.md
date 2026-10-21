---
id: doubling
title: ダブリング
aliases: [binary lifting, 倍化, 2^k 回後の表, ダブリング上の二分探索, doubling]
type: technique
field: basics
chapter: 周期とダブリング
order: 300
level: 水
kind: [ダブリング・分割統治]
prerequisites: [periodicity, bit-operations]
related: [lca, matrix-power, sparse-table, functional-graph]
summary: 各状態から次の状態が決まる遷移を K ≤ 10^18 回進めた結果や途中の和を、2^k 回後の表を作って O(log K) で求める。表は nxt[k+1][v] = nxt[k][nxt[k][v]] で作り、K を 2 進展開して跳ぶ。
complexity: null
signs:
  - {type: constraint, text: K ≤ 10^18 回の移動・操作で、始点やクエリが多い}
  - {type: phrase, text: 各状態から次の状態がただ 1 つに決まる}
  - {type: phrase, text: 途中の和・最小値も必要}
  - {type: phrase, text: 条件を満たす最大の回数を求める}
acl: []
frequency: B
frequency_evidence: recent 0・前提として 8 ページに届く（直接 2）・古い ABC 5 問
sections:
  - {title: 表の作り方と K の 2 進展開, anchor: table}
  - {title: 途中の和・最小値を同じ表に持つ（半開で持つ）, anchor: aggregates}
  - {title: ダブリング上の二分探索（条件を満たす最大の回数）, anchor: binary-search-on-doubling}
  - {title: 置換の K 回合成, anchor: permutation-power}
  - {title: 段数とメモリの見積もり, anchor: memory}
  - {title: 周期の検出・行列累乗・LCA との使い分け, anchor: comparison}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：各状態から次の状態が決まる遷移を K ≤ 10^18 回進めた結果や途中の和を、2^k 回後の表を作って O(log K) で求める。表は nxt\[k+1][v] = nxt\[k][nxt\[k][v]] で作り、K を 2 進展開して跳ぶ。
    - **いつ使うか**：
        - K ≤ 10^18 回の移動・操作で、始点やクエリが多い
        - 各状態から次の状態がただ 1 つに決まる
        - 途中の和・最小値も必要
        - 条件を満たす最大の回数を求める
    - **計算量**：（執筆時に書く）
    - **前提**：[周期性の検出](../basics/periodicity.md)、[bit 演算の基本と XOR の性質](../basics/bit-operations.md)
