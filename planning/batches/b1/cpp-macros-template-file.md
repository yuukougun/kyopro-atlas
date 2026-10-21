# cpp-macros-template-file の報告と提案

- 書いたファイル：docs/cpp/cpp-macros-template-file.md、snippets/cpp-macros-template-file/（16 組の .cpp と .yaml）、docs/img/cpp-macros-template-file/bundling.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21 のまま）。sections は変えていない
- 検査の結果：check_pages エラー 0・警告 0、fix_problems --check 直す行 0、check_snippets 16 片・31 回のコンパイルで期待と違う 0、textlint エラー 0・警告 0
- 使った出典：trap.jp（2 記事。check_noai で noai・noimageai の指定がないことを確かめた：新しいドメイン）、github.com（maspy・Nyaan・ei1333 の雛形、verification-helper、ACL の document_ja）、gcc.gnu.org（Optimize Options・Function Specific Option Pragmas）、cpprefjp（モジュール：名前付きモジュールはマクロを持ち込まない）
- 見出しの表記：bits-stdcpp の見出しは `<bits/stdc++.h>` がタグと解釈されないよう、その部分をバッククォートで囲んだ（cpp-integer-overflow と同じ扱い）。title は変えていない
- 図：catalog の visual（static・priority 2）を SVG で作った（main.cpp とヘッダから 1 ファイルができる流れ。@impl の上下の行き先）。描画の道具が手元になく、目で見た確認はしていない（座標の重なりは計算で避けた）。レビューで表示を確かめてほしい

## 台帳への提案

- なし（catalog の problems_note のとおり、C++ のページには問題を置かない）

## 用語集への提案

- マクロ｜macro｜コンパイルの前にプリプロセッサが行う文字の置き換え（`#define`）。型や変数の有効範囲を知らないので、引数の 2 回評価や括弧の不足で事故が起きる
- 雛形｜template-file｜毎回の提出の先頭に貼る定型のコード（`#include`・マクロ・補助の関数など）。C++ の template（関数テンプレート）とは別の意味だが、どちらも「テンプレート」と呼ばれる
- 展開（バンドル）｜bundling｜`#include "..."` で読む自作のヘッダの中身を埋め込み、提出できる 1 ファイルにすること
- 短絡評価｜short-circuit-evaluation｜`&&` は左が偽なら、`||` は左が真なら右を評価しないこと（chmax の `a < b && (a = b, true)` で使う）

## 手引きへの提案

- 本文にシェルのコマンドを載せるときの書き方を決めてほしい。このページでは `import std;` の std モジュールを作るコマンドを ```` ```bash ```` で書いた（§2.7 が禁じるのは ```` ```cpp ```` だけと読んだ）
- `import std;` を使うコード片は、std モジュールを先に作る手順が check_snippets にないので確かめられない。本文の主張（INT_MAX・assert が使えない、`#include` を前に書けば使える、モジュールを作っていないと `failed to read compiled module`）は scratchpad で手で確かめた。必要なら check_snippets に「前処理のコマンド」の項目を足す案がある

## 問題の補充の候補

- なし（C++ のページには問題を置かない方針）

## 未解決の点

1. AtCoder で `import std;` が通るかは確かめていない。AtCoder の GCC に `-fmodules` が付くこと（decisions.md）と、traP の記事が GCC の対応を partial としていることだけを書き、本文には「この教材では確かめていない」と書いた。catalog の節の title の「（C++23・GCC 15〜）」は手元の g++-15 で通ることに基づく
2. research/09 §4.18 の maspy の `FOR` は「5 番目の引数を選ぶ」とあるが、本文の例は自分で書いた形（候補を後ろに並べて 4 番目を選ぶ）にした。maspy の雛形の文章・コードは写していない
3. `printf("%d")` に `long long` を渡して `-1294967296` と出たのは手元の観測で、規格上は未定義動作である。コード片（define-int-printf）は警告が出ることだけを期待にした
4. cph の「提出用にコピー」の挙動（探す場所・印・`#ifdef LOCAL` の中の扱い・目印が `#if` の中なら警告）は research/09 §6.6（cph-fork.patch を読んだ結果）によった。cph のフォーク自体は手元で動かしていない
5. `#include <bits/stdc++.h>` でコンパイルが「1〜3 秒ほど長くなる」は research/09 §4.2・§4.5 の計測（PCH なし 1.1〜2.7 秒）からの目安である
6. 名前の衝突の一覧（next・prev・distance・data・size・j0・j1）は、グローバルの int 変数にして g++-15 でエラーになることを確かめた（snippets には count と y1 だけを置いた）

## 検証の指摘への対応

- 1〜10 は直した（7 はエラーになる例 `<vector>`・`<cmath>` で言う形にした。9 は表の最後の行を外し、「避け方」に移した。10 は `#pch`・`#judge-macros`・`#march-native` へのリンクにした）
- 11（図をスマホの幅で読みやすくする）は採らなかった。検証役も「急がない」とし、内容は正しく、ライトの表示で読める。描画の道具が手元になく、配置を組み替えると目で確かめられないため、今回は見送る。印の簡略化は本文の説明どおりなのでそのままにした
