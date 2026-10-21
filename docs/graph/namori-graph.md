---
id: namori-graph
title: なもりグラフ
aliases: [なもり, unicyclic graph, pseudotree, 閉路が 1 つのグラフ, 木に辺を 1 本足したグラフ, N 頂点 N 辺の連結グラフ]
type: technique
field: graph
chapter: 有向グラフ
order: 270
level: 水
kind: [グラフ探索, 木]
prerequisites: [connected-components, cycle-detection, tree-basics]
related: [functional-graph, leaf-first, topological-sort]
summary: N 頂点 N 辺の連結グラフは木に辺を 1 本足した形で、閉路がちょうど 1 つあり、閉路上の各頂点から木がぶら下がる。次数 1 の頂点を削り続けると閉路だけが残る。
complexity: null
signs:
  - {type: phrase, text: N 頂点 N 辺の連結グラフ・木に辺を 1 本足したグラフ}
  - {type: phrase, text: 2 頂点間の単純パスが一意か}
acl: [dsu]
frequency: C
frequency_evidence: recent 0・前提として届くページなし・古い ABC 2 問
sections:
  - {title: 閉路がちょうど 1 つある理由, anchor: one-cycle}
  - {title: 次数 1 の頂点を削って閉路を求める（Union-Find でも）, anchor: peel-leaves}
  - {title: 閉路の頂点ごとにぶら下がる木に分ける, anchor: hanging-trees}
  - {title: 単純パスが一意になる条件, anchor: unique-path}
  - {title: 有向版は Functional graph, anchor: directed-version}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：N 頂点 N 辺の連結グラフは木に辺を 1 本足した形で、閉路がちょうど 1 つあり、閉路上の各頂点から木がぶら下がる。次数 1 の頂点を削り続けると閉路だけが残る。
    - **いつ使うか**：
        - N 頂点 N 辺の連結グラフ・木に辺を 1 本足したグラフ
        - 2 頂点間の単純パスが一意か
    - **計算量**：（執筆時に書く）
    - **前提**：[連結成分](../graph/connected-components.md)、[閉路の検出と復元](../graph/cycle-detection.md)、[木の基本性質と表現](../tree/tree-basics.md)
