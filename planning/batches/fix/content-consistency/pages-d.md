# content-consistency の第 2 段：math のページ（担当 pages-d）

- 担当の Issue：#68（平文のまま出る数式と法の文字）・#69（節の並び）・#77（1 次関数の表記）
- 作業ツリー：kyopro-atlas-wt/content-consistency（ブランチ fix/content-consistency）。2026-10-29
- 直したのは docs/math/ の手で書いたページ 30 個だけ。生成ページ docs/math/index.md と台帳・共有ファイルは触っていない
- 本文を直した 30 ページは `updated: 2026-10-29`（stage は変えていない）

## 検査の件数（直す前 → 後）

| 検査 | 前 | 後 |
| --- | --- | --- |
| `check_pages.py --field math` エラー：数式にならずに残る $ | 2（euler-phi:63・65） | 0 |
| 警告：平文の欄の TeX の記号 | 29 | 0 |
| 警告：節の並び | 16 | 0 |
| 警告：要点・題の素の数式 | 12 | 0 |
| 警告：方針の折りたたみの題 | 11 | 0 |
| 警告：法を表す mod の文字 | 3 | 0 |
| 合計 | エラー 2・警告 71 | エラー 0・警告 0 |
| `npx textlint docs/math/*.md`（index.md を除く） | エラー 11（prh 11）・警告 634 | エラー 0・警告 633 |
| `fix_problems.py --check` | 0 | 0 |
| `render_pages.py <作業用>/site --field math`（作業用フォルダへビルド） | — | エラー 0・警告 1（下の「残った点」） |

textlint の警告はファイルごとに前後を突き合わせ、増えたファイルはない（euler-phi が 16 → 15）。index.md（生成ページ）のエラー 8 件（ja-space-between-half-and-full-width）と警告 7 件は数えていない。メインが gen_site で作り直したあとに見る。

## #69 節の並び（16 ページ）

h2 を節ごと（見出しから次の h2 の直前まで）動かした。anchor・見出しの文字は変えていない。作業用フォルダの小さな道具で、フェンスの中の `##` を見出しと取らないようにして並べ替えた。

| ページ | 動かした節 |
| --- | --- |
| divisor-count-bound | `divisor-dp`・`enumerate-hcn`（上の帯の中身の節）を落とし穴の前へ |
| ext-gcd | `acl` を落とし穴の前へ（中身の節。メインの判断） |
| floor-quotient-enum | `vs-others` を落とし穴の前へ（中身の節。メインの判断） |
| floor-sum | `acl` を `applications` の前（front matter の sections の順）へ。落とし穴の前になる |
| mod-pow | `acl` を落とし穴の前へ。`building-block`（§17-4 の next-steps と同じ役）は落とし穴の直後のまま |
| modint | `division`・`self-made`・`acl-internals` を落とし穴の前へ。`connections`（next-steps と同じ役）は落とし穴の直後に残した。front matter の sections も本文の順（…acl-internals → connections）に並べ替えた |
| divisor-enum・mod-inverse・sieve-eratosthenes・spf-sieve | 使い分けを練習問題（spf-sieve は力試し）の後へ |
| exponent-mod・gcd-properties・segmented-sieve | 使い分けを確認問題の後へ |
| geometric-series-mod | 確認問題・使い分けを力試しの後へ |
| multiplicative-order | 使い分けを確認問題の後へ |
| multiplicative-function | 使い分けを確認問題の後へ |

参照の食い違い：16 ページで「上の」「下の」「次の節」「前の節」などを grep で全部見た。動かした節をまたぐ参照はなかった（「次の節」はどれも動かしていない中身の節どうし。modint の落とし穴から割り算の条件へはリンク `#division` で、節が上に来ても意味は変わらない）。

方針の折りたたみの題（11 件）：convolution-ntt（325 練習・339 力試し）・floor-sum（274 力試し）・gaussian-elimination（234・249）・gcd-properties（243「練習問題の方針」→「練習の方針」）・linear-recurrence-fast（218）・matrix-power（358・375）・xor-basis（249・263）。どれも節が 1 問ずつではないので「練習の方針」「力試しの方針」の形にした。

## #68 平文の欄・要点と題・法の文字・$

### front matter（平文の欄 19 件）

範囲つきの和を言葉にし、2 字以上の上付き・下付きをかっこにした。

| ページ | 欄 | 直した後 |
| --- | --- | --- |
| convolution-ntt | summary | i + j = k となる a_i b_j の和 c_k（多項式の積）を ACL の convolution で… |
| convolution-ntt | signs[4] | i + j = k となる a_i b_j の和 c_k の形 |
| floor-quotient-enum | summary・signs[0]・signs[3] | i = 1..N の f(⌊N/i⌋) の和を、…／i = 1..N の ⌊N/i⌋ の和を求める／i = 1..N の f(⌊N/i⌋) の和の形 |
| floor-sum | summary | i = 0..n−1 の ⌊(ai + b)/m⌋ の和を、…（「一次式」も「1 次式」に） |
| geometric-series-mod | signs[3] | i = 0..N−1 の A^i の和の形 |
| hadamard-transform | summary | i XOR j = k となる a_i b_j の和 c_k を、… |
| harmonic-sum | signs[3] | d = 1..M、k = 1..⌊M/d⌋ の f(d, kd) の和の形の二重ループ |
| lagrange-interpolation | signs[1] | i = 1..N の i^k の和を N ≤ 10^18 で求める |
| linear-recurrence-fast | signs[3] | a_n = c_1 a_(n−1) + … + c_K a_(n−K) の形の漸化式 |
| miller-rabin | summary・complexity | O(N^{1/4}) → O(N^(1/4))（3 か所） |
| multiplicative-function | summary・complexity・signs[0] | 「n ≤ N の f(n) の和」、N^(3/4)・N^(2/3)・Θ(N^(1−ε)) |
| online-convolution | signs[1] | dp[i] が j < i の dp[j]·g[i−j] の和のように、自分より前の値との畳み込みで決まる |
| sigma-manipulation | signs[1]・signs[2] | i = 1..N、j = i..N の f(i, j) の和のように…／K = 1..N の K × (K の約数の個数) の和のように… |

要点の囲みは元から KaTeX なので、signs を変えても要点は変えていない（linear-recurrence-fast を除く。下）。

### 本文の問題の行（10 行）

tools.md の D の表の台帳の文と同じにした：convolution-ntt:283（practice2_f）・floor-quotient-enum:173（abc230_e）・同 209（abc172_d。alternatives の文）・floor-sum:225（practice2_c）・lagrange-interpolation:157（abc137_f）・linear-recurrence-fast:184（tdpc_fibonacci）・同 214（abc300_h）・matrix-power:354（abc009_4）・multiplicative-order:271（abc270_g）・sigma-manipulation:238（abc230_e）。`fix_problems.py --check` は 0 のまま。台帳との違いはほかに見つからなかった。

### 要点・題の素の数式（12 件）

KaTeX にした：convolution-ntt の確認問題の題 2 つ（$A_i - B_j = d$・$2 \times 10^5$）、exponent-mod「確認問題：$3^{10^{18}} \bmod 7$」、fft-ntt（$469762049 = 7 \times 2^{26} + 1$・$L$・$\omega$）、floor-quotient-enum（$N = 10^{12}$）、floor-sum の証明の題（$\lfloor (y_{\max} - jm)/a \rfloor$。本文の書き方に合わせた）と確認問題の題（$\sum_{i=1}^{N} (Ai) \bmod M$ を $f$ で表すと？）、gcd-properties（$O(\log N + \log A)$）、hadamard-transform（$2^n$）、harmonic-sum（$\ln(M + 1) \le H_M \le 1 + \ln M$）、linear-recurrence-fast の要点（$K$・$N \le 10^{18}$・$a_n = \sum_{k=1}^{K} c_k a_{n-k}$。検査に出ていない同じ囲みの「有理式 $P(x)/Q(x)$ の $N$ 次の係数」もそろえた）。

### 法の文字（3 件）

- mod-arithmetic:94（確認問題の答え）：`$a - b > -\mathrm{MOD}$` → `$a - b > -998244353$`（問題文が法を 998244353 と書いているので、その数にした。コードの `MOD` はそのまま）
- mod-inverse:202（ACL の囲み）：「要件は `gcd(b.val(), mod) == 1`、計算量は $O(\log \mathrm{mod})$」→「要件は $\gcd(b, m) = 1$、計算量は $O(\log m)$」（同じ囲みの前の文で `inv_mod(x, m)` の $m$ を法にしている）
- geometric-series-mod（参考の行）：「（$\gcd(b, \text{mod}) = 1$）」→「（法を $m$ として $\gcd(b, m) = 1$）」

### 数式にならずに残る $（エラー 2 件）

euler-phi#formula の折りたたみ「包除原理から公式を導く」：段落に続いていた `$$` の前後を空行にし、「包除原理から」の文を「包除原理から次の式になる。」で閉じ、式の後の「となる。」を削って次の段落を「右の等号は、…」から始めた。

## #77 表記

- prh の指摘 11 件を手で直した：floor-sum「一次式」→「1 次式」（37・50・186・204 の見出し・210）、gaussian-elimination（42・123・199）、matrix-power:232「一次関数」→「1 次関数」、lagrange-interpolation:119「連立 1 次方程式」→「連立一次方程式」・147「ヴァンデルモンドの行列式」→「Vandermonde の行列式」
- 単独の「一次」：floor-sum:58・303 と floor-quotient-enum の表と箇条書き（2 か所）の「$i$ が分子に一次」→「$i$ が分子に 1 次」
- front matter（textlint の外）：floor-sum の summary と sections[6] の title（見出しと同じ「応用の型：bit ごとの popcount・1 次式の mod の積」）、gaussian-elimination の signs[4]、online-convolution の signs[0]
- aliases と本文の別名の行（floor-sum の「一次式の mod の和」など）は方針どおり変えていない。一次合同式・一次不定方程式・一次漸化式・連立一次方程式・一次独立は用語なので漢数字のまま

## 流した検査

| 検査 | 結果 |
| --- | --- |
| `python3 tools/check_pages.py --field math -v` | エラー 0・警告 0（前はエラー 2・警告 71） |
| `python3 tools/check_pages.py`（全体） | math は 0。ほかの分野のエラー 13 件はほかの担当の範囲 |
| `python3 tools/fix_problems.py --check` | 直すべき行 0 |
| `npx textlint docs/math/*.md`（index.md を除く 41 ファイル） | エラー 0・警告 633（どのファイルも増えていない） |
| `.venv/bin/mkdocs build -d <作業用>/site` → `python3 tools/render_pages.py <作業用>/site --field math` | エラー 0（KaTeX のエラー・描かれない数式・地の文に残った記法・横ずれがどれも 0）・警告 1 |
| `python3 tools/gen_site.py --check` | 生成物が古い（front matter の summary・signs・sections を変えたので。メインが作り直す） |
| front matter の YAML | 41 ページとも読める |

## 残った点・提案

- **提案（メイン）**：gen_site.py で生成物を作り直す（math の summary・signs・sections の順が変わったので、docs/math/index.md・一覧・索引・llms.txt・graph.json が変わる）。作り直したあとに `npx textlint docs/math/index.md` を見る（今のエラー 8 件は front matter の文から来ているものがあるかもしれない）
- **残った警告**：render_pages の「画面の幅を超える表」1 件（math/miller-rabin#deterministic-bases、幅 452px）は前からあるもので、今回の範囲（#68・#69・#77）の外なので直していない
- 台帳と本文の違いはほかに見つからなかった（台帳への提案なし）
