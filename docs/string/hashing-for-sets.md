---
id: hashing-for-sets
title: 集合・多重集合のハッシュ
aliases: [Zobrist hashing, 集合のハッシュ, 多重集合のハッシュ, XOR ハッシュ, 和のハッシュ, 乱択ハッシュ, 並べ替えて一致するか]
type: technique
field: string
chapter: ハッシュ
order: 40
level: 水
kind: [ハッシュ・乱択, 累積和・差分]
prerequisites: [prefix-sum, bit-operations]
related: [rolling-hash, hash-safety, randomized, fenwick-tree, prime-exponent-vector, parity]
summary: 値ごとに独立な 64 ビットの乱数を割り当て、集合は XOR、多重集合は和で表すと、2 つの集合が等しいかを順序に関係なく O(1) で比べられる。累積と組めば、区間どうしが並べ替えで一致するかも判定できる。
complexity: null
signs:
  - {type: phrase, text: 先頭 x 項の集合と先頭 y 項の集合が等しいか}
  - {type: phrase, text: 2 つの区間を並べ替えると一致するか（多重集合として等しいか）}
  - {type: phrase, text: 区間内の各値が偶数個（3 の倍数個）か・区間の積が平方数（立方数）か}
  - {type: constraint, text: 'N, Q ≤ 2×10^5 で区間の多重集合を毎回比べる'}
acl: []
verify: []
frequency: B
frequency_evidence: recent 1（abc455_g）・前提として届くページなし・古い ABC 4 問
sections:
  - {title: '値ごとに乱数を割り当てる理由（値そのものを足すと {1, 4} と {2, 3} が衝突する）', anchor: random-values}
  - {title: 集合は XOR、多重集合は和（XOR は同じ値 2 個で打ち消す）, anchor: xor-vs-sum}
  - {title: 接頭辞・区間のハッシュ（集合の接頭辞は初めて出た値だけ入れる）, anchor: prefix-hash}
  - {title: BIT と組んで点の更新に対応する, anchor: with-fenwick}
  - {title: 衝突確率と乱数の作り方（mt19937_64）, anchor: collision-and-rng}
  - {title: 各値が偶数個・k の倍数個かの判定（指数 mod k を乱数で符号化）, anchor: multiplicity-mod-k, level: 黄}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：値ごとに独立な 64 ビットの乱数を割り当て、集合は XOR、多重集合は和で表すと、2 つの集合が等しいかを順序に関係なく O(1) で比べられる。累積と組めば、区間どうしが並べ替えで一致するかも判定できる。
    - **いつ使うか**：
        - 先頭 x 項の集合と先頭 y 項の集合が等しいか
        - 2 つの区間を並べ替えると一致するか（多重集合として等しいか）
        - 区間内の各値が偶数個（3 の倍数個）か・区間の積が平方数（立方数）か
        - N, Q ≤ 2×10^5 で区間の多重集合を毎回比べる
    - **計算量**：（執筆時に書く）
    - **前提**：[累積和](../basics/prefix-sum.md)、[bit 演算の基本と XOR の性質](../basics/bit-operations.md)
