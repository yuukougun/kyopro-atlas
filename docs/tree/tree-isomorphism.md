---
id: tree-isomorphism
title: 木の同型判定と木のハッシュ
aliases: [木の同型, 木のハッシュ, AHU, rooted tree hash, tree isomorphism]
type: overview
field: tree
chapter: 木全体の形
order: 140
level: 発展
kind: [木, ハッシュ・乱択]
prerequisites: [tree-diameter]
related: [hashing-for-sets, rolling-hash, static-top-tree, tree-traversal]
summary: 根付き木の同型は、葉から順に「子の部分木の名前の多重集合」に名前を付ける AHU 法か、多重集合のハッシュで判定する。根のない木は中心（1〜2 個）を根にして比べる。
complexity: null
signs:
  - {type: phrase, text: 形が同じ部分木の種類数}
  - {type: phrase, text: 2 つの木が同じ形か（根あり・根なし）}
acl: []
verify: [rooted_tree_isomorphism_classification]
frequency: C
frequency_evidence: recent 0・前提として届くページなし・古い ABC 1 問
sections:
  - {title: AHU 法（子の名前の多重集合に名前を付ける）, anchor: ahu}
  - {title: 木のハッシュと衝突しにくい設計, anchor: tree-hash}
  - {title: 根のない木は中心を根にする, anchor: unrooted}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：根付き木の同型は、葉から順に「子の部分木の名前の多重集合」に名前を付ける AHU 法か、多重集合のハッシュで判定する。根のない木は中心（1〜2 個）を根にして比べる。
    - **いつ使うか**：
        - 形が同じ部分木の種類数
        - 2 つの木が同じ形か（根あり・根なし）
    - **計算量**：（執筆時に書く）
    - **前提**：[木の直径と最遠点](../tree/tree-diameter.md)
