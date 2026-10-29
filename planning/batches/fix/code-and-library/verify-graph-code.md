# graph-code の直しの検証（バッチ code-and-library、2026-10-29）

- 検証したもの：graph-code の報告（`graph-code.md`）にある 61 ファイル（docs/graph の 23 ページ・docs/tree の 5 ページ・snippets の 33 ファイル）の、HEAD との差分
- 作業ツリー：/home/yuuki/projects/kyopro2/kyopro-atlas-wt/code-and-library（feat/code-and-library）。ファイルは直していない。git は読むだけで使った。Issue にはコメント・編集・クローズをしていない。atcoder.jp・codeforces.com は開いていない
- 作業用フォルダ：/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/7a638398-7759-4637-95c7-6739e8d52414/scratchpad/fix/code-and-library/verify-graph-code（ビルドしたサイト・試験用のスクリプト・スクリーンショット）
- コンパイラ：`g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0`

## 結果

| Issue | 判定 | 直しが要る点 |
| --- | --- | --- |
| #63 グラフ・木のコード片の前提（添字・INF） | 直しが要る | 2 |
| #53 Library Checker の問題を開けるようにする（グラフ・木のページ） | 合格 | 0 |

## #63：直しが要る

完了の条件の 3 つ（`:core` の入力の添字・INF の定義・10 ページの添字の宣言）は満たしている。ただし、INF の値を変えたコード片について、本文の記述が古いまま残る箇所が 2 つある（チェックリスト C3 本文との一致）。

### 直しが要る点

1. **docs/graph/difference-constraints.md 150 行目**（落とし穴「届いていない頂点から緩和する」）
   - 理由：本文は「INF を `LLONG_MAX` にすると足し算であふれるので、`LLONG_MAX / 4` のように余裕を持たせる」と勧めている。しかし取り込むコード片 `difference-constraints/max-diff.cpp:core` は `const long long INF = 1LL << 60;` に変わった。Issue の背景にある「本文の勧めが $2^{60}$ と `LLONG_MAX / 4` に分かれる」状態が、このページだけ残っている。graph/ と tree/ の本文で `LLONG_MAX / 4` を勧める箇所は、ここだけである（`grep -rn 'LLONG_MAX / 4' docs/graph docs/tree`）
   - 直し方の案：「なお、INF を `LLONG_MAX` にすると足し算であふれるので、`1LL << 60` のように余裕を持たせる（[INF の決め方](../cpp/cpp-types-literals.md#inf)）。」にする
2. **docs/graph/time-dependent-dijkstra.md 117 行目**（最終電車型の節、コード片の直後の段落）
   - 理由：「上のコードでは $2 \times 10^{18}$ を使っている」とあるが、`time-dependent-dijkstra/last-train.cpp` の INF は `LLONG_MAX` に変わった（11 行目）。担当は 198 行目（例題 ABC342 E の解法の詳細）は直したが、この行は直していない。なお、INF の定義は取り込む範囲（13〜43 行目）の外にあり、ページのコードには出ない
   - 直し方の案：同じ文の前半（「$l + (k - 1)d$ の最大（$10^{18}$ 程度）より大きく、$c$ や $l$ を引いてもあふれない値にする」）は残す。最後の文を「完全なプログラムでは、引くだけで足さないので `LLONG_MAX` を使っている（[INF の決め方](../cpp/cpp-types-literals.md#inf)）。」にする

### 合格と確かめたこと

- **入力の添字**：graph/・tree/ の全ページの取り込み（`--8<--`）を範囲ごとに取り出し、範囲の中で `cin >>` するものを洗い出した（作業用フォルダの `scripts/cin_in_ranges.py`）。16 か所のうち、頂点を読む 13 か所はどれも、読んだ直後に 1 を引くか（`u--, v--`）、使う所で 1 を引く（`d.merge(a - 1, b - 1)`・`mark[p - 1]`）。残る 3 か所はクエリの種類を読むもので、添字ではない。0-indexed のまま頂点を読む範囲は残っていない
- **1-indexed の入力での動作**：入力を読む 5 つのコード片を `-fsanitize=address,undefined -D_GLIBCXX_DEBUG` でコンパイルし、自作の 1-indexed の乱数の入力（頂点 $N$ を含む）で Python の素朴な方法と比べた。wf.cpp（負の辺・負閉路・多重辺・自己ループ）・lowlink.cpp（出力の辺の番号と関節点も 1-indexed）・dsu-double.cpp・offline-dynamic-connectivity/usage.cpp は各 400 件、hld/usage.cpp は 300 件で、すべて一致した。範囲外の参照やサニタイザのエラーはない（`scripts/rand1.py`・`scripts/rand_hld.py`）
- **yaml の cases**：直した yaml の期待出力を手で確かめた。lowlink の本文の図は、橋が 4 本目と 8 本目（`2 4 8`）、関節点が 2・4・6。dsu-double の 5 本目の辺 1-3 で `No`。hld の 3 つ目の case は 2・6・9。wf.cpp の本文の例は、頂点 $v$ を $v + 1$ にした辺である
- **INF のあふれ**：INF の値を変えた 15 ファイル（`1LL << 60` にした 14 と last-train）と、コメントだけ足した wf.cpp・add-edge.cpp の足し算を 1 つずつ読んだ
  - 先に INF を飛ばすもの：bellman-ford・max-diff・dense・steiner・edge-classify・add-edge・wf。edge-classify の 3 項の和も、INF の項を先に除いている
  - 取り出した有限の距離にだけ足すもの：dijkstra・layered・earliest-arrival・range-edges・shortest-path-tree・primal-dual・congruence
  - INF に足さないもの：prim-dense・boruvka・last-train
  - modular-shortest-path：INF を $2^{60}$ にしたため、$H \ge 2^{60}$ で作れない余りを数える誤りが生じうる。これは `d[r] != INF` のガードと $H = 2 \times 10^{18}$ の case で防いでいる。本文 94 行目にも理由がある。本当の $d[r]$ は本文の見積もりで $m \cdot \max_j a_j$ 程度なので、$m$ と $a_j$ が $10^6$ 程度までなら $10^{12}$ 程度で、$2^{60}$ には届かない
  - primal-dual の `flow(s, t, LLONG_MAX)`：`limit - f` を引くだけで、`f += add` も `limit` を超えない。ACL の `mcf_graph::flow` の既定（型の最大値）とも同じになった
  - last-train の `LLONG_MAX`：`t - e.c - e.l` は 0 以上の値を引くだけで、あふれない
  - 直した 27 のコード片を、サニタイザ付きで yaml の cases で動かした（`scripts/san_cases.py`）。すべて一致し、未定義動作の報告はない
- **INF の種類**：graph/・tree/ のコード片の INF の定義は、`1LL << 60`（18 ファイル。コメント「INF + INF でもあふれない大きさ」）・`INT_MAX`（zero-one-bfs の 2 つ）・`LLONG_MAX`（last-train）・`1LL << 50`（project-selection の 2 つ。容量の ∞）になった。型の最大値には、どれも「足さないのでこの値でよい」の理由がコメントにある。容量の $2^{50}$ の理由は、project-selection の落とし穴にある。Issue の「やること」も INT_MAX・LLONG_MAX を理由付きで残すことを認めているので、「距離の INF は 1 通り、ほかは理由を書いた例外」と読む担当の判断に賛成する（判断はメイン）。取り込む範囲の外の試験のコード（bottleneck-path/matching.cpp など）に残る `LLONG_MAX` は、ページに出ない
- **本文の勧めとリンク**：graph-basics・warshall-floyd・dijkstra・shortest-path-dag・steiner-tree・zero-one-bfs・modular-shortest-path・time-dependent-dijkstra（198 行目）・project-selection の記述が、コード片の値と合い、`../cpp/cpp-types-literals.md#inf`（reviewed、anchor あり）へリンクしている。zero-one-bfs の「INF は `INT_MAX` でよい」の理由（足すのは取り出した有限の $d$ だけ）は、graph.cpp と turns.cpp のコードと一致する。dijkstra の「このページのコード片は確定した距離にしか重みを足さない」も、dijkstra.cpp・dense.cpp の両方で正しい
- **10 ページの添字の宣言**：10 ページすべてに 1 文がある。各ページの図・例・コード片と照らした
  - bipartite-matching：図は L0・R0
  - konig-theorem：図は 1〜4・a〜d で、cover.cpp は左右とも 0-indexed
  - project-selection：builder.cpp で変数 $i$ は頂点 $i$
  - shortest-path-dag：確認問題は 1 から番号付けで、ABC211 D の「都市 $N$（頂点 $N - 1$）」も正しい
  - leaf-first：path-split.cpp の根は 0 で、例「根 1 と子 2」は 1 から番号付け
  - tree-degree：pruefer.cpp・from-degrees.cpp は読んで 1 を引き、出すときに 1 を足す
  - euler-path・degree-sqrt・extended-dijkstra・time-dependent-dijkstra も、図とコード片の番号と食い違わない
- **par と prev**：dijkstra.cpp の `prev` は 9 か所とも `par` になり、本文 114 行目の「親 $\mathrm{par}[to]$」と合う。graph/・tree/ のコード片に、最短路木の親を `prev` と書くものは残っていない
- **lca の前提**：本文 123 行目と `:build` の中のコメントの両方に「重みは正、最大値の単位元に 0」がある。`path_max(u, u)` が 0 を返すことも、コードと合う
- **lowlink の出力（担当の判断してほしい点 2）**：start/notation#indexing の「頂点：読み込んだ直後に 1 を引く。出力するときに 1 を足す」に合う。本文に出力の形は出ず、本文の「辺 0・辺 1」はコードの内部の番号の話なので、食い違わない。このままでよいと考える

## #53（グラフ・木のページ）：合格

- Issue が「名前だけでリンクのない箇所」に挙げた 7 ページは、すべて judge.yosupo.jp へのリンクになった（tree/hld・tree/lca・tree/tree-diameter・graph/minimum-spanning-tree・graph/general-matching・graph/bipartite-matching・graph/degree-sqrt）
- リンクにした 11 問と、bipartite-matching の verify の bipartitematching は、yosupo06/library-checker-problems の categories.toml に問題名があることを確かめた（raw.githubusercontent.com。付録 B にある）。各問題の info.toml の title も、リンクの文字と一致した。lca → Lowest Common Ancestor、general_matching → Matching on General Graph、bipartite_edge_coloring → Edge Coloring of Bipartite Graph など。degree-sqrt の「Counting C4's」だけは正式の題名「Counting $C _ 4$'s」の書き換えで、参考の節の書き方に合わせたと担当が断っている。URL はどれも `https://judge.yosupo.jp/problem/<名前>` の形である。general-matching の制約の記述（単純グラフ・$N \le 500$・重み $1$〜$10^6$）も task.md と一致した
- hld の Library Checker の一覧は、`## 練習問題 {#practice}` の `### Library Checker` に移った（手引き §15-5。spanning-tree-advanced と同じ並び）。#library からは `#practice` へリンクしている
- ビルドした HTML で、verify を持つ graph/・tree/ の 27 ページすべてに、verify の問題への judge.yosupo.jp のリンクがあることを確かめた。発展の概要（hld・general-matching など）は本文のリンクで、それ以外は別の担当が変えた `overrides/main.html` の「自作の確認」の行で満たす。bipartite-matching の bipartitematching も、この行に出る（担当の提案 1 は、ページに出すなら任意）

## 検査（書き換えないもの）

- `python3 tools/check_snippets.py snippets/<22 フォルダ>`：コード片 41・期待と違う 0
- `python3 tools/check_pages.py --page <id> -v`（28 ページ）：どれもエラー 0・警告 0。`--field graph`・`--field tree` もエラー 0・警告 0
- `python3 tools/fix_problems.py --check --field graph`・`--field tree`：直すべき行 0
- `npx textlint`（28 ページ）：エラー 0・警告 312。HEAD の版（作業用フォルダに取り出し、同じ設定）は 313 で、規則とファイルごとに比べて増えた警告はない（general-matching の文の長さが 1 減った）
- `python3 tools/gen_site.py --check`：docs/llms.txt・overrides/assets/data/graph.json・docs/start/how-to-use.md が変わる（updated と版の文字列。メインが作り直す）
- `uv run mkdocs build --strict -d <作業用フォルダ>/site-strict`：警告なしで通った。新しいリンクの anchor（`cpp-types-literals#inf`・`dijkstra#pitfalls`・`hld#practice`・`warshall-floyd#init`）は、ビルドした HTML に id がある
- 表示：作業用フォルダで `python3 -m http.server 38517` を立てた。28 ページをヘッドレスの Chrome（幅 390px）で開いて描画後の DOM を取り、KaTeX の要素はあるが `katex-error` は 0 だった。tree/hld の練習問題〜Library Checker の節を、幅 390px のライトとダークで撮って見た（`shots/hld-full-light-b.png`・`hld-full-dark-b.png`）。崩れはない。サーバは止めた
- updated：28 ページとも 2026-10-29。取り込む範囲の中身が変わったページは、範囲ごとに HEAD と比べて洗い出した（`scripts/range_changes.py`）。max-flow（own-dinic.cpp:core にコメントが 1 行増えた）だけは担当の一覧にないが、HEAD でもう 2026-10-29 なので直す必要はない。front matter で変わったのは updated だけである

## 推奨（直さなくても完了の条件は満たす。メインの判断）

1. graph/segment-tree-graph.md 86 行目の「Shortest Path」は、ページのどこにもリンクのない Library Checker の問題名である（verify はなく、担当の範囲のファイルでもない）。#53 の趣旨に合わせるなら `[Shortest Path](https://judge.yosupo.jp/problem/shortest_path)` にする（modular-shortest-path 98 行目と同じ形）
2. tree/hld.md 172 行目の #library は、問題名を練習問題へ移したので、節だけを読むと何で確かめるかが分からない（手引き §1、clarity U6）。同じ形の発展の概要の dynamic-tree は、#library の中にリンク付きの一覧を置いている。検証問題だけでも名前とリンクを残す案がある。例：「このページの検証問題は [Vertex Set Path Composite](…)。ほかの問題は練習問題の Library Checker の節にまとめた。」
3. graph/extended-dijkstra.md 57 行目の宣言は「このページでは頂点を 0-indexed で書き」とページ全体に言う。一方、練習の方針（365・382 行目）は問題文の番号（研究者 1・駅 1・駅 $N$）で書いている。time-dependent-dijkstra と同じように「練習の方針は問題文の番号のまま書く」と添えると、食い違って見えない
