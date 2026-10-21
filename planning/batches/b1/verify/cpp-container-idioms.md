# cpp-container-idioms の検証（工程8b・b1）

- 対象：docs/cpp/cpp-container-idioms.md、snippets/cpp-container-idioms/ の 19 組、docs/img/cpp-container-idioms/iterators.svg
- 観点：planning/checklists/ の fact.md・code.md・clarity.md・figure.md、手引き planning/style-guide.md

## 確かめたこと

- 検査：`python3 tools/check_pages.py --page cpp-container-idioms -v`（エラー 0・警告 0）、`python3 tools/check_snippets.py snippets/cpp-container-idioms`（19 片・コンパイル 38 回・期待と違う 0。g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0 と g++-13）、`npx textlint docs/cpp/cpp-container-idioms.md`（0 errors・3 warnings。106 行の max-comma、139 行の no-unmatched-pair（半開区間）、141 行の sentence-length（代替テキスト）。どれも §13.8 で残してよい誤検出）
- front matter：`git diff` で、変わったのは complexity・stage と要点以降の本文だけ。別名の行に aliases はすべてある。リンク先のページ（stl-containers・ordered-set・hash-safety・cpp-comparators・kth-element・cpp-undefined-behavior・coordinate-compression）はすべてある。glossary#iterator は未作成だが §13.5 でよい（用語集の提案あり）
- コンパイルエラーの文面（作業用の場所 v-cpp-container-idioms で、g++-13・g++-15 の両方）：`'erase' was not declared in this scope`（gnu++17）、`has no member named 'contains'`（gnu++20 の string）、`emplace_back(<brace-enclosed initializer list>)`、`passing 'const std::map<int, int>' as 'this' argument discards qualifiers`、`no match for 'operator-'`、`use of deleted function ... _Hash = std::hash<std::pair<int, int> >`、`max(int&, ...difference_type)` の no matching function は、本文の記述と一致（unordered_map のみ注記あり→指摘 9）
- 実行で確かめた主張：
    - multiset の `erase(end())` は g++-15 で `free(): invalid pointer` の異常終了、`-D_GLIBCXX_ASSERTIONS` で `Assertion '__position != end()' failed`：本文どおり
    - pb_ds の `less_equal` の木に {3, 3, 5}：`erase(3)` 後も size 3、`find(5) == end()`、`lower_bound(3)` は 5（g++-13・g++-15）：本文どおり
    - set の `lower_bound` の速さ：要素 2×10^4・問い合わせ 2×10^4 回で、メンバ 0.8 ms、`std::lower_bound` 2.64 秒、`ranges::lower_bound` 2.69 秒（g++-15 -O2）。本文の「約 2.2 秒」は環境の差の範囲で、主張（O(N)）は成り立つ
    - unordered_map で rehash（bucket_count が変わる）の後も要素へのポインタは同じ値・同じ番地を指した。cppreference の Containers library の無効化の表（unordered の「Insertion caused rehash」の行）とも一致。執筆者の未解決の点 2 は解決
    - `hash<long long>{}(123456789012)` は 123456789012（値そのまま）
    - 容量の列 1・2・4・8・16・32（reserve.cpp の core）：本文どおり
    - `std::erase(set, x)`・`std::erase(map, k)` は g++-13・g++-15 とも `no matching function for call to 'erase(std::set<int>&, int)'`（指摘 1）
    - 消したイテレータを `++it` するループ：普通の実行（-O2）は Segmentation fault だが、AddressSanitizer では -O0・-O2、`address`・`address,undefined`、g++-13・g++-15 のどれでも何も報告されず `1 3` が出た（指摘 4）。`-D_GLIBCXX_DEBUG` では `Error: attempt to increment a singular iterator.` で止まった
    - 範囲 for の中で push_back（執筆者の rf.cpp と同じコード）：普通の実行は g++-15 -O2 で `1 2 3 10`、g++-15 -O0・g++-13 -O0/-O2 では `1 2 3 10 50`（指摘 7）。ASan ではどれも heap-use-after-free。invalidation.cpp も ASan で heap-use-after-free
    - `int i; i < it - v.begin()` は警告なしで通る（指摘 8）
- 事実の出典：cpprefjp の multiset::count の計算量は「log(size()) + count(x)」で、本文 80 行と一致（執筆者の未解決の点 4 は解決）。cpprefjp の set の erase_if の説明（`i = c.erase(i)` のループと同じ）は 68 行と一致。参考の URL 8＋1＋1 件は curl ですべて 200（`https://en.cppreference.com/cpp/container` も 200 で開ける）。どれも付録 B のドメイン。本文は出典の文・例をなぞっていない
- AtCoder の GCC で pb_ds が使えること（未解決の点 3）：atcoder.jp を開けないので直接は確かめていない。GCC（libstdc++）なら `ext/pb_ds` が付くという判断は妥当。ただし 49 行の書き方は直す（指摘 3）
- 図 iterators.svg：Windows の Chrome（headless=new、2 倍密度）で、等倍（640×400）と、幅 390px の暗い背景の画面に幅 358px で画像にして目で見た（作業用の場所 v-cpp-container-idioms/full.png・narrow.png）。背景は白、`viewBox` あり、文字はテキスト・`font-family="sans-serif"`。値（10・20・30・40、begin は 10、prev(end())・rbegin は 40、添字 0〜3 と 4 = size()、erase 後に戻り値が 30）は本文・代替テキスト・iterators.cpp と一致。文字どうしの重なりはない。矢じりの形（指摘 5）と右端（指摘 10）に直す点がある
- 執筆者の未解決の点：(1) 図は上のとおり確かめた。(2)(4) 解決。(3) 上のとおり

## 指摘

### 1｜直すべき｜fact（F2）｜#erase-if の見出し・本文 53 行・sections の title（18 行）

- **問題**：「`erase(v, x)`・`erase_if(v, pred)`：…set・map にも使える」「どちらも消した個数を返す。vector・deque・string のほか、set・multiset・map にも使える」とあるが、値で消す `std::erase(c, x)` は vector・deque・string・list・forward_list だけにあり、set・multiset・map・unordered 系には `erase_if` しかない（連想コンテナはメンバの `erase(key)` で同じことができるため）。`erase(st, 3)` はコンパイルエラーになる
- **根拠**：`set<int> st; erase(st, 2);` と `map<int,int> mp; erase(mp, 1);` が g++-13・g++-15（gnu++23）とも `no matching function for call to 'erase(std::set<int>&, int)'`。cpprefjp の set の項に自由関数は erase_if だけ
- **直し方**：「`erase(v, x)` は vector・deque・string・list で使う。`erase_if(v, pred)` はそれらに加えて set・multiset・map・unordered_map にも使える。set・map で値を消すならメンバの `st.erase(x)`」とする。見出しと sections の title は「erase(v, x)・erase_if(v, pred)：消した個数を返す。erase_if は set・map にも使える（C++20）」のようにする（§13.2 で title も合わせる）

### 2｜直すべき｜fact（F3）｜#iterators の 149 行

- **問題**：「入力 25 なら、30 以上の最小が 30」は打ち間違い。`lower_bound(25)` なので「25 以上の最小が 30」である（iterators.yaml の cases も `ge 30`）
- **根拠**：iterators.cpp の cases（入力 25 → `ge 30`・`lt 20`・`next 40`）
- **直し方**：「入力 25 なら、25 以上の最小が 30、25 未満の最大が 20、その次が 40 と出る」

### 3｜直すべき｜fact（F2・C6）｜導入の 49 行

- **問題**：「書き方はすべて AtCoder の GCC 15.2（`-std=gnu++23`）と手元の g++-13・g++-15 で確かめた」とあるが、AtCoder では提出して確かめていない（執筆者の未解決の点 3。atcoder.jp を開かない規則のため）。確かめていないことを確かめたと書いている
- **根拠**：planning/batches/b1/cpp-container-idioms.md の未解決の点 3。ほかの C++ のページ（cpp-io 51 行・cpp-views-basics 46 行）は「手元で測った／AtCoder の GCC 15.2 では使える」と書き分けている
- **直し方**：「書き方はすべて手元の g++-13・g++-15（`-std=gnu++23`）で確かめた。AtCoder の GCC 15.2（`-std=gnu++23`）でも使える」とする

### 4｜直すべき｜fact（F2）・code（C8）｜#erase-returns-next の落とし穴（179 行）

- **問題**：「AddressSanitizer（`-fsanitize=address`）を付けると `heap-use-after-free` で止まる」は再現しない。set の `++it` は共有ライブラリの libstdc++ にある `_Rb_tree_increment` の中で解放済みの節を読むので、計測されず、ASan は何も報告しないまま `1 3` を出す。読者が ASan で試して「問題ない」と誤解する
- **根拠**：本文と同じコード（執筆者の el.cpp と同じ）を g++-13・g++-15 × -O0・-O2 × `-fsanitize=address`・`address,undefined` の 8 通りで実行し、すべて報告なしで `1 3`。`-D_GLIBCXX_DEBUG` では `Error: attempt to increment a singular iterator.` で止まる
- **直し方**：「AddressSanitizer では見つからないことがある（set の `++` は計測されないライブラリの中で動くため）。`-D_GLIBCXX_DEBUG` を付けると `attempt to increment a singular iterator` で止まる」とする

### 5｜直すべき｜figure（G5）｜iterators.svg の矢じり（marker `arr`）

- **問題**：矢じりの path（`M0,0 L10,0 L5,10`、下向きの三角）に `orient="auto-start-reverse"` を付けているので、線の向き（下向き）に合わせて 90 度回され、すべての矢じりが線の右に寄った横向きの直角三角形に描かれる。begin()・prev(end())・end()・it・戻り値の it の 5 本とも、要素を下向きに指す矢印に見えない
- **根拠**：full.png・narrow.png で目視。`orient="auto"` は marker の +x 方向を線の向きに合わせる
- **直し方**：marker を `viewBox="0 0 10 10" refX="10" refY="5"` と path `M0,0 L10,5 L0,10 z`（+x 向きの三角）にする。線の終点は今の y のままでよい

### 6｜直すべき｜fact（F1）・clarity（U1）｜要点の計算量（40 行）と front matter の complexity（14 行）

- **問題**：「`erase`・`erase_if` は全体を 1 回見るので $O(N)$」の `erase` が、このページで多く使うメンバの `erase`（set の `st.erase(x)` は $O(\log N + \text{個数})$、`erase(it)` はならし $O(1)$）とも読める。辞書として要点だけを見た読者が「set の erase は O(N)」と取り違える
- **根拠**：cpprefjp の multiset::erase・set::erase の計算量。本文 68 行自身が「メンバの `v.erase(x)` と自由関数の `erase(v, x)` は別物」と注意している
- **直し方**：要点を「自由関数の `erase(v, x)`・`erase_if` は全体を 1 回見るので $O(N)$（set・map のメンバの `erase` は $O(\log N)$）」とし、complexity も「自由関数の erase・erase_if は O(N)」と合わせる

### 7｜直すとよい｜fact（F3）｜#invalidation の起きやすい形 1（192 行）

- **問題**：「普通の実行では `1 2 3 10` と 30 を落として終わり」は、手元でも g++-15 -O2 だけの結果で、g++-15 -O0・g++-13 では `1 2 3 10 50` と壊れた値が出た。未定義動作なので結果は環境しだいだが、「落とす」と 1 通りに書くと読者は再現しない
- **根拠**：rf.cpp を g++-13・g++-15 × -O0・-O2 で実行（上の「確かめたこと」）
- **直し方**：「手元の g++-15（-O2）では `1 2 3 10` と 30 を落とし、g++-13 では `1 2 3 10 50` と元にない値が出た。どちらも正しい `1 2 3 10 30` ではない」とする

### 8｜直すとよい｜fact（F2）｜#iterator-index の「型」（167 行）

- **問題**：「`max(i, it - v.begin())` のように `int` と直接比べると型が合わずコンパイルエラーになる」の「比べると」は不正確。`i < it - v.begin()` は警告もなく通る。エラーになるのは `max`・`min` のテンプレートの型推論が `int` と `long` で食い違うとき
- **根拠**：`bool b = i < it - v.begin();` を `-Wall -Wextra` で警告なし。`max(i, it - v.begin())` は `no matching function for call to 'max(int&, ...difference_type)'`
- **直し方**：「`max(i, it - v.begin())` のように `int` と一緒に `max`・`min` に渡すと、型が合わずコンパイルエラーになる。`int` に入れてから渡す」

### 9｜直すとよい｜fact（F3）｜#unordered-map の 212 行

- **問題**：「g++-13・g++-15 とも `use of deleted function` でコンパイルエラーになる」とあるが、g++-15 では最初のエラーが `static assertion failed: hash function must be copy constructible` で、`use of deleted function` はその後に出る。読者が最初の行だけを見ると、本文の文面と一致しない
- **根拠**：unordered-pair-ng.cpp を g++-15 でコンパイルしたエラーの順
- **直し方**：「g++-15 では最初に `hash function must be copy constructible` が出て、続いて `use of deleted function` が出る」と添える。手がかりの `_Hash = std::hash<std::pair<int, int> >` はそのままでよい

### 10｜直すとよい｜figure（G3）｜iterators.svg の右端と小さな文字

- **問題**：右下の「イテレータはそのまま使える」（x = 470、13px）が幅 640 の右端に接している（full.png で端が切れかけ）。幅 358px に縮めると 13px の文字（添字・「rbegin() も同じ要素」・「要素なし」）が約 7px になり読みにくい
- **根拠**：full.png・narrow.png の目視
- **直し方**：右下の 2 行を x = 462 に寄せるか、「ほかのイテレータは」「そのまま使える」のように短くする。13px の文字を 14〜15px にする

### 11｜直すとよい｜clarity（U2）｜#invalidation の 190 行

- **問題**：「libstdc++ では容量が足りなくなるたびに倍増するので、再確保は前触れなく起きる」の「ので」が通らない。倍増することは「前触れなく」の理由ではない（前触れがないのは、`push_back` の側から再確保が見えないため）
- **根拠**：文の論理
- **直し方**：「libstdc++ では容量が足りなくなるたびに倍増する。再確保は `push_back` の見た目からは分からず、前触れなく起きる」と 2 文に分ける

### 12｜直すとよい｜code（C2）｜snippets/cpp-container-idioms/invalidation.yaml・reserve.cpp

- **問題**：invalidation.yaml は `expect: run` で cases がなく、未定義動作のコードを検査で走らせるだけで何も確かめていない。reserve.cpp は `reserve` を使っておらず、名前と中身が合わない（core の容量の列は本文 190 行の根拠だが取り込まれていない）
- **根拠**：yaml と cpp の中身
- **直し方**：invalidation は §13.9 の失敗例として、コンパイルが通ることだけを見る期待（道具にあれば）にするか、そのままにして yaml に「未定義動作の例。出力は確かめない」と注記する。reserve.cpp は capacity.cpp などに改名するか、`v.reserve` の例を足す

## 提案（メイン向け）

- 用語集の「イテレータの無効化」を足すなら、定義に「unordered 系の rehash はイテレータだけを無効にし、参照は保つ」を含めると本文 205 行と合う

## 総合の判定

小さな直しで可（直すべき 6 件・直すとよい 6 件）。どれも文の差し替えか SVG の marker の 1 か所で直る
