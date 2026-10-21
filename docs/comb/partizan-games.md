---
id: partizan-games
title: 非不偏ゲーム
aliases: [超現実数, 組合せゲーム理論, Hackenbush, partizan game, combinatorial game theory]
type: overview
field: comb
chapter: ゲーム
order: 490
level: 発展
kind: [ゲーム]
prerequisites: [grundy-number]
related: [nim]
summary: 先手と後手で取れる手が違うゲームでは Grundy 数が使えないので、局面に数（超現実数）を割り当て、独立な部分の和の符号で勝敗を判定する。
complexity: null
signs:
  - {type: phrase, text: 先手と後手で動かせる駒や手が違う}
  - {type: phrase, text: 独立な部分の和で勝敗を判定したい}
acl: []
frequency: C
frequency_evidence: recent 0・前提として届くページなし・古い ABC 2 問
sections:
  - {title: 何ができるか, anchor: what}
  - {title: Grundy 数が使えない理由, anchor: why-not-grundy}
  - {title: 局面に数を割り当てて和を取る, anchor: surreal}
  - {title: 手数の貯金として見る, anchor: tempo}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：先手と後手で取れる手が違うゲームでは Grundy 数が使えないので、局面に数（超現実数）を割り当て、独立な部分の和の符号で勝敗を判定する。
    - **いつ使うか**：
        - 先手と後手で動かせる駒や手が違う
        - 独立な部分の和で勝敗を判定したい
    - **計算量**：（執筆時に書く）
    - **前提**：[Grundy 数と Sprague-Grundy の定理](../comb/grundy-number.md)
