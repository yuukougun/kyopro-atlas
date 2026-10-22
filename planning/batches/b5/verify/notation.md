# 検証：notation（記法と用語の約束）

- 対象：docs/start/notation.md（stage: draft、2026-10-22）、snippets/notation/conventions.{cpp,yaml}、docs/img/notation/half-open.svg・mod-clock.svg
- 観点：fact.md・code.md・clarity.md・figure.md
- 検証役：執筆者とは別のエージェント

## 確かめたこと（要約）

- `python3 tools/check_pages.py --page notation`：エラー 0・警告 0。textlint：エラー 0・警告 19（執筆者の報告どおり）
- front matter：`git diff` で、執筆者が変えたのは stage・updated だけ（ほかは要点・本文の追加）。要点と summary は一致し、別名の行は aliases をすべて含み、最初の `##` より前にある
- 本文の相対リンク：行き先のページはすべて draft か published（stub への節リンクはない）。anchor の有無は check_pages が通している
- コード片：`python3 tools/check_snippets.py notation` で期待と違う 0（g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0、`-std=gnu++23 -O2 -Wall -Wextra`）。cases 4 件（頂点 1・辺 0、パス、星、多重辺）の出力を手計算で確かめた。`u--, v--` が読み込み直後、`assert(total == 2LL * m)` が握手補題と一致。手引き §9 の形（bits・using namespace std・マクロなし・`'\n'`）に合う。取り込みの印 `core` は本文と一致
- 小さなプログラムで確かめた主張（scratchpad）：$ac \equiv bc \pmod m \Rightarrow a \equiv b \pmod{m/\gcd(c, m)}$（$m < 30$、$\lvert c \rvert \le 20$、$\lvert a \rvert, \lvert b \rvert \le 15$ で全数）、$\lceil a/b \rceil = \lfloor (a + b - 1)/b \rfloor$（$b \ge 1$、負の $a$ を含む）、$\log_2(2 \times 10^5) \approx 17.61$、$2^{30} \approx 1.07 \times 10^9$、$119 \times 2^{23} + 1 = 998244353$、$(10^9 + 6)^2$（指摘 1）
- 手で確かめた主張：$2 \cdot 1 \equiv 2 \cdot 4 \pmod 6$ と $1 \equiv 4 \pmod 3$、確認問題の 3 問の答え（$x = 2, 5$、$[l - 1, r)$、$(-7) \bmod 3 = 2$ と `-7 % 3` $= -1$）、$\mathrm{out}[v] - \mathrm{in}[v] = \mathrm{sz}[v]$、$d(u, v)$ の LCA の式、$T \subseteq S \iff (S \,\&\, T) = T$、横ベクトルでは左の区間の行列を左に置くと `op(a, b) = ab` になること、縦ベクトル $v' = Av$ で $a_{ij}$ が「$j$ から $i$ へ」の係数であること
- 行き先のページとの整合（grep）：matrix-power・segment-tree-monoids の向き、euler-tour#mo-on-tree の $\mathrm{ST}(v)$・$\mathrm{EN}(v)$（入りと出の位置）、string-automaton-dp の $\mathrm{fail}[v]$ と aho-corasick の $\mathrm{link}(v)$（前者の本文に「同じもの」とある）、expectation-of-square の $V[X]$、spf-sieve の $\Omega$、divisor-count-bound の $\omega$、sieve-eratosthenes の $\pi(x)$、multiplicative-order の $\operatorname{ord}_m(a)$、binomial-coefficient の $\mathrm{C}[n][k]$、tree-traversal の「根の親は $-1$」、gcd-lcm の $\gcd(0, a) = a$（$a \ge 0$ の約束の下）、cpp-environment と手引き §9 の「GCC 15.2（`-std=gnu++23`）」と u64・u128 の例外。いずれも一致
- 手引き §6 との整合：計算量・区間・添字・文字・整数・ビット・木・文字列の記法はすべて §6 と一致し、§6 にない記法は執筆者の提案どおり足したもの
- 参考の URL 3 件：すべて 200 で開け、内容が書かれたとおり（cppreference：整数の割り算は 0 の向きに切り捨て、CWG 614 以後 `%` の符号が決まる。ja.wikipedia「整数の合同」：$ax = b$ が $\mathbb{Z}/n\mathbb{Z}$ で一意な解を持つ必要十分条件は $a$ と $n$ が互いに素。en.wikipedia「Iverson bracket」）。atcoder.jp・codeforces.com の URL はない
- 表の中の `` `S | T` ``：mkdocs の `.venv` の Python-Markdown（tables・arithmatex）で変換し、列が割れずに 3 列のままになることを確かめた
- 図：`python3 tools/render_svg.py notation` で 360・720 の幅を目で確かめた。文字の重なり・はみ出しはなく、背景は白、`viewBox` と `width`・`height` の比が同じで幅 400、`font-family="sans-serif"`。half-open は箱の中の位置 0〜7 と箱の下の境目 0〜8 を分けて描き、$l = 2$・$r = 5$ の矢印が境目を指し、個数 $5 - 2 = 3$・分割・空区間 $[6, 6)$ の文が本文と一致。mod-clock は 0〜4 の各位置の数の並び（$\dots, -3, 2, 7, 12$ など）がすべて正しく、位置 2 を濃くして本文の $-3 \equiv 2 \equiv 7$ と $(-3) \bmod 5 = 2$ に対応する。代替テキストと前後の文だけで要点が分かる。色だけに頼る区別はない

## 指摘

### 1．直すべき：$10^9 + 7$ の余りどうしの積は $10^{18}$ 未満ではない

- 観点：事実（F3）
- 場所：#numbers の 1 つ目の箇条（96 行）
- 問題：「$10^9 + 7$：…2 つの余りの積は $10^{18}$ 未満で、`long long` に収まる」とある。余りの最大は $10^9 + 6$ で、その 2 乗は $10^{18}$ を超える。`long long` に収まるという結論は正しいが、理由の数値が誤っている
- 根拠：$(10^9 + 6)^2 = 1000000012000000036 > 10^{18}$（Python で計算）。`long long` の上限は $2^{63} - 1 \approx 9.22 \times 10^{18}$。docs/math/mod-arithmetic.md の 92 行は $998244353$ について $(m - 1)^2 \approx 9.96 \times 10^{17}$ と正しく書いている
- 直し方：例「2 つの余りの積は最大で $(10^9 + 6)^2 \approx 1.0 \times 10^{18}$ で、`long long` の上限 $9.2 \times 10^{18}$ に収まる」

### 2．直すとよい：確認問題 2 が本文の文をそのまま問うている

- 観点：分かりやすさ（U8）
- 場所：#quiz の 2 問目（278〜282 行）
- 問題：#half-open の最後の段落（73 行）に「0-indexed の半開区間に直すと $[l - 1, r)$ になり、右端は変わらない」とそのまま書いてあり、本文を写せば答えられる。チェックリストの「本文の文をそのまま問う」に当たる
- 直し方：条件を変えて当てさせる問いにする。例「問題文の『$l$ 番目から $r$ 番目まで』の和を、$S_0 = 0$、$S_{i+1} = S_i + a_i$（0-indexed）の累積和で書くと？」（答え $S_r - S_{l-1}$、理由は $[l - 1, r)$ への変換）や「1-indexed の閉区間 $[l, r]$ を逆順にたどる for 文を 0-indexed で書くと？」など

### 3．直すとよい：確認問題 1 の問いの下の文が答えの半分を言ってしまう

- 観点：分かりやすさ（U8）
- 場所：#quiz の 1 問目（272〜273 行）
- 問題：問いのすぐ下（折りたたみの外）に「両辺を 2 で割って $x \equiv 2 \pmod{6}$ とすると、$x = 5$ を落とす」とあり、$x = 5$ も解であることを先に明かしている。読者が自分で誤りに気づく機会がなくなる
- 直し方：ヒントを「両辺を 2 で割ってよいか、#congruence-division の条件を確かめる」程度にし、$x = 5$ の話は答えの折りたたみに移す

### 4．直すとよい：接頭辞・接尾辞の「空文字列も含む」の書き方があいまい

- 観点：分かりやすさ（U3）
- 場所：#string の「接頭辞・接尾辞」の箇条（244 行）
- 問題：「$i = 0$ や $i = \lvert S \rvert$ では空文字列も含む」は、$i = \lvert S \rvert$ の接頭辞が空文字列だとも読める。実際は $i = 0$ の接頭辞と $i = \lvert S \rvert$ の接尾辞が空文字列で、$i = 0$ の接尾辞と $i = \lvert S \rvert$ の接頭辞は $S$ 自身である
- 直し方：例「$0 \le i \le \lvert S \rvert$ とし、$i = 0$ の接頭辞と $i = \lvert S \rvert$ の接尾辞は空文字列、$i = \lvert S \rvert$ の接頭辞と $i = 0$ の接尾辞は $S$ 自身である」

### 5．直すとよい：$\gcd(0, a) = a$ に $a \ge 0$ の条件がない

- 観点：事実（F2）
- 場所：#math の表、gcd の行（119 行）
- 問題：$a$ が負なら $\gcd(0, a) = \lvert a \rvert$ である。行き先の gcd-lcm は「$a, b$ を 0 以上の整数とし」と約束してから $\gcd(0, a) = a$ と書いており、ここだけ条件が落ちている（C++ の `std::gcd(0, -3)` も 3 を返す）
- 直し方：「$\gcd(0, a) = a$（$a \ge 0$）」とする

## 執筆者の未解決の点について

1. **値の上限の文字**：本文の「値の上限には決まった文字を当てず、ページの冒頭で定める（辺の出てこないページでは $M$ を使うこともある）」は、harmonic-sum・divisors-and-multiples の今の書き方と矛盾せず、誤りではない。$V$ などにそろえるかはメインの判断（spf-sieve はすでに値の上限を $V$ と書いている）
2. **行列の向き**：両ページの向きと本文の説明が正しいことを確かめた（縦ベクトルの $a_{ij}$ の意味、横ベクトルで `op(a, b) = ab`）。dynamic-dp の向きは未決のままでよい
3. **失敗リンクの記号**：string-automaton-dp の本文が「Aho-Corasick 法のページの $\mathrm{link}(v)$ と同じもの」と明記しており、記法のページの記述と一致する。誤りはない
4. **σ の重なり**：「ページの冒頭の定義に従う」で足りる
5. **GCC 15.2（`-std=gnu++23`）**：cpp-environment の front matter・本文と手引き §9 に一致する（atcoder.jp は開いていない）

## 総合の判定

小さな直しで可（直すべき 1 件：指摘 1 の数値の誤り。直すとよい 4 件）
