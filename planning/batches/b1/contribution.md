# contribution（主客転倒・寄与）の報告と提案

- 書いたファイル：docs/thinking/contribution.md、snippets/contribution/basic.{cpp,yaml}、docs/img/contribution/rows-and-columns.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21）。sections は変えていない
- 検査の結果：check_pages エラー 0・警告 0／check_snippets 期待と違う 0／textlint エラー 0（警告 13：数式を含む文の長さ・数式の中の括弧・代替テキストの読点・問題の要約の「で」の重なりなど）／fix_problems --check は本ページの行は 0 件だが、別の執筆者の math/digit-and-mod.md に ID だけの行が 6 行あり終了コード 1
- 使った出典：drken（abc186_d・abc151_e・abc379_e）、ikatakos（abc468_e、解説の部分だけ）、oraclesqlpuzzle と torus711（abc351_f）、hamayan（abc140_e）。どれも付録 B のドメインで、新しく確かめたドメインはない
- 動く図：作っていない（catalog の visual は static・priority 2 で、静的な SVG で代えた）

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠の URL |
| --- | --- | --- | --- |
| abc468_e | summary | 整数列のすべての区間について平均値を求め、その総和を 998244353 で割った余りを求める。 | https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2026/0725_abc468 |
| abc468_e | approach | 各要素を含む長さ w の区間の数 × 1/w を w について足す。区間の数は増加・一定・減少の 3 段階なので、逆数の累積和で各要素 O(1) | 同上 |
| abc140_e | approach（contribution 用） | 現状のままでよい。本文では大きい値から順に位置を set に入れて左右 2 つずつを求める方法を書いた（ordered-set の alternatives と同じ） | https://blog.hamayanhamayan.com/entry/2019/09/11/203310_3 |

本文の abc468_e の行は上の summary で書いた。台帳を直して fix_problems を流すと同じ文になる。

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| 寄与 | contribution | 総和を要素ごとの和に分けたとき、1 つの要素が答えに足される量。「要素の値 × その要素が数えられる回数（または重みの和）」で表す。 |

本文ではページの題名なので用語集へのリンクはしていない。

## 手引きへの提案

- §2.5・§10 に「台帳の summary が（執筆時に確かめる）のとき、本文の行に自分で書いた要約を置き、fix_problems がそれを上書きしない」ことを明記するとよい（今回 fix_problems はこの行を指摘しなかったので、本文と台帳の要約が食い違ったままでも検査を通る）

## 問題の補充の候補

| 問題 ID | 何を問うか | 役割の案 | 裏付けの URL |
| --- | --- | --- | --- |
| abc172_d | 1 以上 N 以下の各 K について K × (K の約数の個数) の総和を求める。約数 d ごとに倍数の和として数え直す。台帳は確認済みで sigma-manipulation の例題 | 練習（本文の「各約数の寄与」に対応する問題がまだない） | https://qiita.com/dvoraker3/items/8388ab6e1dc3af55070e |
| abc147_d | 全ペアの XOR の総和。bit ごとに 0 と 1 の個数の積で数える。台帳は確認済みで bitwise-independence の例題 | 練習（任意。本文はリンクで済ませた） | https://drken1215.hatenablog.com/entry/2020/04/25/032000 |

## 未解決の点

- 練習の abc468_e は diff 1038 で、例題 abc151_e（1344）より易しい。並びは易しい順にしたので練習の先頭に置いた。例題が 2 問（thinking の目安 2〜4 の下限）なので、abc172_d を練習ではなく例題に足す案もあるが、sigma-manipulation の例題と重なる（1 問 1 ページ）ので練習を提案した
- frequency_evidence の recent 5 問（abc455_f・abc461_e・abc470_g・abc471_g）はどれもほかのページの問題で、本文では使っていない
- abc151_e の値の範囲（負の値を含むか）は確かめきれなかったので、本文は「係数が負になりうるので mod の引き算に気をつける」とだけ書いた
- SVG は描画の道具がなく目で確かめていない。文字の幅を見積もって viewBox を 640 幅にした
- 使用量の目安：道具の呼び出し約 25 回、Web 取得 6 回（ほかに題名の確認で curl 8 回）

## 検証の指摘への対応（planning/batches/b1/verify/contribution.md）

- 1（complexity の整合）：front matter の complexity を「ソートや BIT を使うなら O(N log N)、単調スタックなら O(N)」とし、要点の計算量も同じ書き方にそろえた
- 2（図の幅）：viewBox を 430 × 410 にし、題と下の式をそれぞれ 2 行に分けた（下の式も font-size 14）。表の位置と値は変えていない
- 3・4・5・6：指摘どおりに直した（$L_i$・$R_i$ の番兵、ABC468 E の方針の書き直し、使い分けの前提、コード片のあふれの注意）
- 7（signs の括弧）：signs は catalog 由来で執筆者は変えないので、下の提案に回した。要点の「いつ使うか」は signs から作られるため、本文も変えていない
- 8（台帳の checked）：下の提案に回した

### 追加の提案（台帳・signs）

| 対象 | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| contribution の front matter signs（と catalog） | 3 項目め | 全区間の最小値・2 番目に大きい値などの和 | 括弧が言い換えに読める（検証の指摘 7） |
| abc186_d・abc151_e・abc468_e・abc379_e・abc351_f・abc140_e | checked | 2026-10-21 | 検証役が ap.py と出典で題名・diff・内容を確かめた（検証の指摘 8） |
| abc468_e | summary・approach | 上の「台帳への提案」のとおり（approach は「増加の段は 1、一定・減少の段は逆数の累積和」） | ikatakos の記事 |

- 直した後の検査：check_pages エラー 0・警告 0／check_snippets 期待と違う 0／textlint エラー 0（警告 13）／fix_problems --check は本ページの行は 0 件だが、別の執筆者の dp/rerooting.md に ID だけの行が 4 行あり終了コード 1
