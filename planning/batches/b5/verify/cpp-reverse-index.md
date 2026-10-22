# cpp-reverse-index の検証（b5）

- 対象：docs/cpp/cpp-reverse-index.md、snippets/cpp-reverse-index/（read-line・read-line-ng・required-from-here-ng）、docs/img/cpp-reverse-index/read-line.svg
- 観点：fact.md・code.md・clarity.md・figure.md
- 検証日：2026-10-22。g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0、g++-13 (Ubuntu 13.4.0-6ubuntu1~22~ppa2) 13.4.0

## 確かめたこと（指摘なし）

- `python3 tools/check_pages.py --page cpp-reverse-index`：エラー 0・警告 0
- `python3 tools/check_snippets.py -v snippets/cpp-reverse-index`：3 個・6 回のコンパイル、期待と違う 0（g++-13・g++-15）。read-line.cpp を `-fsanitize=address,undefined` 付きで 2 つの cases に通し、出力一致・エラーなし。cases の 1 つ目（4 頂点）の SCC {3}・{0,1}・{2} の並びはトポロジカル順として正しい
- textlint：エラー 0・警告 2（執筆者の報告どおり。62 行の代替テキストの長さと、要点 1 行目の「か」の重複）
- リンク：本文の 248 個の `../` リンクの行き先のファイルと anchor がすべて存在する（スクリプトで照合）。ページ内リンク（#lookup-types・#symptoms・#compile-errors・#how-to-read）も存在する
- 表の中のバッククォート内の `|`（`dp |= dp << w`・`v | views::reverse` など）：.venv の python-markdown（tables・attr_list・superfences・arithmatex）で描画し、すべての行が 3 セルになることを確かめた
- コンパイルエラーの表：各行のメッセージの断片が、リンク先の節の本文（または見出し）に書かれていることをスクリプトで照合した（use of 'f' before deduction は cpp-lambda#recursive-lambda の見出しにある）。加えて次を手元で出して文面を確かめた：`'println' was not declared`・`'to' is not a member of 'std::ranges'`・`expected identifier before 'this'`（g++-13）、`'concat' is not a member of 'std::views'`（g++-15 の gnu++23）、iota の `no match for call to '(const std::ranges::views::_Iota) (int, std::vector<int>::size_type)'`（両方）、`borrowed_iterator_t`、`conversion from 'int' to non-scalar type 'atcoder::dsu'`、`the value of 'n' is not usable`、designator order、`expected primary-expression before 'long'`、`ambiguous overload for 'operator<<'`、const map の discards qualifiers、`popcount(int&)`、`reference to 'count' is ambiguous`
- required from here の例：g++-15 で 132 行・g++-13 で 79 行（`-std=gnu++23 -O2 -Wall -Wextra`）を再現。`required-from-here-ng.cpp:14:9:   required from here` の後に `predefined_ops.h:45:23: error: no match for 'operator<' (operand types are 'P' and 'P')` が来る並びと、`error:` が 3 つですべて同じ原因であることも本文どおり
- read-line-ng（`auto&`）のエラーは `cannot bind non-const lvalue reference of type 'std::tuple<long int, std::vector<int>&>&' to an rvalue`（両方の版）で、本文 69 行・確認問題 1・表 365 行の説明と一致
- 1 行の読み方の主張：`decltype(i)` が `const ptrdiff_t`、`decltype(component)` が `vector<int>&`（コード片の static_assert が両版で通る）。確認問題 2（`x = 0` で a が全部 0 になる）・確認問題 3（`max(best, i)` が `no matching function for call to 'max(int&, std::tuple_element<0, const std::tuple<long int, int&> >::type&)'` になる）・確認問題 1 の「`auto`・`auto&&` なら受けられる」を小さなプログラムで確かめた
- ACL（v1.6、third_party/ac-library と ~/lib/ac-library-master/document_ja/）：`scc()` は `vector<vector<int>>` でトポロジカル順（scc.md）、`explicit dsu(int n)`、`int val() const`、`template <class S, auto op, auto e> struct segtree`、lazysegtree.hpp の `"mapping must work as S(F, S)"`
- 参考の URL 4 件：すべて 200 で、題名が書かれたとおり（cppreference の Range-based for loop・Structured binding declaration・std::ranges::views::enumerate, std::ranges::enumerate_view、GitHub の ac-library document_ja/scc.md）。en.cppreference.com・github.com は付録 B にある
- 図：`python3 tools/render_svg.py` で 360px・720px の PNG にして目で確かめた。白い背景・幅 400・viewBox と同じ比・文字はテキスト・重なりやはみ出しなし。catalog の visual（static・priority 1、4 部品に分けて節へ矢印）を満たし、①〜④ と本文の 3 つの問い・部品ごとの行き先の箇条書きが対応する
- 執筆者の未解決の点 1（cpp-comparators#less-equal-pitfall の見出し）：リンク先の本文の表では落ちるのは 3.5×10^4 以上で、このページの「大きな入力の sort で RE」は本文と合う。見出しの直しは cpp-comparators 側の話で、このページの指摘にはしない

## 指摘

### 1｜直すとよい｜fact（F2）・clarity（U9）｜symptoms の後の段落（326 行）

- **問題**：「雛形に 2 行があるかどうかに関係なく、質問のたびに `endl` か `fflush(stdout)` を書けば届く」は、どの出力にどちらを使うかが書かれていない。2 行があるときに `println`・`printf` の後に `cout << endl` を書いても `stdout` は書き出されない（cpp-io#flush の本文「同期を切った `cout` の書き出しは `stdout` を書き出さない」）ので、「どちらか好きなほう」と読むと誤る
- **根拠**：cpp-io#flush の表と直後の段落・「直し方」の行（`cout << endl`、または `println`・`printf` の後に `fflush(stdout)`）
- **直し方**：「`cout` なら `endl`、`println`・`printf` ならその後に `fflush(stdout)` を書けば届く」と組を明示する

### 2｜直すとよい｜fact（F3）｜lookup-types の表（96 行）

- **問題**：`-7 / 2`・`-7 % 2` の意味が「0 に向かって切り捨てる」だけで、`%` の側（余りが負になる、符号は割られる数に従う）が分からない。`-7 % 2` は「切り捨て」では説明にならない
- **根拠**：C++11 以降、商は 0 方向への切り捨てで `a == (a / b) * b + a % b`。`-7 / 2 == -3`、`-7 % 2 == -1`
- **直し方**：「商は 0 に向かって切り捨て、余りは負になりうる」などにする

### 3｜直すとよい｜fact（F7）｜how-to-read（67 行と 69 行）

- **問題**：用語集の [一時オブジェクト] へのリンクが 69 行にあるが、この節で語が最初に出るのは 67 行（「`scc.scc()` の戻り値は一時オブジェクトだが」）である
- **根拠**：手引き §7（185 行「最初に出たときの 1 回だけ」）・§15-23
- **直し方**：リンクを 67 行の最初の「一時オブジェクト」に移し、69 行は括弧ごと外すか語だけにする

### 4｜直すとよい｜fact（F3）｜compile-errors の表（374 行・361 行）

- **問題**：(a) 一時オブジェクトを ranges のアルゴリズムに渡したときの文面は、`ranges::max_element` などでは `borrowed_iterator_t<...>` だが、`ranges::find` で得たイテレータを `*` すると `no match for 'operator*' (operand type is 'std::ranges::dangling')` と出る。表の断片では後者を引けない。(b) `min(int, long long int&)` は第 1 引数がリテラルのときの形で、2 つとも変数なら `min(int&, long long int&)` と出る
- **根拠**：g++-15 `-std=gnu++23` で `*ranges::find(vector<int>{1,2}, 1)` → `operand type is 'std::ranges::dangling'`、`int a; long long b; min(a, b);` → `no matching function for call to 'min(int&, long long int&)'`
- **直し方**：(a) 断片を `no match for 'operator*' (operand type is 'std::ranges::dangling')` と併記するか、`operand type is 'std::ranges::...'` に縮める。(b) 断片を `no matching function for call to 'min(` までにするか、`min(int&, long long int&)` を併記する

### 5｜直すとよい｜clarity（U3）｜compile-errors の表の前置き（352 行）

- **問題**：「`'` は端末によって `‘` `’` と表示される」。GCC が `‘’` を使うかは端末ではなくロケール（`LANG` が UTF-8 か）で決まる。また、この注意が出てくるのは表の直前で、先に出る 341〜343 行の抜き出し（`'operator<'`）を読んだ時点では分からない
- **根拠**：手元の g++-13・g++-15 の出力は `‘operator<’`。`LC_ALL=C` では `'` になる（GCC の引用符はロケールに従う）
- **直し方**：「`'` はロケール（`LANG`）によって `‘` `’` と出る」とし、341 行の抜き出しの直前か直後に 1 回置く

### 6｜直すとよい｜fact（F10）・内容の補充｜compile-errors の表・symptoms の表（執筆者の未解決の点 2・3）

- **問題**：(a) 未解決の点 2 の `'typeof' was not declared in this scope` は、いまは cpp-environment#gnu-mode の 93 行に文面がある（「`typeof`：`'typeof' was not declared in this scope`。GNU 拡張で、規格では `decltype` を使う」）。表に 1 行足せる。(b) 未解決の点 3 の「g++-15 の `-O0` でだけ `vector` の範囲外が `Assertion '__n < this->size()' failed` で止まる」は、cpp-environment#when-results-differ（220 行）と cpp-undefined-behavior#out-of-range（101 行）の両方に書かれた。手元（cph・VS Code の `-g` だけ）と提出で結果が違う症状として引かれやすい
- **根拠**：docs/cpp/cpp-environment.md 93 行・220 行、docs/cpp/cpp-undefined-behavior.md 101 行
- **直し方**：(a) compile-errors に「`'typeof' was not declared in this scope`｜`-std=c++23`（厳密モード）で GNU 拡張の `typeof`｜[GNU 拡張](../cpp/cpp-environment.md#gnu-mode)」を足す。(b) symptoms に「手元の `-O0` では `Assertion '__n < this->size()' failed` で止まるが、`-O2`・提出では止まらない｜範囲外の添字（g++-15 は `-O0` で検査が自動で付く）｜[配列の範囲外](../cpp/cpp-undefined-behavior.md#out-of-range)」を足す

### 7｜直すとよい｜fact（F10）｜導入（46 行）・symptoms（309 行・328 行）のリンク（メインの張り替えの対象）

- **問題**：cpp-environment は同じバッチで draft になり、節 #version-matrix・#stack-depth・#when-results-differ・#options がある。執筆者の報告のとおり、ページへのリンクのままの 3 か所を節へ張り替えられる
- **根拠**：docs/cpp/cpp-environment.md の stage: draft と各見出しの anchor
- **直し方**：メインのバッチの終わりの張り替えで、46 行 → #version-matrix、309 行 → #stack-depth、328 行の 1 つ目 → #when-results-differ・2 つ目 → #options にする（debugging-checklist も draft なので、303 行の前置きも該当の節へ）

### 8｜直すとよい｜figure（G5）｜read-line.svg の ② の説明

- **問題**：図の ② は「（添字, 成分）の組の列にする」だが、本文 58 行と確認問題 1 は「（添字, 成分への参照）の組」と書き、③④ の読みどころ（const が参照の先に伝わらない）はこの「参照」にかかっている。図だけを見た読者はコピーの組と受け取りうる
- **根拠**：本文 58・60・388 行、enumerate の要素の型 `tuple<ptrdiff_t, vector<int>&>`（read-line-ng のエラー文面）
- **直し方**：図の ② を「（添字, 成分への参照）の組の列にする」にそろえる（幅 400 に収まる長さ）

## 総合の判定

小さな直しで可。直すべき指摘は 0 件、直すとよい指摘は 8 件（うち 7 はメインのリンクの張り替え）。表の行き先・コンパイルエラーの文面・1 行の読み方の型の主張・コード片・図はどれも確かめたとおりだった。
