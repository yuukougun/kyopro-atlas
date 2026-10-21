---
id: segment-tree-binary-search
title: セグメント木上の二分探索
aliases: [セグ木上の二分探索, セグ木の二分探索, binary search on segment tree, max_right, min_left]
type: technique
field: ds
chapter: 区間クエリ
order: 190
level: 水
kind: [データ構造, 二分探索, 区間クエリ]
prerequisites: [segment-tree, binary-search]
related: [kth-element, monotonic-stack, segment-tree-on-values, lazy-segment-tree, acl-reading]
summary: 左端 l を固定し、区間 [l, r) の総積が条件を満たす最大の r を、木を登って降りる手順で O(log N) で求める。l 以降で初めて x 以上になる位置・和が w を超えない最長の区間・K 番目の 1 に使う。
complexity: null
signs:
  - {type: phrase, text: 位置 i 以降で初めて値が x 以上になる位置}
  - {type: phrase, text: 空いている場所のうち K 番目}
  - {type: phrase, text: 各 l について、条件を満たす最長の区間}
  - {type: constraint, text: 'N, Q ≤ 2×10^5 で、更新のたびに条件を満たす最初の位置を答える'}
acl: [segtree, lazy_segtree]
verify: []
frequency: B
frequency_evidence: recent 1（abc478_f）・前提として届くページなし・古い ABC 5 問
sections:
  - {title: 何ができるか（max_right・min_left）と f の条件（副作用なし・f(e()) が真・単調）, anchor: what-it-does}
  - {title: なぜ O(log N) か（登る段階と降りる段階）, anchor: complexity}
  - {title: 和が K に達する位置（K 番目の 1・空きの K 番目）, anchor: kth-one}
  - {title: 境界（l = N のとき・返り値の r が N のとき・f(e()) が偽になる条件の言い換え・1-indexed への直し）, anchor: boundaries}
  - {title: 使い分け（BIT 上の二分探索・外側の二分探索と prod の O(log^2 N)・set の lower_bound）, anchor: choosing}
  - {title: 落とし穴（min_left に同じ向きの条件を流用する・単調でない条件）, anchor: pitfalls}
  - {title: 遅延セグメント木の上の二分探索（単調な列への区間作用と境界の探索）, anchor: on-lazy-segment-tree, level: 青}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：左端 l を固定し、区間 [l, r) の総積が条件を満たす最大の r を、木を登って降りる手順で O(log N) で求める。l 以降で初めて x 以上になる位置・和が w を超えない最長の区間・K 番目の 1 に使う。
    - **いつ使うか**：
        - 位置 i 以降で初めて値が x 以上になる位置
        - 空いている場所のうち K 番目
        - 各 l について、条件を満たす最長の区間
        - N, Q ≤ 2×10^5 で、更新のたびに条件を満たす最初の位置を答える
    - **計算量**：（執筆時に書く）
    - **前提**：[セグメント木](../ds/segment-tree.md)、[二分探索](../basics/binary-search.md)
