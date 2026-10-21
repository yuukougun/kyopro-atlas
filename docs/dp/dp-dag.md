---
id: dp-dag
title: DAG 上の DP
aliases: [DAG DP, DP on DAG, DAG の最長路, 経路の数え上げ, トポロジカル順の DP]
type: technique
field: dp
chapter: DP の考え方
order: 30
level: 基礎
kind: [DP, グラフ探索]
prerequisites: [dp-basics, topological-sort]
related: [dp-order, memoized-recursion, shortest-path-dag, scc#dp-on-dag, functional-graph, bitset-speedup#reachability]
summary: 閉路のない有向グラフで、最長路や経路の数をトポロジカル順の DP で O(N+M) で求める。どの DP も、状態を頂点・遷移を辺とする DAG の上の計算と見られる。
complexity: null
signs:
  - {type: phrase, text: 番号の小さい頂点から大きい頂点へだけ辺がある（u < v）}
  - {type: phrase, text: 値が増える向きにしか移動できない}
  - {type: phrase, text: 有向グラフの最長の経路の長さ・経路の本数・最短経路の本数}
  - {type: phrase, text: 依存関係に従って順に決める（閉路があれば −1）}
acl: []
frequency: B
frequency_evidence: recent 0・前提として 1 ページに届く（直接 1）・古い ABC 6 問
sections:
  - {title: DP は DAG 上の最短路・最長路・数え上げ, anchor: dp-as-dag}
  - {title: 順序の作り方（Kahn 法・DFS の帰りがけ順の逆・メモ化再帰・問題の性質から）, anchor: ordering}
  - {title: DAG だと気づく・作る（値の順・距離の層・同じ値の頂点をまとめる）, anchor: find-dag, level: 水}
  - {title: 最短路の本数（距離が確定した順に配る）, anchor: count-shortest-paths}
  - {title: 閉路があるとき（SCC で縮約する・最短路に切り替える）, anchor: with-cycles}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：閉路のない有向グラフで、最長路や経路の数をトポロジカル順の DP で O(N+M) で求める。どの DP も、状態を頂点・遷移を辺とする DAG の上の計算と見られる。
    - **いつ使うか**：
        - 番号の小さい頂点から大きい頂点へだけ辺がある（u < v）
        - 値が増える向きにしか移動できない
        - 有向グラフの最長の経路の長さ・経路の本数・最短経路の本数
        - 依存関係に従って順に決める（閉路があれば −1）
    - **計算量**：（執筆時に書く）
    - **前提**：[DP の基本](../dp/dp-basics.md)、[トポロジカルソート](../graph/topological-sort.md)
