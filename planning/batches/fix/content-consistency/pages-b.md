# content-consistency の第 2 段：dp・graph のページ（担当 pages-b）

- 担当の Issue：#68（平文のまま出る数式と法の文字）・#69（節の並び）・#77（1 次関数の表記）
- 作業ツリー：kyopro-atlas-wt/content-consistency（ブランチ fix/content-consistency）。2026-10-29
- 直したのは docs/dp/・docs/graph/ の手で書いたページだけ（生成ページの docs/dp/index.md・docs/graph/index.md は触っていない）。直した 59 ページはどれも `updated: 2026-10-29`（前から 2026-10-29 でなかったのは dp/dp-order・dp/knapsack-undo・graph/complement-graph-bfs・graph/connected-components・graph/cycle-detection・graph/functional-graph の 6 枚。`stage` は変えていない）

## 検査の件数（直す前 → 直した後）

| 検査 | dp | graph |
| --- | --- | --- |
| check_pages エラー（数式にならずに残る $） | 1 → 0 | 1 → 0 |
| 節の並び | 11 → 0 | 16 → 0 |
| 方針の折りたたみの題 | 23 → 0 | 14 → 0 |
| 平文の欄の TeX の記号 | 8 → 0 | 3 → 0 |
| 要点・題の素の数式 | 5 → 0 | 8 → 0 |
| 法を表す mod の文字 | 2 → 0 | 0 → 0 |
| 和文に接した数式 | 1 → 0 | 0 → 0 |
| check_pages の合計 | エラー 1・警告 50 → 0・0 | エラー 1・警告 41 → 0・0 |
| textlint（手で書いたページ全部） | エラー 12・警告 1021 → エラー 0・警告 1023（2 件増。下の「残った点」） | |
| render_pages（dp・graph の 87 ページ、390px ライト・ダーク） | エラー 4（地の文の $ 2・ページの横ずれ 2）→ 0。別行の数式のはみ出しの警告 64 → 63 | |

- `python3 tools/fix_problems.py --check --page <id>`：直した 59 ページすべてで直すべき行 0
- `python3 tools/check_pages.py`（全体）：エラー 0。警告 15 はどれも dp・graph の外（ほかの担当の分野）

## #69 節の並び

並べ替えたのは 27 ページ。h2 を節ごと（見出しから次の h2 の直前まで）動かした。作業用フォルダのスクリプト（`reorder.py`）で、中身の節を元の順のまま前に、定型の節を手引き §4 の順（pitfalls → next-steps → resources → examples → practice → challenge → quiz → comparison → references）に並べた。フェンスの中の `## ` は見出しとみなさない。各ページで、空行を除いた行の集まりが直す前と同じ（並びだけが変わった）ことを確かめた。anchor・見出しの文字は変えていない。

- dp（11）：digit-dp・dp-basics・dp-dag（next-steps を落とし穴の後へ）・dp-order・dp-reconstruction・dp-sequence-partition・dp-speedup-overview（hub。力試しを確認問題の前へ）・exchange-argument-dp・inline-dp・knapsack-01・subset-sum
- graph（16）：bellman-ford・bfs・complement-graph-bfs・connected-components（中身の節 `forest`・`values-as-vertices` を落とし穴の前へ。front matter の sections はもとから本文の新しい順と同じ）・cycle-detection・dfs（next-steps を落とし穴の後へ）・dijkstra・graph-basics・grid-graph・k-shortest-paths（overview。使い分けを資料・練習・確認問題の後へ）・min-cost-flow・minimum-spanning-tree・offline-dynamic-connectivity（overview）・shortest-path-dag・small-graph-brute-force・time-dependent-dijkstra
- 位置で指す言い方（「上の」「下の」「次の節」「前の節」「後の節」と、確認問題・使い分け・例題・練習を前後で指す言い方）を 27 ページで探した。当たったのは中身の節どうしを指すもの（dp-basics の「次の節」→ `#pull-to-prefix-sum` など。リンクの行き先か、動かしていない中身の節の並びのまま）だけで、食い違いはない
- front matter の sections は中身の節だけを載せていて、定型の節は載っていない。中身の節の順は変えていないので、sections の並びは本文と合ったまま

方針の折りたたみの題（37 か所）：練習問題の節の中を「練習の方針」（問題ごとのものは「練習の方針（ABC142 E）」の形）、力試しの節の中を「力試しの方針」にした。dp：bit-dp 8・dp-segment-tree 2・dp-speedup-overview 1・exchange-argument-dp 2・lcs 4・subset-enumeration-dp 2・tree-dp-square 2・tree-dp 2。graph：difference-constraints 1・graph-construction 2・graph-modeling 1・konig-theorem 1・max-flow 2・min-cut 1・project-selection 2・scc 1・two-sat 1・warshall-floyd 2。

## #68 平文の数式と法の文字

### 要点の囲み（頼まれた 5 ページ）を KaTeX に

- graph/extended-dijkstra 37〜49 行：`$K$ 回まで無料…`、`状態数が $10^6$〜$10^7$ 程度に収まる（$9! = 362880$、$60^4 \approx 1.3 \times 10^7$）`、`$\mathrm{dist}[\text{頂点}][\text{向き・残り回数・偶奇}]$`
- graph/modular-shortest-path：`$K$ の倍数…`、`$K$ が $10^5$〜$10^6$ 程度`
- graph/bipartite-graph：`$X_i$ と $Y_i$ は異なる値、という条件が $M$ 個ある`
- graph/functional-graph：`各 $i$ から $A_i$ へ移動する`
- dp/inline-dp：`$\mathrm{dp}[i][\ast]$ から $\mathrm{dp}[i+1][\ast]$ で変わる場所が少ない`。区間の行は本文（154 行「問題の閉区間 $[l, r]$」）に合わせて「閉区間 $[l, r]$ の右端 $r$ で、$l$ 以降の…」と明記した
- front matter の signs は手引き §6 どおり素の文字のまま

### 題の素の数式を KaTeX に

検査の 8 か所：dp/dp-segment-tree 277・286、dp/tree-dp-square 103（`証明（$O(NK)$ になる理由）`）・208、graph/extended-dijkstra 392、graph/max-flow 289、graph/warshall-floyd 294。

tools.md の「題の印のない式」に当たる dp・graph の 5 か所も手で直した：dp/dp-segment-tree 280（`$\mathrm{dp}[y] - C \lvert x - y \rvert$`・`$\mathrm{dp}[y] - C y$`）、dp/interval-dp 295（`$N = 3000$`）、graph/graph-modeling 169（`$V \le 2k$`）、graph/chromatic-number 88（`$k = 1$`）、graph/warshall-floyd 297（`$d[2][2] = -3$`。本文の答えと同じ $d$）。

### 平文の欄

- 問題の行の要約を台帳の summary と同じ文にした：dp/insertion-dp 262（abc267_g）、dp/monge 200・dp/slope-trick 191（abc458_g。行が KaTeX で、言い回しも台帳と違っていた。どちらも台帳の文）、graph/bipartite-graph 189（abc327_d）、graph/functional-graph 221・graph/graph-modeling 144（abc377_e）
- front matter の signs の範囲つきの式を、範囲を外した Σ・max・min とかっこの範囲にした：dp/dp-prefix-sum signs[2]（`dp[i] = Σ dp[j]（j = i−R..i−L）のように…`）、dp/dp-segment-tree signs[1]（`dp[i] = max dp[j] + c（j < i、l ≤ a_j ≤ r）のように…`）・signs[3]（`dp[i] = min dp[j] + c（i−K ≤ j < i。窓が単調に動く）`）、dp/dp-sequence-partition signs[3]（`dp[i] = Σ（または min）dp[j]（j < i で [j, i) が条件を満たすもの）`）、dp/slope-trick signs[2]（`dp[i][x] = min dp[i−1][y] + |x − a_i|（y ≤ x）のように…`）

### 地の文の $・和文に接した数式・法の文字

- dp/dp-phase 158：`$S = $ "a"、$T = $ "aa" で` → `$S$ が "a"、$T$ が "aa" のとき、`
- graph/min-cost-flow 179：`「$B - $ 利得」` → `「$B - \text{利得}$」`（101 行の $B - a$ と同じ意味）
- dp/insertion-dp 77：`すると$p_i` → `すると $p_i`
- dp/dp-prefix-sum 188：`P_t \equiv P_i \ (\mathrm{mod}\ k)` → `P_t \equiv P_i \pmod{k}`
- dp/dp-sequence-partition 171：`$\mathrm{MOD}$ を足してから` → 「法 $m$ で余りを取った累積和の差 … $m$ を足してから余りを取る」（初めて出る所で法と書いた。同じページの $m$ は 91・101 行の区間 DP の分け目にもあるが、別の節の別の話）

### ハブのリンクの文字

「DP の高速化の全体像」を題名の「DP の高速化の選び方」にした：dp/dp-basics 162・195、dp/dp-prefix-sum 312、dp/dp-segment-tree 191。dp-segment-tree は「全体の選び方は [DP の高速化の選び方]にまとめる」と重なるので、「ほかの道具を含めて、どれを使うかは [DP の高速化の選び方](…)で遷移の式の形から決める。」にした。

### render_pages の横ずれと \substack

- dp/knapsack-undo#prefix-and-suffix：横ずれ（9px）の元は別行ではなく、129 行の箇条書きのインラインの数式 `$\max_j \left( … \right) + v_i$` だった。「$\mathrm{pre}[i][j] + \mathrm{suf}[i + 1][W - w_i - j]$ の $j$ についての最大に、$v_i$ を足した値である」と数式を分け、折り返せるようにした。同じ節の別行の数式（109〜114 行）も `aligned` で 2 行に積んだ（`\left( \right)` は `\bigl( \bigr)`）
- graph/degree-sqrt#push-pull：横ずれ（4px）の元も別行ではなく、88 行の箇条書きのインラインの数式 `$\max(\mathrm{pushed}[x], \mathrm{own}[x], \max_{h \in \mathrm{hn}[x]} \mathrm{own}[h])$` だった。「$\mathrm{pushed}[x]$・$\mathrm{own}[x]$ と、$h \in \mathrm{hn}[x]$ のすべての $\mathrm{own}[h]$ のうちの最大である」と言葉で分けた
- \substack の行の区切りを `\\[0.3em]` にした：dp/dp-sequence-partition 58、dp/interval-dp-advanced 62。interval-dp-advanced は式が 520px あった（はみ出しの警告）ので、`f = …` と `g = …` を `aligned` で 2 行に積んだ（警告が 1 件減った）
- 作業用フォルダへのビルドで、render_pages の dp・graph のエラーは 0（KaTeX のエラー・地の文の記法・横ずれとも 0）

## #77 表記

prh のエラー 12 か所（dp/cht 3・dp/dp-speedup-overview 2・dp/dynamic-dp 3・dp/exchange-argument-dp 4）と、textlint が見ない front matter の同じ表記（dp/cht の summary、dp/dp-speedup-overview の summary、dp/exchange-argument-dp の signs[2]）を「1 次関数」「1 次式」にした。和文の字に続く所は空白を入れた（「遷移が 1 次関数」「$\lvert x_i - x_j \rvert$ の 1 次式」）。exchange-argument-dp 207 の問題の行（abc366_f）も 1 次関数にした。dp・graph には一次方程式・一次独立・単独の「一次」・二次・Vandermonde の表記はなかった（2 次関数は dp/slope-trick 202 に正しい形である）。

## 残った点

- textlint の警告が 2 件増えた：dp/dp-segment-tree 286 の確認問題の題（KaTeX にして文の長さの数え方が 137 字になった）と、dp/knapsack-undo 109（`$$` の後に `aligned` にした別行の数式を、textlint が 152 字の文と数えた）。どちらも文の長さの警告で、文は変えていない
- 別行の数式のはみ出しの警告（スクロールで読める。エラーではない）は dp・graph に 63 件残る。頼まれた範囲の外なので直していない（dp/dp-phase#counting-phases 410px、dp/dp-sequence-partition#block-index 392px・#agc031_b 441px、dp/interval-dp-advanced#grundy 560px など。全件は作業用フォルダの render-final.json）
- dp/dp-sequence-partition の要点の 4 つ目（`$\sum$（または $\min$）$_{j < i,\ [j, i) \text{ が条件を満たす}}\ \mathrm{dp}[j]$`）は、下付きだけの数式を和文の後に置いた書き方で、描くと添字が前の文字にかからない。検査には当たらないので今回は直していない

## 提案（メインが反映する共有ファイル）

1. 台帳 data/problems.yaml の abc366_f：summary が「N 個の1 次関数」（「の」と「1」の間に空白がない）。alternatives の summary・approach の「1 次関数」も同じ。本文の行（dp/exchange-argument-dp 207）は「N 個の 1 次関数」と書いたので、台帳も空白を入れてそろえる

## 質問（メインに判断してほしい点）

1. knapsack-undo・degree-sqrt の横ずれは、指示では「別行の数式」だったが、render_pages の指摘の元はどちらもインラインの数式だった。インラインの数式を言葉で分ける直し方にした。別行の形（`aligned` で縦に積む）にそろえたいなら知らせてほしい

## 検証の指摘への対応

1. #68 docs/dp/dp-sequence-partition.md 38 行（要点の「いつ使うか」の式）：下付きの部分が単独の数式で Σ にかからず浮き、signs[3] とも形が食い違っていた。signs[3] に合わせて `$\mathrm{dp}[i] = \sum \mathrm{dp}[j]$（または $\min$。$j < i$ で $[j, i)$ が条件を満たすもの）` に直した（指摘の 1 つ目の案）。`updated` はすでに 2026-10-29
   - 確かめたこと：`check_pages.py --page dp-sequence-partition` はエラー 0・警告 0。`npx textlint` はエラー 0（警告 36 件。38 行の「[ の対がない」は半開区間 `[j, i)` によるもので、直す前の式にもあった）
