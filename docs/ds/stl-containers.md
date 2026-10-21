---
id: stl-containers
title: STL コンテナの使い分け
aliases: [STL, STL containers, 標準ライブラリのコンテナ, コンテナの計算量]
type: technique
field: ds
chapter: 標準コンテナの応用
order: 10
level: 基礎
kind: [データ構造, 実装・C++]
prerequisites: []
related: [ordered-set, priority-queue, stack-techniques, prefix-sum-counting, cpp-container-idioms]
summary: どの操作を速くしたいかで vector・deque・set・map・priority_queue・unordered_map を選ぶ。multiset の erase(x) は同じ値を全部消し、map の [] は要素を作る。
complexity: null
signs:
  - {type: phrase, text: 要素の追加・削除と、検索・最小値の取り出しのクエリが混ざる}
  - {type: shape, text: 'j − i = A_i + A_j のように、i だけの式と j だけの式が等しい組 (i, j) を数える'}
  - {type: constraint, text: 'N, Q ≤ 2×10^5 で、追加・削除・検索のクエリが来る'}
acl: []
verify: [associative_array]
frequency: A
frequency_evidence: recent 0・前提として 72 ページに届く（直接 5）・古い ABC 2 問
sections:
  - {title: 操作とコンテナの計算量の早見表, anchor: complexity-table}
  - {title: 選び方（何を速くしたいか）, anchor: choosing}
  - {title: map で数えながら走査する（→ 累積和と連想配列で区間を数える）, anchor: counting-map}
  - {title: '落とし穴（multiset の erase(x) は全部消す・set に std::lower_bound は O(N)・map の [] は要素を作る・空の size() − 1・イテレータの無効化・unordered_map のハック）', anchor: pitfalls}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：どの操作を速くしたいかで vector・deque・set・map・priority_queue・unordered_map を選ぶ。multiset の erase(x) は同じ値を全部消し、map の [] は要素を作る。
    - **いつ使うか**：
        - 要素の追加・削除と、検索・最小値の取り出しのクエリが混ざる
        - j − i = A_i + A_j のように、i だけの式と j だけの式が等しい組 (i, j) を数える
        - N, Q ≤ 2×10^5 で、追加・削除・検索のクエリが来る
    - **計算量**：（執筆時に書く）
    - **前提**：なし
