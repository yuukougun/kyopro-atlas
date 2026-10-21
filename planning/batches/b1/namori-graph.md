# namori-graph の報告と提案（工程8b・バッチ b1）

- 書いたファイル：docs/graph/namori-graph.md、snippets/namori-graph/peel-leaves.{cpp,yaml}、docs/img/namori-graph/redraw.svg・peel.svg
- front matter で変えたもの：complexity・stage（draft）。updated は 2026-10-21 のまま（今日の日付と同じ）。sections は変えていない
- 検査：check_pages（エラー 0・警告 0）、check_snippets（期待と違う 0）、textlint（エラー 0、警告 1：「2 点間の距離」の項目の文の長さ。数式を含む文なので残した）。fix_problems --check は終了コード 1 だが、指摘はすべてほかのページ（graph/time-dependent-dijkstra.md・graph/warshall-floyd.md）の行で、このページの行には指摘なし
- 図：visual は priority 2 の static なので、SVG 2 枚（閉路を横一列にした描き直し、葉を削る 3 段階）で書いた。動く図は作っていない
- 使った出典：zenn.dev/fjnkt98（abc266_f の問いと方針）、kyo-pro.hatenablog.com（abc292_d の方針）、ACL の document_ja/dsu.md。drken1215.hatenablog.com のカテゴリ「なもりグラフ」と abc378_f の記事は補充の候補探しに読んだ（本文には使っていない）。新しいドメインはない

## 台帳への提案

- abc266_f｜summary｜文末に「。」を付ける（ほかの問題の summary とそろえる。本文の行は台帳から作られるので本文だけでは直していない）｜—
- abc292_d｜summary｜同上（文末の「。」）｜—

## 用語集への提案

- 単純パス｜simple-path｜同じ頂点を 2 回通らないパス。本文ではグラフの基本（graph-basics#terms）へリンクしたので、用語集に足すかはメインの判断に任せる
- 全域木｜spanning-tree｜連結なグラフのすべての頂点を含み、辺を N − 1 本だけ選んでできる木（connected-components からも提案済みのはず。重複なら不要）
- 多重辺｜multi-edge・自己ループ｜self-loop：ほかのページから提案済みの anchor をそのまま使った

## 手引きへの提案

- なし。ひとつだけ、§13 で「確認問題」を見出しにまとめるかインラインにするかの目安があると迷わない（このページはインラインの折りたたみ 2 つで、`## 確認問題 {#quiz}` は置いていない）

## 問題の補充の候補

catalog の problems_note のとおり、練習が 1 問（abc292_d、diff 579 で基礎の帯）で abc319 以降の問題がない。

- abc378_f（F. Add One Edge 2、diff 1436）：木に辺を 1 本足してできるグラフのうち、閉路の頂点の次数がすべて 3 になるものの数を数える。次数 3 の頂点の成分ごとに、隣の次数 2 の頂点から 2 つ選ぶ。台帳では tree-basics の練習。なもりグラフの「木＋1 辺で閉路がちょうど 1 つ」の練習としても使える（abc319 以降）。裏付け：https://drken1215.hatenablog.com/entry/2024/11/04/002341
- abc235_e（E. MST + 1、diff 1304）：最小全域木に辺を 1 本足すとできる閉路の最大の辺と比べる。台帳では minimum-spanning-tree の例題。research/04 §5.1 がなもりの練習に挙げている。裏付け：https://kazun-kyopro.hatenablog.com/entry/ABC/235/E
- jsc2019_qual_e（E. Card Collector、diff 2691）：drken 氏のカテゴリ「なもりグラフ」にある（各成分が辺 ≤ 頂点、すなわち木かなもりになる条件で選ぶ）。発展の帯なので力試しにも重い。記事 https://drken1215.hatenablog.com/entry/2019/09/27/185400 は未読で、問いは確かめていない

## 未解決の点

- chapter が「有向グラフ」だが、本体は無向のなもりグラフで、有向の話は節 directed-version だけである。research/03 は Functional graph の節、research/04 は木の分野としていた。並び（Functional graph の隣）としては今のままでよいと思うが、念のため記す
- 「閉路の辺を 1 本外して場合分けする」「円環にして 2 周分並べる」は型として書いたが、台帳に例となる問題がない（ABC の確認済みの問題が見つからなかった）
- ACL の囲みに `d.size(x)` を「その木の頂点数」と書いた（閉路の辺を結ばないので成り立つ）
