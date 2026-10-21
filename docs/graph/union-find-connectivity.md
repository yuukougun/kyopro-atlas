---
id: union-find-connectivity
title: Union-Find で連結性を扱う
aliases: [逆順 Union-Find, 削除を逆順の追加にする, 辺の削除を逆から, オフラインの連結判定, offline connectivity]
type: technique
field: graph
chapter: 連結性と全域木
order: 290
level: 水
kind: [連結性・全域木, クエリ処理の工夫]
prerequisites: [connected-components]
related: [union-find-applications, minimum-spanning-tree, bottleneck-path, offline-queries, rollback-union-find, offline-dynamic-connectivity, reverse-thinking, binary-search-answer]
summary: 辺や頂点の削除を時間の逆順の追加に直したり、しきい値の順に辺を足したりして、連結成分の数・大きさや 2 点の連結を Union-Find で答える。答えは逆順に記録してから反転する。
complexity: null
signs:
  - {type: phrase, text: 辺（頂点）を順に削除し、そのつど連結成分の数・大きさを答える（橋が崩落する・停電）}
  - {type: phrase, text: 重さ・高さ・年などの制限を満たす辺だけで行けるかを多数答える}
  - {type: phrase, text: 答えを決め打つと、つながっているかどうかで判定できる}
acl: [dsu]
frequency: B
frequency_evidence: recent 0・前提として 2 ページに届く（直接 2）・古い ABC 5 問
sections:
  - {title: 削除を逆順の追加にする（答えは逆順に記録して反転する）, anchor: reverse-deletion}
  - {title: しきい値の順に辺を足してクエリに答える（オフライン）, anchor: threshold}
  - {title: 超頂点と組み合わせる, anchor: super-vertex}
  - {title: 辺の追加と削除が混ざるとき（ロールバック Union-Find・オフライン動的連結性へ）, anchor: mixed-updates}
  - {title: 二分探索と連結判定の組合せ, anchor: binary-search, level: 青}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：辺や頂点の削除を時間の逆順の追加に直したり、しきい値の順に辺を足したりして、連結成分の数・大きさや 2 点の連結を Union-Find で答える。答えは逆順に記録してから反転する。
    - **いつ使うか**：
        - 辺（頂点）を順に削除し、そのつど連結成分の数・大きさを答える（橋が崩落する・停電）
        - 重さ・高さ・年などの制限を満たす辺だけで行けるかを多数答える
        - 答えを決め打つと、つながっているかどうかで判定できる
    - **計算量**：（執筆時に書く）
    - **前提**：[連結成分](../graph/connected-components.md)
