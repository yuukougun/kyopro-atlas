---
id: exponent-mod
title: フェルマーの小定理と指数の mod
aliases: [指数の mod, オイラーの定理, Fermat's little theorem, Euler's theorem, 指数を p−1 で割る, 累乗の塔, tetration]
type: technique
field: math
chapter: mod の計算
order: 70
level: 水
kind: [整数論]
prerequisites: [mod-inverse]
related: [euler-phi, multiplicative-order, miller-rabin, mod-pow]
summary: a^(K^N) のように指数が巨大な累乗の mod を、gcd(a, p) = 1 なら指数を p − 1 で割った余りに直して求める。一般の法ではオイラーの定理を使い、底が法の倍数になる場合を分ける。
complexity: null
signs:
  - {type: phrase, text: a^(b^c) mod p のように、指数にさらに指数がある}
  - {type: phrase, text: 累乗の塔を mod で求める}
  - {type: constraint, text: 指数が 10^18 をさらに累乗した大きさになる}
acl: [pow_mod]
verify: [tetration_mod]
frequency: C
frequency_evidence: recent 0・前提として 1 ページに届く（直接 1）・古い ABC 2 問
sections:
  - {title: フェルマーの小定理と、指数を p − 1 で割ってよい理由（累乗の周期）, anchor: fermat}
  - {title: 指数の計算は mod (p − 1)（p − 1 は合成数なので割り算はできない）, anchor: exponent-mod-p-1}
  - {title: 底が p の倍数の場合（答えは 0、指数が 0 なら 1）, anchor: base-multiple}
  - {title: 一般の法：オイラーの定理と、互いに素でないときの一般化（累乗の塔）, anchor: euler-theorem, level: 黄}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：a&#94;(K&#94;N) のように指数が巨大な累乗の mod を、gcd(a, p) = 1 なら指数を p − 1 で割った余りに直して求める。一般の法ではオイラーの定理を使い、底が法の倍数になる場合を分ける。
    - **いつ使うか**：
        - a&#94;(b&#94;c) mod p のように、指数にさらに指数がある
        - 累乗の塔を mod で求める
        - 指数が 10^18 をさらに累乗した大きさになる
    - **計算量**：（執筆時に書く）
    - **前提**：[逆元と mod での割り算](../math/mod-inverse.md)
