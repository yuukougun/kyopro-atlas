# degree-sqrt の問題の補充（工程9・b6）

- ページ：docs/graph/degree-sqrt.md（レベル 青）
- 今の問題：例題 typical90_ce、練習 abc260_f（1 問）、力試しなし
- 結論：練習の候補 1 問（合わせて 2 問になる）と力試しの候補 1 問を確かめた。difficulty・題名は `python3 tools/ap.py show` で確かめた（2026-10-22）
- 探した範囲：
  - (1) これまでの候補：b1・b5 の candidates.md に degree-sqrt の候補はない。b3 の candidates.md と b2 の報告は「確かめきれた候補なし」（abc258_g は N ≤ 3000 の密なグラフで bitset 側）
  - (2) 台帳で pages に degree-sqrt を持つのは typical90_ce・abc260_f だけで、どちらも本文にある。台帳を「次数」「√」で検索して、別ページに載っている abc219_g（sqrt-decomposition の例題）と abc350_g（dynamic-tree・small-to-large・bitset-speedup の練習）を見つけた
  - (3) 第三者の解説：drken の「平方分割」カテゴリの一覧、kyo-pro の解法パターンの整理、CADDi Tech Blog の平方分割の記事を見たが、ほかに次数で分ける AtCoder の問題は見つからなかった。ap.py の題名検索（Triangle・Neighbor・Adjacent・Friend・Cycle・Square・Common）でも、abc260_f のほかに該当するものはなかった（abc467_e「Adjacent Sums (hard)」は ikatakos の解説で、列の和の問題でグラフではないと確かめた）
  - Web 検索はセッションの上限に達したため途中までしかできていない。残りは既知の URL を直接開いて確かめた

## 練習の候補（practice）

### abc350_g　G. Mediator（diff 2058・黄）

- 台帳：登録済み（dynamic-tree・small-to-large・bitset-speedup の practice）。pages に degree-sqrt:practice を足し、alternatives に degree-sqrt の要約・方針を足す提案
- 要約：辺のない N 頂点のグラフに、森であることを保ちながら辺を 1 本ずつ足し、その合間に 2 頂点の両方に隣接する頂点を 1 つ答える質問にオンラインで答える。
- 方針の要点：どちらかの端点の次数がしきい値 B ≈ √N 未満なら、その隣接リストを走査してもう一方との隣接を辺の集合で調べ、両方が重いときは重い頂点の隣接集合だけを持った bitset の AND（または重い頂点 2 つ以上に隣接する O(N/B) 個の候補の走査）で答える。
- このページとの対応：#few-heavy（重い頂点は 2M/B 個以下なので、重い頂点にだけ大きな情報を持たせられる）と #push-pull（軽い側は隣を全部たどる）。質問の形は「共通の隣」で、本文の 2 つの型とは違う応用になる
- 帯について：difficulty は青の帯の上端を 58 上回る（黄）。今の練習 abc260_f（1995）と並ぶ高さ。帯から少し離れるので、力試しに回すかはメインの判断
- 補足：drken の解説の本文は小さい方の木を根付け直すマージテクの解法で（台帳の small-to-large の方針）、次数による平方分割は別解である
- 裏付け：
  - https://kmjp.hatenablog.jp/entry/2024/04/22/0900 （D ≈ √N で分け、どちらかが軽ければ隣接を走査、両方重ければ重い隣を 2 つ以上持つ O(N/D) 個の候補を調べる。全体 O(N√N)）
  - https://www.cnblogs.com/No-play-Yes-splay/p/18148245/atcoder-beginner-contest-350-sol （次数が B 以下なら素朴に、超えたら bitset を持たせて AND。台帳の evidence にもある）

## 力試しの候補（challenge）

### abc219_g　G. Propagation（diff 2287・黄）

- 台帳：登録済み（sqrt-decomposition:example）。pages に degree-sqrt:challenge を足す提案
- 要約：頂点 i の値が初め i のグラフで、指定した頂点の今の値を隣接頂点すべてに書き写すクエリを Q 回行った後の、全頂点の値を求める。
- 方針の要点：軽い頂点は隣すべてに値とクエリの時刻を配り、重い頂点は最後に配った時刻と値を自分にだけ記録し、値が要るとき（自分がクエリされたときと最後）に隣の重い頂点の記録のうち新しいものを取りに行く。
- このページとの対応：#push-pull の「隣すべてを書き換え、1 点を聞く」型そのもので、例題 typical90_ce とほぼ同じ組み方になる。違いは、書き写す値がクエリの頂点の今の値なので、重い頂点も自分の値を取りに行ってから記録する点である
- 帯について：difficulty は黄の帯で、青のページからは離れるので力試しとした。例題とほとんど同じ考え方なので、練習に下ろすかはメインの判断（sqrt-decomposition では例題として本文で解いている）
- 裏付け：
  - https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2021/0918_abc219 （配る・取りに行くを次数で使い分け、しきい値 √M 程度、全体 O(Q√M)）
  - https://kmjp.hatenablog.jp/entry/2021/09/29/0900 （次数の大きい頂点は伝播を遅らせ、最終時刻と値を持つ。台帳の evidence にもある）

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc350_g | pages | `{id: degree-sqrt, role: practice}` を足す（力試しに回すなら challenge） | 上の kmjp・cnblogs |
| abc350_g | alternatives | pages: degree-sqrt、approach「どちらかの次数が √N 未満ならその隣を走査して隣接を調べ、両方重ければ重い頂点の隣接集合（bitset）か、重い頂点 2 つ以上に隣接する候補だけを調べる」 | 同上 |
| abc350_g | evidence | `https://kmjp.hatenablog.jp/entry/2024/04/22/0900` を足す | 次数による平方分割の解法を確かめた（2026-10-22） |
| abc219_g | pages | `{id: degree-sqrt, role: challenge}` を足す | 上の ikatakos・kmjp |
| abc219_g | evidence | `https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2021/0918_abc219` を足す | 配る・取りに行くの使い分けと O(Q√M) を確かめた（2026-10-22） |

## 新しく確かめたドメイン

- caddi.tech：check_noai で noai・noimageai の指定なし（2026-10-22）。記事（archives/1259）は列の平方分割だけで、今回の候補には使っていない
- sigma1113.hatenablog.com：check_noai で指定なし（2026-10-22）。開いていない
