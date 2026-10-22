# b5 検証：library-design

- 対象：docs/guide/library-design.md、snippets/library-design/fenwick-tests.{cpp,yaml}・verify-test.{cpp,yaml}、docs/img/library-design/workflow.svg
- 観点：fact.md・code.md・clarity.md・figure.md
- 環境：g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0。図は `python3 tools/render_svg.py library-design --scale 2` と `--bg '#1e2129'` で 360px・720px の PNG にして目で確かめた

## 実行して確かめたこと

- `python3 tools/check_pages.py --page library-design`：エラー 0・警告 0
- `python3 tools/check_snippets.py snippets/library-design`：2 件とも期待どおり（期待と違う 0）
- `g++-15 -std=gnu++23 -O1 -Wall -Wextra -fsanitize=address,undefined` で fenwick-tests（`ok`）と verify-test（$10^9$ の 2 要素に $10^9$ を足して `3000000000`）を動かした。警告・サニタイザの報告なし
- `explicit` の主張：`mylib::fenwick_tree<long long> fw = 5;` は `conversion from 'int' to non-scalar type ... requested` でエラーになる（作業用の場所で確かめた）
- `#pragma once` を main のファイルに書くと `-Wpragma-once-outside-header` の警告が出る（執筆者の手引きへの提案 2 のとおり）
- `npx textlint`：エラー 0・警告 4（執筆者の報告と同じ。図の代替テキスト・practice2 の行・確認問題の題 2）
- ACL（~/lib/ac-library-master）：fenwicktree.hpp は `using U = internal::to_unsigned_t<T>;` で `std::vector<U>` に足す、`explicit fenwick_tree(int n)` と引数なしのコンストラクタ、`assert(0 <= l && l <= r && r <= _n)`。document_ja の fenwicktree.md・segtree.md の制約は $0 \le n \le 10^8$（長さ 0 を許す）。expander.py は `#include ["<](atcoder/...)[">]` を展開する（山括弧の ACL も展開する）
- `NDEBUG`：cpp-undefined-behavior#assert の「AtCoder のオプションには -DNDEBUG が含まれない」と一致
- library-checker-problems の categories.toml（2026-05-01 更新のもの）を数えた：14 分類・235 問。Data Structure 43・Graph 36・Polynomial 26・Number Theory 22・Tree 20、Sample 3 問（aplusb・many_aplusb・many_aplusb_128bit）。本文と一致
- README.md の `./generate.py -p unionfind # generate testcases of unionfind` を確かめた
- point_add_range_sum の task.md・info.toml：0-indexed、`1 l r` は $\sum_{i=l}^{r-1} a_i$、$N, Q \le 5 \times 10^5$、$a_i, x \le 10^9$。本文の「半開区間なのでそのまま使える」「入力が $5 \times 10^5$ 行を超える」と合う
- verification-helper の README.ja.md：`.test` の名前、`#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"`、`oj-verify run`、「利用できる問題は主に Library Checker と AOJ。他にもいくつかのサービス」、「#pragma once などの include guard に部分的に対応」
- oj-bundle のソース（onlinejudge_verify/languages/cplusplus_bundle.py）：`#include <...>` は展開せず残す、`#include "..."` を展開する、`#if` の中の `#include "..."` は `unable to process #include in #if / #ifdef / #ifndef other than include guards` のエラー、1 行目以外の `#pragma once` もエラー。本文の主張と合う
- competitive-verifier の document.ja.html（check_noai で指定なし）：`// competitive-verifier: [KEY] [VALUE]` と `#define [KEY] [VALUE] (非推奨)` の表、「互換性のため、C++ では #define PROBLEM ... で属性を定義できます。しかし ... 避けて」。README.md：「inspired by verification-helper」、`competitive-verifier migrate`。本文と合う
- practice2：`python3 tools/ap.py contest practice2` で A. Disjoint Set Union 〜 L. Lazy Segment Tree の 12 問を確かめた
- 執筆者の未解決 2（Library Checker の ACL）：library-checker-judge の langs/langs.toml で、C++ の各言語のコンパイルに `-I /opt/ac-library` が付いている。Library Checker でも ACL の include は展開しなくてよい（`-DNDEBUG` も付かない）
- 生成ブロックの表の問題名 136 個を categories.toml と比べた：aho_corasick・minimum_enclosing_circle・minimum_steiner_tree・range_add_range_min・static_range_sum_with_upper_bound・sum_of_multiplicative_function の 6 個は categories.toml にない。ただしリポジトリには問題のフォルダ（info.toml）がある（GitHub API の木で確かめた。categories.toml にない問題はリポジトリに 18 個、全部で 253 個）
- 図：400×380、viewBox と width・height が同じ比。背景は白で塗られ、暗い周りでも読める。360px で 10px の文字が約 9px、11px が約 10px になり読める。重なり・はみ出しなし。矢印の向き（ヘッダ → 3 つの使う側 → 実行・判定・展開 → Library Checker・AtCoder）は本文と合う
- front matter：git diff で、変えたのが complexity・stage・updated（と要点・本文）だけと確かめた。要点の「何ができるか」は summary と食い違わない

## 指摘

### 1. 直すとよい｜事実（F3）・分かりやすさ｜#verify の Library Checker の行

- **問題**：「問題の一覧（GitHub の categories.toml）を数えると、14 の分類で 235 問あった」は categories.toml については正しいが、読者は Library Checker の問題数と読む。リポジトリには categories.toml にない問題が 18 個あり（全 253 個）、このページの表にも 6 個（range_add_range_min・aho_corasick など）が入っている。「Data Structure 43」と表の数を比べると合わない
- **根拠**：上の「実行して確かめたこと」の categories.toml と GitHub API の木の比較
- **直し方**：「categories.toml の一覧に載る問題は 14 分類・235 問（一覧に載らない問題もリポジトリにある）」のように、数が一覧のものだと分かる書き方にする。または正確な数をやめ「200 問あまり」とする。あわせてメインは、表の 6 問が judge.yosupo.jp で開けるかを確かめるとよい（このページの執筆者の担当外）

### 2. 直すとよい｜コード（C3）・分かりやすさ（U3）｜#interface の BIT のコード片（fenwick-tests.cpp:header）

- **問題**：本文は「BIT をこの約束で書いた例」として header の範囲を見せ、すぐ次の #headers で「先頭に `#pragma once`」「使う標準ヘッダを自分で include する（`<vector>`・`<cassert>`）」を求める。見えている「ヘッダ」にはどちらもない。理由はファイルの 4〜5 行目のコメントにあるが、取り込みの範囲の外なので読者に見えない。写してヘッダにすると、本文の規則に反したヘッダになる
- **根拠**：fenwick-tests.cpp の `[start:header]` は 7 行目から。`#include <cassert>`・`#include <vector>` は 1 ファイルの中で `bits/stdc++.h` の後に書いても警告は出ない
- **直し方**：header の範囲の先頭に `// 実際のヘッダでは 1 行目に #pragma once を書く` のコメントと `#include <cassert>`・`#include <vector>` を入れる（`#pragma once` はコメントのまま）。または本文に「ヘッダの先頭の `#pragma once` と標準ヘッダの include は、次の節で述べるので省いた」と 1 文足す

### 3. 直すとよい｜分かりやすさ（U3）｜#what-to-build の表の前の文と「作り始める合図」

- **問題**：「次の表は目安で、左の段から順に作る」とあるが、表は段階が行（縦）に並ぶので「左」は誤り（上の行から）。また「作り始める合図：… 使ったことのない部品を先回りして作らない」が、表の「順に作る」と食い違って読める
- **根拠**：表の 1 列目が段階 1〜4 で、行ごとに並ぶ
- **直し方**：「上の段から順に」に直す。合図の行と結び付けて「表は、書く機会が来た部品のうちどれを先にヘッダにするかの目安である」のように、表の役割を 1 文で書く

### 4. 直すとよい｜事実（F2）・分かりやすさ｜#tests の「保つ性質を確かめる」

- **問題**：「Union-Find なら、merge のたびに size の合計が $n$ のままかを見る」は、全頂点 $v$ の `size(v)` の和と読むと $n$ にならない（同じ成分の頂点が同じ値を返す）。正しいのは代表元ごとの和
- **根拠**：$n = 2$ で merge(0,1) の後、size(0) + size(1) = 4
- **直し方**：「`leader(v) == v` の頂点の `size` の合計が $n$ のままか」または「`groups()` の大きさの和が $n$ か」と書く

### 5. 直すとよい｜事実（F2）｜#verify の oj-verify の行

- **問題**：「Library Checker と Aizu Online Judge の問題に対応している」は、ほかのジャッジに対応しないと読める。README は「主に Library Checker と AOJ。他にもいくつかのサービスの問題が利用可能」
- **根拠**：verification-helper の README.ja.md の「利用できる問題は主に…」
- **直し方**：「おもに Library Checker と Aizu Online Judge の問題に対応している」とする

### 6. 直すとよい｜事実（F1・F10）｜要点の「計算量」・complexity と fenwick-tests.cpp:stress

- **問題**：要点と complexity は「手元のテストは小さい $n$ の乱数で数千回」だが、見せている stress のコード片は 1000 回（各回 20 操作）である
- **根拠**：fenwick-tests.cpp 59 行目 `iter < 1000`
- **直し方**：コード片を `iter < 5000` などにするか、要点と complexity を「千回単位」「1000 回ほど」にそろえる（3 か所とも）

### 7. 直すとよい｜事実（F2）・ページ間の一貫性｜#headers の `#pragma once` の行

- **問題**：「oj-bundle はインクルードガード（`#ifndef` の組）への対応が部分的なので、`#pragma once` にそろえる」は、cpp-macros-template-file#bundling-tools の「`#pragma once` かインクルードガードで、同じファイルを 1 回だけ展開する」と読み比べると食い違って見える。README の「部分的」は `#pragma once` を含む include guard 全体についての言葉で、ソースでは `#ifndef` の組も扱う（ガードの外にコードがあるとエラー、`#pragma once` は 1 行目でないとエラー）
- **根拠**：cplusplus_bundle.py の 307〜355 行、README.ja.md の「#pragma once などの include guard に部分的に対応」
- **直し方**：「oj-bundle は `#pragma once` を 1 行目に書くと確実に 1 回だけ展開する（インクルードガードはガードの外に行があるとエラーになる）。そこで `#pragma once` にそろえる」のように、理由を具体的にする

### 8. 直すとよい｜事実（F9）｜参考

- **問題**：「oj-bundle は `#ifdef LOCAL` などの条件の中の `#include "..."` をエラーにする」の出典が参考にない。verification-helper の README.ja.md には書かれておらず、ソースにある
- **根拠**：README.ja.md に該当の記述なし。cplusplus_bundle.py の 399〜400 行にエラーの文面がある
- **直し方**：参考に [online-judge-tools「verification-helper」の cplusplus_bundle.py](https://github.com/online-judge-tools/verification-helper/blob/master/onlinejudge_verify/languages/cplusplus_bundle.py)（条件の中の include と `#pragma once` の扱い）を足す。または cpp-macros-template-file#bundling-tools への言及で済ませる

### 9. 直すとよい｜事実・分かりやすさ｜#bundling の ACL の行（執筆者の未解決 2）

- **問題**：「ACL のないジャッジに出すときは、ACL も expander.py で展開する」の前に、確認先の Library Checker に ACL があるかが書かれておらず、#verify の手順 2 で ACL を使ってよいか迷う
- **根拠**：library-checker-judge の langs/langs.toml で C++ のコンパイルに `-I /opt/ac-library`
- **直し方**：「Library Checker の C++ にも ACL が入っている」と 1 文足す（出典に library-checker-judge の langs.toml を足す）。書かなくても誤りではない

### 10. 直すとよい｜コード（C4）・分かりやすさ（U6）｜#verify の確認用の解答（verify-test.cpp:head・core）

- **問題**：本文は「ライブラリは実際には `#include "../lib/fenwick_tree.hpp"` の 1 行で読む」と書くが、見せている 2 つのコード片のどちらにもその行がなく、head と core の間に何が入るのかが見えない
- **根拠**：head は 2〜3 行目、core は 34 行目から。間の 8〜31 行（ヘッダの中身）は取り込まれない
- **直し方**：head の範囲に `// #include "../lib/fenwick_tree.hpp"  ← 実際はこの 1 行（ここでは下に中身を書いた）` のコメント行を入れ、2 つのコード片を 1 つの流れとして読めるようにする

### 11. 直すとよい｜分かりやすさ（U9）｜#headers の「次の 5 つを守る」

- **問題**：「次の 5 つを守る」の後に 6 つ目の箇条（`// @impl` で分けるなら）がある。textlint の無効化のため別の塊だが、表示では 6 つの箇条が並ぶ
- **根拠**：本文 95〜103 行
- **直し方**：@impl の行を箇条から外して段落にするか、「5 つを守る。cph の改造版を使うなら、さらに次の 1 つ」と書く

### 12. 直すとよい｜図（G5）｜workflow.svg

- **問題**：②の枠は破線、③の枠は太線だが、その意味が図にも本文にもない。下の注は①②③の役割だけを説明する
- **根拠**：360px・720px の PNG で確かめた。破線（`stroke-dasharray="5,3"`）・太線（`stroke-width="3"`）
- **直し方**：線の種類をそろえる（①〜③を同じ実線に）か、注に「破線：自動で回すもの、太線：提出するもの」のように書き足す

## 総合の判定

**小さな直しで可**。直すべき 0・直すとよい 12。事実の主張（ACL の fenwick_tree の作りと制約、AtCoder の NDEBUG、oj-bundle の展開の規則、oj-verify・competitive-verifier の書き方、Library Checker の分類の数、practice2 の 12 問）は一次資料・ソースと合っていた。コード片はサニタイザつきでも通り、図も 360px とダークの周りで読める。直すとよいのは、問題数の言い方（1）、コード片と本文の規則のずれ（2・10）、表の読み方（3）、Union-Find の size の言い方（4）など。

### メインへの補足

- 執筆者の未解決 1：stress-testing・problem-sets は作業ツリーでどちらも stage: draft になっている。本文の `[愚直解との比較](../guide/stress-testing.md)` は `#procedure`、`[問題集の案内](../guide/problem-sets.md)` は `#verify-sets`（または `#problem-sets-practice2`）へ張り替えられる
- 執筆者の未解決 4（competitive-verifier の原文）：document.ja.html の本文を読み、`PROBLEM` の属性名と `#define` の非推奨を原文の表と段落で確かめた
- 付録 B の追加の提案（competitive-verifier.github.io・online-judge-tools.github.io）について：competitive-verifier.github.io は check_noai で指定なしを確かめた。raw.githubusercontent.com も check_noai で指定なし
