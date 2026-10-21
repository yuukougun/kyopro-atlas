# cpp-comparators の検証（工程8b・バッチ b1）

- 対象：docs/cpp/cpp-comparators.md、snippets/cpp-comparators/ の 16 組（.cpp と .yaml）。docs/img/cpp-comparators/ はない（図は Markdown の表）
- 観点：fact.md・code.md・clarity.md・figure.md
- 検証日：2026-10-21

## 実行した検査と環境

- コンパイラ：g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0、g++-13 (Ubuntu 13.4.0-6ubuntu1~22~ppa2) 13.4.0
- `python3 tools/check_pages.py --page cpp-comparators`：エラー 0・警告 0
- `python3 tools/check_snippets.py snippets/cpp-comparators`：16 片・コンパイル 32 回・期待と違う 0
- `npx textlint docs/cpp/cpp-comparators.md`：エラー 0・警告 1（245 行の sentence-length。確認問題の題にコードがあるためで、執筆者の報告どおり。問題なし）
- 16 片をすべて読み、本文の取り込み（`:core`・`:pitfall`・`:dijkstra`・`:pair`・`:use`・`:capture`）と説明を 1 行ずつ照らした。cases の期待出力（strict-weak・multiple-keys・operator-less・spaceship）は手で計算し直して一致
- 作業用の場所（/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/ff4dc6ee-16d4-486c-b97a-49fefbe7b218/scratchpad/v-cpp-comparators/）で次を確かめた（-std=gnu++23）
  - `<=` の比較関数で同じ値 n 個を sort（g++-13・g++-15 とも同じ結果）
    - -O2：n = 1・16・17・100・1000・3×10^4 は正常終了、n = 3.5×10^4・4×10^4・5×10^4・10^5 は異常終了（g++-13 は Segmentation fault、g++-15 は 3.5×10^4 で Aborted、4×10^4 以上で Segmentation fault）
    - -O2 -fsanitize=address：n ≤ 16 は報告なし、n ≥ 17 は heap-buffer-overflow（READ）
    - -D_GLIBCXX_DEBUG：n = 1 から `Error: comparison doesn't meet irreflexive requirements, assert(!(a < a)).`（文面は本文と一致）
  - `<=` の比較関数の set に 1 を 3 回 insert：size 3・find は end・count 0（本文どおり）。multiset {1,1,2} の erase(1) で size 1（本文どおり）
  - const のない operator<：set・priority_queue・ranges::sort でコンパイルエラー、エラー文は g++-13・g++-15 とも `no match for 'operator<' (operand types are 'const Seg' and 'const Seg')`（本文どおり）。std::sort は通る
  - キャプチャのあるラムダの `set<int, decltype(by_w)> idx;`：g++-13・g++-15 とも `use of deleted function` （本文どおり）
  - `priority_queue pq(greater<int>{}, vector<int>{})` の型は `priority_queue<int, vector<int>, greater<int>>`（gnu++17）。`(int)3000000000LL` = -1294967296（greater<int> の落とし穴の説明どおり）
  - _GLIBCXX_DEBUG で、推移しない比較関数（`x + 1 < y`）や、一部の値でだけ自分自身と比べて true になる比較関数を sort しても止まらなかった（指摘 1）
- 出典：参考の 8 件の URL を curl で開き、title 要素が書かれた題名と合うことを確かめた。cpprefjp「algorithm」に狭義の弱順序と同値（`!(a < b) && !(b < a)`）の定義、cpprefjp「std::greater」に C++14 の `greater<void>` があることを確かめた。GCC の Semantics のページは指摘 3
- 図：SVG・動く図はない。catalog の visual（static・priority 2「比較関数と取り出される順の対応表」）は priority-queue-order の節の表で満たしている（表の 3 行は正しい）。G1〜G6 は対象なし

## 指摘

### 1｜直すべき｜事実（F2）｜#less-equal-pitfall、85 行

- **問題**：「`-D_GLIBCXX_DEBUG` を付けてコンパイルすると、`sort` は始めに比較関数を確かめる。約束を破っていれば … と出して止まる」は言い過ぎである。libstdc++ のデバッグモードが sort の前に確かめるのは、範囲の先頭の要素を自分自身と比べて false になるか（irreflexive）だけで、ほかの破り方は見つからない
- **根拠**：作業用の場所で `-D_GLIBCXX_DEBUG` を付け、推移しない比較関数 `[](int x, int y) { return x + 1 < y; }` で乱数 1000 個を sort しても、`x == 5` のときだけ `<=` になる比較関数で `{1, 2, 3, 5, 5, 5}` を sort しても、エラーなく終わった（g++-15）。`<=` は先頭の要素でも必ず true になるので、本文の例（1 個でも止まる）は正しい
- **直し方**：「`sort` は始めに、先頭の要素を自分自身と比べて false になるかを確かめる。`<=` や `>=` の比較関数はここで必ず引っかかり、… と出して止まる。ただし、推移しないなどのほかの破り方は見つからないことがある」のように、見つかる範囲を限る

### 2｜直すとよい｜事実（F3）｜#less-equal-pitfall の表（79 行あたり）

- **問題**：表は「17〜3×10^4 は正常」「10^5 で Segmentation fault」で、3×10^4 と 10^5 の間が抜けている。手元では 3.5×10^4 からすでに落ちるので、読者は「10^5 くらいにならないと落ちない」と受け取りかねない
- **根拠**：上の実験。g++-13・g++-15 とも 3×10^4 は正常、3.5×10^4 で異常終了（g++-15 は Aborted）、4×10^4 以上は Segmentation fault
- **直し方**：最後の行を「3.5×10^4〜10^5」とし、結果を「異常終了（Segmentation fault など）」にする。または表の後の文に「手元では 3.5×10^4 個から落ちた」と添える

### 3｜直すとよい｜事実（F9）｜#references、260 行

- **問題**：「GCC『libstdc++ Debug Mode: Semantics』：`_GLIBCXX_DEBUG` が検査する内容」とあるが、このページはデバッグモードでも正しいプログラムの意味が変わらないことと pedantic モードの話で、アルゴリズムの前提（比較関数など）を検査することは書かれていない。ページの title 要素も「Semantics」だけである
- **根拠**：curl で本文を読んだ。アルゴリズムの前提の検査（"Algorithm preconditions: Algorithms attempt to validate their input parameters …"）が書かれているのは、同じ章の概要のページ https://gcc.gnu.org/onlinedocs/libstdc++/manual/debug_mode.html である
- **直し方**：出典を debug_mode.html（題名は「Chapter 18. Debug Mode」）に差し替えるか、併記する。説明は「アルゴリズムの前提を検査すること」とし、irreflexive の検査そのものは手元で確かめた、と本文に書いてある形で足りる

### 4｜直すとよい｜分かりやすさ・事実（F10・F7）｜front matter の summary（13 行）と要点の囲み

- **問題**：summary は「約束（厳密弱順序）」、要点の囲みと本文は「約束（狭義の弱順序）」で、語が食い違う（執筆者の未解決の点 1）
- **根拠**：cpprefjp「algorithm」の訳は「狭義の弱順序 (strict weak ordering)」。sorting-techniques の summary・節の題名・用語集へのリンクも「狭義の弱順序」
- **直し方**：メインが summary を「約束（狭義の弱順序）」に直す（執筆者の提案に賛成）。aliases の「厳密弱順序」は残してよい。prh.yml に「厳密弱順序→狭義の弱順序」を足す提案にも賛成。用語集に strict-weak-ordering の項はまだないので（docs/guide/glossary.md を grep して確認）、執筆者の用語集の提案を反映する必要がある

### 5｜直すとよい｜分かりやすさ（U6）｜85 行と 150 行のリンク

- **問題**：執筆者は「cpp-undefined-behavior の debug-build 節と cpp-container-idioms の multiset-erase-one 節は stub なのでページへリンクした」と書いているが、今は両ページとも stage: draft で、節に本文がある
- **根拠**：docs/cpp/cpp-undefined-behavior.md 275 行に `{#debug-build}`、docs/cpp/cpp-container-idioms.md 98 行に `{#multiset-erase-one}` の節がある
- **直し方**：85 行の「付け方は[未定義動作](../cpp/cpp-undefined-behavior.md#debug-build)」、150 行の「1 個だけ消す書き方は[コンテナの定型](../cpp/cpp-container-idioms.md#multiset-erase-one)」に直す

### 6｜直すとよい｜コード（C2・C4）｜snippets/cpp-comparators/less-equal-crash.cpp

- **問題**：(a) このコード片はページのどこからも取り込まれていない（`grep -rn less-equal-crash docs/` で 0 件）のに `[start:core]` の印がある。(b) 先頭のコメントは「実行はしない…コンパイルが通ることだけを確かめる」だが、設定は `expect: run` で n = 3 で実行している。(c) n = 3 でも約束を破る比較関数で sort するので、規格の上では未定義動作を実行している（手元では挿入ソートの範囲なので落ちない）
- **根拠**：ファイルと yaml を読み、grep した
- **直し方**：本文で使わないなら消す（less-equal.cpp の `bad` と `assert(bad(1, 1))` で、約束を破ることは確かめられている）。残すなら、コメントを「n = 3 では落ちないので実行して、コンパイルと警告なしを確かめる」に直し、`:core` の印を外す。執筆者の手引きへの提案（実行時の異常終了の期待がない）については、落ちる実例は本文の表（手元で測った結果）で示し、コード片は落ちない大きさか compile だけにする、という今の扱いで足りると考える

### 7｜直すとよい｜事実（F2）｜#spaceship、220 行

- **問題**：「`= default` の `<=>` を書くと、コンパイラが `<`・`<=`・`>`・`>=`・`==`・`!=` の 6 つを作る」は仕組みとして不正確である。実際には、`<=>` を default にすると `==` が暗黙に default で宣言され、`<` などは `<=>` を使う式に、`!=` は `==` を使う式に書き換えられて使えるようになる（6 つの関数が作られるわけではない）
- **根拠**：cpprefjp「<=>/==による比較演算子の自動定義」（参考に挙げているページ）
- **直し方**：「6 つの比較が使えるようになる（`==` はコンパイラが合わせて作り、`<` などは `<=>` を使って書き換えられる）」程度にする。読者にとっての結論（6 つとも使える）は変わらないので、軽い直しでよい

### 8｜直すとよい｜分かりやすさ（U5）｜#strict-weak-ordering、64 行

- **問題**：「**素朴に書くと**：比較関数を渡さない `sort(v.begin(), v.end())` は、要素の `<` を使う」は、素朴な別解ではなく既定の動作の説明で、見出し語と中身が合わない
- **根拠**：ほかの節の「素朴に書くと」は、同じことを手で書いた形（ラムダや if の連鎖）を示している
- **直し方**：見出し語を「**既定では**」か「**関連**」に変える

## 執筆者の未解決の点について

1. 節の題名・summary の用語：指摘 4。「狭義の弱順序」にそろえるのに賛成
2. 表の「17〜3×10^4 は正常」：17・100・1000・3×10^4 で再現した。ただし 3.5×10^4 から落ちる（指摘 2）。「手元で」「試した」と書いてあるので、未定義動作の環境差の断りとしては足りている
3. stub へのリンク：両ページとも draft になったので節へのリンクに直せる（指摘 5）

## 総合の判定

小さな直しで可（直すべき 1 件・直すとよい 7 件）。事実の主張（コンパイルエラーの文面、set の「同じ」、priority_queue の向きの表、greater&lt;int&gt; の変換、C++17/20 の版の差）は手元で再現でき、コード片もすべて期待どおりに動く。直すべきは _GLIBCXX_DEBUG で見つかる範囲の言い過ぎ（指摘 1）だけである。
