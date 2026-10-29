# problem-followup の報告（工程11 グループ problem-display・Issue #5・#76 の続き）

作業ツリー：`kyopro-atlas-wt/problem-display`（ブランチ fix/problem-display）。前の担当（[problem-lines.md](problem-lines.md)）の提案 1〜4 を直した。commit はしていない。gen_site は流していない。日付：2026-10-29。

## まとめ

| Issue | 状態 | 一言 |
| --- | --- | --- |
| #5 | 完了 | progress.js が「（diff なし）」を difficulty の書き方として読み、色を付けずにその行を終える。kp.css の注記・atcoder-system・用語集の「diff —」を「diff なし」に直した（atcoder-system には「表の diff の列では「—」」も添えた） |
| #76 | 完了 | progress.js が「（diff 1856・参考値）」の「diff 1856」に色の丸を付け、title を「difficulty 1856・参考値（青）」にする。atcoder-system の推定の約束に参考値の項目を足し（3 つ → 4 つ）、用語集に参考値の書き方を足した |

これで、前の担当が作り直した参考値の 44 行にも色の丸が付く（Chrome で全 1586 行を確かめた。下の「確かめたこと」）。

## 直したファイル

| ファイル | 行 | 直した内容 |
| --- | --- | --- |
| `overrides/assets/js/progress.js` | 181〜187・194・204 | difficulty を読む正規表現を 3 つの形に合わせ、「diff なし」で走査を終える行を足し、title に「・参考値」を添えた。注記を直した |
| `overrides/assets/css/kp.css` | 225〜226 | 注記だけ（規則は変えていない） |
| `docs/start/atcoder-system.md` | 28・107・110・111・242 | updated、「3 つ」→「4 つ」、diff なしの書き方、参考値の項目（新しい箇条）、参考の function.py の行に参考にした点を足した |
| `docs/guide/glossary.md` | 27・135 | updated、difficulty の項目に「diff なし」と「diff 1856・参考値」の説明 |

front matter は `updated` だけを 2026-10-22 から 2026-10-29 にした（stage は reviewed のまま）。

## progress.js

前：

```js
var DIFF_TEXT = /（(diff (\d+))）/;
（略）
span.title = "difficulty " + d + "（" + DIFF_BANDS[k][2] + "）";
```

後：

```js
// 問題の行の difficulty の 3 つの形（tools/check_pages.py の PROBLEM_LINE_RE。#5・#76）：
// 「（diff 1354）」・台帳で参考値のもの「（diff 1856・参考値）」・値のないもの「（diff なし）」
var DIFF_TEXT = /（(diff (\d+))(・参考値)?）|（diff なし）/;
（略）
if (!m[1]) return; // 「diff なし」。行の difficulty はこれで終わり（後ろの要約は見ない）
（略）
span.title = "difficulty " + d + (m[3] || "") + "（" + DIFF_BANDS[k][2] + "）"; // 参考値は「difficulty 1856・参考値（青）」
```

- 3 つの形を check_pages.py の `PROBLEM_LINE_RE`（`（diff (?P<diff>\d+(?:・参考値)?|なし)）`）と同じに読む。m[1] は span で包む「diff 1856」、m[2] は値、m[3] は「・参考値」
- 「（diff なし）」に当たったら、色を付けずにその行の走査を終える。前は「—」に当たらないまま行の終わりまで文字の節を見ていた（結果は同じく色なし。要約の中の文字に誤って当たる余地をなくした）
- span で包むのは「diff 1856」だけで、「・参考値」は span の外の地の文（太字・色なし）のまま。丸の色と塗りは、ふつうの値と同じ計算（前の担当の提案 1 のとおり）
- 前の形「（diff —）」や「（diff 1856（参考値））」「（diff なし・参考値）」はどちらの選択肢にも当たらず色なし（どれも check_pages がエラーにする形）
- 注記（185〜187 行目）：「（diff NNNN）」「（diff NNNN・参考値）」の「diff NNNN」を包むこと、「・参考値」は span の外に残して title に添えること、「diff なし」は色を付けないことを書いた

## kp.css の注記（225〜226 行目）

- 前：「文字は背景に対して読める濃さに直した色（--kp-diff-text）。「diff —」には付けない */」
- 後：「文字は背景に対して読める濃さに直した色（--kp-diff-text）。「diff なし」には付けない。参考値の「diff 1856・参考値」では「diff 1856」の部分だけに付ける */」

## atcoder-system.md（#difficulty の推定の約束）

- 107 行目：「知っておくと読み違えないものが 3 つある」→「4 つある」
- 110 行目の末尾：「この教材では「diff —」と書く。」→「この教材の問題の行では「diff なし」と書く（表の diff の列では「—」）。」
- 111 行目（新しい箇条）：「**古いコンテストの値は参考値**：Rated のコンテストが始まる前（2016 年 7 月の abc041・arc057 まで）の ABC・ARC などには、Rated でなくても値が付く。当時の参加者にはレートがないので、AtCoder Problems はそれまでの順位から再現したレートで推定し、試験的な値（experimental）として出している。この教材の問題の行では「diff 1856・参考値」と書く。」
- 242 行目（参考の kenkoooo「AtCoderProblems / time-estimator/function.py」）の参考にした点の末尾に「、Rated が始まる前の ABC・ARC などでは順位から再現したレートを使い、値を experimental とすること」を足した

110 行目の箇条（「Rated のコンテストとして開かれていない問題集…には値が付かない」）だけでは、古い Rated でない ABC に値があることと食い違って読めるので、新しい箇条を「Rated でなくても値が付く」で始めた。

### 確かめた事実

1. **AtCoder Problems の推定のソースコード**（GitHub の kenkoooo/AtCoderProblems、`lambda-functions/time-estimator/function.py`・`rating.py`、`atcoder-problems-frontend/src/components/ProblemLink.tsx`。`gh api` で読んだ。function.py の最後の commit は e87addd・2025-04-05。github.com は手引きの付録 B で確かめ済み。kenkoooo.com・atcoder.jp は開いていない）
   - `infer_contest_type`：rate_change が「-」のコンテストのうち、ID が abc・arc で始まるもの（`OLD_UNRATED_ABC`・`OLD_UNRATED_ARC`）と、`old_sponsored_contests` の 40 件（code-festival-2014・2015、tenka1-2012〜2015、donuts-2015、dwango2015・2016、mujin-pc-2016、discovery2016 など）を、公式のレートより前のコンテスト（`is_rated` が False）とする。ほかの Rated でないコンテストは `UNRATED` として推定から外す（典型90・EDPC に値がないのはこのため）
   - `run`：公式のレートより前のコンテストの問題は、rating.py の `RatingSystem` がそれまでの古いコンテストの順位から再現したレートを参加者のレートに使い（コメント「contests before official rating system. using the emulated rating」）、その問題の `is_experimental` を true にする
   - ProblemLink.tsx：experimental の値の横に試験管の絵文字と「This estimate is experimental.」の注を出す（本文には書いていない。how-to-use の「参考として出している値」の言い方とも合う）
2. **公開データ**（`.cache/atcoder-problems/`。2026-10-24 取得の tools/ap.py のキャッシュ。作業用フォルダの `check_experimental.py` で数えた）
   - `is_experimental` が true で difficulty のある問題は 514 問（true は全部で 565 問）。初出のコンテストはどれも rate_change が「-」で、いちばん新しいものは arc057（2016-07-09）
   - rate_change が「-」でない最初のコンテストは agc001（2016-07-16。問題に difficulty はない）。experimental でない値の初出はいちばん早いもので abc042・arc058（2016-07-23）。experimental でない値で、初出が Rated でないコンテストのものは 0 問
   - abc001〜041（2013-10-12〜2016-07-02）と arc001〜057（2012-04-14〜2016-07-09）は、すべて rate_change が「-」。2016-07-30 の tenka1-2016-quala も Rated でないが、`old_sponsored_contests` にないので値がない（「Rated でない古いコンテストの問題には必ず値がある」とは書いていない）
   - 例の 1856 は abc014_4（tree/lca の例題。`python3 tools/ap.py show abc014_4` で diff=1856（参考値））。Issue #76 の例と同じ
3. 境を「2016 年 7 月の abc041・arc057 まで」と書いたのは、同じ 7 月の 23 日の abc042・arc058 がふつうの値なので、「2016 年 7 月まで」だけでは境があいまいになるため。同じページの ABC の形式の表（abc001〜041 は Rated なし、abc042 から 〜1199）とも合う

## glossary.md（#difficulty、135 行目）

- 前：「本教材の問題の行の「diff」はこの値で、値のない問題（典型90 など）は「diff —」と書く。推定の式は[difficulty の定義](../start/atcoder-system.md#difficulty)で扱う。」
- 後：「本教材の問題の行の「diff」はこの値で、値のない問題（典型90 など）は「diff なし」と書く。[Rated](#rated) のコンテストが始まる前（2016 年 7 月まで）の古いコンテストの値は、AtCoder Problems が試験的に出す参考値なので「diff 1856・参考値」と書く。推定の式と参考値になる理由は[difficulty の定義](../start/atcoder-system.md#difficulty)で扱う。」
- `[Rated](#rated)` は用語集の中の項目へのリンク（色の項目の `[difficulty](#difficulty)` と同じ書き方）
- 「（2016 年 7 月まで）」は how-to-use の「2016 年 7 月までの Rated でなかったコンテスト」と同じ月の粒度にした。境は「Rated のコンテストが始まる前」が決める（questions 1）

## 確かめたこと

| 検査 | 結果 |
| --- | --- |
| `node --check overrides/assets/js/progress.js` | 構文の誤りなし |
| 正規表現の端（node で 8 通り） | 「（diff 1856・参考値）」→ m[1]「diff 1856」・m[3]「・参考値」。「（diff 1157）」→ m[3] なし。「（diff 3500）」→ m[1]「diff 3500」。「（diff なし）」→ m[1] なし（色なしで終える）。「（diff —）」「（diff 1856（参考値））」「（diff なし・参考値）」「（★4）」は当たらない |
| ビルド `.venv/bin/mkdocs build -q -d <作業用フォルダ>/site` | 成功（15 秒）。作業ツリーの git status は変わらない。ビルドの progress.js・kp.css は作業ツリーのものと同じ（cmp） |
| Chrome（chrome-headless-shell 146。python の http.server で配ったビルドを、DevTools Protocol で開く。作業用フォルダの `cdp_check.mjs`） | 問題の一覧のある 304 ページの全 1586 行を行ごとに確かめた：ふつう 1374 行・参考値 44 行（40 ページ）・なし 168 行（126 ページ）。ふつうと参考値の行は、span.kp-diff がちょうど 1 つで、文字が「diff N」、class が帯のとおり、title が「difficulty N（色）」か「difficulty N・参考値（色）」、`--kp-diff-fill` が帯の中の位置、直前の文字が「（」、直後の文字が「）」か「・参考値）」、`::before` の丸が linear-gradient で塗られている。なしの行は span がない。食い違い 0・コンソールのエラー 0。行数は check_pages の 1586 行・前の担当の数（参考値 44・なし 168）と同じ |
| 前の progress.js との比べ | 同じビルドの 3 ページ（graph/bfs・basics/binary-search-answer・tree/lca）を前の progress.js で開くと、参考値の 3 行（abc007_3・abc026_d・abc014_4）は span が 0（色の丸なし）。今の progress.js では 1 つ |
| 見た目（PNG。作業用フォルダの fontconfig で日本語のフォントを足した Chrome。`shots_jp/`） | 参考値の行「ABC007 C. 幅優先探索（◒diff 1024・参考値）」は緑の丸が 56% 塗られ、「diff 1024」だけが太字の緑で、「・参考値」は地の文。ふつうの行（ABC383 C、茶 88%）、なしの行（典型90 001、丸なし）、ダークモード（ABC014 D、青 64%）、スマホの幅 390px（ABC007 C・典型90 001）も確かめた |
| `python3 tools/check_pages.py --page atcoder-system`・`--page glossary` | どちらもエラー 0・警告 0 |
| `python3 tools/check_pages.py`（全体） | エラー 0・警告 0（353 ページ、本文の問題 1586 行） |
| `python3 tools/fix_problems.py --check` | 直すべき行 0・直せない行 0・台帳にあって本文にない（警告）0（見たページ 354） |
| `python3 -m unittest discover -s tests/tools` | 58 件 OK（skipped 2） |
| `npx textlint docs/start/atcoder-system.md docs/guide/glossary.md` | エラー 0。警告は直す前と同じ 17 件（atcoder-system 3・glossary 14。直す前の版を作業用フォルダに置き、同じ設定で数えた）。中身が変わったのは atcoder-system 242 行目（参考の function.py の行）の sentence-length が 140 字 → 202 字になった 1 件だけで、もとから警告だった。足した本文の文には警告がない |
| `python3 tools/gen_site.py --check --diff`（書かない） | 古いのは 3 ファイル（`docs/llms.txt`・`overrides/assets/data/graph.json`・how-to-use の版の目印）で、中身は版のハッシュだけ（9d105969f6d0 → 9ed22a379f83）。2 ページの updated を変えたため。updated の最大は 2026-10-29 のまま。実行はメインに任せる |

検査のために立てた http.server と Chrome は止めた。

## 提案（メインに頼む変更）

1. `docs/start/how-to-use.md` 230 行目の参考値の文の末尾に、理由の説明へのリンクを足す（例：「…ふつうの値より確かさが低い（[difficulty の定義](atcoder-system.md#difficulty)）。」）。参考値になる理由（当時のレートを順位から再現した推定）は atcoder-system に書いた。how-to-use は担当外なので変えていない
2. スマホの幅では「（diff」と「なし）」、「diff 1024・」と「参考値）」が行をまたぐことがある（`shots_jp/none-typical90_a-mobile.png`・`exp-abc007_3-mobile.png`）。読めるので直していない。まとめたいなら、kp.css に `white-space: nowrap` の規則（例：`.md-typeset .kp-diff-note { white-space: nowrap; }`）を足し、progress.js で「diff なし」と「・参考値」もその class の span で包む（kp.css の規則の変更は担当外）
3. 前の担当の提案 5〜7（手引き §10・interfaces.md §3・design.md §6.6）はメインが直す予定のまま、この担当では触っていない。作業ツリーで古い「`diff —`」の説明が残るのは手引き §10（275 行目）だけになった（tools と試験の「（diff —）」は前の形を読むためのもので、残してよい）

## メインに判断してほしい点

1. 用語集の参考値の境を「（2016 年 7 月まで）」（how-to-use と同じ月の粒度）にした。atcoder-system は「2016 年 7 月の abc041・arc057 まで」と細かく書いた。用語集もそこまで細かくするか
2. 「diff なし」の行に title（例：「AtCoder Problems に difficulty がない」）を付けるか。今は何も付けない（Issue #5 の条件は文字で満たし、ツールチップはスマホで読めないため）
3. atcoder-system には「この教材の問題の行では「diff 1856・参考値」と書く」と書き、表（問題集の表の DONUTS-2015 C の 1661 など）には触れていない。表に参考値の印を出さない今の決定（前の担当の questions 3）と合う。出すことにしたら、この文と、110 行目の「（表の diff の列では「—」）」の周りも合わせて直す
