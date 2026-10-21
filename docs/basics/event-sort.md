---
id: event-sort
title: イベントソートと平面走査の基本
aliases: [イベントソート, 開始と終了をイベントにする, event sorting]
type: technique
field: basics
chapter: ソートと二分探索
order: 110
level: 水
kind: [ソート・座標圧縮, クエリ処理の工夫]
prerequisites: [sorting-techniques]
related: [imos, coordinate-compression, ordered-set, sweep-line-2d, offline-queries]
summary: 区間の開始・終了・クエリを (座標, 種類) の組にして並べ、左から順に処理しながら集合や合計を更新する。2 次元の点を一方の座標の順に処理し、もう一方を集合で管理するのが平面走査の基本形。
complexity: null
signs:
  - {type: phrase, text: 区間の開始・終了と、時刻のクエリが混ざる}
  - {type: phrase, text: x 座標も y 座標も大きい相手と組にする・数える}
  - {type: phrase, text: 締め切りや有効期間がある}
  - {type: phrase, text: クエリを先に全部読んでよい}
  - {type: constraint, text: 座標は 10^9 まで、区間とクエリは合わせて 2×10^5 個程度}
acl: []
frequency: A
frequency_evidence: recent 2（abc467_e・abc478_d）・前提として 1 ページに届く（直接 1）・古い ABC 5 問
sections:
  - {title: イベントの作り方と同じ座標での処理順, anchor: make-events}
  - {title: 集合（set・multiset）を更新しながら走査する, anchor: with-set}
  - {title: 平面走査の基本（一方の座標で並べ、もう一方を集合で）, anchor: plane-sweep}
  - {title: BIT・セグ木と組む平面走査へ（データ構造の章）, anchor: to-data-structures}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：区間の開始・終了・クエリを (座標, 種類) の組にして並べ、左から順に処理しながら集合や合計を更新する。2 次元の点を一方の座標の順に処理し、もう一方を集合で管理するのが平面走査の基本形。
    - **いつ使うか**：
        - 区間の開始・終了と、時刻のクエリが混ざる
        - x 座標も y 座標も大きい相手と組にする・数える
        - 締め切りや有効期間がある
        - クエリを先に全部読んでよい
        - 座標は 10^9 まで、区間とクエリは合わせて 2×10^5 個程度
    - **計算量**：（執筆時に書く）
    - **前提**：[ソートで考える](../basics/sorting-techniques.md)
