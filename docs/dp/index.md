---
title: 動的計画法
type: generated
---

<!-- tools/gen_site.py が生成する。手で直さない -->

# 動的計画法

DP の考え方、列・区間・集合・桁・木の DP、DP の高速化。38 ページ。ページ名の横の印はレベル（[レベルの意味](../start/how-to-use.md#levels)）である。

学ぶ順：[色別ロードマップ](../guide/roadmap.md#reading-order)。使い分け：[最適化の方針](../guide/method-comparison.md#optimization)・[小さい N の全探索](../guide/method-comparison.md#small-n)・[木の手法](../guide/method-comparison.md#trees)。問題集：[EDPC](../guide/problem-sets.md#problem-sets-dp)・[典型90問](../guide/problem-sets.md#problem-sets-typical90)・[TDPC](../guide/problem-sets.md#problem-sets-tdpc)。自作：[自作ライブラリの設計と動作確認](../guide/library-design.md)。

## DP の考え方

- [DP の基本](dp-basics.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：全探索で同じ部分問題が何度も現れるとき、状態ごとの最良値や場合の数を表に 1 回だけ求めて使い回す。
- [メモ化再帰](memoized-recursion.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：漸化式を再帰関数のまま書き、計算済みの値を覚えて使い回す。
- [DAG 上の DP](dp-dag.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：閉路のない有向グラフで、最長路や経路の数をトポロジカル順の DP で O(N+M) で求める。
- [DP の計算順序](dp-order.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>：dp[x] を計算する時点で、依存する値がすべて確定している順に状態を回す。
- [DP の状態の設計](dp-state-design.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>：過去の選び方そのものではなく、将来の選び方と評価に影響する要約（直前の値・個数・末尾の数文字・開き括弧の数など）だけを状態に持つ。
- [余り・個数を状態に持つ DP](dp-mod-state.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>：「和が M の倍数」「平均が整数」のような条件は、和そのものではなく M で割った余りを状態に持てば数えられる。
- [フェーズを状態に持つ DP](dp-phase.md) <span class="kp-mini kp-lv-ao" title="difficulty 1600〜1999">青</span>：区間を 1 つ選ぶ・何文字目まで集めたか、のように各位置でいまどの段階にいるかを状態に持つ。
- [DP の復元](dp-reconstruction.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>：最適値だけでなく選び方そのものを出力するとき、完成した表を終端から逆にたどって最適な遷移を復元する。
- [累積和・いもす法による DP の高速化](dp-prefix-sum.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>：遷移元が連続した範囲の和になる DP を、前の段の累積和で 1 回 O(1) にする。

## 列の DP

- [ナップサック DP](knapsack-01.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：品物を 1 つずつ「選ぶ・選ばない」で分け、重さの合計ごとに価値の最大を求める。
- [部分和 DP](subset-sum.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：いくつか選んで作れる和の集合や、和が S になる選び方の数を、和を添字にした DP で求める。
- [DP の状態の削減](dp-dimension-reduction.md) <span class="kp-mini kp-lv-ao" title="difficulty 1600〜1999">青</span>：DP の表が大きすぎるとき、範囲を上限で打ち切るか、ほかの添字から決まる量・支配される量を値の側に回して状態を減らす。
- [戻す DP](knapsack-undo.md) <span class="kp-mini kp-lv-ao" title="difficulty 1600〜1999">青</span>：数え上げの部分和 DP の更新は逆向きに解けるので、要素を 1 つ取り除いた状態に戻せる。
- [並べ替えてから DP する](exchange-argument-dp.md) <span class="kp-mini kp-lv-ao" title="difficulty 1600〜1999">青</span>：選ぶ集合が決まれば最適な順序がソートで決まるとき、先にその順に並べてから「選ぶ・選ばない」の DP をする。
- [グリッド上の DP](dp-grid.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>：右か下にしか動けないグリッドで、経路の数や経路上の値の最大を、マスの昇順の DP で求める。
- [区間分割 DP](dp-sequence-partition.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>：列をいくつかの区間に区切る方法の数や最小コストを、最後の区間の左端 j で分けて求める。
- [最長増加部分列](lis.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>：列から順序を保って選ぶ増加列の最長を、長さごとの末尾の最小値の配列を二分探索で更新して O(N log N) で求める。
- [最長共通部分列と編集距離](lcs.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>：2 つの文字列の最長共通部分列の長さを、末尾どうしが一致するかで分ける 2 次元の DP で O(NM) で求める。
- [部分列 DP](subsequence-dp.md) <span class="kp-mini kp-lv-ki" title="difficulty 2000〜2399">黄</span>：異なる部分列の個数を、各文字を「まだ使っていない位置のうち最も左」から取る取り出し方だけを数えて求める。

## 状態の形で分かれる DP

- [区間 DP](interval-dp.md) <span class="kp-mini kp-lv-ao" title="difficulty 1600〜1999">青</span>：dp\[l][r]＝区間 [l, r) について求めた値を、内側の短い区間の値から求める。
- [区間 DP の応用](interval-dp-advanced.md) <span class="kp-mini kp-lv-ki" title="difficulty 2000〜2399">黄</span>：区間 DP の上で、DFS 順の区間を部分木とみる木の数え上げ、区間ごとの Grundy 数、訪れた範囲の両端を状態にする移動などを解く。
- [bitDP](bit-dp.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>：順列の探索のうち将来に効くのが「使ったものの集合」と「最後に使ったもの」だけなら、状態を 2^N·N に減らせる。
- [部分集合を列挙する DP](subset-enumeration-dp.md) <span class="kp-mini kp-lv-ao" title="difficulty 1600〜1999">青</span>：集合を部分集合と残りに分ける遷移を T = (T − 1) & S で列挙し、グループ分けの最適値や数を全体 O(3^N) で求める。
- [プロファイル DP](broken-profile-dp.md) <span class="kp-mini kp-lv-ki" title="difficulty 2000〜2399">黄</span>：幅の小さいグリッドを 1 マスずつ進め、まだ処理していない部分に影響する境界の情報だけを bit で持って、敷き詰め方や塗り方を数える。
- [桁 DP](digit-dp.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>：N 以下の整数のうち条件を満たすものの個数や総和を、上の桁から決め、それまでの桁が N と一致しているかのフラグと問題の情報を状態にして求める。
- [桁 DP の応用](digit-dp-advanced.md) <span class="kp-mini kp-lv-ki" title="difficulty 2000〜2399">黄</span>：桁 DP を、2 つ以上の数を同時に決める・下の桁からの繰り上がりを状態にする・種類の少ない状態を map や bit で持つ、などに広げる。
- [木 DP](tree-dp.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>：根を決めると同じ頂点の子の部分木どうしは交わらない小問題に分かれるので、部分木ごとの値を子の値から帰りがけ順に求める。
- [全方位木 DP](rerooting.md) <span class="kp-mini kp-lv-ao" title="difficulty 1600〜1999">青</span>：すべての頂点を根としたときの木 DP の値を、下向きの値と親側の部分木の値を 2 回の DFS で求めて O(N) で出す。
- [二乗の木 DP](tree-dp-square.md) <span class="kp-mini kp-lv-ki" title="difficulty 2000〜2399">黄</span>：子の配列を順にマージする木の上のナップサックのような DP は、配列の長さを部分木のサイズに合わせると全体 O(N^2) で済む。
- [挿入 DP・箱根駅伝 DP](insertion-dp.md) <span class="kp-mini kp-lv-ki" title="difficulty 2000〜2399">黄</span>：順列を、決めた部分の相対順位や「相手が未定の要素の数」だけを状態にして数える。

## DP の高速化

- [DP の高速化の選び方](dp-speedup-overview.md)：素直な DP が間に合わないとき、貰う形の式の右辺の形（区間の和・区間の最小・多項式の積・同じ線形の遷移の繰り返し・一次関数の最小など）から速くする道具を選ぶ。
- [セグメント木・スライド最小値による DP の高速化](dp-segment-tree.md) <span class="kp-mini kp-lv-ao" title="difficulty 1600〜1999">青</span>：遷移元が添字や値の範囲の最小・最大・和になる DP を、dp の値をセグメント木に載せて 1 回 O(log N) にする。
- [インライン DP](inline-dp.md) <span class="kp-mini kp-lv-ao" title="difficulty 1600〜1999">青</span>：dp\[i][\*] から dp\[i+1][\*] へほとんどの値がそのまま写るとき、配列を 1 本だけ持って変わる場所だけを書き換える。
- [動的 DP](dynamic-dp.md) <span class="kp-mini kp-lv-hatten" title="difficulty 2400〜（概要だけ）">発展</span>：列の各位置の遷移を小さな行列にしてセグメント木に載せると、1 点の書き換えのたびに DP の答えを O(S^3 log N) で求め直せる。
- [Convex Hull Trick と Li Chao Tree](cht.md) <span class="kp-mini kp-lv-hatten" title="difficulty 2400〜（概要だけ）">発展</span>：dp[i] = min_j (dp[j] + a_j·x_i + b_j) のように遷移が一次関数の最小になる DP を、下側の包絡線を持って速くする。
- [Monge 性による DP の高速化](monge.md) <span class="kp-mini kp-lv-hatten" title="difficulty 2400〜（概要だけ）">発展</span>：コスト c(i, j) が Monge なら各行の最小値を取る位置が単調になり、分割統治（monotone minima）や Knuth-Yao で区間分割 DP・区間 DP を速くできる。
- [Alien DP](alien-dp.md) <span class="kp-mini kp-lv-hatten" title="difficulty 2400〜（概要だけ）">発展</span>：「ちょうど K 個選ぶ」制約のついた最適化で答えが K について凸なら、1 個あたりの罰金 λ を足して制約を外した問題を解き、選ばれる個数が K になる λ を二分探索する。
- [Slope Trick](slope-trick.md) <span class="kp-mini kp-lv-hatten" title="difficulty 2400〜（概要だけ）">発展</span>：dp[x] が x について区分線形で凸なとき、傾きが変わる点を 2 つの優先度付きキューで持ち、「|x − a| を足す」「累積 min を取る」「平行移動」を 1 回 O(log N) で行う。

## ほかの分野にある関連ページ {#elsewhere}

種類に[DP](../lists/kind-dp.md)を持つ、ほかの分野のページ。

- [グラフ](../graph/index.md)：[彩色数・最大独立集合・最大クリーク](../graph/chromatic-number.md) <span class="kp-mini kp-lv-hatten" title="difficulty 2400〜（概要だけ）">発展</span>・[ワーシャルフロイド法](../graph/warshall-floyd.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>・[最短路 DAG](../graph/shortest-path-dag.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>・[最小シュタイナー木](../graph/steiner-tree.md) <span class="kp-mini kp-lv-hatten" title="difficulty 2400〜（概要だけ）">発展</span>
- [木](../tree/index.md)：[Static Top Tree と木 DP の動的更新](../tree/static-top-tree.md) <span class="kp-mini kp-lv-hatten" title="difficulty 2400〜（概要だけ）">発展</span>
- [整数論・代数](../math/index.md)：[行列累乗](../math/matrix-power.md) <span class="kp-mini kp-lv-ao" title="difficulty 1600〜1999">青</span>・[分割統治 FFT・オンライン畳み込み](../math/online-convolution.md) <span class="kp-mini kp-lv-hatten" title="difficulty 2400〜（概要だけ）">発展</span>
- [数え上げ・確率・ゲーム](../comb/index.md)：[重複の除き方](../comb/counting-dedup.md) <span class="kp-mini kp-lv-ao" title="difficulty 1600〜1999">青</span>・[包除 DP](../comb/inclusion-exclusion-dp.md) <span class="kp-mini kp-lv-ki" title="difficulty 2000〜2399">黄</span>・[第 2 種スターリング数とベル数](../comb/bell-number.md) <span class="kp-mini kp-lv-ao" title="difficulty 1600〜1999">青</span>・[整数の分割と分割数](../comb/partition-number.md) <span class="kp-mini kp-lv-ki" title="difficulty 2000〜2399">黄</span>・[連結なグラフの数え上げ](../comb/counting-labeled-graphs.md) <span class="kp-mini kp-lv-ki" title="difficulty 2000〜2399">黄</span>・[確率 DP](../comb/probability-dp.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>・[期待値 DP](../comb/expected-value-dp.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>・[最適戦略の期待値](../comb/optimal-strategy-expectation.md) <span class="kp-mini kp-lv-ki" title="difficulty 2000〜2399">黄</span>・[閉路のある期待値](../comb/expectation-linear-equations.md) <span class="kp-mini kp-lv-ao" title="difficulty 1600〜1999">青</span>・[ゲームの基本と勝敗の DP](../comb/game-basics.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>・[ミニマックス](../comb/minimax.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>・[後退解析](../comb/game-retrograde-analysis.md) <span class="kp-mini kp-lv-ki" title="difficulty 2000〜2399">黄</span>
- [文字列](../string/index.md)：[照合オートマトン上の DP](../string/string-automaton-dp.md) <span class="kp-mini kp-lv-ao" title="difficulty 1600〜1999">青</span>
- [その他の技法](../misc/index.md)：[bitset による高速化](../misc/bitset-speedup.md) <span class="kp-mini kp-lv-ao" title="difficulty 1600〜1999">青</span>
