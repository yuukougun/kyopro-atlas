---
id: cht
title: Convex Hull Trick と Li Chao Tree
aliases: [CHT, 傾き最適化, 斜率优化, 李超线段树, 直線の最小値]
type: overview
field: dp
chapter: DP の高速化
order: 350
level: 発展
kind: [DP, データ構造]
prerequisites: [dp-basics, convex-hull]
related: [dp-segment-tree, segment-tree, monge, alien-dp, dp-speedup-overview]
summary: dp[i] = min_j (dp[j] + a_j·x_i + b_j) のように遷移が一次関数の最小になる DP を、下側の包絡線を持って速くする。単調なら deque、そうでなければ Li Chao Tree を使う。
complexity: null
signs:
  - {type: shape, text: 遷移のコストが i と j の積の項を 1 つだけ含む（(h_i − h_j)^2 など）}
  - {type: phrase, text: 直線を追加しながら、任意の x での最小値・最大値を答える}
acl: []
verify: [line_add_get_min, segment_add_get_min]
frequency: C
frequency_evidence: recent 0・前提として届くページなし・古い ABC 2 問
sections:
  - {title: 遷移を直線の最小値に変形する, anchor: lines}
  - {title: 下側の包絡線と不要な直線（傾きもクエリも単調なら deque）, anchor: lower-envelope}
  - {title: クエリが単調でないとき（二分探索）, anchor: non-monotone-queries}
  - {title: Li Chao Tree（区間の真ん中で勝つ直線を残す）, anchor: li-chao-tree}
  - {title: 落とし穴：交点の比較は掛け算で（__int128）・最小と最大の取り違え・同じ傾き, anchor: pitfalls}
  - {title: ライブラリでの検証（Library Checker の line_add_get_min・segment_add_get_min）, anchor: verify}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：dp[i] = min_j (dp[j] + a_j·x_i + b_j) のように遷移が一次関数の最小になる DP を、下側の包絡線を持って速くする。単調なら deque、そうでなければ Li Chao Tree を使う。
    - **いつ使うか**：
        - 遷移のコストが i と j の積の項を 1 つだけ含む（(h_i − h_j)^2 など）
        - 直線を追加しながら、任意の x での最小値・最大値を答える
    - **計算量**：（執筆時に書く）
    - **前提**：[DP の基本](../dp/dp-basics.md)、[凸包と凸多角形](../geometry/convex-hull.md)
