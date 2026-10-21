---
id: fractional-binary-search
title: 平均・中央値の最大化
aliases: [平均の最大化, 比の最大化, 中央値の最大化, 分数計画, 濃度の最大化, 中央値の二分探索, 中央値の中央値, fractional programming, Dinkelbach]
type: technique
field: basics
chapter: 二分探索の応用
order: 200
level: 水
kind: [二分探索]
prerequisites: [binary-search-answer, prefix-sum]
related: [kth-value, median-absolute, prefix-sum-2d, dp-dag, inversion-number, minimum-spanning-tree]
summary: 平均・比・中央値の最大化を、答え x を決めた判定問題にして x を二分探索する。平均 ≥ x ⇔ Σ(a_i − x) ≥ 0、中央値 ≥ x ⇔ x 以上を +1・未満を −1 にした和が正、と言い換える。
complexity: null
signs:
  - {type: phrase, text: 平均・濃度・割合・(Σa)/(Σb) の最大（最小）}
  - {type: phrase, text: 中央値の最大値・最小値}
  - {type: phrase, text: 全区間の中央値を集めた中央値}
  - {type: shape, text: 選び方の和の最大化なら解けるが、割り算（平均・比）が入ると直接は最大化できない}
acl: []
frequency: B
frequency_evidence: recent 1（abc469_e）・前提として届くページなし・古い ABC 5 問
sections:
  - {title: 平均の言い換え（x を引いた和の符号で判定する）, anchor: average}
  - {title: 比 Σa / Σb の言い換え（a_i − x·b_i）, anchor: ratio}
  - {title: 判定を累積和・貪欲で行う, anchor: simple-check}
  - {title: 「濃度の高い順に K 個」が誤りである理由, anchor: greedy-pitfall}
  - {title: 中央値の言い換え（x 以上を +1、未満を −1）と偶数個のときの不等号, anchor: median, level: 青}
  - {title: 判定を DP・DAG の最長路・全域木で行う, anchor: dp-check, level: 青}
  - {title: 領域の中央値（2 次元累積和）, anchor: median-2d, level: 青}
  - {title: 全区間の中央値の中央値（転倒数で数える）, anchor: median-of-medians, level: 黄}
  - {title: 実数の精度と分母 0, anchor: precision}
  - {title: Dinkelbach 法, anchor: dinkelbach, level: 発展}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：平均・比・中央値の最大化を、答え x を決めた判定問題にして x を二分探索する。平均 ≥ x ⇔ Σ(a_i − x) ≥ 0、中央値 ≥ x ⇔ x 以上を +1・未満を −1 にした和が正、と言い換える。
    - **いつ使うか**：
        - 平均・濃度・割合・(Σa)/(Σb) の最大（最小）
        - 中央値の最大値・最小値
        - 全区間の中央値を集めた中央値
        - 選び方の和の最大化なら解けるが、割り算（平均・比）が入ると直接は最大化できない
    - **計算量**：（執筆時に書く）
    - **前提**：[答えで二分探索](../basics/binary-search-answer.md)、[累積和](../basics/prefix-sum.md)
