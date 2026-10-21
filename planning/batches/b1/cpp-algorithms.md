# cpp-algorithms の報告と提案（工程8b・b1）

- 書いたファイル：docs/cpp/cpp-algorithms.md、snippets/cpp-algorithms/ の 21 本（取り込むもの：sort・unique-erase・lower-bound・accumulate・partial-sum・iota・next-permutation・max-element・min-ng・count-ng・ranges・projection・ranges-unique・fold-left・starts-with-ng・starts-with-ok・dangling-ng・dangling-ok。確かめるためだけに置いたもの：fold-left-cxx20-ng・projection-ng・ranges-unique-ng）、docs/img/cpp-algorithms/unique-erase.svg
- front matter で変えたもの：complexity・stage（draft）・cpp_std（20）・gcc_min（13）。updated は 2026-10-21 のまま。sections の title を 8 つ短くし、見出しと同じにした（anchor と level は変えていない）。短くしたのは unique-erase・lower-bound・accumulate・max-element・projection・ranges-unique・fold-left・ranges-dangling
- 検査の結果：check_pages（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、check_snippets（21 本・コンパイル 42 回・期待と違う 0）、textlint（エラー 0・警告 4）
  - 残した警告：70 行の sentence-length（図の代替テキストを textlint が 1 文と数える）、132 行の no-unmatched-pair（数式 $[l, r)$ の半開区間）、258 行の max-comma（数式 $(3, 2 \times 10^9, …)$ の中の読点）、282 行の sentence-length（コンパイラのエラー文をそのまま書いたコード）
- 動く図：作っていない。catalog の visual は priority 3 なので、unique → erase の静的な SVG で代えた。射影の図は作らず、文章と例（alice・bob・carol）で示した
- 使った出典：cpprefjp（unique・accumulate・reduce・inclusive_scan・next_permutation・ranges::unique・ranges::fold_left・dangling）、cppreference（partial_sum）、GCC の libstdc++ Implementation Status（fold_left・contains・find_last・ranges::iota が 13.1、starts_with・ends_with が 16.1 を本文の作業中に取得して確かめた）。新しく noai を確かめたドメインはない（どれも付録 B）
- 手元で確かめた事実：accumulate(…, 0) の -1294967296 と double で 0、partial_sum の int のあふれ（-294967296）、set への std::lower_bound・ranges::lower_bound が約 2.3 秒でメンバは 1 ms（g++-15・-O2・2×10^4）、ranges::starts_with が g++-13・g++-15 にないこと、fold_left などが -std=gnu++20 でエラーになること、dangling のエラー文

## 台帳への提案

- なし。catalog の problems は空で、problems_note（C++ のページは ABC の問題を置かない）に従った

## 用語集への提案

- 一時オブジェクト｜temporary-object｜関数の戻り値や式の途中の値のように、名前のない値。ふつうはその文の終わりで消えるので、中を指す参照やイテレータを文の後で使ってはいけない（cpp-range-for もこの anchor でリンクしている。まだ用語集にないので足してほしい）
- 狭義の弱順序｜strict-weak-ordering｜sort・set に渡す比較関数が満たすべき条件。comp(a, a) が偽で、推移的で、「どちらも小さくない」が同値関係になる。`<=` を返す比較はこれを破る（本文では sorting-techniques の節へリンクしたので、用語集は任意）

## 手引きへの提案

- cpp のページの `cpp_std` は、ページの中で最も新しい版か、主な書き方の版か決まっていない。cpp-views-basics（C++23 の string_view(w) を含むが 20）と cpp-types-literals（C++23 の 0uz を含むが 17）にならい、題名の ranges 版に合わせて 20 にした。C++23 の fold_left・ranges::iota を含むので 23 にする考え方もある。決めて §5 の cpp に書いてほしい
- 骨格の sections の title が長く、コードを含む（今回は見出しと同じにするため短くした）。cpp の骨格の title の長さの目安（例：60 字まで）があると迷わない

## 問題の補充の候補

- 探していない（C++ のページは問題を置かない方針のため）

## 未解決の点

- unique-erase.svg は描画して目で確かめる道具がなく、XML として読めることと座標の計算だけを確かめた。表示の確認を検証役に頼みたい
- 「ranges::max は最大が複数あるとき最初の要素を返す」は本文に書いていない（例は最大が 1 つ）。必要なら検証役に cpprefjp で確かめてもらいたい
- reduce の「足す順序が決まっていないので、浮動小数点数では結果がわずかに変わりうる」は cpprefjp の reduce の効果（順不同に集計）に基づく。手元では差の出る例を作っていない
- partial_sum のあふれは符号付き整数のあふれ（未定義動作）で、snippets の期待の出力 -294967296 は g++-13・g++-15 の -O2 で観測した値である。コンパイラの版が変わると出力が変わりうる
- cpp-container-idioms#member-lower-bound と内容が重なる（set の lower_bound）。本文では計測結果を 1 行にしてリンクした。計測値は cpp-container-idioms の計測（research の約 2 秒）とほぼ同じ

## 検証の指摘への対応（verify/cpp-algorithms.md）

- 指摘 1（直すべき）：196 行を「`max` に渡すなら `(int)` で型をそろえる。`long long` にしても `long` とは別の型でエラーのまま。代入だけなら `long long c = count(…);` でよい」に直した。count-ng.cpp のコメントも合わせた
- 指摘 2（直すべき）：unique-erase.svg の marker を x 軸の向きの三角形（`M0,0 L10,5 L0,10`、refX=9・refY=5、orient="auto"）にした
- 指摘 3：projection.cpp を `P best = ranges::max(…)` にし、本文を「score が最大の要素（のコピー）を返す。位置が要るなら `ranges::max_element`」とした
- 指摘 4：#ranges-dangling の 1 文目を「`vector` のような、要素を自分で持つコンテナの一時オブジェクト」に限定した
- 指摘 5：partial-sum.yaml から UB の case を外し、yaml にコメントで観測値を残した。本文は「手元の g++-13・g++-15（`-O2`）で」と添えた。確かめ用の片は増やしていない
- 指摘 6：「`3 1 2` 自身と、辞書順でその次の `3 2 1` の 2 通り」に直した
- 指摘 7：採らなかった（ページは変えない）。cpp_std・gcc_min を執筆者が埋めてよいか、cpp_std を主な書き方の版にするかはメインが §2.1・§5 で決める点なので、上の「手引きへの提案」と合わせて判断してほしい
- 指摘 8：accumulate.cpp（0LL の和が 3000000000）と unique-erase.cpp（erase の後に重複がない）に `assert` を 1 行ずつ足した
- 検査：check_pages（エラー 0・警告 0）、fix_problems --check（0）、check_snippets（21 片・42 回・違い 0）、textlint（エラー 0・警告 4。前と同じ誤検出）
