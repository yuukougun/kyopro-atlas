# geometric-series-mod の検証（工程8b・b1）

- 対象：docs/math/geometric-series-mod.md、snippets/geometric-series-mod/（formula・halving・repeat の 3 組）、docs/img/geometric-series-mod/halving.svg
- 観点：planning/checklists/ の fact.md・code.md・clarity.md・figure.md、手引き planning/style-guide.md、執筆者の報告 planning/batches/b1/geometric-series-mod.md の未解決の点

## 確かめたこと

- 検査：`python3 tools/check_pages.py --page geometric-series-mod`（エラー 0・警告 0）、`python3 tools/check_snippets.py snippets/geometric-series-mod`（3 片・コンパイル 3 回・期待と違う 0）。コンパイラは g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0
- サニタイザ：3 本を `g++-15 -std=gnu++23 -O1 -Wall -Wextra -fsanitize=address,undefined` でコンパイルし、最大の値（formula：`3 10^18`、halving：`999999999 10^12 10^9`、repeat：`10^18` と `999999999999999999`）で動かした。警告・実行時エラーなし。halving の再帰の深さは高々 $2\log_2 n + 2 \approx 82$ 段
- cases の期待出力を Python で別に計算した（作業用の場所の chk.py）：formula の 6 件（`10 5` → 11111、`998244354 7` → 7、`1 10^18` → 716070898、`3 10^18` → 432928662 など）、halving の 3 件の大きい値（法 $m(r-1)$ で累乗して割る別の方法と一致）、repeat の 4 件（`12` は `int("12"*12) % p` = 214985338、`10` は `int("10"*10) % p` = 154579416 と、文字列を実際に並べた値とも一致）。すべて一致
- 数の主張：998244353 で 10 の位数が $p - 1$（$p - 1$ の各素因数 $q$ で $10^{(p-1)/q} \not\equiv 1$）。$10^9+7$ でも $d \le 18$ で $10^d \not\equiv 1$。$100 \equiv 1 \pmod{11}$、$1000 \equiv 1 \pmod{37}$。確認問題の $3^{-1} \equiv 7 \pmod{10}$。行列 $\begin{pmatrix} r & 1 \\ 0 & 1\end{pmatrix}^n$ の右上が $S(n)$ になることは帰納法のとおり。呼び出しの回数が $2\log_2 n + 2$ 以下であることは $n < 2^{16}$ のすべてで確かめた（等号は $n = 2^k - 1$ の形）
- ACL：document_ja/modint.md の割り算の制約は `gcd(b.val(), mod) == 1`、inv も同じ。v1.6 のソース（modint.hpp 105〜113 行）で prime の static_modint は `assert(_v)` のあと `pow(umod() - 2)`、素数でない法は `inv_gcd` と `assert(eg.first == 1)`。本文の「制約の違反とし、内部の assert で止まる」と合う（NDEBUG なら 0 を返す。指摘 6）
- 問題：`python3 tools/ap.py show` で abc357_d（D. 88888888、diff 970）・abc293_e（E. Geometric Progression、diff 1453）・abc129_f（diff 2621）・math_and_algorithm_as（053. Sum of 4^N、diff なし）の題名・diff が本文と一致。台帳 data/problems.yaml の pages・role（example 1・practice 2・challenge 1）・summary と一致。要約に手法名はない
- 参考の URL：5 つとも HTTP 200 で、題名が本文の記載どおり（drken の 2 記事、Kazun の記事、E869120 の prob4-6-3.cpp、ACL の document_ja/modint.md）。atcoder.jp・codeforces.com は開いていない
- 執筆者の未解決の点：
    - abc293_e の M = 1：Kazun 氏の記事の制約（数式の画像の alt）が `1 \leq A,M \leq 10^9`、`1 \leq X \leq 10^{12}` で、M = 1 はありうる。halving の `1 % m` もこれに合う。方針の記述はそのままでよい
    - 図 halving.svg：Windows の Chrome（headless=new）で等倍（640×300）と、幅 358px（2 倍密度、暗い背景の上）で画像にして目で確かめた。和文も上付きの数字も出て、はみ出し・重なりはない。背景は白、`viewBox` あり、文字はテキスト。前半は実線・青、後半は破線・橙で、色に加えて線の種類でも分けている。内容（8 項を 4 項ずつ、後半 $= r^4 \cdot S(4)$、最下行の式）は本文の式と一致し、代替テキストだけでも要点が分かる。幅 358px では文字が約 10px 相当になる（指摘 7）
    - ACL の assert：上のとおり。表現は指摘 6
- 参照先の節：matrix-power#write-as-matrix（「定数項を状態に入れる」）、doubling#aggregates はどちらも見出しがある。matrix-power は青、doubling・exponent-mod は水で、本文の水・青の節の前置き（追加の前提のリンク）と合う

## 指摘

### 1｜直すべき｜fact（F2・F3）・clarity（U8）｜#halving の確認問題「法を m(r − 1) にする別の方法」の答え

- **問題**：答えの「$r^n \equiv 1 \pmod{r - 1}$ なので、求めた余りから 1 を引いても負にならない」は $r = 2$ で成り立たない。$r - 1 = 1$ では法が $m$ そのもので、$r^n \bmod m = 0$ になりうる。問いの前提は $r \ge 2$ なので $r = 2$ を含む
- **根拠**：$r = 2$、$m = 4$、$n = 3$ で、$2^3 \bmod 4 = 0$、$(0 - 1)/1 = -1$ だが正しい値は $S(3) = 7 \equiv 3 \pmod 4$。$r \ge 3$ では、余り $x$ は $x \equiv 1 \pmod{r-1}$ かつ $r - 1 \ge 2$ なので $x \ge 1$ で、負にならない（$3 \le r \le 11$、$1 \le m < 30$、$0 \le n < 30$ をすべて調べて反例なし）
- **直し方**：問いの前提を「$r \ge 3$ とする」にし、答えの最後に「$r = 2$ なら法は $m$ のままで余りが 0 になりうるので、$(x - 1 + m) \bmod m$ とする（$r - 1 = 1$ で割る必要もない）」を足す。または答えの言い方を「$r \ge 3$ なら $r - 1 \ge 2$ で、余りは $r - 1$ で割って 1 余る数なので 1 以上。$r = 2$ だけは余りが 0 になりうるので法を足してから 1 を引く」にする

### 2｜直すべき｜fact（F2）｜#next-steps の「位数と指数の mod」の項

- **問題**：「1 を何個並べると $K$ の倍数になるか …… は、$10^n \equiv 1$ となる $n$ を探す問題に言い換わる」は法が書かれておらず、読者は「mod $K$ で」と読む。repunit は $(10^n - 1)/9$ なので、$K \mid S(n)$ と同値なのは $10^n \equiv 1 \pmod{9K}$ で、$K$ が 3 の倍数のとき mod $K$ とは食い違う
- **根拠**：$K = 3$：$10^1 \equiv 1 \pmod 3$ だが 1 は 3 の倍数でない。最小は 111（$n = 3$）で、$10^3 \equiv 1 \pmod{27}$ と一致。$K$ が 3 と互いに素なら $9$ が $K$ と互いに素なので mod $K$ でよい
- **直し方**：「…… $(10^n - 1)/9$ が $K$ の倍数、つまり $10^n \equiv 1 \pmod{9K}$ となる最小の $n$ を探す問題に言い換わる（$K$ が 3 の倍数でなければ mod $K$ でよい）」などにする

### 3｜直すとよい｜clarity（U3）・fact（F7）｜#repeated-digits の $M$、要点の「いつ使うか」

- **問題**：#repeated-digits では $M$ が「並べる回数」だが、要点（signs 由来）では「同じ数字列を M 回並べて」の次の行で「法 M が入力で与えられ」「法 M ≤ $10^9$」と、同じ $M$ を法に使っている。練習の ABC293 E の方針でも $M$ は法。本文の記法の約束では法は $m$ なので、大文字・小文字だけで区別していて紛らわしい
- **根拠**：要点の「いつ使うか」1〜3 行目、#repeated-digits の式 $\underbrace{TT\cdots T}_{M \text{ 回}}$ と「並べる回数 $M$ が $10^{18}$ でも」、#practice の方針「法 $M$」
- **直し方**：本文の #repeated-digits では並べる回数を $K$ などにする（$O(\log K)$ も合わせる）。要点・signs の文言は front matter なので、「同じ数字列を K 回並べて」への変更を提案として報告に書く

### 4｜直すとよい｜code（C3）｜snippets/geometric-series-mod/halving.cpp の 11・14 行

- **問題**：構造化束縛の `auto [s, p]` の `p` が $r^n$ を表しているが、本文では $p$ は素数の法の記号（「法は $m$、素数なら $p$ と書く」）。取り込んだコードを読む人が `p` を法と取り違えやすい
- **根拠**：本文の記法の行、formula.cpp・repeat.cpp・確認問題で $p$ は 998244353
- **直し方**：`auto [s, pw]` などにする（14 行のコメント「k = n/2：S(2k) = S(k)·(1 + r^k)」と 15 行の `(1 + p)`・`p * p` も合わせる）

### 5｜直すとよい｜clarity（U3）｜#halving の「計算量」の箇条

- **問題**：「奇数の手順の次は必ず偶数の手順になるので、2 回の呼び出しで $n$ は半分以下になる」と「呼び出しは高々 $2 \log_2 n + 2$ 回程度」の「高々 …… 程度」が重なっていて、上界なのか目安なのかがぼやける
- **根拠**：$n < 2^{16}$ で、$n = 0$ の呼び出しを含めた回数は常に $2\log_2 n + 2$ 以下（等号は $n = 2^k - 1$）。上界として正しい
- **直し方**：「程度」を外して「高々 $2 \log_2 n + 2$ 回で」とする

### 6｜直すとよい｜fact（F4）｜#pitfalls の「$r \equiv 1$ の場合分けを忘れる」の括弧

- **問題**：「ACL の modint の割り算は、この場合を制約の違反とし、内部の assert で止まる」は、assert が有効なときの話。`NDEBUG` を定義すると素数の法の inv は `pow(mod - 2)` に進んで 0 を返し、自分で書いた $a^{p-2}$ と同じく黙って 0 になる
- **根拠**：v1.6 の modint.hpp 105〜108 行（`assert(_v); return pow(umod() - 2);`）。document_ja/modint.md の制約 `gcd(b.val(), mod) == 1`
- **直し方**：「ACL の modint の割り算では、この場合は制約の違反で、assert が有効なら止まる（`NDEBUG` を付けると 0 になる）」とする。執筆者の未解決の点の答え

### 7｜直すとよい｜figure（G3）｜docs/img/geometric-series-mod/halving.svg

- **問題**：横 640 の図をスマホの幅（本文の幅 358px 前後）に縮めると、font-size 17〜18 の文字が約 10px 相当になる。読めるが小さく、上付きの指数（r⁴ の 4 など）はさらに小さい
- **根拠**：Chrome（headless=new）で幅 358px・2 倍密度にして画像で確かめた
- **直し方**：必須ではない。直すなら、3 段目の「後半を r⁴ でくくると」を 1 行目の上か図の外（本文）に移し、viewBox の横幅を 560 前後に詰めて文字の縮みを減らす

## 総合の判定

小さな直しで可。直すべきは 2 件（指摘 1：確認問題の $r = 2$ の反例、指摘 2：repunit の言い換えの法の書き落とし）で、どちらも答え・1 文の手直しで済む。公式・場合分け・半分に割る漸化式・行列・例題の式と、コード片 3 本（境界・最大値・サニタイザ）・図・問題・出典に誤りは見つからなかった。
