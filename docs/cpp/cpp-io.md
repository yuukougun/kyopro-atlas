---
id: cpp-io
title: 入出力と定数倍
aliases: [入出力, fast I/O, cin.tie(nullptr), sync_with_stdio, endl, println, 'std::print', 'std::format', printf, setprecision, fixed, 小数の出力, fflush(stdout), TLE になる書き方, 入出力が遅い]
type: cpp
field: cpp
chapter: 入出力・環境・落とし穴
order: 180
level: 基礎
kind: [実装・C++, 計算量]
prerequisites: []
related: [cpp-types-literals, cpp-integer-overflow, acl-reading, interactive, complexity-estimation, debugging-checklist, cpp-views-basics, cpp-lambda]
summary: 入出力を速くし（sync_with_stdio・cin.tie）、println・小数の桁の指定・インタラクティブ問題のフラッシュを正しく書く。C++ の書き方が原因で TLE になる例も、計測つきで示す。
complexity: 入出力は個数に比例する O(N)。endl は 1 行ごとに書き出すので、定数倍が 10 倍ほどになる
signs:
  - {type: constraint, text: 入力や出力が 10^6 個程度ある（入出力の書き方で実行時間に差が出る）}
  - {type: phrase, text: 答えの絶対誤差または相対誤差が 10^-6 以下なら正解とする（小数の桁を指定して出力しないと WA になる）}
acl: []
sections:
  - {title: 入出力の高速化：sync_with_stdio(false) と cin.tie(nullptr), anchor: fast-io}
  - {title: endl は改行のたびに書き出す（10^6 行で約 0.2 秒余計にかかる）、普段は改行文字 '\n' を出す, anchor: endl}
  - {title: 区切りと改行の書き方：最後だけ改行する書き方と Yes・No の出し分け, anchor: separators}
  - {title: 入力の終わりまで読む：読み込みの成否を while の条件にする, anchor: read-until-eof}
  - {title: printf・scanf と書式, anchor: printf}
  - {title: 'std::format（C++20・GCC 13〜）と std::print・println（C++23・GCC 14〜）', anchor: format-println}
  - {title: 書式の指定：幅・左寄せ・0 埋め・2 進・16 進・小数の桁（C++20・GCC 13〜）, anchor: format-spec}
  - {title: 小数の出力：cout の既定は有効数字 6 桁、fixed と setprecision・printf で桁を指定する, anchor: float-output}
  - {title: 同期を切った後に println・printf と cout を混ぜると順番が入れ替わる, anchor: mixing-streams}
  - {title: インタラクティブ問題のフラッシュ：同期を切る 2 行を書いたら、質問のたびに endl か fflush(stdout) が要る, anchor: flush}
  - {title: そのままでは出力できない型：__int128・modint・vector, anchor: unprintable-types}
  - {title: C++ 側で TLE になる書き方の一覧と計測, anchor: tle-causes}
stage: done
updated: 2026-10-29
cpp_std: null
gcc_min: null
atcoder: true
---

!!! abstract "要点"
    - **何ができるか**：`cin`・`cout` を同期の切り離しで速くし、`println`・`format` で書式を指定して出し、小数の桁とインタラクティブ問題のフラッシュを正しく書く。C++ の書き方が原因の TLE（`endl`・`std::function`・set への `std::lower_bound` など）も、計測した差で見分ける。
    - **いつ使うか**：
        - 入力や出力が $10^6$ 個程度ある（入出力の書き方で実行時間に差が出る）
        - 答えの絶対誤差または相対誤差が $10^{-6}$ 以下なら正解とする（小数の桁を指定して出力しないと WA になる）
    - **計算量**：入出力は個数に比例する $O(N)$。`endl` は 1 行ごとに書き出すので、定数倍が 10 倍ほどになる
    - **前提**：なし

<!-- textlint-disable -->
別名：入出力・fast I/O・cin.tie(nullptr)・sync_with_stdio・endl・println・std::print・std::format・printf・setprecision・fixed・小数の出力・fflush(stdout)・TLE になる書き方・入出力が遅い
<!-- textlint-enable -->

入出力と定数倍は、計算量が正しいのに TLE・WA になる原因のうち、C++ の書き方に由来するものである。どれも 1〜2 行の書き換えで直る。速さは手元の g++-15（`-std=gnu++23 -O2`、出力はファイル）で測った。AtCoder の GCC 15.2（`-std=gnu++23`）では、このページの書き方はすべて使える。g++-13 では `println`・`print` と `vector` の書式が使えない（各節の版を参照）。

このページのコードは `#include <bits/stdc++.h>` と `using namespace std;` を前提にする。

## 入出力の高速化：sync_with_stdio(false) と cin.tie(nullptr) {#fast-io}

`main` の最初に次の 2 行を書くと、`cin`・`cout` が速くなる。入出力が $10^5$ 個程度までなら差は小さいが、書いておいて損はない。

```cpp
--8<-- "cpp-io/fast-io.cpp:core"
```

完全なプログラム：[`fast-io.cpp`](https://github.com/yuukougun/kyopro-atlas/blob/main/snippets/cpp-io/fast-io.cpp)（GitHub）
{ .kp-code-src }

- `ios::sync_with_stdio(false)`：既定の `cin`・`cout` は、C の `scanf`・`printf` と混ぜても順番が崩れないように、1 文字ずつ C の入出力を通す。これを切ると、`cin`・`cout` が自前のバッファでまとめて読み書きする
- `cin.tie(nullptr)`：既定では、`cin` で読む前に毎回 `cout` を書き出す。質問を出してから答えを読むプログラムが、そのまま動くようにするためである。これを切ると、読み書きを交互にくり返すときに速くなる

手元の g++-15 で、$10^6$ 個の整数（各 10 桁以下）を読んで和を出すだけのプログラムは、2 行なしで 0.21〜0.23 秒、2 行ありで 0.03〜0.04 秒だった。1 個読むごとに 1 行出すプログラムでは、`sync_with_stdio(false)` だけだと 0.27 秒、`cin.tie(nullptr)` も書くと 0.05 秒だった。

- **素朴に書くと**：2 行なしの `cin >> x` と `cout << x`。計算量は同じで、1 個あたりの重さだけが違う
- **版**：C++98 からある。g++-13・g++-15 のどちらでも使える
- **落とし穴 1**：2 行を書いた後は、`cin` と `scanf`、`cout` と `printf`・`println` を混ぜない。順番が入れ替わる（[混ぜたとき](#mixing-streams)）
- **落とし穴 2**：`cin.tie(nullptr)` を書くと、読む前の自動の書き出しがなくなる。インタラクティブ問題では、自分で[フラッシュ](../guide/glossary.md#flush)（溜めた出力をすぐ書き出すこと）する（[フラッシュ](#flush)）

## endl は改行のたびに書き出す（10^6 行で約 0.2 秒余計にかかる）、普段は改行文字 '\n' を出す {#endl}

`cout << endl` は、改行文字を出したうえで、バッファにたまった出力をすぐ書き出す（フラッシュ）。`cout << '\n'` は改行文字をバッファに入れるだけで、バッファが一杯になったときやプログラムの終わりにまとめて書き出す。書き出しは 1 回ごとに OS を呼ぶので重く、`endl` を $10^6$ 回使うと $10^6$ 回呼ぶことになる。

手元の g++-15 で $0$ から $10^6 - 1$ を 1 行ずつ出すと、次のようになった（3 回ほど測った範囲）。

| 書き方 | 同期あり | 同期なし |
| --- | --- | --- |
| `cout << i << '\n'` | 0.02〜0.04 秒 | 0.02 秒 |
| `cout << i << endl` | 0.24〜0.41 秒 | 0.28〜0.32 秒 |

`endl` の遅さは同期を切っても消えない。改行は `'\n'` で出し、`endl` はすぐに相手へ届けたいとき（[インタラクティブ問題](#flush)）だけに使う。

- **版**：C++98 からある
- **混同**：`endl` は「改行」ではなく「改行と書き出し」である。デバッグの出力を `cerr` に出すときは、`cerr` がもともと書き出しを溜めないので `endl` は要らない

## 区切りと改行の書き方：最後だけ改行する書き方と Yes・No の出し分け {#separators}

解説コードには、配列を空白区切りで 1 行に出す短い書き方がよく出る。`" \n"` は空白と改行の 2 文字の文字列リテラルで、`" \n"[k]` はその `k` 文字目である。`i == n - 1` は最後の要素で `true`（1）、それ以外で `false`（0）になるので、最後だけ改行、ほかは空白を出す。

```cpp
--8<-- "cpp-io/separators.cpp:core"
```

完全なプログラム：[`separators.cpp`](https://github.com/yuukougun/kyopro-atlas/blob/main/snippets/cpp-io/separators.cpp)（GitHub）
{ .kp-code-src }

入力が `3` と `1 2 1` なら、出力は `1 2 1`・`Yes` の 2 行になる。

- **素朴に書くと**：`if (i == n - 1) cout << '\n'; else cout << ' ';` と同じである
- **落とし穴 1**：$n = 0$ のときは何も出ず、改行も出ない。空の行が要る問題では、ループの後に別に `'\n'` を出す
- **落とし穴 2**：三項演算子 `? :` は `<<` より優先順位が低い。`cout << ok ? "Yes" : "No";` は `(cout << ok) ? "Yes" : "No"` と解釈され、`1` か `0` が出る。手元の g++-13・g++-15 では `-Wall` で `second operand of conditional expression has no effect` の警告が出た。`cout << (ok ? "Yes" : "No")` とかっこで囲む

```cpp
--8<-- "cpp-io/ternary-ng.cpp:core"
```

完全なプログラム：[`ternary-ng.cpp`](https://github.com/yuukougun/kyopro-atlas/blob/main/snippets/cpp-io/ternary-ng.cpp)（GitHub）
{ .kp-code-src }

## 入力の終わりまで読む：読み込みの成否を while の条件にする {#read-until-eof}

個数が書かれていない入力は、読めなくなるまで読む。`cin >> x` は `cin` 自身を返し、`cin` は直前の読み込みが失敗すると条件式の中で `false` になる。入力の終わりに来ると読み込みが失敗するので、ループを抜ける。

```cpp
--8<-- "cpp-io/read-until-eof.cpp:core"
```

完全なプログラム：[`read-until-eof.cpp`](https://github.com/yuukougun/kyopro-atlas/blob/main/snippets/cpp-io/read-until-eof.cpp)（GitHub）
{ .kp-code-src }

入力 `1 2 3` と `4` なら `4 10` が出る。空の入力なら `0 0`、最後に改行がない入力でも最後の数まで読む。

- **落とし穴**：数を読むべき所に文字があっても読み込みが失敗し、ループを抜ける。AtCoder の入力は形式が保証されているので困らないが、手元で入力を打ち間違えると途中で止まって見える
- **使い分け**：1 行ずつ読むなら `while (getline(cin, s))`。`cin >> n` の直後に `getline` を呼ぶと、`n` の後に残った改行だけを読んで空の行になる（[文字列の操作](../cpp/cpp-string-api.md)）

## printf・scanf と書式 {#printf}

`printf`・`scanf` は C の入出力で、`%d` などの書式で型を指定する。`int` は `%d`、`long long` は `%lld`、`double` は `%f`（入力では `%lf`）、文字列は `%s`、文字は `%c` である。`scanf` には変数のアドレス（`&n`）を渡す。

```cpp
--8<-- "cpp-io/printf.cpp:core"
```

完全なプログラム：[`printf.cpp`](https://github.com/yuukougun/kyopro-atlas/blob/main/snippets/cpp-io/printf.cpp)（GitHub）
{ .kp-code-src }

入力 `3 10` なら、`3 10`・`3.3333333333`・`    3|3    |00003` の 3 行が出る。

- **版**：C からある。解説コードでは小数の桁を指定するために `printf("%.10f\n", x)` だけを使う例が多い
- **落とし穴 1**：型と書式が合わないと未定義動作になる。`long long` を `%d` で出すと、値が化けることがある。`-Wall` を付ければ警告（`format '%d' expects argument of type 'int', but argument 2 has type 'long long int'`）が出る。警告を有効にしておく

```cpp
--8<-- "cpp-io/printf-ng.cpp:core"
```

完全なプログラム：[`printf-ng.cpp`](https://github.com/yuukougun/kyopro-atlas/blob/main/snippets/cpp-io/printf-ng.cpp)（GitHub）
{ .kp-code-src }

- **落とし穴 2**：環境によっては、`scanf` の戻り値を使わないと `-O2` で警告（`ignoring return value of 'int scanf(const char*, ...)'`）が出る。glibc（Ubuntu・Debian の C の標準ライブラリ）の `_FORTIFY_SOURCE` は、関数に安全のための検査を足すマクロである。これを有効にして最適化したときだけ、glibc は `scanf` に戻り値を使うよう求める印（`warn_unused_result`）を付ける。手元の Ubuntu の g++-13・g++-15 は `-O0` 以外の最適化で `-D_FORTIFY_SOURCE=2` を自動で足すので、`-O2` だけで警告が出た（`-O0` では出ない）。Debian の g++-13 と Docker のイメージ `gcc:15.2.0` の g++ は自動で足さないので、`-D_FORTIFY_SOURCE=2` を付けたときだけ出る。警告が出ても `scanf` の動作は変わらない。気になるなら、上のように読めた個数（戻り値）を確かめる
- **落とし穴 3**：`printf`・`scanf` と `cin`・`cout` は、同期を切った後に混ぜない（[混ぜたとき](#mixing-streams)）

## std::format（C++20・GCC 13〜）と std::print・println（C++23・GCC 14〜） {#format-println}

`println` は、書式の文字列の `{}` に引数を順に入れて出し、最後に改行を付ける関数である。`print` は改行を付けない。`format` は同じ書式で文字列を作るだけで、出力はしない。型は自動で判断されるので、`printf` のように型と書式を合わせる必要はない。

```cpp
--8<-- "cpp-io/println.cpp:core"
```

完全なプログラム：[`println.cpp`](https://github.com/yuukougun/kyopro-atlas/blob/main/snippets/cpp-io/println.cpp)（GitHub）
{ .kp-code-src }

入力 `3 4` なら、`3 4`・`3+4=7`・空の行・`3 4 3`・`3-4` の 5 行が出る。

- **素朴に書くと**：`println("{} {}", a, b)` は `cout << a << ' ' << b << '\n'` と同じ内容を出す。ただし書き出す先は `cout` ではなく C の `stdout` である（[混ぜたとき](#mixing-streams)）
- **速さ**：手元の g++-15 で $10^6$ 個の整数を 1 行ずつ出すと、`println` が 0.04 秒、`printf` が 0.03 秒、同期を切った `cout` が 0.02 秒だった。どれも十分に速い
- **版**：`format` は C++20 で、g++-13・g++-15 とも `-std=gnu++20` から使える。`print`・`println` は C++23 で GCC 14 から入り、g++-13 では `'println' was not declared in this scope` のコンパイルエラーになる。引数なしの `println()` は C++26 の機能だが、g++-15 は `-std=gnu++23` でも通した。AtCoder の GCC 15.2 ではすべて使える
- **使い分け**：手元が g++-13 なら、`cout << format("{} {}\n", a, b)` と書けば同じ書式が使える

```cpp
--8<-- "cpp-io/format-13.cpp:core"
```

完全なプログラム：[`format-13.cpp`](https://github.com/yuukougun/kyopro-atlas/blob/main/snippets/cpp-io/format-13.cpp)（GitHub）
{ .kp-code-src }

- **落とし穴**：書式の文字列はコンパイル時に検査される。`{}` の数より引数が少ない・自動の番号 `{}` と手で書いた番号 `{0}` を混ぜる、などはコンパイルエラーになる。実行してから気づくことはない

```cpp
--8<-- "cpp-io/format-index-ng.cpp:core"
```

完全なプログラム：[`format-index-ng.cpp`](https://github.com/yuukougun/kyopro-atlas/blob/main/snippets/cpp-io/format-index-ng.cpp)（GitHub）
{ .kp-code-src }

## 書式の指定：幅・左寄せ・0 埋め・2 進・16 進・小数の桁（C++20・GCC 13〜） {#format-spec}

`{}` の中で `:` の後に書式を書く。並びは「寄せ方・`0`（0 埋め）・幅・`.` 桁数・種類」で、どれも省略できる。ここでは、埋める文字（`{:*>5}` で `***42`）や符号の指定は省いた。

| 書式 | 意味 | `42` を出すと |
| --- | --- | --- |
| `{:5}` | 幅 5、数は右寄せ | `   42` |
| `{:<5}` | 幅 5、左寄せ（`>` で右、`^` で中央） | `42   ` |
| `{:05}` | 幅 5、0 埋め | `00042` |
| `{:b}`・`{:08b}` | 2 進、8 桁の 0 埋めの 2 進 | `101010`・`00101010` |
| `{:x}`・`{:X}` | 16 進（小文字・大文字） | `2a`・`2A` |
| `{:.3f}` | 小数点以下 3 桁 | `42.000`（`double` のとき） |

```cpp
--8<-- "cpp-io/format-spec.cpp:core"
```

完全なプログラム：[`format-spec.cpp`](https://github.com/yuukougun/kyopro-atlas/blob/main/snippets/cpp-io/format-spec.cpp)（GitHub）
{ .kp-code-src }

入力 `42 3.14159` なら、`[   42] [42   ] [00042]`・`101010 00101010 2a 2A`・`3.142 [    3.14]` の 3 行が出る。

- **素朴に書くと**：2 進の表示は `bitset<8>(n)` を出すのと同じ見た目になる（`bitset` は負の数を 2 の補数で出す。`{:b}` は `-101` のように符号を付ける）。`cout` で幅を指定するなら `setw(5)`・`setfill('0')` を使う
- **版**：C++20。g++-13・g++-15 で、表のとおりに出た
- **落とし穴**：0 埋めは負の数では符号の後を埋める（`-5` を `{:05}` で出すと `-0005`）

## 小数の出力：cout の既定は有効数字 6 桁、fixed と setprecision・printf で桁を指定する {#float-output}

`cout << x` は、`double` を有効数字 6 桁で出す。`123456789.0` は `1.23457e+08`、`1.0 / 3` は `0.333333` になる。「誤差 $10^{-6}$ 以下なら正解」の問題でも、大きな値は桁が足りずに WA になる。指数の表記（`1.23457e+08`）を受け付けないジャッジもあるので、これも避ける。小数を出すときは必ず桁を指定する。

```cpp
--8<-- "cpp-io/float-output.cpp:core"
```

完全なプログラム：[`float-output.cpp`](https://github.com/yuukougun/kyopro-atlas/blob/main/snippets/cpp-io/float-output.cpp)（GitHub）
{ .kp-code-src }

入力ごとの出力は次のとおりで、手元の g++-15 で確かめた（`y` は `x / 3`）。

| 書き方 | `x = 123456789` | `x = 1000000` | `x = 1` の `y` |
| --- | --- | --- | --- |
| `cout << x` | `1.23457e+08` | `1e+06` | `0.333333` |
| `println("{}", x)` | `123456789` | `1e+06` | `0.3333333333333333` |
| `{:.15f}`・`%.15f`・`fixed << setprecision(15)` | `123456789.000000000000000` | `1000000.000000000000000` | `0.333333333333333` |

- `fixed << setprecision(15)`：`fixed` で小数点以下の桁数を指定する表記にし、`setprecision(15)` で 15 桁にする。どちらも以後の出力すべてに効くので、最初に 1 回書けばよい
- `println("{}", x)`：元の値に戻せる最短の表記で、指数の表記の方が短ければ指数で出る。`1000000.0` は `1e+06`、`0.0001` は `1e-04`、$10^{18}$ は `1e+18` になる。答えがちょうど $10^5$ のような値でも指数になるので、小数の答えは `{:.15f}` で出す
- **版**：`fixed`・`setprecision`・`printf` は C++98 から、`{:.15f}` は `format` が C++20・`println` が C++23 である
- **落とし穴 1**：`fixed` を付けずに `setprecision(15)` だけを書くと、有効数字 15 桁になる。小数点以下の桁数ではないので、大きな値は指数の表記になりうる
- **落とし穴 2**：桁を増やしても、`double` の精度（有効数字 15〜16 桁）を超える桁は意味を持たない。$10^{18}$ 程度の整数を `double` で計算すると、1 の位は正しくない（[浮動小数点数の型](../cpp/cpp-types-literals.md#floating-point)）

## 同期を切った後に println・printf と cout を混ぜると順番が入れ替わる {#mixing-streams}

`ios::sync_with_stdio(false)` を書いた後は、`cout` と C の `stdout` が別々のバッファを持つ。`println`・`printf` は `stdout` に書き、`cout` は自分のバッファに書くので、それぞれのバッファが書き出される順に出力が並ぶ。書いた順にはならない。

```cpp
--8<-- "cpp-io/mixing-streams.cpp:core"
```

完全なプログラム：[`mixing-streams.cpp`](https://github.com/yuukougun/kyopro-atlas/blob/main/snippets/cpp-io/mixing-streams.cpp)（GitHub）
{ .kp-code-src }

手元の g++-15 では、出力は 1・4・5・2・3 の順に並んだ。同じプログラムから 2 行を消して同期を切らずに実行すると、1〜5 の順に出た。

- **直し方**：どちらか一方にそろえる。`cout` と一緒に使うなら、`println(cout, "...")` で `cout` に書く
- **落とし穴**：出力の順番が入れ替わると WA になる。手元で実行しても入れ替わるが、出力の長い問題では気づきにくい。雛形に同期を切る 2 行があるなら、`printf`・`println` を使わないと決めておく

## インタラクティブ問題のフラッシュ：同期を切る 2 行を書いたら、質問のたびに endl か fflush(stdout) が要る {#flush}

[インタラクティブ問題](../misc/interactive.md)では、質問を出して、相手（ジャッジ）の答えを読み、また質問する。出力がパイプにつながっていると、出力はバッファにたまるだけで、書き出すまで相手に届かない。相手は質問を待ち、自分は答えを待つので、両方が止まって TLE になる。

```cpp
--8<-- "cpp-io/interactive.cpp:core"
```

完全なプログラム：[`interactive.cpp`](https://github.com/yuukougun/kyopro-atlas/blob/main/snippets/cpp-io/interactive.cpp)（GitHub）
{ .kp-code-src }

手元で、質問を受け取ってから答えを返す相手のプログラムとパイプでつないで確かめた。

| 自分の書き方 | 同期を切る 2 行なし | 2 行あり |
| --- | --- | --- |
| `cout << ... << '\n'` | 届いた | 届かない |
| `cout << ... << endl` | 届いた | 届いた |
| `println(...)` | 届いた | 届かない |
| `println(...)` の後に `fflush(stdout)` | 届いた | 届いた |

2 行なしで `'\n'` でも届いたのは、`cin.tie` が `cin` で読む前に `cout` を書き出し、同期した `cout` の書き出しが `stdout` も書き出すからである。2 行を書いた雛形では、この自動の書き出しがない。`println`・`printf` は、`cin.tie` を残して `sync_with_stdio(false)` だけを書いても届かなくなる（同期を切った `cout` の書き出しは `stdout` を書き出さない）。

- **直し方**：雛形に関係なく、質問のたびに `cout << endl`（または `cout << flush`）か、`println`・`printf` の後に `fflush(stdout)` を書く。質問の回数は多くても数千回程度なので、`endl` の遅さは問題にならない
- **落とし穴**：`println`・`printf` の出力は、端末へ出すときは 1 行ごとに書き出される。手元でキーボードから入力して試すとフラッシュを忘れても動いて見え、提出して初めて TLE になる。同期を切った `cout` は端末でも溜めるので、`cout << ... << '\n'` なら質問が画面に出ないことで気づける

## そのままでは出力できない型：__int128・modint・vector {#unprintable-types}

`cout <<` で出せない型が 2 つよく出る。`__int128` は `cout <<` の版がなく、`ambiguous overload for 'operator<<'` のコンパイルエラーになる。ACL の modint も `no match for 'operator<<'` になる。

```cpp
--8<-- "cpp-io/unprintable.cpp:core"
```

完全なプログラム：[`unprintable.cpp`](https://github.com/yuukougun/kyopro-atlas/blob/main/snippets/cpp-io/unprintable.cpp)（GitHub）。`mint` は ACL の `modint998244353`（[modint](../math/modint.md)）。
{ .kp-code-src }

入力 `2 3` なら、`6`・`6`・`[2, 3]`・`2 3` の 4 行が出る。

- **`__int128`**：`format`・`println` なら 10 進で出せる（g++-13 の `format` でも出せた）。自作の変換と入力の読み方は [`__int128` の入出力](../cpp/cpp-integer-overflow.md#int128-io)にある
- **modint**：`m.val()` で $0$ 以上法未満の整数を取り出して出す（ACL v1.6 の `val()` は `int` を返す）。使い方は [ACL の読み方](../cpp/acl-reading.md)にある
- **`vector`**：`println("{}", v)` は `[2, 3]` のようにかっこと `, ` 付きで出し、AtCoder の空白区切りの形式にならない。`{:n}` でかっこは消えるが、`, ` は残る。空白区切りで出すときは、[区切りの書き方](#separators)のループで出す
- **版**：`vector` などの範囲を `format`・`println` で出すのは C++23 の機能で、GCC 15 から入った。g++-13 ではコンパイルエラーになる。AtCoder の GCC 15.2 では使えるので、デバッグの出力（`println(stderr, "{}", v)`）に便利である

## C++ 側で TLE になる書き方の一覧と計測 {#tle-causes}

計算量の見積もりが合っているのに TLE になるとき、C++ の書き方が原因のことがある。手元の g++-15（`-O2`）で測った例を並べる。計算量そのものの見積もりと定数倍の考え方は[計算量の見積もり](../basics/complexity-estimation.md#constant-factor)にある。

| 書き方 | 計測 | 直し方 |
| --- | --- | --- |
| `endl` で改行 | $10^6$ 行で 0.02 秒が 0.24〜0.41 秒に | `'\n'`（[endl](#endl)） |
| 同期したままの `cin` | $10^6$ 個で 0.03 秒が 0.21〜0.23 秒に | 同期を切る 2 行（[高速化](#fast-io)） |
| `std::function` で再帰 | fib(35) で 9 ms が 41 ms に | `auto&& self` |
| set に `std::lower_bound` | 要素 $2 \times 10^5$ の set に $2 \times 10^4$ 回で約 22 秒 | `st.lower_bound(x)`（1 ms） |
| `s = s + c` | $2 \times 10^5$ 回で 568 ms | `s += c`（1 ms 未満） |
| `vector` の値渡し | 長さ $2 \times 10^5$ を $10^4$ 回渡して 141 ms | `const vector<int>&`（1 ms 未満） |
| 関数の中の大きな配列（`int buf[100000];` の先頭だけ使う） | $2 \times 10^5$ 回呼んで 0.05 秒が、AtCoder と同じ 0 埋めのオプションで 1.03 秒に | グローバルに置くか、外で 1 回だけ確保する（[0 で埋める処理](../cpp/cpp-environment.md#auto-var-init)） |

set への `std::lower_bound` は、計算量の次数が変わる例である。`std::lower_bound` の比べる回数は $O(\log N)$ だが、真ん中へ飛ぶのにイテレータを 1 つずつ進める。set のイテレータは前後にしか動けないので、1 回で $O(N)$ かかる。set・map ではメンバ関数の `st.lower_bound(x)` を使う。

```cpp
--8<-- "cpp-io/tle-fixes.cpp:set-lower-bound"
```

完全なプログラム：[`tle-fixes.cpp`](https://github.com/yuukougun/kyopro-atlas/blob/main/snippets/cpp-io/tle-fixes.cpp)（GitHub）
{ .kp-code-src }

`s = s + c` は、右辺で `s` をコピーした新しい文字列を作ってから代入するので、1 回 $O(\lvert s \rvert)$ かかる。`vector` を値で受ける関数も、呼ぶたびに丸ごとコピーする。どちらも、ループの中や再帰の中にあると全体が $O(N^2)$ になる。

```cpp
--8<-- "cpp-io/tle-fixes.cpp:string-append"
```

```cpp
--8<-- "cpp-io/tle-fixes.cpp:by-value"
```

完全なプログラム：[`tle-fixes.cpp`](https://github.com/yuukougun/kyopro-atlas/blob/main/snippets/cpp-io/tle-fixes.cpp)（GitHub）
{ .kp-code-src }

`std::function` には、どんな関数でも入る。その代わり、呼ぶたびに間接的な呼び出しを挟み、インライン化（呼び出しを中身で置き換える最適化）もされにくい。再帰のように何度も呼ぶと差が出る。ラムダ式の再帰は、自分を引数で受け取る形で書く（[ラムダ式と再帰ラムダ](../cpp/cpp-lambda.md)）。

```cpp
--8<-- "cpp-io/tle-fixes.cpp:recursion"
```

完全なプログラム：[`tle-fixes.cpp`](https://github.com/yuukougun/kyopro-atlas/blob/main/snippets/cpp-io/tle-fixes.cpp)（GitHub）
{ .kp-code-src }

- **遅くないもの**：`for (int i : views::iota(0, n))` は普通の for と同じ速さである（[views::iota](../cpp/cpp-views-basics.md#iota)）。範囲 for の `for (const auto& x : v)` も、添字のループと変わらない
- **計測の注意**：時間は手元の計測で、AtCoder とは環境が違う。比の目安として読む。同じ計測を g++-13 でも行い、比はほぼ同じだった
- **落とし穴**：`#pragma GCC optimize("O3")` などの指定で救おうとする前に、上の書き方がないかを確かめる。次数が違う原因（set への `std::lower_bound`・`s = s + c`・値渡し）は、最適化の指定では直らない

## 確認問題 {#quiz}

??? question "確認問題：雛形に `ios::sync_with_stdio(false); cin.tie(nullptr);` があるとき、インタラクティブ問題で `cout << x << '\n';` と書いて質問すると何が起きるか？"
    質問はバッファにたまったままで、相手に届かない。自分は答えを読もうとして止まり、TLE になる。`cin.tie(nullptr)` で、読む前の自動の書き出しを切っているからである。`cout << x << endl;` と書く。

??? question "確認問題：同期を切った後に `println` と `cout` を交互に使いたい。どう書けばよいか？"
    `println(cout, "...")` と書いて、`println` も `cout` に書かせる。`println("...")` のままだと C の `stdout` に書くので、`cout` の出力と順番が入れ替わる。

??? question "確認問題：`double` の答え `ans` を `cout << ans << '\n';` で出したら WA になった。値は正しい。何が考えられるか？"
    `cout` の既定は有効数字 6 桁なので、桁が足りないか、`1.23457e+08` のような指数の表記で出ている。`cout << fixed << setprecision(15) << ans` か `println("{:.15f}", ans)` で出す。

## 参考 {#references}

- [cpprefjp「sync_with_stdio」](https://cpprefjp.github.io/reference/ios/ios_base/sync_with_stdio.html)：同期を切ったときに C の入出力と混ぜてはいけないこと
- [cpprefjp「tie」](https://cpprefjp.github.io/reference/ios/basic_ios/tie.html)：結び付けたストリームを読み書きの前に書き出すこと
- [cpprefjp「println」](https://cpprefjp.github.io/reference/print/println.html)：`println` の書き出す先と、引数なしの形が C++26 であること
- [cpprefjp「format」](https://cpprefjp.github.io/reference/format/format.html)：書式の指定の文法
- [cppreference「Standard format specification」](https://en.cppreference.com/w/cpp/utility/format/spec)：幅・寄せ方・0 埋め・種類の指定
- [cppreference「std::lower_bound」](https://en.cppreference.com/w/cpp/algorithm/lower_bound)：ランダムアクセスでないイテレータでは進める回数が線形になること
- [GCC「libstdc++ Implementation Status」](https://gcc.gnu.org/onlinedocs/libstdc++/manual/status.html)：`format`・`print`・範囲の書式が入った GCC の版
