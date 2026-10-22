# 工程10 直しの結果（graph・geometry）

audit-*.md の「## graph」「## geometry」の項目を直した結果。直した 86 項目、残した 8 項目（理由は left-graph.md）。ページの id・URL・既存の anchor は変えていない。

## 検査

- python3 tools/check_pages.py：エラー 0・警告 0
- npm run lint:text：エラー 1（docs/ds/partially-persistent-union-find.md L122 の prh。担当外で、left-graph.md に書いた）。graph・geometry のページのエラーは 0
- python3 tools/check_snippets.py --changed：コード片 1（zero-one-bfs/turns.cpp）、期待と違う 0
- 図：graph・geometry の全 SVG を audit と同じ式（360px で本文の幅 328px）で測り、9px 未満の文字が 0、width・height が viewBox と同じ比であることを確かめた。直した図は python3 tools/render_svg.py --width 360 で撮って目で確かめた

## audit-facts（直した 5・残した 3）

- steiner-tree L117：「1024 MB」→「1024 MiB」
- degree-sqrt：「4-サイクル」→「長さ 4 の閉路」（節題と sections の title、要点、complexity、本文 L152・L162・L236・L244。anchor `four-cycles` はそのまま）。summary は残した
- 「歩道」→「ウォーク」：extended-dijkstra L274、scc L177、k-shortest-paths L16（signs）。summary は残した
- 「ダイクストラ」→「ダイクストラ法」：k-shortest-paths（本文・節題・sections・complexity）、steiner-tree の節題、difference-constraints の節題（「ベルマンフォード法」も）、bellman-ford の節題。手法名（拡張ダイクストラなど）は除いた。ほかの分野は残した
- zero-one-bfs：snippets/zero-one-bfs/turns.cpp の `dx`・`dy` を `di`・`dj` に、本文 L162 の式も $\mathrm{di}_d$・$\mathrm{dj}_d$ に
- 残した：euler-path・steiner-tree の summary、minimum-spanning-tree の frequency_evidence

## audit-figure（直した 43）

- 横に並んだ図を縦に積み直して幅を 400 以下にした：bipartite-graph/coloring、connected-components/components（2×2）、degree-sqrt/push-pull、minimum-spanning-tree/kruskal-steps、namori-graph/redraw・peel、union-find-connectivity/reverse-time（2×2）、cycle-detection/three-color、extended-dijkstra/hub、graph-construction/dfs-bfs-trees、complement-graph-bfs/take-unvisited、geometry-vectors/cross-sign・shoelace、manhattan-chebyshev/rotate・diagonal、rotation-transform/affine-compose・grid-rotation
- 描き直して幅を 420 以下にした：functional-graph/rho、min-cut/residual-cut・vertex-split、project-selection/cut-example
- 文字を大きくした（幅は同じ。重なりは撮って確かめ、必要な所は文字を 2 行に分けた・凡例を移した）：bellman-ford/negative-cycle・rounds、dfs/order、dijkstra/two-ends・graph、euler-path/conditions、extended-dijkstra/layers（層の名前を短くした）、grid-graph/obstacle-dual、small-graph-brute-force/isomorphism・coloring-order、time-dependent-dijkstra/fifo、zero-one-bfs/example-graph、bfs/layers、difference-constraints/example、shortest-path-dag/dag、topological-sort/cycle、argument-sort/half-planes、convex-hull/max-slope・fan
- width・height を付けただけ：bipartite-matching/alternating・reduction、euler-path/hierholzer、grid-graph/flatten、circle-geometry/enclose-candidates・two-circles、geometry-precision/double-spacing
- 縦に積んだ図の代替テキストと本文の「左・右」を「上・下」に直した：bipartite-graph、min-cut（vertex-split）、namori-graph（redraw）、cycle-detection（L71・L73・L145）、extended-dijkstra（hub）、graph-construction（L52・L54・L91）、connected-components L96（「右端」→「右下」）、geometry-vectors（cross-sign）、manhattan-chebyshev（rotate）
- complement-graph-bfs の代替テキストを 251 字から要点の 2 文に縮めた

## audit-relations（直した 8・残した 1）

- bipartite-graph L171：最小カットで表せる 2 変数の項を「片方だけ 1 のときコスト」の形とその和にし、project-selection#submodular へリンク
- bipartite-matching L157（「Hall の結婚定理」に）・L276、konig-theorem L128・L244：dilworth-path-cover へのリンクの文字を題名にそろえた
- difference-constraints L219、euler-path L230：「グラフへの帰着」に
- lowlink L120・L254：「辺の追加と削除が混ざる連結性」に。matrix-tree-theorem L112：「連結なグラフの数え上げ」に
- chromatic-number の related に subset-enumeration-dp を足した（相手側は残した）
- geometry：rotation-transform L218「Z-algorithm」、manhattan-chebyshev L250「特殊な最小全域木」
- 残した：degree-sqrt と bitset-speedup の related（bitset-speedup 側の直し）。lis L203・determinant L131 も残りに書いた

## audit-shared（直した 3・残した 1）

- connected-components：abc284_c を練習に足し、方針を書いた
- extended-dijkstra：abc348_d・typical90_bb・zone2021_e を練習に足し、方針（重要な点だけのグラフ・超頂点の補正・頂点倍化）を書いた（練習は 9 問になった）
- union-find-connectivity：abc413_g を練習に足し、方針（grid-graph#obstacle-dual）を書いた
- 残した：spanning-tree-advanced の keyence2019_e（§16-17 の判断待ち）

## audit-structure（直した 27・残した 3）

- 発展の概要に `## 自作するときの要点と Library Checker {#library}`（sections にも足した）と `## 学ぶための資料 {#resources}` を立て、各節に散っていた自作の要点・ACL の囲み・Library Checker の対応を集めた：dilworth-path-cover、flow-lower-bounds、k-shortest-paths、offline-dynamic-connectivity、spanning-tree-advanced（資料の節を練習問題の前へ移した）、geometry/advanced-geometry。各手法の節には集めた先へのリンクを 1 文残した。参考の行の「（学ぶための資料）」の添え書きは消した
- k-shortest-paths の練習問題に「ABC で必須になる問題は確認できなかった。」を足した
- matrix-tree-theorem：sections から resources を外した。graph-modeling：complexity を null に
- 基礎の 5 ページに `## 上位の手法へのつながり {#next-steps}` を足した：bfs、cycle-detection、graph-basics、grid-graph、topological-sort
- zero-one-bfs：`## 必要になる場面` に `{#motivation}` を付けた
- functional-graph・namori-graph・graph-construction：要点の「何ができるか」の 1 文目を何ができるかから始めた
- degree-sqrt・graph-construction・min-cut：箇条書きの句点をそろえた
- geometry/manhattan-chebyshev：`## ACL では {#acl}` の見出しを消し、囲みと続く段落を最遠点対の節へ移した（ページ内の `#acl` へのリンクは `#farthest-pair` に張り替えた）
- 残した：two-sat の anchor（メインの判断）、complement-graph-bfs の練習（台帳に問題がない）、manhattan-chebyshev の motivation を sections に足すか（任意）
