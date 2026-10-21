# nim の報告と提案（工程8b・b1）

- 書いたファイル：docs/comb/nim.md、snippets/nim/nim.{cpp,yaml}、docs/img/nim/winning-move.svg
- front matter で変えたもの：complexity（判定 O(N)、勝つための手の構成 O(N)）・stage（draft）・updated（2026-10-21 のまま）。sections は変えていない
- 検査の結果：check_pages（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、check_snippets（1 件、6 ケースすべて一致）、textlint（エラー 0・警告 11）
  - 残した警告：要点の signs 由来の行（37 行）、図の代替テキストの長さ（80 行）、数式を含む文の助詞の重なり（98・124・156・159 行など）、折りたたみの中の数式の読点（207 行）、台帳の summary 由来の行（230 行）。どれも数式の誤検出か、文を割ると意味が崩れるもの
- コード片：nim.cpp の main の前に自己検査を入れた。3 山・各 0〜7 個の全局面を勝敗の DP で求め、(1) Bouton の定理、(2) winning_move が XOR 0 の局面を作ること、(3) 逆形 Nim の結論、(4) 1〜k 個（k = 1〜4）の上限つき Nim が余りの Nim と同じこと、を assert で確かめている。本文の逆形の節はこの検査に触れている
- 例題・力試しの方針の確認：arc168_b の答え（奇数回現れる値の最大 − 1）と abc172_f の解法（AND を (S − X)/2 で決め、上の位から貪欲）は、一時置き場のスクリプトで小さい全探索と照合した
- 図：winning-move.svg（山 3・4・5 の 2 進表示と XOR、選ぶ山の枠）。描画して目で確かめる道具がなく、XML として読めることと座標の計算だけを確かめた。表示の確認を検証役に頼みたい。catalog の visual は null なので動く図は置いていない
- 使った出典：ja.wikipedia.org「ニム」（判定と逆形の条件）、github.com の kyopro-tessoku answer_A33.cpp、ikatakos の arc168・arc143 のメモ（解説の部分だけ）、kmjp の abc172 F、drken の abc212 H。新しく noai を確かめたドメインはない（どれも付録 B）

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| arc168_b | summary | 1 回に取れる石の数の上限 k を決めた Nim で、先手が必ず勝てるような k の最大値を求める（いくらでも大きくできる場合と、存在しない場合はその旨を出力する）。 | https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2023/1119_arc168#b_-_arbitrary_nim （先手が勝つ k を求める。XOR が 0 でなければ上限なし、奇数回の値がなければ存在しない）。台帳の「後手が必ず勝てる」は誤り。本文は正しい向きで書いた（fix_problems は要約を変えないので、台帳を直すまで本文と台帳が食い違う） |
| arc168_b | approach | 上限 k の Nim は各山を k+1 で割った余りの Nim と同じ。XOR が 0 のとき、奇数回現れる値の最大を M として k = M − 1 | 同上 |
| arc143_c | summary | 先手は X 個、後手は Y 個ずつ、選んだ 1 つ以上の山それぞれから同時に取るゲームで、勝つのはどちらかを求める。 | https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2022/0626_arc143#c_-_piles_of_pebbles （1 手で複数の山を選べることが解法の場合分けに効く。いまの summary では読み取れない）。本文の行は台帳のまま |

ほかの使った問題（tessoku_book_ag・abc172_f・abc212_h）の summary と approach は、evidence と食い違いがなかった。abc212_h は台帳の主の summary（長さ 1〜N の列）を使った。

## 用語集への提案

- ニム和｜nim-sum｜Nim の各山の個数の XOR。0 なら手番の人の負け（Bouton の定理）。Grundy 数の和にも同じ語を使う（本文では用語集にリンクしていない。足すなら nim と grundy-number の最初の出現から）
- 不偏ゲーム｜impartial-game｜どちらの手番でも、同じ局面で打てる手の集まりが同じゲーム。Nim・Grundy 数の議論はこれを前提にする（本文の asymmetric の節で語として使った。リンクはしていない）

## 手引きへの提案

- 例題の解法の詳細で「出力の形」を問題文から確かめられない（問題文を読まない規則）。arc168_b では、いくらでも大きくできる場合と存在しない場合の出力を「問題文の指定に従う」と書いた。第三者の解説に出力の値（-1・0）が書いてあっても、本文には書かない方針でよいか決めてほしい

## 問題の補充の候補

練習が arc143_c の 1 問で、目安（2〜6）に足りない。ap.py の search Nim で見つけた候補（裏付けの解説はまだ読んでいない。台帳には未登録か未確認）：

- arc105_d（D. Let's Play Nim、diff 1871）：袋から皿へ硬貨を移してから Nim をするゲームの勝敗。真似戦略と Nim の組合せと見られる（research の game-mirror-strategy にも挙がる）。裏付けの URL は未確認（第三者の解説を探す必要がある）
- arc091_d（F. Strange Nim、diff 2395）：取れる個数が山ごとに決まる変種で、Grundy 数の周期を求める型と見られる。grundy-number の力試し向き。裏付けの URL は未確認
- abc319 以降の ABC で Nim そのものの問題は ap.py の題名検索では見つからなかった（catalog の problems_note と同じ）

## 未解決の点

- arc143_c の「1 手で 1 つ以上の山を選び、それぞれから同じ個数取る」というルールは ikatakos の解説から読み取ったもので、問題文では確かめていない
- 逆形 Nim の結論は Wikipedia とコード片の全探索で確かめたが、ABC・ARC での出題はない（research §7.2 と同じ）。発展の節として短く置いた
- 前提の game-basics・grundy-number・partizan-games・hadamard-transform・xor-basis はまだ stub なので、ページへのリンクだけにし、節へはリンクしていない。draft になったら、asymmetric の節から game-basics の「手番を状態に入れる」節（turn）へ、bounded の節から grundy-number の patterns へリンクを足すとよい
- 使用量の目安：道具の呼び出し約 25 回、Web 取得 5 回

## 検証の指摘への対応（verify/nim.md）

- 指摘 1（直すべき・台帳）：ページ側は直し済み（本文は正しい向き）。台帳の arc168_b の summary を上の「台帳への提案」どおりに直してから fix_problems を流すよう、改めて提案する
- 指摘 2：直した。$D$ を「出現回数が奇数の正の値」と定め（0 個の山はどの $k$ でも余り 0 で効かない）、「異なる正の値 1 つや 2 つの XOR は 0 にならない」を理由として書いた。制約に頼らない形にした
- 指摘 3：直した。(a)「ちょうど $X$ 個・ちょうど $Y$ 個」と書いた。(b) 2 つ目の箇条を、複数の山から取れるルールで $X \le Y$ のとき先手が余り $X$ 以上の山をまとめて取って戻す側に回れる例に具体化し、場合分けは練習の ARC143 C に任せた
- 指摘 4：直した。#bouton → game-basics#win-lose、#asymmetric → #turn、確認問題の真似戦略 → #mirror-strategy。あわせて「勝敗の DP」のリンク（導入・asymmetric の最後・misere）を #game-dp にした
- 指摘 5：直した。自己検査への言及を消し、「小さい局面なら勝敗の DP で全局面を調べて確かめられる」に言い換えた
- 指摘 6：直した。winning-move.svg の説明文を表の下に移し、viewBox を 340×400 にした（表の文字は 15px のまま、幅 390px の画面でほぼ等倍）。説明は 6 行に分けて短くした。描画しての目視は未確認なので、メインか検証役に一度見てほしい
- 指摘 7（台帳）：上の「台帳への提案」の arc143_c の summary を改めて提案する
- 指摘 8（台帳・メイン）：ページ側では直さない。上の「問題の補充の候補」（arc105_d・arc091_d）の裏付けをメインが取るか、grundy-number と配分を決めてほしい
- 検査：check_pages（エラー 0・警告 0）、fix_problems --check（0）、check_snippets（期待と違う 0）、textlint（エラー 0・警告 11。直す前と同じ種類）
