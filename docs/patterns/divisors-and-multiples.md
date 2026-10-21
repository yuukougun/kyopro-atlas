---
id: divisors-and-multiples
title: 約数と倍数
aliases: [約数, 倍数, divisor, multiple]
type: pattern
field: patterns
order: 80
level: null
kind: [案内, 整数論]
prerequisites: []
related: [divisor-enum, divisor-count-bound, harmonic-sum, spf-sieve, prime-factorization, multiplicative-function, divisor-inclusion-exclusion, mobius-function, zeta-mobius-divisor, prime-exponent-vector, gcd-lcm, gcd-properties, floor-quotient-enum, integer-division]
summary: 約数・倍数・gcd が出てくる問題で、問われ方から使う手法を引ける。約数の列挙、倍数を回して集める調和級数、素因数分解、gcd がちょうど g の数え上げ、約数の個数の上限の問われ方に分ける。
complexity: null
signs:
  - {type: constraint, text: N ≤ 10^12 で、N の約数や素因数を使う}
  - {type: phrase, text: 1 以上 N 以下のすべての整数について、約数や倍数に関する値の総和を求める}
  - {type: phrase, text: gcd がちょうど g になる組・部分集合の個数}
  - {type: phrase, text: 積がちょうど N になる列の個数}
  - {type: phrase, text: 積が平方数になる組の個数}
acl: []
sections:
  - {title: 題材の性質, anchor: properties}
  - {title: 1 つの数の約数を列挙 → √N までの割り算（divisor-enum）, anchor: enumerate}
  - {title: 約数の個数で計算量を見積もる → 約数の個数の上限（divisor-count-bound）, anchor: count-bound}
  - {title: 1〜N の各数の約数・倍数を集める → 倍数を回す調和級数（harmonic-sum）, anchor: harmonic}
  - {title: '素因数分解 → 多数なら最小素因数の篩、1 つなら試し割り（spf-sieve, prime-factorization）', anchor: factorize}
  - {title: 約数の個数・約数の和 → 素因数分解の指数から（multiplicative-function）, anchor: divisor-functions}
  - {title: 'gcd がちょうど g の組の数 → 倍数で数えて大きい方から引く・メビウス関数（divisor-inclusion-exclusion, mobius-function）', anchor: exact-gcd}
  - {title: 約数・倍数の向きの累積和 → 約数のゼータ変換・メビウス変換（zeta-mobius-divisor）, anchor: zeta}
  - {title: 積が平方数・積がちょうど N → 素因数の指数で考える（prime-exponent-vector）, anchor: products}
  - {title: '差の gcd・区間の gcd の値の種類 → gcd の性質（gcd-lcm, gcd-properties）', anchor: gcd}
  - {title: ⌊N/i⌋ の値ごとにまとめる → floor の値の列挙（floor-quotient-enum）, anchor: floor-sums}
  - {title: 落とし穴, anchor: pitfalls}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何のページか**：約数・倍数・gcd が出てくる問題で、問われ方から使う手法を引ける。約数の列挙、倍数を回して集める調和級数、素因数分解、gcd がちょうど g の数え上げ、約数の個数の上限の問われ方に分ける。
    - **いつ使うか**：
        - N ≤ 10^12 で、N の約数や素因数を使う
        - 1 以上 N 以下のすべての整数について、約数や倍数に関する値の総和を求める
        - gcd がちょうど g になる組・部分集合の個数
        - 積がちょうど N になる列の個数
        - 積が平方数になる組の個数
    - **使い方**：（執筆時に書く）
