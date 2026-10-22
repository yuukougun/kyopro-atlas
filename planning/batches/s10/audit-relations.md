# 工程10 洗い出し：ページどうしの関係（s10）

調べ方：全 353 ページの front matter と本文（生成ブロックを除く）をスクリプト（`/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/ff4dc6ee-16d4-486c-b97a-49fefbe7b218/scratchpad/s10/` の `rel_load.py`・`check1.py`〜`check9.py`・`sec.py`）で調べ、判断の要るものは本文を読んで確かめた。

- check1・check2（front matter の前提と関連）：存在しない id・anchor、自分自身、重複、前提と related の重複、ページのレベルの逆転、前提の循環、推移的に冗長な前提、同じ分野の前提がナビゲーションで後ろ、前提が 5 つ以上、入ってくる道のないページ。**どれも 0 件**だった（前提の辺は 455 本）
- check3：要点の「前提」の行と prerequisites の食い違い。0 件（contest-strategy・thinking-checklist は「なし。〜は〜にある」の形で、食い違いではない）
- check5・check6：本文の「〜を前提にする」の文のリンクを、節の帯（sections の level）と比べた。節の帯より上のページを前提にしているものだけを「節のレベルの逆転」として下に挙げた。節ごとの追加の前提（style-guide §2.3「上位の帯の節は、最初に追加の前提をリンクで示す」）は、ほかに 180 件ほどあり、どれもページの前提にない。節の追加の前提として読めるので挙げていない
- check7 と組の表：本文で互いにリンクし合っているのに、どちらの related にもない組。handoff（b1 §2・b2b3 §2・b4b5 §2）の重なりの組 68 組の related と本文のリンクも表にした
- check8・check9：本文のリンクの文字を、相手の title・aliases・nav_title・sections の title・見出しと比べた（281 件が一致しない。多くは文の中の説明的な言い回しで問題ない）。そのうち、手法の名前として書かれていて相手の題名と違うもの、別のページの題名・別名と同じ文字なのに違うページへ張ったものを挙げた
- 重なりの組は、handoff の 3 つの §2 の「確かめる」「持ち主を決める」の項を中心に、両方のページの該当の節を読み比べた。食い違いのなかった組：crt ↔ ext-gcd（解の存在条件・一意性）、dp-dag ↔ shortest-path-dag、ternary-search ↔ circle-geometry、nim ↔ grundy-number（逆形）、bitset-speedup ↔ degree-sqrt（三角形の計算量）、divisor-inclusion-exclusion#period ↔ kmp（周期の議論）、optimal-strategy-expectation#guess-answer ↔ expectation-linear-equations#unknown（「広義に減少」にそろっている）、partition-number ↔ twelvefold-way・stars-and-bars（p(n,k) の定義）、dynamic-dp ↔ segment-tree-monoids（行列は横ベクトル v T の向きでそろっている）、steiner-subtree ↔ tree-edge-contribution（辺の条件）、tree-construction ↔ interval-dp-advanced（abc252_g の 2 種類の状態）、cayley-pruefer ↔ fps-basics（累乗の計算量）、zeta-mobius-subset ↔ subset-enumeration-dp（部分集合の畳み込み O(n² 2ⁿ)）、thinking-checklist ↔ contest-strategy#when-stuck（問いの順）、graph-modeling#contraction（V ≤ 2k の上界）、contest-strategy・atcoder-system・roadmap の数値（四分位・割合・逆転の回数は 3 ページで一致）、mod-inverse#rational ↔ rational-mod（分担が明確）、tree-imos#depth-limited ↔ root-path-dfs（届く数と最大の分担）

数：52 件（basics 2・thinking 1・dp 4・graph 7・geometry 2・tree 9・string 2・ds 7・cpp 1・math 3・comb 5・patterns 1・guide 4・start 2・shared 2。1 行に同じ種類の箇所をまとめたものがあり、直す箇所はリンクの文字だけで約 60 か所）。行の頭の【食い違い】は同じ事実の書き方が違うもの、【逆転】は節のレベルの逆転、【リンク】はリンクの文字・行き先、【関連】は related の欠け、【重なり】は持ち主が決まっていない重複。

## basics

- docs/basics/exchange-argument.md・L167・【食い違い】落とし穴に「`double` の比は誤差で同点になって同等の推移を壊す」「どちらも狭義の弱順序を壊す」とある。根拠：handoff-b2b3 §2 の 2 行目で、要素ごとに決まる `double` のキーの比較は推移的で、害は順の取り違え（誤答）だと決まり、exchange-argument-dp:116・:156 と sorting-techniques:130 はその形（「違う比が同じ値に丸められて順を取り違え、誤答になる」）に直っているが、こちらは直っていない（L107 の本文は正しい）。直し方：L167 を「`<=` は狭義の弱順序を壊して実行時に落ちることがあり、`double` の比は違う比が同じ値に丸められて順を取り違え、誤答になる」に分けて書き直す
- docs/basics/difference-sequence.md・L51〜55（と docs/basics/imos.md・L117）・【食い違い】同じ記号 $d_i$ の差分列を、difference-sequence は両端の外を 0 とした $d_0..d_N$ の $N+1$ 個（$0 \le i \le N$）、imos#adjacent-difference は内側の $d_1..d_{N-1}$（$1 \le i \le N-1$）と定めていて、端の扱い（「l = 0 では何もしない」と「d_0 を変える普通の 2 点の操作」）が逆になっている。根拠：handoff-b2b3 §2「定義をそろえる（style.md の §5 basics の提案）」が未対応。直し方：imos#adjacent-difference に「端の外を 0 とみなして $d_0, d_N$ まで取ると、端の区間も 2 点の操作になる（[差分列への言い換え](difference-sequence.md#to-point-operations)）」の 1 文を足し、記号を分ける（imos 側を「内側の隣接差」と呼ぶ）か、difference-sequence の定義にそろえる

## thinking

- docs/thinking/parity.md・L105・【リンク】文字「重み付き Union-Find」が union-find-applications へ張られている。根拠：「重み付き Union-Find」は docs/ds/weighted-union-find.md の題名で、union-find-applications:168 自身も「差を持つ型は重み付き Union-Find（weighted-union-find）で扱う」と送っている。直し方：行き先を `../ds/weighted-union-find.md` にする（偶奇は weighted-union-find の偶奇の節があれば節へ）。related に weighted-union-find があるかも確かめる

## dp

- docs/dp/dp-dag.md・L143・【逆転】基礎のページの、帯のない節 with-cycles の項目が「この項目は[強連結成分分解](../graph/scc.md)（水）を前提にする」としている。根拠：style-guide §2.3（節の level はページの level 以上、上位の帯の節は最初に追加の前提を示す）・design §3 の 7（前提に上のレベルを置かない）。直し方：この項目を scc#dp-on-dag へ送る 1 文に縮めるか、項目を find-dag と同じ水の帯の節に移す（sections の with-cycles に level: 水 を付けるのでもよい）
- docs/dp/subset-enumeration-dp.md・L152・【逆転】青のページの帯のない節 vs-zeta が「[高速ゼータ変換](../comb/zeta-mobius-subset.md)（黄）を前提にする」としている。根拠：同上。直し方：sections の vs-zeta に level: 黄 を付ける（節の中身はゼータ変換との比較なので黄の帯でよい）か、前提の文を外し、ゼータ変換を「部分集合の和を一度に求める変換」と 1 文で定義してから比べる
- docs/dp/interval-dp.md・L141、docs/dp/knapsack-01.md・L215、docs/dp/subset-sum.md・L110・【リンク】文字「交換論法で順序を決めてから DP」が exchange-argument-dp（題名「並べ替えてから DP する」、別名に「交換論法＋DP」）へ張られている。根拠：§7 の正規形（題名の書き方）・relink-plan（b5）の「リンクの文字を相手の題名にそろえる」と同じ種類。直し方：「[並べ替えてから DP する](../dp/exchange-argument-dp.md)」にする
- docs/dp/knapsack-undo.md・L219（DP の次元を減らす → dp-dimension-reduction「DP の状態の削減」）、docs/dp/digit-dp.md・L219 と docs/dp/digit-dp-advanced.md・L297（文字列の照合状態を持つ DP → string-automaton-dp「照合オートマトン上の DP」）・【リンク】手法の名前として書いたリンクの文字が相手の題名と違う。根拠：同上。直し方：相手の題名にそろえる

## misc

（このページ群には該当なし。bitset-speedup の related の欠けは graph の degree-sqrt の行にまとめた）

## graph

- docs/graph/bipartite-graph.md・L171・【食い違い】「最小カットで表せるのは『2 つが違うとコスト』の形で、『2 つが同じだとコスト』はそのままでは表せない」。根拠：project-selection:104・:184〜188（表せる項と表せない項）は、表せる項を劣モジュラの条件で定め、「片方だけ 1 のときの罰（向きのある罰）」や 1 変数の項も表せる、「違うと罰」はその和の 1 つ、としている。「表せるのは〜の形」は狭すぎる（handoff-b2b3 §2 の bipartite-graph:171 の行）。直し方：「最小カットで表せる 2 変数の項は、『片方だけ 1 のとき罰』の形とその和（『違うと罰』はその例）で、『同じだと罰』はそのままでは表せない（[表せる項と表せない項](../graph/project-selection.md#submodular)）」にする
- docs/graph/bipartite-matching.md・L157・L276、docs/graph/konig-theorem.md・L128・L244、docs/dp/lis.md・L203・【リンク】dilworth-path-cover へのリンクの文字が「Dilworth の定理・DAG の最小パス被覆」「Dilworth・最小パス被覆」「Dilworth の定理とパス被覆」で、題名「最小パス被覆と Hall の定理」と違う。Dilworth の定理そのものは lis#dilworth にあり、dilworth-path-cover は #antichain から LIS へ送っている。根拠：relink-plan（b5）「張り替えるときに文言も直すもの」の bipartite-matching:157（「Hall の結婚定理」に）が未対応で、同じ古い題名がほかに 4 か所ある。直し方：L157 は「[Hall の結婚定理](../graph/dilworth-path-cover.md#hall)」、ほかは「[最小パス被覆と Hall の定理](../graph/dilworth-path-cover.md#path-cover)」か「[DAG の最小パス被覆](…#path-cover)」にする
- docs/graph/difference-constraints.md・L219・【リンク】「グラフへの言い換え」→ graph-modeling（題名「グラフへの帰着」）。根拠：batches/b5/decisions.md の 6 か所の 1 つ（未対応）。直し方：「[グラフへの帰着](../graph/graph-modeling.md#constraints-to-edges)」にする
- docs/graph/euler-path.md・L230（b5 の記録では :221。行がずれた）・【リンク】「グラフの作り方」→ graph-modeling#contraction。根拠：b5 decisions の 6 か所の 1 つ（未対応）。直し方：「[グラフへの帰着](../graph/graph-modeling.md#contraction)」にする
- docs/graph/lowlink.md・L120・L254・【リンク】「オフラインの動的連結性」→ offline-dynamic-connectivity（題名「辺の追加と削除が混ざる連結性」、別名「オフライン動的連結性」）。docs/graph/matrix-tree-theorem.md・L112 の「ラベル付きグラフの数え上げ」→ counting-labeled-graphs（題名「連結なグラフの数え上げ」）も同じ。根拠：§7。直し方：題名にそろえる（lowlink は別名の「オフライン動的連結性」でもよい）
- docs/graph/degree-sqrt.md・L12 と docs/misc/bitset-speedup.md・L12・【関連】bitset-speedup:322 は degree-sqrt#triangles へ、degree-sqrt:235 は bitset-speedup へ送り合い、三角形の数え上げを分担しているが、bitset-speedup の related に degree-sqrt がない（degree-sqrt 側にはある）。根拠：handoff-b2b3 §2 の組。直し方：bitset-speedup の related に `degree-sqrt#triangles` を足す
- docs/graph/chromatic-number.md・L12 と docs/dp/subset-enumeration-dp.md・L12・【関連】互いに 2 か所ずつリンクし合う（彩色数の包除とゼータ、部分集合の列挙）が、どちらの related にもない。直し方：subset-enumeration-dp の related に `chromatic-number` を足す（chromatic-number 側にも subset-enumeration-dp）

## geometry

- docs/geometry/rotation-transform.md・L218・【リンク】「Z algorithm」→ z-algorithm。根拠：付録 A の正規形は「Z-algorithm」（題名も同じ）。直し方：「[Z-algorithm](../string/z-algorithm.md)」にする
- docs/geometry/manhattan-chebyshev.md・L250・【リンク】「最小全域木の応用」→ spanning-tree-advanced#manhattan（題名「特殊な最小全域木」）。docs/math/determinant.md・L131 の「最小全域木の発展」も同じ。直し方：「[特殊な最小全域木](../graph/spanning-tree-advanced.md#manhattan)」にそろえる

## tree

- docs/tree/small-to-large.md・L179・【逆転】黄の帯の節 dsu-on-tree が「[重い子と軽い辺](../tree/hld.md#heavy-light)（hld は発展）」を前提にしている。根拠：style-guide §2.3・design §3 の 7。直し方：節の帯を発展にするか、「重い子＝部分木の頂点数が最大の子」を節の中で 1〜2 文で定義し、hld へのリンクは参照にとどめる（前提の文から外す）
- docs/tree/tree-centroid.md・L92・【食い違い】「木の同型判定のように重心を根にして形を比べるとき」とあるが、docs/tree/tree-isomorphism.md・L96〜103 は根に**中心**（tree-diameter#center）を使い、2 個のときの扱いも中心について書いている（参考の ei1333 だけが重心を根にする）。根拠：handoff-b2b3 §2「重心が 2 個のときの扱いを同型判定のページを書くときにそろえる」。直し方：tree-centroid:92 を「根のない木の同型判定では、中心か重心を根にする（[木の同型判定](../tree/tree-isomorphism.md)は中心を使う）。どちらも 2 個のときは両方を試すか、辺の真ん中に仮の頂点を足す」にする。あわせて tree-isomorphism に「重心を使っても同じ」と 1 文足すとよい
- docs/tree/tree-isomorphism.md・L12 と docs/tree/tree-centroid.md・L12・【関連】上の重なり（2 個のときの扱い）があり、本文で 1 か所ずつリンクし合うが、どちらの related にもない。直し方：tree-isomorphism の related に `tree-centroid#one-or-two`、tree-centroid の related に `tree-isomorphism` を足す
- docs/tree/tree-edge-contribution.md・L131・【関連】「黒い頂点をすべて含む最小の連結な部分（以下『黒を結ぶ木』と呼ぶ）」と独自の呼び名で定義しているが、これは steiner-subtree（指定頂点を結ぶ最小の部分木）の対象そのもので、辺の条件（両側に黒がある）も steiner-subtree:65 の $1 \le c \le K-1$ と同じ。steiner-subtree:113 は tree-edge-contribution#edge-pairs へ送っているのに、逆向きのリンクも related もない。根拠：handoff b1 §2 の steiner-subtree ↔ tree-edge-contribution の組。直し方：L131 の定義に「[指定頂点を結ぶ最小の部分木](../tree/steiner-subtree.md)」へのリンクを足し、両方の related に相手を足す
- docs/tree/tree-imos.md・L12 と docs/tree/root-path-dfs.md・L12・【関連】「根から y 世代までに及ぶ効果」を、tree-imos#depth-limited は最大値で、root-path-dfs（L128〜134 の「祖先から何世代下まで届くか」）は個数で扱い、本文で送り合っているが、どちらの related にもない。根拠：handoff b1 §2 の tree-imos ↔ root-path-dfs の組。直し方：tree-imos の related に `root-path-dfs#path-statistics`、root-path-dfs の related に `tree-imos#depth-limited` を足す
- docs/tree/root-path-dfs.md・L12 と docs/comb/minimax.md・L12・【関連】minimax#tree（黄の帯）は「この節は木 DP と根からのパスを DFS で持ち回るを前提にする」（L150）で、abc218_g も両方の練習・力試しにあるが、どちらの related にもない。根拠：handoff-b2b3 §2 の root-path-dfs ↔ minimax の行。直し方：minimax の related に `root-path-dfs`、root-path-dfs の related に `minimax#tree` を足す
- docs/tree/tree-construction.md・L12・【関連】L102 と力試しの abc252_g で interval-dp-advanced#dfs-order-trees へ送っているが related にない（interval-dp-advanced 側にも tree-construction がない）。根拠：handoff b1 §2 の組。直し方：tree-construction の related に `interval-dp-advanced#dfs-order-trees` を足す
- docs/tree/tree-construction.md・L124・L190（「次数と木」→ tree-degree「木の次数列と Prüfer 列」）、docs/tree/tree-degree.md・L160・L165 と docs/comb/counting-bijection.md・L126・docs/comb/counting-labeled-graphs.md・L283（「ラベル付き木の数と Prüfer 列」→ cayley-pruefer「ラベル付き木の数え上げ」）、docs/tree/tree-distance.md・L83（「木の二部グラフ性」→ tree-bipartite「木の 2 色塗り分けと距離の偶奇」）、docs/tree/tree-centroid.md・L98・L224（「辺ごとの寄与」→ tree-edge-contribution「辺で切って数える」）・【リンク】手法の名前として書いた文字が相手の題名と違う。根拠：§7。直し方：相手の題名にそろえる（文の流れで言い換えたいときは節へのリンクにして、節の見出しの言葉を使う）
- docs/tree/dynamic-tree.md・L12・【関連】本文で euler-tour へ 4 か所リンクし（ETT の説明・部分木が区間になる理由・使い分けの表）、ETT はオイラーツアーの列そのものを持つ構造だが、prerequisites・related のどちらにもない。直し方：related に `euler-tour#in-out` を足す

## string

- docs/string/string-automaton-dp.md・L111〜125・L205 と docs/string/aho-corasick.md・L128〜140・L191・【重なり】「終端の印を失敗リンク先から受け継ぐ」を、同じ例（パターン bc と abcd）と同じ落とし穴で両方のページが全部説明している。記号も string-automaton-dp は $\mathrm{out}$、aho-corasick は `term` で違う。根拠：handoff-b2b3 §2「持ち主を 1 つに決め、ほかはリンク」が未決。直し方：持ち主を aho-corasick#inherit-terminal に決め、string-automaton-dp#multiple-patterns は「パターンを含んだ状態は終端だけでない」の 1 段落と DP の状態の話に縮めてリンクする（記号はどちらかにそろえる）。snippets/string-automaton-dp/aho-dp.cpp:build の持ち主も同時に決める
- docs/string/kmp.md・L12 と docs/comb/divisor-inclusion-exclusion.md・L12・【関連】kmp#count-periodic は「約数包除（#period）を前提にする」（L175）、divisor-inclusion-exclusion#period は「メビウスの書き方は KMP の節にある」（L150）と送り合っているが、どちらの related にもない。根拠：handoff-b2b3 §2 の組。直し方：kmp の related に `divisor-inclusion-exclusion#period`、divisor-inclusion-exclusion の related に `kmp#count-periodic` を足す

## ds

- docs/ds/priority-queue.md・L196、docs/ds/cdq-divide-and-conquer.md・L119・【リンク】「発展的なデータ構造の一覧」→ advanced-ds-catalog（題名「見慣れないデータ構造の名前と用途」）。根拠：b5 decisions の 6 か所のうち 2 か所（未対応）。直し方：「[見慣れないデータ構造の名前と用途](../ds/advanced-ds-catalog.md#meldable-heap)」（cdq は #table）にする
- docs/ds/mo-algorithm.md・L4・L44・【食い違い】別名に「クエリ平方分割」があるが、docs/ds/sqrt-decomposition.md は別名「クエリの平方分割」と節 #query-buckets で別の方法（かたまりごとに作り直す）をその名で呼び、L142 で「Mo's algorithm もクエリを平方分割する方法と呼ばれることがあるが別物」と書いている。用語の索引で 1 つの語が 2 ページに分かれる。根拠：handoff-b2b3 §2（aliases から外す提案。other.md）が未対応。直し方：mo-algorithm の aliases と別名の行から「クエリ平方分割」を外す（索引・用語集も作り直す）
- docs/ds/rollback-union-find.md・L66〜76 と docs/tree/root-path-dfs.md・L151〜161・【重なり】経路圧縮をしない理由（戻せない・ならしが崩れる・union by size で O(log N)・記録 2 件）を両方のページが同じ分量で説明している。書き方も「変わるのは par[s] と r の大きさだけ」（root-path-dfs:155）と「書き換わるのは根 2 つの par だけ」（rollback-union-find:74。大きさを根の par に負で持つ表し方の前提）で違う。根拠：handoff-b2b3 §2 の root-path-dfs ↔ rollback-union-find（後から書いた側が短くする）。直し方：持ち主を rollback-union-find#no-path-compression にし、root-path-dfs の節は「記録は 2 件・経路圧縮はしない（理由はリンク先）」の 2〜3 文に縮める。記録する 2 つの値の言い方をそろえる
- docs/ds/rollback-union-find.md・L102 と docs/graph/offline-dynamic-connectivity.md・【重なり】オフライン動的連結性の手順と、頂点への加算の扱いが両方にあり、方法が違う（rollback-union-find は経路のすべての sum に足す、offline-dynamic-connectivity は加算を時刻 [t, Q) の操作としてセグ木に載せる）。計算量も O(Q log Q log N) と O(N + Q log Q log N) で書き方が違う。根拠：handoff-b4b5 §2 の 1 行目（持ち主を決める）が未決。直し方：持ち主を offline-dynamic-connectivity に決め、rollback-union-find の節は手順の要点 3 行とリンクに縮める。2 つの加算の方法を両方残すなら持ち主のページに並べる
- docs/ds/union-find-applications.md・L203、docs/ds/union-find.md・L137・L202、docs/ds/partially-persistent-union-find.md・L114・【リンク】「Undo 可能（な）Union-Find」→ rollback-union-find（題名「ロールバックできる Union-Find」、別名は「Undo つき Union-Find」）。根拠：§7。直し方：「[ロールバックできる Union-Find](…)」にそろえる
- docs/ds/merge-sort-tree.md・L146、docs/ds/segment-tree-on-values.md・L265（「オフラインのクエリ処理」→ offline-queries「クエリの先読み」）、docs/ds/offline-queries.md・L136・docs/ds/parallel-binary-search.md・L116（「Union-Find と連結性」→「Union-Find で連結性を扱う」）、docs/ds/binary-trie.md・L258（「K 番目の要素」→ kth-element「K 番目の値を求めるデータ構造」）・【リンク】手法の名前として書いた文字が相手の題名と違う。根拠：§7（付録 A の正規形は「オフライン」を全体の語として持つが、ページの題名は「クエリの先読み」）。直し方：相手の題名にそろえる
- docs/ds/merge-sort-tree.md・L12 と docs/ds/sqrt-decomposition.md・L12・【関連】互いに 2 か所ずつリンクし合う（区間の x 以上の個数の使い分け）が、どちらの related にもない。docs/basics/divide-and-conquer.md・L12 と docs/ds/sparse-table.md・L12（3 か所と 2 か所）も同じ。直し方：それぞれの related に相手を足す

## cpp

- docs/cpp/cpp-environment.md・L12・【関連】本文で cpp-views-cpp23 へ 4 か所リンクする（版ごとの対応の説明）が related にない。docs/cpp/cpp-undefined-behavior.md は prerequisites に cpp-environment（level が null）を置いている一方、ほかの cpp の基礎のページは cpp-environment を前提にしていない。根拠：design §3（入ってくる道・前提の網）。直し方：cpp-environment の related に `cpp-views-cpp23` を足す。cpp-undefined-behavior の前提が cpp-environment でよいか（level null のページを前提にするとロードマップの列で位置が決まらない）を決める

## math

- docs/math/spf-sieve.md・L103・【逆転】青の帯の節 linear-sieve が「[オイラーの φ 関数](../math/euler-phi.md#formula)（黄）と[メビウス関数](../comb/mobius-function.md#definition)（黄）の定義を前提にする」。根拠：style-guide §2.3・design §3 の 7。直し方：φ と μ の定義（乗法的で、素数冪での値が $p^{e-1}(p-1)$・$-1$ か 0）を節の中で 1〜2 行で書き、リンクは参照にする。あるいは節を黄の帯にする
- docs/math/euler-phi.md・L153・【リンク】「バーンサイドの補題」→ burnside-lemma#necklace。根拠：b5 decisions の 6 か所の 1 つ（未対応）、付録 A の正規形は「Burnside の補題」。直し方：「[Burnside の補題](../comb/burnside-lemma.md#necklace)」にする
- docs/math/gaussian-elimination.md・L154・L264（「期待値の連立方程式」→ expectation-linear-equations「閉路のある期待値」）、docs/math/modint.md・L101・L138（「有理数を mod で表す」→ rational-mod「確率・期待値を mod 998244353 で答える」）、docs/math/mod-pow.md・L179（「数え上げの基本」→ counting-basics「和・積の法則と順列・組合せ」）、docs/math/matrix-power.md・L159・L316（「文字列の照合の DP」→ string-automaton-dp「照合オートマトン上の DP」）、docs/math/integer-root.md・L158 と docs/math/gcd-properties.md・L123・L205（「約数の包除原理」「約数の包除」→ divisor-inclusion-exclusion「約数包除」）・【リンク】手法の名前として書いた文字が相手の題名と違う。根拠：§7・付録 A（約数包除）。直し方：相手の題名にそろえる

## comb

- docs/comb/counting-labeled-graphs.md・L54・【リンク】文字「余事象」が counting-mindset へ張られている。根拠：「余事象」は docs/thinking/complement.md の題名で、counting-mindset には余事象の節がない（sections は procedure・formula-or-dp・exactly-vs-at-most・contribution-with-binomial・verify-small）。直し方：行き先を `../thinking/complement.md` にする
- docs/comb/twelvefold-way.md・L191・docs/comb/stars-and-bars.md・L211 と docs/comb/partition-number.md・L305・docs/comb/bell-number.md・L231・【食い違い】同じ記事（qiita.com/drken/items/f2ea4b58b0d21621bd51）の題名を、前の 2 ページは「「写像12相」を総整理！ 〜 数え上げ問題の学びの宝庫 〜」、後の 2 ページは「よくある「写像12相」を総整理！ 〜…」と書いている。根拠：§14-24（題名は記事の h1）。直し方：記事の h1 を確かめて 4 ページをそろえる（同じ URL で題名の違う出典は全体で 124 件ある。shared の行）
- docs/comb/zeta-mobius-subset.md・L272、docs/comb/binomial-precompute.md・L292、docs/dp/subset-enumeration-dp.md・L229・【リンク】「ラベル付きグラフの数え上げ」→ counting-labeled-graphs（題名「連結なグラフの数え上げ」）。graph の matrix-tree-theorem:112 と同じ。直し方：題名にそろえる
- docs/comb/continuous-probability.md・L60・docs/comb/expectation-of-square.md・L193（「有理数を mod で表す」→ rational-mod）、docs/comb/reflection-principle.md・L290（「LGV の補題」→「LGV 補題」）、docs/comb/zeta-mobius-divisor.md・L61（「素因数の指数のベクトル」→ prime-exponent-vector「素因数の指数で考える」）、docs/dp/insertion-dp.md・L154（「包除原理の DP」→「包除 DP」）・【リンク】手法の名前として書いた文字が相手の題名と違う。直し方：相手の題名にそろえる
- docs/comb/game-retrograde-analysis.md・L12 と docs/comb/minimax.md・L12・【関連】互いに 2 か所ずつリンクし合う（後退解析とミニマックスの使い分け）が、どちらの related にもない。docs/comb/zeta-mobius-subset.md・L12 と docs/math/convolution-ntt.md・L12（XOR・OR 畳み込みと NTT の比較で 2 か所ずつ）、docs/comb/counting-basics.md・L12 → inclusion-exclusion（3 か所）、docs/comb/cayley-pruefer.md・L12 → fps-basics（累乗の計算。fps-basics 側には cayley-pruefer がある）も同じ。直し方：それぞれの related に相手を足す

## patterns

- docs/patterns/mex.md・L11・【関連】mex#sum-of-mex は「全区間の mex の総和の持ち主は lazy-segment-tree-patterns#reformulate」として 3 か所リンクしているが、related には lazy-segment-tree（遅延セグ木の本体）だけで、持ち主の lazy-segment-tree-patterns がない。根拠：handoff-b4b5 §2 の mex ↔ lazy-segment-tree-patterns の行。直し方：mex の related の `lazy-segment-tree` を `lazy-segment-tree-patterns#reformulate` に替える（または足す）。あわせて、pattern のページのうち xor・bracket-sequence だけが prerequisites（bit-operations・prefix-sum）と要点の「前提」の行を持ち、ほかの 8 ページ（divisors-and-multiples・grid・interval・kth-and-median・mex・operation-sequence・permutation・subsequence-and-substring）は持たない。hub も twelvefold-way・dp-speedup-overview・graph-modeling は前提を持ち、advanced-ds-catalog は持たない。どちらにそろえるかを §16 に足す

## guide

- docs/guide/contest-strategy.md・L44〜66 と docs/start/atcoder-system.md・L153〜179・【重なり】位置ごとの difficulty の表（四分位・中央値）と帯の割合・逆転の回数を、両方のページが同じ値で全部載せている（値は一致）。根拠：handoff-b4b5 §2（値の持ち主を atcoder-system に決めるなら contest-strategy は結論の 3〜4 文とリンクに縮める。検証の指摘 8 を保留中）。直し方：持ち主を atcoder-system に決め、contest-strategy#difficulty-by-position は「E は水、F は青、G は黄以上」と教材のレベルへの読み替え（L58〜63）だけを残し、表はリンクにする。データを足し直すときに片方だけ直す事故を防ぐ
- docs/guide/contest-strategy.md・L203〜217、docs/start/atcoder-system.md・L221〜241、docs/start/how-to-use.md・L322〜337・【重なり】AtCoder生成AI対策ルール（20261014 版）の要約の段落が 3 ページにほぼ同じ文で載っている。ADT・AWC も同じ扱いにすることは how-to-use にだけあり、contest-strategy・atcoder-system の「この教材との関係」の箇条書きにはない。参照も contest-strategy:216 → atcoder-system（版の扱い）、atcoder-system:240 → how-to-use（教材が前提にする版）、how-to-use:336 → contest-strategy（コンテスト中のふるまい）と一巡している。根拠：handoff-b4b5 §2「表現をそろえる。AWC が対象かは未確認」。直し方：ルールの要約と版の履歴の持ち主を atcoder-system#ai-rules、教材の約束（ADT・AWC を含む）の持ち主を how-to-use#ai-rule-version に決め、contest-strategy は「コンテスト中は頼まない・終了後は頼んでよい」の 2 行とリンクにする。版が変わったときに直す場所を 2 か所にする
- docs/guide/debugging-checklist.md・L210・【リンク】参考の行のリンクの文字がページの id のまま（`[cpp-undefined-behavior]`・`[complexity-estimation]`・`[cpp-io]`）。根拠：ほかのページは相手の題名を文字にしている（§7）。直し方：「[未定義動作とダングリング]」「[計算量の見積もり]」「[入出力と定数倍]」にする
- docs/guide/roadmap.md・L113・L137・L163（生成ブロック）・【食い違い】見出しが「E 問題（水の帯）」「F 問題（青の帯）」「G 問題（黄の帯）」だが、atcoder-system:172・contest-strategy:61 は G の 49% が発展（2400〜）で黄は 38% としている（contest-strategy:46 も「G が黄以上」）。直し方：生成スクリプトの見出しを「G 問題（黄・発展の帯）」か「黄以上」にする（tools/gen_site.py。メインが流す）

## start

- docs/start/how-to-use.md・L11 と docs/guide/contest-strategy.md・L12・【関連】生成 AI のルールで互いに 2 か所・1 か所リンクし合う（how-to-use#claude・#ai-rule-version ↔ contest-strategy#ai-rules）が、どちらの related にもない（how-to-use は atcoder-system を related に持つ）。根拠：handoff-b4b5 §2 の 3 ページの組。直し方：上の guide の重なりを決めた後、how-to-use の related に `contest-strategy#ai-rules`、contest-strategy の related に `how-to-use#ai-rule-version` を足す（持ち主を決めた向きだけでもよい）
- docs/start/notation.md・L172・【リンク】文字「分数を mod で表す」は rational-mod の別名と同じだが、行き先は mod-inverse#rational。根拠：check9（別のページの別名と同じ文字で違うページへ張ったもの）。文脈（逆元で割れる理由）は mod-inverse#rational で合っている。直し方：文字を節の見出しに寄せて「[有理数 P/Q を P × Q^(−1) で表す計算](../math/mod-inverse.md#rational)」か「分数を逆元で表す計算」にする

## shared

- tools/gen_site.py（生成物 docs/guide/roadmap.md・L158）・【食い違い】最近の ABC の位置ごとの表で、「連結性・全域木 | 1 | [最小全域木]（2） | abc469_f」と、問題は 1 問なのにページの回数が 2 になっている。根拠：data/recent-abc.yaml の abc469_f の pages が `minimum-spanning-tree#reduce-candidates` と `minimum-spanning-tree#maximum` で、同じページの 2 つの anchor を 2 回と数えている。表の説明（L139「かっこの数は、その位置でそのページを使った問題の数」）と合わない。直し方：生成スクリプトで pages を `id` に落として問題ごとに重複を除いてから数える。ほかの行に同じ数え方の誤りがないことは表全体で確かめた（この 1 行だけ）
- docs 全体（出典の行）・【食い違い】同じ URL の出典を、ページによって違う題名で書いているものが 124 件ある（例：drken の ABC246 G の記事を「AtCoder ABC 246 G - Game on Tree 3 (3D, 黄色, 600 点)」と「ABC246 G - Game on Tree 3」、ikatakos の abc464 を「…F,G問題メモ」と「ikatakos の競プロ Wiki「ABC464」」）。根拠：§14-24（題名は記事の h1）・§16-15（題名は原文のまま）。一覧は `/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/ff4dc6ee-16d4-486c-b97a-49fefbe7b218/scratchpad/s10/cite_titles.txt`。直し方：出典の観点の担当と合わせ、URL ごとに h1 を 1 つに決めてそろえる（check_pages に「同じ URL で題名が違う」の警告を足すとよい）
