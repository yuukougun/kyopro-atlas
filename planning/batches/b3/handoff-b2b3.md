# b2・b3 からの申し送り（2026-10-22 集約）

b2（青 46 ページ）・b3（黄 35 ページ）の報告（`planning/batches/b2/<id>.md`・`b3/<id>.md`）のうち、ほかのページへの申し送り。形は b1/handoff.md にそろえた。行番号は報告の時点のもので、ページを直すとずれる。相手の段階（draft／stub）は 2026-10-22 のページの front matter で見た。

使い方：

- メインは、相手が draft の §1.1 を節へのリンクに張り替える（b1 decisions の E3・手引き §14-23）。張り替える前に、リンクを置いた文と相手の節の中身が合うかを確かめる
- §1.2 は相手が stub のままのもの。相手が draft になったら張り替える
- §2〜§6 は相手のページの執筆の指示に添える

## 1. 節へ張り替えるリンク

### 1.1 相手がすでに draft のもの（今すぐ張り替えられる）

| リンクを置いたページ（行） | リンク先 | anchor 案 | 申し送りを書いたページ |
| --- | --- | --- | --- |
| matrix-power:159（終端だけでなく fail の先も捨てる） | aho-corasick | #inherit-terminal（string-automaton-dp の案は string-automaton-dp#multiple-patterns。食い違い。どちらかを選ぶ） | aho-corasick・string-automaton-dp |
| kmp:217（Trie にまとめて π の代わりに失敗リンク） | aho-corasick | #build（または #failure-links） | aho-corasick |
| kmp:329・suffix-array:291（使い分けの表） | aho-corasick | ページへのままでよい | aho-corasick |
| rolling-hash:214・trie:300（多数のパターンの出現） | aho-corasick | #count-occurrences | aho-corasick |
| suffix-array:261（ABC362 G は Aho-Corasick 法でも解ける） | aho-corasick | #abc362_g | aho-corasick |
| recursive-enumeration の #pruning（b1 handoff 1.2）・complexity-estimation:138 | bell-number | #size | bell-number |
| dijkstra:193（Johnson） | bellman-ford | #vs-potential | bellman-ford |
| warshall-floyd:115（負閉路で値が小さくなる囲み） | bellman-ford | #relevant-cycles | bellman-ford |
| dp-dag:144（負の重み） | bellman-ford | #longest-path も候補 | bellman-ford |
| dijkstra:144・graph-basics:59・warshall-floyd:299・dijkstra:248 | bellman-ford | ページへのままでよい | bellman-ford |
| difference-constraints の #pitfalls（始点から届かない負閉路） | bellman-ford | #relevant-cycles（#longest-path も） | difference-constraints（検証役の見解） |
| ordered-set#adjacent-pairs（最小の組はソート順で隣り合う。証明は binary-trie 側） | binary-trie | #comparison | binary-trie |
| bitwise-independence の #split-by-top-bit・#comparison の Binary Trie（b1 handoff 361 行） | binary-trie | #implicit・#xor-min-max | binary-trie |
| kth-element:74・trie:299・ordered-set:155（b1 handoff 229 行） | binary-trie | #kth-and-global-xor・#build・#comparison | binary-trie |
| minimum-spanning-tree:214・:288 | bottleneck-path | #why-mst | bottleneck-path |
| union-find-connectivity:159 | bottleneck-path | #kruskal-order | bottleneck-path |
| crt:136（任意 mod の畳み込み、Garner） | convolution-ntt | #convolution-ll | convolution-ntt |
| mod-arithmetic:139・modint:136・acl-reading:116（行の中身は未確認） | convolution-ntt | #acl | convolution-ntt |
| rolling-hash:215 | convolution-ntt | #string-matching | convolution-ntt |
| convolution-ntt#acl（NTT に向く素数と 2^c 乗根） | multiplicative-order | #primitive-root（独立の節はなく末尾の応用の型） | convolution-ntt・multiplicative-order |
| counting-dedup:132（b2 の検証の指摘 4）・dp-grid:74・:292・lattice-paths:112・:176 | inclusion-exclusion-dp | #first-obstacle | counting-dedup・inclusion-exclusion-dp |
| exchange-argument-dp の exchange-argument・interval-dp へのリンク（執筆時 stub） | exchange-argument・interval-dp | 相手の見出しを見て選ぶ（比の比較は exchange-argument#ratios。§2） | exchange-argument-dp |
| expected-value-dp・memoized-recursion・dp-order（b1 handoff の 3 か所） | expectation-linear-equations | #cycle・#unknown など | expectation-linear-equations |
| bit-full-search:188（スイッチと電球、b1 handoff §1.2） | gaussian-elimination | #mod-2 | gaussian-elimination |
| prime-exponent-vector:158（積が平方数） | gaussian-elimination | #rank | gaussian-elimination |
| expectation-linear-equations:151（解き方は掃き出し法） | gaussian-elimination | #real か #row-reduction（執筆者は実数・mod の両方を指すのでページへのまま残した） | gaussian-elimination・expectation-linear-equations |
| gcd-properties の線分上の格子点・「多角形の格子点」 | convex-hull | #lattice-points | gcd-properties・convex-hull |
| argument-sort の参考の行（Graham scan）・floor-sum の表の行・geometry-precision の abc296_g の方針 | convex-hull | #andrew・#point-in-convex-polygon・#lattice-points | convex-hull |
| warshall-floyd:193・tree-construction:189（距離表からグラフを作る） | graph-construction | #from-distances | graph-construction |
| construction:174 | graph-construction | ページへのままでよい | graph-construction |
| nim#bounded の「Grundy 数のページ」 | grundy-number | #patterns | grundy-number |
| rolling-hash:102・:103 | hash-safety | #birthday-bound | hash-safety |
| rolling-hash:109・:114 | hash-safety | #recommended-design（または #mod-2-64）・#mod-2-64 | hash-safety |
| knapsack-01:217・knapsack-undo:148・:218 | divide-and-conquer | #range-knapsack | knapsack-undo・divide-and-conquer |
| monotonic-stack:298・sparse-table:61 | divide-and-conquer | #split-at-max | divide-and-conquer |
| sparse-table:145 | divide-and-conquer | #range-knapsack | divide-and-conquer |
| inversion-number:133・recursion-structure:156 | divide-and-conquer | #crossing | divide-and-conquer |
| inversion-number:134（区間ごとの転倒数） | mo-algorithm | #implementation | mo-algorithm |
| offline-queries:267・hashing-for-sets:111 | mo-algorithm | #what-it-does | mo-algorithm |
| hashing-for-sets:261（O(N√Q) の見積もり） | mo-algorithm | #ordering | mo-algorithm |
| euler-tour:188・:195・:319 | mo-algorithm | #mo-on-tree | mo-algorithm |
| binary-search-answer:165・reformulation:59 | kth-value | #why-count | kth-value |
| two-pointers:147 | kth-value | #counting-patterns | kth-value |
| binary-search:178・greedy-priority-queue:143・:192・kth-element:166・fractional-binary-search:217 | kth-value | ページへのままでよい（必要なら #why-count） | kth-value |
| inversion-number:135（0/1 の列の区間反転と転倒数） | lazy-segment-tree-patterns | #flip | lazy-segment-tree-patterns |
| lazy-segment-tree:155（型の一覧） | lazy-segment-tree-patterns | #pattern-table | lazy-segment-tree-patterns |
| lazy-segment-tree:302（値と作用を自分で設計する） | lazy-segment-tree-patterns | #design-steps | lazy-segment-tree-patterns |
| lazy-segment-tree-patterns から sqrt-decomposition・sweep-line-2d・difference-sequence・segment-tree-monoids へのページのリンク（執筆時 stub） | 各ページ | 相手の見出しを見て選ぶ | lazy-segment-tree-patterns |
| bracket-sequence:171 | parsing | #bnf | parsing |
| stack-techniques:160 | parsing | #deep-nesting | parsing |
| string-basics:199 | parsing | ページへのままでよい | parsing |
| tree-imos#depth-limited（b1 handoff §2） | root-path-dfs | #path-statistics | root-path-dfs |
| lis:180（lis#variants の末尾。文言「根からのパスを持つ DFS」は題名「根からのパスを DFS で持ち回る」と違う） | root-path-dfs | #undo-log（文言も題名に） | root-path-dfs |
| digit-dp:219 | string-automaton-dp | #matching-state | string-automaton-dp |
| dp-state-design:136・:317・kmp:210 | string-automaton-dp | #kmp-automaton（kmp:210 は L が巨大なら #matrix-power） | string-automaton-dp |
| matrix-power:316 | string-automaton-dp | #multiple-patterns | string-automaton-dp |
| string-automaton-dp の使い分けの表（執筆時 stub） | subsequence-dp | 相手の見出しを見て選ぶ | string-automaton-dp |
| subset-enumeration-dp の abc321_g の方針 | counting-labeled-graphs | #component-of-1 か #complement | subset-enumeration-dp |
| bit-operations:146 | subset-enumeration-dp | #why-3n | subset-enumeration-dp |
| bit-operations:178 | subset-enumeration-dp | #submask-loop | subset-enumeration-dp |
| bipartite-matching の max-flow・konig-theorem・min-cost-flow へのリンク（執筆時 stub） | 各ページ | 相手の見出しを見て選ぶ（#reduction の整数性は直しで max-flow#residual に張り済み） | bipartite-matching |
| tree-degree#counting-links のこのページの呼び名「ラベル付き木の数と Prüfer 列」 | cayley-pruefer | 題名「ラベル付き木の数え上げ」に合わせる | cayley-pruefer |
| tree-basics・tree-construction の tree-degree の呼び名「次数と次数列」「次数と木」 | tree-degree | 題名「木の次数列と Prüfer 列」へそろえるか | tree-degree |
| rerooting:178・tree-edge-contribution:160・:178・small-to-large:303 | centroid-decomposition | #count-through | centroid-decomposition |
| divide-and-conquer:165 | centroid-decomposition | #depth | centroid-decomposition |
| roadmap:582（距離の頻度表は畳み込みと組む） | centroid-decomposition | #with-convolution | centroid-decomposition |
| counting-labeled-graphs の使い分けの表の cayley-pruefer・zeta-mobius-subset | 各ページ | 相手の見出しを見て選ぶ（#by-size は直しで cayley-pruefer#cayley に張り済み） | counting-labeled-graphs |
| digit-dp:132（総和） | digit-dp-advanced | #count-and-sum | digit-dp-advanced |
| digit-dp:178（2 つの数の上限・繰り上がり） | digit-dp-advanced | #multiple-numbers（繰り上がりは #carry） | digit-dp-advanced |
| digit-dp:218 | digit-dp-advanced | ページへのままでよい | digit-dp-advanced |
| memoized-recursion:159（状態がまばら） | digit-dp-advanced | #sparse-states | digit-dp-advanced |
| spf-sieve の linear-sieve の節（黄のページの定義を前提にしている。spf-sieve の検証の指摘） | euler-phi | #formula | euler-phi |
| multiplicative-order#count-by-order（位数 d の元が φ(d) 個） | euler-phi | #divisor-sum（euler-phi を証明の持ち主にする案。§2） | euler-phi |
| linearity-of-expectation:198（nonlinear の表の二乗の行） | expectation-of-square | #pairs（:306 はページのままでよい） | expectation-of-square |
| expectation-tail-sum の exactly-vs-at-least の節 | expectation-of-square | #pairs（検証の指摘 5。執筆者は §14-23 に従いメインへ回した） | expectation-tail-sum |
| coupon-collector:59 | expectation-tail-sum | #identity | expectation-tail-sum |
| coupon-collector:132 | expectation-tail-sum | #waiting-time | expectation-tail-sum |
| linearity-of-expectation:199・:304 | expectation-tail-sum | #kth-value | expectation-tail-sum |
| counting-mindset:111 | expectation-tail-sum | #kth-value か #identity | expectation-tail-sum |
| inclusion-exclusion-dp の insertion-dp・tree-dp-square へのリンク（執筆時 stub） | 各ページ | 相手の見出しを見て選ぶ | inclusion-exclusion-dp |
| bipartite-graph:170・tree-bipartite:142 | konig-theorem | #theorem | konig-theorem |
| konig-theorem の bipartite-matching・min-cut・project-selection へのリンク（執筆時 stub） | 各ページ | bipartite-matching#reduction・min-cut#restore など | konig-theorem |
| cycle-detection:161・namori-graph:189・shortest-path-dag:187 | lowlink | #conditions | lowlink |
| dfs:129 | lowlink | #ord-low | lowlink |
| graph-basics:81 | lowlink | #multi-edges | lowlink |
| scc:115・:267 | lowlink | #vs-scc | lowlink |
| scc:199 | lowlink | #two-edge-connected（あるいはページのまま） | lowlink |
| min-cut の残余グラフ（今は最大流のページへのリンク） | max-flow | max-flow の節（または用語集の #residual-graph が入れば） | min-cut |
| project-selection の min-cut・max-flow・konig-theorem へのリンク（執筆時 stub） | 各ページ | min-cut#restore など | project-selection |
| binomial-precompute:94・lattice-paths:91・:175・bracket-sequence:79・:120・counting-bijection:111・:124 | reflection-principle | #catalan（括弧列・表の大きさ）、#reflection か #complement-count（境界線を越えない経路・途中で負にならない） | reflection-principle |
| subsequence-matching:165（使い分け） | dp-phase・subsequence-dp | 「何通り取り出せるか」（位置の組）は dp-phase#matched-prefix、異なる部分列の数は subsequence-dp#next-table-dp | subsequence-dp |
| lcs:321 | subsequence-dp | 種類数だけを #next-table-dp（判定は subsequence-matching） | subsequence-dp |
| string-automaton-dp:305 の表 | dp-phase・counting-dedup・subsequence-dp | 個数（位置の組）は dp-phase#matched-prefix、含む文字列の数は counting-dedup#leftmost、部分列 DP は異なる部分列の種類のとき | subsequence-dp |
| dp-reconstruction:191 | subsequence-dp | #kth-subsequence | subsequence-dp |
| dp-reconstruction:270（ARC081 E の方針） | subsequence-dp | #shortest-non-subsequence | subsequence-dp |
| lcs:166（異なる共通部分列の種類） | subsequence-dp | #positions-or-strings か #leftmost | subsequence-dp |
| dp-phase:235 | subsequence-dp | #positions-or-strings | subsequence-dp |
| counting-dedup:104・:130 | subsequence-dp | #leftmost | subsequence-dp |
| binary-trie の #comparison など | xor-basis | #max（作れる値の最大）・#kth（K 番目） | xor-basis |
| bit-operations・nim・bitset-speedup の xor-basis へのリンク | xor-basis | #insert・#max など | xor-basis・bitset-speedup |
| zeta-mobius-subset の counting-labeled-graphs へのリンク（執筆時 stub） | counting-labeled-graphs | 相手の見出しを見て選ぶ | zeta-mobius-subset |
| hash-safety → hashing-for-sets#random-values（今はページへのリンク） | hashing-for-sets | #random-values。ただし check_pages が anchor を拾えない。見出し「値ごとに乱数を割り当てる理由（値そのものを足すと {1, 4} と {2, 3} が衝突する） {#random-values}」の波かっこで attr_list が崩れている可能性。見出しを言い換えるか check_pages を確かめる（style.md の euler-phi の提案と関係） | hash-safety |

### 1.2 相手がまだ stub のもの

| リンクを置いたページ | リンク先（stub） | anchor 案 | 申し送りを書いたページ |
| --- | --- | --- | --- |
| bottleneck-path の reconstruction-tree の節 | merge-process-tree | #bottleneck・#group-as-interval（parallel-binary-search・partially-persistent-union-find もページへのリンク） | bottleneck-path |
| convolution-ntt#acl | fft-ntt | #ntt-prime | convolution-ntt |
| gcd-properties の同余最短路 | modular-shortest-path | #congruence | gcd-properties |
| hash-safety の Miller-Rabin | miller-rabin | 節ができたら | hash-safety |
| parsing の cpp-environment#stack-depth | cpp-environment | #stack-depth | parsing |
| lazy-segment-tree-patterns の segment-tree-beats・mex | segment-tree-beats・mex | 節ができたら | lazy-segment-tree-patterns |
| interval-dp の分割点型の「括弧の対応」の応用の型 | bracket-dp（catalog にあれば） | — | interval-dp |
| subset-enumeration-dp の chromatic-number（2 か所）・konig-theorem・zeta-mobius-subset の chromatic-number | chromatic-number | #independent-set（konig-theorem）ほか | subset-enumeration-dp・konig-theorem・zeta-mobius-subset |
| subset-enumeration-dp#vs-zeta の「部分集合の畳み込み O(2^N N^2)」 | 持ち主の節（zeta-mobius-subset か発展のページ） | §2 | subset-enumeration-dp |
| bipartite-matching の節 edge-coloring の冒頭（Hall の結婚定理） | dilworth-path-cover | #hall | bipartite-matching |
| bipartite-matching・konig-theorem の general-matching | general-matching | 節ができたら | bipartite-matching・konig-theorem |
| broken-profile-dp（catalog の related の grid#tiling） | patterns/grid | #tiling（使い分けから） | broken-profile-dp |
| convex-hull の双対の節 | cht | cht から convex-hull#cht-duality へ、cht 側の該当節へも張り合わせる | convex-hull |
| counting-labeled-graphs の使い分けの表 | matrix-tree-theorem | 節ができたら | counting-labeled-graphs |
| euler-path の BEST 定理（2 か所） | matrix-tree-theorem | #best-theorem | euler-path |
| expectation-tail-sum の #continuous | continuous-probability | #integral | expectation-tail-sum |
| project-selection の two-sat | two-sat | 節ができたら | project-selection |
| zeta-mobius-subset の hadamard-transform | hadamard-transform | 節ができたら | zeta-mobius-subset |
| lowlink の練習問題の節（abc334_g は offline-dynamic-connectivity の例題へのリンク） | offline-dynamic-connectivity | 台帳に lowlink の役割が付いたら問題の囲みに移す（ledger.md） | lowlink |
| binomial-identities・convolution-ntt・sigma-manipulation・mobius-function の Iverson の記法 [P] | start/notation | notation に [P] の 1 行を足す（§3） | mobius-function |
| sqrt-decomposition の「重い頂点」 | 用語集 heavy-vertex（degree-sqrt の提案。glossary.md） | — | sqrt-decomposition |

### 1.3 解決済み（執筆者・検証の直しで張り替え済み）

- bell-number の recurrence の節 → inclusion-exclusion#surjection
- bitset-speedup → degree-sqrt#triangles・gaussian-elimination#mod-2（xor-basis は §1.1 に残る）
- expectation-linear-equations:155 → gaussian-elimination#mod-p
- inline-dp:151 → monotonic-stack#procedure、inline-dp:90 → dp-segment-tree#values-on-segment-tree、ACL の囲み → lazy-segment-tree#acl-standard
- randomized → hash-safety#what-to-randomize・circle-geometry#min-enclosing-circle
- string-automaton-dp の multiple-patterns 節 → aho-corasick#build・#inherit-terminal
- lazy-segment-tree-patterns の design-steps → segment-tree-monoids#design-steps（手順を縮めた）
- counting-labeled-graphs の #by-size → cayley-pruefer#cayley、#subset-dp → subset-enumeration-dp#fix-minimum
- bipartite-matching の #reduction の整数性 → max-flow#residual
- b1 handoff の §2 で b2・b3 に回した確認：tree-construction（abc252_g）と interval-dp-advanced は食い違わない、counting-bijection の Prüfer 列の事実は cayley-pruefer と食い違わない、nim／grundy-number の配分は決まった（逆形 Nim は nim#misere、arc105_d は game-basics の練習）、tree-imos／root-path-dfs は §1.1 の行で解決

## 2. 内容の重なり（後から書く側が、先に書かれたページへリンクして短くする）

| ページ | 重なる相手 | 申し送り |
| --- | --- | --- |
| exchange-argument#ratios | exchange-argument-dp#compare-ratios・sorting-techniques#ratio-and-ties | 持ち主を exchange-argument#ratios にし、ほかはリンクで済ませる（両ページの提案が一致）。exchange-argument-dp は DP 側の例（一次関数の合成）だけ残す |
| exchange-argument の落とし穴「double の比は誤差で同点になって同等の推移を壊す」 | exchange-argument-dp の指摘 1 の直し | 要素ごとに決まる double のキーの比較は推移的で、害は順の取り違え（誤答）。exchange-argument 側も直っているか確かめる（exchange-argument-dp の提案） |
| bottleneck-path#reconstruction-tree（発展の概要） | merge-process-tree#bottleneck（stub） | 持ち主を決める。merge-process-tree を書くときにこちらへリンクするか、こちらを短くする |
| bitset-speedup の使い分け「疎なグラフの三角形は O(M√M)」 | degree-sqrt | 食い違いがないかを確かめる |
| divisor-inclusion-exclusion の周期の節（巡回シフトとベズーによる証明） | kmp（弱周期定理） | 両者の整合を確かめる |
| dp-dimension-reduction の導入（段の次元の使い回し） | knapsack-01#dp-rolling-array | リンクで済ませた。catalog の research の (a) 型をこのページで扱わない判断でよいか |
| expectation-linear-equations#linear-system（mod p の掃き出し） | gaussian-elimination#mod-p | 1 文に縮めてリンク済み。expected-value-dp の確認問題のコインの例（答え 6）を図で解き直したのは意図した重複 |
| optimal-strategy-expectation#guess-answer | expectation-linear-equations#unknown | 「f(y) − y の単調性」の言い方をそろえる（検証の直しで「広義に減少」にした） |
| interval-dp の ABC325 G の力試しの方針 | interval-dp-advanced | 詳しく書くなら interval-dp-advanced へ移すか、ここで状態の定義まで書くか |
| interval-dp-advanced の sections の 4 節 | 練習の解き方（ABC206 F・ABC273 F・ABC292 G） | b1 handoff §2.1 と同じ形。直しで問題名を外したが、ABC292 G を例題に上げるかはメイン |
| inline-dp の with-monotonic-stack の節の例 | 力試し abc480_g の解き方 | ほぼ同じ。abc480_g を節の例題に移すか（ledger.md §1） |
| segment-tree-monoids#design-steps・#pattern-table | lazy-segment-tree-patterns#design-steps・#pattern-table | 同じ anchor を持つ。こちらは作用の側。重なりを確かめる |
| offline-queries#compress・persistent-data-structures | merge-sort-tree | 「(位置, 値) の組を枠として先に全部集める」の言い回し（「枠」）をそろえる |
| root-path-dfs の no-path-compression の節 | rollback-union-find（stub）#no-path-compression・#with-dfs | rollback-union-find を書くときに食い違わないよう確かめる（こちらは併合の記録 2 件・経路圧縮すると戻しても分かれない・union by size で O(log N) まで） |
| root-path-dfs | minimax#tree | minimax#tree は root-path-dfs を前提にしている。abc218_g は両方の力試し |
| euler-phi#divisor-sum（位数 d の元が φ(d) 個、証明） | multiplicative-order#count-by-order | euler-phi を証明の持ち主にし、multiplicative-order から euler-phi#divisor-sum へリンク（euler-phi の検証の指摘 7。multiplicative-order は原始根による証明に絞り和の式は euler-phi へリンク済み） |
| euler-phi（指数の mod の一般化・累乗の塔） | exponent-mod#euler-theorem | exponent-mod を持ち主とみなしリンクだけ |
| cayley-pruefer の発展の節の計算量（FPS の累乗 O(N log N) など） | fps-basics・generating-function-counting（stub） | 相手が draft になったら照らす |
| tree-centroid（全頂点への距離の和は重心で最小、証明） | tree-dp#reroot-difference の確認問題（差分の計算） | 両方残してよい |
| difference-sequence（差分列を d_0..d_N の N + 1 個） | imos#adjacent-difference（内側の d_1..d_{N−1}） | 定義をそろえる（style.md の §5 basics の提案） |
| complement-graph-bfs の計算量の言い方 | linked-list・ordered-set の rows-and-columns | 「消した要素を二度と見ない」型の言い方をそろえる |
| 部分集合の畳み込み（ランク付きゼータ O(n^2 2^n)） | zeta-mobius-subset の vs-xor・subset-enumeration-dp#vs-zeta | 持ち主のページがない。発展のページを作るか、どちらかに寄せる |
| string-automaton-dp の snippets/string-automaton-dp/aho-dp.cpp:build | aho-corasick | 持ち主をどちらにするか（aho-corasick 側へ移してよいと申し送りあり） |
| 照合の状態の DP の「終端の印を失敗リンク先から受け継ぐ」 | aho-corasick#inherit-terminal・string-automaton-dp#multiple-patterns・matrix-power の dp-transition | 持ち主を 1 つに決め、ほかはリンク（style.md にも） |
| bipartite-graph:171「最小カットで表せるのは『2 つが違うとコスト』の形」 | project-selection | 正しくは「片方だけ 1 のときのコスト（向きのある罰）」とその和。違うと罰は表せるので誤りではないが確かめる |
| 分割数の p(n,k) の定義（partition-number は「部分が k 以下」、ちょうど k 個は p(n−k,k)） | twelvefold-way・stars-and-bars | 書くときにそろえる |
| sqrt-decomposition の「Mo's algorithm もクエリを平方分割する方法と呼ばれることがある」 | mo-algorithm（aliases から「クエリ平方分割」を外す提案。other.md） | 言い方をそろえる |
| tree-isomorphism（stub） | tree-centroid | 重心が 2 個のときの扱い（両方試す・辺に仮の頂点を足す）を同型判定のページを書くときにそろえる |
| dynamic-dp（stub） | subsequence-dp・segment-tree-monoids | subsequence-dp：末尾の文字ごとの異なる部分列の数を持つと (σ + 1) 次の行列になりセグ木に載る（abc246_h を書くときに #next-table-dp を参照）。segment-tree-monoids：行列の向き（§3） |
| gaussian-elimination#mod-2「XOR 基底は掃き出しを 1 行ずつ足しながら行うもの」 | xor-basis の insert の囲み | 合っている。張り替え不要 |

## 3. 記法の提案（b1 の E1 のとおり、start/notation を書くときにまとめる）

| 提案 | 出したページ |
| --- | --- |
| 木の Mo：長さ 2N の列の位置 $\mathrm{ST}(v)$・$\mathrm{EN}(v)$ を §6 の木の記法に足す（euler-tour#mo-on-tree にそろえた） | mo-algorithm |
| 分散 $V[X]$ を確率 $P(A)$・期待値 $E[X]$ と並べる | expectation-of-square |
| Iverson の記法 $[P]$ を notation に足す（binomial-identities・convolution-ntt・sigma-manipulation・mobius-function が使う。b1 handoff §3 の sigma-manipulation と同じ） | mobius-function |
| 行列をセグメント木に載せる向き：segment-tree-monoids は状態を横ベクトル・(p, q) 成分は p → q・op(a, b) = ab、matrix-power は縦ベクトル v' = Av（b1 handoff §3）。dynamic-dp を書くときにどちらかにそろえる | segment-tree-monoids |
| 失敗リンクの記号：string-automaton-dp は fail[v]・頂点、aho-corasick は link(v)・節点 | string-automaton-dp |
| 問題に合わせた二項演算を一般に書く記号（subset-enumeration-dp は ∘） | subset-enumeration-dp |
| 差分列の添字の範囲（d_0..d_N か d_1..d_{N−1}） | difference-sequence |
| 互換（transposition）と swap の表記を置換のページ群（permutation-cycles・permutation-parity・inversion-number）でそろえる | permutation-parity |
| `__int128` の mulmod の置き場（miller-rabin#mulmod か mod-pow を持ち主にしてほかはリンク。euler-phi・multiplicative-order など法 10^12・10^13） | multiplicative-order |

## 4. 逆引き・早見表への追加

| 行き先 | 追加する行 | 出したページ |
| --- | --- | --- |
| 早見表・使い分け | 「和・差の分布を値の範囲 10^6 程度まで → 畳み込み」「添字の XOR → アダマール変換」「添字の OR・AND → 部分集合のゼータ変換」 | convolution-ntt |
| complexity-estimation#count-candidates の表 | 「分割数 p(N)：p(30) = 5604、p(50) = 204226、p(100) ≈ 1.9×10^8」（07 調査 §7.5 と同じ） | partition-number |
| term-index | 「クエリ平方分割 → Mo's algorithm」を sqrt-decomposition（#query-buckets）へ向ける | mo-algorithm |

## 5. 計測値・数値の不一致

- kth-value：「二分探索は約 61 回」は V ≈ 2×10^18 の場合（log2 ≈ 60.8）。ほかのページの「約 60 回」（10^18）とは V が違う
- convolution-ntt：長さ 5×10^5 どうしで約 55 ms・約 180 ms は手元 g++-15 -O2 の 1 回の計測（直しで比の約 3〜4 倍だけにした）。AtCoder の環境の値ではない
- hash-safety：unordered_map への攻撃（10^5 個で 3.2 秒、2×10^5 個で 17.5 秒）は手元 g++-15 の 1 回の計測。バケットの数の列（172933・351061）は libstdc++ の実装による
- merge-sort-tree：N = Q = 2×10^5 の目安は見積もり（約 1.3×10^8 回の比較）で、直しで実測 0.4 秒・vector で 100 MB を書いた
- aho-corasick：abc458_f の「状態は 101 個以下」は gdst.dev で制約を確かめた値（matrix-power のページの「100 程度」とそろえる）
- knapsack-undo：long long の表 2 つで約 16NW バイト、NW = 6.4×10^7 で 1024 MB
- bitset-speedup：典型90 059 の詳細は約 3.1×10^8 回の語の演算（うち OR は約 1.6×10^8 回）

## 6. 相手のページを書くときの内容

- merge-process-tree：abc235_h（同じ重みの辺で成分がまとまる過程で塗り方を数える、diff 2967）は力試し向き（candidates.md）。bottleneck-path#reconstruction-tree との分担（§2）
- rollback-union-find：root-path-dfs の no-path-compression の節と食い違わないように（§2）
- dynamic-dp：行列の向き（§3）、subsequence-dp の (σ + 1) 次の行列の説明（§2）
- cht：convex-hull#cht-duality と張り合わせる。上側凸包・下側凸包の語を共有するなら用語集に（glossary.md）
- matrix-tree-theorem：euler-path の BEST 定理（有向グラフの）からのリンク先 #best-theorem を立てる
- tree-isomorphism：重心が 2 個のときの扱い（§2）
- fps-basics・generating-function-counting：cayley-pruefer の発展の節の計算量と照らす
- twelvefold-way・stars-and-bars：p(n,k) の定義（§2）
- miller-rabin：`__int128` の mulmod の持ち主の候補（§3）
- multiplicative-function：mobius-function の「杜教篩で O(N^{2/3})」とメルテンス関数は記憶による一般的な事実。執筆時に出典で確かめる
- continuous-probability：expectation-tail-sum の #continuous から #integral へのリンク
- general-matching・dilworth-path-cover：bipartite-matching・konig-theorem からのリンク（Hall の結婚定理は dilworth-path-cover#hall）
- offline-dynamic-connectivity：abc334_g（関節点でも解ける）を lowlink の練習にも置く提案がある（ledger.md）
- 動く図：max-flow の max-flow-residual は JS と試験の作成を頼む（仕様は max-flow の報告の「動く図の仕様」）。作るなら仕様のあるもの：dp-segment-tree（区間 max のセグ木・deque）、gaussian-elimination（掃き出しのステップ送り）、tree-degree（pruefer）、convex-hull（Andrew のスタック）（other.md）
