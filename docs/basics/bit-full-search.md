---
id: bit-full-search
title: bit 全探索と順列全探索
aliases: [ビット全探索, 部分集合の全列挙, 2^N 全探索, 3 進全探索, next_permutation, N! 全探索, bit brute force]
type: technique
field: basics
chapter: 全探索
order: 50
level: 基礎
kind: [全探索, ビット演算]
prerequisites: [brute-force, bit-operations]
related: [recursive-enumeration, meet-in-the-middle, bit-dp, small-graph-brute-force]
summary: N ≤ 20 程度なら部分集合 2^N 通りを整数の各 bit で表して全部試し、N ≤ 8〜10 なら順列 N! 通りを next_permutation で全部試す。片側だけを全探索して残りを貪欲で決める型もよく出る。
complexity: null
signs:
  - {type: constraint, text: N ≤ 15〜20 で各要素を「選ぶ／選ばない」}
  - {type: constraint, text: N ≤ 8〜10 で並び順・割り当て・頂点の対応を決める}
  - {type: phrase, text: スイッチの on/off、区切る／区切らない}
  - {type: constraint, text: 各要素が 3 択で N ≤ 12 程度（3^N 通り）}
  - {type: phrase, text: 2 つのグラフが頂点の付け替えで一致するか}
acl: []
frequency: A
frequency_evidence: recent 0・前提として 14 ページに届く（直接 6）・古い ABC 10 問
sections:
  - {title: bit 全探索の書き方（mask の i ビット目で要素 i を選ぶ）, anchor: bitmask}
  - {title: k 進の全探索（3^N）, anchor: base-k}
  - {title: 決めてから整合性を確かめる型, anchor: assume-and-check}
  - {title: 片側を bit で決めて残りは貪欲, anchor: half-greedy, level: 水}
  - {title: 順列全探索と next_permutation（昇順から始める・重複要素）, anchor: permutations}
  - {title: 落とし穴（1 << 31 のあふれ・== と & の優先順位）, anchor: pitfalls}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：N ≤ 20 程度なら部分集合 2^N 通りを整数の各 bit で表して全部試し、N ≤ 8〜10 なら順列 N! 通りを next_permutation で全部試す。片側だけを全探索して残りを貪欲で決める型もよく出る。
    - **いつ使うか**：
        - N ≤ 15〜20 で各要素を「選ぶ／選ばない」
        - N ≤ 8〜10 で並び順・割り当て・頂点の対応を決める
        - スイッチの on/off、区切る／区切らない
        - 各要素が 3 択で N ≤ 12 程度（3^N 通り）
        - 2 つのグラフが頂点の付け替えで一致するか
    - **計算量**：（執筆時に書く）
    - **前提**：[全探索の設計](../basics/brute-force.md)、[bit 演算の基本と XOR の性質](../basics/bit-operations.md)
