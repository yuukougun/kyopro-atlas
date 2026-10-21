---
id: interval-set
title: 区間を set で管理する
aliases: [IntervalSet, RangeSet, ODT, Chtholly Tree, 珂朵莉树, 互いに素な区間の集合]
type: technique
field: ds
chapter: 標準コンテナの応用
order: 50
level: 水
kind: [データ構造]
prerequisites: [ordered-set]
related: [union-find-applications, lazy-segment-tree, segment-tree-beats, complexity-estimation, coordinate-compression]
summary: 互いに重ならない区間を左端をキーにした set・map で持ち、点を含む区間の検索・区間の追加と併合・区間への代入を、ならし O(log N) で行う。座標が 10^9 でも使える。
complexity: null
signs:
  - {type: phrase, text: 区間を塗るたびに、塗られたマスの数や色ごとのマスの数を答える}
  - {type: phrase, text: 同じ色でつながった区間をまとめて塗り替える}
  - {type: phrase, text: 点 x が覆われているか・x を含む区間はどこか}
  - {type: constraint, text: 座標が 10^9 まで（配列の添字にできない）}
acl: []
verify: []
frequency: B
frequency_evidence: recent 0・前提として届くページなし・古い ABC 6 問
sections:
  - {title: 持ち方（左端をキーにした map・両端の番兵の区間）, anchor: representation}
  - {title: x を含む区間の検索（upper_bound の 1 つ前）, anchor: find}
  - {title: split(x)（区間の分割）を先に書き、代入・削除はその組み合わせで書く, anchor: split}
  - {title: なぜならしで速いか（新しくできる区間は O(1) 個、消える区間は一度だけ）と、走査だけの操作が混ざると崩れる理由, anchor: amortized}
  - {title: 応用（mex・塗り分け・和集合の長さ・値ごとの合計の差分更新）, anchor: applications}
  - {title: 使い分け（飛ばすだけなら次の空きへ飛ぶ Union-Find、座標が小さく区間和も要るなら遅延セグメント木）, anchor: choosing}
  - {title: 値つきの区間の分割・統合, anchor: valued-intervals, level: 黄}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：互いに重ならない区間を左端をキーにした set・map で持ち、点を含む区間の検索・区間の追加と併合・区間への代入を、ならし O(log N) で行う。座標が 10^9 でも使える。
    - **いつ使うか**：
        - 区間を塗るたびに、塗られたマスの数や色ごとのマスの数を答える
        - 同じ色でつながった区間をまとめて塗り替える
        - 点 x が覆われているか・x を含む区間はどこか
        - 座標が 10^9 まで（配列の添字にできない）
    - **計算量**：（執筆時に書く）
    - **前提**：[set・multiset・map の応用](../ds/ordered-set.md)
