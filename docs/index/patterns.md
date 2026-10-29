---
title: 題材別の詳細索引
type: generated
search:
  exclude: true
---

<!-- tools/gen_site.py が生成する。手で直さない -->

# 題材別の詳細索引

分野の全ページの id・URL・別名・サイン・種類・前提・使い分け・節。全分野の1行の一覧と索引の版は https://yuukougun.github.io/kyopro-atlas/llms.txt にある。

## 区間（interval） {#interval}

- id：`interval`　レベル：—　段階：reviewed　type：pattern
- URL：https://yuukougun.github.io/kyopro-atlas/patterns/interval/
- 別名：連続部分列、部分配列、subarray、区間の集合、interval
- 種類：案内、区間クエリ、累積和・差分
- サイン：
    - 言い回し：和が K（K の倍数）になる連続部分列の個数
    - 言い回し：すべての連続部分列についての最小値・最大値・2 番目の値の総和
    - 言い回し：N 個の区間 [L_i, R_i] から重ならないように最大何個選べるか
    - 言い回し：区間を塗るたびに、塗られていない長さや個数を答える
    - 言い回し：区間に含まれる異なる値の個数を多数答える
- 節：
    - `interval#properties` 題材の性質：https://yuukougun.github.io/kyopro-atlas/patterns/interval/#properties
    - `interval#overview` 問われ方と手法の一覧：https://yuukougun.github.io/kyopro-atlas/patterns/interval/#overview
    - `interval#sum` 区間の和 → 累積和（prefix-sum）：https://yuukougun.github.io/kyopro-atlas/patterns/interval/#sum
    - `interval#count-by-sum` 和が K・K の倍数の区間の個数 → 累積和と連想配列（prefix-sum-counting）：https://yuukougun.github.io/kyopro-atlas/patterns/interval/#count-by-sum
    - `interval#monotone-window` 伸び縮みで単調な条件 → 尺取り法（two-pointers）：https://yuukougun.github.io/kyopro-atlas/patterns/interval/#monotone-window
    - `interval#sum-over-subarrays` 全区間の最小値・最大値の総和 → 寄与と単調スタック（contribution, monotonic-stack）：https://yuukougun.github.io/kyopro-atlas/patterns/interval/#sum-over-subarrays
    - `interval#other-statistics` 全区間の中央値・mex・転倒数 → 題材別の各ページ（kth-and-median, mex, permutation）：https://yuukougun.github.io/kyopro-atlas/patterns/interval/#other-statistics
    - `interval#partition` 列を区間に区切る方法の数・最適値 → 区間分割 DP（dp-sequence-partition）：https://yuukougun.github.io/kyopro-atlas/patterns/interval/#partition
    - `interval#shrink-and-merge` 縮めながら取り除く・隣どうしを合体させる → 区間 DP（interval-dp）：https://yuukougun.github.io/kyopro-atlas/patterns/interval/#shrink-and-merge
    - `interval#batch-add` 加算をまとめて最後に見る → いもす法（imos）：https://yuukougun.github.io/kyopro-atlas/patterns/interval/#batch-add
    - `interval#online-updates` 更新と質問が交互 → BIT・セグメント木（fenwick-tree, segment-tree）：https://yuukougun.github.io/kyopro-atlas/patterns/interval/#online-updates
    - `interval#static-min` 値が変わらない列の区間の最小値 → Sparse Table（sparse-table）：https://yuukougun.github.io/kyopro-atlas/patterns/interval/#static-min
    - `interval#difference` 区間に ±1 する操作の回数・可否 → 差分列への言い換え（difference-sequence）：https://yuukougun.github.io/kyopro-atlas/patterns/interval/#difference
    - `interval#offline` 区間の種類数・x 以下の個数 → 先読みと BIT、Mo（offline-queries, mo-algorithm）：https://yuukougun.github.io/kyopro-atlas/patterns/interval/#offline
    - `interval#scheduling` 重ならない最大個数・すべてを串刺しにする点の数 → 区間スケジューリング（interval-scheduling）：https://yuukougun.github.io/kyopro-atlas/patterns/interval/#scheduling
    - `interval#union` 区間の和集合・塗りつぶし・残りの長さ → 区間を set で管理（interval-set）：https://yuukougun.github.io/kyopro-atlas/patterns/interval/#union
    - `interval#containment` 含まれる・交差する区間の数 → イベントソート・平面走査（event-sort, sweep-line-2d）：https://yuukougun.github.io/kyopro-atlas/patterns/interval/#containment
    - `interval#substrings` 数列ではなく文字列の連続部分 → 部分列と部分文字列（subsequence-and-substring）：https://yuukougun.github.io/kyopro-atlas/patterns/interval/#substrings

## 部分列と部分文字列（subsequence-and-substring） {#subsequence-and-substring}

- id：`subsequence-and-substring`　レベル：—　段階：reviewed　type：pattern
- URL：https://yuukougun.github.io/kyopro-atlas/patterns/subsequence-and-substring/
- 別名：部分列、部分文字列、subsequence、substring
- 種類：案内、文字列、DP
- 使い分け：`method-comparison#similar-names`
- サイン：
    - 言い回し：T が S の部分列か判定する
    - 言い回し：S から何文字か選んで順に並べると T になる選び方の数
    - 言い回し：S の部分列として現れる異なる文字列の個数
    - 言い回し：S の部分文字列の種類数
- 節：
    - `subsequence-and-substring#properties` 題材の性質：https://yuukougun.github.io/kyopro-atlas/patterns/subsequence-and-substring/#properties
    - `subsequence-and-substring#overview` 問われ方と手法の一覧：https://yuukougun.github.io/kyopro-atlas/patterns/subsequence-and-substring/#overview
    - `subsequence-and-substring#is-subsequence` T が S の部分列か → 前から貪欲に照合・次の出現位置の表（subsequence-matching）：https://yuukougun.github.io/kyopro-atlas/patterns/subsequence-and-substring/#is-subsequence
    - `subsequence-and-substring#count-occurrences` T が部分列として現れる選び方の数 → 照合した文字数を状態にした DP（dp-state-design）：https://yuukougun.github.io/kyopro-atlas/patterns/subsequence-and-substring/#count-occurrences
    - `subsequence-and-substring#count-with-condition` 条件を満たす部分列の数 → 末尾の文字や余りを状態にした DP（dp-state-design, dp-mod-state）：https://yuukougun.github.io/kyopro-atlas/patterns/subsequence-and-substring/#count-with-condition
    - `subsequence-and-substring#distinct-subsequences` 異なる部分列の数 → 部分列 DP と代表元の決め方（subsequence-dp, counting-dedup）：https://yuukougun.github.io/kyopro-atlas/patterns/subsequence-and-substring/#distinct-subsequences
    - `subsequence-and-substring#index-tuples` 位置の 3 つ組（添字が増える順）の数 → 段階を状態にした DP（dp-phase）：https://yuukougun.github.io/kyopro-atlas/patterns/subsequence-and-substring/#index-tuples
    - `subsequence-and-substring#longest` 最長共通部分列・最長増加部分列 → LCS・LIS（lcs, lis）：https://yuukougun.github.io/kyopro-atlas/patterns/subsequence-and-substring/#longest
    - `subsequence-and-substring#substring-match` 部分文字列の一致・比較 → ローリングハッシュ・Z（rolling-hash, z-algorithm）：https://yuukougun.github.io/kyopro-atlas/patterns/subsequence-and-substring/#substring-match
    - `subsequence-and-substring#distinct-substrings` 部分文字列の種類数・K 番目 → Suffix Array（suffix-array）：https://yuukougun.github.io/kyopro-atlas/patterns/subsequence-and-substring/#distinct-substrings
    - `subsequence-and-substring#palindromes` 回文の部分文字列・部分列 → 回文のページと区間 DP（palindrome, interval-dp）：https://yuukougun.github.io/kyopro-atlas/patterns/subsequence-and-substring/#palindromes
    - `subsequence-and-substring#avoid-substring` T を部分文字列に含まない文字列の数 → 照合の状態を持つ DP（string-automaton-dp）：https://yuukougun.github.io/kyopro-atlas/patterns/subsequence-and-substring/#avoid-substring
    - `subsequence-and-substring#subarrays` 数列の連続部分列 → 題材別の区間（interval）：https://yuukougun.github.io/kyopro-atlas/patterns/subsequence-and-substring/#subarrays

## 順列と置換（permutation） {#permutation}

- id：`permutation`　レベル：—　段階：reviewed　type：pattern
- URL：https://yuukougun.github.io/kyopro-atlas/patterns/permutation/
- 別名：permutation、置換、1〜N の順列
- 種類：案内、数え上げ、考察
- サイン：
    - 言い回し：(1, 2, …, N) の順列 P が与えられる
    - 言い回し：任意の 2 要素の swap を繰り返してソートする最小回数
    - 言い回し：隣り合う 2 要素の swap でソートする最小回数
    - 言い回し：ちょうど K 回の swap（10^100 回など）で作れる列
    - 言い回し：置換を K 回（K ≤ 10^18）適用した結果
    - 言い回し：条件を満たす順列の個数
- 節：
    - `permutation#properties` 題材の性質：https://yuukougun.github.io/kyopro-atlas/patterns/permutation/#properties
    - `permutation#overview` 問われ方と手法の一覧：https://yuukougun.github.io/kyopro-atlas/patterns/permutation/#overview
    - `permutation#any-swap` 任意の swap でソートする最小回数・手順 → 置換の巡回分解（permutation-cycles, construction）：https://yuukougun.github.io/kyopro-atlas/patterns/permutation/#any-swap
    - `permutation#adjacent-swap` 隣接 swap でソートする最小回数 → 転倒数（inversion-number）：https://yuukougun.github.io/kyopro-atlas/patterns/permutation/#adjacent-swap
    - `permutation#swap-parity` ちょうど K 回の swap で作れるか → 置換の偶奇（permutation-parity）：https://yuukougun.github.io/kyopro-atlas/patterns/permutation/#swap-parity
    - `permutation#repeat` 置換を K 回適用した結果 → 巡回ごとの周期・ダブリング（functional-graph, doubling）：https://yuukougun.github.io/kyopro-atlas/patterns/permutation/#repeat
    - `permutation#inverse` 位置と値の両方から引く操作 → 逆置換を同時に持つ：https://yuukougun.github.io/kyopro-atlas/patterns/permutation/#inverse
    - `permutation#counting` 条件を満たす順列の数 → 挿入 DP・撹乱順列（insertion-dp, inclusion-exclusion）：https://yuukougun.github.io/kyopro-atlas/patterns/permutation/#counting
    - `permutation#lexicographic` 辞書順で何番目・K 番目の順列 → 残りの並べ方の数・順列全探索：https://yuukougun.github.io/kyopro-atlas/patterns/permutation/#lexicographic
    - `permutation#increasing` 増加部分列・いくつの増加部分列に分けるか → LIS（lis）：https://yuukougun.github.io/kyopro-atlas/patterns/permutation/#increasing

## 括弧列（bracket-sequence） {#bracket-sequence}

- id：`bracket-sequence`　レベル：—　段階：reviewed　type：pattern
- URL：https://yuukougun.github.io/kyopro-atlas/patterns/bracket-sequence/
- 別名：正しい括弧列、カッコ列、parentheses、バランスの取れた括弧列、bracket sequence
- 種類：案内、文字列、累積和・差分
- 前提：`prefix-sum`
- サイン：
    - 言い回し：'(' と ')' からなる文字列が正しい括弧列か判定する
    - 言い回し：? を ( か ) に置き換えて正しい括弧列にする方法の数
    - 言い回し：文字の入れ替えのたびに、区間が正しい括弧列かを答える
    - 言い回し：複数の括弧列を並べて連結し、正しい括弧列にできるか
    - 言い回し：長さ 2N の正しい括弧列の個数
- 節：
    - `bracket-sequence#properties` 題材の性質：https://yuukougun.github.io/kyopro-atlas/patterns/bracket-sequence/#properties
    - `bracket-sequence#overview` 問われ方と手法の一覧：https://yuukougun.github.io/kyopro-atlas/patterns/bracket-sequence/#overview
    - `bracket-sequence#check` 1 種類の括弧の判定 → ±1 の累積和（prefix-sum）：https://yuukougun.github.io/kyopro-atlas/patterns/bracket-sequence/#check
    - `bracket-sequence#stack` 複数種類の括弧・入れ子の構造 → スタック（stack-techniques）：https://yuukougun.github.io/kyopro-atlas/patterns/bracket-sequence/#stack
    - `bracket-sequence#counting` ? の埋め方の数・条件を満たす括弧列の数 → 開いている数を状態にした DP（dp-state-design）：https://yuukougun.github.io/kyopro-atlas/patterns/bracket-sequence/#counting
    - `bracket-sequence#range-check` 区間が正しい括弧列か（更新あり）→ 累積和の区間加算と区間の最小値（lazy-segment-tree）：https://yuukougun.github.io/kyopro-atlas/patterns/bracket-sequence/#range-check
    - `bracket-sequence#monoid` （合計, 最小値）をセグメント木に載せる → モノイドの設計（segment-tree-monoids）：https://yuukougun.github.io/kyopro-atlas/patterns/bracket-sequence/#monoid
    - `bracket-sequence#ordering` 複数の括弧列を並べる順序 → 要約して 2 組に分けてソート（exchange-argument）：https://yuukougun.github.io/kyopro-atlas/patterns/bracket-sequence/#ordering
    - `bracket-sequence#max-value` 価値が最大の正しい括弧列 → 先頭からの条件に言い換えて優先度付きキュー（greedy-priority-queue）：https://yuukougun.github.io/kyopro-atlas/patterns/bracket-sequence/#max-value
    - `bracket-sequence#parsing` 数式・入れ子の構造の解析 → 構文解析（parsing）：https://yuukougun.github.io/kyopro-atlas/patterns/bracket-sequence/#parsing

## mex（mex） {#mex}

- id：`mex`　レベル：—　段階：reviewed　type：pattern
- URL：https://yuukougun.github.io/kyopro-atlas/patterns/mex/
- 別名：minimum excluded、含まれない最小の非負整数、まだ出ていない最小の値
- 種類：案内、データ構造、考察
- サイン：
    - 言い回し：含まれない最小の非負整数（mex）を答える
    - 言い回し：1 点を書き換えるたびに数列の mex を答える
    - 言い回し：長さ M の全区間の mex の最小値
    - 言い回し：全区間・全パスの mex の総和
- 節：
    - `mex#properties` 題材の性質：https://yuukougun.github.io/kyopro-atlas/patterns/mex/#properties
    - `mex#overview` 問われ方と手法の一覧：https://yuukougun.github.io/kyopro-atlas/patterns/mex/#overview
    - `mex#online-mex` 更新のたびに mex を答える → 出現回数 0 の値の set・セグメント木上の二分探索：https://yuukougun.github.io/kyopro-atlas/patterns/mex/#online-mex
    - `mex#interval-values` 値が区間でまとめて入る → 区間を set で管理（interval-set）：https://yuukougun.github.io/kyopro-atlas/patterns/mex/#interval-values
    - `mex#window-mex` 区間・窓の mex の最小値・最大値 → 値を固定して出現位置の間隔を見る（fix-variable）：https://yuukougun.github.io/kyopro-atlas/patterns/mex/#window-mex
    - `mex#sum-of-mex` 全区間・全パスの mex の総和 → mex が k+1 以上の数を足す主客転倒：https://yuukougun.github.io/kyopro-atlas/patterns/mex/#sum-of-mex
    - `mex#grundy` ゲームの局面の値 → Grundy 数（grundy-number）：https://yuukougun.github.io/kyopro-atlas/patterns/mex/#grundy
    - `mex#construction` mex を指定した値にする構築 → 0〜k−1 を入れて k を入れない（construction）：https://yuukougun.github.io/kyopro-atlas/patterns/mex/#construction

## K 番目と中央値（kth-and-median） {#kth-and-median}

- id：`kth-and-median`　レベル：—　段階：reviewed　type：pattern
- URL：https://yuukougun.github.io/kyopro-atlas/patterns/kth-and-median/
- 別名：K 番目、中央値、メディアン、上位 K 個、median
- 種類：案内、二分探索、データ構造
- 使い分け：`method-comparison#containers`
- サイン：
    - 言い回し：K 番目に小さい（大きい）値を答える
    - 言い回し：N² 個の積・和・差の中で K 番目
    - 言い回し：値の追加・更新のたびに、大きい方から K 個の和を答える
    - 言い回し：中央値の最大値・最小値
    - 言い回し：Σ|x − a_i| を最小にする x
    - 言い回し：辞書順で K 番目のもの
- 節：
    - `kth-and-median#properties` 題材の性質：https://yuukougun.github.io/kyopro-atlas/patterns/kth-and-median/#properties
    - `kth-and-median#overview` 問われ方と手法の一覧：https://yuukougun.github.io/kyopro-atlas/patterns/kth-and-median/#overview
    - `kth-and-median#count-and-search` 候補が多すぎて並べられない → x 以下の個数で答えを二分探索（kth-value, binary-search-answer）：https://yuukougun.github.io/kyopro-atlas/patterns/kth-and-median/#count-and-search
    - `kth-and-median#streaming` 値を追加しながら K 番目・上位 K 個 → 優先度付きキュー・2 つの multiset：https://yuukougun.github.io/kyopro-atlas/patterns/kth-and-median/#streaming
    - `kth-and-median#dynamic` 追加と削除がある K 番目 → BIT 上の二分探索・値を添字にするセグメント木：https://yuukougun.github.io/kyopro-atlas/patterns/kth-and-median/#dynamic
    - `kth-and-median#k-best` 小さい方から K 個の解を列挙 → 優先度付きキューで最小を取り出す（greedy-priority-queue）：https://yuukougun.github.io/kyopro-atlas/patterns/kth-and-median/#k-best
    - `kth-and-median#range-kth` 区間の K 番目・x 以下の個数 → クエリの先読みと BIT、Wavelet Matrix：https://yuukougun.github.io/kyopro-atlas/patterns/kth-and-median/#range-kth
    - `kth-and-median#maximize-median` 中央値・平均の最大化 → 値を引く・±1 にして符号で判定する二分探索（fractional-binary-search）：https://yuukougun.github.io/kyopro-atlas/patterns/kth-and-median/#maximize-median
    - `kth-and-median#absolute-sum` Σ|x − a_i| の最小 → 中央値を選ぶ（median-absolute）：https://yuukougun.github.io/kyopro-atlas/patterns/kth-and-median/#absolute-sum
    - `kth-and-median#lexicographic-kth` 辞書順で K 番目の文字列・順列 → 残りの個数を数えて先頭から決める：https://yuukougun.github.io/kyopro-atlas/patterns/kth-and-median/#lexicographic-kth
    - `kth-and-median#xor-kth` XOR で作れる値の K 番目 → XOR 基底（xor-basis）：https://yuukougun.github.io/kyopro-atlas/patterns/kth-and-median/#xor-kth

## XOR（xor） {#xor}

- id：`xor`　レベル：—　段階：reviewed　type：pattern
- URL：https://yuukougun.github.io/kyopro-atlas/patterns/xor/
- 別名：排他的論理和、ビットごとの排他的論理和、exclusive or
- 種類：案内、ビット演算、線形代数・行列
- 前提：`bit-operations`
- サイン：
    - 言い回し：すべての組・すべての区間の XOR の総和
    - 言い回し：x を選んで XOR の最大値・最小値を求める
    - 言い回し：いくつか選んだ XOR で作れる値・作れる値の個数・K 番目
    - 言い回し：区間の XOR・木のパスの XOR・経路の XOR
    - 言い回し：石を取り合うゲームで、山の石の数の XOR
- 節：
    - `xor#properties` 題材の性質：https://yuukougun.github.io/kyopro-atlas/patterns/xor/#properties
    - `xor#overview` 問われ方と手法の一覧：https://yuukougun.github.io/kyopro-atlas/patterns/xor/#overview
    - `xor#sum-of-xor` 全ペア・全区間の XOR の和 → 桁ごとに 0 と 1 の個数を数える（bitwise-independence）：https://yuukougun.github.io/kyopro-atlas/patterns/xor/#sum-of-xor
    - `xor#range-xor` 区間の XOR → 累積 XOR、更新があれば BIT（prefix-sum, fenwick-tree）：https://yuukougun.github.io/kyopro-atlas/patterns/xor/#range-xor
    - `xor#tree-path` 木の 2 点間のパスの XOR → 根からの XOR どうしの XOR（tree-distance）：https://yuukougun.github.io/kyopro-atlas/patterns/xor/#tree-path
    - `xor#choose-x` x を選んで XOR の最大・最小、2 要素の XOR の最小 → 上位 bit から決める・Binary Trie：https://yuukougun.github.io/kyopro-atlas/patterns/xor/#choose-x
    - `xor#basis` 選んだ XOR で作れる値・最大値・K 番目 → XOR 基底（xor-basis）：https://yuukougun.github.io/kyopro-atlas/patterns/xor/#basis
    - `xor#path-xor` グラフの経路の XOR の最小 → 閉路の XOR を基底にする（xor-basis）：https://yuukougun.github.io/kyopro-atlas/patterns/xor/#path-xor
    - `xor#digit-dp` XOR が絡む条件を満たす数の個数 → 桁 DP（digit-dp）：https://yuukougun.github.io/kyopro-atlas/patterns/xor/#digit-dp
    - `xor#xor-equals-sum` XOR と和が等しい区間の数 → 尺取り法（two-pointers）：https://yuukougun.github.io/kyopro-atlas/patterns/xor/#xor-equals-sum
    - `xor#meet-in-the-middle` 小さいグリッドの経路の XOR → 半分全列挙（meet-in-the-middle）：https://yuukougun.github.io/kyopro-atlas/patterns/xor/#meet-in-the-middle
    - `xor#games` 石取りゲーム → Nim・Grundy 数（nim, grundy-number）：https://yuukougun.github.io/kyopro-atlas/patterns/xor/#games
    - `xor#set-hash` 2 つの集合が一致するか → 乱数の XOR によるハッシュ（hashing-for-sets）：https://yuukougun.github.io/kyopro-atlas/patterns/xor/#set-hash
    - `xor#xor-convolution` 添字の XOR で畳み込む → アダマール変換（hadamard-transform）：https://yuukougun.github.io/kyopro-atlas/patterns/xor/#xor-convolution
    - `xor#adjacent-xor` 列全体を同じ値で XOR したものを探す → 隣どうしの XOR の列で照合（kmp）：https://yuukougun.github.io/kyopro-atlas/patterns/xor/#adjacent-xor

## 約数と倍数（divisors-and-multiples） {#divisors-and-multiples}

- id：`divisors-and-multiples`　レベル：—　段階：reviewed　type：pattern
- URL：https://yuukougun.github.io/kyopro-atlas/patterns/divisors-and-multiples/
- 別名：約数、倍数、divisor、multiple
- 種類：案内、整数論
- サイン：
    - 制約：N ≤ 10^12 で、N の約数や素因数を使う
    - 言い回し：1 以上 N 以下のすべての整数について、約数や倍数に関する値の総和を求める
    - 言い回し：gcd がちょうど g になる組・部分集合の個数
    - 言い回し：積がちょうど N になる列の個数
    - 言い回し：積が平方数になる組の個数
- 節：
    - `divisors-and-multiples#properties` 題材の性質：https://yuukougun.github.io/kyopro-atlas/patterns/divisors-and-multiples/#properties
    - `divisors-and-multiples#overview` 問われ方と手法の一覧：https://yuukougun.github.io/kyopro-atlas/patterns/divisors-and-multiples/#overview
    - `divisors-and-multiples#enumerate` 1 つの数の約数を列挙 → √N までの割り算（divisor-enum）：https://yuukougun.github.io/kyopro-atlas/patterns/divisors-and-multiples/#enumerate
    - `divisors-and-multiples#count-bound` 約数の個数で計算量を見積もる → 約数の個数の上限（divisor-count-bound）：https://yuukougun.github.io/kyopro-atlas/patterns/divisors-and-multiples/#count-bound
    - `divisors-and-multiples#harmonic` 1〜M の各数の約数・倍数を集める → 倍数を回す調和級数（harmonic-sum）：https://yuukougun.github.io/kyopro-atlas/patterns/divisors-and-multiples/#harmonic
    - `divisors-and-multiples#factorize` 素因数分解 → 多数なら最小素因数の篩、1 つなら試し割り（spf-sieve, prime-factorization）：https://yuukougun.github.io/kyopro-atlas/patterns/divisors-and-multiples/#factorize
    - `divisors-and-multiples#divisor-functions` 約数の個数・約数の和 → 素因数分解の指数から（multiplicative-function）：https://yuukougun.github.io/kyopro-atlas/patterns/divisors-and-multiples/#divisor-functions
    - `divisors-and-multiples#exact-gcd` gcd がちょうど g の組の数 → 倍数で数えて大きい方から引く・メビウス関数：https://yuukougun.github.io/kyopro-atlas/patterns/divisors-and-multiples/#exact-gcd
    - `divisors-and-multiples#zeta` 約数・倍数の向きの累積和 → 約数のゼータ変換・メビウス変換（zeta-mobius-divisor）：https://yuukougun.github.io/kyopro-atlas/patterns/divisors-and-multiples/#zeta
    - `divisors-and-multiples#products` 積が平方数・積がちょうど N → 素因数の指数で考える（prime-exponent-vector）：https://yuukougun.github.io/kyopro-atlas/patterns/divisors-and-multiples/#products
    - `divisors-and-multiples#gcd` 差の gcd・区間の gcd の値の種類 → gcd の性質（gcd-lcm, gcd-properties）：https://yuukougun.github.io/kyopro-atlas/patterns/divisors-and-multiples/#gcd
    - `divisors-and-multiples#floor-sums` ⌊N/i⌋ の値ごとにまとめる → floor の値の列挙（floor-quotient-enum）：https://yuukougun.github.io/kyopro-atlas/patterns/divisors-and-multiples/#floor-sums

## グリッド（grid） {#grid}

- id：`grid`　レベル：—　段階：reviewed　type：pattern
- URL：https://yuukougun.github.io/kyopro-atlas/patterns/grid/
- 別名：マス目、盤面、H×W、二次元配列、grid
- 種類：案内、グラフ探索、DP
- サイン：
    - 言い回し：H×W のマス目で、スタートからゴールへの最小の移動回数
    - 言い回し：右か下にだけ進む経路の数・経路上の値の最大
    - 言い回し：長方形の範囲の和・黒マスの個数を多数答える
    - 言い回し：1×2 のタイル（ドミノ）を敷き詰める・置く
    - 言い回し：盤面を 90 度回転・反転させて一致させる
    - 言い回し：斜めに動く駒・マンハッタン距離・ひし形の範囲
- 節：
    - `grid#properties` 題材の性質：https://yuukougun.github.io/kyopro-atlas/patterns/grid/#properties
    - `grid#overview` 問われ方と手法の一覧：https://yuukougun.github.io/kyopro-atlas/patterns/grid/#overview
    - `grid#shortest` 最小の移動回数 → グリッドの BFS・01-BFS（grid-graph, bfs, zero-one-bfs）：https://yuukougun.github.io/kyopro-atlas/patterns/grid/#shortest
    - `grid#states` 向き・残り回数などの状態がある・盤面全体が状態 → 状態を頂点にする（extended-dijkstra）：https://yuukougun.github.io/kyopro-atlas/patterns/grid/#states
    - `grid#components` 連結成分・塗りつぶし → DFS・BFS・Union-Find（union-find）：https://yuukougun.github.io/kyopro-atlas/patterns/grid/#components
    - `grid#right-down` 右か下にだけ進む → グリッドの DP・格子路（dp-grid, lattice-paths）：https://yuukougun.github.io/kyopro-atlas/patterns/grid/#right-down
    - `grid#rectangles` 長方形の和・長方形への加算 → 2 次元累積和・2 次元いもす法（prefix-sum-2d, imos）：https://yuukougun.github.io/kyopro-atlas/patterns/grid/#rectangles
    - `grid#rows-cols` 行と列を選ぶ・行と列への操作 → 行と列を独立に考える・別々に座標圧縮：https://yuukougun.github.io/kyopro-atlas/patterns/grid/#rows-cols
    - `grid#checkerboard` 到達・敷き詰めの可否 → 市松模様の偶奇（parity）：https://yuukougun.github.io/kyopro-atlas/patterns/grid/#checkerboard
    - `grid#diagonal` 斜めの移動・マンハッタン距離・ひし形の範囲 → 45 度回転・斜めの座標（manhattan-chebyshev）：https://yuukougun.github.io/kyopro-atlas/patterns/grid/#diagonal
    - `grid#rotation` 盤面の回転・反転・平行移動 → 添字の対応の式・全部試す（rotation-transform, brute-force）：https://yuukougun.github.io/kyopro-atlas/patterns/grid/#rotation
    - `grid#tiling` ドミノの配置・隣り合わないマスの選び方 → 二部マッチング・プロファイル DP：https://yuukougun.github.io/kyopro-atlas/patterns/grid/#tiling

## 操作列とクエリ（operation-sequence） {#operation-sequence}

- id：`operation-sequence`　レベル：—　段階：reviewed　type：pattern
- URL：https://yuukougun.github.io/kyopro-atlas/patterns/operation-sequence/
- 別名：クエリの列、操作の列、逆順処理、シミュレーション
- 種類：案内、クエリ処理の工夫、データ構造
- サイン：
    - 言い回し：辺や頂点を 1 つずつ削除するたびに、連結成分の数を答える
    - 言い回し：全体に加算する・全体を反転する操作が混ざる
    - 言い回し：過去の状態に戻す・ある時点の状態をコピーする
    - 言い回し：行や列・区間を塗り替える操作の後の最終状態
    - 言い回し：同じ操作を 10^18 回繰り返した後の状態
- 節：
    - `operation-sequence#properties` 題材の性質：https://yuukougun.github.io/kyopro-atlas/patterns/operation-sequence/#properties
    - `operation-sequence#overview` 問われ方と手法の一覧：https://yuukougun.github.io/kyopro-atlas/patterns/operation-sequence/#overview
    - `operation-sequence#global-ops` 全体への加算・反転・回転 → 全体の操作を変数で持つ（global-offset）：https://yuukougun.github.io/kyopro-atlas/patterns/operation-sequence/#global-ops
    - `operation-sequence#insert-delete` 列の途中への挿入・削除・付け替え → 配列で持つ連結リスト・deque（linked-list, stack-techniques）：https://yuukougun.github.io/kyopro-atlas/patterns/operation-sequence/#insert-delete
    - `operation-sequence#paint` 区間を塗る・同じ値の区間をつなぐ → 区間を set で管理・次の空きへ飛ぶ Union-Find：https://yuukougun.github.io/kyopro-atlas/patterns/operation-sequence/#paint
    - `operation-sequence#overwrite` 後の操作が前の操作を上書きする → 後ろから見る（reverse-thinking）：https://yuukougun.github.io/kyopro-atlas/patterns/operation-sequence/#overwrite
    - `operation-sequence#reverse-deletion` 削除が難しい → 逆順にして追加にする（union-find-connectivity）：https://yuukougun.github.io/kyopro-atlas/patterns/operation-sequence/#reverse-deletion
    - `operation-sequence#offline` 先読みしてよい → 並べ替えてまとめて処理・Mo・イベントにして走査：https://yuukougun.github.io/kyopro-atlas/patterns/operation-sequence/#offline
    - `operation-sequence#online` 更新と質問が交互で区間を扱う → セグメント木・遅延セグメント木・平方分割：https://yuukougun.github.io/kyopro-atlas/patterns/operation-sequence/#online
    - `operation-sequence#versions` 過去の版に戻る・版をコピーする → 版の木・永続データ構造：https://yuukougun.github.io/kyopro-atlas/patterns/operation-sequence/#versions
    - `operation-sequence#repeat` 同じ操作を非常に多く繰り返す → 周期で打ち切る・操作の合成をダブリング（periodicity, doubling）：https://yuukougun.github.io/kyopro-atlas/patterns/operation-sequence/#repeat

## 円環（circular） {#circular}

- id：`circular`　レベル：—　段階：draft　type：pattern
- URL：https://yuukougun.github.io/kyopro-atlas/patterns/circular/
- 別名：環状、円形に並ぶ、円周上に並ぶ、最後と最初が隣り合う、2 周分に伸ばす、輪、リング、circular、cyclic、ring
- 種類：案内、累積和・差分、数え上げ
- サイン：
    - 言い回し：N 個が円形に並び、N 番目と 1 番目も隣り合う
    - 言い回し：円環上の連続する区間の和・個数（端をまたぐ区間も含む）
    - 言い回し：円形に並ぶものを、隣どうしが違う色で塗る方法の数
    - 言い回し：列を何回回転させると、もう一方の列に一致するか
    - 言い回し：円周上に点が並び、時計回りに進む・点どうしを弦で結ぶ
- 節：
    - `circular#properties` 題材の性質：https://yuukougun.github.io/kyopro-atlas/patterns/circular/#properties
    - `circular#overview` 問われ方と手法の一覧：https://yuukougun.github.io/kyopro-atlas/patterns/circular/#overview
    - `circular#sum` 円環上の区間の和 → 2 周分に伸ばした累積和（prefix-sum）：https://yuukougun.github.io/kyopro-atlas/patterns/circular/#sum
    - `circular#count-pairs` 時計回りの距離が M の倍数になる組 → 端をまたぐかで分けて数える（prefix-sum-counting）：https://yuukougun.github.io/kyopro-atlas/patterns/circular/#count-pairs
    - `circular#range-add` 更新のある円環の区間加算 → 端で 2 つに分ける（fenwick-tree, lazy-segment-tree）：https://yuukougun.github.io/kyopro-atlas/patterns/circular/#range-add
    - `circular#difference` 円環で一斉に行う操作の回数・可否 → 円環の差分列（difference-sequence）：https://yuukougun.github.io/kyopro-atlas/patterns/circular/#difference
    - `circular#coloring` 隣どうしが違う色になる塗り方の数 → 両端の色で場合分け（counting-basics）：https://yuukougun.github.io/kyopro-atlas/patterns/circular/#coloring
    - `circular#cut` 最後と最初の両方に条件がかかる DP → 1 か所で切り、最初の状態を固定する（dp-state-design）：https://yuukougun.github.io/kyopro-atlas/patterns/circular/#cut
    - `circular#cyclic-dependency` 円環状に依存し合う確率・期待値 → 1 つを未知数にして解く（expectation-linear-equations）：https://yuukougun.github.io/kyopro-atlas/patterns/circular/#cyclic-dependency
    - `circular#shift` 全体が毎回 1 つずつ回る遷移 → 添字のずらし（inline-dp）：https://yuukougun.github.io/kyopro-atlas/patterns/circular/#shift
    - `circular#rotation-match` 何回回転すると一致するか → A+A の中で B を探す（string-basics, z-algorithm）：https://yuukougun.github.io/kyopro-atlas/patterns/circular/#rotation-match
    - `circular#rotation-order` 回転どうしの辞書順・最小の回転 → S+S の Suffix Array（suffix-array）：https://yuukougun.github.io/kyopro-atlas/patterns/circular/#rotation-order
    - `circular#all-rotations` すべての回転についての値 → 差分の更新・畳み込み（inversion-number, convolution-ntt）：https://yuukougun.github.io/kyopro-atlas/patterns/circular/#all-rotations
    - `circular#up-to-rotation` 回転で同一視して数える → 円順列・Burnside の補題（counting-basics, burnside-lemma）：https://yuukougun.github.io/kyopro-atlas/patterns/circular/#up-to-rotation
    - `circular#angles` 方向が範囲に入る点・半周未満の点・ベクトルの和の長さの最大 → 偏角の列を 2 周分にする（argument-sort）：https://yuukougun.github.io/kyopro-atlas/patterns/circular/#angles
    - `circular#chords` 円周上の弦が交わるか → 1 か所で切って区間にする（stack-techniques）：https://yuukougun.github.io/kyopro-atlas/patterns/circular/#chords
    - `circular#step` 円周を K ずつ進む → gcd と一次合同式（gcd-properties, ext-gcd）：https://yuukougun.github.io/kyopro-atlas/patterns/circular/#step
    - `circular#namori` N 頂点 N 辺の連結グラフ → 閉路とぶら下がる木に分ける（namori-graph）：https://yuukougun.github.io/kyopro-atlas/patterns/circular/#namori
