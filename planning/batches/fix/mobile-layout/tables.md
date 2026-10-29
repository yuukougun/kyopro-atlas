# tables の報告（#55 の表の部分：狭い画面の表と、はみ出す表・数式の手がかり）

担当は #55 のうち表の部分と、はみ出す表・別行の数式に出す「続きがある」手がかりである。`\text` の文を数式の外に出す直し（display-math の担当）と、手引き §8 の改め（メイン）は含まない。

- 直したファイル：`overrides/assets/css/kp.css`（末尾に追記）と、表を組み直した 9 ページ（下の表）。`overrides/assets/js/katex-init.js` は変えていない（理由は「katex-init.js を変えなかった理由」）
- 結果：390px で、対象の 9 ページの表 26 個はどれも横にはみ出さない（直す前は 18 個がはみ出し、そのうち 17 個で行き先のリンクか要の値の列が画面の端で切れていた）。サイト全体では、390px ではみ出す表が 157 個（102 ページ）から 3 個（3 ページ）に減り、最後の列がまるごと画面の外にある表は 28 個から 0 個になった。はみ出す表と別行の数式には、送れる側の端に影が出る
- 作業用フォルダは `/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/7a638398-7759-4637-95c7-6739e8d52414/scratchpad/fix/mobile-layout/tables`（以下 `<W>`）。直す前のビルドは `<W>/site-before`、直した後は `<W>/site`、画像は `<W>/shots/`、測った結果は `<W>/*.json`、使ったスクリプトは `<W>/*.mjs`・`<W>/tabletool.py`・`<W>/summarize.py`
- ビルドは `.venv/bin/mkdocs build --strict -d <W>/site`（警告 0・終了コード 0）。http で配ったもの（`python3 -m http.server`、127.0.0.1 の 8761＝前・8762＝後）を、ヘッドレスの Chrome 146（chrome-headless-shell）を CDP で動かして測り、撮った

## #55 スマホの幅で横にはみ出す表と数式（表の部分は完了。Issue 全体は一部）

### 直したファイルと行

| ファイル | 行 | 内容 |
| --- | --- | --- |
| `overrides/assets/css/kp.css` | 640–669（追記） | 狭い画面の表の規則・囲みの中の数式の左右の余白・はみ出しの影（下の「CSS の中身」） |
| `docs/dp/dp-speedup-overview.md` | 45–50・91–109・121–127・139–144 | 4 つの表で「道具」と「ページ」の列を「道具 → ページ」の 1 列にまとめた（4 列 → 3 列） |
| `docs/graph/graph-modeling.md` | 23・93–102・118–125 | 制約の表は「判定する性質（道具）」と「ページ」、縮約の表は「まとめた後の形・使い方」と「ページ」を 1 列にまとめた（4 列 → 3 列）。`updated` を 2026-10-29 に |
| `docs/basics/complexity-estimation.md` | 57–66 | 列の順を「制約の目安・許される計算量・疑う手法・演算回数の目安」に入れ替えた（節の題「制約 → 許される計算量 → 疑う手法」と、早見表 guide/cheatsheet の 3 列の順にそろう） |
| `docs/basics/two-pointers.md` | 56–61 | 2 つの型の表の縦横を入れ替えた（2 行 × 5 列 → 4 行 × 3 列。列が 2 つの型） |
| `docs/dp/bit-dp.md` | 137–143 | 計算量の表の縦横を入れ替えた（2 行 × 6 列 → 5 行 × 3 列。$N = 17$・$N = 20$ の値が行になる） |
| `docs/ds/lazy-segment-tree.md` | 141–145 | 区間和の表の `composition(f, g)` と `id()` を、すぐ上の標準の型の表と同じ「`composition(f, g)` / `id()`」の 1 列にまとめた（4 列 → 3 列） |
| `docs/ds/lazy-segment-tree-patterns.md` | 78–92 | 型の表の「やりたいこと」と「$S$ と `op`」を「やりたいこと：$S$ と `op`」の 1 列にまとめた（4 列 → 3 列。`composition` と `id` の列はそのまま残る） |
| `docs/ds/segment-tree-monoids.md` | 99–110 | 型の表の「区間の何を求めるか」と「載せる要約」を「区間の何を求めるか：載せる要約」の 1 列にまとめた（4 列 → 3 列。単位元の列はそのまま残る） |
| `docs/ds/segment-tree-binary-search.md` | 135–142 | 条件の書き方の表の「$f$」と「呼び方」を、同じ表の「載せるもの / 単位元」と同じ形の「$f$ / 呼び方」の 1 列にまとめた（4 列 → 3 列） |

front matter は graph-modeling の `updated` だけを直した（ほかの 8 ページは前から 2026-10-29）。`stage` は変えていない。

### CSS の中身（kp.css 640–669）

1. **狭い画面の表**（`@media screen and (max-width: 44.984375em)`。Material の狭い画面の境目と同じ）
   - `.md-typeset table:not([class]) th { min-width: 0; }`：Material が見出しのセルに付ける `min-width: 5rem`（100px）を外す。直す前は 4 列の表が中身によらず 434px になっていた（4 × 100px と枠の余白）
   - `th`・`td` の `padding` を Material の `0.9375em 1.25em` から `0.75em 0.6em` に詰める
   - 詳細度は Material の規則（`.md-typeset table:not([class]) th`）と同じで、後に読む kp.css が勝つ
2. **囲みの中の別行の数式**（同じ media の中）：`.md-typeset .admonition div.arithmatex`・`.md-typeset details div.arithmatex` の左右の margin を -0.6rem にする。Material は狭い画面で別行の数式に `margin: 0 -.8rem` を付けるが、囲みの余白は 0.6rem なので、数式の枠が囲みの枠線に 3px 重なり、外へ 2px 出ていた。下の影の覆い（背景の色）がその枠線を隠すので、Material が囲みの中の表にしている `margin: 1em -.6rem` と同じ幅にそろえた。ビルドした HTML を数えると、別行の数式 632 個のうち 16 個が details の中にある（admonition の中は 0 個）。本文の表は、数えた範囲ではどれも囲みの外にある
3. **はみ出しの影**（幅を問わない）：`.md-typeset .md-typeset__scrollwrap`（Material が表を包む横送りの枠）と `.md-typeset div.arithmatex`（別行の数式の横送りの枠）の背景に 4 枚の線形グラデーションを置く
   - 左右の端に、枠に固定した影（`background-attachment: scroll`、幅 0.9em、色は `--kp-scroll-shadow`）
   - その上に、中身と一緒に動く覆い（`local`、幅 2em で半分まで `--md-default-bg-color`）。中身の端が枠の端に来ると覆いが影に重なって影が消え、はみ出さないときは初めから重なっていて影が出ない。結果として、まだ送れる側の端にだけ影が出る（左端は送った後に出る）
   - 表の背景を透明にした（`.md-typeset .md-typeset__table table:not([class]) { background-color: transparent; }`。Material は `--md-default-bg-color` で塗っていて、枠の背景の影を隠す）。地の色と同じなので、見た目は変わらない
   - 影の色：ライトは `rgba(0, 0, 0, 0.22)`、ダークは `rgba(0, 0, 0, 0.8)`（0.6 では端の明るさが 34 → 14 で見えにくかったので濃くした。0.8 で 34 → 8）
   - `local` は MDN の互換表（browser-compat-data の `css.properties.background-attachment.local`）で、Chrome・Android の Chrome は 1 から、iOS・macOS の Safari は 15.4 から効く。13〜15.3 は「認識するが効かない」で、覆いが動かないので影が出ないだけで、崩れはしない（CSS の注記にも書いた）

### katex-init.js を変えなかった理由

指示の例（KaTeX で描いた後に scrollWidth を見て class を付ける）も考えたが、CSS だけで済ませた。

- 表は Material の JS が後から `.md-typeset__scrollwrap` で包むので、katex-init.js から表を見ると描く順に左右される。数式と表で同じ見た目にするなら、両方とも CSS で出すのが簡単である
- 背景の `scroll`・`local` なら、横に送った位置（端まで送ったら消す）と、画面の回転・幅の変化・フォントの読み込みによる幅の変化に、JS なしで追従する。class を付ける方式では、scroll・resize の監視と instant navigation のたびの付け直しが要る

### data-kp-order の規則とぶつからないこと

`table[data-kp-order] tr > :first-child` の規則は、この作業ツリー（fix/mobile-layout）にはなく、feat/progress の kp.css の 720 行目にある（`.md-typeset table[data-kp-order] tr > :first-child { min-width: 0; padding-right: 0.5em; padding-left: 0.9em; }`）。詳細度は (0,3,2) で、この直しの狭い画面の規則 (0,2,2) より高い。

- `<W>/conflict.mjs` で、`<W>/site` の guide/roadmap の表に `data-kp-order` を付け、feat/progress の規則を kp.css の前と後ろの両方に置いて、計算値を見た。どちらの順でも、390px で 1 列目は `min-width: 0`・左 0.90em・右 0.50em（feat/progress の値）、2 列目以降は左右 0.60em（この直しの値）、上下はどの列も 0.75em でそろう。1280px では 1 列目が feat/progress の値、2 列目以降は Material の既定（min-width 100px・1.25em）のままである
- 両方のブランチとも kp.css の末尾に追記しているので、マージでは末尾の行がぶつかる。両方の節を残せばよく、規則どうしはぶつからない

### 組み直した表（中身は変えない）

列をまとめるのは `<W>/tabletool.py` で機械的に行い、セルの文字を落とさないようにした。まとめるときの区切りは、ハブ（行き先を引く表）は「 → 」（全角の括弧の後ろでは空白を入れず「）→ 」。手引き §7）、データ構造の型の表は「：」、すでに「 / 」で 2 つを 1 列に入れている表（lazy-segment-tree・segment-tree-binary-search）はそれに合わせて「 / 」にした。

- **dp-speedup-overview**（ハブ）：見出しは「道具 → ページ」。セルは「累積和（配る形ならいもす法）→ [DP と累積和](…)」の形。道具の名前とリンクの文字がまったく同じ 3 行（単調スタック・Alien DP・Slope Trick）は、同じ語を 2 度並べないようリンクだけにした（名前はリンクの文字として残る）。read-the-recurrence の 3 列の表は変えていない
- **graph-modeling**（ハブ）：Issue が挙げた制約の表・縮約の表を 3 列にした。縮約の表は、ページが「道具」ではなく「使い方」を説明する行き先なので、「まとめた後の形・使い方 → ページ」にまとめた（最後の行は「次数 3 以上の頂点だけが残る → このページの下の説明」）。頂点・辺の表（4 列）は、行き先の列が 3 列目にあり、直した CSS で 320px まで収まるので変えていない
- **lazy-segment-tree** の標準の型の表（4 列）は、直した CSS で 320px まで収まり、3 列にするには `mapping`・`composition`・`id` を 1 列に詰めることになって読みにくいので変えていない

`<W>` で、直す前（`git show HEAD:<file>` を `<W>/orig/` に置いたもの）と比べて確かめた：

- 組み直した 11 個の表で、リンク（文字と行き先）の多重集合は前後で同じ
- 区切りの文字（→・：・/）と空白を除いた文字の多重集合の差は、dp-speedup-overview の早見表で落とした「単調スタック」「Alien DP」「Slope Trick」の 3 語だけ
- 表の外の本文は、graph-modeling の `updated` の行のほかは変わっていない

### 確かめたこと

**対象の 9 ページの表 26 個**（`<W>/measure.mjs`。枠の scrollWidth − clientWidth）

| 幅 | 直す前 | CSS だけ直した後 | 表も組み直した後 |
| --- | --- | --- | --- |
| 390px | 18 個がはみ出す（最大 244px。dp/bit-dp#complexity）。17 個で列が画面の端で切れる | 0 個 | 0 個 |
| 360px | — | 2 個（lazy-segment-tree-patterns・segment-tree-monoids の型の表。21px・29px） | 0 個 |
| 320px | — | 5 個 | 1 個（segment-tree-monoids の型の表。29px、影が出る） |
| 1280px | 0 個 | — | 0 個 |

どの幅でもページ全体の横のずれ（document の scrollWidth − 画面の幅）は 0 である。

**サイト全体**（422 ページ、390px。`<W>/sitewide.mjs`・`<W>/summarize.py`、結果は `<W>/sitewide-before-390.json`・`<W>/sitewide-after-390.json`）

| | 直す前 | 直した後 |
| --- | --- | --- |
| 表 | 772 個のうち 157 個がはみ出す（102 ページ）。4 列以上の表は 144 個すべて | 3 個（guide/library-design 3 列・102px、math/miller-rabin 2 列・94px、ds/advanced-ds-catalog 4 列・19px） |
| 最後の列がまるごと画面の外にある表 | 28 個 | 0 個 |
| 別行の数式（画面より広いもの） | 632 個のうち 270 個（146 ページ）。math・comb では 54 ページに 119 個で、Issue の調査と一致 | 数は display-math の担当の直しによる（この直しは幅を変えない）。はみ出すものにはすべて影が出る |

直した後の測定では、3 ページ（misc/randomized・patterns/grid・string/subsequence-matching）で表か数式の数が読み込みの途中の値になっていたので測り直し、前と同じ数ではみ出しがないことを確かめた（`<W>/recheck-*.json`）。直した後のビルドには、同じ作業ツリーで display-math の担当が直している最中の comb・math のページも入っている。

**影の出方**（画素の明るさで確かめた。数値は端から 16px の平均の明るさ）

- comb/rational-mod#why の数式（390px で 409px はみ出す）：送る前は右端だけ、真ん中まで送ると両端、端まで送ると左端だけに影が出る（ライト 255 → 202、ダーク 34 → 8）。`<W>/shots/hint-m-comb_rational-mod-why-0-math{,-mid,-end}.png`・`hint2-md-…`
- segment-tree-monoids の型の表（320px で 29px はみ出す）：送る前は右端に影、端まで送ると右端の影が消える（ライト・ダーク）。`<W>/shots/hint2-s{,d}-ds_segment-tree-monoids-pattern-table-0{,-end}.png`
- はみ出さない表と数式（dp-speedup-overview の早見表と別行の数式）には影が出ない（端の画素が地の色のまま）。`<W>/shots/fit-*.png`
- details の中の数式（comb/expectation-of-square、390px）：直す前の数式の枠は 13〜377px で囲み（16〜374px）の枠線に重なっていた。直した後は 17〜373px で、左右の枠線が途切れない（ライト・ダーク）。`<W>/shots/before-m-admon-…`・`after2-m{,d}-admon-comb_expectation-of-square.png`

**見た目**（`<W>/shots/`。`before-` が直す前、`after-` が直した後。`m` は 390px ライト、`md` は 390px ダーク、`d` は 1280px ライト、`n` は 360px、`s` は 320px）

- 390px：直す前は列がどれも 100px 前後で、早見表の「例題」、bit-dp の「$N = 17$」「$N = 20$」、two-pointers の「数え方」などが画面の外にあった。直した後は行き先のリンクと要の値がすべて画面の中にある。早見表は「道具 → ページ」の列が広くなり、ページの名前が 4〜5 文字ずつ折り返されていたのが 2 行ほどに収まった
- ダークモード：表の背景を透明にしても、地の色と同じなので変わらない
- 1280px：組み直した表も 3 列でそのまま読める（早見表・graph-modeling の制約の表・segment-tree-monoids・segment-tree-binary-search を見た）

**検査**

- `python3 tools/check_pages.py --page <id>`：9 ページともエラー 0・警告 0
- `python3 tools/fix_problems.py --check --page <id>`：9 ページとも直すべき行 0（問題の行は触っていない）
- `npx textlint`（9 ページ）：エラー 0。警告は 167 件で、直す前の同じファイルと件数も中身も同じ（行番号がずれただけ）。この直しで増えた警告はない
- `.venv/bin/mkdocs build --strict -d <W>/site`：警告 0

### 残った点

- segment-tree-monoids の型の表は、320px（初代の iPhone SE などの幅）でまだ 29px はみ出す。単位元の列の $(0, -\infty, -\infty, -\infty)$ が折り返せない幅（約 130px）を取るためで、影は出る。390px・360px では収まる
- サイト全体で 390px ではみ出す表が 3 個残る（guide/library-design・math/miller-rabin・ds/advanced-ds-catalog）。担当外なので直していない。どれも影が出る
- 別行の数式は幅を変えていない（`\text` の文を外に出すのは display-math の担当）。影で、はみ出すことは分かる
- 手引き §8 は変えていない（下の提案）

### 提案

1. **手引き §8**：「表は横に広げすぎない（スマホで読む。列は 4〜5 まで）」を次の 2 項目に置き換える。
   - 表は横に広げすぎない（スマホで読む）。列は 3 つまでを目安にし、行き先のリンクと要の値（計算量・単位元・呼び方など）の列は 3 列目までに置く。4 列以上になるなら、2 つの列を 1 つのセルにまとめる（ハブは「道具 → [ページ](…)」、型の表は「求めるもの：載せる値」や「`op` / `e()`」）か、行が 2〜3 しかない表は縦横を入れ替える（工程11、#55）
   - コードや数式の入る表と、別行の数式は、幅 390px（スマホ）で確かめる。セルの中のインラインの数式と長い語は折り返されず、その列の最小の幅になる。はみ出す表と数式には送れる側の端に影が出るが、行き先のリンクと要の値は横に送らずに読めるようにする（工程11、#55）
2. **手引き §4 の hub**（任意）：「表は 3 列までにし、道具とページは『道具 → [ページ](…)』の 1 列にまとめる。道具の名前とページの題名が同じならリンクだけにする」を足すと、ハブの表の形がそろう
3. **#61 の描画の検査（feat/render-check）**：390px で、最後の列の左端が画面の外にある表（`thead th` の最後の left ≥ 枠の clientWidth）と、はみ出しの大きさを一覧にすると、§8 の確かめを機械でできる。`<W>/sitewide.mjs` の測り方（`.md-typeset__scrollwrap` と `div.arithmatex` の scrollWidth − clientWidth、最後の列の位置）がそのまま使える
4. **マージ**：feat/progress とこのブランチは、どちらも kp.css の末尾に節を追記しているので、末尾の行がぶつかる。両方の節を残せばよい（規則どうしはぶつからない。上の「data-kp-order の規則とぶつからないこと」）

### メインに判断してほしい点

1. ハブの「道具 → ページ」のまとめ方で、道具の名前とリンクの文字がまったく同じ 3 行（単調スタック・Alien DP・Slope Trick）をリンクだけにした。表の形をそろえるのを優先するなら「Alien DP → [Alien DP](…)」のように 2 度書く形に戻せる
2. 4 列のまま残した表（graph-modeling の頂点・辺の表、lazy-segment-tree の標準の型の表、complexity-estimation の制約の表は列の順だけ入れ替え）は、直した CSS で 320px まで収まるので組み直さなかった。3 列にそろえるかどうか
3. segment-tree-monoids の型の表が 320px で 29px はみ出すのを残してよいか（390px・360px では収まる。影は出る）
4. #55 の pull request では、表の部分と手がかりはこの直しで済む。`\text` の数式（display-math）と §8 の改めがそろうまでは `Refs #55`、そろえば `Closes #55`

## 検証の指摘への対応（fixup-tables）

[verify-tables.md](verify-tables.md) の「直しが要る点」1〜3 への対応である。直したのは `overrides/assets/css/kp.css` だけで、表を組み直した 9 ページと `katex-init.js` は変えていない。指摘 3 は担当外のページなので直さず、メインに判断を頼む（下の「メインに判断してほしい点」）。

- 作業用フォルダ：`/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/7a638398-7759-4637-95c7-6739e8d52414/scratchpad/fix/mobile-layout/fixup-tables`（以下 `<F>`）
- ビルド（どれも `mkdocs build --strict` で警告 0・終了コード 0）
  - `<F>/site-before`：作業ツリーの直す前（kp.css は最初の担当の版。`<F>/orig/kp.css.fixup-before`）
  - `<F>/site`：作業ツリーの直した後。site-before との違いは kp.css だけ
  - `<F>/site-main`：main（c8924bb）。`git archive main` を `<F>/src-main` に展開してビルドした
  - `<F>/site-merged`：main に 9 ページの差分と、直した後の kp.css の #55 の節を当てたもの（`<F>/src-merged`。節は main の kp.css の末尾、feat/progress の節の後ろに置いた）。マージした後の状態に近い
  - `<F>/site-merged-b`：site-merged の kp.css を、最初の担当の節にしたもの（違いは kp.css だけ。検証の site-merged と同じ状態）
- 計測と撮影：`python3 -m http.server`（127.0.0.1:38917）で配り、chrome-headless-shell 146 を CDP で動かした。幅 700px 未満はタッチ（`pointer: coarse`）を有効にした。ページを開いたあと、表が Material の枠に包まれ、数式が KaTeX で描かれ、フォントが読み終わるのを待ってから測った。スクリプトは `<F>/scripts/`、結果は `<F>/sw/`、画像は `<F>/shots/`（`main-` は main、`b-` は直す前＝最初の担当の CSS、`a-` は直した後。`390d` はダーク）

### 直したところ（kp.css 641〜663 行）

| 行 | 内容 | 指摘 |
| --- | --- | --- |
| 648 | 狭い画面の見出しのセルの `min-width` を `0` から `4em` にした（表の字 0.64rem で 51.2px。余白を除いて全角 2 字が入る） | 1 |
| 649–651 | 列が 7 つ以上の表だけ、狭い画面の下限を外す（`.md-typeset table:not([class]):has(th:nth-child(7)) th { min-width: 0; }`） | 1 の副作用への対処（指示になかった規則） |
| 660–663 | 表の中の Library Checker の問題名のリンクを途中で折り返す（`.md-typeset table:not([class]) a[href^="https://judge.yosupo.jp/"] { overflow-wrap: anywhere; }`）。指示は狭い画面の節だったが、幅を問わず効かせた（理由は下の指摘 2） | 2 |
| 642–646 | 節の頭の注記に、下限を 0 にしない理由を足した | 1 |

ロードマップの # の欄の規則（main の `.md-typeset table[data-kp-order] tr > :first-child`、詳細度 (0,3,2)）とはぶつからない。site-merged の 390px で、色ごとの列の表の # の欄の `min-width` は 0px（main の規則が勝つ）、ほかの列は 51.2px だった。7 列以上の規則は詳細度 (0,3,3) だが、ロードマップの表は 4 列なので当たらない。

### 指摘 1：min-width: 0 で短い日本語の列が 1 字の幅になる（直した）

下限を 4em にした。サイト全体（390px・360px、タッチ。`<F>/scripts/sitewide.mjs`・`summarize.py`）では次のとおりで、1 字の幅の列（中身の幅が 2em 未満で、3 字以上の文字が入る列。検証と同じ定め方）は 0 になった。

| 390px | main | 直す前 | 直した後 |
| --- | --- | --- | --- |
| はみ出す表（774 個のうち） | 159 個（103 ページ） | 4 個（3 ページ） | 3 個（3 ページ） |
| 最後の列がまるごと画面の外にある表 | 29 個 | 0 個 | 0 個 |
| 1 字の幅の列 | 0 | 251（59 ページ） | 1（string/kmp の 1 列目。中身が `$S[i]$`・`$\pi[i]$` のインラインの数式で、折り返さない。KaTeX の文字が 3 重に数えられて 3 字以上になる見かけのもの） |
| 表の高さの合計 | 722148px | 536069px | 535061px |

| 360px | main | 直す前 | 直した後 |
| --- | --- | --- | --- |
| はみ出す表 | 193 個（120 ページ） | 6 個（5 ページ） | 6 個（6 ページ） |
| 最後の列がまるごと画面の外にある表 | 35 個 | 0 個 | 0 個 |
| 1 字の幅の列 | 0 | 257（62 ページ） | 1（同じ kmp の数式の列） |

- main のはみ出す表は 159 個で、検証の 158 個と 1 つ違う。検証の計測では basics/two-pointers の表が読み込みの途中で数えられていなかった（表の総数が 772 個）
- 作業ツリーだけのビルド（site-before → site、390px）でも、1 字の幅の列は 249（58 ページ）→ 1（同じ kmp）、はみ出す表は 3 個のまま（library-design#verify-table が収まり、dp/subset-sum#three-forms が加わる）
- **ロードマップ**（14 個の表。JS が出す集計の表を含む）：390・360・320px でどれもはみ出さない。1 字の幅の列は 7（色ごとの列の表の頻度の列 4 つと、最近 30 回の表の「問題数」3 つ）→ 0。水・青・黄・発展の表の頻度の列は 37〜40px → 56〜57px になり、「準必修」「必修」は 1 行、「余裕があれば」は 2 行に収まる。「余裕があれば」の行（水の 70 番、区間篩）の高さは 143px → 82px（main は 69px）。表の高さの合計は 390px で 54222 → 50047px（−7.7%。main は 73155px）、360px で 57740 → 52890px（−8.4%）。表ごとには 390px で発展 9864 → 6935px（−30%）、水 9613 → 9217px、青 11750 → 11453px、黄 8882 → 8534px。1280px では前と同じ（35366px）
- **Issue の 9 ページの表 26 個**：390px・360px でどれもはみ出さない。320px は segment-tree-monoids の型の表の 29px だけで、前と同じ（影が出る）。表の高さの合計は 390px で 14934 → 14831px、360px で 16572 → 16305px、320px で 18945 → 18311px で、390px で高くなった表はない（two-pointers#vs-binary-search は「観点」の列が 46 → 60px になり 266 → 225px）。1280px は前と同じ
- **検証が挙げたほかの表**（390px）：graph/k-shortest-paths#comparison の「数える対象」は 33 → 53px（表の高さ 450 → 368px）、comb/binomial-coefficient#meanings の「見方」は 36 → 51px（266 → 246px）、start/how-to-use#structure の「ページ」は 35 → 52px

### 列が 7 つ以上の表の例外（指摘 1 の直しに足したもの）

4em だけにすると、検証の予想どおり値の表 4 個がはみ出す（390px で comb/grundy-number#definition 207px・string/kmp#failure-function 54px・math/proof-patterns#rearrangement 17px・dp/subset-sum#three-forms 10px）。grundy-number は最後の列（$x = 9$）がまるごと画面の外に出て、「最後の列が画面の外にある表」が 0 → 1 に戻る。

- 前の 3 個は列が 7 つ以上で、7 × 4em = 358px が 390px の本文の幅（約 358px）に届くので、下限だけではみ出す。サイト全体の表 774 個のうち列が 7 つ以上なのはこの 3 個だけ（6 列が 1 個、5 列以下が 770 個）で、どれも添字と値を並べた、セルが 1〜2 字の表である。そこで、列が 7 つ以上の表だけ下限を外した
- 結果：3 個とも 390・360・320px ではみ出さない（4em だけのときは 320px で 277・124・87px）。列は 22px（1 字の値）になり、どれも最初の担当の版と同じ見た目に戻る（`a-390-grundy-definition.png`・`a-390-kmp-failure.png`・`a-390-proof-rearrangement.png`）。ただ 1 つの 6 列の表（guide/problem-sets#practice-contests。日本語の列がある）は 4em のままで、390・360px で収まる
- 狭い画面の media の中に置いたので、1280px は Material の 5rem のまま（Issue が「狭い画面のときだけ」としているため）。この 3 個は main でも 1280px で 414・114・14px はみ出していて、例外を広い画面にも効かせると 0 になる（下の提案 3）
- `:has()` に対応しないブラウザでは規則ごと読み飛ばされ、4em のまま（はみ出して影が出るだけで、崩れはしない）
- 4 個目の dp/subset-sum#three-forms（4 列）は 390px で 10px はみ出したまま残した（影が出る。`a-390-subsetsum-three-forms.png`・`-end.png`。main は 121px）。「形」の列（可否・数え上げ・最大）が 30 → 51px になり、式の列は折り返せない数式なので、どこかの列を狭めないと収まらない

### 指摘 2：main をマージすると guide/library-design の 2 つの表が崩れる（直した）

| site-merged | 390px | 360px | 320px | 1280px |
| --- | --- | --- | --- | --- |
| #acl-names（直す前） | 105px はみ出す・高さ 3396px・自作の列 28px | 135px・3396px | 175px・3396px | 6px・1720px |
| #acl-names（直した後） | 0・1452px・自作の列 58px | 0・1636px | 0・2414px | 0・820px |
| #verify-table（直す前） | 102px・7039px | 132px・7039px | 172px・7039px | 0・5688px |
| #verify-table（直した後） | 0・6118px | 0・6548px | 0・7264px | 0・4910px |

main は #acl-names が 390px で 336px はみ出し（1720px）、#verify-table が 200px はみ出す（6261px）。

- 自作の列のコード（`UnionFind`・`WeightedUnionFind` など）は、1 字ずつ縦に並んでいたのが 6〜7 字ずつ折り返す形になった（`b-390-libdesign-acl-top.png` → `a-390-libdesign-acl-top.png`。ダークは `a-390d-libdesign-acl-top.png`）
- **幅を問わず効かせた理由**：main でも、#acl-names は 720・960・1220・1280・1440・1920px で 6〜8px はみ出し（800・1024px では収まる）、「ACL との違い」の列が下限の 100px に押し縮められて高さが 1720px ある（1920px は 1890px。問題名の列が 292px を取るため。`main-1280-libdesign-acl.png`）。規則を幅を問わず効かせると、1280px ではみ出しが 0、高さが 820px（「ACL との違い」は 214px）になる（`a-1280-libdesign-acl.png`）。問題名が途中で切れるのは列が狭いときだけで、1280px の #acl-names では問題名の列が 125px で `unionfind_with_potential` などが 2〜3 行になり、#verify-table（列 422px）では切れない。ページ下部の自作の確認（`.kp-links__verify a`）も幅を問わない規則である
- サイト全体で、表の中に Library Checker のリンクがあるのは guide/library-design だけ（main の docs を `git grep` した）。1280px の全ページの計測で、直す前と違う表は library-design の 2 つだけだった（`<F>/sw/mergedb-1280.json`・`merged-1280.json`）。狭い画面だけに戻すなら、663 行を media の中に移せばよい

### 指摘 3：ds/advanced-ds-catalog の一覧の表（担当外なので直していない）

4em は「何ができるか」の列（52px ≥ 51.2px）を変えないので、この表は最初の担当の版のままである（390px で 19px はみ出し、高さ 3232px。main は 117px・1627px。`a-390-advds-table-top.png`）。直すには表を 3 列に組み直すのが要る（下の提案 2）。

### 確かめたこと

- **見た目**（`<F>/shots/`。直す前・後・main を同じ場所で撮った）
  - 390px ライト：ロードマップ（`*-390-roadmap-cyan-yoyu.png`・`*-390-roadmap-advanced-top.png`・`*-390-roadmap-recent-e.png`）、library-design（`*-390-libdesign-acl-top.png`・`*-390-libdesign-verify-top.png`）、1 字の幅だった表（`*-390-kshortest-comparison.png`・`*-390-binom-meanings.png`・`*-390-problemsets-recent-abc-top.png`）、7 列以上の表（`*-390-grundy-definition.png`・`*-390-kmp-failure.png`・`*-390-proof-rearrangement.png`）、9 ページの表（`*-390-dpso-shape-to-tool-top.png`・`*-390-stm-pattern.png`・`*-390-ce-constraint.png`・`*-390-tp-vs-bs.png`・`*-390-bd-tsp.png`・`*-390-gm-vertex.png`）
  - ダーク（390px）：`b-`・`a-390d-roadmap-cyan-yoyu.png`、`a-390d-libdesign-acl-top.png`、`a-390d-dpso-shape-to-tool-top.png`、`a-390d-subsetsum-three-forms.png`。地の色・枠線・影とも崩れはない
  - 1280px：`main-`・`b-`・`a-1280-libdesign-acl.png`（ダークは `a-1280d-`）、`b-`・`a-1280-roadmap-cyan-top.png`（同じ）、`a-1280-dpso-shape-to-tool-top.png`、`a-1280d-stm-pattern.png`
- **影**：はみ出したまま残る表に、送れる側の端の影が出る（math/miller-rabin#deterministic-bases は送る前に右、端まで送ると左。`a-390-millerrabin-bases{,-end}.png`。dp/subset-sum も同じ。segment-tree-monoids の 320px は `a-320-stm-pattern{,-end}.png`）。影の規則は変えていない
- **検査**
  - `python3 tools/check_pages.py --page <9 ページの id>`：エラー 0・警告 0（ページは変えていない）
  - `.venv/bin/mkdocs build --strict -d <F>/…`：5 つのビルドとも警告 0
  - `python3 tools/gen_site.py --check`：古い生成物 3 つ（`docs/llms.txt`・`overrides/assets/data/graph.json`・`docs/start/how-to-use.md`）。検証が見たものと同じで、9 ページの差分によるもの（kp.css は生成物に関わらない）。メインが作り直せば済む
  - textlint・fix_problems：Markdown を変えていないので対象がない

### 残った点

- ds/advanced-ds-catalog#table：390px で 19px はみ出し、「何ができるか」の列が 52px（1 行に 3 字）で高さが main の 2 倍（担当外。提案 2）。390px で隠れるのは右の余白と枠線だけで、字の右端（385px）は見えている
- math/miller-rabin#deterministic-bases：390px で 94px はみ出す（「試す底」の列の数式が折り返せない。main は 127px。担当外。影が出る）
- dp/subset-sum#three-forms：390px で 10px、360px で 40px はみ出す（main は 121px）。390px で隠れるのは右の余白と枠線だけで字は見えている（字の右端 375px）ので、影は薄い。360px では字が 15px 隠れ、影が出る（`<F>/scripts/textedge.mjs`）
- 360px で新たにわずかにはみ出す表が 2 つある：comb/binomial-coefficient#meanings 4px、cpp/cpp-undefined-behavior#other-ub 2px（下限 0 のときは 0px）。どちらも隠れるのは右の余白と枠線だけで、字は見えている。cpp/cpp-types-literals の #inf の節の 2 つ目の表の 26px は前からある（main は 106px）
- 下限を 4em にしたので、短い値の列（「位置」の D、「diff」の 856 など）も 51px を取り、ほかの列が狭まって高くなる表がある。390px で直す前より高い表が 135 個、低い表が 142 個、同じ表が 497 個で、高さの合計はほぼ同じ（536069 → 535061px）。いちばん高くなったのは guide/problem-sets#recent-abc（13558 → 15339px。main は 20486px）で、ページの列は 176 → 150px だが読める（`a-390-problemsets-recent-abc-top.png`）
- guide/library-design#acl-names は 390px で収まるが、5 列なので「確認の問題」の列が 63px になり、長い問題名は 6 行に分かれる（提案 4）
- 1280px で値の表 3 個がはみ出すのは main からのまま（提案 3）

### 提案

1. **手引き §8**：「表は横に広げすぎない（スマホで読む。列は 4〜5 まで）」を次の 2 項目に置き換える（最初の提案 1 を、この直しに合わせて改めたもの）。作業ツリーの `planning/style-guide.md` §8 には、この報告を書いた後に同じ 2 項目が入っている（この担当は手引きを変えていない）。
   - 表は横に広げすぎない（スマホで読む）。列は 3 つまでを目安にし、行き先のリンクと要の値（計算量・単位元・呼び方など）の列は 3 列目までに置く。4 列以上になるなら、2 つの列を 1 つのセルにまとめる（ハブは「道具 → [ページ](…)」、型の表は「求めるもの：載せる値」や「`op` / `e()`」）か、行が 2〜3 しかない表は縦横を入れ替える。添字と値を並べる表（列が 7 つ以上）は、どのセルも 1〜2 字にする（工程11、#55）
   - コードや数式の入る表と、別行の数式は、幅 390px（スマホ）で確かめる。狭い画面では列の幅の下限が 4em（全角 2 字）になるが、セルの中のインラインの数式と、空白のない長い英数字の語は折り返されず、その列の最小の幅になる（コードは途中で折り返す）。はみ出す表と数式には送れる側の端に影が出るが、行き先のリンクと要の値は横に送らずに読めるようにする（工程11、#55）
2. **ds/advanced-ds-catalog#table を 3 列に組み直す**（96 行〜）：検証の案のとおり「名前：何ができるか ｜ 計算量 ｜ 代わりになる手」にする（segment-tree-monoids と同じまとめ方）。CSS では直らない（4 列とも中身の最小の幅まで縮んでいて、和が 390px を超える）
3. **列が 7 つ以上の表の例外を広い画面にも効かせる**（kp.css 651 行を media の外にも置く）：1280px で comb/grundy-number#definition 414px・string/kmp#failure-function 114px・math/proof-patterns#rearrangement 14px のはみ出し（main からある。grundy-number は最後の列が画面の外）が 0 になる（`<F>/scripts/trycss-global.mjs` で確かめた）。Issue が見出しのセルの min-width を変えるのは狭い画面のときだけとしているので、入れていない
4. **guide/library-design#acl-names を組み直す**（任意。ページの持ち主の直し）：確認の問題は #verify-table にもあるので、この列を外して 4 列にすると、390px で「ACL との違い」の列が広がって読みやすくなる（問題名は #verify-table で引ける）
5. **マージ**：前と同じく、kp.css は両方のブランチとも末尾に追記しているので末尾の行がぶつかる。両方の節を残せばよい（site-merged はその形で作って確かめた）

### メインに判断してほしい点

1. Library Checker の規則（kp.css 663 行）は、指示の「狭い画面の節」ではなく幅を問わず効かせた（上の指摘 2）。狭い画面だけに戻すかどうか
2. 列が 7 つ以上の表の例外（kp.css 649〜651 行）は、指示になかった規則である。4em の副作用（値の表 3 個のはみ出しと、最後の列が画面の外に出る表）を消すために足した。残してよいか
3. ds/advanced-ds-catalog#table の組み直し（指摘 3）を誰が行うか
