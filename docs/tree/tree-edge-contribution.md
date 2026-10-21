---
id: tree-edge-contribution
title: 辺で切って数える
aliases: [辺の寄与, 木の主客転倒, 全点対の距離の和, 全ペアのパスの寄与, contribution of edges]
type: technique
field: tree
chapter: 木全体の形
order: 120
level: 水
kind: [木, 考察]
prerequisites: [tree-traversal, contribution]
related: [union-find-applications, rerooting, centroid-decomposition, small-to-large, linearity-of-expectation]
summary: 全ペアのパスについての量の和を、各辺（頂点）が何ペアのパスに含まれるかで数え直す。辺で切った両側の大きさが s と N−s なら、その辺を通るペアは s(N−s) 個になる。
complexity: null
signs:
  - {type: phrase, text: 'すべての i < j について f(i, j) の総和'}
  - {type: phrase, text: 全ペアのパス上の最大値（最小値）の和}
  - {type: constraint, text: N ≤ 2×10^5 の木で、全ペア（N^2/2 組）についての和を求める}
acl: []
frequency: B
frequency_evidence: recent 1（abc479_e）・前提として届くページなし・古い ABC 4 問
sections:
  - {title: 辺を通るペアは s(N−s) 個, anchor: edge-pairs}
  - {title: 森の成分数 = 頂点数 − 辺数 に分けて数える, anchor: forest-count}
  - {title: パス上の最大値の和（重みの小さい順に併合して数える型は Union-Find の応用へ）, anchor: max-on-path}
  - {title: 期待値・特定の色を通らないパスへの応用, anchor: expectation, level: 黄}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：全ペアのパスについての量の和を、各辺（頂点）が何ペアのパスに含まれるかで数え直す。辺で切った両側の大きさが s と N−s なら、その辺を通るペアは s(N−s) 個になる。
    - **いつ使うか**：
        - すべての i < j について f(i, j) の総和
        - 全ペアのパス上の最大値（最小値）の和
        - N ≤ 2×10^5 の木で、全ペア（N^2/2 組）についての和を求める
    - **計算量**：（執筆時に書く）
    - **前提**：[根付き木と走査順](../tree/tree-traversal.md)、[主客転倒・寄与](../thinking/contribution.md)
