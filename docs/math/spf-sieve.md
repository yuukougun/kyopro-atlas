---
id: spf-sieve
title: 最小素因数の篩と線形篩
aliases: [osa_k 法, 最小素因数, smallest prime factor, SPF, 高速素因数分解, linear sieve]
type: technique
field: math
chapter: 素数と約数
order: 130
level: 基礎
kind: [整数論]
prerequisites: [sieve-eratosthenes, prime-factorization]
related: [prime-exponent-vector, euler-phi, mobius-function, grundy-number]
summary: 篩のついでに各数の最小素因数を記録し、それで割り続けて O(log n) で素因数分解する。10^6〜10^7 以下の多数の数を、それぞれ素因数分解するときに使う。
complexity: null
signs:
  - {type: constraint, text: A_i ≤ 10^6（〜10^7）の各要素を素因数分解する}
  - {type: phrase, text: 全ての組が互いに素か（pairwise coprime）を判定する}
  - {type: phrase, text: 各要素の素因数の個数（重複込み）を求める}
acl: []
verify: []
frequency: C
frequency_evidence: recent 0・前提として届くページなし・古い ABC 2 問
sections:
  - {title: 最小素因数の表の作り方と、割るたびに半分以下になるので O(log n) で分解できる理由, anchor: build-and-factor}
  - {title: 多数の数をまとめて分解する（試し割りとの比較）, anchor: many-numbers}
  - {title: 線形篩：各合成数を1回だけ作り、φ・μ の表を同時に作る, anchor: linear-sieve, level: 青}
  - {title: メモリの見積もり（int で 10^7 個は 40MB）, anchor: memory}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：篩のついでに各数の最小素因数を記録し、それで割り続けて O(log n) で素因数分解する。10&#94;6〜10&#94;7 以下の多数の数を、それぞれ素因数分解するときに使う。
    - **いつ使うか**：
        - A_i ≤ 10&#94;6（〜10&#94;7）の各要素を素因数分解する
        - 全ての組が互いに素か（pairwise coprime）を判定する
        - 各要素の素因数の個数（重複込み）を求める
    - **計算量**：（執筆時に書く）
    - **前提**：[エラトステネスの篩](../math/sieve-eratosthenes.md)、[素因数分解とルジャンドルの公式](../math/prime-factorization.md)
