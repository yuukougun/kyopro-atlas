# zero-one-bfs の報告と提案（工程8b・b1）

- 書いたファイル：docs/graph/zero-one-bfs.md、snippets/zero-one-bfs/{graph,turns}.{cpp,yaml}、docs/img/zero-one-bfs/example-graph.svg
- front matter で変えたもの：complexity（`O(N+M)（各頂点が deque に入るのは高々 2 回）`）・stage（draft）・updated（2026-10-21 のまま）。sections に 2 節を足した（`処理の流れ` {#procedure}、`何をコスト 1 にするか` {#cost-modeling}）。既存の 4 つの anchor は変えず、並びだけ本文の順に合わせた
- 検査の結果：check_pages --page zero-one-bfs（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、check_snippets（2 件・各 5 case 一致）、textlint（エラー 0・警告 3）
  - 残した警告：92 行（数式 $0, \dots, 0, 1, \dots, 1$ の中の読点）、162・163 行（数式 $(i, j, d)$ の中の読点）の max-comma。どれも数式の中の誤検出
- 動く図：書いていない。置き場の div `<div class="kp-viz" data-viz="zero-one-bfs" data-config='{"n": 5, "source": 0, "edges": [[0, 1, 1], [0, 2, 1], [0, 3, 0], [3, 2, 0], [1, 4, 0], [2, 4, 1]]}'>` と、図の前後の文章（同じグラフの静的な図と、手順を追う表）を置いた
  - 図の仕様（案）：config は頂点数 `n`・始点 `source`・有向辺 `[u, v, w]`（w は 0 か 1）。各ステップで「取り出した組・たどった辺・更新された dist・deque の中身（先頭 → 末尾、組は (距離, 頂点)）」を示す。重み 0 で縮んだ組は先頭へ、重み 1 は末尾へ入る動きを強調し、古い組を読み飛ばすステップを別の色（`.kp-v-*`）で示す。caption の列は本文の表と同じ 7 ステップ（始め・(0,0)・(0,3)・(0,2)・(1,1)・(1,2) 読み飛ばし・(1,4)）になる。頂点の配置は SVG と同じ（0 左、3 上、1 下、2 中央右、4 右）にすると本文と対応が取れる
- 使った出典（どれも付録 B のドメイン。題名は title 要素で確かめた）：
  - betrue12.hateblo.jp（ARMERIA の 01-BFS の解説）：deque の不変条件
  - drken1215.hatenablog.com/entry/2021/07/30/024800：arc005_3 の方針と H, W ≤ 500
  - oraclesqlpuzzle（abc176_d）：例題の方針と、届かなければ -1
  - github.com E869120 sol/043.cpp：始点の 4 つの向きを距離 0 にする初期化
  - blog.hamayanhamayan.com（abc213_e・abc246_e）：練習の方針
  - oraclesqlpuzzle（abc400_d）：補充の候補の裏付け（本文には使っていない）
  - 新しく noai を確かめたドメインはない

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc176_d | evidence | https://oraclesqlpuzzle.ninja-web.net/kyoupro/05-atcoder-02-abc/kyoupro-abc176-d.html を足す。いまの evidence（ARMERIA）は問題名を挙げるだけで、問いと解き方の裏付けにならない | 同 URL |

ほかの使った問題（arc005_3・typical90_aq・abc213_e・abc246_e）の summary と approach は、evidence の解説と食い違いがなかった。

## 用語集への提案

- deque｜deque｜先頭と末尾のどちらからも要素を出し入れできるキュー。C++ では `std::deque` で、両端の操作はどれも $O(1)$。付録 A のデータ構造に「deque」があるが、ページも用語集の項目もないので、用語集に置くとよい（本文ではまだリンクしていない）
- 緩和｜relaxation｜辺 $u \to v$ について、$\mathrm{dist}[u] + w < \mathrm{dist}[v]$ なら $\mathrm{dist}[v]$ をその値に下げる操作。ダイクストラ法・ベルマンフォード法・01-BFS に共通する（本文は解法の詳細で「緩和して」と使った。リンクはしていない）

## 手引きへの提案

- §5 graph の「BFS・01-BFS・ダイクストラ法は … 壊れる例（負の辺など）を書く」について、01-BFS の壊れる例は負の辺ではなく「初めて見つけたときに確定させる」「重み 0 の辺を末尾に入れる」「重み 2 を末尾に入れる」の 3 つとした。負の辺はダイクストラ法のページに任せた
- 基礎でない technique でも、sections に `処理の流れ` のような定型に近い節を足したくなる。§13.1 の定型の見出しに `## 処理の流れ {#procedure}` を加えるか、各ページで sections に足すかを決めてほしい（今回は sections に足した）

## 問題の補充の候補

- abc400_d（D. Takahashi the Wall Breaker、diff 1026（緑/基礎）、ap.py で実在を確認）：グリッドで、前方 1〜2 マスの壁を壊して進む前蹴りの最小回数を求める。通路へ歩く移動を重み 0、前蹴りで前方 1 マスまたは 2 マスへ進む移動を重み 1 にした 01-BFS。catalog の problems_note にある「abc319 以降の 01-BFS の問題」に当たる。difficulty は水に届かないので練習の最初に置くのがよい。裏付け：https://oraclesqlpuzzle.ninja-web.net/kyoupro/05-atcoder-02-abc/kyoupro-abc400-d.html

## 未解決の点

- example-graph.svg は描画して目で確かめる道具がなく、XML として読めることと座標の計算だけを確かめた。辺の重みのラベルが線と重ならないか、表示の確認を検証役に頼みたい
- 「Dial の方法」（距離ごとのキューを $C + 1$ 個使い回す）は記憶に基づく。名前と計算量（$O(M + N C)$ 程度）は本文に書かず、手順だけを書いた。出典で確かめるなら検証役に頼みたい
- ABC246 E の盤面の上限（N ≤ 1500）は hamayan の解説のコードの配列の大きさからの推測で、本文では「$H = W = 1500$ でも」と一般論の例として使った
- typical90_aq（diff なし、★4）を練習の先頭に置いた。★4 は難しさの見当で、易しい順の位置は確定でない
- 使用量の目安：道具の呼び出し約 35 回、Web 取得 11 回・検索 4 回
