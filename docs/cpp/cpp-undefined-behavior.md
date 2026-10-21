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
complexity: null
signs: []
acl: []
sections:
  - {title: 未定義動作とは：何が起きてもよく、最適化の前提に使われる（手元と AtCoder、-O0 と -O2 で結果が変わる）, anchor: what-is-ub}
  - {title: 他の行まで壊す：あふれる式があると、-O2 では正しく書いた別の式の値まで変わる, anchor: breaks-other-lines}
  - {title: 配列の範囲外：既定では止まらない, anchor: out-of-range}
  - {title: 未初期化変数：手元では不定、AtCoder では -ftrivial-auto-var-init=zero で 0 になる（-Wall は配列の未初期化を警告しない）, anchor: uninitialized}
  - {title: ダングリングとは：寿命の切れた要素・一時オブジェクト・文字列を指す参照・イテレータ・string_view（確かめた 4 つの型を次の節に並べる）, anchor: dangling}
  - {title: 'ダングリング①：const auto& [d, v] = pq.top(); pq.pop(); で値が変わる（どの道具でも見つからない。値で受ける）', anchor: dangling-pq-top}
  - {title: 'ダングリング②：auto& row = g[0]; の後の push_back で再確保され、row が消えた領域を指す', anchor: dangling-reallocation}
  - {title: 'ダングリング③：範囲 for の一時オブジェクト（for (int v : d.groups()[0]) は C++23・GCC 15〜でだけ安全。変数に受けてから回す）', anchor: dangling-temporary}
  - {title: ダングリング④：string_view に一時的な string を入れる, anchor: dangling-string-view}
  - {title: そのほかの未定義動作：比較関数の誤り・型の幅以上のシフト・__builtin_ctz(0)・ループ中のコンテナの変更, anchor: other-ub}
  - {title: 見つける道具と見つけられるもの：-Wall -Wextra・-D_GLIBCXX_ASSERTIONS・-D_GLIBCXX_DEBUG・-fsanitize=address・-fsanitize=undefined, anchor: detection-tools}
  - {title: '不具合を探すビルドを cph とは別に用意する（g++-15 -std=gnu++23 -O1 -g -D_GLIBCXX_DEBUG -fsanitize=address,undefined -DLOCAL。遅くなる）', anchor: debug-build}
  - {title: assert で WA を RE に変えて気づく（AtCoder では NDEBUG が付かない）, anchor: assert}
stage: stub
updated: 2026-10-21
cpp_std: null
gcc_min: null
atcoder: null
---

!!! abstract "要点"
    - **何ができるか**：あふれ・範囲外・未初期化変数・ダングリングなどの未定義動作が、-O2 や手元と AtCoder で結果を変える仕組みを知り、デバッグ用のビルドで見つける。ダングリングの 4 つの型も示す。
    - **いつ使うか**：（執筆時に書く）
    - **計算量**：（執筆時に書く）
    - **前提**：[AtCoder と手元の C++ 環境](../cpp/cpp-environment.md)、[整数のオーバーフローと \_\_int128](../cpp/cpp-integer-overflow.md)、[構造化束縛と pair・tuple・optional](../cpp/cpp-structured-bindings.md)
