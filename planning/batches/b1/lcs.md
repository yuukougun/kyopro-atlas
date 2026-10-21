# lcs の報告（工程8b・バッチ b1）

- 書いたファイル：docs/dp/lcs.md、snippets/lcs/（lcs.{cpp,yaml}・edit-distance.{cpp,yaml}・lcs-row-dp.{cpp,yaml}）、docs/img/lcs/table.svg
- front matter で変えたもの：complexity・stage（draft）・updated。sections は変えていない
- 検査の結果：check_pages エラー 0・警告 0。fix_problems --check 直すべき行 0。check_snippets 3 組で期待と違う 0（lcs-row-dp は Python の別実装と、26^M の全探索（M ≤ 3）で期待値を作った）。textlint エラー 0、警告 28（数式を含む文の長さ・数式の中の読点・「最長共通部分文字列」の漢字の連続・証明の折りたたみの中の長い文。規則の誤検出か用語そのもの）
- 使った出典：drken の Qiita（EDPC F）、drken1215.hatenablog.com（abc185_e・abc141_e・abc130_e・agc021_d）、kmjp.hatenablog.jp（abc391_g）、www.cnblogs.com/wanggk（abc391_g の制約 N ≤ 10・M ≤ 100 と計算量。付録 B にあるドメイン。check_noai でも指定なしを確認）
- 新しく noai を確かめたドメイン：zenn.dev の記事 1 件を確認したが G がなく使わなかった（ドメインは付録 B にある）。新しいドメインはない

## 台帳への提案

- agc021_d｜approach｜「S と反転の LCS（＝最長回文部分列）を、書き換えた回数も状態にした区間 DP で求める。左右から文字を組にしていく DP でもよい」｜根拠：evidence の drken の記事は区間 DP ではなく「分割点を決めて左右から文字を組にする dp[i][j][k]」で解いている。区間 DP dp[l][r][k] は私が小さい場合の全探索で正しさを確かめた（N ≤ 6、K ≤ N の 150 例）が、区間 DP で解いた第三者の解説の URL は見つけていない。evidence に区間 DP の解説を足すか、approach を記事の方法に合わせてほしい
- abc130_e｜summary（任意）｜「…組の数を求める（空の列どうしの組も 1 つと数える）」を足すかどうか。drken の記事の式は空の組を含めて数えている（dp[0][0] = 1 を答えに含める）が、問題文は確かめていない（atcoder.jp を開けないため）。本文の練習の方針では「空の列どうしの組も数える形（初期値 1）」と書いた
- abc391_g｜summary（任意）｜制約が分かるよう「（|S| ≤ 10、M ≤ 100）」を足すと、問題の行だけで DP の DP の状態数の見当が付く。根拠：https://www.cnblogs.com/wanggk/p/-/atcoder
- evidence の追加：abc391_g に https://www.cnblogs.com/wanggk/p/-/atcoder（制約と O(N M 2^N) の前計算の説明）

## 用語集への提案

- 部分列｜subsequence｜列からいくつかの要素を、順番を保ったまま（飛び飛びでよい）取り出した列。連続していなければならない部分文字列とは別物である（本文では string-basics#substring-vs-subsequence にリンクしたので必須ではない）
- 最長共通部分列｜—｜用語集ではなくページ lcs が持ち主なので不要

## 手引きへの提案

- §8 の Mermaid：dp-of-dp の節で、行の遷移図を Mermaid の flowchart（4 状態・自己ループあり）で書いた。自己ループのラベルの描画は手元で確かめていない。CDN が欠けても前後の文章で要点が通じるよう、遷移を文でも書いた
- §6 の記法：反転した文字列の記号が手引きにない。本文では $S^R$ を使った。決めておくと揃う
- 「DP の DP」の正規形：付録 A の DP の行に「DP の DP」がない。別名の行には載っている。ページ lcs の節になったので、付録 A に足すかどうかの判断を

## 問題の補充の候補（問題ID・何を問うか・裏付けの URL）

- abc386_f（F. Operate K、diff 1875、青）｜文字列 S を K 回以下の挿入・削除・置換で T にできるか（K ≤ 20、長さは 5×10^5 まで）。編集距離が K 以下かの判定で、|i − j| ≤ K の帯だけを埋める｜https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2024/1228_abc386 （ikatakos 氏の記録は解説の部分だけを使うこと）、https://www.tunamaguro.dev/articles/2024/12/abc386/ （新しいドメイン。check_noai は未実施）。役割は練習か力試し。abc319 以降の水〜青の LCS 型がないという catalog の見立てを補える。本文の編集距離の節には、問題 ID を出さずに「距離が K 以下かだけを問われたら帯だけを埋める」という型を書いた
- 検索の結果：ap.py で LCS・Edit・Subsequence・Common・Palindrome・Distance を abc の diff 1000 以上で探したが、ほかに LCS の表を直接使う abc319 以降の問題は見つからなかった（abc377_g Edit to Match は Trie の問題）

## 未解決の点

- 図 table.svg は手元に SVG の描画の道具がなく、表示を目で確かめていない（座標は生成スクリプトで計算した）。検証役に表示の確認を頼みたい
- catalog の visual（priority 2）の「1 文字足すと別の行に移る遷移図」は Mermaid で代えた。動く図は作っていない
- 使い分けの「片方の列の値がすべて違えば LCS は LIS に帰着する」は既知の事実として書いたが、出典を付けていない。検証役に確かめてほしい（位置に読み替えた列の狭義増加部分列の最長と一致する）
- abc185_e は台帳の approach では「編集距離の変形」だが、本文では「編集距離そのもの」と書いた（A の削除＝削除、B の削除＝挿入、不一致＝置換で、コストがすべて 1）。drken の記事の遷移は Levenshtein と同じ形である
- 使用量の目安：道具の呼び出し 約 45 回、Web 取得 約 12 回（検索 3 回を含む）

## 検証の指摘への対応（verify/lcs.md）

- 1（直すべき）：string-basics へのリンク 2 か所を `../string/string-basics.md#substring-vs-subsequence` に直した
- 2（直すべき）：table.svg の代替テキストの経路を「斜め・左・斜め・左・斜め」に直した
- 3（直すとよい）：table.svg の viewBox を 680×468 から 460×570 に詰め（表を左へ寄せ、上下の説明を改行）、説明の文字を 15px、添字のラベルを 14px に上げた。幅 358px でも約 0.78 倍で読める。Windows の Chrome（headless）で描いて重なり・はみ出しがないことを目で確かめた
- 4（直すとよい）：要点の計算量に DP の DP の $O(\sigma M 2^N)$ を足し、front matter の complexity とそろえた
- 5（直すとよい）：#count-pairs の別の数え方に、$\mathrm{dp}[0][0] = 1$（空の組）・答えは表全体の和・行ごとに埋めながら累積和を作れることを足した
- 6（直すとよい）：#dp-of-dp で、前の節とは行と列を入れ替えて $T$ の先頭 $i$ 文字を行にすることを一言添えた
- 7（直すとよい）：popcount の初出の文に、`std::popcount` は C++20 の `<bit>` の関数で符号なしの型だけを受け取るので `unsigned` に変換すること、cpp-math-functions#bit-functions へのリンクを足した
- 採らなかったもの：なし
- 「メインへ」の項（abc185_e・agc021_d の approach、abc130_e の summary、abc391_g の evidence、checked、check_pages の壊れたリンクの検出）は台帳・道具の側なので、上の「台帳への提案」とあわせてメインの判断に任せる。abc185_e｜approach｜「編集距離そのもの（削除・挿入・置換がどれもコスト 1）」を提案に加える
