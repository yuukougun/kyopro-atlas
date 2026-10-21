# warshall-floyd の報告（工程8b・バッチ b1）

- 書いたファイル：docs/graph/warshall-floyd.md、snippets/warshall-floyd/wf.{cpp,yaml}（初期化・3 重ループ・負閉路の判定）、snippets/warshall-floyd/add-edge.{cpp,yaml}（無向辺の O(N^2) の追加。main で毎回、最初から計算し直した表と assert で突き合わせ）、docs/img/warshall-floyd/example-graph.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21 のまま）。sections に 1 節を足した：`{title: 距離以外の値を同じ形で求める（到達可能性・ボトルネック・2 つの基準）, anchor: beyond-distance}`（level はページと同じ水。練習 abc143_e の 2 段階の型と、推移閉包・ボトルネック・辞書順の組の型をまとめる受け皿）
- 検査の結果：check_pages（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、check_snippets（2 片・期待と違う 0）、textlint（エラー 0・警告 11。数式を含む文の長さ、要点の入れ子の箇条、助詞「が」「で」「は」の重複で、読みやすさを確かめて残した）
- 数値の確かめ：本文の例のグラフ（4 頂点・5 本の有向辺）の k ごとの表と最後の表、i-j-k の順で回したときに d[0][1] が 5 のまま残ること、6 頂点の完全グラフ（全辺 −1）でループ後の最小値が −5184 になることは Python で計算した。add_edge のその場での上書きは、ランダムな小さいグラフ 300 件で全体の再計算と一致を確かめた（scratchpad での試験。snippet の中にも assert がある）
- 図：静的な SVG 1 枚（例のグラフ。最短路 0 → 3 → 2 → 1 を太い破線と色で示す）。描画の道具が手元になく、見た目は目で確かめていない。検証役に描画の確認を頼みたい

## 事故の報告（fix_problems の範囲）

`python3 tools/fix_problems.py --page warshall-floyd --field graph` を実行したところ、`--field graph` が効いて担当外の docs/graph/time-dependent-dijkstra.md の 3 行（abc192_e・abc342_e・abc204_e の ID だけの行）まで書き換えた。直後に、その 3 行だけを元の「問題 ID：要約」の形に戻した（ほかの行には触れていない）。その後の全体の `--check` は 0 件で、別の執筆者が自分で直したとみられる。今後の指示では `--page <id>` だけを使う（`--field` を付けない）よう手引きに書くとよい（下の提案）。

## 動く図（priority 1）の仕様

本文の k-outer の節に置き場の div を書いた：`<div class="kp-viz" data-viz="warshall-floyd" data-config='{"n": 4, "directed": true, "edges": [[0, 1, 5], [0, 3, 1], [3, 2, 1], [2, 1, 1], [1, 0, 2]]}'></div>`

- 左に小さいグラフ（頂点の配置は SVG と同じ：0 左上・1 右上・2 右下・3 左下）、右に N × N の距離の表を置く
- 最初のステップは辺だけの表（対角 0、辺のない組は ∞）。続けて k = 0, 1, …, N − 1 の各段で、k 行目と k 列目を「中継点」の色で光らせ、グラフの頂点 k も強調する
- 各段の中で (i, j) を 1 マスずつ（または変わるマスだけ）進め、caption に `d[i][j] = min(d[i][j], d[i][k] + d[k][j])` の数値を出す。値が変わったマスは別の class（`.kp-v-*`）で示す
- 本文に書いた各段の変化：k = 0 で d[1][3] = 3、k = 1 で d[2][0] = 3・d[2][3] = 4、k = 2 で d[3][1] = 2・d[3][0] = 4、k = 3 で d[0][2] = 2・d[0][1] = 5 → 3・d[1][2] = 4。最後の表は本文の表と一致すること（試験に入れるとよい）
- 余力があれば、「i-j-k の順」に切り替えるモードを付け、d[0][1] が 5 のまま残る様子を見せる（確認問題の答えと対応）
- 図の前後の文章は本文に書いた（図がなくても通じる）

## 使った出典

- はまやんはまやんはまやん（abc079_d・abc208_d・abc073_d）、Lanly の cnblogs（abc375_f）、E869120 の典型 90 問 087 の想定解（GitHub）、競プロはじめました（abc243_e）、kmjp（abc143_e）、プログラミング広場（abc338_f）：URL はページの参考の節のとおり。例題・練習・力試しの問いと方針をそれぞれ確かめた
- Lanly の abc338_f の記事は、本文ではなく集合ごとにダイクストラ風の緩和をする解き方で、ワーシャルフロイド法は代案として触れるだけだった。ワーシャルフロイド法＋bitDP の裏付けは、台帳の evidence にあるプログラミング広場の記事で取った
- 補充の候補の確認に読んだもの：プログラミング広場の abc369_e・abc286_e の記事、KCPC ブログの ABC416 の記事（下記）
- 新しく noai を確かめたドメイン：kcpc.hatenablog.com（`tools/check_noai.py` で noai・noimageai の指定なし。meta robots は max-image-preview:large だけ）。付録 B のはてなブログの一覧への追加を提案する
- programming-hiroba.com/abc416-e/ は 404 だった

## 台帳への提案

- abc079_d・abc208_d・abc375_f・abc073_d・typical90_ci・abc243_e・abc143_e｜checked｜2026-10-21｜各 evidence で問いと方針を確かめた
- abc338_f｜alternatives の warshall-floyd 向けの summary・approach は確かめた（プログラミング広場）。evidence の kanpurin の記事（2020-04-07）は abc338（2024-01）より古く、別の問題の記事に見える。この問題の裏付けとしては外すのがよい（私は開いていない。日付からの推測）
- abc375_f｜evidence｜Lanly の記事で「都市 300 以下・通行止め 300 回以下」を確かめた。変更は不要

## 用語集への提案

- 負閉路｜negative-cycle｜辺の長さの和が負になる閉路。そこを何周もすると経路の長さがいくらでも小さくなるので、そこを通れる組の最短距離は定まらない（−∞）
- 推移閉包｜transitive-closure｜有向グラフで、i から j へ（辺をたどって）行けるかどうかをすべての組について表したもの
- 本文では用語集へのリンクは張っていない（上の 2 語は本文で説明しているので、足すならメインの判断でリンクを張る）

## 手引きへの提案

- §10 の「行を `- abc340_e：要約` と書いて `python3 tools/fix_problems.py --page <id>` で埋めてもよい」に、「`--field` を付けると分野の全ページを書き換えるので付けない」と添える（上の事故の再発防止）。あるいは fix_problems 側で `--page` と `--field` を同時に渡したら `--page` だけに絞る
- §13.1 の定型の見出しで、使い分けは `## 使い分け {#comparison}` だが、見本の lazy-segment-tree は `{#choosing}`（sections に載せた節）になっている。このページは定型の `{#comparison}` にした

## 問題の補充の候補

catalog の数（例題 3・練習 4・力試し 1）は目安の範囲だが、abc319 以降の問題が abc375_f と abc338_f の 2 問だけで、`recent 0` の根拠も薄いので、最近の ABC の候補を挙げる。

- abc369_e（Sightseeing Tour、diff 1301）：各クエリで指定された K 本（5 以下）の橋をすべて渡って頂点 1 から N へ行く最短時間を求める。全点対の距離を前計算し、橋の順番（K!）と渡る向き（2^K）を全探索する。with-enumeration の節の「通る辺が決まっている」の型の代表で、練習に向く｜https://programming-hiroba.com/abc369-e/
- abc416_e（Development、diff 1428）：道路の追加と空港の設置のクエリを処理しながら、全点対の最短距離の総和を答える。空港を超頂点につなぎ、追加のたびに表を O(N^2) で更新する。add-edge の節の練習に向く（abc375_f と違い、追加そのものが来る型）｜https://kcpc.hatenablog.com/entry/2025/07/28/090000（制約の N・Q の値は記事に書かれておらず、確かめていない）
- abc286_e（Souvenir、diff 1128）：直行便の表とお土産の価値から、各クエリの 2 都市間で、乗る便の数が最小の経路のうちお土産の価値の和が最大のものを答える。（距離, 価値）の組を辞書順で比べるワーシャルフロイド法。beyond-distance の節の練習に向く｜https://programming-hiroba.com/abc286-e/
- arc083_b（Restoring Road Network）は graph-construction の例題なので、redundant-edges の節では問題 ID を出さず、graph-construction へのリンクだけにした（変更の提案ではない）

## 未解決の点

- abc079_d の H・W の上限、abc208_d の辺の長さの上限は、読んだ解説に明記がなく確かめていない。本文では値を書かずに済ませた（abc208_d の N ≤ 400 は解説のコードと記述から）
- 「C++ なら N = 500 でも十分に間に合う」は経験則で、計測はしていない
- 負閉路の判定は「ある i で d[i][i] < 0 ⇔ 負閉路がある」という同値だけを書いた。「d[i][i] < 0 の頂点 i が負閉路の上にある」かどうかは証明を確かめていないので書いていない
- SVG の見た目は未確認（上記）
- 使用量の目安：道具の呼び出し約 45 回、Web 取得 13 回（検索 1 回を含む）

## 検証の指摘への対応（2026-10-21）

- 指摘 1〜6 はすべて直した（採らなかったものはない）
  - 1：#beyond-distance の条件を 2 つ（つなぐ演算が順序を保つ・単純な経路に取れる）にし、積の最大の反例を一言添えた。表の各行の説明に、順序を保つことを一言ずつ足した
  - 2：参考を「プロひろ「ABC338 F問題（Negative Traveling Salesman）を解く」」にした
  - 3：#k-outer と #pitfalls を「見落とすことがある」にした
  - 4：確認問題 3 の答えに「それ以外の組の値は正しい」を添えた
  - 5：「始点の価値は最後に別に足す」を添えた
  - 6：橋の本数を $K$ と書き、$K!$・$2^K$ にした
- 提案（メインへ）：参考のサイト名「programming-hiroba「…」」と「プロひろ「…」」の揺れを、ほかのページでもそろえるとよい（検証の指摘 2 の根拠）
