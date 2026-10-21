---
id: difference-constraints
title: 差分制約（牛ゲー）
aliases: [牛ゲー, 差分制約系, 不等式を辺にする, difference constraints]
type: technique
field: graph
chapter: 最短路
order: 180
level: 青
kind: [最短路]
prerequisites: [bellman-ford, prefix-sum]
related: [weighted-union-find, dijkstra, graph-modeling]
summary: x_v − x_u ≤ c の形の条件を辺 u→v（重み c）と読み、始点からの最短距離で全条件を満たす最大の解を求める。負閉路があれば解はなく、区間の和の条件は累積和の差に直せる。
complexity: null
signs:
  - {type: phrase, text: x_j − x_i ≤ c の形の条件の下で、ある変数を最大化（最小化）する}
  - {type: phrase, text: 区間の和が S 以上・以下という条件が並ぶ}
  - {type: phrase, text: 位置の差の情報が矛盾しないか}
  - {type: shape, text: 条件を整理すると x_v ≤ x_u + c の形の不等式の集まりになる}
acl: []
frequency: C
frequency_evidence: recent 0・前提として届くページなし・古い ABC 2 問
sections:
  - {title: 不等式を辺にする向き, anchor: direction}
  - {title: 最短距離が最大の解になる理由, anchor: why-maximum}
  - {title: 等式・正値・区間の和の条件の書き方, anchor: encodings}
  - {title: 負辺があればベルマンフォード、なければダイクストラ, anchor: which-algorithm}
  - {title: 整合性の判定だけなら重み付き Union-Find（データ構造の章）, anchor: consistency}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：x_v − x_u ≤ c の形の条件を辺 u→v（重み c）と読み、始点からの最短距離で全条件を満たす最大の解を求める。負閉路があれば解はなく、区間の和の条件は累積和の差に直せる。
    - **いつ使うか**：
        - x_j − x_i ≤ c の形の条件の下で、ある変数を最大化（最小化）する
        - 区間の和が S 以上・以下という条件が並ぶ
        - 位置の差の情報が矛盾しないか
        - 条件を整理すると x_v ≤ x_u + c の形の不等式の集まりになる
    - **計算量**：（執筆時に書く）
    - **前提**：[ベルマンフォード法](../graph/bellman-ford.md)、[累積和](../basics/prefix-sum.md)
