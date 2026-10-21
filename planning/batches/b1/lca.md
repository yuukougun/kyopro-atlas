# lca の報告と提案（工程8b・バッチ b1）

- 書いたファイル：docs/tree/lca.md、snippets/lca/lca.{cpp,yaml}、snippets/lca/path-max.{cpp,yaml}、docs/img/lca/jump.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21 のまま）。sections は変えていない
- 検査の結果：check_pages（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、check_snippets（2 件、期待と違う 0）、textlint（エラー 0、警告 10。数式を含む文・要点の囲みの入れ子の箇条書き・画像の代替テキストの文の長さと、助詞の重なりの誤検出に近いもの）
- 動く図：作っていない。置き場の div だけ置いた（下の「動く図の仕様」）
- 使った出典：参考の節のとおり。新しく noai を確かめたドメインはない（どれも付録 B にある）

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠の URL |
| --- | --- | --- | --- |
| abc460_f | pages に追加 | `{id: lca, role: challenge}` | https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2026/0530_abc460 （解法の節。距離をオイラーツアーと Sparse Table の LCA で O(1) にし、セグ木の更新ごとに距離を O(log N) 回計算する） |
| abc460_f | alternatives に追加（lca） | approach：「頂点番号の区間ごとに直径の両端を持つセグ木で、合成のたびに 2 点間の距離を LCA で求める。距離の計算が多いので、O(1) の LCA（オイラーツアーと Sparse Table）にすると速い」 | 同上 |
| typical90_ai | pages に追加 | `{id: lca, role: practice}`（例題は auxiliary-tree のまま） | https://github.com/E869120/kyopro_educational_90/blob/main/sol/035-04.cpp |
| abc014_4・abc267_f | checked | 2026-10-21 | 各 evidence の解説で問いと制約（abc014_4：N, Q ≤ 10^5、abc267_f：N, Q ≤ 2×10^5）を確かめた |
| abc235_e | evidence（lca の alternatives の裏付け） | 「パス上の最大の辺の重み h と比べ、w < h なら含まれる」の条件は kazun 氏の記事で確かめた。ダブリングで h を求める実装は記事にはない（条件からの一般的な帰結） | https://kazun-kyopro.hatenablog.com/entry/ABC/235/E |

- abc319 以降の問題がこのページにない（catalog の problems_note のとおり）。abc460_f を力試しに入れると、水・青のページに abc319 以降を 1 問以上という目安を満たす

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| 祖先 | ancestor | 根付き木で、頂点 v から根へのパス上にある頂点。v 自身も v の祖先に数える流儀が多く、LCA の定義もそれに従う |
| K 個上の祖先（level ancestor） | level-ancestor | 頂点 v から親へ K 回たどった頂点。K が v の深さより大きければ存在しない |

本文では用語集へのリンクは単位元（identity-element）だけを使った。

## 手引きへの提案

- §13 の定型の節の anchor `comparison`（使い分け）と、sections の中身の節の anchor が重なる場合の扱いを決めてほしい。lca は sections に `comparison`（LCA の求め方の比較）があるので、その節を使い分けの位置に置き、別の「使い分け」の見出しは作らなかった
- 例題・練習の方針から練習問題へリンクするとき、練習の行には anchor がないので `#practice` へリンクした。練習の問題を本文から指す書き方（`#practice` でよいか）を手引きに書くとよい

## front matter・catalog について

- 指示文ではレベルが「水」だったが、骨格の front matter と catalog は level: 青 である。front matter は変えずに青のまま書いた（例題は catalog のとおり ABC014 D・ABC267 F）。どちらが正かをメインで確かめてほしい

## 動く図の仕様（priority 1。後でまとめて作る）

- 置き場：`<div class="kp-viz" data-viz="lca" data-config='{"n": 12, "parents": [-1, 0, 0, 1, 1, 2, 3, 4, 6, 7, 5, 8], "query": [11, 9]}'></div>`（0-indexed、根は 0）
- 左に木（深さごとに段をそろえる）、右に表 `up[k][u]`・`up[k][v]`（k = L−1, …, 0）を並べる
- ステップ：①深い方を 1 段ずつ（2 進の桁ごとに）上げて深さをそろえる → ② k を上から 1 段ずつ試し、2 つの値が同じなら「跳ばない」、違えば両方を跳ばす → ③ up[0][u] を答えとして強調
- この設定では：11 → 8（1 個上げる）、k = 3, 2 は同じ（0, 0）、k = 1 は 3 と 4 で違うので跳ぶ、k = 0 は 1, 1 で同じ、答え 1。静的な図 docs/img/lca/jump.svg と同じ例
- caption の例：「k = 2：u の 4 個上と v の 4 個上はどちらも 0。同じなので跳ばない（跳ぶと LCA を通り過ぎるかもしれない）」
- 追加の設定の候補：u が v の祖先になる例（query: [8, 3]）

## 問題の補充の候補

| 問題 ID | 何を問うか | 裏付けの URL |
| --- | --- | --- |
| abc460_f（台帳にあり、確認済み） | 頂点の白黒の切り替えのたびに、黒い頂点どうしの距離の最大を答える。セグ木の合成で 2 点間の距離を何度も求めるので、LCA（特に O(1) の方式）が要る | https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2026/0530_abc460 |
| typical90_ai（台帳にあり、確認済み） | 指定された頂点をすべてつなぐのに要る辺の最小数を多数の質問で答える。行きがけ順に並べた隣どうしの距離を LCA で求める | https://github.com/E869120/kyopro_educational_90/blob/main/sol/035-04.cpp |

## 未解決の点

- オフライン（Tarjan）の計算量は「全体でほぼ O(N + Q)」と書いた（research/04 §4.14 の O(N + Q α) にもとづく。Union-Find の実装でならし計算量の評価が変わるので、「ほぼ」とした）
- 順序で結果が変わる演算をパス上で集約するには上り用・下り用の 2 種類の表が要る、と書いた。コード片では確かめていない（最大値の場合だけ確かめた）
- 使用量の目安：道具の呼び出し 約 30 回、Web 取得 8 回
