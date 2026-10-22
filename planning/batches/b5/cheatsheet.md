# b5 cheatsheet（早見表）の報告と提案

- 書いたファイル：docs/guide/cheatsheet.md（snippets・図はなし。表とリンクだけで足りたため）
- front matter で変えたもの：stage（stub → draft）・updated（2026-10-22）。complexity は案内のページなので null のまま
- 検査の結果：check_pages エラー 0・警告 0、fix_problems --check 直すべき行 0、textlint エラー 0・警告 0。本文のリンク（169 か所）はすべて draft のページの実在する anchor であることを手元のスクリプトで確かめた（stub の reverse-index-constraints・glossary・notation・twelvefold-way・cpp-environment へはページへのリンクだけ）
- 使った出典：drken の計算量・bit 演算の記事（qiita.com）、cppreference の Fundamental types、ACL v1.6 の document_ja（手元の ~/lib/ac-library-master/document_ja/ で計算量を確かめた）。新しく noai を確かめたドメインはない
- 数値の確かめ方：型の上限・階乗・二項係数・フィボナッチ数・2 と 3 の累乗・log2・カタラン数・ベル数・分割数・調和級数・⌊N/i⌋ の値の個数・メモリの個数・998244353 の性質は Python で計算。素数の個数 π(10^k)（k ≤ 9）・π(2×10^5) = 17984・10^9 未満の素数の差の最大 282 は C++ の篩（g++-15）で数えた。約数の個数・互除法の回数は divisor-count-bound・gcd-lcm の表の値にそろえた

## 申し送りの反映

- b1 §4：`<bit>` の値と境界の表（bit-tricks）、`max<long long>`・`min({a, 3LL, b})`・`constexpr auto T = [] { … }();`（cpp）、INF の候補の表（cpp）、doubling の「始点がすべてで K が 1 つなら O(N) のメモリ」（complexity-and-constraints の形の表）、外積は 8×10^18 が見積もりで実際の最大は 4×10^18 であること（type-limits）
- b3 §4：和・差の分布 → 畳み込み、添字の XOR → アダマール変換、OR・AND → ゼータ変換（complexity-and-constraints の形の表）
- b1 §5：std::function の倍率と println の速さは早見表に書いていない（再現しない数値を避けた）

## 台帳への提案

- なし（このページは問題を載せない。hub の目安 0〜3 の 0）

## 用語集への提案

- なし（用語集へのリンクは張っていない。既存の語 complexity・amortized-complexity・popcount・lowbit・submask などで足りる）

## 手引きへの提案

- 早見表の数値は各ページの値と食い違いやすい。早見表に値を書いたページ（complexity-estimation・divisor-count-bound・gcd-lcm・cpp-types-literals・cpp-math-functions・stl-containers・mod-arithmetic）を直すときは、早見表の同じ行も直す、と §7 か §15 に一言足すとよい
- 数の目安を再計算するスクリプトを tools/ に置く案（research 00 §4.1 の提案）。今回の計算は scratchpad の nums.py・pi.cpp で行った。置くならメインが判断する

## 問題の補充の候補

- なし（案内のページなので問題を載せない方針）

## 未解決の点

- C++ の版の表（cpp 節）は research 09 §4.3 と draft の C++ のページ（cpp-io・cpp-lambda・cpp-views-cpp23・cpp-algorithms・cpp-undefined-behavior）の版の記述から作った。cpp-environment（stub）の version-matrix が書かれたら、行と GCC の版を照らし合わせ、早見表の表から #version-matrix へ節のリンクに張り替える
- reverse-index-constraints（stub）が書かれたら、計算量と制約の節の最初のリンクを節（signs-constraint-* など）へ張り替えるか検討する
- 「隣り合う素数の差の最大」は 10^9 までだけを載せた。10^18 までの 1442（research 06 §6.3、OEIS A002386）は手元で確かめられないので載せていない
- 調和級数の回数は ⌊M/d⌋ の和（M = 10^6 で 13970034）で書いた。research 06 の「N = 2×10^5 で 2.56×10^6」は M·H_M（切り捨てなし）の値で、⌊⌋ の和は 2472113。早見表には M = 10^6 の約 1.4×10^7 だけを書いた
- 使用量の目安：道具の呼び出し約 40 回、Web 取得 3 回

## 検証の指摘への対応

- 指摘 1〜6 はすべて直した（1：$3^N$ の条件を足した、2：`bit_width` などは GCC 10〜と添えた、3：`set`・`map` の `contains` と `ranges::contains` に書き分けた、4：「割られる数が負なら 0 か負の値」にした、5：列名を「計算量・振る舞い」、表の名前を「見た目と違う書き方」にし、「遅い操作」に操作がないことを添えた、6：「なら正しい（負だと誤ることがある）」にした）
- 採らなかった指摘：なし
