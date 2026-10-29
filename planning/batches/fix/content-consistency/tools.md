# content-consistency の第 1 段：検査の道具・規則・テンプレート・台帳（担当 tools）

- 担当の Issue：#68（平文のまま出る数式と法の文字）・#69（節の並び）・#77（1 次関数の表記）・#91（nav_title のページの見出し）
- 作業ツリー：kyopro-atlas-wt/content-consistency（ブランチ fix/content-consistency）。2026-10-29
- 第 1 段なので docs/ のページは直していない。新しい検査は今のページに指摘を出す（第 2 段で分野ごとの担当が直す）

## 直したファイル

| ファイル | 中身 |
| --- | --- |
| tools/check_pages.py | 新しい検査 7 種（エラー 1・警告 6）と、その部品（`text_runs`・`run_math`・`split_row`・`table_head`・`raw_math_tokens`・`section_key`）。`MD_MATH_RE` に `re.DOTALL` を足した（Python-Markdown と同じ。1 行ずつの既存の検査は変わらない）。冒頭の説明に新しい検査を足した |
| tests/tools/test_check_writing.py（新規） | 新しい検査の試験 17 個。Python-Markdown があれば、本物（mkdocs.yml の拡張）と乱択の文書 600 個で `$` の数え方を突き合わせる |
| prh.yml | 一次関数→1 次関数・一次式→1 次式・二次関数→2 次関数・二次式→2 次式・1 次独立/1 次従属→一次独立/一次従属・ヴァンデルモンド/ファンデルモンド→Vandermonde（「…の等式」は「Vandermonde の恒等式」）。specs 付き |
| overrides/main.html | nav_title を持つページの h1 を front matter の title にする（#91） |
| data/problems.yaml | summary・approach の平文化 25 項目（上の段 18・alternatives の中 7） |
| planning/style-guide.md | §4（節の並び）・§6（`$` の空白・平文の欄・本文の数式・法の文字）・§7（和文と数式の空白・次数と Vandermonde・別名）・§10（方針の折りたたみの題・要約は平文）・付録 A（Vandermonde の恒等式） |
| planning/decisions.md | 2026-10-29 の節の表の末尾に、方針 1〜6 を 1 行ずつ（「メインの判断」） |
| tools/README.md | 一覧の check_pages の行と、新しい検査の表・数え方・まねていないもの・生成ページの扱い |

## A. check_pages の新しい検査

### 検査の中身

| 重さ | 種類 | 見るもの | 方針 |
| --- | --- | --- | --- |
| エラー | 数式にならずに残る $ | arithmatex の smart_dollar（`MD_MATH_RE` = RE_SMART_DOLLAR_INLINE・RE_BRACKET_INLINE）で対にならない `$`（奇数個の `\` の後の `\$` は数えない）と、前後の行と同じ段落に入った別行の数式の `$$`。1 行 1 件で、`$` の数と前後の文字を出す | 5 |
| 警告 | 要点・題の素の数式 | 要点の囲みの中と、`!!!`・`???`・`???+`（とタブ `===`）の題の、数式・コード・リンクの行き先の外にある、英数字に挟まれた `^`、1 字の英字の後の `_`、`_{`・`^{`、エスケープした `\[`、2 字以上の英字の命令（`\le`）。`&#94;`（md_text が書く `^`）と `\_` は戻してから見る | 3 |
| 警告 | 和文に接した数式 | `$…$`（と `\(…\)`）の直前・直後が和文の字（ひらがな・カタカナ（「・」U+30FB を除く。「ー」は含む）・漢字・々〆） | 5 |
| 警告 | 平文の欄の TeX の記号 | front matter の title・nav_title・summary・complexity・signs の text・sections の title、本文の問題の行の要約（コードの外）、台帳の summary・approach（alternatives の中も）の `_{`・`^{`・2 字以上の英字の命令・`$`。aliases は見ない | 2 |
| 警告 | 節の並び | 定型の節（`STANDARD_SECTIONS` の見出しと anchor。上位の手法へのつながり `next-steps` は基礎の technique でだけ定型）が pitfalls → next-steps → resources → examples → practice → challenge → quiz → comparison → references の相対順でない。technique は中身の節（定型でない h2）が最初の定型の節より後ろにあるものも。1 ページ 1 件で、今の順・手引きの順・後ろにある中身の節を出す | 1 |
| 警告 | 方針の折りたたみの題 | 練習問題・力試しの節の中の `???` の題で「方針」を含むものが「練習の方針」「力試しの方針」（後ろに「（…）」を付けてよい）でない。直し方の文に「（ABC195 F）」などを写して出す | 1 |
| 警告 | 法を表す mod の文字 | 数式（インラインと別行）の中の `\mathrm{mod}`・`\text{mod}`（`\textrm` なども）・`\operatorname{mod}`。大文字の MOD も当てた（下の質問 4）。`\bmod`・`\pmod`・`\mathrm{mode}` は当たらない。1 行 1 件 | 4 |

細かい決め方：

- 和文の字の隣の判定は arithmatex が切り出した数式の範囲で行う（`$a $`・`$$` のような数式にならないものは見ない）
- 方針 3 の「本文の素の数式」は、要点の囲みと題だけを見る（本文の地の文の `10^6` は、ページの説明の中で記号として書くこともあり、誤検出を避けるため見ていない）
- 要点・題の `_` は、`lower_bound`・`pb_ds`・`Min_25`・`unordered_map` のような 2 字以上の語の後の `_` を名前とみなして当てない（1 字の英字の後だけ。`y_max`・`r_v` は当たる）
- 平文の欄の「逆斜線の英字の命令」は 2 字以上（`'\n'` のような C++ のエスケープを当てないため。cpp/cpp-io の sections の title にある）
- 節の並びで、§17-4 の「上位の手法へのつながりと同じ役の中身の節」（modint の `connections`・mod-pow の `building-block`・global-offset の `to-lazy-segment-tree`）は、基礎の technique では next-steps と同じ位置の定型として扱った（`NEXT_STEPS_EQUIVALENTS`。手引き §4 にも書いた）。roadmap の `practice`（§17-3 の例外）は中身の節
- 定型の節が anchor を持たない見出し（「## 例題」だけ）でも、見出しの文字から定型と見る（今のページにはない）

### 数式にならずに残る $ の数え方と確かめたこと

段落の中では数式が改行をまたげる（Python-Markdown は inline の処理を段落ごとにかける）ので、1 行ずつではなく、Python-Markdown が inline の処理をかける塊（段落・箇条書きの項目・見出し・表のセル・囲みの題）を `text_runs` で切り出して数える。塊の切り出しは Python-Markdown 3.11 のブロックの処理のまね（tools/check_pages.py の「本文の inline の塊」の注記）：

- 空行・行頭（字下げ 3 字まで）のコメントと `<div>` の行でブロックが分かれる。囲み・折りたたみ・タブの題（優先度 105）と見出し（70）・引用（20）は前の行に続けて書いても分かれる
- 囲みの中身は字下げが浅くなれば終わる。箇条書きの項目は空行がなければ浅い行も続き（lazy continuation）。箇条書きのブロックの中では印の行が新しい項目、段落の次の行の印は段落の続き。囲みの中の項目の続きのブロック（空行の後）は厳しく閉じる（admonition・details の parse_content）
- 別行の数式（79.9）はブロックの始まり（箇条書きの印・引用の `>` の後も）が `$$` で、ブロック全体か見出し・引用の前で分けた前の部分が `$$…$$`（RE_DOLLAR_BLOCK）のときだけ。フェンスは置き換えの印になって同じブロックに残るので、フェンスの直後の `$$` も段落の文字になる
- 表（75）は 1 行目と 2 行目が見出しと区切りのとき（TableProcessor.test と _split_row のまね）。字下げ 4 字以上でブロックが始まればコード

確かめたこと：

1. 本物との突き合わせ（全ページ）：作業用フォルダのスクリプトで、docs の Markdown 423 枚（生成ページ 66 枚を含む）の本文を本物の Python-Markdown（mkdocs.yml の拡張と設定）で HTML にし、地の文（code・pre・arithmatex の外）に残る `$` を数えた。56 個・13 ページ（生成ページは 0）で、検査の数え方（357 枚）とページごとに完全に一致した
2. render_pages の 25 件（メインの `cc/render-main-errors.json` の leaked-markup。13 ページ）は、検査のエラー 21 件（13 ページ）がすべて含む（下の表）。render_pages の 1 件は地の文の 1 つの文字の塊（text node）で、検査は 1 行 1 件なので数が違う。ほかに出る件はない
3. 乱択の突き合わせ：段落・複数行の段落・箇条書き（入れ子・続きの行・続きの段落）・囲み（入れ子）・見出し・表・`$$`（空行あり・なし）・フェンス・コメント・引用・`<div markdown>` を組み合わせた文書で、本物の地の文の `$` の数（`\$` を含む）と検査の数＋`\$` の数を比べた。食い違いを縮めた最小の文書で規則を直していき、最後の版で 2 種の生成器の文書 7 万 2 千件を流した。残った食い違いは 14 件（0.02%）で、どれも乱択の記号が行頭に「```」を作った閉じないフェンス（`fence_spans` が最後までコードとみなす。既存の作り）の文書だった。縮めた文書ではほかに「本文の 1 行目が空白だけ」（Python-Markdown の前処理が 1 行目だけ空白の行を空行にしない）も出た。どちらも今のページにない。試験 test_check_writing.py は、行頭の「```」を作らない生成器で 600 件（種 20261029）を本物と突き合わせる
4. 生成ページ（type: generated。docs/<field>/index.md・docs/lists/・docs/index/ の 66 枚）にも新しい検査をすべて流して 0 件。要約は md_text が `\$`・`\_` にエスケープして写すので `$` は残らず、平文の欄は元の front matter で見られるので、生成ページは対象にしない（ほかの検査と同じく load_docs が外す）

| ページ | 検査のエラー（行） | render_pages の件数 |
| --- | --- | --- |
| basics/lexicographic-greedy | 159・161・163 | 3 |
| basics/run-length-encoding | 51 | 1 |
| comb/inclusion-exclusion | 236 | 1 |
| comb/probability-dp | 149 | 1 |
| dp/dp-phase | 158 | 1 |
| ds/stack-techniques | 90・201 | 2 |
| graph/min-cost-flow | 179 | 1 |
| math/euler-phi | 63・65（段落に続く `$$` の開きと閉じ） | 1 |
| patterns/subsequence-and-substring | 240 | 1 |
| string/string-basics | 102・121・157 | 8 |
| string/suffix-array | 65・198 | 2 |
| thinking/contribution | 97・216 | 2 |
| tree/euler-tour | 248 | 1 |

### 今のページでの件数

全 356 ページと docs/index.md・台帳で流した（2026-10-29。エラー 21・警告 336。既存の検査の指摘は 0 のまま）。

| 検査 | basics | thinking | dp | graph | tree | ds | math | comb | string | geometry | misc | patterns | cpp | guide | 計 | ページ |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 数式にならずに残る $（エラー） | 4 | 2 | 1 | 1 | 1 | 2 | 2 | 2 | 5 | | | 1 | | | 21 | 13 |
| 要点・題の素の数式 | | 1 | 4 | 8 | 3 | 6 | 11 | 1 | 4 | | 3 | 1 | | 3 | 45 | 35 |
| 和文に接した数式 | | | 1 | | | 4 | | | | | | | | | 5 | 2 |
| 平文の欄の TeX の記号 | 7 | | 8 | 3 | 2 | 1 | 29 | 9 | 1 | | | | | | 60 | 38 |
| 節の並び | 19 | 3 | 11 | 16 | 6 | 16 | 16 | 10 | 2 | 1 | | | 1 | | 101 | 101 |
| 方針の折りたたみの題 | 2 | | 23 | 14 | 12 | 26 | 11 | 8 | 5 | 2 | 4 | | | | 107 | 61 |
| 法を表す mod の文字 | | 3 | 2 | | | | 3 | 8 | | | | | | 2 | 18 | 11 |

第 2 段の下書き（`cc/stage2-draft.md`）の組での件数：

| 検査 | A（basics・thinking・dp・graph・tree） | B（ds・math・comb） | C（string・geometry・misc・patterns・cpp・guide・start） |
| --- | --- | --- | --- |
| 数式にならずに残る $ | 9 | 6 | 6 |
| 要点・題の素の数式 | 16 | 18 | 11（うち guide/method-comparison 2・guide/reverse-index-constraints 1） |
| 和文に接した数式 | 1 | 4 | 0 |
| 平文の欄の TeX の記号 | 20 | 39 | 1 |
| 節の並び | 55 | 42 | 4 |
| 方針の折りたたみの題 | 51 | 45 | 11 |
| 法を表す mod の文字 | 5 | 11 | 2（guide/cheatsheet） |

件数の多い検査の誤検出の確かめ：

- **方針の折りたたみの題（107）**：題の内訳は、練習問題の節の「方針」53・「方針（ABC142 E）」などの形 8・「練習問題の方針」2、力試しの節の「方針」40・「方針（…）」4。どれも練習問題・力試しの h2 の範囲の `???` で、方針 1 の最後の項のとおり直すもの。例題の節の「方針」（thinking の 23 など）と、本文の確認問題の題（「確認問題：運に頼る方針」）は当てていない
- **節の並び（101）**：全件の並びを読んだ。内訳は technique 基礎で定型の順だけ 37・中身の節だけ 4・両方 2、technique 水・青・黄で定型の順だけ 33・中身の節だけ 11・両方 5、overview 4・thinking 3・cpp 1・hub 1。定型の順のずれはほとんどが「使い分け（と確認問題）を例題の前に置いた」形と、基礎の「上位の手法へのつながりを落とし穴の前に置いた」形。誤検出はない（ただし下の質問 1〜3 の扱いはメインの判断が要る）。global-offset（`to-lazy-segment-tree`）は §17-4 の扱いで当たらない
- **平文の欄（60）**：問題の行の要約 27・front matter 33（signs 19・summary 10・complexity 4）。どれも `_{`・`^{`・`$`・`\times` などの TeX の記号を含む本物。台帳の 18＋7 項目は D で直したので 0
- **要点・題の素の数式（45）**：要点 15・題 30。#68 が挙げた要点の 12 ページ（fix-variable・extended-dijkstra・modular-shortest-path・bipartite-graph・functional-graph・aho-corasick・offline-queries・divisor-inclusion-exclusion・linear-recurrence-fast・parsing・interval・inline-dp）と題の 2 例（floor-sum の「Σ_{i=1}^{N} …」、exponent-mod の「3^(10^18) mod 7」）をすべて含む。名前の `_`（lower_bound・pb_ds・Min_25・unordered_map・is_root など）を当てないことを全件で確かめた

検査ではとらえない #68 の残り（第 2 段で手で直す。メインの下書きにもある）：ds/offline-queries の要点の閉区間「[l, r]」（本文の半開区間にそろえる）、comb/coupon-collector の「法 $P = 998244353$」（同じページで確率に $P(A)$ を使う）。

## B. prh.yml の規則と textlint

足した規則（どれも specs で試験し、作業用フォルダの見本で `--fix` の結果を確かめた）：

| 直す表記 | 正規形 | 備考 |
| --- | --- | --- |
| 一次関数・一次式・二次関数・二次式 | 1 次関数・1 次式・2 次関数・2 次式 | 一次合同式・一次方程式は当たらない（「一次式」を含まない） |
| 1 次独立・1 次従属（全角の１、空白なしも） | 一次独立・一次従属 | |
| ヴァンデルモンドの等式・…の恒等式（ファ・バも） | Vandermonde の恒等式 | |
| ヴァンデルモンド・ファンデルモンド・バンデルモンド | Vandermonde | 後ろに語が続けば空白を足す（Vandermonde 行列・Vandermonde の行列式） |

- 空白のない「1次関数」「1次元」は、既存の「1 次元」と同じく prh ではなく ja-space-between-half-and-full-width のエラーになり、`--fix` で「1 次関数」になる。なお「1次関数」（空白なし）には preset の arabic-kanji-numbers が「一次関数」を勧める警告も出すが、空白を入れた「1 次関数」「2 次式」には出ないことを確かめた（方針とぶつからない）
- 別名の行（textlint-disable の中）と front matter（aliases を含む）は textlint が見ないので当たらない（全 60 件が本文の行で、front matter の行は 0 件）
- 4 ページの写しで `--fix` を流し、エラーが 0 になり、新しい警告が増えないことを確かめた（文の長さの字数が 2 字変わるだけ）

`npx textlint $(python3 tools/textlint_targets.py)`（357 ファイル）の結果：エラー 60 件で、すべて新しい規則（今の main ではエラー 0 なので、増えたのはこの 60 件）。一次関数 49・一次式 9・1 次独立 1・ヴァンデルモンド 1、18 ファイル：

| ページ | 件数 | 規則 |
| --- | --- | --- |
| basics/exchange-argument | 3 | 一次関数 |
| comb/lattice-paths | 1 | 1 次独立（92 行） |
| dp/cht | 3 | 一次関数 |
| dp/dp-speedup-overview | 2 | 一次関数 1・一次式 1 |
| dp/dynamic-dp | 3 | 一次関数 |
| dp/exchange-argument-dp | 4 | 一次関数 |
| ds/advanced-ds-catalog | 2 | 一次関数 |
| ds/lazy-segment-tree-patterns | 5 | 一次関数 |
| ds/monotonic-stack | 1 | 一次関数 |
| ds/segment-tree-monoids | 12 | 一次関数 |
| ds/segment-tree-on-values | 1 | 一次関数 |
| ds/sparse-table | 1 | 一次関数 |
| guide/glossary | 1 | 一次関数（473 行。用語集はメインのファイル） |
| math/floor-sum | 5 | 一次式 |
| math/gaussian-elimination | 3 | 一次式 |
| math/lagrange-interpolation | 1 | ヴァンデルモンド（147 行「ヴァンデルモンドの行列式」→「Vandermonde の行列式」） |
| math/matrix-power | 1 | 一次関数 |
| tree/static-top-tree | 11 | 一次関数 |

textlint が見ない所の同じ表記（第 2 段・メインへ。下の提案 3・質問 5）：front matter に 10 か所（dp/cht の summary、dp/dp-speedup-overview の summary、dp/exchange-argument-dp の signs[2]、ds/segment-tree-monoids の summary・signs[3]・sections[2] の title、math/floor-sum の summary・sections[6] の title、math/gaussian-elimination の signs[4]、math/online-convolution の signs[0]）、台帳に 6 か所（abc228_h・abc289_g の approach、abc366_f の summary と alternatives の summary・approach、arc008_4 の summary）。

ほかの「漢数字＋次」の語（本文・別名・front matter を含む数。質問 5）：一次方程式 27（14 ファイル）と 1 次方程式 13（7 ファイル）が混ざっている。一次合同式 72（20）・一次不定方程式 17（6）・一次漸化式 5（3）は算用数字の形がない。線形代数の語では「1 次結合」が 1 か所ある（一次独立と同じ扱いなら一次結合）。二次予選（コンテストの段の名前）は次数ではないので対象外。

## C. #91 nav_title のページの見出し

- Material と Zensical の partials/content.html は、本文に h1 がなければ `<h1>{{ page.title }}</h1>` を出し、page.title は nav に書いた名前（nav_title）になる。overrides/main.html の content の段で、super() の出力のうち `<h1>` + page.title + `</h1>` を `<h1>` + front matter の title（`| e`）+ `</h1>` に置き換えた（nav_title があり title と違うページだけ）。page.title は Material では生のまま、Zensical ではエスケープして出るので、両方の形を置き換える。`~`・`| e`・`| replace` だけを使う（MiniJinja で読める）
- ブラウザのタブ（`<title>`）・ヘッダの題（md-header__topic）・検索の結果の題は、テーマ（base.html・header.html・search プラグイン）が page.meta.title を先に使うので、元から正式な題名だった（main のビルドの search_index.json でも確かめた）。サイドバー・前後のページ・パンくずは nav の短い名前のまま
- 確かめたこと：作業用フォルダへのビルド（`.venv/bin/mkdocs build -d <作業用フォルダ>/site`）で、3 ページの h1 が「構造化束縛と pair・tuple・optional」「整数のオーバーフローと __int128」「Suffix Automaton と発展の文字列アルゴリズム」になり、サイドバーの今のページの項目は「構造化束縛と pair・tuple」「オーバーフローと __int128」「Suffix Automaton など」のまま。メインが同じ commit から作ったビルド（`cc/site-main`）と全ページの HTML を比べ、違うのはこの 3 ページの h1 の 1 行だけ。Zensical 0.0.71（`uvx --offline --from zensical==0.0.71 zensical build --strict`、作業用フォルダの写し）も「No issues found」で、h1・サイドバーが同じ。題名と nav_title に `&`・`<` を入れた写しでも、両方のエンジンで h1 が `整数のオーバーフロー &amp; &lt;__int128&gt;` になる。render_pages（3 ページ、390px のライト・ダーク）はエラー 0・警告 0

## D. 台帳 data/problems.yaml の平文化

方針 2 に合わない summary・approach を 25 項目直した（上の段 18 と、ページごとの言い回し alternatives の中 7。意味は変えていない）。YAML を読み直して、変わった値が summary・approach だけで、ほかの値と並びが同じことを確かめた。check_pages の台帳の指摘は 0、`fix_problems.py --check` も 0。

| 問題 | 欄 | 直した後の文 | 本文の問題の行（第 2 段でそろえる） |
| --- | --- | --- | --- |
| abc009_4 | summary | A_n = (C_1 AND A_(n−1)) XOR … XOR (C_K AND A_(n−K)) で定まる数列の第 M 項を求める（M ≤ 10^9）。 | math/matrix-power:352 |
| abc137_f | summary | 素数 p と 0/1 の列 a_0, …, a_(p−1) が与えられるとき、f(i) ≡ a_i (mod p) を満たす p − 1 次以下の多項式 f の係数を求める。 | math/lagrange-interpolation:157 |
| abc172_d | alternatives[0].summary | x の約数の個数を f(x) とするとき、x = 1..N の x·f(x) の和を求める（N ≤ 10^7）。 | math/floor-quotient-enum:209 |
| abc179_e | summary | A_1 = X、A_(n+1) = A_n^2 mod M で定まる数列の、最初の N 項の和を求める。 | basics/periodicity:188 |
| abc230_e | summary と alternatives[0].summary | i = 1..N の ⌊N/i⌋ の和を求める（N ≤ 10^12）。 | math/floor-quotient-enum:173・math/sigma-manipulation:222 |
| abc241_e | summary | 飴の個数 X に A_(X mod N) 個を足す操作を K ≤ 10^12 回行った後の飴の個数を求める。 | basics/doubling:225 |
| abc266_e | alternatives[0].approach | 残り k 回のときの期待値 E_k を、出目と E_(k−1) の大きい方の平均で後ろから求める（選択は max、偶然は平均） | （approach は行に出ない） |
| abc267_g | summary | 長さ N の数列 A の並べ替え N! 通り（同じ値の要素も区別する）のうち、A_i < A_(i+1) となる i がちょうど K 個あるものの個数を求める。 | dp/insertion-dp:262（行は「数列の並べ替えのうち、A_i < A_{i+1} …」と短い。A_(i+1) にそろえる） |
| abc270_g | summary | X_(i+1) = (A·X_i + B) mod P で定まる数列で、値 G が最初に現れる番号を求める（P は素数、なければ −1）。 | math/multiplicative-order:281 |
| abc300_h | summary | a_0 = … = a_(K−1) = 1、a_i = a_(i−1) + … + a_(i−K)（i ≥ K）で定まる数列について、m AND N = m を満たす非負整数 m すべてにわたる a_m の和を 998244353 で割った余りで求める（K ≤ 5×10^4、N ≤ 10^18）。 | math/linear-recurrence-fast:212 |
| abc304_f | alternatives[1].approach | 周期 d を持つ列の数 F(d) から、最小周期がちょうど d の数をメビウス反転で戻し、答えを、d \| N かつ d < N の μ(N/d) F(d) の和の −1 倍とする | （approach） |
| abc327_d | summary | 長さ M の 2 つの数列 S・T について、すべての i で X_(S_i) ≠ X_(T_i) となる 0/1 の列 X が存在するかを判定する。 | graph/bipartite-graph:189 |
| abc367_e | summary | 各 i について B_i = A_(X_i) とする操作を K ≤ 10^18 回行った後の数列を求める。 | basics/doubling:241 |
| abc377_e | summary と alternatives[0].summary | 順列 P に対して、すべての i で P_i を P_(P_i) に同時に置き換える操作を K 回行った後の列を求める。 | graph/graph-modeling:144・graph/functional-graph:221 |
| abc377_e | alternatives[1].summary | 順列 P に対して、すべての i で P_i を P_(P_i) に同時に置き換える操作を K 回行った後の P を求める。 | comb/permutation-cycles:194 |
| abc436_g | approach | 1/((1 − x)Π(1 − x^(A_i))) の係数として Bostan-Mori（か Berlekamp-Massey）で求める | （approach） |
| abc471_e | alternatives[0].approach | 和の 2 乗を a_i² の項と a_i a_j（i ≠ j）の項に展開し、各項を含む選び方 C(N−1, K−1)・C(N−2, K−2) を掛ける。i ≠ j の a_i a_j の和は (Σa)² − Σa² | （approach） |
| arc150_c | approach | 各頂点で B と貪欲に一致した個数の最小値を距離とし、単調な遷移 x → x + [A_v = B_(x+1)] でダイクストラ法（01-BFS）を回す | （approach） |
| arc167_b | approach | 約数の積は M^(d(M)/2)。指数 B·Π(B e_i + 1) の半分を、偶奇を mod の前の値で判定して求める | （approach） |
| arc185_e | approach | f(n+1) = 2f(n) + Σ 2^x gcd(A_x, A_n) の gcd を d \| gcd の φ(d) の和に分け、d ごとに d の倍数である前の要素の 2^x の和を持って更新する | （approach） |
| practice2_c | summary | T 個のケースそれぞれで i = 0..N−1 の ⌊(A × i + B)/M⌋ の和を求める。 | math/floor-sum:207 |
| practice2_f | summary | 2 つの数列 a, b について、i + j = k となる a_i b_j の和 c_k を、998244353 で割った余りですべての k について求める。 | math/convolution-ntt:280 |
| tdpc_fibonacci | summary | a_1 = … = a_K = 1、a_i = a_(i−1) + … + a_(i−K) で定まる数列の第 N 項を 10^9+7 で割った余りで求める（K ≤ 1000、N ≤ 10^9）。 | math/linear-recurrence-fast:182 |

（表の中の「\|」は「|」。）

ほかに、台帳は平文なのに本文の行が KaTeX で書かれた問題が 10 行ある（第 2 段で平文にする）：typical90_bt（basics/complexity-estimation:212）・abc467_f（basics/exchange-argument:239）・abc428_g（comb/burnside-lemma:186）・abc378_g（comb/young-tableaux:146）・abc458_g（dp/monge:200・dp/slope-trick:191）・abc455_g（string/hashing-for-sets:248）・abc351_g と abc311_h（tree/static-top-tree:160・175）。

## E. 手引きと決定事項

- §4：technique の水・青・黄と基礎の行を方針 1 の並びに直し、表の後に「節の並び」の 3 項（上の帯の節の置き場所・定型の節の相対順・technique の中身の節。§17-4 の同じ役の節は基礎では next-steps の位置、水・青・黄で上位の手法へのつながりを置くなら中身の節として落とし穴より前）を足した
- §6：front matter の平文の例に `O(N^(1/4))`・`log_(3/2)(W/ε) 回`・`i = 1..N の ⌊N/i⌋ の和` を足し、「`$` の空白」「平文の欄」（4 つの小項目）「本文の数式」と、文字の項の下に「法の文字」を足した
- §7：和文と `$…$` の空白（「・」の隣は空白なし）、次数・次元は算用数字と一次独立・一次従属、Vandermonde、別名は今のままでよい、を足した
- §10：方針の折りたたみの題と、要約は平文、を足した
- 付録 A：数え上げに「Vandermonde の恒等式」。付録 A の「かっこ内は別の書き方」とぶつからないよう、出典は付録の冒頭の文に書いた
- どれにも「（工程11、#68）」などの出典を付けた
- decisions.md：2026-10-29 の節の表に 6 行（節の並び・平文の欄・本文の数式・法の文字・数式の `$` の空白・次数と人名の表記。補足は「メインの判断」と手引きの節と検査の名前）。GitHub で数式に読まれないよう、`$` は `` ` `` で囲んだ

## F. tools/README.md

一覧の check_pages.py の行に「書き方」を足し、描画の崩れの表の後に新しい検査の表（7 種）と、数え方（text_runs・本物との一致）・まねていないもの・生成ページを見ない理由を書いた。

## 流した検査

| 検査 | 結果 |
| --- | --- |
| `python3 -m unittest discover -s tests/tools`（システムの Python 3.10） | 128 件 OK（Python-Markdown の要る 5 件は飛ばす） |
| `.venv/bin/python -m unittest discover -s tests/tools`（Python-Markdown 3.11） | 128 件 OK（新しい乱択の突き合わせ 600 件を含む） |
| `python3 tools/check_pages.py` | エラー 21（新しい「数式にならずに残る $」だけ）・警告 336（新しい 6 種だけ）。既存の検査の指摘は 0 のまま。終了コード 1（第 2 段で 0 にする） |
| `python3 tools/fix_problems.py --check` | 直すべき行 0 |
| `npx textlint $(python3 tools/textlint_targets.py)` | エラー 60（すべて新しい prh の規則。第 2 段で 0 にする） |
| `.venv/bin/mkdocs build -d <作業用フォルダ>/site` と Zensical 0.0.71 の `build --strict` | どちらも成功。#91 の 3 ページを確かめた |
| `python3 tools/render_pages.py <作業用フォルダ>/site --page cpp-structured-bindings,cpp-integer-overflow,suffix-automaton` | エラー 0・警告 0 |

CI（check.yml の check_pages と textlint）は、第 2 段でページを直すまで落ちる。第 1 段と第 2 段を同じ pull request にまとめるのがよい。

## 提案（メインが反映する共有ファイル）

1. **用語集 docs/guide/glossary.md#canonical-forms**（prh.yml の冒頭の約束「規則を足したら表にも行を足す」）：
   - 全体と基本の手法の表の「1 次元・2 次元・3 次元」の行の下に `| 1 次関数・1 次式・2 次関数・2 次式 | — | 一次関数・一次式・二次関数・二次式 |`
   - 整数論・代数（線形代数の語のある表）に `| 一次独立・一次従属 | — | 1 次独立・1 次従属 |`
   - 数え上げの表に `| Vandermonde の恒等式・Vandermonde 行列 | — | ヴァンデルモンドの等式・ファンデルモンド |`
   - 表記の規則（#canonical-rules）の数の項に「次数・次元は算用数字（1 次関数・1 次元）。一次独立・一次従属は用語として漢数字」
2. **用語集 473 行**「各区間では一次関数になる関数」→「1 次関数」（textlint のエラー。用語集はメインのファイル）
3. **台帳の 一次関数 6 か所**（abc228_h・abc289_g の approach、abc366_f の summary と alternatives の summary・approach、arc008_4 の summary）を「1 次関数」に（方針 6。今回の頼まれた範囲は平文化だけなので直していない）
4. **共有のページの新しい指摘**：guide/method-comparison（使い分け）の題 2（452・464 行）、guide/cheatsheet（早見表）の `\mathrm{mod}` 2（241・245 行）はメインのファイルなので、第 2 段の C の担当に任せるかメインが直すかを決める
5. 第 2 段の担当には、検査の全件を `python3 tools/check_pages.py --page <id> -v`（か `--field`）で見てもらう。節の並びの警告は 1 ページ 1 件で、今の順と手引きの順を出すので、そのまま並べ替えの指示になる

## 質問（メインに判断してほしい点）

1. **水・青・黄の technique の「上位の手法へのつながり」**：方針どおり（next-steps は基礎だけ定型）にすると、basics/difference-sequence（黄）・basics/exchange-argument（青）・basics/recursive-enumeration（水）の `## 上位の手法へのつながり {#next-steps}`（どれも落とし穴の直後）は中身の節になり、落とし穴より前へ動かすことになる。このままでよいか、technique のどの帯でも next-steps を定型にするか
2. **§15-4 の「使い分けに近い中身の節」**：math/floor-quotient-enum の `{#vs-others}`（落とし穴と例題の間）と ds/kth-element の `{#vs-kth-value}` は中身の節として扱い、落とし穴より前に置く指摘になる。使い分けの位置（確認問題の後）に置いてよいとするなら、検査に例外の表が要る
3. **§15-3 の `{#acl}` の中身の節**：math/ext-gcd・math/floor-sum・math/mod-pow は ACL の節が落とし穴の後ろにあり、中身の節として落とし穴より前へ動かす指摘になる。これでよいか
4. **大文字の `\mathrm{MOD}`**（コードの定数 MOD に合わせた書き方）も「法を表す mod の文字」に当てた（dp/dp-sequence-partition:171・math/mod-arithmetic:90・thinking/complement:121（6 か所）・130・131）。方針 4 の「法は m」に入れてよいか、小文字だけにするか（`MOD_VAR_RE` の `(?i:mod)` を `mod` にすれば外せる）
5. **ほかの「漢数字＋次」の語**：一次方程式（27）と 1 次方程式（13）が混ざっている。一次合同式（72）・一次不定方程式（17）・一次漸化式（5）も次数の語として 1 次… にそろえるか、用語として漢数字のままにするか。「1 次結合」（1）は一次独立と同じく「一次結合」にするか。front matter（10 か所）は textlint が見ないので、第 2 段で手で直すかも決めてほしい

## 使用量の目安

道具の呼び出し 150 回ほど。Web の取得はなし。ビルド（MkDocs・Zensical）各 2 回、textlint の全件 1 回（3 分）。

## 検証の指摘への対応（2026-10-29）

verify-tools.md の直しが要る点 1・2、要確認 A・B・D と、tools.md の質問 1〜5 へのメインの答えを反映した。docs/ のページは直していない。

### 直したこと

| # | ファイル | 中身 |
| --- | --- | --- |
| 1（指摘 1・質問 1） | tools/check_pages.py | `section_key` の「基礎だけ」の条件を外し、上位の手法へのつながり `next-steps`（と §17-4 の同じ役の節 `NEXT_STEPS_EQUIVALENTS`）を technique ならどの帯でも定型にした（technique 以外では今までどおり中身の節）。冒頭の説明と注記も直した |
| 1 | planning/style-guide.md | §4 の水・青・黄の並びに「落とし穴 →（上位の手法へのつながり。置くときだけ）→ 例題」を足し、「technique の中身の節」の項を「next-steps は technique ならどの帯でも定型。落とし穴の直後（例題の前）、sections に載せない」に改めた。§14-3 にも同じ文を足した |
| 1 | tests/tools/test_check_writing.py | test_basic_next_steps を、水・青・黄でも落とし穴 → next-steps → 例題 が通ること、例題の後ろの next-steps が定型の順のずれになること、overview では中身の節のままのこと、global-offset の同じ役の節が水でも通ることに改めた |
| 2（指摘 2） | tools/README.md | 「まねていないもの」に、リンクの行き先の中の `$`（検査は数えるが本物は残らない）と、行頭の HTML のブロック（`<details><summary>…`）の中の文字（本物では `$` が残るが検査は見ない）を足した。どれも今のページにない。`run_math` は直していない |
| 3（要確認 A） | tools/check_pages.py・test・README | 題（囲み・折りたたみ・タブ）に限り、数式・コード・リンクの行き先の外の素の計算量 `O(` を当てる（`RAW_BIG_O_RE`。前が英数字・`_` の `O(` は語の一部として外す。対のかっこまでを語に出す。`O(N^2)` は 1 語にまとめる）。要点の囲みには当てない。試験 test_big_o_in_titles を足した |
| 4（質問 2・3） | style-guide §4・§15-3・§15-4、decisions.md | 使い分けに近い中身の節（floor-quotient-enum#vs-others・kth-element#vs-kth-value）と `{#acl}`（ext-gcd・floor-sum・mod-pow）は中身の節として落とし穴より前に置く。検査の例外は作らない（検査は元から中身の節として見ているので変えていない） |
| 4（質問 4・要確認 B） | check_pages.py・試験・style-guide §6・decisions.md・README | 大文字の `\mathrm{MOD}` も法の文字として m・p に直す（検査は元から当てていた）。直前が開きかっこ（`(`・`\left(`）の `(\mathrm{mod}\ k)` は演算子の形として分け、警告の文を「数式の中の \mathrm{mod} を「(\mathrm{mod}\ k)」の形の演算子に使っている（演算子の \pmod{k} にする。a \equiv b \pmod{k}。2 項の演算子は \bmod）」にした。法の文字の文にも「大文字の MOD も同じ」「演算子の mod なら \pmod{k}・\bmod」を足した。同じ行に両方あれば 1 件の中に両方の文を出す |
| 4（質問 5・要確認 D） | style-guide §7・decisions.md | 関数・式は算用数字（1 次関数・1 次式・2 次関数・2 次式）、単独の「一次」も「1 次」。一次方程式・連立一次方程式・一次合同式・一次不定方程式・一次漸化式・一次独立・一次従属・一次結合は用語として漢数字 |
| 4 | style-guide §6・decisions.md | 本文の数式の項に「題の計算量も `$O(N)$`。検査は題の素の `O(…)` も当てる。`N = 40`・`dp[i]` のような印のない式は当てないので書くときに KaTeX にする」を足した |
| 5 | prh.yml | 「1 次方程式」→「一次方程式」（`/(?:(?<=[和文の字]) )?[1１] ?次方程式/`）と「1 次結合」→「一次結合」を足した。和文の字の後の空白もいっしょに取る（「連立 1 次方程式」→「連立一次方程式」、「の 1 次結合」→「の一次結合」）。同じ扱いを既存の一次独立・一次従属の規則にも入れた（「が 1 次独立」→「が一次独立」）。specs 付き。作業用フォルダの見本で `--fix` の結果を確かめ、「2 次方程式」「一次方程式」は当たらない |
| 6 | data/problems.yaml | 「一次関数」6 か所（abc228_h・abc289_g の approach、abc366_f の summary と alternatives[0] の summary・approach、arc008_4 の summary）を「1 次関数」にした（tools.md の提案 3） |

decisions.md は 2026-10-29 の節の既存の行（節の並び・本文の数式・法の文字・次数と人名の表記）を書き足し、補足に「担当の質問 N への答え」と書いた。

### 題の印のない式（要確認 A の残り）

`O(` の後も、題の数式・コードの外に `=`・`≤`・`<` などの関係か `英字[` を持ち、ほかの印で当たらない題が 35 個ある（basics/complexity-estimation:225「N = 40 の部分集合」、graph/warshall-floyd:297「d[2][2] = −3」、graph/graph-modeling:169「V ≤ 2k」など）。半分ほどは `t[12]`・`sum(13)`・`par[l]`・`S = abab`・`f(v) = (v < x)` のようにコードの名前や文字列を書いたもので、KaTeX にするかコードにするかがページごとに違う。誤検出とまでは言えないが機械では決められないので当てていない。第 2 段で直すなら、この 35 個を手で見る（一覧は作業用フォルダの再現で出せる）。

### 件数（出し直し）

`python3 tools/check_pages.py`：エラー 21・警告 348（前は 336）。既存の検査の指摘は 0 のまま。

| 検査 | basics | thinking | dp | graph | tree | ds | math | comb | string | geometry | misc | patterns | cpp | guide | 計 | ページ |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 数式にならずに残る $（エラー） | 4 | 2 | 1 | 1 | 1 | 2 | 2 | 2 | 5 | | | 1 | | | 21 | 13 |
| 要点・題の素の数式 | 2 | 1 | 5 | 8 | 5 | 13 | 12 | 1 | 4 | | 3 | 1 | | 4 | 59 | 45 |
| 和文に接した数式 | | | 1 | | | 4 | | | | | | | | | 5 | 2 |
| 平文の欄の TeX の記号 | 7 | | 8 | 3 | 2 | 1 | 29 | 9 | 1 | | | | | | 60 | 38 |
| 節の並び | 17 | 3 | 11 | 16 | 6 | 16 | 16 | 10 | 2 | 1 | | | 1 | | 99 | 99 |
| 方針の折りたたみの題 | 2 | | 23 | 14 | 12 | 26 | 11 | 8 | 5 | 2 | 4 | | | | 107 | 61 |
| 法を表す mod の文字 | | 3 | 2 | | | | 3 | 8 | | | | | | 2 | 18 | 11 |

変わったところ：

- 要点・題の素の数式 45 → 59（+14 行）：題の素の `O(…)` は 17 行で、うち 3 行（dp/dp-segment-tree:286・dp/tree-dp-square:208・graph/warshall-floyd:294）は前から別の印で当たっていた。新しい 14 行は basics/complexity-estimation:231・basics/divide-and-conquer:260・dp/tree-dp-square:103・ds/binary-trie:258・ds/interval-set:236・ds/lazy-segment-tree:302・ds/mo-algorithm:141・ds/monotonic-stack:282・ds/sparse-table:216・ds/stack-techniques:110・guide/reverse-index-constraints:468・math/gcd-properties:104・tree/root-path-dfs:236・tree/small-to-large:97。17 行を全部読み、どれも確認問題などの題の素の計算量で、誤検出はない
- 節の並び 101 → 99：basics/difference-sequence（黄）と basics/exchange-argument（青）の next-steps（落とし穴の直後）が通るようになった。basics/recursive-enumeration（水）は使い分けが例題の前にあるので残る（定型の順のずれだけ）
- 法を表す mod の文字：件数は同じ 18。dp/dp-prefix-sum:188 の文が「\pmod{k} にする」に変わった

第 2 段の組での件数（`cc/stage2-draft.md` の組）：要点・題の素の数式は A 21・B 26・C 12（C のうち guide/method-comparison 2・guide/reverse-index-constraints 2）、節の並びは A 53・B 42・C 4。ほかは前の表と同じ。

### prh と textlint

`npx textlint $(python3 tools/textlint_targets.py)`（357 ファイル）：エラー 74（前は 60）。新しく当たるのは 14 件で、どれも新しい 2 つの規則（ほかの規則の件数は同じ）：

| ページ | 件数 | 規則 |
| --- | --- | --- |
| comb/burnside-lemma | 1 | 1 次方程式（207） |
| comb/expectation-linear-equations | 1 | 1 次方程式（242） |
| comb/expectation-of-square | 1 | 1 次結合（133） |
| comb/expected-value-dp | 2 | 1 次方程式（137・145） |
| comb/optimal-strategy-expectation | 6 | 1 次方程式（132・169×2・266×2・271） |
| geometry/circle-geometry | 1 | 1 次方程式（189） |
| math/lagrange-interpolation | 1 | 連立 1 次方程式（119） |
| patterns/circular | 1 | 1 次方程式（186） |

front matter と台帳に「1 次方程式」「1 次結合」はない（grep で 0）。単独の「一次」（math/floor-sum:278・math/floor-quotient-enum:161 の「$i$ が分子に一次」）は prh が当てないので、第 2 段で手で「1 次」にする。

### 流した検査

| 検査 | 結果 |
| --- | --- |
| `python3 -m unittest discover -s tests/tools` | 129 件 OK（5 件は飛ばす） |
| `.venv/bin/python -m unittest discover -s tests/tools` | 129 件 OK |
| `python3 tools/check_pages.py` | エラー 21・警告 348（上の表） |
| `python3 tools/fix_problems.py --check` | 直すべき行 0 |
| `python3 tools/gen_site.py --check` | 生成物は最新 |
| `npx textlint $(python3 tools/textlint_targets.py)` | エラー 74（上の 14 件と前の 60 件） |

### 残った点

- 用語集（docs/guide/glossary.md#canonical-forms）に足す行の提案（上の提案 1）に、「一次方程式・一次結合 | — | 1 次方程式・1 次結合」と「次数の語は関数・式だけ算用数字」を加える（メインのファイル）
- `run_math` のリンクの行き先の `$` は README に書いただけで、検査は直していない（今のページにない）
- 題の印のない式 35 個は検査の外（上）
