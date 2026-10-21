# cpp-views-cpp23 の報告と提案

- 書いたファイル：docs/cpp/cpp-views-cpp23.md、snippets/cpp-views-cpp23/（22 組の .cpp・.yaml）、docs/img/cpp-views-cpp23/views-gallery.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21 のまま）。sections は変えていない
- 検査の結果：check_pages エラー0・警告0、fix_problems --check 0 行、check_snippets 22 片・40 回コンパイルで期待と違う 0、textlint エラー0（警告 9：数式の中の読点・半開区間の `[`・エラー文やコードを含む文の長さ・参考の行・図の代替テキスト。誤検出として残した）
- 図：visual は static・priority 2。SVG を Python で生成した（手元に SVG を画像にする道具がなく、見た目は目で確かめていない。XML としては正しい）
- 使った出典：gcc.gnu.org の GCC 13・14・15 の変更点、en.cppreference.com（enumerate_view・chunk_by_view・ranges::to。/w/ の URL は /cpp/ に転送されるので転送先で書いた）、cpprefjp の C++23。新しいドメインはない

## 台帳への提案

- なし（C++ のページは問題を置かない。problems_note のとおり）

## 用語集への提案

- なし（番兵 #sentinel は用語集にある）。候補として「ベクトル化｜vectorization｜コンパイラが複数の要素をまとめて 1 つの命令で計算する最適化。-O2 でも単純なループには効く」を cartesian_product の速さの節で使った（リンクはしていない）

## 手引きへの提案

- §9 の「views を使うときは C++ の章へリンク」に、`views::cartesian_product` は二重 for より遅いことがある（手元 4×10^8 回で g++-13 約 4 倍、g++-15 約 12 倍）ので、重いループの snippets では普通の for を使う、と足すとよい
- cppreference の URL は /w/cpp/… が /cpp/… へ 301 で転送される。参考の URL の形をどちらにそろえるか決めるとよい（views の基本は /cpp/… で書いている）

## 問題の補充の候補

- なし（C++ の章は問題を置かない）

## 未解決の点

- `ranges::to` が GCC 14 からであることは GCC 14 の変更点で確かめた。手元に g++-14 がないので実機では確かめていない
- `views::stride`・`views::join_with` は GCC 13 の変更点の一覧に載っていないが、手元の g++-13（`-std=gnu++23`）で動いた。本文には「一覧にないが手元で使えた」と書いた（join_with のみ明記）
- 2 つの範囲の `views::zip` の要素型が g++-13 で `pair<int&, int&>`、g++-15 で `tuple<int&, int&>` と違う（P2165 の対応の差と思われるが、根拠の資料は読んでいない）
- cartesian_product が遅い理由は「ベクトル化が効かないため」と推測で書いた（-fno-tree-vectorize で普通の for が 40→80 ms になり、g++-13 の cartesian_product 160 ms・g++-15 の 610 ms には届かないので、ベクトル化以外の損もある）。本文は「と考えられる」とした
- 用語集・related の提案：cpp-structured-bindings の節 #enumerate-reference と内容が重なる。あちらを書くときは、このページの #reference-tuples へリンクして短くするとよい
- 使用量の目安：道具の呼び出し 約 35 回、Web 取得 6 回

## 検証の指摘への対応（planning/batches/b1/verify/cpp-views-cpp23.md）

- 指摘 1（直すべき）：直した。#int-index の「ほかの直し方」を `best` を `ptrdiff_t` にする、に替え、「`long long` にしても通らない」を落とし穴 1 として足した
- 指摘 2（直すべき）：直した。`to_string` をしているのは例の `views::transform` であると分かる書き方にした
- 指摘 3（直すとよい）：直した。比べる相手を `i < a.size() - 1` の符号なしの引き算にし、cpp-integer-overflow#unsigned-size へリンクした
- 指摘 4（直すとよい）：直した。`cartesian_product(iota(0, n), iota(0, n))` で添字を回した測り方を書いた（文の長さのため 2 文に分けた）
- 指摘 5（直すとよい）：直した。図の右側の注記を font-size 13 から 15 にした（見出しとの間隔は文字幅の見積もりで確かめた。画像にしての確認はしていない）
- 指摘 6（直すとよい）：#chunk-slide-stride の版に「`stride` は GCC 13 の一覧にないが手元の g++-13 で使えた」と添えた。cppreference の compiler support の表での裏付けは今回は取っていない
- 直した後の検査：check_pages エラー0・警告0、fix_problems --check 0 行、check_snippets 22 片・期待と違う 0、textlint エラー0（警告 10、誤検出または以前からのもの）
