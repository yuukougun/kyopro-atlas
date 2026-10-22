# 工程10 2巡目 math の直しの記録

decisions.md・style-guide §17 と left-*.md・verify-*.md の math の項目を直した。直した数 9 項目（図 15 枚・出典の題名 31 か所を含む）、残した数 1（floor-sum の練習）。commit はしていない。gen_site.py は実行していない。

検査：`python3 tools/check_pages.py` エラー 0、`npx textlint docs/math/*.md`（index.md を除く 42 ページ）エラー 0、`python3 tools/check_svg.py --page <math の 34 フォルダ>` エラー 0（警告は幅 400 超えの 6 枚で、前からのもの）、`python3 tools/check_snippets.py --changed` 期待と違う 0。

## 直したもの

1. **§17-3 anchor**：linear-recurrence-fast の `## ACL の convolution を使った実装 {#implementation}` を `{#library}` に、sections の anchor も `library` に。本文のリンクは全ページで grep して 0 件（外からは生成物の docs/index/math.md L785 だけ。gen_site で追従）
2. **§17-8 表記**（math の全ページと snippets を grep）：
    - base-conversion：「1 始まりの 26 進」を「0 を使わない 26 進」に（summary・sections の title・要点・見出し・本文 L45・L81・L178・L183）。0-indexed・1-indexed は添字の意味なので当てはめず、桁に 0 を使わない記数法であることを書いた。L81 に「（各桁が 1 から始まる）」を足した。anchor `bijective-26` はそのまま。snippets/base-conversion/bijective26.cpp の 1 行目の注釈も同じに（core の外）
    - snippets/matrix-power/min-plus.cpp の注釈 2 か所・matpow.yaml の注釈の「歩道」を「ウォーク」に
    - ほかの語（多重テストケース・上位ビット・最上位ビット・最下位ビット・平衡二分木・フェニック木・0 始まり）は math の本文・front matter に 0 件
3. **prh「全て→すべて」**（並行して足された規則で、math の front matter が index.md の生成の行でエラーになっていた）：convolution-ntt の summary・signs 2、gcd-properties・hadamard-transform・xor-basis の signs、stern-brocot の summary（「全て1回ずつ」→「すべて 1 回ずつ」）
4. **left-comb**：convolution-ntt の related に `zeta-mobius-subset` を足した
5. **left-graph**：determinant L131 のリンクの文字「最小全域木の発展」を「特殊な最小全域木」に。指示の `#manhattan` は付けなかった（この文は部分集合ごとの全域木の数の話で、Manhattan MST の節とは関係しないため。ページへのリンクのまま）
6. **§17-6 図の端の余白**（verify-pages の「はみ出し」とその同類）：Chrome で文字の枠と viewBox の端の距離を測り、左右が 10 未満・上下が 7 未満（上下は字の枠に行間を含むので）の 15 枚の viewBox を広げ、白の背景の rect を新しい viewBox 全体に合わせた。360px で撮って重なり・切れがないことを見た
    - 右へ：digit-and-mod/suffix-pairs（「（空）」が −9 → 11）、gaussian-elimination/steps-1・steps-2（凡例 −2.7 → 11）、sieve-eratosthenes/grid100（0.8 → 11）、floor-quotient-enum/staircase
    - 左へ：fft-ntt/even-odd-split・online-convolution/cdq-order（幅 400 のまま viewBox を 3 ずらした。広げると 9px 未満の文字の警告が出るため）、integer-division/floor-ceil-negative、matrix-power/adjacency-power・fast-power、digit-and-mod/suffix-pairs
    - 下へ：exponent-mod/powers-mod-7-base3（あわせて、背景の rect が viewBox の下 10px を覆っていなかったのを直した）、miller-rabin/rho、stern-brocot/tree、xor-basis/insert・xor-walk
7. **§17-10 出典の題名**：同じ URL の題名がサイトの中で違うもののうち math にある 31 か所を、多数の書き方か記事の題名にそろえた（ikatakos 氏の ABC461 は記事の h1「AtCoder Beginner Contest 461 E,F,G問題メモ」を確かめた）。主なもの：ACL の document_ja/math.md は「AtCoder Library「Math」（document_ja）」、modint.md は「AtCoder Library「modint」（document_ja）」、convolution.md は「AtCoder Library「Convolution」（document_ja）」、document_ja のフォルダは「AtCoder「AC Library のドキュメント（document_ja）」」、library-checker-problems の根は「yosupo06「library-checker-problems」」、number_theory は「yosupo「Library Checker の問題（number_theory）」」、かんプリン氏は「かんプリン「競技プログラミング　典型問題メモ」」、drken 氏・Kazun 氏・ikatakos 氏・kmjp 氏・oraclesqlpuzzle・loop0919 氏・E869120 の記事は長い方の題名
8. **§17-4**：modint の `connections`・mod-pow の `building-block` はそのまま（next-steps を足さない）
9. **§17-1・§17-11**：math に guide・hub・pattern はなく（proof-patterns は thinking）、重なりの件も math にはないので、直すものなし

## 残したもの

- **floor-sum の練習の節**（decisions「練習の節がない…floor-sum」）：台帳は別の担当なので本文に足していない。候補として ABC193 E. Oversleeping（diff 1948、ap.py で確認。台帳には crt の practice として既にある）を見つけた。opt-cp.com/abc193e/ が「floor sum を二分探索の判定に 2 回使う」解き方を載せていると検索結果にあるが、check_noai が名前解決に失敗して noai を確かめられず、記事も読んでいない。ほかに drken 氏の floor_sum カテゴリに ABC329 F・ABC432 C が挙がるが中身は確かめていない。ABC436 G（Linear Inequation）は第三者の解説で BM 法の問題と分かり、候補から外した。台帳の担当が確かめて pages に `{id: floor-sum, role: practice}` を足せば、本文に囲みと方針を足す。見つからなければ §16-5 の 1 文を置く（例題に ABC443 G があるので「ABC で必須になる問題は確認できなかった」とは書きにくい。言い方はメインが決める）

## メインへの知らせ

- gen_site.py の作り直しで直るもの：docs/index/math.md L785 の `linear-recurrence-fast#implementation`、L517 の「1 始まりの 26 進」、docs/math/index.md・lists・llms.txt の base-conversion・stern-brocot・convolution-ntt の要約（「1 始まり」「全て」。今は docs/math/index.md が textlint のエラー 2 件）
- 台帳 data/problems.yaml L3237（abc171_c の approach）の「1 始まりの 26 進」を「0 を使わない 26 進」に（台帳の担当へ）
- 出典の題名は、ほかの分野の同じ URL（tree-dp の Series_205「EDPC P ~ S…（Qiita）」、cpp-macros-template-file・cheatsheet の ACL document_ja、dp・graph・comb の library-checker-problems の根、dp の kanpurin、segment-tree の ikatakos ABC461、comb/expectation-tail-sum と同じ drken 352 G、basics/binary-search 143 D は math と同じ）を、上の 7 の題名に合わせるとそろう。library-checker-problems の根は「yosupo06「library-checker-problems」」にした（GitHub のリポジトリ名）
- 消した・足した画像はない（15 枚は中身の変更だけ）
