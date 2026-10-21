---
id: mod-inverse
title: 逆元と mod での割り算
aliases: [モジュラ逆元, modular inverse, modinv, inv_mod, mod での割り算, 逆元表]
type: technique
field: math
chapter: mod の計算
order: 50
level: 基礎
kind: [整数論]
prerequisites: [mod-pow]
related: [ext-gcd, modint, binomial-precompute#lucas, rational-mod, geometric-series-mod]
summary: a·x ≡ 1 (mod m) となる逆元 x を求め、mod での割り算を掛け算に直す。素数 mod ならフェルマーの小定理で a^(m−2)、一般の法では拡張ユークリッドで求める。
complexity: null
signs:
  - {type: phrase, text: 答えは有理数 P/Q になるので P × Q^(−1) mod 998244353 を出力する}
  - {type: phrase, text: 平均・等比数列の和などを、割り算を含む式のまま mod で求める}
acl: [inv_mod]
verify: []
frequency: A
frequency_evidence: recent 1（abc468_e）・前提として 24 ページに届く（直接 9）・古い ABC 2 問
sections:
  - {title: '逆元が存在する条件（gcd(a, m) = 1）', anchor: existence}
  - {title: フェルマーの小定理による a^(p−2), anchor: fermat}
  - {title: 拡張ユークリッドによる逆元（法が素数でないとき）, anchor: ext-gcd, level: 水}
  - {title: '逆元表を O(N) で作る（inv[i] = −⌊m/i⌋·inv[m mod i]）と階乗の逆元', anchor: inverse-table}
  - {title: 有理数 P/Q を P × Q^(−1) で表す計算, anchor: rational}
  - {title: 割れないときの3つの場合（割る数が p の倍数・公比 ≡ 1・法が素数でない）, anchor: not-invertible}
  - {title: 'ACL の inv_mod と modint::inv', anchor: acl}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：a·x ≡ 1 (mod m) となる逆元 x を求め、mod での割り算を掛け算に直す。素数 mod ならフェルマーの小定理で a^(m−2)、一般の法では拡張ユークリッドで求める。
    - **いつ使うか**：
        - 答えは有理数 P/Q になるので P × Q^(−1) mod 998244353 を出力する
        - 平均・等比数列の和などを、割り算を含む式のまま mod で求める
    - **計算量**：（執筆時に書く）
    - **前提**：[繰り返し二乗法](../math/mod-pow.md)
