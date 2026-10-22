# divide-and-conquer：問題の補充（工程9）

- ページ：docs/basics/divide-and-conquer.md（レベル 黄）
- 今の問題：例題 arc189_d・abc426_g、練習 chokudai_S001_j（1 問）、力試し abc478_g
- difficulty は 2026-10-22 に `python3 tools/ap.py show` で確かめた。atcoder.jp・codeforces.com は開いていない

## 結論

練習に足せる候補は arc075_c の 1 問だけ見つかった。足すと練習は 2 問になり、目標（2〜4 問）の下限に届く。そのほかに見つかったのは 2600 以上の問題で、力試しの候補とした。中央で分ける・最大値の位置で分ける手法そのものを使い、difficulty が 1200〜2399 の AtCoder の問題で、第三者の解説で裏付けがとれるものは、ほかに見つからなかった。

## 候補

| 問題 ID | 題名 | diff | 役割 | 要約 | 方針の要点 | 裏付け |
| --- | --- | --- | --- | --- | --- | --- |
| arc075_c | E. Meaningful Mean | 1979 | practice | 平均が K 以上になる連続部分列の個数を求める。 | 各項から K を引いた累積和 $S$ で $i < j$ かつ $S_i \le S_j$ の組を数える問題になり、これは等号の向きが違う転倒数なので、節 crossing のマージソートで $O(N \log N)$ で数えられる。 | https://drken1215.hatenablog.com/entry/2020/04/24/015400 ・ https://kmjp.hatenablog.jp/entry/2017/06/03/1030 |
| abc282_h | Ex. Min + Sum | 2621 | challenge | 2 つの列 A・B について、区間の A の最小値と区間の B の和の合計が S 以下になる区間の個数を求める。 | 区間の最小値の位置で分け、左右の短い方の端点を全部試し、長い方の端点を B の累積和の二分探索で数える（節 split-at-max の説明そのままで $O(N \log^2 N)$）。 | https://kmjp.hatenablog.jp/entry/2022/12/18/0930 |
| keyence2019_e | E. Connecting Cities | 2623 | challenge | 一列に並ぶ都市を結ぶ完全グラフで、辺の重みが番号の差と両端の値で決まるときの最小全域木の重みを求める。 | 番号で半分に分け、中央をまたぐ辺は「各点から反対側の代表 1 点への辺」だけを残す（ほかの辺は閉路の最大の辺になり不要）と、候補は $O(N \log N)$ 本になり、Kruskal で解ける。 | https://drken1215.hatenablog.com/entry/2019/01/15/081500 |
| abc223_h | H. Xor Query | 2771 | challenge | 区間の数から選んだものの XOR で、指定の値を作れるかを多数のクエリについて答える。 | 節 range-knapsack と同じく中央をまたぐクエリを、中央から左右へ伸ばした XOR 基底を合わせて答える（基底への 1 個の追加は $O(\log A)$）。 | https://maspypy.com/%E5%88%86%E5%89%B2%E7%B5%B1%E6%B2%BB%E3%81%AB%E3%82%88%E3%82%8B%E9%9D%99%E7%9A%84%E5%88%97%E3%81%AE%E5%8C%BA%E9%96%93%E7%A9%8D%E3%82%AF%E3%82%A8%E3%83%AA |

### 各候補の注意

- **arc075_c**：台帳では inversion-number の practice（approach は BIT）。2 つの解説はどちらも BIT で数えており、マージソートには触れていない。drken 氏の記事が「ほとんど転倒数と一緒」と述べ、kmjp 氏の記事が $S_i \le S_j$ の組の数え上げに帰着させているので、このページの crossing の数え方（マージソートで $i < j$ の組を数える）がそのまま使える、という根拠である。台帳には pages に `{id: divide-and-conquer, role: practice}` を足し、alternatives に「累積和の列でマージソートにより $S_i \le S_j$ の組を数える」を足す案になる。帯は青（1979）で黄に近い
- **abc282_h**：台帳に既にあり（role challenge、本文にない）。kmjp 氏の記事は A の小さい順に位置を set に入れて最小値になる範囲を求める書き方で、明示的な再帰ではないが、「最小値になる範囲で短い側を全部試し、長い側を二分探索」という計算の中身は節 split-at-max と同じである。b3 の報告でも力試しの候補とした
- **keyence2019_e**：b3 の報告で挙げた候補（台帳では centroid-decomposition の challenge）。drken 氏の記事の解法 1 が中央で分ける分割統治である
- **abc223_h**：台帳にない。maspypy 氏の記事が「分割統治による静的列の区間積クエリ」の応用例として挙げている。題名の要約は記事の記述（区間のベクトルの張る空間）からの言い換えで、問題文は読んでいないので、台帳に足す前に第三者の解説でもう 1 つ確かめたい
- 3 つの力試しの候補はどれも 2600 以上で黄の帯から離れる。力試しは既に abc478_g（2582）があるので、足すなら abc282_h（節 split-at-max の唯一の演習になる）を優先する

## 見送ったもの

- **abc451_g**（2221、台帳でこのページの challenge、本文にない）：ikatakos 氏の記録では、値をビットごとに 2 つの組に分けて再帰する「分割統治」で XOR が K 以下の組を数えている。区間を分ける形ではなく Binary Trie の数え方と同じで、kmjp 氏の記事は Trie で解いている。このページの節には対応しないので、台帳の pages から divide-and-conquer を外し、xor-basis（と binary-trie）に任せる案を提案する。根拠：https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2026/0328_abc451 ・ https://kmjp.hatenablog.jp/entry/2026/03/28/0930
- **agc005_b**（1828）：すべての区間の最小値の和。最小値の位置で分ければ解けるが、確かめた解説（https://drken1215.hatenablog.com/entry/2019/04/04/210200 ）は単調スタックと set の方法だけで、分割統治の裏付けがない。monotonic-stack の練習のままにする
- **arc067_d**（2729）：分割統治で最適な区間を求める解法が知られるが、単調性を使う分割統治 DP（monge#monotone-minima の範囲）なので、このページの練習にはしない
- drken 氏の分類「分割統治法」（https://drken1215.hatenablog.com/archive/category/分割統治法 ）の AtCoder の問題は、上のもののほかは分割統治 FFT など他の分野（abc352_g・abc318_h・abc281_h・abc213_h・arc115_d・abl_f・agc001_f）で、このページの練習にはならない

## 使った出典

- https://drken1215.hatenablog.com/entry/2020/04/24/015400 （arc075_c の帰着）
- https://kmjp.hatenablog.jp/entry/2017/06/03/1030 （arc075_c の帰着）
- https://kmjp.hatenablog.jp/entry/2022/12/18/0930 （abc282_h）
- https://drken1215.hatenablog.com/entry/2019/01/15/081500 （keyence2019_e）
- maspypy.com「分割統治による静的列の区間積クエリ」（abc223_h）
- ikatakos.com・kmjp の abc451_g の記事（見送りの根拠）
- どのドメインも付録 B にある。新しく noai を確かめたドメインはない
