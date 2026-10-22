# dynamic-tree の報告（b4）

- 書いたファイル：docs/tree/dynamic-tree.md、snippets/dynamic-tree/link-cut-tree.{cpp,yaml}、docs/img/dynamic-tree/before.svg・after.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-22）。sections に `{title: 自作するときの要点と Library Checker, anchor: library}` を足した
- 検査の結果：check_pages（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、check_snippets（期待と違う 0。乱数の link・cut・加算・パスの和を愚直な森と比べる assert を main に入れた）、textlint（エラー 0・警告 0）。SVG は render_svg.py の 360px で目視した
- 使った出典：ei1333.hateblo.jp（Link-Cut 木）、ferin-tech.hatenablog.com（Link-Cut tree）、ei1333.github.io（dynamic-tree の項目・link-cut-tree.hpp・top-tree.hpp）、kopricky.github.io（Euler Tour Tree）、GitHub の library-checker-problems（tree・graph の dynamic_* の task.md）、drken1215（abc350_g）、cnblogs（abc350_g）
- 新しく noai を確かめたドメイン：ei1333.hateblo.jp・ferin-tech.hatenablog.com・kopricky.github.io・sotanishy.github.io（使っていない）。どれも noai・noimageai の指定なし（2026-10-22）

## 台帳への提案

- abc350_g｜approach（dynamic-tree の役割の説明）｜「Link-Cut Tree で親を管理する解法もある」は第三者の解説で裏付けられなかった（drken はマージテク、cnblogs は次数で分けた bitset。drken の記事は「Link-Cut木」のカテゴリに入っているが、本文に LCT の解法はない）。approach を「辺の追加は link、質問は evert(u)・expose(v) でパスの頂点数が 3 なら真ん中を答える（LCT の解法は想定外の別解）」とするか、LCT の裏付けがないことを注記するよう提案する
- 変更なし：summary・difficulty・evidence はそのまま使った

## front matter・catalog への提案

- summary の「償却 O(log N)」を「ならし O(log N)」に（付録 A の正規形は「ならし計算量」）。level-advanced・tree/index・kind-data-structure の一覧も gen_site で追従するはず

## 用語集への提案

- 優先パス｜preferred-path｜Link-Cut Tree で、各頂点が高々 1 つ選ぶ「優先する子」への辺をたどった縦の鎖。重いパスと違い、操作のたびに付け替える。（本文では定義を書き、リンクは張っていない）
- （付録 A への提案）Link-Cut Tree（LCT）・Euler Tour Tree（ETT）・Top Tree・expose・evert を正規形に足す

## 手引きへの提案

- 特になし。overview で「サイン」「計算量」を独立の見出しにせず、冒頭の要点と sections の中身の節（add-only が使い分けを兼ねる。§15-4 で comparison は置かない）で兼ねた。学ぶための資料は hld・balanced-bst にならって sections に載せない `## 学ぶための資料 {#resources}` にした

## 問題の補充の候補

- 確認済みの例題は 0 問（発展の例題 0〜2 の範囲内）。ABC で動的木が必須の問題は見つからなかった（研究の 04-tree §4.30 と同じ結論）。ap.py での新しい候補探しは、LCT を想定解とする第三者の解説が ABC に見当たらないため行っていない
- Library Checker の dynamic_tree_vertex_add_path_sum・dynamic_tree_vertex_set_path_composite・dynamic_tree_vertex_add_subtree_sum・dynamic_tree_subtree_add_subtree_sum・dynamic_graph_vertex_add_component_sum を、本文の library の節に judge.yosupo.jp のリンクで置いた（§15-5。task.md で内容を確かめた）

## 未解決の点

- 練習の方針の LCT による abc350_g の解き方（evert・expose でパスの頂点数が 3 なら真ん中）は自分の推論で、第三者の解説では確かめていない。マージテクと bitset の方針は解説で確かめた
- 「1 回の expose で優先する子が付け替わる回数はならし O(log N)、splay のポテンシャルと合わせて expose がならし O(log N)」「splay 以外の平衡二分探索木では O(log^2 N)」は Sleator–Tarjan の結果として知られた事実で、資料（ei1333 の記事はならし O(log N) と明記）で一部を確かめたが、証明そのものは読んでいない
- Top Tree が「直径や最も遠い頂点」を保てることは、ei1333 の Library の diameter.hpp が top-tree.hpp に依存していることから書いた
- 動く図は catalog の visual が null なので作っていない。静的な SVG 2 枚（expose の前後）を置いた

## 検証の指摘への対応（b4 の直し）

- 指摘 1（直すべき）：(a) で直した。snippet に `toggle(x)`（印を立てるときに自分の左右を入れ替える）を作り、`push` は子に `toggle` を配るだけ、`evert` は `toggle(x)` だけにした。本文の「保つ性質」と非可換な演算の項に `toggle` で入れ替えることを添えた。check_snippets（乱数の比較を含む）は期待と違う 0
- 指摘 2：splay 木の 1 文の説明と、rotate・splay の 1 文を足した
- 指摘 3：splay 木の部分（node の取り込み）を `??? note` の折りたたみに入れ、本文に見せるのは expose の範囲だけにした
- 指摘 4：表の行に「森で」を入れ、一般のグラフでオンラインの連結性は範囲外と 1 文添えた
- 指摘 5：「2 つの位置で列を 3 つに切り、真ん中（今の根から見て遠い側の木）を取り出す」にした
- 指摘 6：「expose 1 回はならし $O(\log^2 N)$」にした
- 指摘 7：link-cut の節の 1 文目に「$N$ は頂点数」を添え、辺に値があるときの頂点の数は言葉で書いた
- 指摘 8：採らない（front matter の summary はメインが直す。上の「front matter・catalog への提案」のとおり）

## 追加の提案（メインへ）

- 検証役の参考の指摘：docs/ds/balanced-bst.md 108 行と snippets/balanced-bst/implicit-treap.cpp 30〜36 行も、「自分には反映済み」の説明と「push で自分の左右を入れ替える」コードが食い違っている。このページと同じく、印を立てるときに入れ替える形にそろえることを提案する（担当外のため触っていない）
