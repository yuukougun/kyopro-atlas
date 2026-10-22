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
related: [cpp-container-idioms, cpp-algorithms, cpp-structured-bindings, cpp-undefined-behavior, sorting-techniques, priority-queue, dijkstra, minimum-spanning-tree]
summary: sort・set・priority_queue に渡す比較関数を約束（狭義の弱順序）と向きを守って書き、構造体に operator< や <=> で順序を持たせる。比較関数に <= を書いて sort が落ちるような事故を防ぐ。
complexity: '比較関数は sort で O(N log N) 回、set・map・priority_queue の 1 回の操作で O(log N) 回呼ばれる'
signs: []
acl: []
sections:
  - {title: 比較関数の約束：a が b より前なら true を返し、狭義の弱順序を満たす（a と a を比べたら false）, anchor: strict-weak-ordering}
  - {title: 比較関数に「以下」を書くと sort が壊れる（同じ値が多いと Segmentation fault）, anchor: less-equal-pitfall}
  - {title: 降順：greater の 3 つの書き方（型を書く・型を省く・CTAD）, anchor: greater}
  - {title: priority_queue の向き：既定は最大が先頭、greater で最小が先頭, anchor: priority-queue-order}
  - {title: set・map の比較関数は「同じ」も決める（second だけで比べると、second の等しい要素が 1 個しか残らない）, anchor: set-equivalence}
  - {title: 複数のキーで比べる：pair・tuple の辞書順と tie, anchor: multiple-keys}
  - {title: ラムダの比較関数を型として渡す：decltype（C++20。C++17 では pq(cmp) と渡す）, anchor: lambda-comparator-type}
  - {title: 構造体に比較演算子の小なりを持たせる（メンバ関数に const が要る）, anchor: operator-less}
  - {title: 三方比較演算子の default で 6 つの比較を宣言順の辞書順にする（C++20）, anchor: spaceship}
stage: draft
updated: 2026-10-21
cpp_std: null
gcc_min: null
atcoder: true
---

!!! abstract "要点"
    - **何ができるか**：`sort`・`set`・`priority_queue` に渡す比較関数を、約束（狭義の弱順序）と向きを守って書き、構造体に `operator<` や `<=>` で順序を持たせる。比較関数に `<=` を書いて `sort` が落ちるような事故を防ぐ。
    - **いつ使うか**：要素を降順・複数のキー・構造体のメンバで並べたいとき。最小の要素から取り出すキューが要るとき。解説コードに `greater<>`・`decltype(cmp)`・`<=>` が出てきて読みたいとき。
    - **計算量**：比較関数は `sort` で $O(N \log N)$ 回、`set`・`map`・`priority_queue` の 1 回の操作で $O(\log N)$ 回呼ばれる
    - **前提**：[ラムダ式と再帰ラムダ](../cpp/cpp-lambda.md)

<!-- textlint-disable -->
別名：comparator・greater<>・greater{}・priority_queue の向き・最小ヒープ・厳密弱順序・strict weak ordering・operator<・三方比較演算子・宇宙船演算子・<=>・= default・構造体のソート・複数キーのソート
<!-- textlint-enable -->

比較関数は、2 つの要素 `a`・`b` を受け取り「`a` を `b` より前に置くか」を `bool` で返す関数である。`sort`・`set`・`map`・`priority_queue` はどれもこの 1 つの関数だけを頼りに並べるので、約束を破ると並びが崩れたり落ちたりし、向きを取り違えると逆順になる。

版はページの中で混ざる。`greater<>` は C++14、`set<T, decltype(cmp)>` で比較関数を渡さずに作る書き方と `<=>` は C++20 である。AtCoder の GCC 15.2（`-std=gnu++23`）と手元の g++-13・g++-15（`-std=gnu++23`）では、このページの書き方はすべて使える。コードは `#include <bits/stdc++.h>` と `using namespace std;` を前提にする。

## 比較関数の約束：a が b より前なら true を返し、狭義の弱順序を満たす（a と a を比べたら false） {#strict-weak-ordering}

比較関数 `cmp(a, b)` は「`a` が `b` より真に前（小さい）なら true」を返す。等しいときは false を返す。標準ライブラリは、この関数が[狭義の弱順序](../guide/glossary.md#strict-weak-ordering)（厳密弱順序。strict weak ordering）であることを前提にしている。条件を短く言うと次の 3 つである（式での定義と破り方の例は[ソートで考える](../basics/sorting-techniques.md#strict-weak-ordering)）。

- 自分自身と比べたら false（`cmp(a, a)` は false）
- `a` が `b` より前、`b` が `c` より前なら、`a` は `c` より前
- `cmp(a, b)` と `cmp(b, a)` がどちらも false の 2 つを「同じ」とみなし、この「同じ」が推移する

最後の「同じ」は値が等しいことではない。長さだけで比べる比較関数では、`"ab"` と `"cd"` は「同じ」である。`sort` は「同じ」要素どうしの順を決めないので、入力の順を残したいときは `stable_sort` を使う。

```cpp
--8<-- "cpp-comparators/strict-weak.cpp:core"
```

入力 `ccc b aa d ee` なら `b d aa ee ccc` と出る。長さ 1 の `b`・`d`、長さ 2 の `aa`・`ee` は、それぞれ入力の順のまま並ぶ。

- **既定では**：比較関数を渡さない `sort(v.begin(), v.end())` は、要素の `<` を使う。`cmp` を渡すと、その `<` を `cmp` に置き換えて並べる
- **落とし穴**：比較関数の中で重い計算をしない。`sort` では $O(N \log N)$ 回呼ばれる。キーは先に計算して配列で持ち、引数は `const T&` で受ける

## 比較関数に「以下」を書くと sort が壊れる（同じ値が多いと Segmentation fault） {#less-equal-pitfall}

比較関数に `<=`（降順なら `>=`）を書くと、等しい 2 つで true を返し、「自分自身と比べたら false」の約束を破る。約束を破った比較関数を `sort` に渡すのは[未定義動作](../cpp/cpp-undefined-behavior.md#other-ub)で、コンパイラは警告を出さない。

```cpp
--8<-- "cpp-comparators/less-equal.cpp:core"
```

手元で、同じ値 `1` だけが並ぶ配列を `<=` の比較関数で `sort` した（g++-13・g++-15、`-O2`）。結果は要素の数で変わり、小さな入力の試しでは気づけない（表の 17〜3×10^4 は 17・1000・3×10^4 などで、最後の行は 3.5×10^4・4×10^4・10^5 などで試した）。

| 要素の数 | 普通にコンパイル | `-fsanitize=address` | `-D_GLIBCXX_DEBUG` |
| --- | --- | --- | --- |
| 1〜16 | 正常に終わる | 正常に終わる | 止まる（1 個でも） |
| 17〜3×10^4 | 正常に終わる | 配列外の読み込みで止まる | 止まる |
| 3.5×10^4〜10^5 | 異常終了（Segmentation fault など） | 止まる | 止まる |

落ちる理由は、`sort` の中の分割の手順にある。`sort` は基準の値を 1 つ選び、「基準より前に来るべき間は進む」ループで配列を進む。`<=` だと基準と等しい要素でも true が返るので、同じ値が続くとループが止まらず、配列の終わりを越えて読む。16 個以下では別の手順（挿入ソート）だけを使うので、この読み越しが起きなかった。

`-D_GLIBCXX_DEBUG` を付けてコンパイルすると、`sort` は始めに、先頭の要素を自分自身と比べて false になるかを確かめる。`<=` や `>=` の比較関数はここで必ず引っかかり、`Error: comparison doesn't meet irreflexive requirements, assert(!(a < a)).` と出して止まる。手元で試すときに付けておくと見つかる（付け方は[未定義動作](../cpp/cpp-undefined-behavior.md#debug-build)）。ただし、推移しないなどのほかの破り方は、この検査では見つからないことがある（手元では、推移しない比較関数で sort しても止まらなかった）。

- **直し方**：昇順は `<`、降順は `>` を書く。`=` を付けない
- **落とし穴**：`set`・`map` に `<=` の比較関数を渡すと、同じ値を何度でも入れられてしまい、`find` で見つからなくなる。どのコンテナでも、比較関数は `<` か `>` で書く

## 降順：greater の 3 つの書き方（型を書く・型を省く・CTAD） {#greater}

`greater` は `a > b` を返す関数オブジェクトで、比較関数として渡すと降順になる。書き方は 3 通りある。

```cpp
--8<-- "cpp-comparators/greater.cpp:core"
```

- `greater<T>()`：`T` 型の 2 つを比べる。引数は、比べる前に `T` へ変換される
- `greater<>()`：`greater<void>` の略（C++14）。引数を変換せず、そのままの型で `>` を呼ぶ。型の違う 2 つも比べられる
- `greater{}`：型引数を省いた `greater` から、[CTAD](../cpp/cpp-initialization.md#ctad)（C++17）で `greater<void>` が選ばれる。意味は `greater<>()` と同じ

`greater<T>` の `T` を要素の型と違えると、警告なしで並びが誤る。`long long` の配列へ `greater<int>()` を渡すと、3000000000 が `int` へ変換されて負の数になり、いちばん後ろに並んだ。

```cpp
--8<-- "cpp-comparators/greater.cpp:pitfall"
```

- **版**：`greater<>` は C++14、`greater{}` は C++17。g++-13・g++-15 で使える
- **使い分け**：型を書き間違えないよう、`greater<>()` か `greater{}` を使うとよい。`less` も同じで、`less<>` は `<` を型を変換せずに呼ぶ
- **素朴に書くと**：`[](const auto& a, const auto& b) { return a > b; }` と同じである

## priority_queue の向き：既定は最大が先頭、greater で最小が先頭 {#priority-queue-order}

`priority_queue` の比較関数 `cmp(a, b)` は「`a` は `b` より優先度が低い（後で取り出す）」を意味する。既定の比較関数は `less` なので、小さいものほど後になり、最大が `top` に来る。`greater` を渡すと、大きいものほど後になり、最小が `top` に来る。

```cpp
--8<-- "cpp-comparators/pq-order.cpp:core"
```

同じ比較関数でも、コンテナによって「true の側」の行き先が違う。次の表は `cmp(a, b)` が true のときの意味と、先に出てくる要素である（`sort` と `set` は先頭から、`priority_queue` は `top` から出てくる）。

| 渡す先 | `cmp(a, b)` が true の意味 | `less`（既定）で先に出る | `greater` で先に出る |
| --- | --- | --- | --- |
| `sort` | `a` を `b` より前に置く | 最小 | 最大 |
| `set`・`map` | `a` を `b` より前に置く | 最小 | 最大 |
| `priority_queue` | `a` を `b` より後で取り出す | 最大 | 最小 |

`priority_queue` は、比較関数で並べた列のいちばん「後ろ」を `top` に置くと覚えると、向きを取り違えない。`sort` で昇順になる比較関数を渡せば、昇順の最後の要素（最大）が `top` になる。

[ダイクストラ法](../graph/dijkstra.md)では、(距離, 頂点) の `pair` を距離の小さい順に取り出すので、`greater<>` を渡す。

```cpp
--8<-- "cpp-comparators/pq-order.cpp:dijkstra"
```

- **素朴に書くと**：最小を取り出すキューは、値の符号を反転して既定の `priority_queue` に入れても作れる（`push(-x)` して `-top()` を読む）。符号の戻し忘れが起きやすいので、`greater` を渡すほうが安全である
- **落とし穴**：要素を `pair` にしたとき、比べるのは `first` からである。距離で取り出したいなら、距離を `first` に置く
- **落とし穴**：`const auto& [d, v] = pq.top(); pq.pop();` は `pop` の後に消えた要素を読む。値で受ける（[構造化束縛](../cpp/cpp-structured-bindings.md#pq-top-reference)）

## set・map の比較関数は「同じ」も決める（second だけで比べると、second の等しい要素が 1 個しか残らない） {#set-equivalence}

`set`・`map` は `==` を使わない。`!cmp(a, b) && !cmp(b, a)` のとき、2 つを同じキーとみなす。そのため、一部のメンバだけで比べる比較関数を渡すと、そのメンバが等しい要素は 1 つしか入らない。`find`・`count`・`insert` もこの「同じ」で動く。

```cpp
--8<-- "cpp-comparators/set-equivalence.cpp:core"
```

`second` だけで比べる `set` に `{1, 5}` と `{2, 5}` を入れると、`{2, 5}` は `{1, 5}` に等しいとみなされ、入らない。`count({9, 5})` も 1 を返す。等しいときの比べ方（ここでは `first`）を後ろに足して全部のメンバを比べると、両方が残る。

- **使い分け**：同じキーを重ねて持ちたいなら `multiset` を使う。ただし `multiset` でも「同じ」の判定は比較関数で行うので、`erase(x)` は比較関数で同じとみなされる要素をすべて消す（1 個だけ消す書き方は[コンテナの定型](../cpp/cpp-container-idioms.md#multiset-erase-one)）
- **落とし穴**：`sort` では「同じ」要素は並ぶだけで消えない。同じ比較関数を `set` に移すと要素が減るので、移す前に、比較関数がすべてのメンバを見ているかを確かめる

## 複数のキーで比べる：pair・tuple の辞書順と tie {#multiple-keys}

`pair` と `tuple` の `<` は辞書順である。1 つ目で比べ、等しければ 2 つ目で比べる。比較関数を書かずに 2 つのキーで並べられる。

```cpp
--8<-- "cpp-comparators/multiple-keys.cpp:pair"
```

構造体のメンバで比べるときは、`tie` でメンバへの参照の `tuple` を作り、`<` で比べる。キーごとに向きを変えたいときは、降順にするキーだけ `a` と `b` を入れ替える。次の例は、得点の大きい順、得点が等しければ名前の辞書順である。

```cpp
--8<-- "cpp-comparators/multiple-keys.cpp:core"
```

`tie(b.score, a.name) < tie(a.score, b.name)` は、1 つ目のキーでは `b.score < a.score`（得点の降順）を、2 つ目のキーでは `a.name < b.name`（名前の昇順）を比べる。入力 `80 bob`・`90 carol`・`80 alice`・`70 dave` なら、`90 carol`・`80 alice`・`80 bob`・`70 dave` の順になる。

- **素朴に書くと**：`if (a.score != b.score) return a.score > b.score; return a.name < b.name;` と同じである。キーが 3 つ以上になると `if` が増えて書き間違えやすいので、`tie` でまとめる
- **使い分け**：数のキーなら、`pair(-a.score, a.name)` のように符号を反転したキーで比べても降順にできる。符号を反転すると `INT_MIN` であふれるので、範囲に気をつける
- **関連**：`tie` のほかの使い方は[構造化束縛と tie](../cpp/cpp-structured-bindings.md#tie)。構造体に順序を 1 つだけ持たせるなら、[operator<](#operator-less) や [<=>](#spaceship) で書く

## ラムダの比較関数を型として渡す：decltype（C++20。C++17 では pq(cmp) と渡す） {#lambda-comparator-type}

`sort` には比較関数そのものを引数で渡すが、`set`・`map`・`priority_queue` には比較関数の「型」をテンプレート引数で渡す。ラムダ式の型には名前がないので、`decltype(cmp)` で取り出す（[ラムダ式と再帰ラムダ](../cpp/cpp-lambda.md)）。

C++20 では、キャプチャのないラムダの型から比較関数を作れる。そのため、型を渡すだけでよい。

```cpp
--8<-- "cpp-comparators/lambda-type.cpp:core"
```

C++17 では、ラムダの型から比較関数を作れないので、`set<int, decltype(cmp)> st;` はコンパイルエラーになる（g++-13・g++-15 の `-std=gnu++17` で確かめた）。コンストラクタに `cmp` を渡す。

```cpp
--8<-- "cpp-comparators/lambda-type-17.cpp:core"
```

キャプチャのあるラムダ（`[&]` で外の配列を見るものなど）は、C++20 でも型から作れない。`set<int, decltype(by_w)> idx;` は `use of deleted function` のエラーになるので、常に `cmp` を渡す。

```cpp
--8<-- "cpp-comparators/lambda-type.cpp:capture"
```

- **版**：型だけを渡す書き方は C++20。AtCoder の `-std=gnu++23` と g++-13・g++-15 で使える。`cmp` を渡す書き方はどの版でも使えるので、迷ったら渡す
- **落とし穴**：`by_w` で比べる `set` に入れた後で `w` を書き換えると、`set` の中の並びが崩れ、`find` などが正しく動かない。キーにする値は、入れている間は変えない
- **関連**：`priority_queue pq(greater<int>{}, vector<int>{})` のように型引数を省く書き方は[初期化と CTAD](../cpp/cpp-initialization.md#ctad-std-types)

## 構造体に比較演算子の小なりを持たせる（メンバ関数に const が要る） {#operator-less}

構造体に `operator<` を書くと、比較関数を渡さずに `sort`・`set`・`priority_queue` が使える。メンバ関数として書くときは、引数を `const T&` で受け、最後に `const` を付ける。

```cpp
--8<-- "cpp-comparators/operator-less.cpp:core"
```

最後の `const` は「この関数は自分を書き換えない」という印である。`set`・`priority_queue`・`ranges::sort` は要素を `const` のまま比べるので、`const` のない `operator<` は呼べず、コンパイルエラーになる。

```cpp
--8<-- "cpp-comparators/operator-less-ng.cpp:core"
```

g++-13・g++-15 では `no match for 'operator<' (operand types are 'const Seg' and 'const Seg')` と出る。紛らわしいことに、`std::sort` だけなら `const` がなくても通る（手元で確かめた）。`sort` が通ったコードも、`set` に入れたところで初めてエラーになる。

- **素朴に書くと**：`sort(v.begin(), v.end(), [](const Seg& a, const Seg& b) { return a.r < b.r; });` と同じ順である。順序がその構造体で 1 つに決まるなら `operator<`、場面ごとに違う順で並べるならラムダの比較関数を使う
- **落とし穴**：`operator<` を右端 `r` だけで書くと、`set<Seg>` では右端の等しい区間が 1 つしか入らない（[set・map の比較関数は「同じ」も決める](#set-equivalence)）

## 三方比較演算子の default で 6 つの比較を宣言順の辞書順にする（C++20） {#spaceship}

`auto operator<=>(const T&) const = default;` を書くと、`<`・`<=`・`>`・`>=`・`==`・`!=` の 6 つの比較が使えるようになる。`==` はコンパイラが合わせて作り、`<` などは `<=>` を使う式に、`!=` は `==` を使う式に書き換えられる。比べ方はメンバの宣言順の辞書順である。1 つ目のメンバで比べ、等しければ 2 つ目で比べる。`<=>` を三方比較演算子（宇宙船演算子）という。

```cpp
--8<-- "cpp-comparators/spaceship.cpp:core"
```

```cpp
--8<-- "cpp-comparators/spaceship.cpp:use"
```

`Edge` は `cost`・`u`・`v` の順に比べられるので、`sort` するとコストの小さい順に並ぶ（[クラスカル法](../graph/minimum-spanning-tree.md)で辺を並べる形）。比べる順を変えたいときは、メンバの宣言の順を入れ替える。

- **版**：C++20。g++-13・g++-15 とも `-std=gnu++20` から使え、`-std=gnu++17` ではコンパイルエラーになる。AtCoder の `-std=gnu++23` で使える
- **素朴に書くと**：`bool operator<(const Edge& o) const { return tie(cost, u, v) < tie(o.cost, o.u, o.v); }` と、`==` などの残りの 5 つを書くのと同じである
- **落とし穴**：比べたくないメンバ（番号など）も比較に入る。`id` を先頭に置くと `id` の順に並ぶ。一部のメンバだけで比べるなら、`operator<` かラムダの比較関数を書く
- **使い分け**：比べるだけなら `pair`・`tuple` で足りる。メンバに名前を付けたいときは、構造体に `<=>` を付ける

## 確認問題 {#quiz}

??? question "確認問題：最小が top に来る `priority_queue<int>` の書き方を 2 つ挙げよ"
    `priority_queue<int, vector<int>, greater<int>> pq;` と、`auto cmp = [](int a, int b) { return a > b; };` を作って `priority_queue<int, vector<int>, decltype(cmp)> pq(cmp);` とする書き方である（C++20 なら `(cmp)` を省ける）。どちらも「大きいほど優先度が低い」を表すので、最小が `top` に来る。

??? question "確認問題：`second` だけで比べる `set<pair<int, int>, decltype(cmp)>` に `{1, 5}` と `{2, 5}` を入れると、`size()` はいくつか？"
    1 である。`cmp({1, 5}, {2, 5})` と `cmp({2, 5}, {1, 5})` がどちらも false なので、2 つは同じキーとみなされ、後から入れた `{2, 5}` は入らない。両方残すには、`second` が等しいときに `first` で比べるよう比較関数を直す。

??? question "確認問題：降順にしたくて `sort(v.begin(), v.end(), [](int a, int b) { return a >= b; })` と書いた。何が起きうるか？"
    等しい値の組で true を返すので、比較関数の約束（自分自身と比べたら false）を破る。同じ値が多いと配列の外を読み、手元では同じ値 3.5×10^4 個から異常終了した（10^5 個では Segmentation fault）。`a > b` か `greater<>()` に直す。

??? question "確認問題：`struct P { int y, x; auto operator<=>(const P&) const = default; };` の配列を `sort` すると、どの順に並ぶか？"
    `y` の小さい順、`y` が等しければ `x` の小さい順である。`= default` の `<=>` は、メンバを宣言した順（ここでは `y`・`x`）の辞書順で比べる。

## 参考 {#references}

- [cpprefjp「algorithm」](https://cpprefjp.github.io/reference/algorithm.html)：比較関数に求められる狭義の弱順序の定義
- [cppreference「C++ named requirements: Compare」](https://en.cppreference.com/w/cpp/named_req/Compare)：比較関数の要件と、等価（同じ）の定義
- [cpprefjp「std::greater」](https://cpprefjp.github.io/reference/functional/greater.html)：`greater<void>` の特殊化が C++14 で入ったこと
- [cpprefjp「std::priority_queue」](https://cpprefjp.github.io/reference/queue/priority_queue.html)：比較関数の向きと `top` の関係
- [cpprefjp「std::set」](https://cpprefjp.github.io/reference/set/set.html)：比較関数による要素の同値の扱い
- [cpprefjp「状態を持たないラムダ式を、デフォルト構築可能、代入可能とする」](https://cpprefjp.github.io/lang/cpp20/default_constructible_and_assignable_stateless_lambdas.html)：C++20 で `set<T, decltype(cmp)>` を比較関数なしで作れること
- [cpprefjp「<=>/==による比較演算子の自動定義」](https://cpprefjp.github.io/lang/cpp20/consistent_comparison.html)：`= default` の `<=>` がメンバの宣言順に比べること
- [GCC「Chapter 18. Debug Mode」](https://gcc.gnu.org/onlinedocs/libstdc++/manual/debug_mode.html)：`_GLIBCXX_DEBUG` がアルゴリズムの前提（比較関数など）を検査すること。irreflexive の検査の文面と、検査で見つからない破り方は手元で確かめた
