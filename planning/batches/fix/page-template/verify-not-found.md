# not-found の検証の報告（#73 404 のページ）

直した担当（not-found）とは別の目で、`overrides/404.html`（新規・66 行）と報告 `not-found.md` を確かめた。ファイルは直していない（この報告だけを書いた）。git は読むだけにした。

作業用フォルダは `/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/7a638398-7759-4637-95c7-6739e8d52414/scratchpad/fix/page-template/verify-not-found`（以下 `<V>`）。ビルドは `<V>/site`、撮った画像は `<V>/shots/`、結果は `<V>/results.json`、使ったスクリプトは `<V>/tools/` にある。

## 結論

| Issue | 判定 | 直しが要る点 |
| --- | --- | --- |
| #73 404 のページを日本語にし、入口へのリンクを置く | 合格 | 0 |

## 1. Issue の「やること」と「完了の条件」

- 「`overrides/404.html` を置き、日本語の案内と、ホーム・用語の索引・逆引き辞典・知識マップへのリンクを出す」：満たす。見出し「ページが見つからない」、案内の 1 文、「入口から探す」の一覧にホーム・この教材の使い方・用語の索引・逆引き辞典（言い回しから）・知識マップの 5 本が出る
- 「URL の最後の部分を検索（`?q=`）に入れたリンクを出す」：満たす。`/kyopro-atlas/graph/no-such-page/` で「「no-such-page」をサイト内で検索」が `/kyopro-atlas/?q=no-such-page` を指す
- 完了の条件「存在しない URL を開くと、日本語の案内と入口へのリンクが出る」：GitHub Pages と同じ返し方（無いパスに 404.html を状態 404 で返す）のサーバーで、深さの違う 17 通りの URL を開いて確かめた（§2・§3）

## 2. 深い URL で開いたときのリンク（特に見ること）

- ビルドした 404.html の `href`・`src` は 428 個で、424 個が `/kyopro-atlas/…` の絶対パス、4 個が外部の URL だった。相対パスは 0 で、どの深さの URL で返されても同じ先を指す
- 根拠：MkDocs 1.6.1 の `mkdocs/commands/build.py` 68–76 行はエラーのテンプレートだけ `base_url = urlsplit(config.site_url or '/').path`（＝`/kyopro-atlas/`）にし、`mkdocs/utils/templates.py` の `url_filter` は page が None なので `normalize_url`（`mkdocs/utils/__init__.py` 205–216 行）が `posixpath.join(base_url, path)` を返す。担当の報告の行番号と一致した
- ブラウザで `/kyopro-atlas/graph/no-such-page/` を開いたときの入口の解決後の URL と、その先の状態：

| 入口 | 解決後の URL | 状態 |
| --- | --- | --- |
| ホーム | `/kyopro-atlas/` | 200 |
| この教材の使い方 | `/kyopro-atlas/start/how-to-use/` | 200 |
| 用語の索引 | `/kyopro-atlas/guide/term-index/` | 200 |
| 逆引き辞典（言い回しから） | `/kyopro-atlas/guide/reverse-index-signs/` | 200 |
| 知識マップ | `/kyopro-atlas/guide/knowledge-map/` | 200 |
| 検索のボタン | `/kyopro-atlas/?q=no-such-page` | 200 |

- 下の §3 の 17 通りの URL（深さ 1〜6）のどれでも、入口の 5 本が `http://kyopro.test/kyopro-atlas/…` に解決された（`linksOk`）
- サイトの JS（progress.js・viz.js・map.js）は自分の script の src（404 でも絶対パス）から URL を作るので、深さの影響を受けない

## 3. 検索のリンク（特に見ること）

Material 9.7.7 のソースマップで、担当の説明を確かめた：`?q=` は `components/search/query/index.ts` の `watchSearchQuery` が検索の部品を組み立てるときにだけ読む。instant navigation は `integrations/instant/index.ts` 104 行目 `if (el.target || ev.metaKey || ev.ctrlKey) return EMPTY` で target のあるリンクを横取りしない。どちらも報告のとおりである。

| 確かめたこと | 結果 |
| --- | --- |
| 404（`/kyopro-atlas/graph/no-such-page/`）でボタンを押す | 印（`window.__kpMarker`）が消え、load が起きた（ふつうの読み込み）。`/kyopro-atlas/?q=no-such-page`（200）で検索が開き、入力欄は「no-such-page」、「44件見つかりました」（`B-search-390-dark.png`） |
| 戻る（検索 → 404） | 404 に戻り、ボタンと語がまた出る |
| 入口の「知識マップ」を押す | 印が残った（instant navigation）。`/kyopro-atlas/guide/knowledge-map/?field=basics`、h1「知識マップ」、地図の canvas 3 つ（`D-map-390-dark.png`） |
| 戻る（知識マップ → 404） | Material が 404 を取りに行き、2xx でないのでふつうの読み込みに切り替えた（`browser/request/index.ts` の 2xx 以外は error → `setLocation(url, true)`）。状態 404 で開き直し、ボタンと語が出た（`E-back-390-dark.png`） |
| 分野を取り違えた URL から押す（参考） | `graph/segment-tree/` → 116 件、`ds/rolling-hash/` → 11 件（4 位にローリングハッシュ）、`graph/dijkstr/` → 5 件（2 位にダイクストラ法）。どれも検索が開いた |

URL の形ごとの語（390px・ダーク。状態はすべて 404、横のはみ出しはすべて 0）：

| 開いた URL | ボタン | 行数 |
| --- | --- | --- |
| `/kyopro-atlas/graph/no-such-page`（末尾の / なし） | 「no-such-page」 | 1 |
| `/kyopro-atlas/x` | 「x」 | 1 |
| `/kyopro-atlas/a/b/c/d/e/f/` | 「f」 | 1 |
| `/kyopro-atlas/ds/segment-tre/` | 「segment-tre」 | 1 |
| `/kyopro-atlas/%E3%82%BB%E3%82%B0%E6%9C%A8/` | 「セグ木」 | 1 |
| `/kyopro-atlas/ds/segment-tree.md` | 「segment-tree」 | 1 |
| `/kyopro-atlas/graph/dijkstra.html` | 「dijkstra」 | 1 |
| `/kyopro-atlas/foo/index.html` | 「foo」 | 1 |
| `/kyopro-atlas/graph/no-such-page/index.html` | 「no-such-page」 | 1 |
| `/kyopro-atlas/index.md` | 出さない（語がない） | — |
| `/kyopro-atlas/c++/` | 「c++」（`?q=c%2B%2B`） | 1 |
| `/kyopro-atlas/a%ZZb/`（壊れた %） | 「a%ZZb」（`?q=a%25ZZb`） | 1 |
| `/kyopro-atlas/%3Cimg%20src=x%20onerror=alert(1)%3E/` | 文字のまま出る。ダイアログ 0 | 2 |
| `/kyopro-atlas/graph/no-such-page/?q=zzz#frag` | 「no-such-page」（問い合わせと # は使わない） | 1 |
| `/kyopro-atlas/guide/knowledge-map-old/` | 「knowledge-map-old」 | 2 |
| `/kyopro-atlas/ds/offline-dynamic-connectivity/` | 「offline-dynamic-connectivity」（`G-longterm-390-dark.png`） | 2 |
| `/kyopro-atlas/%20/` | 出さない（空白だけ） | — |

## 4. 表示（390px のダーク・ライト、1280px、script なし）

- 390px・ダーク（`A-deep-390-dark.png`）：配色 slate、題名「ページが見つからない - kyopro-atlas」、ボタン 1 行、入口 5 本。崩れなし
- 390px・ライト（`H-deep-390-light.png`）・1280px・ダーク（`H-deep-1280-dark.png`）：崩れなし。1280px では左のナビゲーションも出る（別の担当が main.html に足した `site_nav` は page なしで既定のまま出る）
- script を止めて開く（`I-nojs-390-dark.png`）：ボタンは `hidden`（display: none）のまま、見出し・案内・入口 5 本は出る
- JS の例外は 0。console のエラーは、404 の文書そのものの記録と、api.github.com の 403（手元の環境の制限）だけだった

## 5. 書き換えない検査とほかへの影響

| 検査 | 結果 |
| --- | --- |
| `uv run --no-sync mkdocs build --strict -q -d <V>/site` | 終了コード 0。前後で作業ツリーの `git status` は変わらなかった |
| Zensical 0.0.71（`uvx --offline --from zensical==0.0.71 zensical build --strict`。docs・overrides・snippets・mkdocs.yml・nav.yml を `<V>` に写して実行） | 「No issues found」。404 の本文は MkDocs と同じで、`"base":"/kyopro-atlas"`（末尾の / なし）でもホームは `/kyopro-atlas/`（22 行目のそろえ方が効く）。出力は `<V>/zensical-404.html` |
| `python3 tools/check_pages.py`（全 353 ページ） | エラー 0・警告 0（テンプレートは対象外なので参考） |
| `npx textlint`（見える文を `<V>/text/404-visible.md` に取り出し、作業ツリーの `.textlintrc.json` で検査） | 0 件。です・ます を混ぜた写し（`404-control.md`）では no-mix-dearu-desumasu が出るので、検査は効いている |
| 検索の索引・sitemap | `search_index.json`・`sitemap.xml` に 404 の文は入らない。`kp-not-found` を含むのは 404.html だけ |
| デプロイ・CI | deploy.yml は `mkdocs build --strict` の `site/` をそのまま上げるので、根の 404.html が GitHub Pages の 404 になる。lychee（links.yml）は `docs/**/*.md` の外部リンクだけを見るので関係しない |

- 文体と事実：だ・である調。入口の説明は各ページの中身と合う（how-to-use は引き方・レベル・記録の節を持つ。用語の索引と知識マップの説明はホームの「入口」と同じ言い回し。逆引き辞典の説明は summary と合う）
- 担当の報告の記述（行番号の表、Material と MkDocs のソースの箇所、sitemap のポートの件、Zensical の base_url）は、確かめた範囲ですべて正しかった
- 検証の途中で、同じ作業ツリーの別の担当の変更（how-to-use.md・interfaces.md・`.github/ISSUE_TEMPLATE/`・main.html・kp.css）が増えた。404 が使う id と題名（how-to-use は「この教材の使い方」のまま）は変わっておらず、404.html は content ブロックを上書きするので main.html の content の変更は 404 に及ばない

## メインへの申し送り（#73 の直しは要らない）

1. **誤りの報告（#10）との関係**：#10 の担当が直している interfaces.md §7 は「このページの誤りを報告する」を「どのページにも出し」と書く。404.html は Material の既定の 404 と同じく content ブロックを super() なしで上書きするので、404 のページには出ない。直す前（Material の既定の 404）も出ていなかったので、#73 による後退ではない。main.html の報告のリンクをそのまま 404 に出すと、題名は site_name、URL はホームの URL（page.canonical_url がない）になり、開いた URL が入らないので、出さない今の形がよい。interfaces.md の書き方を「404 のページを除く」にそろえるか、404 用の報告（開いた URL を入れる）を別の Issue にするかをメインが決める
2. **文書（提案）**：interfaces.md §7 の表と design.md のディレクトリの図（`overrides/main.html` だけ）に 404.html がない。足すなら「404 のページ：`overrides/404.html`。日本語の案内、入口 5 本（`nav.pages` から id で引く）、URL の最後の部分を `?q=` に入れた検索のリンク（`target="_self"`。script で作る）」の 1 行
3. **検索の順位（#52 へ）**：`/kyopro-atlas/graph/segment-tree/` から押すと、上位 8 件に「セグメント木」がない（Segment Tree Beats・区間・セグメント木上の二分探索…）。#73 の求めること（`?q=` に入れたリンク）は満たしている。担当の提案（最後の部分がページの id と一致したら直接のリンクを出す）は #52 か別の Issue で判断する
4. **入口の範囲**：ホームの「入口」にある逆引き辞典（制約と計算量から）・色別ロードマップ・レベル別の一覧は、404 の一覧にない。Issue が挙げる 4 つはそろい、ホームからたどれるので、直さなくてよい

## 検証のやり方

- サーバー：`<V>/tools/serve404.py`（`/kyopro-atlas/` の下を `<V>/site` から配り、無いパスとディレクトリの一覧には 404.html を状態 404 で返す。/ のないディレクトリは 301）。ポート 47321 で立て、使い終えて止めた
- ブラウザ：chrome-headless-shell 146 を CDP で動かした（`<V>/tools/cdp.mjs`・`run.mjs`・`search-check.mjs`。CDP のポートは 47322・47323）。日本語のフォントは `<V>/fonts.conf`
- instant navigation を公開中と同じ条件にするため、sitemap.xml を書き換えず、`--host-resolver-rules=MAP kyopro.test 127.0.0.1:47321` で `http://kyopro.test/kyopro-atlas/…` として開いた。Material は sitemap の URL のプロトコルとホスト名だけを今のページに合わせる（`integrations/sitemap/index.ts` の `resolve`）ので、ブラウザから見てポートが既定（80）なら sitemap と一致する。入口のリンクで instant navigation が働いたこと（§3 の印）で、条件がそろっていたと確かめた
