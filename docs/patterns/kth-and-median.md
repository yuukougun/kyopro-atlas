---
id: kth-and-median
title: K 番目と中央値
aliases: [K 番目, 中央値, メディアン, 上位 K 個, median]
type: pattern
field: patterns
order: 60
level: null
kind: [案内, 二分探索, データ構造]
prerequisites: []
related: [kth-value, binary-search-answer, priority-queue, top-k-multiset, kth-element, segment-tree-on-values, ordered-set, balanced-bst, offline-queries, wavelet-matrix, fractional-binary-search, median-absolute, binomial-coefficient, dp-reconstruction, xor-basis]
summary: K 番目に小さい値・上位 K 個の和・中央値を問う問題で、データの動き方から手法を引ける。構造で保つか、「x 以下が K 個以上か」で答えを二分探索するか、小さい順に取り出すかを選ぶ。
complexity: null
signs:
  - {type: phrase, text: K 番目に小さい（大きい）値を答える}
  - {type: phrase, text: N² 個の積・和・差の中で K 番目}
  - {type: phrase, text: 値の追加・更新のたびに、大きい方から K 個の和を答える}
  - {type: phrase, text: 中央値の最大値・最小値}
  - {type: phrase, text: Σ|x − a_i| を最小にする x}
  - {type: phrase, text: 辞書順で K 番目のもの}
acl: []
sections:
  - {title: 題材の性質, anchor: properties}
  - {title: '候補が多すぎて並べられない → x 以下の個数で答えを二分探索（kth-value, binary-search-answer）', anchor: count-and-search}
  - {title: 値を追加しながら K 番目・上位 K 個 → 優先度付きキュー・2 つの multiset, anchor: streaming}
  - {title: 追加と削除がある K 番目 → BIT 上の二分探索・値を添字にするセグメント木, anchor: dynamic}
  - {title: 小さい方から K 個の解を列挙 → 優先度付きキューで最小を取り出す（kth-value）, anchor: k-best}
  - {title: 区間の K 番目・x 以下の個数 → クエリの先読みと BIT、Wavelet Matrix, anchor: range-kth}
  - {title: 中央値・平均の最大化 → 値を引く・±1 にして符号で判定する二分探索（fractional-binary-search）, anchor: maximize-median}
  - {title: Σ|x − a_i| の最小 → 中央値を選ぶ（median-absolute）, anchor: absolute-sum}
  - {title: 辞書順で K 番目の文字列・順列 → 残りの個数を数えて先頭から決める, anchor: lexicographic-kth}
  - {title: XOR で作れる値の K 番目 → XOR 基底（xor-basis）, anchor: xor-kth}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何のページか**：K 番目に小さい値・上位 K 個の和・中央値を問う問題で、データの動き方から手法を引ける。構造で保つか、「x 以下が K 個以上か」で答えを二分探索するか、小さい順に取り出すかを選ぶ。
    - **いつ使うか**：
        - K 番目に小さい（大きい）値を答える
        - N² 個の積・和・差の中で K 番目
        - 値の追加・更新のたびに、大きい方から K 個の和を答える
        - 中央値の最大値・最小値
        - Σ|x − a_i| を最小にする x
        - 辞書順で K 番目のもの
    - **使い方**：（執筆時に書く）
