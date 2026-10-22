# b5 検証：cpp-environment

- 対象：docs/cpp/cpp-environment.md、snippets/cpp-environment/（24 個）。図の SVG はない（catalog の visual は priority 2・static で、Markdown の表 3 つで代えている。G7 の点で問題なし。figure.md の G1〜G6 は対象なし）
- 観点：fact.md・code.md・clarity.md・figure.md
- 環境：g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0、g++-13 (Ubuntu 13.4.0-6ubuntu1~22~ppa2) 13.4.0、g++-11（版の確認だけ）。CPU は FMA あり。試しのコードは作業用の場所に置いた

## 実行して確かめたこと

- `python3 tools/check_snippets.py snippets/cpp-environment`：24 個・コンパイル 32 回・期待と違う 0。`python3 tools/check_pages.py --page cpp-environment -v`：エラー 0・警告 0
- 本文のリンク先の anchor（cpp-macros-template-file#import-std・#pragma・#ifdef-local、cpp-integer-overflow#int128-strict-mode、cpp-undefined-behavior#uninitialized・#debug-build、geometry-precision#integer-comparison、acl-reading#version、tree-traversal#recursion-depth、cpp-lambda#std-function・#deducing-this・#recursive-lambda、dfs#iterative、cpp-views-cpp23#ranges-to・#from-range・#concat、cpp-io#format-println・#unprintable-types、cpp-range-for#temporary-range、cpp-string-api#starts-with）はすべてある
- `-std` なしの `__cplusplus`：g++-13・g++-15 とも 201703。`-std=gnu++23` では g++-13 が 202100、g++-15 が 202302。g++-11 も `-std=gnu++23` を受け付けて 202100（指摘 3）
- gnu-mode：`-std=c++23` で typeof・`static_assert(is_integral_v<__int128>)`・gcd（static_assert）・abs（`call of overloaded 'abs(__int128&)' is ambiguous`）がエラー。可変長配列・`?:`・`case 1 ... 5:` は `-std=c++23 -Wall -Wextra` で通り、`-Wpedantic` で警告 4 件
- auto-var-init-cost（q = 2×10^5, k = 1）：g++-13・g++-15 とも、なし 0.04 秒、`-ftrivial-auto-var-init=zero` 1.03 秒。本文の 0.05・1.03 と一致。GCC の man（gcc-15）の `-ftrivial-auto-var-init` の説明（「未初期化」として扱い続け、警告・最適化はそのまま）も本文と一致
- FMA：`-O2` で 0、`-march=native` で `+ 1.66533e-18`／`- -1.33227e-17`、`-ffp-contract=off` で 0（g++-13・g++-15）。**`-std=c++23`（厳密モード）にしても `-march=native` では同じく FMA になった**（指摘 2）
- スタック（`ulimit -s 8192`、g++-15）：再帰ラムダ `-O2` は 2.2×10^5 で通り 2.4×10^5 で SIGSEGV、`-O0` は 6.5×10^4 で通り 7×10^4 で SIGSEGV、`std::function` 版（自分で書き換えた）`-O2` は 8×10^4 で通り 9×10^4 で SIGSEGV。unlimited では `-O2` で 10^7、`-O0` で 10^6 が通る。表と一致
- `main` の中の `int a[10000000];`：入力で埋めて使うと `-O2`・`-O0` とも SIGSEGV（8 MiB）
- PCH（`-std=gnu++23 -O2` で作成）：`-Wall -Wextra -ftrivial-auto-var-init=zero -DATCODER -DONLINE_JUDGE` を足しても `!`（使われた）。`-std=c++23` は `not used because 'unix' not defined`、`-g` は `created with 'none' debug info`、`-O2` なしと `-march=native` は `created and used with differing settings of …` で `x`。時間は 0.52 秒と 1.14 秒。本文と一致
- GCC 15 の `-O0` の検査：c++config.h に「`! defined(__OPTIMIZE__)` なら `_GLIBCXX_ASSERTIONS` を定義」とある。assertions-o0 は g++-15 の `-O0` だけ `Assertion '__n < this->size()' failed`、`-O1`・`-Og`・`-O2` と g++-13 は検査なし。本文と一致
- g++-13 のエラーの文面（deducing this・println・ranges::to・format・from_range・flat_map・`_` の再宣言）と、g++-15 の `concat`・`add_sat`（`-std=gnu++23`）、`ranges::starts_with`・`mdspan`・`views::indices`（`-std=gnu++26` でも）のエラー：すべて本文どおり。`-std=gnu++26` では concat・add_sat が通る。`<mdspan>` は g++-15 にファイルがない
- GCC 16 の行：gcc.gnu.org/gcc-16/changes.html に `std::mdspan` と `ranges::starts_with and ranges::ends_with` がある。`views::indices`（P3060R3）は cppreference の C++26 の対応表で GCC 16
- generator の誤警告：`n` を入力から読むコードで、g++-15 `-O2 -Wall` に `-Wmismatched-new-delete` が出た（定数の `g(5)` では出なかった）。本文の主張は正しい
- 範囲 for の一時オブジェクト：`for (int x : f().v)`（`v` はデータメンバ）は g++-13 の AddressSanitizer でもエラーなしで正しい値。`f().get()`（参照を返すメンバ関数）にすると g++-13 で `stack-use-after-scope`、g++-15 の `-std=gnu++23` では正しい（指摘 1）
- ACL：GitHub API で v1.6 の公開は 2025-05-01、「(Small) Breaking change：modint.val() から unsigned を外した」。third_party と ~/lib の modint.hpp の `val()` は `int`。acl-reading#version とも一致
- 参考の URL：trap.jp は check_noai で指定なし（執筆者も確認）。traP の記事（2025-06-04、GCC 15.1.0）の主要なフラグは `-std=gnu++23 -DONLINE_JUDGE -DATCODER -Wall -Wextra -O2 -march=native -flto=auto -lstdc++exp -fopenmp -fmodules` で、**`-ftrivial-auto-var-init=zero` はない**（指摘 6）。libc++ にないものの一覧（enumerate・zip の仲間・chunk・slide・stride・cartesian_product・fold_*・generator・stacktrace）は本文と一致。punirunrun の記事：C++23 (GCC 15.2.0)・C++ IOI-Style(GNU++20) (GCC 14.2.0)・C++23 (Clang 21.1.0) で一致。reika727 の記事：2023-06-24、1048576 KiB、手元 8192 KiB で一致。記事の文・例と本文は近すぎない（F8）
- 版の対応表の C++17〜C++23（GCC 13 まで）の行は知られている版（構造化束縛など GCC 7、指示付き初期化 8、範囲 for の初期化式・contains・erase_if 9、`<=>`・コンセプト・span 10、string::contains・uz 11、format 13、enumerate などの views・fold_left 13）と食い違いなし

## 指摘

### 1. 直すべき｜事実（F2）｜#gcc13-limits の最後の段落「`for (int x : f().v)` の形は…g++-13 では未定義動作になる」

- **問題**：例が誤り。`f().v` はデータメンバへのアクセスで、一時オブジェクトのサブオブジェクトに参照を結び付けると一時オブジェクト全体の寿命が延びる（C++17 以前からの規則）。そのため g++-13 でも安全である。壊れるのは、参照を返すメンバ関数や `operator[]` を通す形（`f().get()`・`d.groups()[0]`）
- **根拠**：作業用の場所で、`struct S { vector<int> v; const vector<int>& get() const { return v; } };` と `S f()` を用意した。g++-13 `-std=gnu++23 -O0 -fsanitize=address` では、`for (int x : f().v)` がエラーなく 7000 を出し、`for (int x : f().get())` は `stack-use-after-scope`。リンク先 cpp-range-for#temporary-range も `d.groups()[0]` の形で説明している
- **直し方**：「範囲 for に関数の戻り値の要素を渡す `for (int v : d.groups()[0])` の形は…」のように、リンク先と同じ例（または `f().get()` のような参照を返す関数を通す形）に替える

### 2. 直すべき｜事実（F2）｜#march-native の第 2 段落「GCC は、規格に厳密なモード以外では … （`-ffp-contract=fast` が既定）」

- **問題**：C++ では厳密モード（`-std=c++23`）でも既定は `fast`。「厳密なモード以外では」と書くと、`-std=c++23` にすれば FMA を避けられると読める
- **根拠**：man gcc-15 の `-ffp-contract`：「The default is -ffp-contract=off for C in a standards compliant mode (-std=c11 or similar), -ffp-contract=fast otherwise.」（off になるのは C の厳密モードだけ）。実測でも g++-13・g++-15 の `-std=c++23 -O2 -march=native` で `+ 1.66533e-18` が出た
- **直し方**：「GCC は C++ では既定で（`-std=c++23` でも）`a * b - c * d` のような 1 つの式を…FMA 命令で計算してよい（`-ffp-contract=fast` が既定）」とする

### 3. 直すべき｜事実（F2）｜#gnu-mode の「版」の項「`-std=gnu++23` は g++-13 から指定できる」

- **問題**：`-std=gnu++23` は GCC 11 から受け付ける。「g++-13 から」は最初の版を示すように読めて誤り
- **根拠**：手元の g++-11 で `echo | g++-11 -std=gnu++23 -x c++ -dM -E - | grep __cplusplus` が 202100L を出す
- **直し方**：「`-std=gnu++23` は GCC 11 から指定でき、g++-13 でも使える。ただし g++-13 の `__cplusplus` は 202100 で…」とする

### 4. 直すとよい｜事実・分かりやすさ（F2・U3）｜#quiz の 2 問目の答え「深さが $10^5$ を超えると、手元の 8 MiB のスタックを使い切る」

- **問題**：本文の表では、最小の再帰ラムダは `-O2` で 2.2×10^5 まで通っている。答えの断定は表と食い違って見える（#stack-depth の「$N = 2 \times 10^5$ … 落ちると思っておく」も、表の直後なので一瞬引っかかる）
- **根拠**：上の実測（2.2×10^5 で通る）
- **直し方**：「深さが $10^5$ を超えると…使い切ることがある（1 段の大きさによる）」とする。#stack-depth の文は「局所変数の多い DFS や `-O0` では落ちるので、落ちうると思っておく」のように理由を添えるとよい

### 5. 直すとよい｜事実（F2）｜#march-native の第 1 段落「`#pragma GCC target("avx2")` は、AtCoder では書かなくても同じである」と確認問題 4

- **問題**：ジャッジの CPU が AVX2 を持つことが前提だが、確かめていない（FMA については執筆者も未確認と認め「持てば」とぼかしている。AVX2 も同じ立場）
- **根拠**：`-march=native` が使うのはコンパイルする計算機の命令。ジャッジの CPU の命令セットは本文・参考のどこにもない
- **直し方**：「ジャッジの CPU が AVX2 を持てば、`#pragma GCC target("avx2")` は書かなくても同じである」とぼかすか、出典を足す

### 6. 直すとよい｜事実・出典（F9）｜#options の第 1 段落のオプションの一覧と、#auto-var-init 全体

- **問題**：AtCoder が `-ftrivial-auto-var-init=zero` を付けることは、このページの中心の主張の 1 つだが、参考の 3 つの記事のどれにもない（traP の主要なフラグの一覧にはない）。根拠は decisions.md だけで、読者からは出典をたどれない。traP に載っている `-fopenmp` は本文の一覧にない（「など」で済んではいる）
- **根拠**：traP の記事の「主要なコンパイルフラグ」（GCC 15.1.0 時点）を読んだ。punirunrun の記事は「コンパイルオプションが変更された」とだけ書き、traP を指している
- **直し方**：メインのセッションで decisions.md の出典（ユーザーが公式の一覧で確かめたものか）を確かめ、可能ならユーザーにコードテストで確かめてもらう（例：初期化しない `int x;` を出すコードが常に 0 になるか。ただし未定義動作なので補助的な確認）。参考には「AtCoder の言語の一覧（公式）による。この教材は decisions.md の記録に拠る」の旨の 1 行を足すとよい

### 7. 直すとよい｜分かりやすさ（U3）｜導入の第 1 段落「C++23 (GCC 15.2.0) と C++23 (Clang 21.1.0) の 2 つになった」

- **問題**：#gcc-or-clang の「ほかの版」で C++ IOI-Style（GNU++20、GCC 14.2.0）も出てくるので、「2 つ」と食い違って見える
- **根拠**：punirunrun の記事の一覧では C++ は 3 つ（6017・6054・6116）
- **直し方**：「おもに C++23 (GCC 15.2.0) と C++23 (Clang 21.1.0) の 2 つになった（ほかにライブラリのない IOI-Style がある）」とする

### 8. 直すとよい｜分かりやすさ（U2）｜#gnu-mode の 2 つ目の箇条「`is_integral_v<__int128>` … そのため `gcd`・`abs` に `__int128` を渡せない」

- **問題**：`gcd` は `is_integral` の static_assert で止まるが、`abs` は `call of overloaded 'abs(__int128&)' is ambiguous`（厳密モードでは `__int128` 用の `abs` が用意されない）で、「そのため」の因果は `abs` には当たらない
- **根拠**：`-std=c++23` での g++-13・g++-15 のエラーの文面（上の実行結果）
- **直し方**：「`gcd` は `static_assert` で止まり、`abs` は `__int128` 用の多重定義がなく曖昧になる。どちらも厳密モードでは `__int128` を整数型として扱わないため」とする

### 9. 直すとよい｜コード（C2）｜snippets/cpp-environment/fma-native.yaml

- **問題**：期待出力が、検査を動かす計算機の CPU が FMA を持つかに依存する。CI（gcc:15.2.0 のコンテナ）や週次の検査の計算機が FMA を持たなければ失敗する
- **根拠**：`-march=native` の挙動。GitHub の実行機は通常 FMA を持つので今は通るはずだが、環境で変わる検査になっている
- **直し方**：yaml にコメントで「FMA のある CPU が前提」と書く。本文に取り込まない確かめ用のコード片なので、検査から外してもよい

### 10. 直すとよい｜コード（C2）｜snippets/cpp-environment/judge-macros.yaml

- **問題**：`-DATCODER -DONLINE_JUDGE` を付けた `judge` の側しか検査していない。本文が述べる「付けなければ `local`」は検査に入っていない
- **根拠**：手でフラグなしでコンパイルすると `local`（本文どおり）
- **直し方**：フラグなしの設定のコード片（または同じコードの別の yaml）を足して `local` を確かめる

## 執筆者の未解決の点について

- 新ジャッジのスタックの上限・cph が ulimit を引き継ぐか：本文はぼかして書いており、確かめ方（stack-limit.cpp）もあるので、このままで誤りではない。ユーザーにコードテストで確かめてもらうとよい
- オプションの一覧（`-fopenmp`・`-ftrivial-auto-var-init=zero`）：指摘 6
- ジャッジの CPU が FMA を持つか：本文のぼかし方で可。AVX2 も同じ扱いにそろえる（指摘 5）
- Clang 21.1 の libc++：「非公式の記事（2025-06）によれば、当時の」と時点を明記しており可
- `-fstack-protector-strong` を本文に書かない判断：可

## 総合の判定

小さな直しで可。直すべきは 3 件（指摘 1〜3。どれも 1 文の書き換えで直る）、直すとよいは 7 件。数値の主張（時間・スタックの深さ・PCH・FMA の値・エラーの文面・版の表）はすべて再現した。
