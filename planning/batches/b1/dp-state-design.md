# dp-state-design の報告と提案（工程8b・b1）

- 書いたファイル：docs/dp/dp-state-design.md、snippets/dp-state-design/{avoid-palindrome,bracket,cyclic-coloring}.{cpp,yaml}、docs/img/dp-state-design/{merge,bracket}.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21）。sections は pitfalls の title だけを「落とし穴（最適値だけを持って状態を潰しすぎる）」に変えた（見出しを binary-search と同じ「落とし穴（…）」の形にそろえるため。anchor は同じ）
- 検査の結果：check_pages（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、check_snippets（3 件すべて一致）、textlint（エラー 0・警告 5）
  - 残した警告：41・44 行（要点の「いつ使うか」。signs の文言のまま）、76・147 行（図の代替テキストの長さと数の列）、277 行（台帳の summary から作った問題の行）
- 図：catalog の visual は static・priority 2 なので、静的な SVG を 2 枚作った（決め方の木が要約で合流する図、括弧列を深さの折れ線で描き 0 未満に潜る経路と比べる図）。手元に SVG を画像にする道具（rsvg-convert・cairosvg）がなく、描画は座標の計算でだけ確かめた。メインで一度表示を確かめてほしい
- コード片：期待値は Python の全列挙（回文を避ける埋め方）、カタラン数（括弧列）、$(M-1)^N + (-1)^N (M-1)$（円環の塗り分け）で求めた
- 使った出典：qiita.com/drken（EDPC C）、torus711（abc359_d）、drken のはてなブログ 4 本（abc122_d・abc306_d・abc322_e・abc307_e）、merom686（abc312_d）、ikatakos（abc232_e・abc345_e。解説の部分だけを読むよう指示して取得）。新しく noai を確かめたドメインはない（どれも付録 B のドメイン）

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc147_e | pages | dp-state-design に role: practice を足す（落とし穴「最適値だけを持って状態を潰しすぎる」の代表。途中の和の絶対値の最小だけを持つと誤り、到達できる和の集合が要る）。本文ではいまは問題 ID を出さず、型だけを書いた | 台帳の evidence。research/02-dp §4.A のつまずきにも挙がっている |

ほかの使った問題（dp_c・abc359_d・abc122_d・abc306_d・abc312_d・abc322_e・abc307_e・abc232_e・abc345_e）の summary と approach は、evidence の解説と食い違いがなかった。abc232_e の approach に「K 回の遷移か 4×4 の行列累乗」と足すと、行列累乗のページとのつながりが見えやすい（任意）。

## 用語集への提案

- なし（状態 `state`・正しい括弧列 `balanced-parentheses` は既存の anchor にリンクした）
- 候補：要約｜summary-state｜DP で、過去の選び方のうち将来の可否と評価に影響する部分だけを取り出した情報。要約が同じ選び方は同じ状態にまとめてよい（本文では一般語として使い、リンクはしていない。足すかはメインの判断）

## 手引きへの提案

- §13.1 と、骨格の sections に `anchor: pitfalls` がある場合の扱いが食い違う（binary-search の報告と同じ論点）。今回は §13.2 に従い sections の title と見出しを一致させ、「落とし穴（…）」の形にした。sections から外して `## 落とし穴 {#pitfalls}` にそろえるなら、dp 分野の骨格（dp-basics・cht・dp-prefix-sum など 9 ページ）も同時に直すとよい
- SVG を確かめる道具が手元にない。執筆者が図を目で確かめられるよう、tools に SVG を PNG にする手順（playwright など）があると助かる

## 問題の補充の候補

- abc464_d（D. Celester、diff 752、ap.py で実在を確認、台帳に未登録）：N 日の天気を晴れか雨に決め、元の天気から変えると費用がかかり、雨の翌日に晴れると得点が入るときの、得点から費用を引いた最大を求める（問いは解説のコードからの推測を含む）。直前の天気を状態にする型で、典型の要約（直前の値）の練習に。裏付け：https://qiita.com/comet725/items/79b0587199021cc0f723 。recent-abc.yaml でも dp-state-design#typical-summaries に割り当て済み
- abc462_f（F. More ABC、diff 1952、ap.py で実在を確認、台帳に未登録）：recent-abc.yaml で dp-state-design#last-characters に割り当て済み。「A」「AB」まで一致しているかと作った ABC の数を状態にする（recent-abc.yaml の note）。難しさから力試しの候補。裏付け：https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2026/0613_abc462 （今回は読んでいない。登録前に問いを確かめてほしい）
- abc456_d（D. Not Adjacent 2、diff 586、台帳で確認済み・subsequence-and-substring の練習）：recent-abc.yaml では dp-state-design#last-characters に割り当てられている。こちらにも練習として載せるかはメインの判断（今回は evidence を読んでいない）

## 未解決の点

- ABC122 D の例題の「状態は $5^3$ 程度」「答えは $10^9 + 7$ で割った余り」は drken の解説による。法は問題文で確かめていない（atcoder.jp を開かないため）
- ABC232 E の制約（$K$ の上限）は確かめていないので、練習の方針では「$K$ 回の遷移を回すか行列累乗」と両方を書いた
- ABC312 D の文字列の長さの上限（3000）は merom686 の記事による。本文の状態数の表の「$N = 3000$ で 3001」は一般の例として書いたもので、問題の制約とは結び付けていない
- 動く図は作っていない（visual は priority 2 の static）
- 使用量の目安：道具の呼び出し 約 35 回、Web 取得 10 回

## 検証の指摘への対応（verify/dp-state-design.md）

- 直したもの：1〜8 のすべて
  - 1：sections から pitfalls の行を消し、見出しを `## 落とし穴 {#pitfalls}` にした（§13.1）。上の「手引きへの提案」の 1 つ目はこれで解消。dp 分野の骨格のほかのページをそろえるかはメインの判断
  - 2：二重に数える例を「A を含む」「B を含む」を別々の状態に立てる例に改めた
  - 3：文字の種類の数を $C$ にした（#last-characters と #state-count の表）
  - 4：bit の更新の順を「ずらしてから最下位に入れる」にし、判定の条件を「足した後の文字数が $L$ 以上」に改めた（落とし穴と ABC359 D の解法の詳細）
  - 5：「本節のコード」を「このページのコード片（…）」にした
  - 6：EDPC C の例題を「先頭 $i$ 日を決めた」にそろえた（初期値 $\mathrm{dp}[1]$、答え $\mathrm{dp}[N]$）
  - 7：ABC345 E の方針に、遷移元が斜めの並びになることと累積を使い回せる理由を足した
  - 8：和の絶対値の例を負にもなりうる $a_i, b_i$ にし、小さな数の反例を添えた
- 採らなかったもの：なし
- 台帳への提案（追加）：abc122_d・abc345_e の `checked` に 2026-10-21（検証役が出典を読んで確かめた）
- 検査：check_pages（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、check_snippets（3 片・期待と違う 0）、textlint（エラー 0・警告 5。前回と同じ 5 件）
