---
id: binomial-precompute
title: 二項係数の前計算
aliases: [nCr mod p, 階乗と逆階乗の表, fact と ifact, 逆階乗, Combination テーブル, 任意 mod の二項係数, Lucas の定理, nCr mod 2, Lucas's theorem]
type: technique
field: comb
chapter: 数え上げの基礎
order: 30
level: 基礎
kind: [数え上げ, 整数論]
prerequisites: [binomial-coefficient, mod-inverse]
related: [modint, mod-pow, multinomial-coefficient, lattice-paths, bit-operations, counting-labeled-graphs]
summary: 素数 p を法として階乗と逆階乗を前計算し、C(n,k) を O(1) で求める。n が巨大なら O(k) の積、p が小さく n ≥ p なら Lucas の定理、法が素数でなければパスカルの三角形を使う。
complexity: null
signs:
  - {type: constraint, text: 'N ≤ 2×10^5 程度で C(n,k) を何度も求める'}
  - {type: constraint, text: n ≤ 10^9 で k ≤ 10^6 程度}
  - {type: phrase, text: 法 M が入力で与えられ、素数とは限らない}
  - {type: phrase, text: 隣り合う 2 つから新しい値を作る操作を繰り返し、最後に残る値を求める（三角形・ピラミッド）}
  - {type: phrase, text: 答えを mod 2・mod 3 など小さい素数で求める}
acl: [modint]
frequency: A
frequency_evidence: recent 6（abc453_e・abc458_e・abc459_e・abc463_f・abc463_g・abc471_e）・前提として 11 ページに届く（直接 4）・古い ABC 6 問
sections:
  - {title: fact を前から、ifact を後ろから作る理由, anchor: fact-ifact}
  - {title: 表の大きさ（H+W・N+K・2N など）と範囲外の 0, anchor: table-size}
  - {title: n が巨大で k が小さいときは O(k) で求める, anchor: large-n}
  - {title: 法が素数でないとき：n が小さければパスカルの三角形で作る, anchor: composite-mod}
  - {title: 法が小さい素数で n ≥ p になるとき：Lucas の定理, anchor: lucas, level: 青}
  - {title: p = 2 では (n & k) == k、ピラミッドの係数を二項係数と見抜く, anchor: parity-pyramid, level: 青}
  - {title: mod を取らない正確な値（掛けてから割る・__int128）, anchor: exact}
  - {title: ACL では modint998244353 の inv()・pow() で自作する, anchor: acl}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：素数 p を法として階乗と逆階乗を前計算し、C(n,k) を O(1) で求める。n が巨大なら O(k) の積、p が小さく n ≥ p なら Lucas の定理、法が素数でなければパスカルの三角形を使う。
    - **いつ使うか**：
        - N ≤ 2×10^5 程度で C(n,k) を何度も求める
        - n ≤ 10^9 で k ≤ 10^6 程度
        - 法 M が入力で与えられ、素数とは限らない
        - 隣り合う 2 つから新しい値を作る操作を繰り返し、最後に残る値を求める（三角形・ピラミッド）
        - 答えを mod 2・mod 3 など小さい素数で求める
    - **計算量**：（執筆時に書く）
    - **前提**：[二項係数の意味と性質](../comb/binomial-coefficient.md)、[逆元と mod での割り算](../math/mod-inverse.md)
