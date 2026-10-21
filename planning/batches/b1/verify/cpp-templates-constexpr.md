# cpp-templates-constexpr の検証（工程8b・バッチ b1）

- 対象：docs/cpp/cpp-templates-constexpr.md、snippets/cpp-templates-constexpr/（21 組）。図はない（visual: null）
- 観点：fact.md・code.md・clarity.md・figure.md
- 検証日：2026-10-21

## 実行した検査と環境

- コンパイラ：g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0、g++-13 (Ubuntu 13.4.0-6ubuntu1~22~ppa2) 13.4.0
- `python3 tools/check_pages.py --page cpp-templates-constexpr`：エラー 0・警告 0
- `python3 tools/check_snippets.py snippets/cpp-templates-constexpr`：21 片・コンパイル 42 回・期待と違う 0
- `npx textlint docs/cpp/cpp-templates-constexpr.md`：出力なし（エラー 0）
- 本文に引いたエラー・警告の文面を、両方の版で `-std=gnu++23 -Wall -Wextra` によって出し直した。`chmin(long long int&, int)` と `deduced conflicting types for parameter 'const T'`、`max` の `deduced conflicting types`、`constraints not satisfied`、`refers to a result of 'operator new'`、`'constexpr' loop iteration count exceeds limit of 262144`、`'begin' was not declared in this scope`、`[[nodiscard]]` の `-Wunused-result`（`-Wall` なしでも出る）。どれも本文と一致した
- `chmin-narrow` は `-Wall -Wextra` で警告なし、`-Wconversion` を足すと `conversion from 'long long int' to 'int' may change value` が出る（本文どおり）。出力 5 は $-(2^{32}) + 5 \bmod 2^{32} = 5$ で手計算と合う
- `auto` 引数は `-std=gnu++17` で警告つき、`-std=c++17 -pedantic-errors` でエラー（本文どおり）
- GCC の既定の上限：GCC のドキュメント（C++ Dialect Options）で `-fconstexpr-loop-limit` 既定 262144 (1<<18) を確かめた。`-fconstexpr-ops-limit` の 33554432 は、200000×200 回のループの定数式で `'constexpr' evaluation operation count exceeds limit of 33554432` が出ることで確かめた
- $2 \times 10^5$ までの篩の constexpr：g++-15 `-O2` で 12.3 秒（手元の WSL2）。本文の「約 10 秒」と同じ程度
- 参考の URL 9 件を curl で取得し、すべて 200。cppreference の `/cpp/...` の形は、従来の `/w/cpp/...` から転送される今の正しい URL である。maspy の my_template.hpp の `chmin` が `template <class T, class S>` であることを確かめた
- 試しのコードは scratchpad/v-cpp-templates-constexpr/ に置いた（ic1.cpp・ic2.cpp・ce.cpp・ops.cpp・sieve.cpp・mod.cpp）

## 指摘

### 1｜直すべき｜事実（F2）｜#static-assert の「落とし穴」（`if constexpr` で枝を捨てられる条件）

- **問題**：「`if constexpr` で枝を捨てられるのは、条件が型引数に依存しているときだけである」は誤り。条件が型引数に依存しなくても、テンプレートの中なら捨てた枝はインスタンス化されない。逆に、条件が型引数に依存していても、捨てた枝の中にある型引数に依存しない誤りはエラーになる。決め手は条件ではなく、「テンプレートの中か」と「捨てた枝の中身が型引数に依存するか」である
- **根拠**：(a) ic1.cpp：`template <class T> void f(const T& x) { if constexpr (sizeof(int) == 4) { cout << x; } else { for (auto& e : x) …; } }` を `f(3)` で呼ぶ。条件は `T` に依存しないが、g++-13・g++-15 とも通った。(b) ic2.cpp：条件 `is_integral_v<T>` は `T` に依存するが、捨てた枝に `int y = 0; for (auto& e : y)` と書くと、両方の版で `there are no arguments to 'begin' that depend on a template parameter` のエラーになった。規格の [stmt.if] も「外側のテンプレートのインスタンス化の間に、捨てた枝をインスタンス化しない」という書き方であり、条件が依存することは要件ではない（cpprefjp「if文のconstexpr」も同じ趣旨）
- **直し方**：たとえば「`if constexpr` で捨てた枝がコンパイルされないのは、関数テンプレートの中で、枝の中身が型引数（`T` や `x`）に依存しているときだけである。テンプレートでない普通の関数の中や、`T` に関係しない誤りは、捨てた枝でもエラーになる」とする。本文 204 行の「選ばれなかった側の枝をコンパイルしない」も、この落とし穴とつながるように「型ごとに作るとき、選ばれなかった側の枝を作らない」くらいに直すとよい

### 2｜直すとよい｜事実（F2）｜#constexpr の 1 段落目（constexpr 関数がいつコンパイル時に計算されるか）

- **問題**：「引数がコンパイル時に決まっていればコンパイル時に計算され」は言い過ぎ。コンパイル時の計算が保証されるのは、`constexpr` の変数の初期化・`static_assert`・配列の大きさなど、定数式が要る場所で呼んだときだけである。普通の式の中ではコンパイラ次第になる
- **根拠**：ce.cpp で、ループを含む `constexpr` 関数 `fib` を `long long x = fib(…);`（`constexpr` なしの変数）で呼び、g++-15 `-O0` のアセンブリを見た。`fib(200000)` は呼び出しが消えていた（GCC が試しに計算した）が、`fib(1000000)` は上限の 262144 を超えるので、エラーも警告もなく実行時の `call _Z3fibx` になった。cpprefjp「constexpr」も、定数式の文脈で使ったときにコンパイル時に評価される、という書き方である
- **直し方**：「`constexpr` を付けた関数は、定数式が要る場所（`constexpr` の変数の初期化や `static_assert`）で呼べばコンパイル時に計算され、実行時の値で呼べば普通の関数として動く。普通の式の中で呼んだときにコンパイル時に計算されるかは、コンパイラに任される」とする。必ずコンパイル時に計算したい値は `constexpr` の変数に入れる、と一言足すと、すぐ後の `TEN` の書き方の理由にもなる

### 3｜直すとよい｜事実（F2）・コード（C8）｜#attributes の attributes.cpp の `[[assume(g >= 0)]]`

- **問題**：入力に負の数があると `g` が負になり、`[[assume]]` の式が偽になって未定義動作になる。本文が「式が偽になると未定義動作」と注意している、まさにその例を見本のコードに含んでいる。cases は非負の値だけなので、検査では見えない
- **根拠**：`gcd_ll(0, -4)` は `b != 0` なので `gcd_ll(-4, 0 % -4)` = `gcd_ll(-4, 0)` となり、`-4` を返す（`%` は被除数の符号を持つ）。入力 `1\n-4\n` で `g = -4` になる
- **直し方**：コメントに前提を書く（例：`// 入力の a は 0 以上なので g >= 0。前提が崩れると未定義動作`）か、`gcd_ll` の中で `abs` を取ってから仮定する。本文の 251 行の後に「前提が本当に成り立つときだけ書く」と添えてもよい

### 4｜直すとよい｜事実（F2）｜#attributes の「版」（`-std=gnu++17` で通る理由）

- **問題**：「4 つとも `-std=gnu++17` でも警告なしで通った（GCC の拡張）」とあるが、GNU の拡張モードかどうかは関係がない。厳密モード `-std=c++17 -Wall -Wextra -pedantic` でも、g++-13・g++-15 とも attributes.cpp は警告なしで通った。`auto` 引数（gnu++17 で警告、`-pedantic-errors` でエラー）とは事情が違うので、「GCC の拡張」と並べると同じ種類の話に読める
- **根拠**：`g++-13/15 -std=c++17 -Wall -Wextra -pedantic -fsyntax-only attributes.cpp` の出力が空
- **直し方**：「手元の g++-13・g++-15 では、4 つとも `-std=c++17 -pedantic` でも警告なしで通った。ただし C++17 の規格にない属性の扱いはコンパイラ次第なので、AtCoder と同じ `-std=gnu++23` で使う」くらいにする

### 5｜直すとよい｜事実（F3）｜#abbreviated-template の「版」の警告の文面

- **問題**：引いた警告が途中で切れている。実際は `use of 'auto' in parameter declaration only available with '-std=c++20' or '-fconcepts'` で、g++-15 は末尾に `[-Wc++20-extensions]` が付く。エラーの文で検索する読者には、全文のほうが引きやすい
- **根拠**：`g++-13/15 -std=gnu++17 -fsyntax-only abbrev-cxx17.cpp` の出力
- **直し方**：`… only available with '-std=c++20' or '-fconcepts'` まで書く

### 6｜直すとよい｜分かりやすさ（U2）・事実（F2）｜#concepts の「条件がないと、… 意味の分かりにくいエラーになる」

- **問題**：条件を外して `floor_div(7.0, 2.0)` を呼ぶと、エラーは `invalid operands of types 'double' and 'double' to binary 'operator%'` で、この短い例では十分に分かりやすい。読者が実際に試すと、本文と合わないと感じる
- **根拠**：mod.cpp（条件を外した floor_div）を g++-15 でコンパイルした結果
- **直し方**：コンセプトの利点を「エラーが呼んだ行に出て、どの条件を満たさないかが示される。条件がないと、エラーは関数の中の行（ライブラリなら深いところ）に出る」と、エラーの出る場所の違いとして書く

### 7｜直すとよい｜コード（C4）｜attributes.cpp の取り込みの範囲

- **問題**：`core` が `main` を含むプログラムの全体（約 20 行）になっている。手引き §9 は「要点の数行」を求めている。4 つの属性を見せたいのは分かるが、入力の読み込みなど属性と関係のない行が多い
- **根拠**：attributes.cpp の `// --8<-- [start:core]` が 4 行目、`[end:core]` が `main` の閉じ括弧の後
- **直し方**：`[[nodiscard]]` の関数、`[[maybe_unused]]` の行、`[[unlikely]]` の `if`、`[[assume]]` の行の 4 か所を、別々の印（例：`core`・`body`）で取り込むか、入力の読み込みを印の外に出す。nodiscard-warn.cpp の `core` も `main` を含むが、短いのでそのままでよい

## 執筆者の未解決の点について

- **gnu++17 の属性**：確かめた。`[[likely]]`・`[[assume]]` は `-std=gnu++17` だけでなく `-std=c++17 -pedantic` でも警告なしで通る（指摘 4）。`auto` 引数は gnu++17 で警告つき（本文どおり）
- **篩のコンパイル時間**：g++-15 で 12.3 秒と、報告と同じ程度。本文が AtCoder のコンパイル時間の上限に触れていないのは適切（確かめる手段がない）。「$10^5$ を超える表は実行時に作る」という助言で足りる
- **cerr は採点されない**：atcoder.jp は開いていない。docs/cpp/cpp-io.md の `cerr` の記述（87 行）とは食い違わない。cpp-environment のページには `cerr` の記述がなかった。メインでの確認はそのまま残る

## 問題がなかった点（抜粋）

- 型推論の失敗の理由（引数ごとに推論し、変換を考えない）、`type_identity_t` の働き、`max<long long>` で変換が効く理由、`min({…})` が C++11、`auto` 引数と `template <class T>` の対応、ラムダの `auto` 引数が C++14、ループを含む constexpr 関数が C++14・ラムダの constexpr が C++17、`static_assert` のメッセージの省略が C++17、畳み込み式の展開と空のパック（カンマは `void()`、`+` は初期値の 0）、`[[assume]]` が C++23・GCC 13 から、`[[nodiscard]]` の警告が `-Wall` なしでも出ること：すべて正しい
- 計算量の 3 か所（front matter・要点・本文）は一致している。確認問題 3 問は本文を読めば理由まで答えられ、答えに理由がある
- 断片で読んでも各節が自分の中で完結している（「chmin と同じく」は節の中で `max` の型の話として通じる）。だ・である調で、1 文の長さも目安の範囲
- 図：このページには図がなく、catalog の visual も null なので figure.md の観点は対象外

## 総合の判定

**小さな直しで可**。直すべき 1 件（`if constexpr` で枝を捨てられる条件の誤り）、直すとよい 6 件。コード片は 21 片とも両方の版で期待どおりで、本文に引いたエラーの文面もすべて再現した。
