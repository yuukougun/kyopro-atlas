# counting-labeled-graphs（連結なグラフの数え上げ・黄）の問題の補充

- 現状：例題 1（abc281_g）・練習 1（abc180_f）・力試し 1（abc213_g）
- 目標：練習 2〜4 問

## 確かめた候補

| 問題 ID | 題名 | difficulty | 役割 | 要約 | 方針の要点 | 裏付けの URL |
| --- | --- | --- | --- | --- | --- | --- |
| abc321_g | G. Electric Circuit | 2439（ap.py） | practice（anchor: subset-dp。黄の帯の上端を 39 だけ超える） | N ≤ 17 個の部品の赤い端子と青い端子（どちらも M 個）を一様にランダムに 1 対 1 でつなぐとき、できるグラフの連結成分の個数の期待値を求める問題である。 | 期待値の線形性で「頂点集合 S がちょうど 1 つの成分になる」確率の和にし、S の中だけでつなぐ方法の数 f(S)（赤と青の数が等しければその階乗、違えば 0）から、最小の頂点を含む真部分集合 T について c(T)·f(S∖T) を引いて連結なものの数 c(S) を O(3^N) で求める。 | https://drken1215.hatenablog.com/entry/2023/09/26/105540 ・ https://kmjp.hatenablog.jp/entry/2023/09/23/0900 |
| abc253_h | Ex. We Love Forest | 2758（ap.py） | challenge（anchor: subset-dp・by-size の森の応用の型） | N 頂点の辺のない状態から、M 本の辺の候補から一様に 1 本選んで足す操作を K 回したとき、グラフが森になる確率を K = 1, …, N−1 のそれぞれについて求める問題である。 | 頂点集合ごとの全域木の数を行列木定理で求め、それを「連結なものの数」の代わりにして、最小の頂点を含む成分から決める部分集合の DP で成分の数（＝辺の数）ごとの森の数を組み立てる。 | https://kmjp.hatenablog.jp/entry/2022/05/28/1030 |
| abc389_g | G. Odd Even Graph | 2762（ap.py） | challenge（anchor: bfs-layers） | 素数 P と N について、辺の数 M ごとに、頂点 1 からの距離が偶数の頂点と奇数の頂点の数が等しい N 頂点の連結な単純無向グラフの数を P で割った余りで求める問題である。 | 距離の層ごとに頂点を配る DP に、偶奇の差と辺の数を状態として足し、前の層と新しい層の間の辺の張り方を辺の数ごとに前計算しておく。 | https://kmjp.hatenablog.jp/entry/2025/01/19/1000 |
| abc236_h | Ex. Distinct Multiples | 2898（ap.py） | challenge（anchor: by-size の逆向きの式。帯から遠い） | 長さ N（N ≤ 16）の数列 D について、A_i が M 以下の D_i の倍数で、どの 2 つも異なる数列 A の個数を求める問題である。 | 「等しい」組の集合で包除し、その組をグラフの辺とみなすと、成分ごとの重み（共通の値の選び方の数 × 辺 1 本ごとに −1 を掛けた連結なグラフの和 (−1)^{k−1}(k−1)!）を、最小の頂点を含む成分から決める部分集合の DP で掛け合わせる。 | https://kmjp.hatenablog.jp/entry/2022/01/24/1100 |

- abc321_g は data/problems.yaml に既にあり（pages は `{id: subset-enumeration-dp, role: challenge}` だけ、evidence は drken の記事）、counting-labeled-graphs を pages に足して role: practice にするよう提案する。本文の #subset-dp の応用の型「全体が辺の部分集合でないとき」とほぼ同じ形で、f(S) が階乗になる場合に当たる。difficulty は黄の帯を 39 超えるが、ページの式をそのまま使えるので練習に置ける。帯を厳密に守るなら力試しにする
- abc253_h・abc389_g・abc236_h は台帳になく、追加の提案になる。どれも発展の帯（2400〜）なので力試しの候補である。力試しを増やしすぎないなら、型が本文の節と最も直接に合う abc389_g（#bfs-layers）を優先し、abc253_h は森の応用の型の裏付けとして、abc236_h は採らなくてもよい
- abc253_h の N の上限は kmjp の記事に明記がないので、要約に書いていない（計算量は記事で O(N·2^N + 3^N)）。台帳に入れるときは別の解説で制約を確かめる
- abc389_g は b3 の報告（b3/counting-labeled-graphs.md）の候補と同じで、kmjp の記事で問いと方針を確かめ直した

## 探したが見つからなかったもの

- (1) b1・b3・b5 の candidates.md と b3/counting-labeled-graphs.md：abc389_g（上）・abc253_h（上）・abc327_g。abc281_g は例題で既出
- abc327_g（G. Many Good Tuple Problems、2968）：連結な二部グラフを全体から引く型に合うが、kmjp・drken のブログに記事が見つからず（drken は ABC327 の F まで）、Web 検索でも第三者の解説を見つけられなかった。atcoder.jp の公式解説は noai のため開いていないので候補に入れない
- (2) data/problems.yaml で counting-labeled-graphs を pages に持つのは abc180_f・abc213_g・abc281_g の 3 問で、どれも本文にある
- (3) 第三者の解説：Web 検索（「全体から非連結を引く」「頂点 1 を含む連結成分」「包除DP」「Connectivity 2 類題」など）と ap.py の題名検索（Connect・Graph）で探した。黄の帯（2000〜2399）に入り、このページの手法で解く問題は第三者の解説で確かめられなかった。abc461_g（Graph Problem 2026、2391）は題名で拾ったが、検索結果の要約では二部グラフの最大独立集合の問題で、このページの手法ではないので除いた。abc306_h（Balance Scale）は O(3^N) の包除だが、数えるのは向きの付け方で連結なグラフの数え上げではないので除いた
- 検索結果に atcoder.jp の公式解説（abc213・abc236・abc253・abc321・abc327・abc389 など）が出たが、noai のため開いていない。候補の裏付けはどれも第三者のブログで確かめた

## 結論

- 確かめた候補は 4 問（practice 1：abc321_g、challenge 3：abc253_h・abc389_g・abc236_h）
- abc321_g を練習に足せば、練習は合わせて 2 問（abc180_f・abc321_g）になり、目標の下限に届く。黄の帯にぴったり入る候補は見つからなかった
- 新しく使ったドメインはない（drken1215.hatenablog.com・kmjp.hatenablog.jp は付録 B にある）
