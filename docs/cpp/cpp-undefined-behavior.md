---
id: cpp-undefined-behavior
title: 未定義動作とダングリング
aliases: [未定義動作, UB, undefined behavior, 範囲外アクセス, 未初期化変数, 初期化忘れ, ゴミの値, ダングリング, dangling reference, use-after-free, 参照の無効化, 一時オブジェクトの寿命, pq.top() の参照, _GLIBCXX_DEBUG, _GLIBCXX_ASSERTIONS, -fsanitize=address, AddressSanitizer, UndefinedBehaviorSanitizer, デバッグ用ビルド, assert]
type: cpp
field: cpp
chapter: 入出力・環境・落とし穴
order: 200
level: 基礎
kind: [実装・C++]
prerequisites: [cpp-environment, cpp-integer-overflow, cpp-structured-bindings]
related: [cpp-range-for, cpp-comparators, cpp-container-idioms, cpp-macros-template-file, debugging-checklist, stress-testing, dijkstra, cpp-reverse-index#symptoms]
summary: あふれ・範囲外・未初期化変数・ダングリングなどの未定義動作が、-O2 や手元と AtCoder で結果を変える仕組みを知り、デバッグ用のビルドで見つける。ダングリングの 4 つの型も示す。
complexity: '避ける書き方（初期値を書く・値で受ける・添字で書く）に実行時の費用はない。見つける道具を付けたビルドは遅い（書き方で変わるが、手元の例で -O2 の数倍〜十数倍、_GLIBCXX_DEBUG を足すと数十〜数百倍）'
signs: []
acl: []
sections:
  - {title: 未定義動作とは：何が起きてもよく、最適化の前提に使われる（手元と AtCoder、-O0 と -O2 で結果が変わる）, anchor: what-is-ub}
  - {title: 他の行まで壊す：あふれる式があると、-O2 では正しく書いた別の式の値まで変わる, anchor: breaks-other-lines}
  - {title: 配列の範囲外：既定では止まらない, anchor: out-of-range}
  - {title: 未初期化変数：手元では不定、AtCoder では 0 になる（-Wall は配列の未初期化を見落とす）, anchor: uninitialized}
  - {title: ダングリングとは：寿命の切れたものを指す参照・イテレータ・string_view, anchor: dangling}
  - {title: ダングリング①：pq.top() を参照で受けて pop すると値が変わる（値で受ける）, anchor: dangling-pq-top}
  - {title: ダングリング②：要素への参照を持ったまま push_back すると、再確保で消えた領域を指す, anchor: dangling-reallocation}
  - {title: ダングリング③：範囲 for の一時オブジェクト（変数に受けてから回す）, anchor: dangling-temporary}
  - {title: ダングリング④：string_view に一時的な string を入れる, anchor: dangling-string-view}
  - {title: そのほかの未定義動作：比較関数の誤り・型の幅以上のシフト・__builtin_ctz(0)・ループ中のコンテナの変更, anchor: other-ub}
  - {title: 見つける道具と見つけられるもの：警告・アサーション・デバッグモード・サニタイザ, anchor: detection-tools}
  - {title: 不具合を探すビルドを cph とは別に用意する, anchor: debug-build}
  - {title: assert で WA を RE に変えて気づく（AtCoder では NDEBUG が付かない）, anchor: assert}
stage: reviewed
updated: 2026-10-22
cpp_std: null
gcc_min: null
atcoder: null
---

!!! abstract "要点"
    - **何ができるか**：あふれ・範囲外・未初期化変数・ダングリングなどの未定義動作が、-O2 や手元と AtCoder で結果を変える仕組みを知り、デバッグ用のビルドで見つける。ダングリングの 4 つの型も示す。
    - **いつ使うか**：
        - 手元と AtCoder で結果が違う。`-O0` と `-O2` で結果が違う。
        - 答えに関係のない行や `cerr` の出力を足すと答えが変わる。
        - ダイクストラ法の距離がおかしい、`push_back` の後で値が壊れる。
    - **計算量**：避ける書き方（初期値を書く・値で受ける・添字で書く）に実行時の費用はない。見つける道具を付けたビルドは遅い（書き方で変わるが、手元の例で `-O2` の数倍〜十数倍、`_GLIBCXX_DEBUG` を足すと数十〜数百倍）
    - **前提**：[AtCoder と手元の C++ 環境](../cpp/cpp-environment.md)、[整数のオーバーフローと \_\_int128](../cpp/cpp-integer-overflow.md)、[構造化束縛と pair・tuple・optional](../cpp/cpp-structured-bindings.md)

<!-- textlint-disable -->
別名：未定義動作・UB・undefined behavior・範囲外アクセス・未初期化変数・初期化忘れ・ゴミの値・ダングリング・dangling reference・use-after-free・参照の無効化・一時オブジェクトの寿命・pq.top() の参照・_GLIBCXX_DEBUG・_GLIBCXX_ASSERTIONS・-fsanitize=address・AddressSanitizer・UndefinedBehaviorSanitizer・デバッグ用ビルド・assert
<!-- textlint-enable -->

[未定義動作](../guide/glossary.md#undefined-behavior)は、C++ の規格が「どうなるかを決めない」とした操作である。範囲外の読み書きや符号付き整数のあふれがこれにあたり、手元で合っていても AtCoder で WA になる、という事故の多くはここから来る。未定義動作は書き方で避け、残ったものはデバッグ用のビルドで見つける。

このページのコードは `#include <bits/stdc++.h>` と `using namespace std;` を前提にする。例はすべて手元の g++-13 と g++-15（`-std=gnu++23`）で確かめた。AtCoder の GCC 15.2 のオプションは `-std=gnu++23 -O2 -Wall -Wextra -ftrivial-auto-var-init=zero` などである（[AtCoder と手元の C++ 環境](../cpp/cpp-environment.md#options)）。

## 未定義動作とは：何が起きてもよく、最適化の前提に使われる（手元と AtCoder、-O0 と -O2 で結果が変わる） {#what-is-ub}

未定義動作を含むプログラムは、規格の上では何をしてもよい。止まる・ゴミの値を出す・正しく動くのどれも「規格どおり」である。だから「手元で正しく動いた」ことは、未定義動作がないことの証拠にならない。

コンパイラは逆に「未定義動作は起きない」と仮定して最適化する。たとえば「符号付き整数はあふれない」と仮定してよいので、`x + 1 > x` を常に真とみなしたり、あふれたときにだけ偽になる条件を消したりする。最適化の強さで消し方が変わるので、`-O0` と `-O2` で結果が変わる。

結果が変わる場面は、おもに次の 3 つである。

| 違い | 起きること | 例 |
| --- | --- | --- |
| `-O0` と `-O2` | 最適化が未定義動作を前提に式を消す | [あふれるループの条件が消える](#breaks-other-lines) |
| 手元と AtCoder | オプションの違いで、未初期化の値やメモリの並びが変わる | [未初期化変数が AtCoder だけ 0 になる](#uninitialized) |
| 関係のない行の有無 | 変数の置き場所や最適化の判断が変わる | `cerr` を足すと答えが変わる |

- **落とし穴**：「`cerr` を足したら直った」は直っていない。未定義動作の現れ方が変わっただけなので、[見つける道具](#detection-tools)で原因の行を探す

## 他の行まで壊す：あふれる式があると、-O2 では正しく書いた別の式の値まで変わる {#breaks-other-lines}

未定義動作の影響は、その式の値だけにとどまらない。次のループは `i` を 2 倍し続け、`int` からあふれて負になったら止まるつもりで書いてある。

```cpp
--8<-- "cpp-undefined-behavior/ub-loop.cpp:core"
```

$x = 1$ のとき、`-O0` では 31 回で止まり 31 と出る。`-O2` では止まらず、打ち切りの `loop` が出る（g++-13・g++-15 で同じ。警告は出ない）。コンパイラは「`i` は正の数を 2 倍してもあふれない」と仮定してよいので、「`i` はずっと正」と推論して条件 `i > 0` を消した。条件そのものは正しく書けているのに、あふれる式 `i *= 2` のせいで壊れたのである。

直すには、あふれる前に止める。広い型で計算し、範囲を条件で確かめれば、どの最適化でも 31 になる。

```cpp
--8<-- "cpp-undefined-behavior/ub-loop-fixed.cpp:core"
```

- **見つけ方**：`-fsanitize=undefined` を付けると、あふれた行を教えてくれる。メッセージは `signed integer overflow: 1073741824 * 2 cannot be represented in type 'int'` である
- **関連**：あふれる式があると、正しく計算した別の値との比較まで変わる例は[符号付き整数のあふれは未定義動作](../cpp/cpp-integer-overflow.md#signed-overflow-ub)にある。あふれの直し方は同じページ

## 配列の範囲外：既定では止まらない {#out-of-range}

`vector` の `[]` と生の配列は、添字が範囲内かを調べない。範囲外に書き込んでも、多くの場合はそのまま進む。次のコードは $n = 3$, $i = 3$ でも `100` と出て正常に終わる（g++-13・g++-15 の `-O2`）。

```cpp
--8<-- "cpp-undefined-behavior/out-of-range.cpp:core"
```

範囲外に書いた値は、隣にある別の変数や、メモリの管理に使う領域を壊す。壊れた場所によって、すぐ落ちる・ずっと後で落ちる・黙って答えが変わる、のどれにもなる。「Segmentation fault にならないから範囲内」とは言えない。

- **見つけ方**：`-D_GLIBCXX_ASSERTIONS` を付けると、`vector` の `[]` で `Assertion '__n < this->size()' failed.` と出て止まる。生の配列（`int c[3]`）はこの検査の対象外である。生の配列は `-fsanitize=address`（`global-buffer-overflow` など）か `-fsanitize=undefined`（`index 3 out of bounds`。大きさが型で分かる配列だけ）で見つかる
- **版**：GCC 15 から、最適化なし（`-O0`、VS Code の `-g` だけのビルドもこれ）では `_GLIBCXX_ASSERTIONS` が自動で付く。手元の g++-15 の `-O0` では、上のコードが何も付けずに止まった。g++-13 の `-O0` と、`-O2`（AtCoder・cph）では止まらない
- **落とし穴**：`a.at(i)` は範囲外で例外を投げるので止まるが、解説コードではほとんど使わない。`[]` のまま、手元でだけ検査を付けるほうが速さを失わない

## 未初期化変数：手元では不定、AtCoder では 0 になる（-Wall は配列の未初期化を見落とす） {#uninitialized}

関数の中で宣言した `int`・`long long`・`double` などの変数と、その配列（自動変数）は、初期値を書かなければ値が決まらない。読むと未定義動作で、手元ではゴミの値になる。グローバル変数と `vector<int> a(n)` は 0 で初期化されるので、この問題はない。`string s;` や `vector<int> v;` も空で作られる。

AtCoder の GCC には `-ftrivial-auto-var-init=zero` が付いていて、初期値のない自動変数を 0 で埋める。そのため、初期化を忘れたコードが AtCoder では AC し、手元では答えが合わない。初期値を書けば、手元でも AtCoder でも同じ答えになる。次の関数は文字の出現回数の配列 `cnt` を初期化していない。

```cpp
--8<-- "cpp-undefined-behavior/uninit-array.cpp:core"
```

入力 `abcab` の正しい答えは $2^2 + 2^2 + 1^2 = 9$ である。手元の結果は次のとおりだった。

| ビルド | 結果 | `-Wall -Wextra` の警告 |
| --- | --- | --- |
| `-O2`（g++-13・g++-15） | 3956798619723922246 などのゴミの値 | なし |
| `-O2 -ftrivial-auto-var-init=zero`（AtCoder と同じ） | 9 | なし |

配列を `cnt[c - 'a']++` のように実行時に決まる添字で使うと、`-Wall -Wextra` でも警告されない（添字が定数で、読むだけなら警告される）。次のようにループの中で足していく変数は、`-O2` でだけ `'s' may be used uninitialized` と警告される（`-O0` では出ない。宣言の直後に読むだけなら `-O0` でも警告される）。

```cpp
--8<-- "cpp-undefined-behavior/uninit-scalar.cpp:core"
```

どちらも、宣言のときに初期値を書けば直る。`array` と生の配列は `{}` で 0 になる。

```cpp
--8<-- "cpp-undefined-behavior/uninit-fixed.cpp:core"
```

- **見つけ方**：AddressSanitizer と UndefinedBehaviorSanitizer はどちらも未初期化の読み出しを見つけない（手元では、道具を付けたビルドで上の関数がたまたま 9 を返した）。手元で `-ftrivial-auto-var-init=pattern` を付けると、毎回同じ不自然な値（上の例では 7375861463932509）で埋まるので、AtCoder との違いに気づきやすい
- **落とし穴**：`-ftrivial-auto-var-init=zero` を手元にも付ければ AtCoder と同じ答えになるが、規格の上では未定義動作のままである。0 で埋めることに頼らず、初期値を書く習慣で防ぐ
- **落とし穴**：テストケースごとに使い回す配列（多くのテストケースを読む問題）は、ケースの最初に 0 へ戻す。これは未定義動作ではないが、同じ「初期化忘れ」の症状になる

## ダングリングとは：寿命の切れたものを指す参照・イテレータ・string_view {#dangling}

[ダングリング](../guide/glossary.md#dangling)は、参照・イテレータ・ポインタ・`string_view` が、もう存在しない物（寿命の切れた物）を指している状態である。そこを読み書きすると未定義動作になる（use-after-free）。参照やイテレータは「指す先の場所」だけを持ち、指す先が消えても自分では気づかない。

競プロで起きるダングリングは、次の 4 つの型にほぼ収まる。どれも「参照を取った後で、指す先を変える操作をした」か「すぐ消える物に参照を取った」かである。

| 型 | 指す先が消える（変わる）操作 | 道具で見つかるか |
| --- | --- | --- |
| [① `pq.top()` の参照](#dangling-pq-top) | `pop` で先頭の場所に別の要素が入る | 見つからない |
| [② `vector` の要素への参照](#dangling-reallocation) | `push_back` の再確保で要素が移る | AddressSanitizer |
| [③ 範囲 for の一時オブジェクト](#dangling-temporary) | ループの前に一時的な `vector` が消える | AddressSanitizer |
| [④ `string_view` に一時的な `string`](#dangling-string-view) | 文の終わりで `string` が消える | AddressSanitizer |

手元の g++-13・g++-15 では、このページの 4 つの例のどれも `-Wall -Wextra` で警告が出なかった。避け方は共通で、参照を長く持たずに値で受けるか、使うたびに取り直すかである。

## ダングリング①：pq.top() を参照で受けて pop すると値が変わる（値で受ける） {#dangling-pq-top}

`pq.top()` は、優先度付きキューが中に持つ `vector` の先頭の要素への参照を返す。参照で受けてから `pop` すると、先頭の場所に次の要素が移ってくるので、受けた値が変わる。

```cpp
--8<-- "cpp-undefined-behavior/pq-top.cpp:core"
```

キューに要素が 2 個以上あれば、指している場所の要素はまだ存在するので、厳密には未定義動作ではない。「別の要素の値に変わる」と決まった動作である。だから AddressSanitizer も `_GLIBCXX_DEBUG` も止めず、いつも同じ間違った値が出る。要素が 1 個なら指す先が消えて未定義動作になる。それでも `vector` の領域は解放されないので、AddressSanitizer などの道具では見つからなかった（g++-15 の `-O2` でだけ `-Wuninitialized` の警告が出た）。

道具に頼れないので、書き方で防ぐ。[ダイクストラ法](../graph/dijkstra.md)のループは、先頭を値で受けてから `pop` する形に決めておく。

```cpp
--8<-- "cpp-undefined-behavior/dijkstra-pop.cpp:core"
```

- **費用**：(距離, 頂点) のコピーは 16 バイト程度で、気にしなくてよい
- **関連**：構造化束縛の見えない変数が参照になる仕組みは[構造化束縛の節](../cpp/cpp-structured-bindings.md#pq-top-reference)にある

## ダングリング②：要素への参照を持ったまま push_back すると、再確保で消えた領域を指す {#dangling-reallocation}

`vector` は、容量が足りなくなると、より大きな領域を新しく確保して要素を移し、古い領域を解放する（再確保）。再確保の前に取った参照・イテレータは古い領域を指したまま残る。

![vector の再確保の図。上は auto& row = g[0] の直後で、row が g の唯一の要素 g[0] を指している。下は g.push_back({2}) の後で、要素は容量 2 の新しい領域へ移り、古い領域は解放済みになったが、row は古い領域を指したまま](../img/cpp-undefined-behavior/reallocation.svg)

```cpp
--8<-- "cpp-undefined-behavior/reallocation.cpp:bad"
```

`row.push_back(3)` は解放済みの領域を書き換える。手元では `-O2` で Segmentation fault になり、`-fsanitize=address` では `heap-use-after-free` と出た（`_GLIBCXX_DEBUG` は見つけなかった）。`push_back` のほかに `insert`・`emplace_back`・`resize` も再確保を起こしうる。

参照を持ち続けず、使うたびに添字で `g[0]` と書けば安全である。

```cpp
--8<-- "cpp-undefined-behavior/reallocation.cpp:core"
```

- **応用の型**：BFS のキューを `vector` で書くと、回しながら `push_back` する。範囲 for や参照で回さず、添字 `for (int i = 0; i < (int)q.size(); i++)` で回す（[ループの中で同じ vector に追加しない](../cpp/cpp-range-for.md#modify-in-loop)）
- **落とし穴**：`reserve` で容量を先に取れば再確保は起きないが、要素数の見積もりを誤ると壊れる。参照を持たない書き方のほうが確実である
- **関連**：`set`・`map` の参照は、その要素を消すまで無効にならない（[イテレータと参照の無効化](../cpp/cpp-container-idioms.md#invalidation)）

## ダングリング③：範囲 for の一時オブジェクト（変数に受けてから回す） {#dangling-temporary}

範囲 for は、範囲の式を参照で受けてから回す。`for (int v : groups(n)[0])` では、`groups(n)` が返した[一時オブジェクト](../guide/glossary.md#temporary-object)の `vector<vector<int>>` から `[0]` を取り、その参照で回す。C++20 までの規則では、外側の一時的な `vector` はループが始まる前に消えるので、`[0]` の参照はダングリングになる。ACL の `dsu` の `d.groups()[0]` も同じ形である。

C++23 の規則は、範囲の式の中の一時オブジェクトをループの終わりまで生かすように変わり、GCC 15 で入った。手元の結果は次のとおりで、どれも警告は出なかった。

| コンパイラと版 | `-fsanitize=address` の結果 |
| --- | --- |
| g++-15 `-std=gnu++23`（AtCoder と同じ） | 正しく動く |
| g++-15 `-std=gnu++20` | `heap-use-after-free` |
| g++-13 `-std=gnu++23` | `heap-use-after-free` |

AtCoder では動くが、古い環境や解説の写し方によっては壊れる。変数に受けてから回せば、どの版でも安全である。

```cpp
--8<-- "cpp-undefined-behavior/temporary-range.cpp:core"
```

- **安全な形**：関数の戻り値そのものを回す `for (int x : make(n))` は、どの版でも安全である。危ないのは、戻り値の「中身」（`[0]`・`.first`・参照を返すメンバ関数の戻り値）を回すときだけ
- **関連**：寿命が延びる規則の詳しい説明は[範囲に一時オブジェクトの中身を渡すとき](../cpp/cpp-range-for.md#temporary-range)にある

## ダングリング④：string_view に一時的な string を入れる {#dangling-string-view}

`string_view` は文字列をコピーせず、元の文字列の場所と長さだけを持つ。関数が返した `string` を直接 `string_view` に入れると、その `string` は文の終わりで消え、`string_view` は消えた文字列を指す。

```cpp
--8<-- "cpp-undefined-behavior/string-view.cpp:bad"
```

手元の `-O2` では、長い文字列は先頭が化けて出たが、短い文字列は正しく出た（たまたまである）。どちらも正常に終わった。`-fsanitize=address` を付けると、長い文字列は `heap-use-after-free`、短い文字列は `stack-use-after-scope` と出た（短い `string` は文字を自分の中に持つため）。文字列そのものは `string` の変数に持ち、`string_view` はその変数が生きている間だけ使う。

```cpp
--8<-- "cpp-undefined-behavior/string-view.cpp:core"
```

- **落とし穴**：`string_view` を返す関数で、関数の中の `string` を指して返すのも同じ事故である。競プロでは、読むだけの引数を `const string&` の代わりに受ける程度にとどめる
- **関連**：view を関数から返すときの同じ事故は[view の寿命](../cpp/cpp-views-basics.md#lifetime)にある

## そのほかの未定義動作：比較関数の誤り・型の幅以上のシフト・__builtin_ctz(0)・ループ中のコンテナの変更 {#other-ub}

競プロのコードで起きやすい未定義動作を、見つける道具と並べる。

| 書き方 | 何が起きるか | 見つける道具 | 詳しく |
| --- | --- | --- | --- |
| `sort` の比較関数に `<=` | 範囲外を読んで落ちる・壊れる | `_GLIBCXX_DEBUG`、AddressSanitizer | [比較関数の約束](../cpp/cpp-comparators.md#less-equal-pitfall) |
| `1u << k` で $k \ge 32$ | 手元では $k = 32$ で 1 になった | UndefinedBehaviorSanitizer | [シフトの幅](../cpp/cpp-integer-overflow.md#shift-width) |
| `__builtin_ctz(0)` | 決まった値を返さない | UndefinedBehaviorSanitizer | [組み込み関数](../cpp/cpp-math-functions.md#builtins) |
| 範囲 for の中で同じ `vector` に `push_back` | 再確保で回しているイテレータが壊れる | `_GLIBCXX_DEBUG`、AddressSanitizer | [ループの中で同じ vector に追加しない](../cpp/cpp-range-for.md#modify-in-loop) |

シフトの幅は、x86-64 の命令が幅を 32（64 bit の型なら 64）で割った余りを使うので、$k = 32$ でも 0 にならず 1 になる。ただし手元でそうなったというだけで、定数で書くとコンパイル時に別の値へ畳み込まれることもある。

```cpp
--8<-- "cpp-undefined-behavior/shift-ctz.cpp:core"
```

- **直し方**：シフトは幅の足りる型を使い（`1LL << k`）、$k$ が 64 以上になりうるなら先に場合分けする。最下位の 1 の位置は `countr_zero`（C++20。符号なし整数だけ受ける）で求める。0 を渡すと型の幅を返すと決まっている
- **見つけ方**：ループ中の `push_back` は `_GLIBCXX_DEBUG` で `attempt to increment a singular iterator` と出て止まった

## 見つける道具と見つけられるもの：警告・アサーション・デバッグモード・サニタイザ {#detection-tools}

道具ごとに見つけられるものが違う。このページの例を手元の g++-13・g++-15 で試した結果は次のとおりで、両者は同じだった（○は止まるか警告が出た、×は何も出なかった）。

| 例 | `_GLIBCXX_ASSERTIONS` | `_GLIBCXX_DEBUG` | address | undefined |
| --- | --- | --- | --- | --- |
| 符号付き整数のあふれ | × | × | × | ○ |
| `vector` の範囲外 | ○ | ○ | ○ | × |
| 生の配列の範囲外 | × | × | ○ | ○ |
| 未初期化の変数・配列 | × | × | × | × |
| 比較関数の `<=` | × | ○ | ○（要素が多いとき） | × |
| シフトの幅・`__builtin_ctz(0)` | × | × | × | ○ |
| ダングリング②③④ | × | × | ○ | × |
| ダングリング①（`pq.top()`） | × | × | × | × |

表の列の address は `-fsanitize=address`、undefined は `-fsanitize=undefined` である。`-Wall -Wextra` が警告するのは、単純な未初期化の読み出し（ループで足す変数は `-O2` でだけ）と、定数の添字の範囲外（`array subscript 3 is above array bounds`）くらいである。実行時の添字で使う配列の未初期化、あふれ、ダングリングは、このページの例ではどれも警告されなかった。

- **`-D_GLIBCXX_ASSERTIONS`**：標準ライブラリの前提の検査（`vector` の `[]` の範囲・空の `front` など）を有効にする。遅くなりにくい
- **`-D_GLIBCXX_DEBUG`**：コンテナとイテレータを検査付きのものに置き換える。`ASSERTIONS` の検査に加えて、比較関数の誤りや無効になったイテレータも見つけるが、とても遅くなる
- **`-fsanitize=address`**（AddressSanitizer）：範囲外の読み書きと、解放済みの領域の読み書き（use-after-free）を見つける。`heap-buffer-overflow`・`heap-use-after-free` のように種類と行を出して止まる
- **`-fsanitize=undefined`**（UndefinedBehaviorSanitizer）：あふれ・シフトの幅・`__builtin_ctz(0)` などを見つける。既定では `runtime error:` を出した後も実行を続けるので、出力の答えだけを見ていると見落とす。`-fno-sanitize-recover=all` を足すと、最初の 1 件で止まる
- **落とし穴**：道具で何も出なくても、未定義動作がないとは言えない。道具が見るのは、その入力で実際に通った行だけである。小さいケースを大量に試す[ランダムテスト](../guide/stress-testing.md#procedure)と組み合わせる

## 不具合を探すビルドを cph とは別に用意する {#debug-build}

ふだんのビルド（cph で AtCoder と同じ `-O2`）とは別に、不具合を探すためのビルドを 1 つ用意しておく。答えが合わない・落ちるときに、同じ入力をこちらで動かす。

```text
g++-15 -std=gnu++23 -O1 -g -Wall -Wextra -D_GLIBCXX_DEBUG -fsanitize=address,undefined -DLOCAL a.cpp -o a_debug
./a_debug < in.txt
```

- `-O1 -g`：止まったときに行番号が分かる。`-O0` より速く、`-O2` ほど式が消えない
- `-D_GLIBCXX_DEBUG`：遅すぎるときは `-D_GLIBCXX_ASSERTIONS` に替える（比較関数の誤りと無効なイテレータは見つからなくなる）
- `-DLOCAL`：`#ifdef LOCAL` で囲んだデバッグ出力を有効にする（[手元だけのデバッグ出力](../cpp/cpp-macros-template-file.md#ifdef-local)）
- 加えてよいもの：`-fno-sanitize-recover=all`（UndefinedBehaviorSanitizer の最初の報告で止める）と `-ftrivial-auto-var-init=pattern`（[未初期化変数](#uninitialized)を目立つ値で埋める）。手元では、すべてを合わせたビルドも動いた

**遅くなる**：手元で、長さ $2 \times 10^5$ の配列のソートと $4 \times 10^8$ 回のループを含むコードを比べた。ふだんの `-O2` で 0.08 秒、上のビルドで約 15 秒、`_GLIBCXX_DEBUG` を `_GLIBCXX_ASSERTIONS` に替えて約 0.9 秒だった。倍率は書き方で大きく変わり、別の例では約 3 倍と約 65 倍だった。目安は、`ASSERTIONS` 版で数倍〜十数倍、`_GLIBCXX_DEBUG` 版で数十〜数百倍である。大きいケースではなく、落ちる小さいケースを探してから動かす。

- **落とし穴**：プリコンパイル済みヘッダ（`~/pch`）は作ったときと同じオプションでしか使われない。そのため、このビルドではコンパイルに毎回数秒かかる（[プリコンパイル済みヘッダ](../cpp/cpp-environment.md#pch)）
- **落とし穴**：深い再帰で落ちるのは未定義動作ではなくスタックの不足である。手元で試す前に `ulimit -s unlimited` を実行する（[AtCoder と手元の C++ 環境](../cpp/cpp-environment.md#stack-depth)）

## assert で WA を RE に変えて気づく（AtCoder では NDEBUG が付かない） {#assert}

`assert(条件);` は、条件が偽なら `Assertion '条件' failed.` と出してプログラムを止める。「ここではこうなっているはず」という思い込みを書いておけば、思い込みが崩れたとき、黙って WA になる代わりに RE で止まる。

```cpp
--8<-- "cpp-undefined-behavior/assert.cpp:core"
```

AtCoder のオプションには `-DNDEBUG` が含まれないので、`assert` は提出したコードでも有効である。ジャッジの結果が WA ではなく RE なら、思い込みの崩れるテストケースがあると分かる。

- **使いどころ**：入力の制約（$1 \le N \le 2 \times 10^5$）、二分探索の前の単調性やソート済み、配列の添字の範囲、DP の値が負にならないこと、答えの候補が見つかったこと
- **費用**：条件を 1 回計算するだけである。ただし `is_sorted` のように $O(N)$ かかる条件をループの中に置くと、計算量が変わる
- **落とし穴**：`assert` の中に、副作用のある式（`assert(st.insert(x).second)` など）を書かない。`NDEBUG` を付けたビルドでは式ごと消える。`import std;` だけでは `assert` が使えない（[import std;](../cpp/cpp-macros-template-file.md#import-std)）

## 確認問題 {#quiz}

??? question "確認問題：`-O0` では合うのに `-O2` では答えが変わる。何を疑うか。"
    未定義動作を疑う。特に符号付き整数のあふれと配列の範囲外である。コンパイラは未定義動作が起きないと仮定して最適化するので、最適化の強さで結果が変わる。`-fsanitize=address,undefined` を付けたビルドで同じ入力を動かし、止まった行を見る。

??? question "確認問題：`long long sum;` と書いて足し始めたコードが AtCoder で AC した。手元で答えが変になる理由は？"
    `sum` が初期化されていないからである。AtCoder の GCC は `-ftrivial-auto-var-init=zero` で初期値のない自動変数を 0 で埋めるので、たまたま正しく動いた。手元にはこのオプションがないので、ゴミの値から足し始める。`long long sum = 0;` と書く。

??? question "確認問題：ダイクストラ法で `const auto& [d, v] = pq.top(); pq.pop();` と書くと何が起きるか。AddressSanitizer で見つかるか。"
    `d`・`v` はキューの先頭の場所を指す参照なので、`pop` の後は次に小さい要素の値になる。取り出した要素とは違う距離・頂点で処理が進み、答えが変わる。要素が残っている間は未定義動作ではなく、決まった動作なので、AddressSanitizer でも `_GLIBCXX_DEBUG` でも見つからない。`auto [d, v] = pq.top();` と値で受ける。

??? question "確認問題：`for (int v : d.groups()[0])` が手元の g++-13 で壊れて、AtCoder では動く理由は？"
    `d.groups()` が返す一時的な `vector` の寿命の規則が、C++23 で変わったからである。C++20 までの規則では、ループの前に一時的な `vector` が消え、`[0]` の参照がダングリングになる。C++23 の規則（GCC 15 から）では、ループの終わりまで生きる。AtCoder は GCC 15.2 の `-std=gnu++23` なので動く。`auto gs = d.groups();` と変数に受けてから回せば、どこでも動く。

??? question "確認問題：AddressSanitizer と UndefinedBehaviorSanitizer を付けて何も出なかった。未定義動作はないと言えるか。"
    言えない。道具が調べるのは、その入力で実際に実行された操作だけである。また、未初期化変数の読み出しや `pq.top()` の参照のように、どちらの道具でも見つからないものもある。初期値を書く・参照を長く持たないといった書き方で防ぎ、小さいケースのランダムテストと組み合わせる。

## 参考 {#references}

- [cppreference「Undefined behavior」](https://en.cppreference.com/w/cpp/language/ub)：未定義動作の定義と、最適化が未定義動作を前提にする例
- [cppreference「Range-based for loop」](https://en.cppreference.com/w/cpp/language/range-for)：範囲の式の一時オブジェクトの寿命と、C++23 での変更
- [cppreference「assert」](https://en.cppreference.com/w/cpp/error/assert)：`NDEBUG` を定義すると `assert` が消えること
- [GCC「Program Instrumentation Options」](https://gcc.gnu.org/onlinedocs/gcc/Instrumentation-Options.html)：`-fsanitize=address`・`-fsanitize=undefined`・`-fno-sanitize-recover`
- [GCC「Options That Control Optimization」](https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html)：`-ftrivial-auto-var-init` の `zero` と `pattern`
- [GCC「libstdc++ Macros」](https://gcc.gnu.org/onlinedocs/libstdc++/manual/using_macros.html)：`_GLIBCXX_ASSERTIONS` が最適化なしで自動で付くこと、`_GLIBCXX_DEBUG`
- [GCC「libstdc++ Debug Mode」](https://gcc.gnu.org/onlinedocs/libstdc++/manual/debug_mode_using.html)：`_GLIBCXX_DEBUG` で検査付きのコンテナに置き換わること
