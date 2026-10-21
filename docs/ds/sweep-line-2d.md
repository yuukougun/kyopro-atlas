---
id: sweep-line-2d
title: 平面走査
aliases: [sweep line, plane sweep, 走査線, スイープライン, 2 次元クエリ, 矩形内の点の数, 長方形クエリ]
type: technique
field: ds
chapter: クエリ処理の工夫
order: 270
level: 青
kind: [クエリ処理の工夫, 区間クエリ, ソート・座標圧縮]
prerequisites: [event-sort, offline-queries, lazy-segment-tree]
related: [fenwick-tree, prefix-sum-2d, imos, merge-sort-tree, cdq-divide-and-conquer, inversion-number]
summary: 2 次元の問題を、一方の座標の順にイベント（点・区間の端・クエリ）を並べ、走査線を動かしながらもう一方の座標を BIT・セグメント木で持つ形にする。長方形内の点の数や固定幅の窓の最大を求める。
complexity: null
signs:
  - {type: phrase, text: 長方形の中にある点の数・和を多数のクエリで答える}
  - {type: phrase, text: '区間 [p, q] に完全に含まれる区間の数'}
  - {type: phrase, text: 幅 W・高さ D の枠に入る点の最大数}
  - {type: constraint, text: 座標が 10^9 まで・点とクエリが 2×10^5 個（2 次元累積和の表は作れない）}
acl: [fenwick_tree, lazy_segtree]
verify: [rectangle_sum, area_of_union_of_rectangles]
frequency: B
frequency_evidence: recent 1（abc477_f）・前提として届くページなし・古い ABC 6 問
sections:
  - {title: 考え方（一方の座標で並べ、もう一方をデータ構造で持つ）, anchor: idea}
  - {title: 支配点の数え上げ・長方形内の点の数（4 つの接頭辞の包除、上端での値 − 下端の 1 つ前での値）, anchor: rectangle-count}
  - {title: 区間を 2 次元の点と見る（区間に含まれる区間の数）, anchor: intervals-as-points}
  - {title: 固定幅の窓を動かして区間加算・区間最大（遅延セグメント木）, anchor: window-max}
  - {title: 同じ座標での処理順・閉区間と半開区間・座標圧縮, anchor: boundaries}
  - {title: 長方形の和集合の面積（区間加算・最小値とその個数）, anchor: union-area, level: 黄}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：2 次元の問題を、一方の座標の順にイベント（点・区間の端・クエリ）を並べ、走査線を動かしながらもう一方の座標を BIT・セグメント木で持つ形にする。長方形内の点の数や固定幅の窓の最大を求める。
    - **いつ使うか**：
        - 長方形の中にある点の数・和を多数のクエリで答える
        - 区間 [p, q] に完全に含まれる区間の数
        - 幅 W・高さ D の枠に入る点の最大数
        - 座標が 10^9 まで・点とクエリが 2×10^5 個（2 次元累積和の表は作れない）
    - **計算量**：（執筆時に書く）
    - **前提**：[イベントソートと平面走査の基本](../basics/event-sort.md)、[クエリの先読み](../ds/offline-queries.md)、[遅延セグメント木](../ds/lazy-segment-tree.md)
