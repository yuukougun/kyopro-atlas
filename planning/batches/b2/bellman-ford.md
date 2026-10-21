# bellman-ford の報告と提案（b2）

- 書いたファイル：docs/graph/bellman-ford.md、snippets/bellman-ford/bellman-ford.{cpp,yaml}、docs/img/bellman-ford/rounds.svg・negative-cycle.svg
- front matter で変えたもの：complexity（`O(NM)（負閉路の影響を受ける頂点の判定を含めても O(NM)）`）・stage（draft）・updated。sections は変えていない
- 検査の結果：check_pages エラー 0・警告 0。fix_problems --check 直すべき行 0。check_snippets 7 case 一致（main の中でワーシャルフロイド法による全探索と 2000 個のランダムなグラフで照合）。textlint エラー 0、警告 4（2 枚の図の代替テキストの文の長さ・読点・助詞。§14-25 で残してよいもの）
- 図：render_svg.py で 360px・720px を目で確かめた
- 使った出典：kmjp（ABC137 E・ABC404 G）、drken（ABC061 D。2N 回で dist[N] の変化だけを見る方法の反例もここ。本文の反例は符号を反転した自作の形）。新しく noai を確かめたドメインはない
- 動く図：catalog の visual は priority 2・static。静的な SVG 2 枚（反復ごとの dist の表、3 種類の頂点の塗り分け）で代えた。動く図の div は置いていない

## 台帳への提案

- abc137_e｜summary｜変更なし（本文の方針で「コインが足りないときは持っている分だけ払う」を使った。kmjp の解答の 0 との max から確かめた）
- abc404_g｜変更なし

## 用語集への提案

- 三角不等式｜triangle-inequality｜最短距離 $\mathrm{dist}$ がすべての辺 $u \to v$（重み $w$）で $\mathrm{dist}[v] \le \mathrm{dist}[u] + w$ を満たすこと。どの辺でも緩和が起きない状態と同じで、差分制約・ポテンシャルの正しさの根拠になる。（本文ではリンクしていない。dijkstra・difference-constraints と共有の語なので、足すならメインがリンクを張る）

## 手引きへの提案

- §5 graph に「負閉路があるページ（bellman-ford・warshall-floyd・difference-constraints）は、負閉路の有無ではなく、答えを聞かれた頂点が影響を受けるかで判定すると書く。届かない頂点（INF）からは緩和しない」を足すとよい

## ほかのページのリンクの張り替え（handoff §1.3 の 7 か所）

bellman-ford が draft になったので、節へ張り替えられる。
- dijkstra:144（負辺で壊れる例の後）→ そのまま（ページ）でよい
- dijkstra:193（Johnson）→ `bellman-ford.md#vs-potential`
- warshall-floyd:115（負閉路で値が小さくなる囲み）→ `bellman-ford.md#relevant-cycles`
- dp-dag:144（負の重み）→ `bellman-ford.md#longest-path` も候補
- graph-basics:59・warshall-floyd:299・dijkstra:248 はページへのままでよい

## 問題の補充の候補

練習が 1 問だけで、目安（2〜6）に届かない。負辺の最短路が本体の ABC は少ない（catalog の problems_note のとおり）。
- abc237_e（ABC237 E. Skiing、diff 1208、台帳では dijkstra の練習）｜標高の差で楽しさが増減する移動の最大値。負辺があるがベルマンフォード法では間に合わず、ポテンシャルでダイクストラ法にする。vs-potential の節の「見分け」の練習として bellman-ford の practice にも載せる案｜裏付け：https://kyo-pro.hatenablog.com/entry/ABC237E （台帳の evidence と同じ）
- ほかに ap.py と第三者の解説で新しい候補を探すことはしていない（時間の都合）。差分制約の問題（abc216_g など）は difference-constraints の持ち物で、負辺がないのでこのページには合わない

## 未解決の点

- 例題の制約（N・M の上限）は解説で確かめきれなかったので、本文に書いていない
- SPFA の最悪ケースは「作った入力では遅くなる」とだけ書き、具体的な構成や数値は書いていない

## 検証の指摘への対応（b2 verify）

- 指摘 1（証明の一文）：直し方のとおりに直した
- 指摘 2（反例が drken の記事と同じ数値）：自前の例（$s \to t$ が $-5 \times 10^8$、$a \to b$ が $-2$・$b \to a$ が 1、$b \to t$ が $5 \times 10^8$、約 $10^9$ 周）に替え、snippet の cases 3 も同じ例にした。報告の「自作の形」は誤りだった
- 指摘 3（rounds.svg の「5」）：y を 68 → 86 に下げ、s→b の弧の内側に置いた
- 指摘 4（前提の文の範囲）：方法 1 の前提とし、方法 2 は自然に満たされると書いた
- 採らなかったもの：なし
