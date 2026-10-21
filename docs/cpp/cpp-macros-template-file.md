---
id: cpp-macros-template-file
title: マクロと雛形
aliases: [マクロ, macro, テンプレート（雛形）, rep マクロ, all マクロ, '#define int long long', signed main(), chmin, chmax, '#ifdef LOCAL', '#pragma GCC optimize', bits/stdc++.h, using namespace std, import std;, 名前の衝突, バンドル, ライブラリの展開, expander.py, 提出用にコピー]
type: cpp
field: cpp
chapter: 参照・ラムダ・テンプレート
order: 100
level: 基礎
kind: [実装・C++]
prerequisites: [cpp-templates-constexpr]
related: [cpp-environment, cpp-undefined-behavior, cpp-types-literals, acl-reading, library-design]
summary: '解説コードの先頭に並ぶ #include・using namespace std・マクロ・chmin・#pragma の意味と落とし穴が分かる。自作のヘッダを使うコードを、提出前に 1 ファイルに展開する方法も示す。'
complexity: null
signs: []
acl: []
sections:
  - {title: '#include <bits/stdc++.h> と using namespace std', anchor: bits-stdcpp}
  - {title: '名前の衝突：count・y1 をグローバル変数の名前にするとエラー、std:: を省かない流儀、using namespace atcoder', anchor: namespaces}
  - {title: import std;：#include の代わりに標準ライブラリを読む。INT_MAX・assert などのマクロは来ない、手元では std モジュールを先に作る（C++23・GCC 15〜）, anchor: import-std}
  - {title: マクロは文字の置き換え：rep・all・vc/vvc と、引数の数で切り替える FOR, anchor: macros}
  - {title: '#define int long long と signed main()（printf・scanf の書式とも食い違う）', anchor: define-int}
  - {title: 'chmin・chmax：2 つの型を取る形と、return a < b && (a = b, true) のカンマ演算子', anchor: chmin}
  - {title: '#ifdef LOCAL・#ifndef ONLINE_JUDGE：手元だけのデバッグ出力を切り替える', anchor: ifdef-local}
  - {title: '#pragma GCC optimize・target：AtCoder は -march=native なので target は要らない、g++-13 では #include より前に書くとエラー、Ofast は浮動小数点の約束を変える', anchor: pragma}
  - {title: '自作のヘッダを #include "..." したコードは、提出前に 1 ファイルに展開する（バンドル）', anchor: bundling}
  - {title: 展開の道具：cph の「提出用にコピー」（#include "..." だけを展開）・ACL の expander.py（atcoder/ だけを展開し、v1.6 の --origname で元の行番号を出せる）・oj-bundle, anchor: bundling-tools}
  - {title: // @impl で main の後ろに回せるもの・回せないもの（auto を返す関数・定数式で使う constexpr 関数・クラスの定義は前に置く）, anchor: impl-marker}
stage: stub
updated: 2026-10-21
cpp_std: null
gcc_min: null
atcoder: true
---

!!! abstract "要点"
    - **何ができるか**：解説コードの先頭に並ぶ #include・using namespace std・マクロ・chmin・#pragma の意味と落とし穴が分かる。自作のヘッダを使うコードを、提出前に 1 ファイルに展開する方法も示す。
    - **いつ使うか**：（執筆時に書く）
    - **計算量**：（執筆時に書く）
    - **前提**：[関数テンプレートと constexpr](../cpp/cpp-templates-constexpr.md)
