# 10 技術構成（tech）の調査レポート

調査日：2026-10-21。担当：調査サブエージェント（10 tech）。

この分野は教材の項目ではなく技術の選択なので、手引き §5.1 の節立てを次のように読み替える。

- §1「調べた資料」→ そのまま
- §2「分野の全体像」→ **0. 結論**と **2. 試作で確かめたこと**
- §3〜4「項目一覧・項目ごとのメモ」→ **3. 論点ごとの比較と推奨**（論点 3.1〜3.10）
- §7「設計への提言」→ **4. 推奨構成のまとめ**と **5. 設計で判断が必要な点・未確認事項**

試作は一時ファイル置き場（`/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/ff4dc6ee-16d4-486c-b97a-49fefbe7b218/scratchpad/research-10/`）に作った。セッションが終わると消えるので、確かめた設定とコードの要点はこのレポートに写してある。

---

## 0. 結論（推奨構成の要約）

| 論点 | 推奨 | おもな理由 | 代替案 |
| --- | --- | --- | --- |
| サイト生成の版 | Material for MkDocs **9.7.7**＋MkDocs **1.6.1**＋Python **3.12**。`uv.lock` で全依存を固定 | 9.7.7 が最新のパッチ（2026-07-17、検索候補の XSS 修正を含む）。保守（重大なバグとセキュリティの修正）は **2027-05-05 まで** | Zensical（同じ `mkdocs.yml` で試作がほぼそのまま動いた） |
| Zensical への備え | hooks・自作プラグイン・gen-files・macros を使わない。生成はすべて独立スクリプト。CI で Zensical の試験ビルドを並走させる（失敗してもデプロイは止めない） | Zensical 0.0.71 は `hooks` 非対応で、Python のモジュール API はまだない。試作（タグ・検索・数式・Mermaid・上書きテンプレート・独自 JS）は Zensical でも同じように動いた | — |
| 分類（タグ） | front matter に軸ごとの単一値キー（`level`・`field`・`kind` など）を持たせ、一覧ページは独立スクリプトが Markdown として生成する。ページ上部のバッジはテンプレートの上書きで出す | 二重管理がない。MkDocs と Zensical で同じ動作（両方で確認）。決定事項「タグ一覧の生成は独立スクリプト」に合う | tags プラグインの階層タグ（`レベル/水` など）。両方で動いた。使う場合はスクリプトで整合を検査する |
| 日本語検索 | `lang: ja` に加え、文字種の境目で区切る `separator` と `stopWordFilter` を設定する | 30問の試験で、既定設定は正解ページを含む結果が 18/30、調整後は 29/30（1位 25/30） | 将来は Zensical の検索（設定なしで 27/30、1位 27/30） |
| 数式 | KaTeX **0.16.x の最新（0.16.47）を同梱**し、`pymdownx.arithmatex`（`generic: true`）が出す `.arithmatex` 要素だけを描画する | MathJax 4 より約 3.7 倍軽い（gzip 後 76KB 対 281KB）。競プロで使う記法 22 種を試してすべて描画できた | MathJax 4（長い式の自動折り返しや読み上げが要る場合） |
| 図 | 静的な図は Mermaid（Material の標準統合）。動く図は素の JS＋SVG の小さな部品 | Mermaid は設定だけで instant navigation とダークモードに対応する。動く図は「状態の列を先に全部作り、i 番目を描く」方式にすると壊れにくく、外部ライブラリが要らない | D3（データが大きい図だけ） |
| 知識マップ | **Cytoscape.js 3.34＋cytoscape-dagre 4.0** を同梱。データ（`graph.json`）は独立スクリプトが生成 | gzip 後 約150KB。400 頂点・508 辺の配置が 0.26 秒（CPU を 1/4 に落としても 1.1 秒）。タッチ操作に対応、MIT | ビルド時に Graphviz で SVG を作る（操作性は下がるが最も壊れにくい） |
| LLM 向け索引 | llms.txt の書式（Markdown）で `docs/llms.txt` を生成（サイトでは `/kyopro-atlas/llms.txt`）。サイトの JS 用には別に JSON を生成 | Markdown のほうが読みやすく、文字数は圧縮した JSON と同程度。1行1ページで、RAG の断片検索にも向く | 分野別に分けた索引ファイル（大きくなったとき） |
| claude.ai | 従来のプロジェクトに GitHub 連携で `docs/`・索引・解説手順のファイルを入れる。同期は手動。教材が大きくなると自動で RAG（検索で必要な断片だけ読む）に切り替わる前提で手順を書く | 公式ヘルプで確認した仕様に沿う | 索引だけを知識に入れ、本文は公開サイトから web fetch で読む／新しい Projects（beta）でリポジトリを毎回 clone させる |
| Claude Code スキル | `.claude/skills/<名前>/SKILL.md`。記録用スキルは `disable-model-invocation: true` で手動起動だけにする | 公式ドキュメントの仕様どおり | claude.ai のカスタムスキル（zip でアップロード） |
| デプロイ | 公式の `actions/configure-pages@v6`・`upload-pages-artifact@v5`・`deploy-pages@v5`、`astral-sh/setup-uv@v10`、`uv sync --locked`、`mkdocs build --strict` | 公式の構成。依存はロックファイルどおりにしか入らない | — |
| 自動検証 | MkDocs の `validation` を全部 `warn`＋`--strict`。独立スクリプトでメタデータのスキーマ・前提の循環・生成物の鮮度を検査。コード片は `pymdownx.snippets`（`check_paths: true`）で取り込み、CI では `gcc:15.2.0` コンテナでコンパイル・実行。textlint（prh・である調の統一）。外部リンクは週1回 lychee（atcoder.jp は除外） | 試作でそれぞれ動作を確認した | — |
| 進捗チェック | localStorage（キーに名前空間を付ける）。`document$` でページごとに結び直す。ロードマップと知識マップは `graph.json` と突き合わせて集計。エクスポート／インポートを用意 | 試作で instant navigation をまたいで動いた。Safari は7日間使わないとデータを消すことがあるので、退避の手段が要る | — |

---

## 1. 調べた資料

| 資料 | URL | 参考にしたこと |
| --- | --- | --- |
| Material for MkDocs の変更履歴 | https://squidfunk.github.io/mkdocs-material/changelog/ | 9.6〜9.7.7 の内容、保守モード、EOL（2027-05-05）、MkDocs 2.0 非互換の警告 |
| Material：tags プラグイン | https://squidfunk.github.io/mkdocs-material/plugins/tags/ | 9.6 の新しい tags プラグインの全設定（階層タグ・許可リスト・一覧・shadow・export） |
| Material：タグの設定 | https://squidfunk.github.io/mkdocs-material/setup/setting-up-tags/ | 一覧の書き方、タグのアイコン、meta プラグイン |
| Material：search プラグイン | https://squidfunk.github.io/mkdocs-material/plugins/search/ | `lang`・`separator`・`pipeline`、日本語はクライアント側で分かち書きすること |
| Material：数式 | https://squidfunk.github.io/mkdocs-material/reference/math/ | KaTeX と MathJax の設定例と比較 |
| Material：図 | https://squidfunk.github.io/mkdocs-material/reference/diagrams/ | Mermaid の統合 |
| Material：カスタマイズ | https://squidfunk.github.io/mkdocs-material/customization/ | `document$`、テンプレートの上書き |
| Material：ナビゲーション | https://squidfunk.github.io/mkdocs-material/setup/setting-up-navigation/ | instant navigation は `site_url` と sitemap.xml に依存すること、instant previews |
| Material：色 | https://squidfunk.github.io/mkdocs-material/setup/changing-the-colors/ | ダークモード（`palette`） |
| Material のソース（9.7.7 の配布物） | https://pypi.org/project/mkdocs-material/9.7.7/ | 検索ワーカーのソース（ソースマップ）、tags プラグインのコード、Mermaid の読み込み先 |
| MkDocs：設定（validation） | https://www.mkdocs.org/user-guide/configuration/#validation | リンク検証の設定項目と推奨値 |
| PyPI の各パッケージ | https://pypi.org/project/mkdocs/ ・ https://pypi.org/project/zensical/ ・ https://pypi.org/project/pymdown-extensions/ | 最新版・要求する Python の版・公開日 |
| pymdown-extensions の変更履歴 | https://github.com/facelessuser/pymdown-extensions/blob/main/docs/src/markdown/about/changelog.md | 12.0 の BetterEm 書き直し（日本語の強調への影響）、12.3 の `punctuation` |
| pymdown-extensions：Snippets・Blocks・Arithmatex | https://facelessuser.github.io/pymdown-extensions/extensions/snippets/ ・ https://facelessuser.github.io/pymdown-extensions/extensions/blocks/ ・ https://facelessuser.github.io/pymdown-extensions/extensions/arithmatex/ | コード片の取り込み、`///` 記法の囲み、数式 |
| Zensical：MkDocs との互換 | https://zensical.org/docs/compatibility/mkdocs/ | 互換の範囲 |
| Zensical：移行ガイド | https://zensical.org/docs/compatibility/mkdocs/migration/ | 未対応の設定（hooks）、MiniJinja、テーマの変種 |
| Zensical：プラグイン対応 | https://zensical.org/docs/compatibility/mkdocs/plugins/ | 対応プラグインの一覧と相違点、未対応（gen-files など）、予定 |
| Zensical：Python Markdown Extensions | https://zensical.org/docs/compatibility/markdown/python-markdown-extensions/ | 対応する拡張と設定 |
| Zensical：検索・タグ・検証・カスタマイズ・front matter・数式・図 | https://zensical.org/docs/setup/search/ ・ https://zensical.org/docs/setup/tags/ ・ https://zensical.org/docs/setup/validation/ ・ https://zensical.org/docs/customization/ ・ https://zensical.org/docs/authoring/frontmatter/ ・ https://zensical.org/docs/authoring/math/ ・ https://zensical.org/docs/authoring/diagrams/ | 各機能の Zensical での扱い |
| Zensical：今後の変更・ロードマップ | https://zensical.org/upcoming-changes/ ・ https://zensical.org/roadmap/ | 0.1.0（2026-11-05）、Material の EOL 延長、Python のモジュール API の予定 |
| llms.txt の仕様（v2） | https://llmstxt.org/ | 書式、`.md` 版のページ、GitHub Pages のプロジェクトサイトでの置き場所 |
| claude.ai：GitHub 連携 | https://support.claude.com/en/articles/10167454-use-the-github-integration | ファイル・フォルダの選択、同期、取得される情報 |
| claude.ai：プロジェクト | https://support.claude.com/en/articles/9517075-what-are-projects ・ https://support.claude.com/en/articles/9519177-how-can-i-create-and-manage-projects | プロジェクトの知識と指示、新しい Projects（beta） |
| claude.ai：プロジェクトの RAG | https://support.claude.com/en/articles/11473015-retrieval-augmented-generation-rag-for-projects | 知識が多いときの挙動 |
| claude.ai：コンテキストウィンドウ | https://support.claude.com/en/articles/8606394-how-large-is-the-context-window-on-paid-claude-plans | モデルごとの大きさ |
| claude.ai：ファイルのアップロード | https://support.claude.com/en/articles/8241126-upload-files-to-claude | プロジェクトのファイルの上限 |
| claude.ai：Web 検索と web fetch | https://support.claude.com/en/articles/10684626-enable-and-use-web-search | URL を渡すとページを取得できる条件 |
| claude.ai：スキル | https://support.claude.com/en/articles/12512198-how-to-create-custom-skills ・ https://support.claude.com/en/articles/12512180-use-skills-in-claude | claude.ai のカスタムスキル |
| Claude API：web fetch ツール | https://platform.claude.com/docs/en/agents-and-tools/tool-use/web-fetch-tool | 取得できる URL の条件、キャッシュ、JS で描くページは不可 |
| Claude API：トークン数の計測 | https://platform.claude.com/docs/en/build-with-claude/token-counting | 教材のトークン数を実測する方法 |
| Claude Code：Projects | https://code.claude.com/docs/en/claude-projects | 新しい Projects（リポジトリの clone、指示の上限、スキルの読み込み） |
| Claude Code：スキル | https://code.claude.com/docs/en/skills | SKILL.md の形式・置き場所・呼び出し方 |
| スキルの書き方の推奨 | https://platform.claude.com/docs/en/agents-and-tools/agent-skills/best-practices | name・description の規則、500 行以内など |
| GitHub Pages：独自のワークフロー | https://docs.github.com/en/pages/getting-started-with-github-pages/using-custom-workflows-with-github-pages | 公式 actions と必要な権限 |
| GitHub Pages：制限 | https://docs.github.com/en/pages/getting-started-with-github-pages/github-pages-limits | サイト 1GB、デプロイ 10 分、帯域 100GB/月（目安） |
| 各 action のリリース | https://github.com/actions/configure-pages/releases ・ https://github.com/actions/upload-pages-artifact/releases ・ https://github.com/actions/deploy-pages/releases ・ https://github.com/astral-sh/setup-uv/releases | 最新の版（2026-10-21 時点） |
| uv：GitHub Actions | https://docs.astral.sh/uv/guides/integration/github/ | `uv sync --locked`、action の固定 |
| GitHub ホストのランナー | https://github.com/actions/runner-images/blob/main/images/ubuntu/Ubuntu2404-Readme.md | ubuntu-24.04 の GCC は 12〜14 |
| GCC の Docker イメージ | https://hub.docker.com/_/gcc | `gcc:15.2.0` がある |
| KaTeX の変更履歴 | https://github.com/KaTeX/KaTeX/blob/main/CHANGELOG.md | 0.17〜0.19 の破壊的変更 |
| Cytoscape.js・cytoscape-dagre | https://js.cytoscape.org/ ・ https://github.com/cytoscape/cytoscape.js-dagre | 知識マップ |
| elkjs・vis-network・D3・Sigma.js・d3-dag・viz-js・JSAV | https://github.com/kieler/elkjs ・ https://github.com/visjs/vis-network ・ https://d3js.org/ ・ https://www.sigmajs.org/ ・ https://github.com/erikbrinkman/d3-dag ・ https://github.com/mdaines/viz-js ・ https://github.com/vkaravir/JSAV | 比較（大きさ・ライセンスは npm の配布物で計測） |
| textlint と規則 | https://textlint.org/ ・ https://github.com/textlint-rule/textlint-rule-prh ・ https://github.com/textlint-ja/textlint-rule-no-mix-dearu-desumasu ・ https://github.com/textlint-ja/textlint-rule-preset-ja-technical-writing ・ https://github.com/textlint/textlint-filter-rule-comments | 表記揺れ・文体の検査 |
| lychee | https://github.com/lycheeverse/lychee ・ https://github.com/lycheeverse/lychee-action | 外部リンクの検査 |
| WebKit の ITP（7日ルール） | https://webkit.org/blog/10218/full-third-party-cookie-blocking-and-more/ | Safari が localStorage を消す条件 |
| MDN：後読み・Intl.Segmenter | https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Regular_expressions/Lookbehind_assertion ・ https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Intl/Segmenter | 検索の区切り文字で使う後読みの対応ブラウザ、Zensical の分かち書き |

いずれのサイトにも AI による利用を断る指定はなかった。atcoder.jp は開いていない。Web 検索の回数の上限に達したため、後半は既知の URL を直接読んで調べた。

---

## 2. 試作で確かめたこと

### 2.1 環境

- Python 3.12.13（uv が `/usr/bin/python3.12` を使った）、uv 0.11.24
- mkdocs 1.6.1、mkdocs-material 9.7.7、pymdown-extensions 12.3、Markdown 3.11.2、Pygments 2.21.0（`uv.lock` で固定、全 30 パッケージ）
- zensical 0.0.71（別の仮想環境）
- KaTeX 0.16.47、Cytoscape.js 3.34.3、cytoscape-dagre 4.0.1（`docs/assets/vendor/` に同梱）
- ブラウザでの確認：Playwright 1.64.1 の Chromium 156（ヘッドレス）。足りない共有ライブラリは `apt-get download` で取得して一時ファイル置き場に展開した（システムには入れていない）
- textlint 15.8.0、textlint-rule-prh 6.1.1、textlint-rule-preset-ja-technical-writing 12.0.2
- g++-15（15.2.0、`-std=gnu++23`）

### 2.2 試作の構成

14 ページ（二分探索・累積和・bit 全探索・BFS・ダイクストラ法・ワーシャルフロイド法・最小全域木・木の直径・優先度付きキュー・セグメント木・遅延セグメント木・Union-Find・ナップサック DP・木 DP）と横断ページ（知識マップ・ロードマップ・レベル別一覧・タグ一覧）を作った。各ページの front matter は次の形にした。

```yaml
---
id: dijkstra
title: ダイクストラ法
level: 水
field: グラフ
kind: 手法
tags: [レベル/水, 分野/グラフ, 種類/手法]   # tags プラグインを試すために併記した
prerequisites: [bfs, priority-queue]      # ページの id で指す
aliases: [Dijkstra, 最短経路]
signs: [辺の重みが非負, 単一始点最短経路]
summary: 辺の重みが非負のグラフで、始点からの最短距離を優先度付きキューで確定させていく。
---
```

独立スクリプト `tools/gen_site_data.py`（PyYAML だけを使い、MkDocs を import しない）が front matter を読み、次を生成する。

- `docs/assets/data/graph.json`：知識マップ・ロードマップ用（頂点・辺・ページごとの問題 ID）
- `docs/guide/levels.md`：レベル別一覧（Markdown。MkDocs・Zensical・GitHub のどれでも読める）
- `docs/llms.txt`：LLM 向け索引

同時に、必須キー・型・`level` と `field` の値・`id` の重複・前提ページの存在・前提関係の循環・`tags` と `level`/`field` の一致を検査する。`--check` を付けると、生成物が最新かどうかだけを確かめる（CI 用）。

### 2.3 結果一覧（Material 9.7.7 と Zensical 0.0.71）

同じ `docs/` と `mkdocs.yml` を両方でビルドし、ブラウザで操作して確かめた。

| 確かめたこと | Material 9.7.7 | Zensical 0.0.71 |
| --- | --- | --- |
| ビルド（警告なし） | ○ | ○（`mkdocs.yml` をそのまま読んだ） |
| 日本語の見出しのアンカー（`toc.slugify` に `pymdownx.slugs.slugify`） | ○ `#練習問題` などになる | ○ 同じ |
| KaTeX（同梱）で数式 | ○ 1ページ 8 式 | ○ |
| instant navigation 後の再初期化（`document$`） | ○（ただし `site_url` と配信元が一致するときだけ instant navigation が働く） | ○ |
| ページ本文の `<script>` | instant navigation で移動するたびに再実行される | ○ |
| Mermaid | ○（unpkg から `mermaid@11` を読み込む） | ○（同じ） |
| テンプレートの上書き（`overrides/main.html` の `block content` で `page.meta.level` を表示） | ○ | ○（MiniJinja でも動いた） |
| tags プラグインの階層タグ・`tags_allowed`・一覧の `include` | ○ | ○ |
| tags プラグインの複数インスタンス（`tags_name_property` を変える） | ○ | ○（ただしタグの表示は上書きテンプレートが要る） |
| `tags.json` の出力（export） | ○ | ×（Zensical は export に非対応） |
| 動く図（素の JS＋SVG） | ○ | ○ |
| 知識マップ（Cytoscape.js＋dagre） | ○ | ○ |
| localStorage の「理解した」「解いた」と、ロードマップ・知識マップへの集計 | ○ | ○ |
| ダークモード（OS の設定に追従） | ○ 動く図の色も CSS 変数で追従 | ○ |
| スマホ幅（390px、iPhone 13 相当） | ○ 横はみ出しなし、ボタン 44×44px | （未計測） |
| リンク切れ・アンカー切れの検出 | ○ 4種類を警告（ページなし・アンカーなし・絶対パス・nav にないページ） | ○ 3件（ページなし・アンカーなし×2） |
| コード片の取り込み（`pymdownx.snippets`、節の切り出し） | ○ ファイルがないとビルドが失敗する | ○ 同じ |
| `pymdownx.blocks`（`///` 記法の囲み・折りたたみ） | ○ | ○ 出力 HTML が同一 |
| 日本語検索（30問の試験、§2.4） | 既定 18/30 → 調整後 29/30 | 27/30（設定なしでも同じ） |

### 2.4 日本語検索の比較実験

試作の 14 ページ＋横断ページに対して、30 個のクエリ（手法名・別名・文字種の混ざった語・助詞を含む語句）を検索し、「期待するページが結果に入ったか（発見）」と「1位だったか」を数えた。結果はブラウザで実際の検索画面を操作して取った。

| 設定 | 発見 | 1位 | 平均件数 |
| --- | --- | --- | --- |
| A. Material 既定（`lang: ja` のみ） | 18/30 | 17/30 | 2.1 |
| B. A＋文字種の境目で区切る `separator` | 29/30 | 22/30 | 5.4 |
| C. B＋`pipeline: [stemmer, stopWordFilter]` | 29/30 | 24/30 | 4.9 |
| D. B で `lang: en`（分かち書きなし） | 29/30 | 23/30 | 5.1 |
| E. C＋`fields: {tags: {boost: 2}}` | 29/30 | **25/30** | 4.9 |
| Zensical 0.0.71（既定・B の区切りのどちらも同じ） | 27/30 | **27/30** | 2.7 |

既定の Material で 0 件になったクエリ：「セグメント木」「ダイクストラ法」「優先度付きキュー」「遅延セグメント木」「bit全探索」「木の直径」「木DP」「負の辺」「区間の和」「いもす法」（いずれも本文やページ名にそのまま書いてある）。

原因は Material の検索の作りにある（9.7.7 の検索ワーカーのソースで確認）。

- 索引を作るとき：本文を `separator` で区切ったあと、各断片を TinySegmenter で分かち書きする。「セグメント木」は「セグメント」と「木」の2語として索引に入る
- 検索するとき：クエリのうち**漢字の連続だけ**を、索引にある語で貪欲に分割する（「二分探索」→「二分」「探索」）。カタカナ・ひらがなを含む語は分割されず、「セグメント木*」という1語の前方一致になるので、何も見つからない
- 複数語は OR で結ばれる（「二分探索」で「二分ヒープ」を含むダイクストラ法のページも出る）。一致した語の割合で順位を上げる

`separator` に「カタカナ・ひらがな・漢字・英数字の境目」を加えると、索引とクエリの両方が同じ所で区切られ、ずれがなくなる（B〜E）。`stopWordFilter` を有効にすると「の」などの助詞による雑音が減る（C）。tags の重みは既定で 1,000,000 倍と非常に大きく、「法」が `分野/動的計画法` に当たって「ダイクストラ法」の順位を下げていたので、2 に下げた（E）。

残った失敗は、検索語が本文になくて front matter（`aliases`・`summary`）にしかない場合（「セグ木」「クラスカル法」）と、ひらがなの専門語（「いもす法」は E で 4 位）である。Material の検索は front matter を索引に入れないので、**別名は本文の冒頭に書く**のがよい（スクリプトで「aliases の各語が本文にあるか」を検査できる）。

Zensical の検索は Lunr ではない新しい実装で、検索ワーカーのコードに `Intl.Segmenter`（ブラウザ組み込みの単語分割）が含まれている。区切り文字を調整しなくても日本語に強く、結果が絞られる（クエリの語をすべて含むものに限る挙動とみられる）。Zensical の検索画面はタグで結果を絞り込める。

### 2.5 大きさと速さの測定

- **知識マップの配置**（400 頂点・508 辺の合成データ、ブラウザで計測）：dagre 259ms（CPU を 1/4 に落とすと 1,149ms）、ELK の layered 556ms（同 2,479ms）。要素の生成は 70ms（同 291ms）
- **教材が大きくなったときの検索**（400 ページ・130 万字の合成データ）

  | | Material 9.7.7（設定 C） | Zensical 0.0.71 |
  | --- | --- | --- |
  | ビルド時間 | 2.7 秒 | 3.0 秒 |
  | 検索索引 | `search_index.json` 7.6MB（gzip 435KB） | `search.json` 4.1MB（gzip 371KB） |
  | サイト全体 | 59MB | 52MB |
  | ページを開いてから最初の検索結果まで（デスクトップ） | 約 1.9 秒 | 約 2.7 秒 |

  合成データは同じ語の繰り返しなので、実際の文章では gzip 後の索引はこれより大きくなる。サイトが大きいのは、各ページの HTML に全ページ分のナビゲーションが入るためである（1ページ約 150KB、gzip で数十 KB）。GitHub Pages の上限（1GB）には遠い。
- **ライブラリの大きさ**（npm の配布物を gzip -9 で圧縮して計測）

  | ライブラリ | 版 | ライセンス | min | gzip |
  | --- | --- | --- | --- | --- |
  | KaTeX（JS） | 0.16.47 | MIT | 273KB | 76KB（CSS 3.5KB、フォントは使う分だけ） |
  | MathJax（tex-mml-chtml） | 4.1.3 | Apache-2.0 | 998KB | 281KB（フォントは別） |
  | Mermaid | 11.12.1 | MIT | 2.7MB | 788KB（図のあるページだけで読まれる） |
  | Cytoscape.js | 3.34.3 | MIT | 436KB | 136KB |
  | cytoscape-dagre（dagre を内蔵） | 4.0.1 | MIT | 46KB | 16KB |
  | elkjs（elk.bundled.js） | 0.11.1 | EPL-2.0 または GPL-3.0 | 1.6MB | 466KB |
  | vis-network（standalone） | 10.0.2 | Apache-2.0 または MIT | 645KB | 150KB |
  | D3（全部入り） | 7.9.0 | ISC | 280KB | 92KB |

---

## 3. 論点ごとの比較と推奨

### 3.1 Material for MkDocs 9.7 の機能と設定

#### 3.1.1 固定する版

**推奨**：`mkdocs==1.6.1`、`mkdocs-material==9.7.7`、Python 3.12。`pyproject.toml` に直接の依存だけを書き、`uv lock` で推移的な依存（pymdown-extensions・Markdown・Pygments など）まで `uv.lock` に固定する。更新は `uv lock --upgrade-package <名前>` で意図して行う。

```toml
[project]
name = "kyopro-atlas"
version = "0.0.0"
requires-python = ">=3.12,<3.14"
dependencies = [
  "mkdocs==1.6.1",
  "mkdocs-material==9.7.7",
  "pyyaml>=6",          # 独立スクリプト用
]

[tool.uv]
package = false
```

`.python-version` に `3.12` を書く。

理由：

- 9.7.7（2026-07-17）が最新のパッチで、検索候補の DOM ベースの XSS を直している。9.7.0（2025-11-11）で新機能の追加は終わり、Insiders の機能（階層タグ・パンくず・instant previews など）がすべて無償版に入った。projects と typeset の2プラグインは非推奨（https://squidfunk.github.io/mkdocs-material/changelog/）
- 変更履歴の冒頭に「**Material for MkDocs は 2027-05-05 に EOL**。それまで重大なバグとセキュリティの修正を続ける」とある（当初の「12か月」から6か月延長。https://zensical.org/upcoming-changes/）。教材の制作期間中に保守が切れる見込みなので、移行の準備（§3.2）が必要になる
- PyPI には MkDocs 2.0 の開発版（2.0.dev6、2026-09-15）が出ている。Material は 9.7.5 から `mkdocs<2` に制限しており、MkDocs 2.0 とは互換がない。`mkdocs build` を実行すると毎回、非互換の警告が標準エラーに出る。CI のログを汚さないよう、環境変数 `NO_MKDOCS_2_WARNING=1` で消せる（9.7.7 のコードで確認）
- Python は、pymdown-extensions 12 が 3.10 以上、Markdown 3.11 が 3.11 以上、Zensical が 3.11 以上を要求する。手元の標準の Python は 3.10 なので、uv で 3.12 を使う（手元に `/usr/bin/python3.12` がある）

注意：pymdown-extensions 12.0 で強調（BetterEm）が CommonMark 準拠に書き直された。`pymdownx.betterem` を有効にすると、`**「二分探索」**は` のような日本語の強調が壊れ、HTML が入れ子のまま閉じなくなる（試作で確認）。**`pymdownx.betterem` は入れない**か、入れるなら `punctuation: false` を指定する（12.3 で追加された設定。試作で正しく描画されることを確認）。Python-Markdown 標準の強調はこの文を正しく処理した。

#### 3.1.2 分類（タグ）で複数の軸を作る

9.6.0 で tags プラグインが書き直され、9.7.0 で階層タグ・shadow タグ・JSON の出力が入った（https://squidfunk.github.io/mkdocs-material/plugins/tags/）。複数の軸を作る方法は3つある。

| 案 | 書き方 | 長所 | 短所 |
| --- | --- | --- | --- |
| K：軸ごとのキー＋スクリプト生成 | `level: 水`、`field: グラフ`、`kind: 手法`。一覧ページはスクリプトが Markdown で生成し、バッジは上書きテンプレートで表示 | 単一値で書きやすい。スキーマで検査しやすい。プラグインに依存しない。Claude が front matter を読んで迷わない | Material の検索で「水」などのタグ語が引っかからない（一覧ページは引っかかる）。Zensical の検索画面のタグ絞り込みが使えない |
| T：階層タグ | `tags: [レベル/水, 分野/グラフ, 種類/手法]`、`tags_hierarchy: true`、`tags_allowed` で語彙を制限 | テーマが自動でタグを表示する。両ビルダーで動く（確認済み）。Zensical の検索でタグ絞り込みができる | 階層タグは 9.7.0 で experimental。軸の情報をタグの文字列から読み取る必要がある |
| M：プラグインの複数インスタンス | `levels: [水]` などのキーごとにインスタンスを分け、`tags_name_property`・`tags_name_variable`・`listings_directive`・`export_file` を変える | 軸ごとに一覧を分けられる | front matter が単一値でなく配列になる。2つ目以降のタグの表示には上書きテンプレートが要る |

試作では K と T を併記し、スクリプトで一致を検査した（例：`level: 水` なら `tags` に `レベル/水` が必要）。`tags_allowed` はビルド時に語彙外のタグを止める（試作で「Tags not in allow list」で止まることを確認）。

**推奨**：案 K。決定事項（タグ一覧の生成は独立スクリプト）と合い、プラグインの将来に左右されない。tags プラグインは最初は使わない。Zensical に移ったあとで検索のタグ絞り込みが欲しくなったら、スクリプトで `tags` を書き足す（または T に移る）ことを検討する。T を選ぶ場合も、語彙とタグの組み合わせ（各軸ちょうど1つ）はスクリプトで検査する。

案 K で使ったテンプレートの上書き（MkDocs と Zensical の両方で動作確認）：

```jinja
{% extends "base.html" %}
{% block content %}
  {% if page and page.meta and page.meta.level %}
    <div class="kp-meta">
      <span class="kp-badge kp-level-{{ page.meta.level }}">レベル: {{ page.meta.level }}</span>
      {% if page.meta.field %}<span class="kp-badge">分野: {{ page.meta.field }}</span>{% endif %}
      {% if page.meta.id %}
        <label><input type="checkbox" data-kp-understood="{{ page.meta.id }}"> 理解した</label>
      {% endif %}
    </div>
  {% endif %}
  {{ super() }}
{% endblock %}
```

バッジを一覧ページへのリンクにする場合は、`{{ base_url }}/guide/levels/#{{ page.meta.level }}` のように組み立てる（一覧ページの見出しを日本語のアンカーにしておく）。

#### 3.1.3 日本語の検索

仕組みと実験結果は §2.4。**推奨設定**（設定 E 相当。文字の範囲は実際の文字で書く。「゠-ヿ」はカタカナ、「぀-ゟ」はひらがな、「一-鿿」は漢字の範囲）：

```yaml
plugins:
  - search:
      lang: ja
      # 空白・句読点に加えて、カタカナ・ひらがな・漢字・英数字の境目でも区切る
      separator: '[\s　\-、。，．・：；！？「」『』（）()\[\]/:]+|(?<=[゠-ヿ])(?=[^゠-ヿ])|(?<=[^゠-ヿ])(?=[゠-ヿ])|(?<=[぀-ゟ])(?=[^぀-ゟ])|(?<=[^぀-ゟ])(?=[぀-ゟ])|(?<=[A-Za-z0-9])(?=[一-鿿])|(?<=[一-鿿])(?=[A-Za-z0-9])'
      pipeline: [stemmer, stopWordFilter]
      fields:
        tags:
          boost: 2      # tags を使う場合。既定の 1,000,000 は強すぎる
```

注意点：

- 後読み（`(?<=…)`）を使うので、Safari 16.4 より前の iOS では検索の正規表現が作れない（MDN の対応表を参照）。対象の端末が新しければ問題ない
- 別名（セグ木・segtree など）は本文の冒頭に書く。front matter の `aliases` は検索に入らない
- 日本語の段落を途中で改行しない（1段落1行）。Chromium では改行が空白として描画された（「あいう⏎えお」の幅が改行なしより 5px 広い）
- `search.suggest`（入力補完）は日本語の分かち書きと相性が悪いと考えられるので、有効にしない（未検証）
- Zensical は `lang`・`pipeline`・`fields` を無視し、`separator` だけを使う（https://zensical.org/docs/compatibility/mkdocs/plugins/）。上の設定を書いたまま移行しても害はない（Zensical で同じ結果になった）
- 400 ページ・130 万字でも、検索の準備は 2 秒程度だった（§2.5）。instant navigation 中は索引が保持されるので、最初の1回だけ待つ

#### 3.1.4 数式（KaTeX と MathJax）

| 観点 | KaTeX | MathJax 4 |
| --- | --- | --- |
| 大きさ（gzip） | 76KB＋CSS 3.5KB＋使うフォントだけ | 281KB＋フォント |
| 描画の速さ | 速い（同期的） | 遅め（非同期） |
| 記法 | 競プロで使う範囲は足りる（下の試験） | より広い。長い式の自動折り返し（v4 の新機能）、読み上げ（アクセシビリティ）が強い |
| 版の動き | 0.18.0 で CSS のクラス名に接頭辞（独自 CSS を書いていると壊れる）、0.19.0 で strict の扱いが変わった | v3 → v4 で設定が一部変わった |

KaTeX 0.16.47 で次の 22 式を試し、すべて描画できた：床関数（`\left\lfloor \frac{N}{i} \right\rfloor`）、`\pmod`、`\bmod`、`\binom`、二重和、`aligned`（DP の遷移式）、`cases`、`\operatorname{lcm}`、`\gcd`、`\oplus`、`\log^2`、`\text{区間の和}`、`\mathop{\mathrm{argmax}}`、`pmatrix`、`\lvert S \rvert`、`\xleftarrow{\text{更新}}`、`\overline`、`\vec`、`\mathbb{Z}`、`align` 環境、`\prod_{p \mid n}`。数式の中に日本語をそのまま書くと strict の警告（`unicodeTextInMathMode`）が出る（描画はされる）ので、`\text{…}` で囲む決まりにする。表の中では `|` が表の区切りと衝突するので `\lvert … \rvert` や `\mid` を使う。

**推奨**：KaTeX 0.16 系の最新（0.16.47）を `docs/assets/vendor/katex-0.16.47/` に同梱する（`katex.min.js`・`katex.min.css`・`contrib/auto-render.min.js`・`fonts/*.woff2`、LICENSE も置く）。Material の公式例は `unpkg.com/katex@0/...` を読むが、`@0` は版が固定されず、0.18 以降の破壊的変更を受けるので使わない。描画は arithmatex が出した要素だけに限る（本文中の `$` の誤認を防ぐ）。

```yaml
markdown_extensions:
  - pymdownx.arithmatex:
      generic: true
extra_css:
  - assets/vendor/katex-0.16.47/katex.min.css
extra_javascript:
  - assets/vendor/katex-0.16.47/katex.min.js
  - assets/vendor/katex-0.16.47/contrib/auto-render.min.js
  - assets/js/katex-init.js
```

```js
// assets/js/katex-init.js：instant navigation でページが替わるたびに呼ばれる
document$.subscribe(({ body }) => {
  body.querySelectorAll(".arithmatex").forEach((el) => {
    if (el.dataset.kpRendered) return;
    renderMathInElement(el, {
      delimiters: [
        { left: "\\(", right: "\\)", display: false },
        { left: "\\[", right: "\\]", display: true },
      ],
      throwOnError: false,
    });
    el.dataset.kpRendered = "1";
  });
});
```

ブロックの数式は Material の CSS で横スクロールになる（`.md-typeset div.arithmatex{overflow:auto}`、スマホでは左右の余白も調整される）ので、長い式がページをはみ出すことはない。

#### 3.1.5 Mermaid

Material は `pymdownx.superfences` の custom fence を設定するだけで Mermaid を描く。instant navigation とダークモードに自動で対応する（https://squidfunk.github.io/mkdocs-material/reference/diagrams/）。試作のダイクストラ法のページで、instant navigation 後にも描画されることを確認した。

注意：Material は Mermaid 本体を `https://unpkg.com/mermaid@11/dist/mermaid.min.js` から実行時に読み込む（9.7.7 の bundle で確認。Zensical も同じ）。版は 11 系の最新に追従し、unpkg が落ちていると図が出ない。Mermaid 12（2026-09-10）が出ているが、11 系に留まるので当面は問題ない。図は Shadow DOM の中に描かれる。

**推奨**：フローチャートや状態遷移など、小さな静的な図に限って使う。知識マップのような大きな図や、教材の要になる図は自前の SVG・JS にする。

#### 3.1.6 折りたたみ（確認問題）と囲み（ACL の対応）

2つの書き方がある。

| 書き方 | 例 | 長所 | 短所 |
| --- | --- | --- | --- |
| admonition＋details（字下げ） | `??? question "なぜ？"` の次の行から4字下げ | Material の定番 | 中身が字下げされるので、空行のあとの段落は一般的な Markdown ツールではコードブロックとみなされる。textlint が中身を検査しない（試作で確認）。GitHub 上でもコードとして表示される |
| `pymdownx.blocks`（`///` 記法） | `/// details \| 確認問題：なぜ？` … `///` | 中身を字下げしない。textlint が中身を検査できた。出力 HTML は字下げ記法と同一 | 記法が新しく、例が少ない |

**推奨**：`pymdownx.blocks.admonition` と `pymdownx.blocks.details` を使い、囲みと確認問題は `///` 記法で書く。MkDocs と Zensical で同じ HTML（`div.admonition`・`details`）になることを確認した。

```markdown
/// note | ACL での対応
`atcoder::segtree<S, op, e>`。`prod(l, r)` で区間積を求める。
///

/// details | 確認問題：なぜ $O(\log N)$ になるのか
    type: question

区間の長さが毎回半分になるからである。
///
```

#### 3.1.7 コードハイライトとコード片

`pymdownx.highlight`（`anchor_linenums: true`、`line_spans: __span`、`pygments_lang_class: true`）＋`pymdownx.superfences`＋`pymdownx.inlinehilite`、`content.code.copy` でコピーボタン。C++ は Pygments の `cpp` で問題なく色付けされた。コード片の取り込みと検証は §3.9。

#### 3.1.8 独自の JS・CSS と instant navigation

- instant navigation は、ページ遷移で HTML を再読み込みせず中身だけを差し替える。差し替えのたびに `document$`（RxJS の Observable）が通知されるので、初期化処理は `document$.subscribe(({ body }) => …)` の中に書く（https://squidfunk.github.io/mkdocs-material/customization/）
- 初期化は**何度呼ばれても安全**にする（要素に `data-kp-mounted` を付けて二重の初期化を防ぐ）。`window` へのイベント登録は `subscribe` の外で1回だけ行う
- ページ本文に書いた `<script>` は、instant navigation で移動するたびに再実行された（試作で回数を数えて確認）。ページ専用の小さな処理は本文に書いてもよいが、二重登録に注意する
- 重いライブラリ（知識マップの Cytoscape.js など）は、対象の要素があるページでだけ動的に読み込む（Material が Mermaid でしている方式）。読み込み先は `document.currentScript.src` を基準に組み立てると、サイトの置き場所（`/kyopro-atlas/`）に依存しない
- **instant navigation は `site_url` に依存する**。sitemap.xml の URL と配信元が一致しないと働かず、通常の遷移になる（`python -m http.server` で配信すると働かず、`site_url` をローカルの URL に変えると働いた）。本番（`https://yuukougun.github.io/kyopro-atlas/`）と `mkdocs serve` では問題ない
- `navigation.tracking`（スクロールに合わせて URL の `#…` を書き換える）を有効にしたまま、`#` 付きのリンクで instant navigation すると、前のページの見出し名が URL に残る現象がヘッドレス環境で起きた。実害は小さいが、必要性も低いので有効にしなくてよい

#### 3.1.9 front matter

- YAML の注意：値に `:` や `#` を含む文字列は引用符で囲む。`2026-10-21` は日付型、`no`・`on` は真偽値に変わる（PyYAML は YAML 1.1）。独立スクリプトも `yaml.safe_load` で読むので、ビルドと同じ解釈になる
- テンプレートからは `page.meta.<キー>` で読める（MkDocs・Zensical の両方で確認）
- 自作のキー（`id`・`level`・`field` など）は MkDocs・Material・Zensical のどれも使っていない。ただし Material が意味を持たせているキー（`title`・`description`・`tags`・`hide`・`search`・`status`・`template`・`icon`・`subtitle`）とは名前をぶつけない
- `hide: [toc]` などで要素を隠せる。`search: {exclude: true}` で検索から外せる（Zensical も対応）

#### 3.1.10 テンプレートの上書き

`theme.custom_dir: overrides` を設定し、`overrides/main.html` で `{% extends "base.html" %}` のうえ、必要なブロックだけを上書きする（`block content` に `{{ super() }}` を残す）。ブロック単位の上書きは版の違いに強い。Zensical は MiniJinja で描画するので、Python の関数呼び出しを使わない（9.6.18 以降のテンプレートを元にした上書きはそのまま動く、と Zensical の移行ガイドにある。試作でも動いた）。

#### 3.1.11 ダークモード

`palette` に「OS の設定に従う」「ライト」「ダーク」の3つを並べる。独自の CSS・SVG の色は Material の CSS 変数（`--md-default-fg-color`・`--md-default-bg-color`・`--md-code-bg-color`・`--md-primary-fg-color`・`--md-accent-fg-color` など）だけで指定すると、切り替えに自動で追従する（試作の動く図で、ライト `rgb(245,245,245)`、ダーク `rgb(39,42,53)` に変わることを確認）。

```yaml
theme:
  palette:
    - media: "(prefers-color-scheme)"
      toggle: { icon: material/brightness-auto, name: ライトモードに切り替え }
    - media: "(prefers-color-scheme: light)"
      scheme: default
      primary: indigo
      accent: indigo
      toggle: { icon: material/brightness-7, name: ダークモードに切り替え }
    - media: "(prefers-color-scheme: dark)"
      scheme: slate
      primary: indigo
      accent: indigo
      toggle: { icon: material/brightness-4, name: システム設定に従う }
```

Canvas で描くライブラリ（Cytoscape.js）は CSS 変数を直接読めない。次の2点に注意する（試作で確認）。

- Material の色は `#000000de` のような8桁の16進数で、Cytoscape.js は読めない（「invalid」と警告して無視する）。一度 `span` の `color` に入れて `getComputedStyle` で `rgb()`/`rgba()` に変換して渡す
- Cytoscape.js は `rgba()` の透明度を捨てる（`rgba(10,20,30,0.32)` が `rgb(10,20,30)`、不透明度 1 になる）。透明度は `background-opacity`・`line-opacity` に分けて渡す
- テーマを切り替えたら色を付け直す（`body` の `data-md-color-scheme` の変化を `MutationObserver` で見る）

#### 3.1.12 スマホ表示

Material は標準でスマホに対応している（ナビゲーションは引き出し式）。iPhone 13 相当（幅 390px）で試作を表示し、横方向のはみ出しがないこと、動く図のボタンが 44×44px（指で押せる大きさ）であることを確かめた。

- 自作の部品は `display: flex; flex-wrap: wrap` で折り返し、SVG は `viewBox` と `width: 100%` で縮める
- ボタンの記号に「⏮」「⏭」などの文字を使うと、フォントにない端末で豆腐（□）になった。アイコンは SVG で描く
- 知識マップは高さ 70vh 程度にし、地図の外を触ればページをスクロールできるようにする（Cytoscape.js はピンチ操作に対応）

#### 3.1.13 そのほか日本語で気をつけること

- **見出しのアンカー**：既定の `toc` の slugify は非 ASCII 文字を落とすので、日本語の見出しが `_1`・`_2` のような番号になる。`pymdownx.slugs.slugify` を使うと `#練習問題` になる（両ビルダーで確認）。日本語のアンカーはリンク検証の対象にもなる

  ```yaml
  markdown_extensions:
    - toc:
        permalink: true
        slugify: !!python/object/apply:pymdownx.slugs.slugify
          kwds:
            case: lower
  ```

- **用語の自動ツールチップ**：`abbr` 拡張は単語の境目でしか一致しないので、「セグ木を使う」のように日本語の文中ではツールチップが付かなかった（前後が空白なら付く）。用語集へのリンクは本文に明示的に書く。9.7.0 の instant previews（リンクにマウスを乗せると見出しの中身を表示）は用語集へのリンクに使える
- **フォント**：`theme.font: false` にして Google Fonts を読まない。Roboto は日本語の字形を持たず、OS の日本語フォントが使われる

### 3.2 Zensical への移行に備える

#### 現状（2026-10-21）

- 最新は 0.0.71（2026-10-16、alpha）。**2026-11-05 に 0.1.0 を出し、「信頼できる版の系列」を始める**と予告している。1.0 は「公開 API が安定したことを追認するだけ」の位置づけ（https://zensical.org/upcoming-changes/）
- `mkdocs.yml` をそのまま読む。設定はそのまま使い続けてよく、`zensical.toml` への移行は必須ではない（https://zensical.org/docs/compatibility/mkdocs/migration/）
- **未対応の設定は `hooks`**。コマンドの違い：`gh-deploy` と `get-deps` がない
- テーマは `modern`（既定）と `classic`（Material と同じ見た目）。HTML の構造は同じ
- テンプレートは MiniJinja。Python の関数は呼べない
- プラグイン：tags・search・meta・blog・redirects・macros（制約あり）・llmstxt・include-markdown など多数を Zensical 自身が再実装している。**未対応のプラグインの設定は黙って無視され**、対応プラグインの未知の設定はエラーになる（https://zensical.org/docs/compatibility/mkdocs/plugins/）
  - tags：`tags_allowed`・`tags_hierarchy`・一覧に対応。`export`（`tags.json`）は非対応。Python の関数を渡す設定（`tags_slugify` など）は非対応
  - search：`separator` だけを使う。`lang` は `theme.language` から取る
  - gen-files：非対応。「生成スクリプトは Zensical のビルドとは別に実行し、生成物をバージョン管理に入れよ」と公式が勧めている。これは本プロジェクトの方針（独立スクリプト）と一致する
  - 予定：privacy・git 系プラグイン・optimize。Python でモジュールを書く API（Module API for Python）は「次に取り組む」段階（https://zensical.org/roadmap/）
- 検索は新しい実装で、日本語に強い（§2.4）。リンク検証は既定で有効（§3.9）

#### 試作での確認

§2.3 のとおり、試作の `docs/`・`mkdocs.yml`・`overrides/` は Zensical 0.0.71 でそのまま動いた。Material と違ったのは、`tags.json` が出ないこと、検索の画面と挙動、リンク検証の警告の範囲だけだった。

#### 依存を避けるべき箇所

| 避けるもの | 理由 | 代わり |
| --- | --- | --- |
| MkDocs の hooks（`hooks:`） | Zensical は非対応 | 独立スクリプト（ビルドの前に実行） |
| 自作の MkDocs プラグイン、mkdocs-gen-files、mkdocs-macros の高度な機能 | 未対応か制約が大きい。Python のモジュール API はまだない | 独立スクリプトで Markdown・JSON を生成してコミット |
| tags プラグインの `tags.json`（export）や Python の関数を渡す設定 | Zensical は非対応 | スクリプトが front matter を直接読む |
| テンプレートでの Python 関数の呼び出し、`page.file` などの MkDocs 固有のオブジェクト | MiniJinja では使えない | `page.meta` と `page.url` だけを使う |
| Material の内部のクラス名や JS の内部 API に強く依存する CSS・JS | 版で変わりうる | CSS 変数と `document$` だけを使う |
| 検索の内部設定（`pipeline`・`fields`）に頼った機能 | Zensical は無視する | 検索に頼らない入口（逆引き辞典・一覧ページ）を作る |

#### 推奨

- 決定どおり Material 9.7.7 で始める。CI に **Zensical の試験ビルド**（版を固定、`continue-on-error: true`）を加え、互換が崩れたらすぐ気づけるようにする
- Zensical 0.1.x が出たら（2026-11-05 以降）、全ページの描画・検索・リンク検証を比べ、Material の EOL（2027-05-05）より前に切り替えを判断する。切り替えはビルドのコマンドを `mkdocs` から `zensical` に変えるだけで済む見込み
- 移行時は `theme.variant: classic` を指定すると見た目が変わらない

### 3.3 動く図（ステップ送りの可視化）

#### 選択肢

| 手段 | 長所 | 短所 |
| --- | --- | --- |
| **素の JS＋SVG（自作の小さな部品）** | 依存なし。CSS 変数でダークモードに追従。DOM なので文字が選べ、拡大しても鮮明。部品の作りを統一しやすい | 描画のコードを自分で書く |
| D3（d3-selection・d3-transition など、ISC） | データと要素の対応づけ、アニメーション、ズーム | 学習コスト。ステップ送りの仕組みは結局自作。全部入りは gzip 92KB |
| JSAV（アルゴリズム可視化専用、MIT） | 配列・木・グラフとスライドショーの部品がある | jQuery に依存、npm の最終版が 2022 年。見た目が古い |
| Canvas 系（Konva・p5.js など） | 大量の図形に強い | ダークモードに CSS で追従しない。p5.js は LGPL |
| Mermaid＋内容タブ（`pymdownx.tabbed`） | JS を書かずに「手順1／手順2…」をタブで見せられる | 動きはない。図ごとに Mermaid を書く |
| 動画・GIF | 作るのは簡単 | 重い。ダークモードに追従しない。止めて考えられない |

#### 推奨：素の JS＋SVG の「状態の列」方式

試作の二分探索（lower_bound）で確かめた方式：

1. アルゴリズムを最後まで実行して、各ステップの状態（`lo`・`hi`・`mid`・説明文）を配列に全部記録する
2. 描画関数は「i 番目の状態を描く」だけにする。前へ・次へ・最初・最後・スライダーは i を変えるだけ
3. 説明文は `aria-live="polite"` の要素に出す（読み上げ対応）。キーボードの左右キーでも動かす

この方式の利点：前へ戻る処理が要らない。状態の列だけを取り出して検査できる（Python で同じアルゴリズムを動かし、状態の列が一致するかを CI で比べることもできる）。描画を変えてもアルゴリズムは壊れない。

ページへの埋め込み方：本文に `<div class="kp-viz" data-viz="binary-search" data-array="[1,3,3,5,8,13,21,34]" data-target="8"></div>` を書き（`md_in_html` が要る）、共通の JS が `document$` で `[data-viz]` を探して部品を取り付ける。部品ごとに `assets/js/viz/<名前>.js` を分け、`extra_javascript` に並べるか、`data-viz` の値に応じて動的に読み込む。

壊れにくくするための約束：

- 外部ライブラリを使わない（使うなら版を固定して同梱）
- 取り付けは何度呼ばれても安全にする（`data-kp-mounted`）
- 色は CSS 変数だけ。ボタンは 44px 以上。SVG は `viewBox` で縮める
- 入力は `data-*` 属性に JSON で書く。部品は入力が壊れていたら説明文にエラーを出す
- JS が動かない環境（GitHub 上の表示、Claude が Markdown を読む場合）のために、図の直前に「何を見せる図か」を1文で書く

### 3.4 知識マップ

要件：数百ページの前提関係（有向グラフ）を描き、クリックでページへ移動し、「理解した」で色分けし、レベル・分野で絞り込む。

| ライブラリ | 描画 | 階層（DAG）の配置 | 大きさ（gzip） | ライセンス | スマホ | 評価 |
| --- | --- | --- | --- | --- | --- | --- |
| **Cytoscape.js＋cytoscape-dagre** | Canvas | dagre（拡張に内蔵） | 136KB＋16KB | MIT | ピンチ・パン・タップ対応 | 推奨。グラフ操作の API（祖先・子孫の取得）が豊富で、「このページの前提だけを強調」が簡単 |
| Cytoscape.js＋ELK（cytoscape-elk＋elkjs） | Canvas | ELK layered（配置の質が高い） | 136KB＋466KB | elkjs は EPL-2.0 または GPL-3.0 | 同上 | 重い。配置も dagre の2倍遅かった |
| vis-network | Canvas | 組み込みの hierarchical | 150KB | Apache-2.0 または MIT | 対応 | 代替。設定だけで動くが、大きなグラフの物理演算が重くなりがち |
| D3（＋d3-dag） | SVG | d3-dag の Sugiyama | 92KB＋α | ISC・MIT | ズームは d3-zoom で自作 | SVG なので CSS とリンクが素直。自作の量が多い |
| Sigma.js（＋graphology） | WebGL | なし（力学モデル。座標を事前計算する） | — | MIT | 対応 | 数千頂点向けで、本件には過剰 |
| Graphviz をビルド時に実行（`dot` または @viz-js/viz）して SVG を出力 | SVG（静的） | dot（DAG の配置が最も整う） | 実行時のライブラリなし | Graphviz は EPL、viz-js は MIT | パン・ズームは別のライブラリ | 最も壊れにくいが、絞り込みで配置を変えられない |
| Mermaid | SVG | dagre | 788KB（読み込み済みなら追加なし） | MIT | — | 数百頂点では遅く読みにくい。各ページの「前後のページ」程度の小さな図には使える |

**推奨**：Cytoscape.js 3.34＋cytoscape-dagre 4.0 を `docs/assets/vendor/` に同梱し、知識マップのページでだけ動的に読み込む。データは独立スクリプトが生成した `graph.json`（頂点：id・タイトル・レベル・分野・URL・問題 ID、辺：前提→ページ）。

- 試作：タップで instant navigation のままページへ移動（一時的な `<a>` を作ってクリックさせる）、レベルのチェックボックスで絞り込み（該当しない頂点を薄くする）、「理解した」ページの頂点を強調色に。MkDocs と Zensical の両方で動いた
- 性能：400 頂点・508 辺で配置 0.26 秒（CPU 1/4 で 1.1 秒）。数百頂点なら実行時の配置で足りる。遅くなったら、ビルド時に座標を計算して `graph.json` に入れ、`preset` 配置にする
- 全体図は数百頂点が並ぶとスマホでは読めないので、**分野ごとの表示**と**「選んだページの前提をすべて（祖先）と、次に読むページ（子孫）」だけを表示する機能**を最初から設計に入れる（Cytoscape.js の `predecessors()`／`successors()` で数行）
- ラベルが隣の頂点と重なった（dagre は頂点の大きさしか考えない）。頂点を角丸の四角にして、ラベルを中に入れ、幅をラベルに合わせる（`width: label` など）と重ならない
- Canvas は読み上げに対応しないので、同じ内容を表（レベル別一覧）でも提供する
- CDN と同梱：同梱を推奨する。CDN（jsDelivr・unpkg・cdnjs）は版を固定すれば使えるが、CDN の障害の影響を受け、オフラインで確認できない。同梱しても合計 1MB 程度で、GitHub Pages の制限に比べて小さい。同梱するときは LICENSE を一緒に置き、版をディレクトリ名に入れる

### 3.5 LLM 向けの索引ファイル

#### 慣習：llms.txt（v2）

https://llmstxt.org/ の提案。要点：

- Markdown のファイル。必須は H1（サイト名）だけ。続けて引用（`>`）で要約、見出しなしの説明、H2 の区切りごとに「`- [名前](URL): 説明`」の一覧。「Optional」という H2 は省略してよい情報
- サイトのルートか、任意のパスに置ける。**GitHub Pages のプロジェクトサイトは `/.well-known/` を持てないので、自分のディレクトリに置けばよい**と明記されている（本件は `https://yuukougun.github.io/kyopro-atlas/llms.txt`）
- 各ページの Markdown 版を、同じ URL に `.md` を付けた場所（ディレクトリ形式の URL なら `index.md`）に置くことを勧めている
- `llms.txt` 自体は文脈に収まる大きさに保ち、詳細はリンク先に置く

#### Markdown か JSON か

試作の 14 ページ分で比べた：llms.txt（Markdown、URL 込み）3,044 字、JSON（整形）3,758 字、JSON（詰め）2,990 字、JSON（`ensure_ascii=True`）7,053 字。

- 文字数は Markdown と詰めた JSON で同程度。JSON はキー名と引用符の分だけ冗長で、`ensure_ascii` を有効にすると日本語が `\u` の並びになり2倍以上に膨らむ（トークンの浪費が大きい）
- Claude が読むには Markdown が自然で、1行1ページなら RAG の断片検索（§3.6）でも1件ずつ完結する
- サイトの JS が読むには JSON がよい

**推奨**：同じデータから2種類を生成する。

- `docs/llms.txt`（Claude 用、Markdown）：H1、要約、使い方の説明（「各行はタイトル（id、レベル、分野）：要約。前提／別名／問題のサイン／リポジトリ内のパス」）、レベルまたは分野ごとの H2、1ページ1行。生成日時とコミットを書く（claude.ai 側の同期が古いことに気づけるように）
- `docs/assets/data/graph.json`（サイト用、JSON、`ensure_ascii=False`）

大きさの目安：1行 250〜400 字なので、500 ページで 15〜20 万字程度になる。大きすぎるときは、`llms.txt` は「タイトル・id・レベル・分野・1行要約」だけにし、別名・サインなどの詳細は分野ごとの索引ファイル（`docs/index/<分野>.md` など）に分ける。

各ページの Markdown 版の公開：ビルドの後に、`docs/` の各 `.md` を `site/<ページの URL>/index.md` へ写す小さなスクリプトを CI で実行すれば、claude.ai の web fetch で最新の本文を読める（§3.6）。コード片の取り込み（`--8<--`）は展開してから写す。

### 3.6 claude.ai のプロジェクトと GitHub 連携

#### 仕組み（公式ヘルプで確認）

- **GitHub 連携**（https://support.claude.com/en/articles/10167454-use-the-github-integration）
  - プロジェクトの知識の「＋」→「GitHub」で、リポジトリを検索するか URL を貼り、**ファイルブラウザで特定のファイル・フォルダを選ぶ**
  - 「Sync」で最新にする。「Sync now」は**以前に選んだすべてのファイル・フォルダを更新する**。自動では同期されないので、教材を更新したら手で同期する（要件 §7 のとおり）
  - 「Configure files」で選ぶ範囲を変えられる。ヘルプは「トークンの上限に収まるよう、要らないファイルは選ばない」ことを勧めている
  - 取得されるのは**特定のブランチのファイル（名前と中身）だけ**。コミット履歴・PR・そのほかのメタデータは取得されない
  - 複数のリポジトリを入れられるが、「コンテキストウィンドウに収まる必要がある」と書かれている
- **プロジェクトの知識と指示**（https://support.claude.com/en/articles/9519177-how-can-i-create-and-manage-projects）：知識はプロジェクト内のすべてのチャットで使われる。指示（project instructions）はプロジェクト内のすべてのチャットに適用される。チャット間で文脈は共有されない（知識に入れたものだけが共有される）
- **ファイルの上限**（https://support.claude.com/en/articles/8241126-upload-files-to-claude）：プロジェクトのファイルは1つ 30MB まで、数は無制限だが合計がコンテキストウィンドウに収まる必要がある（有料プランは次の RAG で拡張される）
- **コンテキストウィンドウ**（https://support.claude.com/en/articles/8606394-how-large-is-the-context-window-on-paid-claude-plans）：有料プランのチャットでは、Opus 5.5・Sonnet 5.5・Haiku 5.5 などが 100 万トークン、一部の旧モデルが 50 万トークン、それ以外は 20 万トークン
- **知識が多いときの挙動（RAG）**（https://support.claude.com/en/articles/11473015-retrieval-augmented-generation-rag-for-projects）
  - 有料プラン（Pro・Max・Team・Enterprise）だけ。知識がコンテキストウィンドウの上限に近づくと**自動で RAG モードに切り替わり**、容量が**最大 10 倍**になる。利用者は切り替えを選べない。知識が減れば元に戻る
  - RAG モードでは、Claude は**プロジェクト知識の検索ツール**を使い、関係する部分だけを取り出して読む。全体を一度に読み込まない
  - 勧められていること：説明的なファイル名、関連する内容を同じプロジェクトにまとめる、質問のときに文書名を挙げる
- **Web ページの取得**（https://support.claude.com/en/articles/10684626-enable-and-use-web-search）：「Web search」を有効にすると、**URL を渡せば Claude がそのページの中身を取得できる（web fetch）**。新しい体験の画面では切り替えがなく、Claude が必要に応じて検索する。API の web fetch ツールの仕様（https://platform.claude.com/docs/en/agents-and-tools/tool-use/web-fetch-tool）では、取得できるのは**会話に現れた URL（利用者のメッセージ、ツールの結果、以前の検索・取得結果に含まれる URL）だけ**で、Claude 自身の出力やシステムプロンプトにだけある URL は取得できない。JS で描くページは読めない（静的な HTML・テキスト・PDF は可）。結果はキャッシュされる
- **新しい Projects（beta）**（https://support.claude.com/en/articles/9517075-what-are-projects 、https://code.claude.com/docs/en/claude-projects）：Claude Code のクラウドセッションを使う新しい形のプロジェクトが、Pro・Max の一部から順に提供されている。各スレッドが**プロジェクトのリポジトリを clone して始まり**、リポジトリの `CLAUDE.md` と `.claude/skills/` を読み込む。プロジェクトの指示は 16,000 字まで。既存のチャットのプロジェクトは、新しい形が届くまでそのまま動く

#### 教材が数百ページ・数 MB になったとき

見積もり：400 ページ×平均 8,000 字で約 320 万字（UTF-8 で約 10MB）。日本語のトークン数は文字数と同じ桁と見込まれる（推定。token counting API（https://platform.claude.com/docs/en/build-with-claude/token-counting）で実測できる）。すると、`docs/` 全体を選んだ時点でコンテキストウィンドウ（100 万トークン）を超える可能性が高い。

1. **小さいうち**（知識が数十万トークンまで）：選んだファイルがすべてチャットの文脈に入る。索引も本文も丸ごと見えるので、「索引で探して本文を読む」流れがそのまま成り立つ。ただし毎回の会話で大きな文脈を使う（キャッシュされた部分は利用量の消費が少ない）
2. **上限に近づくと**：自動で RAG モードになる。Claude は検索ツールで断片を取り出す。**索引ファイルも断片として検索される**ので、索引全体を順に読むことは保証されない。本文も、必要な節の断片だけが取り出されうる
3. **10 倍を超えると**：それ以上は追加できない（本件の規模では当面届かない見込み）
4. **同期**：「Sync now」のたびに選んだ全ファイルを取り直す。新しく追加したページがフォルダ選択で自動的に含まれるかは、ヘルプに明記がない（**要確認**）

RAG を前提にした設計上の対策：

- 解説手順のファイルと指示に「最初に索引（`docs/llms.txt`）を検索して読む。見つからなければ、手法名・別名・英語名・問題のサインで言い方を変えて複数回検索する」と書く
- ページは1ページで完結させる。冒頭の段落にタイトル・別名・要点を書き、断片だけ取り出されても何のページか分かるようにする
- 索引は1行1ページで完結させる（行ごとに id・タイトル・パス・URL を持つ）
- 知識に入れるのは本文の Markdown・索引・解説手順だけにする。`docs/assets/`（JS・CSS・同梱ライブラリ・`graph.json`）は選ばない。コード片（`snippets/`）は、本文の `--8<--` が指す中身を Claude が読めるよう、小さいなら選ぶ

#### claude.ai から GitHub Pages を読む方法

- 公開サイトは静的な HTML なので web fetch で読める。ただし知識マップのように JS で描く部分は読めない
- 取得できるのは会話に現れた URL だけなので、**利用者が最初のメッセージに `https://yuukougun.github.io/kyopro-atlas/llms.txt` を書く**（定型文にしておく）。Claude がそれを取得すれば、中に書かれた各ページの URL は「以前の取得結果に含まれる URL」になり、続けて取得できる（API の仕様からの推定。claude.ai での挙動は**要確認**）
- この方法は同期が要らず、常に公開中の最新版を読める。キャッシュで少し古い版が返ることはある
- HTML よりも Markdown 版（§3.5 の `index.md`）のほうが余計な部分がなく、読む量が少ない

#### プロジェクトの指示の書き方

指示は短くし、詳しい手順はリポジトリのファイル（例：`claude/explain.md`）に置いて指示から参照する（要件 §7 のとおり。教材と一緒に版管理され、同期で最新になる）。指示に書くこと：

- このプロジェクトの目的（AtCoder の過去問を教材の用語で解説する）
- 最初に読むファイル（解説手順のファイル名と索引のファイル名を正確に）。RAG のときは「検索して読む」と書く
- 守ること：開催中のコンテスト（ABC・ARC・AGC）の問題は扱わない（AtCoder生成AI対策ルール）。**atcoder.jp のページを取得しない**（問題は利用者が要約かスクリーンショットで渡す）。教材にない知識はそうと明示する
- 出力の形（「ヒントだけ」か「解説まで」を最初に尋ねる、該当ページの URL を示す、など）

新しい Projects（beta）の公式例（https://code.claude.com/docs/en/claude-projects#write-project-instructions）も、目的・作業する場所・確認の方法・足りないときの振る舞い・許可が要ることを短く書く形である。

#### 方式の比較

| 方式 | 同期 | 大きくなったとき | 長所 | 短所 |
| --- | --- | --- | --- | --- |
| A. 従来のプロジェクト＋GitHub 連携で `docs/`・索引・手順を選ぶ | 手動の「Sync now」 | 自動で RAG（断片検索） | 公式の標準の使い方。オフラインのリポジトリの内容を使える | 同期忘れ。RAG では読み方を制御できない |
| B. 知識には索引と手順だけ、本文は web fetch | 不要（索引だけ同期） | 知識が小さいので文脈に全部入る | 常に最新。必要なページだけを丸ごと読める | 利用者が URL をメッセージに書く必要。web fetch の可否・キャッシュに依存 |
| C. 新しい Projects（beta） | 不要（スレッドごとに clone） | ファイルを道具で直接読む | 最も正確。`CLAUDE.md` とスキルも読まれる | beta で提供が段階的。Claude Code の利用量を使う |

**推奨**：A を基本にし、手順ファイルに B の手順（索引の URL を渡されたら取得して読む）も書いておく。C が使えるようになったら試す。

### 3.7 Claude Code のスキル

公式ドキュメント（https://code.claude.com/docs/en/skills）で確認した仕様：

- **形式**：ディレクトリに `SKILL.md` を置く。先頭に `---` で囲んだ YAML の front matter、続けて Markdown の指示。front matter は1行目が `---` のときだけ読まれ、YAML が壊れていると項目なしで読み込まれる（`/名前` では動くが、自動では選ばれない）
- **置き場所**：プロジェクト用は `.claude/skills/<スキル名>/SKILL.md`（リポジトリにコミットする）。個人用は `~/.claude/skills/`。旧形式の `.claude/commands/<名前>.md` も動く
- **呼び出し方**：`/スキル名`（引数は `$ARGUMENTS`、`$0`・`$1`、`$ARGUMENTS[0]` で受け取る）。または、`description` を見て Claude が自動で読み込む
- **front matter の項目**（すべて任意。`description` だけ推奨）：

  | 項目 | 意味 |
  | --- | --- |
  | `name` | `/` で呼ぶ名前（既定はディレクトリ名） |
  | `description` | 何をするか・いつ使うか。`when_to_use` と合わせて一覧では 1,536 字で切られるので、要点を先頭に |
  | `when_to_use` | 起動のきっかけになる言い回しなど |
  | `argument-hint`・`arguments` | 引数の補完の表示、名前付きの引数 |
  | `disable-model-invocation` | `true` で Claude が自動で読み込まない（手動の `/名前` だけ） |
  | `user-invocable` | `false` で `/` の一覧から隠す（Claude だけが使う） |
  | `allowed-tools`・`disallowed-tools` | そのターンで許可なしに使える道具／使わせない道具 |
  | `model`・`effort` | そのスキルの間のモデル・思考の度合い |
  | `context: fork`・`agent`・`background` | サブエージェントで実行する |
  | `hooks`・`paths`・`shell` | フック、対象ファイルのパターン、シェル |
  | `metadata`・`license`・`compatibility` | 自由なメタデータなど（Agent Skills の標準） |

- **書き方の推奨**（https://platform.claude.com/docs/en/agents-and-tools/agent-skills/best-practices）：`name` は64字以内で英小文字・数字・ハイフンだけ（`anthropic`・`claude` は使えない）。`description` は三人称で、何をするかといつ使うかの両方を書く。本文は 500 行以内にし、詳細は同じディレクトリの別ファイルに分けて本文から1段階でリンクする。本文は使われると文脈に残り続けるので簡潔に書く
- 呼び出された内容は会話に残るが、ファイルは再読込されない。会話の圧縮（compaction）後は各スキルの先頭 5,000 トークンだけが再添付されるので、重要な指示は先頭に書く
- 新しい Projects（beta）のクラウドのスレッドも、リポジトリの `.claude/skills/` を読み込む（§3.6）
- claude.ai のカスタムスキル（https://support.claude.com/en/articles/12512198-how-to-create-custom-skills）：フォルダを zip にしてアップロードする。コード実行の機能を有効にする必要がある。`description` は 200 字まで。更新のたびに上げ直す必要があるので、解説手順はリポジトリのファイル（GitHub 連携で同期）に置くほうが要件に合う

記録用スキルの骨格（中身は工程9で決める）：

```markdown
---
name: record-problem
description: 解けなかった AtCoder の問題を notes/ に1問1ファイルで記録する。利用者が記録を頼んだとき、または claude.ai が出した「記録用まとめ」を貼り付けたときに使う。
disable-model-invocation: true
argument-hint: "[問題ID] [原因]"
allowed-tools: Read Write Bash(python3 tools/ap.py *)
---

1. `python3 tools/ap.py show <問題ID>` で問題の実在・タイトル・difficulty を確かめる。atcoder.jp は開かない
2. `notes/<問題ID>.md` を作り、先頭の front matter に日付・問題のリンク・原因の分類・学んだこと・関連ページ・教材の改善案を書く
…
```

`notes/` は `.gitignore` 済み。記録は手元専用なので、クラウドのスレッドでは使わない（クラウドで書いても手元に残らない）ことを本文に書く。

### 3.8 GitHub Pages へのデプロイと依存の固定

#### 公式の actions（2026-10-21 時点の最新）

| action | 最新 |
| --- | --- |
| `actions/checkout` | v7.0.1 |
| `actions/configure-pages` | v6.0.0 |
| `actions/upload-pages-artifact` | v5.0.0 |
| `actions/deploy-pages` | v5.0.1 |
| `astral-sh/setup-uv` | v10.3.0 |
| `actions/setup-node` | v7.1.0 |
| `lycheeverse/lychee-action` | v2.9.0 |

GitHub の公式ドキュメント（https://docs.github.com/en/pages/getting-started-with-github-pages/using-custom-workflows-with-github-pages）の例は1つ前の版を使っているが、構成は同じ。デプロイのジョブには `pages: write` と `id-token: write` の権限と、`github-pages` 環境が要る。リポジトリの設定で Pages の公開元を「GitHub Actions」にする（`gh api -X POST repos/yuukougun/kyopro-atlas/pages -f build_type=workflow` でも設定できる）。

#### 推奨するワークフロー（`.github/workflows/deploy.yml`）

```yaml
name: deploy
on:
  push:
    branches: [main]
  workflow_dispatch:

permissions:
  contents: read

concurrency:
  group: pages
  cancel-in-progress: false

jobs:
  build:
    runs-on: ubuntu-latest
    env:
      NO_MKDOCS_2_WARNING: "1"
    steps:
      - uses: actions/checkout@v7
      - uses: astral-sh/setup-uv@v10     # 安全のためにはコミットの SHA で固定し、Dependabot で更新する
        with:
          enable-cache: true
      - run: uv sync --locked              # uv.lock が pyproject.toml と食い違えば失敗する
      - run: uv run python tools/gen_site_data.py --check   # メタデータの検査と生成物の鮮度
      - run: uv run mkdocs build --strict  # 警告（リンク切れなど）で失敗する
      - run: uv run python tools/publish_markdown.py         # 各ページの Markdown 版を site/ に写す（任意）
      - uses: actions/configure-pages@v6
      - uses: actions/upload-pages-artifact@v5
        with:
          path: site

  deploy:
    needs: build
    runs-on: ubuntu-latest
    permissions:
      pages: write
      id-token: write
    environment:
      name: github-pages
      url: ${{ steps.deployment.outputs.page_url }}
    steps:
      - id: deployment
        uses: actions/deploy-pages@v5
```

検査用のワークフロー（push と PR、デプロイとは別）に入れるもの：

- textlint（`actions/setup-node@v7`＋`npm ci`。`package-lock.json` で固定）
- コード片のコンパイルと実行：**`container: gcc:15.2.0`** のジョブで行う。GitHub のランナー（ubuntu-24.04）の GCC は 12〜14 で、AtCoder の GCC 15.2.0 と合わない。Docker Hub の公式イメージ `gcc:15.2.0` を使えば同じ版になる。ACL を使うコード片のために `atcoder/ac-library` を v1.6 で取得して `-I` に加える
- Zensical の試験ビルド（`uvx --from zensical==<版> zensical build`、`continue-on-error: true`）

#### 依存の固定

- Python：`pyproject.toml`＋`uv.lock`＋`.python-version`。CI は `uv sync --locked`（https://docs.astral.sh/uv/guides/integration/github/）。試作で、`pyproject.toml` を変えて `uv lock` しないと `--locked` が「lockfile needs to be updated」で止まることを確認した
- Node（textlint）：`package.json`＋`package-lock.json`、CI は `npm ci`
- 同梱の JS：`docs/assets/vendor/<名前>-<版>/` に置き、LICENSE を添える
- GitHub Pages の制限（https://docs.github.com/en/pages/getting-started-with-github-pages/github-pages-limits）：公開サイトは 1GB まで、デプロイは 10 分で打ち切り、帯域は月 100GB が目安。Actions でビルドする場合は「1時間に10回」のビルド制限はかからない

### 3.9 自動検証

#### 内部リンク（MkDocs 1.6 の validation）

```yaml
validation:
  omitted_files: warn
  absolute_links: warn
  unrecognized_links: warn
  anchors: warn
```

これは MkDocs の公式ドキュメントが「ほとんどのサイトに勧める最も厳しい設定」としているもの（https://www.mkdocs.org/user-guide/configuration/#validation）。`nav:` と `links:` の両方に効く。`mkdocs build --strict` で警告がエラーになる。試作で検出できたもの：

- nav にないページ（「exist in the docs directory, but are not included in the "nav"」）
- 存在しないページへのリンク
- 存在しない見出しへのリンク（**日本語のアンカー `#練習もんだい` の誤りも検出**）
- 絶対パスのリンク（`/graph/dijkstra/`）

検出できないもの：サイトの URL を直書きしたリンク（`https://yuukougun.github.io/kyopro-atlas/...`）。本文の内部リンクは相対パスの `.md` で書く決まりにし、独立スクリプトで直書きを検査する。

Zensical も既定でページとアンカーを検証し、`--strict` か `strict: true` で失敗にする（https://zensical.org/docs/setup/validation/）。設定の書き方は MkDocs と違う（`validation: {invalid_links: true, invalid_link_anchors: true, …}`）。MkDocs 形式の `validation:` を書いたままでも Zensical のビルドは通った。

#### 外部リンク

lychee（Rust 製、https://github.com/lycheeverse/lychee）を `lycheeverse/lychee-action@v2` で**週1回**（`schedule`）実行する。外部サイトの一時的な不調で毎回の push が失敗しないよう、デプロイとは分ける。**atcoder.jp は除外する**（`--exclude 'atcoder\.jp'`）。AtCoder の問題ページへの自動アクセスを避けるためで、問題 ID の実在は `tools/ap.py`（AtCoder Problems のデータ）で検査する。問題へのリンクは ID から組み立てるか、ID とリンクの一致をスクリプトで検査する。

#### front matter のスキーマ

独立スクリプトで検査する（試作の `gen_site_data.py` で実装し、誤り「level 'DP' は … のどれでもない」「前提 '動的計画法' のページがない」などを検出できた）。規則を JSON Schema（`schema/page.schema.json`）として書き、Python の `jsonschema` で検査すると、規則そのものが文書になる。スキーマで書けない検査（id の重複、前提ページの存在、循環、`aliases` が本文にあるか、問題 ID が `tools/ap.py` のデータにあるか）はスクリプトの中で行う。

```json
{
  "type": "object",
  "required": ["id", "title", "level", "field", "summary", "prerequisites"],
  "properties": {
    "id": { "type": "string", "pattern": "^[a-z0-9]+(-[a-z0-9]+)*$" },
    "title": { "type": "string" },
    "level": { "enum": ["基礎", "水", "青", "黄", "発展"] },
    "field": { "type": "string" },
    "summary": { "type": "string", "maxLength": 120 },
    "prerequisites": { "type": "array", "items": { "type": "string" } },
    "aliases": { "type": "array", "items": { "type": "string" } },
    "signs": { "type": "array", "items": { "type": "string" } }
  }
}
```

#### コード片の取り込みと検証

`pymdownx.snippets` でファイルを取り込む。`check_paths: true` にすると、ファイルがないときにビルドが失敗する（MkDocs と Zensical の両方で「Snippet at path … could not be found」で止まることを確認）。

```yaml
markdown_extensions:
  - pymdownx.snippets:
      base_path: [snippets]
      check_paths: true
```

コード片は `main` と `assert` を持つ完全なプログラムとして `snippets/<ページの id>/<名前>.cpp` に置き、見せたい部分だけを節の印で囲む。印は C++ のコメントの中に書けるので、ファイルはそのままコンパイルできる。

```cpp
int main() {
    // --8<-- [start:usage]
    vector<int> a = {1, 3, 3, 5, 8};
    auto it = lower_bound(a.begin(), a.end(), 3);  // 3 以上の最初の位置
    int idx = it - a.begin();                       // idx == 1
    // --8<-- [end:usage]
    assert(idx == 1);
}
```

本文では `--8<-- "binary-search/usage.cpp:usage"` と書くと、印の間だけが表示される（試作で確認）。検証は `g++-15 -std=gnu++23 -O2 -Wall -Wextra -fsanitize=address,undefined` でコンパイルして実行する（試作で確認。CI では `gcc:15.2.0` コンテナ）。

注意：GitHub 上や Claude が Markdown を直接読む場合、本文には `--8<--` の行しか見えない。対策は、(1) claude.ai の知識に `snippets/` も入れる、(2) 公開する Markdown 版（§3.5）では取り込みを展開しておく、のどちらか（両方でもよい）。

#### 日本語の表記揺れと文体（textlint）

試作の設定（`.textlintrc.json`）：

```json
{
  "filters": { "comments": true },
  "rules": {
    "prh": { "rulePaths": ["./prh.yml"] },
    "preset-ja-technical-writing": {
      "no-mix-dearu-desumasu": { "preferInHeader": "", "preferInBody": "である", "preferInList": "である", "strict": false },
      "ja-no-mixed-period": false,
      "sentence-length": { "max": 120 },
      "max-kanji-continuous-len": { "max": 8 },
      "no-exclamation-question-mark": false,
      "ja-no-weak-phrase": false
    }
  }
}
```

```yaml
# prh.yml（用語集と一緒に育てる）
version: 1
rules:
  - expected: セグメント木
    patterns: [セグメントツリー, セグツリー]
  - expected: 二分探索
    patterns: [2分探索]
  - expected: ダイクストラ法
    pattern: /ダイクストラ(?!法)/
```

試作で確かめたこと：

- prh は「セグメントツリー → セグメント木」「2分探索 → 二分探索」「ダイクストラ → ダイクストラ法」を検出し、`--fix` で自動修正できる
- である調の中の「です」「ます」を本文・箇条書きの両方で検出した。`no-mix-dearu-desumasu` は preset の中にも入っているので、**preset の中で設定する**（単独でも追加すると、多数決で判定する preset 側の既定と二重に動き、である調の文が誤りとされた）
- `<!-- textlint-disable -->` 〜 `<!-- textlint-enable -->` で範囲を除外できる（`textlint-filter-rule-comments`）
- front matter と `$…$` の数式は誤検出の原因にならなかった
- **字下げ記法の admonition・details は、空行のあとの段落が検査されない**（字下げがコードとみなされる）。表の中も検査されなかった。§3.1.6 の `///` 記法なら中身が検査された
- `max-kanji-continuous-len` は既定（6字）だと「単一始点最短経路」などの専門語で誤検出するので、8 程度に上げるか語ごとに許可する

だ・である調の混在の検出は `no-mix-dearu-desumasu`（`preferInBody: "である"`）で足りる。文末が体言止めや「〜だ」のときも である調として数えられる。

### 3.10 localStorage を使う進捗チェック

#### 試作した仕組み

- 保存形式：`{"version": 1, "understood": {"<ページ id>": "日付"}, "solved": {"<問題 ID>": "日付"}}` を1つのキーに保存する
- キーに名前空間を付ける：`kyopro-atlas:progress:v1`。**`yuukougun.github.io` 以下のすべてのプロジェクトサイトは同じオリジンなので、localStorage を共有する**。Material 自身も保存するキーにサイトのパスを付けて区別している
- 「理解した」：テンプレートの上書きでページ上部にチェックボックスを出す（`data-kp-understood="{{ page.meta.id }}"`）
- 「解いた」：本文の問題のそばに `<input type="checkbox" class="kp-solved" data-problem="abc999_x">` を置いた。書く手間を減らすなら、**本文中の AtCoder の問題へのリンクを JS が見つけて、横にチェックボックスを自動で付ける**方式がよい（問題 ID は URL から取る。本文は普通のリンクのままで、GitHub や Claude にも読みやすい）
- `document$.subscribe` でページが替わるたびに結び直す。別のタブでの変更は `storage` イベントで反映する
- ロードマップ：`graph.json`（ページのレベルと問題 ID）と突き合わせ、レベルごとに「理解した数／ページ数」「解いた数／問題数」を表にする。知識マップ：「理解した」ページの頂点の色を変える。どちらも instant navigation をまたいで最新の状態が出た（MkDocs・Zensical の両方）
- 例外処理：プライベートモードや容量超過で `setItem` が失敗しても、ページは壊れないようにする（try/catch）

```js
(function () {
  const KEY = "kyopro-atlas:progress:v1";
  const empty = () => ({ version: 1, understood: {}, solved: {} });
  const load = () => { try { return Object.assign(empty(), JSON.parse(localStorage.getItem(KEY) || "{}")); } catch (e) { return empty(); } };
  const save = (s) => { try { localStorage.setItem(KEY, JSON.stringify(s)); return true; } catch (e) { return false; } };
  function bind(root) {
    const s = load();
    root.querySelectorAll("input[data-kp-understood]").forEach((cb) => {
      cb.checked = !!s.understood[cb.dataset.kpUnderstood];
      cb.addEventListener("change", () => {
        const t = load();
        if (cb.checked) t.understood[cb.dataset.kpUnderstood] = new Date().toLocaleDateString("sv-SE");
        else delete t.understood[cb.dataset.kpUnderstood];
        save(t);
      });
    });
    // 「解いた」も同じ形
  }
  window.kpProgress = { KEY, load, save };
  window.addEventListener("storage", (e) => { if (e.key === KEY) bind(document); });
  document$.subscribe(({ body }) => bind(body));
})();
```

（試作では日付を `toISOString()` で作ったため UTC になった。日本時間の日付にするには上のように地方時で作る。）

#### 注意すること

- **Safari の7日ルール**：WebKit の ITP は、「Safari を使った7日間に、そのサイトを一度も操作しなかった」場合、そのサイトの localStorage・IndexedDB などを**すべて消す**（https://webkit.org/blog/10218/full-third-party-cookie-blocking-and-more/）。ホーム画面に追加したウェブアプリは別の数え方になり、実際に使った日だけを数える。iPhone で読む場合に備えて、**エクスポート（JSON を表示してコピー）とインポート（貼り付け）**をロードマップのページに用意する。ホーム画面への追加も案内する
- **ページの id を変えない**：記録の鍵はページの `id`（front matter）にする。ファイルのパスにすると、ファイルを移しただけで記録が失われる
- **形式の版**：キーに `v1` を付け、形式を変えるときは読み込み時に変換する
- 端末間で同期しない（要件どおり）

---

## 4. 推奨構成のまとめ

### 4.1 リポジトリのファイル配置（案）

```text
kyopro-atlas/
├─ mkdocs.yml
├─ pyproject.toml / uv.lock / .python-version     # Python の依存（固定）
├─ package.json / package-lock.json               # textlint（固定）
├─ .textlintrc.json / prh.yml
├─ docs/
│  ├─ <分野>/<ページ>.md                           # 本文（1ページ1手法）
│  ├─ guide/                                      # 横断ページ（一部はスクリプトが生成）
│  ├─ llms.txt                                    # 生成（Claude 用の索引）
│  └─ assets/
│     ├─ js/  css/                                # 自作の JS・CSS
│     ├─ vendor/katex-0.16.47/ cytoscape-3.34.3/ cytoscape-dagre-4.0.1/
│     └─ data/graph.json                          # 生成（サイトの JS 用）
├─ overrides/main.html                            # テンプレートの上書き（ブロック単位）
├─ snippets/<ページ id>/*.cpp                      # コード片（完全なプログラム）
├─ schema/page.schema.json                        # front matter の規則
├─ tools/                                         # 独立スクリプト（MkDocs を import しない）
│  ├─ ap.py  gen_site_data.py  check_snippets.py  publish_markdown.py
├─ claude/explain.md                              # claude.ai の解説手順（プロジェクトの指示から参照）
├─ .claude/skills/record-problem/SKILL.md         # 記録用スキル
├─ .github/workflows/deploy.yml check.yml links.yml
└─ notes/                                         # 記録（.gitignore 済み）
```

生成物のうち、Claude と GitHub 上の閲覧に要るもの（`docs/llms.txt`・生成した一覧ページの Markdown）はコミットし、CI で `--check` により鮮度を検査する。`graph.json` もコミットしておくと、手元の `mkdocs serve` がスクリプトを実行し忘れても動く。

### 4.2 `mkdocs.yml` の骨子（試作で両ビルダーで動いた設定）

```yaml
site_name: kyopro-atlas
site_url: https://yuukougun.github.io/kyopro-atlas/
repo_url: https://github.com/yuukougun/kyopro-atlas
edit_uri: edit/main/docs/

theme:
  name: material
  language: ja
  custom_dir: overrides
  font: false
  features:
    - navigation.instant
    - navigation.instant.progress
    - navigation.sections
    - navigation.indexes
    - navigation.path
    - navigation.top
    - navigation.footer
    - search.highlight
    - search.share
    - content.code.copy
    - content.tooltips
    - toc.follow
  palette: … # §3.1.11

plugins:
  - search: … # §3.1.3

markdown_extensions:
  - admonition
  - attr_list
  - def_list
  - footnotes
  - md_in_html
  - tables
  - toc: … # §3.1.13（pymdownx.slugs.slugify）
  - pymdownx.arithmatex:
      generic: true
  - pymdownx.blocks.admonition
  - pymdownx.blocks.details
  - pymdownx.details
  - pymdownx.highlight:
      anchor_linenums: true
      line_spans: __span
      pygments_lang_class: true
  - pymdownx.inlinehilite
  - pymdownx.snippets:
      base_path: [snippets]
      check_paths: true
  - pymdownx.superfences:
      custom_fences:
        - name: mermaid
          class: mermaid
          format: !!python/name:pymdownx.superfences.fence_code_format
  - pymdownx.tabbed:
      alternate_style: true

validation:
  omitted_files: warn
  absolute_links: warn
  unrecognized_links: warn
  anchors: warn

extra_css:
  - assets/vendor/katex-0.16.47/katex.min.css
  - assets/css/extra.css
extra_javascript:
  - assets/vendor/katex-0.16.47/katex.min.js
  - assets/vendor/katex-0.16.47/contrib/auto-render.min.js
  - assets/js/katex-init.js
  - assets/js/progress.js
  - assets/js/viz.js
  - assets/js/map.js        # 地図のあるページでだけ Cytoscape.js を読み込む
```

`pymdownx.betterem` は入れない（§3.1.1）。tags プラグインは案 K では入れない（§3.1.2）。

### 4.3 代替案

- **最初から Zensical を使う**：試作はそのまま動き、日本語検索は Zensical のほうが良かった。ただし決定事項で Material を固定しているので、0.1.x の評価を経て切り替える
- **tags プラグインの階層タグ（案 T）**：テーマのタグ表示と Zensical の検索のタグ絞り込みを使いたい場合
- **MathJax 4**：長い式の自動折り返しや読み上げを重視する場合
- **知識マップをビルド時の Graphviz SVG にする**：操作性より壊れにくさを優先する場合
- **claude.ai で本文を web fetch で読む方式（§3.6 の B）や新しい Projects（C）**：同期の手間をなくしたい場合

---

## 5. 設計で判断が必要な点・未確認事項・リスク

### 5.1 設計で判断が必要な点

1. **分類の軸の持ち方**：案 K（`level`・`field` などのキー＋スクリプト生成の一覧）か、案 T（階層タグ）か（§3.1.2）
2. **claude.ai での参照方式**：A（GitHub 連携で本文まで同期、大きくなると RAG）・B（索引だけ同期し本文は web fetch）・C（新しい Projects）のどれを基本にするか。解説手順のファイルの書き方がこれで変わる（§3.6）
3. **Zensical への切り替えの時期**：Material の EOL は 2027-05-05、Zensical 0.1.0 は 2026-11-05。CI の試験ビルドを並走させ、いつ評価して切り替えるか（§3.2）
4. 生成物をコミットするか（Claude に読ませる `llms.txt` と一覧ページはコミットが必要）
5. 動く図・知識マップの JS をどこまで共通部品にするか（部品の作りの約束を設計書に書く）
6. 囲み・折りたたみを `///` 記法に統一するか（textlint の検査範囲が変わる）

### 5.2 未確認事項（実機で確かめる必要があるもの）

- claude.ai の GitHub 連携で、フォルダを選んだあとに追加したファイルが「Sync now」で自動的に含まれるか
- claude.ai で、プロジェクトの知識や指示に書いた URL を web fetch で取得できるか（API の仕様では、システムプロンプトにだけある URL は取得できない）。利用者のメッセージに書いた URL と、取得した `llms.txt` の中の URL を順に取得できるか
- 教材のトークン数（日本語の文字数との比）。token counting API で実測する
- RAG モードでの検索の質（索引を検索させる指示が効くか）
- iPhone の Safari での検索（後読みの正規表現）、知識マップのピンチ操作の使い心地
- `navigation.tracking` と instant navigation の組み合わせで、前のページの見出しが URL に残る現象（ヘッドレス環境でだけ確認）

### 5.3 リスク

- **Material の保守終了（2027-05-05）**：その後に見つかった脆弱性は直らない。サイトは静的で入力を受け付けないので影響は小さいが、移行の計画は要る
- **Mermaid を unpkg から読む**：CDN の障害で図が消える。版は 11 系の最新に自動で上がる。重要な図は Mermaid に頼らない
- **KaTeX の 0.17 以降の破壊的変更**：同梱して版を固定すれば影響しない。上げるときは CSS の上書きを確かめる
- **localStorage の消失**（Safari の7日ルール、ブラウザのデータ削除）：エクスポート／インポートで退避できるようにする
- **pymdown-extensions の更新**：12.0 のように挙動が変わることがある（日本語の強調）。`uv.lock` で固定し、上げるときは全ページの差分を見る
