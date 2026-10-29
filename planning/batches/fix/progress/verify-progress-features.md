# progress-features の検証（グループ progress、2026-10-29）

検証した担当：progress-features（Issue #74・#1）。報告：[progress-features.md](progress-features.md)。
作業ツリー：/home/yuuki/projects/kyopro2/kyopro-atlas-wt/progress（feat/progress。commit 前の差分を見た）。ファイルは直していない（この報告だけを書いた）。
作業用フォルダ：/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/7a638398-7759-4637-95c7-6739e8d52414/scratchpad/fix/progress/verify-progress-features（以下 `<V>`）。

## 結論

| Issue | 判定 | 直しが要る点 |
| --- | --- | --- |
| #74 進捗の拡張 | 合格 | 0 |
| #1 勉強したいリスト | 直しが要る | 1 |

## 直しが要る点

### 1. graph.json を読めないとき、一覧の全行に「このページは見つからない」と誤って出る（#1）

- **ファイルと行**：`overrides/assets/js/progress.js` 995〜996 行目（`renderWishlist()` の注記）、1059〜1062 行目（`mountWishlist()` の読めなかったときの代わり）
- **理由**：読めなかったときは代わりに `{ pages: [], fields: [] }` を使うので、`byId` が空になり、実在するページの行にも「このページは見つからない（id が変わったか、なくなった）」が付く。上の状態の文（「ページの一覧を読み込めなかった（…）。題名の代わりに id を出す。」）と食い違い、1 件外すと状態の文が「「…」を外した。」に置き換わるので、説明が消えて誤った注記だけが残る。読者が、実在するページを「なくなった」と思って外すおそれがある。担当の報告の「graph.json を読めないときも id と外す操作は出す」は動くが、注記が誤り
- **再現**：graph.json の取得を失敗させて一覧を開く（CDP の Fetch.failRequest。`<V>/cdp/t9-graphfail.mjs`）。外す前：2 行とも「このページは見つからない（id が変わったか、なくなった）・入れた日 …」。1 件外した後：状態の文は「「binary-trie」を外した。元に戻す」だけで、残った `lis`（実在する）に同じ注記（画像 `<V>/shots/t9-graphfail-after-remove-390.png`）
- **直し方の案**：代わりの graph に印を付け（例：`wishData.set(box, { pages: [], fields: [], failed: true })`）、`renderWishlist()` で `g.failed` のときは「見つからない」の注記を出さない（入れた日だけにするか、「題名を読み込めなかった」と出す）

## Issue ごとの確かめ

### #74 進捗の拡張 — 合格

完了の条件 3 つを満たす。

1. **ロードマップの列で、理解したページが見分けられる**：5 列すべて（基礎 82・水 110・青 128・黄 91・発展 83 行）の各行にチェック欄が付き、記録どおりに印（チェックと行の地の色）が付く。各行の (ページの id, 列の色) が、そのページの「理解した」の欄の組と一致することを、ビルドした HTML と graph.json で全 494 行確かめた（不一致 0。節の行は、その節の level が列の色と一致）。行で付けた記録はページの上の欄に出る。同じページの同じ帯の節の行（lis の青の 4 行など）は、いっしょに付く（切り替えの欄の注のとおり）。「理解した行を隠す」で理解した行だけが隠れ、見出しの下の数の行に「（理解した N 行を隠している）」が付く。チェック欄のない (ページ, レベル) は C++ の 19 件だけで、これは生成の作りで列に入らないもの（この直しとは関係ない）
2. **集計に difficulty の色ごとの表が出る**：3 つの表（レベル別・分野別・difficulty の色別）を、graph.json と記録から別に計算した値と比べ、すべて一致した（約 1/7 の 179 問を解いた記録で、灰 6/42・茶 19/117・緑 21/174・水 34/233・青 32/214・黄 31/190・橙 12/97・赤 2/35・difficulty なし 22/149・合計 179/1251）。帯の区切りは AtCoder の色（〜399・400〜799・…・2800〜）で、境目（400 は茶、2800 は赤）も正しい。ページの問題の行の「diff NNNN」（全 1,586 行）は graph.json の difficulty とすべて一致するので、行の色と表の帯は食い違わない。表の分母（1,251 問）は、各ページの問題の一覧の和集合と同じ（チェックできない問題を数えていない）
3. **ファイルで書き出し・読み込みができる**：下の「ファイル」の項のとおり

「やること」の 4 つ目（レベルを付け直すときの読み替えを決める）は、担当がメインへの質問 1 にした。完了の条件には入っていないが、決めて decisions.md に残すのはメインの仕事として残る。

### #1 勉強したいリスト — 直しが要る（1 点。上の 1）

それ以外は動く。

- **追加・外す**：id のある 353 ページ（study-list を除く）すべての上と下に切り替えがあり、study-list 自身と id のない 67 ページにはない（ビルドした全 HTML で数えた）。上で入れると下も塗られ、下で外すと上も外れる。記録に `wishlist: {id: 地方時の ISO 8601}` が入る。Tab で焦点が届き、Space で切り替わり、焦点の枠が見える
- **表示**：一覧に題名（ページへのリンク）・レベルの印・分野・入れた日・「✓ 理解した」（ページのレベルの記録があるとき）が出る。並べ方 4 つ（新しい順・古い順・レベルの順・分野の順）の結果が期待どおり（日付のない `true` と見つからない id は最後）。不正な id（大文字）・不正な値（数値）は捨てられる。空のときは案内の 1 文だけ
- **外す・元に戻す**：入れた時刻ごと戻り（`true` は `true` のまま）、焦点も戻る。見つからない id も外せる
- **別のタブ**：別のタブで入れたページ、外した「理解した」が、開いている一覧に直ちに出る
- **書き出し・読み込み**：`wishlist` が書き出したファイルに入り、置き換えで戻る。合わせるときは入れた時刻の早い方、日付のある方（`true` より）が残る（`KPProgress.merge` で直接確かめた）

## ファイル・古い形・instant navigation（「特に見ること」）

ヘッドレスの Chrome（chrome-headless-shell 146）を CDP で動かした（`<V>/cdp/`）。サイトは `<V>/mkdocs-verify.yml`（作業ツリーの mkdocs.yml を INHERIT し、nav に study-list を 1 行足しただけ）で `<V>/www/kyopro-atlas/` にビルドし（`mkdocs build --strict` は exit 0、警告なし）、`python3 -m http.server 47391` で配った。Material の instant navigation は sitemap の URL のホスト名だけを置き換え、ポートを残すので、`--host-resolver-rules="MAP kyopro.test 127.0.0.1:47391"` で `http://kyopro.test/kyopro-atlas/` として開いた（ポートのない URL）。サーバは使い終えて止めた。

- **ファイルに保存**：実際にダウンロードさせ（Browser.setDownloadBehavior）、`kyopro-atlas-progress-2026-10-29.json` ができた。中身は記録と同じで、`exportedAt` だけが保存の時刻、`updatedAt` は変わらない。保存の後「最後に書き出した日：2026-10-29（今日）。」、その後に記録を変えると「。その後に記録が変わっている。」が付く
- **ファイルから読み込む**：ファイル選択の画面を CDP で受けて選ばせた。公開中の progress.js が書き出す形そのもの（`JSON.stringify({solved, understood, updatedAt}, null, 1)`）のファイルを合わせる → 解いた・理解したが足され、勉強したいと `exportedAt` は今の記録のまま、`updatedAt` は今。同じファイルをもう一度合わせると記録も `updatedAt` も変わらない。保存したファイルで置き換える（2 回押しの確認あり）→ 記録がファイルと完全に一致。古い形で置き換える → `wishlist: {}`・`exportedAt: null` が足され、「まだ書き出していない」に戻る。壊れた JSON・形の違うファイル・2 MB を超えるファイルは理由を出し、記録を変えない
- **コピー**：「コピー用に表示」の JSON は記録に書き出す時刻を足したもので、コピーした時点で `exportedAt` が残る。手でのコピー（copy イベント）でも残る
- **古い形の記録（今の公開中の形）**：localStorage に `{solved, understood: {…: {"基礎": true, "青": false}}, updatedAt}` を入れて開く → そのまま読め、開いただけでは書き換えない。勉強したいを入れた時点で `wishlist` と `exportedAt: null` が足される。progress.js はこれまで 1 つの版（7086af6）しか出ていないので、古い形はこの 1 つだけ
- **instant navigation**：ロードマップで隠す切り替えを入れる → 列のリンクでページへ（再読み込みなし。window に置いた印が残る）→ 解いたのチェック欄が全行に付き、上で理解した・勉強したいを押せる → 戻る（instant）→ 切り替えは入ったまま、その行が理解した・隠れた状態、数の行も更新、集計と書き出しの欄も出る → 「リストを見る」で一覧へ（instant）→ 並べ方をレベルの順にして題名からページへ → 戻ると並べ方が残り、一覧は 1 つだけ → 一覧で外して進む（forward）とページの切り替えが外れている → ロードマップへの行き来を 2 回して、数の行 5・切り替え 1・書き出しの欄 1・チェック欄 494 のまま（二重に付かない）。最後まで再読み込みは起きなかった
- **保存できない環境**：`setItem` が例外を出す環境で、切り替えはメモリの記録で動き、instant navigation の後も残り、書き出しの欄に注意が出て、ファイルにも保存できる。localStorage の参照そのものが例外を出す環境でも、一覧・ロードマップ（チェック欄 494・表 3）が出て、行のチェック欄が動く。このとき出る例外 4 件は Material の `__md_get`（インライン）と bundle のもので、progress.js からは出ていない（前からある）
- **知識マップ**：足した形の記録で開いて例外なし、理解した数と次の候補が出る
- **見た目**：幅 390px（ライト・ダーク）と 1280px で、ページの上と下の切り替え、案内のページ（レベルなし）の切り替え、ロードマップの列・切り替えの欄・3 つの表、書き出しの欄（パネルを開いた状態とエラーの状態を含む）、一覧を撮って見た。崩れなし、横のはみ出しなし（scrollWidth = 幅）。画像は `<V>/shots/`

## 書き換えない検査

| 検査 | 結果 |
| --- | --- |
| `node --check overrides/assets/js/progress.js` | 通る |
| `python3 tools/check_pages.py --page study-list --page how-to-use --page roadmap` | エラー 0・警告 0 |
| `python3 tools/check_pages.py`（全ページ） | エラー 0・警告 0（354 ページ、問題の行 1,586） |
| `npx textlint docs/guide/study-list.md docs/start/how-to-use.md docs/guide/roadmap.md` | エラー 0。警告 5 はすべて直していない行（how-to-use 140・193・227・405 行目、roadmap 791 行目）で、前からあるもの |
| `node --test "tests/viz/*.test.mjs"` | 216 通る |
| `python3 -m unittest discover -s tests/tools` | 44 通る（2 は skip） |
| `python3 tools/gen_site.py --check --diff` | 10 ファイルが変わる（nav.yml・docs/guide/index.md・docs/lists/index.md・docs/lists/kind-guide.md・docs/llms.txt・docs/index/start.md・docs/index/guide.md・graph.json・docs/guide/term-index.md・how-to-use の生成部分）。中身は新しいページと #wishlist の節によるものだけで、想定どおり |
| `mkdocs build --strict`（nav に study-list を足した `<V>/mkdocs-verify.yml`） | exit 0、警告なし |

## 別の箇所が壊れていないか

- ほかのページから how-to-use の #progress・#backup、roadmap の #progress・#reading-order へのリンクは、どれも残っている（anchor を変えていない）
- 下の欄の「理解した」は `div.kp-links__actions` の中に移ったが、前からの `.kp-links .kp-understood { grid-column: 1 / -1; }` は子孫の指定なので効き方が変わらず、包む側も全幅にしている。kp.css は末尾への追記だけ（削除 0）
- 担当の報告の行番号（progress.js・main.html・kp.css・roadmap.md・how-to-use.md）は、どれも今のファイルと合っていた
- origin/main はこの作業ツリーより 7 commit 進んでいるが、直したファイルと重なるのは how-to-use.md の生成部分・nav.yml・graph.json だけで、文の重なりはない（マージの後に gen_site.py を流せばそろう）

## 直しは要らないが、メインに伝えること

- **gen_site.py を流す（担当の提案 1）は必須**：流さないと study-list が nav になく、CI の `mkdocs build --strict` が止まる
- **interfaces.md**：§6 は実装と合っている（形・古い形・合わせる／置き換えるの決まりを確かめた）。冒頭の版の行と §7 の表は、まだ新しい部品（勉強したいの切り替え・列のチェック欄・色別の表・一覧）を含まない（担当の提案 2）。design.md §9.1 の「（JSON のコピーと貼り付け）」も同じ（提案 3）。README.md の進捗の行（提案 5）
- **ページの追加**（guide/study-list）は design.md §10.5 で「ユーザーに確かめる場面」にあたる（担当の質問 2）。#74 の「やること」4 つ目の決定（質問 1）と合わせて、decisions.md に残す
- **デプロイの直後の一時的な不整合**：GitHub Pages は progress.js を最大 10 分ほどキャッシュさせる（ファイル名に版がない）。その間に新しい HTML と古い progress.js の組で開くと、「勉強したい」を押しても記録されない。古いタブで記録を変えると `wishlist` が消える（担当の「残った点」と同じ）。どちらも一時のことで、直しは求めない
- マウスで押したときにも切り替えの焦点の枠（`:focus-within`）が出るのは好みの範囲なので、指摘にしない

## 使ったもの

- 試験の台本：`<V>/cdp/`（lib.mjs と t1〜t10。t1 切り替え・古い形、t2 一覧、t3 ファイル、t4 ロードマップ、t5 instant navigation、t6 保存できない環境と地図、t8 合わせる決まり、t9 直しが要る点の再現、t10 はみ出し）、`<V>/py/check_rows.py`（列の行と diff の照合）
- 試験のデータ：`<V>/testdata/`（公開中の形の old-export.json・壊れた JSON・形の違うもの・2 MB を超えるもの）、保存されたファイル：`<V>/downloads/`
- 画像：`<V>/shots/`
