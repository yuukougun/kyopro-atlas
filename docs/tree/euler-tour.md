---
id: euler-tour
title: オイラーツアー
aliases: [Euler Tour, 行きがけ順の番号付け, in/out, 木の平坦化, tree flattening, 辺のオイラーツアー, DFS 順で部分木を区間にする]
type: technique
field: tree
chapter: 部分木とパスのクエリ
order: 180
level: 青
kind: [木, 区間クエリ]
prerequisites: [tree-traversal, fenwick-tree]
related: [segment-tree, lazy-segment-tree, tree-imos, lca, hld, small-to-large, mo-algorithm, euler-path]
summary: DFS の行きがけ順に番号 in[v] を振り、子孫を回り終えた時点の番号 out[v] を記録すると、v の部分木が列の区間 [in[v], out[v]) になる。部分木の和や加算が BIT・セグメント木の区間クエリになる。
complexity: null
signs:
  - {type: phrase, text: 部分木の和・最大・個数を、更新を挟みながら聞かれる}
  - {type: phrase, text: 部分木に加算する・辺を取り除いたときの片側の和}
  - {type: phrase, text: u が v の祖先か・v の子孫のうち深さ d のもの}
  - {type: phrase, text: 辺の重みの変更と 2 点間の距離のクエリ}
  - {type: constraint, text: 'N, Q ≤ 2×10^5 で、部分木への更新と質問が交互に来る'}
acl: [fenwick_tree, segtree, lazy_segtree]
verify: [vertex_add_subtree_sum]
frequency: A
frequency_evidence: recent 2（abc453_g・abc477_g）・前提として 5 ページに届く（直接 3）・古い ABC 6 問
sections:
  - {title: 「オイラーツアー」の 4 つの意味, anchor: meanings}
  - {title: 部分木が区間になる理由と in・out の定義, anchor: in-out}
  - {title: 祖先の判定と深さごとの頂点の数, anchor: ancestor-depth}
  - {title: 部分木の補集合は 2 つの区間, anchor: complement}
  - {title: 根からのパスを区間で扱う（辺の重みを子の部分木に配る）, anchor: root-path}
  - {title: 木上の Mo（データ構造の章）, anchor: mo-on-tree}
  - {title: 逆元がない演算・パスへの一括更新は HL 分解, anchor: to-hld, level: 発展}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：DFS の行きがけ順に番号 in[v] を振り、子孫を回り終えた時点の番号 out[v] を記録すると、v の部分木が列の区間 [in[v], out[v]) になる。部分木の和や加算が BIT・セグメント木の区間クエリになる。
    - **いつ使うか**：
        - 部分木の和・最大・個数を、更新を挟みながら聞かれる
        - 部分木に加算する・辺を取り除いたときの片側の和
        - u が v の祖先か・v の子孫のうち深さ d のもの
        - 辺の重みの変更と 2 点間の距離のクエリ
        - N, Q ≤ 2×10^5 で、部分木への更新と質問が交互に来る
    - **計算量**：（執筆時に書く）
    - **前提**：[根付き木と走査順](../tree/tree-traversal.md)、[BIT（Fenwick Tree）](../ds/fenwick-tree.md)
