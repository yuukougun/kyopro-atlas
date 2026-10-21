---
id: minimum-spanning-tree
title: 最小全域木
aliases: [MST, クラスカル法, プリム法, Kruskal, Prim, 最大全域木, minimum spanning tree]
type: technique
field: graph
chapter: 連結性と全域木
order: 300
level: 水
kind: [連結性・全域木, 貪欲]
prerequisites: [union-find, sorting-techniques]
related: [union-find-connectivity, bottleneck-path, shortest-path-dag, steiner-tree, spanning-tree-advanced, union-find-applications#next-pointer, merge-process-tree]
summary: 連結グラフの全域木のうち辺の重みの和が最小のものを、辺を重みの昇順に見て閉路を作らない辺だけを採る Kruskal 法か、頂点を 1 つずつ伸ばす Prim 法で求める。候補の辺を減らせば完全グラフにも使える。
complexity: null
signs:
  - {type: phrase, text: すべての頂点をつなぐ最小コスト}
  - {type: phrase, text: 不要な辺を取り除いて報酬を最大にする}
  - {type: constraint, text: 完全グラフで N ≤ 2×10^5（辺が N^2 本あり、候補の辺を減らす必要がある）}
  - {type: phrase, text: この辺は最小全域木に入るか}
acl: [dsu]
verify: [minimum_spanning_tree]
frequency: A
frequency_evidence: recent 2（abc451_e・abc469_f）・前提として 3 ページに届く（直接 3）・古い ABC 7 問
sections:
  - {title: Kruskal 法と Prim 法（密なら O(N^2) の Prim）, anchor: kruskal-prim}
  - {title: 正しさの理由（カット性質・閉路性質）, anchor: why-correct}
  - {title: 最大全域木, anchor: maximum}
  - {title: クエリの辺が最小全域木に入るか（まとめて重み順に処理する）, anchor: query-edges}
  - {title: 辺の候補を減らす（ソートした隣どうし・約数で絞る）, anchor: reduce-candidates}
  - {title: 操作を頂点にする・区間を辺にする, anchor: modeling, level: 青}
  - {title: 辺の重みの種類が少ないとき, anchor: few-weights, level: 青}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：連結グラフの全域木のうち辺の重みの和が最小のものを、辺を重みの昇順に見て閉路を作らない辺だけを採る Kruskal 法か、頂点を 1 つずつ伸ばす Prim 法で求める。候補の辺を減らせば完全グラフにも使える。
    - **いつ使うか**：
        - すべての頂点をつなぐ最小コスト
        - 不要な辺を取り除いて報酬を最大にする
        - 完全グラフで N ≤ 2×10^5（辺が N^2 本あり、候補の辺を減らす必要がある）
        - この辺は最小全域木に入るか
    - **計算量**：（執筆時に書く）
    - **前提**：[Union-Find](../ds/union-find.md)、[ソートで考える](../basics/sorting-techniques.md)
