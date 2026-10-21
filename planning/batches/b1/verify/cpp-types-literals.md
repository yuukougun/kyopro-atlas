# cpp-types-literals の検証（工程8b・バッチ b1）

- 対象：docs/cpp/cpp-types-literals.md、snippets/cpp-types-literals/ の 15 組、docs/img/cpp-types-literals/ranges.svg
- 観点：fact.md・code.md・clarity.md・figure.md
- 検証日：2026-10-21

## 実行した検査と環境

- `python3 tools/check_pages.py --page cpp-types-literals`：エラー 0・警告 0
- `python3 tools/check_snippets.py -v snippets/cpp-types-literals`：15 片・30 回のコンパイルで期待と違うもの 0（g++-13 (Ubuntu 13.4.0-6ubuntu1~22~ppa2) 13.4.0、g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0）
- 手で `g++-15 -std=gnu++23 -O2 -Wall -Wextra -fsanitize=address,undefined`：run の 11 片を cases で動かし、警告・サニタイザの報告なし。出力は yaml と一致
- 本文に書かれたコンパイラの文面を g++-13・g++-15 の両方で確かめた。どれも本文どおり
    - define-ll-ng：`expected primary-expression before 'long'`
    - int64-max-ng：`no matching function for call to 'max(int64_t&, long long int&)'`
    - inf-overflow-warn：`integer overflow in expression of type 'int' results in '-2147483648' [-Woverflow]`（`-Wall` なしでも出る）
    - float128-cout-ng：`ambiguous overload for 'operator<<'`
    - float128.cpp を `-std=gnu++20`：`'float128_t' was not declared in this scope`。`-std=c++23`（厳密モード）でも通る
    - literals.cpp を `-std=gnu++20`：`warning: use of C++23 'size_t' integer constant`（警告どまり）
- 試しのプログラム（一時置き場の t1.cpp）で確かめたこと
    - `0.29 * 100` は `28.99999999999999644729`
    - $10^{18}$ の前後の `double` の間隔は上下とも 128（確認問題の答えは正しい）
    - $10^9$ の隣の `double` との間隔は $1.192 \times 10^{-7}$。geometry-precision の #double-precision の「約 $1.2 \times 10^{-7}$」と一致する（執筆者の未解決の点 3 は解決。本文の「$10^{-7}$ 程度」でそろっている）
    - `LLONG_MAX / 2^60 = 7`（「7 倍まで収まる」は正しい）、`0x3f3f3f3f * 2 = 2122219134 < INT_MAX`
    - `decltype(0xFFFFFFFF)`・`decltype(0x80000000)` は `unsigned int`、`decltype(4294967295)` は `long`（指摘 2 の根拠）
- 雛形の INF：raw.githubusercontent.com で 3 つのファイルを取得して確かめた。maspy `infty<int> = 1'010'000'000`・`infty<ll> = 2'020'000'000'000'000'000`、Nyaan `inf = 1001001001`・`infLL = 4004004004004004004LL`、ei1333 `inf = (1 << 30) - 1`・`infll = (1LL << 62) - 1`。表と一致し、どれも 2 倍しても型に収まる（Nyaan の 2 倍は 8008008008008008008 < 9223372036854775807）
- 参考の URL：4 つ（cppreference 2・cpprefjp・GCC 13 changes）とも 200 を返し、GCC 13 changes に「Library support for extended floating-point types」がある。github.com の 3 つは上で中身を確かめた。atcoder.jp・codeforces.com の URL はない
- AtCoder の環境：planning/decisions.md に「C++23 (GCC 15.2.0)、`-std=gnu++23`」とあり、手元の g++-15 も 15.2.0 なので、float128_t が AtCoder で使えるという推定（執筆者の未解決の点 2）は妥当。ただし本文の書き方は指摘 3 を見よ
- 図：puppeteer の chrome-headless-shell 146（Linux、WSL）で ranges.svg を 960×480 と、`<img style="width:390px">` で画像にした。この環境には日本語のフォントがなく和文は豆腐になるが、これは環境の問題で SVG の誤りではない（数値・ASCII の文字と配置だけを見た）
- 座標：$x = 60 + 62 (\log_{10} v - 8)$ で、int（142.6）・$2^{53}$（553.2）・long long（739.8）・$2^{64}$（758.5）・0x3f3f3f3f（123.6）・その 2 倍（142.3）・$10^{18}$（680）・$2^{60}$（683.8）・その 2 倍（702.5）を計算し直した。すべて正しい
- textlint は執筆者の結果（警告 1。代替テキストの文の長さ）をそのまま認めた

## 指摘

### 1｜直すべき｜図（G6・G2）｜docs/img/cpp-types-literals/ranges.svg の 61 行

- **問題**：`<text …>INF = 1LL << 60 ≈ 1.15×10^18</text>` の `<` が実体参照になっておらず、SVG が整形式の XML でない。ブラウザで開くと「error on line 61 at column 66: StartTag: invalid element name」で描画がそこで止まり、`![…](…svg)` の `<img>` として読むと図全体が出ない（`<img>` の SVG は XML の誤りがあると何も描かない）。check_pages・mkdocs build は SVG の中身を見ないので通ってしまう
- **根拠**：`python3 -c "import xml.dom.minidom as m; m.parse('ranges.svg')"` → `ExpatError: not well-formed (invalid token): line 61, column 65`。headless の Chrome で直接開いた画像でも同じエラー表示
- **直し方**：`1LL &lt;&lt; 60` と書く。一時置き場でこの 1 か所だけ直した fixed.svg は整形式になり、全体が描画されることを確かめた（ほかに `<`・`&` を含むテキストはない）

### 2｜直すべき｜事実（F2）｜#literals の 1 段落目「接尾辞のない整数は `int` で、`int` に収まらなければ `long`、`long long` の順に広がる」

- **問題**：この規則は 10 進のリテラルだけのもの。16 進・8 進・2 進のリテラルは `int` → `unsigned int` → `long` → `unsigned long` → … の順で、`0xFFFFFFFF`・`0x80000000` は `unsigned int` になる。同じ節で `0x`・`0b` を紹介しており、`0x80000000` を `long` だと思って `-0x80000000` を書くと正の数になる
- **根拠**：`static_assert(is_same_v<decltype(0xFFFFFFFF), unsigned>)`・`static_assert(is_same_v<decltype(0x80000000), unsigned>)` が g++-15 で通る。cppreference「Integer literal」の型の表（10 進と、2・8・16 進で列が分かれ、後者に unsigned の型が入る）
- **直し方**：「接尾辞のない **10 進の**整数は…」とし、「16 進・2 進は `int` に収まらないと `unsigned int` になる」を 1 文足す（literals.cpp に `static_assert(is_same_v<decltype(0x80000000), unsigned>);` を足してもよい）

### 3｜直すべき｜事実（F2）・版（C6）｜導入の 1 段落目「このページは、AtCoder の GCC 15.2（`-std=gnu++23`）と手元の g++-13・g++-15 で確かめた」

- **問題**：AtCoder 上では何も確かめていない（執筆者の報告の未解決の点 2 に「AtCoder 上では確かめていない」とある）のに、AtCoder で確かめたと読める。#float128 の「AtCoder の GCC 15.2 でも使える」も同じ推定を断定している
- **根拠**：planning/batches/b1/cpp-types-literals.md の未解決の点。AtCoder と同じ版（15.2.0）であることは planning/decisions.md で確かめられるので、推定そのものは妥当
- **直し方**：導入を「AtCoder と同じ GCC 15.2（`-std=gnu++23`）と g++-13 で確かめた」のように、手元の g++-15 が AtCoder と同じ版だと書く形にする。#float128 の版の行も「AtCoder と同じ GCC 15.2 で通る」とする

### 4｜直すとよい｜事実（F2）｜#inf の 2 段落目「符号付き整数のあふれは未定義動作で、`-O2` では比較の結果が狂う」

- **問題**：未定義動作は最適化の段階によらない。「`-O2` では狂う」は、`-O0` なら安全で `-O2` なら必ず狂う、と読める。実際によく起きるのは負に回り込んで比較が真になることで（確認問題の答えのとおり）、`-O2` の有無とは別の話
- **直し方**：「符号付き整数のあふれは未定義動作で、多くは負の数に回り込んで比較が真になり、最適化によっては別の壊れ方もする（[未定義動作](../cpp/cpp-undefined-behavior.md)）」のようにする。cpp-undefined-behavior は draft になったので #what-is-ub か #breaks-other-lines へリンクできる

### 5｜直すとよい｜分かりやすさ（U3）｜#inf の 1 段落目「INF + INF（INF に答え程度の値を足したもの）が型の上限を超えないこと」

- **問題**：「INF + INF」と書いた直後のかっこで「INF に答え程度の値を足したもの」と別のものを言っており、どちらが基準なのか迷う。表の列は「INF + INF」
- **直し方**：「INF に辺の重みや別の INF を足しても（目安は INF + INF）型の上限を超えないこと」のように、基準を INF + INF に一本化する

### 6｜直すとよい｜分かりやすさ（U3）｜#integer-types の 1 段落目

- **問題**：「約 $2 \times 10^9$ 以内なら `int`」の直後に「和や積が $10^9$ を超えそうなら、初めから `long long`」とあり、境目が $2 \times 10^9$ なのか $10^9$ なのか読者が迷う
- **直し方**：「`int` の上限は約 $2.1 \times 10^9$。入力が $10^9$ 以下でも、2 つ足すと超えうるので、和や積は初めから `long long` で持つ」のように、$10^9$ を使う理由を 1 句足す

### 7｜直すとよい｜分かりやすさ（U3）｜#integer-types の 4 段落目「`size_t` と `int64_t` は別名で」

- **問題**：「別名」が「型の別名（typedef）」の意味か「互いに別の名前」の意味か取りにくい
- **直し方**：「`size_t` と `int64_t` は型の別名（ほかの型に付けた名前）で」とする

### 8｜直すとよい｜事実（F3）・分かりやすさ｜#inf の表の `1e18` の行

- **問題**：「値」の列に型の `double` が入り、「INF + INF」が「—」になっている。ほかの行と列の意味がずれる
- **直し方**：値を「$10^{18}$（`double`）」、INF + INF を「`long long` にすれば収まる（$2 \times 10^{18}$）」とする

### 9｜直すとよい｜コード（C3）｜snippets/cpp-types-literals/float-compare.cpp の `long long y = 1 + 2;  // 10 倍して整数で持てば正確`

- **問題**：本文は「小数点以下 2 桁までなら 100 倍」と言い、コードは「10 倍」で `1 + 2` と書くので、何を 10 倍したのかがコードだけでは分からない
- **直し方**：コメントを「0.1・0.2 を 10 倍して 1・2 として持てば正確」にする

### 10｜直すとよい｜図（G3）｜ranges.svg を幅 390px で表示したとき

- **問題**：viewBox 960×480 を 390px に縮めると倍率 0.41 で、14px の文字が約 5.7px、目盛りの 12px が約 4.9px になり、スマホでは読めない（mobile.png で確かめた）。数値は本文の表にもあるので必須ではない
- **直し方**：縦に詰めて viewBox の幅を 640 前後にするか、文字を 18〜20px にする。__int128 の行は本文で扱わないので省いて幅を空けてもよい

### 11｜直すとよい｜図（G5）｜ranges.svg の __int128 の行

- **問題**：(a) 棒が 830 まで伸び、右寄せのラベル「… 2^127−1 ≈ 1.7×10^38」（x = 940 で右寄せ）の先頭がおよそ 750 から始まり、棒の右端と文字が重なる（fixed.png で確かめた）。(b) 本文は `__int128` に一言も触れておらず、図にだけ出てくる
- **直し方**：(a) ラベルを棒の下か、棒の右端（830）より右から始める。(b) #integer-types の表の後に「64 bit を超える値は GCC の拡張 `__int128` で持てる（[整数のオーバーフローと __int128](../cpp/cpp-integer-overflow.md#int128)）」を 1 文足す

### 12｜直すとよい｜用語とリンク（F7）・未解決の点 4｜本文の関連ページへのリンク

- **問題**：(a) リンクの文字が相手の題名と違う。cpp-integer-overflow は「整数のオーバーフローと __int128」（本文は「整数オーバーフローと型の落とし穴」）、cpp-math-functions は「数・ビット・乱数の関数」（「数の関数」）、cpp-initialization は「初期化と CTAD」（「初期化の書き方」）、cpp-io は「入出力と定数倍」（「入出力」）、geometry-precision は「誤差の扱いと整数での処理」（「誤差と整数での判定」）。(b) これらのページは今 draft で、執筆者が挙げた anchor（cpp-integer-overflow#int-product・#edge-values、cpp-initialization#refill、geometry-precision#scale-to-integer・#eps、cpp-io#float-output）はすべて実在する
- **直し方**：リンクの文字を題名（か nav_title）にそろえ、節へのリンクに変える。手引き §7 の「draft 以降なら節へリンクしてよい」の条件を満たしている。#cast の「`(long long)(a * b)`」の話と #quiz の 1 問目は cpp-integer-overflow#int-product と重なるので、そこへのリンクを添えると重複が役割分担になる

## 執筆者の未解決の点への答え

1. 図の文字の重なり：10^18 付近の 3 つのラベルは縦にずらしてあり重ならない。long long・unsigned long long の値のラベルも棒の上に出て重ならない。重なるのは __int128 のラベルだけ（指摘 11）。ただし、その前に XML の誤りで図が出ない（指摘 1）
2. AtCoder での float128_t：同じ GCC 15.2.0・`-std=gnu++23` なので推定は妥当。本文の書き方は指摘 3
3. $10^9$ での誤差：geometry-precision の「約 $1.2 \times 10^{-7}$」と一致している。直しは不要
4. 節へのリンク：関連ページは draft になり、挙げた anchor はすべてある（指摘 12）

front matter の `cpp_std: 17` は、コード片の中心（`is_same_v`・メッセージのない `static_assert`）が C++17 なので妥当。C++23 の 0uz・float128_t は節ごとに版を書いている。手引きの enum の扱い（14 を足すか）はメインの判断に任せる。

## 総合の判定

**小さな直しで可**。直すべき 3 件（SVG の `<` の実体参照、16 進リテラルの型の規則、AtCoder で確かめたと読める書き方）は、どれも 1〜2 文か 1 文字の修正で済む。数値・コンパイラの文面・雛形の INF の値・計算の主張はすべて確かめられ、コード片は g++-13・g++-15 とサニタイザで問題がない。
