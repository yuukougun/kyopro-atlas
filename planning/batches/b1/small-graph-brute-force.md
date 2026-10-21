# small-graph-brute-force の報告と提案（工程8b・b1）

- 書いたファイル：docs/graph/small-graph-brute-force.md、snippets/small-graph-brute-force/{isomorphism,spanning-trees,coloring}.{cpp,yaml}、docs/img/small-graph-brute-force/{isomorphism,coloring-order}.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21 のまま）。sections に「上位の手法とのつながり（next-steps）」を足した（level はページと同じ）
- 検査の結果：check_pages エラー 0・警告 0／fix_problems --check 直すべき行 0／check_snippets 3 本とも期待どおり／textlint エラー 0・警告 3（数式を含む文の長さ、折りたたみの箇条書き 1 行、参考の 1 行の長さ。§13.8 の範囲）
- 図：静的な SVG 2 枚（catalog の visual は null なので動く図はない）。SVG を画像に描く道具が手元になく、XML の妥当性と座標の計算だけを確かめた
- 使った出典：参考の節の 4 件（sano192 の Qiita・Lanly の cnblogs・drken・hamayan）。どれも付録 B のドメインで、新しく noai を確かめたドメインはない

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc232_c | summary | 末尾に「。」を足す | bit-full-search の報告と同じ。本文の行は台帳のまま（§13.7） |
| abc371_c | summary | 末尾に「。」を足す | 同上 |
| abc328_e | summary | 末尾に「。」を足す | 同上 |
| abc199_d | summary | 末尾に「。」を足す | 同上 |
| abc199_d | summary（任意） | 「N ≤ 20」は第三者の解説（hamayan）に上限の明記がなく、3^20 への言及から読み取った値。研究メモと台帳の値を信じて本文でも N ≤ 20 を使った | https://blog.hamayanhamayan.com/entry/2021/04/25/002321 |

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| 同型（グラフの） | graph-isomorphism | 頂点数の等しい 2 つのグラフ G・H について、G の頂点を H の頂点へ移す 1 対 1 の対応 p があり、どの頂点の組 {i, j} でも「G に辺 i–j がある」と「H に辺 p(i)–p(j) がある」が同値であることである。頂点の番号を付け替えると一致する、と言い換えられる |
| 全域木 | spanning-tree | 連結なグラフのすべての頂点を含み、閉路のない部分グラフ（木）である。頂点数 N なら辺はちょうど N − 1 本で、N − 1 本の辺で閉路がなければ全域木になる |

（本文ではこの 2 つの anchor でリンクを書いた）

## 手引きへの提案

- 「上位の手法とのつながり」を基礎のページの sections に載せるかどうかが §13.1 から読み取りにくい（binary-search-answer は載せ、bit-full-search は節自体がない）。中身の節として載せる、と明記するとそろう。本ページは載せた

## 問題の補充の候補

| 問題 ID | 何を問うか | 裏付けの URL | 備考 |
| --- | --- | --- | --- |
| abc054_c | N ≤ 8 の無向グラフで、頂点 1 から出発してすべての頂点をちょうど 1 回ずつ通るパスの数を求める（頂点の並びを順列で全部試し、隣どうしに辺があるか確かめる） | https://drken1215.hatenablog.com/entry/2019/09/16/224600 | ap.py で実在を確認（C. One-stroke Path、diff 1244）。台帳にない。題名と検索結果の要約で問いと方針を確かめた（記事本文は未読）。頂点の順列をパスとして読む型で、練習に足すと「対応」以外の順列の読み方が増える。bitDP のページの導入（N が大きければ bitDP）とも結べる |
| abc073_d | 訪れる町 R ≤ 8 個の順番を全部試し、ワーシャルフロイドで求めた距離で経路長の最小をとる | https://blog.hamayanhamayan.com/entry/2017/09/10/002511 | 台帳では確認済み（warshall-floyd の practice、diff 1345）。「距離を前計算して頂点の順列を全部試す」型として本ページの練習に足してもよいが、diff が水なので力試しが妥当 |

## 未解決の点

- ABC328 E の K の上限は、読んだ解説の範囲に書かれていなかった。本文の落とし穴は「重みと K が大きい問題では」と条件付きで書き、足すたびに余りをとる形にした（snippet もそうしている）
- 3 彩色の計算量 O(2^N (N + M)) は、葉の数 3·2^(N−1) と、1 頂点を塗るときに隣の色を調べる手間からの粗い上界である。厳密な見積もりは書いていない
- 「一般のグラフの同型を多項式時間で判定する方法は知られていない」は一般的な事実として書いた（出典は付けていない）。必要なら検証役に確かめてもらう
- 完全グラフの全域木の数 N^{N−2}（Cayley の公式）も出典なしで書いた。行列木定理・Prüfer 列のページが書かれたらそちらへリンクするとよい
- 使用量の目安：道具の呼び出し約 30 回、Web 取得 6 回（WebFetch 5・WebSearch 1）＋題名の確認 4 件（curl）
