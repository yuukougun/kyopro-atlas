# cpp-templates-constexpr の報告（工程8b・バッチ b1）

- 書いたファイル：docs/cpp/cpp-templates-constexpr.md、snippets/cpp-templates-constexpr/（21 組。本文に取り込まない確認用：abbrev-cxx17・unused-warn・assume-cxx20）。図はなし（visual: null）
- front matter で変えたもの：complexity・stage（draft）・cpp_std（20）・gcc_min（13）。updated は 2026-10-21 のまま（今日）
- 検査：check_pages エラー0・警告0、fix_problems --check 0 行、check_snippets 21 片・期待と違う 0（g++-13・g++-15）、textlint エラー0・警告0
- 出典：cppreference（template_argument_deduction・type_identity・fold・attributes/assume）、cpprefjp（constexpr・if_constexpr）、GCC の C++ Dialect Options（-fconstexpr-loop-limit 既定 262144、-fconstexpr-ops-limit 既定 33554432）、github.com の maspy my_template.hpp（chmin/chmax が template <class T, class S>）。新しいドメインはなし

## 台帳への提案

- なし（problems_note のとおり、C++ のページは ABC の問題を置かない）

## 用語集への提案

- 型推論｜type-deduction｜関数テンプレートを呼んだとき、引数の型から型引数を決めること。引数ごとに別々に行い、食い違うと失敗する。変換（int → long long）は考えない
- インスタンス化｜instantiation｜関数テンプレートから、決まった型引数ごとに実際の関数をコンパイラが作ること
- 可変長テンプレート｜variadic-template｜`template <class... Ts>` の形で、型引数をいくつでも取るテンプレート。引数のまとまりをパラメータパックと呼ぶ
- 定数式｜constant-expression｜コンパイル時に値が決まる式。constexpr の変数の初期化・配列の大きさ・static_assert の条件に使う
- 本文ではこれらを用語集へリンクしていない（語の説明は本文に書いた）。足したらリンクを付けてよい

## front matter・catalog への提案

- cpp_std を 20 にした（コンセプト・auto 引数が C++20）。ただし [[assume]] の節だけ C++23。gcc_min 13 は [[assume]] による。版の一覧で節ごとに版を持たせるなら sections に版を書く項目がほしい
- 逆引き（cpp-reverse-index#compile-errors）に「`deduced conflicting types for parameter` → #deduction-failure」「`'constexpr' loop iteration count exceeds limit of 262144` → #constexpr」「`constraints not satisfied` → #concepts」を載せる
- 早見表：`max<long long>(a, b)`・`min({a, 3LL, b})`・`constexpr auto T = [] { … }();` の 3 行

## 手引きへの提案

- §13.2（見出しと title を同じにする）で、title に `[[...]]` や `((cerr << ...` のようなコードを含むとき、見出しにバッククォートを付けないことを明記するとよい（views の見本に合わせた）
- type cpp のページの complexity の書き方（「実行時の速さは手書きと同じ」のような文でよいか）の例を §2.1 に足すとよい

## 問題の補充の候補

- なし（C++ のページは問題を置かない方針）

## 未解決の点

- GCC は [[likely]]・[[assume]] を -std=gnu++17 でも警告なしで受け付けた（-pedantic でも警告なし）。auto 引数は gnu++17 で警告つき。本文にはこの確かめた結果だけを書いた
- 2×10^5 までの篩の constexpr のコンパイルに g++-15 で約 10 秒・g++-13 で約 14 秒（手元の WSL2）。AtCoder のコンパイル時間の上限は確かめていないので、本文には書いていない
- 「cerr への出力は AtCoder では採点されない」は一般的な知識として書いた（AtCoder のページは開いていない）。cpp-environment のページと食い違わないか、メインで確かめてほしい
- 使用量の目安：道具の呼び出し 約 30 回、Web 取得 2 回

## 検証の指摘への対応（2026-10-21）

- 指摘 1〜7 はすべて直した。採らなかった指摘はない
- 指摘 1：`if constexpr` の落とし穴を「関数テンプレートの中で、枝の中身が型引数に依存するときだけ捨てられる」に直し、本文の説明も「型ごとに作るとき、選ばれなかった枝は作らない」にした
- 指摘 3・7：attributes.cpp を `core`（`[[nodiscard]]` の関数）と `body`（属性を使う行）の 2 つの印に分け、入力の読み込みを印の外に出した。`[[assume]]` の前提（入力が 0 以上）をコメントと本文に書いた
- 共有ファイルへの新しい提案はない
