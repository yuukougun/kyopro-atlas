---
id: offline-queries
title: クエリの先読み
aliases: [オフライン処理, offline queries, クエリ先読み, クエリのソート, 区間の種類数, Range Set Query, オンライン強制]
type: technique
field: ds
chapter: クエリ処理の工夫
order: 260
level: 水
kind: [クエリ処理の工夫, データ構造]
prerequisites: [fenwick-tree, sorting-techniques]
related: [sweep-line-2d, mo-algorithm, union-find-connectivity, event-sort, reverse-thinking, persistent-data-structures, merge-sort-tree, coordinate-compression, parallel-binary-search]
summary: クエリを入力の順に答えなくてよいとき、答えやすい順（右端の順・しきい値の順・時間の逆順）に並べ替えて処理し、最後に元の順に戻す。前の答えで次の入力が決まる問題には使えない。
complexity: null
signs:
  - {type: phrase, text: '区間 [l, r] に含まれる値の種類数を多数のクエリで答える'}
  - {type: phrase, text: 重み w 以下の辺だけを使ったときの連結・X 以下の要素の和をクエリごとに答える}
  - {type: phrase, text: クエリどうしが独立で、順番を入れ替えても答えが変わらない}
  - {type: constraint, text: '値が 10^9 まで、N, Q ≤ 2×10^5 で、クエリにも新しい値が現れる'}
acl: [fenwick_tree]
verify: [static_range_count_distinct, static_range_frequency]
frequency: A
frequency_evidence: recent 4（abc453_g・abc463_g・abc467_g・abc477_f）・前提として 3 ページに届く（直接 3）・古い ABC 6 問
sections:
  - {title: 考え方（並べ替えて処理し、元の順に戻して出力する）, anchor: idea}
  - {title: 右端でソートして BIT（区間の種類数：各値の最後の出現位置にだけ 1 を立てる）, anchor: distinct-count}
  - {title: しきい値でソート（重み w 以下の辺だけで連結か・X 以下の要素の和）, anchor: threshold}
  - {title: 時間を逆にする（削除を追加に → グラフの章の Union-Find と連結性）, anchor: reverse-time}
  - {title: 答えを 2 時点の差に分ける, anchor: difference-of-times}
  - {title: 先に全部読んで座標圧縮する, anchor: compress}
  - {title: オンライン強制の見分け方と、そのときの構造（永続・マージソート木・動的セグメント木）, anchor: online}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：クエリを入力の順に答えなくてよいとき、答えやすい順（右端の順・しきい値の順・時間の逆順）に並べ替えて処理し、最後に元の順に戻す。前の答えで次の入力が決まる問題には使えない。
    - **いつ使うか**：
        - 区間 [l, r] に含まれる値の種類数を多数のクエリで答える
        - 重み w 以下の辺だけを使ったときの連結・X 以下の要素の和をクエリごとに答える
        - クエリどうしが独立で、順番を入れ替えても答えが変わらない
        - 値が 10^9 まで、N, Q ≤ 2×10^5 で、クエリにも新しい値が現れる
    - **計算量**：（執筆時に書く）
    - **前提**：[BIT（Fenwick Tree）](../ds/fenwick-tree.md)、[ソートで考える](../basics/sorting-techniques.md)
