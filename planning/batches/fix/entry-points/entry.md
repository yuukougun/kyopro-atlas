# entry の報告（グループ entry-points）

- 担当の Issue：#6・#7・#58・#65・#75（#65・#75 は入口の 1 行だけが担当）
- 作業ツリー：/home/yuuki/projects/kyopro2/kyopro-atlas-wt/entry-points（ブランチ feat/entry-points）。git は読むだけで、commit などはしていない
- **ブランチは origin/main より 6 コミット遅れている**（#82 page-template の取り込み前。HEAD は d112089）。下の「マージの注意」を参照
- 前の担当（使用量の上限で停止。報告なし）の途中の変更は `tools/gen_site.py` だけにあった。分野の入口（#58・#65・#75）の作り直しとホームの目的別の入口（#7）の行はほぼできていたので、読んで確かめたうえでそのまま使い、問題番号の索引（#6）の生成部分・新しいページ・手書きの部分・試験・文書・検査・見た目の確認を足した。前の担当が作業用フォルダに残した試作（入口の 5 つの形 v2〜v6 と 390px の画面写真、CDP で Chrome を動かす `tools/cdp.mjs`）も確かめ、v4（箇条書き＋要約の 1 文目）を採った判断を引き継いだ
- 直したファイル（作業ツリーからの相対パス）
  - 手で直した：`tools/gen_site.py`、`tests/tools/test_gen_site.py`、`docs/guide/problem-index.md`（新規）、`docs/index.md`、`docs/start/how-to-use.md`、`docs/guide/problem-sets.md`、`tools/README.md`、`planning/interfaces.md`
  - gen_site で作り直した生成物：`nav.yml`、`docs/<15 分野>/index.md`、`docs/lists/index.md`、`docs/lists/kind-guide.md`、`docs/llms.txt`、`docs/index/guide.md`、`overrides/assets/data/graph.json`、手書きのページの目印の中（`docs/index.md` の home-links、`docs/guide/problem-index.md` の problem-index-*、`docs/guide/problem-sets.md` の problem-sets、`docs/guide/term-index.md` の用語の索引、`docs/start/how-to-use.md` の fields・version）
- front matter：本文を直した `problem-sets` の `updated` を 2026-10-22 → 2026-10-29 にした（how-to-use はもとから 2026-10-29）。stage とほかの項目は変えていない。新しいページ `problem-index` は stage を draft にした

## まとめ

| Issue | 状態 | 一言 |
| --- | --- | --- |
| #6 | 完了 | 新しいページ「問題番号の索引」（guide/problem-index）に、本文に載せた全 1251 問を生成。ホーム・使い方の #lookup・ナビから 1 クリック |
| #7 | 完了 | ホームに対象の読者とページの読み方の 2 文、目的別の入口 3 つ（home-links）。使い方と問題番号の索引へのリンクあり |
| #58 | 完了 | 入口を表から箇条書き（レベルは小さな色の印）に。学ぶ順・使い分け・問題集・自作への案内、ほかの章・ほかの分野の関連ページ。並びの方針を決めた（並べ替えは提案） |
| #65 | 一部 | 担当の入口の 1 行は完了。6 ページの使い分けのリンクと 9 ページの合図は担当外 |
| #75 | 一部 | 担当の入口の 1 行とレベルの列の削除は完了。「円環」のページは担当外 |

## #6 問題番号から引ける一覧（完了）

- **新しいページ** `docs/guide/problem-index.md`（id `problem-index`、題名「問題番号の索引」、別名「問題番号から引く・問題 ID から引く・過去問の索引」、chapter「辞書として引く」、order 35 で用語の索引（30）と知識マップ（40）の間、type guide、stage draft）
  - 手書き：要点（何のページか・使い方・ほかの入口）、別名の行、導入、`## 引き方 {#how-to-read}`（行の形・役割・行き先・並び・見つからないとき）、各節の 1 文
  - 一覧にないときの案内：要点の「ほかの入口」と引き方の節に、逆引き辞典（言い回し・制約）・用語の索引と、最近の ABC の表へ案内する文を置いた
  - 生成部分の節：`## ABC {#abc}`・`## ARC {#arc}`・`## AGC {#agc}`・`## 問題集 {#sets}`・`## そのほかのコンテスト {#others}`（見出しは手書き、中は `###` から。手引き §16-11）
- **gen_site**（`tools/gen_site.py`）
  - `_index_parts`（477 行目）：本文の問題の一覧に載せた全問題を abc・arc・agc・sets・other に分ける。abc・arc・agc は回の数 → 記号、sets は PROBLEM_SETS の順 → 番号、other はコンテストの表示名の順。記号は `index_key`（4 桁にそろえる。Ex は G の後、001・A01 は数の順）
  - `index_line`（1239 行目）：1 行は `- ABC174 E. Logs → [答えで二分探索](../basics/binary-search-answer.md#practice)（練習）`。表示名は問題の一覧の label と同じで、atcoder.jp へのリンクは付けない（手引き §2.5）。ページは例題 → 練習 → 力試しの順（同じ役割はナビゲーションの順）。リンクは本文の問題の行の上にある直近の見出しの anchor（例題は `#abc300_e` の小見出し、練習・力試しは `#practice`・`#challenge`）へ跳ぶ（前の担当の `_problem_uses`）。全 1251 問で anchor が取れた（例題 461・練習 852・力試し 273）
  - `b_problem_index_abc`（1263 行目）：先頭に跳び先の行 `[001〜049](#abc-001)・…・[450〜480](#abc-450)`、回の 50 ごとの小見出し `### ABC001〜ABC049 {#abc-001}`（最後は載せた最後の回まで）。`recent_note`（1246 行目）が、最近の ABC の表（recent-abc.yaml）の回を含む小見出しにだけ「ABC451〜ABC480 の D〜G（120 問）は、本文に載せていない問題も[最近の ABC → ページ]の表で、使う手法のページを引ける。」を添える
  - `b_problem_index_arc`・`_agc`・`_other`：回の順・名前の順の箇条書き。`b_problem_index_sets`（1287 行目）：跳び先の行と問題集ごとの小見出し `{#sets-typical90}` など
  - 表ではなく箇条書きにした（幅 390px で列が細らない。#58 と同じ理由）
  - 既存の `problem-sets` の表（1209 行目）も同じ `uses` を使い、例題のページを先にして例題の小見出し・一覧の節へ跳ぶようにした（索引と並びをそろえた。表の形と列は変えていない）
  - 版のハッシュに、問題の行の上の見出しの anchor を足した（前の担当の変更。anchor が変われば版も変わる）
  - `FIELD_DESCRIPTIONS["guide"]` に「問題番号の索引」を足した（使い方の章の表・llms.txt・横断ページの入口に出る）
- **既存の 2 つの表との関係**：残して相互にリンクした
  - problem-sets（手書き）：要点の使い方（31 行目）に「古い ABC・ARC・AGC を含め、本文に載せた全問題は問題番号の索引で引ける」、最近の ABC の節の箇条（93 行目）に「この表は本文に載せていない問題も手法のページに対応させている。本文に載せた問題は…問題番号の索引で引ける」、問題集の節の箇条（232 行目）に「同じ問題は問題番号の索引の問題集とそのほかのコンテストの節にもある。索引は…diff の列を持たない」
  - 索引の側：引き方の節と ABC の最後の小見出しから最近の ABC の表へ、問題集の節から problem-sets の問題集の一覧と表へ。front matter の related にも problem-sets#recent-abc・#sets-to-pages を入れた
- **入口**：ホームの home-links（#7）、使い方の #lookup の表の行（111 行目。「問題番号・問題集の番号 → [問題番号の索引]・[最近の ABC → ページ]」）、ナビゲーション（横断ページ › 辞書として引く）、横断ページの入口。使い方の #structure（61・90 行目）の入口の列挙にも足した
- **確かめたこと**
  - 本文の問題の一覧の問題（1251）と台帳で pages を持つ問題（1251）が、問題 ID と (ページ, 役割) の組まで一致する（作業用の照合）。索引の行の数は 1251（abc 967・arc 92・agc 27・問題集 133・そのほか 32）
  - 特別な文字を含む題名（`M<=ab`・`#(subset sum = K) …`・`x = a^b`・`E [max]`・`Div. 1 & Div. 2`・`rng_10s` など 10 問）が、ビルドした HTML でそのままの文字で出る
  - `mkdocs build --strict`（validation の anchors を含む）が通るので、索引の全リンクの先の anchor がある。atcoder.jp へのリンクは生成部分にない（試験で確かめる）
  - 直接 `#abc-450`・`#sets-dp` を開くと、見出しがヘッダーの下（上から 68px）に出る。390px で横にはみ出さない
- **残った点**：ページは 1251 行で、390px では縦 81,239px ある。跳び先の行・目次・ページ内検索で引く前提にした。分けるなら ABC を別のページにする案がある（判断してほしい点 3）

## #7 トップページの目的別の入口（完了）

- **docs/index.md（手書き）**
  - 5 行目：対象の読者とページの読み方の 2 文。「想定する読者は、ABC の D までは安定して解け、E は時々解ける人である（[この教材の目的と範囲]）。どのページも、冒頭の要点の 4 項目（できること・使う場面・計算量・前提）で問題に使えるかを判断し、分からない前提のページを先に読んでから本文と例題に進めるように書いてある（[ページの構成と読み方]）。」
  - 10〜12 行目：「## 入口」を「## 目的別の入口 {#entrances}」にし、「目的に合う見出しを選び、その最初の行のページから読む。」を置いた（ホームの見出しへのリンクはサイトの中になかった）
  - info「制作中」（#4 で直し済み）は変えていない
- **home-links の生成**（`b_home_links`、907 行目。前の担当の変更をそのまま使い、記法の行の説明だけ直した）：`### 解けなかった問題から引く {#from-problem}`（辞書としての引き方 → 逆引き辞典 → 用語の索引 → 問題番号の索引）、`### 色ごとに順に学ぶ {#by-color}`（色別ロードマップ（進め方は使い方の #by-color）→ レベル別の一覧 → 知識マップ）、`### 初めて使う {#first-time}`（この教材の使い方 → 記法と用語の約束）。どの見出しも最初の行が最初に読むページ。ないページは「（準備中）」の文字だけにする
- **分担**：ページの題名・節の有無・レベル別の一覧の有無で変わる行は gen_site、目的の説明・対象の読者・ページの読み方は docs/index.md の手書き（gen_site の docstring と tools/README に書いた）
- **確かめたこと**：390px・1280px・ダークモードで撮った（下の「見た目」）。3 つの目的から 1 回のクリックで最初のページへ、使い方へのリンクは「辞書としての引き方」「この教材の使い方」と手書きの 2 文の中にある

## #58 分野の入口（完了）

- **形**（`entrance`・`entrance_items`、653・685 行目。前の担当の変更）：章ごとの「ページ・レベル・要約」の表をやめ、`- [題名](…) <span class="kp-mini kp-lv-水">水</span>：要約の 1 文目` の箇条書きにした。レベルの印はページ下部の前提と同じ `kp-mini`（`title` に difficulty の帯）。レベルのあるページのある分野では、説明の文に「ページ名の横の印はレベル（[レベルの意味]）である。」を足した。要約はかっこの外の最初の「。」まで（check_pages の文の数え方と同じ）
- **ほかの入口への案内**（`entrance_guides`、694 行目）：説明の後に 1 段落「学ぶ順：色別ロードマップ。使い分け：（method-comparison の節）。問題集：（problem-sets の問題集の表）。自作：自作ライブラリの設計と動作確認。」。使い分けの節は `FIELD_COMPARISONS`（138 行目。前の担当がその分野のページへのリンクの多い節を選んだ）、問題集は分野のページに 3 問以上載せた問題集を多い順に 3 つまで、自作は verify か acl を持つページのある分野だけ
- **ほかの章・ほかの分野の関連ページ**：章の後に「ほかの章の関連ページ」（章の主な kind を 2 つ目以降に持つ、同じ分野のほかの章のページ。例：最短路の章に BFS）、最後に `## ほかの分野にある関連ページ {#elsewhere}`（分野の主題の kind を持つ、ほかの分野のページ。例：木の入口に木 DP・全方位木 DP・二乗の木 DP）
- **章の中の並びの方針**（gen_site 645 行目の注記に書いた。読者向けの説明は how-to-use 95 行目）：gen_site は並べ替えず front matter の order（＝ナビゲーション）のまま出す。order は (1) 同じ章の前提を先に、(2) 同じ話題（基本形と、それを前提にする応用・発展）は続けて、話題の中はレベルの低い順に、(3) 話題どうしは最初のページのレベルが低い話題を先に（同じなら前提にされる話題を先に）、章の主題から外れる 1 ページの話題は章の終わりに置かない、の順で付ける。レベル順に並べ替えないのは、区間 DP と区間 DP の発展のような同じ話題を離さないため。今の order がこの方針に合わない章は提案 1 に挙げた（front matter は担当外）
- **how-to-use #structure**（95・97 行目）：「分野の入口のページに、章ごとのページの一覧とレベルと要約がある」を、章の中の並び（前提が先・同じ話題は続けて・レベルの順ではない・易しさは印で見分ける）と、入口にある案内・ほかの分野にある関連ページの説明に書き換えた
- **確かめたこと**
  - 390×844（ヘッダーの下 796px）で、章のページの箇条書きの 1 行の高さは平均 81〜109px、1 画面に平均 7.3〜11 ページ。最も悪い位置（長い章の中のどこから見ても）でも dp・graph が 6、ほかは 7 ページ（`measure.js`）。前のビルドとの比較：comb 13,541px → 6,728px、math 10,945 → 5,718、tree 7,394 → 3,983、basics 9,261 → 6,170
  - 15 分野の入口すべてに横断ページへのリンクがある（横断ページの入口は横断ページそのものの一覧）。木の入口から木 DP・全方位木 DP へ 1 クリック
  - 横にはみ出さない（全入口で scrollWidth = 390）
- **残った点**：サイドバー（nav）の木の章には木 DP などは出ない（nav に同じページを 2 回載せない）。360×640 の小さい画面では 1 画面に 4〜5 ページ（判断してほしい点 4）

## #65 考察の章の入口（一部：担当分は完了）

- `FIELD_NOTES["thinking"]`（153 行目）：考察の入口の説明の後に「問題の形から試す型を選ぶときは[詰まったときの発想リスト](../guide/thinking-checklist.md)、言い回しからは[逆引き辞典（言い回しから）](../guide/reverse-index-signs.md#by-phrase)を使う。」を出す
- 担当外で残るもの：6 ページ（complement・contribution・fix-variable・invariant・parity・reverse-thinking）の使い分けから発想リストへのリンクと、9 ページの導入の合図（Issue の「やること」の 2・3 番目）

## #75 題材別の入口（一部：担当分は完了）

- `FIELD_NOTES["patterns"]`：題材別の入口に「問われ方の例から題材を選ぶときは、[逆引き辞典の「題材から引く」](../guide/reverse-index-signs.md#by-topic)の表を使う（ほかの分野のページにある題材も載っている）。」を出す
- レベルの列（10 ページすべて「—」）は、表をやめたのでなくなった。レベルのない分野には印も「ページ名の横の印はレベル」の文も出ない（試験で確かめる）
- 担当外で残るもの：「円環」のページ

## 試験（tests/tools/test_gen_site.py）

`EntrancesTest` を足した（8 件）。試験の問題は台帳の確認済みの問題（abc006_4・abc174_e・abc451_e・arc005_3・agc001_e・typical90_a・dp_a・abl_d。題名と difficulty は台帳と ap.py で確かめた）。

- 索引の区分と並び、1 行の形（例題のページが先・例題は小見出し・練習は #practice）、ABC の跳び先の行と小見出しと最近の ABC の 1 文、問題集・ARC・AGC・そのほか、atcoder.jp へのリンクがないこと、problem-sets の表も例題が先
- home-links の 3 つの見出しと使い方へのリンク、ないページは「（準備中）」
- 入口が表でないこと・レベルの印・要約の 1 文目・問題集の閾値（`FIELD_SET_MIN`）、木の入口の木 DP、最短路の章の後の BFS、考察の入口の 1 行、題材別の入口の 1 行と印のないこと、注記の参照先がないときの知らせ

## 検査（作業ツリーで）

- `python3 tools/gen_site.py`（書いた 26 ファイル）→ `python3 tools/gen_site.py --check`：生成物は最新
- `python3 tools/check_pages.py`：エラー 0・警告 0（`--page problem-index,problem-sets,how-to-use` も 0）
- `python3 -m unittest discover -s tests/tools`：52 件 OK（2 件は Python-Markdown がないので飛ばす）。`.venv/bin/python` では 52 件 OK（飛ばしなし）
- `npx textlint docs/guide/problem-index.md docs/index.md docs/start/how-to-use.md docs/guide/problem-sets.md`：エラー 0、警告 5（どれも直す前からあるもの：index.md 3 行目の「に」の重なり、how-to-use 140・193 行目の「か」の重なり、221 行目の角かっこ、361 行目の文の長さ）。自分の文で出た 2 件（index.md の「か」、how-to-use の「が」）は直した
- `.venv/bin/mkdocs build --strict -q -d <作業用フォルダ>/site`：通る

## 見た目（作業用フォルダ）

ヘッドレスの Chrome（前の担当の `tools/cdp.mjs`。ビルドを http で配って開く。日本語は fc/fonts.conf で Windows のフォント）で撮った。画面写真は `/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/7a638398-7759-4637-95c7-6739e8d52414/scratchpad/fix/entry-points/entry/shots3/`。

- ホーム：390（全体）・1280・390 ダーク（全体）・1280 ダーク
- 入口：木 390・390 ダーク・1280・1280 ダーク（関連ページ）・390（関連ページ）、考察 390、題材別 390・1280 ダーク、グラフ 390（最短路の章の後）、数え上げ 390・1280、基本 390（関連ページ）
- 問題番号の索引：390・390（ABC の先頭）・390（ABC450〜）・390 ダーク・1280・1280 ダーク（問題集）。使い方の #lookup 390、問題集の表 390

レベルの印はダークモードでも読める（青は暗い背景用の色）。

## 提案（共有ファイル・担当外のファイル）

1. **order の並べ替え**（#58 の方針に合わせる。front matter）。どれも同じ分野の前提が後ろにならず、章の並びも変わらないことを確かめた（作業用の試算）。issue の例の proof-patterns を含む
   - basics/median-absolute 230 → 215（凸と三分探索の章で、基礎を水の三分探索の前に）
   - basics/lexicographic-greedy 280 → 255（貪欲の章で、区間スケジューリングの後・水の前に）
   - graph/bellman-ford 140 → 175（最短路の章で、水の応用 3 ページの後・差分制約の直前に）
   - graph/degree-sqrt 380 → 365（青を黄のオイラー路の前に）
   - tree/tree-centroid 110 → 135（木全体の形の章で、水 3 ページの後に）
   - ds/global-offset 60 → 24、ds/linked-list 70 → 27（標準コンテナの応用の章で、基礎を水の前に）
   - math/geometric-series-mod 80 → 65（mod の章で、基礎を水の前に）
   - math/prime-exponent-vector 170 → 135（素数と約数の章で、基礎を水の前に）
   - math/proof-patterns 250 → 205（GCD と合同式の章の末尾から、前提の gcd-lcm の直後に）
   - comb/counting-fix-order 90 → 75、comb/reflection-principle 150 → 135、comb/expectation-linear-equations 400 → 385（水・黄・青を上の帯の前に）
   - 判断の要るもの：dp「状態の形で分かれる DP」の区間 DP（青）2 ページを木 DP の後へ、thinking の reformulation・contribution（水）を基礎 7 ページの後へ。どちらも分野の説明（FIELD_DESCRIPTIONS の「列・区間・集合・桁・木」「言い換え・主客転倒…」）の順と合わせてあるので、並べ替えるなら説明の順も直す
2. **手引き**（planning/style-guide.md）：order の付け方（上の (1)〜(3)）を §2.1 か §5 に書く。今は gen_site の注記と how-to-use にだけある
3. **related**（front matter。頼まれた項目でないので直していない）：how-to-use・problem-sets・term-index の related に `problem-index` を足す
4. **roadmap 110 行目**：「問題ごとに使う手法のページを引くときは…『最近の ABC → ページ』の表を使う」に、本文に載せた問題は問題番号の索引でも引けることを足す（issue #6 の「色別ロードマップの本文の 1 文」）
5. **how-to-use #lookup の図と 3 段の 1 段目**（担当は表の行だけ）：入口に問題番号の索引を足す
6. **design.md**：§7 の横断ページの表に「問題番号の索引 | guide | 手書きの導入＋生成（本文に載せた全問題 → ページ（役割））」の行、§8.3 の生成部分の列に問題番号の索引とホームの目的別の入口を足す。**interfaces.md の版の行**に「2026-10-29 分野の入口の形・問題番号の索引・ホームの目的別の入口（#6・#7・#58）」を足す（origin/main が版の行を直しているので、衝突を避けて §8 の表だけ直した）
7. **catalog**：新しいページ problem-index は catalog（凍結）にない。記録するかはメインが決める

## 判断してほしい点

1. **題名**：指示の例「問題番号から引く」ではなく、用語の索引と並べて「問題番号の索引」にした（「問題番号から引く」は別名に入れた）。ホームの行が「問題番号の索引：本文に載せた問題の番号から…引く」と読める
2. **problem-sets の表の並びとリンク**：索引にそろえて、例題のページを先にし、例題の小見出し・一覧の節へ跳ぶようにした（表の列は同じ）。元の「ナビゲーションの順・ページの先頭へ」に戻すなら `b_problem_sets` の 2 行を戻す
3. **索引の長さ**：1251 行・390px で縦 81,239px（HTML 434KB）。ABC を別のページに分けるか、このままにするか
4. **小さい画面**：390×844 では 1 画面に 6 ページ以上（最悪 6）だが、360×640 では 4〜5。要約の 1 文目が長いページ（最大で題名と合わせて 123 字）を短くするなら、summary の 1 文目を短くする提案になる
5. **基本テクニックの「ほかの分野にある関連ページ」**：主題の kind が 9 個あるので 53 ページ（11 分野）と長い。kind の 3 つ目だけで当たるページ（8 件）を外す案もあるが、今は kind のどこにあってもよい（前の担当の決め方）のままにした

## マージの注意

- このブランチは origin/main より 6 コミット遅れている（#82：ページの部品・誤りの報告など）。origin/main は `docs/start/how-to-use.md`（#stub・#report・#page-anatomy・#progress の節と version の生成部分）と `planning/interfaces.md`（版の行・§2・§7）を直している。こちらは how-to-use の #structure・#lookup の表の行と生成部分（fields・version）、interfaces.md の §8 の 2 行だけなので、手書きの部分は別の場所だが、生成部分（version・fields）と `docs/llms.txt`・`overrides/assets/data/graph.json`・`docs/index/start.md` は衝突しうる。マージの後に `python3 tools/gen_site.py` を流し直せばそろう
- 新しいページのページ下部の「関連」（#56）は origin/main のテンプレートで出るので、マージ後に problem-index の related の表示を確かめるとよい

## 検証の指摘への対応

- 担当：entry の続き（検証の後の直し）。検証の報告は [verify-entry.md](verify-entry.md)。作業用フォルダは `/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/7a638398-7759-4637-95c7-6739e8d52414/scratchpad/fix/entry-points/fixup-entry`（以下「作業用」）
- 指摘は 1 件（#58）。正しいと判断し、案 (a) で直した。git は読むだけで、commit などはしていない

### 指摘 1：使い方 #structure の並びの説明（#58。直した）

- **指摘の確認**：front matter を数え、指摘のとおりだと確かめた。グラフの最短路の章は bellman-ford（140、青）→ shortest-path-dag（150、水）・extended-dijkstra（160、水）・time-dependent-dijkstra（170、水）→ difference-constraints（180、青、前提 bellman-ford）の順である。整数論・代数の GCD と合同式の章の末尾は multiplicative-order（240、黄）→ proof-patterns（250、基礎、前提 gcd-lcm）である。今の order では「同じ話題のページは続けて並ぶ」は成り立たない
- **(a) を選んだ理由**：(b) は 13 ページ（と判断の要る dp・thinking の並べ替え）の front matter の order を変えることで、この担当が直してよいファイルにない。(a) の文は order を並べ替えた後も成り立つので、メインが後で提案 1 を反映しても、この文を直し直す必要はない（(2) を書き足すかどうかを決めるだけでよい）
- **docs/start/how-to-use.md 95 行目**（#structure の手書きの文）
  - 前：「分野の中のページは、小さい章（chapter）に分かれて並ぶ。章の中では前提のページが先に来て、同じ話題のページ（基本形と、その応用・発展）は続けて並ぶ。レベルの順ではないので、話題の切れ目では低いレベルに戻ることもある。易しさは各ページのレベルの印で見分ける。」
  - 後：「分野の中のページは、小さい章（chapter）に分かれて並ぶ。章の中では、前提のページがそれを使うページより先に来る。レベルの順ではないので、高いレベルのページの後に低いレベルのページが来ることもある。易しさは各ページのレベルの印で見分ける。」
  - 検証の案の「前提のページが先に来る」は「章の先頭に基礎のページが来る」とも読める（proof-patterns のように基礎が末尾にある章もある）ので、「それを使うページより先に」と前後の関係を書いた。「後ろに低いレベル」も、何の後かが分かるように「高いレベルのページの後に」とした
  - front matter は変えていない（updated はもとから 2026-10-29）
- **tools/gen_site.py 651〜654 行目**（entrance の注記）：方針 (1)〜(3) はそのまま残し、「(1) は check_pages が見るが、(2)・(3) は検査しない。2026-10-29 の時点では (2)・(3) に合わない章が残るので、読者向けの説明（start/how-to-use #structure）には (1) とレベルの順でないことだけを書いた。order を (2)・(3) に合わせたら、説明に (2) を足してよい。」を足した。同じ話題を続けて置く方針は、この注記と提案 2（手引き）に残る
- **確かめたこと**
  - 新しい文の 2 つの事実を、作業用の `order_facts.py` で front matter から数えた（この作業ツリーと origin/main（a55ee9d）の両方で同じ結果）
    - 同じ章（chapter のない分野は分野の中）の前提が、それを使うページより後ろにある組：0（check_pages の警告「同じ分野の前提が後ろ」も 0）。入口とサイドバーはどちらも章の中を order の順に出すので、どちらで見ても成り立つ
    - 章の中で、前のページよりレベルの低いページが続く箇所：27 か所（23 章）。例：累積和といもす法の章の prefix-sum-2d（水）→ imos（基礎）、最短路の章の bellman-ford（青）→ shortest-path-dag（水）
  - `python3 tools/gen_site.py --check`（3.10）・`.venv/bin/python tools/gen_site.py --check`：生成物は最新（版 18d3adffb7f2 のまま。本文の文と注記は版の入力に入らない）。生成物が変わらないので、gen_site を書き込みでは流していない
  - `python3 tools/check_pages.py`（全 354 ページ）・`--page how-to-use`：エラー 0・警告 0
  - `python3 -m unittest discover -s tests/tools`：52 件 OK（2 件は Python-Markdown がないので飛ばす）。`.venv/bin/python` では 52 件 OK
  - `npx textlint docs/start/how-to-use.md`：エラー 0、警告 4（140・193 行目の「か」の重なり、221 行目の角かっこ、361 行目の文の長さ。どれも直す前からある。95 行目には出ない）
  - `.venv/bin/mkdocs build --strict -q -d <作業用>/site`：通る。ビルドの前後で `git status` は変わらない
  - 見た目：ヘッドレスの Chrome（entry の `cdp.mjs`。ビルドを http で配って開く）で、#structure の段落を 390・390 ダーク・1280・1280 ダークで撮った（`<作業用>/shots/howto-structure-*.png`）。HTML の文が新しい文と一致し、横にはみ出さない（scrollWidth が画面の幅と同じ）
  - origin/main は how-to-use の 95 行目の近くを変えていない（近いのは生成部分 fields の題材別の行の 10 → 11 だけ）ので、この直しでマージの衝突は増えない
- **残った点・提案**
  - メインが提案 1（order の並べ替え）を反映したら、95 行目に「同じ話題のページ（基本形と、その応用・発展）は続けて並ぶ」を足せる。足す前に、全章が (2) に合うかを確かめる。検証の指摘のとおり、木の「木全体の形」の章では tree-isomorphism（140、発展、前提 tree-diameter）が tree-diameter（100）と離れている。木の同型判定を直径とは別の話題（中心を根にして同型を判定する話題）とみれば、提案 1 の tree-centroid 110 → 135 を反映した後の並び（直径 → 辺の寄与 → 構築 → 重心 → 同型）は (3) に合う。同じ話題とみるなら、tree-isomorphism を 105 にする案になる（判断が要る）
