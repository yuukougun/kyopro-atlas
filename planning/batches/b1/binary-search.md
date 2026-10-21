# binary-search の報告と提案（工程8b・b1）

- 書いたファイル：docs/basics/binary-search.md、snippets/binary-search/{meguru,count,triangles}.{cpp,yaml}、docs/img/binary-search/bounds.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21 のまま）。sections は変えていない
- 検査の結果：check_pages（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、check_snippets（3 件すべて一致）、textlint（エラー 0・警告 4）
  - 残した警告：59 行と 97 行の max-comma（数式の中の列 $(2, 3, …)$ と図の代替テキストの数の列）、196 行の sentence-length と no-unmatched-pair（折りたたみの中の数式 $[j + 1, N)$ の半開区間を括弧の対と誤検出）
- 動く図：既存の overrides/assets/js/viz/binary-search.js（見本）をそのまま使い、`<div class="kp-viz" data-viz="binary-search" data-config='{"array": [2, 3, 3, 5, 7, 7, 7, 9], "target": 7}'>` を置いた。図の前後の文章（手順を文章で追う箇条書き）も書いた。新しい JS は書いていない。catalog の visual（priority 1）はこれで満たすと考える
- 使った出典：drken の Qiita（めぐる式）、drken のはてなブログ 6 本（abc143_d・abc302_d・abc205_d・abc321_d・arc084_a・abc119_d の方針）。題名は各ページの title 要素で確かめた。新しく noai を確かめたドメインはない（どれも付録 B のドメイン）

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc299_d | pages | binary-search に role: practice を足す（interactive の例題はそのまま）。「質問で二分探索する」節の練習に使いたい。本文ではいまは問題 ID を出さず、型だけを書いた | https://oraclesqlpuzzle.ninja-web.net/kyoupro/05-atcoder-02-abc/kyoupro-abc299-d.html（台帳の evidence） |

ほかの使った問題（abc143_d・abc302_d・abc205_d・abc321_d・arc084_a・abc119_d）の summary と approach は、evidence の解説と食い違いがなかった。

## 用語集への提案

- 単調性｜monotonicity｜条件の真偽が、候補を小さい順に並べたとき 1 か所だけで切り替わる性質。二分探索・答えで二分探索・尺取り法が成り立つ根拠になる（本文ではまだリンクしていない。足すなら binary-search と binary-search-answer の最初の出現からリンクする）

## 手引きへの提案

- §13.1 は「落とし穴」を定型の節として sections に載せないとするが、binary-search（と binary-search-answer の骨格の時点）は sections に `anchor: pitfalls` を持ち、題名がかっこ書きつきの長いものになっている。§13.2 に従い見出しを sections の title と同じにしたので、見出しが「落とし穴（(ok + ng) / 2 のあふれ・負の数の丸め・set に std::lower_bound）」と長い。sections から外して `## 落とし穴 {#pitfalls}` にそろえるか、メインで決めてほしい（anchor は同じなのでリンクは壊れない）
- 基礎の technique の目安（要点 → 応用の型 → 落とし穴 → 上位の手法とのつながり → 問題）の「上位の手法とのつながり」は、定型の見出しにない。今回は `## 使い分け {#comparison}` にまとめた。定型の見出しにするなら anchor を決めてほしい

## 問題の補充の候補

- abc299_d（D. Find by Query、diff 684、台帳で確認済み）：先頭が 0・末尾が 1 の隠れた 01 列で、隣と値が異なる位置を 20 回以内の質問で見つける。めぐる式の判定を質問に置き換える型。裏付け：https://oraclesqlpuzzle.ninja-web.net/kyoupro/05-atcoder-02-abc/kyoupro-abc299-d.html
- abc319 以降の問題は、基礎のページの要件でないため探していない

## 未解決の点

- frequency_evidence の recent 4（abc457_e・abc476_d・abc480_d・abc480_e）は、abc457_e が台帳で interval の練習（summary が「（執筆時に確かめる）」）で、残り 3 問は台帳に見当たらなかった。このページには載せていない
- 図 bounds.svg は描画して目で確かめる道具がなく、XML として読めることと座標の計算だけを確かめた。表示の確認を検証役に頼みたい
- `std::midpoint` が C++20 であること、`std::set` に `std::lower_bound` を使うとイテレータの前進が O(N) になることは、記憶に基づく（research/01-basics の記述とも一致）。cpprefjp での確認を検証役に頼みたい

## 検証の指摘への対応（verify/binary-search.md）

- 直すべき 1〜5 はすべて直した。1：sections から pitfalls を外し、見出しを `## 落とし穴 {#pitfalls}` にした（手引きへの提案の 1 つ目はこれで解消）。2：あふれの閾値と `ok + (ng - ok) / 2` の条件・`std::midpoint` を直した。3：本文の番兵の段落を直し、count.cpp の番兵を `1e18` にした（cases の出力は変わらない）。4：「各行に印が高々 1 つ」「閉区間 $[1, m]$（1-indexed）」の条件と単調になる理由を足した。5：bounds.svg の marker を右向きの三角・`orient="auto"`・`refX="8" refY="4"` にし、線ごとに青・茶の marker に分け、upper_bound のラベルを上げて矢印と重ならないようにした（描画での目視は未確認）
- 直すとよい 6〜10 もすべて採った。6：番兵では check を呼ばない話と、実在の位置に置いた ok を先に確かめる話を分けた。7：count は素朴な走査、triangles は $N \le 200$ で 3 重ループと assert で比べるようにした。8：#interactive の最初にめぐる式へのリンクと一言、両端が番兵として使える理由を足した。9：「$x$ 未満で最大」にした。10：「よく出る」にし、「高々 1 回（番兵まで含めればちょうど 1 回）」とした
- 採らなかった指摘：なし
- 検査：check_pages（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、check_snippets（3 片・期待と違う 0）、textlint（エラー 0・警告 4。前回と同じ 58・96・195 行の誤検出）
