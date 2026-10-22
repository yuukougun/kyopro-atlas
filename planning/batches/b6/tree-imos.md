# tree-imos の問題の補充（b6・工程9）

- ページ：docs/tree/tree-imos.md（レベル 基礎）。今の練習は abc222_e（diff 1491）の 1 問、例題は abc187_e
- 探したところ：
    - (1) b1 の報告 planning/batches/b1/tree-imos.md と b1 summary/candidates.md の「### tree-imos」に abc138_d・abc309_e がある。b3・b5 の candidates.md には tree-imos の候補なし。tree-imos の報告は b1 だけ
    - (2) data/problems.yaml で pages に tree-imos を持つが本文にない問題は abc138_d（role: practice）・abc309_e（role: practice）の 2 問。b1 で台帳に足したが本文の練習には入っていない
    - (3) パスへの加算（青の節）の代表になる問題を第三者の解説で探そうとしたが、このセッションの検索の上限に達して探せなかった。b1 の報告どおり、パスへの加算の代表は見つかっていない
- 問題の実在・題名・difficulty は `python3 tools/ap.py show` で確かめた（2026-10-22）
- 候補 2 問を足すと練習は合わせて 3 問になる（基礎の帯の 2 問と水の abc222_e）

## 候補

### abc138_d（台帳にあり、本文になし）

- 問題ID：abc138_d
- 題名：D. Ki
- difficulty：920（基礎）
- 役割：practice
- 要約：頂点 1 を根とする木で、部分木の全頂点に x を足す操作を Q 回行った後の、各頂点の値を求める。
- 方針の要点：各操作では部分木の根に x を足すだけにし、最後に根から下へ親の値を子に足して累積する（節 subtree-add のコードそのまま、O(N + Q)）。
- 裏付け：
    - https://drken1215.hatenablog.com/entry/2020/05/18/174000 （問題の設定と、部分木の根に足して根から子へ配る方針・O(N + Q) を確かめた）
- 注：例題 abc187_e と同じ節を使うより易しい形なので、練習の最初に置くとよい

### abc309_e（台帳にあり、本文になし）

- 問題ID：abc309_e
- 題名：E. Family and Insurance
- difficulty：957（基礎）
- 役割：practice
- 要約：親が子より小さい番号で与えられる家系図で、人 x から y 世代下までの子孫に及ぶ保険がいくつかあるとき、保険の対象になる人の数を求める。
- 方針の要点：「あと何世代まで及ぶか」の最大を番号順に dp[i] = max(dp[p_i] − 1, 本人の保険の y の最大) と親から子へ伝え、dp[i] ≥ 0 の人を数える（節 depth-limited の形、O(N + M)）。
- 裏付け：
    - https://qiita.com/ZOI_dayo/items/a55cc4342832efdc23ba （問題の設定と上の漸化式・無保険を −1 とすることを確かめた）
- 注：台帳では tree-traversal の練習にもなっている（そちらは残す）

## 見つからなかったもの

- パスへの加算（LCA に印、葉から上へ累積）を必要とする ABC の問題は見つけていない。abc222_e は制約が小さく素朴に数えても通る。検索の上限のため今回は第三者の解説を探せなかったので、次の機会に探したい
