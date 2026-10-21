---
id: connected-components
title: 連結成分
aliases: [連結成分分解, 連結判定, connected components]
type: technique
field: graph
chapter: 基本と探索
order: 60
level: 基礎
kind: [グラフ探索, 連結性・全域木]
prerequisites: [dfs, union-find]
related: [union-find-connectivity, scc, namori-graph, cycle-detection, graph-modeling]
summary: 無向グラフを互いに行き来できる頂点の集まりに分け、成分ごとに頂点数・辺数などを集計する。グラフが固定なら DFS・BFS、辺が増えていくなら Union-Find を使う。
complexity: null
signs:
  - {type: phrase, text: つながっているか・グループの数・最大のグループの大きさ}
  - {type: phrase, text: 友達の友達は友達}
  - {type: shape, text: 成分ごとの頂点数と辺数の関係（木か・閉路がちょうど 1 つか）で条件が決まる}
  - {type: phrase, text: '点 (x, y) の集合で、同じ x・同じ y を持つ点どうしが関係する'}
acl: [dsu]
frequency: B
frequency_evidence: recent 1（abc470_f）・前提として 5 ページに届く（直接 3）・古い ABC 4 問
sections:
  - {title: DFS・BFS・Union-Find の 3 つの求め方と使い分け, anchor: three-methods}
  - {title: 成分ごとの集計（頂点数と辺数で木・なもり・それ以外を見分ける）, anchor: per-component}
  - {title: 孤立点・多重辺・自己ループの数え方, anchor: pitfalls}
  - {title: 森の連結成分の数は N − M, anchor: forest}
  - {title: 座標や値を頂点にして成分を考える, anchor: values-as-vertices, level: 青}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：無向グラフを互いに行き来できる頂点の集まりに分け、成分ごとに頂点数・辺数などを集計する。グラフが固定なら DFS・BFS、辺が増えていくなら Union-Find を使う。
    - **いつ使うか**：
        - つながっているか・グループの数・最大のグループの大きさ
        - 友達の友達は友達
        - 成分ごとの頂点数と辺数の関係（木か・閉路がちょうど 1 つか）で条件が決まる
        - 点 (x, y) の集合で、同じ x・同じ y を持つ点どうしが関係する
    - **計算量**：（執筆時に書く）
    - **前提**：[深さ優先探索（DFS）](../graph/dfs.md)、[Union-Find](../ds/union-find.md)
