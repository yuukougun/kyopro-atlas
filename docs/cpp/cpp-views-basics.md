---
id: cpp-views-basics
title: views の基本
aliases: [views, ビュー, Range アダプタ, range adaptor, パイプ, 遅延評価, 'views::iota', 'views::reverse', 'views::filter', 'views::transform', 'views::take', 'views::keys', 'views::split', 'views::join', 'views::common']
type: cpp
field: cpp
chapter: ranges と views
order: 160
level: 基礎
kind: [実装・C++]
prerequisites: [cpp-lambda]
related: [cpp-algorithms, cpp-views-cpp23, cpp-integer-overflow, cpp-string-api]
summary: '| でつなぐ views（iota・filter・transform・split など）を、取り出すときに計算する遅延評価として読み書きする。views::iota(0, v.size()) が通らない理由など、型と寿命の罠も分かる。'
complexity: 'view を作るのは O(1)。回すと元の要素を 1 回ずつ見て、そのたびに中の関数を呼ぶ'
signs: []
acl: []
sections:
  - {title: 'view とは：元の範囲を見る方法だけを持ち、取り出すときに計算する', anchor: what-is-view}
  - {title: 'views::iota(a, b)・views::iota(a)：普通の for と同じ速さ', anchor: iota}
  - {title: 'views::iota(0, v.size()) がコンパイルエラーになる理由と直し方', anchor: iota-size-mismatch}
  - {title: 'views::iota(0, n) は n が long long でも i が int になる', anchor: iota-int}
  - {title: 'views::reverse は逆順に見るだけ', anchor: reverse}
  - {title: 'filter と transform：transform の後に filter を置くと関数が 2 回呼ばれる', anchor: filter-transform}
  - {title: 'take・drop・take_while・drop_while', anchor: take-drop}
  - {title: 'keys・values・elements<N>：map のキーだけを回す', anchor: keys-values}
  - {title: 'split と join：文字列を区切る、vector の vector を平らにする', anchor: split-join}
  - {title: 'common：イテレータの組を取る古いコンストラクタに渡すとき', anchor: common}
  - {title: 'view の寿命：元のコンテナより長く使わない', anchor: lifetime}
stage: draft
updated: 2026-10-21
cpp_std: 20
gcc_min: 13
atcoder: true
---

!!! abstract "要点"
    - **何ができるか**：配列や連番を「見る方法」だけを持つ view を `|` でつなぎ、絞り込み・変換・逆順・区切りをコピーなしで書く。要素は取り出すときに初めて計算される。
    - **いつ使うか**：解説コードに `| views::` や `views::iota(0, n)` が出てきて読みたいとき。添字のループ・逆順のループ・空白での分割を短く書きたいとき。
    - **計算量**：view を作るのは $O(1)$。回すと元の要素を 1 回ずつ見て、そのたびに中の関数を呼ぶ（2 回回せば 2 回呼ぶ）
    - **前提**：[ラムダ式と再帰ラムダ](../cpp/cpp-lambda.md)

<!-- textlint-disable -->
別名：views・ビュー・Range アダプタ・range adaptor・パイプ・遅延評価・views::iota・views::reverse・views::filter・views::transform・views::take・views::keys・views::split・views::join・views::common
<!-- textlint-enable -->

views は、C++20 で入った `<ranges>` の部品である。元の配列をコピーせず、「どう見るか」だけを `|` で重ねていく。AtCoder の GCC 15.2（`-std=gnu++23`）でも手元の g++-13（`-std=gnu++23`）でも、このページの書き方はすべて使える。ただし `string_view(w)` と `0uz` は C++23 の機能で、`-std=gnu++20` では前者がコンパイルエラー、後者が警告になる。

このページのコードは `#include <bits/stdc++.h>` と `using namespace std;` を前提にし、`std::views` を `views` と書く。

## view とは：元の範囲を見る方法だけを持ち、取り出すときに計算する {#what-is-view}

view は、元の範囲（`vector` や連番）への参照と「どう見るか」の規則だけを持つ軽い物である（右辺値のコンテナを流したときだけは中に持つ。[view の寿命](#lifetime)）。`a | views::filter(f)` は `views::filter(a, f)` と同じ意味で、`|` は左の範囲を右の部品に渡す記号である（ビットの OR とは別）。`a | views::filter(f) | views::transform(g)` と書いた時点では何も計算しない。範囲 for で 1 つ取り出すたびに、`f` で判定し、通った要素に `g` を適用する。この「必要になってから計算する」ことを遅延評価という。

```cpp
--8<-- "cpp-views-basics/pipe.cpp:core"
```

入力 `1 2 3 4 6` なら `4 16 36` と出て、`transform` の関数は偶数の 3 個にだけ呼ばれる。素朴に書くと、次の範囲 for と同じ意味である。

```cpp
--8<-- "cpp-views-basics/naive-pipe.cpp:core"
```

view は値を覚えない。同じ `transform` の view を 2 回回すと 2 回計算し、途中で元の配列を書き換えると、次に回したときは新しい値が見える。`filter` は例外で、[filter と transform](#filter-transform) の落とし穴 3 のとおり、書き換えた後に回し直してはいけない。

```cpp
--8<-- "cpp-views-basics/recompute.cpp:core"
```

- **版**：C++20。g++-13・g++-15 のどちらでも `-std=gnu++20` から使える
- **落とし穴**：view は結果を保存しない。何度も使う変換の結果や、元を書き換えた後も残したい結果は、`vector` に移してから使う（C++23 の `ranges::to` は [C++23 の views](../cpp/cpp-views-cpp23.md) で扱う）

## views::iota(a, b)・views::iota(a)：普通の for と同じ速さ {#iota}

`views::iota(a, b)` は $a, a+1, \dots, b-1$ の連番（$a$ 以上 $b$ 未満）を作る。`views::iota(a)` は $a$ から始まる終わりのない連番を作る。`for (int i : views::iota(0, n))` は `for (int i = 0; i < n; i++)` と同じ意味である。終わりのない連番は `views::take` などで長さを決めて使う。

```cpp
--8<-- "cpp-views-basics/iota.cpp:core"
```

- **速さ**：手元で、長さ $2 \times 10^4$ の配列に対する二重ループ（$4 \times 10^8$ 回）を `-O2` で比べた。g++-15 では普通の for が 49〜54 ms、`views::iota` が 48〜49 ms で、差は測定のぶれの範囲だった。g++-13 でも同じ程度だった
- **版**：C++20。g++-13・g++-15 で使える
- **落とし穴**：`views::iota(a, b)` は $a \le b$ を前提にしていて、$a > b$ は前提を破る[未定義動作](../cpp/cpp-undefined-behavior.md)になる。普通の for なら 1 回も回らないが、`views::iota` では何が起きるか決まっていない。手元の g++-15 で `views::iota(5, 1)` を回すと、5, 6, 7, … と増え続けた（11 で打ち切った。`-D_GLIBCXX_ASSERTIONS` を付けると前提の検査で止まる）。$a > b$ になりうるなら、先に `if` で除くか普通の for で書く
- **混同**：`std::iota(v.begin(), v.end(), 0)` は配列を連番で「埋める」アルゴリズムで、`views::iota` とは別物である

## views::iota(0, v.size()) がコンパイルエラーになる理由と直し方 {#iota-size-mismatch}

`views::iota(0, v.size())` は g++-13 でも g++-15 でもコンパイルエラーになる。始まりの `0` は `int`（符号付き）、終わりの `v.size()` は `size_t`（符号なし）である。`iota` は、符号付きと符号なしの整数を組にすることを禁じている（比べたときの結果が食い違うため。`-1 < v.size()` は偽になる）。`int` と `long long` のように符号がそろっていれば、型が違っても通る。

```cpp
--8<-- "cpp-views-basics/iota-size-ng.cpp:core"
```

エラーは `no match for call to '(const std::ranges::views::_Iota) (int, std::vector<int>::size_type)'` と出る。2 つの型をそろえれば通る。

```cpp
--8<-- "cpp-views-basics/iota-size-ok.cpp:core"
```

- `(int)v.size()`：要素は `int`。いちばん素直で、普通の for の `i < (int)v.size()` と同じ考え方である
- `ssize(v)`：符号付きの大きさ（`ptrdiff_t`。64 bit の Linux では `long`）を返す。始まりの `0` も符号付きなので通る。要素は始まりの型の `int` である（[要素の型は始まりで決まる](#iota-int)）
- `0uz`：`size_t` 型の 0 を書く C++23 の接尾辞。要素は `size_t`（符号なし）なので、`i - 1` などの引き算の結果は負にならない（大きな正の数になる）
- **版**：`ssize` は C++20、`0uz` は C++23。g++-13・g++-15 とも `-std=gnu++23` で使える。添字の列を作る C++26 の `views::indices(n)` は、g++-15 には（`-std=gnu++26` でも）なく、AtCoder では使えない

## views::iota(0, n) は n が long long でも i が int になる {#iota-int}

`views::iota(a, b)` の要素の型は、始まり `a` の型で決まる。`n` が `long long` でも、`views::iota(0, n)` の要素は `int` である。`n` が $2^{31}$ 以上になりうると `i` があふれる（[オーバーフロー](../cpp/cpp-integer-overflow.md)）。始まりを `0LL` にすれば、要素は `long long` になる。

```cpp
--8<-- "cpp-views-basics/iota-int.cpp:core"
```

- **版**：C++20。g++-13・g++-15 で、どちらの `static_assert` も通る
- **落とし穴**：`for (long long i : views::iota(0, n))` と受ける変数を `long long` にしても直らない。作られる値そのものが `int` で、受け取るときに広げているだけだからである

## views::reverse は逆順に見るだけ {#reverse}

`v | views::reverse` は `v` を後ろから順に見る view で、`v` そのものは変えない。`ranges::reverse(v)` と `std::reverse(v.begin(), v.end())` は、`v` の中身を並べ替える。

```cpp
--8<-- "cpp-views-basics/reverse.cpp:core"
```

入力 `1 2 3` に対して、1 行目は `3 2 1`、2 行目は `1 2 3`（そのまま）、3 行目は `3 2 1` と出る。逆順のループ `for (int i = n - 1; i >= 0; i--)` は、`views::iota` と組み合わせて書ける。

```cpp
--8<-- "cpp-views-basics/reverse-iota.cpp:core"
```

- **版**：C++20。g++-13・g++-15 で使える
- **落とし穴**：名前が似ているので取り違えやすい。並べ替えた結果を後で使うなら `ranges::reverse`、その場で逆から見るだけなら `views::reverse` を使う

## filter と transform：transform の後に filter を置くと関数が 2 回呼ばれる {#filter-transform}

`views::filter(pred)` は `pred` が真になる要素だけを残し、`views::transform(f)` は各要素を `f` の値に置き換える。どちらもラムダ式を渡して使う。

並べる順で、関数を呼ぶ回数が変わる。`transform` を先に置くと、`filter` は判定のために変換後の値を求め、取り出すときにもう一度変換後の値を求める。そのため、残った要素では `f` が 2 回呼ばれる。手元では、5 個のうち 3 個が残る例で、先に `filter` なら 3 回、先に `transform` なら 8 回（判定の 5 回と取り出しの 3 回）だった。

```cpp
--8<-- "cpp-views-basics/filter-transform.cpp:core"
```

- **版**：C++20。g++-13・g++-15 で同じ回数だった
- **落とし穴 1**：重い関数や、呼んだ回数で結果が変わる関数（カウンタを増やす・乱数を引く）を `transform` に入れない。条件が変換前の値で書けるなら、`filter` を先に置く
- **落とし穴 2**：`filter` の view は `const` の参照で受けると回せない（`filter` は最初の要素の位置を覚えておくために、回すとき自分を書き換えるから）。次の関数はコンパイルエラーになる。view を受け取る関数は `auto&& r` と書く

```cpp
--8<-- "cpp-views-basics/filter-const-ng.cpp:core"
```

- **落とし穴 3**：`filter` の view は、最初に見つけた要素の位置を覚えて使い回す。通った要素を条件に合わない値へ書き換えるのは未定義動作である。手元では、書き換えた後に回し直すと条件に合わない要素から始まった。元を書き換えたら view を作り直す

```cpp
--8<-- "cpp-views-basics/filter-rerun.cpp:core"
```

??? question "確認問題：`a | views::transform(f) | views::filter(p)` で `f` を呼ぶ回数は？"
    $N + K$ 回である（$N$ は $a$ の長さ、$K$ は `p` を満たす要素の数）。判定のために全要素で 1 回ずつ、残った要素を取り出すときにもう 1 回ずつ呼ばれる。

## take・drop・take_while・drop_while {#take-drop}

先頭の一部だけを見る view である。

- `views::take(k)`：先頭の $k$ 個（$k$ 個に足りなければあるだけ）
- `views::drop(k)`：先頭の $k$ 個を除いた残り
- `views::take_while(pred)`：先頭から `pred` が真の間だけ
- `views::drop_while(pred)`：先頭から `pred` が真の間を飛ばした残り

```cpp
--8<-- "cpp-views-basics/take-drop.cpp:core"
```

入力 `3 1 -4 1 5 9` なら、順に `3 1 -4`・`1 5 9`・`3 1`・`-4 1 5 9` と出る。長さ 2 の列に `take(3)` をかけると 2 個、`drop(3)` をかけると空になり、範囲外を読むことはない。

- **版**：C++20。g++-13・g++-15 で使える
- **落とし穴**：`take_while` は条件が初めて偽になった所で止まり、その先に条件を満たす要素があっても見ない（`filter` とは違う）。`take_while` の結果を `vector` のコンストラクタに渡すときは、[common](#common) を挟む

## keys・values・elements<N>：map のキーだけを回す {#keys-values}

`views::keys` は `pair` や `tuple` の 0 番目だけ、`views::values` は 1 番目だけを見る。`views::elements<N>` は $N$ 番目（0 から数える）だけを見る。`map` のキーだけ、辺の `tuple` の重みだけを回すときに使う。

```cpp
--8<-- "cpp-views-basics/keys-values.cpp:core"
```

- **素朴に書くと**：`for (const auto& [k, c] : cnt)` と[構造化束縛](../cpp/cpp-structured-bindings.md)で受けて、`k` だけを使うのと同じである
- **版**：C++20。g++-13・g++-15 で使える
- **落とし穴**：見えるのは元の要素への参照である。`for (auto& c : cnt | views::values) c *= 10;` と書くと、元の `map` の値が書き換わる（手元で確かめた）

## split と join：文字列を区切る、vector の vector を平らにする {#split-join}

`s | views::split(' ')` は文字列 `s` を空白で区切った部分を順に見る view である。各部分 `w` は文字列ではなく部分範囲（view）なので、`string_view(w)` を経て `string` にする。

```cpp
--8<-- "cpp-views-basics/split-join.cpp:split"
```

区切り方は次のとおりで、手元の g++-13・g++-15 で同じだった。

| 入力 | 部分の数 | 部分 |
| --- | --- | --- |
| `ab cd e` | 3 | `ab`・`cd`・`e` |
| `a  b`（空白 2 個） | 3 | `a`・空・`b` |
| `a `（末尾に空白） | 2 | `a`・空 |
| 空文字列 | 0 | なし |

`views::join` は逆向きの操作で、`vector<vector<int>>` のような範囲の範囲を 1 列に並べて見る。空の内側は飛ばされる。

```cpp
--8<-- "cpp-views-basics/split-join.cpp:join"
```

- **版**：`split` と `join` は C++20。ただし `string_view(w)`（範囲から `string_view` を作るコンストラクタ）は C++23 で、`-std=gnu++20` では g++-13・g++-15 ともコンパイルエラーになる。AtCoder の `-std=gnu++23` なら通る。C++20 では、イテレータの組から文字列を作る

```cpp
--8<-- "cpp-views-basics/split-cxx20.cpp:core"
```

- **落とし穴**：連続した空白や末尾の空白で、空の部分ができる。空白区切りの入力を読むだけなら、`cin >>` で 1 語ずつ読むほうが確実である（文字列の操作は[文字列の操作](../cpp/cpp-string-api.md)）

## common：イテレータの組を取る古いコンストラクタに渡すとき {#common}

`vector<int> b(r.begin(), r.end());` のように、イテレータの組を取るコンストラクタは、`begin` と `end` が同じ型であることを求める。`take_while` などの view は、終わりを「終わりに来たかを判定するだけの別の型」（[番兵](../guide/glossary.md#sentinel)。`take_while` なら条件が偽になったかを調べる物）で表すので、そのまま渡すとコンパイルエラーになる。

```cpp
--8<-- "cpp-views-basics/common-ng.cpp:core"
```

g++-15 のエラーは `no matching function for call to 'std::vector<int>::vector(…)'` である。2 つ目の引数の型は `take_while_view<…>::_Sentinel<true>` と出る。`| views::common` を挟むと、`begin` と `end` の型がそろって通る。

```cpp
--8<-- "cpp-views-basics/common-ok.cpp:core"
```

- **版**：C++20。g++-13・g++-15 で、挟まないとエラー・挟むと通るのは同じだった
- **使い分け**：`r | ranges::to<vector>()`（C++23）なら `common` なしで `vector` にできる。g++-15 と AtCoder の GCC 15.2 にはあり、g++-13 にはない（[C++23 の views](../cpp/cpp-views-cpp23.md)）。`common` が要るのは、イテレータの組しか取らない関数に渡すときである

## view の寿命：元のコンテナより長く使わない {#lifetime}

左辺値（名前の付いた変数）を流した view は、元のコンテナを参照するだけで、中身を持たない。元のコンテナが消えた後に view を使うと、消えたメモリを読む未定義動作になる。典型は、関数の中の変数を流した view を返す書き方である。

```cpp
--8<-- "cpp-views-basics/lifetime.cpp:bad"
```

この関数の結果を回すと、手元の g++-13・g++-15 では `-Wall -Wextra` でも警告が出なかった。AddressSanitizer（`-fsanitize=address`）を付けると `stack-use-after-return` で止まった。警告に頼れないので、書き方で避ける。

一方、右辺値（関数の戻り値などの一時オブジェクト）のコンテナをパイプに流すと、コンテナは view の中に移される（`owning_view`）。view が生きている間はコンテナも生きているので安全である。

```cpp
--8<-- "cpp-views-basics/lifetime.cpp:good"
```

範囲 for に直接書く場合も、一時オブジェクトはループの間ずっと生きている。

```cpp
--8<-- "cpp-views-basics/lifetime.cpp:core"
```

- **版**：C++20。g++-13・g++-15 で、右辺値を流す書き方は AddressSanitizer でも問題が出なかった
- **落とし穴**：左辺値を流した view を、関数の戻り値やグローバル変数にして元より長く持たない。view は使う直前に作り、その場で回し切るのが安全である

## 確認問題 {#quiz}

??? question "確認問題：`n` が `long long` で $3 \times 10^9$ のとき、`for (long long i : views::iota(0, n))` は正しく回るか？"
    回らない。要素の型は始まりの `0` の型 `int` で決まる。受ける変数を `long long` にしても、作られる値は `int` のままである。$2^{31} - 1$ を超えるところであふれる。`views::iota(0LL, n)` と書く。

??? question "確認問題：`v = make(n); return v | views::filter(p);` と `return make(n) | views::filter(p);` はどちらが安全か？"
    後者である（`v` は関数の中の変数とする）。前者は名前の付いた `v` を流すので、view は `v` を参照するだけで、関数を出ると `v` が消えて壊れる。後者は一時オブジェクトを流すので、`vector` が view の中に移されて view と一緒に生きる。

## 参考 {#references}

- [cppreference「std::ranges::views::iota, std::ranges::iota_view」](https://en.cppreference.com/cpp/ranges/iota_view)：`iota` の型の決まり方と、C++26 の `views::indices`
- [cpprefjp「iota_view」](https://cpprefjp.github.io/reference/ranges/iota_view.html)：日本語で読める `iota` の説明
- [cpprefjp「split_view」](https://cpprefjp.github.io/reference/ranges/split_view.html)：`split` の各部分の型
- [cpprefjp「owning_view」](https://cpprefjp.github.io/reference/ranges/owning_view.html)：右辺値を流したときにコンテナが view の中に移されること
- [cpprefjp「common_view」](https://cpprefjp.github.io/reference/ranges/common_view.html)：`begin` と `end` の型をそろえる view
- [GCC「libstdc++ Implementation Status」](https://gcc.gnu.org/onlinedocs/libstdc++/manual/status.html)：各機能が入った GCC の版
