# cpp-string-api の検証（工程8b・バッチ b1）

- 対象：docs/cpp/cpp-string-api.md、snippets/cpp-string-api/ の 14 片（.cpp と .yaml）。図はなし（catalog の visual は null）
- 観点：fact.md・code.md・clarity.md・figure.md
- 検証日：2026-10-21

## 実行した検査と環境

- コンパイラ：g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0、g++-13 (Ubuntu 13.4.0-6ubuntu1~22~ppa2) 13.4.0
- `python3 tools/check_pages.py --page cpp-string-api`：エラー 0・警告 0
- `python3 tools/check_snippets.py snippets/cpp-string-api`：14 片・コンパイル 28 回・期待と違う 0
- `npx textlint docs/cpp/cpp-string-api.md`：指摘なし
- 本文が引く警告・エラーの文面を両方のコンパイラで確かめた
    - find-ng（`-Wall -Wextra`）：`comparison of unsigned expression in '>= 0' is always true [-Wtype-limits]`。本文の文面と一致
    - contains-20-ng（`-std=gnu++20`）：`'std::string' ... has no member named 'contains'`。本文と一致
    - split.cpp を `-std=gnu++20` で：`no matching function for call to 'std::basic_string_view<char>::basic_string_view(std::ranges::subrange<...>&)'`。「`string_view(w)` は C++23」と一致
- 試しのプログラム（一時置き場 v-cpp-string-api/ の t1〜t4.cpp、g++-15 `-std=gnu++23 -O2`）で確かめたこと
    - `stoll("1000000000000000000")`（$10^{18}$、19 桁）と `stoll("9223372036854775807")`（19 桁）は読める。`stoll("9223372036854775808")` が初めて out_of_range（指摘 1）
    - `to_string(1e20)` = `100000000000000000000.000000`（整数部 21 桁）、`to_string(1e-7)` = `0.000000`、`stoi("  -7")` = -7、`stoi("ab")`・`stoi(" +")` は invalid_argument、`stoi("-2147483649")` は out_of_range
    - `"hello".substr(5)` は空、`substr(3, 100)` は `lo`、`substr(6)` は out_of_range
    - `t += 'a' + x`（x = 7）で `abch`、`string('a', 3)` は長さ 97・各文字のコード 3、`int p = s.find('z')` は -1、`string(sv)` で string に戻せる
    - 時間（$N = 2 \times 10^5$）：`s = s + c` 850〜914 ms、`s.insert(s.begin(), c)` 338〜350 ms、`s = c + s` 408〜414 ms、`s.find(t)`（本文の最悪の型）205〜249 ms（g++-15・g++-13）。執筆者の値と桁は合う（機械の違いで 1.5 倍程度の差）。$N = 10^6$ の `s = s + c` は 22.5 秒
    - 確認問題の `ans = ans + to_string(x) + " "`（$N = 2 \times 10^5$、6 桁の数）：40 秒。答えの「遅い」は正しい
    - string_view に一時的な string：両コンパイラとも `-Wall -Wextra` で警告なし。`-fsanitize=address` で長さ 100 は `heap-use-after-free`、長さ 3 は `stack-use-after-scope`。本文と一致
    - `cin.ignore()` の後の `getline`：`3 `（数の後に空白）と改行のとき、`ignore` は空白だけを捨て、`getline` は空の行を返す（指摘 5）
- 事実：cpprefjp の basic_string::find・to_string（`%f`、C++26 から `format("{}", val)`）・starts_with・contains・basic_string_view と、cppreference の std::getline（`cin >> n` の後に改行が残ること、`std::ws` で飛ばすこと）を読み、本文と食い違いなし。参考の 6 件の URL はどれも 200 で、題名・内容が書かれたとおり。atcoder.jp・codeforces.com は開いていない
- 問題：catalog の problems は空（C++ のページは問題を置かない方針）で、本文にも問題はない
- 図：なし。catalog の visual は null なので図の観点（G1〜G7）は対象外

## 指摘

### 1｜直すべき｜事実（F2・F3）｜#to-string 落とし穴 2、121 行「$10^{18}$ を超える 19 桁以上の数は `stoll` でも入らないので、文字列のまま扱う」

- **問題**：誤り。`long long` の最大は $2^{63} - 1 = 9223372036854775807$（約 $9.2 \times 10^{18}$、19 桁）なので、$10^{18}$ を超える数も 19 桁の数も、$9.2 \times 10^{18}$ までは `stoll` で読める。この文のとおりだと、$10^{18} < x \le 9.2 \times 10^{18}$ の入力（AtCoder でよくある $A_i \le 10^{18}$ の和や積の途中の値など）で、不要な多倍長の処理を書かせることになる
- **根拠**：手元で `stoll("9223372036854775807")` は読め、`stoll("9223372036854775808")` が初めて out_of_range になった
- **直し方**：「$2^{63} - 1$（約 $9.2 \times 10^{18}$）を超える数（20 桁以上は必ず超える）は `stoll` でも入らないので、文字列のまま扱う（`unsigned long long` の `stoull` なら約 $1.8 \times 10^{19}$ まで）」のようにする。`stoull` の括弧は無くてもよい

### 2｜直すとよい｜リンク（F6・U6）｜#to-string 落とし穴 1・#string-view 落とし穴 2・#construct-compare 本文（執筆者の未解決の点）

- **問題**：執筆時は stub だった cpp-io・cpp-undefined-behavior・string-basics が、いまは draft になって目当ての節がある。ページへのリンクのままだと、読者は長いページの中を探すことになる
- **根拠**：docs/cpp/cpp-io.md の sections に `float-output`・`tle-causes`（`s = s + c` の計測を含む）、docs/cpp/cpp-undefined-behavior.md に `dangling-string-view`、docs/string/string-basics.md に `lexicographic-order` がある
- **直し方**：120 行の `cpp-io.md` を `cpp-io.md#float-output` に、164 行の `cpp-undefined-behavior.md` を `cpp-undefined-behavior.md#dangling-string-view` に（158 行の落とし穴 1 から張ってもよい）、137 行の `string-basics.md` を `string-basics.md#lexicographic-order` に直す。#append の表の後に「C++ 側で TLE になる書き方の一覧は[入出力と定数倍](../cpp/cpp-io.md#tle-causes)」を足してもよい。リンク先の anchor は、メインが反映するときにそのページがまだ同じ anchor を持つことを確かめる

### 3｜直すとよい｜事実（F3）・分かりやすさ（U2）｜導入 44 行「$N = 2 \times 10^5$ で TLE になったり」と #append の表

- **問題**：表の `s = s + c` は $N = 2 \times 10^5$ で 0.56〜0.6 秒（検証の手元では 0.85〜0.91 秒）で、制限時間 2 秒の問題ならこれだけでは TLE にならない。導入は「$2 \times 10^5$ で TLE」と書き、表は 1 秒未満を示すので、読者が「$2 \times 10^5$ なら `s = s + c` でも間に合う」と受け取るおそれがある。$O(N^2)$ は $N$ が増えると急に悪くなるので、その点が表から読み取れない
- **根拠**：手元で $N = 10^6$ は 22.5 秒。確認問題の型（1 回に 7 文字ずつ足す）は $N = 2 \times 10^5$ で 40 秒。string-basics の検証（指摘 1）でも同じ傾向（$5 \times 10^5$ で 4.3 秒）が出ている
- **直し方**：表の後に「$N = 2 \times 10^5$ ではメモリのコピーが速く 1 秒を切るが、$N$ が 5 倍になると時間は 25 倍になり、$10^6$ では 20 秒を超えた。1 回に何文字も足す（確認問題の形）と $2 \times 10^5$ でも数十秒かかる」のように 1〜2 文足す。導入の「$N = 2 \times 10^5$ で TLE」は「$N$ が大きいと TLE」にするか、確認問題の形を例にする

### 4｜直すとよい｜分かりやすさ（U9・U5）｜#char-arithmetic 落とし穴 2、109 行末「数字の文字列を `stoi` で数に直すのは、1 文字ずつなら `c - '0'` で足りる」

- **問題**：大文字と小文字の話の落とし穴の中に、別の話題が 1 文だけ入っている。「`stoi` で直すのは…で足りる」の主語と述語がかみ合わず、「1 文字を数に直すのに `stoi` は要らない」のか「`stoi` は 1 文字ずつ使う」のか読み取りにくい
- **根拠**：読者の立場で読み、文の意味が 2 通りに取れた
- **直し方**：この文を消すか、独立の 1 行にして「1 文字の数字を数にするなら `stoi(string(1, c))` ではなく `c - '0'` でよい」と書く

### 5｜直すとよい｜事実（F2）｜#getline 落とし穴 1、199 行「`cin.ignore()` で改行を 1 文字だけ捨ててから `getline` を呼ぶ」

- **問題**：`cin.ignore()` は次の 1 文字を捨てるだけなので、数の後に空白がある（行末の空白）と、改行が残って `getline` は空の行を返す。「改行を 1 文字だけ捨てる」と書くと、どんな場合も改行が捨てられると読める
- **根拠**：手元で入力 `3 \nhello` に対し `>> n`・`ignore()`・`getline` の順で読むと、`line` は空だった
- **直し方**：「行末の改行だけを捨てるなら `cin.ignore(numeric_limits<streamsize>::max(), '\n')`（改行まで読み捨てる）を使う」とするか、「`cin.ignore()` は 1 文字だけ捨てるので、数のすぐ後が改行であることを前提にする」と条件を書く。AtCoder の入力は行末に空白がないので、後者の短い注記で足りる

### 6｜直すとよい｜コード（C2）・手引き §9｜snippets/cpp-string-api/ の各片

- **問題**：手引き §9 は「プログラムは `main` と `assert` を持つ完全なもの」とするが、14 片のどれにも `assert` がない。cases の出力の比較で確かめてはいるので、誤りではない
- **根拠**：`grep assert snippets/cpp-string-api/*.cpp` が 0 件
- **直し方**：string-view.cpp の `count_prefix` のように中心の関数があるものは、素朴な方法（`substr` と比較の繰り返し）と `assert` で比べる行を main に足すとよい。出力を見せるだけの片（char-print・to-string など）はこのままでよい。手引きの「`assert` を持つ」を C++ の章でどう扱うかはメインの判断に任せる

## 確かめて問題がなかった主な点

- 計算量：要点・front matter の `complexity`・本文の 3 か所が一致（`s += c` ならし $O(1)$、`s = s + c` $O(\lvert s \rvert)$、`substr` $O(len)$、比較 $O(\min)$、`string_view::substr` $O(1)$）。find の計算量が規格で決まっていないこと（cpprefjp）、libstdc++ で最悪 $O(\lvert s \rvert \lvert t \rvert)$ になることは計測と合う
- 版：`starts_with`・`ends_with` が C++20、`contains`・`string_view` の範囲コンストラクタが C++23、`string_view` が C++17。to_string の C++26 の変更（cpprefjp に `format("{}", val)`）
- コード片の取り込み：本文の `--8<--` の 14 か所と印の名前が一致。取り込みは要点の数行。`#include`・`main` は見せていない。`'\n'`・マクロなし・views には cpp-views-basics へのリンクあり
- 確認問題 3 問（`ans = ans + ...`・string_view を返す関数・`t += 'a' + x`）と章末の 2 問は、本文から答えが出て、理由まで書かれている
- 断片で読んで通じるか：各節は節名の操作から書き始め、「上の」「前述の」に頼っていない。#starts-with の「[落とし穴 3](#substr-find)」はリンクで飛べる

## 総合の判定

小さな直しで可。直すべきは 1 件（`stoll` の範囲の誤り）。直すとよいは 5 件。
