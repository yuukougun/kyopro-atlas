---
id: inversion-number
title: 転倒数
aliases: [inversion, inversion number, inversion count, 反転数, バブルソートの交換回数, 隣接 swap の最小回数]
type: technique
field: ds
chapter: 区間クエリ
order: 160
level: 水
kind: [データ構造, 数え上げ]
prerequisites: [fenwick-tree, coordinate-compression]
related: [permutation-cycles, divide-and-conquer, two-pointers, mo-algorithm, lazy-segment-tree-patterns]
summary: 列の転倒数（i < j かつ A_i > A_j の組の数）を、左から見て既に出た値のうち自分より大きいものの個数を BIT で足して O(N log N) で数える。隣接 swap でソートする最小回数に等しい。
complexity: null
signs:
  - {type: phrase, text: 隣り合う要素の交換でソートする最小回数・バブルソートの交換回数}
  - {type: phrase, text: i < j かつ A_i > A_j を満たす組の数}
  - {type: phrase, text: 巡回シフトや、全体に加算して mod を取った各列の転倒数}
  - {type: constraint, text: N ≤ 2×10^5 で、答えが約 2×10^10 まで大きくなる}
acl: [fenwick_tree]
verify: []
frequency: A
frequency_evidence: recent 2（abc452_f・abc479_f）・前提として届くページなし・古い ABC 6 問
sections:
  - {title: BIT で数える手順（値を座標圧縮し、左から自分より大きい既出の個数を足す）, anchor: count-with-bit}
  - {title: なぜ隣接 swap の最小回数か（1 回の隣接 swap で転倒数はちょうど 1 増減する）, anchor: adjacent-swaps}
  - {title: 言い換え（P を Q に並べ替える回数＝Q での位置に置き換えた列の転倒数、累積和の大小の組）, anchor: reformulation}
  - {title: 差分で更新する（先頭を末尾へ回す・全体に足して mod を取る・色ごとの転倒数を引く）, anchor: incremental}
  - {title: 使い分け（任意の 2 要素の swap なら置換の巡回分解、区間ごとの転倒数を多数なら Mo）, anchor: choosing}
  - {title: 落とし穴（等しい値の不等号・座標圧縮・64 bit）, anchor: pitfalls}
  - {title: 窓を伸縮しながら転倒数を増減する（尺取り・期待値と組む）, anchor: sliding-window, level: 青}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：列の転倒数（i < j かつ A_i > A_j の組の数）を、左から見て既に出た値のうち自分より大きいものの個数を BIT で足して O(N log N) で数える。隣接 swap でソートする最小回数に等しい。
    - **いつ使うか**：
        - 隣り合う要素の交換でソートする最小回数・バブルソートの交換回数
        - i < j かつ A_i > A_j を満たす組の数
        - 巡回シフトや、全体に加算して mod を取った各列の転倒数
        - N ≤ 2×10^5 で、答えが約 2×10^10 まで大きくなる
    - **計算量**：（執筆時に書く）
    - **前提**：[BIT（Fenwick Tree）](../ds/fenwick-tree.md)、[座標圧縮](../basics/coordinate-compression.md)
