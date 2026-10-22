# b2・b3 の手引き・prh.yml・checklists への提案

出どころは b2・b3 の各 `<id>.md` の「手引きへの提案」「prh.yml への提案」と追記。「ページ数」は同じ趣旨を出したページの数。道具（check_pages・render_svg・gen_site）そのものの直しは other.md §3 にも置いた。

## 1. 食い違い・決めてほしいこと（複数のページから）

| 要旨 | ページ数 | 出したページ |
| --- | --- | --- |
| **§13-5・§7「用語集へのリンクはまだない anchor で書いてよい」と check_pages（用語集にない anchor をエラーにする）が食い違う**。執筆者はリンクを外して本文で定義し、用語集の提案に回した。案：(a) 手引きを「提案中の語はリンクせず提案に書く。足した後でメインが張る」に直す、(b) check_pages を警告に下げる。b1 の決定には入っていない | 15 | binomial-identities・convolution-ntt・degree-sqrt・dp-dimension-reduction・graph-construction・grundy-number・parsing・randomized・root-path-dfs・segment-tree-monoids・sparse-table・bipartite-matching・centroid-decomposition・lowlink・min-cut（ほかに gaussian-elimination も同じ理由でリンクを外したと用語集の提案に書いた） |
| **§14-25「箇条書きは句点で終える」と、見本 lazy-segment-tree・同じ分野の draft（tree-dp など）・参考の節の書き方が食い違う**。§14 が見本に優先するので規則は決まっているが、見本と既存の draft をそろえるか、要点の囲み・参考・使い分けの箇条書きを例外にするかを決める | 6 | sqrt-decomposition・tree-dp-square・min-cost-flow（ほかの draft の揺れ）・inclusion-exclusion-dp（#comparison の箇条書き）・game-retrograde-analysis（参考の節は付けない）・bottleneck-path（要点の囲みと参考は見本どおり付けない） |
| **§14-4（ACL は見出しを立てず囲み）と、骨格の sections に `ACL では… {#acl}` が残るページ**。max-flow・min-cost-flow は中身の節「ACL の mf_graph で書く {#acl}」にして囲みを中に置いた（topological-sort・scc にならう）。認めるか。認めないなら #algorithms の末尾の囲みに移し anchor acl を残す | 2 | max-flow・min-cost-flow |
| **§14-2 の対象を広げるか**：sections の `which-tool`（dp-segment-tree）・`when-to-use`（inclusion-exclusion）は中身が使い分けそのもの。anchor を変えない規則に従い残した。comparison にそろえるなら sections から外し、見出しを `## 使い分け {#comparison}` にして確認問題の後へ移し、docs/index/ の行を gen_site で作り直す | 2 | dp-segment-tree・inclusion-exclusion |
| **練習を Library Checker で補うページ・練習の問題が台帳に 1 問もないページの書き方**：`## 練習問題 {#practice}` に judge.yosupo.jp へのふつうのリンクの箇条書き（問題の囲みは atcoder.jp 専用）を置いてよいか。置かないなら本文のどこに書くか | 3 | lowlink・euler-path・complement-graph-bfs |
| **evidence が ikatakos.com だけの問題は、サイトが落ちると（2026-10-21 は 503）裏付けが取れない**。evidence を 2 つ持つ／代わりに読んだ第三者の解説を参考に載せ台帳への追加を提案する、を §10・§11 に書く | 3（503 の報告は 30 ページ以上） | expectation-linear-equations・zeta-mobius-divisor・expectation-tail-sum |
| **執筆の指示文を level ごとに分ける**：「基礎のページは短く、応用の型・落とし穴・上位の手法とのつながりに絞る」が黄のページにも付いていた。§14-6 のとおり level で構成を決めた（定型の next-steps は置かず other-fields の節で兼ねた） | 2 | divide-and-conquer・xor-basis |

## 2. 手引きの節ごとの提案

### §2・§14-12（見出し）

- 見出しと sections の title に `{` `}` `|`（`Σ_{d|n}` など）を書かない。attr_list の `{#anchor}` と紛れる（hash-safety が報告した hashing-for-sets#random-values の見出しの波かっこで anchor が拾えない件と同じ原因の可能性）。catalog の title にこの形が残るページもあるかもしれない（euler-phi）
- §14-12 を骨格の段階で当てる：長い sections の title（lazy-segment-tree-patterns の design-steps は 56 字。案「設計の手順と載せられる 3 つの条件」）（lazy-segment-tree-patterns）
- §13-2 への添え書き：骨格の sections の title の文字が本文で決めた記法（式の数 n・変数の数 m）と食い違うとき、数学のページでは title を本文の記法にそろえて直してよい（gaussian-elimination）

### §3（確認問題）

- §14-11（`## 確認問題 {#quiz}` にまとめる）と §3（要所に置く）の関係が分かりにくい。§3 を「要所に置かず quiz の節にまとめる」に直す（permutation-parity）。※ §14 が §3 に優先するので扱いは決まっている。文言の直しだけ

### §5 分野ごとの書き方

**basics**

- 交換論法で導いた比較は $t_i w_j < t_j w_i$ の掛け算の形のまま書く。(0, 0) を除き、符号が混じるならグループに分ける。持ち主は exchange-argument#ratios（exchange-argument）
- 最小回数・可否の問題では差分列を両端の外まで N + 1 個取る（端の場合分けがなくなる）。imos#adjacent-difference との定義のそろえ（difference-sequence）

**dp**

- 1 本の配列で書き換えてよいかの規則の例に、インライン DP の「その行で読む値を先にすべて集めてから書き込む」を足す（ABC372 F・ABC203 E）（inline-dp）
- 数え上げの区間 DP は、1 つの対象がただ 1 つの分け方に対応するもの（左端の相手など）で分ける（最小化では重複が害にならない）（interval-dp）
- 戻す DP のような削除の更新は追加と逆向きにループを回す（0-1 は追加が大きい方から・削除が小さい方から、個数制限なしは逆）（knapsack-undo、任意）
- プロファイル DP のように状態が盤の上の位置を表すときは、bit k がどのマスを表すかを図と 1 文で示す（broken-profile-dp）
- 下の桁から決める桁 DP で上限のフラグを持つときは「ここまでの下の桁だけを比べて上限より大きいか」を持ち、上の桁で上限と異なる数字を置いたら上書きする（digit-dp-advanced）
- 異なる部分列（種類）を数える DP では、空文字列を含めるかを入力 1 文字の場合で確かめる（dp[0] = 1 が空文字列）（subsequence-dp）
- 二乗の木 DP の計算量は添字の範囲が部分木のサイズに比例するときだけ成り立つ（配列を長さ N で取らない・サイズの更新はマージの後）（tree-dp-square）

**comb（数え上げ・確率・ゲーム）**

- 「範囲外を 0 とする約束だけでは空の組を落とす」例に ABC290 F の N = 2（C(N−3, k−1) が C(−1, −1)）を足す（binomial-identities）
- 対応づけの検算は、対応 f と逆向き g を小さい場合の全列挙で assert する形を勧める（counting-mindset#verify-small と役割が近い。持ち主を決める）（counting-bijection）
- 約数包除の向き（倍数から引くなら大きい順、約数から引くなら小さい順）と、空集合・1 のようにすべての F に入る対象を除くこと（divisor-inclusion-exclusion）
- 連結なものを全体から引くときは、頂点 1 を含む成分の外を「全体」の数で掛ける（連結なものの数で掛けると成分がちょうど 2 つのものしか引かれない）（counting-labeled-graphs）
- 包除の和を DP にするときは符号を値に掛けて運び、偶奇を状態に持たない（|S| ごとに別の係数が掛かる場合だけ個数を状態に持つ）（inclusion-exclusion-dp）
- メビウス関数の篩は符号の反転を p の倍数すべて（p 自身を含む）に行い、0 にするのだけを p^2 の倍数にする（mobius-function）
- ゼータ変換は和なら戻せるが、max・min（上位 k 個）で累積したものは戻せない。約数・部分集合の 2 ページ共通の落とし穴として持ち主を決める（zeta-mobius-subset）
- 鏡像法は折り返す線を「触れたら違反の線」にし、終点・始点が条件を破る場合を先に 0 で返す（reflection-principle）
- 分割数の p(n,k) は資料によって定義が違う（部分が k 以下・ちょうど k 個・0 を含めて k 個）。ページの中で 1 つに決め小さい値で確かめる（partition-number）
- 閉路のある期待値は、戻る先の状態を (0, 1)、終状態を (0, 0) とする a + bX の組で書く。b = 1（終わらない）は値ではなく到達可能性で判定する（expectation-linear-equations）
- 答えを仮定して二分探索するときは、戦略を固定すると f(y) が y の 1 次式で傾きが 1 未満になる（f(y) − y が単調）ことを根拠に書く（optimal-strategy-expectation）
- 最適な行動が値の比較なしに入力の性質だけで決まると示せるなら mod のまま計算できる（例 abc412_f）を、mod で比較できない話の避け方の 2 つ目として足す（optimal-strategy-expectation）
- 確率を掛けた形（E[X・1{状態}]）で運ぶと合流で足すだけで済む（確率 DP・期待値 DP 共通。probability-dp の forward の節と表記をそろえる）（expectation-of-square）
- 閉路のあるゲームでは「未確定の局面の行き先に未確定の局面が必ずある」ことが引き分けの根拠になる（game-retrograde-analysis）

**graph**

- 負閉路のあるページ（bellman-ford・warshall-floyd・difference-constraints）は、負閉路の有無ではなく答えを聞かれた頂点が影響を受けるかで判定する、届かない頂点（INF）からは緩和しない（bellman-ford）
- 差分制約の最小化は向きを逆にした最短距離の符号反転（x_t − x_s の最小 ＝ −dist(t→s)）と書くか。bellman-ford#longest-path と表現をそろえる（difference-constraints、任意）
- 補グラフの探索は未訪問の集合を走査して「残す」回数を元の辺に、「取り出す」回数を頂点に割り当てて O(N + M) を示す（linked-list・ordered-set の rows-and-columns と言い方をそろえる）（complement-graph-bfs）
- フロー：作ったグラフで「解 → 流れ」「整数の流れ → 解」の両向きが言えることを書く（max-flow）
- フロー：最大の最小化を二分探索するときは答えが組のコストのどれかに等しいので、候補をソートして添字で二分探索する（実数の二分探索を避ける。abc401_g）（bipartite-matching）
- 最小費用流の「定数 − 利得」で非負に直すときは、どの 1 単位の流れも定数を足した辺をちょうど 1 回通る層に置く（燃やす埋める・二部マッチングと言い回しをそろえる）（min-cost-flow）
- カットの容量は S から T へ向かう辺だけを数える。復元は残余グラフで s から届く集合で行い、飽和した辺をカットとして出力しない（min-cut）
- 燃やす埋めるの約束は s 側＝選ぶ（x = 1）にそろえる（min-cut・konig-theorem・two-sat・bipartite-graph で向きが混ざらないように）（project-selection）

**tree**

- パス上の判定に距離の式 d(u,x) + d(x,v) = d(u,v) を使うときは重みのない距離（深さ）で行う（重み 0 の辺で誤判定する）。持ち主は tree-path#pitfalls（tree-path）
- 「Prüfer 列の全単射は証明の筋を図で示す」について、全単射の証明は図ではなく折りたたみの文章で書いた（生成の図で出現回数 = 次数 − 1 の筋は示した）。この形を認めるか（tree-degree）

**string**

- Aho-Corasick 法・KMP 法のオートマトンを DP に使うときは、ならしの O(1) が効かないので遷移表を埋める。終端の印は失敗リンク先から受け継ぐ（out[v] |= out[fail[v]]）ことを必ず書く。持ち主は aho-corasick#inherit-terminal か string-automaton-dp#multiple-patterns（matrix-power の dp-transition にも同じ注意）（aho-corasick・string-automaton-dp）
- 値そのものの mod（巨大な整数）は基数がないので法の素数を乱択する。持ち主は hash-safety#what-to-randomize（hash-safety）

**math・geometry・misc**

- 離散対数（BSGS）で最小の解を返すときは表の同じ値に大きい j を残す（x = in − j の形）。x = 0 と「正の最小」を区別する（multiplicative-order）
- 2 乗の比較は 0 以上の量どうしのときだけ大小を保つ（circle-geometry）
- 凸多角形は頂点を反時計回り・一直線に並ぶ 3 頂点なしで持つ（`<= 0` の凸包で作り直す）と約束すると、内外判定・面積・Pick の定理の書き方がそろう（convex-hull）
- bitset の「1/64 になる根拠を書く」に、次数が 1 つ違う問題は救えないこと（目安の表）とメモリ N²/8 バイトの見積もりを足す（bitset-speedup）
- ds：「(位置, 値) の組を枠として先に全部集める」の言い回しをそろえる（offline-queries#compress・persistent-data-structures）（merge-sort-tree）

### §6 記法

記法は b1 の E1 のとおり start/notation を書くときにまとめる（handoff.md §3 に控えた）。手引きに直接足す案として出たもの：

- 分散 $V[X]$ を $P(A)$・$E[X]$ と並べる（expectation-of-square）
- 木の記法に長さ 2N の列の位置 $\mathrm{ST}(v)$・$\mathrm{EN}(v)$（mo-algorithm）
- Iverson の記法 $[P]$（mobius-function）
- 行列をセグメント木に載せる向き（横ベクトル・op(a, b) = ab と matrix-power の縦ベクトル）（segment-tree-monoids）
- 問題に合わせた二項演算を一般に書く記号（∘）（subset-enumeration-dp）

### §8 図・表

- 横に 2 つ並べた SVG（幅 760 程度）は 360px で文字が 6px ほどになる。並べたい図は 2 枚に分ける（1 枚の幅は 400 程度まで）（bottleneck-path。b2・b3 の検証でも図の 360px の文字の指摘が多数）
- SVG に viewBox と同じ width・height を付けるか（render_svg の 720px で下が切れる件。convex-hull は 3 枚に付けた。サイト全体のそろえ方を決める）（convex-hull）
- 表の列は 4〜5 までの決まりで、値の一覧（μ(1..12) など）は表にできない。一覧は数式の 1 行で書いてよいと明記する（mobius-function）

### §9 コード片

- `using namespace std;` の下で `relation`・`sort` など std の名前と同じ関数名を作ると、C++20 以降は `std::relation`（概念）などとぶつかる（g++-15 で確認）。関数名は `circle_relation` のように具体的にする（circle-geometry）
- 非再帰の DFS で親（DFS 木）が要るときは、（頂点, 親）の組を積み、取り出したときに印と親を決める（「積むときに印を付ける」は DFS 木を作らない）。今の「v と ~v を積む形にそろえる」への例外として添える（graph-construction）
- 型の別名は使わない規則により Miller-Rabin の `u64` も `unsigned long long` に書き直した。長い宣言が続く数論のコード片を例外にするか（hash-safety）
- 法 10^12・10^13 の積が 2^63 を超える問題の `__int128` の mulmod は持ち主のページ（miller-rabin#mulmod か mod-pow）に置き、ほかはリンクする（multiplicative-order）
- 短い補助の関数をラムダで書くのが「ラムダは比較関数・DFS・判定の関数など」の「など」に入るか（centroid-decomposition は検証の指摘 6 (b) を採らずラムダのまま）（centroid-decomposition）

### §10 問題の載せ方

- contest id を大文字にしただけの表示名（YAHOO-PROCON2019-QUAL D. Ears など）を本文でどう呼ぶか。台帳の表示名を「みんなのプロコン 2019」にする案もある（ledger.md）（dp-phase）
- Library Checker の問題へのリンクを本文に置いてよいかの決まり（complement-graph-bfs。§1 の練習の書き方と同じ件）
- 状態数を手元の列挙で数えた値を本文に書くとき「手元の列挙で数えた値」と添える書き方でよいか（broken-profile-dp）
- frequency_evidence の「古い ABC 2 問」の文言をメインで確かめる（inclusion-exclusion-dp）

### §14 に足す道具の注意

- Python で `open(p, 'w').write(... + open(別のファイル).read())` と書くと、後者が見つからないときに先にページが空になる（zeta-mobius-subset は git から骨格を戻した）（zeta-mobius-subset）

## 3. prh.yml

- 「エイホ・コラシック」「エイホ–コラシック」「Aho–Corasick」（en dash）→「Aho-Corasick 法」（aho-corasick）

## 4. 付録 A（用語の正規形）

| 足す語 | 出したページ |
| --- | --- |
| 第 2 種スターリング数・第 1 種スターリング数（スターリング数と並べる。ページの題名に使う） | bell-number |
| ハミング距離・ワイルドカード・指示関数 | convolution-ntt |
| 偶置換・奇置換・恒等置換（今は巡回分解だけ） | permutation-parity |
| モンテカルロ法・ラスベガス法・Color Coding・Boyer-Moore の投票（見出しで使う） | randomized |
| 最大独立集合・最小頂点被覆・最小辺被覆・マッチング・交互路・残余グラフ | konig-theorem |
| 「平面走査」の別の書き方として「走査線」を本文で使ってよいとする | sweep-line-2d |

## 5. 付録 B（確かめたドメイン）

b1 の決定（報告で確かめたとあるドメインを、noai を確かめ直してから足す）に従う。報告で確かめたとあるもの：

- noshi91.github.io・note.com の anoconne/n/n26b5912e1e9c（aho-corasick）
- cirrostratus.hatenablog.com（binomial-identities の検証役）
- yamate11.github.io（difference-constraints）
- inamori.hateblo.jp（knapsack-undo・inline-dp。check_noai で指定なし）
- w.atwiki.jp（指定なしだが Cloudflare で本文を取得できず未使用）・imoz.jp（difference-sequence）
- web.archive.org を足すかの判断（partition-number。ikatakos が保守中のとき写しを使った）
- GitHub の個人の解説リポジトリ（WineChord/algo など）は問題文を英訳して載せていることがある。ikatakos と同じく「問題文の節を読まない・使わない、解法の部分だけを参照」の扱いを書く（zeta-mobius-divisor）

確認の記述がないまま evidence に使われたドメインの一覧は ledger.md §4。

## 6. checklists

checklists への直接の提案はなかった。検証の指摘で繰り返し出た型（図の 360px での文字の大きさ、箇条書きの句点、確認問題が本文の文をそのまま問う、練習の答えが本文で見える、summary と要点の「何ができるか」の不一致）は、checklists の観点に足す候補になる（メインの判断）。

## 7. 解決済み（b1 の決定・手引き §14 で扱いが決まっているもの）

| 提案・迷った点 | 決まり | ページ |
| --- | --- | --- |
| catalog の sections に残る choosing・comparison・pitfalls を本文でどうするか | §14-1・§14-2 のとおり定型の `## 使い分け {#comparison}`・`## 落とし穴 {#pitfalls}` にした（catalog は凍結なので変更不要） | binary-trie・dp-phase・merge-sort-tree・string-automaton-dp・dp-segment-tree・aho-corasick |
| 骨格の sections に pitfall-* の anchor がありほかから指されているとき | §14-1 の趣旨どおり、`## 落とし穴` の下に同じ anchor の `###` を立てて残した。扱いをそろえる一文を §14-1 に添える案（counting-dedup） | counting-dedup |
| basics の field で level が黄のページの構成 | §14-6（level と type で決める）。next-steps は sections の節で兼ねてよい（§14-3 は主に基礎のページ） | divide-and-conquer・xor-basis |
| 箇条書きの句点 | §14-25（句点で終える）。§14 は見本に優先する。残るのは見本・既存ページのそろえ（§1） | sqrt-decomposition・tree-dp-square ほか |
| 確認問題の置き場 | §14-11（quiz にまとめる）が §3 に優先する（§2 の文言の直しだけ残る） | permutation-parity |
| title のカンマ | §14-13（引用符で囲む）。骨格の生成（gen_site）に当てる件は道具の直しとして other.md §3 | bell-number |
| stub のページへのリンク | §14-23（anchor を付けずにページへ。相手が draft になったらメインが張り替える）。各ページの申し送りは handoff.md §1 | 多数 |
| 台帳の summary が表記・事実で合わないとき | §14-15・§14-16（本文の行を先に直す／`- ID：自分の要約`）。直しの提案は ledger.md | circle-geometry・counting-dedup・lazy-segment-tree-patterns・knapsack-undo・difference-sequence など |
| 画像だけの解説の裏付け | §14-17（同じリポジトリの解答コードで確かめる）。evidence に sol/*.cpp を足す提案は ledger.md | dp-segment-tree・interval-dp・subset-enumeration-dp・broken-profile-dp |
| 「歩道」 | §14-22（ウォーク）。台帳の abc286_g の summary を直す（ledger.md） | euler-path |
| 記法の提案 | b1 の工程の決定（E1 は start/notation を書くときにまとめる）。handoff.md §3 | mo-algorithm・expectation-of-square・mobius-function・segment-tree-monoids・subset-enumeration-dp・string-automaton-dp |
| 動く図の置き場と仕様 | §14-21（div の config は仮でよく、仕様は報告に書く。JS は頼まれたときだけ）。作るものの判断は other.md | max-flow・dp-segment-tree・gaussian-elimination・tree-degree・convex-hull |
| 付録 B に足すドメイン | b1 の付録 B の決定（確かめ直してから足す）。一覧は §5 | 上記 |
