# graph-basics の問題の補充（工程9・b6）

- 対象のページ：docs/graph/graph-basics.md（レベル 基礎）。今の練習は abc284_c の 1 問
- 結果：確かめた候補は 2 問。足せば練習は合わせて 3 問になり、目標（2〜4 問）に届く
- 2 問とも、b1 の報告（planning/batches/b1/graph-basics.md の「問題の補充の候補」）と b1/summary/candidates.md に挙がっていたものである。data/problems.yaml でも graph-basics の practice として登録済みで、本文にはまだない
- 並びの案：abc343_b → abc276_b → abc284_c（隣接行列の読み取り → 辺リストから隣接リストを作る → 隣接リストを使った探索）

## 候補

### abc343_b

- 問題ID：abc343_b
- 題名：B. Adjacency Matrix
- difficulty：53（ap.py で確認。灰／基礎）
- 役割：practice
- 要約：N×N の 0/1 の隣接行列が与えられ、各頂点について、辺でつながる頂点の番号を昇順に出力する問題である。
- 方針の要点：行 i を左から見て 1 のある列の番号（1-indexed に直す）を拾えば、隣接行列から隣接リストへの変換になり、全体で O(N^2) である。
- 裏付け：https://www.cnblogs.com/Lanly/p/18058486 （開いて、問いと解法を確かめた）

### abc276_b

- 問題ID：abc276_b
- 題名：B. Adjacency List
- difficulty：143（ap.py で確認。灰／基礎）
- 役割：practice
- 要約：N 都市と M 本の双方向の道路が組で与えられ、各都市について、つながる都市の個数と番号を昇順に出力する問題である。
- 方針の要点：辺 (A, B) ごとに g[A] に B、g[B] に A を入れて隣接リストを両方向に作り、各 g[i] をソートして長さと要素を出力すれば O(N + M log M) である。
- 裏付け：https://qiita.com/sano192/items/298c551f0e63c9c93260 （開いて、解法を確かめた。記事は問題文を全部は書き直していないが、説明とコードから問いが読み取れる）

## 探したが足さなかったもの

- abc232_c（C. Graph Isomorphism、diff 685）：N ≤ 8 なので隣接行列で辺の有無を O(1) で引く例になる。ただし small-graph-brute-force の例題と bit-full-search の練習に既にあり、主な手法は順列の全探索なので、このページには足さない
- abc371_c（C. Make Isomorphic、diff 849）：同じ理由で small-graph-brute-force に任せる
- 水〜青の帯（力試し）の候補：このページの手法（表現の選び方・用語）だけが鍵になる問題は見つからなかった。無理に足さない

## 未解決の点

- 2 つ目の裏付けは取れていない。ikatakos.com の abc276・abc343 の記録には B の節がなかった（https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2022/1105_abc276 、https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2024/0302_abc343 ）。Web 検索はセッションの上限に達して使えなかった。どちらも易しい B 問題で、1 件の解説で問いと解法は確かめられている
- 新しく noai を確かめたドメインはない（www.cnblogs.com・qiita.com・ikatakos.com は付録 B にある）
