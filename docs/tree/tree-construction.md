---
id: tree-construction
title: 木の構築・復元
aliases: [木の構築, 木の復元, 距離の表から木, 訪問順から木, tree construction]
type: technique
field: tree
chapter: 木全体の形
order: 130
level: 水
kind: [木, 考察]
prerequisites: [tree-traversal]
related: [tree-degree, tree-diameter, minimum-spanning-tree, graph-construction, construction]
summary: 距離の情報・訪問順・次数の条件などから、条件を満たす木を作るか、ないと判定する（何通りあるかを数えることもある）。作った木が本当に条件を満たすかを最後に確かめることが要になる。
complexity: null
signs:
  - {type: phrase, text: 条件を満たす木を 1 つ出力せよ（なければ −1）}
  - {type: phrase, text: 距離の情報から木を復元できるか}
  - {type: phrase, text: 訪問順（DFS 順）から元の木が何通りあるか}
acl: [dsu]
frequency: A
frequency_evidence: recent 2（abc451_e・abc478_f）・前提として届くページなし・古い ABC 2 問
sections:
  - {title: 距離の情報から作る（最も近い頂点とは辺で結ばれる）, anchor: from-distances}
  - {title: 訪問順から親の候補を数える, anchor: from-order}
  - {title: 作った木を必ず確かめる, anchor: verify-output}
  - {title: 次数の条件から作る（次数の足りない成分どうしをつなぐ）, anchor: from-degrees, level: 青}
  - {title: 最遠距離の列から直径を決める, anchor: from-eccentricities, level: 青}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：距離の情報・訪問順・次数の条件などから、条件を満たす木を作るか、ないと判定する（何通りあるかを数えることもある）。作った木が本当に条件を満たすかを最後に確かめることが要になる。
    - **いつ使うか**：
        - 条件を満たす木を 1 つ出力せよ（なければ −1）
        - 距離の情報から木を復元できるか
        - 訪問順（DFS 順）から元の木が何通りあるか
    - **計算量**：（執筆時に書く）
    - **前提**：[根付き木と走査順](../tree/tree-traversal.md)
