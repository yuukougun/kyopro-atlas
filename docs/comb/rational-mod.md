---
id: rational-mod
title: 確率・期待値を mod 998244353 で答える
aliases: [有理数 mod, 有理数の mod 表現, P × Q^(−1) mod p, 確率 mod 998244353, 分数を mod で表す]
type: technique
field: comb
chapter: 確率・期待値
order: 340
level: 水
kind: [確率・期待値, 整数論]
prerequisites: [mod-inverse, probability-basics]
related: [modint, expected-value-dp, probability-dp, optimal-strategy-expectation]
summary: 確率・期待値の既約分数 P/Q を P × Q^(−1) mod 998244353 で答える。逆元の掛け算でも四則の関係は保たれるので実数の計算をそのまま mod で行ってよいが、mod の値どうしは大小を比べられない。
complexity: null
signs:
  - {type: phrase, text: 期待値（確率）を mod 998244353 で出力せよ}
  - {type: phrase, text: 求める値は有理数で表せ、既約分数 P/Q について R × Q ≡ P となる R を出力する}
  - {type: phrase, text: 確率が p% で与えられる}
acl: [modint]
frequency: B
frequency_evidence: recent 0・前提として届くページなし・古い ABC 4 問
sections:
  - {title: なぜ有理数を mod で表してよいか（逆元と四則の保存）, anchor: why}
  - {title: 途中の計算をすべて mod で行う, anchor: all-mod}
  - {title: 確率 p% は p × 100^(−1) として入れる, anchor: percent}
  - {title: mod の値では大小比較できない（最適戦略は実数で比べる）, anchor: no-compare}
  - {title: 分母が 0 になる式変形に注意する, anchor: zero-denominator}
  - {title: 検算：出力を分数に戻す（有理数復元）, anchor: reconstruct}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：確率・期待値の既約分数 P/Q を P × Q^(−1) mod 998244353 で答える。逆元の掛け算でも四則の関係は保たれるので実数の計算をそのまま mod で行ってよいが、mod の値どうしは大小を比べられない。
    - **いつ使うか**：
        - 期待値（確率）を mod 998244353 で出力せよ
        - 求める値は有理数で表せ、既約分数 P/Q について R × Q ≡ P となる R を出力する
        - 確率が p% で与えられる
    - **計算量**：（執筆時に書く）
    - **前提**：[逆元と mod での割り算](../math/mod-inverse.md)、[確率の基本](../comb/probability-basics.md)
