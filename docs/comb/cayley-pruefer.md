---
id: cayley-pruefer
title: ラベル付き木の数え上げ
aliases: [Cayley の公式, n^(n−2), 次数を指定した木の数, 頂点にラベルのある木の個数, Cayley's formula]
type: technique
field: comb
chapter: 置換・分割・木の数え上げ
order: 300
level: 黄
kind: [数え上げ, 木]
prerequisites: [multinomial-coefficient, tree-degree]
related: [counting-bijection, matrix-tree-theorem, generating-function-counting, binomial-identities]
summary: 頂点にラベルのある n 頂点の木は n^(n−2) 個で、Prüfer 列に頂点 i がちょうど（次数 − 1）回現れることから、次数を指定した木は (n−2)!/Π(d_i − 1)! 個になる。次数列ごとに数えて総和を取る問題で使う。
complexity: null
signs:
  - {type: phrase, text: 頂点にラベルのある木の個数}
  - {type: phrase, text: 各頂点の次数を指定（制限）した木の個数}
  - {type: phrase, text: すべての木（すべての次数列）についての総和}
acl: []
frequency: C
frequency_evidence: recent 0・前提として届くページなし・古い ABC 2 問
sections:
  - {title: Cayley の公式 n^(n−2)（Prüfer 列の全単射から）, anchor: cayley}
  - {title: 次数を指定した木の数（多項係数）, anchor: degree-sequence}
  - {title: 次数列ごとに数えて総和を取る, anchor: sum-over-degrees}
  - {title: 多項式（母関数）と組み合わせる, anchor: with-polynomials, level: 発展}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：頂点にラベルのある n 頂点の木は n^(n−2) 個で、Prüfer 列に頂点 i がちょうど（次数 − 1）回現れることから、次数を指定した木は (n−2)!/Π(d_i − 1)! 個になる。次数列ごとに数えて総和を取る問題で使う。
    - **いつ使うか**：
        - 頂点にラベルのある木の個数
        - 各頂点の次数を指定（制限）した木の個数
        - すべての木（すべての次数列）についての総和
    - **計算量**：（執筆時に書く）
    - **前提**：[多項係数](../comb/multinomial-coefficient.md)、[木の次数列と Prüfer 列](../tree/tree-degree.md)
