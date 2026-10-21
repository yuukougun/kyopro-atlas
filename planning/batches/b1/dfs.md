# dfs の報告と提案（工程8b・バッチ b1）

- 書いたファイル：docs/graph/dfs.md、snippets/dfs/{components,simple-paths,order}.{cpp,yaml}、docs/img/dfs/order.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21 のまま）。sections に「上位の手法へのつながり（next-steps）」を足した
- 検査の結果：check_pages エラー 0・警告 0、check_snippets 期待と違う 0、fix_problems --check 直すべき行 0、textlint エラー 0・警告 1（37 行目は要点の「いつ使うか」で、signs の文と同じにするため残した）
- 使った出典：kyo-pro ABC315E・ABC284E、programming-hiroba abc315-e・abc284-e、drken abc378_d、E869120 の 072.cpp（どれも付録 B のドメイン）。新しく noai を確かめたドメインはない
- 動く図：catalog の visual は priority 2 なので作らず、静的な SVG（行きがけ順・帰りがけ順）で代えた

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc315_e | summary | 末尾に「。」を足す（ほかの行と表記をそろえる） | — |
| abc378_d | summary | 末尾に「。」を足す | — |
| abc284_e | summary | 「頂点 1 から始まる単純パスの数を、10^6 を上限として求める。」（末尾の「。」） | — |
| typical90_bt | summary | 「16 マス以下のグリッドで、…」とマス数を入れるか検討（complexity-estimation の行は H×W ≤ 16 と書いている。2 ページで要約が違う） | https://sugizakkworld.com/623/ （「16 マス以下」。check_noai 未実施なので要確認） |
| abc378_d・abc284_e・typical90_bt | checked | 2026-10-21（evidence の解説で問いを確かめた） | 各 evidence |
| abc284_e | evidence | https://programming-hiroba.com/abc284-e/ を追加（次数 10 以下と、10^6 × 10 の見積もり） | 同 URL |
| abc315_e | evidence | https://programming-hiroba.com/abc315-e/ を追加 | 同 URL |

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| DFS 木 | dfs-tree | 深さ優先探索でたどった辺（まだ訪れていない頂点へ進んだ辺）だけを残した、始点を根とする木である。たどらなかった辺の向き先が祖先か子孫かで、閉路の検出や lowlink が判定する。 |

本文では `../guide/glossary.md#dfs-tree` へリンクしている。

## 手引きへの提案

- §9 の DFS の書き方 `auto dfs = [&](auto&& self, int v, int p) -> void` は木向けで、一般のグラフでは親の引数が要らない。「木では親を引数で渡し、一般のグラフでは印の配列を使う」と補うとよい
- 非再帰の DFS は「`~v` で出る予定を積む」形に統一すると、tree-traversal・topological-sort・scc のページとそろう（dfs のコード片 order.cpp の iterative の範囲を見本にできる）

## 問題の補充の候補

- abc138_d（D. Ki、diff 920）：根付き木の部分木への加算を、根から DFS で値を流して処理する。調査レポート §5.2 に例題の候補として載るが台帳にない。tree-traversal の例題の方が合うかもしれない。裏付け：https://blog.hamayanhamayan.com/entry/2019/08/19/024030
- 練習の並び：typical90_bt は difficulty がなく、★4 で閉路の扱いがあるため最後に置いた。complexity-estimation のページでの位置と合わせるなら確認してほしい

## 未解決の点

- typical90_bt の正確な制約（H, W の上限）は第三者の資料で揺れている（「16 マス以下」と「16 × 16」）。本文の練習の方針では「マスは 16 個以下」と書き、complexity-estimation の記述（H×W ≤ 16）に合わせた。確認できなければ「マスが少ない」に弱める
- abc315_e の N の上限は第三者の資料で確かめられなかったので、本文では数を書かず「依存が一本道に長くつながると再帰が深くなる」とだけ書いた
- 再帰の深さの節で「AtCoder ではスタックの上限が大きい」と書いた。cpp-environment#stack-depth の節（新ジャッジの値は未確認）が書かれたら、そちらの節へのリンクに替える（いまは stub なのでページへのリンク）
- 使用量の目安：道具の呼び出し約 30 回、Web 取得 12 回

## 検証の指摘への対応（verify/dfs.md）

- 指摘 1（図の子の並び）：採った。頂点を並べ直し、頂点 5 の子を訪れた順に左から 3・6 とした。破線の辺 1-3 は木の左側を回した。ラベルの位置もそれに合わせて動かした
- 指摘 2（完全グラフの本数）：採った。「始点 1 つあたり約 $e \cdot (N-1)!$ 本（$N = 10$ で約 $10^6$）」とした
- 指摘 3（lowlink の定義）：採った。「その頂点の部分木から DFS 木以外の辺を 1 本使って戻れる」を入れた
- 指摘 4（再帰のラムダの説明）：採った。最初のコードの直後に 1 文を足した
- 指摘 5（図の小さい文字）：採った。ラベル・注記・凡例を font-size 14 にそろえ、下の注記を 2 行に詰め直した
- 指摘 6（確認問題）：採った。答えに「4 の側から先に調べても 4 本」を足した
- 採らなかった指摘：なし
- 申し送り：この環境に SVG を画像にする道具がなく、直した order.svg は座標の計算と XML の検査だけで確かめた。再検証で画像にして見てほしい
- 台帳への追加の提案：typical90_bt の summary のマス数の根拠は、sugizakkworld.com ではなく E869120 のリポジトリの problem/072.jpg（$H \times W \le 16$、検証役が確認）とする。abc315_e の checked も 2026-10-21 でよい（検証役が記事 2 本で問いを確かめた）
