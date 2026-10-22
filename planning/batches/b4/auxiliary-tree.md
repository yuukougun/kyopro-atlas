# auxiliary-tree の報告と提案

- 書いたファイル：docs/tree/auxiliary-tree.md、snippets/auxiliary-tree/build.{cpp,yaml}、docs/img/auxiliary-tree/original.svg・compressed.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-22）。sections に `{title: 圧縮木で木 DP をするときの要点と学ぶための資料, anchor: usage}` を足した（overview の「ライブラリでの使い方 → 学ぶための資料」の置き場。既存の anchor は変えていない）
- 検査の結果：check_pages エラー 0・警告 0、fix_problems --check 直すべき行 0、check_snippets 期待と違う 0、textlint エラー 0（警告 11 は数式やリンクを含む文の長さ・読点の数・助詞の重なりで、多くは数式の中を数えた誤検出。ABC340 G の要約の「で」の重なりは台帳の直しで消える）
- 図：静的な SVG 2 枚（元の木と最小の部分木・圧縮木と縮めた辺の長さ）。render_svg で 360px・720px を目で確かめた。visual は priority 2・static なので動く図は置いていない
- 新しく noai を確かめたドメイン（どれも指定なし）：ngtkana.hatenablog.com（blog.ngtkana.com へ転送）、smijake3.hatenablog.com、tjkendev.github.io（読んだが参考には入れていない）、not-leonian.hatenablog.com（記事は削除済みで使っていない）

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc340_g | summary | 各頂点に色が付いた木で、頂点の空でない部分集合のうち、誘導部分グラフが木になり、次数 1 の頂点の色がすべて同じものの個数を 998244353 で割った余りを求める。 | https://kmjp.hatenablog.jp/entry/2024/02/10/0930（問題の要約と、単独の頂点を N 個足す解答コード） |
| abc340_g | evidence に追加 | https://kmjp.hatenablog.jp/entry/2024/02/10/0930 | 問いとマージテクの解法 |
| abc340_g | checked | 2026-10-22 | ngtkana・kmjp の記事で確認 |
| abc359_g | evidence に追加 | https://kmjp.hatenablog.jp/entry/2024/06/23/0930 | 平方分割の解法（多い色は辺の寄与、少ない色は組の総当たり） |
| typical90_ai | checked | 2026-10-22 | E869120 の 035-04.cpp で、DFS 順に並べて隣り合う 2 点（最後と最初も）の距離の和の半分を答えることを確認 |

- abc340_g の summary は本文の行を「…同じになるものの個数を…余りで求める」と書いた（fix_problems が残した自分の要約）。台帳には上の形（「で」の重なりをなくしたもの）を入れ、fix_problems を流してほしい
- abc359_g の auxiliary-tree 向け approach「色ごとに Auxiliary Tree を作り、辺の寄与で数える方法がある」は本文の方針と合っている（圧縮木の辺 (p, v) で s(k − s) × 辺の長さ）

## 用語集への提案

- 誘導部分グラフ｜induced-subgraph｜頂点の部分集合を選び、両端がともに選んだ頂点である辺をすべて残してできるグラフ。（ABC340 G の要約で使う。用語集にあればリンクする）
- 圧縮木の語自体は Auxiliary Tree のページの別名なので用語集には要らない

## 手引きへの提案

- §4 の overview の構成「ライブラリでの使い方 → 学ぶための資料」の置き場として、sections に中身の節を足してよいかを明記してほしい（今回は `usage` を足した。wavelet-matrix も `usage` の節を持つ）
- Library Checker に専用の問題がない手法では「専用の問題はなく、部品（LCA など）の問題で検証する」と書けばよい、という例を §13-10 に添えるとよい

## 問題の補充の候補

- 確認済みの問題で例題 2・練習 1 がそろったので、補充は必須ではない
- 候補（未確認。台帳には書いていない）：クエリごとに指定頂点の集合が与えられ、圧縮木の上で木 DP をする ABC の問題があれば練習に足したい。ap.py では題名から手法が分からず、第三者の解説で Auxiliary Tree を使うと確かめた ABC の問題を今回は新たに見つけられなかった

## 未解決の点

- ABC340 G の問いの「誘導部分グラフが木になる（連結である）」は、kmjp 氏の要約（「部分誘導グラフのうち、葉となる点の色がすべて一致する」）と解答コード（連結な集合を最も浅い頂点で数える DP）から判断した。問題文そのものは開いていないので、検証役に第三者の解説でもう一度確かめてほしい
- 本文の ABC340 G の DP（f(v) と「最も浅い頂点で数える」式）は、kmjp 氏の解答コードの更新式 M[cur][a]·b + M[cur][a] + b = (1 + x)(1 + y) − 1 と対応することを手で確かめたが、提出して確かめてはいない
- 題名の用語：KEA は "auxiliary tree" の呼び名を推奨しないと書いている。本文の導入で一言触れた。題名は catalog のまま
- 使用量の目安：道具の呼び出し 30 回ほど、Web 取得 14 回ほど

## 検証の指摘への対応

- 指摘 1〜6 はすべて直した（1：折りたたみの証明に $x = a$ の場合を足し「$a$ 自身」を消した。2：確認問題の答えを LCA の関係が壊れる・辺の長さの和が 12 になる形に書き直し、$6 \times 4 / 2 = 12$ を添えた。3：辺がちょうど 2 回通られる理由を 2 文足した。4・5：直し方どおりに書き換えた。6：original.svg の凡例に 2 行目「最小の部分木の辺」「部分木の外の辺・頂点」を足し、高さを 322 にした）
- 採らなかった指摘：なし
