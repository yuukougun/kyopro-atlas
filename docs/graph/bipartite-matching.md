---
id: bipartite-matching
title: 二部マッチング
aliases: [二部グラフの最大マッチング, Hopcroft-Karp, 交互路, 完全マッチング, 二部グラフの辺彩色, bipartite matching]
type: technique
field: graph
chapter: フロー・マッチング
order: 420
level: 黄
kind: [フロー・マッチング]
prerequisites: [max-flow, bipartite-graph]
related: [konig-theorem, min-cost-flow, general-matching, dilworth-path-cover, binary-search-answer]
summary: 二部グラフで端点を共有しない辺の最大集合を、容量 1 の最大流（s → 左 → 右 → t）で求める。交互路を反転するとマッチングが 1 増えることが要で、答えの二分探索と完全マッチングの判定を組む型が多い。
complexity: null
signs:
  - {type: phrase, text: ペアを作る最大数・各人に 1 つずつ割り当てる}
  - {type: phrase, text: 答えを決め打つと、全員に割り当てられるかの判定になる}
  - {type: phrase, text: 和が素数・偶奇で 2 つのグループに分かれる}
acl: [mf_graph]
verify: [bipartitematching]
frequency: B
frequency_evidence: recent 1（abc461_g）・前提として 3 ページに届く（直接 3）・古い ABC 4 問
sections:
  - {title: 最大流への帰着（容量 1）, anchor: reduction}
  - {title: 交互路と増加路（Kuhn・Hopcroft-Karp）, anchor: alternating-path}
  - {title: 答えの二分探索と完全マッチングの判定, anchor: binary-search}
  - {title: 構造で貪欲が通る特殊な場合との見分け, anchor: greedy-cases}
  - {title: 正則二部グラフの分解・辺彩色, anchor: edge-coloring, level: 発展}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：二部グラフで端点を共有しない辺の最大集合を、容量 1 の最大流（s → 左 → 右 → t）で求める。交互路を反転するとマッチングが 1 増えることが要で、答えの二分探索と完全マッチングの判定を組む型が多い。
    - **いつ使うか**：
        - ペアを作る最大数・各人に 1 つずつ割り当てる
        - 答えを決め打つと、全員に割り当てられるかの判定になる
        - 和が素数・偶奇で 2 つのグループに分かれる
    - **計算量**：（執筆時に書く）
    - **前提**：[最大流](../graph/max-flow.md)、[二部グラフ判定](../graph/bipartite-graph.md)
