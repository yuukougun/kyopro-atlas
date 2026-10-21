---
title: 動的計画法の詳細索引
type: generated
search:
  exclude: true
---

<!-- tools/gen_site.py が生成する。手で直さない -->

# 動的計画法の詳細索引

分野の全ページの id・URL・別名・サイン・種類・前提・節。全分野の1行の一覧と索引の版は https://yuukougun.github.io/kyopro-atlas/llms.txt にある。stub（準備中）のページは要約と前提しかなく、節の見出しもまだない。

## DP の基本（dp-basics） {#dp-basics}

- id：`dp-basics`　レベル：基礎　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/dp/dp-basics/
- 別名：動的計画法、DP、Dynamic Programming、漸化式、配る DP、貰う DP、push 型、pull 型
- 種類：DP
- 前提：`brute-force`
- サイン：
    - 言い回し：前から順に 1 つずつ選んでいくときの、〜の最小値・最大値
    - 言い回し：ちょうど X にできるか（可否の判定）
    - 制約：N ≤ 10^5 程度で、各位置の選択肢が数通り（全探索だと K^N 通り）
    - 式の形：dp[i] が dp[i−1]・dp[i−2] など定数個の前の状態から決まる
- 節：
    - `dp-basics#four-parts` 状態・遷移・初期値・答えの 4 つを決める：https://yuukougun.github.io/kyopro-atlas/dp/dp-basics/#four-parts
    - `dp-basics#three-kinds` 最適化・数え上げ・可否判定を同じ骨組みで書く（演算と単位元・到達できない状態の表し方）：https://yuukougun.github.io/kyopro-atlas/dp/dp-basics/#three-kinds
    - `dp-basics#dp-push-pull` 配る DP と貰う DP（どちらも各遷移を 1 回ずつ使う）：https://yuukougun.github.io/kyopro-atlas/dp/dp-basics/#dp-push-pull
    - `dp-basics#pull-to-prefix-sum` 貰う形にすると遷移元が区間になる（累積和でまとめる高速化へ）（水）：https://yuukougun.github.io/kyopro-atlas/dp/dp-basics/#pull-to-prefix-sum
    - `dp-basics#greedy-counterexample` 貪欲で解けないことの確かめ方（反例から DP へ）：https://yuukougun.github.io/kyopro-atlas/dp/dp-basics/#greedy-counterexample
    - `dp-basics#map` DP の型の地図（列・区間・集合・桁・木・順列・確率・ゲーム・高速化）：https://yuukougun.github.io/kyopro-atlas/dp/dp-basics/#map

## メモ化再帰（memoized-recursion） {#memoized-recursion}

- id：`memoized-recursion`　レベル：基礎　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/dp/memoized-recursion/
- 別名：メモ化、Memoization、再帰 DP、トップダウン DP、map でメモ化、疎な DP
- 種類：DP
- 前提：`dp-basics`
- サイン：
    - 制約：N ≤ 10^18 で、⌊N/2⌋・⌊N/3⌋ のような値しか現れない
    - 言い回し：f(n) が f(⌊n/k⌋) などで再帰的に定義されている
    - 式の形：dp[x] が x より小さい値の dp で決まるが、どの値が現れるかを前もって列挙しにくい
- 節：
    - `memoized-recursion#write-memo` 再帰とメモの書き方（未計算の印と答えの値の衝突を避ける）：https://yuukougun.github.io/kyopro-atlas/dp/memoized-recursion/#write-memo
    - `memoized-recursion#vs-bottom-up` ボトムアップとの使い分け（速さ・スタック・高速化の載せやすさ）：https://yuukougun.github.io/kyopro-atlas/dp/memoized-recursion/#vs-bottom-up
    - `memoized-recursion#dp-map-sparse` 到達する状態だけを持つ（map でメモ化・現れる値の個数の見積もり）：https://yuukougun.github.io/kyopro-atlas/dp/memoized-recursion/#dp-map-sparse

## DAG 上の DP（dp-dag） {#dp-dag}

- id：`dp-dag`　レベル：基礎　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/dp/dp-dag/
- 別名：DAG DP、DP on DAG、DAG の最長路、経路の数え上げ、トポロジカル順の DP
- 種類：DP、グラフ探索
- 前提：`dp-basics`、`topological-sort`
- サイン：
    - 言い回し：番号の小さい頂点から大きい頂点へだけ辺がある（u < v）
    - 言い回し：値が増える向きにしか移動できない
    - 言い回し：有向グラフの最長の経路の長さ・経路の本数・最短路の本数
    - 言い回し：依存関係に従って順に決める（閉路があれば −1）
- 節：
    - `dp-dag#dp-as-dag` DP は DAG 上の最短路・最長路・数え上げ：https://yuukougun.github.io/kyopro-atlas/dp/dp-dag/#dp-as-dag
    - `dp-dag#ordering` 順序の作り方（Kahn 法・DFS の帰りがけ順の逆・メモ化再帰・問題の性質から）：https://yuukougun.github.io/kyopro-atlas/dp/dp-dag/#ordering
    - `dp-dag#find-dag` DAG だと気づく・作る（値の順・距離の層・同じ値の頂点をまとめる）（水）：https://yuukougun.github.io/kyopro-atlas/dp/dp-dag/#find-dag
    - `dp-dag#count-shortest-paths` 最短路の本数（距離が確定した順に配る）：https://yuukougun.github.io/kyopro-atlas/dp/dp-dag/#count-shortest-paths
    - `dp-dag#with-cycles` 閉路があるとき（SCC で縮約する・最短路に切り替える）：https://yuukougun.github.io/kyopro-atlas/dp/dp-dag/#with-cycles

## DP の計算順序（dp-order） {#dp-order}

- id：`dp-order`　レベル：水　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/dp/dp-order/
- 別名：計算順序、ループの順番、後ろから DP、逆順 DP
- 種類：DP
- 前提：`dp-basics`
- サイン：
    - 言い回し：値の小さい（大きい）方へしか移れない
    - 言い回し：ゴールに着いたら終わり・残り回数が 0 になったら終わり（終わりの値が分かっている）
    - 式の形：dp[i] が dp[j]（j > i）から決まる（i 番目以降で最適に行動したときの値）
- 節：
    - `dp-order#dependency` 依存グラフと計算順序の原則（閉路があれば DP にならない）：https://yuukougun.github.io/kyopro-atlas/dp/dp-order/#dependency
    - `dp-order#typical-orders` 典型の順序（添字・逆順・値の順・区間の長さ順・集合の昇順・木の帰りがけ順）：https://yuukougun.github.io/kyopro-atlas/dp/dp-order/#typical-orders
    - `dp-order#backward` 後ろから解くサイン（終わりの値が分かっている・辞書順最小の復元）：https://yuukougun.github.io/kyopro-atlas/dp/dp-order/#backward
    - `dp-order#expectation-and-games` 期待値 DP・ゲーム DP の計算順序（確率・期待値・ゲームの章へ）：https://yuukougun.github.io/kyopro-atlas/dp/dp-order/#expectation-and-games

## DP の状態の設計（dp-state-design） {#dp-state-design}

- id：`dp-state-design`　レベル：水　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/dp/dp-state-design/
- 別名：状態設計、DP の状態、直前を状態に持つ、末尾の数文字を状態に持つ、環状 DP、円環 DP、括弧列の DP
- 種類：DP
- 前提：`dp-basics`
- サイン：
    - 言い回し：隣り合う〜が異なる・同じことを連続して〜しない
    - 言い回し：直前の選択でコストが変わる・モードが切り替わる
    - 言い回し：長さ K の回文・特定の短い文字列を部分文字列に含まない文字列の数
    - 言い回し：円形に並んでいる（最後と最初も隣り合う）
    - 言い回し：'(' と ')' と '?' の列から正しい括弧列を作る方法の数
    - 制約：制約の一部だけが小さい（K ≤ 5、末尾の K ≤ 10 文字、文字の種類 26）
- 節：
    - `dp-state-design#why-summary-works` 将来に効く要約だけを持てば合流できる理由：https://yuukougun.github.io/kyopro-atlas/dp/dp-state-design/#why-summary-works
    - `dp-state-design#typical-summaries` 典型の要約（直前の値・on/off・偶奇・個数・上限で打ち切った値）：https://yuukougun.github.io/kyopro-atlas/dp/dp-state-design/#typical-summaries
    - `dp-state-design#last-characters` 末尾の数文字を状態にする（禁止された並び・回文を避ける）：https://yuukougun.github.io/kyopro-atlas/dp/dp-state-design/#last-characters
    - `dp-state-design#bracket-dp` 括弧列の DP（開き括弧の残り数を状態にする）：https://yuukougun.github.io/kyopro-atlas/dp/dp-state-design/#bracket-dp
    - `dp-state-design#dp-cyclic` 環状の列（1 か所で切り、最初の状態を固定して DP を回す）：https://yuukougun.github.io/kyopro-atlas/dp/dp-state-design/#dp-cyclic
    - `dp-state-design#state-count` 状態数の見積もり（(P+1)&#94;K・2&#94;K・末尾の数文字の組の数）：https://yuukougun.github.io/kyopro-atlas/dp/dp-state-design/#state-count

## 余り・個数を状態に持つ DP（dp-mod-state） {#dp-mod-state}

- id：`dp-mod-state`　レベル：水　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/dp/dp-mod-state/
- 別名：余りを状態に、mod DP、倍数の数え上げ、平均が整数
- 種類：DP、整数論
- 前提：`dp-state-design`、`mod-arithmetic`
- サイン：
    - 言い回し：和（積）が M の倍数になる選び方の数
    - 言い回し：平均が整数になる・平均がちょうど A になる選び方の数
    - 言い回し：'?' を埋めた数を M で割った余りが r になるものの数
    - 制約：M ≤ 1000 程度、N ≤ 100 程度
- 節：
    - `dp-mod-state#why-remainder` 余りを状態にしてよい理由（足し算・掛け算と mod が両立する）：https://yuukougun.github.io/kyopro-atlas/dp/dp-mod-state/#why-remainder
    - `dp-mod-state#with-count` 個数も状態に持つ（K 個選んで和が D の倍数）：https://yuukougun.github.io/kyopro-atlas/dp/dp-mod-state/#with-count
    - `dp-mod-state#average` 平均の扱い（個数を外側で固定する・平均を引いて和 0 にする）：https://yuukougun.github.io/kyopro-atlas/dp/dp-mod-state/#average
    - `dp-mod-state#game-by-remainder` 後ろから余りごとの勝敗を決めるゲーム（青）：https://yuukougun.github.io/kyopro-atlas/dp/dp-mod-state/#game-by-remainder

## フェーズを状態に持つ DP（dp-phase） {#dp-phase}

- id：`dp-phase`　レベル：青　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/dp/dp-phase/
- 別名：耳 DP、段階を状態に持つ DP、最大部分配列和、Kadane、Kadane's algorithm
- 種類：DP
- 前提：`dp-state-design`
- サイン：
    - 言い回し：区間を 1 つ選んで、その中だけ操作する（1 回だけ変更できる）
    - 言い回し：部分列として 'ABC' などが何個含まれるか（'?' を埋めた全通りの和）
    - 言い回し：連続する部分列の和の最大
    - 式の形：区間 [l, r) の両端を全探索すると O(N^2) になり、各位置の扱いが「区間の前・中・後」で変わる
- 節：
    - `dp-phase#kadane` 最大部分配列和（Kadane）：区間を 1 つ選ぶ最も簡単な例：https://yuukougun.github.io/kyopro-atlas/dp/dp-phase/#kadane
    - `dp-phase#counting-phases` 段階の数え方（区間の外側にも段階がある）：https://yuukougun.github.io/kyopro-atlas/dp/dp-phase/#counting-phases
    - `dp-phase#matched-prefix` 何文字目まで集めたか（部分列として現れる回数を数える）：https://yuukougun.github.io/kyopro-atlas/dp/dp-phase/#matched-prefix
    - `dp-phase#flip-interval` 区間の反転・変更を段階の切り替えで表す：https://yuukougun.github.io/kyopro-atlas/dp/dp-phase/#flip-interval

## DP の復元（dp-reconstruction） {#dp-reconstruction}

- id：`dp-reconstruction`　レベル：水　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/dp/dp-reconstruction/
- 別名：DP 復元、選び方の出力、DP テーブルからの復元、辞書順最小の復元
- 種類：DP
- 前提：`dp-basics`
- サイン：
    - 言い回し：選び方（経路・操作列）を 1 つ出力せよ
    - 言い回し：条件を満たすものが複数あれば辞書順最小のものを出力せよ
    - 言い回し：辞書順で K 番目のものを出力せよ（K は 10^18 程度）
- 節：
    - `dp-reconstruction#trace-back` 表を残して終端から逆にたどる・遷移元を記録しておく：https://yuukougun.github.io/kyopro-atlas/dp/dp-reconstruction/#trace-back
    - `dp-reconstruction#ties` 最適な遷移が複数あるときの選び方：https://yuukougun.github.io/kyopro-atlas/dp/dp-reconstruction/#ties
    - `dp-reconstruction#lexicographic-min` 辞書順最小の復元（後ろからの DP と前からの貪欲）：https://yuukougun.github.io/kyopro-atlas/dp/dp-reconstruction/#lexicographic-min
    - `dp-reconstruction#dp-kth-lexicographic` 辞書順 K 番目を数え上げで決める（個数が K を超えたら打ち切る）：https://yuukougun.github.io/kyopro-atlas/dp/dp-reconstruction/#dp-kth-lexicographic

## 累積和・いもす法による DP の高速化（dp-prefix-sum） {#dp-prefix-sum}

- id：`dp-prefix-sum`　レベル：水　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/dp/dp-prefix-sum/
- 別名：累積和 DP、いもす法 DP、累積和で遷移をまとめる
- 種類：DP、累積和・差分
- 前提：`dp-basics`、`imos`
- サイン：
    - 言い回し：各人に 0〜a_i 個を配る方法の数（上限つきの配り方）
    - 制約：N ≤ 100、K ≤ 10^5 程度で、O(NK) は通るが O(NK^2) は通らない
    - 式の形：dp[i] = Σ_{j=i−R}^{i−L} dp[j] のように、遷移元が連続した範囲の和
    - 式の形：dp[i] から i+L〜i+R の範囲へ同じ値を配る
- 節：
    - `dp-prefix-sum#pull-and-push` 貰う形と累積和・配る形といもす法：https://yuukougun.github.io/kyopro-atlas/dp/dp-prefix-sum/#pull-and-push
    - `dp-prefix-sum#same-row` 同じ段の累積和（上限つきの配り方）：https://yuukougun.github.io/kyopro-atlas/dp/dp-prefix-sum/#same-row
    - `dp-prefix-sum#directional` 区間の和集合・方向ごとの累積（縦・横・斜め）：https://yuukougun.github.io/kyopro-atlas/dp/dp-prefix-sum/#directional
    - `dp-prefix-sum#prefix-min` 遷移元が接頭辞なら累積 min・累積 max でもよい：https://yuukougun.github.io/kyopro-atlas/dp/dp-prefix-sum/#prefix-min
    - `dp-prefix-sum#by-remainder` 余りごとの累積（青）：https://yuukougun.github.io/kyopro-atlas/dp/dp-prefix-sum/#by-remainder
    - `dp-prefix-sum#two-dimensional` 2 次元の累積（青）：https://yuukougun.github.io/kyopro-atlas/dp/dp-prefix-sum/#two-dimensional

## ナップサック DP（knapsack-01） {#knapsack-01}

- id：`knapsack-01`　レベル：基礎　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/dp/knapsack-01/
- 別名：0-1 ナップサック、ナップサック、ナップザック、Knapsack Problem、0-1 Knapsack、個数制限なしナップサック、個数無制限ナップサック、Unbounded Knapsack、個数制限付きナップサック、多重ナップサック、コイン問題、配列の使い回し、1 次元化
- 種類：DP
- 前提：`dp-basics`
- サイン：
    - 言い回し：重さの合計が W 以下で価値の和の最大
    - 言い回し：同じものを何度でも使える（硬貨・魔法）
    - 言い回し：各品物は B_i 個まで使える
    - 制約：NW ≤ 10&#94;7〜10&#94;8（O(NW) が通る）
- 節：
    - `knapsack-01#meaning` DP の表の意味（「以下」と「ちょうど」で初期値と答えが変わる）：https://yuukougun.github.io/kyopro-atlas/dp/knapsack-01/#meaning
    - `knapsack-01#dp-rolling-array` 配列の使い回しとループの向き（0-1 は大きい方から、個数制限なしは小さい方から）：https://yuukougun.github.io/kyopro-atlas/dp/knapsack-01/#dp-rolling-array
    - `knapsack-01#knapsack-unbounded` 個数制限なし（数え上げでは品物と和のループの内外で組合せと列が分かれる）：https://yuukougun.github.io/kyopro-atlas/dp/knapsack-01/#knapsack-unbounded
    - `knapsack-01#variants` 多次元の重さ・上限で打ち切る・グループから 1 つ選ぶ：https://yuukougun.github.io/kyopro-atlas/dp/knapsack-01/#variants
    - `knapsack-01#choose-by-size` 計算量で解法を切り替える（重さ・価値・N のどれが小さいか）（水）：https://yuukougun.github.io/kyopro-atlas/dp/knapsack-01/#choose-by-size
    - `knapsack-01#knapsack-bounded` 個数制限付き（素朴な展開・二進分解・余りごとのスライド最小値）（青）：https://yuukougun.github.io/kyopro-atlas/dp/knapsack-01/#knapsack-bounded

## 部分和 DP（subset-sum） {#subset-sum}

- id：`subset-sum`　レベル：基礎　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/dp/subset-sum/
- 別名：部分和、部分和問題、Subset Sum、部分和の数え上げ
- 種類：DP
- 前提：`dp-basics`
- サイン：
    - 言い回し：いくつか選んで和をちょうど S にできるか・その選び方の数
    - 言い回し：2 つのグループに分けて差（遅い方）を最小にする
    - 言い回し：各要素に + か − を付けて和を K にする
    - 制約：N ≤ 100、値の総和 ≤ 10^5 程度
- 節：
    - `subset-sum#three-forms` 可否・数え上げ・最大の 3 つの形：https://yuukougun.github.io/kyopro-atlas/dp/subset-sum/#three-forms
    - `subset-sum#reformulations` 典型の言い換え（2 グループに分ける・± の和・x と y が独立・平均）：https://yuukougun.github.io/kyopro-atlas/dp/subset-sum/#reformulations
    - `subset-sum#sort-then-count` 最大値を固定するためにソートしてから数える（水）：https://yuukougun.github.io/kyopro-atlas/dp/subset-sum/#sort-then-count
    - `subset-sum#over-all-subsets` 全部分集合についての和（含む部分集合の数を重みにする）（青）：https://yuukougun.github.io/kyopro-atlas/dp/subset-sum/#over-all-subsets

## DP の状態の削減（dp-dimension-reduction） {#dp-dimension-reduction}

- id：`dp-dimension-reduction`　レベル：青　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/dp/dp-dimension-reduction/
- 別名：状態の削減、次元の削減、状態の圧縮、値と添字の入れ替え、キーと値を入れ替える、添字と値を逆に、上限で打ち切る
- 種類：DP
- 前提：`dp-state-design`、`knapsack-01`
- サイン：
    - 制約：重さの上限 W ≤ 10^9 で、価値の総和が 10^5 程度
    - 言い回し：ペナルティが 2^(C−1) のように指数的に増える
    - 式の形：dp\[i]\[a][b] の表が大きすぎ、同じ (i, a) なら b が大きい（小さい）ほど常に良い
- 節：
    - `dp-dimension-reduction#cap` 上限で打ち切る（log 回で十分な量・目標以上をまとめる）：https://yuukougun.github.io/kyopro-atlas/dp/dp-dimension-reduction/#cap
    - `dp-dimension-reduction#dp-swap-key-value` 値と添字の入れ替え（同じ添字なら値が良い方が常に良いとき）：https://yuukougun.github.io/kyopro-atlas/dp/dp-dimension-reduction/#dp-swap-key-value
    - `dp-dimension-reduction#which-to-index` どれを添字に残すか（範囲が小さい量を選ぶ）：https://yuukougun.github.io/kyopro-atlas/dp/dp-dimension-reduction/#which-to-index

## 戻す DP（knapsack-undo） {#knapsack-undo}

- id：`knapsack-undo`　レベル：青　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/dp/knapsack-undo/
- 別名：ナップサックの削除、削除できるナップサック、減らすナップサック
- 種類：DP、数え上げ
- 前提：`subset-sum`、`knapsack-01`
- サイン：
    - 言い回し：要素の追加と削除のクエリのたびに、和が K になる選び方の数を答える
    - 言い回し：各 i について、i を使わないときの答え（〜を除いたとき）
    - 制約：クエリの数 Q と目標の和 K がともに 5000 程度（O(QK) が通る）
- 節：
    - `knapsack-undo#undo-by-subtraction` 足し算の更新は引き算で戻せる（ループの向きは追加と逆）：https://yuukougun.github.io/kyopro-atlas/dp/knapsack-undo/#undo-by-subtraction
    - `knapsack-undo#not-undoable` 戻せない DP（max・min・OR）：https://yuukougun.github.io/kyopro-atlas/dp/knapsack-undo/#not-undoable
    - `knapsack-undo#prefix-and-suffix` 前後からの DP をマージする：https://yuukougun.github.io/kyopro-atlas/dp/knapsack-undo/#prefix-and-suffix
    - `knapsack-undo#offline-divide-and-conquer` 分割統治でオフラインに処理する（黄）：https://yuukougun.github.io/kyopro-atlas/dp/knapsack-undo/#offline-divide-and-conquer

## 並べ替えてから DP する（exchange-argument-dp） {#exchange-argument-dp}

- id：`exchange-argument-dp`　レベル：青　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/dp/exchange-argument-dp/
- 別名：交換論法＋DP、ソートしてから DP、座布団 DP、締切つきナップサック
- 種類：DP、貪欲
- 前提：`exchange-argument`、`knapsack-01`
- サイン：
    - 言い回し：好きな順番で、いくつか選んで順に処理する
    - 言い回し：締切・積み重ね（上に載せられる重さ）がある
    - 言い回し：一次関数を好きな順に合成する
    - 言い回し：最後の 1 つだけ制限を超えてよい
- 節：
    - `exchange-argument-dp#set-and-order` 選ぶ集合と順序を分けて考える：https://yuukougun.github.io/kyopro-atlas/dp/exchange-argument-dp/#set-and-order
    - `exchange-argument-dp#comparison-key` 比較の基準の作り方（入れ替えの差を i だけの量と j だけの量に分ける）：https://yuukougun.github.io/kyopro-atlas/dp/exchange-argument-dp/#comparison-key
    - `exchange-argument-dp#compare-ratios` 比は割らずに掛け算で比べる：https://yuukougun.github.io/kyopro-atlas/dp/exchange-argument-dp/#compare-ratios
    - `exchange-argument-dp#place-at-ends` 大きい順に左右の端へ置く（黄）：https://yuukougun.github.io/kyopro-atlas/dp/exchange-argument-dp/#place-at-ends

## グリッド上の DP（dp-grid） {#dp-grid}

- id：`dp-grid`　レベル：水　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/dp/dp-grid/
- 別名：グリッド DP、Grid DP、格子路の DP、最大正方形
- 種類：DP
- 前提：`dp-basics`
- サイン：
    - 言い回し：右か下にしか動けない
    - 言い回し：経路の数・経路上で集める値の最大
    - 言い回し：条件を満たす正方形の数・最大の正方形
    - 制約：H, W ≤ 3000 程度
- 節：
    - `dp-grid#order-and-init` 計算順序と初期化（1 行目・1 列目・壁）：https://yuukougun.github.io/kyopro-atlas/dp/dp-grid/#order-and-init
    - `dp-grid#extra-state` 状態を足す（今の行で拾った個数・作れる差の集合）：https://yuukougun.github.io/kyopro-atlas/dp/dp-grid/#extra-state
    - `dp-grid#directional-prefix` 方向ごとの累積和で遷移をまとめる：https://yuukougun.github.io/kyopro-atlas/dp/dp-grid/#directional-prefix
    - `dp-grid#largest-square` 最大の正方形（左・上・左上の min + 1）：https://yuukougun.github.io/kyopro-atlas/dp/dp-grid/#largest-square
    - `dp-grid#flip-direction` 向きを反転してもう一度：https://yuukougun.github.io/kyopro-atlas/dp/dp-grid/#flip-direction
    - `dp-grid#top-k-on-path` 経路上の上位 K 個（K 番目を固定して状態に）（黄）：https://yuukougun.github.io/kyopro-atlas/dp/dp-grid/#top-k-on-path

## 区間分割 DP（dp-sequence-partition） {#dp-sequence-partition}

- id：`dp-sequence-partition`　レベル：水　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/dp/dp-sequence-partition/
- 別名：区間分割型 DP、仕切りを入れる DP、列を区切る DP
- 種類：DP
- 前提：`dp-prefix-sum`
- サイン：
    - 言い回し：列をいくつかの連続部分に分ける方法の数
    - 言い回し：各区間のコストの和の最小
    - 言い回し：各区間が条件を満たすように区切れるか
    - 式の形：dp[i] = Σ（または min）\_{j < i, [j, i) が条件を満たす} dp[j]
- 節：
    - `dp-sequence-partition#last-block` 最後の区間で分ける（空の区切りを 1 通りと数える）：https://yuukougun.github.io/kyopro-atlas/dp/dp-sequence-partition/#last-block
    - `dp-sequence-partition#vs-interval-dp` 区間 DP との違い：https://yuukougun.github.io/kyopro-atlas/dp/dp-sequence-partition/#vs-interval-dp
    - `dp-sequence-partition#two-pointers` 遷移元の範囲が単調に動く：尺取りと累積和：https://yuukougun.github.io/kyopro-atlas/dp/dp-sequence-partition/#two-pointers
    - `dp-sequence-partition#block-index` 区間の番号に依存する条件：番号を状態に足す（青）：https://yuukougun.github.io/kyopro-atlas/dp/dp-sequence-partition/#block-index

## 最長増加部分列（lis） {#lis}

- id：`lis`　レベル：水　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/dp/lis/
- 別名：LIS、Longest Increasing Subsequence、最長減少部分列、Dilworth の定理、増加列への最小分割
- 種類：DP、二分探索
- 前提：`dp-basics`、`binary-search`
- ACL：`segtree`
- サイン：
    - 制約：N ≤ 2×10^5 で「部分列」「単調増加」
    - 言い回し：最小で何本の増加（減少）列に分けられるか・何色で塗れるか
    - 言い回し：抜いて差し込む操作の最小回数
    - 言い回し：箱・円を入れ子にできる最大個数
- 節：
    - `lis#binary-search` 二分探索版（L が単調になる理由・狭義は lower_bound、広義は upper_bound）：https://yuukougun.github.io/kyopro-atlas/dp/lis/#binary-search
    - `lis#segment-tree` セグメント木版（重み付き・各要素で終わる最長・数え上げ）：https://yuukougun.github.io/kyopro-atlas/dp/lis/#segment-tree
    - `lis#restore` 復元（直前の要素を記録する）：https://yuukougun.github.io/kyopro-atlas/dp/lis/#restore
    - `lis#contained` 各要素が LIS に含まれうるか（前後から 2 回求める）（青）：https://yuukougun.github.io/kyopro-atlas/dp/lis/#contained
    - `lis#nesting` 2 次元の入れ子（一方は昇順・もう一方は降順に並べる）（青）：https://yuukougun.github.io/kyopro-atlas/dp/lis/#nesting
    - `lis#variants` 1 か所だけ変更できる LIS・木の上の LIS（青）：https://yuukougun.github.io/kyopro-atlas/dp/lis/#variants
    - `lis#dilworth` Dilworth の定理（増加列への最小分割数＝最長減少部分列の長さ）（青）：https://yuukougun.github.io/kyopro-atlas/dp/lis/#dilworth

## 最長共通部分列と編集距離（lcs） {#lcs}

- id：`lcs`　レベル：水　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/dp/lcs/
- 別名：LCS、Longest Common Subsequence、レーベンシュタイン距離、Edit Distance、Levenshtein Distance、最長共通部分文字列、DP の DP
- 種類：DP、文字列
- 前提：`dp-basics`
- サイン：
    - 制約：2 つの列・文字列で N, M ≤ 3000〜5000
    - 言い回し：共通の部分列の最長・共通部分列の組の数
    - 言い回し：挿入・削除・置換で一致させる最小回数
    - 言い回し：ある値（2 つの文字列の最長共通部分列の長さなど）がちょうど k になる文字列の数
- 節：
    - `lcs#recurrence` 表の意味と遷移（一致する末尾を使って損をしない理由）：https://yuukougun.github.io/kyopro-atlas/dp/lcs/#recurrence
    - `lcs#restore` 復元（右下から逆にたどる）：https://yuukougun.github.io/kyopro-atlas/dp/lcs/#restore
    - `lcs#edit-distance` 編集距離（挿入・削除・置換の 3 方向のコスト）：https://yuukougun.github.io/kyopro-atlas/dp/lcs/#edit-distance
    - `lcs#substring` 部分列と部分文字列の違い（最長共通部分文字列）：https://yuukougun.github.io/kyopro-atlas/dp/lcs/#substring
    - `lcs#count-pairs` 共通部分列の組の数（包除で重複を引く・2 次元の累積和）（青）：https://yuukougun.github.io/kyopro-atlas/dp/lcs/#count-pairs
    - `lcs#palindromic-subsequence` 最長回文部分列（S と反転の LCS）：https://yuukougun.github.io/kyopro-atlas/dp/lcs/#palindromic-subsequence
    - `lcs#dp-of-dp` LCS の値ごとに数える：DP の DP（内側の DP の 1 行を外側の状態にする）（黄）：https://yuukougun.github.io/kyopro-atlas/dp/lcs/#dp-of-dp

## 部分列 DP（subsequence-dp） {#subsequence-dp}

- id：`subsequence-dp`　レベル：黄　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/dp/subsequence-dp/
- 別名：異なる部分列の数、部分列の個数、Distinct Subsequences
- 種類：DP、文字列、数え上げ
- 前提：`subsequence-matching`、`counting-dedup`
- サイン：
    - 言い回し：異なる部分列の個数
    - 言い回し：部分列として現れない最短の文字列（辞書順最小）
    - 言い回し：辞書順で K 番目の部分列
    - 制約：文字の種類 26 程度、|S| ≤ 2×10^5
- 節：
    - `subsequence-dp#positions-or-strings` 位置の組を数えるか、異なる文字列を数えるか：https://yuukougun.github.io/kyopro-atlas/dp/subsequence-dp/#positions-or-strings
    - `subsequence-dp#leftmost` 最も左を取る取り出し方が一意な理由：https://yuukougun.github.io/kyopro-atlas/dp/subsequence-dp/#leftmost
    - `subsequence-dp#next-table-dp` 次の出現位置の表で配る DP：https://yuukougun.github.io/kyopro-atlas/dp/subsequence-dp/#next-table-dp
    - `subsequence-dp#shortest-non-subsequence` 部分列として現れない最短の文字列（後ろから DP して辞書順最小に復元）：https://yuukougun.github.io/kyopro-atlas/dp/subsequence-dp/#shortest-non-subsequence
    - `subsequence-dp#kth-subsequence` 辞書順 K 番目の部分列（後ろからの個数で先頭から決める）：https://yuukougun.github.io/kyopro-atlas/dp/subsequence-dp/#kth-subsequence
    - `subsequence-dp#with-conditions` 条件付き・言い換えてから数える（隣り合う位置を選ばない・累積和の列・TT の形）：https://yuukougun.github.io/kyopro-atlas/dp/subsequence-dp/#with-conditions

## 区間 DP（interval-dp） {#interval-dp}

- id：`interval-dp`　レベル：青　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/dp/interval-dp/
- 別名：dp\[l][r]、Interval DP、Range DP、区間を状態にする DP
- 種類：DP
- 前提：`dp-order`、`memoized-recursion`
- サイン：
    - 制約：N ≤ 300〜500 で O(N^3) が通る
    - 言い回し：隣り合うものを合体させる・消す操作のコストの最小
    - 言い回し：列の両端から交互に取っていく
    - 言い回し：括弧の対応・回文
- 節：
    - `interval-dp#state` 区間を状態にする（状態・遷移・初期値・答え）：https://yuukougun.github.io/kyopro-atlas/dp/interval-dp/#state
    - `interval-dp#by-length` 長さ順に埋める理由（l を昇順に回すと困ること）：https://yuukougun.github.io/kyopro-atlas/dp/interval-dp/#by-length
    - `interval-dp#split-point` 分割点型（最後に行う操作で区間を 2 つに割る）：https://yuukougun.github.io/kyopro-atlas/dp/interval-dp/#split-point
    - `interval-dp#ends` 両端型（左端か右端を取る）：https://yuukougun.github.io/kyopro-atlas/dp/interval-dp/#ends
    - `interval-dp#last-operation` 最後に残す・最後に消すものを決める型：https://yuukougun.github.io/kyopro-atlas/dp/interval-dp/#last-operation
    - `interval-dp#pair-with-left-end` 端の相手で分ける数え上げ（二項係数で操作の順序を混ぜる）：https://yuukougun.github.io/kyopro-atlas/dp/interval-dp/#pair-with-left-end

## 区間 DP の応用（interval-dp-advanced） {#interval-dp-advanced}

- id：`interval-dp-advanced`　レベル：黄　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/dp/interval-dp-advanced/
- 別名：区間 DP で木を数える、区間ゲーム
- 種類：DP、数え上げ
- 前提：`interval-dp`、`binomial-coefficient`
- サイン：
    - 言い回し：頂点を訪れた順（行きがけ順）が与えられたときの根付き木の数
    - 言い回し：区間を選び合うゲームの勝敗
    - 言い回し：数直線上を左右に動き、訪れた範囲が常に連続している
    - 制約：N ≤ 400 前後
- 節：
    - `interval-dp-advanced#dfs-order-trees` DFS 順の区間＝部分木（木の数え上げ）：https://yuukougun.github.io/kyopro-atlas/dp/interval-dp-advanced/#dfs-order-trees
    - `interval-dp-advanced#grundy` 区間ごとの Grundy 数（ゲーム）：https://yuukougun.github.io/kyopro-atlas/dp/interval-dp-advanced/#grundy
    - `interval-dp-advanced#visited-range` 訪れた区間の両端と今いる端を状態にする：https://yuukougun.github.io/kyopro-atlas/dp/interval-dp-advanced/#visited-range
    - `interval-dp-advanced#digits-and-ranges` 桁と区間で分ける（'?' を含む数の列）：https://yuukougun.github.io/kyopro-atlas/dp/interval-dp-advanced/#digits-and-ranges

## bitDP（bit-dp） {#bit-dp}

- id：`bit-dp`　レベル：水　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/dp/bit-dp/
- 別名：ビット DP、集合 DP、Bitmask DP、巡回セールスマン問題、TSP、Traveling Salesman Problem、ハミルトン路
- 種類：DP、ビット演算
- 前提：`dp-state-design`、`bit-full-search`
- サイン：
    - 制約：N ≤ 16〜20
    - 言い回し：すべての地点を 1 回ずつ回って戻る最短の経路
    - 言い回し：順番を決める・使ったものの集合が将来に効く
    - 制約：特別な地点が K ≤ 17 個（ほかの地点はグラフで結ばれている）
- 節：
    - `bit-dp#subsets-as-integers` 集合を整数で表す・昇順に回してよい理由：https://yuukougun.github.io/kyopro-atlas/dp/bit-dp/#subsets-as-integers
    - `bit-dp#set-only` 集合だけを状態にする（マッチングの数）：https://yuukougun.github.io/kyopro-atlas/dp/bit-dp/#set-only
    - `bit-dp#tsp` 集合と最後に使ったもの（巡回セールスマン・ハミルトン路）：https://yuukougun.github.io/kyopro-atlas/dp/bit-dp/#tsp
    - `bit-dp#complexity` 計算量とメモリの見積もり：https://yuukougun.github.io/kyopro-atlas/dp/bit-dp/#complexity
    - `bit-dp#with-shortest-paths` ほかの探索と組み合わせる（BFS・ワーシャルフロイドで距離を前計算してから）（青）：https://yuukougun.github.io/kyopro-atlas/dp/bit-dp/#with-shortest-paths
    - `bit-dp#games` ゲームの状態を集合で持つ：https://yuukougun.github.io/kyopro-atlas/dp/bit-dp/#games
    - `bit-dp#primes` 素数の使用状況を集合で持つ（黄）：https://yuukougun.github.io/kyopro-atlas/dp/bit-dp/#primes

## 部分集合を列挙する DP（subset-enumeration-dp） {#subset-enumeration-dp}

- id：`subset-enumeration-dp`　レベル：青　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/dp/subset-enumeration-dp/
- 別名：3^N DP、部分集合の部分集合、Submask Enumeration、グループ分け DP
- 種類：DP、ビット演算
- 前提：`bit-dp`
- サイン：
    - 言い回し：N 個をいくつかのグループに分ける方法の数・最適値
    - 言い回し：集合を部分集合の和に分割する
    - 制約：N ≤ 16〜18（3&#94;N ≈ 4×10&#94;7〜4×10&#94;8）
- 節：
    - `subset-enumeration-dp#submask-loop` 部分集合の部分集合を列挙する（T = (T − 1) & S）：https://yuukougun.github.io/kyopro-atlas/dp/subset-enumeration-dp/#submask-loop
    - `subset-enumeration-dp#why-3n` 3^N になる理由（各要素が 3 通り）：https://yuukougun.github.io/kyopro-atlas/dp/subset-enumeration-dp/#why-3n
    - `subset-enumeration-dp#fix-minimum` 最小の要素を含むグループから決める（順序の重複を除く）：https://yuukougun.github.io/kyopro-atlas/dp/subset-enumeration-dp/#fix-minimum
    - `subset-enumeration-dp#group-count` グループの数を状態に足す：https://yuukougun.github.io/kyopro-atlas/dp/subset-enumeration-dp/#group-count
    - `subset-enumeration-dp#vs-zeta` 高速ゼータ変換との使い分け：https://yuukougun.github.io/kyopro-atlas/dp/subset-enumeration-dp/#vs-zeta

## プロファイル DP（broken-profile-dp） {#broken-profile-dp}

- id：`broken-profile-dp`　レベル：黄　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/dp/broken-profile-dp/
- 別名：Broken Profile DP、插頭 DP、フロンティア法、連結性 DP、スライド bitDP、敷き詰めの DP
- 種類：DP、ビット演算
- 前提：`bit-dp`
- サイン：
    - 制約：グリッドの短い辺 ≤ 6〜14
    - 言い回し：タイル・ドミノの敷き詰め方の数
    - 言い回し：隣り合わないように置く・隣と異なる色で塗る方法の数
    - 言い回し：黒マスが連結になる塗り方
- 節：
    - `broken-profile-dp#row-by-row` 1 行ずつ進める（行の配置パターンを状態に）：https://yuukougun.github.io/kyopro-atlas/dp/broken-profile-dp/#row-by-row
    - `broken-profile-dp#cell-by-cell` 1 マスずつ進める（境界の折れ線を状態に）：https://yuukougun.github.io/kyopro-atlas/dp/broken-profile-dp/#cell-by-cell
    - `broken-profile-dp#compress` 取り得る状態だけを列挙して番号を付ける（圧縮）：https://yuukougun.github.io/kyopro-atlas/dp/broken-profile-dp/#compress
    - `broken-profile-dp#with-matrix-power` 長さが巨大なら行列累乗と組み合わせる：https://yuukougun.github.io/kyopro-atlas/dp/broken-profile-dp/#with-matrix-power
    - `broken-profile-dp#connectivity` 連結性を持つ（フロンティア法）（発展）：https://yuukougun.github.io/kyopro-atlas/dp/broken-profile-dp/#connectivity

## 桁 DP（digit-dp） {#digit-dp}

- id：`digit-dp`　レベル：水　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/dp/digit-dp/
- 別名：Digit DP、smaller フラグ、未満フラグ、leading zero
- 種類：DP、数え上げ
- 前提：`dp-state-design`、`mod-arithmetic`
- サイン：
    - 制約：N ≤ 10^18、または N が 10^4 桁の文字列
    - 言い回し：N 以下で条件を満たす整数の個数・総和
    - 言い回し：各桁の和・0 でない桁の数
    - 言い回し：K 以下の X について、XOR や AND の条件を満たすものを数える・最大化する
- 節：
    - `digit-dp#tight-flag` N と一致しているかのフラグ（一致したままの道は 1 本だけ）：https://yuukougun.github.io/kyopro-atlas/dp/digit-dp/#tight-flag
    - `digit-dp#extra-state` 問題の情報を状態に足す（桁和の余り・個数）：https://yuukougun.github.io/kyopro-atlas/dp/digit-dp/#extra-state
    - `digit-dp#leading-zero` leading zero を区別するとき：https://yuukougun.github.io/kyopro-atlas/dp/digit-dp/#leading-zero
    - `digit-dp#binary` 2 進の桁 DP（XOR・AND）：https://yuukougun.github.io/kyopro-atlas/dp/digit-dp/#binary
    - `digit-dp#fix-divisor` 割る数を全探索して桁 DP を繰り返す：https://yuukougun.github.io/kyopro-atlas/dp/digit-dp/#fix-divisor

## 桁 DP の応用（digit-dp-advanced） {#digit-dp-advanced}

- id：`digit-dp-advanced`　レベル：黄　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/dp/digit-dp-advanced/
- 別名：繰り上がりの DP、上限と下限の桁 DP、複数の数の桁 DP
- 種類：DP、数え上げ
- 前提：`digit-dp`
- サイン：
    - 言い回し：2 つ以上の数を同時に決める（a + b = a xor b・3 つの数の xor）
    - 言い回し：支払いとお釣りの枚数の最小
    - 言い回し：使った数字の種類数・指定の数字を全部含む数
    - 言い回し：L ≤ x ≤ y ≤ R の組を数える（上限と下限の両方）
- 節：
    - `digit-dp-advanced#multiple-numbers` 複数の数を同時に決める（フラグを並べる）：https://yuukougun.github.io/kyopro-atlas/dp/digit-dp-advanced/#multiple-numbers
    - `digit-dp-advanced#lower-and-upper` 上限と下限の両方（2 つのフラグ）：https://yuukougun.github.io/kyopro-atlas/dp/digit-dp-advanced/#lower-and-upper
    - `digit-dp-advanced#carry` 下の桁からの繰り上がりを状態にする：https://yuukougun.github.io/kyopro-atlas/dp/digit-dp-advanced/#carry
    - `digit-dp-advanced#sparse-states` 状態の種類が少ないことを使う（桁の積を map で・数字の集合を bit で）：https://yuukougun.github.io/kyopro-atlas/dp/digit-dp-advanced/#sparse-states
    - `digit-dp-advanced#count-and-sum` 個数と総和を同時に持つ（総和 += 個数×桁の値）：https://yuukougun.github.io/kyopro-atlas/dp/digit-dp-advanced/#count-and-sum

## 木 DP（tree-dp） {#tree-dp}

- id：`tree-dp`　レベル：水　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/dp/tree-dp/
- 別名：Tree DP、部分木の DP、木の上の DP
- 種類：DP、木
- 前提：`dp-basics`、`tree-traversal`
- サイン：
    - 言い回し：木の各頂点を塗る・選ぶ（隣り合う頂点に条件がある）
    - 言い回し：木の辺を選ぶ（次数の上限つき）
    - 言い回し：部分木ごとの値（部分木の上位 K 個など）
    - 言い回し：木の各頂点からほかの全頂点への距離の総和
- 節：
    - `tree-dp#postorder` 帰りがけ順に子から集める（再帰なしなら BFS 順の逆）：https://yuukougun.github.io/kyopro-atlas/dp/tree-dp/#postorder
    - `tree-dp#vertex-states` 頂点の選択を状態に足す（独立集合型）：https://yuukougun.github.io/kyopro-atlas/dp/tree-dp/#vertex-states
    - `tree-dp#path-at-top` パスを最も浅い頂点で数える（子の上位 2 つ）：https://yuukougun.github.io/kyopro-atlas/dp/tree-dp/#path-at-top
    - `tree-dp#product-of-children` 子の値の積・和（数え上げ）：https://yuukougun.github.io/kyopro-atlas/dp/tree-dp/#product-of-children
    - `tree-dp#top-down` 根から下へ配る：https://yuukougun.github.io/kyopro-atlas/dp/tree-dp/#top-down
    - `tree-dp#reroot-difference` 根を動かした差分（全方位の入口）：https://yuukougun.github.io/kyopro-atlas/dp/tree-dp/#reroot-difference
    - `tree-dp#greedy-children` 子ごとの「得」を大きい順に取る（青）：https://yuukougun.github.io/kyopro-atlas/dp/tree-dp/#greedy-children
    - `tree-dp#with-binary-search` 二分探索と組み合わせて判定にする（黄）：https://yuukougun.github.io/kyopro-atlas/dp/tree-dp/#with-binary-search
    - `tree-dp#tree-dp-merge` 部分木の情報をデータ構造で持ってマージする（マージテク）（黄）：https://yuukougun.github.io/kyopro-atlas/dp/tree-dp/#tree-dp-merge

## 全方位木 DP（rerooting） {#rerooting}

- id：`rerooting`　レベル：青　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/dp/rerooting/
- 別名：Rerooting、ReRooting DP、換根 DP
- 種類：DP、木
- 前提：`tree-dp`、`prefix-sum`
- サイン：
    - 言い回し：すべての頂点について、その頂点を根（起点）としたときの値
    - 言い回し：各頂点から最も遠い頂点までの距離（頂点や辺の重みつき）
    - 式の形：根を v としたときの木 DP の値を、すべての v について求めたい（N 回の木 DP は O(N^2)）
- 節：
    - `rerooting#what-changes` 根を隣へ移すと変わるのは親側の部分木だけ：https://yuukougun.github.io/kyopro-atlas/dp/rerooting/#what-changes
    - `rerooting#framework` 一般の枠組み（子の値の合成と「根を付ける」操作を分ける）：https://yuukougun.github.io/kyopro-atlas/dp/rerooting/#framework
    - `rerooting#exclude-self` 自分以外の兄弟の合成（左右からの累積）：https://yuukougun.github.io/kyopro-atlas/dp/rerooting/#exclude-self
    - `rerooting#patterns` 合成と根を付ける操作の作り方の型：https://yuukougun.github.io/kyopro-atlas/dp/rerooting/#patterns
    - `rerooting#when-to-use` 使い分け（最遠点は直径の性質で、距離の総和は根の移動の差分で済む）：https://yuukougun.github.io/kyopro-atlas/dp/rerooting/#when-to-use

## 二乗の木 DP（tree-dp-square） {#tree-dp-square}

- id：`tree-dp-square`　レベル：黄　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/dp/tree-dp-square/
- 別名：2 乗の木 DP、O(N^2) の木 DP、木の上のナップサック
- 種類：DP、木
- 前提：`tree-dp`、`knapsack-01`
- サイン：
    - 制約：N ≤ 2000〜5000 の木
    - 言い回し：部分木から K 個選ぶ・連結成分の数ごとに数える
    - 式の形：dp\[v][k] を子の dp\[c][j] との (k, j) の組の全探索でマージしていて、O(N^3) に見える
- 節：
    - `tree-dp-square#why-n2` O(N^2) で済む理由（頂点の組が LCA で 1 回だけ数えられる）：https://yuukougun.github.io/kyopro-atlas/dp/tree-dp-square/#why-n2
    - `tree-dp-square#size-bounded` 配列の長さを部分木のサイズに合わせる：https://yuukougun.github.io/kyopro-atlas/dp/tree-dp-square/#size-bounded
    - `tree-dp-square#cap-k` サイズを K で打ち切ると O(NK)：https://yuukougun.github.io/kyopro-atlas/dp/tree-dp-square/#cap-k
    - `tree-dp-square#state-and-count` 頂点の状態と個数を同時に持つ：https://yuukougun.github.io/kyopro-atlas/dp/tree-dp-square/#state-and-count

## 挿入 DP・箱根駅伝 DP（insertion-dp） {#insertion-dp}

- id：`insertion-dp`　レベル：黄　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/dp/insertion-dp/
- 別名：相対順位の DP、順列の DP、箱根 DP、Insertion DP、連結成分 DP、Connected Component DP
- 種類：DP、数え上げ
- 前提：`dp-state-design`、`dp-prefix-sum`
- サイン：
    - 言い回し：順列で隣り合う大小関係（< と >）が指定される
    - 言い回し：|p_i − i| の和がちょうど K の順列の数
    - 言い回し：値の小さい順に、列の好きな位置へ挿入していく
    - 制約：N ≤ 3000 程度の順列の数え上げ
- 節：
    - `insertion-dp#relative-rank` 相対順位を状態にする（最後の要素が何番目か）：https://yuukougun.github.io/kyopro-atlas/dp/insertion-dp/#relative-rank
    - `insertion-dp#prefix-sum` 遷移は区間になるので累積和でまとめる：https://yuukougun.github.io/kyopro-atlas/dp/insertion-dp/#prefix-sum
    - `insertion-dp#insert-by-value` 値の大きい（小さい）順に挿入していく見方：https://yuukougun.github.io/kyopro-atlas/dp/insertion-dp/#insert-by-value
    - `insertion-dp#hakone-ekiden-dp` 箱根駅伝 DP（相手が未定の位置と値の数を持つ）：https://yuukougun.github.io/kyopro-atlas/dp/insertion-dp/#hakone-ekiden-dp
    - `insertion-dp#connected-component-dp` 連結成分 DP（ブロックを作る・端に付ける・つなぐ）（発展）：https://yuukougun.github.io/kyopro-atlas/dp/insertion-dp/#connected-component-dp

## DP の高速化の選び方（dp-speedup-overview） {#dp-speedup-overview}

- id：`dp-speedup-overview`　レベル：—　段階：stub　type：hub
- URL：https://yuukougun.github.io/kyopro-atlas/dp/dp-speedup-overview/
- 別名：DP の高速化、DP 高速化、DP 最適化、DP Optimization、遷移の高速化
- 種類：DP、案内
- 前提：`dp-basics`
- サイン：
    - 式の形：素直に書いた DP の遷移が状態 1 つあたり O(N) かかり、全体で O(N^2) になる
- 節：
    - `dp-speedup-overview#two-directions` 状態を減らすか、遷移を速くするか：https://yuukougun.github.io/kyopro-atlas/dp/dp-speedup-overview/#two-directions
    - `dp-speedup-overview#read-the-recurrence` 貰う形の式を書き、右辺の形を見る：https://yuukougun.github.io/kyopro-atlas/dp/dp-speedup-overview/#read-the-recurrence
    - `dp-speedup-overview#shape-to-tool` 早見表：遷移の形から道具を選ぶ：https://yuukougun.github.io/kyopro-atlas/dp/dp-speedup-overview/#shape-to-tool
    - `dp-speedup-overview#algebraic-tools` 多項式の積・同じ線形の遷移の繰り返し（畳み込み・行列累乗へ）：https://yuukougun.github.io/kyopro-atlas/dp/dp-speedup-overview/#algebraic-tools
    - `dp-speedup-overview#convexity` 凸性を使う高速化（CHT・Monge・Alien DP・Slope Trick）の使いどころ：https://yuukougun.github.io/kyopro-atlas/dp/dp-speedup-overview/#convexity

## セグメント木・スライド最小値による DP の高速化（dp-segment-tree） {#dp-segment-tree}

- id：`dp-segment-tree`　レベル：青　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/dp/dp-segment-tree/
- 別名：セグ木 DP、BIT で DP を速くする、値を添字にした DP、deque DP、単調スタック DP
- 種類：DP、区間クエリ、尺取り・スライド窓
- 前提：`dp-prefix-sum`、`segment-tree-on-values`
- ACL：`segtree`、`fenwick_tree`
- サイン：
    - 言い回し：隣り合う要素の差が D 以下になるように選ぶ部分列の最長
    - 式の形：dp[i] = max_{j < i, l ≤ a_j ≤ r} dp[j] + c のように、遷移元が添字や値の範囲の最小・最大
    - 式の形：遷移のコストに |x_i − x_j| を含む（x_j < x_i と x_j > x_i で分けられる）
    - 式の形：dp[i] = min_{i−K ≤ j < i} dp[j] + c（窓が単調に動く）
- 節：
    - `dp-segment-tree#values-on-segment-tree` dp の値を位置や値を添字にしたセグメント木に載せる（座標圧縮）：https://yuukougun.github.io/kyopro-atlas/dp/dp-segment-tree/#values-on-segment-tree
    - `dp-segment-tree#split-abs` |x − y| を左右に分けて 2 本のセグメント木に：https://yuukougun.github.io/kyopro-atlas/dp/dp-segment-tree/#split-abs
    - `dp-segment-tree#interval-cover` 区間を覆う最小コスト（右端までの最小）：https://yuukougun.github.io/kyopro-atlas/dp/dp-segment-tree/#interval-cover
    - `dp-segment-tree#dp-sliding-window` スライド最小値（単調 deque）と単調スタックによる遷移：https://yuukougun.github.io/kyopro-atlas/dp/dp-segment-tree/#dp-sliding-window
    - `dp-segment-tree#which-tool` セグメント木・累積和・スライド最小値の使い分け：https://yuukougun.github.io/kyopro-atlas/dp/dp-segment-tree/#which-tool

## インライン DP（inline-dp） {#inline-dp}

- id：`inline-dp`　レベル：青　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/dp/inline-dp/
- 別名：in-place DP、Inline DP、配列を使い回して一括更新、遅延セグ木 DP
- 種類：DP、区間クエリ
- 前提：`dp-segment-tree`、`lazy-segment-tree`、`knapsack-01`
- ACL：`lazy_segtree`
- サイン：
    - 式の形：dp\[i][\*] から dp\[i+1][\*] で変わる場所が少ない
    - 式の形：遷移で dp 全体に一律の加算・平行移動が入る
    - 式の形：区間 [l, r] の右端 r で、l 以降の位置の dp にまとめて加算する
- 節：
    - `inline-dp#diff-per-row` 2 次元の表で考えてから、行ごとに変わる場所を書き出す：https://yuukougun.github.io/kyopro-atlas/dp/inline-dp/#diff-per-row
    - `inline-dp#update-changes` 変わる場所だけを更新する（辺を 1 本ずつ緩和する）：https://yuukougun.github.io/kyopro-atlas/dp/inline-dp/#update-changes
    - `inline-dp#global-shift` 全体のシフトを添字のずらしで表す：https://yuukougun.github.io/kyopro-atlas/dp/inline-dp/#global-shift
    - `inline-dp#lazy-segment-tree` 区間加算と区間最大を遅延セグメント木で（区間の右端で加算する）：https://yuukougun.github.io/kyopro-atlas/dp/inline-dp/#lazy-segment-tree
    - `inline-dp#with-monotonic-stack` 単調スタックと組み合わせる（黄）：https://yuukougun.github.io/kyopro-atlas/dp/inline-dp/#with-monotonic-stack

## 動的 DP（dynamic-dp） {#dynamic-dp}

- id：`dynamic-dp`　レベル：発展　段階：stub　type：overview
- URL：https://yuukougun.github.io/kyopro-atlas/dp/dynamic-dp/
- 別名：Dynamic DP、DDP、遷移行列のセグメント木
- 種類：DP、線形代数・行列、区間クエリ
- 前提：`matrix-power`、`segment-tree-monoids`
- ACL：`segtree`
- サイン：
    - 言い回し：DP をする列に 1 点更新のクエリが来て、そのたびに DP の答えを求める
    - 言い回し：列の区間 [l, r] だけで DP をしたときの答えを、クエリごとに求める
- 節：
    - `dynamic-dp#what-it-does` 何ができるか（1 点更新と区間の DP の答え）：https://yuukougun.github.io/kyopro-atlas/dp/dynamic-dp/#what-it-does
    - `dynamic-dp#matrix-on-segment-tree` 遷移を行列にしてセグメント木に載せる（ACL の segtree の S を行列にする）：https://yuukougun.github.io/kyopro-atlas/dp/dynamic-dp/#matrix-on-segment-tree
    - `dynamic-dp#order-and-identity` 積の向きと単位行列：https://yuukougun.github.io/kyopro-atlas/dp/dynamic-dp/#order-and-identity
    - `dynamic-dp#on-trees` 木の上の動的 DP（Static Top Tree へ）：https://yuukougun.github.io/kyopro-atlas/dp/dynamic-dp/#on-trees
    - `dynamic-dp#verify` ライブラリでの検証（Library Checker の point_set_range_composite が土台）：https://yuukougun.github.io/kyopro-atlas/dp/dynamic-dp/#verify

## Convex Hull Trick と Li Chao Tree（cht） {#cht}

- id：`cht`　レベル：発展　段階：stub　type：overview
- URL：https://yuukougun.github.io/kyopro-atlas/dp/cht/
- 別名：CHT、傾き最適化、斜率优化、李超线段树、直線の最小値
- 種類：DP、データ構造
- 前提：`dp-basics`、`convex-hull`
- サイン：
    - 式の形：遷移のコストが i と j の積の項を 1 つだけ含む（(h_i − h_j)^2 など）
    - 言い回し：直線を追加しながら、任意の x での最小値・最大値を答える
- 節：
    - `cht#lines` 遷移を直線の最小値に変形する：https://yuukougun.github.io/kyopro-atlas/dp/cht/#lines
    - `cht#lower-envelope` 下側の包絡線と不要な直線（傾きもクエリも単調なら deque）：https://yuukougun.github.io/kyopro-atlas/dp/cht/#lower-envelope
    - `cht#non-monotone-queries` クエリが単調でないとき（二分探索）：https://yuukougun.github.io/kyopro-atlas/dp/cht/#non-monotone-queries
    - `cht#li-chao-tree` Li Chao Tree（区間の真ん中で勝つ直線を残す）：https://yuukougun.github.io/kyopro-atlas/dp/cht/#li-chao-tree
    - `cht#verify` ライブラリでの検証（Library Checker の line_add_get_min・segment_add_get_min）：https://yuukougun.github.io/kyopro-atlas/dp/cht/#verify

## Monge 性による DP の高速化（monge） {#monge}

- id：`monge`　レベル：発展　段階：stub　type：overview
- URL：https://yuukougun.github.io/kyopro-atlas/dp/monge/
- 別名：Monge、四角不等式、四辺形不等式、Quadrangle Inequality、monotone minima、分割統治 DP、Divide and Conquer DP、SMAWK、LARSCH、Knuth-Yao、Knuth's optimization、(max,+) 畳み込み、min-plus 畳み込み、DP の凸性
- 種類：DP、ダブリング・分割統治
- 前提：`dp-sequence-partition`、`divide-and-conquer`
- サイン：
    - 式の形：区間分割 DP のコストが c(a, c) + c(b, d) ≤ c(a, d) + c(b, c) を満たす（区間を広げるほど増え方が大きい）
    - 式の形：最適な区切り位置 opt(i) が i について単調に動く
    - 言い回し：区間から k 個選ぶときの最大値を、すべての k について求める
    - 制約：N ≤ 10^5 の列を K（数十）個の区間に分ける
- 節：
    - `monge#definition` Monge 性の定義と確かめ方：https://yuukougun.github.io/kyopro-atlas/dp/monge/#definition
    - `monge#monotone-minima` monotone minima（分割統治で O(N log N)）：https://yuukougun.github.io/kyopro-atlas/dp/monge/#monotone-minima
    - `monge#smawk-larsch` SMAWK・LARSCH（O(N)・オンラインに決まる DP）：https://yuukougun.github.io/kyopro-atlas/dp/monge/#smawk-larsch
    - `monge#knuth-yao` Knuth-Yao（区間 DP の分割点の範囲を絞って O(N^2)）：https://yuukougun.github.io/kyopro-atlas/dp/monge/#knuth-yao
    - `monge#dp-convexity` DP の値の凸性（個数について凸な答え）：https://yuukougun.github.io/kyopro-atlas/dp/monge/#dp-convexity
    - `monge#convex-max-plus-convolution` 凸な列どうしの (max,+) 畳み込み（差分のマージ）：https://yuukougun.github.io/kyopro-atlas/dp/monge/#convex-max-plus-convolution
    - `monge#verify` ライブラリでの検証（Library Checker の min_plus_convolution_convex_arbitrary など）：https://yuukougun.github.io/kyopro-atlas/dp/monge/#verify

## Alien DP（alien-dp） {#alien-dp}

- id：`alien-dp`　レベル：発展　段階：stub　type：overview
- URL：https://yuukougun.github.io/kyopro-atlas/dp/alien-dp/
- 別名：Aliens trick、WQS 二分、Lagrangian Relaxation、Lagrange 緩和、取り消し付きの貪欲
- 種類：DP、二分探索
- 前提：`monge`、`binary-search`
- サイン：
    - 言い回し：ちょうど K 個選ぶ・K 個の区間に分ける（N, K ≤ 2×10^5）
    - 言い回し：隣り合わない k 個を選ぶ和の最大を、すべての k について答える
    - 式の形：K 個選ぶときの答え f(K) が K について凸（1 個増やすときの得が、個数が増えるほど減る）
- 節：
    - `alien-dp#penalty` 罰金 λ で個数の制約を外す（凸性が要る理由）：https://yuukougun.github.io/kyopro-atlas/dp/alien-dp/#penalty
    - `alien-dp#binary-search-lambda` λ の二分探索と、同じ値が並ぶときの扱い：https://yuukougun.github.io/kyopro-atlas/dp/alien-dp/#binary-search-lambda
    - `alien-dp#undoable-greedy` 取り消し付きの貪欲で解ける場合（優先度付きキュー）：https://yuukougun.github.io/kyopro-atlas/dp/alien-dp/#undoable-greedy
    - `alien-dp#with-monge` Monge な区間分割と組み合わせる：https://yuukougun.github.io/kyopro-atlas/dp/alien-dp/#with-monge

## Slope Trick（slope-trick） {#slope-trick}

- id：`slope-trick`　レベル：発展　段階：stub　type：overview
- URL：https://yuukougun.github.io/kyopro-atlas/dp/slope-trick/
- 別名：スロープトリック、区分線形凸関数、区分線形凸関数の管理
- 種類：DP、データ構造
- 前提：`dp-state-design`、`top-k-multiset`
- サイン：
    - 言い回し：数列を単調（広義増加）にするための、値の変更量の和の最小
    - 言い回し：時刻ごとに位置を少しずつ動かせるときの最小コスト
    - 式の形：dp\[i][x] = min_{y ≤ x} dp\[i−1][y] + |x − a_i| のように、x について区分線形で凸
- 節：
    - `slope-trick#breakpoints` 凸関数を傾きの変わる点の集まりで表す：https://yuukougun.github.io/kyopro-atlas/dp/slope-trick/#breakpoints
    - `slope-trick#two-heaps` 2 つのヒープで中央値を管理する（入口）：https://yuukougun.github.io/kyopro-atlas/dp/slope-trick/#two-heaps
    - `slope-trick#operations` |x − a| を足す・累積 min・平行移動：https://yuukougun.github.io/kyopro-atlas/dp/slope-trick/#operations
    - `slope-trick#on-trees` 木の上で凸関数をマージする（マージテクと組む）：https://yuukougun.github.io/kyopro-atlas/dp/slope-trick/#on-trees
