# content-consistency の第 2 段：basics・thinking・tree・string・geometry・misc・patterns・cpp・guide・start（担当 pages-a）

- 担当の Issue：#68（平文のまま出る数式と法の文字）・#69（節の並び）・#77（1 次関数の表記）
- 作業ツリー：kyopro-atlas-wt/content-consistency（ブランチ fix/content-consistency）。2026-10-29
- 指示：planning/batches/fix/brief-fix.md と第 2 段の共通の指示（cc/stage2-common.txt）。第 1 段の報告 tools.md の検査で、担当の分野の指摘を 0 にした
- 生成ページ（分野の入口など）と `gen:begin`〜`gen:end` の中は直していない。本文を直した 62 ファイルは `updated: 2026-10-29`（stage はそのまま）

## 件数（直す前 → 直した後）

`python3 tools/check_pages.py --field <分野> -v` を 10 分野で流した数。

| 検査 | 前 | 後 |
| --- | --- | --- |
| 数式にならずに残る $（エラー） | 13 | 0 |
| 要点・題の素の数式 | 20 | 0 |
| 和文に接した数式 | 0 | 0 |
| 平文の欄の TeX の記号 | 10 | 0 |
| 節の並び | 30 | 0 |
| 方針の折りたたみの題 | 25 | 0 |
| 法を表す mod の文字 | 5 | 0 |
| 計 | エラー 13・警告 90 | エラー 0・警告 0 |

textlint（`npx textlint docs/<10 分野>/*.md`）：エラー 17 → 0（直したファイル 62 個で流し直して 0）。警告は直したファイルで 854 → 852。どれも元からある種類（文の長さ・読点の数）で、新しい種類の警告は出ていない。

## #69 節の並び

並べ替えた 30 ページ：

- basics（17）：binary-search-answer（見本）・binary-search・bit-full-search・bitwise-independence・brute-force・doubling・event-sort・fractional-binary-search・greedy-priority-queue・imos・interval-scheduling・lexicographic-greedy・prefix-sum-counting・prefix-sum・recursive-enumeration・run-length-encoding・ternary-search
- thinking（3）：complement・contribution・fix-variable
- tree（6）：leaf-first・tree-bipartite・tree-construction・tree-edge-contribution・tree-isomorphism・tree-traversal
- string（2）：string-basics・subsequence-matching
- geometry（1）：manhattan-chebyshev
- cpp（1）：cpp-initialization

やり方：h2 を節ごと（見出しから次の h2 の直前まで）動かした（作業用フォルダの reorder.py。check_pages の `h2_sections`・`section_key` を使う）。technique は「中身の節（元の順）→ 定型の節（手引き §4 の順）」、ほかの type は定型の節が占める位置だけで並べ直した。anchor と見出しの文字は変えていない。

- ほとんどは「使い分け（と確認問題）を例題の前に置いた」形で、使い分け・確認問題を力試しの後へ動かした
- basics/brute-force・prefix-sum-counting：上位の手法へのつながりを落とし穴の直後へ
- basics/binary-search の `{#interactive}`、basics/prefix-sum の `{#next-tools}`：落とし穴の後ろにあった中身の節を、落とし穴の前（中身の節の最後）へ。front matter の sections はもともとこの順なので変えていない
- tree/tree-isomorphism（overview）：学ぶための資料を落とし穴の後へ
- 確かめたこと：30 ファイルとも、空行を除いた行の多重集合が HEAD と同じ（行の消えや重複がない）。挿入と削除の行数も同じ。「上の」「下の」「次の節」「前の節」などの語を全件 grep し、動かした節（使い分け・確認問題・例題・上位の手法へのつながり）を位置で指す文がないことを確かめた（見つかった「次の節」「前の節」はどれも中身の節どうしで、順は変わっていない）

方針の折りたたみの題（25 か所・14 ページ）：練習問題の節の「方針」「練習問題の方針」を「練習の方針」、力試しの節の「方針」を「力試しの方針」にした（basics/divide-and-conquer、tree/auxiliary-tree・centroid-decomposition・euler-tour・lca・merge-process-tree・root-path-dfs・small-to-large・tree-path、string/aho-corasick・hash-safety・string-automaton-dp・suffix-array、geometry/convex-hull、misc/parsing・randomized）。thinking の例題の「方針」はそのまま。

## #68 平文のまま出る数式と法の文字

**要点の囲み**（Issue の 4 ページ）：

- thinking/fix-variable：「N ≤ 2×10^5 で 3 つ組は N^3 通り」→ `$N \le 2 \times 10^5$`・`$N^3$`。同じ囲みの「3 つ組 (i < j < k)」も `$(i < j < k)$`
- string/aho-corasick：`10&#94;5〜10&#94;6` → `$10^5$〜$10^6$`
- misc/parsing：`2×10^5` → `$2 \times 10^5$`
- patterns/interval：「N 個の区間 [L_i, R_i]」→「$N$ 個の閉区間 $[L_i, R_i]$」（本文は半開区間を基本にし、問題文の区間は閉区間と書いているので「閉区間」を足した）。同じ囲みの「和が K（K の倍数）」も `$K$`

**折りたたみ・囲みの題**（16 か所）：basics/complexity-estimation・divide-and-conquer（`O(L²)` → `$O(L^2)$`）、tree/lca（2）・root-path-dfs・small-to-large・tree-traversal、string/hash-safety（2。`2^64` → `$2^{64}$`）・rolling-hash、misc/bitset-speedup・randomized（`10^-9` → `$10^{-9}$`）、guide/method-comparison（2。メインのファイルだが頼まれた所）・reverse-index-constraints（2）。lca の「S[u] + S[v] − 2S[l]」は `$S[u] + S[v] - 2S[l]$` にした。

**数式にならずに残る $**（13 行・7 ページ）：閉じの `$` の前の空白を取った（`$S = $ bacbab` → `$S =$ bacbab`、`（個数）$\times a_j - $（和）` → `$\times a_j -$`、`$\ell = \mathrm{lcp}[i-1] + $ 残り` → `+$ 残り`）。意味と表示は変わらない。basics/lexicographic-greedy（3 行）・run-length-encoding、thinking/contribution（2）、tree/euler-tour、string/string-basics（3）・suffix-array（2）、patterns/subsequence-and-substring。

**平文の欄**（10 件）：

- 台帳を平文にした問題（tools.md の D の表）の本文の行を台帳の summary と同じ文にした：basics/doubling の abc241_e・abc367_e、basics/periodicity の abc179_e
- 台帳が平文で本文が KaTeX の行を平文にした：basics/complexity-estimation の typical90_bt、tree/static-top-tree の abc351_g・abc311_h、string/hashing-for-sets の abc455_g（どれも台帳の summary と同じ文になった）。basics/exchange-argument の abc467_f は本文の行が台帳と違う言い回しなので、`$` だけを外した（下の提案 3）
- front matter：basics/periodicity の signs[1]「x_{n+1}」→「x_(n+1)」、basics/ternary-search の complexity「log_{3/2}」→「log_(3/2)」

**法の文字**（5 件）：

- thinking/complement 121・130・131 行：`\mathrm{MOD}` を $p$ にし、初めて出る所に「法 $p = 10^9 + 7$（コードの `MOD`）」と書いた。このページは $p$ をほかに使っていない
- guide/cheatsheet の ACL の表（メインのファイルだが頼まれた所）：`convolution` は `$O(n \log n + \log p)$`（法は素数）、`modint` は `$O(\log m)$`。表の前の文が「$m$ は辺数」としていたので、「$m$ は辺数（`pow_mod`・`inv_mod`・`floor_sum`・`modint` の行では法）、$p$ は素数の法」にした（`pow_mod` などの行はもとから $O(\log m)$ で法の意味だった）

## #77 表記

- 一次関数 → 1 次関数：basics/exchange-argument（3）・tree/static-top-tree（11）・guide/glossary 473 行（1。頼まれた所）。和文の字に続く所は空白を入れた（「を返す 1 次関数」）
- 1 次方程式 → 一次方程式：geometry/circle-geometry 189 行・patterns/circular 186 行
- 担当の分野の front matter に同じ表記はなかった。guide/roadmap・term-index・reverse-index-signs に残る「一次関数」「一次式」はどれも gen の中（他の分野の front matter から作る）なので、元のページの担当とメインの gen_site で直る
- **guide/glossary#canonical-forms**（頼まれた所。tools.md の提案 1 と prh.yml の規則に合わせた）：
    - 全体と基本の手法の表の「1 次元・2 次元・3 次元」の下に `| 1 次関数・1 次式・2 次関数・2 次式 | — | 一次関数・一次式・二次関数・二次式 |`
    - 整数論・数え上げの表の「掃き出し法」の下に `| 一次独立・一次従属・一次結合 | — | 1 次独立・1 次従属・1 次結合 |` と `| 一次方程式・連立一次方程式 | — | 1 次方程式・連立 1 次方程式 |`（prh の一次方程式・一次結合の規則もあるので足した）
    - 同じ表の「包除原理」の下に `| Vandermonde の恒等式・Vandermonde 行列 | — | ヴァンデルモンドの等式・ファンデルモンド・バンデルモンド |`（prh はヴ・フ・バの 3 つを当てる）
    - #canonical-rules の数の項の後に「次数・次元は算用数字で書く（1 次関数・2 次式・1 次元）。一次独立・一次従属・一次結合・一次方程式・一次合同式・一次不定方程式・一次漸化式は、用語として漢数字のまま残す。」

## 任意：guide/library-design#acl-names

表から「確認の問題」の列を外して 4 列にした。表の前の文の「確認の問題は Library Checker の問題で、各ページの末尾の…」を「各部品の確認に使う Library Checker の問題は、[ページ → 確認用の問題](#verify-table)の表で手法のページの行を引く。」にした。外した 8 問（unionfind・unionfind_with_potential・dynamic_graph_vertex_add_component_sum・point_add_range_sum・ordered_set・point_set_range_composite・range_affine_range_sum・staticrmq）は、どれも #verify-table（gen）にあることを確かめた。

## 流した検査

| 検査 | 結果 |
| --- | --- |
| `python3 tools/check_pages.py --field <分野> -v`（basics・thinking・tree・string・geometry・misc・patterns・cpp・guide・start） | 前 エラー 13・警告 90 → 後 どの分野もエラー 0・警告 0 |
| `npx textlint`（直した 62 ファイル） | エラー 0。警告 852（直す前の同じファイルは 854。新しい種類はない） |
| `python3 tools/fix_problems.py --check --page <id>`（complexity-estimation・doubling・exchange-argument・periodicity・static-top-tree・hashing-for-sets） | どれも直すべき行 0 |
| `.venv/bin/mkdocs build -d <作業用フォルダ>/site` | 成功 |
| `python3 tools/render_pages.py <作業用フォルダ>/site --page <数式や表を直した 32 ページ>` | エラー 0。警告 22（画面の幅を超える別行の数式、15 ページ）。どれも元からある別行の数式で、`$$` は 1 つも触っていない |
| `python3 tools/gen_site.py --check` | 生成物が古い 28 ファイル（updated と front matter の変更、ほかの担当の変更を含む）。作り直しはメインに任せる |

## 提案（メインが反映する共有ファイル）

1. **gen_site の作り直し**：basics/periodicity の signs・basics/ternary-search の complexity を平文にしたので、guide/reverse-index-signs などの生成物が変わる。updated も 62 ページで変えた
2. **台帳の「1 次関数」**：tools.md の提案 3 のとおり、台帳の 6 か所（abc366_f の summary など）が「一次関数」のまま。basics/exchange-argument 225 行の abc366_f の行（本文は「1 次関数」に直した）と台帳の文が違うので、台帳も直すとそろう
3. **abc467_f の要約**：basics/exchange-argument 239 行の本文の要約（「書くのに A_j 分かかり、…A_i か B_i を書き換えるクエリ…」）は台帳の summary と言い回しが違い、添字も j と i が混ざっている。台帳の文（「各メールに書く時間 A_j と返信までの時間 B_j があり、…」）にそろえるかを決めてほしい（今回は `$` を外しただけ）

## 質問（メインに判断してほしい点）

1. guide/cheatsheet の ACL の表は、ACL のドキュメントに合わせて $m$ を辺数と法の両方に使っている（もとから）。前置きの文で行ごとの意味を書いて済ませたが、法の行を別の文字にするか（たとえば法をすべて $p$・$m$ のままにし、辺数を $|E|$ にする）は判断してほしい
2. patterns/interval の要点に「閉区間」を足した。signs（front matter）の「N 個の区間 [L_i, R_i]」は平文で、閉区間と書いていない。signs にも足すか

## 検証の指摘への対応

verify-pages-a.md の 3 点をすべて直した（指摘はいずれも妥当と判断した）。

| Issue | ファイル・行 | 直した内容 |
| --- | --- | --- |
| #77 | docs/geometry/circle-geometry.md:189 | 「2 本の 一次方程式」→「2 本の一次方程式」（和文と漢字の間の空白を除いた） |
| #77 | docs/patterns/circular.md:186 | 「$x$ の 一次方程式」→「$x$ の一次方程式」 |
| #68 | docs/guide/cheatsheet.md:230 | 前置きの文を「（`pow_mod`・`inv_mod`・`modint` の行では法、`floor_sum` の行では割る数）」に分けた。floor_sum(n, m, a, b) の m は floor((ai+b)/m) の割る数で、法ではない |

確かめたこと：

- 担当の分野で「 一次」（空白に続く一次）が地の文に残っていないことを grep で確かめた（glossary の表の中だけ）
- `python3 tools/check_pages.py --page circle-geometry`・`circular`・`cheatsheet`：エラー 0・警告 0
- `npx textlint`（3 ファイル）：エラー 0。警告 23 件はもとからある文の長さ・括弧の対応の警告で、今回の変更によるものではない
- 3 ページとも `updated: 2026-10-29` であることを確かめた
