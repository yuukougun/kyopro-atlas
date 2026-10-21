---
id: persistent-data-structures
title: 永続データ構造
aliases: [persistent data structure, 永続, 版の木, 永続スタック, 永続セグ木, 経路コピー, path copying, 操作の巻き戻し]
type: technique
field: ds
chapter: そのほかのデータ構造
order: 320
level: 青
kind: [データ構造, クエリ処理の工夫]
prerequisites: [segment-tree, stack-techniques]
related: [rollback-union-find, root-path-dfs, euler-tour, merge-sort-tree, offline-queries, partially-persistent-union-find]
summary: 過去の版を残したまま更新し、任意の版から続きの操作をする。末尾の追加・削除・保存・読み込みは版を木の頂点にして表し（版の木）、配列やセグメント木は更新した経路だけを作り直して古い版と共有する。
complexity: null
signs:
  - {type: phrase, text: 状態を保存し、あとで読み込んで続きの操作をする}
  - {type: phrase, text: 配列を丸ごとコピーする操作と、1 点更新・区間和が混ざる}
  - {type: phrase, text: 時刻 t の時点での区間の値の分布}
acl: []
verify: [persistent_queue, persistent_range_affine_range_sum]
frequency: B
frequency_evidence: recent 1（abc453_g）・前提として届くページなし・古い ABC 1 問
sections:
  - {title: 版の木（追加は子を作る・削除は親へ戻る・保存は頂点を覚える）, anchor: version-tree}
  - {title: 経路コピー（1 回の更新で O(log N) 個のノードを新しく作る。丸ごとのコピーは根の指し替え）, anchor: path-copying}
  - {title: 部分永続と完全永続, anchor: partial-vs-full}
  - {title: 操作の版を木にしてオフラインで処理する（版の木の DFS と取り消し）, anchor: offline-version-tree}
  - {title: 使い分け（ロールバックは直前から順に戻すだけ、永続は任意の版へ）, anchor: choosing}
  - {title: 接頭辞ごとの版で区間の K 番目・x 以下の個数をオンラインで求める, anchor: prefix-versions, level: 発展}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：過去の版を残したまま更新し、任意の版から続きの操作をする。末尾の追加・削除・保存・読み込みは版を木の頂点にして表し（版の木）、配列やセグメント木は更新した経路だけを作り直して古い版と共有する。
    - **いつ使うか**：
        - 状態を保存し、あとで読み込んで続きの操作をする
        - 配列を丸ごとコピーする操作と、1 点更新・区間和が混ざる
        - 時刻 t の時点での区間の値の分布
    - **計算量**：（執筆時に書く）
    - **前提**：[セグメント木](../ds/segment-tree.md)、[スタック・キュー・deque の使いどころ](../ds/stack-techniques.md)
