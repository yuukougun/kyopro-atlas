# 設計の見直し 01：学習者と教育の観点

工程4（設計の見直し）の1本目。設計書（[../design.md](../design.md)、初版）と目次（[../catalog/](../catalog/)、15分野・367ページ）を、「レート961・パフォーマンス1100〜1450（ABC は D まで安定、E は時々）の学習者が黄色に届くか」の観点で批判的に読んだ。

- 日付：2026-10-21
- 読んだもの：requirements.md・decisions.md・design.md・catalog の全 yaml（open_issues を含む）と README、research/00 §2.2〜§2.3・§3.2・§6.11・§7、必要に応じて research/04 など
- 方法：catalog を全件読んだうえで、次を機械的に集計した（スクリプトは一時ファイル置き場に置き、リポジトリには入れていない）。difficulty はすべて `python3 tools/ap.py show` で確かめた値
  - research/00 §2.3.8 の 120 問（abc451〜480 の D〜G）が、どのページの `problems` に入っているか
  - ページのレベルと、例題・練習・`level_evidence` の問題（特に abc319 以降の7問体制の問題）の difficulty の帯との比較
  - 節のレベルの印の数（ページより高い・低い）、別名の重複、前提の数と深さ、`frequency` と最近の問題の対応、ABC の問題が少ないページ
- 限界：問題文と公式解説は noai のため読んでいない。問題がどの手法を使うかは research/00 §2.3.8 と catalog の記載に頼っている

## まとめ

| 重さ | 件数 | 番号 |
| --- | ---: | --- |
| 重大 | 2 | 1・2 |
| 中 | 7 | 3〜9 |
| 軽 | 8 | 10〜17 |

目次の網羅は十分である。§2.3.8 の E・F 60 問で使われた手法は、ほぼすべてどこかのページか節にある（どのページの `problems` にもない問題は E 9問・F 8問だが、手法そのものはある）。問題は網羅ではなく次の3つにある。

1. **レベルの付け方と見せ方**：節に付けたレベルの印がロードマップ・知識マップ・「理解した」に乗らない（指摘1）。最近の ABC で水の帯に下りた道具が青に残っている（指摘2・5）
2. **重複と薄いページ**：同じ内容のページが別名・例題ごと重なり（指摘4）、ABC の根拠がほとんどない黄・青の独立ページが分量を黄と発展に寄せている（指摘6）
3. **弱点からの入口**：「E を安定させる」「F を解く」ための、位置ごとの頻出手法から入る導線がない（指摘3）

---

## 指摘

### 1. 節のレベルの印が機械で読めず、ロードマップ・知識マップ・「理解した」に反映されない

- **重さ**：重大
- **場所**：設計書 §3.1 規則4・§3.3（front matter）・§7（色別ロードマップ・知識マップ）・§8.3（生成スクリプト）・§9.1（理解したチェック）。catalog の全ページの `sections`
- **問題**：レベルの印は節の見出しの文字列（「Dilworth の定理（青）」）にしかなく、生成スクリプトはページの `level`・`prerequisites`・`frequency` しか読まない。そのため、下位のページの節に置いた青・黄の内容は、その色のロードマップに一度も出てこない。「理解した」もページ単位なので、水の部分だけ読んで押すと、そのページの青・黄の節まで理解済みとして知識マップが塗られる
- **根拠**：
  - catalog の 209 節にレベルの印があり、191 節はページより高い。**青の印の節は基礎・水のページに 68 節**（青のページは 58）、**黄の印の節は基礎〜青のページに 63 節**（黄のページは 44）。青・黄の内容の半分以上が「下位のページの節」にある
  - 最近の F・G で効く内容が節に入っている例：difference-sequence（水）の「最小回数・可否を差分列で考える（黄）」＝abc454_f（2169）・abc459_f（2163）。lis（水）の「Dilworth の定理（青）」＝abc457_g（1928）。inversion-number（水）の「差分で更新する型（青）」＝abc452_f（1630）。small-to-large（水）の「DSU on Tree（黄）」＝abc454_g（2253）。linearity-of-expectation（水）の指示確率変数など3節（青）＝abc380_g（1995）
  - 設計書 §4.3 自体が、Grundy 数の「易しい abc368_f（1180）は水のロードマップから見せる」、平方分割の「入口の青の問題は例題の先頭に置く」、Suffix Array の「ACL で水色でも使えると注記」、K 番目の値の「考え方の入口は基礎の答えの二分探索に置く」と、ページのレベルをまたいで見せることを前提にしているが、それを実現する仕組みがない
  - research/00 §7.1-1 は「レベルは主な帯＋幅で持ち、基本は水・応用は青を節のレベルとして表す」と提案していたが、設計は節の印を文字列で書くところで止まっている
- **提案**：
  1. catalog の `sections` を文字列の列から `{title, anchor, level, problems}` の列に変える（`level` は省略可で、省略時はページと同じ）。工程8a で front matter に `sections:` として写し、本文の見出しには attr_list で `{#anchor}` を付ける
  2. `tools/gen_site.py` は節も「ページ#節」としてその色のロードマップの列に出す（節に任意で `frequency` を持たせ、なければページの値）。知識マップでは、上位の節を持つページに印（例：右上に青・黄の点）を付ける
  3. 「理解した」を「ページ×レベル」で持つ（キーを `understood:<page-id>:<level>` にする）。進捗の集計も、節の `problems` をその節のレベルで数える
  4. §4.3 の「水のロードマップから見せる」類は、`roadmap_hints: [{level: 水, anchor: …}]` のような指定で表す
  5. この仕組みを入れないなら、§4.1-2 の規則（帯がはっきり分かれる型は基本と応用を分ける）を、上位の節に固有の例題が2問以上あるページ（lis・difference-sequence・tree-dp・linearity-of-expectation・small-to-large・tree-diameter など）に当てはめて分ける。ただしページが20前後増えるので、1〜4 を勧める

### 2. 最近の ABC で水の帯に下りた「ACL を呼ぶだけで使える道具」が青に置かれている（遅延セグ木が中心）

- **重さ**：重大
- **場所**：ds/lazy-segment-tree（青）、設計書 §3.1 規則2・§4.1-2。あわせて ds/segtree-binary-search・basics/fractional-binary-search・tree/tree-construction
- **問題**：設計書 §3.1 規則2「近年の問題を重く見る」が当てはめられていない。遅延セグ木の青の根拠は 2020〜2023 年の問題で、2024 年以降に遅延セグ木が要る問題は水に並ぶ。F で最も多いデータ構造（research/00 §2.3.8：F の「セグ木・BIT 8（遅延セグ木が多い）」）が水のロードマップに出ないので、水の段階で F の水の帯（F の 26%、§2.3.3）を取りに行く準備ができない
- **根拠**：
  - 水：abc340_e（1157、2024）・abc473_f（1303、2026）・abc382_f（1443、2024）・abc455_f（1549、2026）。青：abc327_f（1624、2023）・abl_e（1706、2020）・abc179_f（1713、2020）。catalog の `level_evidence` 自身が「ACL を呼ぶだけの易しい形は水にも出ている」と書き、ds の open_issues も同じ迷いを挙げている
  - 同じ傾向のページ：segtree-binary-search（青）は abc392_f（1395、2025 の F）・abc478_f（1588、2026 の F）が水で、青は abc389_f（1642）が下端。fractional-binary-search（青）は例題の先頭が 2026 年の E の abc469_e（1566）。tree-construction（青）は2つの例題 abc451_e（1215、2026）・abc478_f（1588、2026）がどちらも水で、青の根拠は abc239_f（1959、2022）と agc005_c（1976）
- **提案**：
  - lazy-segment-tree を**水**にする。本体は「ACL の lazy_segtree で標準の型（区間加算×区間 min・max・和、区間代入×区間和など）を呼ぶ」と「S に区間の長さを足す」。保つ性質と push の手順（自作ライブラリ用）は（青）の節にする。前提は segment-tree だけにし、segment-tree-monoids は `related` へ
  - S・F の設計は lazy-segtree-patterns（青）に残し、前提に segment-tree-monoids を足す。設計書 §4.1-2 のセグ木の5ページを「基本（水）／遅延セグ木の使い方（水）／モノイドの設計（青）／セグ木上の二分探索（青）／載せ方の型（青）」に直す。cpp/acl-reading の「lazy_segtree の7つの引数の節（青）」も水にし、§10.1 の試作の候補「遅延セグメント木（青）」の表記も直す
  - segtree-binary-search・tree-construction は、ページを水にするか、少なくとも入口の節を水にして指摘1の仕組みで水の列に出す。fractional-binary-search は指摘4の統合と合わせて基本形を水にする
  - catalog の全ページで「abc319 以降の根拠だけで帯を数え直す」確認を一度行う（今回の集計で該当したのは上の4ページ）

### 3. 学習者の弱点（E を安定させる・F を解く）から入る導線がない

- **重さ**：中
- **場所**：guide/roadmap・guide/contest-strategy・guide/problem-sets、設計書 §1.1・§7
- **問題**：設計書 §1.1 は「E は数え上げ（二項係数・包除・寄与）と累積和・差分、F は言い換えてから（遅延）セグ木」という傾向を書いているが、これを学習者に見せてページへつなぐ節がどこにもない。ロードマップは色ごとに水 90・青 58 ページを頻度と分野で並べるだけで、「E を落とさないために最初に読むページ」が分からない。problem-sets の「問題 → ページの対応表」は典型90問・EDPC などが対象で、学習者が毎週出る最近の ABC が入っていない
- **根拠**：research/00 §2.3.8 の 120 問には第三者の解説による手法の裏付けがある。今回の照合では、E・F の 60 問のうち 43 問がすでにどこかのページの `problems` に入っていた（E 21・F 22）。E の内訳は累積和・差分 10、数え上げ 9、考察 6（例：abc455_e 1157 余事象＋包除、abc458_e 1309 仕切りを固定して二項係数、abc473_e 966 累積和 mod K）
- **提案**：
  - §2.3.8 の表を page id に対応させた data ファイル（例：`planning/data/recent-abc.yaml`。問題 ID・位置・difficulty・使う手法のページ id）を作る
  - そこから roadmap に「位置ごとの頻出手法（最近30回）」の節を生成する。表は「E（水）・F（青）・G（黄）ごとに、分類（累積和・差分／数え上げ／言い換え → セグ木 …）→ 代表ページ → その位置の最近の問題」
  - 同じ data から problem-sets（または新しい guide ページ）に「最近の ABC の D〜G → ページ」の対応表を生成する。claude.ai の解説（設計書 §9.2）でも問題 ID から直接ページを引ける
  - thinking/reformulation の「言い換えの一覧表」を F の入口と位置づけ、method-comparison と同じく「本文と並行して育てるページ」に指定する（F の最多の分類が言い換え）

### 4. 同じ内容のページが複数あり、別名と例題が重なっている

- **重さ**：中
- **場所**：下の表のページ
- **問題**：辞書として引くと同じ名前で2〜4ページが出て、どれを読むべきか分からない。レベルの印の食い違いも起きており、執筆と検証の手間も倍になる
- **根拠**（別名の衝突は catalog の title・aliases を機械的に照合した）：

  | 重なり | ページ | 根拠 |
  | --- | --- | --- |
  | 重複の除き方・代表元 | dp/dp-counting-dedup（青）と comb/counting-dedup（青） | 別名「ダブルカウントを防ぐ」「最小添字規則」が両方にある。例題がどちらも abc310_d（1368） |
  | 平均・比・中央値の最大化 | basics/fractional-binary-search（青）・basics/median-binary-search（青）・dp/dp-decision-binary-search（青）・basics/binary-search-answer（基礎） | 別名「平均の最大化」「比の最大化」「中央値の最大化」「決め打ち二分探索」が重なる。abc236_e（1893）は3ページ、abc324_f（1815）は2ページに入る |
  | 行列累乗 | math/matrix-power（黄）と dp/dp-matrix-power（黄） | 別名「行列累乗」が両方。dp_r・abc009_4 が両方にある |
  | 分割統治 FFT | dp/dp-convolution（発展）と math/online-convolution（発展） | 別名「オンライン畳み込み」「分割統治 FFT」が両方。例題がどちらも abc213_h（2806） |
  | ずらしたときの一致数 | string/fft-string-matching（黄）と math/convolution-ntt（青） | convolution-ntt の signs に「列をずらしたときの一致数・ハミング距離を全てのずらし方で求める」がすでにある |
  | 閉路の XOR | graph/xor-path（黄）と math/xor-basis（黄）の節「グラフの閉路の XOR への応用」 | 例題は abc451_g（2221）の1問 |
  | 到達可能性の bitset | graph/reachability-bitset（黄）と misc/bitset-speedup（青）の節「到達可能性・推移閉包（黄）」 | 同じ内容を節と単独ページの両方に持つ |
  | 集合分割の全列挙 | basics/recursive-enumeration（水）の組分け型と comb/bell-number（青）の「重複なく全列挙する書き方」 | 別名「ベル数」「グループ分けの全列挙」が両方。abc310_d は両方の例題、abc390_d（1607）は bell-number の例題で recursive-enumeration の力試し |
  | 同じ概念でレベルの印が違う | 「全射の数」：comb/inclusion-exclusion（青のページの節）と comb/bell-number の節（黄）。「寄与で総和」：thinking/contribution（水）と comb/counting-mindset の節（青） | 同じ内容に別のレベルが付く |

  abc310_d（1368）は6ページの `problems` に入っている（dp-counting-dedup・counting-dedup・twelvefold-way・bell-number・recursive-enumeration の例題、subset-enumeration-dp の練習）
- **提案**：
  - dp-counting-dedup を comb/counting-dedup に統合する。`kind` に DP を足して DP の一覧に出し、DP 特有の「最も左を取る」「最小番号のグループから決める」は節にする。subsequence-dp の前提も counting-dedup に直す
  - dp-decision-binary-search をやめ、「判定を DP で作る」は binary-search-answer の節（判定の中身）に、平均・比は fractional-binary-search に、中央値は median-binary-search に振る。fractional と median を1ページ「平均・中央値の最大化（値を引く・±1 にする二分探索）」にまとめる案も検討する（abc236_e はちょうど両方を使う）
  - dp-matrix-power を matrix-power に統合する（レベルは指摘5）。DP の章からは dp-speedup-overview の早見表でリンクする
  - dp-convolution を math/online-convolution に統合する
  - fft-string-matching を convolution-ntt の節に、xor-path を xor-basis の節に、reachability-bitset を bitset-speedup の節に統合する（指摘6）
  - 集合分割の全列挙の本体は recursive-enumeration（水）に置き、bell-number は数（S(n,k)・B_n の漸化式と大きさ）に絞る。「全射の数」の持ち主は inclusion-exclusion にし、印を青にそろえる
  - 例題は1つのページにだけ置き、ほかのページは本文で参照する（comb の open_issues の方針を全分野に広げる）。`tools/check_catalog.py`（と工程6の検証）に「同じ問題が2ページ以上の例題」「同じ別名が2ページ以上」の警告を足す

### 5. 行列累乗が黄なのに、青のページの例題がそれを必要とする

- **重さ**：中
- **場所**：math/matrix-power（黄）・dp/dp-matrix-power（黄）・string/string-automaton-dp（青）・ds/segment-tree-monoids（青）・dp/dynamic-dp（発展）、設計書 §4.3（行列累乗・オイラーの φ：黄）
- **問題**：string-automaton-dp（青）の例題 abc458_f（1744）と練習 abc305_g（1989）は、遷移行列の累乗（またはダブリング）が要る。ところがその節は（黄）の印で、matrix-power はレベルの逆転のため前提に置けない。segment-tree-monoids（青）の「行列を載せる（(min,+)・(max,+)）」の節の問題 abc456_f（1888）も行列の積が前提になる。青の学習者がこれらの例題を解くための説明が、青の範囲にない
- **根拠**：行列の積・累乗が要る問題は、abc458_f（1744、2026）・abc456_f（1888、2026）・abc305_g（1989、2023）が青、abc204_f（2044）・abc199_f（2065）・abc009_4（2213 参考値、2014）・abc256_g（2250）が黄。設計書 §4.3 の理由「必須の ABC は 2000 前後以上」は 2026 年の2問を見ていない。research/00 §2.2.1（ガイドライン）と §2.2.3（青の色変記事）も行列累乗を青の知識に挙げている
- **提案**：matrix-power（dp-matrix-power を統合）を**青**にする。根拠は abc458_f・abc456_f・abc305_g・abc199_f。(min,+) 行列は matrix-power の節にし、プロファイル DP との組み合わせ・きたまさ法との使い分けは黄・発展の節にする。string-automaton-dp の「遷移行列の累乗（黄）」の印を青にし、前提に matrix-power を足す。dynamic-dp は発展の概要のままでよいが、abc456_f は区間の積を取る問題で「1点更新のたびに求め直す」動的 DP の代表ではないので、dynamic-dp の例題から外し、segment-tree-monoids の行列の節の例題にする（練習から格上げ）

### 6. ABC の根拠がない・1問だけの独立ページが黄・青に多く、分量が黄と発展に寄っている

- **重さ**：中
- **場所**：graph の complement-graph-bfs・xor-path・reachability-bitset・lowlink・euler-path・biconnected-components、math の multiplicative-order・discrete-log・primitive-root、comb の lucas-theorem・game-mirror-strategy、basics の divide-and-conquer、string の fft-string-matching、tree の long-path-decomposition。設計書 §1.1（水・青を厚く）
- **問題**：ページ数は青 58 に対して黄 44＋発展 55＝99 で、§1.1 の「水・青を厚く」と逆に見える。黄のうち ABC の問題が1問以下のページが 11（黄の4分の1）ある。青にも、ABC の問題がなく ARC・AGC だけを根拠にしたページがあり、要件の「ABC 中心」と research/00 §7.2-3（ARC は知識のページの例題に向かない）に合わない。graph は 52 ページのうち 24 が黄・発展だが、§2.3.8 の E・F 60 問でグラフの手法を使うのは約8問で、ほとんど基礎・水の手法である
- **根拠**：
  - complement-graph-bfs：abc319_g（2185）だけ。xor-path：abc451_g（2221）だけ。reachability-bitset：typical90_bg（★7）と abc287_h（2639、発展の帯）。lowlink：例題 abc075_c（1067）は全探索で解く問題で、lowlink が想定解と確かめられた ABC はない（graph の open_issues）。biconnected-components：問題0。euler-path：abc286_g（2135）だけ
  - multiplicative-order：abc222_g（2242）＋ARC。discrete-log：abc270_g（2220）＋ARC。primitive-root：abc212_g（2150）＋AGC。3ページが同じ数問を共有している
  - lucas-theorem（青）：arc117_c（1768）・agc043_b（1945）だけで、catalog 自身が「ABC での直接の出題は見つかっていない」と書く。game-mirror-strategy（青）：6問のうち ABC は abc398_e（1238、水）だけ
  - divide-and-conquer（黄）：arc189_d（2006）だけで練習0。fft-string-matching（黄）：abc196_f（2274）だけで、指摘4のとおり convolution-ntt と重なる。long-path-decomposition（黄）：abc369_g（2055）だけ
- **提案**：
  - 統合する：complement-graph-bfs → bfs の節（黄）。xor-path → xor-basis の節。reachability-bitset → bitset-speedup の節。lowlink と biconnected-components → 1ページ「橋・関節点・二重連結成分（lowlink）」（黄・C。練習は Library Checker の two_edge_connected_components・biconnected_components で補う）。位数・原始根・離散対数 → 1ページ（黄）。lucas-theorem → binomial-precompute の節（青）。game-mirror-strategy → game-basics の節「手数の偶奇・真似戦略」（ABC の根拠に合わせて水〜青）。fft-string-matching → convolution-ntt の節
  - 残す：euler-path（「一筆書き」で引かれ、次数の偶奇という独自の理由がある）。divide-and-conquer（重心分解・Monge・CDQ の前提。力試しに abc451_g（2221）・abc478_g（2582）を足す）。long-path-decomposition（名前で引かれる。tree-diameter の黄の節に入れる案もある）
  - これで黄・発展が約10ページ減る。発展の概要のうち ABC の問題が1問もない14本（graph 5・ds 4・math 4・tree 1）も、ds/advanced-ds-catalog と同じく分野ごとの「発展の手法の一覧」1ページにまとめられないか、工程5でユーザーに確かめる（「発展は1手法1ページ」はユーザーの回答なので、変えるなら確認が要る）

### 7. 出題頻度（frequency）を数え直しておらず、ロードマップの必修・準必修の根拠が弱い

- **重さ**：中
- **場所**：catalog 全体の `frequency`、catalog/README §5、設計書 §3.2・§7（ロードマップ）
- **問題**：ロードマップの3段（必修 A・準必修 B・余裕があれば C）は `frequency` だけで決まるが、値は担当ごとの見積もりで、comb の open_issues は「abc400 以降の出題数を数え直してはいない」と書く。research/00 §7.1-2 は §2.3.8 の 120 問を key に対応させて数える方法を提案していたが、使われていない
- **根拠**：
  - optimal-strategy-expectation は水・A だが、abc400 以降の問題は abc412_f（2038）・abc421_e（2122）・abc470_e（2096）と全部黄の帯。水の学習者に「必修」と出るが、A の理由は黄の問題である（水の根拠は abc266_e 1227・abc350_e 1385 の2問）
  - 水・青で A のページ 38 のうち 16 は、`problems` にも `level_evidence` にも abc400 以降の問題がない（lca・segment-tree・fenwick-tree・priority-queue・bit-dp・game-basics・expected-value-dp・counting-mindset など。前提として多く参照されるという理由の A も含まれる）
- **提案**：指摘3の data（§2.3.8 の 120 問を page id に対応させたもの）から、各ページの abc451〜480 での出現数を数え、「A＝30回で2回以上、または前提として多く参照される」「B＝1回、または古い ABC で繰り返し」「C＝それ以外」のように機械的に付け直す。数えた結果は `frequency_evidence` として残す。optimal-strategy-expectation は、基本形（選択は max・偶然は平均）を expected-value-dp（水）の節に移し、ページは黄にする案を勧める

### 8. ページより低いレベルの節（17件）の扱いが決まっていない

- **重さ**：中
- **場所**：設計書 §3.1 規則4・5、string/string-automaton-dp ほか
- **問題**：低い節は、その色の学習者がロードマップからたどり着かない（ページは高い色の列にあり、前提にも高いページが並ぶ）。中身が下位のページと重なっていることも多い
- **根拠**：17件。中身と例題を持つもの：
  - string-automaton-dp（青）の「簡易版：直近の数文字を状態にする（水）」＝abc122_d（1533）。dp-state-design（水）の節「典型の要約（…末尾の数文字）」と重なる
  - graph/bellman-ford（青）の「ポテンシャルで負辺を消してダイクストラ（水）」＝abc237_e（1208）。dijkstra（基礎）の「負辺で壊れる例」の節と重なる
  - dp/rerooting（青）の「根の移動の差分で済む場合（水）」＝abc220_f（1304）・abc348_e（1347）
  - tree/tree-centroid（黄）の「全点への距離の和が重心で最小（水）」＝abc348_e（rerooting と同じ問題）
  - comb/inclusion-exclusion（青）の「2〜3 条件の包除（基礎）」＝abc131_c（518）。thinking/complement（基礎）の節「条件が 2 つなら包除原理」と重なる
  - comb/zeta-mobius-divisor（青）の「倍数を回して集める（水）」＝abc393_e（1253）。math/harmonic-sum（基礎）の「倍数の個数を集める」節と重なる
  - ds/sqrt-decomposition（黄）の「歩幅ごとの場合分け（青）」
  - 残りは入口の一言（lowlink の全探索、interactive の flush など）
- **提案**：規則5の続きとして「節の印はページのレベル以上を原則とする。低い節は下位のページへの数行の導線に限り、内容と例題は下位のページに置く」を設計書に足す。個別には、string-automaton-dp の簡易版と abc122_d を dp-state-design へ、ポテンシャルを dijkstra の（水）の節へ、2〜3 条件の包除を complement へ、倍数を回して集めるを harmonic-sum へ移す。tree-centroid の水の節は導線だけにする。rerooting の差分の型など、どうしても入口として残すものは指摘1の仕組みで水の列に出す

### 9. 考察の入口が2つあり、型の一覧が二重になる

- **重さ**：中
- **場所**：guide/thinking-checklist、thinking/observation-hub、設計書 §4.1-7・§7
- **問題**：thinking-checklist の「言い換えの問い」「変わらないものを探す」の節と、observation-hub の「問題の形 → 試す型の表」は、同じ型の一覧を問いの形と表の形で二度持つ。引く側はどちらを開けばよいか分からず、片方だけ直したときに食い違う。さらに observation-hub は索引なのに問題を7問（うち例題3）持ち、鳩の巣原理などの小さな型の本体も兼ねていて、役割が混ざっている
- **根拠**：guide.yaml と thinking.yaml の open_issues。別名「発想の型」が両ページにある。thinking-checklist の節には contest-strategy・stress-testing とも重なる項目（誤読を疑う・実験・一度離れる）がある
- **提案**：入口は guide/thinking-checklist の1つにし、observation-hub の「問題の形 → 試す型」の表と「ほかの型の行き先」をそこへ移す。observation-hub は「対称性・鳩の巣原理・場合分け（小さな考察の型）」の通常の thinking のページに改め、題と別名を変える。「実験」は guide/stress-testing の実験の節と comb/counting-mindset の検算の節にすでに分かれているので、stress-testing を本体にする。thinking の章の先頭には入口へのリンクだけを置く

### 10. 写像12相を青の technique にしている

- **重さ**：軽
- **場所**：comb/twelvefold-way
- **問題**：中身は「各マスの式と行き先のページ」の地図で、マスは基礎（k^n・重複組合せ）から黄（分割数）まで散らばる。青にすると、基礎・水のマスを引きたい学習者がロードマップで出会わない
- **根拠**：例題 abc310_d（1368）・abc021_d（1704 参考値、2015）は各マスのページ（bell-number・stars-and-bars）にも入っている。guide/cheatsheet の「よく使う公式」の節にも写像12相がある
- **提案**：レベルを持たない案内のページ（patterns と同じ扱いで type は pattern、field は comb のまま）にし、例題は各マスのページへ移す。cheatsheet の行はこのページへのリンクだけにする

### 11. 前提の過剰・不足があり、知識マップの「次の候補」が不自然になる

- **重さ**：軽
- **場所**：string/kmp、math/xor-basis、string/string-automaton-dp、dp/dp-order、ds/sweep-line-2d
- **問題と提案**：
  - kmp の前提 z-algorithm：KMP は Z を使わない。`related` へ
  - xor-basis の前提 gaussian-elimination：基底への挿入（最上位 bit で消す）は一般の掃き出し法を知らなくても読める。前提は bit-operations だけにし、掃き出し法は `related` へ（黄の列が軽くなる）
  - string-automaton-dp の前提 aho-corasick：1パターンなら KMP のオートマトンで足りる。aho-corasick は `related` にし、複数パターンの節で参照する
  - dp-order の前提 dp-dag：このため game-basics・expected-value-dp・interval-dp の祖先にトポロジカルソートが入る（grundy-number の前提の連鎖は深さ9）。dp-dag は `related` へ
  - sweep-line-2d：例題 abc477_f（1629）と節「固定幅の窓を動かして区間加算・区間最大（遅延セグ木）」が遅延セグ木を使うのに、前提にない。lazy-segment-tree を前提に足す（指摘2で水にすればレベルの問題もない）

### 12. signs に「問題文の言い回し」ではないものと、候補を絞れないものが混ざる

- **重さ**：軽
- **場所**：catalog の `signs`（特に dp の高速化の章）、設計書 §3.2・§7（逆引き辞典（言い回しから））
- **問題**：逆引き辞典（言い回し）は問題文から引く入口だが、dp の章を中心に「素直な DP が O(N^2)」「dp[i] = Σ dp[j] の形」「遷移元が区間」「区間の右端で並べると決まりそう」のように、式を立てた後や解き手の見込みを書いたサインがある。これらは問題文に現れない。また「〜の個数を 998244353 で割った余り」（dp-basics・counting-basics・counting-mindset・mod-arithmetic・binomial-precompute）や「N ≤ 2×10^5 の木」（tree-dp）は多くの問題に当たり、候補を絞れない。「N ≤ 2×10^5 で素直な DP が O(N^2)」は dp-segment-tree と cht に同じ文がある
- **根拠**：1049 個の signs のうち、式・状態・遷移・素直な解の計算量を書いたものが約70個（dp だけで 26）。research/00 §7.1-6 は「問題文の言い回し・制約の形・求めるものの形」の3種類を提案していた
- **提案**：`signs` の type に `shape`（立てた式・遷移の形）を足し、逆引き辞典に「立てた式の形から」の表を生成する（dp-speedup-overview の早見表と同じ材料になる）。候補を絞れないサインは消すか、逆引きの導入の節に「数え上げ全般」として1行だけ置く

### 13. 例題・練習の候補が古い ABC に偏り、最近の形式の問題がないページがある

- **重さ**：軽
- **場所**：catalog の `problems`、設計書 §3.1 規則2・§5.3
- **問題**：学習者が毎週出るのは abc4xx で、設計書も近年の問題を重く見るとしているが、候補の ABC の問題のうち7問体制（abc319 以降）は水で 38%、青で 41% にとどまる。7問体制の問題が1問もないページが水に 21、青に 14 ある（例：priority-queue・dp-prefix-sum・zero-one-bfs・counting-mindset・lattice-paths・nim・lca・crt・binomial-identities・circle-geometry）
- **提案**：執筆の指示（設計書 §10.2 の「渡すもの」）に「水・青のページは abc319 以降の問題を例題か練習に1問以上入れる」を足す。research/00 §2.3.8 の 120 問はすでに手法の裏付けがあるので優先して使う

### 14. 考察と題材別のページの問題数が設計の目安を超える

- **重さ**：軽
- **場所**：thinking の全ページ、patterns の全ページ、設計書 §4.1-7・§6.3
- **問題**：設計書は thinking を「ABC の例題2〜4」の短いページとしたが、catalog は各ページ 5〜7 問を持つ（例題3問のページが8つ）。patterns は案内のページなのに 7〜11 問を持ち、多くが技法のページの例題と重なる（例：abc436_e は permutation-cycles と patterns/permutation の両方の例題）。要件の「考察は少しだけ」と、「解いた」チェックの二重の数え方の点で合わない
- **提案**：thinking は例題を2〜4に絞る。patterns の問題は「表の各行の代表問題」としてリンクだけ（チェックなし）にし、練習は技法のページに任せる

### 15. 題材別に「部分列」がない

- **重さ**：軽
- **場所**：patterns、設計書 §4.1-8
- **問題**：「部分列」は問題文に頻出する対象だが、判定（string/subsequence-matching、水）・位置の組の数（dp/dp-phase、青）・異なる部分列の数（dp/subsequence-dp、黄）・LIS・LCS が string と dp に散らばり、名前も違う。部分列と部分文字列の取り違えは method-comparison にも挙がっている
- **根拠**：abc452_d（903、部分列照合の DP）・abc456_d（586、末尾文字ごとの部分列 DP）・abc214_f（1973）・arc081_c（2072）・abc299_f（2349）
- **提案**：patterns に「部分列（と部分文字列）」を足す。余裕があれば「約数と倍数」（divisor-enum・harmonic-sum・divisor-inclusion-exclusion・zeta-mobius-divisor・prime-exponent-vector・gcd-properties に散らばる）も候補

### 16. ロードマップの「分野ごとに並べる」と、分野をまたぐ同じ色の前提がぶつかる

- **重さ**：軽
- **場所**：guide/roadmap の生成の節、設計書 §7
- **問題**：「前提の順に分野ごとに並べる」と、分野の並び（basics → … → comb）で後ろにある分野の前提が後に出る
- **根拠**：水：priority-queue（ds）→ greedy-priority-queue（basics）、contribution（thinking）→ bitwise-independence（basics）。青：lazy-segment-tree（ds）→ inline-dp（dp）。黄：matrix-power（math）→ dp-matrix-power（dp）、xor-basis（math）→ xor-path（graph）
- **提案**：色の中ではトポロジカル順の1本の列を基本にして分野で色分けするか、分野ごとの列の前に「この列を読む前に読む他分野のページ」を出す

### 17. summary にレベルや作り手側の言葉が混ざる

- **重さ**：軽
- **場所**：math/gcd-properties（「…など、青の帯で効く性質を集める」）、math/proof-patterns（「…を、ABC の例とともに集める」）
- **問題**：summary は llms.txt と知識マップのツールチップで単独で読まれる（設計書 §3.3）。帯の名前や「集める」は、読者に何ができるかを伝えない
- **提案**：「差の gcd・左端を固定した区間 gcd の値の種類・mod N で A ずつ進んで回れる範囲が分かる」のように、何が分かるかで書き直す。`tools/check_catalog.py` で summary に「水の帯」「青の帯」「集める」「まとめる」などの語があれば警告する

---

## 論点 1〜6 への判断

1. **遅延セグ木のレベル**：基本のページを**水**に下げる（指摘2）。2024 年以降に必要な問題は abc340_e（1157）・abc473_f（1303）・abc382_f（1443）・abc455_f（1549）と水に並び、青の根拠は 2020〜2023 年の 1624〜1713 で、設計書 §3.1 規則2に従えば水になる。ページは ACL での使い方と「S に長さを足す」を本体にし、内部の手順は（青）の節、S・F の設計は lazy-segtree-patterns（青）に残す。前提は segment-tree だけにする
2. **挿入 DP・部分列 DP・動的 DP**：
   - 挿入 DP は**黄のまま**。2026 年の abc468_g（1975）・abc473_g（1974）は境界から 26 以内の G で、abc473_g は確率・FPS と組む。ほかは abc209_f（2307）以上。今後も青の帯に出続けたら下げる、と level_evidence に残す
   - 部分列 DP も**黄のまま**（abc214_f 1973・arc081_c 2072・abc230_f 2113・abc299_f 2349）。前提の dp-counting-dedup は comb/counting-dedup に統合する（指摘4）
   - 動的 DP は**発展の概要のまま**でよい。abc456_f（1888）は「セグ木に (min,+) 行列を載せて区間の積を取る」問題なので segment-tree-monoids（青）の行列の節の例題にし、行列の積の説明は matrix-power を青に下げて用意する（指摘5）
3. **黄の薄いページ**：complement-graph-bfs → bfs の節、xor-path → xor-basis の節、reachability-bitset → bitset-speedup の節、lowlink → biconnected-components と1ページ（黄・C）。euler-path は名前で引かれ独自の理由があるので短い独立ページのまま残す（指摘6）
4. **ページより低いレベルの節**：原則として**認めない**。低い節は下位のページへの数行の導線に限り、内容と例題は下位のページへ移す。string-automaton-dp の（水）の節は dp-state-design の「末尾の数文字」の節へ abc122_d（1533）ごと移す。どうしても残す入口は、指摘1の機械可読な節のレベルで水の列に出す（指摘8）
5. **考察の入口が2つ**：**1つにまとめる**。入口は guide/thinking-checklist にし、observation-hub の「問題の形 → 試す型」の表をそこへ移す。observation-hub は小さな型（対称性・鳩の巣原理・場合分け）の通常のページにする（指摘9）
6. **その他の判断**：
   - 置換の巡回分解を基礎のページにするのは妥当（abc436_e 958）。青・黄の節（abc377_e 1685・abc226_f 2086・abc371_g 2348）は指摘1の仕組みで各色の列に出す。仕組みを入れないなら「巡回型ごとの数え上げ（黄）」を分ける
   - 写像12相は青の technique ではなく、レベルを持たない地図のページにする（指摘10）。分け方（第2種スターリング数・ベル数を青、分割数を黄の単独ページ）は妥当だが、集合分割の全列挙は recursive-enumeration に一本化する（指摘4）
   - 分割統治の黄は規則どおりで妥当（ABC で分割統治が鍵になるのは abc451_g 2221 以上、根拠は arc189_d 2006 だけ）。ページが薄いので力試しに abc451_g・abc478_g（2582）を足す
   - 辞書順最小の貪欲の基礎も妥当（abc076_c 846・abc202_d 966・abc223_d 1069・arc097_a 1108、drken の7問の中央値 885）。判定が重い abc009_3（1915）は 2014 年の参考値なので、規則2に照らして青の節で足りる
