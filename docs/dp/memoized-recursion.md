---
id: memoized-recursion
title: メモ化再帰
aliases: [メモ化, Memoization, 再帰 DP, トップダウン DP, map でメモ化, 疎な DP]
type: technique
field: dp
chapter: DP の考え方
order: 20
level: 基礎
kind: [DP]
prerequisites: [dp-basics]
related: [dp-order, dp-dag, cpp-lambda#recursive-lambda, cpp-environment#stack-depth, digit-dp-advanced, game-basics#game-dp, expected-value-dp#self-loop, probability-dp, expectation-linear-equations#cycle]
summary: 漸化式を再帰関数のまま書き、計算済みの値を覚えて使い回す。計算順序を考えなくてよく、⌊N/2⌋ のようにまばらにしか現れない状態だけを計算できる。
complexity: null
signs:
  - {type: constraint, text: N ≤ 10^18 で、⌊N/2⌋・⌊N/3⌋ のような値しか現れない}
  - {type: phrase, text: f(n) が f(⌊n/k⌋) などで再帰的に定義されている}
  - {type: shape, text: 'dp[x] が x より小さい値の dp で決まるが、どの値が現れるかを前もって列挙しにくい'}
acl: []
frequency: B
frequency_evidence: recent 1（abc470_e）・前提として 8 ページに届く（直接 2）・古い ABC 6 問
sections:
  - {title: 再帰とメモの書き方（未計算の印と答えの値の衝突を避ける）, anchor: write-memo}
  - {title: ボトムアップとの使い分け（速さ・スタック・高速化の載せやすさ）, anchor: vs-bottom-up}
  - {title: 到達する状態だけを持つ（map でメモ化・現れる値の個数の見積もり）, anchor: dp-map-sparse}
  - {title: 落とし穴：再帰が深いとスタックが溢れる・閉路があると止まらない・自己ループは移項してから書く, anchor: pitfalls}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：漸化式を再帰関数のまま書き、計算済みの値を覚えて使い回す。計算順序を考えなくてよく、⌊N/2⌋ のようにまばらにしか現れない状態だけを計算できる。
    - **いつ使うか**：
        - N ≤ 10^18 で、⌊N/2⌋・⌊N/3⌋ のような値しか現れない
        - f(n) が f(⌊n/k⌋) などで再帰的に定義されている
        - dp[x] が x より小さい値の dp で決まるが、どの値が現れるかを前もって列挙しにくい
    - **計算量**：（執筆時に書く）
    - **前提**：[DP の基本](../dp/dp-basics.md)
