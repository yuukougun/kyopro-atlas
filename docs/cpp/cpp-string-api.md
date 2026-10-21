---
id: cpp-string-api
title: 文字列の操作
aliases: [string, substr, 'string::find', npos, to_string, stoi, stoll, starts_with, ends_with, string_view, s += c, getline, c - 'a', 文字と数の変換]
type: cpp
field: cpp
chapter: コンテナ・アルゴリズム・ACL
order: 140
level: 基礎
kind: [実装・C++]
prerequisites: []
related: [string-basics, cpp-views-basics, cpp-io, cpp-undefined-behavior, run-length-encoding]
summary: std::string の操作（substr・find・+=・数との変換）と string_view を、計算量と寿命に気をつけて書く。s = s + c が全体をコピーして遅いことや、cin >> の後の getline の罠を防ぐ。
complexity: 's += c はならし O(1)、s = s + c と substr(i, len) はコピーの分、比較は O(min(|s|, |t|))、string_view の substr は O(1)'
signs: []
acl: []
sections:
  - {title: 'substr(i, len) は O(len) のコピー、find は見つからないと string::npos', anchor: substr-find}
  - {title: s += c と s = s + c（後者は毎回全体をコピーして O(|s|)。先頭に足すなら後ろに足して最後に reverse）, anchor: append}
  - {title: 文字と数の変換：c - 'a'・char('a' + i)・c - '0', anchor: char-arithmetic}
  - {title: to_string（double は小数点以下 6 桁）・stoi・stoll, anchor: to-string}
  - {title: starts_with・ends_with（C++20）、contains（C++23）, anchor: starts-with}
  - {title: 'string(n, c)・reverse・辞書順の比較', anchor: construct-compare}
  - {title: string_view：コピーしない部分文字列。一時的な string を入れると壊れる（C++17）, anchor: string-view}
  - {title: '区切る：views::split('' '') と string_view(w)（C++20）', anchor: split}
  - {title: cin で読む文字列は空白で区切られる、その後の getline は残った改行を読む, anchor: getline}
stage: draft
updated: 2026-10-21
cpp_std: null
gcc_min: null
atcoder: true
---

!!! abstract "要点"
    - **何ができるか**：`std::string` の部分の取り出し・検索・連結・数との変換と `string_view` を、計算量と寿命を間違えずに書く。`s = s + c` が毎回全体をコピーして遅いことや、`cin >>` の後の `getline` が空の行を読む罠を防ぐ。
    - **いつ使うか**：文字列を 1 文字ずつ組み立てる、部分文字列を何度も取り出す、文字を数に直して数える、空白を含む 1 行を読むとき。解説コードに `c - 'a'`・`string::npos`・`string_view` が出てきて読みたいとき。
    - **計算量**：`s += c` はならし $O(1)$、`s = s + c` と `s.substr(i, len)` はコピーの分（$O(\lvert s \rvert)$・$O(len)$）。比較は $O(\min(\lvert s \rvert, \lvert t \rvert))$。`string_view` の `substr` は $O(1)$
    - **前提**：なし

<!-- textlint-disable -->
別名：string・substr・string::find・npos・to_string・stoi・stoll・starts_with・ends_with・string_view・s += c・getline・c - 'a'・文字と数の変換
<!-- textlint-enable -->

文字列の操作は、`std::string` のメンバ関数と、文字を小さな整数として扱う書き方の組み合わせである。どれも短く書けるが、コピーが起きる所と起きない所を区別しないと、$N$ が大きいと TLE になったり、消えた文字列を読んだりする。版の注記のない書き方は C++11 までにあり、g++-13・g++-15 と AtCoder の GCC 15.2（`-std=gnu++23`）のどれでも使える。

このページのコードは `#include <bits/stdc++.h>` と `using namespace std;` を前提にする。添字は 0-indexed である。

## substr(i, len) は O(len) のコピー、find は見つからないと string::npos {#substr-find}

`s.substr(i, len)` は、`s` の $i$ 文字目から $len$ 文字を**新しい文字列にコピーして**返す。`s.find(t)` は `t` が最初に現れる位置を返し、見つからなければ `string::npos`（`size_t` の最大値）を返す。`s.find(t, q)` は位置 $q$ 以降から探すので、`q + 1` から探し直せば重なりも含めてすべての位置を列挙できる。

```cpp
--8<-- "cpp-string-api/substr-find.cpp:core"
```

入力 `abababa aba` なら、`bab`・`bababa`・`0` と出て、`aba` の出現位置は 0・2・4 の 3 個になる。

- **境界**：`len` が残りの文字数より長ければ、あるだけを返す（`"hello".substr(3, 100)` は `lo`）。`i == s.size()` なら空文字列で、`i > s.size()` なら `out_of_range` の例外が投げられ、捕まえなければ実行時エラー（RE）になる
- **落とし穴 1**：`substr` はループの中で使うと、1 回ごとにコピーの分だけかかる。長さ $N$ の文字列の全位置で長さ $K$ の部分を取り出すと $O(NK)$ である。部分を比べるだけなら、[string_view](#string-view) の `substr`（$O(1)$）を使うか、比べる回数そのものを減らす（[ローリングハッシュ](../string/rolling-hash.md)・[Z-algorithm](../string/z-algorithm.md)）
- **落とし穴 2**：`find` の戻り値は符号なしの `size_t` なので、`s.find(t) >= 0` は常に真である。`-Wextra` で `comparison of unsigned expression in '>= 0' is always true` と警告が出る。`string::npos` と比べる。`int p = s.find(t);` と受けると、見つからないとき $p = -1$ になり `p == -1` で判定できるが、符号なしの値を `int` に詰める書き方なので `npos` と比べるほうが安全である（符号なしの罠は[オーバーフロー](../cpp/cpp-integer-overflow.md#unsigned-size)）

```cpp
--8<-- "cpp-string-api/find-ng.cpp:core"
```

- **落とし穴 3**：`find` の計算量は規格で決まっていない。libstdc++ の実装は位置ごとに比べ直すので、最悪 $O(\lvert s \rvert \lvert t \rvert)$ になる。手元で、`a` が $2 \times 10^5$ 個の `s` から「`a` が $10^5$ 個と `b`」を探すと、1 回で 360〜470 ms かかった（g++-15・g++-13、`-O2`）。長い `t` を探す、または何度も探すなら Z-algorithm か [KMP 法](../string/kmp.md)で線形にする

## s += c と s = s + c（後者は毎回全体をコピーして O(|s|)。先頭に足すなら後ろに足して最後に reverse） {#append}

`s += c` は `s` の末尾に 1 文字足す。`vector` の `push_back` と同じく容量を倍々に増やすので、ならし $O(1)$ である。`s = s + c` は、`s + c` で新しい文字列を作ってから `s` に入れ直すので、毎回 $O(\lvert s \rvert)$ かかる。$N$ 回繰り返すと全体で $O(N^2)$ になる。

手元で $N = 2 \times 10^5$ 回ずつ 1 文字を足して比べた（`-O2`）。

| 書き方 | g++-15 | g++-13 |
| --- | --- | --- |
| `s += c` | 0 ms | 0 ms |
| `s = s + c` | 560 ms | 600 ms |
| `s = c + s`（先頭に足す） | 566 ms | 578 ms |
| `s.insert(s.begin(), c)` | 255 ms | 253 ms |

$N = 2 \times 10^5$ ではメモリのコピーが速く 1 秒を切るが、$O(N^2)$ なので $N$ が 5 倍になると時間は約 25 倍になり、$N = 10^6$ の `s = s + c` は 20 秒を超えた。1 回に何文字も足す形（下の確認問題）では、$N = 2 \times 10^5$ でも数十秒かかる。C++ 側で TLE になるほかの書き方は[入出力と定数倍](../cpp/cpp-io.md#tle-causes)にまとめてある。

先頭に足していく処理は、後ろに足して最後に 1 回 `reverse` すれば $O(N)$ で済む。

```cpp
--8<-- "cpp-string-api/append.cpp:core"
```

- **素朴に書くと**：`s = char('a' + i % 26) + s;` を $N$ 回で、全体 $O(N^2)$ になる
- **落とし穴**：`insert`（途中に挿入）と `erase`（途中を削除）も、後ろの文字を全部ずらすので $O(\lvert s \rvert)$ である。両端に出し入れするなら `deque<char>` を使う。`s += t`（文字列を足す）は $O(\lvert t \rvert)$ で、`s = s + t` は $O(\lvert s \rvert + \lvert t \rvert)$ である

??? question "確認問題：`string ans; for (...) ans = ans + to_string(x) + " ";` が $N = 2 \times 10^5$ で遅いのはなぜか？"
    `ans + to_string(x)` で `ans` の全体をコピーした新しい文字列を作るからである。$i$ 回目に $O(i)$ かかり、全体で $O(N^2)$ になる。`ans += to_string(x); ans += ' ';` と書けば全体で $O(N)$ になる（出力するだけなら、文字列に貯めずにそのまま `cout` に流してよい）。

## 文字と数の変換：c - 'a'・char('a' + i)・c - '0' {#char-arithmetic}

`char` は小さな整数で、英小文字 `'a'`〜`'z'` と数字 `'0'`〜`'9'` は文字コードが連続している。そのため `c - 'a'` で英小文字を 0〜25 に、`c - '0'` で数字の文字を 0〜9 に直せる。逆に `char('a' + i)` で 0〜25 を英小文字に戻す。文字ごとの出現回数を `array<int, 26>` で数えるのが典型である。

```cpp
--8<-- "cpp-string-api/char-arithmetic.cpp:core"
```

入力 `banana 2026` なら `abn 10` と出る。

- **落とし穴 1**：`char` と `int` の和は `int` になる。`cout << 'a' + i` は文字ではなく数を出す。文字として出すには `char(...)` で戻す

```cpp
--8<-- "cpp-string-api/char-print.cpp:core"
```

- **落とし穴 2**：英大文字は `c - 'A'` で、大文字と小文字は連続していない（`'Z'` と `'a'` の間に記号がある）。英字を 52 通りにまとめるなら `isupper(c) ? c - 'A' + 26 : c - 'a'` のように分ける
- **使い分け**：1 文字の数字を数にするなら、`stoi(string(1, c))` ではなく `c - '0'` でよい
- **混同**：`'0'` は文字（コード 48）で、`0` は数である。`s[i] == 0` は「数字の 0」ではなく「コード 0 の文字」との比較になる

## to_string（double は小数点以下 6 桁）・stoi・stoll {#to-string}

`to_string(x)` は数を 10 進の文字列にする。`stoi(s)`・`stoll(s)` は文字列を `int`・`long long` に直す。数の桁を 1 つずつ見たいとき（各桁の和・回文数の判定）は `to_string` で文字列にすると書きやすい。

```cpp
--8<-- "cpp-string-api/to-string.cpp:core"
```

- **落とし穴 1**：`to_string(double)` は C の `printf` の `%f` と同じ書式で、小数点以下が常に 6 桁になる。`1e-7` は `0.000000` になって値が消え、`1e20` は 21 桁の整数部で出る。小数を出力するなら `cout << fixed << setprecision(15)` か `printf` で桁を指定する（[入出力と定数倍](../cpp/cpp-io.md#float-output)）。なお C++26 では `std::format` と同じ書式へ変わる予定で、AtCoder の `-std=gnu++23` では 6 桁のままである
- **落とし穴 2**：`stoi` は先頭の空白を飛ばし、数として読めない文字の手前で止まる（`"12ab"` は 12）。先頭から読めなければ `invalid_argument`、`int` に入らなければ `out_of_range` の例外が投げられ、捕まえなければ RE になる。$2^{31}$ 以上になりうるなら `stoll` を使う。$2^{63} - 1$（約 $9.2 \times 10^{18}$）を超える数（20 桁以上は必ず超える）は `stoll` でも入らないので、文字列のまま扱う。`unsigned long long` を返す `stoull` なら約 $1.8 \times 10^{19}$ まで読める

## starts_with・ends_with（C++20）、contains（C++23） {#starts-with}

`s.starts_with(t)` は `s` が `t` で始まるか、`s.ends_with(t)` は `t` で終わるか、`s.contains(t)` は `t` を含むかを返す。引数は文字列でも 1 文字でもよい。

```cpp
--8<-- "cpp-string-api/starts-with.cpp:core"
```

- **素朴に書くと**：`starts_with` は `s.size() >= t.size() && s.compare(0, t.size(), t) == 0` と同じである。`contains` は `s.find(t) != string::npos` と同じである。`s.substr(0, t.size()) == t` でも書けるが、コピーが起きる
- **版**：`starts_with`・`ends_with` は C++20、`contains` は C++23。g++-13・g++-15 とも `-std=gnu++23` ならすべて使え、AtCoder でも使える。`-std=gnu++20` では `contains` だけが `has no member named 'contains'` のコンパイルエラーになる（手元の g++-13・g++-15 で確かめた）
- **落とし穴**：`contains` の中身は `find` なので、計算量は[落とし穴 3](#substr-find) と同じく最悪 $O(\lvert s \rvert \lvert t \rvert)$ である

## string(n, c)・reverse・辞書順の比較 {#construct-compare}

`string(n, c)` は文字 `c` を $n$ 個並べた文字列を作る。`reverse(s.begin(), s.end())` は `s` をその場で反転する。`<`・`==` などの比較は[辞書順](../string/string-basics.md#lexicographic-order)で、先頭から 1 文字ずつ比べ、最初に違う文字で決まる。片方がもう片方の接頭辞なら短い方が小さい。比較は $O(\min(\lvert s \rvert, \lvert t \rvert))$ かかる（`==` は長さが違えばすぐ偽になる）。

```cpp
--8<-- "cpp-string-api/construct-compare.cpp:core"
```

- **落とし穴 1**：`string(n, c)` は個数が先である。`string('a', 3)` と逆に書くと、`'a'`（97）個の `char(3)` という意図しない文字列になる
- **落とし穴 2**：数字の文字列の比較は数の大小にならない（`"10" < "9"` が真）。同じ桁数にそろっていれば数の大小と一致するので、長さで先に比べてから文字列で比べる
- **落とし穴 3**：`set<string>` や `sort` で文字列を並べると、比較のたびに最悪で文字列の長さの分かかる。長さ $M$ の文字列 $N$ 個をソートすると $O(NM \log N)$ である

## string_view：コピーしない部分文字列。一時的な string を入れると壊れる（C++17） {#string-view}

`string_view` は、ほかの場所にある文字の並びの「先頭の位置と長さ」だけを持つ、読むだけの文字列である。作ること・`substr`・`remove_prefix`（前から縮める）はどれも $O(1)$ で、文字はコピーしない。関数の引数を `string_view` にすると、`string` と文字列リテラルのどちらもコピーせずに渡せる。

```cpp
--8<-- "cpp-string-api/string-view.cpp:core"
```

入力 `abababc ab` なら、先頭から `ab` を 3 回取り除けるので 3 と出る。

- **版**：C++17。g++-13・g++-15 と AtCoder で使える
- **落とし穴 1**：`string_view` は文字を持たないので、元の文字列が消えると壊れる。関数が返した一時的な `string` を入れると、その行の終わりで中身が解放される。手元の g++-13・g++-15 では `-Wall -Wextra` で警告は出なかった。AddressSanitizer（`-fsanitize=address`）を付けると `heap-use-after-free` で止まった（短い文字列では `stack-use-after-scope` と出た）

```cpp
--8<-- "cpp-string-api/string-view-ng.cpp:core"
```

- **落とし穴 2**：元の `string` に `+=` などで書き足すと、中身が別の場所へ移ることがあり、前に作った `string_view` は壊れる（`vector` の再確保と同じ）。`string_view` は、元を変えない間にその場で使い切る（寿命の罠の全体は[未定義動作](../cpp/cpp-undefined-behavior.md#dangling-string-view)）
- **落とし穴 3**：`string_view` から `string` には暗黙に変わらない。`map<string, int>` のキーにするなど、`string` が要る所では `string(sv)` と書く。末尾にヌル文字がある保証もないので、C の関数（`printf("%s")` など）に渡さない

??? question "確認問題：`string_view f() { string s = "abc"; return s; }` の戻り値を使うと何が起きるか？"
    未定義動作になる。戻り値の `string_view` は関数の中の `s` の文字を指しているが、関数を出ると `s` は消える。`string` を返すようにする。

## 区切る：views::split(' ') と string_view(w)（C++20） {#split}

1 行の文字列を空白で区切るには、`views::split(' ')` で区切った部分を順に見るか、`istringstream` で 1 語ずつ読む。`split` の各部分 `w` は文字列ではない部分範囲なので、`string_view(w)` を経て `string` にする（詳しくは [views の基本](../cpp/cpp-views-basics.md#split-join)）。

```cpp
--8<-- "cpp-string-api/split.cpp:core"
```

入力 `a  b `（間に空白 2 個、末尾に空白）なら、`split` は `a`・空・`b`・空の 4 個に分け、`istringstream` は `a`・`b` の 2 個を読む。

- **版**：`views::split` は C++20。ただし `string_view(w)` は C++23 で、`-std=gnu++20` ではコンパイルエラーになる。AtCoder の `-std=gnu++23` なら通る
- **使い分け**：空白で区切られた語を読むだけなら `istringstream`（または入力から直接 `cin >>`）が確実である。`,` などの決まった 1 文字で区切り、空の部分も数えたいときは `split` を使う

## cin で読む文字列は空白で区切られる、その後の getline は残った改行を読む {#getline}

`cin >> s` は先頭の空白・改行を読み飛ばし、次の空白・改行の手前までを 1 語として読む。空白を含む 1 行を読むには `getline(cin, s)` を使う。`getline` は改行までを読んで、改行そのものは捨てる。

`cin >> n` の後にすぐ `getline` を呼ぶと、`cin >> n` が読み残した行末の改行までを読むので、空の行が返る。

```cpp
--8<-- "cpp-string-api/getline-ng.cpp:core"
```

入力が `3` の行と `hello world` の行なら、`line` は空になる。`getline(cin >> ws, line)` と書けば、`ws` が空白と改行を読み飛ばしてから 1 行を読む。

```cpp
--8<-- "cpp-string-api/getline.cpp:core"
```

- **落とし穴 1**：`ws` は空の行も行頭の空白も飛ばす。空の行や行頭の空白に意味があるなら、`cin.ignore()` で次の 1 文字を捨ててから `getline` を呼ぶ。これは数のすぐ後が改行であることを前提にする（行末に空白があると、空白だけが捨てられて空の行が返る）。AtCoder の入力は行末に空白がないので、この前提を満たす
- **落とし穴 2**：手元で作った入力ファイルの改行が `\r\n`（Windows の形）だと、`getline` で読んだ行の末尾に `\r` が残る。AtCoder の入力は `\n` なので起きないが、手元の試験で比較が合わないときは疑う。入出力の全体は[入出力と定数倍](../cpp/cpp-io.md)で扱う

## 確認問題 {#quiz}

??? question "確認問題：長さ $N$ の文字列 `s` の全位置 $i$ で `s.substr(i) < best` と比べると、全体の計算量は？"
    最悪 $O(N^2)$ である。`substr(i)` は残りの $N - i$ 文字をコピーするので、コピーだけで合計 $\sum (N - i) = O(N^2)$ かかる。`string_view(s).substr(i)` にすればコピーは $O(1)$ になるが、比較そのものが最悪 $O(N)$ なので、$N = 2 \times 10^5$ では [Suffix Array](../string/suffix-array.md) などの考え方が要る。

??? question "確認問題：`int x = 7; string t = "abc"; t += 'a' + x;` の後の `t` は？"
    `"abch"` である。`'a' + x` は `int` の 104 で、`+=` は 1 文字の `char` として受けるので `'h'` が足される。一方、`cout << 'a' + x` は `104` と出る。意図を明らかにするため `char('a' + x)` と書く。

## 参考 {#references}

- [cpprefjp「basic_string::find」](https://cpprefjp.github.io/reference/string/basic_string/find.html)：見つからないときに `npos` を返すこと。計算量の規定がないこと
- [cpprefjp「to_string」](https://cpprefjp.github.io/reference/string/to_string.html)：`double` が `%f` の書式になること。C++26 から `std::format` と同じ書式になること
- [cpprefjp「basic_string::starts_with」](https://cpprefjp.github.io/reference/string/basic_string/starts_with.html)：C++20 の前方一致
- [cpprefjp「basic_string::contains」](https://cpprefjp.github.io/reference/string/basic_string/contains.html)：C++23 の部分文字列の判定
- [cpprefjp「basic_string_view」](https://cpprefjp.github.io/reference/string_view/basic_string_view.html)：`string_view` の操作と寿命の注意
- [cppreference「std::getline」](https://en.cppreference.com/cpp/string/basic_string/getline)：`cin >>` の後に使うときの注意と `std::ws`
