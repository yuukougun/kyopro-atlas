---
id: optimal-strategy-expectation
title: 最適戦略の期待値
aliases: [最適停止, expectimax, 期待値の最大化, optimal stopping]
type: technique
field: comb
chapter: 確率・期待値
order: 390
level: 黄
kind: [確率・期待値, DP]
prerequisites: [expected-value-dp]
related: [minimax, rational-mod, expectation-linear-equations, binary-search-answer]
summary: 選択と偶然が交互に来る確率過程で、期待値を最大（最小）にする戦略のもとでの期待値を、残すものや知っている情報を状態にして後ろから求める。mod で答える問題でも比較は実数で行い、やり直せるなら答えを仮定して二分探索する。
complexity: null
signs:
  - {type: phrase, text: 最適に行動したときの期待値（勝率）}
  - {type: phrase, text: 好きなタイミングでやめられる・最初からやり直せる}
  - {type: phrase, text: どれを残すか（どれを選ぶか）を選びながら進む}
acl: []
frequency: B
frequency_evidence: recent 1（abc470_e）・前提として届くページなし・古い ABC 7 問
sections:
  - {title: 残すもの・知っている情報を状態にする, anchor: state-design}
  - {title: 止めるタイミングを選ぶ（相手の得点の分布と比べる）, anchor: stopping}
  - {title: 比較は実数で、答えは mod で（比較できない落とし穴）, anchor: compare-real}
  - {title: やり直しがあるときは答えを仮定して二分探索する, anchor: guess-answer}
  - {title: 「最大値の期待値」との違い, anchor: vs-max}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：選択と偶然が交互に来る確率過程で、期待値を最大（最小）にする戦略のもとでの期待値を、残すものや知っている情報を状態にして後ろから求める。mod で答える問題でも比較は実数で行い、やり直せるなら答えを仮定して二分探索する。
    - **いつ使うか**：
        - 最適に行動したときの期待値（勝率）
        - 好きなタイミングでやめられる・最初からやり直せる
        - どれを残すか（どれを選ぶか）を選びながら進む
    - **計算量**：（執筆時に書く）
    - **前提**：[期待値 DP](../comb/expected-value-dp.md)
