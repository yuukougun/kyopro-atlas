---
id: game-retrograde-analysis
title: 後退解析
aliases: [retrograde analysis, 引き分けのあるゲーム, 閉路のあるグラフ上のゲーム, グラフ上のゲーム]
type: technique
field: comb
chapter: ゲーム
order: 480
level: 黄
kind: [ゲーム, DP, グラフ探索]
prerequisites: [game-basics, bfs]
related: [topological-sort, dijkstra, cycle-detection]
summary: 局面の遷移に閉路があり引き分け（終わらない）もありうるゲームで、終局から逆辺をたどって勝敗を確定させる。勝ちと確定していない行き先の数が 0 になれば負け、負け局面へ移れれば勝ちと確定させ、最後まで決まらない局面が引き分けになる。
complexity: null
signs:
  - {type: phrase, text: 無限に続く場合は Draw（引き分け）を出力する}
  - {type: phrase, text: 同じ局面が繰り返し現れうる}
  - {type: phrase, text: グラフ上でコマを動かすゲーム・しりとり}
acl: []
frequency: C
frequency_evidence: recent 0・前提として届くページなし・古い ABC 2 問
sections:
  - {title: メモ化再帰が止まらない理由, anchor: why-not-memo}
  - {title: 逆辺と、勝ちと確定していない行き先の数のカウンタ, anchor: counter}
  - {title: 確定の規則（負けへ移れる → 勝ち、すべて勝ちへ → 負け）, anchor: rules}
  - {title: 決まらない局面 = 引き分け, anchor: draw}
  - {title: 得点のあるゲームはダイクストラの要領で確定させる, anchor: weighted, level: 発展}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：局面の遷移に閉路があり引き分け（終わらない）もありうるゲームで、終局から逆辺をたどって勝敗を確定させる。勝ちと確定していない行き先の数が 0 になれば負け、負け局面へ移れれば勝ちと確定させ、最後まで決まらない局面が引き分けになる。
    - **いつ使うか**：
        - 無限に続く場合は Draw（引き分け）を出力する
        - 同じ局面が繰り返し現れうる
        - グラフ上でコマを動かすゲーム・しりとり
    - **計算量**：（執筆時に書く）
    - **前提**：[ゲームの基本と勝敗の DP](../comb/game-basics.md)、[幅優先探索（BFS）と無重み最短路](../graph/bfs.md)
