# partition-number（整数の分割と分割数）問題の補充の候補

- ページのレベル：黄。いまの問題：例題 abc226_f（2086）・abc404_f（2162）、力試し abc221_h（2793）。練習は 0 問
- 調べた日：2026-10-22

## 候補

| 問題 ID | 題名 | difficulty | 役割 | 要約 | 方針の要点 | 裏付けの URL |
| --- | --- | --- | --- | --- | --- | --- |
| dwacon2018_prelims_c | C. Kill/Death | なし（ap.py で実在を確認。500 点） | practice | キル数が広義単調減少の 2 チームについて、自分のデス数の合計が相手のキル数の合計に等しく、同じキル数の人どうしではデス数が広義単調減少になるデス数の割り当ての数を求める。 | 同じキル数の人が n 人いるまとまりでは、デス数の合計 k への割り当てが「k を n 個以下の部分に分ける」分割数 p(k, n) になるので、これを重みにしてまとまりごとに合計を進める DP で数える（前処理 O(NS)、DP O(NS^2)、S は合計の上限 1000）。 | https://drken1215.hatenablog.com/entry/2023/05/07/160611 、https://drken1215.hatenablog.com/entry/2018/01/16/222843 |
| arc107_d | D. Number of Multisets | 2099（黄） | practice | 1, 1/2, 1/4, … の形の有理数をちょうど N 個選んで和を K にする多重集合の数を求める（K ≤ N ≤ 3000）。 | ページの「分割数型の DP」と同じく 1 を含むかどうかで場合分けし、含むなら 1 を取り除いて f(N−1, K−1)、含まないなら全体を 2 倍して f(N, 2K) とする漸化式 f(N, K) = f(N−1, K−1) + f(N, 2K) を、同じ行の右側を先に埋める順（K の降順）で O(N^2) で求める。 | https://drken1215.hatenablog.com/entry/2020/11/01/175900 、https://kmjp.hatenablog.jp/entry/2020/11/04/0900 |

- 練習は合わせて 2 問になる（目標 2〜4 問の下限）
- dwacon2018_prelims_c はすでに data/problems.yaml で pages に `{id: partition-number, role: practice}` を持つが、本文にない（b3 の報告の候補）。台帳の summary・approach・evidence は上と同じ内容で、そのまま本文の練習の節に載せられる。difficulty がないので、ABC・ARC の候補がもっと見つかれば入れ替えを考える
- arc107_d は台帳にない（新しい問題）。台帳への追加を提案する：summary・approach は上の表、evidence は drken・kmjp の 2 つ、pages は `{id: partition-number, role: practice}`。関連するページとして partition-number#partition-dp の練習が合う。分割数そのものではなく「1 を含むかで場合分けし、含まなければ全体を変換して同じ形に戻す」という分割数型の DP の考え方の練習である点を、本文の要約か方針で添えるとよい（drken・kmjp の記事は「分割数」の語を使っていない。結び付けはこのページの節の構成からの判断）
- 練習の節に置くなら、arc107_d は発展の節（partition-dp）を指すので、方針に節へのリンクを張る

## 探したが入れなかったもの

- b1・b5 の candidates.md に partition-number 向けの AtCoder の候補はなかった。b5 の AOJ DPL_5_J・L（分割数）は AtCoder 以外で、twelvefold-way の候補として出ているので、ここでは入れない
- drken「分割数」カテゴリ（https://drken1215.hatenablog.com/archive/category/分割数 ）の AtCoder の問題は Kill/Death だけだった。ほかは yukicoder No.269（利用規約の確認前なので使わない）・AOJ 0537 ビンゴ・Library Checker の Partition Function で、AtCoder ではない
- arc104_d（Multiset Mean、2251）は題名に多重集合を含むが、個数制限つきナップサックの問題で、このページの手法ではないので入れない
- 分割の全列挙（降順の列）で解く ABC・ARC の練習向きの問題は、Web 検索・kmjp・drken の記事では見つからなかった

## 使ったドメイン

- drken1215.hatenablog.com・kmjp.hatenablog.jp（どちらも付録 B にある）。atcoder.jp・codeforces.com は開いていない
