# cpp-math-functions の報告と提案（工程8b・b1）

- 書いたファイル：docs/cpp/cpp-math-functions.md、snippets/cpp-math-functions/ の 16 組（gcd-lcm・gcd-ng・midpoint-clamp・clamp-ng・division・pow-sqrt・pi・bit-functions・popcount-int-ng・popcount-unsigned・builtins・bit-tricks・bitset・bitset-ng・random・chrono の .cpp と .yaml。どれも g++-13・g++-15）、docs/img/cpp-math-functions/{bit-count,division}.svg
- 取り込まないコード片：gcd-ng（`__gcd(12, 18LL)` のコンパイルエラーを確かめるため。§13.9）
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21 のまま）。sections の gcd-lcm の title を「lcm は a / gcd(a, b) * b の順にしてあふれを避ける」から「lcm は戻り値の型であふれる」に変えた（anchor は同じ）。libstdc++ の `std::lcm` は中で先に割っており（/usr/include/c++/15/numeric）、利用者に起きるのは `int` 同士の `lcm` が `int` で返ってあふれる事故だから。手で書くときの `a / gcd(a, b) * b` の順は本文の落とし穴 2 に残した
- 検査の結果：check_pages（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、check_snippets（16 件・32 回のコンパイルですべて期待どおり）、textlint（エラー 0・警告 0）
- 動く図：作っていない（visual は static・priority 2）。静的な SVG を 2 枚描いた（2 進表記の上の popcount・countr_zero・countl_zero・bit_width、数直線上の 0 に向かう切り捨てと floor）
- 版の確認：gcd・lcm は `-std=gnu++14` で、midpoint・popcount・numbers::pi は `-std=gnu++17` で、g++-13・g++-15 ともコンパイルエラーになることを確かめた（clamp・gcd は gnu++17 で通る）。M_PI は `-std=c++23` でも通った。random_shuffle は gnu++23 で非推奨の警告が出た
- 使った出典：cpprefjp（gcd・lcm・clamp・numbers・bit・bitset・steady_clock）、cppreference（lcm・midpoint・bit_ceil・uniform_int_distribution）、GCC の Bit Operation Builtins、planning/research/09-cpp §4.14・§4.27・§4.28・§4.31・§6.3。どれも付録 B のドメインで、新しく noai を確かめたドメインはない。URL は curl で 200 を確かめ、midpoint の丸めと bit_ceil の未定義動作は本文の文で確かめた

## 台帳への提案

なし（catalog のとおり problems は空。C++ のページは本文の確認問題で確かめる）。

## 用語集への提案

なし（本文は用語集へリンクしていない）。強いて足すなら：

- 組み込み関数｜builtin-function｜コンパイラが特別に用意する関数。GCC では `__builtin_` で始まり、`__builtin_popcount` などが 1 命令に置き換わる。規格の外なので、ほかのコンパイラでは使えないことがある

## 手引きへの提案

- §13.2（見出しと title を同じにする）により、このページの見出しはかなり長い（builtins の節は 100 字を超える）。cpp の節は逆引きの単位なので長い title を保ったが、見出しを短くして詳細を本文の 1 文目に回す方針にするかはメインで決めてほしい
- 見出しに `__gcd`・`__builtin_*`・`_Find_first` のような下線を含む名前があるが、.venv の Python-Markdown（attr_list）で太字にならず文字どおり出ることを確かめた

## 問題の補充の候補

- 探していない（C++ のページは problems を置かない方針。catalog の problems_note のとおり）

## front matter・catalog への提案

- related に math/mod-pow（pow の節で繰り返し二乗法へリンクした）と basics/binary-search（midpoint の落とし穴でリンクした）を足すかを検討してほしい
- 逆引き（cpp-reverse-index#lookup-types）の表に、`bit_ceil`・`__builtin_popcountll`・`mt19937_64 rng(random_device{}())`・`uniform_int_distribution` の行の追加を提案する（行き先は本ページの bit-functions・builtins・random）
- 早見表（research/09 §6.4）に `<bit>` の関数の値と境界の表を入れるなら、本文の bit-functions の表（x = 12 と x = 0 の値）と builtins の表（0 を渡したとき）を使える

## 未解決の点

- 図 bit-count.svg・division.svg は描画して目で確かめる道具がなく、XML として読めることと座標の計算だけを確かめた。文字の重なりがないか検証役に見てほしい
- 「規格は分布（uniform_int_distribution）の計算方法を決めていないので、同じ種でも標準ライブラリが違えば値が変わりうる」は本文に書かなかった（cppreference で該当の文を見つけられなかった）。mt19937 自体の列が規格で決まっていることも書いていない
- `rand()` の RAND_MAX が 32767 の処理系がある（MSVC）という点は記憶に基づく。手元の GCC で 2147483647 なのは確かめた
- `__builtin_ctz(0)` は手元で 32 を返したが、本文では未定義とだけ書き、32 が出たことは「たまたま」と書いた
- sqrtl が 2^64 付近でも常に正しいとは限らない、という記述は具体例を確かめていない（補正を勧める根拠としてだけ書いた）
- 使用量の目安：道具の呼び出し 約 35 回、Web 取得は curl で cppreference・cpprefjp・GCC の 15 URL の状態確認と 6 ページの本文確認
