---
id: fenwick-tree
title: BIT（Fenwick Tree）
aliases: [Binary Indexed Tree, フェニック木, fenwick_tree]
type: technique
field: ds
chapter: 区間クエリ
order: 150
level: 水
kind: [データ構造, 区間クエリ]
prerequisites: [prefix-sum, bit-operations]
related: [segment-tree, inversion-number, kth-element, coordinate-compression, sweep-line-2d, offline-queries, imos, segment-tree-on-values]
summary: 一点への加算と接頭辞の和（したがって区間の和）を、どちらも O(log N) で行う。区間の和は 2 つの接頭辞の差なので演算に逆元が要り、値を添字にして個数を数える使い方が多い。
complexity: null
signs:
  - {type: phrase, text: 一点の値の更新と区間の和の質問が交互に来る}
  - {type: phrase, text: i より前にある x 以下の要素の個数}
  - {type: shape, text: 'Σ_{j<i} [A_j ≤ A_i] のように、前にある要素のうち条件を満たすものの個数・和を i ごとに足す'}
  - {type: constraint, text: 'N, Q ≤ 2×10^5 で更新があり、累積和を毎回作り直すと間に合わない'}
acl: [fenwick_tree]
verify: [point_add_range_sum, static_range_sum]
frequency: A
frequency_evidence: recent 2（abc452_f・abc467_g）・前提として 13 ページに届く（直接 5）・古い ABC 6 問
sections:
  - {title: 何ができるか（一点加算・接頭辞和。区間和は 2 つの接頭辞の差なので逆元が要る）, anchor: what-it-does}
  - {title: '保つ性質（1-indexed で、t[i] は区間 (i − lowbit(i), i] の和。lowbit(i) = i & −i）', anchor: invariants}
  - {title: 各操作の手順（add は i += lowbit(i) で上へ、sum は i −= lowbit(i) で下へ。線形時間の構築）, anchor: operations}
  - {title: 境界（内部は 1-indexed・外部は 0-indexed の半開区間、i = 0 の add は止まらない、ACL は符号なし整数で持つ）, anchor: boundaries}
  - {title: 値を添字にして数える（座標圧縮と組む）, anchor: count-by-value}
  - {title: 変種（区間加算・一点取得は差分の BIT、区間加算・区間和は BIT 2 本、2 次元 BIT、増える更新だけなら接頭辞の max）, anchor: variants}
  - {title: BIT 上の二分探索（→ K 番目の値を求めるデータ構造）, anchor: binary-search}
  - {title: 使い分け（更新がなければ累積和、min・max や非可換な演算ならセグメント木）, anchor: choosing}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：一点への加算と接頭辞の和（したがって区間の和）を、どちらも O(log N) で行う。区間の和は 2 つの接頭辞の差なので演算に逆元が要り、値を添字にして個数を数える使い方が多い。
    - **いつ使うか**：
        - 一点の値の更新と区間の和の質問が交互に来る
        - i より前にある x 以下の要素の個数
        - Σ_{j&lt;i} [A_j ≤ A_i] のように、前にある要素のうち条件を満たすものの個数・和を i ごとに足す
        - N, Q ≤ 2×10^5 で更新があり、累積和を毎回作り直すと間に合わない
    - **計算量**：（執筆時に書く）
    - **前提**：[累積和](../basics/prefix-sum.md)、[bit 演算の基本と XOR の性質](../basics/bit-operations.md)
