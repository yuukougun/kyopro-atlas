# cpp-integer-overflow の報告と提案

- 書いたファイル：docs/cpp/cpp-integer-overflow.md、snippets/cpp-integer-overflow/（22 組の .cpp と .yaml）、docs/img/cpp-integer-overflow/wrap-around.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21 のまま）、sections の signed-overflow-ub の title（下の「未解決の点」1）
- 検査の結果：check_pages エラー 0・警告 0、fix_problems --check 直す行 0、check_snippets 22 片・43 回のコンパイルで期待と違う 0、textlint エラー 0・警告 0
- 使った出典：en.cppreference.com（Arithmetic operators）、cpprefjp（ssize）、gcc.gnu.org（128-bit Integers・Integer-Overflow-Builtins・libstdc++ status）。新しいドメインはなし
- 取り込まないコード片：ub-check-o0（-O0 での結果）、int128-cin-ng、int128-strict-gnu、int128-printf-ng（本文の記述を確かめるため。手引き §13.9）
- 見出しの表記：`<…>` を含む 2 つの見出し（min-max-types・int128-strict-mode）は、`min<long long>` などが HTML のタグと解釈されないよう、その部分だけ見出しでバッククォートで囲んだ。front matter の title は変えていない

## 台帳への提案

- なし（catalog の方針どおり、C++ のページには問題を置かない）

## 用語集への提案

- オーバーフロー｜overflow｜整数の計算の結果が、その型で表せる範囲を超えること。C++ では符号付き整数のあふれは未定義動作、符号なし整数は 2^N を法として回り込む
- 符号なし整数｜unsigned-integer｜負の値を持たない整数型（unsigned・size_t など）。計算は 2^N を法として行われ、0 から 1 を引くと最大値になる

## 手引きへの提案

- 見出しに `<…>`（テンプレートの引数）を含む節の書き方を決めてほしい。Python-Markdown は `<long long>` を HTML のタグとして扱い、見出しから文字が消えうる（views-basics の「elements<N>」の見出しも同じ心配がある）。案：見出しではその部分をバッククォートで囲み、title とは「バッククォートを除いて一致」でよいとする
- 未定義動作の実例は、コード片の期待（run の出力）に手元の観測値を書いて確かめる形にした（int-product-ng・ub-check・shift など）。コンパイラの版が変わると期待と違いうるので、check_snippets で失敗したときは「観測値の変化」として扱う旨を手引きに書くとよい

## 問題の補充の候補

- なし（catalog の problems_note のとおり）

## 未解決の点

1. research/09 §4.35 の「`long long p1 = a * b;` があると、正しく書いた `p2 = 1LL * a * b`・`p3 = (long long)a * b` まで 1410065408 になる（-O2）」は、手元の g++-13・g++-15（-std=gnu++23 -O2）では再現しなかった（p2・p3 は正しく、p1 だけ誤った）。逆に、正しい行を先に置くと p1 が 10000000000 になる（あふれる行の値が別の行の有無で変わる）ことは観測した。本文では再現した別の例（int の積と long long の積を == で比べると、-O2 で違う値なのに same になる）を使い、節の title を「正しく書いた別の行の値まで変わる」から「正しく書いた比較の結果まで変わる」に直した。cpp-undefined-behavior の節 breaks-other-lines（「正しく書いた別の式の値まで変わる」）も同じ根拠なので、そのページの執筆時に見直してほしい
2. `println` が GCC 14 からという点は、手元に g++-14 がないので libstdc++ の状況表と research の記述によった（g++-13 で使えず g++-15 で使えることは確かめた）
3. INT_MIN / -1 と INT_MIN % -1 の異常終了（SIGFPE）は手元で確かめたが、異常終了するためコード片の期待（run）では確かめられず、snippets に置いていない
4. 計算量の「__int128 の積・割り算は long long の 2.5 倍以内」は手元の 1 回の計測（10^7 回、除数は 30 bit 程度）による目安である。除数が 64 bit を超える割り算ではもっと遅くなりうる
5. catalog の visual（priority 3 の動く図）は作らず、静的な SVG（int の値の輪と回り込み）で代えた
