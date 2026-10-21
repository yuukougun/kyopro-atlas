# centroid-decomposition（重心分解）の執筆の報告

- 書いたファイル：docs/tree/centroid-decomposition.md、snippets/centroid-decomposition/{count-k,centroid-tree}.{cpp,yaml}、docs/img/centroid-decomposition/decomposition.svg
- front matter で変えたもの：complexity・stage（draft）・updated。sections は変えていない
- 構成：level 黄・type technique（§14-6）。中身の節は sections の 4 つで、応用の型は count-through と centroid-tree-queries の末尾に置いた。acl: [] なので ACL の囲みはない（convolution_ll へは with-convolution の本文からリンク）
- 検査の結果：check_pages エラー 0・警告 0、fix_problems --check 0 行、check_snippets 2 件とも期待どおり、textlint エラー 0（警告 12：数式を含む文の長さ、数式の中の読点、`$c'$` のアポストロフィで文の切れ目を誤る 132 行、台帳の summary の行と参考の行の長さ。§13-8・§14-25）
- 図：visual は priority 2（static）なので SVG 1 枚（decomposition.svg：元の木を段ごとに線の種類と塗りで分け、最初の重心を消した後の成分を枠で囲み、右に重心木）。render_svg.py で 360px・720px の PNG にして目で確かめた。動く図は作っていない
- コード片：count-k.cpp は乱数の木 500 個（3 回に 1 回はパス）×すべての K で素朴な BFS と照らし合わせて assert する。centroid-tree.cpp は乱数の木 400 個ですべての (v, d) を素朴な BFS と照らし合わせ、重心木の深さが floor(log2 N) 以下であることも assert する。部分木サイズは BFS の順を逆にたどって求め、再帰を使わない

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc291_h | summary | 木 T と同じ頂点の根付き木で、どの 2 頂点についても根付き木での最小共通祖先が T 上のその 2 頂点を結ぶパスの上にあり、どの頂点の部分木の頂点数も親の部分木の頂点数の半分以下になるものを 1 つ作り、各頂点の親を答える。 | https://kmjp.hatenablog.jp/entry/2023/02/26/0930 ・ https://qiita.com/navel_tos/items/d1a2fd2b63e73380eadb （どちらも問いの 2 条件と、重心木をそのまま出力する方針） |
| abc291_h | evidence に足す・checked | https://qiita.com/navel_tos/items/d1a2fd2b63e73380eadb ・ 2026-10-21 | 上と同じ |
| keyence2019_e | summary | 一列に並ぶ都市を結ぶ完全グラフで、辺の重みが番号の差と両端の値で決まるときの最小全域木の重みを求める。 | https://drken1215.hatenablog.com/entry/2019/01/15/081500 （辺の重み $D \lvert i-j \rvert + A_i + A_j$、N ≤ 2×10^5。b3/divide-and-conquer の案と同じ文にした） |
| keyence2019_e | approach・checked | 都市の並び（パス）の重心分解＝中央で割る分割統治で、またぐ辺を各側の代表との辺だけに減らし、候補 O(N log N) 本でクラスカル法。木の上の距離に一般化しても重心分解で同じことができる ・ 2026-10-21 | 同上（解法 1。記事は「Tree MST では重心分解で同じ発想」と書いている） |
| abc359_g | alternatives（centroid-decomposition）の approach | 重心ごとに、色ごとの「個数 m と重心からの深さの和 s」を数え、同じ色の組の距離の和 (m − 1)s から子の成分ごとの同じ値を引く | 本文の練習の方針。evidence の drken 氏の記事は本文の解法がマージテクで、重心分解の解き方は書いていない（タグだけ）。重心分解での解法を述べた第三者の解説は見つけられなかった（未解決の点を参照） |

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| 重心木 | centroid-tree | 重心分解で、各成分の重心を 1 つ前の段の重心の子にしてできる根付き木。深さは log2 N 以下で、2 頂点の重心木での最小共通祖先は元の木のその 2 頂点を結ぶパスの上にある。 |

本文では用語集へのリンクを張ると check_pages がエラー（anchor がない）にするので、リンクは張らず本文で定義した（§13-5 は張ってよいとするが、検査を通すため）。用語集に足したら、#depth の段落の最初の「重心木」をリンクにできる。

## 手引きへの提案

- §13-5（用語集へのリンクはまだなくても書いてよい）と check_pages の「用語集に anchor がない」エラーが食い違う。検査を警告にするか、§13-5 を「提案だけにしてリンクは張らない」に直すかを決めてほしい

## 問題の補充の候補（問題 ID・何を問うか・裏付けの URL）

練習が 1 問（abc359_g）しかない。ap.py で実在を確かめた。

| 問題 ID | diff | 役割の案 | 何を問うか | 使う節 | 裏付け |
| --- | --- | --- | --- | --- | --- |
| yahoo_procon2018_final_c | —（ap.py で difficulty なし） | 練習 | 木の頂点 V_i から距離がちょうど K_i の頂点の数を、多数のクエリで答える | centroid-tree-queries（重心木を上にたどり、同じ側の成分を引く） | https://qiita.com/navel_tos/items/d1a2fd2b63e73380eadb （「みんなのプロコン2018 決勝 C 木の問題」として、根を通るパスへの帰着と、根を通らないパスを引く処理を説明） |
| abc267_f | 1939 | 練習（台帳にあるなら役割の追加） | 各クエリで、頂点 U_i から距離がちょうど K_i の頂点を 1 つ答える | centroid-tree-queries（祖先ごとに具体的な頂点を高々 2 個持つ）。想定は直径の端点と LCA | 同上の記事（ABC267F Exactly K Steps）。台帳では lca などのページの問題と思われる |
| abc202_e | 1638 | 参考程度 | 頂点 U_i の部分木のうち根からの距離が D_i の頂点の数 | 同上の記事は「強化版」として重心分解で解いているが、本来はオイラーツアーと二分探索で解く問題なので、ここに載せる必要は薄い | 同上 |
| abc014_4 | 1856（参考値） | 載せない案 | 2 頂点の距離のクエリ | 重心木の dist_to で答えられるが、LCA の方が速く素直（同記事も重心分解は避けるべきと述べる） | 同上 |

## 未解決の点

- abc359_g の重心分解での解法：第三者の解説で確かめられたのは問いと制約（drken 氏の記事）だけで、重心分解での解き方は本文の count-through の考え方から導いた式（同じ色の組の深さの和は (m − 1)s）で書いた。式そのものは初等的に正しいが、検証役は確かめてほしい。台帳の alternatives に重心分解の解法の裏付けとなる URL がない
- abc291_h の制約（N の上限）は解説から確かめられなかったので本文に書いていない
- keyence2019_e は diff 2623（発展の帯）で、黄のページの力試しとしては重い。役割は台帳のとおり challenge のままにした
- 例題が abc291_h の 1 問だけで、重心を通るペアを数える型（count-through）そのものの例題が ABC にない。上の yahoo_procon2018_final_c を練習に足せば centroid-tree-queries の型を補える

## 使った出典

- https://kmjp.hatenablog.jp/entry/2023/02/26/0930 （abc291_h の問いと方針）
- https://qiita.com/navel_tos/items/d1a2fd2b63e73380eadb （重心の探し方、重心木のクエリと同じ側を引く処理、補充の候補）
- https://drken1215.hatenablog.com/entry/2019/01/15/081500 （keyence2019_e の問いと解法 1）
- https://drken1215.hatenablog.com/entry/2024/06/23/025552 （abc359_g の問いと制約）
- https://judge.yosupo.jp/problem/frequency_table_of_tree_distance （本文で名前とリンクだけ。開いていない）
- 新しく noai を確かめたドメイン：なし（どれも付録 B にある）。atcoder.jp・codeforces.com は開いていない（Web 検索の結果の一覧に出たが開いていない）

## メインへの申し送り（リンクの張り替え）

このページが draft になったので、次のリンクを節へ張り替えられる。

- rerooting:178 → `centroid-decomposition#count-through`
- tree-edge-contribution:160・178 → `centroid-decomposition#count-through`
- small-to-large:303 → `centroid-decomposition#count-through`
- divide-and-conquer:165 → `centroid-decomposition#depth`
- roadmap:582 の「距離の頻度表は畳み込みと組む」→ `centroid-decomposition#with-convolution`

## 使用量の目安

- 道具の呼び出し 約 30 回、Web 取得 4 回・Web 検索 3 回

## 検証の指摘への対応（b3）

- 指摘 1〜5・7：直した（1 は二重に数える理由に言い直して 3 文に割った。2 は応用の型から問題名を外し、練習の方針から #count-through へリンク。3 は添字の範囲外と best の初期値 ∞ を追記。4 は図を上下 2 段・幅 420・文字 16〜18px に作り直し、凡例は本文へ移した。5 は要点を「分解と重心木の構築は」にそろえた。7 は重心木と cnt・cnt_i の説明を添えた）
- 指摘 6 (a)：本文の $\mathrm{fromPar}$ を $\mathrm{from\_par}$ にしてコードにそろえた
- 指摘 6 (b)：採らなかった。`depth_count`・`ordered_pairs`・`prefix` は短い補助の関数で、手引きのラムダの範囲「など」に入ると判断した。普通の関数に出すと dep・removed・k を引数で渡すことになり、中心の処理が読みにくくなる
- 提案（用語集）：「重心木」を用語集に足す案（各成分の重心を 1 つ前の重心の子にした根付き木）。足されたら #centroid-tree-queries の括弧の説明をリンクにする
