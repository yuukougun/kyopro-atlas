---
id: game-basics
title: ゲームの基本と勝敗の DP
aliases: [ゲーム DP, 必勝法, 必勝・必敗, 勝ち局面・負け局面, 二人零和有限確定完全情報ゲーム, 手数の偶奇, 真似戦略, ペアリング戦略]
type: technique
field: comb
chapter: ゲーム
order: 440
level: 水
kind: [ゲーム, DP]
prerequisites: [memoized-recursion, dp-order]
related: [minimax, nim, grundy-number, game-retrograde-analysis, bit-dp, interactive, parity, invariant, symmetry-pigeonhole-casework#symmetry]
summary: 二人零和有限確定完全情報ゲームの各局面は、手番の人の必勝か必敗に決まる。終局から「負け局面へ 1 手で移れるなら勝ち、どこへ移っても勝ち局面なら負け」と DP で埋め、状態が大きすぎるなら手数の偶奇や真似戦略で決まらないかを疑う。
complexity: null
signs:
  - {type: phrase, text: 先手と後手が交互に操作し、両者が最適に行動したとき勝つのはどちらか}
  - {type: phrase, text: First / Second（Takahashi / Aoki）を出力する}
  - {type: constraint, text: カードの枚数 N ≤ 18 程度で、残りのカードの集合が局面になる}
  - {type: phrase, text: 盤面（配置）が対称・同じものが偶数個ずつある}
  - {type: phrase, text: 最終的な形が戦略によらず決まる}
  - {type: phrase, text: ジャッジと対戦する（インタラクティブ）}
acl: []
frequency: B
frequency_evidence: recent 0・前提として 5 ページに届く（直接 3）・古い ABC 6 問
sections:
  - {title: ゲームの前提（零和・有限・確定・完全情報）, anchor: assumptions}
  - {title: 必勝・必敗の定義と後ろ向きに決まる理由, anchor: win-lose}
  - {title: 勝敗の DP とメモ化再帰, anchor: game-dp}
  - {title: 状態の設計：集合（bitDP）・3^N・余り, anchor: state-design}
  - {title: 手番で取れる手が違うときは手番を状態に入れる, anchor: turn}
  - {title: 総手数の偶奇・不変量で決まるゲーム（最終形から数える）, anchor: move-parity}
  - {title: 真似戦略・ペアリング戦略（真似した手が合法かを確かめる）, anchor: mirror-strategy, level: 青}
  - {title: インタラクティブ：必勝戦略を実行する, anchor: interactive}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：二人零和有限確定完全情報ゲームの各局面は、手番の人の必勝か必敗に決まる。終局から「負け局面へ 1 手で移れるなら勝ち、どこへ移っても勝ち局面なら負け」と DP で埋め、状態が大きすぎるなら手数の偶奇や真似戦略で決まらないかを疑う。
    - **いつ使うか**：
        - 先手と後手が交互に操作し、両者が最適に行動したとき勝つのはどちらか
        - First / Second（Takahashi / Aoki）を出力する
        - カードの枚数 N ≤ 18 程度で、残りのカードの集合が局面になる
        - 盤面（配置）が対称・同じものが偶数個ずつある
        - 最終的な形が戦略によらず決まる
        - ジャッジと対戦する（インタラクティブ）
    - **計算量**：（執筆時に書く）
    - **前提**：[メモ化再帰](../dp/memoized-recursion.md)、[DP の計算順序](../dp/dp-order.md)
