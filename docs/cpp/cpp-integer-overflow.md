---
id: cpp-integer-overflow
title: 整数のオーバーフローと __int128
nav_title: オーバーフローと __int128
aliases: [オーバーフロー, integer overflow, あふれ, int の掛け算, 1LL * a * b, 1 << 40, 符号なし整数, v.size() - 1, ssize, __int128, i128, 128bit 整数, __builtin_mul_overflow]
type: cpp
field: cpp
chapter: 型と値
order: 30
level: 基礎
kind: [実装・C++]
prerequisites: [cpp-types-literals]
related: [cpp-undefined-behavior, integer-division, integer-root, cpp-math-functions, cpp-algorithms, cpp-views-basics]
summary: int どうしの積・1 << k・size() の符号なしなど、型の幅を超えて値が壊れる書き方を見分けて直す。64 bit を超える中間値は GCC の拡張 __int128 で持てるが、入出力などに制限がある。
complexity: null
signs:
  - {type: constraint, text: A_i ≤ 10^9 を N ≤ 2×10^5 個足す、または 2 つ掛ける（int に収まらない）}
acl: []
sections:
  - {title: int どうしの積は int で計算される：long long p = a * b は誤り、1LL * a * b か (long long)a * b, anchor: int-product}
  - {title: シフトの幅：1 << 40 は警告が出て 0 になる、1LL << 40, anchor: shift-width}
  - {title: '初期値と推論の型：accumulate(..., 0)・auto x = 0・views::iota(0, n) の i は int', anchor: inferred-int}
  - {title: size() は符号なし：空の v で v.size() - 1 が巨大になる、-1 < v.size() が false、ssize(v)（C++20）か (int)v.size(), anchor: unsigned-size}
  - {title: '型の違う値を min・max に渡すとコンパイルエラー：min(1, x) → min(1LL, x)・min<long long>(1, x)', anchor: min-max-types}
  - {title: INF + INF・abs(INT_MIN)・INT_MIN / -1, anchor: edge-values}
  - {title: 符号付き整数のあふれは未定義動作：-O2 では正しく書いた別の行の値まで変わる（警告は出ず、-fsanitize=undefined で見つかる）, anchor: signed-overflow-ub}
  - {title: __int128：10^18 程度どうしの積を正確に持つ。リテラルはないので (__int128)1 << 100 と書く（GCC の拡張）, anchor: int128}
  - {title: __int128 の入出力：cout << も cin >> もできない、format（C++20・GCC 13〜）・println（C++23・GCC 14〜）か自作の変換で出し、文字列で読んで変換する, anchor: int128-io}
  - {title: -std=c++23 では is_integral_v<__int128> が false で gcd・abs に渡せない（AtCoder の -std=gnu++23 では渡せる。numeric_limits はどちらでも使える）, anchor: int128-strict-mode}
  - {title: 積が上限を超えるかの判定：割り算で比べる考え方は integer-division のページ、C++ では __builtin_mul_overflow（GCC の拡張）も使える、long double は境界で誤りうる, anchor: overflow-check}
stage: stub
updated: 2026-10-21
cpp_std: null
gcc_min: null
atcoder: true
---

!!! abstract "要点"
    - **何ができるか**：int どうしの積・1 << k・size() の符号なしなど、型の幅を超えて値が壊れる書き方を見分けて直す。64 bit を超える中間値は GCC の拡張 \_\_int128 で持てるが、入出力などに制限がある。
    - **いつ使うか**：A_i ≤ 10^9 を N ≤ 2×10^5 個足す、または 2 つ掛ける（int に収まらない）
    - **計算量**：（執筆時に書く）
    - **前提**：[数の型とリテラル](../cpp/cpp-types-literals.md)
