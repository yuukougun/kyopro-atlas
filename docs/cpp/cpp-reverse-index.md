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
  - {title: 1 行の読み方：何を回すか・何を受け取るか・どう受け取るかに分ける, anchor: how-to-read}
  - {title: 書き方から引く：型・リテラル・初期化・数の関数, anchor: lookup-types}
  - {title: 書き方から引く：参照・構造化束縛・組, anchor: lookup-references}
  - {title: 書き方から引く：ラムダ・再帰・テンプレート, anchor: lookup-lambda}
  - {title: 書き方から引く：雛形とマクロ, anchor: lookup-macros}
  - {title: 書き方から引く：コンテナ・比較関数・アルゴリズム・文字列, anchor: lookup-containers}
  - {title: 書き方から引く：views, anchor: lookup-views}
  - {title: 書き方から引く：入出力, anchor: lookup-io}
  - {title: 書き方から引く：ACL, anchor: lookup-acl}
  - {title: '混同しやすい書き方の対（std::iota と views::iota、unique と erase など）', anchor: confusing-pairs}
  - {title: 症状から引く：WA・RE・TLE と、手元と AtCoder で結果が違うとき, anchor: symptoms}
  - {title: 'コンパイルエラーのメッセージから引く（最初の error: の行と、required from here で自分の行を探す読み方を含む）', anchor: compile-errors}
stage: reviewed
updated: 2026-10-29
---

!!! abstract "要点"
    - **何のページか**：解説コードの書き方・実行時の症状・コンパイルエラーのメッセージから、意味と C++ 章の該当する節を引く。1 行を「何を回すか・何を受け取るか・どう受け取るか」に分けて読む手順も示す。
    - **いつ引くか**：
        - 解説コードに見慣れない書き方（`| views::enumerate`・`this auto&& self`・`(a = b, true)` など）があって読めない。
        - 手元と AtCoder で結果が違う、`-O2` にすると答えが変わる、大きいケースだけ RE・TLE になる。
        - コンパイルエラーが長くて、どこを直せばよいか分からない。
    - **使い方**：書き方は[書き方から引く](#lookup-types)の各表で、症状は[症状から引く](#symptoms)で、エラーは[コンパイルエラーから引く](#compile-errors)で探し、行のリンク先の節で意味と落とし穴を確かめる。1 行に部品がいくつも重なっているときは、先に[1 行の読み方](#how-to-read)で部品に分ける。
    - **前提**：なし

<!-- textlint-disable -->
別名：解説コードの読み方・解説コードが読めない・モダン C++ の読み方・書き方から引く・症状から引く・Segmentation fault・コンパイルエラーの読み方・エラーメッセージ・required from here
<!-- textlint-enable -->

C++ の逆引きは、C++ 章の各ページへの索引である。表の 1 行は「書き方（または症状・メッセージ）→ 一言の意味 → 節へのリンク」で、意味の説明・版・落とし穴は行き先の節にある。前提にする環境は AtCoder の GCC 15.2（`-std=gnu++23`）と ACL v1.6 である。手元が g++-13 なら、使えない書き方もある（各節の「版」を見る。対応表は [C++ の版と GCC の対応表](../cpp/cpp-environment.md#version-matrix)）。

## 1 行の読み方：何を回すか・何を受け取るか・どう受け取るかに分ける {#how-to-read}

解説コードの 1 行が読めないのは、たいてい知らない部品が 2〜3 個重なっているからである。次の範囲 for は、ACL・views・構造化束縛・参照の 4 つの部品でできている。

```cpp
--8<-- "cpp-reverse-index/read-line.cpp:core"
```

範囲 for の 1 行は、次の 3 つの問いに分けて読む。

1. **何を回すか**（`:` の右）：範囲の式を左から読む。`scc.scc()` は ACL の強連結成分分解で、成分をトポロジカル順に並べた `vector<vector<int>>` を返す。それを `| views::enumerate` に流すと、（添字, 成分への参照）の組を順に作る範囲になる
2. **何を受け取るか**（`[` `]` の中）：組の中身に名前を付ける構造化束縛である。`i` が添字（型は `ptrdiff_t`）、`component` が 1 つの成分を指す
3. **どう受け取るか**（`[` の左）：`const auto&` は、その場で作られる組を const 参照で受ける。const が付くのは組のほうなので、組が持つ参照の先の `component` は `vector<int>&` のままである（コード片の `static_assert` で確かめた）

![範囲 for の 1 行を 4 つの部品に分けた図。scc.scc() と views::enumerate は何を回すか、[i, component] は何を受け取るか、const auto& はどう受け取るかに当たる。行き先は強連結成分分解・views::enumerate・構造化束縛・範囲 for の受け方の節](../img/cpp-reverse-index/read-line.svg)

部品ごとの行き先は次のとおりである。部品に分けた後は、それぞれを下の表で引けばよい。

- `scc.scc()`：[強連結成分分解](../graph/scc.md)と [ACL の部品の一覧](../cpp/acl-reading.md#components)
- `| views::enumerate`：[views::enumerate](../cpp/cpp-views-cpp23.md#enumerate)。`scc.scc()` の戻り値は[一時オブジェクト](../guide/glossary.md#temporary-object)だが、パイプに流すと view の中に移されるので、ループの間は生きている（[view の寿命](../cpp/cpp-views-basics.md#lifetime)）
- `[i, component]`：[構造化束縛](../cpp/cpp-structured-bindings.md#structured-binding)。組の要素が参照なので、名前も元の成分を指す（[enumerate の要素は参照を含む組](../cpp/cpp-structured-bindings.md#enumerate-reference)）
- `const auto&`：[範囲 for の 4 通りの受け方](../cpp/cpp-range-for.md#range-for-forms)。`auto&` に変えると、その場で作られた組（一時オブジェクト）を const のない参照で受けることになり、コンパイルエラーになる（[要素は参照を含む組](../cpp/cpp-views-cpp23.md#reference-tuples)）

範囲 for 以外の行も同じ考え方で読める。ラムダなら「何を取り込むか（`[` `]`）・何を受け取るか（引数）・何を返すか（`->` の後）」に、宣言なら「型・名前・初期化」に分ける。分けた部品のうち、`auto` が何の型になるかが分からないときは、[auto が推論する型](../cpp/cpp-types-literals.md#auto-deduction)を見る。

## 書き方から引く：型・リテラル・初期化・数の関数 {#lookup-types}

数の型・定数の書き方・配列の作り方・数の関数を引く。整数のあふれに関わる書き方は[症状から引く](#symptoms)にもある。

| 書き方 | 意味 | ページ |
| --- | --- | --- |
| `int`・`long long`・`size_t`・`int64_t` | 整数の型と表せる範囲 | [整数の型](../cpp/cpp-types-literals.md#integer-types) |
| `1LL << 60`・`1'000'000'007`・`0b1010`・`0uz` | `long long` の 1、桁区切り、2 進、`size_t` の 0（C++23） | [リテラルの書き方](../cpp/cpp-types-literals.md#literals) |
| `auto x = 0;`・`auto n = v.size();` | `auto` は `int`・`size_t` になる | [auto が推論する型](../cpp/cpp-types-literals.md#auto-deduction) |
| `using ll = long long;`・`ll(x)` | 型の別名（`#define` との違い） | [型の別名](../cpp/cpp-types-literals.md#type-alias) |
| `static_cast<long long>(x)`・`(long long)x` | キャスト | [キャスト](../cpp/cpp-types-literals.md#cast) |
| `const int INF = 1 << 30;`・`0x3f3f3f3f`・`LLONG_MAX` | INF の決め方と INF + INF | [INF の決め方](../cpp/cpp-types-literals.md#inf) |
| `1e18`・`auto INF = 1e18;` | `double` の値（整数ではない） | [1e18 は double](../cpp/cpp-types-literals.md#double-1e18) |
| `abs(a - b) < 1e-9` | 浮動小数点数を誤差つきで比べる | [== で比べない](../cpp/cpp-types-literals.md#float-compare) |
| `__int128`・`i128` | 128 bit 整数（GCC の拡張） | [__int128](../cpp/cpp-integer-overflow.md#int128) |
| `1LL * a * b` | 積を `long long` で計算する | [int どうしの積](../cpp/cpp-integer-overflow.md#int-product) |
| `1 << 40`・`1 << k` | `int` の 1 を 32 以上ずらすと未定義動作（`1LL << k` と書く） | [シフトの幅](../cpp/cpp-integer-overflow.md#shift-width) |
| `__builtin_mul_overflow(a, b, &r)` | 積があふれるかを判定する（GCC の拡張） | [積のあふれの判定](../cpp/cpp-integer-overflow.md#overflow-check) |
| `vector<int> a(n);`・`vector<int> a(n, x);` | 0 が $n$ 個・$x$ が $n$ 個 | [vector の初期化](../cpp/cpp-initialization.md#vector-init) |
| `vector dp(n, vector(m, 0LL));` | 型を内側から決める 2 次元の vector（CTAD） | [CTAD](../cpp/cpp-initialization.md#ctad)・[多次元 vector](../cpp/cpp-initialization.md#multi-dim-vector) |
| `pair p{1, 2};`・`priority_queue pq(v.begin(), v.end());` | 標準の型の CTAD | [pair などの CTAD](../cpp/cpp-initialization.md#ctad-std-types) |
| `array<int, 26> cnt{};` | 固定長の配列を 0 で作る | [array と 0 初期化](../cpp/cpp-initialization.md#array-init) |
| `Edge{.to = v, .cost = c}` | 指示付き初期化（C++20） | [指示付き初期化](../cpp/cpp-initialization.md#designated-init) |
| `memset(d, 0x3f, sizeof d)`・`fill`・`assign` | 表の埋め直し（`memset` はバイト単位） | [埋め直し](../cpp/cpp-initialization.md#refill) |
| `gcd(a, b)`・`lcm(a, b)`・`__gcd` | 最大公約数・最小公倍数 | [gcd・lcm](../cpp/cpp-math-functions.md#gcd-lcm) |
| `midpoint(a, b)`・`clamp(x, lo, hi)` | あふれない中点（C++20）・範囲に収めた値（C++17） | [midpoint・clamp](../cpp/cpp-math-functions.md#midpoint-clamp) |
| `-7 / 2`・`-7 % 2` | 商は 0 に向かって切り捨て、余りは負になりうる | [整数の割り算](../cpp/cpp-math-functions.md#integer-division) |
| `pow(a, b)`・`sqrt(x)`・`sqrtl(x)` | `double` で計算する | [pow・sqrt](../cpp/cpp-math-functions.md#pow-sqrt) |
| `numbers::pi`・`M_PI`・`acos(-1)` | 円周率（`double` ではどれも同じ値。`numbers::pi` は C++20） | [円周率](../cpp/cpp-math-functions.md#pi) |
| `popcount(x)`・`countr_zero(x)`・`bit_width(x)`・`bit_ceil(x)` | bit ヘッダの関数（符号なしだけ） | [bit ヘッダの関数](../cpp/cpp-math-functions.md#bit-functions) |
| `__builtin_popcountll(x)`・`__builtin_ctz(x)`・`__lg(x)` | GCC の組み込み関数 | [組み込み関数](../cpp/cpp-math-functions.md#builtins) |
| `x & -x`・`x & (x - 1)`・`s = (s - 1) & m` | 最下位の 1・それを消す・部分集合を回す | [ビットの小技](../cpp/cpp-math-functions.md#bit-tricks) |
| `bitset<N> dp;`・`dp |= dp << w` | ビットの集合 | [bitset](../cpp/cpp-math-functions.md#bitset) |
| `mt19937_64 rng(random_device{}());`・`uniform_int_distribution` | 乱数 | [乱数](../cpp/cpp-math-functions.md#random) |
| `chrono::steady_clock::now()` | 時間計測 | [時間計測](../cpp/cpp-math-functions.md#chrono) |

## 書き方から引く：参照・構造化束縛・組 {#lookup-references}

`&` の付いた受け方と、組を名前に分ける書き方を引く。どれも「コピーか、元を指すか」が読みどころである。

| 書き方 | 意味 | ページ |
| --- | --- | --- |
| `auto& row = g[0];`・`const vector<int>& a` | 参照と const 参照（コピーしない） | [参照の基本](../cpp/cpp-range-for.md#reference-basics)・[関数の引数](../cpp/cpp-range-for.md#pass-by-reference) |
| `for (auto x : v)`・`auto&`・`const auto&`・`auto&&` | 範囲 for の 4 通りの受け方 | [範囲 for の受け方](../cpp/cpp-range-for.md#range-for-forms) |
| `auto&&` | 何でも受けられる参照 | [auto&&](../cpp/cpp-range-for.md#forwarding-reference) |
| `for (int i = 0; auto x : v)` | 初期化式付きの範囲 for（C++20） | [範囲 for の初期化式](../cpp/cpp-range-for.md#range-for-init) |
| `swap(dp, ndp)`・`std::move(v)` | 中身の入れ替え・ムーブ | [ムーブと swap](../cpp/cpp-range-for.md#move-swap) |
| `auto [a, b] = p;`・`auto& [x, y] = e;` | 構造化束縛（C++17） | [構造化束縛の形](../cpp/cpp-structured-bindings.md#structured-binding)・[見えない変数](../cpp/cpp-structured-bindings.md#hidden-variable) |
| `for (auto& [k, v] : mp)` | map を回す（キーは const） | [map を回すとき](../cpp/cpp-structured-bindings.md#map-loop) |
| `if (auto it = mp.find(k); it != mp.end())` | 初期化式付き if（C++17） | [初期化式付き if](../cpp/cpp-structured-bindings.md#if-init) |
| `auto [d, v] = pq.top(); pq.pop();` | 値で受けてから pop する | [pq.top() を参照で受けない](../cpp/cpp-structured-bindings.md#pq-top-reference) |
| `auto [h, w] = p;` の後の `[&]`・`auto [_, c] = e;` | 構造化束縛した名前のキャプチャ（C++20）、使わない名前 | [キャプチャと _](../cpp/cpp-structured-bindings.md#capture-and-placeholder) |
| `pair`・`tuple`・`get<0>(t)`・`make_pair` | 組と辞書順の比較 | [pair と tuple](../cpp/cpp-structured-bindings.md#pair-tuple) |
| `tie(a, b) = f();`・`tie(a, b) < tie(c, d)` | 既存の変数にまとめて代入・比較 | [tie](../cpp/cpp-structured-bindings.md#tie) |
| `tie(a, b) = pair{b, a + b};` | まとめて更新（`tie(a, b) = tie(b, a)` は誤り） | [tie の入れ替えの罠](../cpp/cpp-structured-bindings.md#tie-swap-pitfall) |
| `prev = exchange(cur, nxt);` | 代入して前の値を返す | [exchange](../cpp/cpp-structured-bindings.md#exchange) |
| `optional<int>`・`nullopt`・`value_or` | 値がないことを表す | [optional](../cpp/cpp-structured-bindings.md#optional) |
| `apply(f, t)` | 組を引数に展開して呼ぶ | [apply](../cpp/cpp-structured-bindings.md#apply) |

## 書き方から引く：ラムダ・再帰・テンプレート {#lookup-lambda}

ラムダ式と、型を引数に取る書き方（template）を引く。再帰ラムダは書き方が 4 通りあり、解説コードによって違う。

| 書き方 | 意味 | ページ |
| --- | --- | --- |
| `[&](int v) { ... }`・`[=]`・`[x = 0]() mutable` | キャプチャ（参照・コピー・初期化） | [キャプチャ](../cpp/cpp-lambda.md#capture) |
| `[](auto x)`・`[]<class T>(T x)`・`static` | ジェネリックラムダと static ラムダ | [ジェネリックラムダ](../cpp/cpp-lambda.md#generic-lambda) |
| `const int k = [&] { ... }();` | その場で呼ぶラムダ | [その場で呼ぶラムダ](../cpp/cpp-lambda.md#immediately-invoked) |
| `sort(v.begin(), v.end(), [](int a, int b) { ... })` | 関数にラムダを渡す | [関数に渡す](../cpp/cpp-lambda.md#pass-to-function) |
| `set<int, decltype(cmp)>` | ラムダの型を書く（C++20） | [decltype で型を書く](../cpp/cpp-lambda.md#decltype-type) |
| `function<void(int)> dfs = ...` | std::function による再帰（遅い） | [std::function](../cpp/cpp-lambda.md#std-function) |
| `auto dfs = [&](auto&& self, int v) -> void { ... };`・`dfs(dfs, 0)` | 自分を引数で渡す再帰 | [自分を引数で渡す](../cpp/cpp-lambda.md#self-argument) |
| `[&](this auto&& self, int v) -> void` | deducing this（C++23・GCC 14〜） | [deducing this](../cpp/cpp-lambda.md#deducing-this) |
| `FixPoint`・`MFP` | 雛形の不動点コンビネータ | [不動点コンビネータ](../cpp/cpp-lambda.md#fixpoint) |
| `-> void`・`-> long long` | 戻り値の型を後ろに書く | [戻り値の型](../cpp/cpp-lambda.md#return-type) |
| `template <class T>` | 関数テンプレート | [関数テンプレート](../cpp/cpp-templates-constexpr.md#function-template) |
| `max<long long>(a, b)` | 型を明示して呼ぶ | [型を明示して呼ぶ](../cpp/cpp-templates-constexpr.md#explicit-type) |
| `auto sq(auto x)` | 省略形のテンプレート（C++20） | [auto 引数の省略形](../cpp/cpp-templates-constexpr.md#abbreviated-template) |
| `template <integral T>`・`requires` | コンセプト（C++20） | [コンセプトと requires](../cpp/cpp-templates-constexpr.md#concepts) |
| `constexpr`・`constexpr auto T = [] { ... }();` | コンパイル時の定数と表 | [constexpr](../cpp/cpp-templates-constexpr.md#constexpr) |
| `static_assert`・`if constexpr` | コンパイル時の確認と枝分かれ | [static_assert](../cpp/cpp-templates-constexpr.md#static-assert) |
| `(cerr << ... << args)` | 畳み込み式（デバッグ出力） | [畳み込み式](../cpp/cpp-templates-constexpr.md#fold-expression) |
| `[[maybe_unused]]`・`[[nodiscard]]`・`[[likely]]` | 属性 | [属性](../cpp/cpp-templates-constexpr.md#attributes) |

## 書き方から引く：雛形とマクロ {#lookup-macros}

解説コードの先頭に貼られた雛形（テンプレートファイル）の部品を引く。競プロで言う「テンプレート」と C++ の `template` は別物である（[2 つの意味](../cpp/cpp-templates-constexpr.md#two-meanings)）。

| 書き方 | 意味 | ページ |
| --- | --- | --- |
| `#include <bits/stdc++.h>`・`using namespace std;` | 標準ライブラリをすべて読む | [bits/stdc++.h](../cpp/cpp-macros-template-file.md#bits-stdcpp) |
| グローバル変数の `count`・`y1` | 名前の衝突でエラーになる | [名前の衝突](../cpp/cpp-macros-template-file.md#namespaces) |
| `import std;` | モジュールで読む（C++23・GCC 15〜） | [import std;](../cpp/cpp-macros-template-file.md#import-std) |
| `rep(i, n)`・`all(v)`・`FOR`・`vc`・`vvc` | マクロ（文字の置き換え） | [マクロ](../cpp/cpp-macros-template-file.md#macros) |
| `#define int long long`・`signed main()` | `int` を丸ごと置き換える | [#define int long long](../cpp/cpp-macros-template-file.md#define-int) |
| `chmin(a, b)`・`return a > b && (a = b, true);` | 小さければ更新（カンマ演算子の形も） | [chmin・chmax](../cpp/cpp-macros-template-file.md#chmin) |
| `#ifdef LOCAL`・`debug(x)` | 手元だけのデバッグ出力 | [#ifdef LOCAL](../cpp/cpp-macros-template-file.md#ifdef-local) |
| `#ifdef ATCODER`・`#ifndef ONLINE_JUDGE` | ジャッジでだけ定義されるマクロで、提出と手元を分ける | [ジャッジのマクロ](../cpp/cpp-environment.md#judge-macros) |
| `#pragma GCC optimize`・`#pragma GCC target` | 最適化・命令の指定 | [#pragma GCC](../cpp/cpp-macros-template-file.md#pragma) |
| `#include "graph.hpp"` | 自作のヘッダ（提出前に展開する） | [バンドル](../cpp/cpp-macros-template-file.md#bundling)・[展開の道具](../cpp/cpp-macros-template-file.md#bundling-tools) |
| `// @impl` | この教材の作者が改造した cph（VS Code の拡張）で、main の後ろに回す部分を分ける印。公式の cph にはない | [@impl](../cpp/cpp-macros-template-file.md#impl-marker)・[cph の改造版](../cpp/cpp-macros-template-file.md#bundling-tools) |

## 書き方から引く：コンテナ・比較関数・アルゴリズム・文字列 {#lookup-containers}

コンテナの操作・比較関数・algorithm と numeric の関数・文字列の操作を引く。コンテナの種類の選び方は [STL コンテナ](../ds/stl-containers.md)にある。

| 書き方 | 意味 | ページ |
| --- | --- | --- |
| `erase_if(v, pred)`・`erase(v, x)` | 条件で消す（C++20） | [erase_if](../cpp/cpp-container-idioms.md#erase-if) |
| `st.contains(x)`・`st.count(x)` | 含まれるか | [contains](../cpp/cpp-container-idioms.md#contains) |
| `mp[k]` | キーがなければ要素を作る | [map の添字](../cpp/cpp-container-idioms.md#map-subscript) |
| `ms.erase(ms.find(x));` | multiset から 1 個だけ消す | [multiset から 1 個消す](../cpp/cpp-container-idioms.md#multiset-erase-one) |
| `emplace_back(a, b)` | その場で作って追加する | [emplace_back](../cpp/cpp-container-idioms.md#emplace-back) |
| `st.lower_bound(x)` | set・map のメンバ関数（$O(\log N)$） | [メンバの lower_bound](../cpp/cpp-container-idioms.md#member-lower-bound) |
| `*prev(st.end())`・`*st.rbegin()`・`next(it)` | 最後の要素・隣のイテレータ | [イテレータの基本](../cpp/cpp-container-idioms.md#iterators) |
| `lower_bound(...) - v.begin()` | 位置を添字にする | [添字への変換](../cpp/cpp-container-idioms.md#iterator-index) |
| `it = st.erase(it);` | 消して次へ進む | [erase は次を返す](../cpp/cpp-container-idioms.md#erase-returns-next) |
| `unordered_map<long long, int, H>` | 自作のハッシュ | [unordered_map](../cpp/cpp-container-idioms.md#unordered-map) |
| `tree<...>`・`order_of_key`・`find_by_order` | pb_ds の順序付き集合 | [pb_ds](../cpp/cpp-container-idioms.md#pb-ds) |
| `sort(v.rbegin(), v.rend())`・`sort(..., greater<>())` | 降順のソート | [sort と降順](../cpp/cpp-algorithms.md#sort)・[greater](../cpp/cpp-comparators.md#greater) |
| `priority_queue<T, vector<T>, greater<T>>` | 最小が先頭のヒープ | [priority_queue の向き](../cpp/cpp-comparators.md#priority-queue-order) |
| `[](auto& a, auto& b) { return a.x < b.x; }` | 比較関数の約束（狭義の弱順序） | [比較関数の約束](../cpp/cpp-comparators.md#strict-weak-ordering) |
| `bool operator<(const P& o) const` | 構造体の比較演算子 | [比較演算子の小なり](../cpp/cpp-comparators.md#operator-less) |
| `auto operator<=>(const P&) const = default;` | 比較を宣言順の辞書順で作る（C++20） | [三方比較演算子](../cpp/cpp-comparators.md#spaceship) |
| `v.erase(unique(v.begin(), v.end()), v.end());` | 重複の削除 | [重複の削除](../cpp/cpp-algorithms.md#unique-erase) |
| `lower_bound`・`upper_bound`・`equal_range` | 二分探索 | [二分探索の関数](../cpp/cpp-algorithms.md#lower-bound) |
| `accumulate(v.begin(), v.end(), 0LL)`・`reduce` | 総和（初期値の型で足す） | [accumulate](../cpp/cpp-algorithms.md#accumulate) |
| `partial_sum`・`inclusive_scan`・`adjacent_difference` | 累積和と差分 | [累積和と差分](../cpp/cpp-algorithms.md#partial-sum) |
| `iota(v.begin(), v.end(), 0)` | 連番で埋める | [連番](../cpp/cpp-algorithms.md#iota) |
| `do { ... } while (next_permutation(...))` | 順列の列挙 | [next_permutation](../cpp/cpp-algorithms.md#next-permutation) |
| `*max_element(...)`・`max({a, b, c})`・`clamp` | 最大・最小 | [最大・最小・個数](../cpp/cpp-algorithms.md#max-element) |
| `ranges::sort(v)` | コンテナを直接渡す（C++20） | [ranges 版](../cpp/cpp-algorithms.md#ranges) |
| `ranges::sort(ps, {}, &P::score)` | 射影（C++20） | [射影](../cpp/cpp-algorithms.md#projection) |
| `ranges::unique(v)` | 後ろの不要部分を返す | [ranges::unique](../cpp/cpp-algorithms.md#ranges-unique) |
| `ranges::fold_left(v, 0LL, plus{})`・`ranges::contains` | 畳み込み・含まれるか（C++23） | [fold_left](../cpp/cpp-algorithms.md#fold-left) |
| `c - 'a'`・`char('a' + i)`・`c - '0'` | 文字と数の変換 | [文字と数](../cpp/cpp-string-api.md#char-arithmetic) |
| `s.substr(i, len)`・`s.find(t) == string::npos` | 部分文字列と検索 | [substr・find](../cpp/cpp-string-api.md#substr-find) |
| `s += c`・`s = s + c` | 後ろに足す（後者は毎回コピー） | [文字列に足す](../cpp/cpp-string-api.md#append) |
| `to_string(x)`・`stoll(s)` | 数と文字列の変換 | [to_string](../cpp/cpp-string-api.md#to-string) |
| `s.starts_with(t)`・`s.contains(t)` | 先頭・含まれるか | [starts_with](../cpp/cpp-string-api.md#starts-with) |
| `string(n, c)`・`reverse(s.begin(), s.end())` | 作る・反転・辞書順の比較 | [作成と比較](../cpp/cpp-string-api.md#construct-compare) |
| `string_view` | コピーしない部分文字列 | [string_view](../cpp/cpp-string-api.md#string-view) |
| `getline(cin, s)` | 1 行を読む（残った改行に注意） | [getline](../cpp/cpp-string-api.md#getline) |

## 書き方から引く：views {#lookup-views}

`|` でつないだ範囲の書き方（views）を引く。view は元の範囲を見る方法だけを持ち、取り出すときに計算する（[view とは](../cpp/cpp-views-basics.md#what-is-view)）。C++23 の views は GCC 13 から、`ranges::to` は GCC 14 から使える。

| 書き方 | 意味 | ページ |
| --- | --- | --- |
| `for (int i : views::iota(0, n))` | 0 から $n-1$ まで | [views::iota](../cpp/cpp-views-basics.md#iota) |
| `views::iota(0, v.size())` | 型が違ってコンパイルエラー | [iota の型の不一致](../cpp/cpp-views-basics.md#iota-size-mismatch) |
| `v | views::reverse` | 逆順に見るだけ | [views::reverse](../cpp/cpp-views-basics.md#reverse) |
| `v | views::filter(f) | views::transform(g)` | 絞り込み・変換 | [filter と transform](../cpp/cpp-views-basics.md#filter-transform) |
| `views::take(k)`・`views::drop(k)`・`take_while` | 先頭の k 個・残り | [take・drop](../cpp/cpp-views-basics.md#take-drop) |
| `views::keys(mp)`・`views::values(mp)` | map のキー・値だけ | [keys・values](../cpp/cpp-views-basics.md#keys-values) |
| `s | views::split(' ')`・`views::join` | 区切る・平らにする | [split と join](../cpp/cpp-views-basics.md#split-join) |
| `views::common` | 古いコンストラクタに渡す | [common](../cpp/cpp-views-basics.md#common) |
| `v | views::enumerate` | 添字を付ける（添字は `ptrdiff_t`） | [enumerate](../cpp/cpp-views-cpp23.md#enumerate) |
| `views::zip(a, b)`・`zip_transform` | 同じ位置の組 | [zip](../cpp/cpp-views-cpp23.md#zip) |
| `views::pairwise`・`views::adjacent<3>` | 隣り合う組 | [pairwise・adjacent](../cpp/cpp-views-cpp23.md#adjacent) |
| `views::chunk(k)`・`views::slide(k)`・`views::stride(k)` | 塊・窓・k 個おき | [chunk・slide・stride](../cpp/cpp-views-cpp23.md#chunk-slide-stride) |
| `s | views::chunk_by(equal_to{})` | 同じ値の連続をまとめる | [chunk_by](../cpp/cpp-views-cpp23.md#chunk-by) |
| `views::cartesian_product(views::iota(0, h), views::iota(0, w))` | 二重ループを 1 つにする | [cartesian_product](../cpp/cpp-views-cpp23.md#cartesian-product) |
| `views::repeat`・`views::join_with` | 繰り返す・区切りを挟んでつなぐ | [repeat・join_with](../cpp/cpp-views-cpp23.md#repeat-join-with) |
| `views::zip(views::iota(0), v)` | `int` の添字を付ける | [enumerate の添字を int に](../cpp/cpp-views-cpp23.md#int-index) |
| `| ranges::to<vector>()` | コンテナにする（GCC 14〜） | [ranges::to](../cpp/cpp-views-cpp23.md#ranges-to) |
| `vector<int>(from_range, r)`・`append_range` | 範囲から作る・足す（GCC 15〜） | [from_range](../cpp/cpp-views-cpp23.md#from-range) |
| `views::concat(a, b)` | C++26 で AtCoder では使えない | [views::concat](../cpp/cpp-views-cpp23.md#concat) |

## 書き方から引く：入出力 {#lookup-io}

入出力の書き方を引く。出力の速さと TLE の関係は[症状から引く](#symptoms)にもある。

| 書き方 | 意味 | ページ |
| --- | --- | --- |
| `cin.tie(nullptr); ios::sync_with_stdio(false);` | 入出力の高速化 | [入出力の高速化](../cpp/cpp-io.md#fast-io) |
| `endl`・`'\n'` | 改行のたびに書き出すか | [endl](../cpp/cpp-io.md#endl) |
| `cout << a[i] << " \n"[i == n - 1];` | 最後だけ改行する | [区切りと改行](../cpp/cpp-io.md#separators) |
| `while (cin >> x)` | 入力の終わりまで読む | [終わりまで読む](../cpp/cpp-io.md#read-until-eof) |
| `printf("%lld\n", x)`・`scanf` | C の入出力と書式 | [printf・scanf](../cpp/cpp-io.md#printf) |
| `println("{} {}", a, b);`・`format(...)` | 書式つき出力（`println` は GCC 14〜） | [format と println](../cpp/cpp-io.md#format-println) |
| `"{:.10f}"`・`"{:>5}"`・`"{:b}"` | 書式の指定 | [書式の指定](../cpp/cpp-io.md#format-spec) |
| `cout << fixed << setprecision(15)` | 小数の桁 | [小数の出力](../cpp/cpp-io.md#float-output) |
| `fflush(stdout)`・`cout << flush` | 書き出す（インタラクティブ） | [フラッシュ](../cpp/cpp-io.md#flush) |
| `cout << x.val()`・`__int128` の出力 | そのままでは出せない型 | [出力できない型](../cpp/cpp-io.md#unprintable-types)・[__int128 の入出力](../cpp/cpp-integer-overflow.md#int128-io) |

## 書き方から引く：ACL {#lookup-acl}

ACL（AtCoder Library）の部品の書き方を引く。各部品が何をするか（手法）は手法のページにあり、ここで引けるのは C++ としての読み方である。

| 書き方 | 意味 | ページ |
| --- | --- | --- |
| `#include <atcoder/all>`・`using namespace atcoder;` | 取り込みと共通の約束（0-indexed・半開区間） | [include と共通の約束](../cpp/acl-reading.md#conventions) |
| `dsu d(n);`・`fenwick_tree<long long> fw(n);`・`scc_graph g(n);` | 部品の作り方と主なメソッド | [部品の一覧](../cpp/acl-reading.md#components) |
| `dsu d = n;` | explicit なのでエラー | [explicit](../cpp/acl-reading.md#explicit) |
| `for (auto& g : d.groups())` | groups() の戻り値を回す | [dsu の groups()](../cpp/acl-reading.md#dsu-groups) |
| `using mint = modint998244353;` | 法が自動で取られる整数 | [modint の読み方](../cpp/acl-reading.md#modint)・[modint](../math/modint.md) |
| `x.val()` | modint の値（v1.6 で `int`） | [modint の値と出力](../cpp/acl-reading.md#modint-val) |
| `segtree<S, op, e> seg(n);` | 要素の型・演算・単位元 | [segtree の引数](../cpp/acl-reading.md#segtree-args)・[セグメント木](../ds/segment-tree.md) |
| `segtree<int, op, e>`・`segtree<int, [](int a, int b) { ... }, ...>` | 関数の名前かキャプチャのないラムダを渡す | [関数の渡し方](../cpp/acl-reading.md#passing-functions) |
| `seg.max_right(l, [&](S x) { ... })` | 判定の関数にはキャプチャのあるラムダも渡せる | [キャプチャのあるラムダ](../cpp/acl-reading.md#capturing-lambda) |
| `lazy_segtree<S, op, e, F, mapping, composition, id>` | 7 つの引数 | [lazy_segtree の引数](../cpp/acl-reading.md#lazy-segtree-args) |

ACL の版の違い（v1.5 と v1.6）は [ACL の版](../cpp/acl-reading.md#version) にある。

## 混同しやすい書き方の対（std::iota と views::iota、unique と erase など） {#confusing-pairs}

名前や見た目が似ていて、意味が違う書き方の対を並べる。左を見て右と取り違えていないかを確かめる。

| 対 | 違い | ページ |
| --- | --- | --- |
| `std::iota` と `views::iota` | 配列を連番で埋める／連番を生み出す view | [連番](../cpp/cpp-algorithms.md#iota) |
| `reverse(v.begin(), v.end())` と `v | views::reverse` | 並べ替える／逆順に見るだけ | [views::reverse](../cpp/cpp-views-basics.md#reverse) |
| `unique` と `erase` | 前に詰めて終端を返すだけ／実際に消す | [重複の削除](../cpp/cpp-algorithms.md#unique-erase) |
| `accumulate` と `reduce` | 初期値の型で足す／初期値を省くと要素の型 | [accumulate](../cpp/cpp-algorithms.md#accumulate) |
| `v.size()` と `ssize(v)` | 符号なし／符号付き | [size() は符号なし](../cpp/cpp-integer-overflow.md#unsigned-size) |
| `endl` と `'\n'` | 毎回書き出す／書き出さない | [endl](../cpp/cpp-io.md#endl) |
| `-std=c++23` と `-std=gnu++23` | GNU 拡張なし／あり（AtCoder は後者） | [-std=c++23 では __int128 が整数型にならない](../cpp/cpp-integer-overflow.md#int128-strict-mode) |
| `st.lower_bound(x)` と `lower_bound(st.begin(), st.end(), x)` | $O(\log N)$／set では $O(N)$ | [メンバの lower_bound](../cpp/cpp-container-idioms.md#member-lower-bound) |
| `mp[k]` と `mp.contains(k)` | なければ作る／調べるだけ | [map の添字](../cpp/cpp-container-idioms.md#map-subscript) |
| `ms.erase(x)` と `ms.erase(ms.find(x))` | 全部消す／1 個だけ消す | [multiset から 1 個消す](../cpp/cpp-container-idioms.md#multiset-erase-one) |
| `sort` の `greater` と `priority_queue` の `greater` | 降順に並ぶ／最小が先頭 | [priority_queue の向き](../cpp/cpp-comparators.md#priority-queue-order) |
| `<` と `<=` の比較関数 | 正しい／sort が壊れる | [「以下」の比較関数](../cpp/cpp-comparators.md#less-equal-pitfall) |
| `memset` と `fill` | バイト単位／要素単位 | [埋め直し](../cpp/cpp-initialization.md#refill) |
| `vector<int> v(n)` と `vector<int> v{n}` | 0 が $n$ 個／値 $n$ が 1 個 | [vector の初期化](../cpp/cpp-initialization.md#vector-init) |
| `#define ll long long` と `using ll = long long;` | 文字の置き換え／型の別名 | [型の別名](../cpp/cpp-types-literals.md#type-alias) |
| `__builtin_popcount` と `std::popcount` | `int` もそのまま渡せる／符号なし整数しか受けない | [符号なし整数だけ](../cpp/cpp-math-functions.md#bit-unsigned-only) |
| `std::function` と `auto&& self` | 型消去で遅い／速い | [std::function](../cpp/cpp-lambda.md#std-function) |
| `auto` と `auto&` | コピー／元を指す | [範囲 for の受け方](../cpp/cpp-range-for.md#range-for-forms) |
| `swap(dp, ndp)` と `dp = ndp` | $O(1)$ の入れ替え／長さに比例するコピー | [ムーブと swap](../cpp/cpp-range-for.md#move-swap) |
| C++ の `template` と競プロのテンプレート | 型を引数に取る関数／雛形のファイル | [2 つの意味](../cpp/cpp-templates-constexpr.md#two-meanings) |

## 症状から引く：WA・RE・TLE と、手元と AtCoder で結果が違うとき {#symptoms}

実行して初めて分かる不具合のうち、C++ の書き方に由来するものを症状から引く。考察の誤りや境界の見落としも含めた点検の順は[デバッグのチェックリスト](../guide/debugging-checklist.md)にある。

| 症状 | 疑うこと | ページ |
| --- | --- | --- |
| AtCoder では AC、手元では答えがおかしい | 未初期化変数（AtCoder では 0 になる） | [未初期化変数](../cpp/cpp-undefined-behavior.md#uninitialized) |
| `-O0` と `-O2` で答えが違う、関係のない行で答えが変わる | 未定義動作（あふれ・範囲外） | [未定義動作とは](../cpp/cpp-undefined-behavior.md#what-is-ub)・[他の行まで壊す](../cpp/cpp-undefined-behavior.md#breaks-other-lines) |
| 手元でだけ Segmentation fault（深い再帰） | スタックの上限 | [再帰の深さとスタック](../cpp/cpp-environment.md#stack-depth) |
| ACL を使うと手元と結果が違う | ACL の版（v1.5 の `val()` は `unsigned int`） | [ACL の版](../cpp/acl-reading.md#version) |
| 小数の結果が手元と違う（外積の符号・`== 0` の判定） | `-march=native` で FMA が使われ、丸めが変わる | [FMA](../cpp/cpp-environment.md#march-native) |
| 手元では速いのに AtCoder でだけ TLE | 関数の中の大きな配列（AtCoder では呼ぶたびに 0 で埋まる） | [大きな局所配列は遅くなる](../cpp/cpp-environment.md#auto-var-init) |
| 小さいケースは合うが大きいケースで WA、答えが負 | `int` どうしの積、INF + INF | [int どうしの積](../cpp/cpp-integer-overflow.md#int-product)・[INF + INF](../cpp/cpp-integer-overflow.md#edge-values) |
| 空の配列で答えが巨大になる・ループが止まらない | `v.size() - 1` が符号なしで巨大になる | [size() は符号なし](../cpp/cpp-integer-overflow.md#unsigned-size) |
| 負の数の割り算・余りがずれる | 商は 0 に向かって切り捨て、余りは負になりうる | [整数の割り算](../cpp/cpp-math-functions.md#integer-division) |
| 大きな整数の平方根・べき乗がずれる | `sqrt`・`pow` は `double` | [pow・sqrt](../cpp/cpp-math-functions.md#pow-sqrt) |
| ダイクストラ法の距離がおかしい | `pq.top()` を参照で受けて pop した | [pq.top() のダングリング](../cpp/cpp-undefined-behavior.md#dangling-pq-top) |
| push_back の後に値が壊れる | 参照を持ったまま再確保した | [再確保のダングリング](../cpp/cpp-undefined-behavior.md#dangling-reallocation)・[ループの中で追加しない](../cpp/cpp-range-for.md#modify-in-loop) |
| 大きな入力の sort で RE | 比較関数に `<=` | [「以下」の比較関数](../cpp/cpp-comparators.md#less-equal-pitfall) |
| set の要素が減っている | 比較関数が「同じ」とみなした | [set の比較関数と同値](../cpp/cpp-comparators.md#set-equivalence) |
| 手元の `-O0` では `Assertion '__n < this->size()' failed` で止まるが、`-O2`・提出では止まらない | 範囲外の添字（g++-15 は `-O0` で検査が自動で付く） | [配列の範囲外](../cpp/cpp-undefined-behavior.md#out-of-range)・[結果が違うときに疑う順](../cpp/cpp-environment.md#when-results-differ) |
| 配列の範囲外を読んでも止まらない | 既定では範囲を確かめない | [配列の範囲外](../cpp/cpp-undefined-behavior.md#out-of-range)・[見つける道具](../cpp/cpp-undefined-behavior.md#detection-tools) |
| WA の原因の行が分からない | `assert` で RE に変えて気づく | [assert](../cpp/cpp-undefined-behavior.md#assert)・[不具合を探すビルド](../cpp/cpp-undefined-behavior.md#debug-build) |
| 小数の答えが `1.23457e+08` のように出る | 出力の桁 | [小数の出力](../cpp/cpp-io.md#float-output) |
| 出力の順番が入れ替わる | 同期を切った後の `println`・`printf` と `cout` の混在 | [混ぜると入れ替わる](../cpp/cpp-io.md#mixing-streams) |
| インタラクティブで応答が来ない・TLE | 同期を切る 2 行があるときのフラッシュ忘れ | [フラッシュ](../cpp/cpp-io.md#flush) |
| 計算量は合っているのに TLE | `endl`・`std::function`・set に `std::lower_bound`・`s = s + c`・値渡し | [TLE になる書き方](../cpp/cpp-io.md#tle-causes) |

インタラクティブ問題で `'\n'` や `println` の出力が届かないのは、同期を切る 2 行（`cin.tie(nullptr)` と `sync_with_stdio(false)`）を書いたときである。2 行がなければ、`cin` で読む前に `cout` が書き出されるので届く（手元の確認は[フラッシュ](../cpp/cpp-io.md#flush)の表）。雛形に 2 行があるかどうかに関係なく、質問のたびに、`cout` なら `endl`、`println`・`printf` ならその後に `fflush(stdout)` を書けば届く。2 行があるときは、`cout << endl` では `stdout` は書き出されない。

手元と AtCoder で結果が違うときは、未初期化変数 → 未定義動作 → スタック → ACL の版の順に疑う（[疑う順](../cpp/cpp-environment.md#when-results-differ)）。手元で AtCoder と同じ条件にするコンパイルのオプションは [オプションの比較](../cpp/cpp-environment.md#options)にある。

## コンパイルエラーのメッセージから引く（最初の error: の行と、required from here で自分の行を探す読み方を含む） {#compile-errors}

コンパイルエラーは、最初の `error:` の行に原因が書かれている。テンプレートの中で起きたエラーは、その行が標準ライブラリのヘッダの中を指すので、`required from here` の行で自分のコードの行を探す。次のコードは、比べ方のない構造体を `sort` に渡している。

```cpp
--8<-- "cpp-reverse-index/required-from-here-ng.cpp:core"
```

手元の g++-15 では、このエラーが 132 行出た（g++-13 では 79 行）。読むのは次の 2 か所だけである。以下の抜き出しと表の `'` は、ロケール（`LANG`）が UTF-8 なら `‘` `’` と出る。

```text
required-from-here-ng.cpp:14:9:   required from here
   14 |     sort(ps.begin(), ps.end());  // P に比べ方がない
.../bits/predefined_ops.h:45:23: error: no match for 'operator<' (operand types are 'P' and 'P')
```

1. **最初の `error:` の行で、何が起きたかを読む**：`no match for 'operator<' (operand types are 'P' and 'P')` は「`P` どうしを `<` で比べる方法がない」という意味である。場所は `predefined_ops.h` で、自分のファイルではない
2. **`required from here` の行で、自分のどの行が原因かを読む**：`error:` より前にある `required from ...` の行は、標準ライブラリの中の呼び出しの連なりである。その最後の `required from here` が自分のファイル名と行番号（14 行目の `sort`）を指す
3. **その後ろの `note:` は読み飛ばしてよい**：候補になった `operator<` を 1 つずつ挙げて、合わなかった理由を述べている。2 つ目以降の `error:` も、多くは 1 つ目と同じ原因から続いて出たものである

直し方は、`P` に比較演算子を持たせるか（[比較演算子の小なり](../cpp/cpp-comparators.md#operator-less)・[三方比較演算子](../cpp/cpp-comparators.md#spaceship)）、`sort` に比較関数を渡すことである。

よく出るメッセージは次の表で引く。メッセージは g++-13・g++-15 で出た文面の一部である。

| メッセージの一部 | 原因 | ページ |
| --- | --- | --- |
| `'println' was not declared in this scope` | GCC 13 以前（`println` は GCC 14〜） | [format と println](../cpp/cpp-io.md#format-println) |
| `'to' is not a member of 'std::ranges'` | GCC 13 以前（`ranges::to` は GCC 14〜） | [ranges::to](../cpp/cpp-views-cpp23.md#ranges-to) |
| `expected identifier before 'this'` | deducing this を GCC 13 以前で | [deducing this](../cpp/cpp-lambda.md#deducing-this) |
| `'concat' is not a member of 'std::views'` | C++26 の機能（AtCoder でも使えない） | [views::concat](../cpp/cpp-views-cpp23.md#concat) |
| `no match for call to '(const std::ranges::views::_Iota) (int, ...size_type)'` | `views::iota(0, v.size())` | [iota の型の不一致](../cpp/cpp-views-basics.md#iota-size-mismatch) |
| `no matching function for call to 'min(int, long long int&)'`・`'min(int&, long long int&)'` | 型の違う値を `min`・`max` に | [型の違う値を min・max に](../cpp/cpp-integer-overflow.md#min-max-types) |
| `deduced conflicting types for parameter` | 1 つの型引数の `chmin` に `long long` と `int` | [型推論の失敗](../cpp/cpp-templates-constexpr.md#deduction-failure) |
| `constraints not satisfied` | コンセプトの条件を満たさない型を渡した | [コンセプト](../cpp/cpp-templates-constexpr.md#concepts) |
| `'constexpr' loop iteration count exceeds limit of 262144` | コンパイル時に大きな表を作ろうとした | [constexpr](../cpp/cpp-templates-constexpr.md#constexpr) |
| `cannot bind non-const lvalue reference ... to an rvalue` | その場で作られる組や `vector<bool>` の要素を `auto&` で受けた | [要素は参照を含む組](../cpp/cpp-views-cpp23.md#reference-tuples)・[bool の vector](../cpp/cpp-range-for.md#vector-bool) |
| `use of 'f' before deduction of 'auto'` | ラムダが自分の名前を呼んだ、`-> void` がない | [再帰できない理由](../cpp/cpp-lambda.md#recursive-lambda)・[戻り値の型](../cpp/cpp-lambda.md#return-type) |
| `lambda-expression in template-argument only available with '-std=c++20'` | C++17 で ACL にラムダを渡した | [関数の渡し方](../cpp/acl-reading.md#passing-functions) |
| `'<lambda closure object>...' is not a constant expression` | キャプチャのあるラムダを ACL の `op`・`e` に | [キャプチャのあるラムダ](../cpp/acl-reading.md#capturing-lambda) |
| `static assertion failed: mapping must work as S(F, S)` | lazy_segtree の関数の引数の形が違う | [static_assert のエラー](../cpp/acl-reading.md#template-arg-errors) |
| `ambiguous overload for 'operator<<'` | `__int128` を `cout` に | [出力できない型](../cpp/cpp-io.md#unprintable-types) |
| `no match for 'operator<<'` | modint などを `cout` に | [出力できない型](../cpp/cpp-io.md#unprintable-types) |
| `no matching function for call to 'popcount(int&)'` | bit ヘッダの関数に符号付き整数 | [符号なし整数だけ](../cpp/cpp-math-functions.md#bit-unsigned-only) |
| `conversion from 'int' to non-scalar type 'atcoder::dsu' requested` | explicit なコンストラクタを `=` で | [explicit](../cpp/cpp-initialization.md#explicit) |
| `no match for 'operator*' (operand type is 'std::ranges::borrowed_iterator_t<...>')`・`(operand type is 'std::ranges::dangling')` | 一時オブジェクトを ranges のアルゴリズムに | [ranges::dangling](../cpp/cpp-algorithms.md#ranges-dangling) |
| `no match for 'operator-'` | set のイテレータどうしの引き算 | [添字への変換](../cpp/cpp-container-idioms.md#iterator-index) |
| `passing 'const std::map<int, int>' as 'this' argument discards qualifiers` | const の map に `[]` | [map の添字](../cpp/cpp-container-idioms.md#map-subscript) |
| `reference to 'count' is ambiguous`・`'int y1' redeclared` | 名前の衝突 | [名前の衝突](../cpp/cpp-macros-template-file.md#namespaces) |
| `'::main' must return 'int'` | `#define int long long` で `int main()` | [#define int long long](../cpp/cpp-macros-template-file.md#define-int) |
| `'typeof' was not declared in this scope` | `-std=c++23`（厳密モード）で GNU 拡張の `typeof` | [GNU 拡張](../cpp/cpp-environment.md#gnu-mode) |
| `inlining failed in call to 'always_inline' ... target specific option mismatch` | g++-13 で `#pragma GCC target` を include の前に | [#pragma GCC](../cpp/cpp-macros-template-file.md#pragma) |
| `static assertion failed: std::gcd arguments must be integers` | `-std=c++23` で `__int128` を `gcd` に | [-std=c++23 の __int128](../cpp/cpp-integer-overflow.md#int128-strict-mode) |
| `expected primary-expression before 'long'` | `#define ll long long` の `ll(x)` | [型の別名](../cpp/cpp-types-literals.md#type-alias) |
| `designator order for field ... does not match declaration order` | 指示付き初期化の順がメンバの宣言順と違う | [指示付き初期化](../cpp/cpp-initialization.md#designated-init) |
| `the value of 'n' is not usable in a constant expression` | `bitset<n>` の大きさに入力の値 | [bitset](../cpp/cpp-math-functions.md#bitset) |

## 確認問題 {#quiz}

??? question "確認問題 1：`scc.scc() | views::enumerate` を回す範囲 for で、`const auto&` を `auto&` にするとなぜ通らないか"
    `views::enumerate` は、回すたびに（添字, 成分への参照）の組をその場で作って返す。その場で作られた値（一時オブジェクト）は、const のない参照 `auto&` では受けられない。`auto`・`const auto&`・`auto&&` なら受けられる（[要素は参照を含む組](../cpp/cpp-views-cpp23.md#reference-tuples)）。

??? question "確認問題 2：`for (const auto& [i, x] : a | views::enumerate) x = 0;` で、vector の a は変わるか"
    変わる（すべて 0 になる）。const が付くのは組のほうで、組が持つのは `a` の要素への参照 `int&` だからである。const は参照の先には伝わらない（[enumerate の要素は参照を含む組](../cpp/cpp-structured-bindings.md#enumerate-reference)）。

??? question "確認問題 3：上の `i` と `int` の変数 `best` を `max(best, i)` で比べるとどうなるか"
    コンパイルエラーになる。`enumerate` の添字の型は `ptrdiff_t`（64 bit の Linux では `long`）で、`max` は 2 つの引数が同じ型でないと呼べない。`(int)i` と変換するか、`views::zip(views::iota(0), v)` で `int` の添字を作る（[enumerate の添字を int に](../cpp/cpp-views-cpp23.md#int-index)）。

??? question "確認問題 4：100 行を超えるコンパイルエラーで、最初に見る行はどれか"
    最初の `error:` の行で何が起きたかを読み、その前にある `required from here` の行で自分のファイルの行番号を見る。後ろに続く `note:` と 2 つ目以降の `error:` は、多くが同じ原因から出たものである（[コンパイルエラーから引く](#compile-errors)）。

## 参考 {#references}

- [cppreference「Range-based for loop」](https://en.cppreference.com/cpp/language/range-for)：範囲 for の展開と一時オブジェクトの寿命
- [cppreference「Structured binding declaration」](https://en.cppreference.com/cpp/language/structured_binding)：構造化束縛の名前の型（tuple に似た型の要素の型）
- [cppreference「std::ranges::views::enumerate, std::ranges::enumerate_view」](https://en.cppreference.com/cpp/ranges/enumerate_view)：添字の型と要素の組の型
- [AtCoder Library「SCC」（document_ja）](https://github.com/atcoder/ac-library/blob/master/document_ja/scc.md)：`scc()` の戻り値の型と、成分がトポロジカル順に並ぶこと
