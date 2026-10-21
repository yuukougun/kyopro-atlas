# union-find-applications の報告と提案（工程8b・b1）

- 書いたファイル：docs/ds/union-find-applications.md、snippets/union-find-applications/{top-k,pair-max,next-pointer}.{cpp,yaml}、docs/img/union-find-applications/{count-on-merge,next-pointer}.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21 のまま）。sections の title を見出しに合わせて短くした（§13.2。anchor と level は変えていない）。multiple-uf の title の「閾値」は union-find-connectivity の表記に合わせて「しきい値」にした
- 検査の結果：check_pages（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、check_snippets（3 件すべて一致）、textlint（エラー 0・警告 16）
  - 残した警告：no-unmatched-pair（半開区間 $[l, r)$ を括弧の対と誤検出、137・152 行）、sentence-length（図の代替テキスト・数式を含む文・問題の行）、no-doubled-joshi（「道路でも鉄道でも」などの並列。台帳由来の問題の行 277 を含む）
- 動く図：作っていない（visual は priority 2・static）。静的な SVG を 2 枚描いた（重みの昇順に足してサイズの積を数える様子、塗ったマスを飛ばす矢印と経路の半分化）
- 使った出典：ACL document_ja/dsu.md（ローカルの v1.6 で merge の返り値を確認）、drken（abc372_e・abc183_f・arc065_b）、hamayan（abc214_d）、Kazun（abc238_e・abc228_d）、testcampus（zenn、abc420_e）、ikatakos（abc409_f、解説の部分だけ）、Lanly（cnblogs、abc364_f・abc355_f）。題名は各ページの title 要素で確かめた（ikatakos は h1）。新しく noai を確かめたドメインはない（どれも付録 B）

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc372_e | summary | 「k 番目（k ≤ 10）」を「K 番目（K ≤ 10）」に（prh の K 番目の規則でエラーになるため、本文の行はこの形に直した） | 表記の規則（手引き §7） |
| abc183_f・abc355_f・abc364_f | summary | 本文の行は catalog の summary（台帳の alternatives の union-find-applications 向けの summary）を使った。台帳の主の summary と違うので、どちらを正にするかメインで決めてほしい | — |
| abc228_d | evidence | 第三者の解説（Kazun）は set による解法が中心で、Union-Find は別解として計算量だけ触れている。approach（Union-Find で次の空きを指す）を直接裏付ける解説を足すとよい | https://kazun-kyopro.hatenablog.com/entry/ABC/228/D |
| abc131_f | pages | union-find-applications に role: challenge を足す（「何を頂点にするかの言い換え」の x 座標と y 座標の二部グラフの型。本文ではいまは問題 ID を出さず型だけを書いた） | https://drken1215.hatenablog.com/entry/2019/06/23/004700（research 05-ds 付録 A） |

ほかの使った問題（abc214_d・abc238_e・abc420_e・abc409_f・arc065_b）の summary と approach は、evidence の解説と食い違いがなかった。

## 用語集への提案

- なし（本文で用語集へリンクしていない。ならし計算量は前提の union-find のページで説明される想定）

## 手引きへの提案

- §5 ds の「保つ性質・各操作の手順・境界の 3 つの小見出しをそろえる」は、データ構造そのもののページ向けと読んだ。応用のページでは「根に成分の情報を持たせる」「次の空きへ飛ぶ Union-Find」の節の中に太字の段落としてだけ置いた。応用のページでの扱いを明記するとよい
- 骨格の sections の title がかっこ書きつきで長いページが多い。§13.2 で見出しと title をそろえると見出しが長くなるので、骨格の段階で短い title にそろえておくと執筆者の手間が減る

## 問題の補充の候補

- abc131_f（F. Must Be Rectangular!、diff 1937、台帳で確認済み）：長方形の 3 頂点があれば 4 頂点目を足す操作を、最大で何回できるかを求める。x 座標と y 座標を頂点にした Union-Find で、成分ごとに（x の数）×（y の数）の和 − N。裏付け：https://drken1215.hatenablog.com/entry/2019/06/23/004700
- abc380_e（E. 1D Bucket Tool、diff 1230、台帳で確認済み・interval-set の例題）：1 列のマスで、同じ色でつながった区間を塗り替えるクエリと、色ごとのマス数のクエリを処理する。根に区間の左端・右端・色を持たせ、隣と同色なら併合する。練習に足す候補。裏付け：https://drken1215.hatenablog.com/entry/2024/11/17/035045
- abc319 以降で水の帯の候補は、台帳の abc372_e・abc409_f・abc420_e・abc364_f・abc355_f で足りていると判断し、新たには探していない

## 未解決の点

- 次の空きへ飛ぶ Union-Find を経路の半分化だけ（union by size なし）で書いたときの計算量を「1 回ならし O(log N)」と書いた。Tarjan と van Leeuwen の結果（経路圧縮・半分化だけなら $O(m \log_{1+m/n} n)$）に基づく記憶で、資料では確かめていない。検証役に確認を頼みたい
- abc214_d の制約（N と重みの上限）は解説から読み取れず、本文では「N = 10^5 では間に合わない」と目安だけを書いた。合計が long long に収まるかは本文で見積もり方だけを示した
- 図 2 枚は描画して目で確かめる道具がなく、XML として読めることと座標の計算だけを確かめた。文字のはみ出し（特に count-on-merge.svg の右側の注記）を検証役に見てほしい
- 「値を頂点にする」の型（値の書き換えで一致させる最小回数 = 併合に成功した回数）は、台帳に対応する問題がないので型だけを書いた
