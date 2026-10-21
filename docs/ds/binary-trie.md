---
id: binary-trie
title: Binary Trie
aliases: [二分トライ, 2 進 Trie, ビット Trie, XOR Trie, XOR の最小化]
type: technique
field: ds
chapter: そのほかのデータ構造
order: 350
level: 青
kind: [データ構造, ビット演算]
prerequisites: [trie, bit-operations]
related: [bitwise-independence, ordered-set, kth-element, xor-basis]
summary: 整数を 2 進数の上位ビットから Trie に入れ、各ノードに部分木の個数を持たせる。x との XOR の最小・最大、K 番目に小さい値、全体に XOR をかける操作を O(ビット数) で処理する。
complexity: null
signs:
  - {type: phrase, text: x を選んで XOR の最大値を最小にする・集合の中で x との XOR が最小の要素}
  - {type: phrase, text: 追加・削除のたびに、任意の 2 要素の XOR の最小値を答える}
  - {type: phrase, text: 全体に XOR をかけてから K 番目に小さい値}
  - {type: constraint, text: A_i < 2^30 で、追加・削除・質問が合わせて 2×10^5 回程度}
acl: []
verify: [set_xor_min]
frequency: B
frequency_evidence: recent 0・前提として届くページなし・古い ABC 3 問
sections:
  - {title: 作り方（上位ビットから辿る二分木・ノードに個数）, anchor: build}
  - {title: XOR の最小・最大（同じ側を優先して降りる）, anchor: xor-min-max}
  - {title: K 番目と全体への XOR（ビットごとの反転フラグ）, anchor: kth-and-global-xor}
  - {title: 明示的に作らない Binary Trie（上位ビットで分ける再帰）, anchor: implicit}
  - {title: 使い分け（最小の XOR の組はソート順で隣り合う組でも求まる、XOR で作れる値の集合は XOR 基底）, anchor: choosing}
  - {title: 落とし穴（ノード数＝要素数 × ビット数。配列で確保する）, anchor: pitfalls}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：整数を 2 進数の上位ビットから Trie に入れ、各ノードに部分木の個数を持たせる。x との XOR の最小・最大、K 番目に小さい値、全体に XOR をかける操作を O(ビット数) で処理する。
    - **いつ使うか**：
        - x を選んで XOR の最大値を最小にする・集合の中で x との XOR が最小の要素
        - 追加・削除のたびに、任意の 2 要素の XOR の最小値を答える
        - 全体に XOR をかけてから K 番目に小さい値
        - A_i < 2^30 で、追加・削除・質問が合わせて 2×10^5 回程度
    - **計算量**：（執筆時に書く）
    - **前提**：[Trie](../string/trie.md)、[bit 演算の基本と XOR の性質](../basics/bit-operations.md)
