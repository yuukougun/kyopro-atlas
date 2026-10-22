---
title: 基本テクニックの詳細索引
type: generated
search:
  exclude: true
---

<!-- tools/gen_site.py が生成する。手で直さない -->

# 基本テクニックの詳細索引

分野の全ページの id・URL・別名・サイン・種類・前提・節。全分野の1行の一覧と索引の版は https://yuukougun.github.io/kyopro-atlas/llms.txt にある。

## 計算量の見積もり（complexity-estimation） {#complexity-estimation}

- id：`complexity-estimation`　レベル：基礎　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/basics/complexity-estimation/
- 別名：計算量、オーダー、制約から手法を逆算する、制約から考える、TLE の見積もり、ならし計算量、償却計算量、定数倍、time complexity、amortized analysis
- 種類：計算量
- サイン：
    - 制約：N ≤ 8 / 20 / 40 / 400 / 5000 / 2×10^5 / 10^18 のような制約の大きさ
    - 制約：実行時間制限が 5 秒など長い（重めの全探索が想定されている）
    - 制約：Q ≤ 2×10^5 個のクエリ（1 回あたり O(log N) 以下が必要）
    - 制約：テストケースが T 個あり、N の総和が 2×10^5 以下
    - 式の形：while の中に for があって入れ子に見えるが、各要素は一度しか動かない
- 節：
    - `complexity-estimation#constraint-table` 制約 → 許される計算量 → 疑う手法の表：https://yuukougun.github.io/kyopro-atlas/basics/complexity-estimation/#constraint-table
    - `complexity-estimation#how-to-estimate` 見積もりの手順（ループの回数・log の数・定数倍・メモリ）：https://yuukougun.github.io/kyopro-atlas/basics/complexity-estimation/#how-to-estimate
    - `complexity-estimation#amortized` ならし計算量（ポインタが戻らない・各要素が一度入って一度出る）：https://yuukougun.github.io/kyopro-atlas/basics/complexity-estimation/#amortized
    - `complexity-estimation#harmonic-series` 調和級数の計算量（倍数の列挙）：https://yuukougun.github.io/kyopro-atlas/basics/complexity-estimation/#harmonic-series
    - `complexity-estimation#count-candidates` 候補の数で見積もる（階乗・ベル数・約数の個数の最大）：https://yuukougun.github.io/kyopro-atlas/basics/complexity-estimation/#count-candidates
    - `complexity-estimation#constant-factor` 定数倍（配列と set・map の差・メモリの連続性・bitset）（水）：https://yuukougun.github.io/kyopro-atlas/basics/complexity-estimation/#constant-factor
    - `complexity-estimation#multiple-testcases` 複数テストケースは合計（ΣN）で見積もる：https://yuukougun.github.io/kyopro-atlas/basics/complexity-estimation/#multiple-testcases

## bit 演算の基本と XOR の性質（bit-operations） {#bit-operations}

- id：`bit-operations`　レベル：基礎　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/basics/bit-operations/
- 別名：ビット演算、bitwise operations、popcount、submask、最下位ビット、XOR の打ち消し
- 種類：ビット演算
- サイン：
    - 言い回し：XOR・AND・OR が問題文に出る
    - 言い回し：自分以外の XOR・同じ値で打ち消す
    - 言い回し：2 進表記の 1 の個数
    - 制約：N ≤ 18 程度で、集合とその部分集合の組をすべて調べる（全体で 3^N）
- 節：
    - `bit-operations#operators` AND・OR・XOR・シフトと演算子の優先順位：https://yuukougun.github.io/kyopro-atlas/basics/bit-operations/#operators
    - `bit-operations#xor-properties` XOR の性質（打ち消し・a + b との関係・0〜n の XOR）：https://yuukougun.github.io/kyopro-atlas/basics/bit-operations/#xor-properties
    - `bit-operations#popcount` popcount・最下位 bit：https://yuukougun.github.io/kyopro-atlas/basics/bit-operations/#popcount
    - `bit-operations#submask` 部分集合の部分集合の列挙（3^N）：https://yuukougun.github.io/kyopro-atlas/basics/bit-operations/#submask

## bit ごとに独立に考える（bitwise-independence） {#bitwise-independence}

- id：`bitwise-independence`　レベル：水　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/basics/bitwise-independence/
- 別名：bit ごとの寄与、桁ごとに見る、bit ごとに分解、上位ビットから決める、XOR の和、bitwise decomposition
- 種類：ビット演算、考察
- 前提：`bit-operations`、`contribution`
- サイン：
    - 言い回し：全ペア・全区間の XOR の総和
    - 言い回し：AND・OR・XOR の最大化・最小化
    - 言い回し：x を選んで max(a_i xor x) を最小化する
    - 言い回し：a + b = a xor b（繰り上がりがない）
    - 制約：A_i < 2&#94;30〜2&#94;60 で、全ペア（N ≤ 2×10&#94;5）の値を集計する
- 節：
    - `bitwise-independence#per-bit-contribution` bit ごとの寄与（0 の個数 × 1 の個数 × 2^k）：https://yuukougun.github.io/kyopro-atlas/basics/bitwise-independence/#per-bit-contribution
    - `bitwise-independence#range-xor` 区間の XOR は累積 XOR の 0・1 の個数で：https://yuukougun.github.io/kyopro-atlas/basics/bitwise-independence/#range-xor
    - `bitwise-independence#top-down` 上の bit から決める貪欲（上限は桁 DP の考え方）：https://yuukougun.github.io/kyopro-atlas/basics/bitwise-independence/#top-down
    - `bitwise-independence#split-by-top-bit` 上位 bit で 2 つに分けて再帰する（青）：https://yuukougun.github.io/kyopro-atlas/basics/bitwise-independence/#split-by-top-bit
    - `bitwise-independence#addition` 足し算では使えない理由（繰り上がり）：https://yuukougun.github.io/kyopro-atlas/basics/bitwise-independence/#addition

## 全探索の設計（brute-force） {#brute-force}

- id：`brute-force`　レベル：基礎　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/basics/brute-force/
- 別名：全列挙、工夫した全探索、総当たり、何を全探索するか、候補が少ない、盤面の全探索、ポリオミノ、brute force
- 種類：全探索
- 前提：`complexity-estimation`
- サイン：
    - 言い回し：変数が 2〜3 個で、いくつか決めれば残りが計算で決まる
    - 言い回し：答えの候補（暗証番号・中心の座標など）が N によらず少ない
    - 制約：一方の次元だけ極端に小さい（H ≤ 8 など）
    - 制約：K ≤ 10^12 で約数を扱う（約数の個数は最大 6720）
    - 言い回し：小さい盤面を回転・平行移動して重ねる・敷き詰める
- 節：
    - `brute-force#what-to-enumerate` 何を全探索するか（2 つ決めて 3 つ目を計算する）：https://yuukougun.github.io/kyopro-atlas/basics/brute-force/#what-to-enumerate
    - `brute-force#decide-then-check` 決めてから整合性を確かめる：https://yuukougun.github.io/kyopro-atlas/basics/brute-force/#decide-then-check
    - `brute-force#small-candidates` 候補が少ないことに気づく（答えの側・小さい次元・約数の個数・log 回の収束）：https://yuukougun.github.io/kyopro-atlas/basics/brute-force/#small-candidates
    - `brute-force#half-enumeration` 片側を全探索して残りを速く求める（貪欲・二分探索・累積和）：https://yuukougun.github.io/kyopro-atlas/basics/brute-force/#half-enumeration
    - `brute-force#move-board` 盤面を動かして全部試す（回転・平行移動）（水）：https://yuukougun.github.io/kyopro-atlas/basics/brute-force/#move-board

## bit 全探索と順列全探索（bit-full-search） {#bit-full-search}

- id：`bit-full-search`　レベル：基礎　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/basics/bit-full-search/
- 別名：ビット全探索、部分集合の全列挙、2^N 全探索、3 進全探索、next_permutation、N! 全探索、bit brute force
- 種類：全探索、ビット演算
- 前提：`brute-force`、`bit-operations`
- サイン：
    - 制約：N ≤ 15〜20 で各要素を「選ぶ／選ばない」
    - 制約：N ≤ 8〜10 で並び順・割り当て・頂点の対応を決める
    - 言い回し：スイッチの on/off、区切る／区切らない
    - 制約：各要素が 3 択で N ≤ 12 程度（3^N 通り）
    - 言い回し：2 つのグラフが頂点の付け替えで一致するか
- 節：
    - `bit-full-search#bitmask` bit 全探索の書き方（mask の i ビット目で要素 i を選ぶ）：https://yuukougun.github.io/kyopro-atlas/basics/bit-full-search/#bitmask
    - `bit-full-search#base-k` k 進の全探索（3^N）：https://yuukougun.github.io/kyopro-atlas/basics/bit-full-search/#base-k
    - `bit-full-search#assume-and-check` 決めてから整合性を確かめる型：https://yuukougun.github.io/kyopro-atlas/basics/bit-full-search/#assume-and-check
    - `bit-full-search#half-greedy` 片側を bit で決めて残りは貪欲（水）：https://yuukougun.github.io/kyopro-atlas/basics/bit-full-search/#half-greedy
    - `bit-full-search#permutations` 順列全探索と next_permutation（昇順から始める・重複要素）：https://yuukougun.github.io/kyopro-atlas/basics/bit-full-search/#permutations

## 再帰による全列挙（recursive-enumeration） {#recursive-enumeration}

- id：`recursive-enumeration`　レベル：水　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/basics/recursive-enumeration/
- 別名：DFS による全列挙、バックトラック、枝刈り、組分けの全列挙、グループ分けの全列挙、集合分割の全列挙、backtracking
- 種類：全探索
- 前提：`bit-full-search`
- サイン：
    - 言い回し：条件を満たす数・列を小さい順にすべて作る
    - 制約：N ≤ 10〜12 人を組・グループに分ける（ベル数 B12 ≈ 4.2×10^6）
    - 制約：2N ≤ 16 人を 2 人組に分ける（(2N−1)!! 通り）
    - 言い回し：タイルの敷き詰め・パズルを途中で打ち切りながら試す
- 節：
    - `recursive-enumeration#skeleton` 再帰の骨組み（決める・進む・戻す）：https://yuukougun.github.io/kyopro-atlas/basics/recursive-enumeration/#skeleton
    - `recursive-enumeration#generate` 生成型（桁を 1 つずつ足す）：https://yuukougun.github.io/kyopro-atlas/basics/recursive-enumeration/#generate
    - `recursive-enumeration#partition` 組分け型（最小番号から決めて重複を防ぐ）：https://yuukougun.github.io/kyopro-atlas/basics/recursive-enumeration/#partition
    - `recursive-enumeration#pairing` ペア分け型：https://yuukougun.github.io/kyopro-atlas/basics/recursive-enumeration/#pairing
    - `recursive-enumeration#tiling` 敷き詰め型（左上の空きマスから置く）：https://yuukougun.github.io/kyopro-atlas/basics/recursive-enumeration/#tiling
    - `recursive-enumeration#pruning` 枝刈りと計算量の見積もり（葉の数 × 1 本あたり）：https://yuukougun.github.io/kyopro-atlas/basics/recursive-enumeration/#pruning
    - `recursive-enumeration#backtrack` 状態を戻し忘れない（バックトラック）：https://yuukougun.github.io/kyopro-atlas/basics/recursive-enumeration/#backtrack

## ソートで考える（sorting-techniques） {#sorting-techniques}

- id：`sorting-techniques`　レベル：基礎　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/basics/sorting-techniques/
- 別名：ソート、安定ソート、ペアのソート、sorting
- 種類：ソート・座標圧縮、貪欲
- サイン：
    - 言い回し：順番を自由に並べ替えてよい
    - 言い回し：安い順・効果の大きい順に取る
    - 言い回し：2 つの集合を 1 対 1 に対応させて距離の和を最小化する
    - 言い回し：成功率などの比率の大小で並べる
- 節：
    - `sorting-techniques#greedy-order` ソートで貪欲の順が決まる：https://yuukougun.github.io/kyopro-atlas/basics/sorting-techniques/#greedy-order
    - `sorting-techniques#matching-two-lists` 2 つの列を 1 対 1 に対応させる（両方ソートして順に組む）：https://yuukougun.github.io/kyopro-atlas/basics/sorting-techniques/#matching-two-lists
    - `sorting-techniques#strict-weak-ordering` 比較関数の要件（狭義の弱順序）：https://yuukougun.github.io/kyopro-atlas/basics/sorting-techniques/#strict-weak-ordering
    - `sorting-techniques#ratio-and-ties` 比率は掛け算で比べる・同点の順序（stable_sort）：https://yuukougun.github.io/kyopro-atlas/basics/sorting-techniques/#ratio-and-ties

## 二分探索（binary-search） {#binary-search}

- id：`binary-search`　レベル：基礎　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/basics/binary-search/
- 別名：二分法、lower_bound、upper_bound、めぐる式二分探索、partition_point、binary search
- 種類：二分探索
- 前提：`sorting-techniques`
- サイン：
    - 言い回し：ソート済みの列で x 以上の最初の位置・x 以下の個数
    - 言い回し：片方を固定して、もう片方が条件を満たす個数を数える
    - 言い回し：左右で最も近い要素を探す
    - 制約：N ≤ 2×10^5 個の値に対して、Q ≤ 2×10^5 個の位置・個数の質問がある
- 節：
    - `binary-search#meguru` めぐる式（ok と ng の不変条件・初期値は判定しない番兵）：https://yuukougun.github.io/kyopro-atlas/basics/binary-search/#meguru
    - `binary-search#lower-bound` lower_bound・upper_bound と個数の数え方：https://yuukougun.github.io/kyopro-atlas/basics/binary-search/#lower-bound
    - `binary-search#fix-one-side` 片方を固定してもう片方を二分探索する：https://yuukougun.github.io/kyopro-atlas/basics/binary-search/#fix-one-side
    - `binary-search#interactive` 質問で二分探索する（インタラクティブ問題へ）：https://yuukougun.github.io/kyopro-atlas/basics/binary-search/#interactive

## 答えで二分探索（binary-search-answer） {#binary-search-answer}

- id：`binary-search-answer`　レベル：基礎　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/basics/binary-search-answer/
- 別名：決め打ち二分探索、答えの二分探索、最小値の最大化、最大値の最小化、判定問題、実数の二分探索、判定 DP、二分探索と DP、binary search on the answer、parametric search
- 種類：二分探索
- 前提：`binary-search`
- サイン：
    - 言い回し：最小値を最大化する／最大値を最小化する
    - 言い回し：〜を満たす最大（最小）の X を求める
    - 言い回し：答えを実数で出力し、誤差 10^−6 まで許される
    - 制約：答えの範囲が 10&#94;9〜10&#94;18 と広い
    - 式の形：答えを X に固定すると、可否を貪欲・探索・DP で判定できる形になる
- 節：
    - `binary-search-answer#monotonicity` 判定の単調性を確かめる（「ちょうど K」は「K 以上」に直す）：https://yuukougun.github.io/kyopro-atlas/basics/binary-search-answer/#monotonicity
    - `binary-search-answer#minimax` 最大値の最小化・最小値の最大化：https://yuukougun.github.io/kyopro-atlas/basics/binary-search-answer/#minimax
    - `binary-search-answer#greedy-check` 判定を貪欲・探索で作る：https://yuukougun.github.io/kyopro-atlas/basics/binary-search-answer/#greedy-check
    - `binary-search-answer#dp-check` 判定を DP で作る（決め打ちごとに初期化し直す）（青）：https://yuukougun.github.io/kyopro-atlas/basics/binary-search-answer/#dp-check
    - `binary-search-answer#real-number` 実数の二分探索（反復回数を固定する）（水）：https://yuukougun.github.io/kyopro-atlas/basics/binary-search-answer/#real-number

## 座標圧縮（coordinate-compression） {#coordinate-compression}

- id：`coordinate-compression`　レベル：基礎　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/basics/coordinate-compression/
- 別名：座圧、値の圧縮、離散化、coordinate compression
- 種類：ソート・座標圧縮
- 前提：`binary-search`
- サイン：
    - 制約：値は 10^9 まであるが、個数は 2×10^5 以下
    - 言い回し：大小関係（順位）だけが重要
    - 式の形：値を配列の添字にしたいが、値の範囲が広すぎる
- 節：
    - `coordinate-compression#three-steps` sort → unique → lower_bound の 3 段：https://yuukougun.github.io/kyopro-atlas/basics/coordinate-compression/#three-steps
    - `coordinate-compression#intervals` 区間を扱うときは両端点を入れる：https://yuukougun.github.io/kyopro-atlas/basics/coordinate-compression/#intervals
    - `coordinate-compression#keep-original` 圧縮後の番号で長さを測らない（元の値を残す）：https://yuukougun.github.io/kyopro-atlas/basics/coordinate-compression/#keep-original
    - `coordinate-compression#with-ds` BIT・セグメント木・いもす法と組む：https://yuukougun.github.io/kyopro-atlas/basics/coordinate-compression/#with-ds
    - `coordinate-compression#vs-map` map で足りる場合との使い分け：https://yuukougun.github.io/kyopro-atlas/basics/coordinate-compression/#vs-map

## イベントソートと平面走査の基本（event-sort） {#event-sort}

- id：`event-sort`　レベル：水　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/basics/event-sort/
- 別名：イベントソート、開始と終了をイベントにする、event sorting
- 種類：ソート・座標圧縮、クエリ処理の工夫
- 前提：`sorting-techniques`
- サイン：
    - 言い回し：区間の開始・終了と、時刻のクエリが混ざる
    - 言い回し：x 座標も y 座標も大きい相手と組にする・数える
    - 言い回し：締め切りや有効期間がある
    - 言い回し：クエリを先に全部読んでよい
    - 制約：座標は 10^9 まで、区間とクエリは合わせて 2×10^5 個程度
- 節：
    - `event-sort#make-events` イベントの作り方と同じ座標での処理順：https://yuukougun.github.io/kyopro-atlas/basics/event-sort/#make-events
    - `event-sort#with-set` 集合（set・multiset）を更新しながら走査する：https://yuukougun.github.io/kyopro-atlas/basics/event-sort/#with-set
    - `event-sort#plane-sweep` 平面走査の基本（一方の座標で並べ、もう一方を集合で）：https://yuukougun.github.io/kyopro-atlas/basics/event-sort/#plane-sweep
    - `event-sort#to-data-structures` BIT・セグ木と組む平面走査へ（データ構造の章）：https://yuukougun.github.io/kyopro-atlas/basics/event-sort/#to-data-structures

## 累積和（prefix-sum） {#prefix-sum}

- id：`prefix-sum`　レベル：基礎　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/basics/prefix-sum/
- 別名：prefix sum、cumulative sum、累積 GCD、累積 XOR、累積 max、左右からの累積
- 種類：累積和・差分、区間クエリ
- サイン：
    - 言い回し：区間の和を何度も聞かれる
    - 言い回し：1 つだけ除いた（変えた）ときの値
    - 言い回し：円環上の区間
    - 制約：Q ≤ 2×10^5 個の区間和のクエリで、値の更新がない
- 節：
    - `prefix-sum#half-open` 半開区間と、先頭に 0 を置く約束：https://yuukougun.github.io/kyopro-atlas/basics/prefix-sum/#half-open
    - `prefix-sum#left-right` 左右からの累積（1 つ除いた gcd・max）：https://yuukougun.github.io/kyopro-atlas/basics/prefix-sum/#left-right
    - `prefix-sum#circular` 円環は 2 周分に伸ばす：https://yuukougun.github.io/kyopro-atlas/basics/prefix-sum/#circular
    - `prefix-sum#with-binary-search` 累積和の上で二分探索・尺取り：https://yuukougun.github.io/kyopro-atlas/basics/prefix-sum/#with-binary-search
    - `prefix-sum#next-tools` 値が更新されるなら BIT、静的な区間 min なら Sparse Table：https://yuukougun.github.io/kyopro-atlas/basics/prefix-sum/#next-tools

## 累積和と連想配列で区間を数える（prefix-sum-counting） {#prefix-sum-counting}

- id：`prefix-sum-counting`　レベル：基礎　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/basics/prefix-sum-counting/
- 別名：Zero-Sum Ranges、区間和が K、余りが等しい組を数える、累積和の mod、subarray sum equals K
- 種類：累積和・差分
- 前提：`prefix-sum`
- サイン：
    - 言い回し：和がちょうど K の区間の個数
    - 言い回し：和が M の倍数になる区間の個数
    - 制約：−10^9 ≤ A_i ≤ 10^9 のように負の値を含む
    - 式の形：区間の条件が S_r と S_l の関係（差が K・余りが等しい）に書き直せる
- 節：
    - `prefix-sum-counting#equal-k` S_r − S_l = K となる l を数える（S_0 を入れ忘れない）：https://yuukougun.github.io/kyopro-atlas/basics/prefix-sum-counting/#equal-k
    - `prefix-sum-counting#same-remainder` 余りが等しい組（M の倍数の区間・負の余りの正規化）：https://yuukougun.github.io/kyopro-atlas/basics/prefix-sum-counting/#same-remainder
    - `prefix-sum-counting#suffix` 後ろからの累積（数字列の倍数）：https://yuukougun.github.io/kyopro-atlas/basics/prefix-sum-counting/#suffix
    - `prefix-sum-counting#circular` 円環上の組を数える：https://yuukougun.github.io/kyopro-atlas/basics/prefix-sum-counting/#circular
    - `prefix-sum-counting#length-limited` 長さの制限付き（窓の中だけで数える）（青）：https://yuukougun.github.io/kyopro-atlas/basics/prefix-sum-counting/#length-limited
    - `prefix-sum-counting#vs-two-pointers` 尺取りとの使い分け（負の値）：https://yuukougun.github.io/kyopro-atlas/basics/prefix-sum-counting/#vs-two-pointers

## 2 次元累積和（prefix-sum-2d） {#prefix-sum-2d}

- id：`prefix-sum-2d`　レベル：水　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/basics/prefix-sum-2d/
- 別名：二次元累積和、2D prefix sum、長方形の和、3 次元累積和、多次元の累積和
- 種類：累積和・差分、区間クエリ
- 前提：`prefix-sum`
- サイン：
    - 言い回し：長方形領域の和・個数を何度も求める
    - 言い回し：正方形・長方形を全部試す
    - 言い回し：模様が周期的に敷き詰められた盤面
    - 制約：H, W ≤ 2000 程度のグリッドで領域の和を何度も求める
- 節：
    - `prefix-sum-2d#formula` 前計算の式と長方形の和（4 項の包除）：https://yuukougun.github.io/kyopro-atlas/basics/prefix-sum-2d/#formula
    - `prefix-sum-2d#fix-rows` 長方形を全部試す・行の組を固定して 1 次元に落とす：https://yuukougun.github.io/kyopro-atlas/basics/prefix-sum-2d/#fix-rows
    - `prefix-sum-2d#with-binary-search` 各左上から辺の長さを二分探索する：https://yuukougun.github.io/kyopro-atlas/basics/prefix-sum-2d/#with-binary-search
    - `prefix-sum-2d#periodic-board` 周期的な盤面（周期で分割する）：https://yuukougun.github.io/kyopro-atlas/basics/prefix-sum-2d/#periodic-board
    - `prefix-sum-2d#intervals-as-points` 区間を点 (l, r) と見て数える：https://yuukougun.github.io/kyopro-atlas/basics/prefix-sum-2d/#intervals-as-points
    - `prefix-sum-2d#higher-dimensions` 3 次元以上（項の数と符号の決め方）（青）：https://yuukougun.github.io/kyopro-atlas/basics/prefix-sum-2d/#higher-dimensions

## いもす法（imos） {#imos}

- id：`imos`　レベル：基礎　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/basics/imos/
- 別名：imos 法、差分配列、difference array、2 次元いもす法、階差、隣接差、等差数列の区間加算
- 種類：累積和・差分
- 前提：`prefix-sum`
- サイン：
    - 言い回し：区間にまとめて加算し、最後に各点の値を知りたい
    - 言い回し：各時刻に何人いるか・ちょうど k 個重なる長さ
    - 言い回し：長方形にまとめて加算する（重なった枚数ごとの面積）
    - 言い回し：区間に一律の値を足すたびに隣接差の和を答える
    - 言い回し：等差数列になっている区間・区間に 1, 2, 3, … を足す
    - 制約：N, Q ≤ 2×10^5 で区間への加算が多数あり、値を読むのは最後だけ
- 節：
    - `imos#imos-1d` 1 次元のいもす法（閉区間なら右端 + 1 に −x）：https://yuukougun.github.io/kyopro-atlas/basics/imos/#imos-1d
    - `imos#large-coordinates` 座標が大きいとき（座標圧縮・イベントのソート）：https://yuukougun.github.io/kyopro-atlas/basics/imos/#large-coordinates
    - `imos#by-length` 区間長や開始時刻の範囲に直して加算する：https://yuukougun.github.io/kyopro-atlas/basics/imos/#by-length
    - `imos#adjacent-difference` 隣接差で見る（区間加算は 2 点の増減・等差数列の区間）：https://yuukougun.github.io/kyopro-atlas/basics/imos/#adjacent-difference
    - `imos#range-flip` 区間反転を切り替え点 2 つで表す：https://yuukougun.github.io/kyopro-atlas/basics/imos/#range-flip
    - `imos#second-order` 2 階の差分（区間に 1, 2, 3, … を足す）：https://yuukougun.github.io/kyopro-atlas/basics/imos/#second-order
    - `imos#imos-2d` 2 次元いもす法（四隅に ±1、横と縦に累積）：https://yuukougun.github.io/kyopro-atlas/basics/imos/#imos-2d
    - `imos#online` 途中で値を読むなら BIT・遅延セグ木：https://yuukougun.github.io/kyopro-atlas/basics/imos/#online

## 差分列への言い換え（difference-sequence） {#difference-sequence}

- id：`difference-sequence`　レベル：黄　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/basics/difference-sequence/
- 別名：差分列、差分で言い換える、区間 ±1 の最小回数、区間操作を 2 点の操作に、difference sequence
- 種類：累積和・差分、考察
- 前提：`imos`
- サイン：
    - 言い回し：区間に +1・−1 する操作の最小回数・可否
    - 言い回し：数列を単調にする・回文にするための最小の操作回数
    - 言い回し：円形に並んだ箱から一斉に取り除く操作で空にできるか
    - 式の形：操作が区間に一律の値を足す形で、隣接差では 2 か所だけが変わる
- 節：
    - `difference-sequence#to-point-operations` 区間の操作を差分列の 2 点の操作に直す：https://yuukougun.github.io/kyopro-atlas/basics/difference-sequence/#to-point-operations
    - `difference-sequence#min-operations` 最小回数・可否を差分列の正負で考える：https://yuukougun.github.io/kyopro-atlas/basics/difference-sequence/#min-operations
    - `difference-sequence#strict-to-weak` 狭義の条件は a_i − i で広義に直してから差分を取る：https://yuukougun.github.io/kyopro-atlas/basics/difference-sequence/#strict-to-weak
    - `difference-sequence#palindrome` 回文にする操作は左右の差の列に直してから差分を取る：https://yuukougun.github.io/kyopro-atlas/basics/difference-sequence/#palindrome
    - `difference-sequence#circular` 円環で一斉に行う操作：https://yuukougun.github.io/kyopro-atlas/basics/difference-sequence/#circular

## 尺取り法（two-pointers） {#two-pointers}

- id：`two-pointers`　レベル：基礎　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/basics/two-pointers/
- 別名：しゃくとり法、two pointers、2 ポインタ、スライディングウィンドウ、固定長の窓
- 種類：尺取り・スライド窓
- 前提：`prefix-sum`、`complexity-estimation`
- サイン：
    - 言い回し：条件を満たす最長（最短）の連続区間・連続区間の個数
    - 言い回し：区間を縮めても（広げても）条件が保たれる
    - 言い回し：長さ M の範囲に入るものの最大個数
    - 制約：N ≤ 2×10^5 で区間を全部は調べられない
- 節：
    - `two-pointers#two-types` 2 つの型（部分区間も満たす型・より大きい区間も満たす型）：https://yuukougun.github.io/kyopro-atlas/basics/two-pointers/#two-types
    - `two-pointers#monotonicity` 単調性の見抜き方（縮めても保たれるか）：https://yuukougun.github.io/kyopro-atlas/basics/two-pointers/#monotonicity
    - `two-pointers#implementation` 空区間・取り除く処理の書き方：https://yuukougun.github.io/kyopro-atlas/basics/two-pointers/#implementation
    - `two-pointers#fixed-window` 固定長の窓をずらす：https://yuukougun.github.io/kyopro-atlas/basics/two-pointers/#fixed-window
    - `two-pointers#negative-values` 負の値があるとき（累積和＋連想配列へ）：https://yuukougun.github.io/kyopro-atlas/basics/two-pointers/#negative-values
    - `two-pointers#vs-binary-search` 二分探索との関係（O(N log N) でも解ける）：https://yuukougun.github.io/kyopro-atlas/basics/two-pointers/#vs-binary-search

## ランレングス圧縮（run-length-encoding） {#run-length-encoding}

- id：`run-length-encoding`　レベル：基礎　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/basics/run-length-encoding/
- 別名：連長圧縮、RLE、塊ごとに考える、run-length encoding
- 種類：文字列、考察
- サイン：
    - 言い回し：同じ文字・値が続く部分
    - 言い回し：区間を反転して 1 の連続を最長にする
    - 言い回し：操作で塊（境界）の数がいくつ減るか
    - 言い回し：ランレングス形式で与えられる入力
- 節：
    - `run-length-encoding#split` 塊への分け方（最後の塊を忘れない・番兵の塊）：https://yuukougun.github.io/kyopro-atlas/basics/run-length-encoding/#split
    - `run-length-encoding#count-boundaries` 境界の数で操作を数える：https://yuukougun.github.io/kyopro-atlas/basics/run-length-encoding/#count-boundaries
    - `run-length-encoding#two-pointers-on-runs` 塊の列で尺取りする：https://yuukougun.github.io/kyopro-atlas/basics/run-length-encoding/#two-pointers-on-runs
    - `run-length-encoding#parity-per-run` 塊ごとに偶奇で振り分ける：https://yuukougun.github.io/kyopro-atlas/basics/run-length-encoding/#parity-per-run
    - `run-length-encoding#keep-compressed` ランレングスのまま処理する（水）：https://yuukougun.github.io/kyopro-atlas/basics/run-length-encoding/#keep-compressed

## 半分全列挙（meet-in-the-middle） {#meet-in-the-middle}

- id：`meet-in-the-middle`　レベル：水　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/basics/meet-in-the-middle/
- 別名：Meet in the Middle、半分全探索、折半全列挙
- 種類：全探索、二分探索
- 前提：`bit-full-search`、`binary-search`
- サイン：
    - 制約：N ≤ 40 で部分集合を選ぶ（2^N は無理だが 2^(N/2) は間に合う）
    - 言い回し：2 つの独立な選択を組み合わせて条件を満たす
    - 制約：H + W ≤ 40 程度のグリッドで、左上から右下への経路をすべて考える
- 節：
    - `meet-in-the-middle#combine-halves` 前半・後半を列挙して突き合わせる（ソート＋二分探索・尺取り）：https://yuukougun.github.io/kyopro-atlas/basics/meet-in-the-middle/#combine-halves
    - `meet-in-the-middle#by-count` ちょうど K 個などの制約は個数ごとに分けて持つ：https://yuukougun.github.io/kyopro-atlas/basics/meet-in-the-middle/#by-count
    - `meet-in-the-middle#grid-diagonal` グリッドの経路を対角線で分ける（青）：https://yuukougun.github.io/kyopro-atlas/basics/meet-in-the-middle/#grid-diagonal
    - `meet-in-the-middle#vs-greedy` 「片側を全探索して残りは貪欲」との違い：https://yuukougun.github.io/kyopro-atlas/basics/meet-in-the-middle/#vs-greedy
    - `meet-in-the-middle#vs-knapsack` 値の範囲が小さければナップサック DP：https://yuukougun.github.io/kyopro-atlas/basics/meet-in-the-middle/#vs-knapsack

## 平均・中央値の最大化（fractional-binary-search） {#fractional-binary-search}

- id：`fractional-binary-search`　レベル：水　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/basics/fractional-binary-search/
- 別名：平均の最大化、比の最大化、中央値の最大化、分数計画、濃度の最大化、中央値の二分探索、中央値の中央値、fractional programming、Dinkelbach
- 種類：二分探索
- 前提：`binary-search-answer`、`prefix-sum`
- サイン：
    - 言い回し：平均・濃度・割合・(Σa)/(Σb) の最大（最小）
    - 言い回し：中央値の最大値・最小値
    - 言い回し：全区間の中央値を集めた中央値
    - 式の形：選び方の和の最大化なら解けるが、割り算（平均・比）が入ると直接は最大化できない
- 節：
    - `fractional-binary-search#average` 平均の言い換え（x を引いた和の符号で判定する）：https://yuukougun.github.io/kyopro-atlas/basics/fractional-binary-search/#average
    - `fractional-binary-search#ratio` 比 Σa / Σb の言い換え（a_i − x·b_i）：https://yuukougun.github.io/kyopro-atlas/basics/fractional-binary-search/#ratio
    - `fractional-binary-search#simple-check` 判定を累積和・貪欲で行う：https://yuukougun.github.io/kyopro-atlas/basics/fractional-binary-search/#simple-check
    - `fractional-binary-search#greedy-pitfall` 「濃度の高い順に K 個」が誤りである理由：https://yuukougun.github.io/kyopro-atlas/basics/fractional-binary-search/#greedy-pitfall
    - `fractional-binary-search#median` 中央値の言い換え（x 以上を +1、未満を −1）と偶数個のときの不等号（青）：https://yuukougun.github.io/kyopro-atlas/basics/fractional-binary-search/#median
    - `fractional-binary-search#dp-check` 判定を DP・DAG の最長路・全域木で行う（青）：https://yuukougun.github.io/kyopro-atlas/basics/fractional-binary-search/#dp-check
    - `fractional-binary-search#median-2d` 領域の中央値（2 次元累積和）（青）：https://yuukougun.github.io/kyopro-atlas/basics/fractional-binary-search/#median-2d
    - `fractional-binary-search#median-of-medians` 全区間の中央値の中央値（転倒数で数える）（黄）：https://yuukougun.github.io/kyopro-atlas/basics/fractional-binary-search/#median-of-medians
    - `fractional-binary-search#precision` 実数の精度と分母 0：https://yuukougun.github.io/kyopro-atlas/basics/fractional-binary-search/#precision
    - `fractional-binary-search#dinkelbach` Dinkelbach 法（発展）：https://yuukougun.github.io/kyopro-atlas/basics/fractional-binary-search/#dinkelbach

## K 番目の値（kth-value） {#kth-value}

- id：`kth-value`　レベル：青　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/basics/kth-value/
- 別名：K 番目を二分探索で求める、順位を数える、N^2 個の K 番目、K-th smallest
- 種類：二分探索
- 前提：`binary-search-answer`、`two-pointers`
- サイン：
    - 言い回し：N^2 個（以上）の値の K 番目
    - 言い回し：大きい方から M 個の和
    - 制約：N ≤ 2×10^5 で、K が N^2 程度まで大きい
    - 式の形：全部は列挙できないが「x 以下が何個あるか」は数えられる
- 節：
    - `kth-value#why-count` なぜ count(x) ≥ K となる最小の x が答えか：https://yuukougun.github.io/kyopro-atlas/basics/kth-value/#why-count
    - `kth-value#counting-patterns` 数え方の型（ソート＋二分探索・尺取り、符号で場合分け、包除）：https://yuukougun.github.io/kyopro-atlas/basics/kth-value/#counting-patterns
    - `kth-value#top-m-sum` 上位 M 個の和（同じ値の分の調整）：https://yuukougun.github.io/kyopro-atlas/basics/kth-value/#top-m-sum

## 三分探索（ternary-search） {#ternary-search}

- id：`ternary-search`　レベル：水　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/basics/ternary-search/
- 別名：三分法、黄金分割探索、凸関数の極値、凸関数、離散凸、増分が単調、ternary search
- 種類：二分探索
- 前提：`binary-search-answer`
- サイン：
    - 言い回し：時刻や位置を 1 つ選んで、時間やコストを最小化する（谷形）
    - 言い回し：答えを実数で出力し、誤差が許される
    - 式の形：1 つ増やすごとの増分が単調に増える
- 節：
    - `ternary-search#real-and-integer` 実数版（反復回数の目安）と整数版（残りを全部調べる）：https://yuukougun.github.io/kyopro-atlas/basics/ternary-search/#real-and-integer
    - `ternary-search#difference-sign` 差分の符号で二分探索する方法：https://yuukougun.github.io/kyopro-atlas/basics/ternary-search/#difference-sign
    - `ternary-search#convexity` 凸性の確かめ方（凸関数の和・最大は凸、|x − a| と x^2 は凸）：https://yuukougun.github.io/kyopro-atlas/basics/ternary-search/#convexity
    - `ternary-search#flat-pitfall` 平らな部分がある関数での失敗：https://yuukougun.github.io/kyopro-atlas/basics/ternary-search/#flat-pitfall
    - `ternary-search#golden-section` 黄金分割探索：https://yuukougun.github.io/kyopro-atlas/basics/ternary-search/#golden-section
    - `ternary-search#marginal-greedy` 増分が単調なら 1 単位ずつ貪欲に配る（青）：https://yuukougun.github.io/kyopro-atlas/basics/ternary-search/#marginal-greedy

## 絶対値の和の最小化と中央値（median-absolute） {#median-absolute}

- id：`median-absolute`　レベル：基礎　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/basics/median-absolute/
- 別名：中央値で絶対値最小、Σ|x − a_i|、マンハッタン距離の和の最小
- 種類：ソート・座標圧縮、考察
- 前提：`sorting-techniques`
- サイン：
    - 言い回し：Σ|x − a_i| を最小化する
    - 言い回し：マンハッタン距離の和が最小になる点
    - 言い回し：全員を 1 か所に集める移動の和
- 節：
    - `median-absolute#why-median` なぜ中央値か（傾きの変化）：https://yuukougun.github.io/kyopro-atlas/basics/median-absolute/#why-median
    - `median-absolute#even-count` 偶数個のとき（中央の 2 つの間ならどこでもよい）：https://yuukougun.github.io/kyopro-atlas/basics/median-absolute/#even-count
    - `median-absolute#change-variables` 変数変換で帰着する（a_i − i）：https://yuukougun.github.io/kyopro-atlas/basics/median-absolute/#change-variables
    - `median-absolute#separate-axes` x と y に分ける：https://yuukougun.github.io/kyopro-atlas/basics/median-absolute/#separate-axes
    - `median-absolute#with-binary-search` 距離の和で判定して二分探索する（青）：https://yuukougun.github.io/kyopro-atlas/basics/median-absolute/#with-binary-search
    - `median-absolute#vs-squares` 二乗和の最小（平均）との違い：https://yuukougun.github.io/kyopro-atlas/basics/median-absolute/#vs-squares

## 貪欲法の考え方と正当性（greedy-basics） {#greedy-basics}

- id：`greedy-basics`　レベル：基礎　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/basics/greedy-basics/
- 別名：グリーディ、Greedy、貪欲、交換しても悪化しない、マトロイド
- 種類：貪欲
- 前提：`sorting-techniques`
- サイン：
    - 言い回し：強いもの・安いものから順に使う
    - 言い回し：1 回ごとに最大（最小）のものを選ぶ操作を繰り返す
    - 式の形：その場で一番よいものを選んでも後悔しない（入れ替えても悪くならない）
- 節：
    - `greedy-basics#proof` 正当性の示し方（交換論法・帰納法・常に先行している・マトロイド）：https://yuukougun.github.io/kyopro-atlas/basics/greedy-basics/#proof
    - `greedy-basics#strongest-first` 基準を決めて強い順に使う：https://yuukougun.github.io/kyopro-atlas/basics/greedy-basics/#strongest-first
    - `greedy-basics#batch-same-values` 同じ値をまとめて処理する：https://yuukougun.github.io/kyopro-atlas/basics/greedy-basics/#batch-same-values
    - `greedy-basics#counterexamples` 反例の探し方（小さいケースの全探索と比べる）：https://yuukougun.github.io/kyopro-atlas/basics/greedy-basics/#counterexamples
    - `greedy-basics#when-greedy-fails` 貪欲が失敗する例と DP への切り替え：https://yuukougun.github.io/kyopro-atlas/basics/greedy-basics/#when-greedy-fails

## 区間スケジューリング・区間の串刺し（interval-scheduling） {#interval-scheduling}

- id：`interval-scheduling`　レベル：基礎　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/basics/interval-scheduling/
- 別名：区間スケジューリング問題、区間を点で突く、Activity Selection、interval scheduling
- 種類：貪欲、ソート・座標圧縮
- 前提：`greedy-basics`
- サイン：
    - 言い回し：重ならない区間をできるだけ多く選ぶ
    - 言い回し：すべての区間を最少の点（串）で突く
    - 制約：N ≤ 2×10^5 本の区間で、座標は 10^9 まで
- 節：
    - `interval-scheduling#why-right-end` 右端の順に選ぶ理由（交換論法）：https://yuukougun.github.io/kyopro-atlas/basics/interval-scheduling/#why-right-end
    - `interval-scheduling#stabbing` 区間の串刺し（最少の点で突く）：https://yuukougun.github.io/kyopro-atlas/basics/interval-scheduling/#stabbing
    - `interval-scheduling#counterexamples` 左端の順・長さの順が失敗する例：https://yuukougun.github.io/kyopro-atlas/basics/interval-scheduling/#counterexamples
    - `interval-scheduling#deadlines` 処理時間と締め切りがある場合（優先度付きキューの貪欲へ）：https://yuukougun.github.io/kyopro-atlas/basics/interval-scheduling/#deadlines
    - `interval-scheduling#weighted` 区間に重みがあるなら DP：https://yuukougun.github.io/kyopro-atlas/basics/interval-scheduling/#weighted

## 優先度付きキューを使う貪欲（greedy-priority-queue） {#greedy-priority-queue}

- id：`greedy-priority-queue`　レベル：水　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/basics/greedy-priority-queue/
- 別名：priority_queue で貪欲、ヒープで貪欲、締め切り付きスケジューリング、後悔付き貪欲、小さい順に K 個を列挙、K-best enumeration
- 種類：貪欲、データ構造
- 前提：`greedy-basics`、`priority-queue`
- サイン：
    - 言い回し：日が進むと選択肢が増え、各日に 1 つ選ぶ
    - 言い回し：締め切りまでに何個できるか・報酬の最大
    - 言い回し：毎回いちばん大きい（小さい）ものを取り出して更新する
    - 言い回し：組合せの和の小さい方から K 番目（K が小さい）
    - 制約：K ≤ 2×10^5 程度で、小さい順に K 個取り出せば足りる
    - 式の形：一度選んだものを、後でよいものが来たら入れ替えたい
- 節：
    - `greedy-priority-queue#take-max` 毎回最大を取り出す（同じ値はまとめる）：https://yuukougun.github.io/kyopro-atlas/basics/greedy-priority-queue/#take-max
    - `greedy-priority-queue#from-last-day` 後ろの日から決める（使えるようになった候補をキューに入れる）：https://yuukougun.github.io/kyopro-atlas/basics/greedy-priority-queue/#from-last-day
    - `greedy-priority-queue#earliest-deadline` 時刻順に入れて締め切りの早いものから処理する（時刻は次のイベントまで飛ばす）：https://yuukougun.github.io/kyopro-atlas/basics/greedy-priority-queue/#earliest-deadline
    - `greedy-priority-queue#fix-max-keep-k` 最大値を固定して上位 K 個を保つ：https://yuukougun.github.io/kyopro-atlas/basics/greedy-priority-queue/#fix-max-keep-k
    - `greedy-priority-queue#k-best` 小さい順に K 個を列挙する（取り出したら次の候補を入れる）：https://yuukougun.github.io/kyopro-atlas/basics/greedy-priority-queue/#k-best
    - `greedy-priority-queue#regret` 選んだものを後から入れ替える（後悔付き貪欲。一般形は Alien DP のページ）：https://yuukougun.github.io/kyopro-atlas/basics/greedy-priority-queue/#regret

## 交換論法と比較関数の設計（exchange-argument） {#exchange-argument}

- id：`exchange-argument`　レベル：青　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/basics/exchange-argument/
- 別名：隣接交換、exchange argument、ソートの比較関数を作る、連結して最大・最小、a+b と b+a
- 種類：貪欲、ソート・座標圧縮
- 前提：`greedy-basics`
- サイン：
    - 言い回し：並べる順番で結果が変わる
    - 言い回し：文字列・数を並べて連結した結果を最大（最小）にする
    - 式の形：2 つを入れ替えたときの差が、その 2 つだけで決まる
- 節：
    - `exchange-argument#adjacent-swap` 隣接交換で比較を導く：https://yuukougun.github.io/kyopro-atlas/basics/exchange-argument/#adjacent-swap
    - `exchange-argument#strict-weak-ordering` 比較が狭義の弱順序になっているか：https://yuukougun.github.io/kyopro-atlas/basics/exchange-argument/#strict-weak-ordering
    - `exchange-argument#ratios` 比は掛け算で比べる・分母 0：https://yuukougun.github.io/kyopro-atlas/basics/exchange-argument/#ratios
    - `exchange-argument#concatenation` 連結の比較（a+b と b+a）：https://yuukougun.github.io/kyopro-atlas/basics/exchange-argument/#concatenation
    - `exchange-argument#then-dp` 順に並べてから DP（DP の章へ）：https://yuukougun.github.io/kyopro-atlas/basics/exchange-argument/#then-dp
    - `exchange-argument#improve-by-swap` 入れ替えで改善できるかを考える型：https://yuukougun.github.io/kyopro-atlas/basics/exchange-argument/#improve-by-swap

## 辞書順最小を前から決める貪欲（lexicographic-greedy） {#lexicographic-greedy}

- id：`lexicographic-greedy`　レベル：基礎　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/basics/lexicographic-greedy/
- 別名：辞書順最小、lexicographically smallest、辞書順 K 番目、先頭から貪欲に決める
- 種類：貪欲、文字列
- 前提：`greedy-basics`
- サイン：
    - 言い回し：辞書順最小（最大）の文字列・列を出力する（なければ −1）
    - 言い回し：条件を満たす中で最も小さいもの
    - 言い回し：辞書順で K 番目
- 節：
    - `lexicographic-greedy#why-front` 先頭から決める理由（辞書順の性質）：https://yuukougun.github.io/kyopro-atlas/basics/lexicographic-greedy/#why-front
    - `lexicographic-greedy#feasibility` 残りで実現できるかの判定（次の出現位置の表・個数の数え上げ）：https://yuukougun.github.io/kyopro-atlas/basics/lexicographic-greedy/#feasibility
    - `lexicographic-greedy#topological` 順序の制約は入次数 0 を小さい順に（トポロジカルソート）：https://yuukougun.github.io/kyopro-atlas/basics/lexicographic-greedy/#topological
    - `lexicographic-greedy#kth` 辞書順 K 番目（先頭ごとの個数と K を比べる）：https://yuukougun.github.io/kyopro-atlas/basics/lexicographic-greedy/#kth
    - `lexicographic-greedy#heavy-check` 判定が重い型（青）：https://yuukougun.github.io/kyopro-atlas/basics/lexicographic-greedy/#heavy-check

## 周期性の検出（periodicity） {#periodicity}

- id：`periodicity`　レベル：基礎　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/basics/periodicity/
- 別名：周期性、周期の検出、ρ 型、ループの検出、シミュレーションの高速化、cycle finding
- 種類：ダブリング・分割統治
- サイン：
    - 制約：K ≤ 10&#94;18 回の操作で、状態の種類は 10&#94;5〜10&#94;6 程度
    - 言い回し：x_{n+1} = f(x_n) の形の漸化式
    - 言い回し：同じ模様が繰り返し敷き詰められた盤面
- 節：
    - `periodicity#rho` 尾と周期（ρ 型）と K 回後の求め方：https://yuukougun.github.io/kyopro-atlas/basics/periodicity/#rho
    - `periodicity#partial-sums` 途中の和（尾の和＋周期の和 × 回数＋余り）：https://yuukougun.github.io/kyopro-atlas/basics/periodicity/#partial-sums
    - `periodicity#state-design` 状態に将来を決める情報をすべて入れる：https://yuukougun.github.io/kyopro-atlas/basics/periodicity/#state-design
    - `periodicity#convergence` 収束に気づく：https://yuukougun.github.io/kyopro-atlas/basics/periodicity/#convergence
    - `periodicity#periodic-patterns` 盤面・剰余の周期を割り算で数える（水）：https://yuukougun.github.io/kyopro-atlas/basics/periodicity/#periodic-patterns
    - `periodicity#simulation-speedup` シミュレーションを速く進める（ずれ・反転は全体への操作を変数で持つページへ）：https://yuukougun.github.io/kyopro-atlas/basics/periodicity/#simulation-speedup
    - `periodicity#vs-doubling` ダブリング・行列累乗との使い分け：https://yuukougun.github.io/kyopro-atlas/basics/periodicity/#vs-doubling

## ダブリング（doubling） {#doubling}

- id：`doubling`　レベル：水　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/basics/doubling/
- 別名：binary lifting、倍化、2^k 回後の表、ダブリング上の二分探索、doubling
- 種類：ダブリング・分割統治
- 前提：`periodicity`、`bit-operations`
- サイン：
    - 制約：K ≤ 10^18 回の移動・操作で、始点やクエリが多い
    - 言い回し：各状態から次の状態がただ 1 つに決まる
    - 言い回し：途中の和・最小値も必要
    - 言い回し：条件を満たす最大の回数を求める
- 節：
    - `doubling#table` 表の作り方と K の 2 進展開：https://yuukougun.github.io/kyopro-atlas/basics/doubling/#table
    - `doubling#aggregates` 途中の和・最小値を同じ表に持つ（半開で持つ）：https://yuukougun.github.io/kyopro-atlas/basics/doubling/#aggregates
    - `doubling#binary-search-on-doubling` ダブリング上の二分探索（条件を満たす最大の回数）：https://yuukougun.github.io/kyopro-atlas/basics/doubling/#binary-search-on-doubling
    - `doubling#permutation-power` 置換の K 回合成：https://yuukougun.github.io/kyopro-atlas/basics/doubling/#permutation-power
    - `doubling#memory` 段数とメモリの見積もり：https://yuukougun.github.io/kyopro-atlas/basics/doubling/#memory

## 再帰的な構造（recursion-structure） {#recursion-structure}

- id：`recursion-structure`　レベル：基礎　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/basics/recursion-structure/
- 別名：フラクタル、自己相似、再帰関数、レベル N の構造、recursive structure、fractal
- 種類：ダブリング・分割統治
- サイン：
    - 言い回し：レベル N のものがレベル N − 1 のものを並べて作られる
    - 言い回し：長さが 2 倍・3 倍で増える構造の K 番目
    - 言い回し：フラクタル図形を描く
    - 制約：レベルは 50 程度まででも、全体の長さが 10^15 を超える
- 節：
    - `recursion-structure#kth-by-length` 長さを前計算して K 番目を再帰で探す：https://yuukougun.github.io/kyopro-atlas/basics/recursion-structure/#kth-by-length
    - `recursion-structure#draw` 再帰で描く：https://yuukougun.github.io/kyopro-atlas/basics/recursion-structure/#draw
    - `recursion-structure#depth` 必要な深さは log K（長さの上限で打ち切る）：https://yuukougun.github.io/kyopro-atlas/basics/recursion-structure/#depth
    - `recursion-structure#stack` 再帰の深さとスタック：https://yuukougun.github.io/kyopro-atlas/basics/recursion-structure/#stack

## 分割統治（divide-and-conquer） {#divide-and-conquer}

- id：`divide-and-conquer`　レベル：黄　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/basics/divide-and-conquer/
- 別名：divide and conquer、分割統治法、マージソート、中央をまたぐ区間、区間ナップサック
- 種類：ダブリング・分割統治
- 前提：`recursion-structure`
- サイン：
    - 言い回し：区間・部分列の全部の組について数える
    - 言い回し：区間 [L, R] の品物だけを使うナップサックを多数のクエリで答える
    - 制約：N, Q ≤ 2×10^5 で、区間ごとに計算し直すと間に合わない
    - 式の形：左右に分けたとき、中央をまたぐものだけなら速く数えられる
    - 式の形：区間の最大値の位置で左右に分けると、それぞれが同じ形の問題になる
- 節：
    - `divide-and-conquer#recurrence` 漸化式 T(N) = 2T(N/2) + O(N) と計算量：https://yuukougun.github.io/kyopro-atlas/basics/divide-and-conquer/#recurrence
    - `divide-and-conquer#crossing` またぐものの数え方（マージソートで転倒数）：https://yuukougun.github.io/kyopro-atlas/basics/divide-and-conquer/#crossing
    - `divide-and-conquer#split-at-max` 最大値の位置で分ける：https://yuukougun.github.io/kyopro-atlas/basics/divide-and-conquer/#split-at-max
    - `divide-and-conquer#range-knapsack` 区間クエリを中央で分けて左右の DP を合わせる（区間ナップサック）：https://yuukougun.github.io/kyopro-atlas/basics/divide-and-conquer/#range-knapsack
    - `divide-and-conquer#other-fields` 他の分野の分割統治（分割統治 DP・分割統治 FFT・CDQ）への案内：https://yuukougun.github.io/kyopro-atlas/basics/divide-and-conquer/#other-fields
