---
id: cpp-templates-constexpr
title: 関数テンプレートと constexpr
aliases: [テンプレート, template, 関数テンプレート, template <class T>, 型推論, auto 引数, コンセプト, concepts, requires, static_assert, if constexpr, 畳み込み式, fold expression, 属性, '[[maybe_unused]]']
type: cpp
field: cpp
chapter: 参照・ラムダ・テンプレート
order: 90
level: 基礎
kind: [実装・C++]
prerequisites: []
related: [cpp-macros-template-file, cpp-lambda, acl-reading, library-design, cpp-reverse-index#compile-errors]
summary: 型を引数にした関数（テンプレート・auto 引数・コンセプト）と、コンパイル時に値を決める constexpr・static_assert を読み書きする。chmin(a, 3) が通らないような型推論の失敗を避ける。
complexity: '実行時の速さは型ごとに手で書いた関数と同じ。constexpr の計算はコンパイル時に行い、GCC では 1 つのループが 262144 回まで'
signs: []
acl: []
sections:
  - {title: 「テンプレート」の 2 つの意味：C++ の template と、競プロのコードの雛形, anchor: two-meanings}
  - {title: 関数テンプレート：型を引数に取る関数を 1 つ書く, anchor: function-template}
  - {title: '型推論の失敗：chmin(a, 3)（a が long long）が通らない理由と、2 つの型引数を取る形', anchor: deduction-failure}
  - {title: 型を明示して呼ぶ（max に long long を指定する）, anchor: explicit-type}
  - {title: auto 引数の省略形 auto sq(auto x)（C++20）, anchor: abbreviated-template}
  - {title: コンセプトと requires：型の条件を書く（C++20）, anchor: concepts}
  - {title: constexpr の定数と関数、コンパイル時に表を作る, anchor: constexpr}
  - {title: static_assert と if constexpr（if constexpr は C++17）, anchor: static-assert}
  - {title: 畳み込み式で可変長引数を展開する：デバッグ出力の例（C++17）, anchor: fold-expression}
  - {title: 属性：maybe_unused・nodiscard（C++17）、likely（C++20）、assume（C++23・GCC 13〜）, anchor: attributes}
stage: reviewed
updated: 2026-10-22
cpp_std: 20
gcc_min: 13
atcoder: true
---

!!! abstract "要点"
    - **何ができるか**：型を引数にした関数（テンプレート・auto 引数・コンセプト）を書き、`long long` と `double` で同じ関数を使う。`constexpr` と `static_assert` で、定数や表をコンパイル時に作って確かめる。`chmin(a, 3)` が通らないような型推論の失敗の理由と直し方も分かる。
    - **いつ使うか**：解説コードや雛形に `template <class T>`・`auto f(auto x)`・`constexpr`・`[[nodiscard]]` が出てきて読みたいとき。`no matching function for call to 'chmin(long long int&, int)'` のエラーが出たとき。
    - **計算量**：実行時の速さは、型ごとに手で書いた関数と同じ。`constexpr` の計算はコンパイル時に行うが、GCC では 1 つのループが 262144 回までで、大きな表は作れない
    - **前提**：なし

<!-- textlint-disable -->
別名：テンプレート・template・関数テンプレート・template <class T>・型推論・auto 引数・コンセプト・concepts・requires・static_assert・if constexpr・畳み込み式・fold expression・属性・[[maybe_unused]]
<!-- textlint-enable -->

関数テンプレートは、型を引数にして「どの型でも同じ手順」の関数を 1 つだけ書く C++ の仕組みである。呼んだときの引数の型から型引数が決まり（型推論）、型ごとに別の関数がコンパイラによって作られる。`constexpr` は、値をコンパイルの時点で決める指定である。どちらも競プロでは、`chmin`・`power` などの補助関数や、`MOD`・10 の累乗の表などの定数として、灰色の解説から現れる。

このページのコードは `#include <bits/stdc++.h>` と `using namespace std;` を前提にする。版は、手元の g++-13・g++-15 の `-std=gnu++23` で確かめた（AtCoder は GCC 15.2・`-std=gnu++23`）。

## 「テンプレート」の 2 つの意味：C++ の template と、競プロのコードの雛形 {#two-meanings}

競プロで「テンプレート」と言うと、2 つの別のものを指す。

- **C++ の `template`**：型を引数にした関数やクラスを作る言語の機能。このページで扱う
- **コードの雛形**：毎回の提出の先頭に貼る `#include`・マクロ（`rep` など）・補助関数（`chmin` など）のまとまり。「テンプレートを用意する」と言うときはこちらである。[マクロと雛形](../cpp/cpp-macros-template-file.md)で扱う

雛形の中の `chmin` は、たいてい C++ の `template` で書かれている。そのため、雛形を読むには C++ の `template` の読み方が要る。エラーの文に `template argument deduction/substitution failed` とあれば、C++ の `template` の話である。

## 関数テンプレート：型を引数に取る関数を 1 つ書く {#function-template}

`template <class T>` の後に書いた関数では、`T` を型の名前として使える。次の `power` は、`a` の `n` 乗を繰り返し二乗法で求める。`T` は `long long` でも `double` でも、`*=` と `1` からの初期化ができる型なら何でもよい（ACL の [modint](../cpp/acl-reading.md) も入る）。`class T` は `typename T` と書いても同じ意味である。

```cpp
--8<-- "cpp-templates-constexpr/power.cpp:core"
```

完全なプログラム：[`power.cpp`](https://github.com/yuukougun/kyopro-atlas/blob/main/snippets/cpp-templates-constexpr/power.cpp)（GitHub）
{ .kp-code-src }

呼ぶときに型を書く必要はない。1 つ目の引数の型から `T` が決まる。

```cpp
--8<-- "cpp-templates-constexpr/power.cpp:call"
```

完全なプログラム：[`power.cpp`](https://github.com/yuukougun/kyopro-atlas/blob/main/snippets/cpp-templates-constexpr/power.cpp)（GitHub）
{ .kp-code-src }

素朴に書くと、`long long power(long long a, long long n)` と `double power(double a, long long n)` を 2 つ書くのと同じである。コンパイラは呼ばれた型ごとに別の関数を作る（インスタンス化）ので、実行時の速さは手で書いた関数と変わらない。

- **版**：C++98 からある。g++-13・g++-15 で使える
- **落とし穴**：`T` は引数の型そのもので決まる。`power(2, 40)` は `2` が `int` なので `T = int` になり、計算の途中であふれる（[整数オーバーフロー](../cpp/cpp-integer-overflow.md)）。上のコードの `static_assert` で、戻り値の型が `int` であることを確かめた。`power(2LL, 40)` と、リテラルに `LL` を付けて型を決める（[型とリテラル](../cpp/cpp-types-literals.md)）

## 型推論の失敗：chmin(a, 3)（a が long long）が通らない理由と、2 つの型引数を取る形 {#deduction-failure}

型引数が 1 つの `chmin` に、`long long` の変数と `int` のリテラルを渡すと、コンパイルエラーになる。

```cpp
--8<-- "cpp-templates-constexpr/chmin-ng.cpp:core"
```

完全なプログラム：[`chmin-ng.cpp`](https://github.com/yuukougun/kyopro-atlas/blob/main/snippets/cpp-templates-constexpr/chmin-ng.cpp)（GitHub）
{ .kp-code-src }

g++-15 のエラーは次のとおりで、g++-13 も同じだった。

```text
error: no matching function for call to 'chmin(long long int&, int)'
note:   deduced conflicting types for parameter 'const T' ('long long int' and 'int')
```

理由は、型推論が引数ごとに別々に行われることである。1 つ目の引数 `a` からは `T = long long`、2 つ目の `3` からは `T = int` が導かれ、2 つが食い違う（conflicting）。普通の関数 `bool chmin(long long& a, long long b)` なら `3` は `long long` に直されて通るが、型推論の段階では、こうした型の変換を考えない。

直し方は 2 つある。1 つは、型引数を 2 つにして、`a` と `b` に別々の型を許す形である。maspy 氏の雛形もこの形（`template <class T, class S>`）である。

```cpp
--8<-- "cpp-templates-constexpr/chmin-ok.cpp:core"
```

```cpp
--8<-- "cpp-templates-constexpr/chmin-ok.cpp:call"
```

完全なプログラム：[`chmin-ok.cpp`](https://github.com/yuukougun/kyopro-atlas/blob/main/snippets/cpp-templates-constexpr/chmin-ok.cpp)（GitHub）
{ .kp-code-src }

もう 1 つは、2 つ目の引数を `type_identity_t<T>`（C++20）で包み、そこからは推論させない形である。`T` は `a` だけから決まり、`b` はその型に直される。

```cpp
--8<-- "cpp-templates-constexpr/chmin-ok.cpp:identity"
```

完全なプログラム：[`chmin-ok.cpp`](https://github.com/yuukougun/kyopro-atlas/blob/main/snippets/cpp-templates-constexpr/chmin-ok.cpp)（GitHub）
{ .kp-code-src }

- **版**：`type_identity_t` は C++20。それ以外は C++98 から。g++-13・g++-15 で使える
- **落とし穴**：2 つの型引数を取る形では、`a = b` で `b` が `a` の型に黙って直される。`int` の変数 `a` へ、`int` の範囲を超える `long long` を入れると、上位のビットが落ちる。手元では、`-Wall -Wextra` でも警告が出なかった（`-Wconversion` を付けると出た）。`chmin` に渡す変数は、入れうる値の入る型にしておく

```cpp
--8<-- "cpp-templates-constexpr/chmin-narrow.cpp:core"
```

完全なプログラム：[`chmin-narrow.cpp`](https://github.com/yuukougun/kyopro-atlas/blob/main/snippets/cpp-templates-constexpr/chmin-narrow.cpp)（GitHub）
{ .kp-code-src }

## 型を明示して呼ぶ（max に long long を指定する） {#explicit-type}

標準ライブラリの `max` と `min` も、2 つの引数が同じ型 `T` の関数テンプレートである。そのため `chmin` と同じく、`long long` と `int` を混ぜると、`deduced conflicting types` でコンパイルエラーになる。

```cpp
--8<-- "cpp-templates-constexpr/max-ng.cpp:core"
```

完全なプログラム：[`max-ng.cpp`](https://github.com/yuukougun/kyopro-atlas/blob/main/snippets/cpp-templates-constexpr/max-ng.cpp)（GitHub）
{ .kp-code-src }

関数名の後に `<型>` を書くと、型推論をせずにその型を使う。`T` が決まっているので、`int` の引数はその型に直されて通る。

```cpp
--8<-- "cpp-templates-constexpr/max-ok.cpp:core"
```

完全なプログラム：[`max-ok.cpp`](https://github.com/yuukougun/kyopro-atlas/blob/main/snippets/cpp-templates-constexpr/max-ok.cpp)（GitHub）
{ .kp-code-src }

- **版**：C++98 から。3 個以上を `{}` で渡す `min({…})` は C++11。g++-13・g++-15 で使える
- **落とし穴**：`min({a, 3, b})` のように `{}` で渡すときも、中身の型をそろえる。`a` が `long long` なら `3LL` と書く
- **使い分け**：変数の型を変えられるなら、最初から `long long` にそろえるほうが読みやすい。`max<long long>` は、`.size()` の結果（`size_t`）や `int` の配列の値と混ぜるときに使う

## auto 引数の省略形 auto sq(auto x)（C++20） {#abbreviated-template}

引数の型に `auto` を書くと、`template` の行を省いた関数テンプレートになる。`auto sq(auto x)` は `template <class T> auto sq(T x)` と同じ意味である。`auto` を 2 つ書くと、それぞれが別の型引数になる。

```cpp
--8<-- "cpp-templates-constexpr/abbrev.cpp:core"
```

```cpp
--8<-- "cpp-templates-constexpr/abbrev.cpp:call"
```

完全なプログラム：[`abbrev.cpp`](https://github.com/yuukougun/kyopro-atlas/blob/main/snippets/cpp-templates-constexpr/abbrev.cpp)（GitHub）
{ .kp-code-src }

`add(x, 1)` が通るのは、`a` と `b` の型が別々に決まるからである。[型推論の失敗](#deduction-failure)の 2 つの型引数を取る形と同じことが、短く書ける。戻り値の型の `auto` は、`return` の式から決まる（`add(1, 2.5)` は `double`）。ラムダ式の `[](auto x) { … }`（C++14）も、同じ考え方で型ごとに作られる（[ラムダ式](../cpp/cpp-lambda.md)）。

- **版**：C++20。g++-13・g++-15 で使える。`-std=gnu++17` でも GCC は通す。ただし `use of 'auto' in parameter declaration only available with '-std=c++20' or '-fconcepts'` という警告が出る。これは GNU の拡張で、`-std=c++17 -pedantic-errors` ではエラーになる
- **落とし穴**：`auto` を書いた引数どうしの型をそろえたいとき（`a` と `b` を同じ型にしたいとき）は、`template <class T>` の形で書く

## コンセプトと requires：型の条件を書く（C++20） {#concepts}

コンセプトは、型引数に付ける条件である。`template <integral T>` と書くと、`T` は整数型（`int`・`long long`・`char` など）に限られる。`requires integral<T>` と書いても同じで、`integral auto x` のように `auto` 引数にも付けられる。ライブラリのコードで、整数だけを受け取る関数によく使われる。

```cpp
--8<-- "cpp-templates-constexpr/concepts.cpp:core"
```

完全なプログラム：[`concepts.cpp`](https://github.com/yuukougun/kyopro-atlas/blob/main/snippets/cpp-templates-constexpr/concepts.cpp)（GitHub）
{ .kp-code-src }

条件を満たさない型で呼ぶと、関数の中身を調べる前の段階でコンパイルエラーになる。

```cpp
--8<-- "cpp-templates-constexpr/concepts-ng.cpp:core"
```

完全なプログラム：[`concepts-ng.cpp`](https://github.com/yuukougun/kyopro-atlas/blob/main/snippets/cpp-templates-constexpr/concepts-ng.cpp)（GitHub）
{ .kp-code-src }

エラーは `no matching function for call to 'floor_div(double, double)'` の後に `constraints not satisfied` と出る（g++-13・g++-15 で同じ）。エラーは呼んだ行に出て、どの条件を満たさないかが示される。条件がないと、エラーは関数の中の `%` を使った行に出る。この短い例なら読めるが、ライブラリの関数なら深いところの行になり、どこで誤った型を渡したかが分かりにくい。

- **版**：C++20。`integral`・`floating_point`・`same_as` などのコンセプトは `<concepts>` にある。g++-13・g++-15 で使える
- **読み方**：解説コードでは、自分で書くより読むことが多い。`template <integral T>` は「`T` は整数型」、`requires` の後ろは「この条件を満たす型だけ」と読めば足りる

## constexpr の定数と関数、コンパイル時に表を作る {#constexpr}

`constexpr` を付けた変数は、コンパイル時に値が決まる定数になる。配列の大きさや、テンプレートの引数に使える。`constexpr` を付けた関数は、定数式が要る場所（`constexpr` の変数の初期化や `static_assert`）で呼べばコンパイル時に計算され、実行時の値で呼べば普通の関数として動く。普通の式の中で呼んだとき、コンパイル時に計算するかはコンパイラが決める。必ずコンパイル時に計算したい値は、`constexpr` の変数に入れる。

表を作るときは、ラムダ式を書いてその場で呼ぶ（最後の `()`）。ラムダの中でループを回して `array` を埋め、返した `array` が定数になる。

```cpp
--8<-- "cpp-templates-constexpr/constexpr.cpp:core"
```

完全なプログラム：[`constexpr.cpp`](https://github.com/yuukougun/kyopro-atlas/blob/main/snippets/cpp-templates-constexpr/constexpr.cpp)（GitHub）
{ .kp-code-src }

`TEN` はラムダ式ではなく、ラムダが返した `array<long long, 19>` である。`static_assert` で値を確かめているので、表を作る式を書き間違えるとコンパイルが通らない。

- **版**：C++11 から。ループや変数の書き換えを含む `constexpr` 関数は C++14、ラムダ式の `constexpr` は C++17。g++-13・g++-15 で使える
- **落とし穴 1**：`constexpr vector<int> v = {1, 2, 3};` はコンパイルエラーになる。g++-13・g++-15 とも `is not a constant expression because it refers to a result of 'operator new'` と出る。`vector` は確保したメモリを定数として残せないので、`constexpr` の表は `array` で作る

```cpp
--8<-- "cpp-templates-constexpr/constexpr-vector-ng.cpp:core"
```

完全なプログラム：[`constexpr-vector-ng.cpp`](https://github.com/yuukougun/kyopro-atlas/blob/main/snippets/cpp-templates-constexpr/constexpr-vector-ng.cpp)（GitHub）
{ .kp-code-src }

- **落とし穴 2**：大きな表はコンパイル時に作れない。GCC は、定数式の中の 1 つのループを 262144 回（$2^{18}$）まで、計算の手数を 33554432 回（$2^{25}$）までに制限している。$10^6$ までの篩をコンパイル時に作ろうとすると、`'constexpr' loop iteration count exceeds limit of 262144` で止まる（g++-13・g++-15 で同じ）。制限の内側でも遅く、手元では $2 \times 10^5$ までの篩のコンパイルに g++-15 で約 10 秒、g++-13 で約 14 秒かかった。$10^5$ を超える表は、`main` の中で実行時に作る

```cpp
--8<-- "cpp-templates-constexpr/constexpr-limit-ng.cpp:core"
```

完全なプログラム：[`constexpr-limit-ng.cpp`](https://github.com/yuukougun/kyopro-atlas/blob/main/snippets/cpp-templates-constexpr/constexpr-limit-ng.cpp)（GitHub）
{ .kp-code-src }

## static_assert と if constexpr（if constexpr は C++17） {#static-assert}

`static_assert(条件, "メッセージ")` は、条件をコンパイル時に確かめ、偽ならコンパイルエラーにする。前提にしている型の大きさや、`constexpr` で作った表の値を確かめるのに使う。メッセージは省ける（C++17）。

```cpp
--8<-- "cpp-templates-constexpr/if-constexpr.cpp:assert"
```

完全なプログラム：[`if-constexpr.cpp`](https://github.com/yuukougun/kyopro-atlas/blob/main/snippets/cpp-templates-constexpr/if-constexpr.cpp)（GitHub）
{ .kp-code-src }

`if constexpr (条件)` は、条件をコンパイル時に判定する。関数テンプレートを型ごとに作るとき、選ばれなかった側の枝は作らない。関数テンプレートの中で、型によって書き方を変えるときに使う。次の `print` は、数なら 1 つ出し、それ以外なら範囲として要素を並べる。

```cpp
--8<-- "cpp-templates-constexpr/if-constexpr.cpp:core"
```

完全なプログラム：[`if-constexpr.cpp`](https://github.com/yuukougun/kyopro-atlas/blob/main/snippets/cpp-templates-constexpr/if-constexpr.cpp)（GitHub）
{ .kp-code-src }

普通の `if` にすると、`print(3)` でコンパイルエラーになる。普通の `if` は実行時に枝を選ぶので、`T = int` のときも両方の枝がコンパイルされ、`int` を範囲 for で回す行が通らないからである。エラーは g++-13・g++-15 とも `'begin' was not declared in this scope` と出る。

```cpp
--8<-- "cpp-templates-constexpr/if-plain-ng.cpp:core"
```

完全なプログラム：[`if-plain-ng.cpp`](https://github.com/yuukougun/kyopro-atlas/blob/main/snippets/cpp-templates-constexpr/if-plain-ng.cpp)（GitHub）
{ .kp-code-src }

- **版**：`static_assert` は C++11、メッセージの省略と `if constexpr` は C++17。g++-13・g++-15 で使える
- **落とし穴**：`if constexpr` で捨てた枝がコンパイルされないのは、関数テンプレートの中で、枝の中身が型引数（`T` や `x`）に依存しているときだけである。テンプレートでない普通の関数の中や、`T` に関係しない誤り（たとえば `int y` を範囲 for で回す行）は、捨てた枝でもエラーになる

## 畳み込み式で可変長引数を展開する：デバッグ出力の例（C++17） {#fold-expression}

`template <class... Ts>` と書くと、型引数をいくつでも取る関数テンプレート（可変長テンプレート）になる。`xs` は引数のまとまり（パラメータパック）で、畳み込み式でまとめて展開する。デバッグ出力の `debug(n, m, s)` は、雛形によく入っている使い方である。

```cpp
--8<-- "cpp-templates-constexpr/fold.cpp:core"
```

完全なプログラム：[`fold.cpp`](https://github.com/yuukougun/kyopro-atlas/blob/main/snippets/cpp-templates-constexpr/fold.cpp)（GitHub）
{ .kp-code-src }

`((cerr << xs << ' '), ...)` は、`xs` の各要素について `(cerr << x << ' ')` を作り、カンマ演算子でつないだ式に展開される。`debug(n, m, s)` なら `(cerr << n << ' '), (cerr << m << ' '), (cerr << s << ' ')` となり、左から順に出る。引数が 0 個でも通る（カンマの畳み込みは空なら何もしない）。

足し算などの演算子でも畳み込める。`(xs + ... + 0)` は全部の和で、最後の `0` は引数が 0 個のときの値である。

```cpp
--8<-- "cpp-templates-constexpr/fold.cpp:sum"
```

完全なプログラム：[`fold.cpp`](https://github.com/yuukougun/kyopro-atlas/blob/main/snippets/cpp-templates-constexpr/fold.cpp)（GitHub）
{ .kp-code-src }

- **版**：可変長テンプレートは C++11、畳み込み式は C++17。g++-13・g++-15 で使える
- **落とし穴 1**：`(cout << ... << xs)` と書くと、区切りなしで続けて出る。`1, 23, "ab"` が `123ab` になり、数の切れ目が分からない。区切りを入れるならカンマの畳み込みを使う

```cpp
--8<-- "cpp-templates-constexpr/fold-nosep.cpp:core"
```

完全なプログラム：[`fold-nosep.cpp`](https://github.com/yuukougun/kyopro-atlas/blob/main/snippets/cpp-templates-constexpr/fold-nosep.cpp)（GitHub）
{ .kp-code-src }

- **落とし穴 2**：`cerr` への出力は、AtCoder では採点されないが、時間はかかる。ループの中で何万回も呼ぶと TLE の原因になる。提出前に消すか、`#ifdef LOCAL` で手元だけ有効にする（[マクロと雛形](../cpp/cpp-macros-template-file.md)）

## 属性：maybe_unused・nodiscard（C++17）、likely（C++20）、assume（C++23・GCC 13〜） {#attributes}

属性は `[[…]]` の形でコンパイラに伝える注記で、プログラムの意味は（`assume` を除き）変えない。競プロのコードで見るのは次の 4 つである。

- `[[maybe_unused]]`：使わない変数や引数に付けると、`-Wall` の `unused variable` の警告が出なくなる。デバッグ用の変数に付ける
- `[[nodiscard]]`：関数に付けると、戻り値を捨てたときに警告が出る。`g = gcd_ll(g, a)` を `gcd_ll(g, a)` と書き忘れる誤りを見つけられる
- `[[likely]]`・`[[unlikely]]`：`if` の枝が起きやすいか・起きにくいかの目安。速さへの効果は小さく、読めれば足りる
- `[[assume(式)]]`：式が真だと仮定して最適化してよい、という約束。式が偽になると[未定義動作](../cpp/cpp-undefined-behavior.md)になる

```cpp
--8<-- "cpp-templates-constexpr/attributes.cpp:core"
```

```cpp
--8<-- "cpp-templates-constexpr/attributes.cpp:body"
```

完全なプログラム：[`attributes.cpp`](https://github.com/yuukougun/kyopro-atlas/blob/main/snippets/cpp-templates-constexpr/attributes.cpp)（GitHub）
{ .kp-code-src }

`[[assume(g >= 0)]]` は、入力の値が 0 以上だから書ける。負の値があると `gcd_ll` は負の数を返しうる（`%` の結果は割られる数の符号になる）ので、前提が本当に成り立つときだけ書く。

`[[nodiscard]]` の関数の戻り値を捨てると、g++-13・g++-15 とも `-Wall` なしで次の警告が出た。

```cpp
--8<-- "cpp-templates-constexpr/nodiscard-warn.cpp:core"
```

完全なプログラム：[`nodiscard-warn.cpp`](https://github.com/yuukougun/kyopro-atlas/blob/main/snippets/cpp-templates-constexpr/nodiscard-warn.cpp)（GitHub）
{ .kp-code-src }

```text
warning: ignoring return value of 'long long int gcd_ll(long long int, long long int)', declared with attribute 'nodiscard' [-Wunused-result]
```

- **版**：`[[maybe_unused]]`・`[[nodiscard]]` は C++17、`[[likely]]`・`[[unlikely]]` は C++20、`[[assume]]` は C++23 で GCC 13 から。手元の g++-13・g++-15 では、4 つとも `-std=c++17 -pedantic` でも警告なしで通った。ただし規格の版にない属性の扱いはコンパイラ次第なので、AtCoder と同じ `-std=gnu++23` で使う
- **落とし穴**：`[[assume]]` は確かめる仕組みではなく、偽なら何が起きるか決まっていない。確かめたいなら `assert` を使う（`-DNDEBUG` を付けなければ実行時に検査される）

## 確認問題 {#quiz}

??? question "確認問題：型引数が 1 つの `chmin` に `long long a` と `3` を渡すと、なぜコンパイルエラーになるか？ どう直すか？"
    `template <class T> bool chmin(T& a, const T& b)` の場合である。型推論が引数ごとに別々に行われ、`a` から `T = long long`、`3` から `T = int` が導かれて食い違うからである。型推論では `int` から `long long` への変換を考えない。直し方は、`template <class T, class U> bool chmin(T& a, const U& b)` と型引数を 2 つにするか、呼ぶ側で `chmin(a, 3LL)` と型をそろえる。2 つ目の引数を `const type_identity_t<T>& b` にして、`a` だけから `T` を決めてもよい。

??? question "確認問題：`auto sq(auto x) { return x * x; }` で `sq(100000)` の値は正しいか？"
    正しくない。`100000` は `int` なので、`x` と戻り値の型は `int` になり、$10^{10}$ は `int` に入らずあふれる。`sq(100000LL)` と呼ぶか、`long long sq(long long x)` と型を決めた関数にする。

??? question "確認問題：$10^6$ までの素数の表を `constexpr` で作ろうとしてコンパイルエラーになった。どう直すか？"
    `main` の中で、実行時に普通のループで作る。GCC は定数式の中の 1 つのループを 262144 回までに制限しているので、$10^6$ 回のループは回せない。実行時に作れば $O(N \log \log N)$ で、一瞬で終わる。

## 参考 {#references}

- [cppreference「Template argument deduction」](https://en.cppreference.com/cpp/language/template_argument_deduction)：引数ごとに推論し、食い違うと失敗すること
- [cppreference「std::type_identity」](https://en.cppreference.com/cpp/types/type_identity)：推論させない引数の作り方
- [cppreference「Fold expressions」](https://en.cppreference.com/cpp/language/fold)：畳み込み式の 4 つの形と、空のパックの扱い
- [cppreference「C++ attribute: assume」](https://en.cppreference.com/cpp/language/attributes/assume)：式が偽のときは未定義動作になること
- [cpprefjp「constexpr」](https://cpprefjp.github.io/lang/cpp11/constexpr.html)：`constexpr` の定数と関数
- [cpprefjp「if文のconstexpr」](https://cpprefjp.github.io/lang/cpp17/if_constexpr.html)：選ばれなかった枝を捨てる条件
- [GCC「Options Controlling C++ Dialect」](https://gcc.gnu.org/onlinedocs/gcc/C_002b_002b-Dialect-Options.html)：`-fconstexpr-loop-limit`（既定 262144）と `-fconstexpr-ops-limit`（既定 33554432）
- [maspy「library/my_template.hpp」](https://github.com/maspypy/library/blob/main/my_template.hpp)：2 つの型引数を取る `chmin`・`chmax`
