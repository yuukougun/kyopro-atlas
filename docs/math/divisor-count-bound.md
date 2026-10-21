---
id: divisor-count-bound
title: 約数の個数の上界と高度合成数
aliases: [約数の個数の最大値, highly composite number, 約数が多い数, 素因数の種類数の上界]
type: technique
field: math
chapter: 素数と約数
order: 150
level: 水
kind: [整数論, 計算量]
prerequisites: [prime-factorization]
related: [crt, brute-force, recursive-enumeration, complexity-estimation]
summary: 約数（の組）を全部試す全探索が間に合うかを、約数の個数の上界（10^9 以下で 1344、10^18 以下で 103680）から見積もる。約数の多い数は、小さい素数の指数が減っていく形に限って列挙する。
complexity: null
signs:
  - {type: phrase, text: N の約数ごとに〜を計算する・d | N を満たす d を全部試す}
  - {type: phrase, text: N 以下で約数の個数が最大の数・約数が多い数を探す}
  - {type: constraint, text: N ≤ 10^12〜10^18 で、約数の組を全探索して間に合うかを見積もる}
acl: []
verify: []
frequency: A
frequency_evidence: recent 2（abc461_f・abc475_g）・前提として届くページなし・古い ABC 0 問
sections:
  - {title: 約数の個数・素因数の種類数の最大値の表（10^3〜10^18）, anchor: table}
  - {title: 約数の組を全部試す見積もり（1344² ≈ 1.8×10^6）, anchor: pairs}
  - {title: 約数の個数を √N と見積もる誤りと、10^18 の約数の列挙自体に O(√N) かかる注意, anchor: pitfalls}
  - {title: 約数を状態にした DP（約数の個数が少ないことを使う）, anchor: divisor-dp, level: 青}
  - {title: 高度合成数の列挙（小さい素数の指数が単調に減る形を DFS で）, anchor: enumerate-hcn, level: 黄}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：約数（の組）を全部試す全探索が間に合うかを、約数の個数の上界（10^9 以下で 1344、10^18 以下で 103680）から見積もる。約数の多い数は、小さい素数の指数が減っていく形に限って列挙する。
    - **いつ使うか**：
        - N の約数ごとに〜を計算する・d | N を満たす d を全部試す
        - N 以下で約数の個数が最大の数・約数が多い数を探す
        - N ≤ 10&#94;12〜10&#94;18 で、約数の組を全探索して間に合うかを見積もる
    - **計算量**：（執筆時に書く）
    - **前提**：[素因数分解とルジャンドルの公式](../math/prime-factorization.md)
