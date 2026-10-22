# kth-and-median の報告と提案（b5）

- 書いたファイル：docs/patterns/kth-and-median.md、docs/img/kth-and-median/count-median.svg（コード片なし）
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-22）。sections に `問われ方と手法の一覧 {#overview}` を足した（bracket-sequence の形にそろえた）。k-best の title の括弧内を kth-value から greedy-priority-queue に直した（持ち主の節が greedy-priority-queue#k-best のため。anchor は変えていない）
- 検査の結果：check_pages エラー0・警告0、fix_problems --check 直す行0、textlint エラー0・警告7（図の代替テキストの長さと読点、`[l, r)` の括弧の対応、数式を含む文の読点、参考の題名の「「」、助詞の重なり2か所。誤検出か軽微なので残した）。図は render_svg.py で 360px・720px を目で確かめた
- 使った出典：betrue12.hateblo.jp（付録 B にある）の「「答えを決め打つ」タイプの二分探索を使いこなそう」。ほかの事実は本文のあるページ（kth-value・priority-queue・top-k-multiset・kth-element・segment-tree-on-values・ordered-set・offline-queries・wavelet-matrix・fractional-binary-search・median-absolute・lexicographic-greedy・binomial-coefficient・dp-reconstruction・xor-basis・greedy-priority-queue）の節にそろえた

## 台帳への提案

- なし（このページは問題0。catalog の problems_note・D16 のとおり、表の代表の問題は行き先のページの例題の小見出し・練習へのリンクにした）

## 用語集への提案

- なし（多重集合 #multiset・中央値 #median を使った）

## 手引きへの提案

- pattern のページで問題が0のとき、一覧の表の「代表の問題」の列は、行き先のページの例題の小見出し（`../<field>/<id>.md#<問題ID>`）か `#practice` へのリンクで書いた（§2.5 の「例題の見出しかページへリンク」に従った）。bracket-sequence は自ページの問題の label を文字で書いているので、問題0のページの書き方として §4 の pattern に一言足すとよい

## front matter・catalog への提案

- related に greedy-priority-queue（#k-best の持ち主）、lexicographic-greedy（#kth の持ち主）、parallel-binary-search（区間の K 番目をオフラインで）を足す
- guide/reverse-index-signs の 882〜887 行の「（準備中）」を外す（このページが draft になったため）

## 問題の補充の候補

- 探していない。patterns の目安（例題 0〜1・練習 0〜3）の範囲で、catalog が問題0と決めている

## 未解決の点

- 図の値（1, 3, 3, 6, 8）は kth-value の count-staircase.svg と同じ型の図で、重なりがある。こちらは中央値（5 個の 3 番目）と同じ値での段の飛びを示す向きにした
- #range-kth の「先読みできる区間の K 番目は並列二分探索で BIT の方法が使える」は、parallel-binary-search の what-it-does の一般の説明に頼った。そのページに区間の K 番目の例はない

## 検証の指摘への対応

- 1（直すべき・#absolute-sum）：「$x$ がどの点とも重ならない位置にあるとき、右へ少し動かすと傾きは（左の点の数）−（右の点の数）」に直した
- 2（直すべき・#streaming）：「追加・削除の 1 回ごとに高々 1 個（書き換えは削除と追加の 2 回とみる）」に直した
- 3（#k-best）：例の後に「以下は小さい方から取り出す向きで書く。大きい方からなら値の大小を逆にする」を足し、表の ABC123 D に「（大きい方から）」を添えた
- 4（#dynamic）：「$K$ が小さい、または『$x$ 以上の中で $K$ 番目』のように基準の近くを聞かれる」とし、`begin()` や `lower_bound(x)` から $K$ 歩ほど、に直した
- 5（図）：白丸・黒丸をやめ、不可の段を灰色の線、可の段を青の線にし、整数の位置は小さな点にした。凡例を 12px にした。render_svg.py の 360px で確かめた
- 6（参考）：「判定を『ぴったり』にすると単調性が崩れるという注意（別の問題の解説の中）」に直した
- 採らなかった指摘：なし
