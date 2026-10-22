# 工程10 洗い出し：構成の決まり

- 観点：手引き §13〜§16（と §2.2・§2.3・§4・§10）で決めた構成の形に、既存の全 353 ページがそろっているか
- 調べ方：front matter と見出し・囲み・表をスクリプトで全ページ調べ、判断の要るもの（要点と summary の一致、何ができるかの書き方、発展の概要の library の置き場所）は本文を読んで確かめた。スクリプトは一時置き場 `/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/ff4dc6ee-16d4-486c-b97a-49fefbe7b218/scratchpad/s10/`（`lib.py` が読み込み、`audit1.py` 見出し・sections・complexity・発展の概要、`audit2.py`・`audit3.py` pattern と hub の表、`audit4.py` 箇条書きの句点、`audit5.py` 要点と summary、`audit6.py` 問題の囲みの置き場所）
- check_pages は現状でエラー 0・警告 0。下の件はどれも check_pages が見ていない決まり
- 各行の形：ページ ｜ 行の目安 ｜ 問題 ｜ 根拠 ｜ 直し方。行の目安の「FM」は front matter
- 問題がなかったこと：定型の見出しの文字と anchor の組（例題・練習問題・力試し・確認問題・使い分け・落とし穴・上位の手法へのつながり・学ぶための資料・参考）は下に挙げる 2 件以外そろっている。sections の title と見出しの文字の食い違いは 0 件。問題の囲みの role と置いた節（example は #examples の下、など）の食い違いと、例題の小見出しの anchor と問題 ID の食い違いは 0 件。練習と力試しを 1 つの見出しにしたページ、「次に読む」の見出し、見出しの色の印はなし。hub の 4 ページはどれも「引くもの → 手法 → ページ」の表を持ち、例題の列は §16-8 の形。pattern の 10 ページはどれも sections に overview（問われ方と手法の一覧）があり、表に「代表の問題」の列がある。生成ブロックの見出し（§16-11）は 7 ページとも形どおり

## basics

- docs/basics/binary-search.md ｜ — ｜ 基礎の technique に `## 上位の手法へのつながり {#next-steps}` がない ｜ §14-3、§4 technique（基礎） ｜ 落とし穴の後・問題の前に節を足す（sections には載せない）
- docs/basics/bit-full-search.md ｜ — ｜ 同上（next-steps がない） ｜ §14-3 ｜ 同上
- docs/basics/complexity-estimation.md ｜ — ｜ 同上 ｜ §14-3 ｜ 同上
- docs/basics/coordinate-compression.md ｜ — ｜ 同上 ｜ §14-3 ｜ 同上
- docs/basics/imos.md ｜ — ｜ 同上 ｜ §14-3 ｜ 同上
- docs/basics/interval-scheduling.md ｜ — ｜ 同上 ｜ §14-3 ｜ 同上
- docs/basics/lexicographic-greedy.md ｜ — ｜ 同上 ｜ §14-3 ｜ 同上
- docs/basics/periodicity.md ｜ — ｜ 同上 ｜ §14-3 ｜ 同上
- docs/basics/prefix-sum.md ｜ — ｜ 同上 ｜ §14-3 ｜ 同上
- docs/basics/run-length-encoding.md ｜ — ｜ 同上 ｜ §14-3 ｜ 同上
- docs/basics/two-pointers.md ｜ — ｜ 同上 ｜ §14-3 ｜ 同上
- docs/basics/bitwise-independence.md ｜ L35 ｜ 要点の「何ができるか」の 1 文目が性質の説明（「XOR・AND・OR の結果の bit k は、元の値の bit k だけで決まる」）で、何ができるかは 2 文目にある（判断） ｜ §2.2「1 文目で何ができるかを言う」 ｜ 1 文目を「全ペア・全区間の XOR・AND・OR の集計を、bit ごとに 0 と 1 の個数を数えて O(NB) で求める」のような形にし、性質は 2 文目へ

## thinking

（見つからなかった。確認問題の置き場所と箇条書きの句点は ## shared の全体の件に含めた）

## dp

- docs/dp/cht.md ｜ L125 ｜ 発展の概要のライブラリの節の anchor が `verify`（「ライブラリでの検証（Library Checker の line_add_get_min・segment_add_get_min）」、65 字） ｜ §16-2（anchor は library）、§14-12（60 字目安） ｜ anchor を `library` に変え、FM の sections も直す。geometry/advanced-geometry.md L181 の `cht.md#verify` を張り替える。見出しは「ライブラリでの検証」程度に短くし、問題名は本文へ
- docs/dp/dynamic-dp.md ｜ L143 ｜ 同上（anchor が `verify`） ｜ §16-2 ｜ anchor を `library` に変え、sections も直す（このページの `#verify` への外からのリンクはない）
- docs/dp/monge.md ｜ L159 ｜ 同上（anchor が `verify`、見出し 69 字） ｜ §16-2、§14-12 ｜ 同上。見出しを短くする
- docs/dp/dp-speedup-overview.md ｜ FM ｜ hub なのに complexity が null でない（「全体は状態数 × 遷移 1 回の手間。…」） ｜ §16-12、§2.1 ｜ complexity を null にする（要点の囲みの「計算量」の項目は残してよい）
- docs/dp/dp-basics.md ｜ — ｜ 基礎の technique に next-steps がない ｜ §14-3 ｜ `## 上位の手法へのつながり {#next-steps}` を足す
- docs/dp/subset-sum.md ｜ — ｜ 同上 ｜ §14-3 ｜ 同上

## misc

- docs/misc/interactive.md ｜ — ｜ 基礎の technique に next-steps がない ｜ §14-3 ｜ `## 上位の手法へのつながり {#next-steps}` を足す
- docs/misc/bitset-speedup.md ｜ L124 ｜ 1 つの箇条書きで句点のある行とない行が混ざる ｜ §14-25・§15-2 ｜ 文の行に句点を付けてそろえる
- docs/misc/parsing.md ｜ L237〜239 ｜ 同上（句点の混在） ｜ §14-25・§15-2 ｜ 同上

## graph

- docs/graph/dilworth-path-cover.md ｜ L59〜72・L92、L166 ｜ 発展の概要に `{#library}` の節も `## 学ぶための資料 {#resources}` もない。自作の要点と ACL の囲みが path-cover・antichain の節の中に散っている ｜ §16-1・§16-2、§4 overview ｜ 「自作するときの要点と Library Checker {#library}」の節を立てて自作の要点と Library Checker の文を移し、参考の前に `## 学ぶための資料 {#resources}` を足す
- docs/graph/dilworth-path-cover.md ｜ L175〜176 ｜ 参考の行に「（学ぶための資料）」を添える形が残る ｜ §16-1 ｜ その 2 行を `## 学ぶための資料 {#resources}` に移し、添え書きを消す
- docs/graph/flow-lower-bounds.md ｜ L69〜85 ｜ `{#library}` も `{#resources}` もない。L85 は本文で「学ぶための資料としては…」と書いている ｜ §16-1・§16-2 ｜ L69〜84 の ACL の囲みと自作の要点を `## … {#library}` の節にし、L85 の内容を `## 学ぶための資料 {#resources}` に移す
- docs/graph/flow-lower-bounds.md ｜ L114〜115 ｜ 参考の行に「（学ぶための資料）」 ｜ §16-1 ｜ 資料の節に移し、添え書きを消す
- docs/graph/k-shortest-paths.md ｜ L62・L90・L107 ｜ `{#library}` も `{#resources}` もない（自作の要点が k-times・yen-eppstein の中にある） ｜ §16-1・§16-2 ｜ L107 の公開ライブラリの文と自作の要点を `## … {#library}` に集め、資料の節を足す
- docs/graph/k-shortest-paths.md ｜ L125〜126 ｜ 参考の行に「（学ぶための資料）」 ｜ §16-1 ｜ 資料の節に移す
- docs/graph/k-shortest-paths.md ｜ L109 ｜ 例題・練習が 0 問なのに、練習問題の節が Library Checker の小見出しだけで、§16-5 の 1 文がない ｜ §16-5 ｜ 小見出しの前に「ABC で必須になる問題は確認できなかった。」を置く
- docs/graph/offline-dynamic-connectivity.md ｜ L95 ｜ `{#library}` も `{#resources}` もない（自作の要点が dfs-rollback の中） ｜ §16-1・§16-2 ｜ library の節を立て、資料の節を足す
- docs/graph/spanning-tree-advanced.md ｜ L66〜72・L108〜116 ｜ `{#library}` がない（Borůvka・有向 MST の自作の要点がそれぞれの節の中） ｜ §16-2 ｜ 「自作するときの要点と Library Checker {#library}」を立てて集める（各手法の節に 1 文ずつ残してよい）
- docs/graph/spanning-tree-advanced.md ｜ L132・L142 ｜ 学ぶための資料（L142）が練習問題（L132）の後にある ｜ §4 overview（使い方 → 資料 → 例題） ｜ 資料の節を練習問題の前へ移す
- docs/graph/two-sat.md ｜ L122 ｜ ライブラリの節の anchor が `acl`（「ACL の two_sat と自作するときの要点」）。§15-3 では許されるが §16-2 は library にそろえる（判断） ｜ §16-2 と §15-3 ｜ メインが決める。library にするなら sections を直し、cpp/acl-reading.md L113 の `two-sat.md#acl` を張り替える
- docs/graph/matrix-tree-theorem.md ｜ FM L28 ｜ sections に `学ぶための資料`（resources）が載っている ｜ §16-1・§13-1（定型は sections に載せない） ｜ sections から外す
- docs/graph/graph-modeling.md ｜ FM ｜ hub なのに complexity が null でない ｜ §16-12 ｜ null にする
- docs/graph/bfs.md ｜ — ｜ 基礎の technique に next-steps がない ｜ §14-3 ｜ `## 上位の手法へのつながり {#next-steps}` を足す
- docs/graph/cycle-detection.md ｜ — ｜ 同上 ｜ §14-3 ｜ 同上
- docs/graph/graph-basics.md ｜ — ｜ 同上 ｜ §14-3 ｜ 同上
- docs/graph/grid-graph.md ｜ — ｜ 同上 ｜ §14-3 ｜ 同上
- docs/graph/topological-sort.md ｜ — ｜ 同上 ｜ §14-3 ｜ 同上
- docs/graph/zero-one-bfs.md ｜ L34 付近の後の H2 ｜ `## 必要になる場面` に anchor がない（全ページで anchor のない H2 はこれだけ。日本語の自動の anchor になる） ｜ §2.3（見出しは `## 見出し {#anchor}`） ｜ `{#motivation}` を付ける（bit-dp などと同じ）
- docs/graph/functional-graph.md ｜ L34 ｜ 「何ができるか」の 1 文目が形の説明（ρ の形になる）で、何ができるかを言っていない（判断） ｜ §2.2 ｜ 「閉路と木に分けて、K 回たどった先や閉路に入るまでの長さを求める」のように何ができるかを先に言う
- docs/graph/namori-graph.md ｜ L32 ｜ 同上（形の説明だけ） ｜ §2.2 ｜ 同上
- docs/graph/graph-construction.md ｜ L32 ｜ 同上（DFS 木・BFS 木の性質の説明だけ） ｜ §2.2 ｜ 同上
- docs/graph/degree-sqrt.md ｜ L198 ｜ 箇条書きの句点の混在 ｜ §14-25・§15-2 ｜ 句点をそろえる
- docs/graph/graph-construction.md ｜ L213〜215、L228 ｜ 同上 ｜ §14-25・§15-2 ｜ 同上
- docs/graph/min-cut.md ｜ L88〜89 ｜ 同上 ｜ §14-25・§15-2 ｜ 同上
- docs/graph/complement-graph-bfs.md ｜ — ｜ 黄の technique なのに練習問題の節がない（例題 1 問だけ） ｜ §4 technique、§10（練習 2〜6） ｜ 練習の問題を台帳から探して足すか、問題の補充の観点に回す

## geometry

- docs/geometry/advanced-geometry.md ｜ L76〜79 ほか ｜ 発展の概要に `{#library}` がない（自作の要点が rotating-calipers などの各節の中） ｜ §16-2 ｜ 「自作するときの要点と Library Checker {#library}」を立て、各手法の Library Checker の対応と自作の要点を集める
- docs/geometry/manhattan-chebyshev.md ｜ L217 ｜ `## ACL では {#acl}` の見出しを立てている（sections に acl はない） ｜ §14-4（見出しは立てず関係する節の中に囲みで置く）、§15-3 の例外にも当たらない ｜ 見出しを消し、囲みと続く段落を最遠点対の節（L91 `#farthest-pair`）へ移す（`#acl` への外からのリンクはない）
- docs/geometry/manhattan-chebyshev.md ｜ L55 ｜ `## 必要になる場面 {#motivation}` が sections にない（同じ形：dp/bit-dp.md L51・dp/broken-profile-dp.md L51・ds/kth-element.md L46・math/floor-sum.md L54 `#when`）（軽微） ｜ §13-1（中身の節は sections に載せる）。必須ではない ｜ 理解度のチェックの単位にするなら sections に足す。しないなら現状でよい

## tree

- docs/tree/auxiliary-tree.md ｜ L103 ｜ 発展の概要のライブラリの節の anchor が `usage` で、見出しが「圧縮木で木 DP をするときの要点と学ぶための資料」と資料を兼ねる。`{#resources}` がない ｜ §16-1・§16-2 ｜ anchor を `library` に変え（sections も）、資料の部分を `## 学ぶための資料 {#resources}` に分ける
- docs/tree/tree-isomorphism.md ｜ L63 ｜ `{#library}` も `{#resources}` もない（自作の要点が AHU の節の中に太字で） ｜ §16-1・§16-2 ｜ library の節と資料の節を足す
- docs/tree/tree-isomorphism.md ｜ L125 ｜ 例題・練習が 0 問なのに §16-5 の 1 文がない（Library Checker・CSES の小見出しだけ） ｜ §16-5 ｜ 小見出しの前に 1 文を置く
- docs/tree/tree-imos.md ｜ — ｜ 基礎の technique に next-steps がない ｜ §14-3 ｜ 節を足す
- docs/tree/tree-traversal.md ｜ — ｜ 同上 ｜ §14-3 ｜ 同上
- docs/tree/steiner-subtree.md ｜ — ｜ 基礎の technique に練習問題の節がない（例題と力試しだけ） ｜ §4、§10 ｜ 練習を足すか、問題の補充の観点に回す
- docs/tree/hld.md ｜ L196・L200〜201 ｜ 箇条書きの句点の混在 ｜ §14-25・§15-2 ｜ 句点をそろえる
- docs/tree/tree-centroid.md ｜ L31 ｜ 「何ができるか」の 1 文目が定義（「重心は、…頂点で、1 個か隣り合う 2 個ある」）。summary も同じ形（判断） ｜ §2.2 ｜ 「部分木サイズから重心を O(N) で求め、どの枝も半分以下になる頂点として分割統治の軸にする」のように何ができるかを先に言う。summary も合わせる（提案）

## string

- docs/string/suffix-automaton.md ｜ L73・L90・L98 ｜ 発展の概要に `{#library}` も `{#resources}` もない（H3 の「自作するときの要点 {#build-your-own}」が Suffix Automaton の節の中） ｜ §16-1・§16-2 ｜ library の節を立てて H3 の内容と ACL・Library Checker の文を移し（`#build-your-own` は外からリンクされていなければ H2 にして anchor を library に）、資料の節を足す
- docs/string/suffix-automaton.md ｜ L38 ｜ 「何ができるか」が「Suffix Automaton は … DFA で」の定義から始まり、「発展の文字列アルゴリズムも、入口だけをまとめる」とページの説明の言い方をしている ｜ §2.2（1 文目で何ができるか、「扱う」「紹介する」などのページの説明をしない） ｜ 1 文目を「全部分文字列を受理する状態数 2N−1 以下の DFA を作り、異なる部分文字列の数・出現回数・最長共通部分文字列を答える」の形にし、「入口だけをまとめる」の文を消す
- docs/string/string-basics.md ｜ L171、FM L30 ｜ 落とし穴に当たる節が中身の節「計算量の落とし穴 {#cost-pitfalls}」で、定型の `## 落とし穴 {#pitfalls}` がない（判断） ｜ §14-1（落とし穴は定型にそろえ sections から外す） ｜ メインが決める。anchor を変えないなら現状でよく、§14-1 にそろえるなら `#pitfalls` にしてリンクを張り替える
- docs/string/string-basics.md ｜ — ｜ 基礎の technique に next-steps がない ｜ §14-3 ｜ 節を足す
- docs/string/subsequence-matching.md ｜ — ｜ 同上 ｜ §14-3 ｜ 同上

## ds

- docs/ds/parallel-binary-search.md ｜ L87〜94 ｜ 発展の概要に `{#library}` も `{#resources}` もない（自作の要点が procedure の節の中） ｜ §16-1・§16-2 ｜ library の節を立てて L87〜94 を移し、資料の節を足す
- docs/ds/partially-persistent-union-find.md ｜ L66〜77 ｜ 同上（自作の要点が what-it-does の節の中） ｜ §16-1・§16-2 ｜ 同上
- docs/ds/partially-persistent-union-find.md ｜ L156〜157 ｜ 参考の行に「（学ぶための資料）」 ｜ §16-1 ｜ 資料の節に移し、添え書きを消す
- docs/ds/rollback-union-find.md ｜ L54〜64 ｜ `{#library}` も `{#resources}` もない ｜ §16-1・§16-2 ｜ library の節を立て、資料の節を足す
- docs/ds/segment-tree-beats.md ｜ L81 ｜ `{#library}` がない。自作の要点が H3「自作するときの要点」（anchor なし）として node-data の節の中にある ｜ §16-2 ｜ この H3 を `## 自作するときの要点と Library Checker {#library}` に上げる（資料の節は L130 にある）
- docs/ds/wavelet-matrix.md ｜ L98 ｜ ライブラリの節の anchor が `usage`。`{#resources}` もない ｜ §16-1・§16-2 ｜ anchor を `library` にして sections も直し、ds/persistent-data-structures.md L171 の `wavelet-matrix.md#usage` を張り替える。資料の節を足す
- docs/ds/advanced-ds-catalog.md ｜ FM ｜ hub なのに complexity が null でない ｜ §16-12 ｜ null にする
- docs/ds/global-offset.md ｜ L159 ｜ 基礎の technique に定型の next-steps がない。中身の節「遅延セグメント木とのつながり {#to-lazy-segment-tree}」が同じ役をしている（判断） ｜ §14-3 ｜ 現状でよいとするか、定型の節を足すかをメインが決める
- docs/ds/ordered-set.md ｜ — ｜ 基礎の technique に next-steps がない ｜ §14-3 ｜ 節を足す
- docs/ds/binary-trie.md ｜ L217〜218 ｜ 箇条書きの句点の混在 ｜ §14-25・§15-2 ｜ 句点をそろえる
- docs/ds/weighted-union-find.md ｜ L125 ｜ `acl: []` なのに「ACL では」の囲みがある（中身は `dsu d(2 * n)` で頂点を 2 倍にする使い方） ｜ §14-4（acl: [] のページでは省く） ｜ ACL を使う書き方を載せるなら FM の acl に `dsu` を足す提案をする。載せないなら囲みを本文の 1 文にする
- docs/ds/lazy-segment-tree.md ｜ — ｜ 水の technique なのに定型の `## 落とし穴 {#pitfalls}` がない（境界の節 L170 が近い役）。見本のページ ｜ §4 technique、§14-1 ｜ 見本なのでメインが決める（境界の節で足りるなら現状でよい）

## cpp

- docs/cpp/cpp-algorithms.md ｜ L217、FM ｜ 見出しと sections の title に波かっこ（「射影：ranges::sort(ps, {}, &P::score) は …」）。63 字 ｜ §2.3（波かっこを書かない。attr_list が anchor を取り違えるおそれ）、§14-12 ｜ 「射影：メンバのポインタを渡して score で比べる（C++20）」のように言葉で言い換え、title も同時に直す
- docs/cpp/cpp-initialization.md ｜ L50、FM ｜ 見出しに `{n}`（「vector の初期化：(n) は 0 が n 個、(n, x) は x が n 個、{n} は値 n が 1 個」） ｜ §2.3、§14-12 ｜ 「波かっこで書くと値 n が 1 個」などに言い換える
- docs/cpp/cpp-initialization.md ｜ L81、FM ｜ 見出しに `{}`（「array と {} による 0 初期化」） ｜ §2.3 ｜ 「array を空の波かっこで 0 初期化」などに言い換える
- docs/cpp/cpp-initialization.md ｜ L122、FM ｜ 見出しに `Edge{.to = v, .cost = c}`（62 字） ｜ §2.3、§14-12 ｜ 「構造体のメンバの既定値と指示付き初期化（C++20。宣言順に書く）」にし、例は本文へ
- docs/cpp/cpp-structured-bindings.md ｜ L53、FM ｜ 見出しに `pair{a, b}` ｜ §2.3 ｜ 「pair と tuple：get・make_pair・波かっこでの作成、辞書順で比べられる」などに言い換える
- docs/cpp/cpp-views-basics.md ｜ L37、FM summary ｜ summary は「views::iota(0, v.size()) が通らない理由など、型と寿命の罠も分かる」と言うが、要点の「何ができるか」にない。言い方も大きく違う ｜ §2.2（summary と食い違わせない） ｜ 要点に罠の 1 文を足すか、summary を要点に合わせる提案をする
- docs/cpp/cpp-lambda.md ｜ L39、FM summary ｜ summary は「再帰の 4 つの書き方（std::function・auto&& self・deducing this・不動点コンビネータ）の違いと速さも比べる」、要点は「auto&& self か deducing this で書くと普通の関数と同じ速さ」だけ（軽微） ｜ §2.2 ｜ どちらかに合わせる
- docs/cpp/ の見出し（60 字超え、23 か所） ｜ acl-reading L288（65）、cpp-algorithms L250（68）、cpp-comparators L140（63）、cpp-container-idioms L51（70）、cpp-initialization L150（67）・L171（65）・L217（67）、cpp-integer-overflow L94（66）・L106（64）、cpp-io L140（61）・L223（64）、cpp-macros-template-file L134（61）、cpp-math-functions L51（67）・L171（69）・L190（67）、cpp-range-for L84（62）、cpp-reverse-index L331（68）、cpp-string-api L68（65）、cpp-templates-constexpr L244（68）、cpp-types-literals L81（66）・L97（67）・L117（61）・L195（68）、cpp-views-cpp23 L55（63）・L234（65） ｜ 見出しが 60 字の目安を超える。cpp は見出しに要点を詰める書き方で長くなりやすい ｜ §14-12（60 字以内が目安） ｜ anchor を変えずに見出しと title を同時に短くする（括弧の補足を本文の 1 文目へ）。目安なので、直すかはメインが決める

## math

- docs/math/fft-ntt.md ｜ L99 ｜ 発展の概要に `{#library}` がない（自作の要点が butterfly の節の中） ｜ §16-2 ｜ library の節を立て、ACL の convolution・自作の要点・Library Checker を集める
- docs/math/fft-ntt.md ｜ L141 ｜ 例題・練習が 0 問なのに §16-5 の 1 文がない ｜ §16-5 ｜ 小見出しの前に 1 文を置く
- docs/math/fps-basics.md ｜ L89〜96 ｜ `{#library}` がない（ACL の囲みと自作の要点が operations の節の中） ｜ §16-2 ｜ library の節を立てて移す
- docs/math/linear-recurrence-fast.md ｜ L134 ｜ ライブラリの節の anchor が `implementation`（「ACL の convolution を使った実装」） ｜ §16-2 ｜ anchor を `library` に変え sections も直す（外からのリンクはない）
- docs/math/multiplicative-function.md ｜ L103・L135・L150 ｜ `{#library}` も `{#resources}` もない ｜ §16-1・§16-2 ｜ L150 の公開ライブラリの文と自作の要点を library の節に集め、資料の節を足す
- docs/math/multiplicative-function.md ｜ L182 ｜ 参考の行に「（学ぶための資料）」 ｜ §16-1 ｜ 資料の節に移す
- docs/math/multiplicative-function.md ｜ L163 ｜ 例題・練習が 0 問なのに §16-5 の 1 文がない ｜ §16-5 ｜ 1 文を置く
- docs/math/online-convolution.md ｜ L62〜108 ｜ `{#library}` がない（ACL の囲みと自作の要点が online の節の中） ｜ §16-2 ｜ library の節を立てて移す
- docs/math/stern-brocot.md ｜ L115 の後 ｜ 発展の概要に `## 学ぶための資料 {#resources}` がない ｜ §16-1 ｜ 参考の前に資料の節を足す
- docs/math/stern-brocot.md ｜ L32、FM summary ｜ summary は「実数に最も近い分数など」を求めると言い、要点は「与えられた実数を挟む最も近い 2 つ」を求めると言う。求めるものが違って読める ｜ §2.2 ｜ 本文に合わせて片方に寄せる（summary を直すなら提案）
- docs/math/miller-rabin.md ｜ L144 ｜ `acl: []` なのに「ACL では」の囲みがある（公開の関数はない、内部関数がある、という内容） ｜ §14-4 ｜ 囲みをやめて L140 の節（acl-internal）の本文にする
- docs/math/miller-rabin.md ｜ L164〜170 ｜ 0 問なのに `## 例題` を置いてそこに「必須の問題は見つかっていない」と書き、練習問題の節には 1 文がない ｜ §16-5（例題は省き、練習問題に 1 文） ｜ `## 例題` を消し、1 文を練習問題の節の小見出しの前へ移す
- docs/math/determinant.md ｜ L157 ｜ 0 問の練習問題の節の 1 文が §16-5 と違う言い方（「行列式だけを問う AtCoder の問題は、この帯にはない」） ｜ §16-5 ｜ 決まりの言い方にそろえる（ほかのページへの案内の文は残してよい）
- docs/math/floor-sum.md ｜ L112、FM L27 ｜ sections の `why-log`（なぜ O(log m) で終わるか）が H3 になっている ｜ §2.3（sections の節は `## 見出し {#anchor}`） ｜ H2 に上げる（anchor は変えない。guide/reverse-index-constraints.md L98・L430 からリンクされている）
- docs/math/floor-sum.md ｜ — ｜ 黄の technique なのに練習問題の節がない（例題 2・力試し 1） ｜ §4、§10 ｜ 練習を足すか、問題の補充の観点に回す
- docs/math/modint.md ｜ L72 付近 ｜ `acl: [static_modint, dynamic_modint]` なのに「ACL では」の囲みがない ｜ §14-4 ｜ static-dynamic の節に、宣言（`modint998244353`・`modint::set_mod`）と主なメソッド（`val`・`pow`・`inv`）と計算量の囲みを置く
- docs/math/modint.md ｜ L130 ｜ 基礎の technique に定型の next-steps がない。中身の節「上位の手法での使われ方 {#connections}」が同じ役（判断） ｜ §14-3 ｜ 現状でよいとするか、メインが決める
- docs/math/sigma-manipulation.md ｜ L133、FM ｜ 見出しと title に波かっこ（「Σ_{i≠j} a_i a_j = (Σa)² − Σa²」） ｜ §2.3、§14-12 ｜ 「よく使う和の公式と、異なる 2 つの積の和を和の 2 乗で表す式」などに言い換える
- docs/math/divisor-enum.md ｜ — ｜ 基礎の technique に next-steps がない ｜ §14-3 ｜ 節を足す
- docs/math/mod-inverse.md ｜ — ｜ 同上 ｜ §14-3 ｜ 同上
- docs/math/mod-pow.md ｜ — ｜ 同上 ｜ §14-3 ｜ 同上
- docs/math/prime-factorization.md ｜ — ｜ 同上 ｜ §14-3 ｜ 同上
- docs/math/sieve-eratosthenes.md ｜ — ｜ 同上 ｜ §14-3 ｜ 同上
- docs/math/spf-sieve.md ｜ — ｜ 同上 ｜ §14-3 ｜ 同上
- docs/math/euler-phi.md ｜ L210〜212 ｜ 箇条書きの句点の混在 ｜ §14-25・§15-2 ｜ 句点をそろえる

## comb

- docs/comb/generating-function-counting.md ｜ L166、FM L27 ｜ 例題の見出しが「例題：Prüfer 列と累乗、上限つきの桁の和 {#examples}」で、sections にも載っている ｜ §13-1（定型は `## 例題 {#examples}` で sections に載せない）、§13-2 ｜ 見出しを `## 例題 {#examples}` にし、sections から外す
- docs/comb/generating-function-counting.md ｜ L142〜151 ｜ 発展の概要に `{#library}` がない（ACL の囲みと自作の要点が to-fps の節の中） ｜ §16-2 ｜ library の節を立てて移す
- docs/comb/generating-function-counting.md ｜ L194 ｜ 箇条書きの句点の混在 ｜ §14-25・§15-2 ｜ 句点をそろえる
- docs/comb/partizan-games.md ｜ L99〜111 ｜ `{#library}` がない（自作の要点と「ACL・Library Checker に対応がない」の文が surreal の節の中） ｜ §16-2・§16-3・§16-4 ｜ library の節を立てて移す
- docs/comb/stirling-first.md ｜ L129〜148 ｜ `{#library}` がない（ACL の囲みと自作の要点が fps の節の中） ｜ §16-2 ｜ library の節を立てて移す
- docs/comb/burnside-lemma.md ｜ L162〜187 ｜ 確認問題（L162）と落とし穴（L175）が、学ぶための資料（L181）と例題（L187）より前にある ｜ §4 overview の順（使い方 → 資料 → 例題）、§4 technique（確認問題は問題の後） ｜ 落とし穴を library の前後へ、確認問題を例題・練習の後へ移す
- docs/comb/twelvefold-way.md ｜ FM ｜ hub なのに complexity が null でない ｜ §16-12 ｜ null にする
- docs/comb/binomial-coefficient.md ｜ — ｜ 基礎の technique に next-steps がない ｜ §14-3 ｜ 節を足す
- docs/comb/binomial-precompute.md ｜ — ｜ 同上 ｜ §14-3 ｜ 同上
- docs/comb/counting-basics.md ｜ — ｜ 同上 ｜ §14-3 ｜ 同上
- docs/comb/permutation-cycles.md ｜ — ｜ 同上 ｜ §14-3 ｜ 同上
- docs/comb/stars-and-bars.md ｜ — ｜ 同上 ｜ §14-3 ｜ 同上
- docs/comb/expectation-tail-sum.md ｜ — ｜ 黄の technique なのに練習問題の節がない（例題と力試しだけ） ｜ §4、§10 ｜ 練習を足すか、問題の補充の観点に回す
- docs/comb/probability-symmetry.md ｜ L34 ｜ 「何ができるか」が性質の 1 文（「入れ替えても問題が変わらない対象は、どれも同じ確率を持つ」）で、何ができるかを言っていない（判断） ｜ §2.2 ｜ 「対称な対象の確率・期待値を、1 つを計算して個数で割る・掛けるだけで求める」のように言い直す
- docs/comb/bell-number.md ｜ L197〜199 ｜ 箇条書きの句点の混在 ｜ §14-25・§15-2 ｜ 句点をそろえる
- docs/comb/counting-labeled-graphs.md ｜ L240、L253 ｜ 同上 ｜ §14-25・§15-2 ｜ 同上
- docs/comb/inclusion-exclusion-dp.md ｜ L249、L263、L290〜292 ｜ 同上 ｜ §14-25・§15-2 ｜ 同上
- docs/comb/minimax.md ｜ L224 ｜ 同上 ｜ §14-25・§15-2 ｜ 同上
- docs/comb/mobius-function.md ｜ L240、L254〜256 ｜ 同上 ｜ §14-25・§15-2 ｜ 同上
- docs/comb/nim.md ｜ L226〜229 ｜ 同上 ｜ §14-25・§15-2 ｜ 同上
- docs/comb/permutation-parity.md ｜ L187 ｜ 同上 ｜ §14-25・§15-2 ｜ 同上
- docs/comb/zeta-mobius-divisor.md ｜ L218 ｜ 同上 ｜ §14-25・§15-2 ｜ 同上
- docs/comb/zeta-mobius-subset.md ｜ L274 ｜ 同上 ｜ §14-25・§15-2 ｜ 同上

## patterns

- docs/patterns/bracket-sequence.md ｜ FM ｜ pattern なのに complexity が null でない（見本のページ） ｜ §16-12（guide・hub・pattern は null） ｜ null にする（要点の囲みの「計算量」は残してよい）。見本なので ## shared の件と合わせてメインが決める
- docs/patterns/divisors-and-multiples.md ｜ FM ｜ 同上 ｜ §16-12 ｜ null にする
- docs/patterns/grid.md ｜ FM ｜ 同上 ｜ §16-12 ｜ 同上
- docs/patterns/interval.md ｜ FM ｜ 同上 ｜ §16-12 ｜ 同上
- docs/patterns/kth-and-median.md ｜ FM ｜ 同上 ｜ §16-12 ｜ 同上
- docs/patterns/mex.md ｜ FM ｜ 同上 ｜ §16-12 ｜ 同上
- docs/patterns/operation-sequence.md ｜ FM ｜ 同上 ｜ §16-12 ｜ 同上
- docs/patterns/permutation.md ｜ FM ｜ 同上 ｜ §16-12 ｜ 同上
- docs/patterns/subsequence-and-substring.md ｜ FM ｜ 同上 ｜ §16-12 ｜ 同上
- docs/patterns/xor.md ｜ FM ｜ 同上 ｜ §16-12 ｜ 同上
- docs/patterns/kth-and-median.md ｜ L81〜92 ｜ 「代表の問題」の列 10 行が、行き先のページの例題の小見出しへのリンク（`[ABC155 D](../basics/kth-value.md#abc155_d)` など）になっている ｜ §16-7・§4 pattern（label を文字だけで書き、リンクは行き先のページに任せる） ｜ リンクを外して「ABC155 D」の文字だけにする
- docs/patterns/kth-and-median.md ｜ L87 ｜ ABC123 D の行の「ページ」の列は greedy-priority-queue だが、問題が載っているのは ds/priority-queue（行き先のページにない） ｜ §16-7（行き先のページの問題の label） ｜ ページの列に優先度付きキューを足すか、greedy-priority-queue に載っている問題に替える
- docs/patterns/operation-sequence.md ｜ L76〜87 ｜ 「代表の問題」の列 10 行がリンク（`[ABC212 D](../ds/global-offset.md#abc212_d)` など） ｜ §16-7 ｜ 文字だけにする
- docs/patterns/permutation.md ｜ L80 ｜ 代表の問題 ABC350 C は行き先の permutation-cycles にもこのページにもなく、thinking/construction にだけある ｜ §16-7 ｜ permutation-cycles に載っている問題だけにするか、ページの列に構築を足す
- docs/patterns/divisors-and-multiples.md ｜ L173 ｜ 箇条書きの句点の混在 ｜ §14-25・§15-2 ｜ 句点をそろえる
- docs/patterns/ の見出し（60 字超え、7 か所） ｜ divisors-and-multiples L128（61）、grid L188（61）、kth-and-median L100（64）・L151（61）、operation-sequence L104（66）、permutation L92（66）、subsequence-and-substring L117（62） ｜ 「問われ方 → 手法（id）」の形で 60 字を超える ｜ §14-12（目安） ｜ 末尾の（id）を外すと 60 字に収まる。見本 bracket-sequence も（id）付きなので、外すなら全 pattern でそろえる（メインが決める）

## guide

- docs/guide/library-design.md ｜ FM ｜ guide なのに complexity が null でない ｜ §16-12 ｜ null にする
- docs/guide/method-comparison.md ｜ FM ｜ 同上 ｜ §16-12 ｜ 同上
- docs/guide/reverse-index-constraints.md ｜ FM ｜ 同上 ｜ §16-12 ｜ 同上
- docs/guide/roadmap.md ｜ L733、FM L23 ｜ 定型の anchor `practice` を、中身の節「色ごとの練習の方法」に使っている ｜ §13-1（#practice は定型の練習問題の anchor） ｜ anchor を `practice-by-color` などに変えて sections も直す（`roadmap.md#practice` への外からのリンクはない）
- docs/guide/library-design.md ｜ L30、FM summary ｜ summary の「確認用の問題の対応表は各ページの verify から生成する」が要点になく、要点の「提出用の展開」が summary にない ｜ §2.2 ｜ どちらかに合わせる（summary を直すなら提案）
- docs/guide/thinking-checklist.md ｜ L45 ｜ 要点の「前提」に complexity-estimation があるが、FM の prerequisites は空 ｜ §2.2（要点を prerequisites と食い違わせない） ｜ prerequisites に complexity-estimation を足す提案をするか、要点の前提を消す
- docs/guide/glossary.md ｜ L771 ｜ `## 参考 {#references}` がない（最後の節は「表記の正規形と別名の対応表」）（判断） ｜ §11（ページ末尾に参考） ｜ 参考にした資料がなければ現状でよいとするか、メインが決める
- docs/guide/term-index.md ｜ L2705 ｜ 同上（最後は生成の「複数のページに当たる語」） ｜ §11 ｜ 同上

## start

（見つからなかった）

## shared

- 道具（tools/check_pages.py） ｜ — ｜ 上の件の多くは機械的に見つかるのに check_pages が検査していない ｜ interfaces §10 ｜ 次を警告として足す提案：定型の見出しと anchor の組の食い違い、sections に定型の anchor（examples・practice・challenge・quiz・comparison・choosing・pitfalls・next-steps・resources・references）、見出しと sections の title の `< > [ ] { }` とバッククォート、sections の節が H2 でない、overview に `#library`・`#resources` がない、guide・hub・pattern の complexity が null でない、`acl` が空でないのに「ACL では」の囲みがない（とその逆）、pattern の「代表の問題」の列のリンク。調べたスクリプト（一時置き場の `audit1.py`）をそのまま移せる
- 手引き §16-12 と見本 ｜ — ｜ pattern の全 10 ページ・hub の全 4 ページ・guide の 3 ページ（計 17）の complexity が null でない。見本の bracket-sequence も入れている。§16-12 の「計算量のない guide・hub・pattern のページ」は「guide・hub・pattern は計算量がないので null」とも「計算量のないものだけ null」とも読める ｜ §16-12、§2.1 ｜ メインが読み方を決め、手引きの文を直す。null にそろえるなら 17 ページを直し、check_pages に足す
- 手引き §3 と §14-11（確認問題の置き場所） ｜ — ｜ 本文の途中に置いた `??? question` が 192 ページに 417 個ある。そのうち 101 ページ（基礎の technique と thinking が大半。見本の bracket-sequence も途中に置く）には `## 確認問題 {#quiz}` がない。§3 は「要所に置く」、§14-11 は「#quiz にまとめる」と読め、食い違う ｜ §3・§14-11 ｜ メインがどちらにするか決めて手引きを 1 つの文にする。「まとめる」なら 101 ページに #quiz を作る作業になる。一覧は一時置き場のスクリプトで出せる
- 手引き §15-2（箇条書きの句点） ｜ — ｜ 本文の箇条書き（要点の囲み・問題の囲み・参考と資料の節を除く）で、行の途中に句点があるのに末尾に句点がない行が約 3,300（ほかに括弧で終わる行が約 650）、290 ページにある。分野別の行数は cpp 568・ds 510・graph 454・comb 417・math 413・dp 409・basics 355・tree 230・patterns 139・thinking 137・string 132・geometry 110・guide 59・misc 46。§15-2 は「既存のページはそろえ直さない」としたので、1 つのリストの中で句点の有無が混ざる 24 か所だけを各分野に挙げた ｜ §14-25・§15-2 ｜ 工程10でそろえ直すかをメインが決める。そろえるなら機械的な置き換えに近いが、名詞句だけの列挙を除く判断が要る
- 要点と summary（全体） ｜ — ｜ 要点の「何ができるか」（guide などは「何のページか」）を持つ 352 ページのうち、数式と記号を除いて summary と同じ文なのは 109 ページで、243 ページは書き直してある（§2.2 で許される）。文字の似かたが低いものと 0.6 台のものを読み、事実や範囲が食い違うものだけを各分野に挙げた（cpp-views-basics・cpp-lambda・library-design・stern-brocot・suffix-automaton）。ほかは要点のほうが詳しいだけで、食い違いはない ｜ §2.2 ｜ summary は索引（llms.txt・詳細索引）に出るので、食い違いを直すときは summary の直しを台帳ではなく FM の提案としてまとめる
- 「何ができるか」の 1 文目（全体） ｜ — ｜ 1 文目が定義や性質の説明で、何ができるかを 2 文目以降で言うページが 7 つ（各分野に挙げた。bitwise-independence・functional-graph・namori-graph・graph-construction・probability-symmetry・tree-centroid・suffix-automaton。thinking/complement・construction などの「〜は、…して数える」は手順を言っているので入れていない） ｜ §2.2 ｜ 各ページで 1 文目を直す。境目は判断なので、メインが基準を決めてから直す
- 節の並び（全体、参考） ｜ — ｜ §4 の目安の並び（例題 → 練習 → 確認問題 → 使い分け）に対し、使い分けを例題より前に置くページが 72、確認問題を例題より前に置くページが 16 ある。上位の帯の節を問題の後に置くページもある（見本の lazy-segment-tree L306・interval-set L253・mo-algorithm L166〜205・monotonic-stack L296〜320・lowlink L258） ｜ §3「§4・§5 は目安で、内容に合わせて並べ替える」 ｜ 決まりの違反ではないので直さなくてよい。そろえたいならメインが並びを決める
- 発展の概要の library・resources（全体） ｜ — ｜ 発展の概要 51 ページのうち、`{#library}` がないのが 26、`{#resources}` がないのが 13（各分野に挙げた）。どれも中身（自作の要点・ACL・Library Checker の文）は本文のどこかにあり、節として立っていないだけ。`verify`・`usage`・`implementation`・`acl` の anchor で立てたものが 7 ある ｜ §16-1・§16-2（「既存のページをこの決まりにそろえるのは工程10」） ｜ 節を立てる作業はページごとに本文の移動を伴うので、執筆のサブエージェントに分野ごとに分けて渡す。anchor を library に変える 7 件のうち、外からリンクされている 3 件（cht#verify・wavelet-matrix#usage・two-sat#acl）は張り替えを同じ作業に入れる
- 見出しの長さ（全体） ｜ — ｜ 60 字を超える見出しは 37 か所（cpp 23・patterns 7・dp 2（cht・monge）・ds 1（priority-queue L182）ほか）。ほかの分野にはない ｜ §14-12（目安） ｜ cpp と patterns の書き方の型から来るので、直すならメインが型を決めてからまとめて直す
