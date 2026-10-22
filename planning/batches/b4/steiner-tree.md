# steiner-tree の報告と提案（b4）

- 書いたファイル：docs/graph/steiner-tree.md、snippets/steiner-tree/steiner.{cpp,yaml}、docs/img/steiner-tree/example.svg・transitions.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-22）。sections に `{title: 自作するときの要点と確かめ方, anchor: library}` を足した。要点の「何ができるか」から計算量の式を除き、計算量の行に移した（summary は変えていない）
- 検査の結果：check_pages エラー 0・警告 0、fix_problems --check 直す行 0、check_snippets 期待と違う 0、textlint エラー 0（警告 10：数式を含む文の長さ・図の代替テキストの長さ・助詞の重複の誤検出）
- 図：2 枚とも render_svg.py で PNG にして目で確かめた
- 使った出典：ikatakos（abc364・abc395 の解法の節だけ）、kmjp（abc364_g・abc395_g）、ei1333 のライブラリのドキュメント（github.com）、library-checker-problems の info.toml と task.md（raw.githubusercontent.com で取得。中身は github.com のリポジトリ）。新しく noai を確かめたドメインはない

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠の URL |
| --- | --- | --- | --- |
| abc395_g | evidence | 追加：https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2025/0301_abc395 | 解法の節に、指定頂点に 1 点足した DP を前計算し、もう 1 点を根の頂点として読む方法がある。kmjp の記事は本人が TLE のまま終えたと書いているので、裏付けとしては ikatakos の方が確か |
| abc364_g | checked | 2026-10-22 | ikatakos・kmjp の解法の節で問いと方針を確かめた |
| abc395_g | approach | 「指定の点に 1 点足した最小シュタイナー木の DP を前計算し、もう 1 点は根の頂点として読む」 | 上の ikatakos。いまの「2 頂点を足した」は DP を (S, T) の組ごとに回すように読める |

## 用語集への提案

- 指定頂点（ターミナル）｜terminal｜最小シュタイナー木などで、すべてつなぐよう指定された頂点。指定されていない頂点は経由してよい。steiner-subtree と steiner-tree の両方で使う

## 手引きへの提案

- §5 graph に「最小シュタイナー木の DP の重みは 0 以上が前提（木にできることとダイクストラ法の両方に要る）。重み 0 の辺は復元で 2 回出ることがあるので印で除く」を足すかは任せる（持ち主は steiner-tree#library）

## 問題の補充の候補

- 例題 1・練習 1 で、発展の概要の目安（例題 0〜2）は満たしている。新しく探した候補はない
- Library Checker の minimum_steiner_tree（N ≤ 100、M ≤ 1000、K ≤ 12、重み 1〜10^9、辺の番号も出力）を練習の小見出しに置いた

## 未解決の点

- abc364_g の制約（N・M・K の上限）は問題文を開けないので確かめていない。本文の見積もり（K = 10、N = 4000、M = 8000）は「なら」の仮定として書いた。kmjp のコードの配列の大きさから N は 4000 程度と推測されるが、本文には問題の制約として書いていない
- abc395_g の計算量 O(3^K N^2 + 2^K N^3) は ikatakos の解法の節の値（配列のダイクストラ法にした場合）。制約の値は確かめていない
- 要点の「何ができるか」の 1 文目は summary から計算量を除いた形にした。summary 自体を直す必要はないと考えるが、食い違いと見るなら summary に合わせて戻してよい
- 動く図は catalog の visual が null なので置き場の div を置いていない

## 検証の指摘への対応（2026-10-22）

- 1（直すべき）：導入を「一般のグラフでこの DP の要る ABC の問題は、これまで difficulty 2400 を超える G だけである」に限り、木の易しい版が D にも出ることを #on-tree へのリンクで添えた
- 2：#dijkstra-step に「$v$ が $S$ に含まれない場合」の条件と、指定頂点なら分ける遷移で $T = \{v\}$ とする一言を足した
- 3：#library を「`long long` で約 3.3 GB になり、メモリ制限（1024 MB など）に収まらない」に改めた
- 4：transitions.svg の左の楕円を離し（cx 55・145、rx 40）、v の上に「v は両方の木に入る」と注記した
- 5：見積もりを「指定頂点が 10 個、$N = 4000$、…なら」に言い換えた
- 6：資料の項目を「載っているコードは空集合の値を 0 に置いて実装を簡単にしている」に改めた
- 7：restore の行に「// 辺のもう一方の端点」と注を付け、connects のラムダ `find` を `root` に改めた
- 8：検証役の指示どおり本文は直さず、下の提案に回した

## メインへの提案（検証の指摘 8 から）

- front matter の summary の計算量を `O(3^K N + 2^K (N + M) log N)` にそろえ（complexity と字面を合わせる）、summary と要点の「端点の集合」を本文の語「指定頂点の集合」に改める（要点の 1 文目は summary に合わせて生成・確認されるので、両方を一緒に直すのがよい）
