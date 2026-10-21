---
id: coupon-collector
title: 幾何分布とコンプリートガチャ
aliases: [幾何分布, 成功するまでの回数, 1/p, コンプガチャ, クーポンコレクター, N H_N, coupon collector's problem, geometric distribution]
type: technique
field: comb
chapter: 確率・期待値
order: 330
level: 基礎
kind: [確率・期待値]
prerequisites: [probability-basics]
related: [linearity-of-expectation, expected-value-dp, expectation-tail-sum, inclusion-exclusion#min-max]
summary: 成功確率 p の試行を成功するまで繰り返す回数の期待値は 1/p である。N 種類が等確率で出るとき全種類がそろうまでの回数の期待値は、段階ごとの N/(N−k) を足した N(1 + 1/2 + … + 1/N) になる。
complexity: null
signs:
  - {type: phrase, text: 成功するまで繰り返すときの回数の期待値}
  - {type: phrase, text: すべての種類を集める（全頂点を訪れる）までの回数の期待値}
  - {type: phrase, text: 〜が出るまでサイコロを振り続ける}
acl: []
frequency: C
frequency_evidence: recent 0・前提として届くページなし・古い ABC 1 問
sections:
  - {title: 幾何分布：E = 1 + (1 − p)E から 1/p, anchor: geometric}
  - {title: 失敗の回数（1/p − 1）との違い, anchor: failures}
  - {title: 段階に分けて幾何分布の期待値を足す（コンプガチャ）, anchor: staged}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：成功確率 p の試行を成功するまで繰り返す回数の期待値は 1/p である。N 種類が等確率で出るとき全種類がそろうまでの回数の期待値は、段階ごとの N/(N−k) を足した N(1 + 1/2 + … + 1/N) になる。
    - **いつ使うか**：
        - 成功するまで繰り返すときの回数の期待値
        - すべての種類を集める（全頂点を訪れる）までの回数の期待値
        - 〜が出るまでサイコロを振り続ける
    - **計算量**：（執筆時に書く）
    - **前提**：[確率の基本](../comb/probability-basics.md)
