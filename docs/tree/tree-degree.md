---
id: tree-degree
title: 木の次数列と Prüfer 列
aliases: [次数列, プリューファー列, Prüfer code, Prüfer sequence, 握手補題, 星, degree sequence]
type: technique
field: tree
chapter: 木の基礎
order: 90
level: 青
kind: [木, 数え上げ]
prerequisites: [leaf-first]
related: [cayley-pruefer, tree-construction, matrix-tree-theorem]
summary: 各次数が 1 以上で和が 2N−2 なら、その次数列の木が必ず作れる。Prüfer 列（最小番号の葉を消して隣を記録する列）が木と一対一に対応し、各頂点の出現回数が次数 − 1 になることが理由である。
complexity: null
signs:
  - {type: phrase, text: 各頂点の次数を決めて木を作る・次数の和が 2N−2}
  - {type: phrase, text: 次数が○以下の木・星や雪の結晶など次数で決まる形}
acl: []
frequency: B
frequency_evidence: recent 0・前提として 1 ページに届く（直接 1）・古い ABC 4 問
sections:
  - {title: 次数だけで分かること（葉の数・星の中心）, anchor: degree-facts}
  - {title: 次数列から木を作れる条件, anchor: realizable}
  - {title: Prüfer 列と木の全単射（出現回数 = 次数 − 1）, anchor: pruefer}
  - {title: 次数を配る最適化, anchor: allocate-degrees}
  - {title: 木の数え上げ（Cayley の公式）は数え上げの章、全域木の個数はグラフの章の行列木定理, anchor: counting-links}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：各次数が 1 以上で和が 2N−2 なら、その次数列の木が必ず作れる。Prüfer 列（最小番号の葉を消して隣を記録する列）が木と一対一に対応し、各頂点の出現回数が次数 − 1 になることが理由である。
    - **いつ使うか**：
        - 各頂点の次数を決めて木を作る・次数の和が 2N−2
        - 次数が○以下の木・星や雪の結晶など次数で決まる形
    - **計算量**：（執筆時に書く）
    - **前提**：[葉から考える](../tree/leaf-first.md)
