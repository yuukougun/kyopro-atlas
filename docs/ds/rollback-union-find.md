---
id: rollback-union-find
title: ロールバックできる Union-Find
aliases: [ロールバック UF, Undo つき Union-Find, undoable union-find, rollback union-find]
type: overview
field: ds
chapter: Union-Find
order: 140
level: 発展
kind: [データ構造, 連結性・全域木]
prerequisites: [union-find]
related: [offline-dynamic-connectivity, root-path-dfs, partially-persistent-union-find, persistent-data-structures, segment-tree]
summary: 直前の併合から順に取り消せる Union-Find。経路圧縮をせず、書き換えた場所と元の値をスタックに積み、木の DFS（入るとき併合・出るとき取り消し）やオフライン動的連結性の部品に使う。
complexity: null
signs:
  - {type: phrase, text: 木の根から各頂点へのパスごとに、パス上の要素どうしのつながりを答える}
  - {type: phrase, text: 辺の追加と削除が混ざり、そのたびに 2 頂点が連結かを答える}
acl: []
verify: [dynamic_graph_vertex_add_component_sum]
frequency: C
frequency_evidence: recent 0・前提として 1 ページに届く（直接 1）・古い ABC 1 問
sections:
  - {title: 何ができるか（後入れ先出しの取り消し）, anchor: what-it-does}
  - {title: なぜ経路圧縮をしないのか（戻すコストとならしの保証が崩れること）, anchor: no-path-compression}
  - {title: 木の DFS と組む（入るとき併合・出るとき取り消し）, anchor: with-dfs}
  - {title: オフライン動的連結性の部品（時間軸のセグメント木に辺を載せる → グラフの章）, anchor: offline-dynamic-connectivity}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：直前の併合から順に取り消せる Union-Find。経路圧縮をせず、書き換えた場所と元の値をスタックに積み、木の DFS（入るとき併合・出るとき取り消し）やオフライン動的連結性の部品に使う。
    - **いつ使うか**：
        - 木の根から各頂点へのパスごとに、パス上の要素どうしのつながりを答える
        - 辺の追加と削除が混ざり、そのたびに 2 頂点が連結かを答える
    - **計算量**：（執筆時に書く）
    - **前提**：[Union-Find](../ds/union-find.md)
