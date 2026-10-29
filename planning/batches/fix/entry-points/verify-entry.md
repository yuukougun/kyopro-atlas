# entry の検証の報告（グループ entry-points）

- 検証した担当：entry（報告は [entry.md](entry.md)）。担当の Issue：#6・#7・#58・#65・#75（#65・#75 は入口の 1 行だけ）
- 作業ツリー：/home/yuuki/projects/kyopro2/kyopro-atlas-wt/entry-points（ブランチ feat/entry-points、HEAD d112089、まだ commit していない変更）。ファイルは直していない（この報告だけを書いた）。git は読むだけ
- 検証日：2026-10-29。作業用フォルダ：`/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/7a638398-7759-4637-95c7-6739e8d52414/scratchpad/fix/entry-points/verify-entry`（以下「作業用」。ビルド・画面写真・数えたスクリプトを置いた）

## まとめ

| Issue | 判定 | 一言 |
| --- | --- | --- |
| #6 | 合格 | 台帳で pages を持つ 1251 問がちょうど 1 行ずつあり、表示名・行き先・役割・並びが台帳と一致する（ビルドした HTML で数えた） |
| #7 | 合格 | 3 つの目的の最初の行から 1 回のクリックで最初のページへ行ける。使い方へのリンク、対象の読者と読み方の 2 文がある |
| #58 | 直しが要る（1 件） | 完了の条件 3 つは満たす。ただし使い方 #structure に足した並びの説明が、今の order と食い違う |
| #65 | 合格（担当分） | 考察の入口に発想リストと逆引き辞典（言い回し）への 1 行がある |
| #75 | 合格（担当分） | 題材別の入口に by-topic の表への 1 行があり、「—」だけのレベルの列はなくなった |

直しが要る点は 1 件。検査（gen_site --check・check_pages・unittest・mkdocs build --strict）はすべて通る。

## 直しが要る点

### 1. 使い方 #structure の並びの説明が、今の order と食い違う（#58）

- ファイル：`docs/start/how-to-use.md` 95 行目
- 内容：「章の中では前提のページが先に来て、同じ話題のページ（基本形と、その応用・発展）は続けて並ぶ。」と、今の並びの事実として書いている。前半（前提が先）は check_pages の警告「同じ分野の前提が後ろ」が 0 件なので成り立つ。後半（同じ話題は続けて並ぶ）は、front matter の order を変えていない今は成り立たない章がある
  - グラフの最短路の章：ベルマンフォード法（order 140、青）と、それを前提にする差分制約（180、青。prerequisites に bellman-ford）の間に、最短路 DAG・状態を頂点にする・時刻で変わる辺（どれも水、前提は dijkstra）の 3 ページが入る。entry の提案 1 の「bellman-ford 140 → 175」はこの直しで、まだ反映されていない
  - 整数論・代数の GCD と合同式の章：Issue #58 が例に挙げた proof-patterns（基礎、前提 gcd-lcm）は、今も章の末尾（黄の位数・原始根の後）にある
  - 木の「木全体の形」の章：木の同型判定（発展、前提 tree-diameter）と木の直径の間に 3 ページある。提案 1 の tree-centroid 110 → 135 を反映してもこのままなので、提案 1 だけでは (2) の方針に合わない章が残りうる（同じ話題かどうかは判断が要る）
- 読者への影響：入口や使い方を読んだ人が「続けて並ぶ」と受け取ると、差分制約の基本形がすぐ上にないことの説明がつかない
- 直し方の案（どちらか）
  - (a) 95 行目を、今の並びでも成り立つ書き方にする。例：「章の中では前提のページが先に来る。レベルの順ではないので、後ろに低いレベルのページが来ることもある。易しさは各ページのレベルの印で見分ける。」（同じ話題を続けて置く方針は gen_site の注記と手引きの提案に残す）
  - (b) メインが提案 1 の order の並べ替えを同じ pull request で反映し、(2) に合わない章が残っていないかを確かめてから、今の文のままにする

## #6 問題番号から引ける一覧（合格）

作業用に `mkdocs build --strict` したサイトの `guide/problem-index/index.html` を、gen_site の関数を使わずに読む `verify_index.py`（作業用）で台帳と照らした。表示名の規則だけは interfaces.md §3 と同じ `check_pages.problem_label` を使った。

- **全問題がある**：台帳 1255 問のうち pages を持つ 1251 問が、索引の行（li）にちょうど 1 回ずつある。台帳にない行・2 回出る問題はない。台帳の中で表示名が重なる問題はないので、表示名で問題を特定できる
- **表示名**：1251 行すべてで、HTML に出た文字が台帳の表示名（`ABC174 E. Logs` の形）と一致し、行き先のページの問題の一覧の表示名とも一致する。`M<=ab`・`E [max]`・`rng_10s` などの特別な文字も崩れない
- **行き先と役割**：各行の（ページ, 役割）の組が台帳の pages と一致する。並びは例題 → 練習 → 力試しで、同じ役割の中は nav.yml の順（1251 行すべて）。台帳で 1 問が例題になるページは多くて 1 つ（461 問）
- **跳び先**：1586 本のリンク（例題 461 本は問題 ID の小見出し `#abc300_e` の形、練習 852 本は `#practice`、力試し 273 本は `#challenge`）の anchor がすべて HTML にあり、その見出しの節の中に、同じ役割の kp-problems の囲みでその問題の行がある
- **区分と並び**：ABC 967 行（回の 50 ごとの小見出し 10 個。`abc-001`〜`abc-450`）・ARC 92・AGC 27・問題集 133（典型90・EDPC・TDPC・ACL Practice・鉄則本・アルゴ数学の 6 個の小見出し）・そのほか 32。ABC・ARC・AGC は回 → 記号の順、問題集は PROBLEM_SETS の順 → 番号の順、そのほかはコンテストの表示名の順になっている（全行で確かめた）。ページ内の跳び先のリンク 88 本はすべて実在する
- **atcoder.jp へのリンク**：索引の本文（article）に 0 本（手引き §2.5 のとおり）
- **最近の ABC の 1 文**：`ABC450〜ABC480` の小見出しにだけ「ABC451〜ABC480 の D〜G（120 問）は…」がある。recent-abc.yaml は abc451〜abc480 の D・E・F・G 各 30 問で、数が合う
- **入口**：ホームの「解けなかった問題から引く」の 4 行目、使い方の #lookup の表の行（111 行目）、ナビゲーション（横断ページ › 辞書として引く、用語の索引の次）から 1 回のクリック。一覧にない問題の案内（逆引き辞典 2 つ・用語の索引・最近の ABC の表）は要点と「引き方」にある
- **既存の 2 つの表**：problem-sets に索引への 3 か所の案内、索引から両方の表への案内があり、相互にリンクしている。problem-sets の問題集の表は例題のページが先・例題の小見出しへ跳ぶ形に変わった（列は同じ。entry の判断してほしい点 2）。表の上の箇条「例題として載せたページから読むとよい」とも合う
- **手書きの部分**：要点・別名の行・導入・「引き方」は、題名を主語にした導入、だ・である調で、述べている並び・行き先・最近の ABC の扱いは上の数え上げと一致する。要点の項目（何のページか・使い方・ほかの入口）は term-index・reverse-index-signs と同じ形
- **完了の条件**：3 つとも満たす（`gen_site.py --check` も通る）

## #7 トップページの目的別の入口（合格）

- 「目的別の入口 {#entrances}」の下に 3 つの小見出し。最初の行はそれぞれ 辞書としての引き方（how-to-use#lookup）・色別ロードマップ・この教材の使い方で、どれも 1 回のクリック。Issue の案の行（逆引き辞典・用語の索引・問題番号の索引、レベル別の一覧・知識マップ、記法と用語の約束）がすべてある
- 「色ごとに順に学ぶ」の最初が色別ロードマップなのは、how-to-use #by-color の「色別ロードマップから始める」と合う
- 対象の読者とページの読み方の 2 文（5 行目）は how-to-use #purpose・#page-anatomy と食い違わない。リンク先の #purpose・#page-anatomy・#lookup・#by-color は、この作業ツリーと origin/main の両方にある
- 分担（行は gen_site の `b_home_links`、目的の説明・読者・読み方は docs/index.md の手書き）は gen_site の docstring と tools/README.md に書いてある
- 390px・390px ダーク・1280px で撮った。横のはみ出しなし、JS の例外なし（GitHub の API の 403 だけ。手元の通信の都合で、変更とは関係ない）

## #58 分野の入口（直しが要る点 1 件。完了の条件は満たす）

### 390px で 1 画面に 6 ページ以上（満たす）

`measure-entrances.mjs`（作業用。CDP で 390×844・mobile にし、ヘッダー 48px の下の 796px を 1 画面とする）で、章のページの箇条書きの範囲を 1px ずつ動かして数えた。前のビルド（HEAD を `git archive` して作業用でビルド）も同じ方法で測った。

| 分野 | ページ | 高さ（前→後） | 一部でも見える：最悪・平均 | 題名が見える：最悪・平均 | 完全に見える：最悪・平均 |
| --- | --- | --- | --- | --- | --- |
| basics | 32 | 9261→6170 | 5・6.9 | 5・6.0 | 4・5.4 |
| dp | 38 | 9690→5325 | 7・8.2 | 6・7.2 | 5・6.5 |
| graph | 47 | 12104→6808 | 5・7.2 | 4・6.2 | 3・5.5 |
| tree | 26 | 7394→3983 | 6・7.3 | 5・6.4 | 4・5.7 |
| ds | 37 | 10058→5430 | 6・7.7 | 5・6.7 | 4・6.0 |
| math | 42 | 10945→5718 | 7・8.2 | 6・7.2 | 5・6.6 |
| comb | 49 | 13541→6728 | 6・7.7 | 6・6.8 | 5・6.1 |
| cpp | 20 | 6047→3338 | 6・7.1 | 5・6.2 | 4・5.5 |
| guide | 16 | 4310→2248 | 7・8.0 | 6・7.0 | 5・6.4 |
| thinking・string・geometry・patterns | 9・13・8・10 | — | 6〜10 | 6〜10 | 5〜10 |
| start・misc | 3・4 | — | 全ページが 1 画面に入る | | |

- Issue が「comb は縦 13,541px（1 画面に 3〜4 ページ）」と書いた数え方は、「一部でも見える」ページの数と合う（前のビルドの comb は最悪 3・平均 3.9、高さ 13,541px で一致）。同じ数え方で、新しい入口は 6 ページ以上の分野がどこから見ても 6 以上で、5 に下がるのは basics と graph の章の境目のごく一部（スクロールの位置の 1%）だけである。条件は満たすと判断した
- 横のはみ出しはどの入口にもない（scrollWidth = 390）
- 参考：entry.md の「1 画面に平均 7.3〜11 ページ」は 796px ÷ 項目の間隔の平均、「最悪 6〜7」は画面の上端を項目の上端にそろえ、長い章の中だけで数えた値で、どちらも読者が見る数より多めである。完全に見えるページで数えると、平均は 5.4〜6.6（basics・graph・tree・string・cpp は 6 未満）で、章の見出しと「ほかの章の関連ページ」の行をまたぐ位置では 3〜4 になる。pull request に数を書くなら上の表の値を使うとよい

### そのほかの完了の条件（満たす）

- 15 分野の入口すべてから横断ページへ 1 回のクリックで行ける：start（辞書としての引き方・色別ロードマップ）、guide（横断ページの一覧そのもの）、basics〜cpp（学ぶ順・使い分けの節・問題集の表・自作の手引きのうち関係するもの）、thinking（発想リスト・逆引き辞典）、patterns（逆引き辞典の by-topic）。使い分けの節（FIELD_COMPARISONS）は、method-comparison の各節からその分野へのリンクの数を数えて、妥当な選び方だと確かめた
- 木の入口の「ほかの分野にある関連ページ」に木 DP・全方位木 DP・二乗の木 DP（どれも dp/）がある。グラフの最短路の章の後に「ほかの章の関連ページ：幅優先探索（BFS）…（基本と探索の章）」がある
- 全 15 入口の 354 項目で、HTML に出た題名と要約の 1 文目が front matter の title・summary の 1 文目と文字どおり一致する（エスケープの崩れなし）。レベルの印の class は overrides/main.html の LV_CLASS と kp.css にそろっている。ダークモードでも読める（木・基本 1280・考察を撮った）
- 並びの方針は gen_site.py 645 行目の注記と how-to-use 95 行目に書いた。ただし how-to-use の文は上の「直しが要る点 1」

## #65 考察の章の入口（担当分は合格）

- 考察の入口（`docs/thinking/index.md` 12 行目）に「問題の形から試す型を選ぶときは詰まったときの発想リスト、言い回しからは逆引き辞典（言い回しから）を使う。」の 1 行（`../guide/thinking-checklist.md` と `../guide/reverse-index-signs.md#by-phrase` へのリンク）があり、Issue の文案どおり。リンク先の見出し（言い回しから引く `{#by-phrase}`）もある
- 担当外の残り（6 ページから発想リストへのリンク、9 ページの合図）は、origin/main に入った #83（cross-links）で直っている。試しにマージした作業用の写しでは、考察の 9 ページすべてに thinking-checklist へのリンクがあった（合図の文の中身は確かめていない）

## #75 題材別の入口（担当分は合格）

- 題材別の入口（`docs/patterns/index.md` 12 行目）に「問われ方の例から題材を選ぶときは、逆引き辞典の「題材から引く」の表を使う…」の 1 行（`../guide/reverse-index-signs.md#by-topic` へのリンク）があり、リンク先の見出し（題材から引く `{#by-topic}`）もある
- 表をやめたので「—」だけのレベルの列はない。レベルを持たない分野なので、印も「ページ名の横の印はレベル」の文も出ない
- 「円環」のページは担当外

## 生成物の差分（意図どおり）

- `nav.yml`：横断ページ › 辞書として引く の用語の索引の後に 1 行だけ
- `docs/<15 分野>/index.md`：表 → 箇条書き、案内の段落、関連ページ（上の確認のとおり）
- `docs/lists/index.md`・`docs/lists/kind-guide.md`：案内のページの数 33 → 34 と問題番号の索引の行
- `docs/llms.txt`：版・ページ数 354・横断ページ 16・問題番号の索引の行。`docs/index/guide.md`：問題番号の索引の項。`overrides/assets/data/graph.json`：版と problem-index の 1 行
- `docs/guide/term-index.md`：別名 3 つと題名の 4 行。`docs/start/how-to-use.md`：fields の表の横断ページの行・lists の案内の数・version
- 版 9d105969f6d0 → 18d3adffb7f2（ページが 1 つ増え、版のハッシュに問題の行の上の見出しの anchor が加わったため）。Python 3.10.12 と .venv の 3.12 で同じ出力になる
- gen_site のコード（`_problem_uses`・`_index_parts`・`index_key`・`b_problem_index_*`・`recent_note`・`entrance*`・`field_related`・`chapter_related`・`b_home_links`）を読み、上の数え上げと合わせて誤りはないと判断した。試験（EntrancesTest 8 件）の問題 8 つの題名・difficulty は台帳と `tools/ap.py show` に合う

## 検査（作業ツリーで、書き換えないもの）

| 検査 | 結果 |
| --- | --- |
| `python3 tools/gen_site.py --check`（3.10.12）・`.venv/bin/python tools/gen_site.py --check` | どちらも「生成物は最新」（版 18d3adffb7f2） |
| `python3 tools/check_pages.py`（全 354 ページ）・`--page problem-index,problem-sets,how-to-use` | エラー 0・警告 0 |
| `python3 tools/fix_problems.py --check` | 直すべき行 0 |
| `python3 -m unittest discover -s tests/tools` | 52 件 OK（2 件は Python-Markdown がないので飛ばす）。`.venv/bin/python` では 52 件 OK |
| `npx textlint docs/guide/problem-index.md docs/index.md docs/start/how-to-use.md docs/guide/problem-sets.md` | エラー 0、警告 5。5 件とも変更前のファイル（HEAD を取り出したもの）に同じものがある |
| `.venv/bin/mkdocs build --strict -q -d <作業用>/site` | 通る（validation の anchors を含む） |

検査の前後で `git status` は変わらない（作業ツリーに書いていない）。

## マージの試し（参考）

origin/main は #82 に加えて #83（cross-links）も入り、このブランチより 13 コミット先にある（entry.md の「6 コミット」より増えた）。作業用にリポジトリを複製し、この変更を commit したうえで origin/main（e8e3ff5）をマージして試した。

- 衝突は `docs/start/how-to-use.md`・`docs/llms.txt`・`overrides/assets/data/graph.json` の版の行だけ。how-to-use の手書きの変更（#structure・#lookup）と origin/main の新しい節（#report など）は自動で合わさった。how-to-use はファイルごと片方を取ると、どちらかの手書きの変更が消えるので、版の行だけ直すか gen_site に任せる
- 衝突を解いて `python3 tools/gen_site.py` を流すと 3 ファイル（版）だけが変わり、その後の `gen_site --check`・`check_pages`（0・0）・unittest（52 件 OK）・`mkdocs build --strict` がすべて通った。新しいページの下部の「関連」（#56 の部品）も、related の 6 項目が正しいリンクで出た

## 気づいた点（直さなくてもよいもの・メインへの参考）

- `claude/explain.md` 27 行目の入口の表の「問題 ID」の行は、問題集の番号を `guide/problem-sets.md`（#sets-to-pages・#recent-abc）で引くとしている。17 行目は「入口の表も how-to-use の表と同じ」としているので、how-to-use の行が問題番号の索引に変わったのに合わせ、`guide/problem-index.md` を足すとよい（共有の指示のファイルなので提案）
- ホームの 5 行目「どのページも、冒頭の要点の 4 項目（できること・使う場面・計算量・前提）で…」は、案内のページでは項目が違う（how-to-use #page-anatomy は「案内のページでは『何のページか』と『使い方』になる」と書く）。気になるなら「手法のページは」などに言い換える
- entry の提案 1 の order の並べ替えは、上の「直しが要る点 1」を (b) で直すときの前提になる

## 使ったもの（作業用）

- `verify_index.py`：索引と台帳・本文・HTML の照合。`measure-entrances.mjs`：入口の 1 画面のページ数（結果は `measure-390-new.txt`・`measure-390-base.txt`）。`shoot.mjs`：画面写真（`shots/`）
- ビルド：`site/`（この作業ツリー）、`site-base/`（HEAD）、`site-merged/`（試しのマージ）。HTTP の配信（127.0.0.1:37419）とヘッドレスの Chrome（CDP 37420）は使い終えて止めた
