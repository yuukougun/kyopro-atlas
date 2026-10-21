# minimum-spanning-tree（最小全域木）の報告

- 書いたファイル：docs/graph/minimum-spanning-tree.md、snippets/minimum-spanning-tree/{kruskal,prim-dense,query-edges}.{cpp,yaml}、docs/img/minimum-spanning-tree/kruskal-steps.svg
- front matter で変えたもの：complexity・stage（draft）・updated、sections の kruskal-prim の title（「Kruskal 法と Prim 法（密なら O(N^2) の Prim）」→「クラスカル法とプリム法（密なら O(N^2) のプリム法）」。付録 A の正規形に合わせた。anchor は変えていない）
- 検査の結果：check_pages（エラー 0・警告 0）、fix_problems --check（0）、check_snippets（3 件・期待と違う 0）、textlint（エラー 0・警告 18。助詞の重複と、数式を含む文の長さ・読点の数）
- 使った出典：参考の節のとおり（kyo-pro・drken・Lanly（cnblogs）・ikatakos（解法の節だけ）・E869120（GitHub）・hamayan・ACL document_ja）。どれも付録 B のドメインで、新しく noai を確かめたドメインはない
- 動く図：作っていない（catalog の visual は priority 2）。代わりに静的な SVG（kruskal-steps.svg）を置き、図の前後に文章で流れを書いた。後で動く図を作るなら、同じ 5 頂点 7 辺（A–B 1, B–C 2, A–C 3, C–D 4, B–D 5, D–E 6, C–E 7）で、辺を重み順に見て成分の色が混ざり、閉路を作る辺が捨てられるステップ送りにするとよい。置き場の div は書いていない

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc218_e・abc235_e・abc352_e・abc282_e・arc076_b・typical90_aw・abc210_e・abc364_f・abc355_f | summary | 末尾に「。」を付ける（abc469_f だけ「。」で終わっていて、ページの中で不ぞろい） | 表記の統一 |
| arc076_b | summary | 「平面上の町を結ぶ費用が 2 町の x 座標の差と y 座標の差の小さい方のとき、すべての町をつなぐ最小費用を求める。」（`|Δx|` は表に転記すると `|` が崩れるため） | style-guide §6（表の中の `|`） |

役割（例題 2・練習 5・力試し 3）は catalog のとおりで、変更の提案はない。

## catalog・front matter への提案

- summary の「Kruskal 法」「Prim 法」を、付録 A の正規形「クラスカル法」「プリム法」にする。案：「連結グラフの全域木のうち辺の重みの和が最小のものを、辺を重みの昇順に見て閉路を作らない辺だけを採るクラスカル法か、頂点を 1 つずつ伸ばすプリム法で求める。候補の辺を減らせば完全グラフにも使える。」
- prh.yml：「Kruskal 法」→「クラスカル法」、「Prim 法」→「プリム法」の検出を足す（別名の行は textlint の対象外なので影響しない）

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| 全域木 | spanning-tree | 連結な無向グラフのすべての頂点を含み、閉路のない部分グラフ。頂点数が $N$ なら辺はちょうど $N - 1$ 本である。 |
| カット | cut | グラフの頂点を 2 つの組 $S$ と $V \setminus S$ に分けること。両端が別の組にある辺を、カットを渡る辺と呼ぶ。最小カット（フロー）では、渡る辺の容量の和をカットの容量と呼ぶ。 |

本文ではこの 2 つの anchor でリンクしている。

## 手引きへの提案

- §7「用語へのリンクはページの中で最初に出たときの 1 回だけ」が、ほかの手法のページへのリンクにも及ぶかが分からなかった。節ごとに単独で読まれる前提（§1）と合わせ、「同じ節の中では 1 回、節が変われば再びリンクしてよい」と明記するとよい（このページはその解釈で書いた）

## 問題の補充の候補

確認済みの問題で足りたので、補充の候補はない。参考までに、research/03 §4.E にある abc328_e（N ≤ 8 の全域木の全列挙）は small-graph-brute-force の担当と考え、このページには載せていない。

## 未解決の点

- 練習 abc352_e の制約（N・M・ΣK_i の上限）は、裏付けの Lanly 氏の記事に書かれておらず、確かめていない。本文では制約の値に触れていない
- 例題 abc218_e の制約も裏付けの記事になく、本文では触れていない
- SVG は描画の道具が手元になく、目で確かめていない（座標を計算し、辺の交差とラベルの重なりがないことだけ確かめた）。検証役に表示の確認を頼みたい
- [辺の重みの種類が少ないとき] は union-find-applications#multiple-uf と内容が重なる。こちらは式の導き方と 0/1 の重みの型、向こうは Union-Find の持ち方として書き分けたが、メインの判断で片方をリンクだけにしてもよい
- 使用量の目安：道具の呼び出し約 35 回、Web 取得 9 回（WebFetch 8 回と題名の確認の curl）

## 検証の指摘への対応（2026-10-21）

- 直すとよい 1〜5 はすべて採って直した（#abc218_e の方針を「報酬が正の辺」にそろえ 0 の辺の一言を足す、#maximum の「全域木か、それに辺を足したもの」、#modeling 後半の「境目」をやめて隣り合う頂点 $j, j + 1$ の組と書く、#reduce-candidates を「最小全域木の重みは同じ」に、プリム法の push を「高々 2 回（両向き）」に）
- front matter の summary の「Kruskal 法」「Prim 法」を「クラスカル法」「プリム法」に直した（担当ページ内のため。検証役も賛成）
- 採らなかった指摘：なし
- メインへの提案（再掲）：用語集に anchor `spanning-tree`・`cut` を足す。台帳の `checked` に 2026-10-21 を入れてよいもの：abc235_e・abc282_e・abc355_f・abc210_e（検証役が evidence で確認）
