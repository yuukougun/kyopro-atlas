---
id: wavelet-matrix
title: Wavelet Matrix
aliases: [ウェーブレット行列, Wavelet Tree, 区間の K 番目]
type: overview
field: ds
chapter: そのほかのデータ構造
order: 340
level: 発展
kind: [データ構造, 区間クエリ, ビット演算]
prerequisites: [merge-sort-tree, bit-operations]
related: [persistent-data-structures, kth-element]
summary: 区間の K 番目の値・x 未満の個数・和を、オンラインで O(log σ) で答える静的な構造。値を上位ビットから順に安定に 0/1 で振り分けた段を重ね、各段で 0 の個数の累積を持つ。
complexity: null
signs:
  - {type: phrase, text: 区間の K 番目に小さい値をオンラインで答える}
  - {type: phrase, text: 長方形（添字の範囲 × 値の範囲）の中の点の数}
acl: []
verify: [range_kth_smallest]
frequency: C
frequency_evidence: recent 0・前提として届くページなし・古い ABC 2 問
sections:
  - {title: 何ができるか（区間の K 番目・x 未満の個数・和）, anchor: what-it-does}
  - {title: 段の作り方（上位ビットから安定に振り分ける）, anchor: build}
  - {title: ライブラリでの使い方と、マージソート木・永続セグメント木との比較, anchor: usage}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：区間の K 番目の値・x 未満の個数・和を、オンラインで O(log σ) で答える静的な構造。値を上位ビットから順に安定に 0/1 で振り分けた段を重ね、各段で 0 の個数の累積を持つ。
    - **いつ使うか**：
        - 区間の K 番目に小さい値をオンラインで答える
        - 長方形（添字の範囲 × 値の範囲）の中の点の数
    - **計算量**：（執筆時に書く）
    - **前提**：[マージソート木](../ds/merge-sort-tree.md)、[bit 演算の基本と XOR の性質](../basics/bit-operations.md)
