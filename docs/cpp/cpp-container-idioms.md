---
id: cpp-container-idioms
title: コンテナ操作とイテレータ
aliases: [erase_if, contains, emplace_back, 'map の []', multiset の削除, ms.erase(ms.find(x)), イテレータ, iterator, 'std::prev', 'std::next', rbegin, it - v.begin(), イテレータの無効化, unordered_map のハッシュ, pb_ds, order_of_key, find_by_order]
type: cpp
field: cpp
chapter: コンテナ・アルゴリズム・ACL
order: 110
level: 基礎
kind: [実装・C++, データ構造]
prerequisites: []
related: [stl-containers, ordered-set, cpp-comparators, cpp-algorithms, cpp-undefined-behavior, hash-safety, kth-element]
summary: set・map・multiset の定型の操作（erase_if・contains・1 個だけ消す）とイテレータを正しく書く。map の [] が要素を作る、set に std::lower_bound を使うと遅い、などの事故を防ぐ。
complexity: null
signs: []
acl: []
sections:
  - {title: 'erase(v, x)・erase_if(v, pred)：消した個数を返し、set・map にも使える（C++20）', anchor: erase-if}
  - {title: contains（C++20）と find・count, anchor: contains}
  - {title: 'map の [] はキーがなければ既定値で要素を作る（存在を調べるだけなら contains・find、at はなければ例外）', anchor: map-subscript}
  - {title: multiset から 1 個だけ消す：ms.erase(ms.find(x))（ms.erase(x) は全部消す。find が end() でないことを確かめる）, anchor: multiset-erase-one}
  - {title: emplace_back と push_back, anchor: emplace-back}
  - {title: 'set・map の lower_bound はメンバを使う（std::lower_bound・ranges::lower_bound は O(N)）', anchor: member-lower-bound}
  - {title: イテレータの基本：begin は先頭、end は最後の要素の次（*prev(st.end())・*st.rbegin()・next・prev）, anchor: iterators}
  - {title: it - v.begin() で添字（vector だけ）、distance は set では O(N), anchor: iterator-index}
  - {title: erase は次のイテレータを返す（it = st.erase(it)）, anchor: erase-returns-next}
  - {title: イテレータと参照の無効化：vector の再確保はすべてを無効にし、set・map は消した要素だけ, anchor: invalidation}
  - {title: unordered_map：pair のキーにはハッシュがない（コンパイルエラー）、自作のハッシュの渡し方、衝突を狙った入力（安全な設計は hash-safety）, anchor: unordered-map}
  - {title: 'pb_ds の順序付き集合：tree と order_of_key・find_by_order、重複は (値, 通し番号) にする（GCC の拡張）', anchor: pb-ds}
stage: stub
updated: 2026-10-21
cpp_std: null
gcc_min: null
atcoder: true
---

!!! abstract "要点"
    - **何ができるか**：set・map・multiset の定型の操作（erase_if・contains・1 個だけ消す）とイテレータを正しく書く。map の [] が要素を作る、set に std::lower_bound を使うと遅い、などの事故を防ぐ。
    - **いつ使うか**：（執筆時に書く）
    - **計算量**：（執筆時に書く）
    - **前提**：なし
