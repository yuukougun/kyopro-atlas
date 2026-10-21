---
id: imos
title: いもす法
aliases: [imos 法, 差分配列, difference array, 2 次元いもす法, 階差, 隣接差, 等差数列の区間加算]
type: technique
field: basics
chapter: 累積和といもす法
order: 150
level: 基礎
kind: [累積和・差分]
prerequisites: [prefix-sum]
related: [difference-sequence, coordinate-compression, event-sort, lazy-segment-tree, tree-imos]
summary: 区間 [l, r) に x を足す操作を D[l] += x、D[r] −= x と記録し、最後に累積和を取って一度に反映する。Q 回の区間加算が O(N + Q) になり、2 次元では長方形の四隅に印を置く。
complexity: null
signs:
  - {type: phrase, text: 区間にまとめて加算し、最後に各点の値を知りたい}
  - {type: phrase, text: 各時刻に何人いるか・ちょうど k 個重なる長さ}
  - {type: phrase, text: 長方形にまとめて加算する（重なった枚数ごとの面積）}
  - {type: phrase, text: 区間に一律の値を足すたびに隣接差の和を答える}
  - {type: phrase, text: '等差数列になっている区間・区間に 1, 2, 3, … を足す'}
  - {type: constraint, text: 'N, Q ≤ 2×10^5 で区間への加算が多数あり、値を読むのは最後だけ'}
acl: []
frequency: A
frequency_evidence: recent 5（abc453_e・abc462_d・abc464_e・abc465_f・abc466_e）・前提として 9 ページに届く（直接 3）・古い ABC 6 問
sections:
  - {title: 1 次元のいもす法（閉区間なら右端 + 1 に −x）, anchor: imos-1d}
  - {title: 座標が大きいとき（座標圧縮・イベントのソート）, anchor: large-coordinates}
  - {title: 区間長ごとの加算に使う, anchor: by-length}
  - {title: 隣接差で見る（区間加算は 2 点の増減・等差数列の区間）, anchor: adjacent-difference}
  - {title: 区間反転を切り替え点 2 つで表す, anchor: range-flip}
  - {title: '2 階の差分（区間に 1, 2, 3, … を足す）', anchor: second-order}
  - {title: 2 次元いもす法（四隅に ±1、横と縦に累積）, anchor: imos-2d}
  - {title: 途中で値を読むなら BIT・遅延セグ木, anchor: online}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：区間 [l, r) に x を足す操作を D[l] += x、D[r] −= x と記録し、最後に累積和を取って一度に反映する。Q 回の区間加算が O(N + Q) になり、2 次元では長方形の四隅に印を置く。
    - **いつ使うか**：
        - 区間にまとめて加算し、最後に各点の値を知りたい
        - 各時刻に何人いるか・ちょうど k 個重なる長さ
        - 長方形にまとめて加算する（重なった枚数ごとの面積）
        - 区間に一律の値を足すたびに隣接差の和を答える
        - 等差数列になっている区間・区間に 1, 2, 3, … を足す
        - N, Q ≤ 2×10^5 で区間への加算が多数あり、値を読むのは最後だけ
    - **計算量**：（執筆時に書く）
    - **前提**：[累積和](../basics/prefix-sum.md)
