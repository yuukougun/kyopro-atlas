---
id: counting-fix-order
title: 順序を固定して数える
aliases: [相対順序の固定, ソートしてから数える, 数える順番の工夫, n!/k!]
type: technique
field: comb
chapter: 数え方の考え方
order: 90
level: 水
kind: [数え上げ, 考察]
prerequisites: [counting-mindset]
related: [counting-basics, contribution, fix-variable, probability-symmetry, insertion-dp, rerooting, sorting-techniques]
summary: 並べ方の一部の相対順序を固定して数え、全体の何分の一かを掛ける（k 個の順序が決まっていれば n!/k!）。ソート順や BFS 順など、次の選択肢の数が一定になる順番で決めれば積の法則が使える。
complexity: null
signs:
  - {type: phrase, text: A は B より先に来る、という順番の制約がある並べ方の数}
  - {type: phrase, text: 選んだ K 個の最大値（最小値）の総和}
  - {type: phrase, text: 木の頂点に、親が子より先になるように番号を振る方法の数}
acl: []
frequency: B
frequency_evidence: recent 0・前提として届くページなし・古い ABC 3 問
sections:
  - {title: 相対順序を固定する（n!/k!）, anchor: relative-order}
  - {title: ソートして最大・最小を固定する, anchor: sort-and-fix}
  - {title: 積の法則が使える順番で決める（BFS 順）, anchor: bfs-order}
  - {title: 木の上の順番 n!/Π 部分木の大きさ, anchor: tree-order, level: 黄}
  - {title: 順序を状態に持つ DP（挿入 DP・bitDP）との使い分け, anchor: vs-dp}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：並べ方の一部の相対順序を固定して数え、全体の何分の一かを掛ける（k 個の順序が決まっていれば n!/k!）。ソート順や BFS 順など、次の選択肢の数が一定になる順番で決めれば積の法則が使える。
    - **いつ使うか**：
        - A は B より先に来る、という順番の制約がある並べ方の数
        - 選んだ K 個の最大値（最小値）の総和
        - 木の頂点に、親が子より先になるように番号を振る方法の数
    - **計算量**：（執筆時に書く）
    - **前提**：[数え上げの考え方](../comb/counting-mindset.md)
