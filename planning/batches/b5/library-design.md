# library-design の報告（b5）

- 書いたファイル：docs/guide/library-design.md、snippets/library-design/fenwick-tests.{cpp,yaml}・verify-test.{cpp,yaml}、docs/img/library-design/workflow.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-22）。sections は変えていない
- 検査：check_pages エラー 0・警告 0、fix_problems --check 0 行、check_snippets 2 件とも期待どおり、textlint エラー 0（警告 4：図の代替テキスト 1・practice2 の箇条書き 1（122 字）・確認問題の題 2。どれも手引き §14-25 の許容の範囲）
- 図：workflow.svg（400×380）を render_svg.py で 360・720 幅にして目で確かめた
- 生成ブロック verify-table の中は触れていない。前置き（読み方）を外側に書いた

## 台帳への提案

- なし（catalog の problems は空。guide のページなので問題の囲みは置いていない）

## 用語集への提案

- 動作確認（verify）｜verify｜自作のライブラリを、テストケースのそろった問題（Library Checker など）に提出して正しさと速さを確かめること。oj-verify などの道具で自動にできる
- バンドル（展開）｜bundling｜自作のヘッダを `#include "..."` で読む解答を、提出用にヘッダの中身で置き換えた 1 ファイルにすること（持ち主は cpp-macros-template-file#bundling）
- 本文ではどちらも用語集へリンクしていない（§15-1）

## 手引きへの提案

- §9 のコード片の規則に「ライブラリの形のコード片（ヘッダに置く想定の部分）は名前空間に入れ、中では `std::` を付ける」例外を書いておくとよい。library-design の snippets は `namespace mylib` の中で `std::vector` と書き、`main` の側は `using namespace std;` にした
- `#pragma once` を main のファイルに書くと GCC が警告を出すので、ヘッダの形はコード片に入れられない。ヘッダの先頭は本文の文章で説明した。同じ悩みのページがあれば、この扱いを手引きに足すとよい

## 問題の補充の候補

- AAL Contest 001（aalc001、2026-10-12、24 問。ap.py で実在と題名を確認。difficulty なし）：A. Segment Tree・B. Lazy Segment Tree・C. Binary Search on a Segment Tree・D. Inversion Count など、セグ木の型ごとの問題集。自作のセグ木の動作確認先として本文に入れたいが、第三者の解説で各問の内容を確かめられていないので本文には書いていない（research/05-ds §7.5 も未確認）。problem-sets に aalc001 の節ができたら、library-design#verify から案内する案
- practice2（A〜L の 12 問、ap.py で題名を確認）：本文は problem-sets のページへのリンクだけにした。problem-sets#problem-sets-practice2 の anchor は生成ブロックにあるが、ページが stub なので §14-23 に従いページへのリンクにした。problem-sets が draft になったら節へ張り替える。catalog の related の problem-sets#verify-sets も同じ

## 未解決の点

- related の stress-testing・problem-sets は stub なのでページへのリンクにした（draft になったらメインが節へ張り替える）
- Library Checker の C++ の提出環境に ACL が入っているかは確かめていない。本文では「ACL のないジャッジでは expander.py で展開」とだけ書いた
- Library Checker の問題数（14 分類・235 問、Sample 3 問を含む）は 2026-10-22 の categories.toml を手元で数えた値（§15-11 の「手元で数えた値」にあたるので日付を添えた）
- competitive-verifier のドキュメントは GitHub Pages の document.ja.html を WebFetch の要約で読んだ。属性の名前（PROBLEM）と `#define` の非推奨は要約に出た内容で、原文の行は見ていない
- 新しく noai を確かめたドメイン：competitive-verifier.github.io・online-judge-tools.github.io（どちらも指定なし）。付録 B への追加を提案する。raw.githubusercontent.com は github.com の生の配信として categories.toml・README・task.md・info.toml の取得に使った（check_noai は通していない）
- 「何を自作するか」の段階の表は目安として書いた（研究資料に優先度の一次資料はない）。メインの判断で並びを直してよい

## 検証の指摘への対応（b5 verify）

- 直すべき 0・直すとよい 12。12 件すべて直した
  - 1：数は categories.toml の一覧に載る問題のものと書き、一覧に載らない問題もあると足した
  - 2：header の範囲に `// #pragma once`（コメント）と `<cassert>`・`<vector>` の include を入れ、本文にも 1 文足した
  - 3：「上の段から順に」に直し、表を合図と結び付ける文を足した
  - 4：代表元（`leader(v) == v`）の size の合計にした
  - 5：「おもに」を足した
  - 6：stress のコード片を `iter < 5000` にした（要点・complexity の「数千回」に合わせた）
  - 7：oj-bundle の扱い（1 行目の `#pragma once`、ガードの外の行と 2 行目以降の `#pragma once` はエラー）を具体的に書いた
  - 8・9：参考に cplusplus_bundle.py と library-checker-judge の langs.toml を足し、#bundling に「Library Checker の C++ にも ACL が入っている」を足した
  - 10：verify-test の head に `// #include "../lib/fenwick_tree.hpp"` のコメント行を入れ、本文に 1 文足した
  - 11：@impl の行を箇条から外して段落にした
  - 12：図の②③の破線・太線をやめ、①〜③を同じ実線にそろえた
- メインへの補足にあったリンクの張り替え（本文の 2 か所）は済ませた：stress-testing#procedure、problem-sets#problem-sets-practice2。front matter の related（stress-testing・problem-sets#verify-sets）は変えていない。related の stress-testing を stress-testing#procedure にするかはメインの判断に任せる
- 提案（メイン向け）：生成ブロックの表の 6 問（aho_corasick・minimum_enclosing_circle・minimum_steiner_tree・range_add_range_min・static_range_sum_with_upper_bound・sum_of_multiplicative_function）は categories.toml にない。judge.yosupo.jp で開けるかを確かめるとよい（各ページの verify の持ち主の担当）
- textlint：エラー 0・警告 4（図の代替テキスト・practice2 の行・確認問題の題 2。指摘の前と同じ）
