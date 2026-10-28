# verify-f1-tools：描画の崩れの静的な検査（#50・#51・#61）の検証

検証した担当：verify-f1-tools（書いた f1-tools とは別）。対象は `tools/check_pages.py`・`tools/check_svg.py`・`tools/README.md`・`tests/tools/test_check_render.py`（差分は `git diff -- tools/ tests/`、担当の報告は [f1-tools.md](f1-tools.md)）。ファイルは直していない。作業用フォルダは `/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/7a638398-7759-4637-95c7-6739e8d52414/scratchpad/fix/verify-f1-tools`（以下 `<V>`）。行番号は 2026-10-29 04:20 ごろの作業ツリーのもの。

## まとめ

| Issue | 検査 | 合否 | 指摘 |
| --- | --- | --- | --- |
| #50 | 代替テキストの角括弧（エラー） | 合格 | 任意 3（A1〜A3。どれも今の docs では起きない形） |
| #51 | data-viz の JS（エラー） | 合格 | 任意 2（B1・B2） |
| #61 | インラインの `\text{…$…}`（エラー） | 合格 | なし（段落に混じった `$$` は F1 で扱う） |
| #61 | 長いインラインの `\text`（警告） | 直しが要る（軽微） | 1（C1：注釈と報告の実測が段落の場合だけで、リストの中の 15 字のはみ出しを見落とす） |
| #61 | SVG の白い背景（警告） | 合格 | 任意 1（D1） |
| 共通 | 既存の検査・試験・CI | 合格 | メインの判断 2（E1・E2） |
| 範囲の外 | 今の作業ツリーに残る数式の崩れ 27 か所 | — | F1（どの Issue にもない新しい崩れ）・F2 |

- 直しが要る点は 1 つ（C1）。任意の改善が 6 つ（A1〜A3・B1・B2・D1）
- 範囲の外の F1（13 ページで `$S = $` のような生の文字が出ている）は、メインの判断が要る

件数を再現できた。HEAD の木（`git archive HEAD docs overrides snippets` を `<V>/head` に展開）に当てた結果は次のとおりで、報告の 28・4・12・2・6 と一致した。

- `check_pages.py --root <V>/head`：エラー 44（角括弧 28・`\text` の `$` 12・JS 4）・警告 2（長い `\text`）
- `check_svg.py <V>/head/docs/img/**/*.svg`：背景の警告 6

今の作業ツリーでは、check_pages がエラー 0・警告 0、check_svg の背景の警告が 0。報告の時点で残っていた aho-corasick:143 の警告は、03:56 にほかの担当が本文を直して消えた。

## 確かめ方

- 正解の作り方：HEAD の木全体（`git archive HEAD`）を `<V>/headrepo` に展開し、.venv の mkdocs でビルドした（`<V>/site_head`）。今の作業ツリーは `uv run mkdocs build -d <V>/site_cur` でビルドした。ビルドした HTML を正として、検査の結果と突き合わせた
- 新旧の比較：HEAD の check_pages.py・check_svg.py を `<V>/old/tools/` に取り出した（schema・data・planning は symlink）。新旧の版を、HEAD の木と今の木の両方に当てた

## #50 代替テキストの角括弧：合格

### 確かめたこと

1. **本物のビルドと参照ごとに突き合わせた**（`<V>/scripts/img_truth.py`）。docs の図の参照ごとに、ビルドしたページの article に同じ SVG の `<img>` があるかを数えた
    - HEAD：参照 414・`<img>` 386・画像にならない 28（27 ページ）。28 か所の「ファイル:行」は、検査のエラー 28 件と完全に一致した
    - 今の作業ツリー：414・414・0 で、検査も 0
2. **境目の例 56 個を本物と比べた**（`<V>/scripts/edge_alt.py`）。mkdocs.yml を `mkdocs.config.load_config` で読み、同じ拡張・設定（footnotes・abbr・tables・arithmatex・inlinehilite などすべて）の Python-Markdown 3.11.2 で変換し、画像の数を検査のまね（`md_images`）と比べた。次の例では画像の数がすべて一致した
    - エスケープ：`\[`・`\\[`・`\\\[`・`\]`・`\!`・`` \` ``・`\$`
    - コードの中：`` ` ``・``` `` ```・閉じない `` ` ``・最長の列で閉じる形・`` \\` ``
    - 数式：`$…$`・`\(…\)`・`$ ` で始まる数式でない形・`$$[b$$`・代替テキストをまたぐ数式
    - リンク：代替テキストの中のリンクの `[`、リンクの中の画像
    - 画像の後ろの attr_list の `{…}`（値の中に `[`・`]`・`](` があるものも）、題の中の `[`、`<…>` の場所、脚注の参照
    - 表のセル：隣のセルの `[`、セルをまたぐ `[ ]`、`\|`
    - 囲み・リストの中

    食い違ったのは、下の A1〜A3 のほかに次の 2 つで、どちらも扱わなくてよい
    - 行の中の HTML のコメント（`![区間 <!-- [ -->](x.svg)`）：検査はコメントを除いて数えるが、本物はコメントの中の `[` も数える。書く人のいない形
    - 4 字下げのコードのブロック：検査は囲みの中身と区別できない。docs はフェンスだけを使う
3. **ランダムな行で本物と比べた**
    - 担当とは別の語の組（`{`・`}`・`"`・`'`・`<b>`・`|`・`\|`・`[^1]`・`~`・`*`・`_` などを足した）で 4 万行を作った（`<V>/scripts/fuzz_alt.py`）。行の中の画像の数が食い違ったのは 22 行（0.05%）で、どれも図の場所 `(…)` の中の引用符による（題の扱い。担当が「まねていない」と書いたもの）
    - 本物らしい代替テキスト（日本語・半開区間・閉区間・`(l, r]`・`$[l, r)$`・コード・エスケープ）で、1 行に図 1 枚のつもりの行を 3 万作った（`<V>/scripts/fuzz_alt_real.py`）。誤検出（本物で画像になるのにエラー）は 0。見落としは A1 のとおり
4. **処理の優先度と正規表現を .venv のソースで確かめた**。次のとおりで、検査のまね方は順序も置き換え方も合っている。mkdocs.yml のほかの拡張は inline の処理を足さない

    | 優先度 | 処理 | 内容 |
    | --- | --- | --- |
    | 190 | backtick | pymdownx.inlinehilite が、同じ BACKTICK_RE と find_code_spans で差し替える |
    | 189.9 | arithmatex-inline | RE_SMART_DOLLAR_INLINE・RE_BRACKET_INLINE は、検査の MD_MATH_RE と同じ |
    | 180 | escape | ESCAPED_CHARS に、arithmatex の `$` と tables の `|` を足したもの |
    | 175 | footnote | 定義された `[^id]` だけを置き換える。角括弧の対は変えない |
    | 170 | reference | docs に参照の定義がないので、文字を変えない |
    | 160・150 | link・image_link | — |

### A1（任意・推奨）見落とし：同じ行の後ろの `]`、`(l, r][…`

`tools/check_pages.py` 1101〜1115 行（`broken_images`）は、画像にならない `![` のうち次のものを「画像のつもりでない」とみなす。

- 代替テキストが後ろの `]` で閉じ、その後ろに `](` がないもの
- 閉じた直後が `[` のもの（`![alt][ref]` の形）

そのため、次の行は本物で図が出ないのに、エラーにならない。

| 行 | 本物 |
| --- | --- |
| `![区間 [1, 5)](x.svg) と閉区間の右端 (l, r]` | `![区間 <a href="x.svg">1, 5)</a> と…` になる |
| `![区間 [1, 5) の図](x.svg)。左が開いた (l, r] も同じ` | 図が出ない |
| `![区間 [1, 5)](x.svg) と ![区間 (2, 6]](y.svg)` | y.svg の `<img>` 1 枚だけになり、x.svg は代替テキストに飲まれて消える |
| `![(l, r][1, 5)](x.svg)` | 図が出ない（検査は `][` を参照の形とみなす） |
| `[![区間 [1, 5)](x.svg)](y.md)` | src が y.md の `<img>` になる（検査は「画像になる」と数える） |

本物らしい行 3 万のうち、見落としたのは次の数だった。

- 図だけの行の崩れ 6125 のうち 324（5%）
- 後ろに文がある行の崩れ 7520 のうち 1599（21%）

今の docs の 414 か所は、すべて図だけの 1 行（前後に文がない・表の中にない・行をまたがない）なので、今は起きない。ただし手引きにその約束はない（§8 は `![…](…)` の形を示すだけ）。

直し方の案（どちらか）：

1. **「画像のつもり」を図のファイルで決める**。行の中で `![` より後ろにある `](…\.(svg|png|jpe?g|gif|webp))` が、作った画像の場所の `(` になっていなければエラーにする（`md_make` が返す、作った画像の `k` と照らす）
    - `<V>/scripts/proto_target.py` で試すと、本物らしい 3 万行で見落としは 0 になり、上の 5 例をすべて拾い、A2 の誤検出も出ない
    - `<V>/scripts/proto_target_docs.py` で docs に当てると、HEAD は同じ 28 か所、今の木は 0 で、今の形と変わらない
2. **手引きで形を決める**。§8 に「図は 1 行に 1 枚だけ置き、その行に文を書かない。代替テキストを行をまたいで書かない」を足し、check_pages で `![` の行がその形かを見る

### A2（任意）誤検出：`![…]` の後ろに普通のリンクがある行

- 同じ 1112 行は、次の行を「途中の ] で閉じる」のエラーにする。本物ではどちらも画像のつもりでない
    - `![注意] は [リンク](x.md) を見る`
    - `答えは 5 だ![^1] 詳しくは [解説](x.md)`
- docs の `![` は図の 414 か所だけなので、今は起きない。A1 の案 1 にすれば消える

### A3（任意）エラーの文

- 1200 行の「（半開区間などの [ は \[ にエスケープするか、言葉にする）」は、理由が「途中の ] で閉じる」（`(l, r]` など）のときに合わない。そのときは「`]` を `\]` にする」と書くほうがよい
- 代替テキストを行をまたいで書くと、本物は画像になるのに、1 行目が「閉じない [ がある」のエラーになる（`![区間 \[1, 5)` ↵ `の図](x.svg)`）。担当の報告の「残った点」にある前提だが、エラーの文と README の表にも「代替テキストは 1 行に書く」と足すと、書く人が迷わない

## #51 data-viz の JS：合格

- HEAD で 4 件（Issue の 4 つ）、今は 0
- 名前の形と取り付け方が、viz.js と同じだった。viz.js（`overrides/assets/js/viz.js` 29・319 行）は `NAME = /^[a-z0-9][a-z0-9-]*$/` と `.kp-viz[data-viz]` を使い、検査の VIZ_NAME_RE と class の見方もこれと同じ
- docs の data-viz は 28 行で、すべて `<div class="kp-viz" data-viz="…"` の 1 行
- 書き方を変えた 12 例を試した
    - 期待どおりだったもの：属性の順・一重引用符・引用符なし・class が複数・span・data-config の中の `<`・`>`・リストの中・コメントの中・コードの中・`kp-viz-x`
    - 拾わないもの：2 行に分けたタグ（担当の報告にある前提）と、大文字の `DATA-VIZ`（1202 行の前置きの `"data-viz" in code` が大文字・小文字を区別する。書く人はいない）

### B1（任意）`--root` に overrides/ がない木

- `check_pages.py --root DIR` で DIR に overrides/ がないと、data-viz の 28 か所がすべて「JS がない」のエラーになり、終了コードは 1 になる（docs と snippets だけを写した木で確かめた）
- `--root` の説明（11 行・1533 行）は「DIR/docs と DIR/snippets」としか書いていない
- 案：1322 行で `viz_dir.is_dir()` でなければ動く図の検査を飛ばす。または、説明に「DIR/overrides/assets/js/viz も見る」と足す

### B2（任意）2 行に分けたタグ

- 担当の前提どおり、拾わない
- 案：タグを読まずに `data-viz\s*=\s*["']?([^"'\s>]+)` だけで名前を取り出す。または、手引き §8 に「div は 1 行に書く」と足す

## #61 インラインの `\text{…$…}`：合格

- **HEAD の 12 か所（9 行）はすべて正しい指摘**。HEAD のビルドの数式 71205 個を、同梱の KaTeX 0.16.47 で描いた（`<V>/scripts/katex_errors.cjs`。katex-init.js と同じ取り出し方）
    - エラーは 10 個で、すべてこの 9 行のもの
    - 残る 2 か所は、KaTeX のエラーにならないが表示は崩れている。linearity-of-expectation:78 の 2 つ目の `\text{$…$}` と、150 行の `\text{箱 $i$ が空}`（空白の後の `$` で arithmatex が数式を作らず、生の文字が出る）
    - ほかに、`\text` の中の `$` による崩れはない
    - 今の作業ツリーのビルドでは、KaTeX のエラーは 0
- **境目の 20 例で本物と合った**（`<V>/scripts/edge_text.py`）。本物の Markdown→KaTeX で、KaTeX のエラーが出るか、数式・コードの外に `$` が残れば「崩れる」とした
    - エラーにしたもの：`\text{ $i$}`・1 つの数式に 2 つ・`\textbf`・`\mbox`・`\text {…}`・`{…$…}` の入れ子・表のセル・囲みの中
    - エラーにしなかったもの：`\$`・別行の `$$…$$`（1 行・ブロック）・コード・フェンス・`\(…\)`（arithmatex が中の `$` で切らないので、正しく描ける）・`\textstyle`
- **拾わない形が 2 つある**。段落の途中の `$$…$$` と、空行なしで前の行に続く `$$` のブロックの中である。検査は `$$` を別行の数式とみなして飛ばす（1153 行と text_lines）。どちらも `$$` が別行の数式にならないこと自体が崩れなので、F1 の検査で拾うのがよい

## #61 長いインラインの `\text`：直しが要る（軽微）

### 実測

ビルドしたサイトを `python3 -m http.server` で出し（ポート 38517。使い終えて止めた）、幅 360px と 390px の iframe でページを開いた。`\text` を含むインラインの数式について、折り返せない塊（`.katex-html > .base`）の幅と、本文の右端からのはみ出しを測った（`<V>/measure.html`。`\text` の合計が 9 字以上の数式を含む 53 ページ・194 個）。

| `\text` の合計 | 塊 | 360px（本文 328px） | 390px（本文 358px） | 場所 |
| --- | --- | --- | --- | --- |
| 19.5 | 431px | 103px はみ出す | 73px はみ出す | HEAD math/exponent-mod:147（段落） |
| 17 | 346px | 48px はみ出す | 18px はみ出す | HEAD string/aho-corasick:143（リストの項目） |
| 15 | 323px | **25px はみ出す** | 収まる | HEAD string/aho-corasick:142（リストの項目） |
| 15.5 | 310px | 収まる | 収まる | 今 comb/linearity-of-expectation:141（段落） |
| 11〜13 | 249〜286px | 収まる | 収まる | lazy-segment-tree-patterns・segment-tree・counting-dedup ほか |

- HEAD の aho-corasick は、360px でも 390px でもページの横幅が 392px になる（143 行による）
- 360px のスクリーンショット（`<V>/png/head-aho-360.png`）では、142 行の「(ちょうど v で終わるパターンの数) +」が本文の右端を越えている
- 今の作業ツリーでは、測った 92 個（26 ページ）にはみ出すものはない

### C1 注釈と報告の実測が、段落の場合だけになっている

- **ページの上の字下げを入れていない**。次の 2 つは、数式を単体で描いた幅にもとづく
    - `tools/check_pages.py` 969〜973 行の注釈「合計 15〜15.5 字は 312〜317px で収まり、17 字（aho-corasick の 2 つの \text）は 340px…で溢れた」
    - 担当の報告の表（「15 字 317px（収まる）aho-corasick:142」「17 字 … 358px には収まる」）
- **リストの中では目安の内側でもはみ出す**。リストの項目は本文より約 30px 狭い。HEAD の aho-corasick:142（合計 15 字）は 360px で 25px はみ出し、143（17 字）は 390px でも 18px はみ出す。目安の 16 字では 142 を拾えない
- 直し方の案：
    1. 注釈を実測に直す。たとえば「段落では 15.5 字・310px で収まる。リストの項目では 15 字・323px でも 360px で 25px はみ出した（HEAD の aho-corasick:142）。正確な判定は描画の検査（#61 の Chrome の道具）に任せる」。報告の表も直す
    2. （任意）目安を入れ子の深さで下げる。リストの項目・囲みの中の字下げ 1 段ごとに、約 1.5 字（30px ÷ 19.4px）ずつ下げる
        - `16 − 1.5 × 段` で試すと、HEAD の 3 つ（19.5・17・15）を拾い、段落の 15.5 字（linearity:141）は拾わない
        - ただし kmp:247（2 段・14 字）も拾ってしまう。ここの `\text` は指数の中で小さく描かれて 216px なので、誤りである。添字・指数の中の `\text` を 0.7 倍で数えれば避けられる
- 警告なので CI は止めない。今の docs に、16 字を超えるものはない

## #61 SVG の白い背景：合格

- HEAD で 6 枚、今は 0。新旧の check_svg の出力の違いは、この 6 行と合計の行だけだった（前からの警告 120 件は同じで、終了コードは 0 のまま）
- HEAD の 6 枚の背景を開いて確かめた

    | 図 | HEAD の背景 |
    | --- | --- |
    | mult-table-mod6 | viewBox `300 0 280 276` に `width="100%"` の rect。x 0〜280 なので viewBox と重ならない |
    | mult-table-mod7 | 右 10 が透ける |
    | half-open | 高さ 232 < 239 で、下 7 が透ける |
    | swap-grid-cols・swap-grid-rows | 高さ 320 < 344 で、下 24 が透ける |
    | shift-or | 右 10 が透ける |

    警告が「にする」と示す rect は、6 枚とも、今の作業ツリーで直した形と同じだった
- 境目の 14 例を試した（`<V>/scripts/edge_svg.py`）
    - 期待どおりだったもの：大文字の `#FFFFFF`・`White`・空白入りの `rgb(…)`・はみ出す大きさ・カンマ区切りの viewBox・負の原点・translate でずれる形・白でない地（#fafafa）
    - 白いのに「白い rect がない」と出るもの：8 桁の `#ffffffff`、`rgb(100%,100%,100%)`
    - 透けるのに警告が出ないもの：角の丸い背景（rx）・`fill-opacity="0"`・`display="none"` の中
    - 414 枚にはどの書き方もないので、今は問題ない

### D1（任意）警告の中の幅の数

- `tools/check_svg.py` 145 行。rect が viewBox とまったく重ならないとき、透ける幅として viewBox の幅を超える数が出る。HEAD の mult-table-mod6 では「右 300 が透けて」と出るが、viewBox の幅は 280 で、実際は全面が透ける
- 案：`min(v, bw)`・`min(v, bh)` で切る。または、重ならないときは「viewBox と重ならない（全面が透ける）」と書く

## 既存の振る舞い・試験：合格

- **出力は新しい指摘のほかは変わらない**。新旧の check_pages を HEAD の木・今の木に `-v` で当てると、違いは新しい 4 種類の指摘だけだった（HEAD の木では、「エラー 0 件」「警告 0 件」の 2 行が、新しい件数と指摘の 52 行に置き換わっただけ）
- **終了コードと絞り込み**（HEAD の木。終了コードは新／旧）

    | 引数 | 終了コード | 内訳 |
    | --- | --- | --- |
    | `--page imos` | 1／0 | エラー 2 |
    | `--field comb` | 1／0 | 13（`\text` の `$` 12 と JS 1） |
    | `--page union-find` | 0／0 | — |
    | `--page aho-corasick` | 1／0 | JS 1・警告 1 |
    | `--page exponent-mod,string/aho-corasick.md` | 1／0 | — |
    | `--field math` | 1／0 | — |
    | `--page index.md` | 0／0 | — |

    今の木の全体は、終了コード 0
- **時間**：今の木で、新しい版は 4.09〜4.12 秒、古い版は 3.86〜4.01 秒。check_rendering は 0.125 秒
- **試験**：`python3 -m unittest discover -s tests/tools` は、system の Python 3.10.12 で 27 件が通る（Python-Markdown の 2 件は飛ばす）。`.venv/bin/python`（3.12.15）と `uv run python` では 27 件すべて通る
- **compile**：3 ファイルを Python 3.12 の `-W error` で compile して、SyntaxWarning は出ない
- **textlint**：`npx textlint tools/README.md` の指摘は HEAD の README と同じ 3 つで、行がずれただけ
- **check_pages の部品を使うほかの道具**
    - `fix_problems.py --check`・`frequency.py --check` は終了コード 0
    - `gen_site.py --check` は「古い 3 ファイル」（how-to-use など）と出るが、ほかの担当の本文の直しによるもの
    - ほかの道具は text_lines・prose_lines・check_rendering を使っていない
- **試験の作り方（任意）**：AgainstPythonMarkdownTest は、拡張を 6 つに絞って Markdown を作る（footnotes などがない）。今の拡張では角括弧の数え方は変わらない（上で確かめた）。拡張を足したときにずれないよう、`mkdocs.config.load_config` で mkdocs.yml から作ると確か

## CI での動き

- **check.yml の pages ジョブ**（push と pull request で動く）は、uv sync の後の Python 3.12 で `python tools/check_pages.py` を流す
    - 新しいエラーの 3 種（角括弧・JS・`\text` の `$`）は、終了コード 1 でジョブを落とす
    - 長い `\text` は警告で、`-v` でないので、ログに種類ごとの件数と 1 件目が出るだけ
- **check_svg.py と tests/tools は、どのワークフローでも動かない**（README の 83 行に書いてあるとおり）。SVG の背景の検査は手元でだけ走る
- **E1（メインの判断）check_svg を CI に足すなら**：前からの警告が 120 件あるので、`--strict` なしではログに埋もれる。背景の覆い（客観的な崩れ）だけはエラーにする（または `--strict` の対象を背景だけにする）ほうが「公開の前に」に効く
- **E2（メインの判断）CI が落ちても公開は止まらない**
    - deploy.yml は check_pages を動かさず、check.yml の結果も待たない（「どちらもデプロイを止めない」）
    - main は保護されていない（`gh api …/branches/main/protection` が 404、rulesets もない）。必須の検査がないので、CI が落ちても merge と公開は止まらない
    - #61 の「公開の前に」を仕組みで守るなら、deploy.yml の build に `python tools/check_pages.py` を足すか、main の保護で check の pages を必須にする
- **commit の順**：新しい検査は、HEAD の docs でエラー 44 件を出す。f1 のほかの担当の直しと同じ commit か、その後に入れる（担当の提案 2 に同意する）。今の作業ツリーではエラー 0

## 範囲の外で見つけたこと（新しい指摘）

### F1 今の作業ツリーに残る数式の崩れ 27 か所（13 ページ）

今の作業ツリーのビルドでは、本文（article）の数式・コードの外に `$` が 56 個残っている（`<V>/scripts/stray_dollar.py`。HEAD では 78 個）。KaTeX のエラーにも check_pages の新しい検査にもならないが、読者には `$S = $` のような生の文字が見える。

1. **閉じの `$` の前が空白のインラインの数式（26 個）**。arithmatex の smart_dollar は、閉じの `$` の前の空白を許さないので数式にしない（例：`$S = $ bacbab`）。場所は次のとおり（行番号は今のもの）

    | ページ | 行（個数） |
    | --- | --- |
    | basics/lexicographic-greedy | 153・155・157（2） |
    | basics/run-length-encoding | 51 |
    | comb/inclusion-exclusion | 227 |
    | comb/probability-dp | 143 |
    | dp/dp-phase | 149（2） |
    | ds/stack-techniques | 87・189 |
    | graph/min-cost-flow | 173 |
    | patterns/subsequence-and-substring | 240 |
    | string/string-basics | 102（2）・118（2）・151（4） |
    | string/suffix-array | 65・180 |
    | thinking/contribution | 92・210 |
    | tree/euler-tour | 239 |

2. **前の段落に空行なしで続く `$$` のブロック**：math/euler-phi の 63〜65 行（`??? note` の中）。別行の数式にならず、`$$ \varphi(n) = …` が生のまま出る（手引き §6「前後を空行にした `$$…$$`」に反する）

この崩れは、#31（`\text` の中の `$`）にも #68（平文の数式）にも入っていない。同じ部品で静的に拾える。

- 拾い方：`inline_math` で切り出した数式の閉じの `$` の前が空白なら崩れ。`$$` だけの行の前（開き）と後（閉じ）が空行でなければ崩れ
- `<V>/scripts/space_dollar.py` で試すと、26 個と 2 行をちょうど拾い（ビルドに残る `$` の 56 個 = 26 × 2 ＋ 4）、誤検出は 0 だった
- 案：check_rendering にエラーとして足し（f1-tools のファイル）、13 ページの本文を直す。直し方は、`$S =$ bacbab` のように閉じの前の空白を消すか、`$S$ = bacbab` と書く。検査を入れるなら、本文の直しと同じ commit にする

### F2 KaTeX の strict の警告 3 か所（描けてはいる）

同梱の KaTeX で描くと、strict の警告が出る数式が 3 つある。#61 の Chrome の道具で console の警告を数えるか、数式の中の和文を拾う静的な検査の候補にする。

- comb/lattice-paths:97：インラインの `$(行, 列) = (r, c)$`。手引き §6「数式の中の日本語は `\text{…}`」に反する
- comb/expectation-linear-equations:128：別行の数式の `\text{A}：`。全角の「：」が数式の中にある
- comb/minimax:55：別行の数式の `\text` の中の U+2212「−」

## 作業用フォルダに残したもの（`<V>`）

- `scripts/`
    - 本物との突き合わせ：img_truth.py（参照と `<img>`）・edge_alt.py・edge_alt2.py・fuzz_alt.py・fuzz_alt_real.py・edge_text.py・edge_svg.py
    - 試作：proto_target.py・proto_target_docs.py（A1 の案 1）・space_dollar.py（F1）
    - KaTeX と数式：katex_errors.cjs・katex_strict2.cjs・stray_dollar.py・text_dist.py
- 幅の実測：measure.html、m_360.json・m_390.json。スクリーンショット png/head-aho-360.png
- `head/`：HEAD の docs・overrides・snippets
- `headrepo/`・`site_head/`・`site_cur/`：ビルド
- `old/`：HEAD の check_pages.py・check_svg.py
