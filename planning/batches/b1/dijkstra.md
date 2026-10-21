# dijkstra の報告と提案（工程8b・バッチ b1）

- 書いたファイル：docs/graph/dijkstra.md、snippets/dijkstra/dijkstra.{cpp,yaml}（取り込み core・path）、snippets/dijkstra/dense.{cpp,yaml}（取り込み core）、docs/img/dijkstra/graph.svg・negative.svg・two-ends.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21 のまま）。sections に `{title: 上位の手法とのつながり, anchor: next-steps}` を足した（level はページと同じ基礎）
- 検査の結果：check_pages --page dijkstra はエラー 0・警告 0。fix_problems --check は直すべき行 0。check_snippets snippets/dijkstra は期待と違う 0（2 本）。textlint はエラー 0、警告 15（同じ助詞の重複がほとんどで、数式を含む文の長さ 1 件。台帳の summary の行（Saving Snuuk）も 1 件含む）
- 図：SVG は手元に描画する道具（rsvg-convert・cairosvg）がなく、目で確かめていない。XML として正しいことと、座標と文字幅の見積もりだけ確かめた。検証役に表示の確認を頼みたい

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc035_d | evidence に追加 | https://oraclesqlpuzzle.ninja-web.net/kyoupro/05-atcoder-02-abc/kyoupro-abc035-d.html | 今の evidence（drken の蟻本の記事）は問題名を挙げるだけで、問いも解き方も書いていない。oraclesqlpuzzle の記事で「元のグラフと逆向きのグラフで町 1 からダイクストラ法、往復を引いた残り時間 × 稼ぎの最大」を確かめた |
| soundhound2018_summer_qual_d | evidence に追加 | https://blog.hamayanhamayan.com/entry/2018/07/09/190130 | 同上。hamayan の記事で「s からの円の距離 ＋ t からのスヌークの距離、後ろからの最小値、初期の所持金から引く」を確かめた |
| abc325_e | approach | (都市, 乗り換えたか) の 2 層のグラフでダイクストラ法（完全グラフなので配列版 O(N^2) が確実） | evidence の drken の記事は 2 層のグラフと O(N^2) 版だけを説明し、「両端からの最短距離を組み合わせる」は書いていない（記事の前半 10 万字で確認）。本文では両端の方法も触れたが、これは自分の導出 |
| abc376_d | approach（任意） | 頂点 1 から BFS し、頂点 1 へ戻る辺 u → 1 について dist[u] + 1 の最小を取る | 辺の重みがないので BFS でよい。Lanly の解説は「順向きと逆向きの BFS の和」の形で解いている。どちらも同じ答え |
| soundhound2018_summer_qual_d | label の表示名 | 下の「手引きへの提案」を参照 | fix_problems の規則で `SOUNDHOUND2018-SUMMER-QUAL D. Saving Snuuk` になり読みにくい |

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| 緩和 | relaxation | 辺 $u \to v$ について、$\mathrm{dist}[u] + w(u, v) < \mathrm{dist}[v]$ なら $\mathrm{dist}[v]$ をその値に下げる操作。最短路のアルゴリズムはどれも緩和の順序の決め方が違う |
| ポテンシャル | potential | 頂点ごとに決める値 $p(v)$。辺の重みを $w(u, v) + p(u) - p(v)$ に付け替えても、2 頂点を結ぶ道の長さの順位は変わらない。負の辺を非負に直すのに使う |
| 最短路の木 | shortest-path-tree | 始点から各頂点への最短路を 1 本ずつ選んで重ねた木。各頂点の距離を最後に更新した辺（prev）を集めると得られる |

本文ではまだ用語集へリンクしていない（使った語：緩和・ポテンシャル・最短路の木・暫定距離）。足したら最初の出現にリンクを張る。

## 手引きへの提案

- interfaces.md §3 の表示名の表に、`soundhound2018-summer-qual` のような企業コンテストの表示名（例：`SoundHound2018 予選`）を足すか、台帳に `label` の上書きを持てるようにする。今の規則では contest id を大文字にするだけで長く読みにくい
- 基礎の technique の目安（§4）にない「上位の手法とのつながり」を、見本と同じく sections に載せる中身の節として扱った。定型の節（§13-1）に `## 上位の手法とのつながり {#next-steps}` を足すかどうか決めてほしい

## 動く図の仕様（priority 1、JS は未作成）

- 名前：`dijkstra`。本文に 2 か所置いた
  1. why-correct：`{"n": 5, "directed": false, "source": 0, "edges": [[0, 1, 4], [0, 2, 1], [2, 1, 2], [1, 3, 1], [2, 3, 5], [3, 4, 3]]}`
  2. negative-edges：`{"n": 3, "directed": true, "source": 0, "labels": ["s", "a", "b"], "edges": [[0, 1, 2], [0, 2, 3], [2, 1, -2]]}`
- states(config)：ヒープ版のダイクストラ法を 1 回の取り出しごとに 1 ステップにする。各状態は `dist`・`done`（確定済みの集合）・`heap`（(距離, 頂点) の組を小さい順に並べた列）・`popped`（取り出した組）・`stale`（古い組として読み飛ばしたか）・`updated`（このステップで更新した頂点と辺）・`caption`
- 1 の caption は本文の表（7 ステップ。4 と 6 が古い組の読み飛ばし）と一致させる
- 2 は「確定済みの頂点の距離が後から縮む」場面を強調する。確定済みの a に対して、b から −2 の辺で 1 が届くステップで「確定済みなのに更新できてしまう」を caption に出す（実装は確定済みでも更新値を表示だけして、印を付ける）
- 描画：頂点（確定済みは塗り、未確定は白）、辺（更新に使った辺は太線）、右にヒープの列（古い組は取り消し線）。色は kp.css の `.kp-v-*` で付け、線の種類でも区別する

## 問題の補充の候補

| 問題 ID | 何を問うか | 裏付け | 備考 |
| --- | --- | --- | --- |
| abc369_e | 指定された K 本（K ≤ 5）の橋をすべて通る、頂点 1 から N への最短時間をクエリごとに答える | https://www.cnblogs.com/Lanly/p/18402027（調査レポート 03-graph §5.2 の裏付け） | ap.py で実在と diff 1301 を確認（台帳には未登録）。頂点間の距離は全点対で前計算するので、dijkstra よりワーシャルフロイド法の練習に向く |

確認済みの問題で役割の数（例題 1・練習 6・力試し 2）は足りているので、補充はしなかった。

## 未解決の点

- 出典で裏付けていない、自分で導いた記述：無向グラフで頂点 s を含む最短閉路を「s につながる辺ごとに、その辺を除いたグラフで距離を求める」方法、全辺に定数を足すと壊れる反例、古い組を読み飛ばさないときの $N^2/4$ の例、abc325_e を両端からの距離で解く方法。どれも短い論証を本文に付けたが、検証役に確かめてほしい
- 「負の辺があっても入れ直す書き方なら負閉路がない限り答えは合うが、計算量の保証がなくなる」は、指数時間になる例があることまでは書かなかった（出典を確かめていない）
- 「最小費用流がポテンシャル付きのダイクストラ法を使う」は、調査レポート 03-graph §1.1 の ACL の実装の確認に拠った
- abc362_d の制約（重みの大きさ）は確かめていないので、本文は「重みの和は大きくなりうるので long long」とだけ書いた
- 使った出典は本文の「参考」のとおり。新しく noai を確かめたドメイン：judge.yosupo.jp は付録 B にあり、check_noai でも指定なし。cnblogs・ikatakos・oraclesqlpuzzle・hamayan・kyo-pro・drken・qiita・github も付録 B にある
- 使用量の目安：道具の呼び出し約 40 回、Web 取得 11 回・検索 2 回
