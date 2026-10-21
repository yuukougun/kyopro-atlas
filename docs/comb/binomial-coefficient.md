---
id: binomial-coefficient
title: 二項係数の意味と性質
aliases: [二項係数, nCr, パスカルの三角形, 辞書順 K 番目の組合せ, 組合せの順位, binomial coefficient]
type: technique
field: comb
chapter: 数え上げの基礎
order: 20
level: 基礎
kind: [数え上げ]
prerequisites: [counting-basics]
related: [binomial-precompute, stars-and-bars, lattice-paths, binomial-identities, dp-reconstruction, lexicographic-greedy]
summary: n 個から k 個を選ぶ数 C(n,k) を、選び方・1 が k 個の 0/1 列・格子路の 3 つの意味で使い分ける。パスカルの漸化式と対称性、範囲外を 0 とする約束を使い、辞書順 K 番目の組合せも作れる。
complexity: null
signs:
  - {type: phrase, text: N 個から K 個を選ぶ方法の数}
  - {type: phrase, text: 0 と 1 の列で 1 がちょうど K 個のもの}
  - {type: phrase, text: 辞書順で K 番目の並べ方・与えられた並べ方が何番目か}
  - {type: constraint, text: N ≤ 60 程度で、mod を取らない正確な値を求める}
acl: []
frequency: A
frequency_evidence: recent 1（abc476_g）・前提として 28 ページに届く（直接 5）・古い ABC 3 問
sections:
  - {title: 3 つの意味（選ぶ・0/1 列・格子路）, anchor: meanings}
  - {title: パスカルの漸化式と対称性, anchor: pascal}
  - {title: k < 0・k > n を 0 とする約束, anchor: out-of-range}
  - {title: mod を取らないときの大きさとオーバーフロー, anchor: overflow}
  - {title: 辞書順 K 番目の組合せと順位, anchor: kth}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：n 個から k 個を選ぶ数 C(n,k) を、選び方・1 が k 個の 0/1 列・格子路の 3 つの意味で使い分ける。パスカルの漸化式と対称性、範囲外を 0 とする約束を使い、辞書順 K 番目の組合せも作れる。
    - **いつ使うか**：
        - N 個から K 個を選ぶ方法の数
        - 0 と 1 の列で 1 がちょうど K 個のもの
        - 辞書順で K 番目の並べ方・与えられた並べ方が何番目か
        - N ≤ 60 程度で、mod を取らない正確な値を求める
    - **計算量**：（執筆時に書く）
    - **前提**：[和・積の法則と順列・組合せ](../comb/counting-basics.md)
