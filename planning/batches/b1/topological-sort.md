# topological-sort（トポロジカルソート）の報告と提案

- 書いたファイル：docs/graph/topological-sort.md、snippets/topological-sort/{kahn-lex,dfs-order,peel-sinks,acl-scc}.{cpp,yaml}、docs/img/topological-sort/{dag,cycle}.svg（SVG は手で座標を決めた生成。白背景・テキストのまま・viewBox あり。描画の目視はしていない。生成スクリプトは一時置き場）
- front matter で変えたもの：complexity（`O(N+M)（辞書順最小にするなら O(N log N + M)）`）・stage（draft）・updated。sections は変えていない
- 検査の結果：check_pages エラー 0・警告 0、fix_problems --check 0、check_snippets 期待と違う 0（4 片）、textlint エラー 0・警告 0
- 動く図：作っていない（visual は priority 2）。代わりに静的な図 2 枚（DAG と入次数、閉路で止まる例）と、Kahn 法の手順の表を本文に置いた。後で動く図を作るなら、dag.svg と同じグラフ（辺 5→2・5→4・3→4・4→1・2→1・4→6）で、入次数の表とキューを並べたステップ送りにし、最後に cycle.svg のグラフで残る頂点（閉路の 3 頂点＋閉路の先の 1 頂点）を示すとよい
- 使った出典：drken（abc223_d）、kyo-pro（abc315_e・abc245_f）、hamayan（abc216_d）、E869120 の GitHub（typical90_bs）、programming-hiroba.com（abc291_e。付録 B にあるドメイン）、ACL document_ja/scc.md。新しく noai を確かめたドメインはない

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc216_d | approach | 色を頂点にし、同じ筒で色 c が色 d のすぐ上にあれば辺 c→d とみる。一番上の色がそろった色から取り出す（入次数 0 から処理する）シミュレーション | https://blog.hamayanhamayan.com/entry/2021/08/29/230959 （記事はキューのシミュレーションとして説明し、トポロジカルソートには触れていない。グラフへの対応は執筆者の考察） |
| abc216_d | checked | 2026-10-21 | 同上で問いと方針を確かめた |
| abc223_d・abc315_e・abc216_d・abc245_f・typical90_bs | summary | 末尾に「。」を付ける（本文の行は台帳のままにした） | 表記の統一（bfs の報告と同じ指摘） |
| typical90_bs | note | 071-03.cpp のコメントの計算量は O((N+M+K)K)。制約の数値（N・M・K の上限）は第三者の資料で確かめていない | https://github.com/E869120/kyopro_educational_90/blob/main/sol/071-03.cpp |

drken の abc223_d の記事のコードは `G[B].push_back(A)` も足しているように読めた（WebFetch の要約による。記事の本文の方針は正しい）。本文は方針だけを参考にした。

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| DAG | dag | 閉路のない有向グラフ（directed acyclic graph）。頂点をトポロジカル順に並べられ、その順に DP ができる。（dp-dag もこの anchor で張っている） |
| 入次数 | in-degree | 有向グラフで頂点に入る辺の本数。出る辺の本数は出次数（out-degree）という。自己ループは入次数と出次数に 1 ずつ数える。 |

## 手引きへの提案

- なし

## 問題の補充の候補

| 問題 ID | 何を問うか | 裏付けの URL |
| --- | --- | --- |
| abc291_e（E. Find Permutation、diff 1069） | 大小関係の情報から順列が一意に決まるかを判定し、決まるなら復元する。Kahn 法でキューに 2 個以上入ったら一意でない（または最長路の長さが N−1 か）。unique の節の練習に向く | https://programming-hiroba.com/abc291-e/ |
| dp_g（EDPC G. Longest Path） | DAG の最長路。台帳にはあるので、to-dag-dp 節から参照するなら dp-dag の例題として本文でリンク（このページには載せていない） | 台帳の既存の evidence |

abc291_e は本文の unique の節で問題 ID を出さず型だけを書いた（手引き §13-6）。台帳に入れば練習に足したい。

## 未解決の点

- 本文の SVG はブラウザで目視していない（環境に描画の道具がない）。文字の重なりがないか、メインか検証役が確かめてほしい
- 「番号の小さい頂点をできるだけ前に置く」の解き方（辺を逆にして大きい順に末尾から）は lexicographic-greedy#topological の記述に合わせ、ここではリンクだけにした
- cycle-detection の節 kahn-leftover は stub なのでリンクしていない（ページへのリンクだけ）。draft になったら「残った頂点」の段落から節へ張るとよい
- frequency_evidence の abc478_e は scc の練習で、このページには載せていない（catalog のとおり）

## 検証の指摘への対応（verify/topological-sort.md）

- 1（直すべき）：(b) で直した。導入の宣言を「図・表・確認問題では頂点を 1 から番号付けし、コードでは入力から 1 を引いて 0-indexed で持つ」に変え、確認問題（#unique）の頂点を 1〜3 に振り直した（辺 3→1・1→2・3→2、答え 3, 1, 2 と 3, 2, 1）
- 2（直すべき）：典型90 071 の方針の最後を「見つかった並びが K 個に届かなければ −1 を出す（閉路があれば 1 個も作れない）」に直した
- 3〜6・8：指摘の直し方のとおりに直した（6 は cycle-detection#kahn-leftover へ節のリンクを足した）
- 7：cpp-environment は stub なので、ページへのリンク（`../cpp/cpp-environment.md`）に変えた。メインへの申し送り：cpp-environment が draft になり `#stack-depth` ができたら節へ張り直す
- 採らなかったもの：なし

## 台帳への提案（検証を受けて追加）

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| typical90_bs | note | 順が K 個未満でも −1（閉路のときだけではない） | https://github.com/E869120/kyopro_educational_90/blob/main/sol/071-03.cpp の最後 `if (answer_list.size() != K)` |
| abc223_d | checked | 2026-10-21 | 検証役が drken の記事で制約 N, M ≤ 2×10^5 を確かめた |
