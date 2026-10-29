# circle-page の報告（バッチ patterns）

- 担当の Issue：#75（一部。ページは足した。入口から by-topic への案内は別のグループの担当）
- 作業ツリー：/home/yuuki/projects/kyopro2/kyopro-atlas-wt/patterns（ブランチ feat/patterns）。git は読むだけで、commit などはしていない。Issue にはコメント・編集・クローズをしていない
- 書いたファイル（新規 2）：`docs/patterns/circular.md`、`docs/img/circular/unroll.svg`。ほかのページ・生成物・共有のファイルには触れていない
- front matter：新しいページなので全部を書いた（下の「front matter」）。`stage: draft`、`updated: 2026-10-29`

## #75 題材別に「円環」のページを足す（一部）

### 直した内容

`docs/patterns/circular.md`（264 行）を足した。構成は手引き §4 の pattern と見本 bracket-sequence の形で、「題材の性質 → 問われ方と手法の一覧 → 行ごとの節 → 落とし穴 → 参考」の順である。問題の囲み（例題・練習）は置いていない（指示どおり。台帳に問題を足していない）。

- 44〜54 行：要点。「何のページか・いつ使うか（signs の 5 つ）・使い方・計算量・前提（なし）」。使い方の文はほかの 10 ページと同じにした
- 56〜58 行：別名の行（aliases をすべて。textlint から外す）。60 行：題名を主語にした導入
- 62〜86 行 `#properties`：0-indexed と時計回りの約束、3 つの言い換え（2 周分に伸ばす・1 か所で切る・回転は 2 周分の窓）、図、2 点の距離 $\min(d, L - d)$ と累積和での書き方、端がないこと、グラフでは閉路にあたること、確認問題（区間の数 $N^2$ と集合として $N(N-1)+1$）
- 88〜126 行 `#overview`：最初の段落は #66 の担当（pattern-rows）がほかの 10 ページにそろえた文と同じにした（「問題文の形から行を探し、問われ方のリンクから行の節へ移る。節で言い換えを確かめてから、手法のページへ進む。」）。表は interval と同じく 4 つの群に分けた（4 列。16 行）。「よく出る問われ方」の列は、どの行も同じページの行の節へのリンク `[問われ方](#anchor)` で、#66 の形と同じである
- 128〜250 行：行ごとの節 16 個。見出しは「問われ方 → 手法（行き先の id）」の形。どの節も、言い換えを 1〜3 段落で書き、詳しい説明は行き先のページの節へのリンクに任せた。節の中の確認問題は 2 つ（#cut の円環の最大和の DP、#rotation-match の `aaaa`）
- 252〜258 行 `#pitfalls`：負の数の余り、長さ $N$ 以上の区間と $N$ 回目の回転、小さい $N$、固定した最初の状態との整合、更新のある列を 2 周分に伸ばす
- 260〜264 行 `#references`：3 件（下の「使った出典」）

### 表の行・行の節・行き先・代表の問題

| 群 | 行の節（anchor） | 行き先（ページの節） | 代表の問題（行き先での役割） |
|---|---|---|---|
| 列が円形に並ぶ | sum | basics/prefix-sum#circular | 典型90 076（練習） |
| 〃 | count-pairs | basics/prefix-sum-counting#circular | ABC367 D（練習） |
| 〃 | range-add | ds/fenwick-tree#variants、ds/lazy-segment-tree#dual-segment-tree | ABC340 E（どちらも練習） |
| 〃 | difference | basics/difference-sequence#circular | AGC010 B（練習） |
| 最後と最初の両方に条件 | coloring | comb/counting-basics#coloring | ABC307 E（練習） |
| 〃 | cut | dp/dp-state-design#dp-cyclic | ABC307 E（練習） |
| 〃 | up-to-rotation | comb/counting-basics#permutations、comb/burnside-lemma#necklace | ABC428 G（burnside の例題） |
| 〃 | cyclic-dependency | comb/expectation-linear-equations#cycle | ABC333 F（例題） |
| 〃 | shift | dp/inline-dp#global-shift | ABC372 F（例題） |
| 回転（巡回シフト） | rotation-match | string/string-basics#rotation、string/z-algorithm#cyclic-shift | ABC286 C（string-basics の練習）、ABC430 E（z-algorithm の例題） |
| 〃 | rotation-order | string/suffix-array#rotations | ABC272 F（練習） |
| 〃 | all-rotations | ds/inversion-number#incremental、math/convolution-ntt#reverse | ABC190 F（例題）、ABC291 G（練習） |
| 円周上の点・弦・閉路 | angles | geometry/argument-sort#wrap-around | ABC442 E（例題）、ABC139 F（練習） |
| 〃 | chords | ds/stack-techniques#chords | ABC338 E（練習） |
| 〃 | step | math/gcd-properties#step-mod、math/ext-gcd#applications | ABC186 E（ext-gcd の例題）、ABC210 E（gcd-properties の練習） |
| 〃 | namori | graph/namori-graph#hanging-trees | ABC266 F（例題） |

- Issue に挙げた手法（累積和を 2 周分・差分列・塗り分け・1 か所で切る DP・回転の一致・偏角の 2 周分の尺取り・なもりグラフ）はすべて行にした。ほかに、本文に「円環」「円周」「巡回シフト」を含むページを調べ、型がはっきり分かれるもの（円環上の組を数える・更新のある区間加算・円順列と Burnside・円環状の依存の期待値・添字のずらし・回転どうしの辞書順・すべての回転の値・弦の交差・円周を K ずつ進む）を足した
- 節の中では、表に載せない行き先へもリンクした：prefix-sum#with-binary-search、stars-and-bars#gaps（円形の席から隣り合わない K 席）、convolution-ntt#split-by-bit、argument-sort#range-count・#half-plane-compare、merge-sort-tree#query・hashing-for-sets#with-fenwick・dp-segment-tree#challenge（弦の数え上げ・弦の追加・2 周分に開いて切る場所を全部試す）、graph/functional-graph、math/integer-division#cpp-vs-math、用語集 #half-open-interval
- 代表の問題は label の文字だけで書いた（§16-7）。2 問の行は易しい順にした

### front matter

- `id: circular`、`title: 円環`、`type: pattern`、`field: patterns`、`level: null`、`complexity: null`、`acl: []`、`prerequisites: []`（要点の前提も「なし」）、`stage: draft`、`updated: 2026-10-29`。`chapter` はほかの題材別のページと同じく書いていない
- `order: 110`：ほかの 10 ページは 10〜100 の 10 刻みで、重ならない最後の値にした（下の「判断してほしい点」）
- `kind: [案内, 累積和・差分, 数え上げ]`
- `aliases`：環状・円形に並ぶ・円周上に並ぶ・最後と最初が隣り合う・2 周分に伸ばす・輪・リング・circular・cyclic・ring。全ページの題名・別名と照らし合わせ、重なりがないことを確かめた（「円周」だけにすると円の幾何を探す人も来るので「円周上に並ぶ」にした）
- `related`：表の行き先の 20 ページ（prefix-sum・prefix-sum-counting・fenwick-tree・lazy-segment-tree・difference-sequence・counting-basics・dp-state-design・burnside-lemma・expectation-linear-equations・inline-dp・string-basics・z-algorithm・suffix-array・inversion-number・convolution-ntt・argument-sort・stack-techniques・gcd-properties・ext-gcd・namori-graph）
- `summary`（102 字・2 文）：円形に並ぶ列のように、最後と最初も隣り合う並びを含む問題で、問われ方から使う手法を引ける。2 周分に伸ばす、1 か所で切って固定する、回転を 2 周分の窓とみる、の 3 つの言い換えが共通の出発点になる。
- `signs`（phrase 5 つ。要点の「いつ使うか」と同じ）：N 個が円形に並び、N 番目と 1 番目も隣り合う／円環上の連続する区間の和・個数（端をまたぐ区間も含む）／円形に並ぶものを、隣どうしが違う色で塗る方法の数／列を何回回転させると、もう一方の列に一致するか／円周上に点が並び、時計回りに進む・点どうしを弦で結ぶ
- `sections`：properties・overview と行の節 16 個（見出しと title は同じ文字。カンマを含む title は引用符で囲んだ）

### 図 `docs/img/circular/unroll.svg`

- 400×392。上に位置 0〜5 の輪（時計回りに番号が増える）と、位置 4 から時計回りの 4 個（4・5・0・1）を太い枠と矢印の弧で示し、5 と 0 の間の切れ目を破線で描いた。下に、切れ目で切り開いて 2 周分にした列（添字 0〜11、中身は位置 0〜5 を 2 回）を置き、添字 4〜7 を区間 [4, 8) として示した。色だけでなく、太い枠・破線・ラベルでも区別した。背景は白、文字はテキスト、最小の文字は 12（360px 幅で 9.84px）
- 代替テキスト：位置 0〜5 の 6 個が時計回りの輪をなす。位置 4 から時計回りの 4 個（4・5・0・1）は、5 と 0 の間の切れ目をまたぐ。切れ目で切り開き、同じ 6 個をもう 1 周つなげた列では、この 4 個が添字 4〜7 の 1 本の区間になる

### 確かめたこと

- 行き先の節は、どれも実在の anchor で、相手のページの本文を読んで、行の節に書いた言い換え（式・条件・計算量）が相手の説明と食い違わないことを確かめた。行き先のページはすべて reviewed
- 代表の問題 19 問：`python3 tools/ap.py show` で実在と題名を確かめた（すべて OK）。どれも台帳で確認済みで、表に書いた行き先のページの囲みにあることを grep で確かめた（上の表の役割）
- 本文の数や式は、手元の総当たり（作業用フォルダの Python。コード片ではない）で確かめた：円環の塗り分けの式と漸化式（$N = 2$〜$6$、$K = 1$〜$4$）、区間の数 $N^2$・集合として $N(N-1)+1$（$N \le 8$）、円形の最大和を 1 個目を選ぶ／選ばないの 2 回の DP で求めた値と総当たりの一致（乱択 2000 回）、円順列 $(n-1)!$ と赤 2・青 2 の 2 通り、数珠の式の $n = 6$・$k = 4$ で 700、$K$ ずつ進むと $N/g$ 点を通って $N/g$ 回で戻ること、時計回りの距離の式と $M$ の倍数の組の数え方（2 通りの数え方と総当たりの一致）、先頭を末尾へ移したときの転倒数の変化 $N - 1 - 2x$、2 周分の列と反転の畳み込みで回転ごとの積の和が出ること、1 周以上配る操作を全体への加算と 2 つの区間に分けた結果と愚直な配り方の一致
- 確認問題の答え（#cut）に誤りがあったので直した（最初の版は「2 個目を選べないことは、どちらの回も遷移が守る」と書いていた。2 個目を選べないのは 1 個目を選ぶ回だけである）
- 作業用フォルダへの `uv run mkdocs build --strict -q -d <作業用フォルダ>/site`：終了コード 0。ビルドした HTML で、h2 の id が sections と一致し、表の 16 行すべての最初のセルが同じページの行の節（h2）へのリンクであることを確かめた。リンクの文字の中の数式（$M$・$K$・$N$）は arithmatex の span になる
- ローカルに出したビルドを、ヘッドレスの Chrome で幅 1100px と 390px で撮り、日本語のフォント（WSL の Windows のフォント）を足して目で確かめた。KaTeX・表・折りたたみ・図は崩れていない。390px では 4 列の表が横にスクロールする（ほかの題材別のページと同じ。#55 の範囲）
- `tools/render_svg.py circular` で図を 360px・720px の PNG にして目で確かめた

## 検査

- `python3 tools/check_pages.py --page circular`：エラー 0・警告 0
- `python3 tools/check_svg.py --page circular`：図 1 枚・警告 0・エラー 0
- `python3 tools/fix_problems.py --check --page circular`：直すべき行 0（問題の囲みはない）
- `npx textlint docs/patterns/circular.md`：エラー 0・警告 9。どれも規則の誤検出で、§13-8・§14-25 の範囲である
    - 半開区間の数式 `$[i, i + k)$`・`$[l, N)$`・`$A[k, N)$`・`$[x, y)$` の `[` が閉じていないとみなされる（no-unmatched-pair 4 件：68・146・200・236 行）。その後の「。」で文が切れなくなり、同じ行の sentence-length が出る（4 件：68・146・200・236 行）
    - 図の代替テキスト（72 行）の sentence-length 1 件
    - 最初の版で出た助詞の重なり・読点の数・長い文の警告（21 件）は、文を分けたり言い換えたりして消した
- `python3 tools/gen_site.py --check`（書かない）：生成物が 12 ファイル古い（nav.yml・docs/patterns/index.md・docs/lists/index.md・kind-prefix-sum.md・kind-counting.md・kind-guide.md・docs/llms.txt・docs/index/patterns.md・graph.json・reverse-index-signs.md の signs-phrase・term-index.md・how-to-use.md の版）。このうちの一部は #66 の担当の変更による。中身を見て、円環のページの行が意図どおり（ナビの「題材別」の最後、題材別の入口の 11 ページ目、signs の 5 行は「文字列・幾何・ゲーム・そのほか」の群、別名の 10 語が用語の索引）に入ることを確かめた。差分は作業用フォルダの gen_site_diff.txt
- check_snippets：コード片を書いていないので流していない

## 使った出典

- [Reputeless「tenkei_90 076.md」](https://github.com/Reputeless/tenkei_90/blob/main/076.md)：2 周分に伸ばした累積和と、始点を元の位置に限った二分探索（github.com）
- [drken「AtCoder ABC 307 E - Distinct Adjacent (1Q, 水色, 475 点)」](https://drken1215.hatenablog.com/entry/2024/06/10/024932)：両端をまとめて $N - 1$ 個の円環にする漸化式と、1 人目と同じ色かの DP。閉じた式はこの記事にはなく、counting-basics の導出で確かめた
- [drken「AtCoder ABC 367 D - Pedometer (1Q, 緑色, 400 点)」](https://drken1215.hatenablog.com/entry/2024/08/21/084614)：2 周分に伸ばし、添字の差を $N$ 未満に限って余りの一致する組を数える方針
- どれも付録 B のドメインで、新しいドメインは使っていない。題名は、同じ URL を引いているページ（prefix-sum・counting-basics・dp-state-design・prefix-sum-counting）と一字一句同じにした（§17-10）。文章は転載していない。atcoder.jp・codeforces.com は開いていない

## 提案（共有のファイル・生成物）

1. **gen_site の実行**：ナビ・題材別の入口（11 ページになる）・一覧・用語の索引・逆引き（signs）・llms.txt・graph.json を作り直す（メインのマージ時）
2. **guide/reverse-index-signs#by-topic の表に行を足す**（手書きの表）。例：「| 円環 | 区間が端をまたぐ、最後と最初が隣り合う数え上げ・DP、回転の一致、円周上の弦 | [円環](../patterns/circular.md#overview) |」。位置は「区間・連続部分列」の次か「操作列・クエリ」の次
3. **（任意）行き先のページから戻る道**：円環の節を持つページ（prefix-sum#circular・prefix-sum-counting#circular・difference-sequence#circular・counting-basics#coloring・dp-state-design#dp-cyclic・string-basics#rotation・z-algorithm#cyclic-shift・argument-sort#wrap-around・stack-techniques#chords・namori-graph）の related に `circular` を足すか、節の末尾に「円環の問われ方の一覧は[円環](../patterns/circular.md#overview)にある」の 1 文を足す。dp-state-design の括弧列の節が [括弧列](../patterns/bracket-sequence.md) へ戻る書き方と同じ
4. **（任意）gen_site.py の題材別の説明**（70 行目「括弧列・mex・順列・XOR・区間・グリッドなど」）に「円環」を足す
5. **（任意）用語集**：「巡回シフト｜cyclic-shift｜列の先頭の要素を末尾へ移す操作を何回か行ったもの。長さ N の列には N 通りあり、列を 2 つつないだ列の長さ N の窓として並ぶ。」。付録 A の正規形で、多くのページが使うが用語集にない。今回のページでは用語集へリンクしていない
6. 台帳・catalog・手引き・prh.yml は変えなくてよい（問題の囲みを置いていない。表記は付録 A のとおり）

## メインに判断してほしい点

- `order`：110（題材別の最後）にした。区間（10）のすぐ後に並べたいなら 15（10 刻みでなくなる）。どちらでもほかのページと重ならない
- catalog への登録：Issue #75 の「やること」に catalog・ナビへの登録がある。骨格以降は front matter が正で catalog は凍結なので、catalog には足していない（check_pages は catalog にない id でもエラーにしない）。catalog にも足すかを決めてほしい
- Issue #75 の閉じ方：「題材別の入口から by-topic の表へ」は別のグループ（入口の生成）の担当なので、このグループの pull request では `Refs #75` にし、入口の件が入った時点で閉じるのがよいと考える
- kind を [案内, 累積和・差分, 数え上げ] にした。行の数では文字列（回転）・幾何・グラフもあるが、3 つまでなので、行の多い 2 つを選んだ

## 使用量の目安

- 道具の呼び出し：約 80 回（読む・検査・ビルド・撮影を含む）。Web の取得：3 回（上の出典。atcoder.jp・codeforces.com は開いていない）
- 作業用のファイル：/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/7a638398-7759-4637-95c7-6739e8d52414/scratchpad/fix/patterns/circle-page/（sec.py＝節の抜き出し、gen_site_diff.txt、png/＝図の PNG、shots/＝ページの撮影、site/＝ビルド、fonts.conf）

## 検証の指摘への対応（担当 circle-page-fixup、2026-10-29）

- 元にした検証：[verify-circle-page.md](verify-circle-page.md)（必須 1・推奨 6）。すべて直した。ただし推奨 7 の見出し 1 つ（`#up-to-rotation`）は 63 字で、目安の 60 字を 3 字超えたまま残した（下の 7）
- 直したファイル：`docs/patterns/circular.md` だけ（270 行。直す前は 264 行）。図 `docs/img/circular/unroll.svg` は変えていない。front matter で変えたのは sections（見出しに合わせた title 5 つと、`up-to-rotation` の位置）だけで、`updated: 2026-10-29`・`stage: draft` はそのまま。anchor は 1 つも変えていない
- 表は 16 行から 18 行になった（偏角の行を 3 行に分けた）。行の anchor の並び・sections の 3 番目以降・本文の h2 の並びは、直した後も一致する（作業用フォルダの Python で比べた）

### 1. 必須：偏角の行と節 `#angles`（直した）

- 案 A（行を分ける）にした。Issue に挙がった「偏角の 2 周分の尺取り（#wrap-around）」を表に残しつつ、行き先の節と代表の問題をそろえられるからである。3 行とも同じ節 `#angles` を指す（#66 の形。2 行以上が 1 つの節を指すのは、divisors-and-multiples などと同じ）
- 123〜125 行（表）：
    - 「[方向が範囲に入る点の数](#angles)｜偏角の順の累積和、境目をまたぐなら 2 つに分ける｜偏角ソート#range-count｜ABC442 E」
    - 「[原点を含む三角形の数・各点から半周未満にある点の数](#angles)｜偏角の列を 2 周分にして尺取り｜偏角ソート#wrap-around｜—」（argument-sort に #wrap-around で解く問題はない）
    - 「[ベクトルをいくつか選んで和の長さを最大にする](#angles)｜2 周分の列の連続する範囲をすべて試す｜偏角ソート#angular-intervals｜ABC139 F」
- 227 行（見出し）と 36 行（title）：「方向が範囲に入る点・半周未満の点・ベクトルの和の長さの最大 → 偏角の列を 2 周分にする（argument-sort）」（60 字）。3 つとも 2 周分の列で書ける（#range-count も 2 周分の累積和の書き方を挙げている）ので、手法の側をそこにそろえた。「半周以内」は行き先の「$\pi$ 未満」に合わせて「半周未満」にした
- 229〜233 行（本文）：前置きの段落に、偏角の比較（#half-plane-compare）へのリンクを前へ移した。その後を 3 つの箇条書きにし、表の 3 行と同じ順に置いた
    - 方向が範囲に入る点の数：元の 1 段落目と同じ（#range-count）
    - 各点から半周未満にある点の数：元の 2 段落目（#wrap-around）に、行き先の節にある使い道の 1 文を足した。どの 2 点も原点と一直線上にないなら、原点を含む三角形の数は $\binom{N}{3}$ から $\binom{k_i}{2}$ の和を引いた値になる
    - 和の長さが最大になるベクトルの選び方：新しく書いた（#angular-intervals）。最適な選び方は原点を通る直線の片側（直線上を含む）に入るベクトルすべてで、偏角の列の連続した範囲になる。2 周分の列の長さ $N$ 以下の範囲をすべて試し、累積和で $O(N^2)$。長さ 0 のベクトルは先に除く
- 代表の問題は行き先のページに実在する label を文字だけで書いた（ABC442 E は argument-sort の例題、ABC139 F は練習）

### 2. 推奨：回転で同一視する行と ABC428 G（直した）

- 225 行：`#up-to-rotation` の末尾に 1 段落を足した。最短周期がちょうど $d$ の列は回すと $d$ 種類になるので、最短周期ごとに数えて $d$ で割って足す方法がある。列の長さが決まっていないときや積・和の条件があるときは、こちらの方が立式しやすい（burnside-lemma#by-period）。最後に「[Burnside の補題の例題 ABC428 G](../comb/burnside-lemma.md#abc428_g) は、この形で解ける」と書いた（本文から別のページの問題に触れるときは、その例題の見出しへリンクする。§2.5）
- 表の行の手法・行き先（#necklace）は変えていない。検証のとおり、Burnside の補題で書いても同じ式になり、誤りではないからである

### 3. 推奨：すべての回転の行と ABC291 G（直した）

- 116 行（表）：問われ方を「すべての回転についての転倒数・積や OR の和」にし、使う手法に「（OR などは bit ごとに分ける）」を足した。節の本文（217 行）は前から OR の和と #split-by-bit を説明しているので、変えていない
- 212 行（見出し）と 34 行（title）：「すべての回転についての値 → 差分の更新・畳み込み（inversion-number, convolution-ntt）」（66 字 → 60 字。下の 7 も兼ねる）。転倒数・積・OR をまとめて「値」とした。節の 1 文目「$N$ 通りの回転のすべてについて値を答えるとき」と同じ言い方である

### 4. 推奨：2 つ目の群の名前と説明（直した）

- 検証の 2 つの案を両方使った
    - `#up-to-rotation` の行を「回転（巡回シフト）」の群の最後へ移した（117 行）。回転で同一視して数える話で、最後と最初の条件の話ではないからである。#66 の担当（pattern-rows）が本文の位置を表の順に合わせていたのにならい、本文の節（219〜225 行）も `#all-rotations` の後へ移し、sections の並び（35 行）も変えた。回転の群の説明（110 行）は「比べる・まとめて調べる・同じとみなして数える」にした
    - 残った 4 行（塗り分け・1 か所で切る DP・円環状の依存・添字のずらし）に合うように、群の名前と説明を変えた（101 行）：「**最後と最初がつながる数え上げ・DP・期待値**：最後の 1 個が最初の 1 個とつながるので、隣どうしの条件や状態の遷移が 1 周して戻ってくる。」。`#shift` は、全体が 1 つずつ進む遷移が位置 $N-1$ から 0 へ戻る点で、この説明に入る
- 節の中にほかの節の位置を前提にした言い回し（「上の節」など）はなく、移しても文は変えずに済んだ

### 5. 推奨：`#count-pairs` の検索の回数（直した）

- 142 行：「…連想配列に記録する。添字ごとに条件 1 つにつき 1 回、合わせて 2 回検索すれば数えられる」にした（行き先 prefix-sum-counting#circular の擬似コードと同じく、大きい方の添字 1 つにつき 2 回）

### 6. 推奨：確認問題「円環上の区間の数」（直した）

- 83 行：「中身（含む位置の集合）が同じものを 1 つと数えると」にした（位置は、図と本文で円環上の番号 0〜$N-1$ を指し、2 周分の列の番号は添字と呼んでいるので、取り違えない）
- 86 行（答え）：「長さ $N$ 未満の区間は、始点か長さが違えば位置の集合も違う」の 1 文を足し、$N(N-1)+1$ の理由が答えの中で閉じるようにした。「集合として数える」は「位置の集合として数える」にした

### 7. 任意：見出しの長さ（4 つのうち 3 つを 60 字以内にした）

| 節 | 直す前 | 直した後 | 字数 |
|---|---|---|---|
| range-add | …→ 端で 2 つの区間に分ける（…） | 更新のある円環の区間加算 → 端で 2 つに分ける（fenwick-tree, lazy-segment-tree） | 61 → 58 |
| cyclic-dependency | 状態が円環に依存し合う確率・期待値 → 1 つを未知数にして 1 周させる（…） | 円環状に依存し合う確率・期待値 → 1 つを未知数にして解く（expectation-linear-equations） | 67 → 60 |
| all-rotations | すべての回転についての転倒数・積の和 → …（…） | すべての回転についての値 → 差分の更新・畳み込み（inversion-number, convolution-ntt） | 66 → 60 |
| up-to-rotation | 回転して重なるものを同じとみなす数 → 円順列・Burnside の補題（…） | 回転で同一視して数える → 円順列・Burnside の補題（counting-basics, burnside-lemma） | 69 → 63 |

- 見出し（146・184・212・219 行）と sections の title（26・30・34・35 行）を同時に直した。anchor と表の問われ方の文字は変えていない
- `#up-to-rotation` は 63 字で残した。行き先の id 2 つの括弧だけで 33 字あり、60 字に収めるには「円順列」「の補題」を削るか、問われ方を「回転で同一視」まで縮めるしかなく、どれも分かりにくくなる。目安の範囲として、ほかの題材別のページ（61〜66 字の見出しが 6 ページに 7 つある）と同じ扱いにした
- 新しい `#angles` の見出しは 60 字である

### 確かめたこと

- `python3 tools/check_pages.py --page circular`：エラー 0・警告 0
- `python3 tools/check_svg.py --page circular`：図 1 枚・警告 0・エラー 0（図は変えていない）
- `python3 tools/fix_problems.py --check --page circular`：直すべき行 0
- `npx textlint docs/patterns/circular.md`：エラー 0・警告 9。直す前と同じ 9 件で、行がずれただけである（半開区間の `[` の no-unmatched-pair 4 件と続く sentence-length 4 件：68・148・196・242 行、図の代替テキストの sentence-length 1 件：72 行）。折りたたみの中の確認問題の答え（86 行）は検査されないので、文の長さと助詞を自分で読んで確かめた
- `python3 tools/ap.py show`：触った行の 5 問がどれも OK（abc442_e「E. Laser Takahashi」1355、abc139_f「F. Engines」2034、abc428_g「G. Necklace」2472、abc291_g「G. OR Sum」2176、abc190_f「F. Shift and Inversions」1321）。どれも行き先のページの囲みに同じ label で載る（ABC442 E・ABC139 F は argument-sort、ABC428 G は burnside-lemma の例題、ABC291 G は convolution-ntt の練習、ABC190 F は inversion-number の例題）
- 行き先の節を読んで、足した文と食い違わないことを確かめた：argument-sort の #range-count・#wrap-around（三角形の数え上げの段落を含む）・#angular-intervals・#half-plane-compare、burnside-lemma の #necklace・#by-period・#abc428_g、convolution-ntt の #reverse・#split-by-bit と練習の方針、prefix-sum-counting#circular
- 足した式と言い換えを総当たりで確かめた（作業用フォルダの brute.py。すべて OK）：原点を含む三角形の数 $= \binom{N}{3} - \sum \binom{k_i}{2}$（2 周分の尺取りで $k_i$ を求め、乱択 3000 回）、和の長さの最大が 2 周分の連続する範囲の最大と一致すること（$N \le 7$、長さ 0 のベクトルを含む乱択 3000 回）、位置の集合の数 $N(N-1)+1$（$N \le 9$。値の集合なら減る例も）、最短周期で分けて割る和と回転の軌道の数の一致（$n \le 8$、$k \le 3$）、円環上の組を添字ごとに 2 回の検索で数える方法と総当たりの一致
- 作業用フォルダへの `uv run mkdocs build -q -d <作業用フォルダ>/site`：終了コード 0。ビルドした HTML で、h2 の id が sections と同じ並びの 20 個（中身の節 18 と落とし穴・参考）で、表は 18 行、最初のセルはどれも同じページの節へのリンクだった。偏角の 3 行の行き先は #range-count・#wrap-around・#angular-intervals
- ヘッドレスの Chrome（chrome-headless-shell）で JS を動かした後の DOM を見た：KaTeX の数式 265 個（直す前の 255 個に、足した式の分が増えた）がすべて描かれ、`.katex-error` は 0 件
- `python3 tools/gen_site.py --check`（書かない）：古い生成物は直す前と同じ 12 ファイルで、増えていない

### 残った点・提案（メインへ）

1. **related の順**：行を移したので、表の行の順と related の順（counting-basics・burnside-lemma の位置）が少しずれた。front matter のうち頼まれていない項目なので変えていない。検証の「メインへ 4」（近いものから順に並べるか）と合わせて決めてほしい
2. **by-topic の表の行**（最初の報告の提案 2）：例の文「区間が端をまたぐ、最後と最初が隣り合う数え上げ・DP、回転の一致、円周上の弦」は、直した後の表とも合うので、そのままでよい
3. 生成物（gen_site）と Issue #75 の閉じ方は、最初の報告と検証の「メインへ」のとおりである

### 作業用のファイル

/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/7a638398-7759-4637-95c7-6739e8d52414/scratchpad/fix/circle-page-fixup/ に置いた（brute.py＝足した式の総当たり、site/＝ビルド、dom.html＝JS を動かした後の DOM）。
