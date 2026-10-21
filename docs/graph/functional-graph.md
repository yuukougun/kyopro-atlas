---
id: functional-graph
title: Functional graph（出次数 1 のグラフ）
aliases: [関数グラフ, ρ 形, rho 形, successor graph]
type: technique
field: graph
chapter: 有向グラフ
order: 260
level: 水
kind: [グラフ探索]
prerequisites: [cycle-detection]
related: [doubling, periodicity, namori-graph, scc, permutation-cycles, topological-sort, tree-basics]
summary: 各頂点から出る辺がちょうど 1 本の有向グラフは、各成分に閉路がちょうど 1 つあり、そこへ木が流れ込む ρ の形になる。K 回進んだ位置は、閉路に入るまでと閉路の周回に分けて求める。
complexity: null
signs:
  - {type: phrase, text: 各 i から A_i へ移動する}
  - {type: constraint, text: K 回（K ≤ 10^18）移動した後の位置}
  - {type: phrase, text: 嫌いな相手・行き先が 1 人（1 つ）ずつ決まっている}
  - {type: shape, text: 遷移が x → f(x) の写像 1 つで決まる}
acl: [scc_graph]
frequency: B
frequency_evidence: recent 0・前提として届くページなし・古い ABC 5 問
sections:
  - {title: 各成分に閉路がちょうど 1 つある理由, anchor: one-cycle}
  - {title: K 回後の位置（しっぽと周回に分ける・ダブリング）, anchor: k-steps}
  - {title: 全頂点について閉路上かを求める（入次数 0 から剥がす・SCC）, anchor: on-cycle}
  - {title: 閉路ごとの集計・到達できる頂点の数, anchor: per-cycle}
  - {title: 置換は閉路の集まり（巡回分解は数え上げの章）, anchor: permutation}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：各頂点から出る辺がちょうど 1 本の有向グラフは、各成分に閉路がちょうど 1 つあり、そこへ木が流れ込む ρ の形になる。K 回進んだ位置は、閉路に入るまでと閉路の周回に分けて求める。
    - **いつ使うか**：
        - 各 i から A_i へ移動する
        - K 回（K ≤ 10^18）移動した後の位置
        - 嫌いな相手・行き先が 1 人（1 つ）ずつ決まっている
        - 遷移が x → f(x) の写像 1 つで決まる
    - **計算量**：（執筆時に書く）
    - **前提**：[閉路の検出と復元](../graph/cycle-detection.md)
