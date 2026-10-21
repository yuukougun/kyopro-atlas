# cpp-container-idioms の報告と提案（工程8b・b1）

- 書いたファイル：docs/cpp/cpp-container-idioms.md、snippets/cpp-container-idioms/ の 19 組（erase-if・erase-remove・erase-if-cxx17-ng・contains・map-subscript・map-const-ng・multiset-erase・emplace-back・emplace-brace-ng・member-lower-bound・iterators・iterator-index・iterator-index-ng・erase-loop・invalidation・reserve・unordered-pair-ng・unordered-hash・pb-ds の .cpp と .yaml）、docs/img/cpp-container-idioms/iterators.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21 のまま）。sections・cpp_std（null のまま。C++20 の erase_if・contains と C++23 の string::contains、GCC の拡張の pb_ds が混ざるため）・gcc_min・atcoder は変えていない
- 検査の結果：check_pages（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、check_snippets（19 件・38 回のコンパイルすべて期待どおり）、textlint（エラー 0・警告 3）
  - 残した警告：106 行の max-comma（数式 $\{1, 2, 2, 2, 3\}$ の読点）、139 行の no-unmatched-pair（数式の半開区間 $[\texttt{begin}, \texttt{end})$）、141 行の sentence-length（図の代替テキスト）
- 図：catalog の visual（static・priority 2）を静的な SVG で作った。上段に vector の begin・prev(end())・rbegin・end の位置、下段に set の it = st.erase(it) の前後。動く図は作っていない
- 問題：catalog の problems_note（C++ のページは ABC の問題を置かない）に従い、問題の囲みを置いていない
- 手元で確かめた事実（snippets に入れていないもの。scratchpad で実行）：
  - set（要素数 2×10^4）に 2×10^4 回の問い合わせで、std::lower_bound・ranges::lower_bound が約 2.2〜2.4 秒、メンバが 0 ms（g++-13・g++-15、-O2）
  - multiset の erase(end()) は g++-15 で free(): invalid pointer の異常終了、-D_GLIBCXX_ASSERTIONS で `__position != end()` の検査で停止
  - erase した it を ++it するループは g++-13・g++-15 で Segmentation fault、ASan で heap-use-after-free
  - 範囲 for 中の push_back は普通の実行で `1 2 3 10`（30 が落ちる）、ASan で heap-use-after-free
  - invalidation.cpp（参照を取ってから push_back）は普通の実行で正常終了、ASan で heap-use-after-free（g++-13・g++-15）
  - pb_ds の tree を less_equal で作り {3, 3, 5} を入れると、erase(3) で何も消えず、find(5) が end()、lower_bound(3) が 5（g++-13・g++-15）
  - hash<int>{}(12345) は 12345（g++-15）
  - set のイテレータの `end() - 1`、rbegin() と prev(end()) の ==、int と ptrdiff_t の max はどれもコンパイルエラー（g++-13・g++-15）
- 使った出典：cpprefjp（erase_if の vector・set・map、set::contains、basic_string::contains、map::operator[]、multiset::erase、vector::emplace_back）、cppreference の Containers library（イテレータの無効化の表）、GCC の Policy-Based Data Structures の手引き。どれも付録 B のドメインで、新しく noai を確かめたドメインはない。research/09 §4.20・§4.24、05-ds の stl-containers・balanced-bst、08 の hash-safety の記述も使った

## 台帳への提案

なし（問題を使っていない）。

## 用語集への提案

- イテレータ｜iterator｜コンテナの中の 1 つの位置を指す物で、`*it` でその位置の要素を読み、`++it` で次の位置へ進む。`begin()` は先頭、`end()` は最後の要素の次を指す（本文の iterators の節からリンク済み）
- イテレータの無効化｜iterator-invalidation｜コンテナの操作（vector の再確保、要素の削除など）で、それまでのイテレータ・参照が指す先を失うこと。無効になったものを使うと未定義動作になる（本文ではリンクしていない。足すなら invalidation の節からリンクする）

## 手引きへの提案

- type cpp の構成の目安（一言 → 素朴に書くと → 版 → 落とし穴 → 確認問題 → 関連）は、節が 12 個あるページでは各節の中に「素朴に書くと・版・落とし穴」の箇条を置く形にした（見本の cpp-views-basics と同じ）。目安の「関連」に当たる定型の見出しがないので、使い分けは各節の箇条に入れた
- ほかのページの節へのリンクは draft 以降に限られるので、stl-containers・ordered-set・hash-safety・cpp-undefined-behavior などへはページだけにリンクした。これらが draft になったら、節へのリンク（例：cpp-undefined-behavior の dangling、hash-safety の unordered_map の節）に直すとよい

## 問題の補充の候補

- なし。catalog の problems_note のとおり、C++ のページは本文の確認問題で確かめる

## 未解決の点

- 図 iterators.svg は描画して目で確かめる道具がなく、XML として読めることと座標の計算だけを確かめた。文字と矢印の重なりがないか、表示の確認を検証役に頼みたい
- unordered_map の rehash でイテレータは無効になるが参照・ポインタは無効にならない、という記述は規格の記憶と cppreference の無効化の表に基づき、手元の実行では確かめていない
- 「AtCoder の GCC でも pb_ds が使える」は、AtCoder の GCC 15.2 が libstdc++ を使うことからの判断で、提出しては確かめていない（atcoder.jp を開かない規則のため）
- multiset の count が O(log N + 個数) であることは cpprefjp の記述の記憶に基づく（研究資料 05-ds の落とし穴とも一致）。検証役に cpprefjp での確認を頼みたい
