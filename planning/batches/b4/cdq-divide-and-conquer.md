# cdq-divide-and-conquer の報告と提案（b4）

- 書いたファイル：docs/ds/cdq-divide-and-conquer.md、snippets/cdq-divide-and-conquer/dominance.{cpp,yaml}、docs/img/cdq-divide-and-conquer/split.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-22）。sections に `自作するときの要点と Library Checker {#library}` を足した（procedure と alternatives の間）。`## 学ぶための資料 {#resources}` は hld にならい sections に載せない定型の見出しとした
- 検査の結果：check_pages エラー 0・警告 0、fix_problems --check 直すべき行 0、check_snippets 期待と違う 0、textlint エラー 0（警告 13：数式を含む文の長さ・半開区間の `[` の対応・読点の数の誤検出）
- 図：split.svg（幅 400）を render_svg.py で PNG にして目視した（360px でも文字が読める）。catalog の visual は priority 2 の static なので動く図は作っていない
- 使った出典：OI Wiki「CDQ 分治」（名前の由来・3 つの型・同じ点をまとめる扱い・中間順）、robert1003.github.io（枠組みの 4 段と漸化式。check_noai で noai なしを確認）、Library Checker の task.md（GitHub。point_add_rectangle_sum・rectangle_add_point_get の内容と制約）

## 台帳への提案

- なし（catalog の problems が空で、本文に問題の囲みは置いていない。例題 0 問）

## 用語集への提案

- 支配点（多次元の）｜dominance-point｜点 $p$ のすべての座標が点 $q$ の対応する座標以下のとき、$q$ は $p$ を支配するという。3 次元なら $a_p \le a_q$ かつ $b_p \le b_q$ かつ $c_p \le c_q$。各点が支配する点の個数を数える問題を支配点の数え上げという（既存の「支配（状態の）{#dominance}」とは別の語なので、anchor を分ける）
  - 本文では用語集にリンクせず、何ができるかの節で定義した

## 手引きへの提案

- 付録 B に robert1003.github.io を足す（2026-10-22 に check_noai で noai・noimageai なしを確認）
- 発展の概要の「学ぶための資料」の見出し `## 学ぶための資料 {#resources}` を §13-1 の定型の見出しに加えるとよい（hld と本ページで使用。sections に載せるかが手引きに書かれていない）

## 問題の補充の候補

- 見つからなかった。Web 検索（日本語・英語）で、ABC・ARC で CDQ 分割統治が想定解または必須となる問題の第三者の解説は見当たらなかった（研究 01 §4.J・05 §4.E の結論と同じ）。中国の OJ の問題（洛谷 P3810 三维偏序など）は台帳の対象外
- 練習の代わりに、Library Checker の Point Add Rectangle Sum（verify）と Rectangle Add Point Get を自作の確認として本文に置いた

## 未解決の点

- cnblogs の mlystdcall 氏の CDQ 入門記事は check_noai が時間切れで確かめられず、本文を読んでいないので資料から外した
- `related` に advanced-ds-catalog・inversion-number を足す案（本文の代わりの手の表と、仕組みの説明でリンクしている）。front matter の related は執筆者が変えない項目なので提案にとどめる
- 使用量の目安：道具の呼び出し 約 30 回、Web 取得 4 回（WebFetch 3・検索 3）

## 検証の指摘への対応

- 直すとよい 1〜5 をすべて直した（採らなかった指摘はない）
  - 1：「配列の 2 次元 BIT はそのままでは置けない」とし、先読みして圧縮する方法を代わりの手の節へ案内した
  - 2：何ができるかの節でも $(a, b, c)$ の辞書順とし、$a$ が等しい点の扱いは #library へ案内した
  - 3：擬似コードと本文の中央を `mid`（$\mathit{mid}$）にそろえ、長方形を $[x_1, x_2) \times [y_1, y_2)$ に改めた
  - 4：$a$ だけでソートしたときの数え落としを、文を分けて例 $(1, 2, 2)$・$(1, 1, 1)$ で説明した
  - 5：Library Checker の 2 問を judge.yosupo.jp へのリンクにし、$N, Q \le 10^5$・重み $\le 10^9$ から和が $2 \times 10^{14}$ ほどになることを書いた
- 検査：check_pages エラー 0・警告 0、fix_problems --check 直すべき行 0、check_snippets 期待と違う 0、textlint エラー 0（警告 15：数式を含む文の長さ・半開区間の `[`・読点の数の誤検出）
- 共有ファイルへの新しい提案はない（related・用語集の提案は上のとおり）
