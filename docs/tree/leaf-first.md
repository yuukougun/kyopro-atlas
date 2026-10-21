---
id: leaf-first
title: 葉から考える
aliases: [葉から貪欲, 葉を刈る, 次数 1 の頂点を削る, 葉から決める貪欲, greedy from leaves]
type: technique
field: tree
chapter: 木の基礎
order: 80
level: 水
kind: [木, 貪欲]
prerequisites: [tree-traversal, greedy-basics]
related: [exchange-argument, tree-dp, namori-graph, topological-sort, tree-degree, tree-ratio-greedy]
summary: 葉は辺が 1 本しかないので選択肢が少なく、葉から順に決めると貪欲が正しくなりやすい。次数 1 の頂点をキューで削るか帰りがけ順に情報を上へ送り、正しさは交換論法で示す。
complexity: null
signs:
  - {type: phrase, text: 木を K 頂点ずつのパスに分ける}
  - {type: phrase, text: 辺をすべて使う・すべて覆う}
  - {type: phrase, text: 葉を消していく操作}
acl: []
frequency: B
frequency_evidence: recent 1（abc459_e）・前提として 2 ページに届く（直接 1）・古い ABC 2 問
sections:
  - {title: 次数 1 の頂点をキューで削る, anchor: peel-leaves}
  - {title: 帰りがけ順に葉から情報を上へ送る, anchor: send-up}
  - {title: 葉の唯一の辺を今使ってよい理由（交換論法）, anchor: why-greedy}
  - {title: 木の最大マッチング（葉と親を組む）, anchor: tree-matching}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：葉は辺が 1 本しかないので選択肢が少なく、葉から順に決めると貪欲が正しくなりやすい。次数 1 の頂点をキューで削るか帰りがけ順に情報を上へ送り、正しさは交換論法で示す。
    - **いつ使うか**：
        - 木を K 頂点ずつのパスに分ける
        - 辺をすべて使う・すべて覆う
        - 葉を消していく操作
    - **計算量**：（執筆時に書く）
    - **前提**：[根付き木と走査順](../tree/tree-traversal.md)、[貪欲法の考え方と正当性](../basics/greedy-basics.md)
