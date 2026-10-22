# b4・b5 からの申し送り（2026-10-22 集約）

b4（発展の概要 50 ページ）・b5（横断ページ 33 ページ）の報告（`planning/batches/b4/<id>.md`・`b5/<id>.md`）のうち、ほかのページへの申し送り。形は b1/handoff.md・b3/handoff-b2b3.md にそろえた。行番号は報告の時点のもので、ページを直すとずれる。2026-10-22 の時点で全 353 ページが draft なので、§1 はすべて今すぐ張り替えられる。「今」の列は、リンクを置いたページの本文に相手へのリンクがどの形であるかを 2026-10-22 に grep で見た結果（page＝anchor なし、— ＝相手へのリンクがない）。anchor 案はすべて相手のページに存在することを確かめた。

使い方：

- メインは §1 を節へのリンクに張り替える（§14-23）。張り替える前に、リンクを置いた文と相手の節の中身が合うかを確かめる
- §1.2 は執筆者がバッチの中で自分のページを張り替え済みのもの（メインの作業は不要。確認だけ）
- §2〜§6 は相手のページの直しの指示に添える

## 1. 節へ張り替えるリンク

### 1.1 張り替えが残っているもの

| リンクを置いたページ（行） | リンク先 | anchor 案 | 申し送りを書いたページ | 今 |
| --- | --- | --- | --- | --- |
| advanced-geometry#segment-intersections | sweep-line-2d | 新しい節（軸に平行な線分の交点を数える。§6）を足したらその節へ | advanced-geometry | page |
| counting-basics:91（色の個数が決まった例） | burnside-lemma | #necklace（検証役も同じ） | burnside-lemma | page |
| counting-basics:191・counting-dedup:63・226・245 | burnside-lemma | 案なし（ページへのままか、文に合う節を選ぶ） | burnside-lemma | page |
| divisor-inclusion-exclusion:150 | burnside-lemma | #by-period | burnside-lemma | page |
| euler-phi の応用の型（ネックレスの式） | burnside-lemma | #necklace。あわせてリンクの文字「バーンサイドの補題」を題名の「Burnside の補題」に | burnside-lemma | page |
| expectation-tail-sum#continuous | continuous-probability | #integral（handoff-b2b3 の申し送り） | continuous-probability | page |
| lgv-lemma（法が素数でないとき） | determinant | #modulus | determinant・lgv-lemma | page |
| matrix-tree-theorem（行列式の前提） | determinant | ページへのまま。掃き出しは gaussian-elimination#mod-p。自作の要点（法が素数でないとき）を determinant へ寄せてもよい（§2） | matrix-tree-theorem | page |
| bipartite-matching:157（Hall の定理） | dilworth-path-cover | #hall。リンクの文字を「Hall の結婚定理」に | dilworth-path-cover | page |
| generating-function-counting#to-fps | fps-basics | #operations | fps-basics・generating-function-counting | page |
| stirling-first・cayley-pruefer（FPS の演算） | fps-basics | #operations・#polynomial-ops（cayley-pruefer は #polynomial-ops） | fps-basics | page |
| linear-recurrence-fast（きたまさ法の節の「多項式の割り算」） | fps-basics | #polynomial-ops | linear-recurrence-fast | page |
| fps-basics（lagrange-interpolation・online-convolution へ） | lagrange-interpolation・online-convolution | 文に合う節（stub だったのでページへ） | fps-basics | page |
| generating-function-counting（stirling-first・online-convolution へ） | stirling-first・online-convolution | 文に合う節。online-convolution へは今リンクが見当たらない（直しで消えた可能性） | generating-function-counting | page・— |
| bipartite-matching・konig-theorem | general-matching | #odd-cycles など（handoff-b2b3 の申し送り） | general-matching | page |
| dijkstra:220（K 番目の最短路） | k-shortest-paths | #k-times | k-shortest-paths | page |
| euler-path:148・219 | matrix-tree-theorem | #best-theorem（handoff-b2b3） | matrix-tree-theorem | page |
| tree-degree・cayley-pruefer・counting-labeled-graphs・small-graph-brute-force | matrix-tree-theorem | #laplacian | matrix-tree-theorem | page |
| bottleneck-path#reconstruction-tree（「木の作り方の詳細は併合過程の木のページ」） | merge-process-tree | #new-vertex。「重み x 以下の辺で v から行ける頂点」の段落は #group-as-interval | merge-process-tree | page |
| partially-persistent-union-find#alternatives・parallel-binary-search#alternatives・small-to-large（abc183_f の別解と使い分けの表） | merge-process-tree | #group-as-interval・#bottleneck・#alternatives（文に合わせて選ぶ） | merge-process-tree | page |
| hash-safety（Miller-Rabin へ。b3 handoff §1.2） | miller-rabin | #deterministic-bases | miller-rabin | page |
| gcd-properties#frobenius（同余最短路。b3 handoff §1.2） | modular-shortest-path | #congruence | modular-shortest-path | page |
| extended-dijkstra:396・zero-one-bfs:152・digit-and-mod:93・217（b1 handoff） | modular-shortest-path | #residue-vertices | modular-shortest-path | page |
| digit-and-mod:210 | modular-shortest-path | #arc084_b（例題） | modular-shortest-path | page |
| binary-search-answer:167 | parallel-binary-search | #what-it-does | parallel-binary-search | page |
| offline-queries:118 | parallel-binary-search | #what-it-does | parallel-binary-search | page |
| union-find-connectivity:165・268 | parallel-binary-search | #with-union-find | parallel-binary-search | page |
| bottleneck-path:129 | parallel-binary-search | #alternatives | parallel-binary-search | page |
| partially-persistent-union-find（関連の rollback-union-find・merge-process-tree） | rollback-union-find・merge-process-tree | 文に合う節（検証の指摘 4 で、メインの張り替えに任せると明記） | partially-persistent-union-find | page |
| nim#asymmetric・grundy-number#limitations | partizan-games | #why-not-grundy・#tempo | partizan-games | page |
| spanning-tree-advanced:106（併合可能なヒープ） | advanced-ds-catalog | #meldable-heap（b4 の追加の提案と b5 の申し送りが一致） | spanning-tree-advanced・advanced-ds-catalog | page |
| priority-queue:196 | advanced-ds-catalog | #meldable-heap。リンクの文字「発展的なデータ構造の一覧」を題名「見慣れないデータ構造の名前と用途」に | advanced-ds-catalog | page |
| cdq-divide-and-conquer:119（2 次元セグ木の行） | advanced-ds-catalog | #table。リンクの文字も題名に | advanced-ds-catalog | page |
| slope-trick:125（「併合できるヒープ（meldable heap）」） | advanced-ds-catalog | #meldable-heap へのリンクを新たに張り、語を「併合可能なヒープ」に | advanced-ds-catalog | — |
| k-shortest-paths:87（「併合できるヒープ」） | advanced-ds-catalog | 同上 | advanced-ds-catalog | — |
| project-selection（two-sat へ。handoff-b2b3 §1.2） | two-sat | #when-to-use | two-sat | page |
| glossary の color・difficulty・rating・performance・penalty・contest-types の項と #atcoder の前置き | atcoder-system | #colors・#difficulty・#rating（rating・performance）・#ranking（penalty）・#contests（contest-types） | atcoder-system・glossary | page |
| glossary の shojin・upsolve・atcoder-problems | practice-method | ページ・#upsolve・#atcoder-problems | glossary | page |
| glossary の verify | library-design | #verify | glossary | page |
| glossary の adt・typical90 | problem-sets | #practice-contests・#typical90-stars | glossary | page |
| glossary の naive-solution・counterexample | stress-testing | #procedure（stress-testing も同じ案） | glossary・stress-testing | page |
| glossary の judge の節の頭 | debugging-checklist | ページへのまま | glossary | page |
| contest-strategy（要点・#ai-rules の末尾・#difficulty-by-position の「difficulty の帯」） | atcoder-system | #ai-rules・#levels（#ranking も） | atcoder-system・contest-strategy | page |
| problem-sets#practice-contests の末尾 | atcoder-system | #contests | atcoder-system | page（#difficulty は張り済み） |
| contest-strategy | debugging-checklist・thinking-checklist・stress-testing・practice-method・how-to-use・roadmap | #before-submit、#q-misreading ほか、#procedure・#experiment、#upsolve・#when-to-read・#records、#claude・#ai-rule-version、#recent-positions | contest-strategy | page |
| cheatsheet（C++ の版の表） | cpp-environment | #version-matrix（あわせて行と GCC の版を照らし合わせる） | cheatsheet | page |
| cheatsheet（計算量と制約の節の最初のリンク） | reverse-index-constraints | 帯の節（signs-constraint-* など） | cheatsheet | page |
| reverse-index-constraints（AtCoder の C++ の環境） | cpp-environment | 文に合う節（#options など） | reverse-index-constraints | page |
| bipartite-graph:141 | graph-modeling | #what-to-edge か #what-to-vertex | graph-modeling | page |
| connected-components:129・extended-dijkstra:397 | graph-modeling | #what-to-vertex | graph-modeling | page |
| difference-constraints:219 | graph-modeling | #constraints-to-edges。リンクの文字「グラフへの言い換え」を題名「グラフへの帰着」に | graph-modeling | page |
| euler-path:221 | graph-modeling | #contraction。リンクの文字「グラフの作り方」を題名に | graph-modeling | page |
| grid#rows-cols（行や列の塗り替え） | operation-sequence | #overwrite | grid | page |
| warshall-floyd:296・zero-one-bfs:269（使い分け） | method-comparison | #shortest-path | method-comparison | page |
| roadmap（problem-sets 以外の stub だった相手） | reverse-index-signs・reverse-index-constraints・thinking-checklist | 文に合う節（problem-sets は直しで #recent-abc へ張り替え済み） | roadmap | page |
| reverse-index-signs（patterns の 9 ページ） | grid・interval・mex・permutation・xor・divisors-and-multiples・kth-and-median・operation-sequence・subsequence-and-substring | #overview（bracket-sequence の形） | reverse-index-signs | page |
| reverse-index-signs | method-comparison・reverse-index-constraints | 比較の節（最短路・区間のクエリの組）・帯の節 | reverse-index-signs | page |
| reverse-index-signs | term-index・thinking-checklist・stress-testing・cheatsheet・cpp-reverse-index・advanced-ds-catalog・graph-modeling | 案なし（文に合う節があれば） | reverse-index-signs | page |
| greedy-basics:133・interval-scheduling:122・cpp-math-functions:248・cpp-undefined-behavior:272・fix-variable:139・exchange-argument:103・binomial-identities:222（反例探し・ランダムテスト） | stress-testing | #procedure（全探索との比較の組み方なら #setups） | stress-testing | page |
| construction:154（チェッカー） | stress-testing | #caveats | stress-testing | page |
| counting-mindset:154・symmetry-pigeonhole-casework:87・127・grundy-number:163・proof-patterns:179（実験・OEIS） | stress-testing | #experiment | stress-testing | page |
| interactive:190 | stress-testing | #interactive | stress-testing | page |
| bit-operations:179・bitwise-independence:211（b1 handoff 348 行） | xor | #overview | xor | page |
| how-to-use（notation へ） | notation | ページへのまま（半開区間・添字・計算量の 3 つを指すので、執筆者が意図して残した） | how-to-use | page |
| cpp-reverse-index（debugging-checklist への前置き） | debugging-checklist | ページへのまま（点検の順全体を指すので、執筆者が意図して残した） | cpp-reverse-index | page |
| two-sat#acl を指すほかのページ | two-sat | anchor は変わらないが、title を「ACL では（two_sat の囲み）」から自作の要点と Library Checker を含む形に変えた。リンクの文字に影響があれば直す | two-sat | — |

### 1.2 執筆者がバッチの中で張り替え済みのもの（メインの作業は不要）

- debugging-checklist → atcoder-system#ranking、cpp-environment#stack-depth（2 か所）・#when-results-differ、cpp-reverse-index#symptoms、stress-testing#procedure
- cpp-reverse-index → cpp-environment の 3 か所（#version-matrix・#stack-depth・#when-results-differ と #options）
- practice-method → contest-strategy#after-contest・#time-targets、how-to-use#claude・#progress・#record-skill、atcoder-system#ai-rules
- method-comparison → reverse-index-signs#by-phrase・reverse-index-constraints#constraint-table・segment-tree-graph#cover・kth-and-median#overview・stress-testing#procedure・dp-speedup-overview#shape-to-tool・subsequence-and-substring#overview
- library-design → stress-testing#procedure、problem-sets#problem-sets-practice2（front matter の related の stress-testing・problem-sets#verify-sets は変えていない。related を stress-testing#procedure にするかはメイン）
- how-to-use → atcoder-system#difficulty・#contests
- atcoder-system → how-to-use#ai-rule-version
- stress-testing → thinking-checklist#q-small-cases
- subsequence-and-substring → interval#overview
- roadmap → problem-sets#recent-abc、atcoder-system#difficulty-by-position（図）
- parallel-binary-search → persistent-data-structures#prefix-versions、binary-search#meguru、partially-persistent-union-find・cdq-divide-and-conquer・wavelet-matrix の #what-it-does
- partizan-games → hadamard-transform#power（メインの判断で外してよい）
- thinking-checklist → stress-testing#experiment
- spanning-tree-advanced は advanced-ds-catalog が stub だったので #meldable-heap を付けなかった（§1.1 の行）

## 2. 内容の重なり（後から書く側が、先に書かれたページへリンクして短くする）

b1 の決定（other.md §1.6）のとおり、後から書く側が短くする。持ち主を決めてほしいものはメインが決める。

| ページ | 重なり | 申し送りを書いたページ |
| --- | --- | --- |
| rollback-union-find#offline-dynamic-connectivity ↔ offline-dynamic-connectivity | 手順の要点（区間を求める・セグ木に載せる・DFS で併合と取り消し・O(Q log Q log N)）と頂点加算の工夫が重なる。今は rollback-union-find に頂点加算の工夫（経路のすべての sum に足す）、offline-dynamic-connectivity に別の方法（加算を時刻 [t, Q) の操作としてセグ木に載せ、根の合計に足し引き）。持ち主を決める。あわせて rollback-union-find の「根だけに足すと取り消しで x が元の根に残る」は「葉で取り消さずに足す場合の話」と読めるよう言い方を見る（矛盾はしない） | rollback-union-find・offline-dynamic-connectivity |
| matrix-tree-theorem ↔ determinant | 法が素数でないときの行列式（互除法の掃き出し）は determinant#modulus が持ち主。matrix-tree-theorem の自作の要点をそちらへ寄せてもよい | matrix-tree-theorem・determinant |
| bottleneck-path#reconstruction-tree ↔ merge-process-tree | merge-process-tree は木の作り方・グループの区間・自作の要点を持ち、MST との関係と使い分けは bottleneck-path#reconstruction-tree に任せた（handoff-b2b3 §2 の分担どおり） | merge-process-tree |
| contest-strategy#difficulty-by-position ↔ atcoder-system#difficulty-by-position ↔ roadmap#recent-positions | 表の値（中央値・割合）と節が重なる。contest-strategy は「戦い方に使う数字」、atcoder-system は「定義と仕組み」と分けたつもり。値の持ち主を atcoder-system に決めるなら contest-strategy の節は結論の 3〜4 文とリンクに縮める（検証の指摘 8 を保留中） | contest-strategy・roadmap |
| contest-strategy#time-targets ↔ roadmap#targets | 到達の目安の数値（解く確率・解き終える時刻）。roadmap は持ち主を contest-strategy にして 3 行の要約とリンクにした。この分担を決める | roadmap |
| contest-strategy・atcoder-system・how-to-use の生成 AI のルール | how-to-use#ai-rule-version・atcoder-system#ai-rules・contest-strategy#ai-rules の表現をそろえる。AWC が対象かは未確認（how-to-use は「開催中は頼まない」） | contest-strategy・how-to-use |
| practice-method ↔ how-to-use#record-skill | `/record-problem` の流れが重なる。practice-method を要点とリンクにするか、持ち主を決める | practice-method |
| thinking-checklist ↔ contest-strategy#when-stuck | 5 段の手順と 8 段の問いの列は順序をそろえてある（誤読 → 制約 → 小さいケース → 言い換え → … → 一度離れる）。片方を直すときはもう片方も確かめる | thinking-checklist |
| kth-and-median ↔ kth-value | 図（1, 3, 3, 6, 8 の段の図）が同じ型。kth-and-median は中央値と同じ値での段の飛びを示す向きにした | kth-and-median |
| two-sat ↔ scc・bipartite-graph・acl-reading | b1 §2 の重なり（acl-reading:113・bipartite-graph:172・scc:189・scc:268）は two-sat 側を短くして scc#acl・scc#algorithms・bipartite-graph へリンクした（済み） | two-sat |
| graph-modeling#contraction | 次数 1・2 の頂点を消す縮約（V ≤ 2(E − V)）は持ち主のページがないので graph-modeling で短く説明した。ここを持ち主にするか degree-sqrt などへ移すか | graph-modeling |
| advanced-ds-catalog（析合木の代わりの手） | 最大値 − 最小値 −（右端 − 左端）の最小値と個数を遅延セグ木で持つ型に対応する節が教材にない。lazy-segment-tree-patterns に節を足すか | advanced-ds-catalog |
| mex#sum-of-mex ↔ lazy-segment-tree-patterns#reformulate | 全区間の mex の総和（ABC470 G）の持ち主は lazy-segment-tree-patterns。mex はリンクだけ（済み） | mex |
| continuous-probability#integral ↔ expectation-tail-sum#continuous | continuous-probability は式と最大値の例を繰り返さずリンクで済ませた（済み） | continuous-probability |

## 3. 記法の提案（notation が入れたもの・入れなかったもの・残りの決定）

notation の執筆者が b1 handoff §3・b2b3 handoff §3 の記法の提案を本文に入れた。入れたもの（パスカルの三角形 C[n][k]、AND・OR、擬似コードの |x|、val、ord[t]・out[v]、グリッドの (i, j)・di・dj、値の上限の文字、S^R、行列とベクトルの向き、余事象・条件付き確率、Iverson の記法、量の単位、ST(v)・EN(v)、V[X]、fail[v] と link(v)、∘）の一覧は notation の報告のとおり。手引き §6 への反映は style.md。

メインが決めること：

| 件 | 今の状態 | 提案したページ |
| --- | --- | --- |
| 値の上限の文字 | 手引き §6 は M を辺数にしているが、harmonic-sum・divisors-and-multiples は値の上限を M と書く。notation は「決まった文字を当てずページの冒頭で定める（辺の出てこないページでは M も）」と今の状態に合わせた。divisors-and-multiples は「1 つの数 N、値の上限 M」を整数論の案内の記法として提案 | notation・divisors-and-multiples |
| 行列とベクトルの向き | matrix-power は縦ベクトル（v' = Av）、segment-tree-monoids・dynamic-dp は横ベクトル（v ← vT、op(a, b) = ab）。どちらも互いの書き方と op の向きを本文で明記。notation は両方を書き「各ページの冒頭で示す」。dynamic-dp は横ベクトルにそろえたと報告し、§6 に「行列をセグ木に載せるページは横ベクトル・(p, q) は p → q・op(a, b) = ab」を足す案。木の上の動的 DP（値が深い方から浅い方へ流れ、HL 分解の番号は浅い方が小さい）では縦ベクトルの方が番号の順に積が並ぶので、static-top-tree と dynamic-dp#on-trees の書き方をそろえる | notation・dynamic-dp |
| 失敗リンクの記号 | string-automaton-dp は fail[v]、aho-corasick は link(v)。notation は同じものと書くだけ | notation |
| σ の重なり | 文字の種類の数 σ と約数の和 σ(n)。ページの冒頭の定義に従う | notation |
| 幾何の記法 | 偏角の範囲の既定 [0, 2π) と比較関数の名前（argument-sort）は notation に置かなかった。幾何のページが増えたら「幾何の記法」の節を足す案 | notation |
| popcount の書き方 | bit-operations の 39・140・196 行が `\mathrm{popcount}`、hadamard-transform・invariant は `\operatorname{popcount}`。notation は `\operatorname` にした。bit-operations を直す | notation |
| twelvefold-way の単射の列 | notation に Iverson の記法が入ったので、twelvefold-way の「n ≤ k なら 1」を $[n \le k]$ に直せる | twelvefold-way |
| (min,+)・(max,+) | 半角の `(min,+)` で書く（aliases の `'(max,+) 畳み込み'` と本文をそろえた）を §6 に | monge |

## 4. 逆引き（cpp-reverse-index）・早見表（cheatsheet）・debugging-checklist への追加

cheatsheet と cpp-reverse-index は b1 §4・b3 §4 の申し送りを反映した（cheatsheet：`<bit>` の表・INF の候補・doubling のメモリ・外積の最大 4×10^18・畳み込み／アダマール変換／ゼータ変換の行。cpp-reverse-index：lookup-types・compile-errors・symptoms の追加。std::function の倍率と println の速さは再現しない数値なので書いていない）。残りは cpp-environment が新しく確かめた事実：

| 追加先 | 内容 | 提案したページ |
| --- | --- | --- |
| cpp-io#tle-causes・debugging-checklist・cpp-reverse-index の「AtCoder でだけ TLE」 | `-ftrivial-auto-var-init=zero` で、関数の中の大きな局所配列が呼ぶたびに 0 で埋められて遅い（`int buf[100000];` の関数を 2×10^5 回呼ぶと 0.05 秒 → 1.03 秒、g++-13・g++-15、-O2）。持ち主は cpp-environment#auto-var-init | cpp-environment |
| cpp-reverse-index・早見表の症状の欄 | 「手元でだけ CE → -std の付け忘れ（既定は gnu++17）・g++-13」 | cpp-environment |
| geometry-precision | `-march=native` で FMA が使われ、平行な (0.1, 0.3) どうしの外積が 0 でなく 1.66533e-18 になった（-ffp-contract=off で 0）。持ち主は cpp-environment#march-native。ジャッジの CPU が FMA を持つかは未確認 | cpp-environment |
| tree-traversal・research の再帰の深さの記述 | 最小の再帰ラムダの DFS で -O2 は 2.2×10^5 まで、-O0 は 6.5×10^4 まで、std::function 版は 8×10^4 まで（ulimit -s 8192、g++-15）。「10^5 で落ちた」とは 1 段の大きさの違いで説明がつく（cpp-environment の本文は「数倍変わる」） | cpp-environment |
| cpp-undefined-behavior#out-of-range ほか | GCC 15 の -O0 で `_GLIBCXX_ASSERTIONS` が自動で定義される（-O1・-O2・-Og では定義されない）。b1 handoff §6 の件を確認。cpp-reverse-index は symptoms に「-O0 でだけ Assertion で止まる」の行を足した | cpp-environment・cpp-reverse-index |
| C++26 の構造化束縛を条件に使う書き方の記述があるページ | `if (auto [a, b] = pair{1, 2})` は -std=gnu++26 でも通らない（pair が bool に変換できない）。cpp-environment の表から外した | cpp-environment |
| generator を扱うページ | g++-15 の -O2 -Wall で -Wmismatched-new-delete の誤警告 | cpp-environment |
| cpp-reverse-index の compile-errors | `'typeof' was not declared` を足した（研究の §6.2 にあったもの）。cpp-environment#gnu-mode と照らす | cpp-reverse-index |
| 早見表と各ページの数値 | 早見表に値を書いたページ（complexity-estimation・divisor-count-bound・gcd-lcm・cpp-types-literals・cpp-math-functions・stl-containers・mod-arithmetic）を直すときは早見表の同じ行も直す（style.md にも） | cheatsheet |

## 5. 計測値・数値の不一致

| 件 | 内容 | 申し送りを書いたページ |
| --- | --- | --- |
| 調和級数の回数 | research 06 の「N = 2×10^5 で 2.56×10^6」は M·H_M（切り捨てなし）の値で、⌊M/d⌋ の和は 2472113。早見表は M = 10^6 の ⌊⌋ の和 13970034（約 1.4×10^7）だけを書いた | cheatsheet |
| 3^N の目安 | complexity-estimation#constraint-table の「3^N は N ≤ 15 程度」と reverse-index-constraints の「15〜16 程度」。矛盾はしないが、そろえるなら complexity-estimation 側を「15〜16 程度」に | reverse-index-constraints |
| 計算量の目安の数値 | reverse-index-constraints#magnitudes も complexity-estimation と同じ値（log₂(2×10^5) ≈ 17.6、N log N ≈ 3.5×10^6、N log² N ≈ 6.2×10^7、N√N ≈ 8.9×10^7） | reverse-index-constraints |
| cheatsheet ↔ reverse-index-constraints | 1 秒の目安と N = 2×10^5 の量を同じ値にそろえ、相互にリンクする | reverse-index-constraints |
| FPS の計算量の表 | fps-basics・generating-function-counting・cayley-pruefer#with-polynomials の計算量は一致している（確認済み） | fps-basics・generating-function-counting |
| Library Checker の counting_eulerian_circuits の制約 | potato167 の記事は「N ≤ 2×10^5、M ≤ 500」と書くが、info.toml では N ≤ 500、M ≤ 2×10^5。本文は info.toml に従った | matrix-tree-theorem |
| library-design の生成ブロックの表 | aho_corasick・minimum_enclosing_circle・minimum_steiner_tree・range_add_range_min・static_range_sum_with_upper_bound・sum_of_multiplicative_function の 6 問が categories.toml にない。judge.yosupo.jp で開けるかを各ページの verify の持ち主が確かめる | library-design |

## 6. 相手のページの直し（事実・表記・コード）

| ページ | 直すこと | 申し送りを書いたページ |
| --- | --- | --- |
| **permutation-parity#exactly-k**（125 行付近） | 「『最小回数以下か』と『偶奇が合うか』の両方を確かめる」は向きが逆で、「最小回数以上か」が正しい（事実の誤り） | permutation（検証の指摘 1 の参考） |
| balanced-bst:108・snippets/balanced-bst/implicit-treap.cpp 30〜36 行 | 「自分には反映済み」の説明と「push で自分の左右を入れ替える」コードが食い違う。dynamic-tree と同じく、印を立てるときに入れ替える（toggle）形にそろえる | dynamic-tree（検証役の参考の指摘） |
| stars-and-bars:161 | 「箱の順番を区別しないなら、分割数など別の数」を「玉も区別しないなら分割数、玉を区別するならスターリング数」に（twelvefold-way と食い違わない形） | twelvefold-way |
| cpp-io#float-output | 「大きな値は」：有効数字 6 桁では値が 1 程度でも相対誤差が 10^-6 を超えうる | reverse-index-signs |
| bit-operations:90 | 「n mod 4 だけで次のように決まる」は値そのものが 4 通りと読めるので「n mod 4 で場合分けした次の式で決まる」に | xor |
| mobius-function#quotient | 「杜教篩で O(N^{2/3})」に「N^{2/3} までを前計算すれば」の条件を添える（前計算なしは O(N^{3/4})） | multiplicative-function |
| gcd-lcm:166 | リンクの文字「Stern–Brocot 木」のエンダッシュを ASCII のハイフンに（§7） | stern-brocot |
| euler-phi | 「バーンサイドの補題」を「Burnside の補題」に（§1.1 の張り替えと一緒に） | burnside-lemma |
| sweep-line-2d | 「軸に平行な線分の交点を数える」節を足す（水平な線分の両端を +1・−1 のイベントにし、垂直な線分の y の区間の和を BIT で取る）。足したら advanced-geometry#segment-intersections のリンクを張り替える | advanced-geometry |
| zeta-mobius-subset・zeta-mobius-divisor・fps-basics・cpp-templates-constexpr（2 本）のコード片 | 補助関数 `print` が §9（std の名前と同じ関数名を作らない）に触れる（C++23 の std::print）。hadamard-transform は `print_vec` に改めた | hadamard-transform |
| lowlink.md の参考 | あめんばーど氏の記事の題名に h1 の「【AtCoder】」が抜けている（offline-dynamic-connectivity は h1 どおり） | offline-dynamic-connectivity |
| cpp-comparators#less-equal-pitfall | 見出し「同じ値が多いと Segmentation fault」だが、本文の表では落ちるのは要素 3.5×10^4 以上だけ。見出しを本文に合わせるか | cpp-reverse-index |
| cpp-undefined-behavior#uninitialized | debugging-checklist#local-vs-judge の「0 から始まって AC することがあり」と言い方をそろえるか | debugging-checklist |
| roadmap | Safari の記述にも「WebKit が 2020 年に発表した仕様」と時点を添える（how-to-use と同じに） | how-to-use |
| dp-basics・dp-prefix-sum・dp-segment-tree（「DP の高速化の全体像」）・matrix-power（「DP の高速化の一覧」） | リンクの文字を題名「DP の高速化の選び方」にそろえるか | dp-speedup-overview |
| priority-queue・cdq-divide-and-conquer | リンクの文字「発展的なデータ構造の一覧」を題名にそろえる（§1.1） | advanced-ds-catalog |
| complexity-estimation | §5 の 3^N の目安 | reverse-index-constraints |
| monotonic-stack | 台帳では abc189_c が practice だが、ページの練習に載っていない（ledger.md） | interval |
| bit-full-search | 台帳の abc197_c の practice の行がない（ledger.md） | xor |
| subsequence-dp・counting-dedup#leftmost | subsequence-and-substring の言い回し「直前に取った位置より右で最も左」とそろえるか | subsequence-and-substring |
| geometry 系のページ（§5 の注意） | 回転キャリパーは一直線上の点を除いた凸包で行う（convex-hull#degenerate の不等号の向きと関係する） | advanced-geometry（style.md にも） |
| static-top-tree ↔ dynamic-dp | dynamic-dp の Static Top Tree の説明（パスの圧縮と部分木の併合で高さ O(log N)、更新は O(log N) 回の合成）は研究資料に基づく。static-top-tree と食い違いがないか確かめる（static-top-tree は b4 で draft になった） | dynamic-dp |
