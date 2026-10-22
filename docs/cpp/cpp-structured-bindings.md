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
related: [cpp-views-cpp23, cpp-comparators, cpp-undefined-behavior, cpp-lambda, dijkstra, cpp-container-idioms]
summary: pair・tuple・構造体の中身に名前を付けて取り出し（構造化束縛）、tie・optional で組や「値がない」を表す。pq.top() を参照で受けてから pop するような、受け方の誤りを防ぐ。
complexity: '構造化束縛・tie・exchange・optional の操作は O(1)。auto で受けると右辺を丸ごとコピーするので、vector などを持つ組ではその大きさに比例する'
signs: []
acl: []
sections:
  - {title: pair と tuple：get・make_pair・波括弧での作成、辞書順で比べられる, anchor: pair-tuple}
  - {title: 構造化束縛の形：pair・構造体・配列・array を名前に分ける、map の範囲 for（C++17）, anchor: structured-binding}
  - {title: 見えない変数：auto はコピー、auto& は参照。名前はメンバの宣言順に付き、数が合わないとエラー（C++17）, anchor: hidden-variable}
  - {title: map を回すとき：キーは const、値を参照で受けて書き換えると map が変わる（C++17）, anchor: map-loop}
  - {title: 初期化式付き if・switch：find や insert の結果をその場で受けて調べる（C++17）, anchor: if-init}
  - {title: pq.top() を参照で受けて pop すると値が変わる（ダイクストラで起きる。値で受ける）, anchor: pq-top-reference}
  - {title: 'views::enumerate・zip の要素は参照を含む組：構造化束縛でも元の要素を指す', anchor: enumerate-reference}
  - {title: 構造化束縛した名前のキャプチャ（C++20）と、使わない名前 _, anchor: capture-and-placeholder}
  - {title: 'tie：既存の変数にまとめて代入・比較する（std::ignore）', anchor: tie}
  - {title: 'tie(a, b) = tie(b, a) は入れ替えにならない（swap か pair で渡す）', anchor: tie-swap-pitfall}
  - {title: 代入の小技：exchange で代入して前の値を返す、tie と pair でまとめて更新する, anchor: exchange}
  - {title: optional：値がないことを表す（nullopt・has_value・value_or。C++17）, anchor: optional}
  - {title: apply と、同じ型の組としての array（apply は C++17）, anchor: apply}
stage: draft
updated: 2026-10-21
cpp_std: 17
gcc_min: null
atcoder: true
---

!!! abstract "要点"
    - **何ができるか**：pair・tuple・構造体の中身に名前を付けて取り出し（構造化束縛）、tie・optional で組や「値がない」を表す。`pq.top()` を参照で受けてから `pop` するような、受け方の誤りを防ぐ。
    - **いつ使うか**：解説コードに `auto [a, b] = p`・`for (auto& [k, v] : mp)`・`if (auto it = mp.find(k); it != mp.end())`・`tie(a, b) = …` が出てきて読みたいとき。辺の (重み, 始点, 終点) や、ダイクストラ法の (距離, 頂点) を名前で受けたいとき。
    - **計算量**：構造化束縛・tie・exchange・optional の操作はどれも $O(1)$。ただし `auto` で受けると右辺を丸ごとコピーするので、`vector` などを持つ組ではその大きさに比例する
    - **前提**：[参照と範囲 for](../cpp/cpp-range-for.md)

<!-- textlint-disable -->
別名：構造化束縛・structured binding・auto [a, b]・分解宣言・pair・tuple・tie・get<0>・make_pair・optional・nullopt・value_or・exchange・初期化式付き if
<!-- textlint-enable -->

構造化束縛は、C++17 で入った「組の中身に名前を付けて受け取る」書き方である。`p.first`・`get<2>(t)` と書く代わりに、`auto [d, v] = p;` と意味のある名前で読める。仕組みは「見えない変数に右辺を受け、その各メンバに名前を付ける」の 1 つだけで、`auto` と `auto&` の違いも、`pq.top()` の事故も、この仕組みから説明できる。このページの書き方は、AtCoder の GCC 15.2（`-std=gnu++23`）でも手元の g++-13 でも使える（`_` を 2 回使う書き方だけは g++-13 で通らない）。

このページのコードは `#include <bits/stdc++.h>` と `using namespace std;` を前提にする。

## pair と tuple：get・make_pair・波括弧での作成、辞書順で比べられる {#pair-tuple}

`pair<T, U>` は 2 つの値の組で、`first`・`second` で取り出す。`tuple<T, U, V, …>` は好きな個数の組で、3 つ以上をまとめるのに使う。`get<i>(t)`（$i$ は 0 から数える定数）で要素を取り出す。作るときは `make_pair(a, b)`・`make_tuple(a, b, c)`、または型を書かない `pair{a, b}`・`tuple{a, b, c}` を使う（中身から型を決める CTAD。C++17。[初期化の書き方](../cpp/cpp-initialization.md#ctad-std-types)）。

```cpp
--8<-- "cpp-structured-bindings/pair-tuple.cpp:core"
```

pair・tuple は辞書順で比べられる。まず 0 番目どうしを比べ、等しければ 1 番目、… と進む。`sort` すると第 1 キーの昇順、同じなら第 2 キーの昇順になるのはこのためである。ダイクストラ法で (距離, 頂点) の順に入れるのも、距離で比べたいからである（頂点を先に入れると頂点番号の順になる）。

- **版**：pair・tuple・`make_pair` は C++11 以前から。`pair{a, b}` の CTAD は C++17
- **落とし穴**：`get<i>` の $i$ は定数でなければならず、ループの変数では書けない。同じ型を添字で回したいなら [array](#apply) を使う
- **使い分け**：2〜3 個の値を一時的にまとめるなら pair・tuple、意味のある名前を残したいなら構造体、同じ型を添字で扱うなら `array` を使う。構造体の比較は [比較関数と順序](../cpp/cpp-comparators.md) で扱う

## 構造化束縛の形：pair・構造体・配列・array を名前に分ける、map の範囲 for（C++17） {#structured-binding}

`auto [a, b] = p;` は、`p` の中身に先頭から順に `a`・`b` と名前を付ける。分けられるのは次の 3 種類である。

- pair・tuple・`array`（`get` で取り出せる型）
- C の配列 `int c[3]`
- メンバをすべて公開した構造体（メンバの宣言順に名前が付く）

範囲 for と組み合わせると、辺のリストや `map` を名前付きで回せる。

```cpp
--8<-- "cpp-structured-bindings/bindings.cpp:edge"
```

```cpp
--8<-- "cpp-structured-bindings/bindings.cpp:core"
```

素朴に書くと、`for (auto e : es) { int to = e.to; long long cost = e.cost; … }` とほぼ同じ意味である。ただし名前 `to`・`cost` は新しい変数ではなく、見えない変数 `e` のメンバの別名である（[見えない変数](#hidden-variable)）。

- **版**：C++17。g++-13・g++-15 の `-std=gnu++17` 以降で使える
- **落とし穴**：名前はメンバの「宣言順」に付き、名前と意味の対応は検査されない。`struct Edge { int to; long long cost; };` を `auto [cost, to] = e;` と受けても、`cost` に行き先が入るだけでエラーにならない。構造体を受けるときは宣言の順を見て名前を付ける

## 見えない変数：auto はコピー、auto& は参照。名前はメンバの宣言順に付き、数が合わないとエラー（C++17） {#hidden-variable}

`auto [a, b] = p;` は、次の 2 段階として読む。

1. 名前のない変数 `e` を `auto e = p;` で作る（`auto&` なら `auto& e = p;`、`const auto&` なら `const auto& e = p;`）
2. `a` を `e.first` の、`b` を `e.second` の別名にする

`auto`・`auto&`・`const auto&` は 1 段目の `e` にかかる。`auto` なら `e` は `p` のコピーなので、`a` を書き換えても `p` は変わらない。`auto&` なら `e` は `p` そのものなので、`a` を書き換えると `p.first` が変わる。

![上段の auto [a, b] = p では、p を写した見えない変数 e があり、a・b は e のメンバを指すので a を変えても p は変わらない。下段の auto& [a, b] = p では、e が p そのものなので、a・b は p のメンバを直接指す](../img/cpp-structured-bindings/hidden-variable.svg)

```cpp
--8<-- "cpp-structured-bindings/hidden-variable.cpp:core"
```

名前の数は要素の数とちょうど同じでなければならない。過不足があればコンパイルエラーになり、「一部だけ受ける」ことはできない（要らない要素には名前 `_` を付けるか、[tie と ignore](#tie) を使う）。

```cpp
--8<-- "cpp-structured-bindings/count-ng.cpp:core"
```

g++-15 では `only 2 names provided for structured binding` と、続く `note: while 'std::tuple<int, int, int>' decomposes into 3 elements` で要素の数が示される。

- **版**：C++17。g++-13・g++-15 で同じ結果だった
- **使い分け**：読むだけで中身が小さい（数値の組）なら `auto`、書き換えたいなら `auto&`、大きな中身（`vector` や `string` を持つ組）を読むだけなら `const auto&` でコピーを避ける。ただし `const auto&` は元が変わると値も変わる（[pq.top() の事故](#pq-top-reference)）

## map を回すとき：キーは const、値を参照で受けて書き換えると map が変わる（C++17） {#map-loop}

`map<K, V>` の要素の型は `pair<const K, V>` である。`for (auto& [k, v] : mp)` の `v` は `map` の中の値そのものなので、`v` を書き換えると `map` が変わる。`for (auto [k, v] : mp)` なら各要素のコピーを書き換えるだけで、`map` は変わらない。

```cpp
--8<-- "cpp-structured-bindings/map-loop.cpp:core"
```

キー `k` は、`auto&` でも `auto` でも `const` である（コピーしても要素の型が `pair<const K, V>` のままだから）。キーを書き換えようとするとコンパイルエラーになる。`map` はキーの順に並べて持っているので、キーをその場で変えると並びが壊れるからである。

```cpp
--8<-- "cpp-structured-bindings/map-key-ng.cpp:core"
```

- **版**：C++17。`unordered_map` も同じ（要素は `pair<const K, V>`）
- **落とし穴 1**：「各値を 10 倍する」つもりで `auto [k, v]` と書くと、何も変わらないのにコンパイルは通る。書き換えるループは `auto&` にする
- **落とし穴 2**：`auto [k, v]` は 1 要素ごとにキーと値をコピーする。`map<string, vector<int>>` を読むだけなら `const auto& [k, v]` にする
- キーを変えたいときは、`erase` して新しいキーで入れ直す（[コンテナ操作の定型](../cpp/cpp-container-idioms.md)）

## 初期化式付き if・switch：find や insert の結果をその場で受けて調べる（C++17） {#if-init}

`if (宣言; 条件)` と書くと、条件の前に変数を宣言できる。宣言した変数は if 文の中（`else` を含む）だけで使え、外には漏れない。`find` の結果のイテレータのように、判定のためだけに作る変数を閉じ込めるのに使う。`switch (宣言; 値)` も同じである。

```cpp
--8<-- "cpp-structured-bindings/if-init.cpp:core"
```

`set::insert` と `map::insert`・`emplace` は (位置, 入ったか) の pair を返す。`if (auto [it, ok] = seen.insert(x); ok)` は「初めて出た値のときだけ」を 1 行で書く定型である。素朴に書くと次と同じ意味になる。

```text
{
    auto res = seen.insert(x);
    if (res.second) { … }
}   // res はここで消える
```

- **版**：C++17。範囲 for の初期化式 `for (auto v = f(); int x : v)` は C++20 で、g++-13・g++-15 とも使える
- **落とし穴**：`if (auto [it, ok] = seen.insert(x))` のように構造化束縛そのものを条件にする書き方は C++26 の機能である。g++-15 は `-std=gnu++23` では `structured bindings in conditions only available with '-std=c++2c'` と警告し、g++-13 は文法エラーにする。しかも条件になるのは組全体を `bool` に変えた値（`ok` ではない）なので、`insert` が返す pair では C++26 でもコンパイルエラーになる。条件は `; ok` と分けて書く
- `if (auto r = f())` のように宣言だけを書くと、`r` を `bool` に変えた値が条件になる。[optional](#optional) で使う形である

## pq.top() を参照で受けて pop すると値が変わる（ダイクストラで起きる。値で受ける） {#pq-top-reference}

[ダイクストラ法](../graph/dijkstra.md)で、優先度付きキューの先頭を `const auto&` で受けてから `pop` すると、受けた値が別の要素の値に変わる。次のコードは (5, 1)・(7, 2)・(9, 3) を入れたキューで、(5, 1) を取り出したつもりが `7 2` と出る（g++-13・g++-15 で同じ）。

```cpp
--8<-- "cpp-structured-bindings/pq-top.cpp:core"
```

`pq.top()` は、キューが中に持つ `vector` の先頭の要素への参照を返す。`const auto& [d, v]` の見えない変数は、その先頭の場所を指す。`pop` は先頭の要素を末尾に移して取り除き、残りを並べ直すので、先頭の場所には次に小さい (7, 2) が入る。`d`・`v` は同じ場所を見続けるので、新しい値が読めてしまう。キューの要素が 1 個のときは、指していた要素そのものが消えるので[未定義動作](../cpp/cpp-undefined-behavior.md#dangling-pq-top)になる（寿命の切れたものを指す参照、すなわちダングリングである）。

`auto [d, v] = pq.top();` と値で受ければ、見えない変数は先頭のコピーなので `pop` の影響を受けない。

```cpp
--8<-- "cpp-structured-bindings/pq-top-ok.cpp:core"
```

- **版**：C++17（構造化束縛を使わない `const auto& t = pq.top(); pq.pop();` でも同じことが起きる）
- **落とし穴**：手元の g++-13・g++-15 で、`-Wall -Wextra`・`-D_GLIBCXX_DEBUG`・`-fsanitize=address,undefined` のどれを付けた場合も警告や停止はなく、同じ `7 2` が出た。道具では見つからないので、`top()` は必ず値で受けてから `pop` する、と決めておく。(距離, 頂点) は 16 バイト程度なので、コピーの費用は気にしなくてよい

??? question "確認問題：`const auto& [d, v] = pq.top(); pq.pop();` の後、`d` は何を指しているか？"
    キューが中に持つ `vector` の先頭の場所を指している。`pop` の後、そこには残りの中で最小の要素が入っているので、`d` はその距離になる（要素が 1 個だったときは、消えた要素を指す未定義動作）。取り出した要素の値は、もうどこにも残っていない。

## views::enumerate・zip の要素は参照を含む組：構造化束縛でも元の要素を指す {#enumerate-reference}

`v | views::enumerate` の要素は (添字, 元の要素への参照) の組、`views::zip(a, b)` の要素は (a の要素への参照, b の要素への参照) の組である。`auto [i, x]` の見えない変数はこの組のコピーになるが、コピーされるのは「参照」なので、`x` は元の要素を指したままである。`auto` と書いても要素のコピーにはならず、`x` を書き換えると元の `vector` が変わる。

```cpp
--8<-- "cpp-structured-bindings/enumerate-ref.cpp:core"
```

[見えない変数](#hidden-variable)の規則どおり、`auto` が決めるのは「組をコピーするか」だけで、組の中身が値か参照かは組の型が決める。`map` を `auto [k, v]` で回すと `v` が値のコピーになるのは、`map` の要素が値を持つ pair だからである。

- **版**：`views::enumerate`・`views::zip` は C++23。g++-13・g++-15 の `-std=gnu++23` で使える（詳しくは [C++23 の views](../cpp/cpp-views-cpp23.md)）
- **落とし穴**：ループの中で `x` を一時的に書き換えて計算に使う（元の配列は変えたくない）つもりで `auto [i, x]` と書くと、元の `vector` が書き換わる。元を変えたくないなら、ループの中で `int y = x;` とコピーしてから使う

## 構造化束縛した名前のキャプチャ（C++20）と、使わない名前 _ {#capture-and-placeholder}

構造化束縛した名前は、C++20 から普通の変数と同じように[ラムダ式](../cpp/cpp-lambda.md)でキャプチャできる。グリッドの幅と高さを pair で受けて、範囲の判定のラムダで使う、といった書き方が通る。

```cpp
--8<-- "cpp-structured-bindings/capture.cpp:core"
```

使わない要素には `_` という名前を付ける習慣がある。`_` が 1 個だけなら普通の変数名なので、C++17 から通る。同じ場所で `_` を 2 回使う（`auto [_, x, _] = t;`）のは、C++26 で「使わない変数」として `_` を特別扱いするようになってからの書き方である。

```cpp
--8<-- "cpp-structured-bindings/placeholder-twice.cpp:core"
```

- **版（キャプチャ）**：C++20。ただし g++-13・g++-15 は、`-std=gnu++17 -pedantic` でも警告なしで通した（規格より先に許している）
- **版（`_` を 2 回）**：g++-15 は `-std=gnu++23` で `name-independent declarations only available with '-std=c++2c'` の警告を出して通す。AtCoder の GCC 15.2 も同じ版・同じ `-std=gnu++23` を使い、警告をエラーにしないので通るはずである（AtCoder の上では試していない）。g++-13 では `redeclaration of 'auto _'` のコンパイルエラーになる
- **落とし穴**：手元が g++-13 だと、AtCoder で通る `auto [_, x, _]` が手元で通らない。使わない要素が 2 個以上あるなら、`auto [unused1, x, unused2]` と別の名前を付けるか、[tie と ignore](#tie) を使う

## tie：既存の変数にまとめて代入・比較する（std::ignore） {#tie}

`tie(a, b)` は、変数 `a`・`b` への参照の組（`tuple<int&, int&>`）を作る。左辺に置くと、右辺の組を既にある変数へまとめて代入できる。構造化束縛は新しい名前を作る宣言なので、ループの外で宣言した変数を更新するときは `tie` を使う。要らない要素は `ignore` で捨てる。

```cpp
--8<-- "cpp-structured-bindings/tie.cpp:core"
```

`tie(x1, y1) < tie(x2, y2)` は、2 つの組を辞書順で比べる。比較関数で「$x$ の昇順、同じなら $y$ の昇順」を書くとき、`if` を重ねずに 1 行で書ける（`return tie(a.x, a.y) < tie(b.x, b.y);`。[比較関数と順序](../cpp/cpp-comparators.md)）。

- **版**：`tie`・`ignore` は C++11
- **使い分け**：新しい変数で取り出すなら構造化束縛、既にある変数に入れ直すなら `tie`

## tie(a, b) = tie(b, a) は入れ替えにならない（swap か pair で渡す） {#tie-swap-pitfall}

`tie(a, b) = tie(b, a);` は、右辺も参照の組なので、片方を代入した時点で右辺の残りも書き換わっている。GCC（libstdc++）は先頭の要素から順に代入するので、`a = b;` の後に `b = a;`（書き換わった後の `a`）を行うことになり、両方とも元の `b` になる。規格は代入の順を決めていないが、逆の順でも両方とも元の `a` になるだけで、どちらにしても入れ替えにはならない。

```cpp
--8<-- "cpp-structured-bindings/tie-swap.cpp:bad"
```

右辺を値の組 `pair{b, a}` にすれば、元の値のコピーを先に作ってから代入するので入れ替わる。2 つの入れ替えなら `swap(a, b)` がいちばん分かりやすい。

```cpp
--8<-- "cpp-structured-bindings/tie-swap.cpp:good"
```

- **版**：g++-13・g++-15 で同じ結果（`2 2`）だった。警告なしでコンパイルが通る
- **見分け方**：右辺に `tie` を置くのは比べるときだけにし、代入の右辺は `pair{…}`・`tuple{…}` にする

??? question "確認問題：`int a = 1, b = 2;` の後に `tie(a, b) = tie(b, a);` とすると、`a`・`b` はいくつになるか？"
    GCC ではどちらも 2 になる。右辺は `b` と `a` への参照の組なので、まず `a = b`（`a` が 2）、次に `b = a`（いまの `a` の 2）が行われる。入れ替えるには `swap(a, b)` か `tie(a, b) = pair{b, a};` と書く。

## 代入の小技：exchange で代入して前の値を返す、tie と pair でまとめて更新する {#exchange}

`exchange(x, y)` は、`x` に `y` を入れ、入れる前の `x` の値を返す（`<utility>`。C++14）。`int old = x; x = y;` の 2 行を 1 式にしたものである。`tie(f0, f1) = pair{f1, f0 + f1};` は、右辺の pair を先に作ってから代入するので、一時変数なしで「同時に」更新できる。フィボナッチ数のような 2 項の漸化式で使う。

```cpp
--8<-- "cpp-structured-bindings/exchange.cpp:core"
```

$n = 10$ なら $F_{10} = 55$ と出る。素朴に書くと `long long nf = f0 + f1; f0 = f1; f1 = nf;` である。

- **版**：`exchange` は C++14、`pair{…}` の CTAD は C++17
- **落とし穴**：`tie(f0, f1) = tie(f1, f0 + f1)` とは書けない（`f0 + f1` は変数ではないので参照の組に入らず、`cannot bind non-const lvalue reference` のコンパイルエラーになる）。右辺は `pair{…}` にする

## optional：値がないことを表す（nullopt・has_value・value_or。C++17） {#optional}

`optional<T>` は「`T` の値が 1 つある」か「何もない」かのどちらかを持つ型である。見つからないことを `-1` や `INF` で表す代わりに使うと、その値が本物の答えと紛れない。何もないことは `nullopt` で表す。

```cpp
--8<-- "cpp-structured-bindings/optional.cpp:func"
```

```cpp
--8<-- "cpp-structured-bindings/optional.cpp:core"
```

- `if (auto r = f())`：値があるときだけ真になり、中で `*r` で値を読む
- `o.has_value()`・`o.value_or(d)`：値があるか、値（なければ `d`）
- `o.value()`：値がなければ例外 `bad_optional_access` を投げる。`*o` は検査しない
- **版**：C++17。g++-13・g++-15 で使える
- **落とし穴**：空の `optional` に `*o` を使うのは未定義動作である。手元の g++-15 で `-O2` だと、空の `optional<int>` の `*o` が何事もなく `0` を返した。`-D_GLIBCXX_ASSERTIONS` を付けると `Assertion 'this->_M_is_engaged()' failed` で止まった。値があると確かめてから読む

## apply と、同じ型の組としての array（apply は C++17） {#apply}

`apply(f, t)` は、組 `t` の中身を引数に並べて `f` を呼ぶ（`apply(f, tuple{3, 4, 5})` は `f(3, 4, 5)`）。tuple のまま持っている値を、引数を並べる関数に渡すときに使う。

`array<int, 3>` は、同じ型の値を 3 つ持つ軽い組として使える。tuple と同じく辞書順で比べられ、構造化束縛でも分けられ、`apply` にも渡せる。そのうえ `e[i]` のように添字（ループの変数でもよい）で読める。辺 (重み, 始点, 終点) がすべて `int` なら、`tuple<int, int, int>` より `array<int, 3>` のほうが短く書ける。

```cpp
--8<-- "cpp-structured-bindings/apply.cpp:core"
```

- **版**：`apply` は C++17、`array` は C++11。g++-13・g++-15 で使える
- **使い分け**：型が混ざる（`long long` の重みと `int` の頂点）なら tuple か構造体、全部同じ型なら `array`

## 確認問題 {#quiz}

??? question "確認問題：`map<string, int> cnt` の各値を 2 倍にしたい。`for (auto [k, v] : cnt) v *= 2;` は正しいか？"
    正しくない。`auto` なので見えない変数は各要素のコピーで、`v` を書き換えても `cnt` は変わらない（コンパイルは通る）。`for (auto& [k, v] : cnt) v *= 2;` と書く。

??? question "確認問題：`vector<int> a` に対して `for (auto [i, x] : a | views::enumerate) x = 0;` を実行すると、`a` は変わるか？"
    変わる（全要素が 0 になる）。`views::enumerate` の要素は (添字, 元の要素への参照) の組で、`auto` がコピーするのは組だけである。中の参照はコピーしても同じ要素を指す。

## 参考 {#references}

- [cpprefjp「構造化束縛」](https://cpprefjp.github.io/lang/cpp17/structured_bindings.html)：分けられる型の 3 種類と、見えない変数の考え方
- [cppreference「Structured binding declaration」](https://en.cppreference.com/w/cpp/language/structured_binding)：名前の数が合わないときの規則と、`auto`・`auto&` が見えない変数にかかること
- [cpprefjp「構造化束縛を拡張して通常の変数宣言のように使用可能にする」](https://cpprefjp.github.io/lang/cpp20/extending_structured_bindings_to_be_more_like_variable_declarations.html)：ラムダでのキャプチャが C++20 から許されたこと
- [cpprefjp「宣言のみで使用しない変数の名前として_をサポート」](https://cpprefjp.github.io/lang/cpp26/nice_placeholder_with_no_name.html)：`_` を同じ場所で何度も宣言できるのが C++26 からであること
- [cpprefjp「if文とswitch文の条件式と初期化を分離」](https://cpprefjp.github.io/lang/cpp17/selection_statements_with_initializer.html)：初期化式付きの if・switch
- [cpprefjp「tie」](https://cpprefjp.github.io/reference/tuple/tie.html)：参照の組を作ることと `ignore`
- [cpprefjp「exchange」](https://cpprefjp.github.io/reference/utility/exchange.html)：代入して前の値を返す関数
- [cpprefjp「optional」](https://cpprefjp.github.io/reference/optional/optional.html)：`nullopt`・`value_or`・`value` の例外
- [cpprefjp「apply」](https://cpprefjp.github.io/reference/tuple/apply.html)：組を引数に展開して呼ぶ関数
- [cpprefjp「enumerate_view」](https://cpprefjp.github.io/reference/ranges/enumerate_view.html)：`views::enumerate` の要素が参照を含む組であること
