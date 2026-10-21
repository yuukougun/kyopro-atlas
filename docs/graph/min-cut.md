---
id: min-cut
title: 最小カット
aliases: [最大流最小カット定理, 頂点カット, 頂点分割, カットの復元, minimum cut, s-t cut]
type: technique
field: graph
chapter: フロー・マッチング
order: 400
level: 黄
kind: [フロー・マッチング]
prerequisites: [max-flow]
related: [project-selection, konig-theorem, lowlink]
summary: 頂点を s 側と t 側に分けたとき、s 側から t 側へ向かう辺の容量の和の最小値は最大流に等しい。流し終えた残余グラフで s から届く頂点を s 側とすれば、カットを復元できる。
complexity: null
signs:
  - {type: phrase, text: s と t を切り離す最小のコスト}
  - {type: phrase, text: 頂点を消すコストの最小・どれを消したかも出力する}
acl: [mf_graph]
frequency: B
frequency_evidence: recent 1（abc472_g）・前提として 2 ページに届く（直接 2）・古い ABC 4 問
sections:
  - {title: 最大流最小カット定理, anchor: maxflow-mincut}
  - {title: カットの復元（ACL の min_cut）, anchor: restore}
  - {title: 頂点を入口と出口に分けて頂点カットを表す, anchor: vertex-cut}
  - {title: カットの形を決め打つ, anchor: cut-shape, level: 発展}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：頂点を s 側と t 側に分けたとき、s 側から t 側へ向かう辺の容量の和の最小値は最大流に等しい。流し終えた残余グラフで s から届く頂点を s 側とすれば、カットを復元できる。
    - **いつ使うか**：
        - s と t を切り離す最小のコスト
        - 頂点を消すコストの最小・どれを消したかも出力する
    - **計算量**：（執筆時に書く）
    - **前提**：[最大流](../graph/max-flow.md)
