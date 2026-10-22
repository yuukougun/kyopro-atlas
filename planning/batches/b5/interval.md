# interval（区間）の報告と提案

- 書いたファイル：docs/patterns/interval.md、docs/img/interval/subarrays-as-points.svg（コード片なし）
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-22）。sections に `{title: 問われ方と手法の一覧, anchor: overview}` を properties の次に足した（見本 bracket-sequence と同じ形）
- 検査の結果：check_pages エラー 0・警告 0、fix_problems --check 直すべき行 0、textlint エラー 0（警告 24。数式の `[l, r)` による括弧の対応・文の長さ・読点の数の誤検出と、163 行のリンクの題名の中の「に」の重なり）。図は render_svg で 360px・720px を目視
- 構成：題材の性質（点 (l, r) の図・確認問題）→ 一覧の表（3 つの型ごとに 3 つの表）→ 17 の行き先の節 → 落とし穴 → 練習問題 3 → 参考。行き先の draft のページはすべて節の anchor でリンクした。stub の patterns（subsequence-and-substring・kth-and-median・mex・permutation）はページへのリンク

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
|---|---|---|---|
| abc457_e | summary | M 個の区間からちょうど 2 個を選び、選んだ区間で覆われる範囲が、質問の区間とちょうど一致するようにできるかを、多数の質問について判定する。 | https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2026/0509_abc457 の解法の節（2 通りの形の場合分け） |
| abc457_e | approach | 2 個で [S, T] をちょうど覆う形は「左端 S の区間と右端 T の区間がすき間なくつながる」か「[S, T] そのものとその内側の区間」の 2 通り。左端ごと・右端ごとのソートした一覧を作り、質問を T の順に処理して、二分探索とそれまでの左端の最大値で判定する | 同上 |
| abc189_c | evidence | https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2021/0123_abc189 を足す（いまの note の記事は問題の一覧だけで、解法の裏付けにならない） | ヒストグラムの最大長方形と見る・O(N^2) が通る・スタックで O(N) |
| abc265_d | evidence | 2 つ目の裏付けが未確保（ikatakos の abc265 の記録には D の解法の節が見つからなかった） | — |

## 用語集への提案

なし（使った語：half-open-interval・state・associativity・idempotent・offline・subsequence はどれも既存）。「部分文字列」は付録 A にあるが用語集の項目がない。必要なら「部分文字列｜substring｜文字列の連続した一部分。飛び飛びに選ぶ部分列とは別物」を足す案。

## 手引きへの提案

- pattern のページで、表の数が多い（16 行）ときは型ごとに表を分けてよい、と §4 に足す案（今回は太字の 1 行の見出し＋表 3 つにした。小見出し ### は sections に載らないので使わなかった）

## 問題の補充の候補（問題ID・何を問うか・裏付けの URL）

今回は台帳の 3 問で足りた（patterns の練習の目安 0〜3）。追加の候補は探していない。

## 未解決の点

- ABC265 D の方針の「値が正なので累積和は狭義に増える」は、evidence（oraclesqlpuzzle）が累積和の配列を二分探索していることからの読み取りで、制約そのものは確かめていない（atcoder.jp を開けないため）。検証で別の解説から確かめてほしい
- ABC457 E の evidence を読む際、ikatakos のページの抽出結果に問題文の節が混じって表示された。要約・方針は解法の節の記述（2 通りの図と判定の手順）だけから書いた
- sections の title のうち 60 字を超えるもの（offline・online-updates など）は骨格のまま残した。短くするならメインの判断で
- monotonic-stack のページの練習に abc189_c が載っていない（台帳では monotonic-stack の practice）。b4 以前の扱いの確認

## 使用量の目安

道具の呼び出し 約 45 回、Web 取得 5 回（ikatakos 3・oraclesqlpuzzle 1・note 1）

## 検証の指摘への対応（b5/verify/interval.md）

- 指摘 1〜6 はすべて直した。採らなかったものはない
    - 1：落とし穴の「答えの大きさ」を、全区間の最小値（最大値）の総和（約 2×10^19、超えうる）と全区間の和の総和（約 10^24、必ず超える）に書き分けた
    - 2：負の値のとき、ちょうど K は連想配列、K 以下・以上は累積和を座標圧縮して BIT で O(N log N) と書き分けた
    - 3：#containment の最後の文から ABC457 E を外した
    - 4：(a) 位置と値を明記、(b)「質問の区間 [p, q]」と名付けた
    - 5：見出しと sections の title を同時に短くした（anchor は変えていない）。online-updates はかっこの id から lazy-segment-tree を外し（一覧の表と節の本文にリンクは残る）、offline は「区間の種類数・x 以下の個数 → 先読みと BIT、Mo（offline-queries, mo-algorithm）」（59 字）にした
    - 6：3 つ目の型に計算量 O(N^3) と、最後に残す要素を決める決め方を足した
- 検査：check_pages エラー 0・警告 0、fix_problems --check 直すべき行 0、textlint エラー 0（警告 27）

## 台帳への提案（検証を受けて追加）

| 問題 ID | 項目 | 新しい値 | 根拠 |
|---|---|---|---|
| abc189_c・abc265_d・abc457_e | checked | 2026-10-22 | 検証で要約・方針を確かめた |
| abc265_d | evidence | https://zenn.dev/dhirabayashi/articles/557bbf51c35edf を足す | D の節に「A_i は 1 以上なので累積和の配列は単調増加」 |
| abc457_e | summary | 上の表の提案のとおり（台帳はまだ「（執筆時に確かめる）」） | — |
