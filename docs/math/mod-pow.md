---
id: mod-pow
title: 繰り返し二乗法
aliases: [二分累乗法, 高速累乗, binary exponentiation, modpow, pow_mod, モノイドの累乗]
type: technique
field: math
chapter: mod の計算
order: 40
level: 基礎
kind: [整数論, ダブリング・分割統治]
prerequisites: [mod-arithmetic]
related: [doubling, matrix-power, exponent-mod, mod-inverse]
summary: a^n mod m を、n の2進表記に沿って a, a², a⁴, … を掛け合わせて O(log n) で求める。結合法則を満たす演算（行列・写像の合成など）なら同じ方法で累乗できる。
complexity: null
signs:
  - {type: constraint, text: 指数・繰り返しの回数が N ≤ 10^18}
  - {type: phrase, text: a^N を m で割った余り}
  - {type: phrase, text: 結合法則を満たす同じ操作を非常に多く繰り返す}
acl: [pow_mod]
verify: []
frequency: A
frequency_evidence: recent 0・前提として 28 ページに届く（直接 2）・古い ABC 1 問
sections:
  - {title: 指数を2進展開して必要な a^(2^k) だけ掛ける, anchor: binary-expansion}
  - {title: 再帰版と反復版, anchor: recursive-iterative}
  - {title: 結合法則を満たす演算の累乗（行列・写像の合成）, anchor: monoid-power}
  - {title: 落とし穴：指数を m で割ってしまう・0^0・掛け算のあふれ, anchor: pitfalls}
  - {title: 'ACL の pow_mod と modint::pow', anchor: acl}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：a^n mod m を、n の2進表記に沿って a, a², a⁴, … を掛け合わせて O(log n) で求める。結合法則を満たす演算（行列・写像の合成など）なら同じ方法で累乗できる。
    - **いつ使うか**：
        - 指数・繰り返しの回数が N ≤ 10^18
        - a^N を m で割った余り
        - 結合法則を満たす同じ操作を非常に多く繰り返す
    - **計算量**：（執筆時に書く）
    - **前提**：[mod の計算の基本](../math/mod-arithmetic.md)
