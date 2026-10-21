---
id: gcd-lcm
title: GCD・LCM とユークリッドの互除法
aliases: [最大公約数, 最小公倍数, 互除法, Euclidean algorithm, 'std::gcd', 既約分数]
type: technique
field: math
chapter: GCD と合同式
order: 200
level: 基礎
kind: [整数論]
prerequisites: [integer-division]
related: [gcd-properties, ext-gcd, prime-exponent-vector, geometry-precision#line-normalization, prefix-sum, stern-brocot]
summary: gcd(a, b) = gcd(b, a mod b) を繰り返して最大公約数を O(log min(a, b)) で求め、lcm は a / gcd × b で求める。1つ除いた gcd を累積 gcd で求め、分数を既約にして比べる。
complexity: null
signs:
  - {type: phrase, text: 全員が同時に・周期がそろう最初の時刻（lcm）}
  - {type: phrase, text: 等間隔に移動して全ての点を訪れられる最大の幅（gcd）}
  - {type: phrase, text: 1つだけ書き換え（取り除い）たときの gcd の最大}
  - {type: phrase, text: 分数や傾きが等しいものを同じものとして数える}
acl: []
verify: []
frequency: A
frequency_evidence: recent 1（abc460_e）・前提として 14 ページに届く（直接 8）・古い ABC 3 問
sections:
  - {title: 互除法の正しさ（公約数の集合が変わらない）と回数の上限（隣り合うフィボナッチ数）, anchor: euclid}
  - {title: '複数の数の gcd・lcm と gcd(0, a) = a', anchor: many-numbers}
  - {title: lcm のオーバーフロー（割ってから掛ける）, anchor: lcm-overflow}
  - {title: 左右からの累積 gcd（1つ除いた gcd）, anchor: prefix-suffix-gcd}
  - {title: 分数・傾きを既約にして map のキーにする, anchor: reduce-fraction, level: 水}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：gcd(a, b) = gcd(b, a mod b) を繰り返して最大公約数を O(log min(a, b)) で求め、lcm は a / gcd × b で求める。1つ除いた gcd を累積 gcd で求め、分数を既約にして比べる。
    - **いつ使うか**：
        - 全員が同時に・周期がそろう最初の時刻（lcm）
        - 等間隔に移動して全ての点を訪れられる最大の幅（gcd）
        - 1つだけ書き換え（取り除い）たときの gcd の最大
        - 分数や傾きが等しいものを同じものとして数える
    - **計算量**：（執筆時に書く）
    - **前提**：[整数の割り算と余り](../math/integer-division.md)
