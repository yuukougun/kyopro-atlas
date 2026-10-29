# verify-render-check の報告（#61 の直しの検証）

担当：render-check が直した #61（`tools/render_pages.py`・`tests/tools/test_render_pages.py`・`tools/README.md`・`planning/style-guide.md`・報告 `render-check.md`）を、書いた担当とは別の目で確かめた。ファイルは直していない。作業用フォルダは `/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/7a638398-7759-4637-95c7-6739e8d52414/scratchpad/fix/render-check/verify-render-check`（以下 `<V>`）。

## まとめ

| Issue | 判定 | 内容 |
| --- | --- | --- |
| #61 | 直しが要る（2 点） | 道具は全ページで動き、今の main の指摘は自分の測り方と突き合わせて誤検出がなかった（エラー 27 件はすべて本物）。わざと崩した写しの 11 種のうち 10 種を見つけた。直しが要るのは、(1) 未定義の命令（`\abs`・`\floor`・打ち間違い）が赤字になる KaTeX のエラーを数えないこと、(2) 同じ回の中で、文面が同じ別の要素の指摘を 1 件にまとめてしまうこと（今の main の表は 146 件あるのに 140 件と出る） |

## 直しが要る点

### P1 未定義の命令の赤字を「KaTeX のエラー」として数えない（tools/render_pages.py 202 行）

- **理由**：katex-init.js は `throwOnError: false` で描く。このとき KaTeX は、構文の誤り（`\frac{1}{2`、`\text{$…}`）だけを `.katex-error` にし、未定義の命令は `.katex-error` を付けずに命令の名前を赤字（errorColor の #cc0000）で描く。道具は `.katex-error` だけを数え、`.katex` の中は「地の文に残った記法」でも見ないので、赤字の命令が 1 つも数えられない
- **確かめたこと**：崩した写しの T6（`$\nosuchmacro{x}$`）で、ページには赤字の「\nosuchmacro」が出る（`<V>/shots/broken-bfs-t6-dark-390.png`）が、道具の KaTeX のエラーは T1 の 1 件だけだった。同梱の KaTeX 0.16.47 を node で動かすと、`\abs{x}`・`\floor{N/2}`・`\mathrn{lcp}` はどれも `.katex-error` なしの赤字、`throwOnError: true` なら「Undefined control sequence」になる。`\abs`・`\floor` は競プロの文章で書きがちだが KaTeX にない（katex-init.js の MACROS も空）。静的な検査（check_pages）もこれを見ない。今の main には 0 件である（全ページの数式 71599 個を `throwOnError: true` で描き直して、エラー 0・赤字 0 を確かめた）
- **Issue との関係**：Issue の背景の「KaTeX のエラー（#31）」は、読者には赤字の数式として見える崩れである。道具の説明（docstring 36 行・README 99 行「`.katex-error`（赤字）」）も赤字を数えると読めるが、この種類は見落とす
- **直し方の案**：PROBE の 3.（数式）で、描けた `.arithmatex` の `.katex-html` の中に、計算した色が `rgb(204, 0, 0)`（KaTeX の errorColor）の要素があれば `katex-error` に足す（文に赤字の部分と annotation の TeX を添える）。描き直す方法（annotation の TeX を `katex.renderToString(tex, {displayMode, throwOnError: true})` で描き、ParseError の文を出す）でもよいが、そのときは katex-init.js の MACROS と同じマクロを渡す必要がある。試験の BAD_PAGE に、描いた後の形（`<span class="arithmatex" data-kp-rendered="1"><span class="katex"><span class="katex-html"><span class="mord" style="color:#cc0000">\abs</span>…`）を足し、docstring・README の説明に「未定義の命令の赤字」を足す

### P2 同じ回の中の、文面が同じ別の要素を 1 件にまとめてしまう（tools/render_pages.py 916 行）

- **理由**：`collect` の `put` は、指摘を `(種類, ページ, 節, 折りたたみ, 文)` で 1 件にまとめる。幅・配色の違う回の同じ指摘をまとめるためだが、同じ回の中で、同じ節にある文面の同じ別の要素（同じ見出しの行・同じ幅の表、同じ TeX の数式、同じ前後の文の `$`、同じ図）も 1 件になる
- **確かめたこと**：今の main の結果（`<V>/render-main.json`）で、回ごとの生の数（`results[].found`）は表が 146 件なのに、指摘は 140 件だった。patterns/circular の #overview には見出しの行が同じ 4 列 402px の表が 4 つあり（docs/patterns/circular.md 94・103・112・121 行から始まる表）、4 つとも右の 28px が隠れるが、指摘は 1 件になる。patterns/interval（3 → 1）・comb/twelvefold-way（5 → 4）も同じ。自分の測り方（下）でも隠れる表は 146 個だった。`-v` の一覧では 3 つが見えず、1 つを直して流し直すと次の 1 つが出る、をくり返すことになる。数式・`$` は今の main では重なりがなく 288・25 で正しい
- **直し方の案**：まとめるのは「同じ要素の、違う回」だけにする。たとえば `put` で回ごとに同じ key の出た回数を数え、その番号を key に足す（または PROBE で各指摘に要素の文書の順の番号を付け、key に入れる。DOM は回によらず同じなので、ライトとダークは同じ番号でまとまる）。CollectTest に「1 つの回に同じ文面の項目が 2 つ・ダークにも 2 つ」→ 指摘 2 件・それぞれ［390 ライト・390 ダーク］を足す。直したら render-check.md の数（9 行・96 行・132 行・327 行の「表 140 件」→ 146 件、警告 428 → 434 件、付録の 350・413・416 行）も直す。あわせて README 109 行・docstring 59 行の「幅・配色の違う回に出たときは 1 件にまとめ」は、幅で px が変わる種類（横ずれ・別行の数式・表）では幅ごとに別の件になる（`--width 360,390` の knapsack-undo で横ずれが 2 件）ので、文を実際に合わせる

## 確かめたこと

### 試験・静的な検査・表記

- `python3 -m unittest discover -s tests/tools`（Python 3.10.12）：81 件が通る（Python-Markdown の 2 件を飛ばす）。`.venv/bin/python -m unittest discover -s tests/tools`：81 件すべて通る。`CI=true` では test_render_pages の描く 3 件を飛ばし、残り 12 件が通る。負荷の残るとき（load average が 1 分 9.7・15 分 99）に test_render_pages を 3 回流しても毎回通った
- `python3 -W error` で 2 つのファイルを compile してエスケープの警告なし。未使用の import は試験の `import json` だけ（参考）
- `python3 tools/check_pages.py`（全ページ、worktree）：エラー 0・警告 0
- textlint：tools/README.md は HEAD と同じエラー 1・警告 8（行の番号がずれただけ）。planning/style-guide.md も HEAD と同じエラー 34・警告 65。足した文はだ・である調で、記号・コードの書き方も手引きに合う
- README・手引き §14-20 の記述（呼び方・見るものの表・CI に入れないこと・公開の前にメインが全ページを流すこと）は、道具の動きと合う（P1・P2 にかかわる 2 か所を除く）

### 今の main を全ページ（自分でビルドして流した）

`git archive c8924bb` を `<V>/main-src` に書き出し、`mkdocs build -d <V>/site-main` した（423 ページと 404.html）。`python3 tools/render_pages.py <V>/site-main --docs <V>/main-src/docs --json <V>/render-main.json -v`（`-j 4`、397 秒、load average 約 20）。結果（`<V>/render-main.txt`）は担当の報告と同じ数だった：エラー 27 件（地の文に残った記法 25 件・13 ページ、ページの横ずれ 2 件・2 ページ）、警告 428 件（別行の数式 288 件・152 ページ、表 140 件・99 ページ）。848 回とも開けて、待ち切れたもの 0、ダークはすべて slate・ライトは default、検査の JS は中央値 57ms。

### 誤検出がないか（エラーを 1 件ずつ、警告は別の測り方と突き合わせ）

- **地の文に残った `$`（25 件・13 ページ）**：c8924bb の Markdown の行（担当の報告の表の 20 行）を 1 行ずつ見た。すべて閉じの `$` の前に空白がある `$S = $` の形か、euler-phi 62〜65 行の段落に続けた `$$`（折りたたみの中）で、ビルドした HTML でも `$` がそのまま地の文に出ていた（string-basics・euler-phi・min-cost-flow で HTML を確かめた）。誤検出なし。「折りたたみの中」の印も、元の行の字下げと合う
- **ページの横ずれ（2 ページ）**：dp/knapsack-undo（9px）と graph/degree-sqrt（4px）。別の測り方でも scrollWidth が 399・394（画面 390）で、折りたたみを開く前と後で同じ。幅 390px・ダークで撮ると、knapsack-undo の箇条書きの式の末尾の「+」が右端で切れる（`<V>/shots/knapsack-undo-dark-390.png`）。誤検出なし
- **自分の測り方での突き合わせ**：道具のコードを使わず、node 24 の WebSocket で CDP を話す別の測り方（`<V>/bin/measure.mjs`。数式の右端は `.katex-html` の中身の Range の右端で測る）で、424 ページを幅 390px で測った（`<V>/m-all.jsonl`、比べたのは `<V>/bin/compare.py`）。横ずれは同じ 2 ページ・同じ px、別行の数式は 288 個が全ページで 1 つずつ同じ隠れる幅、地の文の `$` は同じ 13 ページ・同じ数、KaTeX のエラー・描かれない数式・読めない画像（415 枚）・動く図のエラー（28 個すべて描けた）・残った Mermaid は 0 で道具と同じ。表は 146 個（道具は 140 件。P2）。地の文の TeX の命令の形は、`$` の崩れのほかには cpp-io の見出し「'\n'」（とその写しの index/cpp）だけで、道具が意図して数えないもの
- **警告の小さいもの**：8px 以下の別行の数式 11 件（最小 2px）も、別の測り方で同じ幅だけ中身が隠れていた。警告なので、そのままでよい
- 見出しの anchor が日本語のもの（`#merge根どうしの差に直してつなぐ` など）は、見出しに `{#id}` がなく自動で付いた id で、道具の節の取り方は正しい

### わざと崩した写し（見つけるか）

`<V>/main-src` を `<V>/broken-src` に写し、docs/graph/bfs.md の「参考」の前に崩れを 11 個足し（`<V>/inject-bfs.md`）、下の帯が透ける SVG（`docs/img/bfs/gap.svg`、背景の rect の高さ 320・viewBox 344）を置いて、`<V>/site-broken` にビルドした。`python3 tools/render_pages.py <V>/site-broken --page bfs --docs <V>/broken-src/docs -v --json <V>/render-broken.json`（終了コード 1）。

| 崩れ | render_pages.py | 静的な検査（main の check_pages・check_svg） |
| --- | --- | --- |
| T1 `$X_i = [\text{$i$ が条件を満たす}]$` | KaTeX のエラー（Unexpected end of input…）と地の文の `$` | エラー（\text の中の $） |
| T2 箇条書きの長い式（`\max_j \left( … \right) + v_i`、\text なし） | ページの横ずれ 111px | 見つけない |
| T2b `$\min(B, \text{法が 1 に…数段多い段数})$` | ページの横ずれ 57px | 警告（長い \text） |
| T3 JS のない `data-viz="no-such-viz"` | 動く図のエラー（図のスクリプトを読み込めない）と JS のエラー（404） | エラー（JS がない） |
| T4 代替テキストの `[`（#50 の形） | 地の文の `![` と図へのリンク | エラー（角括弧） |
| T5 下 24 が透ける SVG（#32 の形） | 縁が透ける図（下 24px） | check_svg の警告 |
| T6 未定義の命令 `$\nosuchmacro{x}$` | **見つけない（P1）** | 見つけない |
| T7 `$S = $ abc` | 地の文の `$` | 見つけない |
| T8 段落に続けた `$$` | 地の文の `$` | 見つけない |
| T9 ない画像 | 読めない画像と JS のエラー（404） | エラー（ファイルがない） |
| T10 折りたたみの中の長い別行の式 | 別行の数式の警告（右の 293px、折りたたみの中） | 見つけない |
| T11 data-config の JSON の誤り | 動く図のエラー（data-config を JSON として読めない） | 見つけない |

頼まれた 3 種（\text の中の `$`・横にはみ出す長い数式・JS のない data-viz）はどれも見つけた。Issue の背景の 5 種（#50・#51・#31・#33・#32）の形もすべて出た。撮ったもの：`<V>/shots/broken-bfs-t1-light-390.png`（T1 の赤字と崩れ、T2・T2b のはみ出し）、`<V>/shots/broken-bfs-t6-dark-390.png`（T5 の暗い帯、T6 の赤字、T7〜T9）。

### 引数と出力

- `--page`：id（`bfs`）・URL のパス（`graph/bfs`・`/graph/bfs/`）・docs/ のパス（`docs/graph/bfs.md`・`graph/bfs.md`）・カンマ区切り（`bfs,dijkstra`）・`index`（トップ）・`404.html` で、どれも合うページだけを選んだ。`graph` は分野のトップを選ぶ
- `--field`：`lists`（36 ページ）・`index`（15）・`start`（4）。`--page` と一緒に使うと合わせた集合になる
- `--json`：site・chrome・variants・pages・elapsed_seconds・totals・summary・notes・findings（種類・重さ・ページ・元の Markdown・節・折りたたみ・文・出た回・data）・results（回ごとの scrollWidth・数・待てたか・時間・種類ごとの生の数）があり、読める JSON だった
- `-v` なしは警告を種類ごとに 3 件と「…ほか N 件」。終了コード：エラーがあれば 1、警告だけなら 0、`--strict` なら 1
- ないページ・ない分野・`--width abc`・`--width 100`・`--scheme dim`・ビルドのないフォルダ・ない Chrome：どれも理由を出して終了コード 1
- `--width 360,390`：同じ横ずれが幅ごとに別の件になる（P2 の最後）
- SIGTERM：途中で止めると終了コード 143 で、道具の Chrome は残らず、一時フォルダも消えた

## 参考（直さなくてよい。直すかはメインの判断）

- 画像・リンクの指摘の URL に、配ったときのポートが残る（`http://127.0.0.1:46711/kyopro-atlas/img/bfs/gap.svg` など）。Material が `src`・`href` を絶対 URL に書き換えるためで、JS のエラーと同じく `short_url` で縮めると、回をまたいで結果を比べやすい
- PROBE は Mermaid を待った後で `loading="lazy"` の画像を eager にし、画像の待ちは T0 からの 8 秒を共有する。Mermaid が描けない（ネットワークがない）ページに lazy の画像があると、読み込み中の画像を「読み込みが終わらない」と出しうる。今のサイトに lazy の画像はない
- 試験の `import json` は使っていない

## 作業の記録

- 道具の実行・別の測り方・撮影は、作業用フォルダの `python3 -m http.server`（127.0.0.1:47213）と、自分で起動したヘッドレスの Chrome（47214〜47216）で行い、終わってすべて止めた。atcoder.jp・codeforces.com は開いていない
- 途中で worktree の tools/ に一時ファイルを 1 つ誤って作り、すぐに消した（`git status` は検証の前と同じ）
- 使ったもの：`<V>/bin/measure.mjs`（別の測り方）・`<V>/bin/compare.py`（突き合わせ）・`<V>/bin/katex-strict.js` と `<V>/bin/loop.mjs`（数式の描き直し。結果は `<V>/katex-strict.jsonl`・`<V>/katex-strict2.jsonl`）・`<V>/bin/shot.mjs`（撮影）
