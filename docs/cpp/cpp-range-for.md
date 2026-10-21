---
id: cpp-range-for
title: 参照と範囲 for
aliases: [参照, 参照渡し, const 参照, 値渡し, コピー, ムーブ, 'std::move', 'std::swap', 範囲 for, range-based for, auto&&, const auto&, 'for (auto& x : v)', vector<bool>]
type: cpp
field: cpp
chapter: 参照・ラムダ・テンプレート
order: 60
level: 基礎
kind: [実装・C++]
prerequisites: []
related: [cpp-structured-bindings, cpp-lambda, cpp-undefined-behavior, cpp-io, knapsack-01]
summary: 値をコピーで受けるか参照で受けるかを選び、範囲 for と関数の引数で無駄なコピーと書き換え漏れを防ぐ。値渡しの再帰が遅い理由と、swap が O(1) の理由も分かる。
complexity: null
signs: []
acl: []
sections:
  - {title: 参照 T& と const 参照 const T&：別名を付けてコピーしない, anchor: references}
  - {title: 関数の引数：値渡しは呼ぶたびにコピー（再帰では O(N) × 呼び出し回数）、大きなものは const& で渡す, anchor: pass-by-reference}
  - {title: 'ムーブと swap：swap(dp, ndp) は中身を入れ替えるだけで O(1)、dp = ndp は O(N) のコピー', anchor: move-swap}
  - {title: auto&&：何でも受けられる参照, anchor: forwarding-reference}
  - {title: 範囲 for の 4 通りの受け方：コピーが起きるか・元を書き換えられるか, anchor: range-for-forms}
  - {title: 'vector<bool> の要素は代わりの小さな物（プロキシ）：auto& で回すとエラー、auto y = vb[0] でも元が書き換わる', anchor: vector-bool}
  - {title: '範囲 for の初期化式 for (int i = 0; auto x : v)（C++20。i の更新は自分で書く）', anchor: range-for-init}
  - {title: ループの中で同じ vector に追加しない（再確保で壊れる）, anchor: modify-in-loop}
  - {title: '範囲に一時オブジェクトの中身を渡すとき：for (int v : d.groups()[0]) は C++23・GCC 15〜でだけ安全、関数の戻り値そのものを回すのはどの版でも安全', anchor: temporary-range}
stage: stub
updated: 2026-10-21
cpp_std: null
gcc_min: null
atcoder: true
---

!!! abstract "要点"
    - **何ができるか**：値をコピーで受けるか参照で受けるかを選び、範囲 for と関数の引数で無駄なコピーと書き換え漏れを防ぐ。値渡しの再帰が遅い理由と、swap が O(1) の理由も分かる。
    - **いつ使うか**：（執筆時に書く）
    - **計算量**：（執筆時に書く）
    - **前提**：なし
