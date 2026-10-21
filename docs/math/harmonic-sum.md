---
id: harmonic-sum
title: 調和級数と倍数の列挙
aliases: [harmonic series, N/1+N/2+…+N/N, O(N log N) の倍数ループ, 倍数を回す]
type: technique
field: math
chapter: 素数と約数
order: 140
level: 水
kind: [計算量, 整数論]
prerequisites: [sigma-manipulation, complexity-estimation]
related: [sieve-eratosthenes, divisor-enum, floor-quotient-enum, divisor-inclusion-exclusion, zeta-mobius-divisor, divisors-and-multiples#harmonic]
summary: 割り切る・割り切られる関係にある組を値ごとに数えるとき、各 d について d の倍数を全てたどる二重ループが合計 N/1 + … + N/N ≈ N ln N 回で済むことを使う。値の上限が 10^6 程度なら間に合う。
complexity: null
signs:
  - {type: constraint, text: A_i ≤ 10^6 程度で、値を配列の添字にできる}
  - {type: phrase, text: 割り切る・割り切られる関係にある組を数える}
  - {type: phrase, text: 各 d について、d の倍数である要素の個数や和を求める}
  - {type: shape, text: 'Σ_{d=1}^{N} Σ_{k=1}^{⌊N/d⌋} f(d, kd) の形の二重ループ'}
acl: []
verify: []
frequency: A
frequency_evidence: recent 2（abc452_e・abc469_f）・前提として 3 ページに届く（直接 1）・古い ABC 7 問
sections:
  - {title: N/1 + N/2 + … + N/N ≈ N ln N の根拠（N = 10^6 で約 1.4×10^7）, anchor: why-n-log-n}
  - {title: 値の倍数に印を付ける, anchor: mark-multiples}
  - {title: 倍数を回して集める（d の倍数である要素の個数・和を全ての d について求める）, anchor: collect-multiples}
  - {title: 倍数の箱を後ろから決める, anchor: decide-from-back}
  - {title: 商が同じ範囲を倍数で区切って数える, anchor: quotient-ranges}
  - {title: 素数の倍数だけをたどる篩（N log log N）との違い, anchor: vs-sieve}
  - {title: 落とし穴：同じ値が複数あると自分自身で割り切れる・ループの上限は値の最大, anchor: pitfalls}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：割り切る・割り切られる関係にある組を値ごとに数えるとき、各 d について d の倍数を全てたどる二重ループが合計 N/1 + … + N/N ≈ N ln N 回で済むことを使う。値の上限が 10^6 程度なら間に合う。
    - **いつ使うか**：
        - A_i ≤ 10^6 程度で、値を配列の添字にできる
        - 割り切る・割り切られる関係にある組を数える
        - 各 d について、d の倍数である要素の個数や和を求める
        - Σ_{d=1}^{N} Σ_{k=1}^{⌊N/d⌋} f(d, kd) の形の二重ループ
    - **計算量**：（執筆時に書く）
    - **前提**：[Σ の変形](../math/sigma-manipulation.md)、[計算量の見積もり](../basics/complexity-estimation.md)
