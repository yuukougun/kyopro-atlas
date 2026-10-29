# verify-tables の報告（#55 の表の部分：tables の直しの検証）

tables の担当が直したもの（`overrides/assets/css/kp.css` の追記と、表を組み直した 9 ページ）を、書いた担当とは別に確かめた。担当の報告は [tables.md](tables.md)。ファイルは直していない。

- 作業用フォルダ：`/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/7a638398-7759-4637-95c7-6739e8d52414/scratchpad/fix/mobile-layout/verify-tables`（以下 `<V>`）。画像は `<V>/shots/`、測った結果は `<V>/*.json`、スクリプトは `<V>/scripts/`
- ビルド（どれも `mkdocs build --strict` で警告 0・終了コード 0）
  - `site-before`：作業ツリーの HEAD（af7ee6c）。直す前
  - `site-wt`：作業ツリーそのまま（display-math の担当が直している comb・math のページも入る）
  - `site-main`：main（c8924bb。feat/progress と feat/code-and-library を含む）。直す前の main
  - `site-merged`：main に tables の差分（kp.css と 9 ページ）だけを当てたもの。kp.css の節は main の末尾（feat/progress の節）の後ろに入る。マージした後の状態に近い
- 撮影と計測：`python3 -m http.server`（127.0.0.1:37461）で配り、chrome-headless-shell 146 を CDP で動かした。幅 390px（ライト・ダーク）・360・320・1280。main と重ねたものは、タッチ（`pointer: coarse`）を有効にして測った（ロードマップの「理解した」の欄が 44px になる）

## #55：直しが要る（3 点）

表の部分の「完了の条件」は満たしている。組み直した表の中身も元と同じで、1280px とロードマップの # の列にも問題はない。ただし、kp.css の `min-width: 0` で、表の列が 1 字の幅まで縮むようになった。Issue に挙げたロードマップの表を含め、サイト全体の 59 ページで縦に 1 字ずつ積まれる列が出る。main をマージした後の guide/library-design の表も崩れる（下の「直しが要る点」）。

### 完了の条件

| 条件 | 結果 |
| --- | --- |
| 390px で、はみ出す表と別行の数式に、続きがあることを示す手がかりが出る | 満たす。下の「手がかり」 |
| 上に挙げた表で、行き先のリンクと要の列が横に送らずに読める | 満たす。9 ページの表 26 個とロードマップの表 13 個は、390px・360px でどれもはみ出さない（直す前は 18 個と 11 個がはみ出していた）。320px では segment-tree-monoids の型の表だけが 29px はみ出す（影は出る。担当の報告どおり）。ただしロードマップの頻度の列は 1 字ずつ縦に積まれる（直しが要る点 1） |
| 手引き §8 が改まっている | この担当の範囲外（メインが反映する）。まだ改まっていないので、Issue を閉じるには §8 と display-math の直しが要る |

### 組み直した表の中身（元と同じ）

`<V>/scripts/tablecmp.py` で、HEAD の表と今の表を行ごとに突き合わせた。

- 列をまとめた 9 個の表：まとめた列は、元の 2 つのセルを区切り（「 → 」「）→ 」「：」「 / 」）でつないだものと一致する。ほかの列と行の並びは元のまま
  - dp-speedup-overview の 4 個（どれも「道具」と「ページ」）、graph-modeling の 2 個、lazy-segment-tree の区間和の表、lazy-segment-tree-patterns・segment-tree-monoids の型の表、segment-tree-binary-search の条件の表
  - 早見表で道具の名前を落とした 3 行（単調スタック・Alien DP・Slope Trick）は、どれもリンクの文字が落とした名前と同じで、失われた情報はない
- 縦横を入れ替えた 2 個（two-pointers#two-types、bit-dp#complexity）：入れ替える前の表の転置と一致する
- 列の順を入れ替えた 1 個（complexity-estimation#constraint-table）：列の並べ替えだけで、行の値は同じ
- 表の外の本文の変更は graph-modeling の `updated`（2026-10-22 → 2026-10-29）だけ。ほかの 8 ページは前から 2026-10-29
- 本文が列の名前に触れている箇所（「例題の列は…」など）は、残った列を指していて食い違いはない

### 手がかり（影）

- 別行の数式（390px）：lazy-segment-tree-patterns の 1 本目は、送る前は右端だけ（端から 16px の明るさ 255 → 184）、真ん中で両端、端まで送ると左端だけに影が出る。ダークでも右端が暗くなる（segment-tree-monoids、33 → 10 前後）。`<V>/shots/wt-390-lstp-math0{,-mid,-end}.png`・`wt-390d-stm-math0{,-end}.png`
- 表：segment-tree-monoids の型の表（320px）は、送る前は右端に影、端まで送ると右の影が消えて左に出る（`wt-320-stm-pattern{,-end}.png`）。main と重ねた guide/library-design・ds/advanced-ds-catalog のはみ出す表にも右端の影が出る
- はみ出さない表と数式には影が出ない（9 ページの表の端の画素は地の色のまま）
- details の中の数式（dp/digit-dp-advanced、390px）：直した後も囲みの左右の枠線が途切れず、はみ出す数式の右端に影が出る（`merged-390-digitdp-details.png`・`merged-390d-digitdp-details.png`。直す前は `main-390-digitdp-details.png`）
- 表と別行の数式の置き場所を全ページで数えた（`<V>/scripts/ancestors.py`）：表 771 個はすべて本文の直下、別行の数式 632 個は本文の直下 615・details の中 16・リストの中 1。地の色と違う背景の箱（`.kp-problem` など）や blockquote の中にはないので、影の覆い（地の色）が枠線や背景を隠す箇所はない

### 1280px

9 ページとロードマップの表はどれもはみ出さず、ページ全体の横のずれも 0。狭い画面の規則は 44.984375em 以下だけに効き、1280px では Material の既定（min-width 5rem・余白 1.25em）のまま。組み直した表（早見表・graph-modeling・two-pointers・segment-tree-monoids（ダーク）など）は 3 列でそのまま読める（`<V>/shots/wt-1280*.png`）。

### ロードマップの # の列（feat/progress の規則とぶつからないか）

main と重ねた `site-merged` で、ロードマップを 390px・360px、タッチを有効にして見た。

- 色ごとの列の表には progress.js が `data-kp-order` を付け、# の列にチェック欄が入る。# の列は main の規則（詳細度 (0,3,2)）が勝ち、左右の余白 0.9em・0.5em、幅 62px。上下の余白はこの直しの 0.75em で、ほかの列とそろう
- 14 個の表（JS が出す集計の表を含む）は 390px・360px でどれもはみ出さない。チェック欄と番号は重ならない（`merged-390t-roadmap-cyan-top.png`・`merged-390td-roadmap-blue-top.png`）
- kp.css は両方のブランチとも末尾に追記しているので、git のマージでは末尾がぶつかる。両方の節を残せばよい（担当の報告どおり）

### 検査

- `python3 tools/check_pages.py --page <id>`：9 ページともエラー 0・警告 0
- `python3 tools/fix_problems.py --check --page <id>`：9 ページとも直すべき行 0
- `npx textlint`（9 ページ）：エラー 0。警告 167 件は直す前と同じ（two-pointers と bit-dp の行番号が 2〜3 行ずれただけ）
- `python3 tools/gen_site.py --check`：HEAD に tables の差分だけを当てると、`docs/llms.txt`・`overrides/assets/data/graph.json`・`docs/start/how-to-use.md` の 3 つが古くなる。作業用フォルダで作り直して比べると、違いは版の値（3571a7ed10f2 → 23db1c4666f2）だけで、メインが作り直せば済む

### ほかの箇所への影響（サイト全体、390px）

main と、main に直しを当てたもの（`site-merged`）を、全 422 ページで測った（`<V>/sw2-*.json`・`<V>/sw3-*.json`。タッチを有効）。

| | main（直す前） | 直した後 |
| --- | --- | --- |
| はみ出す表 | 158 個 | 4 個（ds/advanced-ds-catalog#table 19px、math/miller-rabin#deterministic-bases 94px、guide/library-design#acl-names 105px・#verify-table 102px） |
| 最後の列がまるごと画面の外にある表 | 28 個（af7ee6c で測った値） | 0 個 |
| 1 字の幅しかない列（中身の幅が 2em 未満で、3 字以上の文字が入る列） | 0 個 | 251 個（59 ページ） |

1 字の幅の列は、Material の `min-width: 5rem` を 0 にしたことで出る。中身に折り返せない語（コード・数式・長いリンク）のある列が幅を取り、残りの短い日本語の列が 1 字の幅まで縮む。多いのは lists の「レベル」（164 列。見出しの「レベル」が 3 行になる）・「ページ」・「diff」で、読みにくさがはっきり出るのは次の表である。

- guide/roadmap の色ごとの列の表（下の 1）
- guide/library-design#acl-names（下の 2。main にだけある表）
- graph/k-shortest-paths#comparison：「数える対象」の列が 33px で、見出しと「ウォーク」「単純パス」が 1 字ずつ縦に並ぶ（`merged-390-kshortest-comparison.png`）
- dp/subset-sum#three-forms（「形」の列 30px）、comb/binomial-coefficient#meanings（「見方」36px）、start/how-to-use#structure（「ページ」35px）など

## 直しが要る点

### 1. 列の最小の幅を 0 にすると、短い日本語の列が 1 字ずつ縦に積まれる（ロードマップを含む）

- ファイル：`overrides/assets/css/kp.css` 646 行（`.md-typeset table:not([class]) th { min-width: 0; }`）
- 理由：Issue に挙げた guide/roadmap の色ごとの列の表（水・青・黄・発展）で、390px の頻度の列が 37〜40px になり、「余裕があれば」が 6 行、「準必修」が 3 行、「必修」が 2 行に 1 字ずつ縦に積まれる。ページの名前が 1 行の行も 143px の高さになる（`merged-390t-roadmap-cyan-yoyu.png`）。Issue の背景の「1 行が縦に長くなる」が、ページの列ではなく頻度・分野の列で残る。ロードマップの最近 30 回の表の「問題数」、サイト全体の 251 列も同じ形である
- 直し方の案：狭い画面の `min-width` を 0 ではなく `4em` にする（列の中身に 2〜3 字入る幅）。`<V>/scripts/sitewide4.mjs` で、下の 2 の規則と合わせて main と重ねた 422 ページに当てて測った
  - 1 字の幅の列：251 → 0
  - Issue の表（9 ページとロードマップ）：390px・360px でどれもはみ出さない
  - ロードマップの色ごとの列の表の高さ：390px で 0〜30% 減る（頻度の列は 56〜67px になり、「準必修」が 1 行、「余裕があれば」が 2 行。`cand-390t-roadmap-cyan-yoyu.png`）
  - 代わりに、列の多い値の表など 4 個がはみ出す：comb/grundy-number#definition 207px、string/kmp#failure-function 54px、math/proof-patterns#rearrangement 17px、dp/subset-sum#three-forms 10px（直す前の main では 744・444・344・121px。影は出る）
  - ロードマップだけを直すなら、main をマージした後に `.md-typeset table[data-kp-order] th { min-width: 4em; }` を狭い画面の節に足す形でもよい（390px・360px で収まり、高さは上と同じだけ減る）。ただし k-shortest-paths などの 1 字の列は残る

### 2. main をマージすると、guide/library-design の 2 つの表が崩れる

- ファイル：`overrides/assets/css/kp.css` 645〜653 行（狭い画面の節）。崩れる表は main の `docs/guide/library-design.md` 88 行（#acl-names）と 219 行（#verify-table）。どちらもこの作業ツリーにはまだない
- 理由：「確認の問題」「Library Checker の問題」の列に `dynamic_graph_vertex_add_component_sum` のような折り返せない問題名のリンクがあり、その列が 275〜340px を取る。`min-width: 0` で残りの列が最小まで縮み、#acl-names では「この教材の自作」の列が 28px になって、`UnionFind` などのコードが 1 字ずつ縦に並ぶ（行の高さは最大 614px、表の高さは 1720 → 3396px）。それでも表は 105px はみ出したまま（`merged-390-libdesign-acl-top.png`。直す前は `main-390-libdesign-acl-top.png`）。#verify-table も 102px はみ出したまま、分野の列が 41px になる
- 直し方の案：狭い画面の節に `.md-typeset table:not([class]) a[href^="https://judge.yosupo.jp/"] { overflow-wrap: anywhere; }` を足す（問題名は長い 1 語なので、`.md-typeset .kp-links__verify a` と同じく途中で折り返す）。試すと #acl-names は 105px → 0（表の高さ 3396 → 1452px）、#verify-table は 102px → 0 になり、ほかのページの表は変わらない。これだけだと自作の列は 41px なので、1 の `4em` と合わせる（自作の列は 58px）。表を 3 列に組み直す（確認の問題は #verify-table にもある）なら、ページの持ち主の直しになる

### 3. ds/advanced-ds-catalog の一覧の表で、「何ができるか」の列が 3 字ずつに縮む

- ファイル：`docs/ds/advanced-ds-catalog.md` 96 行（#table。名前・何ができるか・計算量・代わりになる手の 4 列）
- 理由：計算量と代わりになる手の列の折り返せない数式で、表の中身の最小の幅の和が 390px を超える。`min-width: 0` で全部の列が最小まで縮み、「何ができるか」の列が 52px（1 行に 2〜3 字）になる。表の高さは 1627 → 3232px と 2 倍になり、それでも 19px はみ出す（`merged-390-advds-table-top.png`。直す前は 100px で 1 行に 5 字、はみ出しは 117px：`main-390-advds-table-top.png`）。この列は表の中心で、1 の `4em` でも変わらない（すでに 52px ある）
- 直し方の案：3 列に組み直す。たとえば segment-tree-monoids と同じまとめ方で「名前：何ができるか ｜ 計算量 ｜ 代わりになる手」にする。担当外のページなので、直す人はメインが決める

## 気づいた点（直さなくてもよい）

- segment-tree-monoids の型の表は、390px で 1 列目（区間の何を求めるか：載せる要約）が 83px になり、1 行に 5 字ほどで折り返す。表の高さは 883 → 1247px。単位元の列は読める
- complexity-estimation#constraint-table は、390px で 1 列目（制約の目安）が 60px になり、`$N \le 2 \times 10^5$` が 3 行に分かれる。引くときの手がかりの列なので、1 の `4em` を入れても 64px 前後のまま。気になるなら演算回数の列を計算量の列に入れて 3 列にする
- dp-speedup-overview の早見表は、390px で例題の列が 72px になり、「ABC179 D」が「ABC179」と「D」に分かれる。読める
- ロードマップの最近 30 回の表は、390px で「問題数」の列が 30px になり、見出しが「問／題／数」と縦に並ぶ（1 の直しで解消する）
- graph/degree-sqrt（4px）と dp/knapsack-undo（9px）は、直す前から 390px でページ全体が横にずれる。この直しとは関係がない
- 担当の報告の「サイト全体で 390px ではみ出す表が 3 個」は作業ツリーで測った値で、main をマージすると guide/library-design の #acl-names が加わって 4 個になる（直しが要る点 2）
