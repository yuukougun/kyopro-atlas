---
id: cpp-reverse-index
title: C++ の逆引き
aliases: [解説コードの読み方, 解説コードが読めない, モダン C++ の読み方, 書き方から引く, 症状から引く, Segmentation fault, コンパイルエラーの読み方, エラーメッセージ, required from here]
type: guide
field: cpp
order: 10
level: null
kind: [実装・C++, 案内]
prerequisites: []
related: [cpp-environment, cpp-undefined-behavior, debugging-checklist, reverse-index-signs, glossary]
summary: 解説コードの書き方・実行時の症状・コンパイルエラーのメッセージから、意味と C++ 章の該当する節を引く。1 行を「何を回すか・何を受け取るか・どう受け取るか」に分けて読む手順も示す。
complexity: null
signs: []
acl: []
sections:
  - {title: '1 行の読み方：何を回すか（範囲）・何を受け取るか（要素の型）・どう受け取るか（コピーか参照か）に分ける。例 for (const auto& [i, component] : scc.scc() | views::enumerate)', anchor: how-to-read}
  - {title: '書き方から引く：型・リテラル・初期化・数の関数（1LL << 60・1''000''000''007・0uz・vector dp(n, vector(m, 0LL))・array<int, 26> cnt{}・gcd・popcount・__lg・x & -x）', anchor: lookup-types}
  - {title: '書き方から引く：参照・構造化束縛・組（for (auto&& x : v)・auto [a, b] = p・if (auto it = mp.find(k); it != mp.end())・tie・exchange）', anchor: lookup-references}
  - {title: '書き方から引く：ラムダ・再帰・テンプレート（[&](int v) { ... }・[&] { ... }()・this auto&& self・template <class T>・auto f(auto x)・constexpr）', anchor: lookup-lambda}
  - {title: '書き方から引く：雛形とマクロ（rep・all・#define int long long・chmin と (a = b, true)・#ifdef LOCAL・#pragma GCC・import std;）', anchor: lookup-macros}
  - {title: '書き方から引く：コンテナ・比較関数・アルゴリズム・文字列（erase_if・contains・ms.erase(ms.find(x))・*prev(st.end())・greater<>・<=>・lower_bound(...) - v.begin()・ranges::sort(v, {}, &T::x)・c - ''a''）', anchor: lookup-containers}
  - {title: '書き方から引く：views（views::iota・| views::enumerate・| views::chunk_by(equal_to{})・| ranges::to<vector>()）', anchor: lookup-views}
  - {title: '書き方から引く：入出力（cin.tie(nullptr)・" \n"[i == n - 1]・println・setprecision）', anchor: lookup-io}
  - {title: '書き方から引く：ACL（using mint = modint998244353;・x.val()・segtree<S, op, e>・dsu d(n)）', anchor: lookup-acl}
  - {title: '混同しやすい書き方の対（std::iota と views::iota、unique と erase、accumulate と reduce、size と ssize、endl と改行文字、-std=c++23 と -std=gnu++23 など）', anchor: confusing-pairs}
  - {title: 症状から引く：WA・RE・TLE と、手元と AtCoder で結果が違うとき（C++ に由来するもの。全体は debugging-checklist）, anchor: symptoms}
  - {title: 'コンパイルエラーのメッセージから引く（最初の error: の行と、required from here で自分の行を探す読み方を含む）', anchor: compile-errors}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何のページか**：解説コードの書き方・実行時の症状・コンパイルエラーのメッセージから、意味と C++ 章の該当する節を引く。1 行を「何を回すか・何を受け取るか・どう受け取るか」に分けて読む手順も示す。
    - **使い方**：（執筆時に書く）
