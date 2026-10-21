# sigma-manipulation の検証（工程8b・b1）

- 対象：docs/math/sigma-manipulation.md、snippets/sigma-manipulation/（divisor-sum・pair-product の 2 組）、docs/img/sigma-manipulation/swap-grid.svg
- 観点：planning/checklists/ の fact.md・code.md・clarity.md・figure.md、手引き planning/style-guide.md、執筆者の報告 planning/batches/b1/sigma-manipulation.md の未解決の点

## 確かめたこと

- 検査：`python3 tools/check_pages.py --page sigma-manipulation`（エラー 0・警告 0）、`python3 tools/check_snippets.py snippets/sigma-manipulation`（2 片・コンパイル 2 回・期待と違う 0）、`npx textlint docs/math/sigma-manipulation.md`（0 errors・14 warnings。数式を含む文の長さ・読点の数・助詞「で」の重複・半開区間 $[kd, (k+1)d)$ の括弧の誤検出で、§13.8 の範囲）。コンパイラは g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0
- front matter：骨格（75cd131）との差は complexity・stage と、sections への「上位の手法へのつながり（next-steps）」の追加だけ（§2.1 の範囲）。要点の計算量と complexity は一致。別名の行に aliases の 6 語がすべてある
- 問題：`python3 tools/ap.py show` で abc172_d（963）・abc230_e（969）・abc471_e（990）・abc356_e（1506）の題名・diff を確かめ、本文の label・diff と一致。役割は catalog のとおり（例題 1・練習 3）で、練習は易しい順
- 例題 ABC172 D：wafuwafualgorithm（scrapbox.io。`tools/check_noai.py` で指定なしを再確認）は「約数 $i$ ごとに $N$ 以下の倍数の和を等差数列で足す、$O(N)$」、はまやんの記事は $N = 10^7$ と篩の $O(N \log N)$ の別解。本文の方針・解法の詳細と一致。$N = 10^7$ の答えは 838,627,288,460,105（約 $8.4 \times 10^{14}$）で「$10^{15}$ 程度」「long long に収まる」は正しい
- 練習の要約と方針：hyouri の記事（K 個を選ぶ部分集合の和の 2 乗の総和、mod 998244353、$a_i^2 \binom{n-1}{k-1} + a_i(\Sigma A - a_i)\binom{n-2}{k-2}$）、bit_otter の記事（$\sum_{i \ne j} A_i A_j = S_1^2 - S_2$）、Kazun の記事（ABC230 E、$N \le 10^{12}$、商が $O(\sqrt{N})$ 種類）、drken の記事（ABC356 E、$A_i \le 10^6$、値ごとの個数・小さい側を固定して倍数で区切る・同じ値は $\binom{c}{2}$、$O(M \log M)$）で確かめた。abc471_e の制約はどの記事にもなく（未解決の点のとおり）、本文は制約に触れていないので問題ない
- 参考の 6 件：題名・著者・内容が書かれたとおり。atcoder.jp・codeforces.com の URL はない
- 式の確かめ（作業用の場所の Python。乱数の列 500 組、$N \le 8$）：$\sum_i\sum_j (a_i - a_j)^2 = 2N\sum a_i^2 - 2(\sum a_i)^2$、$i + j = k$（$0 \le i, j \le N-1$）の組の数 $N - \lvert k - (N-1) \rvert$、ソート後の $\sum_{i<j}\lvert a_i - a_j\rvert = \sum_j (2j - N - 1)a_j$、ABC471 E の式 $\binom{N-1}{K-1}\sum a_i^2 + \binom{N-2}{K-2}((\sum a_i)^2 - \sum a_i^2)$（$K = 1$ で後ろを 0）、和の公式の表（$N \le 59$）、$\lfloor N/i \rfloor$ の値の種類が $2\sqrt{N}$ 以下（$N < 3000$）はすべて一致。$N(N+1)(2N+1)$ は $N = 2 \times 10^6$ で 1.6000012×10^19（long long の上限 9.22×10^18 を超えるのは $N \approx 1.66 \times 10^6$ から）
- 確認問題 3 つ（範囲の書き換え・約数の個数の和・$a = (1, 2, 3)$ で 11）：答えは正しい
- 空の和の節：二項係数の前計算のページ（#table-size、draft）は $k < 0$・$k > n$・$n < 0$ を 0 にすると書いており、本文の「$K = 1$ や $N = 1$ を特別扱いしなくてよい」と合う
- リンク先：notation・glossary（stub）は節のリンクなし／用語集の anchor（`identity-element`）あり。contribution・harmonic-sum・floor-quotient-enum・prefix-sum・binomial-precompute（`#table-size`）・cpp-integer-overflow（`#int128`）・rational-mod・linearity-of-expectation は draft で anchor あり。divisor-inclusion-exclusion は stub だがページへのリンクだけなので §7 に合う
- コード片：divisor-sum.cpp の core は解法の詳細の式（$M(M+1)/2$ を先に計算し $d$ を掛ける）と 1 行ずつ対応し、$N = 0$〜$300$ を素朴な方法と `assert` で照合している。pair-product.cpp は 1 要素（答え 0）・$10^9$ 級・法以上の値を含み、$N \le 2000$ で二重ループと照合。`-fsanitize=address,undefined` で $N = 10^7$・$N = 0$・負の値（$-1, -2, 5$ → 998244340 ＝ $-13 \bmod p$）・空の列を動かして問題なし。§9 の書き方（bits・using namespace・mint の別名は例外として許可・`'\n'`）に合う
- 図：Windows の Chrome（headless=new）で swap-grid.svg を等倍（640×320）と、幅 390px の画面に幅 358px で（2 倍密度、暗い背景の上に）画像にして目で確かめた。背景は白で塗られ、`viewBox` があり、文字はテキストのまま。行ごと（赤の実線）と列ごと（青の破線）は色に加えて線の種類で分けている。塗ったマス 10 個、囲みの範囲（$j = i$〜$4$、$i = 1$〜$j$）は本文の式と一致し、はみ出し・重なりはない。catalog の visual（static・priority 2）どおり

## 指摘

### 1｜直すべき｜fact（F2）｜#linearity の第 3 段落「$(a_i - a_j)^2$ や $(a_i + b_j) \bmod m$ のように展開できる式も」

- **問題**：$(a_i + b_j) \bmod m$ は「$i$ だけの項」「$j$ だけの項」「積の項」に分けられない。$\sum_i \sum_j ((a_i + b_j) \bmod m)$ は、$a_i + b_j \ge m$ になる組の数を（ソートと二分探索などで）数えないと求まらない。同じ節の最後の文「$\bmod$ … なども Σ の外に出せない」とも食い違う
- **根拠**：$a = (1, 0)$、$b = (1, 0)$、$m = 2$ で値は $(1,1) \to 0$、$(1,2) \to 1$、$(2,1) \to 1$、$(2,2) \to 0$。$f(i) + g(j)$ の形なら対角の和と反対角の和が等しくなるはずだが、0 と 2 で異なる。したがって $i$ だけ・$j$ だけの項の和には分けられない
- **直し方**：例から $(a_i + b_j) \bmod m$ を外し、「$(a_i - a_j)^2$ や $(a_i + b_j)^2$ のように展開できる式も」などにする。$\bmod$ の例は最後の文（外に出せないもの）の側で、「$\sum_i\sum_j ((a_i + b_j) \bmod m)$ は $m$ 以上になる組を数える必要がある」と短く添えるとよい

### 2｜直すべき｜fact（F2）｜#group-by-value の第 3 段落「$\sum_{i<j} h(A_i, A_j)$ は、値の組 $(u, v)$ ごとに $c_u c_v\, h(u, v)$ を足す形になる」

- **問題**：成り立つ条件が書かれていない。(1) $(u, v)$ を $u < v$ に限ることが、この文では書かれていない（次の文の「$u < v$ の組とは別に」で初めて出る）。順序付きのすべての $(u, v)$ と読むと、同じ組を 2 回数え、同じ値どうしは $c_v^2$ になる。(2) $i < j$ は $A_i < A_j$ を意味しないので、$h$ が対称（$h(u, v) = h(v, u)$）でないと成り立たない
- **根拠**：$A = (3, 1, 2, 1)$、$h(u, v) = u - v$ で、直接の $\sum_{i<j} h(A_i, A_j) = 5$、値の組 $u < v$ でまとめた $\sum c_u c_v h(u, v) + \sum \binom{c_v}{2} h(v, v) = -7$（作業用の場所の Python）。ABC356 E の $h$（$\lfloor \max / \min \rfloor$）は対称なので、本文の使い方では正しい
- **直し方**：「$h$ が対称（$h(u, v) = h(v, u)$。$\max$・$\min$・積など）なら、$\sum_{i<j} h(A_i, A_j) = \sum_{u<v} c_u c_v\, h(u, v) + \sum_v \binom{c_v}{2} h(v, v)$ になる」と式で書き、次の文の同じ値どうしの説明をこの式に吸収する

### 3｜直すとよい｜fact（F2）・clarity（U4）｜#pitfalls「公式の途中であふれる」

- **問題**：「割り切れる因子を先に割る（$N$ と $N + 1$ のどちらかは偶数）」は 2 の分しか言っていない。$/6$ には 3 も要り、2 だけ先に割って $\frac{N(N+1)}{2}(2N+1)$ としても $N = 2 \times 10^6$ で 8.0×10^18 と上限ぎりぎりで、$N \approx 2.1 \times 10^6$ を超えるとまたあふれる。読者が「2 で先に割れば足りる」と受け取りやすい
- **根拠**：計算（上の「確かめたこと」）。$N(N+1)(2N+1)$ は $N$・$N+1$・$2N+1$ のどれかが 3 の倍数で、6 で割り切れる
- **直し方**：「2 と 3 をそれぞれ割り切る因子から先に割る（$N$・$N+1$ の一方は偶数、$N$・$N+1$・$2N+1$ のどれかは 3 の倍数）か、`__int128` で計算してから割る」とする。ここで例の値を「先に割っても $N$ が大きければ $N^3/3$ 程度になる」と添えるとよい

### 4｜直すとよい｜fact（F7）・clarity（U3）｜#linearity の最後の文「$\max$・$\min$・$\lfloor \cdot \rfloor$・$\bmod$ の比較なども Σ の外に出せない」

- **問題**：「$\bmod$ の比較」が何を指すか分からない（$\bmod$ を取った後の値の大小比較か）。「Σ の外に出せない」も、何をどう出すのかが具体的でない
- **直し方**：「$\sum_i \max(a_i, b_i) \ne \max(\sum a_i, \sum b_i)$、$\sum_i \lfloor a_i / k \rfloor \ne \lfloor \sum a_i / k \rfloor$ のように、$\max$・$\min$・$\lfloor \cdot \rfloor$・$\bmod$ は和と入れ替えられない」のように、1 つ式の反例を見せる

### 5｜直すとよい｜clarity（U4）｜#practice の折りたたみ「練習の方針」の ABC356 E

- **問題**：「大きい側の値が $[kd, (k+1)d)$ にある組は商が $k$」で $k = 1$ の区間 $[d, 2d)$ は値 $d$ 自身を含む。同じ値どうしを「別に $\binom{c_v}{2}$ 個を足す」なら、$k = 1$ では $d$ を除いた $(d, 2d)$ を数えないと二重に数える。どちらで数えるかが方針から読めない
- **根拠**：drken の記事（evidence）は同じ値を別に足し、区間の数え方で $d$ 自身を除いている
- **直し方**：「大きい側の値が $d$ より大きく $[kd, (k+1)d)$ にある組は商が $k$ で、$c_d \times$（その区間の個数）になる」と書き、同じ値どうしの文と対にする

### 6｜直すとよい｜clarity（U3）｜#reindex の「和を新しい添字にする」（$0 \le i, j \le N-1$）

- **問題**：冒頭で「添字は 1 から数え（1-indexed）」と約束しているのに、この例だけ 0 から数える。同じ節の最後で「0-indexed … を途中で混ぜると、端が 1 つずれる」と注意しているので、読者が混乱しやすい
- **直し方**：1-indexed（$1 \le i, j \le N$、$k = 2$〜$2N$、組の数 $N - \lvert k - (N+1) \rvert$）に直すか、「ここでは $k$ の範囲を $0$ から始めるため、$i, j$ を $0$ から数える」と一言断る

### 7｜直すとよい｜clarity（U3）・code（C3）｜#formulas のコード片の前後

- **問題**：取り込んだ core に `mint`（ACL の `modint998244353`）と `mint(2).inv()` が説明なしに出る。本文は「2 の逆元を掛ける」とだけ書く
- **直し方**：コード片の直前に「`mint` は ACL の `modint998244353`（[modint](../math/modint.md)）で、`mint(2).inv()` が 2 の逆元」と 1 文添える

### 8｜直すとよい｜style（§2.5）｜#group-by-value「（練習の ABC356 E がこの型）」

- **問題**：本文で問題に触れるときはページか見出しへリンクする（§2.5）。binomial-precompute は「[練習の ABC132 D](#practice)」の形にしている
- **直し方**：「（[練習の ABC356 E](#practice) がこの型）」にする

### 9｜直すとよい｜clarity（U2）｜#group-by-value の最後の段落

- **問題**：「$\lfloor N/i \rfloor$ は高々 $2\sqrt{N}$ 種類の値しか取らず」に理由がない（リンク先に任せている）。基礎のページとして 1 文の直感があると「なぜ」が埋まる
- **直し方**：「$i \le \sqrt{N}$ の $i$ は $\sqrt{N}$ 個しかなく、$i > \sqrt{N}$ なら値は $\sqrt{N}$ 未満なので」と括弧で添える

### 10｜直すとよい｜figure（G3）｜swap-grid.svg

- **問題**：幅 358px（スマホ）に縮めると、マスの中の $(i, j)$ のラベル（font-size 12）が約 6.7px になり読みにくい。行と列の見出し（$i = 1$ など）と囲みは読めるので、要点は伝わる
- **直し方**：任意。マスのラベルを 14 程度に上げるか、2 つの表の間の空き（約 130px）を詰めて全体の幅を 560 程度にする

## 提案（メインへ）

- 台帳：abc172_d の `checked` に 2026-10-21 を入れる（問いと $N \le 10^7$ を、はまやんの記事で確かめた）。evidence に執筆者の提案の 2 件（scrapbox の wafuwafualgorithm・blog.hamayanhamayan.com）を足すのに賛成。scrapbox.io は付録 B に足す（check_noai で指定なしを確認）
- 台帳：abc471_e の summary は執筆者の案のとおりでよい（hyouri・bit_otter の記事と一致）。abc356_e の summary の「全ての」→「すべての」と、front matter の signs 1 つ目の「全ての組」→「すべての組」にも賛成
- 練習の補充：abc177_c（diff 386）か abc186_d（diff 436）を練習に足す案に賛成。とくに abc186_d は #formulas の最後の式 $\sum_j (2j - N - 1)a_j$ をそのまま使い、本文の主張の練習になる

## 総合の判定

小さな直しで可（直すべき 2 件：指摘 1・2。どちらも 1〜2 文の差し替えで直る。ほかは直すとよい 8 件）
