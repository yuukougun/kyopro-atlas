---
title: C++
type: generated
---

<!-- tools/gen_site.py が生成する。手で直さない -->

# C++

解説コードに出る書き方、AtCoder と手元の環境、落とし穴、ACL の読み方。20 ページ。ページ名の横の印はレベル（[レベルの意味](../start/how-to-use.md#levels)）である。

学ぶ順：[色別ロードマップ](../guide/roadmap.md#reading-order)。使い分け：[集合とキュー](../guide/method-comparison.md#containers)・[数の扱い](../guide/method-comparison.md#numbers)。自作：[自作ライブラリの設計と動作確認](../guide/library-design.md)。

- [C++ の逆引き](cpp-reverse-index.md)：解説コードの書き方・実行時の症状・コンパイルエラーのメッセージから、意味と C++ 章の該当する節を引く。

## 型と値

- [数の型とリテラル](cpp-types-literals.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：整数・浮動小数点数の型とリテラル、INF の値を、値が収まり意図どおりの型になるように選ぶ。
- [整数のオーバーフローと \_\_int128](cpp-integer-overflow.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：int どうしの積・1 << k・size() の符号なしなど、型の幅を超えて値が壊れる書き方を見分けて直す。
- [初期化と CTAD](cpp-initialization.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：vector・多次元 vector・array・構造体を、意図した大きさと初期値で作る。
- [数・ビット・乱数の関数](cpp-math-functions.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：gcd・割り算・sqrt などの数の関数、popcount・bitset などのビットの関数、乱数と時間計測を正しく使う。

## 参照・ラムダ・テンプレート

- [参照と範囲 for](cpp-range-for.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：値をコピーで受けるか参照で受けるかを選び、範囲 for と関数の引数で無駄なコピーと書き換え漏れを防ぐ。
- [構造化束縛と pair・tuple・optional](cpp-structured-bindings.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：pair・tuple・構造体の中身に名前を付けて取り出し（構造化束縛）、tie・optional で組や「値がない」を表す。
- [ラムダ式と再帰ラムダ](cpp-lambda.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：その場で関数を作るラムダ式で、比較関数・判定関数・DFS を書く。
- [関数テンプレートと constexpr](cpp-templates-constexpr.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：型を引数にした関数（テンプレート・auto 引数・コンセプト）と、コンパイル時に値を決める constexpr・static_assert を読み書きする。
- [マクロと雛形](cpp-macros-template-file.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：解説コードの先頭に並ぶ #include・using namespace std・マクロ・chmin・#pragma の意味と落とし穴が分かる。

## コンテナ・アルゴリズム・ACL

- [コンテナ操作とイテレータ](cpp-container-idioms.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：set・map・multiset の定型の操作（erase_if・contains・1 個だけ消す）とイテレータを正しく書く。
- [比較関数と順序](cpp-comparators.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：sort・set・priority_queue に渡す比較関数を約束（狭義の弱順序）と向きを守って書き、構造体に operator< や <=> で順序を持たせる。
- [アルゴリズム関数と ranges 版](cpp-algorithms.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：sort・unique・lower_bound・accumulate などの定型と、射影も使える ranges 版（C++20）を使い分ける。
- [文字列の操作](cpp-string-api.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：std::string の操作（substr・find・+=・数との変換）と string_view を、計算量と寿命に気をつけて書く。
- [ACL の読み方](acl-reading.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：AtCoder Library（ACL）を使う解説コードを共通の約束（0-indexed・半開区間）とともに読む。

## ranges と views

- [views の基本](cpp-views-basics.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：| でつなぐ views（iota・filter・transform・split など）を、取り出すときに計算する遅延評価として読み書きする。
- [C++23 の views と ranges::to](cpp-views-cpp23.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：C++23 の views（enumerate・zip・pairwise・chunk_by など）で添字付きや隣どうしのループを短く書き、ranges::to で結果をコンテナにする。

## 入出力・環境・落とし穴

- [入出力と定数倍](cpp-io.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：入出力を速くし（sync_with_stdio・cin.tie）、println・小数の桁の指定・インタラクティブ問題のフラッシュを正しく書く。
- [AtCoder と手元の C++ 環境](cpp-environment.md)：手元の g++ と AtCoder（GCC 15.2・-std=gnu++23）の違いで結果が変わる場面（未初期化変数・スタック・GNU 拡張・ACL の版）を知り、同じ条件で試す。
- [未定義動作とダングリング](cpp-undefined-behavior.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：あふれ・範囲外・未初期化変数・ダングリングなどの未定義動作が、-O2 や手元と AtCoder で結果を変える仕組みを知り、デバッグ用のビルドで見つける。

## ほかの分野にある関連ページ {#elsewhere}

種類に[実装・C++](../lists/kind-implementation.md)を持つ、ほかの分野のページ。

- [データ構造](../ds/index.md)：[STL コンテナの使い分け](../ds/stl-containers.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>
- [整数論・代数](../math/index.md)：[modint](../math/modint.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>
- [その他の技法](../misc/index.md)：[インタラクティブ問題](../misc/interactive.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>
