# 検証：cpp-macros-template-file（マクロと雛形）

- 検証役：書いた本人とは別のエージェント。観点は fact.md・code.md・clarity.md・figure.md
- 環境：g++-13 (Ubuntu 13.4.0-6ubuntu1~22~ppa2) 13.4.0、g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0。図は Windows の Chrome（headless、幅 780px、ライト）で PNG にして目で見た
- 試しのコードは scratchpad（/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/ff4dc6ee-16d4-486c-b97a-49fefbe7b218/scratchpad/v-cpp-macros-template-file/）に置いた。リポジトリには置いていない

## 実行した検査と結果

- `python3 tools/check_snippets.py -v snippets/cpp-macros-template-file`：16 片・31 回のコンパイルで期待と違う 0
- `python3 tools/check_pages.py --page cpp-macros-template-file`：エラー 0・警告 0
- front matter の差分（`git diff HEAD`）：変わったのは complexity・stage と本文だけ。規則どおり
- 本文に書かれたエラー・警告の文面を g++-13・g++-15 で 1 つずつ出して照らした。すべて一致した
  - `reference to 'count' is ambiguous`・`'int y1' redeclared as different kind of entity`・`'::main' must return 'int'`・`format '%d' expects argument of type 'int', but argument 2 has type 'long long int'`・`deduced conflicting types for parameter 'const T'`（note として出る）・`use of 'auto twice(int)' before deduction of 'auto'`・`'constexpr int twice(int)' used before its definition`・g++-13 の `inlining failed in call to 'always_inline' ... allocator ...: target specific option mismatch`（-O0 でも出る。g++-15 では出ない）
- 名前の衝突の一覧：`next`・`prev`・`distance`・`data`・`size`・`count` は g++-15 で ambiguous、`j0`・`j1`・`y1` は redeclared。本文のとおり
- `<bits/allocator.h>` を先に読む対策：g++-13 で `#include <bits/allocator.h>` → `#pragma GCC target("avx2")` → `#include <bits/stdc++.h>` の順で通った。maspy の my_template.hpp がこの形であることも確かめた
- Ofast：g++-13・g++-15 とも、`#pragma GCC optimize("Ofast")` ありで入力 -1 に `number`、なしで `nan`。本文のとおり
- `rep(i, v.size() - 1)` の確認問題：空の `v` で 0 回、`(int)(v.size() - 1)` は -1（g++-15）。本文のとおり
- `import std;`（g++-15、-fmodules）：
  - モジュールを作る前は `failed to read compiled module: No such file or directory`
  - `g++-15 -std=gnu++23 -O2 -fmodules -fsearch-include-path -c bits/std.cc` で `gcm.cache/std.gcm` ができた（3.2 秒）
  - `import std;` だけでは `'INT_MAX' was not declared in this scope`・`'assert' was not declared in this scope`
  - `#include <climits>`・`<cassert>` を前に書くと通る
  - 後に書く場合：`<vector>`・`<algorithm>`・`<cmath>`・`<cstdio>`・`<bits/stdc++.h>` はエラー。ただし `<climits>`・`<cassert>` は後に書いても通った（指摘 7）
  - traP の記事（https://trap.jp/post/2589/、uni_kakurenbo）は、モジュールの対応が GCC で partial なこと、import の後に #include を置く形は未対応で import を最後に置くよう勧めることを書いている。本文と合う
- ACL の expander.py（~/lib/ac-library-master/expander.py）：`atcoder_include` の正規表現は `["<]atcoder/...[">]` の両方に合う。除く行はインクルードガード（`ATCODER_*_HPP`）・`#pragma once`・`//` で始まる行。`--lib`・`-c`・`combined.cpp`・`--origname`（include の行の次の行番号で `#line N "名前"` を入れる）は本文のとおり。~/lib/ac-library-v1.5/expander.py には `origname` がない。本文のとおり
- cph のフォーク（~/projects/kyopro2/lib/_cph/cph-fork.patch）：`cph.copyForSubmit`・`cph.bundle.includePaths`・`cph.bundle.implMarker`（既定 `@impl`）の 3 つを確かめた。挙動も確かめた：探す順（ソースのフォルダ → includePaths）、`// ===== begin:`・`end:`・`impl:` の印、見つからない include を残して警告する、条件ブロックの中の include は分けずにその場に展開する、目印が `#if` の中なら警告して分けない、未保存の内容を使う、判定パネルのボタン。どれも本文のとおり
- oj-bundle：verification-helper の README.ja と cplusplus_bundle.py を読んだ。展開するのは `#include "..."`（-I で探す場所）、`<...>` は展開せず残す。表は正しい（言い回しは指摘 5）
- 参考の URL：7 件で HTTP 200 を確かめた（maspy・Nyaan・ei1333・cpprefjp・gcc.gnu.org・document_ja・trap.jp/post/1224）。trap.jp の 2 記事は `tools/check_noai.py` で noai・noimageai の指定がないことを確かめた。atcoder.jp・codeforces.com の URL はない
- リンクの anchor：`cpp-types-literals.md#type-alias`・`cpp-integer-overflow.md#unsigned-size` は存在する

## 執筆者の未解決の点について

1. AtCoder で `import std;` が通るか：本文は「確かめていない」と書いている。decisions.md の AtCoder のオプション（-fmodules・-lstdc++exp）と traP の記事に合う書き方で、問題ない
2. FOR の選び方：maspy の雛形は `overload3(a, b, c, d, ...) d` で、4 番目を選ぶ形だった。research/09 の「5 番目」は誤りで、本文の「4 番目」が正しい。本文のコードは名前（PICK・`_i`・末尾の `_`）が maspy と違い、引数の数でマクロを切り替える技法自体はよく知られたものなので、F8 の問題はない
3. `printf("%d")` の -1294967296：3000000000 − 2^32 = −1294967296 で、手元の観測としては合う。ただし未定義動作なので、本文に一言添えるとよい（指摘 3）
4. cph の挙動：上のとおり、パッチの実装と試験で確かめた。本文と一致する
5. 「1〜3 秒」：目安として書かれていて妥当
6. 名前の一覧：上のとおり確かめた

## 指摘

直すべき指摘はない。以下はすべて「直すとよい」。

1. **直すとよい｜観点：事実（F2）・分かりやすさ（U3）｜場所：#namespaces 1 段落目**
   - 問題：「`y1` は `<cmath>` の数学関数 `y1`」とある。`y1`・`j0`・`j1` は C++ の規格の `<cmath>` の関数ではない。`<cmath>` が読み込む C の `math.h` が、POSIX の拡張としてグローバルに宣言する関数である。だから `count`（ambiguous）と違い、エラーが `redeclared as different kind of entity` になる
   - 根拠：`std::y1` は規格にない。g++ の出すエラーの種類も違う（上の検査）
   - 直し方：「`y1` は `<cmath>` が読み込む C の数学関数（POSIX の拡張。第 2 種ベッセル関数）で、グローバルに宣言されている」とする。count と y1 でエラーの種類が違う理由（std の中か、グローバルか）を一言添えると、確認問題の答えともつながる

2. **直すとよい｜観点：事実（F2）｜場所：#pragma の「Ofast は浮動小数点の約束を変える」**
   - 問題：「`Ofast` は `O3` に `-ffast-math` を加えたもの」とある。GCC の文書では、-Ofast は -O3 に加えて -ffast-math・-fallow-store-data-races などをオンにする
   - 根拠：GCC「Optimize Options」の -Ofast の項
   - 直し方：「`O3` に、規格に厳密に従わない最適化（`-ffast-math` など）を加えたもの」とする

3. **直すとよい｜観点：事実（F2）｜場所：#define-int の落とし穴 1**
   - 問題：「手元では…`-1294967296` と出た」は観測として正しい。ただし書式と型の食い違いは未定義動作で、結果は保証されない。読者が「下位 32 ビットが出る」と覚えるおそれがある
   - 直し方：「（未定義動作なので、いつもこうなるとは限らない）」を添える

4. **直すとよい｜観点：分かりやすさ（U3）・事実（F2）｜場所：#bundling-tools の表と「cph の『提出用にコピー』」の項**
   - 問題：表の「cph（このリポジトリの利用者のフォーク）」は、サイトの読者には何のことか分からない。`cph.copyForSubmit` などは公式の cph（Competitive Programming Helper）にはなく、改造版にだけある機能である。読者が公式の cph を入れて探しても見つからない
   - 直し方：「cph の改造版（公式の cph にはない機能）」と書く。入手先を示せないなら、仕組み（`#include "..."` だけを展開し、@impl で分ける）の例として読めるよう、一言断る

5. **直すとよい｜観点：事実（F2）｜場所：#bundling-tools の「oj-bundle」の項**
   - 問題 1：「`#pragma once` で書いたヘッダを前提にしている」は言い過ぎである。oj-bundle は、ファイル先頭のインクルードガード（`#ifndef`／`#define`／`#endif`）も 1 回だけ展開する対象として扱う
   - 問題 2：「oj-verify と組で使う」は、同じパッケージにあるというだけで、oj-bundle 単独でも使える
   - 問題 3：書かれていない実用上の違いがある。`#ifdef LOCAL` などの条件の中の `#include "..."` は、oj-bundle ではエラーになる（cph はその場に展開する）
   - 根拠：verification-helper の README.ja、onlinejudge_verify/languages/cplusplus_bundle.py（`unable to process #include in #if / #ifdef / #ifndef other than include guards`）
   - 直し方：「verification-helper に含まれる。`#pragma once` かインクルードガードで 1 回だけ展開する。`#ifdef` の中の `#include "..."` はエラーになる」とする

6. **直すとよい｜観点：事実（F2）｜場所：#namespaces の「std:: を省かない流儀」**
   - 問題：「現代的な解説コードは `using namespace std;` を書かず…ことが多い」は、裏付けのない一般化である
   - 直し方：「`using namespace std;` を書かず…と書く解説コードもある」とする

7. **直すとよい｜観点：事実（F2）｜場所：#import-std 2 段落目の括弧**
   - 問題：「`import` の後に `#include` を置く書き方は GCC がまだ対応していない」は、traP の記事どおりで方針として正しい。ただし手元の g++-15 では、`<climits>`・`<cassert>` は後に書いても通った（`<vector>`・`<cmath>` などはエラー）。読者が試して「通った」と混乱しうる
   - 直し方：「（`<vector>` などを `import` の後に `#include` するとエラーになる。GCC はこの順を対応していないので、`#include` は前に書く）」のように、エラーになる例で言う

8. **直すとよい｜観点：分かりやすさ（U3）｜場所：#import-std 1 段落目**
   - 問題：「`import std;` だけのコードは `std::` を付けて書かれている」は、`import std;` と `using namespace std;` を併用するコードもあるので、言い切りが強い
   - 直し方：「`using namespace std;` がなければ `std::` を付けて書く」とする

9. **直すとよい｜観点：分かりやすさ（U9）｜場所：#impl-marker の表の最後の行**
   - 問題：列の見出しは「結果（g++-13・g++-15）」なのに、最後の行だけが「目印より上に置く」という指示になっている。列の意味がそろわない
   - 直し方：最後の行は表から外して、表の下の「避け方」に入れる。または結果を「エラー（目印より上に置く）」とする

10. **直すとよい｜観点：分かりやすさ（U3）｜場所：#bits-stdcpp の「コンパイル時間」、#ifdef-local の「ONLINE_JUDGE」**
    - 問題：[AtCoder と手元の環境](../cpp/cpp-environment.md) へのリンクがページの先頭を指している。リンク先には該当する節（`#pch`・`#judge-macros`）がある
    - 直し方：`cpp-environment.md#pch`・`cpp-environment.md#judge-macros` にする。#pragma の「target は AtCoder では要らない」にも `#march-native` へのリンクを足すとよい

11. **直すとよい｜観点：図（G3）｜場所：bundling.svg**
    - 確かめた結果：ライトの表示で、文字の重なりはない。背景は白、viewBox・sans-serif・テキストのまま。A・B の色に加えて、実線・破線と「A」「B」のラベルでも区別している。本文の 3 つの手順と @impl の説明に合う
    - 問題 1：横 760 の図をスマホの幅（約 360px）に縮めると、13px の文字が 6px ほどになり読みにくい
    - 問題 2（ごく小さい）：提出ファイルの中の印は `// ===== begin: graph.hpp` だけで、実際の cph の出力（`// ===== begin: graph.hpp =====` と `// ===== end: ... =====`）より簡略である
    - 直し方：急がない。直すなら、左右に並べた配置を上下に並べるか、文字を大きくする。印は本文の説明どおりなので、そのままでもよい

## 観点ごとのまとめ

- **事実**：コンパイラの文面・実行結果・ACL の expander.py・cph の実装・oj-bundle の実装・traP の記事と照らし、誤りはなかった。言い回しの精度の改善が 1〜3・5〜8
- **コード**：16 片すべてが期待どおりである。取り込みの範囲と本文の対応は合う。この頁は主題がマクロなので、§9 の「マクロを使わない」の例外として妥当。`debug` の `endl` は標準エラー出力をすぐ出すための用途で問題ない。`ofast.cpp` の期待 `number` は GCC の版に依存する観測だが、本文もそう述べている
- **分かりやすさ**：各節が「素朴に書くと・版・落とし穴・確認問題」の型でそろっていて、断片で読んでも通じる。確認問題は理由まで書かれている。改善は 4・9・10
- **図**：内容は正しく、ライト表示で読める。スマホの幅で文字が小さいのが改善点（11）

## 総合の判定

**小さな直しで可**。直すべき指摘は 0 件、直すとよい指摘は 11 件。
