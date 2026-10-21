---
id: interval
title: 区間
aliases: [連続部分列, 部分配列, subarray, 区間の集合, interval]
type: pattern
field: patterns
order: 10
level: null
kind: [案内, 区間クエリ, 累積和・差分]
prerequisites: []
related: [prefix-sum, prefix-sum-counting, two-pointers, contribution, monotonic-stack, dp-sequence-partition, interval-dp, imos, fenwick-tree, segment-tree, lazy-segment-tree, sparse-table, difference-sequence, offline-queries, mo-algorithm, interval-scheduling, interval-set, event-sort, sweep-line-2d, subsequence-and-substring]
summary: 連続部分列や与えられた区間の集合が出てくる問題で、問われ方から使う手法を引ける。連続部分列を数える・選ぶ、区間に操作して質問する、区間の集合を選ぶ・つなぐ、の3つの型に分ける。
complexity: null
signs:
  - {type: phrase, text: 和が K（K の倍数）になる連続部分列の個数}
  - {type: phrase, text: すべての連続部分列についての最小値・最大値・2 番目の値の総和}
  - {type: phrase, text: 'N 個の区間 [L_i, R_i] から重ならないように最大何個選べるか'}
  - {type: phrase, text: 区間を塗るたびに、塗られていない長さや個数を答える}
  - {type: phrase, text: 区間に含まれる異なる値の個数を多数答える}
acl: []
sections:
  - {title: 題材の性質, anchor: properties}
  - {title: 区間の和 → 累積和（prefix-sum）, anchor: sum}
  - {title: 和が K・K の倍数の区間の個数 → 累積和と連想配列（prefix-sum-counting）, anchor: count-by-sum}
  - {title: 伸び縮みで単調な条件 → 尺取り法（two-pointers）, anchor: monotone-window}
  - {title: '全区間の最小値・最大値の総和 → 寄与と単調スタック（contribution, monotonic-stack）', anchor: sum-over-subarrays}
  - {title: '全区間の中央値・mex・転倒数 → 題材別の各ページ（kth-and-median, mex, permutation）', anchor: other-statistics}
  - {title: 列を区間に区切る方法の数・最適値 → 区間分割 DP（dp-sequence-partition）, anchor: partition}
  - {title: 縮めながら取り除く・隣どうしを合体させる → 区間 DP（interval-dp）, anchor: shrink-and-merge}
  - {title: 加算をまとめて最後に見る → いもす法（imos）, anchor: batch-add}
  - {title: '更新と質問が交互 → BIT・セグメント木（fenwick-tree, segment-tree, lazy-segment-tree）', anchor: online-updates}
  - {title: 値が変わらない列の区間の最小値 → Sparse Table（sparse-table）, anchor: static-min}
  - {title: 区間に ±1 する操作の回数・可否 → 差分列への言い換え（difference-sequence）, anchor: difference}
  - {title: '区間の異なる値の個数・x 以下の個数 → クエリの先読みと BIT、Mo（offline-queries, mo-algorithm）', anchor: offline}
  - {title: 重ならない最大個数・すべてを串刺しにする点の数 → 区間スケジューリング（interval-scheduling）, anchor: scheduling}
  - {title: 区間の和集合・塗りつぶし・残りの長さ → 区間を set で管理（interval-set）, anchor: union}
  - {title: '含まれる・交差する区間の数 → イベントソート・平面走査（event-sort, sweep-line-2d）', anchor: containment}
  - {title: 数列ではなく文字列の連続部分 → 部分列と部分文字列（subsequence-and-substring）, anchor: substrings}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何のページか**：連続部分列や与えられた区間の集合が出てくる問題で、問われ方から使う手法を引ける。連続部分列を数える・選ぶ、区間に操作して質問する、区間の集合を選ぶ・つなぐ、の3つの型に分ける。
    - **いつ使うか**：
        - 和が K（K の倍数）になる連続部分列の個数
        - すべての連続部分列についての最小値・最大値・2 番目の値の総和
        - N 個の区間 [L_i, R_i] から重ならないように最大何個選べるか
        - 区間を塗るたびに、塗られていない長さや個数を答える
        - 区間に含まれる異なる値の個数を多数答える
    - **使い方**：（執筆時に書く）
