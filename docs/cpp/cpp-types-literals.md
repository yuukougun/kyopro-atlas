---
id: cpp-types-literals
title: 数の型とリテラル
aliases: [整数の型, long long, LL, ULL, 桁区切り, 2 進リテラル, 0uz, auto の推論, using ll = long long, static_cast, INF, numeric_limits, LLONG_MAX, INT_MAX, '0x3f3f3f3f', 1LL << 60, double, long double, 1e18, 浮動小数点数の型]
type: cpp
field: cpp
chapter: 型と値
order: 20
level: 基礎
kind: [実装・C++]
prerequisites: []
related: [cpp-integer-overflow, cpp-initialization, cpp-math-functions, cpp-io, geometry-precision, dijkstra]
summary: 整数・浮動小数点数の型とリテラル、INF の値を、値が収まり意図どおりの型になるように選ぶ。auto x = 0 が int、1e18 が double になるような、型のずれによる誤りを防ぐ。
complexity: null
signs: []
acl: []
sections:
  - {title: 整数の型と表せる範囲（int・long long・unsigned・size_t・int64_t）, anchor: integer-types}
  - {title: リテラルの書き方：1LL・ULL、桁区切り 1'000'000'007、2 進 0b1010、size_t の 0uz（C++23）, anchor: literals}
  - {title: auto が推論する型：0 は int、0LL は long long、v.size() は size_t（符号なし）、1e18 は double, anchor: auto-deduction}
  - {title: '型の別名：using ll = long long と #define ll long long（ll(x) と書けるか）', anchor: type-alias}
  - {title: キャスト：static_cast<long long>(x)・(long long)x, anchor: cast}
  - {title: 'INF の決め方：numeric_limits<T>::max()・1LL << 60・0x3f3f3f3f と、INF + INF があふれるか（ライブラリの雛形の値の比較も）', anchor: inf}
  - {title: 浮動小数点数の型：double が整数を正確に表せるのは 2^53 まで、x86-64 の long double は仮数部 64bit, anchor: floating-point}
  - {title: 1e18 は double：(long long)1e18 + 1 は正確だが (long long)(1e18 + 1) は丸められる、auto INF = 1e18 も double, anchor: double-1e18}
  - {title: 浮動小数点数を == で比べない（誤差を許すか、整数で計算する。小数の入力を整数に直す方法と幾何の誤差は geometry-precision のページ）, anchor: float-compare}
  - {title: float128_t（<stdfloat>。C++23・GCC 13〜。解説コードではまれ）, anchor: float128}
stage: stub
updated: 2026-10-21
cpp_std: null
gcc_min: null
atcoder: true
---

!!! abstract "要点"
    - **何ができるか**：整数・浮動小数点数の型とリテラル、INF の値を、値が収まり意図どおりの型になるように選ぶ。auto x = 0 が int、1e18 が double になるような、型のずれによる誤りを防ぐ。
    - **いつ使うか**：（執筆時に書く）
    - **計算量**：（執筆時に書く）
    - **前提**：なし
