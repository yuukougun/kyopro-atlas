# matrix-tree-theorem の報告（b4）

- 書いたファイル：docs/graph/matrix-tree-theorem.md、snippets/matrix-tree-theorem/count.{cpp,yaml}、docs/img/matrix-tree-theorem/example-graph.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-22）。sections に `library`（計算量と自作するときの要点）と `resources`（学ぶための資料）を足した（lgv-lemma と同じ形）
- 検査の結果：check_pages エラー 0・警告 0、fix_problems --check 直すべき行 0、check_snippets 期待と違う 0、textlint エラー 0（警告 3：証明の折りたたみの中の長い 1 文、台帳の要約の行の助詞「で」、参考の 1 行の長さ）
- 図：example-graph.svg を render_svg.py で PNG にして目で確かめた
- コード片：count.cpp は無向の全域木・根から出る有向全域木・BEST 定理の 3 つを持ち、`T` の入力で 5 頂点以下の乱数グラフ 300 個ずつを全列挙（辺の部分集合・辺の順列）と比べる assert を通す。Library Checker の定義（オイラー閉路は 1 本目の辺を固定）に合わせた
- 使った出典：en.wikipedia.org（Kirchhoff's theorem・BEST theorem）、potato167.hatenablog.com（新しいドメイン。check_noai で noai・noimageai の指定なしを確かめた）、kmjp.hatenablog.jp（ABC336 G・ABC253 Ex）、Library Checker の問題定義（GitHub の task.md と info.toml で N ≤ 500 を確かめた）

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠の URL |
|---|---|---|---|
| abc336_g | summary | 0 から 15 の各値 i について個数 X_i が与えられ、X_i の和を N とする。0 と 1 からなる長さ N + 3 の列のうち、連続する 4 文字を 2 進数として読んだ値 i がちょうど X_i 回現れるものの数を、998244353 で割った余りで求める。 | https://kmjp.hatenablog.jp/entry/2024/01/16/0930 |
| abc336_g | evidence | 追加：https://potato167.hatenablog.com/entry/2024/02/21/100000 | 同左（8 頂点の多重辺グラフのオイラー路に帰着し、ΠX_j! で割る方針を確認） |

## 用語集への提案

| 語 | anchor | 定義 |
|---|---|---|
| ラプラシアン行列 | laplacian-matrix | 無向グラフで、対角に各頂点の次数、非対角に「2 頂点を結ぶ辺の本数」の符号を反転した値を置いた行列。次数行列から隣接行列を引いたものに等しい。 |
| 有向全域木 | arborescence | 有向グラフの全域木で、根からすべての頂点へ辺の向きに沿って到達できるもの（根から出る木）。辺の向きを逆にした「根へ向かう木」も同じ語で呼ぶことがある。 |

本文ではどちらもリンクせず、本文で定義した。

## 手引きへの提案

- §5 graph に「BEST 定理の数は、辺を区別し 1 本目の辺を固定した数（巡回シフトを同一視）。始点 s から終点 t（s ≠ t）へのオイラー路は辺 t→s を足して 1 本目に固定、始点だけ決まった閉路は ec × deg⁺(s)。同じ種類の辺は最後に個数の階乗で割る」を足すとよい（持ち主は matrix-tree-theorem#best-theorem）。
- BEST 定理の (deg⁺(v) − 1)! の出次数には自己ループを数え、行列木定理の行列には入れない、という非対称が実装の落とし穴になる（コード片の乱数の全列挙で確かめた）。

## 問題の補充の候補

| 問題 ID | 何を問うか | 裏付けの URL |
|---|---|---|
| abc253_h（Ex. We Love Forest、diff 2758） | N 頂点の候補の辺 M 本から K 回、重複を許して一様に選んで足したとき、森になる確率を K = 1, …, N−1 のそれぞれについて求める。頂点集合ごとの全域木の数を行列木定理で求め、最小の頂点を含む成分で分ける部分集合の DP で森を数える。練習（#subset-dp）に向く | https://kmjp.hatenablog.jp/entry/2022/05/28/1030 （2 つ目の裏付けは未取得） |

本文の #subset-dp は、この問題の ID を出さずに型だけを書いた（§13-6）。台帳に入れば、練習問題の節を足してこの問題を置き、参考に kmjp の記事を戻す。

## 未解決の点

- abc253_h の 2 つ目の裏付けを取っていない（§15-6 の目標は 2 つ）。
- abc336_g の制約（N の上限）は第三者の記事で確かめきれていない。本文では「階乗は N まで前計算する」とだけ書いた。
- potato167 氏の記事は Library Checker の counting_eulerian_circuits の制約を「N ≤ 2×10^5、M ≤ 500」と書いているが、GitHub の info.toml では N ≤ 500、M ≤ 2×10^5 である。本文は info.toml に従った。
- determinant のページが stub なので、行列式の前提はページへのリンクだけにし、掃き出しは gaussian-elimination#mod-p へリンクした。determinant が書けたら、自作の要点（法が素数でないとき）をそちらへ寄せてもよい。
- euler-path の 2 か所（148 行・219 行）は `#best-theorem` へ張り替えられる（handoff-b2b3 の申し送り）。tree-degree・cayley-pruefer・counting-labeled-graphs・small-graph-brute-force からのリンクは `#laplacian` へ張り替えられる。

## 検証の指摘への対応

- 指摘 1（直すべき）：#best-theorem の最後の段落を、c! で割ってよいのは始点を決めた列の数に限ると書き直した。ec(G) そのものは割れないこと、その反例（2 頂点で 2 本ずつ、ec=2 だが区別しない閉路は 1 つ）も 1 文で添えた
- 指摘 2：「$w$ から出る辺を 1 本目に固定して」とした
- 指摘 3：count_eulerian_circuits の先頭に `if (edges.empty()) return 1;`（空の閉路 1 つとみなす約束をコメントに書いた）を足し、case `E 3 0 → 1` を加えた
- 指摘 4：根へ向かう木で非対角も同じく $-(u \to v$ の辺の本数$)$ と明示した
- 採らなかった指摘：なし

## 提案（検証の後）

- 台帳 abc336_g：検証役の確認どおり、`checked: 2026-10-22` の記入と、evidence への potato167 氏の記事の追加を提案する（執筆時の提案と同じ）
