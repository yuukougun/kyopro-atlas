# modular-shortest-path の報告（b4）

- 書いたファイル：docs/graph/modular-shortest-path.md、snippets/modular-shortest-path/congruence.{cpp,yaml}、docs/img/modular-shortest-path/coins-3-5-7.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-22）。sections は変えていない
- 構成：要点 → 余りを頂点、操作を辺にする（#residue-vertices）→ 同余最短路（#congruence、図 1 枚・コード片）→ ライブラリでの使い方（#library。自作の要点と Library Checker の対応）→ 学ぶための資料（#resources）→ 例題 ARC084 D → 参考
- 検査の結果：check_pages エラー 0・警告 0、fix_problems --check 直すべき行 0、check_snippets 期待と違う 0、textlint エラー 0・警告 4（要点の囲みの入れ子の箇条書きの文長、問題の行の文長、題名「墨墨的等式」の連続した字 2 か所。どれも誤検出）。SVG は render_svg.py で 360・720 の幅を目で確かめた
- 使った出典：drken1215.hatenablog.com（ARC084 D の解説。頂点・辺・重み・+1 のコストを 1 としてよい理由・O(K)）、qiita.com/drken（蟻本初級編）、www.luogu.com.cn/article/7yfca7t0（墨墨的等式の題解。法・辺・個数の式）、oi-wiki.org/graph/mod-shortest-path/（構成と O(nm) の方法。文章・図は使っていない）、judge.yosupo.jp/problem/shortest_path と GitHub の library-checker-problems の graph・math の一覧（同余最短路を直接問う問題がないことの確認）。新しいドメインはない

## 台帳への提案

- なし（arc084_b の summary・approach は本文と一致した）

## 用語集への提案

- なし（「同余最短路」はこのページの別名なので、用語集より索引で引ければ足りる）

## 手引きへの提案

- なし

## front matter・ほかのページへの提案

- 申し送り（b3 handoff 1.2）：gcd-properties の frobenius の節の「同余最短路」のリンクを `../graph/modular-shortest-path.md#congruence` に張り替えられる
- b1 handoff の 5 か所（extended-dijkstra:396・zero-one-bfs:152・digit-and-mod:93・210・217）も、内容に合わせて `#residue-vertices`（digit-and-mod:93・217、zero-one-bfs:152、extended-dijkstra:396）または例題 `#arc084_b`（digit-and-mod:210）へ張り替えられる
- 本文に定型でない節 `## ライブラリでの使い方 {#library}`・`## 学ぶための資料 {#resources}` を置いた（overview の構成の目安に合わせた。sections には載せていない）。cht は resources を同じ形で置いている

## 問題の補充の候補

- abc232_g（G. Modulo Shortest Path、diff 2550、ap.py で実在を確認）：辺 i→j のコストが (A_i + B_j) mod M で辺が N^2 本あるグラフの最短路を、M 個の余りの補助頂点を閉路（重み 1）に並べて辺を O(N) にして解く。余りを頂点にする点は近いが、本質は補助頂点で辺を減らす型（超頂点・segment-tree-graph 寄り）で、同余最短路の例題には向かない。練習か related の候補。裏付け：検索結果で見た公式解説の要約だけで、第三者の解説の URL はまだ確かめていない（kmjp の記事は URL を見つけられなかった）
- 同余最短路（硬貨の組合せ）そのものの AtCoder の問題は、検索（日本語・中国語）で見つけられなかった。OI Wiki の練習の一覧には AGC057 D があるが、ap.py と第三者の解説で未確認

## 未解決の点

- 例題は 1 問だけで、#congruence の型（作れる数の個数・作れない最大の数）の AtCoder の問題が台帳にない。見つかれば練習に足したい
- OI Wiki の「辺を種類ごとに処理して O(nm)」の方法は資料の紹介だけにとどめ、本文では説明していない

## 検証の指摘への対応（b4 verify）

- 1〜6 はすべて直した。1：「目的の量（例題なら桁和）がその経路のコスト以下である実際の数」に。2：$m = 1$ で $-1$ になる意味を足した。3：#congruence に頂点 $m$ 個・辺 $nm$ 本・$O(nm \log m)$ と、前の節の $K$ との対応を足した。4：「一般の公式がなく」に。5：#resources と参考の OI Wiki の行を、方法（数の種類ごとに閉路を 2 周して緩和）を書いてから計算量を添える形にした（#resources は文長の警告を避けて 3 文に分けた）。6：図の最短路の木の 2 本（0 →+5→ 2、0 →+7→ 1）を太線にし、凡例「太線：最短距離を決める辺」と代替テキスト・本文の一文を足した（360px の PNG で確かめた）
- 採らなかったもの：なし
- 台帳への提案（指摘 7）：data/problems.yaml の arc084_b に `checked: '2026-10-22'` を入れる（検証役が drken 氏の解説と summary・approach を照らし合わせ済み）
- 直した後の検査：check_pages エラー 0・警告 0、fix_problems --check 直すべき行 0、check_snippets 期待と違う 0、textlint エラー 0（警告 4 はもとからの誤検出：要点の入れ子の箇条書き・問題の行の文長・「墨墨」）
