---
id: binomial-prefix-sum
title: 二項係数の部分和
aliases: [二項係数の累積和, 'Σ_{k≤K} C(n,k)']
type: overview
field: comb
chapter: 二項係数の系統
order: 140
level: 発展
kind: [数え上げ]
prerequisites: [binomial-precompute]
related: [binomial-identities, inclusion-exclusion, mo-algorithm]
summary: 二項係数の部分和 S(n,K) = Σ_{k≤K} C(n,k) を、S(n+1,K) = 2S(n,K) − C(n,K) などの式で (n, K) を 1 ずつ動かしながら更新する。部分和を大量に使う包除の計算で役に立つ。
complexity: null
signs:
  - {type: shape, text: '答えの式に Σ_{k≤K} C(n,k) の形の和が、多くの (n, K) について現れる'}
acl: []
frequency: C
frequency_evidence: recent 0・前提として届くページなし・古い ABC 1 問
sections:
  - {title: 何ができるか, anchor: what}
  - {title: n と K を 1 ずつ動かす更新式, anchor: update}
  - {title: Mo のように動かす順番を工夫する, anchor: order}
  - {title: 包除と組み合わせる例, anchor: with-inclusion-exclusion}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：二項係数の部分和 S(n,K) = Σ_{k≤K} C(n,k) を、S(n+1,K) = 2S(n,K) − C(n,K) などの式で (n, K) を 1 ずつ動かしながら更新する。部分和を大量に使う包除の計算で役に立つ。
    - **いつ使うか**：答えの式に Σ_{k≤K} C(n,k) の形の和が、多くの (n, K) について現れる
    - **計算量**：（執筆時に書く）
    - **前提**：[二項係数の前計算](../comb/binomial-precompute.md)
