# f1-tools：描画の崩れを公開の前に見つける静的な検査（#50・#51・#61）

担当：tools/check_pages.py・tools/check_svg.py・tools/README.md・tests/tools/ だけを直した。docs/・CI・手引きは触っていない。作業用フォルダは `/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/7a638398-7759-4637-95c7-6739e8d52414/scratchpad/fix/f1-tools`（以下 `<W>`）。

## まとめ

| Issue | 足した検査 | 重さ | 直す前（HEAD 6ffc13d）の件数 | 見込み |
| --- | --- | --- | --- | --- |
| #50 | 画像の代替テキストの `[`・`]` の対応（check_pages） | エラー | 27 ページ 28 か所 | 合う |
| #51 | `data-viz` の名前の JS がない（check_pages） | エラー | 4 つ（aho-corasick・convolution-naive・inclusion-exclusion-venn・max-flow-residual） | 合う |
| #61 | インラインの数式の `\text{…$…}`（check_pages） | エラー | 2 ページ 9 行 12 か所（linearity-of-expectation 78・125・141・150、expectation-of-square 82・135・140・141・253） | 合う（#31 の場所の一覧とも一致） |
| #61 | インラインの数式の長い `\text`（check_pages） | 警告 | 2 件：exponent-mod:147、aho-corasick:143 | exponent-mod に加えて 1 件（下の「見込みと違った点」） |
| #61 | SVG の最初の白い rect が viewBox を覆わない（check_svg） | 警告 | 6 枚：mod-inverse 2 枚・sigma-manipulation 2 枚・notation/half-open・subset-sum/shift-or | 4 枚に加えて 2 枚 |

今の作業ツリー（f1 のほかの担当が直した後。この報告を書いた時点）では、check_pages はエラー 0・警告 1（aho-corasick:143 の長い `\text`）、check_svg は背景の警告 0（ほかの種類の警告 120 件は前からのもの）。

直す前の件数は、作業ツリーがほかの担当の直しの途中だったので、HEAD の docs/・overrides/・snippets/ を `git archive` で `<W>/head` に書き出し、`check_pages.py --root <W>/head` と `check_svg.py <W>/head/docs/img/**/*.svg` で数えた。

## #50 画像の代替テキストの角括弧

（この節から「残った点」までの行番号は最初の版のもの。直した後の場所は末尾の節にある）

### 直したもの

- tools/check_pages.py 947〜1114 行（部品）・1186〜1232 行（check_rendering）・1322 行（check_all から呼ぶ）、冒頭の説明 34〜38 行
- 780〜810 行：`prose_lines` を、コメント・フェンス・`$$` の外の行をそのまま返す `text_lines` と、コードと数式を空白にする部分に分けた（`prose_lines` の結果は変えていない。下の「確かめたこと」）

### 数え方

Python-Markdown 3.11.2（.venv）と pymdownx の処理を読み、同じ順序をまねた。

1. コード（`` ` ``。優先度 190。pymdownx.inlinehilite が差し替える）：開きの `` ` `` の列と同じ長さの列で閉じ、なければその先の最長の列で閉じる（`find_code_spans`）。`` ` `` の前の偶数個の `\` はエスケープした `\` に置き換わり、奇数個なら `` ` `` は開きにならない
2. インラインの数式（arithmatex。189.9）：`$…$`（smart_dollar）と `\(…\)` の正規表現をそのまま使う
3. エスケープ（180）：`\[`・`\]` など（ESCAPED_CHARS と、arithmatex が足す `$`、tables が足す `|`）
4. link（160）を作ってから image（150）を作る。どちらも `[` の後ろを `[` で +1・`]` で −1 と数え（getText）、0 になった `]` の次の `(` から `(`・`)` を数える（getLink）。作ったものは置き換えて最初から探し直す。link の文字の中では image だけをもう一度探す

1〜3 は「見つけたものを置き換えてから続きを探す」ので、後ろ読み `(?<!\\)` は置き換えた後の文字を見る（`replace_each`）。半開区間 `[1, 5)` があると、その `[` から link が先に作られて画像にならない（Issue のとおり）。

エラーにするのは、画像にならない `![` のうち次のもの：閉じない `[` がある・図の場所の `(` が閉じない・途中の `]` で閉じて後ろに `](` がある。`![alt][ref]` と、後ろに `](` のない `![…]` は画像のつもりでないとみなす。フェンス・HTML のコメント・`$$` のブロック・行の中のコードの中は見ない。1 行の中で数える（代替テキストを行をまたいで書かない前提）。docs/ に参照の定義 `[id]: url` はないので reference（170）はまねていない。

### 確かめたこと

- HEAD の全ページを本物の Python-Markdown（mkdocs.yml と同じ拡張）で変換し、ページごとの `![` の数と `<img>` の数の差を検査の結果と突き合わせた（`<W>/truth_images.py`）：参照 414・`<img>` 386・差 28（27 ページ）で、検査の 28 件（27 ページ）とページごとに一致した。今の作業ツリーは 414・414・0 で、検査も 0
- ランダムに作った行（`[`・`]`・`\[`・`` ` ``・`$`・`\(` などの組み合わせ）を本物と突き合わせた（`<W>/fuzz_alt.py`・`<W>/fuzz_count.py`）：1 枚目の画像になるかは 5 通りの種で各 2 万行の食い違い 0、行の中の画像の数は約 11 万行で食い違い 1（画像の代替テキストの中にリンクを書いた、本物の側でも崩れる行）。段落全体が `\[…\]`・`$$…$$` のブロックになる行は除いた
- 最初の版は getText だけをまね、819 件食い違った。原因は (1) link が image より先に作られること、(2) 置き換えた後の後ろ読み、(3) arithmatex の `\(…\)`、(4) `` ` `` の前の偶数個の `\` だったので、すべてまねた

## #51 JS のない動く図

### 直したもの

- tools/check_pages.py 963〜966 行（定数）・1117 行（`html_attrs`）・check_rendering の中

### 中身

行の中の HTML の開始タグ（属性の値の中の `>` も扱う）のうち、class に `kp-viz` があり `data-viz` を持つものについて、`overrides/assets/js/viz/<名前>.js` がなければエラーにする。名前が viz.js の `NAME`（`^[a-z0-9][a-z0-9-]*$`）に合わないときもエラー。`kp-viz` の class のない要素は viz.js が取り付けないので見ない。置き場は `--root` の下（`docs` の親の overrides/）。フェンス・コメント・行の中のコードの中は見ない。1 行に書いたタグだけを見る（今の docs/ の 28 か所はすべて 1 行）。

### 確かめたこと

- HEAD で 4 件（Issue の 4 つと同じ）。今の作業ツリーではほかの担当が JS を作ったので 0

## #61 インラインの数式の `\text`

### 直したもの

- tools/check_pages.py 967〜974 行（定数）・1122〜1183 行（`brace_end`・`inline_math`・`text_width`）・check_rendering の中、冒頭の説明 48 行

### 中身

インラインの数式 `$…$` を、書いた人の意図で切り出す（`\text{…}` の中の `$` では閉じない。arithmatex はそこで切るので、それを見つけるため）。`\text`・`\textrm`・`\textbf` など KaTeX の文字の命令と `\mbox`・`\hbox` を見る。1 行の `$$…$$` と、`$$` の行で挟んだブロックは見ない。

- エラー：`\text{…}` の中にエスケープしていない `$` がある（`\$` はよい）
- 警告：1 つのインラインの数式の中の `\text` の字数の合計（全角を 1、半角を 0.5）が 16 を超える

### しきい値（決めた値と理由）

**合計で全角 16 字まで**（`LONG_TEXT_ZW = 16.0`）。→ 検証（verify-f1-tools の C1）で、箇条書きの中の 15 字（HEAD の aho-corasick:142）を見逃すと分かり、入れ物ごとの目安に改めた。この節の値と表は最初の版のもの。今の値は末尾の「検証の指摘への対応」を見る。

- スマホ（360px）の本文の幅は 328px（Material の html 20px、本文 0.8rem＝16px、左右の余白 0.8rem。check_svg.py の AVAIL と同じ）。KaTeX のインラインは 16px × 1.21 ≒ 19.4px／全角 1 字なので、1 行に全角 16.9 字ぶんしか入らない。`\text` の前後の括弧などに 1 字ほど要るので 16 字にした
- 実測で確かめた：`\text` を含むインラインの数式（HEAD で 496 個）を、同梱の KaTeX 0.16.47 とヘッドレスの Chrome（render_svg.py と同じもの・同じ日本語のフォント）で描き、折り返せない塊（`.katex-html > .base`）の最大幅を測った（`<W>/measure_katex.py`）

| `\text` の合計 | 塊の幅 | 場所 |
| --- | --- | --- |
| 19.5 字 | 425px（390px の本文 358px も超える。#33 の約 58px） | math/exponent-mod.md:147 |
| 17 字 | 340px（328px を超え、358px には収まる） | string/aho-corasick.md:143 |
| 15.5 字 | 312px（収まる） | comb/linearity-of-expectation.md:141（ほかの担当が直した後の形） |
| 15 字 | 317px（収まる） | string/aho-corasick.md:142 |
| 14 字以下 | 280px 以下 | kmp:247 の 14 字は指数の中で小さく描かれ 216px |

- 1 つの `\text` の長さで見ると、14〜19 のどこにしきい値を置いても exponent-mod しか拾えず、360px で溢れる aho-corasick:143（1 つずつは最長 11.5 字だが、2 つの `\text` と `\mathbin{\text{OR}}` が同じ塊に入る）を拾えない。合計で見ると、溢れる 2 つだけを拾い、収まる 15〜15.5 字を拾わない。関係・二項演算子の後で折り返せることは見ていない（今の docs/ では合計で見ても誤りの例がない）

## #61 SVG の白い背景

### 直したもの

- tools/check_svg.py：冒頭の説明 16〜21 行、定数 38〜43 行、`fill_of`・`background`・`length`・`background_gaps`（88〜148 行）、`check` の中（165・188〜190 行）

### 中身

文書の順で最初の白い rect（`#fff`・`#ffffff`・`white`・`rgb(255,255,255)`。style が属性より強い。親の fill を継ぐ。defs・marker・pattern などの中は除く）を背景とみなし、viewBox（なければ 0 0 width height）を覆うかを見る。x・y・width・height の `%` は viewBox の幅・高さに対して計算し、ない x・y は 0。親と自分の `translate` は足し合わせ、ほかの transform の中の rect と px 以外の単位は見ない。覆わない向きと幅、直した rect を警告に出す（例：`右 10 が透けて…。<rect x="10" y="0" width="495" height="482" fill="#ffffff"/> にする`）。白い rect がないときも警告する（今は 0 件。§8 の「背景を白で塗る」の欠け）。

### 確かめたこと

- 414 枚の背景の書き方を調べた：`width="100%"` が 149 枚、x・y・width・height が 133 枚、width・height だけが 94 枚、`<g transform="translate(…)">` の中が 29 枚、x・y と % の組み合わせが 9 枚。白い rect のない図はない。transform は translate だけ
- HEAD で 6 枚（下の「見込みと違った点」）。今の作業ツリーでは 0（ほかの担当が 6 枚とも直した）

## 見込みと違った点

1. **背景（5）は 4 枚でなく 6 枚**。notation/half-open.svg（viewBox の高さ 239 に背景の高さ 232。下 7）と subset-sum/shift-or.svg（viewBox="10 0 495 482" に `width="100%"`。右 10）も覆っていない。HEAD の 2 枚をマゼンタの地で描くと（`render_svg.py --bg '#ff00ff'`）、下と右に帯が出た（`<W>/png/`）。f1-render も別に見つけて直している（f1-render.md の追加の依頼）。検査が正しい
2. **長い `\text`（4）は exponent-mod に加えて aho-corasick:143**。実測で 360px の本文（328px）を 12px 超える（390px では収まる）。今の作業ツリーにも残っている（下の提案 3）

## 確かめたこと（全体）

- `python3 -m unittest discover -s tests/tools`：27 件が通る（システムの Python 3.10 では Python-Markdown との突き合わせの 2 件を飛ばす）。`.venv/bin/python -m unittest discover -s tests/tools`：27 件すべて通る。試験は tests/tools/test_check_render.py（代替テキスト 16 例とそれを本物と突き合わせる試験・種を固定した 400 行の突き合わせ・コードの範囲・動く図・`\text` の `$`・長い `\text` の境目（16 字はよく 16.5 字で警告）・SVG の背景の覆い方・translate・継いだ fill・defs・ほかの transform・`length`）
- 既存の検査が変わっていないこと：HEAD の check_pages.py と新しい check_pages.py を、HEAD の docs と今の作業ツリーの両方に当て、`-v` の出力を比べた。違いは新しい 4 種類の指摘だけ
- `--page`・`--field` の絞り込みと終了コード：HEAD に `--page imos` でエラー 2・終了コード 1、`--field comb` でエラー 13、`--page union-find` で終了コード 0
- 時間：check_rendering は 0.12 秒（`\text` を含む行だけを数式として走査する）。check_pages 全体は 4.1〜4.7 秒で、前と揺れの範囲で同じ
- 3.12 で警告をエラーにして 3 ファイルを compile し、文字列のエスケープの誤りがないこと（冒頭の説明は raw でない）
- `npx textlint tools/README.md`：エラー 1・警告 2 で、どれも HEAD の README からあるもの（100 行目「工程10 の残り」の半角と全角の間、29・83 行目の長い文）。README は textlint の対象（docs/）の外
- `gen_site.py --check` は「古い 3 ファイル」と出るが、ほかの担当が `updated: 2026-10-29` にしたことによる版の変わりで、この担当の変更とは関係ない

## CI での扱い（調べたこと）

- check.yml の pages ジョブは `python tools/check_pages.py`（全ページ）を動かす。エラーがあれば終了コード 1 で CI が落ち、警告は種類ごとの件数と 1 件目をログに出すだけ。新しい検査の 1〜3（エラー）はこのまま CI で走って落ち、4（警告）はログに出る
- check_svg.py はどのワークフロー（check・deploy・links・snippets-weekly・zensical）でも動いていない。tests/tools の unittest も動いていない。README の CI の行にそのことを書いた
- 重さの付け方は既存に合わせた：公開すると読めない崩れ（図が出ない・赤字・数式が切れる）はエラー、目安（長い `\text`・SVG の背景や大きさ）は警告。check_svg の警告は `--strict` でなければ終了コード 0、読めない SVG だけ 1

## 提案（メインの判断）

1. **CI に足す**（check.yml の pages ジョブ。`uv sync --locked` の後なので Python-Markdown がある）。check_svg は `--strict` を付けず、check_pages と同じく警告では落とさない

    ```yaml
          - name: 図の SVG（警告は出すだけ。読めない SVG だけエラー）
            run: python tools/check_svg.py
          - name: 道具の試験（Python-Markdown との突き合わせを含む）
            run: python -m unittest discover -s tests/tools
    ```

    足したら tools/README.md の CI の行（83 行目）の「CI で動かしていない」を直す

2. **commit の順**：新しい検査は HEAD の docs/ でエラー 44 件を出す。f1 のほかの担当の直し（代替テキスト・JS・`\text`）と同じ commit か、その後に入れる（先に入れると CI が落ちる）

3. **aho-corasick:143 を直す**（担当外の本文）。`$\mathrm{mask}[v] = (\text{ちょうど } v \text{ で終わるパターンの bit}) \mathbin{\text{OR}} \mathrm{mask}[\mathrm{link}(v)]$` は 360px で 12px 溢れる。たとえば「集合：$\mathrm{mask}[v]$ は、ちょうど $v$ で終わるパターンの bit と $\mathrm{mask}[\mathrm{link}(v)]$ の OR」のように日本語を数式の外に出す。142 行（合計 15 字・317px）は収まるが、同じ形にそろえてもよい

4. **手引きに足す規則**
    - §8 の SVG：「代替テキストに `[`・`]` を書くときは `\[`・`\]` とエスケープする（半開区間 `[l, r)`・`(l, r]` は対にならず、Python-Markdown が画像として読まない。`$[l, r)$` にすると代替テキストに `\(…\)` が残るので使わない）。check_pages がエラーにする」
    - §8 の SVG：「背景の rect は viewBox と同じ `x`・`y`・`width`・`height` にする（`width="100%"` は viewBox の左上が 0 0 のときだけ覆う）。check_svg が警告する」
    - §6 の「数式の中の日本語は `\text{…}` で囲む」の後：「`\text{…}` の中に `$…$` を書かない（インラインでは中の `$` で数式が切れる。`$[i \text{ が条件を満たす}]$` のように数式を外に出す。別行の `$$…$$` の中はよい）。インラインの数式の `\text` は合計で全角 16 字までにし、長い日本語は数式の外に書く（`\text` は折り返せず、360px でページが横にずれる）」
    - §8 の動く図：「div を置くのは JS を作ってから（ないと「図を表示できなかった」と出る。check_pages がエラーにする）」

5. **#61 のヘッドレスの Chrome の道具（render-check のグループ）へ**：`<W>/measure_katex.py` の測り方は、サイトをビルドせずに使える。数式を JSON にして、同梱の KaTeX を読むページを作業用フォルダに書き、`chrome-headless-shell --dump-dom --virtual-time-budget` で描かせ、ページの中の JS が `.katex-html > .base` の幅と `.katex-error` を `<pre>` に書き出す（DevTools の接続は要らない）。インラインの数式すべてと別行の数式（#55）に広げられる。この検査の 16 字の目安も、その道具で全ページを測れば確かめ直せる

## 残った点

- 代替テキストの検査は 1 行の中で数える。表のセルごとの分け方、題（`"…"`）の引用符の中の `(`・`)`、参照の定義は、まねていない（docs/ にない書き方）
- 長い `\text` は合計の字数の目安で、`=`・`+` の後で折り返せることや、前後の数式の幅は見ない。正確な判定はヘッドレスの Chrome の道具（提案 5）に任せる
- 背景の検査は translate だけを足し合わせる。ほかの transform の中の rect と、% と px 以外の単位は調べない（今の 414 枚にはない）

## 検証の指摘への対応（2026-10-29、verify-f1-tools.md を受けて）

メインの依頼で、C1（直しが要る）と、任意の改善のうち小さく妥当なもの（A1〜A3・B1・B2、試験の作り方）を入れた。直したのは tools/check_pages.py・tools/README.md・tests/tools/test_check_render.py だけ。D1 は check_svg.py なので、今回は直していない（下の「残した点」）。

### C1 長い `\text`：入れ物ごとの目安にした

- **入れ物を字下げで追う**（`line_boxes`、check_pages.py 1339 行）。Python-Markdown の tab_length と同じく 4 字で 1 段とし、箇条書き・囲み・折りたたみ（`!!!`・`???`）・タブ（`===`）を積む。行頭の `>` は引用。表の行は見ない（表は表の中で横に送れて、ページはずれない）
- **入れ物の幅と文字**は Material の CSS（site/ の main.*.min.css）から決めた。幅 360px の画面で、本文 328px・16px。箇条書き 1 段で 1.875em（ul 0.625em＋li 1.25em）狭い。囲み・折りたたみは枠 0.075rem と余白 0.6rem で左右 27px 狭く、中の文字は 0.64rem＝12.8px。引用は 16px 狭い。タブは変わらない
- **目安** = 幅 ÷（文字 × 1.21）− 0.9 字（`text_room`。0.9 字は `\text` の前後の括弧など）。段落 16.0 字・箇条書き 1 段 14.5 字・2 段 12.9 字・囲みの中 18.5 字・囲みの中の箇条書き 1 段 17.0 字・2 重の囲み 16.8 字。段落の目安は前と同じ
- **塊ごとに数える**（`math_chunks`、1292 行）。KaTeX はインラインの数式を、一番外の関係・二項演算子の後でだけ折り返すので、そこで区切った塊ごとに `\text` を足す（前は数式全体の合計）。`{}` と `\left … \right` の中では区切らず、式の始めや演算子・開き括弧・コンマの後の `+`・`−` は単項として区切らない。`\mathbin{…}`・`\mathrel{…}` は `{}` の後で区切る
- **小さく描かれるものを縮める**（`text_extent`、1250 行）。上付き・下付きと `\frac`・`\binom` の中は 0.7 倍（2 段目から 0.5 倍）。`\frac` は分子と分母の大きいほう。`\dfrac`・`\cfrac`・`\dbinom` は縮めない。検証の案 2 で心配された kmp:247（折りたたみの中の箇条書き、指数の中の 14 字）は 9.8 字になり、拾わない
- 警告の文に、入れ物と目安を出す（例：「箇条書き 1 段の幅 298px では 14.5 字まで」）

確かめたこと：

- HEAD の docs を `git archive HEAD docs | tar -x` で `<W>/head-docs-only` に取り出して流すと、長い `\text` の警告は 3 件で、exponent-mod:147（段落 19.5 字）・aho-corasick:142（箇条書き 1 段 15 字）・aho-corasick:143（同 17 字）。overrides・snippets も入れた `<W>/head2` でも同じ
- 今の作業ツリー：エラー 0・警告 0
- 検証役の実測（`verify-f1-tools/m_360.json`。ビルドしたページの幅 360px の上での、`\text` の合計が 9 字以上の数式の塊の幅とはみ出し）と数式ごとに照らした（`<W>/compare_measure.py`）。照らせた 190 個のうち、はみ出すのは 3 個で、警告もちょうどその 3 個（誤り 0・見落とし 0）。目安に最も近い収まる数式は、今の linearity-of-expectation:141（段落 15.5 字、目安まで 0.5 字、実測 310px）
- 全ページで、入れ物の内訳は段落 223・箇条書き 1 段 61・囲み 54・2 重の囲み 63・囲みの中の箇条書き 1 段 76・2 段 2・箇条書き 2 段 2（今の作業ツリーの `\text` を含むインラインの数式 481 個）
- 前の報告の表「15 字 317px（収まる）aho-corasick:142」は、数式を本文の幅に単体で描いた幅で、ページの上では箇条書きの字下げで 25px はみ出す。検証の指摘のとおり、前の報告の表は段落の場合だけのものだった

### A1・A2 画像のつもりを図のファイルで決める

- `broken_images`（1131 行）を、検証の案 1 のとおりにした。行の中で `![` より後ろにある、図のファイル（svg・png・jpg・jpeg・gif・webp）を指す `](…)` が、作った画像の場所の `(` でなければ崩れとし、その前の最も近い `![` で報告する。理由は、その `![` からの代替テキストの `[`・`]` の差で「閉じない [ がある」「途中の ] で閉じる」、差がなければ「図の場所の ( が閉じない」か「前の画像の代替テキストに入ってしまう」
- 図のファイルを指さない `![…]`（`![注意] は [リンク](x.md) を見る`、`答えは 5 だ![^1]` など）は見ないので、A2 の誤検出は出ない。`![` のない行の図へのリンク（出典の行の .jpg など）も見ない
- 確かめたこと
    - HEAD の木の 28 か所（27 ページ）は、本物のビルドの `<img>` の欠けとページごとに一致したまま（`<W>/truth_images.py`）
    - 検証の A1 の 5 例はすべてエラーになる（試験 `test_errors_with_text_after`）
    - 検証役の `fuzz_alt_real.py`（mkdocs.yml と同じ設定の本物、本物らしい 3 万行）を新しい版に当てた。崩れ 13478 行（図だけ 6067・後ろに文 7411）をすべて拾い、見落としは 0（検証役の実行では、前の版が崩れ 13645 行のうち 1923 行を見落とした）
    - そのスクリプトで「本物で画像なのにエラー」と数えられた 142 行は、本物の出力を見ると、どれも x.svg でない場所（`src="l, r]"` など）の画像ができ、`](x.svg)` が文字のまま残る行だった。図は出ていないので、エラーにするのが正しい
    - 代替テキストを行をまたいで書いた形（`![区間 \[1, 5)` ↵ `の図](x.svg)`）は、前の版は 1 行目をエラーにしたが、今は図のファイルの行に `![` がないので見ない（本物では画像になる）

### A3 エラーの文

- 理由ごとに直し方を変えた：`[` が多いときは「半開区間などの [ は \[ にエスケープするか、言葉にする」、`]` が多いときは「(l, r] などの ] は \] にエスケープするか、言葉にする」。どの文にも「代替テキストは 1 行に書く」を足した
- 文の頭を「画像の記法が Python-Markdown で画像にならない（理由）」にした（「( が閉じない」などの角括弧でない理由にも合うように）。種類の名前「画像の代替テキストの角括弧」は変えていない
- README の表にも「代替テキストは 1 行に書く」「`(l, r]` は `(l, r\]` と書く」を足した

### B1・B2 動く図

- B1：`--root` の木に `overrides/assets/js/viz` がなければ、動く図の検査を飛ばす（check_all、1523 行）。`--root` の説明と冒頭の使い方に書いた。HEAD の docs だけの木（`<W>/head-docs-only`）では、前の版の「JS がない」28 件が出なくなった（snippets がないので「取り込むコード片がない」は出る）
- B2：ページの行をつないでタグを読むようにした（`check_viz`、1155 行）。2 行以上に分けたタグも読み、行番号はタグの始まりの行。前置きの `"data-viz" in …` を小文字にそろえたので、大文字の `DATA-VIZ` も読む

### 試験の作り方

- 本物との突き合わせ（AgainstPythonMarkdownTest）を、MkDocs があれば `mkdocs.config.load_config` で mkdocs.yml を読み、同じ 16 の拡張と設定で作るようにした（ないときは前の 6 つ）
- 試験は 34 件（前は 27 件）。足したもの：A1 の 5 例と A2 の誤検出しない例、行をまたぐ代替テキスト、エラーの文の直し方、2 行のタグ・大文字の属性、overrides のない木、入れ物ごとの境目（箇条書き 1 段・2 段・項目の中の段落・囲み・囲みの中の箇条書き・表）、塊の区切り（`=`・`\cdot`・コンマ・`\left … \right`・`{}`・単項の `−`）、指数と分数の縮め方、`line_boxes`・`math_chunks`・`text_extent` の単体
- `python3 -m unittest discover -s tests/tools`：34 件が通る（システムの Python 3.10 では本物との突き合わせの 2 件を飛ばす）。`.venv/bin/python` では 34 件すべて通る

### そのほかに確かめたこと

- `python3 tools/check_pages.py`（今の作業ツリー）：エラー 0・警告 0、終了コード 0。HEAD の木（`<W>/head2`）：エラー 44（角括弧 28・`\text` の `$` 12・JS 4）・警告 3、終了コード 1
- HEAD の check_pages.py と新しい版を、HEAD の木と今の作業ツリーに `-v` で当てると、違いは新しい種類の指摘だけ
- 時間：check_rendering は 0.19 秒、check_pages 全体は 4.2〜4.4 秒（前と同じ）
- Python 3.12 の `-W error` で check_pages.py と試験を compile して、SyntaxWarning は出ない
- `npx textlint tools/README.md`：指摘は HEAD の README からある 3 つ（29・83 行の長い文、100 行の半角と全角の間）だけ

### 直した後の主な場所（tools/check_pages.py）

| 部品 | 行 |
| --- | --- |
| 定数（入れ物の幅と文字・演算子の命令・図のファイルの場所の正規表現） | 966・984〜1004 |
| `md_images`・`broken_images`（#50） | 1120・1131 |
| `check_viz`（#51） | 1155 |
| `inline_math`・`text_extent`・`math_chunks`・`line_boxes`・`text_room`（#61） | 1198・1250・1292・1339・1379 |
| `check_rendering` | 1384 |
| check_all から呼ぶところ（overrides のない木は動く図を見ない） | 1523 |

### 残した点・提案

- D1（check_svg.py の「右 300 が透けて」の数を viewBox の幅で切る）は、今回直してよいファイルの外なので入れていない。次に check_svg.py を触るときに、`min(v, bw)`・`min(v, bh)` で切るか、重ならないときは「viewBox と重ならない（全面が透ける）」と書く
- 長い `\text` の目安は CSS から計算した幅と、0.9 字の見込みによる。関係・二項演算子の種類、`\text` 以外の数式の幅（大きな `\sum` や分数）、脚注・定義リストの字下げは見ていない。正確な判定は #61 の Chrome の道具（render-check）に任せる
- 手引きへの提案（前の「提案 4」）の §6 の文は、「インラインの数式の `\text` は合計で全角 16 字まで」を「インラインの数式の `\text` は短くし、長い日本語は数式の外に書く（`\text` は折り返せない。箇条書きの中は段落より 1.5 字ほど短く、check_pages が入れ物ごとの目安で警告する）」に読み替える
- 検証の F1（閉じの `$` の前の空白・空行なしの `$$`、13 ページ 27 か所）と F2・E1・E2 は、メインの判断を待つ（この担当では入れていない）
