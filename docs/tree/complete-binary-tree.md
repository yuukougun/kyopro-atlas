---
id: complete-binary-tree
title: 完全二分木
aliases: [ヒープ番号, 親は i/2, K 分木, heap numbering, perfect binary tree]
type: technique
field: tree
chapter: 木の基礎
order: 70
level: 基礎
kind: [木, ビット演算]
prerequisites: [tree-basics, bit-operations]
related: [lca, tree-path, segment-tree]
summary: 頂点 i の子が 2i と 2i+1、親が ⌊i/2⌋ の木は深さが log N 程度しかないので、N が 10^18 でも祖先を全部たどれる。番号の 2 進表記が根からの道順を表し、LCA と距離も番号だけで求まる。
complexity: null
signs:
  - {type: phrase, text: 頂点 i と ⌊i/2⌋ を結ぶ・L/R/U の移動の列}
  - {type: constraint, text: N ≤ 10^18 の木}
acl: []
frequency: B
frequency_evidence: recent 1（abc465_d）・前提として届くページなし・古い ABC 2 問
sections:
  - {title: 番号の 2 進表記と根からの道順, anchor: binary-path}
  - {title: L/R/U の移動はスタックで打ち消す, anchor: lru-moves}
  - {title: 番号だけで LCA を求める（大きい方を 2 で割る）, anchor: lca-by-index}
  - {title: K 分木への一般化, anchor: k-ary}
  - {title: 距離 K の頂点の数（部分木の深さの範囲を N で切る）, anchor: count-at-distance, level: 青}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：頂点 i の子が 2i と 2i+1、親が ⌊i/2⌋ の木は深さが log N 程度しかないので、N が 10^18 でも祖先を全部たどれる。番号の 2 進表記が根からの道順を表し、LCA と距離も番号だけで求まる。
    - **いつ使うか**：
        - 頂点 i と ⌊i/2⌋ を結ぶ・L/R/U の移動の列
        - N ≤ 10^18 の木
    - **計算量**：（執筆時に書く）
    - **前提**：[木の基本性質と表現](../tree/tree-basics.md)、[bit 演算の基本と XOR の性質](../basics/bit-operations.md)
