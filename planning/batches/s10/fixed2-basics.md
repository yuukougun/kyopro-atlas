# 工程10 2巡目 直し：basics・thinking・dp・misc（直したものと残したもの）

対象：decisions.md・style-guide §17・left-*.md・verify-*.md のうち、basics・thinking・dp・misc のページ・図に要る直し。commit はしていない。gen_site.py は流していない。

**直した数 17 件（図 69 枚を含む）・残した数 4 件**（どれも担当の外のページか、メインの作り直しが要るもの）。

## 直したもの

1. **anchor の改め（§17-3）**：dp/cht・dp/dynamic-dp・dp/monge の `## ライブラリでの検証 {#verify}` と sections の `anchor: verify` を `library` にした。本文のリンクを全ページで grep し、`docs/geometry/advanced-geometry.md` の `../dp/cht.md#verify` を `#library` に張り替えた（担当の外のページだが、指示どおりリンクの張り替えだけ）。ほかに `#verify` を指す本文のリンクはない
2. **complexity null（§17-1）**：この分野の hub・guide・pattern は dp/dp-speedup-overview だけで、すでに null。直しは要らなかった
3. **表記（§17-8）**：4 分野の本文・summary・signs を grep した。直したのは misc/bitset-speedup のリンクの文字「popcount・最下位ビット」→「popcount・最下位 bit」（相手の節の題と同じ）と、bitwise-independence の summary「上の bit から決め」→「上位 bit から決め」。aliases と、aliases を写した「別名：」の行（bit-operations・bitwise-independence）は検索語として残した。dp/bit-dp の abc338_f の行の「歩道」は台帳から作る行なので触っていない（台帳の担当が直して、今は「ウォーク」になっている）。「0 始まり」「1 始まり」「多重テストケース」「平衡二分木」「フェニック木」はこの分野に残っていない
4. **front matter の提案の反映（decisions の「個々の件」）**：
    - basics/divide-and-conquer：signs の「区間 [L, R]」→「閉区間 [L, R]」、related に `sparse-table` を足した（sparse-table 側にはすでに divide-and-conquer がある）
    - dp/interval-dp-advanced：related に `tree-construction#from-order` を足し、#dfs-order-trees の「応用の型」に「区間にならない訪問順」の 1 項目を足して本文からもリンクした
    - misc/bitset-speedup：related に `degree-sqrt#triangles` を足した（本文はすでに 2 か所でリンクしている）
    - dp/subset-enumeration-dp：related に `chromatic-number` を足した（本文はすでに 2 か所でリンクしている）
5. **リンクの文字を相手の題名に（left-comb・left-graph）**：dp/subset-enumeration-dp「ラベル付きグラフの数え上げ」→「連結なグラフの数え上げ」、dp/insertion-dp「包除原理の DP」→「包除 DP」、dp/lis「Dilworth の定理とパス被覆」→「DAG の最小パス被覆」
6. **abc467_f → basics/exchange-argument の力試し**：ikatakos 氏の ABC467 の記録（付録 B で確かめ済みのドメイン）で問いと解き方を確かめ、`tools/ap.py show` で題名と diff 2052 を確かめて、力試しの囲みと方針を足した。方針は「隣接交換で $B$ の降順が最適 → 答えは $\max_i (A_1 + \dots + A_i + B_i)$ → $B$ を座標圧縮したセグメント木に（$A$ の和, 前の和 + $B$ の最大）を持つ」。隣接交換の不等式は自分で確かめた。参考に記事を足した
7. **abc458_g → dp/slope-trick の力試し**：`## 力試し {#challenge}` を作り、ikatakos 氏の ABC458 の記録で解き方（人数の二分探索、$\mathrm{dp}[j]$ が上に凸な折れ線、A は定数・B は傾きの一律の加算・C は傾きの下限をそろえる、傾きのスタックで $O(N)$ 判定）を確かめて方針を書いた。参考に記事を足した（題名は monge と同じ記事の題名にそろえた）
8. **dp/monge の abc458_g の行**（verify-shared の注意 2）：要約を台帳の summary に合わせて書き直し（園児・メダル・$A_i, B_i, C_i$）、方針から slope-trick#challenge へリンクした
9. **メモリの制限の単位**（audit-facts の「1024 MiB」の同じ型）：dp/dp-grid・misc/bitset-speedup の「制限 1024 MB」を「1024 MiB」に。dp/knapsack-undo の「$NW = 6.4 \times 10^7$ で 1024MB に達する」は、$16 \times 6.4 \times 10^7 = 1.024 \times 10^9$ バイト ≈ 977 MiB なので「約 $1.0 \times 10^9$ バイト（約 980 MiB）になり、よくある制限の 1024 MiB にほぼ達する」に直した
10. **出典の題名のそろえ（§17-10）**：この分野のページにある参考のうち、同じ URL でほかのページと題名が違う行（41 の URL）を、記事の実際の題名（og:title・title を取得して確かめた）にそろえた。ほかの分野で多数派の書き方があるもの（ACL の document_ja の 3 件）は多数派にそろえた。題名に入っていた説明（Library Checker の問題名）は「：」の後ろの説明へ移した（cht・monge）
11. **図の端の余白（§17-6・decisions の「余白を 10px 足す」）**：この分野の SVG 107 枚の文字の枠をヘッドレスの Chrome で測り、viewBox の端から 10px 未満の文字がある 69 枚の viewBox と width・height を足りない分だけ広げた（中身は `<g transform="translate(…)">` でずらし、全面の背景の rect は新しい大きさに広げた）。測り直して 69 枚すべてで端から 10px 以上。verify-pages の 9 枚のうちこの分野のものも含む（はみ出していたのは coordinate-compression/intervals −3px・cht/envelope −2px・monge/monotone-minima 0px など）。`python3 tools/render_svg.py --width 360` で 6 枚（cht/envelope・monge/monotone-minima・coordinate-compression/intervals・slope-trick/breakpoints・knapsack-undo/add-remove・randomized/failure-probability）を撮って見た。図の中身は変えていない。dp-order/six-orders も上と左に 1〜2px 足しただけで並びは今のまま

## 残したもの（担当の外）

1. **docs/index/dp.md の `dynamic-dp#verify`・`cht#verify`・`monge#verify` の 3 行**：生成物なので gen_site.py の作り直しで `#library` に追従する（メイン）
2. **出典の題名で、ほかの分野のページだけが違うもの**（`python3 tools/check_pages.py -v` の「同じ URL の出典の題名が違う」）：この分野の側は記事の題名にそろえたので、相手のページを合わせるとよい。comb/grundy-number（drken ABC206 F に「(黄色, 600 点)」がない）、guide/problem-sets（E869120「…」（GitHub）・drken の EDPC 入門の「A〜E」（Qiita））、guide/cheatsheet（ACL の document_ja）、math/fft-ntt（library-checker-problems/convolution）、patterns/interval（ABC457 の題名の末尾）、comb/counting-mindset（ABC460 の ikatakos・comet725）、comb/probability-symmetry（ABC473）、guide/reverse-index-constraints（kanpurin）、comb/young-tableaux・continuous-probability ほか（library-checker-problems の題名に問題名が入っている）、math/matrix-power（ikatakos ABC458 の題名が「AtCoder Beginner Contest 458」）
3. **width の目安の警告**（check_svg の「幅が 400 程度を超える」）：この分野に 38 枚残る。文字は 360px で 9px 以上で、§17-6 の決まりは満たすので触っていない
4. **台帳の abc467_f の summary**：本文の行の要約は記事で確かめた問いで書いた。台帳の summary（台帳の担当が書く）と言い回しが違っても §17-9 の範囲だが、事実が食い違うときは台帳を直す

## 検査

- `python3 tools/check_pages.py`：エラー 0（警告は §17-10 の題名の 43 件で、この分野だけで閉じるものは 0）
- `npx textlint docs/basics/*.md docs/thinking/*.md docs/dp/*.md docs/misc/*.md`：エラー 0。docs/geometry/advanced-geometry.md もエラー 0
- `python3 tools/check_svg.py`：エラー 0（警告 120 件はすべて幅の目安で、直す前と同じ数）
- `python3 tools/fix_problems.py --check`：直すべき行 0・台帳にあって本文にない 0
- コード片は変えていない（`python3 tools/check_snippets.py --changed` は他の担当の変更 6 件を試し、期待と違う 0）
