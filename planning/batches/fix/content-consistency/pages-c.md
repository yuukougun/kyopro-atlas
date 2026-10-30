# content-consistency の第 2 段：ds・comb のページ（担当 pages-c）

- 担当の Issue：#68（平文のまま出る数式と法の文字）・#69（節の並び）・#77（1 次関数の表記）
- 作業ツリー：kyopro-atlas-wt/content-consistency（ブランチ fix/content-consistency）。2026-10-29
- 直したのは docs/ds/・docs/comb/ の手で書いたページ 61 個だけ（生成ページ・gen の区間・台帳・手引き・prh.yml は触っていない）。直したページの front matter の `updated` はすべて 2026-10-29（stage は変えていない）

## 検査の件数（直す前 → 直した後）

| 検査 | ds | comb |
| --- | --- | --- |
| check_pages `--field` のエラー | 2 → 0（数式にならずに残る $） | 2 → 0（同じ） |
| check_pages の警告 | 60 → 0 | 36 → 0 |
| 　節の並び | 16 → 0 | 10 → 0 |
| 　方針の折りたたみの題 | 26 → 0 | 8 → 0 |
| 　要点・題の素の数式 | 13 → 0 | 1 → 0 |
| 　和文に接した数式 | 4 → 0 | 0 |
| 　平文の欄の TeX の記号 | 1 → 0 | 9 → 0 |
| 　法を表す mod の文字 | 0 | 8 → 0 |
| textlint（ds と comb の全 86 ファイル）のエラー | 22 → 0 | 12 → 0 |
| textlint の警告（両分野の合計） | 1291 → 1294 | |
| fix_problems `--check`（行を触った 7 ページ） | 0 | 0 |
| render_pages（ds・comb の 88 ページ、390px のライトとダーク） | エラー 0（KaTeX・描かれない数式・地の文に残った記法・横ずれ）。表のはみ出し 0 | |

textlint の警告が 3 件増えたのは、半開区間 `[l, r)` の「Cannot find a pairing character for [」（offline-queries・sweep-line-2d の要点。既存の 193 件と同じ誤検出）と、要点を KaTeX にして長くなった文の sentence-length（offline-queries 38 行・segment-tree-binary-search 269 行）である。

## #77 表記（1 次関数・一次方程式）

- `npx textlint --fix` で prh の 34 件を直した（ds：一次関数 → 1 次関数 22 件。comb：1 次方程式 → 一次方程式・1 次結合 → 一次結合・1 次独立 → 一次独立 12 件）
- prh の置き換えで前の空白が消えた 2 か所を手で空けた：ds/advanced-ds-catalog 106 行「が 1 次関数」、ds/lazy-segment-tree-patterns 92 行「合成した 1 次関数」
- textlint が見ない front matter：ds/segment-tree-monoids の summary・signs[1]・sections[1] の title の「一次関数」を「1 次関数」にした（signs の「位置の1 次関数」も空けた）
- ds・comb に、単独の「一次」「二次」と、ヴァンデルモンド・ファンデルモンドは残っていない（grep で確認）

## #69 節の並び

並べ替えは、h2 を見出しから次の h2 の直前まで動かす道具（作業用フォルダの reorder.py。コードのフェンスの中の `##` は見ない）で行った。中身の節は今の相対順のまま前に集め、定型の節を手引き §4 の順（落とし穴 → 上位の手法へのつながり → 例題 → 練習問題 → 力試し → 確認問題 → 使い分け → 参考）に並べた。anchor・見出しの文字は変えていない。並べ替えの前後で各ページの行の集まりが同じ（ソートした行の md5 が一致）ことを確かめた。中身の節の相対順は変えていないので、front matter の sections の並びは本文の順のままで、check_pages の sections の検査も 0 である。

| ページ | 動かしたもの |
| --- | --- |
| ds/interval-set | 中身の節 valued-intervals を落とし穴の前へ |
| ds/inversion-number | 使い分けを確認問題の後へ。sliding-window を落とし穴の前へ |
| ds/kth-element | 使い分けを確認問題の後へ（bit-binary-search・reverse-insertion・vs-kth-value が落とし穴の前になる） |
| ds/lazy-segment-tree | 上の帯の invariants を例題の前へ |
| ds/linked-list・ds/stl-containers | 使い分けを練習問題の後へ（stl-containers は counting-map が落とし穴の前になる） |
| ds/mo-algorithm | 例題を落とし穴の後へ（two-prefixes・mo-on-tree・variants が落とし穴の前になる） |
| ds/monotonic-stack | cartesian-tree・swag を落とし穴の前へ |
| ds/ordered-set・ds/union-find | 使い分けを練習問題（力試し）の後へ（next-steps が落とし穴の直後になる） |
| ds/priority-queue | 確認問題を練習問題の後へ |
| ds/segment-tree-binary-search | on-lazy-segment-tree を落とし穴の前へ |
| ds/sparse-table | disjoint-sparse-table を落とし穴の前へ |
| ds/stack-techniques・comb/coupon-collector | next-steps を落とし穴の直後へ |
| ds/top-k-multiset | absolute-sum-function を落とし穴の前へ、使い分けを力試しの後へ |
| ds/union-find-applications | 使い分けを力試しの後へ |
| comb/binomial-coefficient・binomial-precompute・counting-basics・game-basics・multinomial-coefficient・nim・permutation-parity・stars-and-bars | 使い分けを例題・練習・力試し・確認問題の後へ |
| comb/counting-mindset | 確認問題と使い分けを力試しの後へ |

並べ替えで食い違った参照を直した（動いた節の中の「上の」「次の節」「この使い分け」などを grep で拾い、読んで確かめた）。

- ds/kth-element 221 行（使い分けの中）：「手順は[次の節](#bit-binary-search)で述べる」→「手順は[BIT 上の二分探索の節](#bit-binary-search)にある」
- ds/stl-containers 115 行（上位の手法へのつながりの冒頭）：「この使い分けは、上位の手法の部品になる。」→「コンテナの選び方（[早見表](#complexity-table)と[使い分け](#comparison)）は、上位の手法の部品になる。」（前にあった使い分けの節が後ろへ動いたため）
- comb/coupon-collector 115 行：「確率が違うときは[次の節](#next-steps)」→「[上位の手法へのつながり](#next-steps)」（間に落とし穴が入ったため）
- ほかの「次の節」「前の節」（ds/union-find 112・156、comb/binomial-coefficient 85、counting-mindset 68、multinomial-coefficient 96 など）は動いていない中身の節どうしで、そのままでよい

方針の折りたたみの題：練習問題の節の中の `??? note "方針"` を「練習の方針」、力試しの節の中を「力試しの方針」にした（ds 26 件・comb 8 件。ds/inversion-number・kth-element・lazy-segment-tree-patterns・lazy-segment-tree・merge-sort-tree・monotonic-stack・parallel-binary-search・partially-persistent-union-find・segment-tree-binary-search・segment-tree-monoids・segment-tree-on-values・segment-tree・sqrt-decomposition・sweep-line-2d・wavelet-matrix・weighted-union-find、comb/counting-dedup・counting-labeled-graphs・linearity-of-expectation・probability-symmetry）。

## #68 数式・平文・法の文字

### 数式にならずに残る $（エラー）

- ds/stack-techniques 90 行：`$S = $` `AABCBC` → `$S$ = `AABCBC``。201 行：`$T = $ ABC` → `$T$ = ABC`
- comb/inclusion-exclusion 239 行：「項は $+N(\emptyset) = $ 全体である」→「項は $+N(\emptyset)$ で、これは全体の個数である」
- comb/probability-dp 148 行：「$f(\text{状態}) = $「その状態から先手が勝つ確率」を、…から埋める」→「$f(\text{状態})$ を「その状態から先手が勝つ確率」とし、…から埋める」

### 要点と題の素の数式

- ds/offline-queries の要点：区間を本文の半開区間にそろえて `$[l, r)$`、`$w$`・`$X$`・`$10^9$`・`$N, Q \le 2 \times 10^5$` を KaTeX に。要点の元の front matter signs[0] も `[l, r]` → `[l, r)` にした（要点と signs の区間をそろえるため。頼まれた範囲の延長なので報告する）。あわせて例題の解法の詳細 230 行の「列の範囲 $[l, r]$」を「列の範囲（問題文の閉区間 $[l, r]$）」と明記した
- comb/divisor-inclusion-exclusion の要点：`$d$`・`$\le 10^6$`・`$g$` を KaTeX に
- 題の素の数式（12 か所）を KaTeX に：ds/binary-trie（$O(NB)$）・interval-set（$O(N + Q)$）・lazy-segment-tree（$O(1)$・$O(\log N)$）・mo-algorithm（$O(1)$）・monotonic-stack（$O(N)$・$A_j < A_i$・$A_j \ge A_i$）・persistent-data-structures（$2^{17} = 131072$）・sparse-table（$N = 10^6$・$O(1)$）・stack-techniques（$O(1)$）・weighted-union-find（$\mathrm{diff}[r_v]$。本文と同じ `\mathrm`）

### 和文に接した数式

- ds/lazy-segment-tree-patterns 87 行（表）・149 行：「（$-$最小, $-$最大）」→「（$-$ 最小, $-$ 最大）」（手引き §7 の例どおり）

### 平文の欄

- 問題の行を台帳と同じ文にした：comb/burnside-lemma 189 行（abc428_g。$x$・$U$ を平文に）・comb/permutation-cycles 194 行（abc377_e。`P_{P_i}` → `P_(P_i)`。台帳の alternatives[1] と一致）・comb/young-tableaux 146 行（abc378_g。`$AB - 1$` → `AB − 1` など）
- front matter：
  - ds/fenwick-tree signs[2]：`Σ_{j<i} [A_j ≤ A_i] のように` → `j < i の [A_j ≤ A_i] の和のように`
  - comb/binomial-prefix-sum summary：`S(n,K) = Σ_{k≤K} C(n,k) を` → `S(n,K)（k ≤ K の C(n,k) の和）を`。signs[0]：`Σ_{k≤K} C(n,k) の形の和が` → `k ≤ K の C(n,k) の和が`
  - comb/burnside-lemma summary：`(1/n) Σ_{d|n} φ(d) k^(n/d) になる` → `d | n の φ(d) k^(n/d) の和を n で割った値になる`
  - comb/expectation-of-square complexity：`Σ_{i<j} A_i A_j を` → `i < j の A_i A_j の和を`
  - comb/expectation-tail-sum summary：`E[X] = Σ_{k≥1} P(X ≥ k) が成り立つ` → `E[X] は k ≥ 1 の P(X ≥ k) の和に等しい`
  - comb/mobius-function summary：`F(n) = Σ_{d|n} f(d)` → `F(n)（d | n の f(d) の和）`、`[gcd = 1] = Σ_{d|gcd} μ(d) と置き換えて` → `[gcd = 1] を d | gcd の μ(d) の和に置き換えて、`

### 法の文字

どのページも $p$ を確率（comb/generating-function-counting は多項式 $p(x)$）に使っているので、法は $m$ にした。

- comb/coupon-collector：要点「法 $P = 998244353$ … $O(N \log P)$」→「法 $m = 998244353$（素数）… $O(N \log m)$」。元の front matter complexity の「法を P として … O(N log P)」も「法を m として … O(N log m)」にした（要点と同じ文字にするため）
- comb/expected-value-dp：要点 45 行「mod 998244353 で … $O(\log \mathrm{mod})$」→「法 $m = 998244353$（素数）で … $O(\log m)$」、237 行の割り算を $O(\log m)$。front matter complexity の「O(log mod)」も「法を m として … O(log m)」にした
- comb/expectation-linear-equations：95 行（最初に出る所）で「法を $m$（素数）とすると 1 回 $O(\log m)$」と書き、117・206・224 行を $\log m$ に。同じページの 165 行で遷移の総数に $m$ を使っていたので、$M$ にした（$O(k \, m + k^3)$ → $O(kM + k^3)$）。178 行の $M$（サイコロの目の最大、すごろくの例の中だけ）とは別の文の局所的な文字である
- comb/probability-dp 214 行：「法を $m$（素数）とすると、… `b.inv()`（$O(\log m)$）」。同じ文のインラインのコード `mint inv_m = mint(m).inv();` の `m` が法と紛れるので、「同じ数 $d$ で何度も割るなら `mint inv_d = mint(d).inv();`」にし、「$0$ 以上 mod 未満」を「$0$ 以上 $m$ 未満」にした
- comb/generating-function-counting 157 行：「法を $m$ として $O(n \log n + \log m)$」

## 閉区間の断りの残り（手引き §6）

- ds/fenwick-tree：内部の 1-indexed の箱の説明（84 行「閉区間 $[1, 7]$」）、確認問題の答え（317 行「閉区間 $[1, 13]$」）、問題文の区間（261 行「閉区間 $[x, y]$ の XOR」）。練習の解法の詳細（279 行）の `cnt[0, id_j]` は半開区間 `cnt[0, id_j + 1)`（「位置 id_j 以下の和」）に直した。76 行の箱の定義 $(i - \mathrm{lowbit}(i), i]$ は直前の和の式で範囲が分かるのでそのまま
- ds/segment-tree-on-values 208 行（例題 ABC339 E）：「閉区間 $[A_i - D, A_i + D]$ の max」
- ds/sweep-line-2d：要点と signs[2]（「閉区間 [p, q] に完全に含まれる区間の数」。要点と signs をそろえた）、区間を点と見る節の冒頭で「この節の区間は、問題文と同じ閉区間 $[L, R]$ で書き」と断った（表と式の $[L, R]$・$[p, q]$ はこの断りで読む）、150 行「閉区間 $[l, r]$ そのもの」、固定幅の窓の式の後に「右辺の 2 つの範囲は、どちらも閉区間である（半開区間なら $[t - D + 1, t + 1)$・$[x - W + 1, x + 1)$）」の 1 文、167 行・258 行「閉区間 $[x - W + 1, x]$」「閉区間 $[\max(0, X - W + 1), X]$」。練習・力試しの行の要約（ABC106 D・ABC360 F の「区間 [p, q]」「区間 [l, r]」）は台帳の文なので変えていない

## ds/advanced-ds-catalog#table の 3 列化

4 列（名前 ｜ 何ができるか ｜ 計算量 ｜ 代わりになる手）を 3 列（「名前：何ができるか ｜ 計算量 ｜ 代わりになる手」）に組み直した。1 列目は「**名前**：何ができるか」の形で、10 行とも中身の文は変えていない（セルを分けて 4 つあることを確かめてから結んだ）。render_pages で、390px の表のはみ出しは ds・comb で 0 件。

## render_pages の結果

作業用フォルダに `.venv/bin/mkdocs build -d …/pages-c/site` でビルドし、`render_pages.py --field ds --field comb` で 88 ページを描いた。エラーは 0（comb/inclusion-exclusion・comb/probability-dp・ds/stack-techniques の地の文の $ も消えた）。

残った警告は「画面の幅を超える別行の数式」15 件・8 ページで、今回は触っていない既存の式（スクロールで読める）：ds/balanced-bst（treap）・fenwick-tree（variants）・global-offset・lazy-segment-tree-patterns 2 件・segment-tree-monoids 5 件・segment-tree-on-values・sweep-line-2d 3 件・weighted-union-find。sweep-line-2d の 1 件（固定幅の窓の式）は今回の断りの文の直前の式で、式そのものは変えていない。

## 提案（メインに頼む共有ファイルの変更）

- なし（台帳の summary と本文の行は 3 問とも台帳の文にそろえたので、台帳の変更は要らない）

## メインに判断してほしい点

- front matter の頼まれていない項目を、要点とそろえるために 5 か所直した：ds/offline-queries signs[0]（`[l, r]` → `[l, r)`）・ds/sweep-line-2d signs[2]（「閉区間」を足した）・ds/segment-tree-monoids の summary・signs・sections の「一次関数」（#77 の front matter の手直し）・comb/coupon-collector と comb/expected-value-dp の complexity（法の文字）。signs・summary・complexity は生成ページ（分野の入口・一覧・llms.txt）に出るので、gen_site で作り直してほしい
- comb/expectation-linear-equations 165 行の遷移の総数を $m$ から $M$ に変えた（法の $m$ と分けるため）。同じページの 178 行で $M$ をサイコロの目の最大に使っている（別の段落の例の中）。気になるなら別の文字（$|E|$ など）にする
