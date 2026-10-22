---
title: 文字列の詳細索引
type: generated
search:
  exclude: true
---

<!-- tools/gen_site.py が生成する。手で直さない -->

# 文字列の詳細索引

分野の全ページの id・URL・別名・サイン・種類・前提・節。全分野の1行の一覧と索引の版は https://yuukougun.github.io/kyopro-atlas/llms.txt にある。

## 文字列の基本操作と辞書順（string-basics） {#string-basics}

- id：`string-basics`　レベル：基礎　段階：reviewed　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/string/string-basics/
- 別名：辞書順、文字列の比較、文字の一斉置換、文字列の回転、連結して辞書順最小、lexicographical order
- 種類：文字列
- 前提：`sorting-techniques`
- サイン：
    - 言い回し：条件を満たす文字列のうち辞書順で最小（最大）のものを出力する
    - 言い回し：2 種類の文字を一斉に入れ替える操作を繰り返して一致させられるか
    - 言い回し：先頭の文字を末尾に移す（回転する）操作を何回か行う
    - 制約：|S| ≤ 5000 程度で、回転や置き方を全部試せる
- 節：
    - `string-basics#lexicographic-order` 辞書順の定義と std::string の比較（接頭辞は短い方が小さい）：https://yuukougun.github.io/kyopro-atlas/string/string-basics/#lexicographic-order
    - `string-basics#substring-vs-subsequence` 部分文字列（連続）と部分列（連続でなくてよい）の違い：https://yuukougun.github.io/kyopro-atlas/string/string-basics/#substring-vs-subsequence
    - `string-basics#character-mapping` 文字の一斉置換：両方向の対応が一意か（全単射）：https://yuukougun.github.io/kyopro-atlas/string/string-basics/#character-mapping
    - `string-basics#concat-order` 連結して辞書順最小：長さが違えば 2 通りの連結を比べる：https://yuukougun.github.io/kyopro-atlas/string/string-basics/#concat-order
    - `string-basics#rotation` 回転（巡回シフト）の入口：回転回数の全探索と A+A：https://yuukougun.github.io/kyopro-atlas/string/string-basics/#rotation
    - `string-basics#cost-pitfalls` 計算量の落とし穴（substr・+・find は長さに比例する）：https://yuukougun.github.io/kyopro-atlas/string/string-basics/#cost-pitfalls

## 部分列の判定と次の出現位置の表（subsequence-matching） {#subsequence-matching}

- id：`subsequence-matching`　レベル：基礎　段階：reviewed　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/string/subsequence-matching/
- 別名：部分列判定、次の出現位置、nxt 配列、部分列オートマトン、序列自動機、部分列として含むか、subsequence automaton
- 種類：文字列
- 前提：`string-basics`、`binary-search`
- サイン：
    - 言い回し：T を部分列として含むか（連続でなくてよい）
    - 言い回し：長さ K の部分列のうち辞書順で最小のもの
    - 言い回し：S の部分列として現れない最短の文字列
    - 言い回し：S を何回も繰り返した文字列の部分列として入るか
    - 制約：|S| ≤ 10&#94;5〜10&#94;6、文字は英小文字で 26×(N+1) の表が持てる
- 節：
    - `subsequence-matching#greedy-matching` 貪欲な照合：できるだけ左で拾うのが最善な理由：https://yuukougun.github.io/kyopro-atlas/string/subsequence-matching/#greedy-matching
    - `subsequence-matching#next-occurrence` 次の出現位置の表（後ろから作る・番兵 N）：https://yuukougun.github.io/kyopro-atlas/string/subsequence-matching/#next-occurrence
    - `subsequence-matching#position-lists` 文字ごとの位置のリストと lower_bound による代用：https://yuukougun.github.io/kyopro-atlas/string/subsequence-matching/#position-lists
    - `subsequence-matching#lexicographically-smallest` 辞書順最小の部分列（残りで足りる範囲の最小の文字を選ぶ）（水）：https://yuukougun.github.io/kyopro-atlas/string/subsequence-matching/#lexicographically-smallest
    - `subsequence-matching#repeated-string` 繰り返した文字列の部分列（文字ごとの累積個数で位置を飛ばす）（青）：https://yuukougun.github.io/kyopro-atlas/string/subsequence-matching/#repeated-string

## ローリングハッシュ（rolling-hash） {#rolling-hash}

- id：`rolling-hash`　レベル：水　段階：reviewed　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/string/rolling-hash/
- 別名：ロリハ、多項式ハッシュ、Rabin-Karp、文字列のハッシュ、部分文字列のハッシュ、ハッシュのセグ木、rolling hash
- 種類：文字列、ハッシュ・乱択
- 前提：`mod-arithmetic`、`prefix-sum`、`string-basics`
- ACL：`segtree`
- サイン：
    - 言い回し：部分文字列どうしが等しいかを大量に判定する
    - 言い回し：重ならずに 2 回現れる部分文字列の最大の長さ
    - 言い回し：1 文字の更新と、区間が回文か（一致するか）のクエリ
    - 制約：N ≤ 10&#94;5〜10&#94;6 で、任意の 2 区間の一致判定が Q ≤ 2×10&#94;5 回
- 節：
    - `rolling-hash#polynomial-hash` 多項式ハッシュと部分文字列の取り出し：https://yuukougun.github.io/kyopro-atlas/string/rolling-hash/#polynomial-hash
    - `rolling-hash#collision-bound` なぜ衝突しにくいか（0 でない多項式の根は次数以下）：https://yuukougun.github.io/kyopro-atlas/string/rolling-hash/#collision-bound
    - `rolling-hash#recommended-design` 推奨する設計：mod 2^61−1 と実行時に乱択した基数（理由は hash-safety）：https://yuukougun.github.io/kyopro-atlas/string/rolling-hash/#recommended-design
    - `rolling-hash#concat-and-reverse` 連結のハッシュと逆向きのハッシュ（回文判定）：https://yuukougun.github.io/kyopro-atlas/string/rolling-hash/#concat-and-reverse
    - `rolling-hash#hash-lcp-binary-search` ハッシュ＋二分探索：LCP・辞書順の比較・最長の繰り返し：https://yuukougun.github.io/kyopro-atlas/string/rolling-hash/#hash-lcp-binary-search
    - `rolling-hash#hash-segment-tree` セグ木に載せるハッシュ：（ハッシュ, B^長さ）の組で更新ありの一致・回文判定（青）：https://yuukougun.github.io/kyopro-atlas/string/rolling-hash/#hash-segment-tree
    - `rolling-hash#when-to-use` ハッシュで代用できる場面とできない場面（Z・Manacher・SA・畳み込みとの使い分け）：https://yuukougun.github.io/kyopro-atlas/string/rolling-hash/#when-to-use

## 集合・多重集合のハッシュ（hashing-for-sets） {#hashing-for-sets}

- id：`hashing-for-sets`　レベル：水　段階：reviewed　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/string/hashing-for-sets/
- 別名：Zobrist hashing、集合のハッシュ、多重集合のハッシュ、XOR ハッシュ、和のハッシュ、乱択ハッシュ、並べ替えて一致するか
- 種類：ハッシュ・乱択、累積和・差分
- 前提：`prefix-sum`、`bit-operations`
- サイン：
    - 言い回し：先頭 x 項の集合と先頭 y 項の集合が等しいか
    - 言い回し：2 つの区間を並べ替えると一致するか（多重集合として等しいか）
    - 言い回し：区間内の各値が偶数個（3 の倍数個）か・区間の積が平方数（立方数）か
    - 制約：N, Q ≤ 2×10^5 で区間の多重集合を毎回比べる
- 節：
    - `hashing-for-sets#random-values` 値ごとに乱数を割り当てる理由（値そのものを足すと、集合 1, 4 と 2, 3 が衝突する）：https://yuukougun.github.io/kyopro-atlas/string/hashing-for-sets/#random-values
    - `hashing-for-sets#xor-vs-sum` 集合は XOR、多重集合は和（XOR は同じ値 2 個で打ち消す）：https://yuukougun.github.io/kyopro-atlas/string/hashing-for-sets/#xor-vs-sum
    - `hashing-for-sets#prefix-hash` 接頭辞・区間のハッシュ（集合の接頭辞は初めて出た値だけ入れる）：https://yuukougun.github.io/kyopro-atlas/string/hashing-for-sets/#prefix-hash
    - `hashing-for-sets#with-fenwick` BIT と組んで点の更新に対応する：https://yuukougun.github.io/kyopro-atlas/string/hashing-for-sets/#with-fenwick
    - `hashing-for-sets#collision-and-rng` 衝突確率と乱数の作り方（mt19937_64）：https://yuukougun.github.io/kyopro-atlas/string/hashing-for-sets/#collision-and-rng
    - `hashing-for-sets#multiplicity-mod-k` 各値が偶数個・k の倍数個かの判定（指数 mod k を乱数で符号化）（黄）：https://yuukougun.github.io/kyopro-atlas/string/hashing-for-sets/#multiplicity-mod-k

## ハッシュの衝突と安全な設計（hash-safety） {#hash-safety}

- id：`hash-safety`　レベル：青　段階：reviewed　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/string/hash-safety/
- 別名：ハッシュの衝突確率、誕生日のパラドックス、mod 2^61-1、ハッシュの mod の選び方、anti-hash、ハッシュが落とされる、unordered_map の衝突、カスタムハッシュ、hash collision
- 種類：ハッシュ・乱択
- 前提：`rolling-hash`
- サイン：
    - 言い回し：ハッシュ値を set や map に大量に入れて重複を数える
    - 言い回し：1000 桁程度の巨大な数の積や和が一致するかを判定する
    - 制約：比べ合うハッシュが 10^5 個以上（組が 5×10^9 以上）
- 節：
    - `hash-safety#birthday-bound` 衝突確率の見積もり：比較の回数ではなく組の数（誕生日のパラドックス）：https://yuukougun.github.io/kyopro-atlas/string/hash-safety/#birthday-bound
    - `hash-safety#mod-2-64` mod 2^64 が破られる理由（Thue-Morse 列。奇数のどの基数でも長さ 1024 で衝突する）：https://yuukougun.github.io/kyopro-atlas/string/hash-safety/#mod-2-64
    - `hash-safety#recommended-design` 推奨する設計：mod 2^61−1・乱択した基数・除算を使わない剰余：https://yuukougun.github.io/kyopro-atlas/string/hash-safety/#recommended-design
    - `hash-safety#what-to-randomize` 多項式ハッシュは基数を、値のハッシュは mod（素数）を乱択する：https://yuukougun.github.io/kyopro-atlas/string/hash-safety/#what-to-randomize
    - `hash-safety#atcoder-tests` AtCoder で狙われる条件（事前に固定されたテストと、誰でも使う固定の選択）：https://yuukougun.github.io/kyopro-atlas/string/hash-safety/#atcoder-tests
    - `hash-safety#double-hashing` 二重ハッシュとの比較：https://yuukougun.github.io/kyopro-atlas/string/hash-safety/#double-hashing
    - `hash-safety#unordered-map` unordered_map への攻撃と、乱数を混ぜたカスタムハッシュ：https://yuukougun.github.io/kyopro-atlas/string/hash-safety/#unordered-map

## Z-algorithm（z-algorithm） {#z-algorithm}

- id：`z-algorithm`　レベル：水　段階：reviewed　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/string/z-algorithm/
- 別名：Z 法、Z 配列、Z function、拡張 KMP、z_algorithm、各位置からの最長共通接頭辞、巡回シフト、A+A の技
- 種類：文字列
- 前提：`string-basics`
- ACL：`z_algorithm`
- サイン：
    - 言い回し：各位置から、文字列の先頭と何文字一致するか
    - 言い回し：A を何回回転すると B になるか（円環状の文字列の一致）
    - 言い回し：T を S の接頭辞の連結で表す最小の個数
    - 言い回し：パターンの全出現位置
    - 制約：|S|, |T| ≤ 10^6 で、ずらし方ごとに比べる O(|S||T|) が間に合わない
- 節：
    - `z-algorithm#pattern-search` Z 配列の定義と、P＋区切り＋T によるパターン検索：https://yuukougun.github.io/kyopro-atlas/string/z-algorithm/#pattern-search
    - `z-algorithm#linear-time` なぜ O(N) か：Z-box の内側は値をコピーでき、比較のたびに右端が進む：https://yuukougun.github.io/kyopro-atlas/string/z-algorithm/#linear-time
    - `z-algorithm#acl` ACL の z_algorithm（先頭の値が n になる流儀・区切りの −1）：https://yuukougun.github.io/kyopro-atlas/string/z-algorithm/#acl
    - `z-algorithm#cyclic-shift` 巡回シフト：A+A の中で B を探す（回転 N 回を二重に数えない）：https://yuukougun.github.io/kyopro-atlas/string/z-algorithm/#cyclic-shift
    - `z-algorithm#period` 周期の判定：p が周期であることと Z 配列の値の関係：https://yuukougun.github.io/kyopro-atlas/string/z-algorithm/#period
    - `z-algorithm#reverse` 反転と連結する：後ろからの一致と回文の接尾辞：https://yuukougun.github.io/kyopro-atlas/string/z-algorithm/#reverse
    - `z-algorithm#prefix-extension` S＋区切り＋T で各位置から S の接頭辞が何文字続くか（DP の材料）（黄）：https://yuukougun.github.io/kyopro-atlas/string/z-algorithm/#prefix-extension

## KMP 法と文字列の周期（kmp） {#kmp}

- id：`kmp`　レベル：青　段階：reviewed　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/string/kmp/
- 別名：KMP、MP 法、Knuth-Morris-Pratt、失敗関数、prefix function、π 配列、border、最小周期、繰り返し単位
- 種類：文字列
- 前提：`string-basics`
- サイン：
    - 言い回し：接頭辞と接尾辞が一致する最長の長さ
    - 言い回し：最小周期・何かの繰り返しで書けるか
    - 言い回し：N の約数 M を周期に持つ文字列（表）を数える
    - 言い回し：文字が 1 つずつ来るたびに、パターンが現れたかを判定する
    - 制約：|S| ≤ 10^6 で、すべての接頭辞について周期や一致する長さを問う
- 節：
    - `kmp#failure-function` 失敗関数 π（border）の定義と添字の流儀：https://yuukougun.github.io/kyopro-atlas/string/kmp/#failure-function
    - `kmp#linear-time` なぜ O(N) か：照合長は 1 文字で高々 1 増え、ループで減る回数も合計 N 以下：https://yuukougun.github.io/kyopro-atlas/string/kmp/#linear-time
    - `kmp#matching` パターン照合：失敗したら π の値までずらす：https://yuukougun.github.io/kyopro-atlas/string/kmp/#matching
    - `kmp#mp-vs-kmp` MP と KMP の違い（競プロでは MP を KMP と呼ぶことが多い）：https://yuukougun.github.io/kyopro-atlas/string/kmp/#mp-vs-kmp
    - `kmp#border-chain` border の連鎖と全 border の列挙：https://yuukougun.github.io/kyopro-atlas/string/kmp/#border-chain
    - `kmp#string-period` 周期と繰り返し：最小周期と、繰り返しで書ける条件（弱周期定理）：https://yuukougun.github.io/kyopro-atlas/string/kmp/#string-period
    - `kmp#count-periodic` N の約数の周期を数える：約数ごとに数えて包除（メビウス）：https://yuukougun.github.io/kyopro-atlas/string/kmp/#count-periodic
    - `kmp#automaton` 照合オートマトン（状態×文字 → 次の状態）を表に埋める：https://yuukougun.github.io/kyopro-atlas/string/kmp/#automaton

## 回文の扱いと Manacher（palindrome） {#palindrome}

- id：`palindrome`　レベル：水　段階：reviewed　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/string/palindrome/
- 別名：回文、palindrome、回文判定、Manacher's algorithm、回文半径、中心から伸ばす、両端から作る
- 種類：文字列
- 前提：`string-basics`
- サイン：
    - 言い回し：回文にするための最小の操作回数（書き換え・一斉置換）
    - 言い回し：回文になる部分文字列の個数
    - 言い回し：グラフのウォークの文字列が回文になる最短の長さ
    - 言い回し：長さ K の回文を部分文字列に含まないように埋める方法の数
    - 制約：N ≤ 10^6 で、すべての中心（区間）について回文かを問う
- 節：
    - `palindrome#symmetric-pairs` 対称な位置の組を見る（Union-Find でまとめる・組ごとの寄与を数える）：https://yuukougun.github.io/kyopro-atlas/string/palindrome/#symmetric-pairs
    - `palindrome#expand-center` 中心から伸ばす O(N^2)（奇数長と偶数長の中心）：https://yuukougun.github.io/kyopro-atlas/string/palindrome/#expand-center
    - `palindrome#avoid-k-palindrome` 直前 K−1 文字を状態にした DP（長さ K の回文を作らない）：https://yuukougun.github.io/kyopro-atlas/string/palindrome/#avoid-k-palindrome
    - `palindrome#palindrome-path` グラフ上の回文：頂点の組を状態にして両端から BFS（出会う位置の偶奇）：https://yuukougun.github.io/kyopro-atlas/string/palindrome/#palindrome-path
    - `palindrome#build-outside-in` 外側から組み立てる（回文の式・約数）（青）：https://yuukougun.github.io/kyopro-atlas/string/palindrome/#build-outside-in
    - `palindrome#manacher` Manacher：各中心の最長回文半径を O(N) で（Z と同じく内側をコピーする）（青）：https://yuukougun.github.io/kyopro-atlas/string/palindrome/#manacher

## Trie（trie） {#trie}

- id：`trie`　レベル：水　段階：reviewed　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/string/trie/
- 別名：トライ木、接頭辞木、prefix tree、全ペアの LCP の和
- 種類：文字列、データ構造
- 前提：`string-basics`、`dfs`
- サイン：
    - 言い回し：全ペアの最長共通接頭辞（LCP）の長さの和
    - 言い回し：各文字列について、ほかの文字列との LCP の最大
    - 言い回し：ある文字列を接頭辞に持つ文字列の数（追加・削除あり）
    - 言い回し：数列（文字列）の集合を辞書順にたどる
    - 制約：文字列の個数が多く、長さの総和が 5×10^5 程度まで
- 節：
    - `trie#basic-operations` 節点・挿入・検索（子を配列で持つか map で持つか・節点数の上限）：https://yuukougun.github.io/kyopro-atlas/string/trie/#basic-operations
    - `trie#counts` 通過数と終端の印の区別：https://yuukougun.github.io/kyopro-atlas/string/trie/#counts
    - `trie#lcp-sum` 全ペアの LCP の和：節点ごとに C(通過数, 2) を足す（主客転倒）：https://yuukougun.github.io/kyopro-atlas/string/trie/#lcp-sum
    - `trie#sort-alternative` ソートして隣どうしの LCP を見る代用：https://yuukougun.github.io/kyopro-atlas/string/trie/#sort-alternative
    - `trie#dp-on-trie` Trie 上の DFS と、節点に値を持つ DP（青）：https://yuukougun.github.io/kyopro-atlas/string/trie/#dp-on-trie
    - `trie#expectation-on-trie` Trie 上の確率・期待値（黄）：https://yuukougun.github.io/kyopro-atlas/string/trie/#expectation-on-trie

## Aho-Corasick 法（aho-corasick） {#aho-corasick}

- id：`aho-corasick`　レベル：青　段階：reviewed　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/string/aho-corasick/
- 別名：AC オートマトン、失敗リンク、複数パターン照合、禁止語、Aho-Corasick algorithm
- 種類：文字列
- 前提：`trie`、`kmp`、`bfs`
- サイン：
    - 言い回し：多数のパターンそれぞれの、テキスト中の出現回数
    - 言い回し：どのパターンも含まない（すべて含む）文字列の数
    - 言い回し：禁止語を含まないように最少の文字を書き換える
    - 制約：パターンの長さの総和が 10&#94;5〜10&#94;6 で、パターンの個数も多い
- 節：
    - `aho-corasick#failure-links` Trie と失敗リンク（KMP の π を Trie に一般化したもの）：https://yuukougun.github.io/kyopro-atlas/string/aho-corasick/#failure-links
    - `aho-corasick#build` BFS 順に失敗リンクを張る理由と、全文字の遷移表の埋め方：https://yuukougun.github.io/kyopro-atlas/string/aho-corasick/#build
    - `aho-corasick#count-occurrences` 出現回数の集計：訪問回数を失敗リンクの木で葉から根へ足す（出現のたびにたどると遅い）：https://yuukougun.github.io/kyopro-atlas/string/aho-corasick/#count-occurrences
    - `aho-corasick#inherit-terminal` 終端の印を失敗リンク先から受け継ぐ：https://yuukougun.github.io/kyopro-atlas/string/aho-corasick/#inherit-terminal
    - `aho-corasick#as-automaton` 照合オートマトンとして使う（DP・行列累乗）：https://yuukougun.github.io/kyopro-atlas/string/aho-corasick/#as-automaton
    - `aho-corasick#forbidden-greedy` 禁止語の貪欲：一致したら書き換えて状態を根に戻す（黄）：https://yuukougun.github.io/kyopro-atlas/string/aho-corasick/#forbidden-greedy

## 照合オートマトン上の DP（string-automaton-dp） {#string-automaton-dp}

- id：`string-automaton-dp`　レベル：青　段階：reviewed　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/string/string-automaton-dp/
- 別名：オートマトン DP、KMP DP、Aho-Corasick 上の DP、照合状態の DP、禁止文字列、禁止部分文字列、automaton DP
- 種類：DP、文字列
- 前提：`kmp`、`matrix-power`
- サイン：
    - 言い回し：長さ N の文字列のうち、どのパターンも部分文字列に含まないものの数
    - 言い回し：与えられた文字列をすべて含む長さ L の文字列の数
    - 制約：N ≤ 10&#94;9〜10&#94;18 で、パターンの長さの総和が小さい
    - 制約：パターンの個数 ≤ 8 程度で、すべてを含むかを問う
    - 式の形：長さ i までの文字列の数を、末尾とパターンの先頭が何文字一致しているかで分けて持つ
- 節：
    - `string-automaton-dp#matching-state` 照合の状態とマルコフ性：https://yuukougun.github.io/kyopro-atlas/string/string-automaton-dp/#matching-state
    - `string-automaton-dp#kmp-automaton` KMP オートマトンの遷移表を前計算して DP する：https://yuukougun.github.io/kyopro-atlas/string/string-automaton-dp/#kmp-automaton
    - `string-automaton-dp#multiple-patterns` 複数パターンは Aho-Corasick 法（終端の印を受け継ぐ）：https://yuukougun.github.io/kyopro-atlas/string/string-automaton-dp/#multiple-patterns
    - `string-automaton-dp#contain-all` すべて含む：含んだパターンの集合を bit で持つ：https://yuukougun.github.io/kyopro-atlas/string/string-automaton-dp/#contain-all
    - `string-automaton-dp#matrix-power` N が巨大なとき：遷移行列の累乗・ダブリング：https://yuukougun.github.io/kyopro-atlas/string/string-automaton-dp/#matrix-power
    - `string-automaton-dp#why-not-inclusion-exclusion` 包除はどこで破綻するか（位置の重なりとパターンの集合）：https://yuukougun.github.io/kyopro-atlas/string/string-automaton-dp/#why-not-inclusion-exclusion

## Suffix Array と LCP 配列（suffix-array） {#suffix-array}

- id：`suffix-array`　レベル：黄　段階：reviewed　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/string/suffix-array/
- 別名：接尾辞配列、SA、LCP 配列、SA-IS、Kasai 法、suffix_array、lcp_array、異なる部分文字列の数
- 種類：文字列、データ構造
- 前提：`string-basics`、`binary-search`
- ACL：`suffix_array`、`lcp_array`
- サイン：
    - 言い回し：異なる部分文字列の個数
    - 言い回し：全接尾辞どうしの LCP の和
    - 言い回し：回転したものどうしの辞書順の大小を数える
    - 言い回し：部分文字列を辞書順に並べたときの K 番目
    - 制約：|S| ≤ 5×10^5 程度で全部分文字列を扱う
- 節：
    - `suffix-array#definition` SA と LCP 配列の定義（ACL の suffix_array・lcp_array。lcp の長さは N−1）：https://yuukougun.github.io/kyopro-atlas/string/suffix-array/#definition
    - `suffix-array#distinct-substrings` 異なる部分文字列の数 = N(N+1)/2 − Σlcp：https://yuukougun.github.io/kyopro-atlas/string/suffix-array/#distinct-substrings
    - `suffix-array#lcp-rmq` 任意の 2 接尾辞の LCP は LCP 配列の区間最小（Sparse Table）：https://yuukougun.github.io/kyopro-atlas/string/suffix-array/#lcp-rmq
    - `suffix-array#pattern-count` パターンの出現回数：SA 上の二分探索で範囲を求める：https://yuukougun.github.io/kyopro-atlas/string/suffix-array/#pattern-count
    - `suffix-array#lcp-sum` 全ペアの LCP の和：LCP 配列の上の単調スタック：https://yuukougun.github.io/kyopro-atlas/string/suffix-array/#lcp-sum
    - `suffix-array#concat-separator` 複数の文字列を連結するときの区切り（int の列と大きな値）：https://yuukougun.github.io/kyopro-atlas/string/suffix-array/#concat-separator
    - `suffix-array#rotations` 回転どうしの比較：S+S+T+T の SA：https://yuukougun.github.io/kyopro-atlas/string/suffix-array/#rotations
    - `suffix-array#kth-substring` 部分文字列の辞書順 K 番目（発展）：https://yuukougun.github.io/kyopro-atlas/string/suffix-array/#kth-substring
    - `suffix-array#build-your-own` 自作するなら：ダブリング O(N log^2 N) → O(N log N) → SA-IS：https://yuukougun.github.io/kyopro-atlas/string/suffix-array/#build-your-own

## Suffix Automaton と発展の文字列アルゴリズム（suffix-automaton） {#suffix-automaton}

- id：`suffix-automaton`　レベル：発展　段階：reviewed　type：overview
- URL：https://yuukougun.github.io/kyopro-atlas/string/suffix-automaton/
- 別名：SAM、接尾辞オートマトン、DAWG、回文木、eertree、Palindromic Tree、Lyndon 分解、Duval、最小回転、Run の列挙、Main-Lorentz、逆 Manacher、逆 Z
- 種類：文字列
- 前提：`suffix-array`
- サイン：
    - 言い回し：文字を 1 つずつ追加しながら、異なる部分文字列の数を答える
    - 言い回し：2 つの文字列の最長共通部分文字列
    - 言い回し：異なる回文の部分文字列の種類数と、それぞれの出現回数
    - 言い回し：辞書順最小の巡回シフト
    - 言い回し：Z 配列（回文半径）が与えられ、それを満たす文字列を作る
- 節：
    - `suffix-automaton#suffix-automaton` Suffix Automaton（状態数 2N−1 以下・遷移数 3N−4 以下。文字の追加に強い）：https://yuukougun.github.io/kyopro-atlas/string/suffix-automaton/#suffix-automaton
    - `suffix-automaton#palindromic-tree` 回文木（eertree）：https://yuukougun.github.io/kyopro-atlas/string/suffix-automaton/#palindromic-tree
    - `suffix-automaton#lyndon-factorization` Lyndon 分解（Duval）と最小回転：https://yuukougun.github.io/kyopro-atlas/string/suffix-automaton/#lyndon-factorization
    - `suffix-automaton#run-enumeration` Run の列挙（Main-Lorentz）：https://yuukougun.github.io/kyopro-atlas/string/suffix-automaton/#run-enumeration
    - `suffix-automaton#inverse-string-problems` 文字列アルゴリズムの逆問題（逆 Manacher・逆 Z）：https://yuukougun.github.io/kyopro-atlas/string/suffix-automaton/#inverse-string-problems
    - `suffix-automaton#others` そのほかの名前（2 次元ローリングハッシュ・Suffix Tree・Boyer-Moore の検索）：https://yuukougun.github.io/kyopro-atlas/string/suffix-automaton/#others
    - `suffix-automaton#library` ライブラリと Library Checker での確かめ方：https://yuukougun.github.io/kyopro-atlas/string/suffix-automaton/#library
