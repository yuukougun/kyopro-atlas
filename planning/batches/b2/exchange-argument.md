# exchange-argument の報告（b2）

- 書いたファイル：docs/basics/exchange-argument.md、snippets/exchange-argument/{weighted-order,concat}.{cpp,yaml}、docs/img/exchange-argument/adjacent-swap.svg
- front matter で変えたもの：complexity・stage（draft）・updated。sections は変えていない
- 構成：level 青・technique の構成（§14-6）。ただし基礎の分野なので、各節に応用の型を入れて短めにし、落とし穴・上位の手法へのつながりを置いた
- 検査の結果：check_pages エラー 0・警告 0、fix_problems --check 0、check_snippets 2 本とも通過（どちらも小さい n で全順列と assert で比べている）、textlint エラー 0・警告 14（すべて no-doubled-joshi。数式を含む文の誤検出と、言い換えると読みにくくなる文）
- 図：adjacent-swap.svg を render_svg.py で 360px・720px にして目で確かめた
- 使った出典：drken の ABC131 D・ABC116 D・ABC163 E の記事（例題・力試しの方針）、cppreference の Compare。Johnson の規則の非推移の例・(0, 0) の例・連結のキーは、手元の Python と C++ の全探索で確かめた。新しく noai を確かめたドメインはない

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc467_f | pages | exchange-argument の challenge から外す（または summary を確かめるまで保留） | 下の「未解決の点」。本文には載せていない |
| abc467_f | summary | （執筆時に確かめる）のまま。ikatakos.com がメンテナンス中（HTTP 503）で読めず、ほかの第三者の解説も検索で見つからなかった | https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2026/0718_abc467 |
| abc471_f | note | K 個の選び方の裏付けは今回も取れていない（ikatakos.com が 503）。本文の方針は「並べ方は a+b と b+a、選び方は別に考える」までにとどめた | 同上 0815_abc471 |
| abc366_f | pages の exchange-argument 用の summary | 本文は台帳の主の summary（f_i(x) = A_i x + B_i …）を使った。alternatives の短い summary に替える必要はない | — |

## 用語集への提案

- なし（狭義の弱順序 `strict-weak-ordering` は既存）
- 検討：Johnson の規則（2 台の機械のスケジューリング）。本文で名前だけ出した。用語集に載せるなら「Johnson の規則｜johnsons-rule｜2 台の機械を同じ順に通す仕事の並べ方で、a_i < b_i の仕事を a の小さい順に先、残りを b の大きい順に後に置くと終了時刻が最小になる」

## 手引きへの提案

- 交換論法で導いた比較は、`t_i w_j < t_j w_i` の掛け算の形のまま書く。(0, 0) を除き、符号が混じるならグループに分ける（§5 basics に 1 行足す案）。ratios の節を持ち主にして、sorting-techniques#ratio-and-ties・exchange-argument-dp#compare-ratios からはリンクで済ませるとよい
- exchange-argument-dp の compare-ratios 節は、この ratios 節と内容が重なる。DP のページでは比の比較の説明を繰り返さず、ここへリンクする分担を提案する

## 問題の補充の候補

- 補充は見送った。例題 2・練習 2・力試し 1 で目安を満たしている。abc467_f を外すと力試しは 1 問になる
- 候補を探すなら：ABC167 F（括弧列を並べる。patterns/bracket-sequence の例と共通。2 組に分けてソートする狭義の弱順序の例として、本文の strict-weak-ordering 節の練習に向く）。台帳の状態と第三者の解説は未確認なので、メインで ap.py と解説を確かめてほしい

## 未解決の点

- abc467_f（catalog では力試し）は、evidence の ikatakos.com が 503（メンテナンス中）で問いを確かめられず、本文に載せなかった。サイトが戻ったら summary を確かめて力試しに足す
- abc471_f の練習の方針は、選び方の詳細（先頭に 0 がある文字列をどう選ぶか）を書いていない。裏付けが取れたら折りたたみに足す
- 骨格の要点の「何ができるか」の先頭に「並べる順で結果が変わる問題で、」を足した（summary とは食い違わない）

## 検証の指摘への対応（b2）

- 直すべき 1・2、直すとよい 3〜8 はすべて採った。採らなかったものはない
  - 1：#ratios の条件を「向きの幅が 180 度未満（開いた半平面＋境界の片側の半直線）」に直し、「符号が混じる」の箇条を「点が原点の両側に散らばる」に替えた。負の $w$ で割る注意は「比のキーに直すとき」の別の箇条にした。#pitfalls もそろえた
  - 2：ABC163 E の理由を、遠い側の端の幼児との入れ替え（三角不等式と $A_p$ 最大）に替えた
  - 3：Johnson の規則を「< なら i を先に置いて悪くならない」とし、手順 2 は成り立たず単調性で言うことを足した。表の「x を z より先に置く方が得」も「先に置く」にした
  - 4：「隣接交換をそのまま使うことはできない」にした
  - 5：#concatenation と練習の方針から「桁数を多くすることが先」「桁数を稼ぐ」を外した
  - 6・7：指摘どおり
  - 8：図を幅 480 にし、下の 3 行の注記を外して文字を 15〜17px にした。破線は文字に重ならないよう行ごとに切った。代替テキストから差の式の文を外した。render_svg.py の 360px・720px で確かめた
- 検査：check_pages エラー 0・警告 0、fix_problems --check 0、check_snippets 2 本通過、textlint エラー 0・警告 14（no-doubled-joshi と、連結の数式の行の文の長さ。どちらも前からのもの）

### 台帳への追加の提案（検証から）

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc131_d | checked | 2026-10-21 | drken の記事で問いを確かめた（検証の「問題がなかった点」） |
| abc163_e | checked | 2026-10-21 | 同上 |
| abc471_f | note | K 個の選び方は未確認のまま残す（本文からは「桁数を多くすることが先」も外した） | ikatakos.com が検証時も 503 |
