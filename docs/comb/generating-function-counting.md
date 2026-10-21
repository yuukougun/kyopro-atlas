---
id: generating-function-counting
title: 母関数の考え方
aliases: [母関数, 生成関数, 数え上げの多項式表現, 形式的冪級数で数える, generating function]
type: overview
field: comb
chapter: 二項係数の系統
order: 170
level: 発展
kind: [数え上げ, 畳み込み・多項式]
prerequisites: [stars-and-bars, binomial-identities]
related: [fps-basics, convolution-ntt, cayley-pruefer, stirling-first, knapsack-undo]
summary: 選び方の数を多項式の係数で表し、積で独立な選択の組合せ、累乗で同じ選択の繰り返しを表す。DP の遷移も多項式の積・商として立式でき、多項式の演算そのものは FPS に任せる。
complexity: null
signs:
  - {type: phrase, text: 各要素の選び方が独立で、個数（和）の合計に条件がある}
  - {type: shape, text: 答えが (1 + x + … + x^c)^N のような式の特定の係数になる}
  - {type: shape, text: '遷移が dp''[s] = dp[s] + dp[s − v] のように、値をずらして足す形になる'}
acl: [convolution]
frequency: B
frequency_evidence: recent 0・前提として届くページなし・古い ABC 4 問
sections:
  - {title: 係数 = 数え方（積は独立な選択、累乗は繰り返し）, anchor: coefficients}
  - {title: 重複組合せ・上限つきの選び方を式で書く, anchor: formulas}
  - {title: DP の遷移を多項式の積・商として見る, anchor: dp-as-polynomial}
  - {title: 例：Prüfer 列と多項式の累乗、上昇階乗, anchor: examples}
  - {title: 多項式の演算（逆元・log・exp）は FPS のページへ, anchor: to-fps}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：選び方の数を多項式の係数で表し、積で独立な選択の組合せ、累乗で同じ選択の繰り返しを表す。DP の遷移も多項式の積・商として立式でき、多項式の演算そのものは FPS に任せる。
    - **いつ使うか**：
        - 各要素の選び方が独立で、個数（和）の合計に条件がある
        - 答えが (1 + x + … + x&#94;c)&#94;N のような式の特定の係数になる
        - 遷移が dp'[s] = dp[s] + dp[s − v] のように、値をずらして足す形になる
    - **計算量**：（執筆時に書く）
    - **前提**：[重複組合せ](../comb/stars-and-bars.md)、[二項係数の恒等式と和の公式](../comb/binomial-identities.md)
