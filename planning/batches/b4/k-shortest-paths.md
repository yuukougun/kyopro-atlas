# k-shortest-paths の報告（b4）

- 書いたファイル：docs/graph/k-shortest-paths.md、snippets/k-shortest-paths/k-times.{cpp,yaml}
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-22）。sections の yen-eppstein の title を「単純パス（Yen）とウォークの高速な列挙（Eppstein）」に変えた（§14-22 で「歩道」は使わないため。anchor は変えていない）
- 検査の結果：check_pages エラー 0・警告 0、fix_problems --check 直すべき行 0、check_snippets 期待と違う 0、textlint エラー 0（警告 9：要点の計算量の行の長さ、数式を含む文の長さ・読点、参考の記事題名の「！」と長さ。どれも数式か引用した題名による）
- 図：作っていない。catalog の visual は null。小さい例（2 頂点の閉路）は文章で 1 回動かした
- コード片：k-times.cpp は各頂点を K 回まで取り出すダイクストラ。main で乱択の小さいグラフ 200 個を、長さの上限つきのウォークの全列挙と比べる assert を入れた。入出力は Library Checker の k_shortest_walk と同じ形
- 手元の確かめ（scratchpad。本文には取り込まない）：
  - Eppstein の方法を自分で書き、各頂点を K 回まで取り出す版と乱択のグラフ 20000 個で一致を確かめた（重み 0 を含む）
  - 木の辺を等式 d(u) = w + d(v) だけで選ぶ（確定順を見ない）と食い違う例が出た。本文の「木の辺はダイクストラ法で記録した親を使う」の根拠
  - 「異なる長さだけを数える」版（直前と同じ値の取り出しを捨てる）を全列挙と 3000 個比べて一致
- 使った出典：
  - https://qiita.com/hotman78/items/42534a01c4bd05ed5e1e（Eppstein の方法の流れと計算量）
  - https://qiita.com/nariaki3551/items/821dc6ffdc552d3d5f22（Yen の方法。題名の確認と流れ）
  - https://ei1333.github.io/library/graph/shortest-path/k-shortest-walk.hpp・k-shortest-path.hpp（関数の形・計算量・Yen の「verify が甘い」の注記）
  - https://en.wikipedia.org/wiki/Yen%27s_algorithm・https://en.wikipedia.org/wiki/K_shortest_path_routing（計算量・原論文の年）
  - https://github.com/yosupo06/library-checker-problems/tree/master/graph/k_shortest_walk（task.md・info.toml で問いと制約 N, M, K ≤ 3×10^5、0 ≤ c ≤ 10^7、制限 5 秒）
  - 新しいドメイン：なし（qiita.com・ei1333.github.io・github.com・en.wikipedia.org は付録 B）。yukicoder.me を check_noai.py で確かめた（X-Robots-Tag・meta とも指定なし）が、規約までは確かめておらず、問題文も読んでいないので本文には使っていない

## 台帳への提案

- なし（このページに載せる問題はない。台帳にも k-shortest-paths の問題はない）

## 用語集への提案

- なし（ウォーク・単純パスは path-walk、最短路木は shortest-path-tree、ポテンシャルは potential にリンクした）
- 候補として検討：「寄り道の辺（sidetrack）」は Eppstein の方法でしか使わないので本文で定義するにとどめた

## 手引き・front matter・catalog への提案

- summary と signs に「歩道」が残っている（§14-22・付録 A ではウォーク）。案：
  - summary：始点から終点への経路のうち、短い方から K 番目の長さを求める。ウォークなら各頂点を K 回まで取り出すダイクストラで求まり、単純パスは Yen、ウォークの高速な列挙は Eppstein の方法を使う。
  - signs：{type: phrase, text: K 番目に短い経路・ウォークの長さ}
  - 要点の囲みは本文でウォークに直した（意味は summary と同じ）
- aliases に「2 番目に短い経路」「第 K 最短路」を足す案（2 番目の最短路を探す読者がこのページに来るように）
- related に persistent-data-structures を足す案（Eppstein の方法の永続ヒープで #path-copying にリンクした）
- 他ページのリンクの張り替え（このページが draft になったので §14-23 どおり節へ）：graph/dijkstra.md:220 の「K 番目の最短路」→ `../graph/k-shortest-paths.md#k-times`
- 手引きへ：ACL に対応がない発展の概要の「ライブラリでの使い方」は、公開ライブラリ（ei1333）の関数名と返り値を文章で書くにとどめた。parallel-binary-search の報告と同じ論点で、扱いをそろえてほしい

## 問題の補充の候補（問題ID・何を問うか・裏付けの URL）

- AtCoder では見つからなかった。ap.py で Shortest・K-th・Kth・Second・最短 を題名検索したが、K 番目のウォーク・単純パスを問う問題は題名からは見つからず、調査（03-graph §4.B・§6.6）とも合う
- 台帳の外の候補（AtCoder ではないので問題の囲みには載せられない）：yukicoder No.1069「電柱 / Pole (Hard)」。ei1333 の Yen の実装の verify に使われている（https://ei1333.github.io/library/graph/shortest-path/k-shortest-path.hpp）。問題文は読んでおらず、規約も確かめていないので、載せるならメインで判断してほしい

## 未解決の点

- Eppstein の計算量は資料（hotman78・ei1333）の O((V + E) log V + K log K) を、多重辺も含めて確実に成り立つ上界として O((N + M) log(N + M) + K log K) と書いた。永続ヒープの記憶を O(M log M) と書いたのも上界で、厳密な値は確かめていない
- 「KM が 10^7 程度まで」「Yen は N, M が数千、K が数十まで」の目安は計算量からの見積もりで、実測していない
- 原論文（Yen 1971・Eppstein 1998）は開いておらず、Wikipedia の記述で年と計算量を確かめた

## 検証の指摘への対応

- 指摘 1（直すべき・Yen の目安）：本文と表を「$KN(N + M)$ が $10^8$ 程度まで（$N, M$ が数百、$K$ が数十）、パスが短ければもっと」に直した
- 指摘 2（summary・signs の「歩道」）：執筆者は front matter の summary・signs を直さない取り決めなので、ページでは直していない。上の「手引き・front matter・catalog への提案」の案どおり、メインで「ウォーク」に直してほしい
- 指摘 3（確認問題 1 問目）：「異なる長さだけを数える版で、同じ値の組から伸ばさなくてよい理由」を問う問いに替えた
- 指摘 4（確認問題 2 問目の $w$）：$w$ を「最短路の上の重み $w$ の辺」と定義し、辺 1 本のグラフで $3w$ が 2 番目に出る例を添えた
- 指摘 5（多重辺と木の辺）：要点の 1 つ目に、辺の番号で 1 本に決める（最初の 1 本だけ飛ばす）ことを足した
