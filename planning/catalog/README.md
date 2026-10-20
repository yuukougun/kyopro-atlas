# 目次（catalog）の作り方（第2版）

全ページの一覧を分野ごとに `planning/catalog/<field>.yaml` に置く。上位の規則は設計書（[../design.md](../design.md)）§3〜§5 と、見直しへの対応（[../design-review.md](../design-review.md)）。この文書はその詳細。

catalog は工程8a（骨格）で各ページの front matter の元になる。8a 以降は front matter と問題の台帳（`data/problems.yaml`）が正で、catalog は凍結し、執筆の指示（sections・visual・sources）としてだけ使う（design-review T10）。

- 第2版（2026-10-21）：見直しを受けて、節・図・問題を構造化し、hub を足し、題名・別名・前提・要約の規則を決めた

## 1. 担当とファイル

| 担当 | ファイル | 主な材料 |
| --- | --- | --- |
| A | `basics.yaml`・`thinking.yaml`・`misc.yaml` | research/01、research/08 の「その他」、research/00 §3.2 |
| B | `dp.yaml` | research/02、research/00 §3.2 |
| C | `graph.yaml`・`tree.yaml` | research/03・04、research/00 §3.2 |
| D | `ds.yaml` | research/05、research/00 §3.2 |
| E | `math.yaml` | research/06、research/00 §3.2 |
| F | `comb.yaml` | research/07、research/02 の確率・期待値・ゲームの DP と包除 DP、research/00 §3.2 |
| G | `string.yaml`・`geometry.yaml` | research/08（「その他」を除く）、research/00 §3.2 |
| H | `cpp.yaml` | research/09 |
| I | `start.yaml`・`guide.yaml`・`patterns.yaml` | research/00、設計書 §7 |

## 2. ファイルの形式

```yaml
field: ds
pages:                        # 並び順がナビゲーションの順
  - id: lazy-segment-tree     # 一意。英小文字・数字・ハイフン。8a 以降は変えない
    chapter: 区間クエリ       # 分野の中の章。小さい分野では省く
    # 並び順はファイルの中の順（8a で front matter の order に写す）
    title: 遅延セグメント木
    nav_title: null           # 題名が長いときだけ、ナビゲーション用の短い名前
    aliases: [遅延セグ木, Lazy Segment Tree, lazy segtree]
    type: technique           # technique / thinking / pattern / hub / overview / cpp / guide
    level: 水                 # 基礎 / 水 / 青 / 黄 / 発展。start・guide・patterns・hub は null。cpp は目安か null
    level_evidence: "abc340_e (1157, 2024)・abc473_f (1303, 2026)・abc382_f (1443, 2024)・abc455_f (1549, 2026) は ACL を呼ぶだけで解ける"
    kind: [データ構造, 区間クエリ]
    prerequisites: [segment-tree]                 # 直接の前提だけ。ページの id
    related: [lazy-segment-tree-patterns, imos, range-set-management#merge-intervals]   # id か id#anchor
    summary: "区間への一括更新と区間の集約（和・最小など）を、どちらも O(log N) で行う。"
    signs:
      - {type: phrase, text: "区間に一括で加算・代入し、区間の和や最小値を何度も答える"}
      - {type: constraint, text: "N, Q ≤ 2×10^5 で区間の更新と区間の質問が交互に来る"}
    acl: [lazy_segtree]
    verify: [range_affine_range_sum, range_add_range_min]   # Library Checker の問題名（任意）
    frequency: A              # A / B / C（§5。D5 のデータから後で付け直す）
    sections:                 # 主な節。level を省くとページと同じ
      - {title: "区間の長さを S に持たせる", anchor: size-in-node}
      - {title: "保つ性質と push の手順（自作するとき）", anchor: invariants, level: 青}
    merged_keys: [dual-segment-tree]
    visual: {kind: dynamic, priority: 1, text: "遅延の値が子へ降りていく様子のステップ送り"}   # なければ null
    problems:
      - {id: abc340_e, role: example, representative: true, summary: "箱の玉を順に配る操作を繰り返したあとの各箱の玉の数を求める。", approach: "区間加算と一点取得。配る範囲が一周を超える分は全体への加算にする"}
      - {id: abc382_f, role: practice, summary: "…", approach: "…"}
    problems_note: null       # 練習が目安に足りない・最近の問題がないときの理由
    sources: ["05-ds §4.D", "05-ds §5.2"]
moved:
  - {key: some-key, to: comb, reason: "設計書 §4.2"}
dropped:
  - {key: xxx, reason: "…"}
open_issues:
  - "…"
```

## 3. 規則

### 3.1 処理と受け渡し

1. **調査の key をすべて処理する**：自分の担当の調査の全 key を、どれかのページの `id`、`merged_keys`、`moved`、`dropped` のどこかに入れる
2. **統合**：分野をまたいで統合するときは、送る側が `moved`（`to:` に受ける分野）、受ける側が `merged_keys` に入れる。統合で消えたページの id も key として扱う（例：dp-convolution は math の online-convolution の `merged_keys` に入れる）。id を変えたときは旧 id を `merged_keys` に入れる
3. 書いてよいのは自分の担当のファイルだけ。他の担当への依頼は `open_issues` に「提案：〜」と書く。git の commit はしない
4. atcoder.jp・codeforces.com は開かない。新たな Web の調査は原則しない

### 3.2 ページの種類とレベル

1. **type**：`hub` は入口・比較・地図のページ（中身の説明は各ページに任せ、表やリンクが本体）。level は null、frequency なし、問題は0〜3で例題なしでよい
2. **level**：設計書 §3.1 と design-review D2。帯は abc319 以降（2023-09 以降）の根拠を主に数え、古い問題は最近の根拠がないときだけ使う。ACL を呼ぶだけで解ける問題も数える（ACL の外の考察が本体なら数えない）。根拠と、変えたときの理由を `level_evidence` に書く
3. **節のレベル**：節の level はページの level 以上。低い内容は下位のページに置き、上位のページには導線の1行（`related` か本文の参照）だけを残す。**基礎のページの節は青まで**（黄・発展の中身は上位のページへ）
4. 節の `anchor` は英小文字・数字・ハイフン。ページの中で一意

### 3.3 前提と関連

1. `prerequisites` は直接の前提だけ（「これを知らないと読めない」もの。多くて4つ）。推移的に届くものは書かない
2. 前提に自分より高いレベルのページを入れない。循環を作らない
3. 前提と related に同じページを置かない。related は調査の key ではなくページの id、節なら `id#anchor`
4. 同じ分野の前提は、ナビゲーションの並び（ファイルの中の順）でそのページより前に置く
5. 入ってくる道（どのページの prerequisites・related にも出てこない）がないページを作らない

### 3.4 問題

1. 例題1〜3（基礎は1、発展・hub は0〜2）、練習2〜6、力試し0〜3。足りないときは `problems_note` に理由を書く
2. **例題は1問につき1ページだけ**（その手法の持ち主）。ほかのページでは練習か本文の参照にする
3. **代表問題**：帯の中の例題1問に `representative: true`。並びは易しい順のまま
4. **水・青のページは abc319 以降の問題を1問以上**入れる（候補は research/00 §2.3.8 と各調査。ないときは `problems_note`）
5. **summary は問いだけ**（何を求めるか）。手法名・解き方は `approach` に書く。手法名しか分からない問題は summary を「（執筆時に確かめる）」とし、approach に手法を書く
6. 調査で「未確認」とされた問題は入れない。問題 ID は `python3 tools/ap.py show <ID>` で確かめる
7. 題材別（patterns）は例題0〜1・練習0〜3で、ほかのページと重ならないもの。thinking の例題は2〜4

### 3.5 文章

1. **summary**：1文目は何ができるか（いつ使うか）。2文・120字以内。「このページ」「ここ」「まとめる」「扱う」「紹介する」、帯の名前（水・青など）を使わない。だ・である調
2. **signs**：`phrase`（問題文の言い回し・求めるもの）、`constraint`（制約の形。数や不等号を含む）、`shape`（立てた式・遷移の形。例：「dp[i] が dp[j]（j < i）の区間の和で決まる」）。手法名を入れない。候補を絞れないもの（「998244353 で割った余り」「N ≤ 2×10^5 の木」だけのもの）は書かない。技法の特徴が制約に出るページは constraint を1つ以上
3. **title**：正式名は「セグメント木」（本文・補足は「セグ木」可）。数の K は大文字。人名の連結は ASCII のハイフン（Aho-Corasick・Sprague-Grundy）。半角英数字と全角文字の間に空白を入れる（「2 次元累積和」「K 番目」）。長いかっこの補足は付けず、別名・summary に回す（ナビゲーションで長いなら `nav_title`）
4. **aliases**：英語の定まった名前がある手法は英語名を1つ以上入れる。題名と同じ語は入れない。ほかのページの題名・別名と紛らわしい語は入れない（意図した重複は open_issues に理由を書く）
5. **visual**：`kind` は dynamic（ステップ送り・動く図）か static。`priority` は 1（必ず作る）・2（余力があれば）・3（静的な図で代えてよい）。priority 1 は分野ごとの枠（design-review §4.2）まで

### 3.6 章

1. 発展の概要は話題の章に置く（「発展」の章を作らない）
2. 1ページだけの章を作らない（隣の章と合わせる）

## 4. 手法の種類（`kind`）の語彙

1ページに1〜3個。ここにない語を使わない。

| 語 | 対象の例 |
| --- | --- |
| 計算量 | 計算量の見積もり、ならし計算量、調和級数、定数倍 |
| 全探索 | bit 全探索、順列全探索、半分全列挙、再帰による列挙 |
| 二分探索 | 答えの二分探索、K 番目、セグ木上の二分探索、並列二分探索 |
| 累積和・差分 | 累積和、いもす法、差分、木のいもす |
| 尺取り・スライド窓 | 尺取り法、スライド最小値 |
| 貪欲 | 区間スケジューリング、交換論法、辞書順の構成 |
| ソート・座標圧縮 | 比較関数、座標圧縮、イベントソート |
| ダブリング・分割統治 | ダブリング、分割統治、周期性 |
| DP | すべての DP（期待値 DP・ゲーム DP・木 DP を含む） |
| グラフ探索 | BFS、DFS、トポロジカルソート、SCC |
| 最短路 | ダイクストラ、01-BFS、ワーシャルフロイド、ベルマンフォード、状態を頂点にする |
| 連結性・全域木 | Union-Find の使い方、最小全域木、橋・関節点 |
| フロー・マッチング | 最大流、最小カット、燃やす埋める、二部マッチング、最小費用流 |
| 木 | 木の性質、LCA、オイラーツアー、重心、マージテク |
| データ構造 | STL の応用、Union-Find、BIT、セグ木、Trie など構造そのもの |
| 区間クエリ | 区間の和・最小・更新を扱うもの（累積和・BIT・セグ木・Sparse Table・Mo） |
| クエリ処理の工夫 | オフライン処理、平方分割、Mo、逆順処理 |
| 整数論 | mod、素数、約数、GCD、合同式、floor |
| 線形代数・行列 | 行列累乗、掃き出し法、XOR 基底 |
| 畳み込み・多項式 | 畳み込み、FFT/NTT、形式的冪級数 |
| 数え上げ | 二項係数、包除原理、写像12相、数え方の考え方 |
| 確率・期待値 | 期待値の線形性、期待値 DP、確率の mod 表現 |
| ゲーム | 必勝・必敗、Nim、Grundy 数 |
| 文字列 | 文字列アルゴリズム全般 |
| ハッシュ・乱択 | ローリングハッシュ、集合のハッシュ、乱択 |
| 幾何 | 幾何全般 |
| ビット演算 | bit ごとに独立、XOR の性質、部分集合の列挙 |
| 考察 | 言い換え、主客転倒、寄与、余事象、偶奇、不変量、構築 |
| 実装・C++ | C++ の書き方、入出力、落とし穴、ACL の使い方 |
| 案内 | 横断ページ・題材別・はじめに・hub |

## 5. 出題頻度（`frequency`）

| 値 | 基準 |
| --- | --- |
| A | 最近の ABC（abc451〜480 の D〜G の分類、`data/recent-abc.yaml`）で2回以上、または多くのページの前提 |
| B | 最近の ABC で1回、または古い ABC で繰り返し使われた |
| C | それ以外（発展の多く） |

工程4の終わりに `data/recent-abc.yaml` から機械的に付け直し、`frequency_evidence` に回数を残す。cpp・hub・guide・patterns・start は持たない。

## 6. 分野をまたぐ key の持ち主

第1版の表（重複していた調査の key）に加え、見直しで次の統合を決めた（design-review §3・§4）。

| 統合するページ（送る側） | 受けるページ（持ち主） |
| --- | --- |
| dp/dp-convolution | math/online-convolution |
| dp/dp-counting-dedup | comb/counting-dedup |
| dp/dp-matrix-power | math/matrix-power |
| dp/dp-decision-binary-search | basics/binary-search-answer |
| basics/median-binary-search | basics/fractional-binary-search |
| graph/state-space-search | graph/extended-dijkstra |
| graph/shortest-path-overview | guide/method-comparison |
| graph/xor-path | math/xor-basis |
| graph/reachability-bitset | misc/bitset-speedup |
| graph/biconnected-components | graph/lowlink（題名「橋・関節点・二重連結成分」） |
| math/discrete-log・math/primitive-root・math/mod-sqrt | math/multiplicative-order（題名「位数・原始根・離散対数」） |
| comb/game-mirror-strategy | comb/game-basics |
| string/fft-string-matching | math/convolution-ntt |
| tree/long-path-decomposition | tree/tree-diameter |

第1版で決めた、重複していた調査の key の持ち主：amortized-analysis（basics）、base-conversion（math）、biconnected-components（graph）、binary-trie（ds）、bracket-sequence（patterns）、cycle-detection（graph。basics の周期は periodicity）、dag-dp・dp-dag（dp）、difference-constraints（graph）、dynamic-dp（dp）、expected-value-dp（comb）、hashing-for-sets（string）、inclusion-exclusion-dp（comb）、inversion-number（ds）、legendre-formula（math）、lexicographic-greedy（basics）、linear-recurrence-fast（math）、merge-sort-tree（ds）、mo-on-tree（ds）、namori-graph（graph）、parallel-binary-search（ds）、permutation-cycles（comb）、pigeonhole（thinking）、probability-dp（comb）、run-length-encoding（basics）、slope-trick（dp）、steiner-tree（graph）、string-automaton-dp（string）、subsequence-dp（dp）、suffix-automaton（string）、super-vertex（graph）、swag（ds）、xor-convolution・hadamard-transform（math）。

## 7. 検証

`python3 tools/check_catalog.py`（メインのセッションが実行する。`--field` で自分の分野だけ）。第1版の検査（形式・id の重複・前提の解決と循環・レベルの逆転・kind の語彙・問題の実在・調査の key の取りこぼし）に、第2版で次を足す：節の構造とレベル、推移的に冗長な前提、前提と related の重複、related の調査の key、同じ分野の前提がナビゲーションで後ろ、入ってくる道のないページ、例題の重複、同じ別名の重複、根拠の問題が帯に入らない、練習の不足、summary の長さと禁止語、visual の priority 1 の数。
