---
id: segment-tree
title: セグメント木
aliases: [セグ木, segtree, Segment Tree, RMQ, 非再帰セグ木, 区間最小値, 文字の集合を持つセグ木]
type: technique
field: ds
chapter: 区間クエリ
order: 180
level: 水
kind: [データ構造, 区間クエリ]
prerequisites: [prefix-sum]
related: [fenwick-tree, segment-tree-monoids, segment-tree-binary-search, lazy-segment-tree, sparse-table, segment-tree-on-values, complete-binary-tree, acl-reading#segtree-args, dp-segment-tree, rolling-hash#hash-segment-tree, cht]
summary: 結合律と単位元を持つ演算（モノイド）が載った列で、一点の更新と区間の総積（和・最小・最大・gcd など）の取得を、どちらも O(log N) で行う。演算は可換でなくてよい。
complexity: null
signs:
  - {type: phrase, text: 配列の値を書き換えながら、区間の最小値（最大値・gcd）を何度も答える}
  - {type: phrase, text: 1 文字の更新と、区間に現れる文字の種類数}
  - {type: constraint, text: 'N, Q ≤ 2×10^5〜5×10^5 で、一点の更新と区間の質問が交互に来る'}
acl: [segtree]
verify: [point_set_range_composite]
frequency: A
frequency_evidence: recent 4（abc460_g・abc461_e・abc467_f・abc476_e）・前提として 19 ページに届く（直接 10）・古い ABC 4 問
sections:
  - {title: '何ができるか（モノイド (S, op, e)・一点更新・区間取得）', anchor: what-it-does}
  - {title: なぜ O(log N) か（区間を各段で高々 2 個のノードに分ける。結合律と単位元の役割）, anchor: complexity}
  - {title: '保つ性質（d[k] は k が表す区間の総積、葉は d[size + i]、余った葉は e()）', anchor: invariants}
  - {title: 各操作の手順（set は葉から根へ作り直す、prod は左右の端から 1 段ずつ上がり、左は左から右へ・右は右から左へ積む）, anchor: operations}
  - {title: '境界（半開区間 [l, r)・l = r なら e()・0-indexed・e() の選び方と INF のあふれ）', anchor: boundaries}
  - {title: 再帰型と非再帰型, anchor: recursive-vs-iterative}
  - {title: 文字列へのクエリ（文字ごとの BIT・文字の集合を 26 ビットの OR で持つ）, anchor: string-queries}
  - {title: DP の配列を載せる（→ DP の章のセグメント木による遷移の高速化）, anchor: dp}
  - {title: 使い分け（和だけなら BIT、更新がなければ累積和・Sparse Table、区間の更新があるなら遅延セグメント木）, anchor: choosing}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：結合律と単位元を持つ演算（モノイド）が載った列で、一点の更新と区間の総積（和・最小・最大・gcd など）の取得を、どちらも O(log N) で行う。演算は可換でなくてよい。
    - **いつ使うか**：
        - 配列の値を書き換えながら、区間の最小値（最大値・gcd）を何度も答える
        - 1 文字の更新と、区間に現れる文字の種類数
        - N, Q ≤ 2×10&#94;5〜5×10&#94;5 で、一点の更新と区間の質問が交互に来る
    - **計算量**：（執筆時に書く）
    - **前提**：[累積和](../basics/prefix-sum.md)
