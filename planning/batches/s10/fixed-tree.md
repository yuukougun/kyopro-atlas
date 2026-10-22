# 工程10 直し：tree・string（s10）

5 つの一覧（audit-facts・audit-figure・audit-relations・audit-shared・audit-structure）の「## tree」「## string」の項目を直した結果。残したものと理由は [left-tree.md](left-tree.md)。

## 数

| 一覧 | 項目 | 直した | 一部だけ直した（残りは left） | 残した | 直さなくてよい |
|---|---|---|---|---|---|
| audit-facts | 4 | 3 | 1 | 0 | 0 |
| audit-figure | 38 | 38 | 0 | 0 | 0 |
| audit-relations | 11 | 6 | 5 | 0 | 0 |
| audit-shared | 5 | 3 | 0 | 1 | 1 |
| audit-structure | 13 | 9 | 2 | 2 | 0 |
| 計 | 71 | 59 | 8 | 3 | 1 |

直した数（一部を含む）は 67、残したのは 3（steiner-subtree の練習の節、string-basics の落とし穴の定型、hashing-for-sets の trap.jp）。

## 直したもの

### audit-facts

- tree-ratio-greedy L46：「木のトポロジカル順序」→「木のトポロジカル順」
- palindrome：本文の「歩道」をすべて「ウォーク」に（要点の囲み・本文・確認問題・落とし穴・問題の要約の行）。front matter の signs は left
- trie L77：「1024 MB」→「1024 MiB」。同じ文の「約 52 MB」「約 124 MB」も「約 50 MiB」「約 118 MiB」に計算し直した
- string-automaton-dp：「Aho-Corasick」→「Aho-Corasick 法」（要点・見出しと sections の title・本文・例題・参考の説明）。summary は left

### audit-figure（38 項目・39 枚）

すべて `python3 tools/render_svg.py --width 360` で撮って目で確かめ、監査と同じ計算（表示の倍率 = min(width, 328) / viewBox の幅）で 9px 未満の文字が 0 になり、width・height が viewBox と同じ比であることを確かめた。

- 幅を 400 前後に描き直した（文字 14〜16）：small-to-large/doubling、steiner-subtree/root-at-terminal、tree-distance/two-sources、leaf-first/peel-matching、tree-bipartite/depth-parity、tree-centroid/walk・center-vs-centroid、tree-construction/nontree-pair・parent-range、tree-degree/caterpillar・pruefer、tree-diameter/spine、aho-corasick/failure-links・fail-tree、hash-safety/birthday（式から曲線を計算し直した。K = 10^5 で 0.993、K = 10^6 で 2.2 × 10^-7）、hashing-for-sets/prefix-sum-hash、palindrome/symmetric-pairs（幅 440）、rolling-hash/prefix-hash・segtree-merge、string-basics/compare・rotation-window、subsequence-matching/next-table、suffix-array/banana（幅 490）
- 横に 2 枚並んだ図を縦に積んだ（幅 310〜340）：tree-basics/remove-add-edge、tree-traversal/orders、trie/lcp-sum。代替テキストと本文の「左・右」を「上・下」に直した（tree-basics L104、trie L115・L117）
- 文字だけ大きくした（配置はそのまま）：complete-binary-tree/binary-path（17）、hld/decomposition（17）、tree-edge-contribution/edge-pairs（17）、palindrome/manacher-mirror（17）、tree-imos/marks-and-sweep（12→13）、tree-path/decompose・meeting・intersection（14→15）、kmp/shift（15）、string-automaton-dp/kmp-abab（16）
- width・height を足しただけ：centroid-decomposition/decomposition、lca/jump、z-algorithm/z-box

### audit-relations

- small-to-large#dsu-on-tree：前提の文から hld を外し、重い子・軽い子・軽い辺を節の中で定義した（HL 分解へは参照のリンク）。軽い辺で半分以下になる理由も 1 句足した
- tree-centroid L92：「根のない木の同型判定では、中心か重心を根にして形を比べる（木の同型判定は中心を使う）。どちらも 2 個のときは…」に直した。tree-isomorphism には「重心を使ってもよい」の文がすでにあった
- related：tree-centroid（+tree-isomorphism）・tree-isomorphism（+tree-centroid#one-or-two）、tree-edge-contribution（+steiner-subtree）・steiner-subtree（+tree-edge-contribution#edge-pairs）、tree-imos（+root-path-dfs#path-statistics）・root-path-dfs（+tree-imos#depth-limited、+minimax#tree）、tree-construction（+interval-dp-advanced#dfs-order-trees）、dynamic-tree（+euler-tour#in-out）、kmp（+divisor-inclusion-exclusion#period）。相手が comb・dp のページの分は left
- tree-edge-contribution L131：「黒を結ぶ木」の定義に [指定頂点を結ぶ最小の部分木](../tree/steiner-subtree.md) へのリンクを足した
- リンクの文字（§7）：tree-construction L124・L190、tree-degree L160・L165、tree-distance L83、tree-centroid L98・L224 を相手の題名か節の見出しにそろえた。comb の 2 か所は left
- string-automaton-dp#multiple-patterns：終端の印の受け継ぎの説明（例・式・理由）を 1 段落に縮め、aho-corasick#inherit-terminal へリンクした。落とし穴の重複も aho-corasick#pitfalls へのリンクに縮めた

### audit-shared

- tree-diameter：abc267_f を練習に足し（diff 順）、方針の折りたたみに LCA の例題へのリンクを置いた。L162 の名前だけの言及を `#practice` へのリンクにした
- tree-degree：abc303_e を練習に足し、方針に tree-basics の例題へのリンクを置いた
- lca：typical90_ai を練習に足し、方針に auxiliary-tree の例題へのリンクを置いた
- 行は `python3 tools/fix_problems.py --page <id>` で台帳から埋めた
- tree-edge-contribution の abc479_e は「直さなくてよい」のとおり変えていない

### audit-structure

- auxiliary-tree：見出しを「圧縮木で木 DP をするときの要点」（anchor `usage` のまま）にし、資料を `## 学ぶための資料 {#resources}` に分けた。anchor を library にする件は left
- tree-isomorphism：`## 公開ライブラリと自作するときの要点 {#library}`（sections にも足した。Nyaan 氏の RootedTreeHash と ei1333 氏の tree_isomorphism の使い方はソースで確かめた）と `## 学ぶための資料 {#resources}` を足した。練習問題の節に §16-5 の 1 文を置いた。参考の「学ぶための資料」の添え書きを外した
- tree-imos・tree-traversal・string-basics・subsequence-matching：`## 上位の手法へのつながり {#next-steps}` を足した（行き先の anchor は check_pages で確かめた）
- hld L196・L200〜201：解法の詳細の箇条書きの句点をそろえた
- tree-centroid L31：「何ができるか」を何ができるかから始まる文にした（summary は left）
- suffix-automaton：`## ライブラリと Library Checker での確かめ方 {#library}`（sections にも足した）と `## 学ぶための資料 {#resources}` を立て、ACL の段落を移した。逆 Manacher・逆 Z に Library Checker の問題がないことは library-checker-problems の string の一覧で確かめた。要点の「何ができるか」を何ができるかから始め、「入口だけをまとめる」の文を消した。参考の「学ぶための資料」の添え書きを外した

## 検査

- `python3 tools/check_pages.py`：エラー 0・警告 0
- `npm run lint:text`：tree・string のページはエラー 0（`npx textlint docs/tree/*.md docs/string/*.md` でも 0）。全体では 1 件のエラーが docs/ds/partially-persistent-union-find.md L122（UnionFind → Union-Find、prh）にあり、並行して直しているほかの分野のファイルで、この担当では直していない
- `python3 tools/check_snippets.py --changed`：期待と違う 0（この担当ではコード片を変えていない。拾われた 1 件はほかの分野の変更）
