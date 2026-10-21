---
id: small-to-large
title: マージテク
aliases: [small-to-large, 小さい方を大きい方へ移す, データ構造をマージする一般的なテク, weighted union heuristic, DSU on Tree, Sack]
type: technique
field: tree
chapter: まとめる・分ける
order: 220
level: 水
kind: [データ構造, 木]
prerequisites: [union-find, ordered-set]
related: [tree-dp, union-find-applications, merge-process-tree, auxiliary-tree, euler-tour, bottleneck-path]
summary: 2 つの集合を併合するとき小さい方の要素を大きい方へ移すと、1 つの要素が移るのは高々 log N 回なので全体で O(N log N) になる。グループの併合と種類数の問い合わせや、部分木ごとの集計（DSU on Tree）に使う。
complexity: null
signs:
  - {type: phrase, text: グループの併合と、グループ内の種類数・個数の問い合わせ}
  - {type: phrase, text: 部分木ごとに集合（map）を持って併合する}
  - {type: phrase, text: すべての部分木について、色の種類数・最頻値を求める}
acl: [dsu]
frequency: B
frequency_evidence: recent 1（abc454_g）・前提として届くページなし・古い ABC 6 問
sections:
  - {title: 要素が移るのは高々 log N 回の理由, anchor: why-log}
  - {title: swap で入れ替える・大きい方を代表に残す, anchor: swap}
  - {title: Union-Find の代表元に map を持たせる, anchor: map-on-root}
  - {title: 森に辺を足すとき小さい方を根付け直す, anchor: reroot-smaller, level: 黄}
  - {title: 部分木ごとの集合の併合（木 DP での使い方は DP の章）, anchor: subtree-merge, level: 黄}
  - {title: DSU on Tree（重い子の結果を残す）, anchor: dsu-on-tree, level: 黄}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：2 つの集合を併合するとき小さい方の要素を大きい方へ移すと、1 つの要素が移るのは高々 log N 回なので全体で O(N log N) になる。グループの併合と種類数の問い合わせや、部分木ごとの集計（DSU on Tree）に使う。
    - **いつ使うか**：
        - グループの併合と、グループ内の種類数・個数の問い合わせ
        - 部分木ごとに集合（map）を持って併合する
        - すべての部分木について、色の種類数・最頻値を求める
    - **計算量**：（執筆時に書く）
    - **前提**：[Union-Find](../ds/union-find.md)、[set・multiset・map の応用](../ds/ordered-set.md)
