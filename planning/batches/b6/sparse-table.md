# sparse-table の問題の補充（工程9・b6）

- ページ：docs/ds/sparse-table.md（レベル 青）
- 今の問題：例題 abc282_f のみ。練習 0 問（`## 練習問題` の節がない）、力試し 0 問
- 結論：練習の候補 2 問を確かめた（推すのは abc254_f の 1 問。abc125_c は帯より下で、累積でも解ける）。目標の「練習 2〜4 問」には、abc125_c を入れてようやく 2 問になる。ほかに第三者の解説で Sparse Table を使うと確かめられた AtCoder の問題は見つからなかった。difficulty・題名はすべて `python3 tools/ap.py show` で確かめた（2026-10-22）

## 練習の候補（practice）

### abc254_f　F. Rectangle GCD（diff 1764・青）

- 台帳：登録済み（gcd-properties:example・sparse-table:practice）。台帳には practice があるのに、本文に練習の節がないので載っていない。`## 練習問題 {#practice}` を作って載せる
- 要約：(i, j) 成分が A_i + B_j の N×N の表について、指定された長方形の中の値すべての最大公約数を、多数のクエリに答える。
- 方針の要点：gcd は隣り合う項の差に置き換えても変わらないので、長方形の gcd は左上の値と A・B の隣接差の区間 gcd 2 つとの gcd になり、差の列は変わらないので Sparse Table（Disjoint Sparse Table でもよい）で区間 gcd を引く。
- このページとの対応：#what-it-does の「区間の gcd」の型そのもの。gcd は冪等なので普通の Sparse Table でよい
- 裏付け：
  - https://kazun-kyopro.hatenablog.com/entry/ABC/254/F （隣接差への帰着。区間 gcd はセグメント木か Disjoint Sparse Table で引くと書く。普通の Sparse Table の語は出ない。今回開き直して確かめた）
  - 2 つ目は見つからなかった（ikatakos の abc254 のページは未作成だった）

### abc125_c　C. GCD on Blackboard（diff 1197・基礎の上端）

- 台帳：登録済み（prefix-sum:practice・gcd-lcm:practice）。pages に sparse-table:practice を足す提案。ただし帯（青）から大きく下なので、入れるかはメインの判断
- 要約：N 個の整数のうち 1 つを好きな整数に書き換えたとき、全体の最大公約数としてありうる最大値を求める。
- 方針の要点：書き換える要素 i を全探索すると答えは i を除いた gcd で、それは区間 [0, i) と [i+1, N) の 2 つの区間 gcd の gcd なので、Sparse Table で各 i を O(1) 回の gcd で求める。
- このページとの対応：#what-it-does（区間の gcd）と #build の実装の確かめ。左右からの累積 gcd の方が簡単で、記事もそれを併記している。使い分けの「引き算できる演算なら累積和」に近い比較の材料になる
- 帯について：帯より下。力試しにはならないので、載せるなら「実装の練習」として練習の先頭に置く
- 裏付け：
  - https://blog.hamayanhamayan.com/entry/2019/04/28/085936 （Sparse Table で区間 gcd を O(1) で引き、i を除いた 2 区間の gcd を取る方針と、左右の累積 gcd の方針の両方を書く）
  - 2 つ目は探していない（台帳の evidence を参照）

## 調べたが採らなかった問題

- agc040_b（B. Two Contests、diff 1722）：betrue12 の記事（https://betrue12.hateblo.jp/entry/2019/11/04/051835）は区間の min・max をセグメント木か Sparse Table で求められると触れるが、要るのは先頭・末尾からの区間だけで累積の min・max で足りると明記している。このページの練習には向かない
- abc247_e（E. Max Min、diff 1256）：qiita の recuraki の記事は値の出現位置の二分探索で解き、区間 min・max は使っていない
- arc023_4（D. GCD区間、diff 2511 参考値）：「左端ごとに区間 gcd が変わる位置を Sparse Table と二分探索で求める」型の候補として見たが、noimin（https://noimin.hatenablog.com/entry/2020/03/19/184730）と kmyk（https://kmyk.github.io/blog/writeups/algo-atcoder-arc_023_d/）はどちらも右端を進めながら gcd の値ごとの個数を map で持つ方法で、Sparse Table を使う第三者の解説は見つけられなかった。発展の帯でもある
- arc189_d（D. Takahashi is Slime、diff 2006）：このサイトの divide-and-conquer#split-at-max のコードは最大値の位置を Sparse Table で引くが、drken の記事は Cartesian 木、ikatakos の記事は別の方法（累積和と結果の再利用）で、Sparse Table を使う第三者の解説がない。裏付けが取れないので見送り。メインが「自サイトの分割統治のページと同じ解き方」として力試しに置くかは判断に任せる
- LCA（オイラーツアーと RMQ）・Suffix Array の LCP の区間最小を使う問題（abc460_f など）は lca・suffix-array のページの持ち物なので足していない（b2 の報告と同じ扱い）

## 新しく noai を確かめたドメイン

- noimin.hatenablog.com：`tools/check_noai.py` で noai・noimageai の指定なし（2026-10-22）。付録 B への追加の提案
- tookunn.hatenablog.com：同じく指定なし（Sparse Table の解説記事。問題は載っていなかったので資料には使っていない）

## 未解決の点

- 検索の上限に途中で達したため（WebSearch の予算切れ）、「区間 gcd ＋二分探索」「区間 max の位置」の型の問題は、ABC の新しい回（abc300 以降）まで探しきれていない。後でもう一度探す余地がある
- 確かめた候補は 2 件（abc254_f・abc125_c）。推せるのは abc254_f だけで、目標の 2 問は帯の外の abc125_c を含めてようやく届く
