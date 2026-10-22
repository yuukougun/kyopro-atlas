# bellman-ford の問題の補充（b6・工程9）

- ページ：docs/graph/bellman-ford.md（レベル 青）。今の練習は abc404_g（diff 1894）の 1 問、例題は abc137_e・abc061_d
- 探したところ：
    - (1) b2 の報告 planning/batches/b2/bellman-ford.md の「問題の補充の候補」に abc237_e（b3 summary/candidates.md にも同じ記載）。b1・b5 の candidates.md には bellman-ford の補充の候補なし
    - (2) data/problems.yaml で pages に bellman-ford を持つ問題は abc061_d・abc137_e・abc404_g の 3 問で、どれも本文にある（本文にない問題はなし）
    - (3) 第三者の解説：drken のはてなブログのカテゴリ「Bellman-Ford法」「負閉路」「最短路問題」の記事一覧と Web 検索で探した。カテゴリ「負閉路」から abc280_f を見つけた（台帳では weighted-union-find の practice）。負辺の最短路を O(NM) で解くこと自体が本体の新しい ABC の問題は見つからなかった（catalog の problems_note・b2 の報告と同じ見立て）
- 問題の実在・題名・difficulty は `python3 tools/ap.py show` で確かめた（2026-10-22）
- 候補 2 問を足すと練習は合わせて 3 問になる。ただし 2 問とも「ベルマンフォード法を使わずに済む」ことを見抜く問題で、vs-potential の節（見分け）の練習である。ベルマンフォード法そのものを書く練習は abc404_g の 1 問のままになる
- 途中で Web 検索の上限に達したので、検索はこれ以上できなかった（AtCoder Tags の Bellman-Ford の一覧は curl では中身が空で読めなかった）

## 候補

### abc237_e（台帳にあり、pages は dijkstra だけ）

- 問題ID：abc237_e
- 題名：E. Skiing
- difficulty：1208（水）
- 役割：practice（帯の青より下だが、vs-potential の節の表の「重みが高さの差で決まる」の行そのものなので、見分けの練習に置く）
- 要約：標高の差で楽しさが増えたり減ったりする無向グラフの移動で、広場 1 から出発したときの楽しさの最大値を求める。
- 方針の要点：符号を反転すると負の辺が出るが N, M が大きくベルマンフォード法では間に合わないので、標高をポテンシャルにして辺の重みを非負に付け替え、ダイクストラ法で求めてから標高の差で戻す。
- 裏付け：
    - https://kyo-pro.hatenablog.com/entry/ABC237E （符号の反転、p_X = H_X のポテンシャルで全辺が非負になること、ダイクストラ法の後に補正すること。台帳の evidence と同じ）
    - https://zenn.dev/akiku/articles/akiku-abc237 （本番でベルマンフォード法を使うと TLE だったこと、下りだけ標高差をコストにして非負にしダイクストラ法を使うこと）
- 台帳への追加の提案：abc237_e の pages に {id: bellman-ford, role: practice} を足す
- 未確認：N, M の上限の数値は 2 つの解説に書かれておらず、確かめていない（本文の方針に数値を書くなら別の出典が要る）

### abc280_f（台帳にあり、pages は weighted-union-find だけ）

- 問題ID：abc280_f
- 題名：F. Pay or Receive
- difficulty：1819（青）
- 役割：practice（帯の内。ただし解き方の本体は重み付き Union-Find なので、載せるかはメインが決める。載せないなら relevant-cycles・vs-potential からのリンク先にとどめてもよい）
- 要約：辺 A→B を長さ C で通ると逆向きは長さ −C になるグラフで、クエリごとに 2 点間の最長路の長さを答え、届かなければ nan、いくらでも大きくできるなら inf と出す。
- 方針の要点：一般のグラフとしてクエリごとにベルマンフォード法を回すと間に合わないので、逆向きで符号が反転する構造から「正の閉路がない ⇔ 各頂点に x_B − x_A = C を満たす値（ポテンシャル）が置ける」ことを使い、重み付き Union-Find で矛盾を見つけた連結成分を inf にする。
- 裏付け：
    - https://drken1215.hatenablog.com/entry/2022/12/07/231851 （問題の設定、N, M, Q ≤ 10^5、クエリごとのベルマンフォード法では間に合わないこと、ポテンシャルが置けることと閉路の条件、重み付き Union-Find で矛盾した成分に印を付ける方針。台帳の evidence と同じ）
- 台帳への追加の提案：採るなら abc280_f の pages に {id: bellman-ford, role: practice} を足す

## 除いたもの

- abc061_d・abc137_e（例題）・abc404_g（練習）：本文に既にある
- abc216_g（差分制約）：b2 の報告のとおり difference-constraints の持ち物で、負辺がなくダイクストラ法で解くので、このページには合わない
- arc090_b（People on a Line、ABC087 D と同じ問題。台帳は arc090_b）：drken のカテゴリ「最短路問題」の一覧にあったが、位置の差の条件の矛盾を見る問題（台帳ではこのページの外の題材）で、負閉路で inf になる判定がないので候補にしない。解説は開いていない
