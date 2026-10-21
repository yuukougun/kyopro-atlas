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
related: [cpp-undefined-behavior, cpp-macros-template-file, acl-reading, cpp-lambda, atcoder-system, dfs]
summary: 手元の g++ と AtCoder（GCC 15.2・-std=gnu++23）の違いで結果が変わる場面（未初期化変数・スタック・GNU 拡張・ACL の版）を知り、同じ条件で試す。各機能が GCC のどの版から使えるかも分かる。
complexity: null
signs:
  - {type: constraint, text: N ≤ 2×10^5 の木やグラフを再帰でたどる（一直線の入力では深さが N になり、手元の 8 MiB のスタックでは落ちることがある）}
acl: []
sections:
  - {title: AtCoder と手元のオプションの比較と、同じ条件で試すコマンド, anchor: options}
  - {title: '-std=gnu++23 と -std=c++23 の違い：GNU 拡張と __int128 の型特性', anchor: gnu-mode}
  - {title: '-ftrivial-auto-var-init=zero：AtCoder では未初期化の局所変数・配列が 0 になる', anchor: auto-var-init}
  - {title: '-march=native と #pragma GCC target：AtCoder では target の指定は要らない', anchor: march-native}
  - {title: '-DATCODER・-DONLINE_JUDGE：ジャッジでだけ定義されるマクロ', anchor: judge-macros}
  - {title: ACL の版：AtCoder は v1.6（modint の val() が int）。手元も v1.6 にそろえる, anchor: acl-version}
  - {title: 再帰の深さとスタック：手元の上限・ulimit -s unlimited・非再帰への書き直し, anchor: stack-depth}
  - {title: プリコンパイル済みヘッダ：作ったときと同じオプションのときだけ使われる（-Winvalid-pch で理由が出る）, anchor: pch}
  - {title: Clang 版（libc++）ではなく GCC 版を選ぶ, anchor: gcc-or-clang}
  - {title: 手元と AtCoder で結果が違うときに疑う順（未初期化変数 → 未定義動作 → スタック → ACL の版）, anchor: when-results-differ}
  - {title: C++ の版と GCC の対応表（g++-13 と AtCoder の GCC 15.2）, anchor: version-matrix}
  - {title: GCC 13 で通らない書き方（GCC 14〜・GCC 15〜の C++23 の機能）, anchor: gcc13-limits}
  - {title: AtCoder で使えないもの：C++26 の機能と GCC 16 からの機能, anchor: not-on-atcoder}
stage: stub
updated: 2026-10-21
cpp_std: null
gcc_min: null
atcoder: null
---

!!! abstract "要点"
    - **何ができるか**：手元の g++ と AtCoder（GCC 15.2・-std=gnu++23）の違いで結果が変わる場面（未初期化変数・スタック・GNU 拡張・ACL の版）を知り、同じ条件で試す。各機能が GCC のどの版から使えるかも分かる。
    - **いつ使うか**：N ≤ 2×10^5 の木やグラフを再帰でたどる（一直線の入力では深さが N になり、手元の 8 MiB のスタックでは落ちることがある）
    - **計算量**：（執筆時に書く）
    - **前提**：なし
