---
id: minimax
title: ミニマックス
aliases: [negamax, 得点差 DP, 自分 − 相手の最大化, 得点差を最大化するゲーム, minimax]
type: technique
field: comb
chapter: ゲーム
order: 450
level: 水
kind: [ゲーム, DP]
prerequisites: [game-basics]
related: [interval-dp, optimal-strategy-expectation, tree-dp, binary-search-answer#dp-check]
summary: 両者が「自分の得点 − 相手の得点」を最大化するゲームで、f(局面) = 手番の人が以後に得る差の最大値とおくと f = max(その手の得点 − f(次の局面)) と 1 本の式で書け、後ろから値が決まる。
complexity: null
signs:
  - {type: phrase, text: 両者が最適に行動したときの得点（の差）}
  - {type: phrase, text: 太郎は X − Y を最大化し、次郎は最小化する}
  - {type: phrase, text: 列の両端から交互に取る}
  - {type: phrase, text: 交互に駒を進めて得点を取り合う}
acl: []
frequency: B
frequency_evidence: recent 0・前提として届くページなし・古い ABC 6 問
sections:
  - {title: 得点差を 1 本の式で書く（符号の反転）, anchor: negamax}
  - {title: max と min を手番で使い分ける書き方, anchor: max-min}
  - {title: 区間・グリッド・盤面を状態にする, anchor: states}
  - {title: 貪欲が最適でない例, anchor: greedy-fails}
  - {title: 木の上のゲーム, anchor: tree, level: 黄}
  - {title: 答えを決め打ちして勝敗に直す, anchor: binary-search, level: 黄}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：両者が「自分の得点 − 相手の得点」を最大化するゲームで、f(局面) = 手番の人が以後に得る差の最大値とおくと f = max(その手の得点 − f(次の局面)) と 1 本の式で書け、後ろから値が決まる。
    - **いつ使うか**：
        - 両者が最適に行動したときの得点（の差）
        - 太郎は X − Y を最大化し、次郎は最小化する
        - 列の両端から交互に取る
        - 交互に駒を進めて得点を取り合う
    - **計算量**：（執筆時に書く）
    - **前提**：[ゲームの基本と勝敗の DP](../comb/game-basics.md)
