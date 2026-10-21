---
id: xor-basis
title: XOR 基底
aliases: [XOR basis, 線形基底, linear basis, F2 の基底, 部分集合の XOR, XOR で作れる値, 閉路基底, サイクル基底, サイクル空間, XOR 最短路]
type: technique
field: math
chapter: 行列と線形代数
order: 340
level: 黄
kind: [線形代数・行列, ビット演算]
prerequisites: [bit-operations]
related: [gaussian-elimination, binary-trie, bitwise-independence, nim, dfs, extended-dijkstra]
summary: 整数の集合から XOR で作れる値の全体を、最上位 bit が互いに異なる r 個の基底で表す。作れる値は 2^r 種類で、最大値は上の bit から貪欲に、K 番目に小さい値は簡約した基底から求まる。
complexity: null
signs:
  - {type: phrase, text: 部分集合（部分列）の XOR として作れる値の個数・最大値・K 番目}
  - {type: phrase, text: 全ての値を XOR で作れるように最小コストで選ぶ}
  - {type: phrase, text: 経路の重みが辺の重みの XOR で、同じ辺を何度通ってもよい（ウォーク）}
  - {type: constraint, text: A_i < 2^60 で N ≤ 10^5 程度}
acl: []
verify: [intersection_of_f2_vector_spaces]
frequency: B
frequency_evidence: recent 1（abc451_g）・前提として届くページなし・古い ABC 4 問
sections:
  - {title: 基底への挿入（最上位 bit で掃き出す。1 要素 O(bit 数)）, anchor: insert}
  - {title: 作れる値の個数 2^r と作り方の数 2^(n − r), anchor: count}
  - {title: XOR の最大値は上の bit から貪欲に決めてよい理由, anchor: max}
  - {title: 簡約した基底と K 番目に小さい値, anchor: kth}
  - {title: コストの小さい順に基底へ入れる貪欲（線形マトロイド）, anchor: min-cost}
  - {title: グラフのウォークの XOR（全域木の根からの XOR と、閉路の XOR の基底）, anchor: xor-walk}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：整数の集合から XOR で作れる値の全体を、最上位 bit が互いに異なる r 個の基底で表す。作れる値は 2^r 種類で、最大値は上の bit から貪欲に、K 番目に小さい値は簡約した基底から求まる。
    - **いつ使うか**：
        - 部分集合（部分列）の XOR として作れる値の個数・最大値・K 番目
        - 全ての値を XOR で作れるように最小コストで選ぶ
        - 経路の重みが辺の重みの XOR で、同じ辺を何度通ってもよい（ウォーク）
        - A_i < 2^60 で N ≤ 10^5 程度
    - **計算量**：（執筆時に書く）
    - **前提**：[bit 演算の基本と XOR の性質](../basics/bit-operations.md)
