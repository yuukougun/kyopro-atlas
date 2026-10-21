# prefix-sum-counting の報告（工程8b・バッチ b1）

- 書いたファイル：docs/basics/prefix-sum-counting.md、snippets/prefix-sum-counting/count-equal-k.{cpp,yaml}・count-multiple.{cpp,yaml}、docs/img/prefix-sum-counting/pairs.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21）。sections に `{title: XOR・不等式・最長の区間へのつながり, anchor: next-steps}` を足した（基礎の構成の「上位の手法とのつながり」に当たる）
- 検査の結果：check_pages（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、check_snippets（2 片・期待と違う 0。どちらも n ≤ 2000 で全区間の素朴な数え上げと assert で照合）、textlint（エラー 0・警告 21。ほとんどが数式の中の `[l, r)` の括弧の対応・数式を含む文の長さと読点の数の誤検出。41 行目の「が」の重複は signs の文言そのまま）
- 図：catalog の visual（static・priority 2）を静的な SVG 1 枚にした（A = (2, −1, 1, 2, −2)、K = 2 の累積和と、和が 2 の区間 5 個を弧で示し、S_0 から出る 3 個を破線で区別）。手元に SVG の描画の道具がなく、見た目は目視で確かめていない（XML として正しいことだけ確かめた）。連想配列の中身のステップ送りは作っていない
- 使った出典：drken1215.hatenablog.com（abc233_d・abc105_d・abc164_d・abc367_d・abc146_e）、ikatakos.com（abc473_e、解説の部分だけを WebFetch の指示で読ませた）。drken の agc023_a の記事も読んだが、本文は Qiita への案内だけだった。新しく noai を確かめたドメイン：なし

## 台帳への提案

- abc473_e｜summary｜「数列から互いに重ならない連続部分列を選ぶとき、和が K の倍数のものを最大でいくつ選べるかを求める。」｜https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2026/0829_abc473 （本文の行はこの文で書いた。fix_problems は台帳の summary が「（執筆時に確かめる）」のため行を変えなかった）
- abc473_e｜approach｜「余りの一致で区間を見つけ、見つかるたびに区切って集合を空にする貪欲（最も早く終わる区間を取る）」｜同上
- abc146_e｜approach｜「余りが K 未満なので長さも K 未満。(S_i − i) mod K（a_i − 1 の累積和の余り）の一致を長さ K − 1 以下の窓の中で数える」に具体化｜https://drken1215.hatenablog.com/entry/2024/11/23/183549 （drken の解説は a_i − 1 ではなく S_i − i の形。同じものだが両方書くと探しやすい）
- abc367_d｜approach｜「2 周分に伸ばした累積和の余りが等しく、添字の差が N 未満の組を数える（窓）」に具体化｜https://drken1215.hatenablog.com/entry/2024/08/21/084614

## 用語集への提案

- 連想配列｜associative-array｜キー（値）からその値に結び付いたデータを引ける入れ物。C++ では `map`（順序付き、1 回 O(log N)）と `unordered_map`（ハッシュ、期待 O(1)）がある。（本文では stl-containers のページへリンクした）

## 手引きへの提案

- §7 に「リンク先のページがまだ stub のときは、節の anchor を付けずにページへリンクする（draft 以降になったら anchor を足す）」の運用を明記するとよい。今回 stl-containers・digit-and-mod・integer-division・reformulation の節へは anchor なしでリンクした。これらが draft になったら、次の節へのリンクに直す候補：stl-containers#counting-map・#pitfalls、digit-and-mod#p-2-5、integer-division#floor-ceil、reformulation#separate-indices
- SVG の見た目を確かめる道具（rsvg-convert など）が環境にない。検証役に図の目視を頼むか、道具を入れるとよい

## 問題の補充の候補

- agc023_a｜A. Zero-Sum Ranges（diff 1038、ap.py で実在を確認）｜区間和が 0 の区間を数える（累積和が等しい組の数）｜https://drken1215.hatenablog.com/entry/2019/12/25/123932 （ただしこの記事の本文は Qiita の記事への案内だけで、問いの中身は記事からは確かめきれていない。research 01 §4.E の表に載っている）。練習の易しい側（abc233_d と abc473_e の間）か、確認問題「和が 0 の区間」の対応問題に向く。台帳に載れば aliases の「Zero-Sum Ranges」とも合う
- abc455_e（Unbalanced ABC Substrings）：frequency_evidence に挙がっているが、台帳では complement のページの練習だけで、このページには載せていない。「個数が等しい区間」（next-steps の 2 つ目）の型に近い可能性があるが、解説を読んで確かめていない

## 未解決の点

- abc473_e の問いは ikatakos 氏の記録の解法の部分から読み取った（問題文を引用した部分は使っていない）。「数列を区切ったときの和が K の倍数のピースの数の最大」と「重ならない区間を選ぶ個数の最大」のどちらの言い方が問題文に近いかは確かめきれていない（値は同じ）。検証で別の第三者の解説があれば照合してほしい
- 「円環を伸ばして数える」の節は、窓の範囲を max(0, r − N + 1) ≤ l ≤ min(r − 1, N − 1)、r を 1〜2N − 2 と書いた。手で確かめたが、コード片での確認はしていない
- 「後ろからの累積」の節は digit-and-mod#suffix-remainder と内容が重なる。こちらは手順の要点だけにしたが、どちらに詳しく書くかはメインで判断してほしい

- 使用量の目安：道具の呼び出し 約 30 回、Web 取得 11 回（WebFetch 9・検索 2）
