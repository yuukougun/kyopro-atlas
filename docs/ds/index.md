---
title: データ構造
type: generated
---

<!-- tools/gen_site.py が生成する。手で直さない -->

# データ構造

STL の応用、スタック・キュー、Union-Find、BIT・セグメント木、クエリ処理の工夫。37 ページ。ページ名の横の印はレベル（[レベルの意味](../start/how-to-use.md#levels)）である。

学ぶ順：[色別ロードマップ](../guide/roadmap.md#reading-order)。使い分け：[区間の集約](../guide/method-comparison.md#range-queries)・[集合とキュー](../guide/method-comparison.md#containers)。問題集：[ACL Practice](../guide/problem-sets.md#problem-sets-practice2)・[典型90問](../guide/problem-sets.md#problem-sets-typical90)・[鉄則本](../guide/problem-sets.md#problem-sets-tessoku-book)。自作：[自作ライブラリの設計と動作確認](../guide/library-design.md)。

## 標準コンテナの応用

- [STL コンテナの使い分け](stl-containers.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：どの操作を速くしたいかで vector・deque・set・map・priority_queue・unordered_map を選ぶ。
- [set・multiset・map の応用](ordered-set.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：set・multiset・map の lower_bound で「x 以上の最小」「x 未満の最大」を O(log N) で求め、要素の追加・削除と組み合わせる。
- [優先度付きキュー](priority-queue.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>：最大（最小）の要素の取り出しと追加を O(log N) で行う。
- [上位 K 個の和と中央値の管理](top-k-multiset.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>：追加・削除のたびに上位（下位）K 個の和や中央値を O(log N) で答える。
- [区間を set で管理する](interval-set.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>：互いに重ならない区間を左端をキーにした set・map で持ち、点を含む区間の検索・区間の追加と併合・区間への代入を、ならし O(log N) で行う。
- [全体への操作を変数で持つ](global-offset.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：「全要素に x を足す」「全体を反転する」「全体を回転する」を、要素を書き換えずにオフセット・反転フラグ・先頭位置の変数で表す。
- [配列で作る連結リスト](linked-list.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：各要素の前と次を配列（値が大きければ map）で持つ双方向リストで、「x の直後に y を挿入」「x を削除」「列の付け替え」を O(1) で行い、最後に先頭からたどって列を出力する。

## スタックとキュー

- [スタック・キュー・deque の使いどころ](stack-techniques.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：スタックで括弧の対応・直前との打ち消し・操作の取り消しを、deque で両端への追加を処理する。
- [単調スタックとスライド最小値](monotonic-stack.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>：各要素について「左（右）で初めて自分より大きい（小さい）要素」を、添字を単調に積んだスタックで全体 O(N) で求める。

## Union-Find

- [Union-Find](union-find.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：要素を互いに素なグループに分けて持ち、2 つのグループの併合と「同じグループか」の判定を、union by size と経路圧縮でならし O(α(N)) で行う。
- [Union-Find の応用](union-find-applications.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>：Union-Find の根に成分の情報（サイズ・辺数・上位 K 個・値ごとの個数）を持たせ、併合のときに合成する。
- [重み付き Union-Find](weighted-union-find.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>：x_v − x_u = w の形の情報を順に受け取りながら、矛盾の判定と同じ成分の 2 要素の差の取得を行う。
- [部分永続 Union-Find](partially-persistent-union-find.md) <span class="kp-mini kp-lv-hatten" title="difficulty 2400〜（概要だけ）">発展</span>：過去の時刻 t の時点での連結判定や成分の大きさを答えられる Union-Find。
- [ロールバックできる Union-Find](rollback-union-find.md) <span class="kp-mini kp-lv-hatten" title="difficulty 2400〜（概要だけ）">発展</span>：直前の併合から順に取り消せる Union-Find。

## 区間クエリ

- [BIT（Fenwick Tree）](fenwick-tree.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>：一点への加算と接頭辞の和（したがって区間の和）を、どちらも O(log N) で行う。
- [転倒数](inversion-number.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>：列の転倒数（i < j かつ A_i > A_j の組の数）を、左から見て既に出た値のうち自分より大きいものの個数を BIT で足して O(N log N) で数える。
- [K 番目の値を求めるデータ構造](kth-element.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>：値の追加・削除がある多重集合で、K 番目に小さい値や x 以下の個数を O(log N) で求める。
- [セグメント木](segment-tree.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>：結合律と単位元を持つ演算（モノイド）が載った列で、一点の更新と区間の総積（和・最小・最大・gcd など）の取得を、どちらも O(log N) で行う。
- [セグメント木上の二分探索](segment-tree-binary-search.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>：左端 l を固定し、区間 [l, r) の総積が条件を満たす最大の r を、木を登って降りる手順で O(log N) で求める。
- [値を添字にする BIT・セグメント木](segment-tree-on-values.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>：値（必要なら座標圧縮した値）を添字にした BIT・セグメント木に個数や和を載せ、「x 以下の個数・和」「上位 K 個の和」を O(log N) で求める。
- [遅延セグメント木](lazy-segment-tree.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>：区間の全要素への加算・代入・アフィン変換と、区間の和・最小値などの取得を、どちらも O(log N) で行う。
- [セグメント木に何を載せるか](segment-tree-monoids.md) <span class="kp-mini kp-lv-ao" title="difficulty 1600〜1999">青</span>：左右の子の情報だけから親の情報を作れるように、答えに要る情報を足してセグメント木に載せる。
- [遅延セグメント木の載せ方の型](lazy-segment-tree-patterns.md) <span class="kp-mini kp-lv-ao" title="difficulty 1600〜1999">青</span>：区間作用の問題で、遅延セグメント木に載せる S（値）と F（作用）・mapping・composition の組を型の表から選ぶ。
- [Sparse Table](sparse-table.md) <span class="kp-mini kp-lv-ao" title="difficulty 1600〜1999">青</span>：更新のない列で、冪等な演算（min・max・gcd・and・or）の区間クエリに、前処理 O(N log N)・質問 O(1) で答える。
- [Segment Tree Beats](segment-tree-beats.md) <span class="kp-mini kp-lv-hatten" title="difficulty 2400〜（概要だけ）">発展</span>：区間 chmin・chmax と区間和のように遅延セグメント木の条件を満たさない更新を、ならし計算量で処理する。

## クエリ処理の工夫

- [クエリの先読み](offline-queries.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>：クエリを入力の順に答えなくてよいとき、答えやすい順（右端の順・しきい値の順・時間の逆順）に並べ替えて処理し、最後に元の順に戻す。
- [平面走査](sweep-line-2d.md) <span class="kp-mini kp-lv-ao" title="difficulty 1600〜1999">青</span>：2 次元の問題を、一方の座標の順にイベント（点・区間の端・クエリ）を並べ、走査線を動かしながらもう一方の座標を BIT・セグメント木で持つ形にする。
- [Mo's algorithm](mo-algorithm.md) <span class="kp-mini kp-lv-ao" title="difficulty 1600〜1999">青</span>：更新のない列への区間クエリを並べ替え（l のブロックの順、次に r の順）、前の区間から 1 要素ずつ伸び縮みして答える。
- [平方分割](sqrt-decomposition.md) <span class="kp-mini kp-lv-ki" title="difficulty 2000〜2399">黄</span>：セグメント木に載らない区間操作や、合計だけが抑えられた量の処理を、√N を境に分けて O(N√N) 程度で行う。
- [並列二分探索](parallel-binary-search.md) <span class="kp-mini kp-lv-hatten" title="difficulty 2400〜（概要だけ）">発展</span>：多数のクエリがそれぞれ「単調な過程のどの時点で条件を満たすか」を二分探索するとき、全クエリの探索を同時に進める。
- [CDQ 分割統治](cdq-divide-and-conquer.md) <span class="kp-mini kp-lv-hatten" title="difficulty 2400〜（概要だけ）">発展</span>：3 次元の支配点の数え上げや、点の追加つきの長方形クエリを、オフラインで O(N log^2 N) で解く。

ほかの章の関連ページ：[全体への操作を変数で持つ](global-offset.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>（標準コンテナの応用の章）・[永続データ構造](persistent-data-structures.md) <span class="kp-mini kp-lv-ao" title="difficulty 1600〜1999">青</span>（そのほかのデータ構造の章）

## そのほかのデータ構造

- [永続データ構造](persistent-data-structures.md) <span class="kp-mini kp-lv-ao" title="difficulty 1600〜1999">青</span>：過去の版を残したまま更新し、任意の版から続きの操作をする。
- [マージソート木](merge-sort-tree.md) <span class="kp-mini kp-lv-ao" title="difficulty 1600〜1999">青</span>：区間内の x 以下の要素の個数・和を、オンラインで O(log^2 N) で答える静的な構造。
- [Wavelet Matrix](wavelet-matrix.md) <span class="kp-mini kp-lv-hatten" title="difficulty 2400〜（概要だけ）">発展</span>：区間の K 番目の値・x 未満の個数・和を、オンラインで O(log σ) で答える静的な構造。
- [Binary Trie](binary-trie.md) <span class="kp-mini kp-lv-ao" title="difficulty 1600〜1999">青</span>：整数を 2 進数の上位 bit から Trie に入れ、各ノードに部分木の個数を持たせる。
- [平衡二分探索木と pb_ds の tree](balanced-bst.md) <span class="kp-mini kp-lv-hatten" title="difficulty 2400〜（概要だけ）">発展</span>：位置で指定した挿入・削除・区間の反転・区間の総積を、期待 O(log N) で処理する列の構造。
- [見慣れないデータ構造の名前と用途](advanced-ds-catalog.md)：解説に見慣れない名前のデータ構造が出てきたときに、何ができるかと代わりになる手を 1 行ずつ引く。

## ほかの分野にある関連ページ {#elsewhere}

種類に[データ構造](../lists/kind-data-structure.md)・[クエリ処理の工夫](../lists/kind-query-processing.md)のどれかを持つ、ほかの分野のページ。

- [基本テクニック](../basics/index.md)：[イベントソートと平面走査の基本](../basics/event-sort.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>・[優先度付きキューを使う貪欲](../basics/greedy-priority-queue.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>
- [考察](../thinking/index.md)：[後ろから・逆順に考える](../thinking/reverse-thinking.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>
- [動的計画法](../dp/index.md)：[Convex Hull Trick と Li Chao Tree](../dp/cht.md) <span class="kp-mini kp-lv-hatten" title="difficulty 2400〜（概要だけ）">発展</span>・[Slope Trick](../dp/slope-trick.md) <span class="kp-mini kp-lv-hatten" title="difficulty 2400〜（概要だけ）">発展</span>
- [グラフ](../graph/index.md)：[区間に辺を張る](../graph/segment-tree-graph.md) <span class="kp-mini kp-lv-hatten" title="difficulty 2400〜（概要だけ）">発展</span>・[Union-Find で連結性を扱う](../graph/union-find-connectivity.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>・[辺の追加と削除が混ざる連結性](../graph/offline-dynamic-connectivity.md) <span class="kp-mini kp-lv-hatten" title="difficulty 2400〜（概要だけ）">発展</span>・[次数による平方分割](../graph/degree-sqrt.md) <span class="kp-mini kp-lv-ao" title="difficulty 1600〜1999">青</span>
- [木](../tree/index.md)：[根からのパスを DFS で持ち回る](../tree/root-path-dfs.md) <span class="kp-mini kp-lv-ao" title="difficulty 1600〜1999">青</span>・[Static Top Tree と木 DP の動的更新](../tree/static-top-tree.md) <span class="kp-mini kp-lv-hatten" title="difficulty 2400〜（概要だけ）">発展</span>・[動的木](../tree/dynamic-tree.md) <span class="kp-mini kp-lv-hatten" title="difficulty 2400〜（概要だけ）">発展</span>・[マージテク](../tree/small-to-large.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>
- [文字列](../string/index.md)：[Trie](../string/trie.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>・[Suffix Array と LCP 配列](../string/suffix-array.md) <span class="kp-mini kp-lv-ki" title="difficulty 2000〜2399">黄</span>
- [C++](../cpp/index.md)：[コンテナ操作とイテレータ](../cpp/cpp-container-idioms.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>
