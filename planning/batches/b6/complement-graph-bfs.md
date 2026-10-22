# complement-graph-bfs の問題の補充（工程9・b6）

- ページ：docs/graph/complement-graph-bfs.md（レベル 黄）
- 今の問題：例題 abc319_g（diff 2185）だけ。練習・力試しは 0 問。本文の連結成分の段落で Library Checker の connected_components_of_complement_graph を練習として示している（台帳の外）
- 結論：**練習・力試しに足せる AtCoder の問題は見つからなかった**。確かめて足せる候補は 0 問である。無理に足さない

## 探した範囲と結果

1. これまでの候補の一覧と報告
   - planning/batches/b1/summary/candidates.md・b5/summary/candidates.md：このページの候補はない（b5 の abc187_f は補グラフの彩色数で、chromatic-number の候補。BFS は使わない）
   - planning/batches/b3/summary/candidates.md と planning/batches/b3/complement-graph-bfs.md：「ABC319 G 以外は見つからない。練習は Library Checker で補う」とある。問題の補充の候補はない
2. data/problems.yaml：pages に complement-graph-bfs を持つのは abc319_g（example）だけで、本文にもある。本文にない問題はない
3. 第三者の資料と AtCoder Problems のデータ
   - Web 検索（日本語・英語で 8 回。「補グラフ BFS 未訪問」「complement graph BFS AtCoder」「完全グラフから 辺を取り除いた」など）では、ABC319 G 以外に、このページの手法を使う AtCoder の問題の解説は見つからなかった。途中でセッションの Web 検索の上限に達し、中国語（「补图 BFS」）での検索はできていない
   - sotanishy の cp-library の「BFS on a Complement Graph」（https://sotanishy.github.io/cp-library-cpp/graph/complement_bfs.hpp.html ）が挙げる問題も abc319_g だけだった（github.io。付録 B の github.io の各サイトとは別の書き手なので、資料にするなら check_noai が要る。今回は候補探しにだけ使った）
   - nor の解説（https://nor-blog.pages.dev/posts/2021-08-12-complement-graph-traversal/ 。check_noai は未実施）が挙げる問題は Codeforces 920E だけで、noai 指定のため使えない
   - `python3 tools/ap.py search Complement` で題名に Complement を含む問題は arc193_a（A. Complement Interval Graph、diff 1234）だけだった。区間が交わらない組を結ぶグラフの最短路を問う題名だが、解説を開いて方針を確かめられておらず（kmjp の 2025 年 2 月の一覧に記事がない）、レベルの帯（黄）からも遠いので候補にしていない
   - 題名から見つけた arc099_c（E. Independence、diff 2160）は補グラフを扱うが、N ≤ 700 で補グラフを隣接行列でそのまま作る問題として知られており、このページの手法（未訪問頂点の集合）は要らないと考えて候補にしていない（解説は開いていない）

## メインへの提案

- 練習は今のまま、本文の Library Checker の connected_components_of_complement_graph で補う形がよい。§15-5 の「ほかのジャッジ」の小見出しで、これを練習の節にふつうのリンクとして置くことを提案する（AtCoder の練習問題としては数えない）
- 使い分けの「値の条件で決まるグラフ（行・列の set）」の型の問題は ordered-set#rows-and-columns の側の練習で、このページの練習には数えない方がよい
- Web 検索の上限が戻ったら、中国語の題解（luogu・cnblogs。どちらも付録 B にある）で「补图 BFS AtCoder」を探す余地は残っている
