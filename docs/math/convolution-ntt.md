---
id: convolution-ntt
title: 畳み込みの使い方
aliases: [畳み込み, convolution, 多項式の積, ACL の convolution, convolution_ll, ずらしたときの一致数, 全シフトのハミング距離, ワイルドカード照合]
type: technique
field: math
chapter: 畳み込みと多項式
order: 360
level: 青
kind: [畳み込み・多項式]
prerequisites: [mod-arithmetic]
related: [fft-ntt, online-convolution, generating-function-counting, hadamard-transform, rolling-hash, z-algorithm]
summary: c_k = Σ_{i+j=k} a_i b_j（多項式の積）を ACL の convolution で O(N log N) で求める。和が k になる組の数や、ずらしたときの一致数を全ての k について一度に数える。
complexity: null
signs:
  - {type: phrase, text: 全ての k について、和が k になる組の数を求める}
  - {type: phrase, text: 列をずらしたときの一致数・不一致の数を、全てのずらし方について求める}
  - {type: phrase, text: 'ワイルドカード（?）を含むパターンの照合'}
  - {type: constraint, text: 値の範囲や列の長さが 10^5〜10^6 程度で、組の全探索 O(N²) が間に合わない}
  - {type: shape, text: 'c_k = Σ_{i+j=k} a_i b_j の形の和'}
acl: [convolution, convolution_ll]
verify: [convolution_mod, wildcard_pattern_matching]
frequency: B
frequency_evidence: recent 1（abc471_g）・前提として 5 ページに届く（直接 4）・古い ABC 4 問
sections:
  - {title: i + j = k の形に言い換える（出現回数の配列）, anchor: sum-pairs}
  - {title: i − j = k の形は片方を反転する, anchor: reverse}
  - {title: 結果の長さと mod（998244353 での値しか返らない）, anchor: length-mod}
  - {title: 整数のまま・mod 10^9+7 で欲しいとき（convolution_ll）, anchor: convolution-ll}
  - {title: 文字列の照合：ずらしたときの一致数・ハミング距離・ワイルドカード, anchor: string-matching, level: 黄}
  - {title: bit ごと・文字ごとに分けて畳み込む（OR の和など）, anchor: split-by-bit, level: 黄}
  - {title: ACL の convolution の要件（法の形と長さ）, anchor: acl}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：c_k = Σ_{i+j=k} a_i b_j（多項式の積）を ACL の convolution で O(N log N) で求める。和が k になる組の数や、ずらしたときの一致数を全ての k について一度に数える。
    - **いつ使うか**：
        - 全ての k について、和が k になる組の数を求める
        - 列をずらしたときの一致数・不一致の数を、全てのずらし方について求める
        - ワイルドカード（?）を含むパターンの照合
        - 値の範囲や列の長さが 10&#94;5〜10&#94;6 程度で、組の全探索 O(N²) が間に合わない
        - c_k = Σ_{i+j=k} a_i b_j の形の和
    - **計算量**：（執筆時に書く）
    - **前提**：[mod の計算の基本](../math/mod-arithmetic.md)
