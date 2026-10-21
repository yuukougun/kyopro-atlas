# cpp-initialization の報告と提案（工程8b・b1）

- 書いたファイル：docs/cpp/cpp-initialization.md、snippets/cpp-initialization/ の 19 片（vector-init・multi-dim・multi-dim-type-ng・array-init・uninit-ng・uninit-ok・designated-init・designated-order-ng・designated-ctor-ng・aggregate-emplace・aggregate-emplace-17-ng・aggregate-designated-17・explicit-ng・explicit-ok・refill・ctad・ctad-17・ctad-std・ctad-pitfall。どれも .cpp と .yaml）、docs/img/cpp-initialization/{nested,ctad-flow}.svg
- front matter で変えたもの：complexity・stage（draft）・cpp_std（20）・gcc_min（13）。updated は 2026-10-21 のまま。sections は変えていない
- 検査の結果：check_pages エラー 0・警告 0。check_snippets 19 片・38 回のコンパイルがすべて期待どおり（g++-13・g++-15）。fix_problems --check は直すべき行 0。textlint エラー 0・警告 1（落とし穴 3 の半開区間 `$[0, n)$` の括弧の対応。数式の誤検出）
- 版：ページの中で最も新しい機能は C++20（指示付き初期化・丸括弧の集成体初期化・ranges::fill）なので cpp_std を 20 にした。CTAD は ctad-17 で `-std=gnu++17` でも同じ型になることを確かめた。すべて g++-13 と g++-15 の `-std=gnu++23` で通る
- 使った出典：cppreference（CTAD・Aggregate initialization・explicit・memset・Zero-initialization）、cpprefjp（丸括弧の集成体初期化・指示付き初期化・クラステンプレートのテンプレート引数推論）、ACL の document_ja/dsu.md（GitHub）。research/09 §4.2・§4.9・§4.19・§4.36。新しいドメインはない
- 図：catalog の visual は static・priority 2 なので、静的な SVG を 2 枚（3 次元 vector の入れ子と括弧の対応、CTAD で型が内側から決まる流れ）にした。色に加えて線の種類（実線・破線・点線）とラベルで次元を区別した。手元に SVG を描画する道具がなく、見た目は目で確かめていない（XML として読めることだけ確かめた）

## 台帳への提案

- なし（problems は空で、problems_note のとおり C++ のページは ABC の問題を置かない）

## 用語集への提案

- 集成体｜aggregate｜コンストラクタを書いていない、すべてのメンバが public の構造体や配列。メンバを宣言順に `{}` に並べて初期化でき、C++20 からは丸括弧や指示付き初期化も使える
- 縮小変換｜narrowing-conversion｜`double` から `int`、`long long` から `int` のように、値が変わりうる型の変換。波括弧の初期化ではコンパイルエラーになるが、丸括弧や `=` では黙って行われる

## 手引きへの提案

- 見出しの中の `<`：Python-Markdown は `<int, 26>` や `<long long>` を HTML のタグとして扱い、表示から消える。このページでは見出しにだけ `&lt;` と書き、front matter の title は `<` のままにした（生成物では md_text が `&lt;` に直す）。§13.2「見出しの文字と title を同じにする」に「見出しでは `<` を `&lt;` と書く」を足すとよい。見本の cpp-views-basics の見出し「keys・values・elements<N>：…」の `<N>` も同じ理由で消えるおそれがある（ビルドして確かめてほしい）
- prh.yml：特になし

## 問題の補充の候補

- なし（C++ のページは問題を置かない方針）

## 未解決の点

- 「手元の g++-13 で 105842398323404453 のような値が出た」は未初期化の読み出しの結果で、実行のたびに変わりうる（例として示しただけ）
- `vector c{v};` がコピーになる理由（コピーの推論が優先される規則）は cppreference の CTAD のページを根拠にし、g++-13・g++-15 の static_assert で確かめた
- 使い分けの表の「グローバルの C 配列」は research/09 §4.9 の使い分けに従った。大きな局所配列がスタックを溢れさせる話は cpp-stack-depth の担当と考え、触れていない
- 使用量の目安：道具の呼び出し 約 35 回、Web 取得 約 12 回（URL の存在確認と cpprefjp 1 ページの本文）
