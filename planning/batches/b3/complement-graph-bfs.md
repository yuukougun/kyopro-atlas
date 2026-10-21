# complement-graph-bfs の報告（b3）

- 書いたファイル：docs/graph/complement-graph-bfs.md、snippets/complement-graph-bfs/complement-bfs.{cpp,yaml}（範囲 core・count）、snippets/complement-graph-bfs/components.{cpp,yaml}（範囲 core）、docs/img/complement-graph-bfs/take-unvisited.svg
- front matter で変えたもの：complexity・stage（draft）・updated。sections は変えていない
- 検査の結果：check_pages エラー 0・警告 0。fix_problems --check 0 行。check_snippets 2 本とも期待どおり（さらに一時置き場で、N ≤ 8 の乱択 400 件を素朴な補グラフの BFS・本数・連結成分と照合して一致）。textlint エラー 0、警告 3（図の代替テキストの長さ・別行の数式・折りたたみの中の数式を含む文の長さ。§13-8・§14-25 で許された種類）
- 図：take-unvisited.svg を render_svg.py で 360px・720px にして目で確かめた。catalog の visual は static・priority 3 なので静的な図だけにした。360px では凡例の文字が小さいが、同じことを図の後の文章に書いている
- 構成：黄の technique。必要になる場面・処理の流れ・計算量は sections の 3 節で兼ねた（§14-5）。応用の型（補グラフの連結成分・全体から例外を引く）は節の末尾に置いた。ACL は acl: [] なので囲みなし
- 使った出典：kmjp の ABC319 G（例題の方針。層ごとに合計から取り除かれた辺の分を引く形、到達できなければ -1、mod 998244353 はコードで確かめた）、library-checker-problems の task.md（補グラフの連結成分の入出力）
- 新しく noai を確かめたドメイン：なし（kmjp.hatenablog.jp・github.com は付録 B にある）。judge.yosupo.jp の問題ページは本文のリンクに使ったが、本文は JS で描かれていて取得できなかったので、github の task.md を読んだ

## 台帳への提案

- なし（abc319_g の summary・approach はそのまま使えた）

## 用語集への提案

- 補グラフ｜complement-graph｜単純グラフ G に対し、同じ頂点集合の上で、G で隣接しない 2 頂点の組をすべて辺にしたグラフ。完全グラフから G の辺を取り除いたものである。（本文は graph-basics#terms へリンクした。用語集に足すなら graph-basics と同じ定義で）

## 手引きへの提案

- §5 graph に「補グラフの探索は、未訪問の集合を走査して『残す』回数を元の辺に、『取り出す』回数を頂点に割り当てて O(N + M) を示す」を足すとよい（linked-list・ordered-set の rows-and-columns と同じ「消した要素を二度と見ない」型の計算量の言い方をそろえるため）
- Library Checker の問題へのリンクは、本文に置いてよいか（kp-problems の囲みは atcoder.jp 専用）の決まりがない。このページでは連結成分の応用の型の段落に置いた

## 問題の補充の候補

| 問題 ID | 何を問うか | 使い方 | 裏付けの URL |
| --- | --- | --- | --- |
| （見つからず） | — | — | — |

- Web 検索（「補グラフ BFS 未訪問 set AtCoder」など 2 回）では、ABC319 G 以外に補グラフの BFS を使う AtCoder の問題の第三者の解説は見つからなかった。catalog の problems_note のとおり、練習は Library Checker の connected_components_of_complement_graph で補う形にし、本文の連結成分の段落でそれを示した。練習問題・力試しの見出しは置いていない

## 未解決の点

- ABC319 G の制約（N・M の上限、多重辺の有無）は、kmjp の記事に書かれておらず確かめていない。本文では制約の数を書かず、落とし穴で「単純グラフと保証されていなければ重複を除く」と条件付きで書いた
- Library Checker の制約の数（N_MAX・M_MAX）は task.md ではテンプレートの変数で、値を確かめていない。本文には数を書いていない
- 「隣の値の最大」を値の大きい順の列から探す応用（count-by-layer の節の末尾）は、ABC の問題で裏付けていない一般的な手法の説明である。検証役に正しさ（見送る回数が v 自身と G での隣の数以下）を見てほしい

## 検証の指摘への対応（直し）

- 指摘 1（直すべき）：Library Checker の題名を本文と参考の 2 か所とも「Connected Components of Complement Graph」に直した
- 指摘 2：#complexity の「残す回数」を「先に取り出された端点を取り出したときの 1 回だけ、全体で M 回以下」に直した。確認問題 2 は次数の上限の問いとして残し、答えに「辺ごとに見れば 1 回なので実際は M 以下」を足した
- 指摘 3：擬似コードの「u を取り出す」の次に「keep = 空」を足した
- 指摘 4：一部だけ採った。110 行目を「残す頂点はイテレータを進めるだけなので細かく数えれば O(N log N + M)」「set<pair<int, int>> で引く書き方は全体で O((N + M) log M)」に直した。表・front matter の complexity・要点の O((N + M) log N) は、上限として誤りではなく 3 か所の一致を保つため変えていない
- 指摘 5：図の凡例を font-size 13→15、残した辺のラベルを 12→14 にし、ラベルを箱と重ならないよう 4px 下げた。render_svg.py の 360px・720px で重なり・はみ出しがないことを確かめた

## 台帳への提案（検証から）

- abc319_g の `checked` に 2026-10-21 を入れる（検証役が tools/ap.py で題名・diff、kmjp の記事で問題の内容・mod・−1 の出力を確かめた。制約の数は未確認）
