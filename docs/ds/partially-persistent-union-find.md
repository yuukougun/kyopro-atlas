---
id: partially-persistent-union-find
title: 部分永続 Union-Find
aliases: [部分永続 UF, 時刻つき Union-Find, partially persistent union-find]
type: overview
field: ds
chapter: Union-Find
order: 130
level: 発展
kind: [データ構造, 連結性・全域木]
prerequisites: [union-find, binary-search]
related: [parallel-binary-search, rollback-union-find, merge-process-tree, bottleneck-path, persistent-data-structures]
summary: 過去の時刻 t の時点での連結判定や成分の大きさを答えられる Union-Find。経路圧縮をせず各頂点に根でなくなった時刻を記録し、時刻の二分探索で初めて連結になる時刻も求める。
complexity: null
signs:
  - {type: phrase, text: 最初の t 本の辺だけを使ったときに連結か・成分の大きさは}
  - {type: phrase, text: x と y が初めて同じ集合になるのは何回目の操作か}
acl: []
verify: []
frequency: C
frequency_evidence: recent 0・前提として届くページなし・古い ABC 0 問
sections:
  - {title: 何ができるか（過去の時刻での find）, anchor: what-it-does}
  - {title: なぜ経路圧縮をしないのか, anchor: no-path-compression}
  - {title: 時刻の二分探索で「初めて連結になる時刻」を求める, anchor: binary-search-time}
  - {title: 代わりの手（並列二分探索・併合過程の木（Kruskal 再構築木））, anchor: alternatives}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：過去の時刻 t の時点での連結判定や成分の大きさを答えられる Union-Find。経路圧縮をせず各頂点に根でなくなった時刻を記録し、時刻の二分探索で初めて連結になる時刻も求める。
    - **いつ使うか**：
        - 最初の t 本の辺だけを使ったときに連結か・成分の大きさは
        - x と y が初めて同じ集合になるのは何回目の操作か
    - **計算量**：（執筆時に書く）
    - **前提**：[Union-Find](../ds/union-find.md)、[二分探索](../basics/binary-search.md)
