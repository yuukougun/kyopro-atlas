# coordinate-compression の報告（工程8b・バッチ b1）

- 書いたファイル：docs/basics/coordinate-compression.md、snippets/coordinate-compression/compress.{cpp,yaml}・covered-length.{cpp,yaml}、docs/img/coordinate-compression/mapping.svg・intervals.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21 のまま）。sections に「BIT・セグメント木・いもす法と組む（with-ds）」を足した（summary の「BIT・セグ木・いもす法と組んで使う」と、基礎のページの「上位の手法とのつながり」に当たる節。level はページと同じ）
- 検査の結果：check_pages（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、check_snippets（2 片・期待と違う 0）、textlint（エラー 0・警告 12。数式 `$[l, r)$` の括弧の対応の誤検出、数式を含む文の長さ、要点の summary の文の「に」の重複など）
- 図：catalog の visual（static・priority 2）の「元の値と圧縮後の番号の対応表」を mapping.svg にした。区間の両端点と基本区間の長さを示す intervals.svg を足した。動く図は作っていない。SVG は手元に描画の道具がなく、座標の計算で文字のはみ出しを確かめただけなので、検証で見た目を確かめてほしい

## 使った出典

- drken（hatenablog）ABC213 C・ABC036 C・ABC113 C：例題と練習の方針（行と列の独立な圧縮、3 段の手順、県ごとの二分探索、ABC113 C の 6 桁の 0 埋め）
- Reputeless/tenkei_90 の 029.md と E869120/kyopro_educational_90 の sol/029-02.cpp（github.com）：Long Bricks で L−1 と R（半開区間）を圧縮すること、圧縮だけの解は最悪 O(N^2)（部分点）で満点は区間の処理にセグ木が要ること
- zenn.dev/m193h の ABC231 の記事：補充の候補 abc231_f の裏付け
- 新しく noai を確かめたドメイン：なし（すべて付録 B のドメイン）

## 台帳への提案

- typical90_ac｜evidence｜https://github.com/E869120/kyopro_educational_90/blob/main/sol/029-02.cpp を足す｜圧縮する値（L−1 と R）と、圧縮だけでは O(N^2) になることの裏付け。Reputeless の 029.md は解答のコードだけで説明が少ない
- typical90_ac｜coordinate-compression での役割｜practice のままでよいが、満点には遅延セグメント木が要るので、本文の方針では「圧縮だけでは部分点」と書いた。challenge に移す案もある（基礎のページの練習としては重い）

## 用語集への提案

- オフライン｜offline｜クエリをすべて先に読んでから、答えやすい順に処理してよい状況。前の答えで次のクエリが決まる（オンラインの）問題では使えない。（本文で `../guide/glossary.md#offline` にリンクした）
- 基本区間｜elementary-interval｜区間の端点をすべて並べたとき、隣り合う 2 つの端点の間の部分。どの区間にとっても、全部入るか全く入らないかのどちらかになる。（本文では節の中で定義し、リンクはしていない。いもす法・イベントソート・平面走査のページでも使うなら用語集へ）

## 手引きへの提案

- §13 に「区間を座標圧縮するページ（imos・event-sort・lazy-segment-tree など）は、閉区間を半開区間 [l, r+1) に直してから両端点を入れる書き方にそろえる」を足すと、ページの間で書き方がぶれない

## 問題の補充の候補

catalog の数（例題 1・練習 3）で足りており、力試しは 0。どれも台帳では確認済みで、ほかのページの持ち物なので、このページには役割の追加の提案になる。

- abc231_f（F. Jealous Two、diff 1580）｜A_i ≥ A_j かつ B_i ≤ B_j となる組の数を求める。B を圧縮して BIT で数える｜https://zenn.dev/m193h/articles/20211212sun001912m193habc231｜役割：challenge（with-ds の節の「値の大小で数える」の代表。台帳では fenwick-tree の practice）
- abc221_d（D. Online games、diff 832）｜ログイン期間からちょうど k 人がログインしていた日数を k ごとに求める。端点を圧縮していもす法｜https://oraclesqlpuzzle.ninja-web.net/kyoupro/05-atcoder-02-abc/kyoupro-abc221-d.html｜役割：practice（intervals・keep-original の節の型そのもの。台帳では imos の practice）

## 未解決の点

- frequency_evidence の recent に挙がる abc467_f は台帳の summary が「（執筆時に確かめる）」で、exchange-argument の challenge になっている。このページでは使っていない
- 本文の「値の隙間に意味がある問題」（覆われない最小の整数）は型だけで、台帳の問題は付けていない
- catalog の research では prerequisites に sorting-techniques もあったが、front matter は binary-search だけ。変えていない

## 使用量の目安

- 道具の呼び出し約 25 回、Web 取得 7 回（drken 3・github 3・zenn 1）

## 検証の指摘への対応

- 直すべき 1〜4、直すとよい 6〜12 を直した。6 はコード片 covered-length の変数名 `xs` を `vals` にそろえ、本文も vals に統一した（#intervals で「3 段の節と同じく vals と呼ぶ」と定義）。12 は compress に全対の大小の assert、covered-length に座標が ±1000 以内のときの素朴な数え上げとの比較を足した
- 採らなかったもの：5（#vs-map を `## 使い分け {#comparison}` にする）。vs-map は骨格由来の anchor で、§2.1 の「既存の anchor は変えない」とぶつかり、docs/index/basics.md からも `coordinate-compression#vs-map` で参照されている。どちらに寄せるかはメインの判断に任せる
- 提案（メイン）：#vs-map を残すなら「骨格由来の使い分けの節は anchor を保つ」旨を決定事項に書く。寄せるなら anchor を comparison に変え、docs/index/basics.md の参照を直す
- textlint の警告は 15（数式の括弧の誤検出と文の長さ。エラー 0）
