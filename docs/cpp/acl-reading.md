---
id: acl-reading
title: ACL の読み方
aliases: [AtCoder Library, ACL, atcoder/all, using namespace atcoder, val(), 'segtree<S, op, e>', lazy_segtree のテンプレート引数, テンプレート引数, ラムダをテンプレート引数に]
type: cpp
field: cpp
chapter: コンテナ・アルゴリズム・ACL
order: 150
level: 基礎
kind: [実装・C++]
prerequisites: [cpp-templates-constexpr, cpp-lambda]
related: [cpp-initialization, modint, mod-arithmetic, segment-tree, segment-tree-monoids, lazy-segment-tree, segment-tree-binary-search, library-design]
summary: AtCoder Library（ACL）を使う解説コードを、共通の約束（0 始まり・半開区間）とともに読む。modint の val() と出力、segtree・lazy_segtree のテンプレート引数にラムダを渡す書き方が分かる。
complexity: null
signs: []
acl: [static_modint, modint, segtree, lazy_segtree, dsu]
sections:
  - {title: 'include と共通の約束：#include <atcoder/all>・using namespace atcoder、添字は 0 始まり、区間は半開区間 [l, r)、引数なしで作った物は代入するまで使わない、制約の違反は assert で止まる（AtCoder では RE）', anchor: conventions}
  - {title: コンストラクタは modint 以外 explicit：dsu d(n) と書く（dsu d = n はエラー）, anchor: explicit}
  - {title: '版：AtCoder は v1.6。v1.5 との違いは modint::val() の型など（手元も v1.6 にそろえる）', anchor: version}
  - {title: 部品の呼び出し方の一覧：dsu・fenwick_tree・scc_graph・two_sat・mf_graph・mcf_graph・convolution・suffix_array・z_algorithm・floor_sum・crt（意味は各手法のページ）, anchor: components}
  - {title: 'dsu の groups() は vector の vector を返す：for (int v : d.groups()[0]) は C++23・GCC 15〜でだけ安全（変数に受けてから回す）', anchor: dsu-groups}
  - {title: modint の読み方：using mint = modint998244353; と書けば四則演算で法が自動で取られる（static_modint と set_mod の使い分け・割り算の条件・raw は math の modint のページ）, anchor: modint}
  - {title: modint の値・出力と版の差：cout << も println もできないので .val() を出す、v1.6 で val() は int（v1.5 の unsigned int では x.val() - 1 が巨大になる）、< がないのでソートや set に入れられない, anchor: modint-val}
  - {title: 'segtree<S, op, e> の読み方：S は要素の型、op は結合的な演算、e は単位元を返す関数', anchor: segtree-args, level: 水}
  - {title: 関数の渡し方：名前を渡す従来の形と、キャプチャのないラムダを直接渡す形（C++20・ACL v1.5〜）, anchor: passing-functions, level: 水}
  - {title: キャプチャのあるラムダは op・e に渡せない（is not a constant expression）、max_right・min_left の判定関数には渡せる, anchor: capturing-lambda, level: 水}
  - {title: 'lazy_segtree の 7 つの引数：F・mapping(f, x)・composition(f, g) は g の後に f・id', anchor: lazy-segtree-args, level: 水}
  - {title: 'テンプレート引数の形が合わないときの static_assert のメッセージ（op must work as S(S, S) など）', anchor: template-arg-errors, level: 水}
stage: stub
updated: 2026-10-21
cpp_std: null
gcc_min: null
atcoder: true
---

!!! abstract "要点"
    - **何ができるか**：AtCoder Library（ACL）を使う解説コードを、共通の約束（0 始まり・半開区間）とともに読む。modint の val() と出力、segtree・lazy_segtree のテンプレート引数にラムダを渡す書き方が分かる。
    - **いつ使うか**：（執筆時に書く）
    - **計算量**：（執筆時に書く）
    - **前提**：[関数テンプレートと constexpr](../cpp/cpp-templates-constexpr.md)、[ラムダ式と再帰ラムダ](../cpp/cpp-lambda.md)
