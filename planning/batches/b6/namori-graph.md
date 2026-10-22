# namori-graph の問題の補充（b6・工程9）

- ページ：docs/graph/namori-graph.md（レベル 水）。今の練習は abc292_d（diff 579）の 1 問、例題は abc266_f（diff 1525）
- 探したところ：(1) b1 の報告 planning/batches/b1/namori-graph.md の「問題の補充の候補」と b1/summary/candidates.md の §namori-graph に abc378_f・abc235_e・jsc2019_qual_e が挙がっていた（b3・b5 の candidates.md と ほかのバッチの namori-graph.md には候補なし）。(2) data/problems.yaml で pages に namori-graph を持つのは abc266_f・abc292_d だけで、どちらも本文にある。(3) drken1215.hatenablog.com のカテゴリ「なもりグラフ」（11 件）と `ap.py search`（Namori・Cycle・Unicyclic・One Edge など）で探した。カテゴリの残りは有向の Functional graph の問題（abc357_e・abc256_e・abc167_d・agc004_d など）や AOJ・Codeforces の問題で、このページではなく functional-graph の範囲か、対象外である
- 問題の実在・題名・difficulty は `python3 tools/ap.py show` で確かめた（2026-10-22）
- 使ったドメインは drken1215.hatenablog.com・kazun-kyopro.hatenablog.com で、どちらも付録 B にある。新しいドメインはない
- WebSearch の回数の上限に達したので、第三者の解説を広く検索することはできなかった。abc378_f・jsc2019_qual_e の 2 つ目の裏付け（kmjp 氏の記事）は URL を見つけられなかった
- 練習の候補 1 問を足すと練習は合わせて 2 問になる（目標の下限）。ほかに力試しの候補が 1 問

## 候補

### abc378_f（台帳にあり。namori-graph は pages にない）

- 問題ID：abc378_f
- 題名：F. Add One Edge 2
- difficulty：1436（水）
- 役割：practice
- 要約：N 頂点の木に辺を 1 本足して単純グラフを作るとき、できる閉路の上の頂点の次数がすべて 3 になる足し方の数を求める。
- 方針の要点：木に辺を 1 本足すと閉路がちょうど 1 つでき（one-cycle の節）、条件を満たす閉路は次数 2 の端 2 つと次数 3 の頂点だけの道からなるので、次数 3 の頂点の連結成分ごとに接する次数 2 の頂点の数 K を数えて K(K−1)/2 を足す（O(N)）。
- 裏付け：
    - https://drken1215.hatenablog.com/entry/2024/11/04/002341 （問いと、次数 3 の成分ごとに隣の次数 2 の頂点から 2 つ選ぶ数え方を確かめた。drken 氏はこの記事をカテゴリ「なもりグラフ」に入れている）
- 台帳への追加の提案：pages に {id: namori-graph, role: practice}（今は tree-basics:practice のみ）
- 本文に足すときのメモ：閉路を求める（葉を削る）手順は使わず、「木 ＋ 1 辺 ＝ 閉路 1 つ」の形を逆向きに使う練習である。練習の方針には「足す辺の両端は次数 2、間の閉路の頂点は次数 3 であるべき」と書くと、one-cycle の節につながる

### jsc2019_qual_e（新規。台帳になし）

- 問題ID：jsc2019_qual_e
- 題名：E. Card Collector
- difficulty：2691（発展）
- 役割：challenge（帯から大きく離れるので力試し。それでも重いので、載せるかはメインの判断に任せる）
- 要約：H × W の盤に重み付きのカードが N 枚あり、各行から高々 1 枚、続いて各列から高々 1 枚取るとき、取ったカードの重みの和の最大を求める。
- 方針の要点：行と列を頂点、カードを辺とする二部グラフで、取れる辺の集合は各連結成分の辺数が頂点数以下（木かなもりグラフ）であることと同値なので、重い順に Kruskal 風に辺を見て、成分ごとに「なもりか」のフラグを持つ Union-Find で採否を決める（O(N log N)）。
- 裏付け：
    - https://drken1215.hatenablog.com/entry/2019/09/27/185400 （問い、各成分が木かなもりになる条件、フラグ付き Union-Find の貪欲を確かめた）
- 台帳への追加の提案：新規に登録し、pages に {id: namori-graph, role: challenge}。union-find（成分ごとの情報を持つ）や minimum-spanning-tree の貪欲の発展としても使える可能性があるが、そちらは確かめていない
- 本文に足すときのメモ：本文の「成分ごとに頂点数と辺数が等しいなら各成分がなもり」（one-cycle の節の終わり、abc292_d と同じ数え方）を、辺 ≤ 頂点の条件に広げた形である

## 除いたもの

- abc266_f（例題）・abc292_d（練習）：本文に既にある
- abc235_e（E. MST + 1、diff 1304）：最小全域木に辺を 1 本足すと閉路が 1 つでき、その閉路で最も重い辺を除くという理由付けにだけなもりの形を使う（https://kazun-kyopro.hatenablog.com/entry/ABC/235/E で確かめた）。解き方は Kruskal 風のオフライン処理で、このページの手法（葉を削る・閉路の頂点ごとの木に分ける・単純パスの一意性）を使わない。台帳では minimum-spanning-tree の例題なので、こちらに足すと役割が重なる。練習が足りないと判断するなら 3 問目の候補にはなる
- arc079_d（F. Namori Grundy、diff 2636）・agc004_f（F. Namori、diff 3986）・agc070_b（B. Odd Namori、diff 3217）：題名になもりを含むが帯（水）から離れすぎ、解説も開いていない。arc079_d は各頂点の入次数が 1 の有向グラフで functional-graph に近い
- abc401_f（F. Add One Edge 3、diff 1666）・abc309_d（D. Add One Edge、diff 621）：題名は似るが、2 つの木を結ぶ辺の選び方（直径）や BFS の問題で、閉路を扱わない（台帳・解説では確かめていない。題名と一般に知られた内容からの判断なので、確度は低い）
- abc357_e・abc256_e・abc167_d・agc004_d：drken 氏のカテゴリ「なもりグラフ」にあるが、有向の Functional graph の問題で functional-graph の範囲
- KeioPC2025_j・nupc2024_j・nupc2024_n（題名に Namori）：difficulty がなく、解説を開いていない
