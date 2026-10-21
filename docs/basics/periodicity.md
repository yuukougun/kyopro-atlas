---
id: periodicity
title: 周期性の検出
aliases: [周期性, 周期の検出, ρ 型, ループの検出, シミュレーションの高速化, cycle finding]
type: technique
field: basics
chapter: 周期とダブリング
order: 290
level: 基礎
kind: [ダブリング・分割統治]
prerequisites: []
related: [doubling, functional-graph, cycle-detection, symmetry-pigeonhole-casework#pigeonhole, global-offset, matrix-power]
summary: 状態が S 種類しかなければ、S 回進むまでに必ず以前と同じ状態が現れる（鳩の巣原理）。初めて訪れた時刻を記録して尾の長さと周期を求め、K 回後の状態や途中の和を割り算で一度に求める。
complexity: null
signs:
  - {type: constraint, text: K ≤ 10^18 回の操作で、状態の種類は 10^5〜10^6 程度}
  - {type: phrase, text: 'x_{n+1} = f(x_n) の形の漸化式'}
  - {type: phrase, text: 同じ模様が繰り返し敷き詰められた盤面}
acl: []
frequency: B
frequency_evidence: recent 1（abc452_e）・前提として 9 ページに届く（直接 1）・古い ABC 5 問
sections:
  - {title: 尾と周期（ρ 型）と K 回後の求め方, anchor: rho}
  - {title: 途中の和（尾の和＋周期の和 × 回数＋余り）, anchor: partial-sums}
  - {title: 状態に将来を決める情報をすべて入れる, anchor: state-design}
  - {title: 収束に気づく, anchor: convergence}
  - {title: 盤面・剰余の周期を割り算で数える, anchor: periodic-patterns, level: 水}
  - {title: シミュレーションを速く進める（ずれ・反転は全体への操作を変数で持つページへ）, anchor: simulation-speedup}
  - {title: ダブリング・行列累乗との使い分け, anchor: vs-doubling}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：状態が S 種類しかなければ、S 回進むまでに必ず以前と同じ状態が現れる（鳩の巣原理）。初めて訪れた時刻を記録して尾の長さと周期を求め、K 回後の状態や途中の和を割り算で一度に求める。
    - **いつ使うか**：
        - K ≤ 10&#94;18 回の操作で、状態の種類は 10&#94;5〜10&#94;6 程度
        - x_{n+1} = f(x_n) の形の漸化式
        - 同じ模様が繰り返し敷き詰められた盤面
    - **計算量**：（執筆時に書く）
    - **前提**：なし
