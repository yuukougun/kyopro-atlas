---
id: difference-sequence
title: 差分列への言い換え
aliases: [差分列, 差分で言い換える, 区間 ±1 の最小回数, 区間操作を 2 点の操作に, difference sequence]
type: technique
field: basics
chapter: 累積和といもす法
order: 160
level: 黄
kind: [累積和・差分, 考察]
prerequisites: [imos]
related: [reformulation, invariant, lazy-segment-tree, run-length-encoding]
summary: 区間に ±1 する操作の最小回数や可否を、隣接差の列（差分列）の 2 点の操作に言い換えて解く。狭義の条件は a_i − i で広義に直し、回文の条件は左右の差の列に直してから差分を取る。
complexity: null
signs:
  - {type: phrase, text: 区間に +1・−1 する操作の最小回数・可否}
  - {type: phrase, text: 数列を単調にする・回文にするための最小の操作回数}
  - {type: phrase, text: 円形に並んだ箱から一斉に取り除く操作で空にできるか}
  - {type: shape, text: 操作が区間に一律の値を足す形で、隣接差では 2 か所だけが変わる}
acl: []
frequency: A
frequency_evidence: recent 2（abc454_f・abc459_f）・前提として届くページなし・古い ABC 0 問
sections:
  - {title: 区間の操作を差分列の 2 点の操作に直す, anchor: to-point-operations}
  - {title: 最小回数・可否を差分列の正負で考える, anchor: min-operations}
  - {title: 狭義の条件は a_i − i で広義に直してから差分を取る, anchor: strict-to-weak}
  - {title: 回文にする操作は左右の差の列に直してから差分を取る, anchor: palindrome}
  - {title: 円環で一斉に行う操作, anchor: circular}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：区間に ±1 する操作の最小回数や可否を、隣接差の列（差分列）の 2 点の操作に言い換えて解く。狭義の条件は a_i − i で広義に直し、回文の条件は左右の差の列に直してから差分を取る。
    - **いつ使うか**：
        - 区間に +1・−1 する操作の最小回数・可否
        - 数列を単調にする・回文にするための最小の操作回数
        - 円形に並んだ箱から一斉に取り除く操作で空にできるか
        - 操作が区間に一律の値を足す形で、隣接差では 2 か所だけが変わる
    - **計算量**：（執筆時に書く）
    - **前提**：[いもす法](../basics/imos.md)
