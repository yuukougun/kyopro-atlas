# problem-lines の報告（工程11 グループ problem-display・Issue #5・#76）

作業ツリー：`kyopro-atlas-wt/problem-display`（ブランチ fix/problem-display。HEAD d112089 から。commit はしていない）。日付：2026-10-29。

## まとめ

| Issue | 状態 | 一言 |
| --- | --- | --- |
| #5 | 完了 | difficulty のない問題の行を「（diff —）」から「（diff なし）」にした（126 ページ 168 行）。道具・試験・how-to-use の説明も合わせた。表の「—」はそのまま |
| #76 | 完了 | 台帳で参考値（`experimental: true`）の問題の行を「（diff 1856・参考値）」の形にした（40 ページ 44 行・40 問）。how-to-use に参考値の意味を 1 文で書いた。ただし色の丸は progress.js を直すまで付かない（提案 1） |

行を作り直したページは合わせて 148（重なり 18）。要約・label・URL は 1 文字も変わっていない（下の「確かめたこと」）。

## 直したファイル

| ファイル | 直したところ |
| --- | --- |
| `tools/check_pages.py` | 冒頭の説明（25〜27 行目。問題の一覧の書式に difficulty の 3 つの形）。定数 `DIFF_NONE`・`DIFF_EXPERIMENTAL`・`OLD_DIFF_NONE` と `PROBLEM_LINE_RE`（114〜123 行目）。`diff_text`（255〜260 行目）。`ProblemRef.diff` の注記（327 行目）。書式の指摘の文（435〜443 行目。前の形の「（diff —）」には今の形と fix_problems.py を案内し、ほかの崩れには 3 つの形を示す）。台帳との違いの文（727 行目「diff（台帳から作ると diff 1856・参考値）」） |
| `tools/fix_problems.py` | 冒頭の説明（読める行の形と difficulty の書き方）。`DIFF_PAREN`（37 行目。「（diff …）」をどの書き方でも読み、中の 1 段のかっこ「（diff 1856（参考値））」も読む）と、それを使う `LINK_TAIL_RE`・`BARE_RE`（38〜39 行目） |
| `tests/tools/test_problem_lines.py`（新規） | 14 件：`diff_text` の 3 つの形と端（値がないのに experimental が true・true の difficulty・項目なし）、`problem_line` の形と `PROBLEM_LINE_RE` の読み取り、前の形やかっこの参考値を書式の違いにすること、check_pages の指摘（書式・台帳との違い 4 通り）、fix_problems の作り直し 7 通り・字下げ・2 回目に変わらないこと・フェンスの中、`--root`・`--ledger` の一時の木での `--check` の終了コードと書き換え |
| `tools/README.md` | 一覧の fix_problems.py の行に difficulty の 3 つの形。工程8b の「台帳の difficulty を更新したら」に `experimental` も |
| `docs/start/how-to-use.md` | #problems の diff の項目（230 行目）。front matter の updated はもとから 2026-10-29 |
| 本文の問題の行（148 ページ） | `python3 tools/fix_problems.py`（--check なし）で作り直した 212 行。手では直していない。うち 118 ページは front matter の `updated` を 2026-10-22 などから 2026-10-29 にした（残りの 30 ページはもとから 2026-10-29） |

`docs/guide/problem-sets.md` は変えていない。「—」の説明（228 行目「問題集の difficulty は付かないので、diff の列はほとんど「—」になる」）は問題集の表の diff の列のことで、表は「—」のままなので、今のままで正しい。

## #5 difficulty のない問題の「diff —」

### 決めた形と道具

- 行の形：`- [典型90 001. Yokan Party（★4）](https://atcoder.jp/contests/typical90/tasks/typical90_a)（diff なし）：要約`（メインの決定）
- `PROBLEM_LINE_RE` の diff の部分は `（diff (?P<diff>\d+(?:・参考値)?|なし)）`（定数から作る）。「（diff —）」は書式の違いになる。check_pages はその行に「difficulty のない問題は（diff —）ではなく（diff なし）と書く。tools/fix_problems.py で直せる」と出す。ほかの作業ツリーで前の手引きどおり「—」で書いた行がマージで入っても、何を直すかが分かる
- `diff_text` は、difficulty が整数でなければ（None・true・false・項目なし）「なし」を返す
- `ProblemRef.diff` は「（diff …）」の中身（1354、1856・参考値、なし）のまま。gen_site.py の `_used_problems` は台帳にない問題のときだけ `q.diff.isdigit()` で値を読む。「なし」は前の「—」と同じく None になる。参考値の行は台帳にない問題なら値を落とすが、台帳にない問題は check_pages のエラーなので公開には出ない（gen_site.py は担当外なので変えていない）
- fix_problems.py は前の形（「（diff —）」・「（diff 1856）」・「（diff 1856（参考値））」・diff なし・問題 ID だけ）のどれも読み、台帳から行を作り直す

### 作り直した行

- 168 行（126 ページ）。コンテスト別：典型90 77・EDPC 31・TDPC 14・ACL Practice（practice2）12・鉄則本 11・アルゴ数学 5・CODE THANKS FESTIVAL 2017 3・chokudai_S001 2・dwacon2018_prelims 2・yahoo_procon2018_final 2、ほか 1 行ずつ 9（nyc2015・agc001・abc298・icpc2013summer_day4・bitflyer2018_final・practice・joi2020_yo2・ddcc_2016_qual・nikkei2019_final）。Issue の数（126 ページ 168 行）と合う
- 分野別のページ数（#5・#76 の合計 148）：basics 20・comb 20・dp 29・ds 18・geometry 4・graph 21・math 16・misc 3・patterns 1・string 5・thinking 2・tree 9

### how-to-use の #problems（230 行目）

前：「difficulty の付かない問題（典型90 など）は「diff —」と書く。」

後：「difficulty の付かない問題（典型90 など）は「diff なし」と書く。典型90 は題名の★が難しさの目安になる（[典型90問の★とレベル](../guide/problem-sets.md#typical90-stars)）。」に続けて #76 の 1 文（下）。

- ★の 1 文は、Issue #5 の案の 3 つ目（典型90 は★の読み替えへ案内する）を説明の側に置いたもの。メインの指示にはないので、要らなければ消してよい（questions 2）

## #76 参考値の difficulty

### 決めた形

- 行の形：`- [ABC014 D. 閉路](https://atcoder.jp/contests/abc014/tasks/abc014_4)（diff 1856・参考値）：要約`（メインの決定）。参考値にするのは台帳の `experimental` が `true` のときだけ（false・null はふつうの値）
- 作り直した 44 行（40 問。abc011_4・abc040_d・arc033_3 などは 2〜3 ページにある）：abc006_4（lis）・abc007_3（bfs）・abc008_3（probability-basics）・abc009_3（lexicographic-greedy）・abc009_4（matrix-power）・abc010_4（min-cut）・abc011_4（lattice-paths・probability-dp）・abc013_4（doubling）・abc014_4（lca）・abc016_4（geometry-vectors）・abc019_4（tree-diameter）・abc020_d（mobius-function）・abc021_d（stars-and-bars）・abc025_c（minimax）・abc026_d（binary-search-answer）・abc028_d（probability-basics）・abc032_c（two-pointers）・abc032_d（knapsack-01）・abc034_d（fractional-binary-search）・abc035_d（dijkstra）・abc036_c（coordinate-compression）・abc040_d（offline-queries・union-find-connectivity）・arc005_3（zero-one-bfs）・arc008_4（segment-tree-monoids）・arc013_3（nim）・arc022_2（two-pointers）・arc025_2（prefix-sum-2d）・arc026_3（dp-segment-tree）・arc026_4（fractional-binary-search）・arc033_3（balanced-bst・binary-trie・kth-element）・arc037_c（kth-value）・arc038_d（game-retrograde-analysis）・arc039_d（lowlink）・arc042_d（multiplicative-order）・arc044_b（graph-construction）・arc045_c（tree-distance）・arc046_b（nim）・arc054_b（ternary-search）・arc055_c（z-algorithm）・donuts_2015_3（monotonic-stack）
- 行の並び（易しい順）は変えていない。参考値の問題も値の順の位置のまま

### how-to-use の参考値の 1 文

「「diff 1024・参考値」のように「参考値」を添えた値は、2016 年 7 月までの [Rated](../guide/glossary.md#rated) でなかったコンテストの問題に AtCoder Problems が参考として出している値で、ふつうの値より確かさが低い。」

- 「参考として出す値で、確かさが低い」はメインの決定の言い方
- 「2016 年 7 月までの Rated でなかったコンテスト」は、AtCoder Problems の公開データ（`.cache/atcoder-problems/` の problem-models.json・contests.json・contest-problem.json。tools/ap.py のキャッシュ）で確かめた：`is_experimental` が true の 514 問は、どれも初出のコンテストの `rate_change` が「-」（Rated でない）で、開始が 2016-07-09（arc057）以前。逆に、2016-07-23 より前に初出の問題で difficulty があるものはすべて `is_experimental` が true（開始時刻が 0 の再掲の問題を除く）。「2016 年 7 月より前」とは書けない（abc041 は 2016-07-02・arc057 は 2016-07-09）。atcoder-system の ABC の形式の表（abc001〜041 は 2013-10〜2016-07 で Rated なし）とも合う
- AtCoder Problems の画面の文言（experimental の説明）は開いて確かめていない。サイトの UI ではなく公開データの事実だけを足した
- 例の 1024 は abc007_3（bfs の例題。`ap.py show abc007_3` で diff=1024（参考値））
- Rated は how-to-use で初めて出る語なので、用語集へリンクした（手引きの決まり）

### 表示の色（progress.js）

progress.js の `DIFF_TEXT = /（(diff (\d+))）/` は「（diff 1856・参考値）」に当たらないので、**今のままでは参考値の 44 行に difficulty の色の丸が付かない**（node で確かめた。「（diff なし）」は前の「—」と同じく色なし）。progress.js は担当外なので提案 1 にした。同じ pull request で直すのがよい。

## 確かめたこと

| 検査 | 結果 |
| --- | --- |
| `python3 tools/fix_problems.py --check`（作り直しの前） | 直すべき行 212（148 ファイル）・直せない行 0。前の形の行がすべて読めることを確かめてから書いた |
| `python3 tools/fix_problems.py`（--check なし。この担当に限り許された実行） | 直した行 212（148 ファイル）・直せない行 0 |
| 作り直しの照合（作業用フォルダの `verify_lines.py`。HEAD と作業ツリーの docs/ を行ごとに比べる） | 変わった行は 3 種類だけ：「— → なし」168 行（台帳の difficulty が null のものだけ）、「N → N・参考値」44 行（台帳の experimental が true で N が台帳の値のものだけ）、front matter の updated 118 行。label・URL・要約（「：」の後ろ）はすべて同じ。行数も同じ |
| `python3 tools/fix_problems.py --check`（作り直しの後） | 直すべき行 0・直せない行 0・台帳にあって本文にない（警告）0（見たページ 354） |
| `python3 tools/check_pages.py` | エラー 0・警告 0（353 ページ、本文の問題 1586 行。作り直しの前と同じ行数） |
| `python3 tools/check_pages.py --page how-to-use` | エラー 0・警告 0（足したリンク problem-sets#typical90-stars・glossary#rated も確かめた） |
| `python3 -m unittest discover -s tests/tools` | 58 件 OK（新しい 14 件を含む。skipped 2 は前からの Python-Markdown がないときの試験） |
| 新しい試験を HEAD の道具に当てる（作業用フォルダに HEAD の check_pages.py・fix_problems.py を置いて流す） | 14 件中 22 の失敗（subTest を含む）。試験が今回の変更を見ていることを確かめた |
| `npx textlint`（変えた docs の 149 ファイル）と、同じファイルの HEAD の版 | エラー 0。警告は HEAD 2217 → 今 2218。増えたのは 1 件だけ：`docs/math/linear-recurrence-fast.md` 179 行目（TDPC T の行）の sentence-length 121 字（上限 120）。「—」が「なし」になって 1 字増えたため。要約は変えられないので残した（questions 4）。how-to-use の新しい文には警告がない |
| `python3 tools/gen_site.py --check --diff`（書かない） | 生成物が古いのは 3 ファイル：`docs/llms.txt`・`overrides/assets/data/graph.json`・`docs/start/how-to-use.md`（version の目印の中）。中身はどれも版のハッシュ（9d105969f6d0 → afd74e3a2ff3）だけで、updated の最大は 2026-10-29 のまま。版が変わるのは front matter の updated を変えたため（問題の行の文字は版の入力でない）。gen_site.py の実行はメインに任せる |

## 提案（メインに頼む共有ファイルの変更）

1. **`overrides/assets/js/progress.js`**（必ず同じ pull request で）：参考値の行にも色の丸を付ける。181 行目を `var DIFF_TEXT = /（(diff (\d+))(・参考値)?）/;` にし、200 行目を `span.title = "difficulty " + d + (m[3] ? "・参考値" : "") + "（" + DIFF_BANDS[k][2] + "）";` にする（丸と色は「diff 1856」の部分だけに付き、「・参考値」は地の文のまま）。183〜184 行目の注記の「（diff NNNN）」に「（diff NNNN・参考値）」を足し、「「diff —」（difficulty なし）は色を付けない」を「「diff なし」は色を付けない」にする
2. `overrides/assets/css/kp.css` 225 行目の注記：「「diff —」には付けない」→「「diff なし」には付けない」
3. `docs/start/atcoder-system.md` 110 行目（#difficulty の推定の約束）：「この教材では「diff —」と書く。」→「この教材の問題の行では「diff なし」と書く（表の diff の列では「—」）。」。参考値も説明するなら、同じ箇条書きに「**古いコンテストの値は参考値**：2016 年 7 月までの Rated でなかったコンテストの問題の difficulty は、AtCoder Problems が参考値として出す（確かさが低い）。この教材では「diff 1856・参考値」と書く。」を足し、前の文の「3 つ」を「4 つ」にする
4. `docs/guide/glossary.md` 135 行目（difficulty）：「値のない問題（典型90 など）は「diff —」と書く。」→「値のない問題（典型90 など）は「diff なし」、AtCoder Problems が参考値とする古いコンテストの値は「diff 1856・参考値」と書く。」
5. `planning/style-guide.md` §10（275 行目）：「（difficulty のない問題は `diff —`）」→「（difficulty のない問題は `diff なし`、台帳で参考値（experimental: true）の問題は `diff 1856・参考値`。どちらも fix_problems.py が作る）」
6. `planning/interfaces.md` §3：82 行目の正規表現の diff の部分を `（diff (?P<diff>\d+(?:・参考値)?|なし)）` に（label の部分も道具は `(?:[^\[\]]|\[[^\[\]]*\])+` で、今の文書の `[^\]]+` と違う。合わせるならこれも）。86 行目「difficulty は台帳の値と一致させる」に「参考値の印も」を足す
7. （任意）`planning/design.md` §6.6（442 行目）「difficulty は「diff 1882」のように数値と色を添える」に「値がなければ「diff なし」、参考値は「diff 1856・参考値」」を足す

## メインに判断してほしい点

1. **updated の変更**：brief の「本文を直したページは updated: 2026-10-29」と #50 の前例（図の代替テキストの機械的な直しでも 27 ページの updated を変えた）に合わせ、行を作り直した 118 ページの updated を変えた。このため gen_site の版が変わる（上の表）。機械的な表示の直しでは updated を変えない方針なら、118 ページの `updated:` の行だけを戻せばよい（行の作り直しとは別の行）
2. how-to-use の「典型90 は題名の★が難しさの目安になる（典型90問の★とレベル）」の 1 文を残すか（指示の外。Issue #5 の案の 3 つ目）
3. **表の参考値**：問題集の表（gen_site.py の `problem-sets`）の DONUTS-2015 C（donuts_2015_3）は参考値 1661 だが、表では「1661」とだけ出る。最近の ABC の表には参考値の問題はない。表の「—」はそのままの決定だが、参考値の印を表にも出すか（出すなら gen_site.py の `b_problem_sets` で `used_problems` に experimental を持たせる）
4. textlint の警告 1 件の増加（linear-recurrence-fast 179 行目の sentence-length 121 字）を、警告のまま残してよいか
5. マージの注意：148 ページの問題の行（と 118 ページの updated）を変えたので、ほかのグループのブランチが同じ行を触っているとぶつかる。ぶつかったら、どちらかの行を取ってから `python3 tools/fix_problems.py` を流せば、前の形の行も今の形に直る（要約は保つ）。ほかのブランチで「（diff —）」と書いた新しい行は、check_pages が前の形として指摘する
