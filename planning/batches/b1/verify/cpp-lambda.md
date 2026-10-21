# cpp-lambda の検証（工程8b・バッチ b1）

- 対象：docs/cpp/cpp-lambda.md、snippets/cpp-lambda/（22 片）、docs/img/cpp-lambda/capture.svg・call-path.svg
- 観点：fact.md・code.md・clarity.md・figure.md
- 検証日：2026-10-21

## 実行した検査と環境

- `python3 tools/check_pages.py --page cpp-lambda`：エラー 0・警告 0
- `python3 tools/check_snippets.py snippets/cpp-lambda`：22 片・コンパイル 42 回・期待と違う 0
- `npx textlint docs/cpp/cpp-lambda.md`：出力なし（exit 0）
- コンパイラ：g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0、g++-13 (Ubuntu 13.4.0-6ubuntu1~22~ppa2) 13.4.0
- run の 12 片を `g++-15 -std=gnu++23 -O1 -g -fsanitize=address,undefined` で cases に通した：サニタイザの報告なし（出力の違いは行末の空白だけ）
- エラー・警告の文面を両方のコンパイラで確かめた：`use of ‘fact’ before deduction of ‘auto’`（recursive-ng）、`use of ‘main()::<lambda(auto:NN&&, ...)> ...’ before deduction of ‘auto’`（return-type-ng・void-ng）、`no matching function for call to ‘std::priority_queue<...>::priority_queue()’`（decltype-capture-ng）、`use of deleted function ‘main()::<lambda(int, int)>::<lambda>()’`（decltype-cxx17-ng、`-std=gnu++17`）、`the value of ‘op’ is not usable in a constant expression`（segtree-capture-ng。g++-13 も同じ文面）、`expected identifier before ‘this’`（g++-13 の deducing this）。本文の引用と一致する（static の警告だけ指摘 3）
- 本文の主張を小さなプログラムで確かめた（一時置き場の t1〜t5.cpp）：static ラムダにキャプチャを書くと `‘static’ lambda specifier with lambda capture` でエラー。その場で呼ぶラムダの `()` を忘れると、キャプチャありは `cannot convert ... to ‘const int’`、なしは `invalid user-defined conversion` でエラー。`auto self`（値渡し）でも再帰は動く。`return 1;` と `return 2LL;` を混ぜると `inconsistent types ‘int’ and ‘long long int’ deduced` でエラー。segtree.cpp は `-std=gnu++17` では `non-type template parameters of class type only available with ‘-std=c++20’` でエラー（本文の「C++20」と一致）
- ダングリングの例（dang.cpp）：g++-13・g++-15 の `-O2 -Wall -Wextra` で `‘k’ is used uninitialized` の警告が出て、実行すると 1 を出した。`-fsanitize=address` で `stack-use-after-return` で止まった（本文と一致）
- 速さの計測（bench.cpp・dfs.cpp、g++-15 `-O2`、各 3 回）：fib(40) は普通の関数 97.9〜103.6 ms・std::function 509.6〜518.4 ms・auto&& self 97.9〜101.5 ms・deducing this 103.9〜105.8 ms・FixPoint 0.3 ms。頂点数 2×10^6 の二分木（親 (v−1)/2）の DFS は 普通 7.0〜7.3 ms・std::function 8.4〜8.9 ms・self 5.4〜5.6 ms・deducing this 5.4〜5.6 ms・FixPoint 6.3〜7.1 ms。親をランダムに選んだ木はどれも 174〜206 ms で差なし。執筆者の未解決の点 1（fib(40) で約 5 倍、二分木で約 1.5 倍、ランダムな木は差が見えない）は再現した
- スタック 8 MiB（`ulimit -s 8192`）のパスの DFS（depth.cpp）：std::function は 8×10^4 で通り 9×10^4 で落ちた（表と一致）。auto&& self は 2.1×10^5 で通り 2.2×10^5 で落ちた（表は 2.2×10^5 で通る）。deducing this は 2.4×10^5 で通り 2.6×10^5 で落ちた（表と一致）
- 図：chrome-headless-shell 146 で SVG を 1280×600（2 倍密度）と幅 390px（表示幅 358px・2 倍密度）で画像にした（一時置き場の capture.png・call-path.png・narrow.png）。日本語のフォントがなく和文は豆腐になったので、和文の幅は字数×font-size で見積もった。背景は白で塗られており、ダークモードでも白地の図として読める
- 出典：参考の 11 件の URL はすべて 200 を返した。gcc.gnu.org の cxx-status で P0847R7（deducing this）が GCC 14、P1169R4（static operator()）が GCC 13 を確認。cpprefjp「状態を持たないラムダ式を…」でキャプチャのないラムダだけが既定構築できることを確認。ACL の segtree.hpp（third_party）は `#if __cplusplus >= 201703L` で `template <class S, auto op, auto e>`。cplusplus.github.io（CWG の issue 一覧）は `tools/check_noai.py` で noai の指定がないことを確かめてから読んだ（指摘 1）

## 指摘

### 1｜直すべき｜事実（F2・F4）｜#template-argument の 2 段落目（「キャプチャのないラムダは中身を持たない空のオブジェクトなので…（C++20 から、クラス型の値もテンプレート引数として使える）」）

- **問題**：キャプチャのないラムダをテンプレート引数に渡せることを、規格で保証された性質として説明している。しかし C++ の欠陥報告 CWG2542（2023 年 6 月に DR として採択）で、クロージャ型は（キャプチャの有無によらず）構造的型でないと決まった。今の規格ではクロージャ型の値を非型テンプレート引数にできず、GCC が受け入れているだけである。ACL のドキュメント（document_ja/segtree.md）も、ラムダを渡せるとは書いていない
- **根拠**：https://cplusplus.github.io/CWG/issues/2542.html （"[Accepted as a DR at the June, 2023 meeting.]"、expr.prim.lambda.closure に "The closure type is not an aggregate type and not a structural type" を足す）。g++-13・g++-15 の `-std=gnu++23` では通る（check_snippets と手で確認）。cppreference の lambda のページは「captures が空のときに限り構造的型（C++20）」のままで、DR を反映していない。資料どうしが食い違うので、一次資料（CWG）を正とした
- **直し方**：2 段落目を「GCC では、キャプチャのないラムダは中身を持たない空のオブジェクトとして、コンパイル時に決まった値のように扱われ、テンプレート引数に渡せる（AtCoder の GCC 15.2 でも通る）。ただし規格では 2023 年の欠陥報告（CWG2542）でクロージャ型をテンプレート引数の型に使えないと決めたので、Clang などほかのコンパイラでは通らないことがある。確実にするなら普通の関数を `segtree<int, op, e>` と渡す」の趣旨にする。「版」の行も「GCC 13・15 で通る（規格上は CWG2542 で不可）」とする。参考に CWG2542 を足し、cpprefjp「非型テンプレートパラメータとしてクラス型を許可する」の説明（キャプチャのないラムダを渡せる理由）は外すか「クラス型の値を渡せるようになった変更」にとどめる。節の title（front matter）の「C++20」はメインの判断で「GCC」を足すか検討する（提案）

### 2｜直すべき｜事実（F3）｜#speed の 3 つ目の項目（「不動点コンビネータは、fib(40) で 16〜23 ms とかえって速かった」）

- **問題**：同じ FixPoint の fib(40) が、手元では 0.3 ms だった（fib(44) で 0.9 ms、fib(50) で 5.9 ms と、指数の底が約 1.3 で伸びる）。GCC が再帰そのものを大きく変形しており、呼び出しの速さを測れていない。16〜23 ms という値は再現しないうえ、「かえって速い」は書き方による差だと誤解させる
- **根拠**：一時置き場の bench.cpp（g++-15 `-O2`、3 回）。DFS（dfs.cpp）では FixPoint は 6.3〜7.1 ms で、auto&& self（5.4〜5.6 ms）・普通の関数（7.0〜7.3 ms）と同じ程度
- **直し方**：数値を消し、「不動点コンビネータは、fib(40) では GCC が再帰の形ごと変えてしまい（手元で 1 ms 未満）、呼び出しの速さの比較にならなかった。木の DFS では auto&& self と同じ程度だった」とする。表に列を足すなら、DFS の行だけに FixPoint の値を入れる

### 3｜直すとよい｜事実（F3）・コード（C2）｜#generic-lambda の「版」の行

- **問題**：警告の文面を「‘static’ only valid in lambda with ‘-std=c++23’」と途中で切っている。実際は「‘static’ only valid in lambda with ‘-std=c++23’ or ‘-std=gnu++23’ [-Wc++23-extensions]」で、検索に使うと少しずれる
- **根拠**：g++-13・g++-15 の `-std=gnu++20 -fsyntax-only static-cxx20-ng.cpp`
- **直し方**：「‘static’ only valid in lambda with ‘-std=c++23’ or ‘-std=gnu++23’」と全文にする

### 4｜直すとよい｜事実（F10）・手続き｜front matter の sections（speed の title）

- **問題**：執筆者が speed の節の title を書き換えた。手引き §2.1 では、front matter で直してよいのは complexity・stage・updated と節の追加だけで、既存の title の変更は提案にする決まりである
- **根拠**：上の計測で、新しい title の数（fib(40) で約 5 倍、二分木の DFS で約 1.5 倍）は再現した（fib(40)：約 5.0〜5.3 倍、二分木：約 1.5〜1.6 倍）。旧 title の「fib(35)・約 1.3 倍」は catalog（planning/catalog/cpp.yaml の 329 行）と docs/index/cpp.md の 174 行に残っている
- **直し方**：メインが変更を承認し、catalog は凍結のまま、docs/index/cpp.md は gen_site で作り直す（ページの変更は不要）。ほかのページで「約 1.3 倍」を書くものは今は見つからなかった（grep で docs と catalog を確認）

### 5｜直すとよい｜事実（F3）｜#speed のスタックの表

- **問題**：落ちる深さはプログラムの中身（局所変数・最適化）で変わるのに、表だけを見ると決まった値に読める。手元の同じ形の DFS では、auto&& self は 2.2×10^5 で落ちた（表は「2.2×10^5 で通った」）
- **根拠**：一時置き場の depth.cpp（g++-15 `-O2`、`ulimit -s 8192`）：self は 2.1×10^5 で通り 2.2×10^5 で落ちた。std::function・deducing this は表と一致
- **直し方**：表の前か後に「数は関数の中身とコンパイラで変わる目安で、比べてほしいのは書き方どうしの比（std::function は 2〜3 倍のスタックを使う）」と一言足す

### 6｜直すとよい｜図（G5・G3）｜call-path.svg・capture.svg

- **問題**：(a) call-path.svg の下の段は、ラベルに「auto&& self」と「this auto&& self」を並べたのに、箱が `self(to, v)` だけで、auto&& self の呼び方 `self(self, to, v)` と合わない。(b) 2 つの図とも viewBox の幅が 640 で、幅 358px の表示では font-size 12 の注記が約 6.7px、14 の本文が約 7.8px になり、スマホでは読みにくい（narrow.png）。(c) capture.svg の点線の矢印は線が橙なのに矢じりが黒（marker が #333 の 1 つだけ）で、線の種類で区別する説明と少し合わない
- **根拠**：一時置き場の call-path.png・capture.png・narrow.png。文字の重なり・はみ出しは見つからなかった（和文の幅は字数で見積もり、by_copy の注記は箱の幅 230 に対して約 212 で収まる）
- **直し方**：(a) 箱を「self(self, to, v) / self(to, v)」の 2 行にするか、ラベルの横に呼び方を書く。(b) 注記を font-size 16 前後に上げるか、viewBox を幅 480 前後に詰める（ほかのページの図と合わせてメインが方針を決めるとよい）。(c) 橙の矢じりの marker を別に用意する

### 7｜直すとよい｜事実（F3）・分かりやすさ（U9）｜#speed の 1 つ目の項目

- **問題**：「fib(40) は足し算だけを約 $3 \times 10^8$ 回呼ぶ」は、足し算を呼ぶように読める。呼び出しの回数は $2F_{41} - 1 = 331160281 \approx 3.3 \times 10^8$ である
- **直し方**：「fib(40) は中身が足し算だけの呼び出しを約 $3.3 \times 10^8$ 回行うので」とする

### 8｜直すとよい｜事実（F2）｜#speed の 2 つ目の項目の末尾

- **問題**：「隣接リストをランダムな順に読むメモリの待ち時間が、呼び出しの差より大きいからである」と原因を断定しているが、確かめていない（執筆者の報告にも計測はない）。現象（差がぶれに埋もれる）は手元でも再現した
- **直し方**：「…大きいためと考えられる」と弱める

### 9｜直すとよい｜事実（F10）｜要点の「計算量」と front matter の complexity

- **問題**：complexity は「呼び出しは普通の関数と同じ速さで」、要点は「呼び出しは普通の関数と同じで」と、文がわずかに違う
- **直し方**：要点を complexity と同じ文にする

## 提案（メイン向け）

- 用語集：執筆者の提案（型消去・狭義の弱順序・クロージャ）はどれも本文の使い方と合う。強い異論はない
- 手引き：執筆者の提案（§9 に `-> void` を省くとエラーになることを添える）は、void-ng で確かめたとおり正しい

## 総合の判定

**小さな直しで可**。直すべき 2 件（指摘 1：テンプレート引数のラムダの規格上の扱い、指摘 2：FixPoint の fib の数値）は、どちらも段落 1 つの書き換えで済む。コード片・エラーの文面・ほかの数値は手元で再現した。
