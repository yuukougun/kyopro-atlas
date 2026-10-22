# 工程10 2巡目：graph・geometry・tree・string の直し（s10）

decisions.md・style-guide §17・left-*.md・verify-*.md のうち、この 4 分野のページ・図に要る直しを行った。commit はしていない。gen_site.py は実行していない。

## 検査（直した後）

- `python3 tools/check_pages.py`：エラー 0。警告は「同じ URL の出典の題名が違う」だけ（この 4 分野が関わる 15 件は、どれもほかの分野のページの側が実際の題名と違う。下の「メインへ」）
- `npx textlint docs/{graph,geometry,tree,string}/*.md`：エラー 2 件で、どちらも生成物 docs/graph/index.md L42（k-shortest-paths の summary の古い写し「歩道」）。gen_site で消える
- `python3 tools/check_svg.py`：エラー 0
- コード片は変えていない（check_snippets は不要）

## 直したもの（19 件）

1. **front matter の summary・signs・aliases（decisions「個々の件」）**
    - graph/euler-path の summary：O(M) → O(N + M)
    - graph/steiner-tree の summary：O(3^K N + 2^K (N + M) log N)、「ダイクストラ法」
    - graph/degree-sqrt の summary：「長さ 4 の閉路の検出」（aliases と別名の行の「4-サイクルの検出」は残した）
    - graph/k-shortest-paths の summary：「ウォーク」「ダイクストラ法」
    - string/palindrome の signs：「グラフのウォークの文字列」
    - string/string-automaton-dp の summary：「KMP 法や Aho-Corasick 法の状態」
    - tree/tree-centroid の summary：「何ができるか」を先に言う形（要点の 1 文目に合わせた）
    - tree/static-top-tree：aliases と本文の別名の行から「重軽再帰 DP」を外した
2. **「ダイクストラ」→「ダイクストラ法」（付録 A）**：graph/min-cost-flow・graph/time-dependent-dijkstra の summary、tree/tree-distance の見出しと sections の title（「1 点からの距離（ダイクストラ法はいらない）」。anchor `from-one` は同じ）、string/palindrome L122 のリンクの文字（「拡張ダイクストラの…」→「[状態を頂点にするページの両端から伸ばす節]」、相手の題名に合わせた）。aliases・別名の行・出典の題名の「ダイクストラ」は残した
3. **§17-8 の表記**：4 分野の全ページを grep した。直したのは「1 始まり」「0 始まり」の 4 か所（graph/graph-basics L193・graph/two-sat L140・tree/complete-binary-tree L152・tree/tree-traversal L78）→ 0-indexed・1-indexed。多重テストケース・上位／最上位／最下位ビット・平衡二分木・フェニック木は本文・summary・signs に残っていなかった。台帳から作る問題の行の「歩道」（euler-path・warshall-floyd・extended-dijkstra）は触っていない（台帳の担当の fix_problems で直ったらしく、今は textlint のエラーに出ない）
4. **§17-1 complexity**：この 4 分野の guide・hub・pattern は graph/graph-modeling の 1 ページで、すでに null
5. **§17-3 anchor**：tree/auxiliary-tree の `usage` → `library`（見出しと sections。見出しの文字は「圧縮木で木 DP をするときの要点」のまま）。全ページ・data・overrides を grep し、`auxiliary-tree#usage` へのリンクは生成物（docs/index/tree.md）だけ。geometry/advanced-geometry L206 の `../dp/cht.md#verify` を `#library` に張り替えた（cht 側は dp の担当が改め済み）
6. **§17-11 重なりの縮め**：tree/root-path-dfs#no-path-compression を 2 文と [ロールバックできる Union-Find の経路圧縮をしない理由](../ds/rollback-union-find.md#no-path-compression) へのリンクに縮めた（anchor・見出しは残した。記録する値の言い方は rollback-union-find に合わせて「根 2 つの値（par[s] と r の大きさ）」）
7. **graph/offline-dynamic-connectivity L98**：rollback-union-find#offline-dynamic-connectivity が要点とリンクに縮んだので、「そちらの書き方（加算を葉で行って取り消さない）とは食い違わない」という古い突き合わせの 2 文を消した（持ち主はこのページ、§17-11）
8. **keyence2019_e を graph/spanning-tree-advanced の練習に足した**（decisions）：囲みの行は台帳の spanning-tree-advanced 向けの alternatives の summary、方針は approach に Borůvka 法の節の例（同じ重み）への言及を足した。練習の節の 1 文目を「ほかのコンテストの 1 問と…Library Checker の問題を挙げる」に。参考の drken 氏の記事の行に「練習 KEYENCE2019 E の問いと…方針」を足した。`fix_problems.py --check` の keyence2019_e の警告は消えた
9. **練習の節がない 2 ページ**：graph/complement-graph-bfs（確認問題の前）と tree/steiner-subtree（力試しの前）に `## 練習問題 {#practice}` と「例題のほかに練習に置ける問題は確認できなかった。」を置いた（§16-5 の型）。問題は探していない（下の「残したもの」）
10. **出典**：string/hashing-for-sets の trap.jp/post/1594（取れない記事）を参考から外した。ABC250 E・ABC238 G の根拠は台帳の evidence に別にある
11. **図の余白（§17-6・verify-pages の 9 枚のうちこの分野の 4 枚）**：ヘッドレス Chrome で文字の枠と viewBox を測り（`scratchpad/s10b/graph_bbox.py`）、はみ出していた 4 枚に「はみ出し + 10px」の余白を足した。rolling-hash/prefix-hash（右へ 5.3px → 幅 390→406）、tree-traversal/orders（下へ 2px → 高さ 718→730）、hash-safety/birthday（左へ 1px → viewBox を −11 から、幅 420。右端の「10^10」も 1px まで近かったので右にも 9 足した）、segment-tree-graph/cover（下へ 0px → 高さ 230→240）。背景の rect も広げた。測り直してはみ出し 0、render_svg の 360px で 4 枚とも読めることを見た
12. **§17-10 出典の題名**：この 4 分野が関わる「同じ URL で題名が違う」80 URL のうち、4 分野のページの行（約 85 行・約 45 ページ）を 1 つの題名にそろえた。はてなブログ・ikatakos・qiita・kmjp・cnblogs などは記事の `<title>` を取って実際の題名にした（付録 B のドメインだけ）。AC Library の document_ja は「AtCoder Library「名前」（document_ja）」、library-checker-problems は「yosupo06「library-checker-problems」」（tree・graph のフォルダは「…/tree」「…/graph」）、judge の Shortest Path は「Library Checker「Shortest Path」」に。degree-sqrt の典型90 083 の行は題名をそろえ、「083 の解説の画像（083-01〜03）」を説明の側へ移した。題名を確かめて直したもの：drken ABC122 D（1Q, 水色, 400 点）・ABC243 D（2Q）・ABC357 E（1D）・ABC131 F（drken）、ikatakos ABC385（ユニークビジョン…E,F,G）・ABC454（キーサイト…E,F,G）、merom686 ABC296・ABC312・ABC447（記事の題名は「ABCnnn」だけ）、kyo-pro ABC288C・ABC292D、cnblogs の書き手（Billlly）、hamayan ABC222 E（半角の [ ]）、pyteyon「ABC040: D - …」

## 残したもの（9 件）

1. **生成物**：docs/graph/index.md L42・L43・L73（k-shortest-paths・steiner-tree・degree-sqrt の summary の古い写し。textlint の「歩道」2 件もここ）、docs/index/tree.md の auxiliary-tree#usage・tree-distance#from-one の題、docs/index/string.md、guide/problem-sets の from-one の題。gen_site.py で作り直す
2. **tree/static-top-tree L71 の「重軽再帰 DP」を #heavy-path-dp へのリンクにする件**：L71 は #heavy-path-dp の節の中にあり、自分の節へのリンクになるので張っていない。練習の方針 L174 はすでに「[重いパスの上で DP をセグ木に載せる](#heavy-path-dp)の節の最後に触れた重軽再帰 DP」とリンクしている。用語集に「重軽再帰 DP」を足すならそちらへのリンクにできる（提案）
3. **練習の問題の探索（complement-graph-bfs・steiner-subtree）**：台帳への追加はこの担当の外なので、問題は探さず §16-5 の 1 文を置いた。台帳の担当が問題を見つけたら、本文の 1 文を囲みに置き換える
4. **図の端の余白（はみ出していないもの）**：§17-6 の「端の文字は viewBox から 10px 以上」を同じ測り方で見ると、この 4 分野で文字の枠が端から 10px 未満の図が 68 枚ある（多くは −3〜−7px で、枠は字の上下の余白を含むので見た目の隙間はもう少し広い）。verify-pages の 9 枚の指示の外なので直していない。一覧は `scratchpad/s10b/graph_bbox.out`（第 2 列が負の値のもの）。直すなら図の担当で一括に
5. **台帳**：agc002_d の summary（3 ページの行は台帳から作るので触っていない）、keyence2019_e は済み
6. **minimum-spanning-tree の frequency_evidence**：tools/frequency.py の付け直しに任せた（§17-7）
7. **tree/static-top-tree の trap.jp/post/2861**：noai を確かめる作業はメイン（decisions「出典」）。今のまま
8. **そのままにすると決まったもの**：two-sat の `acl`、string-basics の `cost-pitfalls`、manhattan-chebyshev の #motivation、extended-dijkstra の 9 問、tree-ratio-greedy の「トポロジカル順」、suffix-automaton の #build-your-own
9. **ほかの分野のページの出典の題名**（check_pages の警告。4 分野の側は実際の題名に直した）：dp/subset-sum（hamayan ABC222 E の［］→ [ ]）、dp/dp-state-design（drken ABC122 D →「(1Q, 水色, 400 点)」、merom686「ABC312 D」→「ABC312」）、comb/stirling-first（ikatakos ABC385 → ユニークビジョン…E,F,G問題メモ）、thinking/parity（ikatakos ABC454 → キーサイト…E,F,G問題メモ）、ds/union-find（kyo-pro「ABC288 C」→「ABC288C」）、ds/offline-queries は pyteyon の題名が実際どおり、dp/tree-dp（merom686「ABC447」は実際どおり）、comb/linearity-of-expectation（kmjp ABC149 F の略記）、comb/probability-symmetry（kmjp ABC268 G の略記）、comb/counting-mindset（ikatakos ABC460）、patterns/interval（ikatakos ABC457）、dp/dp-segment-tree・dp/lis（AC Library の「（document_ja）」）、library-checker-problems の他分野の題、ds/stack-techniques の drken ABC243 D は 2Q で正しい。ほかに 4 分野が関わらない警告が約 28 件

## メインへ

- **atcoder.jp を取得してしまった**：出典の題名を確かめるために `git diff` から URL を集めたとき、並行の直しで差分に入っていた問題の行の atcoder.jp の問題ページ 6 件（abc197_f・abc244_f・abc286_g・abc338_f・agc002_d・keyence2019_e）を除き忘れ、curl で `<title>` だけを取得した。結果は使っておらず、一時ファイルからも消した。以後の取得はドメインを付録 B のものに絞った
- ds の担当へ：ds/rollback-union-find L79「同じ説明は root-path-dfs#no-path-compression にもある」は、root-path-dfs 側を縮めたので「要点は…にもある」程度に弱めるとよい。L61・L81 の「（[オフライン動的連結性](#offline-dynamic-connectivity)の末尾）」は、その節が縮んで末尾に引き算の話がなくなったので、graph/offline-dynamic-connectivity#dfs-rollback（L98 の加算の段落）へ向けるとよい
- 一時置き場 `/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/ff4dc6ee-16d4-486c-b97a-49fefbe7b218/scratchpad/s10b/` は並行の担当と共有で、titles.py は別の担当のものに上書きされていた。この担当のファイルは graph_ で始まる名前と unify2.py
