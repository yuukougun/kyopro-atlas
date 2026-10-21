# acl-reading の検証（工程8b・b1）

- 対象：docs/cpp/acl-reading.md、snippets/acl-reading/（20 組）、docs/img/acl-reading/template-args.svg
- 観点：planning/checklists/ の fact.md・code.md・clarity.md・figure.md、手引き planning/style-guide.md、執筆者の報告 planning/batches/b1/acl-reading.md の未解決の点

## 確かめたこと

- 検査：`python3 tools/check_pages.py --page acl-reading`（エラー 0・警告 0）、`python3 tools/check_snippets.py snippets/acl-reading`（20 片・コンパイル 37 回・期待と違う 0）、`npx textlint`（0 errors・1 warning。193 行の数式の中のカンマで、§13.8 の誤検出）。コンパイラは g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0 と g++-13 (Ubuntu 13.4.0-6ubuntu1~22~ppa2) 13.4.0。third_party/ac-library と ~/lib/ac-library-master の atcoder/ は同じ（.vscode だけ違う）
- compile-error のコード片は、エラーの文面が本文の理由と合うことを g++-13・g++-15 で確かめた：explicit-ng（`conversion from 'int' to non-scalar type 'atcoder::dsu'`）、modint-cout-ng（`no match for 'operator<<'`）、modint-println-ng（`std::formatter must be specialized`）、modint-sort-ng（`no match for 'operator<'`）、capturing-ng（本文に引いた `'<lambda closure object>main()::<lambda(int, int)>{m}' is not a constant expression`）、template-arg-ng（`static assertion failed: mapping must work as S(F, S)`、場所は lazysegtree.hpp:28）、segtree-lambda-cxx17-ng（`lambda-expression in template-argument only available with '-std=c++20'`）
- ACL のドキュメント（document_ja）と照らした：explicit（appendix.md「modint 以外の構造体のコンストラクタには explicit」、ソースでも dsu・fenwick_tree・segtree・lazy_segtree・scc_graph・two_sat・mf_graph・mcf_graph に explicit）、デフォルトコンストラクタ（appendix.md。メンバの呼び出しは未定義、後から代入できる）、制約外は未定義（index.md）、`ATCODER_` のマクロ（appendix.md）、dsu の計算量（ならし $O(\alpha(n))$）、inv の制約（modint.md：`gcd(x.val(), mod) = 1`、$O(\log \mathrm{mod})$）、composition は $f \circ g$、`z[0]`、crt の解なし `{0, 0}`、scc の順。要点・front matter の complexity・本文の計算量は一致
- 自分で動かして確かめた：
    - `fenwick_tree<long long> fw(3)` の `fw.sum(2, 4)` は `Assertion '0 <= l && l <= r && r <= _n' failed.` で止まり、`-DNDEBUG` では 60734 を返して正常終了（本文どおり）
    - groups-ng：g++-15 gnu++23 は `0 2`、g++-15 gnu++20 と g++-13 gnu++23 は Segmentation fault、ASan では `heap-use-after-free`、`-Wall -Wextra` で警告なし（本文どおり）。GCC の cxx-status で P2718R0 は GCC 15
    - v1.5（~/lib/ac-library-v1.5）で `x.val() - 1` が 4294967295、`max(x.val(), 0)` が `no matching function for call to 'max(unsigned int, int)'`（本文どおり）
    - `S = int` に `long long op(long long, long long)` を渡した segtree は警告なしで通り、2000000000 + 2000000000 が -294967296 になる（304 行のとおり）
    - v1.5 と v1.6 のソースの diff：val() の型、lazysegtree の static_assert の文面 2 か所、lcp_array の assert 2 つ、dsu の `_leader`、**convolution の 2 か所**（指摘 4）
- ACL のリリース（GitHub API で取得）：v1.5 は 2023-04-07、v1.6 は 2025-05-01。v1.5 の要約は「Segtree / LazySegtree can accept more broad function types, e.g. `S op(const S& a, const S& b)` (#160)」。v1.6 には val() の変更のほか、convolution の余分なコピーの修正・expander.py の行番号の対応がある
- 参照先の節：cpp-initialization#explicit・cpp-range-for#temporary-range・cpp-macros-template-file#bundling・lazy-segment-tree#acl-conventions は、いまは本文に見出しがある（執筆者の未解決の点 4 つ目は解決済み）
- 図：Windows の Chrome（headless=new）で template-args.svg を等倍（720×400）と、幅 390px の画面に幅 358px で（2 倍密度、暗い背景の上に）画像にして目で確かめた。和文も出て、はみ出し・重なりはない。背景は白で塗られ、`viewBox` があり、文字はテキストのまま。値の側は実線、作用の側は破線、mapping は点線で、色に加えて線の種類で分けている。内容（7 つの引数の並び、composition は「g の後に f」、mapping の引数は F が先）は本文と一致（執筆者の未解決の点 3 つ目は確認済み。小さい画面の読みやすさは指摘 8）

## 指摘

### 1｜直すべき｜fact（F2・F4）｜#version の 95 行、#passing-functions の見出し（209 行）・213 行・225 行、front matter の sections の passing-functions の title

- **問題**：「segtree・lazy_segtree がラムダなども受け取るようになったのは v1.5 からで、それより前の版ではラムダを直接渡せない」「ACL v1.4 以前は関数の名前しか受け取らない」は誤り。v1.4 のテンプレート引数は関数ポインタ `S (*op)(S, S)` で、C++20 ならキャプチャのないラムダは関数ポインタへ変換されて渡せる。v1.5（#160）で広がったのは「関数の形」で、`S op(const S& a, const S& b)` のように引数や戻り値の型が `S(S, S)` ちょうどでない関数・ラムダも受け取るようになった
- **根拠**：v1.4 の segtree.hpp・lazysegtree.hpp・internal_bit.hpp を raw.githubusercontent.com から取得（`tools/check_noai.py` で指定なしを確認）し、作業用の場所で `segtree<int, [](int x, int y) { return min(x, y); }, [] { return INT_MAX; }> seg(a);` と名前付きの `constexpr auto add = …` の両方を g++-13・g++-15 の `-std=gnu++20` でコンパイル・実行すると、どちらも通り `2 0` と出た。一方、v1.4 に `[](const int& x, const int& y) {…}` を渡すと `conversion from 'int (*)(const int&, const int&)' to 'int (*)(int, int)' in a converted constant expression` でエラー、v1.6 では通る。v1.5 のリリースノートの要約も上のとおり（ラムダの話ではない）。執筆者が未解決とした点の答え
- **直し方**：95 行を「v1.5（2023-04）から、segtree・lazy_segtree は `S op(const S& a, const S& b)` のように `S(S, S)` として呼べる物を広く受け取るようになった。それより前の版は関数ポインタ `S (*)(S, S)` で受け取るので、型がちょうど `S(S, S)` の関数か、それに変換できるキャプチャのないラムダ（C++20）に限る」などに直す。213 行の「ACL も v1.5 から、関数の名前に限らず呼び出せる物を受け取る」と 225 行の「ACL v1.4 以前は関数の名前しか受け取らない」も同じ趣旨に直す。見出しと sections の title から「ACL v1.5〜」を外す（例：「関数の渡し方：関数の名前か、キャプチャのないラムダ（C++20）」。§13.2 で執筆者が直してよい）。311 行の参考の説明（「受け取る関数の形が広がった」）は正しいのでそのままでよい

### 2｜直すべき｜fact（F2・F4）｜#modint の 153 行

- **問題**：「`/` は逆元を掛ける。法が素数で、割る数が法の倍数でないときだけ使える」は言い過ぎ。ACL の割り算（inv）の制約は `gcd(x.val(), mod) = 1` で、法が素数でなくても割る数が法と互いに素なら使える（`modint` や `static_modint<M>` で合成数の法を使うとき）。次の行で `static_modint<M>`・`modint` を紹介しているので、この言い方だと「合成数の法では割り算できない」と読める
- **根拠**：document_ja/modint.md の inv の制約（`gcd(x.val(), mod) = 1`）。ソースでも素数でない法では `inv_gcd` を使い `assert(eg.first == 1)` で止める
- **直し方**：「`/` は逆元を掛ける。割る数が法と互いに素のときだけ使える（法が 998244353 のような素数なら、法の倍数でなければよい。そうでなければ `assert` で止まる）」などにする

### 3｜直すとよい｜fact（F2）・clarity（U3）｜#passing-functions の 219 行

- **問題**：「名前空間の変数にするなら `constexpr` を付けておく（テンプレート引数はコンパイル時に決まる値でなければならないため）」は、`constexpr` がないと渡せないように読めるが、キャプチャのないラムダは `constexpr` なしでも渡せる。読者が #capturing-lambda のエラー（`the value of 'op' is not usable in a constant expression`）の原因を「constexpr を付け忘れたこと」と取り違えるおそれがある
- **根拠**：作業用の場所で、名前空間の `auto add = [](long long a, long long b) { return a + b; };`・`auto zero = [] { return 0LL; };`（constexpr なし）と、`main` の中の同じ宣言の両方を `segtree<long long, add, zero>` に渡すと、g++-13・g++-15 の gnu++23 で通り正しい値を出した。キャプチャのある `auto op = [&](…){…};` だけが上のエラーになる
- **直し方**：「`constexpr` を付けておくと、コンパイル時に使う値だと分かりやすい（キャプチャのないラムダは付けなくても通る。通らないのはキャプチャのあるラムダで、#capturing-lambda のとおり）」などにするか、理由の括弧を外す

### 4｜直すとよい｜fact（F3）｜#version の 89〜93 行

- **問題**：「v1.5 との違いは次のとおりで、手元で 2 つの版のソースを比べて確かめた」と全部を挙げたように書いているが、convolution.hpp の 2 か所（`l.val() - r.val()` の計算の書き換えと、`std::move` で余分なコピーを減らした修正）と expander.py の変更が抜けている。使い方は変わらないが、「次のとおり」が全部だと読める
- **根拠**：`diff -r ~/lib/ac-library-v1.5/atcoder ~/lib/ac-library-master/atcoder` で convolution.hpp の 133 行・226〜227 行が違う。v1.6 のリリースノートに「Fix redundant copy in rvalue ref overload of `convolution`」「expander.py: trace line numbers back to the original source file」
- **直し方**：「おもな違いは次のとおり」にし、3 つ目の項目に「ほかに convolution の内部の修正と expander.py の改良がある」を足す

### 5｜直すとよい｜code（C5）｜#modint-val の 158 行・modint-val.cpp の取り込み、#modint-val の 179 行・modint-sort-ok.cpp

- **問題**：`println` と、`ranges::sort` の射影（第 3 引数にラムダ）を使っているが、C++ の章へのリンクがない（手引き §9「views・`println`・deducing this などを使うときは C++ の章の該当ページへリンクする」）。読者の想定（現代的な書き方に不慣れ）では `ranges::sort(v, {}, …)` の `{}` が読めない
- **根拠**：cpp-io に `#format-println`・`#unprintable-types`（modint は `.val()` を出す、と同じ話題）、cpp-algorithms に `#projection` の節がある
- **直し方**：158 行に「（[出力の書き方](../cpp/cpp-io.md#unprintable-types)）」などを、179 行の前の文に「`ranges::sort` の第 3 引数は比べる値を取り出す関数（[射影](../cpp/cpp-algorithms.md#projection)）」を足す

### 6｜直すとよい｜code（C4）｜snippets/acl-reading/segtree-args.cpp の取り込みの範囲

- **問題**：取り込みが `op`・`e` の定義から `main` の終わりまでで、入力を読むループまで本文に出る。節の主題は 3 つのテンプレート引数なので、見せたいのは `op`・`e` の定義と `segtree<int, op, e> seg(a);`・`seg.prod(l, r)` の数行
- **直し方**：`core` を `op`・`e` の定義と `segtree<int, op, e> seg(a);` の行、`prod` の行だけにする（2 つの区間に分けるか、`main` を短くする）。lazy-args.cpp も `main` の頭と入力が入っているので、同じく `seg(init)` までの数行にできる

### 7｜直すとよい｜clarity（U9）・fact（F4）｜#components の表（114 行・117 行）

- **問題**：(a) `mf_graph` の「`flow(s, t)` は流した量を返し、グラフに残る」は、何がグラフに残るのか分かりにくい（残るのは流した後の状態で、続けて呼ぶとその続きから流す）。(b) `suffix_array`・`lcp_array` の行は、作り方が `suffix_array(s)` だけで、「開始位置の列を返す」も suffix_array だけの話。`lcp_array` は `lcp_array(s, sa)` と作り、長さは $N - 1$
- **直し方**：(a)「`flow(s, t)` は流した量を返す。流した状態はグラフに残り、`edges()` で辺ごとの流量を読める」。(b) 作り方を `suffix_array(s)`・`lcp_array(s, sa)` に、注意を「sa は接尾辞を辞書順に並べた開始位置、lcp は隣どうしの最長共通接頭辞（長さ $N - 1$）」にする

### 8｜直すとよい｜figure（G3）｜template-args.svg

- **問題**：viewBox の幅 720 に対して文字は 12〜15。幅 390px の画面（表示幅 358px）では約 0.5 倍に縮み、灰色の補足（結合法則・`op(e(), x) = …`・`composition(f, id()) = f`・凡例）が 6px 前後になって読みにくい
- **根拠**：Chrome（headless=new）で幅 358px・2 倍密度で描いた画像（/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/ff4dc6ee-16d4-486c-b97a-49fefbe7b218/scratchpad/v-acl-reading/narrow.png）
- **直し方**：補足の式は本文（266〜269 行と #segtree-args）にあるので図から外し、2 つの枠を縦に並べるなどで幅を詰めるか、文字を大きくする。ほかのページの図の指摘と同じ程度の直し

### 9｜直すとよい｜clarity（U5・U6）｜#capturing-lambda（228〜256 行）

- **問題**：キャプチャのあるラムダを op・e に渡せない話と、max_right の判定関数との区別は、前提のページ cpp-lambda の #template-argument にほぼ同じ内容（理由と「混同」の注意）がある。このページでは ACL での回避策（グローバル変数・`S` に持たせる）が独自の中身なので、重なる理由の説明は前提へのリンクで足りる
- **直し方**：節の冒頭の理由の 2 文に「（理由は[ラムダ式の節](../cpp/cpp-lambda.md#template-argument)）」を添え、確認問題の答えと同じ説明が本文に 2 度出ないようにする。#dsu-groups も [cpp-range-for#temporary-range](../cpp/cpp-range-for.md#temporary-range) と表まで重なるので、ACL を読むときの要点（変数に受けてから回す）を残して、版ごとの結果はリンク先に任せてもよい

## 執筆者の未解決の点への答え

- cpp_std・gcc_min が null：catalog の規則どおりで問題ない
- 「ACL v1.4 以前は関数の名前しか受け取らない」：誤り（指摘 1）
- 図の表示：確かめた。内容は正しく、小さい画面の文字だけ指摘 8
- cpp-initialization#explicit・cpp-range-for#temporary-range：いまは本文に見出しがある
- 表の手法のページが stub：ページへのリンクだけで問題ない

## 総合の判定

小さな直しで可。直すべきは 2 件（指摘 1：v1.4 以前とラムダの関係の誤り、指摘 2：割り算の条件の言い過ぎ）。どちらも数行の書き換えで済み、コード片は変えなくてよい（指摘 1 は本文と front matter の見出し）。
