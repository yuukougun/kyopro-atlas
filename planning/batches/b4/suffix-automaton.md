# suffix-automaton の提案（b4）

- 書いたファイル：docs/string/suffix-automaton.md、snippets/suffix-automaton/sam.{cpp,yaml}・lyndon.{cpp,yaml}、docs/img/suffix-automaton/abb.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-22）。sections は変えていない（Suffix Automaton の節の中に H3「自作するときの要点 {#build-your-own}」を置いたが、sections には載せていない）
- 検査：check_pages（エラー・警告 0）、fix_problems --check（0）、check_snippets（2 本・11 case 一致）、textlint（エラー 0、警告 26：「最長共通部分文字列」の漢字の連続、数式を含む文の長さ、数式内の半開区間の括弧の誤検出、助詞の重なり）
- 図：render_svg.py で 360px・720px を目で確かめた（S = abb の SAM。遷移は実線、接尾辞リンクは灰色の点線）
- コード片の確かめ：sam.cpp は長さ 12 までのランダムな文字列 300 本で、各接頭辞の異なる部分文字列の数を総当たりと照合した。一般化 SAM（last を 0 に戻して足す）の数え方も 1000 本で総当たりと照合した（本文の「手元の総当たりで確かめた」）。lyndon.cpp は 500 本で、各片が Lyndon 語で広義に減ることを確かめた
- 新しく noai を確かめたドメイン：arxiv.org（arxiv.org/abs/1506.04862・arxiv.org/abs/1406.0263。X-Robots-Tag・meta とも指定なし）
- そのほかに読んだもの：raw.githubusercontent.com の library-checker-problems の task.md（eertree・lyndon_factorization・runenumerate・longest_common_substring・number_of_substrings）と maspypy/library の string/*.hpp（github.com のリポジトリの生ファイル）

## 台帳への提案

- abc452_g｜evidence｜2 つ目の裏付けは見つからなかった（第三者の解説を検索したが、ABC452 G の記事は ikatakos 氏のもののみ）。ikatakos 氏の記事で、塊の分類（l < c で切る・l = c は残す・l > c は残して切る）と、一般化 SAM の len − len(link) の和、SA＋LCP の別解を確かめた
- abc433_g｜pages｜suffix-automaton を role: practice（または example）で足す案。SAM の状態の DAG の上で「遷移がない状態は手番の負け、負けの状態へ遷移できれば勝ち」を len の大きい順に決めれば解ける（本文の「部分文字列のゲームや数え上げ」の型そのもの）。ただし第三者の解説で SAM による解法を確かめられなかった（ikatakos 氏は SA＋LCP。公式解説が SAM を使うことは検索結果の要約に出たが、atcoder.jp なので開いていない）。裏付けが取れるまでは足さない方がよい

## 用語集への提案

- なし（DAG は既存の語にリンクした。DFA・endpos・接尾辞リンク・Lyndon 語・run は本文で定義し、このページでしか使わないので用語集には足さない）

## 手引きへの提案

- 付録 A（文字列）：「接尾辞リンク」「Lyndon 語」「Lyndon 分解」「回文木」を正規形に足す案（このページでそろえた表記。suffix link・Lyndon word などの別表記を本文で使わない）

## 問題の補充の候補

- abc433_g（G. Substring Game、diff 2060、確認済み・suffix-array の練習）：空から 1 文字ずつ末尾に足して部分文字列であり続けるゲームの勝敗。SAM の状態の DAG 上の勝敗判定。裏付け：https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2025/1122_abc433 （問いの確認と SA＋LCP の解法。SAM の第三者の解説は未確認）
- abc349_g（G. Palindrome Construction、diff 2655、ap.py で実在を確認、台帳になし）：各中心の回文半径から辞書順最小の数列を作る逆 Manacher の型（研究メモ 08 §4.7 の候補）。第三者の解説は見つからなかった（ikatakos 氏の 2024/0413_abc349 の記録は F までで G の節がない）。裏付けが取れれば inverse-string-problems の練習か力試し
- yahoo_procon2018_final_d（D. LCP(prefix,suffix)、diff なし、ap.py で実在を確認、台帳になし）：maspy 氏の inverse_z_algorithm のコメントが参照している逆 Z の問題。内容の第三者の解説は未確認

## 未解決の点

- 回文木の構築の「ならし O(N)」は ei1333 氏のライブラリの記述（O(|S|)）と原論文の「線形サイズ」で裏付けた。原論文の本文の計算量（遷移の持ち方で O(N log σ)）までは読んでいない
- Main-Lorentz 法の説明（周期ごとに左の反転と右の一致の長さの和が 2t 以上かを見る）は、cp-algorithms の要旨と maspy 氏・Nyaan 氏の実装の構成から書いた。細部は資料に任せている
- 公式の解説（atcoder.jp）は開いていない

## 検証の指摘への対応

- 指摘 1〜6 はすべて直した（1：Manacher で集める候補を「鏡に写した値より先で新しく一致した分」に直した。2：「一致の長さ」を「真ん中から周期 t が続く長さ」に言い換えた。3：Duval の周期の取り直しを「S[i, k] 全体の長さ」とした。4：確認問題の 2 問目を abaab・abca に当てる問いに替えた。5：図の {ε} を {空文字列} にした。6：回文木の計算量に「文字の種類を定数とみて、子を配列で持つ場合」を足した。要点と front matter は Suffix Automaton の括弧の条件と並べて読めるので直していない）
- 採らなかった指摘：なし

## 台帳への提案（検証から）

- abc452_g｜checked｜2026-10-22 に更新する案（検証役が ikatakos 氏の記録の解法の節で例題の方針を確かめた）
