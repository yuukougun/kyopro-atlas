---
id: time-dependent-dijkstra
title: 時刻で変わる辺の最短路
aliases: [時刻依存の最短路, 待機, 最終電車, 出発時刻, time-dependent shortest path]
type: technique
field: graph
chapter: 最短路
order: 170
level: 水
kind: [最短路]
prerequisites: [dijkstra]
related: [extended-dijkstra]
summary: 辺の所要時間が出発時刻で変わる最短路は、早く着いて損をしない（待てる）なら、各頂点で最も早い到着時刻だけを持つダイクストラで求まる。終点に間に合う最も遅い出発時刻は逆向きに確定させる。
complexity: null
signs:
  - {type: phrase, text: 決まった時刻にしか出発できない・待つことができる}
  - {type: phrase, text: 出発時刻によって所要時間が変わる}
  - {type: phrase, text: 終点に間に合う最も遅い出発時刻}
acl: []
frequency: B
frequency_evidence: recent 0・前提として届くページなし・古い ABC 3 問
sections:
  - {title: 早く着いて損をしない性質（FIFO 性）, anchor: fifo}
  - {title: 次の出発時刻まで待つ遷移, anchor: wait}
  - {title: 最終電車型：終点から逆向きに最も遅い時刻を確定させる, anchor: latest-departure}
  - {title: 最適な出発時刻を計算してから進む, anchor: optimal-departure, level: 青}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：辺の所要時間が出発時刻で変わる最短路は、早く着いて損をしない（待てる）なら、各頂点で最も早い到着時刻だけを持つダイクストラで求まる。終点に間に合う最も遅い出発時刻は逆向きに確定させる。
    - **いつ使うか**：
        - 決まった時刻にしか出発できない・待つことができる
        - 出発時刻によって所要時間が変わる
        - 終点に間に合う最も遅い出発時刻
    - **計算量**：（執筆時に書く）
    - **前提**：[ダイクストラ法](../graph/dijkstra.md)
