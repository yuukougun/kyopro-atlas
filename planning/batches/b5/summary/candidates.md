# b4・b5 の問題の補充の候補

出どころは各 `<id>.md` の「問題の補充の候補」と検証の指摘への対応。台帳への追加・役割の変更まで提案されたものは ledger.md にも載せた（「ledger にも記載」）。裏付けの「未読」「タグだけ」は執筆者の申告のまま。台帳の状態は 2026-10-22 の data/problems.yaml で見た。台帳に入れる前に、問いを第三者の解説（2 つ以上が目標。§15-6）で確かめる。

## 1. 台帳にない問題（問題 ID 順）

| 問題 ID | 役割の案（ページ） | 何を問うか・使い方 | 裏付けの URL | 出したページ |
| --- | --- | --- | --- | --- |
| abc208_f（diff 2772） | lagrange-interpolation の 2 つ目の例題（「答えが多項式になる DP」の代表） | 数列の累積和を M 回取った表の N 番目の値（N が巨大）。答えが N の K + M 次式になるので小さい N の値から補間する。今は本文で ID を出さず「数列の累積和を何回も取った値を問う型」とだけ書いた | https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2021/0704_abc208 ・ https://nyaannyaan.github.io/docs/problems/editorials/ （手法名だけ） | lagrange-interpolation |
| abc232_g（G. Modulo Shortest Path、diff 2550） | segment-tree-graph・extended-dijkstra の練習か related の候補（modular-shortest-path の例題には向かない） | 辺 i→j のコストが (A_i + B_j) mod M の完全グラフの最短路を、M 個の余りの補助頂点を閉路に並べて辺を O(N) にして解く。本質は補助頂点で辺を減らす型（研究ノート 03-graph で「区間に辺を張るのはこれを階層化したもの」） | 第三者の解説の URL は未確認（検索で見た公式解説の要約だけ） | modular-shortest-path・segment-tree-graph |
| abc235_h（diff 2967 の見込み） | merge-process-tree の力試し | 同じ重みの辺で成分がまとまる過程で塗り方を数える（handoff-b2b3 の申し送り・03-graph の研究） | 未確認（ap.py での確認もまだ） | merge-process-tree |
| abc253_h（Ex. We Love Forest、diff 2758） | matrix-tree-theorem の練習（#subset-dp）。determinant は本文の参照だけ | 候補の辺 M 本から K 回重複を許して一様に選んで足したとき森になる確率を K = 1, …, N−1 で求める。頂点集合ごとの全域木の数を行列木定理で求め、最小の頂点を含む成分で分ける部分集合の DP で森を数える。今は ID を出さず型だけ（§13-6）。台帳に入れば練習の節を足し、参考に kmjp を戻す | https://kmjp.hatenablog.jp/entry/2022/05/28/1030 （2 つ目は未取得） | determinant・matrix-tree-theorem（ledger にも記載） |
| abc272_e（E. Add and Mex、diff 1434） | mex の練習（題材の性質＝値の上限） | 各回の操作の後の数列の mex。mex ≤ N なので [0, N] に入る値だけを列挙し、調和級数で O(N log N) | https://kyo-pro.hatenablog.com/entry/ABC272E 、https://qiita.com/MoroeTachibana-oh/items/2128746896925fbaac5c | mex |
| abc276_c（C. Previous Permutation、diff 389） | permutation の辞書順の行の練習（余力があれば） | ap.py で実在を確認。第三者の解説で問いと解き方はまだ確かめていない | 未確認 | permutation |
| abc284_d（D. Happy New Year 2023、diff 658） | prime-factorization か divisor-enum の練習（miller-rabin の例題には合わない） | N = p²q（N ≤ 9 × 10^18）の p・q。小さい方が立方根以下なので試し割りで足りる（「構造で避ける」型）。miller-rabin の本文では ID を出さず型だけ | 未確認（ikatakos は E〜G だけ、kmjp の URL は見つからない） | miller-rabin |
| abc289_h（Ex. Trio） | fps-basics の練習（多項式の逆元をそのまま使う） | research/06 §5.7 | https://nyaannyaan.github.io/docs/problems/editorials/ （タグだけ） | fps-basics |
| abc290_c（C. Max MEX、diff 225） | mex の構築の節（要素の数の必要条件の例）。練習の易しい側 | 数列から K 個を選んだときの mex の最大値。答えは min(K, mex(A)) | https://programming-hiroba.com/abc290-c/ 、https://aruma256.dev/blog/2023/03/09/abc290-c.html （aruma256.dev は noai 未確認） | mex |
| abc305_h（Ex. Shojin、diff 3344） | alien-dp の力試し | 問題の列を連続する区間（日）に分けるコストの最小を、日数の制約を罰金に置き換えて求める（research/02 §5.1 の記述。問いは未確認）。本文では触れていない | https://kanpurin.hatenablog.com/entry/2020/04/07/182948 （Alien DP の項の一覧に ABC305 H）。解法の第三者の解説は未確認（kmjp の 2023-06 の記事などで確かめる） | alien-dp |
| abc308_e（E. MEX、diff 1042） | mex の練習（fix-variable と組み合わせる型） | 文字列 MEX の位置の 3 つ組について mex の総和（真ん中を固定する） | 未読（候補のみ） | mex |
| abc345_g（G. Sugoroku 5） | fps-basics の練習（ニュートン法・ラグランジュの反転公式） | research/06 | https://nyaannyaan.github.io/docs/problems/editorials/ （タグだけ） | fps-basics |
| abc349_g（G. Palindrome Construction、diff 2655） | inverse-string-problems の練習か力試し | 各中心の回文半径から辞書順最小の数列を作る逆 Manacher の型（研究メモ 08 §4.7）。ap.py で実在を確認 | 未確認（ikatakos の 2024/0413_abc349 は F まで） | suffix-automaton |
| abc357_g（G. Stair-like Grid、diff 3159） | online-convolution（追加は提案しない） | catalog の problems_note のとおり手法の分類（Nyaan の解説一覧）だけで確かめた | タグだけ | online-convolution |
| abc370_g（G. Divisible by 3、diff 3428） | multiplicative-function の力試し（裏付けが 2 件にそろうまで載せない） | 約数の和が 3 の倍数になる数を長さ M の列の積として数える。乗法的関数の和に帰着。研究ノートでも status は tag | https://nyaannyaan.github.io/docs/problems/editorials/ （「乗法的関数の prefix sum」の手法名だけ） | multiplicative-function |
| abc380_d（Strange Mirroring、diff 849） | stress-testing#experiment の練習 | 大文字と小文字を入れ替えて連結する操作を繰り返した文字列の K 文字目。何番目のブロックが反転しているかの表が、番号の 2 進表記の 1 の個数の偶奇で決まる（小さい値の表を作ると規則が見える） | https://drken1215.hatenablog.com/entry/2024/11/17/030500 （2 件目は未確認） | stress-testing（ledger にも記載。提案者が「台帳への追加が要る」） |
| abc419_g（G. Count Simple Paths 2、diff 2677） | graph-modeling#contraction の代表 | 次数 1 の頂点を消し、次数 2 の頂点を辺にまとめてから単純パスを全列挙する。本文では型だけ | https://kmjp.hatenablog.jp/entry/2025/08/16/0930 （research/03 §5.2 H に記載。今回は読み直していない） | graph-modeling |
| agc023_f（F. 01 on Tree、diff 3148） | tree-ratio-greedy の練習（発展なので力試しでも可） | 根付き木の各頂点に 0 か 1 が書かれ、親が子より先に来るように並べた 01 列の転倒数の最小値（型の名前の由来）。問いは 3 資料から組み立てたもので N の上限などは未確認。台帳に足したら本文の「名前の 01 on Tree は過去の AGC の問題名から」を練習へのリンクに張り替える | https://github.com/hitonanode/cplib-cpp/blob/master/other_algorithms/tree_pop_order_optimization.md 、https://maspypy.com/01-on-tree-%e4%ba%ac%e9%83%bd%e8%a6%b3%e5%85%89-train-seats 、https://github.com/yosupo06/library-checker-problems/issues/1263 | tree-ratio-greedy（ledger にも記載） |
| agc024_d（D. Isomorphism Freak、diff 2307） | tree-isomorphism の練習か力試し（tree-diameter#center の力試しの方が合うかも） | 木に頂点と辺を足してよいとき、同じ色の頂点を根にした部分木がすべて同型になる塗り方の色の数の最小と、そのときの葉の数の最小。中心（頂点か辺）を根にして深さごとにそろえる考え方で、同型の判定やハッシュそのものは使わない | https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2018/0520_agc024 （解法の節だけ。2 つ目は見つからない） | tree-isomorphism |
| agc057_d | modular-shortest-path（同余最短路そのもの） | OI Wiki の練習の一覧にある | ap.py と第三者の解説で未確認 | modular-shortest-path |
| arc033_4（diff 2470、参考値） | lagrange-interpolation の練習（または例題） | N 次多項式の x = 0..N での値から x = T の値を mod 10^9+7 で求める。O(N) の補間そのもの | https://kmjp.hatenablog.jp/entry/2015/02/01/1000 ・ https://ei1333.hateblo.jp/entry/2021/07/08/221742 （ARC033 D で検証したとある） | lagrange-interpolation |
| arc067_d | monge の練習 | 焼肉店を巡る区間の選び方で、最適な左端の単調性を使う（research/02 の候補） | USACO Guide だけ（問いは未確認） | monge |
| arc070_c（ARC070 E. NarrowRectangles、diff 3365） | slope-trick の力試し | 横に並ぶ長方形を左右に動かして全体をつなげる最小コスト。区間の min（左右で違う量ずらす）と |x − l_i| の加算（research/02-dp にも） | https://maspypy.com/slope-trick-2-%e5%95%8f%e9%a1%8c%e7%b7%a8 （1 件だけ） | slope-trick |
| arc192_d（D. Fraction Line、diff 2722） | stern-brocot（候補として挙げるだけ） | 題名だけで分数を扱うと分かる。Stern-Brocot 木と関係があるかも未確認 | 未確認 | stern-brocot |
| arc216_b（B. Range Mex Sum、diff 1935） | mex（候補のみ） | 題名から区間の mex の総和の型と思われる | 未確認 | mex |
| cf17_final_j | spanning-tree-advanced（diff 3822 で難しすぎる） | 木の上の距離と頂点の値で重みが決まる完全グラフの最小全域木（Borůvka 法か重心分解） | drken の keyence2019_e の記事に Tree MST も Borůvka 法で解けるという言及（問題そのものの解説は読んでいない。弱い） | spanning-tree-advanced |
| codequeen2023_final_e | monge の練習（「別解」扱い） | 列をいくつかの区間に区切り、各区間の最大 − 最小の和を最大にする。区間のコストが Monge（最大化の向き）で LARSCH により O(N log N) と記事にあるが、主な解法は Monge を使わない O(N) の DP | https://drken1215.hatenablog.com/entry/2023/09/04/214120 | monge |
| colopl2018_final_c | cht の練習 | 各位置 i で (i − j)^2 + a_j の最小値（直線の最小として CHT、傾きもクエリも単調）。調査 02-dp §5.1 の候補。確認問題の 1 問目はこの形を ID なしで使った | https://drken1215.hatenablog.com/entry/2018/09/18/014400 （未読）・ageprocpp の Qiita https://qiita.com/ageprocpp/items/3533b8f5678f9d4a5515 で例題として挙がることを確認 | cht |
| dwango2016qual_e（DWANGO2016-PRELIMS E. 花火、diff 3144 参考値） | slope-trick の力試し | 時刻順の目標位置に対し、単調な列を選んで距離の和を最小にする。累積 min と |x − p_i| の加算 | maspy「slope trick (2) 問題編」（同上・1 件だけ） | slope-trick |
| hhkb2020_f（F. Random Max、diff 2691） | continuous-probability の練習 | N 個の実数をそれぞれ区間 [L_i, R_i] から一様に選んだときの最大値の期待値（に定数を掛けた値）。端点で区切った区分ごとに数える／多項式を積分する（例題 abc226_h の K = 1 に近い） | https://kmjp.hatenablog.jp/entry/2020/10/10/1030 （座標圧縮した区分ごとの DP、O(N^3)）、https://scrapbox.io/nishio/HHKB2020 （未 AC のメモなので補助） | continuous-probability |
| joisc2008_fraction（fraction. 分数、diff なし） | stern-brocot の練習（解説が見つかれば） | Farey 数列の列挙に関わる問題と思われる。ap.py で実在を確認 | 未確認（第三者の解説が見つからない） | stern-brocot |
| math_and_algorithm_af（アルゴ数学 034. Nearest Points） | advanced-geometry（制約が小さく全組で解けるなら合わない） | 題名から最近点対と思われる | 未確認 | advanced-geometry |
| tkppc6-1 の P「Game on Colored Tree」 | partizan-games（ap.py で contest id と問題 ID を確かめてから） | 赤青 Hackenbush の木の値を求める | https://hitonanode.github.io/cplib-cpp/number/dyadic_rational.hpp.html （問題名と内容が挙がる） | partizan-games |
| tupc2022_m（M. Fractal Tree Isomorphism、diff なし） | tree-isomorphism | ap.py で見つかった | 未確認 | tree-isomorphism |
| utpc2012_12（UTPC2012 L. じょうしょうツリー、diff なし） | slope-trick#on-trees の代表 | 木の頂点の値を変えて単調にする最小コスト。木の上のマージ。今は on-trees の節で型だけ | maspy「slope trick (2) 問題編」（1 件だけ） | slope-trick |
| yahoo_procon2018_final_d（D. LCP(prefix,suffix)、diff なし） | 逆 Z の型（inverse-string-problems） | maspy の inverse_z_algorithm のコメントが参照する問題。ap.py で実在を確認 | 未確認 | suffix-automaton |
| KUPC2015 の WAAAAAAAAAAAAALL | slope-trick | maspy (2) の問題。ap.py で kupc2015_h が別の題（Bit Count）だったので問題 ID を確かめられていない | maspy (2) | slope-trick |
| aalc001_a〜aalc001_d（AAL Contest 001。2026-10-12、24 問） | library-design#verify の動作確認先・problem-sets の節 | Segment Tree・Lazy Segment Tree・Binary Search on a Segment Tree・Inversion Count など、セグ木の型ごとの問題集。ap.py で実在と題名を確認（difficulty なし）。problem-sets に aalc001 の節ができたら library-design#verify から案内する | 未確認（第三者の解説が見つからない。research/05-ds §7.5 も未確認） | library-design・problem-sets |
| game_a・game_d・game_e（組合せゲーム 24 題） | nim・grundy-number の練習の候補 | Nim・Parallel Nim・Restricted Nim 1（題名から） | 未確認 | problem-sets |
| ndpc2026_n・ndpc2026_p・ndpc2026_t（NDPC） | knapsack・lis・independent set の各ページの練習の候補 | Knapsack・LIS・Independent Set（題名から）。FPS 24 題も同じ扱い | 未確認 | problem-sets |

## 2. 台帳にある問題を別のページにも載せる候補

| 問題 ID（台帳の役割） | 役割の案（ページ） | 何を問うか・使い方 | 裏付けの URL | 出したページ |
| --- | --- | --- | --- | --- |
| abc121_d（bit-operations の practice） | xor の練習・stress-testing#experiment の練習 | A 以上 B 以下の整数の XOR。0〜n の XOR の表が 4 周期になる | https://drken1215.hatenablog.com/entry/2019/03/09/224100 （台帳の evidence） | xor・stress-testing |
| abc165_d（integer-division の practice） | stress-testing#experiment の練習 | 0 ≤ x ≤ N で ⌊Ax/B⌋ − A⌊x/B⌋ の最大。x を動かした表から周期 B と周期内の単調増加が見える | https://drken1215.hatenablog.com/entry/2020/05/02/225600 | stress-testing |
| abc187_f（subset-enumeration-dp の example） | chromatic-number の practice | 補グラフの彩色数（クリークへの分割の最小）を包除原理で | https://drken1215.hatenablog.com/entry/2021/01/02/224300 | chromatic-number（ledger にも記載） |
| abc201_e（tree-distance の practice） | xor の練習（性質を 2 つ組み合わせる） | 重み付きの木の全頂点の組のパスの XOR の和（根からの XOR と桁ごとの数え上げ） | https://blog.hamayanhamayan.com/entry/2021/05/15/235842 、https://kanpurin.hatenablog.com/entry/2021/05/15/224226 | xor |
| abc265_h（partizan-games の practice） | hadamard-transform の力試し | catalog の problems_note どおり手法の分類（タグ）だけの確認で、問いと解き方は第三者の解説で確かめていない（nyaannyaan の解説などで裏付けが要る） | タグだけ | hadamard-transform |
| abc355_g（alien-dp の practice） | monge の practice | 区間のコストが Monge なので monotone minima と Alien DP を組み合わせる | https://kmjp.hatenablog.jp/entry/2024/06/05/0900 | monge（ledger にも記載） |
| abc365_e（bitwise-independence の practice） | xor の練習（性質を 2 つ組み合わせる） | 長さ 2 以上の全区間の XOR の総和（累積 XOR と桁ごとの数え上げ） | https://oraclesqlpuzzle.ninja-web.net/kyoupro/05-atcoder-02-abc/kyoupro-abc365-e.html | xor |
| abc392_f（kth-element の practice・segment-tree-binary-search の example） | balanced-bst の practice（alternatives） | 空の列に i を先頭から P_i 番目の位置へ挿入していった後の列。implicit treap で split と merge を N 回行えば素直に解ける（逆順の処理と BIT の方が軽い） | https://yuulis.hatenablog.com/entry/ABC-392-F （逆順とセグ木の解。treap の第三者の解説はない。追加はメインの判断） | balanced-bst |
| abc394_g（bottleneck-path・small-to-large の practice） | merge-process-tree（載せていない） | 最大全域木の向きの併合過程の木で LCA の重みを取れば答えられるが、evidence の kmjp の記事は併合過程の木の解き方ではない | — | merge-process-tree |
| abc430_g（interval-set の practice） | segment-tree-beats（提案しない） | 検索結果の要約に「Segment Tree Beats で解ける」とあったが atcoder.jp の解説の要約で、kmjp の方針は値ごとの set と遅延セグ木 | — | segment-tree-beats |
| abc433_g（suffix-array の practice） | suffix-automaton の practice（または example） | SAM の状態の DAG 上の勝敗判定。SAM の第三者の解説は未確認（ikatakos は SA＋LCP）。提案者は「裏付けが取れるまで足さない方がよい」 | https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2025/1122_abc433 | suffix-automaton（ledger にも記載） |
| abc460_f（tree-diameter の practice ほか） | — | advanced-geometry は題名「Farthest Pair Query」から最遠点対のクエリの候補とし、問いを確かめていないとした。**台帳では木の白黒の頂点の距離の最大を答える問題で、幾何ではない**（候補から外してよい） | 台帳 | advanced-geometry |
| abc462_g（inclusion-exclusion の challenge） | fps-basics の練習 | approach に「FPS で項をまとめる」とある。ikatakos・kmjp の解説で FPS の演算が何かを確かめてから。online-convolution の frequency_evidence にもあるが、積の分割統治を使うかは未確認 | — | fps-basics・online-convolution |
| keyence2019_e（centroid-decomposition の challenge） | spanning-tree-advanced の example か practice | 番号の差と両端の値で重みが決まる完全グラフの最小全域木（Borůvka 法・候補の辺を絞るクラスカル法） | https://drken1215.hatenablog.com/entry/2019/01/15/081500 | spanning-tree-advanced（ledger にも記載） |
| typical90_e（matrix-power の challenge） | linear-recurrence-fast の練習（Bostan-Mori の別解） | 使える数字が限られた N 桁の B の倍数の個数。research/06 §5.6 に「練」。中身は読んでいないので確かめが要る | https://drken1215.hatenablog.com/entry/2021/10/08/231200 ・ https://github.com/E869120/kyopro_educational_90/blob/main/sol/005-03.cpp | linear-recurrence-fast |
| practice2（A〜L の 12 問） | library-design の verify 先 | 本文は problem-sets へのリンクだけにした（problem-sets#problem-sets-practice2 へ張り替え済み） | — | library-design |

## 3. AtCoder 以外のジャッジ（§15-5 を広げるなら。style.md §1）

| 問題 | 役割の案 | 内容 | 裏付け・規約 | 出したページ |
| --- | --- | --- | --- | --- |
| AOJ DPL_5_A〜L | twelvefold-way の練習（12 マスに対応） | drken の記事に 6 問（D・F 重複組合せ、G ベル数、I スターリング数、J・L 分割数）しか対応の明記がなく、残りは未確認（API の取得が失敗） | onlinejudge.u-aizu.ac.jp は noai 指定なし（2026-10-22） | twelvefold-way |
| yukicoder No.1069「電柱 / Pole (Hard)」 | k-shortest-paths | ei1333 の Yen の実装の verify に使われる。問題文は読んでおらず規約も未確認 | https://ei1333.github.io/library/graph/shortest-path/k-shortest-path.hpp | k-shortest-paths |
| CSES（tree-isomorphism の練習の小見出し） | tree-isomorphism | 小見出しを立てて置いた | — | tree-isomorphism |
| 洛谷 P3810 三维偏序 など | cdq-divide-and-conquer（台帳の対象外） | 中国の OJ の問題 | — | cdq-divide-and-conquer |

## 4. 探した結果「見つからなかった」報告（記録）

補充が要らない、または探しても候補がなかったページ。発展の概要の例題の目安（0〜2）は多くのページで満たしている。

- ABC で手法そのものが必須の問題が見つからなかった：balanced-bst（treap 必須）・cdq-divide-and-conquer・dynamic-tree・dynamic-dp（1 点更新つきの列の動的 DP）・fft-ntt（自作の NTT・任意 mod）・flow-lower-bounds（abc285_g のほか）・general-matching（abc412_g のほか）・k-shortest-paths・lgv-lemma（abc216_h のほか）・miller-rabin（Pollard's rho 必須）・partially-persistent-union-find・segment-tree-beats・segment-tree-graph（abc414_g のほか）・spanning-tree-advanced（Manhattan MST・最小有向全域木・第 2 最小全域木）・tree-isomorphism・young-tableaux（abc378_g のほか）・multiplicative-function（素数計数・杜教篩）・binomial-prefix-sum（abc235_g のほか。codeforces は noai で調べていない）・burnside-lemma（abc252_h は題名だけで裏付けなし）・rollback-union-find（abc302_h のほか）・chromatic-number（一般グラフの最大独立集合 N ≤ 40）・advanced-geometry（最近点対・回転キャリパー・半平面交差）・auxiliary-tree（圧縮木の上の木 DP を問う ABC）・modular-shortest-path（硬貨の組合せの同余最短路）・monge（Knuth-Yao・SMAWK・LARSCH を使う確認済みの ABC）
- 足りているので探していない：dilworth-path-cover・generating-function-counting・offline-dynamic-connectivity・online-convolution・parallel-binary-search・partizan-games・static-top-tree・steiner-tree・stirling-first・two-sat・wavelet-matrix・determinant（abc184_a は載せない）・alien-dp
- 横断ページ（guide・hub）で問題を持たない：advanced-ds-catalog・atcoder-system・cheatsheet・contest-strategy・cpp-environment・cpp-reverse-index・debugging-checklist・glossary・how-to-use・knowledge-map・method-comparison・notation・practice-method・problem-sets・reverse-index-constraints・reverse-index-signs・roadmap・term-index・thinking-checklist（入口に置くなら複数の問いを順に当てて解ける問題。各考察のページの例題は持ち主が別）・twelvefold-way・dp-speedup-overview・kth-and-median
- patterns の目安に収まり補充は要らない：divisors-and-multiples（表の代表が「—」の行が多いが、他ページの例題を label で書いてよいかの決まりがあれば補充しやすい。style.md §1）・grid・interval・operation-sequence・permutation・subsequence-and-substring（異なる部分列・部分文字列の数は各ページの例題なので重ねない）・xor・graph-modeling
- dp-speedup-overview の早見表の「右へ動くだけの窓の min・max」の行は例題の列が「—」。dp-segment-tree#dp-sliding-window か monotonic-stack#dp-transition に例題がつけば埋まる
- mex の window-mex の節（長さ M の窓の mex の最大値・区間の mex のクエリの先読み）は台帳に確認済みの問題がない
- modular-shortest-path の #congruence の型（作れる数の個数・作れない最大の数）の AtCoder の問題が台帳にない
- permutation の逆置換の節の「値 1〜k の位置が連続しているか」の型は台帳で探していない
