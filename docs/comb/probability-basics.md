---
id: probability-basics
title: 確率の基本
aliases: [確率, 条件付き確率, 全確率の公式, 独立と排反, 期待値の定義, conditional probability]
type: technique
field: comb
chapter: 確率・期待値
order: 320
level: 基礎
kind: [確率・期待値]
prerequisites: [counting-basics]
related: [rational-mod, linearity-of-expectation, expected-value-dp, complement]
summary: 同様に確からしいときは「確率 = 条件を満たす場合の数 / 全体の場合の数」で、独立な事象は掛け、排反な事象は足す。条件付き確率と全確率の公式（最初の一手で場合分け）は、期待値 DP の式の根拠になる。
complexity: null
signs:
  - {type: phrase, text: 確率を求めよ（絶対誤差・相対誤差 10^−6 まで許容）}
  - {type: phrase, text: サイコロ・コイン・カードを使う確率}
  - {type: phrase, text: 最初に〜し、その結果に応じて〜するときの確率}
acl: []
frequency: A
frequency_evidence: recent 1（abc463_f）・前提として 12 ページに届く（直接 6）・古い ABC 2 問
sections:
  - {title: 同様に確からしいとき：場合の数の比, anchor: ratio}
  - {title: 独立・排反・余事象, anchor: independence}
  - {title: 条件付き確率と全確率の公式, anchor: conditional}
  - {title: 期待値の定義, anchor: expectation}
  - {title: 浮動小数点の誤差と出力の桁数, anchor: precision}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：同様に確からしいときは「確率 = 条件を満たす場合の数 / 全体の場合の数」で、独立な事象は掛け、排反な事象は足す。条件付き確率と全確率の公式（最初の一手で場合分け）は、期待値 DP の式の根拠になる。
    - **いつ使うか**：
        - 確率を求めよ（絶対誤差・相対誤差 10^−6 まで許容）
        - サイコロ・コイン・カードを使う確率
        - 最初に〜し、その結果に応じて〜するときの確率
    - **計算量**：（執筆時に書く）
    - **前提**：[和・積の法則と順列・組合せ](../comb/counting-basics.md)
