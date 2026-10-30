# content-consistency の第 2 段 pages-a の検証（担当 verify-pages-a）

- 対象：pages-a が直した 62 ファイル（basics・thinking・tree・string・geometry・misc・patterns・cpp・guide）と報告 pages-a.md。Issue #68・#69・#77
- 作業ツリー：kyopro-atlas-wt/content-consistency（fix/content-consistency、commit 前）。2026-10-29
- 作業用フォルダ：/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/7a638398-7759-4637-95c7-6739e8d52414/scratchpad/fix/content-consistency/verify-pages-a

## 結果

| Issue | 判定 | 直しが要る点 |
| --- | --- | --- |
| #68 平文の数式・法の文字 | 直しが要る | 1 |
| #69 節の並び | 合格 | 0 |
| #77 1 次関数の表記 | 直しが要る | 2 |

## 直しが要る点

1. **#77 docs/geometry/circle-geometry.md 189 行**：「2 本の 一次方程式」。「1 次方程式」を「一次方程式」にしたとき、算用数字の前に置いていた空白が残り、和文（「の」）と漢字の間に空白がある（手引き §7・glossary #canonical-rules「全角どうしの間には入れない」）。textlint はこの形を見ない。→「2 本の一次方程式」にする（prh の一次方程式の規則も、和文の字の後の空白ごと取る形）
2. **#77 docs/patterns/circular.md 186 行**：「$x$ の 一次方程式を解けばよい」。同じく「の」と「一次」の間に空白が残る。→「$x$ の一次方程式を解けばよい」
3. **#68 docs/guide/cheatsheet.md 230 行**：「$m$ は辺数（`pow_mod`・`inv_mod`・`floor_sum`・`modint` の行では法）」。`floor_sum(n, m, a, b)` の $m$ は $\lfloor (ai + b) / m \rfloor$ の割る数で、法ではない（ACL のドキュメントも $O(\log m)$ の $m$ は分母）。新しく足した文が事実と違う。→「（`pow_mod`・`inv_mod`・`modint` の行では法、`floor_sum` の行では割る数）」のように分ける

## 確かめたこと

### 検査

| 検査 | 結果 |
| --- | --- |
| `python3 tools/check_pages.py --field <分野>`（basics・thinking・tree・string・geometry・misc・patterns・cpp・guide・start） | どの分野もエラー 0・警告 0（書き方の 7 種・節の並びを含む） |
| `npx textlint`（直した 62 ファイル） | エラー 0・警告 852（報告どおり） |
| `python3 tools/fix_problems.py --check --page <id>`（complexity-estimation・doubling・exchange-argument・periodicity・static-top-tree・hashing-for-sets） | どれも直すべき行 0 |
| `mkdocs build` → `python3 tools/render_pages.py <作業用>/site --page <62 ページ>` | KaTeX のエラー・描かれない数式・地の文に残った記法・横ずれ はすべて 0。警告は画面の幅を超える別行の数式 50 件（どれも `$$` で、今回は触っていない） |

### #69 節の並び

- 30 ページの h2 の並びを HEAD と比べた。動いたのは定型の節（comparison・quiz・next-steps・pitfalls・resources）と、binary-search の `interactive`・prefix-sum の `next-tools` だけで、どのページも手引き §4（落とし穴 → 上位の手法へのつながり → 学ぶための資料 → 例題 → 練習 → 力試し → 確認問題 → 使い分け → 参考）の順になった
- 中身が落ちていないこと：62 ファイルすべてで、空行を除いた行の多重集合を HEAD と比べた。並べ替えだけのページは差が 0（updated の 1 行を除く）、ほかは書き換えた行の数だけ同数の出入りで、行の消えや重複はない
- front matter の sections は 30 ページとも変わっておらず、本文の h2 の順と食い違わない
- 「前の節」「次の節」「上の」「下の」などの位置で指す語を 30 ページで grep した。残るのは中身の節どうし（bitwise-independence 97・149、fractional-binary-search 129、lexicographic-greedy 70、greedy-priority-queue 93、tree-traversal 65、tree-bipartite 95）で、どれも順は変わっていない。動かした節を位置で指す文はない
- 方針の折りたたみの題（練習の方針・力試しの方針）：差分の 25 か所を見て、節の種類と題が合っている

### #68 平文の数式・法の文字

- 要点・題・本文の数式化（30 か所ほど）を差分で 1 つずつ見た。意味は元と同じ（`2×10^5` → `$2 \times 10^5$`、`10^-9` → `$10^{-9}$`、`2^64` → `$2^{64}$`、`S[u] + S[v] − 2S[l]` → `$S[u] + S[v] - 2S[l]$` など）。lca の確認問題の題は生成した HTML でも `<summary>` の中が arithmatex になっている
- `$S = $ …` → `$S =$ …` などの閉じの空白の除去（13 行）は、表示される文字が変わらない
- thinking/complement：$\mathrm{MOD}$ を $p$ にし、初出で「法 $p = 10^9 + 7$（コードの `MOD`）」とした。範囲 $[0, p)$・$(-p, p)$・$-2p$〜$2p$ は元と同じ意味で、ページに別の $p$ はない
- 問題の行：doubling（abc241_e・abc367_e）・periodicity（abc179_e）・complexity-estimation（typical90_bt）・static-top-tree（abc351_g・abc311_h）・hashing-for-sets（abc455_g）の本文の要約が台帳の summary と一字一句同じであることを確かめた。exchange-argument の abc366_f・abc467_f は台帳と言い回しが違う（pages-a の提案 2・3 のとおり、メインの判断待ち）
- 平文の欄：periodicity の signs・ternary-search の complexity は `_(…)` の平文になり、TeX の記号が残らない

### #77 表記

- 担当の分野の本文（gen の外）に「一次関数」「一次式」「二次関数」「二次式」「1 次方程式」「\mathrm{mod}」「\mathrm{MOD}」は残っていない。残りは guide/roadmap・reverse-index-signs・term-index の gen の中だけ（ほかの分野の front matter から作られる）
- glossary の対応表に足した 4 行と prh.yml を突き合わせた：1 次関数・1 次式・2 次関数・2 次式（一次関数・一次式・二次関数・二次式）、一次独立・一次従属・一次結合（1 次独立など）、一次方程式・連立一次方程式（1 次方程式・連立 1 次方程式）、Vandermonde（ヴ・フ・バの 3 つ。prh の `[ヴフバ]ァ?ンデルモンド` と合う）。どれも prh の expected と pattern に一致する。#canonical-rules に足した 1 文も prh のコメントと同じ方針

### 任意：guide/library-design#acl-names

- 表から外した 8 問は、どれも同じページの #verify-table（gen）にある。#verify-table の anchor はある。start/how-to-use 231 行の #acl-names へのリンクは「違いの一覧」を指すので、列を外しても食い違わない

## メインへの参考（直しが要る点ではない）

- 台帳 data/problems.yaml の abc366_f の summary が「N 個の1 次関数」（「個の」と「1」の間に空白がない）。本文は「N 個の 1 次関数」。台帳を直すとき（pages-a の提案 2）に空白も足すとそろう
- gen_site の作り直しが要る（signs・complexity・updated を変えたため。pages-a の提案 1）
