# 道具（tools/）

制作と検査のための独立スクリプト。MkDocs を import しない（Zensical へ移りやすくするため。設計書 §8.1・§8.3）。部品どうしの約束は [planning/interfaces.md](../planning/interfaces.md)。各スクリプトの冒頭に詳しい使い方があり、`python3 tools/<名前>.py -h` でも出る。

- 依存：PyYAML（check_noai.py は標準ライブラリだけ）。check_snippets.py は g++。手元の Python 3.10 でも、CI の Python 3.12（`uv sync --locked`）でも動く
- atcoder.jp・codeforces.com は開かない。問題の実在・題名・difficulty は ap.py（AtCoder Problems の公開データ）と台帳で確かめる
- `gen_site.py` の実行（書くほう）と commit・push はメインのセッションだけが行う（CLAUDE.md・design-review T9）。執筆のサブエージェントは `check_pages.py`・`fix_problems.py --check`・`check_snippets.py` で自分の担当を確かめてよい

## 一覧

| 道具 | すること | 書くもの |
| --- | --- | --- |
| `ap.py` | AtCoder Problems の公開データ（キャッシュ）で、問題の実在・題名・difficulty を調べる | `.cache/`（追跡外） |
| `check_catalog.py` | 目次（planning/catalog/*.yaml）を検査する | なし |
| `build_ledger.py` | 問題の台帳の下書きを作る。台帳は手で直したので作り直さない。骨格（8a）以降は catalog が凍結なので、`--check`（catalog との食い違い）は食い違いを必ず出す（予期したもの。CI では警告だけ）。台帳の確認は `check_pages.py` と `fix_problems.py --check` で行う | なし（`--check`） |
| `make_skeleton.py` | catalog から骨格のページ（stage: stub）を作る。front matter と要点の囲みだけ。あるページは上書きしない | `docs/<field>/<id>.md` |
| `gen_site.py` | front matter・本文の問題の一覧・台帳・最近の ABC から生成物を作る。`--check` で鮮度だけを見る。試験は `python3 -m unittest discover -s tests/tools`（test_gen_site.py） | `nav.yml`・`docs/<field>/index.md`・`docs/lists/`・`docs/llms.txt`・`docs/index/`・`overrides/assets/data/graph.json`・手書きのページの目印の中 |
| `check_pages.py` | ページの検査（front matter の schema・id・参照・循環・レベル・問題の一覧と台帳・囲みの外の問題リンク・```cpp・要点の囲み・draft 以降の節の anchor と別名・本文のリンク・描画の崩れ・書き方（数式の `$`・素の文字の数式・平文の欄・節の並び。下の節）） | なし |
| `fix_problems.py` | 本文の問題の一覧の各行の label・URL・difficulty を台帳から作り直す（要約は変えない）。difficulty は `（diff 1354）`、台帳で参考値（`experimental: true`）のものは `（diff 1856・参考値）`、値のないものは `（diff なし）` と書く（#5・#76。前の形の `（diff —）` も読んで直す）。`- abc300_e：要約` と書けば行を作る。`--check` は台帳の pages にあるのに本文の囲みにない問題も警告に出す | ページ（`--check` では書かない） |
| `fix_code_links.py` | 本文に取り込んだコード片（```` ```cpp ```` の中の `--8<--`）の下に、GitHub の完全なプログラムへのリンクの行を置き、取り込む範囲に `mint` が出れば同じ行に型と modint のページへのリンクを添える。地の文の `` `snippets/<id>/<名前>` `` も同じ URL へのリンクにする（#8・#72・#62。下の節）。`--check` で差分、`--stat` で件数だけ。試験は test_fix_code_links.py | ページ（`--check` では書かない） |
| `frequency.py` | front matter の frequency・frequency_evidence を最近の ABC（recent-abc.yaml）・台帳の古い ABC の数・前提として届くページの数から付け直す（catalog/README §5・手引き §17-7）。`--check` で差分、`--write` でその 2 行だけを書き換える。試験は `python3 -m unittest discover -s tests/tools` | ページの 2 行（`--write`） |
| `check_snippets.py` | コード片を設定（compilers・flags・expect・cases）どおりにコンパイル・実行して確かめる | なし |
| `render_svg.py` | 図の SVG（`docs/img/<id>/`）をヘッドレスの Chrome で幅 360px・720px の PNG にして目で確かめる。日本語のフォントがなければ WSL の Windows のフォントを足す | 一時ディレクトリ（`--out`）の PNG |
| `render_pages.py` | 作業用フォルダにビルドしたサイトを http で配り、全ページをヘッドレスの Chrome で幅 390px のライトとダークで開いて、描いたときにだけ分かる崩れを数える（#61。下の「公開の前」）。Chrome と日本語のフォントは render_svg.py と同じ。CI では動かさない。試験は test_render_pages.py（Chrome がないときと CI では、描く試験を飛ばす） | 結果の JSON（`--json`） |
| `check_svg.py` | 図の SVG の width・height の欠けと比、幅（§15-8 の目安）、スマホの幅で 9px 未満になる文字、viewBox を覆わない白い背景を警告する（`--strict` で終了コード 1） | なし |
| `check_noai.py` | URL の robots の meta と X-Robots-Tag の noai・noimageai を調べる（atcoder.jp・codeforces.com は取得せず「既知の noai」） | なし |
| `textlint_targets.py` | textlint の対象の Markdown の一覧を出す（stub と生成物を除く。package.json の `lint:text` が使う） | なし |

front matter の規則は [schema/page.schema.json](../schema/page.schema.json)（JSON Schema Draft-07）。check_pages.py は中の小さな検査器でこれを当てる（jsonschema は要らない）。

check_pages.py は本文のリンクを mkdocs build --strict と同じ見方で見る：先のファイル・anchor（ほかのページ・同じページ・用語集）があるか、stage が stub のページの節へのリンクでないか、生の `[&](auto&& self)` のような相対リンクとして解釈できない書き方でないか（コードの中は見ない）。

ビルドが通っても描くと崩れる書き方（Issue #50・#51・#61）も見る。どれもフェンス・HTML のコメント・`$$` の数式ブロック・行の中のコードの中は見ない。

| 重さ | 見るもの | 崩れ方 |
| --- | --- | --- |
| エラー | `![…](….svg)` が画像にならない。Python-Markdown 3.11 と同じ数え方を 1 行の中でまねる（コード・インラインの数式・`\[` の中は数えない。先に link を作ってから image を作る）。行の中で `![` より後ろの、図のファイルを指す `](…)` が画像の場所にならなければ崩れとする | 代替テキストの対にならない `[`・`]` で起き、図が出ずに「![…」の文字と図へのリンクが出る。半開区間は `\[1, 5)`、`(l, r]` は `(l, r\]` と書き、代替テキストは 1 行に書く |
| エラー | class に `kp-viz` があり `data-viz="名前"` を持つタグの `overrides/assets/js/viz/名前.js` がない（タグは行をまたいでよい。`--root` の木に overrides/ がなければ見ない） | 「図を表示できなかった」と出る |
| エラー | インラインの数式 `$…$` の中の `\text{…}` に `$` がある | arithmatex が中の `$` で数式を切り、KaTeX のエラーか崩れた表示になる。別行の `$$…$$` の中ならよい |
| 警告 | インラインの数式の折り返せない塊（一番外の関係・二項演算子の後で区切る）の `\text` の字数（全角を 1、半角を 0.5。上付き・下付き・分数の中は 0.7 倍）が、幅 360px の画面の入れ物に入らない。目安は段落 16.0 字・箇条書き 1 段 14.5 字・2 段 12.9 字・囲みの中 18.5 字・囲みの中の箇条書き 17.0 字で、入れ物は字下げで追う。表の行は見ない | `\text` は折り返せず、ページ全体が横にずれる |

書き方の決まり（工程11、#68・#69。手引き §4・§6・§7・§10、decisions.md の 2026-10-29）も見る。数式の検査は、フェンス・HTML のコメント・行の中のコードの中を見ない。

| 重さ | 種類 | 見るもの |
| --- | --- | --- |
| エラー | 数式にならずに残る $ | arithmatex の smart_dollar（`MD_MATH_RE`。開きの `$` の直後・閉じの `$` の直前が空白なら数式にならない）で対にならない `$`（`\$` は数えない）と、前後の行と同じ段落に入った別行の数式の `$$`。`$S = $ "a"` のように `$` が地の文に残り、KaTeX のエラーにならないので render_pages でしか見えなかったもの |
| 警告 | 要点・題の素の数式 | 要点の囲みと、囲み・折りたたみ・タブの題の、数式・コード・リンクの行き先の外にある素の文字の数式：英数字に挟まれた `^`（`10^6`）、1 字の英字の後の `_`（`X_i`。`lower_bound`・`pb_ds`・`Min_25` のような 2 字以上の語の `_` は名前とみなす）、`_{`・`^{`、エスケープした `\[`（`dp\[i]`）、2 字以上の英字の命令（`\le`）。題では素の計算量 `O(…)`（`O(N)`・`O(N log N)`。対のかっこまで）も当てる。文字参照の `&#94;` と `\_` は戻してから見る。`N = 40`・`dp[i]` のような印のない式は誤検出が多いので見ない |
| 警告 | 和文に接した数式 | `$…$` の直前・直後が和文の字（ひらがな・カタカナ（「・」を除く）・漢字）。数式の中は textlint が見ないので、ここで見る |
| 警告 | 平文の欄の TeX の記号 | front matter の title・nav_title・summary・complexity・signs・sections の title、本文の問題の行の要約（コードの外）、台帳の summary・approach（alternatives の中も）に `_{`・`^{`・2 字以上の英字の命令・`$`。aliases は見ない |
| 警告 | 節の並び | 定型の節（見出しと anchor の対応は `STANDARD_SECTIONS`。上位の手法へのつながり `next-steps` は technique ならどの帯でも定型、§17-4 の同じ役の中身の節もその位置。使い分けに近い中身の節と `acl` は中身の節で、例外は作らない）が 落とし穴 → 上位の手法へのつながり → 学ぶための資料 → 例題 → 練習問題 → 力試し → 確認問題 → 使い分け → 参考 の相対順でない。technique は中身の節が最初の定型の節より後ろにあるものも。1 ページ 1 件で、今の順と手引きの順を出す |
| 警告 | 方針の折りたたみの題 | 練習問題・力試しの節の中の `???` の題のうち「方針」を含むものが「練習の方針」「力試しの方針」（後ろに「（ABC142 E）」の形を付けてよい）でない |
| 警告 | 法を表す mod の文字 | 数式の中の `\mathrm{mod}`・`\text{mod}`・`\operatorname{mod}`（大文字の MOD も。演算子の `\bmod`・`\pmod` は当たらない）。直前が開きかっこの `(\mathrm{mod}\ k)` の形は、法の文字ではなく演算子の書き方として「`\pmod{k}` にする」と出す。1 行 1 件 |

- 数式にならずに残る `$` は、段落・箇条書きの項目・見出し・表のセル・囲みの題ごとの塊（`text_runs`）の中で数える。Python-Markdown が inline の処理をかける単位で、段落の中の改行をまたぐ数式も読む。塊は Python-Markdown 3.11 のブロックの処理（囲み・折りたたみ・タブの題と見出し・引用・箇条書き・表・字下げのコード・HTML のコメントと `<div>`・別行の数式の優先度と字下げ）のまねで切り出す。2026-10-29 の全ページで、本物の Python-Markdown（mkdocs.yml の拡張）の HTML の地の文に残る `$`（56 個・13 ページ）と一致し、render_pages の地の文に残った記法の 25 件（13 ページ）をすべて含む。試験 test_check_writing.py は、Python-Markdown があれば乱択の文書 600 個で本物と突き合わせる
- まねていないもの：閉じないフェンス（`fence_spans` と同じく最後までコードとみなす）、本文の先頭の空白だけの行、行の中の HTML のタグの属性の `$`、リンクの行き先の中の `$`（`[t](http://a/$x)`。本物では地の文に残らないが、検査は数える）、行頭の HTML のブロック（`<details><summary>$x = $</summary>` など）の中の文字（本物では `$x$` も数式にならず `$` が地の文に残るが、検査は見ない）。どれも今のページにはない
- 生成ページ（docs/<field>/index.md・docs/lists/・docs/index/）は、ほかの検査と同じく見ない。front matter の要約は md_text が `\$`・`\_` にエスケープして写すので地の文に `$` は残らず、平文の欄は元の front matter で見る（2026-10-29 に生成ページ 66 枚で新しい検査を流して 0 件）

check_svg.py は、文書の順で最初の白い rect を背景とみなし、viewBox を覆うかを見る（`width="100%"` は viewBox の幅に対してなので、viewBox の左端が 0 でなければ `x` も要る）。

道具の試験は `python3 -m unittest discover -s tests/tools`。Python-Markdown のある Python（`.venv/bin/python` か `uv run python`）では、代替テキストの数え方を本物と突き合わせる試験も走る（ないときは飛ばす）。本物の設定は、MkDocs があれば mkdocs.yml から読む。

## 工程ごとの使い方

### ふだんの検査（工程6 土台作り・工程7 試作から使う）

```sh
python3 tools/check_pages.py                 # 全ページの検査（エラーがあれば終了コード 1）
python3 tools/fix_problems.py --check        # 問題の一覧の行が台帳と合っているか（直すときは --check を外す）
python3 tools/fix_code_links.py --check --stat  # コードの下の完全なプログラムへのリンクの行が最新か（直すときは --check を外す）
python3 tools/check_snippets.py              # コード片（third_party/ac-library がないときは --acl ~/lib/ac-library-master）
python3 tools/gen_site.py --check            # 生成物が最新か（書くのはメインのセッション：python3 tools/gen_site.py）
python3 tools/check_noai.py https://…        # 新しいドメインを資料にする前に。結果は style-guide の記録へ
python3 tools/check_svg.py --page <id>       # 図の大きさと文字の大きさ（§8・§15-8）。描いたら render_svg.py で目でも確かめる
```

### 工程8a 骨格（メインのセッション）

```sh
python3 tools/make_skeleton.py --dry-run     # 作るページと、もうあるので飛ばすページ
python3 tools/make_skeleton.py               # 全ページの骨格（試作で書いたページは上書きしない）
python3 tools/gen_site.py                    # 入口・一覧・索引・graph.json・逆引きなどを作る
python3 tools/check_pages.py && python3 tools/gen_site.py --check && mkdocs build --strict
```

- 試しに一時置き場へ作るときは `make_skeleton.py --out DIR/docs`、`gen_site.py --root DIR`、`check_pages.py --root DIR`（台帳はリポジトリのものを読む）
- 横断ページの生成部分は、手書きのページに目印を置いたところにだけ書かれる（下の表）。目印のないページ・まだないページは飛ばして知らせる。試験で全部を見たいときは `make_skeleton.py --gen-markers` で横断ページの骨格に目印を足せる

### 工程8b 本文（バッチごと）

| 誰が | すること |
| --- | --- |
| 執筆者 | 担当ページを書き、stage を draft にして `check_pages.py --page <id>`・`fix_problems.py --page <id>`・`fix_code_links.py --page <id>`・`check_snippets.py snippets/<id>` を通す |
| 検証役 | `check_pages.py --page <id> -v` の警告（別名が冒頭にない、complexity が null、要点の「（執筆時に書く）」など）も見る。reviewed にすると別名の欠けはエラーになる |
| メイン | バッチの終わりに `check_pages.py`・`gen_site.py`（書く）・`gen_site.py --check`・`mkdocs build --strict` を通して commit・push |

台帳の difficulty（参考値かどうかの `experimental` も）を `ap.py` で更新したら、`fix_problems.py` で本文の diff を直し、別の commit にする（設計書 §5.4）。

### 工程10 全体の検証・定期の検査

- `frequency.py --check`（台帳・recent-abc・prerequisites を直したあと。差分があれば `--write`）
- `check_pages.py -v`（警告まで全部）、`check_snippets.py`（すべて）、`gen_site.py --check --diff`
- CI：check.yml が `check_pages.py`・`check_svg.py`（警告は出すだけ）・`python -m unittest discover -s tests/tools` と `check_snippets.py --changed --base <元>`、deploy.yml が `gen_site.py --check --diff` と `mkdocs build --strict`、snippets-weekly.yml が `check_snippets.py`（すべて）を動かす。gcc の公式コンテナには `g++-15` という名前がないので、check_snippets.py は `g++-N` がなければ版が N の `g++` を使う。コンパイラを絞るときは `--compiler g++-15`。`render_pages.py` は Chrome が要るので CI に入れず、公開の前に手元で流す（次の節）

### 公開の前（手元で。ヘッドレスの Chrome が要る）

check_pages.py・check_svg.py は Markdown と SVG を読むだけなので、描いて初めて分かる崩れは見えない（#61。KaTeX のエラー #31、横ずれ #33、JS のない動く図 #51 など）。公開の前に、作業用フォルダへビルドしたサイトを render_pages.py で描いて数える。リポジトリの `site/` には書かない（ほかの担当とぶつかる）。

```sh
uv run mkdocs build -d DIR/site                         # 作業用フォルダへビルドする
python3 tools/render_pages.py DIR/site --json DIR/render.json   # 全ページ（今は 424）を 390px のライト・ダークで。-j 4 で 4〜5 分
python3 tools/render_pages.py DIR/site --page exponent-mod --width 360,390   # 直したページだけを、幅を変えて
python3 tools/render_pages.py DIR/site --field comb -v  # その分野だけ。警告も全件
```

| 重さ | 種類 | 見るもの |
| --- | --- | --- |
| エラー | KaTeX のエラー・描かれない数式 | 構文の誤りで全体が赤字になる `.katex-error` と、描けた数式の中の赤字（KaTeX の errorColor の #cc0000）。katex-init.js は `throwOnError: false` で描くので、KaTeX にない命令（`\abs`・`\floor`・打ち間違い）と使えない命令（`\href`）は `.katex-error` にならず、命令の名前だけが赤字になる。KaTeX の印（`data-kp-rendered`）の付かない `.arithmatex` も出す |
| エラー | 地の文に残った記法 | コード・数式・図の外の文字に残った `$`・2 文字以上の TeX の命令・`![`・`](`・`**`・`{#…}` と、画像を包まない `.svg` へのリンク。KaTeX のエラーにならずに崩れた数式（閉じの `$` の前に空白がある `$S = $`、段落に続けて書いた `$$`）や、画像にならない図（#50）がここに出る |
| エラー | ページの横ずれ | `document.documentElement.scrollWidth` が画面の幅を超える。はみ出した要素（親ははみ出さず、横にスクロールする入れ物と position: fixed の中でないもの）を 5 つまで出す |
| エラー | 動く図のエラー・描かれない動く図 | `.kp-viz__error` の文と、描けた図の全ステップを送って出た「図を描けなかった」、待っても何も出ない図 |
| エラー | 読めない画像・開けないページ | 読み込みが終わらない・decode できない `<img>`。ページが 30 秒で読めないときは Chrome を起動し直して 1 回やり直す |
| 警告 | 画面の幅を超える別行の数式・表 | 数式・表の右端が、横スクロールの入れ物の見える右端を超える（右が隠れ、横にスクロールしないと読めない。#55）。Material が付ける 0.8rem の余白だけがはみ出すものは数えない |
| 警告 | 縁が透ける図 | SVG の画像を canvas に描き、端から続く透明な行・列の幅を出す（#32。ダークモードで暗い帯になる） |
| 警告 | 描かれない Mermaid の図・JS のエラー | 残った `pre.mermaid`（Mermaid は unpkg.com から読むので、ネットワークがないときも出る）と、例外・console.error・サイトの中のファイルの読み込みの失敗 |

- 開き方：sitemap.xml の URL のパス（`/kyopro-atlas/`）の下に 127.0.0.1 の空いたポートで配り、1 ページずつ開く（オリジンが違うので instant navigation は働かない）。読み込みの後、数式・動く図・Mermaid・画像・フォントを待ち、折りたたみを開いてタブの中身もすべて見せてから測る。指摘には節の anchor と「折りたたみの中」「タブの中」を添える
- 同じ要素の同じ指摘が幅・配色の違う回に出たときは 1 件にまとめて［390 ライト・390 ダーク］と添える。ページの横ずれ・別行の数式・表は px の数が文に入るので、幅が違えば別の件になる。同じ回の中の、文が同じ別の要素（見出しの行と幅が同じ表など）はまとめない。エラーがあれば終了コード 1（`--strict` なら警告でも 1）。警告は種類ごとに 3 件と件数を出し、`-v` で全件、`--json` で一覧とページごとの数を書く
- 幅は手元のフォントで測るので、実機と数 px 違うことがある。Material がリポジトリの星の数を取る api.github.com は止め、ほかのサイトの読み込みの失敗は数えない
- 見つけたものの直し方は手引き §8（図）・§6（記法）。図そのものの見た目は render_svg.py で確かめる

## fix_code_links.py が作る行（#8・#72・#62）

本文のコードは要所だけを取り込み、完全なプログラム（自前の入出力。提出用ではない）は GitHub の `snippets/` で見せる（工程11 の決定。読者向けの説明は docs/start/how-to-use.md#page-anatomy）。行は道具が作るので、手で書かない・直さない。

````markdown
```cpp
--8<-- "binomial-precompute/binom.cpp:core"
```

完全なプログラム：[`binom.cpp`](https://github.com/yuukougun/kyopro-atlas/blob/main/snippets/binomial-precompute/binom.cpp)（GitHub）。`mint` は ACL の `modint998244353`（[modint](../math/modint.md)）。
{ .kp-code-src }
````

- 置く場所：閉じのフェンスの後に空行を 1 つ挟む（挟まないと、Python-Markdown がコードの塊ごと段落に入れる）。字下げはフェンスの開きに合わせるので、折りたたみ・囲み・タブ・箇条書きの中でも同じ入れ物に入る。2 行目は attr_list の class で、p 要素に `kp-code-src` が付く
- 同じファイルを続けて取り込むとき：空行だけを挟んで続き、字下げと取り込むファイルの組が同じフェンスは 1 つの続きとみなし、最後のフェンスの下にだけ置く。地の文を挟めば、それぞれのフェンスの下に置く（節だけを読んでも、各コードの近くにリンクがある）。1 つのフェンスで同じファイルを 2 回取り込んでもリンクは 1 つ
- mint の注記：取り込む範囲（`[start:名前]`〜`[end:名前]`・行の範囲・ファイル全体。pymdownx.snippets と同じ切り出し）に `mint` という語が出れば、ファイルの `using mint = …;` の型を書く（`atcoder::` を外す。ACL の型でなければ「ACL の」を付けない）。modint のページ自身には付けない。型が読めない・2 通りあるときは「直せない」に出し、注記を付けない
- 作り直し：「完全なプログラム：」で始まり次の行が `{ .kp-code-src }` の段落は道具のものとみなし、毎回外してから置き直す。ファイル名の変更・mint の有無の変化・続きになって要らなくなった行・フェンスのない行も追う
- 見ないもの：```` ```cpp ```` 以外のフェンス（c++・cxx・cc・hpp・h は見る）、HTML のコメントの中のフェンス、`;` でエスケープした取り込み
- 地の文の `` `snippets/<id>/<名前>` ``（行の中のコード）は `` [`snippets/<id>/<名前>`](https://github.com/…/blob/main/snippets/<id>/<名前>) `` にする（フォルダは `…/tree/main/…`）。リンクの文字の中にあるものはそのまま。見出しの中・HTML のコメントのある行・ないファイルは直さず「直せない」に出す
- 試すとき：`--root DIR` で DIR/docs を直す（コード片は DIR/snippets、なければリポジトリの snippets/。`--snippets` で変えられる）

## gen_site.py が書く手書きのページの生成部分

手書きのページに `<!-- gen:begin 名前 -->` と `<!-- gen:end 名前 -->` を置くと、その間を gen_site.py が書く（フェンスの中の目印は無視する）。一覧は `python3 tools/gen_site.py --list-blocks`。

| 名前 | 中身 | 置く想定のページ |
| --- | --- | --- |
| `home-links` | ホームの目的別の入口（解けなかった問題から引く・色ごとに順に学ぶ・初めて使う の小見出しと、最初に読むページを先頭にした行） | `docs/index.md` |
| `signs-phrase`・`signs-shape` | 逆引き辞典：言い回しから（kind で5つに分ける）・立てた式の形から | `guide/reverse-index-signs.md` |
| `signs-constraint` | 逆引き辞典：制約の上限の数ごとの候補のページ | `guide/reverse-index-constraints.md` |
| `terms-kana`・`terms-latin`・`terms-shared` | 用語の索引（題名・別名・acl）：かな・漢字・記号／英数字／複数のページに当たる語 | `guide/term-index.md` |
| `roadmap-order`・`recent-positions` | 色ごとのページの列（D17）・位置ごとの頻出手法（最近30回の E・F・G） | `guide/roadmap.md` |
| `recent-abc`・`problem-sets` | 最近の ABC → ページ・問題集の問題 → ページ | `guide/problem-sets.md` |
| `problem-index-abc`・`problem-index-arc`・`problem-index-agc`・`problem-index-sets`・`problem-index-other` | 問題番号の索引（本文に載せた全問題 → ページ（役割））：ABC（回の 50 ごとの小見出し）・ARC・AGC・問題集（問題集ごとの小見出し）・そのほかのコンテスト | `guide/problem-index.md` |
| `verify-table` | ページ → Library Checker の問題 | `guide/library-design.md` |
| `version`・`fields`・`lists`・`stage-summary` | 索引の版・章の一覧（15 の分野と最後の章「一覧」）・一覧へのリンク・制作状況の表（どこに置いてもよい） | 任意 |

- `signs-constraint` の帯は、サインの文から読んだ上限の数で決める（`constraint_bound`）。読むのは「≤・<・≦・≈」の後の数と、後ろに 程度・前後・規模・級・以下・未満・以内・まで・個・回 が続く数と、「10^9〜10^18 と広い」のように範囲だけで書いた数の上端（後ろが で・と・の・読点・句点・閉じかっこ・文の終わりのときだけで、「3〜5 秒」は読まない）で、見積もりの式（`O(N√N) ≈ 10^8`・`60^4 ≈ 1.3×10^7`）・下限（「個以上」「を超える」）・式の一部の数（`N^2`・`M + 1`）は読まない。選ぶ順は、個数・回数（N・Q・K・個数・長さ・総和など）の上限を値の上限（A_i・座標・値）より先に → かっこの外の数を中の数より先に → 「≤」などで書いた数 → 後ろの語で読んだ数 → 範囲だけで書いた数 → 最初に書かれた数。読めないサインは「数の上限で分けられないもの」に入る
- `terms-latin` は、先頭に跳び先の行を置き、数字と A〜Z ごとに小見出し（`{#terms-latin-digits}`・`{#terms-latin-a}` など）を立てる
- `recent-abc`・`recent-positions` の問題は、問題の一覧の label と同じ表示名（ABC451 D. Concat Power of 2。ロードマップの列は短い ABC451 D）で書く。台帳にない問題もあるので recent-abc.yaml の id・position・title から作る。ロードマップの列の短い表示名は、狭い画面で「ABC451」と「D」が 2 行に割れないよう、間の空白を `&nbsp;` にする。ロードマップの表は 4 列で、列ごとの最小幅（5rem）のためスマートフォンの画面の右端を越えるので、問題の列が画面の内側に来るよう、数字だけの問題数を最後の列に置く
- `problem-index-*` の 1 行は「表示名 → ページ（役割）」で、例題として載せたページを先に置く。ページへのリンクは、本文の問題の行の上にある直近の見出しの anchor（例題の小見出し `#abc300_e` か一覧の節 `#practice`・`#challenge`）へ跳ぶ。ABC は先頭に跳び先の行を置き、回の 50 ごとに小見出し（`{#abc-001}`・`{#abc-050}` など）を立て、最近の ABC の表（recent-abc.yaml）の回を含む小見出しには、本文にない問題もその表で引けることの 1 文を添える。問題集は先頭に跳び先の行を置き、問題集ごとに小見出し（`{#sets-typical90}` など）を立てる。`problem-sets` の表のページの並びとリンクも同じにする
- 分野の入口（`docs/<field>/index.md`）は、章ごとのページを箇条書き（題名・レベルの小さな印 `span.kp-mini`・準備中の印・要約の 1 文目）にし、説明の後に分野の注記（`FIELD_NOTES`）と関連する案内の 1 段落（学ぶ順・使い分けの節 `FIELD_COMPARISONS`・その分野の問題の多い問題集・自作の手引き）を、章の後にほかの章の関連ページを、最後にほかの分野にある関連ページ（分野の主題の kind を持つページ）を出す。章の中は order の順のままで、order の付け方の方針は gen_site.py の entrance の注記にある
- 用語の索引の漢字で始まる語は、読みがないので最初の字の順に並ぶ（読みの表か pykakasi を足すかは工程10 の残り。planning/progress.md に記録する）
- 節（`#anchor`）へのリンクは、相手のページが draft 以降のときだけ付ける（stub のページには見出しがまだない）
- 生成物の Markdown には atcoder.jp の問題へのリンクを書かない（問題は表示名で書き、リンクは本文の問題の囲みの中だけ。interfaces.md §3・style-guide §2.5）
