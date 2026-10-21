---
id: scc
title: 強連結成分分解（SCC）
aliases: [強連結成分, SCC, Kosaraju, Tarjan, strongly connected components]
type: technique
field: graph
chapter: 有向グラフ
order: 250
level: 水
kind: [グラフ探索]
prerequisites: [topological-sort]
related: [two-sat, functional-graph, connected-components, lowlink, dilworth-path-cover, bitset-speedup, dp-dag]
summary: 有向グラフを互いに行き来できる頂点の極大集合に分け、成分を 1 点に縮めて DAG にする。Kosaraju か Tarjan で O(N+M) で求まり、ACL の scc_graph は成分をトポロジカル順に返す。
complexity: null
signs:
  - {type: phrase, text: 互いに行き来できる頂点の組・グループ}
  - {type: phrase, text: 何度でもくり返せる（閉路の中にいる）}
  - {type: shape, text: 閉路を 1 点に縮めた DAG の上で DP・数え上げをしたくなる}
acl: [scc_graph]
verify: [scc]
frequency: B
frequency_evidence: recent 1（abc478_e）・前提として 2 ページに届く（直接 2）・古い ABC 3 問
sections:
  - {title: 縮約したグラフが DAG になる理由, anchor: condensation}
  - {title: Kosaraju と Tarjan, anchor: algorithms}
  - {title: ACL の scc_graph（トポロジカル順の成分のリスト）, anchor: acl}
  - {title: 閉路に含まれる頂点（自己ループに注意）, anchor: on-cycle}
  - {title: 縮約した DAG の上で DP する, anchor: dp-on-dag}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：有向グラフを互いに行き来できる頂点の極大集合に分け、成分を 1 点に縮めて DAG にする。Kosaraju か Tarjan で O(N+M) で求まり、ACL の scc_graph は成分をトポロジカル順に返す。
    - **いつ使うか**：
        - 互いに行き来できる頂点の組・グループ
        - 何度でもくり返せる（閉路の中にいる）
        - 閉路を 1 点に縮めた DAG の上で DP・数え上げをしたくなる
    - **計算量**：（執筆時に書く）
    - **前提**：[トポロジカルソート](../graph/topological-sort.md)
