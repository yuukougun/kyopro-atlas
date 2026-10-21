# cpp-views-cpp23 の検証（工程8b・b1）

- 対象：docs/cpp/cpp-views-cpp23.md、snippets/cpp-views-cpp23/（22 片の .cpp・.yaml）、docs/img/cpp-views-cpp23/views-gallery.svg
- 観点：planning/checklists/ の fact.md・code.md・clarity.md・figure.md、手引き planning/style-guide.md

## 確かめたこと

- 検査：`python3 tools/check_pages.py --page cpp-views-cpp23`（エラー 0・警告 0）、`python3 tools/fix_problems.py --page cpp-views-cpp23 --check`（直すべき行 0）、`python3 tools/check_snippets.py snippets/cpp-views-cpp23`（22 片・コンパイル 40 回・期待と違う 0）、`npx textlint docs/cpp/cpp-views-cpp23.md`（0 errors・9 warnings。半開区間の `[`・エラー文を含む文・参考の行の長さで、誤検出として残してよい）。コンパイラは g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0 と g++-13 (Ubuntu 13.4.0-6ubuntu1~22~ppa2) 13.4.0
- サニタイザ：run の 13 片を g++-15 `-std=gnu++23 -O1 -fsanitize=address,undefined` で cases どおり動かし、出力一致・報告なし
- front matter：`git diff` で変わったのは complexity・stage と要点以降だけ。complexity・要点の計算量・本文（121 行の $O(Nk)$）が一致する。別名の行に aliases がすべてある
- 本文の数値を手で数え直した：差分 `-2 3 -3 4 4 -7 4`、山 2 個、塊の和 `8 15 8`、窓の和 `8 6 10 15 16 17`、3 個おき `3 1 2`、積の和 7、並べた添字 `1 3 0 2`、slide(3) 6 個・chunk(3) 3 個、$N = 2 \times 10^5$・$k = 10^5$ で約 $10^{10}$。すべて正しい
- 要素の型（作業用 t1.cpp）：`range_reference_t` を両方のコンパイラで出した。g++-13 は zip(2 個)・pairwise・cartesian_product(2 個) が `pair<int&, int&>`、g++-15 は `tuple<int&, int&>`。3 個の zip はどちらも tuple、enumerate はどちらも `tuple<long, int&>`。88 行の記述は正しい（執筆者の未解決の点 3 は事実として確認。P2165 という理由は本文に書いていないので問題ない）
- エラーの文面：190 行（`cannot bind non-const lvalue reference …`）・209 行（`no matching function for call to 'max(int&, …)'`）・230 行（`'to' is not a member of 'std::ranges'`）・245 行（`'from_range' was not declared`）・271 行（`'concat' is not a member of 'std::views'`）を両方のコンパイラで出し、本文と一致。g++-15 `-std=gnu++26` で concat-ng は通る（278 行のとおり）
- GCC の変更点（gcc.gnu.org）：GCC 13 の一覧に zip・zip_transform・adjacent・adjacent_transform・pairwise・slide・chunk・chunk_by・repeat・cartesian_product・as_rvalue・enumerate・as_const があり、stride・join_with・ranges::to はない。GCC 14 に `std::ranges::to`。GCC 15 に「`from_range_t` constructors added to all containers, as well as new member functions such as `insert_range`」と C++26 の `views::concat`。本文の 171・245・296〜298 行と一致（未解決の点 1・2：ranges::to が 14 からは一覧で確認。stride・join_with は一覧になく、手元の g++-13 で通ることはコード片で確認）
- cppreference の ranges::to：入れ子は `range_value_t<C>` への再帰で変換、`to<vector>()` は `range_value_t<R>` から推論。221 行と一致
- 寿命（73 行）：右辺値を流すと owning_view に移される。cpp-views-basics#lifetime の記述と一致
- cartesian_product の速さ（154 行）：作業用 b.cpp・b2.cpp で再現。$n = 2 \times 10^4$、`-O2`。普通の二重 for は g++-13 44 ms・g++-15 49 ms。`cartesian_product(iota(0, n), iota(0, n))` で添字を回すと g++-13 162 ms・g++-15 610 ms で本文と一致。ただし配列そのもの `cartesian_product(a, a)` だと g++-13 98 ms・g++-15 260 ms で、本文の「配列の全組」という書き方とは測り方がずれる（指摘 4）
- 参考の URL：cppreference の 3 件・cpprefjp・gcc.gnu.org の 3 件とも 200 で開け、内容が書かれたとおり。どれも付録 B のドメイン。本文の文・例は資料と別で、近すぎる箇所はない
- リンク先の anchor：cpp-views-basics の #lifetime・#split-join・#iota-int・#common、cpp-range-for#range-for-forms、run-length-encoding#split、glossary#sentinel はすべてある
- 図 views-gallery.svg：Linux の chrome-headless-shell 146 で、幅 1000 の画面に等倍で画像にした（作業用 v-cpp-views-cpp23/fig.png）。この環境は日本語のフォントがなく和文が豆腐になったので、和文のラベルは SVG の text を取り出して読んだ。値（chunk(3)＝314・159・26、chunk_by(less_equal)＝3・14・159・26、stride(3)＝3 1 2、slide(3) 6 個、pairwise 7 個）は本文・代替テキスト・chunk-by-inc の答え 3 と一致。背景は白、`viewBox` あり、文字はテキスト・`font-family="sans-serif"`、色に加えて実線と破線で隣の塊を区別。catalog の visual（static・priority 2、chunk・slide・chunk_by・stride・adjacent の図鑑）を満たす。はみ出し・重なりはない
- 執筆者の未解決の点 5（cpp-structured-bindings#enumerate-reference との重なり）：あちらは draft で同じ内容を短く書いている。このページの指摘にはしない（メインの判断）

## 指摘

### 1｜直すべき｜fact（F2）・code（C3）｜#int-index の「ほかの直し方」（215 行）

- **問題**：「`best` を `long long` にする」と通る、と書いているが通らない。`ptrdiff_t` は 64 bit の Linux では `long` で、`long long` とは別の型なので、`max(long long&, long&)` はやはりテンプレートの推論が食い違ってコンパイルエラーになる
- **根拠**：作業用 m.cpp で `long long best = 0; … best = max(best, i);` を g++-13・g++-15 でコンパイルし、両方とも `no matching function for call to 'max(long long int&, std::tuple_element<0, std::tuple<long int, int&> >::type&)'`。`max<long long>(best, i)`・`max(best, (int)i)`・`ptrdiff_t best` は通り、答え 2
- **直し方**：「`best` を `long long` にする」を「`best` を `ptrdiff_t` にする」に替える。あわせて「`long long` にしても通らない（`ptrdiff_t` は `long` で、`long long` とは別の型）」と落とし穴として 1 文足すと、読者がはまりやすい点を先回りできる

### 2｜直すべき｜fact（F2）｜#repeat-join-with の落とし穴（172 行）

- **問題**：「`join_with` は一度 `to_string` で文字列にするので」は誤り。`join_with` は文字列に変換しない。`to_string` をしているのは例のコードの `views::transform` で、遅くなりうる理由は「この書き方は数ごとに `to_string` で `string` を作り、1 文字ずつ出力する」ことである
- **根拠**：repeat-join-with.cpp の core（`a | views::transform([](int x) { return to_string(x); })` を `join_with(' ')` に流している）。cppreference の join_with_view は範囲の範囲をつなぐだけ
- **直し方**：「上の書き方は数ごとに `to_string` で文字列を作って 1 文字ずつ出すので、$10^6$ 個の数を出すような場面では遅くなりうる」とする

### 3｜直すとよい｜clarity（U2）｜#adjacent の「素朴に書くと」（101 行）

- **問題**：「`i + 1 < n` の境界を書かずに済むので、長さ 0・1 のときの範囲外アクセスが起きない」は、`i + 1 < n`（`int n`）と書けば素朴な書き方でも範囲外にならないので、何と比べて安全なのかが読者に分からない。実際に起きるのは `i < a.size() - 1` の符号なしの引き算（長さ 0 で巨大な値になる）である
- **根拠**：`int n = 0` で `for (int i = 0; i + 1 < n; i++)` は 1 回も回らない。危ないのは `a.size() - 1`（code.md C8 の例）
- **直し方**：「境界を書かずに済む。`i < a.size() - 1` と書くと長さ 0 のとき符号なしの引き算で巨大な値になるが、`pairwise` なら組が 0 個になるだけである」とし、[整数のあふれ](../cpp/cpp-integer-overflow.md) へのリンクを添える

### 4｜直すとよい｜fact（F3）｜#cartesian-product の速さ（154 行）

- **問題**：「長さ $2 \times 10^4$ の配列の全組」で測ったと書くが、本文の数値（g++-13 約 160 ms、g++-15 約 610 ms）は `cartesian_product(iota(0, n), iota(0, n))` で添字を回して配列を引いたときの値で、配列そのものを `cartesian_product(a, a)` に渡すと g++-13 約 100 ms・g++-15 約 260 ms だった。読者が自分で試すと数値が合わない
- **根拠**：作業用 b.cpp（`cartesian_product(a, a)`）と b2.cpp（iota の組）、`-O2`、各 2 回
- **直し方**：「`views::cartesian_product(views::iota(0, n), views::iota(0, n))` で添字の全組（$4 \times 10^8$ 組）を回し、`a[i] ^ a[j]` の和を求めた」と測り方を書く。結論（重いループは普通の for）はそのままでよい

### 5｜直すとよい｜figure（G3）｜views-gallery.svg の右側の注記

- **問題**：右寄せの注記（「3 個ずつ。最後は 2 個」など）は font-size 13 で、幅 560 の図をスマホ（幅 390px、本文の幅 358px）に縮めると約 8px になり、読みにくい
- **根拠**：SVG の viewBox 0 0 560 474、注記 `font-size="13"`。358 / 560 × 13 ≈ 8.3
- **直し方**：注記を 14〜15 にするか、各段の見出しの下の行へ移して図の横幅を詰める。注記の内容は本文 53 行と代替テキストにもあるので、このままでも意味は通る

### 6｜直すとよい｜fact（F9）｜#chunk-slide-stride・#repeat-join-with の版（120 行・171 行）

- **問題**：`stride` も GCC 13 の変更点の一覧に載っていないが、120 行は「g++-13・g++-15 で使える」とだけ書き、171 行の `join_with` のような注記がない。版の根拠が手元の 13.4 だけで、13.1 から使えるかは資料で裏付けていない
- **根拠**：gcc.gnu.org/gcc-13/changes.html の `<ranges>` の一覧に stride・join_with はない（執筆者の未解決の点 2）
- **直し方**：cppreference の「C++23 compiler support」（en.cppreference.com/cpp/compiler_support/23）で `views::stride`（P1899）・`views::join_with`（P2441）の libstdc++ の版を確かめて参考に足すか、120 行にも「一覧にはないが手元の g++-13 で使えた」と添える

## 総合の判定

小さな直しで可。直すべき指摘は 2 件（指摘 1：`best` を `long long` にしても通らない、指摘 2：`join_with` が `to_string` するという誤り）で、どちらも 1 文の差し替えで直る。コード片 22 片はすべて期待どおりで、本文の数値・エラーの文面・版の記述（GCC 13・14・15 の変更点）は確かめた範囲で正しい。
