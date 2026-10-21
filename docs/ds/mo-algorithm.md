---
id: mo-algorithm
title: Mo's algorithm
aliases: [Mo, Mo 法, クエリ平方分割, 木上の Mo, Mo on tree, 時間付き Mo]
type: technique
field: ds
chapter: クエリ処理の工夫
order: 280
level: 青
kind: [クエリ処理の工夫, 区間クエリ]
prerequisites: [offline-queries]
related: [sqrt-decomposition, euler-tour, lca, fenwick-tree, small-to-large, hld, inversion-number]
summary: 更新のない列への区間クエリを並べ替え（l のブロックの順、次に r の順）、前の区間から 1 要素ずつ伸び縮みして答える。伸縮は合計 O(N√Q) 回で、区間の種類数のように左右を合成できない量に使う。
complexity: null
signs:
  - {type: phrase, text: 静的な列で、区間ごとの同じ値の組の数・出現回数が条件を満たす値の種類数}
  - {type: phrase, text: 木のパス上の値の頻度を多数のクエリで答える}
  - {type: constraint, text: 'N, Q ≈ 2×10^5 で、制限時間が長めにとってある'}
acl: []
verify: [static_range_inversions_query]
frequency: B
frequency_evidence: recent 1（abc477_g）・前提として届くページなし・古い ABC 4 問
sections:
  - {title: 何ができるか（1 要素の出入りで答えを差分更新できる量）, anchor: what-it-does}
  - {title: クエリの並べ方と計算量（ブロックの大きさ N/√Q、伸縮の総回数 O(N√Q)）, anchor: ordering}
  - {title: 実装の要点（伸ばしてから縮める・奇数ブロックで r を逆順・取得を重くしてよい（値の平方分割））, anchor: implementation}
  - {title: '2 つの接頭辞の長さ (X, Y) を区間と見る', anchor: two-prefixes, level: 黄}
  - {title: 木上の Mo（入りと出の両方を記録した列で、パスを区間にする。LCA を別に足す）, anchor: mo-on-tree, level: 黄}
  - {title: 時間付き Mo・ロールバック Mo, anchor: variants, level: 発展}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：更新のない列への区間クエリを並べ替え（l のブロックの順、次に r の順）、前の区間から 1 要素ずつ伸び縮みして答える。伸縮は合計 O(N√Q) 回で、区間の種類数のように左右を合成できない量に使う。
    - **いつ使うか**：
        - 静的な列で、区間ごとの同じ値の組の数・出現回数が条件を満たす値の種類数
        - 木のパス上の値の頻度を多数のクエリで答える
        - N, Q ≈ 2×10^5 で、制限時間が長めにとってある
    - **計算量**：（執筆時に書く）
    - **前提**：[クエリの先読み](../ds/offline-queries.md)
