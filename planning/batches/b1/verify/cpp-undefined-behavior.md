# cpp-undefined-behavior（未定義動作とダングリング）の検証

- 対象：docs/cpp/cpp-undefined-behavior.md、snippets/cpp-undefined-behavior/（14 組）、docs/img/cpp-undefined-behavior/reallocation.svg
- 観点：fact.md（F1〜F10）・code.md（C1〜C8）・clarity.md（U1〜U10）・figure.md（G1〜G7）
- 検証日：2026-10-21。コンパイラ：g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0、g++-13 (Ubuntu 13.4.0-6ubuntu1~22~ppa2) 13.4.0。試しのコードは作業用の場所に置いた（リポジトリには置いていない）

## 確かめたこと

- `python3 tools/check_pages.py --page cpp-undefined-behavior`：エラー 0・警告 0
- `python3 tools/check_snippets.py snippets/cpp-undefined-behavior -v`：14 組・28 回のコンパイルで期待と違う 0
- **リンク先**：cpp-integer-overflow#signed-overflow-ub・#shift-width、cpp-range-for#modify-in-loop・#temporary-range、cpp-container-idioms#invalidation、cpp-comparators#less-equal-pitfall、cpp-math-functions#builtins、cpp-views-basics#lifetime、cpp-structured-bindings#pq-top-reference、cpp-macros-template-file#ifdef-local・#import-std、guide/stress-testing、graph/dijkstra、cpp-environment はある。用語集の #undefined-behavior・#dangling・#temporary-object はまだない（手引き §13 の 5 のとおり提案の anchor で書いてよい。#temporary-object は cpp-range-for・cpp-algorithms も使っている）
- **参考の URL**：7 件とも取得できた（200）。libstdc++ Macros に「_GLIBCXX_ASSERTIONS：Defined by default when compiling with no optimization」がある。`-ftrivial-auto-var-init` は Optimize Options のページにある。cppreference の Range-based for loop に C++23 からの一時オブジェクトの寿命の延長がある。手元の `/usr/include/x86_64-linux-gnu/c++/15/bits/c++config.h` の 601 行目も `! defined(__OPTIMIZE__)` で `_GLIBCXX_ASSERTIONS` を定義している
- **AtCoder の環境**：planning/decisions.md 28 行目の記録（`-std=gnu++23 -O2 -Wall -Wextra -march=native -fmodules -ftrivial-auto-var-init=zero -DATCODER -DONLINE_JUDGE -lstdc++exp`、`-DNDEBUG` なし）と本文が一致する
- **本文の主張を手で確かめた**（どれも g++-13・g++-15、`-std=gnu++23`）
    - ub-loop：`-O0` で 31、`-O2` で `loop`、`-O2 -Wall -Wextra` で警告なし。`-fsanitize=undefined` の文面は本文のとおり（`signed integer overflow: 1073741824 * 2 cannot be represented in type 'int'`）
    - vector の範囲外（`3 3`）：`-O2` で 100。`-D_GLIBCXX_ASSERTIONS` で `Assertion '__n < this->size()' failed`、`_GLIBCXX_DEBUG` でも止まる、ASan で heap-buffer-overflow、UBSan は何も出ない。g++-15 の `-O0` だけ何も付けずに Assertion で止まり、g++-13 の `-O0` は止まらない。生の配列は ASan で global-buffer-overflow（局所なら stack-buffer-overflow）、UBSan で `index 3 out of bounds for type 'int [3]'`、`_GLIBCXX_ASSERTIONS` は対象外。定数の添字 `c[3]` は `-O2 -Wall` で `array subscript 3 is above array bounds of 'int [3]'`
    - uninit-array：`-O2` でゴミの値（実行ごとに違う）、`zero` で 9、`pattern` で両方の版とも 7375861463932509（`0xFEFEFEFE` で埋めたときの $2(v+2)^2 + (v+1)^2 + 23v^2$、$v = -16843010$ と一致）。道具付きのビルド（`-O1 -g -D_GLIBCXX_DEBUG -fsanitize=address,undefined`）で 9。`-Wall -Wextra` はこの関数に警告を出さない。uninit-scalar は `-O2` でだけ `'s' may be used uninitialized`
    - **ただし**、`int a[3]; cout << a[0];` と `int x; cout << x;` には、両方の版の `-O0`・`-O2`・`-O2 -ftrivial-auto-var-init=zero` のどれでも `'a' is used uninitialized [-Wuninitialized]`・`'x' is used uninitialized` が出た（下の 1）
    - pq-top：要素 2 個以上（3 個でも）で決まった値（新しい先頭）になり、ASan・UBSan・`_GLIBCXX_DEBUG` のどれも止めない。要素 1 個では g++-15 `-O2` でだけ `-Wuninitialized` が出て、g++-13 `-O2` は `0 0`、ほかは `5 1` を出した。本文のとおり。heap の性質から pop 後の先頭の場所には新しい最小が入るので、「決まった動作」の説明も正しい
    - reallocation の bad：`-O2` で Segmentation fault、`-O2 -D_GLIBCXX_DEBUG` も Segmentation fault（検査の報告はない）、ASan で heap-use-after-free、`-Wall -Wextra` で警告なし。本文のとおり
    - temporary-range の `for (int v : groups(n)[0])`：g++-15 `-std=gnu++23`・`-std=c++23` で正しく `0 2 4`、g++-15 `-std=gnu++20` と g++-13 `-std=gnu++23` は ASan で heap-use-after-free、警告なし。ACL の `dsu::groups()` は `std::vector<std::vector<int>>` を値で返す（document_ja/dsu.md、dsu.hpp 46 行目）ので、`d.groups()[0]` も同じ形である
    - string-view の bad：ASan で長い文字列（$n = 30$）は heap-use-after-free、短い文字列（$n = 0$）は stack-use-after-scope。`-O2` では長い文字列は化けた文字列が出たが、**短い文字列は正しく `xyz` が出た**（下の 4）
    - sort の `<=`（同じ値だけの配列）：`_GLIBCXX_DEBUG` で `comparison doesn't meet irreflexive requirements, assert(!(a < a))`（3 個でも）。ASan は 17 個以上で heap-buffer-overflow、3 個では何も出ない。`_GLIBCXX_ASSERTIONS` と UBSan は何も出ない。素の `-O2` は 1000 個では落ちず、$10^5$ 個で Segmentation fault（執筆者の未解決の点 2 の「要素数で変わる」はこのとおり。cpp-comparators の検証に回す情報）
    - `1u << 32` は実行時に 1、`__builtin_ctz(0)` は 32。UBSan は `shift exponent 32 is too large for 32-bit type 'unsigned int'` と `passing zero to __builtin_ctz(), which is not a valid argument` を出した。`_GLIBCXX_DEBUG` と `-Wall` は何も出ない
    - 範囲 for の中の push_back：`_GLIBCXX_DEBUG` で `attempt to increment a singular iterator`、ASan で heap-use-after-free、`_GLIBCXX_ASSERTIONS`・UBSan は何も出ない
    - 不具合を探すビルドは、`-fno-sanitize-recover=all -ftrivial-auto-var-init=pattern` を足してもコンパイル・実行できた。ASan 付きのビルドで `ulimit -s unlimited` の下の深さ $10^6$ の再帰も動いた
    - 速さ：自分で書いた「長さ $2 \times 10^5$ のソート＋$4 \times 10^8$ 回の配列を読むループ」では、`-O2` 0.50 秒、`-O1 -g -D_GLIBCXX_ASSERTIONS -fsanitize=address,undefined` 1.47 秒（約 3 倍）、本文のビルド 32.8 秒（約 65 倍）。本文の 0.08 秒・約 0.9 秒・約 15 秒（約 11 倍・約 190 倍）とは倍率が違う（下の 5）。手元の負荷は高かった（load average 約 20）
    - 本文のビルドのコンパイル時間（assert.cpp）：2.2〜5.3 秒（負荷の高い中で 3 回）。素の `-O2` も pch なしで 2.8 秒（下の 5）
- **コード片**：14 組とも `#include <bits/stdc++.h>` と `using namespace std;`、マクロ・型の別名なし、`'\n'`。取り込みの印は本文と一致し、壊れる書き方は呼ばない関数に入れて `:bad` で取り込んでいる。未定義動作を期待値にしている case は out-of-range の `3 3` と shift-ctz の `32 0` の 2 つ（執筆者の手引きへの提案 2 への意見は下の「そのほか」）
- **図**：Linux の chrome-headless-shell（puppeteer 同梱の 146）で幅 640px と 358px の PNG にして目で確かめた。手元に日本語のフォントがないので日本語は豆腐になったが、配置・矢印・枠は確かめられた。白の背景・viewBox あり・文字はテキスト（sans-serif）。row の矢印は左が実線、右は赤の破線で、古い領域は灰色の破線の枠なので、色だけに頼っていない。図の値（`g = {{1}}`、`push_back({2})`、容量 1 → 2）は bad のコード片と代替テキストに一致する。catalog の visual は確かめていない（このページは静的な図 1 つで、本文の文章だけでも要点が分かる）

## 指摘

| 番号 | 重さ | 観点 | 場所 | 問題 | 根拠 | 直し方 |
| --- | --- | --- | --- | --- | --- | --- |
| 1 | 直すべき | fact F2 | #uninitialized の見出し「（-Wall は配列の未初期化を警告しない）」、121 行目「配列の初期化忘れは `-Wall -Wextra` でも警告されない」と「（`-O0` では出ない）」、#detection-tools の表の「配列の未初期化 ×」「変数の未初期化 ○（`-O2`）」 | 言い過ぎである。配列でも、添字が定数で読むだけなら `-Wall` が警告する。変数も、単純に読むだけなら `-O0` で警告が出る。警告が出ないのは、例の `cnt[c - 'a']++` のように添字が実行時に決まる読み書きのときである。このまま読むと「配列は警告が出ないもの」「`-O0` では変数の警告も出ない」と覚えてしまう | `int a[3]; cout << a[0]; int x; cout << x;` に、g++-13・g++-15 の `-O0`・`-O2`・`-O2 -ftrivial-auto-var-init=zero` のどれでも `'a' is used uninitialized [-Wuninitialized]` と `'x' is used uninitialized` が出た。一方で、本文の uninit-array には警告が出ず、uninit-scalar（ループで足す）は `-O2` でだけ `may be used uninitialized` が出た | 本文は「配列を `cnt[c - 'a']++` のように実行時の添字で使うと、`-Wall -Wextra` でも警告されない」「ループの中で足していく変数は `-O2` でだけ警告される（`-O0` では出ない）」のように、例の形に限って書く。表の行も「配列の未初期化（添字が実行時に決まる）」「変数の未初期化（ループで足す）」とする。見出しは sections の title なので、メインに「（-Wall は配列の未初期化を見落とす）」などへの変更を提案する |
| 2 | 直すとよい | clarity U1／fact F1 | front matter の `complexity` と要点の「計算量」の「どれも実行時の費用はない」 | 「どれも」が何を指すか分からない。冒頭だけを読む人には、未定義動作に費用がないのか、避ける書き方に費用がないのかが読み取れない | 要点の「何ができるか」と並べて読んだ | 「避ける書き方（初期値を書く・値で受ける・添字で書く）に実行時の費用はない。見つける道具を付けたビルドは遅い（…）」のように主語を書く |
| 3 | 直すとよい | code C3 | snippets/cpp-undefined-behavior/shift-ctz.cpp の取り込み 3 行目 `int c = (x == 0 ? 32 : countr_zero(x));` | `countr_zero(0u)` は 32 と決まっている、とコメントと本文 248 行目が言うのに、コードは 0 を場合分けしている。読者は「`countr_zero` でも 0 を避けなければならない」と受け取る | 規格の `countr_zero` は 0 で型の幅を返す（本文のとおり）。場合分けなしでも case `32 0` の 3 列目は 32 になる | `int c = countr_zero(x);  // __builtin_ctz(0) は未定義。countr_zero(0u) は 32 と決まっている` にする |
| 4 | 直すとよい | fact F3／clarity U2 | #dangling-string-view の 222 行目「手元では、`-O2` で先頭が化けた文字列が出て正常に終わった」 | 化けたのは長い文字列のときだけである。短い文字列（`make(0)` の `xyz`）は `-O2` で正しく出た。正しく出て見える場合があることのほうが危ないので、書いておく価値がある | `-O2` で $n = 30$ は先頭が化けた。$n = 0$ は `xyz` と正しく出た（両方の版）。ASan では短い方も stack-use-after-scope で止まる | 「長い文字列は先頭が化けたが、短い文字列は正しく出た（たまたまである）」とし、その後の ASan の文につなげる |
| 5 | 直すとよい | fact F3 | #debug-build の「遅くなる」の段落と、落とし穴「コンパイルに毎回 1 秒ほどかかる」 | (a) 倍率は書き方で大きく変わる。本文の `-O2` 0.08 秒は $4 \times 10^8$ 回のループとしては速すぎ、ループの大半が最適化で消えた例と思われる。その場合、道具付きのビルドとの倍率が大きく出る。(b) コンパイル時間の 1 秒は短すぎる | (a) 自分の例（ソート＋配列を読むループ）では、`ASSERTIONS` 版が約 3 倍、本文のビルドが約 65 倍で、本文の約 11 倍・約 190 倍と違った。(b) 本文のビルドで assert.cpp のコンパイルに 2.2〜5.3 秒かかった（負荷が高い中なので幅を持たせた） | (a) 「書き方で変わるが、手元の例では `ASSERTIONS` 版で数倍〜十数倍、`_GLIBCXX_DEBUG` 版で数十〜数百倍だった」のように幅で書き、complexity と要点も合わせる。(b) 「毎回数秒かかる」にし、[プリコンパイル済みヘッダ](../cpp/cpp-environment.md#pch) へリンクする |
| 6 | 直すとよい | clarity U9 | #detection-tools の表 | 列が 6 つあり、手引き §8 の「列は 4〜5 まで」を超える。スマホでは横にはみ出す | 手引き §8 の最後の行 | `-Wall -Wextra` の列を外し（○は「変数の未初期化」の 1 行だけ）、表の下の文で「`-Wall -Wextra` が見つけるのは単純な未初期化の読み出しと定数の添字の範囲外だけ」と書く |
| 7 | 直すとよい | clarity U3 | #uninitialized の 108 行目「（逆に、手元に合わせて直すと AtCoder でも通る）」 | 「手元に合わせて直す」が何をすることか分からない（手元の答えに合わせるのか、初期化を書くのか）。前の文と「逆に」がつながらない | 学ぶ人として読んだ | 括弧を消すか、「初期値を書けば、手元でも AtCoder でも同じ答えになる」とする |
| 8 | 直すとよい | clarity U3 | #dangling-temporary の箇条「危ないのは、戻り値の『中身』（`[0]`・`.first`・メンバ関数の戻り値）を回すときだけ」 | 「メンバ関数の戻り値」は、値で返すメンバ関数なら安全である。危ないのは一時オブジェクトの中を指す参照を返すメンバ関数（`.first` や `operator[]` と同じ）だけ | `groups(n)[0]` が危ないのは `operator[]` が参照を返すからで、値で返す関数を重ねても寿命は延びる | 「参照を返すメンバ関数」と書く |
| 9 | 直すとよい | figure G3 | reallocation.svg | 幅 358px では 640px の約 0.56 倍になり、font-size 14 の文字が約 8px になって読みにくい | 358px の PNG で確かめた | 左右に並べずに上下に積むか（viewBox を 360×520 程度）、font-size を 18 程度に上げて横幅を詰める |
| 10 | 直すとよい | clarity U3 | #uninitialized の 106 行目「関数の中で宣言した変数と配列（自動変数）は、初期値を書かなければ値が決まらない」 | `string`・`vector` などの関数の中の変数は、初期値を書かなくても空で作られる。この文だけを読むと、それらも不定と受け取れる | `string s;` は空文字列、`vector<int> v;` は空 | 「関数の中で宣言した `int`・`long long`・`double` などの変数と、その配列（自動変数）は」とする |

## そのほか（直さなくてよい点・判断の材料）

- 執筆者の手引きへの提案 2（未定義動作の結果を期待値にした case）について：out-of-range の `3 3` は glibc の malloc の余り（12 バイトの要求に 24 バイトの領域）に書くので、Debian の gcc:15.2.0 のコンテナでも同じになると見込める。shift-ctz の `32 0` は入力からシフト幅を読むので定数の畳み込みは起きない。どちらも yaml にコメントがあり、今のままでよい。将来のコンパイラで変わったら、その case を消して本文の「手元では」の記述だけを残せば足りる
- 執筆者の未解決の点 4（図を目で確かめていない）：上のとおり確かめた。内容の誤りはない（指摘 9 は大きさだけ）
- 執筆者の未解決の点 2：素の `-O2` で同じ値だけの配列を `<=` でソートすると、1000 個では落ちず、$10^5$ 個で落ちた（cpp-comparators の検証役に渡す情報）
- reallocation.cpp・string-view.cpp の `(void)&bad;` は要らない（外部結合の関数に `-Wunused-function` は出ない）。取り込みの外なので直さなくてよい

## 判定

**小さな直しで可**。直すべき 1 件（未初期化の警告についての言い過ぎ。本文 2 か所と表 2 行と、見出しの変更の提案）、直すとよい 9 件。ほかの事実（最適化でループの条件が消える例、GCC 15 の `-O0` で `_GLIBCXX_ASSERTIONS` が自動で付くこと、pq.top() の参照・再確保・一時オブジェクト・string_view の 4 つの型とそれぞれを見つける道具、`-ftrivial-auto-var-init=pattern` の値、UBSan・Debug Mode の文面）は、両方の版で本文のとおりに再現した。
