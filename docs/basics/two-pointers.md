---
id: two-pointers
title: 尺取り法
aliases: [しゃくとり法, two pointers, 2 ポインタ, スライディングウィンドウ, 固定長の窓]
type: technique
field: basics
chapter: 尺取り法とランレングス圧縮
order: 170
level: 基礎
kind: [尺取り・スライド窓]
prerequisites: [prefix-sum, complexity-estimation]
related: [binary-search, prefix-sum-counting, monotonic-stack#sliding-window-minimum, run-length-encoding]
summary: 区間 [l, r) について、各 l に対する最大（最小）の r が l とともに単調に増えるなら、r を戻さずに動かして全体を O(N) で調べられる。区間を縮めても条件が保たれるかで単調性を見抜く。
complexity: null
signs:
  - {type: phrase, text: 条件を満たす最長（最短）の連続区間・連続区間の個数}
  - {type: phrase, text: 区間を縮めても（広げても）条件が保たれる}
  - {type: phrase, text: 長さ M の範囲に入るものの最大個数}
  - {type: constraint, text: N ≤ 2×10^5 で区間を全部は調べられない}
acl: []
frequency: A
frequency_evidence: recent 5（abc452_f・abc455_g・abc461_d・abc464_f・abc470_g）・前提として 1 ページに届く（直接 1）・古い ABC 4 問
sections:
  - {title: 2 つの型（部分区間も満たす型・より大きい区間も満たす型）, anchor: two-types}
  - {title: 単調性の見抜き方（縮めても保たれるか）, anchor: monotonicity}
  - {title: 空区間・取り除く処理の書き方, anchor: implementation}
  - {title: 固定長の窓をずらす, anchor: fixed-window}
  - {title: 負の値があるとき（累積和＋連想配列へ）, anchor: negative-values}
  - {title: 二分探索との関係（O(N log N) でも解ける）, anchor: vs-binary-search}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：区間 [l, r) について、各 l に対する最大（最小）の r が l とともに単調に増えるなら、r を戻さずに動かして全体を O(N) で調べられる。区間を縮めても条件が保たれるかで単調性を見抜く。
    - **いつ使うか**：
        - 条件を満たす最長（最短）の連続区間・連続区間の個数
        - 区間を縮めても（広げても）条件が保たれる
        - 長さ M の範囲に入るものの最大個数
        - N ≤ 2×10^5 で区間を全部は調べられない
    - **計算量**：（執筆時に書く）
    - **前提**：[累積和](../basics/prefix-sum.md)、[計算量の見積もり](../basics/complexity-estimation.md)
