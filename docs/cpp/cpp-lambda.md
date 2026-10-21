---
id: cpp-lambda
title: ラムダ式と再帰ラムダ
aliases: [ラムダ, lambda, 無名関数, クロージャ, キャプチャ, '[&]', '[=]', ジェネリックラムダ, 再帰ラムダ, 'std::function', auto&& self, this auto&& self, deducing this, 不動点コンビネータ, FixPoint]
type: cpp
field: cpp
chapter: 参照・ラムダ・テンプレート
order: 80
level: 基礎
kind: [実装・C++]
prerequisites: [cpp-range-for]
related: [cpp-comparators, cpp-algorithms, acl-reading, cpp-environment#stack-depth, cpp-templates-constexpr, dfs, memoized-recursion]
summary: その場で関数を作るラムダ式で、比較関数・判定関数・DFS を書く。ラムダで再帰する 4 つの書き方（std::function・auto&& self・deducing this・不動点コンビネータ）の違いと速さも比べる。
complexity: null
signs: []
acl: []
sections:
  - {title: 'キャプチャ：[&] は参照、[=] は作った時点のコピー、初期化キャプチャ [x = std::move(v)]、mutable。参照キャプチャしたラムダを変数の寿命より長く使わない', anchor: capture}
  - {title: 'auto 引数のジェネリックラムダ、テンプレート構文 []<class T>(...)（C++20）、static ラムダ（C++23・GCC 13〜）', anchor: generic-lambda}
  - {title: 'その場で呼ぶラムダ：const int k = [&] { ... }(); で複雑な初期化をした値を const にする', anchor: immediately-invoked}
  - {title: 関数に渡す：sort の比較関数・二分探索の判定関数, anchor: pass-to-function}
  - {title: '型だけを書く：set<int, decltype(cmp)>・priority_queue<int, vector<int>, decltype(cmp)>（キャプチャのないラムダの既定構築。C++20。C++17 では pq(cmp) と渡す）', anchor: decltype-type}
  - {title: テンプレート引数に渡せるのはキャプチャのないラムダだけ（C++20。ACL の segtree）, anchor: template-argument}
  - {title: ラムダがそのままでは再帰できない理由（use of ‘f’ before deduction of ‘auto’）, anchor: recursive-lambda}
  - {title: 'std::function<void(int)> による再帰：読みやすいが、呼ぶたびに型消去を通る間接呼び出しになり遅い', anchor: std-function}
  - {title: '自分を引数で渡す再帰：[&](auto&& self, int v) -> void { ... self(self, to); } を dfs(dfs, 0) と呼ぶ', anchor: self-argument}
  - {title: 'deducing this：[&](this auto&& self, int v) -> void を dfs(0) と呼ぶ（C++23・GCC 14〜。g++-13 ではエラー）', anchor: deducing-this}
  - {title: 不動点コンビネータ（雛形の FixPoint・MFP）, anchor: fixpoint}
  - {title: 戻り値の型 -> void・-> int を書く場面（再帰より前に型の決まる return がないとき、三項演算子の中の再帰）, anchor: return-type}
  - {title: '速さの比較：std::function は fib(35) で約 5 倍、木の DFS で約 1.3 倍遅い。深い再帰はスタックに注意', anchor: speed}
stage: stub
updated: 2026-10-21
cpp_std: null
gcc_min: null
atcoder: true
---

!!! abstract "要点"
    - **何ができるか**：その場で関数を作るラムダ式で、比較関数・判定関数・DFS を書く。ラムダで再帰する 4 つの書き方（std::function・auto&& self・deducing this・不動点コンビネータ）の違いと速さも比べる。
    - **いつ使うか**：（執筆時に書く）
    - **計算量**：（執筆時に書く）
    - **前提**：[参照と範囲 for](../cpp/cpp-range-for.md)
