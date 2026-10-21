---
id: root-path-dfs
title: 根からのパスを DFS で持ち回る
aliases: [DFS の巻き戻し, 根からのパスの情報, 入るとき足して出るとき戻す, rollback on DFS]
type: technique
field: tree
chapter: パス
order: 170
level: 青
kind: [木, クエリ処理の工夫]
prerequisites: [tree-traversal]
related: [euler-tour, persistent-data-structures#version-tree, rollback-union-find, lis]
summary: DFS で頂点に入るときにデータ構造へ情報を足し、出るときに元に戻すと、常に根から今の頂点までのパスの情報だけを持てる。パス上の色の数・LIS・中央値などを全頂点について求められる。
complexity: null
signs:
  - {type: phrase, text: 根から頂点 v までのパス上の…を、すべての v について求める}
  - {type: phrase, text: 祖先の情報だけで決まる値}
  - {type: phrase, text: 操作を元に戻す・保存した状態に戻る}
acl: []
frequency: B
frequency_evidence: recent 0・前提として届くページなし・古い ABC 5 問
sections:
  - {title: DFS のスタックは根からのパス, anchor: stack-is-path}
  - {title: 変更の記録と巻き戻し（後に変えたものから戻す）, anchor: undo-log}
  - {title: パス上の LIS・中央値・種類数, anchor: path-statistics}
  - {title: 操作の履歴を木にする型は永続データ構造の版の木へ, anchor: to-version-tree}
  - {title: 経路圧縮つきの Union-Find は戻せない（取り消せる Union-Find はデータ構造の章）, anchor: no-path-compression}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：DFS で頂点に入るときにデータ構造へ情報を足し、出るときに元に戻すと、常に根から今の頂点までのパスの情報だけを持てる。パス上の色の数・LIS・中央値などを全頂点について求められる。
    - **いつ使うか**：
        - 根から頂点 v までのパス上の…を、すべての v について求める
        - 祖先の情報だけで決まる値
        - 操作を元に戻す・保存した状態に戻る
    - **計算量**：（執筆時に書く）
    - **前提**：[根付き木と走査順](../tree/tree-traversal.md)
