# verify-pattern-rows の報告（バッチ patterns）

- 検証した直し：担当 pattern-rows の #66（報告は [pattern-rows.md](pattern-rows.md)）
- 作業ツリー：/home/yuuki/projects/kyopro2/kyopro-atlas-wt/patterns（ブランチ feat/patterns、commit 前の差分）。ファイルは直していない。git は読むだけで、Issue にはコメント・編集・クローズをしていない
- 見た差分：docs/patterns/ の 10 ページ（bracket-sequence・divisors-and-multiples・grid・interval・kth-and-median・mex・operation-sequence・permutation・subsequence-and-substring・xor）と pattern-rows.md

## 結果

| Issue | 判定 | 直しが要る点 |
|---|---|---|
| #66 題材別の表の各行から、その行の節へ移れるようにする | 合格 | 0 |

完了の条件「10 ページの表のどの行からも、1 回のクリックで行の節に着く」を満たす。やることのうち、手引き §4・§16-7 の書き換えはメインの仕事で、担当は報告で提案している（下の「メインへ」の 1）。

## 確かめたこと

### 1. 表のすべての行が同じページの節へリンクしているか（スクリプトで数えた）

- Markdown（作業用フォルダの check_rows.py）：10 ページの一覧の節の表の全 104 行（8・11・10・16・10・7・10・9・10・13）で、「よく出る問われ方」のセルが `[文字](#anchor)` のリンク 1 つだけでできていた。行き先はどれも同じページの `##` の中身の節で、overview・properties・定型の節を指す行はない。行の数は直す前と同じで、外した行はない
- ビルドした HTML（check_html.py）：104 行すべてで、最初のセルにある `<a>` は 1 つだけだった。リンクがセルの文字全体を包み、href は同じページの h2 の id を指していた。ほかのセルに残ったこのページへのリンクは、operation-sequence の代表の問題の列の `#practice` だけである。これは前からある練習の囲みへのリンクで、§16-7 の「自分の例題・練習の囲みを持つのは構わない」に当たる
- 2 行が 1 つの節を指すのは 5 組だった：divisors-and-multiples の `#factorize`、kth-and-median の `#streaming`、mex の `#window-mex`、operation-sequence の `#insert-delete`、permutation の `#counting`。Issue の「どちらの行も同じ節へリンクする」のとおりである
- 文字を変えたのは bracket-sequence の 1 行だけである（「同上（点の更新で済ませる）」を「更新ありで区間が正しいか（点の更新で済ませる）」にした）。ほかの列で変わったのは、報告にある 3 か所だけだった（interval 94 行目、permutation 84・87 行目の「ページ」の列）

### 2. 行と節の中身が合っているか

104 行のそれぞれについて、行の問われ方と、行き先の節の見出し・本文を読み比べた。どの行も、行き先の節がその問われ方を扱っている。行を外す・節を足すべきものは、xor の ABC150 F の行のほかにない。

- 2 行で 1 つの節を指すところは、節の中に両方の行の話がある。kth `#streaming` には K 固定のヒープと、上位 K 個の和・中央値の 2 つの multiset がある。mex `#window-mex` には最小値と最大値（答えの二分探索と固定長の窓）がある。operation-sequence `#insert-delete` は最後の段落で、打ち消して消す操作（stack-techniques#cancel）と取り消し（#undo）を扱う。permutation `#counting` の表には、隣の大小・位置と値のずれ・撹乱順列の行がある。divisors `#factorize` は 1 つの数と多数の数の両方を扱う
- 見出しと行の文字が離れている行も、本文に行の話があった。interval `#sum-over-subarrays` の最大長方形、`#containment` の 2 つの区間の組、`#shrink-and-merge` の合体、grid `#states` の壁を壊した回数・2 人の位置、divisors `#zeta` の GCD 畳み込み、`#exact-gcd` の部分集合、subsequence `#substring-match` の KMP 法がそうである

### 3. xor に足した節 `#adjacent-xor`（195〜201 行目）

- 表の行（103 行目）と中身が合う。問われ方は巡回シフトに同じ $x$ を XOR したものを探す形、使う手法は隣どうしの XOR の列での照合、性質は（打消）である
- 事実：$x = a_k \oplus b_0$、$(a_i \oplus x) \oplus (a_{i+1} \oplus x) = a_i \oplus a_{i+1}$、巡回なので末尾と先頭の組を入れる、2 周つないだ列での照合、全体 $O(N)$ を確かめた。どれも正しく、kmp の例題（docs/string/kmp.md 252〜266 行目）と食い違わない。巡回でない場合も確かめた。$T_{s+i} \oplus x = P_i$ がすべての $i$ で成り立つことは、$T_{s+i} \oplus P_i$ が一定であることと同じで、隣どうしの XOR の列が一致することとも同じである
- 問題：`python3 tools/ap.py show abc150_f` は OK（F. Xor Shift、diff 2281）だった。台帳では確認済みで、kmp の例題・rolling-hash の力試しになっている。本文は kmp#abc150_f へのリンクで触れ、atcoder.jp へのリンクは置いていない。表の「代表の問題」の列は label の文字だけである（§16-7）
- 形：見出しと sections の title が一致し、sections の並びと本文の並びも一致する（xor-convolution の後、pitfalls の前）。anchor は英小文字とハイフンで、波かっこはない
- 表の直後の「代表の問題は…、リンクは行の節から張った。」が正しくなった。13 行の代表の問題は、どれも行の節からリンクされている

### 4. 既存の anchor・front matter

- 10 ページの見出しの anchor（`###` の例題を含む）と sections の anchor を、HEAD と比べた。消えた・変わった anchor はなく、増えたのは xor の `adjacent-xor` だけである。重なりもない
- front matter で変わったのは、`updated` と xor の `sections`（1 節を足した）だけだった。`updated` を変えたのは 5 ページ（divisors-and-multiples・interval・kth-and-median・operation-sequence・permutation）で、ほかの 5 ページは前から 2026-10-29 だった。日付はどれも 2026-10-29（今日）である
- ほかのページからこの 10 ページの節へのリンクは、anchor が変わらないので壊れない。mkdocs の anchors の検査（validation の anchors: warn）でも警告は出なかった

### 5. 検査（書き換えない検査）

- `python3 tools/check_pages.py --page <id>`（10 ページ）：どれもエラー 0・警告 0。全ページ（354）でもエラー 0・警告 0
- `python3 tools/fix_problems.py --check --page <id>`（10 ページ）：どれも直すべき行 0
- `npx textlint`（10 ページ）：エラー 0・警告 112。HEAD の 10 ページを作業用フォルダに出して、同じ設定で流しても 112 件だった。違うのは、文の中の行番号が変わった 2 件（operation-sequence・xor）だけである。足した節と書き直した段落から出た警告はない
- `git diff --check`：空白の誤りはない
- check_snippets・check_svg・viz の試験：コード片・図・動く図に触れていないので流していない
- `gen_site.py` はメインだけが流すので、流していない。生成物で変わるのは、docs/index/patterns.md に増える `xor#adjacent-xor` の行と、版の値である（担当の報告のとおり）

### 6. 表示（作業用フォルダへのビルドとヘッドレスの Chrome）

- `uv run mkdocs build --strict -d <作業用フォルダ>/site` は、警告 1 件で止まった。原因は docs/patterns/circular.md が nav にないことである。このファイルは、同じ作業ツリーで別の担当（circle-page）が足している途中の新しいページで、#66 の直しとは関係がない。--strict を外したビルドでは、警告はこの 1 件だけだった
- `http://127.0.0.1:<ポート>/site/…` で 10 ページを開き、JS を動かした後の DOM を見た。KaTeX のエラー（.katex-error）は 0 件だった。リンクの文字に数式を含む 19 行（divisors 4・kth 9・operation-sequence 1・permutation 3・xor 2）は、どれも KaTeX で描かれていた
- 幅 390px・ライトとダークで、xor の表と足した節、kth-and-median の表、divisors-and-multiples の表を撮って見た。問われ方の列がリンクの色になり、数式もリンクの色で読める。ダークモードでも読める。表の 4 列目が画面からはみ出して横にスクロールするのは、直す前からである

## 直しが要る点

なし。

## メインへ（担当の直しは要らない）

1. **手引き §4・§16-7**：Issue のやることの「手引き §4（pattern）・§16-7 にこの形を足す」は、まだ反映されていない。担当の提案 1・2 の文は、実際の直しと合っている（問われ方の列のリンク、2 行で 1 つの節、「同上」を使わない、ページの列にこのページの節へのリンクを置かない、一覧の節の最初の段落での案内）。メインが反映すると、Issue のやることがすべて終わる
2. **生成物**：`gen_site.py` で docs/index/patterns.md（`xor#adjacent-xor` の行）・llms.txt・graph.json・how-to-use の版を作り直す
3. **提案 3（xor の related に kmp）**：足してよいと考える。ただ、見出しの id が related にないのは xor だけではない（interval `#other-statistics` の kth-and-median・mex・permutation、kth-and-median `#k-best` の greedy-priority-queue）。決まりにはなっていないので、必須ではない
4. **担当が判断を求めた点**：interval の「題材別の各ページ」と、permutation の「このページ」（2 か所）は、リンクのない文字のままでよいと考える。どの行も、問われ方のリンクから 1 回で節に着く。interval の行の節には、行き先のページ（kth-and-median・mex・inversion-number など）へのリンクが並んでいる
5. **担当の報告の小さな誤り**：「2026-10-22 だった 6 ページを 2026-10-29 にした。ほかの 4 ページはもとから 2026-10-29」とあるが、正しくは 5 ページと 5 ページである（4 の箇所を参照）。ページへの影響はない
6. **（任意）足した節の書き方**：次の 2 つは kmp の例題の節に書いてあるので、なくても誤りではない。足すなら、1 文目の前に「0-indexed で」と添え（§6 の添字の約束）、「2 周つないだ列の中で、位置 $0 \le k < N$ の出現を求める」とする

## 作業用のファイル

/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/7a638398-7759-4637-95c7-6739e8d52414/scratchpad/fix/patterns/verify-pattern-rows/ に置いた。

- check_rows.py：Markdown の表の行と節の対応、anchor・sections の比較。結果は rows.txt
- check_html.py：ビルドした HTML の表の行の検査。結果は html.txt
- show_sec.py：節の本文を取り出す
- textlint-before.txt・textlint-after.txt：textlint の結果の比較
- dom/：JS を動かした後の DOM
- shots/：390px のライトとダークの画面
- site/：ビルドしたサイト
- offsets.html：撮る位置を測る補助のページ
