# 工程10 2巡目：comb・patterns・guide・start の直し

decisions.md・style-guide §17 と、left-*.md・verify-*.md のうちこの 4 分野に当たる項目を直した。commit はしていない。atcoder.jp・codeforces.com は開いていない。gen_site.py は流していない。

検査（直した後）：`python3 tools/check_pages.py` エラー 0（警告 2：担当の外の出典の題名。下の「残したもの」）。`npx textlint` で 4 分野の全ページ：エラー 0。`python3 tools/check_snippets.py --changed`：コード片 6、期待と違う 0。`python3 tools/check_svg.py --page`（4 分野の 69 枚）：エラー 0（警告 24 は幅 400 超えだけ。下を参照）。

## 直したもの

1. **complexity を null に（§17-1）**：comb/twelvefold-way、guide/library-design・method-comparison・reverse-index-constraints、patterns の 10 ページ（bracket-sequence・divisors-and-multiples・grid・interval・kth-and-median・mex・operation-sequence・permutation・subsequence-and-substring・xor）。計 14 ページ。dp-speedup-overview・advanced-ds-catalog・graph-modeling は 1 巡目で null 済みなので、17 ページがそろった
2. **表記（§17-8）**：本文・summary・signs を 4 分野の全ページで grep した（生成ブロックと台帳から作る問題の行、aliases は除く）
   - 「0 始まり」「1 始まり」→ 0-indexed・1-indexed：comb/binomial-coefficient（L128・L134）・binomial-identities L284・counting-fix-order L212、patterns/kth-and-median L193・permutation L177・L185、guide/reverse-index-signs L73。後ろに和文が続くところは半角の空白を入れた
   - 「最下位ビット」→「最下位 bit」：comb/binomial-precompute L181、guide/cheatsheet L393（出典の説明の文）
   - 「上位ビット」→「上位 bit」：patterns/xor の節の題と sections の title（L27・L130）、L135 のリンクの文字（verify-pages メインへ 3）
   - コード片のコメント：snippets/binomial-coefficient/kth.cpp・snippets/permutation/rank.cpp の「0/1 始まり」、snippets/nim/nim.cpp の「最上位ビット」
   - 多重テストケース・歩道・平衡二分木・フェニック木は 4 分野の本文に残っていなかった（生成ブロックと glossary・term-index の説明の文は残した）
3. **「ダイクストラ」→「ダイクストラ法」**（left-graph）：comb/game-retrograde-analysis の節の題（L128）と sections の title・L200・L226 のリンクの文字（anchor `weighted` は変えていない）。guide/method-comparison の summary も直した。lists・index・roadmap の生成物は gen_site で追従する
4. **リンクの文字を相手の題名に**（left-tree）：comb/counting-bijection L126・comb/counting-labeled-graphs L283 の「ラベル付き木の数と Prüfer 列」→「ラベル付き木の数え上げ」。patterns/xor L154 の「拡張ダイクストラ」（別名）→ 題名「状態を頂点にする」
5. **related の追加**（left-tree、decisions で採用）：comb/minimax に `root-path-dfs`、comb/divisor-inclusion-exclusion に `kmp#count-periodic`
6. **閉区間の断り**（left-math）：guide/method-comparison L429 の区間篩の行に「$[L, R]$（閉区間）」
7. **how-to-use の古い文言**：start/how-to-use L245 の「（章の構成の表の『準備中』の列はどの分野も 0）」を消した（gen_site の直しで列が消えるため）。knowledge-map L59・reverse-index-signs L75 は 1 巡目で直っていた。docs/index.md の info は判断どおり残した
8. **図の端の余白（§17-6、verify-pages）**：ヘッドレスの Chrome で文字の枠と viewBox の端の距離を 4 分野の 69 枚で測り（一時置き場の edge.py）、5px 未満だった 12 枚を 10px 以上にした。上下は viewBox を伸ばし、左右は幅が 400 の図では幅を変えずに端の文字を内側へ寄せた（幅を広げると 328px で 9px 未満になるため）。背景の白い rect も合わせた。360px で撮って目で確かめた
   - viewBox を伸ばした：counting-labeled-graphs/bfs-layers（下）・component-of-1（右、幅 480→491）、nim/winning-move（下）、reflection-principle/reflection（下）、divisors-and-multiples/multiple-hops（上・右、幅 400→418。文字は 9px 以上のまま）、xor/column-parity（下）、notation/half-open（下）、library-design/workflow（下）
   - 文字を寄せた：grid/checkerboard（縦の矢印を x 22→36、「i（行）は下へ増える」を x 14→24）、contest-strategy/finish-times・reverse-index-constraints/max-n-per-class・atcoder-system/levels（左の見出しを x 8→10、右端の目盛りの数「100」「10¹⁸」「3200」を右寄せで x 390 に。上の余白も 5 足した）、library-design/workflow（下の注記を x 8→10）
9. **出典の題名をそろえた（§17-10）**：check_pages の新しい警告に出た URL のうち、4 分野のページにある 38 行（27 ページ）を、ほかのページで使っている題名か記事の題名にそろえた。4 分野だけで食い違うものは記事の題名に近い長い方を選んだ（algo-logic は記事の title「…| アルゴリズムロジック」を確かめた）。題名に入れていた問題名の補足（yosupo06/library-checker-problems の 2 行）は説明の文へ移した。qiita の bluebery1001 は URL のとおりの綴りに直した
10. **確かめただけのもの**：comb/expectation-tail-sum の abc411_e の練習の囲みと方針は 1 巡目のあとに入っている。comb/inclusion-exclusion の abc475_f は台帳の summary が書かれ、本文の囲みと方針も入っている（方針の 4 辺の包除と「+1」は問いと合う）。§17-3 で anchor を改める 6 ページへのリンクは 4 分野の本文にない（docs/index の生成物だけ）

## 残したもの

1. **出典の題名の警告 2 件（担当の外）**：ikatakos の ABC475 の記事は h1 が「AtCoder Beginner Contest 475 E,F,G問題メモ」（2026-10-22 に取得して確かめた）。comb/inclusion-exclusion はこの題名で正しく、**math/divisor-count-bound の「…475 G 問題メモ」を直す**。もう 1 件は library-checker-problems/tree/master/convolution（dp/monge と math/fft-ntt）で 4 分野にない
2. **幅 400 を超える図 24 枚**（check_svg の警告）：bell-number/stirling-table（586）・binomial-coefficient/pascal-and-paths（620）など。どれも 328px で文字 9px 以上で、§17-6 の必須は満たす。幅を 400 にそろえるのは描き直しになるので今回はしていない
3. **端の余白が 5〜10px の図 31 枚**：測った値は文字の行の枠（アセント・ディセントを含む）なので、字そのものはさらに内側にある。はみ出し・5px 未満だけを直した。§17-6 を厳密に当てるなら次に図を触るときに足す（一時置き場の /tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/ff4dc6ee-16d4-486c-b97a-49fefbe7b218/scratchpad/s10b/edge.py で測れる）
4. **生成物の中の古い語**：guide/problem-sets・roadmap・term-index・reverse-index-signs の生成ブロック、docs/lists・docs/index の「ダイクストラの要領」「上位ビット」「歩道」など。gen_site.py で追従する
5. **台帳から作る問題の行**：abc180_f の「パスかサイクル」（counting-mindset・counting-labeled-graphs・counting-dedup）は台帳の担当が直して fix_problems を流す
6. **frequency_evidence**（comb/binomial-precompute の abc458_e など）：tools/frequency.py の担当が付け直す
7. **guide/glossary の表の行**：作業中に「0-indexed・1-indexed」「上位 bit・最上位 bit・最下位 bit」の行が足されていた（共有の担当の作業と見て触っていない）。glossary L843「ウォークを『歩道』とは書かない」と term-index L56 の「ダイクストラのアルゴリズム」は語の説明なので残した

## メインへ

- 図の 12 枚は幅や位置を変えたので、ほかの分野の図の直しと一緒に目で確かめるとよい（PNG は一時置き場の s10b/png）
- 出典の題名は「長い方・記事の題名」に寄せた。ほかの担当が逆向きにそろえると食い違うので、check_pages の警告で最後に確かめる
