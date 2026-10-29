---
title: 木
type: generated
---

<!-- tools/gen_site.py が生成する。手で直さない -->

# 木

木の性質、直径・LCA・オイラーツアー・マージテク・重心など。26 ページ。ページ名の横の印はレベル（[レベルの意味](../start/how-to-use.md#levels)）である。

学ぶ順：[色別ロードマップ](../guide/roadmap.md#reading-order)。使い分け：[木の手法](../guide/method-comparison.md#trees)。問題集：[典型90問](../guide/problem-sets.md#problem-sets-typical90)。自作：[自作ライブラリの設計と動作確認](../guide/library-design.md)。

## 木の基礎

- [木の基本性質と表現](tree-basics.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：連結で閉路がない・連結で辺が N−1 本・閉路がなく辺が N−1 本・どの 2 点間もパスが 1 本、の 4 つは同値で、辺を 1 本除くと 2 つに分かれ、1 本足すと閉路ができる。
- [根付き木と走査順](tree-traversal.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：根を決めて DFS か BFS をすると、親・深さ・部分木サイズ・行きがけ順・帰りがけ順が O(N) で求まる。
- [木の 2 色塗り分けと距離の偶奇](tree-bipartite.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：木は閉路がないので深さの偶奇で必ず 2 色に塗れ、2 点の距離の偶奇は深さの和の偶奇で分かる。
- [木の上の距離](tree-distance.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：木では 2 点間のパスが一意なので、重み付きでも DFS 1 回で 1 点からの距離が求まる。
- [木の上の累積和・いもす法](tree-imos.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：部分木への加算をまとめて受けてから値を出力するなら、部分木の根に印を置いて根から下へ累積する。
- [指定頂点を結ぶ最小の部分木](steiner-subtree.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：指定した K 頂点をすべて含む最小の連結な部分グラフは一意な部分木で、指定頂点の 1 つを根にして、部分木に指定頂点を含む頂点を残せば求まる。
- [完全二分木](complete-binary-tree.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：頂点 i の子が 2i と 2i+1、親が ⌊i/2⌋ の木は深さが log N 程度しかないので、N が 10^18 でも祖先を全部たどれる。
- [葉から考える](leaf-first.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>：葉は辺が 1 本しかないので選択肢が少なく、葉から順に決めると貪欲が正しくなりやすい。
- [木の次数列と Prüfer 列](tree-degree.md) <span class="kp-mini kp-lv-ao" title="difficulty 1600〜1999">青</span>：各次数が 1 以上で和が 2N−2 なら、その次数列の木が必ず作れる。

## 木全体の形

- [木の直径と最遠点](tree-diameter.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>：直径（最も遠い 2 点を結ぶパス）は、任意の点から最も遠い点 a を求め、a から最も遠い点 b を求めれば a–b になる（重みが非負のとき）。
- [辺で切って数える](tree-edge-contribution.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>：全ペアのパスについての量の和を、各辺（頂点）が何ペアのパスに含まれるかで数え直す。
- [木の構築・復元](tree-construction.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>：距離の情報・訪問順・次数の条件などから、条件を満たす木を作るか、ないと判定する（何通りあるかを数えることもある）。
- [木の重心](tree-centroid.md) <span class="kp-mini kp-lv-ki" title="difficulty 2000〜2399">黄</span>：取り除いたときに残る成分の大きさがすべて N/2 以下になる頂点（重心。1 個か隣り合う 2 個ある）を、部分木サイズから O(N) で求める。
- [木の同型判定と木のハッシュ](tree-isomorphism.md) <span class="kp-mini kp-lv-hatten" title="difficulty 2400〜（概要だけ）">発展</span>：根付き木の同型は、葉から順に「子の部分木の名前の多重集合」に名前を付ける AHU 法か、多重集合のハッシュで判定する。

## パス

- [最小共通祖先（LCA）](lca.md) <span class="kp-mini kp-lv-ao" title="difficulty 1600〜1999">青</span>：根付き木で 2 頂点の共通の祖先のうち最も深いものを、各頂点の 2^k 個上の祖先の表（ダブリング）で、前処理 O(N log N)・1 回 O(log N) で求める。
- [木の上のパスの判定と分解](tree-path.md) <span class="kp-mini kp-lv-ao" title="difficulty 1600〜1999">青</span>：パス u–v を「u から LCA へ上る」と「LCA から v へ下る」に分け、点がパス上にあるか・3 点の合流点・2 本のパスの交差・パス上の K 番目の頂点を、LCA と距離の式で判定する。
- [根からのパスを DFS で持ち回る](root-path-dfs.md) <span class="kp-mini kp-lv-ao" title="difficulty 1600〜1999">青</span>：DFS で頂点に入るときにデータ構造へ情報を足し、出るときに元に戻すと、常に根から今の頂点までのパスの情報だけを持てる。

## 部分木とパスのクエリ

- [オイラーツアー](euler-tour.md) <span class="kp-mini kp-lv-ao" title="difficulty 1600〜1999">青</span>：DFS の行きがけ順に番号 in[v] を振り、子孫を回り終えた時点の番号 out[v] を記録すると、v の部分木が列の区間 [in[v], out[v]) になる。
- [HL 分解](hld.md) <span class="kp-mini kp-lv-hatten" title="difficulty 2400〜（概要だけ）">発展</span>：各頂点で部分木が最大の子へ重い辺を引き、重いパスごとに番号が連続するように振ると、任意のパスが O(log N) 個の区間に分かれる。
- [Static Top Tree と木 DP の動的更新](static-top-tree.md) <span class="kp-mini kp-lv-hatten" title="difficulty 2400〜（概要だけ）">発展</span>：頂点の値を書き換えるたびに、木 DP の根の値を O(log N) 程度で更新する。
- [動的木](dynamic-tree.md) <span class="kp-mini kp-lv-hatten" title="difficulty 2400〜（概要だけ）">発展</span>：辺の追加と削除がある森で、パスのクエリや根の付け替えを償却 O(log N) で処理する Link-Cut Tree と、部分木のクエリ向けの Euler Tour Tree、両方に使える Top Tree がある。

## まとめる・分ける

- [マージテク](small-to-large.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>：2 つの集合を併合するとき小さい方の要素を大きい方へ移すと、1 つの要素が移るのは高々 log N 回なので全体で O(N log N) になる。
- [重心分解](centroid-decomposition.md) <span class="kp-mini kp-lv-ki" title="difficulty 2000〜2399">黄</span>：重心を取り、重心を通るパスを一度に処理してから重心を消し、残った各成分で再帰する。
- [Auxiliary Tree](auxiliary-tree.md) <span class="kp-mini kp-lv-hatten" title="difficulty 2400〜（概要だけ）">発展</span>：色ごと・クエリごとに少数の頂点だけが関わる木の問題で、指定頂点と DFS 順で隣り合う 2 点の LCA だけからなる圧縮木を作って木 DP をする。
- [併合過程の木](merge-process-tree.md) <span class="kp-mini kp-lv-hatten" title="difficulty 2400〜（概要だけ）">発展</span>：Union-Find の併合のたびに新しい頂点を作って 2 つの成分を子にした木を作ると、ある時点のグループが DFS 順の区間になる。
- [比で親に併合する貪欲](tree-ratio-greedy.md) <span class="kp-mini kp-lv-hatten" title="difficulty 2400〜（概要だけ）">発展</span>：「親を子より先に選ぶ」制約つきで、順番に依存する重み付きの和を最適化する。

## ほかの分野にある関連ページ {#elsewhere}

種類に[木](../lists/kind-tree.md)を持つ、ほかの分野のページ。

- [動的計画法](../dp/index.md)：[木 DP](../dp/tree-dp.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>・[全方位木 DP](../dp/rerooting.md) <span class="kp-mini kp-lv-ao" title="difficulty 1600〜1999">青</span>・[二乗の木 DP](../dp/tree-dp-square.md) <span class="kp-mini kp-lv-ki" title="difficulty 2000〜2399">黄</span>
- [グラフ](../graph/index.md)：[なもりグラフ](../graph/namori-graph.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>
- [数え上げ・確率・ゲーム](../comb/index.md)：[ラベル付き木の数え上げ](../comb/cayley-pruefer.md) <span class="kp-mini kp-lv-ki" title="difficulty 2000〜2399">黄</span>
