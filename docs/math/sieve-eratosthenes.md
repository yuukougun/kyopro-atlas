---
id: sieve-eratosthenes
title: エラトステネスの篩
aliases: [篩, sieve of Eratosthenes, 素数の列挙, 素数表]
type: technique
field: math
chapter: 素数と約数
order: 120
level: 基礎
kind: [整数論]
prerequisites: [divisor-enum]
related: [spf-sieve, segmented-sieve, harmonic-sum, prefix-sum, mobius-function]
summary: N 以下の素数を、小さい素数の倍数を順に消して O(N log log N) で列挙する。区間にある素数の個数を何度も答えるなら、篩の結果を累積和にする。
complexity: null
signs:
  - {type: constraint, text: N ≤ 10^6〜10^7 の範囲の素数を全部使う}
  - {type: phrase, text: p q³ ≤ N を満たす素数の組を数える}
  - {type: phrase, text: '区間 [l, r] の素数の個数を何度も答える'}
acl: []
verify: [enumerate_primes]
frequency: B
frequency_evidence: recent 1（abc475_d）・前提として 4 ページに届く（直接 4）・古い ABC 3 問
sections:
  - {title: 倍数を消す手順と、p² から消せば十分な理由, anchor: procedure}
  - {title: 計算量 O(N log log N) の根拠（素数の逆数和）と、調和級数の O(N log N) との違い, anchor: complexity}
  - {title: 篩の結果を累積和にして区間の素数を数える, anchor: prefix-count}
  - {title: 篩の変形（異なる素因数の個数を数える）, anchor: variants}
  - {title: メモリの見積もり（vector<bool>、10^8 まで）, anchor: memory}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：N 以下の素数を、小さい素数の倍数を順に消して O(N log log N) で列挙する。区間にある素数の個数を何度も答えるなら、篩の結果を累積和にする。
    - **いつ使うか**：
        - N ≤ 10&#94;6〜10&#94;7 の範囲の素数を全部使う
        - p q³ ≤ N を満たす素数の組を数える
        - 区間 [l, r] の素数の個数を何度も答える
    - **計算量**：（執筆時に書く）
    - **前提**：[約数列挙と素数判定](../math/divisor-enum.md)
