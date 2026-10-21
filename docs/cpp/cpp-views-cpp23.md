---
id: cpp-views-cpp23
title: C++23 の views と ranges::to
aliases: ['views::enumerate', 'views::zip', 'views::zip_transform', 'views::pairwise', 'views::adjacent', 'views::chunk', 'views::slide', 'views::chunk_by', 'views::stride', 'views::cartesian_product', 'views::repeat', 'views::join_with', 'ranges::to', to<vector>, from_range, append_range]
type: cpp
field: cpp
chapter: ranges と views
order: 170
level: 基礎
kind: [実装・C++]
prerequisites: [cpp-views-basics, cpp-structured-bindings]
related: [cpp-range-for, cpp-io, run-length-encoding, grid-graph, scc]
summary: C++23 の views（enumerate・zip・pairwise・chunk_by など）で添字付きや隣どうしのループを短く書き、ranges::to で結果をコンテナにする。要素は参照を含む組で、受けた変数への代入が元を変える。
complexity: null
signs: []
acl: []
sections:
  - {title: 'views::enumerate：（添字, 要素への参照）の組を作る、添字は ptrdiff_t（C++23・GCC 13〜）', anchor: enumerate}
  - {title: 'views::zip・zip_transform：同じ位置の要素の組、短いほうに合わせる（C++23・GCC 13〜）', anchor: zip}
  - {title: pairwise・adjacent<k>・pairwise_transform：隣り合う組と差分（C++23・GCC 13〜）, anchor: adjacent}
  - {title: chunk・slide・stride：k 個ずつの塊・長さ k の窓・k 個おき（C++23・GCC 13〜）, anchor: chunk-slide-stride}
  - {title: 'chunk_by：隣どうしで条件が成り立つ間をまとめる、s | views::chunk_by(equal_to{}) でランレングス圧縮（C++23・GCC 13〜）', anchor: chunk-by}
  - {title: cartesian_product：二重ループ・グリッドの全マスを 1 つのループにする（C++23・GCC 13〜）, anchor: cartesian-product}
  - {title: repeat・join_with・as_const（C++23・GCC 13〜）, anchor: repeat-join-with}
  - {title: '要素は参照を含む組：auto [i, x] でも x は元の要素を指す、auto& で受けるとエラー、const auto& でも書き換えを防げない（C++23・GCC 13〜）', anchor: reference-tuples}
  - {title: 'enumerate の添字を int にしたいとき：views::zip(views::iota(0), v)（max(best, i) の型の不一致を避ける）（C++23・GCC 13〜）', anchor: int-index}
  - {title: 'ranges::to<vector>()・to<set>()・入れ子の to<vector<vector<int>>>()（C++23・GCC 14〜）', anchor: ranges-to}
  - {title: 'from_range・insert_range・append_range（C++23・GCC 15〜）と、GCC 13 での代わり（views::common を挟んでイテレータの組から作る）', anchor: from-range}
  - {title: 'views::concat（C++26）は AtCoder では使えない', anchor: concat}
stage: stub
updated: 2026-10-21
cpp_std: 23
gcc_min: 13
atcoder: true
---

!!! abstract "要点"
    - **何ができるか**：C++23 の views（enumerate・zip・pairwise・chunk_by など）で添字付きや隣どうしのループを短く書き、ranges::to で結果をコンテナにする。要素は参照を含む組で、受けた変数への代入が元を変える。
    - **いつ使うか**：（執筆時に書く）
    - **計算量**：（執筆時に書く）
    - **前提**：[views の基本](../cpp/cpp-views-basics.md)、[構造化束縛と pair・tuple・optional](../cpp/cpp-structured-bindings.md)
