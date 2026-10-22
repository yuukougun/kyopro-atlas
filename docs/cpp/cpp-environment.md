---
id: cpp-environment
title: AtCoder と手元の C++ 環境
aliases: [AtCoder の C++, コンパイルオプション, GCC 15.2, -std=gnu++23, -std=c++23, -ftrivial-auto-var-init=zero, 言語アップデート, C++ の版, 版の対応表, スタックオーバーフロー, ulimit -s, 深い再帰, 手元と結果が違う]
type: cpp
field: cpp
chapter: 入出力・環境・落とし穴
order: 190
level: null
kind: [実装・C++]
prerequisites: []
related: [cpp-undefined-behavior, cpp-macros-template-file, acl-reading, cpp-lambda, atcoder-system, dfs, cpp-views-cpp23]
summary: 手元の g++ と AtCoder（GCC 15.2・-std=gnu++23）の違いで結果が変わる場面（未初期化変数・スタック・GNU 拡張・ACL の版）を知り、同じ条件で試す。各機能が GCC のどの版から使えるかも分かる。
complexity: なし（環境の設定の話。深さ D の再帰はスタックを D 段分使う）
signs:
  - {type: constraint, text: N ≤ 2×10^5 の木やグラフを再帰でたどる（一直線の入力では深さが N になり、手元の 8 MiB のスタックでは落ちることがある）}
acl: []
sections:
  - {title: AtCoder と手元のオプションの比較と、同じ条件で試すコマンド, anchor: options}
  - {title: '-std=gnu++23 と -std=c++23 の違い：GNU 拡張と __int128 の型特性', anchor: gnu-mode}
  - {title: '-ftrivial-auto-var-init=zero：未初期化の局所変数が 0 になり、大きな局所配列は遅くなる', anchor: auto-var-init}
  - {title: '-march=native：pragma の target は要らないが、FMA で小数の結果が変わりうる', anchor: march-native}
  - {title: '-DATCODER・-DONLINE_JUDGE：ジャッジでだけ定義されるマクロ', anchor: judge-macros}
  - {title: ACL の版：AtCoder は v1.6（modint の val() が int）。手元も v1.6 にそろえる, anchor: acl-version}
  - {title: 再帰の深さとスタック：手元の上限・ulimit -s unlimited・非再帰への書き直し, anchor: stack-depth}
  - {title: プリコンパイル済みヘッダ：作ったときと同じオプションのときだけ使われる（-Winvalid-pch で理由が出る）, anchor: pch}
  - {title: Clang 版（libc++）ではなく GCC 版を選ぶ, anchor: gcc-or-clang}
  - {title: 手元と AtCoder で結果が違うときに疑う順（未初期化変数 → 未定義動作 → スタック → ACL の版）, anchor: when-results-differ}
  - {title: C++ の版と GCC の対応表（g++-13 と AtCoder の GCC 15.2）, anchor: version-matrix}
  - {title: GCC 13 で通らない書き方（GCC 14〜・GCC 15〜の C++23 の機能）, anchor: gcc13-limits}
  - {title: AtCoder で使えないもの：C++26 の機能と GCC 16 からの機能, anchor: not-on-atcoder}
stage: draft
updated: 2026-10-22
cpp_std: 23
gcc_min: 15
atcoder: true
---

!!! abstract "要点"
    - **何ができるか**：手元の g++ と AtCoder（GCC 15.2・`-std=gnu++23`）のオプションの違いで結果が変わる場面（未初期化変数・スタック・GNU 拡張・ACL の版・小数）を知り、AtCoder と同じ条件で試す。各機能が GCC のどの版から使えるかも分かる。
    - **いつ使うか**：手元と提出で結果が違う。手元でだけ Segmentation fault になる。$N \le 2 \times 10^5$ の木やグラフを再帰でたどる（一直線の入力では深さが $N$ になり、手元の 8 MiB のスタックでは落ちることがある）。解説コードが手元の g++ でコンパイルできない。
    - **計算量**：なし（環境の設定の話）。深さ $D$ の再帰はスタックを $D$ 段分使う
    - **前提**：なし

<!-- textlint-disable -->
別名：AtCoder の C++・コンパイルオプション・GCC 15.2・-std=gnu++23・-std=c++23・-ftrivial-auto-var-init=zero・言語アップデート・C++ の版・版の対応表・スタックオーバーフロー・ulimit -s・深い再帰・手元と結果が違う
<!-- textlint-enable -->

AtCoder の C++ は、2025-10 の言語アップデートから おもに C++23 (GCC 15.2.0) と C++23 (Clang 21.1.0) の 2 つになった（ほかに、ライブラリのない IOI-Style がある）。同じコードでも、コンパイラの版とオプションが違えば、通る・通らないや出力が変わる。このページは、AtCoder の GCC 版のオプションを 1 つずつ手元と比べ、差が出る場面とそろえ方をまとめる。後半は、C++ の各機能が GCC のどの版から使えるかの対応表である。

このページの「手元」は Linux（WSL を含む）の g++-15 15.2.0 と g++-13 13.4.0 で、確かめた結果はすべてこの 2 つによる。コード片は `#include <bits/stdc++.h>` と `using namespace std;` を前提にする。

## AtCoder と手元のオプションの比較と、同じ条件で試すコマンド {#options}

AtCoder の GCC 版は、`-std=gnu++23 -O2 -Wall -Wextra -march=native -fmodules -ftrivial-auto-var-init=zero -DATCODER -DONLINE_JUDGE -lstdc++exp` などのオプションでコンパイルする（2025-10 の言語アップデートの時点。2026-06 に `-flto=auto` が外された）。手元との違いと、それで差が出る場面は次のとおりである。

| 項目 | AtCoder | 手元でよくある設定 | 差が出る場面 |
| --- | --- | --- | --- |
| コンパイラ | GCC 15.2.0 | g++-15 か、それより古い g++ | g++-13 では GCC 14・15 からの機能が通らない（[GCC 13 で通らない書き方](#gcc13-limits)） |
| 規格 | `-std=gnu++23` | 付け忘れると `gnu++17` | 手元だけコンパイルエラー（[GNU 拡張](#gnu-mode)） |
| 最適化 | `-O2` | デバッガ用のビルドは最適化なし | 未定義動作の現れ方、範囲外の検査（[疑う順](#when-results-differ)） |
| `-ftrivial-auto-var-init=zero` | あり | なし | 未初期化の値、大きな局所配列の速さ（[次の節](#auto-var-init)） |
| `-march=native` | あり | なし | 速さと、小数の最後の桁（[FMA](#march-native)） |
| `-DATCODER -DONLINE_JUDGE` | あり | なし | `#ifdef` で分けた部分（[マクロ](#judge-macros)） |
| ACL | v1.6 | 入れた版 | `modint::val()` の型（[ACL の版](#acl-version)） |
| スタックの上限 | 大きい | 8 MiB が多い | 深い再帰が手元だけで落ちる（[スタック](#stack-depth)） |

`-Wall -Wextra` は手元にも付ける。`-fmodules` は `import std;` を使うときだけ、`-lstdc++exp` は `<stacktrace>` などの一部のヘッダを使うときだけ関係する（[import std;](../cpp/cpp-macros-template-file.md#import-std)）。g++-13 も g++-15 も、`-std` を付けなければ `gnu++17`（`__cplusplus` が 201703）でコンパイルする。手元で `g++ a.cpp` とだけ打つと、C++20 以降の機能が使えない。

AtCoder とできるだけ同じ条件で試すには、次のように打つ。ACL の場所は自分の環境に合わせる。

```text
ulimit -s unlimited      # この端末で 1 回。スタックの上限を外す
g++-15 -std=gnu++23 -O2 -Wall -Wextra -march=native -ftrivial-auto-var-init=zero \
       -DATCODER -DONLINE_JUDGE -I ~/lib/ac-library a.cpp -o a
./a < in.txt
```

- `-march=native` は手元の CPU の命令を使うので、ジャッジの CPU とは同じにならない。速さを比べる目安にはならない
- `-DONLINE_JUDGE` を付けると、`#ifndef ONLINE_JUDGE` で囲んだデバッグ出力も消える
- ふだんの設定（エディタの拡張機能など）は `-std=gnu++23 -O2 -Wall -Wextra` で足りる。上のコマンドは、手元と提出で結果が違うときに使う

## -std=gnu++23 と -std=c++23 の違い：GNU 拡張と __int128 の型特性 {#gnu-mode}

`-std=gnu++23` は C++23 に GCC の拡張を加えたもので、`-std=c++23` は規格どおりのモードである。AtCoder は `gnu++23` なので、手元が `c++23` だと、AtCoder で通るコードが手元だけでコンパイルエラーになる。

```cpp
--8<-- "cpp-environment/gnu-mode.cpp:core"
```

g++-13・g++-15 の `-std=gnu++23` では `3 2 6` と出る。`-std=c++23` では 3 か所ともエラーになる。

- `typeof`：`'typeof' was not declared in this scope`。GNU 拡張で、規格では `decltype` を使う
- `is_integral_v<__int128>`：`c++23` では `false` になり、`static_assert` が失敗する。`gcd` はこの `static_assert` で止まり、`abs` は `__int128` 用の多重定義が用意されず曖昧になる。どちらも、厳密モードでは `__int128` を整数型として扱わないためである（[-std=c++23 では \_\_int128 が整数型と判定されない](../cpp/cpp-integer-overflow.md#int128-strict-mode)）
- `numeric_limits<__int128>` は、どちらのモードでも使える

可変長配列 `int a[n];`・`a ?: b`・`case 1 ... 5:` も GCC の拡張だが、これらは `c++23` でも通る（`-Wpedantic` を付けると警告される）。エディタのコード補完やエラーの表示も、同じ `-std=gnu++23` にそろえておく。

- **版**：`-std=gnu++23` は GCC 11 から指定でき、g++-13 でも使える。ただし g++-13 の `__cplusplus` は 202100 で、C++23 の機能は一部しかない

## -ftrivial-auto-var-init=zero：未初期化の局所変数が 0 になり、大きな局所配列は遅くなる {#auto-var-init}

`-ftrivial-auto-var-init=zero` は、初期値を書いていない自動変数（関数の中の変数と配列）を 0 で埋めるオプションである。AtCoder には付いていて、手元の g++ には既定で付いていない。差は 2 つの場面で出る。

**初期化を忘れたコード**。`long long s;` と書いて足し始めたり、関数の中の `int cnt[26];` を初期化せずに数えたりすると、AtCoder では 0 から始まって AC し、手元ではゴミの値から始まって答えが合わない。例と警告の出方は [未初期化変数](../cpp/cpp-undefined-behavior.md#uninitialized) にある。GCC のドキュメントによると、このオプションを付けても GCC は変数を「未初期化」として扱い続け、警告も最適化もそのままである。規格の上でも未定義動作のままなので、0 で埋まることに頼らず初期値を書く。

**大きな局所配列を持つ関数を何度も呼ぶコード**。0 で埋める処理は、関数を呼ぶたびに配列の全体に対して行われる。次の関数は先頭の `k` 個しか使わないが、AtCoder の設定では呼ぶたびに 40 万バイトを 0 で埋める。

```cpp
--8<-- "cpp-environment/auto-var-init-cost.cpp:core"
```

手元で `f` を $2 \times 10^5$ 回呼ぶと（$k = 1$）、オプションなしの `-O2` で 0.05 秒、`-ftrivial-auto-var-init=zero` を付けて 1.03 秒だった（g++-13・g++-15 で同じ程度）。手元では速いのに AtCoder でだけ TLE する、という形になる。作業用の配列は、グローバルに置くか、外で 1 回だけ確保して使い回す。

- **版**：GCC 12 からのオプションである。g++-13・g++-15 で同じ結果だった
- **手元に付けるか**：付ければ AtCoder と同じ結果になり、付けなければ初期化忘れが手元で表に出る。手元で `-ftrivial-auto-var-init=pattern` を付けると、未初期化の変数が毎回同じ不自然な値になり、気づきやすい（[不具合を探すビルド](../cpp/cpp-undefined-behavior.md#debug-build)）
- **対象外**：グローバル変数はもともと 0 で初期化される。`vector<int> a(n)` も 0 で埋まる。`new`・`malloc` で取った領域はこのオプションの対象外である

## -march=native：pragma の target は要らないが、FMA で小数の結果が変わりうる {#march-native}

`-march=native` は、コンパイルする計算機の CPU が持つ命令（AVX2 など）をすべて使ってよいとするオプションである。AtCoder ではジャッジの計算機でコンパイルするので、ジャッジの CPU の命令が使われる。ジャッジの CPU が AVX2 を持てば、解説コードの `#pragma GCC target("avx2")` は書かなくても同じである（[#pragma GCC optimize・target](../cpp/cpp-macros-template-file.md#pragma)）。

整数だけのコードでは、`-march=native` で変わるのは速さだけである。小数（`double`）のコードでは、最後の桁が変わることがある。GCC は C++ では既定で（`-std=c++23` でも）`a * b - c * d` のような 1 つの式を、CPU に FMA 命令（掛け算と足し算を 1 回の丸めで行う命令）があればそれで計算してよい（`-ffp-contract=fast` が既定）。丸めの回数が減るので、結果が少し変わる。

```cpp
--8<-- "cpp-environment/fma.cpp:core"
```

平行な 2 つのベクトル $(0.1, 0.3)$ と $(0.1, 0.3)$ の外積は、手元の `-O2` では `0` になった。同じコードに `-march=native` を付けると（手元の CPU は FMA を持つ）、`1.66533e-18` と正の値になった。$(0.7, 0.3)$ どうしでは `-1.33227e-17` と負になった（g++-13・g++-15 で同じ）。ジャッジの CPU が FMA を持てば、AtCoder でも同じことが起こりうる。

- **影響**：小数の外積の符号で向きを判定するコードは、`== 0` の判定や符号が手元と変わりうる。整数の座標なら整数のまま外積を求める（[誤差の扱い](../geometry/geometry-precision.md#integer-comparison)）
- **そろえ方**：`-ffp-contract=off` を付けると FMA への置き換えが止まり、`-march=native` があっても `0` になった。AtCoder のオプションは変えられないので、誤差に強い書き方で対処する

## -DATCODER・-DONLINE_JUDGE：ジャッジでだけ定義されるマクロ {#judge-macros}

AtCoder はコンパイルのときに `-DATCODER -DONLINE_JUDGE` を付けるので、マクロ `ATCODER` と `ONLINE_JUDGE` が定義される。`#ifdef` で、提出でだけ（または手元でだけ）コンパイルする部分を選べる。

```cpp
--8<-- "cpp-environment/judge-macros.cpp:core"
```

AtCoder と同じ `-DATCODER -DONLINE_JUDGE` を付けると `judge`、付けなければ `local` と出る。手元のデバッグ出力を `#ifndef ONLINE_JUDGE` で囲めば、提出では消える。手元で `-DLOCAL` を付けて `#ifdef LOCAL` と書く流儀もある（[#ifdef LOCAL・#ifndef ONLINE_JUDGE](../cpp/cpp-macros-template-file.md#ifdef-local)）。

- **落とし穴**：`ONLINE_JUDGE` を定義するかはジャッジごとに違う。ほかのジャッジでは、デバッグ出力が消えずに WA になることがある。手元でだけ `-DLOCAL` を付ける方法なら、どのジャッジでも確実に消える

## ACL の版：AtCoder は v1.6（modint の val() が int）。手元も v1.6 にそろえる {#acl-version}

AtCoder の ACL は v1.6（2025-05 公開）である。v1.5 からの互換性のない変更は、`modint::val()` の戻り値が `unsigned int` から `int` になったことだけで、`a.val() - b.val()` の結果が変わる（[ACL の版](../cpp/acl-reading.md#version)）。手元の ACL が古いと、同じコードの出力が手元と AtCoder で食い違う。手元の版は、次のコードがコンパイルできるかで確かめられる。

```cpp
--8<-- "cpp-environment/acl-version.cpp:core"
```

v1.6 では `-1` と出る。v1.5 以前では `static_assert` で止まる（外せば `4294967295` と出る）。古い版なら、GitHub の atcoder/ac-library の Releases から v1.6 を入れ直す。`atcoder/modint.hpp` の `val()` の宣言を見ても分かる。

## 再帰の深さとスタック：手元の上限・ulimit -s unlimited・非再帰への書き直し {#stack-depth}

関数を呼ぶたびに、戻り先・引数・局所変数がスタックに積まれ、戻ると取り除かれる。深さ $D$ の再帰は $D$ 段分を同時に積むので、1 段の大きさ × $D$ がスタックの上限を超えると Segmentation fault で落ちる。一直線の木（パス）を端から DFS すると、深さは頂点数 $N$ になる。

手元の Linux は、スタックの上限が 8 MiB（`ulimit -s` が 8192）のことが多い。次の再帰ラムダで、一直線の木を頂点 0 からたどる深さを変えて試した。

```cpp
--8<-- "cpp-environment/stack-dfs.cpp:core"
```

| ビルド（`ulimit -s 8192`、g++-15） | 通った深さ | 落ちた深さ |
| --- | --- | --- |
| `-O2`、上の再帰ラムダ | $2.2 \times 10^5$ | $2.4 \times 10^5$ |
| `-O0`、上の再帰ラムダ | $6.5 \times 10^4$ | $7 \times 10^4$ |
| `-O2`、`std::function` で書いた同じ DFS | $8 \times 10^4$ | $9 \times 10^4$ |

1 段の大きさは、最適化の有無と書き方で数倍変わる。局所変数の多い DFS では、`-O2` でも $10^5$ で落ちた例がある（[木の再帰の深さ](../tree/tree-traversal.md#recursion-depth)）。$N = 2 \times 10^5$ の一直線の入力は、手元の既定の上限では落ちうると思っておく（上の最小の DFS でもぎりぎりで、局所変数が増えたり `-O0` にしたりすれば落ちる）。`std::function` の再帰は 1 段が大きく、遅くもある（[std::function による再帰](../cpp/cpp-lambda.md#std-function)）。

**上限を外す**。実行する前に、同じ端末で `ulimit -s unlimited` を実行する。手元では、上の再帰ラムダが `-O2` で深さ $10^7$、`-O0` で $10^6$ まで通った。`ulimit` はその端末（シェル）と、そこから起動したプログラムにだけ効く。エディタの拡張機能から実行するときは、エディタを起動したシェルの上限を引き継ぐことが多い。効いているかは、次のコードをプログラムの冒頭に置いて確かめられる。

```cpp
--8<-- "cpp-environment/stack-limit.cpp:core"
```

**AtCoder の上限**。2023-06 の第三者の記事では、AtCoder のコードテストで調べた上限が 1048576 KiB（1 GiB）だった。2025-10 の新ジャッジでの値は、この教材では確かめていない。上のコードをコードテストで動かせば分かる。AtCoder では深い再帰も通ることが多いが、上限は提出先ごとに違うので、深さ $10^6$ を超えるときや上限が分からないときは非再帰に書き直す。

**非再帰に書き直す**。DFS は明示的なスタックで書き直せる（[非再帰の DFS](../graph/dfs.md#iterative)）。木なら、BFS 順に並べて順・逆順に処理すれば、深さや部分木の値が再帰なしで求まる（[木の再帰の深さ](../tree/tree-traversal.md#recursion-depth)）。

- **大きな局所配列**：関数の中の配列もスタックに置かれる。`main` の中で `int a[10000000];`（40 MB）と宣言すると、手元の 8 MiB の上限では、配列をほとんど使わなくても Segmentation fault になった。グローバルに置くか `vector` にすれば、スタックを使わない
- **症状**：手元でだけ RE になり、入力例やランダムな木では通るのに、一直線の木でだけ落ちる

## プリコンパイル済みヘッダ：作ったときと同じオプションのときだけ使われる（-Winvalid-pch で理由が出る） {#pch}

`#include <bits/stdc++.h>` はすべての標準ヘッダを読むので、手元の g++-15 ではそれだけで 1 秒ほどかかる。ヘッダを前もってコンパイルした `.gch` ファイル（プリコンパイル済みヘッダ）を置くと縮められる。手元では 1.1 秒が 0.47 秒になった。作り方は次のとおりで、提出には関係しない。

```text
mkdir -p ~/pch/bits
cp /usr/include/x86_64-linux-gnu/c++/15/bits/stdc++.h ~/pch/bits/
cd ~/pch/bits && g++-15 -std=gnu++23 -O2 -x c++-header stdc++.h -o stdc++.h.gch
g++-15 -I ~/pch -std=gnu++23 -O2 -Wall -Wextra a.cpp     # -I ~/pch を付けて使う
```

`.gch` は、作ったときとオプションが違うと黙って無視され、ふつうのヘッダが読まれる（結果は同じで、遅くなるだけ）。`-Winvalid-pch` を付けると理由が出る。手元で確かめた結果は次のとおりだった。

- `-Wall -Wextra`・`-ftrivial-auto-var-init=zero`・`-DATCODER -DONLINE_JUDGE` を足しても使われた
- `-std=c++23` では `not used because 'unix' not defined`、`-g` では `created with 'none' debug info` で使われなかった
- `-O2` を外す・`-march=native` を足すと、`created and used with differing settings of …` で使われなかった。[同じ条件で試すコマンド](#options) では使われない

使われたかは `-H` を付けると分かる（`!` で始まる行なら使われ、`x` なら使われていない）。デバッグ用のビルド用にもう 1 つ作るなら、そのオプションで別のフォルダに作る。

## Clang 版（libc++）ではなく GCC 版を選ぶ {#gcc-or-clang}

AtCoder の C++23 には GCC 15.2.0 と Clang 21.1.0 の 2 つがある。同じ `-std` でも、標準ライブラリの実装が違う（GCC 版は libstdc++、Clang 版は libc++）。非公式の記事（2025-06）によれば、当時の libc++ には C++23 の views の多く（`views::enumerate`・`views::zip` の仲間・`views::chunk`・`views::slide`・`views::stride`・`views::cartesian_product`）がなかった。`ranges::fold_left` などの畳み込みの関数、`generator`、`<stacktrace>` もなかった。

この教材のコード片は、GCC 15.2 の `-std=gnu++23` で確かめている。言語の選択は「C++23 (GCC 15.2.0)」にする。

- **落とし穴**：言語を選び間違えると、手元で通ったコードが CE になる。CE になったら、まず提出の言語を確かめる
- **ほかの版**：ライブラリの入っていない C++ IOI-Style（GNU++20、GCC 14.2.0）もある。ACL などを使うなら選ばない

## 手元と AtCoder で結果が違うときに疑う順（未初期化変数 → 未定義動作 → スタック → ACL の版） {#when-results-differ}

手元と AtCoder で結果が違うときの原因は、たいてい次のどれかである。上から順に、手元で何を試せばよいかを書く。

1. **未初期化変数**：AtCoder では AC、手元では WA（またはその逆）。手元で `-ftrivial-auto-var-init=zero` を付けて結果が AtCoder と同じになれば、これである。`-ftrivial-auto-var-init=pattern` で値を目立たせ、初期値を書き足す（[未初期化変数](../cpp/cpp-undefined-behavior.md#uninitialized)）
2. **未定義動作**：範囲外の添字・符号付き整数のオーバーフロー・寿命の切れた参照など。最適化の有無やコンパイラの版で現れ方が変わる。AddressSanitizer などを付けた不具合探しのビルドで動かす（[不具合を探すビルド](../cpp/cpp-undefined-behavior.md#debug-build)）。g++-15 は最適化なし（`-O0`）のときに標準ライブラリの検査（`_GLIBCXX_ASSERTIONS`）を自動で有効にする。そのため、`vector` の範囲外が `-O0` のときだけ `Assertion '__n < this->size()' failed` で止まる。`-O2` では検査されない（g++-13 は `-O0` でも検査しない）
3. **スタック**：手元でだけ Segmentation fault。`ulimit -s unlimited` で通ればこれである（[スタック](#stack-depth)）
4. **ACL の版**：`modint` の `val()` を引き算・比較に使っているなら、手元の ACL が v1.6 か確かめる（[ACL の版](#acl-version)）

ほかに、次の差もある。

- **小数の最後の桁**：`-march=native` の FMA で、外積の符号や `==` の判定が変わる（[FMA](#march-native)）
- **AtCoder でだけ TLE**：大きな局所配列を持つ関数を何度も呼んでいる（[0 で埋める処理](#auto-var-init)）
- **手元でだけ CE**：`-std` が `gnu++23` でない、または g++ が 13 以前（[GCC 13 で通らない書き方](#gcc13-limits)）

## C++ の版と GCC の対応表（g++-13 と AtCoder の GCC 15.2） {#version-matrix}

C++ の機能が、どの規格の版で入り、GCC のどの版から使えるかの表である。○ は使える、× は使えない。g++-13 の列は `-std=gnu++23` を付けたときで、古い環境や他人の環境で解説コードを動かすときの目安になる。GCC の版は cppreference と GCC の更新の一覧により、○× は手元の g++-13・g++-15 で確かめた。

| 機能 | 規格 | GCC | g++-13 | AtCoder |
| --- | --- | --- | --- | --- |
| 構造化束縛・初期化式つきの if・CTAD・`optional`・`gcd`・`lcm`・`clamp` | C++17 | 7 | ○ | ○ |
| 範囲 for の初期化式・指示付き初期化・`<bit>`・`contains`・`erase_if`・ラムダの既定構築 | C++20 | 8〜9 | ○ | ○ |
| `<=>`・コンセプト・`auto` 引数・ranges と views・`span`・`numbers` | C++20 | 10 | ○ | ○ |
| `std::format` | C++20 | 13 | ○ | ○ |
| `string::contains`・`uz` リテラル | C++23 | 11 | ○ | ○ |
| `views::enumerate`・`zip`・`adjacent`・`chunk`・`slide`・`chunk_by`・`cartesian_product`・`ranges::fold_left` | C++23 | 13 | ○ | ○ |
| deducing this・`print`・`println`・`ranges::to`・`generator` | C++23 | 14 | × | ○ |
| 範囲の書式化・`from_range`・`flat_map`・`import std`・範囲 for の一時オブジェクトの寿命の延長 | C++23 | 15 | × | ○ |
| `views::concat`・`add_sat`・名前 `_` の複数宣言 | C++26 | 14〜15 | × | ×（`_` だけは警告つきで通る） |
| `ranges::starts_with`・`mdspan`・`views::indices` | C++23・C++26 | 16 | × | × |

各機能の使い方は、それぞれのページの「版」の項目にある。C++23 の views は [C++23 の views](../cpp/cpp-views-cpp23.md)、`format`・`println` は [入出力](../cpp/cpp-io.md#format-println)、deducing this は [ラムダ式](../cpp/cpp-lambda.md#deducing-this) で扱う。

- **落とし穴**：表の「GCC」は、その版から使えるようになったことを示す。`-std` が古いと使えない（`-std=gnu++20` では C++23 の機能が使えない）

## GCC 13 で通らない書き方（GCC 14〜・GCC 15〜の C++23 の機能） {#gcc13-limits}

AtCoder の GCC 15.2 で通る C++23 の機能のうち、次のものは g++-13 では `-std=gnu++23` でもコンパイルエラーになる。最近の解説コードや他人の提出に出てくるので、手元が g++-13 なら g++-15 を入れるのが早い。

```cpp
--8<-- "cpp-environment/gcc14-15.cpp:core"
```

g++-15 では `6` と `[1, 2, 3] 3 5` と出る。g++-13 で 1 つずつ試したエラーは次のとおりだった。

| 機能 | GCC | g++-13 のエラー | 書き換え |
| --- | --- | --- | --- |
| deducing this | 14 | `expected identifier before 'this'` | `auto&& self` を引数で渡す（[再帰ラムダ](../cpp/cpp-lambda.md#recursive-lambda)） |
| `println` | 14 | `'println' was not declared in this scope` | `cout` か `printf` |
| `ranges::to` | 14 | `'to' is not a member of 'std::ranges'` | [ranges::to](../cpp/cpp-views-cpp23.md#ranges-to) の代わりの書き方 |
| `format("{}", v)` | 15 | `std::formatter must be specialized for each type being formatted` | ループで出す（[そのままでは出力できない型](../cpp/cpp-io.md#unprintable-types)） |
| `from_range` | 15 | `'from_range' was not declared in this scope` | イテレータの組で作る（[from_range](../cpp/cpp-views-cpp23.md#from-range)） |
| `flat_map` | 15 | `'flat_map' was not declared in this scope` | `map` |

コンパイルエラーにならず、g++-13 では結果だけが壊れるものもある。範囲 for に関数の戻り値の中身を渡す `for (int x : d.groups()[0])` の形（参照を返すメンバ関数や `[]` を通す形）は、GCC 15 から一時オブジェクトの寿命が延びて安全になったが、g++-13 では未定義動作になる（[一時オブジェクトの中身を渡すとき](../cpp/cpp-range-for.md#temporary-range)）。

- **誤警告**：`generator`（GCC 14〜）は、g++-15 の `-O2 -Wall` で `-Wmismatched-new-delete` の警告が出た。コードの誤りではない

## AtCoder で使えないもの：C++26 の機能と GCC 16 からの機能 {#not-on-atcoder}

AtCoder は `-std=gnu++23` なので、GCC 15 が持っていても C++26 の機能は使えない。手元の g++-15 の `-std=gnu++23` では、`views::concat` が `'concat' is not a member of 'std::views'` のエラーになった。`add_sat`（あふれたら最大値で止まる足し算）も `'add_sat' was not declared in this scope` になった。どちらも `-std=gnu++26` なら通る。手元で `-std=gnu++26` を付けて試すと、AtCoder で CE になるコードを見逃す（[views::concat](../cpp/cpp-views-cpp23.md#concat)）。

例外は、名前 `_` の変数を同じ場所で何度も宣言する書き方（C++26）で、g++-15 の `-std=gnu++23` では警告つきで通る。

```cpp
--8<-- "cpp-environment/placeholder.cpp:core"
```

g++-15 では `name-independent declarations only available with '-std=c++2c'` と警告して `6` と出る。g++-13 では `conflicting declaration` のエラーになる。警告の出るコードは、提出の前に名前を付け直しておく。

GCC 16 から入る機能は、`-std=gnu++26` を付けても g++-15 にはない。次の 3 つは、どれも g++-15 でコンパイルエラーになった。`ranges::starts_with` は範囲の先頭が別の範囲と一致するかを判定し、`mdspan` は 1 次元の配列を多次元として見る。`views::indices` は `0` から `n - 1` の添字の列を作る。文字列の `s.starts_with(t)`（C++20）は使える（[文字列の操作](../cpp/cpp-string-api.md#starts-with)）。

## 確認問題 {#quiz}

??? question "確認問題：関数の中で `long long sum;` と書いて足し始めたコードが AtCoder で AC した。手元で答えが変になるのはなぜか？"
    AtCoder は `-ftrivial-auto-var-init=zero` 付きでコンパイルするので、初期値のない `sum` が 0 から始まる。手元の g++ には付いていないので、`sum` はゴミの値から始まる。規格の上では未定義動作なので、`long long sum = 0;` と初期値を書いて直す。

??? question "確認問題：手元でだけ Segmentation fault になる典型的な原因を 2 つ挙げよ"
    1 つは深い再帰で、一直線の木などで深さが $10^5$ を超えると、手元の 8 MiB のスタックを使い切ることがある（1 段の大きさによる）。`ulimit -s unlimited` で通るかを試す。もう 1 つは関数の中の大きな配列で、`int a[10000000];` は 40 MB のスタックを使う。グローバルに置くか `vector` にする。

??? question "確認問題：同じ再帰のコードが、`-O0` だと `-O2` より浅い深さで落ちるのはなぜか？"
    最適化しないと、局所変数や途中の値をすべてスタックに置くので、1 段の大きさが大きくなるからである。上の再帰ラムダでは、8 MiB の上限で `-O2` は深さ $2.2 \times 10^5$ まで通ったが、`-O0` は $7 \times 10^4$ で落ちた。

??? question "確認問題：`#pragma GCC target("avx2")` のない提出が、手元より遅いということはあるか？"
    `target` がないことは原因にならない。AtCoder は `-march=native` 付きでコンパイルするので、ジャッジの CPU が持つ命令（AVX2 など）はもともと使われる。AtCoder でだけ遅いなら、大きな局所配列を何度も 0 で埋めていないか（`-ftrivial-auto-var-init=zero`）を疑う。

## 参考 {#references}

- [traP「【非公式】[C++] AtCoder ジャッジアップデート (2024–2025) について」](https://trap.jp/post/2589/)：GCC 版のおもなオプション、ACL 1.6、Clang 版（libc++）にない機能
- [punirunrun「【非公式】AtCoder 言語アップデート 2024-2025 での変更点」](https://qiita.com/punirunrun/items/9bbdb33ef03e9a3a5138)：C++ の言語の一覧（GCC 15.2.0・Clang 21.1.0・IOI-Style）
- [reika727「AtCoder をやるときはスタックサイズを調整しとけ」](https://qiita.com/reika727/items/8fa6f5944b183c0a28f9)：2023-06 時点の AtCoder のスタックの上限（1 GiB）と、手元の 8 MiB との差
- AtCoder の GCC 版のオプションの一覧（`-ftrivial-auto-var-init=zero`・`-fmodules` を含む）は、AtCoder の公式の言語の一覧（2025-10 の言語アップデートの時点）による。上の traP の記事の「主要なコンパイルフラグ」には `-ftrivial-auto-var-init=zero` が載っていない
- [GCC「Options That Control Optimization」](https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html)：`-ftrivial-auto-var-init` の意味と、`-ffp-contract` の既定が `fast` であること
- [GCC「GCC 14 Release Series: Changes」](https://gcc.gnu.org/gcc-14/changes.html)：deducing this・`print`・`ranges::to` が GCC 14 から入ったこと
- [GCC「GCC 15 Release Series: Changes」](https://gcc.gnu.org/gcc-15/changes.html)：範囲の書式化・`from_range`・`flat_map`・`std` モジュール、最適化なしのビルドで検査が有効になること
- [GCC「libstdc++ Implementation Status」](https://gcc.gnu.org/onlinedocs/libstdc++/manual/status.html)：ライブラリの機能ごとの GCC の版
- [cppreference「C++23 compiler support」](https://en.cppreference.com/cpp/compiler_support/23)：C++23 の機能ごとの GCC の版
- [AtCoder Library のリリース](https://github.com/atcoder/ac-library/releases)：v1.6 の変更点（`val()` の型）
