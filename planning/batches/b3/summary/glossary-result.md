# 用語集への反映の結果（prop23）

用語集 docs/guide/glossary.md：82 語 → 117 語（新しい語 35、既存の項への追記 4）。定義はすべて書き直した（提案の文はそのまま使っていない）。
prh.yml は変更なし（揺れの規則が要る語がなかった）。python3 tools/check_pages.py はエラー 0・警告 0。npm run lint:text はエラー 0（glossary.md の警告は反映前と同じ 12 件）。

## 既存の項への追記（4）

| anchor | 追記 |
| --- | --- |
| representative | 数え上げでの意味（作り方のうち規則で 1 つ選んだもの） |
| cut | 有向グラフの s-t カットとその容量（逆向きの辺は数えない） |
| fixed-point | 「不動点ともいう」と一次漸化式の例 |
| dangling | 別名「ぶら下がり参照」 |

見送り：hash-collision（既存の文で足りる）、in-degree（提案者が取り下げた）。

## 採った新しい語（35）

| 語 | anchor | 置いた節 |
| --- | --- | --- |
| 誕生日のパラドックス | birthday-paradox | 手法一般 |
| 交換法則 | commutativity | 手法一般 |
| 冪等 | idempotent | 手法一般 |
| 作用 | action | 手法一般 |
| 支配（状態の） | dominance | 手法一般 |
| 巻き戻し | rollback | 手法一般 |
| 単射 | injection | 数学 |
| 全射 | surjection | 数学 |
| 集合の分割 | set-partition | 数学 |
| 多重集合 | multiset | 数学 |
| 重複度 | multiplicity | 数学 |
| ダブルカウント（2 通りに数える） | double-counting | 数学 |
| 閉じた式 | closed-form | 数学 |
| 分散 | variance | 数学 |
| 一次独立 | linear-independence | 数学 |
| ランク | rank | 数学 |
| マトロイド | matroid | 数学 |
| 不偏ゲーム | impartial-game | 数学 |
| 握手補題 | handshaking-lemma | グラフ |
| クリーク | clique | グラフ |
| 頂点被覆 | vertex-cover | グラフ |
| マッチング | matching | グラフ |
| 完全マッチング | perfect-matching | グラフ |
| 縮約 | contraction | グラフ |
| 三角不等式 | triangle-inequality | グラフ |
| ボトルネック | bottleneck | グラフ |
| 逆辺 | reverse-edge | グラフ（有向グラフの逆向きとフローの逆辺の両方を 1 項で） |
| 残余グラフ | residual-graph | グラフ |
| 増加路 | augmenting-path | グラフ |
| 後退辺 | back-edge | グラフ（前進辺・横断辺も本文で触れた） |
| ラベル付き木 | labeled-tree | グラフ（ラベル付きグラフも本文で触れた） |
| 部分列 | subsequence | 文字列 |
| ハミング距離 | hamming-distance | 文字列 |
| 照合オートマトン | matching-automaton | 文字列 |
| submask | submask | 実装 |

採った基準：競技プログラミングで広く使う語で、複数のページに出る（docs の grep で 3 ページ以上を目安）か、ページのない基本の語。

## 採らなかった語と理由

- ページ（または節）があり、そこへのリンクで足りる：最小包含円・外心（circle-geometry）、凸包・上側凸包（convex-hull）、位数（multiplicative-order）、二重辺連結成分（lowlink#two-edge-connected）、逐次最短路法（min-cost-flow の節）、重心・重心木（tree-centroid・centroid-decomposition）、高速ゼータ変換・メビウス変換・OR 畳み込み（zeta-mobius-subset）、経路コピー（persistent-data-structures）、補グラフ（graph-basics#terms）、多項定理（multinomial-coefficient）、プロファイル（broken-profile-dp）、ワード並列（bitset-speedup）
- 1 ページだけで使い、そのページで定義すれば足りる：失敗リンクの木、向き付け、重い頂点・軽い頂点、原始的な文字列、Johnson の規則、吸収マルコフ連鎖、吸収状態、拡大係数行列、ピボット、自由変数、横断辺（後退辺の項で触れた）、構文木・BNF・左結合（parsing）、恒等置換・互換（permutation-parity）、片側誤り、支配点の数え上げ、毛虫、合流点、正則グラフ、ラベル付きグラフ（ラベル付き木の項で触れた）、混合進数、弱連結、既約分数、共分散、相対順位、極大・極小、辺被覆、LP 緩和、メルテンス関数、平方剰余、戦略、劣モジュラ・閉包（project-selection）、重み付き重心
- 一般語で説明が要らない：順序対、繰り上がり
- 既存の項でまかなう：指示関数（indicator で足りる）

## ページに付けた用語集へのリンク（46 か所・35 ページ）

提案したページで、その語の本文での最初の出現（見出し・別名の行・コード・数式・既存のリンクの中を除く）にリンクを付けただけで、文は変えていない。

- counting-dedup：重複度・部分列（代表元はリンク済み）
- min-cut：残余グラフ（カットはリンク済み）
- multiplicative-order：不動点（#fixed-point）
- aho-corasick・string-automaton-dp：照合オートマトン
- bell-number：集合の分割・全射
- counting-bijection：全射・単射
- inclusion-exclusion：全射
- bellman-ford：三角不等式
- binomial-identities：閉じた式・「2 通りに数え」（#double-counting）
- bottleneck-path：ボトルネック
- convolution-ntt：ハミング距離
- dp-dimension-reduction：支配
- gaussian-elimination：ランク・一次独立
- xor-basis：ランク・マトロイド（「独立」はページ自身が定義しているので付けなかった）
- graph-construction：後退辺
- lowlink：後退辺・縮約
- grundy-number：不偏ゲーム
- hash-safety：誕生日のパラドックス
- kth-value・optimal-strategy-expectation・partition-number：多重集合
- lazy-segment-tree-patterns：作用
- root-path-dfs：巻き戻し
- segment-tree-monoids：交換法則
- sparse-table：冪等
- subset-enumeration-dp：クリーク（submask は最初の出現が見出しと bit-operations#submask へのリンクの近くでコード中のため付けなかった）
- tree-degree：握手補題・ラベル付き木
- cayley-pruefer：ラベル付き木
- bipartite-matching：マッチング・完全マッチング
- konig-theorem：マッチング・頂点被覆
- expectation-of-square：分散
- game-retrograde-analysis：逆辺
- max-flow：残余グラフ・増加路
- min-cost-flow：残余グラフ

## メインへの申し送り

- 付録 A（用語の正規形）に足す語の案（提案の §3）は style-guide の担当なので扱っていない
- glossary の front matter の sections にある judge・atcoder・slang・canonical-forms の節は本文にまだない（以前から）
