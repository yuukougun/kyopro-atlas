---
id: weighted-union-find
title: 重み付き Union-Find
aliases: [weighted union-find, ポテンシャル付き Union-Find, 重み付き UF, 偶奇の Union-Find, 二部グラフの Union-Find, 頂点倍化の Union-Find, 差分の矛盾判定]
type: technique
field: ds
chapter: Union-Find
order: 120
level: 水
kind: [データ構造, 連結性・全域木]
prerequisites: [union-find]
related: [bipartite-graph, difference-constraints, dfs, union-find-applications]
summary: x_v − x_u = w の形の情報を順に受け取りながら、矛盾の判定と同じ成分の 2 要素の差の取得を行う。各要素に親との差を持たせた Union-Find で、差を XOR にすると 2 色の塗り分けになる。
complexity: null
signs:
  - {type: phrase, text: x_R − x_L = D の形の情報が順に与えられ、矛盾しないかを判定する}
  - {type: phrase, text: 相対的な位置・差だけが分かっている}
  - {type: phrase, text: 正直者と嘘つき・2 色に塗り分けられるか}
  - {type: constraint, text: 情報と質問が交互に Q ≤ 2×10^5 回来る}
acl: []
verify: [unionfind_with_potential, unionfind_with_potential_non_commutative_group]
frequency: B
frequency_evidence: recent 1（abc451_f）・前提として届くページなし・古い ABC 4 問
sections:
  - {title: '保つ性質（diff[v] は親との差。経路圧縮の後は根との差）', anchor: invariants}
  - {title: 各操作の手順（find は親を先に圧縮してから差を足す、merge は根どうしの差に直してつなぐ、向きを入れ替えたら符号を反転）, anchor: operations}
  - {title: 矛盾の判定と差の取得, anchor: consistency}
  - {title: 一般化（群なら載る。XOR で偶奇・二部グラフの判定、頂点を 2 倍にする Union-Find）, anchor: generalization}
  - {title: 使い分け（一度だけ判定するなら DFS で十分、不等式の制約なら差分制約の最短路）, anchor: choosing}
  - {title: 落とし穴（圧縮の順序・符号・成分ごとの矛盾フラグの引き継ぎ）, anchor: pitfalls}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：x_v − x_u = w の形の情報を順に受け取りながら、矛盾の判定と同じ成分の 2 要素の差の取得を行う。各要素に親との差を持たせた Union-Find で、差を XOR にすると 2 色の塗り分けになる。
    - **いつ使うか**：
        - x_R − x_L = D の形の情報が順に与えられ、矛盾しないかを判定する
        - 相対的な位置・差だけが分かっている
        - 正直者と嘘つき・2 色に塗り分けられるか
        - 情報と質問が交互に Q ≤ 2×10^5 回来る
    - **計算量**：（執筆時に書く）
    - **前提**：[Union-Find](../ds/union-find.md)
