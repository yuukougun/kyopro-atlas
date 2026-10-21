---
title: 整数論・代数の詳細索引
type: generated
search:
  exclude: true
---

<!-- tools/gen_site.py が生成する。手で直さない -->

# 整数論・代数の詳細索引

分野の全ページの id・URL・別名・サイン・種類・前提・節。全分野の1行の一覧と索引の版は https://yuukougun.github.io/kyopro-atlas/llms.txt にある。stub（準備中）のページは要約と前提しかなく、節の見出しもまだない。

## Σ の変形（sigma-manipulation） {#sigma-manipulation}

- id：`sigma-manipulation`　レベル：基礎　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/math/sigma-manipulation/
- 別名：シグマの変形、和の順序交換、総和の変形、二重和、添字の付け替え、order of summation
- 種類：考察、数え上げ
- サイン：
    - 言い回し：全ての組 (i, j)（i < j）について〜を足した和を求める
    - 式の形：Σ_{i=1}^{N} Σ_{j=i}^{N} f(i, j) のように、内側の和の範囲が外側の添字で決まる二重和
    - 式の形：Σ_{K=1}^{N} K × (K の約数の個数) のように、約数・倍数の関係で書き換えられる和
- 節：
    - `sigma-manipulation#linearity` Σ の線形性と分解（定数を外に出す・和を分ける）：https://yuukougun.github.io/kyopro-atlas/math/sigma-manipulation/#linearity
    - `sigma-manipulation#swap-order` 二重和の順序交換と添字の範囲（i ≤ j ≤ N を j の側から見る）：https://yuukougun.github.io/kyopro-atlas/math/sigma-manipulation/#swap-order
    - `sigma-manipulation#reindex` 添字の付け替え（i → N − i、k = i + j、約数 d と倍数）：https://yuukougun.github.io/kyopro-atlas/math/sigma-manipulation/#reindex
    - `sigma-manipulation#group-by-value` 値でまとめ直す（同じ値になる添字の個数を掛ける）：https://yuukougun.github.io/kyopro-atlas/math/sigma-manipulation/#group-by-value
    - `sigma-manipulation#formulas` よく使う和の公式と Σ_{i≠j} a_i a_j = (Σa)² − Σa²：https://yuukougun.github.io/kyopro-atlas/math/sigma-manipulation/#formulas
    - `sigma-manipulation#empty-sum` 空の和は 0・空の積は 1 と境界：https://yuukougun.github.io/kyopro-atlas/math/sigma-manipulation/#empty-sum
    - `sigma-manipulation#next-steps` 上位の手法へのつながり：https://yuukougun.github.io/kyopro-atlas/math/sigma-manipulation/#next-steps

## 整数の割り算と余り（integer-division） {#integer-division}

- id：`integer-division`　レベル：基礎　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/math/integer-division/
- 別名：floor_div、floor division、切り捨て除算、切り上げ、負の数の割り算、負の数の余り、オーバーフロー判定、割り算で比較
- 種類：整数論
- サイン：
    - 制約：入力に負の数（|X| ≤ 10^18 など）があり、割り算・余り・切り上げを使う
    - 制約：積・lcm・累乗が 10^18 を超えうる（long long の上限は約 9.2×10^18）
    - 言い回し：x 以上で、m で割って r 余る最小の数
    - 言い回し：[L, R] にある K の倍数の個数
    - 言い回し：一定の間隔で発車する・周期的に起こる出来事の、ある時刻以降で最初のもの
- 節：
    - `integer-division#cpp-vs-math` C++ の / と % と、数学の floor・mod の違い：https://yuukougun.github.io/kyopro-atlas/math/integer-division/#cpp-vs-math
    - `integer-division#floor-ceil` 負の数でも正しい floor_div・ceil_div・safe_mod：https://yuukougun.github.io/kyopro-atlas/math/integer-division/#floor-ceil
    - `integer-division#ceil-formula` 切り上げ ⌈a/b⌉ = ⌊(a+b−1)/b⌋ が使える条件：https://yuukougun.github.io/kyopro-atlas/math/integer-division/#ceil-formula
    - `integer-division#count-multiples` 区間 [L, R] の K の倍数の個数と、x 以上で m で割って r 余る最小の数：https://yuukougun.github.io/kyopro-atlas/math/integer-division/#count-multiples
    - `integer-division#overflow` あふれる前に割り算で判定する（a > L / b）と \_\_int128 への逃げ方：https://yuukougun.github.io/kyopro-atlas/math/integer-division/#overflow
    - `integer-division#no-double` double で割らない（10^18 付近の誤差）：https://yuukougun.github.io/kyopro-atlas/math/integer-division/#no-double
    - `integer-division#next-steps` 周期・mod・floor sum・商の列挙へのつながり：https://yuukougun.github.io/kyopro-atlas/math/integer-division/#next-steps

## mod の計算の基本（mod-arithmetic） {#mod-arithmetic}

- id：`mod-arithmetic`　レベル：基礎　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/math/mod-arithmetic/
- 別名：剰余演算、余りを取る、合同式の計算、modular arithmetic、mod 998244353、mod 1e9+7
- 種類：整数論
- 前提：`integer-division`
- サイン：
    - 言い回し：引き算を含む式の値を、0 以上 m 未満の余りで出力する
    - 制約：10^9 程度の値の積を何度も取り、余りを取らないと 64bit に収まらない
- 節：
    - `mod-arithmetic#why-mod` 途中で余りを取ってよい理由（合同式の性質）：https://yuukougun.github.io/kyopro-atlas/math/mod-arithmetic/#why-mod
    - `mod-arithmetic#negative` 引き算の後の負の数を 0 以上に直す：https://yuukougun.github.io/kyopro-atlas/math/mod-arithmetic/#negative
    - `mod-arithmetic#overflow` 掛け算のあふれ（両方を mod に収めてから 64bit で掛ける）：https://yuukougun.github.io/kyopro-atlas/math/mod-arithmetic/#overflow
    - `mod-arithmetic#division` 割り算はそのままではできない（→ 逆元）：https://yuukougun.github.io/kyopro-atlas/math/mod-arithmetic/#division
    - `mod-arithmetic#no-compare` mod を取った値で大小比較・最大値を考えてはいけない：https://yuukougun.github.io/kyopro-atlas/math/mod-arithmetic/#no-compare
    - `mod-arithmetic#why-998244353` なぜ 998244353 か（素数で、NTT に向く形）：https://yuukougun.github.io/kyopro-atlas/math/mod-arithmetic/#why-998244353
    - `mod-arithmetic#next-steps` 繰り返し二乗法・逆元・modint へのつながり：https://yuukougun.github.io/kyopro-atlas/math/mod-arithmetic/#next-steps

## 繰り返し二乗法（mod-pow） {#mod-pow}

- id：`mod-pow`　レベル：基礎　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/math/mod-pow/
- 別名：二分累乗法、高速累乗、binary exponentiation、modpow、pow_mod、モノイドの累乗
- 種類：整数論、ダブリング・分割統治
- 前提：`mod-arithmetic`
- ACL：`pow_mod`
- サイン：
    - 制約：指数・繰り返しの回数が N ≤ 10^18
    - 言い回し：a^N を m で割った余り
    - 言い回し：結合法則を満たす同じ操作を非常に多く繰り返す
- 節：
    - `mod-pow#binary-expansion` 指数を 2 進展開して必要な a&#94;(2&#94;k) だけ掛ける：https://yuukougun.github.io/kyopro-atlas/math/mod-pow/#binary-expansion
    - `mod-pow#recursive-iterative` 再帰版と反復版：https://yuukougun.github.io/kyopro-atlas/math/mod-pow/#recursive-iterative
    - `mod-pow#monoid-power` 結合法則を満たす演算の累乗（行列・写像の合成）：https://yuukougun.github.io/kyopro-atlas/math/mod-pow/#monoid-power
    - `mod-pow#pitfalls` 落とし穴：指数を m で割ってしまう・0^0・掛け算のあふれ：https://yuukougun.github.io/kyopro-atlas/math/mod-pow/#pitfalls
    - `mod-pow#acl` ACL の pow_mod と modint::pow：https://yuukougun.github.io/kyopro-atlas/math/mod-pow/#acl
    - `mod-pow#building-block` 繰り返し二乗法を部品にする手法：https://yuukougun.github.io/kyopro-atlas/math/mod-pow/#building-block

## 逆元と mod での割り算（mod-inverse） {#mod-inverse}

- id：`mod-inverse`　レベル：基礎　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/math/mod-inverse/
- 別名：モジュラ逆元、modular inverse、modinv、inv_mod、mod での割り算、逆元表
- 種類：整数論
- 前提：`mod-pow`
- ACL：`inv_mod`
- サイン：
    - 言い回し：答えは有理数 P/Q になるので P × Q^(−1) mod 998244353 を出力する
    - 言い回し：平均・等比数列の和などを、割り算を含む式のまま mod で求める
- 節：
    - `mod-inverse#existence` 逆元が存在する条件（gcd(a, m) = 1）：https://yuukougun.github.io/kyopro-atlas/math/mod-inverse/#existence
    - `mod-inverse#fermat` フェルマーの小定理による a^(p−2)：https://yuukougun.github.io/kyopro-atlas/math/mod-inverse/#fermat
    - `mod-inverse#ext-gcd` 拡張ユークリッドによる逆元（法が素数でないとき）（水）：https://yuukougun.github.io/kyopro-atlas/math/mod-inverse/#ext-gcd
    - `mod-inverse#inverse-table` 逆元表を O(N) で作る（inv[i] = −⌊m/i⌋·inv[m mod i]）と階乗の逆元：https://yuukougun.github.io/kyopro-atlas/math/mod-inverse/#inverse-table
    - `mod-inverse#rational` 有理数 P/Q を P × Q^(−1) で表す計算：https://yuukougun.github.io/kyopro-atlas/math/mod-inverse/#rational
    - `mod-inverse#not-invertible` 割れないときの3つの場合（割る数が p の倍数・公比 ≡ 1・法が素数でない）：https://yuukougun.github.io/kyopro-atlas/math/mod-inverse/#not-invertible
    - `mod-inverse#acl` ACL の inv_mod と modint::inv：https://yuukougun.github.io/kyopro-atlas/math/mod-inverse/#acl

## modint（modint） {#modint}

- id：`modint`　レベル：基礎　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/math/modint/
- 別名：static_modint、dynamic_modint、mint、modint998244353、modint1000000007
- 種類：整数論、実装・C++
- 前提：`mod-inverse`
- ACL：`static_modint`、`dynamic_modint`
- サイン：
    - 言い回し：法 M（素数とは限らない）が入力で与えられ、その余りで数え上げの答えを出力する
- 節：
    - `modint#what-is-automatic` 何が自動になるか（加減乗除と負の数の正規化）：https://yuukougun.github.io/kyopro-atlas/math/modint/#what-is-automatic
    - `modint#static-dynamic` static_modint と dynamic_modint（set_mod）の使い分け：https://yuukougun.github.io/kyopro-atlas/math/modint/#static-dynamic
    - `modint#pitfalls` val() で取り出す・大小比較や「0 になったか」で元の値は分からない：https://yuukougun.github.io/kyopro-atlas/math/modint/#pitfalls
    - `modint#division` 割り算の条件（法が素数でなければ互いに素が必要）：https://yuukougun.github.io/kyopro-atlas/math/modint/#division
    - `modint#connections` 上位の手法での使われ方（階乗の表・畳み込み・行列・期待値）：https://yuukougun.github.io/kyopro-atlas/math/modint/#connections
    - `modint#self-made` 自作するときの設計（加減の条件分岐・64bit の掛け算・pow と inv・入出力）：https://yuukougun.github.io/kyopro-atlas/math/modint/#self-made
    - `modint#acl-internals` ACL の中身（Barrett 還元・raw）：https://yuukougun.github.io/kyopro-atlas/math/modint/#acl-internals

## フェルマーの小定理と指数の mod（exponent-mod） {#exponent-mod}

- id：`exponent-mod`　レベル：水　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/math/exponent-mod/
- 別名：指数の mod、オイラーの定理、Fermat's little theorem、Euler's theorem、指数を p−1 で割る、累乗の塔、tetration
- 種類：整数論
- 前提：`mod-inverse`
- ACL：`pow_mod`
- サイン：
    - 言い回し：a&#94;(b&#94;c) mod p のように、指数にさらに指数がある
    - 言い回し：累乗の塔を mod で求める
    - 制約：指数が 10^18 をさらに累乗した大きさになる
- 節：
    - `exponent-mod#fermat` フェルマーの小定理と、指数を p − 1 で割ってよい理由（累乗の周期）：https://yuukougun.github.io/kyopro-atlas/math/exponent-mod/#fermat
    - `exponent-mod#exponent-mod-p-1` 指数の計算は mod (p − 1)（p − 1 は合成数なので割り算はできない）：https://yuukougun.github.io/kyopro-atlas/math/exponent-mod/#exponent-mod-p-1
    - `exponent-mod#base-multiple` 底が p の倍数の場合（答えは 0、指数が 0 なら 1）：https://yuukougun.github.io/kyopro-atlas/math/exponent-mod/#base-multiple
    - `exponent-mod#euler-theorem` 一般の法：オイラーの定理と、互いに素でないときの一般化（累乗の塔）（黄）：https://yuukougun.github.io/kyopro-atlas/math/exponent-mod/#euler-theorem

## 等比数列の和を mod で求める（geometric-series-mod） {#geometric-series-mod}

- id：`geometric-series-mod`　レベル：基礎　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/math/geometric-series-mod/
- 別名：等比級数、geometric series、repunit、Σ A^i、同じ数字を並べた数
- 種類：整数論、ダブリング・分割統治
- 前提：`mod-inverse`
- サイン：
    - 言い回し：同じ数字列を M 回並べてできる数を mod で求める
    - 言い回し：法 M が入力で与えられ、素数とは限らない
    - 制約：項数 N ≤ 10&#94;12〜10&#94;18 の等比数列の和を、素数とは限らない法 M ≤ 10&#94;9 で求める
    - 式の形：Σ_{i=0}^{N−1} A^i の形の和
- 節：
    - `geometric-series-mod#formula` 公式 (r^n − 1)/(r − 1) と r ≡ 1 の場合分け：https://yuukougun.github.io/kyopro-atlas/math/geometric-series-mod/#formula
    - `geometric-series-mod#halving` 法が任意のとき：S(2k) = S(k)(1 + r^k) で半分に割る（水）：https://yuukougun.github.io/kyopro-atlas/math/geometric-series-mod/#halving
    - `geometric-series-mod#matrix` 2×2 行列 [[r, 1], [0, 1]] の累乗による別解（青）：https://yuukougun.github.io/kyopro-atlas/math/geometric-series-mod/#matrix
    - `geometric-series-mod#repeated-digits` 同じ数字列を並べた数は公比 10^d の等比数列の和になる：https://yuukougun.github.io/kyopro-atlas/math/geometric-series-mod/#repeated-digits
    - `geometric-series-mod#next-steps` 行列累乗・ダブリング・位数へのつながり：https://yuukougun.github.io/kyopro-atlas/math/geometric-series-mod/#next-steps

## 桁と mod（digit-and-mod） {#digit-and-mod}

- id：`digit-and-mod`　レベル：水　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/math/digit-and-mod/
- 別名：九去法、倍数判定、divisibility rule、数の連結、10 倍して a を足す、部分文字列の余り、桁和
- 種類：整数論、累積和・差分
- 前提：`mod-arithmetic`
- サイン：
    - 言い回し：数字列の部分文字列を整数とみて、P の倍数になるものを数える
    - 言い回し：桁を消したり並べ替えたりして K の倍数にする
    - 言い回し：2 つの数を文字列として連結した数についての条件
    - 制約：|S| ≤ 2×10^5 の数字列で、部分文字列を全部試すと間に合わない
- 節：
    - `digit-and-mod#divisibility` 倍数判定（3・9 は桁和、4 は下2桁、8 は下3桁、11 は交互和）：https://yuukougun.github.io/kyopro-atlas/math/digit-and-mod/#divisibility
    - `digit-and-mod#concatenation` 数の連結：x の後ろに d 桁の y を付けると x·10^d + y：https://yuukougun.github.io/kyopro-atlas/math/digit-and-mod/#concatenation
    - `digit-and-mod#suffix-remainder` 接尾辞の余りで部分文字列を数える（10 と P が互いに素なとき）：https://yuukougun.github.io/kyopro-atlas/math/digit-and-mod/#suffix-remainder
    - `digit-and-mod#p-2-5` P が 2・5 のときの場合分け：https://yuukougun.github.io/kyopro-atlas/math/digit-and-mod/#p-2-5

## 約数列挙と素数判定（divisor-enum） {#divisor-enum}

- id：`divisor-enum`　レベル：基礎　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/math/divisor-enum/
- 別名：試し割り、trial division、divisor enumeration、primality test、√N まで調べる、約数の総和
- 種類：整数論、全探索
- 前提：`integer-division`
- サイン：
    - 制約：N ≤ 10^12 程度（√N ≤ 10^6）の約数・素数判定
    - 言い回し：a × b = N となる組を調べる
    - 言い回し：答え（gcd・周期・個数）が N の約数のどれかになる
    - 言い回し：X 以上の最小の素数
- 節：
    - `divisor-enum#why-sqrt` √N まで調べればよい理由（約数の対）：https://yuukougun.github.io/kyopro-atlas/math/divisor-enum/#why-sqrt
    - `divisor-enum#primality` 素数判定（試し割り）：https://yuukougun.github.io/kyopro-atlas/math/divisor-enum/#primality
    - `divisor-enum#enumerate` 約数の列挙とソート・平方数での重複：https://yuukougun.github.io/kyopro-atlas/math/divisor-enum/#enumerate
    - `divisor-enum#count-and-sum` 約数の個数 Π(e+1) と約数の総和の公式：https://yuukougun.github.io/kyopro-atlas/math/divisor-enum/#count-and-sum
    - `divisor-enum#candidates` 答えの候補が約数に限られる型（gcd の最大・商と余り・割るか引くか）：https://yuukougun.github.io/kyopro-atlas/math/divisor-enum/#candidates
    - `divisor-enum#pitfalls` 落とし穴：sqrt を double で求める・i\*i のあふれ：https://yuukougun.github.io/kyopro-atlas/math/divisor-enum/#pitfalls

## 素因数分解とルジャンドルの公式（prime-factorization） {#prime-factorization}

- id：`prime-factorization`　レベル：基礎　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/math/prime-factorization/
- 別名：prime factorization、Legendre's formula、階乗の素因数、末尾の 0 の個数、v_p(n!)
- 種類：整数論
- 前提：`divisor-enum`
- サイン：
    - 言い回し：素数ごとに独立に考えられる（積・割り切れる回数）
    - 言い回し：N! の末尾の 0 の個数、N! が K の倍数になる最小の N
    - 言い回し：積が M になる数列の数
    - 制約：N ≤ 10^12 程度の数を1つだけ素因数分解する
- 節：
    - `prime-factorization#procedure` 割れるだけ割る手順と、残った数が素数である理由：https://yuukougun.github.io/kyopro-atlas/math/prime-factorization/#procedure
    - `prime-factorization#per-prime` 素因数ごとに独立に考える（指数の組合せ）：https://yuukougun.github.io/kyopro-atlas/math/prime-factorization/#per-prime
    - `prime-factorization#legendre` N! の素因数分解とルジャンドルの公式：https://yuukougun.github.io/kyopro-atlas/math/prime-factorization/#legendre
    - `prime-factorization#which-method` 使い分け：1個なら試し割り、多数なら最小素因数の篩（10^18 は大きな数の素因数分解へ）：https://yuukougun.github.io/kyopro-atlas/math/prime-factorization/#which-method

## エラトステネスの篩（sieve-eratosthenes） {#sieve-eratosthenes}

- id：`sieve-eratosthenes`　レベル：基礎　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/math/sieve-eratosthenes/
- 別名：篩、sieve of Eratosthenes、素数の列挙、素数表
- 種類：整数論
- 前提：`divisor-enum`
- サイン：
    - 制約：N ≤ 10&#94;6〜10&#94;7 の範囲の素数を全部使う
    - 言い回し：p q³ ≤ N を満たす素数の組を数える
    - 言い回し：区間 [l, r] の素数の個数を何度も答える
- 節：
    - `sieve-eratosthenes#procedure` 倍数を消す手順と、p² から消せば十分な理由：https://yuukougun.github.io/kyopro-atlas/math/sieve-eratosthenes/#procedure
    - `sieve-eratosthenes#complexity` 計算量 O(N log log N) の根拠と、調和級数の O(N log N) との違い：https://yuukougun.github.io/kyopro-atlas/math/sieve-eratosthenes/#complexity
    - `sieve-eratosthenes#prefix-count` 篩の結果を累積和にして区間の素数を数える：https://yuukougun.github.io/kyopro-atlas/math/sieve-eratosthenes/#prefix-count
    - `sieve-eratosthenes#variants` 篩の変形（異なる素因数の個数を数える）：https://yuukougun.github.io/kyopro-atlas/math/sieve-eratosthenes/#variants
    - `sieve-eratosthenes#memory` メモリの見積もり（10^8 までは bit で持つ）：https://yuukougun.github.io/kyopro-atlas/math/sieve-eratosthenes/#memory

## 最小素因数の篩と線形篩（spf-sieve） {#spf-sieve}

- id：`spf-sieve`　レベル：基礎　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/math/spf-sieve/
- 別名：osa_k 法、最小素因数、smallest prime factor、SPF、高速素因数分解、linear sieve
- 種類：整数論
- 前提：`sieve-eratosthenes`、`prime-factorization`
- サイン：
    - 制約：A_i ≤ 10&#94;6（〜10&#94;7）の各要素を素因数分解する
    - 言い回し：全ての組が互いに素か（pairwise coprime）を判定する
    - 言い回し：各要素の素因数の個数（重複込み）を求める
- 節：
    - `spf-sieve#build-and-factor` 最小素因数の表の作り方と、割るたびに半分以下になるので O(log n) で分解できる理由：https://yuukougun.github.io/kyopro-atlas/math/spf-sieve/#build-and-factor
    - `spf-sieve#many-numbers` 多数の数をまとめて分解する（試し割りとの比較）：https://yuukougun.github.io/kyopro-atlas/math/spf-sieve/#many-numbers
    - `spf-sieve#after-factor` 分解した後の使い方（異なる素因数・指数・約数）：https://yuukougun.github.io/kyopro-atlas/math/spf-sieve/#after-factor
    - `spf-sieve#linear-sieve` 線形篩：各合成数を1回だけ作り、φ・μ の表を同時に作る（青）：https://yuukougun.github.io/kyopro-atlas/math/spf-sieve/#linear-sieve
    - `spf-sieve#memory` メモリの見積もり（int で 10^7 個は 40MB）：https://yuukougun.github.io/kyopro-atlas/math/spf-sieve/#memory

## 調和級数と倍数の列挙（harmonic-sum） {#harmonic-sum}

- id：`harmonic-sum`　レベル：水　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/math/harmonic-sum/
- 別名：harmonic series、N/1+N/2+…+N/N、O(N log N) の倍数ループ、倍数を回す
- 種類：計算量、整数論
- 前提：`sigma-manipulation`、`complexity-estimation`
- サイン：
    - 制約：A_i ≤ 10^6 程度で、値を配列の添字にできる
    - 言い回し：割り切る・割り切られる関係にある組を数える
    - 言い回し：各 d について、d の倍数である要素の個数や和を求める
    - 式の形：Σ_{d=1}^{N} Σ_{k=1}^{⌊N/d⌋} f(d, kd) の形の二重ループ
- 節：
    - `harmonic-sum#why-n-log-n` M/1 + M/2 + … + M/M ≈ M ln M の根拠（M = 10^6 で約 1.4×10^7）：https://yuukougun.github.io/kyopro-atlas/math/harmonic-sum/#why-n-log-n
    - `harmonic-sum#mark-multiples` 値の倍数に印を付ける：https://yuukougun.github.io/kyopro-atlas/math/harmonic-sum/#mark-multiples
    - `harmonic-sum#collect-multiples` 倍数を回して集める（d の倍数である要素の個数・和）：https://yuukougun.github.io/kyopro-atlas/math/harmonic-sum/#collect-multiples
    - `harmonic-sum#decide-from-back` 倍数の箱を後ろから決める：https://yuukougun.github.io/kyopro-atlas/math/harmonic-sum/#decide-from-back
    - `harmonic-sum#quotient-ranges` 商が同じ範囲を倍数で区切って数える：https://yuukougun.github.io/kyopro-atlas/math/harmonic-sum/#quotient-ranges
    - `harmonic-sum#vs-sieve` 素数の倍数だけをたどる篩（M log log M）との違い：https://yuukougun.github.io/kyopro-atlas/math/harmonic-sum/#vs-sieve
    - `harmonic-sum#pitfalls` 落とし穴：https://yuukougun.github.io/kyopro-atlas/math/harmonic-sum/#pitfalls

## 約数の個数の上界と高度合成数（divisor-count-bound） {#divisor-count-bound}

- id：`divisor-count-bound`　レベル：水　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/math/divisor-count-bound/
- 別名：約数の個数の最大値、highly composite number、約数が多い数、素因数の種類数の上界
- 種類：整数論、計算量
- 前提：`prime-factorization`
- サイン：
    - 言い回し：N の約数ごとに〜を計算する・d | N を満たす d を全部試す
    - 言い回し：N 以下で約数の個数が最大の数・約数が多い数を探す
    - 制約：N ≤ 10&#94;12〜10&#94;18 で、約数の組を全探索して間に合うかを見積もる
- 節：
    - `divisor-count-bound#table` 約数の個数・素因数の種類数の最大値の表（10&#94;3〜10&#94;18）：https://yuukougun.github.io/kyopro-atlas/math/divisor-count-bound/#table
    - `divisor-count-bound#pairs` 約数の組を全部試す見積もり（1344² ≈ 1.8×10^6）：https://yuukougun.github.io/kyopro-atlas/math/divisor-count-bound/#pairs
    - `divisor-count-bound#pitfalls` 落とし穴（約数の個数を √N と見積もる・10^18 の約数の列挙に O(√N) かかる）：https://yuukougun.github.io/kyopro-atlas/math/divisor-count-bound/#pitfalls
    - `divisor-count-bound#divisor-dp` 約数を状態にした DP（約数の個数が少ないことを使う）（青）：https://yuukougun.github.io/kyopro-atlas/math/divisor-count-bound/#divisor-dp
    - `divisor-count-bound#enumerate-hcn` 高度合成数の列挙（小さい素数の指数が単調に減る形を DFS で）（黄）：https://yuukougun.github.io/kyopro-atlas/math/divisor-count-bound/#enumerate-hcn

## 区間篩（segmented-sieve） {#segmented-sieve}

- id：`segmented-sieve`　レベル：水　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/math/segmented-sieve/
- 別名：区間ふるい、segmented sieve、区間の素因数分解
- 種類：整数論
- 前提：`sieve-eratosthenes`
- サイン：
    - 制約：L, R ≤ 10^12 で R − L ≤ 10^6
    - 言い回し：連続する区間の数をそれぞれ素因数分解する
    - 言い回し：二項係数 C(N, K) の分子 N−K+1..N を素因数分解する
- 節：
    - `segmented-sieve#why-sqrt` √R までの素数で十分な理由：https://yuukougun.github.io/kyopro-atlas/math/segmented-sieve/#why-sqrt
    - `segmented-sieve#first-multiple` 区間で最初の p の倍数 ⌈L/p⌉·p の求め方と、p 自身・L = 1 の扱い：https://yuukougun.github.io/kyopro-atlas/math/segmented-sieve/#first-multiple
    - `segmented-sieve#factorize-range` 区間の各数の素因数分解（√R までで割った残りは素数）：https://yuukougun.github.io/kyopro-atlas/math/segmented-sieve/#factorize-range
    - `segmented-sieve#complexity` 計算量とメモリの見積もり：https://yuukougun.github.io/kyopro-atlas/math/segmented-sieve/#complexity
    - `segmented-sieve#patterns` 応用の型：https://yuukougun.github.io/kyopro-atlas/math/segmented-sieve/#patterns

## 素因数の指数で考える（prime-exponent-vector） {#prime-exponent-vector}

- id：`prime-exponent-vector`　レベル：基礎　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/math/prime-exponent-vector/
- 別名：指数ベクトル、平方因子、squarefree、smooth 数、平方数の判定、素数ごとに独立
- 種類：整数論
- 前提：`prime-factorization`
- サイン：
    - 言い回し：積が平方数（立方数）になる組を数える
    - 言い回し：多数の数の lcm を mod で求める
    - 言い回し：2 で割り切れる回数・各素数の指数をそろえる
    - 言い回し：素因数が P 以下の数（P-smooth 数）を数える
- 節：
    - `prime-exponent-vector#exponent-ops` 積は和・gcd は min・lcm は max・割り切りは全成分で ≤（算術の基本定理）：https://yuukougun.github.io/kyopro-atlas/math/prime-exponent-vector/#exponent-ops
    - `prime-exponent-vector#squarefree-kernel` 平方因子を除いた核で、積が平方数になる組を数える（0 の扱い）：https://yuukougun.github.io/kyopro-atlas/math/prime-exponent-vector/#squarefree-kernel
    - `prime-exponent-vector#huge-lcm` 巨大な lcm を指数の最大で持つ（水）：https://yuukougun.github.io/kyopro-atlas/math/prime-exponent-vector/#huge-lcm
    - `prime-exponent-vector#single-prime` 特定の素数（2 など）の指数だけを比べる（水）：https://yuukougun.github.io/kyopro-atlas/math/prime-exponent-vector/#single-prime
    - `prime-exponent-vector#next-steps` XOR 基底・集合のハッシュ・半分全列挙へのつながり：https://yuukougun.github.io/kyopro-atlas/math/prime-exponent-vector/#next-steps

## オイラーの φ 関数（euler-phi） {#euler-phi}

- id：`euler-phi`　レベル：黄　段階：stub　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/math/euler-phi/
- 別名：トーシェント、totient、Euler's totient function、φ(n)、互いに素な数の個数
- 種類：整数論
- 前提：`prime-factorization`
- サイン：
    - 言い回し：n と互いに素な 1..n の数の個数・既約分数の個数
    - 言い回し：位数が d になる元の個数
    - 言い回し：a^k ≡ 1 (mod n) となる最小の k を探す
- 節：
    - `euler-phi#formula` 定義と公式 φ(n) = n Π(1 − 1/p)（素因数分解が必要）：https://yuukougun.github.io/kyopro-atlas/math/euler-phi/#formula
    - `euler-phi#sieve` 篩で 1..N の φ を全て求める：https://yuukougun.github.io/kyopro-atlas/math/euler-phi/#sieve
    - `euler-phi#euler-theorem` オイラーの定理 a^φ(n) ≡ 1 と、指数の mod への応用：https://yuukougun.github.io/kyopro-atlas/math/euler-phi/#euler-theorem
    - `euler-phi#divisor-sum` Σ_{d|n} φ(d) = n と「位数が d の元は φ(d) 個」：https://yuukougun.github.io/kyopro-atlas/math/euler-phi/#divisor-sum

## 大きな数の素数判定と素因数分解（miller-rabin） {#miller-rabin}

- id：`miller-rabin`　レベル：発展　段階：stub　type：overview
- URL：https://yuukougun.github.io/kyopro-atlas/math/miller-rabin/
- 別名：ミラー・ラビン、Miller-Rabin、ポラード・ロー、Pollard's rho、Montgomery 乗算、64bit の素数判定
- 種類：整数論、ハッシュ・乱択
- 前提：`exponent-mod`、`prime-factorization`
- サイン：
    - 制約：N ≤ 10^18 の素数判定・素因数分解（√N の試し割りでは間に合わない）
    - 言い回し：非常に大きい数が素数かを多数判定する
- 節：
    - `miller-rabin#miller-rabin` Miller-Rabin の判定の仕組み（フェルマーの小定理と −1 の現れ方）：https://yuukougun.github.io/kyopro-atlas/math/miller-rabin/#miller-rabin
    - `miller-rabin#deterministic-bases` 決定的な底（32bit は {2, 7, 61}、64bit は 7 個の底）：https://yuukougun.github.io/kyopro-atlas/math/miller-rabin/#deterministic-bases
    - `miller-rabin#pollard-rho` Pollard's rho（x ← x² + c の周期と gcd）：https://yuukougun.github.io/kyopro-atlas/math/miller-rabin/#pollard-rho
    - `miller-rabin#mulmod` 64bit の法での掛け算（\_\_int128・Montgomery・Barrett）：https://yuukougun.github.io/kyopro-atlas/math/miller-rabin/#mulmod
    - `miller-rabin#acl-internal` ACL の内部実装（internal::is_prime_constexpr）：https://yuukougun.github.io/kyopro-atlas/math/miller-rabin/#acl-internal

## GCD・LCM とユークリッドの互除法（gcd-lcm） {#gcd-lcm}

- id：`gcd-lcm`　レベル：基礎　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/math/gcd-lcm/
- 別名：最大公約数、最小公倍数、互除法、Euclidean algorithm、std::gcd、既約分数
- 種類：整数論
- 前提：`integer-division`
- サイン：
    - 言い回し：全員が同時に・周期がそろう最初の時刻（lcm）
    - 言い回し：等間隔に移動して全ての点を訪れられる最大の幅（gcd）
    - 言い回し：1つだけ書き換え（取り除い）たときの gcd の最大
    - 言い回し：分数や傾きが等しいものを同じものとして数える
- 節：
    - `gcd-lcm#euclid` 互除法の正しさ（公約数の集合が変わらない）と回数の上限（隣り合うフィボナッチ数）：https://yuukougun.github.io/kyopro-atlas/math/gcd-lcm/#euclid
    - `gcd-lcm#many-numbers` 複数の数の gcd・lcm と gcd(0, a) = a：https://yuukougun.github.io/kyopro-atlas/math/gcd-lcm/#many-numbers
    - `gcd-lcm#lcm-overflow` lcm のオーバーフロー（割ってから掛ける）：https://yuukougun.github.io/kyopro-atlas/math/gcd-lcm/#lcm-overflow
    - `gcd-lcm#prefix-suffix-gcd` 左右からの累積 gcd（1つ除いた gcd）：https://yuukougun.github.io/kyopro-atlas/math/gcd-lcm/#prefix-suffix-gcd
    - `gcd-lcm#reduce-fraction` 分数・傾きを既約にして map のキーにする（水）：https://yuukougun.github.io/kyopro-atlas/math/gcd-lcm/#reduce-fraction
    - `gcd-lcm#next-steps` 拡張ユークリッド・GCD の性質・素因数の指数へのつながり：https://yuukougun.github.io/kyopro-atlas/math/gcd-lcm/#next-steps

## 拡張ユークリッドの互除法と一次合同式（ext-gcd） {#ext-gcd}

- id：`ext-gcd`　レベル：水　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/math/ext-gcd/
- 別名：拡張 Euclid、extended Euclidean algorithm、extgcd、ベズーの等式、Bézout's identity、ax+by=c、一次不定方程式、linear congruence
- 種類：整数論
- 前提：`gcd-lcm`
- ACL：`inv_mod`
- サイン：
    - 言い回し：ax + by = c を満たす整数の組
    - 言い回し：円周上を K ずつ進んで、何回目で初めて特定の位置に着くか
    - 言い回し：A の倍数を足して、B で割った余りを C にできるか
    - 言い回し：法 M が素数とは限らない一次方程式 a x ≡ b (mod M)
    - 制約：法 M ≤ 10^9 が素数とは限らず、a^(M−2) で逆元を作れない
- 節：
    - `ext-gcd#procedure` 互除法の各段で、余りを a と b の整数係数の組み合わせとして持ち続ける：https://yuukougun.github.io/kyopro-atlas/math/ext-gcd/#procedure
    - `ext-gcd#general-solution` ax + by = c の解の存在条件と一般解 x = x0 + k·b/g：https://yuukougun.github.io/kyopro-atlas/math/ext-gcd/#general-solution
    - `ext-gcd#min-solution` 最小の非負解への調整と、係数のあふれの見積もり：https://yuukougun.github.io/kyopro-atlas/math/ext-gcd/#min-solution
    - `ext-gcd#linear-congruence` 一次合同式 ax ≡ b (mod m) と、gcd で割ること：https://yuukougun.github.io/kyopro-atlas/math/ext-gcd/#linear-congruence
    - `ext-gcd#applications` 応用の型（円周の移動・倍数の余り・面積 1 の格子点・CRT）：https://yuukougun.github.io/kyopro-atlas/math/ext-gcd/#applications
    - `ext-gcd#acl` ACL では（inv_mod の内部の inv_gcd。拡張ユークリッドそのものは公開 API にない）：https://yuukougun.github.io/kyopro-atlas/math/ext-gcd/#acl

## GCD の性質（gcd-properties） {#gcd-properties}

- id：`gcd-properties`　レベル：青　段階：stub　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/math/gcd-properties/
- 別名：差の gcd、区間 gcd、gcd の変化は log 回、gcd と周期
- 種類：整数論、区間クエリ
- 前提：`gcd-lcm`
- サイン：
    - 言い回し：A_i + B_j の矩形・全体に x を足したときの gcd
    - 言い回し：区間の gcd を多数答える
    - 言い回し：mod N で A ずつ進む操作で全ての点に行けるか
    - 制約：N, Q ≤ 2×10^5 で区間 gcd のクエリ
- 節：
    - `gcd-properties#difference-gcd` 差の gcd：gcd(a + x, b + x) = gcd(a + x, b − a)：https://yuukougun.github.io/kyopro-atlas/math/gcd-properties/#difference-gcd
    - `gcd-properties#range-gcd` 区間 gcd はセグメント木・Sparse Table に載る（左端を固定すると値は O(log A) 種類）：https://yuukougun.github.io/kyopro-atlas/math/gcd-properties/#range-gcd
    - `gcd-properties#step-mod` mod N で A ずつ進むと gcd(A, N) の倍数だけを回る（周期と連結性）：https://yuukougun.github.io/kyopro-atlas/math/gcd-properties/#step-mod
    - `gcd-properties#lattice-on-segment` 線分上の格子点は gcd(|dx|, |dy|) + 1 個：https://yuukougun.github.io/kyopro-atlas/math/gcd-properties/#lattice-on-segment
    - `gcd-properties#frobenius` ax + by（x, y ≥ 0）で表せない最大の数 ab − a − b：https://yuukougun.github.io/kyopro-atlas/math/gcd-properties/#frobenius

## 中国剰余定理（crt） {#crt}

- id：`crt`　レベル：青　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/math/crt/
- 別名：CRT、Chinese remainder theorem、中国の剰余定理、Garner、連立合同式
- 種類：整数論
- 前提：`ext-gcd`
- ACL：`crt`
- サイン：
    - 言い回し：周期の違う複数の条件が同時に成り立つ最初の時刻
    - 言い回し：x を m_i で割った余り r_i が複数与えられる
    - 言い回し：法が素数でない数え上げを素因数ごとに分けて最後に戻す
- 節：
    - `crt#two-equations` 2式の CRT は一次不定方程式を1回解くこと：https://yuukougun.github.io/kyopro-atlas/math/crt/#two-equations
    - `crt#non-coprime` 法が互いに素でないときの解の存在条件：https://yuukougun.github.io/kyopro-atlas/math/crt/#non-coprime
    - `crt#many-equations` 多数の式を順に合わせる・lcm のあふれ：https://yuukougun.github.io/kyopro-atlas/math/crt/#many-equations
    - `crt#applications` 応用の型（範囲を余りに直す・分けて戻す）：https://yuukougun.github.io/kyopro-atlas/math/crt/#applications
    - `crt#garner` Garner のアルゴリズム（巨大な解を mod で求める）（黄）：https://yuukougun.github.io/kyopro-atlas/math/crt/#garner
    - `crt#acl` ACL の crt（解がなければ (0, 0)）：https://yuukougun.github.io/kyopro-atlas/math/crt/#acl

## 位数・原始根・離散対数（multiplicative-order） {#multiplicative-order}

- id：`multiplicative-order`　レベル：黄　段階：stub　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/math/multiplicative-order/
- 別名：multiplicative order、primitive root、discrete logarithm、累乗の周期、生成元、BSGS、baby-step giant-step、平方剰余、mod の平方根、mod の K 乗根、Tonelli-Shanks、Cipolla
- 種類：整数論
- 前提：`euler-phi`、`mod-inverse`
- サイン：
    - 言い回し：同じ数字を n 個並べた数が K の倍数になる最小の n
    - 言い回し：a^x ≡ b (mod P) となる最小の x
    - 言い回し：X ← AX + B (mod P) を繰り返して G が最初に現れる番号
    - 言い回し：x^n ≡ y (mod P) となる組を数える
    - 言い回し：mod P での積の値ごとに個数を数える
    - 制約：法 P が 10^9 程度で、√P ≈ 3×10^4 個の表なら持てる
- 節：
    - `multiplicative-order#order` 位数は φ(m) の約数になる理由と、累乗の列の周期：https://yuukougun.github.io/kyopro-atlas/math/multiplicative-order/#order
    - `multiplicative-order#find-order` 位数の求め方（φ(m) の約数を試す・素因数を1つずつ取り除く）：https://yuukougun.github.io/kyopro-atlas/math/multiplicative-order/#find-order
    - `multiplicative-order#primitive-root` 原始根の定義・存在条件（1, 2, 4, p^k, 2p^k）と見つけ方：https://yuukougun.github.io/kyopro-atlas/math/multiplicative-order/#primitive-root
    - `multiplicative-order#count-by-order` 位数が d の元は φ(d) 個：https://yuukougun.github.io/kyopro-atlas/math/multiplicative-order/#count-by-order
    - `multiplicative-order#mul-to-add` 掛け算を指数の足し算に直す（積の個数を畳み込みへ）：https://yuukougun.github.io/kyopro-atlas/math/multiplicative-order/#mul-to-add
    - `multiplicative-order#bsgs` 離散対数：Baby-step Giant-step（表の大きさを √m にする理由）：https://yuukougun.github.io/kyopro-atlas/math/multiplicative-order/#bsgs
    - `multiplicative-order#bsgs-details` gcd(a, m) ≠ 1 の場合と、最小の解の取り方：https://yuukougun.github.io/kyopro-atlas/math/multiplicative-order/#bsgs-details
    - `multiplicative-order#affine-recurrence` 一次漸化式を不動点で等比数列に直して離散対数に帰着する：https://yuukougun.github.io/kyopro-atlas/math/multiplicative-order/#affine-recurrence
    - `multiplicative-order#mod-root` 平方剰余と mod の K 乗根（オイラーの規準・Tonelli-Shanks・Cipolla）（発展）：https://yuukougun.github.io/kyopro-atlas/math/multiplicative-order/#mod-root

## 整数の証明の型（proof-patterns） {#proof-patterns}

- id：`proof-patterns`　レベル：基礎　段階：stub　type：thinking
- URL：https://yuukougun.github.io/kyopro-atlas/math/proof-patterns/
- 別名：整数問題の証明、並べ替え論法、余りの鳩の巣、gcd が不変、mod での矛盾
- 種類：考察、整数論
- 前提：`gcd-lcm`
- サイン：
    - 言い回し：操作を好きなだけ繰り返したとき、最後に残る値や作れる値を答える
    - 言い回し：大きい方から小さい方を引く・余りに置き換える操作を繰り返す
    - 言い回し：区間の幅が法 m 以上なら答えが決まる（余りは m 種類しかない）
- 節：
    - `proof-patterns#gcd-invariant` 操作で gcd が変わらない（互除法の不変量）：https://yuukougun.github.io/kyopro-atlas/math/proof-patterns/#gcd-invariant
    - `proof-patterns#mutual-divisibility` 互いに割り切り合うことで等号を示す：https://yuukougun.github.io/kyopro-atlas/math/proof-patterns/#mutual-divisibility
    - `proof-patterns#rearrangement` 並べ替え論法（a, 2a, …, (p−1)a が余りの並べ替えになる）：https://yuukougun.github.io/kyopro-atlas/math/proof-patterns/#rearrangement
    - `proof-patterns#pigeonhole-remainder` 余りの鳩の巣（m+1 個のうち2つは同じ余り）：https://yuukougun.github.io/kyopro-atlas/math/proof-patterns/#pigeonhole-remainder
    - `proof-patterns#contradiction-mod` mod での矛盾で「できない」を示す：https://yuukougun.github.io/kyopro-atlas/math/proof-patterns/#contradiction-mod
    - `proof-patterns#necessary-sufficient` 必要条件と十分条件（実験の結果を信じてよいか）：https://yuukougun.github.io/kyopro-atlas/math/proof-patterns/#necessary-sufficient

## 整数の平方根・K 乗根と累乗数（integer-root） {#integer-root}

- id：`integer-root`　レベル：基礎　段階：stub　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/math/integer-root/
- 別名：isqrt、integer square root、整数平方根、累乗数、perfect power、誤差のない平方根、sqrt の誤差
- 種類：整数論、二分探索
- 前提：`integer-division`
- サイン：
    - 制約：N ≤ 10^18 で平方数・平方根を扱う
    - 言い回し：a^b（b ≥ 2）の形で表せる N 以下の数
    - 言い回し：2^a × b² のように累乗を組み合わせた数を数える
- 節：
    - `integer-root#sqrt-correction` sqrt の誤差と補正（r² ≤ N < (r+1)² を確かめる）：https://yuukougun.github.io/kyopro-atlas/math/integer-root/#sqrt-correction
    - `integer-root#kth-root` 二分探索による整数の K 乗根（途中の累乗のあふれ）：https://yuukougun.github.io/kyopro-atlas/math/integer-root/#kth-root
    - `integer-root#perfect-powers` 累乗数の数え上げ（b ≥ 3 は列挙、b = 2 は ⌊√N⌋、重複を除く）：https://yuukougun.github.io/kyopro-atlas/math/integer-root/#perfect-powers
    - `integer-root#compare-sqrt` √ を含む式の大小を整数で比べる：https://yuukougun.github.io/kyopro-atlas/math/integer-root/#compare-sqrt

## N 進法（base-conversion） {#base-conversion}

- id：`base-conversion`　レベル：基礎　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/math/base-conversion/
- 別名：基数変換、base conversion、b 進法、n 進数、−2 進法、26 進、Horner 法
- 種類：整数論
- 前提：`integer-division`
- サイン：
    - 言い回し：b 進法・−2 進法で表す
    - 言い回し：a, b, …, z, aa, ab, … と続く名前の n 番目
    - 言い回し：文字列を n 進数とみた値が M 以下になる n を数える
- 節：
    - `base-conversion#convert` b 進表記への変換と Horner 法による復元（0 の扱い）：https://yuukougun.github.io/kyopro-atlas/math/base-conversion/#convert
    - `base-conversion#bijective-26` 1 始まりの 26 進（1 を引いてから割る）：https://yuukougun.github.io/kyopro-atlas/math/base-conversion/#bijective-26
    - `base-conversion#negative-base` 負の基数（余りを 0 以上に直してから割る）（水）：https://yuukougun.github.io/kyopro-atlas/math/base-conversion/#negative-base
    - `base-conversion#base-binary-search` 基数の二分探索とオーバーフロー（1 桁の場合分け）（水）：https://yuukougun.github.io/kyopro-atlas/math/base-conversion/#base-binary-search

## 商の列挙（floor-quotient-enum） {#floor-quotient-enum}

- id：`floor-quotient-enum`　レベル：水　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/math/floor-quotient-enum/
- 別名：商列挙、enumerate quotients、数論分块、√N 分割、floor でまとめる、約数の個数の和
- 種類：整数論
- 前提：`sigma-manipulation`、`integer-division`
- サイン：
    - 言い回し：Σ_{i=1}^{N} ⌊N/i⌋ を求める
    - 制約：N ≤ 10^12 で i を全部回すと間に合わない
    - 言い回し：xy ≤ N となる組を数える
    - 式の形：Σ_{i=1}^{N} f(⌊N/i⌋) の形の和
- 節：
    - `floor-quotient-enum#why-sqrt` 値が O(√N) 種類である理由（i ≤ √N と i > √N）：https://yuukougun.github.io/kyopro-atlas/math/floor-quotient-enum/#why-sqrt
    - `floor-quotient-enum#block-end` 同じ商になる区間の右端 ⌊N/⌊N/l⌋⌋：https://yuukougun.github.io/kyopro-atlas/math/floor-quotient-enum/#block-end
    - `floor-quotient-enum#split-at-sqrt` √N を境に場合分けする（片方を √N まで全探索）：https://yuukougun.github.io/kyopro-atlas/math/floor-quotient-enum/#split-at-sqrt
    - `floor-quotient-enum#vs-others` 調和級数・floor sum との使い分け：https://yuukougun.github.io/kyopro-atlas/math/floor-quotient-enum/#vs-others

## 乗法的関数の和と素数の個数（multiplicative-function） {#multiplicative-function}

- id：`multiplicative-function`　レベル：発展　段階：stub　type：overview
- URL：https://yuukougun.github.io/kyopro-atlas/math/multiplicative-function/
- 別名：ディリクレ積、Dirichlet convolution、杜教筛、Min_25、乗法的関数の prefix sum、素数計数、prime counting、Lucy DP、Meissel-Lehmer
- 種類：整数論
- 前提：`euler-phi`、`floor-quotient-enum`
- サイン：
    - 制約：N ≤ 10&#94;10〜10&#94;11 で Σ_{n≤N} f(n)（f は φ・約数の個数など）を求める
    - 言い回し：N 以下の素数の個数・素数の和
- 節：
    - `multiplicative-function#dirichlet` 乗法的関数（φ・μ・d・σ）とディリクレ積（φ \* 1 = id など）：https://yuukougun.github.io/kyopro-atlas/math/multiplicative-function/#dirichlet
    - `multiplicative-function#prefix-sums` 和の求め方の概要（杜教筛・Lucy DP・Min_25）：https://yuukougun.github.io/kyopro-atlas/math/multiplicative-function/#prefix-sums
    - `multiplicative-function#prime-counting` 素数の個数・素数の和（Lucy DP）：https://yuukougun.github.io/kyopro-atlas/math/multiplicative-function/#prime-counting

## floor sum（floor-sum） {#floor-sum}

- id：`floor-sum`　レベル：黄　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/math/floor-sum/
- 別名：floor_sum、類ユークリッド、sum of floor of linear、mod of linear、一次式の mod の和、直線の下の格子点
- 種類：整数論
- 前提：`sigma-manipulation`、`gcd-lcm`
- ACL：`floor_sum`
- サイン：
    - 言い回し：Σ ⌊(ai + b)/m⌋ や Σ (ai + b) mod m を求める
    - 言い回し：(Ak + B) mod M が条件を満たす k の個数
    - 言い回し：直線の下にある格子点の数
    - 制約：n, m ≤ 10^9 程度で i を全部回せない
- 節：
    - `floor-sum#reduce` a ≥ m・b ≥ m の部分を式で取り除く：https://yuukougun.github.io/kyopro-atlas/math/floor-sum/#reduce
    - `floor-sum#swap-axes` 直線の下の格子点とみて縦横を入れ替える（互除法と同じ再帰）：https://yuukougun.github.io/kyopro-atlas/math/floor-sum/#swap-axes
    - `floor-sum#why-log` なぜ O(log m) で終わるか：https://yuukougun.github.io/kyopro-atlas/math/floor-sum/#why-log
    - `floor-sum#procedure` 処理の流れと自作するときの要点：https://yuukougun.github.io/kyopro-atlas/math/floor-sum/#procedure
    - `floor-sum#mod-to-floor` x mod m = x − m⌊x/m⌋ への書き換え：https://yuukougun.github.io/kyopro-atlas/math/floor-sum/#mod-to-floor
    - `floor-sum#acl` ACL の floor_sum（引数の範囲と負の a, b）：https://yuukougun.github.io/kyopro-atlas/math/floor-sum/#acl
    - `floor-sum#applications` 応用の型：bit ごとの popcount・一次式の mod の積（発展）：https://yuukougun.github.io/kyopro-atlas/math/floor-sum/#applications

## Stern-Brocot 木と連分数（stern-brocot） {#stern-brocot}

- id：`stern-brocot`　レベル：発展　段階：stub　type：overview
- URL：https://yuukougun.github.io/kyopro-atlas/math/stern-brocot/
- 別名：Stern-Brocot tree、continued fraction、最良近似、最良有理近似、Farey 数列、有理数の二分探索
- 種類：整数論、二分探索
- 前提：`gcd-lcm`
- サイン：
    - 言い回し：分母・分子が N 以下で、与えられた実数に最も近い分数
    - 言い回し：分数の範囲を二分探索する
- 節：
    - `stern-brocot#tree` Stern-Brocot 木と既約分数：https://yuukougun.github.io/kyopro-atlas/math/stern-brocot/#tree
    - `stern-brocot#continued-fraction` 同じ方向の移動を一度に進める（連分数）：https://yuukougun.github.io/kyopro-atlas/math/stern-brocot/#continued-fraction
    - `stern-brocot#best-approximation` 最良有理近似と比較の精度（128bit 整数）：https://yuukougun.github.io/kyopro-atlas/math/stern-brocot/#best-approximation

## 行列累乗（matrix-power） {#matrix-power}

- id：`matrix-power`　レベル：青　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/math/matrix-power/
- 別名：行列の累乗、matrix exponentiation、行列累乗 DP、遷移行列、隣接行列の累乗、min-plus 行列、(max,+) 行列、半環の行列
- 種類：線形代数・行列、DP、ダブリング・分割統治
- 前提：`mod-pow`、`dp-state-design`
- サイン：
    - 制約：状態数 n ≤ 100 程度で、繰り返しの回数 K が 10&#94;9〜10&#94;18
    - 言い回し：漸化式の第 N 項（N ≤ 10^18）
    - 言い回し：グラフでちょうど K 歩の経路の数・K 本の辺を使う最短路
    - 言い回し：長さ 10^18 の文字列のうち、禁止された部分文字列を含まないものの数
    - 言い回し：幅の小さい盤を長く伸ばしたときの敷き詰め方の数
    - 式の形：dp[t+1] の各成分が dp[t] の成分の線形結合で、係数が t によらない
- 節：
    - `matrix-power#write-as-matrix` 漸化式・状態の遷移を行列で書く（定数項を状態に入れる）：https://yuukougun.github.io/kyopro-atlas/math/matrix-power/#write-as-matrix
    - `matrix-power#fast-power` 行列の積と繰り返し二乗法（積の向き・単位行列・n³ log K の見積もり・mod の掛け算のあふれ）：https://yuukougun.github.io/kyopro-atlas/math/matrix-power/#fast-power
    - `matrix-power#adjacency-power` 隣接行列の K 乗と長さ K の経路の数：https://yuukougun.github.io/kyopro-atlas/math/matrix-power/#adjacency-power
    - `matrix-power#dp-transition` DP の遷移を行列にする（照合の状態・末尾の数文字・グリッドの境界の状態）：https://yuukougun.github.io/kyopro-atlas/math/matrix-power/#dp-transition
    - `matrix-power#semiring` (min,+)・(max,+) などの半環の行列と単位元・零元：https://yuukougun.github.io/kyopro-atlas/math/matrix-power/#semiring
    - `matrix-power#composition` 累乗でなく合成として使う（アフィン変換の積）：https://yuukougun.github.io/kyopro-atlas/math/matrix-power/#composition
    - `matrix-power#doubling-transition` ダブリングで遷移を合成する（行列にすると大きすぎるとき・桁を倍々に伸ばす）（黄）：https://yuukougun.github.io/kyopro-atlas/math/matrix-power/#doubling-transition
    - `matrix-power#profile-dp` プロファイル DP の遷移行列と状態数の見積もり（黄）：https://yuukougun.github.io/kyopro-atlas/math/matrix-power/#profile-dp

## 掃き出し法（gaussian-elimination） {#gaussian-elimination}

- id：`gaussian-elimination`　レベル：青　段階：stub　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/math/gaussian-elimination/
- 別名：ガウスの消去法、Gaussian elimination、Gauss-Jordan、連立一次方程式、ランク、ライツアウト、mod 2 の連立方程式
- 種類：線形代数・行列
- 前提：`mod-inverse`
- サイン：
    - 言い回し：スイッチを押すと複数のランプが反転する・偶奇の条件が N 個ある
    - 言い回し：条件を満たす押し方の数を mod で答える
    - 言い回し：各頂点に書いた値の、隣接する頂点の XOR が 0 になるように決める
    - 制約：変数・式の数が数百〜2000 程度で O(n³) や O(n³/64)
    - 式の形：変数の一次式（mod 2 なら XOR）＝定数 の式が複数立つ
- 節：
    - `gaussian-elimination#row-reduction` 行基本変形と階段形、解なし（0 = 1）・一意・無数の判定：https://yuukougun.github.io/kyopro-atlas/math/gaussian-elimination/#row-reduction
    - `gaussian-elimination#mod-p` mod p の掃き出し（ピボットで割る＝逆元）：https://yuukougun.github.io/kyopro-atlas/math/gaussian-elimination/#mod-p
    - `gaussian-elimination#mod-2` mod 2 の掃き出しは XOR、bitset で速くする：https://yuukougun.github.io/kyopro-atlas/math/gaussian-elimination/#mod-2
    - `gaussian-elimination#rank` ランクと解の個数 p^(n − rank)：https://yuukougun.github.io/kyopro-atlas/math/gaussian-elimination/#rank
    - `gaussian-elimination#real` 実数の掃き出し（部分ピボット選択と誤差）：https://yuukougun.github.io/kyopro-atlas/math/gaussian-elimination/#real

## XOR 基底（xor-basis） {#xor-basis}

- id：`xor-basis`　レベル：黄　段階：stub　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/math/xor-basis/
- 別名：XOR basis、線形基底、linear basis、F2 の基底、部分集合の XOR、XOR で作れる値、閉路基底、サイクル基底、サイクル空間、XOR 最短路
- 種類：線形代数・行列、ビット演算
- 前提：`bit-operations`
- サイン：
    - 言い回し：部分集合（部分列）の XOR として作れる値の個数・最大値・K 番目
    - 言い回し：全ての値を XOR で作れるように最小コストで選ぶ
    - 言い回し：経路の重みが辺の重みの XOR で、同じ辺を何度通ってもよい（ウォーク）
    - 制約：A_i < 2^60 で N ≤ 10^5 程度
- 節：
    - `xor-basis#insert` 基底への挿入（最上位 bit で掃き出す。1 要素 O(bit 数)）：https://yuukougun.github.io/kyopro-atlas/math/xor-basis/#insert
    - `xor-basis#count` 作れる値の個数 2^r と作り方の数 2^(n − r)：https://yuukougun.github.io/kyopro-atlas/math/xor-basis/#count
    - `xor-basis#max` XOR の最大値は上の bit から貪欲に決めてよい理由：https://yuukougun.github.io/kyopro-atlas/math/xor-basis/#max
    - `xor-basis#kth` 簡約した基底と K 番目に小さい値：https://yuukougun.github.io/kyopro-atlas/math/xor-basis/#kth
    - `xor-basis#min-cost` コストの小さい順に基底へ入れる貪欲（線形マトロイド）：https://yuukougun.github.io/kyopro-atlas/math/xor-basis/#min-cost
    - `xor-basis#xor-walk` グラフのウォークの XOR（全域木の根からの XOR と、閉路の XOR の基底）：https://yuukougun.github.io/kyopro-atlas/math/xor-basis/#xor-walk

## 行列式（determinant） {#determinant}

- id：`determinant`　レベル：発展　段階：stub　type：overview
- URL：https://yuukougun.github.io/kyopro-atlas/math/determinant/
- 別名：determinant、行列式 mod p
- 種類：線形代数・行列
- 前提：`gaussian-elimination`
- サイン：
    - 言い回し：行列式を mod p で求める
    - 言い回し：全域木の個数・交わらない経路の組の数
- 節：
    - `determinant#by-elimination` 掃き出しで行列式を求める（行の交換で符号が変わる）：https://yuukougun.github.io/kyopro-atlas/math/determinant/#by-elimination
    - `determinant#modulus` mod p での計算と、法が素数でない場合（互除法による掃き出し）：https://yuukougun.github.io/kyopro-atlas/math/determinant/#modulus
    - `determinant#applications` 行列木定理・LGV 補題への入口：https://yuukougun.github.io/kyopro-atlas/math/determinant/#applications

## 畳み込みの使い方（convolution-ntt） {#convolution-ntt}

- id：`convolution-ntt`　レベル：青　段階：stub　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/math/convolution-ntt/
- 別名：畳み込み、convolution、多項式の積、ACL の convolution、convolution_ll、ずらしたときの一致数、全シフトのハミング距離、ワイルドカード照合
- 種類：畳み込み・多項式
- 前提：`mod-arithmetic`
- ACL：`convolution`、`convolution_ll`
- サイン：
    - 言い回し：全ての k について、和が k になる組の数を求める
    - 言い回し：列をずらしたときの一致数・不一致の数を、全てのずらし方について求める
    - 言い回し：ワイルドカード（?）を含むパターンの照合
    - 制約：値の範囲や列の長さが 10&#94;5〜10&#94;6 程度で、組の全探索 O(N²) が間に合わない
    - 式の形：c_k = Σ_{i+j=k} a_i b_j の形の和
- 節：
    - `convolution-ntt#sum-pairs` i + j = k の形に言い換える（出現回数の配列）：https://yuukougun.github.io/kyopro-atlas/math/convolution-ntt/#sum-pairs
    - `convolution-ntt#reverse` i − j = k の形は片方を反転する：https://yuukougun.github.io/kyopro-atlas/math/convolution-ntt/#reverse
    - `convolution-ntt#length-mod` 結果の長さと mod（998244353 での値しか返らない）：https://yuukougun.github.io/kyopro-atlas/math/convolution-ntt/#length-mod
    - `convolution-ntt#convolution-ll` 整数のまま・mod 10^9+7 で欲しいとき（convolution_ll）：https://yuukougun.github.io/kyopro-atlas/math/convolution-ntt/#convolution-ll
    - `convolution-ntt#string-matching` 文字列の照合：ずらしたときの一致数・ハミング距離・ワイルドカード（黄）：https://yuukougun.github.io/kyopro-atlas/math/convolution-ntt/#string-matching
    - `convolution-ntt#split-by-bit` bit ごと・文字ごとに分けて畳み込む（OR の和など）（黄）：https://yuukougun.github.io/kyopro-atlas/math/convolution-ntt/#split-by-bit
    - `convolution-ntt#acl` ACL の convolution の要件（法の形と長さ）：https://yuukougun.github.io/kyopro-atlas/math/convolution-ntt/#acl

## FFT・NTT の仕組みと任意 mod の畳み込み（fft-ntt） {#fft-ntt}

- id：`fft-ntt`　レベル：発展　段階：stub　type：overview
- URL：https://yuukougun.github.io/kyopro-atlas/math/fft-ntt/
- 別名：FFT、NTT、高速フーリエ変換、fast Fourier transform、数論変換、number theoretic transform、任意 mod 畳み込み、3 素数 NTT
- 種類：畳み込み・多項式
- 前提：`convolution-ntt`
- ACL：`convolution`、`convolution_ll`
- サイン：
    - 言い回し：mod 10^9+7 や整数のままで畳み込みたい
    - 言い回し：畳み込みを自作ライブラリで実装したい・浮動小数の FFT の誤差が心配
- 節：
    - `fft-ntt#point-value` 点での値に直すと掛け算が O(N)（多項式の値表現）：https://yuukougun.github.io/kyopro-atlas/math/fft-ntt/#point-value
    - `fft-ntt#butterfly` 1 の N 乗根と分割統治（バタフライ）：https://yuukougun.github.io/kyopro-atlas/math/fft-ntt/#butterfly
    - `fft-ntt#ntt-prime` 複素数の FFT と誤差、NTT に向く素数（c·2^k + 1）と原始根：https://yuukougun.github.io/kyopro-atlas/math/fft-ntt/#ntt-prime
    - `fft-ntt#arbitrary-mod` 任意 mod の畳み込み（3 素数 NTT と Garner、convolution_ll）：https://yuukougun.github.io/kyopro-atlas/math/fft-ntt/#arbitrary-mod

## XOR 畳み込み（hadamard-transform） {#hadamard-transform}

- id：`hadamard-transform`　レベル：発展　段階：stub　type：overview
- URL：https://yuukougun.github.io/kyopro-atlas/math/hadamard-transform/
- 別名：アダマール変換、Walsh-Hadamard、FWHT、XOR convolution、添字の XOR の畳み込み
- 種類：畳み込み・多項式、ビット演算
- 前提：`convolution-ntt`、`bit-operations`
- サイン：
    - 言い回し：i XOR j = k となる組を全ての k について数える
    - 言い回し：XOR が 0 でない Nim の盤面の数を数える
    - 制約：値が 2&#94;16〜2&#94;20 程度で、添字の XOR で畳み込む
- 節：
    - `hadamard-transform#transform` アダマール変換と逆変換（各 bit で (x + y, x − y)）：https://yuukougun.github.io/kyopro-atlas/math/hadamard-transform/#transform
    - `hadamard-transform#power` 同じ配列を K 回 XOR 畳み込みする（変換後の累乗）：https://yuukougun.github.io/kyopro-atlas/math/hadamard-transform/#power
    - `hadamard-transform#index-operations` 添字の演算と変換の対応（和は FFT、AND/OR は高速ゼータ変換、gcd/lcm は約数のゼータ変換）：https://yuukougun.github.io/kyopro-atlas/math/hadamard-transform/#index-operations

## 分割統治 FFT・オンライン畳み込み（online-convolution） {#online-convolution}

- id：`online-convolution`　レベル：発展　段階：stub　type：overview
- URL：https://yuukougun.github.io/kyopro-atlas/math/online-convolution/
- 別名：online convolution、relaxed convolution、多項式の積の分割統治、FFT DP、多項式で DP
- 種類：畳み込み・多項式、DP、ダブリング・分割統治
- 前提：`convolution-ntt`
- ACL：`convolution`
- サイン：
    - 言い回し：Π(1 + a_i x) のような多数の一次式の積の係数
    - 式の形：dp[i] = Σ_{j&lt;i} dp[j]·g[i−j] のように、dp が自分より前の値との畳み込みで決まる
    - 式の形：遷移が「和が s になる組の数」の形（多項式の積）
- 節：
    - `online-convolution#product-of-many` 多数の多項式の積（次数の小さいものから掛ける・分割統治）：https://yuukougun.github.io/kyopro-atlas/math/online-convolution/#product-of-many
    - `online-convolution#dp-as-polynomial` DP の遷移を多項式の積とみる：https://yuukougun.github.io/kyopro-atlas/math/online-convolution/#dp-as-polynomial
    - `online-convolution#online` オンライン畳み込み（左半分を確定させてから右半分へ寄与を足す）：https://yuukougun.github.io/kyopro-atlas/math/online-convolution/#online

## 形式的冪級数と多項式の演算（fps-basics） {#fps-basics}

- id：`fps-basics`　レベル：発展　段階：stub　type：overview
- URL：https://yuukougun.github.io/kyopro-atlas/math/fps-basics/
- 別名：FPS、formal power series、多項式の逆元、多項式の割り算、Taylor shift、多点評価、冪級数の log・exp
- 種類：畳み込み・多項式、数え上げ
- 前提：`convolution-ntt`、`mod-inverse`
- ACL：`convolution`
- サイン：
    - 言い回し：(1 + x^v) を掛ける・割るように、集合への追加と削除を繰り返して個数の分布を求める
    - 言い回し：次数の条件つきの木や個数の分布を、多項式の累乗の係数として数える
    - 式の形：答えが多項式 f の 1/f・log f・exp f・f^K の係数で書ける
- 節：
    - `fps-basics#operations` 演算の一覧と計算量（inv・log・exp・pow・sqrt）：https://yuukougun.github.io/kyopro-atlas/math/fps-basics/#operations
    - `fps-basics#polynomial-ops` 多項式の割り算・Taylor shift・多点評価：https://yuukougun.github.io/kyopro-atlas/math/fps-basics/#polynomial-ops

## 線形漸化式の高速化（linear-recurrence-fast） {#linear-recurrence-fast}

- id：`linear-recurrence-fast`　レベル：発展　段階：stub　type：overview
- URL：https://yuukougun.github.io/kyopro-atlas/math/linear-recurrence-fast/
- 別名：きたまさ法、Bostan-Mori、Berlekamp-Massey、Fiduccia、線形漸化式の第 N 項
- 種類：線形代数・行列、畳み込み・多項式
- 前提：`matrix-power`、`fps-basics`
- ACL：`convolution`
- サイン：
    - 制約：線形漸化式の項数 K が数百〜数千で、N ≤ 10^18
    - 言い回し：有理式 P(x)/Q(x) の N 次の係数
    - 言い回し：答えが線形漸化式を満たしそうだが式が分からない（最初の項から推定する）
    - 式の形：a_n = Σ_{k=1}^{K} c_k a_{n−k} の形の漸化式
- 節：
    - `linear-recurrence-fast#vs-matrix` 行列累乗との比較（いつ必要になるか）：https://yuukougun.github.io/kyopro-atlas/math/linear-recurrence-fast/#vs-matrix
    - `linear-recurrence-fast#kitamasa` きたまさ法（x^N mod 特性多項式）：https://yuukougun.github.io/kyopro-atlas/math/linear-recurrence-fast/#kitamasa
    - `linear-recurrence-fast#bostan-mori` Bostan-Mori（Q(x)Q(−x) で次数を半分にする）：https://yuukougun.github.io/kyopro-atlas/math/linear-recurrence-fast/#bostan-mori
    - `linear-recurrence-fast#berlekamp-massey` Berlekamp-Massey（漸化式を見つける）：https://yuukougun.github.io/kyopro-atlas/math/linear-recurrence-fast/#berlekamp-massey
    - `linear-recurrence-fast#implementation` ACL の convolution を使った実装：https://yuukougun.github.io/kyopro-atlas/math/linear-recurrence-fast/#implementation

## ラグランジュ補間とべき乗和（lagrange-interpolation） {#lagrange-interpolation}

- id：`lagrange-interpolation`　レベル：発展　段階：stub　type：overview
- URL：https://yuukougun.github.io/kyopro-atlas/math/lagrange-interpolation/
- 別名：Lagrange interpolation、多項式補間、補間、べき乗和、Faulhaber、答えが多項式になる
- 種類：畳み込み・多項式
- 前提：`mod-inverse`
- サイン：
    - 言い回し：答えが N の多項式になる（小さい N で実験すると分かる）
    - 言い回し：Σ_{i=1}^{N} i^k を N ≤ 10^18 で求める
    - 言い回し：mod p で p 点の値から多項式の係数を復元する
    - 式の形：答え f(N) が N の d 次多項式になる
- 節：
    - `lagrange-interpolation#uniqueness` d + 1 点で多項式が決まる理由：https://yuukougun.github.io/kyopro-atlas/math/lagrange-interpolation/#uniqueness
    - `lagrange-interpolation#linear-time` x = 0..d のときの O(d) の補間（階乗の逆元）：https://yuukougun.github.io/kyopro-atlas/math/lagrange-interpolation/#linear-time
    - `lagrange-interpolation#applications` べき乗和・多項式になる DP への応用：https://yuukougun.github.io/kyopro-atlas/math/lagrange-interpolation/#applications
    - `lagrange-interpolation#coefficients` 係数の復元（O(d²)）：https://yuukougun.github.io/kyopro-atlas/math/lagrange-interpolation/#coefficients
