# cpp-lambda の報告（工程8b・バッチ b1）

- 書いたファイル：docs/cpp/cpp-lambda.md、snippets/cpp-lambda/（22 片：capture・dangling・generic・static-cxx20-ng・iife・pass・decltype-type・decltype-cxx17・decltype-cxx17-ng・decltype-capture・decltype-capture-ng・segtree・segtree-capture-ng・recursive-ng・std-function・self-arg・deducing-this・deducing-this-13-ng・fixpoint・return-type・return-type-ng・void-ng の各 .cpp/.yaml）、docs/img/cpp-lambda/capture.svg・call-path.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21 のまま）。sections の speed の title を「std::function は fib(35) で約 5 倍、木の DFS で約 1.3 倍」から「fib(40) で約 5 倍、木の DFS で約 1.5 倍」に直した（手元で測り直した値。下の未解決の点）。cpp_std・gcc_min は版の混ざるページなので null のまま、atcoder は true のまま
- 検査の結果：check_pages（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、check_snippets（22 片・コンパイル 42 回・期待と違う 0）、textlint（エラー 0・警告 0）
- 図：catalog の visual（static・priority 2）の 2 つの図を SVG にした（キャプチャの図 capture.svg、呼び出しの経路の図 call-path.svg）。手元に SVG の描画の道具がなく、座標の計算で配置を決めただけなので、検証で見た目（文字の重なり・はみ出し）を確かめてほしい。動く図は作っていない
- 問題：catalog・台帳とも problems なし（problems_note のとおり確認問題で確かめる）。確認問題を 4 つ置いた

## 使った出典

- cpprefjp（ラムダ式・ジェネリックラムダ・初期化キャプチャ・テンプレート構文・状態を持たないラムダの既定構築・非型テンプレートパラメータのクラス型・static operator()・deducing this）：各節の仕様の確認
- cppreference「std::function」：型消去の入れ物であること
- gcc.gnu.org の cxx-status：P0847（deducing this）が GCC 14、P1169（static operator()）が GCC 13
- github.com の ac-library document_ja/segtree.md と third_party/ac-library/atcoder/segtree.hpp：`template <class S, auto op, auto e>` の宣言
- 新しく noai を確かめたドメイン：なし（すべて付録 B のドメイン）
- 手元の実験（スクラッチ）：速さの計測（fib(40)・完全二分木とランダムな木の DFS）とスタック 8 MiB での落ちる深さ。プログラムは一時置き場の bench.cpp・depth.cpp で、snippets には入れていない

## 台帳への提案

- なし（このページは問題を置かない）

## 用語集への提案

- 型消去｜type-erasure｜中身の具体的な型を隠し、同じ形で呼べるものを 1 つの型で扱う仕組み。`std::function` が代表で、呼び出しは関数ポインタなどを経る間接呼び出しになる。（本文で `../guide/glossary.md#type-erasure` にリンクした）
- 狭義の弱順序｜strict-weak-ordering｜`sort`・`set` の比較関数が満たすべき条件。`comp(a, a)` は偽、`comp(a, b)` が真なら `comp(b, a)` は偽、推移的、などを満たす。`<=` は満たさない。（本文でリンクした。ほかのページでも同じ anchor が使われている）
- クロージャ｜closure｜ラムダ式を評価して作られるオブジェクト。取り込んだ変数を持ち、関数のように呼べる。（本文では導入の段落で定義し、リンクはしていない）

## 手引きへの提案

- §9 の DFS の形 `auto dfs = [&](auto&& self, int v, int p) -> void { … };` について、`-> void` を省くとコンパイルエラーになる（再帰より前に型の決まる return がないため）ことを一言添えると、執筆者がコード片で外さない
- 速さの数値を本文に書く C++ のページは、計測の条件（コンパイラ・最適化・回数・範囲）を表の前に書く決まりにすると、ページ間でそろう

## 問題の補充の候補

- なし（C++ のページは ABC の問題を置かない方針。比較関数・判定関数・再帰ラムダの使用例は、それぞれ cpp-comparators・binary-search-answer・dfs のページの例題で足りる）

## 未解決の点

- catalog の speed の節と research §4.16・§4.38 の数値（fib(35) で約 5 倍、木の DFS で約 1.3 倍）は、手元で再現しなかった。fib(35) は 10〜30 ms と短く測定のぶれが大きく（約 2 倍）、fib(40) で約 5 倍（108〜163 ms 対 528〜639 ms）だった。木の DFS は、完全二分木（頂点数 2×10^6）で約 1.5 倍（9〜11 ms 対 5〜8 ms）、親をランダムに選んだ木では 200〜1400 ms とぶれが大きく差が見えなかった。本文は手元で測り直した値にし、節の title も直した。cpp-reverse-index・cpp-io（tle-causes）・早見表に「約 5 倍・約 1.3 倍」を書くページがあれば、合わせて直す必要がある
- 不動点コンビネータ（FixPoint）は fib(40) で 16〜23 ms と、普通の関数より速かった。GCC の最適化のかかり方によるものと考えて本文ではそう書いたが、原因は確かめていない
- スタック 8 MiB での落ちる深さ（std::function は 8×10^4 で通り 9×10^4 で落ちる、auto&& self は 2.2×10^5 で通り 2.4×10^5 で落ちる）は g++-15 -O2 の 1 つのプログラムでの値。cpp-environment#stack-depth の research の値（素朴な再帰で 10^5 は通り 2×10^5 で落ちる）とは、1 段の大きさが違うので一致しない
- AtCoder の新ジャッジのスタックの上限は未確認（research §4.4 のとおり）。本文は「大きいとされ、通ることが多い」とぼかした
- 動く図はない（visual は priority 2 の static）

## 検証の指摘への対応（2026-10-21）

- 指摘 1（直すべき）：#template-argument の 2 段落目を、GCC が受け入れる扱いであり規格上は CWG2542 で不可、確実にするなら普通の関数を渡す、の趣旨に書き換えた。「版」の行も直し、参考に CWG2542 を足し、cpprefjp「非型テンプレートパラメータとしてクラス型を許可する」の説明は「C++20 の変更」にとどめた
- 指摘 2（直すべき）：FixPoint の fib(40) の数値を消し、GCC が再帰の形ごと変えて比較にならないこと、木の DFS では auto&& self と同じ程度であることに書き換えた
- 指摘 3・5・7・8・9：指摘どおり直した（警告の全文、スタックの表の後に目安である旨、呼び出し回数 約 3.3×10^8、原因を「と考えられる」に、要点の文を complexity とそろえた）
- 指摘 6：(a) call-path.svg の下の段の箱を「self(self, to, v) / self(to, v)」の 2 行にした。(c) capture.svg の点線の矢印に橙の矢じりを用意した。(b)（スマホ幅での文字の小ささ）は採らなかった：ほかのページの図とそろえる方針の判断が要るため、下の提案に回した
- 指摘 4：ページの変更は不要（メインの判断事項。下の提案）

## 検証後の提案（メイン向け）

- front matter の template-argument の節の title「テンプレート引数に渡せるのはキャプチャのないラムダだけ（C++20。ACL の segtree）」は、規格上は CWG2542 で不可なので、「（GCC で通る。ACL の segtree）」などに変えることを提案する（title の変更は手引き §2.1 によりメインの判断。本文の見出しは front matter と合わせて変える必要がある）
- speed の節の title の変更（fib(40) で約 5 倍、木の DFS で約 1.5 倍）の承認と、docs/index/cpp.md の gen_site での作り直し（検証の指摘 4）
- 図の viewBox の幅 640 では、幅 358px の表示で 12px の注記が約 6.7px になる。図の幅・文字の大きさの方針をほかのページとそろえて決めてほしい（検証の指摘 6 (b)）
