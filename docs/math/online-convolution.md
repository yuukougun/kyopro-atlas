---
id: online-convolution
title: 分割統治 FFT・オンライン畳み込み
aliases: [online convolution, relaxed convolution, 多項式の積の分割統治, FFT DP, 多項式で DP]
type: overview
field: math
chapter: 畳み込みと多項式
order: 390
level: 発展
kind: [畳み込み・多項式, DP, ダブリング・分割統治]
prerequisites: [convolution-ntt]
related: [divide-and-conquer, fps-basics, dp-speedup-overview]
summary: 多数の多項式の積を次数の小さいものから2つずつ掛けて O(N log² N) で求める。dp[i] が dp[0..i−1] と既知の列の畳み込みで決まるときは、左半分を確定させてから右半分へ寄与を足す分割統治で求める。
complexity: null
signs:
  - {type: phrase, text: Π(1 + a_i x) のような多数の一次式の積の係数}
  - {type: shape, text: 'dp[i] = Σ_{j<i} dp[j]·g[i−j] のように、dp が自分より前の値との畳み込みで決まる'}
  - {type: shape, text: 遷移が「和が s になる組の数」の形（多項式の積）}
acl: [convolution]
verify: []
frequency: B
frequency_evidence: recent 1（abc462_g）・前提として届くページなし・古い ABC 3 問
sections:
  - {title: 多数の多項式の積（次数の小さいものから掛ける・分割統治）, anchor: product-of-many}
  - {title: DP の遷移を多項式の積とみる, anchor: dp-as-polynomial}
  - {title: オンライン畳み込み（左半分を確定させてから右半分へ寄与を足す）, anchor: online}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：多数の多項式の積を次数の小さいものから2つずつ掛けて O(N log² N) で求める。dp[i] が dp[0..i−1] と既知の列の畳み込みで決まるときは、左半分を確定させてから右半分へ寄与を足す分割統治で求める。
    - **いつ使うか**：
        - Π(1 + a_i x) のような多数の一次式の積の係数
        - dp[i] = Σ_{j&lt;i} dp[j]·g[i−j] のように、dp が自分より前の値との畳み込みで決まる
        - 遷移が「和が s になる組の数」の形（多項式の積）
    - **計算量**：（執筆時に書く）
    - **前提**：[畳み込みの使い方](../math/convolution-ntt.md)
