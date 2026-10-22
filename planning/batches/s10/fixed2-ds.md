# 工程10 2巡目 直し：ds・cpp（s10）

decisions.md・style-guide §17・left-*.md・verify-*.md のうち、ds・cpp のページ・図に要る直しの記録。commit はしていない。atcoder.jp・codeforces.com は開いていない。gen_site.py は実行していない。

検査（直した後）：`python3 tools/check_pages.py` エラー 0（警告は §17-10 の「同じ URL の出典の題名が違う」だけで、ds・cpp 側はどれも記事の題名にそろえ済み。下の「メインへ」）、`npx textlint docs/ds/*.md docs/cpp/*.md` エラーは生成物の ds/index.md・cpp/index.md の 3 件だけ（担当のページは 0）、`python3 tools/check_svg.py`（直した 16 枚）エラー 0。コード片は変えていない。

## 直したもの（23 項目）

### 表記（§17-8）

1. 「0 始まり」「1 始まり」→ 0-indexed・1-indexed：cpp/acl-reading（summary・sections の title・見出し #conventions・要点・本文。anchor は同じ）、cpp/cpp-reverse-index L261、ds/kth-element L72・L136、ds/wavelet-matrix L48・L138・L139、ds/persistent-data-structures L165、ds/merge-sort-tree L134
2. acl-reading の summary が 1 字長くなり（check_pages の 120 字）、summary と要点の「解説コードを、共通の約束」の読点を外し「書き方が分かる」→「書き方を知る」にした
3. 「上位ビット」→「上位 bit」：binary-trie・wavelet-matrix の summary（left-ds の提案。decisions で採用）
4. 「ダイクストラ」→「ダイクストラ法」：cpp/cpp-structured-bindings の見出し #pq-top-reference と sections の title、cpp/cpp-undefined-behavior L43（left-graph の「ほかの分野」）
5. 多重テストケース・歩道・最上位ビット・最下位ビット・平衡二分木・フェニック木：ds・cpp の本文・summary・signs に残りはない（aliases と別名の行だけ。決まりどおり残した）

### anchor（§17-3）

6. ds/wavelet-matrix の `usage` → `library`（見出しと sections）。本文のリンクは ds/persistent-data-structures L171 の 1 か所だけで、`#library` に張り替えた。生成物 docs/index/ds.md L664 に古い anchor が残る（gen_site で追従）

### 重なり（§17-11）

7. ds/rollback-union-find #offline-dynamic-connectivity：手順 3 段と頂点への加算の扱い（経路のすべての sum に足す方法）を外し、持ち主を graph/offline-dynamic-connectivity と書いて、要点 3 つ（時間軸に載せる→#time-segment-tree、入るとき併合・出るとき取り消す→#dfs-rollback、計算量 $O(Q \log Q \log N)$）とリンクに縮めた。anchor は残した。練習の Dynamic Graph Vertex Add Component Sum の行は、加算の扱いの置き場として offline-dynamic-connectivity#dfs-rollback を指すようにした

### 個々の件（decisions）

8. advanced-ds-catalog L155「HLD・重軽分解」→「HL 分解（HLD）」
9. partially-persistent-union-find の UnionFind の prh エラー：1 巡目の直しで消えていた。あわせて Library Checker の題名を問題の info.toml の `Persistent Unionfind` にそろえた（L80 のリンクの文字と参考の題名）
10. union-find-applications の doi.org：書誌情報だけの出典にした（Journal of the ACM 31(2), 1984, pp. 245–281, doi:10.1145/62.2160。リンクなし）
11. sqrt-decomposition の suzukiapple.tumblr.com：ikatakos 氏の「トヨタ自動車プログラミングコンテスト2024#8（AtCoder Beginner Contest 365）G問題メモ」に替えた。check_noai で指定なしを確かめ、解法の節だけを読んだ（記録の多い人を基準にした前計算とイベント順の処理の使い分け。本文の方針「記録が C 件以上の人は前計算、少ない人どうしは区間の列をマージ」と合う）

### 出典の題名（§17-10）

12. ds・cpp の参考・資料の節で、同じ URL の題名がサイトの中で違うものを、記事の題名（取得して title・h1 を確かめた）か、多数のページが使う形にそろえた。著者名は drken・maspy・ikatakos・kmjp・tmsn（zenn の表示名）にそろえた。直したのは 42 行：cpp-algorithms・cpp-environment（2）・cpp-initialization・cpp-lambda・cpp-macros-template-file（4）・cpp-range-for・cpp-types-literals・cpp-views-cpp23・balanced-bst（2）・advanced-ds-catalog・cdq-divide-and-conquer・inversion-number（3）・kth-element（2）・lazy-segment-tree（2）・linked-list・merge-sort-tree・monotonic-stack・offline-queries（3）・partially-persistent-union-find・segment-tree-binary-search（2）・segment-tree・stl-containers・top-k-multiset・union-find-applications・union-find（3）・weighted-union-find（3）
    - Library Checker の問題の一覧は、題名を `yosupo06「library-checker-problems」`・`yosupo06「library-checker-problems/data_structure」` にし、問題名の括弧書きは説明の側へ移した（advanced-ds-catalog・balanced-bst・cdq-divide-and-conquer）

### 図（§17-6：端の文字を viewBox から 10px 離す）

13. ヘッドレスの Chrome で ds・cpp の全部の図の文字の枠を測り（一時置き場の measure.py。render_svg と同じフォント）、端に近いものを直した。はみ出していた図はなかった（0〜5px が最も近い）
    - 右端：stack-techniques/bracket-stack（「閉じ括弧の相手は、…。」が右端に 0px → 読点を外し、幅 402）、balanced-bst/split・treap（「sz2」が 4px → 幅 386）
    - 左端：linked-list/insert-erase・wavelet-matrix/levels・balanced-bst/split・treap の x=8（・7）の文字を x=10 へ
    - 上下（枠の下端が 8px 未満のもの。余白を 1〜3px 足し、背景の rect も合わせた）：acl-reading/template-args・cpp-undefined-behavior/reallocation・interval-set/assign・inversion-number/inversions・monotonic-stack/procedure・ordered-set/neighbors・parallel-binary-search/rounds・stack-techniques/bracket-stack・sweep-line-2d/window-to-rectangle・top-k-multiset/move-boundary・union-find-applications/next-pointer・wavelet-matrix/levels・weighted-union-find/compression
    - 360px で撮って見た（文字の切れ・重なりなし）。wavelet-matrix/levels は幅を広げると 9px 未満の文字が出るので、幅は 400 のまま文字を動かした

## 残したもの（5 項目）

1. **trap.jp**（cpp-environment L304、cpp-macros-template-file L315・L316）：2026-10-22 に証明書の検証を外して取得したが、HTTP 503 で robots の meta を確かめられなかった。decisions の「取れない記事は外す」は hashing-for-sets の post/1594 についての判断なので、このページの 3 か所は残した。付録 B は「確かめられなかった」のまま
2. **frequency・frequency_evidence**（union-find の「前提として 17 ページ」など）：tools/frequency.py で全ページを付け直す担当に任せた（front matter のこの 2 項目は触っていない）
3. **生成物**：docs/ds/index.md L74・L75（上位ビット）、docs/cpp/index.md L43（0 始まり）、docs/index/ds.md の `wavelet-matrix#usage`。どれも summary・anchor から作られるので gen_site.py で追従する（textlint の担当の外のエラー 3 件はこれ）
4. **出典の題名で、ほかの分野のページが違う形のもの**（ds・cpp 側は記事の題名にそろえ済み。check_pages の警告に出る）：
    - github.com/atcoder/ac-library/tree/master/document_ja：guide/cheatsheet の「AtCoder Library のドキュメント（日本語）」→ AtCoder「AC Library のドキュメント（document_ja）」
    - github.com/yosupo06/library-checker-problems：comb・dp・guide などの「yosupo「Library Checker の問題（…）」」→ yosupo06「library-checker-problems」（括弧書きは説明へ）。data_structure の URL は dp/cht も yosupo06「library-checker-problems/data_structure」に
    - ikatakos 2026/0829_abc473：comb/probability-symmetry の「ikatakos の競プロ Wiki「ABC473」」→ ikatakos「AtCoder Beginner Contest 473 D,E,F,G問題メモ」
    - qiita gotoki_no_joe a1f1755cfe99192773d6：comb/linearity-of-expectation の「ABC276 の解説」→ 記事の題名「ABC276 A～F をHaskellで」
    - zenn shinonome81：comb/counting-basics は tmsn（ds/linked-list を合わせた）。drken 2024/09/24（ABC243 D）は tree/complete-binary-tree の「3Q」が誤りで、記事は「2Q」。drken 2022/12/29（ABC282 F）は misc/interactive を記事の題名「AtCoder ABC 282 F - Union of Two Sets (2D, 青色, 600 点)」に。pyteyon 2019/09/30 は記事の題名が「ABC040: D - 道路の老朽化対策について」で graph/union-find-connectivity も違う。fenwicktree.hpp は ds/fenwick-tree が AtCoder Library「fenwicktree.hpp」、guide/library-design が AtCoder「ac-library」の fenwicktree.hpp
5. **check_svg の幅の警告**（幅 400 を超える ds・cpp の図 14 枚）：§17-6・decisions に直す指示がなく、文字は 9px 以上なのでそのままにした

## メインへ

- wavelet-matrix の anchor を変えた。localStorage の鍵は anchor を使わない（§17-3）ので転送は入れていない。gen_site.py で docs/index/ds.md を作り直すと古い `#usage` が消える
- rollback-union-find を縮めたので、頂点の値への加算の扱いは offline-dynamic-connectivity L98（入るときに根の合計に足し、出るときに引く）だけになった。rollback-union-find にあった「経路のすべての sum に足す」方法は、もうサイトにない
- 図の余白は、Chrome で測った文字の枠（フォントの上下の余白を含む）の 8px を下限にした。この枠は字の形より 1〜2px 大きいので、字そのものは 10px 程度離れている
