# connected-components の報告と提案（工程8b・b1）

- 書いたファイル：docs/graph/connected-components.md、snippets/connected-components/bfs-tally.{cpp,yaml}、snippets/connected-components/acl-dsu.{cpp,yaml}、docs/img/connected-components/components.svg
- front matter で変えたもの：complexity・stage（draft）・updated。sections の pitfalls の title を「孤立点・多重辺・自己ループの数え方」から「落とし穴（孤立点・多重辺・自己ループ・再帰の深さ）」に変えた（anchor はそのまま。§13-1 の定型の「落とし穴」と anchor が重なるため、中身を合わせて 1 節にした）。節 `next-steps`（上位の手法とのつながり）を足した
- 検査の結果：check_pages エラー 0・警告 0、fix_problems --check 直す行 0、check_snippets 期待と違う 0、textlint エラー 0・警告 3（2 つは「に」の重なりで読みに支障がないと判断、1 つは台帳の abc157_d の summary の「でも」）
- 使った出典：drken（abc177_d・abc157_d・abc131_f）、kyo-pro（abc292_d）、kazun-kyopro（abc292_d。制約 u ≤ v で自己ループがありうること）、ACL document_ja/dsu.md。新しく noai を確かめたドメインはない
- 図：静的な SVG 1 枚（visual は priority 2）。動く図は作っていない

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc284_c | pages | `{id: connected-components, role: practice}` を足す（成分の数を数える最小の練習。基礎のページの練習が 2 問しかない） | https://drken1215.hatenablog.com/entry/2023/09/28/022105 （台帳の evidence） |
| abc157_d | summary | 「…同じ成分にいて、友達とブロック相手のどちらでもない人の数を求める」（textlint の no-doubled-joshi「でも」の警告を消すため。任意） | — |

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| 孤立点 | isolated-vertex | どの辺の端点にもなっていない頂点である。それだけで 1 つの連結成分になり、頂点 1・辺 0 の木として数える。 |
| 多重辺 | multi-edge | 同じ 2 頂点を結ぶ 2 本目以降の辺である。連結性は変えないが、辺数や次数を数える問題では 1 本ずつ数える。 |
| 自己ループ | self-loop | 両端が同じ頂点の辺 $(v, v)$ である。無向グラフの次数では 2 と数え、長さ 1 の閉路とみなすことが多い。 |
| 森 | forest | 閉路を持たない無向グラフである。各連結成分は木で、成分の数は $N - M$ になる。 |
| 完全二部グラフ | complete-bipartite-graph | 頂点が 2 つの組に分かれ、異なる組の頂点どうしがすべて辺で結ばれ、同じ組の頂点どうしには辺がない二部グラフである。 |
| 超頂点 | super-vertex | 複数の頂点をまとめてつなぐために足す仮の頂点である。値ごとに 1 頂点を足して同じ値の位置を結ぶと、辺の数を $O(N^2)$ から $O(N)$ に減らせる。（付録 A に語はある。用語集に anchor がまだなければ） |

## 手引きへの提案

- §13-1 の定型の節「落とし穴 {#pitfalls}」と、catalog の sections が anchor `pitfalls` を中身の節として持つ場合の扱いを決めておくとよい。今回は sections の title を「落とし穴（…）」に変えて 1 節にまとめた
- 基礎の technique の構成（§4）にある「上位の手法とのつながり」は、sections に載せるか（中身の節か定型の節か）を §13-1 に明記するとよい。今回は見本（binary-search-answer の next-steps）に合わせて sections に足した

## 問題の補充の候補

| 問題 ID | 何を問うか | 裏付け |
| --- | --- | --- |
| abc284_c（C, diff 193） | 単純無向グラフの連結成分の個数を求める。台帳にあり確認済み（graph-basics の練習）。このページの練習にも足したい | https://drken1215.hatenablog.com/entry/2023/09/28/022105 |
| abc199_d（D, diff 1804） | N ≤ 20 のグラフの 3 彩色の数。連結成分ごとに DFS で塗り、成分ごとの数を掛け合わせる（台帳にあり確認済み。small-graph-brute-force の力試し）。「成分ごとに独立に数える」の力試しとして参照の候補 | https://blog.hamayanhamayan.com/entry/2021/04/25/002321 |

## 未解決の点

- abc292_d で多重辺がありうるかは確かめきれなかった（自己ループは制約 u ≤ v からありうる）。本文では自己ループだけに触れた
- 「座標や値を頂点にして成分を考える」節の中で、力試し abc131_f の考え方（完全二部グラフになる）をそのまま説明している。問題名は出していないが、力試しの方針と重なる。問題を伏せたいなら、節の例を別の型にする必要がある
- values-as-vertices の節の後半で、Union-Find のページの練習（abc206_d、値の一括置換）を `../ds/union-find.md#practice` で参照した
- 使用量の目安：道具の呼び出し 約 30 回、Web 取得 5 回
