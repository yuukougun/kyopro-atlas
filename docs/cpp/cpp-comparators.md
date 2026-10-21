---
id: cpp-comparators
title: 比較関数と順序
aliases: [comparator, greater<>, 'greater{}', priority_queue の向き, 最小ヒープ, 厳密弱順序, strict weak ordering, operator<, 三方比較演算子, 宇宙船演算子, <=>, = default, 構造体のソート, 複数キーのソート]
type: cpp
field: cpp
chapter: コンテナ・アルゴリズム・ACL
order: 120
level: 基礎
kind: [実装・C++, ソート・座標圧縮]
prerequisites: [cpp-lambda]
related: [cpp-container-idioms, cpp-algorithms, cpp-structured-bindings, cpp-undefined-behavior, sorting-techniques, priority-queue, dijkstra]
summary: sort・set・priority_queue に渡す比較関数を約束（厳密弱順序）と向きを守って書き、構造体に operator< や <=> で順序を持たせる。比較関数に <= を書いて sort が落ちるような事故を防ぐ。
complexity: null
signs: []
acl: []
sections:
  - {title: 比較関数の約束：a が b より前なら true を返し、厳密弱順序を満たす（a と a を比べたら false）, anchor: strict-weak-ordering}
  - {title: 比較関数に <= を書くと sort が壊れる（同じ値が多いと Segmentation fault。_GLIBCXX_DEBUG で見つかる）, anchor: less-equal-pitfall}
  - {title: '降順：greater<T>・greater<>（型の違う値も比べられる）・greater{}（CTAD で greater<void>）', anchor: greater}
  - {title: priority_queue の向き：既定は最大が先頭、greater で最小が先頭（比較関数は「優先度が低い」を表すので sort と向きが逆に見える）, anchor: priority-queue-order}
  - {title: set・map の比較関数は「同じ」も決める（second だけで比べると、second の等しい要素が 1 個しか残らない）, anchor: set-equivalence}
  - {title: '複数のキーで比べる：pair・tuple の辞書順、tie(a.x, a.y) < tie(b.x, b.y)', anchor: multiple-keys}
  - {title: 'ラムダの比較関数を型として渡す：set<T, decltype(cmp)>（C++20。C++17 では pq(cmp) と渡す）', anchor: lambda-comparator-type}
  - {title: 構造体に operator< を持たせる（メンバ関数に const が要る）, anchor: operator-less}
  - {title: auto operator<=>(const T&) const = default で 6 つの比較をメンバの宣言順の辞書順で作る（C++20）, anchor: spaceship}
stage: stub
updated: 2026-10-21
cpp_std: null
gcc_min: null
atcoder: true
---

!!! abstract "要点"
    - **何ができるか**：sort・set・priority_queue に渡す比較関数を約束（厳密弱順序）と向きを守って書き、構造体に operator< や <=> で順序を持たせる。比較関数に <= を書いて sort が落ちるような事故を防ぐ。
    - **いつ使うか**：（執筆時に書く）
    - **計算量**：（執筆時に書く）
    - **前提**：[ラムダ式と再帰ラムダ](../cpp/cpp-lambda.md)
