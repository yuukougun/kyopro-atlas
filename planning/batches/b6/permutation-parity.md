# permutation-parity：問題の補充（工程9・b6）

ページ：docs/comb/permutation-parity.md（レベル 青）。今の問題は例題 abc470_f（diff 1604）、練習 abc296_f（diff 1811）の 1 問。

## 候補

| 問題 ID | 題名 | difficulty | 役割 | 要約 | 方針の要点 | 裏付けの URL |
| --- | --- | --- | --- | --- | --- | --- |
| arc136_b | B. Triple Shift | 1358（水） | practice | 長さ N の列 A で隣り合う 3 要素を巡回させる操作を繰り返し、列 B に一致させられるかを判定する問題である。 | 値の多重集合が違えば No、同じ値が 2 つ以上あれば Yes、値がすべて異なれば A と B の転倒数の偶奇が一致するときだけ Yes とする（3 要素の巡回は偶置換）。 | https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2022/0227_arc136 、https://note.com/syamashi/n/nb491ffdf0ca3 |

- ap.py で実在・題名・difficulty を確かめた（OK arc136_b B. Triple Shift diff=1358 水）。台帳 data/problems.yaml には未登録。ページの例題・練習・力試しにはない（参考の節に syamashi の記事だけがある）。
- ikatakos の記事（b2 では 503 で読めなかったが、今回は読めた）の解法の節で、(1) 多重集合の一致が必要、(2) 同じ値が 1 つでもあれば必ず一致させられる、(3) 操作で転倒数の偶奇が変わらず、偶奇が一致すれば Yes（O(N log N)）、を確かめた。syamashi の記事はページの参考に既にある（b2 で確認済み）。
- 本文との対応：#three-cycle の応用の型「隣り合う 3 か所だけを巡回させる」と #duplicates の判定手順そのもの。入れば、その箇条から練習へリンクできる。difficulty は水で青の帯より下だが、内容はこのページの型そのものなので練習に向く（易しい側の練習）。
- 入れると練習は abc296_f と合わせて 2 問になり、目標（2〜4 問）の下限に届く。

## 探したが採らなかったもの

- abc244_d（D. Swap Hats、diff 165）：3 人の帽子の色を、2 人の交換をちょうど 10^18 回行った後に指定の並びにできるかを問う。目標が偶置換かで決まり、このページの #exactly-k の最も易しい形である（裏付け：https://zenn.dev/koboshi/articles/e60e2737854c1e の例題の節）。帯から大きく下に離れ、力試しにもならないので採らない。確認問題のような易しい入口として使うなら別に検討してほしい。
- arc147_b（B. Swap to Sort、diff 1167）：箱星の記事の演習問題に挙がっているが、添字の偶奇（奇数番目・偶数番目）の問題で、置換の符号は使わないと判断して採らない（kazun-kyopro の記事は検索結果の題名だけで、本文は読んでいない）。
- abc190_f（F. Shift and Inversions、diff 1321）：箱星の記事の演習問題にあるが、転倒数の値そのものを巡回シフトごとに求める問題で、偶奇は鍵ではない（inversion-number 向き）。
- chokudai_S001_l（L. N回スワップ、difficulty なし）：箱星の記事の演習問題にある。difficulty がなく、内容を第三者の解説で確かめていないので候補にしない。
- ap.py の題名検索（Swap・Shift・Puzzle・Cyclic・Rotation・Permutation・Exchange、diff 1300〜2400）で見た arc223_b・arc203_b・arc225_d などは、検索で見つかった解説（arc223_b は中国語の索引ページ、arc203_b と arc225_d は解説が見つからない）では置換の偶奇を使うと確かめられなかった。arc223_b は和が K の倍数の隣接 swap で作れる列の数を、剰余の組ごとの区間で多項係数・二項係数の積として数える問題で、偶奇は使わない。
- Web 検索（「置換の偶奇」「偶置換」「転倒数の偶奇」と AtCoder・kmjp・drken・ikatakos の組合せ）では、abc319 以降でこのページの手法を直接使う ABC・ARC は、例題の abc470_f と練習の abc296_f のほかに見つからなかった。

## 使ったドメイン

ikatakos.com・zenn.dev（付録 B にある）。note.com の syamashi の記事は b2 で参考に入れたもの（付録 B の note.com の確かめた記事一覧には載っていないので、メインで利用条件を確かめてほしい）。atcoder.jp・codeforces.com は開いていない。
