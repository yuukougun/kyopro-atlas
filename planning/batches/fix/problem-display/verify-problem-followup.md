# verify-problem-followup の報告（工程11 グループ problem-display・Issue #5・#76 の検証）

作業ツリー：`kyopro-atlas-wt/problem-display`（ブランチ fix/problem-display。HEAD d112089 に、commit していない変更）。日付：2026-10-29。

検証したのはグループの直し全体である。前の担当（[problem-lines.md](problem-lines.md)）の問題の行の作り直し・道具・試験・how-to-use と、続きの担当（[problem-followup.md](problem-followup.md)）の progress.js・kp.css・atcoder-system・用語集を見た。ファイルは直していない（書いたのはこの報告だけ）。

## まとめ

| Issue | 判定 | 一言 |
| --- | --- | --- |
| #5 | 合格 | 値のない問題の行は 168 行とも「（diff なし）」で、文字だけで意味が分かる（ツールチップに頼らない）。check_pages は前の形「（diff —）」を、直し方を添えたエラーにする。check_pages・fix_problems --check は通る |
| #76 | 合格 | 台帳で `experimental: true` の 40 問（40 ページ 44 行）が「（diff N・参考値）」になり、本文の参考値の問題の集合は台帳とちょうど同じ。色の丸も付く。fix_problems --check は通る |

**直しが要る点：0 件。** メインへの申し送り（担当の直しではないもの）は最後の節にまとめた。

## 確かめたこと

### 1. 問題の行の作り直し（前の担当）

自分で書いた照合のスクリプト（作業用フォルダの `vlines.py`）で、HEAD と作業ツリーの docs/ を行ごとに比べた。

- `git diff --stat`：156 ファイル（+380／−354）。内訳は docs 151（問題の行のページ 148、手で直した how-to-use・atcoder-system・用語集）、overrides 2、tools 3。新しいファイルは `tests/tools/test_problem_lines.py` とこのバッチの報告だけ
- 変わった行は次の 3 種類だけだった。行数は atcoder-system（箇条を 1 つ足した）を除いて同じ
  - 「（diff —）→（diff なし）」168 行・126 ページ。どれも台帳で difficulty が null の問題
  - 「（diff N）→（diff N・参考値）」44 行・40 ページ・40 問。どれも台帳で experimental が true、N が台帳の値の問題
  - front matter の `updated` が 2026-10-29 になったもの 120 ページ（前の担当の 118 と、用語集・atcoder-system）。ほかの front matter の行は変わっていない
- 変わった問題の行で、字下げ・label・URL・要約（「：」の後ろ）は 1 文字も変わっていない
- 問題の行を変えたページは、どれも `updated: 2026-10-29` になっている。本文を変えずに updated だけを変えたページはない
- 全ページの照合（フェンスの外の kp-problems の囲み）：1586 行 ＝ ふつう 1374・参考値 44・なし 168。どの行の diff も台帳から作る形と一致し、前の形の行は 0
- 台帳で `experimental: true` は 40 項目で、どれも値と pages を持つ。本文で参考値になっている問題の集合との差は空。experimental の値は true 40・false 1068・null 147 で、参考値になるのは true だけ
- AtCoder Problems のキャッシュ（`.cache/atcoder-problems/`、2026-10-24 取得）とも照らした（`vexp.py`）。台帳で true の 40 問は、どれもキャッシュでも `is_experimental` が true。台帳で true でないのにキャッシュで experimental になっている、本文で使う問題はない
- 作り直しの再現：HEAD の docs を作業用フォルダに出し、作業ツリーの fix_problems.py で直すと、212 行・148 ファイルが直った。結果は作業ツリーの docs と一致した（違うのは updated と、手で直した 3 ページの文だけ）。行は道具で作られ、手では変えられていない

### 2. 道具（check_pages.py・fix_problems.py）と試験

- docs・snippets・data の写しを作業用フォルダに作り、誤った形を 5 行入れて `check_pages.py --root … --ledger …` を流した。5 件ともエラーになり、終了コードは 1 だった
  - 「（diff —）」：書式の違い。「difficulty のない問題は（diff —）ではなく（diff なし）と書く。tools/fix_problems.py で直せる」と出る（tree/lca.md:209）
  - 「（diff 1856（参考値））」「（diff なし・参考値）」：書式の違い。3 つの形が示される
  - 参考値の問題の「（diff 1024）」：台帳との違い「diff（台帳から作ると diff 1024・参考値）」と出る（graph/bfs.md:185）
  - ふつうの問題の「（diff 634・参考値）」：台帳との違いになる（graph/dijkstra.md:257）
- 同じ写しで `fix_problems.py --check` は 5 行（4 ファイル）を出して終了コード 1。直すと、5 行とも作業ツリーと同じ行に戻った（要約は保たれた）
- 新しい試験 `tests/tools/test_problem_lines.py`（14 件）を読んだ。一時のフォルダで動き、リポジトリには書かない。試験に使う 3 問（abc300_e 1354・abc014_4 1856 参考値・typical90_a なし）は `tools/ap.py show` で一致を確かめた
- `tools/README.md` の 2 か所の説明は、道具の動きと合っている

### 3. progress.js・kp.css（続きの担当）

- `markDifficulty` は `.kp-problems li` ごとに呼ばれる（`mountProblems`）。「diff なし」で入る `return` が止めるのはその行の走査だけで、ほかの行には影響しない
- 作業用フォルダへビルドした（`uv run mkdocs build -q -d <作業用フォルダ>/site`。成功。作業ツリーの git status は変わらない）。http.server（ポート 38417）とヘッドレスの Chrome（DevTools Protocol。api.github.com への取得は止めた）で、問題の一覧のある 304 ページの全 1586 行を確かめた（`vcdp.mjs`）
  - ふつう 1374 行・参考値 44 行・なし 168 行で、check_pages の行数と一致する
  - ふつうと参考値の行は、次がすべて期待どおり
    - span.kp-diff がちょうど 1 つで、文字は「diff N」
    - class は帯のとおりで、title は「difficulty N（色）」か「difficulty N・参考値（色）」
    - `--kp-diff-fill` が帯の中の位置で、`::before` の丸が gradient で塗られている
    - 直前の文字は「（」で、直後の文字は「）」か「・参考値）」
  - なしの行には span がない。どの行にも「解いた」のチェック欄が付く
  - 食い違いは 0 件、コンソールのエラーも 0 件だった
- 見た目（幅 390px・ダークモード。作業用フォルダの `shots/`）
  - 参考値の行：ABC007 C は緑、ABC014 D は青（ダーク）、ARC013 C は青、ARC038 D は赤。丸と太字の「diff N」が付き、「・参考値」は地の文のまま
  - なしの行：典型90 001 は丸なしで、ライトとダークの両方を見た
  - 幅 1280px の ABC007 C も見た
  - どのページも横にはみ出さない（scrollWidth 390）
- kp.css の変更は注記だけで、注記の内容は今の動きと合う

### 4. 本文（how-to-use・atcoder-system・用語集）

- **事実**：AtCoder Problems の推定のソースを `gh api` で読んだ（github.com は手引きの付録 B にある。kenkoooo.com・atcoder.jp は開いていない）
  - 読んだのは 2 つある。ページの参考がリンクする master の `lambda-functions/time-estimator/function.py`・`rating.py` と、いまの既定のブランチ main の `estimator/main.py`・`rating.py`（最後の commit は 7b3c901・2026-06-15）
  - どちらも次の 3 点が同じだった
    - `infer_contest_type` は、rate_change が「-」のコンテストのうち、ID が abc・arc で始まるものと `old_sponsored_contests` の 40 件を、公式のレートより前（is_rated が False）とする
    - その問題は「contests before official rating system. using the emulated rating」のとおり、それまでの順位から `RatingSystem` が再現したレートで推定する
    - その問題の `is_experimental` を true にする
  - atcoder-system 111 行目の「当時の参加者にはレートがないので、…それまでの順位から再現したレートで推定し、試験的な値（experimental）として出している」は、このコードと合う
- **境の日付**：キャッシュの contests.json で確かめた
  - abc041（2016-07-02）と arc057（2016-07-09）は rate_change が「-」だった
  - 最初の Rated は agc001（2016-07-16、All）。abc042・arc058（2016-07-23）は Rated だった
  - experimental で値のある 514 問は、初出のコンテストがどれも「-」で、いちばん新しい初出は arc057 だった
  - したがって、atcoder-system の「2016 年 7 月の abc041・arc057 まで」と、how-to-use の「2016 年 7 月までの Rated でなかったコンテスト」は正しい。atcoder-system の ABC の形式の表（abc001〜041 は Rated なし）とも合う
- **約束の数**：推定の約束は「4 つある」と箇条の 4 つが合う。110 行目の「値が付かない」と 111 行目の「Rated でなくても値が付く」は、例外として順に読めて、食い違わない
- **表の「—」**：110 行目の「（表の diff の列では「—」）」は、gen_site.py が表で値のないときに「—」を書くこと（problem-sets の表など）と合う
- **how-to-use の #problems（230 行目）**：「diff なし」の説明、★への案内、参考値の 1 文がある
  - 典型90問の★とレベル（problem-sets#typical90-stars）の節は、★を難しさの目安として扱っている
  - 「Rated」は how-to-use で初めて出る語で、用語集へリンクしてある
  - 例の 1024 は abc007_3 の値（ap.py で 1024・参考値）
- **用語集（135 行目）**：説明が atcoder-system・how-to-use と食い違わない。`[Rated](#rated)` の anchor もある
- `check_pages.py --page how-to-use --page atcoder-system --page glossary -v`：エラー 0・警告 0
- textlint（変わった docs の 151 ファイルと、同じファイルの HEAD の版）：エラー 0。警告は 2234 → 2235
  - 増えたのは `docs/math/linear-recurrence-fast.md` 179 行目（TDPC T の行）の sentence-length 121 字だけで、「—」が「なし」になって 1 字増えたため。要約は変えない決まりなので警告のまま残してよい
  - atcoder-system 242 行目（参考の function.py の行）は、もとから警告で、140 字から 202 字に延びた。件数は変わらない

### 5. 検査（作業ツリーで、書き換えないもの）

| 検査 | 結果 |
| --- | --- |
| `python3 tools/fix_problems.py --check` | 直すべき行 0・直せない行 0・台帳にあって本文にない（警告）0（見たページ 354）、終了コード 0 |
| `python3 tools/check_pages.py` | エラー 0・警告 0（353 ページ、本文の問題 1586 行）、終了コード 0 |
| `python3 -m unittest discover -s tests/tools` | 58 件 OK（skipped 2：Python-Markdown がない試験）。`.venv/bin/python` で流すと 58 件 OK・skip なし |
| `node --test "tests/viz/*.test.mjs"` | 216 件 pass・fail 0 |
| `python3 tools/gen_site.py --check --diff` | 古いのは 3 ファイル（`docs/llms.txt`・`overrides/assets/data/graph.json`・how-to-use の版の目印）。中身は版のハッシュ（9d105969f6d0 → 9ed22a379f83）だけ。updated の最大は 2026-10-29 のまま |

### 6. 最新の main との重なり

この検証の間に origin/main が進み、作業ツリーの HEAD より 20 commit 先になった（#82 page-template・#83 cross-links・#84 patterns。いまは a55ee9d）。

- 両方で変わったファイルは 14 ある（how-to-use・kp.css と、問題の行のページ 12）。作業用フォルダで `git merge-file` による 3 方向のマージを試すと、ぶつかりは 0 だった
- origin/main は、問題の行も台帳 `data/problems.yaml` も変えていない。前の形の「（diff —）」168 行はそのまま残っていて、このブランチで直る。新しいページ patterns/circular には問題の囲みがない。tools・schema・tests・JS・mkdocs.yml も変えていない
- origin/main にこのブランチの変更を重ねた木を作業用フォルダに作り、`check_pages.py --root` と `fix_problems.py --check --root` を流した。エラー 0・警告 0、直すべき行 0 だった

## 直しが要る点

なし。

## メインへの申し送り（担当の直しではないもの）

1. **共有の文書の古い説明**（前の担当の提案 5〜7。まだ反映されていない）
   - `planning/style-guide.md` §10（作業ツリー 275 行目、origin/main では 280 行目）は「difficulty のない問題は `diff —`」のままである。手引きどおりに書いた行は check_pages のエラーになるので、マージのときに合わせるとよい
   - `planning/interfaces.md` §3 の 82 行目（origin/main では 85 行目）の正規表現の diff の部分は `\d+|—` のままである
   - `planning/design.md` §6.6 の 442 行目は任意
2. **生成物**：マージの後に `tools/gen_site.py` を流す（上の表の 3 ファイル。版のハッシュだけ）
3. **updated の扱い**（前の担当の判断 1）：origin/main の #9（page-template）で、ページの最後の行に段階と更新日が出るようになった。このブランチの 120 ページの updated の変更は、読者には「更新日 2026-10-29」として見える。機械的な直しで updated を変えるかを決めるときの材料になる
4. **表の参考値**（前の担当の判断 3）：problem-sets の表の DONUTS-2015 C（donuts_2015_3。`docs/guide/problem-sets.md` 458 行目）は参考値の 1661 だが、表では「1661」だけになる。Issue #76 の範囲は問題の行（fix_problems.py が作る行）なので、完了の条件には入らないと判断した
5. 任意で、直さなくても読めるもの
   - スマホの幅では「（diff な／し）」「・参／考値）」のように行の途中で折り返す。文字だけで読めるので Issue #5 の条件は満たす。まとめたいなら、続きの担当の提案 2（nowrap）がある
   - 用語集の「（2016 年 7 月まで）」は月の粒度で、atcoder-system は「2016 年 7 月の abc041・arc057 まで」と細かい。どちらも誤りではない（続きの担当の判断 1）
   - how-to-use の★の 1 文（前の担当の判断 2）は、#levels の「典型90 は★で読む」と内容が近い。ただし節を単独で読んでも通じるための案内なので、残してよい
6. **報告の出典の記録**：続きの担当の報告にある「function.py の最後の commit は e87addd・2025-04-05」は正確でない
   - e87addd（「bomb」）は既定のブランチ main の commit で、`lambda-functions/` を消したものである。ページの参考がリンクする master では、function.py の最後の commit は d1b837e（2021-05-17）だった
   - いまの推定は main の `estimator/main.py` にあり、同じ判定をしている。そのため、ページの記述と参考のリンク（master の function.py は今も読める）は正しく、直す必要はない
   - 参考を今のコードに向けるかは、この Issue の外の話である

## 作業用フォルダ

`/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/7a638398-7759-4637-95c7-6739e8d52414/scratchpad/fix/problem-display/verify-problem-followup/`

- `vlines.py`：行の照合
- `vexp.py`：キャッシュとの照合
- `vcdp.mjs`：Chrome で全行を確かめるもの。結果は `cdp-all.json`
- `vshot.mjs`：見た目の撮影。PNG は `shots/`
- `src/`：AtCoder Problems のソース
- `tree/`・`headtree/`・`merged/`：試しの写し

http.server と Chrome は止めた。
