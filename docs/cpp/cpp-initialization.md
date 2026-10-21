---
id: cpp-initialization
title: 初期化と CTAD
aliases: [初期化, 多次元 vector, 多次元配列, vector の初期化, 'array<int, 26> cnt{}', 値初期化, memset, fill, assign, 指示付き初期化, 集成体, explicit, クラステンプレートの実引数推論, class template argument deduction, 'vector dp(n, vector(m, 0LL))']
type: cpp
field: cpp
chapter: 型と値
order: 40
level: 基礎
kind: [実装・C++]
prerequisites: [cpp-types-literals]
related: [cpp-structured-bindings, cpp-comparators, cpp-undefined-behavior, acl-reading, dp-basics, grid-graph]
summary: vector・多次元 vector・array・構造体を、意図した大きさと初期値で作る。型引数を省いて中身から型を決める CTAD（C++17）と、括弧の種類で意味が変わる罠も分かる。
complexity: null
signs: []
acl: []
sections:
  - {title: 'vector の初期化：(n) は 0 が n 個、(n, x) は x が n 個、{n} は値 n が 1 個', anchor: vector-init}
  - {title: '多次元 vector：dp(n + 1, vector<long long>(m + 1, -1))、3 次元は入れ子を 1 段深くする', anchor: multi-dim-vector}
  - {title: 'array と {} による 0 初期化（array<int, 26> cnt{}・vector<array<int, 3>> v(n)）', anchor: array-init}
  - {title: グローバル変数は 0 で初期化され、関数の中の変数・配列は初期化されない, anchor: global-vs-local}
  - {title: '構造体のメンバの既定値と指示付き初期化 Edge{.to = v, .cost = c}（C++20。メンバの宣言順に書く）', anchor: designated-init}
  - {title: 'コンストラクタのない構造体（集成体）にも emplace_back(to, cost) が使える（C++20。C++17 ではエラー）', anchor: aggregate-emplace}
  - {title: explicit なコンストラクタは = で初期化できない（ACL の dsu d = 5 はエラーで、dsu d(5) と書く）, anchor: explicit}
  - {title: '埋め直し：memset はバイト単位（0・-1・0x3f だけ）、fill・assign・ranges::fill、2 次元の C 配列の fill', anchor: refill}
  - {title: 'CTAD：vector dp(n, vector(m, 0LL)) で型を内側から決める（0 と書くと int になる）（C++17）', anchor: ctad}
  - {title: 'pair・tuple・array・priority_queue の CTAD：pair p{1, 2.5}・priority_queue pq(greater<int>{}, vector<int>{})（C++17）', anchor: ctad-std-types}
  - {title: 'CTAD の罠：vector w{v.begin(), v.end()} はイテレータ 2 個の vector になる（丸括弧なら要素の vector。警告も出ない）（C++17）', anchor: ctad-pitfall}
stage: stub
updated: 2026-10-21
cpp_std: null
gcc_min: null
atcoder: true
---

!!! abstract "要点"
    - **何ができるか**：vector・多次元 vector・array・構造体を、意図した大きさと初期値で作る。型引数を省いて中身から型を決める CTAD（C++17）と、括弧の種類で意味が変わる罠も分かる。
    - **いつ使うか**：（執筆時に書く）
    - **計算量**：（執筆時に書く）
    - **前提**：[数の型とリテラル](../cpp/cpp-types-literals.md)
