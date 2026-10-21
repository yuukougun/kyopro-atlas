---
id: cycle-detection
title: 閉路の検出と復元
aliases: [閉路検出, サイクル検出, 有向閉路, 無向閉路, 3 色の DFS, cycle detection]
type: technique
field: graph
chapter: 基本と探索
order: 70
level: 基礎
kind: [グラフ探索]
prerequisites: [dfs, union-find]
related: [topological-sort, functional-graph, scc, namori-graph, graph-modeling, periodicity]
summary: 無向グラフでは Union-Find か親以外の訪問済み頂点への辺、有向グラフでは探索中の頂点への辺（3 色の DFS）で閉路を見つけ、親をたどって復元する。シミュレーションの周期の検出とは別物である。
complexity: null
signs:
  - {type: phrase, text: 循環している・依存関係が回っている・矛盾があれば −1}
  - {type: phrase, text: 閉路を 1 つ見つけて出力せよ}
acl: [dsu, scc_graph]
verify: [cycle_detection, cycle_detection_undirected]
frequency: B
frequency_evidence: recent 1（abc456_e）・前提として 2 ページに届く（直接 2）・古い ABC 3 問
sections:
  - {title: 無向グラフ：Union-Find・親以外の訪問済みの頂点への辺（多重辺は辺の番号で除外）, anchor: undirected}
  - {title: 有向グラフ：3 色の DFS（探索中の頂点への辺だけが閉路）, anchor: directed}
  - {title: Kahn 法で残る頂点（すべてが閉路上とは限らない）, anchor: kahn-leftover}
  - {title: 閉路の復元（親をたどる）, anchor: restore}
  - {title: 出次数 1 のグラフでは同じ頂点に 2 回来るまで進む, anchor: out-degree-one}
  - {title: シミュレーションの周期の検出（基本テクニックの章）との違い, anchor: vs-periodicity}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：無向グラフでは Union-Find か親以外の訪問済み頂点への辺、有向グラフでは探索中の頂点への辺（3 色の DFS）で閉路を見つけ、親をたどって復元する。シミュレーションの周期の検出とは別物である。
    - **いつ使うか**：
        - 循環している・依存関係が回っている・矛盾があれば −1
        - 閉路を 1 つ見つけて出力せよ
    - **計算量**：（執筆時に書く）
    - **前提**：[深さ優先探索（DFS）](../graph/dfs.md)、[Union-Find](../ds/union-find.md)
