# inclusion-exclusion-dp の問題の補充（b6・工程9）

- 対象：docs/comb/inclusion-exclusion-dp.md（レベル 黄）。今の練習は arc115_e の 1 問。例題 dp_y・abc309_g、力試し abc214_g・arc101_c
- 確かめ方：実在・題名・difficulty は `python3 tools/ap.py show`（2026-10-22）。問いと解き方は第三者の解説で確かめた（どのドメインも付録 B にある）。atcoder.jp・codeforces.com は開いていない
- 結果：練習に足せるのは 1 問（abc462_g）。これで練習は 2 問になる。力試しの候補は 4 問
- 黄の帯（2000〜2399）で、「最初に踏む障害物」と「等しい区間にまとめる」の形の問題は見つからなかった。見つかった同じ形の問題はどれも帯から遠い（abc357_g 3159・arc118_e 3092・abc297_h 2855）ので、候補にしていない

## 候補

| 問題 ID | 題名 | difficulty | 役割 | 要約 | 方針の要点 | 裏付けの URL |
| --- | --- | --- | --- | --- | --- | --- |
| abc462_g | G. Completely Wrong | 2232 | practice | 色の付いた N 個の玉を一様に無作為な順に取り出すとき、どの i 番目に取り出す玉も指定の色 G_i と違う確率を mod 998244353 で求める。 | 色 c が玉に x 個、指定に y 個あるとき、一致を i 組指定する方法は C(x,i)·C(y,i)·i! である。色ごとの多項式を掛けて r_k を作り、Σ(−1)^k r_k (N−k)! / N! を取る（count-violations の形。N が大きいので積は NTT の分割統治で行う） | https://kmjp.hatenablog.jp/entry/2026/06/13/0900 ・ https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2026/0613_abc462 |
| arc121_e | E. Directed Tree | 2645 | challenge | 頂点 1 を根とする N 頂点の根付き木で、各 i について a_i から辺を 1 本以上たどって i に着かない順列 a の数を数える。 | 条件を破る頂点を k 個指定する包除にし、部分木ごとに「指定した個数」を状態に持つ木 DP（二乗の木 DP で O(N^2)）で r_k を求め、Σ(−1)^k r_k (N−k)! を取る | https://kmjp.hatenablog.jp/entry/2021/06/20/0930 |
| abl_f | F. Heights and Pairs | 2545 | challenge | 身長の決まった 2N 人を N 組の 2 人組に分けるとき、どの組も 2 人の身長が違う分け方の数を数える。 | 同じ身長の組を k 個指定する包除にする。身長ごとに「同じ身長の組を j 個作る方法」C(a,2j)(2j−1)!! を多項式にして掛け（NTT を短い順に）、Σ(−1)^k r_k (2(N−k)−1)!! を取る | https://betrue12.hateblo.jp/entry/2020/09/27/043205 ・ https://scrapbox.io/nishio/abl_f |
| abc236_h | Ex. Distinct Multiples | 2898 | challenge | 各 i で D_i の倍数かつ M 以下の正整数 A_i を選び、すべてが異なる列の数を数える（N ≤ 16）。 | 等しいと指定する組の集合で包除し、成分ごとに「値の選び方 ⌊M/lcm⌋」と「完全グラフの連結な辺集合の符号付きの和 (−1)^{n−1}(n−1)!」を掛け、集合の分割を bit DP（O(3^N)）でまとめる | https://kmjp.hatenablog.jp/entry/2022/01/24/1100 ・ https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2022/0123_abc236 |
| agc005_d | D. ~K Perm Counting | 2943 | challenge | すべての i で \|a_i − i\| ≠ K となる 1〜N の順列の数を数える（N ≤ 2000）。 | 禁止のマスを mod 2K で分けると鎖になり、鎖を並べてつないだ列で「直前の辺を選んだか」と選んだ辺の数を状態に持つ DP で r_k を求め、Σ(−1)^k r_k (N−k)! を取る | https://drken1215.hatenablog.com/entry/2018/07/10/134500 ・ https://ei1333.github.io/luzhiled/snippets/memo/inclusion-exclusion.html（b3 の報告。今回は開いていない） |

## 補足

- abc462_g は台帳で inclusion-exclusion の challenge になっている。pages に `{id: inclusion-exclusion-dp, role: practice}` を足す提案である。b5 の候補一覧では fps-basics の練習の候補にも挙がっている。色ごとの積は ACL の convolution で書けるが、分割統治で掛ける必要があるので、練習の方針にそのことを一言書くのがよい
- 力試しは今 2 問ある。足すなら、本文の節に一番近い arc121_e（符号付きの木 DP の節と count-violations の節の両方を使う）を 1 問目に勧める。abl_f は abc462_g と同じ形で、NTT が要る
- arc121_e の N の上限は解説に書かれていない（kmjp のコードの配列の大きさから 2000 程度と推定）。第三者の解説は kmjp の 1 つだけで、2 つ目は見つからなかった
- 見たが採らなかった問題
  - cpsco2019_s3_f（Flexible Permutation）：difficulty がない。drken の記事では挿入 DP などが主で、包除は「別解がある」と触れるだけ
  - tenka1_2019_d（Three Colors、2237）：全体から悪いものを引くナップサック DP で、包除の補正は 1 項だけ。このページの手法の練習には向かない
  - abc242_f（2268）・abc172_e（1880）：包除の和を直接計算する問題で、DP は要らない（inclusion-exclusion の範囲）
  - abc213_g（2663）：連結な部分グラフを「頂点 1 を含む成分」で分けて全体から引く bit DP。考え方は first-obstacle に近いが、台帳では別のページに載っている
- 調べ方の記録：drken1215 の「包除原理」「包除原理:DP」のカテゴリー、kanpurin の典型問題メモの包除原理の節、はまやんの包除原理問題まとめ、kmjp のブログの「包除原理」の検索結果（AtCoder の問題を全部見た）。WebSearch はこのセッションの上限に達したので、そこで探すのをやめた
