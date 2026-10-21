# bfs（幅優先探索（BFS）と無重み最短路）の報告と提案

- 書いたファイル：docs/graph/bfs.md、snippets/bfs/path.{cpp,yaml}、snippets/bfs/multi-source.{cpp,yaml}、docs/img/bfs/layers.svg
- front matter で変えたもの：complexity（`O(N+M)（グリッドは O(HW)）`）・stage（draft）・updated。sections の weighted の title を「…01-BFS かダイクストラ法」に（見出しの用語を正規形にそろえた）
- 検査の結果：check_pages エラー 0・警告 0、fix_problems --check 0、check_snippets 期待と違う 0、textlint エラー 0・警告 5（要点の 1 行目は summary の写しで助詞の重複、数式を含む箇条の読点の数、解法の詳細の 1 文の長さ、問題の要約と力試しの方針の「に」の重複。どれも意味を変えずに直すと読みにくくなるので残した）
- 動く図：置き場の div（`data-viz="bfs-layers"`）と前後の文章だけ書いた。config は静的な図 layers.svg と同じグラフ（labels・edges・source）。仕様：キューの中身と、頂点を距離の層ごとに色分けして同時に表示し、1 ステップで 1 頂点を取り出す。隣を見つけた瞬間（push のとき）に距離を書き込み印を付けることを強調し、キューの中の距離が 2 種類（d と d+1）までであることを caption で示す。par の辺を太くしていくと path-restoration にもつながる
- 事実の確認：pop で印を付けて読み飛ばさない BFS の push の回数は、手元のシミュレーションで確かめた（12×12 の床のグリッドで全体 2,704,155 回、右下のマスは 705,432 回 ＝ C(22, 11)）

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc007_3 | summary | 壁と通路からなる迷路で、スタートのマスからゴールのマスまで上下左右に進むときの最小の移動回数を求める。 | https://drken1215.hatenablog.com/entry/2023/06/11/123536 |
| abc383_c | summary | 床・壁・加湿器のマスからなるグリッドで、どれかの加湿器から壁を通らずに D 歩以内で行ける床のマスの数を求める。 | https://www.cnblogs.com/Lanly/p/18606772 |
| abc168_d | summary | 無向グラフの各部屋に、部屋 1 へ最短で向かうために次に進む部屋を道しるべとして置き、その置き方を出力する。 | https://blog.hamayanhamayan.com/entry/2020/05/17/224335 |
| abc160_d | summary | 1 列に並ぶ N 頂点に近道の辺を 1 本足したグラフで、距離が k の頂点の組の数を k ごとに求める。 | https://blog.hamayanhamayan.com/entry/2020/03/29/000745 |
| abc151_d | summary | 迷路の通路のマス 2 つを選ぶとき、その間の最短の移動回数の最大値を求める。 | https://blog.hamayanhamayan.com/entry/2020/01/12/225950 |
| agc033_a | summary | 黒マスに隣接する白マスをすべて黒にする操作を、全体が黒になるまで繰り返すときの操作の回数を求める。 | https://blog.hamayanhamayan.com/entry/2019/05/05/000255 |
| abc460_d | summary | 白黒のグリッドで、全マスを同時に「黒は白に、8 近傍に黒がある白は黒に」塗り替える操作を 10^100 回繰り返した後の色を求める。 | https://dev.to/iwamutsu256/atcoder-beginner-contest-460-can-jia-ji-lu-tojie-da-li-a-dwen-ti--3jk2 （塗り替えの規則が書いてある） |
| abc460_d | evidence | 上の dev.to の記事を追加 | 同上 |
| abc460_d | note | 規則の細部は dev.to の記事で確かめた（comet725 の記事には規則がない） | 同上 |

台帳の summary は末尾の「。」がないものが多い（abc007_3 など）。本文の行は上の表の文に揃えた。

## front matter への提案

- signs の「最短経路を 1 つ出力する・次に進む頂点を答える」を「最短路を 1 つ出力する・次に進む頂点を答える」に（prh が「最短経路 → 最短路」をエラーにする。本文の要点の囲みは直した）。summary にも「経路を復元」とあるがこれは prh に掛からない
- aliases の「最短経路の復元」は別名の行（textlint 外）なのでそのままでよいが、prh と揃えるなら「最短路の復元」「経路復元」を検討

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| 最短路木 | shortest-path-tree | 始点から各頂点への最短路を 1 本ずつ選び、それらの辺を合わせてできる、始点を根とする木である。BFS やダイクストラ法で、各頂点を見つけたときの親（par）への辺を集めると得られる。 |
| 超頂点 | super-vertex | 問題のグラフにない頂点を 1 つ足し、複数の頂点との間に辺を張ったもの。多始点の最短路を 1 回の探索に直したり、辺の数を減らしたりするのに使う。（extended-dijkstra#super-vertex に節があるので、用語集はそこへの案内でもよい） |

本文では用語集へのリンクは張っていない（超頂点は extended-dijkstra#super-vertex へ張った）。

## 手引きへの提案

- §2.3「節の level」の運用で、基礎のページの「重みの節」のように上位の手法（01-BFS・ダイクストラ法）を表で紹介する節は level を付けずに済ませた。上位の手法の紹介だけなら level 不要、と明記するとよい
- prh が「最短経路」をエラーにするので、付録 A のグラフの項に「最短路（最短経路は使わない）」と書くと執筆者が迷わない
- 動く図の置き場の div を先に書く場合、config の形は JS を作るときに変わりうる。「div の config は仮で、JS の作成時に直してよい」と書いておくとよい

## 問題の補充の候補（問題ID・何を問うか・裏付けの URL）

台帳の確認済みの問題で数は足りている（例題 1・練習 5・力試し 1）。補充の候補は次のとおり（ap.py で存在を確認するのはメイン側で）：

- abc211_d（確認済み・shortest-path-dag の例題）：最短路の本数。本ページでは shortest-path-dag へのリンクだけにした。練習に入れる必要はない
- abc472_d（確認済み・grid の練習、summary 未確定）：多始点 BFS の型と分類されている。summary が「（執筆時に確かめる）」のため使わなかった。grid-graph の執筆時に確かめる

## 未解決の点

- abc160_d の練習の方針の「各頂点から BFS しても O(N^2)」は、辺が N 本なので BFS 1 回 O(N) × N 回。hamayan の記事は式で解く方法で、全始点 BFS の方は記事にない（計算量は自明なので書いた）
- abc151_d の H, W ≤ 20 は research の記述と記事のコード（配列 20）から。記事の本文には数値がない
- agc033_a の H, W ≤ 1000 程度は本文に書いていない（記事に明記がないため）
- 新しく noai を確かめたドメイン：dev.to（noai・noimageai の指定なし。iwamutsu256 の記事）、note.com の nakahide248 の記事（指定なし。利用条件は記事を読まなかったので未確認、使っていない）。付録 B に dev.to の追加を提案
- 使用量の目安：道具の呼び出し 約 35 回、Web 取得 9 回・検索 1 回
