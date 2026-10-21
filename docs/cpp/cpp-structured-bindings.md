---
id: cpp-structured-bindings
title: 構造化束縛と pair・tuple・optional
nav_title: 構造化束縛と pair・tuple
aliases: [構造化束縛, structured binding, 'auto [a, b]', 分解宣言, pair, tuple, tie, get<0>, make_pair, optional, nullopt, value_or, exchange, 初期化式付き if]
type: cpp
field: cpp
chapter: 参照・ラムダ・テンプレート
order: 70
level: 基礎
kind: [実装・C++]
prerequisites: [cpp-range-for]
related: [cpp-views-cpp23, cpp-comparators, cpp-undefined-behavior, cpp-lambda, dijkstra]
summary: pair・tuple・構造体の中身に名前を付けて取り出し（構造化束縛）、tie・optional で組や「値がない」を表す。pq.top() を参照で受けてから pop するような、受け方の誤りを防ぐ。
complexity: null
signs: []
acl: []
sections:
  - {title: 'pair と tuple：get<i>・make_pair・pair{a, b}、辞書順で比べられる', anchor: pair-tuple}
  - {title: '構造化束縛の形：auto [a, b] = p、構造体・配列・array、for (auto& [k, v] : mp)（C++17）', anchor: structured-binding}
  - {title: 見えない変数：auto はコピー、auto& は参照。名前はメンバの宣言順に付き、数が合わないとエラー（C++17）, anchor: hidden-variable}
  - {title: 'map を回すとき：キーは const、auto& [k, v] で値を書き換えると map が変わる（C++17）', anchor: map-loop}
  - {title: '初期化式付き if・switch：if (auto it = mp.find(k); it != mp.end())、if (auto [it, ok] = st.insert(x); ok)（C++17）', anchor: if-init}
  - {title: 'const auto& [d, v] = pq.top(); pq.pop(); で値が変わる（ダイクストラで起きる。値で受ける。理由は cpp-undefined-behavior のダングリング）', anchor: pq-top-reference}
  - {title: 'views::enumerate・zip の要素は参照を含む組：auto [i, x] と書いても x は元の要素を指す', anchor: enumerate-reference}
  - {title: 構造化束縛した名前のラムダでのキャプチャ（C++20）と、使わない名前 _（同じ場所で 2 回使うのは C++26。AtCoder の GCC 15 では警告つきで通る）, anchor: capture-and-placeholder}
  - {title: 'tie：既存の変数にまとめて代入・比較する（tie(x1, y1) < tie(x2, y2)・std::ignore）', anchor: tie}
  - {title: 'tie(a, b) = tie(b, a) は入れ替えにならない（両方 b になる。swap か tie(a, b) = pair{b, a}）', anchor: tie-swap-pitfall}
  - {title: '代入の小技：prev = exchange(cur, nxt) で代入して前の値を返す、tie(f0, f1) = pair{f1, f0 + f1}', anchor: exchange}
  - {title: optional：値がないことを表す（nullopt・has_value・value_or・if (auto r = f())。空の *o は未定義動作）（C++17）, anchor: optional}
  - {title: apply と、同じ型の組としての array（apply は C++17）, anchor: apply}
stage: stub
updated: 2026-10-21
cpp_std: 17
gcc_min: null
atcoder: true
---

!!! abstract "要点"
    - **何ができるか**：pair・tuple・構造体の中身に名前を付けて取り出し（構造化束縛）、tie・optional で組や「値がない」を表す。pq.top() を参照で受けてから pop するような、受け方の誤りを防ぐ。
    - **いつ使うか**：（執筆時に書く）
    - **計算量**：（執筆時に書く）
    - **前提**：[参照と範囲 for](../cpp/cpp-range-for.md)
