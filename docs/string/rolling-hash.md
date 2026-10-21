---
id: rolling-hash
title: ローリングハッシュ
aliases: [ロリハ, 多項式ハッシュ, Rabin-Karp, 文字列のハッシュ, 部分文字列のハッシュ, ハッシュのセグ木, rolling hash]
type: technique
field: string
chapter: ハッシュ
order: 30
level: 水
kind: [文字列, ハッシュ・乱択]
prerequisites: [mod-arithmetic, prefix-sum, string-basics]
related: [hash-safety, hashing-for-sets, z-algorithm, palindrome#manacher, suffix-array, segment-tree-monoids, binary-search-answer, convolution-ntt#string-matching, method-comparison#strings]
summary: 文字列を B 進数の値（mod p）とみなし、接頭辞のハッシュから任意の部分文字列のハッシュを O(1) で取り出して、部分文字列どうしの一致を確率的に判定する。二分探索と組めば LCP や辞書順の比較もできる。
complexity: null
signs:
  - {type: phrase, text: 部分文字列どうしが等しいかを大量に判定する}
  - {type: phrase, text: 重ならずに 2 回現れる部分文字列の最大の長さ}
  - {type: phrase, text: 1 文字の更新と、区間が回文か（一致するか）のクエリ}
  - {type: constraint, text: N ≤ 10^5〜10^6 で、任意の 2 区間の一致判定が Q ≤ 2×10^5 回}
acl: [segtree]
verify: []
frequency: B
frequency_evidence: recent 0・前提として 1 ページに届く（直接 1）・古い ABC 7 問
sections:
  - {title: '多項式ハッシュと部分文字列の取り出し（h[r] − h[l]·B^(r−l)）', anchor: polynomial-hash}
  - {title: なぜ衝突しにくいか（0 でない多項式の根は次数以下）, anchor: collision-bound}
  - {title: 推奨する設計：mod 2^61−1 と実行時に乱択した基数（理由は hash-safety）, anchor: recommended-design}
  - {title: 連結のハッシュと逆向きのハッシュ（回文判定）, anchor: concat-and-reverse}
  - {title: ハッシュ＋二分探索：LCP・辞書順の比較・最長の繰り返し, anchor: hash-lcp-binary-search}
  - {title: 'セグ木に載せるハッシュ：（ハッシュ, B^長さ）の組で更新ありの一致・回文判定', anchor: hash-segment-tree, level: 青}
  - {title: ハッシュで代用できる場面とできない場面（Z・Manacher・SA・畳み込みとの使い分け）, anchor: when-to-use}
  - {title: 実装の落とし穴（文字を 0 にしない・負の余り・積のオーバーフロー・長さをそろえる）, anchor: pitfalls}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：文字列を B 進数の値（mod p）とみなし、接頭辞のハッシュから任意の部分文字列のハッシュを O(1) で取り出して、部分文字列どうしの一致を確率的に判定する。二分探索と組めば LCP や辞書順の比較もできる。
    - **いつ使うか**：
        - 部分文字列どうしが等しいかを大量に判定する
        - 重ならずに 2 回現れる部分文字列の最大の長さ
        - 1 文字の更新と、区間が回文か（一致するか）のクエリ
        - N ≤ 10&#94;5〜10&#94;6 で、任意の 2 区間の一致判定が Q ≤ 2×10&#94;5 回
    - **計算量**：（執筆時に書く）
    - **前提**：[mod の計算の基本](../math/mod-arithmetic.md)、[累積和](../basics/prefix-sum.md)、[文字列の基本操作と辞書順](../string/string-basics.md)
