# render_pages のメモリと速さ・変えたページだけ流す指定（#100）

作業ツリー：`kyopro-atlas-wt/render-perf`（ブランチ feat/render-perf）。commit・push・gen_site.py はしていない。

## 選んだ作り

- **Chrome は 1 つ、タブを `-j` 個**。browser の target に WebSocket でつなぎ（`/json/version`）、1 ページ・1 つの幅ごとに `Target.createBrowserContext` → `Target.createTarget` で新しいタブを開く。タブとは、タブごとの WebSocket（`/devtools/page/<targetId>`）で話すので、今の `Tab` クラスをそのまま使える（flattened session と、受けたメッセージを振り分けるスレッドは要らない）。調べ終えたら `Target.disposeBrowserContext` で context ごと閉じる。context が別なので描画のプロセスも別になり、閉じると終わる。メモリがたまらない
  - browser との会話は 1 本なので lock を取る。来たイベントは捨てる
  - context ごとに localStorage・キャッシュが新しい。Material の `__palette` が残らないので、次の配色の切り替えが必ず働く
- **やり直し**：開けない回（例外・読み込みの失敗・検査の JS の失敗）は、タブを閉じて新しいタブで 1 回だけやり直す（回ごとに 2 回まで。前と同じ）。タブを閉じる・開く命令に Chrome が答えなければ、Chrome を起動し直す（`Context.restart`。ほかの worker が先に起動し直していれば何もしない）。そのとき同時に開いていたほかのタブも、1 回やり直しになる
- **通信をためない**：Network の domain をやめた。api.github.com は `--host-resolver-rules=MAP api.github.com ~NOTFOUND` で名前を引けないようにして止める。Fetch の domain は、命令の答えを待つ間に `requestPaused` に答える必要があり、作りが重くなるので使わなかった。読み込めないファイルの Log の error（試験の `/img/missing.svg`）は、Network がなくても出る（試験で確かめた）
- **読み込みを減らす**：同じ幅のライトとダークは 1 回だけ読み込む。2 回目は `Emulation.setEmulatedMedia` で prefers-color-scheme だけを替え、Material が `data-md-color-scheme` を替え終わるのを待ってから、検査をもう 1 回流す
  - 検査（PROBE）は 2 回流せるようにした。1 回目に閉じていた折りたたみを `window.__kpClosed` に覚えておき、2 回目も「折りたたみの中」を正しく添える。タブの中身を見せる style は 1 回だけ足す
  - JS のエラーは、読み込みからのすべてを各回に数える（読み込み直していた版でも、読み込みの間のエラーはどの回にも出ていた）
  - 幅が違う回は、前と同じく読み込み直す
  - 検査は、ロードマップの集計の表（`.kp-roadmap-stats`。progress.js が graph.json を読んでから作る）も待つ（追加の指示）。待つのは要素のあるページだけで、上限は数式などと同じ 8 秒（WAIT_MS。検査を始めてからの合計で、配色を替えて調べ直すときはそこから数え直す）。終わりの印は、中に表ができたこと、または読めなかったときに progress.js が `data-kp-mounted` を空にしたこと。waited には足さない（JSON の形を変えない）

## 配色が読み込み直さずに切り替わるか

切り替わる。確かめたこと：

- mkdocs.yml の palette は 3 つで、最初が `media: "(prefers-color-scheme)"`（システムの設定に従う）
- Material の palette の部品（ビルドした bundle の source map の `components/palette/index.ts`）は、localStorage に `__palette` がなければ、media が合う最初の入力（上の「システムの設定に従う」。いつも合う）を選ぶ。`watchMedia("(prefers-color-scheme: light)")` が変わるたびに選び直し（`takeUntil(media$.pipe(skip(1))), repeat()`）、「システムの設定に従う」のときは今の prefers-color-scheme から scheme を決めて `data-md-color-scheme` を付け直す。保存する `__palette` も「システムの設定に従う」のままなので、切り替えのあとも追う
- 実際に比べた：mermaid・動く図・折りたたみ・タブのあるページ 100 と math/miller-rabin を、前の版（読み込み直す）と新しい版で流し、JSON の指摘と、回ごとの結果（scheme・vw・sw・culprits・counts・waited・found・console）がすべて同じだった。注意（配色が替わらない）も出ない
- 全ページでも、指摘 156 件は前の版と同じだった。回ごとの結果の違いは guide/roadmap の表の数だけ（下の「集計の表を待つ」）

## --changed の決まり

`--changed [REF]`（既定 `origin/main`）。`git merge-base HEAD REF` からの差分（`git diff --name-only --no-renames`。コミットしていない変更も入る）と、追跡していないファイル（`git ls-files --others --exclude-standard`）から選ぶ。リポジトリは `--docs` のある木。`--page`・`--field` と合わせると、どれかに当たるページ（和）を流す。関わるページがなければ Chrome を起動せずに終わる（終了コード 0）。

| 変わったファイル | 流すページ |
| --- | --- |
| `docs/<…>.md` | そのページ（消したページは何もしない）。gen_site.py の生成物（分野の入口・一覧・詳細索引・生成部分）も docs/ にあるので、`data/problems.yaml` の変更は、gen_site.py を流したあとの生成物の差分で拾う |
| `snippets/<id>/…` | id が `<id>` のページと、本文に `"<snippets からのパス>` を書いたページ（`--8<--`） |
| `docs/img/<id>/…` | id が `<id>` のページと、本文に `img/<id>/…` を書いたページ |
| `overrides/assets/js/viz/<名前>.js` | 本文に `data-viz="<名前>"` を書いたページ |
| `overrides/assets/js/map.js` | `id="kp-map"` のページ |
| `overrides/assets/js/filter.js` | `class="kp-filter"` と `id="kp-map"` のページ（map.js も使う） |
| `overrides/assets/data/graph.json` | `kp-map`・`kp-roadmap-stats`・`kp-wishlist` のページ（map.js と progress.js が読む） |
| `overrides/404.html` | 404.html |
| 共有：`mkdocs.yml`・`nav.yml`・`pyproject.toml`・`uv.lock`・overrides/ のほかのファイル（main.html・kp.css・katex-init.js・viz.js・progress.js・vendor/）・docs/ の Markdown と画像のほかのファイル | 「共有のファイルが変わったので全ページを流す（…）」と出して、全ページ |
| そのほか（tools/・tests/・planning/・data/・`docs/llms.txt`・`snippets/README.md` など） | 見ない |

このブランチで `--changed` を流すと、変わったのが tools/・tests/・planning/ だけなので「ページに関わるファイルは変わっていない（4 ファイル）」と出て終わる。`--changed HEAD~3` では overrides/main.html が入るので全ページになった。

## 測った値（全 425 ページ・390 ライト／ダーク、`mkdocs build --strict -q -d /tmp/claude-1000/rp/site`）

RSS は `ps -o rss= -C chrome-headless-shell` の合計を 1 秒ごとに測った最大（共有のページを重ねて数えるので、実際の使用量より大きい）。空きは `free -m` の available の最小（全体 15.9GB）。

| 版 | -j | 時間 | Chrome の RSS の合計の最大 | 空きの最小 | エラー・警告 |
| --- | --- | --- | --- | --- | --- |
| 前（2026-10-30 の記録） | 2 | 253 秒 | Chrome 1 つが約 6GB | 575MB | 0・156 |
| 前（今回。4 つに分けて起動し直しながら） | 2 | 45+47+40+44 = 177 秒 | 7.3GB（106 ページで） | 7.6GB | 0・156 |
| 新 | 2 | 154 秒 | 1.1GB | 13.3GB | 0・156 |
| 新（既定） | 4 | 87 秒 | 1.5GB | 13.2GB | 0・156 |
| 新 | 8 | 60 秒 | 2.6GB | 12.4GB | 0・156 |
| 新 | 12 | 52 秒 | 3.1GB | 12.3GB | 0・156 |

- 前の版は、106 ページだけでも RSS の合計が 7GB を超えた。全ページを一度に流すと空きが 2.5GB を切るおそれがあるので、4 つに分けて流し、JSON を合わせて比べた
- 警告 156 の内訳は、どの回も、幅を超える別行の数式 155（95 ページ）と math/miller-rabin#deterministic-bases の表 1 で、前と同じ
- 新しい版の -j 2・4・8・12 の JSON は、指摘も回ごとの結果もすべて同じ（並べ方によらない）
- 既定の `-j` は 4 のままにした。8 にすると約 60 秒・2.6GB で、16GB の機械ならこれも収まる
- 上の新しい版の値は、集計の表を待つ前に測った。待つようにしてから -j 4 で流し直すと、87 秒・1.5GB・空きの最小 13.0GB で、エラー 0・警告 156（同じ内訳）だった

## 集計の表を待つ（追加の指示）

最初の版では、guide/roadmap のダークで数えた表が、前の版の 11 から 14 に変わっていた。ロードマップの集計の表 3 つは progress.js が graph.json を読んでから作るのに、検査がそれを待っていなかったためである。前の版はどちらの回も読み込みの直後に測ったので 11、新しい版のダークは時間がたってから測ったので 14 になっていた。

検査がこの表を待つようにしたので、guide/roadmap はライト・ダークとも 14 になった（`--page roadmap` で 109ms・131ms）。全ページの表の合計（totals は最初の回の数）は 772 から 775 に増える。前の版と比べると、回ごとの結果の違いは guide/roadmap の 2 回の表の数だけで、指摘 156 件は同じ。増えた 3 つの表に幅の警告は出ない。docstring の 11 と 14 の違いの注記は、待つことの説明に替えた。

## 試験

- `.venv/bin/python -m unittest discover -s tests/tools`：147 件すべて通る（Chrome の描く試験も含む）
- test_render_pages.py に `ChangedTest` を足した（Chrome は要らない）。上の表の決まり（id と本文の参照・動く図・部品・404・共有のファイルで全ページ・見ないファイル）と、`git_changed`（一時のリポジトリで、分かれ目より後の main の変更を入れない・コミットした変更・コミットしていない変更・追跡していないファイル・名前を変えたものの両方・ない ref で止まる）
- 試験のページの配色の script を、Material と同じく prefers-color-scheme の変化を追うようにした（読み込み直さないので）
- 手で確かめたこと：読み込んだあとに止まるページ（無限ループ）は、回ごとに 2 回やって「開けないページ」になり、ほかのページは続く。途中で Chrome の browser のプロセスを kill すると、起動し直して全ページを調べ終え、Chrome は残らない
- `npx textlint tools/README.md planning/progress.md`：今の main と同じ 147 件（もとからある全角と半角の間の空白の指摘など）。新しい指摘はない

## 変えたファイル

- tools/render_pages.py（Browser・Page・load・probe・Context・check_page・worker・run を書き換え、`git_changed`・`changed_pages`・`--changed` を足した。PROBE は 2 回流せるようにした。docstring に Chrome の使い方・配色の切り替え・変えたページを足した）
- tests/tools/test_render_pages.py
- tools/README.md（「公開の前」に `--changed`・Chrome の使い方・選ぶページの表。やり直しの文）
- planning/progress.md（工程11 の render_pages の注記：`-j 2` 以下の注意を外し、`--changed` と測った値に替えた）
- planning/batches/fix/render-perf/render-perf.md（この報告）

## 残ったこと・確かでないこと

- 待たずに後から作られる中身がほかにあれば、2 回目からの配色でだけ数えることがある。サイトの JS（overrides/assets/js/）で後から表を作るのは progress.js の集計だけで、これは待つようにした（表の数以外の、後から作られる中身は確かめていない）
- 出力の 1 行目が「Chrome N 個」から「タブ N 個」に変わった。開けない回の文（例 `TimeoutError: …`）の形は同じ
- RSS の合計は共有のページを重ねて数える。前の版の「約 6GB」と今回の値は、同じ測り方での比べ方として見る
- `--changed` は git の差分だけを見る。サイトをビルドした木（`--docs`）と、差分を取る木が同じであることを前提にする
- `--changed` と `--field` は和にした（`--changed --field graph` は「変えたページと graph の全ページ」）。共通部分のほうが便利な場面もあるが、今の `--page`・`--field` が和なのに合わせた

## 検証の指摘への直し（どれも任意の指摘）

1. **Chrome を起動し直すのは、時間切れと接続が切れたときだけにした**（`OSError`。`TimeoutError`・`ConnectionError` を含む）。タブを開く・閉じる命令が CDP のエラー（`CDPError`）か JSON の誤りで失敗したときは、そのタブだけをやり直す。閉じる命令だけが失敗したときは、ほかのタブを巻き込まずに続ける
2. **`--changed` で --docs の木が git のリポジトリの中にないときは止める**。「`--changed: <docs> が git のリポジトリの中にない`」と出し、リポジトリの根（ROOT）の差分には切り替えない。git がないときも止める
3. **`--changed` で選んだページの数を出す**。「変わった N ファイルに関わるページ M」の形で、10 ページ以下なら名前も出す。`--page`・`--field` で足したページは数えない
4. **`--changed DIR/site` と書いても動くようにした**。site の位置引数を省けるようにし、省いたときに `--changed` の値がフォルダなら、それをサイトとして扱う（REF は既定の origin/main）。それ以外で site がなければ argparse のエラーで止める。REF は `--changed=REF` とも書けることを、help と README に書いた
5. **調べるページがなくて早く終わるときも、`--json` には空の結果を書く**（形は同じで、pages 0・findings と results は空・summary はすべて 0）。前の結果を新しいものと取り違えないためである
6. **待つ上限の説明を直した**。8 秒は「検査を始めてからの合計」で、配色を替えて調べ直すときはそこから数え直す（上の作りの節と docstring）
- README の表と docstring に「`docs/img/` の直下のファイルは、本文にそのファイルを書いたページだけ」を足した

確かめたこと：
- unittest は 147 件すべて OK
- このブランチで `--changed --json` を流すと、変わった 5 ファイルに関わるページ 0 で、Chrome を起動せずに終わった（終了コード 0）。空の JSON が書けた
- `--changed DIR/site`（site を後に書いた形）でも同じに動いた
- `--changed=HEAD~1 --field misc` では「384 ファイルに関わるページ 373」と出て、misc の分を足した 374 ページを流した
- `--docs` にリポジトリの外のフォルダを渡すと、リポジトリの中にないと出して止まった
- 引数なしでは、site がないと出して止まった
