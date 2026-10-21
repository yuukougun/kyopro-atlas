---
id: parity
title: 偶奇に着目する
aliases: [パリティ, 偶奇性, mod 2, 市松模様, チェッカーボード, parity]
type: thinking
field: thinking
order: 50
level: 基礎
kind: [考察]
prerequisites: []
related: [invariant, bipartite-graph, game-basics#move-parity, union-find-applications, interactive]
summary: 1 歩ごとに (x + y) の偶奇が入れ替わる、±1 をちょうど K 回なら差と K の偶奇がそろう、など偶奇の必要条件から可否を判定する。グリッドでは市松模様の色の偶奇が不変量になる。
complexity: null
signs:
  - {type: phrase, text: ちょうど K 回の操作・±1 の移動}
  - {type: phrase, text: 和が偶数という条件}
  - {type: phrase, text: グリッドを 1 マスずつ動く操作の可否}
  - {type: phrase, text: チェス盤の塗り分け・ドミノの敷き詰め}
acl: []
frequency: A
frequency_evidence: recent 5（abc454_e・abc459_g・abc460_d・abc467_e・abc474_g）・前提として 1 ページに届く（直接 1）・古い ABC 2 問
sections:
  - {title: 1 歩ごとに偶奇が入れ替わる, anchor: alternating}
  - {title: ちょうど K 回なら偶奇がそろうことが必要, anchor: exactly-k}
  - {title: 偶奇の条件でつながった成分（Union-Find）, anchor: components}
  - {title: 市松模様の偶奇, anchor: checkerboard, level: 青}
  - {title: 二部グラフ・ゲームとのつながり, anchor: bipartite-game}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：1 歩ごとに (x + y) の偶奇が入れ替わる、±1 をちょうど K 回なら差と K の偶奇がそろう、など偶奇の必要条件から可否を判定する。グリッドでは市松模様の色の偶奇が不変量になる。
    - **いつ使うか**：
        - ちょうど K 回の操作・±1 の移動
        - 和が偶数という条件
        - グリッドを 1 マスずつ動く操作の可否
        - チェス盤の塗り分け・ドミノの敷き詰め
    - **計算量**：（執筆時に書く）
    - **前提**：なし
