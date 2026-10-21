---
id: sqrt-decomposition
title: 平方分割
aliases: [sqrt decomposition, バケット法, bucket method, 根号で場合分け, heavy/light, クエリの平方分割]
type: technique
field: ds
chapter: クエリ処理の工夫
order: 290
level: 黄
kind: [クエリ処理の工夫, データ構造, 計算量]
prerequisites: [segment-tree]
related: [mo-algorithm, degree-sqrt, complexity-estimation, lazy-segment-tree]
summary: セグメント木に載らない区間操作や、合計だけが抑えられた量の処理を、√N を境に分けて O(N√N) 程度で行う。ブロックごとに集約とタグを持つ方法と、大きいものと小さいもので処理を変える方法がある。
complexity: null
signs:
  - {type: phrase, text: 次数の合計が 2M・各色の個数の合計が N のように、合計だけが抑えられている}
  - {type: phrase, text: 位置 i から A_i ずつ先へ跳ぶ・配る}
  - {type: phrase, text: 区間加算と、区間内の x 以上の要素の個数}
  - {type: constraint, text: 制限時間が長めで、O(N√N) ≈ 10^8 なら間に合う}
acl: []
verify: [static_range_mode_query]
frequency: B
frequency_evidence: recent 0・前提として届くページなし・古い ABC 5 問
sections:
  - {title: 配列のバケット分割（完全に含まれるブロックはタグ、端は要素ごと）, anchor: buckets}
  - {title: '根号で場合分け（合計が抑えられた量の大小で分ける。歩幅なら小さい歩幅を（歩幅, 余り）でまとめる。入口は次数による平方分割のページ）', anchor: heavy-light}
  - {title: クエリの平方分割（√Q 個ごとに作り直し、未反映の分は愚直に補正する）, anchor: query-buckets}
  - {title: 実装の要点（ブロック番号は i / B・l と r が同じブロックの場合・タグを押し下げる時機・B は定数でよい）, anchor: implementation}
  - {title: 使い分け（載せられるならセグメント木のほうが速く安全）, anchor: choosing}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：セグメント木に載らない区間操作や、合計だけが抑えられた量の処理を、√N を境に分けて O(N√N) 程度で行う。ブロックごとに集約とタグを持つ方法と、大きいものと小さいもので処理を変える方法がある。
    - **いつ使うか**：
        - 次数の合計が 2M・各色の個数の合計が N のように、合計だけが抑えられている
        - 位置 i から A_i ずつ先へ跳ぶ・配る
        - 区間加算と、区間内の x 以上の要素の個数
        - 制限時間が長めで、O(N√N) ≈ 10^8 なら間に合う
    - **計算量**：（執筆時に書く）
    - **前提**：[セグメント木](../ds/segment-tree.md)
