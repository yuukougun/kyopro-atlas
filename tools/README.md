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
| `build_ledger.py` | 問題の台帳の下書きを作る。今は `--check`（catalog との食い違い）だけ使う。台帳は手で直したので作り直さない | なし（`--check`） |
| `make_skeleton.py` | catalog から骨格のページ（stage: stub）を作る。front matter と要点の囲みだけ。あるページは上書きしない | `docs/<field>/<id>.md` |
| `gen_site.py` | front matter・本文の問題の一覧・台帳・最近の ABC から生成物を作る。`--check` で鮮度だけを見る | `nav.yml`・`docs/<field>/index.md`・`docs/lists/`・`docs/llms.txt`・`docs/index/`・`overrides/assets/data/graph.json`・手書きのページの目印の中 |
| `check_pages.py` | ページの検査（front matter の schema・id・参照・循環・レベル・問題の一覧と台帳・囲みの外の問題リンク・```cpp・要点の囲み・draft 以降の節の anchor と別名） | なし |
| `fix_problems.py` | 本文の問題の一覧の各行の label・URL・difficulty を台帳から作り直す（要約は変えない）。`- abc300_e：要約` と書けば行を作る | ページ（`--check` では書かない） |
| `check_snippets.py` | コード片を設定（compilers・flags・expect・cases）どおりにコンパイル・実行して確かめる | なし |
| `check_noai.py` | URL の robots の meta と X-Robots-Tag の noai・noimageai を調べる（atcoder.jp・codeforces.com は取得せず「既知の noai」） | なし |

front matter の規則は [schema/page.schema.json](../schema/page.schema.json)（JSON Schema Draft-07）。check_pages.py は中の小さな検査器でこれを当てる（jsonschema は要らない）。

## 工程ごとの使い方

### 工程6 土台作り・工程7 試作

```sh
python3 tools/check_pages.py                 # 試作のページ。catalog にだけある前提・related は「未作成」の警告
python3 tools/fix_problems.py --check        # 問題の一覧の行が台帳と合っているか（直すときは --check を外す）
python3 tools/check_snippets.py              # コード片（third_party/ac-library がないときは --acl ~/lib/ac-library-master）
python3 tools/gen_site.py --check            # 生成物が最新か（書くのはメインのセッション：python3 tools/gen_site.py）
python3 tools/check_noai.py https://…        # 新しいドメインを資料にする前に。結果は style-guide の記録へ
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
| 執筆者 | 担当ページを書き、stage を draft にして `check_pages.py --page <id>`・`fix_problems.py --page <id>`・`check_snippets.py snippets/<id>` を通す |
| 検証役 | `check_pages.py --page <id> -v` の警告（別名が冒頭にない、complexity が null、要点の「（執筆時に書く）」など）も見る。reviewed にすると別名の欠けはエラーになる |
| メイン | バッチの終わりに `check_pages.py`・`gen_site.py`（書く）・`gen_site.py --check`・`mkdocs build --strict` を通して commit・push |

台帳の difficulty を `ap.py` で更新したら、`fix_problems.py` で本文の diff を直し、別の commit にする（設計書 §5.4）。

### 工程10 全体の検証・定期の検査

- `check_pages.py -v`（警告まで全部）、`check_snippets.py`（すべて）、`gen_site.py --check --diff`
- CI：check.yml が `check_pages.py` と `check_snippets.py --changed --base <元>`、deploy.yml が `gen_site.py --check --diff` と `mkdocs build --strict`、snippets-weekly.yml が `check_snippets.py`（すべて）を動かす。gcc の公式コンテナには `g++-15` という名前がないので、check_snippets.py は `g++-N` がなければ版が N の `g++` を使う。コンパイラを絞るときは `--compiler g++-15`

## gen_site.py が書く手書きのページの生成部分

手書きのページに `<!-- gen:begin 名前 -->` と `<!-- gen:end 名前 -->` を置くと、その間を gen_site.py が書く（フェンスの中の目印は無視する）。一覧は `python3 tools/gen_site.py --list-blocks`。

| 名前 | 中身 | 置く想定のページ |
| --- | --- | --- |
| `home-links` | ホームの入口（知識マップ・逆引き辞典・ロードマップ・レベル別の一覧・用語の索引） | `docs/index.md` |
| `signs-phrase`・`signs-shape` | 逆引き辞典：言い回しから（kind で5つに分ける）・立てた式の形から | `guide/reverse-index-signs.md` |
| `signs-constraint` | 逆引き辞典：制約の上限の数ごとの候補のページ | `guide/reverse-index-constraints.md` |
| `terms-kana`・`terms-latin`・`terms-shared` | 用語の索引（題名・別名・acl）：かな・漢字・記号／英数字／複数のページに当たる語 | `guide/term-index.md` |
| `roadmap-order`・`recent-positions` | 色ごとのページの列（D17）・位置ごとの頻出手法（最近30回の E・F・G） | `guide/roadmap.md` |
| `recent-abc`・`problem-sets` | 最近の ABC → ページ・問題集の問題 → ページ | `guide/problem-sets.md` |
| `verify-table` | ページ → Library Checker の問題 | `guide/library-design.md` |
| `version`・`fields`・`lists`・`stage-summary` | 索引の版・分野の一覧・一覧へのリンク・制作状況の表（どこに置いてもよい） | 任意 |

- 用語の索引の漢字で始まる語は、読みがないので最初の字の順に並ぶ（読みの表か pykakasi を足すかは未定）
- 節（`#anchor`）へのリンクは、相手のページが draft 以降のときだけ付ける（stub のページには見出しがまだない）
- 生成物の Markdown には atcoder.jp の問題へのリンクを書かない（問題は ID と題名だけ。interfaces.md §3）
