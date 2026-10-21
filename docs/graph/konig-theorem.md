---
id: konig-theorem
title: König の定理
aliases: [Konig の定理, 最小頂点被覆, 最大独立集合, 最小辺被覆, LP の半整数性, König's theorem]
type: technique
field: graph
chapter: フロー・マッチング
order: 430
level: 黄
kind: [フロー・マッチング]
prerequisites: [bipartite-matching, min-cut]
related: [project-selection, chromatic-number, dilworth-path-cover]
summary: 二部グラフでは最大マッチングの大きさが最小頂点被覆の大きさに等しく、最大独立集合は頂点数から最小頂点被覆を引いたものになる。被覆は最小カットから復元できる。
complexity: null
signs:
  - {type: phrase, text: 衝突する（隣り合う）ものを同時に選ばずに最大数選ぶ}
  - {type: phrase, text: すべての辺（マス）を監視するのに必要な最小数}
  - {type: phrase, text: 市松模様・偶奇で 2 つのグループに分かれる}
acl: [mf_graph]
frequency: B
frequency_evidence: recent 1（abc461_g）・前提として届くページなし・古い ABC 2 問
sections:
  - {title: König の定理と 3 つの関係（頂点被覆・独立集合・辺被覆）, anchor: theorem}
  - {title: 被覆の復元（最小カットから）, anchor: restore}
  - {title: 二部グラフに作り直す（市松模様・偶奇）, anchor: make-bipartite}
  - {title: 一般グラフでは難しい（彩色数・最大独立集合のページへ）, anchor: general-graph}
  - {title: 頂点を 2 倍にして二部グラフにする（LP の半整数性）, anchor: lp-half-integrality, level: 発展}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：二部グラフでは最大マッチングの大きさが最小頂点被覆の大きさに等しく、最大独立集合は頂点数から最小頂点被覆を引いたものになる。被覆は最小カットから復元できる。
    - **いつ使うか**：
        - 衝突する（隣り合う）ものを同時に選ばずに最大数選ぶ
        - すべての辺（マス）を監視するのに必要な最小数
        - 市松模様・偶奇で 2 つのグループに分かれる
    - **計算量**：（執筆時に書く）
    - **前提**：[二部マッチング](../graph/bipartite-matching.md)、[最小カット](../graph/min-cut.md)
