# content-consistency の第 2 段の検証：dp・graph のページ（担当 pages-b の直し）

- 検証した Issue：#68・#69・#77（直した担当の報告は pages-b.md）。2026-10-29
- 作業ツリー：kyopro-atlas-wt/content-consistency（ブランチ fix/content-consistency）。ファイルは直していない

## 結果

| Issue | 判定 | 直しが要る点 |
| --- | --- | --- |
| #68 | 直しが要る（軽い） | 1 |
| #69 | 合格 | 0 |
| #77 | 合格 | 0 |

## 検査

- `python3 tools/check_pages.py --field dp -v`・`--field graph -v`：エラー 0・警告 0（全体もエラー 0・警告 0）
- `npx textlint docs/dp/*.md docs/graph/*.md`：手で書いたページのエラーは 0。エラー 2 件は生成ページ docs/dp/index.md 55・59 行の「一次関数」で、summary（dp/cht・dp/dp-speedup-overview）はもう「1 次関数」なので、メインが `tools/gen_site.py` を流せば消える
- `python3 tools/fix_problems.py --check --page exchange-argument-dp` ほか：直すべき行 0
- 作業用フォルダへビルドし `python3 tools/render_pages.py <site> --field dp --field graph`：87 ページでエラー 0（KaTeX のエラー・地の文の記法・ページの横ずれとも 0）。別行の数式のはみ出しの警告 63 件（報告と同じ。範囲の外）
- 幅 390px で knapsack-undo#prefix-and-suffix（ライト）と degree-sqrt#push-pull（ダーク）を撮って見た。aligned の 2 行の式、言葉で分けた箇条書きの式とも、画面の内に収まっている

## #69 節の並び

- 並べ替えた 27 ページで、直す前と後の空でない行の多重集合を比べた。並べ替えだけのページは差が updated の 1 行（と別の Issue の直しの行）だけで、節の中身は落ちていない。h2 の見出しの集まりも同じ
- 定型の節の順は手引き §4 の決まり（pitfalls → next-steps → resources → examples → practice → challenge → quiz → comparison → references）どおり。overview の k-shortest-paths・offline-dynamic-connectivity も使い分けが参考の直前になった
- connected-components は中身の節 forest・values-as-vertices を落とし穴の前に移した。front matter の sections の順と本文の順が合っている
- dp・graph の全ページで、front matter の sections の anchor の順と本文の見出しの順を照合し、食い違い 0
- 位置で指す言い方（前の節・次の節・上の・下の など）を 27 ページで探した。当たったのは中身の節どうしを指すもの（dp-reconstruction の「前の節」→ #trace-back、bellman-ford の「前の節」→ #relevant-cycles、dp-basics・dp-speedup-overview の「次の節」）で、どれも動いていない節を指し、正しい
- 方針の折りたたみの題：dp・graph の全ページで「…方針」の note が属する h2 を調べ、practice の中は「練習の方針」、challenge の中は「力試しの方針」で始まる。食い違い 0

## #68 平文の数式と法の文字

- 要点 5 ページ（extended-dijkstra・modular-shortest-path・bipartite-graph・functional-graph・inline-dp）は KaTeX になった。意味は元と同じ
- 題の数式（dp-segment-tree・tree-dp-square・interval-dp・chromatic-number・graph-modeling・max-flow・warshall-floyd・extended-dijkstra）：$ で囲んだだけで文字は同じ。warshall-floyd の $d[2][2] = -3$ は元の「−3」と同じ値
- 数式を直した所の意味：
  - knapsack-undo 109〜114 行：`\left( … \right)` を `\bigl( … \bigr)` にして aligned で 2 行に積んだだけで、式は同じ。129 行「$\mathrm{pre}[i][j] + \mathrm{suf}[i + 1][W - w_i - j]$ の $j$ についての最大に、$v_i$ を足した値」は元の $\max_j(\dots) + v_i$ と同じ
  - degree-sqrt 88 行：「pushed[x]・own[x] と、hn[x] のすべての own[h] のうちの最大」は元の入れ子の max と同じ
  - interval-dp-advanced 62 行：f と g の 2 式を aligned で縦に積んだだけ。`\\[0.3em]` は \substack の行間だけ
  - dp-prefix-sum 188 行の `\pmod{k}`、min-cost-flow 179 行の `$B - \text{利得}$`、dp-phase 158 行、insertion-dp 77 行の空白、dp-sequence-partition 171 行の「法 $m$」：意味は同じ。法の文字は start/notation#numbers の $m$
  - front matter の signs（dp-prefix-sum・dp-segment-tree・dp-sequence-partition・slope-trick）：範囲をかっこに移しただけで意味は同じ
- 問題の行の要約：insertion-dp・monge・slope-trick（abc458_g）・bipartite-graph（abc327_d）・functional-graph・graph-modeling（abc377_e）は台帳の summary と一字一句同じ。exchange-argument-dp 207 行（abc366_f）は「N 個の 1 次関数」で、台帳の「N 個の1 次関数」と空白 1 つだけ違う。本文の方が手引きに合っており、台帳を直す提案（pages-b.md の提案 1）がメインに出ているので、本文の直しは要らない
- dp・graph に `\mathrm{MOD}`・`\mathrm{mod}` は残っていない

### 直しが要る点

1. **docs/dp/dp-sequence-partition.md 38 行（要点）**：`$\mathrm{dp}[i] = \sum$（または $\min$）$_{j < i,\ [j, i) \text{ が条件を満たす}}\ \mathrm{dp}[j]$` は、下付きの数式が土台なしで「（または min）」の後に置かれ、描くと添字が Σ にかからず浮く（担当も「残った点」に挙げている）。同じ行を写した signs[3] は今回「dp[i] = Σ（または min）dp[j]（j < i で [j, i) が条件を満たすもの）」に直したので、要点と signs の形も食い違った。
   直し方の案：signs[3] に合わせ、`$\mathrm{dp}[i] = \sum \mathrm{dp}[j]$（または $\min$。$j < i$ で $[j, i)$ が条件を満たすもの）` のように範囲をかっこの言葉にする。あるいは `$\mathrm{dp}[i] = \sum_{j < i,\ [j, i) \text{ が条件を満たす}} \mathrm{dp}[j]$（$\min$ でも同じ）` と添字を Σ に付ける

## #77 表記

- dp・graph の手で書いたページに「一次」は残っていない（grep で 0）。「1 次関数」「1 次式」の前後の空白は手引き §7 どおり
- dp/cht・dp/dp-speedup-overview の summary、dp/exchange-argument-dp の signs[2] も直っている
- 生成ページ docs/dp/index.md の「一次関数」2 か所は gen_site の再生成で消える（メインの作業）

## 指摘の外で気づいたこと（直しは要らない）

- 台帳 abc366_f の summary・alternatives の「N 個の1 次関数」の空白は、pages-b.md の提案 1 のとおりメインで直す
