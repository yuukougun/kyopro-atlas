# time-dependent-dijkstra の問題の補充（b6・工程9）

- ページ：docs/graph/time-dependent-dijkstra.md（レベル 水）。今の練習は abc204_e（diff 1710）の 1 問、例題は abc192_e・abc342_e
- 探したところ：(1) b1 の報告 planning/batches/b1/time-dependent-dijkstra.md の「問題の補充の候補」に abc319_e と、miscalc の記事が挙げる abc170_f・arc150_c（b1 summary/candidates.md も同じ。b3・b5 の candidates.md には time-dependent-dijkstra の候補なし）。(2) data/problems.yaml で pages に time-dependent-dijkstra を持つのは abc192_e・abc204_e・abc342_e の 3 問で、どれも本文にある（本文にない問題はなし）。(3) ap.py の題名検索（Train・Bus・Rush・Station・Express・Travel・Elevator・Wait など、diff 900〜2300）で abc084_c を新たに見つけ、第三者の解説で確かめた
- 問題の実在・題名・difficulty は `python3 tools/ap.py show` で確かめた（2026-10-22）
- この作業では WebSearch の回数の上限に達したため、検索エンジンでの探索はできなかった。解説は付録 B のブログの直接の URL とブログ内検索で探した
- 候補 3 問（practice 2・challenge 1）を足すと練習は合わせて 3 問、力試しは 1 問になる

## 候補

### abc319_e（台帳になし）

- 問題ID：abc319_e
- 題名：E. Bus Stops
- difficulty：1353（水）
- 役割：practice
- 要約：家からバス停 1 まで X、バス停 i から i+1 へは P_i（≤ 8）の倍数の時刻に出るバスで T_i、最後のバス停から会社まで Y かかるとき、質問ごとの出発時刻に対して会社へ最も早く着く時刻を答える問題である。
- 方針の要点：各停留所で「次の P_i の倍数まで待つ」遷移 ⌈t/P_i⌉·P_i + T_i を順にたどり、待ち方が周期 lcm(1..8) = 840 で繰り返すので出発時刻 mod 840 ごとの到着時刻を前計算して各質問に O(1) で答える。
- 裏付け：
    - https://programming-hiroba.com/abc319-e/ （周期 840 の前計算、(a + P − 1)/P·P の切り上げ、答えが (qt/840)·840 + f(qt mod 840) であることを確かめた）
    - https://merom686.hatenablog.com/entry/2023/09/10/022053 （840 の周期で前計算し、質問は mod 840 で引くこと。b1 では未読だったので今回読んだ）
- 注意：分岐のない一本道なのでヒープは要らない。[次の出発時刻まで待つ遷移](#wait)の切り上げの練習としては良いが、ダイクストラ法そのものは使わない。periodicity のページが持ち主になりそうなら、こちらは参照だけにする（b1 の報告と同じ判断）
- 台帳への追加の提案：pages に {id: time-dependent-dijkstra, role: practice}（periodicity にも置くなら role は持ち主側で決める）

### abc084_c（新規。台帳になし）

- 問題ID：abc084_c
- 題名：C. Special Trains
- difficulty：908（緑。帯では基礎）
- 役割：practice（帯より下だが、wait の節の「最初の便 S_i より前なら S_i まで待ち、以降は F_i の倍数まで待つ」をそのまま書く入門の練習として置く。数を絞るなら外してよい）
- 要約：一直線に並ぶ N 駅で、駅 i から i+1 へは時刻 S_i から F_i ごとに出る列車で C_i かかるとき、各駅から出発して駅 N に最も早く着く時刻を求める問題である。
- 方針の要点：各始点から駅を順にたどり、現在時刻 t が S_i 未満なら S_i、そうでなければ ⌈t/F_i⌉·F_i を出発時刻として C_i を足す（N ≤ 500 なので始点ごとのシミュレーションで間に合う）。
- 裏付け：
    - https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2017/1230_abc084 （始点ごとのシミュレーション、S_i 前なら S_i まで待つ・以降は F_i の倍数への切り上げ、N ≤ 500 を確かめた）
- 注意：abc319_e と同じく一本道でヒープは要らない。本文の表（便の出発時刻ごとの next_e(t)）の「最初の便が S、以降 F ごと」の行に当たる

### arc150_c（台帳になし）

- 問題ID：arc150_c
- 題名：C. Path and Subsequence
- difficulty：1802（青）
- 役割：challenge（帯の上で、時刻ではない量に到着時刻の考え方を当てはめる応用なので）
- 要約：各頂点に値 A_v がある連結な無向グラフと数列 B（長さ K）について、頂点 1 から N へのどの単純パスでも、通った頂点の A の列が B を部分列に含むかを判定する問題である。
- 方針の要点：各頂点で「B を先頭から貪欲に何個まで一致させたか」の最小値を距離とし、頂点 v に入ると一致数 x が x + [A_v = B_{x+1}] になる遷移（x 以上で x について単調、つまりこのページの 2 条件を満たす到着関数）でダイクストラ法（または 01-BFS）を回し、頂点 N の値が K に届けば Yes とする。
- 裏付け：
    - https://miscalc.hatenablog.com/entry/2022/10/10/115348 （辺のコストが今のコストの関数 f(x) でも、f が単調非減少で x ≤ f(x) ならダイクストラ法が使えるという記事。適用例として arc150_c を挙げている。中身は畳まれていて読めなかった）
    - https://merom686.hatenablog.com/entry/2022/10/10/013513 （各頂点で一致数が最小となる最悪のパスをダイクストラ法で求め、コストが今の一致数で変わること、単純でないパスは無視してよいこと、値が K に届けば Yes であることを確かめた）
- 注意：遷移が x 以上で単調であることは、上の式から自分で確かめた（x < x' なら x + 1 ≤ x' なので f(x) ≤ x + 1 ≤ x' ≤ f(x')）。merom686 の記事はこの性質を明示していないので、本文で使うなら式から示す。本文の fifo の節の「時刻」を一般の量に読み替える例として「使い分け」や補足に置く手もある

## 除いたもの

- abc192_e・abc342_e（例題）・abc204_e（練習）：本文に既にある
- abc170_f（F. Pond Skater、diff 1968）：miscalc の記事は「この形に落とすまでの考察がちょっと大変」とだけ書き、到着関数を示していない。ふつうは状態を頂点にするダイクストラや BFS の問題として扱われる（research/03-graph.md でも BFS の分類）ので、grid-graph・extended-dijkstra の持ち主の方が自然と判断した
- abc368_e（E. Train Delay、diff 2140）：題名は列車の時刻だが、第三者の解説を開いて確かめておらず、このページの手法（各頂点で最も早い時刻を持つダイクストラ法）で解く問題か分からないので候補にしない
- TKPPC4-1 H「don't be late」：miscalc の記事は abc192_e とほぼ同じとしているが、AtCoder Problems での ID と difficulty を確かめていないので挙げない
- 題名検索で出たほかの問題（abc073_d・abc143_e・abc197_e・abc210_d・aising2020_e・arc104_c など）：題名に旅行・列車・エレベーターが入るだけで、時刻で変わる辺の問題ではない（台帳・既存のページの担当から判断。解説は開いていない）

## 本文に足すときのメモ

- 練習の並びは易しい順に abc084_c（908）→ abc319_e（1353）→ abc204_e（1710）。前の 2 問は一本道で wait の節の切り上げだけを練習し、グラフ上のダイクストラは例題と abc204_e で扱う、という分担になる
- arc150_c は力試しとして、fifo の節の 2 条件（時刻が戻らない・FIFO 性）を時刻以外の量で確かめる例になる
