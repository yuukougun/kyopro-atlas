# 工程10 洗い出し：事実と数値の一貫性

- 観点：計算量の目安・型の範囲・AtCoder の環境・ACL の関数・記法・用語の表記（付録 A）・frequency と recent-abc の一致・summary と complexity と本文の一致
- 調べ方：front matter の読み込みと各種の照合はスクリプト（/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/ff4dc6ee-16d4-486c-b97a-49fefbe7b218/scratchpad/s10/ の `fm.py`・`freq.py`・`freq2.py`・`freq3.py`・`terms.py`・`terms2.py`・`notation.py`・`cx.py`・`sm.py`・`acl.py`・`facts.py`）で全ページを調べ、当たった行を読んで判断した。docs/index・docs/lists（生成物）は対象外。`1 << 31` の警告は g++-15 で試した
- 照合して食い違いがなかったもの（直す必要なし）：1 秒あたりの回数の目安（complexity-estimation・cheatsheet・reverse-index-constraints・各ページとも「1 秒に $10^8$ 回」を基準にそろう）、制約の表の演算回数と図の上限の値（すべて計算し直して一致）、型の上限（`int`・`long long`・`unsigned long long`・`__int128`・`double` の $2^{53}$。16 ページで同じ値）、数の目安（階乗・ベル数・カタラン数・分割数・$\pi(N)$・約数の個数の最大・互除法の回数・素数の差の最大・$2^{-1} \bmod 998244353$）、ACL の計算量の表（cheatsheet#acl を document_ja と照合）、ACL の関数名と引数・返り値（`dsu::merge` の返り値と同じ大きさのときの残る側、`segtree::get` と `all_prod` が $O(1)$、`lazy_segtree::get` が $O(\log N)$、`floor_sum` の要件、`crt` の返り値、`lcp_array` の長さ、`suffix_array` の多重定義の計算量、`modint::val()` が `int`）、AtCoder の環境（GCC 15.2.0・`-std=gnu++23`・ACL v1.6・Clang 21.1.0・IOI-Style の GCC 14.2.0 はどのページも同じ）、front matter の complexity と要点の計算量（73 ページで表現が違うが、内容の食い違いはなかった）、frequency の値そのもの（A・B・C の付け方の規則に照らすと全ページが合う）、front matter に KaTeX がないこと
- 見つけた数：56 行（同じ型の箇所は 1 行にまとめた。うち内容の誤り・食い違い 12、表記・記法の揺れ 36、shared の提案 8）

## basics

- docs/basics/complexity-estimation.md ・ L60（制約の表の 2 行目）・ $3^N$ の上限を「$N \le 15$ 程度まで」と書くが、cheatsheet L49・L147 と reverse-index-constraints L89・L441 は「15〜16」「16 程度」・ $3^{16} \approx 4.3 \times 10^7$ で 1 秒の目安（$10^8$）に収まり、reverse-index-constraints の図も上限を 16 とする・「$3^N$ は $N \le 15$〜$16$ 程度まで」にそろえ、演算回数の列に $3^{16} \approx 4.3 \times 10^7$ を足す
- docs/basics/bit-operations.md ・ L156 ・「（C++20 以降は値が決まっているので、警告も出ない）」は、C++17 以前では警告が出るように読める。C++14・C++17 の扱い（処理系定義）も書いていない・ g++-15 の `-O2 -Wall -Wextra` で `long long b = 1 << 31;` を試すと、`-std=gnu++14`・`gnu++17`・`gnu++20`・`gnu++23` のどれも警告は出ず、値は $-2147483648$ だった。style-guide §5（cpp）は「C++20 から規格で値が決まった。C++14・C++17 では処理系定義で、GCC では同じ値になる」と書くよう決めている・かっこ内を「C++20 から規格で値が決まった。C++14・C++17 では処理系定義で、GCC では同じ値になる。どの版でも警告は出ない」に直す
- docs/basics/kth-value.md ・ L119・L173 ・「0 始まり」「1 始まり」を使う（付録 A の正規形は 0-indexed・1-indexed）・付録 A「全体」の語・順位の数え方を言う箇所なら「0 番目から数える」など言い換えてもよいが、添字の意味なら 0-indexed にそろえる（同じ型は comb/binomial-coefficient L128・L134、comb/binomial-identities L284、comb/counting-fix-order L212、ds/kth-element L72・L136、ds/wavelet-matrix L48・L138・L139、ds/merge-sort-tree L134、ds/persistent-data-structures L165、tree/tree-traversal L78、tree/complete-binary-tree L152、graph/two-sat L140、graph/graph-basics L184、patterns/kth-and-median L193、patterns/permutation L177・L185、math/base-conversion L13・L25・L33・L79・L81・L178・L183、cpp/acl-reading L13・L18・L38・L51・L56、cpp/cpp-reverse-index L261、guide/reverse-index-signs L73。どこまでを揺れとみなすかはメインが決める）
- docs/basics/bitwise-independence.md ・ L14（summary）ほか L28・L42・L140・L170・L209・L254・L263 ・「上位ビット」と書く（付録 A と §14-22 の正規形は「上位 bit」）・付録 A「基本」の「上位 bit」。同じページの L13 の summary は「上の bit」と書いている・本文を「上位 bit」「最上位 bit」にそろえる。summary の変更は front matter なので提案として扱う
- docs/basics/bit-operations.md ・ L26・L110 ・「上位ビット」「最下位ビット」・同上・「上位 bit」「最下位 bit」に直す
- docs/basics/difference-sequence.md ・ L161 ・「フェニック木」と書く（付録 A は「BIT（Fenwick Tree）」）・付録 A「データ構造」・「BIT」に直す
- docs/basics/divide-and-conquer.md ・ L38 ・ 閉区間 $[L, R]$ を「閉区間」と言わずに使う（ページに閉区間の断りがない）・ style-guide §6「閉区間は『閉区間 $[l, r]$』と明記する」・「閉区間 $[L, R]$」か半開区間に直す
- docs/basics/median-absolute.md ・ L187 ・「slope trick」と小文字で書く（題名は Slope Trick）・付録 A「DP」の「Slope Trick」・「Slope Trick」に直す

## thinking

- docs/thinking/parity.md ・ L137 ・「歩道」と書く・付録 A「ウォーク（歩道は使わない）」、§14-22、glossary L843・「ウォーク」に直す
- docs/thinking/symmetry-pigeonhole-casework.md ・ L99 ・ 閉区間 $[L, R]$ の断りがない（式 $R - L + 1$ から閉区間と分かるが明記なし）・ §6・「閉区間 $[L, R]$」と書く。同じ行の型の言及「4-サイクル」（L109）は graph/degree-sqrt の節題に合わせて直す（下の graph を参照）

## dp

- docs/dp/bit-dp.md ・ L157・L158 ・「歩道」・付録 A・「ウォーク」に直す
- docs/dp/bit-dp.md ・ L146（見出しと sections の title）・「ワーシャルフロイド」と「法」を落とす・付録 A「ワーシャルフロイド法」・見出しと sections の title を同時に「ワーシャルフロイド法」に直す（anchor は変えない）
- docs/dp/digit-dp.md ・ L206 ／ docs/dp/digit-dp-advanced.md ・ L101 ・ 閉区間 $[L, R]$ の断りがない（どちらも「$L$ 以上 $R$ 以下」と添えるか文脈で分かるが、「閉区間」の語がページにない）・ §6・「閉区間 $[L, R]$」と書く

## misc

- docs/misc/interactive.md ・ L159・L260 ・ 閉区間 $[L, R]$・$[l, r]$ の断りがない・ §6・「閉区間」と明記する

## graph

- docs/graph/euler-path.md ・ L13（summary）・ summary は「Hierholzer 法で O(M) で作れる」、要点の計算量（L39 付近）と complexity は $O(N + M)$・要点の囲みと summary を食い違わせない（§2.2）。隣接リストを頂点ごとに読むので $N$ の項が要る・ summary を「O(N + M)」にする提案（front matter なのでメインが反映）
- docs/graph/steiner-tree.md ・ L13（summary）・ summary は「O(3^K N + 2^K M log N)」、要点の計算量は $O(3^K N + 2^K (N + M) \log N)$・同上・ summary を「O(3^K N + 2^K (N + M) log N)」にする提案
- docs/graph/steiner-tree.md ・ L117 ・「メモリ制限（1024 MB など）」と MB で書く・ start/notation L107「メモリ制限は AtCoder の表示どおり MiB」、ほかの 6 ページは 1024 MiB・「1024 MiB」に直す
- docs/graph/degree-sqrt.md ・ L27・L128（節題）、L13・L33（summary・要点）、L152・L236 ・「4-サイクル」と書く・ style-guide §7「グラフは『閉路』と言う」・「長さ 4 の閉路」（短くするなら「4 閉路」）に直す。節題を変えるときは sections の title も同時に直し、anchor `four-cycles` は変えない。roadmap L576（生成）と thinking/symmetry-pigeonhole-casework L109 は追従する
- docs/graph/extended-dijkstra.md ・ L274 ／ docs/graph/scc.md ・ L177 ／ docs/graph/k-shortest-paths.md ・ L13・L16 ・「歩道」・付録 A・「ウォーク」に直す（k-shortest-paths の L13 は summary なので提案）
- docs/graph/k-shortest-paths.md ・ L29・L31・L44・L46・L93・L105・L120 ・「ダイクストラ」と「法」を落とす（prh は誤検出のため規則に入れていない）・付録 A「ダイクストラ法」・「ダイクストラ法」に直す。同じ型は graph/steiner-tree L81（見出し）、graph/difference-constraints L113（見出し。「ベルマンフォード」も法なし）、graph/bellman-ford L127、tree/tree-distance L45（見出し）、comb/game-retrograde-analysis L128（見出し）・L200・L226、string/palindrome L122、cpp/cpp-structured-bindings L156、cpp/cpp-undefined-behavior L43。見出しは sections の title と同時に直す。「拡張ダイクストラ」「時間依存ダイクストラ」などの手法名は除く
- docs/graph/minimum-spanning-tree.md ・ L23（frequency_evidence）・「前提として 3 ページに届く（直接 3）」は今の prerequisites では 4（直接 4）・ prerequisites を今の front matter で数え直した値（freq.py）。値（A）は変わらない・ shared の frequency の項を参照（まとめて直す）
- docs/graph/zero-one-bfs.md ・ L168 で取り込む snippets/zero-one-bfs/turns.cpp L14・L30 ・ 行・列の移動量の配列を `dx`・`dy` と書く（行の添字 `i` に `dx` を足している）・ start/notation L80「移動量の配列は行と列の取り違えを避けて di・dj と書く」。ほかの snippets（grid-graph/grid-bfs.cpp など）は di・dj・`di`・`dj` に名前を変える（コード片の名前は執筆者の担当範囲）

## geometry

（見つからなかった）

## tree

- docs/tree/tree-ratio-greedy.md ・ L46 ・「トポロジカル順序」（ほかのページは「トポロジカル順」）・用語のゆれ。付録 A は「トポロジカルソート」で、順は本文の語・「トポロジカル順」にそろえる（軽微）

## string

- docs/string/palindrome.md ・ L18・L41・L109・L112・L117・L122・L125・L187 ・「歩道」（L18 は signs）・付録 A・「ウォーク」に直す。signs は front matter なので提案
- docs/string/trie.md ・ L77 ・「メモリ制限が 1024 MB」・ notation L107 と他ページは MiB・「1024 MiB」に直す
- docs/string/string-automaton-dp.md ・ L37・L111（見出し）・L139・L141・L201・L227・L244・L247 ・「Aho-Corasick」と「法」を落とす・付録 A「Aho-Corasick 法」（prh は「Aho-Corasick 法」を正にしているが、後ろが記号・空白のときに当たらない）・「Aho-Corasick 法」に直す。見出しは sections と同時に

## ds

- docs/ds/lazy-segment-tree-patterns.md ・ L157 ・「フェニック木」・付録 A・「BIT」に直す
- docs/ds/lazy-segment-tree-patterns.md ・ L190・L311 ・「平衡二分木」・付録 A「平衡二分探索木」・「平衡二分探索木」に直す
- docs/ds/binary-trie.md ・ L13（summary）／ docs/ds/wavelet-matrix.md ・ L13（summary）・L24・L31（sections の title）・L62 ／ docs/ds/fenwick-tree.md ・ L72 ／ docs/ds/kth-element.md ・ L74 ・「上位ビット」「最下位ビット」・付録 A「上位 bit」・本文は直し、summary と sections の title は提案（sections の title は見出しと同時に直してよい。§13-2）
- docs/ds/union-find.md ・ L23（frequency_evidence）・「前提として 17 ページに届く（直接 9）」は今は 18（直接 9）・ shared の frequency の項・まとめて直す
- docs/ds/advanced-ds-catalog.md ・ L155 ・「HLD・重軽分解」を表の名前の列に置く・別名は別名の行でだけ使う（§7）。ただしこの表は名前から引く一覧なので、表の中の別名は意図どおりとみなしてもよい・メインが判断（直すなら「HL 分解（HLD）」）

## cpp

- docs/cpp/cpp-integer-overflow.md ・ L91 ・「`1 << 31` は C++20 から `INT_MIN` と決まった」とだけ書き、C++14・C++17 の扱い（処理系定義で GCC では同じ値）がない・ style-guide §5（cpp）の決めた書き方。bit-full-search L165 はそのとおりに書いている・「C++14・C++17 では処理系定義で、GCC では同じ値になる」を足す
- docs/cpp/cpp-integer-overflow.md ・ L92 ・「上位ビット」・付録 A・「上位 bit」に直す

## math

- docs/math/matrix-power.md ・ L137・L141・L143・L145・L175・L190・L191・L192・L296・L373 ・「歩道」を定義して使う（L137 で「歩道は同じ頂点や同じ辺を何度通ってもよい経路」と定義）・付録 A「ウォーク（歩道は使わない）」。graph/k-shortest-paths・glossary は「ウォーク」・「ウォーク」に直す（定義の文も「ウォークは…」に）
- docs/math/spf-sieve.md ・ L200 ／ docs/graph/time-dependent-dijkstra.md ・ L212 ・ $\mathrm{lcm}$ と書く・ §6「$\operatorname{lcm}(a, b)$」・ `\operatorname{lcm}` に直す
- docs/math/mod-inverse.md ・ L228 ／ docs/math/spf-sieve.md ・ L148・L154 ／ docs/guide/method-comparison.md ・ L429 ・ 閉区間 $[L, R]$ の断りがない・ §6・「閉区間」と明記する（区間篩の話は notation が閉区間のまま書くと認めているので、「区間篩と同じく閉区間」と添えればよい）
- docs/math/convolution-ntt.md ・ L287 ・ 本文で $|S|$（`|` のまま）・ notation L157「本文では $\lvert x \rvert$ と書く」・ `\lvert S \rvert` に直す

## comb

- docs/comb/counting-labeled-graphs.md ・ L111・L239・L290（参考の行は原題なら除く）／ docs/comb/counting-mindset.md ・ L260 ／ docs/comb/counting-dedup.md ・ L212 ／ docs/comb/inclusion-exclusion-dp.md ・ L147・L264 ・ グラフの成分を「サイクル」と言う・ §7「グラフは『閉路』、置換は『巡回』と言う」・「閉路」に直す（成分の形を言うので「閉路の成分」など）
- docs/comb/reflection-principle.md ・ L196 ・ 本文で $|d|$・ notation L157・ `\lvert d \rvert` に直す

## patterns

- docs/patterns/permutation.md ・ L12（summary）・「i → P_i の矢印のサイクル」（置換の話）・ §7「置換は『巡回』と言う」・ summary を「巡回」にする提案（patterns/index L16 は生成で追従）

## guide

- docs/guide/cheatsheet.md ・ L58 ・「多重テストケース」・付録 A「複数テストケース（多重テストケースは使わない）」。リンク先の節の題も「複数テストケース」・「複数テストケース」に直す
- docs/guide/debugging-checklist.md ・ L71・L77（囲みの題）・L78・L110・L140・L169 ・「多重テストケース」・同上・「複数テストケース」に直す
- docs/guide/cheatsheet.md ・ L330・L331 ・「上位ビット」「最下位ビット」・付録 A・「上位 bit」「最下位 bit」に直す（L393 は出典の題名なら原文のまま）
- docs/guide/cheatsheet.md ・ L306 ・ 区間 $[L, R]$ の断りがない（式 $\lfloor (L-1)/K \rfloor$ で閉区間と分かる）・ §6・「閉区間 $[L, R]$」と書く
- docs/guide/glossary.md ・ L485 ・ 本文で $|A| < |B|$・ notation L157・ `\lvert A \rvert` に直す
- docs/guide/glossary.md ・ L713 ・ AND を `\mathbin{\&}` と書く・ §6「AND・OR は `$a \text{ AND } b$`」・ $(T - 1) \text{ AND } S$ に直す
- docs/guide/reverse-index-constraints.md ・ L14（complexity）・ guide なのに complexity に値がある・ §2.1・§16-12「計算量のない guide・hub・pattern のページは null のまま」。同じ状態は guide/library-design・guide/method-comparison（guide）、comb/twelvefold-way・dp/dp-speedup-overview・ds/advanced-ds-catalog・graph/graph-modeling（hub）、patterns の 10 ページ（bracket-sequence・divisors-and-multiples・grid・interval・kth-and-median・mex・operation-sequence・permutation・subsequence-and-substring・xor）にもある・ §16-12 どおり null にするか、§16-12 を「計算量の目安を書いてよい」に改めるかをメインが決める（どちらにしても全 17 ページをそろえる）
- docs/guide/problem-sets.md ・ L202 ／ docs/guide/roadmap.md ・ L422 ・「上位ビット」・付録 A・「上位 bit」に直す（roadmap の該当行が生成なら元のページ側を直す）

## start

- docs/start/notation.md ・ L103 ・「多重テストケースで『$N$ の総和は…』」・付録 A・「複数テストケース」に直す（記法の約束のページなので優先度は高い）

## shared

- data/recent-abc.yaml と各ページの frequency_evidence ・ recent の回数が yaml と合わないページが 4 つある：basics/event-sort L23（根拠は recent 1、yaml では abc467_e・abc478_d の 2）、basics/imos L24（根拠 4、yaml では abc465_f を足して 5）、basics/recursion-structure L22（根拠 0、yaml では abc476_g の 1）、comb/binomial-coefficient L22（根拠 0、yaml では abc476_g の 1）・ yaml は dfde401（2026-10-21）から変わっていないので、付け直したときの数え漏れ（1 問に複数のページがある行の 2 つ目以降を落とした可能性）。値への影響：event-sort は A のまま（2 回で A の条件を満たすようになる）、imos は A のまま、recursion-structure は B のまま（recent 1 で B）、binomial-coefficient は A のまま（前提として 28 ページ）・ frequency_evidence の文を yaml から作り直す（値は変えない）
- 各ページの frequency_evidence の「前提として N ページに届く（直接 n）」 ・ 今の prerequisites で数え直すと、sorting-techniques（58→59）、union-find（17→18）、minimum-spanning-tree（3/3→4/4）が違う・骨格の後に prerequisites が足されたため。値は変わらない（A の条件は「届く 13 以上か直接 5 以上」と推定でき、どれも超えている）・作り直すときに一緒に直す
- 各ページの frequency_evidence の「古い ABC n 問」 ・ 108 ページで今の台帳（data/problems.yaml。abc451〜480 を除く ABC の、そのページに載る問題の数）と違う。工程9 の問題の補充で増えたため。B の付け方（recent 0 のときは古い ABC 3 問以上で B と推定できる。全ページがこの規則に合う）を今の台帳に当てると、C→B になるページが 18 ある：comb/bell-number（2→3）、comb/expectation-of-square（2→3）、comb/expectation-tail-sum（2→3）、comb/game-retrograde-analysis（2→3）、comb/mobius-function（1→4）、comb/nim（2→3）、comb/zeta-mobius-subset（2→4）、ds/sparse-table（1→3）、graph/degree-sqrt（1→3）、graph/namori-graph（2→3）、math/crt（2→3）、math/euler-phi（2→4）、math/exponent-mod（2→3）、math/floor-quotient-enum（2→5）、math/spf-sieve（2→5）、string/hash-safety（2→4）、tree/centroid-decomposition（2→3）。逆に B→C になるのは dp/knapsack-undo（3→2。abc321_f・abc441_f）だけ・数えたのは freq3.py（台帳の status が 未確認 のものを除く）。「古い ABC で繰り返し使われた」の基準（3 問以上）と、補充した問題を数えに入れるかは catalog/README §5 に書かれていない・基準をメインが決め、決めた基準で frequency と frequency_evidence を機械的に付け直す。付け直すならスクリプトを tools/ に残す（今は付け直しのスクリプトがリポジトリにない）
- data/recent-abc.yaml と data/problems.yaml ・ 同じ問題を recent-abc はある手法のページに、台帳は別のページに置いている例：abc455_f（recent：lazy-segment-tree-patterns ほか／台帳：lazy-segment-tree）と abc470_g（recent：lazy-segment-tree ほか／台帳：lazy-segment-tree-patterns）は入れ替わっているように見える。abc466_d は recent の pages が空（対応なしの 2 問の 1 つ）で、台帳は patterns/operation-sequence に置く・ recent は「使う手法のページ」、台帳は「問題を載せるページ」で意味が違うので誤りとは限らない・ abc455_f と abc470_g の 2 問だけ、どちらの対応が正しいかを確かめる
- planning/style-guide.md ・ §5（cpp）L183 ・ `-ftrivial-auto-var-init=zero` の計測を「0.04 秒が 1.0 秒になった」と書くが、持ち主の cpp/cpp-environment L113 は「0.05 秒、… 1.03 秒」・持ち主のページの値が正・手引きの値を「0.05 秒が 1.03 秒」に直す
- prh.yml ・ 付録 A で「使わない」とした表記のうち、prh で検出しないもの：「多重テストケース」（8 か所）、「歩道」（約 28 か所）、「上位ビット」「最下位ビット」（約 45 か所。付録 A は「上位 bit」）、「フェニック木」、「平衡二分木」。グラフの「サイクル」も §7 の規則だが検出しない・ prh に `多重テストケース→複数テストケース`、`歩道→ウォーク`、`上位ビット→上位 bit`、`最上位ビット→最上位 bit`、`最下位ビット→最下位 bit`、`平衡二分木→平衡二分探索木`、`フェニック木→BIT` を足す提案（「サイクル」は置換の文脈と区別できないので規則にしない）。付録 A に「最上位 bit」「最下位 bit」を足すかも決める
- planning/style-guide.md 付録 A ・「0-indexed・1-indexed」が正規形だが、「0 始まり」「1 始まり」が約 35 か所ある（basics の項に列挙）。順位（何番目か）の数え方を言う語として認めるか決まっていない・メインが決め、認めないなら prh に足す
