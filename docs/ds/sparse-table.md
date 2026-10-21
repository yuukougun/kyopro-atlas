---
id: sparse-table
title: Sparse Table
aliases: [スパーステーブル, ST 表, 静的 RMQ, Disjoint Sparse Table]
type: technique
field: ds
chapter: 区間クエリ
order: 240
level: 青
kind: [データ構造, 区間クエリ, ダブリング・分割統治]
prerequisites: [doubling]
related: [segment-tree, lca, prefix-sum, suffix-array]
summary: 更新のない列で、冪等な演算（min・max・gcd・and・or）の区間クエリに、前処理 O(N log N)・質問 O(1) で答える。長さ 2^k の区間の答えを持ち、質問は重なってよい 2 つの区間で覆う。
complexity: null
signs:
  - {type: phrase, text: 配列が変わらず、区間の最小値・最大値・gcd を非常に多く聞かれる}
  - {type: constraint, text: クエリが 10^6 級で、1 回 O(1) で答えたい}
acl: []
verify: [staticrmq]
frequency: C
frequency_evidence: recent 0・前提として届くページなし・古い ABC 1 問
sections:
  - {title: 何ができるか（静的・冪等な演算なら O(1)）, anchor: what-it-does}
  - {title: なぜ重なってよいか（冪等）と k = ⌊log₂ L⌋, anchor: idempotent}
  - {title: '作り方（st[k][i] = op(st[k−1][i], st[k−1][i + 2^(k−1)])、log の表）', anchor: build}
  - {title: 使い分け（更新があるならセグメント木、和なら累積和）, anchor: choosing}
  - {title: 冪等でない演算（2 べきに分けて O(log N)、Disjoint Sparse Table）, anchor: disjoint-sparse-table, level: 発展}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：更新のない列で、冪等な演算（min・max・gcd・and・or）の区間クエリに、前処理 O(N log N)・質問 O(1) で答える。長さ 2^k の区間の答えを持ち、質問は重なってよい 2 つの区間で覆う。
    - **いつ使うか**：
        - 配列が変わらず、区間の最小値・最大値・gcd を非常に多く聞かれる
        - クエリが 10^6 級で、1 回 O(1) で答えたい
    - **計算量**：（執筆時に書く）
    - **前提**：[ダブリング](../basics/doubling.md)
