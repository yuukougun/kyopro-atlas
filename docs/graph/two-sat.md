---
id: two-sat
title: 2-SAT
aliases: [2SAT, 充足可能性, 含意グラフ, 2-satisfiability]
type: overview
field: graph
chapter: 有向グラフ
order: 280
level: 発展
kind: [グラフ探索]
prerequisites: [scc]
related: [bipartite-graph, project-selection]
summary: 各変数が真か偽で、条件がすべて「2 つのリテラルの OR」のとき、全条件を満たす割当を含意グラフの SCC で O(N+M) で求める。ACL の two_sat で書けるので、条件を節に直すモデル化が中心になる。
complexity: null
signs:
  - {type: phrase, text: 各要素が 2 択で「この 2 つは同時に選べない」「少なくともどちらか一方」}
  - {type: phrase, text: 条件を満たす 2 択の割当があるか、あれば 1 つ出力する}
  - {type: shape, text: 条件がすべて (x_i ∨ x_j) の形（2 つのリテラルの OR）に書ける}
acl: [two_sat]
verify: [two_sat]
frequency: C
frequency_evidence: recent 0・前提として届くページなし・古い ABC 2 問
sections:
  - {title: 節を含意の辺 ¬a→b・¬b→a に直す, anchor: implication}
  - {title: x と ¬x が同じ SCC なら充足不能・答えの復元, anchor: unsatisfiable}
  - {title: モデル化の早見表（同時に選べない・どちらかは必ず・a なら b）, anchor: cheatsheet}
  - {title: 「高々 1 つ」を補助変数で O(K) 本の節にする, anchor: at-most-one}
  - {title: ACL では（two_sat の囲み）, anchor: acl}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：各変数が真か偽で、条件がすべて「2 つのリテラルの OR」のとき、全条件を満たす割当を含意グラフの SCC で O(N+M) で求める。ACL の two_sat で書けるので、条件を節に直すモデル化が中心になる。
    - **いつ使うか**：
        - 各要素が 2 択で「この 2 つは同時に選べない」「少なくともどちらか一方」
        - 条件を満たす 2 択の割当があるか、あれば 1 つ出力する
        - 条件がすべて (x_i ∨ x_j) の形（2 つのリテラルの OR）に書ける
    - **計算量**：（執筆時に書く）
    - **前提**：[強連結成分分解（SCC）](../graph/scc.md)
