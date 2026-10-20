# 設計の見直し 03：目次（catalog）のデータの質と分野をまたぐ一貫性

工程4（設計の見直し）の3本目。目次（[../catalog/](../catalog/)、15分野・367ページ）のデータを、項目ごとの質と、分野をまたぐ一貫性の観点で批判的に点検した。目次は変更していない。

- 日付：2026-10-21（commit 8cf737f の作業ツリー）
- 読んだもの：design.md（特に §3〜§6）、catalog/README.md、catalog の全 yaml（各ファイルの open_issues 108件を含む）、research/*.topics.yaml と research/00 §2.3.8、`tools/check_catalog.py` と `tools/ap.py`
- 方法：catalog を読み込むスクリプトで全367ページを機械的に集計し、出てきた候補を目で確かめた。difficulty・出題日はすべて `tools/ap.py` のデータ（AtCoder Problems）。スクリプトは一時ファイル置き場（`/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/ff4dc6ee-16d4-486c-b97a-49fefbe7b218/scratchpad/review-3/`、セッション限り）に置き、リポジトリには入れていない。atcoder.jp・codeforces.com は開いていない
- 見直し 01（学習者の観点、[01-learner.md](01-learner.md)）と同じ事実に触れる指摘には「01 指摘n」と添えた。対応を決めるときの突き合わせに使ってほしい
- 限界：問題が何を問うかは、問題文を読まずに catalog と調査の記載で判断した。用語の「段」はレベルの順（基礎 → 水 → 青 → 黄 → 発展）の差を表す

## まとめ

| 重さ | 件数 | 番号 |
| --- | ---: | --- |
| 重大 | 3 | 1〜3 |
| 中 | 15 | 4〜18 |
| 軽 | 14 | 19〜32 |

検証スクリプトが見る形式（id・前提の解決・循環・レベルの逆転・kind の語彙・問題の実在・調査の key の処理）は全件そろっており、`level_evidence` に書いた difficulty の数値も 1299 組すべて `tools/ap.py` と一致した。問題は形式ではなく、スクリプトが見ない次の4つにある。

1. **分野をまたぐ意味の重複**：同じ手法のページが2つある組が3つ（指摘1〜3）、同じ節・同じ例題・同じ別名を持つ部分的な重なりが10組（指摘5〜8）ある。どれも別々の調査の key から来ており、README §6 の「同じ key の重複」の表にも検証スクリプトにも引っかからない。別名の衝突（81組）と例題の共有（45問）が機械的な手がかりになる
2. **前提とレベルの付け方のぶれ**：dp-order → dp-dag の1本の辺で DP・確率・ゲームの13ページの祖先にグラフの3ページが入る（指摘4）。「ACL を呼ぶだけ」の問題の扱い（指摘12）、横断・入口のページの type・level・frequency（指摘11）、基礎のページに置いた黄の節（指摘14）が分野ごとに違う
3. **problems の量と使い方**：練習が目安に足りないページが75（黄は44ページ中28）（指摘10）、例題の共有（指摘17）、要約に解き方が混ざる（指摘16）、「最初の例題＝代表問題」と「易しい順」の衝突（指摘15）
4. **生成に使う項目の不統一**：動く図の割り当てが設計の目安の約3倍（指摘18）、`related` が調査の key のまま（指摘21）、`verify` が ds だけ（指摘31）、題名・id・別名の表記ゆれ（指摘22〜24）

---

## 第1部　機械的な点検の結果

### 1.1 問題がなかった点（以降の指摘の前提として）

| 点検 | 結果 |
| --- | --- |
| `python3 tools/check_catalog.py` | エラー0・警告0・処理されていない調査の key 0 |
| 問題 ID の実在 | 延べ 1501 件（異なる 1158 問）がすべて実在。出どころは ABC 912 問（79%）・ARC 72・典型90 66・EDPC 26・AGC 23・TDPC 15・ACL Practice 13・鉄則本 12・ほか 19 |
| `level_evidence` の数値 | 「問題 ID と difficulty」の組 1299 組がすべて `tools/ap.py` の値と一致（差 5 以内） |
| 調査で裏付けがない問題 | 調査で `tag`・`unverified` とだけされた問題を使うページは 0（同じ問題がほかの調査で裏付けられている）。topics.yaml にない問題（延べ65件・異なる59問）は、すべて調査レポートの本文にある（43問は research/00 §2.3.8 の表） |
| 問題の並び | 役割の中で difficulty が 100 以上逆転する例は 0。例題 → 練習 → 力試しの順を崩すページも 0 |
| 前提の形 | 前提の数は最大4（README §3-4 の目安内）、前提のレベルの逆転 0、overview 以外のページが overview を前提にする例 0 |
| 文体 | summary に です・ます 0 |

### 1.2 観点ごとの結果

#### 意味の重複

| 点検 | 件数 | 代表例 | 指摘 |
| --- | ---: | --- | --- |
| 同じ手法のページ（要約・代表問題・別名が同じ） | 3組 | dp-convolution と online-convolution（例題 abc213_h が両方）、counting-dedup と dp-counting-dedup（abc310_d）、matrix-power と dp-matrix-power（dp_r） | 1〜3 |
| 部分的な重なり（同じ節・同じ例題・同じ別名） | 10組 | state-space-search と extended-dijkstra、sigma-manipulation と contribution（abc172_d の要約がほぼ同文） | 5〜8 |
| 同じ別名（または題名）を持つページの組 | 81組 | 「BIT DP」（dp-segment-tree）と bit-dp の「bitDP」、「ベル数」が recursive-enumeration と bell-number | 付録 I・指摘22 |
| 2ページ以上で例題にしている問題 | 45問 | abc310_d は6ページにあり、うち5ページで例題 | 付録 C・指摘17 |
| 設計書 §4.2・§4.3 の置き場所と食い違う | 3件 | reachability-bitset（§4.2 は bitset を misc に）、dilworth-path-cover の題名（§4.2 は Dilworth を LIS の節に）、状態を頂点にするページが2つ（§4.3 は1ページ） | 5・9 |
| §4.2 が求める相手側からのリンクがない | 3件 | ds → cht、basics → parallel-binary-search、tree → functional-graph | 9 |

#### 前提関係

| 点検 | 件数 | 代表例 | 指摘 |
| --- | ---: | --- | --- |
| 辺の数 | 前提 526・関連 1840 | 1ページの前提の数：0 が 52、1 が 138、2 が 147、3 が 26、4 が 4 | — |
| 入次数（前提にされる数）の上位 | — | dp-basics 20、bfs 15、dfs 15、bit-operations 14、prefix-sum 14、tree-traversal 14、sorting-techniques 13、segment-tree 13 | — |
| 前提の連鎖の深さ | 最大 9 | partizan-games（9）・grundy-number（8、青）。どちらも complexity-estimation → graph-basics → dfs → topological-sort → dp-dag → dp-order → game-basics … を通る | 4 |
| 祖先に topological-sort が入る graph・tree 以外のページ | 14 | interval-dp・expected-value-dp・game-basics・grundy-number など（原因は dp-order → dp-dag の1本） | 4 |
| 推移的に冗長な前提（A → B と A → C → … → B の両方） | 48 | lazy-segment-tree → segment-tree（segment-tree-monoids 経由で届く） | 付録 D・指摘20 |
| 同じ分野でナビゲーションの後ろにある前提 | 12 | bit-full-search（全探索の章）→ bit-operations（最後の章） | 付録 E・指摘19 |
| 前提にも関連にもどこからも張られていないページ | 4 | complement-graph-bfs、k-shortest-paths、tree-ratio-greedy、stern-brocot | 20 |
| 前提と関連の両方に同じページ | 6 | dp-matrix-power（matrix-power）、bit-dp（bit-full-search） | 20 |
| 調査の key のまま書いた前提・関連 | 145（うち前提2） | lexicographic-greedy.related の kth-combination → binomial-coefficient に解決され、節の行き先が失われる | 21 |
| id に解決すると関連に同じページが2回以上出る | 21 | grid の related に bfs・parity が2回、manhattan-chebyshev が3回 | 付録 L・指摘21 |
| 手作業で見つけた前提の抜け・不要な前提 | 抜け3・不要3 | steiner-tree に subset-enumeration-dp がない、palindrome → bfs は不要 | 20 |

#### レベル

| 点検 | 件数 | 代表例 | 指摘 |
| --- | ---: | --- | --- |
| 例題がすべてページの帯の外 | 35 | ternary-search（水）の例題は abc279_d（766）だけ。hash-safety（水）の例題は 1716 と ★7 | 付録 B-1・13 |
| `level_evidence` の問題がどれもページの帯に入らない | 14 | difference-sequence（水）：323・1027・1892・2163・2169 | 付録 B-2・13 |
| 最初の例題（§5.3 の代表問題）がページの帯から2段以上離れる | 10 | inclusion-exclusion（青）の最初の例題は abc131_c（518） | 15 |
| ページのレベルより2段以上高い印の節 | 73 | 基礎のページで 22 節、うち黄・発展が 9 節（knapsack-01 の「区間の品物だけのナップサック（黄）」など） | 付録 F・14 |
| ページより低い印の節 | 17 | string-automaton-dp（青）の「簡易版（水）」 | 32 |
| 設計書を根拠に挙げているが、設計書にその決定がない | 1 | lowlink：「設計書 §4.3 で黄」だが §4.3 の表に lowlink はない | 13 |
| 「ACL を呼ぶだけ」の問題を帯の根拠に数えるかが分野で違う | 6ページ | scc（水）・convolution-ntt（青）は数え、lazy-segment-tree（青）は水の3問を数えない | 12 |

#### 問題（problems）

| 点検 | 件数 | 代表例 | 指摘 |
| --- | ---: | --- | --- |
| 例題0（overview・pattern を除く） | 2 | dp-speedup-overview、shortest-path-overview | 11 |
| 基礎で例題2以上 | 8 | うち6は thinking（設計書 §4.1-7 は例題2〜4）。technique は bit-full-search・coupon-collector | — |
| 練習が2未満 | 75 | 基礎10・水18・青19・黄28。練習0は30（黄18） | 付録 A・10 |
| 問題が2問以下の technique・thinking | 35 | 黄16（complement-graph-bfs・xor-path・euler-path・lowlink・long-path-decomposition・fft-string-matching は1問） | 10 |
| 問題が11問以上 | 7 | manhattan-chebyshev（12）、extended-dijkstra・union-find-applications・interactive（11）、patterns の3ページ（11） | 17 |
| 2ページ以上・3ページ以上で使う問題 | 282問・52問 | abc127_f・abc202_d・abc141_e・abc359_g・abc330_e・abc241_d は4ページ | 付録 C・17 |
| patterns の問題がほかのページにもある | 77問中69 | うち36問はほかのページの例題 | 17 |
| 問題の6割以上が2019年以前 | 18 | dp-basics（4/5）、prime-factorization（5/7）、string-basics（4/5） | 付録 J・28 |
| 2023-09（7問体制）以降の問題が1つもない（3問以上のページ） | 63 | dp-prefix-sum（8問）、rotation-transform（8問）、matrix-power（7問） | 付録 J・28 |
| ARC・AGC が3割以上（2問以上） | 13 | game-mirror-strategy（6問中5）、lucas-theorem（2問中2） | 28 |
| 要約が手法名だけ・仮のもの | 47 | imos の abc462_d「いもす法で解く最近の D（00 §2.3.8 の分類。内容は執筆時に確かめる）」 | 付録 K・16 |
| 要約に解き方（手法名・「〜で数える」など）が入る | 例題 49%・練習 49%・力試し 59% | ordered-set の abc370_d「…行ごと・列ごとの set から探して両方から消す」 | 16 |

#### summary・signs・aliases

| 点検 | 件数 | 代表例 | 指摘 |
| --- | ---: | --- | --- |
| summary が3文以上（設計は1〜2文） | 21 | binary-search・kth-value・imos・scc・merge-sort-tree | 26 |
| summary が160字を超える | 15 | うち12は cpp（acl-reading 227字） | 26 |
| summary の中心がページの説明（「〜をまとめる」「〜の入口のページ」「〜の概要」） | 約12 | graph-modeling「…型を集めた入口のページ」、tree-construction「…型をまとめる」 | 26 |
| summary に「このページ」「ここで」「ここに」 | 8 | dijkstra「…応用もここで扱う」、palindrome「…このページで扱う」 | 26 |
| signs に constraint が1つもない（technique・thinking・overview） | 322中174 | tree 27中24、comb 51中33、graph 52中34、thinking 9中9 | 27 |
| constraint なのに数・不等号がない | 3 | segtree-on-values「前の答えで次の入力が決まり…（オンライン強制）」 | 27 |
| sign に手法名が入る | 約6 | palindrome「…N ≤ 10^6 なら Manacher」、lazy-segment-tree「…（双対セグ木）」 | 27 |
| 英字の表記（英語名・略称）が題名にも別名にもない | 49 | coordinate-compression、ternary-search、connected-components、min-cut、mobius-function | 付録 H・23 |
| 題名と同じ別名 | 5 | inclusion-exclusion・min-cost-flow・centroid-decomposition・determinant・stirling-first | 22 |

#### kind・frequency・chapter

| 点検 | 件数 | 代表例 | 指摘 |
| --- | ---: | --- | --- |
| kind が語彙外・4個以上 | 0 | — | — |
| kind の意味に合わない使い方 | 6 | complexity-estimation・harmonic-sum・divisor-count-bound に「全探索」、notation（start）に「整数論」 | 25 |
| frequency A のページで、problems と level_evidence に abc400 以降の問題がない | 87中50 | 最近の問題の平均は A 0.71・B 0.59・C 0.15 で、A と B の差が小さい | 29（01 指摘7） |
| overview（発展）なのに frequency B | 6 | 同じ手法の dp-convolution は C、online-convolution は B | 1・29 |
| 1ページだけの章 | 3 | basics「方針を立てる」「尺取り法」、graph「経路の種類」 | 30 |
| 「発展」の章の扱いが分野で違う | — | tree・comb は発展の章を持つが、hld・auxiliary-tree・continuous-probability などは話題の章にある。ds「発展的なデータ構造」に青の technique が3ページ | 30 |

#### title・id

| 点検 | 件数 | 代表例 | 指摘 |
| --- | ---: | --- | --- |
| 全角英数・全角空白 | 0 | — | — |
| かっこの補足つきの題名 | 367中217 | cpp は20中18 | 24 |
| 30字以上の題名 | 35 | うち16は cpp。最長は「C++23 の views と ranges::to（enumerate・zip・pairwise・chunk_by）」59字 | 24 |
| 「セグ木」と「セグメント木」の混在 | 11題名 | segment-tree「セグメント木（…）」、segtree-binary-search「セグ木上の二分探索（…）」 | 24 |
| 「K 番目」と「k 番目」の混在 | — | kth-value「K 番目の値」、kth-element「k 番目の値を求めるデータ構造」 | 24 |
| 人名の連結の記号 | ハイフン1・エンダッシュ5 | monge「Knuth-Yao」と aho-corasick「Aho–Corasick」・grundy-number「Sprague–Grundy」 | 24 |
| 数字と和文の間の空白 | あり12・なし7 | 「2 次元累積和」と「45度回転」「木の2色塗り分け」「写像12相」 | 24 |
| id の「segtree」と「segment-tree」の混在 | 9 id | segtree-on-values・segtree-binary-search・lazy-segtree-patterns と segment-tree-monoids・segment-tree-beats | 24 |

#### そのほかの項目

| 点検 | 件数 | 代表例 | 指摘 |
| --- | ---: | --- | --- |
| `visual` に動く図（ステップ送り）を割り当てたページ | 80（部品の共有を除いて約75） | dp 19・math 11・graph 10・cpp 7。設計書 §8.5 の目安は合計20〜30 | 付録 G・18 |
| `verify` を持つページ | 24（すべて ds） | `acl` を持つ70ページのうち `verify` があるのは9。math・dp の overview 12ページは sections の文中に Library Checker の問題名を書く | 31 |

---

## 第2部　指摘

重さの順に並べた。重さの基準：**重大**は、同じ手法のページが2つあるなど判断の余地なく誤っており、直さないまま工程8a（骨格）に進むとページとリンクを作り直すことになるもの。**中**は、直すべきだが統合か書き分けかなどの判断が要るもの、または生成物・執筆の多くのページに効くもの。**軽**は、局所的な不整合や表記で、工程6〜8b の中で直せるもの。

### 1. dp-convolution と online-convolution が同じ手法の2ページになっている

- **重さ**：重大（01 指摘4と同じ事実）
- **場所**：dp/dp-convolution（overview・発展・C）、math/online-convolution（overview・発展・B）
- **問題**：分割統治 FFT（オンライン畳み込み）を2つのページが持ち、互いに「相手のページへ」と案内し合う。辞書として引くと同じ名前で2ページが出て、知識マップにも同じ手法の点が2つできる。同じ手法なのに frequency が C と B で食い違う
- **根拠**：
  - 別名：両方に「分割統治 FFT」「オンライン畳み込み」
  - summary：dp-convolution「dp の値が自分より前の値との畳み込みで決まる（オンライン）なら、分割統治 FFT で O(N log^2 N) にする」、online-convolution「dp[i] が dp[0..i−1] と既知の列の畳み込みで決まるとき、分割統治で左から順に決めていく方法」
  - 例題：abc213_h（2806）が両方の例題
  - online-convolution の節「DP の高速化としての位置づけ（DP の章へ）」と dp-convolution の related の online-convolution が循環している
  - 由来：02 の key dp-convolution と 06 の key online-convolution。key が違うので README §6 の表に載らなかった
- **提案**：持ち主を math にする（設計書 §4.2 の「畳み込みは math」に合わせる）。
  - dp-convolution のページを削除し、key `dp-convolution` を online-convolution の `merged_keys` に入れる（dp.yaml の `moved` に `{key: dp-convolution, to: math}`）
  - online-convolution の `kind` を `[畳み込み・多項式, DP, ダブリング・分割統治]` にして DP の一覧に出す。frequency は B にそろえる
  - dp-convolution の節「遷移を多項式の積とみる」は、dp-speedup-overview の節（遷移の形 → 道具の表の1行）に移し、dp-speedup-overview の `related` に online-convolution・fps-basics を足す

### 2. counting-dedup と dp-counting-dedup が同じ内容の2ページになっている

- **重さ**：重大（01 指摘4と同じ事実）
- **場所**：comb/counting-dedup（青・B）、dp/dp-counting-dedup（青・B）
- **問題**：「代表元を1つ決めて代表だけを数える」という同じ考え方を、同じ節・同じ例題・同じ別名で2ページが書く。執筆と検証が二重になり、説明が食い違う恐れがある
- **根拠**：
  - summary：counting-dedup「重複度がばらばらなら代表元（正規形）を1つ決めて代表元だけを数える」、dp-counting-dedup「作り方に「代表」を1つ決めて代表だけを数える」
  - 節：両方に「最も左を取る（部分列）」と「番号最小の要素を含むグループから決める（グループ分け）」
  - 別名：両方に「ダブルカウントを防ぐ」「最小添字規則」
  - 例題：abc310_d（1368）が両方の例題。sign の文「区別しないグループに分ける方法の数」も両方にある
  - 由来：07 の key counting-dedup と 02 の key dp-counting-dedup
- **提案**：持ち主を comb/counting-dedup にする（数え方の考え方の章。DP 以外の割り算・Burnside も含む上位の概念）。
  - dp-counting-dedup を削除し、key を counting-dedup の `merged_keys` に入れる（dp.yaml の `moved`）
  - counting-dedup の `kind` を `[数え上げ, DP, 考察]` にする。sections に「DP の中で代表を決める（直前と違う・最初に〜で場合分け）」「落とし穴：グループの順序を区別して K! 倍に数える」を移す
  - 練習に abc130_e（1676）・abc311_f（1984）、力試しに abc180_f（2419）を移す（練習が1問しかない counting-dedup の不足も埋まる）
  - subsequence-dp の `prerequisites` の dp-counting-dedup を counting-dedup に、dp-state-design・lcs・subset-enumeration-dp・insertion-dp・inclusion-exclusion-dp の `related` も直す（`merged_keys` で解決はされるが、id で書き直すと重複（指摘21）が出ない）

### 3. matrix-power と dp-matrix-power の中身がほぼ同じで、代表問題も同じ

- **重さ**：重大（01 指摘4・5と同じ事実）
- **場所**：math/matrix-power（黄・B）、dp/dp-matrix-power（黄・B）
- **問題**：math の open_issues [3] は「math は道具、dp は DP の遷移を行列にする状態設計」と分けたと書くが、データはその分担になっていない。要約・最初の例題・半環の節・別名が重なり、2ページの差が読者に分からない
- **根拠**：
  - summary：matrix-power「状態ベクトルが毎回同じ線形変換 v' = Av で変わるとき、K 回後は A^K v で…繰り返し二乗法で…半環でも同じように累乗できる」、dp-matrix-power「遷移が毎回同じ線形写像（dp_{t+1} = A·dp_t）なら、dp_T = A^T·dp_0 を繰り返し二乗法で…(max,+) の行列でも…」
  - 最初の例題（＝代表問題）がどちらも dp_r。abc009_4（2213）も両方の練習
  - 節：matrix-power「半環上の行列積（min-plus・max-min・AND/XOR）」と dp-matrix-power「(max,+)・(min,+) の行列」
  - 別名「行列累乗」が両方。dp-matrix-power は matrix-power を前提にしたうえで、related に semiring-matrix・adjacency-matrix-power（どちらも matrix-power に解決される）を書いている
- **提案**：統合して matrix-power の1ページにする（01 指摘4と同じ。レベルは 01 指摘5の青案を合わせて決める）。dp-matrix-power の key を `merged_keys` に入れ、DP 特有の節「照合の状態・グリッドの境界の状態を行列にする」「ダブリングで遷移を合成する」を移し、`kind` を `[線形代数・行列, DP, ダブリング・分割統治]` にする。dynamic-dp の `prerequisites` の dp-matrix-power は matrix-power に書き直す。DP の章からは dp-speedup-overview の表でリンクする。
  - 2ページを残すなら、少なくとも次のように分ける：matrix-power は「行列の積・単位行列・計算量・半環・アフィン変換の合成・隣接行列の K 乗」に限り、例題を abc199_f・abc189_e・math_and_algorithm_aw にする。dp_r と abc009_4 は dp-matrix-power だけに置き、dp-matrix-power の節「(max,+)・(min,+) の行列」は消して matrix-power の節へリンクする。別名「行列累乗」は matrix-power だけにし、dp-matrix-power の related から semiring-matrix・adjacency-matrix-power を消す

### 4. dp-order の前提 dp-dag のために、DP・確率・ゲームの13ページの祖先にグラフの3ページが入る

- **重さ**：中（01 指摘11と同じ事実。影響の大きさから中にした）
- **場所**：dp/dp-order の `prerequisites`（dp-basics・dp-dag）、graph/graph-basics の `prerequisites`（complexity-estimation）
- **問題**：dp-dag の前提が graph/topological-sort なので、dp-order を祖先に持つページの前提の連鎖に topological-sort・dfs・graph-basics が入る。設計書 §9.1 の「前提をすべて理解した未読のページ＝次の候補」は、トポロジカルソートを理解済みにしないと区間 DP・期待値 DP・ゲームを候補に出さない
- **根拠**：
  - 祖先に topological-sort が入る graph・tree 以外のページは14（dp-dag 自身と、dp-order を経由する13）：dp-dag・dp-order・interval-dp・interval-dp-advanced・expected-value-dp・optimal-strategy-expectation・expectation-linear-equations・game-basics・minimax・nim・grundy-number・game-mirror-strategy・game-retrograde-analysis・partizan-games
  - 全ページで最も長い連鎖がここにある：partizan-games の9段、青の grundy-number の8段（complexity-estimation → graph-basics → dfs → topological-sort → dp-dag → dp-order → game-basics → nim → grundy-number）
  - dp-order の summary は「依存する値がすべて確定している順に状態を回す…依存関係の向きから選ぶ」で、DAG 上の DP を知らなくても読める。README §3-4 の「これを知らないと読めない」に当たらない
- **提案**：
  - dp-order の `prerequisites` を `[dp-basics]` にし、dp-dag は `related` へ移す（dp-dag の related にはすでに dp-order がある）。grundy-number の連鎖は8段から6段になる
  - interval-dp の `prerequisites` の dp-basics は dp-order 経由で届くので消す
  - graph-basics の `prerequisites` の complexity-estimation は `related` へ移す（グラフの表現と用語を読むのに計算量の見積もりは要らない。グラフ・木の全ページの連鎖が1段短くなる）

### 5. state-space-search と extended-dijkstra の境目が崩れており、設計書 §4.3 の「1ページ」とも食い違う

- **重さ**：中
- **場所**：graph/state-space-search（水・B）、graph/extended-dijkstra（水・A）、graph/graph-modeling（水・A）
- **問題**：設計書 §4.3 は「状態を頂点にする・超頂点：水（応用の節は青）。1ページで節にレベルの印」と決めたが、catalog は「状態空間の探索（盤面・配置・組を頂点にする BFS）」と「状態を頂点にする（拡張ダイクストラ・頂点倍化・超頂点）」の2ページに分けた。分けた軸（BFS かダイクストラか）もデータで守られておらず、graph-modeling の節「何を頂点にするか（物・値・座標・状態・時刻・剰余…）」も同じ内容を持つ。「状態を頂点」で引くと3ページが出る
- **根拠**：
  - extended-dijkstra の最初の例題 abc453_d は「座標と直前の向きの組を頂点にして BFS する」、練習 abc244_f は「…を状態にした BFS」、typical90_bb も BFS の距離
  - extended-dijkstra の `level_evidence` の最初の問題 abc339_d（1276）は state-space-search の例題
  - 由来：同じ research/03 の key state-space-search と extended-dijkstra
- **提案**：state-space-search を extended-dijkstra に統合する（`merged_keys` に state-space-search）。
  - 題名を §4.3 の言い方に合わせて「状態を頂点にする（状態空間の BFS・拡張ダイクストラ・頂点倍化・超頂点）」にし、節「盤面・配置・組を状態にする（状態数の見積もり・整数に詰める）」「両端から伸ばす（回文の最短路）（青）」を足す
  - 問題は合わせて15問になり §5.3 の上限（例題3・練習6・力試し3）を超えるので、例題を abc339_d・abc184_e・abc132_e に、練習を abc453_d・abc361_d・abc463_e・abc302_f・abc244_f・abc224_d に絞り、残りは本文の参照にする
  - graph-modeling の節「何を頂点にするか」は「頂点にするもの → ページ」の表だけにし、本文は extended-dijkstra に任せる

### 6. sigma-manipulation と contribution が同じ節・同じ例題・同じ別名を持つ

- **重さ**：中
- **場所**：math/sigma-manipulation（基礎・A）、thinking/contribution（水・A）
- **問題**：設計書 §4.2 は「Σ の変形・証明の型 → math（短いページ）」「寄与・主客転倒の一般論 → thinking」と分けたが、両ページが同じ「二重和の順序交換」を節に持ち、例題と別名も重なる。同じ考え方に基礎と水の2つのレベルが付いている
- **根拠**：例題 abc172_d（963）が両方の例題で、要約もほぼ同文（sigma「Σ k × (k の約数の個数) を、約数 d ごとに d の倍数の和として数え直す」、contribution「Σ k × (k の約数の個数)。約数 d ごとに、d の倍数の和として数え直す」）。別名「和の順序交換」が両方。節は sigma「二重和の順序交換と添字の範囲」と contribution「二重和の順序の入れ替え（表の行と列）」
- **提案**：分担を「sigma＝式の規則（線形性・添字の範囲の書き換え・付け替え・空和と空積）」「contribution＝数える対象の入れ替え（各要素が何回数えられるか）」と決めて書き分ける。
  - abc172_d（約数ごとに数え直す式変形）は sigma-manipulation だけの例題にし、contribution からは外す（contribution の例題は abc186_d・abc151_e の2問になる）
  - 別名「和の順序交換」は sigma-manipulation だけに置き、contribution には「主客転倒」「寄与」を残す。sigma の節「寄与・期待値の線形性とのつながり」は contribution へのリンクの1行にする

### 7. 平均・中央値・判定 DP の二分探索が4ページに散っている

- **重さ**：中（01 指摘4と同じ事実）
- **場所**：dp/dp-decision-binary-search（青）、basics/binary-search-answer（基礎）・fractional-binary-search（青）・median-binary-search（青）
- **問題**：dp-decision-binary-search の節「平均 ≥ X ⇔ Σ(a_i − X) ≥ 0、比 ≥ X ⇔ …」「中央値 ≥ X ⇔ …」は fractional・median の本体と同じで、summary は binary-search-answer の summary（判定の中身は貪欲・探索・DP）を繰り返す。固有の中身は「判定 DP の書き方（決め打ちごとに初期化し直す）」だけ
- **根拠**：例題 abc324_f（1815）が dp-decision と fractional の両方の例題、abc236_e（1893）が3ページの練習。別名「平均の最大化」「比の最大化」（fractional と）・「中央値の最大化」（median と）・「決め打ち二分探索」（binary-search-answer と）が衝突する。由来は 02 の key と 01 の key
- **提案**：dp-decision-binary-search をやめ、key を binary-search-answer の `merged_keys` に入れる。binary-search-answer の節「判定の中身（貪欲・探索・DP）」に「判定を DP で作る（決め打ちごとに初期化し直す）（青）」を足し、abc415_e（1212）を練習の abc457_d（手法名だけの要約。付録 K）と入れ替え、abc246_g（2313）を力試しに移す（練習の上限6を超えないようにする）。DP の章からは dp-state-design の `related` で binary-search-answer へつなぐ。残す場合でも、別名3つと平均・中央値の節は消す

### 8. そのほかの部分的な重なり（担当を1つに決める）

- **重さ**：中
- **場所と提案**（いずれも「同じ節・同じ例題・同じ別名」のどれかが重なる組。持ち主を1つにし、他方は1行のリンクにする）：

  | 組 | 重なり（根拠） | 提案 |
  | --- | --- | --- |
  | ds/persistent-data-structures（青）と tree/root-path-dfs（青） | 両方に節「操作の履歴を木にする（版の木）」と別名「版の木」。abc273_e（1624）が persistent の例題・root-path-dfs の練習（ds・tree の open_issues [4] が認める） | 版の木は persistent-data-structures が持つ。root-path-dfs から別名「版の木」を外し、節は「巻き戻しの応用として版の木へ」の1行にする。abc273_e は root-path-dfs の練習として残してよい（練習が1問しかないため） |
  | tree/tree-degree（青）と comb/cayley-pruefer（黄） | Prüfer 列の作り方と「出現回数＝次数 − 1」を両方が説明。別名が「プリューファー列」「Prüfer code」（tree-degree）と「Prüfer 列」「プリューファーコード」（cayley-pruefer）に割れる | 全単射の説明は低いレベルの tree-degree が持つ。cayley-pruefer は数え上げの公式に絞り、`prerequisites` に tree-degree を足す（今は related）。別名の両表記をそれぞれのページにそろえて持たせる |
  | tree/tree-edge-contribution（水）と ds/union-find-applications（水） | abc214_d（1341）が両方の例題。「辺を重みの小さい順に併合し、併合の瞬間に両側の大きさの積を数える」が両方の summary・節にある | abc214_d は union-find-applications の例題だけにし、tree-edge-contribution では練習にする。tree-edge-contribution は「辺で切って s(N − s)」（typical90_am・abc479_e）を本体にし、パス上の最大値の和は union-find-applications へのリンクの節にする |
  | ds/top-k-multiset・ds/segtree-on-values・ds/kth-element（いずれも水） | 「上位 K 個の和」を3ページが扱う（top-k-multiset の本体、segtree-on-values の summary、kth-element の節（黄））。abc281_e が3ページ、abc287_g が2ページ（＋patterns） | 方法ごとに持ち主を決める：2つの multiset は top-k-multiset、値を添字にした BIT・セグ木は segtree-on-values。kth-element の節「上位 K 個の和（黄）」は消して segtree-on-values へリンクし、力試しの abc287_g を外す（練習の abc281_e は練習が2問を割らないよう残す） |
  | math/fps-basics（発展）と comb/generating-function-counting（発展） | fps-basics の節「母関数の考え方（DP の遷移を多項式の積・商として見る）」が generating-function-counting の題名「母関数の考え方」と同じ。別名「母関数」が両方、例題 abc303_h（2501）が両方 | fps-basics から別名「母関数」「生成関数」と節「母関数の考え方」を外し、「数え上げでの立式は generating-function-counting へ」の1行にする。abc303_h は generating-function-counting の例題に寄せる（fps-basics は overview なので例題0〜1でよい。残る abc321_f は knapsack-undo の例題でもあるので、fps-basics では練習にする） |
  | graph/shortest-path-overview（technique・水・A）と guide/method-comparison | method-comparison の節「最短路：BFS／01-BFS／ダイクストラ／ベルマンフォード／ワーシャルフロイド」と同じ比較を、問題0の technique ページが持つ | どちらか一方にする。指摘11の方針で入口ページを guide 寄りに扱うなら shortest-path-overview を method-comparison の節に吸収する。残すなら method-comparison の最短路の節はリンクだけにする |
  | basics/periodicity（基礎）と ds/global-offset（基礎） | periodicity に別名「反転フラグ」と節「シミュレーションを速くする（ずれ・反転フラグの記録）」、練習 abc199_c（反転フラグで解く）。basics の open_issues [7] が重なりを認める | 反転フラグは global-offset が持つ。periodicity から別名「反転フラグ」を外し、abc199_c を global-offset の練習へ移す |

### 9. 設計書 §4.2 の置き場所と食い違うページと、§4.2 が求めるリンクの抜け

- **重さ**：中
- **場所**：graph/reachability-bitset（黄・C）、graph/dilworth-path-cover（発展）、ds・basics・tree の related
- **問題と根拠**：
  - reachability-bitset：§4.2 は「bitset による高速化 → misc。dp・graph からリンク」。misc/bitset-speedup にはすでに節「到達可能性・推移閉包（グラフの章の単独ページへ）（黄）」があり、同じ内容を節と単独ページの両方に持つ。根拠の問題は typical90_bg（★7）と abc287_h（2639、発展の帯）の2問だけ（01 指摘4・6と同じ）
  - dilworth-path-cover：§4.2 は「Dilworth の定理 → dp の LIS のページの節。graph（マッチングの双対、発展）からリンク」。lis は節と merged_keys の dilworth を持つが、graph の発展のページの題名の先頭も「Dilworth の定理」で、別名「Dilworth」も持つ。「Dilworth」で引くと発展のページの題名に当たる。最近の ABC で Dilworth を使った abc457_g（1928）・abc476_g（2477）はどちらも数列（LIS 側）の問題
  - §4.2 の「相手側の扱い」のリンクがない：CHT・Li Chao は「ds からリンク」だが ds のどのページも cht を前提・関連に持たない。並列二分探索は「basics からリンク」だが basics/binary-search-answer の related にない（ds の open_issues [9] が依頼したまま）。Functional graph は「tree からリンク」だが tree のどのページにもない
- **提案**：
  - reachability-bitset を bitset-speedup に統合する（`merged_keys`）。例題 typical90_bg・練習 abc287_h を移し、reachability-bitset を related に持つ dp-dag・scc・dilworth-path-cover の related を bitset-speedup に直す
  - dilworth-path-cover の題名を「最小パス被覆と Hall の定理（マッチングの双対）」にし、Dilworth は節「推移閉包と最大反鎖（数列なら LIS のページの Dilworth の定理へ）」に残す。別名「Dilworth」は外し、lis の別名「Dilworth の定理」に一本化する
  - ds/segment-tree（または advanced-ds-catalog）の related に cht、basics/binary-search-answer の related に parallel-binary-search、tree/tree-basics の related に functional-graph を足す。検証スクリプトに §4.2 の表を持たせ、相手側のリンクの有無を確かめる

### 10. 練習が目安に足りないページが75あり、黄では44ページ中28

- **重さ**：中（01 指摘6と同じ方向。こちらは全体の数を示す）
- **場所**：付録 A の75ページ。とくに黄の28ページ（練習0が18）、分野では comb 43中26・math 34中15・graph 39中14・tree 20中8
- **問題**：設計書 §5.3 の練習2〜6を満たさないページが technique・thinking の 28%（267中75）ある。黄は64%で、練習0の黄が18ある。練習の「解いた」チェックとロードマップの集計（§9.1）が、これらのページでは空になる。担当の open_issues は一部のページ（basics 2・ds 4・math 14 など）を挙げるだけで、全体の規模は書かれていない
- **根拠**：
  - 問題が2問以下の technique・thinking は35（基礎7・水6・青6・黄16）。黄の16のうち6ページ（complement-graph-bfs・xor-path・euler-path・lowlink・long-path-decomposition・fft-string-matching）は1問だけ
  - 黄の数論の4ページは数問を共有する：abc212_g は euler-phi と primitive-root の両方の例題、abc222_g は exponent-mod・euler-phi・multiplicative-order の3ページ、arc042_d は multiplicative-order と discrete-log。発展の mod-sqrt は問題0
- **提案**：
  1. 工程8a の前に、問題が2問以下の黄16ページについてページか節かを決める。データから見た案（01 指摘6とほぼ同じ）：complement-graph-bfs → bfs の節（黄）、xor-path → xor-basis の節、reachability-bitset → bitset-speedup の節（指摘9）、fft-string-matching → convolution-ntt の節（abc196_f はすでに convolution-ntt の練習）、multiplicative-order・discrete-log・primitive-root（と mod-sqrt）→ 1ページ「位数・原始根・離散対数」、long-path-decomposition → tree-diameter の節（黄）
  2. 残すページは、工程8b の前に「問題の補充」を1つの作業として progress.md に入れる（`python3 tools/ap.py search` と research/00 §2.3.8 から候補を出し、第三者の解説で裏付ける）。今の設計書 §10.2 の執筆の流れには、問題を探す工程がない
  3. `tools/check_catalog.py` に「練習が2未満」「例題0」の警告を足し、意図して少ないページは理由を残す欄（例：`problems_note`）を設ける

### 11. 横断・入口のページの type・level・frequency・problems の付け方がばらばら

- **重さ**：中（01 指摘10は twelvefold-way について同じ点を指摘）
- **場所**：graph/graph-modeling（technique・水・A・問題6）、graph/shortest-path-overview（technique・水・A・問題0）、dp/dp-speedup-overview（technique・水・A・例題0で力試し1問だけ）、thinking/observation-hub（thinking・基礎・A・問題7）、comb/counting-mindset（technique・水・A・問題9）、comb/twelvefold-way（technique・青・B・問題4）、ds/advanced-ds-catalog（overview・発展・C・問題0）
- **問題**：担当自身が `level_evidence` に「横断ページ」「入口ページ」「地図のページ」と書くページが、technique・thinking・overview の type とレベル・頻度を持つ。設計書 §2.2 の type に入口・比較・地図の型がないため、扱いが担当ごとに違う。ロードマップ（§7）は frequency A を「必修」にするので、問題のない比較のページが水の必修に入る
- **根拠**：graph-modeling・shortest-path-overview の `level_evidence` は「横断ページ。…」、dp-speedup-overview は「（横断の入口ページ）」、observation-hub は「入口ページ」、twelvefold-way は「地図のページ」。shortest-path-overview と dp-speedup-overview は例題0で §5.3（例題1〜3）を満たさない（検証スクリプトは警告しない）
- **提案**：入口・比較・地図のページの扱いを1つに決め、README に書く。案：type に `hub` を足し、level は「扱う手法の最も低い帯」、frequency は持たない（ロードマップには前提として出すが必修の数に入れない）、problems は0〜3で例題なしを許す。type を足さない場合でも、frequency をそろえ（たとえば全部 B）、例題0を許すページを README に列挙する。shortest-path-overview は指摘8のとおり method-comparison とどちらかに寄せる

### 12. 「ACL を呼ぶだけ」の問題を帯の根拠に数えるかが分野で違う

- **重さ**：中（01 指摘2は遅延セグ木について同じ事実を重大としている。ここでは分野をまたぐ規則の不統一として扱う）
- **場所**：graph/scc（水）、string/z-algorithm（水）、math/convolution-ntt（青）、ds/lazy-segment-tree（青）、string/suffix-array（黄）、graph/two-sat（発展）、設計書 §3.1・§4.3
- **問題**：設計書 §3.1 規則1（その手法を知らないと解けない問題がまとまって現れ始める帯）に、ACL を呼ぶだけで解ける問題を数えるかの決まりがない。そのため、scc は「ACL で書け、1285〜1376 の例がある」から水、convolution-ntt は「ACL を呼ぶだけの青」abc392_g（1817）から青、z-algorithm は「ACL で足りるので水」と数える一方、lazy-segment-tree は ACL を呼ぶだけの水の問題が3問（abc473_f 1303・abc382_f 1443・abc455_f 1549）あるのに青のまま（§4.1-2 の決定に従った）
- **根拠**：各ページの `level_evidence`。lazy-segment-tree の例題 abc382_f（1443）自体が水の帯にあり、付録 B-1 で「例題がすべて帯の外」に入る
- **提案**：§3.1 に規則を1つ足す：「ACL を呼ぶだけで解ける問題も帯の根拠に数える。ただし S・F の設計、縮約後の処理など、ACL の外の考察が本体なら数えない」。これを当てると、lazy-segment-tree は水（節「S・F の設計（青）」を置く）、lazy-segtree-patterns は青のまま、scc・z-algorithm・convolution-ntt は今のまま、suffix-array は黄のまま（ACL で足りる問題が水・青の帯にまとまっていない）、two-sat は発展のまま、と一貫する。§4.1-2 の「遅延セグ木（青）」も合わせて直す

### 13. level の根拠が帯と合わない・設計書の引用が誤っているページ

- **重さ**：中
- **場所と提案**：

  | ページ | 問題（根拠） | 提案 |
  | --- | --- | --- |
  | graph/lowlink（黄） | `level_evidence` は「設計書 §4.3 で黄」と書くが、§4.3 の表に lowlink はない。挙げた abc375_g・abc334_g は解説の解法が lowlink ではなく、例題 abc075_c（1067）は全探索で解く問題。レベルの根拠が実質ない（research/03 も同じ問題で黄としている） | 誤った引用を消し、「ABC で lowlink が想定解の問題は未確認。research/03 の判断で黄」と正直に書く。01 指摘6の「lowlink と二重連結成分の1ページ」にするなら、練習の代わりに Library Checker の two_edge_connected_components を `verify` に入れる |
  | basics/difference-sequence（水） | 根拠の問題が基礎（abc369_c 323・typical90_bl ★3・abc466_e 1027）と青〜黄（agc010_b 1892・abc459_f 2163・abc454_f 2169）に分かれ、水が1問もない | 基礎の部分を imos の節に戻し（設計書 §4.1-3 の元の例）、ページは「差分列への言い換え」として青にする。または水の根拠の問題を足して書く |
  | tree/complete-binary-tree（水） | 根拠は abc243_d（758）・abc465_d（839）の基礎と abc321_e（1627）の青だけ | 基礎にし、abc321_e の節に（青）の印を付ける |
  | comb/counting-bijection（水）・comb/lattice-paths（水） | 根拠は abc145_d（1009）の基礎と 1695〜2462 だけで、水がない（comb の open_issues [6] の迷い） | 水の根拠の問題を足すか、基礎の入口と青の節に分ける |
  | string/subsequence-matching（水） | 水の根拠は typical90_f（★5）だけで、ABC の根拠は abc452_d（903）・abc324_e（1153）の基礎と 1840・2072。§3.1 規則3は「ABC の問題があればそちらを優先」 | ABC の水の問題を足すか、基礎にする |
  | string/hash-safety（水） | 例題が abc339_f（1716）と typical90_au（★7）で、どちらも水より上 | 水の問題を例題に足すか、青にする |
  | math/gaussian-elimination（黄） | ABC の根拠は abc313_d（1630、青）と 2409 以上 | math の open_issues [7] のとおり青も検討する（01 指摘5の行列累乗の青案と合わせて決める） |

  あわせて `tools/check_catalog.py` に「`level_evidence` の問題がどれもページの帯に入らない」の警告（付録 B-2 の判定）を足すと、以後の見落としを防げる

### 14. 基礎のページに黄・発展の節があり、「基礎は短く」と合わない

- **重さ**：中（01 指摘1は節の印が生成物に乗らない問題を扱う。ここでは置き場所の問題として扱う）
- **場所**：dp/knapsack-01 の「区間の品物だけのナップサック（分割統治で左右の DP をマージ）（黄）」、basics/median-absolute の「更新しながら中央値を保つ（黄）」、tree/steiner-subtree の「DFS 順に並べて隣り合う2点の距離の和の半分（黄）」、comb/binomial-precompute の「法が素数でない・小さいときはパスカルの三角形（黄）」、comb/permutation-cycles の黄2節、ds/ordered-set の「（青〜黄）」、dp/subset-sum の bitset（黄）、comb/coupon-collector の「min-max 包除（発展）」、math/prime-factorization の「Pollard's rho（発展）」
- **問題**：設計書 §3.1 は基礎を「短いページ。初歩の説明は省き、応用の型・落とし穴・上位の手法とのつながりに絞る」とし、§4.1-2 は帯がはっきり分かれる型を別ページにすると決めた。基礎のページに黄の中身を置くと、ページが短くならず、黄の学習者はその内容にロードマップから届かない
- **根拠**：付録 F（ページより2段以上高い印は73節、基礎のページで22節、うち黄・発展が9節）。取り込んだ調査の key のレベルも離れている：subset-sum の dp-bitset（02 では黄）、greedy-basics の matroid（00 では発展）、permutation-cycles の key は 07 では黄
- **提案**：基礎のページの黄・発展の節は「上位の手法とのつながり（→ ページ）」の1行にし、中身は上位のページへ移す：knapsack-01 の区間ナップサック → divide-and-conquer の節、median-absolute の中央値の更新 → top-k-multiset（abc127_f をすでに持つ）、steiner-subtree のクエリ版 → auxiliary-tree、binomial-precompute のパスカルの三角形 → lucas-theorem（または 01 指摘6の統合先）、permutation-cycles の巡回型の数え上げ → 新ページ「巡回型で数える（黄）」か stirling-first・partition-number の節、subset-sum の bitset → bitset-speedup（節がすでにある）、coupon-collector の min-max 包除 → inclusion-exclusion の節（発展の印）。README §3 に「基礎のページの節の印は青まで」と書く

### 15. 「最初の例題＝代表問題」と「易しい順」が衝突し、代表問題が帯から外れる

- **重さ**：中
- **場所**：設計書 §5.3、catalog/README §3-7。kth-value・exchange-argument・segtree-binary-search・inclusion-exclusion・circle-geometry・parsing・lowlink・tree-centroid・root-path-dfs・broken-profile-dp
- **問題**：§5.3 は「最初の例題がそのページの代表問題」と「易しい順に並べ、帯をまたいで幅を持たせる」の両方を求める。catalog は易しい順を全ページで守った（逆転0）結果、最初の例題がページの帯から2段以上下の入口の問題になったページが10ある。生成物（問題 → ページの対応表など）や執筆者が「最初の例題」を代表として扱うと、青のページの代表が灰〜茶の問題になる
- **根拠**：inclusion-exclusion（青）の最初の例題は abc131_c（518）、segtree-binary-search（青）は abc382_c（476）、exchange-argument（青）は abc131_d（588）、kth-value（青）は abc341_d（829）、broken-profile-dp（黄）は abc113_d（1597）
- **提案**：代表問題を並び順から切り離す。problems の要素に `representative: true` を1つだけ付ける規則にし（帯の中の例題）、並びは易しい順のままにする。該当10ページは帯の中の例題に印を付ける（inclusion-exclusion は abc172_e（1880）、segtree-binary-search は練習の abc389_f（1642）を例題に上げる、exchange-argument は abc116_d（1712）など）

### 16. 問題の要約に解き方が入り、練習の一覧でネタバレになる。手法名だけの要約も47件ある

- **重さ**：中
- **場所**：全ページの `problems[].summary`（README §2 の形式は「何を問う問題か（自分の言葉で一言）」）
- **問題**：要約の約半分が「何を問うか」に続けて解き方を書く。設計書 §5.3 は練習を「要約と難易度だけ」、§6.6 は解法を折りたたみに置くと決めているので、要約をそのまま練習の一覧に使うと解き方が見える。逆に47件は手法名だけで、何を問う問題かが書かれていない（付録 K）
- **根拠**：
  - 解き方の語（DP・セグ木・二分探索・累積和・「〜で数える」「〜に言い換え」など）を含む要約：例題 512中252（49%）、練習 738中361（49%）、力試し 251中148（59%）。例：ordered-set の abc370_d「爆弾で上下左右の最も近い壁を壊すシミュレーション。行ごと・列ごとの set から探して両方から消す」
  - 手法名だけの例：imos の abc462_d「いもす法で解く最近の D（00 §2.3.8 の分類。内容は執筆時に確かめる）」、floor-sum の practice2_c「ACL の floor_sum をそのまま使う」、max-flow の tessoku_book_bp「最大流の基本形（鉄則本 A68）」
- **提案**：problems の要素を `summary`（問い：何を求めるか。手法名を書かない）と `approach`（方針：執筆者向け。サイトでは折りたたみの中にだけ出す）に分ける。工程8a の前に、スクリプトで「。」より後ろを `approach` に移す下ごしらえができる。手法名だけの47件は `approach` にだけ残し、`summary` は執筆時に問題の内容を確かめて書く（basics・dp・tree・ds・geometry の open_issues の約束どおり）

### 17. 同じ問題を多くのページで例題にしており、patterns・thinking も問題を抱えすぎる

- **重さ**：中（01 指摘14と同じ方向）
- **場所**：付録 C。patterns の8ページ、thinking の9ページ
- **問題**：例題は「本文で方針まで説明する」（§5.3）ので、同じ問題の方針が複数のページに書かれ、執筆・検証が重なり、ページどうしで説明が食い違う恐れがある。題材別（patterns）は各ページが例題3・問題8〜11で、設計書 §6.3 の「題材の性質 → 表 → 例題」の案内ページより重く、問題のほとんどがほかのページの再掲になっている
- **根拠**：
  - 2ページ以上で例題にしている問題は45問。abc310_d（1368）は6ページにあり、recursive-enumeration・dp-counting-dedup・counting-dedup・twelvefold-way・bell-number の5ページで例題
  - patterns の問題77問のうち69問はほかのページにもあり、36問はほかのページの例題（例：kth-and-median の例題 abc234_d・abc306_e・abc155_d は、それぞれ priority-queue・top-k-multiset・kth-value の例題）
  - comb の open_issues [8] は comb の中だけで同じ方針（例題は1ページ）を書いている
- **提案**：README §3 に「例題は1問につき1ページ（その手法の持ち主）。ほかのページでは練習か本文の参照にする」を足し、`tools/check_catalog.py` に「2ページ以上で example の問題」の警告を足す。patterns は表が本体なので problems を例題0〜1・練習0〜3（ほかのページと重ならないもの）に減らす。thinking は §4.1-7 の「例題2〜4」を上限にし、練習・力試しは各手法ページに任せる

### 18. 動く図の割り当てが設計書の目安の約3倍あり、優先度がない

- **重さ**：中
- **場所**：付録 G の80ページ（dp 19・math 11・graph 10・cpp 7 など）、設計書 §8.5
- **問題**：§8.5 は動く図を「合わせて20〜30個を目安にし、catalog の visual で割り当てる」としたが、catalog は80ページの `visual` に「動く図」「ステップ送り」を書き、優先度もない。執筆者は visual を指示として受け取るので、このままでは図の作業が見積もりの3倍になるか、執筆者ごとに勝手に削られる
- **根拠**：`visual` の文字列の分類で、動く図80・静的な図223・null 56。部品を共有すると書いたもの（game-retrograde-analysis・grid・operation-sequence など6件）を除いても約75。§8.5 の優先リストの15個はすべて含まれている（抜けはない）。comb だけが open_issues [11] で6つに絞った
- **提案**：`visual` を `{kind: dynamic|static, priority: 1|2|3, text: …}` の形にし、priority 1 を §8.5 の優先リストの15個と各分野の水・青の要のページから合計25前後に絞る。ほかの dynamic は priority 2〜3（余力があれば）にするか static に直す。permutation の「置換の巡回分解のページのステップ送りを共有」は、相手の permutation-cycles の visual が静的な図なので、どちらかに合わせる

### 19. ナビゲーションの順で、前提が同じ分野の後ろにある

- **重さ**：軽
- **場所**：付録 E の12件（basics 7・dp 3・math 2）
- **問題**：並び順がナビゲーションの順（README §2）なので、「順に学ぶ」読者が前提より先に後ろのページに当たる。basics は章の順がトポロジカル順になっていない
- **根拠**：bit-full-search（全探索の章）→ bit-operations（最後の bit 演算の章）、coordinate-compression・meet-in-the-middle → binary-search（後ろの章）、kth-value → two-pointers、median-binary-search → prefix-sum、dp-sequence-partition・insertion-dp → dp-prefix-sum（最後の高速化の章）、dp-dimension-reduction → knapsack-01、proof-patterns → gcd-lcm、multiplicative-function → floor-quotient-enum
- **提案**：basics の章を「方針を立てる → bit 演算 → 全探索 → ソートと二分探索（sorting-techniques・binary-search・coordinate-compression・binary-search-answer）→ 累積和といもす法 → 尺取り法 → 二分探索の応用（meet-in-the-middle・kth-value・fractional・median-binary-search）→ …」の順に並べ替える。dp は dp-prefix-sum を「DP の考え方」の章の末尾へ移す（水・A の基本の道具なので早く見せてよい）か、dp-sequence-partition・insertion-dp の前提を related にする。math は proof-patterns を GCD の章の末尾へ、multiplicative-function を floor の章の floor-quotient-enum の後へ移す。検証スクリプトに「同じ分野の前提がナビの後ろにある」の警告を足す

### 20. 推移的に冗長な前提が48あり、前提の抜けと不要な前提もある

- **重さ**：軽
- **場所**：付録 D、steiner-tree・lgv-lemma・lis・kmp・palindrome・graph-basics、孤立した4ページ
- **問題と根拠**：
  - 冗長な前提48（例：lazy-segment-tree → segment-tree は segment-tree-monoids 経由、counting-dedup・counting-fix-order・counting-bijection・inclusion-exclusion の binomial-coefficient は counting-mindset 経由）。意味は正しいが、知識マップの辺が増え、README §3-4 の「多くて4つ」の枠を使う
  - 前提と related の両方に同じページ：bit-dp・small-graph-brute-force（bit-full-search）、dp-matrix-power（matrix-power）、harmonic-sum（complexity-estimation）、geometry-precision（gcd-lcm）、circle-geometry（binary-search-answer）
  - 抜け：steiner-tree（O(3^K N) の部分集合の分割）に subset-enumeration-dp がない。lgv-lemma（行列式を取る）に determinant がない。lis は節「セグ木版」と `acl: [segtree]` を持つのに segment-tree が前提にも関連にもない。cayley-pruefer に tree-degree（指摘8）
  - 不要：kmp → z-algorithm（KMP は Z を使わない。01 指摘11）、palindrome → bfs（BFS を使うのは節「両端から作る」の abc394_e だけ）、graph-basics → complexity-estimation（指摘4）
  - どこからも張られていないページ：complement-graph-bfs・k-shortest-paths・tree-ratio-greedy・stern-brocot（設計書 §1.2 の「行き止まりを作らない」の逆で、入ってくる道がない）
- **提案**：冗長な48件は catalog から消す（または生成スクリプトが推移簡約してから描く。どちらにするか決めて README に書く）。前提と related の重複6件は related から消す。抜けの3件を足し、不要の3件を related に移す。孤立した4ページは、complement-graph-bfs を bfs から、k-shortest-paths を dijkstra から、tree-ratio-greedy を exchange-argument から、stern-brocot を gcd-lcm（または floor-sum）の related から張る

### 21. `related` が調査の key のままで、節への行き先が失われ、解決すると重複する

- **重さ**：軽
- **場所**：前提・関連の145件（うち前提2件：small-graph-brute-force の permutation-search、min-cost-flow の potential-reweighting）、付録 L の21ページ
- **問題**：設計書 §5.1 は「相手の調査の key を書いてよい（統合後にスクリプトで解決する）」としたが、key は統合先のページの id に解決されるだけで、どの節かが失われる。たとえば lexicographic-greedy の related の kth-combination は binomial-coefficient のページの先頭に飛び、目的の「辞書順 K 番目」の節に届かない。解決すると同じページが2回以上出るページが21ある（grid は bfs・parity が2回、manhattan-chebyshev が3回）
- **提案**：`merged_keys` の各 key に統合先の節を対応させる（例：`merged_keys: [{key: kth-combination, section: "辞書順 K 番目の構成"}]`、または節にアンカーの id を書く規則）と、生成スクリプトが `page#anchor` に解決できる。工程8a の前に、前提の2件は page id に直し、related の重複21件は1つにまとめる

### 22. 紛らわしい・誤った別名と、題名と同じ別名

- **重さ**：軽
- **場所**：付録 I の81組のうち、次のもの
- **問題と提案**：別名は検索と逆引きの入口なので、ほかのページの名前を持つと検索結果が割れる。

  | 別名（ページ） | 問題 | 提案 |
  | --- | --- | --- |
  | 「BIT DP」（dp-segment-tree） | bit-dp の「bitDP」と、空白と大文字小文字を除くと同じ | 「BIT で DP を速くする」に変える |
  | 「ベル数」「グループ分けの全列挙」（recursive-enumeration） | bell-number の題名・別名 | 「ベル数」を外す（01 指摘4） |
  | 「反転フラグ」（periodicity） | global-offset の題名・別名 | 外す（指摘8） |
  | 「mex」（grundy-number） | patterns/mex の題名 | 外す（Grundy 数の説明の中で mex を使うだけ） |
  | 「平面走査」「sweep line」（event-sort） | sweep-line-2d の題名・別名 | event-sort は「平面走査の基本」に変え、「sweep line」は sweep-line-2d だけに置く |
  | 「有理数の mod 表現」（mod-inverse） | 設計書 §4.2 は「確率・期待値を mod で答える」を comb/rational-mod に置いた | mod-inverse からは外す |
  | 「グループ分け」（connected-components） | recursive-enumeration・bell-number の別名と紛らわしい | 「連結成分ごとのグループ」などに変える |
  | 「文字種ごとの BIT」（segment-tree） | BIT は fenwick-tree の名前 | 「文字の集合を持つセグ木」に変える |
  | 「Disjoint Sparse Table」（sparse-table と advanced-ds-catalog） | 2ページにある | sparse-table の節と別名だけにする |
  | 題名と同じ別名（inclusion-exclusion「包除原理」、min-cost-flow・centroid-decomposition・determinant・stirling-first） | 意味がない | 外す |

  検証スクリプトに「同じ別名が2ページ以上」の警告（意図した重複は許可リストに書く）を足す

### 23. 英語名・略称の別名が49ページにない

- **重さ**：軽
- **場所**：付録 H の49ページ
- **問題**：設計書 §9.2 の claude.ai の手順は「手法名・別名・問題のサインで言い方を変えて複数回検索する」とし、英語の解説や記事の手法名から引くことがある。題名にも別名にも英字の表記がないページは、英語名では見つからない。人名を含む名前をエンダッシュで書いたページは、ASCII のハイフンの別名がないと検索の区切り（設計書 §8.4）で一致しないおそれがある
- **根拠**：例：coordinate-compression（coordinate compression）、binary-search-answer（binary search on the answer・parametric search）、ternary-search（ternary search）、connected-components（connected components）、bipartite-graph（bipartite graph）、min-cut（min cut）、difference-constraints（difference constraints）、mobius-function（Möbius・Mobius）、stirling-first（Stirling numbers）、lattice-paths（lattice path）、generating-function-counting（generating function）、chromatic-number（chromatic number）、complement（complementary counting）、invariant（invariant）。grundy-number は「Sprague–Grundy の定理」（エンダッシュ）だけで「Sprague-Grundy」がない（aho-corasick・stern-brocot・miller-rabin・linear-recurrence-fast は ASCII の別名を持つ）
- **提案**：英語の定まった名前がある手法には英語名を1つ別名に足す（付録 H の49ページを担当ごとに確かめる）。題名にエンダッシュを使うページには ASCII ハイフンの別名を必ず置く規則を README §3 に足す

### 24. 題名と id の表記ゆれ

- **重さ**：軽
- **場所と根拠**：
  - 略称：「セグメント木」（segment-tree・lazy-segment-tree・segment-tree-graph）と「セグ木」（ほか8題名）が混在する
  - 大文字小文字：「K 番目の値」（kth-value）・「K 番目と中央値」（patterns）と「k 番目の値を求めるデータ構造」（kth-element）・「k 番目の最短路」（k-shortest-paths）
  - 人名の連結：「Knuth-Yao」（monge、ハイフン）と「Aho–Corasick」「Sprague–Grundy」「Miller–Rabin」「Stern–Brocot」「Bostan–Mori」（エンダッシュ）
  - 人名の表記：カタカナ（ダイクストラ・ワーシャルフロイド・ベルマンフォード・エラトステネス・メビウス・スターリング）とラテン文字（Kruskal・Prim・König・Cayley・Lucas・Burnside・Dilworth・Hall・Monge）が規則なく混ざる。「〜法」も「KMP 法」「Aho–Corasick 法」と「Z-algorithm」「Mo's algorithm」で割れる
  - 数字と和文の間：空白あり12（「2 次元累積和」「2 つの multiset」）と空白なし7（「45度回転」「木の2色塗り分け」「写像12相」「第2種スターリング数」「1点・2点から」）
  - 長さ：30字以上の題名が35（cpp が16）、かっこの補足つきが367中217。スマホのナビゲーション（設計書 §1.2）で2行以上に折り返す
  - id：「segtree-」（segtree-on-values・segtree-binary-search・lazy-segtree-patterns）と「segment-tree-」（segment-tree-monoids・segment-tree-beats・segment-tree-graph・dp-segment-tree）が混在する。DP の id も「dp-grid」「dp-phase」と「tree-dp」「bit-dp」「digit-dp」で前後が割れる
- **提案**：工程6の style-guide と prh.yml に、題名の規則（正式名は「セグメント木」、本文と補足は「セグ木」／数の K は大文字／人名の連結はエンダッシュ・別名に ASCII／日本で定着したカタカナ名はカタカナで、ほかはラテン文字／数字と和文の間は空白なし、など）を決め、catalog の題名をそろえる。題名のかっこの補足はナビゲーションでは省き、summary に回す（必要なら front matter に `nav_title` を足す）。id はファイル名と URL になるので、工程8a の前に「segment-tree-」にそろえるかを決める

### 25. kind の語彙の誤用と、足すべき語

- **重さ**：軽
- **場所と根拠**：
  - 「全探索」を計算量の見積もりの意味で使う：complexity-estimation（[全探索]）、harmonic-sum（[整数論, 全探索]）、divisor-count-bound（[整数論, 全探索]）。basics の open_issues [12] が語の不足を挙げている
  - 分割数・彩色数を「全探索」にする：partition-number（[数え上げ, 全探索]。分割数は DP で数える）、chromatic-number（[全探索, 数え上げ]。彩色数は包除と bitDP）
  - start/notation に「整数論」：種類別の一覧の「整数論」に「記法と用語の約束」が並ぶ
- **提案**：README §4 に語「計算量」（計算量の見積もり・ならし計算量・調和級数・定数倍）を足し、complexity-estimation・harmonic-sum・divisor-count-bound に付ける。partition-number は [数え上げ, DP]、chromatic-number は [DP, 数え上げ]、notation は [案内] にする。interactive（[二分探索, 実装・C++]）は misc の open_issues [5] のとおり語がないので今のままでよい

### 26. summary の長さ・文の数と、ページの説明になった要約

- **重さ**：軽（01 指摘17は作り手側の言葉の混入を扱う）
- **場所と根拠**：
  - 3文以上が21（設計書 §3.3 は1〜2文）：binary-search・kth-value・ternary-search・imos・bitwise-independence・complement・dp-prefix-sum・topological-sort・scc・merge-sort-tree など
  - 160字を超えるものが15（うち cpp が12。acl-reading 227字、cpp-algorithms 221字）。llms.txt の1行（設計書 §8.3）とツールチップには長い
  - 中心がページの説明になっている（何ができるかの文がない、または後回し）：graph-modeling「…言い換える型を集めた入口のページ」、shortest-path-overview「…選ぶための比較のページ」、tree-construction「…作る型をまとめる」、tree-basics「…木の性質をまとめる」、union-find-connectivity「…使い方をまとめる」、digit-and-mod「10 進数の桁を mod で扱う型をまとめる」、kth-element「…方法を比べる」、suffix-automaton「…を並べる」、partizan-games「…入口を紹介する」、observation-hub「…索引」
  - 「このページ」「ここで」「ここに」を含む：observation-hub・dijkstra・tree-basics・counting-mindset・inclusion-exclusion-dp・palindrome・cpp-environment・cpp-macros-template-file。断片で読まれたとき（設計書 §6.1-5）に「ここ」が何を指すか分からない
- **提案**：README §3-8 に「1文目は何ができるか（いつ使うか）。ページの中身の説明（まとめる・扱う・紹介する）で終えない。2文・120字以内。『このページ』『ここ』を使わない」を足し、検証スクリプトで文の数と長さを警告する

### 27. signs の constraint が半分以上のページになく、手法名が入った sign がある

- **重さ**：軽（01 指摘12は phrase の質を扱う。ここでは constraint の欠けを数えた）
- **場所と根拠**：
  - constraint が1つもない technique・thinking・overview は322中174。分野では tree 27中24、comb 51中33、graph 52中34、thinking 9中9、basics 33中19。設計書 §7 の「逆引き辞典（制約から）」は constraint から候補のページを生成するので、これらの分野は生成部分にほとんど出ない
  - constraint なのに数・不等号がない：segtree-on-values（オンライン強制）、geometric-series-mod（法が素数とは限らない）、ext-gcd（同）
  - 手法名が入った sign（言い回しの逆引きで「答え」が見えてしまう）：palindrome「N ≤ 10^6 なら Manacher」、lazy-segment-tree「（双対セグ木）」、convex-hull「累積和の点の上側凸包」、digit-dp「（2進の桁 DP）」、fps-basics「解説に母関数・多項式の逆元・log・exp が出てくる」
  - 「N ≤ 2×10^5 の木」（tree-dp）のように候補を絞れない constraint もある
- **提案**：技法の特徴が制約に出るページ（bitDP の N ≤ 20、区間 DP の N ≤ 500、二乗の木 DP の N ≤ 5000 など）には constraint を1つ以上置く規則にし、tree・comb・graph の担当が見直す。数のない constraint は phrase に移す。sign の文から手法名を外す

### 28. 古い ABC と ARC への偏り

- **重さ**：軽（01 指摘13と同じ方向）
- **場所**：付録 J（2019年以前が6割以上18ページ、2023-09 以降が0のページ63）、ARC・AGC が3割以上の13ページ
- **問題**：設計書 §5.3 は近年（7問体制の 2023-09 以降を含む）の問題を重く見るとし、ARC は少なめにするとした。基礎のページほど古い問題だけになっている（dp-basics は5問中4問が2019年以前で、2023-09 以降0。prime-factorization は7問中5問、string-basics は5問中4問）。game-mirror-strategy は6問中5問が ARC・AGC、lucas-theorem は2問とも ARC・AGC
- **提案**：指摘10の「問題の補充」の作業で、2023-09 以降が0のページに research/00 §2.3.8 と `tools/ap.py search` から最近の問題を1問以上足す。ARC・AGC が多いページは、01 指摘6の統合（lucas-theorem・game-mirror-strategy を節にする）と合わせて決める

### 29. frequency の根拠が残らず、cpp と overview の意味もあいまい

- **重さ**：軽（01 指摘7は数え直しを求める。ここではデータの形の問題を挙げる）
- **場所**：全ページの `frequency`、catalog/README §5
- **問題と根拠**：
  - level には `level_evidence` があるが、frequency には根拠の欄がない。problems と level_evidence にある abc400 以降の問題の平均は A 0.71・B 0.59・C 0.15 で、A と B の差が小さい。A の87ページのうち50は abc400 以降の問題を1つも挙げていない
  - 横断・入口のページ（指摘11）が A を持ち、ロードマップの必修になる
  - overview（発展）に B が6（dynamic-dp・monge・alien-dp・online-convolution・fps-basics・linear-recurrence-fast）。同じ手法の dp-convolution は C（指摘1）
  - cpp の20ページのうち14が A だが、README §5 の基準（最近の ABC の D〜G で使われた回数）は C++ の書き方には当てはまらない
- **提案**：`frequency_evidence`（research/00 §2.3.8 の120問と abc400〜480 の分類から数えた回数）を足し、A・B の判定を数で書く（01 指摘7の数え直しと同じ作業で埋まる）。cpp の frequency は「解説コードで見る頻度」と定義し直すか null にする。入口のページは指摘11の方針に従う

### 30. chapter の区切りと「発展」の章の扱いが分野でそろっていない

- **重さ**：軽
- **場所と根拠**：
  - 1ページだけの章：basics「方針を立てる」（complexity-estimation）・「尺取り法」（two-pointers）、graph「経路の種類」（euler-path）
  - 無関係な2つを束ねた章：basics「イベントソートとランレングス圧縮」。何でも入る章：graph「横断・その他」（graph-construction・degree-sqrt・chromatic-number）
  - 「発展」の章：tree は「発展」、comb は「数え上げの発展」の章を持つが、hld・auxiliary-tree・merge-process-tree（tree）、continuous-probability・partizan-games（comb）などの overview は話題の章にある。dp・graph・math・ds は発展の章を持たない。ds の章「発展的なデータ構造」には青の technique（persistent-data-structures・merge-sort-tree・binary-trie）が3ページあり、レベル名「発展」と紛らわしい
  - 章がない分野：cpp は20ページ（tree の27に近い）で章がない
- **提案**：overview は話題の章に置く（「発展」の章を作らない）に統一し、tree の「発展」の4ページと comb の「数え上げの発展」の6ページを話題の章へ移す。ds の章名は「そのほかのデータ構造」にする。1ページの章は隣の章と合わせ（「方針を立てる」+「全探索」、「尺取り法」+「累積和といもす法」、「経路の種類」+「基本と探索」）、event-sort はソートの章、run-length-encoding は貪欲の前の「列を塊で見る」節かソートの章に移す。cpp は4〜5章（型と式・参照とラムダ・コンテナとアルゴリズム・ranges・入出力と環境と ACL）に分ける

### 31. `verify` が ds の24ページにしかない

- **重さ**：軽
- **場所**：ds の24ページ、catalog/README §2（形式に verify がない）、設計書 §3.3・§7（自作ライブラリの設計と動作確認）
- **問題**：設計書 §7 は「各ページの verify から Library Checker の対応表を生成」とするが、`verify` は ds の担当だけが自主的に入れた（ds の open_issues [13]）。ほかの分野の Library Checker の対応は sections の文中にしかない（例：math/fft-ntt の節「Library Checker での確認（convolution_mod・convolution_mod_1000000007）」）。このままでは生成する対応表が ds だけになる
- **根拠**：`acl` を持つ70ページのうち `verify` があるのは9。sections に Library Checker の問題名を書いたページは14（dp・math の overview など）
- **提案**：README §2 の形式に `verify`（任意）を足し、ACL のあるページ（scc・two-sat・max-flow・min-cost-flow・convolution-ntt・floor-sum・crt・suffix-array・z-algorithm・lca など）を各担当が埋める。sections の中の Library Checker の問題名は `verify` に移す

### 32. 節のレベルの印の書き方がそろっておらず、ページより低い印もある

- **重さ**：軽（01 指摘1・8と同じ対象。ここでは書式の不統一だけを挙げる）
- **場所**：sections の印
- **問題と根拠**：印は大半（197節）が「（青）」のような1語の形だが、ほかに「（発展：Monge・Alien DP へ）」（dp-sequence-partition）、「（黄、bitDP へ）」（extended-dijkstra）、「（黄、木 DP での使い方は DP の章）」（small-to-large）、「（黄・発展 → DP の章）」（top-k-multiset）、「（発展寄り）」（persistent-data-structures）、「（発展の紹介）」（fractional-binary-search）、「（青〜黄）」（ordered-set）など12通りの書き方がある。ページより低い印は17節（string-automaton-dp の「簡易版（水）」、inclusion-exclusion の「2〜3 条件の包除（基礎）」など）
- **提案**：01 指摘1で節を構造化する（節ごとに level を持たせる）なら、そのときに印を「節の level」と「行き先のリンク」に分ける。文字列のまま残すなら、README §2 に「印は末尾の（水）（青）（黄）（発展）のどれか1つ。行き先は印の外に『→ ページ id』で書く」と決め、「〜寄り」「〜の紹介」「範囲（青〜黄）」を使わない

---

## 付録

付録の一覧はすべてスクリプトで catalog から機械的に作った（2026-10-21、commit 8cf737f の作業ツリー）。difficulty は `tools/ap.py` の値。

### 付録 A　練習が2問未満のページ（設計書 §5.3 の目安は2〜6。guide・cpp・overview・pattern を除く）

| レベル | 件数 | ページ（練習の数） |
| --- | ---: | --- |
| 基礎 | 10 | graph/graph-basics（1）、tree/steiner-subtree（0）、math/proof-patterns（1）、math/mod-pow（1）、math/modint（1）、math/spf-sieve（1）、comb/counting-basics（1）、comb/permutation-cycles（1）、comb/probability-basics（1）、comb/coupon-collector（1） |
| 水 | 18 | dp/dp-speedup-overview（0）、graph/shortest-path-overview（0）、graph/state-space-search（1）、graph/time-dependent-dijkstra（1）、graph/namori-graph（1）、tree/leaf-first（0）、tree/complete-binary-tree（1）、math/exponent-mod（1）、math/geometric-series-mod（1）、math/segmented-sieve（1）、math/ext-gcd（1）、comb/counting-bijection（1）、comb/counting-fix-order（0）、comb/multinomial-coefficient（1）、comb/lattice-paths（0）、comb/nim（1）、string/hash-safety（1）、string/hashing-for-sets（1） |
| 青 | 19 | basics/median-binary-search（1）、dp/dp-decision-binary-search（1）、graph/difference-constraints（1）、graph/graph-construction（1）、graph/degree-sqrt（1）、tree/tree-path（1）、tree/root-path-dfs（1）、ds/sparse-table（0）、ds/persistent-data-structures（0）、ds/merge-sort-tree（0）、ds/binary-trie（1）、comb/counting-dedup（1）、comb/binomial-identities（1）、comb/bell-number（0）、comb/lucas-theorem（0）、comb/zeta-mobius-divisor（0）、comb/permutation-parity（1）、comb/expectation-linear-equations（1）、misc/parsing（1） |
| 黄 | 28 | basics/divide-and-conquer（0）、graph/complement-graph-bfs（0）、graph/xor-path（0）、graph/reachability-bitset（1）、graph/lowlink（0）、graph/euler-path（0）、graph/min-cut（0）、tree/tree-centroid（0）、tree/centroid-decomposition（1）、tree/long-path-decomposition（0）、math/euler-phi（1）、math/multiplicative-order（1）、math/discrete-log（1）、math/primitive-root（0）、math/floor-sum（0）、math/gaussian-elimination（1）、math/xor-basis（1）、comb/partition-number（0）、comb/reflection-principle（0）、comb/mobius-function（1）、comb/zeta-mobius-subset（0）、comb/inclusion-exclusion-dp（1）、comb/cayley-pruefer（0）、comb/counting-labeled-graphs（1）、comb/expectation-tail-sum（0）、comb/expectation-of-square（0）、comb/game-retrograde-analysis（0）、string/fft-string-matching（0） |

### 付録 B　レベルと根拠の問題の帯の食い違い

B-1　例題がすべてページのレベルの帯の外にあるページ（difficulty のない問題は除いて判定）

| ページ | レベル | 例題 |
| --- | --- | --- |
| basics/ternary-search | 水 | abc279_d（766） |
| basics/difference-sequence | 水 | typical90_bl（—）・abc466_e（1027） |
| thinking/reformulation | 水 | agc003_a（436）・abc324_e（1153） |
| dp/dp-order | 水 | abc188_e（1170） |
| dp/dp-state-design | 水 | dp_c（—）・abc306_d（596） |
| dp/dp-dimension-reduction | 青 | dp_e（—）・abc364_e（1496） |
| dp/dp-reconstruction | 水 | abc271_d（886）・typical90_bd（—） |
| dp/dp-counting-dedup | 青 | abc310_d（1368） |
| dp/subsequence-dp | 黄 | abc214_f（1973） |
| dp/broken-profile-dp | 黄 | abc113_d（1597） |
| dp/rerooting | 青 | abc220_f（1304）・dp_v（—） |
| dp/insertion-dp | 黄 | dp_t（—）・abc134_f（2532） |
| dp/inline-dp | 青 | abc271_e（1402）・dp_w（—） |
| dp/dp-matrix-power | 黄 | dp_r（—）・abc305_g（1989） |
| dp/slope-trick | 発展 | abc127_f（2003） |
| graph/graph-modeling | 水 | abc285_d（663）・abc327_d（709） |
| graph/warshall-floyd | 水 | abc079_d（949）・abc208_d（1190） |
| graph/lowlink | 黄 | abc075_c（1067） |
| graph/offline-dynamic-connectivity | 発展 | abc334_g（2242） |
| tree/complete-binary-tree | 水 | abc243_d（758）・abc321_e（1627） |
| tree/tree-construction | 青 | abc451_e（1215）・abc478_f（1588） |
| ds/segtree-on-values | 水 | abc339_e（1109） |
| ds/segtree-binary-search | 青 | abc382_c（476）・practice2_j（—） |
| ds/lazy-segment-tree | 青 | abc382_f（1443）・practice2_k（—）・practice2_l（—） |
| math/floor-quotient-enum | 水 | abc230_e（969） |
| math/gaussian-elimination | 黄 | typical90_be（—）・abc313_d（1630） |
| math/linear-recurrence-fast | 発展 | tdpc_fibonacci（—）・abc436_g（2164） |
| comb/counting-bijection | 水 | abc145_d（1009）・abc110_d（1695） |
| comb/lattice-paths | 水 | abc145_d（1009）・arc058_b（1905） |
| comb/linearity-of-expectation | 水 | abc154_d（485）・abc334_e（1195）・typical90_bn（—） |
| comb/continuous-probability | 発展 | agc021_b（2130） |
| comb/grundy-number | 青 | tessoku_book_ah（—）・abc368_f（1180）・typical90_ae（—） |
| string/subsequence-matching | 水 | abc452_d（903）・typical90_f（—） |
| string/hash-safety | 水 | abc339_f（1716）・typical90_au（—） |
| string/suffix-automaton | 発展 | abc452_g（2255） |

B-2　`level_evidence` に挙げた問題のどれもページの帯に入らないページ

| ページ | レベル | level_evidence の問題 |
| --- | --- | --- |
| basics/difference-sequence | 水 | abc369_c（323）・abc466_e（1027）・agc010_b（1892）・abc459_f（2163）・abc454_f（2169） |
| graph/reachability-bitset | 黄 | abc287_h（2639） |
| graph/offline-dynamic-connectivity | 発展 | abc334_g（2242） |
| tree/complete-binary-tree | 水 | abc243_d（758）・abc465_d（839）・abc321_e（1627） |
| tree/dynamic-tree | 発展 | abc350_g（2058） |
| ds/balanced-bst | 発展 | abc241_d（1177）・arc033_3（1641） |
| math/mod-pow | 基礎 | abc228_e（1579） |
| math/mod-inverse | 基礎 | abc186_e（1461） |
| math/gaussian-elimination | 黄 | abc313_d（1630）・abc366_g（2409）・yahoo_procon2019_qual_e（2585） |
| comb/counting-basics | 基礎 | abc307_e（1240） |
| comb/counting-bijection | 水 | abc145_d（1009）・abc110_d（1695）・arc058_b（1905）・arc110_d（2078） |
| comb/lattice-paths | 水 | abc145_d（1009）・arc058_b（1905）・abc240_g（2462） |
| string/subsequence-matching | 水 | abc452_d（903）・abc324_e（1153）・abc346_f（1840）・arc081_c（2072） |
| string/suffix-automaton | 発展 | abc452_g（2255） |

### 付録 C　同じ問題を複数のページで使っている例

C-1　3ページ以上で使う問題（52問）

| 問題 | ページ（役割） |
| --- | --- |
| abc310_d（1368） | recursive-enumeration（例）、dp-counting-dedup（例）、subset-enumeration-dp（練）、counting-dedup（例）、twelvefold-way（例）、bell-number（例） |
| abc127_f（2003） | median-absolute（力）、slope-trick（例）、top-k-multiset（力）、kth-and-median（力） |
| abc141_e（1459） | lcs（練）、rolling-hash（例）、hash-safety（練）、z-algorithm（練） |
| abc202_d（966） | lexicographic-greedy（練）、dp-reconstruction（練）、binomial-coefficient（練）、kth-and-median（練） |
| abc241_d（1177） | ordered-set（練）、kth-element（練）、balanced-bst（練）、kth-and-median（練） |
| abc330_e（1004） | ordered-set（練）、interval-set（練）、segtree-binary-search（練）、mex（例） |
| abc359_g（2099） | tree-dp（力）、small-to-large（練）、centroid-decomposition（練）、auxiliary-tree（練） |
| abc106_d（1319） | event-sort（練）、sweep-line-2d（練）、interval（練） |
| abc110_d（1695） | prime-factorization（力）、stars-and-bars（練）、counting-bijection（例） |
| abc128_e（1840） | event-sort（力）、offline-queries（練）、operation-sequence（力） |
| abc131_f（1937） | connected-components（力）、graph-modeling（練）、union-find-applications（練） |
| abc133_e（1505） | tree-dp（練）、tree-traversal（力）、counting-fix-order（例） |
| abc140_e（1873） | contribution（力）、ordered-set（力）、interval（力） |
| abc156_d（1014） | complement（練）、binomial-precompute（練）、counting-mindset（練） |
| abc163_e（2037） | exchange-argument（力）、exchange-argument-dp（力）、interval-dp（練） |
| abc180_f（2419） | dp-counting-dedup（力）、counting-mindset（力）、counting-labeled-graphs（練） |
| abc181_f（2009） | union-find-connectivity（力）、bottleneck-path（練）、circle-geometry（例） |
| abc183_f（1586） | small-to-large（例）、merge-process-tree（練）、union-find-applications（練） |
| abc185_f（1053） | fenwick-tree（例）、segment-tree（練）、xor（練） |
| abc210_d（1507） | dp-grid（練）、manhattan-chebyshev（練）、grid（練） |
| abc222_g（2242） | exponent-mod（練）、euler-phi（練）、multiplicative-order（例） |
| abc226_f（2086） | twelvefold-way（練）、partition-number（例）、permutation-cycles（力） |
| abc234_d（503） | kth-value（練）、priority-queue（例）、kth-and-median（例） |
| abc235_e（1304） | minimum-spanning-tree（例）、lca（練）、offline-queries（練） |
| abc236_e（1893） | fractional-binary-search（練）、median-binary-search（練）、dp-decision-binary-search（練） |
| abc246_g（2313） | dp-decision-binary-search（力）、tree-dp（力）、minimax（力） |
| abc273_e（1624） | root-path-dfs（練）、persistent-data-structures（例）、operation-sequence（練） |
| abc281_e（1334） | top-k-multiset（例）、kth-element（練）、segtree-on-values（練） |
| abc281_f（1714） | bitwise-independence（力）、binary-trie（例）、xor（練） |
| abc281_g（2304） | modint（練）、binomial-precompute（力）、counting-labeled-graphs（例） |
| abc287_g（2180） | kth-element（力）、segtree-on-values（力）、kth-and-median（力） |
| abc292_d（579） | connected-components（練）、namori-graph（練）、union-find（練） |
| abc294_g（1702） | lca（練）、euler-tour（例）、hld（練） |
| abc300_e（1354） | memoized-recursion（練）、rational-mod（練）、expected-value-dp（練） |
| abc303_h（2501） | fps-basics（例）、cayley-pruefer（力）、generating-function-counting（例） |
| abc308_g（2008） | ordered-set（力）、binary-trie（例）、xor（力） |
| abc311_e（1293） | prefix-sum-2d（例）、dp-grid（例）、grid（例） |
| abc313_d（1630） | parity（練）、gaussian-elimination（例）、interactive（練） |
| abc327_d（709） | bipartite-graph（例）、graph-modeling（例）、weighted-union-find（練） |
| abc350_g（2058） | small-to-large（練）、dynamic-tree（練）、bitset-speedup（練） |
| abc357_e（1295） | memoized-recursion（練）、scc（練）、functional-graph（練） |
| abc368_f（1180） | spf-sieve（練）、grundy-number（例）、mex（練） |
| abc377_e（1685） | graph-modeling（練）、functional-graph（練）、permutation-cycles（練） |
| abc380_g（1995） | inversion-number（力）、linearity-of-expectation（練）、probability-symmetry（練） |
| abc390_d（1607） | recursive-enumeration（力）、twelvefold-way（練）、bell-number（例） |
| abc398_f（1033） | rolling-hash（練）、z-algorithm（練）、palindrome（例） |
| abc430_e（1109） | rolling-hash（練）、z-algorithm（例）、kmp（練） |
| abc466_e（1027） | difference-sequence（例）、dp-phase（練）、interval（練） |
| agc002_d（2514） | merge-process-tree（例）、partially-persistent-union-find（練）、parallel-binary-search（例） |
| arc081_c（2072） | dp-reconstruction（力）、subsequence-dp（練）、subsequence-matching（力） |
| arc090_b（1452） | graph-modeling（練）、difference-constraints（例）、weighted-union-find（例） |
| typical90_f（—） | lexicographic-greedy（練）、subsequence-dp（練）、subsequence-matching（例） |

C-2　2ページ以上で例題にしている問題（45問）

| 問題 | 例題にしているページ |
| --- | --- |
| abc120_d（1355） | reverse-thinking、union-find-connectivity |
| abc145_d（1009） | counting-bijection、lattice-paths |
| abc147_d（1205） | bitwise-independence、xor |
| abc151_e（1344） | contribution、counting-fix-order |
| abc152_f（1965） | tree-path、inclusion-exclusion |
| abc155_d（1845） | kth-value、kth-and-median |
| abc167_d（754） | doubling、functional-graph |
| abc172_d（963） | contribution、sigma-manipulation |
| abc176_d（1248） | zero-one-bfs、grid |
| abc178_c（653） | complement、counting-mindset |
| abc190_f（1321） | inversion-number、permutation |
| abc212_g（2150） | euler-phi、primitive-root |
| abc213_h（2806） | dp-convolution、online-convolution |
| abc214_d（1341） | tree-edge-contribution、union-find-applications |
| abc223_f（1641） | segment-tree-monoids、bracket-sequence |
| abc229_e（1015） | union-find-connectivity、operation-sequence |
| abc230_d（963） | interval-scheduling、interval |
| abc233_d（726） | prefix-sum-counting、interval |
| abc234_d（503） | priority-queue、kth-and-median |
| abc236_f（1943） | xor-basis、xor |
| abc253_f（1756） | offline-queries、operation-sequence |
| abc253_h（2758） | matrix-tree-theorem、determinant |
| abc280_e（1251） | rational-mod、expected-value-dp |
| abc284_f（1575） | rolling-hash、z-algorithm |
| abc285_d（663） | cycle-detection、graph-modeling |
| abc303_h（2501） | fps-basics、generating-function-counting |
| abc306_e（1268） | top-k-multiset、kth-and-median |
| abc310_d（1368） | recursive-enumeration、dp-counting-dedup、counting-dedup、twelvefold-way、bell-number |
| abc311_e（1293） | prefix-sum-2d、dp-grid、grid |
| abc321_f（1645） | knapsack-undo、fps-basics |
| abc324_f（1815） | fractional-binary-search、dp-decision-binary-search |
| abc327_d（709） | bipartite-graph、graph-modeling |
| abc331_f（1666） | segment-tree-monoids、rolling-hash |
| abc339_f（1716） | hash-safety、randomized |
| abc339_g（1792） | merge-sort-tree、wavelet-matrix |
| abc357_d（970） | modint、geometric-series-mod |
| abc435_e（982） | interval-set、interval |
| abc436_e（958） | permutation-cycles、permutation |
| abc470_f（1604） | permutation-parity、permutation |
| agc002_d（2514） | merge-process-tree、parallel-binary-search |
| arc065_a（930） | reverse-thinking、dp-sequence-partition |
| arc090_b（1452） | difference-constraints、weighted-union-find |
| dp_l（—） | interval-dp、minimax |
| dp_r（—） | dp-matrix-power、matrix-power |
| typical90_bq（—） | mod-pow、counting-basics |

### 付録 D　推移的に冗長な前提（48件。A の前提 B が、A の別の前提 C を経由して届く）

| ページ | 冗長な前提 | 経由 |
| --- | --- | --- |
| meet-in-the-middle | sorting-techniques | binary-search |
| coordinate-compression | sorting-techniques | binary-search |
| exchange-argument | sorting-techniques | greedy-basics |
| dp-basics | complexity-estimation | brute-force |
| dp-order | dp-basics | dp-dag |
| dp-sequence-partition | dp-basics | dp-prefix-sum |
| interval-dp | dp-basics | dp-order |
| bit-dp | bit-operations | bit-full-search |
| broken-profile-dp | dp-state-design | bit-dp |
| dp-speedup-overview | dp-basics | dp-state-design |
| dp-prefix-sum | prefix-sum | imos |
| dijkstra | stl-containers | bfs |
| zero-one-bfs | bfs | dijkstra |
| shortest-path-overview | bfs | dijkstra |
| shortest-path-overview | dijkstra | zero-one-bfs |
| extended-dijkstra | bfs | dijkstra |
| scc | dfs | topological-sort |
| union-find-connectivity | union-find | connected-components |
| euler-path | dfs | connected-components |
| tree-basics | graph-basics | dfs |
| tree-traversal | dfs | tree-basics |
| tree-degree | tree-basics | leaf-first |
| tree-diameter | tree-traversal | tree-distance |
| tree-construction | tree-basics | tree-degree |
| long-path-decomposition | tree-traversal | tree-diameter |
| merge-process-tree | union-find | minimum-spanning-tree |
| tree-isomorphism | tree-traversal | tree-diameter |
| static-top-tree | segment-tree | hld |
| lazy-segment-tree | segment-tree | segment-tree-monoids |
| sweep-line-2d | fenwick-tree | offline-queries |
| exponent-mod | mod-pow | mod-inverse |
| divisor-count-bound | divisor-enum | prime-factorization |
| multiplicative-order | divisor-enum | euler-phi |
| discrete-log | mod-pow | mod-inverse |
| counting-mindset | counting-basics | binomial-coefficient |
| counting-bijection | binomial-coefficient | counting-mindset |
| counting-fix-order | binomial-coefficient | counting-mindset |
| counting-dedup | binomial-coefficient | counting-mindset |
| binomial-identities | binomial-coefficient | lattice-paths |
| twelvefold-way | binomial-coefficient | stars-and-bars |
| inclusion-exclusion | binomial-coefficient | counting-mindset |
| continuous-probability | probability-basics | expectation-tail-sum |
| grundy-number | game-basics | nim |
| game-retrograde-analysis | bfs | game-basics |
| string-automaton-dp | kmp | aho-corasick |
| circle-geometry | geometry-vectors | geometry-precision |
| convex-hull | sorting-techniques | binary-search |
| cpp-views-basics | cpp-range-for | cpp-lambda |

### 付録 E　同じ分野でナビゲーションの後ろにある前提（12件）

| ページ（章） | 前提（章） |
| --- | --- |
| bit-full-search（全探索） | bit-operations（bit 演算） |
| meet-in-the-middle（全探索） | binary-search（二分探索） |
| meet-in-the-middle（全探索） | sorting-techniques（ソートと座標圧縮） |
| coordinate-compression（ソートと座標圧縮） | binary-search（二分探索） |
| kth-value（二分探索） | two-pointers（尺取り法） |
| median-binary-search（二分探索） | prefix-sum（累積和といもす法） |
| doubling（周期とダブリング） | bit-operations（bit 演算） |
| dp-dimension-reduction（DP の考え方） | knapsack-01（列の DP） |
| dp-sequence-partition（列の DP） | dp-prefix-sum（DP の高速化） |
| insertion-dp（状態の形で分かれる DP） | dp-prefix-sum（DP の高速化） |
| proof-patterns（数学の言葉） | gcd-lcm（GCD と合同式） |
| multiplicative-function（素数と約数） | floor-quotient-enum（floor と精度） |

### 付録 F　ページのレベルより2段以上高い印の節（73節）

| ページ（レベル） | 節 |
| --- | --- |
| fractional-binary-search（青） | Dinkelbach 法（発展の紹介） |
| median-absolute（基礎） | 更新しながら中央値を保つ（2 つの優先度付きキュー）（黄） |
| prefix-sum-counting（基礎） | 長さの制限付き（窓の中だけで数える）（青） |
| difference-sequence（水） | 最小回数・可否を差分列で考える（黄） |
| lexicographic-greedy（基礎） | 判定が重い型（青） |
| parity（基礎） | 市松模様の偶奇（青） |
| knapsack-01（基礎） | 個数制限付き（素朴な展開・二進分解・余りごとのスライド最小値）（青） |
| knapsack-01（基礎） | 区間の品物だけのナップサック（分割統治で左右の DP をマージ）（黄） |
| subset-sum（基礎） | 全部分集合についての和（含む部分集合の数を重みにする）（青） |
| dp-grid（水） | 経路上の上位 K 個（K 番目を固定して状態に）（黄） |
| dp-sequence-partition（水） | コストが Monge なら（発展：Monge・Alien DP へ） |
| lcs（水） | LCS の値ごとに数える：DP の DP（内側の DP の1行を外側の状態にする）（黄） |
| interval-dp（青） | Knuth-Yao による O(N^2) 化（発展：Monge のページへ） |
| bit-dp（水） | 素数の使用状況を集合で持つ（黄） |
| tree-dp（水） | 二分探索と組み合わせて判定にする（黄） |
| tree-dp（水） | 部分木の情報をデータ構造で持ってマージする（マージテク）（黄） |
| grid-graph（基礎） | 障害物どうしの8近傍の連結で通れるかを判定する（青） |
| connected-components（基礎） | 座標や値を頂点にして成分を考える（青） |
| small-graph-brute-force（基礎） | 彩色は成分ごとに DFS で塗って探索を絞る（青） |
| graph-modeling（水） | グラフの縮約（Union-Find・SCC で1点にまとめる、次数2の頂点を消す）（黄） |
| shortest-path-dag（水） | 辺を消すと距離が変わるか（黄） |
| bottleneck-path（青） | Kruskal 再構築木でオンラインに答える（発展、木の章の「併合過程の木」） |
| tree-imos（基礎） | パスへの加算（LCA に印を置いて葉から上へ累積する）（青） |
| steiner-subtree（基礎） | DFS 順に並べて隣り合う2点の距離の和の半分（黄） |
| tree-diameter（水） | 中心と半径・直径の個数（黄） |
| tree-edge-contribution（水） | 期待値・特定の色を通らないパスへの応用（黄） |
| tree-path（青） | パスへの一括更新があるなら HL 分解（発展） |
| euler-tour（青） | 逆元がない演算・パスへの一括更新は HL 分解（発展） |
| small-to-large（水） | 森に辺を足すとき小さい方を根付け直す（黄） |
| small-to-large（水） | 部分木ごとの集合の併合（黄、木 DP での使い方は DP の章） |
| small-to-large（水） | DSU on Tree（重い子の結果を残す）（黄） |
| ordered-set（基礎） | ソート順で隣り合う組の集合（2 番目に大きい値の寄与・最小の XOR）（青〜黄） |
| top-k-multiset（水） | slope trick への入口（黄・発展 → DP の章） |
| interval-set（水） | 値つきの区間の分割・統合（黄） |
| monotonic-stack（水） | SWAG：スタック 2 本で作る総積つきキュー（gcd・行列・一次関数の合成の窓）（発展） |
| monotonic-stack（水） | Cartesian tree（最大値で区間を左右に割る再帰を O(N) で作る）（黄） |
| kth-element（水） | 上位 K 個の和（個数と和の BIT 2 本＋二分探索）（黄） |
| segtree-on-values（水） | 左の個数の偶奇で右の読み方が変わる量（ソート後の奇数番目の和）（黄） |
| segtree-on-values（水） | 動的セグ木（必要なノードだけ作る。オフラインなら座標圧縮で済む）（黄） |
| segment-tree-monoids（青） | 動的 DP への入口（発展 → DP の章） |
| sparse-table（青） | 冪等でない演算（2 べきに分けて O(log N)、Disjoint Sparse Table）（発展） |
| mo-algorithm（青） | 時間付き Mo・ロールバック Mo（発展） |
| persistent-data-structures（青） | 接頭辞ごとの版で区間の k 番目・x 以下の個数をオンラインで（発展寄り） |
| merge-sort-tree（青） | 各段に BIT を持たせる（先読みと組む）（発展） |
| exponent-mod（水） | 一般の法：オイラーの定理と、互いに素でないときの一般化（黄） |
| geometric-series-mod（水） | 2×2 行列 [[r, 1], [0, 1]] の累乗による別解（黄） |
| digit-and-mod（水） | 余りを頂点にした最短路（発展。グラフの章へ） |
| prime-factorization（基礎） | 使い分け：1個なら試し割り、多数なら最小素因数の篩、10^18 なら Pollard's rho（発展） |
| spf-sieve（基礎） | 線形篩：各合成数を1回だけ作り、φ・μ などの表を同時に作る（青） |
| harmonic-sum（基礎） | gcd を固定して倍数から数える（約数包除は数え上げの章へ）（青） |
| divisor-count-bound（水） | 高度合成数の列挙（小さい素数の指数が単調に減る形を DFS で）（黄） |
| prime-exponent-vector（水） | 立方因子を除いた正規形・smooth 数の列挙（黄） |
| binomial-precompute（基礎） | 変種：法が素数でない・小さいときはパスカルの三角形で作る（黄） |
| counting-fix-order（水） | 木の上の順番 n!/Π 部分木の大きさ（黄） |
| counting-dedup（青） | 対称性で同一視するときは Burnside の補題（発展） |
| multinomial-coefficient（水） | 一部を先に並べて残りを挿入する（黄） |
| multinomial-coefficient（水） | 区別しない同じ大きさのグループを割る（黄） |
| lattice-paths（水） | 45 度回転・軸ごとに分けて独立にする（発展） |
| permutation-cycles（基礎） | K 回の合成と元に戻る回数（青） |
| permutation-cycles（基礎） | 巡回型ごとの置換の数と全列挙（黄） |
| permutation-cycles（基礎） | 巡回ごとに辞書順最小を決める（黄） |
| coupon-collector（基礎） | 確率が等しくないとき：min-max 包除（発展） |
| probability-dp（水） | 同じ遷移を多数回行うときは行列累乗へ（黄） |
| optimal-strategy-expectation（水） | やり直しがあるときは答えを仮定して二分探索する（黄） |
| minimax（水） | 木の上のゲーム（黄） |
| minimax（水） | 答えを決め打ちして勝敗に直す（黄） |
| hashing-for-sets（水） | 各値が偶数個・k の倍数個かの判定（指数 mod k を乱数で符号化）（黄） |
| z-algorithm（水） | S＋区切り＋T で各位置から S の接頭辞が何文字続くか（DP の材料）（黄） |
| trie（水） | Trie 上の確率・期待値（黄） |
| rotation-transform（水） | 点集合の合同判定：重心をそろえて照合する（黄） |
| manhattan-chebyshev（水） | ひし形の範囲を正方形にして2次元累積和（黄） |
| parsing（青） | 式の部分文字列の総和（発展） |
| acl-reading（基礎） | lazy_segtree の7つの引数：F・mapping(f, x)・composition(f, g) は g の後に f・id（青） |

### 付録 G　`visual` に動く図（ステップ送り・動く図）を割り当てたページ（80）

| 分野 | 件数 | ページ |
| --- | ---: | --- |
| guide | 1 | knowledge-map |
| basics | 6 | binary-search、imos、two-pointers、interval-scheduling、periodicity、doubling |
| dp | 19 | dp-basics、dp-reconstruction、knapsack-01、knapsack-undo、dp-grid、lis、lcs、interval-dp、bit-dp、broken-profile-dp、digit-dp、tree-dp、rerooting、insertion-dp、dp-prefix-sum、dp-segment-tree、inline-dp、cht、slope-trick |
| graph | 10 | dfs、bfs、dijkstra、zero-one-bfs、warshall-floyd、topological-sort、scc、union-find-connectivity、minimum-spanning-tree、max-flow |
| tree | 7 | tree-traversal、leaf-first、tree-degree、tree-diameter、lca、root-path-dfs、euler-tour |
| ds | 6 | monotonic-stack、union-find、fenwick-tree、segment-tree、segtree-binary-search、lazy-segment-tree |
| math | 11 | sigma-manipulation、mod-pow、prime-factorization、sieve-eratosthenes、harmonic-sum、gcd-lcm、ext-gcd、floor-quotient-enum、gaussian-elimination、xor-basis、convolution-ntt |
| comb | 6 | lattice-paths、reflection-principle、inclusion-exclusion、expected-value-dp、game-basics、game-retrograde-analysis |
| string | 2 | z-algorithm、aho-corasick |
| geometry | 2 | argument-sort、convex-hull |
| patterns | 3 | permutation、grid、operation-sequence |
| cpp | 7 | cpp-environment、cpp-integer-overflow、cpp-structured-bindings、cpp-algorithms、cpp-views-basics、cpp-io、cpp-undefined-behavior |

### 付録 H　題名にも別名にも英字の表記がない technique・thinking・overview（49）

brute-force、sorting-techniques、coordinate-compression、binary-search-answer、ternary-search、difference-sequence、periodicity、observation-hub、fix-variable、complement、invariant、reverse-thinking、graph-basics、connected-components、bipartite-graph、small-graph-brute-force、graph-modeling、shortest-path-overview、extended-dijkstra、time-dependent-dijkstra、difference-constraints、segment-tree-graph、min-cut、degree-sqrt、chromatic-number、tree-basics、tree-bipartite、tree-imos、steiner-subtree、leaf-first、tree-edge-contribution、tree-construction、tree-path、global-offset、sigma-manipulation、counting-bijection、counting-dedup、multinomial-coefficient、lattice-paths、mobius-function、counting-labeled-graphs、stirling-first、generating-function-counting、probability-basics、probability-symmetry、continuous-probability、game-mirror-strategy、string-basics、rotation-transform

### 付録 I　同じ別名（または題名）を持つページの組（空白・かっこ・大文字小文字を無視して照合）

81 組。

| 別名 | ページ |
| --- | --- |
| 2彩色 | bipartite-graph、tree-bipartite |
| bitdp | bit-dp、dp-segment-tree |
| bitset | bitset-speedup、cpp-math-functions |
| deque | stack-techniques、stl-containers |
| disjointsparsetable | advanced-ds-catalog、sparse-table |
| dsu | acl-reading、union-find |
| fenwick_tree | acl-reading、fenwick-tree |
| fft | convolution-ntt、fft-ntt |
| flush | cpp-io、interactive |
| garner | crt、fft-ntt |
| k番目に小さい値 | kth-element、kth-value |
| longdouble | cpp-types-literals、geometry-precision |
| lower_bound | binary-search、cpp-algorithms、ordered-set |
| max_right | acl-reading、segtree-binary-search |
| mex | grundy-number、mex |
| min_left | acl-reading、segtree-binary-search |
| mint | acl-reading、modint |
| modint1000000007 | acl-reading、modint |
| modint998244353 | acl-reading、modint |
| next_permutation | bit-full-search、cpp-algorithms |
| ntt | convolution-ntt、fft-ntt |
| popcount | bit-operations、cpp-math-functions |
| static_modint | acl-reading、modint |
| swap | cpp-range-for、permutation |
| sweepline | event-sort、sweep-line-2d |
| undo | root-path-dfs、stack-techniques |
| unordered_map | cpp-container-idioms、stl-containers |
| upper_bound | binary-search、cpp-algorithms |
| xor | bit-operations、xor |
| インタラクティブ | cpp-io、interactive |
| オフライン処理 | offline-queries、operation-sequence |
| オンライン畳み込み | dp-convolution、online-convolution |
| クエリ先読み | event-sort、offline-queries、operation-sequence |
| グループ分けの全列挙 | bell-number、recursive-enumeration |
| スライド最小値 | dp-segment-tree、monotonic-stack |
| ダブルカウントを防ぐ | counting-dedup、dp-counting-dedup |
| バックトラック | dfs、recursive-enumeration |
| ベル数 | bell-number、recursive-enumeration |
| メディアン | kth-and-median、median-absolute |
| 中央値の最大化 | dp-decision-binary-search、median-binary-search |
| 傾きの正規化 | gcd-lcm、geometry-precision |
| 全射の数 | bell-number、inclusion-exclusion |
| 分割統治fft | dp-convolution、online-convolution |
| 切り上げ | cpp-math-functions、integer-division |
| 反転フラグ | global-offset、periodicity |
| 周期 | functional-graph、kmp、periodicity |
| 和の順序交換 | contribution、sigma-manipulation |
| 増加路 | bipartite-matching、max-flow |
| 定数倍 | complexity-estimation、cpp-io |
| 対称性 | observation-hub、probability-symmetry |
| 市松模様 | manhattan-chebyshev、parity |
| 帰りがけ順 | dfs、tree-traversal |
| 平均の最大化 | dp-decision-binary-search、fractional-binary-search |
| 平面走査 | event-sort、sweep-line-2d |
| 括弧の対応 | bracket-sequence、stack-techniques |
| 数の連結 | digit-and-mod、geometric-series-mod |
| 最小添字規則 | counting-dedup、dp-counting-dedup |
| 有理数のmod表現 | mod-inverse、rational-mod |
| 構築 | construction、graph-construction |
| 母関数 | fps-basics、generating-function-counting |
| 比の最大化 | dp-decision-binary-search、fractional-binary-search |
| 比較関数 | cpp-comparators、sorting-techniques |
| 決め打ち二分探索 | binary-search-answer、dp-decision-binary-search |
| 浮動小数点の誤差 | cpp-types-literals、geometry-precision |
| 版の木 | persistent-data-structures、root-path-dfs |
| 発想の型 | observation-hub、thinking-checklist |
| 累積gcd | gcd-lcm、prefix-sum |
| 累積xor | prefix-sum、xor |
| 経路復元 | bfs、dp-reconstruction |
| 経路数 | dp-grid、lattice-paths |
| 経路数に帰着 | counting-bijection、lattice-paths |
| 行きがけ順 | dfs、tree-traversal |
| 行列累乗 | dp-matrix-power、matrix-power |
| 言い換え | counting-bijection、reformulation |
| 計算量の目安 | cheatsheet、reverse-index-constraints |
| 負の数の割り算 | cpp-math-functions、integer-division |
| 辞書順k番目 | binomial-coefficient、dp-reconstruction、lexicographic-greedy |
| 迷路 | grid、grid-graph |
| 部分集合の列挙 | bit-operations、subset-enumeration-dp |
| 順位 | binomial-coefficient、kth-and-median |
| 順列 | counting-basics、permutation |

### 付録 J　問題の時期の偏り（technique・thinking で問題が3問以上のページ）

J-1　問題の6割以上が2019年以前（18）：prefix-sum（基礎、3/5）、bitwise-independence（水、3/5）、reformulation（水、3/5）、invariant（基礎、3/5）、reverse-thinking（水、4/6）、dp-basics（基礎、4/5）、lcs（水、4/6）、digit-dp（水、5/8）、tree-distance（基礎、3/4）、proof-patterns（基礎、3/4）、divisor-enum（基礎、4/5）、prime-factorization（基礎、5/7）、gcd-lcm（基礎、3/4）、binomial-coefficient（基礎、2/3）、counting-bijection（水、3/4）、lattice-paths（水、3/4）、mobius-function（黄、2/3）、string-basics（基礎、4/5）

J-2　2023-09（7問体制）以降の問題が1つもない（63）：complexity-estimation（基礎）、bit-full-search（基礎）、meet-in-the-middle（水）、sorting-techniques（基礎）、coordinate-compression（基礎）、median-binary-search（青）、interval-scheduling（基礎）、lexicographic-greedy（基礎）、dp-basics（基礎）、dp-mod-state（水）、dp-counting-dedup（青）、subset-sum（基礎）、dp-sequence-partition（水）、subsequence-dp（黄）、interval-dp-advanced（黄）、digit-dp-advanced（黄）、dp-prefix-sum（水）、dp-matrix-power（黄）、connected-components（基礎）、zero-one-bfs（水）、topological-sort（基礎）、union-find-connectivity（水）、graph-construction（青）、tree-distance（基礎）、tree-imos（基礎）、lca（青）、tree-path（青）、root-path-dfs（青）、stl-containers（基礎）、priority-queue（水）、union-find（基礎）、proof-patterns（基礎）、mod-arithmetic（基礎）、mod-inverse（基礎）、digit-and-mod（水）、divisor-enum（基礎）、prime-factorization（基礎）、sieve-eratosthenes（基礎）、gcd-lcm（基礎）、gcd-properties（青）、crt（青）、base-conversion（基礎）、floor-quotient-enum（水）、matrix-power（黄）、xor-basis（黄）、binomial-coefficient（基礎）、binomial-precompute（基礎）、stars-and-bars（基礎）、counting-mindset（水）、counting-bijection（水）、counting-fix-order（水）、counting-dedup（青）、multinomial-coefficient（水）、lattice-paths（水）、binomial-identities（青）、mobius-function（黄）、zeta-mobius-subset（黄）、inclusion-exclusion-dp（黄）、cayley-pruefer（黄）、counting-labeled-graphs（黄）、string-basics（基礎）、rotation-transform（水）、circle-geometry（青）

### 付録 K　問題の要約が手法名だけ・仮のもの（「§2.3.8 の分類」「執筆時に確かめる」「〜の基本形」「をそのまま使う」などを含む。47件）

| ページ | 問題 | 要約 |
| --- | --- | --- |
| brute-force | abc469_d（練） | 考える候補を 2 つに絞ってから数える最近の D（00 §2.3.8 の分類。内容は執筆時に確かめる） |
| recursive-enumeration | abc473_d（練） | DFS（再帰）による全列挙で解く最近の D（00 §2.3.8 の分類。内容は執筆時に確かめる） |
| binary-search-answer | abc457_d（練） | 最小値を上げる操作の問題を、答えの二分探索で解く最近の D（00 §2.3.8 の分類。内容は執筆時に確かめる） |
| binary-search-answer | abc463_d（練） | 間隔を最大化する問題を、答えの二分探索と貪欲な判定で解く最近の D（00 §2.3.8 の分類） |
| prefix-sum | abc479_d（練） | 左右からの累積 min を前計算して答える最近の D（00 §2.3.8 の分類。内容は執筆時に確かめる） |
| prefix-sum-counting | abc473_e（練） | 累積和の余りで K の倍数の区間を扱い、貪欲と組み合わせる最近の E（00 §2.3.8 の分類） |
| prefix-sum-2d | abc461_d（練） | 和がちょうど K の部分長方形を数える。行の組を固定し、2 次元累積和と尺取りで数える（00 §2.3.8 の分類） |
| prefix-sum-2d | abc465_f（力） | 6 次元の累積和と包除で領域の和を求める（00 §2.3.8 の分類） |
| imos | abc462_d（練） | いもす法で解く最近の D（00 §2.3.8 の分類。内容は執筆時に確かめる） |
| event-sort | abc478_d（練） | 区間のクエリをイベントソートで処理する最近の D（00 §2.3.8 の分類。内容は執筆時に確かめる） |
| greedy-basics | abc459_d（練） | 隣り合う文字が異なるように並べる。出現回数の上限を確かめ、多い文字から並べる貪欲（00 §2.3.8 の分類） |
| exchange-argument | abc467_f（力） | 交換論法で順序を決めた貪欲を、座標圧縮したセグ木で速くする（00 §2.3.8 の分類） |
| periodicity | abc452_e（練） | 剰余の周期性と累積和で総和を求める最近の E（00 §2.3.8 の分類。内容は執筆時に確かめる） |
| observation-hub | abc462_e（練） | 対称性で場合を減らして最小化する最近の E（00 §2.3.8 の分類。内容は執筆時に確かめる） |
| reformulation | abc479_f（力） | 隣接 swap の回数に言い換え、転倒数で数える最近の F（00 §2.3.8 の分類） |
| fix-variable | abc458_e（練） | 仕切りの位置を固定して二項係数で数える最近の E（00 §2.3.8 の分類） |
| fix-variable | abc453_e（力） | 人数を固定して場合を分け、二項係数と累積和で数える最近の E（00 §2.3.8 の分類） |
| contribution | abc468_e（練） | 平均の総和を、主客転倒（寄与）と前計算で求める最近の E（00 §2.3.8 の分類） |
| complement | abc455_e（練） | 条件を満たす部分文字列を、余事象・包除原理・累積和で数える最近の E（00 §2.3.8 の分類） |
| reverse-thinking | abc477_d（練） | クエリを逆順に処理して解く最近の D（00 §2.3.8 の分類。内容は執筆時に確かめる） |
| reverse-thinking | abc466_f（力） | 操作を逆から考え、同じ長さのものをまとめて処理する最近の F（00 §2.3.8 の分類） |
| dp-basics | abc240_c（練） | 毎回 a_i か b_i 進んで、ちょうど X に着けるか（可否判定の基本形） |
| dp-basics | abc129_c（練） | 壊れた段を避けて1段か2段ずつ上る方法の数（数え上げの基本形） |
| knapsack-01 | dp_d（例） | 重さの合計が W 以下で価値の和の最大（0-1 ナップサックの基本形） |
| digit-dp | abc465_e（練） | 使った数字の集合と 3 で割った余りを状態にした桁 DP（2026 年の E） |
| insertion-dp | abc468_g（練） | 制約のついた順列を挿入 DP で数える（2026 年の G） |
| inline-dp | abc480_g（力） | DP の遷移を、遅延セグ木と単調スタックでまとめて更新する（2026 年の G） |
| bfs | abc007_3（例） | 迷路の最短手数を求める。グリッド BFS の基本形 |
| scc | practice2_g（例） | SCC を求めてトポロジカル順に出力する（ACL の scc_graph の使用例） |
| two-sat | practice2_h（例） | 各旗を2か所のどちらかに置き、近すぎる組を禁止する（ACL の two_sat の使用例） |
| max-flow | practice2_d（例） | 市松模様で二部グラフにして 1×2 のタイルを最大数置く（ACL の mf_graph の使用例） |
| max-flow | tessoku_book_bp（練） | 最大流の基本形（鉄則本 A68） |
| project-selection | tessoku_book_eo（練） | 燃やす埋めるの演習（鉄則本 B68） |
| bipartite-matching | tessoku_book_bq（練） | 二部マッチングの基本形（鉄則本 A69） |
| min-cost-flow | practice2_e（例） | 各行・各列 K 個までのマス選びで和を最大化する。コストを「大きい値 − a」にする（ACL の mcf_graph の使用例） |
| multiplicative-order | abc335_g（力） | A_i^k ≡ A_j となる組の数を、位数で分類して数える |
| floor-sum | practice2_c（例） | ACL の floor_sum をそのまま使う |
| convolution-ntt | practice2_f（例） | ACL の convolution をそのまま使う |
| counting-bijection | arc058_b（練） | 禁止された長方形を避ける格子路を、境界を越える位置で分類して数える |
| counting-labeled-graphs | abc180_f（練） | 連結成分がパスかサイクルのグラフを、頂点 1 を含む成分の大きさで分類して数える |
| aho-corasick | abc268_h（力） | S の文字を最少個数だけ * に変え、どの T_i も含まないようにする。走査して一致したら終端を * にして状態を根に戻す貪欲（裏付けは検索結果の要約だけなので、執筆時に確かめる） |
| geometry-vectors | abc472_f（力） | 多角形の重心を扱う問題で、幾何と累積和を組み合わせる（research/00 §2.3.8 の分類による。執筆時に内容を確かめる） |
| geometry-precision | abc467_d（練） | 垂直二等分線の交差と直線の正規化を使う易しい幾何（research/00 §2.3.8 の分類による。執筆時に内容を確かめる） |
| argument-sort | abc479_g（力） | 偏角ソートと累積和で、直線とのマンハッタン距離の和を扱う（research/00 §2.3.8 の分類による。執筆時に内容を確かめる） |
| manhattan-chebyshev | abc476_f（練） | チェビシェフ距離を分解し、四隅から DP する（research/00 §2.3.8 の分類による。執筆時に内容を確かめる） |
| manhattan-chebyshev | abc457_g（力） | 45度回転してから、増加部分列への分割（Dilworth の定理）を貪欲に求める（research/00 §2.3.8 の分類による） |
| advanced-geometry | abc478_g（例） | 分割統治で凸包を作り、ミンコフスキー和で合成する（research/00 §5.2 の分類による） |

### 付録 L　`related` を id に解決すると同じページが2回以上出るページ（21）

| ページ | 重複する行き先（元の書き方） |
| --- | --- |
| reverse-index-constraints | complexity-estimation（complexity-estimation・amortized-analysis） |
| thinking-checklist | observation-hub（observation-hub・experiment）；reformulation（reformulation・independence） |
| debugging-checklist | cpp-undefined-behavior（cpp-undefined-behavior・cpp-debug-build）；cpp-io（cpp-performance・cpp-io） |
| library-design | acl-reading（acl-reading・acl-segtree-template） |
| doubling | lca（binary-lifting-tree・lca） |
| reformulation | manhattan-chebyshev（axis-independence・manhattan-chebyshev） |
| complement | counting-mindset（counting-complement・counting-at-most-difference） |
| tree-dp | small-to-large（small-to-large・dsu-on-tree） |
| dp-segment-tree | monotonic-stack（sliding-window-minimum・monotonic-stack） |
| dp-matrix-power | matrix-power（semiring-matrix・adjacency-matrix-power） |
| stl-containers | cpp-container-idioms（cpp-container-idioms・cpp-iterators） |
| segment-tree-monoids | matrix-power（matrix-power・semiring-matrix） |
| sqrt-decomposition | complexity-estimation（amortized-analysis・complexity-estimation） |
| proof-patterns | observation-hub（pigeonhole・experiment） |
| integer-division | cpp-integer-overflow（cpp-integer-overflow・cpp-int128） |
| circle-geometry | ternary-search（ternary-search・convex-function-basics） |
| advanced-geometry | cht（cht・li-chao-tree） |
| permutation | insertion-dp（insertion-dp・hakone-ekiden-dp） |
| kth-and-median | kth-value（kth-value・k-best-enumeration） |
| grid | bfs（bfs・multi-source-bfs）；manhattan-chebyshev（axis-independence・manhattan-chebyshev・diagonal-coordinates）；parity（parity・checkerboard-parity） |
| operation-sequence | union-find-connectivity（offline-reverse・union-find-connectivity） |

