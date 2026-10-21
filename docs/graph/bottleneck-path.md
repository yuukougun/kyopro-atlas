---
id: bottleneck-path
title: 最小ボトルネック路
aliases: [minimax 経路, ボトルネック, 経路上の最大の辺の最小化, bottleneck path]
type: technique
field: graph
chapter: 連結性と全域木
order: 310
level: 青
kind: [連結性・全域木]
prerequisites: [minimum-spanning-tree, union-find-connectivity]
related: [merge-process-tree, binary-search-answer, small-to-large, parallel-binary-search, partially-persistent-union-find, lca]
summary: 経路上の辺の最大値を最小にする経路は最小全域木の上で実現でき、Kruskal 法で辺を足して 2 点が初めてつながったときの重みが答えになる。多数の 2 点の質問は、成分にクエリを持たせる併合か併合過程の木で答える。
complexity: null
signs:
  - {type: phrase, text: 経路上の最大の辺（最小の頂点）を最小化（最大化）する}
  - {type: phrase, text: 重さ・高さの制限以下で行けるか}
  - {type: phrase, text: しきい値を上げていくと連結になる時刻}
acl: [dsu]
frequency: B
frequency_evidence: recent 0・前提として届くページなし・古い ABC 3 問
sections:
  - {title: 最小全域木の上の経路がボトルネック最小になる理由（カット性質）, anchor: why-mst}
  - {title: Kruskal の順に成分を併合しながら答える, anchor: kruskal-order}
  - {title: 多数の 2 点の質問：成分にクエリを持たせて小さい方から移す, anchor: many-queries, level: 黄}
  - {title: 併合過程の木（Kruskal 再構築木）でオンラインに答える（木の章へ）, anchor: reconstruction-tree, level: 発展}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：経路上の辺の最大値を最小にする経路は最小全域木の上で実現でき、Kruskal 法で辺を足して 2 点が初めてつながったときの重みが答えになる。多数の 2 点の質問は、成分にクエリを持たせる併合か併合過程の木で答える。
    - **いつ使うか**：
        - 経路上の最大の辺（最小の頂点）を最小化（最大化）する
        - 重さ・高さの制限以下で行けるか
        - しきい値を上げていくと連結になる時刻
    - **計算量**：（執筆時に書く）
    - **前提**：[最小全域木](../graph/minimum-spanning-tree.md)、[Union-Find で連結性を扱う](../graph/union-find-connectivity.md)
