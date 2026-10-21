---
id: lowlink
title: 橋・関節点・二重連結成分
aliases: [lowlink, 橋, 関節点, 二重辺連結成分, 二重頂点連結成分, ブロックカット木, ord と low, bridge, articulation point, biconnected components, block-cut tree]
type: technique
field: graph
chapter: 連結性と全域木
order: 320
level: 黄
kind: [連結性・全域木, グラフ探索]
prerequisites: [dfs]
related: [scc, union-find-connectivity, offline-dynamic-connectivity, shortest-path-dag, graph-construction]
summary: DFS 木の行きがけ番号 ord と、部分木から後退辺を 1 本使って戻れる最小の番号 low から、取り除くと非連結になる辺（橋）と頂点（関節点）を O(N+M) で求める。橋や関節点で分けた成分を縮約すると木になる。
complexity: null
signs:
  - {type: phrase, text: その辺（頂点）を取り除くと非連結になるか}
  - {type: phrase, text: すべての辺（頂点）について、取り除いたときの連結成分の数を求める}
  - {type: constraint, text: 'N, M ≤ 2×10^5 で、辺を 1 本ずつ除いて調べる O(M(N+M)) は間に合わない'}
acl: []
verify: [two_edge_connected_components, biconnected_components]
frequency: B
frequency_evidence: recent 0・前提として届くページなし・古い ABC 3 問
sections:
  - {title: ord と low の定義と求め方, anchor: ord-low}
  - {title: 橋の条件と関節点の条件（根は子の数で判定）, anchor: conditions}
  - {title: 多重辺は辺の番号で親を除外する, anchor: multi-edges}
  - {title: 二重辺連結成分（橋で分けて縮約すると木になる）, anchor: two-edge-connected}
  - {title: 有向グラフの SCC（同じ ord・low の考え方）との対比, anchor: vs-scc}
  - {title: 二重頂点連結成分とブロックカット木, anchor: block-cut-tree, level: 発展}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：DFS 木の行きがけ番号 ord と、部分木から後退辺を 1 本使って戻れる最小の番号 low から、取り除くと非連結になる辺（橋）と頂点（関節点）を O(N+M) で求める。橋や関節点で分けた成分を縮約すると木になる。
    - **いつ使うか**：
        - その辺（頂点）を取り除くと非連結になるか
        - すべての辺（頂点）について、取り除いたときの連結成分の数を求める
        - N, M ≤ 2×10^5 で、辺を 1 本ずつ除いて調べる O(M(N+M)) は間に合わない
    - **計算量**：（執筆時に書く）
    - **前提**：[深さ優先探索（DFS）](../graph/dfs.md)
