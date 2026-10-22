# root-path-dfs の問題の補充（b6・工程9）

- ページ：docs/tree/root-path-dfs.md（レベル 青）
- 今の問題：例題 abc198_e・abc165_f、練習 abc273_e の 1 問、力試し abc218_g・abc302_h
- 結論：練習の候補 1 問（abc453_g。足すと練習は合わせて 2 問）と、力試しの候補 1 問（abc133_f）を確かめた。題名・difficulty は `python3 tools/ap.py show` で確かめた（2026-10-22）
- 探した順：
    1. b1・b3・b5 の summary/candidates.md と b2 の報告 planning/batches/b2/root-path-dfs.md の「問題の補充の候補」。b2・b3 は「abc319 以降の問題なし。候補なし」、b1 は abc218_g（既に力試し）だけ、b5 には root-path-dfs の行がない
    2. data/problems.yaml：pages に root-path-dfs を持つのは本文の 5 問だけ。approach に「戻す・取り消す・根からのパス」を含む問題を台帳全体から探し、abc133_f（tree-path:practice）を見つけた。また persistent-data-structures の例題 abc453_g の approach に「先読みして版の木をたどってもよい」とあり、このページの #to-version-tree の方法に当たる
    3. 第三者の解説：上の 2 問の解説を開いて確かめた。Web 検索はセッション全体の上限（200 回）に達していて使えなかったので、台帳と ap.py の題名検索（Tree・Path・Ancestor・Root・Undo・Rollback・Save・Load・History・Version など）から探した。台帳にない新しい問題は見つけられていない

## 練習の候補（practice）

### abc453_g　G. Copy Query（diff 1735・青）

- 台帳：登録済み（persistent-data-structures:example）。pages に {id: root-path-dfs, role: practice} を足し、alternatives に root-path-dfs 向けの approach（下の方針の要点）を足す提案
- 要約：長さ M の数列が N 本あり、ある数列を別の数列へ丸ごと写す・1 点を書き換える・区間の和を答える、の 3 種類のクエリを順に処理する。
- 方針の要点：クエリを先に読み、1 点の書き換えを「数列が今指す版の子を作る」、写しを「版の指し替え」とみなして版の木を作り、セグメント木（BIT）を 1 つだけ持って版の木を DFS し、入るときに書き換えて元の値を覚え、区間の和の質問に答えてから出るときに元へ戻す。
- このページとの対応：#to-version-tree の「クエリをすべて先に読めるなら、版の木を DFS して入るとき施し出るとき巻き戻す」そのもの。変更の記録は 1 頂点で 1 件（位置と元の値）で、#undo-log の形になる。オンラインの解き方（永続セグメント木）は永続データ構造のページの例題で、こちらはその先読み版の練習という位置づけになる
- 裏付け：
    - https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2026/0411_abc453 （先読みして版の木を作り、DFS で入るとき 1 点更新して元の値を保存し、出るときに戻す解法を確かめた。永続セグメント木の解法も併記。制約 N, M, Q ≤ 2×10^5）
    - https://www.cnblogs.com/CR-J/p/19853087 （問題の設定の確認。解き方は永続セグメント木で、版の木の DFS には触れていない）

## 力試しの候補（challenge）

### abc133_f　F. Colorful Tree（diff 2330・黄）

- 台帳：登録済み（tree-path:practice。persistent-data-structures の b6 の報告で challenge の提案あり）。pages に {id: root-path-dfs, role: challenge} を足す提案。difficulty が青の帯から離れる（黄）ので力試しにする
- 要約：辺に色と長さがある木で、色 x の辺の長さをすべて y に変えたときの 2 頂点 u, v の距離を、独立な質問それぞれについて答える。
- 方針の要点：距離を「根からの距離（u）＋（v）−2×（LCA）」に分け、質問を 3 頂点に割り振ってから、色ごとの辺の本数と長さの和を持って DFS し（入るとき足し、出るとき引く）、各頂点でその色の分だけ長さを差し替えた根からの距離を求める。
- このページとの対応：#stack-is-path の出現回数の足し引きを、色ごとの「本数」と「長さの和」の 2 つに広げた形。答えを読むのが u・v・LCA の 3 頂点で、LCA で組み立てる部分は tree-path（・lca）の内容
- 裏付け：
    - https://blog.hamayanhamayan.com/entry/2019/07/08/213009 （LCA で 3 頂点に分け、DFS で色ごとの tot・cnt を入るとき足し戻るとき引き、頂点に着いたときに質問を評価する解法を確かめた。台帳の evidence）
    - https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2019/0707_abc133 （同じ方針。必要な（頂点, 色）の組だけ記録し、入るとき更新して出るとき戻す）

## 除いたもの・調べ残し

- abc477_g（Frequency Query on Tree、diff 2226）：題名は近いが、台帳の方針は木の上の Mo で、このページの手法ではない
- abc201_e（Xor Distances、diff 1694）：根からの XOR を引数で渡すだけで済み、本文の tip「足すだけで済むなら引数で渡す」の型。巻き戻しが要らないので練習には弱い（台帳では tree-distance:practice）
- abc309_e（Family and Insurance、diff 957）：#path-statistics の「祖先から何世代下まで届くか」の型だが、帯（青）から遠く、最大値を受け継ぐだけで解ける（tree-imos#depth-limited の持ち分）
- abc337_g（Tree Inversion、diff 2080）：部分木の個数を数える型で、根からのパスの情報だけでは決まらないので除いた（解説は開いていない）
- abc319 以降の「根からのパスを巻き戻しで持つ」問題は、b2・b3 と同じく、abc453_g 以外に見つけられなかった。Web 検索の上限のため第三者の解説の横断検索はできていない。上限が戻ったら「根からのパス DFS 戻す」「木 巻き戻し ABC」などで探し直す余地がある
- 新しく使ったドメイン：なし（ikatakos.com・blog.hamayanhamayan.com・www.cnblogs.com はどれも付録 B にある）

## 本文に足すときのメモ

- 練習の並びは易しい順に abc273_e（1624）→ abc453_g（1735）。abc273_e は列の末尾だけなので版の木を持つだけ、abc453_g は版の木を DFS して和を巻き戻す、と #to-version-tree の 2 段の練習になる
- 力試しは abc218_g（2217）→ abc133_f（2330）→ abc302_h（2407）の順
