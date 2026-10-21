# knapsack-undo（戻す DP）の報告と提案

- 書いたファイル：docs/dp/knapsack-undo.md、snippets/knapsack-undo/add-remove.{cpp,yaml}、snippets/knapsack-undo/prefix-suffix.{cpp,yaml}、docs/img/knapsack-undo/add-remove.svg
- front matter で変えたもの：complexity・stage（draft）。updated は 2026-10-21 のまま（今日）。sections は変えていない
- 検査の結果：check_pages エラー 0・警告 0、fix_problems --check 0 行、check_snippets 2 本とも期待どおり、textlint エラー 0（警告 16。図の代替テキスト・数式を含む文の長さ・`[` の対の誤検出・折りたたみの中の長い文）
- 図：add-remove.svg を render_svg.py で PNG にして目視した（文字の重なりなし）。visual は dynamic・priority 3 なので静的な図で代えた。動く図の div は置いていない

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc441_f | summary | 代金の合計 M 以下で価値の和を最大にする買い方について、各品物を「どの最適解でも買う」「どの最適解でも買わない」「買う最適解と買わない最適解の両方がある」に分ける。 | https://www.luogu.com.cn/article/632714wx ・ https://inamori.hateblo.jp/entry/2026/01/20/185733 |
| abc441_f | evidence | 上の 2 件を足す（ikatakos の記録は取得時に HTTP 503 で読めなかった） | 同上 |

- 本文の行は `- abc441_f：要約` で書き、fix_problems で label を埋めた

## 用語集への提案

- なし（オフライン・逆元は既存の anchor を使った）

## 手引きへの提案

- §5 dp に「戻す DP のような削除の更新は、追加と逆向きにループを回す（0-1 は追加が大きい方から・削除が小さい方から、個数制限なしは逆）」を足すと、knapsack-01・subset-sum の向きの説明とそろう（任意）

## 問題の補充の候補

- arc028_4（D. 注文の多い高橋商店、diff 2997 参考値・発展）：個数制限付きの数え上げの表から、1 種類だけを取り除いた値を各クエリで答える（戻す DP の個数制限付き版）。https://drken1215.hatenablog.com/entry/2020/10/04/152700 （research/02 で既出。記事は今回は読んでいない。難しすぎるので力試しにするかはメインの判断）
- 戻す DP の ABC の練習（abc319 以降）は見つけていない。現状の例題 1・練習 2 で目安は満たす

## 未解決の点

- abc441_f の制約（N・M の上限）は 2 つの解説から明記を確かめられなかった。本文では「$O(NM)$」とだけ書き、制約の数値は書いていない
- arc070_b の「不要なカードは値の小さい側にまとまる」は、不要の条件（区間 $[K - a_i, K)$ に作れる和がない）から自分で確かめた。drken の記事の要約（WebFetch）では向きが逆に読める箇所があったが、条件から小さい側が正しい
- 黄の節（offline-divide-and-conquer）で SWAG（monotonic-stack#swag、発展の節）へリンクした。帯が上がるリンクだが、補足として触れるだけにした
- 新しく noai を確かめたドメイン：inamori.hateblo.jp（指定なし）。www.luogu.com.cn は付録 B にあり、記事も指定なし

## 検証の指摘への対応（verify/knapsack-undo.md）

- 1（直すべき・メモリの境）：`long long` の表 2 つで約 $16NW$ バイト、$NW = 6.4 \times 10^7$ で 1024MB、$10^7$ を超えるあたりから見積もる、と書き直した
- 2：初期値をすべて 0 にすれば「以下」になること、「ちょうど」なら $j = 0$ だけ 0・ほかは $-\infty$ を足した
- 3：節に「$W$ は重さの上限で、要点の和の上限 $K$ にあたる」と添え、要点と front matter の complexity を「和（重さ）の上限」にした
- 4：可否の例を $\{2, 2\}$ と $\{2\}$ の具体例にした
- 5：時刻 $t$ の意味と、最後まで残る品物は $r = Q$ とすることを足した
- 7：図を作り直した（viewBox 780×340 → 580×380。注記を各表の下へ移し、字を 15px にした。ラベル「2 を削除して戻した表」は表に接するので「2 を削除した表」に縮めた）。render_svg.py の 360px・720px で目視し、重なりなし
- 採らなかった指摘：6（リンクを `divide-and-conquer.md#range-knapsack` に）。先のページが stage: stub で、check_pages.py が「節へのリンクは draft 以降のページにだけ」のエラーを出すため、ページへのリンクのままにした。divide-and-conquer が draft になったら節へのリンクにする（メインへの提案）

## 台帳への提案（検証から）

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc441_f | checked | 2026-10-21 | 検証役が luogu・inamori の記事で方針を確かめた |
| arc070_b | checked | 2026-10-21 | drken の記事で制約と不要の言い換えを確かめた |
| abc321_f | checked | 2026-10-21 | drken の記事で制約と「取り出す値はある」保証を確かめた |
