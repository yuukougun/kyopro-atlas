---
title: C++
type: generated
---

<!-- tools/gen_site.py が生成する。手で直さない -->

# C++

解説コードに出る書き方、AtCoder と手元の環境、落とし穴、ACL の読み方。20 ページ（準備中 19）。

| ページ | レベル | 要約 |
| --- | --- | --- |
| [C++ の逆引き](cpp-reverse-index.md)（準備中） | — | 解説コードの書き方・実行時の症状・コンパイルエラーのメッセージから、意味と C++ 章の該当する節を引く。1 行を「何を回すか・何を受け取るか・どう受け取るか」に分けて読む手順も示す。 |

## 型と値

| ページ | レベル | 要約 |
| --- | --- | --- |
| [数の型とリテラル](cpp-types-literals.md)（準備中） | 基礎 | 整数・浮動小数点数の型とリテラル、INF の値を、値が収まり意図どおりの型になるように選ぶ。auto x = 0 が int、1e18 が double になるような、型のずれによる誤りを防ぐ。 |
| [整数のオーバーフローと \_\_int128](cpp-integer-overflow.md)（準備中） | 基礎 | int どうしの積・1 << k・size() の符号なしなど、型の幅を超えて値が壊れる書き方を見分けて直す。64 bit を超える中間値は GCC の拡張 \_\_int128 で持てるが、入出力などに制限がある。 |
| [初期化と CTAD](cpp-initialization.md)（準備中） | 基礎 | vector・多次元 vector・array・構造体を、意図した大きさと初期値で作る。型引数を省いて中身から型を決める CTAD（C++17）と、括弧の種類で意味が変わる罠も分かる。 |
| [数・ビット・乱数の関数](cpp-math-functions.md)（準備中） | 基礎 | gcd・割り算・sqrt などの数の関数、popcount・bitset などのビットの関数、乱数と時間計測を正しく使う。整数の割り算が 0 に向かって切り捨てることや、sqrt の誤差に気をつける。 |

## 参照・ラムダ・テンプレート

| ページ | レベル | 要約 |
| --- | --- | --- |
| [参照と範囲 for](cpp-range-for.md)（準備中） | 基礎 | 値をコピーで受けるか参照で受けるかを選び、範囲 for と関数の引数で無駄なコピーと書き換え漏れを防ぐ。値渡しの再帰が遅い理由と、swap が O(1) の理由も分かる。 |
| [構造化束縛と pair・tuple・optional](cpp-structured-bindings.md)（準備中） | 基礎 | pair・tuple・構造体の中身に名前を付けて取り出し（構造化束縛）、tie・optional で組や「値がない」を表す。pq.top() を参照で受けてから pop するような、受け方の誤りを防ぐ。 |
| [ラムダ式と再帰ラムダ](cpp-lambda.md)（準備中） | 基礎 | その場で関数を作るラムダ式で、比較関数・判定関数・DFS を書く。ラムダで再帰する 4 つの書き方（std::function・auto&& self・deducing this・不動点コンビネータ）の違いと速さも比べる。 |
| [関数テンプレートと constexpr](cpp-templates-constexpr.md)（準備中） | 基礎 | 型を引数にした関数（テンプレート・auto 引数・コンセプト）と、コンパイル時に値を決める constexpr・static_assert を読み書きする。chmin(a, 3) が通らないような型推論の失敗を避ける。 |
| [マクロと雛形](cpp-macros-template-file.md)（準備中） | 基礎 | 解説コードの先頭に並ぶ #include・using namespace std・マクロ・chmin・#pragma の意味と落とし穴が分かる。自作のヘッダを使うコードを、提出前に 1 ファイルに展開する方法も示す。 |

## コンテナ・アルゴリズム・ACL

| ページ | レベル | 要約 |
| --- | --- | --- |
| [コンテナ操作とイテレータ](cpp-container-idioms.md)（準備中） | 基礎 | set・map・multiset の定型の操作（erase_if・contains・1 個だけ消す）とイテレータを正しく書く。map の [] が要素を作る、set に std::lower_bound を使うと遅い、などの事故を防ぐ。 |
| [比較関数と順序](cpp-comparators.md)（準備中） | 基礎 | sort・set・priority_queue に渡す比較関数を約束（厳密弱順序）と向きを守って書き、構造体に operator< や <=> で順序を持たせる。比較関数に <= を書いて sort が落ちるような事故を防ぐ。 |
| [アルゴリズム関数と ranges 版](cpp-algorithms.md)（準備中） | 基礎 | sort・unique・lower_bound・accumulate などの定型と、射影も使える ranges 版（C++20）を使い分ける。accumulate の初期値の型や、unique だけでは要素が減らない点に気をつける。 |
| [文字列の操作](cpp-string-api.md)（準備中） | 基礎 | std::string の操作（substr・find・+=・数との変換）と string_view を、計算量と寿命に気をつけて書く。s = s + c が全体をコピーして遅いことや、cin >> の後の getline の罠を防ぐ。 |
| [ACL の読み方](acl-reading.md)（準備中） | 基礎 | AtCoder Library（ACL）を使う解説コードを、共通の約束（0 始まり・半開区間）とともに読む。modint の val() と出力、segtree・lazy_segtree のテンプレート引数にラムダを渡す書き方が分かる。 |

## ranges と views

| ページ | レベル | 要約 |
| --- | --- | --- |
| [views の基本](cpp-views-basics.md) | 基礎 | \| でつなぐ views（iota・filter・transform・split など）を、取り出すときに計算する遅延評価として読み書きする。views::iota(0, v.size()) が通らない理由など、型と寿命の罠も分かる。 |
| [C++23 の views と ranges::to](cpp-views-cpp23.md)（準備中） | 基礎 | C++23 の views（enumerate・zip・pairwise・chunk_by など）で添字付きや隣どうしのループを短く書き、ranges::to で結果をコンテナにする。要素は参照を含む組で、受けた変数への代入が元を変える。 |

## 入出力・環境・落とし穴

| ページ | レベル | 要約 |
| --- | --- | --- |
| [入出力と定数倍](cpp-io.md)（準備中） | 基礎 | 入出力を速くし（sync_with_stdio・cin.tie）、println・小数の桁の指定・インタラクティブ問題のフラッシュを正しく書く。C++ の書き方が原因で TLE になる例も、計測つきで示す。 |
| [AtCoder と手元の C++ 環境](cpp-environment.md)（準備中） | — | 手元の g++ と AtCoder（GCC 15.2・-std=gnu++23）の違いで結果が変わる場面（未初期化変数・スタック・GNU 拡張・ACL の版）を知り、同じ条件で試す。各機能が GCC のどの版から使えるかも分かる。 |
| [未定義動作とダングリング](cpp-undefined-behavior.md)（準備中） | 基礎 | あふれ・範囲外・未初期化変数・ダングリングなどの未定義動作が、-O2 や手元と AtCoder で結果を変える仕組みを知り、デバッグ用のビルドで見つける。ダングリングの 4 つの型も示す。 |
