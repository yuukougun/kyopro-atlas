# 工程10 直し：ds・cpp（s10）

audit-*.md の「## ds」「## cpp」の項目を直した記録。直した 74 項目、残した 14 項目（理由は `left-ds.md`）。

検査：`python3 tools/check_pages.py` エラー 0・警告 0、`npm run lint:text` エラー 0（警告だけ）、`python3 tools/check_snippets.py --changed` 期待と違う 0（ds・cpp のコード片は変えていない）。図は 360px で `python3 tools/render_svg.py` を撮って目で確かめ、ds・cpp の全 SVG で 360px 表示の文字が 9px 以上、width・height が viewBox と同じであることをスクリプトで確かめた。gen_site.py は実行していない。commit していない。

## 事実・表記（audit-facts）5 項目

- lazy-segment-tree-patterns：「フェニック木」→「BIT」、「平衡二分木」→「平衡二分探索木」（2 か所）
- 「上位ビット」「最下位ビット」→「上位 bit」「最下位 bit」：wavelet-matrix の見出しと sections の title（anchor build は同じ）・要点、fenwick-tree L72 のリンクの文字（相手の見出し「popcount・最下位 bit」に合わせた）、kth-element L74。summary の 2 つは提案として残した
- cpp-integer-overflow L91：「C++14・C++17 では処理系定義で、GCC では同じ値になる」を足した（C++14 の [expr.shift] は、符号なしの型で表せる値を結果の型に変換した値とし、その変換は処理系定義。GCC は 2 の補数で折り返す）
- cpp-integer-overflow L92：「最上位ビット」→「最上位 bit」

## 図（audit-figure）44 項目

2 枚に分けたもの：
- priority-queue/heap-push-pop.svg → heap-push.svg・heap-pop.svg（幅 340）。heap-push-pop.svg は消した。本文は「下の 2 つの図」にし、図の後に「動く値は根と葉を結ぶ 1 本の経路の上だけで、入れ替えは高々木の高さ回」の 1 文を足した（[低] の項目）

幅 400 で描き直したもの（横に並んだ部分を縦に積む・文字を折り返す）：
- ds：monotonic-stack/histogram・procedure、priority-queue/lazy-deletion、segment-tree-binary-search/climb-descend（手順の 5 行は本文の箇条書きと同じなので図から外した）、segment-tree/prod-nodes・set-path、top-k-multiset/move-boundary、union-find/path-compression、global-offset/offset、kth-element/bit-binary-search、linked-list/insert-erase、offline-queries/distinct-count-sweep、ordered-set/neighbors、persistent-data-structures/version-tree、segment-tree-on-values/count-sum-tree、weighted-union-find/compression・merge
- cpp：cpp-macros-template-file/bundling、cpp-types-literals/ranges（[低] の INF の丸と目盛りの重なりも解消。目盛りの数は 1 つおき）、cpp-algorithms/unique-erase、cpp-container-idioms/iterators、cpp-lambda/capture・call-path、cpp-math-functions/bit-count（桁 28〜6 を省略して示す）、cpp-structured-bindings/hidden-variable、cpp-views-cpp23/views-gallery
- 左右を上下に積んだ図は、代替テキストの「左は・右は」を「上は・下は」に直した（union-find/path-compression、weighted-union-find/merge）

幅を詰めた・文字を大きくしたもの：
- binary-trie/xor-min（幅 560）、persistent-data-structures/path-copying（幅 480）、union-find-applications/next-pointer（幅 440。番兵の字を箱の中へ）、sqrt-decomposition/buckets（viewBox を 32〜688 に切り詰めて幅 656）
- mo-algorithm/query-order（12・13 → 14）、parallel-binary-search/rounds・cdq-divide-and-conquer/split（10 → 11）、inversion-number/inversions（14 → 15）、merge-sort-tree/tree（15 → 17）、segment-tree-monoids/bracket-merge（11・13 → 14）、sparse-table/cover（14・15 → 16）、cpp-initialization/ctad-flow（15 → 16。右の箱を広げた）、cpp-math-functions/division（14 → 15）

width・height だけを足したもの：interval-set/assign、stack-techniques/bracket-stack、union-find-applications/count-on-merge、cpp-integer-overflow/wrap-around、cpp-range-for/copy-ref-move（ほかの描き直した図にもすべて付けた）

## 関係（audit-relations）5 項目

- リンクの文字を相手の題名に：priority-queue L196・cdq L119（見慣れないデータ構造の名前と用途）、union-find L137・L202・union-find-applications L203・partially-persistent-union-find L114（ロールバックできる Union-Find）、merge-sort-tree・segment-tree-on-values（クエリの先読み）、offline-queries・parallel-binary-search（Union-Find で連結性を扱う）、binary-trie（K 番目の値を求めるデータ構造）
- related：merge-sort-tree ↔ sqrt-decomposition を互いに足し、sparse-table に divide-and-conquer を足した（逆向きは basics なので残した）
- cpp-environment の related に cpp-views-cpp23 を足した（前提の判断は残した）

## 台帳との食い違い（audit-shared）3 項目

問題は `python3 tools/ap.py show` で実在・題名・difficulty を確かめ、要約は台帳の summary を使った。方針は台帳の approach と evidence の記事の題名で確かめた（atcoder.jp は開いていない）。
- monotonic-stack の練習に ABC189 C（diff 565）を足した（ヒストグラムの最大長方形と同じ問い。O(N^2) でも通るが単調スタックで O(N)）
- union-find-applications の練習に ABC206 D（diff 879）、力試しに ABC131 F（diff 1937）を足し、参考に drken 氏の 2 記事を足した
- stack-techniques の練習に ABC283 D（453）・ABC428 C（483）・ABC237 D（544）を足し、参考に drken 氏の ABC283 D の記事を足した。ABC237 D の「後ろから deque の両端に足す」方針は手元の総当たりで確かめた

## 構成（audit-structure）17 項目

- parallel-binary-search・partially-persistent-union-find・rollback-union-find：`## 自作するときの要点と Library Checker {#library}` を立てて自作の要点を移し（sections にも足した）、`## 学ぶための資料 {#resources}` を足した。参考の行の「（学ぶための資料）」の添え書きを消した
- segment-tree-beats：H3「自作するときの要点」を `## 自作するときの要点と Library Checker {#library}` に上げ、sections に足した
- wavelet-matrix：本文の「学ぶための資料は次の 3 つ」を `## 学ぶための資料 {#resources}` の節にした（anchor usage の変更は残した）
- advanced-ds-catalog：complexity を null にした
- ordered-set：`## 上位の手法へのつながり {#next-steps}` を足した（区間の集まり・2 つの multiset・K 番目と個数・未訪問の頂点の集合・集合の併合）
- binary-trie：ヒントの箇条書きの句点をそろえた
- weighted-union-find：`acl: []` のページの「ACL では」の囲みを本文の 1 文にした
- cpp の見出しの波かっこ：cpp-algorithms #projection、cpp-initialization #vector-init・#array-init・#designated-init、cpp-structured-bindings #pair-tuple を言葉に言い換え、sections の title も同時に直した（anchor は同じ。designated-init の例 `Edge{.to = v, .cost = c}` は本文へ移した）
- cpp-views-basics：要点に「views::iota(0, v.size()) が符号の違いで通らない・元のコンテナより長く使えない」の型と寿命の罠を足した
- cpp-lambda：要点に再帰の 4 つの書き方を足し、summary に合わせた

## そのほか

- partially-persistent-union-find の資料の節で、出典の題名「UnionFindTree に関する…」が prh のエラーになったので、資料の節では題名を引かずに言い換えた（参考の節の題名はそのまま）
