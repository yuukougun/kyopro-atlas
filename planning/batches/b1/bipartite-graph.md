# bipartite-graph の報告（工程8b・バッチ b1）

- 書いたファイル：docs/graph/bipartite-graph.md、snippets/bipartite-graph/{coloring,odd-cycle,dsu-double}.{cpp,yaml}、docs/img/bipartite-graph/coloring.svg
- front matter で変えたもの：complexity・stage（draft）・updated。sections に「上位の手法とのつながり」（anchor: next-steps、level はページと同じ）を足した。既存の節の title・anchor は変えていない
- 検査の結果：check_pages エラー 0・警告 0。fix_problems --check 直すべき行 0。check_snippets 3 組・期待と違う 0。textlint エラー 0、警告 6（図の代替テキストの長さ、別行数式の行の長さ、「頂点を 2 倍にする」の段落と「燃やす埋める」の行の助詞の重複で、かぎ括弧の中の語を数える誤検出）
- 使った出典：drken1215.hatenablog.com（abc327_d・abc282_d）、qiita.com（bit_otter の abc472_e、drken の蟻本の記事）、ikatakos.com（abc451_f。解法の節だけ）、kmjp.hatenablog.jp と blog.hamayanhamayan.com（3 Steps）。新しいドメインはない
- 図：catalog の visual は static・priority 2。静的な SVG 1 枚（成分ごとの (a, b) と、BFS で同じ色どうしの辺が見つかる例）で代えた。動く図は作っていない

## 台帳への提案

- code_festival_2017_qualb_c｜label｜「CODE FESTIVAL 2017 qual B C. 3 Steps」など読みやすい表示名｜fix_problems の既定の規則で「CODE-FESTIVAL-2017-QUALB C. 3 Steps」になり読みにくい。interfaces.md §3 の表示名の表に code-festival-* を足すのも手
- abc327_d・abc282_d・code_festival_2017_qualb_c｜summary｜末尾に「。」を足す｜abc472_e・abc451_f の summary は「。」で終わっており、ページの中でそろわない
- abc472_e｜summary｜（現状のままでよいが確かめたい）「あれば 1 つ示す」の出力の形は bit_otter 氏の記事に書かれておらず、裏付けがない。記事で確かめられるのは「奇数長の閉路を探す」ことと「公式解説が二部グラフ判定を使う」ことだけ。出力の形を確かめられる第三者の解説を足すか、summary を「無向グラフに長さが奇数の閉路があるかを調べる」に弱めることを提案する｜https://qiita.com/bit_otter/items/9c4ef77dbf7d5ba293e2

## 用語集への提案

- 奇閉路｜odd-cycle｜長さ（辺の数）が奇数の閉路。自己ループは長さ 1 の奇閉路である。無向グラフが二部グラフであることと、奇閉路を持たないことは同じ（本文では本ページの節 `graph/bipartite-graph.md#odd-cycle` で定義したので、用語集に置くならそこへ誘導する形でよい）

## 手引きへの提案

- §10 の label の規則で、contest id が長いコンテスト（code-festival-2017-qualb など）の表示名が決まっていない。表示名の表に足すか、台帳の label を優先する決まりを書くとよい

## 問題の補充の候補（問題ID・何を問うか・裏付けの URL）

- なし。例題 1・練習 3・力試し 1 で目安を満たす。木の 2 色塗り（abc126_d）は tree-bipartite の練習なので、本文では木の節から tree-bipartite へリンクするだけにした

## 未解決の点

- abc327_d で $S_i = T_i$ の組が入力に現れうるかは、drken 氏の記事で確かめられなかった。本文の解法の詳細は「$S_i = T_i$ の組は自己ループで、それだけで No になる」と、現れる場合の扱いとして書いた（現れなくても誤りにはならない）。検証役に制約の確認を頼みたい
- 3 Steps の「グラフは連結」は kmjp 氏の記事（「連結無向グラフが与えられる」）で確かめた
- 図 coloring.svg は手元に描画の道具がなく、XML として正しいことだけを確かめた。表示の確認を検証役に頼みたい
- 「辺を足して矛盾が起きるなら端点で起きる」（頂点を 2 倍にする Union-Find）は本文に短い理由を書き、snippets の assert で確かめた
