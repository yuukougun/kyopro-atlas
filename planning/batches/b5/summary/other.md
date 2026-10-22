# b4・b5 のほかのページ・catalog・ツールへの提案と未解決の点

出どころは各 `<id>.md` の「未解決の点」「front matter・catalog への提案」「メインへの提案」「メインに決めてほしい点」と、検証の指摘への対応で採らなかったもの。台帳は ledger.md、リンクの張り替えと内容の重なり・相手のページの直しは handoff.md、手引きは style.md、練習の不足は candidates.md。

## 1. front matter・生成部分への提案（メインが反映）

執筆者が変えられない項目（summary・signs・aliases・related・verify・frequency_evidence と、要点の囲みとの対応）。b1 の決定（other.md §1.5）のとおり、表記の直しと related の追加は反映し、内容の直しは根拠を確かめてから。frequency_evidence は根拠の問題がページと関係しないものを外す（frequency の値は変えず工程 10 で見直す）。

### 1.1 summary・signs・要点

| ページ | 項目 | 提案 | 根拠・経緯 |
| --- | --- | --- | --- |
| continuous-probability | summary | 「N 個の一様乱数の小さい方から K 番目の期待値は K/(N+1)」に（検証の指摘 4） | 本文と合わせる |
| dynamic-dp | signs の 2 つ目 | text を `'列の区間 [l, r) だけで DP をしたときの答えを、クエリごとに求める'` に（要点・本文の半開区間とそろえる。§6） | 検証の指摘 1 |
| dynamic-tree | summary | 「償却 O(log N)」を「ならし O(log N)」に（付録 A。level-advanced・tree/index・kind-data-structure の一覧も gen_site で追従） | 検証の指摘 8 |
| general-matching | summary・signs（constraint） | 「N ≤ 16 程度なら bitDP で足りる」「N ≤ 16 程度の一般グラフでペアを作る」の 16 を 20 に（O(2^N N) は N = 20 で約 2×10^7。要点の計算量・#bitdp と食い違う）。要点の「何ができるか」「いつ使うか」も合わせる | 検証の指摘 2 |
| k-shortest-paths | summary・signs | 「歩道」をウォークに。summary 案：始点から終点への経路のうち、短い方から K 番目の長さを求める。ウォークなら各頂点を K 回まで取り出すダイクストラで求まり、単純パスは Yen、ウォークの高速な列挙は Eppstein の方法を使う。signs 案：{type: phrase, text: K 番目に短い経路・ウォークの長さ}（要点は本文で直した。lists・llms.txt に「歩道」が 3 か所出ている） | 検証の指摘 2・§14-22 |
| knowledge-map | summary | 「前提をすべて理解した次の候補」を「直接の前提をすべて理解した次の候補」に（map.js 417 行の凡例の文言も同じ言い換えにするとよい） | 検証の後の提案 |
| online-convolution | summary | 案：多数の多項式の積を、半分ずつに分けて（または次数の小さいものから）2つずつ掛けて O(N log² N) で求める。dp[i] が dp[0..i−1] と既知の列の畳み込みで決まるときは、左半分を確定させてから右半分へ寄与を足す分割統治で求める。 | 検証の指摘 5 |
| permutation | summary | 「i → P_i の矢印のサイクル」を「i → P_i の矢印でできる巡回」に（§7「置換は巡回と言う」。index/patterns・lists/kind-counting も gen_site で追従） | 執筆者 |
| reverse-index-signs | summary | 「問題文の言い回しや求めるもの、立てた式の形から、疑う手法とページを引ける。同じ言い回しに複数の手法が当たるときの見分け方も添える。」に（要点に合わせる） | 検証の指摘 8a |
| steiner-tree | summary・要点 | summary の計算量を `O(3^K N + 2^K (N + M) log N)` にそろえ（complexity と字面を合わせる）、summary と要点の「端点の集合」を本文の語「指定頂点の集合」に（両方を一緒に直す）。要点の 1 文目は summary から計算量を除いた形にした（食い違いと見るなら戻してよい） | 検証の指摘 8 |
| term-index | summary・要点 | 「全ページの題名と別名から生成し」を「全ページの題名・別名・ACL の名前から生成し」に | 検証の指摘 3 |
| spanning-tree-advanced | complexity・要点 | 「併合できるヒープ」を advanced-ds-catalog の見出しに合わせて「併合可能なヒープ」に | 検証の直しから |

### 1.2 aliases

| ページ | 提案 | 根拠 |
| --- | --- | --- |
| advanced-geometry | aliases と別名の行から「円の反転」を外す（本文に扱いがない）。扱うなら circle-geometry など円のページの aliases へ | 検証の指摘 10 |
| advanced-ds-catalog | `Sqrt Tree`・`pairing heap`・`ランダム化ヒープ`・`permutation tree`・`64 分木` を足す（本文の表と節で扱う。term-index から引けるように） | 執筆者 |
| k-shortest-paths | 「2 番目に短い経路」「第 K 最短路」を足す | 執筆者 |
| mo-algorithm・sqrt-decomposition | 「クエリ平方分割」（Mo）と「クエリの平方分割」（平方分割）が 1 字違いで別のページに当たる。(a) mo-algorithm の aliases から「クエリ平方分割」を外す（handoff-b2b3 の 189 行目の提案と同じ）、(b) 両方の別名にして「複数のページに当たる語」に載せる、のどちらかを決める。(a) にしたら term-index の shared-terms の手書きの注記「後者は Mo's algorithm の別名で」を「Mo's algorithm もクエリを平方分割する方法と呼ばれることがある」に直す | term-index |
| fenwick-tree | 「Fenwick Tree」を足す（題名「BIT（Fenwick Tree）」のかっこの中の名前が索引にない。全ページで調べて、ほかに索引にないのは functional-graph の「出次数 1 のグラフ」だけ） | term-index |
| multiplicative-function | 「Meissel-Lehmer」は素数計数の方法の名前として引く読者がいるので残した（本文では触れない）。外すかはメイン | 執筆者 |
| static-top-tree | 「重軽再帰 DP」は abc311_h の手法名で Static Top Tree や動的木 DP の別名ではない。外すか、#heavy-path-dp の最後の段落への誘導として残すか（abc311_h を tree-dp-square などへ移すなら一緒に移す。ledger.md） | 執筆者 |

### 1.3 related・prerequisites（b1 の決定で反映する）

| ページ | 足す related | 根拠 |
| --- | --- | --- |
| cdq-divide-and-conquer | advanced-ds-catalog・inversion-number | 本文の代わりの手の表と仕組みの説明でリンク |
| grid | konig-theorem（#make-bipartite）・connected-components・union-find-connectivity・dijkstra・minimax（#states）・construction | 本文の節からリンク。外すものはない（sweep-line-2d・inclusion-exclusion-dp・operation-sequence も使った） |
| k-shortest-paths | persistent-data-structures | Eppstein の永続ヒープで #path-copying にリンク |
| kth-and-median | greedy-priority-queue（#k-best の持ち主）・lexicographic-greedy（#kth の持ち主）・parallel-binary-search（区間の K 番目をオフラインで） | 本文でリンク |
| parallel-binary-search | wavelet-matrix（persistent-data-structures も本文でリンク） | Range Kth Smallest を並列二分探索でも解けると書いた |
| reverse-index-constraints | method-comparison・cpp-container-idioms#member-lower-bound | 本文の「見た目より遅い」から参照 |
| spanning-tree-advanced | bottleneck-path・functional-graph・lca | 本文でリンク |
| subsequence-and-substring | fix-variable（#fix-middle）・kmp（#matching） | 本文でリンク |
| thinking-checklist | global-offset・interval-scheduling・inclusion-exclusion（related の stl-containers・game-basics は別の節で使うので残した） | 検証の直しで本文に加えた |
| library-design | related の stress-testing を stress-testing#procedure にするか（problem-sets#verify-sets も） | 本文は張り替え済み |

### 1.4 verify・frequency_evidence・sections の title

| ページ | 項目 | 提案 |
| --- | --- | --- |
| offline-dynamic-connectivity | verify | `dynamic_graph_vertex_add_component_sum` を足す（rollback-union-find は既に持つ。本ページは練習に同じ問題を置いた） |
| rollback-union-find | verify | コード片が確かめているのは persistent_unionfind の形なので、`verify: [persistent_unionfind, dynamic_graph_vertex_add_component_sum]` にするか（catalog 由来のため変えていない） |
| wavelet-matrix | verify | static_range_frequency・static_range_sum_with_upper_bound・rectangle_sum を足す（本文の Library Checker の節に載せた。どれも静的で解ける） |
| slope-trick | frequency_evidence | 「recent 1（abc458_g）」は台帳では monge の練習で、Slope Trick で解ける裏付けがない。外して frequency を再判定する（monge は abc458_g を slope-trick の練習の候補としたので食い違い。ledger.md §3） |
| online-convolution | frequency_evidence | 「recent 1（abc462_g）」の abc462_g は inclusion-exclusion の力試しで「FPS で項をまとめる」。このページの手法（積の分割統治）を使うかは確かめていない |
| tree-isomorphism | frequency_evidence | 「古い ABC 1 問」がどの問題か分からない。「recent 0・前提として届くページなし・ABC で本質的に使う問題なし」に直すか（本文と research 04-tree §4.29 に合わせる） |
| subsequence-and-substring | sections の title | 節 count-occurrences の title の「（dp-state-design）」は中身の持ち主が dp-phase#matched-prefix なので「（dp-phase）」に（anchor は変えない。本文は両方へリンクした） |
| operation-sequence | sections の title | catalog の title から括弧の id を落としたもの（paint・offline・online・versions）と残したもの（global-ops など）が混ざる。そろえるか（検証の指摘 10 を保留） |
| two-sat | sections の title | 骨格の「ACL では（two_sat の囲み）」を、自作の要点と Library Checker を含むために変えた（anchor は同じ。§15-3 の範囲で、検証役も採るのが妥当とした） |
| permutation | sections の title | catalog の lexicographic の title の「（binomial-coefficient, bit-full-search）」は front matter で落ちている。front matter が正なので変更は不要と考える（記録） |
| grid | sections の title | rows-cols の title は catalog では手法の id が付いていたが骨格にない。そのままにした（記録） |
| interval | sections の title | 60 字を超える title（offline・online-updates）は検証で短くした（§14-12。docs/index は gen_site で作り直す） |
| divisors-and-multiples | sections の title | harmonic の title を「1〜M の各数の約数・倍数を集める → 倍数を回す調和級数（harmonic-sum）」に直した。docs/index/patterns.md は gen_site の再生成で追随 |
| roadmap | related | `atcoder-system#difficulty-by-position` は執筆時に節がなかったが、今は atcoder-system に節がある（解決済み。本文も直しで張った） |

## 2. ほかのページ・メインに決めてほしいこと

| ページ | 点 | 提案したページ |
| --- | --- | --- |
| static-top-tree | abc311_h を練習から tree-dp-square などへ移すか（移すなら aliases の「重軽再帰 DP」と #heavy-path-dp の最後の段落も） | static-top-tree |
| spanning-tree-advanced | keyence2019_e を example にするか practice にするか（ledger.md） | spanning-tree-advanced |
| contest-strategy・atcoder-system | difficulty-by-position の値の持ち主（atcoder-system に決めるなら contest-strategy の節を 3〜4 文とリンクに縮める。検証の指摘 8 を保留） | contest-strategy |
| contest-strategy | abc470 の E・F を ID で出してよいか（台帳にある） | contest-strategy |
| graph-modeling | 表の代表の abc414_g（diff 3020、台帳の summary が仮）を「—」にするか | graph-modeling |
| graph-modeling | 次数 1・2 の頂点を消す縮約の持ち主をここにするか degree-sqrt などへ移すか（handoff.md §2） | graph-modeling |
| advanced-ds-catalog | hub の表で行ごとにリンクを重ねる形（sweep-line-2d の 47・49 行など）を例外として認めるか（検証の指摘 8 の一部を採らなかった） | advanced-ds-catalog |
| advanced-ds-catalog | 析合木の代わりの手に対応する節を lazy-segment-tree-patterns に足すか | advanced-ds-catalog |
| rollback-union-find・offline-dynamic-connectivity | 手順と頂点加算の工夫の持ち主（handoff.md §2） | 両ページ |
| chromatic-number | 確認問題を `## 確認問題 {#quiz}` へ移す（§14-11 で決まっている。検証の指摘 5 を「方針待ち」として保留中） | chromatic-number |
| tree-ratio-greedy | Library Checker の問題を「計算量と自作するときの要点」の節の中から、練習問題の節の小見出し「Library Checker」へ移す（§15-5 で決まっている） | tree-ratio-greedy |
| stirling-first | Library Checker の 3 問は直しで練習問題の小見出しへ移した（記録） | stirling-first |
| flow-lower-bounds | 練習の Minimum Cost b-flow は下限付きの最小費用流でページの範囲（最大流）より広い。重すぎるなら外すか参考だけに移す。負の流量しかなれない入力はページの作り方では「流せない」（Luzhiled の min_flow は負の流量も返す） | flow-lower-bounds |
| lagrange-interpolation | Library Checker の Sum of Exponential times Polynomial は r ≠ 1 で補間以外（母関数）が要る。verify に載せたままでよいか（検証は今のままでよいとした） | lagrange-interpolation |
| advanced-geometry | 練習の Library Checker に Line Add Get Min（cht の検証問題）を双対として載せた。重複が気になるなら外す | advanced-geometry |
| method-comparison | 「数の扱い」に二項係数の計算方法の表を足した（catalog の指示にはないが research/07 §6.2 にある）。不要なら外す。フローチャートは Mermaid（catalog の visual は priority 2 の static）。SVG が要るなら後で描く | method-comparison |
| problem-sets | 指摘 5 の出典（ei1333 の Hu-Tucker のページ）を参考に足すか（本文は「満点に O(N log N) が要る」と断っただけ） | problem-sets |
| thinking-checklist | アルゴリズム×数学の目次の出典を kumonosu から gihyo.jp の書籍ページに替えるか（検証の指摘 14(b)。gihyo.jp に 5 章の節の題名が載っているかを確かめられなかった） | thinking-checklist |
| how-to-use | 書き出し・読み込みの欄（`<div class="kp-progress-io"></div>`）を使い方のページとロードマップの 2 ページに置いた。2 ページに置いた動作は実機で確かめていない | how-to-use |
| how-to-use・roadmap | claude.ai の Projects の指示は v0.2（仮）で工程 9c で確定する。確定したら claude の節（頼み方の定型文・ヒントか解説か・原因の 4 分類）を見直す | how-to-use |
| debugging-checklist | 参考の節に自サイトのページを「数値の確かめ先」として挙げた。参考を外部の資料だけに限るなら消す（style.md） | debugging-checklist |
| interval | monotonic-stack のページの練習に abc189_c が載っていない（handoff.md §6・ledger.md） | interval |
| xor | 表の最後の行（列全体を同じ値で XOR したものを探す → KMP 法の例題 ABC150 F）は sections に節を持たない（記録） | xor |
| reverse-index-signs | 確認問題の答えが生成の表の文言（fenwick-tree・cht の signs）に頼る。signs の文を変えたら確認問題も直す。群の説明は gen_site.py の PHRASE_GROUPS に合わせた | reverse-index-signs |
| knowledge-map | 本文に `?field=`・`?focus=`・`?view=all` の URL の引数を書いた。map.js の引数の名前を変えるときは本文も直す | knowledge-map |
| roadmap | 黄の練習の問題集の例が典型90 の★7 だけと薄い。EDPC・鉄則本などの帯の対応を problem-sets の値で確かめてから足す。生成ブロックの見出し「G 問題（黄の帯）」の扱い | roadmap |
| stern-brocot | 作業中に front matter を書き換えるスクリプトの誤りで担当ページを一度空にし、git の HEAD の骨格から作り直した（ほかのファイルには触れていない。記録） | stern-brocot |

## 3. 道具への提案

| 道具 | 提案 | 提案したページ |
| --- | --- | --- |
| gen_site.py の実行 | reverse-index-signs の signs-shape で dp-speedup-overview が「（準備中）」のまま、882〜887 行の kth-and-median も「（準備中）」。title を直したページ（divisors-and-multiples・interval・two-sat ほか）の docs/index の行、summary を直したページの lists。全ページ draft になったので流せば直る | reverse-index-signs・kth-and-median ほか |
| gen_site.py（how-to-use の新しいブロック） | how-to-use に `<!-- gen:begin fields -->`（章の構成）・`lists`（色ごとに学ぶとき）・`version`（Claude が書く索引の版とサイトの版を見比べる）を空で置いた。--list-blocks で置き場所の決まっていないブロック。中身を入れるか、置かないならマーカーと前後の文を直す。lists は検証で箇条書きの最後へ移した | how-to-use |
| gen_site.py（problem-sets ブロック） | 使っていない問題集には見出し `{#problem-sets-<cid>}` ができず、生成のたびに anchor が消えうる。使っていない問題集にも見出しと「まだない」の 1 行を出すと安定する。ABC・ARC・AGC 以外の本番のコンテスト（KEYENCE2019・CODE-FESTIVAL-2017-QUALB など）を「そのほかの本番のコンテスト」の `####` にまとめると読みやすい | problem-sets |
| gen_site.py（signs-constraint の帯） | 帯の分け方がサインの最大の数によるので、意味とずれる行がある：「上限が 10 以下」に complexity-estimation の「N ≤ 8 / 20 / 40 / … / 10^18」、「上限が 10^12 以下」に状態数 10^6〜10^7（extended-dijkstra）・NW ≤ 10^7〜10^8（knapsack-01）・O(N√N)（sqrt-decomposition）・−10^9 ≤ A_i（prefix-sum-counting）・W ≤ 10^9（dp-dimension-reduction）、「上限が 500 以下」に matrix-power（K が 10^9〜10^18）、「2×10^5 前後」に multiplicative-order（√P）。N（列の長さ・回数）の上限で分けるか、値の上限のサインは「数の上限で分けられないもの」へ回す規則に | reverse-index-constraints |
| gen_site.py（骨格の生成） | signs-constraint のブロックが要点の直後に置かれていた。sections の pages-by-constraint の位置に置く（今回は手で移した） | reverse-index-constraints |
| gen_site.py（terms-shared） | 表記の近い語（「の」・空白・中黒・ハイフンを除くと同じになる語）を別のページが持つ組を候補として出すと手書きの注記の漏れを防げる（今の 353 ページでは「クエリの平方分割」と「クエリ平方分割」の 1 組だけ） | term-index |
| gen_site.py（索引の読み） | 五十音順で漢字で始まる語（約 1240 行）が読みの順に並ばない（文字コード順）。読みを持たせるなら front matter に `reading` を足す案（急がない） | term-index |
| gen_site.py（知識マップ） | 全体の図の Mermaid の本数はページの前提を直すと古くなる。生成ブロック（例 `field-edges`）にするか、定期的に数え直すか | knowledge-map |
| map.js | 次の候補の判定は直接の前提だけ（isCandidate）。祖先すべてを条件にしたいなら map.js の変更。「+水青」の印は upperLevels の join("") で区切りなしに連結されるので「+水・青」に。417 行の凡例の文言（§1.1） | knowledge-map |
| progress.js | 保存を拒否する設定のときの注意「このページを開いている間だけ」を「タブを閉じるか再読み込みするまで」に直すか（instant navigation ではページを移っても記録が残る） | how-to-use |
| fix_problems（--check） | 台帳の pages にある役割の問題がページにない（abc197_c の bit-full-search、abc189_c の monotonic-stack）を検出できると、食い違いが残らない | xor・interval |
| check_pages | advanced-ds-catalog が stub の間は節へのリンクを許さなかった（spanning-tree-advanced）。全ページ draft になったので今は影響なし（記録） | spanning-tree-advanced |
| check_noai | cnblogs の mlystdcall 氏の記事で時間切れ（資料から外した） | cdq-divide-and-conquer |
| Library Checker の問題一覧 | library-design の生成ブロックの表の 6 問（aho_corasick・minimum_enclosing_circle・minimum_steiner_tree・range_add_range_min・static_range_sum_with_upper_bound・sum_of_multiplicative_function）は categories.toml にない。judge.yosupo.jp で開けるか（各ページの verify の持ち主） | library-design |
| tools/ のスクリプト | 数の目安・コンテストの集計を再計算するスクリプトを tools/ に置くか（style.md §1） | cheatsheet・contest-strategy |
| interfaces §3（表示名） | 問題集の問題の label が `PRACTICE2 A. Disjoint Set Union` のように大文字の contest id になる。表示名に practice2 → `ACL Practice`、aalc001 → `AAL001`、ndpc → `NDPC`、fps-24 → `FPS24`、game-24 → `ゲーム24` などを足すか（§15-10 で表示名は変えない決まりなので、変えるなら全ページ一括） | problem-sets |

## 4. ユーザーに確かめてもらうとよいこと（atcoder.jp を開けないため）

| 点 | 内容 | 提案したページ |
| --- | --- | --- |
| AtCoder のコンパイルオプション | decisions.md の一覧（特に `-ftrivial-auto-var-init=zero`・`-fmodules`、traP の記事にある `-fopenmp` の有無）が公式の言語の一覧で確かめたものか。cpp-environment の参考の 1 行（「公式の言語の一覧による」）はその前提で書いた | cpp-environment |
| AtCoder の新ジャッジのスタックの上限 | 2023-06 の reika727 の記事の 1 GiB だけを書いた。コードテストで stack-limit.cpp を動かせば分かる | cpp-environment |
| ジャッジの CPU が FMA・AVX2 を持つか | 本文は「持てば同じことが起こりうる」 | cpp-environment |
| 1 秒あたりの演算回数 | 手元（i7-13700・WSL2）の実測。AtCoder のコードテストで ops-benchmark.cpp に n = 100000000 を与えれば判定機での値が分かる | reverse-index-constraints |
| レートの計算式の変更 | 第三者の解説（2019 年の更新）による。初参加者の内部レートの暫定値を 800 から 1200 に変えた公式のお知らせ（atcoder.jp/posts/1592）が検索結果に出たが開いていない | atcoder-system |
| ペナルティの細則 | CE を数えるか・解けなかった問題の誤答を数えないか（glossary は「最終的に AC した問題の誤答だけ」） | atcoder-system・contest-strategy・debugging-checklist・glossary |
| 生成 AI のルール 20261014 版 | 条文（AHC の扱い・AWC が対象か）。「AHC GenAI Rules Trial Contest 2026」（2026-10-15）があり、AHC 向けの試行があるらしい | atcoder-system・contest-strategy・how-to-use |
| ADT・AWC が Unrated か | AtCoder Problems のデータの rate_change だけで確かめた | problem-sets |

## 5. 未解決の点（ページごと。検証で解決したものは除いた）

事実の確かめが残るもの。本文はぼかした書き方か条件付きで書いてある。

- **advanced-geometry**：ABC478 G の O(N log² N) は自分の見積もり（本文は直しで「程度」を外した）。半平面交差の係数の 3 次の積が座標 10^9 で `__int128` に収まるかは断定していない。動的な凸包の作り方は出典（ikatakos は x をキーにした添字付きの集合で二分探索）と違う
- **alien-dp**：abc355_g の「区間のコストが Monge」は kmjp が証明なしに使う。取り消し付きの貪欲の証明を日本語で書いた資料が見つからない。Library Checker に Alien DP の問題はない
- **auxiliary-tree**：ABC340 G の「誘導部分グラフが木になる」は kmjp の要約と解答コードからの判断（問題文は見ていない）。DP は手で対応を確かめたが提出はしていない。KEA は "auxiliary tree" の呼び名を推奨しない（導入で一言）
- **balanced-bst**：iwiwi 氏のスライド（SlideShare）はドメインと章の有無を確かめていないので載せなかった
- **binomial-prefix-sum**：例題の N の上限は数値で確かめていない。この手法を一般に説明した日本語の記事が見つからない
- **burnside-lemma**：ABC198 F の S の上限（10^18 程度）は推定。ABC428 G の「美しさが 2 以上」は解説の記述による
- **chromatic-number**：分枝の計算量 1.47^N・1.38^N は特性方程式の根の手計算。2 つの法がどちらも 0 になる誤判定の確率は評価していない
- **cht**：EDPC Z の h・C の上限は確かめていない。遷移元が範囲に限られるときの具体的な方法（Li Chao Tree をセグ木に重ねるなど）は書いていない。動く図（data-viz="cht-envelope"、config 例 `{"lines": [[2,1],[0.5,6],[-1,9],[-0.5,10]], "queries": [1,3,5]}`、置き場は #lower-envelope の静的な図の直後）を作るなら動く図のバッチで
- **continuous-probability**：AGC021 B の「一直線に並ぶときは両端が 1/2 ずつ」「辺の途中の点は確率 0」は自分で導いた
- **determinant**：互除法の掃き出しの O(N^3 + N^2 log m) は自分の議論（第三者の明記なし）。Library Checker の任意 mod で N = 0 の試験があるかは未確認。互除法の掃き出しの日本語の記事が見つからない
- **dilworth-path-cover**：重み付きの反鎖（ABC354 G）の「重みの総和 − 最大流」は 2 つの解説の構成をそのまま書いた（証明なし）
- **dynamic-dp**：Static Top Tree の説明は研究資料に基づく（static-top-tree との照合は handoff.md §6）。メモリの見積もり約 420 MB は計算値
- **dynamic-tree**：LCT による abc350_g の解き方は自分の推論。expose のならし O(log N) と splay 以外で O(log² N) は Sleator–Tarjan の結果として書いた（証明は読んでいない）。Top Tree が直径を保てるのは ei1333 の Library の依存関係から
- **fft-ntt**：「mod 2^64 では 30 bit 前後の素数で 5〜6 個」は見積もり（具体的な素数の組は書いていない）。複素数の FFT の誤差は素朴な実装 1 つでの観測値
- **fps-basics**：ABC318 Ex の exp による解き方は記事になく、自分で導いて N ≤ 5 の全探索で確かめた。コード片の exp は定数倍が重く、Library Checker の N = 5×10^5 で間に合うかは試していない。「ABC では主に difficulty 2200 以上の G・Ex」は台帳からの見当
- **general-matching**：乱数の Tutte 行列で階数が保たれる確率 1 − N/p は Schwartz-Zippel からの一般的な導き。abc412_g の制約（ΣA_i の上限）は書いていない
- **generating-function-counting**：maspy.com は工事中の表示で FPS の解説を資料に使えなかった
- **k-shortest-paths**：Eppstein の計算量と永続ヒープの記憶は上界として書いた。「KM が 10^7 程度まで」などの目安は見積もり。原論文は開いていない
- **lagrange-interpolation**：ABC137 F の p の上限は確かめていない（検証で今のままでよいとされた）
- **lgv-lemma**：abc216_h の K ≤ 10 程度は解答コードの配列の大きさからの読み取り。O(2^K K L) は自分の DP の計算量（記事は別の分け方）。「斜めの線の上にあれば恒等置換だけ」は十分条件
- **linear-recurrence-fast**：Library Checker の consecutive_terms の解き方は「多項式の逆元と組み合わせる工夫が要る」とだけ書いた
- **matrix-tree-theorem**：abc336_g の N の上限は確かめていない
- **merge-process-tree**：agc002_d の併合過程の木による第三者の解説がない。Library Checker に直接の問題はない（部品として lca・jump_on_tree）
- **miller-rabin**：「1 つあたり 1 秒よりずっと短い」は控えめな見積もり。rho の期待 O(√p) は発見的な見積もり（本文にもそう書いた）。64bit の法の Barrett 還元は書いていない
- **monge**：abc458_g の要約は解法の節から読み取った仮のもの（問いの細部をメインか検証役が別の解説で確かめる）。Knuth-Yao・SMAWK・LARSCH を使う確認済みの ABC は見つからない。「Monge なコストで k 個の区間に分ける最小値は k について凸」は tatyam の資料による。本文の K の上限（検証の指摘 5）はメインで確かめる
- **multiplicative-function**：Nyaan の O(N^{2/3}) の実装が Meissel-Lehmer の系統かは確かめていない（本文は直しで括弧を消した）。Min_25 篩の Θ(N^{1−ε}) は OI Wiki と Nyaan の注記に従った
- **offline-dynamic-connectivity**：例題の制約（H・W の上限）と答えの法は書いていない
- **online-convolution**：summary の「次数の小さいものから」は本文では 2 通り（添字で半分・優先度付きキュー）として書いた（§1.1）
- **parallel-binary-search**：agc002_d の制約と連結かは数値まで確かめていない（検証で連結と明記）。Range Kth Smallest を BIT で解いて 5 秒に収まるかは実測していない
- **partially-persistent-union-find**：「2 頂点から tm の小さい側を登る」方法は本文の論法とコード片の突き合わせで確かめた（第三者の資料では確かめていない）
- **partizan-games**：「Grundy 数が 0 でない不偏な部分の値は…」と S + *g の勝敗の条件は kmjp の ABC265 Ex の記事の条件と一致することだけを確かめた。教科書『Lessons in Play』の邦訳名は書誌を確かめられず外した
- **rollback-union-find**：root-path-dfs#no-path-compression と 3 点で食い違わないことを確かめた（記録）
- **segment-tree-beats**：割り算の評価 O((N + Q log N) log A) と mod の評価 O(N log N log A) は自分のポテンシャルの議論。chmin と chmax を両方持ち加算がない場合の計算量は資料で確かめきれなかった。平方根の打ち切りと O(log log A) は出典を個別に挙げていない。abc256_h の制約（x の範囲・非負か）は未確認
- **segment-tree-graph**：例題の要約と解法の詳細（降りる区間の西端で距離を分ける・木が 4 本）は kmjp の記録とコードの読み取りで、2 件目の裏付けがない。N・M の上限は書いていない
- **slope-trick**：ABC217 H のダメージの向きは kmjp の記事でも文と式で食い違うので書かなかった。greedy-priority-queue#regret からのリンクがあるが、後悔付き貪欲との関係は裏付けられず書いていない
- **spanning-tree-advanced**：Library Checker の Minimum Spanning Tree・Manhattan MST・Directed MST の URL は GitHub のディレクトリ名から作った（ページそのものは開いていない）。最小有向全域木の「閉路の辺を 1 本だけ外す」は証明を書かず資料に任せた
- **static-top-tree**：構築 O(N log N) はコード片の素朴な分け方の見積もり（直しで「工夫すれば O(N)」を足した）。高さ O(log N) は直感の説明。「ABC351 G の公式解説は ABC の想定解として Static Top Tree を初めて正面から扱った」は第三者の記述に基づく。Point Set Tree Path Composite Sum の助言は maspy の記事の要約で自分では通していない
- **steiner-tree**：abc364_g の制約は確かめていない（本文の見積もりは「なら」の仮定）。abc395_g の計算量は ikatakos の値で、制約は確かめていない
- **stern-brocot**：例題の制約（N の上限・r の桁数）は確かめていない（仮の値で書いた）。判定の回数 O(log N) は cp-algorithms の主張に拠る
- **stirling-first**：例題の閉じた形は自前の導出（N ≤ 7 の全列挙で確認）。Taylor shift の倍化と EGF は Nyaan の実装で確かめた（速さの比較はしていない）
- **suffix-automaton**：回文木の構築のならし O(N) は ei1333 の記述と原論文の「線形サイズ」で裏付けた。Main-Lorentz 法の細部は資料に任せた
- **tree-isomorphism**：木のハッシュの誤る確率「1 組あたり N/p 以下」は Schwartz-Zippel を当てた自分の議論（折りたたみに証明の筋。検証で直した）
- **tree-ratio-greedy**：abc376_g の確率の分子の上限は確かめていない（コード片は常に `__int128` で比べる）。「一般化」の条件は資料に任せた
- **two-sat**：「1 つの数の異なる素因数は 10^7 以下なら 8 種類以下」は手で確かめた値。ABC210 F の制約は書いていない
- **wavelet-matrix**：abc324_g の境界は検証で「x 以下を残す」と確かめた（ledger.md）
- **young-tableaux**：「対合の数 = Σ f^λ」は確かめきれず書いていない
- **atcoder-system**：誤答に数えない提出（CE など）の細則は未確認。ARC の区分ごとの難しさは数えていない。色の割合の違い（ガイドラインと nabata 氏の集計）は「考えられる」と推測で書いた
- **cheatsheet**：隣り合う素数の差の最大は 10^9 までだけ（10^18 までの 1442 は確かめられない）
- **contest-strategy**：「終了前の 10〜15 分」と「切り替えの時刻」の手順は出典のない提案（本文にもそう書いた）
- **cpp-environment**：エディタ（cph）が ulimit を引き継ぐか、Clang 21.1 の libc++ の機能、Ubuntu の g++ の -fstack-protector-strong が AtCoder で同じかは未確認。版の対応表は GCC 14 以降・C++26・GCC 16 の行だけを新たにコンパイルした
- **debugging-checklist**：AtCoder でスタックの使用量がメモリの計測に入るかは確かめていない
- **divisors-and-multiples**：落とし穴の「積が平方数の問題では 0 を核の計算に入れない」は prime-exponent-vector#squarefree-kernel の要約（持ち主はそのページ）
- **dp-speedup-overview**：典型90 090 は公式の解説画像 1 本だけで確かめた（GitHub の API の回数制限で解答コードの一覧を取れなかった）。確認問題の見積もりは手計算
- **glossary**：色の項は灰・水・青・黄・赤の境目だけ（茶・緑・橙は書いていない）
- **graph-modeling**：「頂点・辺が 10^6〜10^7 程度なら線形に近い探索が 1 秒前後」は概算（直しで complexity-estimation へリンク）
- **grid**：abc472_d の移動回数を数える向き・abc464_e の初期の文字が入力で与えられるかは問題文で確かめていない（要約は文字を書かずに済ませた）。#tiling の 2^w は目安
- **how-to-use**：Safari の 7 日の条件は WebKit の 2020 年のブログによる（今の Safari でも同じかは未確認）
- **interval**：ABC265 D の「値が正」は検証の後に dhirabayashi の記事で裏付けた（ledger.md）
- **kth-and-median**：#range-kth の並列二分探索の方法は parallel-binary-search の一般の説明に頼った（区間の K 番目の例はない）
- **library-design**：competitive-verifier の属性名（PROBLEM）と `#define` の非推奨は WebFetch の要約で読んだ（原文の行は見ていない）。段階の表は目安
- **method-comparison**：フローチャートの順（全点対 → DAG → 負の辺 → …）は research の判断の順序と違う（本文の箇条書きは research の順）。ベルマンフォード法の目安は「N と M が数千まで」
- **notation**：「AtCoder の GCC 15.2（-std=gnu++23）」は cpp-environment と手引き §9 による
- **practice-method**：E869120 上級編の表は変換で列の対応がはっきりせず、検証で 700〜900 点の列を足した。AtCoder Problems の画面の項目名はガイドの文面からの確認
- **problem-sets**：NDPC・AAL Contest 001・組合せゲーム 24 題の難しさの目安、鉄則本の B・C の意味、NoviSteps のグレードと ABC の位置の対応は確かめられず書いていない。EDPC・TDPC・鉄則本の「レベルの目安」は本文での level の分布から書いた（作者の目安ではない）
- **roadmap**：「abc319 以降、E〜G の難しさに一方向の変化は見えない」は research/00 §2.3.4 に拠る（再集計していない）
- **stress-testing**：MinGW の `random_device` の注意（GCC 9.2 より前に限定）を短く書いた（cpp-environment が持ち主になるなら移す）。現在の MinGW で再現するかは未確認
- **term-index**：サイト内検索の言い方は research/10 §2.4（試作 14 ページの試験）に拠る。353 ページでの検索の試験（design-review T3）の結果が出たら合わせる
- **thinking-checklist**：鉄則本 6.5 は検証で map と二項係数に当てた。アルゴリズム×数学 5.5 の対応は「推定」と添えた。00-curriculum §4.1 の「典型90問の考察・実装の15項目」は一次資料を確かめられず入れていない。observation-hub の表を受ける件は symmetry-pigeonhole-casework に改められたので、thinking の章の先頭からの入口リンクはメインの判断
- **twelvefold-way**：動く図（マスをクリックで全列挙）は visual が static なので作らず静的な SVG にした
- **xor**：ABC197 C の N の上限は確かめていない

## 6. 解決済み（b1・b3 の決定・手引きで扱いが決まっているもの、またはバッチの中で解決したもの）

- related・prerequisites の追加（§1.3）：b1 の決定（other.md §1.5）で「反映する（双方向にする必要はない）」と決まっている。反映の作業だけが残る
- frequency_evidence の根拠の問題がページと関係しない件（slope-trick・online-convolution・tree-isomorphism）：b1 の決定で「外す（frequency の値は変えない。工程 10 で見直す）」と決まっている
- summary・signs の表記の直し（歩道・償却・サイクル）：b1 の決定と付録 A・§14-22 で反映すると決まっている。内容の直し（general-matching の 16 → 20 など）は根拠を確かめてから
- 内容の重なり：b1 の決定で「後から書く側が先に書かれたページへリンクして短くする」。持ち主の判断が要るものだけ handoff.md §2 に残した
- 確認問題を #quiz へ（chromatic-number）：§14-11
- Library Checker の置き場（tree-ratio-greedy・stirling-first）：§15-5
- ACL の中身の節の title（two-sat）：§15-3・§13-2
- stub のページへのリンク：§14-23。全ページ draft になったので handoff.md §1 で張り替える
- roadmap の related の atcoder-system#difficulty-by-position：atcoder-system が draft になり節がある
- generating-function-counting の「ABC449 G の制約を確かめていない」：検証役が ikatakos で N ≤ 10^5・M ≤ 10^9 と確かめた
- library-design の「Library Checker の C++ に ACL が入っているか」：検証の指摘 8・9 で langs.toml を確かめ、本文に足した
- cpp-reverse-index の cpp-environment への張り替えの依頼：執筆者が直しで済ませた
- lagrange-interpolation の未解決 1・3、wavelet-matrix の境界、interval の ABC265 D、cht の abc289_g・abc228_h の checked：検証で解決（ledger.md）
