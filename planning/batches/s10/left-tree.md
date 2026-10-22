# 工程10 直し：tree・string で残したもの（s10）

担当（tree・string）のファイルの外に要る直しと、判断の要るもの。メインがバッチの終わりにまとめて反映する。

## ほかの分野・共有ファイルに要る直し

- **docs/comb/minimax.md の related**（audit-relations tree）：`root-path-dfs` を足す。root-path-dfs 側の related には `minimax#tree` を足した
- **docs/comb/divisor-inclusion-exclusion.md の related**（audit-relations string）：`kmp#count-periodic` を足す。kmp 側の related には `divisor-inclusion-exclusion#period` を足した
- **docs/dp/interval-dp-advanced.md の related**（audit-relations tree）：`tree-construction` を足すかはメインが決める（tree-construction 側には `interval-dp-advanced#dfs-order-trees` を足した）
- **リンクの文字を相手の題名にそろえる**（audit-relations tree の §7）：docs/comb/counting-bijection.md L126 と docs/comb/counting-labeled-graphs.md L283 の「ラベル付き木の数と Prüfer 列」→ cayley-pruefer の題名「ラベル付き木の数え上げ」（節へのリンクなら節の見出しの言葉）。tree-degree の 2 か所は直した
- **docs/index/string.md・docs/index/tree.md**（生成）：string-automaton-dp#multiple-patterns の見出しを「複数パターンは Aho-Corasick 法（終端の印を受け継ぐ）」に、auxiliary-tree#usage の見出しを「圧縮木で木 DP をするときの要点」に変えた。tree-isomorphism#library・suffix-automaton#library・各 #resources・4 ページの #next-steps を足した。gen_site.py で作り直す

## front matter（執筆者が変えない項目）の提案

- **docs/string/palindrome.md の signs**（L18）：「グラフの歩道の文字列が回文になる最短の長さ」→「グラフのウォークの文字列が回文になる最短の長さ」（付録 A。本文の要点の囲み L41 は直した）
- **docs/string/string-automaton-dp.md の summary**（L13）：「KMP や Aho-Corasick の状態」→「KMP 法や Aho-Corasick 法の状態」（要点の囲みは直した）。aliases の「Aho-Corasick 上の DP」は別名なのでそのまま
- **docs/tree/tree-centroid.md の summary**（L13）：要点の「何ができるか」の 1 文目を「取り除いたときに残る成分の大きさがすべて N/2 以下になる頂点（重心。1 個か隣り合う 2 個ある）を、部分木サイズから O(N) で求める。」に直したので、summary も「何ができるか」を先に言う形にそろえる（audit-structure の提案）
- **related の追加は本文と同じ担当のページで行った**：tree-centroid（+tree-isomorphism）、tree-isomorphism（+tree-centroid#one-or-two）、tree-edge-contribution（+steiner-subtree）、steiner-subtree（+tree-edge-contribution#edge-pairs）、tree-imos（+root-path-dfs#path-statistics）、root-path-dfs（+tree-imos#depth-limited、+minimax#tree）、tree-construction（+interval-dp-advanced#dfs-order-trees）、dynamic-tree（+euler-tour#in-out）、kmp（+divisor-inclusion-exclusion#period）。§2.1 では related の変更は提案の扱いなので、メインが確かめる。sections に足したのは tree-isomorphism の library と suffix-automaton の library（§2.1 で認められた範囲）

## 判断の要るもの

- **docs/tree/auxiliary-tree.md の anchor `usage`**（audit-structure、§16-2 は `library`）：指示で anchor を変えないことになっているので、見出しを「圧縮木で木 DP をするときの要点」に縮め、資料を `## 学ぶための資料 {#resources}` に分けるまでにした。`usage` → `library` に変えるなら、転送と docs/index の作り直しが要る（外からのリンクは生成の索引だけ）
- **docs/string/suffix-automaton.md の `#build-your-own`**：H3 のまま残し（例題の詳細からリンクされている）、別に `## ライブラリと Library Checker での確かめ方 {#library}` と `## 学ぶための資料 {#resources}` を立てた。H3 を H2 にして anchor を library に変える案は anchor の変更になるので取らなかった
- **docs/string/string-basics.md の「計算量の落とし穴 {#cost-pitfalls}」**（audit-structure、§14-1）：anchor を変えないので現状のまま。§14-1 にそろえるかはメインが決める
- **docs/tree/steiner-subtree.md に練習問題の節がない**（audit-structure、§4・§10）：台帳に steiner-subtree の練習の問題がない（典型90 035 は力試し）。問題の補充の観点に回す
- **docs/string/hashing-for-sets.md L266 の trap.jp**（audit-shared）：`python3 tools/check_noai.py https://trap.jp/post/1594/` は「CERTIFICATE_VERIFY_FAILED（self-signed certificate）」で取れず、証明書を確かめずに取ると HTTP 404 だった（2026-10-22）。web.archive.org の照会は 429 で確かめられなかった。記事が移ったか消えた可能性がある。出典を外すか、写しで noai を確かめるかをメインが決める
- **docs/string/string-automaton-dp.md と aho-corasick.md の記号**（audit-relations string）：重なりは string-automaton-dp#multiple-patterns を 1 段落とリンクに縮め、持ち主を aho-corasick#inherit-terminal にした。記号は string-automaton-dp の `out`（パターンの集合の bit）を残し、「Aho-Corasick 法のページの mask と同じもの」と本文に書いた（コード片 aho-dp.cpp の `out` を変えると DP の節の記号も全部変わるため）。snippets/string-automaton-dp/aho-dp.cpp:build は DP のページで使う構造体なのでこのページに残した
- **docs/tree/tree-ratio-greedy.md L46**：「木のトポロジカル順」に直した（付録 A はトポロジカルソートで「トポロジカル順」は本文の語。用語集・付録 A に足すかはメインが決める）
- **docs/string/trie.md L77**：制限を「1024 MiB」にし、同じ文の「約 52 MB」「約 124 MB」も MiB に直して「約 50 MiB」「約 118 MiB」にした（5 × 10^5 × 26 × 4 バイト ＝ 49.6 MiB、× 62 ＝ 118.3 MiB）
