---
id: segment-tree-beats
title: Segment Tree Beats
aliases: [beats, Ji Driver Segment Tree, 吉司机线段树, 区間 chmin 区間和, 区間 chmin・chmax]
type: overview
field: ds
chapter: 区間クエリ
order: 250
level: 発展
kind: [データ構造, 区間クエリ]
prerequisites: [lazy-segment-tree]
related: [interval-set, lazy-segment-tree-patterns]
summary: 区間 chmin・chmax と区間和のように遅延セグメント木の条件を満たさない更新を、ならし計算量で処理する。効かないなら止める・最大値だけ変わるならタグ・それ以外は子へ、の 3 つに分ける。
complexity: null
signs:
  - {type: phrase, text: 区間 chmin・chmax と区間和を同時に答える}
  - {type: phrase, text: 区間の各要素を x で割る（切り捨て）操作と区間和}
acl: []
verify: [range_chmin_chmax_add_range_sum]
frequency: C
frequency_evidence: recent 0・前提として届くページなし・古い ABC 1 問
sections:
  - {title: 何ができるか（遅延セグメント木に載らない更新）, anchor: what-it-does}
  - {title: ノードに持つもの（最大値・真に 2 番目の最大値・最大値の個数・和）と 3 つの場合, anchor: node-data}
  - {title: 計算量（chmin と和だけならならし O((N+Q) log N)、区間加算が混ざると log^2）, anchor: complexity}
  - {title: 値が潰れる操作（割り算・mod・平方根）と、区間を set で管理する別解, anchor: shrinking-values}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：区間 chmin・chmax と区間和のように遅延セグメント木の条件を満たさない更新を、ならし計算量で処理する。効かないなら止める・最大値だけ変わるならタグ・それ以外は子へ、の 3 つに分ける。
    - **いつ使うか**：
        - 区間 chmin・chmax と区間和を同時に答える
        - 区間の各要素を x で割る（切り捨て）操作と区間和
    - **計算量**：（執筆時に書く）
    - **前提**：[遅延セグメント木](../ds/lazy-segment-tree.md)
