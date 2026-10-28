# graph-ds の報告（バッチ minor-content）

- 担当の Issue：#21・#22・#23・#24・#26・#27・#28・#29・#30・#19（#19 は segment-tree-on-values の分だけ。alien-dp・cht は担当の外）
- 作業ツリー：/home/yuuki/projects/kyopro2/kyopro-atlas-wt/minor-content（ブランチ fix/minor-content）。git は読むだけで、commit などはしていない
- 直したファイル：docs/graph/namori-graph.md、docs/graph/lowlink.md、docs/tree/centroid-decomposition.md、docs/graph/scc.md、docs/ds/union-find.md、docs/ds/fenwick-tree.md、docs/ds/sweep-line-2d.md（#27 の 85 行目と updated だけ）、docs/ds/kth-element.md、docs/ds/segment-tree-on-values.md、docs/ds/lazy-segment-tree-patterns.md、docs/ds/advanced-ds-catalog.md、docs/ds/segment-tree-monoids.md、data/problems.yaml（abc309_f と abc283_f の pages の 1 行ずつ）
- front matter：12 ページすべての `updated` を 2026-10-29 にした（namori-graph は本文を変えていないが、chapter と order が変わったので合わせた）。頼まれた項目のほかに変えたのは、segment-tree-on-values の `related` から fenwick-tree を外したことだけである（理由は #19 の節。判断してほしい点 2）。stage は変えていない
- 生成物（nav.yml・docs/graph/index.md・docs/lists/・llms.txt など）と、gen:begin〜gen:end の中には触れていない。`tools/gen_site.py` は `--check --diff` だけを流した

## #21 なもりグラフを無向グラフの章へ（完了）

- **場所**：docs/graph/namori-graph.md 7〜8 行目（front matter）
- **直した内容**：`chapter: 有向グラフ`・`order: 270` → `chapter: 基本と探索`・`order: 75`。基本と探索の章は 10〜100（cycle-detection が 70、bipartite-graph が 80）なので、前提の閉路の検出の直後に入る。前提の connected-components（60）・cycle-detection（70）より後ろで、「同じ分野の前提が後ろ」の警告は出ない。namori-graph を前提に持つページはない
- **確かめたこと**：`python3 tools/gen_site.py --check --diff`（書かない）で、nav.yml の「基本と探索」で「閉路の検出と復元」の次に「なもりグラフ」が入り、「有向グラフ」から消えること、docs/graph/index.md の表も同じ位置に移ることを見た。id・URL・sections は変えていない。有向版とのつながり（#directed-version と related の functional-graph）はそのまま
- **残った点**：nav と分野の入口などの生成物は、メインが gen_site で作り直す

## #22 lowlink のブロックカット木の節の位置（完了）

- **場所**：docs/graph/lowlink.md 170〜181 行目（移した後）
- **直した内容**：`## 二重頂点連結成分とブロックカット木 {#block-cut-tree}` の節（12 行）を、使い分けの後・参考の前から、#vs-scc の後・落とし穴の前へ移した。中身と anchor は変えていない。front matter の sections はもとから #vs-scc の次なので変えていない
- **確かめたこと**：節の冒頭「この節は発展の内容で、ここまでの関節点の条件を前提にする」は、新しい位置でも前の節（#conditions など）を指して通じる。練習の節の「[ブロックカット木の節](#block-cut-tree)」もそのまま届く。作業用フォルダへのビルドで、#vs-scc → #block-cut-tree → #pitfalls の順に出ることを HTML で確かめた

## #23 重心分解の落とし穴のリンク先（完了）

- **場所**：docs/tree/centroid-decomposition.md 184 行目
- **直した内容**：`（[木の基本](../tree/tree-basics.md)）` → `（[BFS 順の逆で集約する](../tree/tree-traversal.md#bfs-order)）`。リンクの文字は、tree-imos・tree-centroid・leaf-first など、同じ節へリンクするほかのページと同じにした
- **確かめたこと**：tree-traversal に `## BFS 順の逆で再帰を使わずに集約する {#bfs-order}` があり（sections にもある）、check_pages の anchor の検査が通る

## #24 SCC の冒頭の推移性の重複（完了）

- **場所**：docs/graph/scc.md 51 行目
- **直した内容**：「互いに行き来できることを $u \leftrightarrow v$ と書く。どの頂点も自分自身とは行き来できるとみなす。…（推移的である）。この関係は自分自身とも成り立ち、向きを入れ替えても同じで、推移的である。」を、「互いに行き来できることを $u \leftrightarrow v$ と書き、どの頂点も自分自身とは行き来できるとみなす。この関係は、$u \leftrightarrow u$（反射律）、$u \leftrightarrow v$ なら $v \leftrightarrow u$（対称律）、$u \leftrightarrow v$ かつ $v \leftrightarrow w$ なら $u \leftrightarrow w$（推移律）の 3 つを満たす。」にした。3 つの性質が 1 文にまとまり、推移性は 1 回だけになった
- **確かめたこと**：律の呼び方は用語集の半順序（「反射律・反対称律・推移律」）にそろえた。続く「よって頂点全体は重なりのないグループに分かれる」はそのまま
- **残った点**：この文は数式の LaTeX の文字数で textlint の文の長さの警告（171 字）になる。描画した長さは 60 字ほどで、§13-8 の数式による誤検出として残した

## #26 Union-Find の merge の返り値と使い分けの行き止まり（完了）

Issue の (a)（違いを書く）で直した。snippets/union-find/ の自作の `merge` は変えていない。

- **場所と直した内容**
  - 121 行目（ACL の囲みの 2 段落目を足した）：「`d.merge` の返り値は自作の `merge`（併合したら `true`）と意味が違い、`if (d.merge(a, b))` は代表元が 0 かどうかを見るだけで、併合できたかの判定にならない。併合できたかは、先に `d.same(a, b)` で調べる（[境界の節](#boundaries)のコード）。」の 2 文。境界の節のコード（acl-cycle.cpp）は、もとから `same` で調べてから `merge` を呼ぶ形である
  - 168 行目（#size-and-edges）：「（ACL では `merge` の返り値）」の括弧を、「ACL では `merge` の返り値が新しい根である。自作の `merge`（[各操作の手順](#operations)のコード）は併合できたかの `bool` を返すので、併合のあとで $\mathrm{find}(a)$ を呼んで新しい根を求める。」に書き分けた。自作のコードのまま読む人が、新しい根の受け取り方で迷わないようにするためである。手引き §3 に合わせ「上の」は使っていない
  - 189 行目（使い分け）：「追加と削除が入り混じるなら発展の手法を使う」→「追加と削除が入り混じるなら、発展の[辺の追加と削除が混ざる連結性](../graph/offline-dynamic-connectivity.md)の方法を使う（これも先読みが前提で、部品は[ロールバックできる Union-Find](../ds/rollback-union-find.md#offline-dynamic-connectivity)）」
- **確かめたこと**：ACL v1.6 の document_ja/dsu.md で、`merge` は「連結だった場合はその代表元、非連結だった場合は新たな代表元を返す」ことを確かめた。rollback-union-find に `#offline-dynamic-connectivity` の節があることを確かめた。作業用フォルダへのビルドで、足した段落が ACL の囲みの中に出ることを HTML で確かめた。ACL の囲みの 2 段落目は textlint が見ないので、だ・である調と空白を目で確かめた

## #27 BIT の閉区間 [0, A_i]（完了）

すべて半開区間に書き直した（手引き §6 の基本の形。すぐ下のコードの `sum(0, id + 1)` とそのまま対応する）。

- docs/ds/fenwick-tree.md 146 行目：「BIT の $[0, A_i]$ の和を読む」→「BIT の $[0, A_i + 1)$ の和（`sum(0, A_i + 1)`）を読む」
- 同 159 行目：「これまでの個数 − $[0, \mathrm{id}]$ の和」→「これまでの個数 − $[0, \mathrm{id} + 1)$ の和」。同じ行の「$A_j < A_i$ なら $[0, \mathrm{id})$」と形がそろった
- 同 218 行目（落とし穴）：「足してから $[0, A_i]$ を読むと」→「足してから $[0, A_i + 1)$ を読むと」
- docs/ds/sweep-line-2d.md 85 行目：「BIT の $[0, y_i]$ の和を読めばよい」→「BIT の $[0, y_i + 1)$ の和を読めばよい」（この行と updated だけを変えた）
- docs/ds/kth-element.md 142 行目（ACL の囲み）：「$[0, r]$ の和が $k$ 以上になる位置」→「$[0, r + 1)$ の和が $k$ 以上になる位置」
- docs/ds/segment-tree-on-values.md 124 行目：「$[0, r]$ まで広げると」→「$[0, r + 1)$ まで広げると」
- **確かめたこと**：fenwick-tree の count-by-value.cpp の `cnt.sum(0, id + 1)` と、kth-element・segment-tree-on-values の `max_right` の返り値の約束（$[0, r)$ が条件を満たす最大の $r$）と合う
- **残った点（担当の外として直していない）**：Issue の挙げた箇所のほかにも、「閉区間」と断らない閉区間がある。fenwick-tree 82・300 行目（内部の 1-indexed の箱の説明 $[1, 7]$・$[1, 13]$）と 244 行目（問題文の $[x, y]$）、segment-tree-on-values 199 行目（ABC339 E の $[A_i - D, A_i + D]$。解法の詳細では半開区間に直している）、sweep-line-2d 39・122・128・134・147・162・247 行目（問題文の区間 $[p, q]$・$[L, R]$ や、位置の軸の範囲 $[x - W + 1, x]$ など）。どれも BIT の $[0, A_i]$ とは別の話なので触れていない。そろえるなら #77（表記）などでまとめて扱うのがよい

## #28 遅延セグメント木の載せ方の型の max_right（完了）

- **場所**：docs/ds/lazy-segment-tree-patterns.md 72 行目（ACL の囲み）
- **直した内容**：「`seg.max_right<g>(l)`・`seg.min_left<g>(r)` で、…」→「`seg.max_right(l, f)`・`seg.min_left(r, f)` で、遅延セグメント木の上の二分探索もできる（[遅延セグメント木の上で使う](../ds/segment-tree-binary-search.md#on-lazy-segment-tree)）。この `f` は作用ではなく `S` を受け取って `bool` を返す判定の関数で、外の変数を参照するラムダでよい。要件は[セグメント木上の二分探索](../ds/segment-tree-binary-search.md#what-it-does)の ACL の囲みと同じである。」
- **理由**：同じ囲みの `seg.apply(l, r, f)` の `f` は作用なので、Issue の指定どおり `f` と書いたうえで、判定の関数であることを 1 文で断った（サイトのほかの箇所はどれも `max_right(l, f)` の `f` を判定の関数に使っている）
- **確かめたこと**：ACL v1.6 の document_ja/lazysegtree.md に `seg.max_right<G>(int l, G g)`（関数オブジェクトを渡す形）があることを確かめた。segment-tree-binary-search の 88 行目の ACL の囲みの約束（$f(e())$ が真・副作用がない）と合う

## #29 見慣れないデータ構造のページの節の並び（完了）

- **場所**：docs/ds/advanced-ds-catalog.md 19〜21 行目（sections）と本文の 40〜91 行目
- **直した内容**：`## ほかのページにあるもの（…） {#elsewhere}` の節（3 つの表、52 行）を、確認問題の前から、最初の節（#table の前）へ移した。front matter の sections の並びも elsewhere → table → meldable-heap にした。anchor と節の中身は変えていない
- **確かめたこと**：要点の「使い方」（まず #elsewhere の表、なければ #table）が節の並びと合う。#table の表の「併合可能なヒープ」の行の「[次の節](#meldable-heap)」は、並べ替えた後も次の節を指す。作業用フォルダへのビルドで、#elsewhere → #table → #meldable-heap の順を HTML で確かめた

## #30 セグメント木に何を載せるかの練習 2 問を移す（完了。台帳の 1 件は提案）

- **台帳**：data/problems.yaml の abc283_f（8767 行目）と abc309_f（9965 行目）の pages を `{id: segment-tree-monoids, role: practice}` → `{id: segment-tree-on-values, role: practice}` にした。ほかの項目は変えていない
- **segment-tree-on-values**：練習の囲みに ABC309 F・ABC283 F の行を足し、易しい順（ABL D 1283・ABC276 F 1562・ABC309 F 1619・ABC283 F 1771）に並べた。方針の折りたたみに 2 問の方針を移した。ABC309 F は「今の箱の $y$ の添字を $\mathrm{id}$ とすると、$[0, \mathrm{id})$（$y$ が真に小さい箱）の $z$ の最小値が…」と半開区間で書き、自分自身へのリンク（値を添字にする BIT・セグメント木）は外した。ABC283 F は「値 $P_j$ を添字にした最小値のセグメント木を…」とした。参考に、2 問の出典（ZOI_dayo・Bellala。題名は segment-tree-monoids にあったものと同じ）を移した
- **segment-tree-monoids**：練習の囲みから 2 問を外し、方針の「ABC309 F・ABC283 F は…値そのものを載せる型で足りる」の行と 2 問の方針、参考の 2 件を消した
- **補った問題**：台帳の確認済みの問題から、要約を足す型で、まだこのページにないものを探した（approach・alternatives を機械的に検索し、候補を読んだ）。合うのは abc467_f（ABC467 F. Email Scheduling Optimization、diff 2052、確認済み。今は exchange-argument の力試し）だけだった。ノードに（$A$ の和, 自分までの $A$ の和 $+ B_i$ の最大）を持ち、括弧列の（合計, 最小接頭和）の min を max に替えた式で結ぶ型で、このページの主題にそのまま当たる。これを練習の 2 問目に足し、方針の折りたたみと参考（ikatakos の ABC467 の記録。題名は exchange-argument の参考と同じ）を書いた。行は `- abc467_f：要約` と書いて `python3 tools/fix_problems.py --page segment-tree-monoids` で label・URL・diff を埋めた。要約は台帳の summary のままである
  - ほかの候補を外した理由：abc403_g（個数・奇数番目の和・偶数番目の和）は動的セグメント木が主で、すでに segment-tree-on-values の力試し。abc322_f（連続する 1）は遅延セグメント木が要り、lazy-segment-tree-patterns の例題。abc157_e（OR の bit 集合）は segment-tree の例題。abc476_e（値と位置）は diff 964 で易しすぎる。abc254_f（gcd）は値そのものを載せる型
  - 台帳の abc467_f の pages はメインに提案する（直してよい台帳の項目は abc309_f と abc283_f だけのため）。役割は判断してほしい点 1
- **確かめたこと**：`python3 tools/ap.py show` で abc467_f（2052）・abc309_f（1619）・abc283_f（1771）・abc331_f（1666）の題名と difficulty を確かめた。ABC467 F の方針は、exchange-argument の力試しの方針と、台帳の evidence の ikatakos の記録（https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2026/0718_abc467 。付録 B のドメイン。WebFetch で F の解法の部分だけを要約させ、問題文の節は読んでいない）で確かめた：$B$ の降順が最適（隣どうしの交換）、$B$ をクエリまで先読みして座標圧縮、同じ $B$ は 1 つの葉に $A$ の和をまとめる、空の葉は寄与なし、全体 $O((N + Q) \log (N + Q))$。ikatakos は $B$ の昇順に並べて $\max(\text{左の最大} + \text{右の和}, \text{右の最大})$ で結んでおり、本文の降順の式と同じものである
- `python3 tools/fix_problems.py --check --page segment-tree-monoids --page segment-tree-on-values` は直すべき行 0・台帳にあって本文にない 0

## #19 前提の過不足（segment-tree-on-values の分は完了。alien-dp・cht は担当の外）

- **場所**：docs/ds/segment-tree-on-values.md 11〜12 行目（front matter）・44 行目（要点の前提）
- **直した内容**：`prerequisites: [segment-tree, coordinate-compression]` → `[fenwick-tree, segment-tree, coordinate-compression]`（題名「値を添字にする BIT・セグメント木」の順）。要点の前提を「[BIT（Fenwick Tree）](../ds/fenwick-tree.md)、[セグメント木](../ds/segment-tree.md)、[座標圧縮](../basics/coordinate-compression.md)」にした（リンクの文字はほかのページの前提の書き方にそろえた）
- **related から fenwick-tree を外した**：check_pages は「前提と related の重複」を警告する。前提に足すと前提と関連の両方に BIT が出るので、related から外した（Issue が alien-dp・cht で求める「related に移す」の逆向きの移動と同じ扱い）。判断してほしい点 2
- **確かめたこと**：fenwick-tree は同じ分野で order 150（このページは 200）、レベルは水どうしなので、「同じ分野の前提が後ろ」「前提のレベルが高い」は出ない。推移的に冗長な前提の警告も出ない（全ページの check_pages でエラー 0・警告 0）。`python3 tools/frequency.py --check` で、fenwick-tree が「前提として 16 ページに届く（直接 6）」になることを見た（提案 2）
- **残った点**：fenwick-tree の「次に読む」と知識マップ・ロードマップは、メインの gen_site の作り直しで反映される

## 検査の結果

- `python3 tools/check_pages.py --page <id>`：12 ページすべてエラー 0・警告 0（直す前も 0・0）。全ページ（353）でもエラー 0・警告 0（ほかの担当の直しが入った状態で）
- `python3 tools/fix_problems.py --check --page segment-tree-monoids --page segment-tree-on-values`：直すべき行 0・直せない行 0・台帳にあって本文にない 0
- `npx textlint`（12 ファイル）：エラー 0。警告は 194 → 207。増えたのは次の誤検出だけである
  - 半開区間 $[0, x + 1)$ の `[` に対の `]` がない（no-unmatched-pair）：fenwick-tree 3・kth-element 1・sweep-line-2d 1・segment-tree-on-values 2。textlint は数式の中も文として読む（§13-8）
  - その `[` のせいで文の区切りがずれ、後ろの文までつながった長い文（sentence-length）：fenwick-tree 159 行目・kth-element 142 行目・sweep-line-2d 85 行目・segment-tree-on-values 124・231 行目
  - 数式の LaTeX の文字数による長い文：scc 51 行目（171 字）。segment-tree-on-values の要点（前提に BIT を足して 130 → 148 字。囲みの中は箇条書きにならず 1 段落と読まれる）
  - 折りたたみの箇条書き（句点で終わらない既存の書き方）がつながった文：segment-tree-monoids の練習の方針（192 字。直す前は同じ場所で 274 字）。ABC467 F の行（140 字。台帳の summary が長い）
- `python3 tools/gen_site.py --check --diff`（書かない）：nav.yml・docs/graph/index.md・一覧・llms.txt などに差分が出る（メインの作り直し待ち。namori-graph の移動は意図どおり）
- 作業用フォルダへのビルド（`uv run mkdocs build -q -d <作業用フォルダ>/site`）：エラーなし。union-find の ACL の囲み、lowlink と advanced-ds-catalog の節の順、2 ページの練習の行・方針・リンクの描画を HTML で確かめた
- コード片と図は触っていないので、check_snippets・check_svg は流していない

## 提案（メインに頼む共有ファイルの変更）

1. **台帳**：data/problems.yaml の abc467_f の pages に `- {id: segment-tree-monoids, role: practice}` を足す（根拠：evidence の ikatakos の記録。approach の「B を座標圧縮したセグメント木に（A の和, その最大）を載せて」がこのページの型。役割は判断してほしい点 1）。本文の行はもう足してある
2. **frequency_evidence**：台帳を直した後に `python3 tools/frequency.py --write --page fenwick-tree,segment-tree-monoids,segment-tree-on-values` を流す。`--check` の差分は、fenwick-tree「前提として 13 ページに届く（直接 5）」→「16 ページ（直接 6）」、segment-tree-monoids「古い ABC 5 問」→「3 問」、segment-tree-on-values「古い ABC 5 問」→「7 問」。frequency の等級（A・A・B）は変わらない
3. **生成物**：`tools/gen_site.py` で作り直す（nav.yml と docs/graph/index.md の namori-graph の位置、fenwick-tree の次に読む、ロードマップ・知識マップの前提など）
4. **任意**：exchange-argument の力試しの ABC467 F の方針は、ノードの設計を「[セグメント木](../ds/segment-tree.md)に載せ」と書いている。segment-tree-monoids の練習に入ったので、[セグメント木に何を載せるか](../ds/segment-tree-monoids.md#design-steps)へのリンクにすると行き来しやすい（担当の外のファイル）
5. **任意**：#27 の残った点の閉区間（fenwick-tree 82・244・300 行目、segment-tree-on-values 199 行目、sweep-line-2d 39・122・128・134・147・162・247 行目）を、表記の Issue（#77 など）でそろえる

## 判断してほしい点

1. **abc467_f の役割**：Issue の「segment-tree-monoids の練習には、要約を足す型の問題が台帳にあれば補ってある」に合わせて練習に入れた。ただし design.md §5.3 の力試しの定義（言い換えや組み合わせで使う難しめの問題）では、交換論法と組み合わせる diff 2052 の問題は力試しに近い。このページの力試しの ABC460 F（1987）より難しく、exchange-argument でも力試しである（青のページの練習で diff 2000 以上は 125 行中 31 行あり、練習でも外れ値ではない）。力試しに移すなら、行と方針を力試しの囲みと折りたたみへ移し、参考の「練習 abc467_f」を「力試し」に直す
2. **segment-tree-on-values の related**：前提に fenwick-tree を足すのに合わせて related から外した。頼まれた項目の外の変更なので、よいかを見てほしい（残すと check_pages が「前提と related の重複」を警告し、ページの前提と関連の両方に BIT が出る）
3. **namori-graph の updated**：本文は変えていないが、chapter と order を変えたので 2026-10-29 にした。本文を直したときだけにするなら戻す

## 使った出典

- AtCoder Library v1.6 の document_ja（手元の ~/lib/ac-library-master/document_ja/dsu.md・lazysegtree.md）：`dsu::merge` の返り値、`lazy_segtree::max_right` の 2 つの形
- ikatakos「AtCoder Beginner Contest 467 E,F問題メモ」（付録 B のドメイン。F の解法の部分だけ）：ABC467 F の方針の確かめ
- 新しく noai を確かめたドメインはない。atcoder.jp・codeforces.com は開いていない

## メインのリポジトリとの重なり（参考）

メインの作業ツリーには、docs/ds/sweep-line-2d.md の未 commit の変更（updated を 2026-10-29 にし、101 行目の図の代替テキストの `[` をエスケープ）がある。この担当の変更は同じ updated の行（同じ値）と 85 行目なので、マージで食い違いは出ないはずである。

## 使用量の目安

- 道具の呼び出し：約 80 回（読む・検査が中心）。Web 取得：1 回（ikatakos）
- 所要時間：約 60 分
