---
id: integer-root
title: 整数の平方根・K 乗根と累乗数
aliases: [isqrt, integer square root, 整数平方根, 累乗数, perfect power, 誤差のない平方根, sqrt の誤差]
type: technique
field: math
chapter: floor と商
order: 260
level: 基礎
kind: [整数論, 二分探索]
prerequisites: [integer-division]
related: [binary-search, cpp-types-literals#floating-point, cpp-math-functions, divisor-inclusion-exclusion, prime-exponent-vector]
summary: ⌊√N⌋ を double の sqrt で求めると 10^18 付近で ±1 ずれるので、r² ≤ N < (r+1)² になるまで整数で補正するか二分探索で求める。a^b ≤ N となる a の上限や、累乗数を重複なく数えるのに使う。
complexity: null
signs:
  - {type: constraint, text: N ≤ 10^18 で平方数・平方根を扱う}
  - {type: phrase, text: a^b（b ≥ 2）の形で表せる N 以下の数}
  - {type: phrase, text: 2^a × b² のように累乗を組み合わせた数を数える}
acl: []
verify: [kth_root_integer]
frequency: B
frequency_evidence: recent 0・前提として届くページなし・古い ABC 4 問
sections:
  - {title: sqrt の誤差と補正（r² ≤ N < (r+1)² を確かめる）, anchor: sqrt-correction}
  - {title: 二分探索による整数の K 乗根（途中の累乗のあふれ）, anchor: kth-root}
  - {title: 累乗数の数え上げ（b ≥ 3 は列挙、b = 2 は ⌊√N⌋、重複を除く）, anchor: perfect-powers}
  - {title: √ を含む式の大小を整数で比べる, anchor: compare-sqrt}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：⌊√N⌋ を double の sqrt で求めると 10^18 付近で ±1 ずれるので、r² ≤ N < (r+1)² になるまで整数で補正するか二分探索で求める。a^b ≤ N となる a の上限や、累乗数を重複なく数えるのに使う。
    - **いつ使うか**：
        - N ≤ 10^18 で平方数・平方根を扱う
        - a^b（b ≥ 2）の形で表せる N 以下の数
        - 2^a × b² のように累乗を組み合わせた数を数える
    - **計算量**：（執筆時に書く）
    - **前提**：[整数の割り算と余り](../math/integer-division.md)
