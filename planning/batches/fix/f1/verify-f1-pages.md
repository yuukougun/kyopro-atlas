# verify-f1-pages：#50（f1-alt）と #31・#32・#33（f1-render）の検証

検証したのは作業ツリー（main。HEAD は 6ffc13d で、まだ commit していない）である。2026-10-29 03:54 にビルドし、対象の 36 ファイル（.md 30・SVG 6）がビルドの後に変わっていないことを確かめた。ファイルは直していない。作業用フォルダは `/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/7a638398-7759-4637-95c7-6739e8d52414/scratchpad/fix/verify-f1-pages`（以下 `<V>`）。

## まとめ

| Issue | 担当 | 判定 | 直しが要る点 |
| --- | --- | --- | --- |
| #50 図 28 枚の代替テキスト（本文側） | f1-alt | 合格 | 0 |
| #31 期待値の 2 ページのインラインの数式 | f1-render | 合格 | 0 |
| #32 図の白い背景（4 枚＋追加の 2 枚） | f1-render | 合格 | 0 |
| #33 指数の mod のページの横ずれ | f1-render | 合格 | 0 |

- `python3 tools/check_pages.py`（全体）：353 ページでエラー 0・警告 0。指示にあった aho-corasick 143 行目の長い `\text` の警告は出ない。別の担当が 142・143 行目をすでに書き換えていたためで、その書き換えは対象外として見ていない
- `uv run mkdocs build --strict`（`<V>/site-strict` に出力）：通る
- #50 を閉じるには、担当の範囲外の作業が 2 つ残っている（後述「#50 を閉じるために残っていること」）

## #50 図の代替テキスト（f1-alt）：合格

### 差分（`<V>/bin/diff_alt.py`）

- 27 ページとも行数は変わっていない。変わった行は、`updated: 2026-10-22` → `2026-10-29` の 27 行と、代替テキストの 28 行だけである
- 28 行とも、新しい行の `\[` を `[` に戻すと HEAD の行と一致する。HEAD の行には、もとから入っていた `\[`・`\]` はない。つまり代替テキストの文言は変わっておらず、増えたのは逆斜線だけである
- エスケープは 77 個で、すべて `\[` である（`\]` は 0）。`<V>/bin/alt_brackets.py` で 77 個すべてを調べ、どれも直後が `)` で閉じる半開区間 `[a, b)` の `[` であることを確かめた。エスケープせずに残した括弧は、すべて対になっている（`L[1]`・`P[0]`・`dp[j]`・`z[1]` など）。対になる括弧を誤ってエスケープした箇所はない

### ビルドでの突き合わせ（担当のスクリプトは使わず、`<V>/bin/count_img.py` を新しく書いた）

- 作業ツリー：420 ページ。図の参照は 414 か所、`<img>`（`img/` を指すもの）は 414 個で、ページごとの数の不一致はない。414 件すべてで、alt（Markdown のエスケープを戻したもの）と src の行き先（ファイルがあること）が一致した。本文（pre・code・script・style の外）に「![」は残っていない
- 対照として、HEAD を `git archive` で `<V>/head` に写し、`<V>/head-site` にビルドした。`<img>` は 386 個で、不一致は 27 ページ、「![」の文字は 28 か所である（Issue と同じ数）。このスクリプトで崩れを捉えられることを確かめた
- 地の文（arithmatex の外も含む）に、崩れたリンクや画像の記法（`](`・`![`）が残っていないかも全ページで探した（`<V>/bin/scan_body.py`）。作業ツリーは 0 件、HEAD は 28 件である。リンクの文字の崩れは起きていない

### 検査と CI

- 新しい代替テキストの検査（f1-tools が check_pages.py に足したもの）を、今の check_pages.py のまま HEAD の写しに当てた（`--root <V>/head`）。「画像の代替テキストの角括弧」が 28 件（27 ページ）出て、Issue の一覧と一致した。作業ツリーでは 0 件である
- `.github/workflows/check.yml` の pages ジョブは `python tools/check_pages.py` を動かす。f1-tools の check_pages.py と一緒に commit すれば、この検査は CI で走る

### 表示（ヘッドレスの Chrome。http で配った）

- 幅 390px のライトとダークで、27 ページすべてを測った（`<V>/bin/measure_imgs.mjs`）。どのページも `scrollWidth` は 390 で横ずれがない。図はすべて読み込めており（`naturalWidth > 0`）、本文の幅を超える図はない。KaTeX のエラーは 0 である
- Issue が例に挙げた imos・z-algorithm・dp-speedup-overview の 3 ページを、ダークモードで撮った（`<V>/shots/sheet-50.png`）。どれも前の文に続いて、図が白い地の上に出る

### 表記

- `npx textlint`（27 ファイル）：エラー 0。警告は HEAD の 682 件から 657 件になった。減ったのは no-unmatched-pair の 26 件、増えたのは ds/segment-tree-binary-search.md 101 行の no-doubled-joshi の 1 件だけである。f1-alt の報告と一致する

### 参考（直さなくてよい）

- ds/segment-tree-binary-search.md 101 行の no-doubled-joshi（警告）：代替テキストの「[4, 8) は 28 で偽になり、降りて [4, 6) は 20 で偽、[4, 5) は 11 で真なので」で、並べた項に「は」が重なっている。警告なので CI は落ちない。文言を変えないという指示のとおり残してある
- 今回の直しで、28 枚が公開中のサイトに初めて出る。そのうち 11 枚は、幅が §15-8 の目安（400 程度）を超えるという check_svg の警告を、前から持っている：imos-2d・range-knapsack・period-count・buckets（656）・assign・path-copying・preorder-split・subtree-interval・decomposition（600）・marks-and-sweep・z-box。文字が小さいという警告はどれにも出ていない。390px では 0.55〜0.8 倍に縮んで表示される。今回の範囲外である

### #50 を閉じるために残っていること（担当の範囲外。メインの作業）

- 手引き §8 に、代替テキストに区間を書くときの注意を足す。Issue の「やること」にあり、f1-alt と f1-tools の報告に文案がある
- f1-tools の check_pages.py を、この直しと同じ commit か、その後の commit で入れる（先に入れると、HEAD の docs/ に対してエラーが 44 件出て CI が落ちる）
- `python3 tools/gen_site.py` を流す。`--check --diff` で見ると、古くなった 3 ファイル（docs/llms.txt・overrides/assets/data/graph.json・docs/start/how-to-use.md）の差分は、版と「updated の最大」（2026-10-22 → 2026-10-29）だけである。代替テキストの中身は生成物に入らない。`updated` は版の計算にしか使われていない（テンプレートは読んでいない）

## #31 期待値の 2 ページのインラインの数式（f1-render）：合格

### 意味が元と同じこと

変わったのは `updated` と 9 行である（linearity-of-expectation 78・125・141・150、expectation-of-square 82・135・140・141・253）。どれも `\text{$x$ …}` の `$x$` を `\text` の外に出しただけで、式の組み立ては変わっていない。描いた後の TeX（MathML の annotation）を読むと、次の式になっていた。

- linearity 78：$X_i = [i \text{ 回目の目} = i - 1 \text{ 回目の目}]$（i 回目と i − 1 回目の目が等しい）
- 125：$X_i = [i \text{ が条件を満たす}]$、$E[X_i] = 1 \cdot P(X_i = 1) + 0 \cdot P(X_i = 0) = P(i \text{ が条件を満たす})$。指示確率変数の定義そのものは元のとおりである
- 141：$X_v = [v \text{ が自分の属する成分で番号が最小}]$
- 150：$X_i = [\text{箱 } i \text{ が空}]$
- expectation-of-square 82：$X_i X_j = [i \text{ と } j \text{ が両方起きる}]$
- 135：$[v \text{ にいる}]$（v にいれば 1、いなければ 0）
- 表（140・141）：$S_v = E[L \cdot [v \text{ にいる}]]$、$T_v = E[L^2 \cdot [v \text{ にいる}]]$。$P_v$ の行と「$L \to L + c$ の後」の列は変えていない。更新式 $S_v + cP_v$・$T_v + 2cS_v + c^2P_v$ は、$(L + c)$ と $(L + c)^2$ に指示確率変数を掛けた期待値を展開した結果と合う
- 253：$E[L^2 \cdot [v \text{ にいる}]]$、$E[1 \cdot [v \text{ にいる}]] = P_v$

書き方は、記法の約束（start/notation.md 135 行の `[A_i \text{ が偶数}]`）と dp/tree-dp.md 209 行の `[v \text{ が黒}]` と同じ形である。手引き §6（数式の中の日本語は `\text`）と §7（英数字と和文の間に空白を入れる）にも合う。別行の `$$…$$`（linearity 128・159 行、square 85 行）は直していない。Issue が直さなくてよいとしたもので、描いた後の DOM でもエラーは出ていない。

### KaTeX（http で配り、Chrome の `--dump-dom` で描いた後の DOM を数えた。`<V>/bin/analyze_dom.py`）

| ページ | katex-error（HEAD → 今） | 地の文に漏れた TeX の塊（HEAD → 今） | 描けた数 / arithmatex（今） |
| --- | --- | --- | --- |
| linearity-of-expectation | 4 → 0 | 7 → 0 | 267 / 267 |
| expectation-of-square | 6 → 0 | 7 → 0 | 333 / 333 |

- docs/ の全ページについて、`$$` のブロックとフェンスの外で、`\text{…}` の中に `$` がある箇所を独自に探した。残りは 0 件で、check_pages の新しい検査も 0 件である
- 幅 390px（ライト・ダーク）と 360px で、両ページとも `scrollWidth` は画面幅と同じだった
- textlint：規則ごとの件数が HEAD と同じである（エラー 0、警告は 18 件と 5 件）
- 撮影：`<V>/shots/sheet-31-lin-125.png`（125 行の前後。前は赤字で読めない）、`31-sq-135-table-{before,after,after-dark}.png`（前は表の 2 行が赤字）、`31-lin-{78,141,150}-after.png`、`31-sq-{82,253}-after.png`。折りたたみの中の確認問題も、開いて撮った
- 参考：表の「意味」の列は狭いので、390px では `E[L ·` の後で折り返す。読めるので直さなくてよい

## #32 図の白い背景（f1-render）：合格

### 差分

- 6 枚とも、変わったのは 2 行目の背景の rect だけである（`fill="#ffffff"` も同じ）。Issue の 4 枚（mod-inverse 2 枚・sigma-manipulation 2 枚）に、メインの追加の依頼で直した 2 枚（notation/half-open・subset-sum/shift-or）を足した 6 枚である。どの rect も、viewBox とちょうど同じ x・y・width・height になった
- 図の 6 枚とは別に、作業の途中で docs/img/aho-corasick/fail-tree.svg にも差分が出た。別の担当の動く図の作業なので、見ていない

### 背景が viewBox を覆うこと

- Chrome の canvas に全 414 枚を 2 倍の大きさで描き、透ける画素を数えた（`<V>/bin/svg_alpha.mjs`）。414 枚すべてで 0 である（端の不透明度はすべて 255）。HEAD の 6 枚には透ける画素がある（対照）
- `check_svg.py`：6 枚を `--strict` で調べると、警告は shift-or の幅 495（前からあるもの）の 1 件だけである。全 414 枚では警告 120 件で、背景の警告は 0 件である。同じ検査を HEAD の SVG に当てると警告は 126 件で、背景の 6 件を除いた 120 件は今の結果とまったく同じだった

### 図の見た目が崩れていないこと（`<V>/bin/svg_diff.mjs`）

- HEAD と今の版を白い地に重ねて描き、画素を比べた。6 枚とも差は 0 で、図の中身は変わっていない（ライトモードでの見た目は同じ）
- 暗い地（#1e2129）に重ねて描くと、違うのは前に透けていた帯だけだった。mod 6 は全体（背景の rect が viewBox の外にあった）、mod 7 は右の 10、Σ の 2 枚は下の 24（y が 320〜344）、half-open は下の 7、shift-or は右の 10 である

### ページでの見え方（幅 390px、ライトとダーク）

- `<V>/shots/sheet-32-*.png`。並びは左から「前（ダーク）・後（ダーク）・後（ライト）」。half-open だけは「後（ダーク）・後（ライト）」である（HEAD では #50 の崩れで `<img>` になっておらず、ページの中の「前」を撮れない）
- 前は、mod 6 の題「mod 6：2・3・4 の行には 1 がない」と見出しの行が暗い地に重なって読めなかった。Σ の 2 枚は、下の行「灰色のマス（i > j）は和に入らない」が地の外に出ていた。shift-or は、右端の「13」の箱が暗い帯にかかっていた
- 後は、6 枚ともすべての文字が白い地の上にあり、読める。図を使う 4 ページ（mod-inverse・sigma-manipulation・notation・subset-sum）は、390px のライトとダークで横ずれがない

### 参考（直さなくてよい）

- 図だけを直したページ（mod-inverse・sigma-manipulation・subset-sum）の `updated` は上げていない。brief-fix.md の「本文を直したページは updated を上げる」に合っている。notation は #50 で本文を直したので上がっている
- shift-or.svg の幅 495 は、§15-8 の目安を前から超えている。今回の範囲外で、f1-render の報告の「残った点」にある

## #33 指数の mod のページの横ずれ（f1-render）：合格

- 差分：147 行と `updated` だけである
- 文：前は「$A \ge 2$ なら頭打ちの値はすぐに上限に達するので、高さを $\min(B, \text{法が 1 になるまでの段数より数段多い段数})$ に縮めても答えは変わらない。」。後は「$A \ge 2$ なら頭打ちの値はすぐに上限に達する。そのため、法が 1 になるまでの段数より数段多い段数を $B_0$ とすると、高さを $\min(B, B_0)$ に縮めても答えは変わらない。」
  - 正しい日本語で、だ・である調である。「ので」の因果は「そのため」で残っており、主張（高さを $\min(B, \cdot)$ に縮めてよい、その上限は法が 1 になるまでの段数より数段多い段数）は元と同じである
  - $B_0$ は使う前に定めてある（clarity U3）。ページのほかの箇所とコード片（snippets/exponent-mod/）では使っていないので、記号はぶつからない
  - Issue の例（後ろの括弧で $B_0$ を定める形）とは違う。それでも完了の条件（日本語が数式の外にあり、390px でページが横にずれない）は満たしている。定めてから使う形のほうが読みやすい
- 横ずれ：幅 390px での `scrollWidth` は、HEAD が 447（57px のはみ出し。はみ出す要素はこの数式だけ）、今は 390 である（ライト・ダークとも）。360px でも 360 になる
- KaTeX：描けた数 / arithmatex は 341 / 341 で、エラー 0、漏れ 0
- textlint：規則ごとの件数が HEAD と同じである（警告 13 件）
- 撮影：`<V>/shots/33-after-390-light.png`・`33-after-390-dark.png`・`33-after-360-light.png`（収まる）、`33-before-390-light.png`（数式が右で切れる）

## 確かめた環境と道具

- ブラウザ：chrome-headless-shell 146.0.7680.76。DevTools Protocol で直接操作した（`<V>/bin/cdp.mjs`。Node 24 の WebSocket を使い、依存はない）。幅は 390px と 360px。ライトは scheme default、ダークは `prefers-color-scheme: dark` を emulate した slate である。日本語のフォントは /mnt/c/Windows/Fonts から読んだ
- 配り方：作業用フォルダを `python3 -m http.server 27431 --bind 127.0.0.1` で配り、`http://127.0.0.1:27431/site/…` と `/head-site/…` を開いた。file:// は使っていない。使い終えたサーバーは止めた
- ビルド：作業ツリーは `uv run mkdocs build -q -d <V>/site`、strict は `<V>/site-strict` に出した。HEAD は `git archive HEAD` で `<V>/head` に写し、`<V>/head-site` にビルドした。リポジトリの site/ には書いていない
- 作業用フォルダのもの：
  - `bin/`：diff_alt.py・alt_brackets.py・count_img.py・scan_body.py・analyze_dom.py・dumpdom.sh・cdp.mjs・measure_pages.mjs・measure_imgs.mjs・shots.mjs・svg_alpha.mjs・svg_diff.mjs・sheet.py
  - 結果：`shots/`・`dom/`・`textlint-{old,new}.json`・`check_svg_{all,head}.txt`・`check_pages_head.txt`・`gen_site_diff.txt`

## 提案（メインの判断）

- `<V>/bin/cdp.mjs` を使うと、ビルドの写しの HTML に script を足さなくても、幅とダークモードを切り替えて scrollWidth を測ったり、要素を撮ったりできる。scrollTo の後に真っ白になる問題も起きない。#61（render-check のグループ）の道具の下敷きになる
