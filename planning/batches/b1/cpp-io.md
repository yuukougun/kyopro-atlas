# cpp-io の報告と提案（工程8b・b1）

- 書いたファイル：docs/cpp/cpp-io.md、snippets/cpp-io/ の 21 組（本文で取り込むもの：fast-io・separators・ternary-ng・read-until-eof・printf・printf-ng・println・format-13・format-index-ng・format-spec・float-output・mixing-streams・interactive・unprintable・tle-fixes。版と失敗例の確認だけのもの：println-13-ng・format-count-ng・scanf-warning・int128-cout-ng・modint-cout-ng・vector-println-13-ng）。図はなし
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21 のまま）。sections の title を 2 つ直した（§13.2 に従い見出しと同じ。anchor は変えていない）
  - fast-io：「約 0.15 秒の差」→「約 0.2 秒の差」（手元の g++-15 で 10^6 個の整数の入力が 0.21〜0.23 秒 → 0.03〜0.04 秒）
  - flush：「出力がパイプのときは cout << endl か fflush(stdout) が要る」→「cin.tie(nullptr) を書いたら、質問のたびに cout << endl か fflush(stdout) が要る」。パイプでつないで確かめると、同期を切る 2 行がなければ `'\n'` でも `println` でも届いた（cin.tie が読む前に cout を書き出し、同期した cout の flush が stdout も書き出すため）。届かないのは 2 行ありのときだけだった
- cpp_std・gcc_min は null のまま（版の混ざるページ）、atcoder は true のまま
- 検査の結果：check_pages（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、check_snippets snippets/cpp-io（21 件・コンパイル 35 回すべて期待どおり）、textlint（エラー 0・警告 6）
  - 残した警告：41 行（要点の「いつ使うか」の入れ子の箇条書きを 1 文と数える sentence-length）、137 行と 301 行（英語のエラーメッセージやコードを含む文の sentence-length）、64・131・289 行の no-doubled-joshi（文を分けると不自然になるため）
- 動く図：catalog の visual は dynamic・priority 3 なので作らず、置き場の div も置いていない。代わりに endl の節で「バッファに入れるだけ／毎回書き出す」を文章と計測の表で示した
- 使った出典：cpprefjp（sync_with_stdio・tie・println・format）、cppreference（format の spec・std::lower_bound）、GCC の libstdc++ Implementation Status（P0645 format 13.1、P2093 print 14.1、P2286 範囲の書式 15.1 で一部・15.2 で完全）。どれも付録 B のドメイン。新しく noai を確かめたドメインはない
- 計測と確認はすべて手元（WSL2、g++-13・g++-15、`-std=gnu++23 -O2`、出力はファイル）で行った。一時置き場は /tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/ff4dc6ee-16d4-486c-b97a-49fefbe7b218/scratchpad/w-cpp-io/

## 台帳への提案

なし（catalog のとおり problems を置かない C++ のページ）。

## 用語集への提案

- フラッシュ｜flush｜バッファにたまった出力を、すぐに書き出すこと。`cout << endl`・`cout << flush`・`fflush(stdout)` で行う。インタラクティブ問題では質問のたびに要る（本文の fast-io の節の最初の出現からリンク済み）
- バッファ｜buffer｜出力を一度ためておく場所。ためた分をまとめて書き出すので、1 個ずつ書き出すより速い（本文ではリンクしていない。足すなら cpp-io の endl の節からリンクできる）

## 手引きへの提案

- §9 の「改行は `'\n'`」に加え、雛形で `ios::sync_with_stdio(false); cin.tie(nullptr);` を書いたコード片では `printf`・`println` を混ぜない、と書き添えるとよい（コード片で `println` を使う執筆者が増えると、順番の入れ替わりを招く）
- 手元の Ubuntu の g++ は `-O2` で `_FORTIFY_SOURCE` が有効になり、`scanf` の戻り値を使わないと `-Wunused-result` の警告が出る（check_snippets の run は警告を誤りにする）。§9 に「`scanf` は戻り値を確かめるか、`cin` を使う」と書いておくと、ほかの執筆者が迷わない

## 問題の補充の候補

なし（catalog の problems_note のとおり、C++ のページは ABC の問題を置かず確認問題で確かめる）。

## 未解決の点

- research/09 §4.30 の「インタラクティブ問題で println と cout << '\n' だけでは届かない」は、同期を切る 2 行があるときの話だと判断した（2 行なしでは届いた）。cpp-reverse-index の「症状から引く」や interactive のページで同じ説明を書くときは、この条件をそろえてほしい
- research/09 §4.30 の println の速さ（2×10^6 行の整数と小数で println 0.20 秒・printf 0.31 秒・cout 0.42 秒）は再現できなかった。手元で 10^6 行の整数だけを測ると println 0.04 秒・printf 0.03 秒・cout（同期なし）0.02 秒で、本文にはこちらを書いた
- research/09 §4.38 の「set に std::lower_bound を 2×10^4 回で約 2 秒」は set の大きさが書かれていない。本文は要素 2×10^5 の set で測った約 22 秒（g++-13 で約 26 秒）を書いた
- 計測の値は手元の環境のもので、AtCoder とは違う。本文には「比の目安」と書いた
- AtCoder の GCC 15.2 で `scanf` の戻り値の警告が出るか（`_FORTIFY_SOURCE` が既定で有効か）は確かめていない。本文は「手元の Ubuntu の g++」と限定して書いた
- 引数なしの `println()` は cpprefjp で C++26 と確かめ、g++-15 の `-std=gnu++23` で通ることを確かめた。`-pedantic` を付けたときの扱いは確かめていない
- catalog の related に cpp-views-basics・cpp-lambda はないが、本文の tle-causes から節・ページへリンクした（views::iota の速さと再帰ラムダ）。related に足すかはメインで決めてほしい

## 検証の指摘への対応（verify/cpp-io.md）

- 指摘 1（直すべき）：#flush の落とし穴を、端末で 1 行ごとに書き出されるのは `println`・`printf`（`stdout`）だけ、同期を切った `cout` は端末でも溜める、と書き直した
- 指摘 2（直すべき）：`println("{}", x)` は指数の方が短ければ指数で出る（`1e+06`・`1e-04`）と書き直し、表に `x = 1000000` の列を足した（float-output.yaml に case を追加）。190 行の WA の理由は「桁が足りない」を主にし、指数の表記は「受け付けないジャッジもあるので避ける」に弱めた
- 指摘 3（直すとよい）：本文に「`println`・`printf` は `sync_with_stdio(false)` だけでも届かなくなる」の 1 文を足した。見出しと sections の title は変えていない（メインの判断。下の提案）
- 指摘 4（直すとよい）：interactive.cpp を `cout << ... << endl` だけにそろえた。`println` と `fflush(stdout)` の組は表と「直し方」の文で示す
- 指摘 5（直すとよい）：println.cpp の `println();` のコメントを「C++26 の形。g++-15 は gnu++23 でも通す」とした。手引きとの整合はメインの判断
- 指摘 6（直すとよい）：書式の並びに `0`（0 埋め）を入れ、埋める文字と符号は省いたと添えた
- 指摘 7（直すとよい）：落とし穴 2 で「フラッシュ（溜めた出力をすぐ書き出すこと）」と括弧で定義した
- 採らなかった指摘：なし

## メインへの提案（検証の後）

- #flush の見出しと sections の title を「インタラクティブ問題のフラッシュ：同期を切る 2 行を書いたら、質問のたびに cout << endl か fflush(stdout) が要る」に変える（anchor の flush はそのまま）。見出しと front matter の両方を同時に変える必要がある
- 手引き §9 の「C++26 は使わない」に、C++ の章で版を説明する例（引数なしの `println()`）に限って許す旨を足すか決める
