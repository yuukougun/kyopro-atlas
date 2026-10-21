---
id: topological-sort
title: トポロジカルソート
aliases: [トポロジカル順序, Kahn 法, 入次数, DAG, topological sort]
type: technique
field: graph
chapter: 有向グラフ
order: 240
level: 基礎
kind: [グラフ探索]
prerequisites: [dfs, bfs]
related: [dp-dag, scc, cycle-detection, dp-order, game-retrograde-analysis]
summary: 閉路のない有向グラフの頂点を、すべての辺が前から後ろへ向くように O(N+M) で並べる。入次数 0 の頂点から取り出す Kahn 法か DFS の帰りがけ順の逆で求め、閉路があれば並べられない。
complexity: null
signs:
  - {type: phrase, text: a は b より前・依存関係・前提条件}
  - {type: phrase, text: 条件を満たす辞書順最小の順序・順序が一意か}
  - {type: phrase, text: 矛盾（閉路）があれば −1}
acl: [scc_graph]
frequency: B
frequency_evidence: recent 1（abc478_e）・前提として 5 ページに届く（直接 2）・古い ABC 4 問
sections:
  - {title: Kahn 法と DFS の帰りがけ順, anchor: kahn-dfs}
  - {title: 辞書順最小は優先度付きキューの Kahn 法, anchor: lexicographic}
  - {title: 順序が一意かの判定, anchor: unique}
  - {title: 出次数 0 の頂点から逆向きに剥がす, anchor: peel-sinks}
  - {title: DAG 上の DP へ（DP の章）, anchor: to-dag-dp}
  - {title: ACL の scc_graph を使う（DAG なら scc() の順がトポロジカル順）, anchor: acl}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：閉路のない有向グラフの頂点を、すべての辺が前から後ろへ向くように O(N+M) で並べる。入次数 0 の頂点から取り出す Kahn 法か DFS の帰りがけ順の逆で求め、閉路があれば並べられない。
    - **いつ使うか**：
        - a は b より前・依存関係・前提条件
        - 条件を満たす辞書順最小の順序・順序が一意か
        - 矛盾（閉路）があれば −1
    - **計算量**：（執筆時に書く）
    - **前提**：[深さ優先探索（DFS）](../graph/dfs.md)、[幅優先探索（BFS）と無重み最短路](../graph/bfs.md)
