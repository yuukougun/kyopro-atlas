# cpp-string-api の報告（工程8b・バッチ b1）

- 書いたファイル：docs/cpp/cpp-string-api.md、snippets/cpp-string-api/{substr-find,find-ng,append,char-arithmetic,char-print,to-string,starts-with,contains-20-ng,construct-compare,string-view,string-view-ng,split,getline-ng,getline}.{cpp,yaml}。図はなし（catalog の visual は null）
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21 のまま）。sections は変えていない
- 検査の結果：check_pages（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、check_snippets（14 片・g++-13 と g++-15 で 28 回・期待と違う 0）、textlint（エラー 0・警告 0）
- find-ng は warning（`-Wtype-limits`）、contains-20-ng は `-std=gnu++20` で compile-error、string-view-ng は未定義動作の関数を main から呼ばない形で run（コンパイルが通ることだけを確かめる）。ASan の結果は手元で別に確かめた（下記）
- 問題：catalog の problems は空（problems_note「C++ のページは ABC の問題を置かず、本文の確認問題で確かめる」）なので、問題の囲みは置いていない

## 使った出典

- cpprefjp（付録 B）：basic_string::find（npos、計算量の規定がない）、to_string（`%f`、C++26 で std::format に基づく形）、starts_with・contains・basic_string_view の各ページ
- en.cppreference.com（付録 B）：std::getline（`/cpp/...` の URL。`/w/cpp/...` は 301 で移っていた）
- 新しく noai を確かめたドメイン：なし
- 手元で確かめた事実（g++-13・g++-15、-std=gnu++23）：
  - 2×10^5 回の 1 文字追加（-O2）：`s += c` 0 ms、`s = s + c` 560/600 ms、`s = c + s` 566/578 ms、`s.insert(s.begin(), c)` 255/253 ms（g++-15/g++-13）
  - `s.find(t)`（s は a が 2×10^5 個、t は a が 10^5 個と b）：1 回で 360 ms（g++-15）・467 ms（g++-13）
  - `string_view sv = make(100);`（一時的な string）：-Wall -Wextra で警告なし、ASan で heap-use-after-free。短い文字列（SSO）では stack-use-after-scope
  - `s.find(t) >= 0` に -Wtype-limits の警告。`int p = s.find('z')` は -1
  - `to_string(3.14)` = 3.140000、`to_string(1e-7)` = 0.000000、`to_string(1e20)` = 100000000000000000000.000000、`stoi("12ab")` = 12、`stoi("  -7")` = -7、`stoi("3000000000")` は out_of_range、`stoi("ab")` は invalid_argument
  - `"hello".substr(5)` は空、`substr(6)` は out_of_range、`substr(3, 100)` は lo
  - `t += 'a' + 7` は警告なしで 'h' を足す。`string('a', 3)` は長さ 97 で各文字のコードが 3

## 台帳への提案

- なし（このページは問題を置かない）

## 用語集への提案

- なし（本文で用語集へのリンクは使っていない）
- 候補として検討してほしいもの：SSO（短い文字列の最適化）｜sso｜短い文字列を、ヒープではなく string のオブジェクトの中に置く実装の工夫。短い string を参照する string_view が壊れたときに、ASan の報告が stack-use-after-scope になる理由。本文では語を出していないので、足さなくてもよい

## 手引きへの提案

- §11 の参考の例に cppreference の URL の形を書いておくとよい。`https://en.cppreference.com/w/cpp/...` は 301 で `https://en.cppreference.com/cpp/...` に移っている（見本の cpp-views-basics も後者）
- C++ の章で「未定義動作を起こす実例」の snippets は、実行すると不定の結果になるので、関数に入れて main から呼ばない形（expect: run でコンパイルだけを確かめる）にした。check_snippets に「compile-only」の期待を足すか、この形を手引き §9 に書いておくとよい

## 問題の補充の候補

- なし（catalog の方針で問題を置かない）。もし置くなら、string-basics の例題・練習（台帳の確認済みのもの）を本文の参照にとどめるのがよい

## 未解決の点

- cpp-undefined-behavior（#dangling・#dangling-string-view）・cpp-io（#float-output・#separators）・string-basics（#lexicographic-order）は stub なので、節ではなくページへリンクした。draft になったら、string_view の落とし穴を cpp-undefined-behavior#dangling-string-view、to_string の落とし穴を cpp-io#float-output、辞書順を string-basics#lexicographic-order へ直すとよい
- `find` の計算量の記述は libstdc++ の実装と手元の計測に基づく（規格は規定しない）。「最悪 O(|s||t|)」は libstdc++ の素朴な照合を前提にしている
- C++26 の to_string(double) の書式の変更は、cpprefjp の記述（std::format の `{}` に基づく）だけで確かめた。具体的な出力は確かめていない（AtCoder の gnu++23 には関係しない）
- catalog の sources の 08-string-geo §4.1 の「比較 O(min(|s|,|t|))」は本文の比較の節と complexity に使った

## 使用量の目安

- 道具の呼び出し 約 22 回、Web 取得 2 回（cpprefjp）＋URL の確認に curl 5 回

## 検証の指摘への対応（2026-10-21）

- 指摘 1（直すべき）：stoll の範囲を「$2^{63} - 1$（約 $9.2 \times 10^{18}$）を超える数（20 桁以上は必ず超える）」に直し、stoull の範囲を足した
- 指摘 2：to_string の落とし穴 1 を cpp-io#float-output、辞書順を string-basics#lexicographic-order、string_view の落とし穴 2 を cpp-undefined-behavior#dangling-string-view へ張り替えた。#append の表の後に cpp-io#tle-causes へのリンクを足した（3 つの anchor は現時点で各ページにあることを確かめた。メインは反映時に再確認してほしい）
- 指摘 3：導入を「$N$ が大きいと TLE」にし、#append の表の後に $N = 10^6$ で 20 秒超・確認問題の形で数十秒になることを足した
- 指摘 4：stoi の 1 文を落とし穴 2 から外し、独立の「使い分け」の 1 行にした
- 指摘 5：cin.ignore() は次の 1 文字を捨てるだけで、数のすぐ後が改行であることを前提にする旨と、AtCoder ではその前提を満たすことを書いた
- 指摘 6：string-view.cpp の main に、素朴な方法（substr と比較の繰り返し）との assert を足した。出力を見せるだけの片は採らなかった（検証の指摘どおり、出力の比較で確かめており assert で比べる相手がないため）。C++ の章で手引き §9 の「assert を持つ」をどう扱うかはメインの判断に任せる
