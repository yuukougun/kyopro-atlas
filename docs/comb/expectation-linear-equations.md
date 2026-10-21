---
id: expectation-linear-equations
title: 閉路のある期待値
aliases: [期待値の方程式, a + bX の形で持つ, 吸収マルコフ連鎖, 閉路のある DP, 振り出しに戻る, absorbing Markov chain]
type: technique
field: comb
chapter: 確率・期待値
order: 400
level: 青
kind: [確率・期待値, DP, 線形代数・行列]
prerequisites: [expected-value-dp]
related: [gaussian-elimination, geometric-series-mod, optimal-strategy-expectation#guess-answer]
summary: 閉路があって後ろ向きに埋められない期待値を、戻る先の期待値を未知数 X とおき各状態を a + bX の形で持って、最後に X = a + bX を解いて求める。一般の状態は連立一次方程式で解く。
complexity: null
signs:
  - {type: phrase, text: 振り出し（スタート）に戻るマスがある}
  - {type: phrase, text: 円形に並んだ人が順番に〜する}
  - {type: phrase, text: 無限に続く可能性がある}
  - {type: phrase, text: 2 人が交互に繰り返し、決着がつくまで続ける}
acl: [modint]
frequency: B
frequency_evidence: recent 0・前提として届くページなし・古い ABC 3 問
sections:
  - {title: 自己ループの移項の一般化（戻る先が 1 か所）, anchor: generalize}
  - {title: 未知数を 1 つ残して a + bX で運ぶ, anchor: unknown}
  - {title: 円環状の依存を 1 周させて閉じる, anchor: cycle}
  - {title: 等比級数で閉じる（交互に繰り返す）, anchor: geometric-series}
  - {title: 一般の連立方程式（掃き出し法は math へ）, anchor: linear-system}
  - {title: b = 1 のとき（期待値が無限大）, anchor: infinite}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：閉路があって後ろ向きに埋められない期待値を、戻る先の期待値を未知数 X とおき各状態を a + bX の形で持って、最後に X = a + bX を解いて求める。一般の状態は連立一次方程式で解く。
    - **いつ使うか**：
        - 振り出し（スタート）に戻るマスがある
        - 円形に並んだ人が順番に〜する
        - 無限に続く可能性がある
        - 2 人が交互に繰り返し、決着がつくまで続ける
    - **計算量**：（執筆時に書く）
    - **前提**：[期待値 DP](../comb/expected-value-dp.md)
