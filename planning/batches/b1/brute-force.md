# brute-force（全探索の設計）の報告と提案

- 書いたファイル：docs/basics/brute-force.md、snippets/brute-force/fix-two.{cpp,yaml}、snippets/brute-force/board-shift.{cpp,yaml}、docs/img/brute-force/fix-two.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21 のまま）。sections に `{title: 上位の手法へのつながり（残りを速くする・重複をまとめる）, anchor: next-steps}` を足した（手引き §4 の基礎の構成「上位の手法とのつながり」に当たる中身の節）
- 検査：check_pages エラー 0・警告 0／fix_problems --check 直す行 0／check_snippets 2 本とも期待どおり／textlint エラー 0・警告 7（図の代替テキストの長さ、折りたたみの中の行がまとめて 1 文と数えられたもの、`[0, k)` の半開区間の括弧、「前から・後ろから」の「から」の重複。どれも誤検出か意図した表現）
- 図：visual は priority 2 の static。「3 重ループと 2 つ決めて 3 つ目を計算」の比較は SVG（fix-two.svg）にし、「探索の対象を入れ替えたときの通り数」は本文の表（small-candidates の節）にした。動く図は作っていない

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc469_d | summary | N 人から 2 人を選ぶとき、M 回のどの大会でも、選んだ 2 人の少なくとも一方が決勝に出ているような選び方の数を求める。 | https://qiita.com/comet725/items/5783b8e77e3ef99c72c6 （解法のコードから読んだ問いなので、未解決の点を参照） |
| sumitb2019_d | evidence | https://qiita.com/c-yan/items/cd3076c0a66eada87152 を足す（今の evidence は類題のリンク集で、解き方の裏付けにならない） | 同 URL（番号 000〜999 の側を全探索、N ≤ 30000） |

## 用語集への提案

- 正規化（盤面の型）｜normalize-shape｜型の空いた行と列を取り除き、左上に詰めた形にそろえること。回転・平行移動の全探索で、試す移動量の範囲を小さくする。※本文ではリンクしていない。用語集に入れるかはメインの判断

## 手引きへの提案

- 基礎の technique の構成「上位の手法とのつながり」に、標準の見出しと anchor（例：`## 上位の手法へのつながり {#next-steps}`）を決め、sections に載せるかを §13.1 に明記するとよい。見本の binary-search-answer も next-steps を sections に載せている

## 問題の補充の候補

台帳にない（または他ページの担当の）問題で、このページの節の型に合うもの。本文では ID を出していない。

| 問題 ID | 何を問うか | 使う型（節） | 裏付けの URL |
| --- | --- | --- | --- |
| abc051_b | 0 以上 K 以下の X, Y, Z で X+Y+Z = S となる組を数える | what-to-enumerate（コード片 fix-two と同じ形。練習向き） | https://drken1215.hatenablog.com/entry/2019/07/06/221600 |
| arc096_a | A・B・AB ピザの買い方で費用を最小にする（AB ピザの枚数だけ全探索） | what-to-enumerate（残りの最良がすぐ決まる型。本文で型だけ触れた） | https://qiita.com/e869120/items/eb50fdaece12be418faa |
| typical90_p | 3 種類の硬貨でちょうど N 円払う最小枚数（2 種類を全探索し 3 種類目は割り算） | what-to-enumerate（割り切れるかの確認） | https://github.com/Reputeless/tenkei_90 |
| abc089_c | 頭文字ごとに人数を数え、5 文字から 3 つを選ぶ 10 通りを試す | small-candidates（同じ種類をまとめる） | https://blog.hamayanhamayan.com/entry/2018/03/05/003346 |
| abc476_d | （research/00 §2.3.8 で「全探索＋累積和＋二分探索」）問いは未確認 | half-enumeration | https://qiita.com/comet725/items/fb0182ba408f04fa3a59 （未読） |
| abc474_e | （同「ソート＋境界の全探索＋累積和・累積 min」）問いは未確認 | half-enumeration（分け目の全探索） | ikatakos.com の abc474 の記録（未読） |

half-enumeration の節は、いま練習に該当する問題がない。frequency_evidence に挙がった abc474_e・abc476_d・abc480_e のどれかを台帳で確かめて練習に足すのがよい（abc469 以降の新しい ABC で、水への入口の型）。

## 未解決の点

- abc469_d の問い：comet725 氏の記事には問題の要旨がなく、コードから「どの大会でも決勝進出者の少なくとも 1 人を含む 2 人組の数」と読んだ。順序なしの組か、同じ人を 2 回選べるかは確かめていない。ikatakos 氏の記録の解法の部分で確かめてほしい（問題文を引用した節は読んでいない）
- typical90_bk の方針（行を全探索し、列ごとに値がそろうかを見て最頻の値の列数 × 行数）は、裏付けが Reputeless の一覧（キーワード）だけで、第三者の詳しい解説を読んでいない。W の上限も本文に書かなかった
- move-board の節（水）に「追加の前提」として bit-full-search を挙げたが、本当に要る前提は特にない。「上位の帯の節は最初に追加の前提を示す」の規則に合わせただけなので、不要なら削ってよい
- 本文の数字列の例で「N = 3 × 10^4 なら」と書いた値は c-yan 氏の記事（検索結果の要約）で N ≤ 30000 とあることに基づく

## 使用量の目安

- 道具の呼び出し 約 30 回、Web 取得 5 回（drken 3・qiita 1・検索 1）、curl で題名の確認 6 件
