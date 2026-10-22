# 工程10 直しの残り（graph・geometry）

graph・geometry の直し担当が、担当の範囲（docs/graph・docs/geometry の本文、その snippets・図）の外にあるため、または判断が要るために直さなかったもの。

## front matter の summary・frequency_evidence（メインが反映）

- docs/graph/euler-path.md L13（summary）：「Hierholzer 法で O(M) で作れる」を「O(N + M)」に。要点の計算量と complexity は $O(N + M)$（audit-facts）
- docs/graph/steiner-tree.md L13（summary）：「O(3^K N + 2^K M log N)」を「O(3^K N + 2^K (N + M) log N)」に（audit-facts）
- docs/graph/degree-sqrt.md L13（summary）：「4-サイクルの検出」を「長さ 4 の閉路の検出」に。本文・sections・complexity は直した。aliases の「4-サイクルの検出」は検索語として残した（audit-facts）
- docs/graph/k-shortest-paths.md L13（summary）：「歩道なら…ダイクストラで求まり、…歩道の列挙は」を「ウォークなら…ダイクストラ法で求まり、…ウォークの列挙は」に。signs（L16）と本文は直した（audit-facts）
- docs/graph/minimum-spanning-tree.md L23（frequency_evidence）：「前提として 3 ページに届く（直接 3）」は今の prerequisites では 4（直接 4）。shared の frequency の項でまとめて直す（audit-facts）

## 台帳の summary（表記の正規形「ウォーク」）

本文の行は台帳から作られるので、台帳を直して fix_problems を流す（§13-7）。

- abc286_g（euler-path の練習）・abc244_f（extended-dijkstra の練習）・abc197_f（extended-dijkstra の力試し）・abc338_f（warshall-floyd の練習）：「歩道」を「ウォーク」に

## ほかの分野のページ（それぞれの担当かメインが直す）

- 「ダイクストラ」→「ダイクストラ法」（付録 A。audit-facts の同じ型）：tree/tree-distance L45（見出し。sections の title も）、comb/game-retrograde-analysis L128（見出し。sections も）・L200・L226、string/palindrome L122、cpp/cpp-structured-bindings L156、cpp/cpp-undefined-behavior L43。graph の 4 ページ（k-shortest-paths・steiner-tree・difference-constraints・bellman-ford）は直した。docs/index/graph.md の見出しの一覧は gen_site で追従する
- 「4-サイクル」→「長さ 4 の閉路」：thinking/symmetry-pigeonhole-casework L109 のリンクの文字。roadmap L576 は生成物なので gen_site で追従する
- dp/lis.md L203：dilworth-path-cover へのリンクの文字「Dilworth の定理とパス被覆」を「[最小パス被覆と Hall の定理](../graph/dilworth-path-cover.md#path-cover)」か「DAG の最小パス被覆」に（audit-relations。graph 側の bipartite-matching・konig-theorem は直した）
- math/determinant.md L131：リンクの文字「最小全域木の発展」を「[特殊な最小全域木](../graph/spanning-tree-advanced.md#manhattan)」に（audit-relations。geometry/manhattan-chebyshev は直した）
- misc/bitset-speedup.md の related に `degree-sqrt#triangles` を足す（audit-relations）
- dp/subset-enumeration-dp.md の related に `chromatic-number` を足す（audit-relations。chromatic-number 側には subset-enumeration-dp を足した）

## 判断が要るもの

- graph/spanning-tree-advanced：keyence2019_e の扱いは §16-17 の判断待ち（## shared (3)）。練習の節は「ABC で必須になる問題は確認できなかった」と Library Checker だけのまま
- graph/two-sat.md L122：ライブラリの節の anchor が `acl`。§15-3 では許されるが、§16-2 の `library` にそろえるかはメインが決める。そろえるなら sections と cpp/acl-reading.md L113 の `two-sat.md#acl` を張り替える
- graph/complement-graph-bfs：黄の technique なのに練習問題の節がない。台帳にこのページの練習・力試しの問題がない（例題 1 問だけ）ので、問題の補充の観点に回す
- geometry/manhattan-chebyshev.md L55：`## 必要になる場面 {#motivation}` が sections にない（軽微。audit は「必須ではない」）。理解度のチェックの単位にするなら sections に足す。今回は変えていない
- graph/extended-dijkstra：台帳どおり abc348_d・typical90_bb・zone2021_e を練習に足したので、練習が 9 問になり §10 の目安（2〜6）を超えた。減らすなら台帳の役割を変える（どれかを本文の参照だけにする）判断が要る
- 図の直し方（§15-8）：横に並んだ図の多くは、2 つのファイルに分けずに 1 枚の SVG の中で縦に積み、幅を 400 以下にした（文字は 9px 以上、width・height を付けた）。代替テキストと本文の「左・右」は「上・下」に直した。「2 枚に分ける」を別のファイルにすることと読むなら、メインが決める

## 担当外で見つけたもの

- docs/ds/partially-persistent-union-find.md L122：textlint のエラー（prh「UnionFind => Union-Find」）。npm run lint:text のエラーはこの 1 件だけで、graph・geometry のページのエラーは 0
