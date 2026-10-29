# progress-features の報告（グループ progress、2026-10-29）

担当の Issue：#74（進捗の記録をロードマップの列と問題の difficulty で見る）・#1（勉強したいリスト・お気に入りのボタン）。
作業ツリー：/home/yuuki/projects/kyopro2/kyopro-atlas-wt/progress（feat/progress）。git は読むだけで、commit などはしていない。`tools/gen_site.py` は `--check` だけを流した。
作業用フォルダ：/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/7a638398-7759-4637-95c7-6739e8d52414/scratchpad/fix/progress/progress-features（以下 `<W>`）。

## 直したファイル

| ファイル | 変更 |
| --- | --- |
| `overrides/assets/js/progress.js` | 記録の形に `wishlist`・`exportedAt` を足した。「勉強したい」の切り替えと一覧、ファイルへの保存と読み込み・最後に書き出した日、ロードマップの列の行のチェック欄と「理解した行を隠す」、集計の difficulty の色別の表（1,101 行。+611／−80） |
| `overrides/main.html` | 「勉強したい」の切り替え（`{% set wish %}`、174〜190 行目）をページの上（243 行目）と下（315〜321 行目の `div.kp-links__actions`）に出す。nav から id `study-list` の URL を引く（76・88 行目）。冒頭のコメント（11〜12 行目） |
| `overrides/assets/css/kp.css` | 末尾に追記だけ（640〜831 行目、+193 行）。既存の規則は 1 行も変えていない（`git diff` の削除行 0） |
| `docs/guide/study-list.md` | 新規。勉強したいリストのページ（id `study-list`、guide・chapter「学び方と練習」・order 65、stage `draft`） |
| `docs/guide/roadmap.md` | 手書きの部分だけ：#reading-order の説明と切り替えの置き場所（211〜213 行目）、#progress の説明（760〜774 行目）。生成部分（gen:begin〜gen:end）は触っていない。updated は 2026-10-29 のまま |
| `docs/start/how-to-use.md` | sections に `{title: 勉強したいリスト, anchor: wishlist}`（27 行目）。#by-color（149 行目）・#page-anatomy（192・196 行目）・#progress（284〜292 行目）を直し、#wishlist（298〜305 行目）を足し、#backup（307〜330 行目）を書き直した。updated は 2026-10-29 のまま、stage は変えていない |
| `planning/interfaces.md` | §6 だけ（記録の形・古い形の読み込み・書き出しと読み込みの約束） |

## 記録の形（interfaces.md §6）

キーは今までどおり `kyopro-atlas:v1` の 1 つで、項目を 2 つ足した（読める足し方なので、キーは変えていない）。

```json
{"solved": {"abc340_e": true},
 "understood": {"lazy-segment-tree": {"水": true}},
 "wishlist": {"segment-tree": "2026-10-29T12:00:00+09:00"},
 "updatedAt": "2026-10-29T12:00:00+09:00",
 "exportedAt": "2026-10-29T12:30:00+09:00"}
```

- `wishlist`：ページの id → 入れた時刻（地方時の ISO 8601）。日付だけのものと、入れた日の分からない `true` も読む（手で書いた JSON のため。一覧では入れた日を「—」にする）。
- `exportedAt`：最後に書き出した（ファイルに保存した・コピーした）時刻。書き出しは記録の中身を変えないので `updatedAt` は変えない（`store()` と `save()` を分けた。progress.js 132・147 行目）。
- 古い形（2026-10-21 版。2 つの項目がない）は、localStorage の値も書き出した JSON も、そのまま読める。`normalize()`（73 行目）がない項目を空にし、知らない項目と崩れた値を捨てる。
- 合わせる（`merge()`、226 行目）：解いた・理解した・勉強したいのどれかがあればある。勉強したいの入れた時刻は早い方（`earlier()`）。`exportedAt` は今の記録のもの。増えたものがなければ記録も `updatedAt` も変えない（「書き出した後に変わった」と出さないため）。
- 置き換える：読み込んだ記録の `updatedAt` と `exportedAt` を使う（中身が読み込んだ記録そのものなので、読み込んだ直後に「その後に記録が変わっている」と出さない。`updatedAt` のない記録は読み込んだ時刻）。
- `kp:progress` イベントと `window.KPProgress` は今までどおり。知識マップ（map.js）は `understood` だけを読むので、形を足しても動く（確かめた。下の「確かめたこと」）。`KPProgress` に `normalize`・`isWished`・`setWished` を足した。

## #1 勉強したいリスト — 完了（nav などへの登録は gen_site.py の実行待ち）

- **ボタン**：id を持つ全ページ（勉強したいリストのページ自身を除く 353 ページ）の、上の帯（「理解した」の後）と下の欄（「理解した」と同じ行）に「勉強したい」を出す（main.html 174〜190・243・315〜321 行目）。中はチェック欄（`input[data-kp-wish="<id>"]`、`aria-label`「勉強したいリストに入れる」）で、見た目はしおりの印（Material 同梱の `material/bookmark-outline`・`bookmark` の SVG）。チェック欄は見えなくし、キーボード（Tab・Space）と読み上げには残した。入れると印が塗られ、アクセントの色の塗りになる（kp.css 640〜687 行目）。横に「リストを見る」（nav に `study-list` のページがあるときだけ）。
- **記録**：「解いた」「理解した」と同じ仕組み（同じキー・同じ `change` の受け方・storage イベント・`kp:progress`）。`setWished()`（progress.js 195 行目）が入れた時刻を残す。
- **一覧のページ** `docs/guide/study-list.md`：`<div class="kp-wishlist">` に progress.js が一覧を出す（`mountWishlist()` 1011 行目・`renderWishlist()` 955 行目）。各行に題名（ページへのリンク。title に summary）・レベルの印・分野・入れた日・「外す」。ページのレベルの「理解した」が付いていれば「✓ 理解した」も出す。並べ方は 入れた日の新しい順（既定）・古い順・レベルの順・分野の順。「外す」の直後は「元に戻す」で入れた時刻ごと戻せる（フォーカスも戻す）。graph.json にない id（変わった・消えたページ）は id のまま出し、外せるようにした。graph.json を読めないときも id と外す操作は出す。空のときは案内の 1 文だけ。
- **書き出し・読み込み**：`wishlist` も入る（#74 の欄と同じ）。
- **ページの置き場所**：guide の chapter「学び方と練習」の色別ロードマップ（order 60）の次（order 65）。`gen_site.py --check --diff` で、nav でもロードマップの次に入ることを確かめた。id と URL（`guide/study-list/`）はマージ後は変えない前提で選んだ（質問 2）。
- **説明**：how-to-use に #wishlist の節を足し、#page-anatomy の上の帯・ページの下と #progress から案内した。roadmap の #progress の最後からもリンクした。

## #74 進捗の拡張 — 完了（レベルの付け直しの読み替えは質問 1）

### 色ごとの列の行の印と「まだのものだけ」

- `mountOrder()`（progress.js 851 行目）：生成された表を `h3#reading-order-<basic|cyan|blue|yellow|advanced>` の後の最初の表として見つけ、各行の「#」の欄にチェック欄を付ける（番号もその文字にした）。行のページの id はリンクの URL の最後の部分（`<field>/<id>/`。interfaces.md §1）、色は見出しの id から取り、`data-kp-understood`・`data-kp-level` で各ページの「理解した」と同じ記録に結ぶ。節の行（`ページ › 節（基礎のページの節）`）は、ページの「水の節」のような欄と同じ記録になる。生成部分（gen_site.py の出力）は変えていない。
- 表には class を付けない（Material は `table:not([class])` だけを整え、包む）。印は `data-kp-order`（表）・`data-kp-row`（行）・`kp-is-understood`（理解した行の地の色）で付けた。
- 見出しの下に「理解した行：2 / 82」を出す（`updateOrderCounts()` 902 行目）。
- roadmap.md 213 行目の `<div class="kp-order-tools">` に「理解した行を隠す（まだのものだけを出す）」の切り替えを出す。隠すと各列の見出しの下に「（理解した N 行を隠している）」が付く。切り替えはタブの間だけ覚える（instant navigation でページを行き来しても残る。判断 4）。
- 同じページの同じ帯の節が 2 行以上ある列（例：lis の青の節は 4 行）では、それらの行は 1 つの記録になる（記録がページ×レベルのため）。切り替えの欄にその旨を 1 文出した。
- 390px では「#」の欄の幅を詰めた（kp.css 719 行目。Material の th の `min-width: 5rem` をこの表だけ外した）。

### difficulty の色別の表

- `computeStats()`（progress.js 684 行目）に、graph.json の `problems` の difficulty で数える表を足した（灰〜399・茶・緑・水・青・黄・橙・赤 2800〜、difficulty なし、合計）。行の見出しは本文の問題の行と同じ色の丸（`.kp-diff`）。表は `statTable()`（746 行目）に一般化し、レベル別・分野別も同じ関数で出す。
- いまの graph.json では 1,251 問（difficulty なし 149 問）。集計の注に、レベル別・分野別は載せたページで数えること（レベルや分野の違う 2 つのページに載る問題は両方に入る）、色別は問題の difficulty（載せた時点の値）で数えることを書いた。

### ファイルに保存・ファイルから読み込む・最後に書き出した日

- 書き出し・読み込みの欄（`mountIO()` 453 行目）のボタンを「ファイルに保存」「ファイルから読み込む」「コピー用に表示」「貼り付けて読み込む」にした。
  - ファイルに保存：`kyopro-atlas-progress-<日付>.json` を Blob と `a[download]` で保存させる（`download()` 417 行目）。blob: の URL は sitemap にないので、instant navigation は横取りしない（Material の `handle()` の作りを source map で確かめた）。
  - ファイルから読み込む：`input[type=file]`（.json・.txt、2 MB まで）を FileReader で読み、中身を貼り付けの欄に入れて「今の記録と合わせる」「今の記録を置き換える」を選ばせる（置き換えの 2 回押しの確認は今までどおり）。読めない JSON・記録の形でないファイルは理由を出す。
- 欄の上に「最後に書き出した日：2026-10-21（8 日前）。その後に記録が変わっている。」を出す（`backupText()` 432 行目）。書き出していなければ「まだ書き出していない。…ファイルに保存しておく。」。コピーは「コピーする」の成功と、欄の文字を手でコピーした（`copy` イベント）ときに書き出したことにする。
- 記録の数の行に「勉強したい N ページ」を足した。

## instant navigation

- 取り付けは今までどおり `document$` の購読（`mount()`）で、入れ替わったページごとに行う。`change`・`storage` は document と window で 1 回だけ受ける。隠す切り替えと一覧の並べ方はモジュールの変数に持つので、instant navigation の間は残る。
- Material の `content.tooltips` は `title` を預かって表示の後に元の値へ戻すので、「勉強したい」の `title` は状態で変えない固定の文にした（変えると古い値に戻される）。

## 確かめたこと

| 検査 | 結果 |
| --- | --- |
| `node --check overrides/assets/js/progress.js` | 通る |
| `python3 tools/check_pages.py --page study-list --page how-to-use --page roadmap` | エラー 0・警告 0。全ページ（絞らない）でもエラー 0・警告 0 |
| `npx textlint docs/guide/study-list.md docs/start/how-to-use.md docs/guide/roadmap.md` | エラー 0。警告 5 はすべて前からあるもの（HEAD の同じファイルでも同じ 5 件：how-to-use の助詞「か」2・`[` の対 1・文の長さ 1、roadmap の参考の「！！」1）。新しい文からの警告はない |
| `.venv/bin/mkdocs build --strict`（nav に study-list を足した作業用の設定 `<W>/mkdocs-test.yml`。作業ツリーの mkdocs.yml を INHERIT し、nav だけ差し替え） | exit 0、警告なし |
| 同（作業ツリーの nav.yml のまま、`-q` なし） | exit 1。警告は「guide/study-list.md が nav にない」の 1 件だけ（gen_site.py を流せば消える。提案 1） |
| `python3 tools/gen_site.py --check`（`--diff` も） | 10 ファイルが変わる（nav.yml・docs/guide/index.md・docs/lists/index.md・docs/lists/kind-guide.md・docs/llms.txt・docs/index/start.md・docs/index/guide.md・graph.json・docs/guide/term-index.md・docs/start/how-to-use.md の生成部分の数）。どれも新しいページと #wishlist の節によるもの |
| `node --test "tests/viz/*.test.mjs"` | 216 通る |
| `python3 -m unittest discover -s tests/tools` | 44 通る（2 は skip） |

ヘッドレスの Chrome（chrome-headless-shell 146 を CDP で。`<W>/tools/cdp.mjs`）で、ビルドしたサイトを http の `/kyopro-atlas/` で配り（instant navigation が効くよう port のない名前に向けた）、記録を入れた状態で確かめた。JS の例外・console のエラーは 0（Material が外の api.github.com に 404 を受けるログだけ）。

- 390px（指の端末の扱い）・1280px、ライト・ダークで：ページの上と下のボタン（`page-*`・`guide-*`）、ロードマップの列・隠す切り替え・集計の 3 つの表・書き出しの欄（`roadmap-*`）、一覧（`list-*`、空のとき `list-empty-390`）、一覧のページ全体（`listpage-*`）。画像は `<W>/shots3/`（前の版の画像は `<W>/shots2/`）。ページの横のはみ出しなし（scrollWidth = 幅）。
- 押したときの動き：上のボタンで入れると下のボタンも塗られ、下で外すと上も外れる。Space で切り替わり、フォーカスの枠が見える（`kbd`）。
- 列：基礎 82・水 110・青 128・黄 91・発展 83 行にチェック欄が付き、記録どおりに 2・3・4 行が理解した。隠すと 80・107・124 行だけ見える。
- 一覧：並べ方の切り替え、外す → 「元に戻す」（入れた時刻ごと戻る）、日付の分からない記録（`true`）を外して戻すと `true` のまま。別のタブの変更（storage イベント）で行が増える（`tab-sync`）。
- ファイル：保存したファイルの中身が記録と同じで、`exportedAt` だけが保存の時刻、`updatedAt` は変わらない（`io-file`）。古い形のファイル（`<W>/testdata/old.json`）を合わせる → 増えた分だけ足される。新しい形のファイルで置き換える → 2 回押しの確認の後、`updatedAt`・`exportedAt` もファイルのもの（`io2`）。何も増えない合わせ方では記録を変えない。形の違うファイル・壊れた JSON は理由を出す。
- 古い形の記録を localStorage に入れて開く → そのまま読め、勉強したいを入れると `wishlist` と `exportedAt: null` が足される（`old-format`）。
- localStorage に書けない環境（`setItem` が例外）：ボタンはメモリの記録で動き、注意の文が出て、ファイルの保存もできる（`blocked`）。
- instant navigation：ロードマップで隠す切り替えを入れる → 列のリンクで bit-full-search へ（instant）→ 上の帯で「理解した」と「勉強したい」を押す → 戻る（instant）と、その行が理解した・隠れた状態で、切り替えも入ったまま → 「リストを見る」で一覧へ（instant）→ 一覧の題名からページへ → また一覧へ、で並べ方も残る（`instant`）。
- 知識マップ：足した形の記録で開き、理解した数と次の候補が出て、`setUnderstood` の後に塗りが変わる（`map`）。

## 判断したこと（見てほしい）

1. **勉強したいはページ単位**にした（節単位にはしない）。「理解した」と違い、上の帯の節ごとのボタンは置いていない。
2. **ボタンは上と下の両方**に置いた（「理解した」と同じ）。読み終えてから「あとでもう一度」と入れる使い方のため。下では「理解した」と同じ 1 行（`div.kp-links__actions`）にまとめた。
3. **列のチェック欄は押せる**ようにした（印だけでなく）。Issue の背景の「順に読むためのチェックリストとして使えない」に合わせた。記録はページの欄と同じなので、どちらで付けても同じになる。
4. **隠す切り替えと並べ方はタブの間だけ覚える**。localStorage は 1 キーの約束（interfaces.md §6）なので、表示の好みは記録に混ぜなかった（質問 3）。
5. **「ファイルに保存」を押した時点で書き出したことにする**。ブラウザが保存先を聞く場合に、本当に保存したかは JS から分からない。
6. **一覧は表ではなく行の並び**にした。390px で 5 列の表は題名の欄が狭くなるため。題名・レベル・分野・入れた日・外す、の 5 つはそろえた。

## 残った点

- デプロイの直後に、古い progress.js のまま開いていたタブで記録を変えると、古い `normalize()` が知らない項目を捨てるので、`wishlist` と `exportedAt` が消える（solved・understood は残る）。開いたままのタブがある間だけの一時のこと。
- 新しいページは stage `draft`。別の担当の検証を受けてから reviewed にする（提案 9）。
- 作業用のビルドの中間物（`<W>/site`・`<W>/site-base`・`<W>/shots*`）は作業用フォルダに残してある。

## 提案（メインに頼む共有ファイルの変更）

1. `tools/gen_site.py` を流す（上の 10 ファイル）。流さないと、CI の `mkdocs build --strict` が「guide/study-list.md が nav にない」で止まる。
2. interfaces.md §7 の表と冒頭の版の行：「勉強したい」の切り替え（テンプレートが `span.kp-wish > label.kp-wish__toggle > input[data-kp-wish]` を上の帯と下の `div.kp-links__actions` に出し、progress.js が結ぶ。study-list のページ自身には出さない。nav に `study-list` があれば「リストを見る」）、ロードマップの列のチェック欄（progress.js が `h3#reading-order-<色>` の後の表に付け、`div.kp-order-tools` に隠す切り替え）、集計の difficulty の色別の表、勉強したいリストの一覧（`div.kp-wishlist`）、書き出しの欄のボタンと最後に書き出した日。
3. design.md §9.1 の表に「勉強したいリスト」の行を足し、「書き出し・読み込み（JSON のコピーと貼り付け）」をファイルの保存・読み込みも含む書き方にする。
4. decisions.md：ページの追加（`guide/study-list`。id と URL は変えない）を残す（design.md §10.3 の「ページの追加は decisions.md に残し、ユーザーに知らせる」）。
5. README.md 13 行目の「進捗」：「勉強したい」と、ファイルへの保存を足す。
6. front matter（頼まれていないので変えていない）：how-to-use と roadmap の `related` に `study-list` を、how-to-use の `aliases` に「勉強したいリスト」「お気に入り」を（別名の行も合わせて）足す。
7. brief-fix.md・brief-verify.md の `mkdocs build ... -q`：`-q` を付けるとログの水準が ERROR になり、`--strict` でも警告を数えずに exit 0 になる（このバッチで、study-list が nav にない状態の `--strict -q` が exit 0、`-q` なしが exit 1 だった）。確かめには `-q` を外すか、出力を絞るなら `2>&1 | grep -i warning` などにする。
8. 知識マップに勉強したいのページの印を出す（map.js。`KPProgress.isWished`）。今回は頼まれていないので作っていない。
9. 新しいページ `study-list` の検証（stage が draft のため）。
10. #55（mobile-layout）で表の CSS を変えるときは、kp.css 719 行目の `table[data-kp-order] tr > :first-child`（ロードマップの列の「#」の欄だけ min-width を外す）とぶつからないかを見る。

## 質問（メインに判断してほしい点）

1. **ページのレベルを付け直したときの読み替え（#74 の 4 つ目）**。案：
    - A（勧める）：読み替える。付け直しの表（ページの id・前のレベル・新しいレベル。節のレベルの付け直しも同じ形）を、id の読み替え表（design.md §10.3）と同じ場所（progress.js の小さな表）に持ち、`normalize()` で `understood[id][前]` を `understood[id][新]` に写す。localStorage の記録にも、古いファイルの読み込みにも効く。ページのレベルと上の帯の節の色が重なる付け直しでは 2 つが 1 つにまとまるが、記録はページ×レベルなのでそれでよい。
    - B：読み替えない。古いレベルの記録は消さずに残る（`normalize()` は 5 つのレベルの鍵を全部残す）ので、後から A に変えても戻せる。読者の「理解した」は集計と地図から見えなくなる。
    - C：表を持たず、graph.json を読んだときに、今のページにないレベルの記録をページのレベルへ寄せる。表は要らないが、graph.json を読まないページのチェック欄には効かず、節の付け直しとの区別がつかない。
2. 新しいページの id と置き場所を `guide/study-list`（chapter「学び方と練習」、order 65、ロードマップの次）にしてよいか。マージ後は URL を変えない前提である。
3. 「理解した行を隠す」と一覧の並べ方を、再読み込みの後も覚えておくか。覚えるなら、別のキー（例：`kyopro-atlas:v1:prefs`）か記録の中の項目が要り、interfaces.md §6 の「キーは 1 つ」を改めることになる。今はタブの間だけ覚える。

## 検証の指摘への対応（2026-10-29、fixup-progress-features）

検証の報告：[verify-progress-features.md](verify-progress-features.md)。直しが要る点は 1 件（#1）で、指摘どおりに直した（指摘は正しいと判断した）。
直したのは `overrides/assets/js/progress.js` だけである（+22 行・−6 行で、1,117 行になった）。kp.css・main.html・ページ・interfaces.md は変えていない。git は読むだけで、commit などはしていない。
作業用フォルダ：/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/7a638398-7759-4637-95c7-6739e8d52414/scratchpad/fix/progress/fixup-progress-features（以下 `<X>`）。差分は `<X>/fix.diff`（検証のときにビルドした progress.js との差）。

### 指摘 1：graph.json を読めないとき、一覧の全行に「このページは見つからない」と誤って出る — 直した

- **代わりの graph に印を付けた**：`failedGraph(reason)`（progress.js 922 行目）が `{ pages: [], fields: [], failed: true, reason }` を返す。`mountWishlist()` は読めなかったとき（1076〜1078 行目）にこれを使う。graph.json は読めたがページの一覧（`pages` の配列）がないときも、同じに扱う（1074 行目）。
- **行の注記**：`renderWishlist()` は `g.failed` のとき「このページは見つからない（id が変わったか、なくなった）」を出さず、行を id と「入れた日 …」だけにする（1010 行目）。graph.json を読めて、その中にない id（変わった・消えたページ）には、前どおり出す。
- **説明が消えないようにした**：読めなかった旨を、外す・元に戻すの知らせ（`p.kp-wishlist__status`）から、別の段落 `p.kp-wishlist__note` に移した（並べ方の帯の下・知らせの上。1037 行目）。`renderWishlist()` が描くたびに出し直す（975〜983 行目）ので、外した・戻した・別のタブで変わった後も残る。文は「ページの一覧を読み込めなかった（<理由>）。題名・レベル・分野の代わりに id を出す。ページを読み込み直すと出ることがある。」で、リストが空のときは出さない（題名が要らないため）。色は書き出しの欄の注意と同じ class `kp-io__warn`（エラーの色）を使い、kp.css は変えていない。
- 読めなかった後に instant navigation でほかのページへ行って戻ると、`loadGraph()` が読み直し（失敗した Promise は前から捨てている）、題名が出て注記が消える。

### 判断したこと（見てほしい）

1. 注記は、外す・元に戻すの知らせとは別の段落にした。知らせは最後の操作のことなので次の操作で上書きされるが、読めなかった旨は一覧の全体に掛かるため。
2. 注記は live region（role=status）にしていない。開いた直後、一覧を出すときに決まることで、読み上げでは一覧の行より先に読まれるため。前の版は知らせの欄（role=status）に出していたので、読めなかった時点で読み上げられていた。
3. 読めなかったときの並べ方は変えていない。レベルの順・分野の順は id の順になる（どの行もページが分からないため）。選択肢は残した。

### 確かめたこと

| 検査 | 結果 |
| --- | --- |
| `node --check overrides/assets/js/progress.js` | 通る |
| `python3 tools/check_pages.py --page study-list --page how-to-use --page roadmap` | エラー 0・警告 0。全ページ（354）でもエラー 0・警告 0 |
| `npx textlint docs/guide/study-list.md docs/start/how-to-use.md docs/guide/roadmap.md` | エラー 0。警告 5 は前からのもの（how-to-use 140・193・227・405 行目、roadmap 791 行目。md は今回変えていない） |
| `node --test "tests/viz/*.test.mjs"` | 216 通る |
| `python3 -m unittest discover -s tests/tools` | 44 通る（2 は skip） |
| `python3 tools/gen_site.py --check` | 10 ファイルが変わる（前と同じ。提案 1 の gen_site.py の実行待ち） |
| `.venv/bin/mkdocs build --strict -q -d <X>/site` | exit 0 |
| `.venv/bin/mkdocs build --strict -f <X>/mkdocs-fixup.yml -d <X>/www/kyopro-atlas`（作業ツリーの mkdocs.yml を INHERIT し、nav に study-list を足しただけ。`-q` なし） | exit 0、警告なし。ビルドの前後で作業ツリーの git status は同じ |

ヘッドレスの Chrome（chrome-headless-shell 146 を CDP で）で、上の 2 つ目のビルドを http の `http://kyopro.test/kyopro-atlas/` で配り（port のない名前に向け、instant navigation が効くようにした）、graph.json の取得を CDP の Fetch で失敗させて確かめた。台本は `<X>/cdp/t-graphfail.mjs` で、28 項目すべて通る。サーバは使い終えて止めた。

- **読めないとき（390px・ライト）**：注記が帯の下に出て、3 行（binary-trie・lis・日付のない segment-tree）はどれも「入れた日 …」だけで、「見つからない」が付かない。知らせの欄は空。1 件外す → 知らせは「「binary-trie」を外した。元に戻す」、注記は同じ文のまま残る（検証の画像 t9-graphfail-after-remove-390 と同じ場面：`<X>/shots/A-fail-after-remove-390-light.png`）。元に戻す → 入れた時刻ごと戻り、注記も残る。全部外す → 空の案内だけになり、注記は消える。もう一度戻す → 注記がまた出る。別のタブで入れた（storage イベント）行にも「見つからない」が付かない
- **ダーク・1280px**：390px ダーク、1280px ライト・ダークで、注記が出て、「見つからない」がなく、横のはみ出しがない（scrollWidth = 幅）。注記の色はライト #c62828、ダーク #ff8a80（`--kp-error-color`）
- **理由の文**：HTTP 404 では「（graph.json を読めない（404））」、ページの一覧のない graph.json（`{}`）では「（graph.json にページの一覧がない）」と出て、どちらも「見つからない」が付かない
- **読めるとき（前と同じ動き）**：注記は出ない。実在するページは題名のリンク・レベル・分野・入れた日（理解した印も）で出て、graph.json にない id（`no-such-page`）だけに「このページは見つからない（id が変わったか、なくなった）」が付く。390px ライト・ダーク、1280px で確かめた
- **instant navigation**：読めない状態で一覧を開き、取得を通すようにしてから、本文のリンクでロードマップへ（instant）→ 戻る（instant）。再読み込みなしで graph.json を読み直し、題名が出て注記が消える。一覧の箱と注記は 1 つずつ
- **例外**：JS の例外 0。console のエラーは、わざと失敗させた graph.json の取得と api.github.com のものだけ
- **検証の台本も流し直した**（`<X>/cdp/v-*.mjs`。検証の台本の写しを今のビルドに向けた）：t5-instant は 19 項目すべて通る。t2-list は 22 項目中 21 が通る。通らない 1 つ「graph.json failure: status message + id row」は、読めなかった旨を知らせの欄（`.kp-wishlist__status`）で探す項目で、今回その文を `.kp-wishlist__note` に移したためである。そちらを見るように変えると通る（行は「lis・入れた日 2026-10-20・外す」で「見つからない」がない。`v-t2-list-note.mjs`）。t6-blocked は 10 項目中 9 が通る。通らない「no exceptions (access throws)」は、localStorage の参照が例外になる環境での SecurityError 4 件で、出どころは Material の bundle とインラインのスクリプトだけ、progress.js からは 0 件だった（`t-access-throws-origin.mjs`。検証の報告の「前からある」と同じ）
- 画像：`<X>/shots/`（A-fail-390-light・A-fail-after-remove-390-light・B-fail-after-remove-390-dark・B-fail-after-remove-1280-light・B-fail-after-remove-1280-dark・D-ok-390-light・D-ok-390-dark・D-ok-1280-light）

### 上の報告の行番号

progress.js の 918 行目より後は、上の報告の行番号から 4〜16 行ずれた。`renderWishlist()` は 959 行目（上では 955）、`mountWishlist()` は 1025 行目（上では 1011）。それより前の行番号（`normalize()` 73・`mountIO()` 453・`computeStats()` 684・`mountOrder()` 851 など）は変わらない。

### 残った点

- 上の「提案」「質問」はそのまま残る（特に提案 1 の gen_site.py の実行は必須。流さないと CI の `mkdocs build --strict` が止まる）。
- 再検証で検証の台本 t2-list を使うなら、上の 1 項目は注記を `.kp-wishlist__note` で探すように直す。
