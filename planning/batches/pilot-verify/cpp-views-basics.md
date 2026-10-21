# 検証：cpp-views-basics（views の基本）

- 対象：docs/cpp/cpp-views-basics.md、snippets/cpp-views-basics/（19 個。うち indices-ng・split-cxx20-ng は本文に取り込まない失敗例）。図はなし（docs/img/cpp-views-basics/ はない。catalog の visual は dynamic・priority 2 で、作らなくても規則違反ではない）。問題はなし（catalog の problems: []、台帳の該当もなし）
- 観点：事実（fact.md）・コード（code.md）・図（figure.md）・分かりやすさ（clarity.md）・規則（style-guide.md）
- 検証日：2026-10-21

## 実行した検査と結果

- `python3 tools/check_snippets.py snippets/cpp-views-basics`：コード片 19・コンパイル 37 回・期待と違う 0（g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0、g++-13 (Ubuntu 13.4.0-6ubuntu1~22~ppa2) 13.4.0）
- `python3 tools/check_pages.py --page cpp-views-basics`：エラー 0。警告 5（未作成のページへの参照：cpp-lambda など。試作の段階では想定どおり）
- `python3 tools/fix_problems.py --check`：直すべき行 0
- `npx textlint docs/cpp/cpp-views-basics.md`：警告・エラーなし
- 自分で確かめたこと（作業場所 /tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/ff4dc6ee-16d4-486c-b97a-49fefbe7b218/scratchpad/verify-cpp-views-basics/。g++-13・g++-15 の両方）
    - t1.cpp：`views::iota(0, ssize(v))` の要素の型は `int`（`static_assert` が通る）。本文 101 行の「要素も `ptrdiff_t`」は誤り（指摘 1）
    - t3.cpp：`views::iota(0, v.size())` のエラー文は本文 94 行のとおり。原因は libstdc++ の推論ガイドの制約（`/usr/include/c++/15/ranges` 735〜737 行：`__is_signed_integer_like<_Winc> == __is_signed_integer_like<_Bound>`）。「要素の型を決められない」からではない（指摘 2）
    - t5.cpp：`a = {1,2,3,4}` の filter（偶数）を 1 回回し、`a[1] = 5` にしてもう一度回すと `5 4` と出る（filter が覚えた先頭の位置を使い回す）。本文 64 行の「書き換えると、次に回したときは新しい値が見える」は filter では成り立たない（指摘 3）
    - t2.cpp：`0uz` は `-std=gnu++20` で `warning: use of C++23 'size_t' integer constant`（46 行の記述どおり）
    - t4.cpp：`views::iota(5, 1)` は 5, 6, …, 11 と増え続け、`-D_GLIBCXX_ASSERTIONS` で `Assertion 'bool(__value <= __bound)' failed` で止まる（83 行どおり）
    - lt.cpp（lifetime.cpp の `evens_bad` を実際に回す版）：`-Wall -Wextra` で寿命の警告なし、`-fsanitize=address` で `stack-use-after-return`（235 行どおり）。右辺値の版はサニタイザでも問題なし
    - b.cpp：長さ $2 \times 10^4$ の二重ループで、普通の for と `views::iota` は g++-13 で 40〜41 ms と 40〜42 ms、g++-15 で 48〜49 ms と 48〜49 ms（81 行の結論と一致）
    - pipe・recompute・filter-transform・take-drop・keys-values・reverse-iota・common-ok・lifetime を `-std=gnu++20 -Wall -Wextra` でもコンパイルし、エラー・警告なし（70 行の「`-std=gnu++20` から使える」を裏付けた）
    - `indices-ng.cpp` を g++-15 の `-std=gnu++26` でもコンパイルし、`'indices' is not a member of 'std::views'`（103 行どおり。snippet の設定は gnu++23 なので、gnu++26 の部分は手で確かめた）
    - `ranges::to`：`/usr/include/c++/13/ranges` に定義なし、g++-15 にはある（225 行どおり）
    - compile-error の 4 つ（common-ng・filter-const-ng・split-cxx20-ng・iota-size-ng）のエラー文が、本文の説明する原因（`_Sentinel<true>`、`const filter_view` の `begin`、`string_view` の範囲コンストラクタがない、`_Iota` の呼び出し）と一致することを両方の版で確かめた
    - `a | views::transform(f) | views::filter(p)` の $N + K$ 回（確認問題）：filter-transform.cpp の 8 回（$5 + 3$）と、filter の begin・++ が `find_if` で各要素を 1 回判定し、取り出しで残った要素をもう 1 回変換する仕組みから正しい
- 出典：参考の 7 件はすべて HTTP 200。cppreference の題名は「std::ranges::views::iota, std::ranges::iota_view, std::ranges::views::indices」（`/w/` のない新しい URL でも開ける）。cpprefjp の split_view などの題名も一致。3 ドメインとも `tools/check_noai.py` で noai の指定なし（付録 B への追加提案は妥当）。本文は資料の文の並びを写していない（F8）
- 図：なし（静的な図・動く図とも置かれていない）。G1〜G7 は対象外

## 指摘

### 1. 直すべき｜事実（F2・F3）・コード（C3）｜#iota-size-mismatch 101 行

- 問題：「`ssize(v)`：…要素も `ptrdiff_t` になる」とあるが、`views::iota(0, ssize(v))` の要素は `int` である。要素の型は始まりの `0` の型で決まる（同じページの #iota-int 107 行が述べる規則そのもの）。ページの中で食い違っている
- 根拠：t1.cpp の `static_assert(is_same_v<ranges::range_value_t<decltype(views::iota(0, ssize(v)))>, int>)` が g++-13・g++-15 で通る。iota_view の推論ガイドは `iota_view(W, Bound) -> iota_view<W, Bound>` で、要素は `W`
- 直し方：101 行を「`ssize(v)`：符号付きの大きさ（`ptrdiff_t`。64 bit の Linux では `long`）を返す。始まりの `0` も符号付きなので通る。要素は始まりの型の `int` である」に直す。iota-size-ok.cpp に `static_assert(is_same_v<ranges::range_value_t<decltype(views::iota(0, ssize(v)))>, int>);` を足して裏付ける

### 2. 直すべき｜事実（F2）・分かりやすさ（U2）｜#iota-size-mismatch 88 行

- 問題：「`iota` は符号の違う 2 つの型から要素の型を決められないからである」は理由として不正確である。要素の型は常に始まりの型で決まる（#iota-int）。エラーになるのは、始まりと終わりが「一方は符号付きの整数、他方は符号なしの整数」の組を、標準が推論ガイドの制約で禁じているからである（符号付きと符号なしの比較は、`-1 < v.size()` が偽になるなど結果が食い違うため）
- 根拠：libstdc++ 15 の `<ranges>` 735〜737 行の推論ガイドの制約。cppreference の iota_view の Deduction guides の項。`views::iota(0, n)`（int と long long。どちらも符号付き）は通るので、「型が違うと決められない」では #iota-int と説明が合わない
- 直し方：「始まりの `0` は `int`（符号付き）、終わりの `v.size()` は `size_t`（符号なし）である。`iota` は、符号付きと符号なしの整数を組にすることを禁じている（比べたときの結果が食い違うため）。`int` と `long long` のように符号がそろっていれば型が違っても通る」。あわせて、#iota-int（要素の型は始まりで決まる）を #iota-size-mismatch より前に置くか、101 行から #iota-int へリンクすると、指摘 1 の直しも読みやすくなる（sections の順は変えず、リンクで済ませてもよい）

### 3. 直すべき｜事実（F2）｜#what-is-view 64 行

- 問題：「途中で元の配列を書き換えると、次に回したときは新しい値が見える」と view 全般の性質として書いているが、`filter` では成り立たない。filter の view は最初に見つけた要素の位置を覚えておく（ページの 145 行自身が述べる）ので、書き換えで判定の結果が変わると、2 回目は条件を満たさない要素から始まる。標準も、filter で取り出した要素を条件を満たさない値に書き換えると未定義動作になると定める
- 根拠：t5.cpp で `a = {1,2,3,4}`、偶数の filter を回すと `2 4`、`a[1] = 5` の後にもう一度回すと `5 4`（g++-13・g++-15 とも）
- 直し方：64 行の後か #filter-transform の落とし穴 2 に 1 文足す。「ただし `filter` の view は先頭の位置を覚えるので、判定の結果が変わる書き換えをした後に同じ view を回し直してはいけない（作り直す）」。recompute.cpp は transform なので、例はそのままでよい

### 4. 直すべき｜規則（§2.1・F10）｜front matter 32 行 `gcc_min: 13`

- 問題：catalog の `gcc_min` は `null` で、make_skeleton.py は catalog の値を写す。執筆者が 13 に書き換えたことになる。手引き §2.1 は front matter で直してよいのを `complexity`・`stage`・`updated` だけとしており、pilot.md の報告にもこの変更の提案がない
- 根拠：planning/catalog/cpp.yaml の cpp-views-basics の `gcc_min: null`、tools/make_skeleton.py 17・40 行
- 直し方：値そのもの（13）は正しい（ページの書き方はすべて g++-13 で通ることを check_snippets と手で確かめた。C6 の「front matter と設定の一致」も満たす）。メインが提案として受け取り catalog 側とそろえるか、手引きで「cpp のページの `gcc_min`・`cpp_std` は確かめた値に直してよい」と許すかを決める

### 5. 直すとよい｜分かりやすさ（U3）｜#what-is-view 52 行

- 問題：`|` が何なのかの説明がない。レート 1000 の読者は `|` をビットの OR として知っており、`a | views::filter(f)` を初めて見ると戸惑う
- 直し方：52 行の前に 1 文足す。「`a | views::filter(f)` は `views::filter(a, f)` と同じ意味で、`|` は左の範囲を右の部品に渡す記号である（ビットの OR とは別）」

### 6. 直すとよい｜事実（F2）・分かりやすさ（U6）｜#what-is-view 52 行

- 問題：「view は、元の範囲への参照と『どう見るか』の規則だけを持つ」と言い切っているが、#lifetime 237 行のとおり、右辺値を流すとコンテナは view の中に移される。この節だけを断片で読むと、`make(n) | views::filter(…)` も参照だと誤解する
- 直し方：「（右辺値のコンテナを流したときは中に持つ。[view の寿命](#lifetime)）」と 1 句足す

### 7. 直すとよい｜分かりやすさ（U8）｜確認問題 252〜256 行

- 問題：末尾の 2 問は本文の文をそのまま問うている（reverse の問いは 118 行・256 行がほぼ同じ文）。#lifetime と #iota-int には確認問題がない
- 直し方：reverse の問いを、たとえば「`vector<int> v = make(n); return v | views::filter(…);` と `return make(n) | views::filter(…);` のどちらが安全か。なぜか」や「`long long n` に対する `for (long long i : views::iota(0, n))` は $n = 3 \times 10^9$ で正しく回るか」に替える

### 8. 直すとよい｜分かりやすさ（U3）｜#common 212 行

- 問題：「終わりを別の型（番兵）で表す」の「番兵」が、この読者には分からない。用語集にもまだない
- 直し方：「終わりに来たかを判定するだけの別の型（番兵。`take_while` なら『条件が偽になったか』を調べる物）」のように中身を一言書く。用語集への「番兵（sentinel）」の追加はほかのページ（binary-search-answer）からも提案があるので、まとめて反映するとよい

### 9. 直すとよい｜事実（F2）｜#iota 83 行

- 問題：$a > b$ のときの振る舞いを「空にならない」「増え続けた」と観測として書いているが、規格上は前提（$a \le b$）を破った未定義動作である。snippet iota.cpp 17 行のコメントは「未定義」と書いており、本文と言い方がそろっていない
- 直し方：「$a > b$ は前提を破る[未定義動作](../cpp/cpp-undefined-behavior.md)で、普通の for のように 1 回も回らないとは限らない。手元の g++-15 では…」とする（#lifetime で未定義動作にリンクしているので、リンクは最初に出るこちらへ移す）

### 10. 直すとよい｜規則（§2.3）｜各節の見出し（執筆者の未解決の点）

- 問題：見出しは sections の title を短くしたもので、title の「（C++20）」や中身の一部（「`for (int i : views::iota(0, n))` は普通の for と同じ速さ」など）が落ちている。手引き §2.3 は「`sections` の各節を `## 見出し {#anchor}` の形で必ず置く」とだけあり、title どおりにするかが決まっていない。check_pages は anchor だけを見て通る
- 直し方：メインが決める。読みやすさの点では今の短い見出しのほうがよく、版は各節の「版」の行にあるので失われる情報はない。短くしてよいと決めるなら手引きに明記する

### 11. 直すとよい｜コード（C6）｜snippets/cpp-views-basics/naive-pipe.yaml

- 問題：ほかの 18 個は `compilers: [g++-13, g++-15]` だが、naive-pipe だけ `[g++-15]`。C++ の章は両方で通す決まり（code.md C6）
- 直し方：`compilers: [g++-13, g++-15]` にする（素朴な for だけなので g++-13 でも通るはず）

### 12. 直すとよい｜分かりやすさ（U2）｜#split-join 207 行

- 問題：`-std=gnu++20` で `string_view(w)` が通らないと書くが、C++20 のままの書き方がない。手元で `-std=gnu++20` を使う読者は困る
- 直し方：「C++20 では `string(w.begin(), w.end())` と書く」と 1 句足す（split の各部分は連続した範囲の部分範囲なので、この形で文字列にできる）

### 執筆者の未解決の点（pilot.md）への見解

- 「取り込まない失敗例の snippet を置いてよいか」：indices-ng・split-cxx20-ng は本文の主張（103 行・207 行）を検査で裏付けるもので、置く価値がある。手引きで「本文の主張を裏付ける、取り込まない snippet を置いてよい」と認めるのがよい。ただし indices-ng の「gnu++26 でもない」は設定が gnu++23 なので裏付けていない（必要なら `flags: "-std=gnu++26 …"`、compilers を g++-15 だけにした版を足す）
- 4 つの「発見」（iota(5,1)、filter の const、split の末尾の空白、ranges::to・indices の有無）はすべて手で再現した

## 良かった点

- 主張のほぼすべてを compile-error・run の snippet と手元の計測で裏付けており、エラー文まで実物と一致する
- 「transform の後に filter」の $N + K$ 回、iota の符号・int の罠、寿命と ASan など、実際に起きる落とし穴を具体的に書いている

## 総合の判定

小さな直しで可（指摘 1〜3 は数文の修正で済む事実の誤り。指摘 4 はメインの判断で片付く）
