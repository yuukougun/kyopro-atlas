---
id: cpp-math-functions
title: 数・ビット・乱数の関数
aliases: [gcd, lcm, midpoint, clamp, 割り算の切り捨ての向き, pow, sqrt, sqrtl, 'numbers::pi', 'std::popcount', countr_zero, bit_width, __builtin_popcount, __builtin_ctz, __lg, 'std::bitset', _Find_first, mt19937_64, uniform_int_distribution, shuffle, chrono, 乱数, 時間計測]
type: cpp
field: cpp
chapter: 型と値
order: 50
level: 基礎
kind: [実装・C++, ビット演算]
prerequisites: [cpp-types-literals]
related: [cpp-integer-overflow, integer-division, gcd-lcm, integer-root, bit-operations, bitset-speedup, randomized, stress-testing]
summary: gcd・割り算・sqrt などの数の関数、popcount・bitset などのビットの関数、乱数と時間計測を正しく使う。整数の割り算が 0 に向かって切り捨てることや、sqrt の誤差に気をつける。
complexity: null
signs: []
acl: []
sections:
  - {title: 'gcd・lcm：型を混ぜられる、負の数は絶対値で計算、lcm は a / gcd(a, b) * b の順にしてあふれを避ける（C++17。__gcd は GCC の古い関数）', anchor: gcd-lcm}
  - {title: midpoint（C++20）・clamp（C++17）, anchor: midpoint-clamp}
  - {title: 整数の / と % は 0 に向かって切り捨てる（-7 / 2 は -3、-7 % 2 は -1。負の数の床関数・切り上げの書き方は integer-division のページ）, anchor: integer-division}
  - {title: pow・sqrt は double で計算する：整数のべき乗に pow を使わない、大きな long long の sqrt は誤差が出る（整数の平方根は標準になく、補正の仕方は integer-root のページ）, anchor: pow-sqrt}
  - {title: '円周率：numbers::pi（C++20）・M_PI・acos(-1)', anchor: pi}
  - {title: <bit> の関数：popcount・countr_zero・countl_zero・bit_width・bit_ceil・bit_floor・has_single_bit（C++20）, anchor: bit-functions}
  - {title: 'std::popcount などは符号なし整数しか受けない（popcount(int) はエラー、負の int を unsigned long long にすると上位が 1 で埋まる）（C++20）', anchor: bit-unsigned-only}
  - {title: '組み込み関数：__builtin_popcount・__builtin_popcountll・__builtin_ctz・__builtin_clzll・__lg（ctz・clz・__lg に 0 を渡すと未定義。std:: の関数は 0 でも値が決まっている）（GCC の拡張）', anchor: builtins}
  - {title: ビットの小技：x & -x（最下位の 1）・x & (x - 1)・部分集合を大きい順に回す for（考え方は bit 演算のページ）, anchor: bit-tricks}
  - {title: bitset：大きさはコンパイル時の定数、count・シフト・dp |= dp << w、_Find_first・_Find_next（後の 2 つは GCC の拡張）, anchor: bitset}
  - {title: '乱数：mt19937_64 rng(random_device{}())・uniform_int_distribution（両端を含む）・shuffle（rand() は使わない。種を固定すると再現できる）', anchor: random}
  - {title: '時間計測：chrono::steady_clock::now()', anchor: chrono}
stage: stub
updated: 2026-10-21
cpp_std: null
gcc_min: null
atcoder: true
---

!!! abstract "要点"
    - **何ができるか**：gcd・割り算・sqrt などの数の関数、popcount・bitset などのビットの関数、乱数と時間計測を正しく使う。整数の割り算が 0 に向かって切り捨てることや、sqrt の誤差に気をつける。
    - **いつ使うか**：（執筆時に書く）
    - **計算量**：（執筆時に書く）
    - **前提**：[数の型とリテラル](../cpp/cpp-types-literals.md)
