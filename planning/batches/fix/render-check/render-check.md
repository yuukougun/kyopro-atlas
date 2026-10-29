# render-check の報告（#61 描画の崩れを数えるヘッドレスの Chrome の道具）

担当：#61 の残り（ヘッドレスの Chrome で全ページを描いて崩れを数える道具）。直したのは頼まれた 4 つのファイルだけである。作業用フォルダは `/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/7a638398-7759-4637-95c7-6739e8d52414/scratchpad/fix/render-check/render-check`（以下 `<W>`）。

## まとめ

| Issue | 状態 | 内容 |
| --- | --- | --- |
| #61 | 完了（道具・試験・説明） | `tools/render_pages.py` を足した。作業用フォルダにビルドしたサイトを http で配り、全ページを幅 390px のライトとダークで開いて崩れを数える。CI には入れず、公開の前に手元で流す（README・手引き §14-20）。今の main（c8924bb）に流すと、エラー 27 件（地の文に残った `$` など 25 件・13 ページ、ページの横ずれ 2 ページ）、警告 434 件（右が隠れる別行の数式 288 件・表 146 件）。出たものは直していない。検証の指摘 2 点（未定義の命令の赤字・同じ回の中の文が同じ要素のまとめ）も直した（末尾の「検証の指摘への対応」） |

静的な検査（f1 で入った check_pages・check_svg）と合わせて、Issue の「上の種類の崩れを、公開の前に検査が指摘する」を満たす。今回の道具は、静的な検査で見つからない崩れ（下の 25 件の `$` と 2 ページの横ずれ）を見つけた。

## 直したファイル

| ファイル | 行 | 内容 |
| --- | --- | --- |
| tools/render_pages.py | 新規（1119 行） | 道具。冒頭に使い方と、見るものの一覧がある（`-h` でも出る） |
| tests/tools/test_render_pages.py | 新規（450 行） | 試験 17 件（うち Chrome で描く 3 件） |
| tools/README.md | 23 行（一覧の表に 1 行）、84 行（CI の行に 1 文）、86〜111 行（新しい節「公開の前（手元で。ヘッドレスの Chrome が要る）」） | 使い方・見るものの表・開き方・まとめ方 |
| planning/style-guide.md | 349 行（§14-20 図の目視） | render_svg.py は SVG を 1 枚ずつ描くのでページの崩れは見えないこと、`render_pages.py --page <id>` で数えること、エラーは直してから報告すること、公開の前にメインが全ページを調べることを足した |

## 道具（tools/render_pages.py）

### 呼び方

```sh
uv run mkdocs build -d DIR/site                                  # 先に作業用フォルダへビルドする
python3 tools/render_pages.py DIR/site --json DIR/render.json    # 全ページを 390px のライトとダークで
python3 tools/render_pages.py DIR/site --page bfs --field graph  # 絞る（id・URL のパス・docs/ のパス。分野は URL の最初のフォルダ）
python3 tools/render_pages.py DIR/site --width 360,390 --scheme dark -j 8 -v --strict
python3 tools/render_pages.py DIR/site --docs DIR/src/docs      # 別の木からビルドしたとき、指摘に添える Markdown の場所
```

終了コードはエラーがあれば 1（`--strict` なら警告でも 1）。出力は種類ごとに「ページ#節（docs/…md）: 中身（折りたたみの中）［390 ライト・390 ダーク］」の形で、エラーは全件、警告は 3 件と件数（`-v` で全件）、最後に種類ごとの件数・ページ数の表。`--json` は指摘の一覧（種類・ページ・元の Markdown・節・中身・出た回）と、ページと回ごとの数（scrollWidth・数式・表・画像・待てたか・かかった時間）を書く。

### 見るもの

| 重さ | 種類 | 見るもの |
| --- | --- | --- |
| エラー | KaTeX のエラー | `.katex-error`。title の KaTeX の文を添える（頼まれたもの）。描けた数式の中の赤字（KaTeX の errorColor の #cc0000。未定義の命令・使えない命令）も出す（検証の P1 で足した） |
| エラー | 描かれない数式 | KaTeX の印 `data-kp-rendered` の付かない `.arithmatex`（KaTeX が読めないと全部がここに出る。katex-error だけでは 0 件と出て見落とす） |
| エラー | 地の文に残った記法 | コード・数式・図の外の文字に残った `$`・2 文字以上の TeX の命令・`![`・`](`・`**`・`{#…}`、画像を包まない `.svg` へのリンク |
| エラー | ページの横ずれ | `document.documentElement.scrollWidth` が画面の幅を超える（頼まれたもの）。はみ出した要素を右端の遠い順に 5 つまで出す |
| エラー | 動く図のエラー・描かれない動く図 | `.kp-viz__error` の文（頼まれたもの）。描けた図は全ステップを送り、「図を描けなかった」が出たステップも出す。待っても何も出ない図 |
| エラー | 読めない画像 | 読み込みが終わらない `<img>`、naturalWidth が 0 で decode できない `<img>`（頼まれたもの） |
| エラー | 開けないページ | 30 秒で読めない・検査の JS が止まった（Chrome を起動し直して 1 回やり直す） |
| 警告 | 画面の幅を超える別行の数式・表 | 右端が、横スクロールの入れ物の見える右端を超える（頼まれたもの。右が隠れる幅を出す） |
| 警告 | 縁が透ける図 | SVG の画像を canvas に描き、端から続く透明な行・列の幅（#32 の暗い帯） |
| 警告 | 描かれない Mermaid の図・JS のエラー | 残った `pre.mermaid`、例外・console.error・サイトの中のファイルの読み込みの失敗 |

頼まれた 5 つ（katex-error・ページの横幅・kp-viz__error・画面幅を超える別行の数式と表・naturalWidth 0 の img）のほかに足したものと理由：

- **地の文に残った記法**：f1-render が「壊れた数式の一部は katex-error にならず、`$`・`\text{` が地の文にそのまま出る」と書いていた。今の main でも 13 ページにあった（下）。静的な検査（check_pages）の目もすり抜けている
- **描かれない数式・動く図・Mermaid**：KaTeX や図の JS がまるごと読めないと、エラーの文が 1 つも出ず 0 件と見える。待っても描かれないものを数えれば見落とさない
- **動く図の全ステップ**：最初の状態だけでは、後のステップの render の例外が見えない。`root.kpViz.go(i)` で全部を送り、最初に戻す
- **縁が透ける図**：Issue の背景の「ダークモードで文字が読めない図（#32）」はページで描かないと見えない。check_svg は translate 以外の transform や白以外の背景を見ないので、描いた画素で見る
- **JS のエラー**：図や数式の部品が console.error に出す失敗（`kyopro-atlas: …`）と、読めない CSS・JS・画像（404）を拾う

### 決めたことと理由

- **Python にした**（node でもよいと言われた）：Chrome の探し方と日本語のフォントは `render_svg.py` の `find_chrome`・`font_env`・`INSTALL_HINT` を import して使い回す（同じ探し方・同じフォントを、写しでなく同じコードで保つ）。試験も tests/tools の unittest に置ける。npm のパッケージは足していない。CDP は標準ライブラリだけの小さな WebSocket の client（RFC 6455 のうち要る分。約 90 行）で話す。測り方は調査の measure.mjs（別行の数式・表・katex-error・横幅）を土台にした
- **Chrome は並列の数だけ起動する**（既定 4）。`--remote-debugging-port=0` で空いたポートを Chrome に選ばせ、プロファイルの `DevToolsActivePort` から読むので、ほかの担当とポートがぶつからない。プロファイルは一時フォルダで、毎回まっさら（配色の記録が残らない）。Chrome は新しいセッションで起動し、閉じるときはプロセスのグループごと止める。Ctrl-C と SIGTERM でも動いている Chrome をすべて閉じる（SIGTERM で止めて、Chrome が残らないことを確かめた）
- **配る場所**：sitemap.xml の URL のパス（`/kyopro-atlas/`）の下に、127.0.0.1 の空いたポートで配る。404.html は `/kyopro-atlas/assets/…` の絶対パスで読むので、ルートに配ると 404.html だけ崩れて見える。1 ページずつ `Page.navigate` で開くので、instant navigation は使わない
- **ダークモード**：`Emulation.setEmulatedMedia` で `prefers-color-scheme` を切り替える。Material の配色は最初の「システムに従う」なので、そのまま slate になる。結果に `data-md-color-scheme` を残し、合わなければ注意を出す（今回のダークの 424 回はすべて slate、ライトは default）
- **待ち方**：読み込みの後、数式・動く図・画像は 8 秒、Mermaid は 15 秒まで描き終わりを待ち、フォント（KaTeX の woff2）の読み込みと 2 フレームを待ってから測る。KaTeX のフォントが読めていないと、数式の幅を代わりのフォントで測ってしまうため
- **閉じた中身も測る**：折りたたみ（details）を開き、タブの中身をすべて見せてから測る。読者が開いたときの崩れも出し、指摘に「折りたたみの中」「タブの中」と添える
- **右が隠れるかで数える**：Material はスマホで数式と表の入れ物を画面の端まで広げ、中身の左右に 0.8rem（16px）の余白を付ける。scrollWidth と clientWidth を比べると、余白だけがはみ出して中身は全部見えるもの（幅 366px の数式が 390px の入れ物に入る形）まで数えた。中身（`.katex-html` の `.base`・表）の右端が入れ物の見える右端を超えるときだけ数え、隠れる幅を出す
- **api.github.com を止める**：Material がヘッダーのリポジトリの情報を取りに行き、Chrome ごとに 403（回数の制限）が出た。`Network.setBlockedURLs` で止め、ほかのサイトの読み込みの失敗も数えない（環境しだいなので）
- **地の文の TeX の命令は 2 文字以上**：cpp-io の見出し「改行文字 '\n' を出す」の `\n` は意図した文字（見出しにはバッククォートを書かない。§14-12）なので数えない
- **CI に入れない**：GitHub の ubuntu-latest には Chrome があるので、試験のうち描く 3 件は環境変数 `CI` があれば飛ばす（check.yml は `unittest discover -s tests/tools` を走らせる）。手元では Chrome があれば走る（1 秒ほど）

## 確かめたこと

- `python3 -m unittest discover -s tests/tools`：83 件が通る（システムの Python 3.10 では Python-Markdown の 2 件を飛ばす）。`.venv/bin/python -m unittest discover -s tests/tools`：83 件すべて通る（検証の指摘への対応で 2 件を足した後の数）。`CI=true` では test_render_pages の描く 3 件を飛ばす
- test_render_pages.py：WebSocket（マスク・長さ 3 通り・分けたメッセージ・ping への pong・close・時間切れの後も続きが読める・handshake の応答と同じ塊で来たフレーム・101 でない応答）、ページの一覧（assets/ と search/ を除く・404.html・元の Markdown）と絞り込み（id・パス・docs/ のパス・分野・ないもの）、sitemap のパス、配り方（パスの外は 404・フォルダへの 301・SVG の Content-Type）、まとめ方（回の違う同じ指摘を 1 件に・配色の注意・数え方）、JS のエラーの選び方。Chrome では、崩れを仕込んだページで「開けないページ」以外の 12 種類がすべて出て、よいページでは 0 件、ダークで slate になることを確かめる
- `python3 -W error` で compile して、文字列のエスケープの誤りがない
- 引数の誤り（ないページ・ない分野・ビルドのないフォルダ・`--scheme dim`・`--width abc`・ない Chrome）で、理由を出して終了コード 1
- 時間：1 ページの検査の JS は中央値 51ms。全ページ（424）を 2 つの配色で開くと、`-j 4` で 215〜298 秒（ほかの担当の負荷で揺れる）。ライトだけの 360px は `-j 6` で 62 秒
- 地の文の `$` の 25 件は、静的にも確かめた。pymdownx.arithmatex の smart_dollar の正規表現で行を左から取り、残った `$` を探す調べ（`<W>/bin/scan_dollar.py`）は 20 行・13 ページを出し、ページは道具の 13 ページと同じだった（道具は 1 行に崩れた組が 2〜4 つある行を、文字の塊ごとに数えるので 25 件）
- スクリーンショット（幅 390px）：`<W>/shots/leak-lexicographic-greedy-390.png`（「$S = $ bacbab」がそのまま出る）、`<W>/shots/leak-euler-phi-390.png`（ダーク。囲みの中に「$$ \varphi(n) = \sum_{S} …」が TeX のまま出る）、`<W>/shots/overflow-knapsack-undo-390.png`（数式の右の「+ v_i」が画面の外に出る）
- textlint：tools/README.md は HEAD と同じエラー 1・警告 8（どれも前からある。行の番号だけがずれた）。planning/style-guide.md も直す前と同じエラー 34・警告 65（349 行の「も」の重複の警告は前からある）

## 今の main に流した結果

今の main は c8924bb（#90 code-and-library のマージ）で、作業ツリー（4700618）より新しい。作業ツリーは checkout しない約束なので、`git archive c8924bb` を `<W>/main-src` に書き出し、そこで `mkdocs build -d <W>/site-main` した（16 秒）。全ページ 424（sitemap.xml の 423 と 404.html）を幅 390px のライトとダークで開いた（848 回。開けないページ 0、待ち切れなかったもの 0）。結果は `<W>/render-main.json`・`<W>/render-main.txt`。

| 重さ | 種類 | 件数 | ページ |
| --- | --- | --- | --- |
| エラー | KaTeX のエラー | 0 | 0 |
| エラー | 描かれない数式 | 0 | 0 |
| エラー | 地の文に残った記法 | 25 | 13 |
| エラー | ページの横ずれ | 2 | 2 |
| エラー | 動く図のエラー・描かれない動く図 | 0 | 0 |
| エラー | 読めない画像・開けないページ | 0 | 0 |
| 警告 | 画面の幅を超える別行の数式 | 288 | 152 |
| 警告 | 画面の幅を超える表 | 146 | 99 |
| 警告 | 縁が透ける図・描かれない Mermaid・JS のエラー | 0 | 0 |

調べた数：数式 71599（別行 632）・表 771・動く図 28・画像 415・Mermaid 10。指摘はすべてライトとダークの両方に出た（ダークだけに出たものはない）。#31・#32・#50・#51 の崩れ（f1 で直した）は 0 件で、直ったことも確かめられた。

### エラー 1：地の文に残った `$`（13 ページ・20 行。道具では 25 件）

どれも「閉じの `$` の前に空白」があり、arithmatex が数式にしない。開きと閉じの `$` を含む全体がそのまま地の文に出る（KaTeX のエラーにはならない）。euler-phi だけは別の形で、段落に続けて `$$` を書いたので、別行の数式の全体が TeX のまま出る（§6「別行は前後を空行にした `$$…$$`」に合わない）。行の番号は c8924bb のもの。

| ページ（節） | 行 | 書いてあるもの |
| --- | --- | --- |
| basics/lexicographic-greedy（#pitfalls） | 159・161・163 | `$S = $ bacbab`、`$S = $ abab`、`$S = $ ab?、$T = $ b` |
| basics/run-length-encoding（#split） | 51 | `次の図は $S = $ ` に続くコードの列 |
| comb/inclusion-exclusion（#pitfalls） | 236 | `$+N(\emptyset) = $ 全体` |
| comb/probability-dp（#vs-expected-value-dp） | 149 | `$f(\text{状態}) = $「その状態から先手が勝つ確率」` |
| dp/dp-phase（#pitfalls） | 158 | `$S = $ "a"、$T = $ "aa"` |
| ds/stack-techniques（#cancel・#abc328_d。折りたたみの中） | 90・201 | `$S = $` に続くコード、`$T = $ ABC` |
| graph/min-cost-flow（#pitfalls） | 179 | `「$B - $ 利得」` |
| math/euler-phi（#formula。折りたたみの中） | 62〜65 | 「包除原理から」の次の行に空行なしで `$$`。φ(n) の式の全体が TeX のまま出る |
| patterns/subsequence-and-substring（#practice。折りたたみの中） | 240 | `$S[i] = $ a` |
| string/string-basics（#character-mapping・#concat-order。102 以外は折りたたみの中） | 102・121・157 | `$S = $` と `$T = $` に続くコード（2 行）、`$a = $`・`$b = $`・`$a + b = $`・`$b + a = $` に続くコード |
| string/suffix-array（#definition・#kth-substring） | 65・198 | `$S = $` に続くコード、`$\ell = \mathrm{lcp}[i-1] + $ 残りの個数` |
| thinking/contribution（#sort-signs・#practice。216 は折りたたみの中） | 97・216 | `（個数）$\times a_j - $（和）`、`（個数）$\times A_j - $（和）` |
| tree/euler-tour（#abc406_f。折りたたみの中） | 248 | `$s = $` に続くコード |

直し方の例（直していない）：閉じの `$` の前の空白を消す（`$S =$ bacbab`・`$\times a_j -$（和）`）か、記号を数式の外に出す（`$S$ = bacbab`）。euler-phi は `$$` の前（と後）に空行を入れる。

### エラー 2：ページの横ずれ（2 ページ）

どちらも箇条書きの中のインラインの数式で、`\left( … \right)`・`\max( … )` のまとまりは KaTeX が途中で折り返せない。`\text` を含まないので、check_pages の長い `\text` の検査には出ない。

| ページ（節） | 行 | はみ出し | 数式 |
| --- | --- | --- | --- |
| dp/knapsack-undo（#prefix-and-suffix） | 126 | 390px で 9px（360px で 39px） | `$\max_j \left( \mathrm{pre}[i][j] + \mathrm{suf}[i + 1][W - w_i - j] \right) + v_i$` |
| graph/degree-sqrt（#push-pull） | 88 | 390px で 4px（360px で 34px） | `$\max(\mathrm{pushed}[x], \mathrm{own}[x], \max_{h \in \mathrm{hn}[x]} \mathrm{own}[h])$` |

### 警告：右が隠れる別行の数式（288 件・152 ページ）と表（146 件・99 ページ）

どちらも横にスクロールすれば読める（入れ物は Material の横スクロール）。#55（スマホの表と数式。mobile-layout のグループ）の材料になる。

- 別行の数式：右の隠れる幅は最小 2px・中央 110px・最大 502px。8px 以下は 11 件。折りたたみの中が 10 件。分野別は comb 88・dp 51・math 43・basics 27 が多い
- 表：半分（76 件）が「4 列で幅 402px」、21 件が「5 列で 502px」である。Material の表は列ごとの最小幅が 5rem（100px）なので、4 列の表は中身によらず 402px になり、右の 28px が隠れる。列の最小幅を狭い画面で小さくすれば、多くが消える見込み（kp.css。#55 の担当の判断）
- ページごとの一覧は末尾の付録にある

### 参考：幅 360px（ライトだけ）

`--width 360 --scheme light`（`<W>/render-main-360.json`）では、エラーは同じ 27 件（横ずれは同じ 2 ページで、はみ出しが 39px・34px に増える）。警告は別行の数式 328 件・166 ページ、表 167 件・108 ページに増える（表は検証の P2 を直した後の数。直した道具で流し直した。末尾の「検証の指摘への対応」）。f1-tools の報告の aho-corasick:143（360px で 12px 溢れる）は、main で書き直されていて出ない。

## 残った点

- **ブランチの元が古い**：作業ツリーは 4700618 で、main（c8924bb）は #90 で tools/README.md と planning/style-guide.md を変えた。README は #90 が CI の行の直後に「## fix_code_links.py が作る行」の節を足し、こちらは同じ場所に「### 公開の前」の節を足したので、マージで重なる。「### 公開の前」は「## 工程ごとの使い方」の中の節なので、「## fix_code_links.py が作る行」より前に置く。表の行（23 行）と手引きの §14-20（main では行の番号がずれるが、#90 はこの項目を変えていない）は重ならない見込み
- 幅は手元のフォント（WSL の Windows のフォント）で測る。数式は同梱の KaTeX のフォントなので実機と同じだが、日本語の文字の幅は実機と数 px 違うことがある（4px・9px の横ずれは実機で出ない可能性もある。360px では 34px・39px なので崩れは確か）
- Mermaid は描けたかだけを見る（Material が閉じた shadow root に描くので、中の構文のエラーの図は見えない）
- ダークモードの読みにくさは、画像の縁の透ける帯だけを見る。動く図や HTML の文字の色の対比（暗い地に暗い字）は数えていない
- 全ページで 4〜5 分かかるので、執筆者・検証役は `--page` で担当のページだけを流す想定にした

## 提案（メインの判断）

1. **エラー 2 種の直し**（担当外の本文。上の表）：地の文の `$` の 13 ページ（20 行）と euler-phi の `$$`、横ずれの 2 ページ。content-consistency か minor-content の続きに回す。直したら `render_pages.py <W>/site --page <id>` で 0 件になることを確かめられる
2. **check_pages に静的な検査を足す**（CI で落とせる）：「インラインの数式にならない `$`」（pymdownx.arithmatex の `RE_SMART_DOLLAR_INLINE` で行を左から取り、コードとエスケープの外に残った `$` をエラーにする）と、「段落に続けて書いた `$$`」。調べの `<W>/bin/scan_dollar.py` は今の main で 20 行・13 ページを出し、描いた結果と同じだった。f1 の check_rendering の続き
3. **手引き §6 に足す**：「インラインの数式は、開きの `$` の直後と閉じの `$` の直前に空白を置かない（`$S = $ ab` は数式にならず、`$` がそのまま出る。`$S =$ ab` か `$S$ = ab` と書く）」
4. **brief-verify.md の「確かめること」5**：表示の確かめに `python3 tools/render_pages.py <作業用フォルダ>/site --page <id>` を足す（数式のエラー・横ずれ・動く図のエラーを数で確かめられ、スクリーンショットは見た目を見るときだけで済む）
5. **#55 の材料**：表の警告の半分は Material の列の最小幅 5rem による（4 列 402px・5 列 502px）。別行の数式の 288 件は、`aligned` で折る・式を分けるなどの書き方の決まりが要る

## メインに判断してほしい点

1. 「地の文に残った記法」をエラーにした（今の main で 25 件。どれも読者に `$` が見える本物の崩れだった）。警告にするか
2. 既定の幅を 390px だけにした（頼まれたとおり）。check_pages の長い `\text` の目安は 360px なので、公開の前の確認は `--width 360,390` にするか（時間は 1.5 倍ほど）
3. 公開の前に流すのはメインの手順として手引き §14-20 と README に書いた。progress.md や deploy の手順の文書にも足すか

## 付録：警告の一覧（今の main、幅 390px。ライトとダークで同じ）

各行は「ページ: 節の anchor 右の隠れる幅（px）」。「・折」は折りたたみの中。詳しい中身（数式の TeX・表の見出しの行・幅）は `<W>/render-main.json`。

### 別行の数式（288 件・152 ページ）

右の隠れる幅：最小 2px・中央 110px・最大 502px。8px 以下 11 件、折りたたみの中 10 件、タブの中 0 件

- basics/bit-full-search/: #half-greedy 3
- basics/bit-operations/: #xor-properties 73
- basics/bitwise-independence/: #per-bit-contribution 108、#split-by-top-bit 231
- basics/doubling/: #table 62
- basics/exchange-argument/: #adjacent-swap 268、#concatenation 246
- basics/fractional-binary-search/: #average 87、#ratio 84、#median 188
- basics/imos/: #second-order 168、#imos-2d 201
- basics/lexicographic-greedy/: #heavy-check 70
- basics/median-absolute/: #why-median 39、#separate-axes 52
- basics/periodicity/: #partial-sums 12、#periodic-patterns 156
- basics/prefix-sum-2d/: #formula 78、#formula 14、#periodic-board 127、#higher-dimensions 104
- basics/prefix-sum-counting/: #equal-k 43、#same-remainder 73、#length-limited 122
- basics/prefix-sum/: #left-right 67
- basics/recursive-enumeration/: #pairing 22
- basics/ternary-search/: #marginal-greedy 110
- comb/bell-number/: #recurrence 120
- comb/binomial-coefficient/: #pascal 44
- comb/binomial-identities/: #parity-sum 11、#power-sums 142
- comb/binomial-precompute/: #fact-ifact 5、#composite-mod 83、#lucas 28・折、#parity-pyramid 260
- comb/binomial-prefix-sum/: #update 218、#update 102
- comb/burnside-lemma/: #cube 73
- comb/cayley-pruefer/: #degree-sequence 372、#degree-sequence 80、#sum-over-degrees 183、#sum-over-degrees 264、#sum-over-degrees 15、#with-polynomials 319
- comb/counting-basics/: #coloring 125、#coloring 326・折
- comb/counting-dedup/: #min-index 118
- comb/counting-fix-order/: #tree-order 43・折
- comb/counting-labeled-graphs/: #complement 6、#component-of-1 68、#by-size 18、#bfs-layers 40、#exactly-l 390
- comb/counting-mindset/: #exactly-vs-at-most 34、#contribution-with-binomial 148
- comb/coupon-collector/: #geometric 121、#geometric 106、#staged 111
- comb/divisor-inclusion-exclusion/: #partition 56
- comb/expectation-linear-equations/: #cycle 49、#geometric-series 85
- comb/expectation-of-square/: #difference 190、#pairs 109、#pairs 36、#variance 150、#variance 65、#abc450_g 28・折
- comb/expectation-tail-sum/: #kth-value 15、#waiting-time 90、#waiting-time 23、#continuous 24、#exactly-vs-at-least 119
- comb/expected-value-dp/: #total-expectation 39、#total-expectation 116、#total-expectation 145、#self-loop 236
- comb/generating-function-counting/: #coefficients 2、#formulas 115
- comb/grundy-number/: #definition 11、#sum 2
- comb/inclusion-exclusion-dp/: #first-obstacle 221、#first-obstacle 40、#count-violations 291、#count-violations 464、#equal-blocks 17、#tree 502、#tree 283
- comb/inclusion-exclusion/: #general 395、#general 13、#symmetric 246
- comb/lgv-lemma/: #what 345
- comb/linearity-of-expectation/: #linearity 17、#linearity 344、#sum-vs-expectation 20
- comb/minimax/: #negamax 300
- comb/mobius-function/: #definition 102、#inversion 20、#inversion 207、#inversion 26、#gcd-one 308、#gcd-one 253
- comb/partition-number/: #recurrence 64、#partition-dp 158
- comb/probability-dp/: #forward 96、#by-time 2、#random-walk 239
- comb/rational-mod/: #why 393
- comb/reflection-principle/: #two-sided 7
- comb/stars-and-bars/: #stars-bars 22
- comb/stirling-first/: #what 77、#recurrence 126、#recurrence 6
- comb/twelvefold-way/: #surjection 147、#surjection 295
- comb/zeta-mobius-subset/: #or-and-convolution 149
- dp/cht/: #lines 37
- dp/digit-dp-advanced/: #carry 29・折
- dp/dp-grid/: #largest-square 105、#top-k-on-path 254・折
- dp/dp-mod-state/: #average 297
- dp/dp-phase/: #counting-phases 36
- dp/dp-prefix-sum/: #pull-and-push 86、#same-row 219、#prefix-min 124、#two-dimensional 142
- dp/dp-reconstruction/: #trace-back 50、#lexicographic-min 180、#dp-kth-lexicographic 355
- dp/dp-segment-tree/: #split-abs 301、#dp-sliding-window 104、#dp-sliding-window 65
- dp/dp-sequence-partition/: #block-index 18、#agc031_b 67
- dp/dp-state-design/: #why-summary-works 397
- dp/dynamic-dp/: #on-trees 87、#abc246_h 55・折
- dp/exchange-argument-dp/: #compare-ratios 421
- dp/inline-dp/: #update-changes 89、#with-monotonic-stack 52
- dp/insertion-dp/: #prefix-sum 24
- dp/interval-dp-advanced/: #dfs-order-trees 146、#grundy 186
- dp/interval-dp/: #split-point 49、#ends 176、#last-operation 100、#last-operation 219、#pair-with-left-end 93
- dp/knapsack-01/: #meaning 333、#knapsack-unbounded 43、#variants 86、#knapsack-bounded 83
- dp/knapsack-undo/: #prefix-and-suffix 27
- dp/lcs/: #recurrence 163、#edit-distance 284、#count-pairs 394
- dp/lis/: #binary-search 21
- dp/monge/: #knuth-yao 5
- dp/rerooting/: #framework 242、#framework 185、#exclude-self 85
- dp/slope-trick/: #breakpoints 58
- dp/subsequence-dp/: #next-table-dp 158、#kth-subsequence 86
- dp/subset-enumeration-dp/: #submask-loop 37、#group-count 169
- dp/tree-dp/: #vertex-states 123
- ds/balanced-bst/: #treap 30
- ds/fenwick-tree/: #variants 57
- ds/global-offset/: #offset 38
- ds/lazy-segment-tree-patterns/: #2-列の積の和 139、#寄与に言い換えて単調な列を保つ 28
- ds/segment-tree-monoids/: #design-steps 78、#design-steps 341、#pattern-table 185、#non-commutative 219、#matrix 112
- ds/segment-tree-on-values/: #odd-position-sum 132
- ds/sweep-line-2d/: #rectangle-count 82、#rectangle-count 333、#window-max 321
- ds/weighted-union-find/: #merge根どうしの差に直してつなぐ 25
- geometry/argument-sort/: #half-plane-compare 24
- geometry/circle-geometry/: #geometry-optimization 119
- geometry/geometry-precision/: #double-coordinates 85
- geometry/geometry-vectors/: #cross-and-dot 268、#segment-intersection 227、#3d-geometry 252
- geometry/manhattan-chebyshev/: #rotate-45 187、#farthest-pair 66、#farthest-pair 72、#axis-independence 67
- geometry/rotation-transform/: #rotation-formula 55、#affine 92
- graph/bipartite-graph/: #odd-cycle 202
- graph/bottleneck-path/: #why-mst 88
- graph/complement-graph-bfs/: #count-by-layer 118
- graph/functional-graph/: #k-steps 142
- graph/konig-theorem/: #theorem 284
- graph/lowlink/: #ord-low 42
- graph/matrix-tree-theorem/: #laplacian 61
- graph/minimum-spanning-tree/: #query-edges 142
- graph/modular-shortest-path/: #congruence 84
- graph/project-selection/: #submodular 218
- graph/scc/: #dp-on-dag 149
- graph/small-graph-brute-force/: #isomorphism 35
- graph/steiner-tree/: #state 310
- graph/warshall-floyd/: #k-outer 28
- math/base-conversion/: #convert 41、#bijective-26 109
- math/convolution-ntt/: #split-by-bit 165
- math/crt/: #two-equations 116、#garner 196、#garner 184
- math/digit-and-mod/: #suffix-remainder 23、#suffix-remainder 54
- math/divisor-enum/: #count-and-sum 122
- math/fft-ntt/: #butterfly 198
- math/floor-sum/: #reduce 163、#swap-axes 273、#swap-axes 272、#mod-to-floor 114、#mod-to-floor 55、#abc443_g 25・折、#quiz 303・折
- math/gcd-lcm/: #prefix-suffix-gcd 67
- math/gcd-properties/: #difference-gcd 172、#difference-gcd 202、#difference-gcd 240
- math/geometric-series-mod/: #matrix 136、#repeated-digits 223
- math/hadamard-transform/: #transform 76
- math/harmonic-sum/: #why-n-log-n 39、#collect-multiples 66、#quotient-ranges 302
- math/integer-root/: #compare-sqrt 149
- math/matrix-power/: #composition 253
- math/miller-rabin/: #miller-rabin 218
- math/mod-arithmetic/: #why-mod 123
- math/mod-inverse/: #inverse-table 78
- math/multiplicative-function/: #dirichlet 210、#prime-counting 112
- math/multiplicative-order/: #bsgs-details 74
- math/sigma-manipulation/: #linearity 48、#linearity 20、#linearity 204、#group-by-value 28、#formulas 185
- math/stern-brocot/: #continued-fraction 46、#best-approximation 382
- math/xor-basis/: #xor-walk 56
- misc/parsing/: #grammar-dp 43
- patterns/bracket-sequence/: #monoid 67
- patterns/divisors-and-multiples/: #divisor-functions 74
- patterns/kth-and-median/: #properties 4
- patterns/mex/: #sum-of-mex 18
- patterns/subsequence-and-substring/: #distinct-substrings 64
- start/atcoder-system/: #rating 115
- start/notation/: #congruence-division 95
- string/hash-safety/: #birthday-bound 308、#mod-2-64 193
- string/hashing-for-sets/: #multiplicity-mod-k 249
- string/rolling-hash/: #polynomial-hash 187、#polynomial-hash 31、#collision-bound 89、#concat-and-reverse 63
- string/string-automaton-dp/: #matching-state 308、#matrix-power 396
- string/string-basics/: #concat-order 171・折
- string/subsequence-matching/: #greedy-matching 203
- string/suffix-array/: #distinct-substrings 64
- string/z-algorithm/: #prefix-extension 195
- thinking/complement/: #two-conditions 200
- thinking/contribution/: #swap-roles 170、#sort-signs 123
- tree/centroid-decomposition/: #count-through 283、#with-convolution 319
- tree/lca/: #path-aggregate 4
- tree/root-path-dfs/: #path-statistics 207
- tree/steiner-subtree/: #root-at-terminal 74
- tree/tree-centroid/: #one-or-two 147、#pair-across 137
- tree/tree-degree/: #realizable 162、#allocate-degrees 187
- tree/tree-distance/: #from-two 339
- tree/tree-edge-contribution/: #edge-pairs 71
- tree/tree-path/: #on-path 101、#meeting-point 73、#intersection 227

### 表（146 件・99 ページ）

右の隠れる幅：最小 4px・中央 28px・最大 728px。8px 以下 1 件、折りたたみの中 0 件、タブの中 0 件

よくある形（列の数, 表の幅）: 4 列 402px が 76 件、5 列 502px が 21 件、4 列 410px が 4 件、4 列 418px が 3 件、4 列 414px が 2 件、4 列 417px が 2 件

- basics/binary-search-answer/: #minimax 28
- basics/bit-operations/: #xor-properties 128
- basics/brute-force/: #small-candidates 28
- basics/complexity-estimation/: #constraint-table 36
- basics/interval-scheduling/: #counterexamples 28
- basics/two-pointers/: #two-types 128
- comb/bell-number/: #vs-subset-dp 28
- comb/binomial-coefficient/: #meanings 40
- comb/binomial-precompute/: #comparison 28
- comb/counting-dedup/: #divide 28
- comb/expectation-of-square/: #carry-three 128
- comb/grundy-number/: #definition 728
- comb/inclusion-exclusion-dp/: #weighted-sum 28
- comb/linearity-of-expectation/: #nonlinear 4
- comb/minimax/: #states 28
- comb/multinomial-coefficient/: #dp-merge 128
- comb/permutation-cycles/: #vs-adjacent 28
- comb/twelvefold-way/: #table 86、#table 28、#table 44、#table 28、#surjection 28
- cpp/acl-reading/: #components 44
- cpp/cpp-comparators/: #less-equal-pitfall 52、#priority-queue-order 28
- cpp/cpp-environment/: #options 28、#version-matrix 128、#gcc13-limits 51
- cpp/cpp-io/: #float-output 28
- cpp/cpp-lambda/: #recursive-lambda 28、#speed 128
- cpp/cpp-math-functions/: #bit-functions 44
- cpp/cpp-range-for/: #pass-by-reference 28、#range-for-forms 28
- cpp/cpp-types-literals/: #integer-types 28、#inf 40、#inf 60、#floating-point 28、#double-1e18 12
- cpp/cpp-undefined-behavior/: #other-ub 119、#detection-tools 128
- dp/bit-dp/: #tsp 43、#complexity 228
- dp/digit-dp/: #tight-flag 128
- dp/dp-basics/: #three-kinds 28
- dp/dp-dag/: #dp-as-dag 28
- dp/dp-order/: #typical-orders 28
- dp/dp-segment-tree/: #which-tool 28
- dp/dp-sequence-partition/: #last-block 41
- dp/dp-speedup-overview/: #two-directions 28、#shape-to-tool 70、#algebraic-tools 75、#convexity 28
- dp/insertion-dp/: #hakone-ekiden-dp 28
- dp/lis/: #binary-search 28
- dp/rerooting/: #exclude-self 128、#patterns 69
- dp/subsequence-dp/: #next-table-dp 28
- dp/subset-enumeration-dp/: #why-3n 28
- dp/subset-sum/: #three-forms 105
- dp/tree-dp-square/: #state-and-count 28
- ds/advanced-ds-catalog/: #table 101
- ds/inversion-number/: #count-with-bit 128
- ds/lazy-segment-tree-patterns/: #pattern-table 72
- ds/lazy-segment-tree/: #acl-standard 28、#size-in-node 43
- ds/monotonic-stack/: #4-つの向きと等号 28
- ds/persistent-data-structures/: #partial-vs-full 28
- ds/segment-tree-binary-search/: #predicate-patterns 28
- ds/segment-tree-monoids/: #pattern-table 122
- ds/segment-tree/: #what-it-does 28
- ds/sweep-line-2d/: #idea 28
- ds/wavelet-matrix/: #library 36
- geometry/geometry-vectors/: #cross-and-dot 28
- graph/graph-basics/: #representations 28
- graph/graph-construction/: #from-distances 128
- graph/graph-modeling/: #what-to-vertex 28、#what-to-edge 28、#constraints-to-edges 28、#contraction 28
- graph/k-shortest-paths/: #comparison 80
- graph/topological-sort/: #kahn-dfs 28
- graph/warshall-floyd/: #k-outer 128、#beyond-distance 28
- graph/zero-one-bfs/: #deque-invariant 28
- guide/cheatsheet/: #type-limits 40、#bit-tricks 31、#cpp 60
- guide/contest-strategy/: #time-targets 128、#time-targets 128、#solves 28
- guide/library-design/: #acl-names 320、#verify-table 184
- guide/problem-sets/: #collections 41、#typical90-stars 28、#recent-abc 76、#practice-contests 228
- guide/reverse-index-constraints/: #ops-per-second 28
- guide/roadmap/: #goal 28、#targets 128、#recent-positions-e 33、#recent-positions-f 32、#recent-positions-g 34、#practice 28
- math/divisor-count-bound/: #table 88、#pairs 28
- math/fps-basics/: #operations 36
- math/hadamard-transform/: #index-operations 59
- math/harmonic-sum/: #vs-sieve 39
- math/matrix-power/: #semiring 128、#profile-dp 28
- math/miller-rabin/: #deterministic-bases 111
- math/mod-pow/: #monoid-power 128
- math/proof-patterns/: #rearrangement 328
- math/sieve-eratosthenes/: #memory 28
- misc/interactive/: #query-budget 48
- misc/parsing/: #substring-sum 28
- misc/randomized/: #monte-carlo-las-vegas 28
- patterns/bracket-sequence/: #overview 28
- patterns/circular/: #overview 28、#overview 28、#overview 28、#overview 28
- patterns/divisors-and-multiples/: #overview 28
- patterns/grid/: #overview 28
- patterns/interval/: #overview 28、#overview 28、#overview 28
- patterns/kth-and-median/: #overview 28
- patterns/mex/: #overview 28
- patterns/operation-sequence/: #overview 28
- patterns/permutation/: #overview 28
- patterns/subsequence-and-substring/: #overview 30
- patterns/xor/: #overview 28
- start/atcoder-system/: #levels 28、#abc-format 128、#difficulty-by-position 128、#contests 128
- start/how-to-use/: #levels 28
- string/kmp/: #failure-function 428
- string/trie/: #basic-operations 28
- tree/euler-tour/: #meanings 28
- tree/lca/: #comparison 36
- tree/tree-edge-contribution/: #forest-count 28
- tree/tree-imos/: #path-add 35
- tree/tree-traversal/: #parent-depth-size 128

## 検証の指摘への対応

担当：fixup-render-check（verify-render-check.md の P1・P2）。作業用フォルダは `/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/7a638398-7759-4637-95c7-6739e8d52414/scratchpad/fix/render-check/fixup-render-check`（以下 `<X>`。`<V>` は検証の作業用フォルダ）。直したのは tools/render_pages.py・tests/tools/test_render_pages.py・tools/README.md と、この報告だけである（手引きは変えていない）。

| 指摘 | 判断 | 直したこと |
| --- | --- | --- |
| P1 未定義の命令の赤字を数えない | 正しい（自分でも確かめた） | PROBE の 3. で、描けた数式の中の赤字（KaTeX の errorColor の #cc0000）を「KaTeX のエラー」に足した |
| P2 同じ回の中の、文が同じ別の要素を 1 件にまとめる | 正しい（自分でも確かめた） | collect で、回の中で同じ文の何番目かを key に足した。今の main の表は 140 → 146 件、警告は 428 → 434 件 |

### P1 未定義の命令の赤字

- 確かめたこと：同梱の KaTeX 0.16.47 を node で動かした（`<X>/bin/katex-red.cjs`）。`throwOnError: false` では、`\nosuchmacro{x}`・`\abs{x}`・`\floor{N/2}`・`\mathrn{lcp}` が `.katex-error` なしの `<span class="mord text" style="color:#cc0000;">` になる。trust のない `\href{…}{…}` も同じ赤字になり、こちらは `throwOnError: true` でも例外にならない。そこで、検証の 2 つの案のうち、描き直して ParseError を見る案ではなく、計算した色で見る案にした（`\href` も見つかり、katex-init.js のマクロを写さずに済む）。サイトの CSS は KaTeX の色を変えず、docs/ に `\color`・`\textcolor` と `#cc0000` はない
- tools/render_pages.py：
    - 103 行：`KATEX_ERROR_COLOR = "rgb(204, 0, 0)"`（errorColor の既定 #cc0000 の、計算した色）を足し、cfg で PROBE に渡す（769 行）
    - PROBE の 3.（214〜226 行）：`.arithmatex .katex-html` の中で style に color を持つ要素のうち、計算した色が errorColor のものを数式ごとに集める。いちばん外の要素の文字（命令の名前）を `red` に入れ、文を「赤字の命令 \abs（KaTeX にない・使えない命令）」にして katex-error に足す。`text` は annotation の TeX である。数式の外の赤い字と、`\color{red}`（rgb(255, 0, 0)）は数えない
    - docstring の「KaTeX のエラー」（36〜39 行）に、描けた数式の中の赤字も出すことと、その理由（throwOnError: false）を足した
- tools/README.md 99 行：「`.katex-error`（赤字）」を、構文の誤りの `.katex-error` と、描けた数式の中の赤字（KaTeX にない命令・使えない命令）に書き直した
- 試験（tests/tools/test_render_pages.py）：
    - BAD_PAGE に、KaTeX 0.16.47 が `\abs{x}` を描いた形（annotation つき。335〜339 行の INLINE・RED_ABS）を足した。test_details で、katex-error が 2 件（`\abs{x}` の赤字と `\frac{` の構文の誤り）になり、`red` が `["\abs"]` になることを確かめる
    - OK_PAGE に、`\color{red}` の数式と、数式の外の `#cc0000` の字を足した。どちらも数えないことを test_clean_pages が確かめる
    - KatexColorTest（301 行。Chrome なしで、CI でも走る）：katex-init.js が errorColor を変えず `throwOnError: false` であること、同梱の KaTeX の errorColor の既定が #cc0000 であることを確かめる。どれかが変われば KATEX_ERROR_COLOR を見直す合図になる
- 崩した写しでの確かめ：検証の `<V>/site-broken` の bfs に流すと、T6 が「graph/bfs/#t6（docs/graph/bfs.md）: \nosuchmacro{x} — 赤字の命令 \nosuchmacro（KaTeX にない・使えない命令）［390 ライト・390 ダーク］」と出た（`<X>/render-broken.txt`）。検証のときの結果と比べて、違うのはこの 1 件だけである（ポートの番号を除いて突き合わせた）。今の main は 0 件のままで、検証の描き直し（赤字 0）と合う

### P2 同じ回の中の、文が同じ別の要素

- tools/render_pages.py の collect（930 行〜）：put に回ごとの Counter を渡し、key を（種類・ページ・節・折りたたみ・文・回の中で同じ文の何番目か）にした（942 行）。ほかの回とは、同じ番目どうしでまとめる（DOM は回によらず同じなので、ライトとダークの n 番目は同じ要素である）。検証の 2 つ目の案（PROBE で要素に番号を付ける）より変える所が少なく、文が違う指摘のまとめ方は前と変わらない
- 文の直し：docstring（62〜64 行）・collect の docstring・README 109 行の「同じ指摘が幅・配色の違う回に出たときは 1 件にまとめ」を「同じ要素の同じ指摘」にした。px の数が文に入る 3 種類（ページの横ずれ・別行の数式・表）は幅が違えば別の件になること、同じ回の中の文が同じ別の要素はまとめないことも足した（幅ごとに別の件になるのは前からの動きで、文を動きに合わせた）
- 試験：CollectTest.test_same_text_in_one_run（263 行）。390 のライトとダークに文が同じ表が 2 つずつ、360 のライトに px の違う表が 2 つ → 指摘 4 件で、390 の 2 件はそれぞれ［390 ライト・390 ダーク］、360 の 2 件は［360 ライト］になる。BAD_PAGE の表は、見出しの行と幅が同じ 2 つにし（TABLE を 2 回）、test_details で wide-table が 2 件になることを確かめる
- 今の main：表は 146 件・99 ページになった。増えたのは patterns/circular の #overview（1 → 4 件）・patterns/interval の #overview（1 → 3 件）・comb/twelvefold-way の #table（3 → 4 件）の 6 件で、どれも 4 列 402px（右の 28px が隠れる）である。前の結果の指摘は 1 件もなくならなかった

### この報告で直した行

9 行（まとめ）・17〜18 行（行の数・試験の数）・40 行（KaTeX のエラーの見るもの）・74 行（試験の数）・96 行・132 行・137 行（4 列 402px の数）・142 行（360px の表の数）・327 行・331 行と、付録の 350・413・416 行である。付録は `<X>/bin/appendix.py` で `<X>/render-main.json` から作り直した。同じ道具で検証の `<V>/render-main.json`（前のまとめ方）から作ると前の付録と一字も違わないことを、先に確かめた（中央の値の丸めだけ合わせた）。

### 確かめたこと

- `python3 -m unittest tests.tools.test_render_pages`：17 件が通る。直す前の形に戻した写し（`<X>/mut-p1`・`<X>/mut-p2`）では、P1 で test_details が、P2 で test_same_text_in_one_run と test_details が落ちる（試験が 2 つの誤りを見分ける）
- `python3 -m unittest discover -s tests/tools`：83 件が通る（Python-Markdown の 2 件を飛ばす）。`.venv/bin/python` では 83 件すべてが通る。`CI=true` では描く 3 件を飛ばし、KatexColorTest を含む 14 件が通る
- `python3 -W error` で 2 つのファイルを compile して、エスケープの警告がない
- textlint：tools/README.md は HEAD と同じエラー 1・警告 8 で、直した 99・109 行には出ない
- 今の main（c8924bb。作業ツリーより新しい）を `git archive` で `<X>/main-src` に書き出し、作業ツリーの .venv の mkdocs で `<X>/site-main` にビルドした（16 秒。pyproject.toml・uv.lock・mkdocs.yml は作業ツリーと同じ）。全 424 ページを幅 390px のライトとダークで流した（848 回・495 秒。ほかの担当の負荷で load average は 10〜38。`<X>/render-main.json`・`<X>/render-main.txt`）
    - エラー 27 件：地の文に残った記法 25 件・13 ページ、ページの横ずれ 2 件・2 ページ。KaTeX のエラーは、赤字の命令を含めて 0 件
    - 警告 434 件：別行の数式 288 件・152 ページ、表 146 件・99 ページ
    - 指摘 461 件はすべてライトとダークの両方に出た。回ごとの生の数（results[].found）と指摘の数は、すべての種類とページで同じになった（`<X>/bin/check_json.py`）
    - 開けないページ 0、待ち切れなかったもの 0、ダークはすべて slate・ライトは default、検査の JS は中央値 58ms
- 幅 360px のライトだけ（`<X>/render-main-360.json`、83 秒）：エラー 27 件（横ずれは同じ 2 ページで 39px・34px）、警告は別行の数式 328 件・166 ページ、表 167 件・108 ページ（前の 161 件は P2 の誤りによる）

### 残した点（検証の「参考」。直していない）

- 画像・リンクの指摘の URL に、配ったときのポートが残る（`http://127.0.0.1:…/kyopro-atlas/img/…`）。1 回の実行の中のまとめには響かないが、別々に流した JSON どうしは比べにくい。`short_url` で縮めるかはメインの判断
- lazy の画像の待ち方（今のサイトに lazy の画像はない）と、試験の使っていない `import json` もそのままにした

### 提案（メインの判断）

- `\abs`・`\floor`・`\ceil`・`\norm` は KaTeX にない（同梱の 0.16.47 で `throwOnError: true` にすると Undefined control sequence。`\lvert x \rvert`・`\lfloor x \rfloor`・`\lceil x \rceil` はある）。手引き §6 に書くか、katex-init.js の MACROS に足すか（どちらも担当外）。今の main では使われていない
