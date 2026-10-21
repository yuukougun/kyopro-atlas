---
id: union-find
title: Union-Find
aliases: [UF, DSU, Disjoint Set Union, disjoint set, 素集合データ構造, 経路圧縮, union by size]
type: technique
field: ds
chapter: Union-Find
order: 100
level: 基礎
kind: [データ構造, 連結性・全域木]
prerequisites: [graph-basics]
related: [connected-components, union-find-connectivity, minimum-spanning-tree, union-find-applications, weighted-union-find, small-to-large, acl-reading#components]
summary: 要素を互いに素なグループに分けて持ち、2 つのグループの併合と「同じグループか」の判定を、union by size と経路圧縮でならし O(α(N)) で行う。グループの大きさや個数も数えられる。
complexity: null
signs:
  - {type: phrase, text: 辺を追加していきながら、2 頂点が同じグループか・グループの大きさを答える}
  - {type: phrase, text: グループを合併する操作と、グループについての質問が交互に来る}
  - {type: phrase, text: 連結成分の個数・最大の連結成分の大きさ}
  - {type: constraint, text: 'N, Q ≤ 2×10^5 で辺の追加と質問が混ざる'}
acl: [dsu]
verify: [unionfind]
frequency: A
frequency_evidence: recent 1（abc451_e）・前提として 17 ページに届く（直接 9）・古い ABC 5 問
sections:
  - {title: 何ができるか（併合と判定。分割・削除はできない）, anchor: what-it-does}
  - {title: 保つ性質（各グループは根付き木で、根が代表元。parent は根なら −(サイズ)）, anchor: invariants}
  - {title: 各操作の手順（find は根までたどって経路圧縮、merge は根どうしを小さい方から大きい方へつなぐ）, anchor: operations}
  - {title: なぜ速いか（union by size だけで深さ log N、経路圧縮と合わせてならし O(α(N))）, anchor: complexity}
  - {title: 境界（同じグループどうしの併合・自己ループと多重辺・成分数は併合に成功した回数を引く・サイズの積のあふれ）, anchor: boundaries}
  - {title: 根にサイズ・辺数を持たせる（ほかの情報を持たせる型は Union-Find の応用）, anchor: size-and-edges}
  - {title: 使い分け（グラフが固定なら BFS・DFS、削除があるなら逆順の処理 → グラフの章）, anchor: choosing}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：要素を互いに素なグループに分けて持ち、2 つのグループの併合と「同じグループか」の判定を、union by size と経路圧縮でならし O(α(N)) で行う。グループの大きさや個数も数えられる。
    - **いつ使うか**：
        - 辺を追加していきながら、2 頂点が同じグループか・グループの大きさを答える
        - グループを合併する操作と、グループについての質問が交互に来る
        - 連結成分の個数・最大の連結成分の大きさ
        - N, Q ≤ 2×10^5 で辺の追加と質問が混ざる
    - **計算量**：（執筆時に書く）
    - **前提**：[グラフの表現と用語](../graph/graph-basics.md)
