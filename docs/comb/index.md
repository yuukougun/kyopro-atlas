---
title: 数え上げ・確率・ゲーム
type: generated
---

<!-- tools/gen_site.py が生成する。手で直さない -->

# 数え上げ・確率・ゲーム

数え方の考え方、二項係数・包除、確率・期待値（期待値 DP を含む）、ゲーム（ゲーム DP を含む）。49 ページ。ページ名の横の印はレベル（[レベルの意味](../start/how-to-use.md#levels)）である。

学ぶ順：[色別ロードマップ](../guide/roadmap.md#reading-order)。使い分け：[数え方](../guide/method-comparison.md#counting)・[ゲーム](../guide/method-comparison.md#games)。問題集：[EDPC](../guide/problem-sets.md#problem-sets-dp)・[典型90問](../guide/problem-sets.md#problem-sets-typical90)・[鉄則本](../guide/problem-sets.md#problem-sets-tessoku-book)。自作：[自作ライブラリの設計と動作確認](../guide/library-design.md)。

## 数え上げの基礎

- [和・積の法則と順列・組合せ](counting-basics.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：排反な場合分けは足し、独立な段階の選択は掛けて数える。
- [二項係数の意味と性質](binomial-coefficient.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：n 個から k 個を選ぶ数 C(n,k) を、選び方・1 が k 個の 0/1 列・格子路の 3 つの意味で使い分ける。
- [二項係数の前計算](binomial-precompute.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：素数 p を法として階乗と逆階乗を前計算し、C(n,k) を O(1) で求める。
- [重複組合せ](stars-and-bars.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：x_1 + … + x_k = n の非負整数解は C(n+k−1, k−1) 個、正の整数解は C(n−1, k−1) 個で、玉と仕切りの並べ方に 1 対 1 に対応する。
- [格子路の数え上げ](lattice-paths.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：(0,0) から (a,b) への右・上の最短路は C(a+b, a) 通りで、R と U の列に 1 対 1 に対応する。
- [写像 12 相](twelvefold-way.md)：n 個の玉を k 個の箱に入れる方法を、玉・箱の区別の有無と各箱の個数の制限で 12 通りに分け、各マスの式と行き先のページを引く。

## 数え方の考え方

- [数え上げの考え方](counting-mindset.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>：数え上げを、対象の確定 → 数えやすい言い換え → 排反な場合の和と独立な段階の積 → 重複と漏れの確認 → 小さいケースでの検算の順に解く。
- [順序を固定して数える](counting-fix-order.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>：並べ方の一部の相対順序を固定して数え、全体の何分の一かを掛ける（k 個の順序が決まっていれば n!/k!）。
- [対応づけ・数える対象の言い換え](counting-bijection.md) <span class="kp-mini kp-lv-ao" title="difficulty 1600〜1999">青</span>：数えにくい対象を、個数が同じで数えやすい対象に 1 対 1 で対応させて数える。
- [重複の除き方](counting-dedup.md) <span class="kp-mini kp-lv-ao" title="difficulty 1600〜1999">青</span>：同じ対象を何度も数えてしまうとき、どれもちょうど c 回ずつなら c で割り、重複度がばらばらなら代表元を 1 つ決めて代表元だけを数える。
- [Burnside の補題](burnside-lemma.md) <span class="kp-mini kp-lv-hatten" title="difficulty 2400〜（概要だけ）">発展</span>：回転・反転などで同一視したときの異なるものの数を、各操作で動かないものの数の平均として求める。

## 二項係数の系統

- [多項係数](multinomial-coefficient.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>：種類ごとの個数が a_1, …, a_m の並べ方は (Σa_i)!/(a_1! … a_m!) 通りで、全部を区別した並べ方を同じ種類の入れ替えで割って得る。
- [二項係数の恒等式と和の公式](binomial-identities.md) <span class="kp-mini kp-lv-ao" title="difficulty 1600〜1999">青</span>：二項定理・Vandermonde の恒等式・縦の和（hockey stick）・吸収公式などで、二項係数を含む和を閉じた式にする。
- [鏡像法とカタラン数](reflection-principle.md) <span class="kp-mini kp-lv-ki" title="difficulty 2000〜2399">黄</span>：境界を越える格子路を、最初に境界に触れた点から先を折り返して別の終点への経路と 1 対 1 に対応させ、全体から引いて数える。
- [二項係数の部分和](binomial-prefix-sum.md) <span class="kp-mini kp-lv-hatten" title="difficulty 2400〜（概要だけ）">発展</span>：二項係数の部分和 S(n,K)（k ≤ K の C(n,k) の和）を、S(n+1,K) = 2S(n,K) − C(n,K) などの式で (n, K) を 1 ずつ動かしながら更新する。
- [LGV 補題](lgv-lemma.md) <span class="kp-mini kp-lv-hatten" title="difficulty 2400〜（概要だけ）">発展</span>：DAG 上で k 個の始点から k 個の終点への、互いに交わらない経路の組の数（符号付き）を、始点 i から終点 j への経路数を並べた行列の行列式で求める。
- [母関数の考え方](generating-function-counting.md) <span class="kp-mini kp-lv-hatten" title="difficulty 2400〜（概要だけ）">発展</span>：選び方の数を多項式の係数で表し、積で独立な選択の組合せ、累乗で同じ選択の繰り返しを表す。

## 包除の系統

- [包除原理](inclusion-exclusion.md) <span class="kp-mini kp-lv-ao" title="difficulty 1600〜1999">青</span>：どの条件も破らないものの個数を、条件の集合 S を少なくとも破るものの個数 N(S) の符号付きの和 Σ(−1)^|S| N(S) で求める。
- [包除 DP](inclusion-exclusion-dp.md) <span class="kp-mini kp-lv-ki" title="difficulty 2000〜2399">黄</span>：包除の和 Σ(−1)^|S| N(S) の項が多すぎて列挙できないとき、S を作る過程を DP にし、符号を DP の値に掛けて運ぶ。
- [約数包除](divisor-inclusion-exclusion.md) <span class="kp-mini kp-lv-ao" title="difficulty 1600〜1999">青</span>：gcd がちょうど g の個数 f(g) を、すべて g の倍数の個数 F(g) から大きい g の順に f(g) = F(g) − f(2g) − f(3g) − … で求める。
- [約数・倍数のゼータ変換とメビウス変換](zeta-mobius-divisor.md) <span class="kp-mini kp-lv-ao" title="difficulty 1600〜1999">青</span>：すべての d について d の倍数（約数）にわたる和を求める変換とその逆変換で、素数ごとに累積和を取って O(N log log N) で求める。
- [メビウス関数とメビウス反転](mobius-function.md) <span class="kp-mini kp-lv-ki" title="difficulty 2000〜2399">黄</span>：約数にわたる和 F(n)（d | n の f(d) の和）から f をメビウス関数 μ で戻す（メビウス反転）。
- [部分集合の高速ゼータ変換とメビウス変換](zeta-mobius-subset.md) <span class="kp-mini kp-lv-ki" title="difficulty 2000〜2399">黄</span>：すべての集合 S について、部分集合（上位集合）にわたる和を bit ごとの累積和として O(n 2^n) で求める（素朴には O(3^n)）。

## 置換・分割・木の数え上げ

- [置換の巡回分解](permutation-cycles.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：順列 P を i → P_i の矢印で描くといくつかの巡回に分かれ、任意の 2 要素の swap でソートする最小回数は N − (巡回の個数) になる。
- [置換の偶奇](permutation-parity.md) <span class="kp-mini kp-lv-ao" title="difficulty 1600〜1999">青</span>：同じ置換をどんな swap の列で作っても swap の回数の偶奇は変わらない（置換の符号）。
- [第 1 種スターリング数](stirling-first.md) <span class="kp-mini kp-lv-hatten" title="difficulty 2400〜（概要だけ）">発展</span>：ちょうど k 個の巡回からなる n 次の置換の数で、c(n,k) = c(n−1,k−1) + (n−1) c(n−1,k) を満たす。
- [第 2 種スターリング数とベル数](bell-number.md) <span class="kp-mini kp-lv-ao" title="difficulty 1600〜1999">青</span>：区別できる n 個を区別しない k 個の空でない組に分ける数が S(n,k)、組の数を問わない総数がベル数 B_n である。
- [整数の分割と分割数](partition-number.md) <span class="kp-mini kp-lv-ki" title="difficulty 2000〜2399">黄</span>：n を順序を区別せずに正の整数の和で表す方法の数が分割数 p(n) で、p(n,k) = p(n,k−1) + p(n−k,k) で数える。
- [Young 図形とフック長公式](young-tableaux.md) <span class="kp-mini kp-lv-hatten" title="difficulty 2400〜（概要だけ）">発展</span>：1〜N を Young 図形に行・列とも増加するように書き込む方法の数を、フック長公式 N!/Π(フック長) で求める。
- [ラベル付き木の数え上げ](cayley-pruefer.md) <span class="kp-mini kp-lv-ki" title="difficulty 2000〜2399">黄</span>：頂点にラベルのある n 頂点の木は n^(n−2) 個で、Prüfer 列に頂点 i がちょうど（次数 − 1）回現れることから、次数を指定した木は (n−2)!/Π(d_i − 1)! 個になる。
- [連結なグラフの数え上げ](counting-labeled-graphs.md) <span class="kp-mini kp-lv-ki" title="difficulty 2000〜2399">黄</span>：連結なものを全体 − 非連結なもので数え、非連結なものは頂点 1 を含む連結成分の大きさや頂点集合で分類して DP する。

## 確率・期待値

- [確率の基本](probability-basics.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：同様に確からしいときは「確率 = 条件を満たす場合の数 / 全体の場合の数」で、独立な事象は掛け、排反な事象は足す。
- [幾何分布とコンプリートガチャ](coupon-collector.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：成功確率 p の試行を成功するまで繰り返す回数の期待値は 1/p である。
- [確率・期待値を mod 998244353 で答える](rational-mod.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>：確率・期待値の既約分数 P/Q を P × Q^(−1) mod 998244353 で答える。
- [期待値の線形性と指示確率変数](linearity-of-expectation.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>：E[X + Y] = E[X] + E[Y] は独立でなくても成り立つので、複雑な量を部分の和に分けて各部分の期待値を足せる。
- [対称性で確率を求める](probability-symmetry.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>：入れ替えても変わらない対象は同じ確率を持つので、1 つの確率・期待値を求めて個数を掛ければよい。
- [確率 DP](probability-dp.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>：dp\[t][s] = 時刻 t に状態 s にいる確率を、初期状態の 1 から前向きに配って求める。
- [期待値 DP](expected-value-dp.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>：終わるまでの量の期待値 E[s] を、最初の一手で場合分けした E[s] = c(s) + Σ P(s→t) E[t] で、終状態の E = 0 から後ろ向きに埋める。
- [閉路のある期待値](expectation-linear-equations.md) <span class="kp-mini kp-lv-ao" title="difficulty 1600〜1999">青</span>：閉路があって後ろ向きに埋められない期待値を、戻る先の期待値を未知数 X とおき各状態を a + bX の形で持って、最後に X = a + bX を解いて求める。
- [最適戦略の期待値](optimal-strategy-expectation.md) <span class="kp-mini kp-lv-ki" title="difficulty 2000〜2399">黄</span>：選択と偶然が交互に来る確率過程で、期待値を最大（最小）にする戦略のもとでの期待値を、残すものや知っている情報を状態にして後ろから求める。
- [期待値と確率の変換](expectation-tail-sum.md) <span class="kp-mini kp-lv-ki" title="difficulty 2000〜2399">黄</span>：非負整数の確率変数 X について、E[X] は k ≥ 1 の P(X ≥ k) の和に等しい。
- [二乗の期待値・分散](expectation-of-square.md) <span class="kp-mini kp-lv-ki" title="difficulty 2000〜2399">黄</span>：E[X^2] は線形性で直接は求まらないので、X^2 = Σ_i Σ_j X_i X_j とペアごとの期待値を足すか、DP で確率・期待値 × 確率・二乗の期待値 × 確率を同時に運ぶ。
- [連続値の確率](continuous-probability.md) <span class="kp-mini kp-lv-hatten" title="difficulty 2400〜（概要だけ）">発展</span>：[0, 1] の一様乱数のような連続な確率変数について、確率は長さ・面積・角度の比、期待値は積分で求める。

## ゲーム

- [ゲームの基本と勝敗の DP](game-basics.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>：二人零和有限確定完全情報ゲームの各局面は、手番の人の必勝か必敗に決まる。
- [ミニマックス](minimax.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>：両者が「自分の得点 − 相手の得点」を最大化するゲームで、f(局面) = 手番の人が以後に得る差の最大値とおくと f = max(その手の得点 − f(次の局面)) と 1 本の式で書け、後ろから値が決まる。
- [Nim と XOR](nim.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>：山から 1 個以上取り合い最後の石を取った方が勝つゲームは、全山の個数の XOR が 0 なら後手必勝、そうでなければ先手必勝である。
- [Grundy 数と Sprague-Grundy の定理](grundy-number.md) <span class="kp-mini kp-lv-ao" title="difficulty 1600〜1999">青</span>：不偏ゲームの局面に Grundy 数 g = mex{次の局面の g} を割り当てると g = 0 ⇔ 必敗で、独立なゲームの和の Grundy 数は各 Grundy 数の XOR になる。
- [後退解析](game-retrograde-analysis.md) <span class="kp-mini kp-lv-ki" title="difficulty 2000〜2399">黄</span>：局面の遷移に閉路があり引き分け（終わらない）もありうるゲームで、終局から逆辺をたどって勝敗を確定させる。
- [非不偏ゲーム](partizan-games.md) <span class="kp-mini kp-lv-hatten" title="difficulty 2400〜（概要だけ）">発展</span>：先手と後手で取れる手が違うゲームでは Grundy 数が使えないので、局面に数（超現実数）を割り当て、独立な部分の和の符号で勝敗を判定する。

## ほかの分野にある関連ページ {#elsewhere}

種類に[数え上げ](../lists/kind-counting.md)・[確率・期待値](../lists/kind-probability.md)・[ゲーム](../lists/kind-game.md)のどれかを持つ、ほかの分野のページ。

- [考察](../thinking/index.md)：[主客転倒・寄与](../thinking/contribution.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>・[余事象](../thinking/complement.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>
- [動的計画法](../dp/index.md)：[戻す DP](../dp/knapsack-undo.md) <span class="kp-mini kp-lv-ao" title="difficulty 1600〜1999">青</span>・[部分列 DP](../dp/subsequence-dp.md) <span class="kp-mini kp-lv-ki" title="difficulty 2000〜2399">黄</span>・[区間 DP の応用](../dp/interval-dp-advanced.md) <span class="kp-mini kp-lv-ki" title="difficulty 2000〜2399">黄</span>・[桁 DP](../dp/digit-dp.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>・[桁 DP の応用](../dp/digit-dp-advanced.md) <span class="kp-mini kp-lv-ki" title="difficulty 2000〜2399">黄</span>・[挿入 DP・箱根駅伝 DP](../dp/insertion-dp.md) <span class="kp-mini kp-lv-ki" title="difficulty 2000〜2399">黄</span>
- [グラフ](../graph/index.md)：[彩色数・最大独立集合・最大クリーク](../graph/chromatic-number.md) <span class="kp-mini kp-lv-hatten" title="difficulty 2400〜（概要だけ）">発展</span>・[行列木定理](../graph/matrix-tree-theorem.md) <span class="kp-mini kp-lv-hatten" title="difficulty 2400〜（概要だけ）">発展</span>
- [木](../tree/index.md)：[木の次数列と Prüfer 列](../tree/tree-degree.md) <span class="kp-mini kp-lv-ao" title="difficulty 1600〜1999">青</span>
- [データ構造](../ds/index.md)：[転倒数](../ds/inversion-number.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>
- [整数論・代数](../math/index.md)：[Σ の変形](../math/sigma-manipulation.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>・[形式的冪級数と多項式の演算](../math/fps-basics.md) <span class="kp-mini kp-lv-hatten" title="difficulty 2400〜（概要だけ）">発展</span>
