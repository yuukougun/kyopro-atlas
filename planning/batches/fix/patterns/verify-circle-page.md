# verify-circle-page の報告（バッチ patterns）

- 検証した直し：担当 circle-page の #75（題材別「円環」のページ。報告は [circle-page.md](circle-page.md)）
- 作業ツリー：/home/yuuki/projects/kyopro2/kyopro-atlas-wt/patterns（ブランチ feat/patterns、commit 前）。ファイルは直していない（書いたのはこの報告だけ）。git は読むだけで、Issue にはコメント・編集・クローズをしていない
- 見たもの：docs/patterns/circular.md（新規・264 行）、docs/img/circular/unroll.svg（新規）、circle-page.md。行き先のページの節は 21 節すべてと、本文だけのリンク先 11 か所を読んだ

## 結果

| Issue | 判定 | 直しが要る点 |
|---|---|---|
| #75 題材別に「円環」のページを足す（このグループの分：ページ） | 直しが要る | 必須 1・推奨 6 |

完了の条件のうち「『円環』で引ける題材別のページがあり、表の各行が手法のページの節へリンクしている」は満たしている（16 行のページの列のリンクはどれも `#anchor` 付きで、すべて実在する）。ただし、表の 1 行（偏角）で、使う手法・行き先の節と代表の問題が食い違っている（下の 1）。「題材別の入口から by-topic の表へ」は別のグループの担当で、入口（docs/patterns/index.md）にはまだ案内がない（作業ツリーにも origin/main にもない）。

## 直しが要る点

### 必須

1. **表の偏角の行と節 `#angles`：使う手法・行き先の節と、代表の問題が合わない**（circular.md 123 行、見出し 223 行と sections の title 36 行、本文 225〜227 行）
    - 行は「方向が範囲に入る点・半周以内の点｜偏角の列を 2 周分にして尺取り｜偏角ソート#wrap-around｜ABC442 E、ABC139 F」である
    - 代表の 2 問は、どちらも #wrap-around の尺取りでは解かない。ABC442 E は argument-sort の例題で、方針は argument-sort#range-count（偏角順に並べ、`lower_bound`・`upper_bound` と累積和。境目をまたぐなら $[l, N)$ と $[0, r)$ を足す。台帳の approach も「整数の偏角ソートと累積和」）。ABC139 F は練習で、方針は #angular-intervals（2 周分の列の連続する範囲をすべて試す。$O(N^2)$。台帳の approach も「節 angular-intervals」）。argument-sort に #wrap-around の尺取りを使う問題はない
    - また、問われ方の前半「方向が範囲に入る点」の手法は尺取りではない。節の本文（225 行）は #range-count へ正しく案内しているので、食い違いは表の行（と見出し）だけにある。尺取りが要るのは後半の「各点から半周以内の点」（#wrap-around）である
    - 直し方の案（どちらか）
        - **A：行を分ける**（#66 の形では、2〜3 行が同じ節 `#angles` を指してよい）。「[方向が範囲に入る点の数](#angles)｜偏角ソートと累積和（境目をまたぐなら 2 つに分ける・2 周分にする）｜[偏角ソート](../geometry/argument-sort.md#range-count)｜ABC442 E」と「[各点から半周以内の点](#angles)｜偏角の列を 2 周分にして尺取り｜[偏角ソート](../geometry/argument-sort.md#wrap-around)｜—」。ABC139 F を残すなら、3 行目「[和の長さが最大になるベクトルの選び方](#angles)｜2 周分の列の連続する範囲を試す｜[偏角ソート](../geometry/argument-sort.md#angular-intervals)｜ABC139 F」を足し、節に #angular-intervals への 1 文を足す（最適な選び方は半平面に入るベクトル＝偏角の列の連続する範囲になる）
        - **B：1 行のまま直す**。使う手法を「偏角の列を 2 周分にする（累積和・尺取り）」、ページを #range-count（本文が #wrap-around へ案内する）、代表の問題を ABC442 E だけにする。見出しと sections の title も「→ 偏角の列を 2 周分にする（argument-sort）」のように合わせる（anchor は変えない）

### 推奨

2. **回転で同一視する行（107 行）と節 `#up-to-rotation`（182〜186 行）：代表の ABC428 G の方針の節へ案内がない**。ABC428 G は burnside-lemma の例題だが、その方針は #by-period（最短周期で分類して割る）で、表の行き先 #necklace ではない（burnside-lemma 113 行「例題の ABC428 G はこの形で解ける」）。Burnside で書いても同じ式になるので行の手法は誤りではない。直し方：186 行の後に「列の長さが決まっていない・積の条件があるなど、回転ごとに数えにくいときは、最短周期で分類して割る（[最短周期で分類して割る方法](../comb/burnside-lemma.md#by-period)）。」の 1 文を足す
3. **すべての回転の行（117 行）：代表の ABC291 G は「OR の和」で、問われ方の「積の和」に入らない**。convolution-ntt の練習の方針は #split-by-bit（bit ごとに分けて畳み込む）を指す。節の 221 行は OR の和と #split-by-bit を説明しているので、表だけの問題である。直し方：問われ方を「すべての回転についての転倒数・積や OR の和」にする（使う手法に「bit ごとに分ける」を足してもよい）
4. **2 つ目の群の名前と説明（101 行）が、群の行の一部に合わない**。「最後と最初の両方に条件がかかる：一列なら積の法則や左からの DP で済むが、最後の 1 個に最初との条件が加わる」に対して、`#up-to-rotation`（回転で同一視して数える）と `#shift`（全体が 1 つずつ回る遷移）は「最後と最初の条件」の話ではない。直し方：群を「数え上げ・DP・確率で、最後と最初がつながる」のように広げて説明も合わせるか、`#up-to-rotation` を「回転（巡回シフト）」の群（説明に「比べる・数える」がある）へ移す
5. **`#count-pairs` 140 行「1 回の検索ずつで数えられる」**：添字ごとに条件が 2 つあり、検索は 2 回である（行き先 prefix-sum-counting#circular も「2 回検索すればよい」）。直し方：「条件ごとに 1 回ずつ、合わせて 2 回の検索で数えられる」
6. **確認問題「円環上の区間の数」（83 行）の「中身（要素の集合）」**：値の等しい要素があると、値の集合と読めて答えが変わる。答えの $N(N-1)+1$ は位置の集合の数である。直し方：「中身（位置の集合）」にする
7. **（任意）見出しの長さ**：手引き §14-12 の目安 60 字を超える見出しが 4 つある（`#up-to-rotation` 69 字・`#cyclic-dependency` 67 字・`#all-rotations` 66 字・`#range-add` 61 字。sections の 26・30・31・35 行と、見出しの 144・182・188・216 行）。ほかの題材別のページにも 61〜66 字があるので必須ではない。縮めるなら見出しと title を同時に直す（anchor は変えない）

## 確かめたこと

### 1. 表の各行と行き先の節・言い換え（Markdown とビルドした HTML）

- 表は 4 つの群・4 列・16 行で、16 行の「よく出る問われ方」のセルは、どれも同じページの行の節へのリンク `[文字](#anchor)` だけでできている。ビルドした HTML でも 16 行すべてで、最初のセルはセル全体を包む `<a href="#…">` 1 つで、href はそのページの h2 の id だった。行の anchor の並びは sections の 3 番目以降と一致する（#66 と同じ形。「同上」はなく、ページの列にこのページの節へのリンクもない）
- ページの列のリンクは 21 本で、行き先はどれも reviewed のページの実在する anchor である。行き先の 21 節を読み、行の節に書いた言い換え・式・条件・計算量と食い違わないことを確かめた（prefix-sum#circular・prefix-sum-counting#circular・fenwick-tree#variants・lazy-segment-tree#dual-segment-tree・difference-sequence#circular・counting-basics#coloring・#permutations・dp-state-design#dp-cyclic・burnside-lemma#necklace・expectation-linear-equations#cycle・inline-dp#global-shift・string-basics#rotation・z-algorithm#cyclic-shift・suffix-array#rotations・inversion-number#incremental・convolution-ntt#reverse・argument-sort#wrap-around・stack-techniques#chords・gcd-properties#step-mod・ext-gcd#applications・namori-graph#hanging-trees）。食い違いは上の 1〜3 だけである
- 本文だけのリンク先 11 か所（prefix-sum#with-binary-search・stars-and-bars#gaps の確認問題・convolution-ntt#split-by-bit・argument-sort#range-count・#half-plane-compare・merge-sort-tree#query・hashing-for-sets#with-fenwick・dp-segment-tree#challenge・graph/functional-graph・integer-division#cpp-vs-math・glossary#half-open-interval）もすべて実在し、書いた内容と合う（dp-segment-tree の $[y, x + 2N)$ は本文の $P$ 個の点で $[y, x + P)$ と同じ）
- Issue に挙げた 7 つの手法（累積和の 2 周分・差分列・塗り分け・1 か所で切る DP・回転の一致・偏角の 2 周分の尺取り・なもりグラフ）は、どれも行になっている

### 2. 本文の式・例（作業用フォルダの Python で総当たり。scripts/brute.py。すべて一致）

- 円環の塗り分け：$C_N = (K-1)^N + (-1)^N (K-1)$ と漸化式 $C_N = K(K-1)^{N-1} - C_{N-1}$（$N = 2$〜$7$、$K = 1$〜$5$）。$K = N = 3$ で 6
- 区間の数：$N^2$ と、位置の集合として $N(N-1)+1$（$N \le 8$）
- 隣り合わないように選ぶ円形の最大和：1 個目を選ぶ回で「最後を選んだ状態」を外し、選ばない回は何も外さない 2 回の DP と総当たり（乱択 2000 回）。円形の席から隣り合わない $K$ 席：$\binom{N-K}{K} + \binom{N-K-1}{K-1}$
- 円順列 $(n-1)!$、赤 2・青 2 の輪が 2 通り、数珠の式（$n \le 7$、$k \le 3$ で軌道の数と一致、$n = 6$、$k = 4$ で 700）
- $K$ ずつ進む：$N/g$ 点を通り $N/g$ 回で戻る、通る点は出発点と $\bmod g$ で合同な点、最小の回数は $Kx \equiv T - S \pmod{N}$ の最小の非負解（$N < 30$）
- 先頭を末尾へ移したときの転倒数の変化 $N - 1 - 2x$、2 周分の $A$ と反転した $B$ の畳み込みの第 $p + N - 1$ 項が $\sum_i A_{(i+p) \bmod N} B_i$
- 時計回りの距離の式（$s \le t$ と $s > t$）、$M$ の倍数の組の数え方（大きい添字で 2 回の検索、2 周分で長さ $1$〜$N-1$）
- 1 周以上配る操作（全体に $\lfloor x/N \rfloor$、残りを $[l, N)$ と $[0, l+k-N)$ に分ける）、$1, 2, \dots, N$ を一斉に取り除く操作の差分の変化（$N-1$ か所で $-1$、切れ目の 1 か所で $+(N-1)$。和は $N(N+1)/2$ 減る）
- 円環状の 1 次の依存（$x$ の係数が $d_0 \cdots d_{N-1}$）、添字のずらし $a[(v - t) \bmod N]$、回転 $= (A+A)[k, k+N)$、$S + S$ の SA で開始位置 $N$ 未満の最初の接尾辞が最小の回転、`aaaa` の出現 5 個と回転 4 通り
- 弦：どこで切っても交差の判定が同じ、スタックの判定、両端に同じ乱数を XOR したときの区間の XOR が 0 と「区間をまたぐ弦がない」の一致
- 落とし穴の C++ の `%`（左が負なら 0 以下）は integer-division#cpp-vs-math と一致する

### 3. 代表の問題（`python3 tools/ap.py show`）

- 19 問すべて OK（題名・difficulty：典型90 076 Cake Cut（★3）diff なし、ABC367 D 1037、ABC340 E 1157、AGC010 B 1892、ABC307 E 1240、ABC428 G 2472、ABC333 F 1770、ABC372 F 1722、ABC286 C 565、ABC430 E 1109、ABC272 F 2238、ABC190 F 1321、ABC291 G 2176、ABC442 E 1355、ABC139 F 2034、ABC338 E 1220、ABC186 E 1461、ABC210 E 1618、ABC266 F 1525）
- どれも台帳で確認済みで、表に書いた行き先のページの囲みに同じ label で載っている（行の役割は担当の報告の表のとおり）。2 問の行は易しい順になっている。label の書き方（「典型90 076」「AGC010 B」）はほかの題材別のページと同じ
- ページに問題の囲み（kp-problems）はなく、atcoder.jp・codeforces.com へのリンクもない。台帳（data/problems.yaml）は変わっていない（git status で未変更）

### 4. 構成・front matter

- 構成は手引き §4 の pattern と見本 bracket-sequence（#66 の後）のとおり：要点 → 別名の行 → 導入 → 題材の性質 → 問われ方と手法の一覧（sections に置いた中身の節）→ 行ごとの節 → 落とし穴 → 参考。一覧の節の最初の段落は #66 でそろえた文と同じで、代表の問題の案内（行き先のページにある）も §16-7 に合う。問題 0 問は §10 の patterns の目安（例題 0〜1・練習 0〜3）に入る
- 要点は summary・signs・prerequisites と一致する（「何のページか」＝summary、「いつ使うか」＝signs の 5 つ、前提なし＝`prerequisites: []`）。別名の行に aliases の 10 語がそろう。見出しと sections の title は 18 節すべて一致し、並びも本文と同じ
- front matter：項目と並びはほかの題材別の 10 ページと同じ（chapter・frequency なし）。schema/page.schema.json に合う（level・complexity は null、kind は語彙の 3 つで先頭が「案内」、summary は 2 文・102 字、title にカンマのある sections は引用符つき）。order 110 は重ならない。stage draft・updated 2026-10-29（今日）。aliases の 10 語は、ほかのページの題名・別名と完全には重ならない（「円環 DP」「環状 DP」は dp-state-design の別名で、部分一致だけ）
- 表記：だ・である調。禁止の表記（全て・出来る・最短経路など）はない。半開区間の用語集へのリンクは最初の 1 回だけ

### 5. 図 docs/img/circular/unroll.svg

- `tools/render_svg.py circular`（360px・720px、地の色をダークの #1e2129 にした 360px も）で目で確かめた。輪の 0〜5 は時計回り、太い枠の 4・5・0・1 と時計回りの矢印の弧、5 と 0 の間の切れ目（破線とラベル）、2 周分の列の添字 4〜7 の太い枠と区間 [4, 8) の括弧が、代替テキストと本文（74 行）に合う。弧は 4 の手前から 1 の先まで、切れ目の線はちょうど 5 と 0 の中間（240 度）にある
- viewBox 400×392 と width・height の比が同じ。白い背景が viewBox 全体を覆う。最小の文字 12 は本文の幅 328px で 9.84px。色だけでなく枠の太さ・破線・ラベルでも区別している。文字はテキストのまま（sans-serif）
- `python3 tools/check_svg.py --page circular`：図 1 枚・警告 0・エラー 0（作業ツリーと origin/main の両方の版で）

### 6. 検査（書き換えない検査）

- `python3 tools/check_pages.py --page circular`：エラー 0・警告 0。全ページ（354）でもエラー 0・警告 0
- origin/main の check_pages.py・check_svg.py（#50・#51・#61 の静的な検査を足した版。作業用フォルダに `git archive origin/main` で出し、circular.md と図を入れた）でも、エラー 0・警告 0
- `python3 tools/fix_problems.py --check --page circular`：直すべき行 0
- `npx textlint docs/patterns/circular.md`：エラー 0・警告 9。担当の報告のとおり、数式の中の半開区間の `[` による no-unmatched-pair 4 件と、それに続く sentence-length 4 件、図の代替テキストの sentence-length 1 件である（§13-8・§14-25 の範囲）。リンクの URL を除いて自分で数えた文の長さは、どれも 120 字以下だった
- 行末の空白・タブはなく、どちらのファイルも改行で終わる
- check_snippets・viz の試験：コード片・動く図がないので流していない
- `python3 tools/gen_site.py --check`：生成物が 12 ファイル古い（担当の報告のとおり。メインが流す）

### 7. 表示（作業用フォルダへのビルドとヘッドレスの Chrome、幅 390px、ライトとダーク）

- 作業ツリーを `uv run mkdocs build -d <作業用フォルダ>/site` でビルドした。警告は nav に circular.md がないことの 1 件だけ（gen_site を流す前なので当然）
- `python3 -m http.server`（ポート 43817。使い終えて止めた）で配り、`http://127.0.0.1:43817/site/patterns/circular/` を開いた。JS を動かした後の DOM で、KaTeX の数式 255 個がすべて描かれ、.katex-error は 0 件だった。半開区間の数式の後ろにあるリンク（146・200・236 行）も `<a>` になっている
- 390px のライトとダークで全体を撮って見た。要点・図・4 つの表・節の数式・落とし穴・参考は崩れていない。図は白い背景のまま、ダークでも読める。4 列の表は 4 列目（代表の問題）が画面の外にはみ出して横にスクロールする（ほかの題材別のページと同じ。#55 の範囲）
- 合併後の姿も見た：origin/main の写しに circular を入れて gen_site.py を流すと、nav.yml（題材別の最後）・patterns/index.md（11 ページ目）・reverse-index-signs の signs 5 行・index/patterns.md・term-index ほか計 12 ファイルが変わり、`mkdocs build --strict` は警告なしで通った。main の新しいテンプレートでは、ページ末尾に「関連」20 件（レベルの印つき）と「段階 下書き・更新日 2026-10-29」が出て、390px のダークでも読める

### 8. 出典

- 3 件とも付録 B のドメイン（github.com・drken1215.hatenablog.com）で、取得でき（HTTP 200）、題名は記事の h1（Reputeless は同じ URL を引く prefix-sum と同じ題名）と一致する。check_pages の「同じ URL の題名」の警告もない
- 中身も合う：ABC307 E の記事に「1 人目と同じか」の DP（解法 1）と、両端をまとめて $N - 1$ 頂点に帰着する式（解法 2）がある。ABC367 D の記事は 2 周させて差が $N$ 未満の組を数える方針、Reputeless の 076 は 2 周分の累積和と始点ごとの二分探索である。本文の文は記事の言い回しと違い、転載はない

## メインへ（担当の直しとは別）

1. **生成物**：gen_site.py で 12 ファイルを作り直す（上の 7 のとおり、origin/main の写しでは strict のビルドまで通った）
2. **担当が判断を求めた点**：order 110 はほかと重ならず、題材別の最後に並ぶので、そのままでよいと考える。catalog は凍結（CLAUDE.md・骨格以降は front matter が正）なので、足さなくても検査は通る。Issue #75 は入口の件（patterns/index.md から reverse-index-signs#by-topic への案内）が入るまで `Refs #75` がよい
3. **by-topic の表**：担当の提案 2 の行（円環 → circular#overview）を足すと、題材別の入口と逆引きの両方から引ける。上の 1 で表の行を直したら、問われ方の例の文もそれに合わせる
4. **related の順**（origin/main の手引き §2.1「近いものから順に書く。20 件まで」）：今は表の行の順で、ちょうど 20 件である。3 つの言い換えの持ち主（prefix-sum・dp-state-design・string-basics）が前にあると「関連」で見つけやすいが、今の順でも誤りではない
5. **作業ツリーは origin/main より 19 commit 遅れている**：新しい 2 ファイルは main と重ならない。マージの後に check_pages・check_svg を流し直す（main の版でも通ることは確かめた）

## 作業用のファイル

/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/7a638398-7759-4637-95c7-6739e8d52414/scratchpad/fix/verify-circle-page/ に置いた。

- sec.py：ページの節を anchor で取り出す
- scripts/brute.py：本文の式・例の総当たり（「ALL OK」）
- png/・png-dark/：図の PNG（360px・720px、ダークの地の色）
- site/：作業ツリーのビルド。site-main/・main-copy/：origin/main の写しに circular を入れ、gen_site を流したもののビルド
- shots/：390px のライト・ダークの全体と切り出し（light-full-*.png・dark-full-*.png・main-*-bottom.png）
- dom/：JS を動かした後の DOM（KaTeX のエラーの数え上げ）
- refs/：出典の取得結果
- fonts.conf：日本語のフォント
