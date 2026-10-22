# counting-fix-order の問題の補充（工程9）

- ページ：docs/comb/counting-fix-order.md（レベル 水）
- 今の問題：例題 abc133_e（1505）・練習 abc151_e（1344）・力試し abc160_f（2048）。練習は 1 問
- 補充後の練習：下の 3 問を足すと合わせて 4 問（易しい順に abc209_c・arc116_b・abc151_e・abc216_f）。2 問だけ足すなら、帯に近い abc216_f と、節 sort-and-fix の型そのものの arc116_b を優先する

## 調べた範囲

- (1) 候補の一覧：b1/summary/candidates.md と b1/counting-fix-order.md の「問題の補充の候補」に abc209_c がある。b3・b5 の candidates.md にこのページの記述はない
- (2) 台帳：data/problems.yaml で pages に counting-fix-order を持つのは abc133_e・abc151_e・abc160_f・abc209_c。本文にないのは abc209_c（role: practice、確認済み）だけ
- (3) 第三者の解説：ikatakos.com の ABC216・ARC116 の記事を開いた。Web 検索（「N!/部分木のサイズの積」「相対順序 固定 N!/K!」など 5 回）では、n!/k! や木の上の順番を主役にする水〜青の ABC は見つからなかった
- 新しいドメインは使っていない（ikatakos.com・qiita.com は付録 B にある）

## 候補

### abc216_f（F. Max Sum Counting、diff 1541）

- 役割：practice
- 要約：添字の集合のうち、選んだ要素の A の最大値が B の和以上になるものの個数を求める問題である。
- 方針の要点：A の昇順に並べて最大になる要素を固定すると、ほかに選べるのはそれより前の要素だけになり、B の和が A_i − B_i 以下になる選び方をナップサックの数え上げ DP で数えればよい（節 sort-and-fix の「ソートで最大の条件を位置の条件に変える」）。
- 裏付け：https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2021/0829_abc216
- 備考：台帳では subset-sum・exchange-argument-dp の practice。このページには pages への role: practice の追加の提案になる。checked は null のまま（今回 ikatakos の記事で問いと方針を確かめた）

### arc116_b（B. Products of Min-Max、diff 816）

- 役割：practice
- 要約：整数列の空でない部分列すべてについて、最大値と最小値の積を足し合わせた値を求める問題である。
- 方針の要点：ソートして最小 a_i と最大 a_j を固定すると間の j − i − 1 個は自由なので寄与は a_i a_j 2^{j−i−1} になり、i ごとに係数をまとめて O(N log N) で求める（節 sort-and-fix）。
- 裏付け：https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2021/0328_arc116
- 備考：台帳に未登録（新規）。帯より下だが、最大・最小をソートで固定する型の易しい練習として置ける。2 つ目の裏付けは Web 検索 2 回で見つからなかった

### abc209_c（C. Not Equal、diff 285）

- 役割：practice
- 要約：各 i について 1 以上 C_i 以下の整数を、すべて異なるように選ぶ方法の数を求める問題である。
- 方針の要点：C を昇順に並べて小さい順に決めると、i 番目（0-indexed）の選択肢が前の選び方によらず C_i − i 個になり、積の法則で掛け合わせればよい（節 bfs-order の最初の例）。
- 裏付け：https://qiita.com/AKpirion/items/21b1aead96fec77d67ef
- 備考：台帳で既に role: practice（確認済み、checked 2026-10-21）だが本文の練習にない。帯よりかなり下なので、練習の先頭に置くか、本文の例で触れるだけにするかはメインの判断。足すときは要約に解き方（並べ替え）を入れない（b1 の報告どおり）

## 見つからなかったもの

- 節 relative-order（n!/k!）と節 tree-order（n!/Π 部分木の大きさ）を主役にする水〜黄の ABC は、今回の検索では見つからなかった。力試しは abc160_f のままでよい
