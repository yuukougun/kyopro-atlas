---
id: reverse-index-signs
title: 逆引き辞典（言い回しから）
aliases: [問題文のサイン, キーワードから解法, 典型の言い換え一覧, 言い回しから逆引き, 式の形から逆引き]
type: guide
field: guide
chapter: 辞書として引く
order: 10
level: null
kind: [案内]
prerequisites: []
related: [reverse-index-constraints, term-index, thinking-checklist, method-comparison, dp-speedup-overview, interval, subsequence-and-substring, permutation, bracket-sequence, mex, kth-and-median, xor, divisors-and-multiples, grid, operation-sequence, debugging-checklist, stress-testing, cpp-reverse-index]
summary: 問題文の言い回しや求めるもの、立てた式の形から、疑う手法とページを引ける。表は各ページのサインから生成し、どれから疑うかの注記を手で添える。
complexity: null
signs: []
acl: []
sections:
  - {title: 引き方と注意, anchor: how-to-read}
  - {title: 言い回しから引く, anchor: by-phrase}
  - {title: 立てた式の形から引く, anchor: by-shape}
  - {title: 1 つのサインに複数の手法が当たるとき, anchor: disambiguation}
  - {title: 題材から引く, anchor: by-topic}
  - {title: 状況から引く, anchor: by-situation}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何のページか**：問題文の言い回しや求めるもの、立てた式の形から、疑う手法とページを引ける。表は各ページのサインから生成し、どれから疑うかの注記を手で添える。
    - **使い方**：（執筆時に書く）

<!-- gen:begin signs-phrase -->
<!-- textlint-disable -->

### 探索・最適化 {#signs-phrase-search}

| 言い回し・求めるもの | ページ | レベル |
| --- | --- | --- |
| 変数が 2〜3 個で、いくつか決めれば残りが計算で決まる | [全探索の設計](../basics/brute-force.md) | 基礎 |
| 答えの候補（暗証番号・中心の座標など）が N によらず少ない | [全探索の設計](../basics/brute-force.md) | 基礎 |
| 小さい盤面を回転・平行移動して重ねる・敷き詰める | [全探索の設計](../basics/brute-force.md) | 基礎 |
| スイッチの on/off、区切る／区切らない | [bit 全探索と順列全探索](../basics/bit-full-search.md) | 基礎 |
| 2 つのグラフが頂点の付け替えで一致するか | [bit 全探索と順列全探索](../basics/bit-full-search.md) | 基礎 |
| 条件を満たす数・列を小さい順にすべて作る | [再帰による全列挙](../basics/recursive-enumeration.md) | 水 |
| タイルの敷き詰め・パズルを途中で打ち切りながら試す | [再帰による全列挙](../basics/recursive-enumeration.md) | 水 |
| 順番を自由に並べ替えてよい | [ソートで考える](../basics/sorting-techniques.md) | 基礎 |
| 安い順・効果の大きい順に取る | [ソートで考える](../basics/sorting-techniques.md) | 基礎 |
| 2 つの集合を 1 対 1 に対応させて距離の和を最小化する | [ソートで考える](../basics/sorting-techniques.md) | 基礎 |
| 成功率などの比率の大小で並べる | [ソートで考える](../basics/sorting-techniques.md) | 基礎 |
| ソート済みの列で x 以上の最初の位置・x 以下の個数 | [二分探索](../basics/binary-search.md) | 基礎 |
| 片方を固定して、もう片方が条件を満たす個数を数える | [二分探索](../basics/binary-search.md) | 基礎 |
| 左右で最も近い要素を探す | [二分探索](../basics/binary-search.md) | 基礎 |
| 最小値を最大化する／最大値を最小化する | [答えで二分探索](../basics/binary-search-answer.md) | 基礎 |
| 〜を満たす最大（最小）の X を求める | [答えで二分探索](../basics/binary-search-answer.md) | 基礎 |
| 答えを実数で出力し、誤差 10^−6 まで許される | [答えで二分探索](../basics/binary-search-answer.md) | 基礎 |
| 大小関係（順位）だけが重要 | [座標圧縮](../basics/coordinate-compression.md) | 基礎 |
| 区間の開始・終了と、時刻のクエリが混ざる | [イベントソートと平面走査の基本](../basics/event-sort.md) | 水 |
| x 座標も y 座標も大きい相手と組にする・数える | [イベントソートと平面走査の基本](../basics/event-sort.md) | 水 |
| 締め切りや有効期間がある | [イベントソートと平面走査の基本](../basics/event-sort.md) | 水 |
| クエリを先に全部読んでよい | [イベントソートと平面走査の基本](../basics/event-sort.md) | 水 |
| 2 つの独立な選択を組み合わせて条件を満たす | [半分全列挙](../basics/meet-in-the-middle.md) | 水 |
| 平均・濃度・割合・(Σa)/(Σb) の最大（最小） | [平均・中央値の最大化](../basics/fractional-binary-search.md) | 水 |
| 中央値の最大値・最小値 | [平均・中央値の最大化](../basics/fractional-binary-search.md) | 水 |
| 全区間の中央値を集めた中央値 | [平均・中央値の最大化](../basics/fractional-binary-search.md) | 水 |
| N^2 個（以上）の値の K 番目 | [K 番目の値](../basics/kth-value.md) | 青 |
| 大きい方から M 個の和 | [K 番目の値](../basics/kth-value.md) | 青 |
| 時刻や位置を 1 つ選んで、時間やコストを最小化する（谷形） | [三分探索](../basics/ternary-search.md) | 水 |
| 答えを実数で出力し、誤差が許される | [三分探索](../basics/ternary-search.md) | 水 |
| Σ\|x − a_i\| を最小化する | [絶対値の和の最小化と中央値](../basics/median-absolute.md) | 基礎 |
| マンハッタン距離の和が最小になる点 | [絶対値の和の最小化と中央値](../basics/median-absolute.md) | 基礎 |
| 全員を 1 か所に集める移動の和 | [絶対値の和の最小化と中央値](../basics/median-absolute.md) | 基礎 |
| 強いもの・安いものから順に使う | [貪欲法の考え方と正当性](../basics/greedy-basics.md) | 基礎 |
| 1 回ごとに最大（最小）のものを選ぶ操作を繰り返す | [貪欲法の考え方と正当性](../basics/greedy-basics.md) | 基礎 |
| 重ならない区間をできるだけ多く選ぶ | [区間スケジューリング・区間の串刺し](../basics/interval-scheduling.md) | 基礎 |
| すべての区間を最少の点（串）で突く | [区間スケジューリング・区間の串刺し](../basics/interval-scheduling.md) | 基礎 |
| 日が進むと選択肢が増え、各日に 1 つ選ぶ | [優先度付きキューを使う貪欲](../basics/greedy-priority-queue.md) | 水 |
| 締め切りまでに何個できるか・報酬の最大 | [優先度付きキューを使う貪欲](../basics/greedy-priority-queue.md) | 水 |
| 毎回いちばん大きい（小さい）ものを取り出して更新する | [優先度付きキューを使う貪欲](../basics/greedy-priority-queue.md) | 水 |
| 組合せの和の小さい方から K 番目（K が小さい） | [優先度付きキューを使う貪欲](../basics/greedy-priority-queue.md) | 水 |
| 並べる順番で結果が変わる | [交換論法と比較関数の設計](../basics/exchange-argument.md) | 青 |
| 文字列・数を並べて連結した結果を最大（最小）にする | [交換論法と比較関数の設計](../basics/exchange-argument.md) | 青 |
| 辞書順最小（最大）の文字列・列を出力する（なければ −1） | [辞書順最小を前から決める貪欲](../basics/lexicographic-greedy.md) | 基礎 |
| 条件を満たす中で最も小さいもの | [辞書順最小を前から決める貪欲](../basics/lexicographic-greedy.md) | 基礎 |
| 辞書順で K 番目 | [辞書順最小を前から決める貪欲](../basics/lexicographic-greedy.md) | 基礎 |
| x_{n+1} = f(x_n) の形の漸化式 | [周期性の検出](../basics/periodicity.md) | 基礎 |
| 同じ模様が繰り返し敷き詰められた盤面 | [周期性の検出](../basics/periodicity.md) | 基礎 |
| 各状態から次の状態がただ 1 つに決まる | [ダブリング](../basics/doubling.md) | 水 |
| 途中の和・最小値も必要 | [ダブリング](../basics/doubling.md) | 水 |
| 条件を満たす最大の回数を求める | [ダブリング](../basics/doubling.md) | 水 |
| レベル N のものがレベル N − 1 のものを並べて作られる | [再帰的な構造](../basics/recursion-structure.md) | 基礎 |
| 長さが 2 倍・3 倍で増える構造の K 番目 | [再帰的な構造](../basics/recursion-structure.md) | 基礎 |
| フラクタル図形を描く | [再帰的な構造](../basics/recursion-structure.md) | 基礎 |
| 区間・部分列の全部の組について数える | [分割統治](../basics/divide-and-conquer.md) | 黄 |
| 区間 [L, R] の品物だけを使うナップサックを多数のクエリで答える | [分割統治](../basics/divide-and-conquer.md) | 黄 |
| 条件が複雑で直接は数えにくい・判定しにくい | [言い換えの典型](../thinking/reformulation.md) | 水 |
| x 方向と y 方向・bit ごと・連結成分ごとに結果が独立に決まる | [言い換えの典型](../thinking/reformulation.md) | 水 |
| 3 つ組 (i < j < k) を数える | [一部を固定して数える](../thinking/fix-variable.md) | 基礎 |
| 2 つの値の組で、片方を決めればもう片方の条件が単純になる | [一部を固定して数える](../thinking/fix-variable.md) | 基礎 |
| 最大値（最小値）を決めて残りを最適化する | [一部を固定して数える](../thinking/fix-variable.md) | 基礎 |
| すべての組・区間・部分集合についての総和 | [主客転倒・寄与](../thinking/contribution.md) | 水 |
| 各要素が答えに何回足されるか | [主客転倒・寄与](../thinking/contribution.md) | 水 |
| 全区間の最小値・2 番目に大きい値などの和 | [主客転倒・寄与](../thinking/contribution.md) | 水 |
| 〜でないもの・少なくとも 1 つ含むもの | [余事象](../thinking/complement.md) | 基礎 |
| すべて異なる・条件を 1 つでも満たす | [余事象](../thinking/complement.md) | 基礎 |
| A でも B でもないものの個数 | [余事象](../thinking/complement.md) | 基礎 |
| ちょうど K 回の操作・±1 の移動 | [偶奇に着目する](../thinking/parity.md) | 基礎 |
| 和が偶数という条件 | [偶奇に着目する](../thinking/parity.md) | 基礎 |
| グリッドを 1 マスずつ動く操作の可否 | [偶奇に着目する](../thinking/parity.md) | 基礎 |
| チェス盤の塗り分け・ドミノの敷き詰め | [偶奇に着目する](../thinking/parity.md) | 基礎 |
| 操作を好きな回数・好きな順に行える | [不変量・単調に変わる量](../thinking/invariant.md) | 基礎 |
| 目標の状態に到達できるか・最終状態の最大値 | [不変量・単調に変わる量](../thinking/invariant.md) | 基礎 |
| 操作の前後で変わらない量（和・偶奇・余り）がありそう | [不変量・単調に変わる量](../thinking/invariant.md) | 基礎 |
| 辺・要素の削除のクエリ | [後ろから・逆順に考える](../thinking/reverse-thinking.md) | 基礎 |
| 操作列を復元する・操作の結果から元を求める | [後ろから・逆順に考える](../thinking/reverse-thinking.md) | 基礎 |
| 条件を満たすものを 1 つ出力せよ（存在しなければ −1） | [構築問題の考え方](../thinking/construction.md) | 基礎 |
| 操作手順を出力せよ（回数の上限が与えられている） | [構築問題の考え方](../thinking/construction.md) | 基礎 |
| 最大値を求めるが、答えに自然な上限がありそう | [構築問題の考え方](../thinking/construction.md) | 基礎 |
| i < j の組の和など、i と j を入れ替えても同じ形の式 | [対称性・鳩の巣原理・場合分け](../thinking/symmetry-pigeonhole-casework.md) | 基礎 |
| 自分以外の全員の XOR（和）が与えられる | [対称性・鳩の巣原理・場合分け](../thinking/symmetry-pigeonhole-casework.md) | 基礎 |
| N = 1 や N が小さいときだけ答えの形が違う | [対称性・鳩の巣原理・場合分け](../thinking/symmetry-pigeonhole-casework.md) | 基礎 |
| 前から順に 1 つずつ選んでいくときの、〜の最小値・最大値 | [DP の基本](../dp/dp-basics.md) | 基礎 |
| ちょうど X にできるか（可否の判定） | [DP の基本](../dp/dp-basics.md) | 基礎 |
| f(n) が f(⌊n/k⌋) などで再帰的に定義されている | [メモ化再帰](../dp/memoized-recursion.md) | 基礎 |
| 番号の小さい頂点から大きい頂点へだけ辺がある（u < v） | [DAG 上の DP](../dp/dp-dag.md) | 基礎 |
| 値が増える向きにしか移動できない | [DAG 上の DP](../dp/dp-dag.md) | 基礎 |
| 有向グラフの最長の経路の長さ・経路の本数・最短路の本数 | [DAG 上の DP](../dp/dp-dag.md) | 基礎 |
| 依存関係に従って順に決める（閉路があれば −1） | [DAG 上の DP](../dp/dp-dag.md) | 基礎 |
| 値の小さい（大きい）方へしか移れない | [DP の計算順序](../dp/dp-order.md) | 水 |
| ゴールに着いたら終わり・残り回数が 0 になったら終わり（終わりの値が分かっている） | [DP の計算順序](../dp/dp-order.md) | 水 |
| 隣り合う〜が異なる・同じことを連続して〜しない | [DP の状態の設計](../dp/dp-state-design.md) | 水 |
| 直前の選択でコストが変わる・モードが切り替わる | [DP の状態の設計](../dp/dp-state-design.md) | 水 |
| 長さ K の回文・特定の短い文字列を部分文字列に含まない文字列の数 | [DP の状態の設計](../dp/dp-state-design.md) | 水 |
| 円形に並んでいる（最後と最初も隣り合う） | [DP の状態の設計](../dp/dp-state-design.md) | 水 |
| '(' と ')' と '?' の列から正しい括弧列を作る方法の数 | [DP の状態の設計](../dp/dp-state-design.md) | 水 |
| 和（積）が M の倍数になる選び方の数 | [余り・個数を状態に持つ DP](../dp/dp-mod-state.md) | 水 |
| 平均が整数になる・平均がちょうど A になる選び方の数 | [余り・個数を状態に持つ DP](../dp/dp-mod-state.md) | 水 |
| '?' を埋めた数を M で割った余りが r になるものの数 | [余り・個数を状態に持つ DP](../dp/dp-mod-state.md) | 水 |
| 区間を 1 つ選んで、その中だけ操作する（1 回だけ変更できる） | [フェーズを状態に持つ DP](../dp/dp-phase.md) | 青 |
| 部分列として 'ABC' などが何個含まれるか（'?' を埋めた全通りの和） | [フェーズを状態に持つ DP](../dp/dp-phase.md) | 青 |
| 連続する部分列の和の最大 | [フェーズを状態に持つ DP](../dp/dp-phase.md) | 青 |
| 選び方（経路・操作列）を 1 つ出力せよ | [DP の復元](../dp/dp-reconstruction.md) | 水 |
| 条件を満たすものが複数あれば辞書順最小のものを出力せよ | [DP の復元](../dp/dp-reconstruction.md) | 水 |
| 辞書順で K 番目のものを出力せよ（K は 10^18 程度） | [DP の復元](../dp/dp-reconstruction.md) | 水 |
| 各人に 0〜a_i 個を配る方法の数（上限つきの配り方） | [累積和・いもす法による DP の高速化](../dp/dp-prefix-sum.md) | 水 |
| 重さの合計が W 以下で価値の和の最大 | [ナップサック DP](../dp/knapsack-01.md) | 基礎 |
| 同じものを何度でも使える（硬貨・魔法） | [ナップサック DP](../dp/knapsack-01.md) | 基礎 |
| 各品物は B_i 個まで使える | [ナップサック DP](../dp/knapsack-01.md) | 基礎 |
| いくつか選んで和をちょうど S にできるか・その選び方の数 | [部分和 DP](../dp/subset-sum.md) | 基礎 |
| 2 つのグループに分けて差（遅い方）を最小にする | [部分和 DP](../dp/subset-sum.md) | 基礎 |
| 各要素に + か − を付けて和を K にする | [部分和 DP](../dp/subset-sum.md) | 基礎 |
| ペナルティが 2^(C−1) のように指数的に増える | [DP の状態の削減](../dp/dp-dimension-reduction.md) | 青 |
| 要素の追加と削除のクエリのたびに、和が K になる選び方の数を答える | [戻す DP](../dp/knapsack-undo.md) | 青 |
| 各 i について、i を使わないときの答え（〜を除いたとき） | [戻す DP](../dp/knapsack-undo.md) | 青 |
| 好きな順番で、いくつか選んで順に処理する | [並べ替えてから DP する](../dp/exchange-argument-dp.md) | 青 |
| 締切・積み重ね（上に載せられる重さ）がある | [並べ替えてから DP する](../dp/exchange-argument-dp.md) | 青 |
| 一次関数を好きな順に合成する | [並べ替えてから DP する](../dp/exchange-argument-dp.md) | 青 |
| 最後の 1 つだけ制限を超えてよい | [並べ替えてから DP する](../dp/exchange-argument-dp.md) | 青 |
| 右か下にしか動けない | [グリッド上の DP](../dp/dp-grid.md) | 水 |
| 経路の数・経路上で集める値の最大 | [グリッド上の DP](../dp/dp-grid.md) | 水 |
| 条件を満たす正方形の数・最大の正方形 | [グリッド上の DP](../dp/dp-grid.md) | 水 |
| 列をいくつかの連続部分に分ける方法の数 | [区間分割 DP](../dp/dp-sequence-partition.md) | 水 |
| 各区間のコストの和の最小 | [区間分割 DP](../dp/dp-sequence-partition.md) | 水 |
| 各区間が条件を満たすように区切れるか | [区間分割 DP](../dp/dp-sequence-partition.md) | 水 |
| 最小で何本の増加（減少）列に分けられるか・何色で塗れるか | [最長増加部分列](../dp/lis.md) | 水 |
| 抜いて差し込む操作の最小回数 | [最長増加部分列](../dp/lis.md) | 水 |
| 箱・円を入れ子にできる最大個数 | [最長増加部分列](../dp/lis.md) | 水 |
| 共通の部分列の最長・共通部分列の組の数 | [最長共通部分列と編集距離](../dp/lcs.md) | 水 |
| 挿入・削除・置換で一致させる最小回数 | [最長共通部分列と編集距離](../dp/lcs.md) | 水 |
| ある値（2 つの文字列の最長共通部分列の長さなど）がちょうど k になる文字列の数 | [最長共通部分列と編集距離](../dp/lcs.md) | 水 |
| 異なる部分列の個数 | [部分列 DP](../dp/subsequence-dp.md) | 黄 |
| 部分列として現れない最短の文字列（辞書順最小） | [部分列 DP](../dp/subsequence-dp.md) | 黄 |
| 辞書順で K 番目の部分列 | [部分列 DP](../dp/subsequence-dp.md) | 黄 |
| 隣り合うものを合体させる・消す操作のコストの最小 | [区間 DP](../dp/interval-dp.md) | 青 |
| 列の両端から交互に取っていく | [区間 DP](../dp/interval-dp.md) | 青 |
| 括弧の対応・回文 | [区間 DP](../dp/interval-dp.md) | 青 |
| 頂点を訪れた順（行きがけ順）が与えられたときの根付き木の数 | [区間 DP の応用](../dp/interval-dp-advanced.md) | 黄 |
| 区間を選び合うゲームの勝敗 | [区間 DP の応用](../dp/interval-dp-advanced.md) | 黄 |
| 数直線上を左右に動き、訪れた範囲が常に連続している | [区間 DP の応用](../dp/interval-dp-advanced.md) | 黄 |
| すべての地点を 1 回ずつ回って戻る最短の経路 | [bitDP](../dp/bit-dp.md) | 水 |
| 順番を決める・使ったものの集合が将来に効く | [bitDP](../dp/bit-dp.md) | 水 |
| N 個をいくつかのグループに分ける方法の数・最適値 | [部分集合を列挙する DP](../dp/subset-enumeration-dp.md) | 青 |
| 集合を部分集合の和に分割する | [部分集合を列挙する DP](../dp/subset-enumeration-dp.md) | 青 |
| タイル・ドミノの敷き詰め方の数 | [プロファイル DP](../dp/broken-profile-dp.md) | 黄 |
| 隣り合わないように置く・隣と異なる色で塗る方法の数 | [プロファイル DP](../dp/broken-profile-dp.md) | 黄 |
| 黒マスが連結になる塗り方 | [プロファイル DP](../dp/broken-profile-dp.md) | 黄 |
| N 以下で条件を満たす整数の個数・総和 | [桁 DP](../dp/digit-dp.md) | 水 |
| 各桁の和・0 でない桁の数 | [桁 DP](../dp/digit-dp.md) | 水 |
| K 以下の X について、XOR や AND の条件を満たすものを数える・最大化する | [桁 DP](../dp/digit-dp.md) | 水 |
| 2 つ以上の数を同時に決める（a + b = a xor b・3 つの数の xor） | [桁 DP の応用](../dp/digit-dp-advanced.md) | 黄 |
| 支払いとお釣りの枚数の最小 | [桁 DP の応用](../dp/digit-dp-advanced.md) | 黄 |
| 使った数字の種類数・指定の数字を全部含む数 | [桁 DP の応用](../dp/digit-dp-advanced.md) | 黄 |
| L ≤ x ≤ y ≤ R の組を数える（上限と下限の両方） | [桁 DP の応用](../dp/digit-dp-advanced.md) | 黄 |
| 木の各頂点を塗る・選ぶ（隣り合う頂点に条件がある） | [木 DP](../dp/tree-dp.md) | 水 |
| 木の辺を選ぶ（次数の上限つき） | [木 DP](../dp/tree-dp.md) | 水 |
| 部分木ごとの値（部分木の上位 K 個など） | [木 DP](../dp/tree-dp.md) | 水 |
| 木の各頂点からほかの全頂点への距離の総和 | [木 DP](../dp/tree-dp.md) | 水 |
| すべての頂点について、その頂点を根（起点）としたときの値 | [全方位木 DP](../dp/rerooting.md) | 青 |
| 各頂点から最も遠い頂点までの距離（頂点や辺の重みつき） | [全方位木 DP](../dp/rerooting.md) | 青 |
| 部分木から K 個選ぶ・連結成分の数ごとに数える | [二乗の木 DP](../dp/tree-dp-square.md) | 黄 |
| 順列で隣り合う大小関係（< と >）が指定される | [挿入 DP・箱根駅伝 DP](../dp/insertion-dp.md) | 黄 |
| \|p_i − i\| の和がちょうど K の順列の数 | [挿入 DP・箱根駅伝 DP](../dp/insertion-dp.md) | 黄 |
| 値の小さい順に、列の好きな位置へ挿入していく | [挿入 DP・箱根駅伝 DP](../dp/insertion-dp.md) | 黄 |
| 隣り合う要素の差が D 以下になるように選ぶ部分列の最長 | [セグメント木・スライド最小値による DP の高速化](../dp/dp-segment-tree.md) | 青 |
| DP をする列に 1 点更新のクエリが来て、そのたびに DP の答えを求める | [動的 DP](../dp/dynamic-dp.md) | 発展 |
| 列の区間 [l, r] だけで DP をしたときの答えを、クエリごとに求める | [動的 DP](../dp/dynamic-dp.md) | 発展 |
| 直線を追加しながら、任意の x での最小値・最大値を答える | [Convex Hull Trick と Li Chao Tree](../dp/cht.md) | 発展 |
| 区間から k 個選ぶときの最大値を、すべての k について求める | [Monge 性による DP の高速化](../dp/monge.md) | 発展 |
| ちょうど K 個選ぶ・K 個の区間に分ける（N, K ≤ 2×10^5） | [Alien DP](../dp/alien-dp.md) | 発展 |
| 隣り合わない k 個を選ぶ和の最大を、すべての k について答える | [Alien DP](../dp/alien-dp.md) | 発展 |
| 数列を単調（広義増加）にするための、値の変更量の和の最小 | [Slope Trick](../dp/slope-trick.md) | 発展 |
| 時刻ごとに位置を少しずつ動かせるときの最小コスト | [Slope Trick](../dp/slope-trick.md) | 発展 |
| 頂点の番号を付け替えて同じ形にできるか | [小さいグラフの全探索](../graph/small-graph-brute-force.md) | 基礎 |
| 隣り合う頂点が異なる色になる 3 色の塗り方の数 | [小さいグラフの全探索](../graph/small-graph-brute-force.md) | 基礎 |
| すべての組 (i, j)（i < j）について〜を足した和を求める | [Σ の変形](../math/sigma-manipulation.md) | 基礎 |
| 割り切る・割り切られる関係にある組を数える | [調和級数と倍数の列挙](../math/harmonic-sum.md) | 水 |
| 各 d について、d の倍数である要素の個数や和を求める | [調和級数と倍数の列挙](../math/harmonic-sum.md) | 水 |
| 操作を好きなだけ繰り返したとき、最後に残る値や作れる値を答える | [整数の証明の型](../math/proof-patterns.md) | 基礎 |
| 大きい方から小さい方を引く・余りに置き換える操作を繰り返す | [整数の証明の型](../math/proof-patterns.md) | 基礎 |
| 区間の幅が法 m 以上なら答えが決まる（余りは m 種類しかない） | [整数の証明の型](../math/proof-patterns.md) | 基礎 |
| 長さ N の文字列のうち、どのパターンも部分文字列に含まないものの数 | [照合オートマトン上の DP](../string/string-automaton-dp.md) | 青 |
| 与えられた文字列をすべて含む長さ L の文字列の数 | [照合オートマトン上の DP](../string/string-automaton-dp.md) | 青 |
| 問題文に「インタラクティブ」「質問は Q 回まで」とある | [インタラクティブ問題](../misc/interactive.md) | 基礎 |
| 質問の答えが入力として返ってくる・入出力例が対話の形 | [インタラクティブ問題](../misc/interactive.md) | 基礎 |

### 区間・列・データ構造 {#signs-phrase-sequence}

| 言い回し・求めるもの | ページ | レベル |
| --- | --- | --- |
| 区間の和を何度も聞かれる | [累積和](../basics/prefix-sum.md) | 基礎 |
| 1 つだけ除いた（変えた）ときの値 | [累積和](../basics/prefix-sum.md) | 基礎 |
| 円環上の区間 | [累積和](../basics/prefix-sum.md) | 基礎 |
| 和がちょうど K の区間の個数 | [累積和と連想配列で区間を数える](../basics/prefix-sum-counting.md) | 基礎 |
| 和が M の倍数になる区間の個数 | [累積和と連想配列で区間を数える](../basics/prefix-sum-counting.md) | 基礎 |
| 長方形領域の和・個数を何度も求める | [2 次元累積和](../basics/prefix-sum-2d.md) | 水 |
| 正方形・長方形を全部試す | [2 次元累積和](../basics/prefix-sum-2d.md) | 水 |
| 模様が周期的に敷き詰められた盤面 | [2 次元累積和](../basics/prefix-sum-2d.md) | 水 |
| 区間にまとめて加算し、最後に各点の値を知りたい | [いもす法](../basics/imos.md) | 基礎 |
| 各時刻に何人いるか・ちょうど k 個重なる長さ | [いもす法](../basics/imos.md) | 基礎 |
| 長方形にまとめて加算する（重なった枚数ごとの面積） | [いもす法](../basics/imos.md) | 基礎 |
| 区間に一律の値を足すたびに隣接差の和を答える | [いもす法](../basics/imos.md) | 基礎 |
| 等差数列になっている区間・区間に 1, 2, 3, … を足す | [いもす法](../basics/imos.md) | 基礎 |
| 区間に +1・−1 する操作の最小回数・可否 | [差分列への言い換え](../basics/difference-sequence.md) | 黄 |
| 数列を単調にする・回文にするための最小の操作回数 | [差分列への言い換え](../basics/difference-sequence.md) | 黄 |
| 円形に並んだ箱から一斉に取り除く操作で空にできるか | [差分列への言い換え](../basics/difference-sequence.md) | 黄 |
| 条件を満たす最長（最短）の連続区間・連続区間の個数 | [尺取り法](../basics/two-pointers.md) | 基礎 |
| 区間を縮めても（広げても）条件が保たれる | [尺取り法](../basics/two-pointers.md) | 基礎 |
| 長さ M の範囲に入るものの最大個数 | [尺取り法](../basics/two-pointers.md) | 基礎 |
| グループの併合と、グループ内の種類数・個数の問い合わせ | [マージテク](../tree/small-to-large.md) | 水 |
| 部分木ごとに集合（map）を持って併合する | [マージテク](../tree/small-to-large.md) | 水 |
| すべての部分木について、色の種類数・最頻値を求める | [マージテク](../tree/small-to-large.md) | 水 |
| 要素の追加・削除と、検索・最小値の取り出しのクエリが混ざる | [STL コンテナの使い分け](../ds/stl-containers.md) | 基礎 |
| x 以上で最小の値・最も近い値を、追加・削除しながら何度も答える | [set・multiset・map の応用](../ds/ordered-set.md) | 基礎 |
| まだ使われていない最小の値（mex）を更新のたびに答える | [set・multiset・map の応用](../ds/ordered-set.md) | 基礎 |
| 同じ行・同じ列で次にある壁や家を見つけて壊す | [set・multiset・map の応用](../ds/ordered-set.md) | 基礎 |
| 毎回いちばん大きい（小さい）ものを取り出し、新しい候補を入れる | [優先度付きキュー](../ds/priority-queue.md) | 水 |
| 接頭辞ごとに K 番目に大きい値を答える | [優先度付きキュー](../ds/priority-queue.md) | 水 |
| グループ間の移動のたびに、各グループの最大値のうちの最小値を答える | [優先度付きキュー](../ds/priority-queue.md) | 水 |
| 1 点を更新するたびに、大きい方から K 個の和を答える | [上位 K 個の和と中央値の管理](../ds/top-k-multiset.md) | 水 |
| 幅 M の窓をずらしながら、小さい方から K 個の和を答える | [上位 K 個の和と中央値の管理](../ds/top-k-multiset.md) | 水 |
| 数を追加しながら中央値（\|x − a_i\| の和を最小にする x）を答える | [上位 K 個の和と中央値の管理](../ds/top-k-multiset.md) | 水 |
| 区間を塗るたびに、塗られたマスの数や色ごとのマスの数を答える | [区間を set で管理する](../ds/interval-set.md) | 水 |
| 同じ色でつながった区間をまとめて塗り替える | [区間を set で管理する](../ds/interval-set.md) | 水 |
| 点 x が覆われているか・x を含む区間はどこか | [区間を set で管理する](../ds/interval-set.md) | 水 |
| 全要素に x を足す・全体に代入する操作がクエリに混ざる | [全体への操作を変数で持つ](../ds/global-offset.md) | 基礎 |
| 列全体を反転してから先頭・末尾に追加する | [全体への操作を変数で持つ](../ds/global-offset.md) | 基礎 |
| 配列を回転してから i 番目を参照する | [全体への操作を変数で持つ](../ds/global-offset.md) | 基礎 |
| 値 x の直後に y を挿入・値 x を削除する操作を繰り返し、最後の列を出力する | [配列で作る連結リスト](../ds/linked-list.md) | 基礎 |
| カードの山を別のカードの上へ付け替える | [配列で作る連結リスト](../ds/linked-list.md) | 基礎 |
| 列車の連結・切り離し | [配列で作る連結リスト](../ds/linked-list.md) | 基礎 |
| 括弧の対応を取る・対応する括弧ごと消す | [スタック・キュー・deque の使いどころ](../ds/stack-techniques.md) | 基礎 |
| 特定の並びが現れたら取り除く操作を繰り返した結果 | [スタック・キュー・deque の使いどころ](../ds/stack-techniques.md) | 基礎 |
| 直前の操作を取り消す（Undo） | [スタック・キュー・deque の使いどころ](../ds/stack-techniques.md) | 基礎 |
| 円周上の弦どうしが交差するか | [スタック・キュー・deque の使いどころ](../ds/stack-techniques.md) | 基礎 |
| 左（右）で初めて自分より大きい（小さい）要素の位置 | [単調スタックとスライド最小値](../ds/monotonic-stack.md) | 水 |
| 各ビルから見えるビルの数・すべての区間の最小値の和 | [単調スタックとスライド最小値](../ds/monotonic-stack.md) | 水 |
| 長さ K のすべての区間の最小値（最大値） | [単調スタックとスライド最小値](../ds/monotonic-stack.md) | 水 |
| 辺を追加していきながら、2 頂点が同じグループか・グループの大きさを答える | [Union-Find](../ds/union-find.md) | 基礎 |
| グループを合併する操作と、グループについての質問が交互に来る | [Union-Find](../ds/union-find.md) | 基礎 |
| 連結成分の個数・最大の連結成分の大きさ | [Union-Find](../ds/union-find.md) | 基礎 |
| 全頂点対について、パス上の最大の辺の重みの総和 | [Union-Find の応用](../ds/union-find-applications.md) | 水 |
| いくつかの区間の和が分かっているとき、全体の和が決まるか | [Union-Find の応用](../ds/union-find-applications.md) | 水 |
| 成分の中で K 番目に大きい番号・成分の中のクラス c の人数 | [Union-Find の応用](../ds/union-find-applications.md) | 水 |
| 右にある最初の空き位置に書き込む | [Union-Find の応用](../ds/union-find-applications.md) | 水 |
| x_R − x_L = D の形の情報が順に与えられ、矛盾しないかを判定する | [重み付き Union-Find](../ds/weighted-union-find.md) | 水 |
| 相対的な位置・差だけが分かっている | [重み付き Union-Find](../ds/weighted-union-find.md) | 水 |
| 正直者と嘘つき・2 色に塗り分けられるか | [重み付き Union-Find](../ds/weighted-union-find.md) | 水 |
| 最初の t 本の辺だけを使ったときに連結か・成分の大きさは | [部分永続 Union-Find](../ds/partially-persistent-union-find.md) | 発展 |
| x と y が初めて同じ集合になるのは何回目の操作か | [部分永続 Union-Find](../ds/partially-persistent-union-find.md) | 発展 |
| 木の根から各頂点へのパスごとに、パス上の要素どうしのつながりを答える | [ロールバックできる Union-Find](../ds/rollback-union-find.md) | 発展 |
| 辺の追加と削除が混ざり、そのたびに 2 頂点が連結かを答える | [ロールバックできる Union-Find](../ds/rollback-union-find.md) | 発展 |
| 一点の値の更新と区間の和の質問が交互に来る | [BIT（Fenwick Tree）](../ds/fenwick-tree.md) | 水 |
| i より前にある x 以下の要素の個数 | [BIT（Fenwick Tree）](../ds/fenwick-tree.md) | 水 |
| 隣り合う要素の交換でソートする最小回数・バブルソートの交換回数 | [転倒数](../ds/inversion-number.md) | 水 |
| i < j かつ A_i > A_j を満たす組の数 | [転倒数](../ds/inversion-number.md) | 水 |
| 巡回シフトや、全体に加算して mod を取った各列の転倒数 | [転倒数](../ds/inversion-number.md) | 水 |
| 数の追加・削除と、K 番目に小さい値の質問 | [K 番目の値を求めるデータ構造](../ds/kth-element.md) | 水 |
| 空いている場所のうち K 番目に置く・指定した位置への挿入を繰り返した最終的な列 | [K 番目の値を求めるデータ構造](../ds/kth-element.md) | 水 |
| x 以下の要素の個数（順位） | [K 番目の値を求めるデータ構造](../ds/kth-element.md) | 水 |
| 配列の値を書き換えながら、区間の最小値（最大値・gcd）を何度も答える | [セグメント木](../ds/segment-tree.md) | 水 |
| 1 文字の更新と、区間に現れる文字の種類数 | [セグメント木](../ds/segment-tree.md) | 水 |
| 位置 i 以降で初めて値が x 以上になる位置 | [セグメント木上の二分探索](../ds/segment-tree-binary-search.md) | 水 |
| 空いている場所のうち K 番目 | [セグメント木上の二分探索](../ds/segment-tree-binary-search.md) | 水 |
| 各 l について、条件を満たす最長の区間 | [セグメント木上の二分探索](../ds/segment-tree-binary-search.md) | 水 |
| 隣り合う要素の差が D 以下の部分列の最長 | [値を添字にする BIT・セグメント木](../ds/segment-tree-on-values.md) | 水 |
| 値を追加しながら、上位 K 個の和・ソートしたときの奇数番目の和を答える | [値を添字にする BIT・セグメント木](../ds/segment-tree-on-values.md) | 水 |
| 前の答えを使って次のクエリが復号され、先読みができない | [値を添字にする BIT・セグメント木](../ds/segment-tree-on-values.md) | 水 |
| 区間に一律に加算・代入・アフィン変換・反転し、区間の和・最小値・最大値を答える | [遅延セグメント木](../ds/lazy-segment-tree.md) | 水 |
| 区間に一律に加算・代入し、一点の値だけを答える | [遅延セグメント木](../ds/lazy-segment-tree.md) | 水 |
| 1 点の更新と、区間が正しい括弧列か・回文かの判定 | [セグメント木に何を載せるか](../ds/segment-tree-monoids.md) | 青 |
| 区間で 2 番目に大きい値（の個数） | [セグメント木に何を載せるか](../ds/segment-tree-monoids.md) | 青 |
| 区間の最大部分配列和・区間で最長の連続する 1 | [セグメント木に何を載せるか](../ds/segment-tree-monoids.md) | 青 |
| 区間をソートする操作を繰り返す | [遅延セグメント木の載せ方の型](../ds/lazy-segment-tree-patterns.md) | 青 |
| 2 つの数列への区間加算と、区間の Σ A_i B_i | [遅延セグメント木の載せ方の型](../ds/lazy-segment-tree-patterns.md) | 青 |
| 0/1 列の区間反転と、区間で 1 が連続する最大の長さ | [遅延セグメント木の載せ方の型](../ds/lazy-segment-tree-patterns.md) | 青 |
| 一列に並ぶ人を順に動かす総移動量 | [遅延セグメント木の載せ方の型](../ds/lazy-segment-tree-patterns.md) | 青 |
| 配列が変わらず、区間の最小値・最大値・gcd を非常に多く聞かれる | [Sparse Table](../ds/sparse-table.md) | 青 |
| 区間 chmin・chmax と区間和を同時に答える | [Segment Tree Beats](../ds/segment-tree-beats.md) | 発展 |
| 区間の各要素を x で割る（切り捨て）操作と区間和 | [Segment Tree Beats](../ds/segment-tree-beats.md) | 発展 |
| 区間 [l, r] に含まれる値の種類数を多数のクエリで答える | [クエリの先読み](../ds/offline-queries.md) | 水 |
| 重み w 以下の辺だけを使ったときの連結・X 以下の要素の和をクエリごとに答える | [クエリの先読み](../ds/offline-queries.md) | 水 |
| クエリどうしが独立で、順番を入れ替えても答えが変わらない | [クエリの先読み](../ds/offline-queries.md) | 水 |
| 長方形の中にある点の数・和を多数のクエリで答える | [平面走査](../ds/sweep-line-2d.md) | 青 |
| 区間 [p, q] に完全に含まれる区間の数 | [平面走査](../ds/sweep-line-2d.md) | 青 |
| 幅 W・高さ D の枠に入る点の最大数 | [平面走査](../ds/sweep-line-2d.md) | 青 |
| 静的な列で、区間ごとの同じ値の組の数・出現回数が条件を満たす値の種類数 | [Mo's algorithm](../ds/mo-algorithm.md) | 青 |
| 木のパス上の値の頻度を多数のクエリで答える | [Mo's algorithm](../ds/mo-algorithm.md) | 青 |
| 次数の合計が 2M・各色の個数の合計が N のように、合計だけが抑えられている | [平方分割](../ds/sqrt-decomposition.md) | 黄 |
| 位置 i から A_i ずつ先へ跳ぶ・配る | [平方分割](../ds/sqrt-decomposition.md) | 黄 |
| 区間加算と、区間内の x 以上の要素の個数 | [平方分割](../ds/sqrt-decomposition.md) | 黄 |
| 多数のクエリが、それぞれ何回目の操作で条件を満たすようになるかを問う | [並列二分探索](../ds/parallel-binary-search.md) | 発展 |
| 最初の t 回の操作の後に条件を満たす最小の t を、クエリごとに答える | [並列二分探索](../ds/parallel-binary-search.md) | 発展 |
| 3 つの値すべての大小関係を満たす組を数える | [CDQ 分割統治](../ds/cdq-divide-and-conquer.md) | 発展 |
| 点の追加と長方形の質問が混ざるが、オフラインでよい | [CDQ 分割統治](../ds/cdq-divide-and-conquer.md) | 発展 |
| 状態を保存し、あとで読み込んで続きの操作をする | [永続データ構造](../ds/persistent-data-structures.md) | 青 |
| 配列を丸ごとコピーする操作と、1 点更新・区間和が混ざる | [永続データ構造](../ds/persistent-data-structures.md) | 青 |
| 時刻 t の時点での区間の値の分布 | [永続データ構造](../ds/persistent-data-structures.md) | 青 |
| 区間内で X 以下の要素の個数・和を多数のクエリで答える | [マージソート木](../ds/merge-sort-tree.md) | 青 |
| 前の答えで次のクエリが決まる（オンライン強制） | [マージソート木](../ds/merge-sort-tree.md) | 青 |
| 区間の K 番目に小さい値をオンラインで答える | [Wavelet Matrix](../ds/wavelet-matrix.md) | 発展 |
| 長方形（添字の範囲 × 値の範囲）の中の点の数 | [Wavelet Matrix](../ds/wavelet-matrix.md) | 発展 |
| x を選んで XOR の最大値を最小にする・集合の中で x との XOR が最小の要素 | [Binary Trie](../ds/binary-trie.md) | 青 |
| 追加・削除のたびに、任意の 2 要素の XOR の最小値を答える | [Binary Trie](../ds/binary-trie.md) | 青 |
| 全体に XOR をかけてから K 番目に小さい値 | [Binary Trie](../ds/binary-trie.md) | 青 |
| 列の途中（位置で指定）への挿入・削除と、区間の反転 | [平衡二分探索木と pb_ds の tree](../ds/balanced-bst.md) | 発展 |
| K 番目の値と、値の順位の両方をオンラインで答える | [平衡二分探索木と pb_ds の tree](../ds/balanced-bst.md) | 発展 |

### グラフ・木 {#signs-phrase-graph}

| 言い回し・求めるもの | ページ | レベル |
| --- | --- | --- |
| グラフが N×N の 0/1 の表（隣接行列）で与えられる | [グラフの表現と用語](../graph/graph-basics.md) | 基礎 |
| すべての単純パス・経路を数える（答えが上限を超えたら打ち切ってよい） | [深さ優先探索（DFS）](../graph/dfs.md) | 基礎 |
| 依存関係をたどり、必要なものを先に済ませる順に出力する | [深さ優先探索（DFS）](../graph/dfs.md) | 基礎 |
| 最小の手数・回数を求める（1 回の移動のコストがすべて同じ） | [幅優先探索（BFS）と無重み最短路](../graph/bfs.md) | 基礎 |
| 一番近い〇〇までの距離・複数の場所から同時に広がる | [幅優先探索（BFS）と無重み最短路](../graph/bfs.md) | 基礎 |
| 最短路を 1 つ出力する・次に進む頂点を答える | [幅優先探索（BFS）と無重み最短路](../graph/bfs.md) | 基礎 |
| H×W のマス目を上下左右（8 方向）に移動する・壁や障害物がある | [グリッドグラフ](../graph/grid-graph.md) | 基礎 |
| H, W が巨大で、障害物の数だけが少ない | [グリッドグラフ](../graph/grid-graph.md) | 基礎 |
| つながっているか・グループの数・最大のグループの大きさ | [連結成分](../graph/connected-components.md) | 基礎 |
| 友達の友達は友達 | [連結成分](../graph/connected-components.md) | 基礎 |
| 点 (x, y) の集合で、同じ x・同じ y を持つ点どうしが関係する | [連結成分](../graph/connected-components.md) | 基礎 |
| 循環している・依存関係が回っている・矛盾があれば −1 | [閉路の検出と復元](../graph/cycle-detection.md) | 基礎 |
| 閉路を 1 つ見つけて出力せよ | [閉路の検出と復元](../graph/cycle-detection.md) | 基礎 |
| 2 つのグループに分ける・隣り合うものは異なる色 | [二部グラフ判定](../graph/bipartite-graph.md) | 基礎 |
| X_i と Y_i は異なる値、という条件が M 個ある | [二部グラフ判定](../graph/bipartite-graph.md) | 基礎 |
| 奇数長の閉路があるか | [二部グラフ判定](../graph/bipartite-graph.md) | 基礎 |
| 非負の重み付きグラフの最短距離・最小コスト（頂点にもコストがある） | [ダイクストラ法](../graph/dijkstra.md) | 基礎 |
| 頂点 k を経由する最短路をすべての k について・行きと帰り | [ダイクストラ法](../graph/dijkstra.md) | 基礎 |
| 負の辺の重みが「高さの差」の形をしている | [ダイクストラ法](../graph/dijkstra.md) | 基礎 |
| 壁を壊す回数・向きを変える回数・ワープの回数を最小化する | [01-BFS](../graph/zero-one-bfs.md) | 水 |
| 1 回の移動のコストが 0 か 1 | [01-BFS](../graph/zero-one-bfs.md) | 水 |
| 辺を 1 本ずつ追加（削除）するたびに、距離についての値を答える | [ワーシャルフロイド法](../graph/warshall-floyd.md) | 水 |
| 訪れる地点の順番を全部試す（地点間の距離が要る） | [ワーシャルフロイド法](../graph/warshall-floyd.md) | 水 |
| 負の重みの辺がある・得点を最大化する（符号を反転すると負辺になる） | [ベルマンフォード法](../graph/bellman-ford.md) | 青 |
| いくらでも大きくできるなら inf と出力する | [ベルマンフォード法](../graph/bellman-ford.md) | 青 |
| 最短路の本数を数える | [最短路 DAG](../graph/shortest-path-dag.md) | 水 |
| この辺を通らなくても最短距離は変わらないか・最短路に使われない辺 | [最短路 DAG](../graph/shortest-path-dag.md) | 水 |
| 始点からの最短距離を保ったまま辺を減らし、全域木を出力する | [最短路 DAG](../graph/shortest-path-dag.md) | 水 |
| K 回まで無料・スキップできる、手持ちのお金・燃料・体力がある | [状態を頂点にする](../graph/extended-dijkstra.md) | 水 |
| 向き・直前の移動・歩数の偶奇や mod で次の移動が変わる | [状態を頂点にする](../graph/extended-dijkstra.md) | 水 |
| 同じグループ（色・文字・集合）の中ならどこへでも移動できる | [状態を頂点にする](../graph/extended-dijkstra.md) | 水 |
| 盤面・配置を操作して目標の形にする最小回数・2 人（2 つの駒）が同時に動く | [状態を頂点にする](../graph/extended-dijkstra.md) | 水 |
| 決まった時刻にしか出発できない・待つことができる | [時刻で変わる辺の最短路](../graph/time-dependent-dijkstra.md) | 水 |
| 出発時刻によって所要時間が変わる | [時刻で変わる辺の最短路](../graph/time-dependent-dijkstra.md) | 水 |
| 終点に間に合う最も遅い出発時刻 | [時刻で変わる辺の最短路](../graph/time-dependent-dijkstra.md) | 水 |
| x_j − x_i ≤ c の形の条件の下で、ある変数を最大化（最小化）する | [差分制約（牛ゲー）](../graph/difference-constraints.md) | 青 |
| 区間の和が S 以上・以下という条件が並ぶ | [差分制約（牛ゲー）](../graph/difference-constraints.md) | 青 |
| 位置の差の情報が矛盾しないか | [差分制約（牛ゲー）](../graph/difference-constraints.md) | 青 |
| 完全グラフから M 本の辺を取り除いたグラフ・辺が「ない」組が与えられる | [補グラフ上の BFS](../graph/complement-graph-bfs.md) | 黄 |
| K の倍数のうち桁和などが最小のもの | [剰余を頂点にする最短路](../graph/modular-shortest-path.md) | 発展 |
| いくつかの数の和で作れる数の集合（硬貨の組合せ） | [剰余を頂点にする最短路](../graph/modular-shortest-path.md) | 発展 |
| 頂点から区間内の全頂点へ移動できる・区間から区間へ移動できる | [区間に辺を張る](../graph/segment-tree-graph.md) | 発展 |
| K 番目に短い経路・歩道の長さ | [K 番目の最短路](../graph/k-shortest-paths.md) | 発展 |
| a は b より前・依存関係・前提条件 | [トポロジカルソート](../graph/topological-sort.md) | 基礎 |
| 条件を満たす辞書順最小の順序・順序が一意か | [トポロジカルソート](../graph/topological-sort.md) | 基礎 |
| 矛盾（閉路）があれば −1 | [トポロジカルソート](../graph/topological-sort.md) | 基礎 |
| 互いに行き来できる頂点の組・グループ | [強連結成分分解（SCC）](../graph/scc.md) | 水 |
| 何度でもくり返せる（閉路の中にいる） | [強連結成分分解（SCC）](../graph/scc.md) | 水 |
| 各 i から A_i へ移動する | [Functional graph（出次数 1 のグラフ）](../graph/functional-graph.md) | 水 |
| 嫌いな相手・行き先が 1 人（1 つ）ずつ決まっている | [Functional graph（出次数 1 のグラフ）](../graph/functional-graph.md) | 水 |
| N 頂点 N 辺の連結グラフ・木に辺を 1 本足したグラフ | [なもりグラフ](../graph/namori-graph.md) | 水 |
| 2 頂点間の単純パスが一意か | [なもりグラフ](../graph/namori-graph.md) | 水 |
| 各要素が 2 択で「この 2 つは同時に選べない」「少なくともどちらか一方」 | [2-SAT](../graph/two-sat.md) | 発展 |
| 条件を満たす 2 択の割当があるか、あれば 1 つ出力する | [2-SAT](../graph/two-sat.md) | 発展 |
| 辺（頂点）を順に削除し、そのつど連結成分の数・大きさを答える（橋が崩落する・停電） | [Union-Find で連結性を扱う](../graph/union-find-connectivity.md) | 水 |
| 重さ・高さ・年などの制限を満たす辺だけで行けるかを多数答える | [Union-Find で連結性を扱う](../graph/union-find-connectivity.md) | 水 |
| 答えを決め打つと、つながっているかどうかで判定できる | [Union-Find で連結性を扱う](../graph/union-find-connectivity.md) | 水 |
| すべての頂点をつなぐ最小コスト | [最小全域木](../graph/minimum-spanning-tree.md) | 水 |
| 不要な辺を取り除いて報酬を最大にする | [最小全域木](../graph/minimum-spanning-tree.md) | 水 |
| この辺は最小全域木に入るか | [最小全域木](../graph/minimum-spanning-tree.md) | 水 |
| 経路上の最大の辺（最小の頂点）を最小化（最大化）する | [最小ボトルネック路](../graph/bottleneck-path.md) | 青 |
| 重さ・高さの制限以下で行けるか | [最小ボトルネック路](../graph/bottleneck-path.md) | 青 |
| しきい値を上げていくと連結になる時刻 | [最小ボトルネック路](../graph/bottleneck-path.md) | 青 |
| その辺（頂点）を取り除くと非連結になるか | [橋・関節点・二重連結成分](../graph/lowlink.md) | 黄 |
| すべての辺（頂点）について、取り除いたときの連結成分の数を求める | [橋・関節点・二重連結成分](../graph/lowlink.md) | 黄 |
| 辺の追加と削除のクエリが混ざり、そのつど連結性を答える（先に全部読んでよい） | [辺の追加と削除が混ざる連結性](../graph/offline-dynamic-connectivity.md) | 発展 |
| 各要素が「ない」時刻の区間がいくつかある | [辺の追加と削除が混ざる連結性](../graph/offline-dynamic-connectivity.md) | 発展 |
| 辺が暗黙に O(N^2) 本ある完全グラフの最小全域木 | [特殊な最小全域木](../graph/spanning-tree-advanced.md) | 発展 |
| マンハッタン距離の完全グラフ | [特殊な最小全域木](../graph/spanning-tree-advanced.md) | 発展 |
| 有向グラフで、根から全頂点へ届く最小コストの辺の集合 | [特殊な最小全域木](../graph/spanning-tree-advanced.md) | 発展 |
| 条件を満たすグラフ・経路・全域木を 1 つ出力せよ | [DFS 木・BFS 木とグラフの構築](../graph/graph-construction.md) | 青 |
| 訪問回数の偶奇が指定された経路を作る | [DFS 木・BFS 木とグラフの構築](../graph/graph-construction.md) | 青 |
| 全点対の距離表からグラフを復元できるか | [DFS 木・BFS 木とグラフの構築](../graph/graph-construction.md) | 青 |
| すべての辺をちょうど 1 回ずつ通る・一筆書き | [オイラー路（一筆書き）](../graph/euler-path.md) | 黄 |
| 同じ道を 2 度通らずにすべての道を通れるか | [オイラー路（一筆書き）](../graph/euler-path.md) | 黄 |
| 頂点とその隣接頂点すべてに対する操作・質問が大量に来る | [次数による平方分割](../graph/degree-sqrt.md) | 青 |
| 長さ 3・4 の閉路を見つける・数える | [次数による平方分割](../graph/degree-sqrt.md) | 青 |
| 同時に使えない資源を割り当てる・各行・各列に高々 1 つ | [最大流](../graph/max-flow.md) | 黄 |
| 辺（頂点）を共有しない経路の本数 | [最大流](../graph/max-flow.md) | 黄 |
| 容量・上限つきで送れる量の最大 | [最大流](../graph/max-flow.md) | 黄 |
| s と t を切り離す最小のコスト | [最小カット](../graph/min-cut.md) | 黄 |
| 頂点を消すコストの最小・どれを消したかも出力する | [最小カット](../graph/min-cut.md) | 黄 |
| 各要素を選ぶ・選ばないの 2 択で、利得とコストの合計を最大化する | [燃やす埋める](../graph/project-selection.md) | 黄 |
| A を選ぶなら B も選ぶ必要がある（依存関係） | [燃やす埋める](../graph/project-selection.md) | 黄 |
| 隣どうしが違う（同じ）とペナルティ・利得 | [燃やす埋める](../graph/project-selection.md) | 黄 |
| ペアを作る最大数・各人に 1 つずつ割り当てる | [二部マッチング](../graph/bipartite-matching.md) | 黄 |
| 答えを決め打つと、全員に割り当てられるかの判定になる | [二部マッチング](../graph/bipartite-matching.md) | 黄 |
| 和が素数・偶奇で 2 つのグループに分かれる | [二部マッチング](../graph/bipartite-matching.md) | 黄 |
| 衝突する（隣り合う）ものを同時に選ばずに最大数選ぶ | [König の定理](../graph/konig-theorem.md) | 黄 |
| すべての辺（マス）を監視するのに必要な最小数 | [König の定理](../graph/konig-theorem.md) | 黄 |
| 市松模様・偶奇で 2 つのグループに分かれる | [König の定理](../graph/konig-theorem.md) | 黄 |
| K 個選んだときの最大（最小）を K ごとに答える | [最小費用流](../graph/min-cost-flow.md) | 黄 |
| 重み付きの割当・各行・各列から高々 K 個 | [最小費用流](../graph/min-cost-flow.md) | 黄 |
| 流す量とコストの両方を最適化する | [最小費用流](../graph/min-cost-flow.md) | 黄 |
| 互いに包含しない（比べられない）ものを最大数選ぶ | [最小パス被覆と Hall の定理](../graph/dilworth-path-cover.md) | 発展 |
| 最少の本数のパス（鎖）で全頂点を覆う | [最小パス被覆と Hall の定理](../graph/dilworth-path-cover.md) | 発展 |
| この辺には少なくとも L だけ流す | [最小流量制約付きフロー](../graph/flow-lower-bounds.md) | 発展 |
| 必ず使う・使ってもよい・使ってはいけないものが混在する割当 | [最小流量制約付きフロー](../graph/flow-lower-bounds.md) | 発展 |
| 二部グラフでないグラフでペアを作る最大数 | [一般グラフのマッチング](../graph/general-matching.md) | 発展 |
| 辺を 1 本取り除く・1 本足す・閉路をなくして森にする | [木の基本性質と表現](../tree/tree-basics.md) | 基礎 |
| 森として残せる辺の数・消す辺の数 | [木の基本性質と表現](../tree/tree-basics.md) | 基礎 |
| 頂点 1 を根とする根付き木で、部分木の頂点数・和・最大を求める | [根付き木と走査順](../tree/tree-traversal.md) | 基礎 |
| 子孫・祖先・訪問順を答える | [根付き木と走査順](../tree/tree-traversal.md) | 基礎 |
| p_i < i（親の番号が自分より小さい）形で木が与えられる | [根付き木と走査順](../tree/tree-traversal.md) | 基礎 |
| 距離の偶奇・2 人が同時に動いて出会う場所 | [木の 2 色塗り分けと距離の偶奇](../tree/tree-bipartite.md) | 基礎 |
| 辺の重みの偶奇で頂点を塗り分ける | [木の 2 色塗り分けと距離の偶奇](../tree/tree-bipartite.md) | 基礎 |
| 独立集合を N/2 個以上選ぶ・二部グラフのまま辺を足す | [木の 2 色塗り分けと距離の偶奇](../tree/tree-bipartite.md) | 基礎 |
| 頂点 K を経由する最短距離 | [木の上の距離](../tree/tree-distance.md) | 基礎 |
| 2 人の追いかけっこ・どちらが先に着くか | [木の上の距離](../tree/tree-distance.md) | 基礎 |
| パス上の辺の重みの XOR | [木の上の距離](../tree/tree-distance.md) | 基礎 |
| 部分木の全頂点に x を加算するクエリがたくさん来て、最後に全頂点の値を出力する | [木の上の累積和・いもす法](../tree/tree-imos.md) | 基礎 |
| 辺のどちら側かの頂点すべてに加算する | [木の上の累積和・いもす法](../tree/tree-imos.md) | 基礎 |
| 多数のパスに沿って +1 し、各辺・各頂点を通った回数を求める | [木の上の累積和・いもす法](../tree/tree-imos.md) | 基礎 |
| 指定した K 頂点をすべて連結に保つのに必要な最小の頂点数・辺数 | [指定頂点を結ぶ最小の部分木](../tree/steiner-subtree.md) | 基礎 |
| 頂点 i と ⌊i/2⌋ を結ぶ・L/R/U の移動の列 | [完全二分木](../tree/complete-binary-tree.md) | 基礎 |
| 木を K 頂点ずつのパスに分ける | [葉から考える](../tree/leaf-first.md) | 水 |
| 辺をすべて使う・すべて覆う | [葉から考える](../tree/leaf-first.md) | 水 |
| 葉を消していく操作 | [葉から考える](../tree/leaf-first.md) | 水 |
| 各頂点の次数を決めて木を作る・次数の和が 2N−2 | [木の次数列と Prüfer 列](../tree/tree-degree.md) | 青 |
| 次数が○以下の木・星や雪の結晶など次数で決まる形 | [木の次数列と Prüfer 列](../tree/tree-degree.md) | 青 |
| 最も遠い 2 頂点・最長のパス | [木の直径と最遠点](../tree/tree-diameter.md) | 水 |
| 全頂点を訪れる最短の移動（戻らなくてよい） | [木の直径と最遠点](../tree/tree-diameter.md) | 水 |
| 各頂点から最も遠い頂点・2 つの木をつないだときの直径 | [木の直径と最遠点](../tree/tree-diameter.md) | 水 |
| K 個の頂点を選んで通る辺の総長を最大化する（K = 1, 2, … のすべてについて） | [木の直径と最遠点](../tree/tree-diameter.md) | 水 |
| ペアを作ってパスの長さの和を最大化する | [木の重心](../tree/tree-centroid.md) | 黄 |
| どの成分も半分以下になるように分ける | [木の重心](../tree/tree-centroid.md) | 黄 |
| すべての i < j について f(i, j) の総和 | [辺で切って数える](../tree/tree-edge-contribution.md) | 水 |
| 全ペアのパス上の最大値（最小値）の和 | [辺で切って数える](../tree/tree-edge-contribution.md) | 水 |
| 条件を満たす木を 1 つ出力せよ（なければ −1） | [木の構築・復元](../tree/tree-construction.md) | 水 |
| 距離の情報から木を復元できるか | [木の構築・復元](../tree/tree-construction.md) | 水 |
| 訪問順（DFS 順）から元の木が何通りあるか | [木の構築・復元](../tree/tree-construction.md) | 水 |
| 形が同じ部分木の種類数 | [木の同型判定と木のハッシュ](../tree/tree-isomorphism.md) | 発展 |
| 2 つの木が同じ形か（根あり・根なし） | [木の同型判定と木のハッシュ](../tree/tree-isomorphism.md) | 発展 |
| 木の 2 頂点の距離をクエリでたくさん聞かれる | [最小共通祖先（LCA）](../tree/lca.md) | 青 |
| ちょうど距離 K の頂点・K 個上の祖先 | [最小共通祖先（LCA）](../tree/lca.md) | 青 |
| u から v へのパス上の…・パスに含まれる辺 | [木の上のパスの判定と分解](../tree/tree-path.md) | 青 |
| 2 本のパスが交わるか・共通部分 | [木の上のパスの判定と分解](../tree/tree-path.md) | 青 |
| どちらの端点に近いか（パスの中点） | [木の上のパスの判定と分解](../tree/tree-path.md) | 青 |
| 根から頂点 v までのパス上の…を、すべての v について求める | [根からのパスを DFS で持ち回る](../tree/root-path-dfs.md) | 青 |
| 祖先の情報だけで決まる値 | [根からのパスを DFS で持ち回る](../tree/root-path-dfs.md) | 青 |
| 操作を元に戻す・保存した状態に戻る | [根からのパスを DFS で持ち回る](../tree/root-path-dfs.md) | 青 |
| 部分木の和・最大・個数を、更新を挟みながら聞かれる | [オイラーツアー](../tree/euler-tour.md) | 青 |
| 部分木に加算する・辺を取り除いたときの片側の和 | [オイラーツアー](../tree/euler-tour.md) | 青 |
| u が v の祖先か・v の子孫のうち深さ d のもの | [オイラーツアー](../tree/euler-tour.md) | 青 |
| 辺の重みの変更と 2 点間の距離のクエリ | [オイラーツアー](../tree/euler-tour.md) | 青 |
| パスへの一括更新とパスの取得が混ざる | [HL 分解](../tree/hld.md) | 発展 |
| パス上の最大値（逆元のない演算）を更新つきで答える | [HL 分解](../tree/hld.md) | 発展 |
| 部分木とパスの両方のクエリ | [HL 分解](../tree/hld.md) | 発展 |
| 頂点の値を更新するたびに、木全体についての最適値・数え上げの結果を答える | [Static Top Tree と木 DP の動的更新](../tree/static-top-tree.md) | 発展 |
| 辺の追加と削除をくり返す森でのパスのクエリ | [動的木](../tree/dynamic-tree.md) | 発展 |
| 根の付け替えがある | [動的木](../tree/dynamic-tree.md) | 発展 |
| 距離がちょうど K の頂点の組の個数 | [重心分解](../tree/centroid-decomposition.md) | 黄 |
| 全ペアのパスについての量で、辺ごとに分解できないもの | [重心分解](../tree/centroid-decomposition.md) | 黄 |
| ある頂点から距離 d 以内の頂点の集計クエリ | [重心分解](../tree/centroid-decomposition.md) | 黄 |
| 色ごと・クエリごとに少数の頂点だけが関わり、その頂点数の合計が N 程度 | [Auxiliary Tree](../tree/auxiliary-tree.md) | 発展 |
| クエリごとに指定された頂点をすべてつなぐのに必要な辺の数を答える | [Auxiliary Tree](../tree/auxiliary-tree.md) | 発展 |
| ある時点のグループについての問い合わせ（オフライン） | [併合過程の木](../tree/merge-process-tree.md) | 発展 |
| パス上の最大の辺の最小値（ボトルネック）をオンラインで多数答える | [併合過程の木](../tree/merge-process-tree.md) | 発展 |
| 辺を重みの順に足していく過程を後から問われる | [併合過程の木](../tree/merge-process-tree.md) | 発展 |
| 親を子より先に選ぶ制約つきで、順番による重み付きの和を最適化する | [比で親に併合する貪欲](../tree/tree-ratio-greedy.md) | 発展 |

### 整数・数え上げ・確率 {#signs-phrase-math}

| 言い回し・求めるもの | ページ | レベル |
| --- | --- | --- |
| XOR・AND・OR が問題文に出る | [bit 演算の基本と XOR の性質](../basics/bit-operations.md) | 基礎 |
| 自分以外の XOR・同じ値で打ち消す | [bit 演算の基本と XOR の性質](../basics/bit-operations.md) | 基礎 |
| 2 進表記の 1 の個数 | [bit 演算の基本と XOR の性質](../basics/bit-operations.md) | 基礎 |
| 全ペア・全区間の XOR の総和 | [bit ごとに独立に考える](../basics/bitwise-independence.md) | 水 |
| AND・OR・XOR の最大化・最小化 | [bit ごとに独立に考える](../basics/bitwise-independence.md) | 水 |
| x を選んで max(a_i xor x) を最小化する | [bit ごとに独立に考える](../basics/bitwise-independence.md) | 水 |
| a + b = a xor b（繰り上がりがない） | [bit ごとに独立に考える](../basics/bitwise-independence.md) | 水 |
| 全域木の個数を数える（mod p で答える） | [行列木定理](../graph/matrix-tree-theorem.md) | 発展 |
| 有向グラフのオイラー閉路の数 | [行列木定理](../graph/matrix-tree-theorem.md) | 発展 |
| x 以上で、m で割って r 余る最小の数 | [整数の割り算と余り](../math/integer-division.md) | 基礎 |
| [L, R] にある K の倍数の個数 | [整数の割り算と余り](../math/integer-division.md) | 基礎 |
| 一定の間隔で発車する・周期的に起こる出来事の、ある時刻以降で最初のもの | [整数の割り算と余り](../math/integer-division.md) | 基礎 |
| 引き算を含む式の値を、0 以上 m 未満の余りで出力する | [mod の計算の基本](../math/mod-arithmetic.md) | 基礎 |
| a^N を m で割った余り | [繰り返し二乗法](../math/mod-pow.md) | 基礎 |
| 結合法則を満たす同じ操作を非常に多く繰り返す | [繰り返し二乗法](../math/mod-pow.md) | 基礎 |
| 答えは有理数 P/Q になるので P × Q^(−1) mod 998244353 を出力する | [逆元と mod での割り算](../math/mod-inverse.md) | 基礎 |
| 平均・等比数列の和などを、割り算を含む式のまま mod で求める | [逆元と mod での割り算](../math/mod-inverse.md) | 基礎 |
| 法 M（素数とは限らない）が入力で与えられ、その余りで数え上げの答えを出力する | [modint](../math/modint.md) | 基礎 |
| a&#94;(b&#94;c) mod p のように、指数にさらに指数がある | [フェルマーの小定理と指数の mod](../math/exponent-mod.md) | 水 |
| 累乗の塔を mod で求める | [フェルマーの小定理と指数の mod](../math/exponent-mod.md) | 水 |
| 同じ数字列を K 回並べてできる数を mod で求める | [等比数列の和を mod で求める](../math/geometric-series-mod.md) | 基礎 |
| 法 M が入力で与えられ、素数とは限らない | [等比数列の和を mod で求める](../math/geometric-series-mod.md) | 基礎 |
| 数字列の部分文字列を整数とみて、P の倍数になるものを数える | [桁と mod](../math/digit-and-mod.md) | 水 |
| 桁を消したり並べ替えたりして K の倍数にする | [桁と mod](../math/digit-and-mod.md) | 水 |
| 2 つの数を文字列として連結した数についての条件 | [桁と mod](../math/digit-and-mod.md) | 水 |
| a × b = N となる組を調べる | [約数列挙と素数判定](../math/divisor-enum.md) | 基礎 |
| 答え（gcd・周期・個数）が N の約数のどれかになる | [約数列挙と素数判定](../math/divisor-enum.md) | 基礎 |
| X 以上の最小の素数 | [約数列挙と素数判定](../math/divisor-enum.md) | 基礎 |
| 素数ごとに独立に考えられる（積・割り切れる回数） | [素因数分解とルジャンドルの公式](../math/prime-factorization.md) | 基礎 |
| N! の末尾の 0 の個数、N! が K の倍数になる最小の N | [素因数分解とルジャンドルの公式](../math/prime-factorization.md) | 基礎 |
| 積が M になる数列の数 | [素因数分解とルジャンドルの公式](../math/prime-factorization.md) | 基礎 |
| p q³ ≤ N を満たす素数の組を数える | [エラトステネスの篩](../math/sieve-eratosthenes.md) | 基礎 |
| 区間 [l, r] の素数の個数を何度も答える | [エラトステネスの篩](../math/sieve-eratosthenes.md) | 基礎 |
| すべての組が互いに素か（pairwise coprime）を判定する | [最小素因数の篩と線形篩](../math/spf-sieve.md) | 基礎 |
| 各要素の素因数の個数（重複込み）を求める | [最小素因数の篩と線形篩](../math/spf-sieve.md) | 基礎 |
| N の約数ごとに〜を計算する・d \| N を満たす d を全部試す | [約数の個数の上界と高度合成数](../math/divisor-count-bound.md) | 水 |
| N 以下で約数の個数が最大の数・約数が多い数を探す | [約数の個数の上界と高度合成数](../math/divisor-count-bound.md) | 水 |
| 連続する区間の数をそれぞれ素因数分解する | [区間篩](../math/segmented-sieve.md) | 水 |
| 二項係数 C(N, K) の分子 N−K+1..N を素因数分解する | [区間篩](../math/segmented-sieve.md) | 水 |
| 区間の中の素数の累乗（lcm(1, …, n) が変わる位置）を数える | [区間篩](../math/segmented-sieve.md) | 水 |
| 積が平方数（立方数）になる組を数える | [素因数の指数で考える](../math/prime-exponent-vector.md) | 基礎 |
| 多数の数の lcm を mod で求める | [素因数の指数で考える](../math/prime-exponent-vector.md) | 基礎 |
| 2 で割り切れる回数・各素数の指数をそろえる | [素因数の指数で考える](../math/prime-exponent-vector.md) | 基礎 |
| 素因数が P 以下の数（P-smooth 数）を数える | [素因数の指数で考える](../math/prime-exponent-vector.md) | 基礎 |
| n と互いに素な 1..n の数の個数・既約分数の個数 | [オイラーの φ 関数](../math/euler-phi.md) | 黄 |
| 位数が d になる元の個数 | [オイラーの φ 関数](../math/euler-phi.md) | 黄 |
| a^k ≡ 1 (mod n) となる最小の k を探す | [オイラーの φ 関数](../math/euler-phi.md) | 黄 |
| 非常に大きい数が素数かを多数判定する | [大きな数の素数判定と素因数分解](../math/miller-rabin.md) | 発展 |
| 全員が同時に・周期がそろう最初の時刻（lcm） | [GCD・LCM とユークリッドの互除法](../math/gcd-lcm.md) | 基礎 |
| 等間隔に移動してすべての点を訪れられる最大の幅（gcd） | [GCD・LCM とユークリッドの互除法](../math/gcd-lcm.md) | 基礎 |
| 1 つだけ書き換え（取り除い）たときの gcd の最大 | [GCD・LCM とユークリッドの互除法](../math/gcd-lcm.md) | 基礎 |
| 分数や傾きが等しいものを同じものとして数える | [GCD・LCM とユークリッドの互除法](../math/gcd-lcm.md) | 基礎 |
| ax + by = c を満たす整数の組 | [拡張ユークリッドの互除法と一次合同式](../math/ext-gcd.md) | 水 |
| 円周上を K ずつ進んで、何回目で初めて特定の位置に着くか | [拡張ユークリッドの互除法と一次合同式](../math/ext-gcd.md) | 水 |
| A の倍数を足して、B で割った余りを C にできるか | [拡張ユークリッドの互除法と一次合同式](../math/ext-gcd.md) | 水 |
| 法 M が素数とは限らない一次方程式 a x ≡ b (mod M) | [拡張ユークリッドの互除法と一次合同式](../math/ext-gcd.md) | 水 |
| A_i + B_j の矩形・全体に x を足したときの gcd | [GCD の性質](../math/gcd-properties.md) | 青 |
| 区間の gcd を多数答える | [GCD の性質](../math/gcd-properties.md) | 青 |
| mod N で A ずつ進む操作で全ての点に行けるか | [GCD の性質](../math/gcd-properties.md) | 青 |
| 周期の違う複数の条件が同時に成り立つ最初の時刻 | [中国剰余定理](../math/crt.md) | 青 |
| x を m_i で割った余り r_i が複数与えられる | [中国剰余定理](../math/crt.md) | 青 |
| 法が素数でない数え上げを素因数ごとに分けて最後に戻す | [中国剰余定理](../math/crt.md) | 青 |
| 同じ数字を n 個並べた数が K の倍数になる最小の n | [位数・原始根・離散対数](../math/multiplicative-order.md) | 黄 |
| a^x ≡ b (mod P) となる最小の x | [位数・原始根・離散対数](../math/multiplicative-order.md) | 黄 |
| X ← AX + B (mod P) を繰り返して G が最初に現れる番号 | [位数・原始根・離散対数](../math/multiplicative-order.md) | 黄 |
| x^n ≡ y (mod P) となる組を数える | [位数・原始根・離散対数](../math/multiplicative-order.md) | 黄 |
| mod P での積の値ごとに個数を数える | [位数・原始根・離散対数](../math/multiplicative-order.md) | 黄 |
| a^b（b ≥ 2）の形で表せる N 以下の数 | [整数の平方根・K 乗根と累乗数](../math/integer-root.md) | 基礎 |
| 2^a × b² のように累乗を組み合わせた数を数える | [整数の平方根・K 乗根と累乗数](../math/integer-root.md) | 基礎 |
| b 進法・−2 進法で表す | [N 進法](../math/base-conversion.md) | 基礎 |
| a, b, …, z, aa, ab, … と続く名前の n 番目 | [N 進法](../math/base-conversion.md) | 基礎 |
| 文字列を n 進数とみた値が M 以下になる n を数える | [N 進法](../math/base-conversion.md) | 基礎 |
| Σ_{i=1}^{N} ⌊N/i⌋ を求める | [商の列挙](../math/floor-quotient-enum.md) | 水 |
| xy ≤ N となる組を数える | [商の列挙](../math/floor-quotient-enum.md) | 水 |
| N 以下の素数の個数・素数の和 | [乗法的関数の和と素数の個数](../math/multiplicative-function.md) | 発展 |
| Σ ⌊(ai + b)/m⌋ や Σ (ai + b) mod m を求める | [floor sum](../math/floor-sum.md) | 黄 |
| (Ak + B) mod M が条件を満たす k の個数 | [floor sum](../math/floor-sum.md) | 黄 |
| 直線の下にある格子点の数 | [floor sum](../math/floor-sum.md) | 黄 |
| 分母・分子が N 以下で、与えられた実数に最も近い分数 | [Stern-Brocot 木と連分数](../math/stern-brocot.md) | 発展 |
| 分数の範囲を二分探索する | [Stern-Brocot 木と連分数](../math/stern-brocot.md) | 発展 |
| 漸化式の第 N 項（N ≤ 10^18） | [行列累乗](../math/matrix-power.md) | 青 |
| グラフでちょうど K 歩の経路の数・K 本の辺を使う最短路 | [行列累乗](../math/matrix-power.md) | 青 |
| 長さ 10^18 の文字列のうち、禁止された部分文字列を含まないものの数 | [行列累乗](../math/matrix-power.md) | 青 |
| 幅の小さい盤を長く伸ばしたときの敷き詰め方の数 | [行列累乗](../math/matrix-power.md) | 青 |
| スイッチを押すと複数のランプが反転する・偶奇の条件が N 個ある | [掃き出し法](../math/gaussian-elimination.md) | 青 |
| 条件を満たす押し方の数を mod で答える | [掃き出し法](../math/gaussian-elimination.md) | 青 |
| 各頂点に書いた値の、隣接する頂点の XOR が 0 になるように決める | [掃き出し法](../math/gaussian-elimination.md) | 青 |
| 部分集合（部分列）の XOR として作れる値の個数・最大値・K 番目 | [XOR 基底](../math/xor-basis.md) | 黄 |
| 全ての値を XOR で作れるように最小コストで選ぶ | [XOR 基底](../math/xor-basis.md) | 黄 |
| 経路の重みが辺の重みの XOR で、同じ辺を何度通ってもよい（ウォーク） | [XOR 基底](../math/xor-basis.md) | 黄 |
| 行列式を mod p で求める | [行列式](../math/determinant.md) | 発展 |
| 全域木の個数・交わらない経路の組の数 | [行列式](../math/determinant.md) | 発展 |
| 全ての k について、和が k になる組の数を求める | [畳み込みの使い方](../math/convolution-ntt.md) | 青 |
| 列をずらしたときの一致数・不一致の数を、全てのずらし方について求める | [畳み込みの使い方](../math/convolution-ntt.md) | 青 |
| ワイルドカード（?）を含むパターンの照合 | [畳み込みの使い方](../math/convolution-ntt.md) | 青 |
| mod 10^9+7 や整数のままで畳み込みたい | [FFT・NTT の仕組みと任意 mod の畳み込み](../math/fft-ntt.md) | 発展 |
| 畳み込みを自作ライブラリで実装したい・浮動小数の FFT の誤差が心配 | [FFT・NTT の仕組みと任意 mod の畳み込み](../math/fft-ntt.md) | 発展 |
| i XOR j = k となる組を全ての k について数える | [XOR 畳み込み](../math/hadamard-transform.md) | 発展 |
| XOR が 0 でない Nim の盤面の数を数える | [XOR 畳み込み](../math/hadamard-transform.md) | 発展 |
| Π(1 + a_i x) のような多数の一次式の積の係数 | [分割統治 FFT・オンライン畳み込み](../math/online-convolution.md) | 発展 |
| (1 + x^v) を掛ける・割るように、集合への追加と削除を繰り返して個数の分布を求める | [形式的冪級数と多項式の演算](../math/fps-basics.md) | 発展 |
| 次数の条件つきの木や個数の分布を、多項式の累乗の係数として数える | [形式的冪級数と多項式の演算](../math/fps-basics.md) | 発展 |
| 有理式 P(x)/Q(x) の N 次の係数 | [線形漸化式の高速化](../math/linear-recurrence-fast.md) | 発展 |
| 答えが線形漸化式を満たしそうだが式が分からない（最初の項から推定する） | [線形漸化式の高速化](../math/linear-recurrence-fast.md) | 発展 |
| 答えが N の多項式になる（小さい N で実験すると分かる） | [ラグランジュ補間とべき乗和](../math/lagrange-interpolation.md) | 発展 |
| Σ_{i=1}^{N} i^k を N ≤ 10^18 で求める | [ラグランジュ補間とべき乗和](../math/lagrange-interpolation.md) | 発展 |
| mod p で p 点の値から多項式の係数を復元する | [ラグランジュ補間とべき乗和](../math/lagrange-interpolation.md) | 発展 |
| 隣り合うもの（距離 2 以内のもの）が異なるように塗り分ける方法の数 | [和・積の法則と順列・組合せ](../comb/counting-basics.md) | 基礎 |
| 円形に並べる・円環で最後と最初も隣り合う | [和・積の法則と順列・組合せ](../comb/counting-basics.md) | 基礎 |
| N 個から K 個を選ぶ方法の数 | [二項係数の意味と性質](../comb/binomial-coefficient.md) | 基礎 |
| 0 と 1 の列で 1 がちょうど K 個のもの | [二項係数の意味と性質](../comb/binomial-coefficient.md) | 基礎 |
| 辞書順で K 番目の並べ方・与えられた並べ方が何番目か | [二項係数の意味と性質](../comb/binomial-coefficient.md) | 基礎 |
| 法 M が入力で与えられ、素数とは限らない | [二項係数の前計算](../comb/binomial-precompute.md) | 基礎 |
| 隣り合う 2 つから新しい値を作る操作を繰り返し、最後に残る値を求める（三角形・ピラミッド） | [二項係数の前計算](../comb/binomial-precompute.md) | 基礎 |
| 答えを mod 2・mod 3 など小さい素数で求める | [二項係数の前計算](../comb/binomial-precompute.md) | 基礎 |
| 和が N になる非負（正）整数の組の個数 | [重複組合せ](../comb/stars-and-bars.md) | 基礎 |
| 広義単調増加な列の個数 | [重複組合せ](../comb/stars-and-bars.md) | 基礎 |
| N 個から隣り合わない（間隔 d 以上の）K 個を選ぶ方法の数 | [重複組合せ](../comb/stars-and-bars.md) | 基礎 |
| 区別のない玉を区別のある箱へ配る方法の数 | [重複組合せ](../comb/stars-and-bars.md) | 基礎 |
| グリッドの左上から右下への最短路の数 | [格子路の数え上げ](../comb/lattice-paths.md) | 基礎 |
| 通れない長方形の領域がある経路の数 | [格子路の数え上げ](../comb/lattice-paths.md) | 基礎 |
| 2 種類の移動を組み合わせて目的地へ行く方法の数 | [格子路の数え上げ](../comb/lattice-paths.md) | 基礎 |
| 最大値（最小値）がちょうど K になるものの個数 | [数え上げの考え方](../comb/counting-mindset.md) | 水 |
| すべての選び方についての〜の総和 | [数え上げの考え方](../comb/counting-mindset.md) | 水 |
| 単調な数列の個数 | [対応づけ・数える対象の言い換え](../comb/counting-bijection.md) | 青 |
| 積（和）が決まった値になる数列の個数 | [対応づけ・数える対象の言い換え](../comb/counting-bijection.md) | 青 |
| 途中で負にならない ±1 の列の個数 | [対応づけ・数える対象の言い換え](../comb/counting-bijection.md) | 青 |
| A は B より先に来る、という順番の制約がある並べ方の数 | [順序を固定して数える](../comb/counting-fix-order.md) | 水 |
| 選んだ K 個の最大値（最小値）の総和 | [順序を固定して数える](../comb/counting-fix-order.md) | 水 |
| 木の頂点に、親が子より先になるように番号を振る方法の数 | [順序を固定して数える](../comb/counting-fix-order.md) | 水 |
| 異なる〜の個数（種類数） | [重複の除き方](../comb/counting-dedup.md) | 青 |
| 操作で作れる文字列（列）の種類数 | [重複の除き方](../comb/counting-dedup.md) | 青 |
| S を部分列として含む文字列の個数 | [重複の除き方](../comb/counting-dedup.md) | 青 |
| 区別しないグループに分ける方法の数 | [重複の除き方](../comb/counting-dedup.md) | 青 |
| 回転（反転）して一致するものは同じとみなす | [Burnside の補題](../comb/burnside-lemma.md) | 発展 |
| 数珠・ネックレスの塗り方の数 | [Burnside の補題](../comb/burnside-lemma.md) | 発展 |
| 立方体の面の塗り方（書き込み方）の数 | [Burnside の補題](../comb/burnside-lemma.md) | 発展 |
| 文字を並べ替えてできる文字列の個数 | [多項係数](../comb/multinomial-coefficient.md) | 水 |
| 各種類を使う個数が決まっている並べ方 | [多項係数](../comb/multinomial-coefficient.md) | 水 |
| 大きさを指定してグループに分ける方法の数 | [多項係数](../comb/multinomial-coefficient.md) | 水 |
| 長方形領域の各点への経路数の総和 | [二項係数の恒等式と和の公式](../comb/binomial-identities.md) | 青 |
| 偶数個（奇数個）を選ぶ方法の数の和 | [二項係数の恒等式と和の公式](../comb/binomial-identities.md) | 青 |
| 全ペアの (A_i + A_j)^x の和 | [二項係数の恒等式と和の公式](../comb/binomial-identities.md) | 青 |
| どの接頭辞でも A の個数が B の個数（+K）以上 | [鏡像法とカタラン数](../comb/reflection-principle.md) | 黄 |
| 途中で負にならない ±1 の列の個数 | [鏡像法とカタラン数](../comb/reflection-principle.md) | 黄 |
| 正しい括弧列の個数 | [鏡像法とカタラン数](../comb/reflection-principle.md) | 黄 |
| 境界線を越えない経路の数 | [鏡像法とカタラン数](../comb/reflection-principle.md) | 黄 |
| K 本の経路が互いに交わらない組の個数 | [LGV 補題](../comb/lgv-lemma.md) | 発展 |
| 複数の駒が衝突せずに動く確率 | [LGV 補題](../comb/lgv-lemma.md) | 発展 |
| 各要素の選び方が独立で、個数（和）の合計に条件がある | [母関数の考え方](../comb/generating-function-counting.md) | 発展 |
| すべて異なる・A_i ≠ B_i となるものの個数 | [包除原理](../comb/inclusion-exclusion.md) | 青 |
| どの禁止条件も満たさないものの個数 | [包除原理](../comb/inclusion-exclusion.md) | 青 |
| 各色（各行・各列）を少なくとも 1 回使うものの個数 | [包除原理](../comb/inclusion-exclusion.md) | 青 |
| 禁止条件が列や木に沿って並ぶ数え上げ | [包除 DP](../comb/inclusion-exclusion-dp.md) | 黄 |
| \|P_i − i\| など、位置と値の差に制約がある順列の個数 | [包除 DP](../comb/inclusion-exclusion-dp.md) | 黄 |
| 隣り合う値が異なる数列の個数 | [包除 DP](../comb/inclusion-exclusion-dp.md) | 黄 |
| gcd の総和を求める | [約数包除](../comb/divisor-inclusion-exclusion.md) | 青 |
| gcd が 1 になる（互いに素な）組の個数 | [約数包除](../comb/divisor-inclusion-exclusion.md) | 青 |
| 最小周期が d の列（文字列）の個数 | [約数包除](../comb/divisor-inclusion-exclusion.md) | 青 |
| 各値 d について、d の倍数（約数）である要素の個数・和 | [約数・倍数のゼータ変換とメビウス変換](../comb/zeta-mobius-divisor.md) | 青 |
| Σ f(gcd(A_i, A_j)) や lcm の総和 | [約数・倍数のゼータ変換とメビウス変換](../comb/zeta-mobius-divisor.md) | 青 |
| gcd(i, j) = 1 となる組の個数・和 | [メビウス関数とメビウス反転](../comb/mobius-function.md) | 黄 |
| Σ gcd や Σ lcm を求める | [メビウス関数とメビウス反転](../comb/mobius-function.md) | 黄 |
| A_i OR A_j が K の部分集合になる組 | [部分集合の高速ゼータ変換とメビウス変換](../comb/zeta-mobius-subset.md) | 黄 |
| x ⊆ S となる x についての和を、すべての S で求める | [部分集合の高速ゼータ変換とメビウス変換](../comb/zeta-mobius-subset.md) | 黄 |
| 順列を任意の 2 要素の swap でソートする最小回数 | [置換の巡回分解](../comb/permutation-cycles.md) | 基礎 |
| i → P_i をたどる・置換を何回も繰り返す | [置換の巡回分解](../comb/permutation-cycles.md) | 基礎 |
| 元に戻るまでの回数 | [置換の巡回分解](../comb/permutation-cycles.md) | 基礎 |
| ちょうど K 回（10^100 回など）の swap の後にありうる列 | [置換の偶奇](../comb/permutation-parity.md) | 青 |
| 3 つの要素を巡回させる操作しかできない | [置換の偶奇](../comb/permutation-parity.md) | 青 |
| 2 つの列でそれぞれ 1 回ずつの swap を同時に行う | [置換の偶奇](../comb/permutation-parity.md) | 青 |
| 同じ値があるかどうかで答えが変わる | [置換の偶奇](../comb/permutation-parity.md) | 青 |
| 巡回（サイクル）の個数ごとの順列の数 | [第 1 種スターリング数](../comb/stirling-first.md) | 発展 |
| 左から見える（最大値を更新する）位置の個数ごとの順列の数 | [第 1 種スターリング数](../comb/stirling-first.md) | 発展 |
| 最小の swap 回数ごとの並びの数 | [第 1 種スターリング数](../comb/stirling-first.md) | 発展 |
| N 人を区別しない K 組に分ける（どの組も空でない）方法の数 | [第 2 種スターリング数とベル数](../comb/bell-number.md) | 青 |
| 和が N になる多重集合の個数 | [整数の分割と分割数](../comb/partition-number.md) | 黄 |
| 区別のない玉を区別のない箱へ配る方法の数 | [整数の分割と分割数](../comb/partition-number.md) | 黄 |
| 順列を巡回の長さの組ごとに分類して数える | [整数の分割と分割数](../comb/partition-number.md) | 黄 |
| 最長増加部分列と最長減少部分列の長さが指定された順列の個数 | [Young 図形とフック長公式](../comb/young-tableaux.md) | 発展 |
| 頂点にラベルのある木の個数 | [ラベル付き木の数え上げ](../comb/cayley-pruefer.md) | 黄 |
| 各頂点の次数を指定（制限）した木の個数 | [ラベル付き木の数え上げ](../comb/cayley-pruefer.md) | 黄 |
| すべての木（すべての次数列）についての総和 | [ラベル付き木の数え上げ](../comb/cayley-pruefer.md) | 黄 |
| 条件を満たす（連結な）グラフの個数 | [連結なグラフの数え上げ](../comb/counting-labeled-graphs.md) | 黄 |
| 辺の部分集合のうち、指定した頂点どうしが連結になるものの数 | [連結なグラフの数え上げ](../comb/counting-labeled-graphs.md) | 黄 |
| 最大の連結成分の大きさがちょうど L | [連結なグラフの数え上げ](../comb/counting-labeled-graphs.md) | 黄 |
| 確率を求めよ（絶対誤差・相対誤差 10^−6 まで許容） | [確率の基本](../comb/probability-basics.md) | 基礎 |
| サイコロ・コイン・カードを使う確率 | [確率の基本](../comb/probability-basics.md) | 基礎 |
| 最初に〜し、その結果に応じて〜するときの確率 | [確率の基本](../comb/probability-basics.md) | 基礎 |
| 成功するまで繰り返すときの回数の期待値 | [幾何分布とコンプリートガチャ](../comb/coupon-collector.md) | 基礎 |
| すべての種類を集める（全頂点を訪れる）までの回数の期待値 | [幾何分布とコンプリートガチャ](../comb/coupon-collector.md) | 基礎 |
| 〜が出るまでサイコロを振り続ける | [幾何分布とコンプリートガチャ](../comb/coupon-collector.md) | 基礎 |
| 期待値（確率）を mod 998244353 で出力せよ | [確率・期待値を mod 998244353 で答える](../comb/rational-mod.md) | 水 |
| 求める値は有理数で表せ、既約分数 P/Q について R × Q ≡ P となる R を出力する | [確率・期待値を mod 998244353 で答える](../comb/rational-mod.md) | 水 |
| 確率が p% で与えられる | [確率・期待値を mod 998244353 で答える](../comb/rational-mod.md) | 水 |
| 〜の個数（種類数）の期待値 | [期待値の線形性と指示確率変数](../comb/linearity-of-expectation.md) | 水 |
| 転倒数・連結成分の数などの期待値 | [期待値の線形性と指示確率変数](../comb/linearity-of-expectation.md) | 水 |
| ランダムな操作の後の値の総和の期待値 | [期待値の線形性と指示確率変数](../comb/linearity-of-expectation.md) | 水 |
| 全パターンについての和を求め、総数で割る | [期待値の線形性と指示確率変数](../comb/linearity-of-expectation.md) | 水 |
| 一様ランダムにシャッフルする | [対称性で確率を求める](../comb/probability-symmetry.md) | 水 |
| ランダムに 2 つを選んで入れ替える操作を K 回行う | [対称性で確率を求める](../comb/probability-symmetry.md) | 水 |
| 残りから一様ランダムに 1 つずつ選ぶ | [対称性で確率を求める](../comb/probability-symmetry.md) | 水 |
| ランダムな順列での順位・転倒の期待値 | [対称性で確率を求める](../comb/probability-symmetry.md) | 水 |
| K 回の操作の後に〜である確率 | [確率 DP](../comb/probability-dp.md) | 水 |
| どちらが先にゴールするかの確率 | [確率 DP](../comb/probability-dp.md) | 水 |
| 時刻 T に〜している確率 | [確率 DP](../comb/probability-dp.md) | 水 |
| N 回ランダムに上下左右へ動いた後の位置 | [確率 DP](../comb/probability-dp.md) | 水 |
| 〜になるまでの操作回数の期待値 | [期待値 DP](../comb/expected-value-dp.md) | 水 |
| 終わるまでにかかる費用の期待値 | [期待値 DP](../comb/expected-value-dp.md) | 水 |
| 出た目が〜なら振り直し・確率 p で何も起きない | [期待値 DP](../comb/expected-value-dp.md) | 水 |
| 最適に行動したときの期待値（勝率） | [最適戦略の期待値](../comb/optimal-strategy-expectation.md) | 黄 |
| 好きなタイミングでやめられる・最初からやり直せる | [最適戦略の期待値](../comb/optimal-strategy-expectation.md) | 黄 |
| どれを残すか（どれを選ぶか）を選びながら進む | [最適戦略の期待値](../comb/optimal-strategy-expectation.md) | 黄 |
| 振り出し（スタート）に戻るマスがある | [閉路のある期待値](../comb/expectation-linear-equations.md) | 青 |
| 円形に並んだ人が順番に〜する | [閉路のある期待値](../comb/expectation-linear-equations.md) | 青 |
| 無限に続く可能性がある | [閉路のある期待値](../comb/expectation-linear-equations.md) | 青 |
| 2 人が交互に繰り返し、決着がつくまで続ける | [閉路のある期待値](../comb/expectation-linear-equations.md) | 青 |
| 最大値（最小値・K 番目の値）の期待値 | [期待値と確率の変換](../comb/expectation-tail-sum.md) | 黄 |
| 〜がそろうまでに取り出す回数の期待値 | [期待値と確率の変換](../comb/expectation-tail-sum.md) | 黄 |
| 〜の二乗の期待値 | [二乗の期待値・分散](../comb/expectation-of-square.md) | 黄 |
| 分散を求める（最小化する） | [二乗の期待値・分散](../comb/expectation-of-square.md) | 黄 |
| スコアの二乗の期待値 | [二乗の期待値・分散](../comb/expectation-of-square.md) | 黄 |
| 実数を一様ランダムに選ぶ | [連続値の確率](../comb/continuous-probability.md) | 発展 |
| 円内（区間内）のランダムな点 | [連続値の確率](../comb/continuous-probability.md) | 発展 |
| 部分和として作れる値か（和の上限が 10&#94;5〜10&#94;6） | [bitset による高速化](../misc/bitset-speedup.md) | 青 |
| 2 頂点の共通の隣接頂点・三角形の数 | [bitset による高速化](../misc/bitset-speedup.md) | 青 |
| 偶奇（XOR）だけ分かればよい | [bitset による高速化](../misc/bitset-speedup.md) | 青 |
| u から v へ到達できるかのクエリが大量にある | [bitset による高速化](../misc/bitset-speedup.md) | 青 |

### 文字列・幾何・ゲーム・そのほか {#signs-phrase-other}

| 言い回し・求めるもの | ページ | レベル |
| --- | --- | --- |
| 同じ文字・値が続く部分 | [ランレングス圧縮](../basics/run-length-encoding.md) | 基礎 |
| 区間を反転して 1 の連続を最長にする | [ランレングス圧縮](../basics/run-length-encoding.md) | 基礎 |
| 操作で塊（境界）の数がいくつ減るか | [ランレングス圧縮](../basics/run-length-encoding.md) | 基礎 |
| ランレングス形式で与えられる入力 | [ランレングス圧縮](../basics/run-length-encoding.md) | 基礎 |
| 区別しない箱（グループ）に分ける方法の数 | [写像 12 相](../comb/twelvefold-way.md)（準備中） | — |
| 玉（人・数）を箱（グループ・色）に配る方法の数 | [写像 12 相](../comb/twelvefold-way.md)（準備中） | — |
| どの箱にも 1 個以上入れる・空の箱を許す | [写像 12 相](../comb/twelvefold-way.md)（準備中） | — |
| 先手と後手が交互に操作し、両者が最適に行動したとき勝つのはどちらか | [ゲームの基本と勝敗の DP](../comb/game-basics.md) | 水 |
| First / Second（Takahashi / Aoki）を出力する | [ゲームの基本と勝敗の DP](../comb/game-basics.md) | 水 |
| 盤面（配置）が対称・同じものが偶数個ずつある | [ゲームの基本と勝敗の DP](../comb/game-basics.md) | 水 |
| 最終的な形が戦略によらず決まる | [ゲームの基本と勝敗の DP](../comb/game-basics.md) | 水 |
| ジャッジと対戦する（インタラクティブ） | [ゲームの基本と勝敗の DP](../comb/game-basics.md) | 水 |
| 両者が最適に行動したときの得点（の差） | [ミニマックス](../comb/minimax.md) | 水 |
| 太郎は X − Y を最大化し、次郎は最小化する | [ミニマックス](../comb/minimax.md) | 水 |
| 列の両端から交互に取る | [ミニマックス](../comb/minimax.md) | 水 |
| 交互に駒を進めて得点を取り合う | [ミニマックス](../comb/minimax.md) | 水 |
| いくつかの山から石を取り合い、最後に取った人が勝ち | [Nim と XOR](../comb/nim.md) | 水 |
| 1 回に取れる個数に上限（範囲）がある | [Nim と XOR](../comb/nim.md) | 水 |
| 先手が勝てるように最初の配置を変えられるか | [Nim と XOR](../comb/nim.md) | 水 |
| 複数の山（盤面）があり、どれか 1 つを選んで操作する | [Grundy 数と Sprague-Grundy の定理](../comb/grundy-number.md) | 青 |
| 先手と後手の取れる手が同じ | [Grundy 数と Sprague-Grundy の定理](../comb/grundy-number.md) | 青 |
| 無限に続く場合は Draw（引き分け）を出力する | [後退解析](../comb/game-retrograde-analysis.md) | 黄 |
| 同じ局面が繰り返し現れうる | [後退解析](../comb/game-retrograde-analysis.md) | 黄 |
| グラフ上でコマを動かすゲーム・しりとり | [後退解析](../comb/game-retrograde-analysis.md) | 黄 |
| 先手と後手で動かせる駒や手が違う | [非不偏ゲーム](../comb/partizan-games.md) | 発展 |
| 独立な部分の和で勝敗を判定したい | [非不偏ゲーム](../comb/partizan-games.md) | 発展 |
| 条件を満たす文字列のうち辞書順で最小（最大）のものを出力する | [文字列の基本操作と辞書順](../string/string-basics.md) | 基礎 |
| 2 種類の文字を一斉に入れ替える操作を繰り返して一致させられるか | [文字列の基本操作と辞書順](../string/string-basics.md) | 基礎 |
| 先頭の文字を末尾に移す（回転する）操作を何回か行う | [文字列の基本操作と辞書順](../string/string-basics.md) | 基礎 |
| T を部分列として含むか（連続でなくてよい） | [部分列の判定と次の出現位置の表](../string/subsequence-matching.md) | 基礎 |
| 長さ K の部分列のうち辞書順で最小のもの | [部分列の判定と次の出現位置の表](../string/subsequence-matching.md) | 基礎 |
| S の部分列として現れない最短の文字列 | [部分列の判定と次の出現位置の表](../string/subsequence-matching.md) | 基礎 |
| S を何回も繰り返した文字列の部分列として入るか | [部分列の判定と次の出現位置の表](../string/subsequence-matching.md) | 基礎 |
| 部分文字列どうしが等しいかを大量に判定する | [ローリングハッシュ](../string/rolling-hash.md) | 水 |
| 重ならずに 2 回現れる部分文字列の最大の長さ | [ローリングハッシュ](../string/rolling-hash.md) | 水 |
| 1 文字の更新と、区間が回文か（一致するか）のクエリ | [ローリングハッシュ](../string/rolling-hash.md) | 水 |
| 先頭 x 項の集合と先頭 y 項の集合が等しいか | [集合・多重集合のハッシュ](../string/hashing-for-sets.md) | 水 |
| 2 つの区間を並べ替えると一致するか（多重集合として等しいか） | [集合・多重集合のハッシュ](../string/hashing-for-sets.md) | 水 |
| 区間内の各値が偶数個（3 の倍数個）か・区間の積が平方数（立方数）か | [集合・多重集合のハッシュ](../string/hashing-for-sets.md) | 水 |
| ハッシュ値を set や map に大量に入れて重複を数える | [ハッシュの衝突と安全な設計](../string/hash-safety.md) | 青 |
| 1000 桁程度の巨大な数の積や和が一致するかを判定する | [ハッシュの衝突と安全な設計](../string/hash-safety.md) | 青 |
| 各位置から、文字列の先頭と何文字一致するか | [Z-algorithm](../string/z-algorithm.md) | 水 |
| A を何回回転すると B になるか（円環状の文字列の一致） | [Z-algorithm](../string/z-algorithm.md) | 水 |
| T を S の接頭辞の連結で表す最小の個数 | [Z-algorithm](../string/z-algorithm.md) | 水 |
| パターンの全出現位置 | [Z-algorithm](../string/z-algorithm.md) | 水 |
| 接頭辞と接尾辞が一致する最長の長さ | [KMP 法と文字列の周期](../string/kmp.md) | 青 |
| 最小周期・何かの繰り返しで書けるか | [KMP 法と文字列の周期](../string/kmp.md) | 青 |
| N の約数 M を周期に持つ文字列（表）を数える | [KMP 法と文字列の周期](../string/kmp.md) | 青 |
| 文字が 1 つずつ来るたびに、パターンが現れたかを判定する | [KMP 法と文字列の周期](../string/kmp.md) | 青 |
| 回文にするための最小の操作回数（書き換え・一斉置換） | [回文の扱いと Manacher](../string/palindrome.md) | 水 |
| 回文になる部分文字列の個数 | [回文の扱いと Manacher](../string/palindrome.md) | 水 |
| グラフの歩道の文字列が回文になる最短の長さ | [回文の扱いと Manacher](../string/palindrome.md) | 水 |
| 長さ K の回文を部分文字列に含まないように埋める方法の数 | [回文の扱いと Manacher](../string/palindrome.md) | 水 |
| 全ペアの最長共通接頭辞（LCP）の長さの和 | [Trie](../string/trie.md) | 水 |
| 各文字列について、ほかの文字列との LCP の最大 | [Trie](../string/trie.md) | 水 |
| ある文字列を接頭辞に持つ文字列の数（追加・削除あり） | [Trie](../string/trie.md) | 水 |
| 数列（文字列）の集合を辞書順にたどる | [Trie](../string/trie.md) | 水 |
| 多数のパターンそれぞれの、テキスト中の出現回数 | [Aho-Corasick 法](../string/aho-corasick.md) | 青 |
| どのパターンも含まない（すべて含む）文字列の数 | [Aho-Corasick 法](../string/aho-corasick.md) | 青 |
| 禁止語を含まないように最少の文字を書き換える | [Aho-Corasick 法](../string/aho-corasick.md) | 青 |
| 異なる部分文字列の個数 | [Suffix Array と LCP 配列](../string/suffix-array.md) | 黄 |
| 全接尾辞どうしの LCP の和 | [Suffix Array と LCP 配列](../string/suffix-array.md) | 黄 |
| 回転したものどうしの辞書順の大小を数える | [Suffix Array と LCP 配列](../string/suffix-array.md) | 黄 |
| 部分文字列を辞書順に並べたときの K 番目 | [Suffix Array と LCP 配列](../string/suffix-array.md) | 黄 |
| 文字を 1 つずつ追加しながら、異なる部分文字列の数を答える | [Suffix Automaton と発展の文字列アルゴリズム](../string/suffix-automaton.md) | 発展 |
| 2 つの文字列の最長共通部分文字列 | [Suffix Automaton と発展の文字列アルゴリズム](../string/suffix-automaton.md) | 発展 |
| 異なる回文の部分文字列の種類数と、それぞれの出現回数 | [Suffix Automaton と発展の文字列アルゴリズム](../string/suffix-automaton.md) | 発展 |
| 辞書順最小の巡回シフト | [Suffix Automaton と発展の文字列アルゴリズム](../string/suffix-automaton.md) | 発展 |
| Z 配列（回文半径）が与えられ、それを満たす文字列を作る | [Suffix Automaton と発展の文字列アルゴリズム](../string/suffix-automaton.md) | 発展 |
| 3 点が一直線上にあるか・三角形ができるか | [ベクトルと外積](../geometry/geometry-vectors.md) | 基礎 |
| 左に曲がるか右に曲がるか・四角形が凸か | [ベクトルと外積](../geometry/geometry-vectors.md) | 基礎 |
| 頂点が順に与えられた多角形の面積 | [ベクトルと外積](../geometry/geometry-vectors.md) | 基礎 |
| 2 本の線分が交わるか・多角形を線分で切って分かれる個数 | [ベクトルと外積](../geometry/geometry-vectors.md) | 基礎 |
| 直方体どうしの共通部分の体積 | [ベクトルと外積](../geometry/geometry-vectors.md) | 基礎 |
| 座標や値が小数第 k 位まで与えられる | [誤差の扱いと整数での処理](../geometry/geometry-precision.md) | 水 |
| ちょうど境界上か・整数になるかを判定する | [誤差の扱いと整数での処理](../geometry/geometry-precision.md) | 水 |
| K 点以上を通る直線の数・平行な辺の組（台形）の数 | [誤差の扱いと整数での処理](../geometry/geometry-precision.md) | 水 |
| 絶対誤差または相対誤差 10&#94;-6〜10&#94;-9 まで許される | [誤差の扱いと整数での処理](../geometry/geometry-precision.md) | 水 |
| 原点から見た方向の順に並べる | [偏角ソート](../geometry/argument-sort.md) | 水 |
| 回転する光線（レーザー）に当たる点の数 | [偏角ソート](../geometry/argument-sort.md) | 水 |
| ∠ABC の最大 | [偏角ソート](../geometry/argument-sort.md) | 水 |
| ベクトルをいくつか選んで和の長さを最大にする | [偏角ソート](../geometry/argument-sort.md) | 水 |
| 点を θ 度回転した位置 | [回転・平行移動・アフィン変換](../geometry/rotation-transform.md) | 水 |
| 回転・反転・平行移動の操作を順に行った後の位置のクエリ | [回転・平行移動・アフィン変換](../geometry/rotation-transform.md) | 水 |
| 回転と平行移動で 2 つの点集合が重なるか | [回転・平行移動・アフィン変換](../geometry/rotation-transform.md) | 水 |
| 盤面を 90 度回転して一致させる | [回転・平行移動・アフィン変換](../geometry/rotation-transform.md) | 水 |
| マンハッタン距離が最大の 2 点・ある点から最も遠い点 | [マンハッタン距離と 45 度回転](../geometry/manhattan-chebyshev.md) | 水 |
| マンハッタン距離の和の最小・全ペアの距離の総和 | [マンハッタン距離と 45 度回転](../geometry/manhattan-chebyshev.md) | 水 |
| 斜め移動（キングの移動）だけでの距離・斜めにしか動けない駒 | [マンハッタン距離と 45 度回転](../geometry/manhattan-chebyshev.md) | 水 |
| ひし形の範囲（\|x\|+\|y\| ≤ D）にある点の数 | [マンハッタン距離と 45 度回転](../geometry/manhattan-chebyshev.md) | 水 |
| 円周を伝って移動できるか・円どうしが交わるか | [円と幾何の最適化](../geometry/circle-geometry.md) | 青 |
| すべての点を含む最小の円 | [円と幾何の最適化](../geometry/circle-geometry.md) | 青 |
| 障害物を避けて通れる円の最大の半径 | [円と幾何の最適化](../geometry/circle-geometry.md) | 青 |
| 円の内部にある格子点の数 | [円と幾何の最適化](../geometry/circle-geometry.md) | 青 |
| すべての点を囲む最小の凸多角形 | [凸包と凸多角形](../geometry/convex-hull.md) | 黄 |
| 外側にある点だけが効く | [凸包と凸多角形](../geometry/convex-hull.md) | 黄 |
| 区間の平均・傾き・比の最大 | [凸包と凸多角形](../geometry/convex-hull.md) | 黄 |
| 多数の点が凸多角形の内部・境界・外部のどこにあるか | [凸包と凸多角形](../geometry/convex-hull.md) | 黄 |
| 多角形の内部にある格子点の数 | [凸包と凸多角形](../geometry/convex-hull.md) | 黄 |
| 最も遠い 2 点（凸包上の対蹠点） | [発展の幾何](../geometry/advanced-geometry.md) | 発展 |
| 最も近い 2 点（N ≤ 2×10^5） | [発展の幾何](../geometry/advanced-geometry.md) | 発展 |
| 点の追加と ax+by の最大のクエリ | [発展の幾何](../geometry/advanced-geometry.md) | 発展 |
| 2 つの凸な点集合の和の凸包 | [発展の幾何](../geometry/advanced-geometry.md) | 発展 |
| 半平面の共通部分 | [発展の幾何](../geometry/advanced-geometry.md) | 発展 |
| 半数を超える要素が条件を満たす（過半数） | [乱択アルゴリズム](../misc/randomized.md) | 青 |
| 数式の文字列が与えられ、値を求める | [構文解析](../misc/parsing.md) | 青 |
| \+ と \* と括弧の優先順位がある | [構文解析](../misc/parsing.md) | 青 |
| 式として正しい部分文字列 | [構文解析](../misc/parsing.md) | 青 |
| 入れ子の構造を持つ文字列 | [構文解析](../misc/parsing.md) | 青 |
| 和が K（K の倍数）になる連続部分列の個数 | [区間](../patterns/interval.md)（準備中） | — |
| すべての連続部分列についての最小値・最大値・2 番目の値の総和 | [区間](../patterns/interval.md)（準備中） | — |
| N 個の区間 [L_i, R_i] から重ならないように最大何個選べるか | [区間](../patterns/interval.md)（準備中） | — |
| 区間を塗るたびに、塗られていない長さや個数を答える | [区間](../patterns/interval.md)（準備中） | — |
| 区間に含まれる異なる値の個数を多数答える | [区間](../patterns/interval.md)（準備中） | — |
| T が S の部分列か判定する | [部分列と部分文字列](../patterns/subsequence-and-substring.md)（準備中） | — |
| S から何文字か選んで順に並べると T になる選び方の数 | [部分列と部分文字列](../patterns/subsequence-and-substring.md)（準備中） | — |
| S の部分列として現れる異なる文字列の個数 | [部分列と部分文字列](../patterns/subsequence-and-substring.md)（準備中） | — |
| S の部分文字列の種類数 | [部分列と部分文字列](../patterns/subsequence-and-substring.md)（準備中） | — |
| (1, 2, …, N) の順列 P が与えられる | [順列と置換](../patterns/permutation.md)（準備中） | — |
| 任意の 2 要素の swap を繰り返してソートする最小回数 | [順列と置換](../patterns/permutation.md)（準備中） | — |
| 隣り合う 2 要素の swap でソートする最小回数 | [順列と置換](../patterns/permutation.md)（準備中） | — |
| ちょうど K 回の swap（10^100 回など）で作れる列 | [順列と置換](../patterns/permutation.md)（準備中） | — |
| 置換を K 回（K ≤ 10^18）適用した結果 | [順列と置換](../patterns/permutation.md)（準備中） | — |
| 条件を満たす順列の個数 | [順列と置換](../patterns/permutation.md)（準備中） | — |
| '(' と ')' からなる文字列が正しい括弧列か判定する | [括弧列](../patterns/bracket-sequence.md) | — |
| ? を ( か ) に置き換えて正しい括弧列にする方法の数 | [括弧列](../patterns/bracket-sequence.md) | — |
| 文字の入れ替えのたびに、区間が正しい括弧列かを答える | [括弧列](../patterns/bracket-sequence.md) | — |
| 複数の括弧列を並べて連結し、正しい括弧列にできるか | [括弧列](../patterns/bracket-sequence.md) | — |
| 長さ 2N の正しい括弧列の個数 | [括弧列](../patterns/bracket-sequence.md) | — |
| 含まれない最小の非負整数（mex）を答える | [mex](../patterns/mex.md)（準備中） | — |
| 1 点を書き換えるたびに数列の mex を答える | [mex](../patterns/mex.md)（準備中） | — |
| 長さ M の全区間の mex の最小値 | [mex](../patterns/mex.md)（準備中） | — |
| 全区間・全パスの mex の総和 | [mex](../patterns/mex.md)（準備中） | — |
| K 番目に小さい（大きい）値を答える | [K 番目と中央値](../patterns/kth-and-median.md)（準備中） | — |
| N² 個の積・和・差の中で K 番目 | [K 番目と中央値](../patterns/kth-and-median.md)（準備中） | — |
| 値の追加・更新のたびに、大きい方から K 個の和を答える | [K 番目と中央値](../patterns/kth-and-median.md)（準備中） | — |
| 中央値の最大値・最小値 | [K 番目と中央値](../patterns/kth-and-median.md)（準備中） | — |
| Σ\|x − a_i\| を最小にする x | [K 番目と中央値](../patterns/kth-and-median.md)（準備中） | — |
| 辞書順で K 番目のもの | [K 番目と中央値](../patterns/kth-and-median.md)（準備中） | — |
| すべての組・すべての区間の XOR の総和 | [XOR](../patterns/xor.md)（準備中） | — |
| x を選んで XOR の最大値・最小値を求める | [XOR](../patterns/xor.md)（準備中） | — |
| いくつか選んだ XOR で作れる値・作れる値の個数・K 番目 | [XOR](../patterns/xor.md)（準備中） | — |
| 区間の XOR・木のパスの XOR・経路の XOR | [XOR](../patterns/xor.md)（準備中） | — |
| 石を取り合うゲームで、山の石の数の XOR | [XOR](../patterns/xor.md)（準備中） | — |
| 1 以上 N 以下のすべての整数について、約数や倍数に関する値の総和を求める | [約数と倍数](../patterns/divisors-and-multiples.md)（準備中） | — |
| gcd がちょうど g になる組・部分集合の個数 | [約数と倍数](../patterns/divisors-and-multiples.md)（準備中） | — |
| 積がちょうど N になる列の個数 | [約数と倍数](../patterns/divisors-and-multiples.md)（準備中） | — |
| 積が平方数になる組の個数 | [約数と倍数](../patterns/divisors-and-multiples.md)（準備中） | — |
| H×W のマス目で、スタートからゴールへの最小の移動回数 | [グリッド](../patterns/grid.md)（準備中） | — |
| 右か下にだけ進む経路の数・経路上の値の最大 | [グリッド](../patterns/grid.md)（準備中） | — |
| 長方形の範囲の和・黒マスの個数を多数答える | [グリッド](../patterns/grid.md)（準備中） | — |
| 1×2 のタイル（ドミノ）を敷き詰める・置く | [グリッド](../patterns/grid.md)（準備中） | — |
| 盤面を 90 度回転・反転させて一致させる | [グリッド](../patterns/grid.md)（準備中） | — |
| 斜めに動く駒・マンハッタン距離・ひし形の範囲 | [グリッド](../patterns/grid.md)（準備中） | — |
| 辺や頂点を 1 つずつ削除するたびに、連結成分の数を答える | [操作列とクエリ](../patterns/operation-sequence.md)（準備中） | — |
| 全体に加算する・全体を反転する操作が混ざる | [操作列とクエリ](../patterns/operation-sequence.md)（準備中） | — |
| 過去の状態に戻す・ある時点の状態をコピーする | [操作列とクエリ](../patterns/operation-sequence.md)（準備中） | — |
| 行や列・区間を塗り替える操作の後の最終状態 | [操作列とクエリ](../patterns/operation-sequence.md)（準備中） | — |
| 同じ操作を 10^18 回繰り返した後の状態 | [操作列とクエリ](../patterns/operation-sequence.md)（準備中） | — |
| 答えの絶対誤差または相対誤差が 10^-6 以下なら正解とする（小数の桁を指定して出力しないと WA になる） | [入出力と定数倍](../cpp/cpp-io.md) | 基礎 |

<!-- textlint-enable -->
<!-- gen:end signs-phrase -->

<!-- gen:begin signs-shape -->
<!-- textlint-disable -->

| 立てた式・遷移の形 | ページ | レベル |
| --- | --- | --- |
| while の中に for があって入れ子に見えるが、各要素は一度しか動かない | [計算量の見積もり](../basics/complexity-estimation.md) | 基礎 |
| 答えを X に固定すると、可否を貪欲・探索・DP で判定できる形になる | [答えで二分探索](../basics/binary-search-answer.md) | 基礎 |
| 値を配列の添字にしたいが、値の範囲が広すぎる | [座標圧縮](../basics/coordinate-compression.md) | 基礎 |
| 区間の条件が S_r と S_l の関係（差が K・余りが等しい）に書き直せる | [累積和と連想配列で区間を数える](../basics/prefix-sum-counting.md) | 基礎 |
| 操作が区間に一律の値を足す形で、隣接差では 2 か所だけが変わる | [差分列への言い換え](../basics/difference-sequence.md) | 黄 |
| 選び方の和の最大化なら解けるが、割り算（平均・比）が入ると直接は最大化できない | [平均・中央値の最大化](../basics/fractional-binary-search.md) | 水 |
| 全部は列挙できないが「x 以下が何個あるか」は数えられる | [K 番目の値](../basics/kth-value.md) | 青 |
| 1 つ増やすごとの増分が単調に増える | [三分探索](../basics/ternary-search.md) | 水 |
| その場で一番よいものを選んでも後悔しない（入れ替えても悪くならない） | [貪欲法の考え方と正当性](../basics/greedy-basics.md) | 基礎 |
| 一度選んだものを、後でよいものが来たら入れ替えたい | [優先度付きキューを使う貪欲](../basics/greedy-priority-queue.md) | 水 |
| 2 つを入れ替えたときの差が、その 2 つだけで決まる | [交換論法と比較関数の設計](../basics/exchange-argument.md) | 青 |
| 左右に分けたとき、中央をまたぐものだけなら速く数えられる | [分割統治](../basics/divide-and-conquer.md) | 黄 |
| 区間の最大値の位置で左右に分けると、それぞれが同じ形の問題になる | [分割統治](../basics/divide-and-conquer.md) | 黄 |
| 式を変形すると i の項と j の項に分離できる | [言い換えの典型](../thinking/reformulation.md) | 水 |
| 直接数えると場合分けが多いが、条件を満たさない側は数えやすい | [余事象](../thinking/complement.md) | 基礎 |
| 後ろから決めると選択肢が 1 つに決まる | [後ろから・逆順に考える](../thinking/reverse-thinking.md) | 基礎 |
| dp[i] が dp[i−1]・dp[i−2] など定数個の前の状態から決まる | [DP の基本](../dp/dp-basics.md) | 基礎 |
| dp[x] が x より小さい値の dp で決まるが、どの値が現れるかを前もって列挙しにくい | [メモ化再帰](../dp/memoized-recursion.md) | 基礎 |
| dp[i] が dp[j]（j > i）から決まる（i 番目以降で最適に行動したときの値） | [DP の計算順序](../dp/dp-order.md) | 水 |
| 区間 [l, r) の両端を全探索すると O(N^2) になり、各位置の扱いが「区間の前・中・後」で変わる | [フェーズを状態に持つ DP](../dp/dp-phase.md) | 青 |
| dp[i] = Σ_{j=i−R}^{i−L} dp[j] のように、遷移元が連続した範囲の和 | [累積和・いもす法による DP の高速化](../dp/dp-prefix-sum.md) | 水 |
| dp[i] から i+L〜i+R の範囲へ同じ値を配る | [累積和・いもす法による DP の高速化](../dp/dp-prefix-sum.md) | 水 |
| dp\[i]\[a][b] の表が大きすぎ、同じ (i, a) なら b が大きい（小さい）ほど常に良い | [DP の状態の削減](../dp/dp-dimension-reduction.md) | 青 |
| dp[i] = Σ（または min）\_{j < i, [j, i) が条件を満たす} dp[j] | [区間分割 DP](../dp/dp-sequence-partition.md) | 水 |
| 根を v としたときの木 DP の値を、すべての v について求めたい（N 回の木 DP は O(N^2)） | [全方位木 DP](../dp/rerooting.md) | 青 |
| dp\[v][k] を子の dp\[c][j] との (k, j) の組の全探索でマージしていて、O(N^3) に見える | [二乗の木 DP](../dp/tree-dp-square.md) | 黄 |
| 素直に書いた DP の遷移が状態 1 つあたり O(N) かかり、全体で O(N^2) になる | [DP の高速化の選び方](../dp/dp-speedup-overview.md)（準備中） | — |
| dp[i] = max_{j < i, l ≤ a_j ≤ r} dp[j] + c のように、遷移元が添字や値の範囲の最小・最大 | [セグメント木・スライド最小値による DP の高速化](../dp/dp-segment-tree.md) | 青 |
| 遷移のコストに \|x_i − x_j\| を含む（x_j < x_i と x_j > x_i で分けられる） | [セグメント木・スライド最小値による DP の高速化](../dp/dp-segment-tree.md) | 青 |
| dp[i] = min_{i−K ≤ j < i} dp[j] + c（窓が単調に動く） | [セグメント木・スライド最小値による DP の高速化](../dp/dp-segment-tree.md) | 青 |
| dp\[i][\*] から dp\[i+1][\*] で変わる場所が少ない | [インライン DP](../dp/inline-dp.md) | 青 |
| 遷移で dp 全体に一律の加算・平行移動が入る | [インライン DP](../dp/inline-dp.md) | 青 |
| 区間 [l, r] の右端 r で、l 以降の位置の dp にまとめて加算する | [インライン DP](../dp/inline-dp.md) | 青 |
| 遷移のコストが i と j の積の項を 1 つだけ含む（(h_i − h_j)^2 など） | [Convex Hull Trick と Li Chao Tree](../dp/cht.md) | 発展 |
| 区間分割 DP のコストが c(a, c) + c(b, d) ≤ c(a, d) + c(b, c) を満たす（区間を広げるほど増え方が大きい） | [Monge 性による DP の高速化](../dp/monge.md) | 発展 |
| 最適な区切り位置 opt(i) が i について単調に動く | [Monge 性による DP の高速化](../dp/monge.md) | 発展 |
| K 個選ぶときの答え f(K) が K について凸（1 個増やすときの得が、個数が増えるほど減る） | [Alien DP](../dp/alien-dp.md) | 発展 |
| dp\[i][x] = min_{y ≤ x} dp\[i−1][y] + \|x − a_i\| のように、x について区分線形で凸 | [Slope Trick](../dp/slope-trick.md) | 発展 |
| 成分ごとの頂点数と辺数の関係（木か・閉路がちょうど 1 つか）で条件が決まる | [連結成分](../graph/connected-components.md) | 基礎 |
| 言い換えると、辺の重みが 0 と 1 の 2 種類だけのグラフの最短路になる | [01-BFS](../graph/zero-one-bfs.md) | 水 |
| 距離を dist\[頂点][向き・残り回数・偶奇] のように 2 次元以上で持ちたくなる | [状態を頂点にする](../graph/extended-dijkstra.md) | 水 |
| 条件を整理すると x_v ≤ x_u + c の形の不等式の集まりになる | [差分制約（牛ゲー）](../graph/difference-constraints.md) | 青 |
| 閉路を 1 点に縮めた DAG の上で DP・数え上げをしたくなる | [強連結成分分解（SCC）](../graph/scc.md) | 水 |
| 遷移が x → f(x) の写像 1 つで決まる | [Functional graph（出次数 1 のグラフ）](../graph/functional-graph.md) | 水 |
| 条件がすべて (x_i ∨ x_j) の形（2 つのリテラルの OR）に書ける | [2-SAT](../graph/two-sat.md) | 発展 |
| 目的関数が、0/1 変数ごとの項と「x_i = 1 かつ x_j = 0 ならコスト c」の項の和で書ける | [燃やす埋める](../graph/project-selection.md) | 黄 |
| j − i = A_i + A_j のように、i だけの式と j だけの式が等しい組 (i, j) を数える | [STL コンテナの使い分け](../ds/stl-containers.md) | 基礎 |
| dp[i] = min(dp[i−K..i−1]) + c のように、直前 K 個の最小値で決まる遷移 | [単調スタックとスライド最小値](../ds/monotonic-stack.md) | 水 |
| Σ_{j&lt;i} [A_j ≤ A_i] のように、前にある要素のうち条件を満たすものの個数・和を i ごとに足す | [BIT（Fenwick Tree）](../ds/fenwick-tree.md) | 水 |
| dp[v] = max(dp[v − D..v + D]) + 1 のように、値の範囲から最大を取る遷移 | [値を添字にする BIT・セグメント木](../ds/segment-tree-on-values.md) | 水 |
| 区間 [l, r) の答えが、各位置の一次関数や小さな行列を順に合成したもので書ける | [セグメント木に何を載せるか](../ds/segment-tree-monoids.md) | 青 |
| Σ_{i=1}^{N} Σ_{j=i}^{N} f(i, j) のように、内側の和の範囲が外側の添字で決まる二重和 | [Σ の変形](../math/sigma-manipulation.md) | 基礎 |
| Σ_{K=1}^{N} K × (K の約数の個数) のように、約数・倍数の関係で書き換えられる和 | [Σ の変形](../math/sigma-manipulation.md) | 基礎 |
| Σ_{i=0}^{N−1} A^i の形の和 | [等比数列の和を mod で求める](../math/geometric-series-mod.md) | 基礎 |
| Σ_{d=1}^{M} Σ_{k=1}^{⌊M/d⌋} f(d, kd) の形の二重ループ | [調和級数と倍数の列挙](../math/harmonic-sum.md) | 水 |
| Σ_{i=1}^{N} f(⌊N/i⌋) の形の和 | [商の列挙](../math/floor-quotient-enum.md) | 水 |
| dp[t+1] の各成分が dp[t] の成分の線形結合で、係数が t によらない | [行列累乗](../math/matrix-power.md) | 青 |
| 変数の一次式（mod 2 なら XOR）＝定数 の式が複数立つ | [掃き出し法](../math/gaussian-elimination.md) | 青 |
| c_k = Σ_{i+j=k} a_i b_j の形の和 | [畳み込みの使い方](../math/convolution-ntt.md) | 青 |
| dp[i] = Σ_{j&lt;i} dp[j]·g[i−j] のように、dp が自分より前の値との畳み込みで決まる | [分割統治 FFT・オンライン畳み込み](../math/online-convolution.md) | 発展 |
| 遷移が「和が s になる組の数」の形（多項式の積） | [分割統治 FFT・オンライン畳み込み](../math/online-convolution.md) | 発展 |
| 答えが多項式 f の 1/f・log f・exp f・f^K の係数で書ける | [形式的冪級数と多項式の演算](../math/fps-basics.md) | 発展 |
| a_n = Σ_{k=1}^{K} c_k a_{n−k} の形の漸化式 | [線形漸化式の高速化](../math/linear-recurrence-fast.md) | 発展 |
| 答え f(N) が N の d 次多項式になる | [ラグランジュ補間とべき乗和](../math/lagrange-interpolation.md) | 発展 |
| 答えが K(K−1)^(N−1) のような累乗の積の形になる | [和・積の法則と順列・組合せ](../comb/counting-basics.md) | 基礎 |
| 答えが「K 以下」の個数の差 f(K) − f(K−1) で書ける | [数え上げの考え方](../comb/counting-mindset.md) | 水 |
| 二項係数の積の和を、1 つの二項係数（経路の数）に直したい | [対応づけ・数える対象の言い換え](../comb/counting-bijection.md) | 青 |
| 作り方（遷移の列）を数える式で、同じ対象が複数回数えられてしまう | [重複の除き方](../comb/counting-dedup.md) | 青 |
| Σ の中に二項係数があり、N が大きく項ごとには足せない | [二項係数の恒等式と和の公式](../comb/binomial-identities.md) | 青 |
| 答えの式に Σ_{k≤K} C(n,k) の形の和が、多くの (n, K) について現れる | [二項係数の部分和](../comb/binomial-prefix-sum.md) | 発展 |
| 答えが (1 + x + … + x&#94;c)&#94;N のような式の特定の係数になる | [母関数の考え方](../comb/generating-function-counting.md) | 発展 |
| 遷移が dp'[s] = dp[s] + dp[s − v] のように、値をずらして足す形になる | [母関数の考え方](../comb/generating-function-counting.md) | 発展 |
| E[s] が、s から 1 手で移る状態の E の平均に定数を足した式になる | [期待値 DP](../comb/expected-value-dp.md) | 水 |
| 長さ i までの文字列の数を、末尾とパターンの先頭が何文字一致しているかで分けて持つ | [照合オートマトン上の DP](../string/string-automaton-dp.md) | 青 |
| (x2 − x1)(y3 − y1) − (y2 − y1)(x3 − x1) の符号で場合を分ける | [ベクトルと外積](../geometry/geometry-vectors.md) | 基礎 |
| \|x_i − x_j\| + \|y_i − y_j\| や max(\|x_i − x_j\|, \|y_i − y_j\|) の最大・和が式に出る | [マンハッタン距離と 45 度回転](../geometry/manhattan-chebyshev.md) | 水 |
| (S_j − S_i)/(j − i) の最大（2 点を結ぶ傾きの最大） | [凸包と凸多角形](../geometry/convex-hull.md) | 黄 |
| 決定的な方法は重いが、確率的に正しければ十分に速い | [乱択アルゴリズム](../misc/randomized.md) | 青 |
| 固定の mod・係数のハッシュが、作為的な入力で衝突させられる | [乱択アルゴリズム](../misc/randomized.md) | 青 |

<!-- textlint-enable -->
<!-- gen:end signs-shape -->
