# floor-quotient-enum の問題の補充（b6・工程9）

- ページ：docs/math/floor-quotient-enum.md（レベル 水）。今の練習は abc296_d（diff 999）の 1 問。例題は abc230_e・arc160_b、力試しは arc060_b
- 探したところ：(1) b1 の報告 planning/batches/b1/floor-quotient-enum.md と b1 summary/candidates.md に abc414_e（b3・b5 の candidates.md には floor-quotient-enum の候補なし。viz の報告は図の件だけ）。(2) data/problems.yaml で pages に floor-quotient-enum を持つ問題は abc230_e・abc296_d・arc060_b・arc160_b の 4 問で、どれも本文にある（本文にない問題はなし）。(3) 第三者の解説で abc172_d・abc132_f を確かめた。abc448_e（E. Simple Division）は題名から調べたが、ikatakos の解説では筆算の余りのダブリングで、このページの手法ではないので外した
- 問題の実在・題名・difficulty は `python3 tools/ap.py show` で確かめた（2026-10-22）
- 練習の候補 2 問を足すと練習は合わせて 3 問になる。ほかに力試しの候補が 1 問
- この作業の途中で Web 検索の上限に達したため、検索での新しい候補探しは十分にできていない。候補は ap.py の題名の検索と、付録 B のサイトの URL を直接開いて確かめた

## 候補

### abc414_e（台帳になし。b1 の報告で提案済み）

- 問題ID：abc414_e
- 題名：E. Count A%B=C
- difficulty：1296（水）
- 役割：practice
- 要約：1 以上 N 以下の互いに異なる整数の組 (a, b, c) で、a を b で割った余りが c になるものの個数を 998244353 で割った余りで求める（3 ≤ N ≤ 10^12）。
- 方針の要点：b を固定して c を数えると答えは Σ_{b=1}^{N} (N + 1 − b − ⌊N/b⌋) にまとまり、残る Σ⌊N/b⌋ を商が同じ区間ごと（または √N で分けた 2Σ_{i≤s}⌊N/i⌋ − s^2）で O(√N) に求める。
- 裏付け：
    - https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2025/0712_abc414 （制約 3 ≤ N ≤ 10^12、上の式変形、2Σ⌊N/i⌋ − s^2 の実装。b1 で未確認だった N の上限はここで確かめた）
    - https://zenn.dev/nakst_hide/articles/f5b3e3a3473e9d （a > b の組 N(N−1)/2 から a が b の倍数の組 Σ⌊N/b⌋ を引き、商が同じ区間 `to = N / (N / from) + 1` でまとめる）
- 台帳への追加の提案：pages に {id: floor-quotient-enum, role: practice}。2025-07 の ABC なので、b1 の報告にある「abc319 以降の根拠がない」も解消できる

### abc172_d（台帳にあり。pages は sigma-manipulation の example だけ）

- 問題ID：abc172_d
- 題名：D. Sum of Divisors
- difficulty：963（基礎。水の帯の下だが近い）
- 役割：practice
- 要約：x の約数の個数を f(x) とするとき、Σ_{x=1}^{N} x·f(x) を求める（N ≤ 10^7）。
- 方針の要点：約数 a ごとに倍数の和 a·k(k+1)/2（k = ⌊N/a⌋）を足す形に直すと、#block-end の「f が i にもよる場合」の g(i) = i の形になり、k が同じ a の区間を等差数列の和でまとめれば O(√N) になる（N ≤ 10^7 なので O(N) の全探索でも通る点は練習のヒントに書く）。
- 裏付け：
    - https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2020/0627_abc172 （制約 N ≤ 10^7、O(N) の解法と、倍数の個数が同じ a をまとめ √N で切り替える O(√N) の解法の両方を確かめた）
- 台帳への追加の提案：pages に {id: floor-quotient-enum, role: practice} を足す（sigma-manipulation の example はそのまま）

### abc132_f（新規。台帳になし）

- 問題ID：abc132_f
- 題名：F. Small Products
- difficulty：2143（黄）
- 役割：challenge（ページは水で、帯から 2 つ上なので力試し）
- 要約：隣り合う 2 数の積がどれも N 以下になる、正の整数 K 個の列の個数を 10^9+7 で割った余りで求める（N ≤ 10^9、K ≤ 100）。
- 方針の要点：√N を超える数どうしは隣り合えないので、右端が √N 以下の数のときは値ごとに、√N を超える数のときは隣に置ける小さい数の範囲（⌊N/x⌋ で決まる）ごとにまとめて DP し、累積和で遷移して O(K√N) にする（#split-at-sqrt の型）。
- 裏付け：
    - https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2019/0629_abc132 （制約、√N を境に DP を 2 つに分ける方針、O(K√N) を確かめた）
    - 2 つ目の解説は、検索の上限のため見つけられなかった（kmjp・oraclesqlpuzzle の URL を推測して開いたが 404）
- 台帳への追加の提案：pages に {id: floor-quotient-enum, role: challenge}。力試しは今 arc060_b の 1 問なので、足すと 2 問になる

## 未解決の点

- abc132_f の裏付けが 1 つだけ。台帳に入れる前にもう 1 つ解説で確かめたい
- Web 検索の上限で、商の値を DP の添字にする型（素数の個数など）の水〜青の AtCoder の問題は探せていない
