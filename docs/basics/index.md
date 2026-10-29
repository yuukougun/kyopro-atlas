---
title: 基本テクニック
type: generated
---

<!-- tools/gen_site.py が生成する。手で直さない -->

# 基本テクニック

計算量の見積もり、全探索、二分探索、累積和・いもす法、尺取り法、ソート・座標圧縮、貪欲、半分全列挙、ダブリング、分割統治、周期性、bit 演算。32 ページ。ページ名の横の印はレベル（[レベルの意味](../start/how-to-use.md#levels)）である。

学ぶ順：[色別ロードマップ](../guide/roadmap.md#reading-order)。使い分け：[二分探索の種類](../guide/method-comparison.md#binary-search)・[小さい N の全探索](../guide/method-comparison.md#small-n)・[繰り返しの高速化](../guide/method-comparison.md#repetition)・[最適化の方針](../guide/method-comparison.md#optimization)。問題集：[典型90問](../guide/problem-sets.md#problem-sets-typical90)。

## 計算量と bit 演算

- [計算量の見積もり](complexity-estimation.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：制約の大きさから許される計算量を逆算し、使える手法の候補を絞る。
- [bit 演算の基本と XOR の性質](bit-operations.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：XOR の打ち消し（x xor x = 0）、a + b = (a xor b) + 2(a and b)、0〜n の XOR の周期などで式を簡単にする。
- [bit ごとに独立に考える](bitwise-independence.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>：XOR・AND・OR の結果は bit ごとに独立に決まるので、bit ごとに 0 と 1 の個数を数えて 2^k を掛けて足す。

ほかの章の関連ページ：[bit 全探索と順列全探索](bit-full-search.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>（全探索の章）

## 全探索

- [全探索の設計](brute-force.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：何を全探索するかを選び直して通り数を減らす。
- [bit 全探索と順列全探索](bit-full-search.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：N ≤ 20 程度なら部分集合 2^N 通りを整数の各 bit で表して全部試し、N ≤ 8〜10 なら順列 N! 通りを next_permutation で全部試す。
- [再帰による全列挙](recursive-enumeration.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>：部分的に決めた状態から 1 つずつ決めていく再帰で、条件を満たす数・組分け・敷き詰めを全部列挙する。

## ソートと二分探索

- [ソートで考える](sorting-techniques.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：並べ替えてよい問題では、ソートすると貪欲の順番が決まり、二分探索や尺取りが使えるようになる。
- [二分探索](binary-search.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：単調な条件の境界を、ok 側と ng 側の不変条件を保ちながら区間を半分ずつ狭めて O(log N) で見つける。
- [答えで二分探索](binary-search-answer.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：「答えを x にできるか」の判定が x について単調なら、x を二分探索して最適値を求める。
- [座標圧縮](coordinate-compression.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：値を sort・unique・lower_bound で 0〜K−1 の番号に置き換え、大小関係だけを残したまま配列の添字にできるようにする。
- [イベントソートと平面走査の基本](event-sort.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>：区間の開始・終了・クエリを (座標, 種類) の組にして並べ、左から順に処理しながら集合や合計を更新する。

ほかの章の関連ページ：[区間スケジューリング・区間の串刺し](interval-scheduling.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>（貪欲の章）・[交換論法と比較関数の設計](exchange-argument.md) <span class="kp-mini kp-lv-ao" title="difficulty 1600〜1999">青</span>（貪欲の章）

## 累積和といもす法

- [累積和](prefix-sum.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：S[0] = 0、S[i+1] = S[i] + a[i] と前計算すると、区間 [l, r) の和が S[r] − S[l] で O(1) で求まる。
- [累積和と連想配列で区間を数える](prefix-sum-counting.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：和がちょうど K の区間や和が M の倍数の区間の個数を、条件を S_r と S_l の関係に言い換えて数える。
- [2 次元累積和](prefix-sum-2d.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>：長方形領域の和を、S\[i+1][j+1] = S\[i][j+1] + S\[i+1][j] − S\[i][j] + a\[i][j] の前計算と 4 項の足し引きで O(1) で求める。
- [いもす法](imos.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：区間 [l, r) に x を足す操作を D[l] += x、D[r] −= x と記録し、最後に累積和を取って一度に反映する。
- [差分列への言い換え](difference-sequence.md) <span class="kp-mini kp-lv-ki" title="difficulty 2000〜2399">黄</span>：区間に ±1 する操作の最小回数や可否を、隣接差の列（差分列）の 2 点の操作に言い換えて解く。

## 尺取り法とランレングス圧縮

- [尺取り法](two-pointers.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：区間 [l, r) について、各 l に対する最大（最小）の r が l とともに単調に増えるなら、r を戻さずに動かして全体を O(N) で調べられる。
- [ランレングス圧縮](run-length-encoding.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：同じ値（文字）の連続を（値, 長さ）の組にして、塊の単位で考える。

## 二分探索の応用

- [半分全列挙](meet-in-the-middle.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>：N ≤ 40 程度の部分集合の問題を前半と後半に分け、それぞれ 2^(N/2) 通りを列挙してから、ソートと二分探索（または尺取り）で組み合わせる。
- [平均・中央値の最大化](fractional-binary-search.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>：平均・比・中央値の最大化を、答え x を決めた判定問題にして x を二分探索する。
- [K 番目の値](kth-value.md) <span class="kp-mini kp-lv-ao" title="difficulty 1600〜1999">青</span>：N^2 個の積・和のように全部は列挙できない値の K 番目を、「x 以下の個数 ≥ K」となる最小の x として二分探索で求める。

## 凸と三分探索

- [三分探索](ternary-search.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>：下に凸（谷が 1 つ）な関数の最小値を、2 点の値を比べて外側を捨てながら求める。
- [絶対値の和の最小化と中央値](median-absolute.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：Σ|x − a_i| は中央値で最小になる（x を動かしたときの傾きが「左の点の数 − 右の点の数」になるため）。

## 貪欲

- [貪欲法の考え方と正当性](greedy-basics.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：その場で最もよいものを選び続ける方針が正しいことを、交換論法（最適解を貪欲解に近づけても悪くならない）や帰納法で確かめてから使う。
- [区間スケジューリング・区間の串刺し](interval-scheduling.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：重ならない区間をできるだけ多く選ぶには、右端の小さい順に、選んだ区間と重ならないものを取ればよい。
- [優先度付きキューを使う貪欲](greedy-priority-queue.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>：締め切りのある仕事の選び方や、毎回最大（最小）を取り出す操作の繰り返しを、候補を優先度付きキューに入れて O(N log N) で処理する。
- [交換論法と比較関数の設計](exchange-argument.md) <span class="kp-mini kp-lv-ao" title="difficulty 1600〜1999">青</span>：隣り合う 2 つを入れ替えたときに変わる項だけを比べ、「i を先に置くべき条件」を式で導いて比較関数にする。
- [辞書順最小を前から決める貪欲](lexicographic-greedy.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：条件を満たすもののうち辞書順最小を、先頭から 1 つずつ「小さい候補から試し、残りで条件を満たせるならその候補に確定」で作る。

ほかの章の関連ページ：[ソートで考える](sorting-techniques.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>（ソートと二分探索の章）

## 周期とダブリング

- [周期性の検出](periodicity.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：状態が S 種類しかなければ、S 回進むまでに必ず以前と同じ状態が現れる（鳩の巣原理）。
- [ダブリング](doubling.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>：各状態から次の状態が決まる遷移を K ≤ 10^18 回進めた結果や途中の和を、2^k 回後の表を作って O(log K) で求める。

## 再帰と分割統治

- [再帰的な構造](recursion-structure.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：レベル N のものがレベル N − 1 のものの組合せで定義される構造の K 番目を、各レベルの長さを前計算して再帰でたどって求める。
- [分割統治](divide-and-conquer.md) <span class="kp-mini kp-lv-ki" title="difficulty 2000〜2399">黄</span>：区間を半分に分けて左右を再帰で解き、中央を「またぐもの」だけを O(長さ) で処理すれば全体が O(N log N) になる。

## ほかの分野にある関連ページ {#elsewhere}

種類に[計算量](../lists/kind-complexity.md)・[全探索](../lists/kind-brute-force.md)・[二分探索](../lists/kind-binary-search.md)・[累積和・差分](../lists/kind-prefix-sum.md)・[尺取り・スライド窓](../lists/kind-two-pointers.md)・[貪欲](../lists/kind-greedy.md)・[ソート・座標圧縮](../lists/kind-sorting.md)・[ダブリング・分割統治](../lists/kind-doubling.md)・[ビット演算](../lists/kind-bit.md)のどれかを持つ、ほかの分野のページ。

- [考察](../thinking/index.md)：[一部を固定して数える](../thinking/fix-variable.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>
- [動的計画法](../dp/index.md)：[累積和・いもす法による DP の高速化](../dp/dp-prefix-sum.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>・[並べ替えてから DP する](../dp/exchange-argument-dp.md) <span class="kp-mini kp-lv-ao" title="difficulty 1600〜1999">青</span>・[最長増加部分列](../dp/lis.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>・[bitDP](../dp/bit-dp.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>・[部分集合を列挙する DP](../dp/subset-enumeration-dp.md) <span class="kp-mini kp-lv-ao" title="difficulty 1600〜1999">青</span>・[プロファイル DP](../dp/broken-profile-dp.md) <span class="kp-mini kp-lv-ki" title="difficulty 2000〜2399">黄</span>・[セグメント木・スライド最小値による DP の高速化](../dp/dp-segment-tree.md) <span class="kp-mini kp-lv-ao" title="difficulty 1600〜1999">青</span>・[Monge 性による DP の高速化](../dp/monge.md) <span class="kp-mini kp-lv-hatten" title="difficulty 2400〜（概要だけ）">発展</span>・[Alien DP](../dp/alien-dp.md) <span class="kp-mini kp-lv-hatten" title="difficulty 2400〜（概要だけ）">発展</span>
- [グラフ](../graph/index.md)：[小さいグラフの全探索](../graph/small-graph-brute-force.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>・[最小全域木](../graph/minimum-spanning-tree.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>
- [木](../tree/index.md)：[木の上の累積和・いもす法](../tree/tree-imos.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>・[完全二分木](../tree/complete-binary-tree.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>・[葉から考える](../tree/leaf-first.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>・[最小共通祖先（LCA）](../tree/lca.md) <span class="kp-mini kp-lv-ao" title="difficulty 1600〜1999">青</span>・[重心分解](../tree/centroid-decomposition.md) <span class="kp-mini kp-lv-ki" title="difficulty 2000〜2399">黄</span>・[比で親に併合する貪欲](../tree/tree-ratio-greedy.md) <span class="kp-mini kp-lv-hatten" title="difficulty 2400〜（概要だけ）">発展</span>
- [データ構造](../ds/index.md)：[優先度付きキュー](../ds/priority-queue.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>・[単調スタックとスライド最小値](../ds/monotonic-stack.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>・[K 番目の値を求めるデータ構造](../ds/kth-element.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>・[セグメント木上の二分探索](../ds/segment-tree-binary-search.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>・[値を添字にする BIT・セグメント木](../ds/segment-tree-on-values.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>・[Sparse Table](../ds/sparse-table.md) <span class="kp-mini kp-lv-ao" title="difficulty 1600〜1999">青</span>・[平面走査](../ds/sweep-line-2d.md) <span class="kp-mini kp-lv-ao" title="difficulty 1600〜1999">青</span>・[平方分割](../ds/sqrt-decomposition.md) <span class="kp-mini kp-lv-ki" title="difficulty 2000〜2399">黄</span>・[並列二分探索](../ds/parallel-binary-search.md) <span class="kp-mini kp-lv-hatten" title="difficulty 2400〜（概要だけ）">発展</span>・[CDQ 分割統治](../ds/cdq-divide-and-conquer.md) <span class="kp-mini kp-lv-hatten" title="difficulty 2400〜（概要だけ）">発展</span>・[Wavelet Matrix](../ds/wavelet-matrix.md) <span class="kp-mini kp-lv-hatten" title="difficulty 2400〜（概要だけ）">発展</span>・[Binary Trie](../ds/binary-trie.md) <span class="kp-mini kp-lv-ao" title="difficulty 1600〜1999">青</span>
- [整数論・代数](../math/index.md)：[繰り返し二乗法](../math/mod-pow.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>・[等比数列の和を mod で求める](../math/geometric-series-mod.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>・[桁と mod](../math/digit-and-mod.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>・[約数列挙と素数判定](../math/divisor-enum.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>・[調和級数と倍数の列挙](../math/harmonic-sum.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>・[約数の個数の上界と高度合成数](../math/divisor-count-bound.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>・[整数の平方根・K 乗根と累乗数](../math/integer-root.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>・[Stern-Brocot 木と連分数](../math/stern-brocot.md) <span class="kp-mini kp-lv-hatten" title="difficulty 2400〜（概要だけ）">発展</span>・[行列累乗](../math/matrix-power.md) <span class="kp-mini kp-lv-ao" title="difficulty 1600〜1999">青</span>・[XOR 基底](../math/xor-basis.md) <span class="kp-mini kp-lv-ki" title="difficulty 2000〜2399">黄</span>・[XOR 畳み込み](../math/hadamard-transform.md) <span class="kp-mini kp-lv-hatten" title="difficulty 2400〜（概要だけ）">発展</span>・[分割統治 FFT・オンライン畳み込み](../math/online-convolution.md) <span class="kp-mini kp-lv-hatten" title="difficulty 2400〜（概要だけ）">発展</span>
- [数え上げ・確率・ゲーム](../comb/index.md)：[部分集合の高速ゼータ変換とメビウス変換](../comb/zeta-mobius-subset.md) <span class="kp-mini kp-lv-ki" title="difficulty 2000〜2399">黄</span>・[Nim と XOR](../comb/nim.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>
- [文字列](../string/index.md)：[集合・多重集合のハッシュ](../string/hashing-for-sets.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>
- [幾何](../geometry/index.md)：[偏角ソート](../geometry/argument-sort.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>・[円と幾何の最適化](../geometry/circle-geometry.md) <span class="kp-mini kp-lv-ao" title="difficulty 1600〜1999">青</span>
- [その他の技法](../misc/index.md)：[インタラクティブ問題](../misc/interactive.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>・[bitset による高速化](../misc/bitset-speedup.md) <span class="kp-mini kp-lv-ao" title="difficulty 1600〜1999">青</span>
- [C++](../cpp/index.md)：[数・ビット・乱数の関数](../cpp/cpp-math-functions.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>・[比較関数と順序](../cpp/cpp-comparators.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>・[アルゴリズム関数と ranges 版](../cpp/cpp-algorithms.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>・[入出力と定数倍](../cpp/cpp-io.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>
