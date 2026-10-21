---
id: counting-labeled-graphs
title: 連結なグラフの数え上げ
aliases: [連結グラフの数え上げ, 全体から非連結を引く, 頂点 1 を含む成分で分類, 条件を満たすグラフの個数]
type: technique
field: comb
chapter: 置換・分割・木の数え上げ
order: 310
level: 黄
kind: [数え上げ, DP]
prerequisites: [counting-mindset, binomial-precompute, subset-enumeration-dp]
related: [counting-dedup, zeta-mobius-subset, connected-components, bfs]
summary: 連結なものを全体 − 非連結なもので数え、非連結なものは頂点 1 を含む連結成分の大きさや頂点集合で分類して DP する。代表の頂点 1 を含む成分から決めるので、成分の順序による重複が出ない。
complexity: null
signs:
  - {type: phrase, text: 条件を満たす（連結な）グラフの個数}
  - {type: phrase, text: 辺の部分集合のうち、指定した頂点どうしが連結になるものの数}
  - {type: constraint, text: N ≤ 17 程度の頂点数で、条件を満たす辺の選び方を数える}
  - {type: phrase, text: 最大の連結成分の大きさがちょうど L}
acl: []
frequency: B
frequency_evidence: recent 0・前提として届くページなし・古い ABC 3 問
sections:
  - {title: 連結 = 全体 − 非連結, anchor: complement}
  - {title: 頂点 1 を含む成分で分類する（重複を防ぐ代表）, anchor: component-of-1}
  - {title: 頂点集合ごとの DP（3^N）, anchor: subset-dp}
  - {title: 大きさだけで決まるときは二項係数で頂点を選ぶ, anchor: by-size}
  - {title: 距離の層ごとに頂点を配る, anchor: bfs-layers}
  - {title: 「ちょうど L」を「L 以下」の差で数える, anchor: exactly-l}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：連結なものを全体 − 非連結なもので数え、非連結なものは頂点 1 を含む連結成分の大きさや頂点集合で分類して DP する。代表の頂点 1 を含む成分から決めるので、成分の順序による重複が出ない。
    - **いつ使うか**：
        - 条件を満たす（連結な）グラフの個数
        - 辺の部分集合のうち、指定した頂点どうしが連結になるものの数
        - N ≤ 17 程度の頂点数で、条件を満たす辺の選び方を数える
        - 最大の連結成分の大きさがちょうど L
    - **計算量**：（執筆時に書く）
    - **前提**：[数え上げの考え方](../comb/counting-mindset.md)、[二項係数の前計算](../comb/binomial-precompute.md)、[部分集合を列挙する DP](../dp/subset-enumeration-dp.md)
