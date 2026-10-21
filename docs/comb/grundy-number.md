---
id: grundy-number
title: Grundy 数と Sprague-Grundy の定理
aliases: [nimber, Sprague-Grundy の定理, ゲームの和, Grundy 数の周期性, Sprague-Grundy theorem, Grundy number]
type: technique
field: comb
chapter: ゲーム
order: 470
level: 青
kind: [ゲーム]
prerequisites: [nim]
related: [interval-dp, mex, stress-testing, partizan-games]
summary: 不偏ゲームの局面に Grundy 数 g = mex{次の局面の g} を割り当てると g = 0 ⇔ 必敗で、独立なゲームの和の Grundy 数は各 Grundy 数の XOR になる。状態が大きければ小さい局面の表から周期を見つける。
complexity: null
signs:
  - {type: phrase, text: 複数の山（盤面）があり、どれか 1 つを選んで操作する}
  - {type: phrase, text: 先手と後手の取れる手が同じ}
  - {type: constraint, text: 山の大きさが 10^18 程度まであり、小さい山から全部の局面を調べられない}
acl: []
frequency: B
frequency_evidence: recent 0・前提として 1 ページに届く（直接 1）・古い ABC 5 問
sections:
  - {title: mex と Grundy 数の定義, anchor: definition}
  - {title: Grundy 数を Nim の山の大きさとみなせる理由, anchor: as-nim}
  - {title: ゲームの和は XOR, anchor: sum}
  - {title: Grundy 数を DP で求める（区間・2 種類の石）, anchor: dp}
  - {title: 規則を見つける：小さい局面の表と周期, anchor: patterns}
  - {title: 使えない場合（1 手で複数を動かす・非不偏）, anchor: limitations}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：不偏ゲームの局面に Grundy 数 g = mex{次の局面の g} を割り当てると g = 0 ⇔ 必敗で、独立なゲームの和の Grundy 数は各 Grundy 数の XOR になる。状態が大きければ小さい局面の表から周期を見つける。
    - **いつ使うか**：
        - 複数の山（盤面）があり、どれか 1 つを選んで操作する
        - 先手と後手の取れる手が同じ
        - 山の大きさが 10^18 程度まであり、小さい山から全部の局面を調べられない
    - **計算量**：（執筆時に書く）
    - **前提**：[Nim と XOR](../comb/nim.md)
