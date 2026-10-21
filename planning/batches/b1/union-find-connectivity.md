# union-find-connectivity の報告と提案（工程8b・b1）

- 書いたファイル：docs/graph/union-find-connectivity.md、snippets/union-find-connectivity/reverse-deletion.{cpp,yaml}、docs/img/union-find-connectivity/reverse-time.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21 のまま）。sections は変えていない
- 本文で足した小見出し（sections には載せていない `###`）：reverse-steps・vertex-deletion・other-values
- 検査の結果：check_pages エラー 0・警告 0／fix_problems --check で本ページの直すべき行 0（ほかに minimum-spanning-tree の行が出るが担当外）／check_snippets 期待と違う 0／textlint エラー 0、警告 1（61 行：数式 $d_0, d_1, \dots$ の中の読点を数える誤検出）
- 使った出典：kyo-pro（abc229_e・abc264_e）、drken（abc120_d・abc181_f）、kazun（abc264_e）、pyteyon（abc040_d）、kmjp（abc181_f・abc413_g）。新しく noai を確かめたドメイン：pyteyon.hatenablog.com（noai・noimageai の指定なし、2026-10-21）→ 付録 B への追加を提案

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc229_e・abc120_d・abc264_e・abc040_d | summary | 末尾に「。」を足す（ほかのページの行と表記をそろえる。本文の行は「。」付きで書いた） | 表記の統一 |
| abc181_f | alternatives（union-find-connectivity）の summary | 末尾に「。」を足す | 同上 |
| abc413_g | pages | {id: union-find-connectivity, role: practice} を足す（超頂点の節の「壁から壁まで障害物がつながるか」の型。abc319 以降の問題がこのページにないため） | https://kmjp.hatenablog.jp/entry/2025/07/05/0930 |

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| ならし計算量 | amortized | 操作を何回も行ったときの合計を回数で割った、1 回あたりの計算量。1 回だけ見ると遅いことがあっても、合計では上限が守られる。 |
| 超頂点 | super-vertex | 複数の頂点をまとめて扱うために足す仮の頂点、またはまとめた頂点。「どれかとつながっているか」を 1 回の判定にできる。 |

（本文では、オフラインは offline-queries のページへ、超頂点は extended-dijkstra#super-vertex へリンクした。ならし計算量は用語集へのリンクを付けていない）

## 手引きへの提案

- 骨格の要点の「いつ使うか」は signs をそのまま句点なしで並べるため、textlint が 1 文として数えて sentence-length の警告を出す。骨格の生成で各行に「。」を付けるか、手引きに「signs の行に句点を付ける」と書くとよい（本ページでは句点を足した）
- `fix_problems.py --page <id>` は `--field` を付けないと書き換えないことがあった（1 回目は「見たページ 1・直した行 0」で行が直らず、`--field graph` を付けたら直った）。手引き §10 の例に `--field` を添えるとよい

## 問題の補充の候補

- abc413_g（G. Big Banned Grid、diff 1723、確認済み・grid-graph の力試し）：巨大なグリッドで障害物を避けて左上から右下へ行けるかを判定する。障害物どうしを 8 近傍で Union-Find につなぎ、左端・下端に接するものと右端・上端に接するものをそれぞれまとめて、両者が連結なら通れない。裏付け https://kmjp.hatenablog.jp/entry/2025/07/05/0930 。練習（超頂点の節）として提案
- 逆順の削除そのものを問う abc319 以降の ABC は見つけられなかった（catalog の problems_note と同じ）。候補探しは ap.py と第三者の解説で続ける必要がある

## 未解決の点

- 図の SVG は手元に描画の道具がなく、目で確かめていない（座標の計算で重なりがないことだけ確かめた）。検証で表示を見てほしい
- 動く図（visual は priority 3）は作らず、静的な SVG で代えた
- mixed-updates の節の計算量 $O(N + Q \log Q \log N)$ は、各辺の区間がセグメント木の $O(\log Q)$ 個のノードに分かれ、ロールバックできる Union-Find の 1 操作が $O(\log N)$ であることからの見積もり。research 03 §4.D は $O((N+Q) \log Q \log N)$ と書いている（本質は同じ）
- ACL の囲みの「merge はすでに同じ成分だったかを返さない」は document_ja の記述（併合後の代表元を返す）からの判断
