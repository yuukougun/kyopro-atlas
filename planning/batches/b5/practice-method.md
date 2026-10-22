# b5 practice-method（精進の仕方）の報告と提案

- 書いたファイル：docs/guide/practice-method.md（snippets・図の画像はなし。Mermaid の流れ図を 1 つ本文に置いた）
- front matter で変えたもの：stage（stub → draft）・updated（2026-10-22）。complexity は guide なので null のまま
- 検査の結果：check_pages エラー0・警告0、fix_problems --check 直すべき行0（問題は載せていない）、textlint エラー0・警告2（参考の記事の題名「【入青】凡人が青コーダーになるために」の助詞「に」、「AtCoderで入黄しました！！」の「！」の連続。どちらも題名の引用なので残した）
- リンク：相手の guide・start のページはすべて stub なので、anchor なしのページへのリンクにした（§14-23）。相手が draft になったら次の節へ張り替えるとよい
  - how-to-use → #claude（claude.ai での解説）・#progress（理解したチェック）
  - contest-strategy → #after-contest（原因の切り分け）、速さの目標の時間の節
  - atcoder-system → 生成 AI のルールの節
- 使った出典（どれも付録 B の qiita.com・chokudai.hatenablog.com・github.com。新しいドメインはなし）：
  - E869120 中級編・上級編（解説を見るまでの時間の表、易しい問題を 30 分で 6 問、週 2〜3 回のバーチャル参加、120 分で打ち切り 2 週間〜数か月後に再挑戦、AC 数ごとの黄色の達成割合、精選 100 問の 70 問）
  - drken「AtCoder コンテストについての tips」（解説放送・提出時刻順の提出・検索語）
  - chokudai「競技プログラミングの強みと「典型力」について」（連想できた要素の確認）
  - 色変記事 edon8618・igeee・mkreem・Youteru・siooisi・nouka28・Un_titled（本文の記述はどれも記事を読んで確かめた）
  - AtCoder Problems の FAQ・recommend.md・virtual_contest.md（GitHub）
- 使わなかった資料：USACO Guide の Practicing の諸説（研究 §6.8 にある）は、手引き §11 の「構成の参考だけ」に従い、本文に名前も数値も出していない

## 台帳への提案

- なし（catalog の problems が空で、guide のページなので問題を載せていない）

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| upsolve | upsolve | コンテストで解けなかった問題を、終了後に解説などを使って AC まで持っていくこと。 |
| 解説 AC | editorial-ac | 解説を読んでから実装して AC すること。自力で解いたこととは区別して数えることが多い。 |
| 精進 | shojin | 競技プログラミングで練習を指して使われる言葉。 |
| バーチャル参加 | virtual-participation | 終わったコンテストに、本番と同じ時間の制限で参加して解くこと。AtCoder Problems のバーチャルコンテストも同じ用途に使う。 |
| 色変記事 | color-change-article | AtCoder のレートの色が上がった人が、学んだ内容や練習の方法を振り返って書く記事。 |

- 本文では用語集にリンクしていない（§15-1）。足した後に、upsolve・解説 AC の最初の出現へリンクを張るとよい

## 手引きへの提案

- 横断ページ（guide）で色変記事などの個人の体験を引くときの書き方を決めておくとよい。今回は「氏名（入水・入黄などの時期の区別）＋要旨を自分の言葉で」とし、一人の声を一般化しないよう、異論（Un_titled の類題を勧める考え）も並べた
- guide のページの要点の項目（何のページか・使い方・前提）は、hub・pattern と同じく自由に決めてよいことを §2.2 に明記するとよい（現状でも「guide・start・patterns・hub は項目を内容に合わせて変えてよい」とあり、それに従った）

## 問題の補充の候補

- なし（guide のページで、§10 の数の目安でも問題は不要と判断した）

## 未解決の点

- E869120 上級編の表は、取得した本文の変換で 700 点以上の列と水色・青色の行の対応がはっきりしなかった。本文には研究 §6.8 と一致する 100〜600 点の列だけを載せた
- AtCoder Problems の画面の項目名（Recommendation の除外の選択肢など）はガイドの文面からの確認で、実際の画面は見ていない。「既定では解いた問題を除く」は「Don't exclude solved problems」の選択肢があることから書いた
- 色変記事の時期（入水・入黄）は研究 §2.2.2 の分類に従い、表には括弧で添えた。Youteru は入水、igeee・edon8618 は入黄
- 本文で `/record-problem` の流れを書いたが、how-to-use#record-skill と重なる。how-to-use が draft になったら、こちらは要点だけ残してリンクにするか、メインが持ち主を決めるとよい

## 検証の指摘への対応（2026-10-22）

- 直すべき 2 件（1・2）と直すとよい 3〜10・12〜15 はすべて直した
  - 1：E869120 の表の行を「今の色」として書き、「今の色の行を使う」を 1 文添えた
  - 2：#still-stuck の保留は教材の考えとして書き直し、E869120 上級編の再挑戦は「黄〜橙を目指す段階で、難問を解説なしで考える練習」という文脈を付けて別の段落にした。#upsolve の表の「期間をおいた再挑戦」の出典欄は「教材の考え（E869120 上級編の再挑戦は、難問を解説なしで考えるときの話）」とし、期間も「日をおいてから」にした。okudeottu の記事は読んで確かめていないので使わなかった
  - 3：上級編の 700〜900 点の列を本文の表に足した
  - 14：contest-strategy・how-to-use・atcoder-system がどれも draft になっていたので、§14-23 の張り替えをこのページの中で行った（contest-strategy#after-contest・#time-targets、how-to-use#claude・#progress・#record-skill、atcoder-system#ai-rules）。時間不足の行は #speed へつないだ。メインが改めて張り替える必要はない
- 採らなかったもの：なし
- 11（報告の訂正）：前の報告で chokudai.hatenablog.com を付録 B のドメインとしたのは誤りだった。検証役が check_noai で noai の指定なし（2026-10-22）を確かめている

## 手引きへの提案（追加）

- 付録 B のはてなブログの一覧に chokudai.hatenablog.com を足す（検証の指摘 11。noai・noimageai の指定なしを 2026-10-22 に確かめた）
