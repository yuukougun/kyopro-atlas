# cpp-types-literals の報告と提案（工程8b・b1）

- 書いたファイル：docs/cpp/cpp-types-literals.md、snippets/cpp-types-literals/ の 15 組（int-types・int64-max-ng・literals・auto-deduction・define-ll-ng・using-ll・cast・inf・inf-overflow-warn・double-precision・double-1e18・float-compare・scale-round・float128・float128-cout-ng。各 .cpp と .yaml）、docs/img/cpp-types-literals/ranges.svg
- front matter で変えたもの：complexity（「実行時の計算量には関わらない（型の選び方の話）」）・stage（draft）・cpp_std（17）・gcc_min（13）。updated は 2026-10-21 のまま。sections は変えていない
- 検査の結果：check_pages（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、check_snippets（15 件・g++-13 と g++-15 で期待どおり）、textlint（エラー 0・警告 1）
  - 残した警告：53 行の sentence-length（図の代替テキスト。数値を並べるので 120 字を少し超える）
- 図：catalog の visual は static・priority 2。数直線の静的な SVG（ranges.svg）を作った。動く図は作っていない
- 問題：catalog・front matter の problems は空で、problems_note のとおり ABC の問題を置かず確認問題で確かめた
- 使った出典：cppreference（integer_literal・numeric_limits）、cpprefjp（stdfloat）、GCC 13 changes、GitHub の maspy・Nyaan・ei1333 の雛形（INF の値を 2026-10-21 に確かめた）。どれも付録 B のドメイン（github.com・en.cppreference.com・cpprefjp.github.io・gcc.gnu.org）で、新しく noai を確かめたドメインはない

## 台帳への提案

- なし（このページは問題を載せない）

## 用語集への提案

- 浮動小数点数の仮数部｜mantissa｜浮動小数点数のうち有効数字を持つ部分のビット数。double は 53 bit で、整数を正確に表せるのは 2^53 まで（本文ではリンクしていない。足すならこのページの floating-point 節の最初の出現から）
- research の Nyaan の INF「4004004004004004004（2倍しても収まる）」はそのとおりだった。research/09 §4.8 の maspy の値「2.02×10^18」も一致

## 手引きへの提案

- front matter の cpp_std は enum が 17・20・23 だけで、C++14 までで済む内容（このページの中心）を表せない。今回は 17 にした（0uz と float128_t は C++23 で、節ごとに版を書いた）。14 を足すか、「中心の内容が C++17 以前なら 17」と決めてほしい
- cpp の構成の目安（一言 → 素朴に書くと → 版 → 落とし穴 → 確認問題 → 関連）は、型を説明するこのページには「素朴に書くと」が合わない節が多かった。合わない節では省き、表で型と起きることを並べた

## 早見表・使い分けへの提案

- 早見表（research/09 §6.4）の「INF の候補」は、本文 inf 節の表（INT_MAX・0x3f3f3f3f・1LL << 60・LLONG_MAX・1e18 と INF + INF）をそのまま使える
- 逆引き（コードの見た目）：`1e18`・`auto INF = 1e18`・`0x3f3f3f3f`・`memset(d, 0x3f, sizeof d)`・`0uz`・`ll(x)` → このページの各節

## 問題の補充の候補

- なし（problems_note のとおり C++ のページは ABC の問題を置かない）

## 未解決の点

- 図 ranges.svg は描画する道具が手元になく、座標の計算と XML の形だけを確かめた。文字の重なり（とくに 10^18 付近の 3 つの印のラベル、右端の long long・unsigned long long の値のラベル）の表示の確認を検証役に頼みたい
- AtCoder の GCC 15.2 での float128_t の可否は、手元の g++-15（-std=gnu++23）で通ることからの推定。AtCoder 上では確かめていない
- 「値が 10^9 なら double の誤差は 10^-7 程度」は 10^9 付近の隣の数との間隔（2^-23 ≈ 1.19×10^-7）からの見積もり。geometry-precision の double-precision 節と数値をそろえてほしい
- 関連のページ（cpp-integer-overflow・cpp-initialization・cpp-math-functions・cpp-io・cpp-undefined-behavior・cpp-macros-template-file・geometry-precision）はまだ stub なので、節ではなくページへリンクした。draft になったら、たとえば cpp-integer-overflow#int-product・#edge-values、cpp-initialization#refill、geometry-precision#scale-to-integer・#eps、cpp-io#float-output へのリンクに変えるとよい
- 使用量の目安：道具の呼び出し 約 30 回、Web 取得 6 回

## 検証の指摘への対応（2026-10-21）

- 直したもの：1（SVG の `<` を `&lt;` に。整形式を確かめた）・2（10 進とそれ以外のリテラルの型の規則を分け、literals.cpp に `0x80000000` の static_assert を追加）・3（「AtCoder と同じ GCC 15.2 の g++-15」と書く形に）・4・5・6・7・8・9・11（__int128 のラベルを棒の下へ移し、本文に __int128 への 1 文とリンクを追加）・12（リンクの文字を題名にそろえ、節へのリンクに。#cast と確認問題 1 問目から cpp-integer-overflow#int-product へ）
- 採らなかったもの：10（幅 390px での文字の小ささ）。文字を大きくすると長いラベル（INF + INF の 2 本、下端の注記）が重なり、図の組み直しが要る。数値は本文の表にもあるので、今回は見送った。直すなら viewBox を幅 640 前後に詰め直す（メインの判断に任せる）
