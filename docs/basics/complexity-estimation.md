---
id: complexity-estimation
title: 計算量の見積もり
aliases: [計算量, オーダー, 制約から手法を逆算する, 制約から考える, TLE の見積もり, ならし計算量, 償却計算量, 定数倍, time complexity, amortized analysis]
type: technique
field: basics
chapter: 計算量と bit 演算
order: 10
level: 基礎
kind: [計算量]
prerequisites: []
related: [reverse-index-constraints, harmonic-sum, two-pointers, cpp-io#tle-causes]
summary: 制約の大きさから許される計算量を逆算し、使える手法の候補を絞る。C++ なら 1 秒に 10^8〜数×10^8 回を目安に、ループの回数・log の数・定数倍・メモリを見積もる。
complexity: null
signs:
  - {type: constraint, text: N ≤ 8 / 20 / 40 / 400 / 5000 / 2×10^5 / 10^18 のような制約の大きさ}
  - {type: constraint, text: 実行時間制限が 5 秒など長い（重めの全探索が想定されている）}
  - {type: constraint, text: Q ≤ 2×10^5 個のクエリ（1 回あたり O(log N) 以下が必要）}
  - {type: constraint, text: テストケースが T 個あり、N の総和が 2×10^5 以下}
  - {type: shape, text: while の中に for があって入れ子に見えるが、各要素は一度しか動かない}
acl: []
frequency: A
frequency_evidence: recent 0・前提として 79 ページに届く（直接 4）・古い ABC 2 問
sections:
  - {title: 制約 → 許される計算量 → 疑う手法の表, anchor: constraint-table}
  - {title: 見積もりの手順（ループの回数・log の数・定数倍・メモリ）, anchor: how-to-estimate}
  - {title: ならし計算量（ポインタが戻らない・各要素が一度入って一度出る）, anchor: amortized}
  - {title: 調和級数の計算量（倍数の列挙。詳しくは整数論の調和級数のページ）, anchor: harmonic-series}
  - {title: 候補の数で見積もる（階乗・ベル数・約数の個数の最大）, anchor: count-candidates}
  - {title: 定数倍（配列と set・map の差・メモリの連続性・bitset）, anchor: constant-factor, level: 水}
  - {title: 複数テストケースは合計（ΣN）で見積もる, anchor: multiple-testcases}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：制約の大きさから許される計算量を逆算し、使える手法の候補を絞る。C++ なら 1 秒に 10&#94;8〜数×10&#94;8 回を目安に、ループの回数・log の数・定数倍・メモリを見積もる。
    - **いつ使うか**：
        - N ≤ 8 / 20 / 40 / 400 / 5000 / 2×10^5 / 10^18 のような制約の大きさ
        - 実行時間制限が 5 秒など長い（重めの全探索が想定されている）
        - Q ≤ 2×10^5 個のクエリ（1 回あたり O(log N) 以下が必要）
        - テストケースが T 個あり、N の総和が 2×10^5 以下
        - while の中に for があって入れ子に見えるが、各要素は一度しか動かない
    - **計算量**：（執筆時に書く）
    - **前提**：なし
