# resources の報告（バッチ cross-links）

- 担当の Issue：#71（発展の概要の「学ぶための資料」の各行にリンクを付ける）のうち、docs/dp/ 以外の type: overview の 46 ページ。docs/dp/ の 5 ページ（cht・alien-dp・dynamic-dp・monge・slope-trick）は担当の外
- 作業ツリー：/home/yuuki/projects/kyopro2/kyopro-atlas-wt/cross-links（ブランチ fix/cross-links）。git は読むだけで、commit などはしていない
- 直したファイル：下の表の 46 ページ。直したのは各ページの `## 学ぶための資料 {#resources}` の節と、front matter の `updated` だけである
- front matter：46 ページすべての `updated` を 2026-10-22 → 2026-10-29 にした。stage ほかは変えていない
- 参考の節・生成物・共有のファイル（手引き・用語集・prh.yml・台帳など）は変えていない。`tools/gen_site.py` は `--check`（`--diff`）だけを流した
- Web は開いていない（atcoder.jp・codeforces.com を含め、取得は 0 回）。題名と URL は、各ページの参考の節の行から写した。新しい資料・URL は足していない

## #71 学ぶための資料の各行のリンク（担当の 46 ページは完了）

### 書き方

- 各行を、参考の節の同じ資料の行と同じリンク `[著者「題名」](URL)` で始め、「：」の後にその資料から何が学べるかを書く形にした。リンクの文字も URL も、参考の行から一字一句そのまま写した（§11 の参考の行の形と同じ。§17-10）
  - この形にした理由：check_pages の §17-10 の検査（「同じ URL の出典の題名が違う」）は、参考と学ぶための資料の節で「- [題名](URL)」と始まる行の最初のリンクを全ページで集めて比べる。行をリンクで始めると、資料の行の題名もこの検査に入り、参考と食い違えば警告になる
  - 元の説明の文は残した。名前を言い換えていた部分（「けんちょん（drken）氏の yukicoder 399 の記事」「Luzhiled's Library（ei1333 氏）の HL 分解」など）だけを参考の題名のリンクに置き換え、主語がリンクに移った文は「：」の後の述語の形に直した。例：「正しさと計算量の確認には cp-algorithms の Heavy-light decomposition の記事がある（英語）」→「[cp-algorithms「Heavy-light decomposition」](https://cp-algorithms.com/graph/hld.html)（英語）：正しさと計算量の確認に使える」
  - 元の行にあった言語・種類の注記（英語）（中国語）（日本語）（Qiita）（Zenn）（Scrapbox）（traP ブログ）（HackMD のメモ…）（英語の論文）（ライブラリのドキュメント）は、リンクの直後のかっこに残した。リンクの文字に「（英語版 Wikipedia）」などがある行には（英語）を重ねていない
  - 資料の一部の節を指す行は、リンクの後に「の G 問題の節」「の Parallel Binary Search の節」「の節「应用：线段树优化建图」」のように書いた（URL は参考のままで、anchor を足していない）
  - 1 行に資料が 2 つ以上ある 9 行は、それぞれをリンクにして「と」（2 つ）・「・」（3 つ）でつないだ。リンクの文字が半角で始まるときは「と」の後に空白を入れ（§7。サイトの多数の書き方は 720 対 78）、「・」の後には入れない（サイトの書き方は 78 対 0）。9 行：continuous-probability L137・segment-tree-beats L135・spanning-tree-advanced L151・two-sat L146・miller-rabin L160・online-convolution L123・suffix-automaton L168・L170・static-top-tree L146
- 置き換えは、資料の節の新しい本文に `{{u:URL の一部}}` と書き、スクリプトで同じページの参考の節のただ 1 つのリンクに置き換えて行った（題名と URL を手で写していない）。スクリプトは作業用フォルダの /tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/7a638398-7759-4637-95c7-6739e8d52414/scratchpad/fix/cross-links/resources/new_sections.py（新しい本文）と /tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/7a638398-7759-4637-95c7-6739e8d52414/scratchpad/fix/cross-links/resources/apply.py（置き換え）

### 直したページと行

表の「資料」は直した後の節の範囲（見出しから次の見出しの前まで）、「行」は箇条書きの行数、「リンク」は外部リンクの数。

| ページ | updated | 資料 | 行 | リンク |
| --- | --- | --- | --- | --- |
| docs/comb/binomial-prefix-sum.md | L27 | L119〜124 | 3 | 2 |
| docs/comb/burnside-lemma.md | L30 | L168〜173 | 3 | 3 |
| docs/comb/continuous-probability.md | L28 | L134〜139 | 3 | 4 |
| docs/comb/generating-function-counting.md | L29 | L162〜167 | 3 | 3 |
| docs/comb/lgv-lemma.md | L28 | L156〜161 | 3 | 3 |
| docs/comb/partizan-games.md | L28 | L138〜143 | 3 | 3 |
| docs/comb/stirling-first.md | L30 | L166〜171 | 3 | 2 |
| docs/comb/young-tableaux.md | L26 | L128〜133 | 3 | 3 |
| docs/ds/balanced-bst.md | L29 | L164〜169 | 3 | 3 |
| docs/ds/cdq-divide-and-conquer.md | L28 | L123〜127 | 2 | 2 |
| docs/ds/parallel-binary-search.md | L29 | L134〜138 | 2 | 2 |
| docs/ds/partially-persistent-union-find.md | L29 | L120〜124 | 2 | 2 |
| docs/ds/rollback-union-find.md | L29 | L107〜111 | 2 | 2 |
| docs/ds/segment-tree-beats.md | L29 | L133〜138 | 3 | 4 |
| docs/ds/wavelet-matrix.md | L27 | L119〜124 | 3 | 3 |
| docs/geometry/advanced-geometry.md | L34 | L166〜174 | 6 | 6 |
| docs/graph/chromatic-number.md | L28 | L147〜152 | 3 | 3 |
| docs/graph/dilworth-path-cover.md | L28 | L128〜133 | 3 | 3 |
| docs/graph/flow-lower-bounds.md | L26 | L94〜99 | 3 | 3 |
| docs/graph/general-matching.md | L29 | L131〜136 | 3 | 3 |
| docs/graph/k-shortest-paths.md | L26 | L116〜120 | 2 | 2 |
| docs/graph/matrix-tree-theorem.md | L29 | L156〜161 | 3 | 3 |
| docs/graph/modular-shortest-path.md | L26 | L101〜106 | 3 | 3 |
| docs/graph/offline-dynamic-connectivity.md | L26 | L120〜124 | 2 | 1 |
| docs/graph/segment-tree-graph.md | L25 | L88〜92 | 2 | 2 |
| docs/graph/spanning-tree-advanced.md | L30 | L145〜152 | 5 | 7 |
| docs/graph/steiner-tree.md | L28 | L131〜136 | 3 | 3 |
| docs/graph/two-sat.md | L31 | L142〜147 | 3 | 4 |
| docs/math/determinant.md | L28 | L151〜156 | 3 | 3 |
| docs/math/fft-ntt.md | L29 | L142〜147 | 3 | 3 |
| docs/math/fps-basics.md | L29 | L130〜135 | 3 | 3 |
| docs/math/hadamard-transform.md | L29 | L127〜132 | 3 | 3 |
| docs/math/lagrange-interpolation.md | L31 | L142〜147 | 3 | 3 |
| docs/math/linear-recurrence-fast.md | L31 | L164〜169 | 3 | 3 |
| docs/math/miller-rabin.md | L30 | L157〜162 | 3 | 4 |
| docs/math/multiplicative-function.md | L28 | L170〜173 | 1 | 1 |
| docs/math/online-convolution.md | L29 | L119〜124 | 3 | 4 |
| docs/math/stern-brocot.md | L28 | L136〜140 | 2 | 2 |
| docs/string/suffix-automaton.md | L35 | L165〜171 | 4 | 6 |
| docs/tree/auxiliary-tree.md | L29 | L123〜130 | 3 | 3 |
| docs/tree/dynamic-tree.md | L28 | L152〜158 | 4 | 4 |
| docs/tree/hld.md | L30 | L177〜182 | 3 | 3 |
| docs/tree/merge-process-tree.md | L29 | L138〜143 | 3 | 3 |
| docs/tree/static-top-tree.md | L26 | L140〜147 | 5 | 5 |
| docs/tree/tree-isomorphism.md | L28 | L129〜134 | 3 | 3 |
| docs/tree/tree-ratio-greedy.md | L27 | L129〜134 | 3 | 3 |
| 計 46 ページ | | | 137 | 143 |

### ページごとに決めた点

1. **もとからリンクがあった 3 ページ（fft-ntt・multiplicative-function・stern-brocot）**：「51_24_11_ 氏の記事[「題名」](URL)」「cp-algorithms の解説[「題名」](URL)」「Nyaan 氏のライブラリ[「題名」](URL)」の形を、ほかの 43 ページと同じ「[51_24_11_「題名」](URL)」（参考の行と同じリンク）に直した。題名と URL は変わらない。s10 の fixed2-citations は、この形の違いを「そろえなくてよい」としていたが、46 ページの形をそろえるために直した（戻すなら 6 行。判断してほしい点 1）
2. **geometry/advanced-geometry**：「cp-algorithms（英語）：ミンコフスキー和・最近点対・半平面交差・ドロネー三角形分割とボロノイ図・交わる線分の組の探索の各記事が、手順と計算量をまとめている。…」の 1 行を、記事ごとの 5 行に分けた（題名の長いリンクを 5 つ 1 行に並べると読めないため）。各行の説明は元の行の「手順と計算量をまとめている」で、半平面交差の行に「有界にするための正方形と、平行な半平面の扱いに詳しい」を置いた。資料の行は 2 → 6
3. **tree/auxiliary-tree**：節の頭の「次の 3 つがよい（URL は参考の節にある）。」から「（URL は参考の節にある）」を消した（各行にリンクが付いたので）
4. **math/hadamard-transform・math/linear-recurrence-fast**：資料の節の `<!-- textlint-disable -->`〜`<!-- textlint-enable -->`（hadamard の 2 行を囲む）と `<!-- textlint-disable ja-space-between-half-and-full-width -->`〜（linear-recurrence-fast の 3 行を囲む）を外した。題名を地の文に書いていたための無効化で、題名はリンクの文字に移った。textlint の ja-space-between-half-and-full-width と prh はリンクの文字を見ないことを試験のファイルで確かめ、外した後も 2 ページのエラーは 0。ページのほかの場所（別名の行・参考）の無効化はそのまま
5. **ds/balanced-bst・tree/dynamic-tree**：参考の URL が Luzhiled's Library のトップ（https://ei1333.github.io/library/）なので、リンクの後に、参考の行にある場所（structure/bbst・structure/dynamic-tree）を文字で添えた
6. **comb/partizan-games L142**：書籍の文と Wikipedia の文が 1 行にあるので、行を分けず、後ろの文の「Wikipedia の「超現実数」の項目」を「[Wikipedia「超現実数」](…)の項目」にした。リンクが行の途中にあるので、check_pages の §17-10 の検査には入らない（題名が参考と同じことは下の verify.py で確かめた）
7. **comb/lgv-lemma・comb/young-tableaux**：リンクの文字は参考の題名（Wikipedia の記事名のエンダッシュ「Lindström–Gessel–Viennot」「Robinson–Schensted」）のままにした。地の文なら prh が ASCII のハイフンに直すが、リンクの文字は prh が見ない（§16-15 の「題名は原文のまま」）
8. **ds/partially-persistent-union-find**：s10 で「UnionFindTree」が prh のエラーになるので題名を引かずに言い換えた行である。リンクの文字にすると prh は見ないので、参考と同じ題名「noshi91「UnionFindTree に関する知見の諸々」」のリンクにした（エラー 0）
9. **tree/static-top-tree L144**：noya2 の記事（https://trap.jp/post/2861/）も、参考にある URL なのでリンクにした。trap.jp は付録 B で「トップページは noai の指定なし、記事は取得できなかった」で、メインの判断待ちの 3 ページの 1 つである（判断してほしい点 3）

### リンクを付けなかった資料（参考の節に URL がない）

| ページ・行 | 資料 | 理由 |
| --- | --- | --- |
| tree/static-top-tree L142 | ABC351 G の公式解説 | atcoder.jp の解説ページ。参考に URL がなく、行の本文も「このサイトからはリンクしない」と書いている（§11）。この行だけはリンクが 1 つもない（判断してほしい点 2） |
| comb/partizan-games L142 | Albert・Nowakowski・Wolfe の教科書『Lessons in Play: An Introduction to Combinatorial Game Theory』 | 書籍。参考の節にもない。同じ行の Wikipedia「超現実数」にはリンクを付けた |

外部リンクを足さず、もとのサイトの中のリンクのままにした行（どれもリンクはある）：

- comb/binomial-prefix-sum L123：Mo's algorithm の 2 つの接頭辞の節（../ds/mo-algorithm.md#two-prefixes）
- comb/stirling-first L170：「Library Checker の 3 問（[練習問題の節](#practice)の一覧）」。3 問の judge.yosupo.jp へのリンクは練習問題の節にある。参考の「yosupo「Library Checker の問題（enumerative_combinatorics）」」（問題の定義の GitHub）は、この行の資料（問題そのもの）とは別のものと考えて足していない
- graph/offline-dynamic-connectivity L123：ロールバックできる Union-Find のページ（../ds/rollback-union-find.md）

### 確かめたこと（どれも書き換えない検査）

- **verify.py**（/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/7a638398-7759-4637-95c7-6739e8d52414/scratchpad/fix/cross-links/resources/verify.py）：46 ページについて
  - HEAD との差分が、資料の節の中と front matter の `updated` の行だけにある。参考の節は HEAD と同じ
  - 資料の節の外部リンク 143 個のすべてが、同じページの参考の節に同じ「[題名](URL)」としてある（題名も URL も一致）。新しい URL はない
  - atcoder.jp・codeforces.com の URL はない
  - 参考の行で「学ぶための資料」と添えた URL は、どれも資料の節からリンクされている
  - 箇条書き 137 行のうち、リンクのない行は static-top-tree L142 の 1 行だけ
- **check_pages**：`--page`（46 ページ）でエラー 0・警告 0。全ページでもエラー 0・警告 0（§17-10 の「同じ URL の出典の題名が違う」も 0。資料の行の最初のリンクがこの検査に入るようになった後でも 0）
- **textlint**（46 ページ）：エラー 0。警告は 474 → 483。資料の節の外の警告は変わらない（459 → 459）。資料の節の中は 15 → 24 で、どれも題名をリンクの文字に入れたことによる警告（§14-25 の「リンクの題名の誤検出は、警告なら残してよい」により残した）
  - 文の長さ（sentence-length）が新しく出た行：binomial-prefix-sum L121・continuous-probability L137・k-shortest-paths L118・spanning-tree-advanced L151・steiner-tree L133・linear-recurrence-fast L167・miller-rabin L160・tree-ratio-greedy L133。もとから警告のあった 9 行（young-tableaux・cdq-divide-and-conquer・rollback-union-find・wavelet-matrix・general-matching・fft-ntt・stern-brocot・suffix-automaton・auxiliary-tree）は文字数が変わっただけで、two-sat L145 の警告は消えた
  - k-shortest-paths L118 の ja-no-successive-word 2 件：hotman78 の題名「…！？…！！！…」による（参考の L139 にも同じ警告がある）
- **作業用フォルダへのビルド**（`uv run mkdocs build -q -d …/resources/site`）：成功。46 ページの HTML の資料の節で、li 137 個にリンクの崩れ（`](` や `[…「` の名残）がないことを確かめた。入れ子の角かっこの題名（maspy「[Library Checker] Point Set Tree Path Composite Sum」・Heartlessly「题解 P2371 【[国家集训队]墨墨的等式】」・issue #1263「[問題案] 01 on Tree」）、題名の中の数式（Nyaan「$\sum_{i}a^i f(i)$」）、かっこを含む URL（Independent_set_(graph_theory)）も正しいリンクになる（/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/7a638398-7759-4637-95c7-6739e8d52414/scratchpad/fix/cross-links/resources/scripts/check_html.py）
- **gen_site.py --check --diff**：変わるのは docs/llms.txt・overrides/assets/data/graph.json・docs/start/how-to-use.md の版のハッシュだけ（並行して直しているほかの担当の分も含む）。メインが作り直す
- 外部リンクの検査（links.yml の lychee）は、URL が増えていないので対象は変わらない

## 提案（メインに頼む共有ファイルの変更）

1. **手引き §16-1 に足す文の案**（「参考の各行に…使わない」の後）：

    > 資料の各行にもリンクを付ける。行は参考の節の同じ資料と同じリンク `[著者「題名」](URL)` で始め（題名と URL は参考の行と一字一句同じにする。§17-10）、「：」の後に何が学べるかを書く。言語や種類は（英語）（中国語）（Qiita）のようにリンクの直後に添える。1 行に資料が 2 つ以上あるときは、それぞれをリンクにして「と」「・」でつなぐ。URL のない資料（書籍・atcoder.jp の解説）はリンクを付けずに書き、サイトの中のページ・節は相対リンクで指す。資料の節に資料を足すときは、参考の節にも同じリンクの行を足す

2. **（道具。急がない）check_pages の §17-10 の検査を広げる案**：今は行の最初のリンクだけを見る（progress.md の残りにある「行の 2 つ目以降のリンク」の案と同じ）。資料の節では、2 つ以上のリンクがある上の 9 行と、partizan-games L142 の行の途中のリンクが検査に入っていない。あわせて「資料の節の外部リンクの URL が同じページの参考の節にない」「資料の節にリンクのない行がある」（例外は書籍と atcoder.jp の解説）を警告にすると、§16-1 の決まりを保てる。今回の verify.py が同じことをしている

## 判断してほしい点

1. **行の形**：リンクの文字を参考と同じ「著者「題名」」にし、行をリンクで始めた（check_pages の §17-10 の検査に入るため）。fft-ntt などのもとの形（著者をリンクの外に書く「X 氏の記事[「題名」](URL)」）がよければ、46 ページを機械的に戻せる。docs/dp/ の 5 ページの担当も、作業ツリーの今の差分を見ると同じ「- [著者「題名」](URL)：」の形で直している。違いは 2 点：言語の注記を説明の頭（「：英語の解説。」）に書いていることと、cht・dynamic-dp で「](URL) と [」とリンクの後に空白を入れていること（「」」と「と」の間の空白は §7 では入れない）。§16-1 でどちらかに決めるとよい
2. **#71 の完了の条件（どの行にもリンクがある）**：static-top-tree L142 の ABC351 G の公式解説の行は、atcoder.jp なのでリンクを付けていない。この行を条件の例外にするか、「ABC351 G（[例題](#abc351_g)）の公式解説は…」のようにページの中の例題の小見出し（`### ABC351 G. Hash on Tree {#abc351_g}`）へのリンクを足すか
3. **trap.jp**：static-top-tree の資料の節に、参考と同じ noya2 の記事（https://trap.jp/post/2861/）へのリンクが 1 つ増えた。付録 B の trap.jp の扱い（記事の noai を確かめられていない）が決まったら、参考の行と一緒に扱う

## 使用量の目安

- 道具の呼び出し 約 50 回（読む・検査・スクリプト）、Web の取得 0 回
