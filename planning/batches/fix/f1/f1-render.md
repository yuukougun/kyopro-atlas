# f1-render の報告（#31・#32・#33 表示の崩れ）

直したのは頼まれた 3 ページと SVG 4 枚だけである。3 件とも完了した。作業用フォルダは `/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/7a638398-7759-4637-95c7-6739e8d52414/scratchpad/fix/f1-render`（以下 `<W>`）。直す前のビルドは `<W>/site-before`、直した後は `<W>/site` にある。

## #31 期待値の 2 ページのインラインの数式（完了）

### 直したファイルと行

`docs/comb/linearity-of-expectation.md`（front matter の updated を 2026-10-29 に）

| 行 | 前 | 後 |
| --- | --- | --- |
| 78 | `$X_i = [\text{$i$ 回目の目} = \text{$i - 1$ 回目の目}]$` | `$X_i = [i \text{ 回目の目} = i - 1 \text{ 回目の目}]$` |
| 125 | `$X_i = [\text{$i$ が条件を満たす}]$` | `$X_i = [i \text{ が条件を満たす}]$` |
| 125 | `… = P(\text{$i$ が条件を満たす})$` | `… = P(i \text{ が条件を満たす})$` |
| 141 | `$X_v = [\text{$v$ が自分の属する成分で番号が最小}]$` | `$X_v = [v \text{ が自分の属する成分で番号が最小}]$` |
| 150 | `$X_i = [\text{箱 $i$ が空}]$` | `$X_i = [\text{箱 } i \text{ が空}]$` |

`docs/comb/expectation-of-square.md`（front matter の updated を 2026-10-29 に）

| 行 | 前 | 後 |
| --- | --- | --- |
| 82 | `$X_i X_j = [\text{$i$ と $j$ が両方起きる}]$` | `$X_i X_j = [i \text{ と } j \text{ が両方起きる}]$` |
| 135 | `$[\text{$v$ にいる}]$` | `$[v \text{ にいる}]$` |
| 140（表） | `$E[L \cdot [\text{$v$ にいる}]]$` | `$E[L \cdot [v \text{ にいる}]]$` |
| 141（表） | `$E[L^2 \cdot [\text{$v$ にいる}]]$` | `$E[L^2 \cdot [v \text{ にいる}]]$` |
| 253 | `$E[L^2 \cdot [\text{$v$ にいる}]]$`・`$E[1 \cdot [\text{$v$ にいる}]] = P_v$` | `$E[L^2 \cdot [v \text{ にいる}]]$`・`$E[1 \cdot [v \text{ にいる}]] = P_v$` |

- 別行の `$$…$$`（linearity 128・159 行目、square 85 行目）は指示どおり直していない。描いた後の DOM で katex-error 0 を確かめた。
- 形は start/notation.md 135 行目の `[A_i \text{ が偶数}]` と同じである。`\text{ が…}` の先頭の空白で、英字と和文の間に空白が入る。

### 確かめたこと

ビルドを http で配り、ヘッドレスの Chrome の `--dump-dom` で描いた後の DOM を数えた（file:// では KaTeX が描かれない。後述）。

| ページ | katex-error（前 → 後） | 地の文に漏れた TeX の行（前 → 後） | 描いた数式 / arithmatex（後） |
| --- | --- | --- | --- |
| linearity-of-expectation | 4 → 0 | 4 → 0 | 267 / 267 |
| expectation-of-square | 6 → 0 | 5 → 0 | 333 / 333 |

- 直す前は、赤字にならない箇所でも `i$ が条件を満たす}]$` のような断片が地の文に出ていた。150 行目は赤字にならず `$X_i = [\text{箱 ` がそのまま出ていた。katex-error だけを数えると見落とすので、地の文（.katex・pre・code を除く）の `$`・`\英字` も数えた。
- 描いた数式の TeX（MathML の annotation）が上の表の「後」と一致することを確かめた。
- 幅 390px・360px で両ページとも `document.documentElement.scrollWidth` が画面幅と同じだった。直した数式はどれも本文の幅に収まる。表の `$E[L \cdot [v \text{ にいる}]]$` は狭い列で `\cdot` の後で折り返すが読める。
- スクリーンショット：`<W>/shots/31-linearity-indicator-{before,after}-390.png`・`<W>/shots/31-square-carry-{before,after}-390.png`。前は赤字の `[\text{v$ にいる}]]$` が出ており、後は正しく描けている。
- `check_pages.py --page`：両ページともエラー 0・警告 0。
- textlint：エラー 0。警告は直す前と同じ（linearity 18 件・square 5 件。文の長さ・助詞の重複など既存のもの）。差は linearity 77 行目の文の長さが 133 字から 131 字になったことだけである。

## #32 図 4 枚の白い背景（完了）

### 直したファイルと行（どれも 2 行目の背景の rect）

| ファイル | 前 | 後 |
| --- | --- | --- |
| docs/img/mod-inverse/mult-table-mod6.svg（viewBox="300 0 280 276"） | `<rect width="100%" height="100%" …>` | `<rect x="300" y="0" width="280" height="276" …>` |
| docs/img/mod-inverse/mult-table-mod7.svg（viewBox="10 0 260 276"） | `<rect width="100%" height="100%" …>` | `<rect x="10" y="0" width="260" height="276" …>` |
| docs/img/sigma-manipulation/swap-grid-rows.svg（viewBox="8 0 310 344"） | `<rect x="0" y="0" width="640" height="320" …>` | `<rect x="8" y="0" width="310" height="344" …>` |
| docs/img/sigma-manipulation/swap-grid-cols.svg（viewBox="334 0 280 344"） | `<rect x="0" y="0" width="640" height="320" …>` | `<rect x="334" y="0" width="280" height="344" …>` |

- 背景を viewBox とちょうど同じ範囲にした。`width="100%"` は x = 0 から測られるので、数で書いた。Σ の 2 枚は高さを 344 にし、幅も viewBox に合わせた（もとの 640 は、1 枚の図を 2 枚に分ける前の名残とみられる）。
- 図を使うページ（mod-inverse・sigma-manipulation）の本文は変えていないので、updated はそのままにした。

### 確かめたこと

- 背景が viewBox を覆うかを数で比べた。直す前は 4 枚とも覆っておらず（mod 6 は x が [0, 280] で viewBox は [300, 580]、Σ は y が [0, 320] で viewBox は [0, 344]）、直した後は 4 枚とも覆う。
- `check_svg.py --page mod-inverse`・`--page sigma-manipulation`・4 枚を `--strict`：警告 0・エラー 0。
- `render_svg.py mod-inverse sigma-manipulation --bg '#1e2129' --scale 2`（`<W>/render/`）：4 枚とも全体が白い地で、端に暗い帯がない。端の文字も viewBox から 10 以上離れている（mod 7 の題の右端は約 12、mod 6 の「1 がない」の右端は約 10.5）。
- ダークモード（`--blink-settings=preferredColorScheme=0`。body の scheme は slate）・幅 390px でページを撮った（`<W>/shots/32-mod-inverse-{before,after}-dark-390.png`・`<W>/shots/32-sigma-{before,after}-dark-390.png`）。前は mod 6 の題「mod 6：2・3・4 の行には 1 がない」と見出しの行が暗い地に重なって読めず、Σ の 2 枚は下の「灰色のマス（i > j）は和に入らない」が地の外に出ていた。後はすべて白い地の上で読める。
- `check_pages.py --page mod-inverse`・`--page sigma-manipulation`：エラー 0・警告 0。

## #33 指数の mod のページの横ずれ（完了）

### 直したファイルと行

`docs/math/exponent-mod.md` 147 行目（front matter の updated を 2026-10-29 に）

- 前：「$A \ge 2$ なら頭打ちの値はすぐに上限に達するので、高さを $\min(B, \text{法が 1 になるまでの段数より数段多い段数})$ に縮めても答えは変わらない。」
- 後：「$A \ge 2$ なら頭打ちの値はすぐに上限に達する。そのため、法が 1 になるまでの段数より数段多い段数を $B_0$ とすると、高さを $\min(B, B_0)$ に縮めても答えは変わらない。」

Issue の例の形（「…答えは変わらない（$B_0$ は…）」）にすると、textlint の no-doubled-joshi（「は」の重複）の警告が 1 件増えた。そこで $B_0$ を先に定めてから使う 2 文にした。中身（事実）は変えていない。$B_0$ はページのほかの箇所では使っていない。

### 確かめたこと

- 幅 390px の `document.documentElement.scrollWidth`：前は 447（はみ出しは 57px で、Issue の約 58px と合う。はみ出していた要素はこの数式だけ）、後は 390。360px では 360、ダークモードの 390px でも 390。
- katex-error 0、地の文に漏れた TeX 0（描いた数式 341 / arithmatex 341）。
- スクリーンショット：`<W>/shots/33-exponent-mod-before-390.png`（数式が右で切れる）、`<W>/shots/33-exponent-mod-after-390.png`（折り返して収まる）。
- `check_pages.py --page exponent-mod`：エラー 0・警告 0。textlint：エラー 0。警告は直す前と同じ 13 件。

## 検証役への引き継ぎ（確かめ方の注意）

- **file:// で開くと KaTeX が描かれない**。ヘッドレスの Chrome で `--dump-dom` すると `class="katex"` が 0 になり、katex-error も 0 と出る。数えるときは作業用フォルダを `python3 -m http.server --bind 127.0.0.1 --directory <作業用フォルダ> <port>` で配り、http:// で開く。描けたかは、`data-kp-rendered` の数と `class="arithmatex"` の数が等しいかで確かめる。
- 壊れた数式の一部は katex-error にならず、`$`・`\text{` が地の文にそのまま出る。地の文に残っていないかも数える。
- script で scrollTo してから `--screenshot` すると真っ白になった。代わりに、対象より前のブロックを display:none にして撮った（対象の幅と折り返しは変わらない）。
- 使った道具は `<W>/bin/` にある：`dumpdom.sh`（描いた後の DOM）・`analyze.py`（katex-error と漏れた TeX を数える）・`measure.sh`＋`inject.py`（scrollWidth を測る）・`shot.sh`＋`inject_shot.py`（対象の箇所を撮る）。ビルドの写しの HTML に script を足した別のファイル（measure.html・shot-*.html）を作るだけで、リポジトリは書き換えない。

## 提案（メインの判断）

1. **背景が viewBox を覆っていない図がほかに 2 枚ある**。`<g transform="translate(…)">` の中の背景も含めて、docs/img の全 414 枚を調べた。→ メインの追加の依頼で 2 枚とも直した（末尾の「追加の依頼」の節）。
   - `docs/img/notation/half-open.svg`：viewBox の高さ 239 に対して、背景の高さが 232。下の 7 が暗い帯になり、最後の行「箱の下の小さい数は境目の番号で、l と r は境目を指す」が帯に接する。
   - `docs/img/subset-sum/shift-or.svg`：viewBox="10 0 495 482" に `width="100%"`（x = 0 から）。右の 10 が暗い帯になり、右端の「13」と箱がかかる。幅 495 は §15-8 の目安（400 程度）も超える。
   - ダークの地での描画は `<W>/render-other/` にある。#32 の続きとして直すか、別の Issue にする。notation は f1 のほかの担当（#50）が本文を触っている。
2. **再発を防ぐ検査**：check_svg.py に「最初の白い rect（g の translate を含む）が viewBox を覆うか」を足すと、この欠けを機械的に見つけられる。上の調べ方を直す前の版に当てると、今回の 4 枚と上の 2 枚の計 6 枚を見つける。インラインの数式の `\text{…}` の中の `$` も、`$$` のブロックとコードを除いて `\\text\{[^}]*\$` を探せば見つかる（直した後は全ページで 0）。f1 の静的な検査の担当に回すとよい。
3. **brief-verify.md の「スクリーンショット」に、KaTeX を確かめるときは http で配ることを足す**。file:// だと KaTeX が描かれず、katex-error が 0 と出て見落とす。
4. `gen_site.py --check` は、updated の最大が 2026-10-29 になったことによる版の差分（docs/llms.txt・overrides/assets/data/graph.json・docs/start/how-to-use.md）だけを出す。ほかの担当の updated とあわせて、メインが gen_site.py を流せば解消する。

## 追加の依頼：背景が欠けていたほかの 2 枚（完了）

メインの追加の依頼で、上の提案 1 の 2 枚を #32 と同じ直し方で直した。直したのはこの 2 枚の SVG だけで、ページの .md（start/notation・dp/subset-sum）は触っていない。

### 直したファイルと行（どれも 2 行目の背景の rect）

| ファイル | 前 | 後 |
| --- | --- | --- |
| docs/img/notation/half-open.svg（viewBox="0 0 400 239"） | `<rect width="400" height="232" …>` | `<rect x="0" y="0" width="400" height="239" …>` |
| docs/img/subset-sum/shift-or.svg（viewBox="10 0 495 482"） | `<rect width="100%" height="100%" …>` | `<rect x="10" y="0" width="495" height="482" …>` |

背景を viewBox とちょうど同じ範囲にした。直す前は、half-open の y が [0, 232] で viewBox は [0, 239]、shift-or の x が [0, 495] で viewBox は [10, 505] だった。直した後は 2 枚とも覆う。shift-or の中身は `<g transform="translate(4 0)">` の中にあるが、背景は g の外の rect なので viewBox の座標で書いた。

### 確かめたこと

- `check_svg.py --page notation`：図 2 枚・警告 0・エラー 0。
- `check_svg.py --page subset-sum`：エラー 0。警告 1 件「幅 495 が §15-8 の目安（400 程度）を超える」は直す前からあるもので、背景とは関係ない（残った点を参照）。
- `render_svg.py --bg '#1e2129' --scale 2`（`<W>/render-other/`）：2 枚とも全体が白い地で、端に暗い帯がない。直す前の版の描画は `<W>/render-other-before/` にあり、half-open は下に、shift-or は右に暗い帯が出る。
- ダークモード（`--blink-settings=preferredColorScheme=0`、scheme は slate）・幅 390px でページを撮った（`<W>/shots/32x-notation-after-dark-390.png`・`<W>/shots/32x-subset-sum-{before,after}-dark-390.png`）。後は 2 枚とも白い地の上で文字が読める。subset-sum の直す前は、右端の「13」の列と赤い箱が暗い帯にかかっていた。notation の直す前のビルド（`<W>/site-before`）では、この図が #50 の代替テキストの崩れで `<img>` になっていなかった。そのため、ページでの「前」の撮影はなく、比較は上の render_svg の画像で行う。今のビルドでは、別の担当の代替テキストの直しで `<img>` として出ている。
- 両ページとも、幅 390px（ダークモード）で `document.documentElement.scrollWidth` が 390（横ずれなし）。
- `check_pages.py --page notation`・`--page subset-sum`：エラー 0・警告 0。

### 残った点

- shift-or.svg は幅 495 で、§15-8 の目安（400 程度）と check_svg の上限 450 を超える。幅 360px の画面（本文の幅 328px）では 0.66 倍に縮み、目盛りの数字（font-size 14）は 9.3px になる（390px では 0.72 倍で約 10px）。check_svg の文字の下限 9px は満たしている。今回は背景だけを直す依頼なので、図の組み直し（2 段に分けるなど）はしていない。直すなら別の依頼にする。
