# cpp-undefined-behavior の報告（工程8b・バッチ b1）

- 書いたファイル：docs/cpp/cpp-undefined-behavior.md、snippets/cpp-undefined-behavior/（14 組。ub-loop・ub-loop-o0・ub-loop-fixed・out-of-range・uninit-array・uninit-scalar・uninit-fixed・pq-top・dijkstra-pop・reallocation・temporary-range・string-view・shift-ctz・assert）、docs/img/cpp-undefined-behavior/reallocation.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21 のまま）。sections・cpp_std・gcc_min・atcoder は変えていない（環境・落とし穴のページなので null のまま）
- 検査の結果：check_pages エラー 0・警告 0。fix_problems --check 直すべき行 0。check_snippets 14 組・28 回のコンパイルで期待と違う 0。textlint エラー 0、警告 10（no-doubled-joshi はコードや文の境目をまたいで数える誤検出が多い。sentence-length は要点の計算量の行・図の代替テキスト・オプションを並べた箇条で、分けると読みにくくなるので残した）
- 使った出典：en.cppreference.com（Undefined behavior・Range-based for loop・assert）、gcc.gnu.org（Instrumentation Options・Optimize Options・libstdc++ Macros・Debug Mode）。新しいドメインはない。事実はすべて手元の g++-13.4・g++-15.2 で再現して確かめた（下の「手元で確かめたこと」）

## 手元で確かめたこと（本文の根拠）

- ub-loop：`for (int i = x; i > 0; i *= 2)` は -O0 で 31 回、-O2 では条件が消えて止まらない（g++-13・g++-15。警告なし）。-fsanitize=undefined で signed integer overflow を報告
- vector の範囲外：-O2 では止まらない。-D_GLIBCXX_ASSERTIONS・-D_GLIBCXX_DEBUG で abort、ASan で heap-buffer-overflow、UBSan では見つからない。生の配列は ASan（global-buffer-overflow）と UBSan（index out of bounds）で見つかる
- **新しく分かったこと**：GCC 15 の libstdc++ は最適化なし（-O0・-g だけ）で _GLIBCXX_ASSERTIONS を自動で定義する（libstdc++ Macros の文書と、g++-15 -O0 で vector の範囲外が Assertion で止まることで確認。g++-13 -O0 では止まらない）。cpp-environment の「VS Code のビルドタスクは -g だけ」の行に関係する
- 未初期化：配列は -Wall -Wextra で警告なし、変数は -O2 でだけ may be used uninitialized。-ftrivial-auto-var-init=zero で正しい値、pattern で毎回同じ値（7375861463932509）。ASan・UBSan・_GLIBCXX_DEBUG は見つけない（道具付きのビルドでたまたま正しい値が出た）
- ダングリング：pq.top() は要素 2 個以上なら決まった動作（7 2）で、どの道具も止めない。要素 1 個でも ASan は見つけず、g++-15 -O2 でだけ -Wuninitialized の警告。再確保・string_view・範囲 for の一時オブジェクトは ASan で検出、-Wall と _GLIBCXX_DEBUG では検出しない（再確保は -O2 で Segmentation fault）。string_view は短い文字列だと stack-use-after-scope
- 範囲 for の一時オブジェクト：g++-15 gnu++23 だけ正しく動き、g++-15 gnu++20・g++-13 gnu++23 は ASan で heap-use-after-free
- `1u << 32` は実行時に 1、`__builtin_ctz(0)` は 32 を返した。UBSan はどちらも報告
- sort の比較関数 `<=`：_GLIBCXX_DEBUG で irreflexive の検査に失敗、ASan は要素 100 個で heap-buffer-overflow（3 個では何も出ない）、_GLIBCXX_ASSERTIONS と UBSan は見つけない。素の -O2 は 100 個では落ちなかった
- 速さ：ソートと 4×10^8 回のループのコードで、-O2 0.08 秒、-O1 -g -D_GLIBCXX_DEBUG -fsanitize=address,undefined 約 15 秒、_GLIBCXX_ASSERTIONS に替えて約 0.9 秒
- UBSan は既定で報告後も続行し、-fno-sanitize-recover=all で終了コード 1 で止まる
- assert：-O2 -Wall -Wextra で有効（AtCoder のオプションに -DNDEBUG がないことは decisions.md の記録による）

## 台帳への提案

- なし。catalog の problems_note のとおり、C++ のページには問題を置かなかった（本文の確認問題 5 問で確かめる）

## 用語集への提案

- 未定義動作｜undefined-behavior｜C++ の規格が結果を決めていない操作（符号付き整数のあふれ・範囲外の読み書き・未初期化の変数の読み出しなど）。何が起きてもよく、コンパイラは起きないと仮定して最適化する
- ダングリング｜dangling｜参照・イテレータ・ポインタ・string_view が、寿命の切れた物を指している状態。そこを読み書きすると未定義動作になる
- 一時オブジェクト｜temporary-object｜本文でリンクした（cpp-range-for でも使われているが、用語集にまだ見出しがない）。定義案：関数の戻り値など、名前のない値。ふつうはそれを含む文の終わりで消える

## 手引きへの提案

- 実行時に止まること（sanitizer の報告・Assertion・Segmentation fault）を check_snippets の expect で表せないので、壊れる書き方は呼ばない関数に入れて `:bad` で取り込み、手元の結果を本文に書いた（cpp-views-basics の lifetime と同じ形）。expect: crash（終了コードが 0 でないことを期待）か、flags に sanitizer を付けて失敗を期待する形があれば、本文の「止まる」の主張も CI で保てる
- out-of-range・shift-ctz の run の case は、未定義動作の結果（範囲外に書いても 100 と出る、`1u << 32` が 1）を期待値にしている（cpp-integer-overflow の ub-check と同じ扱い）。将来のコンパイラで変わりうるので、検証役に方針を確かめてほしい

## 問題の補充の候補（問題ID・何を問うか・裏付けの URL）

- なし（C++ のページは問題を置かない方針）

## 未解決の点

- cpp-environment（stub）の「VS Code のビルドタスクは最適化なし」の記述と、GCC 15 の -O0 で _GLIBCXX_ASSERTIONS が自動で付くことは関係がある。cpp-environment の執筆者に伝えると、手元で範囲外が -O0 のときだけ止まる理由を説明できる
- cpp-comparators の less-equal-pitfall は「同じ値が多いと Segmentation fault」と書く予定だが、手元の素の -O2 では同じ値 100 個で落ちなかった（ASan では検出）。要素数で変わると思われるので、その節の検証で確かめてほしい
- 「Ubuntu の g++ は既定で -fstack-protector-strong が付き、局所配列を壊すと stack smashing detected で止まることがある」ことは確かめたが、AtCoder の GCC で同じかは分からないので本文に書かなかった
- 図 reallocation.svg は手元に SVG を描画する道具がなく、表示を目で確かめていない。検証役に確認を頼みたい
- 使用量の目安：道具の呼び出し 約 40 回、Web 取得 8 回（URL の生存確認と GCC の文書 2 件の確認）

## 検証の指摘への対応（2026-10-21）

- 直したもの：1（未初期化の警告の言い過ぎ。本文を例の形に限り、表の未初期化を「未初期化の変数・配列」の 1 行にまとめた）、2（complexity と要点の主語）、3（shift-ctz の場合分けを外した）、4（string_view の短い文字列は正しく出た）、5（倍率を幅で書き、別の例の約 3 倍・約 65 倍を足した。コンパイルは「毎回数秒」にし #pch へリンク）、6（表から `-Wall -Wextra` の列を外し、表の下の文で述べた）、7、8、9（図を上下に積む 360×500 にし、代替テキストの「左・右」を「上・下」に）、10（`string`・`vector` は空で作られることも足した）
- 採らなかったもの：なし
- 検査：check_pages エラー 0・警告 0、fix_problems --check 0 行、check_snippets 14 組・28 回で期待と違う 0、textlint エラー 0（警告 10。前と同じ種類）

### メインへの提案（sections の title の変更。front matter の sections と本文の見出しを一緒に変える）

- anchor: uninitialized の title を「未初期化変数：手元では不定、AtCoder では -ftrivial-auto-var-init=zero で 0 になる（-Wall は配列の未初期化を見落とす）」に変える（検証の指摘 1。「警告しない」は添字が定数のときに言い過ぎになる）
