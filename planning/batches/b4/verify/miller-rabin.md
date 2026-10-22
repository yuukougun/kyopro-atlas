# b4 検証：miller-rabin

- 対象：docs/math/miller-rabin.md、snippets/miller-rabin/factorize.{cpp,yaml}、docs/img/miller-rabin/rho.svg
- 観点：fact.md・code.md・clarity.md・figure.md
- 環境：g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0。図は `python3 tools/render_svg.py --out <作業用の場所> docs/img/miller-rabin/rho.svg` で 360px・720px の PNG にして目で確かめた

## 実行して確かめたこと

- `python3 tools/check_pages.py --page miller-rabin`：エラー 0・警告 0
- `python3 tools/check_snippets.py -v snippets/miller-rabin`：factorize.cpp（g++-15・run）3 case 一致
- `g++-15 -std=gnu++23 -O2 -Wall -Wextra -fsanitize=address,undefined` で取り込み部分を別の試験に入れて動かした（作業用の場所）：
    - `is_prime` を $5 \times 10^6$ までのエラトステネスの篩とすべて比べて一致
    - 底の素因数で 37 より大きい素数 407521（9780504 の因数）・299210837（1795265022 の因数）を素数と判定（`a % n == 0` の飛ばしが効く）。底を割る合成数 14089 = 73 × 193（28178 の因数）・73 × 407521 を合成数と判定
    - 強擬素数の 3215031751・3825123056546413051 を合成数と判定
    - 乱数の 200 個（$10^{18}$ 以下）の分解で、積が元の数に戻り、すべての因数が素数。$999999929 \times 999999937$ を含めて全体 0.025 秒（サニタイザ付き）。導入の「1 秒よりずっと短い」は正しい（執筆者の未解決 1）
- 数値をプログラムで計算し直した（Python）：
    - 561 で底 2：$2^{35}, 2^{70}, 2^{140}, 2^{280}, 2^{560} \equiv 263, 166, 67, 1, 1$、$67^2 \equiv 1$。本文と一致
    - 221 で底 174：$47, 220$。底 137：$188, 205$。本文と一致
    - $48781 \times 97561 = 4759123141$ で、底 2・7・61 のすべてで強い判定を通る。本文と一致
    - $325 = 5^2 \times 13$ など底の素因数分解。本文の「$n = 5$ や $n = 13$ で $a \equiv 0$」は正しい
    - rho の例：$x = 2, 7, 52, 42, 168, 511, 487, 520, 172, 272, 433, \dots$（mod 533）、mod 13 は $2, 7, 0, 3, 12, 4, 6, 0, \dots$。$i = 1..4$ では $\gcd(\lvert x_i - x_{2i} \rvert, 533) = 1$、$i = 5$ で $x_5 = 511$、$x_{10} = 433$、$\gcd(78, 533) = 13$。mod 41 では周期がそろわない。本文・図・代替テキストと一致
    - $\sqrt[3]{9 \times 10^{18}} \approx 2.08 \times 10^6$。本文の $2.1 \times 10^6$ と一致
    - 奇数の合成数 $9 \le n < 3000$ のすべてで、強い判定をすり抜ける底の数が $(n - 1)/4$ 以下（$n = 9$ でちょうど $2/8$）。本文の「$1$ 以上 $n - 1$ 以下の $a$ の高々 $1/4$」は正しい
- 一次資料：
    - ACL のソース（third_party/ac-library/atcoder/internal_math.hpp・modint.hpp）：`is_prime_constexpr(int n)` は $n \in \{2, 7, 61\}$ を先に true、底 $2, 7, 61$。`is_prime<m>` を `static_modint` が `static constexpr bool prime` として使い、`inv()` を切り替える。`dynamic_modint` は `internal::barrett`。本文と一致
    - library-checker-problems（GitHub。check_noai で noai 指定なし）：primality_test は timelimit 5.0・$Q \le 10^5$・$N \le 10^{18}$。factorize は timelimit 10.0・$Q \le 100$・$a \le 10^{18}$・出力は昇順、solutions に `fixed_RNG.cpp`（expect TLE）。テスト名 `999381247093216751.cpp` もある。本文と一致
    - drken「ミラー・ラビンの素数判定法」：`__uint128_t` 1783 ms、Montgomery 247 ms、底の組 $\{2, 7, 61\}$（$< 4{,}759{,}123{,}141$）と 7 個の組。本文と一致。記事の数値例は 97・161・2047 で、本文の例とは別
    - Wikipedia「Miller–Rabin primality test」：$2, 7, 61$ と $4{,}759{,}123{,}141$ の記述あり。ただし下の指摘 1
- 図：360px で文字は読める大きさで、重なり・はみ出しなし。矢印は $2 \to 7 \to 0 \to 3 \to 12 \to 4 \to 6 \to 0$ の向きで正しい。白の背景つき、`viewBox` と `width`・`height` が同じ比（380×345）、`font-family="sans-serif"`、相対パスで参照。catalog の visual は null なので G7 は対象外
- リンク先の anchor（exponent-mod#fermat、prime-factorization#procedure、mod-pow#pitfalls、cpp-integer-overflow#int128、randomized#failure-probability・#cpp-random、用語集 #birthday-paradox）はすべてある
- front matter：変えたのは complexity・sections（2 つの title の文字と library の追加。anchor は不変）・stage・updated（git diff で確かめた）。summary と要点の「何ができるか」は同じ文。complexity と要点の計算量は一致
- コード片の書き方：`u64`・`u128` の別名は §15-9 の例外、補助のラムダ `f` は §9・§15-9 の「短い補助の関数」に入る。`endl` なし

## 指摘

### 1. 直すべき｜事実（F8）｜#quiz の 1 問目

- **問題**：確認問題の例「$n = 221 = 13 \times 17$、$a = 174$ はすり抜け、$174^{55} \equiv 47$、$174^{110} \equiv 220$。$a = 137$ なら $137^{55} \equiv 188$、$137^{110} \equiv 205$ で合成数と分かる」は、英語版 Wikipedia「Miller–Rabin primality test」の例（n = 221 を、強い嘘つきの底 174 と証拠の底 137 で調べる）と、数・底・途中の値・話の運び（まず 174 で通り、次に 137 で見抜く）までそのまま同じである
- **根拠**：Wikipedia の該当記事の例の節（"n = 221 … a = 174 … 47 … 220 … a = 137 … 188 … 205 … 174 was in fact a strong liar"）。fact.md F8 の「よくある失敗：記事の例をそのまま使う（同じ数値・同じ図）」
- **直し方**：別の合成数と底に替える。例えば小さい奇数の合成数で強い嘘つきの底を自分で探し（$n = 9$ の底 8、$n = 25$ の底 7、$n = 91$ の底 9 など。作業用のプログラムで、$n - 1 = 2^s d$ の列に $-1$ が現れるか先頭が 1 かを確かめる）、同じ $n$ で証拠になる底も 1 つ添える。問いの形（1 つの底では足りない理由）はそのままでよい

### 2. 直すとよい｜分かりやすさ・事実（U8・F2）｜#quiz の 2 問目の答え

- **問題**：「$n$ のすべての素因数について、同じときに余りがそろった（$x \equiv y \pmod n$）とき」は、$n$ が平方因子を持つと不正確である。$n = p^2$ では $x \equiv y \pmod p$ でも $\pmod{p^2}$ でそろわなければ $g = p$ が得られる（コード片の case の $65537^2$ がこの形）。括弧内の $x \equiv y \pmod n$ は正しいが、前半の言い方と食い違う
- **根拠**：$\gcd(\lvert x - y \rvert, n) = n \iff n \mid x - y$。$n = p^2 q$ では $p^2$ と $q$ のそれぞれで差が割り切れることが条件
- **直し方**：「$x \equiv y \pmod n$、つまり $n$ を割るすべての素数べき（$p^2$ なども含む）で同じときに余りがそろったとき」とするか、前半を削って「$x \equiv y \pmod n$ になったとき（どの素因数についても、余りが同じ歩数でそろったとき）」とする

### 3. 直すとよい｜コード（C3）｜#pollard-rho の擬似コードと snippets/miller-rabin/factorize.cpp の `find_factor`

- **問題**：本文の擬似コードと確認問題は約数を $g$ と呼ぶが、コード片は `d` と書く。`d` は同じページの Miller-Rabin で $n - 1 = 2^s d$ の奇数の部分を指すので、断片で読むと取り違えやすい
- **根拠**：code.md C3「本文の記号とコードの変数名が違う」
- **直し方**：`find_factor` の `d` を `g` にする（`while (g == 1)`、`if (g != n) return g;`）。`factor_rec` の `u64 d = find_factor(n);` も `g` にそろえる

### 4. 直すとよい｜事実（F4）｜#mulmod の Barrett 還元の項

- **問題**：「ACL の `dynamic_modint`（法は `int` の範囲）」とあるが、v1.6 のドキュメントの `set_mod` の制約は $1 \le m \le 2 \times 10^9 + 1000$ で、`int` の最大値（約 $2.147 \times 10^9$）までではない
- **根拠**：~/lib/ac-library-master/document_ja/modint.md の set_mod の制約
- **直し方**：「（法は $2 \times 10^9$ 程度まで）」か「（法は 32 bit に収まる範囲）」とする

## 総合の判定

小さな直しで可。直すべき 1 件（確認問題の例が Wikipedia の例と同じ）、直すとよい 3 件。事実・計算量・数値・コード片・図は確かめた範囲で誤りはない。執筆者の未解決 1（1 秒よりずっと短い）は計測で裏付けた。未解決 2（rho の $O(\sqrt{p})$ が発見的な見積もり）は本文にそう書かれており十分。未解決 3（Barrett の 64bit 版に触れない）は発展の概要として問題ない。
