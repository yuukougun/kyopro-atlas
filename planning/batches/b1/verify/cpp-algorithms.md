# cpp-algorithms の検証（工程8b・b1）

- 対象：docs/cpp/cpp-algorithms.md、snippets/cpp-algorithms/ の 21 片（.cpp と .yaml）、docs/img/cpp-algorithms/unique-erase.svg
- 観点：planning/checklists/ の fact.md・code.md・clarity.md・figure.md、手引き planning/style-guide.md

## 確かめたこと

- 検査：`python3 tools/check_pages.py --page cpp-algorithms`（エラー 0・警告 0）、`python3 tools/check_snippets.py snippets/cpp-algorithms`（21 片・コンパイル 42 回・期待と違う 0。g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0、g++-13 (Ubuntu 13.4.0-6ubuntu1~22~ppa2) 13.4.0）、`npx textlint docs/cpp/cpp-algorithms.md`（0 errors・4 warnings。執筆者の報告どおり、代替テキスト・半開区間 $[l, r)$・数式の中の読点・エラー文のコードの誤検出で、§13.8 により残してよい）
- front matter：`git diff` で、変わったのは complexity・stage・sections の title 8 つ（anchor・level は不変。§13.2 で可）と、cpp_std（null → 20）・gcc_min（null → 13）。complexity・要点の計算量・本文が一致する（指摘 7 も見る）
- 「`-std=gnu++20` から使える」の主張：取り込む run のコード片 13 本（fold-left を除く）を g++-13・g++-15 の `-std=gnu++20 -O2 -Wall -Wextra` でコンパイルし、すべて通り警告もなし。accumulate.cpp の「`-Wall -Wextra` で警告は出ない」もこれで確かめた
- 自分で確かめた主張（作業用の場所 v-cpp-algorithms/）
    - `long long best = 0; best = max(best, ranges::count(v, 1));` は g++-13・g++-15（gnu++23）とも `no matching function for call to 'max(long long int&, std::ranges::range_difference_t<…>)'` でコンパイルエラー（cnt.cpp。指摘 1）
    - `ranges::max(ps, {}, &P::score)` の戻り値の型は `P`（値。`static_assert(is_same_v<…, P>)` が通る）。最大が複数あれば最初の要素を返し、`ranges::minmax` は最小が最初・最大が最後（mx.cpp。指摘 3、執筆者の未解決の点 2）
    - set への問い合わせ：要素 $2 \times 10^4$ 個・$2 \times 10^4$ 回で、`std::lower_bound` 2637 ms・`ranges::lower_bound` 2111 ms・メンバ 0.9 ms（st.cpp、g++-15 -O2）。本文の「約 2.3 秒・1 ms」と矛盾しない
    - reduce の順序：`{1e16, 1, -1e16, 1, 1, 1, 1, 1}` で accumulate は 5、reduce は 4（red.cpp、g++-15 -O2）。libstdc++ の reduce は順を変えて足すので「浮動小数点数では結果がわずかに変わりうる」は実際に起きる（執筆者の未解決の点 3 は解決）
    - accumulate の値：$0 \to 10^9 \to 2 \times 10^9 - 2^{32} \to -1294967296$ と手で追い、本文と一致。int への変換は C++20 から $2^{32}$ を法とする規定で、未定義動作ではない。partial_sum の $4 \times 10^9 - 2^{32} = -294967296$ も一致（こちらは int どうしの和なので未定義動作。指摘 5）
    - 例の数値（lower_bound の 1 4 3・2 2 0・6、next_permutation の 2 6・3 3、max_element の 9 1・7 5・2、ranges の -1 4 4・2 1、projection の carol alice bob・bob・3,7 2,9 1,5、ranges::unique の 3、fold_left の 4000000007・1・2）を手で数え直し、本文・cases と一致
    - dangling-ng のエラー文 `no match for 'operator*' (operand type is 'std::ranges::borrowed_iterator_t<std::vector<int> >')` は g++-13・g++-15 とも本文どおり。starts-with-ng は両方で `'starts_with' is not a member of 'std::ranges'`
- 事実の出典：GCC の libstdc++ Implementation Status（gcc.gnu.org、付録 B）を開き、P2322R6 fold・P2302R4 contains・P1223R5 find_last が 13.1、P2440R1 は ranges::iota が 13.1（shift 系は 16.1）、P1659R3 starts_with・ends_with が 16.1 であることを確かめた。本文 262・313 行と一致。参考の cpprefjp・cppreference はどれも付録 B のドメイン
- 図 unique-erase.svg：headless の Chrome（chrome-headless-shell 146、Linux）で 620×300 の等倍に画像にして見た（v-cpp-algorithms/fig.png）。値（1 1 2 3 3 3 → 1 2 3 ? ? ? → 1 2 3）は本文の例 `3 1 3 2 1 3` と unique-erase.cpp の cases と一致。背景は白、`viewBox` あり、文字はテキストのまま `font-family="sans-serif"`、不要部分は灰色に加えて破線と「?」で区別。幅 390px の画面でも viewBox で縮む。矢印の向きに誤りがある（指摘 2）。catalog の visual は priority 3 なので静的な図でよい
- リンク先：11 の節リンクは anchor があり、どのページも draft。`guide/glossary.md#temporary-object` はまだない（§13.5 によりよい。執筆者の用語集の提案を反映すれば解決）
- 執筆者の未解決の点：(1) 図は上のとおり見た（指摘 2）。(2) ranges::max は最初の要素を返すと確かめた。本文に足す必要はない。(3) 上のとおり解決。(4) 指摘 5。(5) cpp-container-idioms との重なりは 1 行とリンクで、重複として問題にしない

## 指摘

### 1｜直すべき｜fact（F2）・code（C3）｜#max-element の落とし穴 3（196 行）

- **問題**：「`(int)` で直すか、受ける変数を `long long` にする」の後半は誤り。`count` の戻り値は `ptrdiff_t`＝`long` で、`long long` とは別の型なので、`best` を `long long` にしても `max(best, ranges::count(v, 1))` はやはりコンパイルエラーになる。読者は直前の文から「`max` で比べる変数を `long long` にする」と読む
- **根拠**：cnt.cpp（`long long best` で `max(best, ranges::count(v, 1))`）が g++-13・g++-15 とも `no matching function for call to 'max(long long int&, …)'`。max-element.cpp の `long long c = count(…)` が通るのは、`max` に渡さず代入しているからである
- **直し方**：「`max` に渡すなら `(int)ranges::count(v, 1)` のように型をそろえる（`best` を `long long` にしても `long` とは別の型なのでエラーのまま）。代入だけなら `long long c = count(…)` で受けてよい」とする

### 2｜直すべき｜figure（G5）｜unique-erase.svg の矢印（defs の marker）

- **問題**：it と v.end() の矢印の先が上（マス）を向かず、右を向いて描かれる。marker の三角形が下向き（`M0,0 L10,0 L5,10`）なのに `orient="auto-start-reverse"` を使っているので、上向きの線の向きに合わせて 90 度回り、横向きになる
- **根拠**：v-cpp-algorithms/fig.png（headless Chrome で描いた画像）で、2 つの矢印の先がどちらも右向きの三角形になっている。binary-search の bounds.svg の検証（指摘 5）と同じ型
- **直し方**：marker を x 軸の向きの三角形にする。例：`<marker id="ar" viewBox="0 0 10 10" refX="9" refY="5" markerWidth="8" markerHeight="8" orient="auto"><path d="M0,0 L10,5 L0,10 z" fill="#333"/></marker>`

### 3｜直すとよい｜fact（F2）・code（C3）｜#projection の `const P& best`（projection.cpp と 229 行）

- **問題**：range を渡す `ranges::max` は要素の型 `P` を値で返す（コピー）。`const P& best = …` は一時オブジェクトを寿命の延長で受けているだけで、参照に見えて「要素そのもの（ps の中の要素）を指す」と誤解させる。本文の「score が最大の要素そのものを返す」も同じ誤解を招く
- **根拠**：mx.cpp で `static_assert(is_same_v<decltype(ranges::max(ps, {}, &P::score)), P>)` が通り、`&best == &ps[0]` は偽
- **直し方**：コードを `P best = ranges::max(ps, {}, &P::score);` にし、本文を「score の値ではなく、score が最大の要素（のコピー）を返す。位置が要るなら `ranges::max_element(ps, {}, &P::score)`」とする

### 4｜直すとよい｜fact（F2）｜#ranges-dangling の 1 文目（276 行）

- **問題**：「一時オブジェクトを渡すと、イテレータを返す関数の戻り値は `ranges::dangling` になる」は言い過ぎ。`string_view`・`span`・`views::iota(0, n)` のような借用できる range（borrowed_range）なら、一時オブジェクトでも普通のイテレータが返る
- **根拠**：cpprefjp「dangling」・cppreference の `borrowed_iterator_t`（`borrowed_range` でない右辺値のときだけ `dangling`）
- **直し方**：「`vector` など、要素を自分で持つコンテナの一時オブジェクトを渡すと」と限定する（借用できる range の説明は要らない）

### 5｜直すとよい｜code（C2・C8）｜partial-sum.yaml の 4 つ目の case

- **問題**：`2000000000 2000000000` の case の 3 行目 `-294967296` は、符号付き整数のあふれ（未定義動作）の結果を期待出力にしている。本文はそれを断っているが、コンパイラの版や最適化で変わると check_snippets が落ち、`-fsanitize=undefined` でも報告が出る
- **根拠**：本文 136 行と執筆者の未解決の点 4。checklist C8
- **直し方**：本文の数値はそのまま（「手元の g++-13・g++-15 -O2 では」と添える）にし、cases からは外して `partial-sum-ng` のような確かめ用の片（取り込まない）に分けるか、yaml にコメントで UB の値だと書く。メインの判断でよい

### 6｜直すとよい｜clarity（U3）｜#next-permutation の例の説明（171 行）

- **問題**：「それより辞書順で後ろの `3 1 2` と `3 2 1` の 2 通り」は、`3 1 2` 自身が「後ろ」に入っていて読みにくい
- **直し方**：「`3 1 2` 自身と、辞書順でその次の `3 2 1` の 2 通りしか見ない」とする

### 7｜直すとよい｜手引き（§2.1）｜front matter の cpp_std・gcc_min

- **問題**：§2.1 で執筆者が変えてよいのは complexity・stage・updated（と sections）だけだが、cpp_std（20）・gcc_min（13）を埋めている。値そのものは確かめた結果と合う（ranges・射影は C++20、C++23 の 4 つは GCC 13.1 から）。ほかの cpp のページも同じく埋めているので、規則の扱いをメインが決める点である。執筆者の手引きへの提案（cpp_std を最新の版にするか主な書き方の版にするか）も同じ
- **直し方**：メインが §5 の cpp に「cpp_std・gcc_min は執筆者が埋めてよい。cpp_std は主な書き方の版」などと決めて書く。このページの値は 20・13 のままでよい

### 8｜直すとよい｜code（C5）｜snippets の assert（§9）

- **問題**：§9 は「`main` と `assert` を持つ完全なもの」だが、21 片とも `assert` がない（出力を cases で比べているので検査は効いている）。ほかの cpp のページでも 0 本のもの（cpp-container-idioms・cpp-string-api）があり、ページ間でそろっていない
- **直し方**：このページでは必須にしない。run の片で値の主張が中心のもの（accumulate・unique-erase）に `assert` を 1〜2 行足すと手引きに沿う

## 判定

小さな直しで可。直すべき 2 件（指摘 1：`long long` にしても `max` はエラーのまま、指摘 2：図の矢印の向き）、直すとよい 6 件。事実の大半（版・GCC の対応・計算量・例の数値・エラー文・計測）は一次資料と手元のコンパイルで確かめられた。
