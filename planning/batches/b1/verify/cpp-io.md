# cpp-io の検証（工程8b・バッチ b1）

- 対象：docs/cpp/cpp-io.md、snippets/cpp-io/ の 21 組。図はない（catalog の visual は dynamic・priority 3 で、作らないのは規則どおり）
- 観点：fact.md・code.md・clarity.md・figure.md
- 検証日：2026-10-21
- 一時置き場：/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/ff4dc6ee-16d4-486c-b97a-49fefbe7b218/scratchpad/v-cpp-io/

## 実行した検査と環境

- `python3 tools/check_pages.py --page cpp-io`：エラー 0・警告 0
- `python3 tools/check_snippets.py -v snippets/cpp-io`：21 片・35 回のコンパイルで期待と違うもの 0（g++-13 (Ubuntu 13.4.0-6ubuntu1~22~ppa2) 13.4.0、g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0）
- 本文に書かれたコンパイラの文面を g++-13・g++-15 の `-std=gnu++23 -O2 -Wall -Wextra` で確かめた。どれも本文どおり
    - ternary-ng：`second operand of conditional expression has no effect`（`-Wall` なしでは出ない。本文の「`-Wall` で」と合う）
    - printf-ng：`format '%d' expects argument of type 'int', but argument 2 has type 'long long int'`
    - scanf-warning：`ignoring return value of 'int scanf(const char*, ...)'`（`-O0` では出ない）
    - int128-cout-ng：`ambiguous overload for 'operator<<'`、modint-cout-ng：`no match for 'operator<<'`
    - println-13-ng（g++-13）：`'println' was not declared in this scope`
    - format-count-ng・format-index-ng・vector-println-13-ng：g++-13 でコンパイルエラー
- 試しのプログラムで確かめたこと
    - 引数なしの `println()`：g++-15 の `-std=gnu++23` に加え、`-std=c++23 -pedantic` でも警告なしで通る（執筆者の未解決の点 6 は解決）
    - `__int128` を `format` で出す：g++-13 の `-std=gnu++20`・`-std=c++20` のどちらでも 10 進で出る
    - `println("{:n}", vector{1,2,3})` は `1, 2, 3`（本文どおり）。`setprecision(15)` だけだと `1e18/3` は `3.33333333333333e+17`（落とし穴 1 どおり）
    - `println("{}", x)` の出力：`1e-07`・`1e-04`（0.0001）・`1.5e-05`・`1e+15`・`1e+16`・`1e+06`（1000000.0）・`1e+05`（100000.0）・`100`・`0.001`（指摘 2 の根拠）
- 計測（手元 WSL2、g++-15 `-O2`、入出力はファイル）：本文の値とおおむね一致
    - 10^6 個の入力の和：2 行なし 0.25 秒、2 行あり 0.05 秒。1 個読むごとに 1 行出す：`sync_with_stdio(false)` だけ 0.42 秒、2 行あり 0.06 秒
    - 10^6 行の出力：`'\n'` 0.03〜0.04 秒、`endl` 0.36 秒（同期の有無によらない）
    - `std::function` の fib(35) 40 ms・`auto&& self` 9 ms。`s = s + c` 2×10^5 回 634 ms・`+=` 0.2 ms。長さ 2×10^5 の vector の値渡し 10^4 回 172〜185 ms・参照 0.01 ms 未満
    - set への `std::lower_bound`：要素 2×10^4・2×10^4 回で 2.5 秒、要素 2×10^5・2×10^3 回で 3.7 秒（2×10^4 回なら 37 秒ほどの見込み）。本文の約 22 秒とは環境の差の範囲で、次数が変わる例としての主張は正しい。research の「約 2 秒」は要素 2×10^4 程度の set の値と考えると合う（執筆者の未解決の点 3）
- インタラクティブの表（#flush）：名前付きパイプで、質問を 1 行読んで答えを返す相手（Python）とつなぎ、3 秒で打ち切って確かめた。8 マスすべて本文の表どおり（執筆者の未解決の点 1 は確認済み）。加えて、`sync_with_stdio(false)` だけ（`cin.tie` はそのまま）では `'\n'` は届き `println` は届かず、`cin.tie(nullptr)` だけでは両方届かなかった（指摘 3 の根拠）
- 端末での動き：`script -qc` で疑似端末につなぎ、質問の後に `write(2, …)` で目印を出して順番を見た。2 行ありで `cout << "? 21\n"` は入力を読んだ後（プログラムの終わり）まで画面に出ず、`println("? 21")` はすぐ出た（指摘 1 の根拠）。`cerr` は `cout` に tie されているので、目印に `cerr` を使うと `cout` が書き出されて誤った結果になる点に注意した
- 参考の URL：7 つすべて 200 を返す。cpprefjp の println に引数なしの形（`void println(); // (2) C++26`）と、`println(stdout, …)` と等しいことがある。GCC の Implementation Status に P0645R10 が 13.1、P2093R14 が 14.1、P2286R8 が「15.1 (changes to adaptors missing) 15.2 (complete)」とある。atcoder.jp・codeforces.com の URL はない
- 本文中のリンク先の anchor（cpp-types-literals#floating-point・cpp-integer-overflow#int128-io・cpp-views-basics#iota・complexity-estimation#constant-factor）はすべて存在する。glossary#flush はまだないが、手引き（style-guide.md 219 行の「用語集へのリンク」）のとおり提案済みなので問題ない
- textlint は執筆者の結果（エラー 0・警告 6）をそのまま認めた

## 指摘

### 1｜直すべき｜事実（F2）・分かりやすさ（U2）｜#flush の「落とし穴」（243 行）

- **問題**：「手元でキーボードから入力して試すと、端末への出力は 1 行ごとに書き出されるので、フラッシュを忘れても動いて見える」は、同期を切った `cout` には当てはまらない。1 行ごとに書き出されるのは C の `stdout`（`println`・`printf`）だけで、`sync_with_stdio(false)` の後の `cout` は自前のバッファに溜め、端末でも改行で書き出さない。雛形の 2 行と `cout << … << '\n'` の組み合わせ（この節と確認問題 1 が扱う典型）では、手元でも質問が画面に出ず、プログラムの終わりにまとめて出る
- **根拠**：上の「端末での動き」。疑似端末で、2 行ありの `cout << "? 21\n"` は入力を読んだ後に出て、`println("? 21")` はすぐ出た
- **直し方**：対象を限る。例「`println`・`printf` は、端末へ出すときは 1 行ごとに書き出される。手元でキーボードから試すとフラッシュを忘れても動いて見え、提出して初めて TLE になる。同期を切った `cout` は端末でも溜めるので、質問が画面に出ないことで気づける」

### 2｜直すべき｜事実（F2・F3）｜#float-output の `println("{}", x)` の説明（205 行）と 190 行

- **問題**：「`println("{}", x)`：元の値に戻せる最短の表記で、誤差の問題ならそのまま正解になることが多い。ただし $10^{18}$ は `1e+18` のように指数の表記になる」は、指数の表記になる範囲を大きく狭く書いている。最短の表記は、指数の表記の方が短ければ小さな値でも普通の大きさの値でも指数の表記を選ぶ。`1000000.0` は `1e+06`、`100000.0` は `1e+05`、`0.0001` は `1e-04`、`1.5e-05` もそのまま指数で出る。答えが $10^5$ ちょうどや $10^{-4}$ のような値は珍しくなく、「大きさが分からないなら」ではなく、ほぼいつも `{:.15f}` が要る。また 190 行の「指数の表記もそのまま WA になる」は、ジャッジが指数の表記を受け付けるかを確かめた根拠が本文・報告にない（atcoder.jp を開けないので、ここでも確かめていない）
- **根拠**：上の試しのプログラムの出力（`1e+06`・`1e+05`・`1e-04`・`1.5e-05`）。float-output.yaml の 1e18 の case も `1e+18`
- **直し方**：205 行を「元の値に戻せる最短の表記で、指数の方が短ければ指数で出る（`1000000.0` が `1e+06`、`0.0001` が `1e-04`）。小数の答えは `{:.15f}` で出す」のように直し、表に `x = 1000000` などの行を足すとよい。190 行の WA の理由は「桁が足りない」を主にし、指数の表記は「受け付けないジャッジもあるので避ける」程度に弱めるか、根拠を確かめてから書く

### 3｜直すとよい｜事実（F2）｜#flush の見出しと sections の title、確認問題 1

- **問題**：見出しは「cin.tie(nullptr) を書いたら、質問のたびに … が要る」と、原因を `cin.tie(nullptr)` だけに置く。実際は `println`・`printf` で質問する場合、`sync_with_stdio(false)` だけで（`cin.tie` を残しても）届かなくなる。同期を切ると `cout` のフラッシュが `stdout` を書き出さなくなるからで、240 行の説明とも合う。見出しだけを引いた読者は「`cin.tie` を書かなければ `println` で大丈夫」と取りうる
- **根拠**：上の「インタラクティブの表」の追加の試し（sync だけ：`'\n'` は届く・`println` は届かない）
- **直し方**：見出し（と sections の title。anchor は変えない）を「同期を切る 2 行を書いたら、質問のたびに cout << endl か fflush(stdout) が要る」とするか、本文に「`println`・`printf` は `sync_with_stdio(false)` だけでも届かなくなる」の 1 文を足す。見出しの変更は sections の title に関わるのでメインの判断とする

### 4｜直すとよい｜コード（C3）・分かりやすさ（U3）｜snippets/cpp-io/interactive.cpp（#flush で取り込み）

- **問題**：同期を切る 2 行のある雛形で `cout << … << endl` と `println` を混ぜている。`endl` で `cout` を書き出した後なので順番は崩れず結果は正しいが、同じページの #fast-io の落とし穴 1・#mixing-streams の「雛形に同期を切る 2 行があるなら、`printf`・`println` を使わないと決めておく」と食い違い、なぜここだけ混ぜてよいのかの説明がない。コード片はそのまま写されやすい
- **根拠**：本文 70 行・221 行と interactive.cpp の 8〜12 行
- **直し方**：`cout` だけの書き方（`cout << "? 21" << endl; … cout << "! " << r << endl;`）にそろえ、`println` と `fflush(stdout)` の組は表と「直し方」の文で示す。混ぜたまま残すなら、「`endl` で書き出し済みなので入れ替わらない」とコメントを足す

### 5｜直すとよい｜コード（C5）｜snippets/cpp-io/println.cpp の `println();`（#format-println で取り込み）

- **問題**：手引き §9 は「C++26 は使わない」とし、code.md C5 も「C++26 の機能を使う」を失敗に挙げる。引数なしの `println()` は C++26（cpprefjp）。本文は C++26 と明記し、catalog の見出しも「引数なしの println() も通る」を扱うので意図した例外と読めるが、コード片の中で区別されていない
- **根拠**：cpprefjp println の `void println(); // (2) C++26`。g++-15 は `-std=c++23 -pedantic` でも警告なしで通す
- **直し方**：コード片のコメントを「改行だけ（C++26 の形。g++-15 は gnu++23 でも通す）」とする。手引きとの整合は、C++ の章で版を説明する例に限って許すかをメインで決める

### 6｜直すとよい｜事実（F7）・分かりやすさ（U3）｜#format-spec の 167 行

- **問題**：「並びは『寄せ方・幅・`.` 桁数・種類』で、どれも省略できる」とあるが、直後の表の `{:05}`・`{:08b}` の `0`（0 埋めの指定）はこの並びのどこにも入らない。読者は `0` を幅の一部と取るか、寄せ方の位置に書くものと取りうる（実際の並びは「埋める文字と寄せ方・符号・`#`・`0`・幅・`.` 桁数・種類」）
- **根拠**：cppreference「Standard format specification」の fill-and-align / sign / # / 0 / width / precision / type
- **直し方**：「寄せ方・`0`（0 埋め）・幅・`.` 桁数・種類」とし、埋める文字（`{:*>5}`）や符号は省いたと一言添える

### 7｜直すとよい｜分かりやすさ（U6・U3）｜#fast-io の落とし穴 2（71 行）

- **問題**：ページで最初に「フラッシュ」が出るのはこの節で、意味の説明は次の #endl の節にある。用語集へのリンクはあるが用語集の項目はまだ提案の段階で、節だけを読むと「読む前の自動の書き出し」と「フラッシュ」が同じものだと分かりにくい
- **直し方**：「自分で[フラッシュ](…)（溜めた出力をすぐ書き出すこと）する」と括弧で短く定義する

## 執筆者の未解決の点への答え

1. インタラクティブの条件：パイプで確かめ、本文の表どおり。ただし `println` は `sync_with_stdio(false)` だけでも届かない（指摘 3）。cpp-reverse-index・interactive のページでは「同期を切る 2 行があるとき」でそろえるのがよい
2. println の速さ：手元の値をそのまま採ったのは妥当（本文は「どれも十分に速い」の主張にとどまる）
3. set への `std::lower_bound`：要素 2×10^4 の set なら約 2.5 秒で research の値と合う。本文の 22 秒（要素 2×10^5）も次数の主張として正しい
4. 計測は環境の値：本文の「比の目安」の断りで足りる
5. AtCoder の `scanf` の警告：ここでも確かめていない。本文の「手元の Ubuntu の g++」の限定で足りる
6. `println()` と `-pedantic`：`-std=c++23 -pedantic` でも警告なしで通る
7. related に cpp-views-basics・cpp-lambda を足すか：メインの判断。本文のリンクは正しい先を指している

## 総合の判定

小さな直しで可。直すべき指摘は 2 件（指摘 1：端末で 1 行ごとに書き出されるのは `stdout` だけ、指摘 2：`println("{}")` が指数で出る範囲）。どちらも数文の書き換えで済む。コード片はすべてコンパイル・実行とも期待どおりで、本文の計測・コンパイラの文面・インタラクティブの表は再現できた。
