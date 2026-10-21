# cpp-comparators の報告と提案（工程8b・b1）

- 書いたファイル：docs/cpp/cpp-comparators.md、snippets/cpp-comparators/ の 16 組（strict-weak・less-equal・less-equal-crash・greater・pq-order・set-equivalence・multiple-keys・lambda-type・lambda-type-17・lambda-type-17-ng・lambda-capture-ng・operator-less・operator-less-ng・operator-less-sort-only・spaceship・spaceship-17-ng。どれも .cpp と .yaml）。docs/img/cpp-comparators/ は作っていない
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21 のまま）。sections は strict-weak-ordering の title の「厳密弱順序」を「狭義の弱順序」に変えた（下の「未解決の点」）。anchor は変えていない。cpp_std・gcc_min は null のまま（版が C++98〜C++20 で混ざるため。catalog の注記どおり）、atcoder は true のまま
- 検査の結果：check_pages（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、check_snippets（16 件・32 回のコンパイルすべて期待どおり）、textlint（エラー 0・警告 1）
  - 残した警告：245 行の sentence-length（確認問題の題に `sort(...)` のコードを書いたため）
- 図：catalog の visual（static・priority 2「比較関数と取り出される順の対応表」）は、priority-queue-order の節に Markdown の表（渡す先 × true の意味 × less・greater で先に出るもの）として書いた。SVG は作っていない。動く図はない
- 問題：catalog どおり置いていない（C++ のページは問題を置かず確認問題で確かめる）
- 手元で確かめた事実（g++-13・g++-15、-std=gnu++23）：
  - `<=` の比較関数で同じ値だけの配列を sort：-O2 で 1〜3×10^4 個は正常終了、10^5 個で Segmentation fault。-fsanitize=address は 17 個以上で heap-buffer-overflow、16 個以下は検出なし。-D_GLIBCXX_DEBUG は 1 個でも `comparison doesn't meet irreflexive requirements` で abort
  - `<=` の比較関数の set に 1 を 3 回 insert すると size 3・find は end・count 0
  - `long long` の配列に `greater<int>()` で sort すると 3000000000 が最後に並ぶ（-Wall -Wextra で警告なし）
  - const のない `operator<`：std::sort は通り、set・priority_queue・ranges::sort はコンパイルエラー
  - `set<int, decltype(cmp)> st;`（キャプチャなし）は gnu++17 でエラー・gnu++20 で通る。キャプチャありは gnu++20 でもエラー。`decltype([](...){...})` を直接書くのは gnu++20 から
  - `= default` の `<=>` は gnu++20 から通り、gnu++17 ではエラー
- 使った出典：cpprefjp（algorithm・greater・priority_queue・set・C++20 の状態を持たないラムダ・<=>）、cppreference（Compare）、gcc.gnu.org（Debug Mode Semantics）。題名は各ページの title 要素で確かめた。新しいドメインはない（どれも付録 B）

## 台帳への提案

なし（問題を使っていない）。

## catalog・front matter への提案

- summary の「約束（厳密弱順序）」を「約束（狭義の弱順序）」にする。sorting-techniques（draft）と用語集の anchor strict-weak-ordering が「狭義の弱順序」を使い、cpprefjp もこの訳である。本文の要点の囲みはすでに「狭義の弱順序」にした（summary と食い違うのは語だけで、意味は同じ）。aliases の「厳密弱順序」はそのまま残す
- related に minimum-spanning-tree を足してもよい（spaceship の節で、`<=>` を付けた辺の構造体をクラスカル法の並べ方の例にしてリンクした）

## 用語集への提案

- 狭義の弱順序｜strict-weak-ordering｜比較関数が満たすべき条件。自分自身と比べたら false、前後関係が推移する、どちらが前とも言えない 2 つ（同等）の関係も推移する、の 3 つ。sort・set・priority_queue は比較関数がこれを満たすことを前提にする（sorting-techniques がすでに同じ anchor でリンクしている。用語集にまだなければ足す）
- 三方比較演算子｜three-way-comparison｜C++20 の演算子 `<=>`。2 つの値の大小と等しさを 1 回で返す。`= default` で書くと、`<`・`==` など 6 つの比較をメンバの宣言順の辞書順で作れる（本文ではリンクしていない。research/09 §6.5 の用語集の候補にある）

## prh.yml への提案

- 「厳密弱順序」→「狭義の弱順序」（別名の行は textlint の外なので影響しない）

## 手引きへの提案

- check_snippets の expect に「実行時に異常終了する」がないため、`<=` の比較関数で落ちる実例はコード片の期待で確かめられない。今回は落ちない大きさ（3 個）で run にした less-equal-crash と、本文の表（手元で測った結果）で代えた。実行時エラーの実例を扱う cpp のページ（未定義動作など）では、この扱いでよいかを決めてほしい

## 問題の補充の候補

なし（C++ のページは問題を置かない方針のため探していない）。

## 未解決の点

- 節の題名の用語：catalog の title は「厳密弱順序」だったが、§13.2 で執筆者が title を直してよいとあるので、sorting-techniques・用語集の anchor にそろえて「狭義の弱順序」にした。メインで統一の方針を決めてほしい（summary も上の提案のとおり）
- 表の「17〜3×10^4 は正常に終わる」は 17・100・1000・2000・5000・10^4・3×10^4 で試した結果で、未定義動作なので環境によって変わりうる。本文では「手元で」「試した」と書いた
- cpp-undefined-behavior の debug-build 節と cpp-container-idioms の multiset-erase-one 節は stub なので、節ではなくページへリンクした。draft になったら #debug-build・#multiset-erase-one へのリンクに直せる
- 使用量の目安：道具の呼び出し約 35 回、Web 取得は URL の存在と題名の確認（curl）のみ約 3 回
