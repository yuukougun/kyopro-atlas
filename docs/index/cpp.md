---
title: C++の詳細索引
type: generated
search:
  exclude: true
---

<!-- tools/gen_site.py が生成する。手で直さない -->

# C++の詳細索引

分野の全ページの id・URL・別名・サイン・種類・前提・使い分け・節。全分野の1行の一覧と索引の版は https://yuukougun.github.io/kyopro-atlas/llms.txt にある。

## C++ の逆引き（cpp-reverse-index） {#cpp-reverse-index}

- id：`cpp-reverse-index`　レベル：—　段階：reviewed　type：guide
- URL：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-reverse-index/
- 別名：解説コードの読み方、解説コードが読めない、モダン C++ の読み方、書き方から引く、症状から引く、Segmentation fault、コンパイルエラーの読み方、エラーメッセージ、required from here
- 種類：実装・C++、案内
- 節：
    - `cpp-reverse-index#how-to-read` 1 行の読み方：何を回すか・何を受け取るか・どう受け取るかに分ける：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-reverse-index/#how-to-read
    - `cpp-reverse-index#lookup-types` 書き方から引く：型・リテラル・初期化・数の関数：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-reverse-index/#lookup-types
    - `cpp-reverse-index#lookup-references` 書き方から引く：参照・構造化束縛・組：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-reverse-index/#lookup-references
    - `cpp-reverse-index#lookup-lambda` 書き方から引く：ラムダ・再帰・テンプレート：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-reverse-index/#lookup-lambda
    - `cpp-reverse-index#lookup-macros` 書き方から引く：雛形とマクロ：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-reverse-index/#lookup-macros
    - `cpp-reverse-index#lookup-containers` 書き方から引く：コンテナ・比較関数・アルゴリズム・文字列：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-reverse-index/#lookup-containers
    - `cpp-reverse-index#lookup-views` 書き方から引く：views：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-reverse-index/#lookup-views
    - `cpp-reverse-index#lookup-io` 書き方から引く：入出力：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-reverse-index/#lookup-io
    - `cpp-reverse-index#lookup-acl` 書き方から引く：ACL：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-reverse-index/#lookup-acl
    - `cpp-reverse-index#confusing-pairs` 混同しやすい書き方の対（std::iota と views::iota、unique と erase など）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-reverse-index/#confusing-pairs
    - `cpp-reverse-index#symptoms` 症状から引く：WA・RE・TLE と、手元と AtCoder で結果が違うとき：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-reverse-index/#symptoms
    - `cpp-reverse-index#compile-errors` コンパイルエラーのメッセージから引く（最初の error: の行と、required from here で自分の行を探す読み方を含む）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-reverse-index/#compile-errors

## 数の型とリテラル（cpp-types-literals） {#cpp-types-literals}

- id：`cpp-types-literals`　レベル：基礎　段階：reviewed　type：cpp
- URL：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-types-literals/
- 別名：整数の型、long long、LL、ULL、桁区切り、2 進リテラル、0uz、auto の推論、using ll = long long、static_cast、INF、numeric_limits、LLONG_MAX、INT_MAX、0x3f3f3f3f、1LL << 60、double、long double、1e18、浮動小数点数の型
- 種類：実装・C++
- 使い分け：`method-comparison#numbers`
- 節：
    - `cpp-types-literals#integer-types` 整数の型と表せる範囲（int・long long・unsigned・size_t・int64_t）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-types-literals/#integer-types
    - `cpp-types-literals#literals` リテラルの書き方：1LL・ULL、桁区切り 1'000'000'007、2 進 0b1010、size_t の 0uz（C++23）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-types-literals/#literals
    - `cpp-types-literals#auto-deduction` auto が推論する型：0 は int、0LL は long long、v.size() は size_t、1e18 は double：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-types-literals/#auto-deduction
    - `cpp-types-literals#type-alias` 型の別名：using ll = long long と #define ll long long（ll(x) と書けるか）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-types-literals/#type-alias
    - `cpp-types-literals#cast` キャスト：static_cast と C 形式のキャスト：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-types-literals/#cast
    - `cpp-types-literals#inf` INF の決め方と、INF + INF があふれるか：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-types-literals/#inf
    - `cpp-types-literals#floating-point` 浮動小数点数の型：double が整数を正確に表せるのは 2^53 まで、x86-64 の long double は仮数部 64bit：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-types-literals/#floating-point
    - `cpp-types-literals#double-1e18` 1e18 は double：long long に直す位置で値が変わる、auto INF = 1e18 も double：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-types-literals/#double-1e18
    - `cpp-types-literals#float-compare` 浮動小数点数を == で比べない（誤差を許すか、整数で計算する）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-types-literals/#float-compare
    - `cpp-types-literals#float128` float128_t（stdfloat ヘッダ。C++23・GCC 13〜。解説コードではまれ）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-types-literals/#float128

## 整数のオーバーフローと \_\_int128（cpp-integer-overflow） {#cpp-integer-overflow}

- id：`cpp-integer-overflow`　レベル：基礎　段階：reviewed　type：cpp
- URL：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-integer-overflow/
- 別名：オーバーフロー、integer overflow、あふれ、int の掛け算、1LL \* a \* b、1 << 40、符号なし整数、v.size() - 1、ssize、\_\_int128、i128、128bit 整数、\_\_builtin_mul_overflow
- 種類：実装・C++
- 前提：`cpp-types-literals`
- サイン：
    - 制約：A_i ≤ 10^9 を N ≤ 2×10^5 個足す、または 2 つ掛ける（int に収まらない）
- 節：
    - `cpp-integer-overflow#int-product` int どうしの積は int で計算される（1LL \* a \* b と書く）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-integer-overflow/#int-product
    - `cpp-integer-overflow#shift-width` シフトの幅：int の 1 を 40 ずらすと警告が出て 0 になる、1LL をずらす：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-integer-overflow/#shift-width
    - `cpp-integer-overflow#inferred-int` 初期値と推論の型：accumulate(..., 0)・auto x = 0・views::iota(0, n) の i は int：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-integer-overflow/#inferred-int
    - `cpp-integer-overflow#unsigned-size` size() は符号なし：空の v で v.size() - 1 が巨大になる、ssize(v) か (int)v.size()：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-integer-overflow/#unsigned-size
    - `cpp-integer-overflow#min-max-types` 型の違う値を min・max に渡すとコンパイルエラー（1LL にそろえるか型を明示する）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-integer-overflow/#min-max-types
    - `cpp-integer-overflow#edge-values` INF + INF・abs(INT_MIN)・INT_MIN / -1：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-integer-overflow/#edge-values
    - `cpp-integer-overflow#signed-overflow-ub` 符号付き整数のあふれは未定義動作：-O2 では正しく書いた比較の結果まで変わる：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-integer-overflow/#signed-overflow-ub
    - `cpp-integer-overflow#int128` \_\_int128：10^18 程度どうしの積を正確に持つ（GCC の拡張）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-integer-overflow/#int128
    - `cpp-integer-overflow#int128-io` \_\_int128 の入出力：cin・cout では扱えない、format・println か自作の変換で出す：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-integer-overflow/#int128-io
    - `cpp-integer-overflow#int128-strict-mode` -std=c++23 では \_\_int128 が整数型と判定されず gcd・abs に渡せない：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-integer-overflow/#int128-strict-mode
    - `cpp-integer-overflow#overflow-check` 積が上限を超えるかの判定：割り算で比べる・\_\_builtin_mul_overflow：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-integer-overflow/#overflow-check

## 初期化と CTAD（cpp-initialization） {#cpp-initialization}

- id：`cpp-initialization`　レベル：基礎　段階：reviewed　type：cpp
- URL：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-initialization/
- 別名：初期化、多次元 vector、多次元配列、vector の初期化、array&lt;int, 26> cnt{\}、値初期化、memset、fill、assign、指示付き初期化、集成体、explicit、クラステンプレートの実引数推論、class template argument deduction、vector dp(n, vector(m, 0LL))
- 種類：実装・C++
- 前提：`cpp-types-literals`
- 節：
    - `cpp-initialization#vector-init` vector の初期化：(n) は 0 が n 個、(n, x) は x が n 個、波括弧の n は値 n が 1 個：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-initialization/#vector-init
    - `cpp-initialization#multi-dim-vector` 多次元 vector：入れ子の vector で作り、3 次元は 1 段深くする：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-initialization/#multi-dim-vector
    - `cpp-initialization#array-init` array を空の波括弧で 0 初期化：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-initialization/#array-init
    - `cpp-initialization#global-vs-local` グローバル変数は 0 で初期化され、関数の中の変数・配列は初期化されない：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-initialization/#global-vs-local
    - `cpp-initialization#designated-init` 構造体のメンバの既定値と指示付き初期化（C++20。宣言順に書く）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-initialization/#designated-init
    - `cpp-initialization#aggregate-emplace` コンストラクタのない構造体（集成体）にも emplace_back(to, cost) が使える（C++20。C++17 ではエラー）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-initialization/#aggregate-emplace
    - `cpp-initialization#explicit` explicit なコンストラクタは = で初期化できない（ACL の dsu d = 5 はエラーで、dsu d(5) と書く）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-initialization/#explicit
    - `cpp-initialization#refill` 埋め直し：memset はバイト単位、fill・assign・ranges::fill：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-initialization/#refill
    - `cpp-initialization#ctad` CTAD：vector dp(n, vector(m, 0LL)) で型を内側から決める（0 と書くと int になる）（C++17）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-initialization/#ctad
    - `cpp-initialization#ctad-std-types` pair・tuple・array・priority_queue の CTAD（C++17）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-initialization/#ctad-std-types
    - `cpp-initialization#ctad-pitfall` CTAD の罠：波括弧にイテレータ 2 個を渡すとイテレータの vector になる（C++17）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-initialization/#ctad-pitfall

## 数・ビット・乱数の関数（cpp-math-functions） {#cpp-math-functions}

- id：`cpp-math-functions`　レベル：基礎　段階：reviewed　type：cpp
- URL：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-math-functions/
- 別名：gcd、lcm、midpoint、clamp、割り算の切り捨ての向き、pow、sqrt、sqrtl、numbers::pi、std::popcount、countr_zero、bit_width、\_\_builtin_popcount、\_\_builtin_ctz、\_\_lg、std::bitset、\_Find_first、mt19937_64、uniform_int_distribution、shuffle、chrono、乱数、時間計測
- 種類：実装・C++、ビット演算
- 前提：`cpp-types-literals`
- 節：
    - `cpp-math-functions#gcd-lcm` gcd・lcm：型を混ぜられる、負の数は絶対値で計算、lcm は戻り値の型であふれる（C++17。\_\_gcd は GCC の古い関数）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-math-functions/#gcd-lcm
    - `cpp-math-functions#midpoint-clamp` midpoint（C++20）・clamp（C++17）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-math-functions/#midpoint-clamp
    - `cpp-math-functions#integer-division` 整数の / と % は 0 に向かって切り捨てる（-7 / 2 は -3、-7 % 2 は -1）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-math-functions/#integer-division
    - `cpp-math-functions#pow-sqrt` pow・sqrt は double で計算する：整数のべき乗や大きな long long の平方根に使わない：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-math-functions/#pow-sqrt
    - `cpp-math-functions#pi` 円周率：numbers::pi（C++20）・M_PI・acos(-1)：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-math-functions/#pi
    - `cpp-math-functions#bit-functions` bit ヘッダの関数：popcount・countr_zero・bit_width など（C++20）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-math-functions/#bit-functions
    - `cpp-math-functions#bit-unsigned-only` std::popcount などは符号なし整数しか受けない（C++20）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-math-functions/#bit-unsigned-only
    - `cpp-math-functions#builtins` 組み込み関数：\_\_builtin_popcount・\_\_builtin_ctz・\_\_builtin_clzll・\_\_lg（GCC の拡張）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-math-functions/#builtins
    - `cpp-math-functions#bit-tricks` ビットの小技：x & -x（最下位の 1）・x & (x - 1)・部分集合を大きい順に回す for（考え方は bit 演算のページ）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-math-functions/#bit-tricks
    - `cpp-math-functions#bitset` bitset：大きさはコンパイル時の定数、count・シフト・\_Find_first・\_Find_next：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-math-functions/#bitset
    - `cpp-math-functions#random` 乱数：mt19937_64・uniform_int_distribution・shuffle（rand() は使わない）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-math-functions/#random
    - `cpp-math-functions#chrono` 時間計測：chrono::steady_clock::now()：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-math-functions/#chrono

## 参照と範囲 for（cpp-range-for） {#cpp-range-for}

- id：`cpp-range-for`　レベル：基礎　段階：reviewed　type：cpp
- URL：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-range-for/
- 別名：参照、参照渡し、const 参照、値渡し、コピー、ムーブ、std::move、std::swap、範囲 for、range-based for、auto&&、const auto&、for (auto& x : v)、vector&lt;bool>
- 種類：実装・C++
- 節：
    - `cpp-range-for#reference-basics` 参照 T& と const 参照 const T&：別名を付けてコピーしない：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-range-for/#reference-basics
    - `cpp-range-for#pass-by-reference` 関数の引数：値渡しは呼ぶたびにコピー（再帰では O(N) × 呼び出し回数）、大きなものは const& で渡す：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-range-for/#pass-by-reference
    - `cpp-range-for#move-swap` ムーブと swap：swap(dp, ndp) は中身を入れ替えるだけで O(1)、dp = ndp は長さに比例するコピー：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-range-for/#move-swap
    - `cpp-range-for#forwarding-reference` auto&&：何でも受けられる参照：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-range-for/#forwarding-reference
    - `cpp-range-for#range-for-forms` 範囲 for の 4 通りの受け方：コピーが起きるか・元を書き換えられるか：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-range-for/#range-for-forms
    - `cpp-range-for#vector-bool` bool の vector の要素はプロキシ：auto& で回すとエラー、auto で受けても元が書き換わる：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-range-for/#vector-bool
    - `cpp-range-for#range-for-init` 範囲 for の初期化式 for (int i = 0; auto x : v)（C++20。i の更新は自分で書く）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-range-for/#range-for-init
    - `cpp-range-for#modify-in-loop` ループの中で同じ vector に追加しない（再確保で壊れる）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-range-for/#modify-in-loop
    - `cpp-range-for#temporary-range` 範囲に一時オブジェクトの中身を渡すとき（C++23・GCC 15〜でだけ安全な形）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-range-for/#temporary-range

## 構造化束縛と pair・tuple・optional（cpp-structured-bindings） {#cpp-structured-bindings}

- id：`cpp-structured-bindings`　レベル：基礎　段階：reviewed　type：cpp
- URL：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-structured-bindings/
- 別名：構造化束縛、structured binding、auto [a, b]、分解宣言、pair、tuple、tie、get<0>、make_pair、optional、nullopt、value_or、exchange、初期化式付き if
- 種類：実装・C++
- 前提：`cpp-range-for`
- 節：
    - `cpp-structured-bindings#pair-tuple` pair と tuple：get・make_pair・波括弧での作成、辞書順で比べられる：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-structured-bindings/#pair-tuple
    - `cpp-structured-bindings#structured-binding` 構造化束縛の形：pair・構造体・配列・array を名前に分ける、map の範囲 for（C++17）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-structured-bindings/#structured-binding
    - `cpp-structured-bindings#hidden-variable` 見えない変数：auto はコピー、auto& は参照。名前はメンバの宣言順に付き、数が合わないとエラー（C++17）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-structured-bindings/#hidden-variable
    - `cpp-structured-bindings#map-loop` map を回すとき：キーは const、値を参照で受けて書き換えると map が変わる（C++17）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-structured-bindings/#map-loop
    - `cpp-structured-bindings#if-init` 初期化式付き if・switch：find や insert の結果をその場で受けて調べる（C++17）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-structured-bindings/#if-init
    - `cpp-structured-bindings#pq-top-reference` pq.top() を参照で受けて pop すると値が変わる（ダイクストラ法で起きる。値で受ける）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-structured-bindings/#pq-top-reference
    - `cpp-structured-bindings#enumerate-reference` views::enumerate・zip の要素は参照を含む組：構造化束縛でも元の要素を指す：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-structured-bindings/#enumerate-reference
    - `cpp-structured-bindings#capture-and-placeholder` 構造化束縛した名前のキャプチャ（C++20）と、使わない名前 \_：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-structured-bindings/#capture-and-placeholder
    - `cpp-structured-bindings#tie` tie：既存の変数にまとめて代入・比較する（std::ignore）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-structured-bindings/#tie
    - `cpp-structured-bindings#tie-swap-pitfall` tie(a, b) = tie(b, a) は入れ替えにならない（swap か pair で渡す）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-structured-bindings/#tie-swap-pitfall
    - `cpp-structured-bindings#exchange` 代入の小技：exchange で代入して前の値を返す、tie と pair でまとめて更新する：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-structured-bindings/#exchange
    - `cpp-structured-bindings#optional` optional：値がないことを表す（nullopt・has_value・value_or。C++17）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-structured-bindings/#optional
    - `cpp-structured-bindings#apply` apply と、同じ型の組としての array（apply は C++17）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-structured-bindings/#apply

## ラムダ式と再帰ラムダ（cpp-lambda） {#cpp-lambda}

- id：`cpp-lambda`　レベル：基礎　段階：reviewed　type：cpp
- URL：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-lambda/
- 別名：ラムダ、lambda、無名関数、クロージャ、キャプチャ、[&]、[=]、ジェネリックラムダ、再帰ラムダ、std::function、auto&& self、this auto&& self、deducing this、不動点コンビネータ、FixPoint
- 種類：実装・C++
- 前提：`cpp-range-for`
- 節：
    - `cpp-lambda#capture` キャプチャ：参照・コピー・初期化キャプチャ・mutable と、参照で取り込んだときの寿命：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-lambda/#capture
    - `cpp-lambda#generic-lambda` auto 引数のジェネリックラムダ、テンプレート構文（C++20）、static ラムダ（C++23・GCC 13〜）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-lambda/#generic-lambda
    - `cpp-lambda#immediately-invoked` その場で呼ぶラムダ：複雑な初期化をした値を const にする：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-lambda/#immediately-invoked
    - `cpp-lambda#pass-to-function` 関数に渡す：sort の比較関数・二分探索の判定関数：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-lambda/#pass-to-function
    - `cpp-lambda#decltype-type` 型だけを書く：decltype でラムダの型を set・priority_queue に渡す（C++20）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-lambda/#decltype-type
    - `cpp-lambda#template-argument` テンプレート引数にキャプチャのないラムダを渡す（GCC で通る。ACL の segtree）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-lambda/#template-argument
    - `cpp-lambda#recursive-lambda` ラムダがそのままでは再帰できない理由（use of ‘f’ before deduction of ‘auto’）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-lambda/#recursive-lambda
    - `cpp-lambda#std-function` std::function による再帰：読みやすいが、型消去を通る間接呼び出しになり遅い：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-lambda/#std-function
    - `cpp-lambda#self-argument` 自分を引数で渡す再帰：self(self, to) と書き、dfs(dfs, 0) と呼ぶ：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-lambda/#self-argument
    - `cpp-lambda#deducing-this` deducing this：this auto&& self で受ける再帰ラムダ（C++23・GCC 14〜）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-lambda/#deducing-this
    - `cpp-lambda#fixpoint` 不動点コンビネータ（雛形の FixPoint・MFP）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-lambda/#fixpoint
    - `cpp-lambda#return-type` 戻り値の型を後置で書く場面（再帰より前に型の決まる return がないとき）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-lambda/#return-type
    - `cpp-lambda#speed` 速さの比較：std::function は fib(40) で約 5 倍、木の DFS で約 1.5 倍遅い：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-lambda/#speed

## 関数テンプレートと constexpr（cpp-templates-constexpr） {#cpp-templates-constexpr}

- id：`cpp-templates-constexpr`　レベル：基礎　段階：reviewed　type：cpp
- URL：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-templates-constexpr/
- 別名：テンプレート、template、関数テンプレート、template &lt;class T>、型推論、auto 引数、コンセプト、concepts、requires、static_assert、if constexpr、畳み込み式、fold expression、属性、[[maybe_unused]]
- 種類：実装・C++
- 節：
    - `cpp-templates-constexpr#two-meanings` 「テンプレート」の 2 つの意味：C++ の template と、競プロのコードの雛形：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-templates-constexpr/#two-meanings
    - `cpp-templates-constexpr#function-template` 関数テンプレート：型を引数に取る関数を 1 つ書く：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-templates-constexpr/#function-template
    - `cpp-templates-constexpr#deduction-failure` 型推論の失敗：chmin(a, 3)（a が long long）が通らない理由と、2 つの型引数を取る形：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-templates-constexpr/#deduction-failure
    - `cpp-templates-constexpr#explicit-type` 型を明示して呼ぶ（max に long long を指定する）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-templates-constexpr/#explicit-type
    - `cpp-templates-constexpr#abbreviated-template` auto 引数の省略形 auto sq(auto x)（C++20）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-templates-constexpr/#abbreviated-template
    - `cpp-templates-constexpr#concepts` コンセプトと requires：型の条件を書く（C++20）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-templates-constexpr/#concepts
    - `cpp-templates-constexpr#constexpr` constexpr の定数と関数、コンパイル時に表を作る：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-templates-constexpr/#constexpr
    - `cpp-templates-constexpr#static-assert` static_assert と if constexpr（if constexpr は C++17）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-templates-constexpr/#static-assert
    - `cpp-templates-constexpr#fold-expression` 畳み込み式で可変長引数を展開する：デバッグ出力の例（C++17）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-templates-constexpr/#fold-expression
    - `cpp-templates-constexpr#attributes` 属性：maybe_unused・nodiscard（C++17）、likely（C++20）、assume（C++23・GCC 13〜）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-templates-constexpr/#attributes

## マクロと雛形（cpp-macros-template-file） {#cpp-macros-template-file}

- id：`cpp-macros-template-file`　レベル：基礎　段階：reviewed　type：cpp
- URL：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-macros-template-file/
- 別名：マクロ、macro、テンプレート（雛形）、rep マクロ、all マクロ、\#define int long long、signed main()、chmin、chmax、\#ifdef LOCAL、\#pragma GCC optimize、bits/stdc++.h、using namespace std、import std;、名前の衝突、バンドル、ライブラリの展開、expander.py、提出用にコピー
- 種類：実装・C++
- 前提：`cpp-templates-constexpr`
- 節：
    - `cpp-macros-template-file#bits-stdcpp` bits/stdc++.h の取り込みと using namespace std：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-macros-template-file/#bits-stdcpp
    - `cpp-macros-template-file#namespaces` 名前の衝突：count・y1 をグローバル変数の名前にするとエラー：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-macros-template-file/#namespaces
    - `cpp-macros-template-file#import-std` import std;：#include の代わりに標準ライブラリを読む（C++23・GCC 15〜）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-macros-template-file/#import-std
    - `cpp-macros-template-file#macros` マクロは文字の置き換え：rep・all・vc/vvc と、引数の数で切り替える FOR：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-macros-template-file/#macros
    - `cpp-macros-template-file#define-int` \#define int long long と signed main()（printf・scanf の書式とも食い違う）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-macros-template-file/#define-int
    - `cpp-macros-template-file#chmin` chmin・chmax：2 つの型を取る形とカンマ演算子で書く形：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-macros-template-file/#chmin
    - `cpp-macros-template-file#ifdef-local` \#ifdef LOCAL・#ifndef ONLINE_JUDGE：手元だけのデバッグ出力を切り替える：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-macros-template-file/#ifdef-local
    - `cpp-macros-template-file#pragma` \#pragma GCC optimize・target：AtCoder では target は要らない：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-macros-template-file/#pragma
    - `cpp-macros-template-file#bundling` 自作のヘッダを #include "..." したコードは、提出前に 1 ファイルに展開する（バンドル）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-macros-template-file/#bundling
    - `cpp-macros-template-file#bundling-tools` 展開の道具：cph の提出用のコピー・ACL の expander.py・oj-bundle：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-macros-template-file/#bundling-tools
    - `cpp-macros-template-file#impl-marker` // @impl で main の後ろに回せるもの・回せないもの：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-macros-template-file/#impl-marker

## コンテナ操作とイテレータ（cpp-container-idioms） {#cpp-container-idioms}

- id：`cpp-container-idioms`　レベル：基礎　段階：reviewed　type：cpp
- URL：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-container-idioms/
- 別名：erase_if、contains、emplace_back、map の []、multiset の削除、ms.erase(ms.find(x))、イテレータ、iterator、std::prev、std::next、rbegin、it - v.begin()、イテレータの無効化、unordered_map のハッシュ、pb_ds、order_of_key、find_by_order
- 種類：実装・C++、データ構造
- 使い分け：`method-comparison#containers`
- 節：
    - `cpp-container-idioms#erase-if` erase(v, x)・erase_if(v, pred)：消した個数を返す。erase_if は set・map にも使える（C++20）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-container-idioms/#erase-if
    - `cpp-container-idioms#contains` contains（C++20）と find・count：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-container-idioms/#contains
    - `cpp-container-idioms#map-subscript` map の添字演算子はキーがなければ要素を作る（存在を調べるなら contains・find）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-container-idioms/#map-subscript
    - `cpp-container-idioms#multiset-erase-one` multiset から 1 個だけ消す：ms.erase(ms.find(x))（erase(x) は全部消す）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-container-idioms/#multiset-erase-one
    - `cpp-container-idioms#emplace-back` emplace_back と push_back：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-container-idioms/#emplace-back
    - `cpp-container-idioms#member-lower-bound` set・map の lower_bound はメンバ関数を使う（std::lower_bound は O(N)）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-container-idioms/#member-lower-bound
    - `cpp-container-idioms#iterators` イテレータの基本：begin は先頭、end は最後の要素の次（prev・next・rbegin）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-container-idioms/#iterators
    - `cpp-container-idioms#iterator-index` it - v.begin() で添字（vector だけ）、distance は set では O(N)：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-container-idioms/#iterator-index
    - `cpp-container-idioms#erase-returns-next` erase は次のイテレータを返す（it = st.erase(it)）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-container-idioms/#erase-returns-next
    - `cpp-container-idioms#invalidation` イテレータと参照の無効化：vector の再確保はすべてを無効にし、set・map は消した要素だけ：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-container-idioms/#invalidation
    - `cpp-container-idioms#unordered-map` unordered_map：pair のキーにはハッシュがない、自作のハッシュ、衝突を狙った入力：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-container-idioms/#unordered-map
    - `cpp-container-idioms#pb-ds` pb_ds の順序付き集合：tree と order_of_key・find_by_order（GCC の拡張）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-container-idioms/#pb-ds

## 比較関数と順序（cpp-comparators） {#cpp-comparators}

- id：`cpp-comparators`　レベル：基礎　段階：reviewed　type：cpp
- URL：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-comparators/
- 別名：comparator、greater<>、greater{\}、priority_queue の向き、最小ヒープ、厳密弱順序、strict weak ordering、operator&lt;、三方比較演算子、宇宙船演算子、<=>、= default、構造体のソート、複数キーのソート
- 種類：実装・C++、ソート・座標圧縮
- 前提：`cpp-lambda`
- 節：
    - `cpp-comparators#strict-weak-ordering` 比較関数の約束：a が b より前なら true を返し、狭義の弱順序を満たす（a と a を比べたら false）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-comparators/#strict-weak-ordering
    - `cpp-comparators#less-equal-pitfall` 比較関数に「以下」を書くと sort が壊れる（同じ値が多いと Segmentation fault）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-comparators/#less-equal-pitfall
    - `cpp-comparators#greater` 降順：greater の 3 つの書き方（型を書く・型を省く・CTAD）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-comparators/#greater
    - `cpp-comparators#priority-queue-order` priority_queue の向き：既定は最大が先頭、greater で最小が先頭：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-comparators/#priority-queue-order
    - `cpp-comparators#set-equivalence` set・map の比較関数は「同じ」も決める（second だけで比べると、second の等しい要素が 1 個しか残らない）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-comparators/#set-equivalence
    - `cpp-comparators#multiple-keys` 複数のキーで比べる：pair・tuple の辞書順と tie：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-comparators/#multiple-keys
    - `cpp-comparators#lambda-comparator-type` ラムダの比較関数を型として渡す：decltype（C++20。C++17 では pq(cmp) と渡す）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-comparators/#lambda-comparator-type
    - `cpp-comparators#operator-less` 構造体に比較演算子の小なりを持たせる（メンバ関数に const が要る）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-comparators/#operator-less
    - `cpp-comparators#spaceship` 三方比較演算子の default で 6 つの比較を宣言順の辞書順にする（C++20）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-comparators/#spaceship

## アルゴリズム関数と ranges 版（cpp-algorithms） {#cpp-algorithms}

- id：`cpp-algorithms`　レベル：基礎　段階：reviewed　type：cpp
- URL：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-algorithms/
- 別名：algorithm、sort、unique、std::lower_bound、std::upper_bound、accumulate、reduce、partial_sum、std::iota、std::next_permutation、max_element、max({a, b, c})、ranges::sort、射影、projection、ranges::unique、ranges::fold_left、ranges::contains
- 種類：実装・C++、ソート・座標圧縮
- 前提：`cpp-container-idioms`、`cpp-lambda`
- 節：
    - `cpp-algorithms#sort` sort と降順（greater・rbegin/rend）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-algorithms/#sort
    - `cpp-algorithms#unique-erase` 重複の削除：sort → unique → erase（unique は前に詰めて新しい終端を返すだけ）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-algorithms/#unique-erase
    - `cpp-algorithms#lower-bound` 二分探索：lower_bound・upper_bound・equal_range・binary_search：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-algorithms/#lower-bound
    - `cpp-algorithms#accumulate` 総和：accumulate は初期値の型で足す（0LL・0.0）、reduce は初期値を省くと要素の型で足す：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-algorithms/#accumulate
    - `cpp-algorithms#partial-sum` 累積和と差分：partial_sum・inclusive_scan・adjacent_difference：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-algorithms/#partial-sum
    - `cpp-algorithms#iota` 連番：std::iota で埋める（views::iota・ranges::iota との違い）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-algorithms/#iota
    - `cpp-algorithms#next-permutation` next_permutation で順列を列挙する（ソートした状態から始める）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-algorithms/#next-permutation
    - `cpp-algorithms#max-element` 最大・最小・個数：max_element・max・clamp・count の戻り値：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-algorithms/#max-element
    - `cpp-algorithms#ranges` ranges 版：ranges::sort(v) のようにコンテナを直接渡す（C++20）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-algorithms/#ranges
    - `cpp-algorithms#projection` 射影：メンバのポインタを渡して score で比べ、要素ごと並べ替える（C++20）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-algorithms/#projection
    - `cpp-algorithms#ranges-unique` ranges::unique は後ろの不要部分を返す（C++20）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-algorithms/#ranges-unique
    - `cpp-algorithms#fold-left` fold_left・contains・find_last（C++23・GCC 13〜）と AtCoder にない starts_with：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-algorithms/#fold-left
    - `cpp-algorithms#ranges-dangling` 一時オブジェクトを渡すと戻り値が ranges::dangling になる（使うとコンパイルエラー）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-algorithms/#ranges-dangling

## 文字列の操作（cpp-string-api） {#cpp-string-api}

- id：`cpp-string-api`　レベル：基礎　段階：reviewed　type：cpp
- URL：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-string-api/
- 別名：string、substr、string::find、npos、to_string、stoi、stoll、starts_with、ends_with、string_view、s += c、getline、c - 'a'、文字と数の変換
- 種類：実装・C++
- 節：
    - `cpp-string-api#substr-find` substr(i, len) は O(len) のコピー、find は見つからないと string::npos：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-string-api/#substr-find
    - `cpp-string-api#append` s += c と s = s + c（後者は毎回全体をコピーして O(|s|)。先頭に足すなら後ろに足して最後に reverse）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-string-api/#append
    - `cpp-string-api#char-arithmetic` 文字と数の変換：c - 'a'・char('a' + i)・c - '0'：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-string-api/#char-arithmetic
    - `cpp-string-api#to-string` to_string（double は小数点以下 6 桁）・stoi・stoll：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-string-api/#to-string
    - `cpp-string-api#starts-with` starts_with・ends_with（C++20）、contains（C++23）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-string-api/#starts-with
    - `cpp-string-api#construct-compare` string(n, c)・reverse・辞書順の比較：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-string-api/#construct-compare
    - `cpp-string-api#string-view` string_view：コピーしない部分文字列。一時的な string を入れると壊れる（C++17）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-string-api/#string-view
    - `cpp-string-api#split` 区切る：views::split(' ') と string_view(w)（C++20）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-string-api/#split
    - `cpp-string-api#getline` cin で読む文字列は空白で区切られる、その後の getline は残った改行を読む：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-string-api/#getline

## ACL の読み方（acl-reading） {#acl-reading}

- id：`acl-reading`　レベル：基礎　段階：reviewed　type：cpp
- URL：https://yuukougun.github.io/kyopro-atlas/cpp/acl-reading/
- 別名：AtCoder Library、ACL、atcoder/all、using namespace atcoder、val()、segtree&lt;S, op, e>、lazy_segtree のテンプレート引数、テンプレート引数、ラムダをテンプレート引数に
- 種類：実装・C++
- 前提：`cpp-templates-constexpr`、`cpp-lambda`
- ACL：`static_modint`、`modint`、`segtree`、`lazy_segtree`、`dsu`
- 節：
    - `acl-reading#conventions` include と共通の約束：0-indexed・半開区間・引数なしで作った物・assert：https://yuukougun.github.io/kyopro-atlas/cpp/acl-reading/#conventions
    - `acl-reading#explicit` コンストラクタは modint 以外 explicit：dsu d(n) と書く（dsu d = n はエラー）：https://yuukougun.github.io/kyopro-atlas/cpp/acl-reading/#explicit
    - `acl-reading#version` 版：AtCoder は v1.6、v1.5 との違いは modint::val() の型など：https://yuukougun.github.io/kyopro-atlas/cpp/acl-reading/#version
    - `acl-reading#components` 部品の呼び出し方の一覧（意味は各手法のページ）：https://yuukougun.github.io/kyopro-atlas/cpp/acl-reading/#components
    - `acl-reading#dsu-groups` dsu の groups()：戻り値の要素を範囲 for で直接回すのは C++23・GCC 15〜でだけ安全：https://yuukougun.github.io/kyopro-atlas/cpp/acl-reading/#dsu-groups
    - `acl-reading#modint` modint の読み方：using mint = modint998244353; で法が自動で取られる：https://yuukougun.github.io/kyopro-atlas/cpp/acl-reading/#modint
    - `acl-reading#modint-val` modint の値と出力：.val() を出す、v1.6 で val() は int、大小比較はない：https://yuukougun.github.io/kyopro-atlas/cpp/acl-reading/#modint-val
    - `acl-reading#segtree-args` segtree のテンプレート引数の読み方：S は要素の型、op は結合的な演算、e は単位元（水）：https://yuukougun.github.io/kyopro-atlas/cpp/acl-reading/#segtree-args
    - `acl-reading#passing-functions` 関数の渡し方：関数の名前か、キャプチャのないラムダ（C++20）（水）：https://yuukougun.github.io/kyopro-atlas/cpp/acl-reading/#passing-functions
    - `acl-reading#capturing-lambda` キャプチャのあるラムダは op・e に渡せない（max_right・min_left の判定関数には渡せる）（水）：https://yuukougun.github.io/kyopro-atlas/cpp/acl-reading/#capturing-lambda
    - `acl-reading#lazy-segtree-args` lazy_segtree の 7 つの引数：composition(f, g) は g の後に f（水）：https://yuukougun.github.io/kyopro-atlas/cpp/acl-reading/#lazy-segtree-args
    - `acl-reading#template-arg-errors` テンプレート引数の形が合わないときの static_assert（mapping must work as S(F, S) など）（水）：https://yuukougun.github.io/kyopro-atlas/cpp/acl-reading/#template-arg-errors

## views の基本（cpp-views-basics） {#cpp-views-basics}

- id：`cpp-views-basics`　レベル：基礎　段階：reviewed　type：cpp
- URL：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-views-basics/
- 別名：views、ビュー、Range アダプタ、range adaptor、パイプ、遅延評価、views::iota、views::reverse、views::filter、views::transform、views::take、views::keys、views::split、views::join、views::common
- 種類：実装・C++
- 前提：`cpp-lambda`
- 節：
    - `cpp-views-basics#what-is-view` view とは：元の範囲を見る方法だけを持ち、取り出すときに計算する：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-views-basics/#what-is-view
    - `cpp-views-basics#iota` views::iota(a, b)・views::iota(a)：普通の for と同じ速さ：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-views-basics/#iota
    - `cpp-views-basics#iota-size-mismatch` views::iota(0, v.size()) がコンパイルエラーになる理由と直し方：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-views-basics/#iota-size-mismatch
    - `cpp-views-basics#iota-int` views::iota(0, n) は n が long long でも i が int になる：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-views-basics/#iota-int
    - `cpp-views-basics#reverse` views::reverse は逆順に見るだけ：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-views-basics/#reverse
    - `cpp-views-basics#filter-transform` filter と transform：transform の後に filter を置くと関数が 2 回呼ばれる：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-views-basics/#filter-transform
    - `cpp-views-basics#take-drop` take・drop・take_while・drop_while：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-views-basics/#take-drop
    - `cpp-views-basics#keys-values` keys・values・elements：map のキーだけを回す：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-views-basics/#keys-values
    - `cpp-views-basics#split-join` split と join：文字列を区切る、vector の vector を平らにする：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-views-basics/#split-join
    - `cpp-views-basics#common` common：イテレータの組を取る古いコンストラクタに渡すとき：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-views-basics/#common
    - `cpp-views-basics#lifetime` view の寿命：元のコンテナより長く使わない：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-views-basics/#lifetime

## C++23 の views と ranges::to（cpp-views-cpp23） {#cpp-views-cpp23}

- id：`cpp-views-cpp23`　レベル：基礎　段階：reviewed　type：cpp
- URL：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-views-cpp23/
- 別名：views::enumerate、views::zip、views::zip_transform、views::pairwise、views::adjacent、views::chunk、views::slide、views::chunk_by、views::stride、views::cartesian_product、views::repeat、views::join_with、ranges::to、to&lt;vector>、from_range、append_range
- 種類：実装・C++
- 前提：`cpp-views-basics`、`cpp-structured-bindings`
- 節：
    - `cpp-views-cpp23#enumerate` views::enumerate：（添字, 要素への参照）の組を作る、添字は ptrdiff_t（C++23・GCC 13〜）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-views-cpp23/#enumerate
    - `cpp-views-cpp23#zip` views::zip・zip_transform：同じ位置の要素の組、短いほうに合わせる（C++23・GCC 13〜）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-views-cpp23/#zip
    - `cpp-views-cpp23#adjacent` pairwise・adjacent・pairwise_transform：隣り合う組と差分（C++23・GCC 13〜）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-views-cpp23/#adjacent
    - `cpp-views-cpp23#chunk-slide-stride` chunk・slide・stride：k 個ずつの塊・長さ k の窓・k 個おき（C++23・GCC 13〜）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-views-cpp23/#chunk-slide-stride
    - `cpp-views-cpp23#chunk-by` chunk_by：隣どうしで条件が成り立つ間をまとめる（C++23・GCC 13〜）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-views-cpp23/#chunk-by
    - `cpp-views-cpp23#cartesian-product` cartesian_product：二重ループ・グリッドの全マスを 1 つのループにする（C++23・GCC 13〜）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-views-cpp23/#cartesian-product
    - `cpp-views-cpp23#repeat-join-with` repeat・join_with・as_const（C++23・GCC 13〜）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-views-cpp23/#repeat-join-with
    - `cpp-views-cpp23#reference-tuples` 要素は参照を含む組：構造化束縛でも元の要素を指す（C++23・GCC 13〜）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-views-cpp23/#reference-tuples
    - `cpp-views-cpp23#int-index` enumerate の添字を int にしたいとき：zip と iota で作る（C++23・GCC 13〜）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-views-cpp23/#int-index
    - `cpp-views-cpp23#ranges-to` ranges::to でコンテナに変換する（入れ子も。C++23・GCC 14〜）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-views-cpp23/#ranges-to
    - `cpp-views-cpp23#from-range` from_range・insert_range・append_range（C++23・GCC 15〜）と GCC 13 での代わり：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-views-cpp23/#from-range
    - `cpp-views-cpp23#concat` views::concat（C++26）は AtCoder では使えない：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-views-cpp23/#concat

## 入出力と定数倍（cpp-io） {#cpp-io}

- id：`cpp-io`　レベル：基礎　段階：reviewed　type：cpp
- URL：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-io/
- 別名：入出力、fast I/O、cin.tie(nullptr)、sync_with_stdio、endl、println、std::print、std::format、printf、setprecision、fixed、小数の出力、fflush(stdout)、TLE になる書き方、入出力が遅い
- 種類：実装・C++、計算量
- サイン：
    - 制約：入力や出力が 10^6 個程度ある（入出力の書き方で実行時間に差が出る）
    - 言い回し：答えの絶対誤差または相対誤差が 10^-6 以下なら正解とする（小数の桁を指定して出力しないと WA になる）
- 節：
    - `cpp-io#fast-io` 入出力の高速化：sync_with_stdio(false) と cin.tie(nullptr)：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-io/#fast-io
    - `cpp-io#endl` endl は改行のたびに書き出す（10^6 行で約 0.2 秒余計にかかる）、普段は改行文字 '\\n' を出す：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-io/#endl
    - `cpp-io#separators` 区切りと改行の書き方：最後だけ改行する書き方と Yes・No の出し分け：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-io/#separators
    - `cpp-io#read-until-eof` 入力の終わりまで読む：読み込みの成否を while の条件にする：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-io/#read-until-eof
    - `cpp-io#printf` printf・scanf と書式：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-io/#printf
    - `cpp-io#format-println` std::format（C++20・GCC 13〜）と std::print・println（C++23・GCC 14〜）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-io/#format-println
    - `cpp-io#format-spec` 書式の指定：幅・左寄せ・0 埋め・2 進・16 進・小数の桁（C++20・GCC 13〜）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-io/#format-spec
    - `cpp-io#float-output` 小数の出力：cout の既定は有効数字 6 桁、fixed と setprecision・printf で桁を指定する：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-io/#float-output
    - `cpp-io#mixing-streams` 同期を切った後に println・printf と cout を混ぜると順番が入れ替わる：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-io/#mixing-streams
    - `cpp-io#flush` インタラクティブ問題のフラッシュ：同期を切る 2 行を書いたら、質問のたびに endl か fflush(stdout) が要る：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-io/#flush
    - `cpp-io#unprintable-types` そのままでは出力できない型：\_\_int128・modint・vector：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-io/#unprintable-types
    - `cpp-io#tle-causes` C++ 側で TLE になる書き方の一覧と計測：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-io/#tle-causes

## AtCoder と手元の C++ 環境（cpp-environment） {#cpp-environment}

- id：`cpp-environment`　レベル：—　段階：reviewed　type：cpp
- URL：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-environment/
- 別名：AtCoder の C++、コンパイルオプション、GCC 15.2、-std=gnu++23、-std=c++23、-ftrivial-auto-var-init=zero、言語アップデート、C++ の版、版の対応表、スタックオーバーフロー、ulimit -s、深い再帰、手元と結果が違う
- 種類：実装・C++
- サイン：
    - 制約：N ≤ 2×10^5 の木やグラフを再帰でたどる（一直線の入力では深さが N になり、手元の 8 MiB のスタックでは落ちることがある）
- 節：
    - `cpp-environment#options` AtCoder と手元のオプションの比較と、同じ条件で試すコマンド：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-environment/#options
    - `cpp-environment#gnu-mode` -std=gnu++23 と -std=c++23 の違い：GNU 拡張と \_\_int128 の型特性：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-environment/#gnu-mode
    - `cpp-environment#auto-var-init` -ftrivial-auto-var-init=zero：未初期化の局所変数が 0 になり、大きな局所配列は遅くなる：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-environment/#auto-var-init
    - `cpp-environment#march-native` -march=native：pragma の target は要らないが、FMA で小数の結果が変わりうる：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-environment/#march-native
    - `cpp-environment#judge-macros` -DATCODER・-DONLINE_JUDGE：ジャッジでだけ定義されるマクロ：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-environment/#judge-macros
    - `cpp-environment#acl-version` ACL の版：AtCoder は v1.6（modint の val() が int）。手元も v1.6 にそろえる：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-environment/#acl-version
    - `cpp-environment#stack-depth` 再帰の深さとスタック：手元の上限・ulimit -s unlimited・非再帰への書き直し：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-environment/#stack-depth
    - `cpp-environment#pch` プリコンパイル済みヘッダ：作ったときと同じオプションのときだけ使われる（-Winvalid-pch で理由が出る）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-environment/#pch
    - `cpp-environment#gcc-or-clang` Clang 版（libc++）ではなく GCC 版を選ぶ：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-environment/#gcc-or-clang
    - `cpp-environment#when-results-differ` 手元と AtCoder で結果が違うときに疑う順（未初期化変数 → 未定義動作 → スタック → ACL の版）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-environment/#when-results-differ
    - `cpp-environment#version-matrix` C++ の版と GCC の対応表（g++-13 と AtCoder の GCC 15.2）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-environment/#version-matrix
    - `cpp-environment#gcc13-limits` GCC 13 で通らない書き方（GCC 14〜・GCC 15〜の C++23 の機能）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-environment/#gcc13-limits
    - `cpp-environment#not-on-atcoder` AtCoder で使えないもの：C++26 の機能と GCC 16 からの機能：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-environment/#not-on-atcoder

## 未定義動作とダングリング（cpp-undefined-behavior） {#cpp-undefined-behavior}

- id：`cpp-undefined-behavior`　レベル：基礎　段階：reviewed　type：cpp
- URL：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-undefined-behavior/
- 別名：未定義動作、UB、undefined behavior、範囲外アクセス、未初期化変数、初期化忘れ、ゴミの値、ダングリング、dangling reference、use-after-free、参照の無効化、一時オブジェクトの寿命、pq.top() の参照、\_GLIBCXX_DEBUG、\_GLIBCXX_ASSERTIONS、-fsanitize=address、AddressSanitizer、UndefinedBehaviorSanitizer、デバッグ用ビルド、assert
- 種類：実装・C++
- 前提：`cpp-environment`、`cpp-integer-overflow`、`cpp-structured-bindings`
- 節：
    - `cpp-undefined-behavior#what-is-ub` 未定義動作とは：何が起きてもよく、最適化の前提に使われる（手元と AtCoder、-O0 と -O2 で結果が変わる）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-undefined-behavior/#what-is-ub
    - `cpp-undefined-behavior#breaks-other-lines` 他の行まで壊す：あふれる式があると、-O2 では正しく書いた別の式の値まで変わる：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-undefined-behavior/#breaks-other-lines
    - `cpp-undefined-behavior#out-of-range` 配列の範囲外：既定では止まらない：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-undefined-behavior/#out-of-range
    - `cpp-undefined-behavior#uninitialized` 未初期化変数：手元では不定、AtCoder では 0 になる（-Wall は配列の未初期化を見落とす）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-undefined-behavior/#uninitialized
    - `cpp-undefined-behavior#dangling` ダングリングとは：寿命の切れたものを指す参照・イテレータ・string_view：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-undefined-behavior/#dangling
    - `cpp-undefined-behavior#dangling-pq-top` ダングリング①：pq.top() を参照で受けて pop すると値が変わる（値で受ける）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-undefined-behavior/#dangling-pq-top
    - `cpp-undefined-behavior#dangling-reallocation` ダングリング②：要素への参照を持ったまま push_back すると、再確保で消えた領域を指す：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-undefined-behavior/#dangling-reallocation
    - `cpp-undefined-behavior#dangling-temporary` ダングリング③：範囲 for の一時オブジェクト（変数に受けてから回す）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-undefined-behavior/#dangling-temporary
    - `cpp-undefined-behavior#dangling-string-view` ダングリング④：string_view に一時的な string を入れる：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-undefined-behavior/#dangling-string-view
    - `cpp-undefined-behavior#other-ub` そのほかの未定義動作：比較関数の誤り・型の幅以上のシフト・\_\_builtin_ctz(0)・ループ中のコンテナの変更：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-undefined-behavior/#other-ub
    - `cpp-undefined-behavior#detection-tools` 見つける道具と見つけられるもの：警告・アサーション・デバッグモード・サニタイザ：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-undefined-behavior/#detection-tools
    - `cpp-undefined-behavior#debug-build` 不具合を探すビルドを cph とは別に用意する：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-undefined-behavior/#debug-build
    - `cpp-undefined-behavior#assert` assert で WA を RE に変えて気づく（AtCoder では NDEBUG が付かない）：https://yuukougun.github.io/kyopro-atlas/cpp/cpp-undefined-behavior/#assert
