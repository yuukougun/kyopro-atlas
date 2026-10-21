---
id: bit-operations
title: bit 演算の基本と XOR の性質
aliases: [ビット演算, bitwise operations, popcount, submask, 最下位ビット, XOR の打ち消し]
type: technique
field: basics
chapter: 計算量と bit 演算
order: 20
level: 基礎
kind: [ビット演算]
prerequisites: []
related: [bitwise-independence, bit-full-search, cpp-math-functions#bit-functions, xor-basis, subset-enumeration-dp#submask-loop]
summary: XOR の打ち消し（x xor x = 0）、a + b = (a xor b) + 2(a and b)、0〜n の XOR の周期などで式を簡単にする。部分集合の部分集合は s = (s − 1) & m で列挙できる。
complexity: null
signs:
  - {type: phrase, text: XOR・AND・OR が問題文に出る}
  - {type: phrase, text: 自分以外の XOR・同じ値で打ち消す}
  - {type: phrase, text: 2 進表記の 1 の個数}
  - {type: constraint, text: N ≤ 18 程度で、集合とその部分集合の組をすべて調べる（全体で 3^N）}
acl: []
frequency: A
frequency_evidence: recent 1（abc476_g）・前提として 45 ページに届く（直接 13）・古い ABC 4 問
sections:
  - {title: AND・OR・XOR・シフトと演算子の優先順位, anchor: operators}
  - {title: XOR の性質（打ち消し・a + b との関係・0〜n の XOR）, anchor: xor-properties}
  - {title: popcount・最下位ビット, anchor: popcount}
  - {title: 部分集合の部分集合の列挙（3^N）, anchor: submask}
  - {title: 落とし穴（1 << 31 のあふれ・符号付きの右シフト）, anchor: pitfalls}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：XOR の打ち消し（x xor x = 0）、a + b = (a xor b) + 2(a and b)、0〜n の XOR の周期などで式を簡単にする。部分集合の部分集合は s = (s − 1) & m で列挙できる。
    - **いつ使うか**：
        - XOR・AND・OR が問題文に出る
        - 自分以外の XOR・同じ値で打ち消す
        - 2 進表記の 1 の個数
        - N ≤ 18 程度で、集合とその部分集合の組をすべて調べる（全体で 3^N）
    - **計算量**：（執筆時に書く）
    - **前提**：なし
