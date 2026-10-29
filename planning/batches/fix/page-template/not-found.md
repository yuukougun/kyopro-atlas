# not-found の報告（#73 404 のページ）

直したのは `overrides/404.html`（新しく作った）だけである。#73 は完了した。kp.css・main.html・生成物は触っていない。

作業用フォルダは `/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/7a638398-7759-4637-95c7-6739e8d52414/scratchpad/fix/page-template/not-found`（以下 `<W>`）。直す前のビルドは `<W>/site-before`、直した後は `<W>/root/kyopro-atlas`、撮った画像と結果は `<W>/shots/`、確かめに使ったスクリプトは `<W>/tools/` にある。

## #73 404 のページを日本語にし、入口へのリンクを置く（完了）

### 直したファイルと行

`overrides/404.html`（新規・66 行）

| 行 | 内容 |
| --- | --- |
| 1 | `{% extends "main.html" %}`。Material の 404.html と同じ継承で、main.html の上書きも 404 で効く |
| 3–15 | 方針の注記（base の扱い・入口の引き方・target="_self" の理由・Zensical） |
| 17–19 | `htmltitle` ブロック：タブの題名を `ページが見つからない - kyopro-atlas` にする（前は `kyopro-atlas` だけ） |
| 21–66 | `content` ブロック（Material の 404.html が上書きするのと同じブロック） |
| 22 | ホームの URL。`base_url` の末尾の `/` をそろえる（Zensical 対策。後述） |
| 23–28 | 入口の id と短い説明：how-to-use・term-index・reverse-index-signs・knowledge-map |
| 29–30 | 見出しと案内文 |
| 31–33 | 検索のボタン（`hidden`。下の script が語を入れて出す） |
| 34–42 | 入口の一覧。ホームと、`nav.pages` から front matter の id で引いた 4 ページ（main.html と同じ引き方。nav にないものは出さないので、リンク切れを出さない） |
| 43–65 | 検索語を作る script（インライン） |

### 出す内容

- 見出し「ページが見つからない」
- 「開いた URL にページがない（404）。URL の打ち間違いか、ページの移動が考えられる。」
- ボタン「「no-such-page」をサイト内で検索」（`/kyopro-atlas/?q=no-such-page` へ。Material の `md-button md-button--primary`）
- 見出し「入口から探す」と一覧
  - ホーム：教材の概要と、入口の一覧
  - この教材の使い方：教材の引き方の順と、レベル・記録の意味
  - 用語の索引：手法の名前・別名・英語名から引く
  - 逆引き辞典（言い回しから）：問題文の言い回しから、疑う手法を引く
  - 知識マップ：ページの前提関係をたどる

リンクの文字はページの題名（`nav_title` か `title`。main.html と同じ）から取り、説明は手で書いた。説明はホームの「入口」の言い回しに合わせた。kp.css は変えず、Material の `md-button` と、インラインの style 2 つ（ボタンに `overflow-wrap: anywhere`、「をサイト内で検索」に `white-space: nowrap`）で済ませた。

### サイトの base（/kyopro-atlas/）の扱い

- GitHub Pages は、`/kyopro-atlas/` の下の存在しない URL に、深さによらず同じ 404.html を返す（URL はそのまま）。そのため相対パスは使えない。公開中のサイトで確かめた：`https://yuukougun.github.io/kyopro-atlas/graph/no-such-page/` は状態 404 で、いまの Material の既定の 404（`<h1>404 - Not found</h1>`・`"base": "/kyopro-atlas/"`・資源は `/kyopro-atlas/assets/…`）を返す（`<W>/live-404.html`）
- MkDocs 1.6.1 の `mkdocs/commands/build.py` の `_build_template`（68–76 行）は、エラーのテンプレートだけ `base_url = urlsplit(config.site_url or '/').path`（＝ `/kyopro-atlas/`）にし、page を None にする。`| url`（`utils.normalize_url`、205–216 行）は page が None なら `posixpath.join(base_url, path)` を返すので、入口のリンクは `/kyopro-atlas/guide/term-index/` のような絶対パスになる
- ホームには `base_url` を使った。`nav.homepage.url | url` だと `/kyopro-atlas/.` になる（直す前のビルドで、Material のヘッダーのロゴのリンクがそうなっている）。ブラウザでは同じ所へ解決されるが、見た目のために避けた
- Zensical 0.0.71 では `base_url` が `/kyopro-atlas`（末尾の `/` なし）だった。そのままではホームが GitHub Pages の転送を挟むので、22 行目で `/` をそろえた（Python のメソッドを呼ばず、main.html でも使っている切り出し `[-1:]` で書いた）

### `?q=` と instant navigation（target="_self" の理由）

- Material 9.7.7 の検索は、`?q=` を検索の部品を組み立てるときにだけ読む（ソースマップの `components/search/query/index.ts` の `watchSearchQuery`）。検索の部品は最初の読み込みで 1 回だけ組み立てる（`bundle.ts` の `control$`）
- instant navigation は sitemap にあるサイト内のリンクを横取りして中身だけを差し替えるので、ふつうのリンクでは `?q=` が読まれず、検索が開かない。`target` のあるリンクは横取りしない（`integrations/instant/index.ts` 104 行目 `if (el.target || ev.metaKey || ev.ctrlKey) return EMPTY`）。そこで検索のリンクに `target="_self"` を付け、ふつうの読み込みにした
- 入口の 5 本のリンクは target を付けず、instant navigation のまま速く開く

### 検索語の作り方（script）

- `location.pathname` からホームのパス（`/kyopro-atlas/`）を除き、最後の空でない部分を取る。`decodeURIComponent` で戻し（壊れた `%` の並びはそのまま使う）、末尾の `.html`・`.htm`・`.md` を除く。`index` ならその前の部分を使う。語がなければボタンは隠したままにする
- 語は `textContent` で入れ、URL は `URLSearchParams` で作るので、HTML としては解釈されない
- script が動かないときはボタンを出さない（Material の検索も script がないと動かない）。案内と入口の一覧は出る
- ハイフンは空白に変えず、URL の最後の部分をそのまま `?q=` に入れた。Material は検索語をハイフンでも区切る（`lunr.tokenizer.separator`）ので、比べると上位の結果は同じで、件数が少し違うだけだった（`<W>/tools/searchcmp.mjs`）

| 検索語 | 件数 | 検索語 | 件数 |
| --- | --- | --- | --- |
| segment-tre | 118 | segment tre | 126 |
| segment-tree | 116 | segment tree | 124 |
| rolling-hash | 11 | rolling hash | 9 |
| warshall-floyd | 4 | warshall floyd | 4 |

### 確かめたこと

GitHub Pages を手元で再現した。`<W>/root/kyopro-atlas/` にビルドし、`/kyopro-atlas/` の下のないパスに 404.html を状態 404 で返す小さなサーバー（`<W>/tools/serve404.py`。`python3 -m http.server` は自前のエラーページを返すので使わなかった）を `127.0.0.1:8765` で立てた。

注意：Material は sitemap の URL のプロトコルとホスト名だけを今のページに合わせ、ポートは合わせない（`integrations/sitemap/index.ts` の `resolve`）。そのため `127.0.0.1:8765` では sitemap の URL と一致せず、instant navigation がまったく働かない（最初の試験では、入口のリンクも検索のリンクもふつうの読み込みになり、`target` の要不要が見えなかった）。公開中のサイトはホストが一致して instant navigation が働くので、手元の試験では作業用フォルダのビルドの `sitemap.xml` の `https://yuukougun.github.io/` を `http://127.0.0.1:8765/` に置き換えて、公開中と同じ条件にした（リポジトリのファイルは変えていない）。

ヘッドレスの Chrome（chrome-headless-shell 146）を CDP で動かし（`<W>/tools/shoot.mjs`・`shoot-extra.mjs`・`nojs.mjs`）、日本語のフォントは WSL の Windows のフォントを fontconfig で足した。途中で、例外で止まった比較用のスクリプトの Chrome が残ってポートを握り、その後の数回はその Chrome（同じフラグ・フォント）で動いていたので、最後に残りを止め、毎回新しい Chrome で全部の試験を流し直した。下の表はその結果で、前の結果と同じだった。

| 確かめたこと | 結果 |
| --- | --- |
| `uv run --no-sync mkdocs build --strict -q -d <W>/root/kyopro-atlas` | 警告なしで終わった（終了コード 0）。404 の本文は 404.html にだけ出て、ほかのページには出ない |
| Zensical 0.0.71 `zensical build --strict`（作業ツリーの docs・overrides・snippets・mkdocs.yml・nav.yml を `<W>/zcopy` に写して実行。`.cache` は写していない） | 「No issues found」。描いた 404 の本文は MkDocs と同じ（ホームも `/kyopro-atlas/`） |
| 390px・ダーク（`404-390-dark.png`） | 状態 404、題名「ページが見つからない - kyopro-atlas」、配色 slate、横のはみ出し 0、ボタン 1 行、入口 5 本 |
| 390px・ライト（`404-390-light.png`）、1280px・ライト／ダーク（`404-1280-light.png`・`404-1280-dark.png`） | 同上（1280px では左のナビゲーションも出る） |
| 入口のリンクの href | `/kyopro-atlas/`・`/kyopro-atlas/start/how-to-use/`・`/kyopro-atlas/guide/term-index/`・`/kyopro-atlas/guide/reverse-index-signs/`・`/kyopro-atlas/guide/knowledge-map/`（`/kyopro-atlas/graph/no-such-page/` のような深い URL で開いても正しい） |
| 検索のボタンを押す（`/kyopro-atlas/ds/segment-tre/` から。`click-search-390-dark.png`） | ふつうの読み込みで `/kyopro-atlas/?q=segment-tre` が開き、検索が「segment-tre」で開いて 118 件出た |
| 対照：target を外して押す | instant navigation で `/kyopro-atlas/?q=no-such-page` に移ったが、検索は開かなかった（`click-search-without-target-390-dark.png`）。target="_self" が要ることの確認 |
| 入口の「知識マップ」を押す | instant navigation（読み込みなし）で知識マップが開いた（h1・題名とも「知識マップ」） |
| script を止めて開く | 検索のボタンは出ず、見出し・案内・入口 5 本は出る |
| JS の例外・console のエラー | なし。出たのは、404 の本体の「状態 404」の記録と、Material がリポジトリの情報を取りに行く api.github.com の 403（手元の環境の制限で、この変更とは関係がない）だけ |
| `npx textlint`（見える文を `<W>/text/404-text.md` に取り出して、リポジトリの設定で検査） | 0 件。.html は textlint の対象外なので取り出した。わざと です を混ぜた写しでは no-mix-dearu-desumasu が出たので、検査は効いている |
| `python3 tools/check_pages.py`（全ページ） | エラー 0・警告 0（テンプレートは検査しないので参考） |

URL の形ごとの検索語（390px。はみ出しはどれも 0）：

| 開いた URL | ボタンの文字 | ボタンの高さ |
| --- | --- | --- |
| `/kyopro-atlas/graph/no-such-page/` | 「no-such-page」をサイト内で検索 | 1 行 |
| `/kyopro-atlas/ds/segment-tre/` | 「segment-tre」をサイト内で検索 | 1 行 |
| `/kyopro-atlas/%E3%82%BB%E3%82%B0%E6%9C%A8/` | 「セグ木」をサイト内で検索 | 1 行 |
| `/kyopro-atlas/ds/segment-tree.md` | 「segment-tree」をサイト内で検索 | 1 行 |
| `/kyopro-atlas/graph/dijkstra.html` | 「dijkstra」をサイト内で検索 | 1 行 |
| `/kyopro-atlas/foo/index.html` | 「foo」をサイト内で検索 | 1 行 |
| `/kyopro-atlas/c++/` | 「c++」をサイト内で検索（`?q=c%2B%2B`） | 1 行 |
| `/kyopro-atlas/a%ZZb/`（壊れた %） | 「a%ZZb」をサイト内で検索 | 1 行 |
| `/kyopro-atlas/guide/knowledge-map-old/` | 「knowledge-map-old」をサイト内で検索 | 2 行（」の後で折れる） |
| `/kyopro-atlas/ds/offline-dynamic-connectivity/`（分野の違い） | 「offline-dynamic-connectivity」をサイト内で検索 | 2 行（`404-390-dark-wrongfield.png`） |
| `/kyopro-atlas/%3Cimg%20src=x%20onerror=alert(1)%3E/` | 「<img src=x onerror=alert(1)>」をサイト内で検索（文字のまま。ダイアログは出ない） | 2 行 |
| 区切りのない 100 文字の語 | ボタンの中で折り返す | 4 行（`404-390-light-longterm.png`） |

ボタンの文字は、最初は「…をサイト内で検索する」にしたが、390px で「る」だけが 2 行目に落ちたので「…をサイト内で検索」に縮めた。長い語で「をサ／イト内で検索」と折れたので、「をサイト内で検索」を折り返さないようにした（」の後で折れる）。

### 残った点・提案

- **id が一致したら直接のリンクを出す（提案・判断を頼む）**：claude.ai の解説が分野を取り違えた URL を書いた場合（例：`/kyopro-atlas/graph/segment-tree/`）、最後の部分はページの id と一致する。いまの検索では id のページが上位に来ない（「segment-tree」の上位は Segment Tree Beats・区間・セグメント木上の二分探索で、`ds/segment-tree/` は上位 6 件にない。「rolling-hash」も同じ）。404.html に `nav.pages` から id → URL・題名の表（id のあるページは 353。20〜30 KB 程度で、いまの 404.html は 226 KB）を埋め、一致したら「もしかして：セグメント木」のリンクを出せる。頼まれた範囲の外なので入れていない
- **検索の順位（#52 の担当への引き継ぎ）**：上の観察は #52（検索）にも関わる。aliases の英語名は本文に出るので見つかりはするが、ページの題名・id の重みが効いていない
- **手元で instant navigation を確かめるときの落とし穴（#61 描画の検査の担当へ）**：Material は sitemap の URL のポートを合わせないので、`http.server` の 8000 番などで配ると instant navigation が働かない。公開中と同じ動きを見るには、作業用フォルダのビルドの `sitemap.xml` のオリジンを置き換える（今回のやり方）
- 同じ作業ツリーで別の担当が main.html に `site_nav` ブロックを足していた（作業中）。404.html は main.html を継ぐのでこのブロックも 404 で効くが、`page and page.meta` で守られていて、404（page なし）では既定のナビゲーションをそのまま出すことを確かめた（そのビルドで上の試験を流した）
- GitHub Pages への公開は、メインのマージ後の deploy.yml による。公開後に `https://yuukougun.github.io/kyopro-atlas/graph/no-such-page/` を開けば、上の表と同じ表示になるはずである
