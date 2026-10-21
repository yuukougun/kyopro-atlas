---
id: cpp-templates-constexpr
title: 関数テンプレートと constexpr
aliases: [テンプレート, template, 関数テンプレート, template <class T>, 型推論, auto 引数, コンセプト, concepts, requires, static_assert, if constexpr, 畳み込み式, fold expression, 属性, '[[maybe_unused]]']
type: cpp
field: cpp
chapter: 参照・ラムダ・テンプレート
order: 90
level: 基礎
kind: [実装・C++]
prerequisites: []
related: [cpp-macros-template-file, cpp-lambda, acl-reading, library-design, cpp-reverse-index#compile-errors]
summary: 型を引数にした関数（テンプレート・auto 引数・コンセプト）と、コンパイル時に値を決める constexpr・static_assert を読み書きする。chmin(a, 3) が通らないような型推論の失敗を避ける。
complexity: null
signs: []
acl: []
sections:
  - {title: 「テンプレート」の 2 つの意味：C++ の template と、競プロのコードの雛形, anchor: two-meanings}
  - {title: '関数テンプレート：template <class T> T power(T a, long long n)', anchor: function-template}
  - {title: '型推論の失敗：chmin(a, 3)（a が long long）が通らない理由と、2 つの型引数を取る形', anchor: deduction-failure}
  - {title: '型を明示して呼ぶ：max<long long>(a, b)', anchor: explicit-type}
  - {title: auto 引数の省略形 auto sq(auto x)（C++20）, anchor: abbreviated-template}
  - {title: コンセプトと requires：template <integral T>（C++20）, anchor: concepts}
  - {title: 'constexpr の定数と関数、コンパイル時に表を作る constexpr auto table = [] { ... }();', anchor: constexpr}
  - {title: static_assert と if constexpr（if constexpr は C++17）, anchor: static-assert}
  - {title: '畳み込み式で可変長引数を展開する：((cerr << xs << '' ''), ...) のデバッグ出力（C++17）', anchor: fold-expression}
  - {title: '属性：[[maybe_unused]]・[[nodiscard]]（C++17）、[[likely]]（C++20）、[[assume]]（C++23・GCC 13〜）', anchor: attributes}
stage: stub
updated: 2026-10-21
cpp_std: null
gcc_min: null
atcoder: true
---

!!! abstract "要点"
    - **何ができるか**：型を引数にした関数（テンプレート・auto 引数・コンセプト）と、コンパイル時に値を決める constexpr・static_assert を読み書きする。chmin(a, 3) が通らないような型推論の失敗を避ける。
    - **いつ使うか**：（執筆時に書く）
    - **計算量**：（執筆時に書く）
    - **前提**：なし
