# tree-imos の執筆の報告（工程8b・b1）

- 書いたファイル：docs/tree/tree-imos.md、snippets/tree-imos/subtree-add.{cpp,yaml}、snippets/tree-imos/path-add.{cpp,yaml}、docs/img/tree-imos/marks-and-sweep.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21 のまま）。sections は変えていない
- 検査の結果：check_pages エラー 0・警告 0／fix_problems --check 直すべき行 0／check_snippets 期待と違う 0（2 片）／textlint エラー 0・警告 15（数式を含む文の「に」の重複・長さ、代替テキストの `[1, 4)` の括弧の対応、参考の行の長さなどの誤検出）
- 使った出典：drken ABC187 E（https://drken1215.hatenablog.com/entry/2021/01/03/162800）、drken ABC138 D（https://drken1215.hatenablog.com/entry/2020/05/18/174000）、hamayan ABC222 E（https://blog.hamayanhamayan.com/entry/2021/10/10/142820）。新しいドメインはなし
- 図：catalog の visual は priority 2・static なので、静的な SVG（配列のいもす法と木の部分木加算の「印 → 累積」を上下に並べたもの）にした。動く図は作っていない

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠の URL |
| --- | --- | --- | --- |
| abc138_d | 追加（status 確認済み、pages: tree-imos・practice） | summary：頂点 1 を根とする木で、部分木の全頂点に x を足す操作を繰り返した後の、各頂点の値を求める。／approach：部分木の根に印を足し、最後に根から下へ累積する | https://drken1215.hatenablog.com/entry/2020/05/18/174000（ap.py：D. Ki、diff 920） |
| abc309_e | pages に {id: tree-imos, role: practice} を足す（tree-traversal の練習は残す） | 「根から y 世代まで」の節の代表。summary はそのまま | https://qiita.com/ZOI_dayo/items/a55cc4342832efdc23ba（台帳の evidence） |
| abc187_e | summary の末尾に「。」を足す | 木の辺 i = (a_i, b_i) について「a_i から b_i を通らずに行ける頂点すべてに x を足す」型のクエリを処理した後の、各頂点の値を求める。 | 表記の規則（ほかの行は句点で終わる） |
| abc222_e | alternatives（tree-imos）の summary の末尾に「。」を足すか、本体の summary に統一する | 本体の summary（句点あり）と同じ文でよい | 同上 |

- abc138_d を足すなら、基礎の例題の位置にも合う（diff 920）。ただし例題は基礎で 1 問の目安なので、abc187_e を例題のまま、abc138_d を練習の先頭に置く案にした。逆（abc138_d を例題、abc187_e を練習）もあり得るので、メインが決める

## 用語集への提案

- なし（オフライン `#offline` だけを使った。既存）

## 手引きへの提案

- なし

## 問題の補充の候補

| 問題 ID | 何を問うか | 裏付けの URL |
| --- | --- | --- |
| abc138_d（D. Ki、diff 920） | 部分木への加算を繰り返した後の各頂点の値（部分木加算の基本形） | https://drken1215.hatenablog.com/entry/2020/05/18/174000 |
| abc309_e（E. Family and Insurance、diff 957、台帳にあり） | 家系図で y 世代先までの子孫に及ぶ保険に入っている人数（max を下へ伝える形） | https://qiita.com/ZOI_dayo/items/a55cc4342832efdc23ba |

- パスへの加算（青の節）の代表の ABC の問題は見つけていない（abc222_e は素朴な方法でも通る）。台帳に既にある問題で「多数のパスに +1 して各頂点・各辺の回数」を問うものがあれば、練習か力試しに足したい

## 未解決の点

- 「根から y 世代まで」の節で、数える形（何個のクエリが届くか）は root-path-dfs（まだ骨格）へリンクした。root-path-dfs の本文でこの形を扱うか、メインが確かめてほしい
- 「途中で値を聞かれる」節の「パスへの加算・一点の取得は、4 つの印を BIT に置いて部分木の和で読む」は自分で導いたもので、snippet では確かめていない（オフライン版の正しさの表と同じ理屈）。検証役に確かめてほしい
- 使用量の目安：道具の呼び出し 約 25 回、Web 取得 3 回

## 検証の指摘への対応

- 1（直すべき）：#online-queries の「パスへの加算・一点の取得」と累積の向きの対応の段落を #path-add の末尾へ移し、#online-queries からは 1 行で送るだけにした
- 2：1 つ目の項目に「位置 in[v] までの和は祖先に置いた印の和」と、out[p] = N のときの扱いを足した
- 3：リンクの文字を「p_i < i の木」にし、文を漸化式の直後へ移した
- 4：図を幅 460 の縦並び（配列は印の行と累積の行を上下に、木は 2 つ横並び）に作り直し、段の間を空けた。Windows の Chrome で画像にして確かめた。パスへの加算の小さな図は足していない（priority 2 で必須でなく、表で印の届き方を示しているため。後のバッチで足してよい）
- 5：ページの直しは要らない。用語集への提案を下に書いた
- 6：落とし穴の文を「部分木への加算の印を葉から上へ累積すると、根から p までのパスに届く」と具体的にした
- 7：使い分けの表の 4・5 行目を「途中で何度も（一点の値）」「途中で何度も（パスの最大値・パスの和）」にそろえ、#path-add へリンクした

## 用語集への提案（追記）

- 「オフライン｜offline」（`docs/guide/glossary.md#offline`）は見出しがまだない。メインが足すときに、このページ（#online-queries）を参照元に入れてほしい
