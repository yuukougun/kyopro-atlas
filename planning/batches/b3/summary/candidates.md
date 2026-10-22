# b2・b3 の問題の補充の候補

出どころは各 `<id>.md` の「問題の補充の候補」と検証の指摘への対応。台帳への追加・役割の変更まで提案されたものは ledger.md にも載せた（「ledger にも記載」）。裏付けの「未読」「要約だけ」は執筆者の申告のまま。台帳に入れる前に問いを第三者の解説で確かめる。

## 1. 候補の問題（問題 ID 順）

| 問題 ID | 役割の案（ページ） | 何を問うか・使い方 | 裏付けの URL | 出したページ |
| --- | --- | --- | --- | --- |
| ABC167 F（括弧列を並べる） | exchange-argument の strict-weak-ordering 節の練習 | 2 組に分けてソートする狭義の弱順序の例（patterns/bracket-sequence と共通）。台帳の状態と解説は未確認 | — | exchange-argument |
| abc003_4（AtCoder社の冬、diff 2033 参考値） | inclusion-exclusion の練習か本文の参照（4 辺の条件の最小の例） | R×C の部屋の X×Y の区画に机 D 個とロッカー L 個をすべて置き、区画の 4 辺それぞれに何かがある配置の数。4 辺の条件を 16 通り包除 | https://torus711.hatenablog.com/entry/20131212/p1 | inclusion-exclusion |
| abc020_d（LCM Rush、diff 2695 参考値） | mobius-function の力試し（発展） | Σ lcm(i, K)（N, K ≤ 10^9）。gcd ごとに分け K/x と互いに素な i' の和を μ(d) ≠ 0 の約数で足し引き（gcd-one の節の型そのもの） | https://tsutaj.hatenablog.com/entry/2017/07/01/073648 | mobius-function |
| abc054_c（C. One-stroke Path、diff 1244） | euler-path の本文の参照（「一筆書き」でも頂点の話＝ハミルトン路の例）。持ち主は順列全探索か bit-dp | 頂点 1 から全頂点を 1 回ずつ通るパスの数（N ≤ 8） | https://drken1215.hatenablog.com/entry/2019/09/16/224600 | euler-path |
| abc116_c（Grand Garden、diff 542） | difference-sequence の練習（先頭の易しい 1 問） | （ledger の新しい問題）区間 +1 で目標の高さにする最小回数。黄の練習はほかに見つからない | https://oraclesqlpuzzle.ninja-web.net/kyoupro/05-atcoder-02-abc/kyoupro-abc116-c.html | difference-sequence |
| abc133_f | persistent-data-structures の力試し（path-copying） | （ledger にも記載）色 x の辺の長さを y にしたときの 2 頂点間の距離 | https://qiita.com/hotman78/items/9c643feae1de087e6fc5 | persistent-data-structures |
| abc155_e（Payment、diff 1569） | digit-dp の練習か digit-dp-advanced の carry 節の易しい練習 | 10 の累乗の額面で N 円を払う枚数とお釣りの枚数の和の最小（N は巨大）。本文は未読 | https://kmjp.hatenablog.jp/entry/2020/02/17/0900 | digit-dp-advanced |
| abc162_e（台帳にあり） | euler-phi の練習 | （ledger にも記載）Σ_d φ(d) ⌊K/d⌋^N | — | euler-phi |
| abc182_f（Valid payments、diff 2121） | digit-dp-advanced の carry 節の練習（黄） | 払う硬貨とお釣りの硬貨に同じ額面が現れない「お釣りの額」の数（繰り上がりの有無を状態に）。問いの詳細は未確認 | https://kyo-pro.hatenablog.com/entry/ABC231E（ABC231 E の難しい版として言及） | digit-dp-advanced |
| abc202_e（diff 1638、台帳にあり euler-tour の例題） | merge-sort-tree の練習 | （ledger にも記載）頂点 U を祖先に持つ深さ D の頂点の数 | https://blog.hamayanhamayan.com/entry/2021/05/22/225525 | merge-sort-tree |
| abc202_e（1638）・abc014_4（1856） | centroid-decomposition（参考程度・載せない案） | 本来はオイラーツアーと二分探索／LCA の方が素直 | 同上 | centroid-decomposition |
| abc211_c（台帳では subsequence-and-substring の例題） | dp-phase の練習（matched-prefix の最も易しい形） | 8 文字を選んで chokudai になる選び方の数 | https://qiita.com/sano192/items/051207b6607b56cc439e（台帳の evidence） | dp-phase |
| abc211_f（Rectilinear Polygons、diff 2350） | convex-hull の point-in-polygon の節の力試し | 軸に平行な多角形と多数の点の内外（含む多角形の数）と思われる。解説は未確認 | — | convex-hull |
| abc214_d | bottleneck-path の practice | （ledger にも記載）全頂点対のパス上の最大の辺の和 | https://blog.hamayanhamayan.com/entry/2021/08/15/034729 | bottleneck-path |
| abc214_h（H. Collecting、diff 3138）・abc224_h（H. Security Camera 2、diff 2887） | min-cost-flow の力試し（発展） | SCC で縮約した DAG で K 人の経路・頂点の分割とコスト／LP の双対で最小費用流。どちらも未読 | https://kmjp.hatenablog.jp/entry/2021/08/16/0930 ・ https://kmjp.hatenablog.jp/entry/2021/10/26/0930 | min-cost-flow |
| abc215_h（Cabbage Master、diff 3101） | zeta-mobius-subset の力試し（発展） | （ledger にも記載）Hall の条件の全部分集合の確認にゼータ変換 | https://kmjp.hatenablog.jp/entry/2021/08/22/0930 | zeta-mobius-subset |
| abc235_h（Ex. Painting Weighted Graph、diff 2967） | merge-process-tree の力試し向き | 同じ重みの辺で成分がまとまる過程で塗り方を数える。執筆者は記事未読 | https://kmjp.hatenablog.jp/entry/2022/01/17/0930（research/03 の記載） | bottleneck-path |
| abc236_h（Ex. Distinct Multiples、diff 2898） | inclusion-exclusion-dp の力試し | 各 i で D_i の倍数かつ M 以下の正整数を選びすべて異なる列の数。等しいと指定した組の集合で包除し連結成分ごとの係数を bitDP でまとめる。本文は未読 | https://kmjp.hatenablog.jp/entry/2022/01/24/1100 ・ ikatakos …/2022/0123_abc236 | inclusion-exclusion-dp |
| abc237_e | bellman-ford の practice | （ledger にも記載）負辺をポテンシャルで消す。練習が 1 問のため | https://kyo-pro.hatenablog.com/entry/ABC237E | bellman-ford |
| abc245_f（F. Endless Walk、diff 1451） | game-retrograde-analysis の練習（練習 0 問） | （ledger にも記載）出次数のカウンタと逆辺で確定を広げる。探すなら kanpurin の典型問題メモの「後退解析」の項から | https://kyo-pro.hatenablog.com/entry/ABC245F ・ https://kanpurin.hatenablog.com/entry/2020/04/07/182948 | game-retrograde-analysis |
| abc248_g（GCD cost on the tree、diff 2514） | mobius-function（未確認） | 木の全パスのパス上の gcd × 頂点数の総和と思われる。解説未読 | — | mobius-function |
| abc253_h（We Love Forest、2758）・abc327_g（Many Good Tuple Problems、2968） | counting-labeled-graphs（未確認のため候補外） | 型に合うが解説の本文を確かめられなかった | — | counting-labeled-graphs |
| abc254_f（Rectangle GCD、diff 1764、台帳で確認済み） | sparse-table の練習（練習問題の節がない） | （ledger にも記載）A_i + B_j の行列の部分長方形の gcd。隣接差の区間 gcd を Sparse Table で | https://kazun-kyopro.hatenablog.com/entry/ABC/254/F | sparse-table |
| abc266_g（Yet Another RGB Sequence、diff 2045、台帳にあり） | insertion-dp の練習に重ねるか | drken の「挿入DP」カテゴリ。multinomial-coefficient の練習 | https://drken1215.hatenablog.com/entry/2023/05/04/185000 | insertion-dp |
| abc267_f（1939） | centroid-decomposition の練習（役割の追加） | 距離がちょうど K_i の頂点を 1 つ答える。想定は直径の端点と LCA | 同上 | centroid-decomposition |
| abc284_f（台帳では z-algorithm の例題・rolling-hash の練習） | hash-safety の練習（出典が見つかれば） | 「法 2^64 で WA と TLE、2^61−1 で通った」記録の出典が特定できない（hyouchun の qiita にはない）。検証の指摘 8 でも採らず、frequency C で練習 1 問のまま | — | hash-safety |
| abc303_e（diff 1113）・abc378_f（diff 1436） | tree-degree の練習 | （ledger にも記載）星の中心は次数 3 以上／閉路の頂点の次数がすべて 3 になる足し方。abc412_g（3402）は発展、abc303_h は cayley-pruefer 側 | drken の記事 | tree-degree |
| abc314_h（Ex. Disk and Segments、diff 2938） | ternary-search-caveats（黄）の力試し。台帳にない | 入れ子の三分探索の発展の例。執筆者は未読 | https://drken1215.hatenablog.com/entry/2023/08/12/231800（研究ノートの記載） | circle-geometry |
| abc317_d（台帳では knapsack-01 の練習） | dp-dimension-reduction の練習（易しい例） | 議席の過半数を取る鞍替えの最小。議席数を添字、人数の最小を値にする入れ替え | https://programming-hiroba.com/abc317-d/ | dp-dimension-reduction |
| abc332_e（E. Lucky bag、diff 1883） | subset-enumeration-dp の practice | N ≤ 15 個の品物を D 個の袋に分け（空の袋も許す）分散を最小に。状態は「入れた品物の集合と袋の数」、部分集合を 1 袋にまとめる遷移。空の袋にも値があるので初期値に注意（本文の「空のグループにも値がある」の型そのもの） | https://qiita.com/rareshana/items/76af4e8d8dcbedfc8714 ・ https://qiita.com/navel_tos/items/7d4db517b8a0c3d4d21b | subset-enumeration-dp |
| abc332_e | expectation-of-square の practice（variance の節） | （subset-enumeration-dp の候補と同じ問題。両方の pages に）。ペアに分ける型の練習が 0 問なので次のバッチの補充で探したい | https://qiita.com/rareshana/items/76af4e8d8dcbedfc8714 | expectation-of-square |
| abc334_f（F. Christmas Present 2、diff 1813） | dp-segment-tree の dp-sliding-window の節の例題か練習（節に例題がない） | 容量 K の袋で順に配り拠点との往復を挟む最短距離。直近 K 軒からの遷移で i だけの項を外に出すと窓の最小 | https://kazun-kyopro.hatenablog.com/entry/ABC/334/F（記事は遅延セグ木で解く。スライド最小値は式からで記事では未確認） | dp-segment-tree |
| abc334_f | inline-dp の practice | 状態（位置, 持っている個数）の表で、写し・オフセット・ずらしの 3 つの道具がそろう（dp-segment-tree の候補と同じ問題） | https://inamori.hateblo.jp/entry/2023/12/28/193744（check_noai で noai なし） | inline-dp |
| abc335_g（Discrete Logarithm Problems、diff 2614） | multiplicative-order の側（入れなかった） | 位数を P − 1 の約数から求める。第三者の解説は未確認 | — | euler-phi |
| abc339_g | persistent-data-structures の練習（prefix-versions） | （ledger にも記載）区間内で X 以下の要素の和をオンライン強制で答える | https://tayu0110.hatenablog.com/entry/2024/02/05/205618 | persistent-data-structures |
| abc348_e（diff 1347） | tree-centroid の練習（先頭） | （ledger にも記載）Σ C_i d(v, i) の最小値。重み付き重心 | https://qiita.com/gotoki_no_joe/items/6a3a10194d5a276281ca | tree-centroid |
| abc349_f（Subsequence LCM、diff 2169） | divisor-inclusion-exclusion の力試し（または zeta-mobius-subset の例題） | 空でない部分列で lcm がちょうど M のものの数。M の約数の上で引く。主な解説は素因数の bit の高速ゼータ・メビウス変換 | https://www.cnblogs.com/MoyouSayuki/p/18134468 ・ https://merom686.hatenablog.com/entry/2024/04/14/011833（検索の要約だけ） | divisor-inclusion-exclusion |
| abc349_f（Subsequence LCM、diff 2169） | zeta-mobius-subset の練習（vs-subset の節の型の代表） | （divisor-inclusion-exclusion の候補と同じ問題）M を素因数分解し、各要素を「指数が M と等しい素数の集合」の bit に潰して部分集合のゼータ → 2 の冪 → メビウス | https://merom686.hatenablog.com/entry/2024/04/14/011833 | zeta-mobius-divisor |
| abc349_f（Subsequence LCM、diff 2169） | zeta-mobius-subset の practice（練習がない） | （ledger の新しい問題。3 ページから） | https://merom686.hatenablog.com/entry/2024/04/14/011833 | zeta-mobius-subset |
| abc360_g（台帳では lis の練習） | dp-phase の練習（「変更済みか」の 2 段階） | 要素を 1 つ変えてよいときの LIS の最大。台帳の evidence は usaco.guide のみなので日本語の解説を足してから | —（未確認） | dp-phase |
| abc364_d（ABC364 D. K-th Nearest、diff 1136） | kth-value の practice | （ledger の新しい問題）距離を二分探索し区間に入る点を lower_bound・upper_bound で数える | https://oraclesqlpuzzle.ninja-web.net/kyoupro/05-atcoder-02-abc/kyoupro-abc364-d.html | kth-value |
| abc368_e（E. Train Delay、diff 2140） | difference-constraints の力試し（要確認） | 遅延 X_i を X_j − X_i ≥ T_i − S_j の下で総和最小（記憶による）。第三者の解説で未確認、主は時刻順の処理と思われ候補として弱い | research/03-graph の表 | difference-constraints |
| abc373_g（geometry-vectors の力試し） | min-cost-flow の割当問題の節の練習に足すなら役割を相談 | 最小重み完全マッチングには交差がない性質の問題 | — | min-cost-flow |
| abc375_g（Road Blocked 2、diff 2014）・abc334_g（Christmas Color Grid 2、diff 2242） | lowlink の練習（または例題） | （ledger にも記載）最短路に乗る辺の部分グラフの橋／関節点で切り離される部分木を数える | https://www.cnblogs.com/codwarm/p/18463129 ・ https://amentorimaru.hatenablog.com/entry/2025/04/11/210228 | lowlink |
| abc379_f（Buildings 2、diff 1659） | merge-sort-tree（要確認） | yuu_kyopro の記事がマージソート木の使える問題として挙げる。問いと解き方は未確認 | https://qiita.com/yuu_kyopro/items/51ad67c3c980bf91c5a6 | merge-sort-tree |
| abc389_d（Squares in Circle、diff 749） | circle-geometry の練習（節 lattice-points-in-circle。基礎帯） | 中心のマスを中心とする半径 R の円に全体が入るマスの数。マスの右上の格子点が円の内部にあるかに言い換え、列ごとに高さの最大を二分探索（または尺取り）。座標を 2 倍して整数で判定 | https://kcpc.hatenablog.com/entry/2025/01/20/032000（ほかに https://yuulis.hatenablog.com/entry/ABC-389-D は未確認のドメイン） | circle-geometry |
| abc389_g（G. Odd Even Graph、diff 2762） | counting-labeled-graphs の力試し（#bfs-layers の応用。発展の帯） | 辺の数 M ごとに、頂点 1 からの距離が偶数・奇数の頂点数が等しい N 頂点の連結な単純無向グラフの数を P で割った余り。層の大きさ・偶奇の差・辺の数を状態にする DP | https://kmjp.hatenablog.jp/entry/2025/01/19/1000 | counting-labeled-graphs |
| abc390_d（diff 1607、台帳で確認済み） | counting-dedup の練習（#min-index） | N ≤ 12 個の袋の石を袋ごと移す操作の後の XOR の種類数。最後の状態は集合の分割に対応し最小番号から組を決めてベル数通り全列挙（set で数える） | https://oraclesqlpuzzle.ninja-web.net/kyoupro/05-atcoder-02-abc/kyoupro-abc390-d.html ・ https://yuulis.hatenablog.com/entry/ABC-390-D（台帳の evidence） | counting-dedup |
| abc391_f（K-th Largest Triplet） | greedy-priority-queue#k-best 向き（kth-value ではない） | 優先度付きキューで小さい順に取り出す型 | — | kth-value |
| abc401_g（2022） | bipartite-matching の例題の方が合う（max-flow の練習にはしない） | 答えで二分探索して完全マッチング判定 | — | max-flow |
| abc405_e（E. Fruit Lineup、diff 1259） | binomial-identities の練習（水だが「閉じた式を探しすぎる」の例） | 4 種類の果物を種類ごとの順序の条件を満たして並べる方法の数。左端の葡萄の左のバナナの個数 k で分け、C(A+B+k, B)·C(D−1+C−k, C−k) を k について足す。和の範囲が途中で切れて閉じた式にならず O(C) のループ | https://qiita.com/testcampus/items/1389257a0c177ceb736a ・ https://zenn.dev/sukenori/articles/sukenori-abc405 ・ https://rsk0315.hatenablog.com/entry/2025/05/11/201737 | binomial-identities |
| abc405_f（Chord Crossing、diff 1588） | merge-sort-tree（要確認） | 同じ記事が挙げる（題名と ID の食い違いの可能性）。merom686 はセグ木の別解で、マージソート木での裏付けなし | https://merom686.hatenablog.com/entry/2025/05/11/021302 | merge-sort-tree |
| abc405_g・typical90_ac（台帳にあり） | sqrt-decomposition の練習 | （ledger にも記載）値の平方分割（Mo と共有）／配列のバケット分割で区間 max・区間代入。abc319 以降でバケット分割そのものやクエリの平方分割の例題はない | https://kmjp.hatenablog.jp/entry/2025/05/10/0900 | sqrt-decomposition |
| abc411_e（E. E [max]、diff 1400） | expectation-tail-sum の練習 | （ledger の新しい問題案）サイコロの最大値の期待値。面の値の範囲は要確認 | https://qiita.com/Shizen_Tota/items/687ddc17baff09e97176 ・ https://kcpc.hatenablog.com/entry/2025/06/28/233000 | expectation-tail-sum |
| abc412_f | rational-mod の練習（b1 rational-mod.md:32 の申し送りへの答え） | （ledger にも記載）比較が要り答えを mod で出す（比較は性質で消える型） | https://qiita.com/gotoki_no_joe/items/dbd1cf6437edd867afa3 | optimal-strategy-expectation |
| abc437_g（G. Colorful Christmas Tree、diff 2806） | max-flow の力試し（発展の帯。flow 系の発展のページに回すか） | research/03-graph §4.G で「最大流」。裏付けは未調査（kmjp の記事を探す） | — | max-flow |
| abc448_f（Authentic Traveling Salesman Problem、diff 1719） | mo-algorithm の練習（ordering の節「並べ方だけを使う」） | 点をすべて巡る閉路でマンハッタン距離の和が上限（解説によれば 10^10）以下のものを出力。x で √N 個ずつのブロックに分け、y の昇順・降順を交互に（Mo の並べ方）。上限と N の制約は別の解説で確かめてから | https://www.cnblogs.com/CR-J/p/19684169 ・ https://www.cnblogs.com/rickylin/p/19687650/ABC448（後者は未読） | mo-algorithm |
| abc453_f（F. Avoid Division、diff 2811） | tree-centroid の力試し（裏付けが取れたら） | research 00-curriculum に「木の『葉の重心』を使う構築」。第三者の文章の解説が見つからない | — | tree-centroid |
| abc455_f | lazy-segment-tree-patterns の練習（任意） | （ledger にも記載）区間加算のたびに区間の相異なる 2 要素の積の和を mod で答える | ikatakos（503 で読み直せず） | lazy-segment-tree-patterns |
| abc463_g（台帳にあり、probability-dp の力試し、diff 2452） | binomial-identities の力試し（要確認） | 距離の期待値を二項係数の和として求める。どの恒等式でまとめるかは未確認 | — | binomial-identities |
| agc005_d（D. ~K Perm Counting、diff 2943） | inclusion-exclusion-dp の力試し（count-violations の型） | すべての i で \|P_i − i\| ≠ K の順列の数。違反のマスを鎖に分けてルークの置き方を DP、(N−k)! を掛けて包除。本文は未読 | https://ei1333.github.io/luzhiled/snippets/memo/inclusion-exclusion.html | inclusion-exclusion-dp |
| agc032_c（C. Three Circuits、diff 2284） | euler-path の力試し（黄） | 単純な連結グラフの辺全体を 3 つの閉路に分けられるか。全頂点の次数が偶数が前提で、次数 4 の頂点の数と次数 6 以上の頂点の有無で場合分け | https://drken1215.hatenablog.com/entry/2019/03/28/161000 | euler-path |
| agc045_a（2070）・zone2021_f（2197） | xor-basis の練習 | （ledger の新しい問題案）。abc223_h（2771、発展、未確認）は候補外 | https://maspypy.com/atcoder-%E5%8F%82%E5%8A%A0%E6%84%9F%E6%83%B3-2020-06-07agc045 ・ https://fairy-lettuce.hatenadiary.com/entry/2021/05/02/004052 | xor-basis |
| arc028_4（D. 注文の多い高橋商店、diff 2997 参考値） | knapsack-undo の力試し（難しすぎるのでメインの判断） | 個数制限付きの数え上げの表から 1 種類を取り除いた値を各クエリで答える（戻す DP の個数制限付き版）。記事は今回未読 | https://drken1215.hatenablog.com/entry/2020/10/04/152700（research/02 で既出） | knapsack-undo |
| arc039_d（旅行会社高橋君、diff 2550 参考値） | lowlink の力試し | （ledger の新しい問題案） | https://ei1333.github.io/luzhiled/snippets/graph/two-edge-connected-components.html | lowlink |
| arc074_d（ARC074 F. Lotus Leaves、diff 2208） | min-cut の練習（vertex-cut。練習がない） | 同じ行・列の葉へ跳ぶ蛙がゴールに着けないように消す最小の枚数（不可なら −1）。葉を入口と出口に分けた頂点カット（行・列を頂点に） | https://kmjp.hatenablog.jp/entry/2017/05/20/0930 ・ https://blog.hamayanhamayan.com/entry/2017/05/20/230731（後者は未読） | min-cut |
| arc085_a（C. HSI、diff 752） | expectation-tail-sum の練習（入門） | 幾何分布を P(T ≥ k) の等比級数で。黄の練習にふさわしい問題は見つからない（drken のカテゴリは ABC では abc352_g と arc085_a だけ） | https://drken1215.hatenablog.com/entry/2019/03/23/175300 | expectation-tail-sum |
| arc087_c（ARC087 E. Prefix-free Game、diff 2431） | grundy-number（trie の b1 報告の候補） | Trie の空いた部分木ごとの Grundy 数を XOR。第三者の解説が見つからず evidence を探す必要 | — | grundy-number |
| arc087_d（F. Squirrel Migration、diff 3252） | tree-centroid の発展の力試し（pair-across の順列の段落） | 順列で Σ d(i, p_i) を最大にするものの数（記憶）。未確認 | — | tree-centroid |
| arc091_d（ARC091 F. Strange Nim、diff 2395） | grundy-number の力試し（patterns の節） | 各山で石 X 個のとき 1 個以上 ⌊X/K_i⌋ 個以下を取れる Nim。X が K の倍数なら X/K、そうでなければ X − ⌈X/K⌉ の山と同じ値。商が同じ間はまとめて引く | https://kmjp.hatenablog.jp/entry/2018/03/11/1130 | grundy-number |
| arc121_e・arc101_c（発展、level_evidence） | tree-dp-square の力試しの候補 | 第三者の解説で問いを確かめていない | — | tree-dp-square |
| arc122_d（D. XOR Game、diff 2331） | binary-trie の力試し | 2N 個の整数を 2 人が交互に取り、組の XOR の最大値を先手は大きく後手は小さくしたいときの値。上位 bit で分け、両側が偶数個なら再帰、奇数なら 2 つの集合をまたぐ組の XOR の最小を Binary Trie で求める | https://kmjp.hatenablog.jp/entry/2021/06/13/0930 | binary-trie |
| arc122_a（A. Many Formulae、diff 783） | parsing の練習 | 数の間に + か − を入れ − が続かない式すべての値の和を mod で。最後の演算子ごとに式の数と値の和を持つ DP（式の部分文字列の総和の易しい版）。検索の要約だけ | https://zenn.dev/hal_mat/articles/0c3857b22b6ff1 ・ ikatakos …/2021/0612_arc122 | parsing |
| arc136_b（B. Triple Shift、diff 1358） | permutation-parity の練習（練習 1 問のため。検証の指摘 4 も同じ） | 隣り合う 3 要素を巡回させる操作で A を B にできるか（多重集合が違えば No、同じ値があれば Yes、なければ転倒数の偶奇）。入れば「隣り合う 3 か所だけを巡回させる」の箇条から練習へリンク | https://note.com/syamashi/n/nb491ffdf0ca3 ・ ikatakos …/2022/0227_arc136（503 で未読） | permutation-parity |
| arc143_d（diff 2229） | graph-construction の力試し | 辺の向きを選び橋の数を最小にする。DFS の順に向きを付けて閉路を作る（DFS 木の辺と後退辺を逆向きにする向き付けと同じ） | https://kmjp.hatenablog.jp/entry/2023/03/16/0900（記述が短い。別の解説でも確かめたい） | graph-construction |
| arc145_c（Split and Maximize、diff 1697） | reflection-principle の練習（catalan の節。練習 0 問） | （ledger の新しい問題）。arc202_d（3116）・arc147_f（4016）は難しすぎ、kupc2020_m は内容未確認。abc319 以降で鏡像法を直接使う ABC はない | https://kmjp.hatenablog.jp/entry/2023/09/21/1000 | reflection-principle |
| arc159_b（GCD Subtraction、diff 1438、台帳になし） | gcd-properties の練習（差の gcd の節「2 つの数から同じ数を引き続ける」） | 両方から gcd を引く操作を片方が 0 になるまで何回か。差が不変で gcd の候補が差の素因数に絞れる | https://www.luogu.com.cn/article/x31btgkz（中国語。日本語の解説でもう一度確かめる） | gcd-properties |
| arc185_e（Adjacent GCD、diff 2185） | divisor-inclusion-exclusion の力試し | 接頭辞ごとに全部分列の隣り合う項の gcd の和の総和。gcd = Σ_{d∣gcd} φ(d) | https://www.cnblogs.com/georgeyucjr/p/18464435（検索の要約だけ） | divisor-inclusion-exclusion |
| arc185_e（Adjacent GCD、diff 2185） | zeta-mobius-divisor の力試し（黄）か mobius-function・euler-phi の練習 | （divisor-inclusion-exclusion の候補と同じ問題）gcd(a, b) = Σ_{d\|gcd} φ(d) に分け、d の倍数ごとに 2^i の和を持って更新 | https://kmjp.hatenablog.jp/entry/2024/10/19/0900 | zeta-mobius-divisor |
| arc185_e | euler-phi の力試し（divisor-sum） | （ledger の新しい問題。zeta-mobius-divisor・divisor-inclusion-exclusion と重複） | https://kmjp.hatenablog.jp/entry/2024/10/19/0900 | euler-phi |
| arc185_e | mobius-function の練習（黄） | （euler-phi・zeta-mobius-divisor・divisor-inclusion-exclusion と同じ候補） | https://kmjp.hatenablog.jp/entry/2024/10/19/0900 | mobius-function |
| dp_u・typical90_as | bell-number の practice | （ledger にも記載）vs-subset-dp の対比。練習が 1 問のため | 台帳の evidence | bell-number |
| dwacon2018_prelims_c（C. Kill/Death、diff なし） | partition-number の練習 | （ledger の新しい問題案）ABC の候補が見つかればそちら優先。kmjp・drken の「分割数」カテゴリでは ABC が見つからない | https://drken1215.hatenablog.com/entry/2023/05/07/160611 ・ https://drken1215.hatenablog.com/entry/2018/01/16/222843 | partition-number |
| exawizards2019_d（D. Modulo Operations、diff 2075） | insertion-dp の練習（値の順に挿入する見方。水〜黄の易しい側） | （ledger の新しい問題案）dp[i+1][x] = dp[i][x mod s] + i·dp[i][x] | https://drken1215.hatenablog.com/entry/2019/04/01/201600 | insertion-dp |
| joi2020_yo2_e（E. じゃんけん式、diff なし） | parsing の練習 | 式の ? を埋めて結果が指定の手になる方法の数を再帰下降で数える（記憶）。問いは未確認 | https://blog.hamayanhamayan.com/entry/2019/11/09/180622（一覧の行だけ） | parsing |
| keyence2019_e（2623）・abc282_h（2621、台帳にない） | divide-and-conquer の力試し（crossing／split-at-max） | （ledger にも記載）どちらも 2600 台で黄には難しい。練習に置ける黄までの ABC は見つからない（drken の「分割統治法」の ABC は 2400 以上で多くは分割統治 FFT） | https://drken1215.hatenablog.com/entry/2019/01/15/081500 ・ https://kmjp.hatenablog.jp/entry/2022/12/18/0930 | divide-and-conquer |
| math_and_algorithm_bu（アルゴ数学 098. Polygon and Point、diff なし、台帳になし） | convex-hull の point-in-polygon の節の練習 | 一般の多角形の内外判定（交差数）と思われる。第三者の解説が見つからず問いは未確認 | — | convex-hull |
| nyc2015_5（E. ひも、diff なし） | cayley-pruefer の練習（degree-sequence） | （ledger の新しい問題）次数を指定した全域木の数。練習が 0 問のため。ABC からは見つからない（abc253_h は行列木定理、abc359_f は tree-degree） | https://drken1215.hatenablog.com/entry/2020/10/25/132900 | cayley-pruefer |
| tenka1_2015_qualA_d（ハシポン、2559）・arc045_d（みんな仲良し高橋君、3039）・arc062_d（Painting Graphs with AtCoDeer、3175） | lowlink（難しすぎ・未読） | hamayan の一覧にあるだけ | https://blog.hamayanhamayan.com/entry/2016/10/18/123552 | lowlink |
| yahoo_procon2018_final_c（diff なし） | centroid-decomposition の練習（centroid-tree-queries） | （ledger の新しい問題）距離がちょうど K_i の頂点の数 | https://qiita.com/navel_tos/items/d1a2fd2b63e73380eadb | centroid-decomposition |

## 2. 探索の結果・依頼（候補が見つからなかったページ）

| ページ | 内容 |
| --- | --- |
| binary-trie の練習 | 練習が abc425_g の 1 問だけ。abc319 以降で Binary Trie を主に使う問題は題名検索では見つからない。問題の補充で第三者の解説のタグから探す |
| counting-bijection | abc319 以降で対応づけが鍵の問題は見つからなかった。abc458_e（1309）は fix-variable が主で未確認のため提案しない。古い候補 abc205_e（White and Black Balls）は鏡像法が主で reflection-principle の例題向き（drken の「経路数に帰着」カテゴリ） |
| degree-sqrt | 確かめきれた候補なし。abc258_g は N ≤ 3000 の密なグラフでこの手法では間に合わないので bitset 側。練習は 1 問のまま（Library Checker enumerate_triangles・counting_c4 は verify） |
| exchange-argument-dp | 目安は満たす。abc319 以降は abc366_f の 1 問だけ。新しい候補なし |
| expectation-linear-equations の練習 | 練習は abc189_f の 1 問で abc319 以降なし。「振り出しに戻る・円環・連立方程式」の期待値の問題を research 02・07 の調査役か次の調査で探す |
| gaussian-elimination の練習 | 練習は abc128_c の 1 問。atcoder-tags の「行列」「XOR」タグ一覧から kmjp・drken の解説で掃き出しを使うものを拾う（https://atcoder-tags.herokuapp.com/tags/Mathematics/Matrix） |
| gcd-properties | abc469_f は別の型なので足さない。abc319 以降で差の gcd・区間 gcd・mod の周期が鍵の問題は見つからない。格子点の節は typical90_ao（convex-hull の例題）へリンクだけ |
| grundy-number | abc319 以降は abc368_f のほか見つからない。AtCoder Tags などから探す |
| interval-dp | abc319 以降の青の区間 DP は見つからず（drken の「区間DP」カテゴリの abc329_f・abc432_c は区間 DP でないと判断）。abc319 以降の目安は力試し abc325_g（2388）だけが満たす。例題が EDPC N と典型90 019 で ABC がない → abc217_f（1954）を例題に上げる案 |
| randomized | 区間の過半数（セグ木に (候補, 個数)）と Freivalds の行列積の検査の ABC の例が見つからない。abc455_g（3092、乱択ハッシュ、level_evidence）は内容未確認 |
| root-path-dfs | abc319 以降の問題なし（catalog の problems_note のとおり）。候補なし |
| segment-tree-monoids の練習 | abc309_f・abc283_f を segment-tree-on-values へ移すなら、情報を足して載せる型の問題を補う |
| string-automaton-dp | 力試し 0。ikatakos が読めず新しい候補は探していない |
| sweep-line-2d の union-area の節（黄） | 例題が台帳にない（Library Checker area_of_union_of_rectangles は verify）。ABC から 1 問あれば練習に |
| tree-path の練習（練習 1 問・abc319 以降なし） | abc014_4（閉路の長さ＝距離＋1）・abc267_f（K 個上の祖先）・typical90_ai（DFS 順で隣り合う 2 点の距離の和の半分）。どれも持ち主は lca。typical90_ai を足すなら sol/035-04.cpp を裏付けに |
| zeta-mobius-divisor | 練習は abc393_e の 1 問だけ。青の帯で素数ごとの変換か GCD 畳み込みを直接使う ABC は見つからない |
| bipartite-matching の greedy-cases の節 | しきい値の形・区間の形で貪欲とマッチングの見分けを問う ABC の E〜F があれば練習に |
| broken-profile-dp | 1 行ずつ進める形の練習がない（abc113_d は例題）。行の配置どうしの相性だけが条件の ABC（幅 8〜10）を AtCoder Tags の Bit-DP・DP から探す |
| complement-graph-bfs | ABC319 G 以外は見つからない。練習は Library Checker の connected_components_of_complement_graph で補い、練習・力試しの見出しは置いていない |
| interval-dp-advanced | 新しい候補は探していない。発展の abc261_g（2803）・abc262_g（3114）は黄の範囲外 |
| konig-theorem | 黄の例題が 1 問（abc274_g）。易しめの例題（ABC の F・典型90 の二部グラフの最大独立集合など）があれば |
| min-cost-flow | 練習 2 問。abc319 以降で重み付き二部マッチング・slope を使う ABC G を探す余地 |
| multiplicative-order | 新しい探索なし。abc319 以降で位数・離散対数を主に使うのは abc335_g（力試し）だけ |
| optimal-strategy-expectation の guess-answer の節 | 「やり直しを答えの二分探索で解く」型の実数で答える ABC は見つからない（abc224_g は 1 次方程式が本筋） |
| subsequence-dp | frequency_evidence が recent 0。abc319 以降で「異なる部分列の個数」を問う問題を探す価値 |
| tree-dp-square の cap-k の節 | 「N ≤ 10^5 の木から K ≤ 100 個選ぶ」型の確認済みの問題があれば練習に |

## 3. まとめて見ると

- 複数のページが同じ問題を挙げたもの：arc185_e（divisor-inclusion-exclusion・zeta-mobius-divisor・euler-phi・mobius-function）、abc349_f（divisor-inclusion-exclusion・zeta-mobius-divisor・zeta-mobius-subset）、abc332_e（subset-enumeration-dp・expectation-of-square）、abc334_f（dp-segment-tree・inline-dp）、keyence2019_e（centroid-decomposition・divide-and-conquer）
- 練習が目安（2〜6）に届かないと報告したページ：bell-number・bellman-ford・binary-trie・graph-construction・hash-safety・expectation-linear-equations・gaussian-elimination・permutation-parity・sparse-table（練習の節なし）・tree-path・degree-sqrt・zeta-mobius-divisor・counting-labeled-graphs・cayley-pruefer（0 問）・tree-centroid（0 問）・game-retrograde-analysis（0 問）・reflection-principle（0 問）・zeta-mobius-subset（0 問）・euler-path（台帳に 0 問）・complement-graph-bfs（Library Checker のみ）・expectation-tail-sum（節なし）・min-cut（0 問）・divide-and-conquer・euler-phi・mobius-function・difference-sequence（下限）・min-cost-flow（下限）
- abc319 以降の問題がない（水・青の目安を満たさない）と報告したページ：counting-bijection・expectation-linear-equations・graph-construction・tree-path・root-path-dfs・bottleneck-path（frequency_evidence の recent 0 と合う）
- 探し方の提案：ap.py は題名の検索しかできないので、型での検索は AtCoder Tags（例 https://atcoder-tags.herokuapp.com/tags/Mathematics/Matrix）・kanpurin の典型問題メモ・drken のカテゴリ・hamayan のまとめから拾い、第三者の解説で確かめる（binary-trie・gaussian-elimination・grundy-number・broken-profile-dp・game-retrograde-analysis）
