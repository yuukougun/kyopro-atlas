# 目次（catalog）の作り方

全ページの一覧を分野ごとに `planning/catalog/<field>.yaml` に置く。設計書（[../design.md](../design.md)）の §3〜§5 が上位の規則で、この文書はその詳細。catalog は工程8a（骨格）で各ページの front matter の元になり、執筆者への指示書にもなる。

## 1. 担当とファイル

| 担当 | ファイル | 主な材料 |
| --- | --- | --- |
| A | `basics.yaml`・`thinking.yaml`・`misc.yaml` | research/01、research/08 の「その他」、research/00 §3.2 の抜けている項目 |
| B | `dp.yaml` | research/02、research/00 §3.2 |
| C | `graph.yaml`・`tree.yaml` | research/03・04、research/00 §3.2 |
| D | `ds.yaml` | research/05、research/00 §3.2 |
| E | `math.yaml` | research/06、research/00 §3.2 |
| F | `comb.yaml` | research/07、research/02 の確率・期待値・ゲームの DP と包除 DP（設計書 §4.2 で comb に移すもの）、research/00 §3.2 |
| G | `string.yaml`・`geometry.yaml` | research/08（「その他」を除く）、research/00 §3.2 |
| H | `cpp.yaml` | research/09 |
| I | `start.yaml`・`guide.yaml`・`patterns.yaml` | research/00（横断ページ・題材別）、設計書 §7 |

## 2. ファイルの形式

```yaml
field: ds                     # 設計書 §2.1 の field
pages:                        # 並び順がナビゲーションの順
  - id: segment-tree          # 一意。英小文字・数字・ハイフン。原則は調査の key
    chapter: 区間クエリ       # 分野の中の章（ナビゲーションの小見出し）。小さい分野では省く
    title: セグメント木
    aliases: [セグ木, Segment Tree]
    type: technique           # technique / thinking / pattern / overview / cpp / guide
    level: 水                 # 基礎 / 水 / 青 / 黄 / 発展。start・guide・patterns は null。cpp は目安か null
    level_evidence: "abc???_? (1350)・abc???_? (1420) で必須。易しい例 abc???_? (1100)"
    kind: [データ構造, 区間クエリ]       # §4 の語彙から1〜3個
    prerequisites: [monoid-basics]       # 必須の前提。同じ分野は id、他分野は相手の調査の key でよい
    related: [fenwick-tree, sparse-table]
    summary: "一点の更新と区間の集約（和・最小など）を、どちらも O(log N) で行うデータ構造。"
    signs:
      - {type: phrase, text: "配列の値を書き換えながら、区間の最小値を何度も答える"}
      - {type: constraint, text: "N, Q ≤ 2×10^5 で更新と区間の質問が交互に来る"}
    acl: [segtree]            # ACL の対応（なければ []）
    frequency: A              # A / B / C（§5）
    sections:                 # 主な節。レベルが違う節は末尾に（青）などの印
      - "一点更新・区間取得の流れ"
      - "非可換なモノイド（青）"
    merged_keys: [segment-tree-basics]   # このページに統合した調査の key（id 自身は書かない）
    visual: "更新で根まで、取得で O(log N) 個のノードを選ぶ様子のステップ送り"   # 図・動く図の案。なければ null
    problems:                 # 例題・練習の候補（調査から。執筆時に確かめ直す）
      - {id: abc???_?, role: example, summary: "何を問う問題か（自分の言葉で一言）"}
      - {id: abc???_?, role: practice, summary: "…"}
    sources: ["05-ds §4.B", "05-ds §5.2"]   # 執筆時に読む調査レポートの節
moved:                        # 自分の調査の key のうち、他の分野に置くもの
  - {key: expected-value-dp, to: comb, reason: "設計書 §4.2"}
dropped:                      # どのページにも入れない key（重複・範囲外など）
  - {key: xxx, reason: "…"}
open_issues:                  # 設計で決めきれず、見直しで判断してほしい点
  - "…"
```

## 3. 規則

1. **調査の key をすべて処理する**：自分の担当の調査（topics.yaml）の全 key を、どれかのページの `id`、どれかのページの `merged_keys`、`moved`、`dropped` のいずれかに必ず入れる。検証スクリプトが取りこぼしを調べる
2. **他の担当から移ってくるもの**：設計書 §4.2 で自分の分野が持ち主になっている項目は、相手の調査の key を `merged_keys` か `id` に入れて取り込む。相手の調査レポートの該当節も `sources` に書く
3. **id**：原則は調査の key。統合したページは代表の key を id にする。分野をまたいで重複していた key（research/00 と各分野など）は、設計書 §4.2 の持ち主の分野だけが使う
4. **前提**：`prerequisites` は「これを知らないと読めない」ものだけ（多くて4つ程度）。知っていると良いものは `related`。前提には自分より高いレベルのページを入れない（入れるなら related）。循環を作らない
5. **レベル**：設計書 §3.1 の規則と §4.3 の決定に従う。調査の `level` を基本にし、変えるときは `level_evidence` に理由を書く
6. **粒度**：設計書 §4.1 に従う。調査の `page: own` をそのまま全部単独ページにする必要はない。名前で引かれ、独自の「なぜ」を持つ単位をページにし、変種・応用は `sections` に入れる
7. **problems**：調査の候補から、設計書 §5.3 の数の目安で選ぶ（例題1〜3、練習2〜6、力試し0〜3。基礎は少なめ、発展は0〜2）。**調査で「未確認」とした問題は入れない**。問題 ID は `python3 tools/ap.py show <ID>` で実在を確かめる。易しい順に並べる
8. **summary**：1〜2文。単独で意味が通るように書く（索引と知識マップで使う）。だ・である調
9. **signs**：逆引き辞典の材料。`phrase`（問題文の言い回し・求めるもの）と `constraint`（制約の形）。具体的に（「N ≤ 20」「最小値の最大化」「区間に一括で加算」など）
10. **frequency**：§5 の基準で付ける
11. **sources**：執筆者が読むべき調査レポートの節を、`"05-ds §4.B"` のように書く
12. **書いてよいのは自分の担当のファイルだけ**。git の commit はしない
13. atcoder.jp・codeforces.com は開かない（設計書 §6.7）。この作業は調査の結果をまとめるもので、新たな Web の調査は原則しない

## 4. 手法の種類（`kind`）の語彙

分野をまたぐ一覧を作るための固定の語彙。1ページに1〜3個付ける。ここにない語を使わない（足すべき語があれば `open_issues` に書く）。

| 語 | 対象の例 |
| --- | --- |
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
| 案内 | 横断ページ・題材別・はじめに |

## 5. 出題頻度（`frequency`）の基準

| 値 | 基準 |
| --- | --- |
| A | 最近の ABC（目安：abc400〜abc480）の D〜G で繰り返し（3回以上）使われる。またはその分野の多くのページの前提になる |
| B | 最近の ABC で1〜2回、または古い ABC で繰り返し使われた |
| C | 最近の ABC でほとんど見ない（発展の多くはここ） |

根拠は調査の例題の日付・research/00 §2.3.8 の分類表で見積もる。厳密でなくてよい。ロードマップの「必修（A）・準必修（B）・余裕があれば（C）」に使う。

## 6. 分野をまたいで重複する調査の key の持ち主

同じ key（または同じ題名）が複数の調査に出ているもの。**持ち主の分野だけ**がその key を `id` か `merged_keys` に使う。持ち主でない担当は、その key を `moved`（`to:` に持ち主の分野）に入れる。意味が違うのに key が同じもの（cycle-detection）は、持ち主でない側が別の id を付ける。

| key | 調査 | 持ち主 | 備考 |
| --- | --- | --- | --- |
| amortized-analysis | 00, 01 | basics | |
| base-conversion | 00, 06 | math | |
| biconnected-components | 00, 03 | graph | |
| binary-trie | 00, 05, 08 | ds | |
| bracket-sequence | 00, 08 | patterns | DP・セグ木・貪欲での扱いは各ページの節 |
| cycle-detection | 01, 03 | graph | basics の「シミュレーションの周期の検出」は別の id にする（例：periodicity） |
| dag-dp（03）／dp-dag（02） | 02, 03 | dp | dp は dag-dp を merged_keys に入れる |
| difference-constraints | 00, 03 | graph | |
| dynamic-dp | 02, 05 | dp | 発展の概要。ds のセグ木のページから行列を載せる話としてリンク |
| expected-value-dp | 02, 07 | comb | |
| hashing-for-sets | 05, 08 | string | |
| inclusion-exclusion-dp | 02, 07 | comb | |
| inversion-number | 00, 05 | ds | |
| legendre-formula | 00, 06 | math | |
| lexicographic-greedy | 00, 01, 08 | basics | |
| linear-recurrence-fast | 00, 06 | math | |
| merge-sort-tree | 00, 05 | ds | |
| mo-on-tree | 00, 04 | ds | Mo のページの節 |
| namori-graph | 00, 03, 04 | graph | |
| parallel-binary-search | 00, 01, 05 | ds | |
| permutation-cycles | 00, 07 | comb | |
| pigeonhole | 00, 01 | thinking | |
| probability-dp | 02, 07 | comb | |
| run-length-encoding | 00, 01, 08 | basics | |
| slope-trick | 00, 02 | dp | |
| steiner-tree | 00, 03 | graph | |
| string-automaton-dp | 02, 08 | string | |
| subsequence-dp | 02, 08 | dp | |
| suffix-automaton | 00, 08 | string | |
| super-vertex | 00, 03 | graph | 「状態を頂点にする」ページの節 |
| swag | 00, 05 | ds | |
| xor-convolution（00）／hadamard-transform（06） | 00, 06 | math | math は xor-convolution を merged_keys に入れる |

このほかの受け渡し：

- research/00 の `kind: gap`・`gap-candidate` の項目は、research/00 §3.2 の「置き場所の案」の分野（設計書 §4.2 と食い違うときは §4.2）が持ち主。各担当は、自分の分野に置かれた 00 の項目を取り込む（id・merged_keys・dropped のどれか）。担当 I は、00 の gap 項目を `moved` で各分野へ送る
- research/08 の「その他」（インタラクティブ・乱択・bitset など）は担当 A の `misc` が持ち主。担当 G は `moved` で misc へ送る
- research/02 の確率・期待値・ゲームの DP と包除 DP は担当 F の `comb` が持ち主。担当 B は `moved` で comb へ送る
- 数学の記法（research/06）は担当 I の `start` の「記法と用語の約束」が持ち主
- 意味が近いのに key も題名も違う項目（例：DP 側の「ゲーム DP」と comb 側の「ゲームの基本」）は、設計書 §4.2 の持ち主が取り込み、相手は `moved` にする

## 7. 検証

`python3 tools/check_catalog.py` で次を確かめる（メインのセッションが実行する）。

- YAML が読め、必須の項目がある
- id が全分野で一意
- `prerequisites`・`related` が解決できる（id か、どこかの `merged_keys` に入っている key）
- 前提の循環がない
- 前提のレベルが自分より高くない（警告）
- `kind` が語彙にある
- 問題 ID が実在する
- 全調査の key が、id・merged_keys・moved・dropped のどこかで処理されている
