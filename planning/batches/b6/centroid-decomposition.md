# centroid-decomposition の問題の補充（b6・工程9）

- ページ：docs/tree/centroid-decomposition.md（レベル 黄）。今の練習は abc359_g（diff 2099）の 1 問、例題は abc291_h、力試しは keyence2019_e
- 探したところ：(1) b3 の報告 planning/batches/b3/centroid-decomposition.md の「問題の補充の候補」に yahoo_procon2018_final_c・abc267_f・abc202_e・abc014_4（b3 の summary/candidates.md にも同じ記載。b1 の candidates.md には centroid-decomposition の候補なし、b5 の candidates.md は keyence2019_e の別ページへの転用だけ）。(2) data/problems.yaml で pages に centroid-decomposition を持つが本文にない問題は yahoo_procon2018_final_c の 1 問（role: practice）。(3) 第三者の解説で nikkei2019_final_g・ddcc_2016_qual_d を新たに見つけた（navel_tos の記事と、はまやんの「重心分解問題まとめ」に挙がっていたもの）
- 問題の実在・題名・difficulty は `python3 tools/ap.py show` / `contest` で確かめた（2026-10-22）
- 使った資料のドメイン（qiita.com・blog.hamayanhamayan.com・kmjp.hatenablog.jp）はどれも付録 B にあるので、check_noai は流していない
- 調べている途中で、このセッションの WebSearch の上限に達した。そのため (3) は既知の記事（navel_tos・はまやんのまとめ・kmjp の月別アーカイブ）をたどる範囲にとどまる。ABC の最近の回で重心分解を使う問題は見つけられていない
- 候補の practice 2 問を足すと練習は合わせて 3 問になる。力試しの候補が 2 問ある

## 候補

### yahoo_procon2018_final_c（台帳にあり、本文になし）

- 問題ID：yahoo_procon2018_final_c
- 題名：C. 木の問題
- difficulty：なし（AtCoder Problems に値なし）
- 役割：practice
- 要約：木の頂点 V_i から距離がちょうど K_i の頂点の個数を、多数のクエリについて答える。
- 方針の要点：重心分解し、各クエリで重心木の祖先 c ごとに「c からの距離が K_i − d(V_i, c) の頂点数」を足し、V_i と同じ子の成分の分を引く（centroid-tree-queries の節の形そのもの）。全体は O((N+Q) log N) である。
- 裏付け：
    - https://qiita.com/navel_tos/items/d1a2fd2b63e73380eadb （「みんなのプロコン2018 決勝 C 木の問題」として、重心を通るパスへの帰着と、同じ子の部分木の分を引く処理、O((N+Q) log N) を説明している。記事に N・Q の制約は書かれていない）
    - https://blog.hamayanhamayan.com/entry/2017/12/19/152143 （重心分解の問題のまとめで、この問題を「木全体についての数え上げ」の分類に挙げている。解法の説明はない）
- 台帳の直しの提案：checked が null なので '2026-10-22' にし、evidence に上のはまやんの URL を足す

### abc267_f（台帳にあり、このページの役割はなし）

- 問題ID：abc267_f
- 題名：F. Exactly K Steps
- difficulty：1939（青）
- 役割：practice（帯の青の上端で黄に近い。ただし想定解は直径の端点と祖先のたどりで、重心分解は別解である。本文では「直径でも解ける」と添えるのがよい。別解の練習を嫌うなら載せない）
- 要約：木の頂点 U_i から距離がちょうど K_i の頂点を 1 つ答える（なければ −1）クエリに、Q 回答える。
- 方針の要点：yahoo_procon2018_final_c と同じく重心木の祖先 c をたどり、各 c について「c からの距離が K_i − d(U_i, c) の頂点」を、U_i と別の子の成分から 1 つ取れるよう、距離ごとに別の子の成分に属する具体的な頂点を高々 2 個持っておく。
- 裏付け：
    - https://qiita.com/navel_tos/items/d1a2fd2b63e73380eadb （ABC267F を「木の問題と同じ方針で、候補の頂点を高々 2 個持つ」と説明。Python では定数倍の工夫が要るとも書いている）
    - https://kazun-kyopro.hatenablog.com/entry/ABC/267/F （台帳の evidence。想定の直径を使う解き方の確認用）
- 台帳への追加の提案：pages に {id: centroid-decomposition, role: practice}

### nikkei2019_final_g（新規。台帳になし）

- 問題ID：nikkei2019_final_g
- 題名：G. Greatest Journey
- difficulty：なし（AtCoder Problems に値なし。全国統一プログラミング王決定戦 本戦の G）
- 役割：challenge（重心分解に Convex Hull Trick 型の直線の最大値を組み合わせるので、黄の帯の練習としては重い）
- 要約：重み付きの木で、頂点 V_i から始まる長さ L_i のウォークについて通った辺の重みの和の最大値を、多数のクエリについて答える。
- 方針の要点：最適なウォークは「V_i から別の頂点へ向かう最短のパス」と「最後にある辺の往復を繰り返す部分」に分けられるので、パスを重心を通るものとして重心ごとに集計し、残りの長さに比例する往復の分を直線の最大値の問題としてクエリを x の順に並べて処理し、O((N+Q) log N) 程度にする。
- 裏付け：
    - https://qiita.com/navel_tos/items/d1a2fd2b63e73380eadb （全国統一プログラミング王決定戦2019 本戦 G として、最短パスと辺の往復への分解、重心を通るパスへの帰着、クエリを並べて直線を足す処理、O((n+q) log n) を説明している）
    - https://blog.hamayanhamayan.com/entry/2017/12/19/152143 （まとめの未整理のメモにこの問題のリンクがある。説明はない）
- 確かめきれなかった点：N・Q・L_i の制約と、往復する辺の選び方の細部は記事から読み取れた範囲だけである。本文に入れるなら、方針は記事でもう一度確かめる
- 台帳への追加の提案：新しい問題として、pages に {id: centroid-decomposition, role: challenge}

### ddcc_2016_qual_d（新規。台帳になし）

- 問題ID：ddcc_2016_qual_d
- 題名：D. 道路網
- difficulty：なし（AtCoder Problems に値なし）
- 役割：challenge（重心を通る組の数え方は count-through の節の形だが、木の辺が X より長い場合の例外の処理が重い）
- 要約：N 頂点の完全グラフで、N−1 本の辺は木をなして長さが与えられ、残りの辺の長さがすべて X のとき、全頂点対の最短距離の総和を求める。
- 方針の要点：木の上で別の子の成分にある 2 頂点の距離は min(X, D(v)+D(w)) とみて、重心からの距離ごとの個数と和を 2 本の BIT で持って重心分解で総和を数え、そのうえで長さが X を超える木の辺を経由する組を、隣の頂点を経由して X や 2X・3X で行く候補と比べて直す。
- 裏付け：
    - https://kmjp.hatenablog.jp/entry/2016/11/22/0930 （問題の設定、重心を根にして min(X, D(v)+D(w)) を 2 本の BIT で数える重心分解、X より長い辺がある組の補正を説明している。計算量は記事に明記なし。O(N log^2 N) と見積もれる）
    - https://blog.hamayanhamayan.com/entry/2017/12/19/152143 （まとめの未整理のメモにこの問題のリンクがある。説明はない）
- 確かめきれなかった点：例外の処理の細部（どの候補を比べるか）は kmjp の記事の要約からしか読んでいない。本文に入れるなら記事でもう一度確かめる
- 台帳への追加の提案：新しい問題として、pages に {id: centroid-decomposition, role: challenge}

## 除いたもの

- abc291_h（例題）・abc359_g（練習）・keyence2019_e（力試し）：本文に既にある
- abc202_e（Count Descendants、diff 1638）：navel_tos の記事は「強化版」を重心分解で解いているが、元の問題はオイラーツアーと二分探索で解くもので、台帳でも euler-tour の例題・merge-sort-tree の練習。重心分解の練習としては不自然なので除いた（b3 の判断と同じ）
- abc014_4（閉路、diff 1856）：重心木で 2 頂点の距離を答えられるが、LCA の方が速く素直（navel_tos の記事も重心分解は避けるべきと書いている）。除いた
- IOI 2011 Race（はまやんのまとめにあるリンク ioi2011_1_2）：`tools/ap.py` で見つからない（AtCoder Problems にコンテストがない）ので除いた
- はまやんのまとめのほかの問題（Codeforces・CodeChef・HackerRank・CSA Academy）：AtCoder ではない。Codeforces は noai 指定もある

## 本文に足すときのメモ

- 練習の並び：yahoo_procon2018_final_c と abc267_f はどちらも centroid-tree-queries の節の練習で、前者が「個数を数えて同じ側を引く」、後者が「数えずに具体的な頂点を持つ」の違いがある。abc267_f（1939）→ abc359_g（2099）の順に、difficulty のない yahoo_procon2018_final_c は内容の易しさから先頭に置くのが自然
- 力試しの並び：ddcc_2016_qual_d は count-through の発展、nikkei2019_final_g は重心分解とクエリの並べ替え・直線の最大値の組み合わせ。どちらも difficulty がないので、keyence2019_e（2623）の前後は内容で決める
