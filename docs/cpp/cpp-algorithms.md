---
id: cpp-algorithms
title: アルゴリズム関数と ranges 版
aliases: [algorithm, sort, unique, 'std::lower_bound', 'std::upper_bound', accumulate, reduce, partial_sum, 'std::iota', 'std::next_permutation', max_element, 'max({a, b, c})', 'ranges::sort', 射影, projection, 'ranges::unique', 'ranges::fold_left', 'ranges::contains']
type: cpp
field: cpp
chapter: コンテナ・アルゴリズム・ACL
order: 130
level: 基礎
kind: [実装・C++, ソート・座標圧縮]
prerequisites: [cpp-container-idioms, cpp-lambda]
related: [cpp-views-basics, cpp-comparators, cpp-integer-overflow, coordinate-compression, binary-search, bit-full-search, prefix-sum]
summary: sort・unique・lower_bound・accumulate などの定型と、射影も使える ranges 版（C++20）を使い分ける。accumulate の初期値の型や、unique だけでは要素が減らない点に気をつける。
complexity: null
signs: []
acl: []
sections:
  - {title: sort と降順（greater・rbegin/rend）, anchor: sort}
  - {title: '重複の削除：sort してから v.erase(unique(v.begin(), v.end()), v.end())（unique は前に詰めて新しい終端を返すだけ）', anchor: unique-erase}
  - {title: 二分探索：lower_bound・upper_bound の位置と添字（- v.begin()）・個数、equal_range・binary_search（set・map にはメンバの lower_bound）, anchor: lower-bound}
  - {title: 総和：accumulate は初期値の型で計算する（0 ではなく 0LL・0.0）、reduce は初期値を省くと要素の型で足す, anchor: accumulate}
  - {title: 累積和と差分：partial_sum・inclusive_scan・adjacent_difference, anchor: partial-sum}
  - {title: '連番：std::iota で埋める（views::iota・ranges::iota との違い）', anchor: iota}
  - {title: next_permutation で順列を列挙する（ソートした状態から始める）, anchor: next-permutation}
  - {title: '最大・最小・個数：max_element はイテレータを返す、max({a, b, c})、clamp（C++17）、count の戻り値は ptrdiff_t', anchor: max-element}
  - {title: 'ranges 版：ranges::sort(v) のようにコンテナを直接渡す（C++20）', anchor: ranges}
  - {title: '射影：ranges::sort(ps, {}, &P::score)・ranges::max(ps, {}, &P::score)（{} は既定の比較）（C++20）', anchor: projection}
  - {title: 'ranges::unique は後ろの不要部分を返す：v.erase(ranges::unique(v).begin(), v.end())（C++20）', anchor: ranges-unique}
  - {title: 'ranges::fold_left・contains・find_last（C++23・GCC 13〜）。ranges::starts_with（C++23・GCC 16〜）は AtCoder では使えない', anchor: fold-left}
  - {title: '一時オブジェクトを渡すと戻り値が ranges::dangling になり、使うとコンパイルエラーになる（C++20）', anchor: ranges-dangling}
stage: stub
updated: 2026-10-21
cpp_std: null
gcc_min: null
atcoder: true
---

!!! abstract "要点"
    - **何ができるか**：sort・unique・lower_bound・accumulate などの定型と、射影も使える ranges 版（C++20）を使い分ける。accumulate の初期値の型や、unique だけでは要素が減らない点に気をつける。
    - **いつ使うか**：（執筆時に書く）
    - **計算量**：（執筆時に書く）
    - **前提**：[コンテナ操作とイテレータ](../cpp/cpp-container-idioms.md)、[ラムダ式と再帰ラムダ](../cpp/cpp-lambda.md)
