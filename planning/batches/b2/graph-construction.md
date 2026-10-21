# graph-construction の報告（b2・青）

- 書いたファイル：docs/graph/graph-construction.md、snippets/graph-construction/spanning-trees.{cpp,yaml}、snippets/graph-construction/restore.{cpp,yaml}、docs/img/graph-construction/dfs-bfs-trees.svg
- front matter で変えたもの：complexity（`DFS 木・BFS 木 O(N + M)、距離表からの復元 O(N^3)`）・stage（draft）・updated（2026-10-21）。sections は変えていない
- 検査の結果：check_pages エラー0・警告0、fix_problems --check 直すべき行0、check_snippets 2 件とも期待どおり、textlint エラー0・警告3（54 行目は図の代替テキストの長さ、253 行目は参考のリンクの題名の長さ、122 行目は「は」の重複の誤検出に近いもの）。SVG は render_svg.py で 360px・720px を目で確かめた。非再帰の DFS 木が再帰と同じ木になることは、手元でランダムなグラフ 300 個で確かめた（snippet には入れていない）
- 動く図：catalog の visual は priority 2・static なので、静的な SVG（DFS 木と BFS 木の対比）で代えた。div は置いていない
- 使った出典：
  - https://kyo-pro.hatenablog.com/entry/ABC251F（台帳の evidence。付録 B）：ABC251 F の方針
  - https://kazun-kyopro.hatenablog.com/entry/ABC/251/F（付録 B の kazun-kyopro）：ABC251 F の 2 つの条件（「木に入らない辺」についての条件であること）と制約
  - https://blog.hamayanhamayan.com/entry/2017/09/17/212251（付録 B）：ARC083 D の問いと方針（-1 の判定・等号で外す）
  - https://qiita.com/e869120/items/eb50fdaece12be418faa（台帳の evidence）：ARC083 D をワーシャルフロイド法の問題に分類していることだけ。問いの裏付けとしては弱い
  - https://kmjp.hatenablog.jp/entry/2022/03/22/0900・https://kmjp.hatenablog.jp/entry/2021/12/19/1030：ABC244 G・ABC232 H の方針
  - 新しく noai を確かめたドメインはない

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| arc083_b | evidence | `https://blog.hamayanhamayan.com/entry/2017/09/17/212251` を足す（今の qiita は分類の一覧で、問いの中身を裏付けない） | 記事で問いと方針を確かめた |
| abc251_f | evidence | `https://kazun-kyopro.hatenablog.com/entry/ABC/251/F` を足す（kyo-pro の記事には 2 つの条件の文面がない） | 記事で条件を確かめた |

summary はどれも表記・事実とも問題なし。abc244_g の「長さ 4N 以下」は kmjp の記事に書かれておらず、確かめきれていない（未解決の点）。

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| 後退辺 | back-edge | DFS 木に入らない辺のうち、頂点とその祖先を結ぶものである。無向グラフの DFS 木では、木に入らない辺はすべて後退辺になる。 |
| 横断辺 | cross-edge | 探索木に入らない辺のうち、どちらも相手の祖先でない 2 頂点（別の枝）を結ぶものである。無向グラフの DFS 木には現れず、有向グラフの DFS や BFS 木には現れる。 |

本文では後退辺を用語集へリンクしていない（anchor がないと check_pages がエラーにするため）。用語集に足したら、dfs-tree の節の最初の「後退辺」を `../guide/glossary.md#back-edge` へリンクしてほしい。

## 手引きへの提案

- §13-5 は「用語集へのリンクは提案した anchor で書いてよい（まだなくても）」とあるが、check_pages はこれをエラーにする。執筆者は検査を通すためにリンクを外すことになるので、どちらかにそろえたい（警告に下げるか、§13-5 を「リンクは用語集に足した後でメインが張る」に改める）
- 非再帰の DFS で「積むときに印を付ける」書き方は DFS 木を作らない（本ページの落とし穴）。§9 の「非再帰の DFS は v と ~v を積む形にそろえる」に、「親（DFS 木）が要るときは（頂点, 親）の組を積み、取り出したときに印と親を決める」を添えるとよい

## 申し送りへの対応（handoff §1.3）

ほかのページからこのページへ anchor なしで張られているリンクの張り替え先の案：

- warshall-floyd:193（距離表から最小のグラフを作る話）→ `graph-construction.md#from-distances`
- tree-construction:189（一般のグラフを距離表から作る）→ `graph-construction.md#from-distances`
- construction:174（グラフや木の作り方そのもの）→ ページへのリンクのままでよい（特定の節を指していない）

## 問題の補充の候補

練習が 1 問（abc244_g）だけで、abc319 以降の問題がない。

| 問題 ID | 何を問うか | 役割の案 | 裏付けの URL |
| --- | --- | --- | --- |
| arc143_d | A・B の列から決まるグラフの辺の向き（どちらの組で結ぶか）を選び、橋の数を最小にする。DFS の順に向きを付けて閉路を作る（DFS 木の辺と後退辺を逆向きにする向き付けと同じ考え方） | 力試し（diff 2229、ap.py で確認） | https://kmjp.hatenablog.jp/entry/2023/03/16/0900（方針は「DFS 順で向きを付け閉路を作る」の短い記述だけ。コードは辺をたどりながら向きを決める形。採るなら別の解説でも確かめたい） |

abc319 以降で DFS 木・BFS 木の性質そのものを使う ABC は、ap.py の題名検索では見つからなかった。abc451_g（XOR のウォーク。全域木と木に入らない辺の閉路の XOR を使う）は近いが、台帳では別のページの問題で、本ページの性質（祖先と子孫）は使わないので候補にしなかった。

## 未解決の点

- abc244_g の summary の「長さ 4N 以下」：kmjp の記事に上限の記述がなく、確かめきれていない。本文の parity-walk の節は上限を $4N - 3$ と自分で導いて書いた（列の長さを頂点の個数で数えた場合）。問題の「長さ」が頂点の個数か辺の本数かは確かめていない
- arc083_b の制約（N ≤ 300、値 ≤ 10^9）は記憶で、記事のコードの配列の大きさ（303）と合うことだけ確かめた。本文では「N が数百まで」「値が 10^9 程度なら」とぼかして書いた
- parity-walk の節は level 黄で、使う問題（abc244_g）は練習に置いた。節の本文で手順を書いたので、練習の方針の折りたたみと内容が重なる（手引き §10 の「一覧で解き方が見えないように」は満たしている）
- 使用量の目安：道具の呼び出し約 35 回、Web 取得 9 回（WebFetch 7・WebSearch 4 のうち重なりあり）

## 検証の指摘への対応（直し）

- 直した：1（橋は「p かその祖先に届けば橋でない」、関節点は真の祖先と区別）・2（長さ K 以上の閉路の主張を外し、奇閉路の判定に限定。逆が言えないことを明記）・3（ウォークの長さを列の頂点の個数で数えると断り、ABC244 G に合わせたことを明記。$2N - 1$・$4N - 3$・確認問題の「頂点が 0 個」）・4（図を頂点 0〜5 に付け直し、本文・代替テキスト・snippet の case の注記をそろえた。導入に問題文の $v$ はコードの $v - 1$ と明記。落とし穴と ABC251 F に「0-indexed のコードでは頂点 0」を添えた）・5（$N = 300$ で約 $4.5 \times 10^{13}$）・6（隣は番号の小さい順と図の前と代替テキストに明記）・7（図の 12・13px の文字を 14px に上げた。360px・720px で確かめた）・8（合流する頂点 $w$ を使う形に書き換え）・9（前提から DFS 木の性質を外し、どの全域木でもよいが DFS なら作りながらたどれる、と理由を書いた）・10（非再帰版の説明に、親を記録するため dfs のページの `~v` の形ではなく（頂点, 親）の組を積むと一言）
- 採らなかった：11（練習の補充）。arc143_d を足すかは台帳と役割の変更なのでメインが決める（執筆者の候補のまま）
- 指摘 9 の見出し「DFS 木をたどって偶奇を合わせる」は sections の変更になるので変えていない。変えるなら「全域木をたどって偶奇を合わせる」（anchor parity-walk はそのまま）を提案する
- 検査：check_pages エラー0・警告0、fix_problems --check 直すべき行0、check_snippets 期待と違う 0、textlint エラー0・警告3（従来と同じ 54・122・255 行目）

## 台帳への提案（検証を受けて追加）

- abc244_g の evidence に `https://blog.hamayanhamayan.com/entry/2022/03/21/163327` を足す（上限 4N と K が列の頂点の個数であることの裏付け。検証役が確認）
- arc083_b・abc251_f・abc244_g・abc232_h の checked を 2026-10-21 にする（検証役が evidence で確認）
