---
id: stars-and-bars
title: 重複組合せ
aliases: [玉と仕切り, 'H(n,k)', 非負整数解の個数, 隣り合わない選び方, stars and bars]
type: technique
field: comb
chapter: 数え上げの基礎
order: 40
level: 基礎
kind: [数え上げ]
prerequisites: [binomial-coefficient]
related: [counting-bijection, twelvefold-way, multinomial-coefficient, inclusion-exclusion, generating-function-counting, prime-exponent-vector]
summary: x_1 + … + x_k = n の非負整数解は C(n+k−1, k−1) 個、正の整数解は C(n−1, k−1) 個で、玉と仕切りの並べ方に 1 対 1 に対応する。広義単調な列や間隔を空けて選ぶ方法も、同じ形に直して数える。
complexity: null
signs:
  - {type: phrase, text: 和が N になる非負（正）整数の組の個数}
  - {type: phrase, text: 広義単調増加な列の個数}
  - {type: phrase, text: N 個から隣り合わない（間隔 d 以上の）K 個を選ぶ方法の数}
  - {type: phrase, text: 区別のない玉を区別のある箱へ配る方法の数}
acl: []
frequency: B
frequency_evidence: recent 1（abc456_g）・前提として 3 ページに届く（直接 3）・古い ABC 6 問
sections:
  - {title: 玉と仕切りの対応（非負解と正の解）, anchor: stars-bars}
  - {title: 「以下」は余りの変数を 1 つ足して等式にする, anchor: at-most}
  - {title: 広義単調な列との対応, anchor: monotone}
  - {title: 隣り合わない選び方・間隔 d 以上の選び方, anchor: gaps}
  - {title: 場合分けしてから配る・素因数ごとに配る, anchor: applications, level: 水}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：x_1 + … + x_k = n の非負整数解は C(n+k−1, k−1) 個、正の整数解は C(n−1, k−1) 個で、玉と仕切りの並べ方に 1 対 1 に対応する。広義単調な列や間隔を空けて選ぶ方法も、同じ形に直して数える。
    - **いつ使うか**：
        - 和が N になる非負（正）整数の組の個数
        - 広義単調増加な列の個数
        - N 個から隣り合わない（間隔 d 以上の）K 個を選ぶ方法の数
        - 区別のない玉を区別のある箱へ配る方法の数
    - **計算量**：（執筆時に書く）
    - **前提**：[二項係数の意味と性質](../comb/binomial-coefficient.md)
