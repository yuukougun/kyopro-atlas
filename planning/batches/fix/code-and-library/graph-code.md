# graph-code の報告（バッチ code-and-library）

- 担当の Issue：#63（完了）、#53 のうちグラフ・木のページ（完了。bipartite-matching の verify の問題へのリンクは提案に回した）
- 作業ツリー：/home/yuuki/projects/kyopro2/kyopro-atlas-wt/code-and-library（ブランチ feat/code-and-library）。git は読むだけ（status・diff・show）で、commit などはしていない。Issue にはコメント・編集・クローズをしていない。atcoder.jp・codeforces.com は開いていない
- 直したファイル（61）
  - ページ（28）：docs/graph/ の bellman-ford・bipartite-graph・bipartite-matching・degree-sqrt・difference-constraints・dijkstra・euler-path・extended-dijkstra・general-matching・graph-basics・konig-theorem・lowlink・min-cost-flow・minimum-spanning-tree・modular-shortest-path・offline-dynamic-connectivity・project-selection・shortest-path-dag・small-graph-brute-force・steiner-tree・time-dependent-dijkstra・warshall-floyd・zero-one-bfs、docs/tree/ の hld・lca・leaf-first・tree-degree・tree-diameter
  - コード片（33）：snippets/ の bellman-ford/bellman-ford.cpp、bipartite-graph/dsu-double.cpp・.yaml、difference-constraints/max-diff.cpp、dijkstra/dense.cpp・dijkstra.cpp、extended-dijkstra/layered.cpp、general-matching/bitdp.cpp、hld/usage.cpp・.yaml、lca/path-max.cpp、lowlink/lowlink.cpp・.yaml、max-flow/own-dinic.cpp、min-cost-flow/primal-dual.cpp、minimum-spanning-tree/prim-dense.cpp、modular-shortest-path/congruence.cpp・.yaml、offline-dynamic-connectivity/usage.cpp・.yaml、segment-tree-graph/range-edges.cpp、shortest-path-dag/edge-classify.cpp・shortest-path-tree.cpp、small-graph-brute-force/spanning-trees.cpp、spanning-tree-advanced/boruvka.cpp、steiner-tree/steiner.cpp、time-dependent-dijkstra/earliest-arrival.cpp・last-train.cpp、warshall-floyd/add-edge.cpp・wf.cpp・wf.yaml、zero-one-bfs/graph.cpp・turns.cpp
- front matter で変えたのは `updated` だけである。28 ページすべてを 2026-10-29 にした（lowlink・offline-dynamic-connectivity・hld はもとから 2026-10-29）。本文を直していない bellman-ford・difference-constraints・min-cost-flow・small-graph-brute-force も、取り込むコード片の中身（`:core`）が変わったので直した（手引き §2.1）。取り込む範囲が変わったページは、HEAD との差を範囲ごとに比べて洗い出した。stage とほかの項目は変えていない
- 生成物・共有のファイル（用語集・prh.yml・手引き・catalog・台帳・kp.css・viz.js・overrides/main.html）には触れていない。同じ作業ツリーのほかの担当のファイル（ds のコード片・overrides など）にも触れていない

## #63 グラフ・木のコード片の前提（入力の添字・INF）をそろえる（完了）

### 1. 入力を読むコード片は、読んだ直後に 1 を引く

graph/・tree/ の全ページの取り込み（`--8<--`）を範囲ごとに取り出し、範囲の中で `cin` するものを洗い出した。1 を引いていなかった 5 つ（Issue の挙げたものと同じ）をすべて「読んだ直後に 1 を引く」形にし、0-indexed のまま残したものはない。

| コード片（範囲） | 直したこと | 本文 |
| --- | --- | --- |
| warshall-floyd/wf.cpp（core） | `cin >> u >> v >> w;` の直後に `u--, v--;  // 1-indexed → 0-indexed`。先頭のコメントも 1-indexed に | 100 行目に「入力の頂点は 1-indexed で、読んだ直後に 1 を引く。」。199 行目の落とし穴（入力のときに 1 を引くほうが安全）に「（[初期化の節](#init)のコードはこの形）」 |
| lowlink/lowlink.cpp（core） | `a--, b--;` を足した。main の出力（橋の辺の番号・関節点）も start/notation#indexing の「出力するときに 1 を足す」に合わせて 1-indexed にした | 112 行目に同じ 1 文 |
| bipartite-graph/dsu-double.cpp（core） | `u--, v--;` を足した | 122 行目に「次のコードでは、頂点は 0-indexed の $0, \dots, N - 1$ で、入力の 1-indexed の番号は読んだ直後に 1 を引く。」 |
| offline-dynamic-connectivity/usage.cpp（usage） | `if (type != 3) { cin >> u >> v; u--, v--; }`。クエリの種類の番号（0〜3）は添字ではないので変えていない | 90 行目にクエリの形（0 u v・1 u v・2 u v・3）と「頂点は 1-indexed で読んで直後に 1 を引く」 |
| hld/usage.cpp（query） | 種類ごとに読む形にした（`0 v x` は `v--`、`1 u v` は `u--, v--`）。値 `x` は `long long` で読む。main の木の辺の読み込みも 1-indexed にし、先頭に入力の形のコメントを足した | 166 行目に、コード片の説明と「入力の頂点は 1-indexed で、読んだ直後に 1 を引く。」 |

- yaml の cases は、入力の頂点の番号をすべて 1 増やし、期待する出力は同じ答えのまま（lowlink だけは出力の番号も 1 増やした）。コメントの頂点の番号も入力に合わせた（「本文の頂点 v を v + 1 にしたもの」など）
- もとから 1 を引いていたもの：graph-basics/build.cpp・scc/condense-dp.cpp・scc/on-cycle.cpp・tree-imos の 2 つ（`u--, v--`）、connected-components/acl-dsu.cpp（`d.merge(a - 1, b - 1)`）・tree-imos/subtree-add.cpp の 1 か所（`mark[p - 1]`）。後の 2 つは使う所で引く形だが、Issue の背景で「読んだ直後に 1 を引く」側に数えられているので変えていない

### 2. INF を `1LL << 60` にそろえる

**決めた値：`1LL << 60`**。理由は次の 3 つである。

1. リンク先の cpp/cpp-types-literals#inf の表とコード片と確認問題の答えが `1LL << 60` を勧めている（「7 倍まで収まる」）。`LLONG_MAX / 4` は表にないので、選ぶとリンク先と食い違う
2. 本文の勧めのうち graph-basics・warshall-floyd（と flow-lower-bounds）はすでに $2^{60}$ で、こちらにそろえると本文の書き直しが少ない
3. INF + INF でもあふれず、本当の距離の上限（重み $10^9$ の辺が $2 \times 10^5$ 本で $2 \times 10^{14}$）より十分大きい。edge-classify の `ds[a] + w + dt[b]` のように 3 項を足しても収まる

コード片の INF の定義は次のようになった（graph/ のページのコード片すべて。tree/ には INF の定義はない）。

- **`1LL << 60`（コメント「INF + INF でもあふれない大きさ」）**：bellman-ford、difference-constraints、dijkstra の 2 つ、extended-dijkstra、graph-basics、min-cost-flow/primal-dual、minimum-spanning-tree/prim-dense、modular-shortest-path、segment-tree-graph、shortest-path-dag の 2 つ、spanning-tree-advanced/boruvka、steiner-tree、time-dependent-dijkstra/earliest-arrival、warshall-floyd の 2 つ、flow-lower-bounds（容量。もとから）。もとの値は `LLONG_MAX / 4`・`LLONG_MAX`・`numeric_limits<long long>::max()`・`numeric_limits<long long>::max() / 4` だった
- **型の最大値を残したもの（どれも「INF には足さないのでこの値でよい」の理由をコメントに書いた）**
  - zero-one-bfs/graph.cpp・turns.cpp の `INT_MAX`：足すのは取り出した組の距離だけである。本文 116 行目に「INF は `INT_MAX` でよい」の項目を足し、届かない頂点の距離に足す処理を書き加えるならダイクストラ法の落とし穴のとおりにする、と添えた（Issue の「zero-one-bfs に理由がない」への対応）
  - time-dependent-dijkstra/last-train.cpp の `LLONG_MAX`（もとは `2'000'000'000'000'000'000LL`）：終点の締め切り $+\infty$ からは $c$ と $l$ を引くだけで足さない。本文 198 行目の「$+\infty$ は $2 \times 10^{18}$ などにする」も「それより大きくする。引くだけで足さないので `LLONG_MAX` でよい」に直した
- **容量の ∞ として残したもの**：project-selection/builder.cpp・closure.cpp の `1LL << 50`。条件を満たす割り当てがない入力では最小カットに ∞ の辺が何本も入り、$2^{60}$ では 8 本であふれる（$8 \times 2^{60} = 2^{63}$）。ページの落とし穴（249 行目）がもともと $2^{50}$ の理由を書いているので、そこに「距離の INF に使う $2^{60}$ も 8 本で溢れる」とリンクを足した
- **INF ではないが範囲の中に残る型の最大値**にも、足さない理由のコメントを添えた：max-flow/own-dinic.cpp の `dfs(s, t, LLONG_MAX)`（流せる量の上限。min を取るだけ）、small-graph-brute-force/spanning-trees.cpp の `best = LLONG_MAX`、general-matching/bitdp.cpp の `LLONG_MIN`（作れない印。足す前に飛ばす）。min-cost-flow/primal-dual.cpp の main の流量の上限 `LLONG_MAX / 4` も `LLONG_MAX`（引くだけ）にした
- **modular-shortest-path**：`count_upto` が INF を $H$ と比べる（`d[r] <= h`）ので、INF を $2^{60}$ にすると $H \ge 2^{60}$ で作れない余りを数えてしまう。`if (d[r] != INF && d[r] <= h)` と明示して除く形にし、$H = 2 \times 10^{18}$・$a = (2)$ の case を足した（ガードを外すと 1423539247696576514 を出して落ちることを手元で確かめた。正しくは 1000000000000000001）。本文 94 行目に「コード片の ∞ は `1LL << 60` で、$H$ はそれより大きいことがあるので、個数を数えるときは ∞ の余りを先に除く」を足した

本文の勧めと cpp/cpp-types-literals#inf へのリンク：

- graph-basics 137 行目：リンクを足し、「グラフの章のコード片は、距離の INF を `1LL << 60` にそろえている。INF に足さない用途で型の最大値（`INT_MAX` など）を使うコード片には、その理由を書き添えている。」を足した
- warshall-floyd 109 行目：リンクを足した（値はもとから `1LL << 60`）
- dijkstra 206 行目：`LLONG_MAX / 4` を `1LL << 60` にした。このページのコード片は確定した距離にしか重みを足さないが、届かない頂点の距離に足す処理を後で書き加えてもあふれないよう `1LL << 60` にしてある、とリンク付きで書いた
- shortest-path-dag 106 行目（確認問題の答え）：`LLONG_MAX / 4` を `1LL << 60` に
- steiner-tree 118 行目：「$\infty$ を上限の 4 分の 1 程度にする」を「`1LL << 60` のように足してもあふれない値にする」にしてリンク
- zero-one-bfs 116 行目・modular-shortest-path 94 行目・time-dependent-dijkstra 198 行目・project-selection 249 行目：上に書いたとおり

### 3. 10 ページに頂点の添字の 1 文を足す

各ページの図と例の番号の付け方に合わせて書いた（どれも導入の段落か、記号を定める段落の末尾）。

- graph/bipartite-matching 46 行目：「このページでは頂点を 0-indexed で書き、左右の組で別々に 0 から番号を振る（$L_0$・$R_0$ など）。問題文の 1-indexed の番号からは 1 を引いて使う。」
- graph/degree-sqrt 45 行目：「以下、頂点は 0-indexed で $0, \dots, N - 1$ と書き、問題文の 1-indexed の番号からは 1 を引いて使う。」
- graph/euler-path 43 行目：「以下、頂点の番号は 0-indexed で書き（コード片も同じ）、…」（Hierholzer の図は 0〜5）
- graph/extended-dijkstra 57 行目：「このページでは頂点を 0-indexed で書き、…（問題文の頂点 1 は頂点 0 になる）。」（本文の例は「頂点 0 から頂点 N−1」）
- graph/konig-theorem 49 行目：「図では左の頂点を 1〜4、右の頂点を a〜d と呼ぶ。コード片では左右それぞれの頂点を 0-indexed で持ち、…」（図は 1-indexed のラベル）
- graph/project-selection 51 行目：「式では変数を $x_1, \dots, x_N$ と 1 から番号付けし、コード片では 0-indexed で持つ（$x_i$ はコードの `x[i - 1]`、頂点 $i - 1$ に当たる）。」
- graph/shortest-path-dag 45 行目：「コード片は頂点を 0-indexed で持ち、…（問題文の頂点 1 は頂点 0 になる）。確認問題の頂点は 1 から番号付けする。」。あわせて例題 ABC211 D の解法の詳細（203 行目）で、`dist[0] = 0` と並ぶ「頂点 $N$」を「都市 $N$（頂点 $N - 1$）」に直した
- graph/time-dependent-dijkstra 44 行目：「コード片は頂点を 0-indexed で持ち、…。例題の解説は問題文の番号（駅 $1, \dots, N$）のまま書く。」
- tree/leaf-first 44 行目：「例と図は頂点を 1 から番号付けし（問題文と同じ）、コード片は入力から 1 を引いて 0-indexed で持つ（根は頂点 0）。」
- tree/tree-degree 44 行目：「コード片は入力から 1 を引いて 0-indexed の $0, \dots, N - 1$ で持ち、出力するときに 1 を足す。」（式と図は 1〜$N$）

### 4. par と prev をそろえる・lca の path-max の前提

- dijkstra/dijkstra.cpp の `prev` を `par` にした（core と path の範囲、main。9 か所）。手引き §6・§9 と bfs/path.cpp の `par` に合わせた。本文 114 行目の $\mathrm{prev}$ も「親 $\mathrm{par}[to]$」にした。graph/・tree/ のほかのコード片に最短路木の親を `prev` と書くものはない（centroid-decomposition の `prev` は「1 つ前の重心」で別の意味なので変えていない）
- tree/lca 123 行目に「次のコード片は辺の重みを正と仮定し、最大値の単位元に $0$ を使う（パス $u$–$u$ の答えも $0$ になる）。負の重みがありうるなら、単位元を `LLONG_MIN` にする。」を足した。lca/path-max.cpp の build の範囲の `mx[0][0] = 0;` のコメントも「重みは正とするので、最大値の単位元に 0 を使う」にした（前提が `:core` の中にも出る）

### 確かめたこと

- 範囲の中で `cin` するものを、直した後にもう一度すべて取り出し、どれも直後に 1 を引いていることを見た
- INF の定義を graph/・tree/ のコード片で grep し直し、上の一覧のとおりであることを見た
- `uv run mkdocs build -q -d <作業用フォルダ>/site` でビルドし、dijkstra・warshall-floyd・lowlink・bipartite-graph・offline-dynamic-connectivity・hld・zero-one-bfs・lca の HTML のコードの囲みに、直した行（`par[v]`・`u--, v--`・コメント）が出ていることを確かめた

### 残った点

- 取り込む範囲の外（main）で 0-indexed の入力を読むコード片が残っている（difference-constraints・zero-one-bfs・min-cost-flow・steiner-tree・konig-theorem・project-selection/closure・segment-tree-graph・euler-path など）。読者には見えず、Issue の完了の条件（`:core`）の外なので変えていない
- 範囲の外の試験用のコードに `best = LLONG_MAX` などが残る（bottleneck-path/matching.cpp・time-dependent-dijkstra/best-departure.cpp・tree-degree/allocate.cpp・project-selection/builder.cpp の全探索）。INF の定義ではないので変えていない

## #53 名前だけの Library Checker の問題名をリンクにする（グラフ・木のページは完了）

問題名とタイトルは、yosupo06/library-checker-problems の categories.toml と各問題の info.toml（raw.githubusercontent.com と GitHub の API。どちらも付録 B の github 系）で、2026-10-29 に存在とタイトルを確かめた。リンクの文字は info.toml のタイトルにし、サイトの既存のリンク（auxiliary-tree・spanning-tree-advanced など）と同じ文字にそろえた。

- tree/hld：#library の 4 行の一覧（名前だけ）を消し、172 行目を「自作したら、Library Checker で確かめる。使う問題は[練習問題](#practice)の Library Checker の節にまとめた。」にした。`## 練習問題 {#practice}` の「練習の方針」の折りたたみの後に `### Library Checker` を立て、Vertex Add Path Sum・Vertex Add Subtree Sum・Vertex Set Path Composite・Lowest Common Ancestor を judge.yosupo.jp へのリンクで並べた（211〜216 行目。手引き §15-5。並びは spanning-tree-advanced と同じ、方針の後）
- tree/lca 169 行目：lca → [Lowest Common Ancestor](https://judge.yosupo.jp/problem/lca)
- tree/tree-diameter 102 行目：Tree Diameter → リンク（tree_diameter）
- graph/minimum-spanning-tree 84 行目：minimum_spanning_tree → [Minimum Spanning Tree](…/minimum_spanning_tree)
- graph/general-matching 129・134 行目：「General Matching（general_matching）」は正式の題名が **Matching on General Graph** なので、その題名でリンクにした。General Weighted Matching もリンクにした。同じ段落の制約（単純グラフ・$N \le 500$・重み $1$〜$10^6$）は task.md と一致することを確かめた
- graph/bipartite-matching 165 行目：bipartite_edge_coloring → 正式の題名 **Edge Coloring of Bipartite Graph** でリンク
- graph/degree-sqrt 126・152 行目：Enumerate Triangles・Counting C4's → リンク（enumerate_triangles・counting_c4）。Counting C4's の正式の題名は「Counting $C _ 4$'s」だが、参考の節の書き方「Counting C4's」に合わせた

### 残った点

- graph/bipartite-matching は verify が bipartitematching（Matching on Bipartite Graph）だが、本文に名前もリンクもない（Issue の「名前だけの問題名」には当たらないので足していない）。提案 1 を参照

## 検査

- `python3 tools/check_snippets.py`（直した 22 のフォルダ）：コード片 41・期待と違う 0。直す前にも同じフォルダで 33 個を流し、0 だった
- `python3 tools/check_pages.py --page <id>`（直した 28 ページ）：どれもエラー 0・警告 0。`--field graph`・`--field tree` もエラー 0・警告 0
- `npx textlint`（直した 28 ページ）：エラー 0、警告 312。HEAD の版を同じ設定で流すと 313 で、規則ごと・ファイルごとに比べて、増えた警告はない（general-matching の文の長さの警告が 1 つ減った）。途中で出た 2 つ（bipartite-matching の読点と「は」の重なり、steiner-tree の文の長さ）は書き直して消した。残る警告はもとからあるもの
- `python3 tools/gen_site.py --check`（書かない）：docs/llms.txt・overrides/assets/data/graph.json・docs/start/how-to-use.md の版の文字列（ハッシュ）だけが変わる。メインが作り直す
- 問題の行は触っていないので fix_problems は流していない。図は触っていない

## 提案（メインに頼む共有ファイルの変更など）

1. **#53 の bipartite-matching**：verify の Matching on Bipartite Graph へのリンクが本文にない。verify の出し方（overrides/main.html か §15-5 の小見出し）を決めるときに、ページで出すなら `## 練習問題` に `### Library Checker` を立てて [Matching on Bipartite Graph](https://judge.yosupo.jp/problem/bipartitematching) を置く（Hopcroft-Karp・Kuhn の確かめ）
2. **手引き §9（コード片）に INF の決まりを足す**：「グラフの章の距離の INF は `const long long INF = 1LL << 60;  // INF + INF でもあふれない大きさ`。INF に足さない用途で型の最大値を使うときは、その理由をコメントに書く。燃やす埋めるの容量の ∞ は $2^{50}$（project-selection#pitfalls）」
3. **手引き §9 に入力の添字の決まりを足す**：「取り込む範囲で入力を読むなら、読んだ直後に `u--, v--;  // 1-indexed → 0-indexed` と 1 を引く。0-indexed のまま読むなら、取り込む直前の本文に『入力は 0-indexed』と書く」（start/notation#indexing と #63 の決まり）

## 判断してほしい点

1. **INF の種類の数**：コード片の INF は `1LL << 60`（18 ファイル）、足さないので残した `INT_MAX`（zero-one-bfs の 2 つ）と `LLONG_MAX`（last-train）、容量の ∞ の `1LL << 50`（project-selection の 2 つ）になった。完了の条件「1〜2 通り」を「距離の INF は `1LL << 60` の 1 通り、ほかは理由を書いた例外」と読んでよいか。last-train も `1LL << 60` にそろえることはできる（ABC342 E の最も遅い到着は $10^{18} + 10^9$ ほどで $2^{60} \approx 1.15 \times 10^{18}$ に収まる）が、制約に頼る余裕の小さい議論になるので `LLONG_MAX` にした
2. **lowlink の出力**：入力を 1-indexed にしたのに合わせて、コード片の main の出力（橋の辺の番号・関節点）も 1-indexed にした（start/notation#indexing の「出力するときに 1 を足す」）。本文の図の番号（0〜6）とは 1 ずれるが、本文には出力が出ないのでこのままでよいか

## 検証の指摘への対応（2026-10-29）

検証（`verify-graph-code.md`）の「直しが要る点」2 つを、検証の案のとおりに直した。どちらも #63 の点で、本文の INF の記述がコード片の値と合っていなかった（チェックリスト C3）。#53 は合格だったので変えていない。直したのは本文の 2 行だけで、コード片と front matter は変えていない。2 ページとも `updated: 2026-10-29` はもとからある。

| ファイルと行 | 直す前 | 直した後 |
| --- | --- | --- |
| docs/graph/difference-constraints.md 150 行目（落とし穴「届いていない頂点から緩和する」） | 「なお、INF を `LLONG_MAX` にすると足し算であふれるので、`LLONG_MAX / 4` のように余裕を持たせる。」 | 「なお、INF を `LLONG_MAX` にすると足し算であふれるので、`1LL << 60` のように余裕を持たせる（[INF の決め方](../cpp/cpp-types-literals.md#inf)）。」。取り込む max-diff.cpp:core の `const long long INF = 1LL << 60;` と合う |
| docs/graph/time-dependent-dijkstra.md 117 行目（最終電車型の節、コード片の直後の段落） | 「…$c$ や $l$ を引いてもあふれない値にする。上のコードでは $2 \times 10^{18}$ を使っている。」 | 文の前半（$l + (k - 1)d$ の最大より大きく、$c$ や $l$ を引いてもあふれない値にする）は残した。最後の文を「完全なプログラムでは、引くだけで足さないので `LLONG_MAX` を使っている（[INF の決め方](../cpp/cpp-types-literals.md#inf)）。」にした。last-train.cpp 11 行目の `const long long INF = LLONG_MAX;` と、198 行目（例題 ABC342 E の解法の詳細）の記述と合う |

- time-dependent-dijkstra の INF の定義は取り込む範囲（`:core`）の外にあるので、「上のコード」ではなく「完全なプログラム」と書いた。メインが最後に `tools/fix_code_links.py` を流すと、このコードの下に「完全なプログラム：`last-train.cpp`（GitHub）」の行が入り、この段落はその行のすぐ後に続く（`python3 tools/fix_code_links.py --check --page time-dependent-dijkstra` の差分で確かめた。`--check` なので書いていない）。difference-constraints の INF の定義は取り込む範囲（max-diff.cpp の 7〜43 行目）の中にあり、ページのコードに出る
- `LLONG_MAX` でよい理由を確かめた：`latest` の `t - e.c - e.l` は 0 以上の値を引くだけで、`t = LLONG_MAX` でもあふれない。そのとき `i = k - 1` になり、返す `l + (k - 1)d` は制約の範囲（$10^{18}$ 程度）に収まる。INF に足す処理はない

### 確かめたこと

- `grep -rn 'LLONG_MAX / 4\|2 \\times 10^{18}\|4 分の 1\|numeric_limits\|1e18\|0x3f3f3f3f' docs/graph docs/tree`：0 件になった（直す前は difference-constraints 150 行目の 1 件）。`LLONG_MAX`・`INT_MAX`・`10^{18}` を含む本文の行（dijkstra 206・graph-basics 137・zero-one-bfs 116・warshall-floyd 109・shortest-path-dag 103・time-dependent-dijkstra 117・198）も読み直し、取り込むコード片の値と食い違うものはない
- `python3 tools/check_pages.py --page difference-constraints -v`・`--page time-dependent-dijkstra -v`：どちらもエラー 0・警告 0
- `npx textlint`（2 ページ）：エラー 0・警告 18。直す前の版（作業用フォルダに写したもの）も 18 で、規則と行も同じである。time-dependent-dijkstra 119 行目の文の長さの警告は、117 行目の文字が増えた分だけ列の位置がずれただけである。直した 2 行に警告はない
- `python3 tools/check_snippets.py snippets/difference-constraints snippets/time-dependent-dijkstra`：コード片 4・期待と違う 0（コード片は変えていないが、本文が述べる値のコードが動くことを確かめた）
- `python3 tools/fix_problems.py --check --page <id>`（2 ページ）：直すべき行 0
- `uv run mkdocs build --strict -q -d <作業用フォルダ>/site`：警告なしで通った（終了コード 0）。ビルドした HTML に直した 2 つの文があり、リンクが `../../cpp/cpp-types-literals/#inf` になること、リンク先に `id="inf"` があることを確かめた。2 ページの HTML に `LLONG_MAX / 4` と `2 \times 10^{18}` は残っていない
- `python3 tools/gen_site.py --check`：docs/llms.txt・overrides/assets/data/graph.json・docs/start/how-to-use.md が変わる（検証のときと同じ 3 つ。メインが作り直す）

### 検証の推奨について

検証の「推奨」1〜3（graph/segment-tree-graph 86 行目の「Shortest Path」のリンク、tree/hld の #library に検証問題の名前とリンクを残す案、graph/extended-dijkstra 57 行目の宣言に「練習の方針は問題文の番号のまま書く」を添える案）は、メインの判断とされているので変えていない。どれも docs/graph・docs/tree のページなので、直すと決まればこの担当の範囲で直せる。
