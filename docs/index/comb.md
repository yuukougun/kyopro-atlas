---
title: 数え上げ・確率・ゲームの詳細索引
type: generated
search:
  exclude: true
---

<!-- tools/gen_site.py が生成する。手で直さない -->

# 数え上げ・確率・ゲームの詳細索引

分野の全ページの id・URL・別名・サイン・種類・前提・節。全分野の1行の一覧と索引の版は https://yuukougun.github.io/kyopro-atlas/llms.txt にある。

## 和・積の法則と順列・組合せ（counting-basics） {#counting-basics}

- id：`counting-basics`　レベル：基礎　段階：reviewed　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/comb/counting-basics/
- 別名：和の法則、積の法則、円順列、重複順列、nPr、塗り分けの数、rule of product
- 種類：数え上げ
- サイン：
    - 言い回し：隣り合うもの（距離 2 以内のもの）が異なるように塗り分ける方法の数
    - 言い回し：円形に並べる・円環で最後と最初も隣り合う
    - 制約：N ≤ 10^18 で、答えが段階ごとの選択肢の数の積になる
    - 式の形：答えが K(K−1)^(N−1) のような累乗の積の形になる
- 節：
    - `counting-basics#sum-and-product` 和の法則と積の法則（積の法則が使える条件）：https://yuukougun.github.io/kyopro-atlas/comb/counting-basics/#sum-and-product
    - `counting-basics#permutations` 順列・組合せ・重複順列・円順列：https://yuukougun.github.io/kyopro-atlas/comb/counting-basics/#permutations
    - `counting-basics#coloring` 一列の塗り分けと円環の塗り分け：https://yuukougun.github.io/kyopro-atlas/comb/counting-basics/#coloring
    - `counting-basics#order-of-choice` 決める順番を変えて積の法則を使えるようにする：https://yuukougun.github.io/kyopro-atlas/comb/counting-basics/#order-of-choice
    - `counting-basics#twelvefold-cells` 写像 12 相の「玉も箱も区別する」マス（k^n と順列）：https://yuukougun.github.io/kyopro-atlas/comb/counting-basics/#twelvefold-cells

## 二項係数の意味と性質（binomial-coefficient） {#binomial-coefficient}

- id：`binomial-coefficient`　レベル：基礎　段階：reviewed　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/comb/binomial-coefficient/
- 別名：二項係数、nCr、パスカルの三角形、辞書順 K 番目の組合せ、組合せの順位、binomial coefficient
- 種類：数え上げ
- 前提：`counting-basics`
- サイン：
    - 言い回し：N 個から K 個を選ぶ方法の数
    - 言い回し：0 と 1 の列で 1 がちょうど K 個のもの
    - 言い回し：辞書順で K 番目の並べ方・与えられた並べ方が何番目か
    - 制約：N ≤ 60 程度で、mod を取らない正確な値を求める
- 節：
    - `binomial-coefficient#meanings` 3 つの意味（選ぶ・0/1 列・格子路）：https://yuukougun.github.io/kyopro-atlas/comb/binomial-coefficient/#meanings
    - `binomial-coefficient#pascal` パスカルの漸化式と対称性：https://yuukougun.github.io/kyopro-atlas/comb/binomial-coefficient/#pascal
    - `binomial-coefficient#out-of-range` 範囲の外の k（負や n 超え）を 0 とする約束：https://yuukougun.github.io/kyopro-atlas/comb/binomial-coefficient/#out-of-range
    - `binomial-coefficient#overflow` mod を取らないときの大きさとオーバーフロー：https://yuukougun.github.io/kyopro-atlas/comb/binomial-coefficient/#overflow
    - `binomial-coefficient#kth` 辞書順 K 番目の組合せと順位：https://yuukougun.github.io/kyopro-atlas/comb/binomial-coefficient/#kth

## 二項係数の前計算（binomial-precompute） {#binomial-precompute}

- id：`binomial-precompute`　レベル：基礎　段階：reviewed　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/comb/binomial-precompute/
- 別名：nCr mod p、階乗と逆階乗の表、fact と ifact、逆階乗、Combination テーブル、任意 mod の二項係数、Lucas の定理、nCr mod 2、Lucas's theorem
- 種類：数え上げ、整数論
- 前提：`binomial-coefficient`、`mod-inverse`
- ACL：`modint`
- サイン：
    - 制約：N ≤ 2×10^5 程度で C(n,k) を何度も求める
    - 制約：n ≤ 10^9 で k ≤ 10^6 程度
    - 言い回し：法 M が入力で与えられ、素数とは限らない
    - 言い回し：隣り合う 2 つから新しい値を作る操作を繰り返し、最後に残る値を求める（三角形・ピラミッド）
    - 言い回し：答えを mod 2・mod 3 など小さい素数で求める
- 節：
    - `binomial-precompute#fact-ifact` fact を前から、ifact を後ろから作る理由：https://yuukougun.github.io/kyopro-atlas/comb/binomial-precompute/#fact-ifact
    - `binomial-precompute#table-size` 表の大きさ（H+W・N+K・2N など）と範囲外の 0：https://yuukougun.github.io/kyopro-atlas/comb/binomial-precompute/#table-size
    - `binomial-precompute#large-n` n が巨大で k が小さいときは O(k) で求める：https://yuukougun.github.io/kyopro-atlas/comb/binomial-precompute/#large-n
    - `binomial-precompute#composite-mod` 法が素数でないとき：n が小さければパスカルの三角形で作る：https://yuukougun.github.io/kyopro-atlas/comb/binomial-precompute/#composite-mod
    - `binomial-precompute#lucas` 法が小さい素数で n ≥ p になるとき：Lucas の定理（青）：https://yuukougun.github.io/kyopro-atlas/comb/binomial-precompute/#lucas
    - `binomial-precompute#parity-pyramid` p = 2 では (n & k) == k、ピラミッドの係数を二項係数と見抜く（青）：https://yuukougun.github.io/kyopro-atlas/comb/binomial-precompute/#parity-pyramid
    - `binomial-precompute#exact` mod を取らない正確な値（掛けてから割る・\_\_int128）：https://yuukougun.github.io/kyopro-atlas/comb/binomial-precompute/#exact
    - `binomial-precompute#acl` ACL では modint998244353 の inv()・pow() で自作する：https://yuukougun.github.io/kyopro-atlas/comb/binomial-precompute/#acl

## 重複組合せ（stars-and-bars） {#stars-and-bars}

- id：`stars-and-bars`　レベル：基礎　段階：reviewed　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/comb/stars-and-bars/
- 別名：玉と仕切り、ₖHₙ、非負整数解の個数、隣り合わない選び方、stars and bars
- 種類：数え上げ
- 前提：`binomial-coefficient`
- サイン：
    - 言い回し：和が N になる非負（正）整数の組の個数
    - 言い回し：広義単調増加な列の個数
    - 言い回し：N 個から隣り合わない（間隔 d 以上の）K 個を選ぶ方法の数
    - 言い回し：区別のない玉を区別のある箱へ配る方法の数
- 節：
    - `stars-and-bars#stars-bars` 玉と仕切りの対応（非負解と正の解）：https://yuukougun.github.io/kyopro-atlas/comb/stars-and-bars/#stars-bars
    - `stars-and-bars#at-most` 「以下」は余りの変数を 1 つ足して等式にする：https://yuukougun.github.io/kyopro-atlas/comb/stars-and-bars/#at-most
    - `stars-and-bars#monotone` 広義単調な列との対応：https://yuukougun.github.io/kyopro-atlas/comb/stars-and-bars/#monotone
    - `stars-and-bars#gaps` 隣り合わない選び方・間隔 d 以上の選び方：https://yuukougun.github.io/kyopro-atlas/comb/stars-and-bars/#gaps
    - `stars-and-bars#applications` 場合分けしてから配る・素因数ごとに配る（水）：https://yuukougun.github.io/kyopro-atlas/comb/stars-and-bars/#applications

## 格子路の数え上げ（lattice-paths） {#lattice-paths}

- id：`lattice-paths`　レベル：基礎　段階：reviewed　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/comb/lattice-paths/
- 別名：格子路、グリッドの最短経路の数、障害物のある経路、lattice path
- 種類：数え上げ
- 前提：`binomial-precompute`
- サイン：
    - 言い回し：グリッドの左上から右下への最短路の数
    - 制約：H, W ≤ 10^5 のグリッドで、左上から右下への経路の数を求める
    - 言い回し：通れない長方形の領域がある経路の数
    - 言い回し：2 種類の移動を組み合わせて目的地へ行く方法の数
- 節：
    - `lattice-paths#basic` 基本：C(a+b, a) と R・U の列：https://yuukougun.github.io/kyopro-atlas/comb/lattice-paths/#basic
    - `lattice-paths#move-counts` 移動の種類を回数の組に直す：https://yuukougun.github.io/kyopro-atlas/comb/lattice-paths/#move-counts
    - `lattice-paths#forbidden-region` 禁止領域を避ける：境界を越える点で分類する（青）：https://yuukougun.github.io/kyopro-atlas/comb/lattice-paths/#forbidden-region
    - `lattice-paths#sum-of-paths` 経路数の総和と、二項係数の和を経路数として一括で求める（青）：https://yuukougun.github.io/kyopro-atlas/comb/lattice-paths/#sum-of-paths
    - `lattice-paths#independent-axes` 移動を軸ごとの回数に分けて独立にする（45 度回転）（青）：https://yuukougun.github.io/kyopro-atlas/comb/lattice-paths/#independent-axes

## 写像 12 相（twelvefold-way） {#twelvefold-way}

- id：`twelvefold-way`　レベル：—　段階：reviewed　type：hub
- URL：https://yuukougun.github.io/kyopro-atlas/comb/twelvefold-way/
- 別名：玉と箱、玉と箱の数え上げ、区別する・しない、twelvefold way
- 種類：案内、数え上げ
- 前提：`stars-and-bars`
- サイン：
    - 言い回し：区別しない箱（グループ）に分ける方法の数
    - 言い回し：玉（人・数）を箱（グループ・色）に配る方法の数
    - 言い回し：どの箱にも 1 個以上入れる・空の箱を許す
- 節：
    - `twelvefold-way#table` 12 マスの表と各マスの行き先：https://yuukougun.github.io/kyopro-atlas/comb/twelvefold-way/#table
    - `twelvefold-way#why-not-divide` 箱を区別しないと k! で割れない理由（空の箱）：https://yuukougun.github.io/kyopro-atlas/comb/twelvefold-way/#why-not-divide
    - `twelvefold-way#surjection` 全射のマス：二項係数の系統と包除の系統の合流：https://yuukougun.github.io/kyopro-atlas/comb/twelvefold-way/#surjection
    - `twelvefold-way#reading` 問題文から区別の有無と制限を読み取る：https://yuukougun.github.io/kyopro-atlas/comb/twelvefold-way/#reading

## 数え上げの考え方（counting-mindset） {#counting-mindset}

- id：`counting-mindset`　レベル：水　段階：reviewed　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/comb/counting-mindset/
- 別名：数え上げの基本方針、ちょうど 1 回数える、ちょうど＝以下の差、式で数えるか DP で数えるか
- 種類：数え上げ、考察
- 前提：`binomial-coefficient`
- サイン：
    - 言い回し：最大値（最小値）がちょうど K になるものの個数
    - 言い回し：すべての選び方についての〜の総和
    - 式の形：答えが「K 以下」の個数の差 f(K) − f(K−1) で書ける
- 節：
    - `counting-mindset#procedure` 数え上げの手順と「ちょうど 1 回」：https://yuukougun.github.io/kyopro-atlas/comb/counting-mindset/#procedure
    - `counting-mindset#formula-or-dp` 式で数えるか DP で数えるか：https://yuukougun.github.io/kyopro-atlas/comb/counting-mindset/#formula-or-dp
    - `counting-mindset#exactly-vs-at-most` 「ちょうど」を「以下」の差で数える：https://yuukougun.github.io/kyopro-atlas/comb/counting-mindset/#exactly-vs-at-most
    - `counting-mindset#contribution-with-binomial` 二項係数と組み合わせた寄与（残りの選び方を掛ける）（青）：https://yuukougun.github.io/kyopro-atlas/comb/counting-mindset/#contribution-with-binomial
    - `counting-mindset#verify-small` 小さいケースの全探索で式を検算する：https://yuukougun.github.io/kyopro-atlas/comb/counting-mindset/#verify-small

## 対応づけ・数える対象の言い換え（counting-bijection） {#counting-bijection}

- id：`counting-bijection`　レベル：青　段階：reviewed　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/comb/counting-bijection/
- 別名：全単射、1 対 1 対応、経路数に帰着、bijection、bijective proof
- 種類：数え上げ、考察
- 前提：`counting-mindset`、`stars-and-bars`、`lattice-paths`
- サイン：
    - 言い回し：単調な数列の個数
    - 言い回し：積（和）が決まった値になる数列の個数
    - 言い回し：途中で負にならない ±1 の列の個数
    - 式の形：二項係数の積の和を、1 つの二項係数（経路の数）に直したい
- 節：
    - `counting-bijection#bijection` 全単射なら個数が等しい（逆に戻せるかで検算する）：https://yuukougun.github.io/kyopro-atlas/comb/counting-bijection/#bijection
    - `counting-bijection#decompose` 素因数ごと・軸ごとに分けて独立な成分の積にする：https://yuukougun.github.io/kyopro-atlas/comb/counting-bijection/#decompose
    - `counting-bijection#to-lattice-paths` 格子路に帰着できないかを疑う：https://yuukougun.github.io/kyopro-atlas/comb/counting-bijection/#to-lattice-paths
    - `counting-bijection#classic-bijections` 括弧列と格子路、ラベル付き木と Prüfer 列：https://yuukougun.github.io/kyopro-atlas/comb/counting-bijection/#classic-bijections
    - `counting-bijection#non-injective` 単射でない対応は重複する：https://yuukougun.github.io/kyopro-atlas/comb/counting-bijection/#non-injective

## 順序を固定して数える（counting-fix-order） {#counting-fix-order}

- id：`counting-fix-order`　レベル：水　段階：reviewed　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/comb/counting-fix-order/
- 別名：相対順序の固定、ソートしてから数える、数える順番の工夫、n!/k!
- 種類：数え上げ、考察
- 前提：`counting-mindset`
- サイン：
    - 言い回し：A は B より先に来る、という順番の制約がある並べ方の数
    - 言い回し：選んだ K 個の最大値（最小値）の総和
    - 言い回し：木の頂点に、親が子より先になるように番号を振る方法の数
- 節：
    - `counting-fix-order#relative-order` 相対順序を固定する（n!/k!）：https://yuukougun.github.io/kyopro-atlas/comb/counting-fix-order/#relative-order
    - `counting-fix-order#sort-and-fix` ソートして最大・最小を固定する：https://yuukougun.github.io/kyopro-atlas/comb/counting-fix-order/#sort-and-fix
    - `counting-fix-order#bfs-order` 積の法則が使える順番で決める（BFS 順）：https://yuukougun.github.io/kyopro-atlas/comb/counting-fix-order/#bfs-order
    - `counting-fix-order#tree-order` 木の上の順番 n!/Π 部分木の大きさ（黄）：https://yuukougun.github.io/kyopro-atlas/comb/counting-fix-order/#tree-order
    - `counting-fix-order#vs-dp` 順序を状態に持つ DP（挿入 DP・bitDP）との使い分け：https://yuukougun.github.io/kyopro-atlas/comb/counting-fix-order/#vs-dp

## 重複の除き方（counting-dedup） {#counting-dedup}

- id：`counting-dedup`　レベル：青　段階：reviewed　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/comb/counting-dedup/
- 別名：ダブルカウントを防ぐ、重複を除く、代表元、正規形、最左マッチ、最小添字規則
- 種類：数え上げ、DP、考察
- 前提：`counting-mindset`、`dp-state-design`
- サイン：
    - 言い回し：異なる〜の個数（種類数）
    - 言い回し：操作で作れる文字列（列）の種類数
    - 言い回し：S を部分列として含む文字列の個数
    - 言い回し：区別しないグループに分ける方法の数
    - 式の形：作り方（遷移の列）を数える式で、同じ対象が複数回数えられてしまう
- 節：
    - `counting-dedup#divide` 重複度が一定なら割る（同じものを含む順列・円順列）：https://yuukougun.github.io/kyopro-atlas/comb/counting-dedup/#divide
    - `counting-dedup#representative` 重複度が一定でないなら代表元を決める：https://yuukougun.github.io/kyopro-atlas/comb/counting-dedup/#representative
    - `counting-dedup#leftmost` 部分列として含む文字列は最も左の埋め込みで数える：https://yuukougun.github.io/kyopro-atlas/comb/counting-dedup/#leftmost
    - `counting-dedup#min-index` グループ分けは未使用の最小番号から決める：https://yuukougun.github.io/kyopro-atlas/comb/counting-dedup/#min-index
    - `counting-dedup#in-dp` DP の中で代表を決める（何も変えない操作を除く・最初に〜で場合分け・包除で重なりを引く）：https://yuukougun.github.io/kyopro-atlas/comb/counting-dedup/#in-dp

## Burnside の補題（burnside-lemma） {#burnside-lemma}

- id：`burnside-lemma`　レベル：発展　段階：reviewed　type：overview
- URL：https://yuukougun.github.io/kyopro-atlas/comb/burnside-lemma/
- 別名：Pólya の数え上げ定理、ネックレス、数珠順列、回転で同一視して数える、Burnside's lemma
- 種類：数え上げ
- 前提：`counting-dedup`
- サイン：
    - 言い回し：回転（反転）して一致するものは同じとみなす
    - 言い回し：数珠・ネックレスの塗り方の数
    - 言い回し：立方体の面の塗り方（書き込み方）の数
- 節：
    - `burnside-lemma#what` 何ができるか（同一視したものの数 = 動かないものの数の平均）：https://yuukougun.github.io/kyopro-atlas/comb/burnside-lemma/#what
    - `burnside-lemma#why-not-divide` なぜ単純に操作の数で割れないか：https://yuukougun.github.io/kyopro-atlas/comb/burnside-lemma/#why-not-divide
    - `burnside-lemma#necklace` 数珠（回転のみ）の式：https://yuukougun.github.io/kyopro-atlas/comb/burnside-lemma/#necklace
    - `burnside-lemma#by-period` 最短周期で分類して割る方法（約数包除の形）：https://yuukougun.github.io/kyopro-atlas/comb/burnside-lemma/#by-period
    - `burnside-lemma#cube` 立方体の 24 通りの回転：https://yuukougun.github.io/kyopro-atlas/comb/burnside-lemma/#cube
    - `burnside-lemma#library` 自作するときの要点と検証：https://yuukougun.github.io/kyopro-atlas/comb/burnside-lemma/#library

## 多項係数（multinomial-coefficient） {#multinomial-coefficient}

- id：`multinomial-coefficient`　レベル：水　段階：reviewed　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/comb/multinomial-coefficient/
- 別名：同じものを含む順列、並べ替えの数、グループ分けの数、多項定理、multinomial coefficient
- 種類：数え上げ
- 前提：`binomial-precompute`
- サイン：
    - 言い回し：文字を並べ替えてできる文字列の個数
    - 言い回し：各種類を使う個数が決まっている並べ方
    - 言い回し：大きさを指定してグループに分ける方法の数
- 節：
    - `multinomial-coefficient#meaning` 式の意味（全部区別した n! を入れ替えで割る）：https://yuukougun.github.io/kyopro-atlas/comb/multinomial-coefficient/#meaning
    - `multinomial-coefficient#product-of-binomials` 二項係数の積として順に場所を決める：https://yuukougun.github.io/kyopro-atlas/comb/multinomial-coefficient/#product-of-binomials
    - `multinomial-coefficient#dp-merge` DP で個数を決めながら合流ごとに二項係数を掛ける：https://yuukougun.github.io/kyopro-atlas/comb/multinomial-coefficient/#dp-merge
    - `multinomial-coefficient#insert-rest` 一部を先に並べて残りを挿入する（黄）：https://yuukougun.github.io/kyopro-atlas/comb/multinomial-coefficient/#insert-rest
    - `multinomial-coefficient#same-size-groups` 区別しない同じ大きさのグループを割る（黄）：https://yuukougun.github.io/kyopro-atlas/comb/multinomial-coefficient/#same-size-groups

## 二項係数の恒等式と和の公式（binomial-identities） {#binomial-identities}

- id：`binomial-identities`　レベル：青　段階：reviewed　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/comb/binomial-identities/
- 別名：二項定理、Vandermonde の恒等式、hockey stick、縦の和の公式、吸収公式、二項係数の和、binomial theorem、Vandermonde's identity
- 種類：数え上げ
- 前提：`lattice-paths`
- サイン：
    - 言い回し：長方形領域の各点への経路数の総和
    - 言い回し：偶数個（奇数個）を選ぶ方法の数の和
    - 言い回し：全ペアの (A_i + A_j)^x の和
    - 式の形：Σ の中に二項係数があり、N が大きく項ごとには足せない
- 節：
    - `binomial-identities#binomial-theorem` 二項定理、二項係数の和 2^n と交代和：https://yuukougun.github.io/kyopro-atlas/comb/binomial-identities/#binomial-theorem
    - `binomial-identities#parity-sum` 偶奇の条件つきの和：https://yuukougun.github.io/kyopro-atlas/comb/binomial-identities/#parity-sum
    - `binomial-identities#vandermonde` Vandermonde の恒等式（2 グループから合計 k 個）：https://yuukougun.github.io/kyopro-atlas/comb/binomial-identities/#vandermonde
    - `binomial-identities#hockey-stick` 縦の和（hockey stick）と経路数の総和：https://yuukougun.github.io/kyopro-atlas/comb/binomial-identities/#hockey-stick
    - `binomial-identities#absorption` 吸収公式 k C(n,k) = n C(n−1, k−1)：https://yuukougun.github.io/kyopro-atlas/comb/binomial-identities/#absorption
    - `binomial-identities#power-sums` 二項定理で累乗の和を展開する：https://yuukougun.github.io/kyopro-atlas/comb/binomial-identities/#power-sums
    - `binomial-identities#verify` 式変形の検算（小さいケース）：https://yuukougun.github.io/kyopro-atlas/comb/binomial-identities/#verify

## 二項係数の部分和（binomial-prefix-sum） {#binomial-prefix-sum}

- id：`binomial-prefix-sum`　レベル：発展　段階：reviewed　type：overview
- URL：https://yuukougun.github.io/kyopro-atlas/comb/binomial-prefix-sum/
- 別名：二項係数の累積和、Σ_{k≤K} C(n,k)
- 種類：数え上げ
- 前提：`binomial-precompute`
- サイン：
    - 式の形：答えの式に Σ_{k≤K} C(n,k) の形の和が、多くの (n, K) について現れる
- 節：
    - `binomial-prefix-sum#what` 何ができるか：https://yuukougun.github.io/kyopro-atlas/comb/binomial-prefix-sum/#what
    - `binomial-prefix-sum#update` n と K を 1 ずつ動かす更新式：https://yuukougun.github.io/kyopro-atlas/comb/binomial-prefix-sum/#update
    - `binomial-prefix-sum#order` Mo のように動かす順番を工夫する：https://yuukougun.github.io/kyopro-atlas/comb/binomial-prefix-sum/#order
    - `binomial-prefix-sum#with-inclusion-exclusion` 包除と組み合わせる例：https://yuukougun.github.io/kyopro-atlas/comb/binomial-prefix-sum/#with-inclusion-exclusion
    - `binomial-prefix-sum#library` 自作するときの要点：https://yuukougun.github.io/kyopro-atlas/comb/binomial-prefix-sum/#library

## 鏡像法とカタラン数（reflection-principle） {#reflection-principle}

- id：`reflection-principle`　レベル：黄　段階：reviewed　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/comb/reflection-principle/
- 別名：鏡像法、反射原理、カタラン数、ballot 数、Dyck path、正しい括弧列の個数、reflection principle、Catalan number
- 種類：数え上げ
- 前提：`lattice-paths`
- サイン：
    - 言い回し：どの接頭辞でも A の個数が B の個数（+K）以上
    - 言い回し：途中で負にならない ±1 の列の個数
    - 言い回し：正しい括弧列の個数
    - 言い回し：境界線を越えない経路の数
- 節：
    - `reflection-principle#reflection` 折り返しの全単射（最初に触れた点から先を折り返す）：https://yuukougun.github.io/kyopro-atlas/comb/reflection-principle/#reflection
    - `reflection-principle#complement-count` 越えない経路 = 全体 − 越える経路：https://yuukougun.github.io/kyopro-atlas/comb/reflection-principle/#complement-count
    - `reflection-principle#catalan` カタラン数と括弧列・二分木：https://yuukougun.github.io/kyopro-atlas/comb/reflection-principle/#catalan
    - `reflection-principle#offset` 折り返す線のずれ（+1）と条件を満たせないときの 0：https://yuukougun.github.io/kyopro-atlas/comb/reflection-principle/#offset
    - `reflection-principle#vs-dp` 括弧列を DP で数えるときとの使い分け：https://yuukougun.github.io/kyopro-atlas/comb/reflection-principle/#vs-dp
    - `reflection-principle#two-sided` 両端を越えない場合（発展）：https://yuukougun.github.io/kyopro-atlas/comb/reflection-principle/#two-sided

## LGV 補題（lgv-lemma） {#lgv-lemma}

- id：`lgv-lemma`　レベル：発展　段階：reviewed　type：overview
- URL：https://yuukougun.github.io/kyopro-atlas/comb/lgv-lemma/
- 別名：Lindström-Gessel-Viennot の補題、交わらない経路の組、LGV lemma
- 種類：数え上げ、線形代数・行列
- 前提：`lattice-paths`、`determinant`
- サイン：
    - 言い回し：K 本の経路が互いに交わらない組の個数
    - 言い回し：複数の駒が衝突せずに動く確率
- 節：
    - `lgv-lemma#what` 何ができるか（行列式で数える）：https://yuukougun.github.io/kyopro-atlas/comb/lgv-lemma/#what
    - `lgv-lemma#why-signed` 符号付きで数える理由（交わる組が打ち消し合う）：https://yuukougun.github.io/kyopro-atlas/comb/lgv-lemma/#why-signed
    - `lgv-lemma#with-lattice-paths` 格子路と組み合わせる：https://yuukougun.github.io/kyopro-atlas/comb/lgv-lemma/#with-lattice-paths
    - `lgv-lemma#bitdp` 行列式を bitDP で展開する例：https://yuukougun.github.io/kyopro-atlas/comb/lgv-lemma/#bitdp
    - `lgv-lemma#library` 計算量と自作するときの要点：https://yuukougun.github.io/kyopro-atlas/comb/lgv-lemma/#library

## 母関数の考え方（generating-function-counting） {#generating-function-counting}

- id：`generating-function-counting`　レベル：発展　段階：reviewed　type：overview
- URL：https://yuukougun.github.io/kyopro-atlas/comb/generating-function-counting/
- 別名：母関数、生成関数、数え上げの多項式表現、形式的冪級数で数える、generating function
- 種類：数え上げ、畳み込み・多項式
- 前提：`stars-and-bars`、`binomial-identities`
- ACL：`convolution`
- サイン：
    - 言い回し：各要素の選び方が独立で、個数（和）の合計に条件がある
    - 式の形：答えが (1 + x + … + x&#94;c)&#94;N のような式の特定の係数になる
    - 式の形：遷移が dp'[s] = dp[s] + dp[s − v] のように、値をずらして足す形になる
- 節：
    - `generating-function-counting#coefficients` 係数 = 数え方（積は独立な選択、累乗は繰り返し）：https://yuukougun.github.io/kyopro-atlas/comb/generating-function-counting/#coefficients
    - `generating-function-counting#formulas` 重複組合せ・上限つきの選び方を式で書く：https://yuukougun.github.io/kyopro-atlas/comb/generating-function-counting/#formulas
    - `generating-function-counting#dp-as-polynomial` DP の遷移を多項式の積・商として見る：https://yuukougun.github.io/kyopro-atlas/comb/generating-function-counting/#dp-as-polynomial
    - `generating-function-counting#to-fps` 多項式の演算（逆元・log・exp）は FPS のページへ：https://yuukougun.github.io/kyopro-atlas/comb/generating-function-counting/#to-fps
    - `generating-function-counting#library` ライブラリでの使い方：https://yuukougun.github.io/kyopro-atlas/comb/generating-function-counting/#library

## 包除原理（inclusion-exclusion） {#inclusion-exclusion}

- id：`inclusion-exclusion`　レベル：青　段階：reviewed　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/comb/inclusion-exclusion/
- 別名：包除、撹乱順列、完全順列、モンモール数、全射の数、min-max 包除、inclusion-exclusion principle、derangement
- 種類：数え上げ
- 前提：`counting-mindset`、`complement`、`bit-full-search`
- サイン：
    - 言い回し：すべて異なる・A_i ≠ B_i となるものの個数
    - 言い回し：どの禁止条件も満たさないものの個数
    - 言い回し：各色（各行・各列）を少なくとも 1 回使うものの個数
    - 制約：禁止条件が M ≤ 20 個程度
- 節：
    - `inclusion-exclusion#general` 一般形と、N(S) が「少なくとも」である理由：https://yuukougun.github.io/kyopro-atlas/comb/inclusion-exclusion/#general
    - `inclusion-exclusion#bit-enumeration` 条件の組を bit 全探索する（M ≤ 20）：https://yuukougun.github.io/kyopro-atlas/comb/inclusion-exclusion/#bit-enumeration
    - `inclusion-exclusion#symmetric` 対称なら破る個数 k ごとに足す：https://yuukougun.github.io/kyopro-atlas/comb/inclusion-exclusion/#symmetric
    - `inclusion-exclusion#derangement` 撹乱順列（完全順列）：https://yuukougun.github.io/kyopro-atlas/comb/inclusion-exclusion/#derangement
    - `inclusion-exclusion#surjection` 全射の数（各色を少なくとも 1 回使う）：https://yuukougun.github.io/kyopro-atlas/comb/inclusion-exclusion/#surjection
    - `inclusion-exclusion#when-to-use` 使い分け：余事象・包除 DP・約数包除：https://yuukougun.github.io/kyopro-atlas/comb/inclusion-exclusion/#when-to-use
    - `inclusion-exclusion#min-max` min-max 包除（全種類がそろうまでの期待値）（発展）：https://yuukougun.github.io/kyopro-atlas/comb/inclusion-exclusion/#min-max

## 包除 DP（inclusion-exclusion-dp） {#inclusion-exclusion-dp}

- id：`inclusion-exclusion-dp`　レベル：黄　段階：reviewed　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/comb/inclusion-exclusion-dp/
- 別名：符号付き DP、最初に踏む障害物で分類、障害物 DP、包除原理を DP に載せる
- 種類：数え上げ、DP
- 前提：`inclusion-exclusion`、`dp-basics`、`lattice-paths`
- サイン：
    - 制約：H, W ≤ 10^5 のグリッドに障害物が N ≤ 3000 個
    - 言い回し：禁止条件が列や木に沿って並ぶ数え上げ
    - 言い回し：|P_i − i| など、位置と値の差に制約がある順列の個数
    - 言い回し：隣り合う値が異なる数列の個数
- 節：
    - `inclusion-exclusion-dp#weighted-sum` 包除の和を「S を作る過程」の重みの和と見る：https://yuukougun.github.io/kyopro-atlas/comb/inclusion-exclusion-dp/#weighted-sum
    - `inclusion-exclusion-dp#first-obstacle` 最初に踏む障害物で分類する（ソート順と終点の扱い）：https://yuukougun.github.io/kyopro-atlas/comb/inclusion-exclusion-dp/#first-obstacle
    - `inclusion-exclusion-dp#count-violations` 違反の個数を状態に持ち、最後に符号と残りの自由度を掛ける：https://yuukougun.github.io/kyopro-atlas/comb/inclusion-exclusion-dp/#count-violations
    - `inclusion-exclusion-dp#equal-blocks` 「等しい」を区間にまとめる符号付き DP：https://yuukougun.github.io/kyopro-atlas/comb/inclusion-exclusion-dp/#equal-blocks
    - `inclusion-exclusion-dp#tree` 符号付きの木 DP（発展）：https://yuukougun.github.io/kyopro-atlas/comb/inclusion-exclusion-dp/#tree

## 約数包除（divisor-inclusion-exclusion） {#divisor-inclusion-exclusion}

- id：`divisor-inclusion-exclusion`　レベル：青　段階：reviewed　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/comb/divisor-inclusion-exclusion/
- 別名：約数系包除、gcd がちょうど g、倍数から引く、互いに素な組の数、gcd の総和
- 種類：数え上げ、整数論
- 前提：`counting-mindset`、`gcd-lcm`、`harmonic-sum`
- サイン：
    - 言い回し：gcd の総和を求める
    - 言い回し：gcd が 1 になる（互いに素な）組の個数
    - 言い回し：最小周期が d の列（文字列）の個数
    - 制約：値の上限 ≤ 10^6 程度で、すべての g について数える
- 節：
    - `divisor-inclusion-exclusion#partition` 「g の倍数」は gcd = g, 2g, 3g, … に排反に分かれる：https://yuukougun.github.io/kyopro-atlas/comb/divisor-inclusion-exclusion/#partition
    - `divisor-inclusion-exclusion#order` 大きい g から引く理由と計算量 O(M log M)：https://yuukougun.github.io/kyopro-atlas/comb/divisor-inclusion-exclusion/#order
    - `divisor-inclusion-exclusion#gcd-sum` gcd の総和・互いに素な組：https://yuukougun.github.io/kyopro-atlas/comb/divisor-inclusion-exclusion/#gcd-sum
    - `divisor-inclusion-exclusion#period` 周期の数え上げ（約数の周期で重複した分を引く）：https://yuukougun.github.io/kyopro-atlas/comb/divisor-inclusion-exclusion/#period
    - `divisor-inclusion-exclusion#perfect-powers` 累乗数の重複を指数ごとに除く：https://yuukougun.github.io/kyopro-atlas/comb/divisor-inclusion-exclusion/#perfect-powers
    - `divisor-inclusion-exclusion#vs-mobius` メビウス関数での書き方との対応：https://yuukougun.github.io/kyopro-atlas/comb/divisor-inclusion-exclusion/#vs-mobius

## 約数・倍数のゼータ変換とメビウス変換（zeta-mobius-divisor） {#zeta-mobius-divisor}

- id：`zeta-mobius-divisor`　レベル：青　段階：reviewed　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/comb/zeta-mobius-divisor/
- 別名：約数ゼータ変換、倍数ゼータ変換、約数メビウス変換、倍数メビウス変換、GCD 畳み込み、LCM 畳み込み、GCD convolution、LCM convolution
- 種類：数え上げ、整数論、畳み込み・多項式
- 前提：`divisor-inclusion-exclusion`、`sieve-eratosthenes`
- サイン：
    - 言い回し：各値 d について、d の倍数（約数）である要素の個数・和
    - 言い回し：Σ f(gcd(A_i, A_j)) や lcm の総和
    - 制約：値の上限 ≤ 10^6 程度で、gcd・lcm ごとに集計する
- 節：
    - `zeta-mobius-divisor#per-prime` 素数ごとの累積和で O(N log log N)：https://yuukougun.github.io/kyopro-atlas/comb/zeta-mobius-divisor/#per-prime
    - `zeta-mobius-divisor#inverse` 逆変換（メビウス変換）と回す向き：https://yuukougun.github.io/kyopro-atlas/comb/zeta-mobius-divisor/#inverse
    - `zeta-mobius-divisor#gcd-lcm-convolution` GCD 畳み込み・LCM 畳み込み：https://yuukougun.github.io/kyopro-atlas/comb/zeta-mobius-divisor/#gcd-lcm-convolution
    - `zeta-mobius-divisor#vs-subset` 部分集合のゼータ変換との対応（指数ベクトルの累積和）：https://yuukougun.github.io/kyopro-atlas/comb/zeta-mobius-divisor/#vs-subset

## メビウス関数とメビウス反転（mobius-function） {#mobius-function}

- id：`mobius-function`　レベル：黄　段階：reviewed　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/comb/mobius-function/
- 別名：メビウス関数、μ、メビウス反転、Möbius function、Mobius inversion
- 種類：数え上げ、整数論
- 前提：`divisor-inclusion-exclusion`、`sieve-eratosthenes`
- サイン：
    - 言い回し：gcd(i, j) = 1 となる組の個数・和
    - 言い回し：Σ gcd や Σ lcm を求める
    - 制約：N ≤ 10^6 程度で、μ を篩で前計算できる
- 節：
    - `mobius-function#definition` μ の定義と、約数についての和が n = 1 のときだけ 1 になる性質：https://yuukougun.github.io/kyopro-atlas/comb/mobius-function/#definition
    - `mobius-function#inversion` メビウス反転：https://yuukougun.github.io/kyopro-atlas/comb/mobius-function/#inversion
    - `mobius-function#gcd-one` 「gcd が 1」の条件の置き換えと和の入れ替え：https://yuukougun.github.io/kyopro-atlas/comb/mobius-function/#gcd-one
    - `mobius-function#sieve` μ を篩で作る：https://yuukougun.github.io/kyopro-atlas/comb/mobius-function/#sieve
    - `mobius-function#quotient` 商の列挙で同じ値の範囲を束ねる（発展）：https://yuukougun.github.io/kyopro-atlas/comb/mobius-function/#quotient
    - `mobius-function#vs-divisor-ie` 約数包除との書き換え：https://yuukougun.github.io/kyopro-atlas/comb/mobius-function/#vs-divisor-ie

## 部分集合の高速ゼータ変換とメビウス変換（zeta-mobius-subset） {#zeta-mobius-subset}

- id：`zeta-mobius-subset`　レベル：黄　段階：reviewed　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/comb/zeta-mobius-subset/
- 別名：高速ゼータ変換、高速メビウス変換、SOS DP、部分集合にわたる和、上位集合の和、OR 畳み込み、AND 畳み込み、zeta transform
- 種類：数え上げ、ビット演算、畳み込み・多項式
- 前提：`bit-full-search`、`prefix-sum-2d`
- サイン：
    - 制約：N ≤ 20 で、すべての部分集合（bit）ごとの和・最大を求める
    - 言い回し：A_i OR A_j が K の部分集合になる組
    - 言い回し：x ⊆ S となる x についての和を、すべての S で求める
- 節：
    - `zeta-mobius-subset#multidimensional` n 次元の累積和として見る（bit ごとに 1 軸ずつ）：https://yuukougun.github.io/kyopro-atlas/comb/zeta-mobius-subset/#multidimensional
    - `zeta-mobius-subset#loop-order` ループの順（bit を外側）：https://yuukougun.github.io/kyopro-atlas/comb/zeta-mobius-subset/#loop-order
    - `zeta-mobius-subset#inverse` メビウス変換（引き算で同じ順に回す）：https://yuukougun.github.io/kyopro-atlas/comb/zeta-mobius-subset/#inverse
    - `zeta-mobius-subset#superset` 上位集合の版：https://yuukougun.github.io/kyopro-atlas/comb/zeta-mobius-subset/#superset
    - `zeta-mobius-subset#or-and-convolution` OR 畳み込み・AND 畳み込み：https://yuukougun.github.io/kyopro-atlas/comb/zeta-mobius-subset/#or-and-convolution
    - `zeta-mobius-subset#top-two` 和の代わりに上位 2 つを持つ：https://yuukougun.github.io/kyopro-atlas/comb/zeta-mobius-subset/#top-two
    - `zeta-mobius-subset#vs-xor` XOR 畳み込みとの違い：https://yuukougun.github.io/kyopro-atlas/comb/zeta-mobius-subset/#vs-xor

## 置換の巡回分解（permutation-cycles） {#permutation-cycles}

- id：`permutation-cycles`　レベル：基礎　段階：reviewed　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/comb/permutation-cycles/
- 別名：巡回置換、サイクル分解、順列のサイクル、swap でソートする最小回数、置換の位数、cycle decomposition
- 種類：数え上げ、考察
- サイン：
    - 言い回し：順列を任意の 2 要素の swap でソートする最小回数
    - 言い回し：i → P_i をたどる・置換を何回も繰り返す
    - 言い回し：元に戻るまでの回数
    - 制約：置換を K ≤ 10^18 回繰り返した結果を求める
- 節：
    - `permutation-cycles#decompose` 巡回分解の作り方（訪問済みの印を付けてたどる）：https://yuukougun.github.io/kyopro-atlas/comb/permutation-cycles/#decompose
    - `permutation-cycles#min-swaps` swap で巡回が割れる・つながる：最小回数は N − 巡回の個数：https://yuukougun.github.io/kyopro-atlas/comb/permutation-cycles/#min-swaps
    - `permutation-cycles#vs-adjacent` 隣接 swap（転倒数）との違い：https://yuukougun.github.io/kyopro-atlas/comb/permutation-cycles/#vs-adjacent
    - `permutation-cycles#power` K 回の合成と元に戻る回数（巡回の長さの lcm）（青）：https://yuukougun.github.io/kyopro-atlas/comb/permutation-cycles/#power
    - `permutation-cycles#functional-graph` Functional graph との関係：https://yuukougun.github.io/kyopro-atlas/comb/permutation-cycles/#functional-graph

## 置換の偶奇（permutation-parity） {#permutation-parity}

- id：`permutation-parity`　レベル：青　段階：reviewed　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/comb/permutation-parity/
- 別名：偶置換、奇置換、置換の符号、swap の回数の偶奇、3 要素の巡回、sign of a permutation
- 種類：数え上げ、考察
- 前提：`permutation-cycles`、`parity`
- サイン：
    - 言い回し：ちょうど K 回（10^100 回など）の swap の後にありうる列
    - 言い回し：3 つの要素を巡回させる操作しかできない
    - 言い回し：2 つの列でそれぞれ 1 回ずつの swap を同時に行う
    - 言い回し：同じ値があるかどうかで答えが変わる
- 節：
    - `permutation-parity#sign` 置換の符号：swap の回数の偶奇は列によらない：https://yuukougun.github.io/kyopro-atlas/comb/permutation-parity/#sign
    - `permutation-parity#compute` 巡回の個数・転倒数から偶奇を求める：https://yuukougun.github.io/kyopro-atlas/comb/permutation-parity/#compute
    - `permutation-parity#three-cycle` 3 要素の巡回は偶置換：https://yuukougun.github.io/kyopro-atlas/comb/permutation-parity/#three-cycle
    - `permutation-parity#duplicates` 同じ値があれば偶奇を調整できる：https://yuukougun.github.io/kyopro-atlas/comb/permutation-parity/#duplicates
    - `permutation-parity#exactly-k` ちょうど K 回の操作で作れるもの：https://yuukougun.github.io/kyopro-atlas/comb/permutation-parity/#exactly-k

## 第 1 種スターリング数（stirling-first） {#stirling-first}

- id：`stirling-first`　レベル：発展　段階：reviewed　type：overview
- URL：https://yuukougun.github.io/kyopro-atlas/comb/stirling-first/
- 別名：巡回の個数ごとの順列の数、上昇階乗、Stirling numbers of the first kind
- 種類：数え上げ、畳み込み・多項式
- 前提：`permutation-cycles`
- ACL：`convolution`
- サイン：
    - 言い回し：巡回（サイクル）の個数ごとの順列の数
    - 言い回し：左から見える（最大値を更新する）位置の個数ごとの順列の数
    - 言い回し：最小の swap 回数ごとの並びの数
- 節：
    - `stirling-first#what` 何ができるか（巡回の個数ごとの数）：https://yuukougun.github.io/kyopro-atlas/comb/stirling-first/#what
    - `stirling-first#recurrence` 漸化式と上昇階乗：https://yuukougun.github.io/kyopro-atlas/comb/stirling-first/#recurrence
    - `stirling-first#records` 左から見える位置の数との対応：https://yuukougun.github.io/kyopro-atlas/comb/stirling-first/#records
    - `stirling-first#fps` FPS・分割統治で一度に求める：https://yuukougun.github.io/kyopro-atlas/comb/stirling-first/#fps
    - `stirling-first#library` ライブラリでの使い方：https://yuukougun.github.io/kyopro-atlas/comb/stirling-first/#library
    - `stirling-first#vs-second-kind` 第 2 種との違い：https://yuukougun.github.io/kyopro-atlas/comb/stirling-first/#vs-second-kind

## 第 2 種スターリング数とベル数（bell-number） {#bell-number}

- id：`bell-number`　レベル：青　段階：reviewed　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/comb/bell-number/
- 別名：集合の分割の数、第 2 種スターリング数、ベル数、S(n,k)、B_n、Stirling numbers of the second kind、Bell number
- 種類：数え上げ、DP
- 前提：`binomial-coefficient`、`dp-basics`
- サイン：
    - 制約：N ≤ 10〜12 で、グループ分けを全部試す
    - 言い回し：N 人を区別しない K 組に分ける（どの組も空でない）方法の数
- 節：
    - `bell-number#recurrence` S(n,k) の漸化式（最後の要素が新しい組を作るか既存の組に入るか）：https://yuukougun.github.io/kyopro-atlas/comb/bell-number/#recurrence
    - `bell-number#size` ベル数と全列挙の個数の見積もり（B_10 = 115975、B_12 = 4213597）：https://yuukougun.github.io/kyopro-atlas/comb/bell-number/#size
    - `bell-number#vs-subset-dp` bitDP・3^N の部分集合 DP との使い分け：https://yuukougun.github.io/kyopro-atlas/comb/bell-number/#vs-subset-dp

## 整数の分割と分割数（partition-number） {#partition-number}

- id：`partition-number`　レベル：黄　段階：reviewed　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/comb/partition-number/
- 別名：分割数、p(n,k)、分割の全列挙、巡回型、partition number、integer partition
- 種類：数え上げ、DP
- 前提：`recursive-enumeration`、`dp-basics`、`permutation-cycles`
- サイン：
    - 制約：N ≤ 50 程度で、長さ（個数）の組合せ（多重集合）を全部試す
    - 言い回し：和が N になる多重集合の個数
    - 言い回し：区別のない玉を区別のない箱へ配る方法の数
    - 言い回し：順列を巡回の長さの組ごとに分類して数える
- 節：
    - `partition-number#recurrence` 分割数の漸化式 p(n,k)：https://yuukougun.github.io/kyopro-atlas/comb/partition-number/#recurrence
    - `partition-number#enumeration` 降順の列だけを作る全列挙：https://yuukougun.github.io/kyopro-atlas/comb/partition-number/#enumeration
    - `partition-number#size` 全列挙の個数の見積もり（p(30) = 5604、p(50) = 204226）：https://yuukougun.github.io/kyopro-atlas/comb/partition-number/#size
    - `partition-number#cycle-type` 置換の巡回型ごとの数 N!/Π(ℓ^m_ℓ · m_ℓ!)：https://yuukougun.github.io/kyopro-atlas/comb/partition-number/#cycle-type
    - `partition-number#partition-dp` 分割数型の DP（発展）：https://yuukougun.github.io/kyopro-atlas/comb/partition-number/#partition-dp

## Young 図形とフック長公式（young-tableaux） {#young-tableaux}

- id：`young-tableaux`　レベル：発展　段階：reviewed　type：overview
- URL：https://yuukougun.github.io/kyopro-atlas/comb/young-tableaux/
- 別名：ヤング図形、標準タブロー、フック長公式、Robinson-Schensted 対応、Young tableau、hook length formula
- 種類：数え上げ
- 前提：`partition-number`
- サイン：
    - 言い回し：最長増加部分列と最長減少部分列の長さが指定された順列の個数
- 節：
    - `young-tableaux#what` 何ができるか：https://yuukougun.github.io/kyopro-atlas/comb/young-tableaux/#what
    - `young-tableaux#hook-length` フック長公式：https://yuukougun.github.io/kyopro-atlas/comb/young-tableaux/#hook-length
    - `young-tableaux#robinson-schensted` Robinson-Schensted 対応と LIS・LDS：https://yuukougun.github.io/kyopro-atlas/comb/young-tableaux/#robinson-schensted
    - `young-tableaux#partitions` 分割数との関係：https://yuukougun.github.io/kyopro-atlas/comb/young-tableaux/#partitions

## ラベル付き木の数え上げ（cayley-pruefer） {#cayley-pruefer}

- id：`cayley-pruefer`　レベル：黄　段階：reviewed　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/comb/cayley-pruefer/
- 別名：Cayley の公式、n^(n−2)、次数を指定した木の数、頂点にラベルのある木の個数、Cayley's formula
- 種類：数え上げ、木
- 前提：`multinomial-coefficient`、`tree-degree`
- サイン：
    - 言い回し：頂点にラベルのある木の個数
    - 言い回し：各頂点の次数を指定（制限）した木の個数
    - 言い回し：すべての木（すべての次数列）についての総和
- 節：
    - `cayley-pruefer#cayley` Cayley の公式 n^(n−2)（Prüfer 列の全単射から）：https://yuukougun.github.io/kyopro-atlas/comb/cayley-pruefer/#cayley
    - `cayley-pruefer#degree-sequence` 次数を指定した木の数（多項係数）：https://yuukougun.github.io/kyopro-atlas/comb/cayley-pruefer/#degree-sequence
    - `cayley-pruefer#sum-over-degrees` 次数列ごとに数えて総和を取る：https://yuukougun.github.io/kyopro-atlas/comb/cayley-pruefer/#sum-over-degrees
    - `cayley-pruefer#with-polynomials` 多項式（母関数）と組み合わせる（発展）：https://yuukougun.github.io/kyopro-atlas/comb/cayley-pruefer/#with-polynomials

## 連結なグラフの数え上げ（counting-labeled-graphs） {#counting-labeled-graphs}

- id：`counting-labeled-graphs`　レベル：黄　段階：reviewed　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/comb/counting-labeled-graphs/
- 別名：連結グラフの数え上げ、全体から非連結を引く、頂点 1 を含む成分で分類、条件を満たすグラフの個数
- 種類：数え上げ、DP
- 前提：`counting-mindset`、`binomial-precompute`、`subset-enumeration-dp`
- サイン：
    - 言い回し：条件を満たす（連結な）グラフの個数
    - 言い回し：辺の部分集合のうち、指定した頂点どうしが連結になるものの数
    - 制約：N ≤ 17 程度の頂点数で、条件を満たす辺の選び方を数える
    - 言い回し：最大の連結成分の大きさがちょうど L
- 節：
    - `counting-labeled-graphs#complement` 連結 = 全体 − 非連結：https://yuukougun.github.io/kyopro-atlas/comb/counting-labeled-graphs/#complement
    - `counting-labeled-graphs#component-of-1` 頂点 1 を含む成分で分類する（重複を防ぐ代表）：https://yuukougun.github.io/kyopro-atlas/comb/counting-labeled-graphs/#component-of-1
    - `counting-labeled-graphs#by-size` 大きさだけで決まるときは二項係数で頂点を選ぶ：https://yuukougun.github.io/kyopro-atlas/comb/counting-labeled-graphs/#by-size
    - `counting-labeled-graphs#subset-dp` 頂点集合ごとの DP（3^N）：https://yuukougun.github.io/kyopro-atlas/comb/counting-labeled-graphs/#subset-dp
    - `counting-labeled-graphs#bfs-layers` 距離の層ごとに頂点を配る：https://yuukougun.github.io/kyopro-atlas/comb/counting-labeled-graphs/#bfs-layers
    - `counting-labeled-graphs#exactly-l` 「ちょうど L」を「L 以下」の差で数える：https://yuukougun.github.io/kyopro-atlas/comb/counting-labeled-graphs/#exactly-l

## 確率の基本（probability-basics） {#probability-basics}

- id：`probability-basics`　レベル：基礎　段階：reviewed　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/comb/probability-basics/
- 別名：確率、条件付き確率、全確率の公式、独立と排反、期待値の定義、conditional probability
- 種類：確率・期待値
- 前提：`counting-basics`
- サイン：
    - 言い回し：確率を求めよ（絶対誤差・相対誤差 10^−6 まで許容）
    - 言い回し：サイコロ・コイン・カードを使う確率
    - 言い回し：最初に〜し、その結果に応じて〜するときの確率
- 節：
    - `probability-basics#ratio` 同様に確からしいとき：場合の数の比：https://yuukougun.github.io/kyopro-atlas/comb/probability-basics/#ratio
    - `probability-basics#independence` 独立・排反・余事象：https://yuukougun.github.io/kyopro-atlas/comb/probability-basics/#independence
    - `probability-basics#conditional` 条件付き確率と全確率の公式：https://yuukougun.github.io/kyopro-atlas/comb/probability-basics/#conditional
    - `probability-basics#expectation` 期待値の定義：https://yuukougun.github.io/kyopro-atlas/comb/probability-basics/#expectation
    - `probability-basics#precision` 浮動小数点の誤差と出力の桁数：https://yuukougun.github.io/kyopro-atlas/comb/probability-basics/#precision

## 幾何分布とコンプリートガチャ（coupon-collector） {#coupon-collector}

- id：`coupon-collector`　レベル：基礎　段階：reviewed　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/comb/coupon-collector/
- 別名：幾何分布、成功するまでの回数、1/p、コンプガチャ、クーポンコレクター、N H_N、coupon collector's problem、geometric distribution
- 種類：確率・期待値
- 前提：`probability-basics`
- サイン：
    - 言い回し：成功するまで繰り返すときの回数の期待値
    - 言い回し：すべての種類を集める（全頂点を訪れる）までの回数の期待値
    - 言い回し：〜が出るまでサイコロを振り続ける
- 節：
    - `coupon-collector#geometric` 幾何分布：E = 1 + (1 − p)E から 1/p：https://yuukougun.github.io/kyopro-atlas/comb/coupon-collector/#geometric
    - `coupon-collector#failures` 失敗の回数（1/p − 1）との違い：https://yuukougun.github.io/kyopro-atlas/comb/coupon-collector/#failures
    - `coupon-collector#staged` 段階に分けて幾何分布の期待値を足す（コンプガチャ）：https://yuukougun.github.io/kyopro-atlas/comb/coupon-collector/#staged

## 確率・期待値を mod 998244353 で答える（rational-mod） {#rational-mod}

- id：`rational-mod`　レベル：水　段階：reviewed　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/comb/rational-mod/
- 別名：有理数 mod、有理数の mod 表現、P × Q^(−1) mod p、確率 mod 998244353、分数を mod で表す
- 種類：確率・期待値、整数論
- 前提：`mod-inverse`、`probability-basics`
- ACL：`modint`
- サイン：
    - 言い回し：期待値（確率）を mod 998244353 で出力せよ
    - 言い回し：求める値は有理数で表せ、既約分数 P/Q について R × Q ≡ P となる R を出力する
    - 言い回し：確率が p% で与えられる
- 節：
    - `rational-mod#why` なぜ有理数を mod で表してよいか（逆元と四則の保存）：https://yuukougun.github.io/kyopro-atlas/comb/rational-mod/#why
    - `rational-mod#all-mod` 途中の計算をすべて mod で行う：https://yuukougun.github.io/kyopro-atlas/comb/rational-mod/#all-mod
    - `rational-mod#percent` 確率 p% は p × 100^(−1) として入れる：https://yuukougun.github.io/kyopro-atlas/comb/rational-mod/#percent
    - `rational-mod#no-compare` mod の値では大小比較できない（最適戦略は実数で比べる）：https://yuukougun.github.io/kyopro-atlas/comb/rational-mod/#no-compare
    - `rational-mod#zero-denominator` 分母が 0 になる式変形に注意する：https://yuukougun.github.io/kyopro-atlas/comb/rational-mod/#zero-denominator
    - `rational-mod#reconstruct` 検算：出力を分数に戻す（有理数復元）：https://yuukougun.github.io/kyopro-atlas/comb/rational-mod/#reconstruct

## 期待値の線形性と指示確率変数（linearity-of-expectation） {#linearity-of-expectation}

- id：`linearity-of-expectation`　レベル：水　段階：reviewed　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/comb/linearity-of-expectation/
- 別名：期待値の線形性、和の期待値は期待値の和、指示確率変数、indicator、ペアごとの確率、総和と期待値の行き来、linearity of expectation
- 種類：確率・期待値
- 前提：`probability-basics`
- サイン：
    - 言い回し：〜の個数（種類数）の期待値
    - 言い回し：転倒数・連結成分の数などの期待値
    - 言い回し：ランダムな操作の後の値の総和の期待値
    - 言い回し：全パターンについての和を求め、総数で割る
- 節：
    - `linearity-of-expectation#linearity` 線形性と独立性（積は独立なら分かれる）：https://yuukougun.github.io/kyopro-atlas/comb/linearity-of-expectation/#linearity
    - `linearity-of-expectation#split` 量を和に分けて各部分の期待値を足す：https://yuukougun.github.io/kyopro-atlas/comb/linearity-of-expectation/#split
    - `linearity-of-expectation#linear-operations` 操作が期待値に線形に作用するなら期待値のまま追う：https://yuukougun.github.io/kyopro-atlas/comb/linearity-of-expectation/#linear-operations
    - `linearity-of-expectation#indicator` 指示確率変数：個数の期待値 = 確率の和：https://yuukougun.github.io/kyopro-atlas/comb/linearity-of-expectation/#indicator
    - `linearity-of-expectation#pairs` ペアごとの確率と対称性（青）：https://yuukougun.github.io/kyopro-atlas/comb/linearity-of-expectation/#pairs
    - `linearity-of-expectation#sum-vs-expectation` 総和と期待値の行き来：https://yuukougun.github.io/kyopro-atlas/comb/linearity-of-expectation/#sum-vs-expectation
    - `linearity-of-expectation#nonlinear` 線形性が使えない量（積・二乗・max）：https://yuukougun.github.io/kyopro-atlas/comb/linearity-of-expectation/#nonlinear

## 対称性で確率を求める（probability-symmetry） {#probability-symmetry}

- id：`probability-symmetry`　レベル：水　段階：reviewed　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/comb/probability-symmetry/
- 別名：どれも同じ確率、ランダムな順列に置き換える、2 状態に縮める
- 種類：確率・期待値、考察
- 前提：`probability-basics`
- サイン：
    - 言い回し：一様ランダムにシャッフルする
    - 言い回し：ランダムに 2 つを選んで入れ替える操作を K 回行う
    - 言い回し：残りから一様ランダムに 1 つずつ選ぶ
    - 言い回し：ランダムな順列での順位・転倒の期待値
- 節：
    - `probability-symmetry#symmetry` 入れ替えで移り合う事象は同じ確率：https://yuukougun.github.io/kyopro-atlas/comb/probability-symmetry/#symmetry
    - `probability-symmetry#two-states` 特別な 1 つとその他に縮める（2 状態）：https://yuukougun.github.io/kyopro-atlas/comb/probability-symmetry/#two-states
    - `probability-symmetry#random-permutation` 残りから一様に選ぶ = ランダムな順列：https://yuukougun.github.io/kyopro-atlas/comb/probability-symmetry/#random-permutation
    - `probability-symmetry#pairs` ペアの大小は確率 1/2：https://yuukougun.github.io/kyopro-atlas/comb/probability-symmetry/#pairs
    - `probability-symmetry#asymmetric` 対称でない要素（初期位置・特別な要素）に注意する：https://yuukougun.github.io/kyopro-atlas/comb/probability-symmetry/#asymmetric

## 確率 DP（probability-dp） {#probability-dp}

- id：`probability-dp`　レベル：水　段階：reviewed　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/comb/probability-dp/
- 別名：前向きに確率を配る、到達確率、分布を求める DP、ランダムウォーク、random walk
- 種類：確率・期待値、DP
- 前提：`probability-basics`、`dp-basics`
- ACL：`modint`
- サイン：
    - 言い回し：K 回の操作の後に〜である確率
    - 言い回し：どちらが先にゴールするかの確率
    - 言い回し：時刻 T に〜している確率
    - 言い回し：N 回ランダムに上下左右へ動いた後の位置
- 節：
    - `probability-dp#forward` 状態に到達する確率を前から配る（和が 1 の検算）：https://yuukougun.github.io/kyopro-atlas/comb/probability-dp/#forward
    - `probability-dp#state-design` 状態の設計：まとめる・上限で打ち切る・到達する値だけ持つ：https://yuukougun.github.io/kyopro-atlas/comb/probability-dp/#state-design
    - `probability-dp#by-time` 時刻ごとに配る：https://yuukougun.github.io/kyopro-atlas/comb/probability-dp/#by-time
    - `probability-dp#vs-expected-value-dp` 期待値 DP との使い分け（前向きと後ろ向き）：https://yuukougun.github.io/kyopro-atlas/comb/probability-dp/#vs-expected-value-dp
    - `probability-dp#random-walk` ランダムウォークと二項係数（青）：https://yuukougun.github.io/kyopro-atlas/comb/probability-dp/#random-walk
    - `probability-dp#matrix-power` 同じ遷移を多数回行うときは行列累乗へ（黄）：https://yuukougun.github.io/kyopro-atlas/comb/probability-dp/#matrix-power

## 期待値 DP（expected-value-dp） {#expected-value-dp}

- id：`expected-value-dp`　レベル：水　段階：reviewed　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/comb/expected-value-dp/
- 別名：後ろから決める期待値、残りの期待値、全期待値の公式、自己ループ、振り直し、移項して解く、選択は max・偶然は平均
- 種類：確率・期待値、DP
- 前提：`linearity-of-expectation`、`dp-order`
- ACL：`modint`
- サイン：
    - 言い回し：〜になるまでの操作回数の期待値
    - 言い回し：終わるまでにかかる費用の期待値
    - 言い回し：出た目が〜なら振り直し・確率 p で何も起きない
    - 制約：状態数 N ≤ 10^5 程度で、各状態の遷移が少数（または区間）
    - 式の形：E[s] が、s から 1 手で移る状態の E の平均に定数を足した式になる
- 節：
    - `expected-value-dp#total-expectation` 全期待値の公式（最初の一手で場合分け）：https://yuukougun.github.io/kyopro-atlas/comb/expected-value-dp/#total-expectation
    - `expected-value-dp#why-backward` なぜ後ろ向きか（終状態が 0 の境界条件）：https://yuukougun.github.io/kyopro-atlas/comb/expected-value-dp/#why-backward
    - `expected-value-dp#state-design` 状態の設計：区別しない・個数の組にする：https://yuukougun.github.io/kyopro-atlas/comb/expected-value-dp/#state-design
    - `expected-value-dp#order` 計算順序とメモ化再帰：https://yuukougun.github.io/kyopro-atlas/comb/expected-value-dp/#order
    - `expected-value-dp#self-loop` 自己ループの移項 E = (c + Σ …)/(1 − p)：https://yuukougun.github.io/kyopro-atlas/comb/expected-value-dp/#self-loop
    - `expected-value-dp#choice` 選択がある期待値：選択は max、偶然は平均：https://yuukougun.github.io/kyopro-atlas/comb/expected-value-dp/#choice
    - `expected-value-dp#prefix-sum` 遷移を累積和でまとめる（青）：https://yuukougun.github.io/kyopro-atlas/comb/expected-value-dp/#prefix-sum
    - `expected-value-dp#vs-probability-dp` 前向きの確率 DP との使い分け：https://yuukougun.github.io/kyopro-atlas/comb/expected-value-dp/#vs-probability-dp

## 最適戦略の期待値（optimal-strategy-expectation） {#optimal-strategy-expectation}

- id：`optimal-strategy-expectation`　レベル：黄　段階：reviewed　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/comb/optimal-strategy-expectation/
- 別名：最適停止、expectimax、期待値の最大化、optimal stopping
- 種類：確率・期待値、DP
- 前提：`expected-value-dp`
- サイン：
    - 言い回し：最適に行動したときの期待値（勝率）
    - 言い回し：好きなタイミングでやめられる・最初からやり直せる
    - 言い回し：どれを残すか（どれを選ぶか）を選びながら進む
- 節：
    - `optimal-strategy-expectation#state-design` 残すもの・知っている情報を状態にする：https://yuukougun.github.io/kyopro-atlas/comb/optimal-strategy-expectation/#state-design
    - `optimal-strategy-expectation#stopping` 止めるタイミングを選ぶ（相手の得点の分布と比べる）：https://yuukougun.github.io/kyopro-atlas/comb/optimal-strategy-expectation/#stopping
    - `optimal-strategy-expectation#compare-real` 比較は実数で、答えは mod で（比較できない落とし穴）：https://yuukougun.github.io/kyopro-atlas/comb/optimal-strategy-expectation/#compare-real
    - `optimal-strategy-expectation#guess-answer` やり直しがあるときは答えを仮定して二分探索する：https://yuukougun.github.io/kyopro-atlas/comb/optimal-strategy-expectation/#guess-answer
    - `optimal-strategy-expectation#vs-max` 「最大値の期待値」との違い：https://yuukougun.github.io/kyopro-atlas/comb/optimal-strategy-expectation/#vs-max

## 閉路のある期待値（expectation-linear-equations） {#expectation-linear-equations}

- id：`expectation-linear-equations`　レベル：青　段階：reviewed　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/comb/expectation-linear-equations/
- 別名：期待値の方程式、a + bX の形で持つ、吸収マルコフ連鎖、閉路のある DP、振り出しに戻る、absorbing Markov chain
- 種類：確率・期待値、DP、線形代数・行列
- 前提：`expected-value-dp`
- ACL：`modint`
- サイン：
    - 言い回し：振り出し（スタート）に戻るマスがある
    - 言い回し：円形に並んだ人が順番に〜する
    - 言い回し：無限に続く可能性がある
    - 言い回し：2 人が交互に繰り返し、決着がつくまで続ける
- 節：
    - `expectation-linear-equations#generalize` 自己ループの移項の一般化（戻る先が 1 か所）：https://yuukougun.github.io/kyopro-atlas/comb/expectation-linear-equations/#generalize
    - `expectation-linear-equations#unknown` 未知数を 1 つ残して a + bX で運ぶ：https://yuukougun.github.io/kyopro-atlas/comb/expectation-linear-equations/#unknown
    - `expectation-linear-equations#cycle` 円環状の依存を 1 周させて閉じる：https://yuukougun.github.io/kyopro-atlas/comb/expectation-linear-equations/#cycle
    - `expectation-linear-equations#geometric-series` 等比級数で閉じる（交互に繰り返す）：https://yuukougun.github.io/kyopro-atlas/comb/expectation-linear-equations/#geometric-series
    - `expectation-linear-equations#linear-system` 一般の連立方程式（掃き出し法は math へ）：https://yuukougun.github.io/kyopro-atlas/comb/expectation-linear-equations/#linear-system
    - `expectation-linear-equations#infinite` b = 1 のとき（期待値が無限大）：https://yuukougun.github.io/kyopro-atlas/comb/expectation-linear-equations/#infinite

## 期待値と確率の変換（expectation-tail-sum） {#expectation-tail-sum}

- id：`expectation-tail-sum`　レベル：黄　段階：reviewed　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/comb/expectation-tail-sum/
- 別名：E[X] = Σ P(X ≥ k)、tail sum、期待値と確率の行き来、最大値の期待値、K 番目の値の期待値
- 種類：確率・期待値
- 前提：`linearity-of-expectation`、`counting-mindset`
- サイン：
    - 言い回し：最大値（最小値・K 番目の値）の期待値
    - 言い回し：〜がそろうまでに取り出す回数の期待値
    - 制約：値の範囲 M ≤ 5000 程度で、各 k について P(X ≥ k) を数える
- 節：
    - `expectation-tail-sum#identity` X を「X ≥ k」の個数の和に分けて線形性を使う：https://yuukougun.github.io/kyopro-atlas/comb/expectation-tail-sum/#identity
    - `expectation-tail-sum#kth-value` 最大値・K 番目の値：「すべて k 未満」の余事象：https://yuukougun.github.io/kyopro-atlas/comb/expectation-tail-sum/#kth-value
    - `expectation-tail-sum#waiting-time` 「〜になるまでの回数」= Σ P(k 回目までに終わらない)：https://yuukougun.github.io/kyopro-atlas/comb/expectation-tail-sum/#waiting-time
    - `expectation-tail-sum#continuous` 連続値の場合（積分）（発展）：https://yuukougun.github.io/kyopro-atlas/comb/expectation-tail-sum/#continuous
    - `expectation-tail-sum#exactly-vs-at-least` 「ちょうど」と「以上」の行き来：https://yuukougun.github.io/kyopro-atlas/comb/expectation-tail-sum/#exactly-vs-at-least

## 二乗の期待値・分散（expectation-of-square） {#expectation-of-square}

- id：`expectation-of-square`　レベル：黄　段階：reviewed　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/comb/expectation-of-square/
- 別名：二乗の期待値、分散、E[X^2]、確率・期待値・二乗を同時に運ぶ、variance
- 種類：確率・期待値
- 前提：`linearity-of-expectation`
- サイン：
    - 言い回し：〜の二乗の期待値
    - 言い回し：分散を求める（最小化する）
    - 言い回し：スコアの二乗の期待値
- 節：
    - `expectation-of-square#difference` 二乗の期待値と期待値の二乗の違い：https://yuukougun.github.io/kyopro-atlas/comb/expectation-of-square/#difference
    - `expectation-of-square#pairs` ペアに分ける（i = j の項を忘れない）：https://yuukougun.github.io/kyopro-atlas/comb/expectation-of-square/#pairs
    - `expectation-of-square#carry-three` (x + 1)^2 = x^2 + 2x + 1 で 3 つの量を同時に運ぶ：https://yuukougun.github.io/kyopro-atlas/comb/expectation-of-square/#carry-three
    - `expectation-of-square#variance` 分散と二乗和の関係：https://yuukougun.github.io/kyopro-atlas/comb/expectation-of-square/#variance

## 連続値の確率（continuous-probability） {#continuous-probability}

- id：`continuous-probability`　レベル：発展　段階：reviewed　type：overview
- URL：https://yuukougun.github.io/kyopro-atlas/comb/continuous-probability/
- 別名：連続確率、一様乱数、確率と積分、長さ・面積・角度の比、continuous probability
- 種類：確率・期待値
- 前提：`expectation-tail-sum`
- サイン：
    - 言い回し：実数を一様ランダムに選ぶ
    - 言い回し：円内（区間内）のランダムな点
- 節：
    - `continuous-probability#what` 何ができるか：https://yuukougun.github.io/kyopro-atlas/comb/continuous-probability/#what
    - `continuous-probability#ratio` 長さ・面積・角度の比：https://yuukougun.github.io/kyopro-atlas/comb/continuous-probability/#ratio
    - `continuous-probability#integral` 積分と tail sum：https://yuukougun.github.io/kyopro-atlas/comb/continuous-probability/#integral
    - `continuous-probability#piecewise` 区分的な多項式の積分：https://yuukougun.github.io/kyopro-atlas/comb/continuous-probability/#piecewise
    - `continuous-probability#library` 自作するときの要点：https://yuukougun.github.io/kyopro-atlas/comb/continuous-probability/#library

## ゲームの基本と勝敗の DP（game-basics） {#game-basics}

- id：`game-basics`　レベル：水　段階：reviewed　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/comb/game-basics/
- 別名：ゲーム DP、必勝法、必勝・必敗、勝ち局面・負け局面、二人零和有限確定完全情報ゲーム、手数の偶奇、真似戦略、ペアリング戦略
- 種類：ゲーム、DP
- 前提：`memoized-recursion`、`dp-order`
- サイン：
    - 言い回し：先手と後手が交互に操作し、両者が最適に行動したとき勝つのはどちらか
    - 言い回し：First / Second（Takahashi / Aoki）を出力する
    - 制約：カードの枚数 N ≤ 18 程度で、残りのカードの集合が局面になる
    - 言い回し：盤面（配置）が対称・同じものが偶数個ずつある
    - 言い回し：最終的な形が戦略によらず決まる
    - 言い回し：ジャッジと対戦する（インタラクティブ）
- 節：
    - `game-basics#assumptions` ゲームの前提（零和・有限・確定・完全情報）：https://yuukougun.github.io/kyopro-atlas/comb/game-basics/#assumptions
    - `game-basics#win-lose` 必勝・必敗の定義と後ろ向きに決まる理由：https://yuukougun.github.io/kyopro-atlas/comb/game-basics/#win-lose
    - `game-basics#game-dp` 勝敗の DP とメモ化再帰：https://yuukougun.github.io/kyopro-atlas/comb/game-basics/#game-dp
    - `game-basics#state-design` 状態の設計：集合（bitDP）・3^N・余り：https://yuukougun.github.io/kyopro-atlas/comb/game-basics/#state-design
    - `game-basics#turn` 手番で取れる手が違うときは手番を状態に入れる：https://yuukougun.github.io/kyopro-atlas/comb/game-basics/#turn
    - `game-basics#move-parity` 総手数の偶奇・不変量で決まるゲーム（最終形から数える）：https://yuukougun.github.io/kyopro-atlas/comb/game-basics/#move-parity
    - `game-basics#mirror-strategy` 真似戦略・ペアリング戦略（真似した手が合法かを確かめる）（青）：https://yuukougun.github.io/kyopro-atlas/comb/game-basics/#mirror-strategy
    - `game-basics#interactive` インタラクティブ：必勝戦略を実行する：https://yuukougun.github.io/kyopro-atlas/comb/game-basics/#interactive

## ミニマックス（minimax） {#minimax}

- id：`minimax`　レベル：水　段階：reviewed　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/comb/minimax/
- 別名：negamax、得点差 DP、自分 − 相手の最大化、得点差を最大化するゲーム、minimax
- 種類：ゲーム、DP
- 前提：`game-basics`
- サイン：
    - 言い回し：両者が最適に行動したときの得点（の差）
    - 言い回し：太郎は X − Y を最大化し、次郎は最小化する
    - 言い回し：列の両端から交互に取る
    - 言い回し：交互に駒を進めて得点を取り合う
- 節：
    - `minimax#negamax` 得点差を 1 本の式で書く（符号の反転）：https://yuukougun.github.io/kyopro-atlas/comb/minimax/#negamax
    - `minimax#max-min` max と min を手番で使い分ける書き方：https://yuukougun.github.io/kyopro-atlas/comb/minimax/#max-min
    - `minimax#states` 区間・グリッド・盤面を状態にする：https://yuukougun.github.io/kyopro-atlas/comb/minimax/#states
    - `minimax#greedy-fails` 貪欲が最適でない例：https://yuukougun.github.io/kyopro-atlas/comb/minimax/#greedy-fails
    - `minimax#tree` 木の上のゲーム（黄）：https://yuukougun.github.io/kyopro-atlas/comb/minimax/#tree
    - `minimax#binary-search` 答えを決め打ちして勝敗に直す（黄）：https://yuukougun.github.io/kyopro-atlas/comb/minimax/#binary-search

## Nim と XOR（nim） {#nim}

- id：`nim`　レベル：水　段階：reviewed　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/comb/nim/
- 別名：ニム、ニム和、石取りゲーム、上限つき Nim、逆形 Nim、Bouton の定理、misère Nim
- 種類：ゲーム、ビット演算
- 前提：`game-basics`、`bit-operations`
- サイン：
    - 言い回し：いくつかの山から石を取り合い、最後に取った人が勝ち
    - 言い回し：1 回に取れる個数に上限（範囲）がある
    - 言い回し：先手が勝てるように最初の配置を変えられるか
- 節：
    - `nim#bouton` Bouton の定理と証明の筋：https://yuukougun.github.io/kyopro-atlas/comb/nim/#bouton
    - `nim#winning-move` 勝つための手（XOR を 0 にする山の選び方）：https://yuukougun.github.io/kyopro-atlas/comb/nim/#winning-move
    - `nim#bounded` 上限つき（x mod (k+1)）・範囲つきの変種（青）：https://yuukougun.github.io/kyopro-atlas/comb/nim/#bounded
    - `nim#asymmetric` 先手と後手で取れる数が違うとき（青）：https://yuukougun.github.io/kyopro-atlas/comb/nim/#asymmetric
    - `nim#misere` 逆形 Nim（最後に取った方が負け）（発展）：https://yuukougun.github.io/kyopro-atlas/comb/nim/#misere
    - `nim#counting` 必勝局面の数え上げ（XOR 畳み込み）（発展）：https://yuukougun.github.io/kyopro-atlas/comb/nim/#counting

## Grundy 数と Sprague-Grundy の定理（grundy-number） {#grundy-number}

- id：`grundy-number`　レベル：青　段階：reviewed　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/comb/grundy-number/
- 別名：nimber、Sprague-Grundy の定理、ゲームの和、Grundy 数の周期性、Sprague-Grundy theorem、Grundy number
- 種類：ゲーム
- 前提：`nim`
- サイン：
    - 言い回し：複数の山（盤面）があり、どれか 1 つを選んで操作する
    - 言い回し：先手と後手の取れる手が同じ
    - 制約：山の大きさが 10^18 程度まであり、小さい山から全部の局面を調べられない
- 節：
    - `grundy-number#definition` mex と Grundy 数の定義：https://yuukougun.github.io/kyopro-atlas/comb/grundy-number/#definition
    - `grundy-number#as-nim` Grundy 数を Nim の山の大きさとみなせる理由：https://yuukougun.github.io/kyopro-atlas/comb/grundy-number/#as-nim
    - `grundy-number#sum` ゲームの和は XOR：https://yuukougun.github.io/kyopro-atlas/comb/grundy-number/#sum
    - `grundy-number#dp` Grundy 数を DP で求める（区間・2 種類の石）：https://yuukougun.github.io/kyopro-atlas/comb/grundy-number/#dp
    - `grundy-number#patterns` 規則を見つける：小さい局面の表と周期：https://yuukougun.github.io/kyopro-atlas/comb/grundy-number/#patterns
    - `grundy-number#limitations` 使えない場合（1 手で複数を動かす・非不偏）：https://yuukougun.github.io/kyopro-atlas/comb/grundy-number/#limitations

## 後退解析（game-retrograde-analysis） {#game-retrograde-analysis}

- id：`game-retrograde-analysis`　レベル：黄　段階：reviewed　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/comb/game-retrograde-analysis/
- 別名：retrograde analysis、引き分けのあるゲーム、閉路のあるグラフ上のゲーム、グラフ上のゲーム
- 種類：ゲーム、DP、グラフ探索
- 前提：`game-basics`、`bfs`
- サイン：
    - 言い回し：無限に続く場合は Draw（引き分け）を出力する
    - 言い回し：同じ局面が繰り返し現れうる
    - 言い回し：グラフ上でコマを動かすゲーム・しりとり
- 節：
    - `game-retrograde-analysis#why-not-memo` メモ化再帰が止まらない理由：https://yuukougun.github.io/kyopro-atlas/comb/game-retrograde-analysis/#why-not-memo
    - `game-retrograde-analysis#rules` 確定の規則（負けへ移れる → 勝ち、すべて勝ちへ → 負け）：https://yuukougun.github.io/kyopro-atlas/comb/game-retrograde-analysis/#rules
    - `game-retrograde-analysis#counter` 逆辺と、勝ちと確定していない行き先の数のカウンタ：https://yuukougun.github.io/kyopro-atlas/comb/game-retrograde-analysis/#counter
    - `game-retrograde-analysis#draw` 決まらない局面 = 引き分け：https://yuukougun.github.io/kyopro-atlas/comb/game-retrograde-analysis/#draw
    - `game-retrograde-analysis#weighted` 得点のあるゲームはダイクストラ法の要領で確定させる（発展）：https://yuukougun.github.io/kyopro-atlas/comb/game-retrograde-analysis/#weighted

## 非不偏ゲーム（partizan-games） {#partizan-games}

- id：`partizan-games`　レベル：発展　段階：reviewed　type：overview
- URL：https://yuukougun.github.io/kyopro-atlas/comb/partizan-games/
- 別名：超現実数、組合せゲーム理論、Hackenbush、partizan game、combinatorial game theory
- 種類：ゲーム
- 前提：`grundy-number`
- サイン：
    - 言い回し：先手と後手で動かせる駒や手が違う
    - 言い回し：独立な部分の和で勝敗を判定したい
- 節：
    - `partizan-games#what` 何ができるか：https://yuukougun.github.io/kyopro-atlas/comb/partizan-games/#what
    - `partizan-games#why-not-grundy` Grundy 数が使えない理由：https://yuukougun.github.io/kyopro-atlas/comb/partizan-games/#why-not-grundy
    - `partizan-games#surreal` 局面に数を割り当てて和を取る：https://yuukougun.github.io/kyopro-atlas/comb/partizan-games/#surreal
    - `partizan-games#tempo` 手数の貯金として見る：https://yuukougun.github.io/kyopro-atlas/comb/partizan-games/#tempo
    - `partizan-games#library` 計算量と自作するときの要点：https://yuukougun.github.io/kyopro-atlas/comb/partizan-games/#library
