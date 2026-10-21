---
id: bitwise-independence
title: bit ごとに独立に考える
aliases: [bit ごとの寄与, 桁ごとに見る, bit ごとに分解, 上位ビットから決める, XOR の和, bitwise decomposition]
type: technique
field: basics
chapter: 計算量と bit 演算
order: 30
level: 水
kind: [ビット演算, 考察]
prerequisites: [bit-operations, contribution]
related: [xor-basis, binary-trie, digit-dp, reformulation]
summary: XOR・AND・OR の結果は bit ごとに独立に決まるので、bit ごとに 0 と 1 の個数を数えて 2^k を掛けて足す。最大化・最小化は上の bit から決め、繰り上がりで bit が干渉する足し算には使えない。
complexity: null
signs:
  - {type: phrase, text: 全ペア・全区間の XOR の総和}
  - {type: phrase, text: AND・OR・XOR の最大化・最小化}
  - {type: phrase, text: x を選んで max(a_i xor x) を最小化する}
  - {type: phrase, text: a + b = a xor b（繰り上がりがない）}
  - {type: constraint, text: A_i < 2^30〜2^60 で、全ペア（N ≤ 2×10^5）の値を集計する}
acl: []
frequency: B
frequency_evidence: recent 0・前提として届くページなし・古い ABC 5 問
sections:
  - {title: bit ごとの寄与（0 の個数 × 1 の個数 × 2^k）, anchor: per-bit-contribution}
  - {title: 区間の XOR は累積 XOR の 0・1 の個数で, anchor: range-xor}
  - {title: 上の bit から決める貪欲（上限は桁 DP の考え方）, anchor: top-down}
  - {title: 上位ビットで 2 つに分けて再帰する, anchor: split-by-top-bit, level: 青}
  - {title: 足し算では使えない理由（繰り上がり）, anchor: addition}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：XOR・AND・OR の結果は bit ごとに独立に決まるので、bit ごとに 0 と 1 の個数を数えて 2^k を掛けて足す。最大化・最小化は上の bit から決め、繰り上がりで bit が干渉する足し算には使えない。
    - **いつ使うか**：
        - 全ペア・全区間の XOR の総和
        - AND・OR・XOR の最大化・最小化
        - x を選んで max(a_i xor x) を最小化する
        - a + b = a xor b（繰り上がりがない）
        - A_i < 2&#94;30〜2&#94;60 で、全ペア（N ≤ 2×10&#94;5）の値を集計する
    - **計算量**：（執筆時に書く）
    - **前提**：[bit 演算の基本と XOR の性質](../basics/bit-operations.md)、[主客転倒・寄与](../thinking/contribution.md)
