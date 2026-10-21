# scc の報告（工程8b・バッチ b1）

- 書いたファイル：docs/graph/scc.md、snippets/scc/{condense-dp,on-cycle,kosaraju}.{cpp,yaml}、docs/img/scc/condensation.svg
- front matter で変えたもの：complexity（`O(N+M)（Kosaraju・Tarjan・ACL の scc_graph。縮約した DAG の構築も O(N+M)）`）・stage（draft）・updated（2026-10-21 のまま）。sections に `{title: 縮約の応用の型（組の数・不等式の割り当て・2-SAT）, anchor: patterns}` を足した（既存の anchor は変えていない）
- 検査の結果：check_pages（エラー 0・警告 0）、fix_problems --page scc --check（直すべき行 0。全体の --check は、並行して書かれている graph/minimum-spanning-tree.md の 10 行で「直すべき行」が出るが、このページの分ではない）、check_snippets（3 片・期待と違う 0）、textlint（エラー 0・警告 3。36 行は要点の「いつ使うか」の入れ子の箇条書きを 1 文と数える誤検出、234 行は台帳の summary（abc296_e）の文、253 行は数式 `$3, 2, 1$`・`$1, 2, 3$` の中の読点を数える誤検出）
- コード片の確かめ：kosaraju.cpp を ACL の scc_graph と素朴な推移閉包の分け方とランダムな 400 ケース（N ≤ 9、自己ループ・多重辺を含む）で突き合わせ、分け方の一致と「成分をまたぐ辺は番号の小さい方から大きい方へ」を確かめた。condense-dp.cpp は（頂点, 訪れた集合）の全探索と 400 ケースで突き合わせた（一時置き場で実施）
- 図：静的な SVG 1 枚（8 頂点の例と縮約した DAG。成分の番号は ACL の scc() の実際の出力 0 0 0 2 2 1 3 4 に合わせた）。描画の道具が手元になく、見た目は目で確かめていない（座標の計算だけ）。検証役に描画の確認を頼みたい
- 動く図：catalog の visual は priority 3 なので作らず、置き場の div も置いていない（静的な SVG で代えた）
- 使った出典：ACL v1.6 の document_ja/scc.md・atcoder/scc.hpp・internal_scc.hpp・test/example/scc_practice.cpp（手元）、E869120 sol/021.cpp（typical90_u の Kosaraju 法）、kyo-pro ABC296E、drken ABC357E、ikatakos ABC478（解法の節だけ）、torus711 ABC335E（縮約して DAG 上で DP する型）、kyo-pro ABC245F（補充の候補の確認）。新しく noai を確かめたドメインはない（すべて付録 B）

## 台帳への提案

- practice2_g｜checked｜2026-10-21｜ACL の scc_practice.cpp で問いと使い方を確かめた
- abc296_e・abc357_e・abc478_e・typical90_u｜変更なし（summary・approach は evidence と食い違いなし）
- abc357_e の alternatives（scc の summary）は末尾に句点がなく、abc296_e・abc478_e の summary には句点がある。本文の行は台帳のとおりにしたので、句点の有無をそろえるなら台帳で直してほしい（practice2_g・typical90_u も句点なし）

## 用語集への提案

- 強連結成分｜strongly-connected-component｜有向グラフで、互いに行き来できる頂点の極大の集まり。閉路に乗らない頂点は 1 頂点だけの成分になる
- 縮約｜condensation｜互いに行き来できる頂点の集まり（強連結成分）を 1 頂点にまとめ、集まりをまたぐ辺だけを残したグラフ。必ず DAG になる
- 自己ループ｜self-loop｜頂点から自分自身へ向かう辺。有向グラフでは長さ 1 の閉路になる（graph-basics の terms の節にあれば不要）
- 本文では用語集へリンクしていない（定義を本文の最初の節に書いた）

## 手引きへの提案

- §9 のコード片で、`vector<pair<int,int>> edges(m); for (auto& [u, v] : edges) cin >> u >> v;` のように構造化束縛で入力を読む書き方を使った。許される範囲（§9 の「構造化束縛は使ってよい」）と判断したが、入力の読み方まで構造化束縛にしてよいかを明記すると迷わない

## 問題の補充の候補（問題ID・何を問うか・裏付けの URL）

- abc335_e（diff 1540、確認済み・dp-dag の練習）：値の書かれたグラフで、値が減らないように頂点 1 から N へ進むときの値の種類数の最大。値の小さい方から大きい方へ（同じ値なら両方向に）有向辺を張って強連結成分で縮約し、DAG 上で DP する。scc の練習（dp-on-dag の節の代表）に足すことを提案する｜https://torus711.hatenablog.com/entry/2024/01/07/215719（強連結成分で縮約し、成分の番号順に DP すると明記）
- abc245_f（diff 1451、確認済み・topological-sort の練習）：有向グラフで、無限に動き続けられる頂点の数。強連結成分で「閉路の成分か、閉路の成分に辿り着ける成分」を後ろから決めても解ける（本文の on-cycle の節に型として書いた）。ただし evidence の kyo-pro の記事は出次数 0 から剥がす方法だけで、強連結成分の解き方は第三者の解説で未確認。足すなら SCC の解き方を書いた解説を evidence に足してほしい｜https://kyo-pro.hatenablog.com/entry/ABC245F
- 力試し（青の位置）は確認済みの候補が見つからなかった。research の abc374_g（2608）・abc214_h（3138）は発展で、dilworth-path-cover などの担当

## 未解決の点

- typical90_u の制約（N, M の上限）は evidence の想定解のコードからは配列の大きさ（2^18）しか分からないので、本文では具体的な上限を書かず「頂点数が 10^5 なら組の数は約 5×10^9」とした
- frequency_evidence の「前提として 2 ページに届く」は変えていない
- related にある functional-graph・two-sat・lowlink・dilworth-path-cover・bitset-speedup・topological-sort・cycle-detection は stub なので、ページへのリンクだけにした（節へのリンクは draft の dfs#pre-post-order・dfs#iterative・dp-dag#find-dag だけ）
- dp-dag の related に `scc#dp-on-dag` があり、本文の dp-on-dag の節はこれに対応する
- 使用量の目安：道具の呼び出し 約 35 回、Web 取得 6 回

## 検証の指摘への対応（verify/scc.md）

- 1〜8：すべて直した（非負の条件を問題設定・dp の理由・コード片の先頭に書いた。問題設定を「好きなだけ動き、どこで止めてもよい。各頂点の価値は初めて訪れたときに 1 回だけ得る」に直した。Kahn 法の例を外した。辞書順最小は「なるとは限らない」に。low の説明・最短路の理由・無向グラフの向き付け・同値関係の説明を直した）
- 9：「成分 3」「成分 4」のラベルを枠の下へ移した
- 10：左右に並べていた 2 つの図を上下に並べた縦長の図（幅 430）にした。代替テキストと本文の「左・右」を「上・下」に直した。スマホの幅で倍率は約 0.83 になる
- 11：condense-dp に「出口の先が価値 0」のケースを足し、w の非負と DAG の辺の向き（c < d）を assert にした。kosaraju にすべての辺で comp[u] <= comp[v] の assert、on-cycle に cnt の範囲の assert を足した（どれも core の外か、core の中でも本文の主張を確かめる 1〜3 行）
- 採らなかったもの：なし
