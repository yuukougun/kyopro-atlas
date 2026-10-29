# pattern-rows の報告（バッチ patterns）

- 担当の Issue：#66（完了）
- 作業ツリー：/home/yuuki/projects/kyopro2/kyopro-atlas-wt/patterns（ブランチ feat/patterns）。git は読むだけで、commit などはしていない。Issue にはコメント・編集・クローズをしていない
- 直したファイル（10）：docs/patterns/ の bracket-sequence.md・divisors-and-multiples.md・grid.md・interval.md・kth-and-median.md・mex.md・operation-sequence.md・permutation.md・subsequence-and-substring.md・xor.md（docs/patterns/index.md は生成物なので触れていない）
- front matter で変えたもの：`updated`（2026-10-22 だった 6 ページを 2026-10-29 にした。ほかの 4 ページはもとから 2026-10-29）と、xor の `sections` に足した 1 節（`adjacent-xor`）だけ。既存の anchor・stage・ほかの項目は変えていない
- 生成物には触れていない。`gen_site.py --check` で 4 ファイルが古くなる（下の「検査」）。メインが作り直す

## #66 題材別の表の各行から、その行の節へ移れるようにする（完了）

### 形（見本 bracket-sequence で決め、ほかの 9 ページをそろえた）

1. 表の「よく出る問われ方」の列の文字を、そのまま行の節へのリンク `[問われ方](#anchor)` にした。1 つの節が 2 行を受け持つところは、どちらの行も同じ節へリンクした（divisors-and-multiples の素因数分解の 2 行 → `#factorize`、kth-and-median の 2 行 → `#streaming`、mex の窓の最小値・最大値 → `#window-mex`、operation-sequence の 2 行 → `#insert-delete`、permutation の 2 行 → `#counting`）
2. 一覧の節の最初の段落の 1 文目を「問題文の形から行を探し、問われ方のリンクから行の節へ移る。節で〈…〉を確かめてから、手法のページへ進む。」にした。〈…〉は要点の「使い方」に合わせ、mex は「性質の使い方」、operation-sequence は「使い分け」、xor は「使う性質」、ほかは「言い換え」とした。2 文目以降（代表の問題の書き方など）は変えていない
3. 「ページ」の列にあった、このページの節へのリンク（interval の 1 行、permutation の 2 行）は、問われ方の列のリンクと行き先が同じになるので外した
    - interval 94 行目：「題材別の各ページ（[節](#other-statistics)）」→「題材別の各ページ」
    - permutation 84 行目：「このページの[節](#inverse)」→「このページ」（逆置換を扱う手法のページはなく、この節が持ち主である）
    - permutation 87 行目：「このページの[節](#lexicographic)、[順列全探索](…)」→「このページ、[順列全探索](…)」
4. bracket-sequence の「同上（点の更新で済ませる）」は、リンクの文字だけで問われ方が分かるように「更新ありで区間が正しいか（点の更新で済ませる）」にした（→ `#monoid`）
5. operation-sequence の表の直後の「ページの欄に複数の手法がある行は、行の節で使い分けを確かめてから進む。」は、2 の最初の段落（「節で使い分けを確かめてから、手法のページへ進む」）と重なるので消した

### ページごとの箇所（行番号は直した後のもの）

| ページ | 最初の段落 | 表の行 | ほか |
|---|---|---|---|
| bracket-sequence | 73 | 77〜84（8 行） | 81 行目の「同上」を書き直した |
| divisors-and-multiples | 74 | 78〜88（11 行） | updated |
| grid | 80 | 84〜93（10 行） | — |
| interval | 84 | 90〜115（3 つの表で 16 行） | 94 行目のページの列、updated |
| kth-and-median | 79 | 83〜92（10 行） | updated |
| mex | 76 | 80〜86（7 行） | — |
| operation-sequence | 74 | 78〜87（10 行） | 表の後の 1 文を消した、updated |
| permutation | 76 | 80〜88（9 行） | 84・87 行目のページの列、updated |
| subsequence-and-substring | 77 | 81〜90（10 行） | — |
| xor | 87 | 91〜103（13 行） | 36 行目（sections）、195〜201 行目（足した節） |

行の順の行き先（検証用）：

- bracket-sequence：check・stack・counting・range-check・monoid・ordering・max-value・parsing
- divisors-and-multiples：enumerate・count-bound・harmonic・factorize・factorize・divisor-functions・exact-gcd・zeta・products・gcd・floor-sums
- grid：shortest・states・components・right-down・rectangles・rows-cols・checkerboard・diagonal・rotation・tiling
- interval：sum・count-by-sum・monotone-window・sum-over-subarrays・other-statistics・partition・shrink-and-merge・substrings／batch-add・online-updates・static-min・difference・offline／scheduling・union・containment
- kth-and-median：count-and-search・streaming・streaming・dynamic・k-best・range-kth・maximize-median・absolute-sum・lexicographic-kth・xor-kth
- mex：online-mex・interval-values・window-mex・window-mex・sum-of-mex・grundy・construction
- operation-sequence：global-ops・insert-delete・insert-delete・paint・overwrite・reverse-deletion・offline・online・versions・repeat
- permutation：any-swap・adjacent-swap・swap-parity・repeat・inverse・counting・counting・lexicographic・increasing
- subsequence-and-substring：is-subsequence・count-occurrences・count-with-condition・distinct-subsequences・index-tuples・longest・substring-match・distinct-substrings・palindromes・avoid-substring
- xor：sum-of-xor・range-xor・tree-path・choose-x・basis・path-xor・digit-dp・xor-equals-sum・meet-in-the-middle・games・set-hash・xor-convolution・adjacent-xor（足した節）

対応は、行の問われ方と節の中身を読んで決めた。operation-sequence の「直前と打ち消し合うものを消す・直前を取り消す」は、`#insert-delete` の最後の段落（スタックで打ち消す・取り消す。stack-techniques#cancel・#undo へのリンク）が受け持つので、そこへリンクした。

### xor の ABC150 F の行：節を足した（行は外していない）

表の 103 行目「列全体を同じ値で XOR したものを探す｜隣どうしの XOR の列で照合（打消）｜[KMP 法](../string/kmp.md#abc150_f)｜ABC150 F」には節がなかった。外さずに節を足した。この行は「同じ値で打ち消し合う」性質の典型の使い方で、ほかの行と重ならない。ABC の F（diff 2281）で、黄色を目指す読者の水準にも合う。節を足したので、表の直後の「代表の問題は…、リンクは行の節から張った。」も正しくなった。

- 見出し：`## 列全体を同じ値で XOR したものを探す → 隣どうしの XOR の列で照合（kmp） {#adjacent-xor}`。前半は表の行の文字と同じで、ほかの節と同じ「問われ方 → 手法（id）」の形にした。front matter の sections の最後（xor-convolution の後）に同じ title で足した。本文の位置も表の順に合わせ、`#xor-convolution` と `#pitfalls` の間にした
- 中身（3 段落）：シフト量 $k$ を決めれば $x = a_k \oplus b_0$ に決まるが、$k$ ごとに比べると $O(N^2)$ かかる。隣どうしの XOR では $x$ が 2 回現れて打ち消し合う。両方の列を隣どうしの XOR の列に直し、$a'$ を 2 周つないだ列で $b'$ の出現を KMP 法の[パターン照合](../string/kmp.md#matching)で求めれば $O(N)$ である。一致した位置で $x = a_k \oplus b_0$ とすれば、残りの要素も順にそろう。巡回でない連続部分と一致させる場合も同じ形で解ける。代表は [KMP 法の例題 ABC150 F](../string/kmp.md#abc150_f)（xor の #range-xor の「[BIT の例題 ABC185 F](…)」と同じ書き方）
- 確かめたこと
    - `python3 tools/ap.py show abc150_f`：OK、F. Xor Shift、diff 2281。台帳では確認済みで、kmp の例題・rolling-hash の力試し
    - 式と手順は kmp の例題の節（docs/string/kmp.md 252〜266 行目）と一致する。台帳の evidence の drken「AtCoder ABC 150 F - Xor Shift」は kmp の参考の節にあり、xor では新しい出典を使っていない（Web は開いていない）
    - 巡回でない場合は、長い列 $T$ の位置 $s$ からの窓と $P$ について「ある $x$ で $T_{s+i} \oplus x = P_i$（すべての $i$）」⇔「$T_{s+i} \oplus P_i$ が $i$ によらず一定」⇔「隣どうしの XOR の列が一致する」を式で確かめた
- 台帳は変えない：pattern のページを台帳の pages に持つのは、そのページの囲みにある問題だけである（xor なら abc171_e・abc197_c）。表の代表の問題（abc283_g・abc147_d など）は載っていないので、abc150_f も同じ扱いにした

### 確かめたこと

- 作業用フォルダへの `uv run mkdocs build --strict -d <作業用フォルダ>/site` が警告なしで通った
- ビルドした HTML をスクリプト（作業用フォルダの verify_html.py）で読んだ。10 ページの一覧の表の 104 行すべてで、最初のセルのリンクがちょうど 1 つで、同じページの h2（overview・properties 以外）の id を指していた。ほかのセルに残ったこのページへのリンクは、operation-sequence の代表の問題の列の `#practice` だけである（下の「残った点」）
- リンクの文字に数式を含む 19 行（divisors の $N \le 10^{12}$、kth の $\sum_i \lvert x - a_i \rvert$ など）は arithmatex の span になった。ヘッドレスの Chrome を 390px 幅にして、ローカルに出したビルドを撮った。KaTeX の式がリンクの色で描かれていた（この環境に日本語のフォントがないので、和文は豆腐になる）。表の 4 列目がはみ出して横にスクロールするのは前からで、この変更でセルの文字は増えていない
- 完了の条件「10 ページの表のどの行からも、1 回のクリックで行の節に着く」を満たす

### 残った点

- subsequence-and-substring の `#subarrays`（数列の連続部分列 → 区間）は表に行がなく、表の直後の文（92 行目「…[区間の題材のページ](#subarrays)へ進む」）からリンクしている。Issue の条件（行 → 節）は満たしている。interval の「文字列の連続部分」の行（→ `#substrings`）と対にするなら行を足せる（提案 4）
- operation-sequence の「最後の状態だけを問う・後の操作が上書きする」の行は、代表の問題の列が「ABC466 D（このページの[練習](#practice)）」である。節ではなくこのページの練習の囲みへのリンクで、§16-7 の「自分の例題・練習の囲みを持つのは構わない」に当たるので残した

## 検査

- `python3 tools/check_pages.py --page <10 ページ>`：エラー 0・警告 0。全ページ（353）でもエラー 0・警告 0
- `python3 tools/fix_problems.py --check --page <id>`（10 ページ）：どれも直すべき行 0
- `npx textlint`（10 ページ）：エラー 0、警告 112。直す前も 112 件だった。行と列の位置を除いて文を比べた。違いは、文の中の行番号が変わった 2 件だけである（operation-sequence で 2 行消し、xor の front matter に 1 行足したため）。足した節と書き直した段落から出た警告はない
- 作業用フォルダへの `mkdocs build --strict`：警告なし
- `python3 tools/gen_site.py --check`：4 ファイルが古い。docs/llms.txt・graph.json・docs/start/how-to-use.md は版の値（ce5bc86bd22f → 7bb8bfdaf531）だけ。docs/index/patterns.md は版の値と、`xor#adjacent-xor` の 1 行が増える
- check_snippets・check_svg・render_svg：コード片と図に触れていないので流していない

## 提案（共有ファイル）

1. **手引き §4 の pattern**：次の形にする（足すのは「→ 行ごとの節」以降の 2 文）。
    > - **pattern**：題材の性質 → 「問われ方と手法の一覧」の節（anchor `overview`。中身の節として sections に置く）→ 「よく出る問われ方 → 使う手法 → ページ」の表 → 行ごとの節（見出しは「問われ方 → 手法（行き先の id）」）。表の「よく出る問われ方」の列は、その行の節へのリンクにする（§16-7）。問題は行の代表だけで、表の「代表の問題」の列には行き先のページの問題の label を文字だけで書き、リンクは行き先のページに任せる（見本 bracket-sequence の形。§16-7・§16-9）
2. **手引き §16-7**：題を「pattern の表の列」にし、今の文の後ろに次を足す。
    > 「よく出る問われ方」の列は、文字をそのまま行の節へのリンクにする（`| [更新ありで区間が正しいか](#range-check) | … |`）。1 つの節が 2 行を受け持つなら、どちらの行も同じ節へリンクする。どの行にも節を置き、節のない行は節を足すか行を外す。「同上」とは書かず、リンクの文字だけで問われ方が分かるようにする。「ページ」の列には行き先のページだけを書き、このページの節へのリンクは問われ方の列に任せる（行き先がこのページの節だけなら「このページ」と書く）。一覧の節の最初の段落で「問われ方のリンクから行の節へ移る」と案内する（Issue #66、2026-10-29）
3. **xor の front matter の related に `kmp` を足す**：足した節の見出しが（kmp）を名乗り、本文で kmp#matching・kmp#abc150_f へリンクしている。ほかの節の見出しの id（two-pointers・digit-dp など）はどれも related にあるのでそろえる。front matter の related は頼まれた項目の外なので変えていない（graph.json の辺が 1 本増える）
4. **（任意）subsequence-and-substring の表に `#subarrays` の行を足す**：例「| [数列の連続部分列（区間）の和・個数](#subarrays) | 累積和・尺取り法など | [区間](../patterns/interval.md#overview) | — |」。足すなら、77 行目の「上の 6 行が部分列、下の 4 行が主に部分文字列の問われ方である。」も直す
5. **（任意）check_pages.py に検査を足す**：type が pattern のページで、`## … {#overview}` の節の表（見出しが「よく出る問われ方」）の各行の最初のセルが、そのページの sections の anchor へのリンクでなければ警告にする。今回の形が崩れるのを防げる

## メインに判断してほしい点

- 「ページ」の列で、このページの節へのリンクを外した 3 か所（interval「題材別の各ページ」、permutation「このページ」2 か所）を、リンクのない文字にしてよいか。interval は、中央値・mex・転倒数の行き先のページ（kth-and-median・mex・inversion-number など）を並べる案もある。その場合は節の箇条書きとリンクが重なり、セルが長くなるので採らなかった
- 提案 4（subsequence-and-substring の `#subarrays` の行）を足すか

## 使用量の目安

- 道具の呼び出し：約 65 回（読む・検査・ビルド・画面の撮影を含む）。Web の取得：0 回（atcoder.jp・codeforces.com は開いていない）
- 作業用のファイル：/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/7a638398-7759-4637-95c7-6739e8d52414/scratchpad/fix/patterns/pattern-rows/（apply.py＝置き換えのスクリプト、verify_html.py＝ビルドした HTML の検査、textlint-before.txt・textlint-after.txt、gen_site_diff.txt、shots/＝画面の撮影、site/＝ビルド）
